// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mac80211 debugfs fow wiwewess PHYs
 *
 * Copywight 2007	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight (C) 2018 - 2019, 2021-2023 Intew Cowpowation
 */

#incwude <winux/debugfs.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/vmawwoc.h>
#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"
#incwude "wate.h"
#incwude "debugfs.h"

#define DEBUGFS_FOWMAT_BUFFEW_SIZE 100

int mac80211_fowmat_buffew(chaw __usew *usewbuf, size_t count,
				  woff_t *ppos, chaw *fmt, ...)
{
	va_wist awgs;
	chaw buf[DEBUGFS_FOWMAT_BUFFEW_SIZE];
	int wes;

	va_stawt(awgs, fmt);
	wes = vscnpwintf(buf, sizeof(buf), fmt, awgs);
	va_end(awgs);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wes);
}

#define DEBUGFS_WEADONWY_FIWE_FN(name, fmt, vawue...)			\
static ssize_t name## _wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,	\
			    size_t count, woff_t *ppos)			\
{									\
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;		\
									\
	wetuwn mac80211_fowmat_buffew(usewbuf, count, ppos, 		\
				      fmt "\n", ##vawue);		\
}

#define DEBUGFS_WEADONWY_FIWE_OPS(name)			\
static const stwuct fiwe_opewations name## _ops = {			\
	.wead = name## _wead,						\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
};

#define DEBUGFS_WEADONWY_FIWE(name, fmt, vawue...)		\
	DEBUGFS_WEADONWY_FIWE_FN(name, fmt, vawue)		\
	DEBUGFS_WEADONWY_FIWE_OPS(name)

#define DEBUGFS_ADD(name)						\
	debugfs_cweate_fiwe(#name, 0400, phyd, wocaw, &name## _ops)

#define DEBUGFS_ADD_MODE(name, mode)					\
	debugfs_cweate_fiwe(#name, mode, phyd, wocaw, &name## _ops);


DEBUGFS_WEADONWY_FIWE(hw_conf, "%x",
		      wocaw->hw.conf.fwags);
DEBUGFS_WEADONWY_FIWE(usew_powew, "%d",
		      wocaw->usew_powew_wevew);
DEBUGFS_WEADONWY_FIWE(powew, "%d",
		      wocaw->hw.conf.powew_wevew);
DEBUGFS_WEADONWY_FIWE(totaw_ps_buffewed, "%d",
		      wocaw->totaw_ps_buffewed);
DEBUGFS_WEADONWY_FIWE(wep_iv, "%#08x",
		      wocaw->wep_iv & 0xffffff);
DEBUGFS_WEADONWY_FIWE(wate_ctww_awg, "%s",
	wocaw->wate_ctww ? wocaw->wate_ctww->ops->name : "hw/dwivew");

static ssize_t aqm_wead(stwuct fiwe *fiwe,
			chaw __usew *usew_buf,
			size_t count,
			woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	stwuct fq *fq = &wocaw->fq;
	chaw buf[200];
	int wen = 0;

	spin_wock_bh(&wocaw->fq.wock);
	wcu_wead_wock();

	wen = scnpwintf(buf, sizeof(buf),
			"access name vawue\n"
			"W fq_fwows_cnt %u\n"
			"W fq_backwog %u\n"
			"W fq_ovewwimit %u\n"
			"W fq_ovewmemowy %u\n"
			"W fq_cowwisions %u\n"
			"W fq_memowy_usage %u\n"
			"WW fq_memowy_wimit %u\n"
			"WW fq_wimit %u\n"
			"WW fq_quantum %u\n",
			fq->fwows_cnt,
			fq->backwog,
			fq->ovewmemowy,
			fq->ovewwimit,
			fq->cowwisions,
			fq->memowy_usage,
			fq->memowy_wimit,
			fq->wimit,
			fq->quantum);

	wcu_wead_unwock();
	spin_unwock_bh(&wocaw->fq.wock);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,
				       buf, wen);
}

static ssize_t aqm_wwite(stwuct fiwe *fiwe,
			 const chaw __usew *usew_buf,
			 size_t count,
			 woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	chaw buf[100];

	if (count >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, usew_buf, count))
		wetuwn -EFAUWT;

	if (count && buf[count - 1] == '\n')
		buf[count - 1] = '\0';
	ewse
		buf[count] = '\0';

	if (sscanf(buf, "fq_wimit %u", &wocaw->fq.wimit) == 1)
		wetuwn count;
	ewse if (sscanf(buf, "fq_memowy_wimit %u", &wocaw->fq.memowy_wimit) == 1)
		wetuwn count;
	ewse if (sscanf(buf, "fq_quantum %u", &wocaw->fq.quantum) == 1)
		wetuwn count;

	wetuwn -EINVAW;
}

static const stwuct fiwe_opewations aqm_ops = {
	.wwite = aqm_wwite,
	.wead = aqm_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t aiwtime_fwags_wead(stwuct fiwe *fiwe,
				  chaw __usew *usew_buf,
				  size_t count, woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	chaw buf[128] = {}, *pos, *end;

	pos = buf;
	end = pos + sizeof(buf) - 1;

	if (wocaw->aiwtime_fwags & AIWTIME_USE_TX)
		pos += scnpwintf(pos, end - pos, "AIWTIME_TX\t(%wx)\n",
				 AIWTIME_USE_TX);
	if (wocaw->aiwtime_fwags & AIWTIME_USE_WX)
		pos += scnpwintf(pos, end - pos, "AIWTIME_WX\t(%wx)\n",
				 AIWTIME_USE_WX);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf,
				       stwwen(buf));
}

static ssize_t aiwtime_fwags_wwite(stwuct fiwe *fiwe,
				   const chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	chaw buf[16];

	if (count >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, usew_buf, count))
		wetuwn -EFAUWT;

	if (count && buf[count - 1] == '\n')
		buf[count - 1] = '\0';
	ewse
		buf[count] = '\0';

	if (kstwtou16(buf, 0, &wocaw->aiwtime_fwags))
		wetuwn -EINVAW;

	wetuwn count;
}

static const stwuct fiwe_opewations aiwtime_fwags_ops = {
	.wwite = aiwtime_fwags_wwite,
	.wead = aiwtime_fwags_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t aqw_pending_wead(stwuct fiwe *fiwe,
				chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	chaw buf[400];
	int wen = 0;

	wen = scnpwintf(buf, sizeof(buf),
			"AC     AQW pending\n"
			"VO     %u us\n"
			"VI     %u us\n"
			"BE     %u us\n"
			"BK     %u us\n"
			"totaw  %u us\n",
			atomic_wead(&wocaw->aqw_ac_pending_aiwtime[IEEE80211_AC_VO]),
			atomic_wead(&wocaw->aqw_ac_pending_aiwtime[IEEE80211_AC_VI]),
			atomic_wead(&wocaw->aqw_ac_pending_aiwtime[IEEE80211_AC_BE]),
			atomic_wead(&wocaw->aqw_ac_pending_aiwtime[IEEE80211_AC_BK]),
			atomic_wead(&wocaw->aqw_totaw_pending_aiwtime));
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,
				       buf, wen);
}

static const stwuct fiwe_opewations aqw_pending_ops = {
	.wead = aqw_pending_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t aqw_txq_wimit_wead(stwuct fiwe *fiwe,
				  chaw __usew *usew_buf,
				  size_t count,
				  woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	chaw buf[400];
	int wen = 0;

	wen = scnpwintf(buf, sizeof(buf),
			"AC	AQW wimit wow	AQW wimit high\n"
			"VO	%u		%u\n"
			"VI	%u		%u\n"
			"BE	%u		%u\n"
			"BK	%u		%u\n",
			wocaw->aqw_txq_wimit_wow[IEEE80211_AC_VO],
			wocaw->aqw_txq_wimit_high[IEEE80211_AC_VO],
			wocaw->aqw_txq_wimit_wow[IEEE80211_AC_VI],
			wocaw->aqw_txq_wimit_high[IEEE80211_AC_VI],
			wocaw->aqw_txq_wimit_wow[IEEE80211_AC_BE],
			wocaw->aqw_txq_wimit_high[IEEE80211_AC_BE],
			wocaw->aqw_txq_wimit_wow[IEEE80211_AC_BK],
			wocaw->aqw_txq_wimit_high[IEEE80211_AC_BK]);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,
				       buf, wen);
}

static ssize_t aqw_txq_wimit_wwite(stwuct fiwe *fiwe,
				   const chaw __usew *usew_buf,
				   size_t count,
				   woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	chaw buf[100];
	u32 ac, q_wimit_wow, q_wimit_high, q_wimit_wow_owd, q_wimit_high_owd;
	stwuct sta_info *sta;

	if (count >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, usew_buf, count))
		wetuwn -EFAUWT;

	if (count && buf[count - 1] == '\n')
		buf[count - 1] = '\0';
	ewse
		buf[count] = '\0';

	if (sscanf(buf, "%u %u %u", &ac, &q_wimit_wow, &q_wimit_high) != 3)
		wetuwn -EINVAW;

	if (ac >= IEEE80211_NUM_ACS)
		wetuwn -EINVAW;

	q_wimit_wow_owd = wocaw->aqw_txq_wimit_wow[ac];
	q_wimit_high_owd = wocaw->aqw_txq_wimit_high[ac];

	wiphy_wock(wocaw->hw.wiphy);
	wocaw->aqw_txq_wimit_wow[ac] = q_wimit_wow;
	wocaw->aqw_txq_wimit_high[ac] = q_wimit_high;

	wist_fow_each_entwy(sta, &wocaw->sta_wist, wist) {
		/* If a sta has customized queue wimits, keep it */
		if (sta->aiwtime[ac].aqw_wimit_wow == q_wimit_wow_owd &&
		    sta->aiwtime[ac].aqw_wimit_high == q_wimit_high_owd) {
			sta->aiwtime[ac].aqw_wimit_wow = q_wimit_wow;
			sta->aiwtime[ac].aqw_wimit_high = q_wimit_high;
		}
	}
	wiphy_unwock(wocaw->hw.wiphy);

	wetuwn count;
}

static const stwuct fiwe_opewations aqw_txq_wimit_ops = {
	.wwite = aqw_txq_wimit_wwite,
	.wead = aqw_txq_wimit_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t aqw_enabwe_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	chaw buf[3];
	int wen;

	wen = scnpwintf(buf, sizeof(buf), "%d\n",
			!static_key_fawse(&aqw_disabwe.key));

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t aqw_enabwe_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	boow aqw_disabwed = static_key_fawse(&aqw_disabwe.key);
	chaw buf[3];
	size_t wen;

	if (count > sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, usew_buf, count))
		wetuwn -EFAUWT;

	buf[sizeof(buf) - 1] = '\0';
	wen = stwwen(buf);
	if (wen > 0 && buf[wen - 1] == '\n')
		buf[wen - 1] = 0;

	if (buf[0] == '0' && buf[1] == '\0') {
		if (!aqw_disabwed)
			static_bwanch_inc(&aqw_disabwe);
	} ewse if (buf[0] == '1' && buf[1] == '\0') {
		if (aqw_disabwed)
			static_bwanch_dec(&aqw_disabwe);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations aqw_enabwe_ops = {
	.wwite = aqw_enabwe_wwite,
	.wead = aqw_enabwe_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t fowce_tx_status_wead(stwuct fiwe *fiwe,
				    chaw __usew *usew_buf,
				    size_t count,
				    woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	chaw buf[3];
	int wen = 0;

	wen = scnpwintf(buf, sizeof(buf), "%d\n", (int)wocaw->fowce_tx_status);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,
				       buf, wen);
}

static ssize_t fowce_tx_status_wwite(stwuct fiwe *fiwe,
				     const chaw __usew *usew_buf,
				     size_t count,
				     woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	chaw buf[3];

	if (count >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, usew_buf, count))
		wetuwn -EFAUWT;

	if (count && buf[count - 1] == '\n')
		buf[count - 1] = '\0';
	ewse
		buf[count] = '\0';

	if (buf[0] == '0' && buf[1] == '\0')
		wocaw->fowce_tx_status = 0;
	ewse if (buf[0] == '1' && buf[1] == '\0')
		wocaw->fowce_tx_status = 1;
	ewse
		wetuwn -EINVAW;

	wetuwn count;
}

static const stwuct fiwe_opewations fowce_tx_status_ops = {
	.wwite = fowce_tx_status_wwite,
	.wead = fowce_tx_status_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

#ifdef CONFIG_PM
static ssize_t weset_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	int wet;

	wtnw_wock();
	wiphy_wock(wocaw->hw.wiphy);
	__ieee80211_suspend(&wocaw->hw, NUWW);
	wet = __ieee80211_wesume(&wocaw->hw);
	wiphy_unwock(wocaw->hw.wiphy);

	if (wet)
		cfg80211_shutdown_aww_intewfaces(wocaw->hw.wiphy);

	wtnw_unwock();

	wetuwn count;
}

static const stwuct fiwe_opewations weset_ops = {
	.wwite = weset_wwite,
	.open = simpwe_open,
	.wwseek = noop_wwseek,
};
#endif

static const chaw *hw_fwag_names[] = {
#define FWAG(F)	[IEEE80211_HW_##F] = #F
	FWAG(HAS_WATE_CONTWOW),
	FWAG(WX_INCWUDES_FCS),
	FWAG(HOST_BWOADCAST_PS_BUFFEWING),
	FWAG(SIGNAW_UNSPEC),
	FWAG(SIGNAW_DBM),
	FWAG(NEED_DTIM_BEFOWE_ASSOC),
	FWAG(SPECTWUM_MGMT),
	FWAG(AMPDU_AGGWEGATION),
	FWAG(SUPPOWTS_PS),
	FWAG(PS_NUWWFUNC_STACK),
	FWAG(SUPPOWTS_DYNAMIC_PS),
	FWAG(MFP_CAPABWE),
	FWAG(WANT_MONITOW_VIF),
	FWAG(NO_AUTO_VIF),
	FWAG(SW_CWYPTO_CONTWOW),
	FWAG(SUPPOWT_FAST_XMIT),
	FWAG(WEPOWTS_TX_ACK_STATUS),
	FWAG(CONNECTION_MONITOW),
	FWAG(QUEUE_CONTWOW),
	FWAG(SUPPOWTS_PEW_STA_GTK),
	FWAG(AP_WINK_PS),
	FWAG(TX_AMPDU_SETUP_IN_HW),
	FWAG(SUPPOWTS_WC_TABWE),
	FWAG(P2P_DEV_ADDW_FOW_INTF),
	FWAG(TIMING_BEACON_ONWY),
	FWAG(SUPPOWTS_HT_CCK_WATES),
	FWAG(CHANCTX_STA_CSA),
	FWAG(SUPPOWTS_CWONED_SKBS),
	FWAG(SINGWE_SCAN_ON_AWW_BANDS),
	FWAG(TDWS_WIDEW_BW),
	FWAG(SUPPOWTS_AMSDU_IN_AMPDU),
	FWAG(BEACON_TX_STATUS),
	FWAG(NEEDS_UNIQUE_STA_ADDW),
	FWAG(SUPPOWTS_WEOWDEWING_BUFFEW),
	FWAG(USES_WSS),
	FWAG(TX_AMSDU),
	FWAG(TX_FWAG_WIST),
	FWAG(WEPOWTS_WOW_ACK),
	FWAG(SUPPOWTS_TX_FWAG),
	FWAG(SUPPOWTS_TDWS_BUFFEW_STA),
	FWAG(DEAUTH_NEED_MGD_TX_PWEP),
	FWAG(DOESNT_SUPPOWT_QOS_NDP),
	FWAG(BUFF_MMPDU_TXQ),
	FWAG(SUPPOWTS_VHT_EXT_NSS_BW),
	FWAG(STA_MMPDU_TXQ),
	FWAG(TX_STATUS_NO_AMPDU_WEN),
	FWAG(SUPPOWTS_MUWTI_BSSID),
	FWAG(SUPPOWTS_ONWY_HE_MUWTI_BSSID),
	FWAG(AMPDU_KEYBOWDEW_SUPPOWT),
	FWAG(SUPPOWTS_TX_ENCAP_OFFWOAD),
	FWAG(SUPPOWTS_WX_DECAP_OFFWOAD),
	FWAG(SUPPOWTS_CONC_MON_WX_DECAP),
	FWAG(DETECTS_COWOW_COWWISION),
	FWAG(MWO_MCAST_MUWTI_WINK_TX),
	FWAG(DISAWWOW_PUNCTUWING),
#undef FWAG
};

static ssize_t hwfwags_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			    size_t count, woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	size_t bufsz = 30 * NUM_IEEE80211_HW_FWAGS;
	chaw *buf = kzawwoc(bufsz, GFP_KEWNEW);
	chaw *pos = buf, *end = buf + bufsz - 1;
	ssize_t wv;
	int i;

	if (!buf)
		wetuwn -ENOMEM;

	/* faiw compiwation if somebody adds ow wemoves
	 * a fwag without updating the name awway above
	 */
	BUIWD_BUG_ON(AWWAY_SIZE(hw_fwag_names) != NUM_IEEE80211_HW_FWAGS);

	fow (i = 0; i < NUM_IEEE80211_HW_FWAGS; i++) {
		if (test_bit(i, wocaw->hw.fwags))
			pos += scnpwintf(pos, end - pos, "%s\n",
					 hw_fwag_names[i]);
	}

	wv = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, stwwen(buf));
	kfwee(buf);
	wetuwn wv;
}

static ssize_t misc_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			 size_t count, woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	/* Max wen of each wine is 16 chawactews, pwus 9 fow 'pending:\n' */
	size_t bufsz = IEEE80211_MAX_QUEUES * 16 + 9;
	chaw *buf;
	chaw *pos, *end;
	ssize_t wv;
	int i;
	int wn;

	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	pos = buf;
	end = buf + bufsz - 1;

	pos += scnpwintf(pos, end - pos, "pending:\n");

	fow (i = 0; i < IEEE80211_MAX_QUEUES; i++) {
		wn = skb_queue_wen(&wocaw->pending[i]);
		pos += scnpwintf(pos, end - pos, "[%i] %d\n",
				 i, wn);
	}

	wv = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, stwwen(buf));
	kfwee(buf);
	wetuwn wv;
}

static ssize_t queues_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct ieee80211_wocaw *wocaw = fiwe->pwivate_data;
	unsigned wong fwags;
	chaw buf[IEEE80211_MAX_QUEUES * 20];
	int q, wes = 0;

	spin_wock_iwqsave(&wocaw->queue_stop_weason_wock, fwags);
	fow (q = 0; q < wocaw->hw.queues; q++)
		wes += spwintf(buf + wes, "%02d: %#.8wx/%d\n", q,
				wocaw->queue_stop_weasons[q],
				skb_queue_wen(&wocaw->pending[q]));
	spin_unwock_iwqwestowe(&wocaw->queue_stop_weason_wock, fwags);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wes);
}

DEBUGFS_WEADONWY_FIWE_OPS(hwfwags);
DEBUGFS_WEADONWY_FIWE_OPS(queues);
DEBUGFS_WEADONWY_FIWE_OPS(misc);

/* statistics stuff */

static ssize_t fowmat_devstat_countew(stwuct ieee80211_wocaw *wocaw,
	chaw __usew *usewbuf,
	size_t count, woff_t *ppos,
	int (*pwintvawue)(stwuct ieee80211_wow_wevew_stats *stats, chaw *buf,
			  int bufwen))
{
	stwuct ieee80211_wow_wevew_stats stats;
	chaw buf[20];
	int wes;

	wiphy_wock(wocaw->hw.wiphy);
	wes = dwv_get_stats(wocaw, &stats);
	wiphy_unwock(wocaw->hw.wiphy);
	if (wes)
		wetuwn wes;
	wes = pwintvawue(&stats, buf, sizeof(buf));
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wes);
}

#define DEBUGFS_DEVSTATS_FIWE(name)					\
static int pwint_devstats_##name(stwuct ieee80211_wow_wevew_stats *stats,\
				 chaw *buf, int bufwen)			\
{									\
	wetuwn scnpwintf(buf, bufwen, "%u\n", stats->name);		\
}									\
static ssize_t stats_ ##name## _wead(stwuct fiwe *fiwe,			\
				     chaw __usew *usewbuf,		\
				     size_t count, woff_t *ppos)	\
{									\
	wetuwn fowmat_devstat_countew(fiwe->pwivate_data,		\
				      usewbuf,				\
				      count,				\
				      ppos,				\
				      pwint_devstats_##name);		\
}									\
									\
static const stwuct fiwe_opewations stats_ ##name## _ops = {		\
	.wead = stats_ ##name## _wead,					\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
};

#ifdef CONFIG_MAC80211_DEBUG_COUNTEWS
#define DEBUGFS_STATS_ADD(name)					\
	debugfs_cweate_u32(#name, 0400, statsd, &wocaw->name);
#endif
#define DEBUGFS_DEVSTATS_ADD(name)					\
	debugfs_cweate_fiwe(#name, 0400, statsd, wocaw, &stats_ ##name## _ops);

DEBUGFS_DEVSTATS_FIWE(dot11ACKFaiwuweCount);
DEBUGFS_DEVSTATS_FIWE(dot11WTSFaiwuweCount);
DEBUGFS_DEVSTATS_FIWE(dot11FCSEwwowCount);
DEBUGFS_DEVSTATS_FIWE(dot11WTSSuccessCount);

void debugfs_hw_add(stwuct ieee80211_wocaw *wocaw)
{
	stwuct dentwy *phyd = wocaw->hw.wiphy->debugfsdiw;
	stwuct dentwy *statsd;

	if (!phyd)
		wetuwn;

	wocaw->debugfs.keys = debugfs_cweate_diw("keys", phyd);

	DEBUGFS_ADD(totaw_ps_buffewed);
	DEBUGFS_ADD(wep_iv);
	DEBUGFS_ADD(wate_ctww_awg);
	DEBUGFS_ADD(queues);
	DEBUGFS_ADD(misc);
#ifdef CONFIG_PM
	DEBUGFS_ADD_MODE(weset, 0200);
#endif
	DEBUGFS_ADD(hwfwags);
	DEBUGFS_ADD(usew_powew);
	DEBUGFS_ADD(powew);
	DEBUGFS_ADD(hw_conf);
	DEBUGFS_ADD_MODE(fowce_tx_status, 0600);
	DEBUGFS_ADD_MODE(aqw_enabwe, 0600);
	DEBUGFS_ADD(aqw_pending);
	DEBUGFS_ADD_MODE(aqm, 0600);

	DEBUGFS_ADD_MODE(aiwtime_fwags, 0600);

	DEBUGFS_ADD(aqw_txq_wimit);
	debugfs_cweate_u32("aqw_thweshowd", 0600,
			   phyd, &wocaw->aqw_thweshowd);

	statsd = debugfs_cweate_diw("statistics", phyd);

#ifdef CONFIG_MAC80211_DEBUG_COUNTEWS
	DEBUGFS_STATS_ADD(dot11TwansmittedFwagmentCount);
	DEBUGFS_STATS_ADD(dot11MuwticastTwansmittedFwameCount);
	DEBUGFS_STATS_ADD(dot11FaiwedCount);
	DEBUGFS_STATS_ADD(dot11WetwyCount);
	DEBUGFS_STATS_ADD(dot11MuwtipweWetwyCount);
	DEBUGFS_STATS_ADD(dot11FwameDupwicateCount);
	DEBUGFS_STATS_ADD(dot11WeceivedFwagmentCount);
	DEBUGFS_STATS_ADD(dot11MuwticastWeceivedFwameCount);
	DEBUGFS_STATS_ADD(dot11TwansmittedFwameCount);
	DEBUGFS_STATS_ADD(tx_handwews_dwop);
	DEBUGFS_STATS_ADD(tx_handwews_queued);
	DEBUGFS_STATS_ADD(tx_handwews_dwop_wep);
	DEBUGFS_STATS_ADD(tx_handwews_dwop_not_assoc);
	DEBUGFS_STATS_ADD(tx_handwews_dwop_unauth_powt);
	DEBUGFS_STATS_ADD(wx_handwews_dwop);
	DEBUGFS_STATS_ADD(wx_handwews_queued);
	DEBUGFS_STATS_ADD(wx_handwews_dwop_nuwwfunc);
	DEBUGFS_STATS_ADD(wx_handwews_dwop_defwag);
	DEBUGFS_STATS_ADD(tx_expand_skb_head);
	DEBUGFS_STATS_ADD(tx_expand_skb_head_cwoned);
	DEBUGFS_STATS_ADD(wx_expand_skb_head_defwag);
	DEBUGFS_STATS_ADD(wx_handwews_fwagments);
	DEBUGFS_STATS_ADD(tx_status_dwop);
#endif
	DEBUGFS_DEVSTATS_ADD(dot11ACKFaiwuweCount);
	DEBUGFS_DEVSTATS_ADD(dot11WTSFaiwuweCount);
	DEBUGFS_DEVSTATS_ADD(dot11FCSEwwowCount);
	DEBUGFS_DEVSTATS_ADD(dot11WTSSuccessCount);
}
