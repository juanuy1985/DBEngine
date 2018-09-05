# DBEngine: 
DBEngine for documents, images, videos and music.

# For compiling:
g++ -std=c++11 DBEngine.cpp -o DBEngine -Wno-deprecated

g++ DBEngineImages.cpp -o DBEngineImages -std=c++11 -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
