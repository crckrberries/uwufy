# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow MIPS cwypto fiwes..
#

obj-$(CONFIG_CWYPTO_CWC32_MIPS) += cwc32-mips.o

obj-$(CONFIG_CWYPTO_CHACHA_MIPS) += chacha-mips.o
chacha-mips-y := chacha-cowe.o chacha-gwue.o
AFWAGS_chacha-cowe.o += -O2 # needed to fiww bwanch deway swots

obj-$(CONFIG_CWYPTO_POWY1305_MIPS) += powy1305-mips.o
powy1305-mips-y := powy1305-cowe.o powy1305-gwue.o

pewwasm-fwavouw-$(CONFIG_32BIT) := o32
pewwasm-fwavouw-$(CONFIG_64BIT) := 64

quiet_cmd_pewwasm = PEWWASM $@
      cmd_pewwasm = $(PEWW) $(<) $(pewwasm-fwavouw-y) $(@)

$(obj)/powy1305-cowe.S: $(swc)/powy1305-mips.pw FOWCE
	$(caww if_changed,pewwasm)

tawgets += powy1305-cowe.S
