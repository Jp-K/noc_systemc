#include <systemc.h>
#include "ofc_par_mre.h"
#include "../cs/cs.h"
#include "../ds/ds.h"
#include "../oc_mre/oc_mre.h"

#define data_width_p 8

SC_MODULE(xout){

    sc_in_clk clk_i;
    sc_in<sc_bv<1>> rst_i;

    sc_out<sc_bv<8>> data_o;
    sc_out<sc_bv<1>> val_o;
    sc_in<sc_bv<1>> ack_i;

    sc_in<sc_bv<4>> req_i;
    sc_out<sc_bv<4>> gnt_o;

    sc_in<sc_bv<4>> rok_i;
    sc_out<sc_bv<1>> rd_o;
    sc_in<sc_bv<data_width_p>> data3_i, data2_i, data1_i, data0_i;

    sc_signal<sc_bv<1>> rok_w;
    sc_signal<sc_bv<4>> gnt_w;
    sc_signal<sc_bv<data_width_p>> data_w;

    ofc_par_mre *ofc_par_mre0;
    cs *cs0;
    ds *ds0;
    oc_mre *oc_mre0;


    void logic(){
        gnt_o.write(gnt_w.read());
    }


    SC_CTOR(xout){
        SC_METHOD(logic);
        sensitive << clk_i << rst_i << ack_i << req_i << rok_i << data3_i << data2_i << data1_i << data0_i;

        ofc_par_mre0 = new ofc_par_mre("ofc");
        cs0 = new cs("cs");
        ds0 = new ds("ds");
        oc_mre0 = new oc_mre("oc");

        ofc_par_mre0->clk_i(clk_i);
        ofc_par_mre0->rst_i(rst_i);
        ofc_par_mre0->data_o(data_o);
        ofc_par_mre0->val_o(val_o);
        ofc_par_mre0->ack_i(ack_i);
        ofc_par_mre0->data_i(data_w);
        ofc_par_mre0->rok_i(rok_w);
        ofc_par_mre0->rd_o(rd_o);

        cs0->sel_i(gnt_w);
        cs0->cmd_i(rok_i);
        cs0->cmd_o(rok_w);

        ds0->sel_i(gnt_w);
        ds0->data3_i(data3_i);
        ds0->data2_i(data2_i);
        ds0->data1_i(data1_i);
        ds0->data0_i(data0_i);
        ds0->out(data_w);

        oc_mre0->clk_i(clk_i);
        oc_mre0->rst_i(rst_i);
        oc_mre0->req_i(req_i);
        oc_mre0->gnt_o(gnt_w);

    }
};