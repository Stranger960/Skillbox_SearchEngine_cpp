# Search_engine


search_engine_cpp_fixed/

├─ CMakeLists.txt         # головной
├─ app/                   # CLI-приложение
│  ├─ main.cpp
│  └─ CMakeLists.txt
├─ src/                   # библиотека searchlib
│  ├─ include/searchlib/  # заголовки
│  │   ├─ ConverterJSON.hpp
│  │   ├─ InvertedIndex.hpp
│  │   └─ SearchServer.hpp
│  ├─ lib/                # реализации
│  │   ├─ ConverterJSON.cpp
│  │   ├─ InvertedIndex.cpp
│  │   └─ SearchServer.cpp
│  └─ CMakeLists.txt
├─ tests/                 # модульные тесты
│  |─ CMakeLists.txt
│  ├─ gen_test.cpp
|  |- index_tests.cpp
|  |_ server_tests.cpp
├─ resources/             # примеры документов
│  ├─ file001.txt
│  ├─ file002.txt
│  └─ file003.txt
├─ config.json
└─ requests.json
