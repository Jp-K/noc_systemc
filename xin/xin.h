#include <systemc.h>
#include "ifc_par_mre.h"
#include "../fifo_shift/fifo_shift.h"
#include "../cs/cs.h"
#include "../ic_mre/ic_mre.h"

#define data_width_p 8

SC_MODULE(xin){
    
    sc_in_clk clk_i;
    sc_in<sc_bv<1>> rst_i;
    sc_in<sc_bv<data_width_p>> data_i;
    sc_in<sc_bv<1>> val_i;
    sc_out<sc_bv<1>> ack_o;

    sc_out<sc_bv<1>> req_l_o, req_n_o, req_e_o, req_s_o, req_w_o;
    sc_in<sc_bv<4>> gnt_i;

    sc_out<sc_bv<1>> rok_o;
    sc_in<sc_bv<4>> rd_i;
    sc_out<sc_bv<data_width_p>> data_o;

    sc_signal<sc_bv<1>> rok_w, rd_w, wok_w, wr_w;
    sc_signal<sc_bv<data_width_p>> data_in_w, data_out_w;
    sc_signal<sc_bv<1>> frame_w;
    sc_signal<sc_bv<data_width_p-1>> ic_data_w;


    ifc_par_mre *ifc_par_mre0;
    fifo_shift *fifo_shift0;
    cs *cs1;
    ic_mre *ic_mre0;

    void adjust(){
        frame_w.write(data_out_w.read().get_bit(data_width_p-1));
        ic_data_w.write(data_out_w.read().range(data_width_p-2, 0));
        rok_o.write(rok_w.read());
        data_o.write(data_out_w.read());
    }



    SC_CTOR(xin){
        SC_METHOD(adjust);
        sensitive << clk_i << rst_i << data_i << val_i << gnt_i << rd_i;


        ifc_par_mre0 = new ifc_par_mre("ifc");
        fifo_shift0 = new fifo_shift("fifo");
        cs1 = new cs("cs1");
        ic_mre0 = new ic_mre("ic");

        ifc_par_mre0->clk_i(clk_i);
        ifc_par_mre0->rst_i(rst_i);
        ifc_par_mre0->data_i(data_i);
        ifc_par_mre0->val_i(val_i);
        ifc_par_mre0->ack_o(ack_o);
        ifc_par_mre0->data_o(data_in_w);
        ifc_par_mre0->wok_i(wok_w);
        ifc_par_mre0->wr_o(wr_w);

        fifo_shift0->clk_i(clk_i);
        fifo_shift0->rst_i(rst_i);
        fifo_shift0->rok_o(rok_w);
        fifo_shift0->rd_i(rd_w);
        fifo_shift0->data_o(data_out_w);
        fifo_shift0->wok_o(wok_w);
        fifo_shift0->wr_i(wr_w);
        fifo_shift0->data_i(data_in_w);

        cs1->sel_i(gnt_i);
        cs1->cmd_i(rd_i);
        cs1->cmd_o(rd_w);

        ic_mre0->clk_i(clk_i);
        ic_mre0->rst_i(rst_i);
        ic_mre0->frame_i(frame_w);
        ic_mre0->data_i(ic_data_w);
        ic_mre0->rok_i(rok_w);
        ic_mre0->rd_i(rd_w);
        ic_mre0->req_l_o(req_l_o);
        ic_mre0->req_n_o(req_n_o);
        ic_mre0->req_e_o(req_e_o);
        ic_mre0->req_s_o(req_s_o);
        ic_mre0->req_w_o(req_w_o);

    }
};