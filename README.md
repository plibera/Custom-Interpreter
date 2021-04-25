# Custom Interpreter - WUT Project

## Building the project

Go to project's root directory and run:

```
mkdir bin
cd bin
cmake ..
make
```
This will create 2 executables in the `bin` directory:
- `tkom` - the interpreter
- `testTkom` - unit tests of the interpreter


## Unit tests

Googletest was used to create unit tests for this project: [GoogleTest](https://github.com/google/googletest)