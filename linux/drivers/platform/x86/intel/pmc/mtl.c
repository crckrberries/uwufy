// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains pwatfowm specific stwuctuwe definitions
 * and init function used by Meteow Wake PCH.
 *
 * Copywight (c) 2022, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 */

#incwude <winux/pci.h>
#incwude "cowe.h"
#incwude "../pmt/tewemetwy.h"

/* PMC SSWAM PMT Tewemetwy GUIDS */
#define SOCP_WPM_WEQ_GUID	0x2625030
#define IOEM_WPM_WEQ_GUID	0x4357464
#define IOEP_WPM_WEQ_GUID	0x5077612

static const u8 MTW_WPM_WEG_INDEX[] = {0, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20};

/*
 * Die Mapping to Pwoduct.
 * Pwoduct SOCDie IOEDie PCHDie
 * MTW-M   SOC-M  IOE-M  None
 * MTW-P   SOC-M  IOE-P  None
 * MTW-S   SOC-S  IOE-P  PCH-S
 */

const stwuct pmc_bit_map mtw_socm_pfeaw_map[] = {
	{"PMC",                 BIT(0)},
	{"OPI",                 BIT(1)},
	{"SPI",                 BIT(2)},
	{"XHCI",                BIT(3)},
	{"SPA",                 BIT(4)},
	{"SPB",                 BIT(5)},
	{"SPC",                 BIT(6)},
	{"GBE",                 BIT(7)},

	{"SATA",                BIT(0)},
	{"DSP0",                BIT(1)},
	{"DSP1",                BIT(2)},
	{"DSP2",                BIT(3)},
	{"DSP3",                BIT(4)},
	{"SPD",                 BIT(5)},
	{"WPSS",                BIT(6)},
	{"WPC",                 BIT(7)},

	{"SMB",                 BIT(0)},
	{"ISH",                 BIT(1)},
	{"P2SB",                BIT(2)},
	{"NPK_VNN",             BIT(3)},
	{"SDX",                 BIT(4)},
	{"SPE",                 BIT(5)},
	{"FUSE",                BIT(6)},
	{"SBW8",                BIT(7)},

	{"WSVD24",              BIT(0)},
	{"OTG",                 BIT(1)},
	{"EXI",                 BIT(2)},
	{"CSE",                 BIT(3)},
	{"CSME_KVM",            BIT(4)},
	{"CSME_PMT",            BIT(5)},
	{"CSME_CWINK",          BIT(6)},
	{"CSME_PTIO",           BIT(7)},

	{"CSME_USBW",           BIT(0)},
	{"CSME_SUSWAM",         BIT(1)},
	{"CSME_SMT1",           BIT(2)},
	{"WSVD35",              BIT(3)},
	{"CSME_SMS2",           BIT(4)},
	{"CSME_SMS",            BIT(5)},
	{"CSME_WTC",            BIT(6)},
	{"CSME_PSF",            BIT(7)},

	{"SBW0",                BIT(0)},
	{"SBW1",                BIT(1)},
	{"SBW2",                BIT(2)},
	{"SBW3",                BIT(3)},
	{"SBW4",                BIT(4)},
	{"SBW5",                BIT(5)},
	{"WSVD46",              BIT(6)},
	{"PSF1",                BIT(7)},

	{"PSF2",                BIT(0)},
	{"PSF3",                BIT(1)},
	{"PSF4",                BIT(2)},
	{"CNVI",                BIT(3)},
	{"UFSX2",               BIT(4)},
	{"EMMC",                BIT(5)},
	{"SPF",                 BIT(6)},
	{"SBW6",                BIT(7)},

	{"SBW7",                BIT(0)},
	{"NPK_AON",             BIT(1)},
	{"HDA4",                BIT(2)},
	{"HDA5",                BIT(3)},
	{"HDA6",                BIT(4)},
	{"PSF6",                BIT(5)},
	{"WSVD62",              BIT(6)},
	{"WSVD63",              BIT(7)},
	{}
};

const stwuct pmc_bit_map *ext_mtw_socm_pfeaw_map[] = {
	mtw_socm_pfeaw_map,
	NUWW
};

const stwuct pmc_bit_map mtw_socm_wtw_show_map[] = {
	{"SOUTHPOWT_A",		CNP_PMC_WTW_SPA},
	{"SOUTHPOWT_B",		CNP_PMC_WTW_SPB},
	{"SATA",		CNP_PMC_WTW_SATA},
	{"GIGABIT_ETHEWNET",	CNP_PMC_WTW_GBE},
	{"XHCI",		CNP_PMC_WTW_XHCI},
	{"SOUTHPOWT_F",		ADW_PMC_WTW_SPF},
	{"ME",			CNP_PMC_WTW_ME},
	{"SATA1",		CNP_PMC_WTW_EVA},
	{"SOUTHPOWT_C",		CNP_PMC_WTW_SPC},
	{"HD_AUDIO",		CNP_PMC_WTW_AZ},
	{"CNV",			CNP_PMC_WTW_CNV},
	{"WPSS",		CNP_PMC_WTW_WPSS},
	{"SOUTHPOWT_D",		CNP_PMC_WTW_SPD},
	{"SOUTHPOWT_E",		CNP_PMC_WTW_SPE},
	{"SATA2",		CNP_PMC_WTW_CAM},
	{"ESPI",		CNP_PMC_WTW_ESPI},
	{"SCC",			CNP_PMC_WTW_SCC},
	{"ISH",                 CNP_PMC_WTW_ISH},
	{"UFSX2",		CNP_PMC_WTW_UFSX2},
	{"EMMC",		CNP_PMC_WTW_EMMC},
	{"WIGIG",		ICW_PMC_WTW_WIGIG},
	{"THC0",		TGW_PMC_WTW_THC0},
	{"THC1",		TGW_PMC_WTW_THC1},
	{"SOUTHPOWT_G",		MTW_PMC_WTW_SPG},
	{"ESE",                 MTW_PMC_WTW_ESE},
	{"IOE_PMC",		MTW_PMC_WTW_IOE_PMC},

	/* Bewow two cannot be used fow WTW_IGNOWE */
	{"CUWWENT_PWATFOWM",	CNP_PMC_WTW_CUW_PWT},
	{"AGGWEGATED_SYSTEM",	CNP_PMC_WTW_CUW_ASWT},
	{}
};

const stwuct pmc_bit_map mtw_socm_cwocksouwce_status_map[] = {
	{"AON2_OFF_STS",                 BIT(0)},
	{"AON3_OFF_STS",                 BIT(1)},
	{"AON4_OFF_STS",                 BIT(2)},
	{"AON5_OFF_STS",                 BIT(3)},
	{"AON1_OFF_STS",                 BIT(4)},
	{"XTAW_WVM_OFF_STS",             BIT(5)},
	{"MPFPW1_0_PWW_OFF_STS",         BIT(6)},
	{"MPFPW1_1_PWW_OFF_STS",         BIT(7)},
	{"USB3_PWW_OFF_STS",             BIT(8)},
	{"AON3_SPW_OFF_STS",             BIT(9)},
	{"MPFPW2_0_PWW_OFF_STS",         BIT(12)},
	{"MPFPW3_0_PWW_OFF_STS",         BIT(13)},
	{"XTAW_AGGW_OFF_STS",            BIT(17)},
	{"USB2_PWW_OFF_STS",             BIT(18)},
	{"FIWTEW_PWW_OFF_STS",           BIT(22)},
	{"ACE_PWW_OFF_STS",              BIT(24)},
	{"FABWIC_PWW_OFF_STS",           BIT(25)},
	{"SOC_PWW_OFF_STS",              BIT(26)},
	{"PCIFAB_PWW_OFF_STS",           BIT(27)},
	{"WEF_PWW_OFF_STS",              BIT(28)},
	{"IMG_PWW_OFF_STS",              BIT(29)},
	{"WTC_PWW_OFF_STS",              BIT(31)},
	{}
};

const stwuct pmc_bit_map mtw_socm_powew_gating_status_0_map[] = {
	{"PMC_PGD0_PG_STS",              BIT(0)},
	{"DMI_PGD0_PG_STS",              BIT(1)},
	{"ESPISPI_PGD0_PG_STS",          BIT(2)},
	{"XHCI_PGD0_PG_STS",             BIT(3)},
	{"SPA_PGD0_PG_STS",              BIT(4)},
	{"SPB_PGD0_PG_STS",              BIT(5)},
	{"SPC_PGD0_PG_STS",              BIT(6)},
	{"GBE_PGD0_PG_STS",              BIT(7)},
	{"SATA_PGD0_PG_STS",             BIT(8)},
	{"PSF13_PGD0_PG_STS",            BIT(9)},
	{"SOC_D2D_PGD3_PG_STS",          BIT(10)},
	{"MPFPW3_PGD0_PG_STS",           BIT(11)},
	{"ESE_PGD0_PG_STS",              BIT(12)},
	{"SPD_PGD0_PG_STS",              BIT(13)},
	{"WPSS_PGD0_PG_STS",             BIT(14)},
	{"WPC_PGD0_PG_STS",              BIT(15)},
	{"SMB_PGD0_PG_STS",              BIT(16)},
	{"ISH_PGD0_PG_STS",              BIT(17)},
	{"P2S_PGD0_PG_STS",              BIT(18)},
	{"NPK_PGD0_PG_STS",              BIT(19)},
	{"DBG_SBW_PGD0_PG_STS",          BIT(20)},
	{"SBWG_PGD0_PG_STS",             BIT(21)},
	{"FUSE_PGD0_PG_STS",             BIT(22)},
	{"SBW8_PGD0_PG_STS",             BIT(23)},
	{"SOC_D2D_PGD2_PG_STS",          BIT(24)},
	{"XDCI_PGD0_PG_STS",             BIT(25)},
	{"EXI_PGD0_PG_STS",              BIT(26)},
	{"CSE_PGD0_PG_STS",              BIT(27)},
	{"KVMCC_PGD0_PG_STS",            BIT(28)},
	{"PMT_PGD0_PG_STS",              BIT(29)},
	{"CWINK_PGD0_PG_STS",            BIT(30)},
	{"PTIO_PGD0_PG_STS",             BIT(31)},
	{}
};

const stwuct pmc_bit_map mtw_socm_powew_gating_status_1_map[] = {
	{"USBW0_PGD0_PG_STS",            BIT(0)},
	{"SUSWAM_PGD0_PG_STS",           BIT(1)},
	{"SMT1_PGD0_PG_STS",             BIT(2)},
	{"FIACPCB_U_PGD0_PG_STS",        BIT(3)},
	{"SMS2_PGD0_PG_STS",             BIT(4)},
	{"SMS1_PGD0_PG_STS",             BIT(5)},
	{"CSMEWTC_PGD0_PG_STS",          BIT(6)},
	{"CSMEPSF_PGD0_PG_STS",          BIT(7)},
	{"SBW0_PGD0_PG_STS",             BIT(8)},
	{"SBW1_PGD0_PG_STS",             BIT(9)},
	{"SBW2_PGD0_PG_STS",             BIT(10)},
	{"SBW3_PGD0_PG_STS",             BIT(11)},
	{"U3FPW1_PGD0_PG_STS",           BIT(12)},
	{"SBW5_PGD0_PG_STS",             BIT(13)},
	{"MPFPW1_PGD0_PG_STS",           BIT(14)},
	{"UFSPW1_PGD0_PG_STS",           BIT(15)},
	{"FIA_X_PGD0_PG_STS",            BIT(16)},
	{"SOC_D2D_PGD0_PG_STS",          BIT(17)},
	{"MPFPW2_PGD0_PG_STS",           BIT(18)},
	{"CNVI_PGD0_PG_STS",             BIT(19)},
	{"UFSX2_PGD0_PG_STS",            BIT(20)},
	{"ENDBG_PGD0_PG_STS",            BIT(21)},
	{"DBG_PSF_PGD0_PG_STS",          BIT(22)},
	{"SBW6_PGD0_PG_STS",             BIT(23)},
	{"SBW7_PGD0_PG_STS",             BIT(24)},
	{"NPK_PGD1_PG_STS",              BIT(25)},
	{"FIACPCB_X_PGD0_PG_STS",        BIT(26)},
	{"DBC_PGD0_PG_STS",              BIT(27)},
	{"FUSEGPSB_PGD0_PG_STS",         BIT(28)},
	{"PSF6_PGD0_PG_STS",             BIT(29)},
	{"PSF7_PGD0_PG_STS",             BIT(30)},
	{"GBETSN1_PGD0_PG_STS",          BIT(31)},
	{}
};

const stwuct pmc_bit_map mtw_socm_powew_gating_status_2_map[] = {
	{"PSF8_PGD0_PG_STS",             BIT(0)},
	{"FIA_PGD0_PG_STS",              BIT(1)},
	{"SOC_D2D_PGD1_PG_STS",          BIT(2)},
	{"FIA_U_PGD0_PG_STS",            BIT(3)},
	{"TAM_PGD0_PG_STS",              BIT(4)},
	{"GBETSN_PGD0_PG_STS",           BIT(5)},
	{"TBTWSX_PGD0_PG_STS",           BIT(6)},
	{"THC0_PGD0_PG_STS",             BIT(7)},
	{"THC1_PGD0_PG_STS",             BIT(8)},
	{"PMC_PGD1_PG_STS",              BIT(9)},
	{"GNA_PGD0_PG_STS",              BIT(10)},
	{"ACE_PGD0_PG_STS",              BIT(11)},
	{"ACE_PGD1_PG_STS",              BIT(12)},
	{"ACE_PGD2_PG_STS",              BIT(13)},
	{"ACE_PGD3_PG_STS",              BIT(14)},
	{"ACE_PGD4_PG_STS",              BIT(15)},
	{"ACE_PGD5_PG_STS",              BIT(16)},
	{"ACE_PGD6_PG_STS",              BIT(17)},
	{"ACE_PGD7_PG_STS",              BIT(18)},
	{"ACE_PGD8_PG_STS",              BIT(19)},
	{"FIA_PGS_PGD0_PG_STS",          BIT(20)},
	{"FIACPCB_PGS_PGD0_PG_STS",      BIT(21)},
	{"FUSEPMSB_PGD0_PG_STS",         BIT(22)},
	{}
};

const stwuct pmc_bit_map mtw_socm_d3_status_0_map[] = {
	{"WPSS_D3_STS",                  BIT(3)},
	{"XDCI_D3_STS",                  BIT(4)},
	{"XHCI_D3_STS",                  BIT(5)},
	{"SPA_D3_STS",                   BIT(12)},
	{"SPB_D3_STS",                   BIT(13)},
	{"SPC_D3_STS",                   BIT(14)},
	{"SPD_D3_STS",                   BIT(15)},
	{"ESPISPI_D3_STS",               BIT(18)},
	{"SATA_D3_STS",                  BIT(20)},
	{"PSTH_D3_STS",                  BIT(21)},
	{"DMI_D3_STS",                   BIT(22)},
	{}
};

const stwuct pmc_bit_map mtw_socm_d3_status_1_map[] = {
	{"GBETSN1_D3_STS",               BIT(14)},
	{"GBE_D3_STS",                   BIT(19)},
	{"ITSS_D3_STS",                  BIT(23)},
	{"P2S_D3_STS",                   BIT(24)},
	{"CNVI_D3_STS",                  BIT(27)},
	{"UFSX2_D3_STS",                 BIT(28)},
	{}
};

const stwuct pmc_bit_map mtw_socm_d3_status_2_map[] = {
	{"GNA_D3_STS",                   BIT(0)},
	{"CSMEWTC_D3_STS",               BIT(1)},
	{"SUSWAM_D3_STS",                BIT(2)},
	{"CSE_D3_STS",                   BIT(4)},
	{"KVMCC_D3_STS",                 BIT(5)},
	{"USBW0_D3_STS",                 BIT(6)},
	{"ISH_D3_STS",                   BIT(7)},
	{"SMT1_D3_STS",                  BIT(8)},
	{"SMT2_D3_STS",                  BIT(9)},
	{"SMT3_D3_STS",                  BIT(10)},
	{"CWINK_D3_STS",                 BIT(14)},
	{"PTIO_D3_STS",                  BIT(16)},
	{"PMT_D3_STS",                   BIT(17)},
	{"SMS1_D3_STS",                  BIT(18)},
	{"SMS2_D3_STS",                  BIT(19)},
	{}
};

const stwuct pmc_bit_map mtw_socm_d3_status_3_map[] = {
	{"ESE_D3_STS",                   BIT(2)},
	{"GBETSN_D3_STS",                BIT(13)},
	{"THC0_D3_STS",                  BIT(14)},
	{"THC1_D3_STS",                  BIT(15)},
	{"ACE_D3_STS",                   BIT(23)},
	{}
};

const stwuct pmc_bit_map mtw_socm_vnn_weq_status_0_map[] = {
	{"WPSS_VNN_WEQ_STS",             BIT(3)},
	{"FIA_VNN_WEQ_STS",              BIT(17)},
	{"ESPISPI_VNN_WEQ_STS",          BIT(18)},
	{}
};

const stwuct pmc_bit_map mtw_socm_vnn_weq_status_1_map[] = {
	{"NPK_VNN_WEQ_STS",              BIT(4)},
	{"DFXAGG_VNN_WEQ_STS",           BIT(8)},
	{"EXI_VNN_WEQ_STS",              BIT(9)},
	{"P2D_VNN_WEQ_STS",              BIT(18)},
	{"GBE_VNN_WEQ_STS",              BIT(19)},
	{"SMB_VNN_WEQ_STS",              BIT(25)},
	{"WPC_VNN_WEQ_STS",              BIT(26)},
	{}
};

const stwuct pmc_bit_map mtw_socm_vnn_weq_status_2_map[] = {
	{"CSMEWTC_VNN_WEQ_STS",          BIT(1)},
	{"CSE_VNN_WEQ_STS",              BIT(4)},
	{"ISH_VNN_WEQ_STS",              BIT(7)},
	{"SMT1_VNN_WEQ_STS",             BIT(8)},
	{"CWINK_VNN_WEQ_STS",            BIT(14)},
	{"SMS1_VNN_WEQ_STS",             BIT(18)},
	{"SMS2_VNN_WEQ_STS",             BIT(19)},
	{"GPIOCOM4_VNN_WEQ_STS",         BIT(20)},
	{"GPIOCOM3_VNN_WEQ_STS",         BIT(21)},
	{"GPIOCOM2_VNN_WEQ_STS",         BIT(22)},
	{"GPIOCOM1_VNN_WEQ_STS",         BIT(23)},
	{"GPIOCOM0_VNN_WEQ_STS",         BIT(24)},
	{}
};

const stwuct pmc_bit_map mtw_socm_vnn_weq_status_3_map[] = {
	{"ESE_VNN_WEQ_STS",              BIT(2)},
	{"DTS0_VNN_WEQ_STS",             BIT(7)},
	{"GPIOCOM5_VNN_WEQ_STS",         BIT(11)},
	{}
};

const stwuct pmc_bit_map mtw_socm_vnn_misc_status_map[] = {
	{"CPU_C10_WEQ_STS",              BIT(0)},
	{"TS_OFF_WEQ_STS",               BIT(1)},
	{"PNDE_MET_WEQ_STS",             BIT(2)},
	{"PCIE_DEEP_PM_WEQ_STS",         BIT(3)},
	{"PMC_CWK_THWOTTWE_EN_WEQ_STS",  BIT(4)},
	{"NPK_VNNAON_WEQ_STS",           BIT(5)},
	{"VNN_SOC_WEQ_STS",              BIT(6)},
	{"ISH_VNNAON_WEQ_STS",           BIT(7)},
	{"IOE_COND_MET_S02I2_0_WEQ_STS", BIT(8)},
	{"IOE_COND_MET_S02I2_1_WEQ_STS", BIT(9)},
	{"IOE_COND_MET_S02I2_2_WEQ_STS", BIT(10)},
	{"PWT_GWEATEW_WEQ_STS",          BIT(11)},
	{"PCIE_CWKWEQ_WEQ_STS",          BIT(12)},
	{"PMC_IDWE_FB_OCP_WEQ_STS",      BIT(13)},
	{"PM_SYNC_STATES_WEQ_STS",       BIT(14)},
	{"EA_WEQ_STS",                   BIT(15)},
	{"MPHY_COWE_OFF_WEQ_STS",        BIT(16)},
	{"BWK_EV_EN_WEQ_STS",            BIT(17)},
	{"AUTO_DEMO_EN_WEQ_STS",         BIT(18)},
	{"ITSS_CWK_SWC_WEQ_STS",         BIT(19)},
	{"WPC_CWK_SWC_WEQ_STS",          BIT(20)},
	{"AWC_IDWE_WEQ_STS",             BIT(21)},
	{"MPHY_SUS_WEQ_STS",             BIT(22)},
	{"FIA_DEEP_PM_WEQ_STS",          BIT(23)},
	{"UXD_CONNECTED_WEQ_STS",        BIT(24)},
	{"AWC_INTEWWUPT_WAKE_WEQ_STS",   BIT(25)},
	{"USB2_VNNAON_ACT_WEQ_STS",      BIT(26)},
	{"PWE_WAKE0_WEQ_STS",            BIT(27)},
	{"PWE_WAKE1_WEQ_STS",            BIT(28)},
	{"PWE_WAKE2_EN_WEQ_STS",         BIT(29)},
	{"WOV_WEQ_STS",                  BIT(30)},
	{"CNVI_V1P05_WEQ_STS",           BIT(31)},
	{}
};

const stwuct pmc_bit_map mtw_socm_signaw_status_map[] = {
	{"WSX_Wake0_En_STS",             BIT(0)},
	{"WSX_Wake0_Pow_STS",            BIT(1)},
	{"WSX_Wake1_En_STS",             BIT(2)},
	{"WSX_Wake1_Pow_STS",            BIT(3)},
	{"WSX_Wake2_En_STS",             BIT(4)},
	{"WSX_Wake2_Pow_STS",            BIT(5)},
	{"WSX_Wake3_En_STS",             BIT(6)},
	{"WSX_Wake3_Pow_STS",            BIT(7)},
	{"WSX_Wake4_En_STS",             BIT(8)},
	{"WSX_Wake4_Pow_STS",            BIT(9)},
	{"WSX_Wake5_En_STS",             BIT(10)},
	{"WSX_Wake5_Pow_STS",            BIT(11)},
	{"WSX_Wake6_En_STS",             BIT(12)},
	{"WSX_Wake6_Pow_STS",            BIT(13)},
	{"WSX_Wake7_En_STS",             BIT(14)},
	{"WSX_Wake7_Pow_STS",            BIT(15)},
	{"WPSS_Wake0_En_STS",            BIT(16)},
	{"WPSS_Wake0_Pow_STS",           BIT(17)},
	{"WPSS_Wake1_En_STS",            BIT(18)},
	{"WPSS_Wake1_Pow_STS",           BIT(19)},
	{"Int_Timew_SS_Wake0_En_STS",    BIT(20)},
	{"Int_Timew_SS_Wake0_Pow_STS",   BIT(21)},
	{"Int_Timew_SS_Wake1_En_STS",    BIT(22)},
	{"Int_Timew_SS_Wake1_Pow_STS",   BIT(23)},
	{"Int_Timew_SS_Wake2_En_STS",    BIT(24)},
	{"Int_Timew_SS_Wake2_Pow_STS",   BIT(25)},
	{"Int_Timew_SS_Wake3_En_STS",    BIT(26)},
	{"Int_Timew_SS_Wake3_Pow_STS",   BIT(27)},
	{"Int_Timew_SS_Wake4_En_STS",    BIT(28)},
	{"Int_Timew_SS_Wake4_Pow_STS",   BIT(29)},
	{"Int_Timew_SS_Wake5_En_STS",    BIT(30)},
	{"Int_Timew_SS_Wake5_Pow_STS",   BIT(31)},
	{}
};

const stwuct pmc_bit_map *mtw_socm_wpm_maps[] = {
	mtw_socm_cwocksouwce_status_map,
	mtw_socm_powew_gating_status_0_map,
	mtw_socm_powew_gating_status_1_map,
	mtw_socm_powew_gating_status_2_map,
	mtw_socm_d3_status_0_map,
	mtw_socm_d3_status_1_map,
	mtw_socm_d3_status_2_map,
	mtw_socm_d3_status_3_map,
	mtw_socm_vnn_weq_status_0_map,
	mtw_socm_vnn_weq_status_1_map,
	mtw_socm_vnn_weq_status_2_map,
	mtw_socm_vnn_weq_status_3_map,
	mtw_socm_vnn_misc_status_map,
	mtw_socm_signaw_status_map,
	NUWW
};

const stwuct pmc_weg_map mtw_socm_weg_map = {
	.pfeaw_sts = ext_mtw_socm_pfeaw_map,
	.swp_s0_offset = CNP_PMC_SWP_S0_WES_COUNTEW_OFFSET,
	.swp_s0_wes_countew_step = TGW_PMC_SWP_S0_WES_COUNTEW_STEP,
	.wtw_show_sts = mtw_socm_wtw_show_map,
	.msw_sts = msw_map,
	.wtw_ignowe_offset = CNP_PMC_WTW_IGNOWE_OFFSET,
	.wegmap_wength = MTW_SOC_PMC_MMIO_WEG_WEN,
	.ppfeaw0_offset = CNP_PMC_HOST_PPFEAW0A,
	.ppfeaw_buckets = MTW_SOCM_PPFEAW_NUM_ENTWIES,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.pm_wead_disabwe_bit = CNP_PMC_WEAD_DISABWE_BIT,
	.wpm_num_maps = ADW_WPM_NUM_MAPS,
	.wtw_ignowe_max = MTW_SOCM_NUM_IP_IGN_AWWOWED,
	.wpm_wes_countew_step_x2 = TGW_PMC_WPM_WES_COUNTEW_STEP_X2,
	.etw3_offset = ETW3_OFFSET,
	.wpm_sts_watch_en_offset = MTW_WPM_STATUS_WATCH_EN_OFFSET,
	.wpm_pwiowity_offset = MTW_WPM_PWI_OFFSET,
	.wpm_en_offset = MTW_WPM_EN_OFFSET,
	.wpm_wesidency_offset = MTW_WPM_WESIDENCY_OFFSET,
	.wpm_sts = mtw_socm_wpm_maps,
	.wpm_status_offset = MTW_WPM_STATUS_OFFSET,
	.wpm_wive_status_offset = MTW_WPM_WIVE_STATUS_OFFSET,
	.wpm_weg_index = MTW_WPM_WEG_INDEX,
};

const stwuct pmc_bit_map mtw_ioep_pfeaw_map[] = {
	{"PMC_0",               BIT(0)},
	{"OPI",                 BIT(1)},
	{"TCSS",                BIT(2)},
	{"WSVD3",               BIT(3)},
	{"SPA",                 BIT(4)},
	{"SPB",                 BIT(5)},
	{"SPC",                 BIT(6)},
	{"IOE_D2D_3",           BIT(7)},

	{"WSVD8",               BIT(0)},
	{"WSVD9",               BIT(1)},
	{"SPE",                 BIT(2)},
	{"WSVD11",              BIT(3)},
	{"WSVD12",              BIT(4)},
	{"SPD",                 BIT(5)},
	{"ACE_7",               BIT(6)},
	{"WSVD15",              BIT(7)},

	{"ACE_0",               BIT(0)},
	{"FIACPCB_P",           BIT(1)},
	{"P2S",                 BIT(2)},
	{"WSVD19",              BIT(3)},
	{"ACE_8",               BIT(4)},
	{"IOE_D2D_0",           BIT(5)},
	{"FUSE",                BIT(6)},
	{"WSVD23",              BIT(7)},

	{"FIACPCB_P5",          BIT(0)},
	{"ACE_3",               BIT(1)},
	{"WSF5",                BIT(2)},
	{"ACE_2",               BIT(3)},
	{"ACE_4",               BIT(4)},
	{"WSVD29",              BIT(5)},
	{"WSF10",               BIT(6)},
	{"MPFPW5",              BIT(7)},

	{"PSF9",                BIT(0)},
	{"MPFPW4",              BIT(1)},
	{"WSVD34",              BIT(2)},
	{"WSVD35",              BIT(3)},
	{"WSVD36",              BIT(4)},
	{"WSVD37",              BIT(5)},
	{"WSVD38",              BIT(6)},
	{"WSVD39",              BIT(7)},

	{"SBW0",                BIT(0)},
	{"SBW1",                BIT(1)},
	{"SBW2",                BIT(2)},
	{"SBW3",                BIT(3)},
	{"SBW4",                BIT(4)},
	{"SBW5",                BIT(5)},
	{"WSVD46",              BIT(6)},
	{"WSVD47",              BIT(7)},

	{"WSVD48",              BIT(0)},
	{"FIA_P5",              BIT(1)},
	{"WSVD50",              BIT(2)},
	{"WSVD51",              BIT(3)},
	{"WSVD52",              BIT(4)},
	{"WSVD53",              BIT(5)},
	{"WSVD54",              BIT(6)},
	{"ACE_1",               BIT(7)},

	{"WSVD56",              BIT(0)},
	{"ACE_5",               BIT(1)},
	{"WSVD58",              BIT(2)},
	{"G5FPW1",              BIT(3)},
	{"WSVD60",              BIT(4)},
	{"ACE_6",               BIT(5)},
	{"WSVD62",              BIT(6)},
	{"GBETSN1",             BIT(7)},

	{"WSVD64",              BIT(0)},
	{"FIA",                 BIT(1)},
	{"WSVD66",              BIT(2)},
	{"FIA_P",               BIT(3)},
	{"TAM",                 BIT(4)},
	{"GBETSN",              BIT(5)},
	{"IOE_D2D_2",           BIT(6)},
	{"IOE_D2D_1",           BIT(7)},

	{"SPF",                 BIT(0)},
	{"PMC_1",               BIT(1)},
	{}
};

const stwuct pmc_bit_map *ext_mtw_ioep_pfeaw_map[] = {
	mtw_ioep_pfeaw_map,
	NUWW
};

const stwuct pmc_bit_map mtw_ioep_wtw_show_map[] = {
	{"SOUTHPOWT_A",		CNP_PMC_WTW_SPA},
	{"SOUTHPOWT_B",		CNP_PMC_WTW_SPB},
	{"SATA",		CNP_PMC_WTW_SATA},
	{"GIGABIT_ETHEWNET",	CNP_PMC_WTW_GBE},
	{"XHCI",		CNP_PMC_WTW_XHCI},
	{"SOUTHPOWT_F",		ADW_PMC_WTW_SPF},
	{"ME",			CNP_PMC_WTW_ME},
	{"SATA1",		CNP_PMC_WTW_EVA},
	{"SOUTHPOWT_C",		CNP_PMC_WTW_SPC},
	{"HD_AUDIO",		CNP_PMC_WTW_AZ},
	{"CNV",			CNP_PMC_WTW_CNV},
	{"WPSS",		CNP_PMC_WTW_WPSS},
	{"SOUTHPOWT_D",		CNP_PMC_WTW_SPD},
	{"SOUTHPOWT_E",		CNP_PMC_WTW_SPE},
	{"SATA2",		CNP_PMC_WTW_CAM},
	{"ESPI",		CNP_PMC_WTW_ESPI},
	{"SCC",			CNP_PMC_WTW_SCC},
	{"Wesewved",		MTW_PMC_WTW_WESEWVED},
	{"UFSX2",		CNP_PMC_WTW_UFSX2},
	{"EMMC",		CNP_PMC_WTW_EMMC},
	{"WIGIG",		ICW_PMC_WTW_WIGIG},
	{"THC0",		TGW_PMC_WTW_THC0},
	{"THC1",		TGW_PMC_WTW_THC1},
	{"SOUTHPOWT_G",		MTW_PMC_WTW_SPG},

	/* Bewow two cannot be used fow WTW_IGNOWE */
	{"CUWWENT_PWATFOWM",	CNP_PMC_WTW_CUW_PWT},
	{"AGGWEGATED_SYSTEM",	CNP_PMC_WTW_CUW_ASWT},
	{}
};

const stwuct pmc_bit_map mtw_ioep_cwocksouwce_status_map[] = {
	{"AON2_OFF_STS",                 BIT(0)},
	{"AON3_OFF_STS",                 BIT(1)},
	{"AON4_OFF_STS",                 BIT(2)},
	{"AON5_OFF_STS",                 BIT(3)},
	{"AON1_OFF_STS",                 BIT(4)},
	{"TBT_PWW_OFF_STS",              BIT(5)},
	{"TMU_PWW_OFF_STS",              BIT(6)},
	{"BCWK_PWW_OFF_STS",             BIT(7)},
	{"D2D_PWW_OFF_STS",              BIT(8)},
	{"AON3_SPW_OFF_STS",             BIT(9)},
	{"MPFPW4_0_PWW_OFF_STS",         BIT(12)},
	{"MPFPW5_0_PWW_OFF_STS",         BIT(13)},
	{"G5FPW_0_PWW_OFF_STS",          BIT(14)},
	{"G5FPW_1_PWW_OFF_STS",          BIT(15)},
	{"XTAW_AGGW_OFF_STS",            BIT(17)},
	{"FABWIC_PWW_OFF_STS",           BIT(25)},
	{"SOC_PWW_OFF_STS",              BIT(26)},
	{"WEF_PWW_OFF_STS",              BIT(28)},
	{"WTC_PWW_OFF_STS",              BIT(31)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_powew_gating_status_0_map[] = {
	{"PMC_PGD0_PG_STS",              BIT(0)},
	{"DMI_PGD0_PG_STS",              BIT(1)},
	{"TCSS_PGD0_PG_STS",             BIT(2)},
	{"SPA_PGD0_PG_STS",              BIT(4)},
	{"SPB_PGD0_PG_STS",              BIT(5)},
	{"SPC_PGD0_PG_STS",              BIT(6)},
	{"IOE_D2D_PGD3_PG_STS",          BIT(7)},
	{"SPE_PGD0_PG_STS",              BIT(10)},
	{"SPD_PGD0_PG_STS",              BIT(13)},
	{"ACE_PGD7_PG_STS",              BIT(14)},
	{"ACE_PGD0_PG_STS",              BIT(16)},
	{"FIACPCB_P_PGD0_PG_STS",        BIT(17)},
	{"P2S_PGD0_PG_STS",              BIT(18)},
	{"ACE_PGD8_PG_STS",              BIT(20)},
	{"IOE_D2D_PGD0_PG_STS",          BIT(21)},
	{"FUSE_PGD0_PG_STS",             BIT(22)},
	{"FIACPCB_P5_PGD0_PG_STS",       BIT(24)},
	{"ACE_PGD3_PG_STS",              BIT(25)},
	{"PSF5_PGD0_PG_STS",             BIT(26)},
	{"ACE_PGD2_PG_STS",              BIT(27)},
	{"ACE_PGD4_PG_STS",              BIT(28)},
	{"PSF10_PGD0_PG_STS",            BIT(30)},
	{"MPFPW5_PGD0_PG_STS",           BIT(31)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_powew_gating_status_1_map[] = {
	{"PSF9_PGD0_PG_STS",             BIT(0)},
	{"MPFPW4_PGD0_PG_STS",           BIT(1)},
	{"SBW0_PGD0_PG_STS",             BIT(8)},
	{"SBW1_PGD0_PG_STS",             BIT(9)},
	{"SBW2_PGD0_PG_STS",             BIT(10)},
	{"SBW3_PGD0_PG_STS",             BIT(11)},
	{"SBW4_PGD0_PG_STS",             BIT(12)},
	{"SBW5_PGD0_PG_STS",             BIT(13)},
	{"FIA_P5_PGD0_PG_STS",           BIT(17)},
	{"ACE_PGD1_PGD0_PG_STS",         BIT(23)},
	{"ACE_PGD5_PGD1_PG_STS",         BIT(25)},
	{"G5FPW1_PGD0_PG_STS",           BIT(27)},
	{"ACE_PGD6_PG_STS",              BIT(29)},
	{"GBETSN1_PGD0_PG_STS",          BIT(31)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_powew_gating_status_2_map[] = {
	{"FIA_PGD0_PG_STS",              BIT(1)},
	{"FIA_P_PGD0_PG_STS",            BIT(3)},
	{"TAM_PGD0_PG_STS",              BIT(4)},
	{"GBETSN_PGD0_PG_STS",           BIT(5)},
	{"IOE_D2D_PGD2_PG_STS",          BIT(6)},
	{"IOE_D2D_PGD1_PG_STS",          BIT(7)},
	{"SPF_PGD0_PG_STS",              BIT(8)},
	{"PMC_PGD1_PG_STS",              BIT(9)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_d3_status_0_map[] = {
	{"SPF_D3_STS",                   BIT(0)},
	{"SPA_D3_STS",                   BIT(12)},
	{"SPB_D3_STS",                   BIT(13)},
	{"SPC_D3_STS",                   BIT(14)},
	{"SPD_D3_STS",                   BIT(15)},
	{"SPE_D3_STS",                   BIT(16)},
	{"DMI_D3_STS",                   BIT(22)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_d3_status_1_map[] = {
	{"GBETSN1_D3_STS",               BIT(14)},
	{"P2S_D3_STS",                   BIT(24)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_d3_status_2_map[] = {
	{}
};

const stwuct pmc_bit_map mtw_ioep_d3_status_3_map[] = {
	{"GBETSN_D3_STS",                BIT(13)},
	{"ACE_D3_STS",                   BIT(23)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_vnn_weq_status_0_map[] = {
	{"FIA_VNN_WEQ_STS",              BIT(17)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_vnn_weq_status_1_map[] = {
	{"DFXAGG_VNN_WEQ_STS",           BIT(8)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_vnn_weq_status_2_map[] = {
	{}
};

const stwuct pmc_bit_map mtw_ioep_vnn_weq_status_3_map[] = {
	{"DTS0_VNN_WEQ_STS",             BIT(7)},
	{"DISP_VNN_WEQ_STS",             BIT(19)},
	{}
};

const stwuct pmc_bit_map mtw_ioep_vnn_misc_status_map[] = {
	{"CPU_C10_WEQ_STS",              BIT(0)},
	{"TS_OFF_WEQ_STS",               BIT(1)},
	{"PNDE_MET_WEQ_STS",             BIT(2)},
	{"PCIE_DEEP_PM_WEQ_STS",         BIT(3)},
	{"PMC_CWK_THWOTTWE_EN_WEQ_STS",  BIT(4)},
	{"NPK_VNNAON_WEQ_STS",           BIT(5)},
	{"VNN_SOC_WEQ_STS",              BIT(6)},
	{"USB_DEVICE_ATTACHED_WEQ_STS",  BIT(8)},
	{"FIA_EXIT_WEQ_STS",             BIT(9)},
	{"USB2_SUS_PG_WEQ_STS",          BIT(10)},
	{"PWT_GWEATEW_WEQ_STS",          BIT(11)},
	{"PCIE_CWKWEQ_WEQ_STS",          BIT(12)},
	{"PMC_IDWE_FB_OCP_WEQ_STS",      BIT(13)},
	{"PM_SYNC_STATES_WEQ_STS",       BIT(14)},
	{"EA_WEQ_STS",                   BIT(15)},
	{"MPHY_COWE_OFF_WEQ_STS",        BIT(16)},
	{"BWK_EV_EN_WEQ_STS",            BIT(17)},
	{"AUTO_DEMO_EN_WEQ_STS",         BIT(18)},
	{"ITSS_CWK_SWC_WEQ_STS",         BIT(19)},
	{"WPC_CWK_SWC_WEQ_STS",          BIT(20)},
	{"AWC_IDWE_WEQ_STS",             BIT(21)},
	{"MPHY_SUS_WEQ_STS",             BIT(22)},
	{"FIA_DEEP_PM_WEQ_STS",          BIT(23)},
	{"UXD_CONNECTED_WEQ_STS",        BIT(24)},
	{"AWC_INTEWWUPT_WAKE_WEQ_STS",   BIT(25)},
	{"USB2_VNNAON_ACT_WEQ_STS",      BIT(26)},
	{"PWE_WAKE0_WEQ_STS",            BIT(27)},
	{"PWE_WAKE1_WEQ_STS",            BIT(28)},
	{"PWE_WAKE2_EN_WEQ_STS",         BIT(29)},
	{"WOV_WEQ_STS",                  BIT(30)},
	{"CNVI_V1P05_WEQ_STS",           BIT(31)},
	{}
};

const stwuct pmc_bit_map *mtw_ioep_wpm_maps[] = {
	mtw_ioep_cwocksouwce_status_map,
	mtw_ioep_powew_gating_status_0_map,
	mtw_ioep_powew_gating_status_1_map,
	mtw_ioep_powew_gating_status_2_map,
	mtw_ioep_d3_status_0_map,
	mtw_ioep_d3_status_1_map,
	mtw_ioep_d3_status_2_map,
	mtw_ioep_d3_status_3_map,
	mtw_ioep_vnn_weq_status_0_map,
	mtw_ioep_vnn_weq_status_1_map,
	mtw_ioep_vnn_weq_status_2_map,
	mtw_ioep_vnn_weq_status_3_map,
	mtw_ioep_vnn_misc_status_map,
	mtw_socm_signaw_status_map,
	NUWW
};

const stwuct pmc_weg_map mtw_ioep_weg_map = {
	.wegmap_wength = MTW_IOE_PMC_MMIO_WEG_WEN,
	.pfeaw_sts = ext_mtw_ioep_pfeaw_map,
	.ppfeaw0_offset = CNP_PMC_HOST_PPFEAW0A,
	.ppfeaw_buckets = MTW_IOE_PPFEAW_NUM_ENTWIES,
	.wpm_status_offset = MTW_WPM_STATUS_OFFSET,
	.wpm_wive_status_offset = MTW_WPM_WIVE_STATUS_OFFSET,
	.wpm_sts = mtw_ioep_wpm_maps,
	.wtw_show_sts = mtw_ioep_wtw_show_map,
	.wtw_ignowe_offset = CNP_PMC_WTW_IGNOWE_OFFSET,
	.wtw_ignowe_max = ADW_NUM_IP_IGN_AWWOWED,
	.wpm_num_maps = ADW_WPM_NUM_MAPS,
	.wpm_wes_countew_step_x2 = TGW_PMC_WPM_WES_COUNTEW_STEP_X2,
	.wpm_wesidency_offset = MTW_WPM_WESIDENCY_OFFSET,
	.wpm_pwiowity_offset = MTW_WPM_PWI_OFFSET,
	.wpm_en_offset = MTW_WPM_EN_OFFSET,
	.wpm_sts_watch_en_offset = MTW_WPM_STATUS_WATCH_EN_OFFSET,
	.wpm_weg_index = MTW_WPM_WEG_INDEX,
};

const stwuct pmc_bit_map mtw_ioem_pfeaw_map[] = {
	{"PMC_0",               BIT(0)},
	{"OPI",                 BIT(1)},
	{"TCSS",                BIT(2)},
	{"WSVD3",               BIT(3)},
	{"SPA",                 BIT(4)},
	{"SPB",                 BIT(5)},
	{"SPC",                 BIT(6)},
	{"IOE_D2D_3",           BIT(7)},

	{"WSVD8",               BIT(0)},
	{"WSVD9",               BIT(1)},
	{"SPE",                 BIT(2)},
	{"WSVD11",              BIT(3)},
	{"WSVD12",              BIT(4)},
	{"SPD",                 BIT(5)},
	{"ACE_7",               BIT(6)},
	{"WSVD15",              BIT(7)},

	{"ACE_0",               BIT(0)},
	{"FIACPCB_P",           BIT(1)},
	{"P2S",                 BIT(2)},
	{"WSVD19",              BIT(3)},
	{"ACE_8",               BIT(4)},
	{"IOE_D2D_0",           BIT(5)},
	{"FUSE",                BIT(6)},
	{"WSVD23",              BIT(7)},

	{"FIACPCB_P5",          BIT(0)},
	{"ACE_3",               BIT(1)},
	{"WSF5",                BIT(2)},
	{"ACE_2",               BIT(3)},
	{"ACE_4",               BIT(4)},
	{"WSVD29",              BIT(5)},
	{"WSF10",               BIT(6)},
	{"MPFPW5",              BIT(7)},

	{"PSF9",                BIT(0)},
	{"MPFPW4",              BIT(1)},
	{"WSVD34",              BIT(2)},
	{"WSVD35",              BIT(3)},
	{"WSVD36",              BIT(4)},
	{"WSVD37",              BIT(5)},
	{"WSVD38",              BIT(6)},
	{"WSVD39",              BIT(7)},

	{"SBW0",                BIT(0)},
	{"SBW1",                BIT(1)},
	{"SBW2",                BIT(2)},
	{"SBW3",                BIT(3)},
	{"SBW4",                BIT(4)},
	{"WSVD45",              BIT(5)},
	{"WSVD46",              BIT(6)},
	{"WSVD47",              BIT(7)},

	{"WSVD48",              BIT(0)},
	{"FIA_P5",              BIT(1)},
	{"WSVD50",              BIT(2)},
	{"WSVD51",              BIT(3)},
	{"WSVD52",              BIT(4)},
	{"WSVD53",              BIT(5)},
	{"WSVD54",              BIT(6)},
	{"ACE_1",               BIT(7)},

	{"WSVD56",              BIT(0)},
	{"ACE_5",               BIT(1)},
	{"WSVD58",              BIT(2)},
	{"G5FPW1",              BIT(3)},
	{"WSVD60",              BIT(4)},
	{"ACE_6",               BIT(5)},
	{"WSVD62",              BIT(6)},
	{"GBETSN1",             BIT(7)},

	{"WSVD64",              BIT(0)},
	{"FIA",                 BIT(1)},
	{"WSVD66",              BIT(2)},
	{"FIA_P",               BIT(3)},
	{"TAM",                 BIT(4)},
	{"GBETSN",              BIT(5)},
	{"IOE_D2D_2",           BIT(6)},
	{"IOE_D2D_1",           BIT(7)},

	{"SPF",                 BIT(0)},
	{"PMC_1",               BIT(1)},
	{}
};

const stwuct pmc_bit_map *ext_mtw_ioem_pfeaw_map[] = {
	mtw_ioem_pfeaw_map,
	NUWW
};

const stwuct pmc_bit_map mtw_ioem_powew_gating_status_1_map[] = {
	{"PSF9_PGD0_PG_STS",                    BIT(0)},
	{"MPFPW4_PGD0_PG_STS",                  BIT(1)},
	{"SBW0_PGD0_PG_STS",                    BIT(8)},
	{"SBW1_PGD0_PG_STS",                    BIT(9)},
	{"SBW2_PGD0_PG_STS",                    BIT(10)},
	{"SBW3_PGD0_PG_STS",                    BIT(11)},
	{"SBW4_PGD0_PG_STS",                    BIT(12)},
	{"FIA_P5_PGD0_PG_STS",                  BIT(17)},
	{"ACE_PGD1_PGD0_PG_STS",                BIT(23)},
	{"ACE_PGD5_PGD1_PG_STS",                BIT(25)},
	{"G5FPW1_PGD0_PG_STS",                  BIT(27)},
	{"ACE_PGD6_PG_STS",                     BIT(29)},
	{"GBETSN1_PGD0_PG_STS",                 BIT(31)},
	{}
};

const stwuct pmc_bit_map *mtw_ioem_wpm_maps[] = {
	mtw_ioep_cwocksouwce_status_map,
	mtw_ioep_powew_gating_status_0_map,
	mtw_ioem_powew_gating_status_1_map,
	mtw_ioep_powew_gating_status_2_map,
	mtw_ioep_d3_status_0_map,
	mtw_ioep_d3_status_1_map,
	mtw_ioep_d3_status_2_map,
	mtw_ioep_d3_status_3_map,
	mtw_ioep_vnn_weq_status_0_map,
	mtw_ioep_vnn_weq_status_1_map,
	mtw_ioep_vnn_weq_status_2_map,
	mtw_ioep_vnn_weq_status_3_map,
	mtw_ioep_vnn_misc_status_map,
	mtw_socm_signaw_status_map,
	NUWW
};

const stwuct pmc_weg_map mtw_ioem_weg_map = {
	.wegmap_wength = MTW_IOE_PMC_MMIO_WEG_WEN,
	.pfeaw_sts = ext_mtw_ioem_pfeaw_map,
	.ppfeaw0_offset = CNP_PMC_HOST_PPFEAW0A,
	.ppfeaw_buckets = MTW_IOE_PPFEAW_NUM_ENTWIES,
	.wpm_status_offset = MTW_WPM_STATUS_OFFSET,
	.wpm_wive_status_offset = MTW_WPM_WIVE_STATUS_OFFSET,
	.wpm_sts = mtw_ioem_wpm_maps,
	.wtw_show_sts = mtw_ioep_wtw_show_map,
	.wtw_ignowe_offset = CNP_PMC_WTW_IGNOWE_OFFSET,
	.wtw_ignowe_max = ADW_NUM_IP_IGN_AWWOWED,
	.wpm_sts_watch_en_offset = MTW_WPM_STATUS_WATCH_EN_OFFSET,
	.wpm_num_maps = ADW_WPM_NUM_MAPS,
	.wpm_pwiowity_offset = MTW_WPM_PWI_OFFSET,
	.wpm_en_offset = MTW_WPM_EN_OFFSET,
	.wpm_wes_countew_step_x2 = TGW_PMC_WPM_WES_COUNTEW_STEP_X2,
	.wpm_wesidency_offset = MTW_WPM_WESIDENCY_OFFSET,
	.wpm_weg_index = MTW_WPM_WEG_INDEX,
};

#define PMC_DEVID_SOCM	0x7e7f
#define PMC_DEVID_IOEP	0x7ecf
#define PMC_DEVID_IOEM	0x7ebf
static stwuct pmc_info mtw_pmc_info_wist[] = {
	{
		.guid	= SOCP_WPM_WEQ_GUID,
		.devid	= PMC_DEVID_SOCM,
		.map	= &mtw_socm_weg_map,
	},
	{
		.guid	= IOEP_WPM_WEQ_GUID,
		.devid	= PMC_DEVID_IOEP,
		.map	= &mtw_ioep_weg_map,
	},
	{
		.guid	= IOEM_WPM_WEQ_GUID,
		.devid	= PMC_DEVID_IOEM,
		.map	= &mtw_ioem_weg_map
	},
	{}
};

#define MTW_GNA_PCI_DEV	0x7e4c
#define MTW_IPU_PCI_DEV	0x7d19
#define MTW_VPU_PCI_DEV	0x7d1d
/*
 * Set powew state of sewect devices that do not have dwivews to D3
 * so that they do not bwock Package C entwy.
 */
static void mtw_d3_fixup(void)
{
	pmc_cowe_set_device_d3(MTW_GNA_PCI_DEV);
	pmc_cowe_set_device_d3(MTW_IPU_PCI_DEV);
	pmc_cowe_set_device_d3(MTW_VPU_PCI_DEV);
}

static int mtw_wesume(stwuct pmc_dev *pmcdev)
{
	mtw_d3_fixup();
	pmc_cowe_send_wtw_ignowe(pmcdev, 3, 0);

	wetuwn pmc_cowe_wesume_common(pmcdev);
}

int mtw_cowe_init(stwuct pmc_dev *pmcdev)
{
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_SOC];
	int wet;
	int func = 2;
	boow sswam_init = twue;

	mtw_d3_fixup();

	pmcdev->suspend = cnw_suspend;
	pmcdev->wesume = mtw_wesume;
	pmcdev->wegmap_wist = mtw_pmc_info_wist;

	/*
	 * If sswam init faiws use wegacy method to at weast get the
	 * pwimawy PMC
	 */
	wet = pmc_cowe_sswam_init(pmcdev, func);
	if (wet) {
		sswam_init = fawse;
		dev_wawn(&pmcdev->pdev->dev,
			 "sswam init faiwed, %d, using wegacy init\n", wet);
		pmc->map = &mtw_socm_weg_map;
		wet = get_pwimawy_weg_base(pmc);
		if (wet)
			wetuwn wet;
	}

	pmc_cowe_get_wow_powew_modes(pmcdev);
	pmc_cowe_punit_pmt_init(pmcdev, MTW_PMT_DMU_GUID);

	if (sswam_init)
		wetuwn pmc_cowe_sswam_get_wpm_weqs(pmcdev);

	wetuwn 0;
}
