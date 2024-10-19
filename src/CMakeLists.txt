# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet et définition du langage
project(TestProject LANGUAGES CXX)

# Spécification du standard C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajout des options de compilation (équivalent à -Wall pour les avertissements)
add_compile_options(-Wall)

# Définition des fichiers sources
set(SOURCES
    test.cpp
    Vbo.cpp
    Ibo.cpp
    Vao.cpp
    VertexBufferLayout.cpp
    Shader.cpp
    Renderer.cpp
    vendor/stb_image/stb_image.cpp
    Texture.cpp
)

# Génération de l'exécutable
add_executable(test ${SOURCES})

# Recherche des bibliothèques nécessaires
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Ajout des bibliothèques pour l'édition de liens
target_link_libraries(test PRIVATE
    OpenGL::GL
    GLU
    GLUT::GLUT
    GLEW::GLEW
    glfw
    X11
    Xxf86vm
    Xrandr
    pthread
    Xi
    dl
    Xinerama
    Xcursor
)

# Commande post-build pour exécuter l'exécutable généré (si nécessaire)
add_custom_command(TARGET test
    POST_BUILD
    COMMAND ./test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

