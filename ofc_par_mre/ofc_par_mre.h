#include "systemc.h"

#define data_width_p 8

enum fsm {
	s0, s1, s2
};

SC_MODULE(ofc_par_mre){
    sc_in_clk clk_i;
    sc_in<sc_bv<1>> rst_i, ack_i, rok_i;
    sc_out<sc_bv<1>> val_o, rd_o;
    sc_in<sc_bv<data_width_p>> data_i;
    sc_out<sc_bv<data_width_p>> data_o;
    sc_signal<fsm> state;

    void ofc_par_mre_logic(){
        if(rst_i.read() != "1" && clk_i.posedge()){
            switch(state){
                case s0:
                    if (ack_i.read()=="0" && rok_i.read() == "1"){
                        state.write(s1);
                    } else {
                        state.write(s0);
                    }
                break;
                case s1:
                    if(ack_i.read()=="1"){
                        state.write(s2);
                    }else{
                        state.write(s1);
                    }
                break;
                case s2:
                    if(ack_i.read()=="0" && rok_i.read()=="1"){
                        state.write(s1);
                    }else {
                        state.write(s0);
                    }
                break;
                default:
                    state.write(s0);
                break;
            }
            data_o.write(data_i.read());
            if(state.read()==s1){
                val_o.write("1");
            } else {
                val_o.write("0");
            }
            if(state.read()==s2){
                rd_o.write("1");
            } else {
                rd_o.write("0");
            }
        } else if(rst_i.read() == "1"){
            state.write(s0);
        }
    }

    SC_CTOR(ofc_par_mre){
        SC_METHOD(ofc_par_mre_logic);
        sensitive << clk_i << rst_i << ack_i << rok_i << data_i;
    }




};