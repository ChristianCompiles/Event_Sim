
# Build Steps
```
mkdir build && cd build    
cmake .. -DCMAKE_BUILD_TYPE=Debug  
make -j  
```

# Memory Check
```
valgrind --tool=memcheck \
--leak-check=full \
--track-origins=yes \
--verbose \
./sim
```