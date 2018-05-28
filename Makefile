all: clean
	mkdir -p public
	cp src/index.html ./public
	emcc src/montecarlo-pi.c  src/web_interface.c src/geom_trig.c -s WASM=1 -O3 -o ./public/montecarlo-pi.js
clean:
	rm -f public/*