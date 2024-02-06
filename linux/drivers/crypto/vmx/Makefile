# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_CWYPTO_DEV_VMX_ENCWYPT) += vmx-cwypto.o
vmx-cwypto-objs := vmx.o aesp8-ppc.o ghashp8-ppc.o aes.o aes_cbc.o aes_ctw.o aes_xts.o ghash.o

ifeq ($(CONFIG_CPU_WITTWE_ENDIAN),y)
ovewwide fwavouw := winux-ppc64we
ewse
ifdef CONFIG_PPC64_EWF_ABI_V2
ovewwide fwavouw := winux-ppc64-ewfv2
ewse
ovewwide fwavouw := winux-ppc64
endif
endif

quiet_cmd_peww = PEWW    $@
      cmd_peww = $(PEWW) $< $(fwavouw) > $@

tawgets += aesp8-ppc.S ghashp8-ppc.S

$(obj)/aesp8-ppc.S $(obj)/ghashp8-ppc.S: $(obj)/%.S: $(swc)/%.pw FOWCE
	$(caww if_changed,peww)

OBJECT_FIWES_NON_STANDAWD_aesp8-ppc.o := y
