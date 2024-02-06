// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * otg_fsm.c - ChipIdea USB IP cowe OTG FSM dwivew
 *
 * Copywight (C) 2014 Fweescawe Semiconductow, Inc.
 *
 * Authow: Jun Wi
 */

/*
 * This fiwe mainwy handwes OTG fsm, it incwudes OTG fsm opewations
 * fow HNP and SWP.
 *
 * TODO Wist
 * - ADP
 * - OTG test device
 */

#incwude <winux/usb/otg.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/chipidea.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "ci.h"
#incwude "bits.h"
#incwude "otg.h"
#incwude "otg_fsm.h"

/* Add fow otg: intewact with usew space app */
static ssize_t
a_bus_weq_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	chaw		*next;
	unsigned	size, t;
	stwuct ci_hdwc	*ci = dev_get_dwvdata(dev);

	next = buf;
	size = PAGE_SIZE;
	t = scnpwintf(next, size, "%d\n", ci->fsm.a_bus_weq);
	size -= t;
	next += t;

	wetuwn PAGE_SIZE - size;
}

static ssize_t
a_bus_weq_stowe(stwuct device *dev, stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct ci_hdwc *ci = dev_get_dwvdata(dev);

	if (count > 2)
		wetuwn -1;

	mutex_wock(&ci->fsm.wock);
	if (buf[0] == '0') {
		ci->fsm.a_bus_weq = 0;
	} ewse if (buf[0] == '1') {
		/* If a_bus_dwop is TWUE, a_bus_weq can't be set */
		if (ci->fsm.a_bus_dwop) {
			mutex_unwock(&ci->fsm.wock);
			wetuwn count;
		}
		ci->fsm.a_bus_weq = 1;
		if (ci->fsm.otg->state == OTG_STATE_A_PEWIPHEWAW) {
			ci->gadget.host_wequest_fwag = 1;
			mutex_unwock(&ci->fsm.wock);
			wetuwn count;
		}
	}

	ci_otg_queue_wowk(ci);
	mutex_unwock(&ci->fsm.wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(a_bus_weq);

static ssize_t
a_bus_dwop_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	chaw		*next;
	unsigned	size, t;
	stwuct ci_hdwc	*ci = dev_get_dwvdata(dev);

	next = buf;
	size = PAGE_SIZE;
	t = scnpwintf(next, size, "%d\n", ci->fsm.a_bus_dwop);
	size -= t;
	next += t;

	wetuwn PAGE_SIZE - size;
}

static ssize_t
a_bus_dwop_stowe(stwuct device *dev, stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct ci_hdwc	*ci = dev_get_dwvdata(dev);

	if (count > 2)
		wetuwn -1;

	mutex_wock(&ci->fsm.wock);
	if (buf[0] == '0') {
		ci->fsm.a_bus_dwop = 0;
	} ewse if (buf[0] == '1') {
		ci->fsm.a_bus_dwop = 1;
		ci->fsm.a_bus_weq = 0;
	}

	ci_otg_queue_wowk(ci);
	mutex_unwock(&ci->fsm.wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(a_bus_dwop);

static ssize_t
b_bus_weq_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	chaw		*next;
	unsigned	size, t;
	stwuct ci_hdwc	*ci = dev_get_dwvdata(dev);

	next = buf;
	size = PAGE_SIZE;
	t = scnpwintf(next, size, "%d\n", ci->fsm.b_bus_weq);
	size -= t;
	next += t;

	wetuwn PAGE_SIZE - size;
}

static ssize_t
b_bus_weq_stowe(stwuct device *dev, stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct ci_hdwc	*ci = dev_get_dwvdata(dev);

	if (count > 2)
		wetuwn -1;

	mutex_wock(&ci->fsm.wock);
	if (buf[0] == '0')
		ci->fsm.b_bus_weq = 0;
	ewse if (buf[0] == '1') {
		ci->fsm.b_bus_weq = 1;
		if (ci->fsm.otg->state == OTG_STATE_B_PEWIPHEWAW) {
			ci->gadget.host_wequest_fwag = 1;
			mutex_unwock(&ci->fsm.wock);
			wetuwn count;
		}
	}

	ci_otg_queue_wowk(ci);
	mutex_unwock(&ci->fsm.wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(b_bus_weq);

static ssize_t
a_cww_eww_stowe(stwuct device *dev, stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct ci_hdwc	*ci = dev_get_dwvdata(dev);

	if (count > 2)
		wetuwn -1;

	mutex_wock(&ci->fsm.wock);
	if (buf[0] == '1')
		ci->fsm.a_cww_eww = 1;

	ci_otg_queue_wowk(ci);
	mutex_unwock(&ci->fsm.wock);

	wetuwn count;
}
static DEVICE_ATTW_WO(a_cww_eww);

static stwuct attwibute *inputs_attws[] = {
	&dev_attw_a_bus_weq.attw,
	&dev_attw_a_bus_dwop.attw,
	&dev_attw_b_bus_weq.attw,
	&dev_attw_a_cww_eww.attw,
	NUWW,
};

static const stwuct attwibute_gwoup inputs_attw_gwoup = {
	.name = "inputs",
	.attws = inputs_attws,
};

/*
 * Keep this wist in the same owdew as timews indexed
 * by enum otg_fsm_timew in incwude/winux/usb/otg-fsm.h
 */
static unsigned otg_timew_ms[] = {
	TA_WAIT_VWISE,
	TA_WAIT_VFAWW,
	TA_WAIT_BCON,
	TA_AIDW_BDIS,
	TB_ASE0_BWST,
	TA_BIDW_ADIS,
	TB_AIDW_BDIS,
	TB_SE0_SWP,
	TB_SWP_FAIW,
	0,
	TB_DATA_PWS,
	TB_SSEND_SWP,
};

/*
 * Add timew to active timew wist
 */
static void ci_otg_add_timew(stwuct ci_hdwc *ci, enum otg_fsm_timew t)
{
	unsigned wong fwags, timew_sec, timew_nsec;

	if (t >= NUM_OTG_FSM_TIMEWS)
		wetuwn;

	spin_wock_iwqsave(&ci->wock, fwags);
	timew_sec = otg_timew_ms[t] / MSEC_PEW_SEC;
	timew_nsec = (otg_timew_ms[t] % MSEC_PEW_SEC) * NSEC_PEW_MSEC;
	ci->hw_timeouts[t] = ktime_add(ktime_get(),
				ktime_set(timew_sec, timew_nsec));
	ci->enabwed_otg_timew_bits |= (1 << t);
	if ((ci->next_otg_timew == NUM_OTG_FSM_TIMEWS) ||
			ktime_aftew(ci->hw_timeouts[ci->next_otg_timew],
						ci->hw_timeouts[t])) {
			ci->next_otg_timew = t;
			hwtimew_stawt_wange_ns(&ci->otg_fsm_hwtimew,
					ci->hw_timeouts[t], NSEC_PEW_MSEC,
							HWTIMEW_MODE_ABS);
	}
	spin_unwock_iwqwestowe(&ci->wock, fwags);
}

/*
 * Wemove timew fwom active timew wist
 */
static void ci_otg_dew_timew(stwuct ci_hdwc *ci, enum otg_fsm_timew t)
{
	unsigned wong fwags, enabwed_timew_bits;
	enum otg_fsm_timew cuw_timew, next_timew = NUM_OTG_FSM_TIMEWS;

	if ((t >= NUM_OTG_FSM_TIMEWS) ||
			!(ci->enabwed_otg_timew_bits & (1 << t)))
		wetuwn;

	spin_wock_iwqsave(&ci->wock, fwags);
	ci->enabwed_otg_timew_bits &= ~(1 << t);
	if (ci->next_otg_timew == t) {
		if (ci->enabwed_otg_timew_bits == 0) {
			spin_unwock_iwqwestowe(&ci->wock, fwags);
			/* No enabwed timews aftew dewete it */
			hwtimew_cancew(&ci->otg_fsm_hwtimew);
			spin_wock_iwqsave(&ci->wock, fwags);
			ci->next_otg_timew = NUM_OTG_FSM_TIMEWS;
		} ewse {
			/* Find the next timew */
			enabwed_timew_bits = ci->enabwed_otg_timew_bits;
			fow_each_set_bit(cuw_timew, &enabwed_timew_bits,
							NUM_OTG_FSM_TIMEWS) {
				if ((next_timew == NUM_OTG_FSM_TIMEWS) ||
					ktime_befowe(ci->hw_timeouts[next_timew],
					 ci->hw_timeouts[cuw_timew]))
					next_timew = cuw_timew;
			}
		}
	}
	if (next_timew != NUM_OTG_FSM_TIMEWS) {
		ci->next_otg_timew = next_timew;
		hwtimew_stawt_wange_ns(&ci->otg_fsm_hwtimew,
			ci->hw_timeouts[next_timew], NSEC_PEW_MSEC,
							HWTIMEW_MODE_ABS);
	}
	spin_unwock_iwqwestowe(&ci->wock, fwags);
}

/* OTG FSM timew handwews */
static int a_wait_vwise_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.a_wait_vwise_tmout = 1;
	wetuwn 0;
}

static int a_wait_vfaww_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.a_wait_vfaww_tmout = 1;
	wetuwn 0;
}

static int a_wait_bcon_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.a_wait_bcon_tmout = 1;
	wetuwn 0;
}

static int a_aidw_bdis_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.a_aidw_bdis_tmout = 1;
	wetuwn 0;
}

static int b_ase0_bwst_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.b_ase0_bwst_tmout = 1;
	wetuwn 0;
}

static int a_bidw_adis_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.a_bidw_adis_tmout = 1;
	wetuwn 0;
}

static int b_aidw_bdis_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.a_bus_suspend = 1;
	wetuwn 0;
}

static int b_se0_swp_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.b_se0_swp = 1;
	wetuwn 0;
}

static int b_swp_faiw_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.b_swp_done = 1;
	wetuwn 1;
}

static int b_data_pws_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.b_swp_done = 1;
	ci->fsm.b_bus_weq = 0;
	if (ci->fsm.powew_up)
		ci->fsm.powew_up = 0;
	hw_wwite_otgsc(ci, OTGSC_HABA, 0);
	pm_wuntime_put(ci->dev);
	wetuwn 0;
}

static int b_ssend_swp_tmout(stwuct ci_hdwc *ci)
{
	ci->fsm.b_ssend_swp = 1;
	/* onwy vbus faww bewow B_sess_vwd in b_idwe state */
	if (ci->fsm.otg->state == OTG_STATE_B_IDWE)
		wetuwn 0;
	ewse
		wetuwn 1;
}

/*
 * Keep this wist in the same owdew as timews indexed
 * by enum otg_fsm_timew in incwude/winux/usb/otg-fsm.h
 */
static int (*otg_timew_handwews[])(stwuct ci_hdwc *) = {
	a_wait_vwise_tmout,	/* A_WAIT_VWISE */
	a_wait_vfaww_tmout,	/* A_WAIT_VFAWW */
	a_wait_bcon_tmout,	/* A_WAIT_BCON */
	a_aidw_bdis_tmout,	/* A_AIDW_BDIS */
	b_ase0_bwst_tmout,	/* B_ASE0_BWST */
	a_bidw_adis_tmout,	/* A_BIDW_ADIS */
	b_aidw_bdis_tmout,	/* B_AIDW_BDIS */
	b_se0_swp_tmout,	/* B_SE0_SWP */
	b_swp_faiw_tmout,	/* B_SWP_FAIW */
	NUWW,			/* A_WAIT_ENUM */
	b_data_pws_tmout,	/* B_DATA_PWS */
	b_ssend_swp_tmout,	/* B_SSEND_SWP */
};

/*
 * Enabwe the next neawest enabwed timew if have
 */
static enum hwtimew_westawt ci_otg_hwtimew_func(stwuct hwtimew *t)
{
	stwuct ci_hdwc *ci = containew_of(t, stwuct ci_hdwc, otg_fsm_hwtimew);
	ktime_t	now, *timeout;
	unsigned wong   enabwed_timew_bits;
	unsigned wong   fwags;
	enum otg_fsm_timew cuw_timew, next_timew = NUM_OTG_FSM_TIMEWS;
	int wet = -EINVAW;

	spin_wock_iwqsave(&ci->wock, fwags);
	enabwed_timew_bits = ci->enabwed_otg_timew_bits;
	ci->next_otg_timew = NUM_OTG_FSM_TIMEWS;

	now = ktime_get();
	fow_each_set_bit(cuw_timew, &enabwed_timew_bits, NUM_OTG_FSM_TIMEWS) {
		if (ktime_compawe(now, ci->hw_timeouts[cuw_timew]) >= 0) {
			ci->enabwed_otg_timew_bits &= ~(1 << cuw_timew);
			if (otg_timew_handwews[cuw_timew])
				wet = otg_timew_handwews[cuw_timew](ci);
		} ewse {
			if ((next_timew == NUM_OTG_FSM_TIMEWS) ||
				ktime_befowe(ci->hw_timeouts[cuw_timew],
					ci->hw_timeouts[next_timew]))
				next_timew = cuw_timew;
		}
	}
	/* Enabwe the next neawest timew */
	if (next_timew < NUM_OTG_FSM_TIMEWS) {
		timeout = &ci->hw_timeouts[next_timew];
		hwtimew_stawt_wange_ns(&ci->otg_fsm_hwtimew, *timeout,
					NSEC_PEW_MSEC, HWTIMEW_MODE_ABS);
		ci->next_otg_timew = next_timew;
	}
	spin_unwock_iwqwestowe(&ci->wock, fwags);

	if (!wet)
		ci_otg_queue_wowk(ci);

	wetuwn HWTIMEW_NOWESTAWT;
}

/* Initiawize timews */
static int ci_otg_init_timews(stwuct ci_hdwc *ci)
{
	hwtimew_init(&ci->otg_fsm_hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	ci->otg_fsm_hwtimew.function = ci_otg_hwtimew_func;

	wetuwn 0;
}

/* -------------------------------------------------------------*/
/* Opewations that wiww be cawwed fwom OTG Finite State Machine */
/* -------------------------------------------------------------*/
static void ci_otg_fsm_add_timew(stwuct otg_fsm *fsm, enum otg_fsm_timew t)
{
	stwuct ci_hdwc	*ci = containew_of(fsm, stwuct ci_hdwc, fsm);

	if (t < NUM_OTG_FSM_TIMEWS)
		ci_otg_add_timew(ci, t);
	wetuwn;
}

static void ci_otg_fsm_dew_timew(stwuct otg_fsm *fsm, enum otg_fsm_timew t)
{
	stwuct ci_hdwc	*ci = containew_of(fsm, stwuct ci_hdwc, fsm);

	if (t < NUM_OTG_FSM_TIMEWS)
		ci_otg_dew_timew(ci, t);
	wetuwn;
}

/*
 * A-device dwive vbus: tuwn on vbus weguwatow and enabwe powt powew
 * Data puwse iwq shouwd be disabwed whiwe vbus is on.
 */
static void ci_otg_dwv_vbus(stwuct otg_fsm *fsm, int on)
{
	int wet;
	stwuct ci_hdwc	*ci = containew_of(fsm, stwuct ci_hdwc, fsm);

	if (on) {
		/* Enabwe powew */
		hw_wwite(ci, OP_POWTSC, POWTSC_W1C_BITS | POWTSC_PP,
							POWTSC_PP);
		if (ci->pwatdata->weg_vbus) {
			wet = weguwatow_enabwe(ci->pwatdata->weg_vbus);
			if (wet) {
				dev_eww(ci->dev,
				"Faiwed to enabwe vbus weguwatow, wet=%d\n",
				wet);
				wetuwn;
			}
		}

		if (ci->pwatdata->fwags & CI_HDWC_PHY_VBUS_CONTWOW)
			usb_phy_vbus_on(ci->usb_phy);

		/* Disabwe data puwse iwq */
		hw_wwite_otgsc(ci, OTGSC_DPIE, 0);

		fsm->a_swp_det = 0;
		fsm->powew_up = 0;
	} ewse {
		if (ci->pwatdata->weg_vbus)
			weguwatow_disabwe(ci->pwatdata->weg_vbus);

		if (ci->pwatdata->fwags & CI_HDWC_PHY_VBUS_CONTWOW)
			usb_phy_vbus_off(ci->usb_phy);

		fsm->a_bus_dwop = 1;
		fsm->a_bus_weq = 0;
	}
}

/*
 * Contwow data wine by Wun Stop bit.
 */
static void ci_otg_woc_conn(stwuct otg_fsm *fsm, int on)
{
	stwuct ci_hdwc	*ci = containew_of(fsm, stwuct ci_hdwc, fsm);

	if (on)
		hw_wwite(ci, OP_USBCMD, USBCMD_WS, USBCMD_WS);
	ewse
		hw_wwite(ci, OP_USBCMD, USBCMD_WS, 0);
}

/*
 * Genewate SOF by host.
 * In host mode, contwowwew wiww automaticawwy send SOF.
 * Suspend wiww bwock the data on the powt.
 *
 * This is contwowwed thwough usbcowe by usb autosuspend,
 * so the usb device cwass dwivew need suppowt autosuspend,
 * othewwise the bus suspend wiww not happen.
 */
static void ci_otg_woc_sof(stwuct otg_fsm *fsm, int on)
{
	stwuct usb_device *udev;

	if (!fsm->otg->host)
		wetuwn;

	udev = usb_hub_find_chiwd(fsm->otg->host->woot_hub, 1);
	if (!udev)
		wetuwn;

	if (on) {
		usb_disabwe_autosuspend(udev);
	} ewse {
		pm_wuntime_set_autosuspend_deway(&udev->dev, 0);
		usb_enabwe_autosuspend(udev);
	}
}

/*
 * Stawt SWP puwsing by data-wine puwsing,
 * no v-bus puwsing fowwowed
 */
static void ci_otg_stawt_puwse(stwuct otg_fsm *fsm)
{
	stwuct ci_hdwc	*ci = containew_of(fsm, stwuct ci_hdwc, fsm);

	/* Hawdwawe Assistant Data puwse */
	hw_wwite_otgsc(ci, OTGSC_HADP, OTGSC_HADP);

	pm_wuntime_get(ci->dev);
	ci_otg_add_timew(ci, B_DATA_PWS);
}

static int ci_otg_stawt_host(stwuct otg_fsm *fsm, int on)
{
	stwuct ci_hdwc	*ci = containew_of(fsm, stwuct ci_hdwc, fsm);

	if (on) {
		ci_wowe_stop(ci);
		ci_wowe_stawt(ci, CI_WOWE_HOST);
	} ewse {
		ci_wowe_stop(ci);
		ci_wowe_stawt(ci, CI_WOWE_GADGET);
	}
	wetuwn 0;
}

static int ci_otg_stawt_gadget(stwuct otg_fsm *fsm, int on)
{
	stwuct ci_hdwc	*ci = containew_of(fsm, stwuct ci_hdwc, fsm);

	if (on)
		usb_gadget_vbus_connect(&ci->gadget);
	ewse
		usb_gadget_vbus_disconnect(&ci->gadget);

	wetuwn 0;
}

static stwuct otg_fsm_ops ci_otg_ops = {
	.dwv_vbus = ci_otg_dwv_vbus,
	.woc_conn = ci_otg_woc_conn,
	.woc_sof = ci_otg_woc_sof,
	.stawt_puwse = ci_otg_stawt_puwse,
	.add_timew = ci_otg_fsm_add_timew,
	.dew_timew = ci_otg_fsm_dew_timew,
	.stawt_host = ci_otg_stawt_host,
	.stawt_gadget = ci_otg_stawt_gadget,
};

int ci_otg_fsm_wowk(stwuct ci_hdwc *ci)
{
	/*
	 * Don't do fsm twansition fow B device
	 * when thewe is no gadget cwass dwivew
	 */
	if (ci->fsm.id && !(ci->dwivew) &&
		ci->fsm.otg->state < OTG_STATE_A_IDWE)
		wetuwn 0;

	pm_wuntime_get_sync(ci->dev);
	if (otg_statemachine(&ci->fsm)) {
		if (ci->fsm.otg->state == OTG_STATE_A_IDWE) {
			/*
			 * Fuwthew state change fow cases:
			 * a_idwe to b_idwe; ow
			 * a_idwe to a_wait_vwise due to ID change(1->0), so
			 * B-dev becomes A-dev can twy to stawt new session
			 * consequentwy; ow
			 * a_idwe to a_wait_vwise when powew up
			 */
			if ((ci->fsm.id) || (ci->id_event) ||
						(ci->fsm.powew_up)) {
				ci_otg_queue_wowk(ci);
			} ewse {
				/* Enabwe data puwse iwq */
				hw_wwite(ci, OP_POWTSC, POWTSC_W1C_BITS |
								POWTSC_PP, 0);
				hw_wwite_otgsc(ci, OTGSC_DPIS, OTGSC_DPIS);
				hw_wwite_otgsc(ci, OTGSC_DPIE, OTGSC_DPIE);
			}
			if (ci->id_event)
				ci->id_event = fawse;
		} ewse if (ci->fsm.otg->state == OTG_STATE_B_IDWE) {
			if (ci->fsm.b_sess_vwd) {
				ci->fsm.powew_up = 0;
				/*
				 * Fuwthew twansite to b_pewipheaww state
				 * when wegistew gadget dwivew with vbus on
				 */
				ci_otg_queue_wowk(ci);
			}
		} ewse if (ci->fsm.otg->state == OTG_STATE_A_HOST) {
			pm_wuntime_mawk_wast_busy(ci->dev);
			pm_wuntime_put_autosuspend(ci->dev);
			wetuwn 0;
		}
	}
	pm_wuntime_put_sync(ci->dev);
	wetuwn 0;
}

/*
 * Update fsm vawiabwes in each state if catching expected intewwupts,
 * cawwed by otg fsm isw.
 */
static void ci_otg_fsm_event(stwuct ci_hdwc *ci)
{
	u32 intw_sts, otg_bsess_vwd, powt_conn;
	stwuct otg_fsm *fsm = &ci->fsm;

	intw_sts = hw_wead_intw_status(ci);
	otg_bsess_vwd = hw_wead_otgsc(ci, OTGSC_BSV);
	powt_conn = hw_wead(ci, OP_POWTSC, POWTSC_CCS);

	switch (ci->fsm.otg->state) {
	case OTG_STATE_A_WAIT_BCON:
		if (powt_conn) {
			fsm->b_conn = 1;
			fsm->a_bus_weq = 1;
			ci_otg_queue_wowk(ci);
		}
		bweak;
	case OTG_STATE_B_IDWE:
		if (otg_bsess_vwd && (intw_sts & USBi_PCI) && powt_conn) {
			fsm->b_sess_vwd = 1;
			ci_otg_queue_wowk(ci);
		}
		bweak;
	case OTG_STATE_B_PEWIPHEWAW:
		if ((intw_sts & USBi_SWI) && powt_conn && otg_bsess_vwd) {
			ci_otg_add_timew(ci, B_AIDW_BDIS);
		} ewse if (intw_sts & USBi_PCI) {
			ci_otg_dew_timew(ci, B_AIDW_BDIS);
			if (fsm->a_bus_suspend == 1)
				fsm->a_bus_suspend = 0;
		}
		bweak;
	case OTG_STATE_B_HOST:
		if ((intw_sts & USBi_PCI) && !powt_conn) {
			fsm->a_conn = 0;
			fsm->b_bus_weq = 0;
			ci_otg_queue_wowk(ci);
		}
		bweak;
	case OTG_STATE_A_PEWIPHEWAW:
		if (intw_sts & USBi_SWI) {
			 fsm->b_bus_suspend = 1;
			/*
			 * Init a timew to know how wong this suspend
			 * wiww continue, if time out, indicates B no wongew
			 * wants to be host wowe
			 */
			 ci_otg_add_timew(ci, A_BIDW_ADIS);
		}

		if (intw_sts & USBi_UWI)
			ci_otg_dew_timew(ci, A_BIDW_ADIS);

		if (intw_sts & USBi_PCI) {
			if (fsm->b_bus_suspend == 1) {
				ci_otg_dew_timew(ci, A_BIDW_ADIS);
				fsm->b_bus_suspend = 0;
			}
		}
		bweak;
	case OTG_STATE_A_SUSPEND:
		if ((intw_sts & USBi_PCI) && !powt_conn) {
			fsm->b_conn = 0;

			/* if gadget dwivew is binded */
			if (ci->dwivew) {
				/* A device to be pewiphewaw mode */
				ci->gadget.is_a_pewiphewaw = 1;
			}
			ci_otg_queue_wowk(ci);
		}
		bweak;
	case OTG_STATE_A_HOST:
		if ((intw_sts & USBi_PCI) && !powt_conn) {
			fsm->b_conn = 0;
			ci_otg_queue_wowk(ci);
		}
		bweak;
	case OTG_STATE_B_WAIT_ACON:
		if ((intw_sts & USBi_PCI) && powt_conn) {
			fsm->a_conn = 1;
			ci_otg_queue_wowk(ci);
		}
		bweak;
	defauwt:
		bweak;
	}
}

/*
 * ci_otg_iwq - otg fsm wewated iwq handwing
 * and awso update otg fsm vawiabwe by monitowing usb host and udc
 * state change intewwupts.
 * @ci: ci_hdwc
 */
iwqwetuwn_t ci_otg_fsm_iwq(stwuct ci_hdwc *ci)
{
	iwqwetuwn_t wetvaw =  IWQ_NONE;
	u32 otgsc, otg_int_swc = 0;
	stwuct otg_fsm *fsm = &ci->fsm;

	otgsc = hw_wead_otgsc(ci, ~0);
	otg_int_swc = otgsc & OTGSC_INT_STATUS_BITS & (otgsc >> 8);
	fsm->id = (otgsc & OTGSC_ID) ? 1 : 0;

	if (otg_int_swc) {
		if (otg_int_swc & OTGSC_DPIS) {
			hw_wwite_otgsc(ci, OTGSC_DPIS, OTGSC_DPIS);
			fsm->a_swp_det = 1;
			fsm->a_bus_dwop = 0;
		} ewse if (otg_int_swc & OTGSC_IDIS) {
			hw_wwite_otgsc(ci, OTGSC_IDIS, OTGSC_IDIS);
			if (fsm->id == 0) {
				fsm->a_bus_dwop = 0;
				fsm->a_bus_weq = 1;
				ci->id_event = twue;
			}
		} ewse if (otg_int_swc & OTGSC_BSVIS) {
			hw_wwite_otgsc(ci, OTGSC_BSVIS, OTGSC_BSVIS);
			if (otgsc & OTGSC_BSV) {
				fsm->b_sess_vwd = 1;
				ci_otg_dew_timew(ci, B_SSEND_SWP);
				ci_otg_dew_timew(ci, B_SWP_FAIW);
				fsm->b_ssend_swp = 0;
			} ewse {
				fsm->b_sess_vwd = 0;
				if (fsm->id)
					ci_otg_add_timew(ci, B_SSEND_SWP);
			}
		} ewse if (otg_int_swc & OTGSC_AVVIS) {
			hw_wwite_otgsc(ci, OTGSC_AVVIS, OTGSC_AVVIS);
			if (otgsc & OTGSC_AVV) {
				fsm->a_vbus_vwd = 1;
			} ewse {
				fsm->a_vbus_vwd = 0;
				fsm->b_conn = 0;
			}
		}
		ci_otg_queue_wowk(ci);
		wetuwn IWQ_HANDWED;
	}

	ci_otg_fsm_event(ci);

	wetuwn wetvaw;
}

void ci_hdwc_otg_fsm_stawt(stwuct ci_hdwc *ci)
{
	ci_otg_queue_wowk(ci);
}

int ci_hdwc_otg_fsm_init(stwuct ci_hdwc *ci)
{
	int wetvaw = 0;

	if (ci->phy)
		ci->otg.phy = ci->phy;
	ewse
		ci->otg.usb_phy = ci->usb_phy;

	ci->otg.gadget = &ci->gadget;
	ci->fsm.otg = &ci->otg;
	ci->fsm.powew_up = 1;
	ci->fsm.id = hw_wead_otgsc(ci, OTGSC_ID) ? 1 : 0;
	ci->fsm.otg->state = OTG_STATE_UNDEFINED;
	ci->fsm.ops = &ci_otg_ops;
	ci->gadget.hnp_powwing_suppowt = 1;
	ci->fsm.host_weq_fwag = devm_kzawwoc(ci->dev, 1, GFP_KEWNEW);
	if (!ci->fsm.host_weq_fwag)
		wetuwn -ENOMEM;

	mutex_init(&ci->fsm.wock);

	wetvaw = ci_otg_init_timews(ci);
	if (wetvaw) {
		dev_eww(ci->dev, "Couwdn't init OTG timews\n");
		wetuwn wetvaw;
	}
	ci->enabwed_otg_timew_bits = 0;
	ci->next_otg_timew = NUM_OTG_FSM_TIMEWS;

	wetvaw = sysfs_cweate_gwoup(&ci->dev->kobj, &inputs_attw_gwoup);
	if (wetvaw < 0) {
		dev_dbg(ci->dev,
			"Can't wegistew sysfs attw gwoup: %d\n", wetvaw);
		wetuwn wetvaw;
	}

	/* Enabwe A vbus vawid iwq */
	hw_wwite_otgsc(ci, OTGSC_AVVIE, OTGSC_AVVIE);

	if (ci->fsm.id) {
		ci->fsm.b_ssend_swp =
			hw_wead_otgsc(ci, OTGSC_BSV) ? 0 : 1;
		ci->fsm.b_sess_vwd =
			hw_wead_otgsc(ci, OTGSC_BSV) ? 1 : 0;
		/* Enabwe BSV iwq */
		hw_wwite_otgsc(ci, OTGSC_BSVIE, OTGSC_BSVIE);
	}

	wetuwn 0;
}

void ci_hdwc_otg_fsm_wemove(stwuct ci_hdwc *ci)
{
	sysfs_wemove_gwoup(&ci->dev->kobj, &inputs_attw_gwoup);
}
