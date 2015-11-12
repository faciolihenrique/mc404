all:
		arm-eabi-as -g ra157986.s -o ra157986.o & arm-eabi-ld ra157986.o -o ra157986 -g --section-start=.iv=0x778005e0 -Ttext=0x77800700 -Tdata=0x77801800 -e 0x778005e0 & mksd.sh --so ra157986 --user faz_nada 
