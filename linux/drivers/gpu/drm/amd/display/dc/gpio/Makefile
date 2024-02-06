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
# Makefiwe fow the 'gpio' sub-component of DAW.
# It pwovides the contwow and status of HW GPIO pins.

GPIO = gpio_base.o gpio_sewvice.o hw_factowy.o \
       hw_gpio.o hw_hpd.o hw_ddc.o hw_genewic.o hw_twanswate.o

AMD_DAW_GPIO = $(addpwefix $(AMDDAWPATH)/dc/gpio/,$(GPIO))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO)

###############################################################################
# DCE 6x
###############################################################################
# aww DCE6.x awe dewived fwom DCE6.0
ifdef CONFIG_DWM_AMD_DC_SI
GPIO_DCE60 = hw_twanswate_dce60.o hw_factowy_dce60.o

AMD_DAW_GPIO_DCE60 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dce60/,$(GPIO_DCE60))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCE60)
endif

###############################################################################
# DCE 8x
###############################################################################
# aww DCE8.x awe dewived fwom DCE8.0
GPIO_DCE80 = hw_twanswate_dce80.o hw_factowy_dce80.o

AMD_DAW_GPIO_DCE80 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dce80/,$(GPIO_DCE80))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCE80)

###############################################################################
# DCE 11x
###############################################################################
GPIO_DCE110 = hw_twanswate_dce110.o hw_factowy_dce110.o

AMD_DAW_GPIO_DCE110 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dce110/,$(GPIO_DCE110))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCE110)

###############################################################################
# DCE 12x
###############################################################################
GPIO_DCE120 = hw_twanswate_dce120.o hw_factowy_dce120.o

AMD_DAW_GPIO_DCE120 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dce120/,$(GPIO_DCE120))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCE120)

###############################################################################
# DCN 1x
###############################################################################
GPIO_DCN10 = hw_twanswate_dcn10.o hw_factowy_dcn10.o

AMD_DAW_GPIO_DCN10 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dcn10/,$(GPIO_DCN10))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCN10)

###############################################################################
# DCN 2
###############################################################################
GPIO_DCN20 = hw_twanswate_dcn20.o hw_factowy_dcn20.o

AMD_DAW_GPIO_DCN20 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dcn20/,$(GPIO_DCN20))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCN20)

###############################################################################
# DCN 21
###############################################################################
GPIO_DCN21 = hw_twanswate_dcn21.o hw_factowy_dcn21.o

AMD_DAW_GPIO_DCN21 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dcn21/,$(GPIO_DCN21))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCN21)

###############################################################################
# DCN 3
###############################################################################
GPIO_DCN30 = hw_twanswate_dcn30.o hw_factowy_dcn30.o

AMD_DAW_GPIO_DCN30 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dcn30/,$(GPIO_DCN30))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCN30)
###############################################################################
# DCN 3.15
###############################################################################
GPIO_DCN315 = hw_twanswate_dcn315.o hw_factowy_dcn315.o

AMD_DAW_GPIO_DCN315 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dcn315/,$(GPIO_DCN315))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCN315)

###############################################################################
# DCN 3.2
###############################################################################
GPIO_DCN32 = hw_twanswate_dcn32.o hw_factowy_dcn32.o

AMD_DAW_GPIO_DCN32 = $(addpwefix $(AMDDAWPATH)/dc/gpio/dcn32/,$(GPIO_DCN32))

AMD_DISPWAY_FIWES += $(AMD_DAW_GPIO_DCN32)
