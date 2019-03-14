	#Makefile for HW5
#Author: Michael Escue
#Assignment: HW5
#Due Date: 03/06/19 

C = gcc
obs = hw5.o printids.o randarray.o
hdrs = randarray.h printids.h

#Homework 1
all: hw5
again: clean hw5

hw5: hw5.o printids.o randarray.o
	$(C) $(obs) -g -o $@.exe

bubblesort: bubblesort.o randarray.o 

debug: hw5.o printids.o randarray.o
	$(C) $(obs) -g -D VERBOSE -o $@.exe
	
hw5.o: hw5.c 
	$(C) -c -g hw5.c
	
printids.o: printids.c printids.h
	$(C) -c -g printids.c
	
randarray.o: randarray.c randarray.h
	$(C) -c -g randarray.c 

clean: 
	rm $(obs)


