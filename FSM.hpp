#ifndef FSM_HPP
#define FSM_HPP

#include <cstdint>
#include <cstdbool>
#include <vector>

class FSM
{
    public:
        struct State
        {
            State(void (*onEnterFunc)(), void (*onStateFunc)(), void (*onExitFunc)());
            void (*onEnter)();
            void (*onState)();
            void (*onExit)();
        };

        FSM(State *initial_state);
        ~FSM();

        void addTransition( int event, State *fromState, State *toState);

        void trigger(int event);
        void init();

    private:
        struct Transition
        {
            int event;
            State *fromState;
            State *toState;
        };

        void doTransition(Transition *transition);

    private:
        State *mCurrentState;
        std::vector<Transition> *mTransitions = nullptr;
        bool mInitialized;
};

#endif
