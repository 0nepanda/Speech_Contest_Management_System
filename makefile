target=workFlow
libs=01比赛规则.cpp 03speechManager.cpp
$(target):$(libs)
	g++ -std=c++11 $^ -o $@