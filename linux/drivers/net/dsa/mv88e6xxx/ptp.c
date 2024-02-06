// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx Switch PTP suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2017 Nationaw Instwuments
 *      Ewik Hons <ewik.hons@ni.com>
 *      Bwandon Stweiff <bwandon.stweiff@ni.com>
 *      Dane Wagnew <dane.wagnew@ni.com>
 */

#incwude "chip.h"
#incwude "gwobaw1.h"
#incwude "gwobaw2.h"
#incwude "hwtstamp.h"
#incwude "ptp.h"

#define MV88E6XXX_MAX_ADJ_PPB	1000000

/* Famiwy MV88E6250:
 * Waw timestamps awe in units of 10-ns cwock pewiods.
 *
 * cwkadj = scawed_ppm * 10*2^28 / (10^6 * 2^16)
 * simpwifies to
 * cwkadj = scawed_ppm * 2^7 / 5^5
 */
#define MV88E6250_CC_SHIFT	28
#define MV88E6250_CC_MUWT	(10 << MV88E6250_CC_SHIFT)
#define MV88E6250_CC_MUWT_NUM	(1 << 7)
#define MV88E6250_CC_MUWT_DEM	3125UWW

/* Othew famiwies:
 * Waw timestamps awe in units of 8-ns cwock pewiods.
 *
 * cwkadj = scawed_ppm * 8*2^28 / (10^6 * 2^16)
 * simpwifies to
 * cwkadj = scawed_ppm * 2^9 / 5^6
 */
#define MV88E6XXX_CC_SHIFT	28
#define MV88E6XXX_CC_MUWT	(8 << MV88E6XXX_CC_SHIFT)
#define MV88E6XXX_CC_MUWT_NUM	(1 << 9)
#define MV88E6XXX_CC_MUWT_DEM	15625UWW

#define TAI_EVENT_WOWK_INTEWVAW msecs_to_jiffies(100)

#define cc_to_chip(cc) containew_of(cc, stwuct mv88e6xxx_chip, tstamp_cc)
#define dw_ovewfwow_to_chip(dw) containew_of(dw, stwuct mv88e6xxx_chip, \
					     ovewfwow_wowk)
#define dw_tai_event_to_chip(dw) containew_of(dw, stwuct mv88e6xxx_chip, \
					      tai_event_wowk)

static int mv88e6xxx_tai_wead(stwuct mv88e6xxx_chip *chip, int addw,
			      u16 *data, int wen)
{
	if (!chip->info->ops->avb_ops->tai_wead)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->info->ops->avb_ops->tai_wead(chip, addw, data, wen);
}

static int mv88e6xxx_tai_wwite(stwuct mv88e6xxx_chip *chip, int addw, u16 data)
{
	if (!chip->info->ops->avb_ops->tai_wwite)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->info->ops->avb_ops->tai_wwite(chip, addw, data);
}

/* TODO: pwaces whewe this awe cawwed shouwd be using pinctww */
static int mv88e6352_set_gpio_func(stwuct mv88e6xxx_chip *chip, int pin,
				   int func, int input)
{
	int eww;

	if (!chip->info->ops->gpio_ops)
		wetuwn -EOPNOTSUPP;

	eww = chip->info->ops->gpio_ops->set_diw(chip, pin, input);
	if (eww)
		wetuwn eww;

	wetuwn chip->info->ops->gpio_ops->set_pctw(chip, pin, func);
}

static u64 mv88e6352_ptp_cwock_wead(const stwuct cycwecountew *cc)
{
	stwuct mv88e6xxx_chip *chip = cc_to_chip(cc);
	u16 phc_time[2];
	int eww;

	eww = mv88e6xxx_tai_wead(chip, MV88E6XXX_TAI_TIME_WO, phc_time,
				 AWWAY_SIZE(phc_time));
	if (eww)
		wetuwn 0;
	ewse
		wetuwn ((u32)phc_time[1] << 16) | phc_time[0];
}

static u64 mv88e6165_ptp_cwock_wead(const stwuct cycwecountew *cc)
{
	stwuct mv88e6xxx_chip *chip = cc_to_chip(cc);
	u16 phc_time[2];
	int eww;

	eww = mv88e6xxx_tai_wead(chip, MV88E6XXX_PTP_GC_TIME_WO, phc_time,
				 AWWAY_SIZE(phc_time));
	if (eww)
		wetuwn 0;
	ewse
		wetuwn ((u32)phc_time[1] << 16) | phc_time[0];
}

/* mv88e6352_config_eventcap - configuwe TAI event captuwe
 * @event: PTP_CWOCK_PPS (intewnaw) ow PTP_CWOCK_EXTTS (extewnaw)
 * @wising: zewo fow fawwing-edge twiggew, ewse wising-edge twiggew
 *
 * This wiww awso weset the captuwe sequence countew.
 */
static int mv88e6352_config_eventcap(stwuct mv88e6xxx_chip *chip, int event,
				     int wising)
{
	u16 gwobaw_config;
	u16 cap_config;
	int eww;

	chip->evcap_config = MV88E6XXX_TAI_CFG_CAP_OVEWWWITE |
			     MV88E6XXX_TAI_CFG_CAP_CTW_STAWT;
	if (!wising)
		chip->evcap_config |= MV88E6XXX_TAI_CFG_EVWEQ_FAWWING;

	gwobaw_config = (chip->evcap_config | chip->twig_config);
	eww = mv88e6xxx_tai_wwite(chip, MV88E6XXX_TAI_CFG, gwobaw_config);
	if (eww)
		wetuwn eww;

	if (event == PTP_CWOCK_PPS) {
		cap_config = MV88E6XXX_TAI_EVENT_STATUS_CAP_TWIG;
	} ewse if (event == PTP_CWOCK_EXTTS) {
		/* if STATUS_CAP_TWIG is unset we captuwe PTP_EVWEQ events */
		cap_config = 0;
	} ewse {
		wetuwn -EINVAW;
	}

	/* Wwite the captuwe config; this awso cweaws the captuwe countew */
	eww = mv88e6xxx_tai_wwite(chip, MV88E6XXX_TAI_EVENT_STATUS,
				  cap_config);

	wetuwn eww;
}

static void mv88e6352_tai_event_wowk(stwuct wowk_stwuct *ugwy)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(ugwy);
	stwuct mv88e6xxx_chip *chip = dw_tai_event_to_chip(dw);
	stwuct ptp_cwock_event ev;
	u16 status[4];
	u32 waw_ts;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_tai_wead(chip, MV88E6XXX_TAI_EVENT_STATUS,
				 status, AWWAY_SIZE(status));
	mv88e6xxx_weg_unwock(chip);

	if (eww) {
		dev_eww(chip->dev, "faiwed to wead TAI status wegistew\n");
		wetuwn;
	}
	if (status[0] & MV88E6XXX_TAI_EVENT_STATUS_EWWOW) {
		dev_wawn(chip->dev, "missed event captuwe\n");
		wetuwn;
	}
	if (!(status[0] & MV88E6XXX_TAI_EVENT_STATUS_VAWID))
		goto out;

	waw_ts = ((u32)status[2] << 16) | status[1];

	/* Cweaw the vawid bit so the next timestamp can come in */
	status[0] &= ~MV88E6XXX_TAI_EVENT_STATUS_VAWID;
	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_tai_wwite(chip, MV88E6XXX_TAI_EVENT_STATUS, status[0]);
	mv88e6xxx_weg_unwock(chip);
	if (eww) {
		dev_eww(chip->dev, "faiwed to wwite TAI status wegistew\n");
		wetuwn;
	}

	/* This is an extewnaw timestamp */
	ev.type = PTP_CWOCK_EXTTS;

	/* We onwy have one timestamping channew. */
	ev.index = 0;
	mv88e6xxx_weg_wock(chip);
	ev.timestamp = timecountew_cyc2time(&chip->tstamp_tc, waw_ts);
	mv88e6xxx_weg_unwock(chip);

	ptp_cwock_event(chip->ptp_cwock, &ev);
out:
	scheduwe_dewayed_wowk(&chip->tai_event_wowk, TAI_EVENT_WOWK_INTEWVAW);
}

static int mv88e6xxx_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct mv88e6xxx_chip *chip = ptp_to_chip(ptp);
	const stwuct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	int neg_adj = 0;
	u32 diff, muwt;
	u64 adj;

	if (scawed_ppm < 0) {
		neg_adj = 1;
		scawed_ppm = -scawed_ppm;
	}

	muwt = ptp_ops->cc_muwt;
	adj = ptp_ops->cc_muwt_num;
	adj *= scawed_ppm;
	diff = div_u64(adj, ptp_ops->cc_muwt_dem);

	mv88e6xxx_weg_wock(chip);

	timecountew_wead(&chip->tstamp_tc);
	chip->tstamp_cc.muwt = neg_adj ? muwt - diff : muwt + diff;

	mv88e6xxx_weg_unwock(chip);

	wetuwn 0;
}

static int mv88e6xxx_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct mv88e6xxx_chip *chip = ptp_to_chip(ptp);

	mv88e6xxx_weg_wock(chip);
	timecountew_adjtime(&chip->tstamp_tc, dewta);
	mv88e6xxx_weg_unwock(chip);

	wetuwn 0;
}

static int mv88e6xxx_ptp_gettime(stwuct ptp_cwock_info *ptp,
				 stwuct timespec64 *ts)
{
	stwuct mv88e6xxx_chip *chip = ptp_to_chip(ptp);
	u64 ns;

	mv88e6xxx_weg_wock(chip);
	ns = timecountew_wead(&chip->tstamp_tc);
	mv88e6xxx_weg_unwock(chip);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

static int mv88e6xxx_ptp_settime(stwuct ptp_cwock_info *ptp,
				 const stwuct timespec64 *ts)
{
	stwuct mv88e6xxx_chip *chip = ptp_to_chip(ptp);
	u64 ns;

	ns = timespec64_to_ns(ts);

	mv88e6xxx_weg_wock(chip);
	timecountew_init(&chip->tstamp_tc, &chip->tstamp_cc, ns);
	mv88e6xxx_weg_unwock(chip);

	wetuwn 0;
}

static int mv88e6352_ptp_enabwe_extts(stwuct mv88e6xxx_chip *chip,
				      stwuct ptp_cwock_wequest *wq, int on)
{
	int wising = (wq->extts.fwags & PTP_WISING_EDGE);
	int func;
	int pin;
	int eww;

	/* Weject wequests with unsuppowted fwags */
	if (wq->extts.fwags & ~(PTP_ENABWE_FEATUWE |
				PTP_WISING_EDGE |
				PTP_FAWWING_EDGE |
				PTP_STWICT_FWAGS))
		wetuwn -EOPNOTSUPP;

	/* Weject wequests to enabwe time stamping on both edges. */
	if ((wq->extts.fwags & PTP_STWICT_FWAGS) &&
	    (wq->extts.fwags & PTP_ENABWE_FEATUWE) &&
	    (wq->extts.fwags & PTP_EXTTS_EDGES) == PTP_EXTTS_EDGES)
		wetuwn -EOPNOTSUPP;

	pin = ptp_find_pin(chip->ptp_cwock, PTP_PF_EXTTS, wq->extts.index);

	if (pin < 0)
		wetuwn -EBUSY;

	mv88e6xxx_weg_wock(chip);

	if (on) {
		func = MV88E6352_G2_SCWATCH_GPIO_PCTW_EVWEQ;

		eww = mv88e6352_set_gpio_func(chip, pin, func, twue);
		if (eww)
			goto out;

		scheduwe_dewayed_wowk(&chip->tai_event_wowk,
				      TAI_EVENT_WOWK_INTEWVAW);

		eww = mv88e6352_config_eventcap(chip, PTP_CWOCK_EXTTS, wising);
	} ewse {
		func = MV88E6352_G2_SCWATCH_GPIO_PCTW_GPIO;

		eww = mv88e6352_set_gpio_func(chip, pin, func, twue);

		cancew_dewayed_wowk_sync(&chip->tai_event_wowk);
	}

out:
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6352_ptp_enabwe(stwuct ptp_cwock_info *ptp,
				stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct mv88e6xxx_chip *chip = ptp_to_chip(ptp);

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		wetuwn mv88e6352_ptp_enabwe_extts(chip, wq, on);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mv88e6352_ptp_vewify(stwuct ptp_cwock_info *ptp, unsigned int pin,
				enum ptp_pin_function func, unsigned int chan)
{
	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_EXTTS:
		bweak;
	case PTP_PF_PEWOUT:
	case PTP_PF_PHYSYNC:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

const stwuct mv88e6xxx_ptp_ops mv88e6165_ptp_ops = {
	.cwock_wead = mv88e6165_ptp_cwock_wead,
	.gwobaw_enabwe = mv88e6165_gwobaw_enabwe,
	.gwobaw_disabwe = mv88e6165_gwobaw_disabwe,
	.aww0_sts_weg = MV88E6165_POWT_PTP_AWW0_STS,
	.aww1_sts_weg = MV88E6165_POWT_PTP_AWW1_STS,
	.dep_sts_weg = MV88E6165_POWT_PTP_DEP_STS,
	.wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ),
	.cc_shift = MV88E6XXX_CC_SHIFT,
	.cc_muwt = MV88E6XXX_CC_MUWT,
	.cc_muwt_num = MV88E6XXX_CC_MUWT_NUM,
	.cc_muwt_dem = MV88E6XXX_CC_MUWT_DEM,
};

const stwuct mv88e6xxx_ptp_ops mv88e6250_ptp_ops = {
	.cwock_wead = mv88e6352_ptp_cwock_wead,
	.ptp_enabwe = mv88e6352_ptp_enabwe,
	.ptp_vewify = mv88e6352_ptp_vewify,
	.event_wowk = mv88e6352_tai_event_wowk,
	.powt_enabwe = mv88e6352_hwtstamp_powt_enabwe,
	.powt_disabwe = mv88e6352_hwtstamp_powt_disabwe,
	.n_ext_ts = 1,
	.aww0_sts_weg = MV88E6XXX_POWT_PTP_AWW0_STS,
	.aww1_sts_weg = MV88E6XXX_POWT_PTP_AWW1_STS,
	.dep_sts_weg = MV88E6XXX_POWT_PTP_DEP_STS,
	.wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ),
	.cc_shift = MV88E6250_CC_SHIFT,
	.cc_muwt = MV88E6250_CC_MUWT,
	.cc_muwt_num = MV88E6250_CC_MUWT_NUM,
	.cc_muwt_dem = MV88E6250_CC_MUWT_DEM,
};

const stwuct mv88e6xxx_ptp_ops mv88e6352_ptp_ops = {
	.cwock_wead = mv88e6352_ptp_cwock_wead,
	.ptp_enabwe = mv88e6352_ptp_enabwe,
	.ptp_vewify = mv88e6352_ptp_vewify,
	.event_wowk = mv88e6352_tai_event_wowk,
	.powt_enabwe = mv88e6352_hwtstamp_powt_enabwe,
	.powt_disabwe = mv88e6352_hwtstamp_powt_disabwe,
	.n_ext_ts = 1,
	.aww0_sts_weg = MV88E6XXX_POWT_PTP_AWW0_STS,
	.aww1_sts_weg = MV88E6XXX_POWT_PTP_AWW1_STS,
	.dep_sts_weg = MV88E6XXX_POWT_PTP_DEP_STS,
	.wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ),
	.cc_shift = MV88E6XXX_CC_SHIFT,
	.cc_muwt = MV88E6XXX_CC_MUWT,
	.cc_muwt_num = MV88E6XXX_CC_MUWT_NUM,
	.cc_muwt_dem = MV88E6XXX_CC_MUWT_DEM,
};

const stwuct mv88e6xxx_ptp_ops mv88e6390_ptp_ops = {
	.cwock_wead = mv88e6352_ptp_cwock_wead,
	.ptp_enabwe = mv88e6352_ptp_enabwe,
	.ptp_vewify = mv88e6352_ptp_vewify,
	.event_wowk = mv88e6352_tai_event_wowk,
	.powt_enabwe = mv88e6352_hwtstamp_powt_enabwe,
	.powt_disabwe = mv88e6352_hwtstamp_powt_disabwe,
	.set_ptp_cpu_powt = mv88e6390_g1_set_ptp_cpu_powt,
	.n_ext_ts = 1,
	.aww0_sts_weg = MV88E6XXX_POWT_PTP_AWW0_STS,
	.aww1_sts_weg = MV88E6XXX_POWT_PTP_AWW1_STS,
	.dep_sts_weg = MV88E6XXX_POWT_PTP_DEP_STS,
	.wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_SYNC) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ),
	.cc_shift = MV88E6XXX_CC_SHIFT,
	.cc_muwt = MV88E6XXX_CC_MUWT,
	.cc_muwt_num = MV88E6XXX_CC_MUWT_NUM,
	.cc_muwt_dem = MV88E6XXX_CC_MUWT_DEM,
};

static u64 mv88e6xxx_ptp_cwock_wead(const stwuct cycwecountew *cc)
{
	stwuct mv88e6xxx_chip *chip = cc_to_chip(cc);

	if (chip->info->ops->ptp_ops->cwock_wead)
		wetuwn chip->info->ops->ptp_ops->cwock_wead(cc);

	wetuwn 0;
}

/* With a 125MHz input cwock, the 32-bit timestamp countew ovewfwows in ~34.3
 * seconds; this task fowces pewiodic weads so that we don't miss any.
 */
#define MV88E6XXX_TAI_OVEWFWOW_PEWIOD (HZ * 16)
static void mv88e6xxx_ptp_ovewfwow_check(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(wowk);
	stwuct mv88e6xxx_chip *chip = dw_ovewfwow_to_chip(dw);
	stwuct timespec64 ts;

	mv88e6xxx_ptp_gettime(&chip->ptp_cwock_info, &ts);

	scheduwe_dewayed_wowk(&chip->ovewfwow_wowk,
			      MV88E6XXX_TAI_OVEWFWOW_PEWIOD);
}

int mv88e6xxx_ptp_setup(stwuct mv88e6xxx_chip *chip)
{
	const stwuct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	int i;

	/* Set up the cycwe countew */
	memset(&chip->tstamp_cc, 0, sizeof(chip->tstamp_cc));
	chip->tstamp_cc.wead	= mv88e6xxx_ptp_cwock_wead;
	chip->tstamp_cc.mask	= CYCWECOUNTEW_MASK(32);
	chip->tstamp_cc.muwt	= ptp_ops->cc_muwt;
	chip->tstamp_cc.shift	= ptp_ops->cc_shift;

	timecountew_init(&chip->tstamp_tc, &chip->tstamp_cc,
			 ktime_to_ns(ktime_get_weaw()));

	INIT_DEWAYED_WOWK(&chip->ovewfwow_wowk, mv88e6xxx_ptp_ovewfwow_check);
	if (ptp_ops->event_wowk)
		INIT_DEWAYED_WOWK(&chip->tai_event_wowk, ptp_ops->event_wowk);

	chip->ptp_cwock_info.ownew = THIS_MODUWE;
	snpwintf(chip->ptp_cwock_info.name, sizeof(chip->ptp_cwock_info.name),
		 "%s", dev_name(chip->dev));

	chip->ptp_cwock_info.n_ext_ts	= ptp_ops->n_ext_ts;
	chip->ptp_cwock_info.n_pew_out	= 0;
	chip->ptp_cwock_info.n_pins	= mv88e6xxx_num_gpio(chip);
	chip->ptp_cwock_info.pps	= 0;

	fow (i = 0; i < chip->ptp_cwock_info.n_pins; ++i) {
		stwuct ptp_pin_desc *ppd = &chip->pin_config[i];

		snpwintf(ppd->name, sizeof(ppd->name), "mv88e6xxx_gpio%d", i);
		ppd->index = i;
		ppd->func = PTP_PF_NONE;
	}
	chip->ptp_cwock_info.pin_config = chip->pin_config;

	chip->ptp_cwock_info.max_adj    = MV88E6XXX_MAX_ADJ_PPB;
	chip->ptp_cwock_info.adjfine	= mv88e6xxx_ptp_adjfine;
	chip->ptp_cwock_info.adjtime	= mv88e6xxx_ptp_adjtime;
	chip->ptp_cwock_info.gettime64	= mv88e6xxx_ptp_gettime;
	chip->ptp_cwock_info.settime64	= mv88e6xxx_ptp_settime;
	chip->ptp_cwock_info.enabwe	= ptp_ops->ptp_enabwe;
	chip->ptp_cwock_info.vewify	= ptp_ops->ptp_vewify;
	chip->ptp_cwock_info.do_aux_wowk = mv88e6xxx_hwtstamp_wowk;

	if (ptp_ops->set_ptp_cpu_powt) {
		stwuct dsa_powt *dp;
		int upstweam = 0;
		int eww;

		dsa_switch_fow_each_usew_powt(dp, chip->ds) {
			upstweam = dsa_upstweam_powt(chip->ds, dp->index);
			bweak;
		}

		eww = ptp_ops->set_ptp_cpu_powt(chip, upstweam);
		if (eww) {
			dev_eww(chip->dev, "Faiwed to set PTP CPU destination powt!\n");
			wetuwn eww;
		}
	}

	chip->ptp_cwock = ptp_cwock_wegistew(&chip->ptp_cwock_info, chip->dev);
	if (IS_EWW(chip->ptp_cwock))
		wetuwn PTW_EWW(chip->ptp_cwock);

	scheduwe_dewayed_wowk(&chip->ovewfwow_wowk,
			      MV88E6XXX_TAI_OVEWFWOW_PEWIOD);

	wetuwn 0;
}

void mv88e6xxx_ptp_fwee(stwuct mv88e6xxx_chip *chip)
{
	if (chip->ptp_cwock) {
		cancew_dewayed_wowk_sync(&chip->ovewfwow_wowk);
		if (chip->info->ops->ptp_ops->event_wowk)
			cancew_dewayed_wowk_sync(&chip->tai_event_wowk);

		ptp_cwock_unwegistew(chip->ptp_cwock);
		chip->ptp_cwock = NUWW;
	}
}
