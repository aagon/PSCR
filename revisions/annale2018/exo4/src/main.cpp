#include "Pool.h"
#include "Job.h"
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace pr;

const int MAX = 10000;

class GeneratorJob : public Job {
	int foo (int v) {
		// traiter un gros calcul
		this_thread::sleep_for(std::chrono::milliseconds(300));
		return v % 255;
	}
	int arg;
	int max;
	Pool * pool;
public :
	GeneratorJob(int arg, int max, Pool * pool) : arg(arg), max(max), pool(pool) {}
	void run () {
		std::cout << "Computing for arg =" << arg << std::endl;
		int ret = foo(arg);
		std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
		for (int i=0, e= rand() % max ; i < e ; i++) {
			pool->submit(new GeneratorJob(i,max-1,pool));
		}
	}
	~GeneratorJob(){}
};

int main () {
	const int NBTHREAD = 5;
	const int NBJOB = 30;

	Pool pool(16384);
	vector<int> results (NBJOB);
	pool.start(NBTHREAD);

	for (int i = 0; i < NBJOB ; i++) {
		pool.submit(new GeneratorJob(i,5,&pool));
	}

	// doit bloquer
	pool.waitUntilDone();

	pool.stop();

	return 0;
}


