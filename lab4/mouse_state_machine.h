#ifndef _MOUSE_STATE_MACHINE_H_
#define _MOUSE_STATE_MACHINE_H_

enum State {
    INITIAL_STATE = 0,
    GOING_UP,
    VERTEX_STATE,
    GOING_DOWN,
    FINAL_STATE,
    INVALID
};


enum Event {
    LB_PRESSED_GOING_UP = 0,
    RELEASED,
    RB_PRESSED_GOING_DOWN,
    OTHER
};

enum State run_state_machine(enum State curr_state, enum Event ev);

enum Event process_event(struct packet * pac, uint8_t tolerance);

uint16_t absolute_value(int num);



#endif

