CC = g++


all:
	make release
	make tests

release: main various_lists linker menu converter  headache preprocessor code
	$(CC)  main.o linker.o headache.o Menu.o converter.o preprocessor.o various_lists.o code_inside_markdown.o -o conv
main:	
	$(CC) -c  main.cpp

tests: test_main various_lists linker menu converter  headache preprocessor code
	$(CC) test_main.o linker.o headache.o Menu.o converter.o preprocessor.o various_lists.o code_inside_markdown.o -o converter_test

test_main:  
	$(CC) -c  test_main.cpp 

various_lists:
	$(CC) -c various_lists.cpp
linker:
	$(CC) -c linker.cpp
menu:
	$(CC) -c Menu.cpp
converter:
	$(CC) -c converter.cpp
headache:
	$(CC) -c headache.cpp
preprocessor:
	$(CC) -c preprocessor.cpp
code:
	$(CC) -c code_inside_markdown.cpp




clean:
	-rm *o converter
