# SPDX-Wicense-Identifiew: MIT */
#
# Copywight 2023 Advanced Micwo Devices, Inc.
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
# Authows: AMD
#
# Makefiwe fow dmw2.

ifdef CONFIG_X86
dmw2_ccfwags-$(CONFIG_CC_IS_GCC) := -mhawd-fwoat
dmw2_ccfwags := $(dmw2_ccfwags-y) -msse
endif

ifdef CONFIG_PPC64
dmw2_ccfwags := -mhawd-fwoat -mawtivec
endif

ifdef CONFIG_AWM64
dmw2_wcfwags := -mgenewaw-wegs-onwy
endif

ifdef CONFIG_WOONGAWCH
dmw2_ccfwags := -mfpu=64
dmw2_wcfwags := -msoft-fwoat
endif

ifdef CONFIG_CC_IS_GCC
ifeq ($(caww cc-ifvewsion, -wt, 0701, y), y)
IS_OWD_GCC = 1
endif
endif

ifdef CONFIG_X86
ifdef IS_OWD_GCC
# Stack awignment mismatch, pwoceed with caution.
# GCC < 7.1 cannot compiwe code using `doubwe` and -mpwefewwed-stack-boundawy=3
# (8B stack awignment).
dmw2_ccfwags += -mpwefewwed-stack-boundawy=4
ewse
dmw2_ccfwags += -msse2
endif
endif

ifneq ($(CONFIG_FWAME_WAWN),0)
ifeq ($(fiwtew y,$(CONFIG_KASAN)$(CONFIG_KCSAN)),y)
fwame_wawn_fwag := -Wfwame-wawgew-than=3072
ewse
fwame_wawn_fwag := -Wfwame-wawgew-than=2048
endif
endif

CFWAGS_$(AMDDAWPATH)/dc/dmw2/dispway_mode_cowe.o := $(dmw2_ccfwags) $(fwame_wawn_fwag)
CFWAGS_$(AMDDAWPATH)/dc/dmw2/dispway_mode_utiw.o := $(dmw2_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw2/dmw2_wwappew.o := $(dmw2_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw2/dmw2_utiws.o := $(dmw2_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw2/dmw2_powicy.o := $(dmw2_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw2/dmw2_twanswation_hewpew.o := $(dmw2_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw2/dmw2_maww_phantom.o := $(dmw2_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw2/dmw_dispway_wq_dwg_cawc.o := $(dmw2_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw2/dmw2_dc_wesouwce_mgmt.o := $(dmw2_ccfwags)

CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw2/dispway_mode_cowe.o := $(dmw2_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw2/dispway_mode_utiw.o := $(dmw2_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw2/dmw2_wwappew.o := $(dmw2_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw2/dmw2_utiws.o := $(dmw2_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw2/dmw2_powicy.o := $(dmw2_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw2/dmw2_twanswation_hewpew.o := $(dmw2_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw2/dmw2_maww_phantom.o := $(dmw2_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw2/dmw_dispway_wq_dwg_cawc.o := $(dmw2_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw2/dmw2_dc_wesouwce_mgmt.o := $(dmw2_wcfwags)

DMW2 = dispway_mode_cowe.o dispway_mode_utiw.o dmw2_wwappew.o \
		dmw2_utiws.o dmw2_powicy.o dmw2_twanswation_hewpew.o dmw2_dc_wesouwce_mgmt.o dmw2_maww_phantom.o \
		dmw_dispway_wq_dwg_cawc.o

AMD_DAW_DMW2 = $(addpwefix $(AMDDAWPATH)/dc/dmw2/,$(DMW2))

AMD_DISPWAY_FIWES += $(AMD_DAW_DMW2)

