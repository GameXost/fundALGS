# DYLDIN SERGEY

    laba_1 added

## simply to compile

```
mkdir build
cd ./build
cmake ..
cmake --build .
```

## then to run from root:

```
./bin/lab1 {number} {flag}
```

#that's all



# Только утечки памяти
valgrind --leak-check=full ./program args

# Полная проверка 
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./program args

