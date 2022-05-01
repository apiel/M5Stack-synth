#ifndef ZIC_SEQ_PATTERN_H_
#define ZIC_SEQ_PATTERN_H_

#define MAX_STEPS_IN_PATTERN 64
#define PATTERN_NAME_SIZE 15
#define SLIDE 1
#define END 1

typedef uint8_t Pat[MAX_STEPS_IN_PATTERN][2];

class Zic_Seq_Step
{
public:
    uint8_t note = 0;
    uint8_t velocity = 127;
    bool slide = false;

    Zic_Seq_Step() {}

    Zic_Seq_Step(uint8_t _note, bool _slide)
    {
        note = _note;
        slide = _slide;
    }

    void reset()
    {
        note = 0;
        velocity = 127;
        slide = false;
    }

    void set(Zic_Seq_Step *step)
    {
        set(step->note, step->velocity, step->slide);
    }

    void set(uint8_t _note)
    {
        note = _note;
    }

    void set(uint8_t _note, uint8_t _velocity)
    {
        velocity = _velocity;
        set(_note);
    }

    void set(uint8_t _note, bool _slide)
    {
        slide = _slide;
        set(_note);
    }

    void set(uint8_t _note, uint8_t _velocity, bool _slide)
    {
        slide = _slide;
        set(_note, _velocity);
    }
};

class Zic_Seq_Pattern
{
public:
    uint8_t stepCount = MAX_STEPS_IN_PATTERN;
    Zic_Seq_Step steps[MAX_STEPS_IN_PATTERN];

    Zic_Seq_Pattern(Pat _steps)
    {
        for (uint8_t pos = 0; pos < MAX_STEPS_IN_PATTERN; pos++)
        {
            if (_steps[pos][0] == END)
            {
                stepCount = pos;
                break;
            }
            steps[pos].set(_steps[pos][0], _steps[pos][1] == 1);
        }
    }

    // for testing
    void print()
    {
        for (uint8_t x = 0; x < stepCount; x++)
        {
            Serial.print("[");
            Serial.print(x);
            Serial.print(", ");
            Serial.print(steps[x].note);
            Serial.print(", ");
            Serial.print(steps[x].slide);
            Serial.print("],");
            if (x % 8 == 7)
            {
                Serial.println("");
            }
        }
        Serial.println("\n");
    }
};

#endif
