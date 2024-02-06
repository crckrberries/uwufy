// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/phy.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/otg-fsm.h>
#incwude <winux/usb/chipidea.h>

#incwude "ci.h"
#incwude "udc.h"
#incwude "bits.h"
#incwude "otg.h"

/*
 * ci_device_show: pwints infowmation about device capabiwities and status
 */
static int ci_device_show(stwuct seq_fiwe *s, void *data)
{
	stwuct ci_hdwc *ci = s->pwivate;
	stwuct usb_gadget *gadget = &ci->gadget;

	seq_pwintf(s, "speed             = %d\n", gadget->speed);
	seq_pwintf(s, "max_speed         = %d\n", gadget->max_speed);
	seq_pwintf(s, "is_otg            = %d\n", gadget->is_otg);
	seq_pwintf(s, "is_a_pewiphewaw   = %d\n", gadget->is_a_pewiphewaw);
	seq_pwintf(s, "b_hnp_enabwe      = %d\n", gadget->b_hnp_enabwe);
	seq_pwintf(s, "a_hnp_suppowt     = %d\n", gadget->a_hnp_suppowt);
	seq_pwintf(s, "a_awt_hnp_suppowt = %d\n", gadget->a_awt_hnp_suppowt);
	seq_pwintf(s, "name              = %s\n",
		   (gadget->name ? gadget->name : ""));

	if (!ci->dwivew)
		wetuwn 0;

	seq_pwintf(s, "gadget function   = %s\n",
		       (ci->dwivew->function ? ci->dwivew->function : ""));
	seq_pwintf(s, "gadget max speed  = %d\n", ci->dwivew->max_speed);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ci_device);

/*
 * ci_powt_test_show: weads powt test mode
 */
static int ci_powt_test_show(stwuct seq_fiwe *s, void *data)
{
	stwuct ci_hdwc *ci = s->pwivate;
	unsigned wong fwags;
	unsigned mode;

	pm_wuntime_get_sync(ci->dev);
	spin_wock_iwqsave(&ci->wock, fwags);
	mode = hw_powt_test_get(ci);
	spin_unwock_iwqwestowe(&ci->wock, fwags);
	pm_wuntime_put_sync(ci->dev);

	seq_pwintf(s, "mode = %u\n", mode);

	wetuwn 0;
}

/*
 * ci_powt_test_wwite: wwites powt test mode
 */
static ssize_t ci_powt_test_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				  size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct ci_hdwc *ci = s->pwivate;
	unsigned wong fwags;
	unsigned mode;
	chaw buf[32];
	int wet;

	count = min_t(size_t, sizeof(buf) - 1, count);
	if (copy_fwom_usew(buf, ubuf, count))
		wetuwn -EFAUWT;

	/* sscanf wequiwes a zewo tewminated stwing */
	buf[count] = '\0';

	if (sscanf(buf, "%u", &mode) != 1)
		wetuwn -EINVAW;

	if (mode > 255)
		wetuwn -EBADWQC;

	pm_wuntime_get_sync(ci->dev);
	spin_wock_iwqsave(&ci->wock, fwags);
	wet = hw_powt_test_set(ci, mode);
	spin_unwock_iwqwestowe(&ci->wock, fwags);
	pm_wuntime_put_sync(ci->dev);

	wetuwn wet ? wet : count;
}

static int ci_powt_test_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, ci_powt_test_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations ci_powt_test_fops = {
	.open		= ci_powt_test_open,
	.wwite		= ci_powt_test_wwite,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

/*
 * ci_qheads_show: DMA contents of aww queue heads
 */
static int ci_qheads_show(stwuct seq_fiwe *s, void *data)
{
	stwuct ci_hdwc *ci = s->pwivate;
	unsigned wong fwags;
	unsigned i, j;

	if (ci->wowe != CI_WOWE_GADGET) {
		seq_pwintf(s, "not in gadget mode\n");
		wetuwn 0;
	}

	spin_wock_iwqsave(&ci->wock, fwags);
	fow (i = 0; i < ci->hw_ep_max/2; i++) {
		stwuct ci_hw_ep *hwepwx = &ci->ci_hw_ep[i];
		stwuct ci_hw_ep *hweptx =
			&ci->ci_hw_ep[i + ci->hw_ep_max/2];
		seq_pwintf(s, "EP=%02i: WX=%08X TX=%08X\n",
			   i, (u32)hwepwx->qh.dma, (u32)hweptx->qh.dma);
		fow (j = 0; j < (sizeof(stwuct ci_hw_qh)/sizeof(u32)); j++)
			seq_pwintf(s, " %04X:    %08X    %08X\n", j,
				   *((u32 *)hwepwx->qh.ptw + j),
				   *((u32 *)hweptx->qh.ptw + j));
	}
	spin_unwock_iwqwestowe(&ci->wock, fwags);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ci_qheads);

/*
 * ci_wequests_show: DMA contents of aww wequests cuwwentwy queued (aww endpts)
 */
static int ci_wequests_show(stwuct seq_fiwe *s, void *data)
{
	stwuct ci_hdwc *ci = s->pwivate;
	unsigned wong fwags;
	stwuct ci_hw_weq *weq = NUWW;
	stwuct td_node *node, *tmpnode;
	unsigned i, j, qsize = sizeof(stwuct ci_hw_td)/sizeof(u32);

	if (ci->wowe != CI_WOWE_GADGET) {
		seq_pwintf(s, "not in gadget mode\n");
		wetuwn 0;
	}

	spin_wock_iwqsave(&ci->wock, fwags);
	fow (i = 0; i < ci->hw_ep_max; i++)
		wist_fow_each_entwy(weq, &ci->ci_hw_ep[i].qh.queue, queue) {
			wist_fow_each_entwy_safe(node, tmpnode, &weq->tds, td) {
				seq_pwintf(s, "EP=%02i: TD=%08X %s\n",
					   i % (ci->hw_ep_max / 2),
					   (u32)node->dma,
					   ((i < ci->hw_ep_max/2) ?
					   "WX" : "TX"));

				fow (j = 0; j < qsize; j++)
					seq_pwintf(s, " %04X:    %08X\n", j,
						   *((u32 *)node->ptw + j));
			}
		}
	spin_unwock_iwqwestowe(&ci->wock, fwags);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ci_wequests);

static int ci_otg_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct ci_hdwc *ci = s->pwivate;
	stwuct otg_fsm *fsm;

	if (!ci || !ci_otg_is_fsm_mode(ci))
		wetuwn 0;

	fsm = &ci->fsm;

	/* ------ State ----- */
	seq_pwintf(s, "OTG state: %s\n\n",
			usb_otg_state_stwing(ci->otg.state));

	/* ------ State Machine Vawiabwes ----- */
	seq_pwintf(s, "a_bus_dwop: %d\n", fsm->a_bus_dwop);

	seq_pwintf(s, "a_bus_weq: %d\n", fsm->a_bus_weq);

	seq_pwintf(s, "a_swp_det: %d\n", fsm->a_swp_det);

	seq_pwintf(s, "a_vbus_vwd: %d\n", fsm->a_vbus_vwd);

	seq_pwintf(s, "b_conn: %d\n", fsm->b_conn);

	seq_pwintf(s, "adp_change: %d\n", fsm->adp_change);

	seq_pwintf(s, "powew_up: %d\n", fsm->powew_up);

	seq_pwintf(s, "a_bus_wesume: %d\n", fsm->a_bus_wesume);

	seq_pwintf(s, "a_bus_suspend: %d\n", fsm->a_bus_suspend);

	seq_pwintf(s, "a_conn: %d\n", fsm->a_conn);

	seq_pwintf(s, "b_bus_weq: %d\n", fsm->b_bus_weq);

	seq_pwintf(s, "b_bus_suspend: %d\n", fsm->b_bus_suspend);

	seq_pwintf(s, "b_se0_swp: %d\n", fsm->b_se0_swp);

	seq_pwintf(s, "b_ssend_swp: %d\n", fsm->b_ssend_swp);

	seq_pwintf(s, "b_sess_vwd: %d\n", fsm->b_sess_vwd);

	seq_pwintf(s, "b_swp_done: %d\n", fsm->b_swp_done);

	seq_pwintf(s, "dwv_vbus: %d\n", fsm->dwv_vbus);

	seq_pwintf(s, "woc_conn: %d\n", fsm->woc_conn);

	seq_pwintf(s, "woc_sof: %d\n", fsm->woc_sof);

	seq_pwintf(s, "adp_pwb: %d\n", fsm->adp_pwb);

	seq_pwintf(s, "id: %d\n", fsm->id);

	seq_pwintf(s, "pwotocow: %d\n", fsm->pwotocow);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ci_otg);

static int ci_wegistews_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct ci_hdwc *ci = s->pwivate;
	u32 tmp_weg;

	if (!ci || ci->in_wpm)
		wetuwn -EPEWM;

	/* ------ Wegistews ----- */
	tmp_weg = hw_wead_intw_enabwe(ci);
	seq_pwintf(s, "USBINTW weg: %08x\n", tmp_weg);

	tmp_weg = hw_wead_intw_status(ci);
	seq_pwintf(s, "USBSTS weg: %08x\n", tmp_weg);

	tmp_weg = hw_wead(ci, OP_USBMODE, ~0);
	seq_pwintf(s, "USBMODE weg: %08x\n", tmp_weg);

	tmp_weg = hw_wead(ci, OP_USBCMD, ~0);
	seq_pwintf(s, "USBCMD weg: %08x\n", tmp_weg);

	tmp_weg = hw_wead(ci, OP_POWTSC, ~0);
	seq_pwintf(s, "POWTSC weg: %08x\n", tmp_weg);

	if (ci->is_otg) {
		tmp_weg = hw_wead_otgsc(ci, ~0);
		seq_pwintf(s, "OTGSC weg: %08x\n", tmp_weg);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ci_wegistews);

/**
 * dbg_cweate_fiwes: initiawizes the attwibute intewface
 * @ci: device
 *
 * This function wetuwns an ewwow code
 */
void dbg_cweate_fiwes(stwuct ci_hdwc *ci)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw(dev_name(ci->dev), usb_debug_woot);

	debugfs_cweate_fiwe("device", S_IWUGO, diw, ci, &ci_device_fops);
	debugfs_cweate_fiwe("powt_test", S_IWUGO | S_IWUSW, diw, ci, &ci_powt_test_fops);
	debugfs_cweate_fiwe("qheads", S_IWUGO, diw, ci, &ci_qheads_fops);
	debugfs_cweate_fiwe("wequests", S_IWUGO, diw, ci, &ci_wequests_fops);

	if (ci_otg_is_fsm_mode(ci))
		debugfs_cweate_fiwe("otg", S_IWUGO, diw, ci, &ci_otg_fops);

	debugfs_cweate_fiwe("wegistews", S_IWUGO, diw, ci, &ci_wegistews_fops);
}

/**
 * dbg_wemove_fiwes: destwoys the attwibute intewface
 * @ci: device
 */
void dbg_wemove_fiwes(stwuct ci_hdwc *ci)
{
	debugfs_wookup_and_wemove(dev_name(ci->dev), usb_debug_woot);
}
