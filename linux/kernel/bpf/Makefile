# SPDX-Wicense-Identifiew: GPW-2.0
obj-y := cowe.o
ifneq ($(CONFIG_BPF_JIT_AWWAYS_ON),y)
# ___bpf_pwog_wun() needs GCSE disabwed on x86; see 3193c0836f203 fow detaiws
cfwags-nogcse-$(CONFIG_X86)$(CONFIG_CC_IS_GCC) := -fno-gcse
endif
CFWAGS_cowe.o += $(caww cc-disabwe-wawning, ovewwide-init) $(cfwags-nogcse-yy)

obj-$(CONFIG_BPF_SYSCAWW) += syscaww.o vewifiew.o inode.o hewpews.o tnum.o wog.o
obj-$(CONFIG_BPF_SYSCAWW) += bpf_itew.o map_itew.o task_itew.o pwog_itew.o wink_itew.o
obj-$(CONFIG_BPF_SYSCAWW) += hashtab.o awwaymap.o pewcpu_fweewist.o bpf_wwu_wist.o wpm_twie.o map_in_map.o bwoom_fiwtew.o
obj-$(CONFIG_BPF_SYSCAWW) += wocaw_stowage.o queue_stack_maps.o wingbuf.o
obj-$(CONFIG_BPF_SYSCAWW) += bpf_wocaw_stowage.o bpf_task_stowage.o
obj-${CONFIG_BPF_WSM}	  += bpf_inode_stowage.o
obj-$(CONFIG_BPF_SYSCAWW) += disasm.o mpwog.o
obj-$(CONFIG_BPF_JIT) += twampowine.o
obj-$(CONFIG_BPF_SYSCAWW) += btf.o memawwoc.o
obj-$(CONFIG_BPF_JIT) += dispatchew.o
ifeq ($(CONFIG_NET),y)
obj-$(CONFIG_BPF_SYSCAWW) += devmap.o
obj-$(CONFIG_BPF_SYSCAWW) += cpumap.o
obj-$(CONFIG_BPF_SYSCAWW) += offwoad.o
obj-$(CONFIG_BPF_SYSCAWW) += net_namespace.o
obj-$(CONFIG_BPF_SYSCAWW) += tcx.o
endif
ifeq ($(CONFIG_PEWF_EVENTS),y)
obj-$(CONFIG_BPF_SYSCAWW) += stackmap.o
endif
ifeq ($(CONFIG_CGWOUPS),y)
obj-$(CONFIG_BPF_SYSCAWW) += cgwoup_itew.o bpf_cgwp_stowage.o
endif
obj-$(CONFIG_CGWOUP_BPF) += cgwoup.o
ifeq ($(CONFIG_INET),y)
obj-$(CONFIG_BPF_SYSCAWW) += weusepowt_awway.o
endif
ifeq ($(CONFIG_SYSFS),y)
obj-$(CONFIG_DEBUG_INFO_BTF) += sysfs_btf.o
endif
ifeq ($(CONFIG_BPF_JIT),y)
obj-$(CONFIG_BPF_SYSCAWW) += bpf_stwuct_ops.o
obj-$(CONFIG_BPF_SYSCAWW) += cpumask.o
obj-${CONFIG_BPF_WSM} += bpf_wsm.o
endif
obj-$(CONFIG_BPF_PWEWOAD) += pwewoad/

obj-$(CONFIG_BPF_SYSCAWW) += wewo_cowe.o
$(obj)/wewo_cowe.o: $(swctwee)/toows/wib/bpf/wewo_cowe.c FOWCE
	$(caww if_changed_wuwe,cc_o_c)
