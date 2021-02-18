/*
 * Copyright (c) 2008, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * $Id: shell-ps.c,v 1.1 2008/02/04 23:42:17 adamdunkels Exp $
 */

/**
 * \file
 *         Process-related Contiki shell commands
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "shell-setname.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------*/
PROCESS(shell_setname_process, "setname USER_NAME");
SHELL_COMMAND(setname_command,
	      "setname",
	      "setname USER_NAME: store username in global variable",
	      &shell_setname_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(shell_setname_process, ev, data)
{
  char *name = malloc(sizeof(char)*50);
  extern char* name_from_command;
  PROCESS_BEGIN();

  strncpy(name, data, 50);
  if (name == NULL || strlen(name) == 0)
  {
    //shell_output_str(&setname_command, 
    //	"setname USER_NAME: user name must be given", "");
    printf("setname USER_NAME: user name must be given\n");
    PROCESS_EXIT();
  }
  else
  {
    //shell_output_str(&setname_command, "Your username is: ", name);
    printf("You username is: %s\n", name);
    name_from_command = malloc(sizeof(char)*strlen(name));
    strcpy(name_from_command, name);
    /*   
    shell_output_str(&setname_command, "User name saved: ",
        name_from_command);
    */
  }

  free(name);

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
void
shell_setname_init(void)
{
  shell_register_command(&setname_command);
}
/*---------------------------------------------------------------------------*/
