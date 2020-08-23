void StepperMotorControl()
{   
  if(Step_counter >= Step_countTarget)
  {
    dir = 0;
    Step_counter = 0;
    Step_start = 0;
    Step_ready = 1;
    Step_current_pos = Step_degree;
  }
  else
  {
    Step_counter++;              
    myStepper.step(dir);
  }
}
