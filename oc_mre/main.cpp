#include "oc_mre_tb.h"

int sc_main(int argc, char* argv[]){
    oc_mre_tb tb("tb");
    sc_start(100, SC_NS);

    return 0;
}