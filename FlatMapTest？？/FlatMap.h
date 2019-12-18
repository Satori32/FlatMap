#pragma once
#include <utility>
#include <vector>
#include <functional>
#include <algorithm>

template<class Key, class T,class CompareT = std::less<>,class Allocater = std::allocator<std::pair<const Key,T>> >
class FlatMap {
public:
	typedef std::pair<Key, T> Item;
	typedef std::vector<Item,Allocater> Map;
	typedef Key KeyType;
	typedef T ValueType;
	typedef CompareT Compare;

	FlatMap() {}
	FlatMap(const std::initializer_list<Item>& IL) :M(IL) {}
	template<class it>
	FlatMap(it F, it E) : M(F, E) {}

	Item& at(const Key& k) {
		auto It = std::find_if(M.begin(), M.end(), [&](auto& o) {return k == o.first; });
		if (It == M.end()) throw std::out_of_range("FlatMap::at()");
		return *It;
	}
	typename Map::iterator find(const Key& k) {
		return std::find_if(M.begin(), M.end(), [&](auto& o) {return k == o.first; });
	}

	typename Map::iterator find(const Item& k) {
		return std::find_if(M.begin(), M.end(), [&](auto& o) {return k == o; });
	}

	typename Map::const_iterator find(const Key& k)const {
		return std::find_if(M.cbegin(), M.cend(), [&](const auto& o) {return k == o.first; });
	}

	typename Map::const_iterator find(const Item& k)const {
		return std::find_if(M.cbegin(), M.cend(), [&](auto& o) {return k == o; });
	}

	typename Map::iterator  erase(typename Map::const_iterator it) {
		return M.erase(it);
	}
	typename Map::iterator erase(const Key& k) {
		return M.erase(std::find_if(M.begin(), M.end(), [&](auto& o) {return k == o.first; }));
	}
	bool insert(const Item& I) {
		if (find(I.first) == M.end()) { return false; }
		M.push_back(I);
		return true;
	}
	typename Map::iterator  insert(typename Map::const_iterator Pos, const Item& I) {
		if (find(I.first) == M.end()) return  M.end();
		return M.insert(Pos, I);
	}
	bool sort() {
		std::stable_sort(M.begin(), M.end(),Compare());
		return true;
	}
	template<class F>
	bool sort(const F& Fn) {
		std::stable_sort(M.begin(), M.end(),Fn);
		return true;
	}
	bool clear() {
		M.clear();
		return true;
	}
	std::size_t size() const{
		return M.size(); 
	}
	std::size_t max_size() const{
		return M.max_size();
	}
	bool empty() {
		return M.size() == 0;
	}
	/** /
	Item& operator[](const std::size_t& Idx) {
		return M[Idx];
	}
	/**/
	T& operator[](const Key& Idx) {
		auto It = find(Idx);
		if (It != M.end()) {
			return It->second;
		}
		else {
			M.push_back({ Idx,T() });
			return M.back().second;
		}
	}
	const T& operator[](const Key& Idx)const {
		auto It = find(Idx);
		if (It != M.end()) {
			return It->second;
		}
		else {
			throw std::range_error("FlatMap::Operator []");
		}
	}
	typename Map::iterator begin() {
		return M.begin();
	}
	typename Map::iterator end() {
		return M.end();
	}
	typename Map::const_iterator begin()const  {
		return M.begin();
	}
	typename Map::const_iterator end() const {
		return M.end();
	}
	typename Map::const_iterator cbegin() const {
		return M.begin();
	}
	typename Map::const_iterator cend() const{
		return M.end();
	}
	typename Map::reverse_iterator rbegin() {
		return M.rbegin();
	}
	typename Map::reverse_iterator rend() {
		return M.rend();
	}
	typename Map::const_reverse_iterator rbegin()const {
		return M.rbegin();
	}
	typename Map::const_reverse_iterator rend() const{
		return M.rend();
	}
	typename Map::const_reverse_iterator crbegin() const{
		return M.rbegin();
	}
	typename Map::const_reverse_iterator crend() const {
		return M.rend();
	}
	bool push_back(const Item& I) {
		if (find(I.first) != M.end()) { return false; }
		M.push_back(I);
		return true;
	}
	bool pop_back() {
		M.pop_back();
		return true;
	}
protected:
	Map M;
};