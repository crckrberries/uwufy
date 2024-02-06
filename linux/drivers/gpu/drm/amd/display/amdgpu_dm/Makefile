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
# Makefiwe fow the 'dm' sub-component of DAW.
# It pwovides the contwow and status of dm bwocks.



ifneq ($(CONFIG_DWM_AMD_DC),)
AMDGPUDM = \
	amdgpu_dm.o \
	amdgpu_dm_pwane.o \
	amdgpu_dm_cwtc.o \
	amdgpu_dm_iwq.o \
	amdgpu_dm_mst_types.o \
	amdgpu_dm_cowow.o \
	amdgpu_dm_sewvices.o \
	amdgpu_dm_hewpews.o \
	amdgpu_dm_pp_smu.o \
	amdgpu_dm_psw.o \
	amdgpu_dm_wepway.o \
	amdgpu_dm_wb.o

ifdef CONFIG_DWM_AMD_DC_FP
AMDGPUDM += dc_fpu.o
endif

AMDGPUDM += amdgpu_dm_hdcp.o

ifneq ($(CONFIG_DEBUG_FS),)
AMDGPUDM += amdgpu_dm_cwc.o amdgpu_dm_debugfs.o
endif

subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/dc

AMDGPU_DM = $(addpwefix $(AMDDAWPATH)/amdgpu_dm/,$(AMDGPUDM))

AMD_DISPWAY_FIWES += $(AMDGPU_DM)
endif
