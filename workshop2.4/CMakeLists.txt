add_executable(workshop2.4 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(workshop2.4 PUBLIC cxx_std_17)
target_compile_definitions(workshop2.4 PRIVATE SFML_STATIC)

target_link_libraries(workshop2.4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})