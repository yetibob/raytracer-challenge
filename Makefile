build:
	echo "building"

build-tests:
	gcc src/tuples.c tests/tuples.c -o tests/tuples

clean:
	rm -rf ./bin/*
	find ./tests -type f ! -iname "*.c" -delete
