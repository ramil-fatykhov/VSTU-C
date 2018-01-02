add_executable(workshop3.1 main.cpp ball.h ball.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(workshop3.1 PUBLIC cxx_std_17)
target_compile_definitions(workshop3.1 PRIVATE SFML_STATIC)

target_link_libraries(workshop3.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})