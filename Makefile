all: main
	g++ main.o -o factorial -std=c++14

main:
	g++ -c main.cc -std=c++14

clear:
	rm main.o
	rm factorial

run:
	./factorial
