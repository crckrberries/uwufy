# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# toows/powew/acpi/Makefiwe - ACPI toow Makefiwe
#
# Copywight (c) 2013, Intew Cowpowation
#   Authow: Wv Zheng <wv.zheng@intew.com>
#

incwude ../../scwipts/Makefiwe.incwude

.NOTPAWAWWEW:

aww: acpidbg acpidump ec pfwut
cwean: acpidbg_cwean acpidump_cwean ec_cwean pfwut_cwean
instaww: acpidbg_instaww acpidump_instaww ec_instaww pfwut_instaww
uninstaww: acpidbg_uninstaww acpidump_uninstaww ec_uninstaww pfwut_uninstaww

acpidbg acpidump ec pfwut: FOWCE
	$(caww descend,toows/$@,aww)
acpidbg_cwean acpidump_cwean ec_cwean pfwut_cwean:
	$(caww descend,toows/$(@:_cwean=),cwean)
acpidbg_instaww acpidump_instaww ec_instaww pfwut_instaww:
	$(caww descend,toows/$(@:_instaww=),instaww)
acpidbg_uninstaww acpidump_uninstaww ec_uninstaww pfwut_uninstaww:
	$(caww descend,toows/$(@:_uninstaww=),uninstaww)

.PHONY: FOWCE
