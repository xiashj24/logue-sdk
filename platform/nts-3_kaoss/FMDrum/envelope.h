namespace env {

class ad  {
public:
    enum State {
        IDLE, ATTACK, DECAY
    };

    float getLevel() {
        return current_level;
    }

    ad(float samplerate, float attackTime, float decayTime) : 
        state(IDLE), 
        Fs(samplerate),
        attack_time(attackTime),
        decay_time(decayTime),
        current_level(0.f)
        {}

    // update should be called once for every sample
    void update() {
        float dt = 1.f / Fs;

        switch (state)
        {
        case IDLE:
            current_level = 0.f;
            break;
        case ATTACK:
            current_level += dt/attack_time;
            if (current_level >= 1.f) {
                    current_level = 1.f;
                    state = DECAY;
                }
            break;
        case DECAY:
            current_level -= dt/decay_time;
            if (current_level <= 0.f) {
                    current_level = 0.f;
                    state = IDLE;
                }
            break;
        default:
            // impossible branch
            break;
        }

    }

    void setDecayTime(float decayTime) {
        decay_time = decayTime;
    }

    void setGate(bool on) {
        if (on) {
            state = ATTACK;
        }
        else {
            state = IDLE;
        }
    }

private:
    State state;
    const float Fs;
    float attack_time;
    float decay_time;
    float current_level;
};

}