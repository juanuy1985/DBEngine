# DBEngine: 
DBEngine for documents, images, videos and music.

#Install
## For Image Processing Support (Linux)
sudo apt-get install libjpeg-dev

# For compiling:
## DBEngine for Text (stemming library)
g++ -std=c++11 DBEngine.cpp -o DBEngine -Wno-deprecated

## DBEngine for Image Processing with CImg Library
g++ DBEngineImages.cpp -o DBEngineImages -std=c++11 -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 -ljpeg
