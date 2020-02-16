build:
	mkdir -p bin

build-excercises:
	gcc -lm excercises/projectile.c src/tuples.c src/utils.c -o excercises/projectile

build-tests:
	gcc -lm src/tuples.c src/utils.c tests/tuples.c -o tests/tuples
	gcc src/utils.c tests/utils.c -o tests/utils

clean:
	rm -rf ./bin
	find ./tests -type f ! -iname "*.c" -delete
