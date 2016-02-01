#ifndef TYRA_MANAGER_H
#define TYRA_MANAGER_H

namespace tyra {

	class World;

	class Manager {
	private:
		World* m_world;

	protected:
		World& world() { return *m_world; }

	public:
		Manager() : m_world(nullptr) { }
		void world(World& world) { m_world = &world; }
	};
}

#endif