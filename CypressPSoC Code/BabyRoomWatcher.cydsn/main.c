/*
    Project:    While you were away
    By:         Inderpreet Singh
    Ver:        0.1
*/

#include <project.h>
#include <my_macros.h>


/* Function Prototypes */
void InitResources(void );
CY_ISR(TIMEBASE_ISR);
__inline uint16 CalculateCapacitance(uint16 rawCounts, uint16 refSensorCounts);
__inline uint16 CalculateHumidity(uint16 capacitance);


// Declare i2cbuffer to exchange data.
psoc_data i2cBuffer = {
                        THREE_FEET,             /* PIR detection distance */
                        SENSOR_RAW_INITIAL,     /* ADC result */
                        PIR_WINDOW_HIGH_3FT,    /* High threshold for motion detection */
                        PIR_WINDOW_LOW_3FT,     /* Low threshold for motion detection */
                        MOTION_NOT_DETECTED,    /* Motion detection flag */
                        0x0000, //Temperature
                        0x0000, //Illuminicance
                        0x0000  //Humidity
};
// ****************************************************************************************************
int main()
{
	int16 sensorRawValue = 0; /* Sensor raw value */
    int16 highThreshold = PIR_WINDOW_HIGH_3FT;	/* Motion detection thresholds */	                           
	int16 lowThreshold = PIR_WINDOW_LOW_3FT;
    uint8 prevDetectionDistance = THREE_FEET; // Variable that stores previous detection distance
    uint8 interruptState = 0; /* Variable to store the status returned by CyEnterCriticalSection() */
   
	int16 filterInput; /* These are used for firmware low pass filter input and output */
	int32 filterOutput = 0;
	
    int16 alsCurrent;     /* Variable to store sensor current and light illuminance */
    uint16 illuminance;
    int16 adcResult;
    
    int16 adcResultVREF, adcResultVTH; /* Variables to hold the the ADC readings */
    int16 filterOutputVref=0;     /* Filter input and output variables for Vref and Vth measurements */
    int16 filterOutputVth=0;
    int16 thermistorResistance, temperature;     /* Variables to hold calculated resistance and temperature */
    uint16 capacitance=0;
    uint16 humidityRawCounts=0;
    uint16 rawCountsRefCap;
    
    //uint8 light;
    
    CyGlobalIntEnable; /* Enable global interrupts */ 
    InitResources();    /* Initialize all the hardware resources */
    
    for(;;)
    {   
        /* If the master(BCP) changed the detection distance, change the second stage 
            amplifier (PGA) gain and the thresholds for the required detection distance*/
        if (i2cBuffer.detectionDistance != prevDetectionDistance)
        {
            prevDetectionDistance = i2cBuffer.detectionDistance;
            switch (i2cBuffer.detectionDistance) /* Set the required detection distance */
            {
                case THREE_FEET:
                    /* Set second stage PGA gain and thresholds that gives 
                        3 feet detection distance */
                    PIRAmplifierStage2_SetGain(PIRAmplifierStage2_GAIN_1);
                    highThreshold = PIR_WINDOW_HIGH_3FT;
                    lowThreshold = PIR_WINDOW_LOW_3FT;
                    break;
                case TEN_FEET:
                    /* Set second stage PGA gain and thresholds that gives 
                        10 feet detection distance */
                    PIRAmplifierStage2_SetGain(PIRAmplifierStage2_GAIN_2);
                    highThreshold = PIR_WINDOW_HIGH_10FT;
                    lowThreshold = PIR_WINDOW_LOW_10FT;
                    break;
                case TWENTY_FEET:
                    /* Set second stage PGA gain and thresholds that gives 
                        20 feet detection distance */
                    PIRAmplifierStage2_SetGain(PIRAmplifierStage2_GAIN_32);
                    highThreshold = PIR_WINDOW_HIGH_20FT;
                    lowThreshold = PIR_WINDOW_LOW_20FT;
                    break;
                default:
                    /* Set second stage PGA gain and thresholds that gives 
                        3 feet detection distance */
                    PIRAmplifierStage2_SetGain(PIRAmplifierStage2_GAIN_1);
                    highThreshold = PIR_WINDOW_HIGH_3FT;
                    lowThreshold = PIR_WINDOW_LOW_3FT;
                    break;
            }
        }            
        
        // Select Channel and start conversion for PIR
        if(ADC_IsEndConversion(ADC_RETURN_STATUS)) /* Check if ADC data is ready */
        {
            sensorRawValue = ADC_GetResult16(ADC_CHANNEL_PIR); /* Read ADC result */
            if((sensorRawValue > highThreshold) ||  /* Check if motion is detected */
               (sensorRawValue < lowThreshold)){
                Timebase5s_Stop(); /* Stop the timer */
				Timebase5s_WriteCounter(Timebase5s_TC_PERIOD_VALUE); /* Reload the counter */
                Timebase5s_Start(); /* Start the 5s timer */
				i2cBuffer.motionDetected = MOTION_DETECTED; /* Update the status of motion detection */
//                Pin_LED_Write(LED_ON); /* Turn ON the LED */
                
                interruptState = CyEnterCriticalSection();
        	    if(!(EzI2C_EzI2CGetActivity() & EzI2C_EZI2C_STATUS_BUSY)){
                    /* Update I2C Buffer */
                    i2cBuffer.sensorRawValue = sensorRawValue;
			        i2cBuffer.highThreshold = highThreshold;
			        i2cBuffer.lowThreshold = lowThreshold;
                }
                CyExitCriticalSection(interruptState);        
            }
        } 
		
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Code for Ambient Light stuff
        // Select and start ADC conversion for Ambient Light
        if(ADC_IsEndConversion(ADC_RETURN_STATUS))
		{			
			adcResult = ADC_GetResult16(ADC_CHANNEL_ALS);	/* Get the ADC result */
			filterInput = adcResult; /* Low pass filter the ADC result */
    		filterOutput = (filterInput + (FILTER_COEFFICIENT_ALS - 1)*filterOutput)/FILTER_COEFFICIENT_ALS;
			alsCurrent = (filterOutput * ALS_CURRENT_SCALE_FACTOR_NUMERATOR)/ALS_CURRENT_SCALE_FACTOR_DENOMINATOR;  /* Calculate the photodiode current */
			/* If the calculated current is negative, limit it to zero */
			if(alsCurrent < 0)
			{
				alsCurrent = 0;
			}
			illuminance = (alsCurrent * ALS_LIGHT_SCALE_FACTOR_NUMERATOR)/ALS_LIGHT_SCALE_FACTOR_DENOMINATOR;						/* Calculate the light illuminance */
            
            interruptState = CyEnterCriticalSection();
        	if(!(EzI2C_EzI2CGetActivity() & EzI2C_EZI2C_STATUS_BUSY)){
                /* Update I2C Buffer */
                // i2cBuffer.alsCurrent = alsCurrent;
		        i2cBuffer.illuminance = illuminance;
            }
            CyExitCriticalSection(interruptState);
        }
        
        
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Code for Temperature Measurement
        // Select and start ADC Conversion for Thirmistor
        
        if(ADC_IsEndConversion(ADC_RETURN_STATUS))
        {
            adcResultVREF = ADC_GetResult16(ADC_CHANNEL_VREF); /* Read the ADC result for reference and thermistor voltages */
            adcResultVTH = ADC_GetResult16(ADC_CHANNEL_VTH);
            /* Low pass filter the measured ADC counts of Vref */            
            filterOutputVref = (adcResultVREF + (FILTER_COEFFICIENT_TEMPERATURE - 1) * filterOutputVref) / FILTER_COEFFICIENT_TEMPERATURE;
            /* Low pass filter the measured ADC counts of Vth */         
            filterOutputVth = (adcResultVTH + (FILTER_COEFFICIENT_TEMPERATURE - 1) * filterOutputVth) / FILTER_COEFFICIENT_TEMPERATURE;
            /* Calculate thermistor resistance */
            thermistorResistance = Thermistor_GetResistance(filterOutputVref, filterOutputVth);           
            /* Calculate temperature in degree Celsius using the Component API */
            temperature = Thermistor_GetTemperature(thermistorResistance);
            
            interruptState = CyEnterCriticalSection();
        	if(!(EzI2C_EzI2CGetActivity() & EzI2C_EZI2C_STATUS_BUSY)){
                /* Update I2C Buffer */
                //i2cBuffer.Vth = filterOutputVth;
		        //i2cBuffer.Rth = thermistorResistance;
                i2cBuffer.temperature = temperature;
            }
            CyExitCriticalSection(interruptState);
        }
        
        /* Check if CapSense scan is complete */
        if(!(CSD_IsBusy()))
        {       
            /* Enter critical section to check if I2C bus is busy or not */
            interruptState = CyEnterCriticalSection();

            if(!(EzI2C_EzI2CGetActivity() & EzI2C_EZI2C_STATUS_BUSY))
            {
               // i2cBuffer.humidityRawCounts = CSD_BUTTON0_SNS0_RAW0_VALUE;
               // i2cBuffer.rawCountsRefCap = CSD_BUTTON0_SNS1_RAW0_VALUE;
                /* Convert raw counts to capacitance */
               // i2cBuffer.capacitance = CalculateCapacitance(i2cBuffer.humidityRawCounts, i2cBuffer.rawCountsRefCap);
                capacitance = CalculateCapacitance(humidityRawCounts, rawCountsRefCap);
                /* Calculate humidity */
                i2cBuffer.humidity = CalculateHumidity(capacitance);                
            }
            CyExitCriticalSection(interruptState);
            /* Scan sensors */
            CSD_ScanAllWidgets();
        }
        
        /*  Set up I2C as master */
        /* Attempt to initiate communication with the slave until the function
         * completes without error.
         */
        
        //do
        {
            /* automatically writes a buffer of data to a slave
             * device from start to stop.
              */
        //    light = I2C_1_I2CMasterWriteBuf(I2C_1_I2C_SLAVE_ADDRESS, (uint8 *)&i2cBuffer,
                            //            WR_BUFFER_SIZE, I2C_1_I2C_MODE_COMPLETE_XFER);
        }
        //while (light != I2C_1_I2C_MSTR_NO_ERROR);

        /* Wait for the data transfer to complete */
        //while(I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_XFER_INP);
    }    
}

/*******************************************************************************
* Function Name: void InitResources(void)
*******************************************************************************/
void InitResources(void)
{
    /* Start EZI2C Slave Component and initialize buffer */
    EzI2C_Start();
    EzI2C_EzI2CSetBuffer1(sizeof(i2cBuffer), READ_WRITE_BOUNDARY, (uint8*)&i2cBuffer);
   
    
    /* Enable LED timebase ISR */
    isr_Timebase5s_Start();
    isr_Timebase5s_StartEx(TIMEBASE_ISR);   
    
    /* Start the Scanning SAR ADC Component and start conversion */
    ADC_Start();
    ADC_StartConvert();
    
    /* Start the Reference Buffer */
    RefBuffer_Start();
    
    /* Start Programmable Voltage Reference */
    PVref_Start();
    
    /* Enable Programmable Voltage Reference */
    PVref_Enable();
    
    /* Start the first stage amplifier */
    PIRAmplifierStage1_Start();
    
    /* Start the second stage amplifier (PGA) */
    PIRAmplifierStage2_Start();    
    
    // Start Opamp 1
    Opamp_1_Start();
    
    /* Start CapSense Component */
    CSD_Start();    
    
    //I2C_1_Start(); 
 }

/*******************************************************************************
* Function Name: CY_ISR(TIMEBASE_ISR)
********************************************************************************/
CY_ISR(TIMEBASE_ISR)
{
   	/* Reset the motion detection flag */
    i2cBuffer.motionDetected = MOTION_NOT_DETECTED;
    /* Turn OFF the LED */
//    Pin_LED_Write(LED_OFF);
    /* Stop the 5s timer */
    Timebase5s_Stop();
}

__inline uint16 CalculateCapacitance(uint16 rawCounts, uint16 refsensorCounts)
{
    return (uint16)((float)(rawCounts - OFFSETCOUNT) * (CREF - COFFSET) / (float)(refsensorCounts - OFFSETCOUNT));
}

__inline uint16 CalculateHumidity(uint16 capacitance)
{
    int16 humidity;
    int16 delta;
    
    /* Find capacitance difference from nominal capacitance at 55% RH */
    delta = capacitance - CAPACITANCE_AT_55_RH;
    
    /* Calculate humidity from capacitance difference and sensor sensitivity */
    humidity = ((delta * SENSITIVITY_DENOMINATOR) / SENSITIVITY_NUMERATOR) + NOMINAL_HUMIDITY;
    
    /* If humidity is less than zero, limit it to 0; If humidity is greater than 1000 (100%), limit to 1000 */
    humidity = (humidity < HUMIDITY_0_PERCENT) ? HUMIDITY_0_PERCENT : (humidity > HUMIDITY_100_PERCENT) ? HUMIDITY_100_PERCENT : humidity;

    /* Return Humidity value */
    return humidity;
}



/* [] END OF FILE */
