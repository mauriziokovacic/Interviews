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
a. Used for compile-time type conversions. It can convert between related types (e.g., base and derived classes) and perform numeric conversions. It does not perform runtime checks.
b. Used to add or remove the `const` qualifier from a variable. It allows modifying a const object, but should be used with caution. Modifying a truly const object after removing const is undefined behavior.
c. Used for low-level type conversions. It can convert any pointer type to any other pointer type, but it does not check for type safety. It should be used with caution as it can lead to undefined behavior if misused.
d. Used for safe downcasting in class hierarchies. It checks at runtime if the cast is valid (i.e., if the object is of the target type). If the cast fails, it returns `nullptr` for pointer types or throws an exception for references.
e. A legacy casting method that combines the functionality of static_cast, const_cast, and reinterpret_cast. It is less safe and harder to read compared to C++-style casts, as it does not specify the intent of the cast.

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
Pure virtual methods in C++ are methods declared within a base class that must be overridden by any derived class.
They are specified by assigning = 0 to the method declaration in the base class.
A class containing at least one pure virtual method is considered an abstract class and cannot be instantiated directly.

They are used to create abstract base classes that serve as blueprints for other classes.
Pure virtual methods define a contract that derived classes must fulfill, ensuring they implement specific behavior.
They enable runtime polymorphism, allowing derived classes to provide their own implementation of the method.


#
## Question
What are the dangers of calling virtual functions in constructors and destructors?

## Answer
Calling virtual functions in constructors and destructors is dangerous because uring a constructor's execution, the object's type is considered to be the type of the class whose constructor is currently running, not the derived class.
This means that if a virtual function is called in a constructor, the base class version of the function will be executed, not the derived class version. This can lead to unexpected behavior and bugs.


#
## Question
What is the output of `Func()` and why? What is wrong with this code?
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
The output of `Func()` will be:
```
I'm a Thing!
I'm a Thing!
```
because `pA` is a pointer to an object of type `Thing`, and `pB` is a pointer to the same object, casted to `Thing*`.
Both pointers will call the `Print()` method of the `Thing` class, which overrides the `Print()` method of the `Object` class.

There are a few issues with this code:
- `ObjectManager::GetInstance()` assumes the instance is always valid
- `g_thingCollection` is assumed to be always valid
- `Object` class has no virtual destructor, which can lead to resource leaks or undefined behavior when deleting derived class objects through base class pointers.


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
	sprintf( pFullPath, "files/%s", pFileName );
  
	m_Texture = new Texture( pFullPath );

	delete[] pFullPath;
}

void Thing::B( const char * pFileName )
{
	char FullPath[1024];
	sprintf( FullPath, "files/%s", pFileName );
  
	m_Texture = new Texture( FullPath );
}
```

## Answer
Function `A` allocates 1024 bytes on the heap using `new char[1024]`. Function `B` allocates 1024 bytes on the stack using a local array.
The memory allocated in `A` must be explicitly deallocated using `delete[]`, while the memory allocated in `B` is automatically deallocated when the function returns.
- Stack memory is generally faster to allocate and deallocate than heap memory.
- Stack memory is limited in size, while heap memory can be larger but requires manual management.
- Function `A` may cause a memory leak if `delete[]` is not called. For instance, if an exception occurs before the `delete[]` statement, the allocated memory will not be freed.
- Function `B` may cause cause a stack overflow exception if the stack cannot accommodate the size of the array, especially if this function is called recursively or in a loop.
- Function `A` incurs the overhead of dynamic memory allocation and deallocation, while function `B` does not have this overhead.


#
## Question
What is data alignment? What's the purpose of it?

## Answer
Data alignment refers to arranging data in memory according to specific boundaries (e.g., 2, 4, 8, or 16 bytes) to match the architecture's requirements.
This ensures that data is stored at memory addresses that are multiples of the data type's size or alignment requirement.

The purpose of data alignment is to improve performance and access speed.
Misaligned data can lead to inefficient memory access, as the CPU may need to perform multiple memory accesses to read or write the data, resulting in slower performance.


#
## Question
Why is unordered memory access slower than sequential access?

## Answer
Unordered memory access is slower than sequential access primarily due to cache locality and memory prefetching.
Sequential memory access takes advantage of spatial locality, where adjacent memory locations are loaded into the cache together.
This reduces the number of expensive main memory accesses.
In contrast, unordered access often results in cache misses, as the accessed memory locations are scattered and not already in the cache.


#
## Question
What does the C/C++ volatile keyword do? When would you use it?

## Answer
The volatile keyword in C/C++ is used to indicate that a variable's value can be changed at any time by external factors outside the program's control, such as hardware or another thread.
It prevents the compiler from optimizing code in a way that assumes the variable's value remains constant between accesses.


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
- struct `Foo` is not size optimap due to potential padding. The order of members can be rearranged to minimize padding and improve cache locality.
A possible improvement rearranging its members as follows:
```
Foo* nextItem;
const char* name;
float coords[3];
int someValue;
bool isInitialized;
bool someFlag;
```
- The `Init()` function creates 1000 instances of `Foo` and links them together. This can lead to memory fragmentation and performance issues.
A possible improvement could be:
```
std::vector<Foo> fooList(1000);
Foo* previous = nullptr;

void Init()
{
	for ( int i = 0; i < 1000; ++i )
	{
        fooList[i] = Foo(previous);
        previous = &fooList[i];
	}
}
```
- The `Transform()` function iterates through the linked list of `Foo` objects, which can be inefficient due to pointer chasing.
A possible improvement could be:
```
void Transform( const Matrix & _transform )
{
	for (std::size_t i = 0; i < fooList.size(); ++i)
	{
		_transform.ApplyTo(fooList[i]);
	}
}
```


#
## Question
List things to be aware of when using templates

## Answer
Here are some key points to be aware of when using templates in C++:
1.	Code Bloat: Templates generate separate code for each type they are instantiated with, which can lead to larger binary sizes.
2.	Compilation Time: Templates can significantly increase compilation time due to the generation of multiple versions of the same code.
3.	Error Messages: Errors in template code can result in long and hard-to-read compiler error messages, especially for deeply nested templates.
4.	Type Constraints: Templates do not enforce type constraints directly. If a type does not support the required operations, errors will occur during instantiation.
5.	Specialization: Be cautious when using template specialization. It can make the code harder to read and maintain.
6.	Linker Errors: Templates can lead to linker errors if definitions are not properly included in the translation units where they are instantiated.
7.	Debugging: Debugging template code can be challenging due to the complexity of the generated code.
8.	Overhead: While templates are powerful, they can introduce runtime overhead if not used carefully, especially with non-trivial instantiations.
9.	Explicit Instantiation: Use explicit instantiation to reduce code bloat and improve compile times when you know the specific types you need.
10.	SFINAE (Substitution Failure Is Not An Error): Understand and use SFINAE or concepts (in C++20) to constrain template parameters and improve error diagnostics.
11.	Default Arguments: Templates can have default arguments, but they should be used judiciously to avoid confusion.
12.	Template Recursion: Be cautious with recursive templates, as they can lead to deep instantiation chains and potential stack overflows.
13.	Inline Definitions: Template definitions must be in the header file or explicitly instantiated in a source file to avoid linker errors.
14.	Compatibility: Ensure that the types used with templates are compatible with the operations performed within the template.
15.	Concepts (C++20): Use concepts to define constraints on template parameters, making the code more readable and error messages more meaningful.


#
## Question
Give good uses of C++ templates

## Answer
Here are some good uses of C++ templates:
1.	Generic Containers: Templates are widely used to create generic containers like `std::vector`, `std::list`, `std::map`, and `std::set` in the Standard Template Library (STL). These containers can store any data type without duplicating code.
2.	Algorithms: Templates allow the creation of generic algorithms, such as `std::sort`, `std::find`, and `std::accumulate`, which work with any container or data type that satisfies the required interface.
3.	Type-Safe Code: Templates enable type-safe code by allowing the compiler to enforce type correctness at compile time, reducing runtime errors.
4.	Custom Data Structures: Templates are ideal for implementing custom data structures like linked lists, binary trees, and hash tables that can work with any data type.
5.	Mathematical Libraries: Templates are useful for creating mathematical libraries that work with different numeric types (e.g., `int`, `float`, `double`) or even user-defined types.
6.	Policy-Based Design: Templates can be used to implement policy-based design, where behavior is customized by passing policy classes as template parameters.
7.	Compile-Time Computation: Templates can perform computations at compile time using techniques like template metaprogramming, reducing runtime overhead.
8.	Code Reusability: Templates promote code reusability by allowing the same code to work with different data types, reducing duplication and maintenance effort.
9.	Type Traits and Metaprogramming: Templates are used in type traits (e.g., `std::is_integral`, `std::is_pointer`) to inspect and manipulate types at compile time.
10.	Function Overloading: Function templates allow the creation of generic functions that can operate on different types without writing multiple overloads.
11.	Smart Pointers: Templates are used to implement smart pointers like `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`, which manage memory for any type.
12.	Custom Allocators: Templates allow the creation of custom memory allocators that can be used with STL containers or other data structures.
13.	Cross-Type Operations: Templates enable operations between different types, such as matrix multiplication or vector operations, where the types of elements may vary.
14.	Static Polymorphism: Templates enable static polymorphism through the Curiously Recurring Template Pattern (CRTP), which avoids the overhead of virtual function calls.
15.	Unit Testing: Templates can be used to create test utilities that work with multiple data types, making it easier to test generic code.


#
## Question
Given the following code, implement the function `EnemyCanSeePlayer()`. Assume that the Enemy should be able to see the Player if the player is in the 180 degree cone in front of the Enemy:
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
```
bool EnemyCanSeePlayer()
{
	Vec3 dir = (GetPlayerPosition() - GetEnemyPosition()).GetNormalized();
    return GetEnemySightDir().DotProduct(dir) >= 0.0f;
}
```


#
## Question
Given a 3D world where Y is the up axis, write a function that builds a matrix (right-handed, Matrix struct definition is up to you) for placing a camera, looking at a target world position along its local Z axis:
```
void BuildCameraMatrix(const Vec3 & camPos, const Vec3 & targetPos, Matrix & camMat)
{
	...
}
```

## Answer
```
struct Matrix
{
    Vec3 forward;
    Vec3 up;
    Vec3 right;
    Vec3 position;
};


void BuildCameraMatrix(const Vec3 & camPos, const Vec3 & targetPos, Matrix & camMat)
{
    Vec3 forward = (camPos - targetPos).Normalized();
    Vec3 right = Vec3(0.0f, 1.0f, 0.0f).CrossProduct(forward).Normalized();
    Vec3 up = forward.CrossProduct(right).Normalized();

    camMat.right = right;
    camMat.up = up;
    camMat.forward = forward;
    camMat.position = camPos;
}
```


#
## Question
Implement and document this C function that reverses a string:
```
void ReverseString(const char* inStr, char* outStr)
{
	...
}
```

## Answer
```
void ReverseString(const char* inStr, char* outStr)
{
    // Check for null pointers
    if (inStr == NULL || outStr == NULL)
    {
        return;
    }

    // Get the length of the input string
    size_t length = strlen(inStr);

    /*
    // Alternative way to calculate length without using strlen
    size_t length = 0;
    while (inStr[length] != '\0')
    {
        ++length;
    }
    +/

    // Reverse the string
    for (size_t i = 0; i < length; ++i)
    {
        outStr[i] = inStr[length - i - 1];
    }

    // Null-terminate the reversed string
    outStr[length] = '\0';
}
```

#
## Question
Let say you have random behaviors and/or crashes in your game when doing the same specific action (_Ex.: firing your gun_).
What could cause such a non-deterministic bug? How do you proceed to debug it?

## Answer
Possible causes can be found in:
1. Race Conditions: Multiple threads accessing shared resources without proper synchronization.
2. Uninitialized Variables: Using variables without initializing them can lead to undefined behavior.
3. Memory Corruption: Issues like buffer overflows, dangling pointers, or accessing freed memory.
4. Floating-Point Precision: Small differences in floating-point calculations can accumulate and cause inconsistencies.
5. Undefined Behavior: Violating language rules (e.g., out-of-bounds array access) can lead to unpredictable results.
6. External Dependencies: Relying on external systems (e.g., hardware, network) that behave inconsistently.
7. Random Number Generators: Improper seeding or usage of random number generators.
8. Concurrency Issues: Deadlocks, livelocks, or improper thread synchronization.
9. Event Timing: Events processed in an unexpected order due to timing differences.

Possible debugging steps:
1. Reproduce the Issue:
    - Try to consistently reproduce the bug by isolating the specific action or sequence of actions causing it.
2. Enable Debugging Tools:
    - Use tools like AddressSanitizer, Valgrind, or Visual Studio's built-in debugger to detect memory issues.
    - Enable thread sanitizers to catch race conditions.
3. Log Everything:
    - Add detailed logging around the problematic code to capture the state of variables, threads, and events.
4. Check for Uninitialized Variables:
    - Use static analysis tools or enable compiler warnings (-Wall -Wextra in GCC/Clang) to catch uninitialized variables.
5. Analyze Threading Code:
    - Review thread synchronization mechanisms (e.g., mutexes, locks) and ensure proper usage.
6. Use Breakpoints:
    - Set breakpoints in the debugger to step through the code and observe the program's behavior.
7. Simplify the Problem:
    - Comment out unrelated code to narrow down the scope of the issue.
8. Test on Different Systems:
    - Run the game on different hardware or operating systems to identify platform-specific issues.
9. Check Random Number Generators:
    - Ensure random number generators are properly seeded and used consistently.
10. Review Recent Changes:
    - If the bug is new, review recent code changes for potential causes.
11. Stress Testing:
    - Simulate high load or unusual conditions to trigger the bug more reliably.
12. Consult Logs and Crash Dumps:
    - Analyze logs and crash dumps to identify patterns or specific points of failure.


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
The loop will execute 45 times.
The value of `count` is 150, and when multiplied by 2, it becomes 300, but due to overflow it will become 44.
The variable i is initialized to 50, but the for loop will set it to 0 and increment it until it reaches 44, resulting in 45 iterations.


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
```
int Func( int n )
{
	while(n > 1)
    {
        n *= --n;
    }
    return n;
}
```
The non-recursive version eliminates the overhead of function calls, making it faster.
It uses constant memory and avoids stack overflow issues for large values of n.
The recursive version can lead to stack overflow for large `n` due to deep recursion.


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
The purpose of `Func()` is to reverse the byte order of a 32-bit integer, effectively converting it between little-endian and big-endian formats.


#
## Question
What is the distinctiveness of a constructor with a single parameter?

## Answer
A constructor with a single parameter in C++ is distinctive because it can be used for implicit type conversions, unless explicitly marked with the `explicit` keyword.
This means that the constructor can be invoked automatically to convert an object of the parameter's type into an object of the class.


#
## Question
Explain the C++ explicit keyword

## Answer
The explicit keyword in C++ is used to prevent implicit conversions or unintended type casting when a constructor or conversion operator is invoked.
It ensures that the constructor or operator can only be called explicitly, improving code clarity and reducing the risk of subtle bugs.


#
## Question
What does the C++ mutable keyword do? When would you use it?

## Answer
The `mutable` keyword in C++ allows a non-static data member of a class to be modified even if it is part of an object that is declared as `const`.
Normally, `const` objects prevent any modification of their members, but `mutable` provides an exception to this rule.
You would use `mutable` when you need to modify a specific member variable in a `const` context, such as within a `const` member function.
This is typically used for caching, logging, or other operations that do not conceptually alter the logical state of the object.


#
## Question
What is reflection? What are the usages of it?

## Answer
Reflection is the ability of a program to inspect, analyze, and modify its own structure, behavior, and properties at runtime.
It allows a program to examine types, methods, fields, and other metadata dynamically, without knowing them at compile time.


#
## Question
The `mutable` keyword appointed to a class data member allows us to change the content of that data from otherwise const tagged functions.
This might suggest some faults in the class design but can you picture a scenario where this won't be the case?

## Answer
There are scenarios where using the mutable keyword is justified and does not indicate a fault in the class design.
These scenarios typically involve operations that do not conceptually alter the logical state of the object, even though they modify some internal data.
Here are a few examples:
1. Caching: When a class needs to cache the result of an expensive computation, the cache can be marked as `mutable`.
This allows the cache to be updated in a `const` member function without violating the `const` contract.
2. Logging: If a class needs to log information for debugging or auditing purposes, the logging mechanism can be marked as `mutable`.
This ensures that logging can occur even in `const` member functions.
3.	Reference Counting: In smart pointers or other resource management classes, reference counts are often marked as `mutable` to allow modification in `const` operations like copying or assignment.


#
## Question
We're writing an event system for our game and we decided to create a class that models the event itself. Please sketch a proposal for such a class, knowing that, through events, we need to pass a variable amount of data.
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
```
class A;
class B;
class C;

class A
{
public:
    A(B* b) : m_B(b) {}

private:
    B* m_B; // Raw pointer to B
};

class B
{
public:
    B() : m_A(new A(this)) {} // B owns A
    B(A* a) : m_A(a) {} // B can also take ownership of A

private:
    std::shared_ptr<A> m_A; // B owns A
};

class C
{
public:
    C() : m_A(new A(m_B)) {} // C also owns A
    C(A* a) : m_A(a) {} // C can also take ownership of A

private:
    std::shared_ptr<A> m_A; // C owns A
};
```


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
```
#include <type_traits>

class Stuff
{
public:
    template <typename T, typename = std::enable_if_t<!std::is_same_v<T, void>>>
    void Look_At_Pointer(T* ptr)
    {
        // staring at ptr...
    }
};
```


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
Half-orcs are a mix between humans and orcs. Since both humans and orcs have a lot of common traits, we can all agree that both are part of the larger "humanoids" group.
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
```
struct Vec3
{
    // ...

    float x, y, z;
};

class AbstractCurve
{
public:
    // ...

    float GetValue(float t) const = 0;
};


class LinearCurve : public AbstractCurve
{
public:
    // ...

    LinearCurve(float begin, float end) : m_Begin(begin), m_End(end) {}

    float GetValue(float t) const override
    {
        return m_Begin + (m_End - m_Begin) * t;
    }

protected:
    float m_Begin;
    float m_End;
};


class GenericCurve : public AbstractCurve
{
public:
    // ...

    float GetValue(float t) const override
    {
        // ...
    }
};


struct CameraParams
{
    float minDistance;
    float maxDistance;

    float minPitchInDegrees;
    float maxPitchInDegrees;

    float minYawInDegrees;
    float maxYawInDegrees;
};


class Camera
{
public:
    // ...

    void LookAt(const Vec3& target, float yawInDegrees, float pitchInDegrees)
    {
        static constexpr float deg2rad = std::numbers::pi / 180.0f;
        static constexpr float rad2deg = 180.0f / std::numbers::pi;

        const float yaw = std::clamp(yawInDegrees, m_Params.minYawInDegrees, m_Params.maxYawInDegrees) * deg2rad;
        const float pitch = std::clamp(pitchInDegrees, m_Params.minPitchInDegrees, m_Params.maxPitchIDegrees) * deg2rad;

        const float distance = m_Curve->GetValue(std::abs(pitch * rad2deg));

        m_Position.x = target.x + distance * std::cos(yaw) * std::sin(pitch);
        m_Position.y = target.y + distance * std::sin(yaw) * std::sin(pitch);
        m_Position.z = target.z + distance * std::cos(pitch);
    }

protected:
    std::weak_ptr<Curve> m_Curve;
    CameraParams m_Params;
    Vec3 m_Position;
};

```


#
## Question
Given a large 2D game map we would like to pathfind our way between any 2 points.
For this scenario we will use a grid to partition the space, each cell being either free or blocked by some collision box.
Also we would like to consider dynamic moving obstacles (like other moving characters) that would need to be avoided.

Please propose a possible implementation for this problem.

## Answer


#
## Question
Consider a character that can be moved on some game map by choosing a destination with the mouse.
When navigating, the character can select from one of the following actions: **walk**, **run** or **jump over obstacles**.

The pathfinder will compute a path from the current location to the desired one and what remains for us is to determine the appropriate moving action (e.g. can **run** in an open environment, but has to transition to just **walk** when traversing a narrow ledge).
- Please describe a high level approach to select the 'natural' chain of actions while navigating some path.
- The character can also **attack**, thus needing to do a transition from his current state. Actually, we realised that he can do all sorts of things and there's an ever growing number of states and transitions. Please suggest an approach to avoid having to handle a great number of states and transitions.

## Answer
When computing a path for the character, we can use annotations or properties for each segment of the path to determine the appropriate action.
For instance, we can assign properties like "open area", "narrow ledge", or "obstacle" to each segment of the path.
The character can then select the proper action based on these properties. If two consecutive segments have different properties, then the character can transition between actions (e.g., from **run** to **walk** when entering a narrow ledge from an open area).

More in general, we can use a state machine or a behaviour tree to model the character's actions and transitions.
This will allow us to define high-level states (like **moving**, **attacking**, etc.) and transitions based on conditions (like reaching a certain point in the path or encountering an obstacle).
Moreover, we can group similar actions and reduce the number of states and transitions, handling them in a more abstract way, and scaling better with the growing number of actions.


#
## Question
Given a plane defined by a point $Q$ and a normal vector $\vec{n}$, a point $P$ can be projected on the mentioned plane in a direction indicated by another vector $\vec{v}$.
We'll call the resulting projection point by $\Pi(P)$.
- Compute the projected point $\Pi(P)$, writing the equation that links to $\Pi(P)$ to $P$
Now consider that the direction of projection, previously given by $\vec{v}$, is now defined by the line defined by the origin point $O$ and the point $P$.
- Write down the equation that models this new projection. Please mention the usual name attributed to this kind of projection.

## Answer
We have the following two equations:
- $(\Pi(P) - Q) \cdot \vec{n} = 0$
- $\Pi(P) = P + t \cdot \vec{v}$

Where $t$ is a scalar that determines how far along the direction $\vec{v}$ we go from $P$ to reach the plane.

Substituting the second equation into the first gives us the projection point $\Pi(P)$ in terms of $P$:
- $(P + t \cdot \vec{v} - Q) \cdot \vec{n} = 0$
- $(P - Q) \cdot \vec{n} + t \cdot (\vec{v} \cdot \vec{n}) = 0$

Then we can solve for $t$:
- $t = \frac{(Q - P) \cdot \vec{n}}{\vec{v} \cdot \vec{n}}$

Substituting $t$ back into the second equation gives us the projection point $\Pi(P)$:
- $\Pi(P) = P + \frac{(Q - P) \cdot \vec{n}}{\vec{v} \cdot \vec{n}} \cdot \vec{v}$

If the direction of projection is now defined by the line from the origin point $O$ to the point $P$, we can rewrite the equation as:
- $\Pi(P) = P + \frac{(Q - P) \cdot \vec{n}}{P \cdot \vec{n}} \cdot P$

The projection name is called perspective projection.


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
`4 4 4 4`


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
```
0
5
_address of memory pointed by c_
_address of memory pointed by d_
```


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
`4 0 0 4`


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

## Answer
```
Base::Test
Derived::Test
Base::Test
```


#
## Question
Describe what it's going to happen in the following code.
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
The code will fail to compile because the copy constructor of class `A` is deleted. 
When trying to create an object `b` as a copy of `a`, the compiler will generate an error indicating that the copy constructor is not available.


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
The code will not compile because `GetAnObject()` returns a temporary object, and `refToObject` is a non-const reference to that temporary object.


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
The code will compile and run without errors.
The temporary object returned by `GetAnObject()` will be bound to the `const Object& refToObject`.


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
The code will compile and run without errors.
The temporary returned by `GetAnObject()` is bound to the rvalue reference rvalueRef, and its lifetime is extended to the end of the `main()` function.


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
The code will compile.
However, it will cause a runtime error due to dereferencing a null pointer `d` when trying to assign `54` to it.


#
## Question
Given the Object class below and taking into account the RVO (Return Value Optimization), describe what it is going to be printed out at run-time.
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
```
def ctor
def ctor
mov assign
dtor
dtor
 ```


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
```
def ctor
mov ctor
dtor
def ctor
mov assign
dtor
dtor
```


#
## Question
Suppose `Vector` is a class representing a position in 3D space defined in the code below. What does the `test` variable represent?
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
The `test` variable represents the unit direction vector pointing from `enemyPosition` to `playerPosition`.


#
## Question
Assume a class `Vector`, representing a 3D coordinate in space, is fully implemented.
We have a game in which all entities have a super-power: they can see 180° in front of them.
The `Vector` representing entities' view (i.e. where their head is turned to) is called `sight`.
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
A


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
Observer


#
## Question
Suppose it exists a class called `InputHandler`, used to handle the player's inputs during the game.
Among other things, the class has a `handleInput()` function which is used to select an action whenever a button is pressed.
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
Command pattern


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
`1 2 2 4`


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
`0 0 0 0 0 1 1 1  `


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
```
ctor A
ctor B
dtor B
dtor A
 ```


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
```
ctor A
ctor B
dtor A
```


#
## Question
Suppose you have a function:
```
    static int f(int value)
```
processing the input value the way showed in the code below.
What is going to be printed out at runtime?
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
`1 1 2  `


#
## Question
Given the following `String` class and its defined operations, list the `String` operations that are called from function `Test()` in the order they are called.
Assume the four unimplemented functions are implemented elsewhere.
```
class String 
{ 
public:
    String() { m_str = new char[1]; *m_str = 0; }
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
1. Calls `String(const char* str)` constructor
2. Calls `String(const String& other)` constructor to copy `str3` into `str1` in `Func`
3. Calls `String()` constructor
4. Calls `operator=(const String& other)`
5. Calls `String(const String& other)` constructor for return value from `Func`
6. Calls `~String()` for `str1`
7. Calls `~String()` for `str2`
8. Calls `operator=(const String& other)` to copy the return value into `str3`
9. Calls `~String()` for `str3`


#
## Question
This function looks fine but there is a performance problem with it.
What is it and what ways are there round it?
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
The main performance problem with this function is that it does not take advantage of data locality or vectorization, and it increments the pointer in each iteration, which can be less clear and less efficient for some compilers.
A possible is the following:
```
void addToAll(const vec3* array, const vec3* toAdd, cost u32 num)
{
    for (int i = 0; i < num; ++i)
    {
        array[i].x += toAdd->x;
        array[i].y += toAdd->y;
        array[i].z += toAdd->z;
    }
}
```


#
## Question
You want to know:
1. where a particular variable is stored in an executable
2. what the biggest global variables in a program are (by storage space, not value)

How would you go about finding this information without running the program?

## Answer
1. Use a symbol table dumper: Tools like `nm` on Unix, `objdump`, or `dumpbin` on Windows can list symbols and their addresses in the executable or object files.
2. On Unix, `nm -S` can show symbol sizes. On Windows, `dumpbin /symbols` can be used to list symbols and their sizes.


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
This function counts the number of set bits (bits with value 1) in the integer `val`.


#
## Question
Compare the following function and macro definition. In what cases will they produce different results and/or side effects?
```
int square(int val) { return val*val; }
#define square(val) (val*val)
```

## Answer
Macros can produce different results and side effects when:
- The argument has side effects (e.g., `i++`, function calls).
- The argument is an expression (e.g., `1+2`) and the macro is not properly parenthesized.
- Type safety is required.

Functions are safer and more predictable.
Macros should be used with great care, and always with full parentheses around arguments and the macro body if used at all.



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
The function `vector<int> do_thing(vector<int> data1, vector<int> data2)` returns a vector containing the common elements between of `data1` and `data2`.
Its computational complexity is $O(n_{data1} log n_{data1})$ due to the sorting of `data1`, plus $O(n_{data2} log n_{data1})$ due to searching for the common elements.
Its memory complexity is $O(n)$ for the `output` vector.

If the client does not need the output vector, we can modify the function to print the values directly instead of pushing them into the output vector.
The modified function would look like this:
```
void do_thing(vector<int> data1, vector<int> data2)
{
    sort(data1.begin(), data1.end());
    for (auto i : data2)
    {
        auto it = lower_bound(data1.begin(), data1.end(), i);
        if (it != data1.end() && *it == i)
        {
            std::cout << i << std::endl; // Print instead of pushing to output
        }
    }
}
```

The second function `vector<int> do_thing2(vector<int> data1, vector<int> data2)` also returns a vector containing the common elements between `data1` and `data2`, but it uses a set to store the elements of `data1` for faster lookups.
Its computational complexity is $O(n_{data1} + log n_{data1})$ for inserting elements into the set, plus $O(n_{data2} log n_{data1})$ due to searching for the common elements.
Its memory complexity is $O(2n)$ for the `output` vector and the set.

In general, the first function is faster, because avoids the overhead of inserting elements into a set, and it is more memory efficient as it only uses one vector for output.
If `unordered_set` is used instead of `set`, the second function could be faster than the first one, as its time complexity goes down to $O(n_{data1} + n_{data2})$ in total.


#
## Question
How can you improve built times of a large C++ project?

## Answer
To improve build times of a large C++ project, consider the following strategies:
- Minimize Header File Inclusions
    - Use forward declarations where possible instead of including headers.
    - Include headers only in source files (.cpp), not in other headers, unless necessary.
- Precompiled Headers (PCH):
    - Use precompiled headers to speed up compilation of commonly used headers.
- Reduce Header File Size and Dependencies:
    - Split large headers and avoid including unnecessary headers.
    - Use the "pImpl" (pointer to implementation) idiom to reduce dependencies.
- Use Unity/Jumbo Builds:
    - Combine multiple source files into a single compilation unit to reduce overhead.
- Parallel Builds:
    - Enable multi-core compilation (e.g., /MP in Visual Studio, -j with make or ninja).
    - Use external tools such as Incredibuilds or distcc for distributed builds.
- Incremental Builds:
    - Ensure your build system only rebuilds files that have changed.
- Template Usage:
    - Limit template usage in headers, as templates can cause code bloat and longer compile times.
- Optimize Build System:
    - Use efficient build systems like CMake with Ninja, or optimize your existing build scripts.
- Disable Unnecessary Debug Info:
    - Only generate debug information when needed.
- Use Faster Storage:
    - Place your build output and intermediate files on SSDs or fast storage.
- Profile Build Times:
    - Use tools (like Visual Studio’s Build Insights, clang -ftime-trace, or ninja -d stats) to identify bottlenecks.
Applying these techniques can significantly reduce build times and improve developer productivity.



#
## Question
Given a set of natural positive numbers [1, ..., N], where N is known, a entry is taken out from the set.
Explain how you find the missing number
```
Ex.:

N == 4
	[3, 4, 1]  Missing is 2

N == 6
	[1, 2, 5, 6, 3] Missing is 4
```

## Answer
The sum of `N` natural numbers is represented as $\frac{N \cdot (N + 1)}{2}$.
By summing the numbers in the array and subtracting it from the sum of `N` natural numbers, we can find the missing number.



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
```
#include <vector>
#include <unordered_set>

// Combines two lists of unique numbers into a third list without duplicates.
std::vector<int> CombineUnique(const std::vector<int>& A, const std::vector<int>& B)
{
    std::unordered_set<int> result;
    result.insert(A.begin(), A.end());
    result.insert(B.begin(), B.end());

    // Convert the set back to a vector
    return std::vector<int>(result.begin(), result.end());
}
```

A more generic approach would be to sort both lists and then merge them, but this is less efficient than using a hash set for uniqueness.


#
## Question
What is the size of an instance of this class?
How would you go about making it smaller?
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
Assuming a 32-bit system, the size of the triangle class is 240 bytes.
By rearranging the variables in the following manner:
```
class triangle
{
public:
    triangle();
    
    triangle   *m_adjacentWorldPolys[3];
    triangle   *m_adjacentUVPolys[3];
    
    vector3  m_coords[3];
    vector3  m_vertNormals[3];
    vector3  m_colour[3];
    vector3  m_faceNormal;
    vector3  m_midpoint;
    vector2  m_textureUVs[3];
    vector2  m_lightmapUVs[3];
        

    unsigned int   m_materialID;
    unsigned int   m_polygonID;
    unsigned int   m_objectID;
    unsigned int   m_lodID;
    
    unsigned short m_lightmapID;
    unsigned char  m_adjacentWorldEdges[6];
    unsigned char  m_isTrans;
    unsigned char  m_lodLevel;
};
```
we can reduce the size of the class to 232 bytes.


#
## Question
This is a recursive function that transverses a tree by decoding secret messages.
What problem would you run into if the tree was very deep (apart from it being slow)?
Can you rearrange it to solve this problem ?
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
If the tree is too deep, the function may cause a stack overflow due to excessive recursion depth.

We could refactor the function as:
```
void recurseDecodeSecretMessage(node* n)
{
    while (n != nullptr)
    {
        s8 tmp[MAX_MESSAGE_LENGTH];
        decodeSecretMessage(tmp, n->message, n->key);
        if (strcmp(tmp, "Go Left") == 0)
        {
            n = n->leftNode;
        }
        else
        {
            n = n->rightNode;
        }
    }
}
```


#
## Question
These are part of a pack file system (single file that contains many files).
There are many entries in each pack!

How would you go about reducing the memory use of this, and as a bonus, speed up the find?
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
The first column is a decimal offset for the symbol.
We want to know the total size of the symbols in each class.

How would you do this?

## Answer
```
struct Symbol
{
    std::string className;
    int offset;
}


Symbol parse_symbol(const std::string& data)
{
    int offset;
    std::string text;
    std::istringstream stream(data);
    stream >> offset >> text;
    std::string className = text.substr(0, text.find(':'));
    return {className, offset};
}


std::vector<Symbol> parse_symbols(const std::string& filename)
{
    std::vector<Symbol> output;

    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        output.push_back(parse_symbol(line));
    }
    std::sort(output.begin(), output.end(),
        [](const Symbol& a, const Symbol& b)
        {
            const int result = a.className.compare(b.className);
            if (result < 0)
            {
                return true;
            }
            if (result == 0)
            {
                return a.offset < b.offset;
            }
            return false;
        });
    return output;
}


std::map<std::string, int> get_size(const std::vector<Symbol>& data)
{
    std::map<std::string, int> output;

    std::string currentClass = "";
    int currentOffset;
    for (std::size_t i = 0; i < data.size(); ++i)
    {
        const Symbol& entry = data[i];
        if (currentClass != entry.className)
        {
            currentClass = entry.className;
            currentOffset = 0;
        }

        output[currentClass] += entry.offset - currentOffset;
        currentOffset = entry.offset;
    }

    return output;
}


```


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
This code is wasteful because it generates separate instances of the `BubbleSort` function for each type used, leading to code bloat and increased compilation time.
Each instantiation of the template creates a new copy of the function, which can lead to larger binary sizes if many types are used.
A generic, non-template sort can be written using `void*` and a comparison function pointer.
This avoids code bloat and works for any type:
```
void BubbleSort(void* begin, u32 num, u32 size, int (*compare)(const void*, const void*)) {
    char* ptr = static_cast<char*>(begin);
    u32 change;
    do
    {
        change = FALSE;
        for (u32 i = 0; i < num - 1; ++i)
        {
            char* a = ptr + i * size;
            char* b = ptr + (i + 1) * size;
            if (compare(a, b) > 0)
            {
                for (u32 j = 0; j < size; ++j)
                {
                    char tmp = a[j];
                    a[j] = b[j];
                    b[j] = tmp;
                }
                change = TRUE;
            }
        }
    } while (change);
}
```


#
## Question
The following class is used to store entries in a string table, containing thousands of entries.
How could the memory use be reduced?
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
```
class StringTableEntry
{
public:
	StringTableEntry();
	~StringTableEntry();

	const char* getString(const char* ptr)
	{
		return ptr + offset;
	}

	u8 getFlags(void) const
	{
		return flags;
	}

	u32 offset;
    u8 flags;
};
```

A possible solution is to store the string as an offset from a base pointer, rather than storing a pointer directly.
This reduces the size of each entry from 8 bytes (on a 64-bit system) to 4 bytes for the offset.

Assuming 8 (bit flags) or 256 flags are sufficient, then 1 byte for the flags is going to be more than enough, saving further memory.

Lastly, avoiding virtual functions can also save memory and improve performance, as virtual function tables (vtables) add overhead to each instance of the class.


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
Use C# or C++ to show the structure of an element of a sorted binary tree in which each element contains a single character.

Describe briefly what any reference point to.

## Answer
```
struct Node
{
    Node(
        char value = '\0',
        Node* parent = nullptr,
        Node* left = nullptr,
        Node* right = nullptr)
        : m_Parent(parent), m_Left(left), m_Right(right), m_Value(value)
    { }

    Node* parent; // Pointer to the parent node [optional]. Nullptr if this is the root node
    Node* left; // Pointer to the left child node, containing a character less than value
    Node* right; // Pointer to the right child node, containing a character greater than value
    char value; // Character value stored in the node
};
```


#
## Question
Use C# or C++ to implement a function that locates the element in the tree which matches a given character.

It should match this signature:
```
Node FindElementInTree(Node root, char charToFind)
```

## Answer
```
Node FindElementInTree(Node root, char charToFind)
{
    Node* current = &root;

    while (current != nullptr)
    {
        if (current->value == charToFind)
        {
            return *current; // Found the element
        }
        
        if (charToFind < current->value)
        {
            current = current->left; // Go left
        }
        else
        {
            current = current->right; // Go right
        }
    }
    return Node(); // Return an empty node if not found
}
```

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
- The root `R`.
- `A` and `B`: children of `R`.
- `C`: child of `B`.

The position and orientation of each object is represented as a 4x4 matrix transforming the local space of the object to the space of its parent.
Vectors are in homogeneous coordinates and are represented by 4-component column vectors.

What is the equation for the matrix `M` transforming points from the local space of `A` to the local space of `C`?

## Answer
The transformation to the local space of `C` is given by the matrix multiplication:
$M = C^{-1} \cdot B^{-1} \cdot A$


#
## Question
Describe geometrically the difference between applying a rigid transform to the vectors $p = [x, y, z, 1]^T$ and $q = [x, y, z, 0]^T$

## Answer
The two vectors are expressed in homogeneous coordinates.

The first one is a point in 3D space, while the second one is a direction vector.

The difference between them is that the first one is affected by both translation and rotation, while the second one only by the rotation.


#
## Question
Representing rigid transformations by 4x4 matrices will in a straightforward implementation require 16 floats of data per object.
Briefly describe a representation using as few floats as possible without loss of precision.

## Answer
A first possibility could be ommitting the bottom part of the matrix, which is always $[0 0 0 1]$.
This would reduce the size to 12 floats.

A second possibility could be using dual quaternions to represent the rotation and translation of the object.
This would reduce the size to 8 floats.

Another possibility could be using a quaternion to represent the rotation and a 3D vector to represent the translation.
This would reduce the size to 7 floats.


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
