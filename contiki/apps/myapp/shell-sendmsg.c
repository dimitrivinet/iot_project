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
#include "lib/random.h"
#include "sys/ctimer.h"
#include "sys/etimer.h"
#include "net/uip.h"
#include "net/uip-ds6.h"

#include "simple-udp.h"

#include "shell-setname.h"
#include "shell-sendmsg.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UDP_PORT 1234

static struct simple_udp_connection broadcast_connection;

/*---------------------------------------------------------------------------*/
PROCESS(shell_sendmsg_process, "send MSG");
SHELL_COMMAND(sendmsg_command,
	      "send",
	      "send MSG: broadcast message",
	      &shell_sendmsg_process);
/*---------------------------------------------------------------------------*/
static void
receiver(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{
  printf("%s\n", data);
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(shell_sendmsg_process, ev, data)
{
  char* msg;
  char* input;
  extern char* name_from_command;
  uip_ipaddr_t addr;


  PROCESS_BEGIN();

  simple_udp_register(&broadcast_connection, UDP_PORT,
                      NULL, UDP_PORT,
                      receiver);

  input = data;
  if (input == NULL || strlen(input) == 0)
  {
    //shell_output_str(&sendmsg_command, 
    //	"send MSG: message must be given", "");
    printf("send MSG: message must be given\n");
    PROCESS_EXIT();
  }
  else if (name_from_command == NULL || strlen(name_from_command) == 0)
  {
    //shell_output_str(&sendmsg_command,
    //	"send MSG: need username first (use setname USER_NAME)", "");
    printf("send MSG: need username first (use netmane USER_NAME)"); 
  }
  else
  {
    msg = malloc(sizeof(char) * (strlen(input) + strlen(name_from_command) + 2));
    strcat(msg, name_from_command);
    strcat(msg, ": ");
    strcat(msg, input);

    // shell_output_str(&sendmsg_command, "msg:\n", msg);
    printf("msg: \n%s\n", msg);
    //printf("Sending broadcast\n");
    uip_create_linklocal_allnodes_mcast(&addr);
    simple_udp_sendto(&broadcast_connection, msg, strlen(msg), &addr);

    free(msg);    
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
void
shell_sendmsg_init(void)
{
  shell_register_command(&sendmsg_command);
}
/*---------------------------------------------------------------------------*/
