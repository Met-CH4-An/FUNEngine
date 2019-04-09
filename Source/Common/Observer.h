#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>



template <typename... Args>
class Signal {

public:

	Signal() : current_id_(0) {}

	// copy creates new signal
	Signal(Signal const& other) : current_id_(0) {}

	// connects a member function to this Signal
	template <typename T>
	int connect_member(T *inst, void (T::*func)(Args...)) {
		return connect([=](Args... args) {
			(inst->*func)(args...);
		});
	}

	// connects a const member function to this Signal
	template <typename T>
	inline int connect_member(T *inst, void (T::*func)(Args...) const) {
		return connect([=](Args... args) {
			(inst->*func)(args...);
		});
	}

	// connects a std::function to the signal. The returned
	// value can be used to disconnect the function again
	inline int connect(std::function<void(Args...)> const& slot) const {
		slots_.insert(std::make_pair(++current_id_, slot));
		return current_id_;
	}

	// disconnects a previously connected function
	inline void disconnect(int id) const {
		slots_.erase(id);
	}

	// disconnects all previously connected functions
	inline void disconnect_all() const {
		slots_.clear();
	}

	// calls all connected functions
	inline void emit(Args... p) {
		for (auto it : slots_) {
			it.second(p...);
		}
	}

	// assignment creates new Signal
	inline Signal& operator=(Signal const& other) {
		disconnect_all();
	}

private:
	mutable std::map<int, std::function<void(Args...)>> slots_;
	mutable int current_id_;
};

//enum class Event { RED, GREEN, BLUE, ORANGE, MAGENTA, CYAN };

/*class Observer; // a passible subscriber callback class

template <typename Event>
class Observed {
public:

	template <typename Observer>
	void registerObserver(const Event& event, Observer&& observer)
	{
		observers_[event].push_back(std::forward<Observer>(observer));
	}

	template <typename Observer>
	void registerObserver(Event&& event, Observer&& observer)
	{
		observers_[std::move(event)].push_back(std::forward<Observer>(observer));
	}

	void notify(const Event& event) const
	{
		FE::INPUT::EVENT_KEYBOARD a;

		try {

			for (const auto& obs : observers_.at(event)) obs(1);

		}

		catch (std::out_of_range) {


		}
	}

private:
	std::map<Event, std::vector<std::function<void(int)>>> observers_;
};*/



