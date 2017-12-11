#ifndef DEQUE
#define _SECURE_SCL_DEPRECATE 0
#include <algorithm>
#include <cassert>

template<typename T>
class Deque {
	const enum { CHUNK = 15	};	// 0 and 1 are not magic numbers
	const double INCREASE_BY = 2.5;
	size_t capacity, _front, _back;
	T *storage;

	void resize() {
		assert(_front == 0 || _back == capacity);

		//Calculate new capacity, and find out where to start copying to center all the data.
		capacity = static_cast<int>(capacity * INCREASE_BY);
		int startPoint = (capacity - size()) / 2;	

		//Create bigger array on heap.
		T *newArray = new T[capacity];
		assert(newArray != nullptr);

		//copy over elements
		copy(storage + _front, storage + _back, newArray + startPoint);

		//delete old array, then move storage pointer to new array.
		delete[] storage;
		storage = newArray;

		//Update references.
		int assertSize = size();
		_back = startPoint + size();
		_front = startPoint;
		assert(assertSize == size());
	};

public:
	// (De)Constructors
	Deque() {
		capacity = CHUNK;
		storage = new T[CHUNK];
		_front = CHUNK / 2;		//Find midpoint. Integer division will truncate result - round down.
		_back = CHUNK / 2;		//Find midpoint. Integer division will truncate result - round down.
	}; // Allocate default-size array

	~Deque() {
		delete[] storage;
	}; // Delete array memory


	// Methods
	void push_front(T newVal) {
		//Check if we've filled the deque to the front already.
		if (_front == 0) resize();

		//move _front to left before inserting new element
		_front--;
		storage[_front] = newVal;
	}; // Adds new element to the front (left end)

	void push_back(T newVal) {
		//Check if we've filled the deque to the back already.
		if (_back == capacity) resize();

		//insert new element before moving _back to the right.
		storage[_back] = newVal;
		_back++;
	}; // Adds new element to the back (right end)

	T& front() {
		if (size() == 0) throw std::logic_error("");

		return storage[_front];
	}; // Returns a reference to the first used element

	T& back() {
		if (size() == 0) throw std::logic_error("");

		return storage[_back - 1];
	}; // Returns a reference to the last used element

	T& at(size_t pos) {
		if (size() == 0) throw std::logic_error("");
		else if ( (pos + _front) > _back) throw std::logic_error("");
		else if ( (pos + _front) < _front) throw std::logic_error("");
	
		return storage[_front + pos];
	}; // Return the element in position pos by reference

	void pop_front() {
		//Ignore request if deque is empty already.
		assert(size() >= 0);
		if (size() > 0) {
			_front++;

			//Set _back and _front vars to middle of deque when they point to the same location.
			if (size() == 0) {
				int midPoint = capacity / 2;
				_back = midPoint;
				_front = midPoint;
			}
		}
	}; // "Removes" first deque element (just change _front)

	void pop_back() {
		//Ignore request if deque is empty already.
		assert(size() >= 0);
		if (size() > 0) {
			_back--;

			//Set _back and _front vars to middle of deque when they point to the same location.
			if (size() == 0) {
				int midPoint = capacity / 2;
				_back = midPoint;
				_front = midPoint;
			}
		}
	}; // "Removes" last deque element (just change _back)

	size_t size() const {
		return _back - _front;
	}; // Returns the # of used items. NOTE:size_t is defined in <cstddef>

	T* begin() {
		return storage + _front;
	}; // Returns a pointer to the first element

	T* end() {
		return storage + _back;
	}; // Returns a pointer to one position past the last element
};

#endif