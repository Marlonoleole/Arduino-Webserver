/*
 * HashMap.h
 *
 * Created: 21/04/2019 20:05:29
 *  Author: Marlon Abeln
 */ 


#ifndef HASHMAP_H
#define HASHMAP_H

namespace Map
{
	template <class K, class V>
	struct MapEntry
	{
		K key_{};
		V value_{};
		MapEntry *next_{};
		MapEntry(K key, V value, MapEntry<K, V> *next = nullptr) : key_{key}, value_{value}, next_{next} {}
		MapEntry() : next_{nullptr} {};
		~MapEntry()
		{
			//if there is a next MapEntry, delete it!
			if (next_)
			{
				delete next_;
				next_ = nullptr;
			}
		}
	};

	template <class K, class V>
	class Hashmap
	{
		private:
		int capacity_{10};
		int length_{0};
		double load_factor_{0.75};
		MapEntry<K, V> **elements_;
		void reparent(MapEntry<K, V> *parent, MapEntry<K, V> *child);

		public:
		Hashmap() : capacity_{10}, length_{0}, load_factor_{0.75}
		{
			elements_ = new MapEntry<K, V> *[capacity_] {};
			for (int i = 0; i < capacity_; ++i)
			elements_[i] = nullptr;
		};
		~Hashmap()
		{
			//delete all the map entries
			for (int i = 0; i < capacity_; ++i)
			{
				if (elements_[i])
				{
					delete elements_[i];
				}
			}
			//delete the mapping
			delete[](elements_);
		}
		const V &add(K key, V element);
		V *get(const K key) const;
		V remove(const K key);
	};

	inline int hash_code(const int i) { return i; }
	inline int hash_code(char *i)
	{
		int code{0};
		int loop_counter{0};
		char *current = i;
		while (*current)
		{
			code += i[loop_counter] + (loop_counter * 1000);
			++current;
		}
		return code;
	}

	template <class K, class V>
	const V &Hashmap<K, V>::add(K key, V element)
	{
		const int index = hash_code(key) % capacity_;
		const MapEntry<K, V> *current_entry = elements_[index];
		if (current_entry)
		{
			while (current_entry)
			{
				if (current_entry->key_ == key)
				return current_entry->value_;
				current_entry = current_entry->next_;
			}
		}
		elements_[index] = new MapEntry<K, V>(key, element, elements_[index]);
		++length_;
		return elements_[index]->value_;
	}
	template <class K, class V>
	V *Hashmap<K, V>::get(const K key) const
	{
		const int index = hash_code(key) % capacity_;
		MapEntry<K, V> *current_entry = elements_[index];
		if (current_entry)
		{
			while (current_entry)
			{
				if (current_entry->key_ == key)
				return &(current_entry->value_);
				current_entry = current_entry->next_;
			}
		}
		return nullptr;
	}
	template <class K, class V>
	V Hashmap<K, V>::remove(const K key)
	{
		const int index = hash_code(key) % capacity_;
		MapEntry<K, V> *current_entry = elements_[index];
		if (current_entry)
		{
			if (!(current_entry->next_) && current_entry->key_ == key)
			{
				delete current_entry;
				elements_[index] = nullptr;
			}
			else if (current_entry->next_)
			{
				MapEntry<K, V> *parent = current_entry;
				current_entry = current_entry->next_;
				while (current_entry->next_ && current_entry->key_ != key)
				{
					parent = current_entry;
					current_entry = current_entry->next_;
				}
				if (current_entry->key_ == key)
				{
					V return_value = current_entry->value_;
					reparent(parent, current_entry->next_);
					--length_;
					return return_value;
				}
			}
		}
		//! A proper Return Value is needed here
		//TODO: Fix a Proper notFound Return Value;
		V returnobj{};
		return returnobj;
	}
	template <class K, class V>
	void Hashmap<K, V>::reparent(MapEntry<K, V> *parent, MapEntry<K, V> *child)
	{
		MapEntry<K, V> *last_child = parent;
		while (last_child->next_ && last_child->next_ != child)
		last_child = last_child->next_;
		last_child->next_ = nullptr;
		delete parent->next_;
		parent->next_ = child;
	}
} // namespace Map
#endif