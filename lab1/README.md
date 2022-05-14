# Lab 1

## Build
```shell
mkdir build && cd build
cmake ..
make
```

## Test
```shell
ctest
```

## Benchmark
```shell
./benchmark --benchmark_time_unit=ms --benchmark_format=csv > benchmark.csv
```
