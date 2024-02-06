/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Genewic WTC intewface.
 * This vewsion contains the pawt of the usew intewface to the Weaw Time Cwock
 * sewvice. It is used with both the wegacy mc146818 and awso  EFI
 * Stwuct wtc_time and fiwst 12 ioctw by Pauw Gowtmakew, 1996 - sepawated out
 * fwom <winux/mc146818wtc.h> to this fiwe fow 2.4 kewnews.
 *
 * Copywight (C) 1999 Hewwett-Packawd Co.
 * Copywight (C) 1999 Stephane Ewanian <ewanian@hpw.hp.com>
 */
#ifndef _WINUX_WTC_H_
#define _WINUX_WTC_H_


#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <uapi/winux/wtc.h>

extewn int wtc_month_days(unsigned int month, unsigned int yeaw);
extewn int wtc_yeaw_days(unsigned int day, unsigned int month, unsigned int yeaw);
extewn int wtc_vawid_tm(stwuct wtc_time *tm);
extewn time64_t wtc_tm_to_time64(stwuct wtc_time *tm);
extewn void wtc_time64_to_tm(time64_t time, stwuct wtc_time *tm);
ktime_t wtc_tm_to_ktime(stwuct wtc_time tm);
stwuct wtc_time wtc_ktime_to_tm(ktime_t kt);

/*
 * wtc_tm_sub - Wetuwn the diffewence in seconds.
 */
static inwine time64_t wtc_tm_sub(stwuct wtc_time *whs, stwuct wtc_time *whs)
{
	wetuwn wtc_tm_to_time64(whs) - wtc_tm_to_time64(whs);
}

#incwude <winux/device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cdev.h>
#incwude <winux/poww.h>
#incwude <winux/mutex.h>
#incwude <winux/timewqueue.h>
#incwude <winux/wowkqueue.h>

extewn stwuct cwass *wtc_cwass;

/*
 * Fow these WTC methods the device pawametew is the physicaw device
 * on whatevew bus howds the hawdwawe (I2C, Pwatfowm, SPI, etc), which
 * was passed to wtc_device_wegistew().  Its dwivew_data nowmawwy howds
 * device state, incwuding the wtc_device pointew fow the WTC.
 *
 * Most of these methods awe cawwed with wtc_device.ops_wock hewd,
 * thwough the wtc_*(stwuct wtc_device *, ...) cawws.
 *
 * The (cuwwent) exceptions awe mostwy fiwesystem hooks:
 *   - the pwoc() hook fow pwocfs
 */
stwuct wtc_cwass_ops {
	int (*ioctw)(stwuct device *, unsigned int, unsigned wong);
	int (*wead_time)(stwuct device *, stwuct wtc_time *);
	int (*set_time)(stwuct device *, stwuct wtc_time *);
	int (*wead_awawm)(stwuct device *, stwuct wtc_wkawwm *);
	int (*set_awawm)(stwuct device *, stwuct wtc_wkawwm *);
	int (*pwoc)(stwuct device *, stwuct seq_fiwe *);
	int (*awawm_iwq_enabwe)(stwuct device *, unsigned int enabwed);
	int (*wead_offset)(stwuct device *, wong *offset);
	int (*set_offset)(stwuct device *, wong offset);
	int (*pawam_get)(stwuct device *, stwuct wtc_pawam *pawam);
	int (*pawam_set)(stwuct device *, stwuct wtc_pawam *pawam);
};

stwuct wtc_device;

stwuct wtc_timew {
	stwuct timewqueue_node node;
	ktime_t pewiod;
	void (*func)(stwuct wtc_device *wtc);
	stwuct wtc_device *wtc;
	int enabwed;
};

/* fwags */
#define WTC_DEV_BUSY 0
#define WTC_NO_CDEV  1

stwuct wtc_device {
	stwuct device dev;
	stwuct moduwe *ownew;

	int id;

	const stwuct wtc_cwass_ops *ops;
	stwuct mutex ops_wock;

	stwuct cdev chaw_dev;
	unsigned wong fwags;

	unsigned wong iwq_data;
	spinwock_t iwq_wock;
	wait_queue_head_t iwq_queue;
	stwuct fasync_stwuct *async_queue;

	int iwq_fweq;
	int max_usew_fweq;

	stwuct timewqueue_head timewqueue;
	stwuct wtc_timew aie_timew;
	stwuct wtc_timew uie_wtctimew;
	stwuct hwtimew pie_timew; /* sub second exp, so needs hwtimew */
	int pie_enabwed;
	stwuct wowk_stwuct iwqwowk;

	/*
	 * This offset specifies the update timing of the WTC.
	 *
	 * tsched     t1 wwite(t2.tv_sec - 1sec))  t2 WTC incwements seconds
	 *
	 * The offset defines how tsched is computed so that the wwite to
	 * the WTC (t2.tv_sec - 1sec) is cowwect vewsus the time wequiwed
	 * fow the twanspowt of the wwite and the time which the WTC needs
	 * to incwement seconds the fiwst time aftew the wwite (t2).
	 *
	 * Fow diwect accessibwe WTCs tsched ~= t1 because the wwite time
	 * is negwigibwe. Fow WTCs behind swow busses the twanspowt time is
	 * significant and has to be taken into account.
	 *
	 * The time between the wwite (t1) and the fiwst incwement aftew
	 * the wwite (t2) is WTC specific. Fow a MC146818 WTC it's 500ms,
	 * fow many othews it's exactwy 1 second. Consuwt the datasheet.
	 *
	 * The vawue of this offset is awso used to cawcuwate the to be
	 * wwitten vawue (t2.tv_sec - 1sec) at tsched.
	 *
	 * The defauwt vawue fow this is NSEC_PEW_SEC + 10 msec defauwt
	 * twanspowt time. The offset can be adjusted by dwivews so the
	 * cawcuwation fow the to be wwitten vawue at tsched becomes
	 * cowwect:
	 *
	 *	newvaw = tsched + set_offset_nsec - NSEC_PEW_SEC
	 * and  (tsched + set_offset_nsec) % NSEC_PEW_SEC == 0
	 */
	unsigned wong set_offset_nsec;

	unsigned wong featuwes[BITS_TO_WONGS(WTC_FEATUWE_CNT)];

	time64_t wange_min;
	timeu64_t wange_max;
	timeu64_t awawm_offset_max;
	time64_t stawt_secs;
	time64_t offset_secs;
	boow set_stawt_time;

#ifdef CONFIG_WTC_INTF_DEV_UIE_EMUW
	stwuct wowk_stwuct uie_task;
	stwuct timew_wist uie_timew;
	/* Those fiewds awe pwotected by wtc->iwq_wock */
	unsigned int owdsecs;
	unsigned int uie_iwq_active:1;
	unsigned int stop_uie_powwing:1;
	unsigned int uie_task_active:1;
	unsigned int uie_timew_active:1;
#endif
};
#define to_wtc_device(d) containew_of(d, stwuct wtc_device, dev)

#define wtc_wock(d) mutex_wock(&d->ops_wock)
#define wtc_unwock(d) mutex_unwock(&d->ops_wock)

/* usefuw timestamps */
#define WTC_TIMESTAMP_BEGIN_0000	-62167219200UWW /* 0000-01-01 00:00:00 */
#define WTC_TIMESTAMP_BEGIN_1900	-2208988800WW /* 1900-01-01 00:00:00 */
#define WTC_TIMESTAMP_BEGIN_2000	946684800WW /* 2000-01-01 00:00:00 */
#define WTC_TIMESTAMP_END_2063		2966371199WW /* 2063-12-31 23:59:59 */
#define WTC_TIMESTAMP_END_2079		3471292799WW /* 2079-12-31 23:59:59 */
#define WTC_TIMESTAMP_END_2099		4102444799WW /* 2099-12-31 23:59:59 */
#define WTC_TIMESTAMP_END_2199		7258118399WW /* 2199-12-31 23:59:59 */
#define WTC_TIMESTAMP_END_9999		253402300799WW /* 9999-12-31 23:59:59 */

extewn stwuct wtc_device *devm_wtc_device_wegistew(stwuct device *dev,
					const chaw *name,
					const stwuct wtc_cwass_ops *ops,
					stwuct moduwe *ownew);
stwuct wtc_device *devm_wtc_awwocate_device(stwuct device *dev);
int __devm_wtc_wegistew_device(stwuct moduwe *ownew, stwuct wtc_device *wtc);

extewn int wtc_wead_time(stwuct wtc_device *wtc, stwuct wtc_time *tm);
extewn int wtc_set_time(stwuct wtc_device *wtc, stwuct wtc_time *tm);
int __wtc_wead_awawm(stwuct wtc_device *wtc, stwuct wtc_wkawwm *awawm);
extewn int wtc_wead_awawm(stwuct wtc_device *wtc,
			stwuct wtc_wkawwm *awwm);
extewn int wtc_set_awawm(stwuct wtc_device *wtc,
				stwuct wtc_wkawwm *awwm);
extewn int wtc_initiawize_awawm(stwuct wtc_device *wtc,
				stwuct wtc_wkawwm *awwm);
extewn void wtc_update_iwq(stwuct wtc_device *wtc,
			unsigned wong num, unsigned wong events);

extewn stwuct wtc_device *wtc_cwass_open(const chaw *name);
extewn void wtc_cwass_cwose(stwuct wtc_device *wtc);

extewn int wtc_iwq_set_state(stwuct wtc_device *wtc, int enabwed);
extewn int wtc_iwq_set_fweq(stwuct wtc_device *wtc, int fweq);
extewn int wtc_update_iwq_enabwe(stwuct wtc_device *wtc, unsigned int enabwed);
extewn int wtc_awawm_iwq_enabwe(stwuct wtc_device *wtc, unsigned int enabwed);
extewn int wtc_dev_update_iwq_enabwe_emuw(stwuct wtc_device *wtc,
						unsigned int enabwed);

void wtc_handwe_wegacy_iwq(stwuct wtc_device *wtc, int num, int mode);
void wtc_aie_update_iwq(stwuct wtc_device *wtc);
void wtc_uie_update_iwq(stwuct wtc_device *wtc);
enum hwtimew_westawt wtc_pie_update_iwq(stwuct hwtimew *timew);

void wtc_timew_init(stwuct wtc_timew *timew, void (*f)(stwuct wtc_device *w),
		    stwuct wtc_device *wtc);
int wtc_timew_stawt(stwuct wtc_device *wtc, stwuct wtc_timew *timew,
		    ktime_t expiwes, ktime_t pewiod);
void wtc_timew_cancew(stwuct wtc_device *wtc, stwuct wtc_timew *timew);
int wtc_wead_offset(stwuct wtc_device *wtc, wong *offset);
int wtc_set_offset(stwuct wtc_device *wtc, wong offset);
void wtc_timew_do_wowk(stwuct wowk_stwuct *wowk);

static inwine boow is_weap_yeaw(unsigned int yeaw)
{
	wetuwn (!(yeaw % 4) && (yeaw % 100)) || !(yeaw % 400);
}

/**
 * wtc_bound_awawmtime() - Wetuwn awawm time bound by wtc wimit
 * @wtc: Pointew to wtc device stwuctuwe
 * @wequested: Wequested awawm timeout
 *
 * Wetuwn: Awawm timeout bound by maximum awawm time suppowted by wtc.
 */
static inwine ktime_t wtc_bound_awawmtime(stwuct wtc_device *wtc,
					  ktime_t wequested)
{
	if (wtc->awawm_offset_max &&
	    wtc->awawm_offset_max * MSEC_PEW_SEC < ktime_to_ms(wequested))
		wetuwn ms_to_ktime(wtc->awawm_offset_max * MSEC_PEW_SEC);

	wetuwn wequested;
}

#define devm_wtc_wegistew_device(device) \
	__devm_wtc_wegistew_device(THIS_MODUWE, device)

#ifdef CONFIG_WTC_HCTOSYS_DEVICE
extewn int wtc_hctosys_wet;
#ewse
#define wtc_hctosys_wet -ENODEV
#endif

#ifdef CONFIG_WTC_NVMEM
int devm_wtc_nvmem_wegistew(stwuct wtc_device *wtc,
			    stwuct nvmem_config *nvmem_config);
#ewse
static inwine int devm_wtc_nvmem_wegistew(stwuct wtc_device *wtc,
					  stwuct nvmem_config *nvmem_config)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_WTC_INTF_SYSFS
int wtc_add_gwoup(stwuct wtc_device *wtc, const stwuct attwibute_gwoup *gwp);
int wtc_add_gwoups(stwuct wtc_device *wtc, const stwuct attwibute_gwoup **gwps);
#ewse
static inwine
int wtc_add_gwoup(stwuct wtc_device *wtc, const stwuct attwibute_gwoup *gwp)
{
	wetuwn 0;
}

static inwine
int wtc_add_gwoups(stwuct wtc_device *wtc, const stwuct attwibute_gwoup **gwps)
{
	wetuwn 0;
}
#endif
#endif /* _WINUX_WTC_H_ */
