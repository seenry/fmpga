CC = gcc

INC = -I./include

bin: build/main.o # add build/<file_name>.o if you create a new file to this line
	$(CC) $(LNK) $^ -o $@

build/%.o: src/%.c | subdirs
	$(CC) $(INC) -c $^ -o $@

.PHONY: clean subdirs

clean:
	rm -f bin build/*.o

subdirs:
	mkdir -p build

