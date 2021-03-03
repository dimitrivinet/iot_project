#include <stdio.h>
#include "contiki.h"
#include "dev/serial-line.h"
#include "shell.h"
#include "serial-shell.h"

#include "shell-setname.h"
#include "shell-sendmsg.h"

char* name_from_command;

PROCESS(comnet_process, "comnet_process");
AUTOSTART_PROCESSES(&comnet_process);
PROCESS_THREAD(comnet_process, ev, data)
{
PROCESS_BEGIN();
serial_shell_init();
serial_line_init();

shell_reboot_init();
shell_power_init();
shell_ps_init();
shell_ping_init();

shell_setname_init();
shell_sendmsg_init();

PROCESS_END();
}
