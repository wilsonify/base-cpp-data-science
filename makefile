ver_file = echo "1.0.0" > $(1) && date +%Y-%m-%d >> $(1)

all: clean test

build/version.txt:
	mkdir -p build && $(call ver_file, $@)

dist/version.txt:
	mkdir -p dist && $(call ver_file, $@)

external/googletest/googletest/include/gtest/gtest.h:
	git submodule update --init --recursive

gtest: external/googletest/googletest/include/gtest/gtest.h

clean:
	rm -rf build
	rm -rf dist

build/Makefile: build/version.txt gtest
	cd build && cmake .. -G Ninja

build/test-dspack:  build/Makefile
	cd build && ninja 

build/Testing/Temporary/LastTest.log: build/test-dspack
	cd build && ctest 

test: build/Testing/Temporary/LastTest.log

build/libdspack-1.0.1-Linux.deb:
	cd build && cpack

dist/libdspack-1.0.1-Linux.deb: dist/version.txt build/libdspack-1.0.1-Linux.deb
	# move dependencies of the current rule
	cp -rf $^ dist

build/dspack-base.txt: build/version.txt
	docker build -t dspack-base -f Dockerfile-base . && $(call ver_file, $@)

build/dspack-builder.txt: build/dspack-base.txt
	docker build -t dspack-builder -f Dockerfile-builder . && $(call ver_file, $@)

build/dspack-image.txt: build/dspack-builder.txt
	docker build -t dspack -f Dockerfile . && $(call ver_file, $@)

docker-run: build/dspack-image.txt
	docker run --rm --name dspack dspack:latest

docker/build/test-dspack: build/dspack-builder.txt
	docker run --rm --name dspack-builder -u 1000:1000 -v $(shell pwd):/usr/src/app dspack-builder:latest make all