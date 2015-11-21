#include "api_robot.h" /* Robot control API */

void delay();

/* main function */
void _start(void) 
{
  unsigned int distances[16];

  /* While not close to anything. */
  do {
      if(read_sonar(3) < 1200)
          set_speed_motors(30, 0);
      else if(read_sonar(4) < 1200)
          set_speed_motors(0, 30);
      else
          set_speed_motors(30,30);
  } while (1);
}

/* Spend some time doing nothing. */
void delay()
{
  int i;
  /* Not the best way to delay */
  for(i = 0; i < 10000; i++ );  
}
