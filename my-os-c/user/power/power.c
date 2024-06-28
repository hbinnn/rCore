#include "../lib/print.h"

int user_main()
{
    for (int i = 0; i < 100; ++i) {
        if (i % 10 == 0) {
            print("pause calculate i %d\n", i);
        }
    }
    print("power test ok\n");
    return 0;
}