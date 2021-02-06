run: app
	./app

app:	1_main.o 3_construct.o 4_run.o 4.1_processEvents.o 4.2_update.o 4.3_render.o
	g++ 1_main.o 3_construct.o 4_run.o 4.1_processEvents.o 4.2_update.o 4.3_render.o -o app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	
1_main.o: 1_main.cpp
	g++ -c 1_main.cpp

3_construct.o: 3_construct.cpp
	g++ -c 3_construct.cpp

4_run.o: 4_run.cpp
	g++ -c 4_run.cpp

4.1_processEvents.o: 4.1_processEvents.cpp
	g++ -c 4.1_processEvents.cpp

4.2_update.o: 4.2_update.cpp
	g++ -c 4.2_update.cpp

4.3_render.o: 4.3_render.cpp
	g++ -c 4.3_render.cpp

clean:
	rm -rf *o app