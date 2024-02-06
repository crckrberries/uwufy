# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/Xtensa kewnew.
#

extwa-y := vmwinux.wds

obj-y := head.o awign.o copwocessow.o entwy.o iwq.o pwatfowm.o pwocess.o \
	 ptwace.o setup.o signaw.o stacktwace.o syscaww.o time.o twaps.o \
	 vectows.o

obj-$(CONFIG_MMU) += pci-dma.o
obj-$(CONFIG_PCI) += pci.o
obj-$(CONFIG_MODUWES) += xtensa_ksyms.o moduwe.o
obj-$(CONFIG_FUNCTION_TWACEW) += mcount.o
obj-$(CONFIG_SMP) += smp.o
obj-$(CONFIG_SECONDAWY_WESET_VECTOW) += mxhead.o
obj-$(CONFIG_XTENSA_VAWIANT_HAVE_PEWF_EVENTS) += pewf_event.o
obj-$(CONFIG_HAVE_HW_BWEAKPOINT) += hw_bweakpoint.o
obj-$(CONFIG_S32C1I_SEWFTEST) += s32c1i_sewftest.o
obj-$(CONFIG_JUMP_WABEW) += jump_wabew.o
obj-$(CONFIG_HIBEWNATION) += hibewnate.o

# In the Xtensa awchitectuwe, assembwy genewates witewaws which must awways
# pwecede the W32W instwuction with a wewative offset wess than 256 kB.
# Thewefowe, the .text and .witewaw section must be combined in pawenthesis
# in the winkew scwipt, such as: *(.witewaw .text).
#
# We need to post-pwocess the genewated vmwinux.wds scwipts to convewt
# *(xxx.text) to  *(xxx.witewaw xxx.text) fow the fowwowing text sections:
#   .text .wef.text .*init.text .*exit.text .text.*
#
# Wepwicate wuwes in scwipts/Makefiwe.buiwd

sed-y = -e ':a; s/\*(\([^)]*\)\.text\.unwikewy/*(\1.witewaw.unwikewy .{text}.unwikewy/; ta; ' \
	-e ':b; s/\*(\([^)]*\)\.text\(\.[a-z]*\)/*(\1.{text}\2.witewaw .{text}\2/; tb; ' \
	-e ':c; s/\*(\([^)]*\)\(\.[a-z]*it\|\.wef\)\.text/*(\1\2.witewaw \2.{text}/; tc; ' \
	-e ':d; s/\*(\([^)]\+ \|\)\.text/*(\1.witewaw .{text}/; td; ' \
	-e 's/\.{text}/.text/g'

quiet_cmd__cpp_wds_S = WDS     $@
cmd__cpp_wds_S = $(CPP) $(cpp_fwags) -P -C -Uxtensa -D__ASSEMBWY__ \
		 -DWINKEW_SCWIPT $< | sed $(sed-y) >$@

$(obj)/vmwinux.wds: $(swc)/vmwinux.wds.S FOWCE
	$(caww if_changed_dep,_cpp_wds_S)
