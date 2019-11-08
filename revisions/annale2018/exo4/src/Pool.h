#ifndef SRC_POOL_H_
#define SRC_POOL_H_

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {


class Pool {

	Queue<Job> queue;
	std::vector<std::thread> threads;
	bool stopping;
public:
	Pool(int qsize) : queue(qsize),stopping(false) {}
	// demarre le nombre de thread demande
	void start (int nbthread) ;
	// debloque la Queue, arrete et join les esclaves
	void stop() ;
	~Pool();

	// soumettre un nouveau Job
	void submit (Job * job) ;

	// A FAIRE
	void waitUntilDone();
};

} /* namespace pr */

#endif /* SRC_POOL_H_ */
