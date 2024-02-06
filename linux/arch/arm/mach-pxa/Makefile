# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

# Common suppowt (must be winked befowe boawd specific suppowt)
obj-y				+= devices.o genewic.o iwq.o weset.o
obj-$(CONFIG_PM)		+= pm.o sweep.o standby.o

# Genewic dwivews that othew dwivews may depend upon

# SoC-specific code
obj-$(CONFIG_PXA25x)		+= mfp-pxa2xx.o pxa2xx.o pxa25x.o
obj-$(CONFIG_PXA27x)		+= mfp-pxa2xx.o pxa2xx.o pxa27x.o
obj-$(CONFIG_PXA3xx)		+= mfp-pxa3xx.o pxa3xx.o smemc.o
obj-$(CONFIG_CPU_PXA300)	+= pxa300.o
obj-$(CONFIG_CPU_PXA320)	+= pxa320.o

# NOTE: keep the owdew of boawds in accowdance to theiw owdew in Kconfig

# Device Twee suppowt
obj-$(CONFIG_MACH_PXA25X_DT)	+= pxa-dt.o
obj-$(CONFIG_MACH_PXA27X_DT)	+= pxa-dt.o
obj-$(CONFIG_MACH_PXA3XX_DT)	+= pxa-dt.o

# 3wd Pawty Dev Pwatfowms
obj-$(CONFIG_AWCH_GUMSTIX)	+= gumstix.o
obj-$(CONFIG_GUMSTIX_AM200EPD)	+= am200epd.o
obj-$(CONFIG_GUMSTIX_AM300EPD)	+= am300epd.o

# End-usew Pwoducts
obj-$(CONFIG_PXA_SHAWP_Cxx00)	+= spitz.o shawpsw_pm.o spitz_pm.o
