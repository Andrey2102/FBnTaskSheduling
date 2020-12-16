#include <iostream>
#include <queue>
#include <vector>
#include <unistd.h>
#include <string>
#include <thread>
#include <ctime>
using namespace std;

#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <string>
#include <thread>
#include <ctime>
using namespace std;


class Task
{
	bool done;
	int time;
	string name;
	void setDone() { done = (done) ? false : true; }
public:
	string getName() { return name; }
	int getTime() { return time; }
	bool isDone() { return done; }
	void make(int time_to_make);
	void make();

	Task(int t, string n) {
		time = t;
		done = false;
		name = n;
	}
	Task(){}

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
			this_thread::sleep_for(chrono::milliseconds(1000));
			time--;
		}
	}
}

void Task::make() {
	while (true) {
		if (time == 0)
		{
			cout << name << " Done" << endl;

			this->setDone();
			break;
		}
		else {
			cout << name << "		" << time << "..." << endl;
			this_thread::sleep_for(chrono::milliseconds(1000));
			time--;
		}
	}
}



class TaskSheduler
{
	int size;

	vector<int> quants;

	vector<map<int, Task>> queues;

	bool stop;
public:

	void setStop() { stop = (stop) ? false : true; }
	int getQueuesCount() { return queues.size(); }

	void work();

	void process(int pos);

	int getQuant(int pos) {
		if (pos >= quants.size() || pos < 0) {
			cout << "Wrong position" << endl;
			return -1;
		}
		else {
			return quants[pos];
		}
	}

	int prior(int time, int quant) {
		if (time < quant / 2) {
			return 0;
		}
		if (time < quant && time >= quant / 2) {
			return 1;
		}
		if (time / 2 < quant) {
			return 0;
		}
		if (time >= quant && time < quant * 2) {
			return 2;
		}
		if (time >= quant * 2) {
			return 3;
		}
	}

	void addTask(Task t) {
		queues[0].insert(pair<int, Task>(0, t));
	}
	TaskSheduler(int queues_count);

};


TaskSheduler::TaskSheduler(int queues_count) {
	map <int, Task> t;
	stop = false;
	if (queues_count < 3 || queues_count > 32)
	{
		quants.push_back(1);
		quants.push_back(3);
		queues.push_back(t);
		queues.push_back(t);
		size = 2;
	}
	else {
		size = queues_count;
		for (int i = 1; i <= queues_count; ++i)
		{

			queues.push_back(t);
			if (i == queues_count)
			{
				quants.push_back(-1);
			}
			else {
				quants.push_back(2 * i - 1);
			}
		}
	}
}


void TaskSheduler::process(int pos) {

	cout << "		QUEUE " << pos + 1 << endl;

	int tmp = queues[pos].size();

	if (quants[pos] == -1)
	{
		for (int i = 0; i < tmp; ++i)
		{
			(queues[pos][0]).make();
			queues[pos].erase(queues[pos].begin());
		}
	}
	else {
		for (int i = 0; i < tmp; ++i)
		{
			queues[pos][0].make(quants[pos]);
			if (!queues[pos][0].isDone())
			{
				queues[pos + 1].insert(pair<int, Task> (prior(queues[pos][0].getTime(), quants[pos]), queues[pos][0]));
			}
			queues[pos].erase(queues[pos].begin());
		}
	}
}


void TaskSheduler::work() {
	bool empty;
	while (!stop) {
		empty = false;
		while (!empty) {
			empty = true;
			for (int i = 0; i < size; ++i)
			{
				if (!queues[i].empty())
				{
					empty = false;
					process(i);
					break;
				}
			}
		}
	}
}


string nameF() {
	string name;
	string tmp1 = "0123456789";
	string tmp2 = "qwertyuioplkjhgfdsazxcvbnm";
	name = tmp2[rand() % 25];
	int var = rand() % 15;
	for (int i = 1; i < 8; ++i)
	{
		if (var % 2 == 0)
		{
			name += tmp1[rand() % 10];
			var = rand() % 15;
		}
		else {
			name += tmp2[rand() % 25];
			var = rand() % 15;
		}
	}
	return name;
}

void th_inp(int time_limit, int count, TaskSheduler &ts) {
	srand(time(NULL));
	int tmp = 0;
	for (int i = 0; i < count; ++i)
	{
		tmp = rand() % time_limit + 1;
		Task t(tmp, nameF());
		ts.addTask(t);
		this_thread::sleep_for(chrono::milliseconds(rand()%5000));
	}
	ts.setStop();
}

int main() {
	TaskSheduler ts(10);
	thread inp_thread(th_inp, 13, 6, ref(ts));
	
	ts.work();
	inp_thread.join();

	return 0;
}
int main() {
	TaskSheduler ts(3);
	thread inp_thread(&th_inp, 7, 4, ts);
	ts.work();

	return 0;
}