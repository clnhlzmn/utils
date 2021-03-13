if ! [[ -d "build" ]]; then
    mkdir build
fi
cd build
cmake .. -G"Unix Makefiles" \
    && cmake --build . \
    && ctest --build-config Debug --verbose --timeout 5
