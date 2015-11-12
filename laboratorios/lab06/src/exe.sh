arm-eabi-as motors.s -o motors.o 
arm-eabi-ld motors.o -o motors -Ttext=0x77802000 
mksd.sh --so /home/specg12-1/mc404/simulador/simulador_player/bin/knrl --user motors 
player /home/specg12-1/mc404/simulador/simulador_player/worlds_mc404/simple.cfg 

