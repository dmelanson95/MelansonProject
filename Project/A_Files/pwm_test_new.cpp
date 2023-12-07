/*
 * Modified by Amer Qouneh on: July 24 2020
 * The original code used old directory and file names.
 * It also used old names for duty_cycle and enable.
 * Added sleep() and included <unistd>.
 * Added a call to set duty_cycle as nano seconds.
 * Added a call to stop().
 *
 *
 *
 * pwm_test.cpp  Created on: 3rd Feb 2015
 * Copyright (c) 2014 Derek Molloy (www.derekmolloy.ie)
 * Made available for the book "Exploring BeagleBone"
 * See: www.exploringbeaglebone.com
 * Licensed under the EUPL V.1.1
 *
 * This Software is provided to You under the terms of the European
 * Union Public License (the "EUPL") version 1.1 as published by the
 * European Union. Any use of this Software, other than as authorized
 * under this License is strictly prohibited (to the extent such use
 * is covered by a right of the copyright holder of this Software).
 *
 * This Software is provided under the License on an "AS IS" basis and
 * without warranties of any kind concerning the Software, including
 * without limitation merchantability, fitness for a particular purpose,
 * absence of defects or errors, accuracy, and non-infringement of
 * intellectual property rights other than copyright. This disclaimer
 * of warranty is an essential part of the License and a condition for
 * the grant of any rights to this Software.
 *
 * For more details, see http://www.derekmolloy.ie/
 */

#include<iostream>
#include"PWM.h"      //placed in the current directory for ease of use

#include<unistd.h>

using namespace exploringBB;
using namespace std;

int main(){
  
  PWM pwm("pwm-1:0");               // Directory name in new images

  pwm.setPeriod(100u);          // Set period in ns

  //pwm.setDutyCycle(10.0f);        // Set duty cycle as a percentage
  pwm.setDutyCycle(1u);       // Set duty cycle as nano seconds.
                                    // Rotate to 0 degrees.
  // Add u after the integer to indicate that it is unsigned otherwise shows error.

  cout << "Setting to 1 percent." << endl;

  pwm.setPolarity(PWM::ACTIVE_HIGH); // using active low PWM

  pwm.run();                        // start PWM output
  cout << "Starting PWM output." << endl;
  sleep(2);
  
  pwm.setDutyCycle(25u);        // Set duty cycle as nano seconds
                                    // Rotate to -90 degrees.
  cout << "Setting to 25 percent." << endl;
  sleep(2);

  pwm.setDutyCycle(50u);        // Set duty cycle as nano seconds
                                    // Rotate to +90 degrees.
  cout << "Setting to 50 percent." << endl;
  sleep(2);

  pwm.setDutyCycle(75u);        // Set duty cycle as nano seconds
                                    // Rotate to -90 degrees.
  cout << "Setting to 75 percent." << endl;
  sleep(2);

  pwm.setDutyCycle(100u);        // Set duty cycle as nano seconds
                                    // Rotate to -90 degrees.
  cout << "Setting to 100 percent." << endl;
  sleep(2);
  
  pwm.stop();                        // stop PWM output
  cout << "Stopping PWM output." << endl;
}
