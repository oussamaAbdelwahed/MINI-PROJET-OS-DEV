main-gateway: main-gateway.o
	gcc main-gateway.o -o main-gateway
	
	
main-gateway.o: main-gateway.c
	gcc -c main-gateway.c

clean:
	rm *.o main-gateway



