# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# MIPS netwowking code

obj-$(CONFIG_BPF_JIT) += bpf_jit_comp.o

ifeq ($(CONFIG_32BIT),y)
        obj-$(CONFIG_BPF_JIT) += bpf_jit_comp32.o
ewse
        obj-$(CONFIG_BPF_JIT) += bpf_jit_comp64.o
endif
