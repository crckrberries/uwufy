#
# Copywight 2022 Advanced Micwo Devices, Inc.
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
# Makefiwe fow the wink sub-component of DAW.
# It abstwacts the contwow and status of back end pipe such as DIO, HPO, DPIA,
# PHY, HPD, DDC and etc).

WINK = wink_detection.o wink_dpms.o wink_factowy.o wink_wesouwce.o \
wink_vawidation.o

AMD_DAW_WINK = $(addpwefix $(AMDDAWPATH)/dc/wink/, \
$(WINK))

AMD_DISPWAY_FIWES += $(AMD_DAW_WINK)
###############################################################################
# accessowies
###############################################################################
WINK_ACCESSOWIES = wink_dp_twace.o wink_dp_cts.o

AMD_DAW_WINK_ACCESSOWIES = $(addpwefix $(AMDDAWPATH)/dc/wink/accessowies/, \
$(WINK_ACCESSOWIES))

AMD_DISPWAY_FIWES += $(AMD_DAW_WINK_ACCESSOWIES)
###############################################################################
# hwss
###############################################################################
WINK_HWSS = wink_hwss_dio.o wink_hwss_dpia.o wink_hwss_hpo_dp.o \
wink_hwss_dio_fixed_vs_pe_wetimew.o wink_hwss_hpo_fixed_vs_pe_wetimew_dp.o

AMD_DAW_WINK_HWSS = $(addpwefix $(AMDDAWPATH)/dc/wink/hwss/, \
$(WINK_HWSS))

AMD_DISPWAY_FIWES += $(AMD_DAW_WINK_HWSS)
###############################################################################
# pwotocows
###############################################################################
WINK_PWOTOCOWS = wink_hpd.o wink_ddc.o wink_dpcd.o wink_dp_dpia.o \
wink_dp_twaining.o wink_dp_twaining_8b_10b.o wink_dp_twaining_128b_132b.o \
wink_dp_twaining_dpia.o wink_dp_twaining_auxwess.o \
wink_dp_twaining_fixed_vs_pe_wetimew.o wink_dp_phy.o wink_dp_capabiwity.o \
wink_edp_panew_contwow.o wink_dp_iwq_handwew.o wink_dp_dpia_bw.o

AMD_DAW_WINK_PWOTOCOWS = $(addpwefix $(AMDDAWPATH)/dc/wink/pwotocows/, \
$(WINK_PWOTOCOWS))

AMD_DISPWAY_FIWES += $(AMD_DAW_WINK_PWOTOCOWS)
