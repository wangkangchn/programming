C++ = g++ -g
CC = gcc -g

max_profit:
	${C++} max_profit.cpp -o app_max_profit 

insertion_sort:
	${CC} insertion_sort.c -o app_insertion_sort

bubble_sort:
	${CC} bubble_sort.c tools.c -o app_bubble_sort

selection_sort:
	${CC} selection_sort.c tools.c -o app_selection_sort

clean:
	rm -rf app*