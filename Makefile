
#create executable
output: ./build/main.o ./build/lib/sqlite3.o
	g++ ./build/main.o ./build/lib/sqlite3.o -lpthread -ldl -o exe

./build/main.o: main.cpp ./build/node_types.o ./build/db_manager.o
	g++ -c main.cpp -o ./build/main.o

./build/node_types.o: node_types.h ./build/node_classes.o
	g++ -c node_types.h -o ./build/node_types.o

./build/node_classes.o: node_classes.h
	g++ -c node_classes.h -o ./build/node_classes.o

./build/db_manager.o: db_manager.h ./build/sql_manager.o
	g++ -c db_manager.h -o ./build/db_manager.o

./build/sql_manager.o: sql_manager.h
	g++ -c sql_manager.h -o ./build/sql_manager.o


./build/lib/sqlite3.o: ./lib/sqlite3.c
	gcc -O2 -c ./lib/sqlite3.c -o ./build/lib/sqlite3.o

#delete build files
clean:
	rm ./build/*.o

clean-all:
	rm ./build/*.o ./build/lib/*.o exe
