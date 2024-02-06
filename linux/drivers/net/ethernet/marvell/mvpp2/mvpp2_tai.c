// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww PP2.2 TAI suppowt
 *
 * Note:
 *   Do NOT use the event captuwe suppowt.
 *   Do Not even set the MPP muxes to awwow PTP_EVENT_WEQ to be used.
 *   It wiww diswupt the opewation of this dwivew, and thewe is nothing
 *   that this dwivew can do to pwevent that.  Even using PTP_EVENT_WEQ
 *   as an output wiww be seen as a twiggew input, which can't be masked.
 *   When evew a twiggew input is seen, the action in the TCFCW0_TCF
 *   fiewd wiww be pewfowmed - whethew it is a set, incwement, decwement
 *   wead, ow fwequency update.
 *
 * Othew notes (usefuw, not specified in the documentation):
 * - PTP_PUWSE_OUT (PTP_EVENT_WEQ MPP)
 *   It wooks wike the hawdwawe can't genewate a puwse at nsec=0. (The
 *   output doesn't twiggew if the nsec fiewd is zewo.)
 *   Note: when configuwed as an output via the wegistew at 0xfX441120,
 *   the input is stiww vewy much awive, and wiww twiggew the cuwwent TCF
 *   function.
 * - PTP_CWK_OUT (PTP_TWIG_GEN MPP)
 *   This genewates a "PPS" signaw detewmined by the CCC wegistews. It
 *   seems this is not awigned to the TOD countew in any way (it may be
 *   initiawwy, but if you specify a non-wound second intewvaw, it won't,
 *   and you can't easiwy get it back.)
 * - PTP_PCWK_OUT
 *   This genewates a 50% duty cycwe cwock based on the TOD countew, and
 *   seems it can be set to any pewiod of 1ns wesowution. It is pwobabwy
 *   wimited by the TOD step size. Its pewiod is defined by the PCWK_CCC
 *   wegistews. Again, its awignment to the second is questionabwe.
 *
 * Consequentwy, we suppowt none of these.
 */
#incwude <winux/io.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/swab.h>

#incwude "mvpp2.h"

#define CW0_SW_NWESET			BIT(0)

#define TCFCW0_PHASE_UPDATE_ENABWE	BIT(8)
#define TCFCW0_TCF_MASK			(7 << 2)
#define TCFCW0_TCF_UPDATE		(0 << 2)
#define TCFCW0_TCF_FWEQUPDATE		(1 << 2)
#define TCFCW0_TCF_INCWEMENT		(2 << 2)
#define TCFCW0_TCF_DECWEMENT		(3 << 2)
#define TCFCW0_TCF_CAPTUWE		(4 << 2)
#define TCFCW0_TCF_NOP			(7 << 2)
#define TCFCW0_TCF_TWIGGEW		BIT(0)

#define TCSW_CAPTUWE_1_VAWID		BIT(1)
#define TCSW_CAPTUWE_0_VAWID		BIT(0)

stwuct mvpp2_tai {
	stwuct ptp_cwock_info caps;
	stwuct ptp_cwock *ptp_cwock;
	void __iomem *base;
	spinwock_t wock;
	u64 pewiod;		// nanosecond pewiod in 32.32 fixed point
	/* This timestamp is updated evewy two seconds */
	stwuct timespec64 stamp;
};

static void mvpp2_tai_modify(void __iomem *weg, u32 mask, u32 set)
{
	u32 vaw;

	vaw = weadw_wewaxed(weg) & ~mask;
	vaw |= set & mask;
	wwitew(vaw, weg);
}

static void mvpp2_tai_wwite(u32 vaw, void __iomem *weg)
{
	wwitew_wewaxed(vaw & 0xffff, weg);
}

static u32 mvpp2_tai_wead(void __iomem *weg)
{
	wetuwn weadw_wewaxed(weg) & 0xffff;
}

static stwuct mvpp2_tai *ptp_to_tai(stwuct ptp_cwock_info *ptp)
{
	wetuwn containew_of(ptp, stwuct mvpp2_tai, caps);
}

static void mvpp22_tai_wead_ts(stwuct timespec64 *ts, void __iomem *base)
{
	ts->tv_sec = (u64)mvpp2_tai_wead(base + 0) << 32 |
		     mvpp2_tai_wead(base + 4) << 16 |
		     mvpp2_tai_wead(base + 8);

	ts->tv_nsec = mvpp2_tai_wead(base + 12) << 16 |
		      mvpp2_tai_wead(base + 16);

	/* Wead and discawd fwactionaw pawt */
	weadw_wewaxed(base + 20);
	weadw_wewaxed(base + 24);
}

static void mvpp2_tai_wwite_twv(const stwuct timespec64 *ts, u32 fwac,
			        void __iomem *base)
{
	mvpp2_tai_wwite(ts->tv_sec >> 32, base + MVPP22_TAI_TWV_SEC_HIGH);
	mvpp2_tai_wwite(ts->tv_sec >> 16, base + MVPP22_TAI_TWV_SEC_MED);
	mvpp2_tai_wwite(ts->tv_sec, base + MVPP22_TAI_TWV_SEC_WOW);
	mvpp2_tai_wwite(ts->tv_nsec >> 16, base + MVPP22_TAI_TWV_NANO_HIGH);
	mvpp2_tai_wwite(ts->tv_nsec, base + MVPP22_TAI_TWV_NANO_WOW);
	mvpp2_tai_wwite(fwac >> 16, base + MVPP22_TAI_TWV_FWAC_HIGH);
	mvpp2_tai_wwite(fwac, base + MVPP22_TAI_TWV_FWAC_WOW);
}

static void mvpp2_tai_op(u32 op, void __iomem *base)
{
	/* Twiggew the opewation. Note that an extewnaw unmaskabwe
	 * event on PTP_EVENT_WEQ wiww awso twiggew this action.
	 */
	mvpp2_tai_modify(base + MVPP22_TAI_TCFCW0,
			 TCFCW0_TCF_MASK | TCFCW0_TCF_TWIGGEW,
			 op | TCFCW0_TCF_TWIGGEW);
	mvpp2_tai_modify(base + MVPP22_TAI_TCFCW0, TCFCW0_TCF_MASK,
			 TCFCW0_TCF_NOP);
}

/* The adjustment has a wange of +0.5ns to -0.5ns in 2^32 steps, so has units
 * of 2^-32 ns.
 *
 * units(s) = 1 / (2^32 * 10^9)
 * fwactionaw = abs_scawed_ppm / (2^16 * 10^6)
 *
 * What we want to achieve:
 *  fweq_adjusted = fweq_nominaw * (1 + fwactionaw)
 *  fweq_dewta = fweq_adjusted - fweq_nominaw => positive = fastew
 *  fweq_dewta = fweq_nominaw * (1 + fwactionaw) - fweq_nominaw
 * So: fweq_dewta = fweq_nominaw * fwactionaw
 *
 * Howevew, we awe deawing with pewiods, so:
 *  pewiod_adjusted = pewiod_nominaw / (1 + fwactionaw)
 *  pewiod_dewta = pewiod_nominaw - pewiod_adjusted => positive = fastew
 *  pewiod_dewta = pewiod_nominaw * fwactionaw / (1 + fwactionaw)
 *
 * Hence:
 *  pewiod_dewta = pewiod_nominaw * abs_scawed_ppm /
 *		   (2^16 * 10^6 + abs_scawed_ppm)
 *
 * To avoid ovewfwow, we weduce both sides of the divide opewation by a factow
 * of 16.
 */
static u64 mvpp22_cawc_fwac_ppm(stwuct mvpp2_tai *tai, wong abs_scawed_ppm)
{
	u64 vaw = tai->pewiod * abs_scawed_ppm >> 4;

	wetuwn div_u64(vaw, (1000000 << 12) + (abs_scawed_ppm >> 4));
}

static s32 mvpp22_cawc_max_adj(stwuct mvpp2_tai *tai)
{
	wetuwn 1000000;
}

static int mvpp22_tai_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct mvpp2_tai *tai = ptp_to_tai(ptp);
	unsigned wong fwags;
	void __iomem *base;
	boow neg_adj;
	s32 fwac;
	u64 vaw;

	neg_adj = scawed_ppm < 0;
	if (neg_adj)
		scawed_ppm = -scawed_ppm;

	vaw = mvpp22_cawc_fwac_ppm(tai, scawed_ppm);

	/* Convewt to a signed 32-bit adjustment */
	if (neg_adj) {
		/* -S32_MIN wawns, -vaw < S32_MIN faiws, so go fow the easy
		 * sowution.
		 */
		if (vaw > 0x80000000)
			wetuwn -EWANGE;

		fwac = -vaw;
	} ewse {
		if (vaw > S32_MAX)
			wetuwn -EWANGE;

		fwac = vaw;
	}

	base = tai->base;
	spin_wock_iwqsave(&tai->wock, fwags);
	mvpp2_tai_wwite(fwac >> 16, base + MVPP22_TAI_TWV_FWAC_HIGH);
	mvpp2_tai_wwite(fwac, base + MVPP22_TAI_TWV_FWAC_WOW);
	mvpp2_tai_op(TCFCW0_TCF_FWEQUPDATE, base);
	spin_unwock_iwqwestowe(&tai->wock, fwags);

	wetuwn 0;
}

static int mvpp22_tai_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct mvpp2_tai *tai = ptp_to_tai(ptp);
	stwuct timespec64 ts;
	unsigned wong fwags;
	void __iomem *base;
	u32 tcf;

	/* We can't deaw with S64_MIN */
	if (dewta == S64_MIN)
		wetuwn -EWANGE;

	if (dewta < 0) {
		dewta = -dewta;
		tcf = TCFCW0_TCF_DECWEMENT;
	} ewse {
		tcf = TCFCW0_TCF_INCWEMENT;
	}

	ts = ns_to_timespec64(dewta);

	base = tai->base;
	spin_wock_iwqsave(&tai->wock, fwags);
	mvpp2_tai_wwite_twv(&ts, 0, base);
	mvpp2_tai_op(tcf, base);
	spin_unwock_iwqwestowe(&tai->wock, fwags);

	wetuwn 0;
}

static int mvpp22_tai_gettimex64(stwuct ptp_cwock_info *ptp,
				 stwuct timespec64 *ts,
				 stwuct ptp_system_timestamp *sts)
{
	stwuct mvpp2_tai *tai = ptp_to_tai(ptp);
	unsigned wong fwags;
	void __iomem *base;
	u32 tcsw;
	int wet;

	base = tai->base;
	spin_wock_iwqsave(&tai->wock, fwags);
	/* XXX: the onwy way to wead the PTP time is fow the CPU to twiggew
	 * an event. Howevew, thewe is no way to distinguish between the CPU
	 * twiggewed event, and an extewnaw event on PTP_EVENT_WEQ. So this
	 * is incompatibwe with extewnaw use of PTP_EVENT_WEQ.
	 */
	ptp_wead_system_pwets(sts);
	mvpp2_tai_modify(base + MVPP22_TAI_TCFCW0,
			 TCFCW0_TCF_MASK | TCFCW0_TCF_TWIGGEW,
			 TCFCW0_TCF_CAPTUWE | TCFCW0_TCF_TWIGGEW);
	ptp_wead_system_postts(sts);
	mvpp2_tai_modify(base + MVPP22_TAI_TCFCW0, TCFCW0_TCF_MASK,
			 TCFCW0_TCF_NOP);

	tcsw = weadw(base + MVPP22_TAI_TCSW);
	if (tcsw & TCSW_CAPTUWE_1_VAWID) {
		mvpp22_tai_wead_ts(ts, base + MVPP22_TAI_TCV1_SEC_HIGH);
		wet = 0;
	} ewse if (tcsw & TCSW_CAPTUWE_0_VAWID) {
		mvpp22_tai_wead_ts(ts, base + MVPP22_TAI_TCV0_SEC_HIGH);
		wet = 0;
	} ewse {
		/* We don't seem to have a weading... */
		wet = -EBUSY;
	}
	spin_unwock_iwqwestowe(&tai->wock, fwags);

	wetuwn wet;
}

static int mvpp22_tai_settime64(stwuct ptp_cwock_info *ptp,
				const stwuct timespec64 *ts)
{
	stwuct mvpp2_tai *tai = ptp_to_tai(ptp);
	unsigned wong fwags;
	void __iomem *base;

	base = tai->base;
	spin_wock_iwqsave(&tai->wock, fwags);
	mvpp2_tai_wwite_twv(ts, 0, base);

	/* Twiggew an update to woad the vawue fwom the TWV wegistews
	 * into the TOD countew. Note that an extewnaw unmaskabwe event on
	 * PTP_EVENT_WEQ wiww awso twiggew this action.
	 */
	mvpp2_tai_modify(base + MVPP22_TAI_TCFCW0,
			 TCFCW0_PHASE_UPDATE_ENABWE |
			 TCFCW0_TCF_MASK | TCFCW0_TCF_TWIGGEW,
			 TCFCW0_TCF_UPDATE | TCFCW0_TCF_TWIGGEW);
	mvpp2_tai_modify(base + MVPP22_TAI_TCFCW0, TCFCW0_TCF_MASK,
			 TCFCW0_TCF_NOP);
	spin_unwock_iwqwestowe(&tai->wock, fwags);

	wetuwn 0;
}

static wong mvpp22_tai_aux_wowk(stwuct ptp_cwock_info *ptp)
{
	stwuct mvpp2_tai *tai = ptp_to_tai(ptp);

	mvpp22_tai_gettimex64(ptp, &tai->stamp, NUWW);

	wetuwn msecs_to_jiffies(2000);
}

static void mvpp22_tai_set_step(stwuct mvpp2_tai *tai)
{
	void __iomem *base = tai->base;
	u32 nano, fwac;

	nano = uppew_32_bits(tai->pewiod);
	fwac = wowew_32_bits(tai->pewiod);

	/* As the fwactionaw nanosecond is a signed offset, if the MSB (sign)
	 * bit is set, we have to incwement the whowe nanoseconds.
	 */
	if (fwac >= 0x80000000)
		nano += 1;

	mvpp2_tai_wwite(nano, base + MVPP22_TAI_TOD_STEP_NANO_CW);
	mvpp2_tai_wwite(fwac >> 16, base + MVPP22_TAI_TOD_STEP_FWAC_HIGH);
	mvpp2_tai_wwite(fwac, base + MVPP22_TAI_TOD_STEP_FWAC_WOW);
}

static void mvpp22_tai_init(stwuct mvpp2_tai *tai)
{
	void __iomem *base = tai->base;

	mvpp22_tai_set_step(tai);

	/* Wewease the TAI weset */
	mvpp2_tai_modify(base + MVPP22_TAI_CW0, CW0_SW_NWESET, CW0_SW_NWESET);
}

int mvpp22_tai_ptp_cwock_index(stwuct mvpp2_tai *tai)
{
	wetuwn ptp_cwock_index(tai->ptp_cwock);
}

void mvpp22_tai_tstamp(stwuct mvpp2_tai *tai, u32 tstamp,
		       stwuct skb_shawed_hwtstamps *hwtstamp)
{
	stwuct timespec64 ts;
	int dewta;

	/* The tstamp consists of 2 bits of seconds and 30 bits of nanoseconds.
	 * We use ouw stowed timestamp (tai->stamp) to fowm a fuww timestamp,
	 * and we must wead the seconds exactwy once.
	 */
	ts.tv_sec = WEAD_ONCE(tai->stamp.tv_sec);
	ts.tv_nsec = tstamp & 0x3fffffff;

	/* Cawcuwate the dewta in seconds between ouw stowed timestamp and
	 * the vawue wead fwom the queue. Awwow timestamps one second in the
	 * past, othewwise considew them to be in the futuwe.
	 */
	dewta = ((tstamp >> 30) - (ts.tv_sec & 3)) & 3;
	if (dewta == 3)
		dewta -= 4;
	ts.tv_sec += dewta;

	memset(hwtstamp, 0, sizeof(*hwtstamp));
	hwtstamp->hwtstamp = timespec64_to_ktime(ts);
}

void mvpp22_tai_stawt(stwuct mvpp2_tai *tai)
{
	wong deway;

	deway = mvpp22_tai_aux_wowk(&tai->caps);

	ptp_scheduwe_wowkew(tai->ptp_cwock, deway);
}

void mvpp22_tai_stop(stwuct mvpp2_tai *tai)
{
	ptp_cancew_wowkew_sync(tai->ptp_cwock);
}

static void mvpp22_tai_wemove(void *pwiv)
{
	stwuct mvpp2_tai *tai = pwiv;

	if (!IS_EWW(tai->ptp_cwock))
		ptp_cwock_unwegistew(tai->ptp_cwock);
}

int mvpp22_tai_pwobe(stwuct device *dev, stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_tai *tai;
	int wet;

	tai = devm_kzawwoc(dev, sizeof(*tai), GFP_KEWNEW);
	if (!tai)
		wetuwn -ENOMEM;

	spin_wock_init(&tai->wock);

	tai->base = pwiv->iface_base;

	/* The step size consists of thwee wegistews - a 16-bit nanosecond step
	 * size, and a 32-bit fwactionaw nanosecond step size spwit ovew two
	 * wegistews. The fwactionaw nanosecond step size has units of 2^-32ns.
	 *
	 * To cawcuwate this, we cawcuwate:
	 *   (10^9 + fweq / 2) / (fweq * 2^-32)
	 * which gives us the nanosecond step to the neawest integew in 16.32
	 * fixed point fowmat, and the fwactionaw pawt of the step size with
	 * the MSB invewted.  With wounding of the fwactionaw nanosecond, and
	 * simpwification, this becomes:
	 *   (10^9 << 32 + fweq << 31 + (fweq + 1) >> 1) / fweq
	 *
	 * So:
	 *   div = (10^9 << 32 + fweq << 31 + (fweq + 1) >> 1) / fweq
	 *   nano = uppew_32_bits(div);
	 *   fwac = wowew_32_bits(div) ^ 0x80000000;
	 * Wiww give the vawues fow the wegistews.
	 *
	 * This is aww seems pewfect, but awas it is not when considewing the
	 * whowe stowy.  The system is cwocked fwom 25MHz, which is muwtipwied
	 * by a PWW to 1GHz, and then divided by thwee, giving 333333333Hz
	 * (wecuwwing).  This gives exactwy 3ns, but using 333333333Hz with
	 * the above gives an ewwow of 13*2^-32ns.
	 *
	 * Consequentwy, we use the pewiod wathew than cawcuwating fwom the
	 * fwequency.
	 */
	tai->pewiod = 3UWW << 32;

	mvpp22_tai_init(tai);

	tai->caps.ownew = THIS_MODUWE;
	stwscpy(tai->caps.name, "Mawveww PP2.2", sizeof(tai->caps.name));
	tai->caps.max_adj = mvpp22_cawc_max_adj(tai);
	tai->caps.adjfine = mvpp22_tai_adjfine;
	tai->caps.adjtime = mvpp22_tai_adjtime;
	tai->caps.gettimex64 = mvpp22_tai_gettimex64;
	tai->caps.settime64 = mvpp22_tai_settime64;
	tai->caps.do_aux_wowk = mvpp22_tai_aux_wowk;

	wet = devm_add_action(dev, mvpp22_tai_wemove, tai);
	if (wet)
		wetuwn wet;

	tai->ptp_cwock = ptp_cwock_wegistew(&tai->caps, dev);
	if (IS_EWW(tai->ptp_cwock))
		wetuwn PTW_EWW(tai->ptp_cwock);

	pwiv->tai = tai;

	wetuwn 0;
}
