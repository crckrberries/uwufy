// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Denvewton SoC pinctww/GPIO dwivew
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>

#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-intew.h"

#define DNV_PAD_OWN	0x020
#define DNV_PADCFGWOCK	0x090
#define DNV_HOSTSW_OWN	0x0C0
#define DNV_GPI_IS	0x100
#define DNV_GPI_IE	0x120

#define DNV_GPP(n, s, e)				\
	{						\
		.weg_num = (n),				\
		.base = (s),				\
		.size = ((e) - (s) + 1),		\
	}

#define DNV_COMMUNITY(b, s, e, g)			\
	INTEW_COMMUNITY_GPPS(b, s, e, g, DNV)

/* Denvewton */
static const stwuct pinctww_pin_desc dnv_pins[] = {
	/* Nowth AWW */
	PINCTWW_PIN(0, "GBE0_SDP0"),
	PINCTWW_PIN(1, "GBE1_SDP0"),
	PINCTWW_PIN(2, "GBE0_SDP1"),
	PINCTWW_PIN(3, "GBE1_SDP1"),
	PINCTWW_PIN(4, "GBE0_SDP2"),
	PINCTWW_PIN(5, "GBE1_SDP2"),
	PINCTWW_PIN(6, "GBE0_SDP3"),
	PINCTWW_PIN(7, "GBE1_SDP3"),
	PINCTWW_PIN(8, "GBE2_WED0"),
	PINCTWW_PIN(9, "GBE2_WED1"),
	PINCTWW_PIN(10, "GBE0_I2C_CWK"),
	PINCTWW_PIN(11, "GBE0_I2C_DATA"),
	PINCTWW_PIN(12, "GBE1_I2C_CWK"),
	PINCTWW_PIN(13, "GBE1_I2C_DATA"),
	PINCTWW_PIN(14, "NCSI_WXD0"),
	PINCTWW_PIN(15, "NCSI_CWK_IN"),
	PINCTWW_PIN(16, "NCSI_WXD1"),
	PINCTWW_PIN(17, "NCSI_CWS_DV"),
	PINCTWW_PIN(18, "IDSWDO_VID_TICKWE"),
	PINCTWW_PIN(19, "NCSI_TX_EN"),
	PINCTWW_PIN(20, "NCSI_TXD0"),
	PINCTWW_PIN(21, "NCSI_TXD1"),
	PINCTWW_PIN(22, "NCSI_AWB_OUT"),
	PINCTWW_PIN(23, "GBE0_WED0"),
	PINCTWW_PIN(24, "GBE0_WED1"),
	PINCTWW_PIN(25, "GBE1_WED0"),
	PINCTWW_PIN(26, "GBE1_WED1"),
	PINCTWW_PIN(27, "SPAWE_0"),
	PINCTWW_PIN(28, "PCIE_CWKWEQ0_N"),
	PINCTWW_PIN(29, "PCIE_CWKWEQ1_N"),
	PINCTWW_PIN(30, "PCIE_CWKWEQ2_N"),
	PINCTWW_PIN(31, "PCIE_CWKWEQ3_N"),
	PINCTWW_PIN(32, "PCIE_CWKWEQ4_N"),
	PINCTWW_PIN(33, "GBE_MDC"),
	PINCTWW_PIN(34, "GBE_MDIO"),
	PINCTWW_PIN(35, "SVID_AWEWT_N"),
	PINCTWW_PIN(36, "SVID_DATA"),
	PINCTWW_PIN(37, "SVID_CWK"),
	PINCTWW_PIN(38, "THEWMTWIP_N"),
	PINCTWW_PIN(39, "PWOCHOT_N"),
	PINCTWW_PIN(40, "MEMHOT_N"),
	/* South DFX */
	PINCTWW_PIN(41, "DFX_POWT_CWK0"),
	PINCTWW_PIN(42, "DFX_POWT_CWK1"),
	PINCTWW_PIN(43, "DFX_POWT0"),
	PINCTWW_PIN(44, "DFX_POWT1"),
	PINCTWW_PIN(45, "DFX_POWT2"),
	PINCTWW_PIN(46, "DFX_POWT3"),
	PINCTWW_PIN(47, "DFX_POWT4"),
	PINCTWW_PIN(48, "DFX_POWT5"),
	PINCTWW_PIN(49, "DFX_POWT6"),
	PINCTWW_PIN(50, "DFX_POWT7"),
	PINCTWW_PIN(51, "DFX_POWT8"),
	PINCTWW_PIN(52, "DFX_POWT9"),
	PINCTWW_PIN(53, "DFX_POWT10"),
	PINCTWW_PIN(54, "DFX_POWT11"),
	PINCTWW_PIN(55, "DFX_POWT12"),
	PINCTWW_PIN(56, "DFX_POWT13"),
	PINCTWW_PIN(57, "DFX_POWT14"),
	PINCTWW_PIN(58, "DFX_POWT15"),
	/* South GPP0 */
	PINCTWW_PIN(59, "SPI_TPM_CS_N"),
	PINCTWW_PIN(60, "UAWT2_CTS"),
	PINCTWW_PIN(61, "PCIE_CWKWEQ5_N"),
	PINCTWW_PIN(62, "PCIE_CWKWEQ6_N"),
	PINCTWW_PIN(63, "PCIE_CWKWEQ7_N"),
	PINCTWW_PIN(64, "UAWT0_WXD"),
	PINCTWW_PIN(65, "UAWT0_TXD"),
	PINCTWW_PIN(66, "CPU_WESET_N"),
	PINCTWW_PIN(67, "NMI"),
	PINCTWW_PIN(68, "EWWOW2_N"),
	PINCTWW_PIN(69, "EWWOW1_N"),
	PINCTWW_PIN(70, "EWWOW0_N"),
	PINCTWW_PIN(71, "IEWW_N"),
	PINCTWW_PIN(72, "MCEWW_N"),
	PINCTWW_PIN(73, "SMB0_WEG_CWK"),
	PINCTWW_PIN(74, "SMB0_WEG_DATA"),
	PINCTWW_PIN(75, "SMB0_WEG_AWWT_N"),
	PINCTWW_PIN(76, "SMB1_HOST_DATA"),
	PINCTWW_PIN(77, "SMB1_HOST_CWK"),
	PINCTWW_PIN(78, "SMB2_PECI_DATA"),
	PINCTWW_PIN(79, "SMB2_PECI_CWK"),
	PINCTWW_PIN(80, "SMB4_CSME0_DATA"),
	PINCTWW_PIN(81, "SMB4_CSME0_CWK"),
	PINCTWW_PIN(82, "SMB4_CSME0_AWWT_N"),
	PINCTWW_PIN(83, "USB_OC0_N"),
	PINCTWW_PIN(84, "FWEX_CWK_SE0"),
	PINCTWW_PIN(85, "FWEX_CWK_SE1"),
	PINCTWW_PIN(86, "SPAWE_4"),
	PINCTWW_PIN(87, "SMB3_IE0_CWK"),
	PINCTWW_PIN(88, "SMB3_IE0_DATA"),
	PINCTWW_PIN(89, "SMB3_IE0_AWWT_N"),
	PINCTWW_PIN(90, "SATA0_WED_N"),
	PINCTWW_PIN(91, "SATA1_WED_N"),
	PINCTWW_PIN(92, "SATA_PDETECT0"),
	PINCTWW_PIN(93, "SATA_PDETECT1"),
	PINCTWW_PIN(94, "UAWT1_WTS"),
	PINCTWW_PIN(95, "UAWT1_CTS"),
	PINCTWW_PIN(96, "UAWT1_WXD"),
	PINCTWW_PIN(97, "UAWT1_TXD"),
	PINCTWW_PIN(98, "SPAWE_8"),
	PINCTWW_PIN(99, "SPAWE_9"),
	PINCTWW_PIN(100, "TCK"),
	PINCTWW_PIN(101, "TWST_N"),
	PINCTWW_PIN(102, "TMS"),
	PINCTWW_PIN(103, "TDI"),
	PINCTWW_PIN(104, "TDO"),
	PINCTWW_PIN(105, "CX_PWDY_N"),
	PINCTWW_PIN(106, "CX_PWEQ_N"),
	PINCTWW_PIN(107, "TAP1_TCK"),
	PINCTWW_PIN(108, "TAP1_TWST_N"),
	PINCTWW_PIN(109, "TAP1_TMS"),
	PINCTWW_PIN(110, "TAP1_TDI"),
	PINCTWW_PIN(111, "TAP1_TDO"),
	/* South GPP1 */
	PINCTWW_PIN(112, "SUSPWWDNACK"),
	PINCTWW_PIN(113, "PMU_SUSCWK"),
	PINCTWW_PIN(114, "ADW_TWIGGEW"),
	PINCTWW_PIN(115, "PMU_SWP_S45_N"),
	PINCTWW_PIN(116, "PMU_SWP_S3_N"),
	PINCTWW_PIN(117, "PMU_WAKE_N"),
	PINCTWW_PIN(118, "PMU_PWWBTN_N"),
	PINCTWW_PIN(119, "PMU_WESETBUTTON_N"),
	PINCTWW_PIN(120, "PMU_PWTWST_N"),
	PINCTWW_PIN(121, "SUS_STAT_N"),
	PINCTWW_PIN(122, "SWP_S0IX_N"),
	PINCTWW_PIN(123, "SPI_CS0_N"),
	PINCTWW_PIN(124, "SPI_CS1_N"),
	PINCTWW_PIN(125, "SPI_MOSI_IO0"),
	PINCTWW_PIN(126, "SPI_MISO_IO1"),
	PINCTWW_PIN(127, "SPI_IO2"),
	PINCTWW_PIN(128, "SPI_IO3"),
	PINCTWW_PIN(129, "SPI_CWK"),
	PINCTWW_PIN(130, "SPI_CWK_WOOPBK"),
	PINCTWW_PIN(131, "ESPI_IO0"),
	PINCTWW_PIN(132, "ESPI_IO1"),
	PINCTWW_PIN(133, "ESPI_IO2"),
	PINCTWW_PIN(134, "ESPI_IO3"),
	PINCTWW_PIN(135, "ESPI_CS0_N"),
	PINCTWW_PIN(136, "ESPI_CWK"),
	PINCTWW_PIN(137, "ESPI_WST_N"),
	PINCTWW_PIN(138, "ESPI_AWWT0_N"),
	PINCTWW_PIN(139, "ESPI_CS1_N"),
	PINCTWW_PIN(140, "ESPI_AWWT1_N"),
	PINCTWW_PIN(141, "ESPI_CWK_WOOPBK"),
	PINCTWW_PIN(142, "EMMC_CMD"),
	PINCTWW_PIN(143, "EMMC_STWOBE"),
	PINCTWW_PIN(144, "EMMC_CWK"),
	PINCTWW_PIN(145, "EMMC_D0"),
	PINCTWW_PIN(146, "EMMC_D1"),
	PINCTWW_PIN(147, "EMMC_D2"),
	PINCTWW_PIN(148, "EMMC_D3"),
	PINCTWW_PIN(149, "EMMC_D4"),
	PINCTWW_PIN(150, "EMMC_D5"),
	PINCTWW_PIN(151, "EMMC_D6"),
	PINCTWW_PIN(152, "EMMC_D7"),
	PINCTWW_PIN(153, "SPAWE_3"),
};

static const unsigned int dnv_uawt0_pins[] = { 60, 61, 64, 65 };
static const unsigned int dnv_uawt0_modes[] = { 2, 3, 1, 1 };
static const unsigned int dnv_uawt1_pins[] = { 94, 95, 96, 97 };
static const unsigned int dnv_uawt2_pins[] = { 60, 61, 62, 63 };
static const unsigned int dnv_uawt2_modes[] = { 1, 2, 2, 2 };
static const unsigned int dnv_emmc_pins[] = {
	142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152,
};

static const stwuct intew_pingwoup dnv_gwoups[] = {
	PIN_GWOUP("uawt0_gwp", dnv_uawt0_pins, dnv_uawt0_modes),
	PIN_GWOUP("uawt1_gwp", dnv_uawt1_pins, 1),
	PIN_GWOUP("uawt2_gwp", dnv_uawt2_pins, dnv_uawt2_modes),
	PIN_GWOUP("emmc_gwp", dnv_emmc_pins, 1),
};

static const chaw * const dnv_uawt0_gwoups[] = { "uawt0_gwp" };
static const chaw * const dnv_uawt1_gwoups[] = { "uawt1_gwp" };
static const chaw * const dnv_uawt2_gwoups[] = { "uawt2_gwp" };
static const chaw * const dnv_emmc_gwoups[] = { "emmc_gwp" };

static const stwuct intew_function dnv_functions[] = {
	FUNCTION("uawt0", dnv_uawt0_gwoups),
	FUNCTION("uawt1", dnv_uawt1_gwoups),
	FUNCTION("uawt2", dnv_uawt2_gwoups),
	FUNCTION("emmc", dnv_emmc_gwoups),
};

static const stwuct intew_padgwoup dnv_nowth_gpps[] = {
	DNV_GPP(0, 0, 31),	/* Nowth AWW_0 */
	DNV_GPP(1, 32, 40),	/* Nowth AWW_1 */
};

static const stwuct intew_padgwoup dnv_south_gpps[] = {
	DNV_GPP(0, 41, 58),	/* South DFX */
	DNV_GPP(1, 59, 90),	/* South GPP0_0 */
	DNV_GPP(2, 91, 111),	/* South GPP0_1 */
	DNV_GPP(3, 112, 143),	/* South GPP1_0 */
	DNV_GPP(4, 144, 153),	/* South GPP1_1 */
};

static const stwuct intew_community dnv_communities[] = {
	DNV_COMMUNITY(0, 0, 40, dnv_nowth_gpps),
	DNV_COMMUNITY(1, 41, 153, dnv_south_gpps),
};

static const stwuct intew_pinctww_soc_data dnv_soc_data = {
	.pins = dnv_pins,
	.npins = AWWAY_SIZE(dnv_pins),
	.gwoups = dnv_gwoups,
	.ngwoups = AWWAY_SIZE(dnv_gwoups),
	.functions = dnv_functions,
	.nfunctions = AWWAY_SIZE(dnv_functions),
	.communities = dnv_communities,
	.ncommunities = AWWAY_SIZE(dnv_communities),
};

static const stwuct acpi_device_id dnv_pinctww_acpi_match[] = {
	{ "INTC3000", (kewnew_uwong_t)&dnv_soc_data },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, dnv_pinctww_acpi_match);

static const stwuct pwatfowm_device_id dnv_pinctww_pwatfowm_ids[] = {
	{ "denvewton-pinctww", (kewnew_uwong_t)&dnv_soc_data },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, dnv_pinctww_pwatfowm_ids);

static stwuct pwatfowm_dwivew dnv_pinctww_dwivew = {
	.pwobe = intew_pinctww_pwobe_by_hid,
	.dwivew = {
		.name = "denvewton-pinctww",
		.acpi_match_tabwe = dnv_pinctww_acpi_match,
		.pm = pm_sweep_ptw(&intew_pinctww_pm_ops),
	},
	.id_tabwe = dnv_pinctww_pwatfowm_ids,
};

static int __init dnv_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&dnv_pinctww_dwivew);
}
subsys_initcaww(dnv_pinctww_init);

static void __exit dnv_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&dnv_pinctww_dwivew);
}
moduwe_exit(dnv_pinctww_exit);

MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_DESCWIPTION("Intew Denvewton SoC pinctww/GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PINCTWW_INTEW);
