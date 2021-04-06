#include "cs.h"

#define WIDTH  4

int sc_main(int argc, char* argv[]){

    cs c("cs");

    sc_signal<sc_lv<WIDTH> >w_cmd_i, w_sel_i;
    sc_signal<sc_lv<1>> w_cmd_o;

    c.cmd_i(w_cmd_i);
    c.sel_i(w_sel_i);
    c.cmd_o(w_cmd_o);

    sc_trace_file *wf = sc_create_vcd_trace_file("mux");

    sc_trace(wf, w_cmd_i, "w_data3");
    sc_trace(wf, w_cmd_o, "out");
    sc_trace(wf, w_sel_i, "sel");

    w_cmd_i.write("0101");

    w_sel_i.write("1010");

    sc_start(10, SC_NS);

    cout<< "resultado(0): " <<w_cmd_o.read()<<"\n";

    w_cmd_i.write("0001");

    w_sel_i.write("1000");

    sc_start(10, SC_NS);

    cout<< "resultado(0): " <<w_cmd_o.read()<<"\n";

    w_cmd_i.write("0100");

    w_sel_i.write("0010");

    sc_start(10, SC_NS);

    cout<< "resultado(0): " <<w_cmd_o.read()<<"\n";

    w_cmd_i.write("1111");

    w_sel_i.write("1111");

    sc_start(10, SC_NS);

    cout<< "resultado(1): " <<w_cmd_o.read()<<"\n";

    w_cmd_i.write("0110");

    w_sel_i.write("0110");

    sc_start(10, SC_NS);

    cout<< "resultado(1): " <<w_cmd_o.read()<<"\n";

    w_cmd_i.write("0001");

    w_sel_i.write("1110");

    sc_start(10, SC_NS);

    cout<< "resultado(0): " <<w_cmd_o.read()<<"\n";

    sc_stop();

    sc_close_vcd_trace_file(wf);
    return 0;


}