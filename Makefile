CC = gcc
CFLAGS = -g3
SOURCES = main.c primes.c hashfunction.c list.c myRecordDef.c
OBJECTS = $(SOURCES:.c = .o)
EXECUTABLE = myphones

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

main.o: main.c
	$(CC) $(CFLAGS) main.c

primes.o: primes.c
	$(CC) $(CFLAGS) primes.c

hashfunction.o: hashfunction.c
	$(CC) $(CFLAGS) hashfunction.c

list.o: list.c
	$(CC) $(CFLAGS) list.c

myRecordDef.o: myRecordDef.c
	$(CC) $(CFLAGS) myRecordDef.c

clean:
	rm -rf *o $(EXECUTABLE)
