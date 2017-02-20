
// g++ -std=c++14 rb_tree.cpp -o rb_tree

#include <cassert>

#include <iostream>
#include <string>

#include <memory>
#include <type_traits>

#include <boost/noncopyable.hpp>

#include <boost/mpl/map.hpp>



namespace algo
{
	//
	template <
		typename K,
		typename V,
		typename Cmp = std::less<K>,
		template <typename> class Alloc = std::allocator
	>
	class rb_tree: private boost::noncopyable // temporary noncopyable
	{
	private:
		//
		// Deleter for unique_ptr
		//
		template <typename Allocator>
		struct node_deleter
		{
		public:
			using allocator_type = Allocator;
			using type = typename allocator_type::value_type;
			
		public:
			node_deleter(allocator_type* alloc_ptr): alloc_ptr_(alloc_ptr) {}
			
			void operator() (type* p)
			{
				assert(alloc_ptr_);
				
				try {
					alloc_ptr_ -> destroy(p);
				} catch (...) {
					;
				}
				alloc_ptr_ -> deallocate(p, 1);
			}
			
		private:
			allocator_type* alloc_ptr_;
		};
		
		//
		// Node colors
		//	
		enum class node_color
		{
			Black = 1,
			Red = 2
		};
		
		//
		// Node structure. We can use allocator::rebind, and template parameter of template is more interesting
		//
		template <
			typename T1,
			typename T2,
			template <typename> class Allocator
		>
		class node
		{
		public:
			using t1_type = T1;
			using t2_type = T2;
			using value_type = std::pair< t1_type, t2_type >;
			
			using allocator_node_type = Allocator< node >;
			using allocator_value_type = Allocator< value_type >;
			
			using deleter_node_type = node_deleter< allocator_node_type >;
			using deleter_value_type = node_deleter< allocator_value_type >;
			
			using uptr_node_type = std::unique_ptr< node, deleter_node_type >;
			using uptr_value_type = std::unique_ptr< value_type, deleter_value_type >;
			
		public:
			node(
				allocator_node_type & node_alloc,
				allocator_value_type & value_alloc
			):
				value_(nullptr, deleter_value_type(nullptr)),
				left_(nullptr, deleter_node_type(nullptr)),
				right_(nullptr, deleter_node_type(nullptr)),
				parent_(),
				color_(node_color::Red),
				node_alloc_(node_alloc),
				value_alloc_(value_alloc)
			{
				return;
			}
			
			uptr_value_type & get_value_ref()
			{
				return value_;
			}
			
			uptr_node_type & get_left_ref()
			{
				return left_;
			}
			
			uptr_node_type & get_right_ref()
			{
				return right_;
			}
			
			node* & get_parent_ref()
			{
				return parent_;
			}
			
			node_color & get_color_ref()
			{
				return color_;
			}
			
		private:
			uptr_value_type value_;
			
			uptr_node_type left_;
			uptr_node_type right_;
			node* parent_;
			node_color color_;
			
			allocator_node_type & node_alloc_;
			allocator_value_type & value_alloc_;
		};
		
	public:
		using key_type = K;
		using mapped_type = V;
		using value_type = typename node< const key_type, mapped_type, Alloc >::value_type;
		using compare_type = Cmp;
		
	private:
		using node_type = node< const key_type, mapped_type, Alloc >;
		using allocator_node_type = typename node_type::allocator_node_type;
		using allocator_value_type = typename node_type::allocator_value_type;
		using deleter_node_type = node_deleter< allocator_node_type >;
		using uptr_node_type = std::unique_ptr< node_type, deleter_node_type >;
		
	public:
		rb_tree():
			root_(nullptr, deleter_node_type(&node_alloc_)),
			leaf_node_(nullptr, deleter_node_type(&node_alloc_))
		{
			node_type* tmp_root = node_alloc_.allocate(1);
			try {
				node_alloc_.construct(tmp_root, node_alloc_, value_alloc_);
			} catch (...) {
				node_alloc_.deallocate(tmp_root, 1);
				throw;
			}
			root_ = uptr_node_type(tmp_root, deleter_node_type(&node_alloc_));
			root_ -> get_color_ref() = node_color::Black;
		}
		
		~rb_tree()
		{
			return;
		}
		
		bool insert()
		{
			return false;
		}
		
		bool find()
		{
			return true;
		}
		
		bool erase()
		{
			return true;
		}
		
	private:
		void left_rotate()
		{
			;
		}
		
		void right_rotate()
		{
			;
		}
		
		bool is_leaf(uptr_node_type const & ref) const
		{
			return ref == nullptr;
		}
		
	private:
		uptr_node_type root_;
		uptr_node_type leaf_node_;
		allocator_node_type node_alloc_;
		allocator_value_type value_alloc_;
		compare_type cmp_;
	};
	//
}



int main (int argc, char ** argv)
{
	using namespace algo;
	using namespace boost::mpl;
	
	using type1 = map< pair<int, char> >;
	
	rb_tree<int, std::string> dat;
		
	return 0;
}







