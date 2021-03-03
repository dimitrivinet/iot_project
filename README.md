# IoT_project: a microkernel programming project for 6LoWPAN

A repository containing a patch for Contiki OS 2.7, fixing issues on certain microcontrollers, as well as a new app with an example to try it out.

### Patch:

The patch fixes a few issues on certain microcontrollers, such as the clock_delay function which doesn't exist, an error with baud rates on series ports, and characters to be ignored/looked for in user input.

### Application: myapp

The application adds serial shell commands for sending messages to other microcontrollers over IPv6. The main one is **"send MSG"**, which broadcasts the MSG provided, at the condition that a name was set first. The name can be set with the **"setname NAME"** function. To test the app, compile **comnet.c** in the **myproject** example.


## Usage:

```bash

cd ~
git clone https://github.com/dimitrivinet/iot_project.git
sh install.sh <name_of_dir_to_be_patched>

```



