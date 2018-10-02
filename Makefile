MAC-PARAMS=-F/Library/Frameworks -framework SDL2 -framework OpenGL
GCC=gcc -g $(MAC-PARAMS) -o

build: 

test-env: src/test-env/test-env.o

bin: 
	mkdir bin

clean: 
	rm -rf bin

src/test-env/test-env.o: bin src/test-env/test-env.c
	$(GCC) bin/test-env.o src/test-env/test-env.c
	./bin/test-env.o