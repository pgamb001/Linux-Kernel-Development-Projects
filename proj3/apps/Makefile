CC=gcc
CPP=gpp
CROSS_COMPILE=arm-linux-gnueabihf-
all: program1 program2

program1: mem_alloc.c

	$(CROSS_COMPILE)$(CC) -o mem_alloc mem_alloc.c

program2: mem_allock_lock.c

	$(CROSS_COMPILE)$(CC) -o mem_allock_lock mem_allock_lock.c
