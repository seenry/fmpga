#ifndef ADRS_h
#define ADRS_h


class ADSR {
public:
	ADSR(void);
	~ADSR(void);
	double process(void);
    double getOutput(void);
    int getState(void);
	void gate(int on);
    void setAttackRate(double rate);
    void setDecayRate(double rate);
    void setReleaseRate(double rate);
	void setSustainLevel(double level);
    void setTargetRatioA(double targetRatio);
    void setTargetRatioDR(double targetRatio);
    void reset(void);

    enum envState {
        env_idle = 0,
        env_attack,
        env_decay,
        env_sustain,
        env_release
    };

protected:
	int state;
	double output;
	double attackRate;
	double decayRate;
	double releaseRate;
	double attackCoef;
	double decayCoef;
	double releaseCoef;
	double sustainLevel;
    double targetRatioA;
    double targetRatioDR;
    double attackBase;
    double decayBase;
    double releaseBase;
 
    double calcCoef(double rate, double targetRatio);
};

inline double ADSR::process() {
	switch (state) {
        case env_idle:
            break;
        case env_attack:
            output = attackBase + output * attackCoef;
            if (output >= 1.0) {
                output = 1.0;
                state = env_decay;
            }
            break;
        case env_decay:
            output = decayBase + output * decayCoef;
            if (output <= sustainLevel) {
                output = sustainLevel;
                state = env_sustain;
            }
            break;
        case env_sustain:
            break;
        case env_release:
            output = releaseBase + output * releaseCoef;
            if (output <= 0.0) {
                output = 0.0;
                state = env_idle;
            }
	}
	return output;
}

inline void ADSR::gate(int gate) {
	if (gate)
		state = env_attack;
	else if (state != env_idle)
        state = env_release;
}

inline int ADSR::getState() {
    return state;
}

inline void ADSR::reset() {
    state = env_idle;
    output = 0.0;
}

inline double ADSR::getOutput() {
	return output;
}

#endif
