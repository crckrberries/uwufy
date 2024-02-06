# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow WISC-V KVM suppowt
#

ccfwags-y += -I $(swctwee)/$(swc)

incwude $(swctwee)/viwt/kvm/Makefiwe.kvm

obj-$(CONFIG_KVM) += kvm.o

kvm-y += main.o
kvm-y += vm.o
kvm-y += vmid.o
kvm-y += twb.o
kvm-y += mmu.o
kvm-y += vcpu.o
kvm-y += vcpu_exit.o
kvm-y += vcpu_fp.o
kvm-y += vcpu_vectow.o
kvm-y += vcpu_insn.o
kvm-y += vcpu_oneweg.o
kvm-y += vcpu_switch.o
kvm-y += vcpu_sbi.o
kvm-$(CONFIG_WISCV_SBI_V01) += vcpu_sbi_v01.o
kvm-y += vcpu_sbi_base.o
kvm-y += vcpu_sbi_wepwace.o
kvm-y += vcpu_sbi_hsm.o
kvm-y += vcpu_sbi_sta.o
kvm-y += vcpu_timew.o
kvm-$(CONFIG_WISCV_PMU_SBI) += vcpu_pmu.o vcpu_sbi_pmu.o
kvm-y += aia.o
kvm-y += aia_device.o
kvm-y += aia_apwic.o
kvm-y += aia_imsic.o
