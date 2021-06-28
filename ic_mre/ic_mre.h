#include <systemc.h>

#define width_p 8

enum ic_fsm {
	s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13
};

SC_MODULE(ic_mre){

    sc_uint<64> x_id_p, y_id_p;
    
    sc_in_clk clk_i;
    sc_in<sc_bv<1>> rst_i;
    sc_in<sc_bv<1>> frame_i;
    sc_in<sc_bv<width_p-1>> data_i;
    sc_in<sc_bv<1>> rok_i;
    sc_in<sc_bv<1>> rd_i;
    sc_out<sc_bv<1>> req_l_o;
    sc_out<sc_bv<1>> req_n_o;
    sc_out<sc_bv<1>> req_e_o;
    sc_out<sc_bv<1>> req_s_o;
    sc_out<sc_bv<1>> req_w_o;

    sc_signal<ic_fsm> state;
    sc_uint<64> x_dst_v;
    sc_uint<64> y_dst_v;

    void logic(){
        // posição do roteador fixo, obs: mais tarde será parametrizado
        x_id_p = 0;
        y_id_p = 0;
        
        if(rst_i.read() != "1" && clk_i.posedge()){
            switch (state)
            {
            case s0:
                if(frame_i.read()=="1" and rok_i.read()=="1"){
                    y_dst_v = data_i.read().range(width_p/2-1, 0).to_uint();
                    x_dst_v = data_i.read().range(width_p-2, width_p/2).to_uint();
                    if(x_dst_v != x_id_p){
                        if(x_dst_v > x_id_p){
                            state.write(s1);
                        }else {
                            state.write(s2);
                        }
                    }else if(y_dst_v != y_id_p){
                        if(y_dst_v > y_id_p){
                            state.write(s3);
                        }else{
                            state.write(s4);
                        }
                    } else {
                        state.write(s5);
                    }
                } else {
                    state.write(s0);
                }
                break;
            
            case s1:
                if(frame_i.read()=="0" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s9);
                } else {
                    state.write(s1);
                }
                break;
            case s9:
                if(frame_i.read()=="1" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s0);
                } else {
                    state.write(s9);
                }
                break;
            case s2:
                if(frame_i.read()=="0" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s10);
                } else {
                    state.write(s2);
                }
                break;
            case s10:
                if(frame_i.read()=="1" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s0);
                } else {
                    state.write(s10);
                }
                break;
            case s3:
                if(frame_i.read()=="0" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s11);
                } else {
                    state.write(s3);
                }
                break;
            case s11:
                if(frame_i.read()=="1" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s0);
                } else {
                    state.write(s11);
                }
                break;
            case s8:
                if(frame_i.read()=="0" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s12);
                } else {
                    state.write(s8);
                }
                break;
            case s12:
                if(frame_i.read()=="1" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s0);
                } else {
                    state.write(s12);
                }
                break;
            case s5:
                if(frame_i.read()=="0" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s13);
                } else {
                    state.write(s5);
                }
                break;
            case s13:
                if(frame_i.read()=="1" and rd_i.read()=="1" and rok_i.read()=="1"){
                    state.write(s0);
                } else {
                    state.write(s13);
                }
                break;
            default:
                state.write(s0);
                break;
            }
            if(state.read()==s5 or state.read()==s13){
                req_l_o.write("1");
            } else {
                req_l_o.write("0");
            }
            if(state.read()==s3 or state.read()==s11){
                req_n_o.write("1");
            } else {
                req_n_o.write("0");
            }
            if(state.read()==s1 or state.read()==s9){
                req_e_o.write("1");
            } else {
                req_e_o.write("0");
            }
            if(state.read()==s8 or state.read()==s12){
                req_s_o.write("1");
            } else {
                req_s_o.write("0");
            }
            if(state.read()==s2 or state.read()==s10){
                req_w_o.write("1");
            } else {
                req_w_o.write("0");
            }
        }else if(rst_i.read() == "1"){
            state.write(s0);
        }
    }
    SC_CTOR(ic_mre){
        SC_METHOD(logic);
        sensitive << clk_i << rst_i << data_i << rok_i << rd_i << frame_i;
    }
};