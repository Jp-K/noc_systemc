
#include "systemc.h"

#define WIDTH_ds 8

SC_MODULE(ds) {
    sc_in<sc_bv<WIDTH_ds> > data3_i, data2_i, data1_i, data0_i;
    sc_in<sc_bv<4> >sel_i;
    sc_out<sc_bv<WIDTH_ds> > out;

    void ds_logic() {
        if(sel_i.read()=="1000"){
            out.write(data3_i.read());
        }else if(sel_i.read()=="0100"){
            out.write(data2_i.read());
        }else if(sel_i.read()=="0010"){
            out.write(data1_i.read());
        }else if(sel_i.read()=="0001"){
            out.write(data0_i.read());
        } else {
            out.write("0000");
        }
    }

    SC_CTOR(ds){
        SC_METHOD(ds_logic);
        sensitive << data3_i << data2_i << data0_i << sel_i;
    }
    
};