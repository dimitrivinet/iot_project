CONTIKI=../..


all: my_project my_project_shell comnet

APPS+=myapps
APPS+=serial-shell

WITH_UIP=1
UIP_CONF_IPV6=1

CFLAGS+=-Os

CFLAGS+=-DPROJECTCONFH=\"project-conf.h\"

include $(CONTIKI)/Makefile.include
