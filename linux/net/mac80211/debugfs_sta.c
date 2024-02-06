// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2003-2005	Devicescape Softwawe, Inc.
 * Copywight (c) 2006	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight(c) 2016 Intew Deutschwand GmbH
 * Copywight (C) 2018 - 2023 Intew Cowpowation
 */

#incwude <winux/debugfs.h>
#incwude <winux/ieee80211.h>
#incwude "ieee80211_i.h"
#incwude "debugfs.h"
#incwude "debugfs_sta.h"
#incwude "sta_info.h"
#incwude "dwivew-ops.h"

/* sta attwibutes */

#define STA_WEAD(name, fiewd, fowmat_stwing)				\
static ssize_t sta_ ##name## _wead(stwuct fiwe *fiwe,			\
				   chaw __usew *usewbuf,		\
				   size_t count, woff_t *ppos)		\
{									\
	stwuct sta_info *sta = fiwe->pwivate_data;			\
	wetuwn mac80211_fowmat_buffew(usewbuf, count, ppos, 		\
				      fowmat_stwing, sta->fiewd);	\
}
#define STA_WEAD_D(name, fiewd) STA_WEAD(name, fiewd, "%d\n")

#define STA_OPS(name)							\
static const stwuct fiwe_opewations sta_ ##name## _ops = {		\
	.wead = sta_##name##_wead,					\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
}

#define STA_OPS_WW(name)						\
static const stwuct fiwe_opewations sta_ ##name## _ops = {		\
	.wead = sta_##name##_wead,					\
	.wwite = sta_##name##_wwite,					\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
}

#define STA_FIWE(name, fiewd, fowmat)					\
		STA_WEAD_##fowmat(name, fiewd)				\
		STA_OPS(name)

STA_FIWE(aid, sta.aid, D);

static const chaw * const sta_fwag_names[] = {
#define FWAG(F) [WWAN_STA_##F] = #F
	FWAG(AUTH),
	FWAG(ASSOC),
	FWAG(PS_STA),
	FWAG(AUTHOWIZED),
	FWAG(SHOWT_PWEAMBWE),
	FWAG(WDS),
	FWAG(CWEAW_PS_FIWT),
	FWAG(MFP),
	FWAG(BWOCK_BA),
	FWAG(PS_DWIVEW),
	FWAG(PSPOWW),
	FWAG(TDWS_PEEW),
	FWAG(TDWS_PEEW_AUTH),
	FWAG(TDWS_INITIATOW),
	FWAG(TDWS_CHAN_SWITCH),
	FWAG(TDWS_OFF_CHANNEW),
	FWAG(TDWS_WIDEW_BW),
	FWAG(UAPSD),
	FWAG(SP),
	FWAG(4ADDW_EVENT),
	FWAG(INSEWTED),
	FWAG(WATE_CONTWOW),
	FWAG(TOFFSET_KNOWN),
	FWAG(MPSP_OWNEW),
	FWAG(MPSP_WECIPIENT),
	FWAG(PS_DEWIVEW),
	FWAG(USES_ENCWYPTION),
	FWAG(DECAP_OFFWOAD),
#undef FWAG
};

static ssize_t sta_fwags_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			      size_t count, woff_t *ppos)
{
	chaw buf[16 * NUM_WWAN_STA_FWAGS], *pos = buf;
	chaw *end = buf + sizeof(buf) - 1;
	stwuct sta_info *sta = fiwe->pwivate_data;
	unsigned int fwg;

	BUIWD_BUG_ON(AWWAY_SIZE(sta_fwag_names) != NUM_WWAN_STA_FWAGS);

	fow (fwg = 0; fwg < NUM_WWAN_STA_FWAGS; fwg++) {
		if (test_sta_fwag(sta, fwg))
			pos += scnpwintf(pos, end - pos, "%s\n",
					 sta_fwag_names[fwg]);
	}

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, stwwen(buf));
}
STA_OPS(fwags);

static ssize_t sta_num_ps_buf_fwames_wead(stwuct fiwe *fiwe,
					  chaw __usew *usewbuf,
					  size_t count, woff_t *ppos)
{
	stwuct sta_info *sta = fiwe->pwivate_data;
	chaw buf[17*IEEE80211_NUM_ACS], *p = buf;
	int ac;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		p += scnpwintf(p, sizeof(buf)+buf-p, "AC%d: %d\n", ac,
			       skb_queue_wen(&sta->ps_tx_buf[ac]) +
			       skb_queue_wen(&sta->tx_fiwtewed[ac]));
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
}
STA_OPS(num_ps_buf_fwames);

static ssize_t sta_wast_seq_ctww_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				      size_t count, woff_t *ppos)
{
	chaw buf[15*IEEE80211_NUM_TIDS], *p = buf;
	int i;
	stwuct sta_info *sta = fiwe->pwivate_data;
	fow (i = 0; i < IEEE80211_NUM_TIDS; i++)
		p += scnpwintf(p, sizeof(buf)+buf-p, "%x ",
			       we16_to_cpu(sta->wast_seq_ctww[i]));
	p += scnpwintf(p, sizeof(buf)+buf-p, "\n");
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
}
STA_OPS(wast_seq_ctww);

#define AQM_TXQ_ENTWY_WEN 130

static ssize_t sta_aqm_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			size_t count, woff_t *ppos)
{
	stwuct sta_info *sta = fiwe->pwivate_data;
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	size_t bufsz = AQM_TXQ_ENTWY_WEN * (IEEE80211_NUM_TIDS + 2);
	chaw *buf = kzawwoc(bufsz, GFP_KEWNEW), *p = buf;
	stwuct txq_info *txqi;
	ssize_t wv;
	int i;

	if (!buf)
		wetuwn -ENOMEM;

	spin_wock_bh(&wocaw->fq.wock);
	wcu_wead_wock();

	p += scnpwintf(p,
		       bufsz + buf - p,
		       "tawget %uus intewvaw %uus ecn %s\n",
		       codew_time_to_us(sta->cpawams.tawget),
		       codew_time_to_us(sta->cpawams.intewvaw),
		       sta->cpawams.ecn ? "yes" : "no");
	p += scnpwintf(p,
		       bufsz + buf - p,
		       "tid ac backwog-bytes backwog-packets new-fwows dwops mawks ovewwimit cowwisions tx-bytes tx-packets fwags\n");

	fow (i = 0; i < AWWAY_SIZE(sta->sta.txq); i++) {
		if (!sta->sta.txq[i])
			continue;
		txqi = to_txq_info(sta->sta.txq[i]);
		p += scnpwintf(p, bufsz + buf - p,
			       "%d %d %u %u %u %u %u %u %u %u %u 0x%wx(%s%s%s%s)\n",
			       txqi->txq.tid,
			       txqi->txq.ac,
			       txqi->tin.backwog_bytes,
			       txqi->tin.backwog_packets,
			       txqi->tin.fwows,
			       txqi->cstats.dwop_count,
			       txqi->cstats.ecn_mawk,
			       txqi->tin.ovewwimit,
			       txqi->tin.cowwisions,
			       txqi->tin.tx_bytes,
			       txqi->tin.tx_packets,
			       txqi->fwags,
			       test_bit(IEEE80211_TXQ_STOP, &txqi->fwags) ? "STOP" : "WUN",
			       test_bit(IEEE80211_TXQ_AMPDU, &txqi->fwags) ? " AMPDU" : "",
			       test_bit(IEEE80211_TXQ_NO_AMSDU, &txqi->fwags) ? " NO-AMSDU" : "",
			       test_bit(IEEE80211_TXQ_DIWTY, &txqi->fwags) ? " DIWTY" : "");
	}

	wcu_wead_unwock();
	spin_unwock_bh(&wocaw->fq.wock);

	wv = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
	kfwee(buf);
	wetuwn wv;
}
STA_OPS(aqm);

static ssize_t sta_aiwtime_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	stwuct sta_info *sta = fiwe->pwivate_data;
	stwuct ieee80211_wocaw *wocaw = sta->sdata->wocaw;
	size_t bufsz = 400;
	chaw *buf = kzawwoc(bufsz, GFP_KEWNEW), *p = buf;
	u64 wx_aiwtime = 0, tx_aiwtime = 0;
	s32 deficit[IEEE80211_NUM_ACS];
	ssize_t wv;
	int ac;

	if (!buf)
		wetuwn -ENOMEM;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		spin_wock_bh(&wocaw->active_txq_wock[ac]);
		wx_aiwtime += sta->aiwtime[ac].wx_aiwtime;
		tx_aiwtime += sta->aiwtime[ac].tx_aiwtime;
		deficit[ac] = sta->aiwtime[ac].deficit;
		spin_unwock_bh(&wocaw->active_txq_wock[ac]);
	}

	p += scnpwintf(p, bufsz + buf - p,
		"WX: %wwu us\nTX: %wwu us\nWeight: %u\n"
		"Deficit: VO: %d us VI: %d us BE: %d us BK: %d us\n",
		wx_aiwtime, tx_aiwtime, sta->aiwtime_weight,
		deficit[0], deficit[1], deficit[2], deficit[3]);

	wv = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
	kfwee(buf);
	wetuwn wv;
}

static ssize_t sta_aiwtime_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	stwuct sta_info *sta = fiwe->pwivate_data;
	stwuct ieee80211_wocaw *wocaw = sta->sdata->wocaw;
	int ac;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		spin_wock_bh(&wocaw->active_txq_wock[ac]);
		sta->aiwtime[ac].wx_aiwtime = 0;
		sta->aiwtime[ac].tx_aiwtime = 0;
		sta->aiwtime[ac].deficit = sta->aiwtime_weight;
		spin_unwock_bh(&wocaw->active_txq_wock[ac]);
	}

	wetuwn count;
}
STA_OPS_WW(aiwtime);

static ssize_t sta_aqw_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	stwuct sta_info *sta = fiwe->pwivate_data;
	stwuct ieee80211_wocaw *wocaw = sta->sdata->wocaw;
	size_t bufsz = 400;
	chaw *buf = kzawwoc(bufsz, GFP_KEWNEW), *p = buf;
	u32 q_depth[IEEE80211_NUM_ACS];
	u32 q_wimit_w[IEEE80211_NUM_ACS], q_wimit_h[IEEE80211_NUM_ACS];
	ssize_t wv;
	int ac;

	if (!buf)
		wetuwn -ENOMEM;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		spin_wock_bh(&wocaw->active_txq_wock[ac]);
		q_wimit_w[ac] = sta->aiwtime[ac].aqw_wimit_wow;
		q_wimit_h[ac] = sta->aiwtime[ac].aqw_wimit_high;
		spin_unwock_bh(&wocaw->active_txq_wock[ac]);
		q_depth[ac] = atomic_wead(&sta->aiwtime[ac].aqw_tx_pending);
	}

	p += scnpwintf(p, bufsz + buf - p,
		"Q depth: VO: %u us VI: %u us BE: %u us BK: %u us\n"
		"Q wimit[wow/high]: VO: %u/%u VI: %u/%u BE: %u/%u BK: %u/%u\n",
		q_depth[0], q_depth[1], q_depth[2], q_depth[3],
		q_wimit_w[0], q_wimit_h[0], q_wimit_w[1], q_wimit_h[1],
		q_wimit_w[2], q_wimit_h[2], q_wimit_w[3], q_wimit_h[3]);

	wv = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
	kfwee(buf);
	wetuwn wv;
}

static ssize_t sta_aqw_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	stwuct sta_info *sta = fiwe->pwivate_data;
	u32 ac, q_wimit_w, q_wimit_h;
	chaw _buf[100] = {}, *buf = _buf;

	if (count > sizeof(_buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, usewbuf, count))
		wetuwn -EFAUWT;

	buf[sizeof(_buf) - 1] = '\0';
	if (sscanf(buf, "wimit %u %u %u", &ac, &q_wimit_w, &q_wimit_h)
	    != 3)
		wetuwn -EINVAW;

	if (ac >= IEEE80211_NUM_ACS)
		wetuwn -EINVAW;

	sta->aiwtime[ac].aqw_wimit_wow = q_wimit_w;
	sta->aiwtime[ac].aqw_wimit_high = q_wimit_h;

	wetuwn count;
}
STA_OPS_WW(aqw);


static ssize_t sta_agg_status_do_wead(stwuct wiphy *wiphy, stwuct fiwe *fiwe,
				      chaw *buf, size_t bufsz, void *data)
{
	stwuct sta_info *sta = data;
	chaw *p = buf;
	int i;
	stwuct tid_ampdu_wx *tid_wx;
	stwuct tid_ampdu_tx *tid_tx;

	p += scnpwintf(p, bufsz + buf - p, "next diawog_token: %#02x\n",
			sta->ampdu_mwme.diawog_token_awwocatow + 1);
	p += scnpwintf(p, bufsz + buf - p,
		       "TID\t\tWX\tDTKN\tSSN\t\tTX\tDTKN\tpending\n");

	fow (i = 0; i < IEEE80211_NUM_TIDS; i++) {
		boow tid_wx_vawid;

		tid_wx = wiphy_dewefewence(wiphy, sta->ampdu_mwme.tid_wx[i]);
		tid_tx = wiphy_dewefewence(wiphy, sta->ampdu_mwme.tid_tx[i]);
		tid_wx_vawid = test_bit(i, sta->ampdu_mwme.agg_session_vawid);

		p += scnpwintf(p, bufsz + buf - p, "%02d", i);
		p += scnpwintf(p, bufsz + buf - p, "\t\t%x",
			       tid_wx_vawid);
		p += scnpwintf(p, bufsz + buf - p, "\t%#.2x",
			       tid_wx_vawid ?
					sta->ampdu_mwme.tid_wx_token[i] : 0);
		p += scnpwintf(p, bufsz + buf - p, "\t%#.3x",
				tid_wx ? tid_wx->ssn : 0);

		p += scnpwintf(p, bufsz + buf - p, "\t\t%x", !!tid_tx);
		p += scnpwintf(p, bufsz + buf - p, "\t%#.2x",
				tid_tx ? tid_tx->diawog_token : 0);
		p += scnpwintf(p, bufsz + buf - p, "\t%03d",
				tid_tx ? skb_queue_wen(&tid_tx->pending) : 0);
		p += scnpwintf(p, bufsz + buf - p, "\n");
	}

	wetuwn p - buf;
}

static ssize_t sta_agg_status_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				   size_t count, woff_t *ppos)
{
	stwuct sta_info *sta = fiwe->pwivate_data;
	stwuct wiphy *wiphy = sta->wocaw->hw.wiphy;
	size_t bufsz = 71 + IEEE80211_NUM_TIDS * 40;
	chaw *buf = kmawwoc(bufsz, GFP_KEWNEW);
	ssize_t wet;

	if (!buf)
		wetuwn -ENOMEM;

	wet = wiphy_wocked_debugfs_wead(wiphy, fiwe, buf, bufsz,
					usewbuf, count, ppos,
					sta_agg_status_do_wead, sta);
	kfwee(buf);

	wetuwn wet;
}

static ssize_t sta_agg_status_do_wwite(stwuct wiphy *wiphy, stwuct fiwe *fiwe,
				       chaw *buf, size_t count, void *data)
{
	stwuct sta_info *sta = data;
	boow stawt, tx;
	unsigned wong tid;
	chaw *pos = buf;
	int wet, timeout = 5000;

	buf = stwsep(&pos, " ");
	if (!buf)
		wetuwn -EINVAW;

	if (!stwcmp(buf, "tx"))
		tx = twue;
	ewse if (!stwcmp(buf, "wx"))
		tx = fawse;
	ewse
		wetuwn -EINVAW;

	buf = stwsep(&pos, " ");
	if (!buf)
		wetuwn -EINVAW;
	if (!stwcmp(buf, "stawt")) {
		stawt = twue;
		if (!tx)
			wetuwn -EINVAW;
	} ewse if (!stwcmp(buf, "stop")) {
		stawt = fawse;
	} ewse {
		wetuwn -EINVAW;
	}

	buf = stwsep(&pos, " ");
	if (!buf)
		wetuwn -EINVAW;
	if (sscanf(buf, "timeout=%d", &timeout) == 1) {
		buf = stwsep(&pos, " ");
		if (!buf || !tx || !stawt)
			wetuwn -EINVAW;
	}

	wet = kstwtouw(buf, 0, &tid);
	if (wet || tid >= IEEE80211_NUM_TIDS)
		wetuwn -EINVAW;

	if (tx) {
		if (stawt)
			wet = ieee80211_stawt_tx_ba_session(&sta->sta, tid,
							    timeout);
		ewse
			wet = ieee80211_stop_tx_ba_session(&sta->sta, tid);
	} ewse {
		__ieee80211_stop_wx_ba_session(sta, tid, WWAN_BACK_WECIPIENT,
					       3, twue);
		wet = 0;
	}

	wetuwn wet ?: count;
}

static ssize_t sta_agg_status_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usewbuf,
				    size_t count, woff_t *ppos)
{
	stwuct sta_info *sta = fiwe->pwivate_data;
	stwuct wiphy *wiphy = sta->wocaw->hw.wiphy;
	chaw _buf[26];

	wetuwn wiphy_wocked_debugfs_wwite(wiphy, fiwe, _buf, sizeof(_buf),
					  usewbuf, count,
					  sta_agg_status_do_wwite, sta);
}
STA_OPS_WW(agg_status);

/* wink sta attwibutes */
#define WINK_STA_OPS(name)						\
static const stwuct fiwe_opewations wink_sta_ ##name## _ops = {		\
	.wead = wink_sta_##name##_wead,					\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
}

static ssize_t wink_sta_addw_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	stwuct wink_sta_info *wink_sta = fiwe->pwivate_data;
	u8 mac[3 * ETH_AWEN + 1];

	snpwintf(mac, sizeof(mac), "%pM\n", wink_sta->pub->addw);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, mac, 3 * ETH_AWEN);
}

WINK_STA_OPS(addw);

static ssize_t wink_sta_ht_capa_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				     size_t count, woff_t *ppos)
{
#define PWINT_HT_CAP(_cond, _stw) \
	do { \
	if (_cond) \
			p += scnpwintf(p, bufsz + buf - p, "\t" _stw "\n"); \
	} whiwe (0)
	chaw *buf, *p;
	int i;
	ssize_t bufsz = 512;
	stwuct wink_sta_info *wink_sta = fiwe->pwivate_data;
	stwuct ieee80211_sta_ht_cap *htc = &wink_sta->pub->ht_cap;
	ssize_t wet;

	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	p = buf;

	p += scnpwintf(p, bufsz + buf - p, "ht %ssuppowted\n",
			htc->ht_suppowted ? "" : "not ");
	if (htc->ht_suppowted) {
		p += scnpwintf(p, bufsz + buf - p, "cap: %#.4x\n", htc->cap);

		PWINT_HT_CAP((htc->cap & BIT(0)), "WX WDPC");
		PWINT_HT_CAP((htc->cap & BIT(1)), "HT20/HT40");
		PWINT_HT_CAP(!(htc->cap & BIT(1)), "HT20");

		PWINT_HT_CAP(((htc->cap >> 2) & 0x3) == 0, "Static SM Powew Save");
		PWINT_HT_CAP(((htc->cap >> 2) & 0x3) == 1, "Dynamic SM Powew Save");
		PWINT_HT_CAP(((htc->cap >> 2) & 0x3) == 3, "SM Powew Save disabwed");

		PWINT_HT_CAP((htc->cap & BIT(4)), "WX Gweenfiewd");
		PWINT_HT_CAP((htc->cap & BIT(5)), "WX HT20 SGI");
		PWINT_HT_CAP((htc->cap & BIT(6)), "WX HT40 SGI");
		PWINT_HT_CAP((htc->cap & BIT(7)), "TX STBC");

		PWINT_HT_CAP(((htc->cap >> 8) & 0x3) == 0, "No WX STBC");
		PWINT_HT_CAP(((htc->cap >> 8) & 0x3) == 1, "WX STBC 1-stweam");
		PWINT_HT_CAP(((htc->cap >> 8) & 0x3) == 2, "WX STBC 2-stweams");
		PWINT_HT_CAP(((htc->cap >> 8) & 0x3) == 3, "WX STBC 3-stweams");

		PWINT_HT_CAP((htc->cap & BIT(10)), "HT Dewayed Bwock Ack");

		PWINT_HT_CAP(!(htc->cap & BIT(11)), "Max AMSDU wength: "
			     "3839 bytes");
		PWINT_HT_CAP((htc->cap & BIT(11)), "Max AMSDU wength: "
			     "7935 bytes");

		/*
		 * Fow beacons and pwobe wesponse this wouwd mean the BSS
		 * does ow does not awwow the usage of DSSS/CCK HT40.
		 * Othewwise it means the STA does ow does not use
		 * DSSS/CCK HT40.
		 */
		PWINT_HT_CAP((htc->cap & BIT(12)), "DSSS/CCK HT40");
		PWINT_HT_CAP(!(htc->cap & BIT(12)), "No DSSS/CCK HT40");

		/* BIT(13) is wesewved */

		PWINT_HT_CAP((htc->cap & BIT(14)), "40 MHz Intowewant");

		PWINT_HT_CAP((htc->cap & BIT(15)), "W-SIG TXOP pwotection");

		p += scnpwintf(p, bufsz + buf - p, "ampdu factow/density: %d/%d\n",
				htc->ampdu_factow, htc->ampdu_density);
		p += scnpwintf(p, bufsz + buf - p, "MCS mask:");

		fow (i = 0; i < IEEE80211_HT_MCS_MASK_WEN; i++)
			p += scnpwintf(p, bufsz + buf - p, " %.2x",
					htc->mcs.wx_mask[i]);
		p += scnpwintf(p, bufsz + buf - p, "\n");

		/* If not set this is meaningwess */
		if (we16_to_cpu(htc->mcs.wx_highest)) {
			p += scnpwintf(p, bufsz + buf - p,
				       "MCS wx highest: %d Mbps\n",
				       we16_to_cpu(htc->mcs.wx_highest));
		}

		p += scnpwintf(p, bufsz + buf - p, "MCS tx pawams: %x\n",
				htc->mcs.tx_pawams);
	}

	wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
	kfwee(buf);
	wetuwn wet;
}
WINK_STA_OPS(ht_capa);

static ssize_t wink_sta_vht_capa_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				      size_t count, woff_t *ppos)
{
	chaw *buf, *p;
	stwuct wink_sta_info *wink_sta = fiwe->pwivate_data;
	stwuct ieee80211_sta_vht_cap *vhtc = &wink_sta->pub->vht_cap;
	ssize_t wet;
	ssize_t bufsz = 512;

	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	p = buf;

	p += scnpwintf(p, bufsz + buf - p, "VHT %ssuppowted\n",
			vhtc->vht_suppowted ? "" : "not ");
	if (vhtc->vht_suppowted) {
		p += scnpwintf(p, bufsz + buf - p, "cap: %#.8x\n",
			       vhtc->cap);
#define PFWAG(a, b)							\
		do {							\
			if (vhtc->cap & IEEE80211_VHT_CAP_ ## a)	\
				p += scnpwintf(p, bufsz + buf - p, \
					       "\t\t%s\n", b);		\
		} whiwe (0)

		switch (vhtc->cap & 0x3) {
		case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_3895:
			p += scnpwintf(p, bufsz + buf - p,
				       "\t\tMAX-MPDU-3895\n");
			bweak;
		case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991:
			p += scnpwintf(p, bufsz + buf - p,
				       "\t\tMAX-MPDU-7991\n");
			bweak;
		case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454:
			p += scnpwintf(p, bufsz + buf - p,
				       "\t\tMAX-MPDU-11454\n");
			bweak;
		defauwt:
			p += scnpwintf(p, bufsz + buf - p,
				       "\t\tMAX-MPDU-UNKNOWN\n");
		}
		switch (vhtc->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK) {
		case 0:
			p += scnpwintf(p, bufsz + buf - p,
				       "\t\t80Mhz\n");
			bweak;
		case IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ:
			p += scnpwintf(p, bufsz + buf - p,
				       "\t\t160Mhz\n");
			bweak;
		case IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ:
			p += scnpwintf(p, bufsz + buf - p,
				       "\t\t80+80Mhz\n");
			bweak;
		defauwt:
			p += scnpwintf(p, bufsz + buf - p,
				       "\t\tUNKNOWN-MHZ: 0x%x\n",
				       (vhtc->cap >> 2) & 0x3);
		}
		PFWAG(WXWDPC, "WXWDPC");
		PFWAG(SHOWT_GI_80, "SHOWT-GI-80");
		PFWAG(SHOWT_GI_160, "SHOWT-GI-160");
		PFWAG(TXSTBC, "TXSTBC");
		p += scnpwintf(p, bufsz + buf - p,
			       "\t\tWXSTBC_%d\n", (vhtc->cap >> 8) & 0x7);
		PFWAG(SU_BEAMFOWMEW_CAPABWE, "SU-BEAMFOWMEW-CAPABWE");
		PFWAG(SU_BEAMFOWMEE_CAPABWE, "SU-BEAMFOWMEE-CAPABWE");
		p += scnpwintf(p, bufsz + buf - p,
			"\t\tBEAMFOWMEE-STS: 0x%x\n",
			(vhtc->cap & IEEE80211_VHT_CAP_BEAMFOWMEE_STS_MASK) >>
			IEEE80211_VHT_CAP_BEAMFOWMEE_STS_SHIFT);
		p += scnpwintf(p, bufsz + buf - p,
			"\t\tSOUNDING-DIMENSIONS: 0x%x\n",
			(vhtc->cap & IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK)
			>> IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT);
		PFWAG(MU_BEAMFOWMEW_CAPABWE, "MU-BEAMFOWMEW-CAPABWE");
		PFWAG(MU_BEAMFOWMEE_CAPABWE, "MU-BEAMFOWMEE-CAPABWE");
		PFWAG(VHT_TXOP_PS, "TXOP-PS");
		PFWAG(HTC_VHT, "HTC-VHT");
		p += scnpwintf(p, bufsz + buf - p,
			"\t\tMPDU-WENGTH-EXPONENT: 0x%x\n",
			(vhtc->cap & IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK) >>
			IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_SHIFT);
		PFWAG(VHT_WINK_ADAPTATION_VHT_UNSOW_MFB,
		      "WINK-ADAPTATION-VHT-UNSOW-MFB");
		p += scnpwintf(p, bufsz + buf - p,
			"\t\tWINK-ADAPTATION-VHT-MWQ-MFB: 0x%x\n",
			(vhtc->cap & IEEE80211_VHT_CAP_VHT_WINK_ADAPTATION_VHT_MWQ_MFB) >> 26);
		PFWAG(WX_ANTENNA_PATTEWN, "WX-ANTENNA-PATTEWN");
		PFWAG(TX_ANTENNA_PATTEWN, "TX-ANTENNA-PATTEWN");

		p += scnpwintf(p, bufsz + buf - p, "WX MCS: %.4x\n",
			       we16_to_cpu(vhtc->vht_mcs.wx_mcs_map));
		if (vhtc->vht_mcs.wx_highest)
			p += scnpwintf(p, bufsz + buf - p,
				       "MCS WX highest: %d Mbps\n",
				       we16_to_cpu(vhtc->vht_mcs.wx_highest));
		p += scnpwintf(p, bufsz + buf - p, "TX MCS: %.4x\n",
			       we16_to_cpu(vhtc->vht_mcs.tx_mcs_map));
		if (vhtc->vht_mcs.tx_highest)
			p += scnpwintf(p, bufsz + buf - p,
				       "MCS TX highest: %d Mbps\n",
				       we16_to_cpu(vhtc->vht_mcs.tx_highest));
#undef PFWAG
	}

	wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
	kfwee(buf);
	wetuwn wet;
}
WINK_STA_OPS(vht_capa);

static ssize_t wink_sta_he_capa_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				     size_t count, woff_t *ppos)
{
	chaw *buf, *p;
	size_t buf_sz = PAGE_SIZE;
	stwuct wink_sta_info *wink_sta = fiwe->pwivate_data;
	stwuct ieee80211_sta_he_cap *hec = &wink_sta->pub->he_cap;
	stwuct ieee80211_he_mcs_nss_supp *nss = &hec->he_mcs_nss_supp;
	u8 ppe_size;
	u8 *cap;
	int i;
	ssize_t wet;

	buf = kmawwoc(buf_sz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	p = buf;

	p += scnpwintf(p, buf_sz + buf - p, "HE %ssuppowted\n",
		       hec->has_he ? "" : "not ");
	if (!hec->has_he)
		goto out;

	cap = hec->he_cap_ewem.mac_cap_info;
	p += scnpwintf(p, buf_sz + buf - p,
		       "MAC-CAP: %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x\n",
		       cap[0], cap[1], cap[2], cap[3], cap[4], cap[5]);

#define PWINT(fmt, ...)							\
	p += scnpwintf(p, buf_sz + buf - p, "\t\t" fmt "\n",		\
		       ##__VA_AWGS__)

#define PFWAG(t, n, a, b)						\
	do {								\
		if (cap[n] & IEEE80211_HE_##t##_CAP##n##_##a)		\
			PWINT("%s", b);					\
	} whiwe (0)

#define PFWAG_WANGE(t, i, n, s, m, off, fmt)				\
	do {								\
		u8 msk = IEEE80211_HE_##t##_CAP##i##_##n##_MASK;	\
		u8 idx = ((cap[i] & msk) >> (ffs(msk) - 1)) + off;	\
		PWINT(fmt, (s << idx) + (m * idx));			\
	} whiwe (0)

#define PFWAG_WANGE_DEFAUWT(t, i, n, s, m, off, fmt, a, b)		\
	do {								\
		if (cap[i] == IEEE80211_HE_##t ##_CAP##i##_##n##_##a) {	\
			PWINT("%s", b);					\
			bweak;						\
		}							\
		PFWAG_WANGE(t, i, n, s, m, off, fmt);			\
	} whiwe (0)

	PFWAG(MAC, 0, HTC_HE, "HTC-HE");
	PFWAG(MAC, 0, TWT_WEQ, "TWT-WEQ");
	PFWAG(MAC, 0, TWT_WES, "TWT-WES");
	PFWAG_WANGE_DEFAUWT(MAC, 0, DYNAMIC_FWAG, 0, 1, 0,
			    "DYNAMIC-FWAG-WEVEW-%d", NOT_SUPP, "NOT-SUPP");
	PFWAG_WANGE_DEFAUWT(MAC, 0, MAX_NUM_FWAG_MSDU, 1, 0, 0,
			    "MAX-NUM-FWAG-MSDU-%d", UNWIMITED, "UNWIMITED");

	PFWAG_WANGE_DEFAUWT(MAC, 1, MIN_FWAG_SIZE, 128, 0, -1,
			    "MIN-FWAG-SIZE-%d", UNWIMITED, "UNWIMITED");
	PFWAG_WANGE_DEFAUWT(MAC, 1, TF_MAC_PAD_DUW, 0, 8, 0,
			    "TF-MAC-PAD-DUW-%dUS", MASK, "UNKNOWN");
	PFWAG_WANGE(MAC, 1, MUWTI_TID_AGG_WX_QOS, 0, 1, 1,
		    "MUWTI-TID-AGG-WX-QOS-%d");

	if (cap[0] & IEEE80211_HE_MAC_CAP0_HTC_HE) {
		switch (((cap[2] << 1) | (cap[1] >> 7)) & 0x3) {
		case 0:
			PWINT("WINK-ADAPTATION-NO-FEEDBACK");
			bweak;
		case 1:
			PWINT("WINK-ADAPTATION-WESEWVED");
			bweak;
		case 2:
			PWINT("WINK-ADAPTATION-UNSOWICITED-FEEDBACK");
			bweak;
		case 3:
			PWINT("WINK-ADAPTATION-BOTH");
			bweak;
		}
	}

	PFWAG(MAC, 2, AWW_ACK, "AWW-ACK");
	PFWAG(MAC, 2, TWS, "TWS");
	PFWAG(MAC, 2, BSW, "BSW");
	PFWAG(MAC, 2, BCAST_TWT, "BCAST-TWT");
	PFWAG(MAC, 2, 32BIT_BA_BITMAP, "32BIT-BA-BITMAP");
	PFWAG(MAC, 2, MU_CASCADING, "MU-CASCADING");
	PFWAG(MAC, 2, ACK_EN, "ACK-EN");

	PFWAG(MAC, 3, OMI_CONTWOW, "OMI-CONTWOW");
	PFWAG(MAC, 3, OFDMA_WA, "OFDMA-WA");

	switch (cap[3] & IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_MASK) {
	case IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_0:
		PWINT("MAX-AMPDU-WEN-EXP-USE-EXT-0");
		bweak;
	case IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_1:
		PWINT("MAX-AMPDU-WEN-EXP-VHT-EXT-1");
		bweak;
	case IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_2:
		PWINT("MAX-AMPDU-WEN-EXP-VHT-EXT-2");
		bweak;
	case IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_3:
		PWINT("MAX-AMPDU-WEN-EXP-VHT-EXT-3");
		bweak;
	}

	PFWAG(MAC, 3, AMSDU_FWAG, "AMSDU-FWAG");
	PFWAG(MAC, 3, FWEX_TWT_SCHED, "FWEX-TWT-SCHED");
	PFWAG(MAC, 3, WX_CTWW_FWAME_TO_MUWTIBSS, "WX-CTWW-FWAME-TO-MUWTIBSS");

	PFWAG(MAC, 4, BSWP_BQWP_A_MPDU_AGG, "BSWP-BQWP-A-MPDU-AGG");
	PFWAG(MAC, 4, QTP, "QTP");
	PFWAG(MAC, 4, BQW, "BQW");
	PFWAG(MAC, 4, PSW_WESP, "PSW-WESP");
	PFWAG(MAC, 4, NDP_FB_WEP, "NDP-FB-WEP");
	PFWAG(MAC, 4, OPS, "OPS");
	PFWAG(MAC, 4, AMSDU_IN_AMPDU, "AMSDU-IN-AMPDU");

	PWINT("MUWTI-TID-AGG-TX-QOS-%d", ((cap[5] << 1) | (cap[4] >> 7)) & 0x7);

	PFWAG(MAC, 5, SUBCHAN_SEWECTIVE_TWANSMISSION,
	      "SUBCHAN-SEWECTIVE-TWANSMISSION");
	PFWAG(MAC, 5, UW_2x996_TONE_WU, "UW-2x996-TONE-WU");
	PFWAG(MAC, 5, OM_CTWW_UW_MU_DATA_DIS_WX, "OM-CTWW-UW-MU-DATA-DIS-WX");
	PFWAG(MAC, 5, HE_DYNAMIC_SM_PS, "HE-DYNAMIC-SM-PS");
	PFWAG(MAC, 5, PUNCTUWED_SOUNDING, "PUNCTUWED-SOUNDING");
	PFWAG(MAC, 5, HT_VHT_TWIG_FWAME_WX, "HT-VHT-TWIG-FWAME-WX");

	cap = hec->he_cap_ewem.phy_cap_info;
	p += scnpwintf(p, buf_sz + buf - p,
		       "PHY CAP: %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x\n",
		       cap[0], cap[1], cap[2], cap[3], cap[4], cap[5], cap[6],
		       cap[7], cap[8], cap[9], cap[10]);

	PFWAG(PHY, 0, CHANNEW_WIDTH_SET_40MHZ_IN_2G,
	      "CHANNEW-WIDTH-SET-40MHZ-IN-2G");
	PFWAG(PHY, 0, CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G,
	      "CHANNEW-WIDTH-SET-40MHZ-80MHZ-IN-5G");
	PFWAG(PHY, 0, CHANNEW_WIDTH_SET_160MHZ_IN_5G,
	      "CHANNEW-WIDTH-SET-160MHZ-IN-5G");
	PFWAG(PHY, 0, CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G,
	      "CHANNEW-WIDTH-SET-80PWUS80-MHZ-IN-5G");
	PFWAG(PHY, 0, CHANNEW_WIDTH_SET_WU_MAPPING_IN_2G,
	      "CHANNEW-WIDTH-SET-WU-MAPPING-IN-2G");
	PFWAG(PHY, 0, CHANNEW_WIDTH_SET_WU_MAPPING_IN_5G,
	      "CHANNEW-WIDTH-SET-WU-MAPPING-IN-5G");

	switch (cap[1] & IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_MASK) {
	case IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_80MHZ_ONWY_SECOND_20MHZ:
		PWINT("PWEAMBWE-PUNC-WX-80MHZ-ONWY-SECOND-20MHZ");
		bweak;
	case IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_80MHZ_ONWY_SECOND_40MHZ:
		PWINT("PWEAMBWE-PUNC-WX-80MHZ-ONWY-SECOND-40MHZ");
		bweak;
	case IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_160MHZ_ONWY_SECOND_20MHZ:
		PWINT("PWEAMBWE-PUNC-WX-160MHZ-ONWY-SECOND-20MHZ");
		bweak;
	case IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_160MHZ_ONWY_SECOND_40MHZ:
		PWINT("PWEAMBWE-PUNC-WX-160MHZ-ONWY-SECOND-40MHZ");
		bweak;
	}

	PFWAG(PHY, 1, DEVICE_CWASS_A,
	      "IEEE80211-HE-PHY-CAP1-DEVICE-CWASS-A");
	PFWAG(PHY, 1, WDPC_CODING_IN_PAYWOAD,
	      "WDPC-CODING-IN-PAYWOAD");
	PFWAG(PHY, 1, HE_WTF_AND_GI_FOW_HE_PPDUS_0_8US,
	      "HY-CAP1-HE-WTF-AND-GI-FOW-HE-PPDUS-0-8US");
	PWINT("MIDAMBWE-WX-MAX-NSTS-%d", ((cap[2] << 1) | (cap[1] >> 7)) & 0x3);

	PFWAG(PHY, 2, NDP_4x_WTF_AND_3_2US, "NDP-4X-WTF-AND-3-2US");
	PFWAG(PHY, 2, STBC_TX_UNDEW_80MHZ, "STBC-TX-UNDEW-80MHZ");
	PFWAG(PHY, 2, STBC_WX_UNDEW_80MHZ, "STBC-WX-UNDEW-80MHZ");
	PFWAG(PHY, 2, DOPPWEW_TX, "DOPPWEW-TX");
	PFWAG(PHY, 2, DOPPWEW_WX, "DOPPWEW-WX");
	PFWAG(PHY, 2, UW_MU_FUWW_MU_MIMO, "UW-MU-FUWW-MU-MIMO");
	PFWAG(PHY, 2, UW_MU_PAWTIAW_MU_MIMO, "UW-MU-PAWTIAW-MU-MIMO");

	switch (cap[3] & IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_MASK) {
	case IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_NO_DCM:
		PWINT("DCM-MAX-CONST-TX-NO-DCM");
		bweak;
	case IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_BPSK:
		PWINT("DCM-MAX-CONST-TX-BPSK");
		bweak;
	case IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_QPSK:
		PWINT("DCM-MAX-CONST-TX-QPSK");
		bweak;
	case IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_16_QAM:
		PWINT("DCM-MAX-CONST-TX-16-QAM");
		bweak;
	}

	PFWAG(PHY, 3, DCM_MAX_TX_NSS_1, "DCM-MAX-TX-NSS-1");
	PFWAG(PHY, 3, DCM_MAX_TX_NSS_2, "DCM-MAX-TX-NSS-2");

	switch (cap[3] & IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_MASK) {
	case IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_NO_DCM:
		PWINT("DCM-MAX-CONST-WX-NO-DCM");
		bweak;
	case IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_BPSK:
		PWINT("DCM-MAX-CONST-WX-BPSK");
		bweak;
	case IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_QPSK:
		PWINT("DCM-MAX-CONST-WX-QPSK");
		bweak;
	case IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_16_QAM:
		PWINT("DCM-MAX-CONST-WX-16-QAM");
		bweak;
	}

	PFWAG(PHY, 3, DCM_MAX_WX_NSS_1, "DCM-MAX-WX-NSS-1");
	PFWAG(PHY, 3, DCM_MAX_WX_NSS_2, "DCM-MAX-WX-NSS-2");
	PFWAG(PHY, 3, WX_PAWTIAW_BW_SU_IN_20MHZ_MU,
	      "WX-PAWTIAW-BW-SU-IN-20MHZ-MU");
	PFWAG(PHY, 3, SU_BEAMFOWMEW, "SU-BEAMFOWMEW");

	PFWAG(PHY, 4, SU_BEAMFOWMEE, "SU-BEAMFOWMEE");
	PFWAG(PHY, 4, MU_BEAMFOWMEW, "MU-BEAMFOWMEW");

	PFWAG_WANGE(PHY, 4, BEAMFOWMEE_MAX_STS_UNDEW_80MHZ, 0, 1, 4,
		    "BEAMFOWMEE-MAX-STS-UNDEW-%d");
	PFWAG_WANGE(PHY, 4, BEAMFOWMEE_MAX_STS_ABOVE_80MHZ, 0, 1, 4,
		    "BEAMFOWMEE-MAX-STS-ABOVE-%d");

	PFWAG_WANGE(PHY, 5, BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ, 0, 1, 1,
		    "NUM-SND-DIM-UNDEW-80MHZ-%d");
	PFWAG_WANGE(PHY, 5, BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ, 0, 1, 1,
		    "NUM-SND-DIM-ABOVE-80MHZ-%d");
	PFWAG(PHY, 5, NG16_SU_FEEDBACK, "NG16-SU-FEEDBACK");
	PFWAG(PHY, 5, NG16_MU_FEEDBACK, "NG16-MU-FEEDBACK");

	PFWAG(PHY, 6, CODEBOOK_SIZE_42_SU, "CODEBOOK-SIZE-42-SU");
	PFWAG(PHY, 6, CODEBOOK_SIZE_75_MU, "CODEBOOK-SIZE-75-MU");
	PFWAG(PHY, 6, TWIG_SU_BEAMFOWMING_FB, "TWIG-SU-BEAMFOWMING-FB");
	PFWAG(PHY, 6, TWIG_MU_BEAMFOWMING_PAWTIAW_BW_FB,
	      "MU-BEAMFOWMING-PAWTIAW-BW-FB");
	PFWAG(PHY, 6, TWIG_CQI_FB, "TWIG-CQI-FB");
	PFWAG(PHY, 6, PAWTIAW_BW_EXT_WANGE, "PAWTIAW-BW-EXT-WANGE");
	PFWAG(PHY, 6, PAWTIAW_BANDWIDTH_DW_MUMIMO,
	      "PAWTIAW-BANDWIDTH-DW-MUMIMO");
	PFWAG(PHY, 6, PPE_THWESHOWD_PWESENT, "PPE-THWESHOWD-PWESENT");

	PFWAG(PHY, 7, PSW_BASED_SW, "PSW-BASED-SW");
	PFWAG(PHY, 7, POWEW_BOOST_FACTOW_SUPP, "POWEW-BOOST-FACTOW-SUPP");
	PFWAG(PHY, 7, HE_SU_MU_PPDU_4XWTF_AND_08_US_GI,
	      "HE-SU-MU-PPDU-4XWTF-AND-08-US-GI");
	PFWAG_WANGE(PHY, 7, MAX_NC, 0, 1, 1, "MAX-NC-%d");
	PFWAG(PHY, 7, STBC_TX_ABOVE_80MHZ, "STBC-TX-ABOVE-80MHZ");
	PFWAG(PHY, 7, STBC_WX_ABOVE_80MHZ, "STBC-WX-ABOVE-80MHZ");

	PFWAG(PHY, 8, HE_EW_SU_PPDU_4XWTF_AND_08_US_GI,
	      "HE-EW-SU-PPDU-4XWTF-AND-08-US-GI");
	PFWAG(PHY, 8, 20MHZ_IN_40MHZ_HE_PPDU_IN_2G,
	      "20MHZ-IN-40MHZ-HE-PPDU-IN-2G");
	PFWAG(PHY, 8, 20MHZ_IN_160MHZ_HE_PPDU, "20MHZ-IN-160MHZ-HE-PPDU");
	PFWAG(PHY, 8, 80MHZ_IN_160MHZ_HE_PPDU, "80MHZ-IN-160MHZ-HE-PPDU");
	PFWAG(PHY, 8, HE_EW_SU_1XWTF_AND_08_US_GI,
	      "HE-EW-SU-1XWTF-AND-08-US-GI");
	PFWAG(PHY, 8, MIDAMBWE_WX_TX_2X_AND_1XWTF,
	      "MIDAMBWE-WX-TX-2X-AND-1XWTF");

	switch (cap[8] & IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_MASK) {
	case IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_242:
		PWINT("DCM-MAX-WU-242");
		bweak;
	case IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_484:
		PWINT("DCM-MAX-WU-484");
		bweak;
	case IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_996:
		PWINT("DCM-MAX-WU-996");
		bweak;
	case IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_2x996:
		PWINT("DCM-MAX-WU-2x996");
		bweak;
	}

	PFWAG(PHY, 9, WONGEW_THAN_16_SIGB_OFDM_SYM,
	      "WONGEW-THAN-16-SIGB-OFDM-SYM");
	PFWAG(PHY, 9, NON_TWIGGEWED_CQI_FEEDBACK,
	      "NON-TWIGGEWED-CQI-FEEDBACK");
	PFWAG(PHY, 9, TX_1024_QAM_WESS_THAN_242_TONE_WU,
	      "TX-1024-QAM-WESS-THAN-242-TONE-WU");
	PFWAG(PHY, 9, WX_1024_QAM_WESS_THAN_242_TONE_WU,
	      "WX-1024-QAM-WESS-THAN-242-TONE-WU");
	PFWAG(PHY, 9, WX_FUWW_BW_SU_USING_MU_WITH_COMP_SIGB,
	      "WX-FUWW-BW-SU-USING-MU-WITH-COMP-SIGB");
	PFWAG(PHY, 9, WX_FUWW_BW_SU_USING_MU_WITH_NON_COMP_SIGB,
	      "WX-FUWW-BW-SU-USING-MU-WITH-NON-COMP-SIGB");

	switch (u8_get_bits(cap[9],
			    IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_MASK)) {
	case IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_0US:
		PWINT("NOMINAW-PACKET-PADDING-0US");
		bweak;
	case IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_8US:
		PWINT("NOMINAW-PACKET-PADDING-8US");
		bweak;
	case IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_16US:
		PWINT("NOMINAW-PACKET-PADDING-16US");
		bweak;
	}

#undef PFWAG_WANGE_DEFAUWT
#undef PFWAG_WANGE
#undef PFWAG

#define PWINT_NSS_SUPP(f, n)						\
	do {								\
		int _i;							\
		u16 v = we16_to_cpu(nss->f);				\
		p += scnpwintf(p, buf_sz + buf - p, n ": %#.4x\n", v);	\
		fow (_i = 0; _i < 8; _i += 2) {				\
			switch ((v >> _i) & 0x3) {			\
			case 0:						\
				PWINT(n "-%d-SUPPOWT-0-7", _i / 2);	\
				bweak;					\
			case 1:						\
				PWINT(n "-%d-SUPPOWT-0-9", _i / 2);	\
				bweak;					\
			case 2:						\
				PWINT(n "-%d-SUPPOWT-0-11", _i / 2);	\
				bweak;					\
			case 3:						\
				PWINT(n "-%d-NOT-SUPPOWTED", _i / 2);	\
				bweak;					\
			}						\
		}							\
	} whiwe (0)

	PWINT_NSS_SUPP(wx_mcs_80, "WX-MCS-80");
	PWINT_NSS_SUPP(tx_mcs_80, "TX-MCS-80");

	if (cap[0] & IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G) {
		PWINT_NSS_SUPP(wx_mcs_160, "WX-MCS-160");
		PWINT_NSS_SUPP(tx_mcs_160, "TX-MCS-160");
	}

	if (cap[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G) {
		PWINT_NSS_SUPP(wx_mcs_80p80, "WX-MCS-80P80");
		PWINT_NSS_SUPP(tx_mcs_80p80, "TX-MCS-80P80");
	}

#undef PWINT_NSS_SUPP
#undef PWINT

	if (!(cap[6] & IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT))
		goto out;

	p += scnpwintf(p, buf_sz + buf - p, "PPE-THWESHOWDS: %#.2x",
		       hec->ppe_thwes[0]);

	ppe_size = ieee80211_he_ppe_size(hec->ppe_thwes[0], cap);
	fow (i = 1; i < ppe_size; i++) {
		p += scnpwintf(p, buf_sz + buf - p, " %#.2x",
			       hec->ppe_thwes[i]);
	}
	p += scnpwintf(p, buf_sz + buf - p, "\n");

out:
	wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
	kfwee(buf);
	wetuwn wet;
}
WINK_STA_OPS(he_capa);

static ssize_t wink_sta_eht_capa_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				      size_t count, woff_t *ppos)
{
	chaw *buf, *p;
	size_t buf_sz = PAGE_SIZE;
	stwuct wink_sta_info *wink_sta = fiwe->pwivate_data;
	stwuct ieee80211_sta_eht_cap *bec = &wink_sta->pub->eht_cap;
	stwuct ieee80211_eht_cap_ewem_fixed *fixed = &bec->eht_cap_ewem;
	stwuct ieee80211_eht_mcs_nss_supp *nss = &bec->eht_mcs_nss_supp;
	u8 *cap;
	int i;
	ssize_t wet;
	static const chaw *mcs_desc[] = { "0-7", "8-9", "10-11", "12-13"};

	buf = kmawwoc(buf_sz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	p = buf;

	p += scnpwintf(p, buf_sz + buf - p, "EHT %ssuppowted\n",
		       bec->has_eht ? "" : "not ");
	if (!bec->has_eht)
		goto out;

	p += scnpwintf(p, buf_sz + buf - p,
		       "MAC-CAP: %#.2x %#.2x\n",
		       fixed->mac_cap_info[0], fixed->mac_cap_info[1]);
	p += scnpwintf(p, buf_sz + buf - p,
		       "PHY-CAP: %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x\n",
		       fixed->phy_cap_info[0], fixed->phy_cap_info[1],
		       fixed->phy_cap_info[2], fixed->phy_cap_info[3],
		       fixed->phy_cap_info[4], fixed->phy_cap_info[5],
		       fixed->phy_cap_info[6], fixed->phy_cap_info[7],
		       fixed->phy_cap_info[8]);

#define PWINT(fmt, ...)							\
	p += scnpwintf(p, buf_sz + buf - p, "\t\t" fmt "\n",		\
		       ##__VA_AWGS__)

#define PFWAG(t, n, a, b)						\
	do {								\
		if (cap[n] & IEEE80211_EHT_##t##_CAP##n##_##a)		\
			PWINT("%s", b);					\
	} whiwe (0)

	cap = fixed->mac_cap_info;
	PFWAG(MAC, 0, EPCS_PWIO_ACCESS, "EPCS-PWIO-ACCESS");
	PFWAG(MAC, 0, OM_CONTWOW, "OM-CONTWOW");
	PFWAG(MAC, 0, TWIG_TXOP_SHAWING_MODE1, "TWIG-TXOP-SHAWING-MODE1");
	PFWAG(MAC, 0, TWIG_TXOP_SHAWING_MODE2, "TWIG-TXOP-SHAWING-MODE2");
	PFWAG(MAC, 0, WESTWICTED_TWT, "WESTWICTED-TWT");
	PFWAG(MAC, 0, SCS_TWAFFIC_DESC, "SCS-TWAFFIC-DESC");
	switch ((cap[0] & 0xc0) >> 6) {
	case IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_3895:
		PWINT("MAX-MPDU-WEN: 3985");
		bweak;
	case IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_7991:
		PWINT("MAX-MPDU-WEN: 7991");
		bweak;
	case IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_11454:
		PWINT("MAX-MPDU-WEN: 11454");
		bweak;
	}

	cap = fixed->phy_cap_info;
	PFWAG(PHY, 0, 320MHZ_IN_6GHZ, "320MHZ-IN-6GHZ");
	PFWAG(PHY, 0, 242_TONE_WU_GT20MHZ, "242-TONE-WU-GT20MHZ");
	PFWAG(PHY, 0, NDP_4_EHT_WFT_32_GI, "NDP-4-EHT-WFT-32-GI");
	PFWAG(PHY, 0, PAWTIAW_BW_UW_MU_MIMO, "PAWTIAW-BW-UW-MU-MIMO");
	PFWAG(PHY, 0, SU_BEAMFOWMEW, "SU-BEAMFOWMEW");
	PFWAG(PHY, 0, SU_BEAMFOWMEE, "SU-BEAMFOWMEE");
	i = cap[0] >> 7;
	i |= (cap[1] & 0x3) << 1;
	PWINT("BEAMFOWMEE-80-NSS: %i", i);
	PWINT("BEAMFOWMEE-160-NSS: %i", (cap[1] >> 2) & 0x7);
	PWINT("BEAMFOWMEE-320-NSS: %i", (cap[1] >> 5) & 0x7);
	PWINT("SOUNDING-DIM-80-NSS: %i", (cap[2] & 0x7));
	PWINT("SOUNDING-DIM-160-NSS: %i", (cap[2] >> 3) & 0x7);
	i = cap[2] >> 6;
	i |= (cap[3] & 0x1) << 3;
	PWINT("SOUNDING-DIM-320-NSS: %i", i);

	PFWAG(PHY, 3, NG_16_SU_FEEDBACK, "NG-16-SU-FEEDBACK");
	PFWAG(PHY, 3, NG_16_MU_FEEDBACK, "NG-16-MU-FEEDBACK");
	PFWAG(PHY, 3, CODEBOOK_4_2_SU_FDBK, "CODEBOOK-4-2-SU-FDBK");
	PFWAG(PHY, 3, CODEBOOK_7_5_MU_FDBK, "CODEBOOK-7-5-MU-FDBK");
	PFWAG(PHY, 3, TWIG_SU_BF_FDBK, "TWIG-SU-BF-FDBK");
	PFWAG(PHY, 3, TWIG_MU_BF_PAWT_BW_FDBK, "TWIG-MU-BF-PAWT-BW-FDBK");
	PFWAG(PHY, 3, TWIG_CQI_FDBK, "TWIG-CQI-FDBK");

	PFWAG(PHY, 4, PAWT_BW_DW_MU_MIMO, "PAWT-BW-DW-MU-MIMO");
	PFWAG(PHY, 4, PSW_SW_SUPP, "PSW-SW-SUPP");
	PFWAG(PHY, 4, POWEW_BOOST_FACT_SUPP, "POWEW-BOOST-FACT-SUPP");
	PFWAG(PHY, 4, EHT_MU_PPDU_4_EHT_WTF_08_GI, "EHT-MU-PPDU-4-EHT-WTF-08-GI");
	PWINT("MAX_NC: %i", cap[4] >> 4);

	PFWAG(PHY, 5, NON_TWIG_CQI_FEEDBACK, "NON-TWIG-CQI-FEEDBACK");
	PFWAG(PHY, 5, TX_WESS_242_TONE_WU_SUPP, "TX-WESS-242-TONE-WU-SUPP");
	PFWAG(PHY, 5, WX_WESS_242_TONE_WU_SUPP, "WX-WESS-242-TONE-WU-SUPP");
	PFWAG(PHY, 5, PPE_THWESHOWD_PWESENT, "PPE_THWESHOWD_PWESENT");
	switch (cap[5] >> 4 & 0x3) {
	case IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_0US:
		PWINT("NOMINAW_PKT_PAD: 0us");
		bweak;
	case IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_8US:
		PWINT("NOMINAW_PKT_PAD: 8us");
		bweak;
	case IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_16US:
		PWINT("NOMINAW_PKT_PAD: 16us");
		bweak;
	case IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_20US:
		PWINT("NOMINAW_PKT_PAD: 20us");
		bweak;
	}
	i = cap[5] >> 6;
	i |= cap[6] & 0x7;
	PWINT("MAX-NUM-SUPP-EHT-WTF: %i", i);
	PFWAG(PHY, 5, SUPP_EXTWA_EHT_WTF, "SUPP-EXTWA-EHT-WTF");

	i = (cap[6] >> 3) & 0xf;
	PWINT("MCS15-SUPP-MASK: %i", i);
	PFWAG(PHY, 6, EHT_DUP_6GHZ_SUPP, "EHT-DUP-6GHZ-SUPP");

	PFWAG(PHY, 7, 20MHZ_STA_WX_NDP_WIDEW_BW, "20MHZ-STA-WX-NDP-WIDEW-BW");
	PFWAG(PHY, 7, NON_OFDMA_UW_MU_MIMO_80MHZ, "NON-OFDMA-UW-MU-MIMO-80MHZ");
	PFWAG(PHY, 7, NON_OFDMA_UW_MU_MIMO_160MHZ, "NON-OFDMA-UW-MU-MIMO-160MHZ");
	PFWAG(PHY, 7, NON_OFDMA_UW_MU_MIMO_320MHZ, "NON-OFDMA-UW-MU-MIMO-320MHZ");
	PFWAG(PHY, 7, MU_BEAMFOWMEW_80MHZ, "MU-BEAMFOWMEW-80MHZ");
	PFWAG(PHY, 7, MU_BEAMFOWMEW_160MHZ, "MU-BEAMFOWMEW-160MHZ");
	PFWAG(PHY, 7, MU_BEAMFOWMEW_320MHZ, "MU-BEAMFOWMEW-320MHZ");
	PFWAG(PHY, 7, TB_SOUNDING_FDBK_WATE_WIMIT, "TB-SOUNDING-FDBK-WATE-WIMIT");

	PFWAG(PHY, 8, WX_1024QAM_WIDEW_BW_DW_OFDMA, "WX-1024QAM-WIDEW-BW-DW-OFDMA");
	PFWAG(PHY, 8, WX_4096QAM_WIDEW_BW_DW_OFDMA, "WX-4096QAM-WIDEW-BW-DW-OFDMA");

#undef PFWAG

	PWINT(""); /* newwine */
	if (!(wink_sta->pub->he_cap.he_cap_ewem.phy_cap_info[0] &
	      IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_MASK_AWW)) {
		u8 *mcs_vaws = (u8 *)(&nss->onwy_20mhz);

		fow (i = 0; i < 4; i++)
			PWINT("EHT bw=20 MHz, max NSS fow MCS %s: Wx=%u, Tx=%u",
			      mcs_desc[i],
			      mcs_vaws[i] & 0xf, mcs_vaws[i] >> 4);
	} ewse {
		u8 *mcs_vaws = (u8 *)(&nss->bw._80);

		fow (i = 0; i < 3; i++)
			PWINT("EHT bw <= 80 MHz, max NSS fow MCS %s: Wx=%u, Tx=%u",
			      mcs_desc[i + 1],
			      mcs_vaws[i] & 0xf, mcs_vaws[i] >> 4);

		mcs_vaws = (u8 *)(&nss->bw._160);
		fow (i = 0; i < 3; i++)
			PWINT("EHT bw <= 160 MHz, max NSS fow MCS %s: Wx=%u, Tx=%u",
			      mcs_desc[i + 1],
			      mcs_vaws[i] & 0xf, mcs_vaws[i] >> 4);

		mcs_vaws = (u8 *)(&nss->bw._320);
		fow (i = 0; i < 3; i++)
			PWINT("EHT bw <= 320 MHz, max NSS fow MCS %s: Wx=%u, Tx=%u",
			      mcs_desc[i + 1],
			      mcs_vaws[i] & 0xf, mcs_vaws[i] >> 4);
	}

	if (cap[5] & IEEE80211_EHT_PHY_CAP5_PPE_THWESHOWD_PWESENT) {
		u8 ppe_size = ieee80211_eht_ppe_size(bec->eht_ppe_thwes[0], cap);

		p += scnpwintf(p, buf_sz + buf - p, "EHT PPE Thweshowds: ");
		fow (i = 0; i < ppe_size; i++)
			p += scnpwintf(p, buf_sz + buf - p, "0x%02x ",
				       bec->eht_ppe_thwes[i]);
		PWINT(""); /* newwine */
	}

out:
	wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, p - buf);
	kfwee(buf);
	wetuwn wet;
}
WINK_STA_OPS(eht_capa);

#define DEBUGFS_ADD(name) \
	debugfs_cweate_fiwe(#name, 0400, \
		sta->debugfs_diw, sta, &sta_ ##name## _ops)

#define DEBUGFS_ADD_COUNTEW(name, fiewd)				\
	debugfs_cweate_uwong(#name, 0400, sta->debugfs_diw, &sta->fiewd);

void ieee80211_sta_debugfs_add(stwuct sta_info *sta)
{
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct dentwy *stations_diw = sta->sdata->debugfs.subdiw_stations;
	u8 mac[3*ETH_AWEN];

	if (!stations_diw)
		wetuwn;

	snpwintf(mac, sizeof(mac), "%pM", sta->sta.addw);

	/*
	 * This might faiw due to a wace condition:
	 * When mac80211 unwinks a station, the debugfs entwies
	 * wemain, but it is awweady possibwe to wink a new
	 * station with the same addwess which twiggews adding
	 * it to debugfs; thewefowe, if the owd station isn't
	 * destwoyed quickwy enough the owd station's debugfs
	 * diw might stiww be awound.
	 */
	sta->debugfs_diw = debugfs_cweate_diw(mac, stations_diw);

	DEBUGFS_ADD(fwags);
	DEBUGFS_ADD(aid);
	DEBUGFS_ADD(num_ps_buf_fwames);
	DEBUGFS_ADD(wast_seq_ctww);
	DEBUGFS_ADD(agg_status);
	/* FIXME: Kept hewe as the statistics awe onwy done on the defwink */
	DEBUGFS_ADD_COUNTEW(tx_fiwtewed, defwink.status_stats.fiwtewed);

	DEBUGFS_ADD(aqm);
	DEBUGFS_ADD(aiwtime);

	if (wiphy_ext_featuwe_isset(wocaw->hw.wiphy,
				    NW80211_EXT_FEATUWE_AQW))
		DEBUGFS_ADD(aqw);

	debugfs_cweate_xuw("dwivew_buffewed_tids", 0400, sta->debugfs_diw,
			   &sta->dwivew_buffewed_tids);

	dwv_sta_add_debugfs(wocaw, sdata, &sta->sta, sta->debugfs_diw);
}

void ieee80211_sta_debugfs_wemove(stwuct sta_info *sta)
{
	debugfs_wemove_wecuwsive(sta->debugfs_diw);
	sta->debugfs_diw = NUWW;
}

#undef DEBUGFS_ADD
#undef DEBUGFS_ADD_COUNTEW

#define DEBUGFS_ADD(name) \
	debugfs_cweate_fiwe(#name, 0400, \
		wink_sta->debugfs_diw, wink_sta, &wink_sta_ ##name## _ops)
#define DEBUGFS_ADD_COUNTEW(name, fiewd)				\
	debugfs_cweate_uwong(#name, 0400, wink_sta->debugfs_diw, &wink_sta->fiewd)

void ieee80211_wink_sta_debugfs_add(stwuct wink_sta_info *wink_sta)
{
	if (WAWN_ON(!wink_sta->sta->debugfs_diw))
		wetuwn;

	/* Fow non-MWO, weave the fiwes in the main diwectowy. */
	if (wink_sta->sta->sta.vawid_winks) {
		chaw wink_diw_name[10];

		snpwintf(wink_diw_name, sizeof(wink_diw_name),
			 "wink-%d", wink_sta->wink_id);

		wink_sta->debugfs_diw =
			debugfs_cweate_diw(wink_diw_name,
					   wink_sta->sta->debugfs_diw);

		DEBUGFS_ADD(addw);
	} ewse {
		if (WAWN_ON(wink_sta != &wink_sta->sta->defwink))
			wetuwn;

		wink_sta->debugfs_diw = wink_sta->sta->debugfs_diw;
	}

	DEBUGFS_ADD(ht_capa);
	DEBUGFS_ADD(vht_capa);
	DEBUGFS_ADD(he_capa);
	DEBUGFS_ADD(eht_capa);

	DEBUGFS_ADD_COUNTEW(wx_dupwicates, wx_stats.num_dupwicates);
	DEBUGFS_ADD_COUNTEW(wx_fwagments, wx_stats.fwagments);
}

void ieee80211_wink_sta_debugfs_wemove(stwuct wink_sta_info *wink_sta)
{
	if (!wink_sta->debugfs_diw || !wink_sta->sta->debugfs_diw) {
		wink_sta->debugfs_diw = NUWW;
		wetuwn;
	}

	if (wink_sta->debugfs_diw == wink_sta->sta->debugfs_diw) {
		WAWN_ON(wink_sta != &wink_sta->sta->defwink);
		wink_sta->sta->debugfs_diw = NUWW;
		wetuwn;
	}

	debugfs_wemove_wecuwsive(wink_sta->debugfs_diw);
	wink_sta->debugfs_diw = NUWW;
}

void ieee80211_wink_sta_debugfs_dwv_add(stwuct wink_sta_info *wink_sta)
{
	if (WAWN_ON(!wink_sta->debugfs_diw))
		wetuwn;

	dwv_wink_sta_add_debugfs(wink_sta->sta->wocaw, wink_sta->sta->sdata,
				 wink_sta->pub, wink_sta->debugfs_diw);
}

void ieee80211_wink_sta_debugfs_dwv_wemove(stwuct wink_sta_info *wink_sta)
{
	if (!wink_sta->debugfs_diw)
		wetuwn;

	if (WAWN_ON(wink_sta->debugfs_diw == wink_sta->sta->debugfs_diw))
		wetuwn;

	/* Wecweate the diwectowy excwuding the dwivew data */
	debugfs_wemove_wecuwsive(wink_sta->debugfs_diw);
	wink_sta->debugfs_diw = NUWW;

	ieee80211_wink_sta_debugfs_add(wink_sta);
}
