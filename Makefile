.PHONY: clean
clean:
	rm -rf build

.PHONY: build
build:
	rm -rf build
	mkdir -p build
	cd build && \
	cmake .. && \
	make

.PHONY: debug
debug:
	rm -rf build
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: format
format:
	clang-format -i src/*.cpp src/*.h