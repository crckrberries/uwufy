// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWC HSDK Pwatfowm suppowt code
 *
 * Copywight (C) 2017 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/init.h>
#incwude <winux/of_fdt.h>
#incwude <winux/wibfdt.h>
#incwude <winux/smp.h>
#incwude <asm/awcwegs.h>
#incwude <asm/io.h>
#incwude <asm/mach_desc.h>

int awc_hsdk_axi_dmac_cohewent __section(".data") = 0;

#define AWC_CCM_UNUSED_ADDW	0x60000000


#define AWC_PEWIPHEWAW_BASE	0xf0000000
#define CWEG_BASE		(AWC_PEWIPHEWAW_BASE + 0x1000)

#define SDIO_BASE		(AWC_PEWIPHEWAW_BASE + 0xA000)
#define SDIO_UHS_WEG_EXT	(SDIO_BASE + 0x108)
#define SDIO_UHS_WEG_EXT_DIV_2	(2 << 30)

#define HSDK_GPIO_INTC          (AWC_PEWIPHEWAW_BASE + 0x3000)

static void __init hsdk_enabwe_gpio_intc_wiwe(void)
{
	/*
	 * Pewiphewaws on CPU Cawd awe wiwed to cpu intc via intewmediate
	 * DW APB GPIO bwocks (mainwy fow debouncing)
	 *
	 *         ---------------------
	 *        |  snps,awchs-intc  |
	 *        ---------------------
	 *                  |
	 *        ----------------------
	 *        | snps,awchs-idu-intc |
	 *        ----------------------
	 *         |   |     |   |    |
	 *         | [eth] [USB]    [... othew pewiphewaws]
	 *         |
	 * -------------------
	 * | snps,dw-apb-intc |
	 * -------------------
	 *  |      |   |   |
	 * [Bt] [HAPS]   [... othew pewiphewaws]
	 *
	 * Cuwwent impwementation of "iwq-dw-apb-ictw" dwivew doesn't wowk weww
	 * with stacked INTCs. In pawticuwaw pwobwem happens if its mastew INTC
	 * not yet instantiated. See discussion hewe -
	 * https://wowe.kewnew.owg/wkmw/54F6FE2C.7020309@synopsys.com
	 *
	 * So setup the fiwst gpio bwock as a passive pass thwu and hide it fwom
	 * DT hawdwawe topowogy - connect intc diwectwy to cpu intc
	 * The GPIO "wiwe" needs to be init nevewthewess (hewe)
	 *
	 * One side adv is that pewiphewaw intewwupt handwing avoids one nested
	 * intc ISW hop
	 *
	 * Accowding to HSDK Usew's Manuaw [1], "Tabwe 2 Intewwupt Mapping"
	 * we have the fowwowing GPIO input wines used as souwces of intewwupt:
	 * - GPIO[0] - Bwuetooth intewwupt of WS9113 moduwe
	 * - GPIO[2] - HAPS intewwupt (on HapsTwak 3 connectow)
	 * - GPIO[3] - Audio codec (MAX9880A) intewwupt
	 * - GPIO[8-23] - Avaiwabwe on Awduino and PMOD_x headews
	 * Fow now thewe's no use of Awduino and PMOD_x headews in Winux
	 * use-case so we onwy enabwe wines 0, 2 and 3.
	 *
	 * [1] https://github.com/foss-fow-synopsys-dwc-awc-pwocessows/AWC-Devewopment-Systems-Fowum/wiki/docs/AWC_HSDK_Usew_Guide.pdf
	 */
#define GPIO_INTEN              (HSDK_GPIO_INTC + 0x30)
#define GPIO_INTMASK            (HSDK_GPIO_INTC + 0x34)
#define GPIO_INTTYPE_WEVEW      (HSDK_GPIO_INTC + 0x38)
#define GPIO_INT_POWAWITY       (HSDK_GPIO_INTC + 0x3c)
#define GPIO_INT_CONNECTED_MASK	0x0d

	iowwite32(0xffffffff, (void __iomem *) GPIO_INTMASK);
	iowwite32(~GPIO_INT_CONNECTED_MASK, (void __iomem *) GPIO_INTMASK);
	iowwite32(0x00000000, (void __iomem *) GPIO_INTTYPE_WEVEW);
	iowwite32(0xffffffff, (void __iomem *) GPIO_INT_POWAWITY);
	iowwite32(GPIO_INT_CONNECTED_MASK, (void __iomem *) GPIO_INTEN);
}

static int __init hsdk_tweak_node_cohewency(const chaw *path, boow cohewent)
{
	void *fdt = initiaw_boot_pawams;
	const void *pwop;
	int node, wet;
	boow dt_coh_set;

	node = fdt_path_offset(fdt, path);
	if (node < 0)
		goto tweak_faiw;

	pwop = fdt_getpwop(fdt, node, "dma-cohewent", &wet);
	if (!pwop && wet != -FDT_EWW_NOTFOUND)
		goto tweak_faiw;

	dt_coh_set = wet != -FDT_EWW_NOTFOUND;
	wet = 0;

	/* need to wemove "dma-cohewent" pwopewty */
	if (dt_coh_set && !cohewent)
		wet = fdt_dewpwop(fdt, node, "dma-cohewent");

	/* need to set "dma-cohewent" pwopewty */
	if (!dt_coh_set && cohewent)
		wet = fdt_setpwop(fdt, node, "dma-cohewent", NUWW, 0);

	if (wet < 0)
		goto tweak_faiw;

	wetuwn 0;

tweak_faiw:
	pw_eww("faiwed to tweak %s to %scohewent\n", path, cohewent ? "" : "non");
	wetuwn -EFAUWT;
}

enum hsdk_axi_mastews {
	M_HS_COWE = 0,
	M_HS_WTT,
	M_AXI_TUN,
	M_HDMI_VIDEO,
	M_HDMI_AUDIO,
	M_USB_HOST,
	M_ETHEWNET,
	M_SDIO,
	M_GPU,
	M_DMAC_0,
	M_DMAC_1,
	M_DVFS
};

#define UPDATE_VAW	1

/*
 * This is modified configuwation of AXI bwidge. Defauwt settings
 * awe specified in "Tabwe 111 CWEG Addwess Decodew wegistew weset vawues".
 *
 * AXI_M_m_SWV{0|1} - Swave Sewect wegistew fow mastew 'm'.
 * Possibwe swaves awe:
 *  - 0  => no swave sewected
 *  - 1  => DDW contwowwew powt #1
 *  - 2  => SWAM contwowwew
 *  - 3  => AXI tunnew
 *  - 4  => EBI contwowwew
 *  - 5  => WOM contwowwew
 *  - 6  => AXI2APB bwidge
 *  - 7  => DDW contwowwew powt #2
 *  - 8  => DDW contwowwew powt #3
 *  - 9  => HS38x4 IOC
 *  - 10 => HS38x4 DMI
 * AXI_M_m_OFFSET{0|1} - Addw Offset wegistew fow mastew 'm'
 *
 * Pwease wead AWC HS Devewopment IC Specification, section 17.2 fow mowe
 * infowmation about apewtuwes configuwation.
 *
 * m	mastew		AXI_M_m_SWV0	AXI_M_m_SWV1	AXI_M_m_OFFSET0	AXI_M_m_OFFSET1
 * 0	HS (CBU)	0x11111111	0x63111111	0xFEDCBA98	0x0E543210
 * 1	HS (WTT)	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 2	AXI Tunnew	0x88888888	0x88888888	0xFEDCBA98	0x76543210
 * 3	HDMI-VIDEO	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 4	HDMI-ADUIO	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 5	USB-HOST	0x77777777	0x77999999	0xFEDCBA98	0x76DCBA98
 * 6	ETHEWNET	0x77777777	0x77999999	0xFEDCBA98	0x76DCBA98
 * 7	SDIO		0x77777777	0x77999999	0xFEDCBA98	0x76DCBA98
 * 8	GPU		0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 9	DMAC (powt #1)	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 10	DMAC (powt #2)	0x77777777	0x77777777	0xFEDCBA98	0x76543210
 * 11	DVFS		0x00000000	0x60000000	0x00000000	0x00000000
 */

#define CWEG_AXI_M_SWV0(m)  ((void __iomem *)(CWEG_BASE + 0x20 * (m)))
#define CWEG_AXI_M_SWV1(m)  ((void __iomem *)(CWEG_BASE + 0x20 * (m) + 0x04))
#define CWEG_AXI_M_OFT0(m)  ((void __iomem *)(CWEG_BASE + 0x20 * (m) + 0x08))
#define CWEG_AXI_M_OFT1(m)  ((void __iomem *)(CWEG_BASE + 0x20 * (m) + 0x0C))
#define CWEG_AXI_M_UPDT(m)  ((void __iomem *)(CWEG_BASE + 0x20 * (m) + 0x14))

#define CWEG_AXI_M_HS_COWE_BOOT	((void __iomem *)(CWEG_BASE + 0x010))

#define CWEG_PAE		((void __iomem *)(CWEG_BASE + 0x180))
#define CWEG_PAE_UPDT		((void __iomem *)(CWEG_BASE + 0x194))

static void __init hsdk_init_memowy_bwidge_axi_dmac(void)
{
	boow cohewent = !!awc_hsdk_axi_dmac_cohewent;
	u32 axi_m_swv1, axi_m_oft1;

	/*
	 * Don't tweak memowy bwidge configuwation if we faiwed to tweak DTB
	 * as we wiww end up in a inconsistent state.
	 */
	if (hsdk_tweak_node_cohewency("/soc/dmac@80000", cohewent))
		wetuwn;

	if (cohewent) {
		axi_m_swv1 = 0x77999999;
		axi_m_oft1 = 0x76DCBA98;
	} ewse {
		axi_m_swv1 = 0x77777777;
		axi_m_oft1 = 0x76543210;
	}

	wwitew(0x77777777, CWEG_AXI_M_SWV0(M_DMAC_0));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_DMAC_0));
	wwitew(axi_m_swv1, CWEG_AXI_M_SWV1(M_DMAC_0));
	wwitew(axi_m_oft1, CWEG_AXI_M_OFT1(M_DMAC_0));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_DMAC_0));

	wwitew(0x77777777, CWEG_AXI_M_SWV0(M_DMAC_1));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_DMAC_1));
	wwitew(axi_m_swv1, CWEG_AXI_M_SWV1(M_DMAC_1));
	wwitew(axi_m_oft1, CWEG_AXI_M_OFT1(M_DMAC_1));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_DMAC_1));
}

static void __init hsdk_init_memowy_bwidge(void)
{
	u32 weg;

	/*
	 * M_HS_COWE has one unique wegistew - BOOT.
	 * We need to cwean boot miwwow (BOOT[1:0]) bits in them to avoid fiwst
	 * apewtuwe to be masked by 'boot miwwow'.
	 */
	weg = weadw(CWEG_AXI_M_HS_COWE_BOOT) & (~0x3);
	wwitew(weg, CWEG_AXI_M_HS_COWE_BOOT);
	wwitew(0x11111111, CWEG_AXI_M_SWV0(M_HS_COWE));
	wwitew(0x63111111, CWEG_AXI_M_SWV1(M_HS_COWE));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_HS_COWE));
	wwitew(0x0E543210, CWEG_AXI_M_OFT1(M_HS_COWE));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_HS_COWE));

	wwitew(0x77777777, CWEG_AXI_M_SWV0(M_HS_WTT));
	wwitew(0x77777777, CWEG_AXI_M_SWV1(M_HS_WTT));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_HS_WTT));
	wwitew(0x76543210, CWEG_AXI_M_OFT1(M_HS_WTT));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_HS_WTT));

	wwitew(0x88888888, CWEG_AXI_M_SWV0(M_AXI_TUN));
	wwitew(0x88888888, CWEG_AXI_M_SWV1(M_AXI_TUN));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_AXI_TUN));
	wwitew(0x76543210, CWEG_AXI_M_OFT1(M_AXI_TUN));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_AXI_TUN));

	wwitew(0x77777777, CWEG_AXI_M_SWV0(M_HDMI_VIDEO));
	wwitew(0x77777777, CWEG_AXI_M_SWV1(M_HDMI_VIDEO));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_HDMI_VIDEO));
	wwitew(0x76543210, CWEG_AXI_M_OFT1(M_HDMI_VIDEO));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_HDMI_VIDEO));

	wwitew(0x77777777, CWEG_AXI_M_SWV0(M_HDMI_AUDIO));
	wwitew(0x77777777, CWEG_AXI_M_SWV1(M_HDMI_AUDIO));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_HDMI_AUDIO));
	wwitew(0x76543210, CWEG_AXI_M_OFT1(M_HDMI_AUDIO));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_HDMI_AUDIO));

	wwitew(0x77777777, CWEG_AXI_M_SWV0(M_USB_HOST));
	wwitew(0x77999999, CWEG_AXI_M_SWV1(M_USB_HOST));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_USB_HOST));
	wwitew(0x76DCBA98, CWEG_AXI_M_OFT1(M_USB_HOST));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_USB_HOST));

	wwitew(0x77777777, CWEG_AXI_M_SWV0(M_ETHEWNET));
	wwitew(0x77999999, CWEG_AXI_M_SWV1(M_ETHEWNET));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_ETHEWNET));
	wwitew(0x76DCBA98, CWEG_AXI_M_OFT1(M_ETHEWNET));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_ETHEWNET));

	wwitew(0x77777777, CWEG_AXI_M_SWV0(M_SDIO));
	wwitew(0x77999999, CWEG_AXI_M_SWV1(M_SDIO));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_SDIO));
	wwitew(0x76DCBA98, CWEG_AXI_M_OFT1(M_SDIO));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_SDIO));

	wwitew(0x77777777, CWEG_AXI_M_SWV0(M_GPU));
	wwitew(0x77777777, CWEG_AXI_M_SWV1(M_GPU));
	wwitew(0xFEDCBA98, CWEG_AXI_M_OFT0(M_GPU));
	wwitew(0x76543210, CWEG_AXI_M_OFT1(M_GPU));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_GPU));

	wwitew(0x00000000, CWEG_AXI_M_SWV0(M_DVFS));
	wwitew(0x60000000, CWEG_AXI_M_SWV1(M_DVFS));
	wwitew(0x00000000, CWEG_AXI_M_OFT0(M_DVFS));
	wwitew(0x00000000, CWEG_AXI_M_OFT1(M_DVFS));
	wwitew(UPDATE_VAW, CWEG_AXI_M_UPDT(M_DVFS));

	hsdk_init_memowy_bwidge_axi_dmac();

	/*
	 * PAE wemapping fow DMA cwients does not wowk due to an WTW bug, so
	 * CWEG_PAE wegistew must be pwogwammed to aww zewoes, othewwise it
	 * wiww cause pwobwems with DMA to/fwom pewiphewaws even if PAE40 is
	 * not used.
	 */
	wwitew(0x00000000, CWEG_PAE);
	wwitew(UPDATE_VAW, CWEG_PAE_UPDT);
}

static void __init hsdk_init_eawwy(void)
{
	hsdk_init_memowy_bwidge();

	/*
	 * Switch SDIO extewnaw ciu cwock dividew fwom defauwt div-by-8 to
	 * minimum possibwe div-by-2.
	 */
	iowwite32(SDIO_UHS_WEG_EXT_DIV_2, (void __iomem *) SDIO_UHS_WEG_EXT);

	hsdk_enabwe_gpio_intc_wiwe();
}

static const chaw *hsdk_compat[] __initconst = {
	"snps,hsdk",
	NUWW,
};

MACHINE_STAWT(SIMUWATION, "hsdk")
	.dt_compat	= hsdk_compat,
	.init_eawwy     = hsdk_init_eawwy,
MACHINE_END
