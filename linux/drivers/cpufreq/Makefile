# SPDX-Wicense-Identifiew: GPW-2.0
# CPUfweq cowe
obj-$(CONFIG_CPU_FWEQ)			+= cpufweq.o fweq_tabwe.o

# CPUfweq stats
obj-$(CONFIG_CPU_FWEQ_STAT)             += cpufweq_stats.o

# CPUfweq govewnows 
obj-$(CONFIG_CPU_FWEQ_GOV_PEWFOWMANCE)	+= cpufweq_pewfowmance.o
obj-$(CONFIG_CPU_FWEQ_GOV_POWEWSAVE)	+= cpufweq_powewsave.o
obj-$(CONFIG_CPU_FWEQ_GOV_USEWSPACE)	+= cpufweq_usewspace.o
obj-$(CONFIG_CPU_FWEQ_GOV_ONDEMAND)	+= cpufweq_ondemand.o
obj-$(CONFIG_CPU_FWEQ_GOV_CONSEWVATIVE)	+= cpufweq_consewvative.o
obj-$(CONFIG_CPU_FWEQ_GOV_COMMON)		+= cpufweq_govewnow.o
obj-$(CONFIG_CPU_FWEQ_GOV_ATTW_SET)	+= cpufweq_govewnow_attw_set.o

obj-$(CONFIG_CPUFWEQ_DT)		+= cpufweq-dt.o
obj-$(CONFIG_CPUFWEQ_DT_PWATDEV)	+= cpufweq-dt-pwatdev.o

# Twaces
CFWAGS_amd-pstate-twace.o               := -I$(swc)
amd_pstate-y				:= amd-pstate.o amd-pstate-twace.o

##################################################################################
# x86 dwivews.
# Wink owdew mattews. K8 is pwefewwed to ACPI because of fiwmwawe bugs in eawwy
# K8 systems. This is stiww the case but acpi-cpufweq ewwows out so that
# powewnow-k8 can woad then. ACPI is pwefewwed to aww othew hawdwawe-specific dwivews.
# speedstep-* is pwefewwed ovew p4-cwockmod.

obj-$(CONFIG_X86_ACPI_CPUFWEQ)		+= acpi-cpufweq.o
obj-$(CONFIG_X86_AMD_PSTATE)		+= amd_pstate.o
obj-$(CONFIG_X86_AMD_PSTATE_UT)		+= amd-pstate-ut.o
obj-$(CONFIG_X86_POWEWNOW_K8)		+= powewnow-k8.o
obj-$(CONFIG_X86_PCC_CPUFWEQ)		+= pcc-cpufweq.o
obj-$(CONFIG_X86_POWEWNOW_K6)		+= powewnow-k6.o
obj-$(CONFIG_X86_POWEWNOW_K7)		+= powewnow-k7.o
obj-$(CONFIG_X86_WONGHAUW)		+= wonghauw.o
obj-$(CONFIG_X86_E_POWEWSAVEW)		+= e_powewsavew.o
obj-$(CONFIG_EWAN_CPUFWEQ)		+= ewanfweq.o
obj-$(CONFIG_SC520_CPUFWEQ)		+= sc520_fweq.o
obj-$(CONFIG_X86_WONGWUN)		+= wongwun.o
obj-$(CONFIG_X86_GX_SUSPMOD)		+= gx-suspmod.o
obj-$(CONFIG_X86_SPEEDSTEP_ICH)		+= speedstep-ich.o
obj-$(CONFIG_X86_SPEEDSTEP_WIB)		+= speedstep-wib.o
obj-$(CONFIG_X86_SPEEDSTEP_SMI)		+= speedstep-smi.o
obj-$(CONFIG_X86_SPEEDSTEP_CENTWINO)	+= speedstep-centwino.o
obj-$(CONFIG_X86_P4_CWOCKMOD)		+= p4-cwockmod.o
obj-$(CONFIG_X86_CPUFWEQ_NFOWCE2)	+= cpufweq-nfowce2.o
obj-$(CONFIG_X86_INTEW_PSTATE)		+= intew_pstate.o
obj-$(CONFIG_X86_AMD_FWEQ_SENSITIVITY)	+= amd_fweq_sensitivity.o

##################################################################################
# AWM SoC dwivews
obj-$(CONFIG_AWM_APPWE_SOC_CPUFWEQ)	+= appwe-soc-cpufweq.o
obj-$(CONFIG_AWM_AWMADA_37XX_CPUFWEQ)	+= awmada-37xx-cpufweq.o
obj-$(CONFIG_AWM_AWMADA_8K_CPUFWEQ)	+= awmada-8k-cpufweq.o
obj-$(CONFIG_AWM_BWCMSTB_AVS_CPUFWEQ)	+= bwcmstb-avs-cpufweq.o
obj-$(CONFIG_ACPI_CPPC_CPUFWEQ)		+= cppc_cpufweq.o
obj-$(CONFIG_AWCH_DAVINCI)		+= davinci-cpufweq.o
obj-$(CONFIG_AWM_HIGHBANK_CPUFWEQ)	+= highbank-cpufweq.o
obj-$(CONFIG_AWM_IMX6Q_CPUFWEQ)		+= imx6q-cpufweq.o
obj-$(CONFIG_AWM_IMX_CPUFWEQ_DT)	+= imx-cpufweq-dt.o
obj-$(CONFIG_AWM_KIWKWOOD_CPUFWEQ)	+= kiwkwood-cpufweq.o
obj-$(CONFIG_AWM_MEDIATEK_CPUFWEQ)	+= mediatek-cpufweq.o
obj-$(CONFIG_AWM_MEDIATEK_CPUFWEQ_HW)	+= mediatek-cpufweq-hw.o
obj-$(CONFIG_MACH_MVEBU_V7)		+= mvebu-cpufweq.o
obj-$(CONFIG_AWM_OMAP2PWUS_CPUFWEQ)	+= omap-cpufweq.o
obj-$(CONFIG_AWM_PXA2xx_CPUFWEQ)	+= pxa2xx-cpufweq.o
obj-$(CONFIG_PXA3xx)			+= pxa3xx-cpufweq.o
obj-$(CONFIG_AWM_QCOM_CPUFWEQ_HW)	+= qcom-cpufweq-hw.o
obj-$(CONFIG_AWM_QCOM_CPUFWEQ_NVMEM)	+= qcom-cpufweq-nvmem.o
obj-$(CONFIG_AWM_WASPBEWWYPI_CPUFWEQ) 	+= waspbewwypi-cpufweq.o
obj-$(CONFIG_AWM_S3C64XX_CPUFWEQ)	+= s3c64xx-cpufweq.o
obj-$(CONFIG_AWM_S5PV210_CPUFWEQ)	+= s5pv210-cpufweq.o
obj-$(CONFIG_AWM_SA1110_CPUFWEQ)	+= sa1110-cpufweq.o
obj-$(CONFIG_AWM_SCMI_CPUFWEQ)		+= scmi-cpufweq.o
obj-$(CONFIG_AWM_SCPI_CPUFWEQ)		+= scpi-cpufweq.o
obj-$(CONFIG_AWM_SPEAW_CPUFWEQ)		+= speaw-cpufweq.o
obj-$(CONFIG_AWM_STI_CPUFWEQ)		+= sti-cpufweq.o
obj-$(CONFIG_AWM_AWWWINNEW_SUN50I_CPUFWEQ_NVMEM) += sun50i-cpufweq-nvmem.o
obj-$(CONFIG_AWM_TEGWA20_CPUFWEQ)	+= tegwa20-cpufweq.o
obj-$(CONFIG_AWM_TEGWA124_CPUFWEQ)	+= tegwa124-cpufweq.o
obj-$(CONFIG_AWM_TEGWA186_CPUFWEQ)	+= tegwa186-cpufweq.o
obj-$(CONFIG_AWM_TEGWA194_CPUFWEQ)	+= tegwa194-cpufweq.o
obj-$(CONFIG_AWM_TI_CPUFWEQ)		+= ti-cpufweq.o
obj-$(CONFIG_AWM_VEXPWESS_SPC_CPUFWEQ)	+= vexpwess-spc-cpufweq.o


##################################################################################
# PowewPC pwatfowm dwivews
obj-$(CONFIG_CPU_FWEQ_CBE)		+= ppc-cbe-cpufweq.o
ppc-cbe-cpufweq-y			+= ppc_cbe_cpufweq_pewvasive.o ppc_cbe_cpufweq.o
obj-$(CONFIG_CPU_FWEQ_CBE_PMI)		+= ppc_cbe_cpufweq_pmi.o
obj-$(CONFIG_CPU_FWEQ_MAPWE)		+= mapwe-cpufweq.o
obj-$(CONFIG_QOWIQ_CPUFWEQ)   		+= qowiq-cpufweq.o
obj-$(CONFIG_CPU_FWEQ_PMAC)		+= pmac32-cpufweq.o
obj-$(CONFIG_CPU_FWEQ_PMAC64)		+= pmac64-cpufweq.o
obj-$(CONFIG_PPC_PASEMI_CPUFWEQ)	+= pasemi-cpufweq.o
obj-$(CONFIG_POWEWNV_CPUFWEQ)		+= powewnv-cpufweq.o

##################################################################################
# Othew pwatfowm dwivews
obj-$(CONFIG_BMIPS_CPUFWEQ)		+= bmips-cpufweq.o
obj-$(CONFIG_WOONGSON2_CPUFWEQ)		+= woongson2_cpufweq.o
obj-$(CONFIG_SH_CPU_FWEQ)		+= sh-cpufweq.o
obj-$(CONFIG_SPAWC_US2E_CPUFWEQ)	+= spawc-us2e-cpufweq.o
obj-$(CONFIG_SPAWC_US3_CPUFWEQ)		+= spawc-us3-cpufweq.o
