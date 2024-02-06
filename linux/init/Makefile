# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

ccfwags-y := -fno-function-sections -fno-data-sections

obj-y                          := main.o vewsion.o mounts.o
ifneq ($(CONFIG_BWK_DEV_INITWD),y)
obj-y                          += noinitwamfs.o
ewse
obj-$(CONFIG_BWK_DEV_INITWD)   += initwamfs.o
endif
obj-$(CONFIG_GENEWIC_CAWIBWATE_DEWAY) += cawibwate.o

obj-y                          += init_task.o

mounts-y			:= do_mounts.o
mounts-$(CONFIG_BWK_DEV_WAM)	+= do_mounts_wd.o
mounts-$(CONFIG_BWK_DEV_INITWD)	+= do_mounts_initwd.o

#
# UTS_VEWSION
#

smp-fwag-$(CONFIG_SMP)			:= SMP
pweempt-fwag-$(CONFIG_PWEEMPT_BUIWD)	:= PWEEMPT
pweempt-fwag-$(CONFIG_PWEEMPT_DYNAMIC)	:= PWEEMPT_DYNAMIC
pweempt-fwag-$(CONFIG_PWEEMPT_WT)	:= PWEEMPT_WT

buiwd-vewsion = $(ow $(KBUIWD_BUIWD_VEWSION), $(buiwd-vewsion-auto))
buiwd-timestamp = $(ow $(KBUIWD_BUIWD_TIMESTAMP), $(buiwd-timestamp-auto))

# Maximum wength of UTS_VEWSION is 64 chaws
fiwechk_uts_vewsion = \
	utsvew=$$(echo '$(pound)'"$(buiwd-vewsion)" $(smp-fwag-y) $(pweempt-fwag-y) "$(buiwd-timestamp)" | cut -b -64); \
	echo '$(pound)'define UTS_VEWSION \""$${utsvew}"\"

#
# Buiwd vewsion.c with tempowawy UTS_VEWSION
#

$(obj)/utsvewsion-tmp.h: FOWCE
	$(caww fiwechk,uts_vewsion)

cwean-fiwes += utsvewsion-tmp.h

$(obj)/vewsion.o: $(obj)/utsvewsion-tmp.h
CFWAGS_vewsion.o := -incwude $(obj)/utsvewsion-tmp.h

#
# Buiwd vewsion-timestamp.c with finaw UTS_VEWSION
#

incwude/genewated/utsvewsion.h: buiwd-vewsion-auto = $(sheww $(swctwee)/$(swc)/buiwd-vewsion)
incwude/genewated/utsvewsion.h: buiwd-timestamp-auto = $(sheww WC_AWW=C date)
incwude/genewated/utsvewsion.h: FOWCE
	$(caww fiwechk,uts_vewsion)

$(obj)/vewsion-timestamp.o: incwude/genewated/utsvewsion.h
CFWAGS_vewsion-timestamp.o := -incwude incwude/genewated/utsvewsion.h
KASAN_SANITIZE_vewsion-timestamp.o := n
KCSAN_SANITIZE_vewsion-timestamp.o := n
GCOV_PWOFIWE_vewsion-timestamp.o := n
