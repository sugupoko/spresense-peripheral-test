/**
 * @enum ParamSat
 * @brief Satellite system
 */

void shell_cmdregister(void)
{
  shell_register(command_help, PSTR("help"));
  shell_register(command_led, PSTR("led"));
  shell_register(gnss_task, PSTR("gnss"));
  shell_register(accelerometer_task, PSTR("accel"));
  shell_register(airpressure_task, PSTR("airpre"));
  shell_register(geomagnetic_task, PSTR("geomag"));
  shell_register(ble_task, PSTR("ble"));
  shell_register(cam_task, PSTR("cam"));
  shell_register(audplay_task, PSTR("audplay"));
  shell_register(audrec_task, PSTR("audrec"));
}


/**
 * @enum ParamSat
 * @brief Satellite system
 */

int command_help(int argc, char** argv)
{
  shell_print_commands();
  return SHELL_RET_SUCCESS;
}


/**
 * @enum ParamSat
 * @brief Satellite system
 */

int command_led(int argc, char** argv)
{
  char c;
    
  led_setup();
  
  Serial.println("If you want to stop, please press E. ");
  for(;;) 
  {
    led_loop();

    if (Serial.available() > 0) {
        c = Serial.read();
        Serial.println(c);
        if (c == 'E'){
            break;
        }            
    }
  }
  return SHELL_RET_SUCCESS;
}

/**
 * @enum ParamSat
 * @brief Satellite system
 */

int gnss_task(int argc, char** argv)
{
  char c;
  gnss_setup();

  Serial.println("If you want to stop, please press E. ");
  for(;;) 
  {
    gnss_loop();

    if (Serial.available() > 0) {
        c = Serial.read();
        Serial.println(c);
        if (c == 'E'){
            break;
        }            
    }
  }
  return SHELL_RET_SUCCESS;
}

/**
 * @enum ParamSat
 * @brief Satellite system
 */
int accelerometer_task(int argc, char** argv)
{
  char c;
  acceleromete_setup();

  Serial.println("If you want to stop, please press E. ");
  for(;;) 
  {
    acceleromete_loop();

    if (Serial.available() > 0) {
        c = Serial.read();
        Serial.println(c);
        if (c == 'E'){
            break;
        }            
    }
  }
  return SHELL_RET_SUCCESS;

}

/**
 * @enum ParamSat
 * @brief Satellite system
 */
int airpressure_task(int argc, char** argv)
{
  char c;
  airpressure_setup();

  Serial.println("If you want to stop, please press E. ");
  for(;;) 
  {
    airpressure_loop();

    if (Serial.available() > 0) {
        c = Serial.read();
        Serial.println(c);
        if (c == 'E'){
            break;
        }            
    }
  }
  return SHELL_RET_SUCCESS;

}

/**
 * @enum ParamSat
 * @brief Satellite system
 */
int geomagnetic_task(int argc, char** argv)
{
  char c;
  geomagnetic_setup();

  Serial.println("If you want to stop, please press E. ");
  for(;;) 
  {
    geomagnetic_loop();

    if (Serial.available() > 0) {
        c = Serial.read();
        Serial.println(c);
        if (c == 'E'){
            break;
        }            
    }
  }
  return SHELL_RET_SUCCESS;

}

/**
 * @enum ParamSat
 * @brief Satellite system
 */
int ble_task(int argc, char** argv)
{
  char c;
  ble_setup();

  Serial.println("If you want to stop, please press E. ");
  for(;;) 
  {
    ble_loop();

    if (Serial.available() > 0) {
        c = Serial.read();
        Serial.println(c);
        if (c == 'E'){
            break;
        }            
    }
  }
  return SHELL_RET_SUCCESS;

}

/**
 * @enum ParamSat
 * @brief Satellite system
 */
int cam_task(int argc, char** argv)
{
  char c;
  cam_setup();

  Serial.println("If you want to stop, please press E. ");
  for(;;) 
  {
    cam_loop();

    if (Serial.available() > 0) {
        c = Serial.read();
        Serial.println(c);
        if (c == 'E'){
            break;
        }            
    }
  }
  return SHELL_RET_SUCCESS;

}

/**
 * @enum ParamSat
 * @brief Satellite system
 */
int audplay_task(int argc, char** argv)
{
  char c;
  audplay_setup();

  Serial.println("If you want to stop, please press E. ");
  for(;;) 
  {
    audplayloop();

    if (Serial.available() > 0) {
        c = Serial.read();
        Serial.println(c);
        if (c == 'E'){
            break;
        }            
    }
  }
  return SHELL_RET_SUCCESS;

}

/**
 * @enum ParamSat
 * @brief Satellite system
 */
int audrec_task(int argc, char** argv)
{
  char c;
  audrec_setup();

  Serial.println("If you want to stop, please press E. ");
  for(;;) 
  {
    audrec_loop();

    if (Serial.available() > 0) {
        c = Serial.read();
        Serial.println(c);
        if (c == 'E'){
            break;
        }            
    }
  }
  return SHELL_RET_SUCCESS;

}







