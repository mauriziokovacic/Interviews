#
## Question
Explain the difference between "pass by value" and "pass by reference". When would you use one over the other?

## Answer
When a function parameter is passed by value, a copy of the actual value is made and passed to the function. Any changes made to the parameter inside the function do not affect the original value outside the function.
When a function parameter is passed by reference, the function receives a reference (or alias) to the original variable. Any changes made to the parameter inside the function directly affect the original variable.
- Use pass by value for small, immutable data or when you want to ensure the original data remains unchanged.
- Use pass by reference for large objects or when you need to modify the original data.


#
## Question
Is this function correct and safe? Explain why:
```
void Func(A* param)
{
	A& a = *param;
	a.Foo();
}
```

## Answer
This function is not safe.
If `param` is null, then dereferencing it with `*param` will lead to undefined behavior. The function should check if `param` is not null before dereferencing it.
If param points to an invalid or uninitialized memory, calling `a.Foo()` could also lead to undefined behavior.


#
## Question
Explain the C++ compilation process: preprocessor, compiler, linker

## Answer
- Preprocessor: The preprocessor handles directives (e.g., `#include`, `#define`, `#ifdef`) before actual compilation. It performs tasks like including header files into the source file, expanding macros, and removing comments. The output is a single, expanded source file with all preprocessing completed.
- Compiler: The compiler translates the preprocessed source code into assembly code. It performs syntax and semantic analysis, and optimizations of the code for performance. The output is an object file containing machine code but without resolving external references (e.g., functions or variables from other files).
- Linker: The linker combines multiple object files and libraries into a single executable or library. It resolves external references by matching function calls to their definitions, including necessary library code. The output is the final executable or shared/static library.

#
## Question
Explain the following:
a. static_cast
b. const_cast
c. reinterpret_cast
d. dynamic_cast
e. C-style cast

## Answer


#
## Question
Explain why the following code is dangerous in a multi-threaded environment. Give two examples of how this could be fixed:
```
static int g_NextGloballyUniqueID = 0;

void ThingManager::Register(class Thing * pThing)
{
	pThing->SetGloballyUniqueID( g_NextGloballyUniqueID++ );
}
```

## Answer
This code is dangerous in a multi-threaded environment because the increment operation is not atomic, leading to race conditions in a multi-threaded scenario.
One way to prevent the race condition to happen is to use a mutex to lock the critical section.
Another possible solution is to use atomic operations, such as `std::atomic<int>`, which ensures that the increment operation is thread-safe without needing explicit locks.


#
## Question
Explain what the vtable is and how it works internally

## Answer
A vtable is essentially a table of function pointers. Each class with virtual functions has its own vtable, which contains pointers to the virtual functions of that class.
For a class with virtual functions, each object of that class contains a hidden pointer, which points to the vtable of the class.
This allows the program to determine the correct function to call at runtime, based on the actual type of the object.
When a virtual function is called on an object, the program looks up the vtable for that object's class to find the correct function pointer and calls the function through that pointer.


#
## Question
What are pure virtual methods? What are they used for?

## Answer


#
## Question
What are the dangers of calling virtual functions in constructors and destructors?

## Answer


#
## Question
What is the output of Func() and why? What is wrong with this code?
```
class Object
{
public:
	Object() { ObjectManager::GetInstance().Register( this ); }
	~Object() { ObjectManager::GetInstance().Unregister( this ); }
	virtual void Print() { printf( "Hello!\n" ); }
};

class Thing : public Object
{
public:
	Thing() { g_thingCollection.Append( this ); }
	~Thing() { g_thingCollection.Remove( this ); }
	virtual void Print() override { printf( "I'm a Thing!\n" ); }
};

void Func()
{
	Object * pA = new Thing;
	Thing * pB = static_cast< Thing * >( pA );
	pA->Print();
	pB->Print();
	delete pA;
}
```

## Answer


#
## Question
Rewrite this code, that fills a buffer with random values, to make it faster
```
unsigned int Rand32(); // returns a 32-bit random number

char buffer[12];

for ( int i = 0; i < 12; i++ )
{
	buffer[i] = (char)Rand32();
}
```

## Answer
```
unsigned int Rand32(); // returns a 32-bit random number

char buffer[12];
int* pBuffer = reinterpret_cast<int*>(buffer); // reinterpret the buffer as an array of ints
for (int i = 0; i < 3; ++i)
{
	pBuffer[i] = Rand32();
}
```


#
## Question
Explain the memory usage of these two functions, and any side effects caused by these differences:
```
void Thing::A( const char * pFileName )
{
	char * pFullPath = new char[1024];
	sprintf( pFullPath, �files/%s�, pFileName );
  
	m_Texture = new Texture( pFullPath );

	delete[] pFullPath;
}

void Thing::B( const char * pFileName )
{
	char FullPath[1024];
	sprintf( FullPath, �files/%s�, pFileName );
  
	m_Texture = new Texture( FullPath );
}
```

## Answer


#
## Question
What is data alignment? What's the purpose of it?

## Answer


#
## Question
Why is unordered memory access slower than sequential access?

## Answer


#
## Question
What does the C/C++ volatile keyword do? When would you use it?

## Answer


#
## Question
Explain the following code inefficiency, and propose ways to improve it:
```
struct Foo
{
	Foo( Foo * _nextItem )
	{
		nextItem = _nextItem;
		RandomizeCoords( coords );
		... // assume other members initialization
	}
 
	int    someValue;
	Foo *   nextItem;
	bool   isInitialized;
	const char * name;
	bool   someFlag;
	float   coords[3];
};

Foo * first = nullptr;

void Init()
{
	for ( int i = 0; i < 1000; ++i )
	{
		first = new Foo( first );
	}
}

void Transform( const Matrix & _transform )
{
	for ( Foo * foo = first; foo != nullptr; foo = foo->nextItem )
	{
		_transform.ApplyTo( foo->coords );
	}
}
```

## Answer


#
## Question
List things to be aware of when using templates

## Answer


#
## Question
Give good uses of C++ templates

## Answer


#
## Question
Given the following code, implement the function EnemyCanSeePlayer(). Assume that the Enemy should be able to see the Player if the player is in the 180 degree cone in front of the Enemy:
```
struct Vec3
{
	float X, Y, Z;

	float DotProduct( const Vec3& rOther ) const;
	Vec3 CrossProduct( const Vec3& rOther ) const;
	Vec3 operator+( const Vec3& rOther ) const;
	Vec3 operator-( const Vec3& rOther ) const;
	Vec3 operator*( float scale ) const;
	float GetLength() const;
	Vec3 GetNormalized() const;
};

Vec3 GetPlayerPosition();
Vec3 GetPlayerSightDir();
Vec3 GetEnemyPosition();
Vec3 GetEnemySightDir();

bool EnemyCanSeePlayer()
{
	...
}
```

## Answer


#
## Question
Given a 3D world where Y is the up axis, write a function that builds a matrix (right-handed, Matrix struct definition is up to you) for placing a camera, looking at a target world position along its local Z axis:
```
void BuildCameraMatrix( const Vec3 & camPos, const Vec3 & targetPos, Matrix & camMat )
{
	...
}
```

## Answer


#
## Question
Implement and document this C function that reverses a string:
```
void ReverseString(const char * inStr, char * outStr)
{
	...
}
```

## Answer


#
## Question
Let say you have random behaviors and/or crashes in your game when doing the same specific action (firing your gun for example). What could cause such a non-deterministic bug? How do you proceed to debug it?

## Answer


#
## Question
How many time will this loop execute?
```
unsigned char count = 150;
count *= 2;
unsigned char i = 50;

for (i = 0; i <= count; ++i)
{
	// do something
}
```

## Answer


#
## Question
Write a non-recursive version of Func(). Why will it be better?
```
int Func( int n )
{
	if ( n > 1 )
	{
		return n * Func( n - 1 );
	}
	else
	{
		return 1;
	}
}
```

## Answer


#
## Question
Given the following code that computes the number of pixels of some image file, what is the purpose of Func()?
```
int Func( int value )
{
	union Union
	{
		int integer;
		unsigned char bytes[ 4 ];
	};
	Union in;
	in.integer = value;
	Union out;
	out.bytes[ 0 ] = in.bytes[ 3 ];
	out.bytes[ 1 ] = in.bytes[ 2 ];
	out.bytes[ 2 ] = in.bytes[ 1 ];
	out.bytes[ 3 ] = in.bytes[ 0 ];
	return out.integer;
}

int GetNumPixels( const char * filename )
{
	int numPixels = 0;
	FILE * pFile = fopen( filename, "rb" );
	if ( pFile )
	{
		int width;
		int height;
		if ( fread( &width, sizeof( width ), 1, pFile ) == 1 &&
			 fread( &height, sizeof( height ), 1, pFile ) == 1 )
		{
			width = Func( width );
			height = Func( height );
			numPixels = width * height;
		}
		fclose( pFile );
	}
	return numPixels;
}
```

## Answer


#
## Question
What is the distinctiveness of a constructor with a single parameter?

## Answer


#
## Question
Explain the C++ explicit keyword

## Answer


#
## Question
What does the C++ mutable keyword do? When would you use it?

## Answer


#
## Question
What is reflection? What are the usages of it?

## Answer


#
## Question
The �mutable� keyword appointed to a class data member allows us to change the content of that data from otherwise const tagged functions.
This might suggest some faults in the class design but can you picture a scenario where this won�t be the case?

## Answer


#
## Question
We�re writing an event system for our game and we decided to create a class that models the event itself. Please sketch a proposal for such a class, knowing that, through events, we need to pass a variable amount of data.
```
class Event
{
    // ...
};
```

## Answer
```
class Event
{
public:
    template <typename T>
    Event(const T& data) : m_Data(data) {}
    
    template <typename T>
    inline T data() const
    {
        return std::any_cast<T>(m_Data);
    }
    
private:
    std::any m_Data;
};
```

#
## Question
Consider 3 objects A, B and C with the following relationship:
- B and C are owners of A.
- A accesses information from B, so it stores a pointer to it.

Please model the above dependencies using raw or smart pointers.

## Answer


#
## Question
Given the following class that contains a template function:
```
class Stuff
{
public:
	template <typename T>
	void Look_At_Pointer(T *ptr)
	{
		//staring at ptr...
	}
};
```
Please describe a way to deny calls to that with `void *` arguments [i.e. `void *ptr; Look_At_Pointer(ptr)` ]

## Answer


#
## Question
Having the following functions:
- `void func(const some_type &param)`
- `void func(some_type &&param)`

Write a 3rd function that can receive both lvalue and rvalue arguments and can select and call the appropriate variante of the above `func`

## Answer
```
template <typename T>
void wrapper(T&& param)
{
    func(std::forward<T>(param));
}
```


#
## Question
Half-orcs are a mix between humans and orcs. Since both humans and orcs have a lot of common traits, we can all agree that both are part of the larger �humanoids� group.
Interestingly enough, while humans can have a variety of skin colors and orcs are green, for some reason half-orcs are always red.

Please model the above statements using C++ classes.

## Answer
```
using color_t = unsigned int;

class Humanoid
{
public:
    Humanoid(color_t skinColor) : m_SkinColor(skinColor) {}
    
    color_t skin_color() const
    {
        return m_SkinColor;
    }
        
protected:
    color_t m_SkinColor;
};


class Human : virtual public Humanoid
{
public:
    Human(color_t skinColor) : Humanoid(skinColor) {}
};


class Orc : virtual public Humanoid
{
public:
    Orc() : Humanoid(0xff0000) {}
};


class HalfOrc : public Human, public Orc
{
public:
    HalfOrc() : Humanoid(0xff0000), Human(0xff0000) {}
};

```


#
## Question
When designing a camera for a 3rd person game we decided to allow rotations about horizontal and vertical axis.
When rotating around the horizontal axis we would like to vary the distance to target (player) depending on the angle.
Maybe moving the camera away for high angle shots and closing in for low angles, near the ground.

Please propose an implementation of those requirements.
What camera parameters would you choose to expose so that design can tweak that behaviour.

## Answer


#
## Question
Given a large 2d game map we would like to pathfind our way between any 2 points.
For this scenario we will use a grid to partition the space, each cell being either free or blocked by some collision box.
Also we would like to consider dynamic moving obstacles (like other moving characters) that would need to be avoided.

Please propose a possible implementation for this problem.

## Answer


#
## Question
Consider a character that can be moved on some game map by choosing a destination with the mouse.
When navigating, the character can select from one of the following actions - walk, run or jump over obstacles.
The pathfinder will compute a path from the current location to the desired one and what remains for us is to determine the appropriate moving action (e.g. can -run- in an open environment, but has to transition to just -walk- when traversing a narrow ledge).
- Please describe a high level approach to select the 'natural' chain of actions while navigating some path.
- The character can also attack, thus needing to do a transition from his current state. Actually, we realised that he can do all sorts of things and there�s an ever growing number of states and transitions. Please suggest an approach to avoid having to handle a great number of states and transitions.

## Answer


#
## Question
Given a plane defined by a point Q and a normal vector n, a point P can be projected on the mentioned plane in a direction indicated by another vector v.
We'll call the resulting projection point by P_proj.
- Compute the projected point P_proj, writing the equation that links to P_proj to P
Now consider that the direction of projection, previously given by v, is now defined by the line defined by the origin point O and the point P.
- Write down the equation that models this new projection. Please mention the usual name attributed to this kind of projection.

## Answer


#
## Question
Review the following code. Can you spot what is wrong with it?
```
template <typename T>
class Stack
{
public:
	Stack() : 
		m_pData(0),
		m_capacity(0)
	{
	}

	~Stack()
	{
		if (m_pData)
			delete m_pData;
	}

	void Initialise(const size_t& capacity)
	{
		m_pData = new T[capacity];
		m_capacity = capacity;
		Size = 0;
	}

	void Push(const T& value)
	{
		if (Size < m_capacity)
			m_pData[++Size];
	}

	T Pop()
	{
		return m_pData[--Size];
	}

	bool IsEmpty()
	{
		return (Size == 0);
	}

	size_t Size;

private:
	T* m_pData;
	size_t m_capacity;
}
```

## Answer
- The destructor uses `delete` instead of `delete[]` to deallocate the array allocated with `new[]`. This leads to undefined behavior.
- The `Size` member variable is public, which violates encapsulation and allows external modification. Moreover it is not initialized in the constructor, which can lead to undefined behavior when accessing it.
- The `Push` method is wrong. It does not assign the input value, and increments `Size` before assigning the value, which skips the first index and causes out-of-bounds access when `Size` equals `m_capacity`.


#
## Question
Suppose you have the classes defined as in the code below. What is going to be printed out at runtime?
```
#include <iostream>

class Base
{
public:
    Base() { s_Counter++; }
    static int GetCounter() { return s_Counter; }

private:
    static int s_Counter;
};

int Base::s_Counter = 0;


class Derived : public Base {};


int main()
{
    Base    a;
    Derived b;
    Derived c;
    Base    d;

    std::cout << a.GetCounter() << " ";
    std::cout << b.GetCounter() << " ";
    std::cout << c.GetCounter() << " ";
    std::cout << d.GetCounter() << std::endl;

    return 0;
}
```

## Answer


#
## Question
Suppose you have the code below. What is going to be printed out at runtime?
```
#include <iostream>

int main()
{
    int a{0};
    int b{5};
    int* c = &a;
    int* d = &b;
    std::swap(a, *c);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;

    return 0;
}
```

## Answer


#
## Question
Suppose you have the classes defined as in the code below. What is going to be printed out at runtime?
```
#include <iostream>

class Base
{
public:
    Base() { s_Counter++; }
    int GetCounter() { return s_Counter; }

private:
    static int s_Counter;
};

int Base::s_Counter = 0;


class Derived : public Base
{
public:
    int GetCounter() const { return m_Counter; }

private:
    unsigned int m_Counter{};
};


int main()
{
    Base    a;
    Derived b;
    Derived c;
    Base    d;

    std::cout << a.GetCounter() << " ";
    std::cout << b.GetCounter() << " ";
    std::cout << c.GetCounter() << " ";
    std::cout << d.GetCounter() << std::endl;

    return 0;
}
```

## Answer


#
## Question
Suppose you have the classes defined in the code below. What is going to be printed out at runtime?
```
#include <iostream>

class Base
{
public:
    virtual void Test() { std::cout << "Base::Test" << std::endl; }
};


class Derived : public Base
{
public:
    void Test() override { std::cout << "Derived::Test" << std::endl; }
};


int main() 
{
    Base  a;
    Base* b = new Derived();
    Base  c = Derived();
    a.Test();
    b->Test();
    c.Test();
    delete b;

    return 0;
}
```


Q. Describe what it's going to happen in the following code.
```
class A
{
public:
    A() = default;
    A(const A& a) = delete;
    ~A() = default;
};


int main()
{
    A a;
    A b(a);
    return 0;
}
```

## Answer


#
## Question
Given the code below, describe what is going to happen.
```
struct Object
{
    int m_Value{0};
};


static Object GetAnObject()
{
    Object result;
    return result;
}

int main()
{
    Object& refToObject = GetAnObject();
    return 0;
}
```

## Answer


#
## Question
Given the code below, describe what is going to happen.
```
struct Object
{
    int m_Value{0};
};

static Object GetAnObject()
{
    Object result;
    return result;
}

int main()
{
    const Object& refToObject = GetAnObject();
    return 0;
}
```

## Answer


#
## Question
Given the code below, describe what is going to happen.
```
struct Object
{
    int m_Value{0};
};


static Object GetAnObject()
{
    Object result;
    return result;
}

int main()
{
    Object&& rvalueRef = GetAnObject();
    return 0;
}
```

## Answer


#
## Question
Given the code below, tell whether or not the code compiles. In the affermative case, state what is going to be printed out at run-time.
```
#include <iostream>

int main()
{
    int  a{128};
    int  b{1024};
    int& c{a};
    int* d{};

    c  = b;
    *d = 54;
    std::swap(a, b);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;

    return 0;
}
```

## Answer


#
## Question
Given the Object class belowm and taking into account the RVO (Return Value Optimization), describe what it is going to be printed out at run-time.
```
#include <iostream>

class Object
{
public:
    Object()                    { std::cout << "def ctor" << std::endl; }
    Object(const Object& other) { std::cout << "cpy ctor" << std::endl; }
    Object(Object&& other)      { std::cout << "mov ctor" << std::endl; }
    virtual ~Object()           { std::cout << "dtor" << std::endl; }

    Object& operator=(const Object& other) { std::cout << "cpy assign" << std::endl; return *this; }
    Object& operator=(Object&& other)      { std::cout << "mov assign" << std::endl; return *this; }
};


static Object GetObject()
{
    return Object();
}


int main()
{
    Object aVariable;
    aVariable = GetObject();
    return 0;
}
```

## Answer


#
## Question
 Given the Object class belowm and taking into account the RVO (Return Value Optimization), describe what it is going to be printed out at run-time.
```
#include <iostream>

class Object
{
public:
    Object()                    { std::cout << "def ctor" << std::endl; }
    Object(const Object& other) { std::cout << "cpy ctor" << std::endl; }
    Object(Object&& other)      { std::cout << "mov ctor" << std::endl; }
    virtual ~Object()           { std::cout << "dtor" << std::endl; }

    Object& operator=(const Object& other) { std::cout << "cpy assign" << std::endl; return *this; }
    Object& operator=(Object&& other)      { std::cout << "mov assign" << std::endl; return *this; }
};


static Object GetObject()
{
    return Object();
}


int main()
{
    Object aVariable{ std::move(GetObject()) };
    aVariable = GetObject();
    return 0;
}
```

## Answer


#
## Question
Suppose Vector is a class representing a position in 3D space defined in the code below. What does the test variable represent?
```
#include <cmath>
#include <iostream>

class Vector
{
public:
    //////////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR
    //////////////////////////////////////////////////////////////////////////////
    constexpr Vector(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    constexpr Vector(const Vector& other) = default;

    //////////////////////////////////////////////////////////////////////////////
    // MATH
    //////////////////////////////////////////////////////////////////////////////
    constexpr float Dot(const Vector& other) const { return x*other.x + y*other.y + z*other.z; }

    constexpr float Norm() const { return std::sqrt(Dot(*this)); }

    constexpr Vector& Normalize()
	{
        const float d = Norm();
        x /= d;
        y /= d;
        z /= d;
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////////
    // OPERATOR
    //////////////////////////////////////////////////////////////////////////////
    constexpr Vector operator-(const Vector& other) const { return Vector{x-other.x, y-other.y, z-other.z}; }

public:
    //////////////////////////////////////////////////////////////////////////////
    // VARIABLE
    //////////////////////////////////////////////////////////////////////////////
    float x, y, z;
};


int main()
{
    Vector playerPosition{1, 1, 0};
    Vector enemyPosition{0, 0, 0};
    Vector test(playerPosition - enemyPosition);
    test.Normalize();
    std::cout << test.x << " ";
    std::cout << test.y << " ";
    std::cout << test.z << std::endl;
    return 0;
}
```

## Answer


#
## Question
Assume a class Vector, representing a 3D coordinate in space, is fully implemented.
We have a game in which all entities have a super-power: they can see 180� in front of them.
The Vector representing entities' view (i.e. where their head is turned to) is called sight.
We want to find the most efficient way to understand if the enemy can see the player.
The data you have access to is represented by these variables:
```
    Vector playerPosition;
    Vector playerSight;
    Vector enemyPosition;
    Vector enemySight;
```
Among the given solutions, select the correct one and state why is the case.

```
//////////////////////////////////////////////////////////////////////////////
// A
//////////////////////////////////////////////////////////////////////////////
bool Test(const Vector& first, const Vector& second) {
    return first.Dot(second) > 0;
}

Vector enemyToPlayer = playerPosition - enemyPosition;
enemyToPlayer.Normalize();
bool canEnemySeeThePlayer = Test(enemySight, enemyToPlayer);



//////////////////////////////////////////////////////////////////////////////
// B
//////////////////////////////////////////////////////////////////////////////
bool Test(const Vector& first, const Vector& second) {
    return first.Dot(second) > 0;
}

Vector enemyToPlayer = playerPosition - enemyPosition;
bool canEnemySeeThePlayer = Test(enemySight, enemyToPlayer);



//////////////////////////////////////////////////////////////////////////////
// C
//////////////////////////////////////////////////////////////////////////////
bool Test(const Vector& first, const Vector& second) {
    return first.Dot(second) > 0;
}

Vector enemyToPlayer = enemySight - playerSight;
bool canEnemySeeThePlayer = Test(enemySight, enemyToPlayer);



//////////////////////////////////////////////////////////////////////////////
// D
//////////////////////////////////////////////////////////////////////////////
bool Test(const Vector& first, const Vector& second) {
    return first.Dot(second) > 0;
}

Vector enemyToPlayer = enemyPosition - playerPosition;
bool canEnemySeeThePlayer = Test(enemySight, enemyToPlayer);



//////////////////////////////////////////////////////////////////////////////
// E
//////////////////////////////////////////////////////////////////////////////
bool Test(const Vector& first, const Vector& second) {
    return first.Dot(second) < 0;
}

Vector enemyToPlayer = enemySight - playerSight;
bool canEnemySeeThePlayer = Test(enemySight, enemyToPlayer);
```

## Answer


#
## Question
You have to implement an Achievement system, basically a reward system when certain events happen in the game.
```
Example:
    "You get 10000 points when you kill 100 enemies"
    "You get 10000 points when you fall a cliff 5 times"
```
Which one of the following design patterns will you consider to use?
- Singleton
- Prototype
- Visitor
- Observer
- Strategy

## Answer


#
## Question
Suppose it exists a class called InputHandler, used to handle the player's inputs during the game.
Among other things, the class has a handleInput() function which is used to select an action whenever a button is pressed.
```
class InputHandler
{
public:
    // ...

    void handleInput()
    {
        if(isPressed(BUTTON_X)) reload();
        else if(isPressed(BUTTON_Y)) swapWeapon();
        else if(isPressed(BUTTON_A)) jump();
        else if(isPressed(BUTTON_B)) crouch();
    }

    // ...
};
```
Which one of the following design pattern would you apply to improve the input handling?
- Flyweight pattern
- Factory pattern
- Command pattern
- Singleton pattern
- Visitor pattern

## Answer


#
## Question
Suppose you have a function
```
    SetBitTo1(unsigned int value, unsigned int pos)
```
that set to 1 the bit at position pos in the given value.
What is going to be printed out at runtime?
```
#include <iostream>

unsigned int SetBitTo1(unsigned int value, unsigned int pos)
{
    return value | (1 << pos);
}

int main()
{
    std::cout << SetBitTo1(0,0) << " ";
    std::cout << SetBitTo1(0,1) << " ";
    std::cout << SetBitTo1(2,1) << " ";
    std::cout << SetBitTo1(4,2) << std::endl;
    return 0;
}
```

## Answer


#
## Question
Suppose you have a function:
```
    static int f(int value)
```
processing the input value the way showed in the code below. What is going to be printed out at runtime?
```
#include <iostream>

static int f(int value)
{
    int result{value};
    result += value | 3;
    return (value > 3);
}

int main()
{
    for(int i = -1; i < 7; ++i)
    {
        std::cout << f(i) << " ";
    }
    return 0;
}
```

## Answer


#
## Question
Suppose you have the classes described in the code below.
What is going to be printed out at runtime?
```
#include <iostream>

// Class A
class A
{
public:
    A()          { std::cout << "ctor A" << std::endl; }
    virtual ~A() { std::cout << "dtor A" << std::endl; }
};


// Class B
class B : public A
{
public:
    B()  { std::cout << "ctor B" << std::endl; }
    ~B() { std::cout << "dtor B" << std::endl; }
};


int main()
{
    A* obj = new B();
    delete obj;

    return 0;
}
```

## Answer


#
## Question
Suppose you have the classes described in the code below.
What is going to be printed out at runtime?
```
#include <iostream>

// Class A
class A
{
public:
    A()  { std::cout << "ctor A" << std::endl; }
    ~A() { std::cout << "dtor A" << std::endl; }
};


// Class B
class B : public A
{
public:
    B()  { std::cout << "ctor B" << std::endl; }
    ~B() { std::cout << "dtor B" << std::endl; }
};


int main() 
{
    A* obj = new B();
    delete obj;

    return 0;
}
```

## Answer


#
## Question
Suppose you have a function:
```
    static int f(int value)
```
processing the input value the way showed in the code below. What is going to be printed out at runtime?
```
#include <iostream>

static int f(int value)
{
    int result{value};
    result = (value >> 1) + 1;
    return result;
}


int main()
{
    for(int i = 0; i < 3; ++i) {
        std::cout << f(i) << " ";
    }
    return 0;
}
```

## Answer


#
## Question
Given the following String class and its defined operations, list the String operations that are called from function Test() in the order they are called.
A Assume the four unimplemented functions are implemented elsewhere.
```
class String 
{ 
public:
    String() 	  { m_str = new char[1]; *m_str = 0; }
    ~String();
    String(const char* str);
    String(const String& other);
    String& operator = (const String& other);
private:
    char* m_str;
};

String Func(String str1)
{
    String str2;
    str2 = str1;
    return str2;
}

void Test()
{
    String str3("Hello");
    str3 = Func(str3);
}
```

## Answer


#
## Question
This function looks fine but there is a performance problem with it. What is it and what ways are there round it?
```
void addToAll(vec3* array, vec3* toAdd, u32 num)
{
    for (int i = 0; i < num; i++)
    {
        array->x += toAdd->x;
        array->y += toAdd->y;
        array->z += toAdd->z;
        array++;
    }
}
```

## Answer


#
## Question
You want to know:
- where a particular variable is stored in an executable
- what the biggest global variables in a program are (by storage space, not value)

How would you go about finding this information without running the program?

## Answer


#
## Question
Examine the following function. What does it accomplish?
```
int foo(int val)
{
    int n = 0;
    while (val)
    {
        val &= val - 1;
        ++n;
    }
    return n;
}
```

## Answer


#
## Question
Compare the following function and macro definition. In what cases will they produce different results and/or side effects?
```
int square(int val) { return val*val; }
#define square(val) (val*val)
```

## Answer


#
## Question
Read and analyze the following code.
- What does it do?
- What is its computational complexity?
- What is its memory complexity?
```
#include <algorithm>
#include <vector>

using namespace std;

vector<int> do_thing(vector<int> data1, vector<int> data2)
{
    vector<int> output;
    sort(data1.begin(), data1.end());
    for (auto i : data2)
    {
        auto it = lower_bound(data1.begin(), data1.end(), i);
        if (it != data1.end() && *it == i)
        {
            output.push_back(i);
        }
    }
    return output;
}
```
One of our client would like to use this function, but he/she is not interested in having the output vector, and can't afford to use memory to store the values.
Instead, he/she would like the function to print directly the value i instead of pushing it back in the output vector.
Change the function in such a way each customer can decide its behavior.

Read and analyze the following code.
- Is it doing the the same thing as the previous algorithm?
- What is its computational complexity?
- What is its memory complexity?
- Which is the fastest?
```
#include <set>

vector<int> do_thing2(vector<int> data1, vector<int> data2)
{
    vector<int> output;
    set<int> data1_set;
    for (auto i : data1)
    {
        data1_set.insert(i);
    }
    for (auto i : data2)
    {
        if (data1_set.find(i) != data1_set.end())
        {
            output.push_back(i);
        }
    }
    return output;
}
```

## Answer


#
## Question
How can you improve built times of a large C++ project?

## Answer


#
## Question
Given a set of natural positive numbers [1, ..., N], where N is known a entry is taken out from the set.
Explain how you find the missing number
```
Ex.:

N == 4
	[3, 4, 1]  Missing is 2

N == 6
	[1, 2, 5, 6, 3] Missing is 4
```

## Answer


#
## Question
Given two list of unique numbers, create a third list containing the numbers of both lists, without any duplicate
```
Ex.:
A [45, 1, 6, 77, 0, 5, ... ]
B [2, 80, 1, 54, 5, 35, ... ]

The number one is contained in both lists, but it should appear only once in the result
```

## Answer


#
## Question
What is the size of an instance of this class? How would you go about making it smaller?
```
typedef struct
{	
    float x, y, z;
} vector3;

typedef struct
{
    float x, y;
} vector2;

class triangle
{
public:
    unsigned short m_lightmapID;
    unsigned int   m_materialID;
    unsigned int   m_polygonID;

    vector3  m_coords[3];
    vector3  m_vertNormals[3];
    vector3  m_faceNormal;

    unsigned char  m_isTrans;
    unsigned int   m_objectID;
    unsigned char  m_lodLevel;
    unsigned int   m_lodID;
 
    vector3  m_midpoint;
    vector2  m_textureUVs[3];
    vector2  m_lightmapUVs[3];
    vector3  m_colour[3];

    triangle   *m_adjacentWorldPolys[3];
    triangle   *m_adjacentUVPolys[3];
    unsigned char   m_adjacentWorldEdges[6];
 
    triangle();
};
```

## Answer


#
## Question
This is a recursive function that transverses a tree by decoding secret messages.
What problem would you run into if the tree was very deep(apart from it being slow)? Can you rearrange it to solve this problem ?
```
void recurseDecodeSecretMessage(node* n)
{
    s8 tmp[MAX_MESSAGE_LENGTH];
    decodeSecretMessage(tmp, n->message, n->key);
    if (strcmp(tmp, "Go Left") == 0)
    {
        recurseDecodeSecretMessage(n->leftNode);
    }
    else
    {
        recurseDecodeSecretMessage(n->rightNode);
    }
}
```

## Answer


#
## Question
These are part of a pack file system(single file that contains many files). There are many entries in each pack!
How would you go about reducing the memory use of this, and as a bonus, speed up the find ?
```
typedef struct pakFileEntry_s
{
  char name[MAX_FILENAME_LENGTH];
  u32 fileSize;
  u32 fileOffset;
} pakFileEntry;

pakFileEntry* findFile(pack* pak, char* name)
{
    for (i = 0; i < pak->numEntries; i++)
    {
        pakFileEntry* e = &pak->entry[i];
        if (strcmp(e->name, name) == 0)
            return e;
    }
    return NULL;
}
```

## Answer


#
## Question
You have a file (in text format) that contains a list of symbols, like this:
```
0 class:function
20 class:otherfunction
...
...
80 otherclass:function
```
The first column is a decimal offset for the symbol. We want to know the total size of the symbols in each class. How would you do this?

## Answer


#
## Question
```
template<class T>
void BubbleSort(T* ptr, u32 num)
{
	u32 change;
	do
	{
		change = FALSE;
		for (int i = 0; i < num - 1; i++)
		{
			if (ptr[i] > ptr[i + 1])
			{
				T tmp = ptr[i];
				ptr[i] = ptr[i + 1];
				ptr[i + 1] = tmp;
				change = TRUE;
			}
		}
	} while (change);
}

BubbleSort<u32>(someNumbers, 100);
BubbleSort<enumT>(someEnums, 100);
BubbleSort<enum2T>(someEnum2s, 100);
BubbleSort<u8*>(some32bitPointers, 100);
```
Ignoring the inherent problems of bubble sort, why is this wasteful?
(_If you are stuck consider why templates can be bad, but also the advantages they offer._)
How would you go about writing a generic replacement?

## Answer


#
## Question
The following class is used to store entries in a string table, containing thousands of entries. How could the memory use be reduced?
```
class StringTableEntry
{
public:

	StringTableEntry();
	~StringTableEntry();

	virtual char* getString(void)
	{
		return ptr;
	}

	virtual u32 getFlags(void)
	{
		return flags;
	}

	u32 flags;
	char* ptr;
};
```

## Answer


#
## Question
Write a C/C++ function to insert a list element into a double-linked list given a pointer to the new element and a pointer to the element which the new element is to follow.

## Answer
```
void Insert(Node* insertAfter, Node* nodeToInsert)
    {
        if ((insertAfter == nullptr) || (nodeToInsert == nullptr))
        {
            return;
        }

        nodeToInsert->next = insertAfter->next;
        insertAfter->next = nodeToInsert;
        nodeToInsert->prev = insertAfter;
        

        if (insertAfter == nullptr)
        {
            nodeToInsert->next = head;
            if (head != nullptr)
            {
                head->prev = nodeToInsert;
            }
            head = nodeToInsert;
            nodeToInsert->prev = nullptr;
        }
        else
        {
            nodeToInsert->next = insertAfter->next;
            nodeToInsert->prev = insertAfter;
            if (insertAfter->next != nullptr)
            {
                insertAfter->next->prev = nodeToInsert;
            }
            insertAfter->next = nodeToInsert;
        }
    }
```


#
## Question
Use C# or C++ to show the structure of an element of a sorted binary tree in which each element contains a single character. Describe briefly what any reference point to.

## Answer


#
## Question
Use C# or C++ to implement a function that locates the element in the tree which matches a given character.
It should match this signature:
```
Node FindElementInTree(Node root, char charToFind)
```

## Answer


#
## Question
Write a C# or C++ function which converts a character string into a signed integer without using any library functions.  
Assume that the string contains a valid integer, and no white space. 
```
// Use this signature:
int ConvertStringToInt(string s);

// for example:
int val = ConvertStringToInt("-459"); 
// val would end up with the integer value -459 in it
```

## Answer
```
int ConvertStringToInt(string s)
{
    int result = 0;
    int i = 0;
    int sign = 1;

    if (s[0] != '\0')
    {
        if (s[0] == '-')
        {
            sign = -1;
            ++i;
        }
        else
        {
            if (s[0] == '+')
            {
                ++i;
            }
        }

        for(; s[i] != '\0'; ++i)
        {
            result = result * 10 + (s[i] - '0');
        }
    }
    return sign * result;
}
```

#
## Question
Assume you have a variable p:
```
unsafe
{
    int* p = (int*)0x0A000000;
}
```
what is the value of p+10 and why?

## Answer
In pointer arithmetic, adding an integer to a pointer moves the pointer by that many elements of the type pointed to.
In this context, `p+10` will be `0x0A000000 + 10 * sizeof(int)`, which is `0x0A000000 + 40`, or `0x0A000028`.


#
## Question
If you have the following struct:
```
struct A 
{
	char a;
	int b;
};
```
What is `sizeof()` of this structure? And why is it so?

## Answer
The size will be 8 bytes: 1 byte for the char, 3 bytes of padding to align the int to a multiple of 4 bytes, and 4 bytes for the int.


#
## Question
If you have the following C++ class:
```
class B
{
public:
	virtual ~B();
	int getA() const { return a; }

private:
	int a;
};
```
What is `sizeof()` of this type? And why is it so?

## Answer
On a 32-bit system the size will be 8 bytes: 4 bytes for the integer and 4 bytes for the vtable pointer.
On a 64-bit system the size will be 16 bytes: 4 bytes for the integer and 8 bytes for the vtable pointer, plus 4 bytes of padding to align the class to a multiple of 8 bytes.


#
## Question
Defined below is the skeleton of a C++ String class. Implement the 4 methods that don't have an implementation yet.
Keep in mind the memory management assumptions implied  by the implementation of the default constructor.  
```
class String 
{ 
public:
    String()
	{ 
		m_str = new char[1]; 
		*m_str = 0; 
	}
		
    ~String();
    String(const char* str);
    String(const String& other);
    String& operator= (const String& other);
private:
    char* m_str;
};
```

## Answer
```
class String 
{ 
public:
    String()
	{ 
		m_str = new char[1]; 
		*m_str = 0; 
	}
		
    ~String()
    {
        delete[] m_str;
    }

    String(const char* str)
    {
        if (str == nullptr)
        {
            m_str = new char[1]; 
		    *m_str = 0; 
        }
        else
        {
            m_str = new char[strlen(str) + 1];
            strcpy(m_str, str);
        }
    }

    String(const String& other) : String(other.m_str) {}

    String& operator= (const String& other)
    {
        if (this != &other)
        {
            delete[] m_str;
            m_str = new char[strlen(other.m_str) + 1];
            strcpy(m_str, other.m_str);
        }
        return *this;
    }

private:
    char* m_str;
};
```


#
## Question
Write a C# or C++ method on LinkedList (which is provided in C++ as reference) that inserts a list element into a doubly linked list given a pointer to the new element and a pointer to the element which the new element is to follow assuming this structure.
Remember to take care of edge cases.
```
class Node
{
public:
	Node* prev;
	Node* next; // Is NULL if this is the last element
	void* data;
};

class LinkedList
{
public:
	// Implement this! If insertAfter is null then the element is 
	// inserted at the beginning of the list. You can assume
	// that insertAfter is an existing element of the list and
	// nodeToInsert is not already a member of the list.
	void Insert(Node* insertAfter, Node* nodeToInsert); 

	// ...
private:
	Node* head; // Points to first element
	Node* tail; // Points to last element
};
```

## Answer
```
class Node
{
public:
	Node* prev;
	Node* next; // Is NULL if this is the last element
	void* data;
};

class LinkedList
{
public:
	void Insert(Node* insertAfter, Node* nodeToInsert)
    {
        if (nodeToInsert == nullptr)
        {
            return;
        }

        if (insertAfter == nullptr)
        {
            nodeToInsert->next = head;
            if (head != nullptr)
            {
                head->prev = nodeToInsert;
            }
            head = nodeToInsert;
            nodeToInsert->prev = nullptr;
        }
        else
        {
            nodeToInsert->next = insertAfter->next;
            nodeToInsert->prev = insertAfter;
            if (insertAfter->next != nullptr)
            {
                insertAfter->next->prev = nodeToInsert;
            }
            insertAfter->next = nodeToInsert;

            if (insertAfter == tail)
            {
                tail = nodeToInsert;
            }
        }
    }


	// ...
private:
	Node* head; // Points to first element
	Node* tail; // Points to last element
};
```


#
## Question
A game engine arranges its objects in a hierarchy. 
Assume we have a scene consists of the following 4 objects:
- The root R.
- A and B: children of R.
- C: child of B.

The position and orientation of each object is represented as a 4x4 matrix transforming the local space of the object to the space of its' parent.
Vectors are in homogeneous coordinates and are represented by 4-component column vectors.

What is the equation for the matrix M transforming points from the local space of A to the local space of C?

## Answer


#
## Question
Describe geometrically the difference between applying a rigid transform to the vectors `p = [x y z 1]^T` and `q = [x y z 0]^T`

## Answer
The two vectors are expressed in homogeneous coordinates. The first one is a point in 3D space, while the second one is a direction vector.
The difference between them is that the first one is affected by both translation and rotation, while the second one only by the rotation.


#
## Question
Representing rigid transformations by 4x4 matrices will in a straightforward implementation require 16 floats of data per object.
Briefly describe a representation using as few floats as possible without loss of precision.

## Answer
A first possibility could be ommitting the bottom part of the matrix, which is always [0 0 0 1]. This would reduce the size to 12 floats.
A second possibility could be using dual quaternions to represent the rotation and translation of the object. This would reduce the size to 8 floats.
Another possibility could be using a quaternion to represent the rotation and a 3D vector to represent the translation. This would reduce the size to 7 floats.

#
## Question
Implement a BitArray class by completing the skeleton below. You should aim at using as little memory as possible. You are not allowed to use standard library functions. And remember to do bounds checking.
```
class BitArray
{
public:
	BitArray(int size);
	~BitArray();
	bool GetBit(int index) const;
	void SetBit(int index, bool value);
private:
	...
};
```

## Answer
```
class BitArray
{
public:
    BitArray(int size)
        : size(size)
    {
        size = size <= 0 ? 1 : size;
        const int count = (size + 7) / 8;
        data = new unsigned char[count];
        for (int i = 0; i < count; ++i)
        {
            data[i] = 0;
        }
    }

	~BitArray()
    {
        delete[] data;
    }


	bool GetBit(int index) const
    {
        if (index < 0 || index >= size)
        {
            return false;
        }
        return (data[index / 8] & (1 << (index % 8))) != 0;
    }

	void SetBit(int index, bool value)
    {
        if (index < 0 || index >= size)
        {
            return;
        }

        int mask = 1 << (index % 8);
        if (value)
        {
            data[index / 8] |= mask;
        }
        else
        {
            data[index / 8] &= ~mask;
        }
    }

private:
	std::size_t size;
    unsigned char* data;
};
```