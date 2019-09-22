#include <lcom/lcf.h>

#include "mouse_state_machine.h"
#include "mouse.h"
#include "mouse_macros.h"



enum State run_state_machine(enum State curr_state, enum Event ev) {
    switch (curr_state) {
        case INITIAL_STATE: 
            if (ev == LB_PRESSED_GOING_UP) {
                return GOING_UP;
                break;
            }
            else {
                return INITIAL_STATE;
                break;
            }

        case GOING_UP: 
            if(ev == RELEASED) {
                return VERTEX_STATE;
                break;
            }
            else if (ev == LB_PRESSED_GOING_UP) {
                return GOING_UP;
                break;
            }
            else {
                return INITIAL_STATE;
                break;
            }

        case VERTEX_STATE: 
            if (ev == RB_PRESSED_GOING_DOWN) {
                return GOING_DOWN;
                break;
            }
            else if (ev == RELEASED) {
                return VERTEX_STATE;
                break;
            }
            else {
                return INITIAL_STATE;
                break;
            }

        case GOING_DOWN: 
            if (ev == RELEASED) {
                return FINAL_STATE;
                break;
            }
            else if (ev == RB_PRESSED_GOING_DOWN) {
                return GOING_DOWN;
                break;
            }
            else {
                return INITIAL_STATE;
                break;
            }

        case FINAL_STATE:
            return INITIAL_STATE;
            break;

        default: 
            return INVALID;
            break;
    }
}



enum Event process_event(struct packet * pac, uint8_t tolerance) {

    if (pac->lb && !pac->mb && !pac->rb && pac->delta_y >= pac->delta_x && (pac->delta_x > 0 || (absolute_value(pac->delta_x) < tolerance && absolute_value(pac->delta_y) < tolerance)))  {
        return LB_PRESSED_GOING_UP;
    }
    else if(!pac->lb && !pac->mb && pac->rb && -pac->delta_y >= pac->delta_x && (pac->delta_x > 0 || (absolute_value(pac->delta_x) < tolerance && absolute_value(pac->delta_y) < tolerance))  ) {
        return RB_PRESSED_GOING_DOWN;
    }
    else if(!pac->lb && !pac->mb && !pac->rb && absolute_value(pac->delta_x) <= tolerance && absolute_value(pac->delta_y) <= tolerance) {
        return RELEASED;
    }
    else {
        return OTHER;
    }
}

uint16_t absolute_value(int num) {
    if (num < 0) {
        return -num;
    }
    else {
        return num;
    }
}

