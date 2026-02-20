#pragma once
#include<iostream>
#include<functional>
#include"Iterators.h"



namespace dl
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         Class Defs
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T>
	using Node = DL_Node<T>;
	template<class T>
	using NodePtr = DL_Node<T>*;

	template<class T>
	class list 
	{
		using iterator			=	DLL_Iterator<T>;
		using const_iterator	=	const_DLL_Iterator<T>;

		NodePtr<T> head;
		NodePtr<T> tail;
		size_t size;

	public:

		list() :head(nullptr), tail(nullptr), size(0)					{	}

		list(std::initializer_list<T> list);
		~list();
		list(list& copy);

		bool is_empty();
		int getsize()													{ return size; }
		
		void push_back(T data);
		void push_front(T data);
		//bool push_at(T data, int index);
		void pop_front();
		void pop_back();

		template<class... Args>
		void emplace_front(Args&&... args);
		template<class... Args>
		void emplace_back(Args&& ...args);

		bool search(T data);
		void remove(T data);

		iterator begin()	 											{ return iterator(head); }
		iterator end()													{ return iterator(nullptr); }

		const_iterator begin() const									{ return const_iterator(head); }
		const_iterator end() const										{ return const_iterator(nullptr); }

		NodePtr<T> getHeadRef()											{ if(!head){ return head;} return nullptr; }
		NodePtr<T> getTailRef()											{ if(!tail){ return tail;} return nullptr; }
		
	};


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                          Methods For SL_List
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	template<class T>
	inline list<T>::list(std::initializer_list<T> list)
	{
		for (auto& i : list)
		{
			push_back(i);
		}
	}


	template<class T>
	inline list<T>::~list()
	{
		NodePtr<T> current{ head }, next{};
		while (current != 0) {
			next = current->next;
			delete current;
			current = next;
		}
		head = nullptr;
		tail = nullptr;
	}

	template<class T>
	inline list<T>::list(list& copy)
	{
		int counter{ this->size };
		NodePtr<T> ite{ head };
		while (0 < counter)
		{
			if (ite->next == nullptr)
				break;
			copy.pushback(ite->data);
			ite = ite->next;
			counter--;
		}
	}

	template<class T>
	inline bool list<T>::is_empty()
	{
		return head == nullptr;
	}

	template<class T>
	inline void list<T>::push_back(T data)
	{
		size++;
		if (is_empty())
		{
			head = new Node<T>(data);
			tail = head;
			head->next = nullptr;
			head->prev = nullptr;
			tail = head;
			
		}
		else
		{
			NodePtr<T> temp = head;

			while (true)
			{
				if (temp->next == nullptr)
					break;
				temp = temp->next;
			}
			temp = temp->next;
			temp = new Node<T>(data);
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
	}

	template<class T>
	inline void list<T>::push_front(T data)
	{
		size++;
		if (is_empty())
		{
			head = new Node<T>(data);
			tail = head;
			head->next = nullptr;
			head->prev = nullptr;
			tail = head;
		}
		else
		{
			NodePtr<T> temp = new Node<T>(data);
			temp->next = head;
			head->prev = temp;
			head = temp;
			temp = nullptr;
		}
	}

	/*template<class T>
	inline bool list<T>::push_at(const int data, int index)
	{
		return false;
	}*/

	template<class T>
	template<class ...Args>
	inline void list<T>::emplace_front(Args && ...args)
	{
		push_front(T(std::forward<Args>(args)...));
	}

	template<class T>
	template<class ...Args>
	inline void list<T>::emplace_back(Args && ...args)
	{
		push_back(T(std::forward<Args>(args)...));
	}


	template<class T>
	inline bool list<T>::search(T data)
	{
		NodePtr<T> temp = head;
		bool found = false;
		while (temp != 0)
		{
			temp = temp->next;
			if (temp->data == data)
			{
				return true;
				break;
			}
		}
	}

	template<class T>
	inline void list<T>::remove(T data)
	{
		NodePtr<T> temp = head;
		bool found = false;
		while (temp != 0)
		{
			temp = temp->next;
			if (temp->data == data)
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				size--;
				break;
			}
		}
	}






}
