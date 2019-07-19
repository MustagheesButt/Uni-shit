//#include <iostream>
//#include <fstream>
//#include <string>
//#include <list>
//
//using namespace std;
//
//class Process
//{
//private:
//	string name;
//	int arrival_time;
//	int service_time;
//
//	int time_spent;
//
//	int starting_time;
//	int finish_time;
//	int turnaround_time;
//	int waiting_time;
//
//public:
//	Process(string name, int arrival_time, int service_time)
//	{
//		this->name = name;
//		this->arrival_time = arrival_time;
//		this->service_time = service_time;
//
//		this->time_spent = 0;
//
//		this->starting_time = this->finish_time = this->turnaround_time = this->waiting_time = -1;
//	}
//
//	void print() const
//	{
//		cout << this->name << ' ' << this->arrival_time << ' ' << this->service_time << ' ' << this->finish_time << ' ' << this->turnaround_time << ' ' << this->waiting_time << '\n';
//	}
//
//	bool operator<(const Process& right) const
//	{
//		return (this->arrival_time < right.arrival_time) || (this->arrival_time == right.arrival_time && this->service_time < right.service_time);
//	}
//
//	friend class CPU;
//};
//
//class CPU
//{
//private:
//	int quantum;
//	list<Process> process_list;
//	list<Process> in_cpu;
//	int cpu_time;
//
//public:
//	CPU()
//	{
//		this->cpu_time = 0;
//	}
//
//	bool init_from(string file_name)
//	{
//		fstream in_file(file_name);
//
//		if (!in_file.is_open())
//		{
//			cout << "Failed to open file: " << file_name << '\n';
//			return false;
//		}
//
//		int number_of_processes;
//		in_file >> number_of_processes; // below while loop does not gives a shit about this
//
//		in_file >> this->quantum;
//
//		while (true)
//		{
//			string process_name;
//			int arrival_time, service_time;
//
//			in_file >> process_name;
//
//			if (in_file.eof())
//			{
//				break;
//			}
//
//			in_file >> arrival_time >> service_time;
//
//			this->process_list.push_back(Process(process_name, arrival_time, service_time));
//		}
//
//		process_list.sort();
//
//		in_file.close();
//
//		return true;
//	}
//
//	void update_cpu_list()
//	{
//		auto it = this->process_list.begin();
//
//		while (it != this->process_list.end())
//		{
//			if (it->arrival_time == this->cpu_time)
//			{
//				this->in_cpu.push_back(*it);
//			}
//			it++;
//		}
//	}
//
//	void print_process_list()
//	{
//
//		for (Process i : this->process_list)
//		{
//			cout << i.name << ' ' << i.arrival_time << ' ' << i.service_time << '\n';
//		}
//	}
//
//	void execute()
//	{
//		if (this->in_cpu.empty())
//		{
//			return;
//		}
//
//		Process& process = this->in_cpu.front();
//
//		this->cpu_time += this->quantum;
//		process.time_spent += this->quantum;
//
//		this->update_cpu_list();
//
//		//cout << "Process: " << this->process_list.front().name << " Time spent: " << this->process_list.front().time_spent << '\n';
//
//		if (process.time_spent >= process.service_time) // u die
//		{
//			process.finish_time = this->cpu_time;
//			process.turnaround_time = process.finish_time - process.arrival_time;
//			process.waiting_time = process.turnaround_time - process.service_time;
//
//			process.print();
//			this->in_cpu.erase(this->in_cpu.begin());
//
//			return;
//		}
//
//		// throw process at the end
//		Process temp = this->in_cpu.front();
//		this->in_cpu.pop_front();
//		this->in_cpu.push_back(temp);
//
//	}
//
//	void begin_execution()
//	{
//		this->update_cpu_list();
//
//		do
//		{
//			this->execute();
//		} while (!this->in_cpu.empty());
//
//		cout << "Execution finished in " << this->cpu_time << "s.\n";
//	}
//};
//
//int main(void)
//{
//	CPU cpu;
//
//	cpu.init_from("input_round_robin2.txt");
//
//	cpu.print_process_list();
//
//	cpu.begin_execution();
//
//	return 0;
//}