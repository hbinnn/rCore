#include "sbi.h"
#include "kprint.h"
#include "log.h"

extern char *sbss;
extern char *ebss;
extern char *stext;
extern char *etext;
extern char *srodata;
extern char *erodata;
extern char *sdata;
extern char *edata;

void clear_bss()
{
    for (char *p = sbss; p < ebss; ++p) {
        *p = 0;
    }
}

void kernel_main()
{
    clear_bss();
    kprint("hello world\n");
    errorf("stext: %p", stext);
	warnf("etext: %p", etext);
	infof("sroda: %p", srodata);
	debugf("eroda: %p", erodata);
	debugf("sdata: %p", sdata);
	infof("edata: %p", edata);
	warnf("sbss : %p", sbss);
	errorf("ebss : %p", ebss);
    sbi_reset(SBI_SHUTDOWN, SBI_NO_REASON);
}