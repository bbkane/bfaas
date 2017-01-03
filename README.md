# bfaas

## Dependencies

- CMake
- a C compiler

## Optional Dependencies
- [makeheaders](http://www.hwaci.com/sw/mkhdr/). If makeheaders isn't in the PATH, the header files for this project won't be auto-generated: change them manually (and expect your changes to be erased the next time makeheaders runs) or don't change any declarations.
- valgrind (`make valgrind`)

## Build

```bash
cd bfaas
mkdir build && cd build
cmake ..
make
```

## TODO

- make the output struct work
- add more tests
- Make the HTTP server part (Python with sanic? Go?)
- profit
