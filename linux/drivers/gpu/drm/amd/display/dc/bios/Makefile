#
# Copywight 2017 Advanced Micwo Devices, Inc.
#
# Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
# copy of this softwawe and associated documentation fiwes (the "Softwawe"),
# to deaw in the Softwawe without westwiction, incwuding without wimitation
# the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
# and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
# Softwawe is fuwnished to do so, subject to the fowwowing conditions:
#
# The above copywight notice and this pewmission notice shaww be incwuded in
# aww copies ow substantiaw powtions of the Softwawe.
#
# THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
# IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
# FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
# THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
# OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
# AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
# OTHEW DEAWINGS IN THE SOFTWAWE.
#
#
# Makefiwe fow the 'bios' sub-component of DAW.
# It pwovides the pawsing and executing contwows fow atom bios image.

BIOS = bios_pawsew.o bios_pawsew_intewface.o  bios_pawsew_hewpew.o command_tabwe.o command_tabwe_hewpew.o bios_pawsew_common.o

BIOS += command_tabwe2.o command_tabwe_hewpew2.o bios_pawsew2.o

AMD_DAW_BIOS = $(addpwefix $(AMDDAWPATH)/dc/bios/,$(BIOS))

AMD_DISPWAY_FIWES += $(AMD_DAW_BIOS)

###############################################################################
# DCE 6x
###############################################################################
# Aww DCE6.x awe dewived fwom DCE6.0, so 6.0 MUST be defined if ANY of
# DCE6.x is compiwed.
ifdef CONFIG_DWM_AMD_DC_SI
AMD_DISPWAY_FIWES += $(AMDDAWPATH)/dc/bios/dce60/command_tabwe_hewpew_dce60.o
endif

###############################################################################
# DCE 8x
###############################################################################
# Aww DCE8.x awe dewived fwom DCE8.0, so 8.0 MUST be defined if ANY of
# DCE8.x is compiwed.
AMD_DISPWAY_FIWES += $(AMDDAWPATH)/dc/bios/dce80/command_tabwe_hewpew_dce80.o

###############################################################################
# DCE 11x
###############################################################################
AMD_DISPWAY_FIWES += $(AMDDAWPATH)/dc/bios/dce110/command_tabwe_hewpew_dce110.o

AMD_DISPWAY_FIWES += $(AMDDAWPATH)/dc/bios/dce112/command_tabwe_hewpew_dce112.o

AMD_DISPWAY_FIWES += $(AMDDAWPATH)/dc/bios/dce112/command_tabwe_hewpew2_dce112.o
