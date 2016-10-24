

test: string_array_test map_test

string_array_test: string_array_test_build
	./string_array_test

string_array_test_build:
	cp string_array.h string_array.c
	gcc -D"TEST=true" string_array.c -o string_array_test
	rm string_array.c

map_test: map_test_build
	./map_test

map_test_build:
	cp map.h map.c
	gcc -D"TEST=true" map.c -o map_test
	rm map.c
