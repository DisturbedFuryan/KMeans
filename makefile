CC=g++
CFLAGS=-c -std=c++0x -Wall


all: KMeans

KMeans: main.o KMeans.o Cluster.o Object.o Timer.o Utility.o Vector.o
	$(CC) main.o KMeans.o Cluster.o Object.o Timer.o Utility.o Vector.o -lrt -o KMeans

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
	
KMeans.o: KMeans.cpp
	$(CC) $(CFLAGS) KMeans.cpp

Cluster.o: Cluster.cpp
	$(CC) $(CFLAGS) Cluster.cpp
	
Object.o: Object.cpp
	$(CC) $(CFLAGS) Object.cpp

Timer.o: Timer.cpp
	$(CC) $(CFLAGS) Timer.cpp

Utility.o: Utility.cpp
	$(CC) $(CFLAGS) Utility.cpp

Vector.o: Vector.cpp
	$(CC) $(CFLAGS) Vector.cpp

clean:
	rm -rf *.o KMeans
