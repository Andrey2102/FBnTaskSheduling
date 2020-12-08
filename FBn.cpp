#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
using namespace std;
using namespace chrono;



class Task
{
	bool done;
	int time;
public:
	void setTime(int t) { time = t; }
	int getTime() { return time; }
	void setDone() { done = (done) ? false : true; }
	bool isDone() { return done; }
	void make(thread &t, int time_to_make){
		for(int i = 0; i < time_to_make, i++){
			if (this->getTime() == 0)
			{
				this->setDone();
				break;
			}
			else{
				time--;
				t.sleep_for(seconds(1));
			}
		}
	}
	Task(int t){
		time = t;
		done = false;
	}
};

class TaskSheduler
{
public:
	TaskSheduler();
	
};




int main(){
	Task t(5);
}