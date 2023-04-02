#include <signal.h>
#include <stdio.h>  //printf()
#include <stdlib.h> //exit()

#include "DEV_Config.h"
#include "PCA9685.h"

void Handler(int signo) {
  // System Exit
  printf("\r\nHandler:Program stop\r\n");

  IIC_Write(MODE2, 0x00);
  DEV_ModuleExit();

  exit(0);
}

int main(int argc, char **argv) {
  int i;
  if (DEV_ModuleInit() == 1)
    return 1;

  // Exception handling:ctrl + c
  signal(SIGINT, Handler);
  // PCA9685 initialization
  Init_PCA9685();

  int j = 0;
  PCA9685_Set_Rotation_Angle(0, 0);
  PCA9685_Set_Rotation_Angle(1, 120);
  DEV_Delay_ms(125);
  while (1) {
    for (i = 10; i < 135; i += 3) {
      PCA9685_Set_Rotation_Angle(0, i);
      DEV_Delay_ms(125);
    }

    j = (j + 10) % 70;
    PCA9685_Set_Rotation_Angle(1, 120 + j);

    for (i = 10; i < 135; i += 3) {
      PCA9685_Set_Rotation_Angle(0, 135 - i);
      DEV_Delay_ms(125);
    }

    j = (j + 10) % 70;
    PCA9685_Set_Rotation_Angle(1, 120 + j);
  }
  DEV_ModuleExit();
  return 0;
}
