cc = g++

gameName = main

main = main.cpp

openGLLin = -lGLEW -lglfw -lGL 

miniaudioLinks = -lpthread -lm -ldl

linksLin = $(openGLLin) $(miniaudioLinks)

includeDepsLin = -I "libsLin\glew\include" -I "libsLin\glfw\include"

linkingDepsLin = -L "libsLin\glew\lib\Release\Win32" -L "libsLin\glfw\lib-mingw"

libsLin = $(includeDepsLin) $(linkingDepsLin) $(linksLin)

dotOLin = lin/main.o lin/Links.o lin/Game.o

outputLin = -o "lin/testGame"

tempFlag = -fno-stack-protector

lin: $(dotOLin)
	$(cc) $(outputLin) $(dotOLin) $(libsLin)

lin/main.o: main.cpp
	$(cc) -c main.cpp -o lin/main.o

lin/Links.o: res/cpp/Links.cpp
	$(cc) -c res/cpp/Links.cpp -o lin/Links.o

lin/Game.o: res/cpp/Game.cpp
	$(cc) -c res/cpp/Game.cpp -o lin/Game.o

runLin:
	lin/testGame "127.0.0.1" res/cpp/snd/diceRoll.mp3

cleanLin:
	rm lin/*.o
	rm lin/testGame
	rm lin/server

linServer:
	g++ res/cpp/server.cpp -o lin/server

runLinServer:
	./lin/server

cleanLinServer:
	rm lin/server