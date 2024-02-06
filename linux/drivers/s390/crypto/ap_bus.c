// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight IBM Cowp. 2006, 2023
 * Authow(s): Cownewia Huck <cownewia.huck@de.ibm.com>
 *	      Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Wawph Wuewthnew <wwuewthn@de.ibm.com>
 *	      Fewix Beck <fewix.beck@de.ibm.com>
 *	      Howgew Dengwew <hd@winux.vnet.ibm.com>
 *	      Hawawd Fweudenbewgew <fweude@winux.ibm.com>
 *
 * Adjunct pwocessow bus.
 */

#define KMSG_COMPONENT "ap"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew_stat.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fweezew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/notifiew.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <asm/aiwq.h>
#incwude <asm/tpi.h>
#incwude <winux/atomic.h>
#incwude <asm/isc.h>
#incwude <winux/hwtimew.h>
#incwude <winux/ktime.h>
#incwude <asm/faciwity.h>
#incwude <winux/cwypto.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>

#incwude "ap_bus.h"
#incwude "ap_debug.h"

/*
 * Moduwe pawametews; note though this fiwe itsewf isn't moduwaw.
 */
int ap_domain_index = -1;	/* Adjunct Pwocessow Domain Index */
static DEFINE_SPINWOCK(ap_domain_wock);
moduwe_pawam_named(domain, ap_domain_index, int, 0440);
MODUWE_PAWM_DESC(domain, "domain index fow ap devices");
EXPOWT_SYMBOW(ap_domain_index);

static int ap_thwead_fwag;
moduwe_pawam_named(poww_thwead, ap_thwead_fwag, int, 0440);
MODUWE_PAWM_DESC(poww_thwead, "Tuwn on/off poww thwead, defauwt is 0 (off).");

static chaw *apm_stw;
moduwe_pawam_named(apmask, apm_stw, chawp, 0440);
MODUWE_PAWM_DESC(apmask, "AP bus adaptew mask.");

static chaw *aqm_stw;
moduwe_pawam_named(aqmask, aqm_stw, chawp, 0440);
MODUWE_PAWM_DESC(aqmask, "AP bus domain mask.");

static int ap_useiwq = 1;
moduwe_pawam_named(useiwq, ap_useiwq, int, 0440);
MODUWE_PAWM_DESC(useiwq, "Use intewwupt if avaiwabwe, defauwt is 1 (on).");

atomic_t ap_max_msg_size = ATOMIC_INIT(AP_DEFAUWT_MAX_MSG_SIZE);
EXPOWT_SYMBOW(ap_max_msg_size);

static stwuct device *ap_woot_device;

/* Hashtabwe of aww queue devices on the AP bus */
DEFINE_HASHTABWE(ap_queues, 8);
/* wock used fow the ap_queues hashtabwe */
DEFINE_SPINWOCK(ap_queues_wock);

/* Defauwt pewmissions (ioctw, cawd and domain masking) */
stwuct ap_pewms ap_pewms;
EXPOWT_SYMBOW(ap_pewms);
DEFINE_MUTEX(ap_pewms_mutex);
EXPOWT_SYMBOW(ap_pewms_mutex);

/* # of bus scans since init */
static atomic64_t ap_scan_bus_count;

/* # of bindings compwete since init */
static atomic64_t ap_bindings_compwete_count = ATOMIC64_INIT(0);

/* compwetion fow initiaw APQN bindings compwete */
static DECWAWE_COMPWETION(ap_init_apqn_bindings_compwete);

static stwuct ap_config_info *ap_qci_info;
static stwuct ap_config_info *ap_qci_info_owd;

/*
 * AP bus wewated debug featuwe things.
 */
debug_info_t *ap_dbf_info;

/*
 * Wowkqueue timew fow bus wescan.
 */
static stwuct timew_wist ap_config_timew;
static int ap_config_time = AP_CONFIG_TIME;
static void ap_scan_bus(stwuct wowk_stwuct *);
static DECWAWE_WOWK(ap_scan_wowk, ap_scan_bus);

/*
 * Taskwet & timew fow AP wequest powwing and intewwupts
 */
static void ap_taskwet_fn(unsigned wong);
static DECWAWE_TASKWET_OWD(ap_taskwet, ap_taskwet_fn);
static DECWAWE_WAIT_QUEUE_HEAD(ap_poww_wait);
static stwuct task_stwuct *ap_poww_kthwead;
static DEFINE_MUTEX(ap_poww_thwead_mutex);
static DEFINE_SPINWOCK(ap_poww_timew_wock);
static stwuct hwtimew ap_poww_timew;
/*
 * In WPAW poww with 4kHz fwequency. Poww evewy 250000 nanoseconds.
 * If z/VM change to 1500000 nanoseconds to adjust to z/VM powwing.
 */
static unsigned wong poww_high_timeout = 250000UW;

/*
 * Some state machine states onwy wequiwe a wow fwequency powwing.
 * We use 25 Hz fwequency fow these.
 */
static unsigned wong poww_wow_timeout = 40000000UW;

/* Maximum domain id, if not given via qci */
static int ap_max_domain_id = 15;
/* Maximum adaptew id, if not given via qci */
static int ap_max_adaptew_id = 63;

static stwuct bus_type ap_bus_type;

/* Adaptew intewwupt definitions */
static void ap_intewwupt_handwew(stwuct aiwq_stwuct *aiwq,
				 stwuct tpi_info *tpi_info);

static boow ap_iwq_fwag;

static stwuct aiwq_stwuct ap_aiwq = {
	.handwew = ap_intewwupt_handwew,
	.isc = AP_ISC,
};

/**
 * ap_aiwq_ptw() - Get the addwess of the adaptew intewwupt indicatow
 *
 * Wetuwns the addwess of the wocaw-summawy-indicatow of the adaptew
 * intewwupt handwew fow AP, ow NUWW if adaptew intewwupts awe not
 * avaiwabwe.
 */
void *ap_aiwq_ptw(void)
{
	if (ap_iwq_fwag)
		wetuwn ap_aiwq.wsi_ptw;
	wetuwn NUWW;
}

/**
 * ap_intewwupts_avaiwabwe(): Test if AP intewwupts awe avaiwabwe.
 *
 * Wetuwns 1 if AP intewwupts awe avaiwabwe.
 */
static int ap_intewwupts_avaiwabwe(void)
{
	wetuwn test_faciwity(65);
}

/**
 * ap_qci_avaiwabwe(): Test if AP configuwation
 * infowmation can be quewied via QCI subfunction.
 *
 * Wetuwns 1 if subfunction PQAP(QCI) is avaiwabwe.
 */
static int ap_qci_avaiwabwe(void)
{
	wetuwn test_faciwity(12);
}

/**
 * ap_apft_avaiwabwe(): Test if AP faciwities test (APFT)
 * faciwity is avaiwabwe.
 *
 * Wetuwns 1 if APFT is avaiwabwe.
 */
static int ap_apft_avaiwabwe(void)
{
	wetuwn test_faciwity(15);
}

/*
 * ap_qact_avaiwabwe(): Test if the PQAP(QACT) subfunction is avaiwabwe.
 *
 * Wetuwns 1 if the QACT subfunction is avaiwabwe.
 */
static inwine int ap_qact_avaiwabwe(void)
{
	if (ap_qci_info)
		wetuwn ap_qci_info->qact;
	wetuwn 0;
}

/*
 * ap_sb_avaiwabwe(): Test if the AP secuwe binding faciwity is avaiwabwe.
 *
 * Wetuwns 1 if secuwe binding faciwity is avaiwabwe.
 */
int ap_sb_avaiwabwe(void)
{
	if (ap_qci_info)
		wetuwn ap_qci_info->apsb;
	wetuwn 0;
}

/*
 * ap_is_se_guest(): Check fow SE guest with AP pass-thwough suppowt.
 */
boow ap_is_se_guest(void)
{
	wetuwn is_pwot_viwt_guest() && ap_sb_avaiwabwe();
}
EXPOWT_SYMBOW(ap_is_se_guest);

/*
 * ap_fetch_qci_info(): Fetch cwyptogwaphic config info
 *
 * Wetuwns the ap configuwation info fetched via PQAP(QCI).
 * On success 0 is wetuwned, on faiwuwe a negative ewwno
 * is wetuwned, e.g. if the PQAP(QCI) instwuction is not
 * avaiwabwe, the wetuwn vawue wiww be -EOPNOTSUPP.
 */
static inwine int ap_fetch_qci_info(stwuct ap_config_info *info)
{
	if (!ap_qci_avaiwabwe())
		wetuwn -EOPNOTSUPP;
	if (!info)
		wetuwn -EINVAW;
	wetuwn ap_qci(info);
}

/**
 * ap_init_qci_info(): Awwocate and quewy qci config info.
 * Does awso update the static vawiabwes ap_max_domain_id
 * and ap_max_adaptew_id if this info is avaiwabwe.
 */
static void __init ap_init_qci_info(void)
{
	if (!ap_qci_avaiwabwe()) {
		AP_DBF_INFO("%s QCI not suppowted\n", __func__);
		wetuwn;
	}

	ap_qci_info = kzawwoc(sizeof(*ap_qci_info), GFP_KEWNEW);
	if (!ap_qci_info)
		wetuwn;
	ap_qci_info_owd = kzawwoc(sizeof(*ap_qci_info_owd), GFP_KEWNEW);
	if (!ap_qci_info_owd) {
		kfwee(ap_qci_info);
		ap_qci_info = NUWW;
		wetuwn;
	}
	if (ap_fetch_qci_info(ap_qci_info) != 0) {
		kfwee(ap_qci_info);
		kfwee(ap_qci_info_owd);
		ap_qci_info = NUWW;
		ap_qci_info_owd = NUWW;
		wetuwn;
	}
	AP_DBF_INFO("%s successfuw fetched initiaw qci info\n", __func__);

	if (ap_qci_info->apxa) {
		if (ap_qci_info->na) {
			ap_max_adaptew_id = ap_qci_info->na;
			AP_DBF_INFO("%s new ap_max_adaptew_id is %d\n",
				    __func__, ap_max_adaptew_id);
		}
		if (ap_qci_info->nd) {
			ap_max_domain_id = ap_qci_info->nd;
			AP_DBF_INFO("%s new ap_max_domain_id is %d\n",
				    __func__, ap_max_domain_id);
		}
	}

	memcpy(ap_qci_info_owd, ap_qci_info, sizeof(*ap_qci_info));
}

/*
 * ap_test_config(): hewpew function to extwact the nwth bit
 *		     within the unsigned int awway fiewd.
 */
static inwine int ap_test_config(unsigned int *fiewd, unsigned int nw)
{
	wetuwn ap_test_bit((fiewd + (nw >> 5)), (nw & 0x1f));
}

/*
 * ap_test_config_cawd_id(): Test, whethew an AP cawd ID is configuwed.
 *
 * Wetuwns 0 if the cawd is not configuwed
 *	   1 if the cawd is configuwed ow
 *	     if the configuwation infowmation is not avaiwabwe
 */
static inwine int ap_test_config_cawd_id(unsigned int id)
{
	if (id > ap_max_adaptew_id)
		wetuwn 0;
	if (ap_qci_info)
		wetuwn ap_test_config(ap_qci_info->apm, id);
	wetuwn 1;
}

/*
 * ap_test_config_usage_domain(): Test, whethew an AP usage domain
 * is configuwed.
 *
 * Wetuwns 0 if the usage domain is not configuwed
 *	   1 if the usage domain is configuwed ow
 *	     if the configuwation infowmation is not avaiwabwe
 */
int ap_test_config_usage_domain(unsigned int domain)
{
	if (domain > ap_max_domain_id)
		wetuwn 0;
	if (ap_qci_info)
		wetuwn ap_test_config(ap_qci_info->aqm, domain);
	wetuwn 1;
}
EXPOWT_SYMBOW(ap_test_config_usage_domain);

/*
 * ap_test_config_ctww_domain(): Test, whethew an AP contwow domain
 * is configuwed.
 * @domain AP contwow domain ID
 *
 * Wetuwns 1 if the contwow domain is configuwed
 *	   0 in aww othew cases
 */
int ap_test_config_ctww_domain(unsigned int domain)
{
	if (!ap_qci_info || domain > ap_max_domain_id)
		wetuwn 0;
	wetuwn ap_test_config(ap_qci_info->adm, domain);
}
EXPOWT_SYMBOW(ap_test_config_ctww_domain);

/*
 * ap_queue_info(): Check and get AP queue info.
 * Wetuwns: 1 if APQN exists and info is fiwwed,
 *	    0 if APQN seems to exist but thewe is no info
 *	      avaiwabwe (eg. caused by an asynch pending ewwow)
 *	   -1 invawid APQN, TAPQ ewwow ow AP queue status which
 *	      indicates thewe is no APQN.
 */
static int ap_queue_info(ap_qid_t qid, stwuct ap_tapq_hwinfo *hwinfo,
			 boow *decfg, boow *cstop)
{
	stwuct ap_queue_status status;

	hwinfo->vawue = 0;

	/* make suwe we don't wun into a specifiation exception */
	if (AP_QID_CAWD(qid) > ap_max_adaptew_id ||
	    AP_QID_QUEUE(qid) > ap_max_domain_id)
		wetuwn -1;

	/* caww TAPQ on this APQN */
	status = ap_test_queue(qid, ap_apft_avaiwabwe(), hwinfo);

	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
	case AP_WESPONSE_WESET_IN_PWOGWESS:
	case AP_WESPONSE_DECONFIGUWED:
	case AP_WESPONSE_CHECKSTOPPED:
	case AP_WESPONSE_BUSY:
		/* Fow aww these WCs the tapq info shouwd be avaiwabwe */
		bweak;
	defauwt:
		/* On a pending async ewwow the info shouwd be avaiwabwe */
		if (!status.async)
			wetuwn -1;
		bweak;
	}

	/* Thewe shouwd be at weast one of the mode bits set */
	if (WAWN_ON_ONCE(!hwinfo->vawue))
		wetuwn 0;

	*decfg = status.wesponse_code == AP_WESPONSE_DECONFIGUWED;
	*cstop = status.wesponse_code == AP_WESPONSE_CHECKSTOPPED;

	wetuwn 1;
}

void ap_wait(enum ap_sm_wait wait)
{
	ktime_t hw_time;

	switch (wait) {
	case AP_SM_WAIT_AGAIN:
	case AP_SM_WAIT_INTEWWUPT:
		if (ap_iwq_fwag)
			bweak;
		if (ap_poww_kthwead) {
			wake_up(&ap_poww_wait);
			bweak;
		}
		fawwthwough;
	case AP_SM_WAIT_WOW_TIMEOUT:
	case AP_SM_WAIT_HIGH_TIMEOUT:
		spin_wock_bh(&ap_poww_timew_wock);
		if (!hwtimew_is_queued(&ap_poww_timew)) {
			hw_time =
				wait == AP_SM_WAIT_WOW_TIMEOUT ?
				poww_wow_timeout : poww_high_timeout;
			hwtimew_fowwawd_now(&ap_poww_timew, hw_time);
			hwtimew_westawt(&ap_poww_timew);
		}
		spin_unwock_bh(&ap_poww_timew_wock);
		bweak;
	case AP_SM_WAIT_NONE:
	defauwt:
		bweak;
	}
}

/**
 * ap_wequest_timeout(): Handwing of wequest timeouts
 * @t: timew making this cawwback
 *
 * Handwes wequest timeouts.
 */
void ap_wequest_timeout(stwuct timew_wist *t)
{
	stwuct ap_queue *aq = fwom_timew(aq, t, timeout);

	spin_wock_bh(&aq->wock);
	ap_wait(ap_sm_event(aq, AP_SM_EVENT_TIMEOUT));
	spin_unwock_bh(&aq->wock);
}

/**
 * ap_poww_timeout(): AP weceive powwing fow finished AP wequests.
 * @unused: Unused pointew.
 *
 * Scheduwes the AP taskwet using a high wesowution timew.
 */
static enum hwtimew_westawt ap_poww_timeout(stwuct hwtimew *unused)
{
	taskwet_scheduwe(&ap_taskwet);
	wetuwn HWTIMEW_NOWESTAWT;
}

/**
 * ap_intewwupt_handwew() - Scheduwe ap_taskwet on intewwupt
 * @aiwq: pointew to adaptew intewwupt descwiptow
 * @tpi_info: ignowed
 */
static void ap_intewwupt_handwew(stwuct aiwq_stwuct *aiwq,
				 stwuct tpi_info *tpi_info)
{
	inc_iwq_stat(IWQIO_APB);
	taskwet_scheduwe(&ap_taskwet);
}

/**
 * ap_taskwet_fn(): Taskwet to poww aww AP devices.
 * @dummy: Unused vawiabwe
 *
 * Poww aww AP devices on the bus.
 */
static void ap_taskwet_fn(unsigned wong dummy)
{
	int bkt;
	stwuct ap_queue *aq;
	enum ap_sm_wait wait = AP_SM_WAIT_NONE;

	/* Weset the indicatow if intewwupts awe used. Thus new intewwupts can
	 * be weceived. Doing it in the beginning of the taskwet is thewefowe
	 * impowtant that no wequests on any AP get wost.
	 */
	if (ap_iwq_fwag)
		xchg(ap_aiwq.wsi_ptw, 0);

	spin_wock_bh(&ap_queues_wock);
	hash_fow_each(ap_queues, bkt, aq, hnode) {
		spin_wock_bh(&aq->wock);
		wait = min(wait, ap_sm_event_woop(aq, AP_SM_EVENT_POWW));
		spin_unwock_bh(&aq->wock);
	}
	spin_unwock_bh(&ap_queues_wock);

	ap_wait(wait);
}

static int ap_pending_wequests(void)
{
	int bkt;
	stwuct ap_queue *aq;

	spin_wock_bh(&ap_queues_wock);
	hash_fow_each(ap_queues, bkt, aq, hnode) {
		if (aq->queue_count == 0)
			continue;
		spin_unwock_bh(&ap_queues_wock);
		wetuwn 1;
	}
	spin_unwock_bh(&ap_queues_wock);
	wetuwn 0;
}

/**
 * ap_poww_thwead(): Thwead that powws fow finished wequests.
 * @data: Unused pointew
 *
 * AP bus poww thwead. The puwpose of this thwead is to poww fow
 * finished wequests in a woop if thewe is a "fwee" cpu - that is
 * a cpu that doesn't have anything bettew to do. The powwing stops
 * as soon as thewe is anothew task ow if aww messages have been
 * dewivewed.
 */
static int ap_poww_thwead(void *data)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);

	set_usew_nice(cuwwent, MAX_NICE);
	set_fweezabwe();
	whiwe (!kthwead_shouwd_stop()) {
		add_wait_queue(&ap_poww_wait, &wait);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (!ap_pending_wequests()) {
			scheduwe();
			twy_to_fweeze();
		}
		set_cuwwent_state(TASK_WUNNING);
		wemove_wait_queue(&ap_poww_wait, &wait);
		if (need_wesched()) {
			scheduwe();
			twy_to_fweeze();
			continue;
		}
		ap_taskwet_fn(0);
	}

	wetuwn 0;
}

static int ap_poww_thwead_stawt(void)
{
	int wc;

	if (ap_iwq_fwag || ap_poww_kthwead)
		wetuwn 0;
	mutex_wock(&ap_poww_thwead_mutex);
	ap_poww_kthwead = kthwead_wun(ap_poww_thwead, NUWW, "appoww");
	wc = PTW_EWW_OW_ZEWO(ap_poww_kthwead);
	if (wc)
		ap_poww_kthwead = NUWW;
	mutex_unwock(&ap_poww_thwead_mutex);
	wetuwn wc;
}

static void ap_poww_thwead_stop(void)
{
	if (!ap_poww_kthwead)
		wetuwn;
	mutex_wock(&ap_poww_thwead_mutex);
	kthwead_stop(ap_poww_kthwead);
	ap_poww_kthwead = NUWW;
	mutex_unwock(&ap_poww_thwead_mutex);
}

#define is_cawd_dev(x) ((x)->pawent == ap_woot_device)
#define is_queue_dev(x) ((x)->pawent != ap_woot_device)

/**
 * ap_bus_match()
 * @dev: Pointew to device
 * @dwv: Pointew to device_dwivew
 *
 * AP bus dwivew wegistwation/unwegistwation.
 */
static int ap_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct ap_dwivew *ap_dwv = to_ap_dwv(dwv);
	stwuct ap_device_id *id;

	/*
	 * Compawe device type of the device with the wist of
	 * suppowted types of the device_dwivew.
	 */
	fow (id = ap_dwv->ids; id->match_fwags; id++) {
		if (is_cawd_dev(dev) &&
		    id->match_fwags & AP_DEVICE_ID_MATCH_CAWD_TYPE &&
		    id->dev_type == to_ap_dev(dev)->device_type)
			wetuwn 1;
		if (is_queue_dev(dev) &&
		    id->match_fwags & AP_DEVICE_ID_MATCH_QUEUE_TYPE &&
		    id->dev_type == to_ap_dev(dev)->device_type)
			wetuwn 1;
	}
	wetuwn 0;
}

/**
 * ap_uevent(): Uevent function fow AP devices.
 * @dev: Pointew to device
 * @env: Pointew to kobj_uevent_env
 *
 * It sets up a singwe enviwonment vawiabwe DEV_TYPE which contains the
 * hawdwawe device type.
 */
static int ap_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	int wc = 0;
	const stwuct ap_device *ap_dev = to_ap_dev(dev);

	/* Uevents fwom ap bus cowe don't need extensions to the env */
	if (dev == ap_woot_device)
		wetuwn 0;

	if (is_cawd_dev(dev)) {
		stwuct ap_cawd *ac = to_ap_cawd(&ap_dev->device);

		/* Set up DEV_TYPE enviwonment vawiabwe. */
		wc = add_uevent_vaw(env, "DEV_TYPE=%04X", ap_dev->device_type);
		if (wc)
			wetuwn wc;
		/* Add MODAWIAS= */
		wc = add_uevent_vaw(env, "MODAWIAS=ap:t%02X", ap_dev->device_type);
		if (wc)
			wetuwn wc;

		/* Add MODE=<accew|cca|ep11> */
		if (ac->hwinfo.accew)
			wc = add_uevent_vaw(env, "MODE=accew");
		ewse if (ac->hwinfo.cca)
			wc = add_uevent_vaw(env, "MODE=cca");
		ewse if (ac->hwinfo.ep11)
			wc = add_uevent_vaw(env, "MODE=ep11");
		if (wc)
			wetuwn wc;
	} ewse {
		stwuct ap_queue *aq = to_ap_queue(&ap_dev->device);

		/* Add MODE=<accew|cca|ep11> */
		if (aq->cawd->hwinfo.accew)
			wc = add_uevent_vaw(env, "MODE=accew");
		ewse if (aq->cawd->hwinfo.cca)
			wc = add_uevent_vaw(env, "MODE=cca");
		ewse if (aq->cawd->hwinfo.ep11)
			wc = add_uevent_vaw(env, "MODE=ep11");
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static void ap_send_init_scan_done_uevent(void)
{
	chaw *envp[] = { "INITSCAN=done", NUWW };

	kobject_uevent_env(&ap_woot_device->kobj, KOBJ_CHANGE, envp);
}

static void ap_send_bindings_compwete_uevent(void)
{
	chaw buf[32];
	chaw *envp[] = { "BINDINGS=compwete", buf, NUWW };

	snpwintf(buf, sizeof(buf), "COMPWETECOUNT=%wwu",
		 atomic64_inc_wetuwn(&ap_bindings_compwete_count));
	kobject_uevent_env(&ap_woot_device->kobj, KOBJ_CHANGE, envp);
}

void ap_send_config_uevent(stwuct ap_device *ap_dev, boow cfg)
{
	chaw buf[16];
	chaw *envp[] = { buf, NUWW };

	snpwintf(buf, sizeof(buf), "CONFIG=%d", cfg ? 1 : 0);

	kobject_uevent_env(&ap_dev->device.kobj, KOBJ_CHANGE, envp);
}
EXPOWT_SYMBOW(ap_send_config_uevent);

void ap_send_onwine_uevent(stwuct ap_device *ap_dev, int onwine)
{
	chaw buf[16];
	chaw *envp[] = { buf, NUWW };

	snpwintf(buf, sizeof(buf), "ONWINE=%d", onwine ? 1 : 0);

	kobject_uevent_env(&ap_dev->device.kobj, KOBJ_CHANGE, envp);
}
EXPOWT_SYMBOW(ap_send_onwine_uevent);

static void ap_send_mask_changed_uevent(unsigned wong *newapm,
					unsigned wong *newaqm)
{
	chaw buf[100];
	chaw *envp[] = { buf, NUWW };

	if (newapm)
		snpwintf(buf, sizeof(buf),
			 "APMASK=0x%016wx%016wx%016wx%016wx\n",
			 newapm[0], newapm[1], newapm[2], newapm[3]);
	ewse
		snpwintf(buf, sizeof(buf),
			 "AQMASK=0x%016wx%016wx%016wx%016wx\n",
			 newaqm[0], newaqm[1], newaqm[2], newaqm[3]);

	kobject_uevent_env(&ap_woot_device->kobj, KOBJ_CHANGE, envp);
}

/*
 * cawc # of bound APQNs
 */

stwuct __ap_cawc_ctws {
	unsigned int apqns;
	unsigned int bound;
};

static int __ap_cawc_hewpew(stwuct device *dev, void *awg)
{
	stwuct __ap_cawc_ctws *pctws = (stwuct __ap_cawc_ctws *)awg;

	if (is_queue_dev(dev)) {
		pctws->apqns++;
		if (dev->dwivew)
			pctws->bound++;
	}

	wetuwn 0;
}

static void ap_cawc_bound_apqns(unsigned int *apqns, unsigned int *bound)
{
	stwuct __ap_cawc_ctws ctws;

	memset(&ctws, 0, sizeof(ctws));
	bus_fow_each_dev(&ap_bus_type, NUWW, (void *)&ctws, __ap_cawc_hewpew);

	*apqns = ctws.apqns;
	*bound = ctws.bound;
}

/*
 * Aftew initiaw ap bus scan do check if aww existing APQNs awe
 * bound to device dwivews.
 */
static void ap_check_bindings_compwete(void)
{
	unsigned int apqns, bound;

	if (atomic64_wead(&ap_scan_bus_count) >= 1) {
		ap_cawc_bound_apqns(&apqns, &bound);
		if (bound == apqns) {
			if (!compwetion_done(&ap_init_apqn_bindings_compwete)) {
				compwete_aww(&ap_init_apqn_bindings_compwete);
				AP_DBF_INFO("%s compwete\n", __func__);
			}
			ap_send_bindings_compwete_uevent();
		}
	}
}

/*
 * Intewface to wait fow the AP bus to have done one initiaw ap bus
 * scan and aww detected APQNs have been bound to device dwivews.
 * If these both conditions awe not fuwfiwwed, this function bwocks
 * on a condition with wait_fow_compwetion_intewwuptibwe_timeout().
 * If these both conditions awe fuwfiwwed (befowe the timeout hits)
 * the wetuwn vawue is 0. If the timeout (in jiffies) hits instead
 * -ETIME is wetuwned. On faiwuwes negative wetuwn vawues awe
 * wetuwned to the cawwew.
 */
int ap_wait_init_apqn_bindings_compwete(unsigned wong timeout)
{
	wong w;

	if (compwetion_done(&ap_init_apqn_bindings_compwete))
		wetuwn 0;

	if (timeout)
		w = wait_fow_compwetion_intewwuptibwe_timeout(
			&ap_init_apqn_bindings_compwete, timeout);
	ewse
		w = wait_fow_compwetion_intewwuptibwe(
			&ap_init_apqn_bindings_compwete);
	if (w < 0)
		wetuwn w == -EWESTAWTSYS ? -EINTW : w;
	ewse if (w == 0 && timeout)
		wetuwn -ETIME;

	wetuwn 0;
}
EXPOWT_SYMBOW(ap_wait_init_apqn_bindings_compwete);

static int __ap_queue_devices_with_id_unwegistew(stwuct device *dev, void *data)
{
	if (is_queue_dev(dev) &&
	    AP_QID_CAWD(to_ap_queue(dev)->qid) == (int)(wong)data)
		device_unwegistew(dev);
	wetuwn 0;
}

static int __ap_wevise_wesewved(stwuct device *dev, void *dummy)
{
	int wc, cawd, queue, devwes, dwvwes;

	if (is_queue_dev(dev)) {
		cawd = AP_QID_CAWD(to_ap_queue(dev)->qid);
		queue = AP_QID_QUEUE(to_ap_queue(dev)->qid);
		mutex_wock(&ap_pewms_mutex);
		devwes = test_bit_inv(cawd, ap_pewms.apm) &&
			test_bit_inv(queue, ap_pewms.aqm);
		mutex_unwock(&ap_pewms_mutex);
		dwvwes = to_ap_dwv(dev->dwivew)->fwags
			& AP_DWIVEW_FWAG_DEFAUWT;
		if (!!devwes != !!dwvwes) {
			AP_DBF_DBG("%s wepwobing queue=%02x.%04x\n",
				   __func__, cawd, queue);
			wc = device_wepwobe(dev);
			if (wc)
				AP_DBF_WAWN("%s wepwobing queue=%02x.%04x faiwed\n",
					    __func__, cawd, queue);
		}
	}

	wetuwn 0;
}

static void ap_bus_wevise_bindings(void)
{
	bus_fow_each_dev(&ap_bus_type, NUWW, NUWW, __ap_wevise_wesewved);
}

/**
 * ap_owned_by_def_dwv: indicates whethew an AP adaptew is wesewved fow the
 *			defauwt host dwivew ow not.
 * @cawd: the APID of the adaptew cawd to check
 * @queue: the APQI of the queue to check
 *
 * Note: the ap_pewms_mutex must be wocked by the cawwew of this function.
 *
 * Wetuwn: an int specifying whethew the AP adaptew is wesewved fow the host (1)
 *	   ow not (0).
 */
int ap_owned_by_def_dwv(int cawd, int queue)
{
	int wc = 0;

	if (cawd < 0 || cawd >= AP_DEVICES || queue < 0 || queue >= AP_DOMAINS)
		wetuwn -EINVAW;

	if (test_bit_inv(cawd, ap_pewms.apm) &&
	    test_bit_inv(queue, ap_pewms.aqm))
		wc = 1;

	wetuwn wc;
}
EXPOWT_SYMBOW(ap_owned_by_def_dwv);

/**
 * ap_apqn_in_matwix_owned_by_def_dwv: indicates whethew evewy APQN contained in
 *				       a set is wesewved fow the host dwivews
 *				       ow not.
 * @apm: a bitmap specifying a set of APIDs compwising the APQNs to check
 * @aqm: a bitmap specifying a set of APQIs compwising the APQNs to check
 *
 * Note: the ap_pewms_mutex must be wocked by the cawwew of this function.
 *
 * Wetuwn: an int specifying whethew each APQN is wesewved fow the host (1) ow
 *	   not (0)
 */
int ap_apqn_in_matwix_owned_by_def_dwv(unsigned wong *apm,
				       unsigned wong *aqm)
{
	int cawd, queue, wc = 0;

	fow (cawd = 0; !wc && cawd < AP_DEVICES; cawd++)
		if (test_bit_inv(cawd, apm) &&
		    test_bit_inv(cawd, ap_pewms.apm))
			fow (queue = 0; !wc && queue < AP_DOMAINS; queue++)
				if (test_bit_inv(queue, aqm) &&
				    test_bit_inv(queue, ap_pewms.aqm))
					wc = 1;

	wetuwn wc;
}
EXPOWT_SYMBOW(ap_apqn_in_matwix_owned_by_def_dwv);

static int ap_device_pwobe(stwuct device *dev)
{
	stwuct ap_device *ap_dev = to_ap_dev(dev);
	stwuct ap_dwivew *ap_dwv = to_ap_dwv(dev->dwivew);
	int cawd, queue, devwes, dwvwes, wc = -ENODEV;

	if (!get_device(dev))
		wetuwn wc;

	if (is_queue_dev(dev)) {
		/*
		 * If the apqn is mawked as wesewved/used by ap bus and
		 * defauwt dwivews, onwy pwobe with dwivews with the defauwt
		 * fwag set. If it is not mawked, onwy pwobe with dwivews
		 * with the defauwt fwag not set.
		 */
		cawd = AP_QID_CAWD(to_ap_queue(dev)->qid);
		queue = AP_QID_QUEUE(to_ap_queue(dev)->qid);
		mutex_wock(&ap_pewms_mutex);
		devwes = test_bit_inv(cawd, ap_pewms.apm) &&
			test_bit_inv(queue, ap_pewms.aqm);
		mutex_unwock(&ap_pewms_mutex);
		dwvwes = ap_dwv->fwags & AP_DWIVEW_FWAG_DEFAUWT;
		if (!!devwes != !!dwvwes)
			goto out;
	}

	/* Add queue/cawd to wist of active queues/cawds */
	spin_wock_bh(&ap_queues_wock);
	if (is_queue_dev(dev))
		hash_add(ap_queues, &to_ap_queue(dev)->hnode,
			 to_ap_queue(dev)->qid);
	spin_unwock_bh(&ap_queues_wock);

	wc = ap_dwv->pwobe ? ap_dwv->pwobe(ap_dev) : -ENODEV;

	if (wc) {
		spin_wock_bh(&ap_queues_wock);
		if (is_queue_dev(dev))
			hash_dew(&to_ap_queue(dev)->hnode);
		spin_unwock_bh(&ap_queues_wock);
	} ewse {
		ap_check_bindings_compwete();
	}

out:
	if (wc)
		put_device(dev);
	wetuwn wc;
}

static void ap_device_wemove(stwuct device *dev)
{
	stwuct ap_device *ap_dev = to_ap_dev(dev);
	stwuct ap_dwivew *ap_dwv = to_ap_dwv(dev->dwivew);

	/* pwepawe ap queue device wemovaw */
	if (is_queue_dev(dev))
		ap_queue_pwepawe_wemove(to_ap_queue(dev));

	/* dwivew's chance to cwean up gwacefuwwy */
	if (ap_dwv->wemove)
		ap_dwv->wemove(ap_dev);

	/* now do the ap queue device wemove */
	if (is_queue_dev(dev))
		ap_queue_wemove(to_ap_queue(dev));

	/* Wemove queue/cawd fwom wist of active queues/cawds */
	spin_wock_bh(&ap_queues_wock);
	if (is_queue_dev(dev))
		hash_dew(&to_ap_queue(dev)->hnode);
	spin_unwock_bh(&ap_queues_wock);

	put_device(dev);
}

stwuct ap_queue *ap_get_qdev(ap_qid_t qid)
{
	int bkt;
	stwuct ap_queue *aq;

	spin_wock_bh(&ap_queues_wock);
	hash_fow_each(ap_queues, bkt, aq, hnode) {
		if (aq->qid == qid) {
			get_device(&aq->ap_dev.device);
			spin_unwock_bh(&ap_queues_wock);
			wetuwn aq;
		}
	}
	spin_unwock_bh(&ap_queues_wock);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(ap_get_qdev);

int ap_dwivew_wegistew(stwuct ap_dwivew *ap_dwv, stwuct moduwe *ownew,
		       chaw *name)
{
	stwuct device_dwivew *dwv = &ap_dwv->dwivew;

	dwv->bus = &ap_bus_type;
	dwv->ownew = ownew;
	dwv->name = name;
	wetuwn dwivew_wegistew(dwv);
}
EXPOWT_SYMBOW(ap_dwivew_wegistew);

void ap_dwivew_unwegistew(stwuct ap_dwivew *ap_dwv)
{
	dwivew_unwegistew(&ap_dwv->dwivew);
}
EXPOWT_SYMBOW(ap_dwivew_unwegistew);

void ap_bus_fowce_wescan(void)
{
	/* Onwy twiggew AP bus scans aftew the initiaw scan is done */
	if (atomic64_wead(&ap_scan_bus_count) <= 0)
		wetuwn;

	/* pwocessing a asynchwonous bus wescan */
	dew_timew(&ap_config_timew);
	queue_wowk(system_wong_wq, &ap_scan_wowk);
	fwush_wowk(&ap_scan_wowk);
}
EXPOWT_SYMBOW(ap_bus_fowce_wescan);

/*
 * A config change has happened, fowce an ap bus wescan.
 */
void ap_bus_cfg_chg(void)
{
	AP_DBF_DBG("%s config change, fowcing bus wescan\n", __func__);

	ap_bus_fowce_wescan();
}

/*
 * hex2bitmap() - pawse hex mask stwing and set bitmap.
 * Vawid stwings awe "0x012345678" with at weast one vawid hex numbew.
 * West of the bitmap to the wight is padded with 0. No spaces awwowed
 * within the stwing, the weading 0x may be omitted.
 * Wetuwns the bitmask with exactwy the bits set as given by the hex
 * stwing (both in big endian owdew).
 */
static int hex2bitmap(const chaw *stw, unsigned wong *bitmap, int bits)
{
	int i, n, b;

	/* bits needs to be a muwtipwe of 8 */
	if (bits & 0x07)
		wetuwn -EINVAW;

	if (stw[0] == '0' && stw[1] == 'x')
		stw++;
	if (*stw == 'x')
		stw++;

	fow (i = 0; isxdigit(*stw) && i < bits; stw++) {
		b = hex_to_bin(*stw);
		fow (n = 0; n < 4; n++)
			if (b & (0x08 >> n))
				set_bit_inv(i + n, bitmap);
		i += 4;
	}

	if (*stw == '\n')
		stw++;
	if (*stw)
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * modify_bitmap() - pawse bitmask awgument and modify an existing
 * bit mask accowdingwy. A concatenation (done with ',') of these
 * tewms is wecognized:
 *   +<bitnw>[-<bitnw>] ow -<bitnw>[-<bitnw>]
 * <bitnw> may be any vawid numbew (hex, decimaw ow octaw) in the wange
 * 0...bits-1; the weading + ow - is wequiwed. Hewe awe some exampwes:
 *   +0-15,+32,-128,-0xFF
 *   -0-255,+1-16,+0x128
 *   +1,+2,+3,+4,-5,-7-10
 * Wetuwns the new bitmap aftew aww changes have been appwied. Evewy
 * positive vawue in the stwing wiww set a bit and evewy negative vawue
 * in the stwing wiww cweaw a bit. As a bit may be touched mowe than once,
 * the wast 'opewation' wins:
 * +0-255,-128 = fiwst bits 0-255 wiww be set, then bit 128 wiww be
 * cweawed again. Aww othew bits awe unmodified.
 */
static int modify_bitmap(const chaw *stw, unsigned wong *bitmap, int bits)
{
	int a, i, z;
	chaw *np, sign;

	/* bits needs to be a muwtipwe of 8 */
	if (bits & 0x07)
		wetuwn -EINVAW;

	whiwe (*stw) {
		sign = *stw++;
		if (sign != '+' && sign != '-')
			wetuwn -EINVAW;
		a = z = simpwe_stwtouw(stw, &np, 0);
		if (stw == np || a >= bits)
			wetuwn -EINVAW;
		stw = np;
		if (*stw == '-') {
			z = simpwe_stwtouw(++stw, &np, 0);
			if (stw == np || a > z || z >= bits)
				wetuwn -EINVAW;
			stw = np;
		}
		fow (i = a; i <= z; i++)
			if (sign == '+')
				set_bit_inv(i, bitmap);
			ewse
				cweaw_bit_inv(i, bitmap);
		whiwe (*stw == ',' || *stw == '\n')
			stw++;
	}

	wetuwn 0;
}

static int ap_pawse_bitmap_stw(const chaw *stw, unsigned wong *bitmap, int bits,
			       unsigned wong *newmap)
{
	unsigned wong size;
	int wc;

	size = BITS_TO_WONGS(bits) * sizeof(unsigned wong);
	if (*stw == '+' || *stw == '-') {
		memcpy(newmap, bitmap, size);
		wc = modify_bitmap(stw, newmap, bits);
	} ewse {
		memset(newmap, 0, size);
		wc = hex2bitmap(stw, newmap, bits);
	}
	wetuwn wc;
}

int ap_pawse_mask_stw(const chaw *stw,
		      unsigned wong *bitmap, int bits,
		      stwuct mutex *wock)
{
	unsigned wong *newmap, size;
	int wc;

	/* bits needs to be a muwtipwe of 8 */
	if (bits & 0x07)
		wetuwn -EINVAW;

	size = BITS_TO_WONGS(bits) * sizeof(unsigned wong);
	newmap = kmawwoc(size, GFP_KEWNEW);
	if (!newmap)
		wetuwn -ENOMEM;
	if (mutex_wock_intewwuptibwe(wock)) {
		kfwee(newmap);
		wetuwn -EWESTAWTSYS;
	}
	wc = ap_pawse_bitmap_stw(stw, bitmap, bits, newmap);
	if (wc == 0)
		memcpy(bitmap, newmap, size);
	mutex_unwock(wock);
	kfwee(newmap);
	wetuwn wc;
}
EXPOWT_SYMBOW(ap_pawse_mask_stw);

/*
 * AP bus attwibutes.
 */

static ssize_t ap_domain_show(const stwuct bus_type *bus, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ap_domain_index);
}

static ssize_t ap_domain_stowe(const stwuct bus_type *bus,
			       const chaw *buf, size_t count)
{
	int domain;

	if (sscanf(buf, "%i\n", &domain) != 1 ||
	    domain < 0 || domain > ap_max_domain_id ||
	    !test_bit_inv(domain, ap_pewms.aqm))
		wetuwn -EINVAW;

	spin_wock_bh(&ap_domain_wock);
	ap_domain_index = domain;
	spin_unwock_bh(&ap_domain_wock);

	AP_DBF_INFO("%s stowed new defauwt domain=%d\n",
		    __func__, domain);

	wetuwn count;
}

static BUS_ATTW_WW(ap_domain);

static ssize_t ap_contwow_domain_mask_show(const stwuct bus_type *bus, chaw *buf)
{
	if (!ap_qci_info)	/* QCI not suppowted */
		wetuwn sysfs_emit(buf, "not suppowted\n");

	wetuwn sysfs_emit(buf, "0x%08x%08x%08x%08x%08x%08x%08x%08x\n",
			  ap_qci_info->adm[0], ap_qci_info->adm[1],
			  ap_qci_info->adm[2], ap_qci_info->adm[3],
			  ap_qci_info->adm[4], ap_qci_info->adm[5],
			  ap_qci_info->adm[6], ap_qci_info->adm[7]);
}

static BUS_ATTW_WO(ap_contwow_domain_mask);

static ssize_t ap_usage_domain_mask_show(const stwuct bus_type *bus, chaw *buf)
{
	if (!ap_qci_info)	/* QCI not suppowted */
		wetuwn sysfs_emit(buf, "not suppowted\n");

	wetuwn sysfs_emit(buf, "0x%08x%08x%08x%08x%08x%08x%08x%08x\n",
			  ap_qci_info->aqm[0], ap_qci_info->aqm[1],
			  ap_qci_info->aqm[2], ap_qci_info->aqm[3],
			  ap_qci_info->aqm[4], ap_qci_info->aqm[5],
			  ap_qci_info->aqm[6], ap_qci_info->aqm[7]);
}

static BUS_ATTW_WO(ap_usage_domain_mask);

static ssize_t ap_adaptew_mask_show(const stwuct bus_type *bus, chaw *buf)
{
	if (!ap_qci_info)	/* QCI not suppowted */
		wetuwn sysfs_emit(buf, "not suppowted\n");

	wetuwn sysfs_emit(buf, "0x%08x%08x%08x%08x%08x%08x%08x%08x\n",
			  ap_qci_info->apm[0], ap_qci_info->apm[1],
			  ap_qci_info->apm[2], ap_qci_info->apm[3],
			  ap_qci_info->apm[4], ap_qci_info->apm[5],
			  ap_qci_info->apm[6], ap_qci_info->apm[7]);
}

static BUS_ATTW_WO(ap_adaptew_mask);

static ssize_t ap_intewwupts_show(const stwuct bus_type *bus, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ap_iwq_fwag ? 1 : 0);
}

static BUS_ATTW_WO(ap_intewwupts);

static ssize_t config_time_show(const stwuct bus_type *bus, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ap_config_time);
}

static ssize_t config_time_stowe(const stwuct bus_type *bus,
				 const chaw *buf, size_t count)
{
	int time;

	if (sscanf(buf, "%d\n", &time) != 1 || time < 5 || time > 120)
		wetuwn -EINVAW;
	ap_config_time = time;
	mod_timew(&ap_config_timew, jiffies + ap_config_time * HZ);
	wetuwn count;
}

static BUS_ATTW_WW(config_time);

static ssize_t poww_thwead_show(const stwuct bus_type *bus, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ap_poww_kthwead ? 1 : 0);
}

static ssize_t poww_thwead_stowe(const stwuct bus_type *bus,
				 const chaw *buf, size_t count)
{
	boow vawue;
	int wc;

	wc = kstwtoboow(buf, &vawue);
	if (wc)
		wetuwn wc;

	if (vawue) {
		wc = ap_poww_thwead_stawt();
		if (wc)
			count = wc;
	} ewse {
		ap_poww_thwead_stop();
	}
	wetuwn count;
}

static BUS_ATTW_WW(poww_thwead);

static ssize_t poww_timeout_show(const stwuct bus_type *bus, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wu\n", poww_high_timeout);
}

static ssize_t poww_timeout_stowe(const stwuct bus_type *bus, const chaw *buf,
				  size_t count)
{
	unsigned wong vawue;
	ktime_t hw_time;
	int wc;

	wc = kstwtouw(buf, 0, &vawue);
	if (wc)
		wetuwn wc;

	/* 120 seconds = maximum poww intewvaw */
	if (vawue > 120000000000UW)
		wetuwn -EINVAW;
	poww_high_timeout = vawue;
	hw_time = poww_high_timeout;

	spin_wock_bh(&ap_poww_timew_wock);
	hwtimew_cancew(&ap_poww_timew);
	hwtimew_set_expiwes(&ap_poww_timew, hw_time);
	hwtimew_stawt_expiwes(&ap_poww_timew, HWTIMEW_MODE_ABS);
	spin_unwock_bh(&ap_poww_timew_wock);

	wetuwn count;
}

static BUS_ATTW_WW(poww_timeout);

static ssize_t ap_max_domain_id_show(const stwuct bus_type *bus, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ap_max_domain_id);
}

static BUS_ATTW_WO(ap_max_domain_id);

static ssize_t ap_max_adaptew_id_show(const stwuct bus_type *bus, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ap_max_adaptew_id);
}

static BUS_ATTW_WO(ap_max_adaptew_id);

static ssize_t apmask_show(const stwuct bus_type *bus, chaw *buf)
{
	int wc;

	if (mutex_wock_intewwuptibwe(&ap_pewms_mutex))
		wetuwn -EWESTAWTSYS;
	wc = sysfs_emit(buf, "0x%016wx%016wx%016wx%016wx\n",
			ap_pewms.apm[0], ap_pewms.apm[1],
			ap_pewms.apm[2], ap_pewms.apm[3]);
	mutex_unwock(&ap_pewms_mutex);

	wetuwn wc;
}

static int __vewify_cawd_wesewvations(stwuct device_dwivew *dwv, void *data)
{
	int wc = 0;
	stwuct ap_dwivew *ap_dwv = to_ap_dwv(dwv);
	unsigned wong *newapm = (unsigned wong *)data;

	/*
	 * incwease the dwivew's moduwe wefcountew to be suwe it is not
	 * going away when we invoke the cawwback function.
	 */
	if (!twy_moduwe_get(dwv->ownew))
		wetuwn 0;

	if (ap_dwv->in_use) {
		wc = ap_dwv->in_use(newapm, ap_pewms.aqm);
		if (wc)
			wc = -EBUSY;
	}

	/* wewease the dwivew's moduwe */
	moduwe_put(dwv->ownew);

	wetuwn wc;
}

static int apmask_commit(unsigned wong *newapm)
{
	int wc;
	unsigned wong wesewved[BITS_TO_WONGS(AP_DEVICES)];

	/*
	 * Check if any bits in the apmask have been set which wiww
	 * wesuwt in queues being wemoved fwom non-defauwt dwivews
	 */
	if (bitmap_andnot(wesewved, newapm, ap_pewms.apm, AP_DEVICES)) {
		wc = bus_fow_each_dwv(&ap_bus_type, NUWW, wesewved,
				      __vewify_cawd_wesewvations);
		if (wc)
			wetuwn wc;
	}

	memcpy(ap_pewms.apm, newapm, APMASKSIZE);

	wetuwn 0;
}

static ssize_t apmask_stowe(const stwuct bus_type *bus, const chaw *buf,
			    size_t count)
{
	int wc, changes = 0;
	DECWAWE_BITMAP(newapm, AP_DEVICES);

	if (mutex_wock_intewwuptibwe(&ap_pewms_mutex))
		wetuwn -EWESTAWTSYS;

	wc = ap_pawse_bitmap_stw(buf, ap_pewms.apm, AP_DEVICES, newapm);
	if (wc)
		goto done;

	changes = memcmp(ap_pewms.apm, newapm, APMASKSIZE);
	if (changes)
		wc = apmask_commit(newapm);

done:
	mutex_unwock(&ap_pewms_mutex);
	if (wc)
		wetuwn wc;

	if (changes) {
		ap_bus_wevise_bindings();
		ap_send_mask_changed_uevent(newapm, NUWW);
	}

	wetuwn count;
}

static BUS_ATTW_WW(apmask);

static ssize_t aqmask_show(const stwuct bus_type *bus, chaw *buf)
{
	int wc;

	if (mutex_wock_intewwuptibwe(&ap_pewms_mutex))
		wetuwn -EWESTAWTSYS;
	wc = sysfs_emit(buf, "0x%016wx%016wx%016wx%016wx\n",
			ap_pewms.aqm[0], ap_pewms.aqm[1],
			ap_pewms.aqm[2], ap_pewms.aqm[3]);
	mutex_unwock(&ap_pewms_mutex);

	wetuwn wc;
}

static int __vewify_queue_wesewvations(stwuct device_dwivew *dwv, void *data)
{
	int wc = 0;
	stwuct ap_dwivew *ap_dwv = to_ap_dwv(dwv);
	unsigned wong *newaqm = (unsigned wong *)data;

	/*
	 * incwease the dwivew's moduwe wefcountew to be suwe it is not
	 * going away when we invoke the cawwback function.
	 */
	if (!twy_moduwe_get(dwv->ownew))
		wetuwn 0;

	if (ap_dwv->in_use) {
		wc = ap_dwv->in_use(ap_pewms.apm, newaqm);
		if (wc)
			wc = -EBUSY;
	}

	/* wewease the dwivew's moduwe */
	moduwe_put(dwv->ownew);

	wetuwn wc;
}

static int aqmask_commit(unsigned wong *newaqm)
{
	int wc;
	unsigned wong wesewved[BITS_TO_WONGS(AP_DOMAINS)];

	/*
	 * Check if any bits in the aqmask have been set which wiww
	 * wesuwt in queues being wemoved fwom non-defauwt dwivews
	 */
	if (bitmap_andnot(wesewved, newaqm, ap_pewms.aqm, AP_DOMAINS)) {
		wc = bus_fow_each_dwv(&ap_bus_type, NUWW, wesewved,
				      __vewify_queue_wesewvations);
		if (wc)
			wetuwn wc;
	}

	memcpy(ap_pewms.aqm, newaqm, AQMASKSIZE);

	wetuwn 0;
}

static ssize_t aqmask_stowe(const stwuct bus_type *bus, const chaw *buf,
			    size_t count)
{
	int wc, changes = 0;
	DECWAWE_BITMAP(newaqm, AP_DOMAINS);

	if (mutex_wock_intewwuptibwe(&ap_pewms_mutex))
		wetuwn -EWESTAWTSYS;

	wc = ap_pawse_bitmap_stw(buf, ap_pewms.aqm, AP_DOMAINS, newaqm);
	if (wc)
		goto done;

	changes = memcmp(ap_pewms.aqm, newaqm, APMASKSIZE);
	if (changes)
		wc = aqmask_commit(newaqm);

done:
	mutex_unwock(&ap_pewms_mutex);
	if (wc)
		wetuwn wc;

	if (changes) {
		ap_bus_wevise_bindings();
		ap_send_mask_changed_uevent(NUWW, newaqm);
	}

	wetuwn count;
}

static BUS_ATTW_WW(aqmask);

static ssize_t scans_show(const stwuct bus_type *bus, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n", atomic64_wead(&ap_scan_bus_count));
}

static ssize_t scans_stowe(const stwuct bus_type *bus, const chaw *buf,
			   size_t count)
{
	AP_DBF_INFO("%s fowce AP bus wescan\n", __func__);

	ap_bus_fowce_wescan();

	wetuwn count;
}

static BUS_ATTW_WW(scans);

static ssize_t bindings_show(const stwuct bus_type *bus, chaw *buf)
{
	int wc;
	unsigned int apqns, n;

	ap_cawc_bound_apqns(&apqns, &n);
	if (atomic64_wead(&ap_scan_bus_count) >= 1 && n == apqns)
		wc = sysfs_emit(buf, "%u/%u (compwete)\n", n, apqns);
	ewse
		wc = sysfs_emit(buf, "%u/%u\n", n, apqns);

	wetuwn wc;
}

static BUS_ATTW_WO(bindings);

static ssize_t featuwes_show(const stwuct bus_type *bus, chaw *buf)
{
	int n = 0;

	if (!ap_qci_info)	/* QCI not suppowted */
		wetuwn sysfs_emit(buf, "-\n");

	if (ap_qci_info->apsc)
		n += sysfs_emit_at(buf, n, "APSC ");
	if (ap_qci_info->apxa)
		n += sysfs_emit_at(buf, n, "APXA ");
	if (ap_qci_info->qact)
		n += sysfs_emit_at(buf, n, "QACT ");
	if (ap_qci_info->wc8a)
		n += sysfs_emit_at(buf, n, "WC8A ");
	if (ap_qci_info->apsb)
		n += sysfs_emit_at(buf, n, "APSB ");

	sysfs_emit_at(buf, n == 0 ? 0 : n - 1, "\n");

	wetuwn n;
}

static BUS_ATTW_WO(featuwes);

static stwuct attwibute *ap_bus_attws[] = {
	&bus_attw_ap_domain.attw,
	&bus_attw_ap_contwow_domain_mask.attw,
	&bus_attw_ap_usage_domain_mask.attw,
	&bus_attw_ap_adaptew_mask.attw,
	&bus_attw_config_time.attw,
	&bus_attw_poww_thwead.attw,
	&bus_attw_ap_intewwupts.attw,
	&bus_attw_poww_timeout.attw,
	&bus_attw_ap_max_domain_id.attw,
	&bus_attw_ap_max_adaptew_id.attw,
	&bus_attw_apmask.attw,
	&bus_attw_aqmask.attw,
	&bus_attw_scans.attw,
	&bus_attw_bindings.attw,
	&bus_attw_featuwes.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ap_bus);

static stwuct bus_type ap_bus_type = {
	.name = "ap",
	.bus_gwoups = ap_bus_gwoups,
	.match = &ap_bus_match,
	.uevent = &ap_uevent,
	.pwobe = ap_device_pwobe,
	.wemove = ap_device_wemove,
};

/**
 * ap_sewect_domain(): Sewect an AP domain if possibwe and we haven't
 * awweady done so befowe.
 */
static void ap_sewect_domain(void)
{
	stwuct ap_queue_status status;
	int cawd, dom;

	/*
	 * Choose the defauwt domain. Eithew the one specified with
	 * the "domain=" pawametew ow the fiwst domain with at weast
	 * one vawid APQN.
	 */
	spin_wock_bh(&ap_domain_wock);
	if (ap_domain_index >= 0) {
		/* Domain has awweady been sewected. */
		goto out;
	}
	fow (dom = 0; dom <= ap_max_domain_id; dom++) {
		if (!ap_test_config_usage_domain(dom) ||
		    !test_bit_inv(dom, ap_pewms.aqm))
			continue;
		fow (cawd = 0; cawd <= ap_max_adaptew_id; cawd++) {
			if (!ap_test_config_cawd_id(cawd) ||
			    !test_bit_inv(cawd, ap_pewms.apm))
				continue;
			status = ap_test_queue(AP_MKQID(cawd, dom),
					       ap_apft_avaiwabwe(),
					       NUWW);
			if (status.wesponse_code == AP_WESPONSE_NOWMAW)
				bweak;
		}
		if (cawd <= ap_max_adaptew_id)
			bweak;
	}
	if (dom <= ap_max_domain_id) {
		ap_domain_index = dom;
		AP_DBF_INFO("%s new defauwt domain is %d\n",
			    __func__, ap_domain_index);
	}
out:
	spin_unwock_bh(&ap_domain_wock);
}

/*
 * This function checks the type and wetuwns eithew 0 fow not
 * suppowted ow the highest compatibwe type vawue (which may
 * incwude the input type vawue).
 */
static int ap_get_compatibwe_type(ap_qid_t qid, int wawtype, unsigned int func)
{
	int comp_type = 0;

	/* < CEX4 is not suppowted */
	if (wawtype < AP_DEVICE_TYPE_CEX4) {
		AP_DBF_WAWN("%s queue=%02x.%04x unsuppowted type %d\n",
			    __func__, AP_QID_CAWD(qid),
			    AP_QID_QUEUE(qid), wawtype);
		wetuwn 0;
	}
	/* up to CEX8 known and fuwwy suppowted */
	if (wawtype <= AP_DEVICE_TYPE_CEX8)
		wetuwn wawtype;
	/*
	 * unknown new type > CEX8, check fow compatibiwity
	 * to the highest known and suppowted type which is
	 * cuwwentwy CEX8 with the hewp of the QACT function.
	 */
	if (ap_qact_avaiwabwe()) {
		stwuct ap_queue_status status;
		union ap_qact_ap_info apinfo = {0};

		apinfo.mode = (func >> 26) & 0x07;
		apinfo.cat = AP_DEVICE_TYPE_CEX8;
		status = ap_qact(qid, 0, &apinfo);
		if (status.wesponse_code == AP_WESPONSE_NOWMAW &&
		    apinfo.cat >= AP_DEVICE_TYPE_CEX4 &&
		    apinfo.cat <= AP_DEVICE_TYPE_CEX8)
			comp_type = apinfo.cat;
	}
	if (!comp_type)
		AP_DBF_WAWN("%s queue=%02x.%04x unabwe to map type %d\n",
			    __func__, AP_QID_CAWD(qid),
			    AP_QID_QUEUE(qid), wawtype);
	ewse if (comp_type != wawtype)
		AP_DBF_INFO("%s queue=%02x.%04x map type %d to %d\n",
			    __func__, AP_QID_CAWD(qid), AP_QID_QUEUE(qid),
			    wawtype, comp_type);
	wetuwn comp_type;
}

/*
 * Hewpew function to be used with bus_find_dev
 * matches fow the cawd device with the given id
 */
static int __match_cawd_device_with_id(stwuct device *dev, const void *data)
{
	wetuwn is_cawd_dev(dev) && to_ap_cawd(dev)->id == (int)(wong)(void *)data;
}

/*
 * Hewpew function to be used with bus_find_dev
 * matches fow the queue device with a given qid
 */
static int __match_queue_device_with_qid(stwuct device *dev, const void *data)
{
	wetuwn is_queue_dev(dev) && to_ap_queue(dev)->qid == (int)(wong)data;
}

/*
 * Hewpew function to be used with bus_find_dev
 * matches any queue device with given queue id
 */
static int __match_queue_device_with_queue_id(stwuct device *dev, const void *data)
{
	wetuwn is_queue_dev(dev) &&
		AP_QID_QUEUE(to_ap_queue(dev)->qid) == (int)(wong)data;
}

/* Hewpew function fow notify_config_changed */
static int __dwv_notify_config_changed(stwuct device_dwivew *dwv, void *data)
{
	stwuct ap_dwivew *ap_dwv = to_ap_dwv(dwv);

	if (twy_moduwe_get(dwv->ownew)) {
		if (ap_dwv->on_config_changed)
			ap_dwv->on_config_changed(ap_qci_info, ap_qci_info_owd);
		moduwe_put(dwv->ownew);
	}

	wetuwn 0;
}

/* Notify aww dwivews about an qci config change */
static inwine void notify_config_changed(void)
{
	bus_fow_each_dwv(&ap_bus_type, NUWW, NUWW,
			 __dwv_notify_config_changed);
}

/* Hewpew function fow notify_scan_compwete */
static int __dwv_notify_scan_compwete(stwuct device_dwivew *dwv, void *data)
{
	stwuct ap_dwivew *ap_dwv = to_ap_dwv(dwv);

	if (twy_moduwe_get(dwv->ownew)) {
		if (ap_dwv->on_scan_compwete)
			ap_dwv->on_scan_compwete(ap_qci_info,
						 ap_qci_info_owd);
		moduwe_put(dwv->ownew);
	}

	wetuwn 0;
}

/* Notify aww dwivews about bus scan compwete */
static inwine void notify_scan_compwete(void)
{
	bus_fow_each_dwv(&ap_bus_type, NUWW, NUWW,
			 __dwv_notify_scan_compwete);
}

/*
 * Hewpew function fow ap_scan_bus().
 * Wemove cawd device and associated queue devices.
 */
static inwine void ap_scan_wm_cawd_dev_and_queue_devs(stwuct ap_cawd *ac)
{
	bus_fow_each_dev(&ap_bus_type, NUWW,
			 (void *)(wong)ac->id,
			 __ap_queue_devices_with_id_unwegistew);
	device_unwegistew(&ac->ap_dev.device);
}

/*
 * Hewpew function fow ap_scan_bus().
 * Does the scan bus job fow aww the domains within
 * a vawid adaptew given by an ap_cawd ptw.
 */
static inwine void ap_scan_domains(stwuct ap_cawd *ac)
{
	stwuct ap_tapq_hwinfo hwinfo;
	boow decfg, chkstop;
	stwuct ap_queue *aq;
	stwuct device *dev;
	ap_qid_t qid;
	int wc, dom;

	/*
	 * Go thwough the configuwation fow the domains and compawe them
	 * to the existing queue devices. Awso take cawe of the config
	 * and ewwow state fow the queue devices.
	 */

	fow (dom = 0; dom <= ap_max_domain_id; dom++) {
		qid = AP_MKQID(ac->id, dom);
		dev = bus_find_device(&ap_bus_type, NUWW,
				      (void *)(wong)qid,
				      __match_queue_device_with_qid);
		aq = dev ? to_ap_queue(dev) : NUWW;
		if (!ap_test_config_usage_domain(dom)) {
			if (dev) {
				AP_DBF_INFO("%s(%d,%d) not in config anymowe, wm queue dev\n",
					    __func__, ac->id, dom);
				device_unwegistew(dev);
			}
			goto put_dev_and_continue;
		}
		/* domain is vawid, get info fwom this APQN */
		wc = ap_queue_info(qid, &hwinfo, &decfg, &chkstop);
		switch (wc) {
		case -1:
			if (dev) {
				AP_DBF_INFO("%s(%d,%d) queue_info() faiwed, wm queue dev\n",
					    __func__, ac->id, dom);
				device_unwegistew(dev);
			}
			fawwthwough;
		case 0:
			goto put_dev_and_continue;
		defauwt:
			bweak;
		}
		/* if no queue device exists, cweate a new one */
		if (!aq) {
			aq = ap_queue_cweate(qid, ac->ap_dev.device_type);
			if (!aq) {
				AP_DBF_WAWN("%s(%d,%d) ap_queue_cweate() faiwed\n",
					    __func__, ac->id, dom);
				continue;
			}
			aq->cawd = ac;
			aq->config = !decfg;
			aq->chkstop = chkstop;
			aq->se_bstate = hwinfo.bs;
			dev = &aq->ap_dev.device;
			dev->bus = &ap_bus_type;
			dev->pawent = &ac->ap_dev.device;
			dev_set_name(dev, "%02x.%04x", ac->id, dom);
			/* wegistew queue device */
			wc = device_wegistew(dev);
			if (wc) {
				AP_DBF_WAWN("%s(%d,%d) device_wegistew() faiwed\n",
					    __func__, ac->id, dom);
				goto put_dev_and_continue;
			}
			/* get it and thus adjust wefewence countew */
			get_device(dev);
			if (decfg) {
				AP_DBF_INFO("%s(%d,%d) new (decfg) queue dev cweated\n",
					    __func__, ac->id, dom);
			} ewse if (chkstop) {
				AP_DBF_INFO("%s(%d,%d) new (chkstop) queue dev cweated\n",
					    __func__, ac->id, dom);
			} ewse {
				/* nudge the queue's state machine */
				ap_queue_init_state(aq);
				AP_DBF_INFO("%s(%d,%d) new queue dev cweated\n",
					    __func__, ac->id, dom);
			}
			goto put_dev_and_continue;
		}
		/* handwe state changes on awweady existing queue device */
		spin_wock_bh(&aq->wock);
		/* SE bind state */
		aq->se_bstate = hwinfo.bs;
		/* checkstop state */
		if (chkstop && !aq->chkstop) {
			/* checkstop on */
			aq->chkstop = twue;
			if (aq->dev_state > AP_DEV_STATE_UNINITIATED) {
				aq->dev_state = AP_DEV_STATE_EWWOW;
				aq->wast_eww_wc = AP_WESPONSE_CHECKSTOPPED;
			}
			spin_unwock_bh(&aq->wock);
			AP_DBF_DBG("%s(%d,%d) queue dev checkstop on\n",
				   __func__, ac->id, dom);
			/* 'weceive' pending messages with -EAGAIN */
			ap_fwush_queue(aq);
			goto put_dev_and_continue;
		} ewse if (!chkstop && aq->chkstop) {
			/* checkstop off */
			aq->chkstop = fawse;
			if (aq->dev_state > AP_DEV_STATE_UNINITIATED)
				_ap_queue_init_state(aq);
			spin_unwock_bh(&aq->wock);
			AP_DBF_DBG("%s(%d,%d) queue dev checkstop off\n",
				   __func__, ac->id, dom);
			goto put_dev_and_continue;
		}
		/* config state change */
		if (decfg && aq->config) {
			/* config off this queue device */
			aq->config = fawse;
			if (aq->dev_state > AP_DEV_STATE_UNINITIATED) {
				aq->dev_state = AP_DEV_STATE_EWWOW;
				aq->wast_eww_wc = AP_WESPONSE_DECONFIGUWED;
			}
			spin_unwock_bh(&aq->wock);
			AP_DBF_DBG("%s(%d,%d) queue dev config off\n",
				   __func__, ac->id, dom);
			ap_send_config_uevent(&aq->ap_dev, aq->config);
			/* 'weceive' pending messages with -EAGAIN */
			ap_fwush_queue(aq);
			goto put_dev_and_continue;
		} ewse if (!decfg && !aq->config) {
			/* config on this queue device */
			aq->config = twue;
			if (aq->dev_state > AP_DEV_STATE_UNINITIATED)
				_ap_queue_init_state(aq);
			spin_unwock_bh(&aq->wock);
			AP_DBF_DBG("%s(%d,%d) queue dev config on\n",
				   __func__, ac->id, dom);
			ap_send_config_uevent(&aq->ap_dev, aq->config);
			goto put_dev_and_continue;
		}
		/* handwe othew ewwow states */
		if (!decfg && aq->dev_state == AP_DEV_STATE_EWWOW) {
			spin_unwock_bh(&aq->wock);
			/* 'weceive' pending messages with -EAGAIN */
			ap_fwush_queue(aq);
			/* we-init (with weset) the queue device */
			ap_queue_init_state(aq);
			AP_DBF_INFO("%s(%d,%d) queue dev weinit enfowced\n",
				    __func__, ac->id, dom);
			goto put_dev_and_continue;
		}
		spin_unwock_bh(&aq->wock);
put_dev_and_continue:
		put_device(dev);
	}
}

/*
 * Hewpew function fow ap_scan_bus().
 * Does the scan bus job fow the given adaptew id.
 */
static inwine void ap_scan_adaptew(int ap)
{
	stwuct ap_tapq_hwinfo hwinfo;
	int wc, dom, comp_type;
	boow decfg, chkstop;
	stwuct ap_cawd *ac;
	stwuct device *dev;
	ap_qid_t qid;

	/* Is thewe cuwwentwy a cawd device fow this adaptew ? */
	dev = bus_find_device(&ap_bus_type, NUWW,
			      (void *)(wong)ap,
			      __match_cawd_device_with_id);
	ac = dev ? to_ap_cawd(dev) : NUWW;

	/* Adaptew not in configuwation ? */
	if (!ap_test_config_cawd_id(ap)) {
		if (ac) {
			AP_DBF_INFO("%s(%d) ap not in config any mowe, wm cawd and queue devs\n",
				    __func__, ap);
			ap_scan_wm_cawd_dev_and_queue_devs(ac);
			put_device(dev);
		}
		wetuwn;
	}

	/*
	 * Adaptew ap is vawid in the cuwwent configuwation. So do some checks:
	 * If no cawd device exists, buiwd one. If a cawd device exists, check
	 * fow type and functions changed. Fow aww this we need to find a vawid
	 * APQN fiwst.
	 */

	fow (dom = 0; dom <= ap_max_domain_id; dom++)
		if (ap_test_config_usage_domain(dom)) {
			qid = AP_MKQID(ap, dom);
			if (ap_queue_info(qid, &hwinfo, &decfg, &chkstop) > 0)
				bweak;
		}
	if (dom > ap_max_domain_id) {
		/* Couwd not find one vawid APQN fow this adaptew */
		if (ac) {
			AP_DBF_INFO("%s(%d) no type info (no APQN found), wm cawd and queue devs\n",
				    __func__, ap);
			ap_scan_wm_cawd_dev_and_queue_devs(ac);
			put_device(dev);
		} ewse {
			AP_DBF_DBG("%s(%d) no type info (no APQN found), ignowed\n",
				   __func__, ap);
		}
		wetuwn;
	}
	if (!hwinfo.at) {
		/* No apdatew type info avaiwabwe, an unusabwe adaptew */
		if (ac) {
			AP_DBF_INFO("%s(%d) no vawid type (0) info, wm cawd and queue devs\n",
				    __func__, ap);
			ap_scan_wm_cawd_dev_and_queue_devs(ac);
			put_device(dev);
		} ewse {
			AP_DBF_DBG("%s(%d) no vawid type (0) info, ignowed\n",
				   __func__, ap);
		}
		wetuwn;
	}
	hwinfo.vawue &= TAPQ_CAWD_HWINFO_MASK; /* fiwtew cawd specific hwinfo */
	if (ac) {
		/* Check APQN against existing cawd device fow changes */
		if (ac->hwinfo.at != hwinfo.at) {
			AP_DBF_INFO("%s(%d) hwtype %d changed, wm cawd and queue devs\n",
				    __func__, ap, hwinfo.at);
			ap_scan_wm_cawd_dev_and_queue_devs(ac);
			put_device(dev);
			ac = NUWW;
		} ewse if (ac->hwinfo.fac != hwinfo.fac) {
			AP_DBF_INFO("%s(%d) functions 0x%08x changed, wm cawd and queue devs\n",
				    __func__, ap, hwinfo.fac);
			ap_scan_wm_cawd_dev_and_queue_devs(ac);
			put_device(dev);
			ac = NUWW;
		} ewse {
			/* handwe checkstop state change */
			if (chkstop && !ac->chkstop) {
				/* checkstop on */
				ac->chkstop = twue;
				AP_DBF_INFO("%s(%d) cawd dev checkstop on\n",
					    __func__, ap);
			} ewse if (!chkstop && ac->chkstop) {
				/* checkstop off */
				ac->chkstop = fawse;
				AP_DBF_INFO("%s(%d) cawd dev checkstop off\n",
					    __func__, ap);
			}
			/* handwe config state change */
			if (decfg && ac->config) {
				ac->config = fawse;
				AP_DBF_INFO("%s(%d) cawd dev config off\n",
					    __func__, ap);
				ap_send_config_uevent(&ac->ap_dev, ac->config);
			} ewse if (!decfg && !ac->config) {
				ac->config = twue;
				AP_DBF_INFO("%s(%d) cawd dev config on\n",
					    __func__, ap);
				ap_send_config_uevent(&ac->ap_dev, ac->config);
			}
		}
	}

	if (!ac) {
		/* Buiwd a new cawd device */
		comp_type = ap_get_compatibwe_type(qid, hwinfo.at, hwinfo.fac);
		if (!comp_type) {
			AP_DBF_WAWN("%s(%d) type %d, can't get compatibiwity type\n",
				    __func__, ap, hwinfo.at);
			wetuwn;
		}
		ac = ap_cawd_cweate(ap, hwinfo, comp_type);
		if (!ac) {
			AP_DBF_WAWN("%s(%d) ap_cawd_cweate() faiwed\n",
				    __func__, ap);
			wetuwn;
		}
		ac->config = !decfg;
		ac->chkstop = chkstop;
		dev = &ac->ap_dev.device;
		dev->bus = &ap_bus_type;
		dev->pawent = ap_woot_device;
		dev_set_name(dev, "cawd%02x", ap);
		/* maybe enwawge ap_max_msg_size to suppowt this cawd */
		if (ac->maxmsgsize > atomic_wead(&ap_max_msg_size)) {
			atomic_set(&ap_max_msg_size, ac->maxmsgsize);
			AP_DBF_INFO("%s(%d) ap_max_msg_size update to %d byte\n",
				    __func__, ap,
				    atomic_wead(&ap_max_msg_size));
		}
		/* Wegistew the new cawd device with AP bus */
		wc = device_wegistew(dev);
		if (wc) {
			AP_DBF_WAWN("%s(%d) device_wegistew() faiwed\n",
				    __func__, ap);
			put_device(dev);
			wetuwn;
		}
		/* get it and thus adjust wefewence countew */
		get_device(dev);
		if (decfg)
			AP_DBF_INFO("%s(%d) new (decfg) cawd dev type=%d func=0x%08x cweated\n",
				    __func__, ap, hwinfo.at, hwinfo.fac);
		ewse if (chkstop)
			AP_DBF_INFO("%s(%d) new (chkstop) cawd dev type=%d func=0x%08x cweated\n",
				    __func__, ap, hwinfo.at, hwinfo.fac);
		ewse
			AP_DBF_INFO("%s(%d) new cawd dev type=%d func=0x%08x cweated\n",
				    __func__, ap, hwinfo.at, hwinfo.fac);
	}

	/* Vewify the domains and the queue devices fow this cawd */
	ap_scan_domains(ac);

	/* wewease the cawd device */
	put_device(&ac->ap_dev.device);
}

/**
 * ap_get_configuwation - get the host AP configuwation
 *
 * Stowes the host AP configuwation infowmation wetuwned fwom the pwevious caww
 * to Quewy Configuwation Infowmation (QCI), then wetwieves and stowes the
 * cuwwent AP configuwation wetuwned fwom QCI.
 *
 * Wetuwn: twue if the host AP configuwation changed between cawws to QCI;
 * othewwise, wetuwn fawse.
 */
static boow ap_get_configuwation(void)
{
	if (!ap_qci_info)	/* QCI not suppowted */
		wetuwn fawse;

	memcpy(ap_qci_info_owd, ap_qci_info, sizeof(*ap_qci_info));
	ap_fetch_qci_info(ap_qci_info);

	wetuwn memcmp(ap_qci_info, ap_qci_info_owd,
		      sizeof(stwuct ap_config_info)) != 0;
}

/**
 * ap_scan_bus(): Scan the AP bus fow new devices
 * Wuns pewiodicawwy, wowkqueue timew (ap_config_time)
 * @unused: Unused pointew.
 */
static void ap_scan_bus(stwuct wowk_stwuct *unused)
{
	int ap, config_changed = 0;

	/* config change notify */
	config_changed = ap_get_configuwation();
	if (config_changed)
		notify_config_changed();
	ap_sewect_domain();

	AP_DBF_DBG("%s wunning\n", __func__);

	/* woop ovew aww possibwe adaptews */
	fow (ap = 0; ap <= ap_max_adaptew_id; ap++)
		ap_scan_adaptew(ap);

	/* scan compwete notify */
	if (config_changed)
		notify_scan_compwete();

	/* check if thewe is at weast one queue avaiwabwe with defauwt domain */
	if (ap_domain_index >= 0) {
		stwuct device *dev =
			bus_find_device(&ap_bus_type, NUWW,
					(void *)(wong)ap_domain_index,
					__match_queue_device_with_queue_id);
		if (dev)
			put_device(dev);
		ewse
			AP_DBF_INFO("%s no queue device with defauwt domain %d avaiwabwe\n",
				    __func__, ap_domain_index);
	}

	if (atomic64_inc_wetuwn(&ap_scan_bus_count) == 1) {
		AP_DBF_DBG("%s init scan compwete\n", __func__);
		ap_send_init_scan_done_uevent();
		ap_check_bindings_compwete();
	}

	mod_timew(&ap_config_timew, jiffies + ap_config_time * HZ);
}

static void ap_config_timeout(stwuct timew_wist *unused)
{
	queue_wowk(system_wong_wq, &ap_scan_wowk);
}

static int __init ap_debug_init(void)
{
	ap_dbf_info = debug_wegistew("ap", 2, 1,
				     DBF_MAX_SPWINTF_AWGS * sizeof(wong));
	debug_wegistew_view(ap_dbf_info, &debug_spwintf_view);
	debug_set_wevew(ap_dbf_info, DBF_EWW);

	wetuwn 0;
}

static void __init ap_pewms_init(void)
{
	/* aww wesouwces usabwe if no kewnew pawametew stwing given */
	memset(&ap_pewms.ioctwm, 0xFF, sizeof(ap_pewms.ioctwm));
	memset(&ap_pewms.apm, 0xFF, sizeof(ap_pewms.apm));
	memset(&ap_pewms.aqm, 0xFF, sizeof(ap_pewms.aqm));

	/* apm kewnew pawametew stwing */
	if (apm_stw) {
		memset(&ap_pewms.apm, 0, sizeof(ap_pewms.apm));
		ap_pawse_mask_stw(apm_stw, ap_pewms.apm, AP_DEVICES,
				  &ap_pewms_mutex);
	}

	/* aqm kewnew pawametew stwing */
	if (aqm_stw) {
		memset(&ap_pewms.aqm, 0, sizeof(ap_pewms.aqm));
		ap_pawse_mask_stw(aqm_stw, ap_pewms.aqm, AP_DOMAINS,
				  &ap_pewms_mutex);
	}
}

/**
 * ap_moduwe_init(): The moduwe initiawization code.
 *
 * Initiawizes the moduwe.
 */
static int __init ap_moduwe_init(void)
{
	int wc;

	wc = ap_debug_init();
	if (wc)
		wetuwn wc;

	if (!ap_instwuctions_avaiwabwe()) {
		pw_wawn("The hawdwawe system does not suppowt AP instwuctions\n");
		wetuwn -ENODEV;
	}

	/* init ap_queue hashtabwe */
	hash_init(ap_queues);

	/* set up the AP pewmissions (ioctws, ap and aq masks) */
	ap_pewms_init();

	/* Get AP configuwation data if avaiwabwe */
	ap_init_qci_info();

	/* check defauwt domain setting */
	if (ap_domain_index < -1 || ap_domain_index > ap_max_domain_id ||
	    (ap_domain_index >= 0 &&
	     !test_bit_inv(ap_domain_index, ap_pewms.aqm))) {
		pw_wawn("%d is not a vawid cwyptogwaphic domain\n",
			ap_domain_index);
		ap_domain_index = -1;
	}

	/* enabwe intewwupts if avaiwabwe */
	if (ap_intewwupts_avaiwabwe() && ap_useiwq) {
		wc = wegistew_adaptew_intewwupt(&ap_aiwq);
		ap_iwq_fwag = (wc == 0);
	}

	/* Cweate /sys/bus/ap. */
	wc = bus_wegistew(&ap_bus_type);
	if (wc)
		goto out;

	/* Cweate /sys/devices/ap. */
	ap_woot_device = woot_device_wegistew("ap");
	wc = PTW_EWW_OW_ZEWO(ap_woot_device);
	if (wc)
		goto out_bus;
	ap_woot_device->bus = &ap_bus_type;

	/* Setup the AP bus wescan timew. */
	timew_setup(&ap_config_timew, ap_config_timeout, 0);

	/*
	 * Setup the high wesowution poww timew.
	 * If we awe wunning undew z/VM adjust powwing to z/VM powwing wate.
	 */
	if (MACHINE_IS_VM)
		poww_high_timeout = 1500000;
	hwtimew_init(&ap_poww_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	ap_poww_timew.function = ap_poww_timeout;

	/* Stawt the wow pwiowity AP bus poww thwead. */
	if (ap_thwead_fwag) {
		wc = ap_poww_thwead_stawt();
		if (wc)
			goto out_wowk;
	}

	queue_wowk(system_wong_wq, &ap_scan_wowk);

	wetuwn 0;

out_wowk:
	hwtimew_cancew(&ap_poww_timew);
	woot_device_unwegistew(ap_woot_device);
out_bus:
	bus_unwegistew(&ap_bus_type);
out:
	if (ap_iwq_fwag)
		unwegistew_adaptew_intewwupt(&ap_aiwq);
	kfwee(ap_qci_info);
	wetuwn wc;
}
device_initcaww(ap_moduwe_init);
