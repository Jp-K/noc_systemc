#include <systemc.h>
#include "../xin/xin.h"
#include "../xout/xout.h"
#include "../xbar/xbar.h"

#define link_width_p 8

template<int x_id_p, int y_id_p>
struct router: sc_module{

    sc_in_clk clk_i;
    sc_in<sc_bv<1>> rst_i;

    sc_in<sc_bv<link_width_p>> l_in_data_i;
    sc_in<sc_bv<1>> l_in_val_i;
    sc_out<sc_bv<1>> l_in_ack_o;
    sc_out<sc_bv<link_width_p>> l_out_data_o;
    sc_out<sc_bv<1>> l_out_val_o;
    sc_in<sc_bv<1>> l_out_ack_i;

    sc_in<sc_bv<link_width_p>> n_in_data_i;
    sc_in<sc_bv<1>> n_in_val_i;
    sc_out<sc_bv<1>> n_in_ack_o;
    sc_out<sc_bv<link_width_p>> n_out_data_o;
    sc_out<sc_bv<1>> n_out_val_o;
    sc_in<sc_bv<1>> n_out_ack_i;

    sc_in<sc_bv<link_width_p>> e_in_data_i;
    sc_in<sc_bv<1>> e_in_val_i;
    sc_out<sc_bv<1>> e_in_ack_o;
    sc_out<sc_bv<link_width_p>> e_out_data_o;
    sc_out<sc_bv<1>> e_out_val_o;
    sc_in<sc_bv<1>> e_out_ack_i;

    sc_in<sc_bv<link_width_p>> s_in_data_i;
    sc_in<sc_bv<1>> s_in_val_i;
    sc_out<sc_bv<1>> s_in_ack_o;
    sc_out<sc_bv<link_width_p>> s_out_data_o;
    sc_out<sc_bv<1>> s_out_val_o;
    sc_in<sc_bv<1>> s_out_ack_i;

    sc_in<sc_bv<link_width_p>> w_in_data_i;
    sc_in<sc_bv<1>> w_in_val_i;
    sc_out<sc_bv<1>> w_in_ack_o;
    sc_out<sc_bv<link_width_p>> w_out_data_o;
    sc_out<sc_bv<1>> w_out_val_o;
    sc_in<sc_bv<1>> w_out_ack_i;

    sc_signal<sc_bv<1>> openl, openn, opene, opens, openw;

    sc_signal<sc_bv<1>> l_req_n_xin_w, l_req_e_xin_w, l_req_s_xin_w, l_req_w_xin_w, l_gnt_n_xin_w, l_gnt_e_xin_w, l_gnt_s_xin_w, l_gnt_w_xin_w, l_req_n_xout_w, l_req_e_xout_w, l_req_s_xout_w, l_req_w_xout_w, l_gnt_n_xout_w, l_gnt_e_xout_w, l_gnt_s_xout_w, l_gnt_w_xout_w, l_rok_w, l_rd_w;
    sc_signal<sc_bv<4>> gnt_w_l_i, rd_w_l_i, gnt_w_l_o, rok_w_l_o, req_w_l_o;
    sc_bv<4> gnt_ww_l_i, rd_ww_l_i, gnt_ww_l_o, rok_ww_l_o, req_ww_l_o;
    sc_signal<sc_bv<1>> n_req_l_xin_w, n_req_e_xin_w, n_req_s_xin_w, n_req_w_xin_w, n_gnt_l_xin_w, n_gnt_e_xin_w, n_gnt_s_xin_w, n_gnt_w_xin_w, n_req_l_xout_w, n_req_e_xout_w, n_req_s_xout_w, n_req_w_xout_w, n_gnt_l_xout_w, n_gnt_e_xout_w, n_gnt_s_xout_w, n_gnt_w_xout_w, n_rok_w, n_rd_w;
    sc_signal<sc_bv<4>> gnt_w_n_i, rd_w_n_i, gnt_w_n_o, rok_w_n_o, req_w_n_o;
    sc_bv<4> gnt_ww_n_i, rd_ww_n_i, gnt_ww_n_o, rok_ww_n_o, req_ww_n_o;
    sc_signal<sc_bv<1>> e_req_l_xin_w, e_req_n_xin_w, e_req_s_xin_w, e_req_w_xin_w, e_gnt_l_xin_w, e_gnt_n_xin_w, e_gnt_s_xin_w, e_gnt_w_xin_w, e_req_l_xout_w, e_req_n_xout_w, e_req_s_xout_w, e_req_w_xout_w, e_gnt_l_xout_w, e_gnt_n_xout_w, e_gnt_s_xout_w, e_gnt_w_xout_w, e_rok_w, e_rd_w;
    sc_signal<sc_bv<4>> gnt_w_e_i, rd_w_e_i, gnt_w_e_o, rok_w_e_o, req_w_e_o;
    sc_bv<4> gnt_ww_e_i, rd_ww_e_i, gnt_ww_e_o, rok_ww_e_o, req_ww_e_o;
    sc_signal<sc_bv<1>> s_req_l_xin_w, s_req_n_xin_w, s_req_e_xin_w, s_req_w_xin_w, s_gnt_l_xin_w, s_gnt_n_xin_w, s_gnt_e_xin_w, s_gnt_w_xin_w, s_req_l_xout_w, s_req_n_xout_w, s_req_e_xout_w, s_req_w_xout_w, s_gnt_l_xout_w, s_gnt_n_xout_w, s_gnt_e_xout_w, s_gnt_w_xout_w, s_rok_w, s_rd_w;
    sc_signal<sc_bv<4>> gnt_w_s_i, rd_w_s_i, gnt_w_s_o, rok_w_s_o, req_w_s_o;
    sc_bv<4> gnt_ww_s_i, rd_ww_s_i, gnt_ww_s_o, rok_ww_s_o, req_ww_s_o;
    sc_signal<sc_bv<1>> w_req_l_xin_w, w_req_n_xin_w, w_req_e_xin_w, w_req_s_xin_w, w_gnt_l_xin_w, w_gnt_n_xin_w, w_gnt_e_xin_w, w_gnt_s_xin_w, w_req_l_xout_w, w_req_n_xout_w, w_req_e_xout_w, w_req_s_xout_w, w_gnt_l_xout_w, w_gnt_n_xout_w, w_gnt_e_xout_w, w_gnt_s_xout_w, w_rok_w, w_rd_w;
    sc_signal<sc_bv<4>> gnt_w_w_i, rd_w_w_i, gnt_w_w_o, rok_w_w_o, req_w_w_o;
    sc_bv<4> gnt_ww_w_i, rd_ww_w_i, gnt_ww_w_o, rok_ww_w_o, req_ww_w_o;

    sc_signal<sc_bv<link_width_p>> l_data_w, n_data_w, e_data_w, s_data_w, w_data_w;

    xin<x_id_p, y_id_p> *lxin0;
    xout *lxout0;
    xin<x_id_p, y_id_p> *nxin0;
    xout *nxout0;
    xin<x_id_p, y_id_p> *exin0;
    xout *exout0;
    xin<x_id_p, y_id_p> *sxin0;
    xout *sxout0;
    xin<x_id_p, y_id_p> *wxin0;
    xout *wxout0;


    xbar *xbar0;

    void connections(){
        //entradas
        
        gnt_ww_l_i[3] = n_gnt_l_xin_w.read().get_bit(0);
        gnt_ww_l_i[2] = e_gnt_l_xin_w.read().get_bit(0);
        gnt_ww_l_i[1] = s_gnt_l_xin_w.read().get_bit(0);
        gnt_ww_l_i[0] = w_gnt_l_xin_w.read().get_bit(0);
        gnt_w_l_i.write(gnt_ww_l_i);

        rd_ww_l_i[3] = n_rd_w.read().get_bit(0);
        rd_ww_l_i[2] = e_rd_w.read().get_bit(0);
        rd_ww_l_i[1] = s_rd_w.read().get_bit(0);
        rd_ww_l_i[0] = w_rd_w.read().get_bit(0);
        rd_w_l_i.write(rd_ww_l_i);

        gnt_ww_n_i[3] = l_gnt_n_xin_w.read().get_bit(0);
        gnt_ww_n_i[2] = e_gnt_n_xin_w.read().get_bit(0);
        gnt_ww_n_i[1] = s_gnt_n_xin_w.read().get_bit(0);
        gnt_ww_n_i[0] = w_gnt_n_xin_w.read().get_bit(0);
        gnt_w_n_i.write(gnt_ww_n_i);

        rd_ww_n_i[3] = l_rd_w.read().get_bit(0);
        rd_ww_n_i[2] = e_rd_w.read().get_bit(0);
        rd_ww_n_i[1] = s_rd_w.read().get_bit(0);
        rd_ww_n_i[0] = w_rd_w.read().get_bit(0);
        rd_w_n_i.write(rd_ww_n_i);

        gnt_ww_e_i[3] = l_gnt_e_xin_w.read().get_bit(0);
        gnt_ww_e_i[2] = n_gnt_e_xin_w.read().get_bit(0);
        gnt_ww_e_i[1] = s_gnt_e_xin_w.read().get_bit(0);
        gnt_ww_e_i[0] = w_gnt_e_xin_w.read().get_bit(0);
        gnt_w_e_i.write(gnt_ww_e_i);

        rd_ww_e_i[3] = l_rd_w.read().get_bit(0);
        rd_ww_e_i[2] = n_rd_w.read().get_bit(0);
        rd_ww_e_i[1] = s_rd_w.read().get_bit(0);
        rd_ww_e_i[0] = w_rd_w.read().get_bit(0);
        rd_w_e_i.write(rd_ww_e_i);

        gnt_ww_s_i[3] = l_gnt_s_xin_w.read().get_bit(0);
        gnt_ww_s_i[2] = n_gnt_s_xin_w.read().get_bit(0);
        gnt_ww_s_i[1] = e_gnt_s_xin_w.read().get_bit(0);
        gnt_ww_s_i[0] = w_gnt_s_xin_w.read().get_bit(0);
        gnt_w_s_i.write(gnt_ww_s_i);

        rd_ww_s_i[3] = l_rd_w.read().get_bit(0);
        rd_ww_s_i[2] = n_rd_w.read().get_bit(0);
        rd_ww_s_i[1] = e_rd_w.read().get_bit(0);
        rd_ww_s_i[0] = w_rd_w.read().get_bit(0);
        rd_w_s_i.write(rd_ww_s_i);

        gnt_ww_w_i[3] = l_gnt_w_xin_w.read().get_bit(0);
        gnt_ww_w_i[2] = n_gnt_w_xin_w.read().get_bit(0);
        gnt_ww_w_i[1] = e_gnt_w_xin_w.read().get_bit(0);
        gnt_ww_w_i[0] = s_gnt_w_xin_w.read().get_bit(0);
        gnt_w_w_i.write(gnt_ww_w_i);

        rd_ww_w_i[3] = l_rd_w.read().get_bit(0);
        rd_ww_w_i[2] = n_rd_w.read().get_bit(0);
        rd_ww_w_i[1] = e_rd_w.read().get_bit(0);
        rd_ww_w_i[0] = s_rd_w.read().get_bit(0);
        rd_w_w_i.write(rd_ww_w_i);

        //saidas

        l_gnt_n_xout_w.write(gnt_w_l_o.read().get_bit(3));
        l_gnt_e_xout_w.write(gnt_w_l_o.read().get_bit(2));
        l_gnt_s_xout_w.write(gnt_w_l_o.read().get_bit(1));
        l_gnt_w_xout_w.write(gnt_w_l_o.read().get_bit(0));

        rok_ww_l_o[3] = n_rok_w.read().get_bit(0);
        rok_ww_l_o[2] = e_rok_w.read().get_bit(0);
        rok_ww_l_o[1] = s_rok_w.read().get_bit(0);
        rok_ww_l_o[0] = w_rok_w.read().get_bit(0);
        rok_w_l_o.write(rok_ww_l_o);

        req_ww_l_o[3] = n_req_l_xout_w.read().get_bit(0);
        req_ww_l_o[2] = e_req_l_xout_w.read().get_bit(0);
        req_ww_l_o[1] = s_req_l_xout_w.read().get_bit(0);
        req_ww_l_o[0] = w_req_l_xout_w.read().get_bit(0);
        req_w_l_o.write(req_ww_l_o);

        n_gnt_l_xout_w.write(gnt_w_n_o.read().get_bit(3));
        n_gnt_e_xout_w.write(gnt_w_n_o.read().get_bit(2));
        n_gnt_s_xout_w.write(gnt_w_n_o.read().get_bit(1));
        n_gnt_w_xout_w.write(gnt_w_n_o.read().get_bit(0));

        rok_ww_n_o[3] = l_rok_w.read().get_bit(0);
        rok_ww_n_o[2] = e_rok_w.read().get_bit(0);
        rok_ww_n_o[1] = s_rok_w.read().get_bit(0);
        rok_ww_n_o[0] = w_rok_w.read().get_bit(0);
        rok_w_n_o.write(rok_ww_n_o);

        req_ww_n_o[3] = l_req_n_xout_w.read().get_bit(0);
        req_ww_n_o[2] = e_req_n_xout_w.read().get_bit(0);
        req_ww_n_o[1] = s_req_n_xout_w.read().get_bit(0);
        req_ww_n_o[0] = w_req_n_xout_w.read().get_bit(0);
        req_w_n_o.write(req_ww_n_o);

        e_gnt_l_xout_w.write(gnt_w_e_o.read().get_bit(3));
        e_gnt_n_xout_w.write(gnt_w_e_o.read().get_bit(2));
        e_gnt_s_xout_w.write(gnt_w_e_o.read().get_bit(1));
        e_gnt_w_xout_w.write(gnt_w_e_o.read().get_bit(0));

        rok_ww_e_o[3] = l_rok_w.read().get_bit(0);
        rok_ww_e_o[2] = n_rok_w.read().get_bit(0);
        rok_ww_e_o[1] = s_rok_w.read().get_bit(0);
        rok_ww_e_o[0] = w_rok_w.read().get_bit(0);
        rok_w_e_o.write(rok_ww_e_o);

        req_ww_e_o[3] = l_req_e_xout_w.read().get_bit(0);
        req_ww_e_o[2] = n_req_e_xout_w.read().get_bit(0);
        req_ww_e_o[1] = s_req_e_xout_w.read().get_bit(0);
        req_ww_e_o[0] = w_req_e_xout_w.read().get_bit(0);
        req_w_e_o.write(req_ww_e_o);
        
        s_gnt_l_xout_w.write(gnt_w_s_o.read().get_bit(3));
        s_gnt_n_xout_w.write(gnt_w_s_o.read().get_bit(2));
        s_gnt_e_xout_w.write(gnt_w_s_o.read().get_bit(1));
        s_gnt_w_xout_w.write(gnt_w_s_o.read().get_bit(0));

        rok_ww_s_o[3] = l_rok_w.read().get_bit(0);
        rok_ww_s_o[2] = n_rok_w.read().get_bit(0);
        rok_ww_s_o[1] = e_rok_w.read().get_bit(0);
        rok_ww_s_o[0] = w_rok_w.read().get_bit(0);
        rok_w_s_o.write(rok_ww_s_o);

        req_ww_s_o[3] = l_req_s_xout_w.read().get_bit(0);
        req_ww_s_o[2] = n_req_s_xout_w.read().get_bit(0);
        req_ww_s_o[1] = e_req_s_xout_w.read().get_bit(0);
        req_ww_s_o[0] = w_req_s_xout_w.read().get_bit(0);
        req_w_s_o.write(req_ww_s_o);

        w_gnt_l_xout_w.write(gnt_w_w_o.read().get_bit(3));
        w_gnt_n_xout_w.write(gnt_w_w_o.read().get_bit(2));
        w_gnt_e_xout_w.write(gnt_w_w_o.read().get_bit(1));
        w_gnt_s_xout_w.write(gnt_w_w_o.read().get_bit(0));

        rok_ww_w_o[3] = l_rok_w.read().get_bit(0);
        rok_ww_w_o[2] = n_rok_w.read().get_bit(0);
        rok_ww_w_o[1] = e_rok_w.read().get_bit(0);
        rok_ww_w_o[0] = s_rok_w.read().get_bit(0);
        rok_w_w_o.write(rok_ww_w_o);

        req_ww_w_o[3] = l_req_w_xout_w.read().get_bit(0);
        req_ww_w_o[2] = n_req_w_xout_w.read().get_bit(0);
        req_ww_w_o[1] = e_req_w_xout_w.read().get_bit(0);
        req_ww_w_o[0] = s_req_w_xout_w.read().get_bit(0);
        req_w_w_o.write(req_ww_w_o);

    }



    SC_CTOR(router){
        SC_METHOD(connections);
        sensitive << clk_i << rst_i;
        lxin0 = new xin<x_id_p, y_id_p>("lxin");
        nxin0 = new xin<x_id_p, y_id_p>("nxin");
        exin0 = new xin<x_id_p, y_id_p>("exin");
        sxin0 = new xin<x_id_p, y_id_p>("sxin");
        wxin0 = new xin<x_id_p, y_id_p>("wxin");
        lxout0 = new xout("lxout");
        nxout0 = new xout("nxout");
        exout0 = new xout("exout");
        sxout0 = new xout("sxout");
        wxout0 = new xout("wxout");
        xbar0 = new xbar("xbar");

        lxin0->clk_i(clk_i);
        lxin0->rst_i(rst_i);
        lxin0->data_i(l_in_data_i);
        lxin0->val_i(l_in_val_i);
        lxin0->ack_o(l_in_ack_o);
        lxin0->req_l_o(openl);
        lxin0->req_n_o(l_req_n_xin_w);
        lxin0->req_e_o(l_req_e_xin_w);
        lxin0->req_s_o(l_req_s_xin_w);
        lxin0->req_w_o(l_req_w_xin_w);
        lxin0->gnt_i(gnt_w_l_i);
        lxin0->rok_o(l_rok_w);
        lxin0->rd_i(rd_w_l_i);
        lxin0->data_o(l_data_w);

        nxin0->clk_i(clk_i);
        nxin0->rst_i(rst_i);
        nxin0->data_i(n_in_data_i);
        nxin0->val_i(n_in_val_i);
        nxin0->ack_o(n_in_ack_o);
        nxin0->req_l_o(n_req_l_xin_w);
        nxin0->req_n_o(openn);
        nxin0->req_e_o(n_req_e_xin_w);
        nxin0->req_s_o(n_req_s_xin_w);
        nxin0->req_w_o(n_req_w_xin_w);
        nxin0->gnt_i(gnt_w_n_i);
        nxin0->rok_o(n_rok_w);
        nxin0->rd_i(rd_w_n_i);
        nxin0->data_o(n_data_w);

        exin0->clk_i(clk_i);
        exin0->rst_i(rst_i);
        exin0->data_i(e_in_data_i);
        exin0->val_i(e_in_val_i);
        exin0->ack_o(e_in_ack_o);
        exin0->req_l_o(e_req_l_xin_w);
        exin0->req_n_o(e_req_n_xin_w);
        exin0->req_e_o(opene);
        exin0->req_s_o(e_req_s_xin_w);
        exin0->req_w_o(e_req_w_xin_w);
        exin0->gnt_i(gnt_w_e_i);
        exin0->rok_o(e_rok_w);
        exin0->rd_i(rd_w_e_i);
        exin0->data_o(e_data_w);

        sxin0->clk_i(clk_i);
        sxin0->rst_i(rst_i);
        sxin0->data_i(s_in_data_i);
        sxin0->val_i(s_in_val_i);
        sxin0->ack_o(s_in_ack_o);
        sxin0->req_l_o(s_req_l_xin_w);
        sxin0->req_n_o(s_req_n_xin_w);
        sxin0->req_e_o(s_req_e_xin_w);
        sxin0->req_s_o(opens);
        sxin0->req_w_o(s_req_w_xin_w);
        sxin0->gnt_i(gnt_w_s_i);
        sxin0->rok_o(s_rok_w);
        sxin0->rd_i(rd_w_s_i);
        sxin0->data_o(s_data_w);

        wxin0->clk_i(clk_i);
        wxin0->rst_i(rst_i);
        wxin0->data_i(w_in_data_i);
        wxin0->val_i(w_in_val_i);
        wxin0->ack_o(w_in_ack_o);
        wxin0->req_l_o(w_req_l_xin_w);
        wxin0->req_n_o(w_req_n_xin_w);
        wxin0->req_e_o(w_req_e_xin_w);
        wxin0->req_s_o(w_req_s_xin_w);
        wxin0->req_w_o(openw);
        wxin0->gnt_i(gnt_w_w_i);
        wxin0->rok_o(w_rok_w);
        wxin0->rd_i(rd_w_w_i);
        wxin0->data_o(w_data_w);

        lxout0->clk_i(clk_i);
        lxout0->rst_i(rst_i);
        lxout0->data_o(l_out_data_o);
        lxout0->val_o(l_out_val_o);
        lxout0->ack_i(l_out_ack_i);
        lxout0->req_i(req_w_l_o);
        lxout0->gnt_o(gnt_w_l_o);
        lxout0->rok_i(rok_w_l_o);
        lxout0->rd_o(l_rd_w);
        lxout0->data3_i(n_data_w);
        lxout0->data2_i(e_data_w);
        lxout0->data1_i(s_data_w);
        lxout0->data0_i(w_data_w);

        nxout0->clk_i(clk_i);
        nxout0->rst_i(rst_i);
        nxout0->data_o(n_out_data_o);
        nxout0->val_o(n_out_val_o);
        nxout0->ack_i(n_out_ack_i);
        nxout0->req_i(req_w_n_o);
        nxout0->gnt_o(gnt_w_n_o);
        nxout0->rok_i(rok_w_n_o);
        nxout0->rd_o(n_rd_w);
        nxout0->data3_i(l_data_w);
        nxout0->data2_i(e_data_w);
        nxout0->data1_i(s_data_w);
        nxout0->data0_i(w_data_w);

        exout0->clk_i(clk_i);
        exout0->rst_i(rst_i);
        exout0->data_o(e_out_data_o);
        exout0->val_o(e_out_val_o);
        exout0->ack_i(e_out_ack_i);
        exout0->req_i(req_w_e_o);
        exout0->gnt_o(gnt_w_e_o);
        exout0->rok_i(rok_w_e_o);
        exout0->rd_o(e_rd_w);
        exout0->data3_i(l_data_w);
        exout0->data2_i(n_data_w);
        exout0->data1_i(s_data_w);
        exout0->data0_i(w_data_w);

        sxout0->clk_i(clk_i);
        sxout0->rst_i(rst_i);
        sxout0->data_o(s_out_data_o);
        sxout0->val_o(s_out_val_o);
        sxout0->ack_i(s_out_ack_i);
        sxout0->req_i(req_w_s_o);
        sxout0->gnt_o(gnt_w_s_o);
        sxout0->rok_i(rok_w_s_o);
        sxout0->rd_o(s_rd_w);
        sxout0->data3_i(l_data_w);
        sxout0->data2_i(n_data_w);
        sxout0->data1_i(e_data_w);
        sxout0->data0_i(w_data_w);

        wxout0->clk_i(clk_i);
        wxout0->rst_i(rst_i);
        wxout0->data_o(w_out_data_o);
        wxout0->val_o(w_out_val_o);
        wxout0->ack_i(w_out_ack_i);
        wxout0->req_i(req_w_w_o);
        wxout0->gnt_o(gnt_w_w_o);
        wxout0->rok_i(rok_w_w_o);
        wxout0->rd_o(w_rd_w);
        wxout0->data3_i(l_data_w);
        wxout0->data2_i(n_data_w);
        wxout0->data1_i(e_data_w);
        wxout0->data0_i(s_data_w);

        xbar0->l_req_n_i(l_req_n_xin_w);
        xbar0->l_req_e_i(l_req_e_xin_w);
        xbar0->l_req_s_i(l_req_s_xin_w);
        xbar0->l_req_w_i(l_req_w_xin_w);
        xbar0->l_req_n_o(l_req_n_xout_w);
        xbar0->l_req_e_o(l_req_e_xout_w);
        xbar0->l_req_s_o(l_req_s_xout_w);
        xbar0->l_req_w_o(l_req_w_xout_w);
        xbar0->n_req_l_i(n_req_l_xin_w);
        xbar0->n_req_e_i(n_req_e_xin_w);
        xbar0->n_req_s_i(n_req_s_xin_w);
        xbar0->n_req_w_i(n_req_w_xin_w);
        xbar0->n_req_l_o(n_req_l_xout_w);
        xbar0->n_req_e_o(n_req_e_xout_w);
        xbar0->n_req_s_o(n_req_s_xout_w);
        xbar0->n_req_w_o(n_req_w_xout_w);
        xbar0->e_req_l_i(e_req_l_xin_w);
        xbar0->e_req_n_i(e_req_n_xin_w);
        xbar0->e_req_s_i(e_req_s_xin_w);
        xbar0->e_req_w_i(e_req_w_xin_w);
        xbar0->e_req_l_o(e_req_l_xout_w);
        xbar0->e_req_n_o(e_req_n_xout_w);
        xbar0->e_req_s_o(e_req_s_xout_w);
        xbar0->e_req_w_o(e_req_w_xout_w);
        xbar0->s_req_l_i(s_req_l_xin_w);
        xbar0->s_req_n_i(s_req_n_xin_w);
        xbar0->s_req_e_i(s_req_e_xin_w);
        xbar0->s_req_w_i(s_req_w_xin_w);
        xbar0->s_req_l_o(s_req_l_xout_w);
        xbar0->s_req_n_o(s_req_n_xout_w);
        xbar0->s_req_e_o(s_req_e_xout_w);
        xbar0->s_req_w_o(s_req_w_xout_w);
        xbar0->w_req_l_i(w_req_l_xin_w);
        xbar0->w_req_n_i(w_req_n_xin_w);
        xbar0->w_req_e_i(w_req_e_xin_w);
        xbar0->w_req_s_i(w_req_s_xin_w);
        xbar0->w_req_l_o(w_req_l_xout_w);
        xbar0->w_req_n_o(w_req_n_xout_w);
        xbar0->w_req_e_o(w_req_e_xout_w);
        xbar0->w_req_s_o(w_req_s_xout_w);
        xbar0->l_gnt_n_i(l_gnt_n_xout_w);
        xbar0->l_gnt_e_i(l_gnt_e_xout_w);
        xbar0->l_gnt_s_i(l_gnt_s_xout_w);
        xbar0->l_gnt_w_i(l_gnt_w_xout_w);
        xbar0->l_gnt_n_o(l_gnt_n_xin_w);
        xbar0->l_gnt_e_o(l_gnt_e_xin_w);
        xbar0->l_gnt_s_o(l_gnt_s_xin_w);
        xbar0->l_gnt_w_o(l_gnt_w_xin_w);
        xbar0->n_gnt_l_i(n_gnt_l_xout_w);
        xbar0->n_gnt_e_i(n_gnt_e_xout_w);
        xbar0->n_gnt_s_i(n_gnt_s_xout_w);
        xbar0->n_gnt_w_i(n_gnt_w_xout_w);
        xbar0->n_gnt_l_o(n_gnt_l_xin_w);
        xbar0->n_gnt_e_o(n_gnt_e_xin_w);
        xbar0->n_gnt_s_o(n_gnt_s_xin_w);
        xbar0->n_gnt_w_o(n_gnt_w_xin_w);
        xbar0->e_gnt_l_i(e_gnt_l_xout_w);
        xbar0->e_gnt_n_i(e_gnt_n_xout_w);
        xbar0->e_gnt_s_i(e_gnt_s_xout_w);
        xbar0->e_gnt_w_i(e_gnt_w_xout_w);
        xbar0->e_gnt_l_o(e_gnt_l_xin_w);
        xbar0->e_gnt_n_o(e_gnt_n_xin_w);
        xbar0->e_gnt_s_o(e_gnt_s_xin_w);
        xbar0->e_gnt_w_o(e_gnt_w_xin_w);
        xbar0->s_gnt_l_i(s_gnt_l_xout_w);
        xbar0->s_gnt_n_i(s_gnt_n_xout_w);
        xbar0->s_gnt_e_i(s_gnt_e_xout_w);
        xbar0->s_gnt_w_i(s_gnt_w_xout_w);
        xbar0->s_gnt_l_o(s_gnt_l_xin_w);
        xbar0->s_gnt_n_o(s_gnt_n_xin_w);
        xbar0->s_gnt_e_o(s_gnt_e_xin_w);
        xbar0->s_gnt_w_o(s_gnt_w_xin_w);
        xbar0->w_gnt_l_i(w_gnt_l_xout_w);
        xbar0->w_gnt_n_i(w_gnt_n_xout_w);
        xbar0->w_gnt_e_i(w_gnt_e_xout_w);
        xbar0->w_gnt_s_i(w_gnt_s_xout_w);
        xbar0->w_gnt_l_o(w_gnt_l_xin_w);
        xbar0->w_gnt_n_o(w_gnt_n_xin_w);
        xbar0->w_gnt_e_o(w_gnt_e_xin_w);
        xbar0->w_gnt_s_o(w_gnt_s_xin_w);
    }


};