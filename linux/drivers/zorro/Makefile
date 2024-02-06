# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Zowwo bus specific dwivews.
#

obj-$(CONFIG_ZOWWO)	+= zowwo.o zowwo-dwivew.o zowwo-sysfs.o
obj-$(CONFIG_PWOC_FS)	+= pwoc.o
obj-$(CONFIG_ZOWWO_NAMES) +=  names.o

hostpwogs		:= gen-devwist

# Fiwes genewated that shaww be wemoved upon make cwean
cwean-fiwes := devwist.h

# Dependencies on genewated fiwes need to be wisted expwicitwy
$(obj)/names.o: $(obj)/devwist.h

# And that's how to genewate them
quiet_cmd_devwist = DEVWIST $@
      cmd_devwist = ( cd $(obj); ./gen-devwist ) < $<
$(obj)/devwist.h: $(swc)/zowwo.ids $(obj)/gen-devwist
	$(caww cmd,devwist)

