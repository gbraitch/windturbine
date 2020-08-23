/*
 * Take analog read from A2 for voltage every interrupt and add to sum, display the average every 100 reads and reset
 *                       A3     current  
 *                       A4     voltage from potentiometer
 */


void AnalogSensor()
{
  VS_count++;
  VS_sum += analogRead(VS_inputPin);
  WS_sum += analogRead(WS_inputPin);
  CS_sum += analogRead(CS_inputPin);
  if(VS_count == 100){
    // Voltage Calculations
    VS_sum /= (float)VS_count;                  // Divide by VS_count to get average voltage
    VS_sum *= (5.0/1023.0);                     // Multiply by 5/1023 to get the actual voltage value
    VS_sum = VS_sum/(R2/(R1+R2));               // Reverse voltage divider to get real voltage

    // Current Calculations
    CS_sum /= (float)VS_count;                  // Divide by VS_count to get average
    CS_sum *= (5.0/1023.0);           
    CS_sum /= 1.75;                             // Use formula derived from sample points to convert voltage
                                                // to current                                                
    // Voltage calculations from potentiometer
    WS_sum /= (float)VS_count;
    WS_sum *= (5.0/1023);
    WS_val = WS_sum;
    
    // Pass values to power calculation                                            
    PC_voltage = VS_sum;   
    PC_current = CS_sum;      
    PC_power = PC_voltage * PC_current;
   
    // Display values on serial print
    Serial.print("Voltage Sensor = ");
    Serial.print(VS_sum, 4);
    Serial.println("V");
    
    Serial.print("WSensor Voltage = ");
    Serial.print(WS_val, 4);
    Serial.println("V");
    
    Serial.print("Current = ");
    Serial.print(CS_sum, 3);
    Serial.println("A");

    Serial.print("Power =");
    Serial.print(PC_power, 4);
    Serial.println("W");

    dutycycle = (int)((float)(duty3_2)/1023 * 100);
    
    Serial.println(dutycycle);
    Serial.println(boostup);
    Serial.println();
    
    /*
    Serial.print(",");
    Serial.print(VS_sum, 4);
    Serial.print(" V");
    Serial.print(",");
    Serial.print(CS_sum, 3);
    Serial.print(" A");
    Serial.print(",");
    Serial.print(WS_val, 4);
    Serial.print(" V");
    Serial.print(",");
    Serial.print(PC_power, 4);
    Serial.print(" W");
    Serial.print(",");
    Serial.print(dutycycle,1);
    Serial.print(" ?");
    Serial.println(",");
*/
    ble.print(",");
    ble.print(VS_sum, 4);
    ble.print(",");
    ble.print(CS_sum, 3);
    ble.print(",");
    ble.print(WS_val, 4);
    ble.print(",");
    ble.print(PC_power, 4);
    ble.print(",");
    ble.print(dutycycle,1);
    ble.println(",");
    
    // Reset counter and sum vals
    VS_count = VS_sum = CS_sum = WS_sum = 0;
  }
}
