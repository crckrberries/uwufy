# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Awch-specific netwowk moduwes
#
obj-$(CONFIG_BPF_JIT) += bpf_jit_comp_$(BITS).o
ifeq ($(BITS),32)
obj-$(CONFIG_BPF_JIT) += bpf_jit_asm_32.o
endif
