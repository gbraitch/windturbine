#define mid 1.35

void WindSensor()
 {
  if(Step_ready)
  {
    if((WS_val-mid) >= 0.1)
    {
      dir = -1;
    }
    else
    {
      if((WS_val-mid) <= -0.1)
      {
        dir = 1; 
      }
      else
      {
        dir = 0;
      }
    }
  }
  Step_countTarget = 15;
  
  Step_start = 1;   //Start motor
  
 }


/*
void WindSensor()
{
  if(Step_ready == 1){
    Step_degree = 124.4*WS_val;
    if((Step_degree - Step_current_pos) == 0)
    {
      dir = 0;
      Step_countTarget = 0;
    }   
    else
      if( (Step_degree - Step_current_pos) > (Step_current_pos - Step_degree))
      {
        dir = 1;
        Step_countTarget = (Step_degree - Step_current_pos)/0.176;
      }
      else
      {
        dir = -1;
        Step_countTarget = (Step_current_pos - Step_degree)/0.176;
      }
    
    Step_start = 1;   //Start motor
    Step_ready = 0;   //Don't take any more keyboard inputs
  }
}

/*
 * Want to make it so potentiometer faces the wind head on ->|<- , thus not moving 
 * We will find its middle point voltage value, and use that our reference
 * If the voltage value increases, we will rotate the base of the turbine to decrease the value
 *                      decreases,                                           increase the value
 * Goal is to keep that voltage value constant, thus the wind turbine gets the most possible amount
 * of wind, and thus produces the largest amount of power
 */
 
