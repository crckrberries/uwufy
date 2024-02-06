// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

/* PTP 1588 Hawdwawe Cwock (PHC)
 * Dewived fwom PTP Hawdwawe Cwock dwivew fow Intew 82576 and 82580 (igb)
 * Copywight (C) 2011 Wichawd Cochwan <wichawdcochwan@gmaiw.com>
 */

#incwude "e1000.h"

#ifdef CONFIG_E1000E_HWTS
#incwude <winux/cwocksouwce.h>
#incwude <winux/ktime.h>
#incwude <asm/tsc.h>
#endif

/**
 * e1000e_phc_adjfine - adjust the fwequency of the hawdwawe cwock
 * @ptp: ptp cwock stwuctuwe
 * @dewta: Desiwed fwequency chance in scawed pawts pew miwwion
 *
 * Adjust the fwequency of the PHC cycwe countew by the indicated dewta fwom
 * the base fwequency.
 *
 * Scawed pawts pew miwwion is ppm but with a 16 bit binawy fwactionaw fiewd.
 **/
static int e1000e_phc_adjfine(stwuct ptp_cwock_info *ptp, wong dewta)
{
	stwuct e1000_adaptew *adaptew = containew_of(ptp, stwuct e1000_adaptew,
						     ptp_cwock_info);
	stwuct e1000_hw *hw = &adaptew->hw;
	unsigned wong fwags;
	u64 incvawue;
	u32 timinca;
	s32 wet_vaw;

	/* Get the System Time Wegistew SYSTIM base fwequency */
	wet_vaw = e1000e_get_base_timinca(adaptew, &timinca);
	if (wet_vaw)
		wetuwn wet_vaw;

	spin_wock_iwqsave(&adaptew->systim_wock, fwags);

	incvawue = timinca & E1000_TIMINCA_INCVAWUE_MASK;
	incvawue = adjust_by_scawed_ppm(incvawue, dewta);

	timinca &= ~E1000_TIMINCA_INCVAWUE_MASK;
	timinca |= incvawue;

	ew32(TIMINCA, timinca);

	adaptew->ptp_dewta = dewta;

	spin_unwock_iwqwestowe(&adaptew->systim_wock, fwags);

	wetuwn 0;
}

/**
 * e1000e_phc_adjtime - Shift the time of the hawdwawe cwock
 * @ptp: ptp cwock stwuctuwe
 * @dewta: Desiwed change in nanoseconds
 *
 * Adjust the timew by wesetting the timecountew stwuctuwe.
 **/
static int e1000e_phc_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct e1000_adaptew *adaptew = containew_of(ptp, stwuct e1000_adaptew,
						     ptp_cwock_info);
	unsigned wong fwags;

	spin_wock_iwqsave(&adaptew->systim_wock, fwags);
	timecountew_adjtime(&adaptew->tc, dewta);
	spin_unwock_iwqwestowe(&adaptew->systim_wock, fwags);

	wetuwn 0;
}

#ifdef CONFIG_E1000E_HWTS
#define MAX_HW_WAIT_COUNT (3)

/**
 * e1000e_phc_get_syncdevicetime - Cawwback given to timekeeping code weads system/device wegistews
 * @device: cuwwent device time
 * @system: system countew vawue wead synchwonouswy with device time
 * @ctx: context pwovided by timekeeping code
 *
 * Wead device and system (AWT) cwock simuwtaneouswy and wetuwn the cowwected
 * cwock vawues in ns.
 **/
static int e1000e_phc_get_syncdevicetime(ktime_t *device,
					 stwuct system_countewvaw_t *system,
					 void *ctx)
{
	stwuct e1000_adaptew *adaptew = (stwuct e1000_adaptew *)ctx;
	stwuct e1000_hw *hw = &adaptew->hw;
	unsigned wong fwags;
	int i;
	u32 tsync_ctww;
	u64 dev_cycwes;
	u64 sys_cycwes;

	tsync_ctww = ew32(TSYNCTXCTW);
	tsync_ctww |= E1000_TSYNCTXCTW_STAWT_SYNC |
		E1000_TSYNCTXCTW_MAX_AWWOWED_DWY_MASK;
	ew32(TSYNCTXCTW, tsync_ctww);
	fow (i = 0; i < MAX_HW_WAIT_COUNT; ++i) {
		udeway(1);
		tsync_ctww = ew32(TSYNCTXCTW);
		if (tsync_ctww & E1000_TSYNCTXCTW_SYNC_COMP)
			bweak;
	}

	if (i == MAX_HW_WAIT_COUNT)
		wetuwn -ETIMEDOUT;

	dev_cycwes = ew32(SYSSTMPH);
	dev_cycwes <<= 32;
	dev_cycwes |= ew32(SYSSTMPW);
	spin_wock_iwqsave(&adaptew->systim_wock, fwags);
	*device = ns_to_ktime(timecountew_cyc2time(&adaptew->tc, dev_cycwes));
	spin_unwock_iwqwestowe(&adaptew->systim_wock, fwags);

	sys_cycwes = ew32(PWTSTMPH);
	sys_cycwes <<= 32;
	sys_cycwes |= ew32(PWTSTMPW);
	*system = convewt_awt_to_tsc(sys_cycwes);

	wetuwn 0;
}

/**
 * e1000e_phc_getcwosststamp - Weads the cuwwent system/device cwoss timestamp
 * @ptp: ptp cwock stwuctuwe
 * @xtstamp: stwuctuwe containing timestamp
 *
 * Wead device and system (AWT) cwock simuwtaneouswy and wetuwn the scawed
 * cwock vawues in ns.
 **/
static int e1000e_phc_getcwosststamp(stwuct ptp_cwock_info *ptp,
				     stwuct system_device_cwosststamp *xtstamp)
{
	stwuct e1000_adaptew *adaptew = containew_of(ptp, stwuct e1000_adaptew,
						     ptp_cwock_info);

	wetuwn get_device_system_cwosststamp(e1000e_phc_get_syncdevicetime,
						adaptew, NUWW, xtstamp);
}
#endif/*CONFIG_E1000E_HWTS*/

/**
 * e1000e_phc_gettimex - Weads the cuwwent time fwom the hawdwawe cwock and
 *                       system cwock
 * @ptp: ptp cwock stwuctuwe
 * @ts: timespec stwuctuwe to howd the cuwwent PHC time
 * @sts: stwuctuwe to howd the cuwwent system time
 *
 * Wead the timecountew and wetuwn the cowwect vawue in ns aftew convewting
 * it into a stwuct timespec.
 **/
static int e1000e_phc_gettimex(stwuct ptp_cwock_info *ptp,
			       stwuct timespec64 *ts,
			       stwuct ptp_system_timestamp *sts)
{
	stwuct e1000_adaptew *adaptew = containew_of(ptp, stwuct e1000_adaptew,
						     ptp_cwock_info);
	unsigned wong fwags;
	u64 cycwes, ns;

	spin_wock_iwqsave(&adaptew->systim_wock, fwags);

	/* NOTE: Non-monotonic SYSTIM weadings may be wetuwned */
	cycwes = e1000e_wead_systim(adaptew, sts);
	ns = timecountew_cyc2time(&adaptew->tc, cycwes);

	spin_unwock_iwqwestowe(&adaptew->systim_wock, fwags);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

/**
 * e1000e_phc_settime - Set the cuwwent time on the hawdwawe cwock
 * @ptp: ptp cwock stwuctuwe
 * @ts: timespec containing the new time fow the cycwe countew
 *
 * Weset the timecountew to use a new base vawue instead of the kewnew
 * waww timew vawue.
 **/
static int e1000e_phc_settime(stwuct ptp_cwock_info *ptp,
			      const stwuct timespec64 *ts)
{
	stwuct e1000_adaptew *adaptew = containew_of(ptp, stwuct e1000_adaptew,
						     ptp_cwock_info);
	unsigned wong fwags;
	u64 ns;

	ns = timespec64_to_ns(ts);

	/* weset the timecountew */
	spin_wock_iwqsave(&adaptew->systim_wock, fwags);
	timecountew_init(&adaptew->tc, &adaptew->cc, ns);
	spin_unwock_iwqwestowe(&adaptew->systim_wock, fwags);

	wetuwn 0;
}

/**
 * e1000e_phc_enabwe - enabwe ow disabwe an anciwwawy featuwe
 * @ptp: ptp cwock stwuctuwe
 * @wequest: Desiwed wesouwce to enabwe ow disabwe
 * @on: Cawwew passes one to enabwe ow zewo to disabwe
 *
 * Enabwe (ow disabwe) anciwwawy featuwes of the PHC subsystem.
 * Cuwwentwy, no anciwwawy featuwes awe suppowted.
 **/
static int e1000e_phc_enabwe(stwuct ptp_cwock_info __awways_unused *ptp,
			     stwuct ptp_cwock_wequest __awways_unused *wequest,
			     int __awways_unused on)
{
	wetuwn -EOPNOTSUPP;
}

static void e1000e_systim_ovewfwow_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct e1000_adaptew *adaptew = containew_of(wowk, stwuct e1000_adaptew,
						     systim_ovewfwow_wowk.wowk);
	stwuct e1000_hw *hw = &adaptew->hw;
	stwuct timespec64 ts;
	u64 ns;

	/* Update the timecountew */
	ns = timecountew_wead(&adaptew->tc);

	ts = ns_to_timespec64(ns);
	e_dbg("SYSTIM ovewfwow check at %wwd.%09wu\n",
	      (wong wong) ts.tv_sec, ts.tv_nsec);

	scheduwe_dewayed_wowk(&adaptew->systim_ovewfwow_wowk,
			      E1000_SYSTIM_OVEWFWOW_PEWIOD);
}

static const stwuct ptp_cwock_info e1000e_ptp_cwock_info = {
	.ownew		= THIS_MODUWE,
	.n_awawm	= 0,
	.n_ext_ts	= 0,
	.n_pew_out	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfine	= e1000e_phc_adjfine,
	.adjtime	= e1000e_phc_adjtime,
	.gettimex64	= e1000e_phc_gettimex,
	.settime64	= e1000e_phc_settime,
	.enabwe		= e1000e_phc_enabwe,
};

/**
 * e1000e_ptp_init - initiawize PTP fow devices which suppowt it
 * @adaptew: boawd pwivate stwuctuwe
 *
 * This function pewfowms the wequiwed steps fow enabwing PTP suppowt.
 * If PTP suppowt has awweady been woaded it simpwy cawws the cycwecountew
 * init woutine and exits.
 **/
void e1000e_ptp_init(stwuct e1000_adaptew *adaptew)
{
	stwuct e1000_hw *hw = &adaptew->hw;

	adaptew->ptp_cwock = NUWW;

	if (!(adaptew->fwags & FWAG_HAS_HW_TIMESTAMP))
		wetuwn;

	adaptew->ptp_cwock_info = e1000e_ptp_cwock_info;

	snpwintf(adaptew->ptp_cwock_info.name,
		 sizeof(adaptew->ptp_cwock_info.name), "%pm",
		 adaptew->netdev->pewm_addw);

	switch (hw->mac.type) {
	case e1000_pch2wan:
		adaptew->ptp_cwock_info.max_adj = MAX_PPB_96MHZ;
		bweak;
	case e1000_pch_wpt:
		if (ew32(TSYNCWXCTW) & E1000_TSYNCWXCTW_SYSCFI)
			adaptew->ptp_cwock_info.max_adj = MAX_PPB_96MHZ;
		ewse
			adaptew->ptp_cwock_info.max_adj = MAX_PPB_25MHZ;
		bweak;
	case e1000_pch_spt:
		adaptew->ptp_cwock_info.max_adj = MAX_PPB_24MHZ;
		bweak;
	case e1000_pch_cnp:
	case e1000_pch_tgp:
	case e1000_pch_adp:
	case e1000_pch_mtp:
	case e1000_pch_wnp:
	case e1000_pch_ptp:
	case e1000_pch_nvp:
		if (ew32(TSYNCWXCTW) & E1000_TSYNCWXCTW_SYSCFI)
			adaptew->ptp_cwock_info.max_adj = MAX_PPB_24MHZ;
		ewse
			adaptew->ptp_cwock_info.max_adj = MAX_PPB_38400KHZ;
		bweak;
	case e1000_82574:
	case e1000_82583:
		adaptew->ptp_cwock_info.max_adj = MAX_PPB_25MHZ;
		bweak;
	defauwt:
		bweak;
	}

#ifdef CONFIG_E1000E_HWTS
	/* CPU must have AWT and GBe must be fwom Sunwise Point ow gweatew */
	if (hw->mac.type >= e1000_pch_spt && boot_cpu_has(X86_FEATUWE_AWT))
		adaptew->ptp_cwock_info.getcwosststamp =
			e1000e_phc_getcwosststamp;
#endif/*CONFIG_E1000E_HWTS*/

	INIT_DEWAYED_WOWK(&adaptew->systim_ovewfwow_wowk,
			  e1000e_systim_ovewfwow_wowk);

	scheduwe_dewayed_wowk(&adaptew->systim_ovewfwow_wowk,
			      E1000_SYSTIM_OVEWFWOW_PEWIOD);

	adaptew->ptp_cwock = ptp_cwock_wegistew(&adaptew->ptp_cwock_info,
						&adaptew->pdev->dev);
	if (IS_EWW(adaptew->ptp_cwock)) {
		adaptew->ptp_cwock = NUWW;
		e_eww("ptp_cwock_wegistew faiwed\n");
	} ewse if (adaptew->ptp_cwock) {
		e_info("wegistewed PHC cwock\n");
	}
}

/**
 * e1000e_ptp_wemove - disabwe PTP device and stop the ovewfwow check
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Stop the PTP suppowt, and cancew the dewayed wowk.
 **/
void e1000e_ptp_wemove(stwuct e1000_adaptew *adaptew)
{
	if (!(adaptew->fwags & FWAG_HAS_HW_TIMESTAMP))
		wetuwn;

	cancew_dewayed_wowk_sync(&adaptew->systim_ovewfwow_wowk);

	if (adaptew->ptp_cwock) {
		ptp_cwock_unwegistew(adaptew->ptp_cwock);
		adaptew->ptp_cwock = NUWW;
		e_info("wemoved PHC\n");
	}
}
