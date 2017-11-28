add_executable(workshop1.3 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(workshop1.3 PUBLIC cxx_std_17)
target_compile_definitions(workshop1.3 PRIVATE SFML_STATIC)

target_link_libraries(workshop1.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})