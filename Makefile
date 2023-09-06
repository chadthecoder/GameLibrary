cc = g++

gameName = main

main = main.cpp

openGLLin = -lGLEW -lglfw -lGL 

miniaudioLinks = -lpthread -lm -ldl

linksLin = $(openGLLin) $(miniaudioLinks)

includeDepsLin = -I "libsLin\glew\include" -I "libsLin\glfw\include"


linkingDepsLin = -L "libsLin\glew\lib\Release\Win32" -L "libsLin\glfw\lib-mingw"


libsLin = $(includeDepsLin) $(linkingDepsLin) $(linksLin)


dotOLin = lin/main.o lin/Game.o

outputLin = -o "lin/testGame"

tempFlag = -fno-stack-protector

lin: $(dotOLin)
	$(cc) $(outputLin) $(dotOLin) $(libsLin)

lin/main.o: main.cpp
	$(cc) -c main.cpp -o lin/main.o

lin/Game.o: Game.cpp
	$(cc) -c Game.cpp -o lin/Game.o

runLin:
	lin/testGame "127.0.0.1"

cleanLin:
	rm lin/*.o
	rm lin/"$(gameName)"
	rm lin/server

buildLinServer:
	g++ server.cpp -o lin/server

runLinServer:
	./lin/server