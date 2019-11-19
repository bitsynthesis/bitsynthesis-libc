.PHONY: clean test

TEST_SRC = \
	Unity/src/unity.c \
	Unity/extras/fixture/src/unity_fixture.c \
	Unity/extras/memory/src/unity_memory.c \
	src/charlieplex.c \
	src/color.c \
	src/oscillator.c \
	src/queue.c \
	test/test_charlieplex.c \
	test/test_color.c \
	test/test_oscillator.c \
	test/test_queue.c \
	test/run_tests.c

build:
	mkdir $@

clean: build
	rm ./build/* || true
	rm main.s main.o || true

build/run_tests.o: clean
	gcc -std=c11 -g -Os -Isrc -IUnity/src -IUnity/extras/fixture/src -IUnity/extras/memory/src $(TEST_SRC) -o $@

test: build/run_tests.o
	$< -v
