#include "ifc_par_mre_2.h"
#include "ifc_par_mre_tb.h"

#define data_width_p 8

int sc_main(int argc, char* argv[]){
    ifc_par_mre ifc_par_mre0("ifc_par_mre");
    ifc_par_mre_tb tb("tb");

    sc_signal<sc_bv<data_width_p>> w_data_i, w_data_o;
    sc_clock w_clk_i;
    sc_signal<sc_bv<1>> w_rst_i, w_val_i, w_wok_i, w_ack_o, w_wr_o;
    sc_signal<sc_bv<2>> w_current_r, w_next_w;

    ifc_par_mre0.data_i(w_data_i);
    ifc_par_mre0.data_o(w_data_o);
    ifc_par_mre0.clk_i(w_clk_i);
    ifc_par_mre0.rst_i(w_rst_i);
    ifc_par_mre0.val_i(w_val_i);
    ifc_par_mre0.wok_i(w_wok_i);
    ifc_par_mre0.ack_o(w_ack_o);
    ifc_par_mre0.wr_o(w_wr_o);

    tb.data_i(w_data_i);
    tb.data_o(w_data_o);
    tb.clk_i(w_clk_i);
    tb.rst_i(w_rst_i);
    tb.val_i(w_val_i);
    tb.wok_i(w_wok_i);
    tb.ack_o(w_ack_o);
    tb.wr_o(w_wr_o);

    sc_trace_file *wf = sc_create_vcd_trace_file("ifc_par_mre");

    sc_trace(wf, w_data_i, "w_data_i");
    sc_trace(wf, w_data_o, "w_data_o");

    sc_trace(wf, w_clk_i, "w_clk_i");
    sc_trace(wf, w_rst_i, "w_rst_i");
    sc_trace(wf, w_val_i, "w_val_i");
    sc_trace(wf, w_wok_i, "w_wok_i");
    sc_trace(wf, w_ack_o, "w_ack_o");
    sc_trace(wf, w_wr_o, "w_wr_o");

    sc_start(100, SC_NS);

    sc_close_vcd_trace_file(wf);
    
    return 0;

}