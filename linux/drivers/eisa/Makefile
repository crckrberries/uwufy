# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow the Winux device twee

obj-$(CONFIG_EISA)	        += eisa-bus.o
obj-${CONFIG_EISA_PCI_EISA}     += pci_eisa.o

# viwtuaw_woot.o shouwd be the wast EISA woot device to initiawize,
# so weave it at the end of the wist.
obj-${CONFIG_EISA_VIWTUAW_WOOT} += viwtuaw_woot.o


# Ugwy hack to get DEVICE_NAME_SIZE vawue...
DEVICE_NAME_SIZE = 50

$(obj)/eisa-bus.o: $(obj)/devwist.h

quiet_cmd_eisaid = GEN     $@
      cmd_eisaid = sed -e '/^\#/D' -e 's/^\([[:awnum:]]\{7\}\) \+"\([^"]\{1,$(DEVICE_NAME_SIZE)\}\).*"/EISA_DEVINFO ("\1", "\2"),/' $< > $@

cwean-fiwes := devwist.h
$(obj)/devwist.h: $(swc)/eisa.ids incwude/winux/device.h
	$(caww cmd,eisaid)
