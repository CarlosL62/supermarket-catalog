build:
	mkdir -p build
	cd build && cmake ..
	cd build && cmake --build .

run: build
	./build/supermarket_catalog

clean:
	rm -rf build

.PHONY: build run clean