all:

	gcc -Wall tokenizer.c sorted-list.c readprocess.c main.c -o index


clean:
	rm -rf *.o
