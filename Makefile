
#create executable
output: ./build/main.o ./build/node_types.o ./build/sqlite3.o
	g++ ./build/main.o ./lib/sqlite3.o -lpthread -ldl -o exe

./build/main.o: main.cpp
	g++ -c main.cpp -o ./build/main.o

./build/node_types.o: node_types.h
	g++ -c node_types.h -o ./build/node_types.o

./build/sqlite3.o: ./lib/sqlite3.c
	gcc -O2 -c ./lib/sqlite3.c -o ./build/sqlite3.o

#delete build files
clean:
	rm ./build/*.o exe
