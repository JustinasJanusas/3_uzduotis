compile:
	gcc -I`readlink -f ../lib` -L`readlink -f ../lib` -o reader reader.c -llogger -Wl,-rpath=-L`readlink -f ../lib`
	gcc -I`readlink -f ../lib` -L`readlink -f ../lib` -o writer1 writer1.c -llogger -Wl,-rpath=-L`readlink -f ../lib`
	gcc -I`readlink -f ../lib` -L`readlink -f ../lib` -o writer2 writer2.c -llogger -Wl,-rpath=-L`readlink -f ../lib`