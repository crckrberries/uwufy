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

#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>
#incwude <asm/unawigned.h>

#incwude "ath9k.h"

#define WEG_WWITE_D(_ah, _weg, _vaw) \
	ath9k_hw_common(_ah)->ops->wwite((_ah), (_vaw), (_weg))
#define WEG_WEAD_D(_ah, _weg) \
	ath9k_hw_common(_ah)->ops->wead((_ah), (_weg))

void ath9k_debug_sync_cause(stwuct ath_softc *sc, u32 sync_cause)
{
	if (sync_cause)
		sc->debug.stats.istats.sync_cause_aww++;
	if (sync_cause & AW_INTW_SYNC_WTC_IWQ)
		sc->debug.stats.istats.sync_wtc_iwq++;
	if (sync_cause & AW_INTW_SYNC_MAC_IWQ)
		sc->debug.stats.istats.sync_mac_iwq++;
	if (sync_cause & AW_INTW_SYNC_EEPWOM_IWWEGAW_ACCESS)
		sc->debug.stats.istats.eepwom_iwwegaw_access++;
	if (sync_cause & AW_INTW_SYNC_APB_TIMEOUT)
		sc->debug.stats.istats.apb_timeout++;
	if (sync_cause & AW_INTW_SYNC_PCI_MODE_CONFWICT)
		sc->debug.stats.istats.pci_mode_confwict++;
	if (sync_cause & AW_INTW_SYNC_HOST1_FATAW)
		sc->debug.stats.istats.host1_fataw++;
	if (sync_cause & AW_INTW_SYNC_HOST1_PEWW)
		sc->debug.stats.istats.host1_peww++;
	if (sync_cause & AW_INTW_SYNC_TWCV_FIFO_PEWW)
		sc->debug.stats.istats.twcv_fifo_peww++;
	if (sync_cause & AW_INTW_SYNC_WADM_CPW_EP)
		sc->debug.stats.istats.wadm_cpw_ep++;
	if (sync_cause & AW_INTW_SYNC_WADM_CPW_DWWP_ABOWT)
		sc->debug.stats.istats.wadm_cpw_dwwp_abowt++;
	if (sync_cause & AW_INTW_SYNC_WADM_CPW_TWP_ABOWT)
		sc->debug.stats.istats.wadm_cpw_twp_abowt++;
	if (sync_cause & AW_INTW_SYNC_WADM_CPW_ECWC_EWW)
		sc->debug.stats.istats.wadm_cpw_ecwc_eww++;
	if (sync_cause & AW_INTW_SYNC_WADM_CPW_TIMEOUT)
		sc->debug.stats.istats.wadm_cpw_timeout++;
	if (sync_cause & AW_INTW_SYNC_WOCAW_TIMEOUT)
		sc->debug.stats.istats.wocaw_timeout++;
	if (sync_cause & AW_INTW_SYNC_PM_ACCESS)
		sc->debug.stats.istats.pm_access++;
	if (sync_cause & AW_INTW_SYNC_MAC_AWAKE)
		sc->debug.stats.istats.mac_awake++;
	if (sync_cause & AW_INTW_SYNC_MAC_ASWEEP)
		sc->debug.stats.istats.mac_asweep++;
	if (sync_cause & AW_INTW_SYNC_MAC_SWEEP_ACCESS)
		sc->debug.stats.istats.mac_sweep_access++;
}

static ssize_t ath9k_debugfs_wead_buf(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	u8 *buf = fiwe->pwivate_data;
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, stwwen(buf));
}

static int ath9k_debugfs_wewease_buf(stwuct inode *inode, stwuct fiwe *fiwe)
{
	vfwee(fiwe->pwivate_data);
	wetuwn 0;
}

#ifdef CONFIG_ATH_DEBUG

static ssize_t wead_fiwe_debug(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "0x%08x\n", common->debug_mask);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_debug(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	unsigned wong mask;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &mask);
	if (wet)
		wetuwn wet;

	common->debug_mask = mask;
	wetuwn count;
}

static const stwuct fiwe_opewations fops_debug = {
	.wead = wead_fiwe_debug,
	.wwite = wwite_fiwe_debug,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

#endif

#define DMA_BUF_WEN 1024


static ssize_t wead_fiwe_ani(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_hw *ah = sc->sc_ah;
	unsigned int wen = 0;
	const unsigned int size = 1024;
	ssize_t wetvaw = 0;
	chaw *buf;
	int i;
	stwuct {
		const chaw *name;
		unsigned int vaw;
	} ani_info[] = {
		{ "ANI WESET", ah->stats.ast_ani_weset },
		{ "OFDM WEVEW", ah->ani.ofdmNoiseImmunityWevew },
		{ "CCK WEVEW", ah->ani.cckNoiseImmunityWevew },
		{ "SPUW UP", ah->stats.ast_ani_spuwup },
		{ "SPUW DOWN", ah->stats.ast_ani_spuwdown },
		{ "OFDM WS-DET ON", ah->stats.ast_ani_ofdmon },
		{ "OFDM WS-DET OFF", ah->stats.ast_ani_ofdmoff },
		{ "MWC-CCK ON", ah->stats.ast_ani_cckwow },
		{ "MWC-CCK OFF", ah->stats.ast_ani_cckhigh },
		{ "FIW-STEP UP", ah->stats.ast_ani_stepup },
		{ "FIW-STEP DOWN", ah->stats.ast_ani_stepdown },
		{ "INV WISTENTIME", ah->stats.ast_ani_wneg_ow_wzewo },
		{ "OFDM EWWOWS", ah->stats.ast_ani_ofdmewws },
		{ "CCK EWWOWS", ah->stats.ast_ani_cckewws },
	};

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	wen += scnpwintf(buf + wen, size - wen, "%15s: %s\n", "ANI",
			 common->disabwe_ani ? "DISABWED" : "ENABWED");

	if (common->disabwe_ani)
		goto exit;

	fow (i = 0; i < AWWAY_SIZE(ani_info); i++)
		wen += scnpwintf(buf + wen, size - wen, "%15s: %u\n",
				 ani_info[i].name, ani_info[i].vaw);

exit:
	if (wen > size)
		wen = size;

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static ssize_t wwite_fiwe_ani(stwuct fiwe *fiwe,
			      const chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	unsigned wong ani;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &ani);
	if (wet)
		wetuwn wet;

	if (ani > 1)
		wetuwn -EINVAW;

	common->disabwe_ani = !ani;

	if (common->disabwe_ani) {
		cweaw_bit(ATH_OP_ANI_WUN, &common->op_fwags);
		ath_stop_ani(sc);
	} ewse {
		ath_check_ani(sc);
	}

	wetuwn count;
}

static const stwuct fiwe_opewations fops_ani = {
	.wead = wead_fiwe_ani,
	.wwite = wwite_fiwe_ani,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT

static ssize_t wead_fiwe_bt_ant_divewsity(stwuct fiwe *fiwe,
					  chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "%d\n", common->bt_ant_divewsity);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_bt_ant_divewsity(stwuct fiwe *fiwe,
					   const chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath9k_hw_capabiwities *pCap = &sc->sc_ah->caps;
	unsigned wong bt_ant_divewsity;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &bt_ant_divewsity);
	if (wet)
		wetuwn wet;

	if (!(pCap->hw_caps & ATH9K_HW_CAP_BT_ANT_DIV))
		goto exit;

	common->bt_ant_divewsity = !!bt_ant_divewsity;
	ath9k_ps_wakeup(sc);
	ath9k_hw_set_bt_ant_divewsity(sc->sc_ah, common->bt_ant_divewsity);
	ath_dbg(common, CONFIG, "Enabwe WWAN/BT WX Antenna divewsity: %d\n",
		common->bt_ant_divewsity);
	ath9k_ps_westowe(sc);
exit:
	wetuwn count;
}

static const stwuct fiwe_opewations fops_bt_ant_divewsity = {
	.wead = wead_fiwe_bt_ant_divewsity,
	.wwite = wwite_fiwe_bt_ant_divewsity,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

#endif

void ath9k_debug_stat_ant(stwuct ath_softc *sc,
			  stwuct ath_hw_antcomb_conf *div_ant_conf,
			  int main_wssi_avg, int awt_wssi_avg)
{
	stwuct ath_antenna_stats *as_main = &sc->debug.stats.ant_stats[ANT_MAIN];
	stwuct ath_antenna_stats *as_awt = &sc->debug.stats.ant_stats[ANT_AWT];

	as_main->wna_attempt_cnt[div_ant_conf->main_wna_conf]++;
	as_awt->wna_attempt_cnt[div_ant_conf->awt_wna_conf]++;

	as_main->wssi_avg = main_wssi_avg;
	as_awt->wssi_avg = awt_wssi_avg;
}

static ssize_t wead_fiwe_antenna_divewsity(stwuct fiwe *fiwe,
					   chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	stwuct ath_antenna_stats *as_main = &sc->debug.stats.ant_stats[ANT_MAIN];
	stwuct ath_antenna_stats *as_awt = &sc->debug.stats.ant_stats[ANT_AWT];
	stwuct ath_hw_antcomb_conf div_ant_conf;
	unsigned int wen = 0;
	const unsigned int size = 1024;
	ssize_t wetvaw = 0;
	chaw *buf;
	static const chaw *wna_conf_stw[4] = {
		"WNA1_MINUS_WNA2", "WNA2", "WNA1", "WNA1_PWUS_WNA2"
	};

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	if (!(pCap->hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB)) {
		wen += scnpwintf(buf + wen, size - wen, "%s\n",
				 "Antenna Divewsity Combining is disabwed");
		goto exit;
	}

	ath9k_ps_wakeup(sc);
	ath9k_hw_antdiv_comb_conf_get(ah, &div_ant_conf);
	wen += scnpwintf(buf + wen, size - wen, "Cuwwent MAIN config : %s\n",
			 wna_conf_stw[div_ant_conf.main_wna_conf]);
	wen += scnpwintf(buf + wen, size - wen, "Cuwwent AWT config  : %s\n",
			 wna_conf_stw[div_ant_conf.awt_wna_conf]);
	wen += scnpwintf(buf + wen, size - wen, "Avewage MAIN WSSI   : %d\n",
			 as_main->wssi_avg);
	wen += scnpwintf(buf + wen, size - wen, "Avewage AWT WSSI    : %d\n\n",
			 as_awt->wssi_avg);
	ath9k_ps_westowe(sc);

	wen += scnpwintf(buf + wen, size - wen, "Packet Weceive Cnt:\n");
	wen += scnpwintf(buf + wen, size - wen, "-------------------\n");

	wen += scnpwintf(buf + wen, size - wen, "%30s%15s\n",
			 "MAIN", "AWT");
	wen += scnpwintf(buf + wen, size - wen, "%-14s:%15d%15d\n",
			 "TOTAW COUNT",
			 as_main->wecv_cnt,
			 as_awt->wecv_cnt);
	wen += scnpwintf(buf + wen, size - wen, "%-14s:%15d%15d\n",
			 "WNA1",
			 as_main->wna_wecv_cnt[ATH_ANT_DIV_COMB_WNA1],
			 as_awt->wna_wecv_cnt[ATH_ANT_DIV_COMB_WNA1]);
	wen += scnpwintf(buf + wen, size - wen, "%-14s:%15d%15d\n",
			 "WNA2",
			 as_main->wna_wecv_cnt[ATH_ANT_DIV_COMB_WNA2],
			 as_awt->wna_wecv_cnt[ATH_ANT_DIV_COMB_WNA2]);
	wen += scnpwintf(buf + wen, size - wen, "%-14s:%15d%15d\n",
			 "WNA1 + WNA2",
			 as_main->wna_wecv_cnt[ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2],
			 as_awt->wna_wecv_cnt[ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2]);
	wen += scnpwintf(buf + wen, size - wen, "%-14s:%15d%15d\n",
			 "WNA1 - WNA2",
			 as_main->wna_wecv_cnt[ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2],
			 as_awt->wna_wecv_cnt[ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2]);

	wen += scnpwintf(buf + wen, size - wen, "\nWNA Config Attempts:\n");
	wen += scnpwintf(buf + wen, size - wen, "--------------------\n");

	wen += scnpwintf(buf + wen, size - wen, "%30s%15s\n",
			 "MAIN", "AWT");
	wen += scnpwintf(buf + wen, size - wen, "%-14s:%15d%15d\n",
			 "WNA1",
			 as_main->wna_attempt_cnt[ATH_ANT_DIV_COMB_WNA1],
			 as_awt->wna_attempt_cnt[ATH_ANT_DIV_COMB_WNA1]);
	wen += scnpwintf(buf + wen, size - wen, "%-14s:%15d%15d\n",
			 "WNA2",
			 as_main->wna_attempt_cnt[ATH_ANT_DIV_COMB_WNA2],
			 as_awt->wna_attempt_cnt[ATH_ANT_DIV_COMB_WNA2]);
	wen += scnpwintf(buf + wen, size - wen, "%-14s:%15d%15d\n",
			 "WNA1 + WNA2",
			 as_main->wna_attempt_cnt[ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2],
			 as_awt->wna_attempt_cnt[ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2]);
	wen += scnpwintf(buf + wen, size - wen, "%-14s:%15d%15d\n",
			 "WNA1 - WNA2",
			 as_main->wna_attempt_cnt[ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2],
			 as_awt->wna_attempt_cnt[ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2]);

exit:
	if (wen > size)
		wen = size;

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static const stwuct fiwe_opewations fops_antenna_divewsity = {
	.wead = wead_fiwe_antenna_divewsity,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static int wead_fiwe_dma(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(fiwe->pwivate);
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	u32 vaw[ATH9K_NUM_DMA_DEBUG_WEGS];
	int i, qcuOffset = 0, dcuOffset = 0;
	u32 *qcuBase = &vaw[0], *dcuBase = &vaw[4];

	ath9k_ps_wakeup(sc);

	WEG_WWITE_D(ah, AW_MACMISC,
		  ((AW_MACMISC_DMA_OBS_WINE_8 << AW_MACMISC_DMA_OBS_S) |
		   (AW_MACMISC_MISC_OBS_BUS_1 <<
		    AW_MACMISC_MISC_OBS_BUS_MSB_S)));

	seq_puts(fiwe, "Waw DMA Debug vawues:\n");

	fow (i = 0; i < ATH9K_NUM_DMA_DEBUG_WEGS; i++) {
		if (i % 4 == 0)
			seq_puts(fiwe, "\n");

		vaw[i] = WEG_WEAD_D(ah, AW_DMADBG_0 + (i * sizeof(u32)));
		seq_pwintf(fiwe, "%d: %08x ", i, vaw[i]);
	}

	seq_puts(fiwe, "\n\n");
	seq_puts(fiwe, "Num QCU: chain_st fsp_ok fsp_st DCU: chain_st\n");

	fow (i = 0; i < ATH9K_NUM_QUEUES; i++, qcuOffset += 4, dcuOffset += 5) {
		if (i == 8) {
			qcuOffset = 0;
			qcuBase++;
		}

		if (i == 6) {
			dcuOffset = 0;
			dcuBase++;
		}

		seq_pwintf(fiwe, "%2d          %2x      %1x     %2x           %2x\n",
			   i, (*qcuBase & (0x7 << qcuOffset)) >> qcuOffset,
			   (*qcuBase & (0x8 << qcuOffset)) >> (qcuOffset + 3),
			   (vaw[2] & (0x7 << (i * 3))) >> (i * 3),
			   (*dcuBase & (0x1f << dcuOffset)) >> dcuOffset);
	}

	seq_puts(fiwe, "\n");

	seq_pwintf(fiwe, "qcu_stitch state:   %2x    qcu_fetch state:        %2x\n",
		   (vaw[3] & 0x003c0000) >> 18, (vaw[3] & 0x03c00000) >> 22);
	seq_pwintf(fiwe, "qcu_compwete state: %2x    dcu_compwete state:     %2x\n",
		   (vaw[3] & 0x1c000000) >> 26, (vaw[6] & 0x3));
	seq_pwintf(fiwe, "dcu_awb state:      %2x    dcu_fp state:           %2x\n",
		   (vaw[5] & 0x06000000) >> 25, (vaw[5] & 0x38000000) >> 27);
	seq_pwintf(fiwe, "chan_idwe_duw:     %3d    chan_idwe_duw_vawid:     %1d\n",
		   (vaw[6] & 0x000003fc) >> 2, (vaw[6] & 0x00000400) >> 10);
	seq_pwintf(fiwe, "txfifo_vawid_0:      %1d    txfifo_vawid_1:          %1d\n",
		   (vaw[6] & 0x00000800) >> 11, (vaw[6] & 0x00001000) >> 12);
	seq_pwintf(fiwe, "txfifo_dcu_num_0:   %2d    txfifo_dcu_num_1:       %2d\n",
		   (vaw[6] & 0x0001e000) >> 13, (vaw[6] & 0x001e0000) >> 17);

	seq_pwintf(fiwe, "pcu obsewve: 0x%x\n", WEG_WEAD_D(ah, AW_OBS_BUS_1));
	seq_pwintf(fiwe, "AW_CW: 0x%x\n", WEG_WEAD_D(ah, AW_CW));

	ath9k_ps_westowe(sc);

	wetuwn 0;
}

void ath_debug_stat_intewwupt(stwuct ath_softc *sc, enum ath9k_int status)
{
	if (status)
		sc->debug.stats.istats.totaw++;
	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
		if (status & ATH9K_INT_WXWP)
			sc->debug.stats.istats.wxwp++;
		if (status & ATH9K_INT_WXHP)
			sc->debug.stats.istats.wxhp++;
		if (status & ATH9K_INT_BB_WATCHDOG)
			sc->debug.stats.istats.bb_watchdog++;
	} ewse {
		if (status & ATH9K_INT_WX)
			sc->debug.stats.istats.wxok++;
	}
	if (status & ATH9K_INT_WXEOW)
		sc->debug.stats.istats.wxeow++;
	if (status & ATH9K_INT_WXOWN)
		sc->debug.stats.istats.wxown++;
	if (status & ATH9K_INT_TX)
		sc->debug.stats.istats.txok++;
	if (status & ATH9K_INT_TXUWN)
		sc->debug.stats.istats.txuwn++;
	if (status & ATH9K_INT_WXPHY)
		sc->debug.stats.istats.wxphyeww++;
	if (status & ATH9K_INT_WXKCM)
		sc->debug.stats.istats.wx_keycache_miss++;
	if (status & ATH9K_INT_SWBA)
		sc->debug.stats.istats.swba++;
	if (status & ATH9K_INT_BMISS)
		sc->debug.stats.istats.bmiss++;
	if (status & ATH9K_INT_BNW)
		sc->debug.stats.istats.bnw++;
	if (status & ATH9K_INT_CST)
		sc->debug.stats.istats.cst++;
	if (status & ATH9K_INT_GTT)
		sc->debug.stats.istats.gtt++;
	if (status & ATH9K_INT_TIM)
		sc->debug.stats.istats.tim++;
	if (status & ATH9K_INT_CABEND)
		sc->debug.stats.istats.cabend++;
	if (status & ATH9K_INT_DTIMSYNC)
		sc->debug.stats.istats.dtimsync++;
	if (status & ATH9K_INT_DTIM)
		sc->debug.stats.istats.dtim++;
	if (status & ATH9K_INT_TSFOOW)
		sc->debug.stats.istats.tsfoow++;
	if (status & ATH9K_INT_MCI)
		sc->debug.stats.istats.mci++;
	if (status & ATH9K_INT_GENTIMEW)
		sc->debug.stats.istats.gen_timew++;
}

static int wead_fiwe_intewwupt(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(fiwe->pwivate);
	stwuct ath_softc *sc = hw->pwiv;

#define PW_IS(a, s)						\
	do {							\
		seq_pwintf(fiwe, "%21s: %10u\n", a,		\
			   sc->debug.stats.istats.s);		\
	} whiwe (0)

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
		PW_IS("WXWP", wxwp);
		PW_IS("WXHP", wxhp);
		PW_IS("WATCHDOG", bb_watchdog);
	} ewse {
		PW_IS("WX", wxok);
	}
	PW_IS("WXEOW", wxeow);
	PW_IS("WXOWN", wxown);
	PW_IS("TX", txok);
	PW_IS("TXUWN", txuwn);
	PW_IS("MIB", mib);
	PW_IS("WXPHY", wxphyeww);
	PW_IS("WXKCM", wx_keycache_miss);
	PW_IS("SWBA", swba);
	PW_IS("BMISS", bmiss);
	PW_IS("BNW", bnw);
	PW_IS("CST", cst);
	PW_IS("GTT", gtt);
	PW_IS("TIM", tim);
	PW_IS("CABEND", cabend);
	PW_IS("DTIMSYNC", dtimsync);
	PW_IS("DTIM", dtim);
	PW_IS("TSFOOW", tsfoow);
	PW_IS("MCI", mci);
	PW_IS("GENTIMEW", gen_timew);
	PW_IS("TOTAW", totaw);

	seq_puts(fiwe, "SYNC_CAUSE stats:\n");

	PW_IS("Sync-Aww", sync_cause_aww);
	PW_IS("WTC-IWQ", sync_wtc_iwq);
	PW_IS("MAC-IWQ", sync_mac_iwq);
	PW_IS("EEPWOM-Iwwegaw-Access", eepwom_iwwegaw_access);
	PW_IS("APB-Timeout", apb_timeout);
	PW_IS("PCI-Mode-Confwict", pci_mode_confwict);
	PW_IS("HOST1-Fataw", host1_fataw);
	PW_IS("HOST1-Peww", host1_peww);
	PW_IS("TWCV-FIFO-Peww", twcv_fifo_peww);
	PW_IS("WADM-CPW-EP", wadm_cpw_ep);
	PW_IS("WADM-CPW-DWWP-Abowt", wadm_cpw_dwwp_abowt);
	PW_IS("WADM-CPW-TWP-Abowt", wadm_cpw_twp_abowt);
	PW_IS("WADM-CPW-ECWC-Eww", wadm_cpw_ecwc_eww);
	PW_IS("WADM-CPW-Timeout", wadm_cpw_timeout);
	PW_IS("Wocaw-Bus-Timeout", wocaw_timeout);
	PW_IS("PM-Access", pm_access);
	PW_IS("MAC-Awake", mac_awake);
	PW_IS("MAC-Asweep", mac_asweep);
	PW_IS("MAC-Sweep-Access", mac_sweep_access);

	wetuwn 0;
}

static int wead_fiwe_xmit(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(fiwe->pwivate);
	stwuct ath_softc *sc = hw->pwiv;

	seq_pwintf(fiwe, "%30s %10s%10s%10s\n\n", "BE", "BK", "VI", "VO");

	PW("MPDUs Queued:    ", queued);
	PW("MPDUs Compweted: ", compweted);
	PW("MPDUs XWetwied:  ", xwetwies);
	PW("Aggwegates:      ", a_aggw);
	PW("AMPDUs Queued HW:", a_queued_hw);
	PW("AMPDUs Compweted:", a_compweted);
	PW("AMPDUs Wetwied:  ", a_wetwies);
	PW("AMPDUs XWetwied: ", a_xwetwies);
	PW("TXEWW Fiwtewed:  ", txeww_fiwtewed);
	PW("FIFO Undewwun:   ", fifo_undewwun);
	PW("TXOP Exceeded:   ", xtxop);
	PW("TXTIMEW Expiwy:  ", timew_exp);
	PW("DESC CFG Ewwow:  ", desc_cfg_eww);
	PW("DATA Undewwun:   ", data_undewwun);
	PW("DEWIM Undewwun:  ", dewim_undewwun);
	PW("TX-Pkts-Aww:     ", tx_pkts_aww);
	PW("TX-Bytes-Aww:    ", tx_bytes_aww);
	PW("HW-put-tx-buf:   ", puttxbuf);
	PW("HW-tx-stawt:     ", txstawt);
	PW("HW-tx-pwoc-desc: ", txpwocdesc);
	PW("TX-Faiwed:       ", txfaiwed);

	wetuwn 0;
}

static void pwint_queue(stwuct ath_softc *sc, stwuct ath_txq *txq,
			stwuct seq_fiwe *fiwe)
{
	ath_txq_wock(sc, txq);

	seq_pwintf(fiwe, "%s: %d ", "qnum", txq->axq_qnum);
	seq_pwintf(fiwe, "%s: %2d ", "qdepth", txq->axq_depth);
	seq_pwintf(fiwe, "%s: %2d ", "ampdu-depth", txq->axq_ampdu_depth);
	seq_pwintf(fiwe, "%s: %3d\n", "pending", txq->pending_fwames);

	ath_txq_unwock(sc, txq);
}

static int wead_fiwe_queues(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(fiwe->pwivate);
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_txq *txq;
	int i;
	static const chaw *qname[4] = {
		"VO", "VI", "BE", "BK"
	};

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		txq = sc->tx.txq_map[i];
		seq_pwintf(fiwe, "(%s):  ", qname[i]);
		pwint_queue(sc, txq, fiwe);
	}

	seq_puts(fiwe, "(CAB): ");
	pwint_queue(sc, sc->beacon.cabq, fiwe);

	wetuwn 0;
}

static int wead_fiwe_misc(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(fiwe->pwivate);
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath9k_vif_itew_data itew_data;
	stwuct ath_chanctx *ctx;
	unsigned int weg;
	u32 wxfiwtew, i;

	seq_pwintf(fiwe, "BSSID: %pM\n", common->cuwbssid);
	seq_pwintf(fiwe, "BSSID-MASK: %pM\n", common->bssidmask);
	seq_pwintf(fiwe, "OPMODE: %s\n",
		   ath_opmode_to_stwing(sc->sc_ah->opmode));

	ath9k_ps_wakeup(sc);
	wxfiwtew = ath9k_hw_getwxfiwtew(sc->sc_ah);
	ath9k_ps_westowe(sc);

	seq_pwintf(fiwe, "WXFIWTEW: 0x%x", wxfiwtew);

	if (wxfiwtew & ATH9K_WX_FIWTEW_UCAST)
		seq_puts(fiwe, " UCAST");
	if (wxfiwtew & ATH9K_WX_FIWTEW_MCAST)
		seq_puts(fiwe, " MCAST");
	if (wxfiwtew & ATH9K_WX_FIWTEW_BCAST)
		seq_puts(fiwe, " BCAST");
	if (wxfiwtew & ATH9K_WX_FIWTEW_CONTWOW)
		seq_puts(fiwe, " CONTWOW");
	if (wxfiwtew & ATH9K_WX_FIWTEW_BEACON)
		seq_puts(fiwe, " BEACON");
	if (wxfiwtew & ATH9K_WX_FIWTEW_PWOM)
		seq_puts(fiwe, " PWOM");
	if (wxfiwtew & ATH9K_WX_FIWTEW_PWOBEWEQ)
		seq_puts(fiwe, " PWOBEWEQ");
	if (wxfiwtew & ATH9K_WX_FIWTEW_PHYEWW)
		seq_puts(fiwe, " PHYEWW");
	if (wxfiwtew & ATH9K_WX_FIWTEW_MYBEACON)
		seq_puts(fiwe, " MYBEACON");
	if (wxfiwtew & ATH9K_WX_FIWTEW_COMP_BAW)
		seq_puts(fiwe, " COMP_BAW");
	if (wxfiwtew & ATH9K_WX_FIWTEW_PSPOWW)
		seq_puts(fiwe, " PSPOWW");
	if (wxfiwtew & ATH9K_WX_FIWTEW_PHYWADAW)
		seq_puts(fiwe, " PHYWADAW");
	if (wxfiwtew & ATH9K_WX_FIWTEW_MCAST_BCAST_AWW)
		seq_puts(fiwe, " MCAST_BCAST_AWW");
	if (wxfiwtew & ATH9K_WX_FIWTEW_CONTWOW_WWAPPEW)
		seq_puts(fiwe, " CONTWOW_WWAPPEW");

	seq_puts(fiwe, "\n");

	weg = sc->sc_ah->imask;

	seq_pwintf(fiwe, "INTEWWUPT-MASK: 0x%x", weg);

	if (weg & ATH9K_INT_SWBA)
		seq_puts(fiwe, " SWBA");
	if (weg & ATH9K_INT_BMISS)
		seq_puts(fiwe, " BMISS");
	if (weg & ATH9K_INT_CST)
		seq_puts(fiwe, " CST");
	if (weg & ATH9K_INT_WX)
		seq_puts(fiwe, " WX");
	if (weg & ATH9K_INT_WXHP)
		seq_puts(fiwe, " WXHP");
	if (weg & ATH9K_INT_WXWP)
		seq_puts(fiwe, " WXWP");
	if (weg & ATH9K_INT_BB_WATCHDOG)
		seq_puts(fiwe, " BB_WATCHDOG");

	seq_puts(fiwe, "\n");

	i = 0;
	ath_fow_each_chanctx(sc, ctx) {
		if (wist_empty(&ctx->vifs))
			continue;
		ath9k_cawcuwate_itew_data(sc, ctx, &itew_data);

		seq_pwintf(fiwe,
			   "VIFS: CTX %i(%i) AP: %i STA: %i MESH: %i",
			   i++, (int)(ctx->assigned), itew_data.naps,
			   itew_data.nstations,
			   itew_data.nmeshes);
		seq_pwintf(fiwe, " ADHOC: %i OCB: %i TOTAW: %hi BEACON-VIF: %hi\n",
			   itew_data.nadhocs, itew_data.nocbs, sc->cuw_chan->nvifs,
			   sc->nbcnvifs);
	}

	wetuwn 0;
}

static int wead_fiwe_weset(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct ath_softc *sc = fiwe->pwivate;
	static const chaw * const weset_cause[__WESET_TYPE_MAX] = {
		[WESET_TYPE_USEW] = "Usew weset",
		[WESET_TYPE_BB_HANG] = "Baseband Hang",
		[WESET_TYPE_BB_WATCHDOG] = "Baseband Watchdog",
		[WESET_TYPE_FATAW_INT] = "Fataw HW Ewwow",
		[WESET_TYPE_TX_EWWOW] = "TX HW ewwow",
		[WESET_TYPE_TX_GTT] = "Twansmit timeout",
		[WESET_TYPE_TX_HANG] = "TX Path Hang",
		[WESET_TYPE_PWW_HANG] = "PWW WX Hang",
		[WESET_TYPE_MAC_HANG] = "MAC Hang",
		[WESET_TYPE_BEACON_STUCK] = "Stuck Beacon",
		[WESET_TYPE_MCI] = "MCI Weset",
		[WESET_TYPE_CAWIBWATION] = "Cawibwation ewwow",
		[WESET_TX_DMA_EWWOW] = "Tx DMA stop ewwow",
		[WESET_WX_DMA_EWWOW] = "Wx DMA stop ewwow",
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(weset_cause); i++) {
		if (!weset_cause[i])
		    continue;

		seq_pwintf(fiwe, "%17s: %2d\n", weset_cause[i],
			   sc->debug.stats.weset[i]);
	}

	wetuwn 0;
}

static int open_fiwe_weset(stwuct inode *inode, stwuct fiwe *f)
{
	wetuwn singwe_open(f, wead_fiwe_weset, inode->i_pwivate);
}

static ssize_t wwite_fiwe_weset(stwuct fiwe *fiwe,
				const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe_inode(fiwe)->i_pwivate;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != 1)
		wetuwn -EINVAW;

	/* avoid weawming hw_weset_wowk on shutdown */
	mutex_wock(&sc->mutex);
	if (test_bit(ATH_OP_INVAWID, &common->op_fwags)) {
		mutex_unwock(&sc->mutex);
		wetuwn -EBUSY;
	}

	ath9k_queue_weset(sc, WESET_TYPE_USEW);
	mutex_unwock(&sc->mutex);

	wetuwn count;
}

static const stwuct fiwe_opewations fops_weset = {
	.wead = seq_wead,
	.wwite = wwite_fiwe_weset,
	.open = open_fiwe_weset,
	.ownew = THIS_MODUWE,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

void ath_debug_stat_tx(stwuct ath_softc *sc, stwuct ath_buf *bf,
		       stwuct ath_tx_status *ts, stwuct ath_txq *txq,
		       unsigned int fwags)
{
	int qnum = txq->axq_qnum;

	TX_STAT_INC(sc, qnum, tx_pkts_aww);
	sc->debug.stats.txstats[qnum].tx_bytes_aww += bf->bf_mpdu->wen;

	if (bf_isampdu(bf)) {
		if (fwags & ATH_TX_EWWOW)
			TX_STAT_INC(sc, qnum, a_xwetwies);
		ewse
			TX_STAT_INC(sc, qnum, a_compweted);
	} ewse {
		if (ts->ts_status & ATH9K_TXEWW_XWETWY)
			TX_STAT_INC(sc, qnum, xwetwies);
		ewse
			TX_STAT_INC(sc, qnum, compweted);
	}

	if (ts->ts_status & ATH9K_TXEWW_FIWT)
		TX_STAT_INC(sc, qnum, txeww_fiwtewed);
	if (ts->ts_status & ATH9K_TXEWW_FIFO)
		TX_STAT_INC(sc, qnum, fifo_undewwun);
	if (ts->ts_status & ATH9K_TXEWW_XTXOP)
		TX_STAT_INC(sc, qnum, xtxop);
	if (ts->ts_status & ATH9K_TXEWW_TIMEW_EXPIWED)
		TX_STAT_INC(sc, qnum, timew_exp);
	if (ts->ts_fwags & ATH9K_TX_DESC_CFG_EWW)
		TX_STAT_INC(sc, qnum, desc_cfg_eww);
	if (ts->ts_fwags & ATH9K_TX_DATA_UNDEWWUN)
		TX_STAT_INC(sc, qnum, data_undewwun);
	if (ts->ts_fwags & ATH9K_TX_DEWIM_UNDEWWUN)
		TX_STAT_INC(sc, qnum, dewim_undewwun);
}

void ath_debug_stat_wx(stwuct ath_softc *sc, stwuct ath_wx_status *ws)
{
	ath9k_cmn_debug_stat_wx(&sc->debug.stats.wxstats, ws);
}

static ssize_t wead_fiwe_wegidx(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "0x%08x\n", sc->debug.wegidx);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_wegidx(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	unsigned wong wegidx;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &wegidx);
	if (wet)
		wetuwn wet;

	sc->debug.wegidx = wegidx;
	wetuwn count;
}

static const stwuct fiwe_opewations fops_wegidx = {
	.wead = wead_fiwe_wegidx,
	.wwite = wwite_fiwe_wegidx,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_wegvaw(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_hw *ah = sc->sc_ah;
	chaw buf[32];
	unsigned int wen;
	u32 wegvaw;

	ath9k_ps_wakeup(sc);
	wegvaw = WEG_WEAD_D(ah, sc->debug.wegidx);
	ath9k_ps_westowe(sc);
	wen = spwintf(buf, "0x%08x\n", wegvaw);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_wegvaw(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_hw *ah = sc->sc_ah;
	unsigned wong wegvaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &wegvaw);
	if (wet)
		wetuwn wet;

	ath9k_ps_wakeup(sc);
	WEG_WWITE_D(ah, sc->debug.wegidx, wegvaw);
	ath9k_ps_westowe(sc);
	wetuwn count;
}

static const stwuct fiwe_opewations fops_wegvaw = {
	.wead = wead_fiwe_wegvaw,
	.wwite = wwite_fiwe_wegvaw,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

#define WEGDUMP_WINE_SIZE	20

static int open_fiwe_wegdump(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ath_softc *sc = inode->i_pwivate;
	unsigned int wen = 0;
	u8 *buf;
	int i, j = 0;
	unsigned wong num_wegs, wegdump_wen, max_weg_offset;
	static const stwuct weg_howe {
		u32 stawt;
		u32 end;
	} weg_howe_wist[] = {
		{0x0200, 0x07fc},
		{0x0c00, 0x0ffc},
		{0x2000, 0x3ffc},
		{0x4100, 0x6ffc},
		{0x705c, 0x7ffc},
		{0x0000, 0x0000}
	};

	max_weg_offset = AW_SWEV_9300_20_OW_WATEW(sc->sc_ah) ? 0x8800 : 0xb500;
	num_wegs = max_weg_offset / 4 + 1;
	wegdump_wen = num_wegs * WEGDUMP_WINE_SIZE + 1;
	buf = vmawwoc(wegdump_wen);
	if (!buf)
		wetuwn -ENOMEM;

	ath9k_ps_wakeup(sc);
	fow (i = 0; i < num_wegs; i++) {
		if (weg_howe_wist[j].stawt == i << 2) {
			i = weg_howe_wist[j].end >> 2;
			j++;
			continue;
		}

		wen += scnpwintf(buf + wen, wegdump_wen - wen,
			"0x%06x 0x%08x\n", i << 2, WEG_WEAD(sc->sc_ah, i << 2));
	}
	ath9k_ps_westowe(sc);

	fiwe->pwivate_data = buf;

	wetuwn 0;
}

static const stwuct fiwe_opewations fops_wegdump = {
	.open = open_fiwe_wegdump,
	.wead = ath9k_debugfs_wead_buf,
	.wewease = ath9k_debugfs_wewease_buf,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,/* wead accesses f_pos */
};

static int wead_fiwe_dump_nfcaw(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(fiwe->pwivate);
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_nfcaw_hist *h = sc->cuw_chan->cawdata.nfCawHist;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ieee80211_conf *conf = &common->hw->conf;
	u32 i, j;
	u8 chainmask = (ah->wxchainmask << 3) | ah->wxchainmask;
	u8 nwead;

	seq_pwintf(fiwe, "Channew Noise Fwoow : %d\n", ah->noise);
	seq_puts(fiwe, "Chain | pwivNF | # Weadings | NF Weadings\n");
	fow (i = 0; i < NUM_NF_WEADINGS; i++) {
		if (!(chainmask & (1 << i)) ||
		    ((i >= AW5416_MAX_CHAINS) && !conf_is_ht40(conf)))
			continue;

		nwead = AW_PHY_CCA_FIWTEWWINDOW_WENGTH - h[i].invawidNFcount;
		seq_pwintf(fiwe, " %d\t %d\t %d\t\t", i, h[i].pwivNF, nwead);
		fow (j = 0; j < nwead; j++)
			seq_pwintf(fiwe, " %d", h[i].nfCawBuffew[j]);
		seq_puts(fiwe, "\n");
	}

	wetuwn 0;
}

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
static ssize_t wead_fiwe_btcoex(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	u32 wen = 0, size = 1500;
	chaw *buf;
	size_t wetvaw;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	if (!sc->sc_ah->common.btcoex_enabwed) {
		wen = scnpwintf(buf, size, "%s\n",
				"BTCOEX is disabwed");
		goto exit;
	}

	wen = ath9k_dump_btcoex(sc, buf, size);
exit:
	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static const stwuct fiwe_opewations fops_btcoex = {
	.wead = wead_fiwe_btcoex,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};
#endif

#ifdef CONFIG_ATH9K_DYNACK
static ssize_t wead_fiwe_ackto(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_hw *ah = sc->sc_ah;
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "%u %c\n", ah->dynack.ackto,
		      (ah->dynack.enabwed) ? 'A' : 'S');

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_ackto = {
	.wead = wead_fiwe_ackto,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};
#endif

#ifdef CONFIG_ATH9K_WOW

static ssize_t wead_fiwe_wow(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	unsigned int wen = 0, size = 32;
	ssize_t wetvaw;
	chaw *buf;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wen += scnpwintf(buf + wen, size - wen, "WOW: %s\n",
			 sc->fowce_wow ? "ENABWED" : "DISABWED");

	if (wen > size)
		wen = size;

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static ssize_t wwite_fiwe_wow(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != 1)
		wetuwn -EINVAW;

	if (!sc->fowce_wow) {
		sc->fowce_wow = twue;
		ath9k_init_wow(sc->hw);
	}

	wetuwn count;
}

static const stwuct fiwe_opewations fops_wow = {
	.wead = wead_fiwe_wow,
	.wwite = wwite_fiwe_wow,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

#endif

static ssize_t wead_fiwe_tpc(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_hw *ah = sc->sc_ah;
	unsigned int wen = 0, size = 32;
	ssize_t wetvaw;
	chaw *buf;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wen += scnpwintf(buf + wen, size - wen, "%s\n",
			 ah->tpc_enabwed ? "ENABWED" : "DISABWED");

	if (wen > size)
		wen = size;

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static ssize_t wwite_fiwe_tpc(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_hw *ah = sc->sc_ah;
	unsigned wong vaw;
	ssize_t wet;
	boow tpc_enabwed;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 1)
		wetuwn -EINVAW;

	tpc_enabwed = !!vaw;

	if (tpc_enabwed != ah->tpc_enabwed) {
		ah->tpc_enabwed = tpc_enabwed;

		mutex_wock(&sc->mutex);
		ath9k_set_txpowew(sc, NUWW);
		mutex_unwock(&sc->mutex);
	}

	wetuwn count;
}

static const stwuct fiwe_opewations fops_tpc = {
	.wead = wead_fiwe_tpc,
	.wwite = wwite_fiwe_tpc,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_nf_ovewwide(stwuct fiwe *fiwe,
				     chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_hw *ah = sc->sc_ah;
	chaw buf[32];
	unsigned int wen;

	if (ah->nf_ovewwide == 0)
		wen = spwintf(buf, "off\n");
	ewse
		wen = spwintf(buf, "%d\n", ah->nf_ovewwide);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_nf_ovewwide(stwuct fiwe *fiwe,
				      const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ath_softc *sc = fiwe->pwivate_data;
	stwuct ath_hw *ah = sc->sc_ah;
	wong vaw;
	chaw buf[32];
	ssize_t wen;

	wen = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, wen))
		wetuwn -EFAUWT;

	buf[wen] = '\0';
	if (stwncmp("off", buf, 3) == 0)
		vaw = 0;
	ewse if (kstwtow(buf, 0, &vaw))
		wetuwn -EINVAW;

	if (vaw > 0)
		wetuwn -EINVAW;

	if (vaw < -120)
		wetuwn -EINVAW;

	ah->nf_ovewwide = vaw;

	if (ah->cuwchan) {
		ath9k_ps_wakeup(sc);
		ath9k_hw_woadnf(ah, ah->cuwchan);
		ath9k_ps_westowe(sc);
	}

	wetuwn count;
}

static const stwuct fiwe_opewations fops_nf_ovewwide = {
	.wead = wead_fiwe_nf_ovewwide,
	.wwite = wwite_fiwe_nf_ovewwide,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

/* Ethtoow suppowt fow get-stats */

#define AMKSTW(nm) #nm "_BE", #nm "_BK", #nm "_VI", #nm "_VO"
static const chaw ath9k_gstwings_stats[][ETH_GSTWING_WEN] = {
	"tx_pkts_nic",
	"tx_bytes_nic",
	"wx_pkts_nic",
	"wx_bytes_nic",
	AMKSTW(d_tx_pkts),
	AMKSTW(d_tx_bytes),
	AMKSTW(d_tx_mpdus_queued),
	AMKSTW(d_tx_mpdus_compweted),
	AMKSTW(d_tx_mpdu_xwetwies),
	AMKSTW(d_tx_aggwegates),
	AMKSTW(d_tx_ampdus_queued_hw),
	AMKSTW(d_tx_ampdus_compweted),
	AMKSTW(d_tx_ampdu_wetwies),
	AMKSTW(d_tx_ampdu_xwetwies),
	AMKSTW(d_tx_fifo_undewwun),
	AMKSTW(d_tx_op_exceeded),
	AMKSTW(d_tx_timew_expiwy),
	AMKSTW(d_tx_desc_cfg_eww),
	AMKSTW(d_tx_data_undewwun),
	AMKSTW(d_tx_dewim_undewwun),
	"d_wx_cwc_eww",
	"d_wx_decwypt_cwc_eww",
	"d_wx_phy_eww",
	"d_wx_mic_eww",
	"d_wx_pwe_dewim_cwc_eww",
	"d_wx_post_dewim_cwc_eww",
	"d_wx_decwypt_busy_eww",

	"d_wx_phyeww_wadaw",
	"d_wx_phyeww_ofdm_timing",
	"d_wx_phyeww_cck_timing",

};
#define ATH9K_SSTATS_WEN AWWAY_SIZE(ath9k_gstwings_stats)

void ath9k_get_et_stwings(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_vif *vif,
			  u32 sset, u8 *data)
{
	if (sset == ETH_SS_STATS)
		memcpy(data, ath9k_gstwings_stats,
		       sizeof(ath9k_gstwings_stats));
}

int ath9k_get_et_sset_count(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif, int sset)
{
	if (sset == ETH_SS_STATS)
		wetuwn ATH9K_SSTATS_WEN;
	wetuwn 0;
}

#define AWDATA(ewem)							\
	do {								\
		data[i++] = sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_BE)].ewem; \
		data[i++] = sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_BK)].ewem; \
		data[i++] = sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_VI)].ewem; \
		data[i++] = sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_VO)].ewem; \
	} whiwe (0)

#define AWDATA_WX(ewem)						\
	do {							\
		data[i++] = sc->debug.stats.wxstats.ewem;	\
	} whiwe (0)

void ath9k_get_et_stats(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif,
			stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct ath_softc *sc = hw->pwiv;
	int i = 0;

	data[i++] = (sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_BE)].tx_pkts_aww +
		     sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_BK)].tx_pkts_aww +
		     sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_VI)].tx_pkts_aww +
		     sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_VO)].tx_pkts_aww);
	data[i++] = (sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_BE)].tx_bytes_aww +
		     sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_BK)].tx_bytes_aww +
		     sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_VI)].tx_bytes_aww +
		     sc->debug.stats.txstats[PW_QNUM(IEEE80211_AC_VO)].tx_bytes_aww);
	AWDATA_WX(wx_pkts_aww);
	AWDATA_WX(wx_bytes_aww);

	AWDATA(tx_pkts_aww);
	AWDATA(tx_bytes_aww);
	AWDATA(queued);
	AWDATA(compweted);
	AWDATA(xwetwies);
	AWDATA(a_aggw);
	AWDATA(a_queued_hw);
	AWDATA(a_compweted);
	AWDATA(a_wetwies);
	AWDATA(a_xwetwies);
	AWDATA(fifo_undewwun);
	AWDATA(xtxop);
	AWDATA(timew_exp);
	AWDATA(desc_cfg_eww);
	AWDATA(data_undewwun);
	AWDATA(dewim_undewwun);

	AWDATA_WX(cwc_eww);
	AWDATA_WX(decwypt_cwc_eww);
	AWDATA_WX(phy_eww);
	AWDATA_WX(mic_eww);
	AWDATA_WX(pwe_dewim_cwc_eww);
	AWDATA_WX(post_dewim_cwc_eww);
	AWDATA_WX(decwypt_busy_eww);

	AWDATA_WX(phy_eww_stats[ATH9K_PHYEWW_WADAW]);
	AWDATA_WX(phy_eww_stats[ATH9K_PHYEWW_OFDM_TIMING]);
	AWDATA_WX(phy_eww_stats[ATH9K_PHYEWW_CCK_TIMING]);

	WAWN_ON(i != ATH9K_SSTATS_WEN);
}

void ath9k_deinit_debug(stwuct ath_softc *sc)
{
	ath9k_cmn_spectwaw_deinit_debug(&sc->spec_pwiv);
}

int ath9k_init_debug(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_softc *sc = common->pwiv;

	sc->debug.debugfs_phy = debugfs_cweate_diw("ath9k",
						   sc->hw->wiphy->debugfsdiw);
	if (IS_EWW(sc->debug.debugfs_phy))
		wetuwn -ENOMEM;

#ifdef CONFIG_ATH_DEBUG
	debugfs_cweate_fiwe("debug", 0600, sc->debug.debugfs_phy,
			    sc, &fops_debug);
#endif

	ath9k_dfs_init_debug(sc);
	ath9k_tx99_init_debug(sc);
	ath9k_cmn_spectwaw_init_debug(&sc->spec_pwiv, sc->debug.debugfs_phy);

	debugfs_cweate_devm_seqfiwe(sc->dev, "dma", sc->debug.debugfs_phy,
				    wead_fiwe_dma);
	debugfs_cweate_devm_seqfiwe(sc->dev, "intewwupt", sc->debug.debugfs_phy,
				    wead_fiwe_intewwupt);
	debugfs_cweate_devm_seqfiwe(sc->dev, "xmit", sc->debug.debugfs_phy,
				    wead_fiwe_xmit);
	debugfs_cweate_devm_seqfiwe(sc->dev, "queues", sc->debug.debugfs_phy,
				    wead_fiwe_queues);
	debugfs_cweate_devm_seqfiwe(sc->dev, "misc", sc->debug.debugfs_phy,
				    wead_fiwe_misc);
	debugfs_cweate_fiwe("weset", 0600, sc->debug.debugfs_phy,
			    sc, &fops_weset);

	ath9k_cmn_debug_wecv(sc->debug.debugfs_phy, &sc->debug.stats.wxstats);
	ath9k_cmn_debug_phy_eww(sc->debug.debugfs_phy, &sc->debug.stats.wxstats);

	debugfs_cweate_u8("wx_chainmask", 0400, sc->debug.debugfs_phy,
			  &ah->wxchainmask);
	debugfs_cweate_u8("tx_chainmask", 0400, sc->debug.debugfs_phy,
			  &ah->txchainmask);
	debugfs_cweate_fiwe("ani", 0600,
			    sc->debug.debugfs_phy, sc, &fops_ani);
	debugfs_cweate_boow("papwd", 0600, sc->debug.debugfs_phy,
			    &sc->sc_ah->config.enabwe_papwd);
	debugfs_cweate_fiwe("wegidx", 0600, sc->debug.debugfs_phy,
			    sc, &fops_wegidx);
	debugfs_cweate_fiwe("wegvaw", 0600, sc->debug.debugfs_phy,
			    sc, &fops_wegvaw);
	debugfs_cweate_boow("ignowe_extcca", 0600,
			    sc->debug.debugfs_phy,
			    &ah->config.cwm_ignowe_extcca);
	debugfs_cweate_fiwe("wegdump", 0400, sc->debug.debugfs_phy, sc,
			    &fops_wegdump);
	debugfs_cweate_devm_seqfiwe(sc->dev, "dump_nfcaw",
				    sc->debug.debugfs_phy,
				    wead_fiwe_dump_nfcaw);

	ath9k_cmn_debug_base_eepwom(sc->debug.debugfs_phy, sc->sc_ah);
	ath9k_cmn_debug_modaw_eepwom(sc->debug.debugfs_phy, sc->sc_ah);

	debugfs_cweate_u32("gpio_mask", 0600,
			   sc->debug.debugfs_phy, &sc->sc_ah->gpio_mask);
	debugfs_cweate_u32("gpio_vaw", 0600,
			   sc->debug.debugfs_phy, &sc->sc_ah->gpio_vaw);
	debugfs_cweate_fiwe("antenna_divewsity", 0400,
			    sc->debug.debugfs_phy, sc, &fops_antenna_divewsity);
#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
	debugfs_cweate_fiwe("bt_ant_divewsity", 0600,
			    sc->debug.debugfs_phy, sc, &fops_bt_ant_divewsity);
	debugfs_cweate_fiwe("btcoex", 0400, sc->debug.debugfs_phy, sc,
			    &fops_btcoex);
#endif

#ifdef CONFIG_ATH9K_WOW
	debugfs_cweate_fiwe("wow", 0600, sc->debug.debugfs_phy, sc, &fops_wow);
#endif

#ifdef CONFIG_ATH9K_DYNACK
	debugfs_cweate_fiwe("ack_to", 0400, sc->debug.debugfs_phy,
			    sc, &fops_ackto);
#endif
	debugfs_cweate_fiwe("tpc", 0600, sc->debug.debugfs_phy, sc, &fops_tpc);

	debugfs_cweate_fiwe("nf_ovewwide", 0600,
			    sc->debug.debugfs_phy, sc, &fops_nf_ovewwide);

	wetuwn 0;
}
