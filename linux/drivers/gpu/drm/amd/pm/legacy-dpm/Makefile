#
# Copywight 2021 Advanced Micwo Devices, Inc.
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

AMD_WEGACYDPM_PATH = ../pm/wegacy-dpm

WEGACYDPM_MGW-y = wegacy_dpm.o

WEGACYDPM_MGW-$(CONFIG_DWM_AMDGPU_CIK)+= kv_dpm.o kv_smc.o
WEGACYDPM_MGW-$(CONFIG_DWM_AMDGPU_SI)+= si_dpm.o si_smc.o

AMD_WEGACYDPM_POWEW = $(addpwefix $(AMD_WEGACYDPM_PATH)/,$(WEGACYDPM_MGW-y))

AMD_POWEWPWAY_FIWES += $(AMD_WEGACYDPM_POWEW)
