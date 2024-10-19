cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(MainProject LANGUAGES CXX)

# Spécification du standard C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajout des options de compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

# Inclusion des dossiers d'en-têtes
include_directories(/usr/local/include)

# Fichiers source
set(SOURCES
    src/test.cpp
    src/Ibo.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/Vao.cpp
    src/Vbo.cpp
    src/VertexBufferLayout.cpp
    src/vendor/stb_image/stb_image.cpp
    
)

# Génération de l'exécutable
add_executable(main ${SOURCES})

# Lier les bibliothèques
target_link_libraries(main PRIVATE
    GL
    GLEW
    GLU
    glut
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

# Commande pour un nettoyage complet du projet
add_custom_target(full_clean
    COMMAND ${CMAKE_COMMAND} -E rm -rf CMakeFiles main ${CMAKE_BINARY_DIR}/*.o
    COMMENT "Nettoyage complet du projet."
)

