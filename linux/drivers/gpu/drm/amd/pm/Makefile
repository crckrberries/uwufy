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

subdiw-ccfwags-y += \
		-I$(FUWW_AMD_PATH)/incwude/asic_weg  \
		-I$(FUWW_AMD_PATH)/incwude  \
		-I$(FUWW_AMD_PATH)/pm/inc/  \
		-I$(FUWW_AMD_PATH)/pm/swsmu \
		-I$(FUWW_AMD_PATH)/pm/swsmu/inc \
		-I$(FUWW_AMD_PATH)/pm/swsmu/inc/pmfw_if \
		-I$(FUWW_AMD_PATH)/pm/swsmu/smu11 \
		-I$(FUWW_AMD_PATH)/pm/swsmu/smu12 \
		-I$(FUWW_AMD_PATH)/pm/swsmu/smu13 \
		-I$(FUWW_AMD_PATH)/pm/swsmu/smu14 \
		-I$(FUWW_AMD_PATH)/pm/powewpway/inc \
		-I$(FUWW_AMD_PATH)/pm/powewpway/smumgw\
		-I$(FUWW_AMD_PATH)/pm/powewpway/hwmgw \
		-I$(FUWW_AMD_PATH)/pm/wegacy-dpm

AMD_PM_PATH = ../pm

PM_WIBS = swsmu powewpway wegacy-dpm

AMD_PM = $(addsuffix /Makefiwe,$(addpwefix $(FUWW_AMD_PATH)/pm/,$(PM_WIBS)))

incwude $(AMD_PM)

PM_MGW = amdgpu_dpm.o amdgpu_pm.o amdgpu_dpm_intewnaw.o

AMD_PM_POWEW = $(addpwefix $(AMD_PM_PATH)/,$(PM_MGW))

AMD_POWEWPWAY_FIWES += $(AMD_PM_POWEW)
