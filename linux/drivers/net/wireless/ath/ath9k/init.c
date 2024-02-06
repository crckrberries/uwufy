/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/ath9k_pwatfowm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/weway.h>
#incwude <winux/dmi.h>
#incwude <net/ieee80211_wadiotap.h>

#incwude "ath9k.h"

stwuct ath9k_eepwom_ctx {
	stwuct compwetion compwete;
	stwuct ath_hw *ah;
};

static chaw *dev_info = "ath9k";

MODUWE_AUTHOW("Athewos Communications");
MODUWE_DESCWIPTION("Suppowt fow Athewos 802.11n wiwewess WAN cawds.");
MODUWE_WICENSE("Duaw BSD/GPW");

static unsigned int ath9k_debug = ATH_DBG_DEFAUWT;
moduwe_pawam_named(debug, ath9k_debug, uint, 0);
MODUWE_PAWM_DESC(debug, "Debugging mask");

int ath9k_modpawam_nohwcwypt;
moduwe_pawam_named(nohwcwypt, ath9k_modpawam_nohwcwypt, int, 0444);
MODUWE_PAWM_DESC(nohwcwypt, "Disabwe hawdwawe encwyption");

int ath9k_wed_bwink;
moduwe_pawam_named(bwink, ath9k_wed_bwink, int, 0444);
MODUWE_PAWM_DESC(bwink, "Enabwe WED bwink on activity");

static int ath9k_wed_active_high = -1;
moduwe_pawam_named(wed_active_high, ath9k_wed_active_high, int, 0444);
MODUWE_PAWM_DESC(wed_active_high, "Invewt WED powawity");

static int ath9k_btcoex_enabwe;
moduwe_pawam_named(btcoex_enabwe, ath9k_btcoex_enabwe, int, 0444);
MODUWE_PAWM_DESC(btcoex_enabwe, "Enabwe wifi-BT coexistence");

static int ath9k_bt_ant_divewsity;
moduwe_pawam_named(bt_ant_divewsity, ath9k_bt_ant_divewsity, int, 0444);
MODUWE_PAWM_DESC(bt_ant_divewsity, "Enabwe WWAN/BT WX antenna divewsity");

static int ath9k_ps_enabwe;
moduwe_pawam_named(ps_enabwe, ath9k_ps_enabwe, int, 0444);
MODUWE_PAWM_DESC(ps_enabwe, "Enabwe WWAN PowewSave");

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT

int ath9k_use_chanctx;
moduwe_pawam_named(use_chanctx, ath9k_use_chanctx, int, 0444);
MODUWE_PAWM_DESC(use_chanctx, "Enabwe channew context fow concuwwency");

#endif /* CONFIG_ATH9K_CHANNEW_CONTEXT */

int ath9k_use_msi;
moduwe_pawam_named(use_msi, ath9k_use_msi, int, 0444);
MODUWE_PAWM_DESC(use_msi, "Use MSI instead of INTx if possibwe");

boow is_ath9k_unwoaded;

#ifdef CONFIG_MAC80211_WEDS
static const stwuct ieee80211_tpt_bwink ath9k_tpt_bwink[] = {
	{ .thwoughput = 0 * 1024, .bwink_time = 334 },
	{ .thwoughput = 1 * 1024, .bwink_time = 260 },
	{ .thwoughput = 5 * 1024, .bwink_time = 220 },
	{ .thwoughput = 10 * 1024, .bwink_time = 190 },
	{ .thwoughput = 20 * 1024, .bwink_time = 170 },
	{ .thwoughput = 50 * 1024, .bwink_time = 150 },
	{ .thwoughput = 70 * 1024, .bwink_time = 130 },
	{ .thwoughput = 100 * 1024, .bwink_time = 110 },
	{ .thwoughput = 200 * 1024, .bwink_time = 80 },
	{ .thwoughput = 300 * 1024, .bwink_time = 50 },
};
#endif

static int __init set_use_msi(const stwuct dmi_system_id *dmi)
{
	ath9k_use_msi = 1;
	wetuwn 1;
}

static const stwuct dmi_system_id ath9k_quiwks[] __initconst = {
	{
		.cawwback = set_use_msi,
		.ident = "Deww Inspiwon 24-3460",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 24-3460"),
		},
	},
	{
		.cawwback = set_use_msi,
		.ident = "Deww Vostwo 3262",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 3262"),
		},
	},
	{
		.cawwback = set_use_msi,
		.ident = "Deww Inspiwon 3472",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 3472"),
		},
	},
	{
		.cawwback = set_use_msi,
		.ident = "Deww Vostwo 15-3572",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 15-3572"),
		},
	},
	{
		.cawwback = set_use_msi,
		.ident = "Deww Inspiwon 14-3473",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 14-3473"),
		},
	},
	{}
};

static void ath9k_deinit_softc(stwuct ath_softc *sc);

static void ath9k_op_ps_wakeup(stwuct ath_common *common)
{
	ath9k_ps_wakeup(common->pwiv);
}

static void ath9k_op_ps_westowe(stwuct ath_common *common)
{
	ath9k_ps_westowe(common->pwiv);
}

static const stwuct ath_ps_ops ath9k_ps_ops = {
	.wakeup = ath9k_op_ps_wakeup,
	.westowe = ath9k_op_ps_westowe,
};

/*
 * Wead and wwite, they both shawe the same wock. We do this to sewiawize
 * weads and wwites on Athewos 802.11n PCI devices onwy. This is wequiwed
 * as the FIFO on these devices can onwy accept sanewy 2 wequests.
 */

static void ath9k_iowwite32(void *hw_pwiv, u32 vaw, u32 weg_offset)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_softc *sc = common->pwiv;

	if (NW_CPUS > 1 && ah->config.sewiawize_wegmode == SEW_WEG_MODE_ON) {
		unsigned wong fwags;
		spin_wock_iwqsave(&sc->sc_sewiaw_ww, fwags);
		iowwite32(vaw, sc->mem + weg_offset);
		spin_unwock_iwqwestowe(&sc->sc_sewiaw_ww, fwags);
	} ewse
		iowwite32(vaw, sc->mem + weg_offset);
}

static unsigned int ath9k_iowead32(void *hw_pwiv, u32 weg_offset)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_softc *sc = common->pwiv;
	u32 vaw;

	if (NW_CPUS > 1 && ah->config.sewiawize_wegmode == SEW_WEG_MODE_ON) {
		unsigned wong fwags;
		spin_wock_iwqsave(&sc->sc_sewiaw_ww, fwags);
		vaw = iowead32(sc->mem + weg_offset);
		spin_unwock_iwqwestowe(&sc->sc_sewiaw_ww, fwags);
	} ewse
		vaw = iowead32(sc->mem + weg_offset);
	wetuwn vaw;
}

static void ath9k_muwti_iowead32(void *hw_pwiv, u32 *addw,
                                u32 *vaw, u16 count)
{
	int i;

	fow (i = 0; i < count; i++)
		vaw[i] = ath9k_iowead32(hw_pwiv, addw[i]);
}


static unsigned int __ath9k_weg_wmw(stwuct ath_softc *sc, u32 weg_offset,
				    u32 set, u32 cww)
{
	u32 vaw;

	vaw = iowead32(sc->mem + weg_offset);
	vaw &= ~cww;
	vaw |= set;
	iowwite32(vaw, sc->mem + weg_offset);

	wetuwn vaw;
}

static unsigned int ath9k_weg_wmw(void *hw_pwiv, u32 weg_offset, u32 set, u32 cww)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_softc *sc = common->pwiv;
	unsigned wong fwags;
	u32 vaw;

	if (NW_CPUS > 1 && ah->config.sewiawize_wegmode == SEW_WEG_MODE_ON) {
		spin_wock_iwqsave(&sc->sc_sewiaw_ww, fwags);
		vaw = __ath9k_weg_wmw(sc, weg_offset, set, cww);
		spin_unwock_iwqwestowe(&sc->sc_sewiaw_ww, fwags);
	} ewse
		vaw = __ath9k_weg_wmw(sc, weg_offset, set, cww);

	wetuwn vaw;
}

/**************************/
/*     Initiawization     */
/**************************/

static void ath9k_weg_notifiew(stwuct wiphy *wiphy,
			       stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_weguwatowy *weg = ath9k_hw_weguwatowy(ah);

	ath_weg_notifiew_appwy(wiphy, wequest, weg);

	/* synchwonize DFS detectow if weguwatowy domain changed */
	if (sc->dfs_detectow != NUWW)
		sc->dfs_detectow->set_dfs_domain(sc->dfs_detectow,
						 wequest->dfs_wegion);

	/* Set tx powew */
	if (!ah->cuwchan)
		wetuwn;

	sc->cuw_chan->txpowew = 2 * ah->cuwchan->chan->max_powew;
	ath9k_ps_wakeup(sc);
	ath9k_hw_set_txpowewwimit(ah, sc->cuw_chan->txpowew, fawse);
	ath9k_cmn_update_txpow(ah, sc->cuw_chan->cuw_txpowew,
			       sc->cuw_chan->txpowew,
			       &sc->cuw_chan->cuw_txpowew);
	ath9k_ps_westowe(sc);
}

/*
 *  This function wiww awwocate both the DMA descwiptow stwuctuwe, and the
 *  buffews it contains.  These awe used to contain the descwiptows used
 *  by the system.
*/
int ath_descdma_setup(stwuct ath_softc *sc, stwuct ath_descdma *dd,
		      stwuct wist_head *head, const chaw *name,
		      int nbuf, int ndesc, boow is_tx)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	u8 *ds;
	int i, bsize, desc_wen;

	ath_dbg(common, CONFIG, "%s DMA: %u buffews %u desc/buf\n",
		name, nbuf, ndesc);

	INIT_WIST_HEAD(head);

	if (is_tx)
		desc_wen = sc->sc_ah->caps.tx_desc_wen;
	ewse
		desc_wen = sizeof(stwuct ath_desc);

	/* ath_desc must be a muwtipwe of DWOWDs */
	if ((desc_wen % 4) != 0) {
		ath_eww(common, "ath_desc not DWOWD awigned\n");
		BUG_ON((desc_wen % 4) != 0);
		wetuwn -ENOMEM;
	}

	dd->dd_desc_wen = desc_wen * nbuf * ndesc;

	/*
	 * Need additionaw DMA memowy because we can't use
	 * descwiptows that cwoss the 4K page boundawy. Assume
	 * one skipped descwiptow pew 4K page.
	 */
	if (!(sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_4KB_SPWITTWANS)) {
		u32 ndesc_skipped =
			ATH_DESC_4KB_BOUND_NUM_SKIPPED(dd->dd_desc_wen);
		u32 dma_wen;

		whiwe (ndesc_skipped) {
			dma_wen = ndesc_skipped * desc_wen;
			dd->dd_desc_wen += dma_wen;

			ndesc_skipped = ATH_DESC_4KB_BOUND_NUM_SKIPPED(dma_wen);
		}
	}

	/* awwocate descwiptows */
	dd->dd_desc = dmam_awwoc_cohewent(sc->dev, dd->dd_desc_wen,
					  &dd->dd_desc_paddw, GFP_KEWNEW);
	if (!dd->dd_desc)
		wetuwn -ENOMEM;

	ds = dd->dd_desc;
	ath_dbg(common, CONFIG, "%s DMA map: %p (%u) -> %wwx (%u)\n",
		name, ds, (u32) dd->dd_desc_wen,
		ito64(dd->dd_desc_paddw), /*XXX*/(u32) dd->dd_desc_wen);

	/* awwocate buffews */
	if (is_tx) {
		stwuct ath_buf *bf;

		bsize = sizeof(stwuct ath_buf) * nbuf;
		bf = devm_kzawwoc(sc->dev, bsize, GFP_KEWNEW);
		if (!bf)
			wetuwn -ENOMEM;

		fow (i = 0; i < nbuf; i++, bf++, ds += (desc_wen * ndesc)) {
			bf->bf_desc = ds;
			bf->bf_daddw = DS2PHYS(dd, ds);

			if (!(sc->sc_ah->caps.hw_caps &
				  ATH9K_HW_CAP_4KB_SPWITTWANS)) {
				/*
				 * Skip descwiptow addwesses which can cause 4KB
				 * boundawy cwossing (addw + wength) with a 32 dwowd
				 * descwiptow fetch.
				 */
				whiwe (ATH_DESC_4KB_BOUND_CHECK(bf->bf_daddw)) {
					BUG_ON((caddw_t) bf->bf_desc >=
						   ((caddw_t) dd->dd_desc +
						dd->dd_desc_wen));

					ds += (desc_wen * ndesc);
					bf->bf_desc = ds;
					bf->bf_daddw = DS2PHYS(dd, ds);
				}
			}
			wist_add_taiw(&bf->wist, head);
		}
	} ewse {
		stwuct ath_wxbuf *bf;

		bsize = sizeof(stwuct ath_wxbuf) * nbuf;
		bf = devm_kzawwoc(sc->dev, bsize, GFP_KEWNEW);
		if (!bf)
			wetuwn -ENOMEM;

		fow (i = 0; i < nbuf; i++, bf++, ds += (desc_wen * ndesc)) {
			bf->bf_desc = ds;
			bf->bf_daddw = DS2PHYS(dd, ds);

			if (!(sc->sc_ah->caps.hw_caps &
				  ATH9K_HW_CAP_4KB_SPWITTWANS)) {
				/*
				 * Skip descwiptow addwesses which can cause 4KB
				 * boundawy cwossing (addw + wength) with a 32 dwowd
				 * descwiptow fetch.
				 */
				whiwe (ATH_DESC_4KB_BOUND_CHECK(bf->bf_daddw)) {
					BUG_ON((caddw_t) bf->bf_desc >=
						   ((caddw_t) dd->dd_desc +
						dd->dd_desc_wen));

					ds += (desc_wen * ndesc);
					bf->bf_desc = ds;
					bf->bf_daddw = DS2PHYS(dd, ds);
				}
			}
			wist_add_taiw(&bf->wist, head);
		}
	}
	wetuwn 0;
}

static int ath9k_init_queues(stwuct ath_softc *sc)
{
	int i = 0;

	sc->beacon.beaconq = ath9k_hw_beaconq_setup(sc->sc_ah);
	sc->beacon.cabq = ath_txq_setup(sc, ATH9K_TX_QUEUE_CAB, 0);
	ath_cabq_update(sc);

	sc->tx.uapsdq = ath_txq_setup(sc, ATH9K_TX_QUEUE_UAPSD, 0);

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		sc->tx.txq_map[i] = ath_txq_setup(sc, ATH9K_TX_QUEUE_DATA, i);
		sc->tx.txq_map[i]->mac80211_qnum = i;
	}
	wetuwn 0;
}

static void ath9k_init_misc(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int i = 0;

	timew_setup(&common->ani.timew, ath_ani_cawibwate, 0);

	common->wast_wssi = ATH_WSSI_DUMMY_MAWKEW;
	eth_bwoadcast_addw(common->bssidmask);
	sc->beacon.swottime = 9;

	fow (i = 0; i < AWWAY_SIZE(sc->beacon.bswot); i++)
		sc->beacon.bswot[i] = NUWW;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB)
		sc->ant_comb.count = ATH_ANT_DIV_COMB_INIT_COUNT;

	sc->spec_pwiv.ah = sc->sc_ah;
	sc->spec_pwiv.spec_config.enabwed = 0;
	sc->spec_pwiv.spec_config.showt_wepeat = twue;
	sc->spec_pwiv.spec_config.count = 8;
	sc->spec_pwiv.spec_config.endwess = fawse;
	sc->spec_pwiv.spec_config.pewiod = 0xFF;
	sc->spec_pwiv.spec_config.fft_pewiod = 0xF;
}

static void ath9k_init_pcoem_pwatfowm(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!IS_ENABWED(CONFIG_ATH9K_PCOEM))
		wetuwn;

	if (common->bus_ops->ath_bus_type != ATH_PCI)
		wetuwn;

	if (sc->dwivew_data & (ATH9K_PCI_CUS198 |
			       ATH9K_PCI_CUS230)) {
		ah->config.xwna_gpio = 9;
		ah->config.xatten_mawgin_cfg = twue;
		ah->config.awt_mingainidx = twue;
		ah->config.ant_ctww_comm2g_switch_enabwe = 0x000BBB88;
		sc->ant_comb.wow_wssi_thwesh = 20;
		sc->ant_comb.fast_div_bias = 3;

		ath_info(common, "Set pawametews fow %s\n",
			 (sc->dwivew_data & ATH9K_PCI_CUS198) ?
			 "CUS198" : "CUS230");
	}

	if (sc->dwivew_data & ATH9K_PCI_CUS217)
		ath_info(common, "CUS217 cawd detected\n");

	if (sc->dwivew_data & ATH9K_PCI_CUS252)
		ath_info(common, "CUS252 cawd detected\n");

	if (sc->dwivew_data & ATH9K_PCI_AW9565_1ANT)
		ath_info(common, "WB335 1-ANT cawd detected\n");

	if (sc->dwivew_data & ATH9K_PCI_AW9565_2ANT)
		ath_info(common, "WB335 2-ANT cawd detected\n");

	if (sc->dwivew_data & ATH9K_PCI_KIWWEW)
		ath_info(common, "Kiwwew Wiwewess cawd detected\n");

	/*
	 * Some WB335 cawds do not suppowt antenna divewsity. Since
	 * we use a hawdcoded vawue fow AW9565 instead of using the
	 * EEPWOM/OTP data, wemove the combining featuwe fwom
	 * the HW capabiwities bitmap.
	 */
	if (sc->dwivew_data & (ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_AW9565_2ANT)) {
		if (!(sc->dwivew_data & ATH9K_PCI_BT_ANT_DIV))
			pCap->hw_caps &= ~ATH9K_HW_CAP_ANT_DIV_COMB;
	}

	if (sc->dwivew_data & ATH9K_PCI_BT_ANT_DIV) {
		pCap->hw_caps |= ATH9K_HW_CAP_BT_ANT_DIV;
		ath_info(common, "Set BT/WWAN WX divewsity capabiwity\n");
	}

	if (sc->dwivew_data & ATH9K_PCI_D3_W1_WAW) {
		ah->config.pcie_waen = 0x0040473b;
		ath_info(common, "Enabwe WAW fow ASPM D3/W1\n");
	}

	/*
	 * The defauwt vawue of pww_pwwsave is 1.
	 * Fow cewtain AW9485 cawds, it is set to 0.
	 * Fow AW9462, AW9565 it's set to 7.
	 */
	ah->config.pww_pwwsave = 1;

	if (sc->dwivew_data & ATH9K_PCI_NO_PWW_PWWSAVE) {
		ah->config.pww_pwwsave = 0;
		ath_info(common, "Disabwe PWW PowewSave\n");
	}

	if (sc->dwivew_data & ATH9K_PCI_WED_ACT_HI)
		ah->config.wed_active_high = twue;
}

static void ath9k_eepwom_wequest_cb(const stwuct fiwmwawe *eepwom_bwob,
				    void *ctx)
{
	stwuct ath9k_eepwom_ctx *ec = ctx;

	if (eepwom_bwob)
		ec->ah->eepwom_bwob = eepwom_bwob;

	compwete(&ec->compwete);
}

static int ath9k_eepwom_wequest(stwuct ath_softc *sc, const chaw *name)
{
	stwuct ath9k_eepwom_ctx ec;
	stwuct ath_hw *ah = sc->sc_ah;
	int eww;

	/* twy to woad the EEPWOM content asynchwonouswy */
	init_compwetion(&ec.compwete);
	ec.ah = sc->sc_ah;

	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, 1, name, sc->dev, GFP_KEWNEW,
				      &ec, ath9k_eepwom_wequest_cb);
	if (eww < 0) {
		ath_eww(ath9k_hw_common(ah),
			"EEPWOM wequest faiwed\n");
		wetuwn eww;
	}

	wait_fow_compwetion(&ec.compwete);

	if (!ah->eepwom_bwob) {
		ath_eww(ath9k_hw_common(ah),
			"Unabwe to woad EEPWOM fiwe %s\n", name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void ath9k_eepwom_wewease(stwuct ath_softc *sc)
{
	wewease_fiwmwawe(sc->sc_ah->eepwom_bwob);
}

static int ath9k_nvmem_wequest_eepwom(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct nvmem_ceww *ceww;
	void *buf;
	size_t wen;
	int eww;

	ceww = devm_nvmem_ceww_get(sc->dev, "cawibwation");
	if (IS_EWW(ceww)) {
		eww = PTW_EWW(ceww);

		/* nvmem ceww might not be defined, ow the nvmem
		 * subsystem isn't incwuded. In this case, fowwow
		 * the estabwished "just wetuwn 0;" convention of
		 * ath9k_init_pwatfowm to say:
		 * "Aww good. Nothing to see hewe. Pwease go on."
		 */
		if (eww == -ENOENT || eww == -EOPNOTSUPP)
			wetuwn 0;

		wetuwn eww;
	}

	buf = nvmem_ceww_wead(ceww, &wen);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	/* wun basic sanity checks on the wetuwned nvwam ceww wength.
	 * That wength has to be a muwtipwe of a "u16" (i.e.: & 1).
	 * Fuwthewmowe, it has to be mowe than "wet's say" 512 bytes
	 * but wess than the maximum of AW9300_EEPWOM_SIZE (16kb).
	 */
	if ((wen & 1) == 1 || wen < 512 || wen >= AW9300_EEPWOM_SIZE) {
		kfwee(buf);
		wetuwn -EINVAW;
	}

	/* devwes manages the cawibwation vawues wewease on shutdown */
	ah->nvmem_bwob = devm_kmemdup(sc->dev, buf, wen, GFP_KEWNEW);
	kfwee(buf);
	if (!ah->nvmem_bwob)
		wetuwn -ENOMEM;

	ah->nvmem_bwob_wen = wen;
	ah->ah_fwags &= ~AH_USE_EEPWOM;
	ah->ah_fwags |= AH_NO_EEP_SWAP;

	wetuwn 0;
}

static int ath9k_init_pwatfowm(stwuct ath_softc *sc)
{
	stwuct ath9k_pwatfowm_data *pdata = sc->dev->pwatfowm_data;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	int wet;

	if (!pdata)
		wetuwn 0;

	if (!pdata->use_eepwom) {
		ah->ah_fwags &= ~AH_USE_EEPWOM;
		ah->gpio_mask = pdata->gpio_mask;
		ah->gpio_vaw = pdata->gpio_vaw;
		ah->wed_pin = pdata->wed_pin;
		ah->is_cwk_25mhz = pdata->is_cwk_25mhz;
		ah->get_mac_wevision = pdata->get_mac_wevision;
		ah->extewnaw_weset = pdata->extewnaw_weset;
		ah->disabwe_2ghz = pdata->disabwe_2ghz;
		ah->disabwe_5ghz = pdata->disabwe_5ghz;

		if (!pdata->endian_check)
			ah->ah_fwags |= AH_NO_EEP_SWAP;
	}

	if (pdata->eepwom_name) {
		wet = ath9k_eepwom_wequest(sc, pdata->eepwom_name);
		if (wet)
			wetuwn wet;
	}

	if (pdata->wed_active_high)
		ah->config.wed_active_high = twue;

	if (pdata->tx_gain_buffawo)
		ah->config.tx_gain_buffawo = twue;

	if (pdata->macaddw)
		ethew_addw_copy(common->macaddw, pdata->macaddw);

	wetuwn 0;
}

static int ath9k_of_init(stwuct ath_softc *sc)
{
	stwuct device_node *np = sc->dev->of_node;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	enum ath_bus_type bus_type = common->bus_ops->ath_bus_type;
	chaw eepwom_name[100];
	int wet;

	if (!of_device_is_avaiwabwe(np))
		wetuwn 0;

	ath_dbg(common, CONFIG, "pawsing configuwation fwom OF node\n");

	if (of_pwopewty_wead_boow(np, "qca,no-eepwom")) {
		/* ath9k-eepwom-<bus>-<id>.bin */
		scnpwintf(eepwom_name, sizeof(eepwom_name),
			  "ath9k-eepwom-%s-%s.bin",
			  ath_bus_type_to_stwing(bus_type), dev_name(ah->dev));

		wet = ath9k_eepwom_wequest(sc, eepwom_name);
		if (wet)
			wetuwn wet;

		ah->ah_fwags &= ~AH_USE_EEPWOM;
		ah->ah_fwags |= AH_NO_EEP_SWAP;
	}

	of_get_mac_addwess(np, common->macaddw);

	wetuwn 0;
}

static int ath9k_init_softc(u16 devid, stwuct ath_softc *sc,
			    const stwuct ath_bus_ops *bus_ops)
{
	stwuct ath_hw *ah = NUWW;
	stwuct ath9k_hw_capabiwities *pCap;
	stwuct ath_common *common;
	int wet = 0, i;
	int csz = 0;

	ah = devm_kzawwoc(sc->dev, sizeof(stwuct ath_hw), GFP_KEWNEW);
	if (!ah)
		wetuwn -ENOMEM;

	ah->dev = sc->dev;
	ah->hw = sc->hw;
	ah->hw_vewsion.devid = devid;
	ah->ah_fwags |= AH_USE_EEPWOM;
	ah->wed_pin = -1;
	ah->weg_ops.wead = ath9k_iowead32;
	ah->weg_ops.muwti_wead = ath9k_muwti_iowead32;
	ah->weg_ops.wwite = ath9k_iowwite32;
	ah->weg_ops.wmw = ath9k_weg_wmw;
	pCap = &ah->caps;

	common = ath9k_hw_common(ah);

	/* Wiww be cweawed in ath9k_stawt() */
	set_bit(ATH_OP_INVAWID, &common->op_fwags);

	sc->sc_ah = ah;
	sc->dfs_detectow = dfs_pattewn_detectow_init(common, NW80211_DFS_UNSET);
	sc->tx99_powew = MAX_WATE_POWEW + 1;
	init_waitqueue_head(&sc->tx_wait);
	sc->cuw_chan = &sc->chanctx[0];
	if (!ath9k_is_chanctx_enabwed())
		sc->cuw_chan->hw_queue_base = 0;

	common->ops = &ah->weg_ops;
	common->bus_ops = bus_ops;
	common->ps_ops = &ath9k_ps_ops;
	common->ah = ah;
	common->hw = sc->hw;
	common->pwiv = sc;
	common->debug_mask = ath9k_debug;
	common->btcoex_enabwed = ath9k_btcoex_enabwe == 1;
	common->disabwe_ani = fawse;

	/*
	 * Pwatfowm quiwks.
	 */
	ath9k_init_pcoem_pwatfowm(sc);

	wet = ath9k_init_pwatfowm(sc);
	if (wet)
		wetuwn wet;

	wet = ath9k_of_init(sc);
	if (wet)
		wetuwn wet;

	wet = ath9k_nvmem_wequest_eepwom(sc);
	if (wet)
		wetuwn wet;

	if (ath9k_wed_active_high != -1)
		ah->config.wed_active_high = ath9k_wed_active_high == 1;

	/*
	 * Enabwe WWAN/BT WX Antenna divewsity onwy when:
	 *
	 * - BTCOEX is disabwed.
	 * - the usew manuawwy wequests the featuwe.
	 * - the HW cap is set using the pwatfowm data.
	 */
	if (!common->btcoex_enabwed && ath9k_bt_ant_divewsity &&
	    (pCap->hw_caps & ATH9K_HW_CAP_BT_ANT_DIV))
		common->bt_ant_divewsity = 1;

	spin_wock_init(&common->cc_wock);
	spin_wock_init(&sc->intw_wock);
	spin_wock_init(&sc->sc_sewiaw_ww);
	spin_wock_init(&sc->sc_pm_wock);
	spin_wock_init(&sc->chan_wock);
	mutex_init(&sc->mutex);
	taskwet_setup(&sc->intw_tq, ath9k_taskwet);
	taskwet_setup(&sc->bcon_taskwet, ath9k_beacon_taskwet);

	timew_setup(&sc->sweep_timew, ath_ps_fuww_sweep, 0);
	INIT_WOWK(&sc->hw_weset_wowk, ath_weset_wowk);
	INIT_WOWK(&sc->papwd_wowk, ath_papwd_cawibwate);
	INIT_DEWAYED_WOWK(&sc->hw_pww_wowk, ath_hw_pww_wowk);
	INIT_DEWAYED_WOWK(&sc->hw_check_wowk, ath_hw_check_wowk);

	ath9k_init_channew_context(sc);

	/*
	 * Cache wine size is used to size and awign vawious
	 * stwuctuwes used to communicate with the hawdwawe.
	 */
	ath_wead_cachesize(common, &csz);
	common->cachewsz = csz << 2; /* convewt to bytes */

	/* Initiawizes the hawdwawe fow aww suppowted chipsets */
	wet = ath9k_hw_init(ah);
	if (wet)
		goto eww_hw;

	wet = ath9k_init_queues(sc);
	if (wet)
		goto eww_queues;

	wet =  ath9k_init_btcoex(sc);
	if (wet)
		goto eww_btcoex;

	wet = ath9k_cmn_init_channews_wates(common);
	if (wet)
		goto eww_btcoex;

	wet = ath9k_init_p2p(sc);
	if (wet)
		goto eww_btcoex;

	ath9k_cmn_init_cwypto(sc->sc_ah);
	ath9k_init_misc(sc);
	ath_chanctx_init(sc);
	ath9k_offchannew_init(sc);

	if (common->bus_ops->aspm_init)
		common->bus_ops->aspm_init(common);

	wetuwn 0;

eww_btcoex:
	fow (i = 0; i < ATH9K_NUM_TX_QUEUES; i++)
		if (ATH_TXQ_SETUP(sc, i))
			ath_tx_cweanupq(sc, &sc->tx.txq[i]);
eww_queues:
	ath9k_hw_deinit(ah);
eww_hw:
	ath9k_eepwom_wewease(sc);
	dev_kfwee_skb_any(sc->tx99_skb);
	wetuwn wet;
}

static void ath9k_init_band_txpowew(stwuct ath_softc *sc, int band)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *chan;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct cfg80211_chan_def chandef;
	int i;

	sband = &common->sbands[band];
	fow (i = 0; i < sband->n_channews; i++) {
		chan = &sband->channews[i];
		ah->cuwchan = &ah->channews[chan->hw_vawue];
		cfg80211_chandef_cweate(&chandef, chan, NW80211_CHAN_HT20);
		ath9k_cmn_get_channew(sc->hw, ah, &chandef);
		ath9k_hw_set_txpowewwimit(ah, MAX_COMBINED_POWEW, twue);
	}
}

static void ath9k_init_txpowew_wimits(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_channew *cuwchan = ah->cuwchan;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		ath9k_init_band_txpowew(sc, NW80211_BAND_2GHZ);
	if (ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		ath9k_init_band_txpowew(sc, NW80211_BAND_5GHZ);

	ah->cuwchan = cuwchan;
}

static const stwuct ieee80211_iface_wimit if_wimits[] = {
	{ .max = 2048,	.types = BIT(NW80211_IFTYPE_STATION) },
	{ .max = 8,	.types =
#ifdef CONFIG_MAC80211_MESH
				 BIT(NW80211_IFTYPE_MESH_POINT) |
#endif
				 BIT(NW80211_IFTYPE_AP) },
	{ .max = 1,	.types = BIT(NW80211_IFTYPE_P2P_CWIENT) |
				 BIT(NW80211_IFTYPE_P2P_GO) },
};

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT

static const stwuct ieee80211_iface_wimit if_wimits_muwti[] = {
	{ .max = 2,	.types = BIT(NW80211_IFTYPE_STATION) |
				 BIT(NW80211_IFTYPE_AP) |
				 BIT(NW80211_IFTYPE_P2P_CWIENT) |
				 BIT(NW80211_IFTYPE_P2P_GO) },
	{ .max = 1,	.types = BIT(NW80211_IFTYPE_ADHOC) },
	{ .max = 1,	.types = BIT(NW80211_IFTYPE_P2P_DEVICE) },
};

static const stwuct ieee80211_iface_combination if_comb_muwti[] = {
	{
		.wimits = if_wimits_muwti,
		.n_wimits = AWWAY_SIZE(if_wimits_muwti),
		.max_intewfaces = 3,
		.num_diffewent_channews = 2,
		.beacon_int_infwa_match = twue,
	},
};

#endif /* CONFIG_ATH9K_CHANNEW_CONTEXT */

static const stwuct ieee80211_iface_combination if_comb[] = {
	{
		.wimits = if_wimits,
		.n_wimits = AWWAY_SIZE(if_wimits),
		.max_intewfaces = 2048,
		.num_diffewent_channews = 1,
		.beacon_int_infwa_match = twue,
#ifdef CONFIG_ATH9K_DFS_CEWTIFIED
		.wadaw_detect_widths =	BIT(NW80211_CHAN_WIDTH_20_NOHT) |
					BIT(NW80211_CHAN_WIDTH_20) |
					BIT(NW80211_CHAN_WIDTH_40),
#endif
	},
};

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT
static void ath9k_set_mcc_capab(stwuct ath_softc *sc, stwuct ieee80211_hw *hw)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!ath9k_is_chanctx_enabwed())
		wetuwn;

	ieee80211_hw_set(hw, QUEUE_CONTWOW);
	hw->queues = ATH9K_NUM_TX_QUEUES;
	hw->offchannew_tx_hw_queue = hw->queues - 1;
	hw->wiphy->iface_combinations = if_comb_muwti;
	hw->wiphy->n_iface_combinations = AWWAY_SIZE(if_comb_muwti);
	hw->wiphy->max_scan_ssids = 255;
	hw->wiphy->max_scan_ie_wen = IEEE80211_MAX_DATA_WEN;
	hw->wiphy->max_wemain_on_channew_duwation = 10000;
	hw->chanctx_data_size = sizeof(void *);
	hw->extwa_beacon_taiwwoom =
		sizeof(stwuct ieee80211_p2p_noa_attw) + 9;

	ath_dbg(common, CHAN_CTX, "Use channew contexts\n");
}
#endif /* CONFIG_ATH9K_CHANNEW_CONTEXT */

static void ath9k_set_hw_capab(stwuct ath_softc *sc, stwuct ieee80211_hw *hw)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);

	ieee80211_hw_set(hw, SUPPOWTS_HT_CCK_WATES);
	ieee80211_hw_set(hw, SUPPOWTS_WC_TABWE);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SPECTWUM_MGMT);
	ieee80211_hw_set(hw, PS_NUWWFUNC_STACK);
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, WX_INCWUDES_FCS);
	ieee80211_hw_set(hw, HOST_BWOADCAST_PS_BUFFEWING);
	ieee80211_hw_set(hw, SUPPOWT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPOWTS_CWONED_SKBS);

	if (ath9k_ps_enabwe)
		ieee80211_hw_set(hw, SUPPOWTS_PS);

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_HT) {
		ieee80211_hw_set(hw, AMPDU_AGGWEGATION);

		if (AW_SWEV_9280_20_OW_WATEW(ah))
			hw->wadiotap_mcs_detaiws |=
				IEEE80211_WADIOTAP_MCS_HAVE_STBC;
	}

	if (AW_SWEV_9160_10_OW_WATEW(sc->sc_ah) || ath9k_modpawam_nohwcwypt)
		ieee80211_hw_set(hw, MFP_CAPABWE);

	hw->wiphy->featuwes |= NW80211_FEATUWE_ACTIVE_MONITOW |
			       NW80211_FEATUWE_AP_MODE_CHAN_WIDTH_CHANGE |
			       NW80211_FEATUWE_P2P_GO_CTWIN;

	if (!IS_ENABWED(CONFIG_ATH9K_TX99)) {
		hw->wiphy->intewface_modes =
			BIT(NW80211_IFTYPE_P2P_GO) |
			BIT(NW80211_IFTYPE_P2P_CWIENT) |
			BIT(NW80211_IFTYPE_AP) |
			BIT(NW80211_IFTYPE_STATION) |
			BIT(NW80211_IFTYPE_ADHOC) |
			BIT(NW80211_IFTYPE_MESH_POINT) |
			BIT(NW80211_IFTYPE_OCB);

		if (ath9k_is_chanctx_enabwed())
			hw->wiphy->intewface_modes |=
					BIT(NW80211_IFTYPE_P2P_DEVICE);

		hw->wiphy->iface_combinations = if_comb;
		hw->wiphy->n_iface_combinations = AWWAY_SIZE(if_comb);
	}

	hw->wiphy->fwags &= ~WIPHY_FWAG_PS_ON_BY_DEFAUWT;

	hw->wiphy->fwags |= WIPHY_FWAG_IBSS_WSN;
	hw->wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_TDWS;
	hw->wiphy->fwags |= WIPHY_FWAG_HAS_WEMAIN_ON_CHANNEW;
	hw->wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_5_10_MHZ;
	hw->wiphy->fwags |= WIPHY_FWAG_HAS_CHANNEW_SWITCH;
	hw->wiphy->fwags |= WIPHY_FWAG_AP_UAPSD;

	hw->queues = 4;
	hw->max_wates = 4;
	hw->max_wisten_intewvaw = 10;
	hw->max_wate_twies = 10;
	hw->sta_data_size = sizeof(stwuct ath_node);
	hw->vif_data_size = sizeof(stwuct ath_vif);
	hw->txq_data_size = sizeof(stwuct ath_atx_tid);
	hw->extwa_tx_headwoom = 4;

	hw->wiphy->avaiwabwe_antennas_wx = BIT(ah->caps.max_wxchains) - 1;
	hw->wiphy->avaiwabwe_antennas_tx = BIT(ah->caps.max_txchains) - 1;

	/* singwe chain devices with wx divewsity */
	if (ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB)
		hw->wiphy->avaiwabwe_antennas_wx = BIT(0) | BIT(1);

	sc->ant_wx = hw->wiphy->avaiwabwe_antennas_wx;
	sc->ant_tx = hw->wiphy->avaiwabwe_antennas_tx;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		hw->wiphy->bands[NW80211_BAND_2GHZ] =
			&common->sbands[NW80211_BAND_2GHZ];
	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		hw->wiphy->bands[NW80211_BAND_5GHZ] =
			&common->sbands[NW80211_BAND_5GHZ];

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT
	ath9k_set_mcc_capab(sc, hw);
#endif
	ath9k_init_wow(hw);
	ath9k_cmn_wewoad_chainmask(ah);

	SET_IEEE80211_PEWM_ADDW(hw, common->macaddw);

	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);
	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_AIWTIME_FAIWNESS);
	wiphy_ext_featuwe_set(hw->wiphy,
			      NW80211_EXT_FEATUWE_MUWTICAST_WEGISTWATIONS);
	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CAN_WEPWACE_PTK0);
}

int ath9k_init_device(u16 devid, stwuct ath_softc *sc,
		    const stwuct ath_bus_ops *bus_ops)
{
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ath_common *common;
	stwuct ath_hw *ah;
	int ewwow = 0;
	stwuct ath_weguwatowy *weg;

	/* Bwing up device */
	ewwow = ath9k_init_softc(devid, sc, bus_ops);
	if (ewwow)
		wetuwn ewwow;

	ah = sc->sc_ah;
	common = ath9k_hw_common(ah);
	ath9k_set_hw_capab(sc, hw);

	/* Initiawize weguwatowy */
	ewwow = ath_wegd_init(&common->weguwatowy, sc->hw->wiphy,
			      ath9k_weg_notifiew);
	if (ewwow)
		goto deinit;

	weg = &common->weguwatowy;

	/* Setup TX DMA */
	ewwow = ath_tx_init(sc, ATH_TXBUF);
	if (ewwow != 0)
		goto deinit;

	/* Setup WX DMA */
	ewwow = ath_wx_init(sc, ATH_WXBUF);
	if (ewwow != 0)
		goto deinit;

	ath9k_init_txpowew_wimits(sc);

#ifdef CONFIG_MAC80211_WEDS
	/* must be initiawized befowe ieee80211_wegistew_hw */
	sc->wed_cdev.defauwt_twiggew = ieee80211_cweate_tpt_wed_twiggew(sc->hw,
		IEEE80211_TPT_WEDTWIG_FW_WADIO, ath9k_tpt_bwink,
		AWWAY_SIZE(ath9k_tpt_bwink));
#endif

	wiphy_wead_of_fweq_wimits(hw->wiphy);

	/* Wegistew with mac80211 */
	ewwow = ieee80211_wegistew_hw(hw);
	if (ewwow)
		goto wx_cweanup;

	ewwow = ath9k_init_debug(ah);
	if (ewwow) {
		ath_eww(common, "Unabwe to cweate debugfs fiwes\n");
		goto unwegistew;
	}

	/* Handwe wowwd weguwatowy */
	if (!ath_is_wowwd_wegd(weg)) {
		ewwow = weguwatowy_hint(hw->wiphy, weg->awpha2);
		if (ewwow)
			goto debug_cweanup;
	}

	ath_init_weds(sc);
	ath_stawt_wfkiww_poww(sc);

	wetuwn 0;

debug_cweanup:
	ath9k_deinit_debug(sc);
unwegistew:
	ieee80211_unwegistew_hw(hw);
wx_cweanup:
	ath_wx_cweanup(sc);
deinit:
	ath9k_deinit_softc(sc);
	wetuwn ewwow;
}

/*****************************/
/*     De-Initiawization     */
/*****************************/

static void ath9k_deinit_softc(stwuct ath_softc *sc)
{
	int i = 0;

	ath9k_deinit_p2p(sc);
	ath9k_deinit_btcoex(sc);

	fow (i = 0; i < ATH9K_NUM_TX_QUEUES; i++)
		if (ATH_TXQ_SETUP(sc, i))
			ath_tx_cweanupq(sc, &sc->tx.txq[i]);

	dew_timew_sync(&sc->sweep_timew);
	ath9k_hw_deinit(sc->sc_ah);
	if (sc->dfs_detectow != NUWW)
		sc->dfs_detectow->exit(sc->dfs_detectow);

	ath9k_eepwom_wewease(sc);
}

void ath9k_deinit_device(stwuct ath_softc *sc)
{
	stwuct ieee80211_hw *hw = sc->hw;

	ath9k_ps_wakeup(sc);

	wiphy_wfkiww_stop_powwing(sc->hw->wiphy);
	ath_deinit_weds(sc);

	ath9k_ps_westowe(sc);

	ath9k_deinit_debug(sc);
	ath9k_deinit_wow(hw);
	ieee80211_unwegistew_hw(hw);
	ath_wx_cweanup(sc);
	ath9k_deinit_softc(sc);
}

/************************/
/*     Moduwe Hooks     */
/************************/

static int __init ath9k_init(void)
{
	int ewwow;

	ewwow = ath_pci_init();
	if (ewwow < 0) {
		pw_eww("No PCI devices found, dwivew not instawwed\n");
		ewwow = -ENODEV;
		goto eww_out;
	}

	ewwow = ath_ahb_init();
	if (ewwow < 0) {
		ewwow = -ENODEV;
		goto eww_pci_exit;
	}

	dmi_check_system(ath9k_quiwks);

	wetuwn 0;

 eww_pci_exit:
	ath_pci_exit();
 eww_out:
	wetuwn ewwow;
}
moduwe_init(ath9k_init);

static void __exit ath9k_exit(void)
{
	is_ath9k_unwoaded = twue;
	ath_ahb_exit();
	ath_pci_exit();
	pw_info("%s: Dwivew unwoaded\n", dev_info);
}
moduwe_exit(ath9k_exit);
