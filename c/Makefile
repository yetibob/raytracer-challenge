CC=gcc -Wall -Werror -O2
CCTEST= $(CC) src/utils.c
BINDIR=./bin
EXDIR=$(BINDIR)/excercises
TESTDIR=$(BINDIR)/tests

LIBS=-lm

build:
	mkdir -p $(EXDIR)
	mkdir -p $(TESTDIR)

ex:
	$(CC) excercises/projectile.c src/tuples.c src/utils.c src/canvas.c src/colors.c -o $(EXDIR)/projectile $(LIBS)
	$(CC) excercises/analog.c src/matrix.c src/tuples.c src/utils.c src/canvas.c src/colors.c -o $(EXDIR)/analog $(LIBS)
	$(CC) excercises/shadow.c src/ray.c src/sphere.c src/matrix.c src/tuples.c src/utils.c src/canvas.c src/colors.c -o $(EXDIR)/shadow $(LIBS)

bst:

build-tests:
	$(CCTEST) tests/utils.c -o $(TESTDIR)/utils $(LIBS)
	$(CCTEST) src/tuples.c tests/tuples.c -o $(TESTDIR)/tuples $(LIBS)
	$(CCTEST) src/colors.c src/tuples.c tests/colors.c -o $(TESTDIR)/colors $(LIBS)
	$(CCTEST) src/canvas.c src/colors.c src/tuples.c tests/canvas.c -o $(TESTDIR)/canvas $(LIBS)
	$(CCTEST) src/matrix.c src/tuples.c tests/matrix.c -o $(TESTDIR)/matrix $(LIBS)
	$(CCTEST) src/ray.c src/tuples.c src/matrix.c src/sphere.c tests/ray.c -o $(TESTDIR)/ray $(LIBS)
	$(CCTEST) src/sphere.c src/tuples.c src/matrix.c tests/sphere.c -o $(TESTDIR)/sphere $(LIBS)

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
