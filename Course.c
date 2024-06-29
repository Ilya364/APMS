#include <stdio.h>
#include <limits.h>
#include "Course.h"

#define work_timer_DELTA(work_timer) ((work_timer) * 230)
#define DELAY_DELTA(delay) ((delay) * 230)

void pneumo_engine_init(struct PneumoEngine* engine) {
    if (0 != engine) {
        engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] = 0;
        engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] = 1;
        engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;

        engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] = 0;
        engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] = 1;
        engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;

        engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] = 0;
        engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] = 1;
        engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;

        engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] = 0;
        engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] = 1;
        engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;

        engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] = 0;
        engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] = 1;
        engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;

        engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] = 0;
        engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] = 1;
        engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;

        engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] = 0;
        engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] = 1;
        engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;

        engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] = 0;
        engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] = 1;
        engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;

        engine->state = State_Init;
        engine->delay = 0;
        engine->work_timer = 0;
        engine->work_timers[State_Init] = INT_MAX;
        engine->delays[State_Init] = INT_MAX;
        engine->work_timers[State_0] = work_timer_DELTA(30);
        engine->delays[State_0] = DELAY_DELTA(78);
        engine->work_timers[State_1] = work_timer_DELTA(56);
        engine->delays[State_1] = DELAY_DELTA(60);
        engine->work_timers[State_2] = work_timer_DELTA(120);
        engine->delays[State_2] = DELAY_DELTA(45);
        engine->work_timers[State_3] = work_timer_DELTA(60);
        engine->delays[State_3] = DELAY_DELTA(60);
        engine->work_timers[State_4] = work_timer_DELTA(120);
        engine->delays[State_4] = DELAY_DELTA(45);
        engine->work_timers[State_5] = work_timer_DELTA(120);
        engine->delays[State_5] = DELAY_DELTA(60);
        engine->work_timers[State_6] = work_timer_DELTA(120);
        engine->delays[State_6] = DELAY_DELTA(78);
        engine->work_timers[State_7] = work_timer_DELTA(60);
        engine->delays[State_7] = DELAY_DELTA(60);
        engine->work_timers[State_8] = work_timer_DELTA(30);
        engine->delays[State_8] = DELAY_DELTA(78);
        engine->work_timers[State_9] = work_timer_DELTA(30);
        engine->delays[State_9] = DELAY_DELTA(45);
        engine->work_timers[State_10] = work_timer_DELTA(120);
        engine->delays[State_10] = DELAY_DELTA(78);
        engine->work_timers[State_11] = work_timer_DELTA(120);
        engine->delays[State_11] = DELAY_DELTA(70);
        engine->work_timers[State_12] = work_timer_DELTA(56);
        engine->delays[State_12] = DELAY_DELTA(78);
        engine->work_timers[State_13] = work_timer_DELTA(56);
        engine->delays[State_13] = DELAY_DELTA(70);
        engine->work_timers[State_14] = work_timer_DELTA(60);
        engine->delays[State_14] = DELAY_DELTA(78);
        engine->work_timers[State_15] = work_timer_DELTA(60);
        engine->delays[State_15] = DELAY_DELTA(60);
        engine->work_timers[State_16] = work_timer_DELTA(30);
        engine->delays[State_16] = DELAY_DELTA(45);
    }
}

#define TIMER_GE(engine) ( (engine)->work_timer > (engine)->work_timers[(engine)->state] )
#define DELAY_GE(engine) ( (engine)->delay > (engine)->delays[(engine)->state] )

bool pneumo_engine_tick(struct PneumoEngine* engine) {
    bool ret = true;
    if (0 == engine)
        return false;
    switch (engine->state) {
        case State_Init: {
            engine->state = State_0;
            engine->delay = 0;
            engine->work_timer = 0;
            break;
        }
        case State_0: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 1;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_1;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_1: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 1;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_2;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_2: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_3;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_3: {
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 1;

            if (engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_4;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_4: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 1;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_5;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_11;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_5: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_6;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_6: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 1;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_7;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_7: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_8;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_8: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 1; 

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_9;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_14;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_9: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_10;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_10: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_11;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_11: {
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 1;

            if (engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_12;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_12: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_13;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_13: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 1;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_14;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_14: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 1;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y5].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y8].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_15;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_15: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y4].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y7].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_16;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        } 
        case State_16: {
            engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
            engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 1;
            engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 1;

            if (engine->cylinders[PNEUMO_CYLINDER_Y1].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y2].input_signal[PNEUMO_CYLINDER_SIGNAL_DOWN] &&
                engine->cylinders[PNEUMO_CYLINDER_Y3].input_signal[PNEUMO_CYLINDER_SIGNAL_UP] &&
                engine->cylinders[PNEUMO_CYLINDER_Y6].input_signal[PNEUMO_CYLINDER_SIGNAL_UP]) {
                engine->work_timer = 0;
                if (DELAY_GE(engine)) {
                    engine->state = State_0;
                    engine->delay = 0;
                    engine->work_timer = 0;
                }
            }
            else if (TIMER_GE(engine)) {
                engine->state = State_FatalException;
                engine->cylinders[PNEUMO_CYLINDER_Y1].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y2].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y3].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y4].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y5].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y6].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y7].output_signal = 0;
                engine->cylinders[PNEUMO_CYLINDER_Y8].output_signal = 0;
                engine->delay = 0;
                engine->work_timer = 0;
            }
            break;
        }
        case State_FatalException: {
            ret = false;
            break;
        }
    }
    engine->work_timer++;
    engine->delay++;
    return ret;
}

void pneumo_engine_destroy(struct PneumoEngine* engine) {
    if (0 != engine) {
        //Освобождаем ресурсы, если есть
    }
}