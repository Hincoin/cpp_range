#ifndef WHOSHUU_Range_H
#define WHOSHUU_Range_H

#include <iterator>
#include <exception>


namespace whoshuu {
	namespace detail {

		template <typename T,typename U>
		class Range {
		public:
			Range(const T& start, const T& stop, const U& step) : start_{ start }, stop_{ stop }, 
									      step_{ step } 
			{
				if (step_ == 0) {
					throw std::invalid_argument("Range step argument must not be zero");
				}
				else {
					auto difference = stop_ - start_;
					if ((difference < 0 && step_ > 0) || (difference > 0 && step_ < 0)) {
						throw std::invalid_argument("Range arguments must result in termination");
					}
				}
			}

			class iterator {
			public:
				typedef std::forward_iterator_tag iterator_category;
				typedef T value_type_T;
				typedef U value_type_U;
				typedef T& reference;
				typedef T* pointer;

				iterator(value_type_T value, value_type_U step) : step_{ step }, value_{ value } {}
				iterator operator++() { value_ += step_; return *this; }
				reference operator*() { return value_; }
				const pointer operator->() { return &value_; }
				bool operator==(const iterator& rhs) { return value_ >= rhs.value_; }
				bool operator!=(const iterator& rhs) { return value_ < rhs.value_; }

			private:
				const U step_;
				value_type_T value_;
			};

			iterator begin() const {
				return iterator(start_, step_);
			}

			iterator end() const {
				return iterator(stop_, step_);
			}

		private:
			const T start_;
			const T stop_;
			const U step_;
		};

	} // namespace detail

	template <typename T>
	detail::Range<T,T> range(const T& stop) {
		return detail::Range<T,T>(T{ 0 }, stop, T{ 1 });
	}

	template <typename T>
	detail::Range<T,T> range(const T& start, const T& stop) {
		return detail::Range<T,T>(start, stop, T{ 1 });
	}

	template <typename T,typename U>
	detail::Range<T,U> range(const T& start, const T& stop, const U& step) {
		return detail::Range<T,U>(start, stop, step);
	}

} // namespace whoshuu

#endif /* WHOSHUU_Range_H */
