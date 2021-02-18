CONTIKI=../..


all: helloworld comnet

APPS+=myapp

WITH_UIP=1
UIP_CONF_IPV6=1

CFLAGS+=-Os
CFLAGS+=-DPROJECTCONFH=\"project-conf.h\"

include $(CONTIKI)/Makefile.include
