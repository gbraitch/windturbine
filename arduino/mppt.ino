void mppt()
{
  if(PC_power >= oldPower) // new value is higher than old value, continue doing what you were doing
  {
    oldPower = PC_power;
  }
  else // new value is lower than old value, do opposite of what you were doing
  {
    boostup *= -1;
    oldPower = PC_power;
  }      
}


/*
 * MPPT: Make sure most power is being achieved by 
 * detecting wind direction and keeping boost converter 
 * between 12-15 V whilst adjusting the PWM to get the most power
 */
