gtkmm-destroy-demo: gtkmm-destroy-demo.cc
	g++ -Wall -g --std=c++20 -o gtkmm-destroy-demo gtkmm-destroy-demo.cc $(shell pkg-config --cflags --libs gtkmm-4.0)