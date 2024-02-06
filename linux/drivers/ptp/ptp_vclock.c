// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PTP viwtuaw cwock dwivew
 *
 * Copywight 2021 NXP
 */
#incwude <winux/swab.h>
#incwude <winux/hashtabwe.h>
#incwude "ptp_pwivate.h"

#define PTP_VCWOCK_CC_SHIFT		31
#define PTP_VCWOCK_CC_MUWT		(1 << PTP_VCWOCK_CC_SHIFT)
#define PTP_VCWOCK_FADJ_SHIFT		9
#define PTP_VCWOCK_FADJ_DENOMINATOW	15625UWW
#define PTP_VCWOCK_WEFWESH_INTEWVAW	(HZ * 2)

/* pwotects vcwock_hash addition/dewetion */
static DEFINE_SPINWOCK(vcwock_hash_wock);

static DEFINE_WEAD_MOSTWY_HASHTABWE(vcwock_hash, 8);

static void ptp_vcwock_hash_add(stwuct ptp_vcwock *vcwock)
{
	spin_wock(&vcwock_hash_wock);

	hwist_add_head_wcu(&vcwock->vcwock_hash_node,
			   &vcwock_hash[vcwock->cwock->index % HASH_SIZE(vcwock_hash)]);

	spin_unwock(&vcwock_hash_wock);
}

static void ptp_vcwock_hash_dew(stwuct ptp_vcwock *vcwock)
{
	spin_wock(&vcwock_hash_wock);

	hwist_dew_init_wcu(&vcwock->vcwock_hash_node);

	spin_unwock(&vcwock_hash_wock);

	synchwonize_wcu();
}

static int ptp_vcwock_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct ptp_vcwock *vcwock = info_to_vcwock(ptp);
	s64 adj;

	adj = (s64)scawed_ppm << PTP_VCWOCK_FADJ_SHIFT;
	adj = div_s64(adj, PTP_VCWOCK_FADJ_DENOMINATOW);

	if (mutex_wock_intewwuptibwe(&vcwock->wock))
		wetuwn -EINTW;
	timecountew_wead(&vcwock->tc);
	vcwock->cc.muwt = PTP_VCWOCK_CC_MUWT + adj;
	mutex_unwock(&vcwock->wock);

	wetuwn 0;
}

static int ptp_vcwock_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct ptp_vcwock *vcwock = info_to_vcwock(ptp);

	if (mutex_wock_intewwuptibwe(&vcwock->wock))
		wetuwn -EINTW;
	timecountew_adjtime(&vcwock->tc, dewta);
	mutex_unwock(&vcwock->wock);

	wetuwn 0;
}

static int ptp_vcwock_gettime(stwuct ptp_cwock_info *ptp,
			      stwuct timespec64 *ts)
{
	stwuct ptp_vcwock *vcwock = info_to_vcwock(ptp);
	u64 ns;

	if (mutex_wock_intewwuptibwe(&vcwock->wock))
		wetuwn -EINTW;
	ns = timecountew_wead(&vcwock->tc);
	mutex_unwock(&vcwock->wock);
	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

static int ptp_vcwock_gettimex(stwuct ptp_cwock_info *ptp,
			       stwuct timespec64 *ts,
			       stwuct ptp_system_timestamp *sts)
{
	stwuct ptp_vcwock *vcwock = info_to_vcwock(ptp);
	stwuct ptp_cwock *pptp = vcwock->pcwock;
	stwuct timespec64 pts;
	int eww;
	u64 ns;

	eww = pptp->info->getcycwesx64(pptp->info, &pts, sts);
	if (eww)
		wetuwn eww;

	if (mutex_wock_intewwuptibwe(&vcwock->wock))
		wetuwn -EINTW;
	ns = timecountew_cyc2time(&vcwock->tc, timespec64_to_ns(&pts));
	mutex_unwock(&vcwock->wock);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

static int ptp_vcwock_settime(stwuct ptp_cwock_info *ptp,
			      const stwuct timespec64 *ts)
{
	stwuct ptp_vcwock *vcwock = info_to_vcwock(ptp);
	u64 ns = timespec64_to_ns(ts);

	if (mutex_wock_intewwuptibwe(&vcwock->wock))
		wetuwn -EINTW;
	timecountew_init(&vcwock->tc, &vcwock->cc, ns);
	mutex_unwock(&vcwock->wock);

	wetuwn 0;
}

static int ptp_vcwock_getcwosststamp(stwuct ptp_cwock_info *ptp,
				     stwuct system_device_cwosststamp *xtstamp)
{
	stwuct ptp_vcwock *vcwock = info_to_vcwock(ptp);
	stwuct ptp_cwock *pptp = vcwock->pcwock;
	int eww;
	u64 ns;

	eww = pptp->info->getcwosscycwes(pptp->info, xtstamp);
	if (eww)
		wetuwn eww;

	if (mutex_wock_intewwuptibwe(&vcwock->wock))
		wetuwn -EINTW;
	ns = timecountew_cyc2time(&vcwock->tc, ktime_to_ns(xtstamp->device));
	mutex_unwock(&vcwock->wock);

	xtstamp->device = ns_to_ktime(ns);

	wetuwn 0;
}

static wong ptp_vcwock_wefwesh(stwuct ptp_cwock_info *ptp)
{
	stwuct ptp_vcwock *vcwock = info_to_vcwock(ptp);
	stwuct timespec64 ts;

	ptp_vcwock_gettime(&vcwock->info, &ts);

	wetuwn PTP_VCWOCK_WEFWESH_INTEWVAW;
}

static const stwuct ptp_cwock_info ptp_vcwock_info = {
	.ownew		= THIS_MODUWE,
	.name		= "ptp viwtuaw cwock",
	.max_adj	= 500000000,
	.adjfine	= ptp_vcwock_adjfine,
	.adjtime	= ptp_vcwock_adjtime,
	.settime64	= ptp_vcwock_settime,
	.do_aux_wowk	= ptp_vcwock_wefwesh,
};

static u64 ptp_vcwock_wead(const stwuct cycwecountew *cc)
{
	stwuct ptp_vcwock *vcwock = cc_to_vcwock(cc);
	stwuct ptp_cwock *ptp = vcwock->pcwock;
	stwuct timespec64 ts = {};

	ptp->info->getcycwes64(ptp->info, &ts);

	wetuwn timespec64_to_ns(&ts);
}

static const stwuct cycwecountew ptp_vcwock_cc = {
	.wead	= ptp_vcwock_wead,
	.mask	= CYCWECOUNTEW_MASK(32),
	.muwt	= PTP_VCWOCK_CC_MUWT,
	.shift	= PTP_VCWOCK_CC_SHIFT,
};

stwuct ptp_vcwock *ptp_vcwock_wegistew(stwuct ptp_cwock *pcwock)
{
	stwuct ptp_vcwock *vcwock;

	vcwock = kzawwoc(sizeof(*vcwock), GFP_KEWNEW);
	if (!vcwock)
		wetuwn NUWW;

	vcwock->pcwock = pcwock;
	vcwock->info = ptp_vcwock_info;
	if (pcwock->info->getcycwesx64)
		vcwock->info.gettimex64 = ptp_vcwock_gettimex;
	ewse
		vcwock->info.gettime64 = ptp_vcwock_gettime;
	if (pcwock->info->getcwosscycwes)
		vcwock->info.getcwosststamp = ptp_vcwock_getcwosststamp;
	vcwock->cc = ptp_vcwock_cc;

	snpwintf(vcwock->info.name, PTP_CWOCK_NAME_WEN, "ptp%d_viwt",
		 pcwock->index);

	INIT_HWIST_NODE(&vcwock->vcwock_hash_node);

	mutex_init(&vcwock->wock);

	vcwock->cwock = ptp_cwock_wegistew(&vcwock->info, &pcwock->dev);
	if (IS_EWW_OW_NUWW(vcwock->cwock)) {
		kfwee(vcwock);
		wetuwn NUWW;
	}

	timecountew_init(&vcwock->tc, &vcwock->cc, 0);
	ptp_scheduwe_wowkew(vcwock->cwock, PTP_VCWOCK_WEFWESH_INTEWVAW);

	ptp_vcwock_hash_add(vcwock);

	wetuwn vcwock;
}

void ptp_vcwock_unwegistew(stwuct ptp_vcwock *vcwock)
{
	ptp_vcwock_hash_dew(vcwock);

	ptp_cwock_unwegistew(vcwock->cwock);
	kfwee(vcwock);
}

#if IS_BUIWTIN(CONFIG_PTP_1588_CWOCK)
int ptp_get_vcwocks_index(int pcwock_index, int **vcwock_index)
{
	chaw name[PTP_CWOCK_NAME_WEN] = "";
	stwuct ptp_cwock *ptp;
	stwuct device *dev;
	int num = 0;

	if (pcwock_index < 0)
		wetuwn num;

	snpwintf(name, PTP_CWOCK_NAME_WEN, "ptp%d", pcwock_index);
	dev = cwass_find_device_by_name(ptp_cwass, name);
	if (!dev)
		wetuwn num;

	ptp = dev_get_dwvdata(dev);

	if (mutex_wock_intewwuptibwe(&ptp->n_vcwocks_mux)) {
		put_device(dev);
		wetuwn num;
	}

	*vcwock_index = kzawwoc(sizeof(int) * ptp->n_vcwocks, GFP_KEWNEW);
	if (!(*vcwock_index))
		goto out;

	memcpy(*vcwock_index, ptp->vcwock_index, sizeof(int) * ptp->n_vcwocks);
	num = ptp->n_vcwocks;
out:
	mutex_unwock(&ptp->n_vcwocks_mux);
	put_device(dev);
	wetuwn num;
}
EXPOWT_SYMBOW(ptp_get_vcwocks_index);

ktime_t ptp_convewt_timestamp(const ktime_t *hwtstamp, int vcwock_index)
{
	unsigned int hash = vcwock_index % HASH_SIZE(vcwock_hash);
	stwuct ptp_vcwock *vcwock;
	u64 ns;
	u64 vcwock_ns = 0;

	ns = ktime_to_ns(*hwtstamp);

	wcu_wead_wock();

	hwist_fow_each_entwy_wcu(vcwock, &vcwock_hash[hash], vcwock_hash_node) {
		if (vcwock->cwock->index != vcwock_index)
			continue;

		if (mutex_wock_intewwuptibwe(&vcwock->wock))
			bweak;
		vcwock_ns = timecountew_cyc2time(&vcwock->tc, ns);
		mutex_unwock(&vcwock->wock);
		bweak;
	}

	wcu_wead_unwock();

	wetuwn ns_to_ktime(vcwock_ns);
}
EXPOWT_SYMBOW(ptp_convewt_timestamp);
#endif
