#include "cli.h"


int main(void) {
    cli_clear();
    cli_set_buffred_inputs(0);

    for (int i = 0; i < 8; ++i) {
        cli_set_fg(i);
        printf("Color ");
    }

    cli_reset();
    printf("\n");

    for (int i = 0; i < 8; ++i) {
        cli_set_bg(i);
        printf("Color ");
    }

    cli_reset(); printf("\n");
    cli_bold(); printf("Bold\n");
    cli_reset();
    cli_dimmed(); printf("dimmed\n");
    cli_reset();
    cli_italic(); printf("italic\n");
    cli_reset();
    cli_underlined(); printf("underlined\n");
    cli_reset();

    cli_goto(10, 20);
    printf("10, 20");

    printf("\n"); /* empty buffer */

    printf("press a key to quit\n");
    while (!cli_kbhit()) { }

    cli_set_buffred_inputs(1);

    return 0;
}
