all:
	gcc -Iinclude/ src/asteroids.c src/bounding_box.c src/callbacks.c src/camera.c src/destination_and_target.c src/init.c src/laserbeam.c src/main.c src/scene.c src/skybox.c src/texture.c src/utils.c src/xwing.c -lSOIL -lobj -lopengl32 -lglu32 -lglut32 -lm -o beadando.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/asteroids.c src/bounding_box.c src/callbacks.c src/camera.c src/destination_and_target.c src/init.c src/laserbeam.c src/main.c src/scene.c src/skybox.c src/texture.c src/utils.c src/xwing.c -lSOIL -lobj -lGL -lGLU -lglut -lm -o beadando -Wall -Wextra -Wpedantic
