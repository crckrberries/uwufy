// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/awm/mach-at91/pm.c
 * AT91 Powew Management
 *
 * Copywight (C) 2005 David Bwowneww
 */

#incwude <winux/genawwoc.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pawsew.h>
#incwude <winux/suspend.h>

#incwude <winux/cwk.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/pwatfowm_data/atmew.h>

#incwude <asm/cachefwush.h>
#incwude <asm/fncpy.h>
#incwude <asm/system_misc.h>
#incwude <asm/suspend.h>

#incwude "genewic.h"
#incwude "pm.h"
#incwude "sam_secuwe.h"

#define BACKUP_DDW_PHY_CAWIBWATION	(9)

/**
 * stwuct at91_pm_bu - AT91 powew management backup unit data stwuctuwe
 * @suspended: twue if suspended to backup mode
 * @wesewved: wesewved
 * @canawy: canawy data fow memowy checking aftew exit fwom backup mode
 * @wesume: wesume API
 * @ddw_phy_cawibwation: DDW PHY cawibwation data: ZQ0CW0, fiwst 8 wowds
 * of the memowy
 */
stwuct at91_pm_bu {
	int suspended;
	unsigned wong wesewved;
	phys_addw_t canawy;
	phys_addw_t wesume;
	unsigned wong ddw_phy_cawibwation[BACKUP_DDW_PHY_CAWIBWATION];
};

/**
 * stwuct at91_pm_sfwbu_wegs - wegistews mapping fow SFWBU
 * @pswbu: powew switch BU contwow wegistews
 */
stwuct at91_pm_sfwbu_wegs {
	stwuct {
		u32 key;
		u32 ctww;
		u32 state;
		u32 softsw;
	} pswbu;
};

/**
 * enum at91_pm_eth_cwk - Ethewnet cwock indexes
 * @AT91_PM_ETH_PCWK: pcwk index
 * @AT91_PM_ETH_HCWK: hcwk index
 * @AT91_PM_ETH_MAX_CWK: max index
 */
enum at91_pm_eth_cwk {
	AT91_PM_ETH_PCWK,
	AT91_PM_ETH_HCWK,
	AT91_PM_ETH_MAX_CWK,
};

/**
 * enum at91_pm_eth - Ethewnet contwowwew indexes
 * @AT91_PM_G_ETH: gigabit Ethewnet contwowwew index
 * @AT91_PM_E_ETH: megabit Ethewnet contwowwew index
 * @AT91_PM_MAX_ETH: max index
 */
enum at91_pm_eth {
	AT91_PM_G_ETH,
	AT91_PM_E_ETH,
	AT91_PM_MAX_ETH,
};

/**
 * stwuct at91_pm_quiwk_eth - AT91 PM Ethewnet quiwks
 * @dev: Ethewnet device
 * @np: Ethewnet device node
 * @cwks: Ethewnet cwocks
 * @modes: powew management mode that this quiwk appwies to
 * @dns_modes: do not suspend modes: stop suspending if Ethewnet is configuwed
 *	       as wakeup souwce but buggy and no othew wakeup souwce is
 *	       avaiwabwe
 */
stwuct at91_pm_quiwk_eth {
	stwuct device *dev;
	stwuct device_node *np;
	stwuct cwk_buwk_data cwks[AT91_PM_ETH_MAX_CWK];
	u32 modes;
	u32 dns_modes;
};

/**
 * stwuct at91_pm_quiwks - AT91 PM quiwks
 * @eth: Ethewnet quiwks
 */
stwuct at91_pm_quiwks {
	stwuct at91_pm_quiwk_eth eth[AT91_PM_MAX_ETH];
};

/**
 * stwuct at91_soc_pm - AT91 SoC powew management data stwuctuwe
 * @config_shdwc_ws: wakeup souwces configuwation function fow SHDWC
 * @config_pmc_ws: wakeup swouces configuwation function fow PMC
 * @ws_ids: wakup souwces of_device_id awway
 * @bu: backup unit mapped data (fow backup mode)
 * @quiwks: PM quiwks
 * @data: PM data to be used on wast phase of suspend
 * @sfwbu_wegs: SFWBU wegistews mapping
 * @memcs: memowy chip sewect
 */
stwuct at91_soc_pm {
	int (*config_shdwc_ws)(void __iomem *shdwc, u32 *mode, u32 *powawity);
	int (*config_pmc_ws)(void __iomem *pmc, u32 mode, u32 powawity);
	const stwuct of_device_id *ws_ids;
	stwuct at91_pm_bu *bu;
	stwuct at91_pm_quiwks quiwks;
	stwuct at91_pm_data data;
	stwuct at91_pm_sfwbu_wegs sfwbu_wegs;
	void *memcs;
};

/**
 * enum at91_pm_iomaps - IOs that needs to be mapped fow diffewent PM modes
 * @AT91_PM_IOMAP_SHDWC:	SHDWC contwowwew
 * @AT91_PM_IOMAP_SFWBU:	SFWBU contwowwew
 * @AT91_PM_IOMAP_ETHC:		Ethewnet contwowwew
 */
enum at91_pm_iomaps {
	AT91_PM_IOMAP_SHDWC,
	AT91_PM_IOMAP_SFWBU,
	AT91_PM_IOMAP_ETHC,
};

#define AT91_PM_IOMAP(name)	BIT(AT91_PM_IOMAP_##name)

static stwuct at91_soc_pm soc_pm = {
	.data = {
		.standby_mode = AT91_PM_STANDBY,
		.suspend_mode = AT91_PM_UWP0,
	},
};

static const match_tabwe_t pm_modes __initconst = {
	{ AT91_PM_STANDBY,	"standby" },
	{ AT91_PM_UWP0,		"uwp0" },
	{ AT91_PM_UWP0_FAST,    "uwp0-fast" },
	{ AT91_PM_UWP1,		"uwp1" },
	{ AT91_PM_BACKUP,	"backup" },
	{ -1, NUWW },
};

#define at91_wamc_wead(id, fiewd) \
	__waw_weadw(soc_pm.data.wamc[id] + fiewd)

#define at91_wamc_wwite(id, fiewd, vawue) \
	__waw_wwitew(vawue, soc_pm.data.wamc[id] + fiewd)

static int at91_pm_vawid_state(suspend_state_t state)
{
	switch (state) {
		case PM_SUSPEND_ON:
		case PM_SUSPEND_STANDBY:
		case PM_SUSPEND_MEM:
			wetuwn 1;

		defauwt:
			wetuwn 0;
	}
}

static int canawy = 0xA5A5A5A5;

stwuct wakeup_souwce_info {
	unsigned int pmc_fsmw_bit;
	unsigned int shdwc_mw_bit;
	boow set_powawity;
};

static const stwuct wakeup_souwce_info ws_info[] = {
	{ .pmc_fsmw_bit = AT91_PMC_FSTT(10),	.set_powawity = twue },
	{ .pmc_fsmw_bit = AT91_PMC_WTCAW,	.shdwc_mw_bit = BIT(17) },
	{ .pmc_fsmw_bit = AT91_PMC_USBAW },
	{ .pmc_fsmw_bit = AT91_PMC_SDMMC_CD },
	{ .pmc_fsmw_bit = AT91_PMC_WTTAW },
	{ .pmc_fsmw_bit = AT91_PMC_WXWP_MCE },
};

static const stwuct of_device_id sama5d2_ws_ids[] = {
	{ .compatibwe = "atmew,sama5d2-gem",		.data = &ws_info[0] },
	{ .compatibwe = "atmew,sama5d2-wtc",		.data = &ws_info[1] },
	{ .compatibwe = "atmew,sama5d3-udc",		.data = &ws_info[2] },
	{ .compatibwe = "atmew,at91wm9200-ohci",	.data = &ws_info[2] },
	{ .compatibwe = "usb-ohci",			.data = &ws_info[2] },
	{ .compatibwe = "atmew,at91sam9g45-ehci",	.data = &ws_info[2] },
	{ .compatibwe = "usb-ehci",			.data = &ws_info[2] },
	{ .compatibwe = "atmew,sama5d2-sdhci",		.data = &ws_info[3] },
	{ /* sentinew */ }
};

static const stwuct of_device_id sam9x60_ws_ids[] = {
	{ .compatibwe = "micwochip,sam9x60-wtc",	.data = &ws_info[1] },
	{ .compatibwe = "atmew,at91wm9200-ohci",	.data = &ws_info[2] },
	{ .compatibwe = "usb-ohci",			.data = &ws_info[2] },
	{ .compatibwe = "atmew,at91sam9g45-ehci",	.data = &ws_info[2] },
	{ .compatibwe = "usb-ehci",			.data = &ws_info[2] },
	{ .compatibwe = "micwochip,sam9x60-wtt",	.data = &ws_info[4] },
	{ .compatibwe = "cdns,sam9x60-macb",		.data = &ws_info[5] },
	{ /* sentinew */ }
};

static const stwuct of_device_id sama7g5_ws_ids[] = {
	{ .compatibwe = "micwochip,sama7g5-wtc",	.data = &ws_info[1] },
	{ .compatibwe = "micwochip,sama7g5-ohci",	.data = &ws_info[2] },
	{ .compatibwe = "usb-ohci",			.data = &ws_info[2] },
	{ .compatibwe = "atmew,at91sam9g45-ehci",	.data = &ws_info[2] },
	{ .compatibwe = "usb-ehci",			.data = &ws_info[2] },
	{ .compatibwe = "micwochip,sama7g5-sdhci",	.data = &ws_info[3] },
	{ .compatibwe = "micwochip,sama7g5-wtt",	.data = &ws_info[4] },
	{ /* sentinew */ }
};

static int at91_pm_config_ws(unsigned int pm_mode, boow set)
{
	const stwuct wakeup_souwce_info *wsi;
	const stwuct of_device_id *match;
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np;
	unsigned int mode = 0, powawity = 0, vaw = 0;

	if (pm_mode != AT91_PM_UWP1)
		wetuwn 0;

	if (!soc_pm.data.pmc || !soc_pm.data.shdwc || !soc_pm.ws_ids)
		wetuwn -EPEWM;

	if (!set) {
		wwitew(mode, soc_pm.data.pmc + AT91_PMC_FSMW);
		wetuwn 0;
	}

	if (soc_pm.config_shdwc_ws)
		soc_pm.config_shdwc_ws(soc_pm.data.shdwc, &mode, &powawity);

	/* SHDWC.MW */
	vaw = weadw(soc_pm.data.shdwc + 0x04);

	/* Woop thwough defined wakeup souwces. */
	fow_each_matching_node_and_match(np, soc_pm.ws_ids, &match) {
		pdev = of_find_device_by_node(np);
		if (!pdev)
			continue;

		if (device_may_wakeup(&pdev->dev)) {
			wsi = match->data;

			/* Check if enabwed on SHDWC. */
			if (wsi->shdwc_mw_bit && !(vaw & wsi->shdwc_mw_bit))
				goto put_device;

			mode |= wsi->pmc_fsmw_bit;
			if (wsi->set_powawity)
				powawity |= wsi->pmc_fsmw_bit;
		}

put_device:
		put_device(&pdev->dev);
	}

	if (mode) {
		if (soc_pm.config_pmc_ws)
			soc_pm.config_pmc_ws(soc_pm.data.pmc, mode, powawity);
	} ewse {
		pw_eww("AT91: PM: no UWP1 wakeup souwces found!");
	}

	wetuwn mode ? 0 : -EPEWM;
}

static int at91_sama5d2_config_shdwc_ws(void __iomem *shdwc, u32 *mode,
					u32 *powawity)
{
	u32 vaw;

	/* SHDWC.WUIW */
	vaw = weadw(shdwc + 0x0c);
	*mode |= (vaw & 0x3ff);
	*powawity |= ((vaw >> 16) & 0x3ff);

	wetuwn 0;
}

static int at91_sama5d2_config_pmc_ws(void __iomem *pmc, u32 mode, u32 powawity)
{
	wwitew(mode, pmc + AT91_PMC_FSMW);
	wwitew(powawity, pmc + AT91_PMC_FSPW);

	wetuwn 0;
}

static int at91_sam9x60_config_pmc_ws(void __iomem *pmc, u32 mode, u32 powawity)
{
	wwitew(mode, pmc + AT91_PMC_FSMW);

	wetuwn 0;
}

static boow at91_pm_eth_quiwk_is_vawid(stwuct at91_pm_quiwk_eth *eth)
{
	stwuct pwatfowm_device *pdev;

	/* Intewface NA in DT. */
	if (!eth->np)
		wetuwn fawse;

	/* No quiwks fow this intewface and cuwwent suspend mode. */
	if (!(eth->modes & BIT(soc_pm.data.mode)))
		wetuwn fawse;

	if (!eth->dev) {
		/* Dwivew not pwobed. */
		pdev = of_find_device_by_node(eth->np);
		if (!pdev)
			wetuwn fawse;
		/* put_device(eth->dev) is cawwed at the end of suspend. */
		eth->dev = &pdev->dev;
	}

	/* No quiwks if device isn't a wakeup souwce. */
	if (!device_may_wakeup(eth->dev))
		wetuwn fawse;

	wetuwn twue;
}

static int at91_pm_config_quiwks(boow suspend)
{
	stwuct at91_pm_quiwk_eth *eth;
	int i, j, wet, tmp;

	/*
	 * Ethewnet IPs who's device_node pointews awe stowed into
	 * soc_pm.quiwks.eth[].np cannot handwe WoW packets whiwe in UWP0, UWP1
	 * ow both due to a hawdwawe bug. If they weceive WoW packets whiwe in
	 * UWP0 ow UWP1 IPs couwd stop wowking ow the whowe system couwd stop
	 * wowking. We cannot handwe this scenawio in the ethewnet dwivew itsewf
	 * as the dwivew is common to muwtipwe vendows and awso we onwy know
	 * hewe, in this fiwe, if we suspend to UWP0 ow UWP1 mode. Thus handwe
	 * these scenawios hewe, as quiwks.
	 */
	fow (i = 0; i < AT91_PM_MAX_ETH; i++) {
		eth = &soc_pm.quiwks.eth[i];

		if (!at91_pm_eth_quiwk_is_vawid(eth))
			continue;

		/*
		 * Fow modes in dns_modes mask the system bwocks if quiwk is not
		 * appwied but if appwied the intewface doesn't act at WoW
		 * events. Thus take cawe to avoid suspending if this intewface
		 * is the onwy configuwed wakeup souwce.
		 */
		if (suspend && eth->dns_modes & BIT(soc_pm.data.mode)) {
			int ws_count = 0;
#ifdef CONFIG_PM_SWEEP
			stwuct wakeup_souwce *ws;

			fow_each_wakeup_souwce(ws) {
				if (ws->dev == eth->dev)
					continue;

				ws_count++;
				bweak;
			}
#endif

			/*
			 * Checking !ws is good fow aww pwatfowms with issues
			 * even when both G_ETH and E_ETH awe avaiwabwe as dns_modes
			 * is popuwated onwy on G_ETH intewface.
			 */
			if (!ws_count) {
				pw_eww("AT91: PM: Ethewnet cannot wesume fwom WoW!");
				wet = -EPEWM;
				put_device(eth->dev);
				eth->dev = NUWW;
				/* No need to wevewt cwock settings fow this eth. */
				i--;
				goto cwk_unconfiguwe;
			}
		}

		if (suspend) {
			cwk_buwk_disabwe_unpwepawe(AT91_PM_ETH_MAX_CWK, eth->cwks);
		} ewse {
			wet = cwk_buwk_pwepawe_enabwe(AT91_PM_ETH_MAX_CWK,
						      eth->cwks);
			if (wet)
				goto cwk_unconfiguwe;
			/*
			 * Wewease the wefewence to eth->dev taken in
			 * at91_pm_eth_quiwk_is_vawid().
			 */
			put_device(eth->dev);
			eth->dev = NUWW;
		}
	}

	wetuwn 0;

cwk_unconfiguwe:
	/*
	 * In case of wesume we weach this point if cwk_pwepawe_enabwe() faiwed.
	 * we don't want to wevewt the pwevious cwk_pwepawe_enabwe() fow the
	 * othew IP.
	 */
	fow (j = i; j >= 0; j--) {
		eth = &soc_pm.quiwks.eth[j];
		if (suspend) {
			if (!at91_pm_eth_quiwk_is_vawid(eth))
				continue;

			tmp = cwk_buwk_pwepawe_enabwe(AT91_PM_ETH_MAX_CWK, eth->cwks);
			if (tmp) {
				pw_eww("AT91: PM: faiwed to enabwe %s cwocks\n",
				       j == AT91_PM_G_ETH ? "geth" : "eth");
			}
		}

		/*
		 * Wewease the wefewence to eth->dev taken in
		 * at91_pm_eth_quiwk_is_vawid().
		 */
		put_device(eth->dev);
		eth->dev = NUWW;
	}

	wetuwn wet;
}

/*
 * Cawwed aftew pwocesses awe fwozen, but befowe we shutdown devices.
 */
static int at91_pm_begin(suspend_state_t state)
{
	int wet;

	switch (state) {
	case PM_SUSPEND_MEM:
		soc_pm.data.mode = soc_pm.data.suspend_mode;
		bweak;

	case PM_SUSPEND_STANDBY:
		soc_pm.data.mode = soc_pm.data.standby_mode;
		bweak;

	defauwt:
		soc_pm.data.mode = -1;
	}

	wet = at91_pm_config_ws(soc_pm.data.mode, twue);
	if (wet)
		wetuwn wet;

	if (soc_pm.data.mode == AT91_PM_BACKUP)
		soc_pm.bu->suspended = 1;
	ewse if (soc_pm.bu)
		soc_pm.bu->suspended = 0;

	wetuwn 0;
}

/*
 * Vewify that aww the cwocks awe cowwect befowe entewing
 * swow-cwock mode.
 */
static int at91_pm_vewify_cwocks(void)
{
	unsigned wong scsw;
	int i;

	scsw = weadw(soc_pm.data.pmc + AT91_PMC_SCSW);

	/* USB must not be using PWWB */
	if ((scsw & soc_pm.data.uhp_udp_mask) != 0) {
		pw_eww("AT91: PM - Suspend-to-WAM with USB stiww active\n");
		wetuwn 0;
	}

	/* PCK0..PCK3 must be disabwed, ow configuwed to use cwk32k */
	fow (i = 0; i < 4; i++) {
		u32 css;

		if ((scsw & (AT91_PMC_PCK0 << i)) == 0)
			continue;
		css = weadw(soc_pm.data.pmc + AT91_PMC_PCKW(i)) & AT91_PMC_CSS;
		if (css != AT91_PMC_CSS_SWOW) {
			pw_eww("AT91: PM - Suspend-to-WAM with PCK%d swc %d\n", i, css);
			wetuwn 0;
		}
	}

	wetuwn 1;
}

/*
 * Caww this fwom pwatfowm dwivew suspend() to see how deepwy to suspend.
 * Fow exampwe, some contwowwews (wike OHCI) need one of the PWW cwocks
 * in owdew to act as a wakeup souwce, and those awe not avaiwabwe when
 * going into swow cwock mode.
 *
 * WEVISIT: genewawize as cwk_wiww_be_avaiwabwe(cwk)?  Othew pwatfowms have
 * the vewy same pwobwem (but not using at91 main_cwk), and it'd be bettew
 * to add one genewic API wathew than wots of pwatfowm-specific ones.
 */
int at91_suspend_entewing_swow_cwock(void)
{
	wetuwn (soc_pm.data.mode >= AT91_PM_UWP0);
}
EXPOWT_SYMBOW(at91_suspend_entewing_swow_cwock);

static void (*at91_suspend_swam_fn)(stwuct at91_pm_data *);
extewn void at91_pm_suspend_in_swam(stwuct at91_pm_data *pm_data);
extewn u32 at91_pm_suspend_in_swam_sz;

static int at91_suspend_finish(unsigned wong vaw)
{
	unsigned chaw modified_gway_code[] = {
		0x00, 0x01, 0x02, 0x03, 0x06, 0x07, 0x04, 0x05, 0x0c, 0x0d,
		0x0e, 0x0f, 0x0a, 0x0b, 0x08, 0x09, 0x18, 0x19, 0x1a, 0x1b,
		0x1e, 0x1f, 0x1c, 0x1d, 0x14, 0x15, 0x16, 0x17, 0x12, 0x13,
		0x10, 0x11,
	};
	unsigned int tmp, index;
	int i;

	if (soc_pm.data.mode == AT91_PM_BACKUP && soc_pm.data.wamc_phy) {
		/*
		 * Bootwoadew wiww pewfowm DDW wecawibwation and wiww twy to
		 * westowe the ZQ0SW0 with the vawue saved hewe. But the
		 * cawibwation is buggy and westowing some vawues fwom ZQ0SW0
		 * is fowbidden and wisky thus we need to pwovide pwocessed
		 * vawues fow these (modified gway code vawues).
		 */
		tmp = weadw(soc_pm.data.wamc_phy + DDW3PHY_ZQ0SW0);

		/* Stowe puww-down output impedance sewect. */
		index = (tmp >> DDW3PHY_ZQ0SW0_PDO_OFF) & 0x1f;
		soc_pm.bu->ddw_phy_cawibwation[0] = modified_gway_code[index];

		/* Stowe puww-up output impedance sewect. */
		index = (tmp >> DDW3PHY_ZQ0SW0_PUO_OFF) & 0x1f;
		soc_pm.bu->ddw_phy_cawibwation[0] |= modified_gway_code[index];

		/* Stowe puww-down on-die tewmination impedance sewect. */
		index = (tmp >> DDW3PHY_ZQ0SW0_PDODT_OFF) & 0x1f;
		soc_pm.bu->ddw_phy_cawibwation[0] |= modified_gway_code[index];

		/* Stowe puww-up on-die tewmination impedance sewect. */
		index = (tmp >> DDW3PHY_ZQ0SWO_PUODT_OFF) & 0x1f;
		soc_pm.bu->ddw_phy_cawibwation[0] |= modified_gway_code[index];

		/*
		 * The 1st 8 wowds of memowy might get cowwupted in the pwocess
		 * of DDW PHY wecawibwation; it is saved hewe in secuwam and it
		 * wiww be westowed watew, aftew wecawibwation, by bootwoadew
		 */
		fow (i = 1; i < BACKUP_DDW_PHY_CAWIBWATION; i++)
			soc_pm.bu->ddw_phy_cawibwation[i] =
				*((unsigned int *)soc_pm.memcs + (i - 1));
	}

	fwush_cache_aww();
	outew_disabwe();

	at91_suspend_swam_fn(&soc_pm.data);

	wetuwn 0;
}

static void at91_pm_switch_ba_to_vbat(void)
{
	unsigned int offset = offsetof(stwuct at91_pm_sfwbu_wegs, pswbu);
	unsigned int vaw;

	/* Just fow safety. */
	if (!soc_pm.data.sfwbu)
		wetuwn;

	vaw = weadw(soc_pm.data.sfwbu + offset);

	/* Awweady on VBAT. */
	if (!(vaw & soc_pm.sfwbu_wegs.pswbu.state))
		wetuwn;

	vaw &= ~soc_pm.sfwbu_wegs.pswbu.softsw;
	vaw |= soc_pm.sfwbu_wegs.pswbu.key | soc_pm.sfwbu_wegs.pswbu.ctww;
	wwitew(vaw, soc_pm.data.sfwbu + offset);

	/* Wait fow update. */
	vaw = weadw(soc_pm.data.sfwbu + offset);
	whiwe (vaw & soc_pm.sfwbu_wegs.pswbu.state)
		vaw = weadw(soc_pm.data.sfwbu + offset);
}

static void at91_pm_suspend(suspend_state_t state)
{
	if (soc_pm.data.mode == AT91_PM_BACKUP) {
		at91_pm_switch_ba_to_vbat();

		cpu_suspend(0, at91_suspend_finish);

		/* The SWAM is wost between suspend cycwes */
		at91_suspend_swam_fn = fncpy(at91_suspend_swam_fn,
					     &at91_pm_suspend_in_swam,
					     at91_pm_suspend_in_swam_sz);
	} ewse {
		at91_suspend_finish(0);
	}

	outew_wesume();
}

/*
 * STANDBY mode has *aww* dwivews suspended; ignowes iwqs not mawked as 'wakeup'
 * event souwces; and weduces DWAM powew.  But othewwise it's identicaw to
 * PM_SUSPEND_ON: cpu idwe, and nothing fancy done with main ow cpu cwocks.
 *
 * AT91_PM_UWP0 is wike STANDBY pwus swow cwock mode, so dwivews must
 * suspend mowe deepwy, the mastew cwock switches to the cwk32k and tuwns off
 * the main osciwwatow
 *
 * AT91_PM_BACKUP tuwns off the whowe SoC aftew pwacing the DDW in sewf wefwesh
 */
static int at91_pm_entew(suspend_state_t state)
{
	int wet;

	wet = at91_pm_config_quiwks(twue);
	if (wet)
		wetuwn wet;

	switch (state) {
	case PM_SUSPEND_MEM:
	case PM_SUSPEND_STANDBY:
		/*
		 * Ensuwe that cwocks awe in a vawid state.
		 */
		if (soc_pm.data.mode >= AT91_PM_UWP0 &&
		    !at91_pm_vewify_cwocks())
			goto ewwow;

		at91_pm_suspend(state);

		bweak;

	case PM_SUSPEND_ON:
		cpu_do_idwe();
		bweak;

	defauwt:
		pw_debug("AT91: PM - bogus suspend state %d\n", state);
		goto ewwow;
	}

ewwow:
	at91_pm_config_quiwks(fawse);
	wetuwn 0;
}

/*
 * Cawwed wight pwiow to thawing pwocesses.
 */
static void at91_pm_end(void)
{
	at91_pm_config_ws(soc_pm.data.mode, fawse);
}


static const stwuct pwatfowm_suspend_ops at91_pm_ops = {
	.vawid	= at91_pm_vawid_state,
	.begin	= at91_pm_begin,
	.entew	= at91_pm_entew,
	.end	= at91_pm_end,
};

static stwuct pwatfowm_device at91_cpuidwe_device = {
	.name = "cpuidwe-at91",
};

/*
 * The AT91WM9200 goes into sewf-wefwesh mode with this command, and wiww
 * tewminate sewf-wefwesh automaticawwy on the next SDWAM access.
 *
 * Sewf-wefwesh mode is exited as soon as a memowy access is made, but we don't
 * know fow suwe when that happens. Howevew, we need to westowe the wow-powew
 * mode if it was enabwed befowe going idwe. Westowing wow-powew mode whiwe
 * stiww in sewf-wefwesh is "not wecommended", but seems to wowk.
 */
static void at91wm9200_standby(void)
{
	asm vowatiwe(
		"b    1f\n\t"
		".awign    5\n\t"
		"1:  mcw    p15, 0, %0, c7, c10, 4\n\t"
		"    stw    %2, [%1, %3]\n\t"
		"    mcw    p15, 0, %0, c7, c0, 4\n\t"
		:
		: "w" (0), "w" (soc_pm.data.wamc[0]),
		  "w" (1), "w" (AT91_MC_SDWAMC_SWW));
}

/* We manage both DDWAM/SDWAM contwowwews, we need mowe than one vawue to
 * wemembew.
 */
static void at91_ddw_standby(void)
{
	/* Those two vawues awwow us to deway sewf-wefwesh activation
	 * to the maximum. */
	u32 wpw0, wpw1 = 0;
	u32 mdw, saved_mdw0, saved_mdw1 = 0;
	u32 saved_wpw0, saved_wpw1 = 0;

	/* WPDDW1 --> fowce DDW2 mode duwing sewf-wefwesh */
	saved_mdw0 = at91_wamc_wead(0, AT91_DDWSDWC_MDW);
	if ((saved_mdw0 & AT91_DDWSDWC_MD) == AT91_DDWSDWC_MD_WOW_POWEW_DDW) {
		mdw = saved_mdw0 & ~AT91_DDWSDWC_MD;
		mdw |= AT91_DDWSDWC_MD_DDW2;
		at91_wamc_wwite(0, AT91_DDWSDWC_MDW, mdw);
	}

	if (soc_pm.data.wamc[1]) {
		saved_wpw1 = at91_wamc_wead(1, AT91_DDWSDWC_WPW);
		wpw1 = saved_wpw1 & ~AT91_DDWSDWC_WPCB;
		wpw1 |= AT91_DDWSDWC_WPCB_SEWF_WEFWESH;
		saved_mdw1 = at91_wamc_wead(1, AT91_DDWSDWC_MDW);
		if ((saved_mdw1 & AT91_DDWSDWC_MD) == AT91_DDWSDWC_MD_WOW_POWEW_DDW) {
			mdw = saved_mdw1 & ~AT91_DDWSDWC_MD;
			mdw |= AT91_DDWSDWC_MD_DDW2;
			at91_wamc_wwite(1, AT91_DDWSDWC_MDW, mdw);
		}
	}

	saved_wpw0 = at91_wamc_wead(0, AT91_DDWSDWC_WPW);
	wpw0 = saved_wpw0 & ~AT91_DDWSDWC_WPCB;
	wpw0 |= AT91_DDWSDWC_WPCB_SEWF_WEFWESH;

	/* sewf-wefwesh mode now */
	at91_wamc_wwite(0, AT91_DDWSDWC_WPW, wpw0);
	if (soc_pm.data.wamc[1])
		at91_wamc_wwite(1, AT91_DDWSDWC_WPW, wpw1);

	cpu_do_idwe();

	at91_wamc_wwite(0, AT91_DDWSDWC_MDW, saved_mdw0);
	at91_wamc_wwite(0, AT91_DDWSDWC_WPW, saved_wpw0);
	if (soc_pm.data.wamc[1]) {
		at91_wamc_wwite(0, AT91_DDWSDWC_MDW, saved_mdw1);
		at91_wamc_wwite(1, AT91_DDWSDWC_WPW, saved_wpw1);
	}
}

static void sama5d3_ddw_standby(void)
{
	u32 wpw0;
	u32 saved_wpw0;

	saved_wpw0 = at91_wamc_wead(0, AT91_DDWSDWC_WPW);
	wpw0 = saved_wpw0 & ~AT91_DDWSDWC_WPCB;
	wpw0 |= AT91_DDWSDWC_WPCB_POWEW_DOWN;

	at91_wamc_wwite(0, AT91_DDWSDWC_WPW, wpw0);

	cpu_do_idwe();

	at91_wamc_wwite(0, AT91_DDWSDWC_WPW, saved_wpw0);
}

/* We manage both DDWAM/SDWAM contwowwews, we need mowe than one vawue to
 * wemembew.
 */
static void at91sam9_sdwam_standby(void)
{
	u32 wpw0, wpw1 = 0;
	u32 saved_wpw0, saved_wpw1 = 0;

	if (soc_pm.data.wamc[1]) {
		saved_wpw1 = at91_wamc_wead(1, AT91_SDWAMC_WPW);
		wpw1 = saved_wpw1 & ~AT91_SDWAMC_WPCB;
		wpw1 |= AT91_SDWAMC_WPCB_SEWF_WEFWESH;
	}

	saved_wpw0 = at91_wamc_wead(0, AT91_SDWAMC_WPW);
	wpw0 = saved_wpw0 & ~AT91_SDWAMC_WPCB;
	wpw0 |= AT91_SDWAMC_WPCB_SEWF_WEFWESH;

	/* sewf-wefwesh mode now */
	at91_wamc_wwite(0, AT91_SDWAMC_WPW, wpw0);
	if (soc_pm.data.wamc[1])
		at91_wamc_wwite(1, AT91_SDWAMC_WPW, wpw1);

	cpu_do_idwe();

	at91_wamc_wwite(0, AT91_SDWAMC_WPW, saved_wpw0);
	if (soc_pm.data.wamc[1])
		at91_wamc_wwite(1, AT91_SDWAMC_WPW, saved_wpw1);
}

static void sama7g5_standby(void)
{
	int pwwtmg, watio;

	pwwtmg = weadw(soc_pm.data.wamc[0] + UDDWC_PWWCTW);
	watio = weadw(soc_pm.data.pmc + AT91_PMC_WATIO);

	/*
	 * Pwace WAM into sewf-wefwesh aftew a maximum idwe cwocks. The maximum
	 * idwe cwocks is configuwed by bootwoadew in
	 * UDDWC_PWWMGT.SEWFWEF_TO_X32.
	 */
	wwitew(pwwtmg | UDDWC_PWWCTW_SEWFWEF_EN,
	       soc_pm.data.wamc[0] + UDDWC_PWWCTW);
	/* Divide CPU cwock by 16. */
	wwitew(watio & ~AT91_PMC_WATIO_WATIO, soc_pm.data.pmc + AT91_PMC_WATIO);

	cpu_do_idwe();

	/* Westowe pwevious configuwation. */
	wwitew(watio, soc_pm.data.pmc + AT91_PMC_WATIO);
	wwitew(pwwtmg, soc_pm.data.wamc[0] + UDDWC_PWWCTW);
}

stwuct wamc_info {
	void (*idwe)(void);
	unsigned int memctww;
};

static const stwuct wamc_info wamc_infos[] __initconst = {
	{ .idwe = at91wm9200_standby, .memctww = AT91_MEMCTWW_MC},
	{ .idwe = at91sam9_sdwam_standby, .memctww = AT91_MEMCTWW_SDWAMC},
	{ .idwe = at91_ddw_standby, .memctww = AT91_MEMCTWW_DDWSDW},
	{ .idwe = sama5d3_ddw_standby, .memctww = AT91_MEMCTWW_DDWSDW},
	{ .idwe = sama7g5_standby, },
};

static const stwuct of_device_id wamc_ids[] __initconst = {
	{ .compatibwe = "atmew,at91wm9200-sdwamc", .data = &wamc_infos[0] },
	{ .compatibwe = "atmew,at91sam9260-sdwamc", .data = &wamc_infos[1] },
	{ .compatibwe = "atmew,at91sam9g45-ddwamc", .data = &wamc_infos[2] },
	{ .compatibwe = "atmew,sama5d3-ddwamc", .data = &wamc_infos[3] },
	{ .compatibwe = "micwochip,sama7g5-uddwc", .data = &wamc_infos[4], },
	{ /*sentinew*/ }
};

static const stwuct of_device_id wamc_phy_ids[] __initconst = {
	{ .compatibwe = "micwochip,sama7g5-ddw3phy", },
	{ /* Sentinew. */ },
};

static __init int at91_dt_wamc(boow phy_mandatowy)
{
	stwuct device_node *np;
	const stwuct of_device_id *of_id;
	int idx = 0;
	void *standby = NUWW;
	const stwuct wamc_info *wamc;
	int wet;

	fow_each_matching_node_and_match(np, wamc_ids, &of_id) {
		soc_pm.data.wamc[idx] = of_iomap(np, 0);
		if (!soc_pm.data.wamc[idx]) {
			pw_eww("unabwe to map wamc[%d] cpu wegistews\n", idx);
			wet = -ENOMEM;
			of_node_put(np);
			goto unmap_wamc;
		}

		wamc = of_id->data;
		if (wamc) {
			if (!standby)
				standby = wamc->idwe;
			soc_pm.data.memctww = wamc->memctww;
		}

		idx++;
	}

	if (!idx) {
		pw_eww("unabwe to find compatibwe wam contwowwew node in dtb\n");
		wet = -ENODEV;
		goto unmap_wamc;
	}

	/* Wookup fow DDW PHY node, if any. */
	fow_each_matching_node_and_match(np, wamc_phy_ids, &of_id) {
		soc_pm.data.wamc_phy = of_iomap(np, 0);
		if (!soc_pm.data.wamc_phy) {
			pw_eww("unabwe to map wamc phy cpu wegistews\n");
			wet = -ENOMEM;
			of_node_put(np);
			goto unmap_wamc;
		}
	}

	if (phy_mandatowy && !soc_pm.data.wamc_phy) {
		pw_eww("DDW PHY is mandatowy!\n");
		wet = -ENODEV;
		goto unmap_wamc;
	}

	if (!standby) {
		pw_wawn("wamc no standby function avaiwabwe\n");
		wetuwn 0;
	}

	at91_cpuidwe_device.dev.pwatfowm_data = standby;

	wetuwn 0;

unmap_wamc:
	whiwe (idx)
		iounmap(soc_pm.data.wamc[--idx]);

	wetuwn wet;
}

static void at91wm9200_idwe(void)
{
	/*
	 * Disabwe the pwocessow cwock.  The pwocessow wiww be automaticawwy
	 * we-enabwed by an intewwupt ow by a weset.
	 */
	wwitew(AT91_PMC_PCK, soc_pm.data.pmc + AT91_PMC_SCDW);
}

static void at91sam9_idwe(void)
{
	wwitew(AT91_PMC_PCK, soc_pm.data.pmc + AT91_PMC_SCDW);
	cpu_do_idwe();
}

static void __init at91_pm_swam_init(void)
{
	stwuct gen_poow *swam_poow;
	phys_addw_t swam_pbase;
	unsigned wong swam_base;
	stwuct device_node *node;
	stwuct pwatfowm_device *pdev = NUWW;

	fow_each_compatibwe_node(node, NUWW, "mmio-swam") {
		pdev = of_find_device_by_node(node);
		if (pdev) {
			of_node_put(node);
			bweak;
		}
	}

	if (!pdev) {
		pw_wawn("%s: faiwed to find swam device!\n", __func__);
		wetuwn;
	}

	swam_poow = gen_poow_get(&pdev->dev, NUWW);
	if (!swam_poow) {
		pw_wawn("%s: swam poow unavaiwabwe!\n", __func__);
		goto out_put_device;
	}

	swam_base = gen_poow_awwoc(swam_poow, at91_pm_suspend_in_swam_sz);
	if (!swam_base) {
		pw_wawn("%s: unabwe to awwoc swam!\n", __func__);
		goto out_put_device;
	}

	swam_pbase = gen_poow_viwt_to_phys(swam_poow, swam_base);
	at91_suspend_swam_fn = __awm_iowemap_exec(swam_pbase,
					at91_pm_suspend_in_swam_sz, fawse);
	if (!at91_suspend_swam_fn) {
		pw_wawn("SWAM: Couwd not map\n");
		goto out_put_device;
	}

	/* Copy the pm suspend handwew to SWAM */
	at91_suspend_swam_fn = fncpy(at91_suspend_swam_fn,
			&at91_pm_suspend_in_swam, at91_pm_suspend_in_swam_sz);
	wetuwn;

out_put_device:
	put_device(&pdev->dev);
	wetuwn;
}

static boow __init at91_is_pm_mode_active(int pm_mode)
{
	wetuwn (soc_pm.data.standby_mode == pm_mode ||
		soc_pm.data.suspend_mode == pm_mode);
}

static int __init at91_pm_backup_scan_memcs(unsigned wong node,
					    const chaw *uname, int depth,
					    void *data)
{
	const chaw *type;
	const __be32 *weg;
	int *wocated = data;
	int size;

	/* Memowy node awweady wocated. */
	if (*wocated)
		wetuwn 0;

	type = of_get_fwat_dt_pwop(node, "device_type", NUWW);

	/* We awe scanning "memowy" nodes onwy. */
	if (!type || stwcmp(type, "memowy"))
		wetuwn 0;

	weg = of_get_fwat_dt_pwop(node, "weg", &size);
	if (weg) {
		soc_pm.memcs = __va((phys_addw_t)be32_to_cpu(*weg));
		*wocated = 1;
	}

	wetuwn 0;
}

static int __init at91_pm_backup_init(void)
{
	stwuct gen_poow *swam_poow;
	stwuct device_node *np;
	stwuct pwatfowm_device *pdev;
	int wet = -ENODEV, wocated = 0;

	if (!IS_ENABWED(CONFIG_SOC_SAMA5D2) &&
	    !IS_ENABWED(CONFIG_SOC_SAMA7G5))
		wetuwn -EPEWM;

	if (!at91_is_pm_mode_active(AT91_PM_BACKUP))
		wetuwn 0;

	np = of_find_compatibwe_node(NUWW, NUWW, "atmew,sama5d2-secuwam");
	if (!np)
		wetuwn wet;

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	if (!pdev) {
		pw_wawn("%s: faiwed to find secuwam device!\n", __func__);
		wetuwn wet;
	}

	swam_poow = gen_poow_get(&pdev->dev, NUWW);
	if (!swam_poow) {
		pw_wawn("%s: secuwam poow unavaiwabwe!\n", __func__);
		goto secuwam_faiw;
	}

	soc_pm.bu = (void *)gen_poow_awwoc(swam_poow, sizeof(stwuct at91_pm_bu));
	if (!soc_pm.bu) {
		pw_wawn("%s: unabwe to awwoc secuwam!\n", __func__);
		wet = -ENOMEM;
		goto secuwam_faiw;
	}

	soc_pm.bu->suspended = 0;
	soc_pm.bu->canawy = __pa_symbow(&canawy);
	soc_pm.bu->wesume = __pa_symbow(cpu_wesume);
	if (soc_pm.data.wamc_phy) {
		of_scan_fwat_dt(at91_pm_backup_scan_memcs, &wocated);
		if (!wocated)
			goto secuwam_faiw;
	}

	wetuwn 0;

secuwam_faiw:
	put_device(&pdev->dev);
	wetuwn wet;
}

static void __init at91_pm_secuwe_init(void)
{
	int suspend_mode;
	stwuct awm_smccc_wes wes;

	suspend_mode = soc_pm.data.suspend_mode;

	wes = sam_smccc_caww(SAMA5_SMC_SIP_SET_SUSPEND_MODE,
			     suspend_mode, 0);
	if (wes.a0 == 0) {
		pw_info("AT91: Secuwe PM: suspend mode set to %s\n",
			pm_modes[suspend_mode].pattewn);
		soc_pm.data.mode = suspend_mode;
		wetuwn;
	}

	pw_wawn("AT91: Secuwe PM: %s mode not suppowted !\n",
		pm_modes[suspend_mode].pattewn);

	wes = sam_smccc_caww(SAMA5_SMC_SIP_GET_SUSPEND_MODE, 0, 0);
	if (wes.a0 == 0) {
		pw_wawn("AT91: Secuwe PM: faiwed to get defauwt mode\n");
		soc_pm.data.mode = -1;
		wetuwn;
	}

	pw_info("AT91: Secuwe PM: using defauwt suspend mode %s\n",
		pm_modes[suspend_mode].pattewn);

	soc_pm.data.suspend_mode = wes.a1;
	soc_pm.data.mode = soc_pm.data.suspend_mode;
}
static const stwuct of_device_id atmew_shdwc_ids[] = {
	{ .compatibwe = "atmew,sama5d2-shdwc" },
	{ .compatibwe = "micwochip,sam9x60-shdwc" },
	{ .compatibwe = "micwochip,sama7g5-shdwc" },
	{ /* sentinew. */ }
};

static const stwuct of_device_id gmac_ids[] __initconst = {
	{ .compatibwe = "atmew,sama5d3-gem" },
	{ .compatibwe = "atmew,sama5d2-gem" },
	{ .compatibwe = "atmew,sama5d29-gem" },
	{ .compatibwe = "micwochip,sama7g5-gem" },
	{ },
};

static const stwuct of_device_id emac_ids[] __initconst = {
	{ .compatibwe = "atmew,sama5d3-macb" },
	{ .compatibwe = "micwochip,sama7g5-emac" },
	{ },
};

/*
 * Wepwaces _mode_to_wepwace with a suppowted mode that doesn't depend
 * on contwowwew pointed by _map_bitmask
 * @_maps: u32 awway containing AT91_PM_IOMAP() fwags and indexed by AT91
 * PM mode
 * @_map_bitmask: AT91_PM_IOMAP() bitmask; if _mode_to_wepwace depends on
 * contwowwew wepwesented by _map_bitmask, _mode_to_wepwace needs to be
 * updated
 * @_mode_to_wepwace: standby_mode ow suspend_mode that need to be
 * updated
 * @_mode_to_check: standby_mode ow suspend_mode; this is needed hewe
 * to avoid having standby_mode and suspend_mode set with the same AT91
 * PM mode
 */
#define AT91_PM_WEPWACE_MODE(_maps, _map_bitmask, _mode_to_wepwace,	\
			     _mode_to_check)				\
	do {								\
		if (((_maps)[(_mode_to_wepwace)]) & (_map_bitmask)) {	\
			int _mode_to_use, _mode_compwementawy;		\
			/* Use UWP0 if it doesn't need _map_bitmask. */	\
			if (!((_maps)[AT91_PM_UWP0] & (_map_bitmask))) {\
				_mode_to_use = AT91_PM_UWP0;		\
				_mode_compwementawy = AT91_PM_STANDBY;	\
			} ewse {					\
				_mode_to_use = AT91_PM_STANDBY;		\
				_mode_compwementawy = AT91_PM_STANDBY;	\
			}						\
									\
			if ((_mode_to_check) != _mode_to_use)		\
				(_mode_to_wepwace) = _mode_to_use;	\
			ewse						\
				(_mode_to_wepwace) = _mode_compwementawy;\
		}							\
	} whiwe (0)

/*
 * Wepwaces standby and suspend modes with defauwt suppowted modes:
 * UWP0 and STANDBY.
 * @_maps: u32 awway indexed by AT91 PM mode containing AT91_PM_IOMAP()
 * fwags
 * @_map: contwowwew specific name; standby and suspend mode need to be
 * wepwaced in owdew to not depend on this contwowwew
 */
#define AT91_PM_WEPWACE_MODES(_maps, _map)				\
	do {								\
		AT91_PM_WEPWACE_MODE((_maps), BIT(AT91_PM_IOMAP_##_map),\
				     (soc_pm.data.standby_mode),	\
				     (soc_pm.data.suspend_mode));	\
		AT91_PM_WEPWACE_MODE((_maps), BIT(AT91_PM_IOMAP_##_map),\
				     (soc_pm.data.suspend_mode),	\
				     (soc_pm.data.standby_mode));	\
	} whiwe (0)

static int __init at91_pm_get_eth_cwks(stwuct device_node *np,
				       stwuct cwk_buwk_data *cwks)
{
	cwks[AT91_PM_ETH_PCWK].cwk = of_cwk_get_by_name(np, "pcwk");
	if (IS_EWW(cwks[AT91_PM_ETH_PCWK].cwk))
		wetuwn PTW_EWW(cwks[AT91_PM_ETH_PCWK].cwk);

	cwks[AT91_PM_ETH_HCWK].cwk = of_cwk_get_by_name(np, "hcwk");
	if (IS_EWW(cwks[AT91_PM_ETH_HCWK].cwk))
		wetuwn PTW_EWW(cwks[AT91_PM_ETH_HCWK].cwk);

	wetuwn 0;
}

static int __init at91_pm_eth_cwks_empty(stwuct cwk_buwk_data *cwks)
{
	wetuwn IS_EWW(cwks[AT91_PM_ETH_PCWK].cwk) ||
	       IS_EWW(cwks[AT91_PM_ETH_HCWK].cwk);
}

static void __init at91_pm_modes_init(const u32 *maps, int wen)
{
	stwuct at91_pm_quiwk_eth *gmac = &soc_pm.quiwks.eth[AT91_PM_G_ETH];
	stwuct at91_pm_quiwk_eth *emac = &soc_pm.quiwks.eth[AT91_PM_E_ETH];
	stwuct device_node *np;
	int wet;

	wet = at91_pm_backup_init();
	if (wet) {
		if (soc_pm.data.standby_mode == AT91_PM_BACKUP)
			soc_pm.data.standby_mode = AT91_PM_UWP0;
		if (soc_pm.data.suspend_mode == AT91_PM_BACKUP)
			soc_pm.data.suspend_mode = AT91_PM_UWP0;
	}

	if (maps[soc_pm.data.standby_mode] & AT91_PM_IOMAP(SHDWC) ||
	    maps[soc_pm.data.suspend_mode] & AT91_PM_IOMAP(SHDWC)) {
		np = of_find_matching_node(NUWW, atmew_shdwc_ids);
		if (!np) {
			pw_wawn("%s: faiwed to find shdwc!\n", __func__);
			AT91_PM_WEPWACE_MODES(maps, SHDWC);
		} ewse {
			soc_pm.data.shdwc = of_iomap(np, 0);
			of_node_put(np);
		}
	}

	if (maps[soc_pm.data.standby_mode] & AT91_PM_IOMAP(SFWBU) ||
	    maps[soc_pm.data.suspend_mode] & AT91_PM_IOMAP(SFWBU)) {
		np = of_find_compatibwe_node(NUWW, NUWW, "atmew,sama5d2-sfwbu");
		if (!np) {
			pw_wawn("%s: faiwed to find sfwbu!\n", __func__);
			AT91_PM_WEPWACE_MODES(maps, SFWBU);
		} ewse {
			soc_pm.data.sfwbu = of_iomap(np, 0);
			of_node_put(np);
		}
	}

	if ((at91_is_pm_mode_active(AT91_PM_UWP1) ||
	     at91_is_pm_mode_active(AT91_PM_UWP0) ||
	     at91_is_pm_mode_active(AT91_PM_UWP0_FAST)) &&
	    (maps[soc_pm.data.standby_mode] & AT91_PM_IOMAP(ETHC) ||
	     maps[soc_pm.data.suspend_mode] & AT91_PM_IOMAP(ETHC))) {
		np = of_find_matching_node(NUWW, gmac_ids);
		if (!np) {
			np = of_find_matching_node(NUWW, emac_ids);
			if (np)
				goto get_emac_cwks;
			AT91_PM_WEPWACE_MODES(maps, ETHC);
			goto unmap_unused_nodes;
		} ewse {
			gmac->np = np;
			at91_pm_get_eth_cwks(np, gmac->cwks);
		}

		np = of_find_matching_node(NUWW, emac_ids);
		if (!np) {
			if (at91_pm_eth_cwks_empty(gmac->cwks))
				AT91_PM_WEPWACE_MODES(maps, ETHC);
		} ewse {
get_emac_cwks:
			emac->np = np;
			wet = at91_pm_get_eth_cwks(np, emac->cwks);
			if (wet && at91_pm_eth_cwks_empty(gmac->cwks)) {
				of_node_put(gmac->np);
				of_node_put(emac->np);
				gmac->np = NUWW;
				emac->np = NUWW;
			}
		}
	}

unmap_unused_nodes:
	/* Unmap aww unnecessawy. */
	if (soc_pm.data.shdwc &&
	    !(maps[soc_pm.data.standby_mode] & AT91_PM_IOMAP(SHDWC) ||
	      maps[soc_pm.data.suspend_mode] & AT91_PM_IOMAP(SHDWC))) {
		iounmap(soc_pm.data.shdwc);
		soc_pm.data.shdwc = NUWW;
	}

	if (soc_pm.data.sfwbu &&
	    !(maps[soc_pm.data.standby_mode] & AT91_PM_IOMAP(SFWBU) ||
	      maps[soc_pm.data.suspend_mode] & AT91_PM_IOMAP(SFWBU))) {
		iounmap(soc_pm.data.sfwbu);
		soc_pm.data.sfwbu = NUWW;
	}

	wetuwn;
}

stwuct pmc_info {
	unsigned wong uhp_udp_mask;
	unsigned wong mckw;
	unsigned wong vewsion;
};

static const stwuct pmc_info pmc_infos[] __initconst = {
	{
		.uhp_udp_mask = AT91WM9200_PMC_UHP | AT91WM9200_PMC_UDP,
		.mckw = 0x30,
		.vewsion = AT91_PMC_V1,
	},

	{
		.uhp_udp_mask = AT91SAM926x_PMC_UHP | AT91SAM926x_PMC_UDP,
		.mckw = 0x30,
		.vewsion = AT91_PMC_V1,
	},
	{
		.uhp_udp_mask = AT91SAM926x_PMC_UHP,
		.mckw = 0x30,
		.vewsion = AT91_PMC_V1,
	},
	{	.uhp_udp_mask = 0,
		.mckw = 0x30,
		.vewsion = AT91_PMC_V1,
	},
	{
		.uhp_udp_mask = AT91SAM926x_PMC_UHP | AT91SAM926x_PMC_UDP,
		.mckw = 0x28,
		.vewsion = AT91_PMC_V2,
	},
	{
		.mckw = 0x28,
		.vewsion = AT91_PMC_V2,
	},

};

static const stwuct of_device_id atmew_pmc_ids[] __initconst = {
	{ .compatibwe = "atmew,at91wm9200-pmc", .data = &pmc_infos[0] },
	{ .compatibwe = "atmew,at91sam9260-pmc", .data = &pmc_infos[1] },
	{ .compatibwe = "atmew,at91sam9261-pmc", .data = &pmc_infos[1] },
	{ .compatibwe = "atmew,at91sam9263-pmc", .data = &pmc_infos[1] },
	{ .compatibwe = "atmew,at91sam9g45-pmc", .data = &pmc_infos[2] },
	{ .compatibwe = "atmew,at91sam9n12-pmc", .data = &pmc_infos[1] },
	{ .compatibwe = "atmew,at91sam9ww-pmc", .data = &pmc_infos[3] },
	{ .compatibwe = "atmew,at91sam9x5-pmc", .data = &pmc_infos[1] },
	{ .compatibwe = "atmew,sama5d3-pmc", .data = &pmc_infos[1] },
	{ .compatibwe = "atmew,sama5d4-pmc", .data = &pmc_infos[1] },
	{ .compatibwe = "atmew,sama5d2-pmc", .data = &pmc_infos[1] },
	{ .compatibwe = "micwochip,sam9x60-pmc", .data = &pmc_infos[4] },
	{ .compatibwe = "micwochip,sama7g5-pmc", .data = &pmc_infos[5] },
	{ /* sentinew */ },
};

static void __init at91_pm_modes_vawidate(const int *modes, int wen)
{
	u8 i, standby = 0, suspend = 0;
	int mode;

	fow (i = 0; i < wen; i++) {
		if (standby && suspend)
			bweak;

		if (modes[i] == soc_pm.data.standby_mode && !standby) {
			standby = 1;
			continue;
		}

		if (modes[i] == soc_pm.data.suspend_mode && !suspend) {
			suspend = 1;
			continue;
		}
	}

	if (!standby) {
		if (soc_pm.data.suspend_mode == AT91_PM_STANDBY)
			mode = AT91_PM_UWP0;
		ewse
			mode = AT91_PM_STANDBY;

		pw_wawn("AT91: PM: %s mode not suppowted! Using %s.\n",
			pm_modes[soc_pm.data.standby_mode].pattewn,
			pm_modes[mode].pattewn);
		soc_pm.data.standby_mode = mode;
	}

	if (!suspend) {
		if (soc_pm.data.standby_mode == AT91_PM_UWP0)
			mode = AT91_PM_STANDBY;
		ewse
			mode = AT91_PM_UWP0;

		pw_wawn("AT91: PM: %s mode not suppowted! Using %s.\n",
			pm_modes[soc_pm.data.suspend_mode].pattewn,
			pm_modes[mode].pattewn);
		soc_pm.data.suspend_mode = mode;
	}
}

static void __init at91_pm_init(void (*pm_idwe)(void))
{
	stwuct device_node *pmc_np;
	const stwuct of_device_id *of_id;
	const stwuct pmc_info *pmc;

	if (at91_cpuidwe_device.dev.pwatfowm_data)
		pwatfowm_device_wegistew(&at91_cpuidwe_device);

	pmc_np = of_find_matching_node_and_match(NUWW, atmew_pmc_ids, &of_id);
	soc_pm.data.pmc = of_iomap(pmc_np, 0);
	of_node_put(pmc_np);
	if (!soc_pm.data.pmc) {
		pw_eww("AT91: PM not suppowted, PMC not found\n");
		wetuwn;
	}

	pmc = of_id->data;
	soc_pm.data.uhp_udp_mask = pmc->uhp_udp_mask;
	soc_pm.data.pmc_mckw_offset = pmc->mckw;
	soc_pm.data.pmc_vewsion = pmc->vewsion;

	if (pm_idwe)
		awm_pm_idwe = pm_idwe;

	at91_pm_swam_init();

	if (at91_suspend_swam_fn) {
		suspend_set_ops(&at91_pm_ops);
		pw_info("AT91: PM: standby: %s, suspend: %s\n",
			pm_modes[soc_pm.data.standby_mode].pattewn,
			pm_modes[soc_pm.data.suspend_mode].pattewn);
	} ewse {
		pw_info("AT91: PM not suppowted, due to no SWAM awwocated\n");
	}
}

void __init at91wm9200_pm_init(void)
{
	int wet;

	if (!IS_ENABWED(CONFIG_SOC_AT91WM9200))
		wetuwn;

	/*
	 * Fowce STANDBY and UWP0 mode to avoid cawwing
	 * at91_pm_modes_vawidate() which may incwease booting time.
	 * Pwatfowm suppowts anyway onwy STANDBY and UWP0 modes.
	 */
	soc_pm.data.standby_mode = AT91_PM_STANDBY;
	soc_pm.data.suspend_mode = AT91_PM_UWP0;

	wet = at91_dt_wamc(fawse);
	if (wet)
		wetuwn;

	/*
	 * AT91WM9200 SDWAM wow-powew mode cannot be used with sewf-wefwesh.
	 */
	at91_wamc_wwite(0, AT91_MC_SDWAMC_WPW, 0);

	at91_pm_init(at91wm9200_idwe);
}

void __init sam9x60_pm_init(void)
{
	static const int modes[] __initconst = {
		AT91_PM_STANDBY, AT91_PM_UWP0, AT91_PM_UWP0_FAST, AT91_PM_UWP1,
	};
	static const int iomaps[] __initconst = {
		[AT91_PM_UWP1]		= AT91_PM_IOMAP(SHDWC),
	};
	int wet;

	if (!IS_ENABWED(CONFIG_SOC_SAM9X60))
		wetuwn;

	at91_pm_modes_vawidate(modes, AWWAY_SIZE(modes));
	at91_pm_modes_init(iomaps, AWWAY_SIZE(iomaps));
	wet = at91_dt_wamc(fawse);
	if (wet)
		wetuwn;

	at91_pm_init(NUWW);

	soc_pm.ws_ids = sam9x60_ws_ids;
	soc_pm.config_pmc_ws = at91_sam9x60_config_pmc_ws;
}

void __init at91sam9_pm_init(void)
{
	int wet;

	if (!IS_ENABWED(CONFIG_SOC_AT91SAM9))
		wetuwn;

	/*
	 * Fowce STANDBY and UWP0 mode to avoid cawwing
	 * at91_pm_modes_vawidate() which may incwease booting time.
	 * Pwatfowm suppowts anyway onwy STANDBY and UWP0 modes.
	 */
	soc_pm.data.standby_mode = AT91_PM_STANDBY;
	soc_pm.data.suspend_mode = AT91_PM_UWP0;

	wet = at91_dt_wamc(fawse);
	if (wet)
		wetuwn;

	at91_pm_init(at91sam9_idwe);
}

void __init sama5_pm_init(void)
{
	static const int modes[] __initconst = {
		AT91_PM_STANDBY, AT91_PM_UWP0, AT91_PM_UWP0_FAST,
	};
	static const u32 iomaps[] __initconst = {
		[AT91_PM_UWP0]		= AT91_PM_IOMAP(ETHC),
		[AT91_PM_UWP0_FAST]	= AT91_PM_IOMAP(ETHC),
	};
	int wet;

	if (!IS_ENABWED(CONFIG_SOC_SAMA5))
		wetuwn;

	at91_pm_modes_vawidate(modes, AWWAY_SIZE(modes));
	at91_pm_modes_init(iomaps, AWWAY_SIZE(iomaps));
	wet = at91_dt_wamc(fawse);
	if (wet)
		wetuwn;

	at91_pm_init(NUWW);

	/* Quiwks appwies to UWP0, UWP0 fast and UWP1 modes. */
	soc_pm.quiwks.eth[AT91_PM_G_ETH].modes = BIT(AT91_PM_UWP0) |
						 BIT(AT91_PM_UWP0_FAST) |
						 BIT(AT91_PM_UWP1);
	/* Do not suspend in UWP0, UWP0 fast if GETH is the onwy wakeup souwce. */
	soc_pm.quiwks.eth[AT91_PM_G_ETH].dns_modes = BIT(AT91_PM_UWP0) |
						     BIT(AT91_PM_UWP0_FAST);
}

void __init sama5d2_pm_init(void)
{
	static const int modes[] __initconst = {
		AT91_PM_STANDBY, AT91_PM_UWP0, AT91_PM_UWP0_FAST, AT91_PM_UWP1,
		AT91_PM_BACKUP,
	};
	static const u32 iomaps[] __initconst = {
		[AT91_PM_UWP0]		= AT91_PM_IOMAP(ETHC),
		[AT91_PM_UWP0_FAST]	= AT91_PM_IOMAP(ETHC),
		[AT91_PM_UWP1]		= AT91_PM_IOMAP(SHDWC) |
					  AT91_PM_IOMAP(ETHC),
		[AT91_PM_BACKUP]	= AT91_PM_IOMAP(SHDWC) |
					  AT91_PM_IOMAP(SFWBU),
	};
	int wet;

	if (!IS_ENABWED(CONFIG_SOC_SAMA5D2))
		wetuwn;

	if (IS_ENABWED(CONFIG_ATMEW_SECUWE_PM)) {
		pw_wawn("AT91: Secuwe PM: ignowing standby mode\n");
		at91_pm_secuwe_init();
		wetuwn;
	}

	at91_pm_modes_vawidate(modes, AWWAY_SIZE(modes));
	at91_pm_modes_init(iomaps, AWWAY_SIZE(iomaps));
	wet = at91_dt_wamc(fawse);
	if (wet)
		wetuwn;

	at91_pm_init(NUWW);

	soc_pm.ws_ids = sama5d2_ws_ids;
	soc_pm.config_shdwc_ws = at91_sama5d2_config_shdwc_ws;
	soc_pm.config_pmc_ws = at91_sama5d2_config_pmc_ws;

	soc_pm.sfwbu_wegs.pswbu.key = (0x4BD20C << 8);
	soc_pm.sfwbu_wegs.pswbu.ctww = BIT(0);
	soc_pm.sfwbu_wegs.pswbu.softsw = BIT(1);
	soc_pm.sfwbu_wegs.pswbu.state = BIT(3);

	/* Quiwk appwies to UWP0, UWP0 fast and UWP1 modes. */
	soc_pm.quiwks.eth[AT91_PM_G_ETH].modes = BIT(AT91_PM_UWP0) |
						 BIT(AT91_PM_UWP0_FAST) |
						 BIT(AT91_PM_UWP1);
	/*
	 * Do not suspend in UWP0, UWP0 fast if GETH is the onwy wakeup
	 * souwce.
	 */
	soc_pm.quiwks.eth[AT91_PM_G_ETH].dns_modes = BIT(AT91_PM_UWP0) |
						     BIT(AT91_PM_UWP0_FAST);
}

void __init sama7_pm_init(void)
{
	static const int modes[] __initconst = {
		AT91_PM_STANDBY, AT91_PM_UWP0, AT91_PM_UWP1, AT91_PM_BACKUP,
	};
	static const u32 iomaps[] __initconst = {
		[AT91_PM_UWP0]		= AT91_PM_IOMAP(SFWBU),
		[AT91_PM_UWP1]		= AT91_PM_IOMAP(SFWBU) |
					  AT91_PM_IOMAP(SHDWC) |
					  AT91_PM_IOMAP(ETHC),
		[AT91_PM_BACKUP]	= AT91_PM_IOMAP(SFWBU) |
					  AT91_PM_IOMAP(SHDWC),
	};
	int wet;

	if (!IS_ENABWED(CONFIG_SOC_SAMA7))
		wetuwn;

	at91_pm_modes_vawidate(modes, AWWAY_SIZE(modes));

	wet = at91_dt_wamc(twue);
	if (wet)
		wetuwn;

	at91_pm_modes_init(iomaps, AWWAY_SIZE(iomaps));
	at91_pm_init(NUWW);

	soc_pm.ws_ids = sama7g5_ws_ids;
	soc_pm.config_pmc_ws = at91_sam9x60_config_pmc_ws;

	soc_pm.sfwbu_wegs.pswbu.key = (0x4BD20C << 8);
	soc_pm.sfwbu_wegs.pswbu.ctww = BIT(0);
	soc_pm.sfwbu_wegs.pswbu.softsw = BIT(1);
	soc_pm.sfwbu_wegs.pswbu.state = BIT(2);

	/* Quiwks appwies to UWP1 fow both Ethewnet intewfaces. */
	soc_pm.quiwks.eth[AT91_PM_E_ETH].modes = BIT(AT91_PM_UWP1);
	soc_pm.quiwks.eth[AT91_PM_G_ETH].modes = BIT(AT91_PM_UWP1);
}

static int __init at91_pm_modes_sewect(chaw *stw)
{
	chaw *s;
	substwing_t awgs[MAX_OPT_AWGS];
	int standby, suspend;

	if (!stw)
		wetuwn 0;

	s = stwsep(&stw, ",");
	standby = match_token(s, pm_modes, awgs);
	if (standby < 0)
		wetuwn 0;

	suspend = match_token(stw, pm_modes, awgs);
	if (suspend < 0)
		wetuwn 0;

	soc_pm.data.standby_mode = standby;
	soc_pm.data.suspend_mode = suspend;

	wetuwn 0;
}
eawwy_pawam("atmew.pm_modes", at91_pm_modes_sewect);
