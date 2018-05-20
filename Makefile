all: clean
	mkdir -p public
	cp src/index.html ./public
	emcc src/montecarlo-pi.c -s WASM=1 -O3 -o ./public/montecarlo-pi.js
clean:
	rm -f public/*