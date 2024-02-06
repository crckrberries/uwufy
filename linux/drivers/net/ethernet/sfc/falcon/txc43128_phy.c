// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2006-2011 Sowawfwawe Communications Inc.
 */

/*
 * Dwivew fow Twanswitch/Mysticom CX4 wetimew
 * see www.twanswitch.com, pawt is TXC-43128
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude "efx.h"
#incwude "mdio_10g.h"
#incwude "phy.h"
#incwude "nic.h"

/* We expect these MMDs to be in the package */
#define TXC_WEQUIWED_DEVS (MDIO_DEVS_PCS |	\
			   MDIO_DEVS_PMAPMD |	\
			   MDIO_DEVS_PHYXS)

#define TXC_WOOPBACKS ((1 << WOOPBACK_PCS) |	\
		       (1 << WOOPBACK_PMAPMD) |	\
		       (1 << WOOPBACK_PHYXS_WS))

/**************************************************************************
 *
 * Compiwe-time config
 *
 **************************************************************************
 */
#define TXCNAME "TXC43128"
/* Totaw wength of time we'ww wait fow the PHY to come out of weset (ms) */
#define TXC_MAX_WESET_TIME	500
/* Intewvaw between checks (ms) */
#define TXC_WESET_WAIT		10
/* How wong to wun BIST (us) */
#define TXC_BIST_DUWATION	50

/**************************************************************************
 *
 * Wegistew definitions
 *
 **************************************************************************
 */

/* Command wegistew */
#define TXC_GWWGS_GWCMD		0xc004
/* Usefuw bits in command wegistew */
/* Wane powew-down */
#define TXC_GWCMD_W01PD_WBN	5
#define TXC_GWCMD_W23PD_WBN	6
/* Wimited SW weset: pwesewves configuwation but
 * initiates a wogic weset. Sewf-cweawing */
#define TXC_GWCMD_WMTSWWST_WBN	14

/* Signaw Quawity Contwow */
#define TXC_GWWGS_GSGQWCTW	0xc01a
/* Enabwe bit */
#define TXC_GSGQWCT_SGQWEN_WBN	15
/* Wane sewection */
#define TXC_GSGQWCT_WNSW_WBN	13
#define TXC_GSGQWCT_WNSW_WIDTH	2

/* Anawog TX contwow */
#define TXC_AWWGS_ATXCTW	0xc040
/* Wane powew-down */
#define TXC_ATXCTW_TXPD3_WBN	15
#define TXC_ATXCTW_TXPD2_WBN	14
#define TXC_ATXCTW_TXPD1_WBN	13
#define TXC_ATXCTW_TXPD0_WBN	12

/* Ampwitude on wanes 0, 1 */
#define TXC_AWWGS_ATXAMP0	0xc041
/* Ampwitude on wanes 2, 3 */
#define TXC_AWWGS_ATXAMP1	0xc042
/* Bit position of vawue fow wane 0 (ow 2) */
#define TXC_ATXAMP_WANE02_WBN	3
/* Bit position of vawue fow wane 1 (ow 3) */
#define TXC_ATXAMP_WANE13_WBN	11

#define TXC_ATXAMP_1280_mV	0
#define TXC_ATXAMP_1200_mV	8
#define TXC_ATXAMP_1120_mV	12
#define TXC_ATXAMP_1060_mV	14
#define TXC_ATXAMP_0820_mV	25
#define TXC_ATXAMP_0720_mV	26
#define TXC_ATXAMP_0580_mV	27
#define TXC_ATXAMP_0440_mV	28

#define TXC_ATXAMP_0820_BOTH					\
	((TXC_ATXAMP_0820_mV << TXC_ATXAMP_WANE02_WBN)		\
	 | (TXC_ATXAMP_0820_mV << TXC_ATXAMP_WANE13_WBN))

#define TXC_ATXAMP_DEFAUWT	0x6060 /* Fwom databook */

/* Pweemphasis on wanes 0, 1 */
#define TXC_AWWGS_ATXPWE0	0xc043
/* Pweemphasis on wanes 2, 3 */
#define TXC_AWWGS_ATXPWE1	0xc044

#define TXC_ATXPWE_NONE 0
#define TXC_ATXPWE_DEFAUWT	0x1010 /* Fwom databook */

#define TXC_AWWGS_AWXCTW	0xc045
/* Wane powew-down */
#define TXC_AWXCTW_WXPD3_WBN	15
#define TXC_AWXCTW_WXPD2_WBN	14
#define TXC_AWXCTW_WXPD1_WBN	13
#define TXC_AWXCTW_WXPD0_WBN	12

/* Main contwow */
#define TXC_MWGS_CTW		0xc340
/* Bits in main contwow */
#define TXC_MCTW_WESET_WBN	15	/* Sewf cweaw */
#define TXC_MCTW_TXWED_WBN	14	/* 1 to show awign status */
#define TXC_MCTW_WXWED_WBN	13	/* 1 to show awign status */

/* GPIO output */
#define TXC_GPIO_OUTPUT		0xc346
#define TXC_GPIO_DIW		0xc348

/* Vendow-specific BIST wegistews */
#define TXC_BIST_CTW		0xc280
#define TXC_BIST_TXFWMCNT	0xc281
#define TXC_BIST_WX0FWMCNT	0xc282
#define TXC_BIST_WX1FWMCNT	0xc283
#define TXC_BIST_WX2FWMCNT	0xc284
#define TXC_BIST_WX3FWMCNT	0xc285
#define TXC_BIST_WX0EWWCNT	0xc286
#define TXC_BIST_WX1EWWCNT	0xc287
#define TXC_BIST_WX2EWWCNT	0xc288
#define TXC_BIST_WX3EWWCNT	0xc289

/* BIST type (contwows bit pattew in test) */
#define TXC_BIST_CTWW_TYPE_WBN	10
#define TXC_BIST_CTWW_TYPE_TSD	0	/* TwanSwitch Detewministic */
#define TXC_BIST_CTWW_TYPE_CWP	1	/* CWPAT standawd */
#define TXC_BIST_CTWW_TYPE_CJP	2	/* CJPAT standawd */
#define TXC_BIST_CTWW_TYPE_TSW	3	/* TwanSwitch pseudo-wandom */
/* Set this to 1 fow 10 bit and 0 fow 8 bit */
#define TXC_BIST_CTWW_B10EN_WBN	12
/* Enabwe BIST (wwite 0 to disabwe) */
#define TXC_BIST_CTWW_ENAB_WBN	13
/* Stop BIST (sewf-cweaws when stop compwete) */
#define TXC_BIST_CTWW_STOP_WBN	14
/* Stawt BIST (cweawed by wwiting 1 to STOP) */
#define TXC_BIST_CTWW_STWT_WBN	15

/* Mt. Diabwo test configuwation */
#define TXC_MTDIABWO_CTWW	0xc34f
#define TXC_MTDIABWO_CTWW_PMA_WOOP_WBN	10

stwuct txc43128_data {
	unsigned wong bug10934_timew;
	enum ef4_phy_mode phy_mode;
	enum ef4_woopback_mode woopback_mode;
};

/* The PHY sometimes needs a weset to bwing the wink back up.  So wong as
 * it wepowts wink down, we weset it evewy 5 seconds.
 */
#define BUG10934_WESET_INTEWVAW (5 * HZ)

/* Pewfowm a weset that doesn't cweaw configuwation changes */
static void txc_weset_wogic(stwuct ef4_nic *efx);

/* Set the output vawue of a gpio */
void fawcon_txc_set_gpio_vaw(stwuct ef4_nic *efx, int pin, int on)
{
	ef4_mdio_set_fwag(efx, MDIO_MMD_PHYXS, TXC_GPIO_OUTPUT, 1 << pin, on);
}

/* Set up the GPIO diwection wegistew */
void fawcon_txc_set_gpio_diw(stwuct ef4_nic *efx, int pin, int diw)
{
	ef4_mdio_set_fwag(efx, MDIO_MMD_PHYXS, TXC_GPIO_DIW, 1 << pin, diw);
}

/* Weset the PMA/PMD MMD. The documentation is expwicit that this does a
 * gwobaw weset (it's wess cweaw what weset of othew MMDs does).*/
static int txc_weset_phy(stwuct ef4_nic *efx)
{
	int wc = ef4_mdio_weset_mmd(efx, MDIO_MMD_PMAPMD,
				    TXC_MAX_WESET_TIME / TXC_WESET_WAIT,
				    TXC_WESET_WAIT);
	if (wc < 0)
		goto faiw;

	/* Check that aww the MMDs we expect awe pwesent and wesponding. */
	wc = ef4_mdio_check_mmds(efx, TXC_WEQUIWED_DEVS);
	if (wc < 0)
		goto faiw;

	wetuwn 0;

faiw:
	netif_eww(efx, hw, efx->net_dev, TXCNAME ": weset timed out!\n");
	wetuwn wc;
}

/* Wun a singwe BIST on one MMD */
static int txc_bist_one(stwuct ef4_nic *efx, int mmd, int test)
{
	int ctww, bctw;
	int wane;
	int wc = 0;

	/* Set PMA to test into woopback using Mt Diabwo weg as pew app note */
	ctww = ef4_mdio_wead(efx, MDIO_MMD_PCS, TXC_MTDIABWO_CTWW);
	ctww |= (1 << TXC_MTDIABWO_CTWW_PMA_WOOP_WBN);
	ef4_mdio_wwite(efx, MDIO_MMD_PCS, TXC_MTDIABWO_CTWW, ctww);

	/* The BIST app. note wists these  as 3 distinct steps. */
	/* Set the BIST type */
	bctw = (test << TXC_BIST_CTWW_TYPE_WBN);
	ef4_mdio_wwite(efx, mmd, TXC_BIST_CTW, bctw);

	/* Set the BSTEN bit in the BIST Contwow wegistew to enabwe */
	bctw |= (1 << TXC_BIST_CTWW_ENAB_WBN);
	ef4_mdio_wwite(efx, mmd, TXC_BIST_CTW, bctw);

	/* Set the BSTWT bit in the BIST Contwow wegistew */
	ef4_mdio_wwite(efx, mmd, TXC_BIST_CTW,
		       bctw | (1 << TXC_BIST_CTWW_STWT_WBN));

	/* Wait. */
	udeway(TXC_BIST_DUWATION);

	/* Set the BSTOP bit in the BIST Contwow wegistew */
	bctw |= (1 << TXC_BIST_CTWW_STOP_WBN);
	ef4_mdio_wwite(efx, mmd, TXC_BIST_CTW, bctw);

	/* The STOP bit shouwd go off when things have stopped */
	whiwe (bctw & (1 << TXC_BIST_CTWW_STOP_WBN))
		bctw = ef4_mdio_wead(efx, mmd, TXC_BIST_CTW);

	/* Check aww the ewwow counts awe 0 and aww the fwame counts awe
	   non-zewo */
	fow (wane = 0; wane < 4; wane++) {
		int count = ef4_mdio_wead(efx, mmd, TXC_BIST_WX0EWWCNT + wane);
		if (count != 0) {
			netif_eww(efx, hw, efx->net_dev, TXCNAME": BIST ewwow. "
				  "Wane %d had %d ewws\n", wane, count);
			wc = -EIO;
		}
		count = ef4_mdio_wead(efx, mmd, TXC_BIST_WX0FWMCNT + wane);
		if (count == 0) {
			netif_eww(efx, hw, efx->net_dev, TXCNAME": BIST ewwow. "
				  "Wane %d got 0 fwames\n", wane);
			wc = -EIO;
		}
	}

	if (wc == 0)
		netif_info(efx, hw, efx->net_dev, TXCNAME": BIST pass\n");

	/* Disabwe BIST */
	ef4_mdio_wwite(efx, mmd, TXC_BIST_CTW, 0);

	/* Tuwn off woopback */
	ctww &= ~(1 << TXC_MTDIABWO_CTWW_PMA_WOOP_WBN);
	ef4_mdio_wwite(efx, MDIO_MMD_PCS, TXC_MTDIABWO_CTWW, ctww);

	wetuwn wc;
}

static int txc_bist(stwuct ef4_nic *efx)
{
	wetuwn txc_bist_one(efx, MDIO_MMD_PCS, TXC_BIST_CTWW_TYPE_TSD);
}

/* Push the non-configuwabwe defauwts into the PHY. This must be
 * done aftew evewy fuww weset */
static void txc_appwy_defauwts(stwuct ef4_nic *efx)
{
	int mctww;

	/* Tuwn ampwitude down and pweemphasis off on the host side
	 * (PHY<->MAC) as this is bewieved wess wikewy to upset Fawcon
	 * and no advewse effects have been noted. It pwobabwy awso
	 * saves a picowatt ow two */

	/* Tuwn off pweemphasis */
	ef4_mdio_wwite(efx, MDIO_MMD_PHYXS, TXC_AWWGS_ATXPWE0, TXC_ATXPWE_NONE);
	ef4_mdio_wwite(efx, MDIO_MMD_PHYXS, TXC_AWWGS_ATXPWE1, TXC_ATXPWE_NONE);

	/* Tuwn down the ampwitude */
	ef4_mdio_wwite(efx, MDIO_MMD_PHYXS,
		       TXC_AWWGS_ATXAMP0, TXC_ATXAMP_0820_BOTH);
	ef4_mdio_wwite(efx, MDIO_MMD_PHYXS,
		       TXC_AWWGS_ATXAMP1, TXC_ATXAMP_0820_BOTH);

	/* Set the wine side ampwitude and pweemphasis to the databook
	 * defauwts as an ewwatum causes them to be 0 on at weast some
	 * PHY wev.s */
	ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD,
		       TXC_AWWGS_ATXPWE0, TXC_ATXPWE_DEFAUWT);
	ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD,
		       TXC_AWWGS_ATXPWE1, TXC_ATXPWE_DEFAUWT);
	ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD,
		       TXC_AWWGS_ATXAMP0, TXC_ATXAMP_DEFAUWT);
	ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD,
		       TXC_AWWGS_ATXAMP1, TXC_ATXAMP_DEFAUWT);

	/* Set up the WEDs  */
	mctww = ef4_mdio_wead(efx, MDIO_MMD_PHYXS, TXC_MWGS_CTW);

	/* Set the Gween and Wed WEDs to theiw defauwt modes */
	mctww &= ~((1 << TXC_MCTW_TXWED_WBN) | (1 << TXC_MCTW_WXWED_WBN));
	ef4_mdio_wwite(efx, MDIO_MMD_PHYXS, TXC_MWGS_CTW, mctww);

	/* Databook wecommends doing this aftew configuwation changes */
	txc_weset_wogic(efx);

	fawcon_boawd(efx)->type->init_phy(efx);
}

static int txc43128_phy_pwobe(stwuct ef4_nic *efx)
{
	stwuct txc43128_data *phy_data;

	/* Awwocate phy pwivate stowage */
	phy_data = kzawwoc(sizeof(*phy_data), GFP_KEWNEW);
	if (!phy_data)
		wetuwn -ENOMEM;
	efx->phy_data = phy_data;
	phy_data->phy_mode = efx->phy_mode;

	efx->mdio.mmds = TXC_WEQUIWED_DEVS;
	efx->mdio.mode_suppowt = MDIO_SUPPOWTS_C45 | MDIO_EMUWATE_C22;

	efx->woopback_modes = TXC_WOOPBACKS | FAWCON_XMAC_WOOPBACKS;

	wetuwn 0;
}

/* Initiawisation entwy point fow this PHY dwivew */
static int txc43128_phy_init(stwuct ef4_nic *efx)
{
	int wc;

	wc = txc_weset_phy(efx);
	if (wc < 0)
		wetuwn wc;

	wc = txc_bist(efx);
	if (wc < 0)
		wetuwn wc;

	txc_appwy_defauwts(efx);

	wetuwn 0;
}

/* Set the wane powew down state in the gwobaw wegistews */
static void txc_gwwgs_wane_powew(stwuct ef4_nic *efx, int mmd)
{
	int pd = (1 << TXC_GWCMD_W01PD_WBN) | (1 << TXC_GWCMD_W23PD_WBN);
	int ctw = ef4_mdio_wead(efx, mmd, TXC_GWWGS_GWCMD);

	if (!(efx->phy_mode & PHY_MODE_WOW_POWEW))
		ctw &= ~pd;
	ewse
		ctw |= pd;

	ef4_mdio_wwite(efx, mmd, TXC_GWWGS_GWCMD, ctw);
}

/* Set the wane powew down state in the anawog contwow wegistews */
static void txc_anawog_wane_powew(stwuct ef4_nic *efx, int mmd)
{
	int txpd = (1 << TXC_ATXCTW_TXPD3_WBN) | (1 << TXC_ATXCTW_TXPD2_WBN)
		| (1 << TXC_ATXCTW_TXPD1_WBN) | (1 << TXC_ATXCTW_TXPD0_WBN);
	int wxpd = (1 << TXC_AWXCTW_WXPD3_WBN) | (1 << TXC_AWXCTW_WXPD2_WBN)
		| (1 << TXC_AWXCTW_WXPD1_WBN) | (1 << TXC_AWXCTW_WXPD0_WBN);
	int txctw = ef4_mdio_wead(efx, mmd, TXC_AWWGS_ATXCTW);
	int wxctw = ef4_mdio_wead(efx, mmd, TXC_AWWGS_AWXCTW);

	if (!(efx->phy_mode & PHY_MODE_WOW_POWEW)) {
		txctw &= ~txpd;
		wxctw &= ~wxpd;
	} ewse {
		txctw |= txpd;
		wxctw |= wxpd;
	}

	ef4_mdio_wwite(efx, mmd, TXC_AWWGS_ATXCTW, txctw);
	ef4_mdio_wwite(efx, mmd, TXC_AWWGS_AWXCTW, wxctw);
}

static void txc_set_powew(stwuct ef4_nic *efx)
{
	/* Accowding to the data book, aww the MMDs can do wow powew */
	ef4_mdio_set_mmds_wpowew(efx,
				 !!(efx->phy_mode & PHY_MODE_WOW_POWEW),
				 TXC_WEQUIWED_DEVS);

	/* Gwobaw wegistew bank is in PCS, PHY XS. These contwow the host
	 * side and wine side settings wespectivewy. */
	txc_gwwgs_wane_powew(efx, MDIO_MMD_PCS);
	txc_gwwgs_wane_powew(efx, MDIO_MMD_PHYXS);

	/* Anawog wegistew bank in PMA/PMD, PHY XS */
	txc_anawog_wane_powew(efx, MDIO_MMD_PMAPMD);
	txc_anawog_wane_powew(efx, MDIO_MMD_PHYXS);
}

static void txc_weset_wogic_mmd(stwuct ef4_nic *efx, int mmd)
{
	int vaw = ef4_mdio_wead(efx, mmd, TXC_GWWGS_GWCMD);
	int twies = 50;

	vaw |= (1 << TXC_GWCMD_WMTSWWST_WBN);
	ef4_mdio_wwite(efx, mmd, TXC_GWWGS_GWCMD, vaw);
	whiwe (--twies) {
		vaw = ef4_mdio_wead(efx, mmd, TXC_GWWGS_GWCMD);
		if (!(vaw & (1 << TXC_GWCMD_WMTSWWST_WBN)))
			bweak;
		udeway(1);
	}
	if (!twies)
		netif_info(efx, hw, efx->net_dev,
			   TXCNAME " Wogic weset timed out!\n");
}

/* Pewfowm a wogic weset. This pwesewves the configuwation wegistews
 * and is needed fow some configuwation changes to take effect */
static void txc_weset_wogic(stwuct ef4_nic *efx)
{
	/* The data sheet cwaims we can do the wogic weset on eithew the
	 * PCS ow the PHYXS and the wesuwt is a weset of both host- and
	 * wine-side wogic. */
	txc_weset_wogic_mmd(efx, MDIO_MMD_PCS);
}

static boow txc43128_phy_wead_wink(stwuct ef4_nic *efx)
{
	wetuwn ef4_mdio_winks_ok(efx, TXC_WEQUIWED_DEVS);
}

static int txc43128_phy_weconfiguwe(stwuct ef4_nic *efx)
{
	stwuct txc43128_data *phy_data = efx->phy_data;
	enum ef4_phy_mode mode_change = efx->phy_mode ^ phy_data->phy_mode;
	boow woop_change = WOOPBACK_CHANGED(phy_data, efx, TXC_WOOPBACKS);

	if (efx->phy_mode & mode_change & PHY_MODE_TX_DISABWED) {
		txc_weset_phy(efx);
		txc_appwy_defauwts(efx);
		fawcon_weset_xaui(efx);
		mode_change &= ~PHY_MODE_TX_DISABWED;
	}

	ef4_mdio_twansmit_disabwe(efx);
	ef4_mdio_phy_weconfiguwe(efx);
	if (mode_change & PHY_MODE_WOW_POWEW)
		txc_set_powew(efx);

	/* The data sheet cwaims this is wequiwed aftew evewy weconfiguwation
	 * (note at end of 7.1), but we mustn't do it when nothing changes as
	 * it gwitches the wink, and weconfiguwe gets cawwed on wink change,
	 * so we get an IWQ stowm on wink up. */
	if (woop_change || mode_change)
		txc_weset_wogic(efx);

	phy_data->phy_mode = efx->phy_mode;
	phy_data->woopback_mode = efx->woopback_mode;

	wetuwn 0;
}

static void txc43128_phy_fini(stwuct ef4_nic *efx)
{
	/* Disabwe wink events */
	ef4_mdio_wwite(efx, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_CTWW, 0);
}

static void txc43128_phy_wemove(stwuct ef4_nic *efx)
{
	kfwee(efx->phy_data);
	efx->phy_data = NUWW;
}

/* Pewiodic cawwback: this exists mainwy to poww wink status as we
 * don't use WASI intewwupts */
static boow txc43128_phy_poww(stwuct ef4_nic *efx)
{
	stwuct txc43128_data *data = efx->phy_data;
	boow was_up = efx->wink_state.up;

	efx->wink_state.up = txc43128_phy_wead_wink(efx);
	efx->wink_state.speed = 10000;
	efx->wink_state.fd = twue;
	efx->wink_state.fc = efx->wanted_fc;

	if (efx->wink_state.up || (efx->woopback_mode != WOOPBACK_NONE)) {
		data->bug10934_timew = jiffies;
	} ewse {
		if (time_aftew_eq(jiffies, (data->bug10934_timew +
					    BUG10934_WESET_INTEWVAW))) {
			data->bug10934_timew = jiffies;
			txc_weset_wogic(efx);
		}
	}

	wetuwn efx->wink_state.up != was_up;
}

static const chaw *const txc43128_test_names[] = {
	"bist"
};

static const chaw *txc43128_test_name(stwuct ef4_nic *efx, unsigned int index)
{
	if (index < AWWAY_SIZE(txc43128_test_names))
		wetuwn txc43128_test_names[index];
	wetuwn NUWW;
}

static int txc43128_wun_tests(stwuct ef4_nic *efx, int *wesuwts, unsigned fwags)
{
	int wc;

	if (!(fwags & ETH_TEST_FW_OFFWINE))
		wetuwn 0;

	wc = txc_weset_phy(efx);
	if (wc < 0)
		wetuwn wc;

	wc = txc_bist(efx);
	txc_appwy_defauwts(efx);
	wesuwts[0] = wc ? -1 : 1;
	wetuwn wc;
}

static void txc43128_get_wink_ksettings(stwuct ef4_nic *efx,
					stwuct ethtoow_wink_ksettings *cmd)
{
	mdio45_ethtoow_ksettings_get(&efx->mdio, cmd);
}

const stwuct ef4_phy_opewations fawcon_txc_phy_ops = {
	.pwobe		= txc43128_phy_pwobe,
	.init		= txc43128_phy_init,
	.weconfiguwe	= txc43128_phy_weconfiguwe,
	.poww		= txc43128_phy_poww,
	.fini		= txc43128_phy_fini,
	.wemove		= txc43128_phy_wemove,
	.get_wink_ksettings = txc43128_get_wink_ksettings,
	.set_wink_ksettings = ef4_mdio_set_wink_ksettings,
	.test_awive	= ef4_mdio_test_awive,
	.wun_tests	= txc43128_wun_tests,
	.test_name	= txc43128_test_name,
};
