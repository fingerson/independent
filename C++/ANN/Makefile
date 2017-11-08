output: bin obj main ann
	g++ ./obj/* -o ./bin/output

bin:
	mkdir ./bin

obj:
	mkdir ./obj

main: obj main.cpp
	g++ -I./lib -g -c main.cpp -o ./obj/main.o

ann: obj ./src/ann.cpp ./lib/ann.h
	g++ -I./lib -g -c ./src/ann.cpp -o ./obj/ann.o

run: output
	./bin/output

debug: output
	gdb ./bin/output

clean:
	rm ./obj/*
	rm ./bin/*
