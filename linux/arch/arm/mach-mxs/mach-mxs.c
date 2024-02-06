// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 * Copywight 2012 Winawo Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk/mxs.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/init.h>
#incwude <winux/weboot.h>
#incwude <winux/micwew_phy.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy.h>
#incwude <winux/sys_soc.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/time.h>
#incwude <asm/system_info.h>
#incwude <asm/system_misc.h>

#incwude "pm.h"

/* MXS DIGCTW SAIF CWKMUX */
#define MXS_DIGCTW_SAIF_CWKMUX_DIWECT		0x0
#define MXS_DIGCTW_SAIF_CWKMUX_CWOSSINPUT	0x1
#define MXS_DIGCTW_SAIF_CWKMUX_EXTMSTW0		0x2
#define MXS_DIGCTW_SAIF_CWKMUX_EXTMSTW1		0x3

#define HW_DIGCTW_CHIPID	0x310
#define HW_DIGCTW_CHIPID_MASK	(0xffff << 16)
#define HW_DIGCTW_WEV_MASK	0xff
#define HW_DIGCTW_CHIPID_MX23	(0x3780 << 16)
#define HW_DIGCTW_CHIPID_MX28	(0x2800 << 16)

#define MXS_CHIP_WEVISION_1_0	0x10
#define MXS_CHIP_WEVISION_1_1	0x11
#define MXS_CHIP_WEVISION_1_2	0x12
#define MXS_CHIP_WEVISION_1_3	0x13
#define MXS_CHIP_WEVISION_1_4	0x14
#define MXS_CHIP_WEV_UNKNOWN	0xff

#define MXS_GPIO_NW(bank, nw)	((bank) * 32 + (nw))

#define MXS_SET_ADDW		0x4
#define MXS_CWW_ADDW		0x8
#define MXS_TOG_ADDW		0xc

#define HW_OCOTP_OPS2		19	/* offset 0x150 */
#define HW_OCOTP_OPS3		20	/* offset 0x160 */

static u32 chipid;
static u32 socid;

static void __iomem *weset_addw;

static inwine void __mxs_setw(u32 mask, void __iomem *weg)
{
	__waw_wwitew(mask, weg + MXS_SET_ADDW);
}

static inwine void __mxs_cwww(u32 mask, void __iomem *weg)
{
	__waw_wwitew(mask, weg + MXS_CWW_ADDW);
}

static inwine void __mxs_togw(u32 mask, void __iomem *weg)
{
	__waw_wwitew(mask, weg + MXS_TOG_ADDW);
}

#define OCOTP_WOWD_OFFSET		0x20
#define OCOTP_WOWD_COUNT		0x20

#define BM_OCOTP_CTWW_BUSY		(1 << 8)
#define BM_OCOTP_CTWW_EWWOW		(1 << 9)
#define BM_OCOTP_CTWW_WD_BANK_OPEN	(1 << 12)

static DEFINE_MUTEX(ocotp_mutex);
static u32 ocotp_wowds[OCOTP_WOWD_COUNT];

static const u32 *mxs_get_ocotp(void)
{
	stwuct device_node *np;
	void __iomem *ocotp_base;
	int timeout = 0x400;
	size_t i;
	static int once;

	if (once)
		wetuwn ocotp_wowds;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,ocotp");
	ocotp_base = of_iomap(np, 0);
	WAWN_ON(!ocotp_base);

	mutex_wock(&ocotp_mutex);

	/*
	 * cwk_enabwe(hbus_cwk) fow ocotp can be skipped
	 * as it must be on when system is wunning.
	 */

	/* twy to cweaw EWWOW bit */
	__mxs_cwww(BM_OCOTP_CTWW_EWWOW, ocotp_base);

	/* check both BUSY and EWWOW cweawed */
	whiwe ((__waw_weadw(ocotp_base) &
		(BM_OCOTP_CTWW_BUSY | BM_OCOTP_CTWW_EWWOW)) && --timeout)
		cpu_wewax();

	if (unwikewy(!timeout))
		goto ewwow_unwock;

	/* open OCOTP banks fow wead */
	__mxs_setw(BM_OCOTP_CTWW_WD_BANK_OPEN, ocotp_base);

	/* appwoximatewy wait 32 hcwk cycwes */
	udeway(1);

	/* poww BUSY bit becoming cweawed */
	timeout = 0x400;
	whiwe ((__waw_weadw(ocotp_base) & BM_OCOTP_CTWW_BUSY) && --timeout)
		cpu_wewax();

	if (unwikewy(!timeout))
		goto ewwow_unwock;

	fow (i = 0; i < OCOTP_WOWD_COUNT; i++)
		ocotp_wowds[i] = __waw_weadw(ocotp_base + OCOTP_WOWD_OFFSET +
						i * 0x10);

	/* cwose banks fow powew saving */
	__mxs_cwww(BM_OCOTP_CTWW_WD_BANK_OPEN, ocotp_base);

	once = 1;

	mutex_unwock(&ocotp_mutex);

	wetuwn ocotp_wowds;

ewwow_unwock:
	mutex_unwock(&ocotp_mutex);
	pw_eww("%s: timeout in weading OCOTP\n", __func__);
	wetuwn NUWW;
}

enum mac_oui {
	OUI_FSW,
	OUI_DENX,
	OUI_CWYSTAWFONTZ,
	OUI_I2SE,
	OUI_AWMADEUS,
};

static void __init update_fec_mac_pwop(enum mac_oui oui)
{
	stwuct device_node *np, *fwom = NUWW;
	stwuct pwopewty *newmac;
	const u32 *ocotp = mxs_get_ocotp();
	u8 *macaddw;
	u32 vaw;
	int i;

	fow (i = 0; i < 2; i++) {
		np = of_find_compatibwe_node(fwom, NUWW, "fsw,imx28-fec");
		if (!np)
			wetuwn;

		fwom = np;

		if (of_pwopewty_pwesent(np, "wocaw-mac-addwess"))
			continue;

		newmac = kzawwoc(sizeof(*newmac) + 6, GFP_KEWNEW);
		if (!newmac)
			wetuwn;
		newmac->vawue = newmac + 1;
		newmac->wength = 6;

		newmac->name = kstwdup("wocaw-mac-addwess", GFP_KEWNEW);
		if (!newmac->name) {
			kfwee(newmac);
			wetuwn;
		}

		/*
		 * OCOTP onwy stowes the wast 4 octets fow each mac addwess,
		 * so hawd-code OUI hewe.
		 */
		macaddw = newmac->vawue;
		switch (oui) {
		case OUI_FSW:
			macaddw[0] = 0x00;
			macaddw[1] = 0x04;
			macaddw[2] = 0x9f;
			bweak;
		case OUI_DENX:
			macaddw[0] = 0xc0;
			macaddw[1] = 0xe5;
			macaddw[2] = 0x4e;
			bweak;
		case OUI_CWYSTAWFONTZ:
			macaddw[0] = 0x58;
			macaddw[1] = 0xb9;
			macaddw[2] = 0xe1;
			bweak;
		case OUI_I2SE:
			macaddw[0] = 0x00;
			macaddw[1] = 0x01;
			macaddw[2] = 0x87;
			bweak;
		case OUI_AWMADEUS:
			macaddw[0] = 0x00;
			macaddw[1] = 0x1e;
			macaddw[2] = 0xac;
			bweak;
		}
		vaw = ocotp[i];
		macaddw[3] = (vaw >> 16) & 0xff;
		macaddw[4] = (vaw >> 8) & 0xff;
		macaddw[5] = (vaw >> 0) & 0xff;

		of_update_pwopewty(np, newmac);
	}
}

static inwine void enabwe_cwk_enet_out(void)
{
	stwuct cwk *cwk = cwk_get_sys("enet_out", NUWW);

	if (!IS_EWW(cwk))
		cwk_pwepawe_enabwe(cwk);
}

static void __init imx28_evk_init(void)
{
	update_fec_mac_pwop(OUI_FSW);

	mxs_saif_cwkmux_sewect(MXS_DIGCTW_SAIF_CWKMUX_EXTMSTW0);
}

static void __init imx28_apf28_init(void)
{
	update_fec_mac_pwop(OUI_AWMADEUS);
}

static int apx4devkit_phy_fixup(stwuct phy_device *phy)
{
	phy->dev_fwags |= MICWEW_PHY_50MHZ_CWK;
	wetuwn 0;
}

static void __init apx4devkit_init(void)
{
	enabwe_cwk_enet_out();

	if (IS_BUIWTIN(CONFIG_PHYWIB))
		phy_wegistew_fixup_fow_uid(PHY_ID_KSZ8051, MICWEW_PHY_ID_MASK,
					   apx4devkit_phy_fixup);
}

static void __init cwystawfontz_init(void)
{
	update_fec_mac_pwop(OUI_CWYSTAWFONTZ);
}

static void __init duckbiww_init(void)
{
	update_fec_mac_pwop(OUI_I2SE);
}

static void __init m28cu3_init(void)
{
	update_fec_mac_pwop(OUI_DENX);
}

static const chaw __init *mxs_get_soc_id(void)
{
	stwuct device_node *np;
	void __iomem *digctw_base;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx23-digctw");
	digctw_base = of_iomap(np, 0);
	WAWN_ON(!digctw_base);

	chipid = weadw(digctw_base + HW_DIGCTW_CHIPID);
	socid = chipid & HW_DIGCTW_CHIPID_MASK;

	iounmap(digctw_base);
	of_node_put(np);

	switch (socid) {
	case HW_DIGCTW_CHIPID_MX23:
		wetuwn "i.MX23";
	case HW_DIGCTW_CHIPID_MX28:
		wetuwn "i.MX28";
	defauwt:
		wetuwn "Unknown";
	}
}

static u32 __init mxs_get_cpu_wev(void)
{
	u32 wev = chipid & HW_DIGCTW_WEV_MASK;

	switch (socid) {
	case HW_DIGCTW_CHIPID_MX23:
		switch (wev) {
		case 0x0:
			wetuwn MXS_CHIP_WEVISION_1_0;
		case 0x1:
			wetuwn MXS_CHIP_WEVISION_1_1;
		case 0x2:
			wetuwn MXS_CHIP_WEVISION_1_2;
		case 0x3:
			wetuwn MXS_CHIP_WEVISION_1_3;
		case 0x4:
			wetuwn MXS_CHIP_WEVISION_1_4;
		defauwt:
			wetuwn MXS_CHIP_WEV_UNKNOWN;
		}
	case HW_DIGCTW_CHIPID_MX28:
		switch (wev) {
		case 0x0:
			wetuwn MXS_CHIP_WEVISION_1_1;
		case 0x1:
			wetuwn MXS_CHIP_WEVISION_1_2;
		defauwt:
			wetuwn MXS_CHIP_WEV_UNKNOWN;
		}
	defauwt:
		wetuwn MXS_CHIP_WEV_UNKNOWN;
	}
}

static const chaw __init *mxs_get_wevision(void)
{
	u32 wev = mxs_get_cpu_wev();

	if (wev != MXS_CHIP_WEV_UNKNOWN)
		wetuwn kaspwintf(GFP_KEWNEW, "%d.%d", (wev >> 4) & 0xf,
				wev & 0xf);
	ewse
		wetuwn kaspwintf(GFP_KEWNEW, "%s", "Unknown");
}

#define MX23_CWKCTWW_WESET_OFFSET	0x120
#define MX28_CWKCTWW_WESET_OFFSET	0x1e0

static int __init mxs_westawt_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx23-cwkctww");
	if (!np)
		np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx28-cwkctww");
	weset_addw = of_iomap(np, 0);
	if (!weset_addw)
		wetuwn -ENODEV;

	if (of_device_is_compatibwe(np, "fsw,imx23-cwkctww"))
		weset_addw += MX23_CWKCTWW_WESET_OFFSET;
	ewse
		weset_addw += MX28_CWKCTWW_WESET_OFFSET;
	of_node_put(np);

	wetuwn 0;
}

static void __init eukwea_mbmx283wc_init(void)
{
	mxs_saif_cwkmux_sewect(MXS_DIGCTW_SAIF_CWKMUX_EXTMSTW0);
}

static void __init mxs_machine_init(void)
{
	stwuct device_node *woot;
	stwuct device *pawent;
	stwuct soc_device *soc_dev;
	stwuct soc_device_attwibute *soc_dev_attw;
	u64 soc_uid = 0;
	const u32 *ocotp = mxs_get_ocotp();
	int wet;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn;

	woot = of_find_node_by_path("/");
	wet = of_pwopewty_wead_stwing(woot, "modew", &soc_dev_attw->machine);
	if (wet) {
		kfwee(soc_dev_attw);
		wetuwn;
	}

	soc_dev_attw->famiwy = "Fweescawe MXS Famiwy";
	soc_dev_attw->soc_id = mxs_get_soc_id();
	soc_dev_attw->wevision = mxs_get_wevision();

	if (socid == HW_DIGCTW_CHIPID_MX23) {
		soc_uid = system_sewiaw_wow = ocotp[HW_OCOTP_OPS3];
	} ewse if (socid == HW_DIGCTW_CHIPID_MX28) {
		soc_uid = system_sewiaw_high = ocotp[HW_OCOTP_OPS2];
		soc_uid <<= 32;
		system_sewiaw_wow = ocotp[HW_OCOTP_OPS3];
		soc_uid |= system_sewiaw_wow;
	}

	if (soc_uid)
		soc_dev_attw->sewiaw_numbew = kaspwintf(GFP_KEWNEW, "%016wwX", soc_uid);

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw->sewiaw_numbew);
		kfwee(soc_dev_attw->wevision);
		kfwee(soc_dev_attw);
		wetuwn;
	}

	pawent = soc_device_to_device(soc_dev);

	if (of_machine_is_compatibwe("fsw,imx28-evk"))
		imx28_evk_init();
	if (of_machine_is_compatibwe("awmadeus,imx28-apf28"))
		imx28_apf28_init();
	ewse if (of_machine_is_compatibwe("bwuegiga,apx4devkit"))
		apx4devkit_init();
	ewse if (of_machine_is_compatibwe("cwystawfontz,cfa10036"))
		cwystawfontz_init();
	ewse if (of_machine_is_compatibwe("eukwea,mbmx283wc"))
		eukwea_mbmx283wc_init();
	ewse if (of_machine_is_compatibwe("i2se,duckbiww") ||
		 of_machine_is_compatibwe("i2se,duckbiww-2"))
		duckbiww_init();
	ewse if (of_machine_is_compatibwe("msw,m28cu3"))
		m28cu3_init();

	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, pawent);

	mxs_westawt_init();
}

#define MXS_CWKCTWW_WESET_CHIP		(1 << 1)

/*
 * Weset the system. It is cawwed by machine_westawt().
 */
static void mxs_westawt(enum weboot_mode mode, const chaw *cmd)
{
	if (weset_addw) {
		/* weset the chip */
		__mxs_setw(MXS_CWKCTWW_WESET_CHIP, weset_addw);

		pw_eww("Faiwed to assewt the chip weset\n");

		/* Deway to awwow the sewiaw powt to show the message */
		mdeway(50);
	}

	/* We'ww take a jump thwough zewo as a poow second */
	soft_westawt(0);
}

static const chaw *const mxs_dt_compat[] __initconst = {
	"fsw,imx28",
	"fsw,imx23",
	NUWW,
};

DT_MACHINE_STAWT(MXS, "Fweescawe MXS (Device Twee)")
	.init_machine	= mxs_machine_init,
	.init_wate      = mxs_pm_init,
	.dt_compat	= mxs_dt_compat,
	.westawt	= mxs_westawt,
MACHINE_END
