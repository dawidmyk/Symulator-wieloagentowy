#pragma once
#include <memory>
namespace std {
	template <typename kind>
	class general_ptr {
		kind * object;
		public:
		kind & operator * () const {
			return *object;
		}
		kind * operator -> () const {
			return object;
		}
		bool isEmpty() const {
			return object == nullptr;
		}
		operator bool() const {
			return !isEmpty();
		}
		bool operator == (const general_ptr<kind> & another) const {
			return object == another.object;
		}
		bool operator != (const general_ptr<kind> & another) const {
			return ! operator == (another);
		}
		kind * get() const {
			return object;
		}
		void set(kind * object) {
			this->object = object;
		}
		
		general_ptr(): object(nullptr) {}
		general_ptr(kind * object): object(object) {}
		general_ptr(const std::unique_ptr<kind> & object): object(object.get()) {}
		general_ptr(const general_ptr<kind> & another) = default;
		general_ptr & operator = (const general_ptr<kind> & another) = default;
		general_ptr & operator = (general_ptr<kind> && another) = default;
		general_ptr & operator = (const std::unique_ptr<kind> & object) {
			this->object = object.get();
			return *this;
		}
		~general_ptr() = default;
		};
}
