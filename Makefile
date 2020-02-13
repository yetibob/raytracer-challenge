build:
	mkdir -p bin
	echo "building"

build-tests:
	gcc src/tuples.c tests/tuples.c -o tests/tuples
	gcc src/utils.c tests/utils.c -o tests/utils

clean:
	rm -rf ./bin
	find ./tests -type f ! -iname "*.c" -delete
