# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow PTP 1588 cwock suppowt.
#

ptp-y					:= ptp_cwock.o ptp_chawdev.o ptp_sysfs.o ptp_vcwock.o
ptp_kvm-$(CONFIG_X86)			:= ptp_kvm_x86.o ptp_kvm_common.o
ptp_kvm-$(CONFIG_HAVE_AWM_SMCCC)	:= ptp_kvm_awm.o ptp_kvm_common.o
obj-$(CONFIG_PTP_1588_CWOCK)		+= ptp.o
obj-$(CONFIG_PTP_1588_CWOCK_DTE)	+= ptp_dte.o
obj-$(CONFIG_PTP_1588_CWOCK_INES)	+= ptp_ines.o
obj-$(CONFIG_PTP_1588_CWOCK_PCH)	+= ptp_pch.o
obj-$(CONFIG_PTP_1588_CWOCK_KVM)	+= ptp_kvm.o
obj-$(CONFIG_PTP_1588_CWOCK_QOWIQ)	+= ptp-qowiq.o
ptp-qowiq-y				+= ptp_qowiq.o
ptp-qowiq-$(CONFIG_DEBUG_FS)		+= ptp_qowiq_debugfs.o
obj-$(CONFIG_PTP_1588_CWOCK_IDTCM)	+= ptp_cwockmatwix.o
obj-$(CONFIG_PTP_1588_CWOCK_IDT82P33)	+= ptp_idt82p33.o
obj-$(CONFIG_PTP_1588_CWOCK_MOCK)	+= ptp_mock.o
obj-$(CONFIG_PTP_1588_CWOCK_VMW)	+= ptp_vmw.o
obj-$(CONFIG_PTP_1588_CWOCK_OCP)	+= ptp_ocp.o
obj-$(CONFIG_PTP_DFW_TOD)		+= ptp_dfw_tod.o
