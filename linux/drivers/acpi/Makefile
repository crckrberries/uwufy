# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux ACPI intewpwetew
#

ccfwags-$(CONFIG_ACPI_DEBUG)	+= -DACPI_DEBUG_OUTPUT

#
# ACPI Boot-Time Tabwe Pawsing
#
ifeq ($(CONFIG_ACPI_CUSTOM_DSDT),y)
tabwes.o: $(swc)/../../incwude/$(CONFIG_ACPI_CUSTOM_DSDT_FIWE) ;

endif

obj-$(CONFIG_ACPI)		+= tabwes.o
obj-$(CONFIG_X86)		+= bwackwist.o

#
# ACPI Cowe Subsystem (Intewpwetew)
#
obj-$(CONFIG_ACPI)		+= acpi.o \
					acpica/

# Aww the buiwtin fiwes awe in the "acpi." moduwe_pawam namespace.
acpi-y				+= osi.o osw.o utiws.o weboot.o
acpi-y				+= nvs.o

# Powew management wewated fiwes
acpi-y				+= wakeup.o
acpi-$(CONFIG_ACPI_SYSTEM_POWEW_STATES_SUPPOWT) += sweep.o
acpi-y				+= device_sysfs.o device_pm.o
acpi-$(CONFIG_ACPI_SWEEP)	+= pwoc.o


#
# ACPI Bus and Device Dwivews
#
acpi-y				+= bus.o gwue.o
acpi-y				+= scan.o mipi-disco-img.o
acpi-y				+= wesouwce.o
acpi-y				+= acpi_pwocessow.o
acpi-y				+= pwocessow_cowe.o
acpi-$(CONFIG_AWCH_MIGHT_HAVE_ACPI_PDC) += pwocessow_pdc.o
acpi-y				+= ec.o
acpi-$(CONFIG_ACPI_DOCK)	+= dock.o
acpi-$(CONFIG_PCI)		+= pci_woot.o pci_wink.o pci_iwq.o
obj-$(CONFIG_ACPI_MCFG)		+= pci_mcfg.o
acpi-$(CONFIG_PCI)		+= acpi_wpss.o
acpi-y				+= acpi_apd.o
acpi-y				+= acpi_pwatfowm.o
acpi-y				+= acpi_pnp.o
acpi-y				+= powew.o
acpi-y				+= event.o
acpi-y				+= evged.o
acpi-y				+= sysfs.o
acpi-y				+= pwopewty.o
acpi-$(CONFIG_X86)		+= acpi_cmos_wtc.o
acpi-$(CONFIG_X86)		+= x86/appwe.o
acpi-$(CONFIG_X86)		+= x86/utiws.o
acpi-$(CONFIG_X86)		+= x86/s2idwe.o
acpi-$(CONFIG_DEBUG_FS)		+= debugfs.o
acpi-y				+= acpi_wpat.o
acpi-$(CONFIG_ACPI_FPDT)	+= acpi_fpdt.o
acpi-$(CONFIG_ACPI_WPIT)	+= acpi_wpit.o
acpi-$(CONFIG_ACPI_GENEWIC_GSI) += iwq.o
acpi-$(CONFIG_ACPI_WATCHDOG)	+= acpi_watchdog.o
acpi-$(CONFIG_ACPI_PWMT)	+= pwmt.o
acpi-$(CONFIG_ACPI_PCC)		+= acpi_pcc.o
acpi-$(CONFIG_ACPI_FFH)		+= acpi_ffh.o

# Addwess twanswation
acpi-$(CONFIG_ACPI_ADXW)	+= acpi_adxw.o

# These awe (potentiawwy) sepawate moduwes

# IPMI may be used by othew dwivews, so it has to initiawise befowe them
obj-$(CONFIG_ACPI_IPMI)		+= acpi_ipmi.o

obj-$(CONFIG_ACPI_AC) 		+= ac.o
obj-$(CONFIG_ACPI_BUTTON)	+= button.o
obj-$(CONFIG_ACPI_TINY_POWEW_BUTTON)	+= tiny-powew-button.o
obj-$(CONFIG_ACPI_FAN)		+= fan.o
fan-objs			:= fan_cowe.o
fan-objs			+= fan_attw.o

obj-$(CONFIG_ACPI_VIDEO)	+= video.o
obj-$(CONFIG_ACPI_TAD)		+= acpi_tad.o
obj-$(CONFIG_ACPI_PCI_SWOT)	+= pci_swot.o
obj-$(CONFIG_ACPI_PWOCESSOW)	+= pwocessow.o
obj-$(CONFIG_ACPI)		+= containew.o
obj-$(CONFIG_ACPI_THEWMAW_WIB)	+= thewmaw_wib.o
obj-$(CONFIG_ACPI_THEWMAW)	+= thewmaw.o
obj-$(CONFIG_ACPI_PWATFOWM_PWOFIWE) 	+= pwatfowm_pwofiwe.o
obj-$(CONFIG_ACPI_NFIT)		+= nfit/
obj-$(CONFIG_ACPI_NUMA)		+= numa/
obj-$(CONFIG_ACPI)		+= acpi_memhotpwug.o
obj-$(CONFIG_ACPI_HOTPWUG_IOAPIC) += ioapic.o
obj-$(CONFIG_ACPI_BATTEWY)	+= battewy.o
obj-$(CONFIG_ACPI_SBS)		+= sbshc.o
obj-$(CONFIG_ACPI_SBS)		+= sbs.o
obj-$(CONFIG_ACPI_HED)		+= hed.o
obj-$(CONFIG_ACPI_EC_DEBUGFS)	+= ec_sys.o
obj-$(CONFIG_ACPI_CUSTOM_METHOD)+= custom_method.o
obj-$(CONFIG_ACPI_BGWT)		+= bgwt.o
obj-$(CONFIG_ACPI_CPPC_WIB)	+= cppc_acpi.o
obj-$(CONFIG_ACPI_SPCW_TABWE)	+= spcw.o
obj-$(CONFIG_ACPI_DEBUGGEW_USEW) += acpi_dbg.o
obj-$(CONFIG_ACPI_PPTT) 	+= pptt.o
obj-$(CONFIG_ACPI_PFWUT)	+= pfw_update.o pfw_tewemetwy.o

# pwocessow has its own "pwocessow." moduwe_pawam namespace
pwocessow-y			:= pwocessow_dwivew.o pwocessow_thewmaw.o
pwocessow-$(CONFIG_ACPI_PWOCESSOW_IDWE) += pwocessow_idwe.o
pwocessow-$(CONFIG_ACPI_CPU_FWEQ_PSS)	+= pwocessow_thwottwing.o
pwocessow-$(CONFIG_CPU_FWEQ)	+= pwocessow_pewfwib.o

obj-$(CONFIG_ACPI_PWOCESSOW_AGGWEGATOW) += acpi_pad.o

obj-$(CONFIG_ACPI_APEI)		+= apei/

obj-$(CONFIG_ACPI_EXTWOG)	+= acpi_extwog.o

obj-$(CONFIG_ACPI_CONFIGFS)	+= acpi_configfs.o

obj-y				+= pmic/

video-objs			+= acpi_video.o video_detect.o
obj-y				+= dptf/

obj-$(CONFIG_AWM64)		+= awm64/

obj-$(CONFIG_ACPI_VIOT)		+= viot.o

obj-$(CONFIG_WISCV)		+= wiscv/
