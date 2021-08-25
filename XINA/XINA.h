#include "systemc.h"
#include "../router/router.h"


template<int rows_c, int cols_c, int data_width_c>
struct XINA : sc_module {

    sc_clock clk_i;
    sc_in<sc_bv<1>> rst_i;

    sc_in<sc_bv<data_width_c>> l_in_data_i[cols_c][rows_c];
    sc_in<sc_bv<1>> l_in_val_i[cols_c][rows_c];
    sc_in<sc_bv<1>> l_in_ack_o[cols_c][rows_c];
    sc_out<sc_bv<data_width_c>> l_out_data_o[cols_c][rows_c];
    sc_out<sc_bv<1>> l_out_val_o[cols_c][rows_c];
    sc_out<sc_bv<1>> l_out_ack_i[cols_c][rows_c];

    sc_signal<sc_bv<data_width_c>> x_in_data_w[cols_c+1][rows_c];
    sc_signal<sc_bv<1>> x_in_val_w[cols_c+1][rows_c];
    sc_signal<sc_bv<1>> x_in_ack_w[cols_c+1][rows_c];
    sc_signal<sc_bv<data_width_c>> x_out_data_w[cols_c+1][rows_c];
    sc_signal<sc_bv<1>> x_out_val_w[cols_c+1][rows_c];
    sc_signal<sc_bv<1>> x_out_ack_w[cols_c+1][rows_c];

    sc_signal<sc_bv<data_width_c>> y_in_data_w[cols_c][rows_c+1];
    sc_signal<sc_bv<1>> y_in_val_w[cols_c][rows_c+1];
    sc_signal<sc_bv<1>> y_in_ack_w[cols_c][rows_c+1];
    sc_signal<sc_bv<data_width_c>> y_out_data_w[cols_c][rows_c+1];
    sc_signal<sc_bv<1>> y_out_val_w[cols_c][rows_c+1];
    sc_signal<sc_bv<1>> y_out_ack_w[cols_c][rows_c+1];

    router<0,0,data_width_c> *u_router[cols_c][rows_c];

    //sc_vector<router<0,0,data_width_c>> a;
    
    //sc_module *u_router[cols_c][rows_c];

    void y0(){
        for(int i=0; i<cols_c; i++){
            y_in_data_w[i][rows_c-1].write(0);
            y_in_val_w[i][rows_c-1].write(0);
            y_in_ack_w[i][rows_c-1].write(0);
            y_out_data_w[i][0].write(0);
            y_out_val_w[i][0].write(0);
            y_out_ack_w[i][0].write(0);
        }
    }

    void x0(){
        for(int i=0; i<rows_c; i++){
            x_in_data_w[0][i].write(0);
            x_in_val_w[0][i].write(0);
            x_in_ack_w[0][i].write(0);
            x_out_data_w[cols_c-1][i].write(0);
            x_out_val_w[cols_c-1][i].write(0);
            x_out_ack_w[cols_c-1][i].write(0);
        }
    }

    SC_CTOR(XINA)
    {
        SC_METHOD(y0);
        SC_METHOD(x0);
        sensitive << clk_i << rst_i;
        
        u_router[0][0] = new router<0, 0, data_width_c>("router");
        u_router[0][1] = new router<0, 1, data_width_c>("router");
        u_router[1][0] = new router<1, 0, data_width_c>("router");
        u_router[1][1] = new router<1, 1, data_width_c>("router");

        for(int i=0; i<cols_c; i++){
            for(int j=0; j<rows_c; j++){
                //u_router[i][j] = new router<i, j, data_width_c>("router");
                u_router[i][j]->clk_i(clk_i);
                u_router[i][j]->rst_i(rst_i);
                u_router[i][j]->l_in_data_i(l_in_data_i[i][j]);
                u_router[i][j]->l_in_val_i(l_in_val_i[i][j]);
                u_router[i][j]->l_in_ack_o(l_in_ack_o[i][j]);
                u_router[i][j]->l_out_data_o(l_out_data_o[i][j]);
                u_router[i][j]->l_out_val_o(l_out_val_o[i][j]);
                u_router[i][j]->l_out_ack_i(l_out_ack_i[i][j]);
                
                u_router[i][j]->n_in_data_i(y_in_data_w[i][j+1]);
                u_router[i][j]->n_in_val_i(y_in_val_w[i][j+1]);
                u_router[i][j]->n_in_ack_o(y_in_ack_w[i][j+1]);
                u_router[i][j]->n_out_data_o(y_out_data_w[i][j+1]);
                u_router[i][j]->n_out_val_o(y_out_val_w[i][j+1]);
                u_router[i][j]->n_out_ack_i(y_out_ack_w[i][j+1]);

                u_router[i][j]->e_in_data_i(x_in_data_w[i+1][j]);
                u_router[i][j]->e_in_val_i(x_in_val_w[i+1][j]);
                u_router[i][j]->e_in_ack_o(x_in_ack_w[i+1][j]);
                u_router[i][j]->e_out_data_o(x_out_data_w[i+1][j]);
                u_router[i][j]->e_out_val_o(x_out_val_w[i+1][j]);
                u_router[i][j]->e_out_ack_i(x_out_ack_w[i+1][j]);

                u_router[i][j]->s_in_data_i(y_in_data_w[i][j]);
                u_router[i][j]->s_in_val_i(y_in_val_w[i][j]);
                u_router[i][j]->s_in_ack_o(y_in_ack_w[i][j]);
                u_router[i][j]->s_out_data_o(y_out_data_w[i][j]);
                u_router[i][j]->s_out_val_o(y_out_val_w[i][j]);
                u_router[i][j]->s_out_ack_i(y_out_ack_w[i][j]);

                u_router[i][j]->w_in_data_i(x_in_data_w[i][j]);
                u_router[i][j]->w_in_val_i(x_in_val_w[i][j]);
                u_router[i][j]->w_in_ack_o(x_in_ack_w[i][j]);
                u_router[i][j]->w_out_data_o(x_out_data_w[i][j]);
                u_router[i][j]->w_out_val_o(x_out_val_w[i][j]);
                u_router[i][j]->w_out_ack_i(x_out_ack_w[i][j]);
            }
        }
    }
};