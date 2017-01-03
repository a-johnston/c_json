build: src/json.h src/*.c
	mkdir -p include bin lib
	cp src/json.h include/json.h
	cd bin/; \
	gcc -fpic -fno-strict-aliasing -O3 -Wall -Werror -Wextra -c ../src/*.c ../src/json.h ;\
	gcc -shared -fpic -fno-strict-aliasing -O3 -Wall -Werror -Wextra -o ../lib/libjson.so *.o -lc

install: lib/libjson.so include/json.h
	sudo cp lib/libjson.so /usr/lib/
	sudo cp include/json.h /usr/local/include/
