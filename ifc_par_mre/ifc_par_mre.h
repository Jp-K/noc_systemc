#include "systemc.h"

#define data_width_p 8

SC_MODULE(ifc_par_mre){
    sc_in_clk clk_i;
    sc_in<sc_bv<1>>rst_i, val_i, wok_i;
    sc_out<sc_bv<1>> ack_o, wr_o;
    sc_in<sc_bv<data_width_p>> data_i;
    sc_out<sc_bv<data_width_p>> data_o;
    sc_inout<sc_bv<2>> current_r, next_w;


    void ifc_par_mre_logic(){
        if(rst_i.read() == "1"){
            current_r.write("00");
        } else if(clk_i.posedge()){
            current_r.write(next_w.read());
        }
        cout << "current_r:" << current_r.read() << "\n";
        if(current_r.read() == "00"){
            if(val_i.read() == "1" and wok_i.read() == "1"){
                next_w.write("01");
            } else {
                next_w.write("00");
            }
        } else if(current_r.read() == "01"){
            if(val_i.read() == "0"){
                next_w.write("00");
            } else {
                next_w.write("10");
            }
        } else if(current_r.read() == "10"){
            if(val_i.read() == "0"){
                next_w.write("00");
            } else {
                next_w.write("10");
            } 
        } else {
            next_w.write("00");
        }
        if(current_r.read() == "01" or current_r.read() == "10"){
            ack_o.write("1");
        } else {
            ack_o.write("0");
        }

        if(current_r.read() == "01"){
            wr_o.write("1");
        } else {
            wr_o.write("0");
        }

        data_o.write(data_i.read());

    }


    SC_CTOR(ifc_par_mre){
        SC_METHOD(ifc_par_mre_logic);
        sensitive << clk_i << rst_i << val_i << wok_i << data_i;
    }

};