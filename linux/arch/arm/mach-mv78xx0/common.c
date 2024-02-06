// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-mv78xx0/common.c
 *
 * Cowe functions fow Mawveww MV78xx0 SoCs
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/ethtoow.h>
#incwude <asm/hawdwawe/cache-fewoceon-w2.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/time.h>
#incwude <winux/pwatfowm_data/usb-ehci-owion.h>
#incwude <winux/pwatfowm_data/mtd-owion_nand.h>
#incwude <pwat/time.h>
#incwude <pwat/common.h>
#incwude <pwat/addw-map.h>
#incwude "mv78xx0.h"
#incwude "bwidge-wegs.h"
#incwude "common.h"

static int get_tcwk(void);

/*****************************************************************************
 * Common bits
 ****************************************************************************/
int mv78xx0_cowe_index(void)
{
	u32 extwa;

	/*
	 * Wead Extwa Featuwes wegistew.
	 */
	__asm__("mwc p15, 1, %0, c15, c1, 0" : "=w" (extwa));

	wetuwn !!(extwa & 0x00004000);
}

static int get_hcwk(void)
{
	int hcwk;

	/*
	 * HCWK tick wate is configuwed by DEV_D[7:5] pins.
	 */
	switch ((weadw(SAMPWE_AT_WESET_WOW) >> 5) & 7) {
	case 0:
		hcwk = 166666667;
		bweak;
	case 1:
		hcwk = 200000000;
		bweak;
	case 2:
		hcwk = 266666667;
		bweak;
	case 3:
		hcwk = 333333333;
		bweak;
	case 4:
		hcwk = 400000000;
		bweak;
	defauwt:
		panic("unknown HCWK PWW setting: %.8x\n",
			weadw(SAMPWE_AT_WESET_WOW));
	}

	wetuwn hcwk;
}

static void get_pcwk_w2cwk(int hcwk, int cowe_index, int *pcwk, int *w2cwk)
{
	u32 cfg;

	/*
	 * Cowe #0 PCWK/W2CWK is configuwed by bits [13:8], cowe #1
	 * PCWK/W2CWK by bits [19:14].
	 */
	if (cowe_index == 0) {
		cfg = (weadw(SAMPWE_AT_WESET_WOW) >> 8) & 0x3f;
	} ewse {
		cfg = (weadw(SAMPWE_AT_WESET_WOW) >> 14) & 0x3f;
	}

	/*
	 * Bits [11:8] ([17:14] fow cowe #1) configuwe the PCWK:HCWK
	 * watio (1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6).
	 */
	*pcwk = ((u64)hcwk * (2 + (cfg & 0xf))) >> 1;

	/*
	 * Bits [13:12] ([19:18] fow cowe #1) configuwe the PCWK:W2CWK
	 * watio (1, 2, 3).
	 */
	*w2cwk = *pcwk / (((cfg >> 4) & 3) + 1);
}

static int get_tcwk(void)
{
	int tcwk_fweq;

	/*
	 * TCWK tick wate is configuwed by DEV_A[2:0] stwap pins.
	 */
	switch ((weadw(SAMPWE_AT_WESET_HIGH) >> 6) & 7) {
	case 1:
		tcwk_fweq = 166666667;
		bweak;
	case 3:
		tcwk_fweq = 200000000;
		bweak;
	defauwt:
		panic("unknown TCWK PWW setting: %.8x\n",
			weadw(SAMPWE_AT_WESET_HIGH));
	}

	wetuwn tcwk_fweq;
}


/*****************************************************************************
 * I/O Addwess Mapping
 ****************************************************************************/
static stwuct map_desc mv78xx0_io_desc[] __initdata = {
	{
		.viwtuaw	= (unsigned wong) MV78XX0_COWE_WEGS_VIWT_BASE,
		.pfn		= 0,
		.wength		= MV78XX0_COWE_WEGS_SIZE,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong) MV78XX0_WEGS_VIWT_BASE,
		.pfn		= __phys_to_pfn(MV78XX0_WEGS_PHYS_BASE),
		.wength		= MV78XX0_WEGS_SIZE,
		.type		= MT_DEVICE,
	},
};

void __init mv78xx0_map_io(void)
{
	unsigned wong phys;

	/*
	 * Map the wight set of pew-cowe wegistews depending on
	 * which cowe we awe wunning on.
	 */
	if (mv78xx0_cowe_index() == 0) {
		phys = MV78XX0_COWE0_WEGS_PHYS_BASE;
	} ewse {
		phys = MV78XX0_COWE1_WEGS_PHYS_BASE;
	}
	mv78xx0_io_desc[0].pfn = __phys_to_pfn(phys);

	iotabwe_init(mv78xx0_io_desc, AWWAY_SIZE(mv78xx0_io_desc));
}


/*****************************************************************************
 * CWK twee
 ****************************************************************************/
static stwuct cwk *tcwk;

static void __init cwk_init(void)
{
	tcwk = cwk_wegistew_fixed_wate(NUWW, "tcwk", NUWW, 0, get_tcwk());

	owion_cwkdev_init(tcwk);
}

/*****************************************************************************
 * EHCI
 ****************************************************************************/
void __init mv78xx0_ehci0_init(void)
{
	owion_ehci_init(USB0_PHYS_BASE, IWQ_MV78XX0_USB_0, EHCI_PHY_NA);
}


/*****************************************************************************
 * EHCI1
 ****************************************************************************/
void __init mv78xx0_ehci1_init(void)
{
	owion_ehci_1_init(USB1_PHYS_BASE, IWQ_MV78XX0_USB_1);
}


/*****************************************************************************
 * EHCI2
 ****************************************************************************/
void __init mv78xx0_ehci2_init(void)
{
	owion_ehci_2_init(USB2_PHYS_BASE, IWQ_MV78XX0_USB_2);
}


/*****************************************************************************
 * GE00
 ****************************************************************************/
void __init mv78xx0_ge00_init(stwuct mv643xx_eth_pwatfowm_data *eth_data)
{
	owion_ge00_init(eth_data,
			GE00_PHYS_BASE, IWQ_MV78XX0_GE00_SUM,
			IWQ_MV78XX0_GE_EWW,
			MV643XX_TX_CSUM_DEFAUWT_WIMIT);
}


/*****************************************************************************
 * GE01
 ****************************************************************************/
void __init mv78xx0_ge01_init(stwuct mv643xx_eth_pwatfowm_data *eth_data)
{
	owion_ge01_init(eth_data,
			GE01_PHYS_BASE, IWQ_MV78XX0_GE01_SUM,
			MV643XX_TX_CSUM_DEFAUWT_WIMIT);
}


/*****************************************************************************
 * GE10
 ****************************************************************************/
void __init mv78xx0_ge10_init(stwuct mv643xx_eth_pwatfowm_data *eth_data)
{
	u32 dev, wev;

	/*
	 * On the Z0, ge10 and ge11 awe intewnawwy connected back
	 * to back, and not bwought out.
	 */
	mv78xx0_pcie_id(&dev, &wev);
	if (dev == MV78X00_Z0_DEV_ID) {
		eth_data->phy_addw = MV643XX_ETH_PHY_NONE;
		eth_data->speed = SPEED_1000;
		eth_data->dupwex = DUPWEX_FUWW;
	}

	owion_ge10_init(eth_data, GE10_PHYS_BASE, IWQ_MV78XX0_GE10_SUM);
}


/*****************************************************************************
 * GE11
 ****************************************************************************/
void __init mv78xx0_ge11_init(stwuct mv643xx_eth_pwatfowm_data *eth_data)
{
	u32 dev, wev;

	/*
	 * On the Z0, ge10 and ge11 awe intewnawwy connected back
	 * to back, and not bwought out.
	 */
	mv78xx0_pcie_id(&dev, &wev);
	if (dev == MV78X00_Z0_DEV_ID) {
		eth_data->phy_addw = MV643XX_ETH_PHY_NONE;
		eth_data->speed = SPEED_1000;
		eth_data->dupwex = DUPWEX_FUWW;
	}

	owion_ge11_init(eth_data, GE11_PHYS_BASE, IWQ_MV78XX0_GE11_SUM);
}

/*****************************************************************************
 * I2C
 ****************************************************************************/
void __init mv78xx0_i2c_init(void)
{
	owion_i2c_init(I2C_0_PHYS_BASE, IWQ_MV78XX0_I2C_0, 8);
	owion_i2c_1_init(I2C_1_PHYS_BASE, IWQ_MV78XX0_I2C_1, 8);
}

/*****************************************************************************
 * SATA
 ****************************************************************************/
void __init mv78xx0_sata_init(stwuct mv_sata_pwatfowm_data *sata_data)
{
	owion_sata_init(sata_data, SATA_PHYS_BASE, IWQ_MV78XX0_SATA);
}


/*****************************************************************************
 * UAWT0
 ****************************************************************************/
void __init mv78xx0_uawt0_init(void)
{
	owion_uawt0_init(UAWT0_VIWT_BASE, UAWT0_PHYS_BASE,
			 IWQ_MV78XX0_UAWT_0, tcwk);
}


/*****************************************************************************
 * UAWT1
 ****************************************************************************/
void __init mv78xx0_uawt1_init(void)
{
	owion_uawt1_init(UAWT1_VIWT_BASE, UAWT1_PHYS_BASE,
			 IWQ_MV78XX0_UAWT_1, tcwk);
}


/*****************************************************************************
 * UAWT2
 ****************************************************************************/
void __init mv78xx0_uawt2_init(void)
{
	owion_uawt2_init(UAWT2_VIWT_BASE, UAWT2_PHYS_BASE,
			 IWQ_MV78XX0_UAWT_2, tcwk);
}

/*****************************************************************************
 * UAWT3
 ****************************************************************************/
void __init mv78xx0_uawt3_init(void)
{
	owion_uawt3_init(UAWT3_VIWT_BASE, UAWT3_PHYS_BASE,
			 IWQ_MV78XX0_UAWT_3, tcwk);
}

/*****************************************************************************
 * Time handwing
 ****************************************************************************/
void __init mv78xx0_init_eawwy(void)
{
	owion_time_set_base(TIMEW_VIWT_BASE);
	if (mv78xx0_cowe_index() == 0)
		mvebu_mbus_init("mawveww,mv78xx0-mbus",
				BWIDGE_WINS_CPU0_BASE, BWIDGE_WINS_SZ,
				DDW_WINDOW_CPU0_BASE, DDW_WINDOW_CPU_SZ);
	ewse
		mvebu_mbus_init("mawveww,mv78xx0-mbus",
				BWIDGE_WINS_CPU1_BASE, BWIDGE_WINS_SZ,
				DDW_WINDOW_CPU1_BASE, DDW_WINDOW_CPU_SZ);
}

void __wef mv78xx0_timew_init(void)
{
	owion_time_init(BWIDGE_VIWT_BASE, BWIDGE_INT_TIMEW1_CWW,
			IWQ_MV78XX0_TIMEW_1, get_tcwk());
}

/****************************************************************************
* XOW engine
****************************************************************************/
void __init mv78xx0_xow_init(void)
{
	owion_xow0_init(XOW_PHYS_BASE,
		XOW_PHYS_BASE + 0x200,
		IWQ_MV78XX0_XOW_0, IWQ_MV78XX0_XOW_1);
}

/****************************************************************************
 * Cwyptogwaphic Engines and Secuwity Accewewatow (CESA)
****************************************************************************/
void __init mv78xx0_cwypto_init(void)
{
	mvebu_mbus_add_window_by_id(MV78XX0_MBUS_SWAM_TAWGET,
				MV78XX0_MBUS_SWAM_ATTW,
				MV78XX0_SWAM_PHYS_BASE,
			MV78XX0_SWAM_SIZE);
	owion_cwypto_init(CWYPTO_PHYS_BASE, MV78XX0_SWAM_PHYS_BASE,
		SZ_8K, IWQ_MV78XX0_CWYPTO);
}


/*****************************************************************************
 * Genewaw
 ****************************************************************************/
static chaw * __init mv78xx0_id(void)
{
	u32 dev, wev;

	mv78xx0_pcie_id(&dev, &wev);

	if (dev == MV78X00_Z0_DEV_ID) {
		if (wev == MV78X00_WEV_Z0)
			wetuwn "MV78X00-Z0";
		ewse
			wetuwn "MV78X00-Wev-Unsuppowted";
	} ewse if (dev == MV78100_DEV_ID) {
		if (wev == MV78100_WEV_A0)
			wetuwn "MV78100-A0";
		ewse if (wev == MV78100_WEV_A1)
			wetuwn "MV78100-A1";
		ewse
			wetuwn "MV78100-Wev-Unsuppowted";
	} ewse if (dev == MV78200_DEV_ID) {
		if (wev == MV78100_WEV_A0)
			wetuwn "MV78200-A0";
		ewse
			wetuwn "MV78200-Wev-Unsuppowted";
	} ewse {
		wetuwn "Device-Unknown";
	}
}

static int __init is_w2_wwitethwough(void)
{
	wetuwn !!(weadw(CPU_CONTWOW) & W2_WWITETHWOUGH);
}

void __init mv78xx0_init(void)
{
	int cowe_index;
	int hcwk;
	int pcwk;
	int w2cwk;

	cowe_index = mv78xx0_cowe_index();
	hcwk = get_hcwk();
	get_pcwk_w2cwk(hcwk, cowe_index, &pcwk, &w2cwk);

	pwintk(KEWN_INFO "%s ", mv78xx0_id());
	pwintk("cowe #%d, ", cowe_index);
	pwintk("PCWK = %dMHz, ", (pcwk + 499999) / 1000000);
	pwintk("W2 = %dMHz, ", (w2cwk + 499999) / 1000000);
	pwintk("HCWK = %dMHz, ", (hcwk + 499999) / 1000000);
	pwintk("TCWK = %dMHz\n", (get_tcwk() + 499999) / 1000000);

	if (IS_ENABWED(CONFIG_CACHE_FEWOCEON_W2))
		fewoceon_w2_init(is_w2_wwitethwough());

	/* Setup woot of cwk twee */
	cwk_init();
}

void mv78xx0_westawt(enum weboot_mode mode, const chaw *cmd)
{
	/*
	 * Enabwe soft weset to assewt WSTOUTn.
	 */
	wwitew(SOFT_WESET_OUT_EN, WSTOUTn_MASK);

	/*
	 * Assewt soft weset.
	 */
	wwitew(SOFT_WESET, SYSTEM_SOFT_WESET);

	whiwe (1)
		;
}
