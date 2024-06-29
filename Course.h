#ifndef COURSE_PNEUMO_CTRL_H
#define COURSE_PNEUMO_CTRL_H

#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

    enum State
    {
        State_Init = 0,
        State_0, State_1, State_2,
        State_3, State_4, State_5,
        State_6, State_7, State_8,
        State_9, State_10, State_11,
        State_12, State_13, State_14,
        State_15, State_16,
        State_FatalException
    };

#define PNEUMO_CYLINDER_SIGNAL_UP     0
#define PNEUMO_CYLINDER_SIGNAL_DOWN   1
    struct PneumoCylinder
    {
        int input_signal[2];
        int output_signal;
    };

#define PNEUMO_CYLINDER_Y1 0
#define PNEUMO_CYLINDER_Y2 1
#define PNEUMO_CYLINDER_Y3 2
#define PNEUMO_CYLINDER_Y4 3
#define PNEUMO_CYLINDER_Y5 4
#define PNEUMO_CYLINDER_Y6 5
#define PNEUMO_CYLINDER_Y7 6
#define PNEUMO_CYLINDER_Y8 7

    struct PneumoEngine
    {
        enum State state;
        int work_timer;
        int delay;
        int work_timers[State_FatalException];
        int delays[State_FatalException];
        struct PneumoCylinder cylinders[8];
    };

    void pneumo_engine_init(struct PneumoEngine* engine);

    bool pneumo_engine_tick(struct PneumoEngine* engine);

    void pneumo_engine_destroy(struct PneumoEngine* engine);

#if defined(__cplusplus)
}
#endif

#endif 
