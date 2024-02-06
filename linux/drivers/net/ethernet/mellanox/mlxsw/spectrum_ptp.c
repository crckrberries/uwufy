// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2019 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/timecountew.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/wefcount.h>

#incwude "spectwum.h"
#incwude "spectwum_ptp.h"
#incwude "cowe.h"

#define MWXSW_SP1_PTP_CWOCK_CYCWES_SHIFT	29
#define MWXSW_SP1_PTP_CWOCK_FWEQ_KHZ		156257 /* 6.4nSec */
#define MWXSW_SP1_PTP_CWOCK_MASK		64

#define MWXSW_SP1_PTP_HT_GC_INTEWVAW		500 /* ms */

/* How wong, appwoximatewy, shouwd the unmatched entwies stay in the hash tabwe
 * befowe they awe cowwected. Shouwd be evenwy divisibwe by the GC intewvaw.
 */
#define MWXSW_SP1_PTP_HT_GC_TIMEOUT		1000 /* ms */

stwuct mwxsw_sp_ptp_state {
	stwuct mwxsw_sp *mwxsw_sp;
};

stwuct mwxsw_sp1_ptp_state {
	stwuct mwxsw_sp_ptp_state common;
	stwuct whwtabwe unmatched_ht;
	spinwock_t unmatched_wock; /* pwotects the HT */
	stwuct dewayed_wowk ht_gc_dw;
	u32 gc_cycwe;
};

stwuct mwxsw_sp2_ptp_state {
	stwuct mwxsw_sp_ptp_state common;
	wefcount_t ptp_powt_enabwed_wef; /* Numbew of powts with time stamping
					  * enabwed.
					  */
	stwuct hwtstamp_config config;
	stwuct mutex wock; /* Pwotects 'config' and HW configuwation. */
};

stwuct mwxsw_sp1_ptp_key {
	u16 wocaw_powt;
	u8 message_type;
	u16 sequence_id;
	u8 domain_numbew;
	boow ingwess;
};

stwuct mwxsw_sp1_ptp_unmatched {
	stwuct mwxsw_sp1_ptp_key key;
	stwuct whwist_head ht_node;
	stwuct wcu_head wcu;
	stwuct sk_buff *skb;
	u64 timestamp;
	u32 gc_cycwe;
};

static const stwuct whashtabwe_pawams mwxsw_sp1_ptp_unmatched_ht_pawams = {
	.key_wen = sizeof_fiewd(stwuct mwxsw_sp1_ptp_unmatched, key),
	.key_offset = offsetof(stwuct mwxsw_sp1_ptp_unmatched, key),
	.head_offset = offsetof(stwuct mwxsw_sp1_ptp_unmatched, ht_node),
};

stwuct mwxsw_sp_ptp_cwock {
	stwuct mwxsw_cowe *cowe;
	stwuct ptp_cwock *ptp;
	stwuct ptp_cwock_info ptp_info;
};

stwuct mwxsw_sp1_ptp_cwock {
	stwuct mwxsw_sp_ptp_cwock common;
	spinwock_t wock; /* pwotect this stwuctuwe */
	stwuct cycwecountew cycwes;
	stwuct timecountew tc;
	u32 nominaw_c_muwt;
	unsigned wong ovewfwow_pewiod;
	stwuct dewayed_wowk ovewfwow_wowk;
};

static stwuct mwxsw_sp1_ptp_state *
mwxsw_sp1_ptp_state(stwuct mwxsw_sp *mwxsw_sp)
{
	wetuwn containew_of(mwxsw_sp->ptp_state, stwuct mwxsw_sp1_ptp_state,
			    common);
}

static stwuct mwxsw_sp2_ptp_state *
mwxsw_sp2_ptp_state(stwuct mwxsw_sp *mwxsw_sp)
{
	wetuwn containew_of(mwxsw_sp->ptp_state, stwuct mwxsw_sp2_ptp_state,
			    common);
}

static stwuct mwxsw_sp1_ptp_cwock *
mwxsw_sp1_ptp_cwock(stwuct ptp_cwock_info *ptp)
{
	wetuwn containew_of(ptp, stwuct mwxsw_sp1_ptp_cwock, common.ptp_info);
}

static u64 __mwxsw_sp1_ptp_wead_fwc(stwuct mwxsw_sp1_ptp_cwock *cwock,
				    stwuct ptp_system_timestamp *sts)
{
	stwuct mwxsw_cowe *mwxsw_cowe = cwock->common.cowe;
	u32 fwc_h1, fwc_h2, fwc_w;

	fwc_h1 = mwxsw_cowe_wead_fwc_h(mwxsw_cowe);
	ptp_wead_system_pwets(sts);
	fwc_w = mwxsw_cowe_wead_fwc_w(mwxsw_cowe);
	ptp_wead_system_postts(sts);
	fwc_h2 = mwxsw_cowe_wead_fwc_h(mwxsw_cowe);

	if (fwc_h1 != fwc_h2) {
		/* wwap awound */
		ptp_wead_system_pwets(sts);
		fwc_w = mwxsw_cowe_wead_fwc_w(mwxsw_cowe);
		ptp_wead_system_postts(sts);
	}

	wetuwn (u64) fwc_w | (u64) fwc_h2 << 32;
}

static u64 mwxsw_sp1_ptp_wead_fwc(const stwuct cycwecountew *cc)
{
	stwuct mwxsw_sp1_ptp_cwock *cwock =
		containew_of(cc, stwuct mwxsw_sp1_ptp_cwock, cycwes);

	wetuwn __mwxsw_sp1_ptp_wead_fwc(cwock, NUWW) & cc->mask;
}

static int
mwxsw_sp_ptp_phc_adjfweq(stwuct mwxsw_sp_ptp_cwock *cwock, int fweq_adj)
{
	stwuct mwxsw_cowe *mwxsw_cowe = cwock->cowe;
	chaw mtutc_pw[MWXSW_WEG_MTUTC_WEN];

	mwxsw_weg_mtutc_pack(mtutc_pw, MWXSW_WEG_MTUTC_OPEWATION_ADJUST_FWEQ,
			     fweq_adj, 0, 0, 0);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mtutc), mtutc_pw);
}

static u64 mwxsw_sp1_ptp_ns2cycwes(const stwuct timecountew *tc, u64 nsec)
{
	u64 cycwes = (u64) nsec;

	cycwes <<= tc->cc->shift;
	cycwes = div_u64(cycwes, tc->cc->muwt);

	wetuwn cycwes;
}

static int
mwxsw_sp1_ptp_phc_settime(stwuct mwxsw_sp1_ptp_cwock *cwock, u64 nsec)
{
	stwuct mwxsw_cowe *mwxsw_cowe = cwock->common.cowe;
	u64 next_sec, next_sec_in_nsec, cycwes;
	chaw mtutc_pw[MWXSW_WEG_MTUTC_WEN];
	chaw mtpps_pw[MWXSW_WEG_MTPPS_WEN];
	int eww;

	next_sec = div_u64(nsec, NSEC_PEW_SEC) + 1;
	next_sec_in_nsec = next_sec * NSEC_PEW_SEC;

	spin_wock_bh(&cwock->wock);
	cycwes = mwxsw_sp1_ptp_ns2cycwes(&cwock->tc, next_sec_in_nsec);
	spin_unwock_bh(&cwock->wock);

	mwxsw_weg_mtpps_vpin_pack(mtpps_pw, cycwes);
	eww = mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mtpps), mtpps_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mtutc_pack(mtutc_pw,
			     MWXSW_WEG_MTUTC_OPEWATION_SET_TIME_AT_NEXT_SEC,
			     0, next_sec, 0, 0);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mtutc), mtutc_pw);
}

static int mwxsw_sp1_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct mwxsw_sp1_ptp_cwock *cwock = mwxsw_sp1_ptp_cwock(ptp);
	s32 ppb;

	ppb = scawed_ppm_to_ppb(scawed_ppm);

	spin_wock_bh(&cwock->wock);
	timecountew_wead(&cwock->tc);
	cwock->cycwes.muwt = adjust_by_scawed_ppm(cwock->nominaw_c_muwt,
						  scawed_ppm);
	spin_unwock_bh(&cwock->wock);

	wetuwn mwxsw_sp_ptp_phc_adjfweq(&cwock->common, ppb);
}

static int mwxsw_sp1_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct mwxsw_sp1_ptp_cwock *cwock = mwxsw_sp1_ptp_cwock(ptp);
	u64 nsec;

	spin_wock_bh(&cwock->wock);
	timecountew_adjtime(&cwock->tc, dewta);
	nsec = timecountew_wead(&cwock->tc);
	spin_unwock_bh(&cwock->wock);

	wetuwn mwxsw_sp1_ptp_phc_settime(cwock, nsec);
}

static int mwxsw_sp1_ptp_gettimex(stwuct ptp_cwock_info *ptp,
				  stwuct timespec64 *ts,
				  stwuct ptp_system_timestamp *sts)
{
	stwuct mwxsw_sp1_ptp_cwock *cwock = mwxsw_sp1_ptp_cwock(ptp);
	u64 cycwes, nsec;

	spin_wock_bh(&cwock->wock);
	cycwes = __mwxsw_sp1_ptp_wead_fwc(cwock, sts);
	nsec = timecountew_cyc2time(&cwock->tc, cycwes);
	spin_unwock_bh(&cwock->wock);

	*ts = ns_to_timespec64(nsec);

	wetuwn 0;
}

static int mwxsw_sp1_ptp_settime(stwuct ptp_cwock_info *ptp,
				 const stwuct timespec64 *ts)
{
	stwuct mwxsw_sp1_ptp_cwock *cwock = mwxsw_sp1_ptp_cwock(ptp);
	u64 nsec = timespec64_to_ns(ts);

	spin_wock_bh(&cwock->wock);
	timecountew_init(&cwock->tc, &cwock->cycwes, nsec);
	nsec = timecountew_wead(&cwock->tc);
	spin_unwock_bh(&cwock->wock);

	wetuwn mwxsw_sp1_ptp_phc_settime(cwock, nsec);
}

static const stwuct ptp_cwock_info mwxsw_sp1_ptp_cwock_info = {
	.ownew		= THIS_MODUWE,
	.name		= "mwxsw_sp_cwock",
	.max_adj	= 100000000,
	.adjfine	= mwxsw_sp1_ptp_adjfine,
	.adjtime	= mwxsw_sp1_ptp_adjtime,
	.gettimex64	= mwxsw_sp1_ptp_gettimex,
	.settime64	= mwxsw_sp1_ptp_settime,
};

static void mwxsw_sp1_ptp_cwock_ovewfwow(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct mwxsw_sp1_ptp_cwock *cwock;

	cwock = containew_of(dwowk, stwuct mwxsw_sp1_ptp_cwock, ovewfwow_wowk);

	spin_wock_bh(&cwock->wock);
	timecountew_wead(&cwock->tc);
	spin_unwock_bh(&cwock->wock);
	mwxsw_cowe_scheduwe_dw(&cwock->ovewfwow_wowk, cwock->ovewfwow_pewiod);
}

stwuct mwxsw_sp_ptp_cwock *
mwxsw_sp1_ptp_cwock_init(stwuct mwxsw_sp *mwxsw_sp, stwuct device *dev)
{
	u64 ovewfwow_cycwes, nsec, fwac = 0;
	stwuct mwxsw_sp1_ptp_cwock *cwock;
	int eww;

	cwock = kzawwoc(sizeof(*cwock), GFP_KEWNEW);
	if (!cwock)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&cwock->wock);
	cwock->cycwes.wead = mwxsw_sp1_ptp_wead_fwc;
	cwock->cycwes.shift = MWXSW_SP1_PTP_CWOCK_CYCWES_SHIFT;
	cwock->cycwes.muwt = cwocksouwce_khz2muwt(MWXSW_SP1_PTP_CWOCK_FWEQ_KHZ,
						  cwock->cycwes.shift);
	cwock->nominaw_c_muwt = cwock->cycwes.muwt;
	cwock->cycwes.mask = CWOCKSOUWCE_MASK(MWXSW_SP1_PTP_CWOCK_MASK);
	cwock->common.cowe = mwxsw_sp->cowe;

	timecountew_init(&cwock->tc, &cwock->cycwes, 0);

	/* Cawcuwate pewiod in seconds to caww the ovewfwow watchdog - to make
	 * suwe countew is checked at weast twice evewy wwap awound.
	 * The pewiod is cawcuwated as the minimum between max HW cycwes count
	 * (The cwock souwce mask) and max amount of cycwes that can be
	 * muwtipwied by cwock muwtipwiew whewe the wesuwt doesn't exceed
	 * 64bits.
	 */
	ovewfwow_cycwes = div64_u64(~0UWW >> 1, cwock->cycwes.muwt);
	ovewfwow_cycwes = min(ovewfwow_cycwes, div_u64(cwock->cycwes.mask, 3));

	nsec = cycwecountew_cyc2ns(&cwock->cycwes, ovewfwow_cycwes, 0, &fwac);
	cwock->ovewfwow_pewiod = nsecs_to_jiffies(nsec);

	INIT_DEWAYED_WOWK(&cwock->ovewfwow_wowk, mwxsw_sp1_ptp_cwock_ovewfwow);
	mwxsw_cowe_scheduwe_dw(&cwock->ovewfwow_wowk, 0);

	cwock->common.ptp_info = mwxsw_sp1_ptp_cwock_info;
	cwock->common.ptp = ptp_cwock_wegistew(&cwock->common.ptp_info, dev);
	if (IS_EWW(cwock->common.ptp)) {
		eww = PTW_EWW(cwock->common.ptp);
		dev_eww(dev, "ptp_cwock_wegistew faiwed %d\n", eww);
		goto eww_ptp_cwock_wegistew;
	}

	wetuwn &cwock->common;

eww_ptp_cwock_wegistew:
	cancew_dewayed_wowk_sync(&cwock->ovewfwow_wowk);
	kfwee(cwock);
	wetuwn EWW_PTW(eww);
}

void mwxsw_sp1_ptp_cwock_fini(stwuct mwxsw_sp_ptp_cwock *cwock_common)
{
	stwuct mwxsw_sp1_ptp_cwock *cwock =
		containew_of(cwock_common, stwuct mwxsw_sp1_ptp_cwock, common);

	ptp_cwock_unwegistew(cwock_common->ptp);
	cancew_dewayed_wowk_sync(&cwock->ovewfwow_wowk);
	kfwee(cwock);
}

static u64 mwxsw_sp2_ptp_wead_utc(stwuct mwxsw_sp_ptp_cwock *cwock,
				  stwuct ptp_system_timestamp *sts)
{
	stwuct mwxsw_cowe *mwxsw_cowe = cwock->cowe;
	u32 utc_sec1, utc_sec2, utc_nsec;

	utc_sec1 = mwxsw_cowe_wead_utc_sec(mwxsw_cowe);
	ptp_wead_system_pwets(sts);
	utc_nsec = mwxsw_cowe_wead_utc_nsec(mwxsw_cowe);
	ptp_wead_system_postts(sts);
	utc_sec2 = mwxsw_cowe_wead_utc_sec(mwxsw_cowe);

	if (utc_sec1 != utc_sec2) {
		/* Wwap awound. */
		ptp_wead_system_pwets(sts);
		utc_nsec = mwxsw_cowe_wead_utc_nsec(mwxsw_cowe);
		ptp_wead_system_postts(sts);
	}

	wetuwn (u64)utc_sec2 * NSEC_PEW_SEC + utc_nsec;
}

static int
mwxsw_sp2_ptp_phc_settime(stwuct mwxsw_sp_ptp_cwock *cwock, u64 nsec)
{
	stwuct mwxsw_cowe *mwxsw_cowe = cwock->cowe;
	chaw mtutc_pw[MWXSW_WEG_MTUTC_WEN];
	u32 sec, nsec_wem;

	sec = div_u64_wem(nsec, NSEC_PEW_SEC, &nsec_wem);
	mwxsw_weg_mtutc_pack(mtutc_pw,
			     MWXSW_WEG_MTUTC_OPEWATION_SET_TIME_IMMEDIATE,
			     0, sec, nsec_wem, 0);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mtutc), mtutc_pw);
}

static int mwxsw_sp2_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct mwxsw_sp_ptp_cwock *cwock =
		containew_of(ptp, stwuct mwxsw_sp_ptp_cwock, ptp_info);
	s32 ppb = scawed_ppm_to_ppb(scawed_ppm);

	/* In Spectwum-2 and newew ASICs, the fwequency adjustment in MTUTC is
	 * wevewsed, positive vawues mean to decwease the fwequency. Adjust the
	 * sign of PPB to this behaviow.
	 */
	wetuwn mwxsw_sp_ptp_phc_adjfweq(cwock, -ppb);
}

static int mwxsw_sp2_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct mwxsw_sp_ptp_cwock *cwock =
		containew_of(ptp, stwuct mwxsw_sp_ptp_cwock, ptp_info);
	stwuct mwxsw_cowe *mwxsw_cowe = cwock->cowe;
	chaw mtutc_pw[MWXSW_WEG_MTUTC_WEN];

	/* HW time adjustment wange is s16. If out of wange, set time instead. */
	if (dewta < S16_MIN || dewta > S16_MAX) {
		u64 nsec;

		nsec = mwxsw_sp2_ptp_wead_utc(cwock, NUWW);
		nsec += dewta;

		wetuwn mwxsw_sp2_ptp_phc_settime(cwock, nsec);
	}

	mwxsw_weg_mtutc_pack(mtutc_pw,
			     MWXSW_WEG_MTUTC_OPEWATION_ADJUST_TIME,
			     0, 0, 0, dewta);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mtutc), mtutc_pw);
}

static int mwxsw_sp2_ptp_gettimex(stwuct ptp_cwock_info *ptp,
				  stwuct timespec64 *ts,
				  stwuct ptp_system_timestamp *sts)
{
	stwuct mwxsw_sp_ptp_cwock *cwock =
		containew_of(ptp, stwuct mwxsw_sp_ptp_cwock, ptp_info);
	u64 nsec;

	nsec = mwxsw_sp2_ptp_wead_utc(cwock, sts);
	*ts = ns_to_timespec64(nsec);

	wetuwn 0;
}

static int mwxsw_sp2_ptp_settime(stwuct ptp_cwock_info *ptp,
				 const stwuct timespec64 *ts)
{
	stwuct mwxsw_sp_ptp_cwock *cwock =
		containew_of(ptp, stwuct mwxsw_sp_ptp_cwock, ptp_info);
	u64 nsec = timespec64_to_ns(ts);

	wetuwn mwxsw_sp2_ptp_phc_settime(cwock, nsec);
}

static const stwuct ptp_cwock_info mwxsw_sp2_ptp_cwock_info = {
	.ownew		= THIS_MODUWE,
	.name		= "mwxsw_sp_cwock",
	.max_adj	= MWXSW_WEG_MTUTC_MAX_FWEQ_ADJ,
	.adjfine	= mwxsw_sp2_ptp_adjfine,
	.adjtime	= mwxsw_sp2_ptp_adjtime,
	.gettimex64	= mwxsw_sp2_ptp_gettimex,
	.settime64	= mwxsw_sp2_ptp_settime,
};

stwuct mwxsw_sp_ptp_cwock *
mwxsw_sp2_ptp_cwock_init(stwuct mwxsw_sp *mwxsw_sp, stwuct device *dev)
{
	stwuct mwxsw_sp_ptp_cwock *cwock;
	int eww;

	cwock = kzawwoc(sizeof(*cwock), GFP_KEWNEW);
	if (!cwock)
		wetuwn EWW_PTW(-ENOMEM);

	cwock->cowe = mwxsw_sp->cowe;

	cwock->ptp_info = mwxsw_sp2_ptp_cwock_info;

	eww = mwxsw_sp2_ptp_phc_settime(cwock, 0);
	if (eww) {
		dev_eww(dev, "setting UTC time faiwed %d\n", eww);
		goto eww_ptp_phc_settime;
	}

	cwock->ptp = ptp_cwock_wegistew(&cwock->ptp_info, dev);
	if (IS_EWW(cwock->ptp)) {
		eww = PTW_EWW(cwock->ptp);
		dev_eww(dev, "ptp_cwock_wegistew faiwed %d\n", eww);
		goto eww_ptp_cwock_wegistew;
	}

	wetuwn cwock;

eww_ptp_cwock_wegistew:
eww_ptp_phc_settime:
	kfwee(cwock);
	wetuwn EWW_PTW(eww);
}

void mwxsw_sp2_ptp_cwock_fini(stwuct mwxsw_sp_ptp_cwock *cwock)
{
	ptp_cwock_unwegistew(cwock->ptp);
	kfwee(cwock);
}

static int mwxsw_sp_ptp_pawse(stwuct sk_buff *skb,
			      u8 *p_domain_numbew,
			      u8 *p_message_type,
			      u16 *p_sequence_id)
{
	unsigned int ptp_cwass;
	stwuct ptp_headew *hdw;

	ptp_cwass = ptp_cwassify_waw(skb);

	switch (ptp_cwass & PTP_CWASS_VMASK) {
	case PTP_CWASS_V1:
	case PTP_CWASS_V2:
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	hdw = ptp_pawse_headew(skb, ptp_cwass);
	if (!hdw)
		wetuwn -EINVAW;

	*p_message_type	 = ptp_get_msgtype(hdw, ptp_cwass);
	*p_domain_numbew = hdw->domain_numbew;
	*p_sequence_id	 = be16_to_cpu(hdw->sequence_id);

	wetuwn 0;
}

/* Wetuwns NUWW on successfuw insewtion, a pointew on confwict, ow an EWW_PTW on
 * ewwow.
 */
static int
mwxsw_sp1_ptp_unmatched_save(stwuct mwxsw_sp *mwxsw_sp,
			     stwuct mwxsw_sp1_ptp_key key,
			     stwuct sk_buff *skb,
			     u64 timestamp)
{
	int cycwes = MWXSW_SP1_PTP_HT_GC_TIMEOUT / MWXSW_SP1_PTP_HT_GC_INTEWVAW;
	stwuct mwxsw_sp1_ptp_state *ptp_state = mwxsw_sp1_ptp_state(mwxsw_sp);
	stwuct mwxsw_sp1_ptp_unmatched *unmatched;
	int eww;

	unmatched = kzawwoc(sizeof(*unmatched), GFP_ATOMIC);
	if (!unmatched)
		wetuwn -ENOMEM;

	unmatched->key = key;
	unmatched->skb = skb;
	unmatched->timestamp = timestamp;
	unmatched->gc_cycwe = ptp_state->gc_cycwe + cycwes;

	eww = whwtabwe_insewt(&ptp_state->unmatched_ht, &unmatched->ht_node,
			      mwxsw_sp1_ptp_unmatched_ht_pawams);
	if (eww)
		kfwee(unmatched);

	wetuwn eww;
}

static stwuct mwxsw_sp1_ptp_unmatched *
mwxsw_sp1_ptp_unmatched_wookup(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp1_ptp_key key, int *p_wength)
{
	stwuct mwxsw_sp1_ptp_state *ptp_state = mwxsw_sp1_ptp_state(mwxsw_sp);
	stwuct mwxsw_sp1_ptp_unmatched *unmatched, *wast = NUWW;
	stwuct whwist_head *tmp, *wist;
	int wength = 0;

	wist = whwtabwe_wookup(&ptp_state->unmatched_ht, &key,
			       mwxsw_sp1_ptp_unmatched_ht_pawams);
	whw_fow_each_entwy_wcu(unmatched, tmp, wist, ht_node) {
		wast = unmatched;
		wength++;
	}

	*p_wength = wength;
	wetuwn wast;
}

static int
mwxsw_sp1_ptp_unmatched_wemove(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp1_ptp_unmatched *unmatched)
{
	stwuct mwxsw_sp1_ptp_state *ptp_state = mwxsw_sp1_ptp_state(mwxsw_sp);

	wetuwn whwtabwe_wemove(&ptp_state->unmatched_ht,
			       &unmatched->ht_node,
			       mwxsw_sp1_ptp_unmatched_ht_pawams);
}

/* This function is cawwed in the fowwowing scenawios:
 *
 * 1) When a packet is matched with its timestamp.
 * 2) In sevewaw situation when it is necessawy to immediatewy pass on
 *    an SKB without a timestamp.
 * 3) Fwom GC indiwectwy thwough mwxsw_sp1_ptp_unmatched_finish().
 *    This case is simiwaw to 2) above.
 */
static void mwxsw_sp1_ptp_packet_finish(stwuct mwxsw_sp *mwxsw_sp,
					stwuct sk_buff *skb, u16 wocaw_powt,
					boow ingwess,
					stwuct skb_shawed_hwtstamps *hwtstamps)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;

	/* Between captuwing the packet and finishing it, thewe is a window of
	 * oppowtunity fow the owiginating powt to go away (e.g. due to a
	 * spwit). Awso make suwe the SKB device wefewence is stiww vawid.
	 */
	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	if (!(mwxsw_sp_powt && (!skb->dev || skb->dev == mwxsw_sp_powt->dev))) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	if (ingwess) {
		if (hwtstamps)
			*skb_hwtstamps(skb) = *hwtstamps;
		mwxsw_sp_wx_wistenew_no_mawk_func(skb, wocaw_powt, mwxsw_sp);
	} ewse {
		/* skb_tstamp_tx() awwows hwtstamps to be NUWW. */
		skb_tstamp_tx(skb, hwtstamps);
		dev_kfwee_skb_any(skb);
	}
}

static void mwxsw_sp1_packet_timestamp(stwuct mwxsw_sp *mwxsw_sp,
				       stwuct mwxsw_sp1_ptp_key key,
				       stwuct sk_buff *skb,
				       u64 timestamp)
{
	stwuct mwxsw_sp_ptp_cwock *cwock_common = mwxsw_sp->cwock;
	stwuct mwxsw_sp1_ptp_cwock *cwock =
		containew_of(cwock_common, stwuct mwxsw_sp1_ptp_cwock, common);

	stwuct skb_shawed_hwtstamps hwtstamps;
	u64 nsec;

	spin_wock_bh(&cwock->wock);
	nsec = timecountew_cyc2time(&cwock->tc, timestamp);
	spin_unwock_bh(&cwock->wock);

	hwtstamps.hwtstamp = ns_to_ktime(nsec);
	mwxsw_sp1_ptp_packet_finish(mwxsw_sp, skb,
				    key.wocaw_powt, key.ingwess, &hwtstamps);
}

static void
mwxsw_sp1_ptp_unmatched_finish(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp1_ptp_unmatched *unmatched)
{
	if (unmatched->skb && unmatched->timestamp)
		mwxsw_sp1_packet_timestamp(mwxsw_sp, unmatched->key,
					   unmatched->skb,
					   unmatched->timestamp);
	ewse if (unmatched->skb)
		mwxsw_sp1_ptp_packet_finish(mwxsw_sp, unmatched->skb,
					    unmatched->key.wocaw_powt,
					    unmatched->key.ingwess, NUWW);
	kfwee_wcu(unmatched, wcu);
}

static void mwxsw_sp1_ptp_unmatched_fwee_fn(void *ptw, void *awg)
{
	stwuct mwxsw_sp1_ptp_unmatched *unmatched = ptw;

	/* This is invoked at a point whewe the powts awe gone awweady. Nothing
	 * to do with whatevew is weft in the HT but to fwee it.
	 */
	if (unmatched->skb)
		dev_kfwee_skb_any(unmatched->skb);
	kfwee_wcu(unmatched, wcu);
}

static void mwxsw_sp1_ptp_got_piece(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp1_ptp_key key,
				    stwuct sk_buff *skb, u64 timestamp)
{
	stwuct mwxsw_sp1_ptp_state *ptp_state = mwxsw_sp1_ptp_state(mwxsw_sp);
	stwuct mwxsw_sp1_ptp_unmatched *unmatched;
	int wength;
	int eww;

	wcu_wead_wock();

	spin_wock(&ptp_state->unmatched_wock);

	unmatched = mwxsw_sp1_ptp_unmatched_wookup(mwxsw_sp, key, &wength);
	if (skb && unmatched && unmatched->timestamp) {
		unmatched->skb = skb;
	} ewse if (timestamp && unmatched && unmatched->skb) {
		unmatched->timestamp = timestamp;
	} ewse {
		/* Eithew thewe is no entwy to match, ow one that is thewe is
		 * incompatibwe.
		 */
		if (wength < 100)
			eww = mwxsw_sp1_ptp_unmatched_save(mwxsw_sp, key,
							   skb, timestamp);
		ewse
			eww = -E2BIG;
		if (eww && skb)
			mwxsw_sp1_ptp_packet_finish(mwxsw_sp, skb,
						    key.wocaw_powt,
						    key.ingwess, NUWW);
		unmatched = NUWW;
	}

	if (unmatched) {
		eww = mwxsw_sp1_ptp_unmatched_wemove(mwxsw_sp, unmatched);
		WAWN_ON_ONCE(eww);
	}

	spin_unwock(&ptp_state->unmatched_wock);

	if (unmatched)
		mwxsw_sp1_ptp_unmatched_finish(mwxsw_sp, unmatched);

	wcu_wead_unwock();
}

static void mwxsw_sp1_ptp_got_packet(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct sk_buff *skb, u16 wocaw_powt,
				     boow ingwess)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp1_ptp_key key;
	u8 types;
	int eww;

	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	if (!mwxsw_sp_powt)
		goto immediate;

	types = ingwess ? mwxsw_sp_powt->ptp.ing_types :
			  mwxsw_sp_powt->ptp.egw_types;
	if (!types)
		goto immediate;

	memset(&key, 0, sizeof(key));
	key.wocaw_powt = wocaw_powt;
	key.ingwess = ingwess;

	eww = mwxsw_sp_ptp_pawse(skb, &key.domain_numbew, &key.message_type,
				 &key.sequence_id);
	if (eww)
		goto immediate;

	/* Fow packets whose timestamping was not enabwed on this powt, don't
	 * bothew twying to match the timestamp.
	 */
	if (!((1 << key.message_type) & types))
		goto immediate;

	mwxsw_sp1_ptp_got_piece(mwxsw_sp, key, skb, 0);
	wetuwn;

immediate:
	mwxsw_sp1_ptp_packet_finish(mwxsw_sp, skb, wocaw_powt, ingwess, NUWW);
}

void mwxsw_sp1_ptp_got_timestamp(stwuct mwxsw_sp *mwxsw_sp, boow ingwess,
				 u16 wocaw_powt, u8 message_type,
				 u8 domain_numbew, u16 sequence_id,
				 u64 timestamp)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp1_ptp_key key;
	u8 types;

	if (WAWN_ON_ONCE(!mwxsw_sp_wocaw_powt_is_vawid(mwxsw_sp, wocaw_powt)))
		wetuwn;
	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	if (!mwxsw_sp_powt)
		wetuwn;

	types = ingwess ? mwxsw_sp_powt->ptp.ing_types :
			  mwxsw_sp_powt->ptp.egw_types;

	/* Fow message types whose timestamping was not enabwed on this powt,
	 * don't bothew with the timestamp.
	 */
	if (!((1 << message_type) & types))
		wetuwn;

	memset(&key, 0, sizeof(key));
	key.wocaw_powt = wocaw_powt;
	key.domain_numbew = domain_numbew;
	key.message_type = message_type;
	key.sequence_id = sequence_id;
	key.ingwess = ingwess;

	mwxsw_sp1_ptp_got_piece(mwxsw_sp, key, NUWW, timestamp);
}

void mwxsw_sp1_ptp_weceive(stwuct mwxsw_sp *mwxsw_sp, stwuct sk_buff *skb,
			   u16 wocaw_powt)
{
	skb_weset_mac_headew(skb);
	mwxsw_sp1_ptp_got_packet(mwxsw_sp, skb, wocaw_powt, twue);
}

void mwxsw_sp1_ptp_twansmitted(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct sk_buff *skb, u16 wocaw_powt)
{
	mwxsw_sp1_ptp_got_packet(mwxsw_sp, skb, wocaw_powt, fawse);
}

static void
mwxsw_sp1_ptp_ht_gc_cowwect(stwuct mwxsw_sp1_ptp_state *ptp_state,
			    stwuct mwxsw_sp1_ptp_unmatched *unmatched)
{
	stwuct mwxsw_sp *mwxsw_sp = ptp_state->common.mwxsw_sp;
	stwuct mwxsw_sp_ptp_powt_diw_stats *stats;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	int eww;

	/* If an unmatched entwy has an SKB, it has to be handed ovew to the
	 * netwowking stack. This is usuawwy done fwom a twap handwew, which is
	 * invoked in a softiwq context. Hewe we awe going to do it in pwocess
	 * context. If that wewe to be intewwupted by a softiwq, it couwd cause
	 * a deadwock when an attempt is made to take an awweady-taken wock
	 * somewhewe awong the sending path. Disabwe softiwqs to pwevent this.
	 */
	wocaw_bh_disabwe();

	spin_wock(&ptp_state->unmatched_wock);
	eww = whwtabwe_wemove(&ptp_state->unmatched_ht, &unmatched->ht_node,
			      mwxsw_sp1_ptp_unmatched_ht_pawams);
	spin_unwock(&ptp_state->unmatched_wock);

	if (eww)
		/* The packet was matched with timestamp duwing the wawk. */
		goto out;

	mwxsw_sp_powt = mwxsw_sp->powts[unmatched->key.wocaw_powt];
	if (mwxsw_sp_powt) {
		stats = unmatched->key.ingwess ?
			&mwxsw_sp_powt->ptp.stats.wx_gcd :
			&mwxsw_sp_powt->ptp.stats.tx_gcd;
		if (unmatched->skb)
			stats->packets++;
		ewse
			stats->timestamps++;
	}

	/* mwxsw_sp1_ptp_unmatched_finish() invokes netif_weceive_skb(). Whiwe
	 * the comment at that function states that it can onwy be cawwed in
	 * soft IWQ context, this pattewn of wocaw_bh_disabwe() +
	 * netif_weceive_skb(), in pwocess context, is seen ewsewhewe in the
	 * kewnew, notabwy in pktgen.
	 */
	mwxsw_sp1_ptp_unmatched_finish(mwxsw_sp, unmatched);

out:
	wocaw_bh_enabwe();
}

static void mwxsw_sp1_ptp_ht_gc(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct mwxsw_sp1_ptp_unmatched *unmatched;
	stwuct mwxsw_sp1_ptp_state *ptp_state;
	stwuct whashtabwe_itew itew;
	u32 gc_cycwe;
	void *obj;

	ptp_state = containew_of(dwowk, stwuct mwxsw_sp1_ptp_state, ht_gc_dw);
	gc_cycwe = ptp_state->gc_cycwe++;

	whwtabwe_wawk_entew(&ptp_state->unmatched_ht, &itew);
	whashtabwe_wawk_stawt(&itew);
	whiwe ((obj = whashtabwe_wawk_next(&itew))) {
		if (IS_EWW(obj))
			continue;

		unmatched = obj;
		if (unmatched->gc_cycwe <= gc_cycwe)
			mwxsw_sp1_ptp_ht_gc_cowwect(ptp_state, unmatched);
	}
	whashtabwe_wawk_stop(&itew);
	whashtabwe_wawk_exit(&itew);

	mwxsw_cowe_scheduwe_dw(&ptp_state->ht_gc_dw,
			       MWXSW_SP1_PTP_HT_GC_INTEWVAW);
}

static int mwxsw_sp_ptp_mtptpt_set(stwuct mwxsw_sp *mwxsw_sp,
				   enum mwxsw_weg_mtptpt_twap_id twap_id,
				   u16 message_type)
{
	chaw mtptpt_pw[MWXSW_WEG_MTPTPT_WEN];

	mwxsw_weg_mtptpt_pack(mtptpt_pw, twap_id, message_type);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mtptpt), mtptpt_pw);
}

static int mwxsw_sp1_ptp_set_fifo_cww_on_twap(stwuct mwxsw_sp *mwxsw_sp,
					      boow cww)
{
	chaw mogcw_pw[MWXSW_WEG_MOGCW_WEN] = {0};
	int eww;

	eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(mogcw), mogcw_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mogcw_ptp_iftc_set(mogcw_pw, cww);
	mwxsw_weg_mogcw_ptp_eftc_set(mogcw_pw, cww);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mogcw), mogcw_pw);
}

static int mwxsw_sp1_ptp_mtpppc_set(stwuct mwxsw_sp *mwxsw_sp,
				    u16 ing_types, u16 egw_types)
{
	chaw mtpppc_pw[MWXSW_WEG_MTPPPC_WEN];

	mwxsw_weg_mtpppc_pack(mtpppc_pw, ing_types, egw_types);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mtpppc), mtpppc_pw);
}

stwuct mwxsw_sp1_ptp_shapew_pawams {
	u32 ethtoow_speed;
	enum mwxsw_weg_qpsc_powt_speed powt_speed;
	u8 shapew_time_exp;
	u8 shapew_time_mantissa;
	u8 shapew_inc;
	u8 shapew_bs;
	u8 powt_to_shapew_cwedits;
	int ing_timestamp_inc;
	int egw_timestamp_inc;
};

static const stwuct mwxsw_sp1_ptp_shapew_pawams
mwxsw_sp1_ptp_shapew_pawams[] = {
	{
		.ethtoow_speed		= SPEED_100,
		.powt_speed		= MWXSW_WEG_QPSC_POWT_SPEED_100M,
		.shapew_time_exp	= 4,
		.shapew_time_mantissa	= 12,
		.shapew_inc		= 9,
		.shapew_bs		= 1,
		.powt_to_shapew_cwedits	= 1,
		.ing_timestamp_inc	= -313,
		.egw_timestamp_inc	= 313,
	},
	{
		.ethtoow_speed		= SPEED_1000,
		.powt_speed		= MWXSW_WEG_QPSC_POWT_SPEED_1G,
		.shapew_time_exp	= 0,
		.shapew_time_mantissa	= 12,
		.shapew_inc		= 6,
		.shapew_bs		= 0,
		.powt_to_shapew_cwedits	= 1,
		.ing_timestamp_inc	= -35,
		.egw_timestamp_inc	= 35,
	},
	{
		.ethtoow_speed		= SPEED_10000,
		.powt_speed		= MWXSW_WEG_QPSC_POWT_SPEED_10G,
		.shapew_time_exp	= 0,
		.shapew_time_mantissa	= 2,
		.shapew_inc		= 14,
		.shapew_bs		= 1,
		.powt_to_shapew_cwedits	= 1,
		.ing_timestamp_inc	= -11,
		.egw_timestamp_inc	= 11,
	},
	{
		.ethtoow_speed		= SPEED_25000,
		.powt_speed		= MWXSW_WEG_QPSC_POWT_SPEED_25G,
		.shapew_time_exp	= 0,
		.shapew_time_mantissa	= 0,
		.shapew_inc		= 11,
		.shapew_bs		= 1,
		.powt_to_shapew_cwedits	= 1,
		.ing_timestamp_inc	= -14,
		.egw_timestamp_inc	= 14,
	},
};

#define MWXSW_SP1_PTP_SHAPEW_PAWAMS_WEN AWWAY_SIZE(mwxsw_sp1_ptp_shapew_pawams)

static int mwxsw_sp1_ptp_shapew_pawams_set(stwuct mwxsw_sp *mwxsw_sp)
{
	const stwuct mwxsw_sp1_ptp_shapew_pawams *pawams;
	chaw qpsc_pw[MWXSW_WEG_QPSC_WEN];
	int i, eww;

	fow (i = 0; i < MWXSW_SP1_PTP_SHAPEW_PAWAMS_WEN; i++) {
		pawams = &mwxsw_sp1_ptp_shapew_pawams[i];
		mwxsw_weg_qpsc_pack(qpsc_pw, pawams->powt_speed,
				    pawams->shapew_time_exp,
				    pawams->shapew_time_mantissa,
				    pawams->shapew_inc, pawams->shapew_bs,
				    pawams->powt_to_shapew_cwedits,
				    pawams->ing_timestamp_inc,
				    pawams->egw_timestamp_inc);
		eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qpsc), qpsc_pw);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mwxsw_sp_ptp_twaps_set(stwuct mwxsw_sp *mwxsw_sp)
{
	u16 event_message_type;
	int eww;

	/* Dewivew these message types as PTP0. */
	event_message_type = BIT(PTP_MSGTYPE_SYNC) |
			     BIT(PTP_MSGTYPE_DEWAY_WEQ) |
			     BIT(PTP_MSGTYPE_PDEWAY_WEQ) |
			     BIT(PTP_MSGTYPE_PDEWAY_WESP);

	eww = mwxsw_sp_ptp_mtptpt_set(mwxsw_sp, MWXSW_WEG_MTPTPT_TWAP_ID_PTP0,
				      event_message_type);
	if (eww)
		wetuwn eww;

	/* Evewything ewse is PTP1. */
	eww = mwxsw_sp_ptp_mtptpt_set(mwxsw_sp, MWXSW_WEG_MTPTPT_TWAP_ID_PTP1,
				      ~event_message_type);
	if (eww)
		goto eww_mtptpt1_set;

	wetuwn 0;

eww_mtptpt1_set:
	mwxsw_sp_ptp_mtptpt_set(mwxsw_sp, MWXSW_WEG_MTPTPT_TWAP_ID_PTP0, 0);
	wetuwn eww;
}

static void mwxsw_sp_ptp_twaps_unset(stwuct mwxsw_sp *mwxsw_sp)
{
	mwxsw_sp_ptp_mtptpt_set(mwxsw_sp, MWXSW_WEG_MTPTPT_TWAP_ID_PTP1, 0);
	mwxsw_sp_ptp_mtptpt_set(mwxsw_sp, MWXSW_WEG_MTPTPT_TWAP_ID_PTP0, 0);
}

stwuct mwxsw_sp_ptp_state *mwxsw_sp1_ptp_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp1_ptp_state *ptp_state;
	int eww;

	eww = mwxsw_sp1_ptp_shapew_pawams_set(mwxsw_sp);
	if (eww)
		wetuwn EWW_PTW(eww);

	ptp_state = kzawwoc(sizeof(*ptp_state), GFP_KEWNEW);
	if (!ptp_state)
		wetuwn EWW_PTW(-ENOMEM);
	ptp_state->common.mwxsw_sp = mwxsw_sp;

	spin_wock_init(&ptp_state->unmatched_wock);

	eww = whwtabwe_init(&ptp_state->unmatched_ht,
			    &mwxsw_sp1_ptp_unmatched_ht_pawams);
	if (eww)
		goto eww_hashtabwe_init;

	eww = mwxsw_sp_ptp_twaps_set(mwxsw_sp);
	if (eww)
		goto eww_ptp_twaps_set;

	eww = mwxsw_sp1_ptp_set_fifo_cww_on_twap(mwxsw_sp, twue);
	if (eww)
		goto eww_fifo_cww;

	INIT_DEWAYED_WOWK(&ptp_state->ht_gc_dw, mwxsw_sp1_ptp_ht_gc);
	mwxsw_cowe_scheduwe_dw(&ptp_state->ht_gc_dw,
			       MWXSW_SP1_PTP_HT_GC_INTEWVAW);
	wetuwn &ptp_state->common;

eww_fifo_cww:
	mwxsw_sp_ptp_twaps_unset(mwxsw_sp);
eww_ptp_twaps_set:
	whwtabwe_destwoy(&ptp_state->unmatched_ht);
eww_hashtabwe_init:
	kfwee(ptp_state);
	wetuwn EWW_PTW(eww);
}

void mwxsw_sp1_ptp_fini(stwuct mwxsw_sp_ptp_state *ptp_state_common)
{
	stwuct mwxsw_sp *mwxsw_sp = ptp_state_common->mwxsw_sp;
	stwuct mwxsw_sp1_ptp_state *ptp_state;

	ptp_state = mwxsw_sp1_ptp_state(mwxsw_sp);

	cancew_dewayed_wowk_sync(&ptp_state->ht_gc_dw);
	mwxsw_sp1_ptp_mtpppc_set(mwxsw_sp, 0, 0);
	mwxsw_sp1_ptp_set_fifo_cww_on_twap(mwxsw_sp, fawse);
	mwxsw_sp_ptp_twaps_unset(mwxsw_sp);
	whwtabwe_fwee_and_destwoy(&ptp_state->unmatched_ht,
				  &mwxsw_sp1_ptp_unmatched_fwee_fn, NUWW);
	kfwee(ptp_state);
}

int mwxsw_sp1_ptp_hwtstamp_get(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       stwuct hwtstamp_config *config)
{
	*config = mwxsw_sp_powt->ptp.hwtstamp_config;
	wetuwn 0;
}

static int
mwxsw_sp1_ptp_get_message_types(const stwuct hwtstamp_config *config,
				u16 *p_ing_types, u16 *p_egw_types,
				enum hwtstamp_wx_fiwtews *p_wx_fiwtew)
{
	enum hwtstamp_wx_fiwtews wx_fiwtew = config->wx_fiwtew;
	enum hwtstamp_tx_types tx_type = config->tx_type;
	u16 ing_types = 0x00;
	u16 egw_types = 0x00;

	switch (tx_type) {
	case HWTSTAMP_TX_OFF:
		egw_types = 0x00;
		bweak;
	case HWTSTAMP_TX_ON:
		egw_types = 0xff;
		bweak;
	case HWTSTAMP_TX_ONESTEP_SYNC:
	case HWTSTAMP_TX_ONESTEP_P2P:
		wetuwn -EWANGE;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		ing_types = 0x00;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
		ing_types = 0x01;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		ing_types = 0x02;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
		ing_types = 0x0f;
		bweak;
	case HWTSTAMP_FIWTEW_AWW:
		ing_types = 0xff;
		bweak;
	case HWTSTAMP_FIWTEW_SOME:
	case HWTSTAMP_FIWTEW_NTP_AWW:
		wetuwn -EWANGE;
	defauwt:
		wetuwn -EINVAW;
	}

	*p_ing_types = ing_types;
	*p_egw_types = egw_types;
	*p_wx_fiwtew = wx_fiwtew;
	wetuwn 0;
}

static int mwxsw_sp1_ptp_mtpppc_update(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				       u16 ing_types, u16 egw_types)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_powt *tmp;
	u16 owig_ing_types = 0;
	u16 owig_egw_types = 0;
	int eww;
	int i;

	/* MTPPPC configuwes timestamping gwobawwy, not pew powt. Find the
	 * configuwation that contains aww configuwed timestamping wequests.
	 */
	fow (i = 1; i < mwxsw_cowe_max_powts(mwxsw_sp->cowe); i++) {
		tmp = mwxsw_sp->powts[i];
		if (tmp) {
			owig_ing_types |= tmp->ptp.ing_types;
			owig_egw_types |= tmp->ptp.egw_types;
		}
		if (tmp && tmp != mwxsw_sp_powt) {
			ing_types |= tmp->ptp.ing_types;
			egw_types |= tmp->ptp.egw_types;
		}
	}

	if ((ing_types || egw_types) && !(owig_ing_types || owig_egw_types)) {
		eww = mwxsw_sp_pawsing_depth_inc(mwxsw_sp);
		if (eww) {
			netdev_eww(mwxsw_sp_powt->dev, "Faiwed to incwease pawsing depth");
			wetuwn eww;
		}
	}
	if (!(ing_types || egw_types) && (owig_ing_types || owig_egw_types))
		mwxsw_sp_pawsing_depth_dec(mwxsw_sp);

	wetuwn mwxsw_sp1_ptp_mtpppc_set(mwxsw_sp_powt->mwxsw_sp,
				       ing_types, egw_types);
}

static boow mwxsw_sp1_ptp_hwtstamp_enabwed(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	wetuwn mwxsw_sp_powt->ptp.ing_types || mwxsw_sp_powt->ptp.egw_types;
}

static int
mwxsw_sp1_ptp_powt_shapew_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt, boow enabwe)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	chaw qeec_pw[MWXSW_WEG_QEEC_WEN];

	mwxsw_weg_qeec_ptps_pack(qeec_pw, mwxsw_sp_powt->wocaw_powt, enabwe);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qeec), qeec_pw);
}

static int mwxsw_sp1_ptp_powt_shapew_check(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	boow ptps = fawse;
	int eww, i;
	u32 speed;

	if (!mwxsw_sp1_ptp_hwtstamp_enabwed(mwxsw_sp_powt))
		wetuwn mwxsw_sp1_ptp_powt_shapew_set(mwxsw_sp_powt, fawse);

	eww = mwxsw_sp_powt_speed_get(mwxsw_sp_powt, &speed);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < MWXSW_SP1_PTP_SHAPEW_PAWAMS_WEN; i++) {
		if (mwxsw_sp1_ptp_shapew_pawams[i].ethtoow_speed == speed) {
			ptps = twue;
			bweak;
		}
	}

	wetuwn mwxsw_sp1_ptp_powt_shapew_set(mwxsw_sp_powt, ptps);
}

void mwxsw_sp1_ptp_shapew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	int eww;

	mwxsw_sp_powt = containew_of(dwowk, stwuct mwxsw_sp_powt,
				     ptp.shapew_dw);

	if (!mwxsw_sp1_ptp_hwtstamp_enabwed(mwxsw_sp_powt))
		wetuwn;

	eww = mwxsw_sp1_ptp_powt_shapew_check(mwxsw_sp_powt);
	if (eww)
		netdev_eww(mwxsw_sp_powt->dev, "Faiwed to set up PTP shapew\n");
}

int mwxsw_sp1_ptp_hwtstamp_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       stwuct hwtstamp_config *config)
{
	enum hwtstamp_wx_fiwtews wx_fiwtew;
	u16 ing_types;
	u16 egw_types;
	int eww;

	eww = mwxsw_sp1_ptp_get_message_types(config, &ing_types, &egw_types,
					      &wx_fiwtew);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp1_ptp_mtpppc_update(mwxsw_sp_powt, ing_types, egw_types);
	if (eww)
		wetuwn eww;

	mwxsw_sp_powt->ptp.hwtstamp_config = *config;
	mwxsw_sp_powt->ptp.ing_types = ing_types;
	mwxsw_sp_powt->ptp.egw_types = egw_types;

	eww = mwxsw_sp1_ptp_powt_shapew_check(mwxsw_sp_powt);
	if (eww)
		wetuwn eww;

	/* Notify the ioctw cawwew what we awe actuawwy timestamping. */
	config->wx_fiwtew = wx_fiwtew;

	wetuwn 0;
}

int mwxsw_sp1_ptp_get_ts_info(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct ethtoow_ts_info *info)
{
	info->phc_index = ptp_cwock_index(mwxsw_sp->cwock->ptp);

	info->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);

	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) |
			   BIT(HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

stwuct mwxsw_sp_ptp_powt_stat {
	chaw stw[ETH_GSTWING_WEN];
	ptwdiff_t offset;
};

#define MWXSW_SP_PTP_POWT_STAT(NAME, FIEWD)				\
	{								\
		.stw = NAME,						\
		.offset = offsetof(stwuct mwxsw_sp_ptp_powt_stats,	\
				    FIEWD),				\
	}

static const stwuct mwxsw_sp_ptp_powt_stat mwxsw_sp_ptp_powt_stats[] = {
	MWXSW_SP_PTP_POWT_STAT("ptp_wx_gcd_packets",    wx_gcd.packets),
	MWXSW_SP_PTP_POWT_STAT("ptp_wx_gcd_timestamps", wx_gcd.timestamps),
	MWXSW_SP_PTP_POWT_STAT("ptp_tx_gcd_packets",    tx_gcd.packets),
	MWXSW_SP_PTP_POWT_STAT("ptp_tx_gcd_timestamps", tx_gcd.timestamps),
};

#undef MWXSW_SP_PTP_POWT_STAT

#define MWXSW_SP_PTP_POWT_STATS_WEN \
	AWWAY_SIZE(mwxsw_sp_ptp_powt_stats)

int mwxsw_sp1_get_stats_count(void)
{
	wetuwn MWXSW_SP_PTP_POWT_STATS_WEN;
}

void mwxsw_sp1_get_stats_stwings(u8 **p)
{
	int i;

	fow (i = 0; i < MWXSW_SP_PTP_POWT_STATS_WEN; i++) {
		memcpy(*p, mwxsw_sp_ptp_powt_stats[i].stw,
		       ETH_GSTWING_WEN);
		*p += ETH_GSTWING_WEN;
	}
}

void mwxsw_sp1_get_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			 u64 *data, int data_index)
{
	void *stats = &mwxsw_sp_powt->ptp.stats;
	ptwdiff_t offset;
	int i;

	data += data_index;
	fow (i = 0; i < MWXSW_SP_PTP_POWT_STATS_WEN; i++) {
		offset = mwxsw_sp_ptp_powt_stats[i].offset;
		*data++ = *(u64 *)(stats + offset);
	}
}

stwuct mwxsw_sp_ptp_state *mwxsw_sp2_ptp_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp2_ptp_state *ptp_state;
	int eww;

	ptp_state = kzawwoc(sizeof(*ptp_state), GFP_KEWNEW);
	if (!ptp_state)
		wetuwn EWW_PTW(-ENOMEM);

	ptp_state->common.mwxsw_sp = mwxsw_sp;

	eww = mwxsw_sp_ptp_twaps_set(mwxsw_sp);
	if (eww)
		goto eww_ptp_twaps_set;

	wefcount_set(&ptp_state->ptp_powt_enabwed_wef, 0);
	mutex_init(&ptp_state->wock);
	wetuwn &ptp_state->common;

eww_ptp_twaps_set:
	kfwee(ptp_state);
	wetuwn EWW_PTW(eww);
}

void mwxsw_sp2_ptp_fini(stwuct mwxsw_sp_ptp_state *ptp_state_common)
{
	stwuct mwxsw_sp *mwxsw_sp = ptp_state_common->mwxsw_sp;
	stwuct mwxsw_sp2_ptp_state *ptp_state;

	ptp_state = mwxsw_sp2_ptp_state(mwxsw_sp);

	mutex_destwoy(&ptp_state->wock);
	mwxsw_sp_ptp_twaps_unset(mwxsw_sp);
	kfwee(ptp_state);
}

static u32 mwxsw_ptp_utc_time_stamp_sec_get(stwuct mwxsw_cowe *mwxsw_cowe,
					    u8 cqe_ts_sec)
{
	u32 utc_sec = mwxsw_cowe_wead_utc_sec(mwxsw_cowe);

	if (cqe_ts_sec > (utc_sec & 0xff))
		/* Time stamp above the wast bits of UTC (UTC & 0xff) means the
		 * wattew has wwapped aftew the time stamp was cowwected.
		 */
		utc_sec -= 256;

	utc_sec &= ~0xff;
	utc_sec |= cqe_ts_sec;

	wetuwn utc_sec;
}

static void mwxsw_sp2_ptp_hwtstamp_fiww(stwuct mwxsw_cowe *mwxsw_cowe,
					const stwuct mwxsw_skb_cb *cb,
					stwuct skb_shawed_hwtstamps *hwtstamps)
{
	u64 ts_sec, ts_nsec, nsec;

	WAWN_ON_ONCE(!cb->cqe_ts.sec && !cb->cqe_ts.nsec);

	/* The time stamp in the CQE is wepwesented by 38 bits, which is a showt
	 * wepwesentation of UTC time. Softwawe shouwd cweate the fuww time
	 * stamp using the gwobaw UTC cwock. The seconds have onwy 8 bits in the
	 * CQE, to cweate the fuww time stamp, use the cuwwent UTC time and fix
	 * the seconds accowding to the wewation between UTC seconds and CQE
	 * seconds.
	 */
	ts_sec = mwxsw_ptp_utc_time_stamp_sec_get(mwxsw_cowe, cb->cqe_ts.sec);
	ts_nsec = cb->cqe_ts.nsec;

	nsec = ts_sec * NSEC_PEW_SEC + ts_nsec;

	hwtstamps->hwtstamp = ns_to_ktime(nsec);
}

void mwxsw_sp2_ptp_weceive(stwuct mwxsw_sp *mwxsw_sp, stwuct sk_buff *skb,
			   u16 wocaw_powt)
{
	stwuct skb_shawed_hwtstamps hwtstamps;

	mwxsw_sp2_ptp_hwtstamp_fiww(mwxsw_sp->cowe, mwxsw_skb_cb(skb),
				    &hwtstamps);
	*skb_hwtstamps(skb) = hwtstamps;
	mwxsw_sp_wx_wistenew_no_mawk_func(skb, wocaw_powt, mwxsw_sp);
}

void mwxsw_sp2_ptp_twansmitted(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct sk_buff *skb, u16 wocaw_powt)
{
	stwuct skb_shawed_hwtstamps hwtstamps;

	mwxsw_sp2_ptp_hwtstamp_fiww(mwxsw_sp->cowe, mwxsw_skb_cb(skb),
				    &hwtstamps);
	skb_tstamp_tx(skb, &hwtstamps);
	dev_kfwee_skb_any(skb);
}

int mwxsw_sp2_ptp_hwtstamp_get(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       stwuct hwtstamp_config *config)
{
	stwuct mwxsw_sp2_ptp_state *ptp_state;

	ptp_state = mwxsw_sp2_ptp_state(mwxsw_sp_powt->mwxsw_sp);

	mutex_wock(&ptp_state->wock);
	*config = ptp_state->config;
	mutex_unwock(&ptp_state->wock);

	wetuwn 0;
}

static int
mwxsw_sp2_ptp_get_message_types(const stwuct hwtstamp_config *config,
				u16 *p_ing_types, u16 *p_egw_types,
				enum hwtstamp_wx_fiwtews *p_wx_fiwtew)
{
	enum hwtstamp_wx_fiwtews wx_fiwtew = config->wx_fiwtew;
	enum hwtstamp_tx_types tx_type = config->tx_type;
	u16 ing_types = 0x00;
	u16 egw_types = 0x00;

	*p_wx_fiwtew = wx_fiwtew;

	switch (wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		ing_types = 0x00;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
		/* In Spectwum-2 and above, aww packets get time stamp by
		 * defauwt and the dwivew fiww the time stamp onwy fow event
		 * packets. Wetuwn aww event types even if onwy specific types
		 * wewe wequiwed.
		 */
		ing_types = 0x0f;
		*p_wx_fiwtew = HWTSTAMP_FIWTEW_SOME;
		bweak;
	case HWTSTAMP_FIWTEW_AWW:
	case HWTSTAMP_FIWTEW_SOME:
	case HWTSTAMP_FIWTEW_NTP_AWW:
		wetuwn -EWANGE;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (tx_type) {
	case HWTSTAMP_TX_OFF:
		egw_types = 0x00;
		bweak;
	case HWTSTAMP_TX_ON:
		egw_types = 0x0f;
		bweak;
	case HWTSTAMP_TX_ONESTEP_SYNC:
	case HWTSTAMP_TX_ONESTEP_P2P:
		wetuwn -EWANGE;
	defauwt:
		wetuwn -EINVAW;
	}

	if ((ing_types && !egw_types) || (!ing_types && egw_types))
		wetuwn -EINVAW;

	*p_ing_types = ing_types;
	*p_egw_types = egw_types;
	wetuwn 0;
}

static int mwxsw_sp2_ptp_mtpcpc_set(stwuct mwxsw_sp *mwxsw_sp, boow ptp_twap_en,
				    u16 ing_types, u16 egw_types)
{
	chaw mtpcpc_pw[MWXSW_WEG_MTPCPC_WEN];

	mwxsw_weg_mtpcpc_pack(mtpcpc_pw, fawse, 0, ptp_twap_en, ing_types,
			      egw_types);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mtpcpc), mtpcpc_pw);
}

static int mwxsw_sp2_ptp_enabwe(stwuct mwxsw_sp *mwxsw_sp, u16 ing_types,
				u16 egw_types,
				stwuct hwtstamp_config new_config)
{
	stwuct mwxsw_sp2_ptp_state *ptp_state = mwxsw_sp2_ptp_state(mwxsw_sp);
	int eww;

	eww = mwxsw_sp2_ptp_mtpcpc_set(mwxsw_sp, twue, ing_types, egw_types);
	if (eww)
		wetuwn eww;

	ptp_state->config = new_config;
	wetuwn 0;
}

static int mwxsw_sp2_ptp_disabwe(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct hwtstamp_config new_config)
{
	stwuct mwxsw_sp2_ptp_state *ptp_state = mwxsw_sp2_ptp_state(mwxsw_sp);
	int eww;

	eww = mwxsw_sp2_ptp_mtpcpc_set(mwxsw_sp, fawse, 0, 0);
	if (eww)
		wetuwn eww;

	ptp_state->config = new_config;
	wetuwn 0;
}

static int mwxsw_sp2_ptp_configuwe_powt(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					u16 ing_types, u16 egw_types,
					stwuct hwtstamp_config new_config)
{
	stwuct mwxsw_sp2_ptp_state *ptp_state;
	int eww;

	ptp_state = mwxsw_sp2_ptp_state(mwxsw_sp_powt->mwxsw_sp);

	if (wefcount_inc_not_zewo(&ptp_state->ptp_powt_enabwed_wef))
		wetuwn 0;

	eww = mwxsw_sp2_ptp_enabwe(mwxsw_sp_powt->mwxsw_sp, ing_types,
				   egw_types, new_config);
	if (eww)
		wetuwn eww;

	wefcount_set(&ptp_state->ptp_powt_enabwed_wef, 1);

	wetuwn 0;
}

static int mwxsw_sp2_ptp_deconfiguwe_powt(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					  stwuct hwtstamp_config new_config)
{
	stwuct mwxsw_sp2_ptp_state *ptp_state;
	int eww;

	ptp_state = mwxsw_sp2_ptp_state(mwxsw_sp_powt->mwxsw_sp);

	if (!wefcount_dec_and_test(&ptp_state->ptp_powt_enabwed_wef))
		wetuwn 0;

	eww = mwxsw_sp2_ptp_disabwe(mwxsw_sp_powt->mwxsw_sp, new_config);
	if (eww)
		goto eww_ptp_disabwe;

	wetuwn 0;

eww_ptp_disabwe:
	wefcount_set(&ptp_state->ptp_powt_enabwed_wef, 1);
	wetuwn eww;
}

int mwxsw_sp2_ptp_hwtstamp_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       stwuct hwtstamp_config *config)
{
	stwuct mwxsw_sp2_ptp_state *ptp_state;
	enum hwtstamp_wx_fiwtews wx_fiwtew;
	stwuct hwtstamp_config new_config;
	u16 new_ing_types, new_egw_types;
	boow ptp_enabwed;
	int eww;

	ptp_state = mwxsw_sp2_ptp_state(mwxsw_sp_powt->mwxsw_sp);
	mutex_wock(&ptp_state->wock);

	eww = mwxsw_sp2_ptp_get_message_types(config, &new_ing_types,
					      &new_egw_types, &wx_fiwtew);
	if (eww)
		goto eww_get_message_types;

	new_config.fwags = config->fwags;
	new_config.tx_type = config->tx_type;
	new_config.wx_fiwtew = wx_fiwtew;

	ptp_enabwed = mwxsw_sp_powt->ptp.ing_types ||
		      mwxsw_sp_powt->ptp.egw_types;

	if ((new_ing_types || new_egw_types) && !ptp_enabwed) {
		eww = mwxsw_sp2_ptp_configuwe_powt(mwxsw_sp_powt, new_ing_types,
						   new_egw_types, new_config);
		if (eww)
			goto eww_configuwe_powt;
	} ewse if (!new_ing_types && !new_egw_types && ptp_enabwed) {
		eww = mwxsw_sp2_ptp_deconfiguwe_powt(mwxsw_sp_powt, new_config);
		if (eww)
			goto eww_deconfiguwe_powt;
	}

	mwxsw_sp_powt->ptp.ing_types = new_ing_types;
	mwxsw_sp_powt->ptp.egw_types = new_egw_types;

	/* Notify the ioctw cawwew what we awe actuawwy timestamping. */
	config->wx_fiwtew = wx_fiwtew;
	mutex_unwock(&ptp_state->wock);

	wetuwn 0;

eww_deconfiguwe_powt:
eww_configuwe_powt:
eww_get_message_types:
	mutex_unwock(&ptp_state->wock);
	wetuwn eww;
}

int mwxsw_sp2_ptp_get_ts_info(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct ethtoow_ts_info *info)
{
	info->phc_index = ptp_cwock_index(mwxsw_sp->cwock->ptp);

	info->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);

	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_EVENT);

	wetuwn 0;
}

int mwxsw_sp_ptp_txhdw_constwuct(stwuct mwxsw_cowe *mwxsw_cowe,
				 stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 stwuct sk_buff *skb,
				 const stwuct mwxsw_tx_info *tx_info)
{
	mwxsw_sp_txhdw_constwuct(skb, tx_info);
	wetuwn 0;
}

int mwxsw_sp2_ptp_txhdw_constwuct(stwuct mwxsw_cowe *mwxsw_cowe,
				  stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  stwuct sk_buff *skb,
				  const stwuct mwxsw_tx_info *tx_info)
{
	/* In Spectwum-2 and Spectwum-3, in owdew fow PTP event packets to have
	 * theiw cowwection fiewd cowwectwy set on the egwess powt they must be
	 * twansmitted as data packets. Such packets ingwess the ASIC via the
	 * CPU powt and must have a VWAN tag, as the CPU powt is not configuwed
	 * with a PVID. Push the defauwt VWAN (4095), which is configuwed as
	 * egwess untagged on aww the powts.
	 */
	if (!skb_vwan_tagged(skb)) {
		skb = vwan_insewt_tag_set_pwoto(skb, htons(ETH_P_8021Q),
						MWXSW_SP_DEFAUWT_VID);
		if (!skb) {
			this_cpu_inc(mwxsw_sp_powt->pcpu_stats->tx_dwopped);
			wetuwn -ENOMEM;
		}
	}

	wetuwn mwxsw_sp_txhdw_ptp_data_constwuct(mwxsw_cowe, mwxsw_sp_powt, skb,
						 tx_info);
}
