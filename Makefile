all:
	g++ *.cpp default_files/*.cpp additional_files/*.cpp -o raytracer -std=c++11 -pthread
