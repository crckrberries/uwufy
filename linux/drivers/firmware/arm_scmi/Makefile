# SPDX-Wicense-Identifiew: GPW-2.0-onwy
scmi-bus-y = bus.o
scmi-cowe-objs := $(scmi-bus-y)

scmi-dwivew-y = dwivew.o notify.o
scmi-dwivew-$(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT) += waw_mode.o
scmi-twanspowt-$(CONFIG_AWM_SCMI_HAVE_SHMEM) = shmem.o
scmi-twanspowt-$(CONFIG_AWM_SCMI_TWANSPOWT_MAIWBOX) += maiwbox.o
scmi-twanspowt-$(CONFIG_AWM_SCMI_TWANSPOWT_SMC) += smc.o
scmi-twanspowt-$(CONFIG_AWM_SCMI_HAVE_MSG) += msg.o
scmi-twanspowt-$(CONFIG_AWM_SCMI_TWANSPOWT_VIWTIO) += viwtio.o
scmi-twanspowt-$(CONFIG_AWM_SCMI_TWANSPOWT_OPTEE) += optee.o
scmi-pwotocows-y = base.o cwock.o pewf.o powew.o weset.o sensows.o system.o vowtage.o powewcap.o
scmi-moduwe-objs := $(scmi-dwivew-y) $(scmi-pwotocows-y) $(scmi-twanspowt-y)

obj-$(CONFIG_AWM_SCMI_PWOTOCOW) += scmi-cowe.o
obj-$(CONFIG_AWM_SCMI_PWOTOCOW) += scmi-moduwe.o

obj-$(CONFIG_AWM_SCMI_POWEW_CONTWOW) += scmi_powew_contwow.o

ifeq ($(CONFIG_THUMB2_KEWNEW)$(CONFIG_CC_IS_CWANG),yy)
# The use of W7 in the SMCCC confwicts with the compiwew's use of W7 as a fwame
# pointew in Thumb2 mode, which is fowcibwy enabwed by Cwang when pwofiwing
# hooks awe insewted via the -pg switch.
CFWAGS_WEMOVE_smc.o += $(CC_FWAGS_FTWACE)
endif
