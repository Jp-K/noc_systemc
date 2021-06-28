#include "ic_mre.h"

SC_MODULE(ic_mre_tb){

    sc_clock clk_w;
    sc_signal<sc_bv<1>> rst_w;
    sc_signal<sc_bv<1>> frame_w;
    sc_signal<sc_bv<width_p-1>> data_w;
    sc_signal<sc_bv<1>> rok_w;
    sc_signal<sc_bv<1>> rd_w;
    sc_signal<sc_bv<1>> req_l_o;
    sc_signal<sc_bv<1>> req_n_o;
    sc_signal<sc_bv<1>> req_e_o;
    sc_signal<sc_bv<1>> req_s_o;
    sc_signal<sc_bv<1>> req_w_o;
    ic_mre *ic_mre0;

    void logic(){
        sc_bv<width_p+1> count[4] = {"100100001", "000000010", "000000101", "100000111"};
        sc_bv<1> data;
        for(int i=0; i<4; i++){
            frame_w.write(count[i].get_bit(8));
            cout << count[i] << "\n";
            cout << count[i].get_bit(8) << "\n";
            data_w.write(count[i]);
            rok_w.write("1");
            rd_w.write("0");
            wait(1,SC_NS);
            rok_w.write("1");
            rd_w.write("1");
            wait(1, SC_NS);
        }
        wait(10,SC_NS);
        sc_stop();
    }

    void reset(){
        rst_w.write("1");
        wait(1, SC_NS);
        rst_w.write("0");
        wait(1, SC_NS);
    }

    SC_CTOR(ic_mre_tb){
        ic_mre0 = new ic_mre("tb");

        ic_mre0->clk_i(clk_w);
        ic_mre0->rst_i(rst_w);
        ic_mre0->rok_i(rok_w);
        ic_mre0->rd_i(rd_w);
        ic_mre0->data_i(data_w);
        ic_mre0->frame_i(frame_w);
        ic_mre0->req_e_o(req_e_o);
        ic_mre0->req_l_o(req_l_o);
        ic_mre0->req_s_o(req_s_o);
        ic_mre0->req_w_o(req_w_o);
        ic_mre0->req_n_o(req_n_o);

        sensitive << clk_w << rst_w << rok_w << rd_w << data_w;
        SC_THREAD(logic);
        SC_THREAD(reset);

        sc_trace_file *wf = sc_create_vcd_trace_file("ic_tb");

        sc_trace(wf, req_w_o, "req_w_o");
        sc_trace(wf, req_s_o, "req_s_o");
        sc_trace(wf, req_e_o, "req_e_o");
        sc_trace(wf, req_n_o, "req_n_o");
        sc_trace(wf, req_l_o, "req_l_o");
        sc_trace(wf, data_w, "data_i");
        sc_trace(wf, rok_w, "rok_w");
        sc_trace(wf, rd_w, "rd_i");
        sc_trace(wf, rst_w, "rst_i");
        sc_trace(wf, clk_w, "clk_i");
        sc_trace(wf, frame_w, "frame_i");
    }
};