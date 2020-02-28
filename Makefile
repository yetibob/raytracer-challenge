GCCTEST=gcc -lm src/utils.c

build:
	mkdir -p bin

build-excercises:
	gcc -lm excercises/projectile.c src/tuples.c src/utils.c src/canvas.c src/colors.c -o excercises/projectile

build-tests:
	$(GCCTEST) src/tuples.c tests/tuples.c -o tests/tuples
	$(GCCTEST) tests/utils.c -o tests/utils
	$(GCCTEST) src/colors.c src/tuples.c tests/colors.c -o tests/colors
	$(GCCTEST) src/canvas.c src/colors.c src/tuples.c tests/canvas.c -o tests/canvas
	$(GCCTEST) src/matrix.c src/tuples.c tests/matrix.c -o tests/matrix

test: build-tests
	./tests/tuples
	./tests/utils
	./tests/colors
	./tests/canvas
	./tests/matrix

clean:
	rm -rf ./bin
	find ./tests -type f ! -iname "*.c" -delete
	find ./excercises -type f ! -iname "*.c" -delete
