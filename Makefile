wator:	wator.c main.c
	cc wator.c main.c -o wator \
	  -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2

.PHONY: clean
clean:
	rm wator
