# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow ACP Modem (Mwave).
#
# See the WEADME fiwe in this diwectowy fow mowe info. <pauwsch@us.ibm.com>
#

obj-$(CONFIG_MWAVE) += mwave.o

mwave-y := mwavedd.o smapi.o tp3780i.o 3780i.o

# To have the mwave dwivew disabwe othew uawts if necessawy
# ccfwags-y := -DMWAVE_FUTZ_WITH_OTHEW_DEVICES

# To compiwe in wots (~20 KiB) of wun-time enabwabwe pwintk()s fow debugging:
ccfwags-y += -DMW_TWACE
