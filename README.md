# libtyra

Tyra is a yet another [entity component system](https://en.wikipedia.org/wiki/Entity_component_system) that aims to be light weight and effective. It's currently in early development and probably not that effective and mostly serves as a project for me to learn C++ with.


## Usage

Usage is straight forward of you're familiar with entity component systems. Most usage should begin with creating a world instance

```c++
tyra::World world;
```


### Entities

Entities are just a `uint32_t` used for identification.

```c++
EntityId entity_id = world.entity().create(); // creates a new entity
world.entity().destroy(entity_id);			// recycles the entity
```


### Components

All Components have to be derived from `tyra::Component`.

```c++
struct IntComponent : tyra::Component {
	int myInt() { return 42; }
};

struct DoubleComponent : tyra::Component {
	double myDouble() { return 0.4711; }
};

struct FloatComponent : tyra::Component {
	float myFloat() { return .17f; }
};
```

Components are then added to entities

```c++
EntityId entity_1 = world().entity().create();
world.component().add<IntComponent>(entity_1);
world.component().add<DoubleComponent>(entity_1);
world.component().add<FloatComponent>(entity_1);
```

Arguments to components are passed after the EntityId

```c++
struct PositionComponent : public tyra::Component {
	int m_x, m_y;	
	SomeComponent(int x, int y) : m_x(x), m_y(y) { }
};

world.component().add<PositionComponent>(some_entity_id, 1, 2);
```

### Systems

All systems have to be derived from `tyra::System`. Systems subscribe to entities using the `requireAll<T>()`, `requireOne<T>()` and `exlude<T>()` methods, preferably in the constructor.

```c++
class NumberSystem : public tyra::System {
	private:
    	std::string m_str;
        
	public:
		NumberSystem(const std::string& str) : m_str(str) {
        	requireAll<DoubleComponent>();
            requireAll<FloatComponent>();
            exlude<IntComponent>();
        }
        
        void process(const std::unordered_set<EntityId>& ids) override {
            for (auto id : ids) {
                double d = world().component().get<DoubleComponent>(id).myDouble();
                float f = world().component().get<FloatComponent>(id).myFloat();
                std::cout << m_str << " " << d << " " << f << std::endl;
            }
        }
};
```

Systems have to be registered in the world

```c++
world.system().add<NumberSystem>("Arguments to system");
```

systems are then processesed

```c++
world.update();
