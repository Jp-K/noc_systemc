#ifndef CS
#define CS

#include "systemc.h"

//#define WIDTH  4

SC_MODULE(cs) {
    sc_in<sc_bv<4> > cmd_i, sel_i;
    sc_out<sc_bv<1>> cmd_o;
    void cs_logic() {
            cmd_o.write((cmd_i.read() & sel_i.read()).or_reduce());
    }

    SC_CTOR(cs){
        SC_METHOD(cs_logic);
        sensitive << cmd_i << sel_i;
    }
    
};

#endif