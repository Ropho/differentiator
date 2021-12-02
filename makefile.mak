CC = g++

main.o: main.cpp
	$(CC) main.cpp func.cpp libr\libr_tree_diff.cpp -o a