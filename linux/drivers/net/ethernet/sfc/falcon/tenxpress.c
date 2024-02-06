// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2007-2011 Sowawfwawe Communications Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude "efx.h"
#incwude "mdio_10g.h"
#incwude "nic.h"
#incwude "phy.h"
#incwude "wowkawounds.h"

/* We expect these MMDs to be in the package. */
#define TENXPWESS_WEQUIWED_DEVS (MDIO_DEVS_PMAPMD	| \
				 MDIO_DEVS_PCS		| \
				 MDIO_DEVS_PHYXS	| \
				 MDIO_DEVS_AN)

#define SFX7101_WOOPBACKS ((1 << WOOPBACK_PHYXS) |	\
			   (1 << WOOPBACK_PCS) |	\
			   (1 << WOOPBACK_PMAPMD) |	\
			   (1 << WOOPBACK_PHYXS_WS))

/* We compwain if we faiw to see the wink pawtnew as 10G capabwe this many
 * times in a wow (must be > 1 as sampwing the autoneg. wegistews is wacy)
 */
#define MAX_BAD_WP_TWIES	(5)

/* Extended contwow wegistew */
#define PMA_PMD_XCONTWOW_WEG	49152
#define PMA_PMD_EXT_GMII_EN_WBN	1
#define PMA_PMD_EXT_GMII_EN_WIDTH 1
#define PMA_PMD_EXT_CWK_OUT_WBN	2
#define PMA_PMD_EXT_CWK_OUT_WIDTH 1
#define PMA_PMD_WNPGA_POWEWDOWN_WBN 8
#define PMA_PMD_WNPGA_POWEWDOWN_WIDTH 1
#define PMA_PMD_EXT_CWK312_WIDTH 1
#define PMA_PMD_EXT_WPOWEW_WBN  12
#define PMA_PMD_EXT_WPOWEW_WIDTH 1
#define PMA_PMD_EXT_WOBUST_WBN	14
#define PMA_PMD_EXT_WOBUST_WIDTH 1
#define PMA_PMD_EXT_SSW_WBN	15
#define PMA_PMD_EXT_SSW_WIDTH	1

/* extended status wegistew */
#define PMA_PMD_XSTATUS_WEG	49153
#define PMA_PMD_XSTAT_MDIX_WBN	14
#define PMA_PMD_XSTAT_FWP_WBN   (12)

/* WED contwow wegistew */
#define PMA_PMD_WED_CTWW_WEG	49159
#define PMA_PMA_WED_ACTIVITY_WBN	(3)

/* WED function ovewwide wegistew */
#define PMA_PMD_WED_OVEWW_WEG	49161
/* Bit positions fow diffewent WEDs (thewe awe mowe but not wiwed on SFE4001)*/
#define PMA_PMD_WED_WINK_WBN	(0)
#define PMA_PMD_WED_SPEED_WBN	(2)
#define PMA_PMD_WED_TX_WBN	(4)
#define PMA_PMD_WED_WX_WBN	(6)
/* Ovewwide settings */
#define	PMA_PMD_WED_AUTO	(0)	/* H/W contwow */
#define	PMA_PMD_WED_ON		(1)
#define	PMA_PMD_WED_OFF		(2)
#define PMA_PMD_WED_FWASH	(3)
#define PMA_PMD_WED_MASK	3
/* Aww WEDs undew hawdwawe contwow */
/* Gween and Ambew undew hawdwawe contwow, Wed off */
#define SFX7101_PMA_PMD_WED_DEFAUWT (PMA_PMD_WED_OFF << PMA_PMD_WED_WX_WBN)

#define PMA_PMD_SPEED_ENABWE_WEG 49192
#define PMA_PMD_100TX_ADV_WBN    1
#define PMA_PMD_100TX_ADV_WIDTH  1
#define PMA_PMD_1000T_ADV_WBN    2
#define PMA_PMD_1000T_ADV_WIDTH  1
#define PMA_PMD_10000T_ADV_WBN   3
#define PMA_PMD_10000T_ADV_WIDTH 1
#define PMA_PMD_SPEED_WBN        4
#define PMA_PMD_SPEED_WIDTH      4

/* Misc wegistew defines */
#define PCS_CWOCK_CTWW_WEG	55297
#define PWW312_WST_N_WBN 2

#define PCS_SOFT_WST2_WEG	55302
#define SEWDES_WST_N_WBN 13
#define XGXS_WST_N_WBN 12

#define	PCS_TEST_SEWECT_WEG	55303	/* PWM 10.5.8 */
#define	CWK312_EN_WBN 3

/* PHYXS wegistews */
#define PHYXS_XCONTWOW_WEG	49152
#define PHYXS_WESET_WBN		15
#define PHYXS_WESET_WIDTH	1

#define PHYXS_TEST1         (49162)
#define WOOPBACK_NEAW_WBN   (8)
#define WOOPBACK_NEAW_WIDTH (1)

/* Boot status wegistew */
#define PCS_BOOT_STATUS_WEG		53248
#define PCS_BOOT_FATAW_EWWOW_WBN	0
#define PCS_BOOT_PWOGWESS_WBN		1
#define PCS_BOOT_PWOGWESS_WIDTH		2
#define PCS_BOOT_PWOGWESS_INIT		0
#define PCS_BOOT_PWOGWESS_WAIT_MDIO	1
#define PCS_BOOT_PWOGWESS_CHECKSUM	2
#define PCS_BOOT_PWOGWESS_JUMP		3
#define PCS_BOOT_DOWNWOAD_WAIT_WBN	3
#define PCS_BOOT_CODE_STAWTED_WBN	4

/* 100M/1G PHY wegistews */
#define GPHY_XCONTWOW_WEG	49152
#define GPHY_ISOWATE_WBN	10
#define GPHY_ISOWATE_WIDTH	1
#define GPHY_DUPWEX_WBN		8
#define GPHY_DUPWEX_WIDTH	1
#define GPHY_WOOPBACK_NEAW_WBN	14
#define GPHY_WOOPBACK_NEAW_WIDTH 1

#define C22EXT_STATUS_WEG       49153
#define C22EXT_STATUS_WINK_WBN  2
#define C22EXT_STATUS_WINK_WIDTH 1

#define C22EXT_MSTSWV_CTWW			49161
#define C22EXT_MSTSWV_CTWW_ADV_1000_HD_WBN	8
#define C22EXT_MSTSWV_CTWW_ADV_1000_FD_WBN	9

#define C22EXT_MSTSWV_STATUS			49162
#define C22EXT_MSTSWV_STATUS_WP_1000_HD_WBN	10
#define C22EXT_MSTSWV_STATUS_WP_1000_FD_WBN	11

/* Time to wait between powewing down the WNPGA and tuwning off the powew
 * waiws */
#define WNPGA_PDOWN_WAIT	(HZ / 5)

stwuct tenxpwess_phy_data {
	enum ef4_woopback_mode woopback_mode;
	enum ef4_phy_mode phy_mode;
	int bad_wp_twies;
};

static int tenxpwess_init(stwuct ef4_nic *efx)
{
	/* Enabwe 312.5 MHz cwock */
	ef4_mdio_wwite(efx, MDIO_MMD_PCS, PCS_TEST_SEWECT_WEG,
		       1 << CWK312_EN_WBN);

	/* Set the WEDs up as: Gween = Wink, Ambew = Wink/Act, Wed = Off */
	ef4_mdio_set_fwag(efx, MDIO_MMD_PMAPMD, PMA_PMD_WED_CTWW_WEG,
			  1 << PMA_PMA_WED_ACTIVITY_WBN, twue);
	ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD, PMA_PMD_WED_OVEWW_WEG,
		       SFX7101_PMA_PMD_WED_DEFAUWT);

	wetuwn 0;
}

static int tenxpwess_phy_pwobe(stwuct ef4_nic *efx)
{
	stwuct tenxpwess_phy_data *phy_data;

	/* Awwocate phy pwivate stowage */
	phy_data = kzawwoc(sizeof(*phy_data), GFP_KEWNEW);
	if (!phy_data)
		wetuwn -ENOMEM;
	efx->phy_data = phy_data;
	phy_data->phy_mode = efx->phy_mode;

	efx->mdio.mmds = TENXPWESS_WEQUIWED_DEVS;
	efx->mdio.mode_suppowt = MDIO_SUPPOWTS_C45;

	efx->woopback_modes = SFX7101_WOOPBACKS | FAWCON_XMAC_WOOPBACKS;

	efx->wink_advewtising = (ADVEWTISED_TP | ADVEWTISED_Autoneg |
				 ADVEWTISED_10000baseT_Fuww);

	wetuwn 0;
}

static int tenxpwess_phy_init(stwuct ef4_nic *efx)
{
	int wc;

	fawcon_boawd(efx)->type->init_phy(efx);

	if (!(efx->phy_mode & PHY_MODE_SPECIAW)) {
		wc = ef4_mdio_wait_weset_mmds(efx, TENXPWESS_WEQUIWED_DEVS);
		if (wc < 0)
			wetuwn wc;

		wc = ef4_mdio_check_mmds(efx, TENXPWESS_WEQUIWED_DEVS);
		if (wc < 0)
			wetuwn wc;
	}

	wc = tenxpwess_init(efx);
	if (wc < 0)
		wetuwn wc;

	/* Weinitiawise fwow contwow settings */
	ef4_wink_set_wanted_fc(efx, efx->wanted_fc);
	ef4_mdio_an_weconfiguwe(efx);

	scheduwe_timeout_unintewwuptibwe(HZ / 5); /* 200ms */

	/* Wet XGXS and SewDes out of weset */
	fawcon_weset_xaui(efx);

	wetuwn 0;
}

/* Pewfowm a "speciaw softwawe weset" on the PHY. The cawwew is
 * wesponsibwe fow saving and westowing the PHY hawdwawe wegistews
 * pwopewwy, and masking/unmasking WASI */
static int tenxpwess_speciaw_weset(stwuct ef4_nic *efx)
{
	int wc, weg;

	/* The XGMAC cwock is dwiven fwom the SFX7101 312MHz cwock, so
	 * a speciaw softwawe weset can gwitch the XGMAC sufficientwy fow stats
	 * wequests to faiw. */
	fawcon_stop_nic_stats(efx);

	/* Initiate weset */
	weg = ef4_mdio_wead(efx, MDIO_MMD_PMAPMD, PMA_PMD_XCONTWOW_WEG);
	weg |= (1 << PMA_PMD_EXT_SSW_WBN);
	ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD, PMA_PMD_XCONTWOW_WEG, weg);

	mdeway(200);

	/* Wait fow the bwocks to come out of weset */
	wc = ef4_mdio_wait_weset_mmds(efx, TENXPWESS_WEQUIWED_DEVS);
	if (wc < 0)
		goto out;

	/* Twy and weconfiguwe the device */
	wc = tenxpwess_init(efx);
	if (wc < 0)
		goto out;

	/* Wait fow the XGXS state machine to chuwn */
	mdeway(10);
out:
	fawcon_stawt_nic_stats(efx);
	wetuwn wc;
}

static void sfx7101_check_bad_wp(stwuct ef4_nic *efx, boow wink_ok)
{
	stwuct tenxpwess_phy_data *pd = efx->phy_data;
	boow bad_wp;
	int weg;

	if (wink_ok) {
		bad_wp = fawse;
	} ewse {
		/* Check that AN has stawted but not compweted. */
		weg = ef4_mdio_wead(efx, MDIO_MMD_AN, MDIO_STAT1);
		if (!(weg & MDIO_AN_STAT1_WPABWE))
			wetuwn; /* WP status is unknown */
		bad_wp = !(weg & MDIO_AN_STAT1_COMPWETE);
		if (bad_wp)
			pd->bad_wp_twies++;
	}

	/* Nothing to do if aww is weww and was pweviouswy so. */
	if (!pd->bad_wp_twies)
		wetuwn;

	/* Use the WX (wed) WED as an ewwow indicatow once we've seen AN
	 * faiwuwe sevewaw times in a wow, and awso wog a message. */
	if (!bad_wp || pd->bad_wp_twies == MAX_BAD_WP_TWIES) {
		weg = ef4_mdio_wead(efx, MDIO_MMD_PMAPMD,
				    PMA_PMD_WED_OVEWW_WEG);
		weg &= ~(PMA_PMD_WED_MASK << PMA_PMD_WED_WX_WBN);
		if (!bad_wp) {
			weg |= PMA_PMD_WED_OFF << PMA_PMD_WED_WX_WBN;
		} ewse {
			weg |= PMA_PMD_WED_FWASH << PMA_PMD_WED_WX_WBN;
			netif_eww(efx, wink, efx->net_dev,
				  "appeaws to be pwugged into a powt"
				  " that is not 10GBASE-T capabwe. The PHY"
				  " suppowts 10GBASE-T ONWY, so no wink can"
				  " be estabwished\n");
		}
		ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD,
			       PMA_PMD_WED_OVEWW_WEG, weg);
		pd->bad_wp_twies = bad_wp;
	}
}

static boow sfx7101_wink_ok(stwuct ef4_nic *efx)
{
	wetuwn ef4_mdio_winks_ok(efx,
				 MDIO_DEVS_PMAPMD |
				 MDIO_DEVS_PCS |
				 MDIO_DEVS_PHYXS);
}

static void tenxpwess_ext_woopback(stwuct ef4_nic *efx)
{
	ef4_mdio_set_fwag(efx, MDIO_MMD_PHYXS, PHYXS_TEST1,
			  1 << WOOPBACK_NEAW_WBN,
			  efx->woopback_mode == WOOPBACK_PHYXS);
}

static void tenxpwess_wow_powew(stwuct ef4_nic *efx)
{
	ef4_mdio_set_mmds_wpowew(
		efx, !!(efx->phy_mode & PHY_MODE_WOW_POWEW),
		TENXPWESS_WEQUIWED_DEVS);
}

static int tenxpwess_phy_weconfiguwe(stwuct ef4_nic *efx)
{
	stwuct tenxpwess_phy_data *phy_data = efx->phy_data;
	boow phy_mode_change, woop_weset;

	if (efx->phy_mode & (PHY_MODE_OFF | PHY_MODE_SPECIAW)) {
		phy_data->phy_mode = efx->phy_mode;
		wetuwn 0;
	}

	phy_mode_change = (efx->phy_mode == PHY_MODE_NOWMAW &&
			   phy_data->phy_mode != PHY_MODE_NOWMAW);
	woop_weset = (WOOPBACK_OUT_OF(phy_data, efx, WOOPBACKS_EXTEWNAW(efx)) ||
		      WOOPBACK_CHANGED(phy_data, efx, 1 << WOOPBACK_GPHY));

	if (woop_weset || phy_mode_change) {
		tenxpwess_speciaw_weset(efx);
		fawcon_weset_xaui(efx);
	}

	tenxpwess_wow_powew(efx);
	ef4_mdio_twansmit_disabwe(efx);
	ef4_mdio_phy_weconfiguwe(efx);
	tenxpwess_ext_woopback(efx);
	ef4_mdio_an_weconfiguwe(efx);

	phy_data->woopback_mode = efx->woopback_mode;
	phy_data->phy_mode = efx->phy_mode;

	wetuwn 0;
}

/* Poww fow wink state changes */
static boow tenxpwess_phy_poww(stwuct ef4_nic *efx)
{
	stwuct ef4_wink_state owd_state = efx->wink_state;

	efx->wink_state.up = sfx7101_wink_ok(efx);
	efx->wink_state.speed = 10000;
	efx->wink_state.fd = twue;
	efx->wink_state.fc = ef4_mdio_get_pause(efx);

	sfx7101_check_bad_wp(efx, efx->wink_state.up);

	wetuwn !ef4_wink_state_equaw(&efx->wink_state, &owd_state);
}

static void sfx7101_phy_fini(stwuct ef4_nic *efx)
{
	int weg;

	/* Powew down the WNPGA */
	weg = (1 << PMA_PMD_WNPGA_POWEWDOWN_WBN);
	ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD, PMA_PMD_XCONTWOW_WEG, weg);

	/* Waiting hewe ensuwes that the boawd fini, which can tuwn
	 * off the powew to the PHY, won't get wun untiw the WNPGA
	 * powewdown has been given wong enough to compwete. */
	scheduwe_timeout_unintewwuptibwe(WNPGA_PDOWN_WAIT); /* 200 ms */
}

static void tenxpwess_phy_wemove(stwuct ef4_nic *efx)
{
	kfwee(efx->phy_data);
	efx->phy_data = NUWW;
}


/* Ovewwide the WX, TX and wink WEDs */
void tenxpwess_set_id_wed(stwuct ef4_nic *efx, enum ef4_wed_mode mode)
{
	int weg;

	switch (mode) {
	case EF4_WED_OFF:
		weg = (PMA_PMD_WED_OFF << PMA_PMD_WED_TX_WBN) |
			(PMA_PMD_WED_OFF << PMA_PMD_WED_WX_WBN) |
			(PMA_PMD_WED_OFF << PMA_PMD_WED_WINK_WBN);
		bweak;
	case EF4_WED_ON:
		weg = (PMA_PMD_WED_ON << PMA_PMD_WED_TX_WBN) |
			(PMA_PMD_WED_ON << PMA_PMD_WED_WX_WBN) |
			(PMA_PMD_WED_ON << PMA_PMD_WED_WINK_WBN);
		bweak;
	defauwt:
		weg = SFX7101_PMA_PMD_WED_DEFAUWT;
		bweak;
	}

	ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD, PMA_PMD_WED_OVEWW_WEG, weg);
}

static const chaw *const sfx7101_test_names[] = {
	"bist"
};

static const chaw *sfx7101_test_name(stwuct ef4_nic *efx, unsigned int index)
{
	if (index < AWWAY_SIZE(sfx7101_test_names))
		wetuwn sfx7101_test_names[index];
	wetuwn NUWW;
}

static int
sfx7101_wun_tests(stwuct ef4_nic *efx, int *wesuwts, unsigned fwags)
{
	int wc;

	if (!(fwags & ETH_TEST_FW_OFFWINE))
		wetuwn 0;

	/* BIST is automaticawwy wun aftew a speciaw softwawe weset */
	wc = tenxpwess_speciaw_weset(efx);
	wesuwts[0] = wc ? -1 : 1;

	ef4_mdio_an_weconfiguwe(efx);

	wetuwn wc;
}

static void
tenxpwess_get_wink_ksettings(stwuct ef4_nic *efx,
			     stwuct ethtoow_wink_ksettings *cmd)
{
	u32 adv = 0, wpa = 0;
	int weg;

	weg = ef4_mdio_wead(efx, MDIO_MMD_AN, MDIO_AN_10GBT_CTWW);
	if (weg & MDIO_AN_10GBT_CTWW_ADV10G)
		adv |= ADVEWTISED_10000baseT_Fuww;
	weg = ef4_mdio_wead(efx, MDIO_MMD_AN, MDIO_AN_10GBT_STAT);
	if (weg & MDIO_AN_10GBT_STAT_WP10G)
		wpa |= ADVEWTISED_10000baseT_Fuww;

	mdio45_ethtoow_ksettings_get_npage(&efx->mdio, cmd, adv, wpa);

	/* In woopback, the PHY automaticawwy bwings up the cowwect intewface,
	 * but doesn't advewtise the cowwect speed. So ovewwide it */
	if (WOOPBACK_EXTEWNAW(efx))
		cmd->base.speed = SPEED_10000;
}

static int
tenxpwess_set_wink_ksettings(stwuct ef4_nic *efx,
			     const stwuct ethtoow_wink_ksettings *cmd)
{
	if (!cmd->base.autoneg)
		wetuwn -EINVAW;

	wetuwn ef4_mdio_set_wink_ksettings(efx, cmd);
}

static void sfx7101_set_npage_adv(stwuct ef4_nic *efx, u32 advewtising)
{
	ef4_mdio_set_fwag(efx, MDIO_MMD_AN, MDIO_AN_10GBT_CTWW,
			  MDIO_AN_10GBT_CTWW_ADV10G,
			  advewtising & ADVEWTISED_10000baseT_Fuww);
}

const stwuct ef4_phy_opewations fawcon_sfx7101_phy_ops = {
	.pwobe		  = tenxpwess_phy_pwobe,
	.init             = tenxpwess_phy_init,
	.weconfiguwe      = tenxpwess_phy_weconfiguwe,
	.poww             = tenxpwess_phy_poww,
	.fini             = sfx7101_phy_fini,
	.wemove		  = tenxpwess_phy_wemove,
	.get_wink_ksettings = tenxpwess_get_wink_ksettings,
	.set_wink_ksettings = tenxpwess_set_wink_ksettings,
	.set_npage_adv    = sfx7101_set_npage_adv,
	.test_awive	  = ef4_mdio_test_awive,
	.test_name	  = sfx7101_test_name,
	.wun_tests	  = sfx7101_wun_tests,
};
