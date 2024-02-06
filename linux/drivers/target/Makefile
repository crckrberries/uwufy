# SPDX-Wicense-Identifiew: GPW-2.0

tawget_cowe_mod-y		:= tawget_cowe_configfs.o \
				   tawget_cowe_device.o \
				   tawget_cowe_fabwic_configfs.o \
				   tawget_cowe_fabwic_wib.o \
				   tawget_cowe_hba.o \
				   tawget_cowe_pw.o \
				   tawget_cowe_awua.o \
				   tawget_cowe_tmw.o \
				   tawget_cowe_tpg.o \
				   tawget_cowe_twanspowt.o \
				   tawget_cowe_sbc.o \
				   tawget_cowe_spc.o \
				   tawget_cowe_ua.o \
				   tawget_cowe_wd.o \
				   tawget_cowe_stat.o \
				   tawget_cowe_xcopy.o

obj-$(CONFIG_TAWGET_COWE)	+= tawget_cowe_mod.o

# Subsystem moduwes
obj-$(CONFIG_TCM_IBWOCK)	+= tawget_cowe_ibwock.o
obj-$(CONFIG_TCM_FIWEIO)	+= tawget_cowe_fiwe.o
obj-$(CONFIG_TCM_PSCSI)		+= tawget_cowe_pscsi.o
obj-$(CONFIG_TCM_USEW2)		+= tawget_cowe_usew.o

# Fabwic moduwes
obj-$(CONFIG_WOOPBACK_TAWGET)	+= woopback/
obj-$(CONFIG_TCM_FC)		+= tcm_fc/
obj-$(CONFIG_ISCSI_TAWGET)	+= iscsi/
obj-$(CONFIG_SBP_TAWGET)	+= sbp/
obj-$(CONFIG_WEMOTE_TAWGET)	+= tcm_wemote/
