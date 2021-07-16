#include "ds.h"

#define WIDTH  4

int sc_main(int argc, char* argv[]){

    ds d("ds");

    sc_signal<sc_bv<WIDTH> >w_data3,w_data2, w_data1, w_data0, w_out, w_sel;

    d.data3_i(w_data3);
    d.data2_i(w_data2);
    d.data1_i(w_data1);
    d.data0_i(w_data0);
    d.sel_i(w_sel);
    d.out(w_out);

    sc_trace_file *wf = sc_create_vcd_trace_file("mux");

    sc_trace(wf, w_data3, "w_data3");
    sc_trace(wf, w_data2, "w_data2");
    sc_trace(wf, w_data1, "w_data1");
    sc_trace(wf, w_data0, "w_data0");
    sc_trace(wf, w_out, "out");
    sc_trace(wf, w_sel, "sel");

    w_data3.write("1000");
    w_data2.write("1100");
    w_data1.write("1110");
    w_data0.write("1111");

    w_sel.write("0001");

    sc_start(10, SC_NS);

    cout<< "resultado: " <<w_out.read()<<"\n";

    w_data3.write("1000");
    w_data2.write("1100");
    w_data1.write("1110");
    w_data0.write("1111");

    w_sel.write("0010");

    sc_start(10, SC_NS);

    cout<< "resultado: " <<w_out.read()<<"\n";

    w_data3.write("1000");
    w_data2.write("1100");
    w_data1.write("1110");
    w_data0.write("1111");

    w_sel.write("0100");

    sc_start(10, SC_NS);

    cout<< "resultado: " <<w_out.read()<<"\n";

    w_data3.write("1000");
    w_data2.write("1100");
    w_data1.write("1110");
    w_data0.write("1111");

    w_sel.write("1000");

    sc_start(10, SC_NS);

    cout<< "resultado: " <<w_out.read()<<"\n";

    w_data3.write("1000");
    w_data2.write("1100");
    w_data1.write("1110");
    w_data0.write("1111");

    w_sel.write("0000");

    sc_start(10, SC_NS);

    cout<< "resultado: " <<w_out.read()<<"\n";

    w_data3.write("1000");
    w_data2.write("1100");
    w_data1.write("1110");
    w_data0.write("1111");

    w_sel.write("1100");

    sc_start(10, SC_NS);

    cout<< "resultado: " <<w_out.read()<<"\n";

    sc_stop();

    sc_close_vcd_trace_file(wf);
    return 0;


}