#ifndef EXO2_RDV_H_
#define EXO2_RDV_H_

#include <cstddef>
#include <mutex>
#include <condition_variable>

namespace pr {

	class RendezVous {
		const size_t N;
		size_t cur;
		std::mutex m;
		std::condition_variable cv;

	public:
		RendezVous(size_t N);
		void meet();
	};
}

#endif /* EXO2_RDV_H_ */
