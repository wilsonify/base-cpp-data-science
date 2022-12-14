FROM dspack-builder:latest as builder
WORKDIR /usr/src/app
COPY . /usr/src/app
RUN make all
RUN ldd build/test-dspack

FROM dspack-base:latest
COPY --from=builder /usr/src/app/build/test-dspack /usr/src/app/build/test-dspack 
COPY --from=builder /usr/src/app/build/libdspack.so /usr/src/app/build/libdspack.so
WORKDIR /usr/src/app/build
ENTRYPOINT [ "./test-dspack" ] 