#include "systemc.h"

#define data_width_p 8

enum fsm {
	s0, s1, s2
};

SC_MODULE(ifc_par_mre){
    sc_in_clk clk_i;
    sc_in<sc_bv<1>> rst_i, val_i, wok_i;
    sc_out<sc_bv<1>> ack_o, wr_o;
    sc_in<sc_bv<data_width_p>> data_i;
    sc_out<sc_bv<data_width_p>> data_o;
    sc_signal<fsm> state;

    void ifc_par_mre_logic(){
        if(rst_i.read() != "1" && clk_i.posedge()){
            switch(state){
                case s0:
                wr_o.write("0");
                ack_o.write("0");
                if(val_i.read() == "1" and wok_i.read() == "1"){
                    state = s1;
                } else {
                    state = s0;
                }
                break;
                case s1:
                ack_o.write("1");
                wr_o.write("1");
                if(val_i.read() == "0"){
                    state = s0;
                } else {
                    state = s2;
                }
                break;
                case s2:
                ack_o.write("1");
                wr_o.write("0");
                if(val_i.read() == "0"){
                    state = s0;
                } else {
                    state = s2;
                } 
                break;
                default:
                    wr_o.write("0");
                    ack_o.write("0");
                    state = s0;
                    break;

            }
            data_o.write(data_i.read());
        }
    }

    SC_CTOR(ifc_par_mre){
        SC_METHOD(ifc_par_mre_logic);
        sensitive << clk_i << rst_i << val_i << wok_i << data_i;
    }




};