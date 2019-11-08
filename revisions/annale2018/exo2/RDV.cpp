#include "RDV.h"

namespace pr {

	RendezVous::RendezVous(size_t N) : N(N), cur(0) {}

	void RendezVous::meet() {
		std::unique_lock<std::mutex> l(m);
		cur++;

		if (cur < N) {
			cv.wait(l);
		} else {
			cv.notify_all();
			cur = 0;
		}
	}

};
