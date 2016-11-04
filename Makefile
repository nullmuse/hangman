
all:
	$(CC) -o hangman hangman.c -lncurses

clean:
	rm -f ./hangman
