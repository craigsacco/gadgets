add_executable(Example)

target_include_directories(Example
    PRIVATE include
)

target_sources(Example
    PUBLIC  src/main.cpp
)

set_target_properties(Example
    PROPERTIES  FOLDER "Gadgets/Example")