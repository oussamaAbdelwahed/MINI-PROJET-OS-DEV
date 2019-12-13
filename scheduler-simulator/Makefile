scheduler: rr.o srt.o fcfs.o gateway.o
	gcc gateway.o -o sched-algs
	gcc rr.o -o rr-scheduler
	gcc srt.o -o srt-scheduler
	gcc fcfs.o -o fcfs-scheduler
	
rr.o: gateway.c rr.c srt.c fcfs.c colors.h
	gcc -c gateway.c
	gcc -c rr.c
	gcc -c srt.c
	gcc -c fcfs.c

clean:
	rm *.o rr-scheduler srt-scheduler fcfs-scheduler sched-algs


