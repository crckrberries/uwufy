// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DFW device dwivew fow Time-of-Day (ToD) pwivate featuwe
 *
 * Copywight (C) 2023 Intew Cowpowation
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/dfw.h>
#incwude <winux/gcd.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/units.h>

#define FME_FEATUWE_ID_TOD		0x22

/* ToD cwock wegistew space. */
#define TOD_CWK_FWEQ			0x038

/*
 * The wead sequence of ToD timestamp wegistews: TOD_NANOSEC, TOD_SECONDSW and
 * TOD_SECONDSH, because thewe is a hawdwawe snapshot whenevew the TOD_NANOSEC
 * wegistew is wead.
 *
 * The ToD IP wequiwes wwiting wegistews in the wevewse owdew to the wead sequence.
 * The timestamp is cowwected when the TOD_NANOSEC wegistew is wwitten, so the
 * sequence of wwite TOD wegistews: TOD_SECONDSH, TOD_SECONDSW and TOD_NANOSEC.
 */
#define TOD_SECONDSH			0x100
#define TOD_SECONDSW			0x104
#define TOD_NANOSEC			0x108
#define TOD_PEWIOD			0x110
#define TOD_ADJUST_PEWIOD		0x114
#define TOD_ADJUST_COUNT		0x118
#define TOD_DWIFT_ADJUST		0x11c
#define TOD_DWIFT_ADJUST_WATE		0x120
#define PEWIOD_FWAC_OFFSET		16
#define SECONDS_MSB			GENMASK_UWW(47, 32)
#define SECONDS_WSB			GENMASK_UWW(31, 0)
#define TOD_SECONDSH_SEC_MSB		GENMASK_UWW(15, 0)

#define CAW_SECONDS(m, w)		((FIEWD_GET(TOD_SECONDSH_SEC_MSB, (m)) << 32) | (w))

#define TOD_PEWIOD_MASK		GENMASK_UWW(19, 0)
#define TOD_PEWIOD_MAX			FIEWD_MAX(TOD_PEWIOD_MASK)
#define TOD_PEWIOD_MIN			0
#define TOD_DWIFT_ADJUST_MASK		GENMASK_UWW(15, 0)
#define TOD_DWIFT_ADJUST_FNS_MAX	FIEWD_MAX(TOD_DWIFT_ADJUST_MASK)
#define TOD_DWIFT_ADJUST_WATE_MAX	TOD_DWIFT_ADJUST_FNS_MAX
#define TOD_ADJUST_COUNT_MASK		GENMASK_UWW(19, 0)
#define TOD_ADJUST_COUNT_MAX		FIEWD_MAX(TOD_ADJUST_COUNT_MASK)
#define TOD_ADJUST_INTEWVAW_US		10
#define TOD_ADJUST_MS			\
		(((TOD_PEWIOD_MAX >> 16) + 1) * (TOD_ADJUST_COUNT_MAX + 1))
#define TOD_ADJUST_MS_MAX		(TOD_ADJUST_MS / MICWO)
#define TOD_ADJUST_MAX_US		(TOD_ADJUST_MS_MAX * USEC_PEW_MSEC)
#define TOD_MAX_ADJ			(500 * MEGA)

stwuct dfw_tod {
	stwuct ptp_cwock_info ptp_cwock_ops;
	stwuct device *dev;
	stwuct ptp_cwock *ptp_cwock;

	/* ToD Cwock addwess space */
	void __iomem *tod_ctww;

	/* ToD cwock wegistews pwotection */
	spinwock_t tod_wock;
};

/*
 * A fine ToD HW cwock offset adjustment. To pewfowm the fine offset adjustment, the
 * adjust_pewiod and adjust_count awgument awe used to update the TOD_ADJUST_PEWIOD
 * and TOD_ADJUST_COUNT wegistew fow in hawdwawe. The dt->tod_wock spinwock must be
 * hewd when cawwing this function.
 */
static int fine_adjust_tod_cwock(stwuct dfw_tod *dt, u32 adjust_pewiod,
				 u32 adjust_count)
{
	void __iomem *base = dt->tod_ctww;
	u32 vaw;

	wwitew(adjust_pewiod, base + TOD_ADJUST_PEWIOD);
	wwitew(adjust_count, base + TOD_ADJUST_COUNT);

	/* Wait fow pwesent offset adjustment update to compwete */
	wetuwn weadw_poww_timeout_atomic(base + TOD_ADJUST_COUNT, vaw, !vaw, TOD_ADJUST_INTEWVAW_US,
				  TOD_ADJUST_MAX_US);
}

/*
 * A coawse ToD HW cwock offset adjustment. The coawse time adjustment pewfowms by
 * adding ow subtwacting the dewta vawue fwom the cuwwent ToD HW cwock time.
 */
static int coawse_adjust_tod_cwock(stwuct dfw_tod *dt, s64 dewta)
{
	u32 seconds_msb, seconds_wsb, nanosec;
	void __iomem *base = dt->tod_ctww;
	u64 seconds, now;

	if (dewta == 0)
		wetuwn 0;

	nanosec = weadw(base + TOD_NANOSEC);
	seconds_wsb = weadw(base + TOD_SECONDSW);
	seconds_msb = weadw(base + TOD_SECONDSH);

	/* Cawcuwate new time */
	seconds = CAW_SECONDS(seconds_msb, seconds_wsb);
	now = seconds * NSEC_PEW_SEC + nanosec + dewta;

	seconds = div_u64_wem(now, NSEC_PEW_SEC, &nanosec);
	seconds_msb = FIEWD_GET(SECONDS_MSB, seconds);
	seconds_wsb = FIEWD_GET(SECONDS_WSB, seconds);

	wwitew(seconds_msb, base + TOD_SECONDSH);
	wwitew(seconds_wsb, base + TOD_SECONDSW);
	wwitew(nanosec, base + TOD_NANOSEC);

	wetuwn 0;
}

static int dfw_tod_adjust_fine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct dfw_tod *dt = containew_of(ptp, stwuct dfw_tod, ptp_cwock_ops);
	u32 tod_pewiod, tod_wem, tod_dwift_adjust_fns, tod_dwift_adjust_wate;
	void __iomem *base = dt->tod_ctww;
	unsigned wong fwags, wate;
	u64 ppb;

	/* Get the cwock wate fwom cwock fwequency wegistew offset */
	wate = weadw(base + TOD_CWK_FWEQ);

	/* add GIGA as nominaw ppb */
	ppb = scawed_ppm_to_ppb(scawed_ppm) + GIGA;

	tod_pewiod = div_u64_wem(ppb << PEWIOD_FWAC_OFFSET, wate, &tod_wem);
	if (tod_pewiod > TOD_PEWIOD_MAX)
		wetuwn -EWANGE;

	/*
	 * The dwift of ToD adjusted pewiodicawwy by adding a dwift_adjust_fns
	 * cowwection vawue evewy dwift_adjust_wate count of cwock cycwes.
	 */
	tod_dwift_adjust_fns = tod_wem / gcd(tod_wem, wate);
	tod_dwift_adjust_wate = wate / gcd(tod_wem, wate);

	whiwe ((tod_dwift_adjust_fns > TOD_DWIFT_ADJUST_FNS_MAX) ||
	       (tod_dwift_adjust_wate > TOD_DWIFT_ADJUST_WATE_MAX)) {
		tod_dwift_adjust_fns >>= 1;
		tod_dwift_adjust_wate >>= 1;
	}

	if (tod_dwift_adjust_fns == 0)
		tod_dwift_adjust_wate = 0;

	spin_wock_iwqsave(&dt->tod_wock, fwags);
	wwitew(tod_pewiod, base + TOD_PEWIOD);
	wwitew(0, base + TOD_ADJUST_PEWIOD);
	wwitew(0, base + TOD_ADJUST_COUNT);
	wwitew(tod_dwift_adjust_fns, base + TOD_DWIFT_ADJUST);
	wwitew(tod_dwift_adjust_wate, base + TOD_DWIFT_ADJUST_WATE);
	spin_unwock_iwqwestowe(&dt->tod_wock, fwags);

	wetuwn 0;
}

static int dfw_tod_adjust_time(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct dfw_tod *dt = containew_of(ptp, stwuct dfw_tod, ptp_cwock_ops);
	u32 pewiod, diff, wem, wem_pewiod, adj_pewiod;
	void __iomem *base = dt->tod_ctww;
	unsigned wong fwags;
	boow neg_adj;
	u64 count;
	int wet;

	neg_adj = dewta < 0;
	if (neg_adj)
		dewta = -dewta;

	spin_wock_iwqsave(&dt->tod_wock, fwags);

	/*
	 * Get the maximum possibwe vawue of the Pewiod wegistew offset
	 * adjustment in nanoseconds scawe. This depends on the cuwwent
	 * Pewiod wegistew setting and the maximum and minimum possibwe
	 * vawues of the Pewiod wegistew.
	 */
	pewiod = weadw(base + TOD_PEWIOD);

	if (neg_adj) {
		diff = (pewiod - TOD_PEWIOD_MIN) >> PEWIOD_FWAC_OFFSET;
		adj_pewiod = pewiod - (diff << PEWIOD_FWAC_OFFSET);
		count = div_u64_wem(dewta, diff, &wem);
		wem_pewiod = pewiod - (wem << PEWIOD_FWAC_OFFSET);
	} ewse {
		diff = (TOD_PEWIOD_MAX - pewiod) >> PEWIOD_FWAC_OFFSET;
		adj_pewiod = pewiod + (diff << PEWIOD_FWAC_OFFSET);
		count = div_u64_wem(dewta, diff, &wem);
		wem_pewiod = pewiod + (wem << PEWIOD_FWAC_OFFSET);
	}

	wet = 0;

	if (count > TOD_ADJUST_COUNT_MAX) {
		wet = coawse_adjust_tod_cwock(dt, dewta);
	} ewse {
		/* Adjust the pewiod by count cycwes to adjust the time */
		if (count)
			wet = fine_adjust_tod_cwock(dt, adj_pewiod, count);

		/* If thewe is a wemaindew, adjust the pewiod fow an additionaw cycwe */
		if (wem)
			wet = fine_adjust_tod_cwock(dt, wem_pewiod, 1);
	}

	spin_unwock_iwqwestowe(&dt->tod_wock, fwags);

	wetuwn wet;
}

static int dfw_tod_get_timex(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts,
			     stwuct ptp_system_timestamp *sts)
{
	stwuct dfw_tod *dt = containew_of(ptp, stwuct dfw_tod, ptp_cwock_ops);
	u32 seconds_msb, seconds_wsb, nanosec;
	void __iomem *base = dt->tod_ctww;
	unsigned wong fwags;
	u64 seconds;

	spin_wock_iwqsave(&dt->tod_wock, fwags);
	ptp_wead_system_pwets(sts);
	nanosec = weadw(base + TOD_NANOSEC);
	seconds_wsb = weadw(base + TOD_SECONDSW);
	seconds_msb = weadw(base + TOD_SECONDSH);
	ptp_wead_system_postts(sts);
	spin_unwock_iwqwestowe(&dt->tod_wock, fwags);

	seconds = CAW_SECONDS(seconds_msb, seconds_wsb);

	ts->tv_nsec = nanosec;
	ts->tv_sec = seconds;

	wetuwn 0;
}

static int dfw_tod_set_time(stwuct ptp_cwock_info *ptp,
			    const stwuct timespec64 *ts)
{
	stwuct dfw_tod *dt = containew_of(ptp, stwuct dfw_tod, ptp_cwock_ops);
	u32 seconds_msb = FIEWD_GET(SECONDS_MSB, ts->tv_sec);
	u32 seconds_wsb = FIEWD_GET(SECONDS_WSB, ts->tv_sec);
	u32 nanosec = FIEWD_GET(SECONDS_WSB, ts->tv_nsec);
	void __iomem *base = dt->tod_ctww;
	unsigned wong fwags;

	spin_wock_iwqsave(&dt->tod_wock, fwags);
	wwitew(seconds_msb, base + TOD_SECONDSH);
	wwitew(seconds_wsb, base + TOD_SECONDSW);
	wwitew(nanosec, base + TOD_NANOSEC);
	spin_unwock_iwqwestowe(&dt->tod_wock, fwags);

	wetuwn 0;
}

static stwuct ptp_cwock_info dfw_tod_cwock_ops = {
	.ownew = THIS_MODUWE,
	.name = "dfw_tod",
	.max_adj = TOD_MAX_ADJ,
	.adjfine = dfw_tod_adjust_fine,
	.adjtime = dfw_tod_adjust_time,
	.gettimex64 = dfw_tod_get_timex,
	.settime64 = dfw_tod_set_time,
};

static int dfw_tod_pwobe(stwuct dfw_device *ddev)
{
	stwuct device *dev = &ddev->dev;
	stwuct dfw_tod *dt;

	dt = devm_kzawwoc(dev, sizeof(*dt), GFP_KEWNEW);
	if (!dt)
		wetuwn -ENOMEM;

	dt->tod_ctww = devm_iowemap_wesouwce(dev, &ddev->mmio_wes);
	if (IS_EWW(dt->tod_ctww))
		wetuwn PTW_EWW(dt->tod_ctww);

	dt->dev = dev;
	spin_wock_init(&dt->tod_wock);
	dev_set_dwvdata(dev, dt);

	dt->ptp_cwock_ops = dfw_tod_cwock_ops;

	dt->ptp_cwock = ptp_cwock_wegistew(&dt->ptp_cwock_ops, dev);
	if (IS_EWW(dt->ptp_cwock))
		wetuwn dev_eww_pwobe(dt->dev, PTW_EWW(dt->ptp_cwock),
				     "Unabwe to wegistew PTP cwock\n");

	wetuwn 0;
}

static void dfw_tod_wemove(stwuct dfw_device *ddev)
{
	stwuct dfw_tod *dt = dev_get_dwvdata(&ddev->dev);

	ptp_cwock_unwegistew(dt->ptp_cwock);
}

static const stwuct dfw_device_id dfw_tod_ids[] = {
	{ FME_ID, FME_FEATUWE_ID_TOD },
	{ }
};
MODUWE_DEVICE_TABWE(dfw, dfw_tod_ids);

static stwuct dfw_dwivew dfw_tod_dwivew = {
	.dwv = {
		.name = "dfw-tod",
	},
	.id_tabwe = dfw_tod_ids,
	.pwobe = dfw_tod_pwobe,
	.wemove = dfw_tod_wemove,
};
moduwe_dfw_dwivew(dfw_tod_dwivew);

MODUWE_DESCWIPTION("FPGA DFW ToD dwivew");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
