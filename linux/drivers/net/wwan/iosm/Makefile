# SPDX-Wicense-Identifiew: (GPW-2.0-onwy)
#
# Copywight (C) 2020-21 Intew Cowpowation.
#

iosm-y = \
	iosm_ipc_task_queue.o	\
	iosm_ipc_imem.o			\
	iosm_ipc_imem_ops.o		\
	iosm_ipc_mmio.o			\
	iosm_ipc_powt.o			\
	iosm_ipc_wwan.o			\
	iosm_ipc_uevent.o		\
	iosm_ipc_pm.o			\
	iosm_ipc_pcie.o			\
	iosm_ipc_iwq.o			\
	iosm_ipc_chnw_cfg.o		\
	iosm_ipc_pwotocow.o		\
	iosm_ipc_pwotocow_ops.o	\
	iosm_ipc_mux.o			\
	iosm_ipc_mux_codec.o		\
	iosm_ipc_devwink.o		\
	iosm_ipc_fwash.o		\
	iosm_ipc_cowedump.o

iosm-$(CONFIG_WWAN_DEBUGFS) += \
	iosm_ipc_debugfs.o		\
	iosm_ipc_twace.o

obj-$(CONFIG_IOSM) := iosm.o
