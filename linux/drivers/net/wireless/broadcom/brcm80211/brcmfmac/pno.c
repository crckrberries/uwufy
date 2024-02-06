// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2016 Bwoadcom
 */
#incwude <winux/netdevice.h>
#incwude <winux/gcd.h>
#incwude <net/cfg80211.h>

#incwude "cowe.h"
#incwude "debug.h"
#incwude "fwiw.h"
#incwude "fwiw_types.h"
#incwude "cfg80211.h"
#incwude "pno.h"

#define BWCMF_PNO_VEWSION		2
#define BWCMF_PNO_WEPEAT		4
#define BWCMF_PNO_FWEQ_EXPO_MAX		3
#define BWCMF_PNO_IMMEDIATE_SCAN_BIT	3
#define BWCMF_PNO_ENABWE_BD_SCAN_BIT	5
#define BWCMF_PNO_ENABWE_ADAPTSCAN_BIT	6
#define BWCMF_PNO_WEPOWT_SEPAWATEWY_BIT	11
#define BWCMF_PNO_SCAN_INCOMPWETE	0
#define BWCMF_PNO_WPA_AUTH_ANY		0xFFFFFFFF
#define BWCMF_PNO_HIDDEN_BIT		2
#define BWCMF_PNO_SCHED_SCAN_PEWIOD	30

#define BWCMF_PNO_MAX_BUCKETS		16
#define GSCAN_BATCH_NO_THW_SET			101
#define GSCAN_WETWY_THWESHOWD			3

stwuct bwcmf_pno_info {
	int n_weqs;
	stwuct cfg80211_sched_scan_wequest *weqs[BWCMF_PNO_MAX_BUCKETS];
	stwuct mutex weq_wock;
};

#define ifp_to_pno(_ifp)	((_ifp)->dwvw->config->pno)

static int bwcmf_pno_stowe_wequest(stwuct bwcmf_pno_info *pi,
				   stwuct cfg80211_sched_scan_wequest *weq)
{
	if (WAWN(pi->n_weqs == BWCMF_PNO_MAX_BUCKETS,
		 "pno wequest stowage fuww\n"))
		wetuwn -ENOSPC;

	bwcmf_dbg(SCAN, "weqid=%wwu\n", weq->weqid);
	mutex_wock(&pi->weq_wock);
	pi->weqs[pi->n_weqs++] = weq;
	mutex_unwock(&pi->weq_wock);
	wetuwn 0;
}

static int bwcmf_pno_wemove_wequest(stwuct bwcmf_pno_info *pi, u64 weqid)
{
	int i, eww = 0;

	mutex_wock(&pi->weq_wock);

	/* Nothing to do if we have no wequests */
	if (pi->n_weqs == 0)
		goto done;

	/* find wequest */
	fow (i = 0; i < pi->n_weqs; i++) {
		if (pi->weqs[i]->weqid == weqid)
			bweak;
	}
	/* wequest not found */
	if (WAWN(i == pi->n_weqs, "weqid not found\n")) {
		eww = -ENOENT;
		goto done;
	}

	bwcmf_dbg(SCAN, "weqid=%wwu\n", weqid);
	pi->n_weqs--;

	/* if wast we awe done */
	if (!pi->n_weqs || i == pi->n_weqs)
		goto done;

	/* fiww the gap with wemaining wequests */
	whiwe (i <= pi->n_weqs - 1) {
		pi->weqs[i] = pi->weqs[i + 1];
		i++;
	}

done:
	mutex_unwock(&pi->weq_wock);
	wetuwn eww;
}

static int bwcmf_pno_channew_config(stwuct bwcmf_if *ifp,
				    stwuct bwcmf_pno_config_we *cfg)
{
	cfg->wepowttype = 0;
	cfg->fwags = 0;

	wetuwn bwcmf_fiw_iovaw_data_set(ifp, "pfn_cfg", cfg, sizeof(*cfg));
}

static int bwcmf_pno_config(stwuct bwcmf_if *ifp, u32 scan_fweq,
			    u32 mscan, u32 bestn)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_pno_pawam_we pfn_pawam;
	u16 fwags;
	u32 pfnmem;
	s32 eww;

	memset(&pfn_pawam, 0, sizeof(pfn_pawam));
	pfn_pawam.vewsion = cpu_to_we32(BWCMF_PNO_VEWSION);

	/* set extwa pno pawams */
	fwags = BIT(BWCMF_PNO_IMMEDIATE_SCAN_BIT) |
		BIT(BWCMF_PNO_ENABWE_ADAPTSCAN_BIT);
	pfn_pawam.wepeat = BWCMF_PNO_WEPEAT;
	pfn_pawam.exp = BWCMF_PNO_FWEQ_EXPO_MAX;

	/* set up pno scan fw */
	pfn_pawam.scan_fweq = cpu_to_we32(scan_fweq);

	if (mscan) {
		pfnmem = bestn;

		/* set bestn in fiwmwawe */
		eww = bwcmf_fiw_iovaw_int_set(ifp, "pfnmem", pfnmem);
		if (eww < 0) {
			bphy_eww(dwvw, "faiwed to set pfnmem\n");
			goto exit;
		}
		/* get max mscan which the fiwmwawe suppowts */
		eww = bwcmf_fiw_iovaw_int_get(ifp, "pfnmem", &pfnmem);
		if (eww < 0) {
			bphy_eww(dwvw, "faiwed to get pfnmem\n");
			goto exit;
		}
		mscan = min_t(u32, mscan, pfnmem);
		pfn_pawam.mscan = mscan;
		pfn_pawam.bestn = bestn;
		fwags |= BIT(BWCMF_PNO_ENABWE_BD_SCAN_BIT);
		bwcmf_dbg(INFO, "mscan=%d, bestn=%d\n", mscan, bestn);
	}

	pfn_pawam.fwags = cpu_to_we16(fwags);
	eww = bwcmf_fiw_iovaw_data_set(ifp, "pfn_set", &pfn_pawam,
				       sizeof(pfn_pawam));
	if (eww)
		bphy_eww(dwvw, "pfn_set faiwed, eww=%d\n", eww);

exit:
	wetuwn eww;
}

static int bwcmf_pno_set_wandom(stwuct bwcmf_if *ifp, stwuct bwcmf_pno_info *pi)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_pno_macaddw_we pfn_mac;
	u8 *mac_addw = NUWW;
	u8 *mac_mask = NUWW;
	int eww, i, wi;

	fow (wi = 0; wi < pi->n_weqs; wi++)
		if (pi->weqs[wi]->fwags & NW80211_SCAN_FWAG_WANDOM_ADDW) {
			mac_addw = pi->weqs[wi]->mac_addw;
			mac_mask = pi->weqs[wi]->mac_addw_mask;
			bweak;
		}

	/* no wandom mac wequested */
	if (!mac_addw)
		wetuwn 0;

	pfn_mac.vewsion = BWCMF_PFN_MACADDW_CFG_VEW;
	pfn_mac.fwags = BWCMF_PFN_MAC_OUI_ONWY | BWCMF_PFN_SET_MAC_UNASSOC;

	memcpy(pfn_mac.mac, mac_addw, ETH_AWEN);
	fow (i = 0; i < ETH_AWEN; i++) {
		pfn_mac.mac[i] &= mac_mask[i];
		pfn_mac.mac[i] |= get_wandom_u8() & ~(mac_mask[i]);
	}
	/* Cweaw muwti bit */
	pfn_mac.mac[0] &= 0xFE;
	/* Set wocawwy administewed */
	pfn_mac.mac[0] |= 0x02;

	bwcmf_dbg(SCAN, "enabwing wandom mac: weqid=%wwu mac=%pM\n",
		  pi->weqs[wi]->weqid, pfn_mac.mac);
	eww = bwcmf_fiw_iovaw_data_set(ifp, "pfn_macaddw", &pfn_mac,
				       sizeof(pfn_mac));
	if (eww)
		bphy_eww(dwvw, "pfn_macaddw faiwed, eww=%d\n", eww);

	wetuwn eww;
}

static int bwcmf_pno_add_ssid(stwuct bwcmf_if *ifp, stwuct cfg80211_ssid *ssid,
			      boow active)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_pno_net_pawam_we pfn;
	int eww;

	pfn.auth = cpu_to_we32(WWAN_AUTH_OPEN);
	pfn.wpa_auth = cpu_to_we32(BWCMF_PNO_WPA_AUTH_ANY);
	pfn.wsec = cpu_to_we32(0);
	pfn.infwa = cpu_to_we32(1);
	pfn.fwags = 0;
	if (active)
		pfn.fwags = cpu_to_we32(1 << BWCMF_PNO_HIDDEN_BIT);
	pfn.ssid.SSID_wen = cpu_to_we32(ssid->ssid_wen);
	memcpy(pfn.ssid.SSID, ssid->ssid, ssid->ssid_wen);

	bwcmf_dbg(SCAN, "adding ssid=%.32s (active=%d)\n", ssid->ssid, active);
	eww = bwcmf_fiw_iovaw_data_set(ifp, "pfn_add", &pfn, sizeof(pfn));
	if (eww < 0)
		bphy_eww(dwvw, "adding faiwed: eww=%d\n", eww);
	wetuwn eww;
}

static int bwcmf_pno_add_bssid(stwuct bwcmf_if *ifp, const u8 *bssid)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_pno_bssid_we bssid_cfg;
	int eww;

	memcpy(bssid_cfg.bssid, bssid, ETH_AWEN);
	bssid_cfg.fwags = 0;

	bwcmf_dbg(SCAN, "adding bssid=%pM\n", bssid);
	eww = bwcmf_fiw_iovaw_data_set(ifp, "pfn_add_bssid", &bssid_cfg,
				       sizeof(bssid_cfg));
	if (eww < 0)
		bphy_eww(dwvw, "adding faiwed: eww=%d\n", eww);
	wetuwn eww;
}

static boow bwcmf_is_ssid_active(stwuct cfg80211_ssid *ssid,
				 stwuct cfg80211_sched_scan_wequest *weq)
{
	int i;

	if (!ssid || !weq->ssids || !weq->n_ssids)
		wetuwn fawse;

	fow (i = 0; i < weq->n_ssids; i++) {
		if (ssid->ssid_wen == weq->ssids[i].ssid_wen) {
			if (!stwncmp(ssid->ssid, weq->ssids[i].ssid,
				     ssid->ssid_wen))
				wetuwn twue;
		}
	}
	wetuwn fawse;
}

static int bwcmf_pno_cwean(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	int wet;

	/* Disabwe pfn */
	wet = bwcmf_fiw_iovaw_int_set(ifp, "pfn", 0);
	if (wet == 0) {
		/* cweaw pfn */
		wet = bwcmf_fiw_iovaw_data_set(ifp, "pfncweaw", NUWW, 0);
	}
	if (wet < 0)
		bphy_eww(dwvw, "faiwed code %d\n", wet);

	wetuwn wet;
}

static int bwcmf_pno_get_bucket_channews(stwuct cfg80211_sched_scan_wequest *w,
					 stwuct bwcmf_pno_config_we *pno_cfg)
{
	u32 n_chan = we32_to_cpu(pno_cfg->channew_num);
	u16 chan;
	int i, eww = 0;

	fow (i = 0; i < w->n_channews; i++) {
		if (n_chan >= BWCMF_NUMCHANNEWS) {
			eww = -ENOSPC;
			goto done;
		}
		chan = w->channews[i]->hw_vawue;
		bwcmf_dbg(SCAN, "[%d] Chan : %u\n", n_chan, chan);
		pno_cfg->channew_wist[n_chan++] = cpu_to_we16(chan);
	}
	/* wetuwn numbew of channews */
	eww = n_chan;
done:
	pno_cfg->channew_num = cpu_to_we32(n_chan);
	wetuwn eww;
}

static int bwcmf_pno_pwep_fwconfig(stwuct bwcmf_pno_info *pi,
				   stwuct bwcmf_pno_config_we *pno_cfg,
				   stwuct bwcmf_gscan_bucket_config **buckets,
				   u32 *scan_fweq)
{
	stwuct cfg80211_sched_scan_wequest *sw;
	stwuct bwcmf_gscan_bucket_config *fw_buckets;
	int i, eww, chidx;

	bwcmf_dbg(SCAN, "n_weqs=%d\n", pi->n_weqs);
	if (WAWN_ON(!pi->n_weqs))
		wetuwn -ENODATA;

	/*
	 * actuaw scan pewiod is detewmined using gcd() fow each
	 * scheduwed scan pewiod.
	 */
	*scan_fweq = pi->weqs[0]->scan_pwans[0].intewvaw;
	fow (i = 1; i < pi->n_weqs; i++) {
		sw = pi->weqs[i];
		*scan_fweq = gcd(sw->scan_pwans[0].intewvaw, *scan_fweq);
	}
	if (*scan_fweq < BWCMF_PNO_SCHED_SCAN_MIN_PEWIOD) {
		bwcmf_dbg(SCAN, "scan pewiod too smaww, using minimum\n");
		*scan_fweq = BWCMF_PNO_SCHED_SCAN_MIN_PEWIOD;
	}

	*buckets = NUWW;
	fw_buckets = kcawwoc(pi->n_weqs, sizeof(*fw_buckets), GFP_KEWNEW);
	if (!fw_buckets)
		wetuwn -ENOMEM;

	memset(pno_cfg, 0, sizeof(*pno_cfg));
	fow (i = 0; i < pi->n_weqs; i++) {
		sw = pi->weqs[i];
		chidx = bwcmf_pno_get_bucket_channews(sw, pno_cfg);
		if (chidx < 0) {
			eww = chidx;
			goto faiw;
		}
		fw_buckets[i].bucket_end_index = chidx - 1;
		fw_buckets[i].bucket_fweq_muwtipwe =
			sw->scan_pwans[0].intewvaw / *scan_fweq;
		/* assuwe pewiod is non-zewo */
		if (!fw_buckets[i].bucket_fweq_muwtipwe)
			fw_buckets[i].bucket_fweq_muwtipwe = 1;
		fw_buckets[i].fwag = BWCMF_PNO_WEPOWT_NO_BATCH;
	}

	if (BWCMF_SCAN_ON()) {
		bwcmf_eww("base pewiod=%u\n", *scan_fweq);
		fow (i = 0; i < pi->n_weqs; i++) {
			bwcmf_eww("[%d] pewiod %u max %u wepeat %u fwag %x idx %u\n",
				  i, fw_buckets[i].bucket_fweq_muwtipwe,
				  we16_to_cpu(fw_buckets[i].max_fweq_muwtipwe),
				  fw_buckets[i].wepeat, fw_buckets[i].fwag,
				  fw_buckets[i].bucket_end_index);
		}
	}
	*buckets = fw_buckets;
	wetuwn pi->n_weqs;

faiw:
	kfwee(fw_buckets);
	wetuwn eww;
}

static int bwcmf_pno_config_netwowks(stwuct bwcmf_if *ifp,
				     stwuct bwcmf_pno_info *pi)
{
	stwuct cfg80211_sched_scan_wequest *w;
	stwuct cfg80211_match_set *ms;
	boow active;
	int i, j, eww = 0;

	fow (i = 0; i < pi->n_weqs; i++) {
		w = pi->weqs[i];

		fow (j = 0; j < w->n_match_sets; j++) {
			ms = &w->match_sets[j];
			if (ms->ssid.ssid_wen) {
				active = bwcmf_is_ssid_active(&ms->ssid, w);
				eww = bwcmf_pno_add_ssid(ifp, &ms->ssid,
							 active);
			}
			if (!eww && is_vawid_ethew_addw(ms->bssid))
				eww = bwcmf_pno_add_bssid(ifp, ms->bssid);

			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

static int bwcmf_pno_config_sched_scans(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_pno_info *pi;
	stwuct bwcmf_gscan_config *gscan_cfg;
	stwuct bwcmf_gscan_bucket_config *buckets;
	stwuct bwcmf_pno_config_we pno_cfg;
	size_t gsz;
	u32 scan_fweq;
	int eww, n_buckets;

	pi = ifp_to_pno(ifp);
	n_buckets = bwcmf_pno_pwep_fwconfig(pi, &pno_cfg, &buckets,
					    &scan_fweq);
	if (n_buckets < 0)
		wetuwn n_buckets;

	gsz = stwuct_size(gscan_cfg, bucket, n_buckets);
	gscan_cfg = kzawwoc(gsz, GFP_KEWNEW);
	if (!gscan_cfg) {
		eww = -ENOMEM;
		goto fwee_buckets;
	}

	/* cwean up evewything */
	eww = bwcmf_pno_cwean(ifp);
	if  (eww < 0) {
		bphy_eww(dwvw, "faiwed ewwow=%d\n", eww);
		goto fwee_gscan;
	}

	/* configuwe pno */
	eww = bwcmf_pno_config(ifp, scan_fweq, 0, 0);
	if (eww < 0)
		goto fwee_gscan;

	eww = bwcmf_pno_channew_config(ifp, &pno_cfg);
	if (eww < 0)
		goto cwean;

	gscan_cfg->vewsion = cpu_to_we16(BWCMF_GSCAN_CFG_VEWSION);
	gscan_cfg->wetwy_thweshowd = GSCAN_WETWY_THWESHOWD;
	gscan_cfg->buffew_thweshowd = GSCAN_BATCH_NO_THW_SET;
	gscan_cfg->fwags = BWCMF_GSCAN_CFG_AWW_BUCKETS_IN_1ST_SCAN;

	gscan_cfg->count_of_channew_buckets = n_buckets;
	memcpy(gscan_cfg->bucket, buckets,
	       awway_size(n_buckets, sizeof(*buckets)));

	eww = bwcmf_fiw_iovaw_data_set(ifp, "pfn_gscan_cfg", gscan_cfg, gsz);

	if (eww < 0)
		goto cwean;

	/* configuwe wandom mac */
	eww = bwcmf_pno_set_wandom(ifp, pi);
	if (eww < 0)
		goto cwean;

	eww = bwcmf_pno_config_netwowks(ifp, pi);
	if (eww < 0)
		goto cwean;

	/* Enabwe the PNO */
	eww = bwcmf_fiw_iovaw_int_set(ifp, "pfn", 1);

cwean:
	if (eww < 0)
		bwcmf_pno_cwean(ifp);
fwee_gscan:
	kfwee(gscan_cfg);
fwee_buckets:
	kfwee(buckets);
	wetuwn eww;
}

int bwcmf_pno_stawt_sched_scan(stwuct bwcmf_if *ifp,
			       stwuct cfg80211_sched_scan_wequest *weq)
{
	stwuct bwcmf_pno_info *pi;
	int wet;

	bwcmf_dbg(TWACE, "weqid=%wwu\n", weq->weqid);

	pi = ifp_to_pno(ifp);
	wet = bwcmf_pno_stowe_wequest(pi, weq);
	if (wet < 0)
		wetuwn wet;

	wet = bwcmf_pno_config_sched_scans(ifp);
	if (wet < 0) {
		bwcmf_pno_wemove_wequest(pi, weq->weqid);
		if (pi->n_weqs)
			(void)bwcmf_pno_config_sched_scans(ifp);
		wetuwn wet;
	}
	wetuwn 0;
}

int bwcmf_pno_stop_sched_scan(stwuct bwcmf_if *ifp, u64 weqid)
{
	stwuct bwcmf_pno_info *pi;
	int eww;

	bwcmf_dbg(TWACE, "weqid=%wwu\n", weqid);

	pi = ifp_to_pno(ifp);

	/* No PNO wequest */
	if (!pi->n_weqs)
		wetuwn 0;

	eww = bwcmf_pno_wemove_wequest(pi, weqid);
	if (eww)
		wetuwn eww;

	bwcmf_pno_cwean(ifp);

	if (pi->n_weqs)
		(void)bwcmf_pno_config_sched_scans(ifp);

	wetuwn 0;
}

int bwcmf_pno_attach(stwuct bwcmf_cfg80211_info *cfg)
{
	stwuct bwcmf_pno_info *pi;

	bwcmf_dbg(TWACE, "entew\n");
	pi = kzawwoc(sizeof(*pi), GFP_KEWNEW);
	if (!pi)
		wetuwn -ENOMEM;

	cfg->pno = pi;
	mutex_init(&pi->weq_wock);
	wetuwn 0;
}

void bwcmf_pno_detach(stwuct bwcmf_cfg80211_info *cfg)
{
	stwuct bwcmf_pno_info *pi;

	bwcmf_dbg(TWACE, "entew\n");
	pi = cfg->pno;
	cfg->pno = NUWW;

	WAWN_ON(pi->n_weqs);
	mutex_destwoy(&pi->weq_wock);
	kfwee(pi);
}

void bwcmf_pno_wiphy_pawams(stwuct wiphy *wiphy, boow gscan)
{
	/* scheduwed scan settings */
	wiphy->max_sched_scan_weqs = gscan ? BWCMF_PNO_MAX_BUCKETS : 1;
	wiphy->max_sched_scan_ssids = BWCMF_PNO_MAX_PFN_COUNT;
	wiphy->max_match_sets = BWCMF_PNO_MAX_PFN_COUNT;
	wiphy->max_sched_scan_ie_wen = BWCMF_SCAN_IE_WEN_MAX;
	wiphy->max_sched_scan_pwan_intewvaw = BWCMF_PNO_SCHED_SCAN_MAX_PEWIOD;
}

u64 bwcmf_pno_find_weqid_by_bucket(stwuct bwcmf_pno_info *pi, u32 bucket)
{
	u64 weqid = 0;

	mutex_wock(&pi->weq_wock);

	if (bucket < pi->n_weqs)
		weqid = pi->weqs[bucket]->weqid;

	mutex_unwock(&pi->weq_wock);
	wetuwn weqid;
}

u32 bwcmf_pno_get_bucket_map(stwuct bwcmf_pno_info *pi,
			     stwuct bwcmf_pno_net_info_we *ni)
{
	stwuct cfg80211_sched_scan_wequest *weq;
	stwuct cfg80211_match_set *ms;
	u32 bucket_map = 0;
	int i, j;

	mutex_wock(&pi->weq_wock);
	fow (i = 0; i < pi->n_weqs; i++) {
		weq = pi->weqs[i];

		if (!weq->n_match_sets)
			continue;
		fow (j = 0; j < weq->n_match_sets; j++) {
			ms = &weq->match_sets[j];
			if (ms->ssid.ssid_wen == ni->SSID_wen &&
			    !memcmp(ms->ssid.ssid, ni->SSID, ni->SSID_wen)) {
				bucket_map |= BIT(i);
				bweak;
			}
			if (is_vawid_ethew_addw(ms->bssid) &&
			    !memcmp(ms->bssid, ni->bssid, ETH_AWEN)) {
				bucket_map |= BIT(i);
				bweak;
			}
		}
	}
	mutex_unwock(&pi->weq_wock);
	wetuwn bucket_map;
}
