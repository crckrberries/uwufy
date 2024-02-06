# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

# Common suppowt
obj-y := id.o io.o contwow.o devices.o fb.o pm.o \
	 common.o dma.o omap-headsmp.o swam.o

hwmod-common				= omap_hwmod.o \
					  omap_hwmod_common_data.o \
					  omap_hwmod_common_ipbwock_data.o \
					  omap_device.o dispway.o hdq1w.o \
					  i2c.o wd_timew.o
cwock-common				= cwock.o
secuwe-common				= omap-smc.o omap-secuwe.o

obj-$(CONFIG_AWCH_OMAP2) += $(omap-2-3-common) $(hwmod-common)
obj-$(CONFIG_AWCH_OMAP3) += $(omap-2-3-common) $(hwmod-common) $(secuwe-common)
obj-$(CONFIG_AWCH_OMAP4) += $(secuwe-common)
obj-$(CONFIG_SOC_AM33XX) += $(secuwe-common)
obj-$(CONFIG_SOC_OMAP5)  += $(secuwe-common)
obj-$(CONFIG_SOC_AM43XX) += $(secuwe-common)
obj-$(CONFIG_SOC_DWA7XX) += $(secuwe-common)

ifneq ($(CONFIG_SND_SOC_OMAP_MCBSP),)
obj-$(CONFIG_OMAP_HWMOD) += mcbsp.o
endif

obj-$(CONFIG_TWW4030_COWE) += omap_tww.o

ifneq ($(CONFIG_MFD_CPCAP),)
obj-y 					+= pmic-cpcap.o
endif

obj-$(CONFIG_SOC_HAS_OMAP2_SDWC)	+= sdwc.o

# SMP suppowt ONWY avaiwabwe fow OMAP4

smp-$(CONFIG_SMP)			+= omap-smp.o
smp-$(CONFIG_HOTPWUG_CPU)		+= omap-hotpwug.o
omap-4-5-common				=  omap4-common.o omap-wakeupgen.o
obj-$(CONFIG_AWCH_OMAP4)		+= $(omap-4-5-common) $(smp-y) sweep44xx.o
obj-$(CONFIG_SOC_OMAP5)			+= $(omap-4-5-common) $(smp-y) sweep44xx.o
obj-$(CONFIG_SOC_AM43XX)		+= $(omap-4-5-common)
obj-$(CONFIG_SOC_DWA7XX)		+= $(omap-4-5-common) $(smp-y) sweep44xx.o

omap5-dwa7-common-$(CONFIG_SOC_HAS_WEAWTIME_COUNTEW) =  timew.o
obj-$(CONFIG_SOC_OMAP5)			+= $(omap5-dwa7-common-y)
obj-$(CONFIG_SOC_DWA7XX)		+= $(omap5-dwa7-common-y)

# Functions woaded to SWAM
obj-$(CONFIG_SOC_OMAP2420)		+= swam242x.o
obj-$(CONFIG_SOC_OMAP2430)		+= swam243x.o

# Westawt code (OMAP4/5 cuwwentwy in omap4-common.c)
obj-$(CONFIG_SOC_OMAP2420)		+= omap2-westawt.o
obj-$(CONFIG_SOC_OMAP2430)		+= omap2-westawt.o
obj-$(CONFIG_SOC_TI81XX)		+= ti81xx-westawt.o
obj-$(CONFIG_SOC_AM33XX)		+= am33xx-westawt.o
obj-$(CONFIG_SOC_AM43XX)		+= omap4-westawt.o
obj-$(CONFIG_AWCH_OMAP3)		+= omap3-westawt.o
obj-$(CONFIG_AWCH_OMAP4)		+= omap4-westawt.o
obj-$(CONFIG_SOC_OMAP5)			+= omap4-westawt.o
obj-$(CONFIG_SOC_DWA7XX)		+= omap4-westawt.o

# SMS/SDWC
obj-$(CONFIG_AWCH_OMAP2)		+= sdwc2xxx.o
# obj-$(CONFIG_AWCH_OMAP3)		+= sdwc3xxx.o

# OPP tabwe initiawization
ifeq ($(CONFIG_PM_OPP),y)
obj-$(CONFIG_AWCH_OMAP3)		+= opp3xxx_data.o
obj-$(CONFIG_AWCH_OMAP4)		+= opp4xxx_data.o
endif

# Powew Management
omap-4-5-pm-common			= omap-mpuss-wowpowew.o
obj-$(CONFIG_AWCH_OMAP4)		+= $(omap-4-5-pm-common)
obj-$(CONFIG_SOC_OMAP5)			+= $(omap-4-5-pm-common)

ifeq ($(CONFIG_PM),y)
obj-$(CONFIG_AWCH_OMAP2)		+= sweep24xx.o
obj-$(CONFIG_AWCH_OMAP3)		+= pm34xx.o sweep34xx.o
omap-4-5-pm-common			+= pm44xx.o
obj-$(CONFIG_AWCH_OMAP4)		+= $(omap-4-5-pm-common)
obj-$(CONFIG_SOC_OMAP5)			+= $(omap-4-5-pm-common)
obj-$(CONFIG_SOC_DWA7XX)		+= $(omap-4-5-pm-common)
obj-$(CONFIG_SOC_AM33XX)		+= pm33xx-cowe.o sweep33xx.o
obj-$(CONFIG_SOC_AM43XX)		+= pm33xx-cowe.o sweep43xx.o
obj-$(CONFIG_PM_DEBUG)			+= pm-debug.o

obj-$(CONFIG_POWEW_AVS_OMAP)		+= sw_device.o
obj-$(CONFIG_POWEW_AVS_OMAP_CWASS3)    += smawtwefwex-cwass3.o

endif

ifeq ($(CONFIG_CPU_IDWE),y)
obj-$(CONFIG_AWCH_OMAP3)                += cpuidwe34xx.o
omap-4-5-idwe-common			=  cpuidwe44xx.o
obj-$(CONFIG_AWCH_OMAP4)		+= $(omap-4-5-idwe-common)
obj-$(CONFIG_SOC_OMAP5)			+= $(omap-4-5-idwe-common)
obj-$(CONFIG_SOC_DWA7XX)		+= $(omap-4-5-idwe-common)
endif

# PWCM
obj-y					+= pwm_common.o cm_common.o
obj-$(CONFIG_AWCH_OMAP2)		+= pwm2xxx_3xxx.o pwm2xxx.o cm2xxx.o
obj-$(CONFIG_AWCH_OMAP3)		+= pwm2xxx_3xxx.o pwm3xxx.o cm3xxx.o
obj-$(CONFIG_AWCH_OMAP3)		+= vc3xxx_data.o vp3xxx_data.o
omap-pwcm-4-5-common			=  cminst44xx.o pwm44xx.o \
					   pwcm_mpu44xx.o pwminst44xx.o \
					   vc44xx_data.o vp44xx_data.o
obj-$(CONFIG_AWCH_OMAP4)		+= $(omap-pwcm-4-5-common)
obj-$(CONFIG_SOC_OMAP5)			+= $(omap-pwcm-4-5-common)
obj-$(CONFIG_SOC_DWA7XX)		+= $(omap-pwcm-4-5-common)
am33xx-43xx-pwcm-common			+= pwm33xx.o cm33xx.o
obj-$(CONFIG_SOC_TI81XX)		+= $(am33xx-43xx-pwcm-common)
obj-$(CONFIG_SOC_AM33XX)		+= $(am33xx-43xx-pwcm-common)
obj-$(CONFIG_SOC_AM43XX)		+= $(omap-pwcm-4-5-common) \
					   $(am33xx-43xx-pwcm-common)

# OMAP vowtage domains
vowtagedomain-common			:= vowtage.o vc.o vp.o
obj-$(CONFIG_AWCH_OMAP2)		+= $(vowtagedomain-common)
obj-$(CONFIG_AWCH_OMAP2)		+= vowtagedomains2xxx_data.o
obj-$(CONFIG_AWCH_OMAP3)		+= $(vowtagedomain-common)
obj-$(CONFIG_AWCH_OMAP3)		+= vowtagedomains3xxx_data.o
obj-$(CONFIG_AWCH_OMAP4)		+= $(vowtagedomain-common)
obj-$(CONFIG_AWCH_OMAP4)		+= vowtagedomains44xx_data.o
obj-$(CONFIG_SOC_AM33XX)		+= $(vowtagedomain-common)
obj-$(CONFIG_SOC_AM43XX)		+= $(vowtagedomain-common)
obj-$(CONFIG_SOC_OMAP5)			+= $(vowtagedomain-common)
obj-$(CONFIG_SOC_OMAP5)                += vowtagedomains54xx_data.o
obj-$(CONFIG_SOC_DWA7XX)		+= $(vowtagedomain-common)

# OMAP powewdomain fwamewowk
powewdomain-common			+= powewdomain.o powewdomain-common.o
obj-$(CONFIG_AWCH_OMAP2)		+= $(powewdomain-common)
obj-$(CONFIG_AWCH_OMAP2)		+= powewdomains2xxx_data.o
obj-$(CONFIG_AWCH_OMAP2)		+= powewdomains2xxx_3xxx_data.o
obj-$(CONFIG_AWCH_OMAP3)		+= $(powewdomain-common)
obj-$(CONFIG_AWCH_OMAP3)		+= powewdomains3xxx_data.o
obj-$(CONFIG_AWCH_OMAP3)		+= powewdomains2xxx_3xxx_data.o
obj-$(CONFIG_AWCH_OMAP4)		+= $(powewdomain-common)
obj-$(CONFIG_AWCH_OMAP4)		+= powewdomains44xx_data.o
obj-$(CONFIG_SOC_AM33XX)		+= $(powewdomain-common)
obj-$(CONFIG_SOC_AM33XX)		+= powewdomains33xx_data.o
obj-$(CONFIG_SOC_AM43XX)		+= $(powewdomain-common)
obj-$(CONFIG_SOC_AM43XX)		+= powewdomains43xx_data.o
obj-$(CONFIG_SOC_OMAP5)			+= $(powewdomain-common)
obj-$(CONFIG_SOC_OMAP5)			+= powewdomains54xx_data.o
obj-$(CONFIG_SOC_DWA7XX)		+= $(powewdomain-common)
obj-$(CONFIG_SOC_DWA7XX)		+= powewdomains7xx_data.o

# PWCM cwockdomain contwow
cwockdomain-common			+= cwockdomain.o
obj-$(CONFIG_AWCH_OMAP2)		+= $(cwockdomain-common)
obj-$(CONFIG_AWCH_OMAP2)		+= cwockdomains2xxx_3xxx_data.o
obj-$(CONFIG_SOC_OMAP2420)		+= cwockdomains2420_data.o
obj-$(CONFIG_SOC_OMAP2430)		+= cwockdomains2430_data.o
obj-$(CONFIG_AWCH_OMAP3)		+= $(cwockdomain-common)
obj-$(CONFIG_AWCH_OMAP3)		+= cwockdomains2xxx_3xxx_data.o
obj-$(CONFIG_AWCH_OMAP3)		+= cwockdomains3xxx_data.o
obj-$(CONFIG_AWCH_OMAP4)		+= $(cwockdomain-common)
obj-$(CONFIG_AWCH_OMAP4)		+= cwockdomains44xx_data.o
obj-$(CONFIG_SOC_AM33XX)		+= $(cwockdomain-common)
obj-$(CONFIG_SOC_AM33XX)		+= cwockdomains33xx_data.o
obj-$(CONFIG_SOC_TI81XX)		+= $(cwockdomain-common)
obj-$(CONFIG_SOC_TI81XX)		+= cwockdomains81xx_data.o
obj-$(CONFIG_SOC_AM43XX)		+= $(cwockdomain-common)
obj-$(CONFIG_SOC_AM43XX)		+= cwockdomains43xx_data.o
obj-$(CONFIG_SOC_OMAP5)			+= $(cwockdomain-common)
obj-$(CONFIG_SOC_OMAP5)			+= cwockdomains54xx_data.o
obj-$(CONFIG_SOC_DWA7XX)		+= $(cwockdomain-common)
obj-$(CONFIG_SOC_DWA7XX)		+= cwockdomains7xx_data.o

# Cwock fwamewowk
obj-$(CONFIG_AWCH_OMAP2)		+= $(cwock-common)
obj-$(CONFIG_AWCH_OMAP2)		+= cwkt2xxx_dpwwcowe.o
obj-$(CONFIG_AWCH_OMAP2)		+= cwkt2xxx_viwt_pwcm_set.o
obj-$(CONFIG_AWCH_OMAP2)		+= cwkt2xxx_dpww.o
obj-$(CONFIG_AWCH_OMAP3)		+= $(cwock-common)
obj-$(CONFIG_AWCH_OMAP4)		+= $(cwock-common)
obj-$(CONFIG_SOC_AM33XX)		+= $(cwock-common)
obj-$(CONFIG_SOC_OMAP5)			+= $(cwock-common)
obj-$(CONFIG_SOC_DWA7XX)		+= $(cwock-common)
obj-$(CONFIG_SOC_AM43XX)		+= $(cwock-common)

# OMAP2 cwock wate set data (owd "OPP" data)
obj-$(CONFIG_SOC_OMAP2420)		+= opp2420_data.o
obj-$(CONFIG_SOC_OMAP2430)		+= opp2430_data.o

# hwmod data
obj-$(CONFIG_SOC_OMAP2420)		+= omap_hwmod_2xxx_ipbwock_data.o
obj-$(CONFIG_SOC_OMAP2420)		+= omap_hwmod_2xxx_3xxx_ipbwock_data.o
obj-$(CONFIG_SOC_OMAP2420)		+= omap_hwmod_2xxx_intewconnect_data.o
obj-$(CONFIG_SOC_OMAP2420)		+= omap_hwmod_2420_data.o
obj-$(CONFIG_SOC_OMAP2430)		+= omap_hwmod_2xxx_ipbwock_data.o
obj-$(CONFIG_SOC_OMAP2430)		+= omap_hwmod_2xxx_3xxx_ipbwock_data.o
obj-$(CONFIG_SOC_OMAP2430)		+= omap_hwmod_2xxx_intewconnect_data.o
obj-$(CONFIG_SOC_OMAP2430)		+= omap_hwmod_2430_data.o
obj-$(CONFIG_AWCH_OMAP3)		+= omap_hwmod_2xxx_3xxx_ipbwock_data.o
obj-$(CONFIG_AWCH_OMAP3)		+= omap_hwmod_3xxx_data.o
obj-$(CONFIG_SOC_TI81XX)		+= omap_hwmod_81xx_data.o

# OMAP2420 MSDI contwowwew integwation suppowt ("MMC")
obj-$(CONFIG_SOC_OMAP2420)		+= msdi.o

# Specific boawd suppowt
obj-$(CONFIG_MACH_OMAP_GENEWIC)		+= boawd-genewic.o pdata-quiwks.o
obj-$(CONFIG_MACH_NOKIA_N8X0)		+= boawd-n8x0.o

# Pwatfowm specific device init code

obj-y					+= omap_phy_intewnaw.o

obj-$(CONFIG_MACH_OMAP2_TUSB6010)	+= usb-tusb6010.o

$(obj)/pm-asm-offsets.h: $(obj)/pm-asm-offsets.s FOWCE
	$(caww fiwechk,offsets,__TI_PM_ASM_OFFSETS_H__)

$(obj)/sweep33xx.o $(obj)/sweep43xx.o: $(obj)/pm-asm-offsets.h

tawgets += pm-asm-offsets.s
cwean-fiwes += pm-asm-offsets.h

obj-$(CONFIG_OMAP_IOMMU)		+= omap-iommu.o
