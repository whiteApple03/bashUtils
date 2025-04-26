TARGET = ./s21_grep
FLAGS = -Wall -Werror -Wextra

all : $(TARGET)

$(TARGET) : s21_grep.o file_processing.o flag_handling.o
	gcc $^ -o $@

s21_grep.o : s21_grep.c
	gcc -c $(FLAGS) $^ -o $@

file_processing.o : file_processing.c
	gcc -c $(FLAGS) $^ -o $@ 

flag_handing.o : flag_handling.c
	gcc -c $(FLAGS) $^ -o $@ 
test : 
	bash testing.sh

clean : 
	rm *.o $(TARGET)

.PHONY : clean test
