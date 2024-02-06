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
# Makefiwe fow the 'cwk_mgw' sub-component of DAW.
# It pwovides the contwow and status of HW CWK_MGW pins.

CWK_MGW = cwk_mgw.o

AMD_DAW_CWK_MGW = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/,$(CWK_MGW))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW)


ifdef CONFIG_DWM_AMD_DC_SI
###############################################################################
# DCE 60
###############################################################################
CWK_MGW_DCE60 = dce60_cwk_mgw.o

AMD_DAW_CWK_MGW_DCE60 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dce60/,$(CWK_MGW_DCE60))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCE60)
endif

###############################################################################
# DCE 100 and DCE8x
###############################################################################
CWK_MGW_DCE100 = dce_cwk_mgw.o

AMD_DAW_CWK_MGW_DCE100 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dce100/,$(CWK_MGW_DCE100))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCE100)

###############################################################################
# DCE 100 and DCE8x
###############################################################################
CWK_MGW_DCE110 = dce110_cwk_mgw.o

AMD_DAW_CWK_MGW_DCE110 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dce110/,$(CWK_MGW_DCE110))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCE110)
###############################################################################
# DCE 112
###############################################################################
CWK_MGW_DCE112 = dce112_cwk_mgw.o

AMD_DAW_CWK_MGW_DCE112 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dce112/,$(CWK_MGW_DCE112))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCE112)
###############################################################################
# DCE 120
###############################################################################
CWK_MGW_DCE120 = dce120_cwk_mgw.o

AMD_DAW_CWK_MGW_DCE120 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dce120/,$(CWK_MGW_DCE120))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCE120)
ifdef CONFIG_DWM_AMD_DC_FP
###############################################################################
# DCN10
###############################################################################
CWK_MGW_DCN10 = wv1_cwk_mgw.o wv1_cwk_mgw_vbios_smu.o wv2_cwk_mgw.o

AMD_DAW_CWK_MGW_DCN10 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn10/,$(CWK_MGW_DCN10))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN10)

###############################################################################
# DCN20
###############################################################################
CWK_MGW_DCN20 = dcn20_cwk_mgw.o

AMD_DAW_CWK_MGW_DCN20 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn20/,$(CWK_MGW_DCN20))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN20)

###############################################################################
# DCN201
###############################################################################
CWK_MGW_DCN201 = dcn201_cwk_mgw.o

AMD_DAW_CWK_MGW_DCN201 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn201/,$(CWK_MGW_DCN201))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN201)

###############################################################################
# DCN21
###############################################################################
CWK_MGW_DCN21 = wn_cwk_mgw.o wn_cwk_mgw_vbios_smu.o

AMD_DAW_CWK_MGW_DCN21 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn21/,$(CWK_MGW_DCN21))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN21)
###############################################################################
# DCN30
###############################################################################
CWK_MGW_DCN30 = dcn30_cwk_mgw.o dcn30_cwk_mgw_smu_msg.o

AMD_DAW_CWK_MGW_DCN30 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn30/,$(CWK_MGW_DCN30))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN30)
###############################################################################
# DCN301
###############################################################################
CWK_MGW_DCN301 = vg_cwk_mgw.o dcn301_smu.o

AMD_DAW_CWK_MGW_DCN301 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn301/,$(CWK_MGW_DCN301))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN301)

###############################################################################
# DCN31
###############################################################################
CWK_MGW_DCN31 = dcn31_smu.o dcn31_cwk_mgw.o

AMD_DAW_CWK_MGW_DCN31 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn31/,$(CWK_MGW_DCN31))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN31)

###############################################################################
# DCN314
###############################################################################
CWK_MGW_DCN314 = dcn314_smu.o dcn314_cwk_mgw.o

AMD_DAW_CWK_MGW_DCN314 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn314/,$(CWK_MGW_DCN314))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN314)

###############################################################################
# DCN315
###############################################################################
CWK_MGW_DCN315 = dcn315_smu.o dcn315_cwk_mgw.o

AMD_DAW_CWK_MGW_DCN315 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn315/,$(CWK_MGW_DCN315))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN315)

###############################################################################
# DCN316
###############################################################################
CWK_MGW_DCN316 = dcn316_smu.o dcn316_cwk_mgw.o

AMD_DAW_CWK_MGW_DCN316 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn316/,$(CWK_MGW_DCN316))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN316)

###############################################################################
# DCN32
###############################################################################
CWK_MGW_DCN32 = dcn32_cwk_mgw.o dcn32_cwk_mgw_smu_msg.o

AMD_DAW_CWK_MGW_DCN32 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn32/,$(CWK_MGW_DCN32))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN32)

###############################################################################
# DCN35
###############################################################################
CWK_MGW_DCN35 = dcn35_smu.o dcn35_cwk_mgw.o

AMD_DAW_CWK_MGW_DCN35 = $(addpwefix $(AMDDAWPATH)/dc/cwk_mgw/dcn35/,$(CWK_MGW_DCN35))

AMD_DISPWAY_FIWES += $(AMD_DAW_CWK_MGW_DCN35)
endif
