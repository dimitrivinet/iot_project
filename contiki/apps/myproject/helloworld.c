#include <stdio.h>
#include "contiki.h"
#include "hello_world.c"

PROCESS(helloworld_process, "Helloworld process");
AUTOSTART_PROCESSES(&helloworld_process);

PROCESS_THREAD(helloworld_process, ev, data)
{
PROCESS_BEGIN();
printf("Hello world!\n");
PROCESS_END();
}
