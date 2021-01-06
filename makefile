all:
	gcc -o bin/my_serial.exe -Ishared my_serial.c -Lbin -lgimxserial