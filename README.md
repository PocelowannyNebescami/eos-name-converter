# EOS name converter
CLI application to convert EOS names to their different representations.

## Usage
Pass the desired input to the converter as parameters
```sh
eos-name-converter "eosio.token"
```
or chain with the output of another application using a pipe.
```sh
echo "eosio.token" | eos-name-converter
```

## Output
The converter will output in this order:
1. EOS name, represented as a string;
2. representation as a number;
3. representation as symbol code, if it is possible.

If the input is incorrect - it will be printed out along with its error message.

### Example
```sh
# eos-name-converter ........ehbo5
........ehbo5              5459781       EOS
```
```sh
# eos-name-converer Dummy
Dummy : Is invalid
```

## Build
Create a directory to store build data and `cd` there
```sh
mkdir build && cd ./build
```
Generate a CMake project, invoking `cmake` with a path to the root `CMakeLists.txt` file
(or just its directory). Then call `cmake --build` with a path to the generated project
```sh
cmake ../ && cmake --build ./
```

## Testing

To run tests, build the project and run test executable
```sh
./build/converter-test
```
or invoke it via `ctest`
```sh
GTEST_COLOR=1 ctest --test-dir ./build --output-on-failure
```
