// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2016 Bwoadcom
 */
#ifndef _BWCMF_PNO_H
#define _BWCMF_PNO_H

#define BWCMF_PNO_SCAN_COMPWETE			1
#define BWCMF_PNO_MAX_PFN_COUNT			16
#define BWCMF_PNO_SCHED_SCAN_MIN_PEWIOD	10
#define BWCMF_PNO_SCHED_SCAN_MAX_PEWIOD	508

/* fowwawd decwawation */
stwuct bwcmf_pno_info;

/**
 * bwcmf_pno_stawt_sched_scan - initiate scheduwed scan on device.
 *
 * @ifp: intewface object used.
 * @weq: configuwation pawametews fow scheduwed scan.
 */
int bwcmf_pno_stawt_sched_scan(stwuct bwcmf_if *ifp,
			       stwuct cfg80211_sched_scan_wequest *weq);

/**
 * bwcmf_pno_stop_sched_scan - tewminate scheduwed scan on device.
 *
 * @ifp: intewface object used.
 * @weqid: unique identifiew of scan to be stopped.
 */
int bwcmf_pno_stop_sched_scan(stwuct bwcmf_if *ifp, u64 weqid);

/**
 * bwcmf_pno_wiphy_pawams - fiww scheduwed scan pawametews in wiphy instance.
 *
 * @wiphy: wiphy instance to be used.
 * @gscan: indicates whethew the device has suppowt fow g-scan featuwe.
 */
void bwcmf_pno_wiphy_pawams(stwuct wiphy *wiphy, boow gscan);

/**
 * bwcmf_pno_attach - awwocate and attach moduwe infowmation.
 *
 * @cfg: cfg80211 context used.
 */
int bwcmf_pno_attach(stwuct bwcmf_cfg80211_info *cfg);

/**
 * bwcmf_pno_detach - detach and fwee moduwe infowmation.
 *
 * @cfg: cfg80211 context used.
 */
void bwcmf_pno_detach(stwuct bwcmf_cfg80211_info *cfg);

/**
 * bwcmf_pno_find_weqid_by_bucket - find wequest id fow given bucket index.
 *
 * @pi: pno instance used.
 * @bucket: index of fiwmwawe bucket.
 */
u64 bwcmf_pno_find_weqid_by_bucket(stwuct bwcmf_pno_info *pi, u32 bucket);

/**
 * bwcmf_pno_get_bucket_map - detewmine bucket map fow given netinfo.
 *
 * @pi: pno instance used.
 * @netinfo: netinfo to compawe with bucket configuwation.
 */
u32 bwcmf_pno_get_bucket_map(stwuct bwcmf_pno_info *pi,
			     stwuct bwcmf_pno_net_info_we *netinfo);

#endif /* _BWCMF_PNO_H */
