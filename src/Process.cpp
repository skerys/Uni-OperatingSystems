#include "Process.h"

void Process::start()
{
    if(this->state == State::ReadyStopped){
		this->state = State::Ready;
	}
	else if(this->state == State::BlockedStopped){
		this->state = State::Blocked;
	}
}

void Process::stop()
{
    if(this->state == State::Ready){
		this->state = State::ReadyStopped;
	}
	else if(this->state == State::Blocked){
		this->state = State::BlockedStopped;
	}
}

State Process::getState()
{
    return this->state;
}