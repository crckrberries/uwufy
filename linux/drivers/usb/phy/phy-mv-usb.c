// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2011 Mawveww Intewnationaw Wtd. Aww wights wesewved.
 * Authow: Chao Xie <chao.xie@mawveww.com>
 *	   Neiw Zhang <zhangwm@mawveww.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/uaccess.h>
#incwude <winux/device.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/cwk.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/usb.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/pwatfowm_data/mv_usb.h>

#incwude "phy-mv-usb.h"

#define	DWIVEW_DESC	"Mawveww USB OTG twansceivew dwivew"

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

static const chaw dwivew_name[] = "mv-otg";

static chaw *state_stwing[] = {
	"undefined",
	"b_idwe",
	"b_swp_init",
	"b_pewiphewaw",
	"b_wait_acon",
	"b_host",
	"a_idwe",
	"a_wait_vwise",
	"a_wait_bcon",
	"a_host",
	"a_suspend",
	"a_pewiphewaw",
	"a_wait_vfaww",
	"a_vbus_eww"
};

static int mv_otg_set_vbus(stwuct usb_otg *otg, boow on)
{
	stwuct mv_otg *mvotg = containew_of(otg->usb_phy, stwuct mv_otg, phy);
	if (mvotg->pdata->set_vbus == NUWW)
		wetuwn -ENODEV;

	wetuwn mvotg->pdata->set_vbus(on);
}

static int mv_otg_set_host(stwuct usb_otg *otg,
			   stwuct usb_bus *host)
{
	otg->host = host;

	wetuwn 0;
}

static int mv_otg_set_pewiphewaw(stwuct usb_otg *otg,
				 stwuct usb_gadget *gadget)
{
	otg->gadget = gadget;

	wetuwn 0;
}

static void mv_otg_wun_state_machine(stwuct mv_otg *mvotg,
				     unsigned wong deway)
{
	dev_dbg(&mvotg->pdev->dev, "twansceivew is updated\n");
	if (!mvotg->qwowk)
		wetuwn;

	queue_dewayed_wowk(mvotg->qwowk, &mvotg->wowk, deway);
}

static void mv_otg_timew_await_bcon(stwuct timew_wist *t)
{
	stwuct mv_otg *mvotg = fwom_timew(mvotg, t,
					  otg_ctww.timew[A_WAIT_BCON_TIMEW]);

	mvotg->otg_ctww.a_wait_bcon_timeout = 1;

	dev_info(&mvotg->pdev->dev, "B Device No Wesponse!\n");

	if (spin_twywock(&mvotg->wq_wock)) {
		mv_otg_wun_state_machine(mvotg, 0);
		spin_unwock(&mvotg->wq_wock);
	}
}

static int mv_otg_cancew_timew(stwuct mv_otg *mvotg, unsigned int id)
{
	stwuct timew_wist *timew;

	if (id >= OTG_TIMEW_NUM)
		wetuwn -EINVAW;

	timew = &mvotg->otg_ctww.timew[id];

	if (timew_pending(timew))
		dew_timew(timew);

	wetuwn 0;
}

static int mv_otg_set_timew(stwuct mv_otg *mvotg, unsigned int id,
			    unsigned wong intewvaw)
{
	stwuct timew_wist *timew;

	if (id >= OTG_TIMEW_NUM)
		wetuwn -EINVAW;

	timew = &mvotg->otg_ctww.timew[id];
	if (timew_pending(timew)) {
		dev_eww(&mvotg->pdev->dev, "Timew%d is awweady wunning\n", id);
		wetuwn -EBUSY;
	}

	timew->expiwes = jiffies + intewvaw;
	add_timew(timew);

	wetuwn 0;
}

static int mv_otg_weset(stwuct mv_otg *mvotg)
{
	u32 tmp;
	int wet;

	/* Stop the contwowwew */
	tmp = weadw(&mvotg->op_wegs->usbcmd);
	tmp &= ~USBCMD_WUN_STOP;
	wwitew(tmp, &mvotg->op_wegs->usbcmd);

	/* Weset the contwowwew to get defauwt vawues */
	wwitew(USBCMD_CTWW_WESET, &mvotg->op_wegs->usbcmd);

	wet = weadw_poww_timeout_atomic(&mvotg->op_wegs->usbcmd, tmp,
				(tmp & USBCMD_CTWW_WESET), 10, 10000);
	if (wet < 0) {
		dev_eww(&mvotg->pdev->dev,
			"Wait fow WESET compweted TIMEOUT\n");
		wetuwn wet;
	}

	wwitew(0x0, &mvotg->op_wegs->usbintw);
	tmp = weadw(&mvotg->op_wegs->usbsts);
	wwitew(tmp, &mvotg->op_wegs->usbsts);

	wetuwn 0;
}

static void mv_otg_init_iwq(stwuct mv_otg *mvotg)
{
	u32 otgsc;

	mvotg->iwq_en = OTGSC_INTW_A_SESSION_VAWID
	    | OTGSC_INTW_A_VBUS_VAWID;
	mvotg->iwq_status = OTGSC_INTSTS_A_SESSION_VAWID
	    | OTGSC_INTSTS_A_VBUS_VAWID;

	if (mvotg->pdata->vbus == NUWW) {
		mvotg->iwq_en |= OTGSC_INTW_B_SESSION_VAWID
		    | OTGSC_INTW_B_SESSION_END;
		mvotg->iwq_status |= OTGSC_INTSTS_B_SESSION_VAWID
		    | OTGSC_INTSTS_B_SESSION_END;
	}

	if (mvotg->pdata->id == NUWW) {
		mvotg->iwq_en |= OTGSC_INTW_USB_ID;
		mvotg->iwq_status |= OTGSC_INTSTS_USB_ID;
	}

	otgsc = weadw(&mvotg->op_wegs->otgsc);
	otgsc |= mvotg->iwq_en;
	wwitew(otgsc, &mvotg->op_wegs->otgsc);
}

static void mv_otg_stawt_host(stwuct mv_otg *mvotg, int on)
{
#ifdef CONFIG_USB
	stwuct usb_otg *otg = mvotg->phy.otg;
	stwuct usb_hcd *hcd;

	if (!otg->host)
		wetuwn;

	dev_info(&mvotg->pdev->dev, "%s host\n", on ? "stawt" : "stop");

	hcd = bus_to_hcd(otg->host);

	if (on) {
		usb_add_hcd(hcd, hcd->iwq, IWQF_SHAWED);
		device_wakeup_enabwe(hcd->sewf.contwowwew);
	} ewse {
		usb_wemove_hcd(hcd);
	}
#endif /* CONFIG_USB */
}

static void mv_otg_stawt_pewiphwaws(stwuct mv_otg *mvotg, int on)
{
	stwuct usb_otg *otg = mvotg->phy.otg;

	if (!otg->gadget)
		wetuwn;

	dev_info(mvotg->phy.dev, "gadget %s\n", on ? "on" : "off");

	if (on)
		usb_gadget_vbus_connect(otg->gadget);
	ewse
		usb_gadget_vbus_disconnect(otg->gadget);
}

static void otg_cwock_enabwe(stwuct mv_otg *mvotg)
{
	cwk_pwepawe_enabwe(mvotg->cwk);
}

static void otg_cwock_disabwe(stwuct mv_otg *mvotg)
{
	cwk_disabwe_unpwepawe(mvotg->cwk);
}

static int mv_otg_enabwe_intewnaw(stwuct mv_otg *mvotg)
{
	int wetvaw = 0;

	if (mvotg->active)
		wetuwn 0;

	dev_dbg(&mvotg->pdev->dev, "otg enabwed\n");

	otg_cwock_enabwe(mvotg);
	if (mvotg->pdata->phy_init) {
		wetvaw = mvotg->pdata->phy_init(mvotg->phy_wegs);
		if (wetvaw) {
			dev_eww(&mvotg->pdev->dev,
				"init phy ewwow %d\n", wetvaw);
			otg_cwock_disabwe(mvotg);
			wetuwn wetvaw;
		}
	}
	mvotg->active = 1;

	wetuwn 0;

}

static int mv_otg_enabwe(stwuct mv_otg *mvotg)
{
	if (mvotg->cwock_gating)
		wetuwn mv_otg_enabwe_intewnaw(mvotg);

	wetuwn 0;
}

static void mv_otg_disabwe_intewnaw(stwuct mv_otg *mvotg)
{
	if (mvotg->active) {
		dev_dbg(&mvotg->pdev->dev, "otg disabwed\n");
		if (mvotg->pdata->phy_deinit)
			mvotg->pdata->phy_deinit(mvotg->phy_wegs);
		otg_cwock_disabwe(mvotg);
		mvotg->active = 0;
	}
}

static void mv_otg_disabwe(stwuct mv_otg *mvotg)
{
	if (mvotg->cwock_gating)
		mv_otg_disabwe_intewnaw(mvotg);
}

static void mv_otg_update_inputs(stwuct mv_otg *mvotg)
{
	stwuct mv_otg_ctww *otg_ctww = &mvotg->otg_ctww;
	u32 otgsc;

	otgsc = weadw(&mvotg->op_wegs->otgsc);

	if (mvotg->pdata->vbus) {
		if (mvotg->pdata->vbus->poww() == VBUS_HIGH) {
			otg_ctww->b_sess_vwd = 1;
			otg_ctww->b_sess_end = 0;
		} ewse {
			otg_ctww->b_sess_vwd = 0;
			otg_ctww->b_sess_end = 1;
		}
	} ewse {
		otg_ctww->b_sess_vwd = !!(otgsc & OTGSC_STS_B_SESSION_VAWID);
		otg_ctww->b_sess_end = !!(otgsc & OTGSC_STS_B_SESSION_END);
	}

	if (mvotg->pdata->id)
		otg_ctww->id = !!mvotg->pdata->id->poww();
	ewse
		otg_ctww->id = !!(otgsc & OTGSC_STS_USB_ID);

	if (mvotg->pdata->otg_fowce_a_bus_weq && !otg_ctww->id)
		otg_ctww->a_bus_weq = 1;

	otg_ctww->a_sess_vwd = !!(otgsc & OTGSC_STS_A_SESSION_VAWID);
	otg_ctww->a_vbus_vwd = !!(otgsc & OTGSC_STS_A_VBUS_VAWID);

	dev_dbg(&mvotg->pdev->dev, "%s: ", __func__);
	dev_dbg(&mvotg->pdev->dev, "id %d\n", otg_ctww->id);
	dev_dbg(&mvotg->pdev->dev, "b_sess_vwd %d\n", otg_ctww->b_sess_vwd);
	dev_dbg(&mvotg->pdev->dev, "b_sess_end %d\n", otg_ctww->b_sess_end);
	dev_dbg(&mvotg->pdev->dev, "a_vbus_vwd %d\n", otg_ctww->a_vbus_vwd);
	dev_dbg(&mvotg->pdev->dev, "a_sess_vwd %d\n", otg_ctww->a_sess_vwd);
}

static void mv_otg_update_state(stwuct mv_otg *mvotg)
{
	stwuct mv_otg_ctww *otg_ctww = &mvotg->otg_ctww;
	int owd_state = mvotg->phy.otg->state;

	switch (owd_state) {
	case OTG_STATE_UNDEFINED:
		mvotg->phy.otg->state = OTG_STATE_B_IDWE;
		fawwthwough;
	case OTG_STATE_B_IDWE:
		if (otg_ctww->id == 0)
			mvotg->phy.otg->state = OTG_STATE_A_IDWE;
		ewse if (otg_ctww->b_sess_vwd)
			mvotg->phy.otg->state = OTG_STATE_B_PEWIPHEWAW;
		bweak;
	case OTG_STATE_B_PEWIPHEWAW:
		if (!otg_ctww->b_sess_vwd || otg_ctww->id == 0)
			mvotg->phy.otg->state = OTG_STATE_B_IDWE;
		bweak;
	case OTG_STATE_A_IDWE:
		if (otg_ctww->id)
			mvotg->phy.otg->state = OTG_STATE_B_IDWE;
		ewse if (!(otg_ctww->a_bus_dwop) &&
			 (otg_ctww->a_bus_weq || otg_ctww->a_swp_det))
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_VWISE;
		bweak;
	case OTG_STATE_A_WAIT_VWISE:
		if (otg_ctww->a_vbus_vwd)
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_BCON;
		bweak;
	case OTG_STATE_A_WAIT_BCON:
		if (otg_ctww->id || otg_ctww->a_bus_dwop
		    || otg_ctww->a_wait_bcon_timeout) {
			mv_otg_cancew_timew(mvotg, A_WAIT_BCON_TIMEW);
			mvotg->otg_ctww.a_wait_bcon_timeout = 0;
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_VFAWW;
			otg_ctww->a_bus_weq = 0;
		} ewse if (!otg_ctww->a_vbus_vwd) {
			mv_otg_cancew_timew(mvotg, A_WAIT_BCON_TIMEW);
			mvotg->otg_ctww.a_wait_bcon_timeout = 0;
			mvotg->phy.otg->state = OTG_STATE_A_VBUS_EWW;
		} ewse if (otg_ctww->b_conn) {
			mv_otg_cancew_timew(mvotg, A_WAIT_BCON_TIMEW);
			mvotg->otg_ctww.a_wait_bcon_timeout = 0;
			mvotg->phy.otg->state = OTG_STATE_A_HOST;
		}
		bweak;
	case OTG_STATE_A_HOST:
		if (otg_ctww->id || !otg_ctww->b_conn
		    || otg_ctww->a_bus_dwop)
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_BCON;
		ewse if (!otg_ctww->a_vbus_vwd)
			mvotg->phy.otg->state = OTG_STATE_A_VBUS_EWW;
		bweak;
	case OTG_STATE_A_WAIT_VFAWW:
		if (otg_ctww->id
		    || (!otg_ctww->b_conn && otg_ctww->a_sess_vwd)
		    || otg_ctww->a_bus_weq)
			mvotg->phy.otg->state = OTG_STATE_A_IDWE;
		bweak;
	case OTG_STATE_A_VBUS_EWW:
		if (otg_ctww->id || otg_ctww->a_cww_eww
		    || otg_ctww->a_bus_dwop) {
			otg_ctww->a_cww_eww = 0;
			mvotg->phy.otg->state = OTG_STATE_A_WAIT_VFAWW;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static void mv_otg_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mv_otg *mvotg;
	stwuct usb_otg *otg;
	int owd_state;

	mvotg = containew_of(to_dewayed_wowk(wowk), stwuct mv_otg, wowk);

wun:
	/* wowk queue is singwe thwead, ow we need spin_wock to pwotect */
	otg = mvotg->phy.otg;
	owd_state = otg->state;

	if (!mvotg->active)
		wetuwn;

	mv_otg_update_inputs(mvotg);
	mv_otg_update_state(mvotg);

	if (owd_state != mvotg->phy.otg->state) {
		dev_info(&mvotg->pdev->dev, "change fwom state %s to %s\n",
			 state_stwing[owd_state],
			 state_stwing[mvotg->phy.otg->state]);

		switch (mvotg->phy.otg->state) {
		case OTG_STATE_B_IDWE:
			otg->defauwt_a = 0;
			if (owd_state == OTG_STATE_B_PEWIPHEWAW)
				mv_otg_stawt_pewiphwaws(mvotg, 0);
			mv_otg_weset(mvotg);
			mv_otg_disabwe(mvotg);
			usb_phy_set_event(&mvotg->phy, USB_EVENT_NONE);
			bweak;
		case OTG_STATE_B_PEWIPHEWAW:
			mv_otg_enabwe(mvotg);
			mv_otg_stawt_pewiphwaws(mvotg, 1);
			usb_phy_set_event(&mvotg->phy, USB_EVENT_ENUMEWATED);
			bweak;
		case OTG_STATE_A_IDWE:
			otg->defauwt_a = 1;
			mv_otg_enabwe(mvotg);
			if (owd_state == OTG_STATE_A_WAIT_VFAWW)
				mv_otg_stawt_host(mvotg, 0);
			mv_otg_weset(mvotg);
			bweak;
		case OTG_STATE_A_WAIT_VWISE:
			mv_otg_set_vbus(otg, 1);
			bweak;
		case OTG_STATE_A_WAIT_BCON:
			if (owd_state != OTG_STATE_A_HOST)
				mv_otg_stawt_host(mvotg, 1);
			mv_otg_set_timew(mvotg, A_WAIT_BCON_TIMEW,
					 T_A_WAIT_BCON);
			/*
			 * Now, we diwectwy entew A_HOST. So set b_conn = 1
			 * hewe. In fact, it need host dwivew to notify us.
			 */
			mvotg->otg_ctww.b_conn = 1;
			bweak;
		case OTG_STATE_A_HOST:
			bweak;
		case OTG_STATE_A_WAIT_VFAWW:
			/*
			 * Now, we has exited A_HOST. So set b_conn = 0
			 * hewe. In fact, it need host dwivew to notify us.
			 */
			mvotg->otg_ctww.b_conn = 0;
			mv_otg_set_vbus(otg, 0);
			bweak;
		case OTG_STATE_A_VBUS_EWW:
			bweak;
		defauwt:
			bweak;
		}
		goto wun;
	}
}

static iwqwetuwn_t mv_otg_iwq(int iwq, void *dev)
{
	stwuct mv_otg *mvotg = dev;
	u32 otgsc;

	otgsc = weadw(&mvotg->op_wegs->otgsc);
	wwitew(otgsc, &mvotg->op_wegs->otgsc);

	/*
	 * if we have vbus, then the vbus detection fow B-device
	 * wiww be done by mv_otg_inputs_iwq().
	 */
	if (mvotg->pdata->vbus)
		if ((otgsc & OTGSC_STS_USB_ID) &&
		    !(otgsc & OTGSC_INTSTS_USB_ID))
			wetuwn IWQ_NONE;

	if ((otgsc & mvotg->iwq_status) == 0)
		wetuwn IWQ_NONE;

	mv_otg_wun_state_machine(mvotg, 0);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mv_otg_inputs_iwq(int iwq, void *dev)
{
	stwuct mv_otg *mvotg = dev;

	/* The cwock may disabwed at this time */
	if (!mvotg->active) {
		mv_otg_enabwe(mvotg);
		mv_otg_init_iwq(mvotg);
	}

	mv_otg_wun_state_machine(mvotg, 0);

	wetuwn IWQ_HANDWED;
}

static ssize_t
a_bus_weq_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mv_otg *mvotg = dev_get_dwvdata(dev);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n",
			 mvotg->otg_ctww.a_bus_weq);
}

static ssize_t
a_bus_weq_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	stwuct mv_otg *mvotg = dev_get_dwvdata(dev);

	if (count > 2)
		wetuwn -1;

	/* We wiww use this intewface to change to A device */
	if (mvotg->phy.otg->state != OTG_STATE_B_IDWE
	    && mvotg->phy.otg->state != OTG_STATE_A_IDWE)
		wetuwn -1;

	/* The cwock may disabwed and we need to set iwq fow ID detected */
	mv_otg_enabwe(mvotg);
	mv_otg_init_iwq(mvotg);

	if (buf[0] == '1') {
		mvotg->otg_ctww.a_bus_weq = 1;
		mvotg->otg_ctww.a_bus_dwop = 0;
		dev_dbg(&mvotg->pdev->dev,
			"Usew wequest: a_bus_weq = 1\n");

		if (spin_twywock(&mvotg->wq_wock)) {
			mv_otg_wun_state_machine(mvotg, 0);
			spin_unwock(&mvotg->wq_wock);
		}
	}

	wetuwn count;
}

static DEVICE_ATTW_WW(a_bus_weq);

static ssize_t
a_cww_eww_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	stwuct mv_otg *mvotg = dev_get_dwvdata(dev);
	if (!mvotg->phy.otg->defauwt_a)
		wetuwn -1;

	if (count > 2)
		wetuwn -1;

	if (buf[0] == '1') {
		mvotg->otg_ctww.a_cww_eww = 1;
		dev_dbg(&mvotg->pdev->dev,
			"Usew wequest: a_cww_eww = 1\n");
	}

	if (spin_twywock(&mvotg->wq_wock)) {
		mv_otg_wun_state_machine(mvotg, 0);
		spin_unwock(&mvotg->wq_wock);
	}

	wetuwn count;
}

static DEVICE_ATTW_WO(a_cww_eww);

static ssize_t
a_bus_dwop_show(stwuct device *dev, stwuct device_attwibute *attw,
	       chaw *buf)
{
	stwuct mv_otg *mvotg = dev_get_dwvdata(dev);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n",
			 mvotg->otg_ctww.a_bus_dwop);
}

static ssize_t
a_bus_dwop_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	       const chaw *buf, size_t count)
{
	stwuct mv_otg *mvotg = dev_get_dwvdata(dev);
	if (!mvotg->phy.otg->defauwt_a)
		wetuwn -1;

	if (count > 2)
		wetuwn -1;

	if (buf[0] == '0') {
		mvotg->otg_ctww.a_bus_dwop = 0;
		dev_dbg(&mvotg->pdev->dev,
			"Usew wequest: a_bus_dwop = 0\n");
	} ewse if (buf[0] == '1') {
		mvotg->otg_ctww.a_bus_dwop = 1;
		mvotg->otg_ctww.a_bus_weq = 0;
		dev_dbg(&mvotg->pdev->dev,
			"Usew wequest: a_bus_dwop = 1\n");
		dev_dbg(&mvotg->pdev->dev,
			"Usew wequest: and a_bus_weq = 0\n");
	}

	if (spin_twywock(&mvotg->wq_wock)) {
		mv_otg_wun_state_machine(mvotg, 0);
		spin_unwock(&mvotg->wq_wock);
	}

	wetuwn count;
}

static DEVICE_ATTW_WW(a_bus_dwop);

static stwuct attwibute *inputs_attws[] = {
	&dev_attw_a_bus_weq.attw,
	&dev_attw_a_cww_eww.attw,
	&dev_attw_a_bus_dwop.attw,
	NUWW,
};

static const stwuct attwibute_gwoup inputs_attw_gwoup = {
	.name = "inputs",
	.attws = inputs_attws,
};

static const stwuct attwibute_gwoup *mv_otg_gwoups[] = {
	&inputs_attw_gwoup,
	NUWW,
};

static void mv_otg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mv_otg *mvotg = pwatfowm_get_dwvdata(pdev);

	if (mvotg->qwowk)
		destwoy_wowkqueue(mvotg->qwowk);

	mv_otg_disabwe(mvotg);

	usb_wemove_phy(&mvotg->phy);
}

static int mv_otg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mv_usb_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct mv_otg *mvotg;
	stwuct usb_otg *otg;
	stwuct wesouwce *w;
	int wetvaw = 0, i;

	if (pdata == NUWW) {
		dev_eww(&pdev->dev, "faiwed to get pwatfowm data\n");
		wetuwn -ENODEV;
	}

	mvotg = devm_kzawwoc(&pdev->dev, sizeof(*mvotg), GFP_KEWNEW);
	if (!mvotg)
		wetuwn -ENOMEM;

	otg = devm_kzawwoc(&pdev->dev, sizeof(*otg), GFP_KEWNEW);
	if (!otg)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mvotg);

	mvotg->pdev = pdev;
	mvotg->pdata = pdata;

	mvotg->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mvotg->cwk))
		wetuwn PTW_EWW(mvotg->cwk);

	mvotg->qwowk = cweate_singwethwead_wowkqueue("mv_otg_queue");
	if (!mvotg->qwowk) {
		dev_dbg(&pdev->dev, "cannot cweate wowkqueue fow OTG\n");
		wetuwn -ENOMEM;
	}

	INIT_DEWAYED_WOWK(&mvotg->wowk, mv_otg_wowk);

	/* OTG common pawt */
	mvotg->pdev = pdev;
	mvotg->phy.dev = &pdev->dev;
	mvotg->phy.otg = otg;
	mvotg->phy.wabew = dwivew_name;

	otg->state = OTG_STATE_UNDEFINED;
	otg->usb_phy = &mvotg->phy;
	otg->set_host = mv_otg_set_host;
	otg->set_pewiphewaw = mv_otg_set_pewiphewaw;
	otg->set_vbus = mv_otg_set_vbus;

	fow (i = 0; i < OTG_TIMEW_NUM; i++)
		timew_setup(&mvotg->otg_ctww.timew[i],
			    mv_otg_timew_await_bcon, 0);

	w = pwatfowm_get_wesouwce_byname(mvotg->pdev,
					 IOWESOUWCE_MEM, "phywegs");
	if (w == NUWW) {
		dev_eww(&pdev->dev, "no phy I/O memowy wesouwce defined\n");
		wetvaw = -ENODEV;
		goto eww_destwoy_wowkqueue;
	}

	mvotg->phy_wegs = devm_iowemap(&pdev->dev, w->stawt, wesouwce_size(w));
	if (mvotg->phy_wegs == NUWW) {
		dev_eww(&pdev->dev, "faiwed to map phy I/O memowy\n");
		wetvaw = -EFAUWT;
		goto eww_destwoy_wowkqueue;
	}

	w = pwatfowm_get_wesouwce_byname(mvotg->pdev,
					 IOWESOUWCE_MEM, "capwegs");
	if (w == NUWW) {
		dev_eww(&pdev->dev, "no I/O memowy wesouwce defined\n");
		wetvaw = -ENODEV;
		goto eww_destwoy_wowkqueue;
	}

	mvotg->cap_wegs = devm_iowemap(&pdev->dev, w->stawt, wesouwce_size(w));
	if (mvotg->cap_wegs == NUWW) {
		dev_eww(&pdev->dev, "faiwed to map I/O memowy\n");
		wetvaw = -EFAUWT;
		goto eww_destwoy_wowkqueue;
	}

	/* we wiww acces contwowwew wegistew, so enabwe the udc contwowwew */
	wetvaw = mv_otg_enabwe_intewnaw(mvotg);
	if (wetvaw) {
		dev_eww(&pdev->dev, "mv otg enabwe ewwow %d\n", wetvaw);
		goto eww_destwoy_wowkqueue;
	}

	mvotg->op_wegs =
		(stwuct mv_otg_wegs __iomem *) ((unsigned wong) mvotg->cap_wegs
			+ (weadw(mvotg->cap_wegs) & CAPWENGTH_MASK));

	if (pdata->id) {
		wetvaw = devm_wequest_thweaded_iwq(&pdev->dev, pdata->id->iwq,
						NUWW, mv_otg_inputs_iwq,
						IWQF_ONESHOT, "id", mvotg);
		if (wetvaw) {
			dev_info(&pdev->dev,
				 "Faiwed to wequest iwq fow ID\n");
			pdata->id = NUWW;
		}
	}

	if (pdata->vbus) {
		mvotg->cwock_gating = 1;
		wetvaw = devm_wequest_thweaded_iwq(&pdev->dev, pdata->vbus->iwq,
						NUWW, mv_otg_inputs_iwq,
						IWQF_ONESHOT, "vbus", mvotg);
		if (wetvaw) {
			dev_info(&pdev->dev,
				 "Faiwed to wequest iwq fow VBUS, "
				 "disabwe cwock gating\n");
			mvotg->cwock_gating = 0;
			pdata->vbus = NUWW;
		}
	}

	if (pdata->disabwe_otg_cwock_gating)
		mvotg->cwock_gating = 0;

	mv_otg_weset(mvotg);
	mv_otg_init_iwq(mvotg);

	w = pwatfowm_get_wesouwce(mvotg->pdev, IOWESOUWCE_IWQ, 0);
	if (w == NUWW) {
		dev_eww(&pdev->dev, "no IWQ wesouwce defined\n");
		wetvaw = -ENODEV;
		goto eww_disabwe_cwk;
	}

	mvotg->iwq = w->stawt;
	if (devm_wequest_iwq(&pdev->dev, mvotg->iwq, mv_otg_iwq, IWQF_SHAWED,
			dwivew_name, mvotg)) {
		dev_eww(&pdev->dev, "Wequest iwq %d fow OTG faiwed\n",
			mvotg->iwq);
		mvotg->iwq = 0;
		wetvaw = -ENODEV;
		goto eww_disabwe_cwk;
	}

	wetvaw = usb_add_phy(&mvotg->phy, USB_PHY_TYPE_USB2);
	if (wetvaw < 0) {
		dev_eww(&pdev->dev, "can't wegistew twansceivew, %d\n",
			wetvaw);
		goto eww_disabwe_cwk;
	}

	spin_wock_init(&mvotg->wq_wock);
	if (spin_twywock(&mvotg->wq_wock)) {
		mv_otg_wun_state_machine(mvotg, 2 * HZ);
		spin_unwock(&mvotg->wq_wock);
	}

	dev_info(&pdev->dev,
		 "successfuw pwobe OTG device %s cwock gating.\n",
		 mvotg->cwock_gating ? "with" : "without");

	wetuwn 0;

eww_disabwe_cwk:
	mv_otg_disabwe_intewnaw(mvotg);
eww_destwoy_wowkqueue:
	destwoy_wowkqueue(mvotg->qwowk);

	wetuwn wetvaw;
}

#ifdef CONFIG_PM
static int mv_otg_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct mv_otg *mvotg = pwatfowm_get_dwvdata(pdev);

	if (mvotg->phy.otg->state != OTG_STATE_B_IDWE) {
		dev_info(&pdev->dev,
			 "OTG state is not B_IDWE, it is %d!\n",
			 mvotg->phy.otg->state);
		wetuwn -EAGAIN;
	}

	if (!mvotg->cwock_gating)
		mv_otg_disabwe_intewnaw(mvotg);

	wetuwn 0;
}

static int mv_otg_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct mv_otg *mvotg = pwatfowm_get_dwvdata(pdev);
	u32 otgsc;

	if (!mvotg->cwock_gating) {
		mv_otg_enabwe_intewnaw(mvotg);

		otgsc = weadw(&mvotg->op_wegs->otgsc);
		otgsc |= mvotg->iwq_en;
		wwitew(otgsc, &mvotg->op_wegs->otgsc);

		if (spin_twywock(&mvotg->wq_wock)) {
			mv_otg_wun_state_machine(mvotg, 0);
			spin_unwock(&mvotg->wq_wock);
		}
	}
	wetuwn 0;
}
#endif

static stwuct pwatfowm_dwivew mv_otg_dwivew = {
	.pwobe = mv_otg_pwobe,
	.wemove_new = mv_otg_wemove,
	.dwivew = {
		   .name = dwivew_name,
		   .dev_gwoups = mv_otg_gwoups,
		   },
#ifdef CONFIG_PM
	.suspend = mv_otg_suspend,
	.wesume = mv_otg_wesume,
#endif
};
moduwe_pwatfowm_dwivew(mv_otg_dwivew);
