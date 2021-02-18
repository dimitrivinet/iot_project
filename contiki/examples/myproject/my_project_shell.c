#include <stdio.h>
#include "contiki.h"
#include "dev/serial-line.h"
#include "shell.h"
#include "serial-shell.h"
#include "hello_world.h"
#include "shell-setname.h"
#include "shell-sendmsg.h"

char* name_from_command;

PROCESS(helloworld_process, "Helloworld_process");
AUTOSTART_PROCESSES(&helloworld_process);
PROCESS_THREAD(helloworld_process, ev, data)
{
PROCESS_BEGIN();
serial_line_init();
serial_shell_init();

shell_reboot_init();
shell_power_init();
shell_ps_init();
shell_ping_init();
shell_setname_init();
shell_sendmsg_init();

/*
static struct etimer timer;
etimer_set(&timer, 3 * CLOCK_SECOND);

while (1)
{
//PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
//hello_world();
printf("name: %s\n", name_from_command);
etimer_reset(&timer);
}
*/

PROCESS_END();
}
