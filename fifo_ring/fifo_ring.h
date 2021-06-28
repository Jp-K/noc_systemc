#include "systemc.h"
#include "math.h"
#include <cmath>

#define WIDTH 8
#define DEPTH 4

SC_MODULE(fifo_ring){
    sc_in_clk clk_i;
    sc_in<sc_bv<1>> rst_i, rd_i, wr_i;

    sc_out<sc_bv<1>> rok_o, wok_o;

    sc_in<sc_bv<WIDTH>> data_i;
    sc_out<sc_bv<WIDTH>> data_o;
    
    sc_signal<sc_bv<WIDTH>> fifo_r[DEPTH];
    sc_signal<sc_uint<2>> rd_ptr_r, wr_ptr_r;
    sc_signal<sc_uint<4>> n_pos_r;

    void fifo_ring_logic(){
        if(rst_i.read()=="1"){
            rd_ptr_r.write(0);
            wr_ptr_r.write(0);
            n_pos_r.write(0);
        } else if(clk_i.posedge()){
            if(wr_i.read()=="1" and n_pos_r.read() != DEPTH){
                wr_ptr_r.write(wr_ptr_r.read()+1);
                fifo_r[wr_ptr_r.read()].write(data_i.read());
                if(rd_i.read()=="1" and n_pos_r.read() != 0){
                    rd_ptr_r.write(rd_ptr_r.read()+1);
                } else {
                    n_pos_r.write(n_pos_r.read()+1);
                }
            } else if(rd_i.read()=="1" and n_pos_r.read() != 0){
                rd_ptr_r.write(rd_ptr_r.read()+1);
                n_pos_r.write(n_pos_r.read()-1);
            }
        }
        if(n_pos_r.read()!=0){
            rok_o.write("1");
        }else{
            rok_o.write("0");
        }
        if(n_pos_r.read()!=DEPTH){
            wok_o.write("1");
        }else{
            wok_o.write("0");
        }
        data_o.write(fifo_r[rd_ptr_r.read()].read());
    }


    SC_CTOR(fifo_ring){
        SC_METHOD(fifo_ring_logic);
        sensitive << clk_i << rst_i << rd_i << wr_i << data_i;
    }
};