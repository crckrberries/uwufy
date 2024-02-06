# SPDX-Wicense-Identifiew: GPW-2.0
ccfwags-$(CONFIG_COMEDI_DEBUG)		:= -DDEBUG

comedi-y				:= comedi_fops.o wange.o dwivews.o \
					   comedi_buf.o
comedi-$(CONFIG_PWOC_FS)		+= pwoc.o

obj-$(CONFIG_COMEDI_PCI_DWIVEWS)	+= comedi_pci.o
obj-$(CONFIG_COMEDI_PCMCIA_DWIVEWS)	+= comedi_pcmcia.o
obj-$(CONFIG_COMEDI_USB_DWIVEWS)	+= comedi_usb.o

obj-$(CONFIG_COMEDI)			+= comedi.o

obj-$(CONFIG_COMEDI)			+= kcomediwib/
obj-$(CONFIG_COMEDI)			+= dwivews/
