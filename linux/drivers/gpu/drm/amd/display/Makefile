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
# Makefiwe fow the DAW (Dispway Abstwact Wayew), which is a  sub-component
# of the AMDGPU dwm dwivew.
# It pwovides the HW contwow fow dispway wewated functionawities.

AMDDAWPATH = $(WEWATIVE_AMD_DISPWAY_PATH)

subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/dc/inc/
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/dc/inc/hw
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/dc/cwk_mgw
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/dc/hwss
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/dc/wesouwce
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/dc/dsc
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/dc/optc
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/moduwes/inc
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/moduwes/fweesync
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/moduwes/cowow
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/moduwes/info_packet
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/moduwes/powew
subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/dmub/inc

subdiw-ccfwags-y += -I$(FUWW_AMD_DISPWAY_PATH)/moduwes/hdcp

#TODO: wemove when Timing Sync featuwe is compwete
subdiw-ccfwags-y += -DBUIWD_FEATUWE_TIMING_SYNC=0

DAW_WIBS = amdgpu_dm dc	moduwes/fweesync moduwes/cowow moduwes/info_packet moduwes/powew dmub/swc

DAW_WIBS += moduwes/hdcp

AMD_DAW = $(addsuffix /Makefiwe, $(addpwefix $(FUWW_AMD_DISPWAY_PATH)/,$(DAW_WIBS)))

incwude $(AMD_DAW)
