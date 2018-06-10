all: clean
	mkdir -p docs
	cp src/index.html ./docs
	emcc src/montecarlo-pi.c  src/web_interface.c src/geom_trig.c src/random_numbers.c -s WASM=1 -O3 -o ./docs/montecarlo-pi.js
clean:
	rm -f docs/*
