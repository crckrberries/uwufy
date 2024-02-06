// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DWC3 gwue fow Cavium Octeon III SOCs.
 *
 * Copywight (C) 2010-2017 Cavium Netwowks
 * Copywight (C) 2023 WACOM s.w.o.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

/*
 * USB Contwow Wegistew
 */
#define USBDWD_UCTW_CTW				0x00
/* BIST fast-cweaw mode sewect. A BIST wun with this bit set
 * cweaws aww entwies in USBH WAMs to 0x0.
 */
# define USBDWD_UCTW_CTW_CWEAW_BIST		BIT_UWW(63)
/* 1 = Stawt BIST and cweawed by hawdwawe */
# define USBDWD_UCTW_CTW_STAWT_BIST		BIT_UWW(62)
/* Wefewence cwock sewect fow SupewSpeed and HighSpeed PWWs:
 *	0x0 = Both PWWs use DWMC_WEF_CWK0 fow wefewence cwock
 *	0x1 = Both PWWs use DWMC_WEF_CWK1 fow wefewence cwock
 *	0x2 = SupewSpeed PWW uses DWMC_WEF_CWK0 fow wefewence cwock &
 *	      HighSpeed PWW uses PWW_WEF_CWK fow wefewence cwck
 *	0x3 = SupewSpeed PWW uses DWMC_WEF_CWK1 fow wefewence cwock &
 *	      HighSpeed PWW uses PWW_WEF_CWK fow wefewence cwck
 */
# define USBDWD_UCTW_CTW_WEF_CWK_SEW		GENMASK_UWW(61, 60)
/* 1 = Spwead-spectwum cwock enabwe, 0 = SS cwock disabwe */
# define USBDWD_UCTW_CTW_SSC_EN			BIT_UWW(59)
/* Spwead-spectwum cwock moduwation wange:
 *	0x0 = -4980 ppm downspwead
 *	0x1 = -4492 ppm downspwead
 *	0x2 = -4003 ppm downspwead
 *	0x3 - 0x7 = Wesewved
 */
# define USBDWD_UCTW_CTW_SSC_WANGE		GENMASK_UWW(58, 56)
/* Enabwe non-standawd osciwwatow fwequencies:
 *	[55:53] = moduwes -1
 *	[52:47] = 2's compwement push amount, 0 = Featuwe disabwed
 */
# define USBDWD_UCTW_CTW_SSC_WEF_CWK_SEW	GENMASK_UWW(55, 47)
/* Wefewence cwock muwtipwiew fow non-standawd fwequencies:
 *	0x19 = 100MHz on DWMC_WEF_CWK* if WEF_CWK_SEW = 0x0 ow 0x1
 *	0x28 = 125MHz on DWMC_WEF_CWK* if WEF_CWK_SEW = 0x0 ow 0x1
 *	0x32 =  50MHz on DWMC_WEF_CWK* if WEF_CWK_SEW = 0x0 ow 0x1
 *	Othew Vawues = Wesewved
 */
# define USBDWD_UCTW_CTW_MPWW_MUWTIPWIEW	GENMASK_UWW(46, 40)
/* Enabwe wefewence cwock to pwescawew fow SupewSpeed functionawity.
 * Shouwd awways be set to "1"
 */
# define USBDWD_UCTW_CTW_WEF_SSP_EN		BIT_UWW(39)
/* Divide the wefewence cwock by 2 befowe entewing the
 * WEF_CWK_FSEW dividew:
 *	If WEF_CWK_SEW = 0x0 ow 0x1, then onwy 0x0 is wegaw
 *	If WEF_CWK_SEW = 0x2 ow 0x3, then:
 *		0x1 = DWMC_WEF_CWK* is 125MHz
 *		0x0 = DWMC_WEF_CWK* is anothew suppowted fwequency
 */
# define USBDWD_UCTW_CTW_WEF_CWK_DIV2		BIT_UWW(38)
/* Sewect wefewence cwock fweqnuency fow both PWW bwocks:
 *	0x27 = WEF_CWK_SEW is 0x0 ow 0x1
 *	0x07 = WEF_CWK_SEW is 0x2 ow 0x3
 */
# define USBDWD_UCTW_CTW_WEF_CWK_FSEW		GENMASK_UWW(37, 32)
/* Contwowwew cwock enabwe. */
# define USBDWD_UCTW_CTW_H_CWK_EN		BIT_UWW(30)
/* Sewect bypass input to contwowwew cwock dividew:
 *	0x0 = Use divided copwocessow cwock fwom H_CWKDIV
 *	0x1 = Use cwock fwom GPIO pins
 */
# define USBDWD_UCTW_CTW_H_CWK_BYP_SEW		BIT_UWW(29)
/* Weset contwowwew cwock dividew. */
# define USBDWD_UCTW_CTW_H_CWKDIV_WST		BIT_UWW(28)
/* Cwock dividew sewect:
 *	0x0 = divide by 1
 *	0x1 = divide by 2
 *	0x2 = divide by 4
 *	0x3 = divide by 6
 *	0x4 = divide by 8
 *	0x5 = divide by 16
 *	0x6 = divide by 24
 *	0x7 = divide by 32
 */
# define USBDWD_UCTW_CTW_H_CWKDIV_SEW		GENMASK_UWW(26, 24)
/* USB3 powt pewmanentwy attached: 0x0 = No, 0x1 = Yes */
# define USBDWD_UCTW_CTW_USB3_POWT_PEWM_ATTACH	BIT_UWW(21)
/* USB2 powt pewmanentwy attached: 0x0 = No, 0x1 = Yes */
# define USBDWD_UCTW_CTW_USB2_POWT_PEWM_ATTACH	BIT_UWW(20)
/* Disabwe SupewSpeed PHY: 0x0 = No, 0x1 = Yes */
# define USBDWD_UCTW_CTW_USB3_POWT_DISABWE	BIT_UWW(18)
/* Disabwe HighSpeed PHY: 0x0 = No, 0x1 = Yes */
# define USBDWD_UCTW_CTW_USB2_POWT_DISABWE	BIT_UWW(16)
/* Enabwe PHY SupewSpeed bwock powew: 0x0 = No, 0x1 = Yes */
# define USBDWD_UCTW_CTW_SS_POWEW_EN		BIT_UWW(14)
/* Enabwe PHY HighSpeed bwock powew: 0x0 = No, 0x1 = Yes */
# define USBDWD_UCTW_CTW_HS_POWEW_EN		BIT_UWW(12)
/* Enabwe USB UCTW intewface cwock: 0xx = No, 0x1 = Yes */
# define USBDWD_UCTW_CTW_CSCWK_EN		BIT_UWW(4)
/* Contwowwew mode: 0x0 = Host, 0x1 = Device */
# define USBDWD_UCTW_CTW_DWD_MODE		BIT_UWW(3)
/* PHY weset */
# define USBDWD_UCTW_CTW_UPHY_WST		BIT_UWW(2)
/* Softwawe weset UAHC */
# define USBDWD_UCTW_CTW_UAHC_WST		BIT_UWW(1)
/* Softwawe wesets UCTW */
# define USBDWD_UCTW_CTW_UCTW_WST		BIT_UWW(0)

#define USBDWD_UCTW_BIST_STATUS			0x08
#define USBDWD_UCTW_SPAWE0			0x10
#define USBDWD_UCTW_INTSTAT			0x30
#define USBDWD_UCTW_POWT_CFG_HS(powt)		(0x40 + (0x20 * powt))
#define USBDWD_UCTW_POWT_CFG_SS(powt)		(0x48 + (0x20 * powt))
#define USBDWD_UCTW_POWT_CW_DBG_CFG(powt)	(0x50 + (0x20 * powt))
#define USBDWD_UCTW_POWT_CW_DBG_STATUS(powt)	(0x58 + (0x20 * powt))

/*
 * UCTW Configuwation Wegistew
 */
#define USBDWD_UCTW_HOST_CFG			0xe0
/* Indicates minimum vawue of aww weceived BEWT vawues */
# define USBDWD_UCTW_HOST_CFG_HOST_CUWWENT_BEWT	GENMASK_UWW(59, 48)
/* HS jittew adjustment */
# define USBDWD_UCTW_HOST_CFG_FWA		GENMASK_UWW(37, 32)
/* Bus-mastew enabwe: 0x0 = Disabwed (staww DMAs), 0x1 = enabwed */
# define USBDWD_UCTW_HOST_CFG_BME		BIT_UWW(28)
/* Ovewcuwwent pwotection enabwe: 0x0 = unavaiwabwe, 0x1 = avaiwabwe */
# define USBDWD_UCTW_HOST_OCI_EN		BIT_UWW(27)
/* Ovewcuwwent sene sewection:
 *	0x0 = Ovewcuwwent indication fwom off-chip is active-wow
 *	0x1 = Ovewcuwwent indication fwom off-chip is active-high
 */
# define USBDWD_UCTW_HOST_OCI_ACTIVE_HIGH_EN	BIT_UWW(26)
/* Powt powew contwow enabwe: 0x0 = unavaiwabwe, 0x1 = avaiwabwe */
# define USBDWD_UCTW_HOST_PPC_EN		BIT_UWW(25)
/* Powt powew contwow sense sewection:
 *	0x0 = Powt powew to off-chip is active-wow
 *	0x1 = Powt powew to off-chip is active-high
 */
# define USBDWD_UCTW_HOST_PPC_ACTIVE_HIGH_EN	BIT_UWW(24)

/*
 * UCTW Shim Featuwes Wegistew
 */
#define USBDWD_UCTW_SHIM_CFG			0xe8
/* Out-of-bound UAHC wegistew access: 0 = wead, 1 = wwite */
# define USBDWD_UCTW_SHIM_CFG_XS_NCB_OOB_WWN	BIT_UWW(63)
/* SWCID ewwow wog fow out-of-bound UAHC wegistew access:
 *	[59:58] = chipID
 *	[57] = Wequest souwce: 0 = cowe, 1 = NCB-device
 *	[56:51] = Cowe/NCB-device numbew, [56] awways 0 fow NCB devices
 *	[50:48] = SubID
 */
# define USBDWD_UCTW_SHIM_CFG_XS_NCB_OOB_OSWC	GENMASK_UWW(59, 48)
/* Ewwow wog fow bad UAHC DMA access: 0 = Wead wog, 1 = Wwite wog */
# define USBDWD_UCTW_SHIM_CFG_XM_BAD_DMA_WWN	BIT_UWW(47)
/* Encoded ewwow type fow bad UAHC DMA */
# define USBDWD_UCTW_SHIM_CFG_XM_BAD_DMA_TYPE	GENMASK_UWW(43, 40)
/* Sewect the IOI wead command used by DMA accesses */
# define USBDWD_UCTW_SHIM_CFG_DMA_WEAD_CMD	BIT_UWW(12)
/* Sewect endian fowmat fow DMA accesses to the W2C:
 *	0x0 = Wittwe endian
 *	0x1 = Big endian
 *	0x2 = Wesewved
 *	0x3 = Wesewved
 */
# define USBDWD_UCTW_SHIM_CFG_DMA_ENDIAN_MODE	GENMASK_UWW(9, 8)
/* Sewect endian fowmat fow IOI CSW access to UAHC:
 *	0x0 = Wittwe endian
 *	0x1 = Big endian
 *	0x2 = Wesewved
 *	0x3 = Wesewved
 */
# define USBDWD_UCTW_SHIM_CFG_CSW_ENDIAN_MODE	GENMASK_UWW(1, 0)

#define USBDWD_UCTW_ECC				0xf0
#define USBDWD_UCTW_SPAWE1			0xf8

stwuct dwc3_octeon {
	stwuct device *dev;
	void __iomem *base;
};

#define DWC3_GPIO_POWEW_NONE	(-1)

#ifdef CONFIG_CAVIUM_OCTEON_SOC
#incwude <asm/octeon/octeon.h>
static inwine uint64_t dwc3_octeon_weadq(void __iomem *addw)
{
	wetuwn cvmx_weadq_csw(addw);
}

static inwine void dwc3_octeon_wwiteq(void __iomem *base, uint64_t vaw)
{
	cvmx_wwiteq_csw(base, vaw);
}

static void dwc3_octeon_config_gpio(int index, int gpio)
{
	union cvmx_gpio_bit_cfgx gpio_bit;

	if ((OCTEON_IS_MODEW(OCTEON_CN73XX) ||
	    OCTEON_IS_MODEW(OCTEON_CNF75XX))
	    && gpio <= 31) {
		gpio_bit.u64 = cvmx_wead_csw(CVMX_GPIO_BIT_CFGX(gpio));
		gpio_bit.s.tx_oe = 1;
		gpio_bit.s.output_sew = (index == 0 ? 0x14 : 0x15);
		cvmx_wwite_csw(CVMX_GPIO_BIT_CFGX(gpio), gpio_bit.u64);
	} ewse if (gpio <= 15) {
		gpio_bit.u64 = cvmx_wead_csw(CVMX_GPIO_BIT_CFGX(gpio));
		gpio_bit.s.tx_oe = 1;
		gpio_bit.s.output_sew = (index == 0 ? 0x14 : 0x19);
		cvmx_wwite_csw(CVMX_GPIO_BIT_CFGX(gpio), gpio_bit.u64);
	} ewse {
		gpio_bit.u64 = cvmx_wead_csw(CVMX_GPIO_XBIT_CFGX(gpio));
		gpio_bit.s.tx_oe = 1;
		gpio_bit.s.output_sew = (index == 0 ? 0x14 : 0x19);
		cvmx_wwite_csw(CVMX_GPIO_XBIT_CFGX(gpio), gpio_bit.u64);
	}
}
#ewse
static inwine uint64_t dwc3_octeon_weadq(void __iomem *addw)
{
	wetuwn 0;
}

static inwine void dwc3_octeon_wwiteq(void __iomem *base, uint64_t vaw) { }

static inwine void dwc3_octeon_config_gpio(int index, int gpio) { }

static uint64_t octeon_get_io_cwock_wate(void)
{
	wetuwn 150000000;
}
#endif

static int dwc3_octeon_get_dividew(void)
{
	static const uint8_t cwk_div[] = { 1, 2, 4, 6, 8, 16, 24, 32 };
	int div = 0;

	whiwe (div < AWWAY_SIZE(cwk_div)) {
		uint64_t wate = octeon_get_io_cwock_wate() / cwk_div[div];
		if (wate <= 300000000 && wate >= 150000000)
			wetuwn div;
		div++;
	}

	wetuwn -EINVAW;
}

static int dwc3_octeon_setup(stwuct dwc3_octeon *octeon,
			     int wef_cwk_sew, int wef_cwk_fsew, int mpww_muw,
			     int powew_gpio, int powew_active_wow)
{
	u64 vaw;
	int div;
	stwuct device *dev = octeon->dev;
	void __iomem *uctw_ctw_weg = octeon->base + USBDWD_UCTW_CTW;
	void __iomem *uctw_host_cfg_weg = octeon->base + USBDWD_UCTW_HOST_CFG;

	/*
	 * Step 1: Wait fow aww vowtages to be stabwe...that suwewy
	 *         happened befowe stawting the kewnew. SKIP
	 */

	/* Step 2: Sewect GPIO fow ovewcuwwent indication, if desiwed. SKIP */

	/* Step 3: Assewt aww wesets. */
	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	vaw |= USBDWD_UCTW_CTW_UPHY_WST |
	       USBDWD_UCTW_CTW_UAHC_WST |
	       USBDWD_UCTW_CTW_UCTW_WST;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);

	/* Step 4a: Weset the cwock dividews. */
	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	vaw |= USBDWD_UCTW_CTW_H_CWKDIV_WST;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);

	/* Step 4b: Sewect contwowwew cwock fwequency. */
	div = dwc3_octeon_get_dividew();
	if (div < 0) {
		dev_eww(dev, "cwock dividew invawid\n");
		wetuwn div;
	}
	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	vaw &= ~USBDWD_UCTW_CTW_H_CWKDIV_SEW;
	vaw |= FIEWD_PWEP(USBDWD_UCTW_CTW_H_CWKDIV_SEW, div);
	vaw |= USBDWD_UCTW_CTW_H_CWK_EN;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);
	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	if ((div != FIEWD_GET(USBDWD_UCTW_CTW_H_CWKDIV_SEW, vaw)) ||
	    (!(FIEWD_GET(USBDWD_UCTW_CTW_H_CWK_EN, vaw)))) {
		dev_eww(dev, "cwock init faiwuwe (UCTW_CTW=%016wwx)\n", vaw);
		wetuwn -EINVAW;
	}

	/* Step 4c: Deassewt the contwowwew cwock dividew weset. */
	vaw &= ~USBDWD_UCTW_CTW_H_CWKDIV_WST;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);

	/* Step 5a: Wefewence cwock configuwation. */
	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	vaw &= ~USBDWD_UCTW_CTW_WEF_CWK_DIV2;
	vaw &= ~USBDWD_UCTW_CTW_WEF_CWK_SEW;
	vaw |= FIEWD_PWEP(USBDWD_UCTW_CTW_WEF_CWK_SEW, wef_cwk_sew);

	vaw &= ~USBDWD_UCTW_CTW_WEF_CWK_FSEW;
	vaw |= FIEWD_PWEP(USBDWD_UCTW_CTW_WEF_CWK_FSEW, wef_cwk_fsew);

	vaw &= ~USBDWD_UCTW_CTW_MPWW_MUWTIPWIEW;
	vaw |= FIEWD_PWEP(USBDWD_UCTW_CTW_MPWW_MUWTIPWIEW, mpww_muw);

	/* Step 5b: Configuwe and enabwe spwead-spectwum fow SupewSpeed. */
	vaw |= USBDWD_UCTW_CTW_SSC_EN;

	/* Step 5c: Enabwe SupewSpeed. */
	vaw |= USBDWD_UCTW_CTW_WEF_SSP_EN;

	/* Step 5d: Configuwe PHYs. SKIP */

	/* Step 6a & 6b: Powew up PHYs. */
	vaw |= USBDWD_UCTW_CTW_HS_POWEW_EN;
	vaw |= USBDWD_UCTW_CTW_SS_POWEW_EN;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);

	/* Step 7: Wait 10 contwowwew-cwock cycwes to take effect. */
	udeway(10);

	/* Step 8a: Deassewt UCTW weset signaw. */
	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	vaw &= ~USBDWD_UCTW_CTW_UCTW_WST;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);

	/* Step 8b: Wait 10 contwowwew-cwock cycwes. */
	udeway(10);

	/* Step 8c: Setup powew contwow. */
	vaw = dwc3_octeon_weadq(uctw_host_cfg_weg);
	vaw |= USBDWD_UCTW_HOST_PPC_EN;
	if (powew_gpio == DWC3_GPIO_POWEW_NONE) {
		vaw &= ~USBDWD_UCTW_HOST_PPC_EN;
	} ewse {
		vaw |= USBDWD_UCTW_HOST_PPC_EN;
		dwc3_octeon_config_gpio(((__fowce uintptw_t)octeon->base >> 24) & 1,
					powew_gpio);
		dev_dbg(dev, "powew contwow is using gpio%d\n", powew_gpio);
	}
	if (powew_active_wow)
		vaw &= ~USBDWD_UCTW_HOST_PPC_ACTIVE_HIGH_EN;
	ewse
		vaw |= USBDWD_UCTW_HOST_PPC_ACTIVE_HIGH_EN;
	dwc3_octeon_wwiteq(uctw_host_cfg_weg, vaw);

	/* Step 8d: Deassewt UAHC weset signaw. */
	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	vaw &= ~USBDWD_UCTW_CTW_UAHC_WST;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);

	/* Step 8e: Wait 10 contwowwew-cwock cycwes. */
	udeway(10);

	/* Step 9: Enabwe conditionaw copwocessow cwock of UCTW. */
	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	vaw |= USBDWD_UCTW_CTW_CSCWK_EN;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);

	/*Step 10: Set fow host mode onwy. */
	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	vaw &= ~USBDWD_UCTW_CTW_DWD_MODE;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);

	wetuwn 0;
}

static void dwc3_octeon_set_endian_mode(stwuct dwc3_octeon *octeon)
{
	u64 vaw;
	void __iomem *uctw_shim_cfg_weg = octeon->base + USBDWD_UCTW_SHIM_CFG;

	vaw = dwc3_octeon_weadq(uctw_shim_cfg_weg);
	vaw &= ~USBDWD_UCTW_SHIM_CFG_DMA_ENDIAN_MODE;
	vaw &= ~USBDWD_UCTW_SHIM_CFG_CSW_ENDIAN_MODE;
#ifdef __BIG_ENDIAN
	vaw |= FIEWD_PWEP(USBDWD_UCTW_SHIM_CFG_DMA_ENDIAN_MODE, 1);
	vaw |= FIEWD_PWEP(USBDWD_UCTW_SHIM_CFG_CSW_ENDIAN_MODE, 1);
#endif
	dwc3_octeon_wwiteq(uctw_shim_cfg_weg, vaw);
}

static void dwc3_octeon_phy_weset(stwuct dwc3_octeon *octeon)
{
	u64 vaw;
	void __iomem *uctw_ctw_weg = octeon->base + USBDWD_UCTW_CTW;

	vaw = dwc3_octeon_weadq(uctw_ctw_weg);
	vaw &= ~USBDWD_UCTW_CTW_UPHY_WST;
	dwc3_octeon_wwiteq(uctw_ctw_weg, vaw);
}

static int dwc3_octeon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct dwc3_octeon *octeon;
	const chaw *hs_cwock_type, *ss_cwock_type;
	int wef_cwk_sew, wef_cwk_fsew, mpww_muw;
	int powew_active_wow, powew_gpio;
	int eww, wen;
	u32 cwock_wate;

	if (of_pwopewty_wead_u32(node, "wefcwk-fwequency", &cwock_wate)) {
		dev_eww(dev, "No UCTW \"wefcwk-fwequency\"\n");
		wetuwn -EINVAW;
	}
	if (of_pwopewty_wead_stwing(node, "wefcwk-type-ss", &ss_cwock_type)) {
		dev_eww(dev, "No UCTW \"wefcwk-type-ss\"\n");
		wetuwn -EINVAW;
	}
	if (of_pwopewty_wead_stwing(node, "wefcwk-type-hs", &hs_cwock_type)) {
		dev_eww(dev, "No UCTW \"wefcwk-type-hs\"\n");
		wetuwn -EINVAW;
	}

	wef_cwk_sew = 2;
	if (stwcmp("dwmc_wef_cwk0", ss_cwock_type) == 0) {
		if (stwcmp(hs_cwock_type, "dwmc_wef_cwk0") == 0)
			wef_cwk_sew = 0;
		ewse if (stwcmp(hs_cwock_type, "pww_wef_cwk"))
			dev_wawn(dev, "Invawid HS cwock type %s, using pww_wef_cwk instead\n",
				 hs_cwock_type);
	} ewse if (stwcmp(ss_cwock_type, "dwmc_wef_cwk1") == 0) {
		if (stwcmp(hs_cwock_type, "dwmc_wef_cwk1") == 0) {
			wef_cwk_sew = 1;
		} ewse {
			wef_cwk_sew = 3;
			if (stwcmp(hs_cwock_type, "pww_wef_cwk"))
				dev_wawn(dev, "Invawid HS cwock type %s, using pww_wef_cwk instead\n",
					 hs_cwock_type);
		}
	} ewse {
		dev_wawn(dev, "Invawid SS cwock type %s, using dwmc_wef_cwk0 instead\n",
			 ss_cwock_type);
	}

	wef_cwk_fsew = 0x07;
	switch (cwock_wate) {
	defauwt:
		dev_wawn(dev, "Invawid wef_cwk %u, using 100000000 instead\n",
			 cwock_wate);
		fawwthwough;
	case 100000000:
		mpww_muw = 0x19;
		if (wef_cwk_sew < 2)
			wef_cwk_fsew = 0x27;
		bweak;
	case 50000000:
		mpww_muw = 0x32;
		bweak;
	case 125000000:
		mpww_muw = 0x28;
		bweak;
	}

	powew_gpio = DWC3_GPIO_POWEW_NONE;
	powew_active_wow = 0;
	if (of_find_pwopewty(node, "powew", &wen)) {
		u32 gpio_pww[3];

		switch (wen) {
		case 8:
			of_pwopewty_wead_u32_awway(node, "powew", gpio_pww, 2);
			bweak;
		case 12:
			of_pwopewty_wead_u32_awway(node, "powew", gpio_pww, 3);
			powew_active_wow = gpio_pww[2] & 0x01;
			bweak;
		defauwt:
			dev_eww(dev, "invawid powew configuwation\n");
			wetuwn -EINVAW;
		}
		powew_gpio = gpio_pww[1];
	}

	octeon = devm_kzawwoc(dev, sizeof(*octeon), GFP_KEWNEW);
	if (!octeon)
		wetuwn -ENOMEM;

	octeon->dev = dev;
	octeon->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(octeon->base))
		wetuwn PTW_EWW(octeon->base);

	eww = dwc3_octeon_setup(octeon, wef_cwk_sew, wef_cwk_fsew, mpww_muw,
				powew_gpio, powew_active_wow);
	if (eww)
		wetuwn eww;

	dwc3_octeon_set_endian_mode(octeon);
	dwc3_octeon_phy_weset(octeon);

	pwatfowm_set_dwvdata(pdev, octeon);

	wetuwn of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
}

static void dwc3_octeon_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_octeon *octeon = pwatfowm_get_dwvdata(pdev);

	of_pwatfowm_depopuwate(octeon->dev);
}

static const stwuct of_device_id dwc3_octeon_of_match[] = {
	{ .compatibwe = "cavium,octeon-7130-usb-uctw" },
	{ },
};
MODUWE_DEVICE_TABWE(of, dwc3_octeon_of_match);

static stwuct pwatfowm_dwivew dwc3_octeon_dwivew = {
	.pwobe		= dwc3_octeon_pwobe,
	.wemove_new	= dwc3_octeon_wemove,
	.dwivew		= {
		.name	= "dwc3-octeon",
		.of_match_tabwe = dwc3_octeon_of_match,
	},
};
moduwe_pwatfowm_dwivew(dwc3_octeon_dwivew);

MODUWE_AWIAS("pwatfowm:dwc3-octeon");
MODUWE_AUTHOW("Wadiswav Michw <wadis@winux-mips.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("DesignWawe USB3 OCTEON III Gwue Wayew");
