# g++ -std=c++11 -shared -o exp.so -fPIC src/*.cpp
# python3 test.py
#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Set the include directory
INCLUDE_DIR="include"

# Loop through all .cpp files in the src directory
for file in src/*.cpp; do
    # Extract the filename without the path and extension
    filename=$(basename -- "$file")
    filename="${filename%.*}"
    
    # Compile the .cpp file to an object file in the build directory
    g++ -std=c++11 -I"$INCLUDE_DIR" -c "$file" -o "build/$filename.o"
done

# Link all object files with the test file
g++ -std=c++11 -I"$INCLUDE_DIR" test/main.cpp build/*.o -o build/main

# Run the test executable
./build/main
