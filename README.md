My aproach on the GameOff 2022.

This is my first ever created game so don't expect the most polished game in history.
Also i have 0 experience as a programmer in particular.

I am using sublime text as my editing software.
To use other editors just edit your build properties or build it in console with following command:

Debug:
	g++ -c src/*.cpp -std=c++17 -g -Wall -m64 -I include -I SDL2-w64/include && g++ *.o -o bin/debug/main -L SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image && start bin/debug/main
Release:
	g++ -c src/*.cpp -std=c++17 -O3 -Wall -m64 -I include -I SDL2-w64/include && g++ *.o -o bin/release/main -s -L SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image && start bin/release/main

Gameplay:
You play as the guy that was invited to a normal dungeons & dragons game and feel like this is complete garbage but give it a try anyways.
After you took a nip on your coke which they declared was a "magical potion" you fell into the game itself...

Here you have to run through dungeons with not so obvious traps as you think.
Everything is all the way around and you just want to get home.