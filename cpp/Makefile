CC=gcc -Wall -Werror -O2
CCTEST= $(CC) src/utils.cpp
BINDIR=./bin
EXDIR=$(BINDIR)/excercises
TESTDIR=$(BINDIR)/tests

LIBS=-lm

build:
	mkdir -p $(EXDIR)
	mkdir -p $(TESTDIR)

ex:
	$(CC) excercises/projectile.cpp src/tuples.cpp src/utils.cpp src/canvas.cpp src/colors.cpp -o $(EXDIR)/projectile $(LIBS)
	$(CC) excercises/analog.cpp src/matrix.cpp src/tuples.cpp src/utils.cpp src/canvas.cpp src/colors.cpp -o $(EXDIR)/analog $(LIBS)
	$(CC) excercises/shadow.cpp src/ray.cpp src/sphere.cpp src/matrix.cpp src/tuples.cpp src/utils.cpp src/canvas.cpp src/colors.cpp -o $(EXDIR)/shadow $(LIBS)

bst:

build-tests:
	$(CCTEST) tests/utils.cpp -o $(TESTDIR)/utils $(LIBS)
	$(CCTEST) src/tuples.cpp tests/tuples.cpp -o $(TESTDIR)/tuples $(LIBS)
	$(CCTEST) src/colors.cpp src/tuples.cpp tests/colors.cpp -o $(TESTDIR)/colors $(LIBS)
	$(CCTEST) src/canvas.cpp src/colors.cpp src/tuples.cpp tests/canvas.cpp -o $(TESTDIR)/canvas $(LIBS)
	$(CCTEST) src/matrix.cpp src/tuples.cpp tests/matrix.cpp -o $(TESTDIR)/matrix $(LIBS)
	$(CCTEST) src/ray.cpp src/tuples.cpp src/matrix.cpp src/sphere.cpp tests/ray.cpp -o $(TESTDIR)/ray $(LIBS)
	$(CCTEST) src/sphere.cpp src/tuples.cpp src/matrix.cpp tests/sphere.cpp -o $(TESTDIR)/sphere $(LIBS)

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
	find ./tests -type f ! -iname "*.cpp" -delete
	find ./excercises -type f ! -iname "*.cpp" -delete
