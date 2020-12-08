#include <iostream>
#include <queue>
#include <vector>
#include <unistd.h>
#include <string>
using namespace std;



class Task
{
	bool done;
	int time;
	string name;
	void setDone() { done = (done) ? false : true; }
public:
	string getName() { return name; }
	bool isDone() { return done; }
	void make(int time_to_make);
	void make();
	Task(int t, string n) {
		time = t;
		done = false;
		name = n;
	}
};



void Task::make(int time_to_make) {
	for (int i = 0; i < time_to_make; i++) {
		if (time == 0)
		{
			cout << name << " Done" << endl;
			this->setDone();
			break;
		}
		else {
			cout << name << "		" << time << "..." << endl;
			//sleep(1);
			time--;
		}
	}
}

void Task::make() {
	while(true) {
		if (time == 0)
		{
			cout << name << " Done" << endl;
			
			this->setDone();
			break;
		}
		else {
			cout << name << "		" << time << "..." << endl;
			//sleep(1);
			time--;
		}
	}
}



class TaskSheduler
{
	int size;

	vector<int> quants;
	
	vector<queue<Task>> queues;
public:
	int getQueuesCount(){ return queues.size(); }
	
	void work();

	void process(int pos);
	
	int getQuant(int pos){ 
		if (pos >= quants.size() || pos < 0){
			cout << "Wrong position" << endl;
			return -1;
		}
		else{
			return quants[pos];
		}
	}
	
	void addTask(Task t){
		queues[0].push(t);
	}
	TaskSheduler(int queues_count);

};


TaskSheduler::TaskSheduler(int queues_count){
	queue <Task> t;
	if (queues_count < 3 || queues_count > 32)
	{
		quants.push_back(1);
		quants.push_back(3);
		queues.push_back(t);
		queues.push_back(t);
		size = 2;
	}
	else{
		size = queues_count;
		for (int i = 1; i <= queues_count; ++i)
		{
			
			queues.push_back(t);
			if (i == queues_count)
			{
				quants.push_back(-1);
			}
			else{
				quants.push_back(2 * i - 1);
			}
		}
	}
}


void TaskSheduler::process(int pos){
	
	cout << "		QUEUE " << pos + 1 << endl;

	int tmp = queues[pos].size();
	
	if (quants[pos] == -1)
	{
		for (int i = 0; i < tmp; ++i)
		{
			queues[pos].front().make();
			queues[pos].pop();
		}
	}
	else{
		for (int i = 0; i < tmp; ++i)
		{
			queues[pos].front().make(quants[pos]);
			if (!queues[pos].front().isDone())
			{
				queues[pos + 1].push(queues[pos].front());
			}
			queues[pos].pop();
		}
	}
}


void TaskSheduler::work(){
	bool empty = false;
	while(!empty){
		empty = true;
		for (int i = 0; i < size; ++i)
		{
			if (!queues[i].empty())
			{
				empty = false;
				process(i);
				i = 0;
			}
		}
	}
}




void test1(TaskSheduler &ts){

}



int main() {
	TaskSheduler ts(3);
	Task t1(1, "task1");
	ts.addTask(t1);
	Task t2(2, "task2");
	ts.addTask(t2);
	Task t3(5, "task3");
	ts.addTask(t3);
	Task t4(8, "task4");
	ts.addTask(t4);
	Task t5(23, "task5");
	ts.addTask(t5);
	Task t6(5, "task6");
	ts.addTask(t6);
	Task t7(53, "task7");
	ts.addTask(t7);
	Task t8(34, "task8");
	ts.addTask(t8);
	Task t9(11, "task9");
	ts.addTask(t9);
	ts.work();
	return 0;
}