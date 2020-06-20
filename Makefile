CC=gcc -Wall -Werror -O2 -lm
CCTEST= $(CC) src/utils.c
BINDIR=./bin
EXDIR=$(BINDIR)/excercises
TESTDIR=$(BINDIR)/tests

build:
	mkdir -p $(EXDIR)
	mkdir -p $(TESTDIR)

ex:
	$(CC) excercises/projectile.c src/tuples.c src/utils.c src/canvas.c src/colors.c -o $(EXDIR)/projectile
	$(CC) excercises/analog.c src/matrix.c src/tuples.c src/utils.c src/canvas.c src/colors.c -o $(EXDIR)/analog
	$(CC) excercises/shadow.c src/ray.c src/matrix.c src/tuples.c src/utils.c src/canvas.c src/colors.c -o $(EXDIR)/shadow

bst:

build-tests:
	$(CCTEST) tests/utils.c -o $(TESTDIR)/utils
	$(CCTEST) src/tuples.c tests/tuples.c -o $(TESTDIR)/tuples
	$(CCTEST) src/colors.c src/tuples.c tests/colors.c -o $(TESTDIR)/colors
	$(CCTEST) src/canvas.c src/colors.c src/tuples.c tests/canvas.c -o $(TESTDIR)/canvas
	$(CCTEST) src/matrix.c src/tuples.c tests/matrix.c -o $(TESTDIR)/matrix
	$(CCTEST) src/ray.c src/tuples.c src/matrix.c src/sphere.c tests/ray.c -o $(TESTDIR)/ray
	$(CCTEST) src/sphere.c src/tuples.c src/matrix.c tests/sphere.c -o $(TESTDIR)/sphere

test: build-tests
	$(TESTDIR)/tuples
	$(TESTDIR)/utils
	$(TESTDIR)/colors
	$(TESTDIR)/canvas
	$(TESTDIR)/matrix
	$(TESTDIR)/ray
	$(TESTDIR)/sphere

clean:
	rm -rf ./bin/excercises/*
	rm -rf ./bin/tests/*
	find ./tests -type f ! -iname "*.c" -delete
	find ./excercises -type f ! -iname "*.c" -delete
