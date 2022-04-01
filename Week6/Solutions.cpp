#include <iostream>
#include <stdexcept>

using namespace std;

class Person {
private:
	int age = 0;
	char* name;

	void copy(const Person& other) {
		age = other.age;

		//name = new char[strlen(other.name)];
		name = new char[strlen(other.name) + 1];
		strcpy(name, other.name);
	}

	void clear() {
		delete[] name;
	}

public:
	int getAge() const {
		return age;
	}

	const char* getName() const {
		return name;
	}

	void setAge(int age) {
		if (age < 0) {
			this->age = 0;
		}
		else {
			this->age = age;
		}
	}

	void setName(const char* name) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

public:
	Person() : age(0), name(nullptr) { }

	Person(int age, const char* name)
		: age(age) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	};

	Person(const Person& other) {
		copy(other);
	};

	Person& operator=(const Person& other) {
		if (this != &other) {
			clear();
			copy(other);
		}

		return *this;
	};

	Person& operator=(Person&& other) noexcept {
		if (this != &other) {
			try {
				clear();
				copy(other);
			}
			catch (std::exception& error) {
				std::cout << error.what();
			}
		}

		return *this;
	};

	~Person() {
		clear();
	};

	Person operator+(const Person& other) {
		Person result(*this);
		result += other;
		return result;
	};

	Person& operator+=(const Person& other) {
		age += other.age;
		name = new char[7];
		strcpy(name, "Merged");
		return *this;
	};

	bool operator==(const Person& other) const {
		return age == other.age && !strcmp(name, other.name);
	};

	friend bool operator==(const Person& other, Person& curr) {
		return other.age == curr.age && !strcmp(other.name, curr.name);
	};

	friend std::ostream& operator<<(std::ostream& out, const Person& person) {
		out << "Name: " << person.name << "\nAge: "
			<< person.age << "\n";

		return out;
	};

	friend std::istream& operator>>(std::istream& in, Person& person) {
		char buffer[1024];
		in.getline(buffer, 1024);

		person.name = new char[strlen(buffer) + 1];
		strcpy(person.name, buffer);

		in >> person.age;

		return in;
	};

// private
		// 	   char *data;
		//	   int capacity;
		//	   int size;
		// 
		//	   if (size >= capacity) -> resize()
		
	// copy
	// destroy
	// resize(newCapacity = 2)


// public:
	// push_back()
	// append()
		// append(char ch)
		// append(char *ch)
		// append(String &other)
		
	// 4x ctor dtor powerOfTwo -> (number & (number - 1)) == 0
	// 1000000 <- number
	// 0111111 <- number - 1
	// 0000000

	// marinovmartinn@gmail.com
	// voynski@g.fmi.uni-sofia.bg
	
	// ctor dtor ... 
	// copy operator=
	// c_str() const
	// data() NE_const
	// == != += + << >> 
};

int main()
{
	Person person(12, "user");
	Person you(person);
	you += person;
	Person me((person + (person + person)) + person);
	std::cout << me;

	return 0;
}
