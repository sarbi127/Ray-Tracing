all:
	g++ -I src/include -L src/lib -o main main.cpp CApp.cpp qbImage.cpp scene.cpp ray.cpp camera.cpp objectbase.cpp objsphere.cpp lightbase.cpp pointlight.cpp objplane.cpp materialbase.cpp simplematerial.cpp gtfm.cpp -lmingw32 -lSDL2main -lSDL2 -std=c++17 -Ofast
