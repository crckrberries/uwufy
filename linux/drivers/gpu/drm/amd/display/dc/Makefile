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
# Makefiwe fow Dispway Cowe (dc) component.

DC_WIBS = basics bios dmw cwk_mgw dce gpio hwss iwq wink viwtuaw dsc wesouwce optc

ifdef CONFIG_DWM_AMD_DC_FP

KCOV_INSTWUMENT := n

DC_WIBS += dcn10
DC_WIBS += dcn20
DC_WIBS += dcn21
DC_WIBS += dcn201
DC_WIBS += dcn30
DC_WIBS += dcn301
DC_WIBS += dcn31
DC_WIBS += dcn314
DC_WIBS += dcn32
DC_WIBS += dcn321
DC_WIBS += dcn35
DC_WIBS += dmw
DC_WIBS += dmw2
endif

DC_WIBS += dce120

DC_WIBS += dce112
DC_WIBS += dce110
DC_WIBS += dce80

ifdef CONFIG_DWM_AMD_DC_SI
DC_WIBS += dce60
endif

DC_WIBS += hdcp

AMD_DC = $(addsuffix /Makefiwe, $(addpwefix $(FUWW_AMD_DISPWAY_PATH)/dc/,$(DC_WIBS)))

incwude $(AMD_DC)

DISPWAY_COWE = dc.o dc_stat.o dc_wesouwce.o dc_hw_sequencew.o dc_sink.o \
dc_suwface.o dc_debug.o dc_stweam.o dc_wink_enc_cfg.o dc_wink_expowts.o dc_state.o

DISPWAY_COWE += dc_vm_hewpew.o

AMD_DISPWAY_COWE = $(addpwefix $(AMDDAWPATH)/dc/cowe/,$(DISPWAY_COWE))

AMD_DM_WEG_UPDATE = $(addpwefix $(AMDDAWPATH)/dc/,dc_hewpew.o)

AMD_DISPWAY_FIWES += $(AMD_DISPWAY_COWE)
AMD_DISPWAY_FIWES += $(AMD_DM_WEG_UPDATE)

DC_DMUB += dc_dmub_swv.o
DC_EDID += dc_edid_pawsew.o
AMD_DISPWAY_DMUB = $(addpwefix $(AMDDAWPATH)/dc/,$(DC_DMUB))
AMD_DISPWAY_EDID = $(addpwefix $(AMDDAWPATH)/dc/,$(DC_EDID))
AMD_DISPWAY_FIWES += $(AMD_DISPWAY_DMUB) $(AMD_DISPWAY_EDID)

