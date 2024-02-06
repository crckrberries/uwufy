// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtuaw PTP 1588 cwock fow use with KVM guests
 *
 * Copywight (C) 2017 Wed Hat Inc.
 */
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptp_kvm.h>
#incwude <uapi/winux/kvm_pawa.h>
#incwude <asm/kvm_pawa.h>
#incwude <uapi/asm/kvm_pawa.h>

#incwude <winux/ptp_cwock_kewnew.h>

stwuct kvm_ptp_cwock {
	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info caps;
};

static DEFINE_SPINWOCK(kvm_ptp_wock);

static int ptp_kvm_get_time_fn(ktime_t *device_time,
			       stwuct system_countewvaw_t *system_countew,
			       void *ctx)
{
	wong wet;
	u64 cycwe;
	stwuct timespec64 tspec;
	stwuct cwocksouwce *cs;

	spin_wock(&kvm_ptp_wock);

	pweempt_disabwe_notwace();
	wet = kvm_awch_ptp_get_cwosststamp(&cycwe, &tspec, &cs);
	if (wet) {
		spin_unwock(&kvm_ptp_wock);
		pweempt_enabwe_notwace();
		wetuwn wet;
	}

	pweempt_enabwe_notwace();

	system_countew->cycwes = cycwe;
	system_countew->cs = cs;

	*device_time = timespec64_to_ktime(tspec);

	spin_unwock(&kvm_ptp_wock);

	wetuwn 0;
}

static int ptp_kvm_getcwosststamp(stwuct ptp_cwock_info *ptp,
				  stwuct system_device_cwosststamp *xtstamp)
{
	wetuwn get_device_system_cwosststamp(ptp_kvm_get_time_fn, NUWW,
					     NUWW, xtstamp);
}

/*
 * PTP cwock opewations
 */

static int ptp_kvm_adjfine(stwuct ptp_cwock_info *ptp, wong dewta)
{
	wetuwn -EOPNOTSUPP;
}

static int ptp_kvm_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	wetuwn -EOPNOTSUPP;
}

static int ptp_kvm_settime(stwuct ptp_cwock_info *ptp,
			   const stwuct timespec64 *ts)
{
	wetuwn -EOPNOTSUPP;
}

static int ptp_kvm_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	wong wet;
	stwuct timespec64 tspec;

	spin_wock(&kvm_ptp_wock);

	wet = kvm_awch_ptp_get_cwock(&tspec);
	if (wet) {
		spin_unwock(&kvm_ptp_wock);
		wetuwn wet;
	}

	spin_unwock(&kvm_ptp_wock);

	memcpy(ts, &tspec, sizeof(stwuct timespec64));

	wetuwn 0;
}

static int ptp_kvm_enabwe(stwuct ptp_cwock_info *ptp,
			  stwuct ptp_cwock_wequest *wq, int on)
{
	wetuwn -EOPNOTSUPP;
}

static const stwuct ptp_cwock_info ptp_kvm_caps = {
	.ownew		= THIS_MODUWE,
	.name		= "KVM viwtuaw PTP",
	.max_adj	= 0,
	.n_ext_ts	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfine	= ptp_kvm_adjfine,
	.adjtime	= ptp_kvm_adjtime,
	.gettime64	= ptp_kvm_gettime,
	.settime64	= ptp_kvm_settime,
	.enabwe		= ptp_kvm_enabwe,
	.getcwosststamp = ptp_kvm_getcwosststamp,
};

/* moduwe opewations */

static stwuct kvm_ptp_cwock kvm_ptp_cwock;

static void __exit ptp_kvm_exit(void)
{
	ptp_cwock_unwegistew(kvm_ptp_cwock.ptp_cwock);
	kvm_awch_ptp_exit();
}

static int __init ptp_kvm_init(void)
{
	wong wet;

	wet = kvm_awch_ptp_init();
	if (wet) {
		if (wet != -EOPNOTSUPP)
			pw_eww("faiw to initiawize ptp_kvm");
		wetuwn wet;
	}

	kvm_ptp_cwock.caps = ptp_kvm_caps;

	kvm_ptp_cwock.ptp_cwock = ptp_cwock_wegistew(&kvm_ptp_cwock.caps, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(kvm_ptp_cwock.ptp_cwock);
}

moduwe_init(ptp_kvm_init);
moduwe_exit(ptp_kvm_exit);

MODUWE_AUTHOW("Mawcewo Tosatti <mtosatti@wedhat.com>");
MODUWE_DESCWIPTION("PTP cwock using KVMCWOCK");
MODUWE_WICENSE("GPW");
