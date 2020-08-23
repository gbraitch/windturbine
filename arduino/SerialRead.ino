static char input_line [50];

void SerialRead(){

  if(Serial.available() > 0 && Step_ready == 1){
    while (Serial.available () > 0){
    processIncomingByte (Serial.read ());
    }
    
    Step_degree = atoi(input_line);  //Convert char array to integer
    // Compute the shortest path

    if(abs(Step_degree - Step_current_pos) < ((360 - Step_degree) + Step_current_pos)){
      dir = (Step_degree - Step_current_pos)/abs(Step_degree - Step_current_pos);
      Step_countTarget = abs(Step_degree - Step_current_pos)/0.176; 
    }
    else{
      dir = - 1;
      Step_countTarget = ((360 - Step_degree) + Step_current_pos)/0.176;
    }
    
    Step_start = 1;   //Start motor
    Step_ready = 0;   //Don't take any more keyboard inputs
  }
}

// read value from serial monitor, can only read one byte at a times
// taken from http://www.gammon.com.au/serial
void processIncomingByte (const byte inByte){  
  static unsigned int input_pos = 0;

  switch (inByte){ 
    case '\n':   // end of text
      input_line [input_pos] = 0;  // terminating null byte    
      // terminator reached! process input_line here ...
      input_pos = 0;  // reset buffer for next time 
      break;
    case '\r':   // discard carriage return
      break;
    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (50 - 1))
        input_line [input_pos++] = inByte;
      break;
    } 
  } 
