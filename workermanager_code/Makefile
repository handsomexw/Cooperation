CC=gcc
BIN=project
OBJ=system.o teacher.o main.o student.o principal.o
FLAG=-DDEBUG
STD=-std=gnu99

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ) && ./$(BIN)

main.o:main.c system.h student.h teacher.h principal.h
	gcc -c main.c
student.o:student.c student.h teacher.h system.h
	gcc -c student.c
teacher.o:teacher.c teacher.h system.h student.h principal.h
	gcc -c teacher.c
principal.o:principal.c principal.h system.h teacher.h
	gcc -c principal.c
system.o:system.c system.h student.h teacher.h principal.h
	gcc -c system.c

clean:
	rm -f $(BIN) $(OBJ)

