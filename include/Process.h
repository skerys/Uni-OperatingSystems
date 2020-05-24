#pragma once

enum State { Blocked, BlockedStopped, Ready, ReadyStopped, Running };

class Process
{
private:
    State state;
public:
    void start();
    void stop();
    State get_state();
};