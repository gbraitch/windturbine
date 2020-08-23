//Boost Converter Constants

#define boost_low 10          // Min output voltage
#define boost_high 15         // Max output voltage

// Use nested loops so only one if statement can be triggered in each call to BoostControl
void BoostControl()
{ 
  if(PC_voltage < boost_low) dutychange(-1, 4);             //Voltage below 1V, decrease duty cycle
    else{
      if(PC_voltage > boost_high) dutychange(-1, 2);            //If voltage above 15V, increase duty cycle
      else
      {
        if(boostup == 1) dutychange(1, 2);                  // MPPT wants duty cycle increased
        else dutychange(-1,2);                        // MPPT wants duty cycle decreased
      }
    }
  } 


void dutychange(int sign, int inc)
{
  if(sign == 1) duty3_2 += inc;
  else duty3_2 = duty3_2 - inc;
  
  if(duty3_2 >= 1023) duty3_2 = 1023;
  if(duty3_2 <= 0) duty3_2 = 0;
  Timer3.setPwmDuty(2, duty3_2);
}
