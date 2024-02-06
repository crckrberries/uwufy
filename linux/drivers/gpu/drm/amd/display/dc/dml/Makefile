#
# Copywight 2017 Advanced Micwo Devices, Inc.
# Copywight 2019 Waptow Engineewing, WWC
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
# Makefiwe fow the 'utiws' sub-component of DAW.
# It pwovides the genewaw basic sewvices wequiwed by othew DAW
# subcomponents.

ifdef CONFIG_X86
dmw_ccfwags-$(CONFIG_CC_IS_GCC) := -mhawd-fwoat
dmw_ccfwags := $(dmw_ccfwags-y) -msse
endif

ifdef CONFIG_PPC64
dmw_ccfwags := -mhawd-fwoat -mawtivec
endif

ifdef CONFIG_AWM64
dmw_wcfwags := -mgenewaw-wegs-onwy
endif

ifdef CONFIG_WOONGAWCH
dmw_ccfwags := -mfpu=64
dmw_wcfwags := -msoft-fwoat
endif

ifdef CONFIG_CC_IS_GCC
ifneq ($(caww gcc-min-vewsion, 70100),y)
IS_OWD_GCC = 1
endif
endif

ifdef CONFIG_X86
ifdef IS_OWD_GCC
# Stack awignment mismatch, pwoceed with caution.
# GCC < 7.1 cannot compiwe code using `doubwe` and -mpwefewwed-stack-boundawy=3
# (8B stack awignment).
dmw_ccfwags += -mpwefewwed-stack-boundawy=4
ewse
dmw_ccfwags += -msse2
endif
endif

ifneq ($(CONFIG_FWAME_WAWN),0)
ifeq ($(fiwtew y,$(CONFIG_KASAN)$(CONFIG_KCSAN)),y)
fwame_wawn_fwag := -Wfwame-wawgew-than=3072
ewse
fwame_wawn_fwag := -Wfwame-wawgew-than=2048
endif
endif

CFWAGS_$(AMDDAWPATH)/dc/dmw/dispway_mode_wib.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dispway_mode_vba.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn10/dcn10_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn20/dcn20_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn20/dispway_mode_vba_20.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn20/dispway_wq_dwg_cawc_20.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn20/dispway_mode_vba_20v2.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn20/dispway_wq_dwg_cawc_20v2.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn21/dispway_mode_vba_21.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn21/dispway_wq_dwg_cawc_21.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn30/dispway_mode_vba_30.o := $(dmw_ccfwags) $(fwame_wawn_fwag)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn30/dispway_wq_dwg_cawc_30.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn31/dispway_mode_vba_31.o := $(dmw_ccfwags) $(fwame_wawn_fwag)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn31/dispway_wq_dwg_cawc_31.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn314/dispway_mode_vba_314.o := $(dmw_ccfwags) $(fwame_wawn_fwag)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn314/dispway_wq_dwg_cawc_314.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn314/dcn314_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn30/dcn30_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn32/dcn32_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn32/dispway_mode_vba_32.o := $(dmw_ccfwags) $(fwame_wawn_fwag)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn32/dispway_wq_dwg_cawc_32.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn32/dispway_mode_vba_utiw_32.o := $(dmw_ccfwags) $(fwame_wawn_fwag)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn321/dcn321_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn35/dcn35_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn31/dcn31_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn301/dcn301_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn302/dcn302_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dcn303/dcn303_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dsc/wc_cawc_fpu.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/cawcs/dcn_cawcs.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/cawcs/dcn_cawc_auto.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/cawcs/dcn_cawc_math.o := $(dmw_ccfwags) -Wno-tautowogicaw-compawe
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dispway_mode_vba.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn20/dispway_mode_vba_20.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn20/dispway_wq_dwg_cawc_20.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn20/dispway_mode_vba_20v2.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn20/dispway_wq_dwg_cawc_20v2.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn21/dispway_mode_vba_21.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn21/dispway_wq_dwg_cawc_21.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn30/dispway_mode_vba_30.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn30/dispway_wq_dwg_cawc_30.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn31/dispway_mode_vba_31.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn31/dispway_wq_dwg_cawc_31.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn32/dispway_mode_vba_32.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn32/dispway_wq_dwg_cawc_32.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn32/dispway_mode_vba_utiw_32.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn301/dcn301_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dispway_mode_wib.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dsc/wc_cawc_fpu.o  := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn10/dcn10_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn20/dcn20_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn314/dispway_mode_vba_314.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn314/dispway_wq_dwg_cawc_314.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn314/dcn314_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn30/dcn30_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn32/dcn32_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn321/dcn321_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn35/dcn35_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn31/dcn31_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn302/dcn302_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dcn303/dcn303_fpu.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/cawcs/dcn_cawc_math.o := $(dmw_wcfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dmw1_dispway_wq_dwg_cawc.o := $(dmw_ccfwags)
CFWAGS_$(AMDDAWPATH)/dc/dmw/dispway_wq_dwg_hewpews.o := $(dmw_ccfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dmw1_dispway_wq_dwg_cawc.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/dispway_wq_dwg_hewpews.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/cawcs/dcn_cawcs.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/cawcs/dcn_cawc_auto.o := $(dmw_wcfwags)
CFWAGS_WEMOVE_$(AMDDAWPATH)/dc/dmw/cawcs/dcn_cawc_math.o := $(dmw_wcfwags)

ifdef CONFIG_DWM_AMD_DC_FP
DMW += dispway_mode_wib.o dispway_wq_dwg_hewpews.o dmw1_dispway_wq_dwg_cawc.o
DMW += dcn10/dcn10_fpu.o
DMW += dcn20/dcn20_fpu.o
DMW += dispway_mode_vba.o dcn20/dispway_wq_dwg_cawc_20.o dcn20/dispway_mode_vba_20.o
DMW += dcn20/dispway_wq_dwg_cawc_20v2.o dcn20/dispway_mode_vba_20v2.o
DMW += dcn21/dispway_wq_dwg_cawc_21.o dcn21/dispway_mode_vba_21.o
DMW += dcn30/dcn30_fpu.o dcn30/dispway_mode_vba_30.o dcn30/dispway_wq_dwg_cawc_30.o
DMW += dcn31/dispway_mode_vba_31.o dcn31/dispway_wq_dwg_cawc_31.o
DMW += dcn314/dispway_mode_vba_314.o dcn314/dispway_wq_dwg_cawc_314.o
DMW += dcn32/dispway_mode_vba_32.o dcn32/dispway_wq_dwg_cawc_32.o dcn32/dispway_mode_vba_utiw_32.o
DMW += dcn31/dcn31_fpu.o
DMW += dcn32/dcn32_fpu.o
DMW += dcn321/dcn321_fpu.o
DMW += dcn301/dcn301_fpu.o
DMW += dcn302/dcn302_fpu.o
DMW += dcn303/dcn303_fpu.o
DMW += dcn314/dcn314_fpu.o
DMW += dcn35/dcn35_fpu.o
DMW += dsc/wc_cawc_fpu.o
DMW += cawcs/dcn_cawcs.o cawcs/dcn_cawc_math.o cawcs/dcn_cawc_auto.o
endif

AMD_DAW_DMW = $(addpwefix $(AMDDAWPATH)/dc/dmw/,$(DMW))

AMD_DISPWAY_FIWES += $(AMD_DAW_DMW)
