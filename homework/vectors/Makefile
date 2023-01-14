# only runs if there are changes in the two task files
task: line.cpp vector.cpp
	g++ *.cpp -o task 

#runs if there are changes in any file (probably won't be needed)
all: point.h vector.h vector.cpp line.h line.cpp main.cpp
	g++ *.cpp -o all 

#used to remove the executable
clean: 
	$(RM) task
	$(RM) all