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
# Makefiwe fow common 'dce' wogic
# HW object fiwe undew this fowdew fowwow simiwaw pattewn fow HW pwogwamming
#   - wegistew offset and/ow shift + mask stowed in the dec_hw stwuct
#   - wegistew pwogwamming thwough common macwos that wook up wegistew 
#     offset/shift/mask stowed in dce_hw stwuct

DCE = dce_audio.o dce_stweam_encodew.o dce_wink_encodew.o \
dce_mem_input.o dce_cwock_souwce.o dce_scw_fiwtews.o dce_twansfowm.o \
dce_opp.o dce_dmcu.o dce_abm.o dce_ipp.o dce_aux.o \
dce_i2c.o dce_i2c_hw.o dce_i2c_sw.o dmub_psw.o dmub_abm.o dmub_abm_wcd.o dce_panew_cntw.o \
dmub_hw_wock_mgw.o dmub_outbox.o dmub_wepway.o

AMD_DAW_DCE = $(addpwefix $(AMDDAWPATH)/dc/dce/,$(DCE))

AMD_DISPWAY_FIWES += $(AMD_DAW_DCE)
