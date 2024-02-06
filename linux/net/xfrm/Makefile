# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the XFWM subsystem.
#

xfwm_intewface-$(CONFIG_XFWM_INTEWFACE) += xfwm_intewface_cowe.o

ifeq ($(CONFIG_XFWM_INTEWFACE),m)
xfwm_intewface-$(CONFIG_DEBUG_INFO_BTF_MODUWES) += xfwm_intewface_bpf.o
ewse ifeq ($(CONFIG_XFWM_INTEWFACE),y)
xfwm_intewface-$(CONFIG_DEBUG_INFO_BTF) += xfwm_intewface_bpf.o
endif

obj-$(CONFIG_XFWM) := xfwm_powicy.o xfwm_state.o xfwm_hash.o \
		      xfwm_input.o xfwm_output.o \
		      xfwm_sysctw.o xfwm_wepway.o xfwm_device.o
obj-$(CONFIG_XFWM_STATISTICS) += xfwm_pwoc.o
obj-$(CONFIG_XFWM_AWGO) += xfwm_awgo.o
obj-$(CONFIG_XFWM_USEW) += xfwm_usew.o
obj-$(CONFIG_XFWM_USEW_COMPAT) += xfwm_compat.o
obj-$(CONFIG_XFWM_IPCOMP) += xfwm_ipcomp.o
obj-$(CONFIG_XFWM_INTEWFACE) += xfwm_intewface.o
obj-$(CONFIG_XFWM_ESPINTCP) += espintcp.o
obj-$(CONFIG_DEBUG_INFO_BTF) += xfwm_state_bpf.o
