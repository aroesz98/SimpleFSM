#include <FSM.hpp>
#include <cstdlib>

FSM::State::State(void (*onEnterFunc)(), void (*onStateFunc)(), void (*onExitFunc)())
    : onEnter(onEnterFunc),
      onState(onStateFunc),
      onExit(onExitFunc)
{
}

FSM::FSM(State *initial_state)
    : mCurrentState(initial_state),
      mTransitions(nullptr),
      mInitialized(false)
{
}

FSM::~FSM()
{
    mTransitions->clear();
    delete []mTransitions;
}

void FSM::addTransition(int event, State *fromState, State *toState)
{
    if (fromState == NULL || toState == NULL)
    {
        return;
    }
    if (mTransitions == nullptr)
    {
        mTransitions = new std::vector<Transition>;
    }

    Transition transition;
    transition.event = event;
    transition.fromState = fromState;
    transition.toState = toState;
    mTransitions->push_back(transition);
}

void FSM::trigger(int event)
{
    if (mInitialized)
    {
        for(auto t : *mTransitions)
        {
            if (t.fromState == mCurrentState &&
                t.event == event)
            {
                FSM::doTransition(&t);
                return;
            }
        }
    }
}

void FSM::init()
{
    if (!mInitialized)
    {
        mInitialized = true;
        if (mCurrentState->onEnter != NULL)
        {
            mCurrentState->onEnter();
        }
    }

    if (mCurrentState->onState != NULL)
    {
        mCurrentState->onState();
    }
}

void FSM::doTransition(Transition *transition)
{
    if (transition->fromState->onExit != NULL)
    {
        transition->fromState->onExit();
    }

    if (transition->toState->onEnter != NULL)
    {
        transition->toState->onEnter();
    }

    mCurrentState = transition->toState;
}
