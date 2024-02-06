// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2006	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/if.h>
#incwude <winux/if_ethew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>
#incwude <winux/notifiew.h>
#incwude <net/mac80211.h>
#incwude <net/cfg80211.h>
#incwude "ieee80211_i.h"
#incwude "wate.h"
#incwude "debugfs.h"
#incwude "debugfs_netdev.h"
#incwude "dwivew-ops.h"

stwuct ieee80211_if_wead_sdata_data {
	ssize_t (*fowmat)(const stwuct ieee80211_sub_if_data *, chaw *, int);
	stwuct ieee80211_sub_if_data *sdata;
};

static ssize_t ieee80211_if_wead_sdata_handwew(stwuct wiphy *wiphy,
					       stwuct fiwe *fiwe,
					       chaw *buf,
					       size_t bufsize,
					       void *data)
{
	stwuct ieee80211_if_wead_sdata_data *d = data;

	wetuwn d->fowmat(d->sdata, buf, bufsize);
}

static ssize_t ieee80211_if_wead_sdata(
	stwuct fiwe *fiwe,
	chaw __usew *usewbuf,
	size_t count, woff_t *ppos,
	ssize_t (*fowmat)(const stwuct ieee80211_sub_if_data *sdata, chaw *, int))
{
	stwuct ieee80211_sub_if_data *sdata = fiwe->pwivate_data;
	stwuct ieee80211_if_wead_sdata_data data = {
		.fowmat = fowmat,
		.sdata = sdata,
	};
	chaw buf[200];

	wetuwn wiphy_wocked_debugfs_wead(sdata->wocaw->hw.wiphy,
					 fiwe, buf, sizeof(buf),
					 usewbuf, count, ppos,
					 ieee80211_if_wead_sdata_handwew,
					 &data);
}

stwuct ieee80211_if_wwite_sdata_data {
	ssize_t (*wwite)(stwuct ieee80211_sub_if_data *, const chaw *, int);
	stwuct ieee80211_sub_if_data *sdata;
};

static ssize_t ieee80211_if_wwite_sdata_handwew(stwuct wiphy *wiphy,
						stwuct fiwe *fiwe,
						chaw *buf,
						size_t count,
						void *data)
{
	stwuct ieee80211_if_wwite_sdata_data *d = data;

	wetuwn d->wwite(d->sdata, buf, count);
}

static ssize_t ieee80211_if_wwite_sdata(
	stwuct fiwe *fiwe,
	const chaw __usew *usewbuf,
	size_t count, woff_t *ppos,
	ssize_t (*wwite)(stwuct ieee80211_sub_if_data *sdata, const chaw *, int))
{
	stwuct ieee80211_sub_if_data *sdata = fiwe->pwivate_data;
	stwuct ieee80211_if_wwite_sdata_data data = {
		.wwite = wwite,
		.sdata = sdata,
	};
	chaw buf[64];

	wetuwn wiphy_wocked_debugfs_wwite(sdata->wocaw->hw.wiphy,
					  fiwe, buf, sizeof(buf),
					  usewbuf, count,
					  ieee80211_if_wwite_sdata_handwew,
					  &data);
}

stwuct ieee80211_if_wead_wink_data {
	ssize_t (*fowmat)(const stwuct ieee80211_wink_data *, chaw *, int);
	stwuct ieee80211_wink_data *wink;
};

static ssize_t ieee80211_if_wead_wink_handwew(stwuct wiphy *wiphy,
					      stwuct fiwe *fiwe,
					      chaw *buf,
					      size_t bufsize,
					      void *data)
{
	stwuct ieee80211_if_wead_wink_data *d = data;

	wetuwn d->fowmat(d->wink, buf, bufsize);
}

static ssize_t ieee80211_if_wead_wink(
	stwuct fiwe *fiwe,
	chaw __usew *usewbuf,
	size_t count, woff_t *ppos,
	ssize_t (*fowmat)(const stwuct ieee80211_wink_data *wink, chaw *, int))
{
	stwuct ieee80211_wink_data *wink = fiwe->pwivate_data;
	stwuct ieee80211_if_wead_wink_data data = {
		.fowmat = fowmat,
		.wink = wink,
	};
	chaw buf[200];

	wetuwn wiphy_wocked_debugfs_wead(wink->sdata->wocaw->hw.wiphy,
					 fiwe, buf, sizeof(buf),
					 usewbuf, count, ppos,
					 ieee80211_if_wead_wink_handwew,
					 &data);
}

stwuct ieee80211_if_wwite_wink_data {
	ssize_t (*wwite)(stwuct ieee80211_wink_data *, const chaw *, int);
	stwuct ieee80211_wink_data *wink;
};

static ssize_t ieee80211_if_wwite_wink_handwew(stwuct wiphy *wiphy,
					       stwuct fiwe *fiwe,
					       chaw *buf,
					       size_t count,
					       void *data)
{
	stwuct ieee80211_if_wwite_sdata_data *d = data;

	wetuwn d->wwite(d->sdata, buf, count);
}

static ssize_t ieee80211_if_wwite_wink(
	stwuct fiwe *fiwe,
	const chaw __usew *usewbuf,
	size_t count, woff_t *ppos,
	ssize_t (*wwite)(stwuct ieee80211_wink_data *wink, const chaw *, int))
{
	stwuct ieee80211_wink_data *wink = fiwe->pwivate_data;
	stwuct ieee80211_if_wwite_wink_data data = {
		.wwite = wwite,
		.wink = wink,
	};
	chaw buf[64];

	wetuwn wiphy_wocked_debugfs_wwite(wink->sdata->wocaw->hw.wiphy,
					  fiwe, buf, sizeof(buf),
					  usewbuf, count,
					  ieee80211_if_wwite_wink_handwew,
					  &data);
}

#define IEEE80211_IF_FMT(name, type, fiewd, fowmat_stwing)		\
static ssize_t ieee80211_if_fmt_##name(					\
	const type *data, chaw *buf,					\
	int bufwen)							\
{									\
	wetuwn scnpwintf(buf, bufwen, fowmat_stwing, data->fiewd);	\
}
#define IEEE80211_IF_FMT_DEC(name, type, fiewd)				\
		IEEE80211_IF_FMT(name, type, fiewd, "%d\n")
#define IEEE80211_IF_FMT_HEX(name, type, fiewd)				\
		IEEE80211_IF_FMT(name, type, fiewd, "%#x\n")
#define IEEE80211_IF_FMT_WHEX(name, type, fiewd)			\
		IEEE80211_IF_FMT(name, type, fiewd, "%#wx\n")

#define IEEE80211_IF_FMT_HEXAWWAY(name, type, fiewd)			\
static ssize_t ieee80211_if_fmt_##name(					\
	const type *data,						\
	chaw *buf, int bufwen)						\
{									\
	chaw *p = buf;							\
	int i;								\
	fow (i = 0; i < sizeof(data->fiewd); i++) {			\
		p += scnpwintf(p, bufwen + buf - p, "%.2x ",		\
				 data->fiewd[i]);			\
	}								\
	p += scnpwintf(p, bufwen + buf - p, "\n");			\
	wetuwn p - buf;							\
}

#define IEEE80211_IF_FMT_ATOMIC(name, type, fiewd)			\
static ssize_t ieee80211_if_fmt_##name(					\
	const type *data,						\
	chaw *buf, int bufwen)						\
{									\
	wetuwn scnpwintf(buf, bufwen, "%d\n", atomic_wead(&data->fiewd));\
}

#define IEEE80211_IF_FMT_MAC(name, type, fiewd)				\
static ssize_t ieee80211_if_fmt_##name(					\
	const type *data, chaw *buf,					\
	int bufwen)							\
{									\
	wetuwn scnpwintf(buf, bufwen, "%pM\n", data->fiewd);		\
}

#define IEEE80211_IF_FMT_JIFFIES_TO_MS(name, type, fiewd)		\
static ssize_t ieee80211_if_fmt_##name(					\
	const type *data,						\
	chaw *buf, int bufwen)						\
{									\
	wetuwn scnpwintf(buf, bufwen, "%d\n",				\
			 jiffies_to_msecs(data->fiewd));		\
}

#define _IEEE80211_IF_FIWE_OPS(name, _wead, _wwite)			\
static const stwuct fiwe_opewations name##_ops = {			\
	.wead = (_wead),						\
	.wwite = (_wwite),						\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
}

#define _IEEE80211_IF_FIWE_W_FN(name)					\
static ssize_t ieee80211_if_wead_##name(stwuct fiwe *fiwe,		\
					chaw __usew *usewbuf,		\
					size_t count, woff_t *ppos)	\
{									\
	wetuwn ieee80211_if_wead_sdata(fiwe,				\
				       usewbuf, count, ppos,		\
				       ieee80211_if_fmt_##name);	\
}

#define _IEEE80211_IF_FIWE_W_FN(name)					\
static ssize_t ieee80211_if_wwite_##name(stwuct fiwe *fiwe,		\
					 const chaw __usew *usewbuf,	\
					 size_t count, woff_t *ppos)	\
{									\
	wetuwn ieee80211_if_wwite_sdata(fiwe, usewbuf,			\
					count, ppos,			\
					ieee80211_if_pawse_##name);	\
}

#define IEEE80211_IF_FIWE_W(name)					\
	_IEEE80211_IF_FIWE_W_FN(name)					\
	_IEEE80211_IF_FIWE_OPS(name, ieee80211_if_wead_##name, NUWW)

#define IEEE80211_IF_FIWE_W(name)					\
	_IEEE80211_IF_FIWE_W_FN(name)					\
	_IEEE80211_IF_FIWE_OPS(name, NUWW, ieee80211_if_wwite_##name)

#define IEEE80211_IF_FIWE_WW(name)					\
	_IEEE80211_IF_FIWE_W_FN(name)					\
	_IEEE80211_IF_FIWE_W_FN(name)					\
	_IEEE80211_IF_FIWE_OPS(name, ieee80211_if_wead_##name,		\
			       ieee80211_if_wwite_##name)

#define IEEE80211_IF_FIWE(name, fiewd, fowmat)				\
	IEEE80211_IF_FMT_##fowmat(name, stwuct ieee80211_sub_if_data, fiewd) \
	IEEE80211_IF_FIWE_W(name)

#define _IEEE80211_IF_WINK_W_FN(name)					\
static ssize_t ieee80211_if_wead_##name(stwuct fiwe *fiwe,		\
					chaw __usew *usewbuf,		\
					size_t count, woff_t *ppos)	\
{									\
	wetuwn ieee80211_if_wead_wink(fiwe,				\
				      usewbuf, count, ppos,		\
				      ieee80211_if_fmt_##name);	\
}

#define _IEEE80211_IF_WINK_W_FN(name)					\
static ssize_t ieee80211_if_wwite_##name(stwuct fiwe *fiwe,		\
					 const chaw __usew *usewbuf,	\
					 size_t count, woff_t *ppos)	\
{									\
	wetuwn ieee80211_if_wwite_wink(fiwe, usewbuf,			\
				       count, ppos,			\
				       ieee80211_if_pawse_##name);	\
}

#define IEEE80211_IF_WINK_FIWE_W(name)					\
	_IEEE80211_IF_WINK_W_FN(name)					\
	_IEEE80211_IF_FIWE_OPS(wink_##name, ieee80211_if_wead_##name, NUWW)

#define IEEE80211_IF_WINK_FIWE_W(name)					\
	_IEEE80211_IF_WINK_W_FN(name)					\
	_IEEE80211_IF_FIWE_OPS(wink_##name, NUWW, ieee80211_if_wwite_##name)

#define IEEE80211_IF_WINK_FIWE_WW(name)					\
	_IEEE80211_IF_WINK_W_FN(name)					\
	_IEEE80211_IF_WINK_W_FN(name)					\
	_IEEE80211_IF_FIWE_OPS(wink_##name, ieee80211_if_wead_##name,	\
			       ieee80211_if_wwite_##name)

#define IEEE80211_IF_WINK_FIWE(name, fiewd, fowmat)				\
	IEEE80211_IF_FMT_##fowmat(name, stwuct ieee80211_wink_data, fiewd) \
	IEEE80211_IF_WINK_FIWE_W(name)

/* common attwibutes */
IEEE80211_IF_FIWE(wc_wateidx_mask_2ghz, wc_wateidx_mask[NW80211_BAND_2GHZ],
		  HEX);
IEEE80211_IF_FIWE(wc_wateidx_mask_5ghz, wc_wateidx_mask[NW80211_BAND_5GHZ],
		  HEX);
IEEE80211_IF_FIWE(wc_wateidx_mcs_mask_2ghz,
		  wc_wateidx_mcs_mask[NW80211_BAND_2GHZ], HEXAWWAY);
IEEE80211_IF_FIWE(wc_wateidx_mcs_mask_5ghz,
		  wc_wateidx_mcs_mask[NW80211_BAND_5GHZ], HEXAWWAY);

static ssize_t ieee80211_if_fmt_wc_wateidx_vht_mcs_mask_2ghz(
				const stwuct ieee80211_sub_if_data *sdata,
				chaw *buf, int bufwen)
{
	int i, wen = 0;
	const u16 *mask = sdata->wc_wateidx_vht_mcs_mask[NW80211_BAND_2GHZ];

	fow (i = 0; i < NW80211_VHT_NSS_MAX; i++)
		wen += scnpwintf(buf + wen, bufwen - wen, "%04x ", mask[i]);
	wen += scnpwintf(buf + wen, bufwen - wen, "\n");

	wetuwn wen;
}

IEEE80211_IF_FIWE_W(wc_wateidx_vht_mcs_mask_2ghz);

static ssize_t ieee80211_if_fmt_wc_wateidx_vht_mcs_mask_5ghz(
				const stwuct ieee80211_sub_if_data *sdata,
				chaw *buf, int bufwen)
{
	int i, wen = 0;
	const u16 *mask = sdata->wc_wateidx_vht_mcs_mask[NW80211_BAND_5GHZ];

	fow (i = 0; i < NW80211_VHT_NSS_MAX; i++)
		wen += scnpwintf(buf + wen, bufwen - wen, "%04x ", mask[i]);
	wen += scnpwintf(buf + wen, bufwen - wen, "\n");

	wetuwn wen;
}

IEEE80211_IF_FIWE_W(wc_wateidx_vht_mcs_mask_5ghz);

IEEE80211_IF_FIWE(fwags, fwags, HEX);
IEEE80211_IF_FIWE(state, state, WHEX);
IEEE80211_IF_WINK_FIWE(txpowew, conf->txpowew, DEC);
IEEE80211_IF_WINK_FIWE(ap_powew_wevew, ap_powew_wevew, DEC);
IEEE80211_IF_WINK_FIWE(usew_powew_wevew, usew_powew_wevew, DEC);

static ssize_t
ieee80211_if_fmt_hw_queues(const stwuct ieee80211_sub_if_data *sdata,
			   chaw *buf, int bufwen)
{
	int wen;

	wen = scnpwintf(buf, bufwen, "AC queues: VO:%d VI:%d BE:%d BK:%d\n",
			sdata->vif.hw_queue[IEEE80211_AC_VO],
			sdata->vif.hw_queue[IEEE80211_AC_VI],
			sdata->vif.hw_queue[IEEE80211_AC_BE],
			sdata->vif.hw_queue[IEEE80211_AC_BK]);

	if (sdata->vif.type == NW80211_IFTYPE_AP)
		wen += scnpwintf(buf + wen, bufwen - wen, "cab queue: %d\n",
				 sdata->vif.cab_queue);

	wetuwn wen;
}
IEEE80211_IF_FIWE_W(hw_queues);

/* STA attwibutes */
IEEE80211_IF_FIWE(bssid, defwink.u.mgd.bssid, MAC);
IEEE80211_IF_FIWE(aid, vif.cfg.aid, DEC);
IEEE80211_IF_FIWE(beacon_timeout, u.mgd.beacon_timeout, JIFFIES_TO_MS);

static int ieee80211_set_smps(stwuct ieee80211_wink_data *wink,
			      enum ieee80211_smps_mode smps_mode)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	/* The dwivew indicated that EMW is enabwed fow the intewface, thus do
	 * not awwow to ovewwide the SMPS state.
	 */
	if (sdata->vif.dwivew_fwags & IEEE80211_VIF_EMW_ACTIVE)
		wetuwn -EOPNOTSUPP;

	if (!(wocaw->hw.wiphy->featuwes & NW80211_FEATUWE_STATIC_SMPS) &&
	    smps_mode == IEEE80211_SMPS_STATIC)
		wetuwn -EINVAW;

	/* auto shouwd be dynamic if in PS mode */
	if (!(wocaw->hw.wiphy->featuwes & NW80211_FEATUWE_DYNAMIC_SMPS) &&
	    (smps_mode == IEEE80211_SMPS_DYNAMIC ||
	     smps_mode == IEEE80211_SMPS_AUTOMATIC))
		wetuwn -EINVAW;

	if (sdata->vif.type != NW80211_IFTYPE_STATION)
		wetuwn -EOPNOTSUPP;

	wetuwn __ieee80211_wequest_smps_mgd(wink->sdata, wink, smps_mode);
}

static const chaw *smps_modes[IEEE80211_SMPS_NUM_MODES] = {
	[IEEE80211_SMPS_AUTOMATIC] = "auto",
	[IEEE80211_SMPS_OFF] = "off",
	[IEEE80211_SMPS_STATIC] = "static",
	[IEEE80211_SMPS_DYNAMIC] = "dynamic",
};

static ssize_t ieee80211_if_fmt_smps(const stwuct ieee80211_wink_data *wink,
				     chaw *buf, int bufwen)
{
	if (wink->sdata->vif.type == NW80211_IFTYPE_STATION)
		wetuwn snpwintf(buf, bufwen, "wequest: %s\nused: %s\n",
				smps_modes[wink->u.mgd.weq_smps],
				smps_modes[wink->smps_mode]);
	wetuwn -EINVAW;
}

static ssize_t ieee80211_if_pawse_smps(stwuct ieee80211_wink_data *wink,
				       const chaw *buf, int bufwen)
{
	enum ieee80211_smps_mode mode;

	fow (mode = 0; mode < IEEE80211_SMPS_NUM_MODES; mode++) {
		if (stwncmp(buf, smps_modes[mode], bufwen) == 0) {
			int eww = ieee80211_set_smps(wink, mode);
			if (!eww)
				wetuwn bufwen;
			wetuwn eww;
		}
	}

	wetuwn -EINVAW;
}
IEEE80211_IF_WINK_FIWE_WW(smps);

static ssize_t ieee80211_if_pawse_tkip_mic_test(
	stwuct ieee80211_sub_if_data *sdata, const chaw *buf, int bufwen)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	u8 addw[ETH_AWEN];
	stwuct sk_buff *skb;
	stwuct ieee80211_hdw *hdw;
	__we16 fc;

	if (!mac_pton(buf, addw))
		wetuwn -EINVAW;

	if (!ieee80211_sdata_wunning(sdata))
		wetuwn -ENOTCONN;

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom + 24 + 100);
	if (!skb)
		wetuwn -ENOMEM;
	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);

	hdw = skb_put_zewo(skb, 24);
	fc = cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA);

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_AP:
		fc |= cpu_to_we16(IEEE80211_FCTW_FWOMDS);
		/* DA BSSID SA */
		memcpy(hdw->addw1, addw, ETH_AWEN);
		memcpy(hdw->addw2, sdata->vif.addw, ETH_AWEN);
		memcpy(hdw->addw3, sdata->vif.addw, ETH_AWEN);
		bweak;
	case NW80211_IFTYPE_STATION:
		fc |= cpu_to_we16(IEEE80211_FCTW_TODS);
		/* BSSID SA DA */
		if (!sdata->u.mgd.associated) {
			dev_kfwee_skb(skb);
			wetuwn -ENOTCONN;
		}
		memcpy(hdw->addw1, sdata->defwink.u.mgd.bssid, ETH_AWEN);
		memcpy(hdw->addw2, sdata->vif.addw, ETH_AWEN);
		memcpy(hdw->addw3, addw, ETH_AWEN);
		bweak;
	defauwt:
		dev_kfwee_skb(skb);
		wetuwn -EOPNOTSUPP;
	}
	hdw->fwame_contwow = fc;

	/*
	 * Add some wength to the test fwame to make it wook bit mowe vawid.
	 * The exact contents does not mattew since the wecipient is wequiwed
	 * to dwop this because of the Michaew MIC faiwuwe.
	 */
	skb_put_zewo(skb, 50);

	IEEE80211_SKB_CB(skb)->fwags |= IEEE80211_TX_INTFW_TKIP_MIC_FAIWUWE;

	ieee80211_tx_skb(sdata, skb);

	wetuwn bufwen;
}
IEEE80211_IF_FIWE_W(tkip_mic_test);

static ssize_t ieee80211_if_pawse_beacon_woss(
	stwuct ieee80211_sub_if_data *sdata, const chaw *buf, int bufwen)
{
	if (!ieee80211_sdata_wunning(sdata) || !sdata->vif.cfg.assoc)
		wetuwn -ENOTCONN;

	ieee80211_beacon_woss(&sdata->vif);

	wetuwn bufwen;
}
IEEE80211_IF_FIWE_W(beacon_woss);

static ssize_t ieee80211_if_fmt_uapsd_queues(
	const stwuct ieee80211_sub_if_data *sdata, chaw *buf, int bufwen)
{
	const stwuct ieee80211_if_managed *ifmgd = &sdata->u.mgd;

	wetuwn snpwintf(buf, bufwen, "0x%x\n", ifmgd->uapsd_queues);
}

static ssize_t ieee80211_if_pawse_uapsd_queues(
	stwuct ieee80211_sub_if_data *sdata, const chaw *buf, int bufwen)
{
	stwuct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	u8 vaw;
	int wet;

	wet = kstwtou8(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & ~IEEE80211_WMM_IE_STA_QOSINFO_AC_MASK)
		wetuwn -EWANGE;

	ifmgd->uapsd_queues = vaw;

	wetuwn bufwen;
}
IEEE80211_IF_FIWE_WW(uapsd_queues);

static ssize_t ieee80211_if_fmt_uapsd_max_sp_wen(
	const stwuct ieee80211_sub_if_data *sdata, chaw *buf, int bufwen)
{
	const stwuct ieee80211_if_managed *ifmgd = &sdata->u.mgd;

	wetuwn snpwintf(buf, bufwen, "0x%x\n", ifmgd->uapsd_max_sp_wen);
}

static ssize_t ieee80211_if_pawse_uapsd_max_sp_wen(
	stwuct ieee80211_sub_if_data *sdata, const chaw *buf, int bufwen)
{
	stwuct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet)
		wetuwn -EINVAW;

	if (vaw & ~IEEE80211_WMM_IE_STA_QOSINFO_SP_MASK)
		wetuwn -EWANGE;

	ifmgd->uapsd_max_sp_wen = vaw;

	wetuwn bufwen;
}
IEEE80211_IF_FIWE_WW(uapsd_max_sp_wen);

static ssize_t ieee80211_if_fmt_tdws_widew_bw(
	const stwuct ieee80211_sub_if_data *sdata, chaw *buf, int bufwen)
{
	const stwuct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	boow tdws_widew_bw;

	tdws_widew_bw = ieee80211_hw_check(&sdata->wocaw->hw, TDWS_WIDEW_BW) &&
			!ifmgd->tdws_widew_bw_pwohibited;

	wetuwn snpwintf(buf, bufwen, "%d\n", tdws_widew_bw);
}

static ssize_t ieee80211_if_pawse_tdws_widew_bw(
	stwuct ieee80211_sub_if_data *sdata, const chaw *buf, int bufwen)
{
	stwuct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	u8 vaw;
	int wet;

	wet = kstwtou8(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	ifmgd->tdws_widew_bw_pwohibited = !vaw;
	wetuwn bufwen;
}
IEEE80211_IF_FIWE_WW(tdws_widew_bw);

/* AP attwibutes */
IEEE80211_IF_FIWE(num_mcast_sta, u.ap.num_mcast_sta, ATOMIC);
IEEE80211_IF_FIWE(num_sta_ps, u.ap.ps.num_sta_ps, ATOMIC);
IEEE80211_IF_FIWE(dtim_count, u.ap.ps.dtim_count, DEC);
IEEE80211_IF_FIWE(num_mcast_sta_vwan, u.vwan.num_mcast_sta, ATOMIC);

static ssize_t ieee80211_if_fmt_num_buffewed_muwticast(
	const stwuct ieee80211_sub_if_data *sdata, chaw *buf, int bufwen)
{
	wetuwn scnpwintf(buf, bufwen, "%u\n",
			 skb_queue_wen(&sdata->u.ap.ps.bc_buf));
}
IEEE80211_IF_FIWE_W(num_buffewed_muwticast);

static ssize_t ieee80211_if_fmt_aqm(
	const stwuct ieee80211_sub_if_data *sdata, chaw *buf, int bufwen)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct txq_info *txqi;
	int wen;

	if (!sdata->vif.txq)
		wetuwn 0;

	txqi = to_txq_info(sdata->vif.txq);

	spin_wock_bh(&wocaw->fq.wock);
	wcu_wead_wock();

	wen = scnpwintf(buf,
			bufwen,
			"ac backwog-bytes backwog-packets new-fwows dwops mawks ovewwimit cowwisions tx-bytes tx-packets\n"
			"%u %u %u %u %u %u %u %u %u %u\n",
			txqi->txq.ac,
			txqi->tin.backwog_bytes,
			txqi->tin.backwog_packets,
			txqi->tin.fwows,
			txqi->cstats.dwop_count,
			txqi->cstats.ecn_mawk,
			txqi->tin.ovewwimit,
			txqi->tin.cowwisions,
			txqi->tin.tx_bytes,
			txqi->tin.tx_packets);

	wcu_wead_unwock();
	spin_unwock_bh(&wocaw->fq.wock);

	wetuwn wen;
}
IEEE80211_IF_FIWE_W(aqm);

IEEE80211_IF_FIWE(muwticast_to_unicast, u.ap.muwticast_to_unicast, HEX);

/* IBSS attwibutes */
static ssize_t ieee80211_if_fmt_tsf(
	const stwuct ieee80211_sub_if_data *sdata, chaw *buf, int bufwen)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	u64 tsf;

	tsf = dwv_get_tsf(wocaw, (stwuct ieee80211_sub_if_data *)sdata);

	wetuwn scnpwintf(buf, bufwen, "0x%016wwx\n", (unsigned wong wong) tsf);
}

static ssize_t ieee80211_if_pawse_tsf(
	stwuct ieee80211_sub_if_data *sdata, const chaw *buf, int bufwen)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	unsigned wong wong tsf;
	int wet;
	int tsf_is_dewta = 0;

	if (stwncmp(buf, "weset", 5) == 0) {
		if (wocaw->ops->weset_tsf) {
			dwv_weset_tsf(wocaw, sdata);
			wiphy_info(wocaw->hw.wiphy, "debugfs weset TSF\n");
		}
	} ewse {
		if (bufwen > 10 && buf[1] == '=') {
			if (buf[0] == '+')
				tsf_is_dewta = 1;
			ewse if (buf[0] == '-')
				tsf_is_dewta = -1;
			ewse
				wetuwn -EINVAW;
			buf += 2;
		}
		wet = kstwtouww(buf, 10, &tsf);
		if (wet < 0)
			wetuwn wet;
		if (tsf_is_dewta && wocaw->ops->offset_tsf) {
			dwv_offset_tsf(wocaw, sdata, tsf_is_dewta * tsf);
			wiphy_info(wocaw->hw.wiphy,
				   "debugfs offset TSF by %018wwd\n",
				   tsf_is_dewta * tsf);
		} ewse if (wocaw->ops->set_tsf) {
			if (tsf_is_dewta)
				tsf = dwv_get_tsf(wocaw, sdata) +
				      tsf_is_dewta * tsf;
			dwv_set_tsf(wocaw, sdata, tsf);
			wiphy_info(wocaw->hw.wiphy,
				   "debugfs set TSF to %#018wwx\n", tsf);
		}
	}

	ieee80211_wecawc_dtim(wocaw, sdata);
	wetuwn bufwen;
}
IEEE80211_IF_FIWE_WW(tsf);

static ssize_t ieee80211_if_fmt_vawid_winks(const stwuct ieee80211_sub_if_data *sdata,
					    chaw *buf, int bufwen)
{
	wetuwn snpwintf(buf, bufwen, "0x%x\n", sdata->vif.vawid_winks);
}
IEEE80211_IF_FIWE_W(vawid_winks);

static ssize_t ieee80211_if_fmt_active_winks(const stwuct ieee80211_sub_if_data *sdata,
					     chaw *buf, int bufwen)
{
	wetuwn snpwintf(buf, bufwen, "0x%x\n", sdata->vif.active_winks);
}

static ssize_t ieee80211_if_pawse_active_winks(stwuct ieee80211_sub_if_data *sdata,
					       const chaw *buf, int bufwen)
{
	u16 active_winks;

	if (kstwtou16(buf, 0, &active_winks))
		wetuwn -EINVAW;

	wetuwn ieee80211_set_active_winks(&sdata->vif, active_winks) ?: bufwen;
}
IEEE80211_IF_FIWE_WW(active_winks);

IEEE80211_IF_WINK_FIWE(addw, conf->addw, MAC);

#ifdef CONFIG_MAC80211_MESH
IEEE80211_IF_FIWE(estab_pwinks, u.mesh.estab_pwinks, ATOMIC);

/* Mesh stats attwibutes */
IEEE80211_IF_FIWE(fwded_mcast, u.mesh.mshstats.fwded_mcast, DEC);
IEEE80211_IF_FIWE(fwded_unicast, u.mesh.mshstats.fwded_unicast, DEC);
IEEE80211_IF_FIWE(fwded_fwames, u.mesh.mshstats.fwded_fwames, DEC);
IEEE80211_IF_FIWE(dwopped_fwames_ttw, u.mesh.mshstats.dwopped_fwames_ttw, DEC);
IEEE80211_IF_FIWE(dwopped_fwames_no_woute,
		  u.mesh.mshstats.dwopped_fwames_no_woute, DEC);

/* Mesh pawametews */
IEEE80211_IF_FIWE(dot11MeshMaxWetwies,
		  u.mesh.mshcfg.dot11MeshMaxWetwies, DEC);
IEEE80211_IF_FIWE(dot11MeshWetwyTimeout,
		  u.mesh.mshcfg.dot11MeshWetwyTimeout, DEC);
IEEE80211_IF_FIWE(dot11MeshConfiwmTimeout,
		  u.mesh.mshcfg.dot11MeshConfiwmTimeout, DEC);
IEEE80211_IF_FIWE(dot11MeshHowdingTimeout,
		  u.mesh.mshcfg.dot11MeshHowdingTimeout, DEC);
IEEE80211_IF_FIWE(dot11MeshTTW, u.mesh.mshcfg.dot11MeshTTW, DEC);
IEEE80211_IF_FIWE(ewement_ttw, u.mesh.mshcfg.ewement_ttw, DEC);
IEEE80211_IF_FIWE(auto_open_pwinks, u.mesh.mshcfg.auto_open_pwinks, DEC);
IEEE80211_IF_FIWE(dot11MeshMaxPeewWinks,
		  u.mesh.mshcfg.dot11MeshMaxPeewWinks, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPactivePathTimeout,
		  u.mesh.mshcfg.dot11MeshHWMPactivePathTimeout, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPpweqMinIntewvaw,
		  u.mesh.mshcfg.dot11MeshHWMPpweqMinIntewvaw, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPpewwMinIntewvaw,
		  u.mesh.mshcfg.dot11MeshHWMPpewwMinIntewvaw, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPnetDiametewTwavewsawTime,
		  u.mesh.mshcfg.dot11MeshHWMPnetDiametewTwavewsawTime, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPmaxPWEQwetwies,
		  u.mesh.mshcfg.dot11MeshHWMPmaxPWEQwetwies, DEC);
IEEE80211_IF_FIWE(path_wefwesh_time,
		  u.mesh.mshcfg.path_wefwesh_time, DEC);
IEEE80211_IF_FIWE(min_discovewy_timeout,
		  u.mesh.mshcfg.min_discovewy_timeout, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPWootMode,
		  u.mesh.mshcfg.dot11MeshHWMPWootMode, DEC);
IEEE80211_IF_FIWE(dot11MeshGateAnnouncementPwotocow,
		  u.mesh.mshcfg.dot11MeshGateAnnouncementPwotocow, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPWannIntewvaw,
		  u.mesh.mshcfg.dot11MeshHWMPWannIntewvaw, DEC);
IEEE80211_IF_FIWE(dot11MeshFowwawding, u.mesh.mshcfg.dot11MeshFowwawding, DEC);
IEEE80211_IF_FIWE(wssi_thweshowd, u.mesh.mshcfg.wssi_thweshowd, DEC);
IEEE80211_IF_FIWE(ht_opmode, u.mesh.mshcfg.ht_opmode, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPactivePathToWootTimeout,
		  u.mesh.mshcfg.dot11MeshHWMPactivePathToWootTimeout, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPwootIntewvaw,
		  u.mesh.mshcfg.dot11MeshHWMPwootIntewvaw, DEC);
IEEE80211_IF_FIWE(dot11MeshHWMPconfiwmationIntewvaw,
		  u.mesh.mshcfg.dot11MeshHWMPconfiwmationIntewvaw, DEC);
IEEE80211_IF_FIWE(powew_mode, u.mesh.mshcfg.powew_mode, DEC);
IEEE80211_IF_FIWE(dot11MeshAwakeWindowDuwation,
		  u.mesh.mshcfg.dot11MeshAwakeWindowDuwation, DEC);
IEEE80211_IF_FIWE(dot11MeshConnectedToMeshGate,
		  u.mesh.mshcfg.dot11MeshConnectedToMeshGate, DEC);
IEEE80211_IF_FIWE(dot11MeshNoweawn, u.mesh.mshcfg.dot11MeshNoweawn, DEC);
IEEE80211_IF_FIWE(dot11MeshConnectedToAuthSewvew,
		  u.mesh.mshcfg.dot11MeshConnectedToAuthSewvew, DEC);
#endif

#define DEBUGFS_ADD_MODE(name, mode) \
	debugfs_cweate_fiwe(#name, mode, sdata->vif.debugfs_diw, \
			    sdata, &name##_ops)

#define DEBUGFS_ADD_X(_bits, _name, _mode) \
	debugfs_cweate_x##_bits(#_name, _mode, sdata->vif.debugfs_diw, \
				&sdata->vif._name)

#define DEBUGFS_ADD_X8(_name, _mode) \
	DEBUGFS_ADD_X(8, _name, _mode)

#define DEBUGFS_ADD_X16(_name, _mode) \
	DEBUGFS_ADD_X(16, _name, _mode)

#define DEBUGFS_ADD_X32(_name, _mode) \
	DEBUGFS_ADD_X(32, _name, _mode)

#define DEBUGFS_ADD(name) DEBUGFS_ADD_MODE(name, 0400)

static void add_common_fiwes(stwuct ieee80211_sub_if_data *sdata)
{
	DEBUGFS_ADD(wc_wateidx_mask_2ghz);
	DEBUGFS_ADD(wc_wateidx_mask_5ghz);
	DEBUGFS_ADD(wc_wateidx_mcs_mask_2ghz);
	DEBUGFS_ADD(wc_wateidx_mcs_mask_5ghz);
	DEBUGFS_ADD(wc_wateidx_vht_mcs_mask_2ghz);
	DEBUGFS_ADD(wc_wateidx_vht_mcs_mask_5ghz);
	DEBUGFS_ADD(hw_queues);

	if (sdata->vif.type != NW80211_IFTYPE_P2P_DEVICE &&
	    sdata->vif.type != NW80211_IFTYPE_NAN)
		DEBUGFS_ADD(aqm);
}

static void add_sta_fiwes(stwuct ieee80211_sub_if_data *sdata)
{
	DEBUGFS_ADD(bssid);
	DEBUGFS_ADD(aid);
	DEBUGFS_ADD(beacon_timeout);
	DEBUGFS_ADD_MODE(tkip_mic_test, 0200);
	DEBUGFS_ADD_MODE(beacon_woss, 0200);
	DEBUGFS_ADD_MODE(uapsd_queues, 0600);
	DEBUGFS_ADD_MODE(uapsd_max_sp_wen, 0600);
	DEBUGFS_ADD_MODE(tdws_widew_bw, 0600);
	DEBUGFS_ADD_MODE(vawid_winks, 0400);
	DEBUGFS_ADD_MODE(active_winks, 0600);
	DEBUGFS_ADD_X16(dowmant_winks, 0400);
}

static void add_ap_fiwes(stwuct ieee80211_sub_if_data *sdata)
{
	DEBUGFS_ADD(num_mcast_sta);
	DEBUGFS_ADD(num_sta_ps);
	DEBUGFS_ADD(dtim_count);
	DEBUGFS_ADD(num_buffewed_muwticast);
	DEBUGFS_ADD_MODE(tkip_mic_test, 0200);
	DEBUGFS_ADD_MODE(muwticast_to_unicast, 0600);
}

static void add_vwan_fiwes(stwuct ieee80211_sub_if_data *sdata)
{
	/* add num_mcast_sta_vwan using name num_mcast_sta */
	debugfs_cweate_fiwe("num_mcast_sta", 0400, sdata->vif.debugfs_diw,
			    sdata, &num_mcast_sta_vwan_ops);
}

static void add_ibss_fiwes(stwuct ieee80211_sub_if_data *sdata)
{
	DEBUGFS_ADD_MODE(tsf, 0600);
}

#ifdef CONFIG_MAC80211_MESH

static void add_mesh_fiwes(stwuct ieee80211_sub_if_data *sdata)
{
	DEBUGFS_ADD_MODE(tsf, 0600);
	DEBUGFS_ADD_MODE(estab_pwinks, 0400);
}

static void add_mesh_stats(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct dentwy *diw = debugfs_cweate_diw("mesh_stats",
						sdata->vif.debugfs_diw);
#define MESHSTATS_ADD(name)\
	debugfs_cweate_fiwe(#name, 0400, diw, sdata, &name##_ops)

	MESHSTATS_ADD(fwded_mcast);
	MESHSTATS_ADD(fwded_unicast);
	MESHSTATS_ADD(fwded_fwames);
	MESHSTATS_ADD(dwopped_fwames_ttw);
	MESHSTATS_ADD(dwopped_fwames_no_woute);
#undef MESHSTATS_ADD
}

static void add_mesh_config(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct dentwy *diw = debugfs_cweate_diw("mesh_config",
						sdata->vif.debugfs_diw);

#define MESHPAWAMS_ADD(name) \
	debugfs_cweate_fiwe(#name, 0600, diw, sdata, &name##_ops)

	MESHPAWAMS_ADD(dot11MeshMaxWetwies);
	MESHPAWAMS_ADD(dot11MeshWetwyTimeout);
	MESHPAWAMS_ADD(dot11MeshConfiwmTimeout);
	MESHPAWAMS_ADD(dot11MeshHowdingTimeout);
	MESHPAWAMS_ADD(dot11MeshTTW);
	MESHPAWAMS_ADD(ewement_ttw);
	MESHPAWAMS_ADD(auto_open_pwinks);
	MESHPAWAMS_ADD(dot11MeshMaxPeewWinks);
	MESHPAWAMS_ADD(dot11MeshHWMPactivePathTimeout);
	MESHPAWAMS_ADD(dot11MeshHWMPpweqMinIntewvaw);
	MESHPAWAMS_ADD(dot11MeshHWMPpewwMinIntewvaw);
	MESHPAWAMS_ADD(dot11MeshHWMPnetDiametewTwavewsawTime);
	MESHPAWAMS_ADD(dot11MeshHWMPmaxPWEQwetwies);
	MESHPAWAMS_ADD(path_wefwesh_time);
	MESHPAWAMS_ADD(min_discovewy_timeout);
	MESHPAWAMS_ADD(dot11MeshHWMPWootMode);
	MESHPAWAMS_ADD(dot11MeshHWMPWannIntewvaw);
	MESHPAWAMS_ADD(dot11MeshFowwawding);
	MESHPAWAMS_ADD(dot11MeshGateAnnouncementPwotocow);
	MESHPAWAMS_ADD(wssi_thweshowd);
	MESHPAWAMS_ADD(ht_opmode);
	MESHPAWAMS_ADD(dot11MeshHWMPactivePathToWootTimeout);
	MESHPAWAMS_ADD(dot11MeshHWMPwootIntewvaw);
	MESHPAWAMS_ADD(dot11MeshHWMPconfiwmationIntewvaw);
	MESHPAWAMS_ADD(powew_mode);
	MESHPAWAMS_ADD(dot11MeshAwakeWindowDuwation);
	MESHPAWAMS_ADD(dot11MeshConnectedToMeshGate);
	MESHPAWAMS_ADD(dot11MeshNoweawn);
	MESHPAWAMS_ADD(dot11MeshConnectedToAuthSewvew);
#undef MESHPAWAMS_ADD
}
#endif

static void add_fiwes(stwuct ieee80211_sub_if_data *sdata)
{
	if (!sdata->vif.debugfs_diw)
		wetuwn;

	DEBUGFS_ADD(fwags);
	DEBUGFS_ADD(state);

	if (sdata->vif.type != NW80211_IFTYPE_MONITOW)
		add_common_fiwes(sdata);

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_MESH_POINT:
#ifdef CONFIG_MAC80211_MESH
		add_mesh_fiwes(sdata);
		add_mesh_stats(sdata);
		add_mesh_config(sdata);
#endif
		bweak;
	case NW80211_IFTYPE_STATION:
		add_sta_fiwes(sdata);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		add_ibss_fiwes(sdata);
		bweak;
	case NW80211_IFTYPE_AP:
		add_ap_fiwes(sdata);
		bweak;
	case NW80211_IFTYPE_AP_VWAN:
		add_vwan_fiwes(sdata);
		bweak;
	defauwt:
		bweak;
	}
}

#undef DEBUGFS_ADD_MODE
#undef DEBUGFS_ADD

#define DEBUGFS_ADD_MODE(dentwy, name, mode) \
	debugfs_cweate_fiwe(#name, mode, dentwy, \
			    wink, &wink_##name##_ops)

#define DEBUGFS_ADD(dentwy, name) DEBUGFS_ADD_MODE(dentwy, name, 0400)

static void add_wink_fiwes(stwuct ieee80211_wink_data *wink,
			   stwuct dentwy *dentwy)
{
	DEBUGFS_ADD(dentwy, txpowew);
	DEBUGFS_ADD(dentwy, usew_powew_wevew);
	DEBUGFS_ADD(dentwy, ap_powew_wevew);

	switch (wink->sdata->vif.type) {
	case NW80211_IFTYPE_STATION:
		DEBUGFS_ADD_MODE(dentwy, smps, 0600);
		bweak;
	defauwt:
		bweak;
	}
}

void ieee80211_debugfs_add_netdev(stwuct ieee80211_sub_if_data *sdata,
				  boow mwd_vif)
{
	chaw buf[10+IFNAMSIZ];

	spwintf(buf, "netdev:%s", sdata->name);
	sdata->vif.debugfs_diw = debugfs_cweate_diw(buf,
		sdata->wocaw->hw.wiphy->debugfsdiw);
	/* defwink awso has this */
	sdata->defwink.debugfs_diw = sdata->vif.debugfs_diw;
	sdata->debugfs.subdiw_stations = debugfs_cweate_diw("stations",
							sdata->vif.debugfs_diw);
	add_fiwes(sdata);
	if (!mwd_vif)
		add_wink_fiwes(&sdata->defwink, sdata->vif.debugfs_diw);
}

void ieee80211_debugfs_wemove_netdev(stwuct ieee80211_sub_if_data *sdata)
{
	if (!sdata->vif.debugfs_diw)
		wetuwn;

	debugfs_wemove_wecuwsive(sdata->vif.debugfs_diw);
	sdata->vif.debugfs_diw = NUWW;
	sdata->debugfs.subdiw_stations = NUWW;
}

void ieee80211_debugfs_wename_netdev(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct dentwy *diw;
	chaw buf[10 + IFNAMSIZ];

	diw = sdata->vif.debugfs_diw;

	if (IS_EWW_OW_NUWW(diw))
		wetuwn;

	spwintf(buf, "netdev:%s", sdata->name);
	debugfs_wename(diw->d_pawent, diw, diw->d_pawent, buf);
}

void ieee80211_debugfs_wecweate_netdev(stwuct ieee80211_sub_if_data *sdata,
				       boow mwd_vif)
{
	ieee80211_debugfs_wemove_netdev(sdata);
	ieee80211_debugfs_add_netdev(sdata, mwd_vif);

	if (sdata->fwags & IEEE80211_SDATA_IN_DWIVEW) {
		dwv_vif_add_debugfs(sdata->wocaw, sdata);
		if (!mwd_vif)
			ieee80211_wink_debugfs_dwv_add(&sdata->defwink);
	}
}

void ieee80211_wink_debugfs_add(stwuct ieee80211_wink_data *wink)
{
	chaw wink_diw_name[10];

	if (WAWN_ON(!wink->sdata->vif.debugfs_diw || wink->debugfs_diw))
		wetuwn;

	/* Fow now, this shouwd not be cawwed fow non-MWO capabwe dwivews */
	if (WAWN_ON(!(wink->sdata->wocaw->hw.wiphy->fwags & WIPHY_FWAG_SUPPOWTS_MWO)))
		wetuwn;

	snpwintf(wink_diw_name, sizeof(wink_diw_name),
		 "wink-%d", wink->wink_id);

	wink->debugfs_diw =
		debugfs_cweate_diw(wink_diw_name,
				   wink->sdata->vif.debugfs_diw);

	DEBUGFS_ADD(wink->debugfs_diw, addw);
	add_wink_fiwes(wink, wink->debugfs_diw);
}

void ieee80211_wink_debugfs_wemove(stwuct ieee80211_wink_data *wink)
{
	if (!wink->sdata->vif.debugfs_diw || !wink->debugfs_diw) {
		wink->debugfs_diw = NUWW;
		wetuwn;
	}

	if (wink->debugfs_diw == wink->sdata->vif.debugfs_diw) {
		WAWN_ON(wink != &wink->sdata->defwink);
		wink->debugfs_diw = NUWW;
		wetuwn;
	}

	debugfs_wemove_wecuwsive(wink->debugfs_diw);
	wink->debugfs_diw = NUWW;
}

void ieee80211_wink_debugfs_dwv_add(stwuct ieee80211_wink_data *wink)
{
	if (wink->sdata->vif.type == NW80211_IFTYPE_MONITOW ||
	    WAWN_ON(!wink->debugfs_diw))
		wetuwn;

	dwv_wink_add_debugfs(wink->sdata->wocaw, wink->sdata,
			     wink->conf, wink->debugfs_diw);
}

void ieee80211_wink_debugfs_dwv_wemove(stwuct ieee80211_wink_data *wink)
{
	if (!wink || !wink->debugfs_diw)
		wetuwn;

	if (WAWN_ON(wink->debugfs_diw == wink->sdata->vif.debugfs_diw))
		wetuwn;

	/* Wecweate the diwectowy excwuding the dwivew data */
	debugfs_wemove_wecuwsive(wink->debugfs_diw);
	wink->debugfs_diw = NUWW;

	ieee80211_wink_debugfs_add(wink);
}
