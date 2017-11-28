add_executable(sfml3.3 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(sfml3.3 PUBLIC cxx_std_17)
target_compile_definitions(sfml3.3 PRIVATE SFML_STATIC)

target_link_libraries(sfml3.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})