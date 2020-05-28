#include "../include/ProcessClass.h"

void Process::start()
{
    if (state == State::ReadyStopped)
    {
		state = State::Ready;
	}
	else if (state == State::BlockedStopped)
    {
	    state = State::Blocked;
	}
}

void Process::stop()
{
    if (state == State::Ready)
    {
		state = State::ReadyStopped;
	}
	else if (state == State::Blocked)
    {
		state = State::BlockedStopped;
	}
}

State Process::get_state()
{
    return this->state;
}

void Process::set_state(State newState)
{
	state = newState;
}

int Process::get_priority()
{
	return priority;
}