
#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <algorithm>
#include <boost/foreach.hpp>

template <typename BlockType>
class EventBase
{
public:
	EventBase& operator+=(BlockType block)
	{
		blocks_.push_back(block);
		return *this;
	}
	
	EventBase& operator-=(BlockType block)
	{
		blocks_.erase(
			std::remove(blocks_.begin(), blocks_.end(), block),
			blocks_.end());
		return *this;
	}
	
protected:
	std::vector<BlockType> blocks_;
};

template <class Arg1Type = void, class Arg2Type = void, class Arg3Type = void>
struct Event : public EventBase<void(^)(Arg1Type, Arg2Type, Arg3Type)>
{
	void operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const
	{
		BOOST_FOREACH (void(^block)(Arg1Type, Arg2Type, Arg3Type), this->blocks_) {
			block(arg1, arg2, arg3);
		}
	}
};

template <class Arg1Type, class Arg2Type>
struct Event<Arg1Type, Arg2Type, void> : public EventBase<void(^)(Arg1Type, Arg2Type)>
{
	void operator()(const Arg1Type& arg1, const Arg2Type& arg2) const
	{
		BOOST_FOREACH (void(^block)(Arg1Type, Arg2Type), this->blocks_) {
			block(arg1, arg2);
		}
	}
};

template <class Arg1Type>
struct Event<Arg1Type, void, void> : public EventBase<void(^)(Arg1Type)>
{
	void operator()(Arg1Type arg1) const
	{
		BOOST_FOREACH (void(^block)(Arg1Type), this->blocks_) {
			block(arg1);
		}
	}
};

template <>
struct Event<void, void, void> : public EventBase<void(^)(void)>
{
	void operator()() const
	{
		BOOST_FOREACH (void(^block)(void), this->blocks_) {
			block();
		}
	}
};

#endif // EVENT_HPP
