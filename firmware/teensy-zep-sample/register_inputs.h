

#ifndef REGISTER_INPUTS_H
#define REGISTER_INPUTS_H 1

int registerInputTrigger(uint8_t pin, bool single_shot=false);
int deregisterInputTrigger(uint8_t pin);
void clearPinStates();

class PinState {

    public:
        
        enum {
            REGISTERED      = 1 << 0,
            SINGLE_SHOT     = 1 << 1,
            LOGIC_HIGH      = 1 << 2,
        };

        PinState();
        PinState(uint8_t state);
        PinState(const PinState& other);

        PinState& operator =(const PinState& rhs);

        uint8_t state() const;

        void setLogicLevel(int level);
        bool logicLevel() const;
        void flipLogicLevel();

    private:
        
        uint8_t m_state;
};

#endif
