ludo:fonction_nana.c fonction_nana.h main_nana.c
	gcc -o ludo fonction_nana.c main_nana.c -g -O0 -lm -lpthread -fopenmp 

run_ludo:ludo
	./ludo 
run_valgrind:ludo
	valgrind  --tool=memcheck --leak-check=yes --leak-resolution=low --show-reachable=yes  ./ludo
clean:
	rm  ludo

profile:
	gcc -Wall -pg fonction_nana.c main_nana.c -lm -lpthread -o ludo

