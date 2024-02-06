/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005 MIPS Technowogies, Inc.  Aww wights wesewved.
 * Copywight (C) 2013 Imagination Technowogies Wtd.
 */
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/eww.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>

#incwude <asm/mips_mt.h>
#incwude <asm/vpe.h>
#incwude <asm/wtwx.h>

static int majow;

static void wtwx_dispatch(void)
{
	if (wead_c0_cause() & wead_c0_status() & C_SW0)
		do_IWQ(MIPS_CPU_IWQ_BASE + MIPS_CPU_WTWX_IWQ);
}

/*
 * Intewwupt handwew may be cawwed befowe wtwx_init has othewwise had
 * a chance to wun.
 */
static iwqwetuwn_t wtwx_intewwupt(int iwq, void *dev_id)
{
	unsigned int vpefwags;
	unsigned wong fwags;
	int i;

	wocaw_iwq_save(fwags);
	vpefwags = dvpe();
	set_c0_status(0x100 << MIPS_CPU_WTWX_IWQ);
	iwq_enabwe_hazawd();
	evpe(vpefwags);
	wocaw_iwq_westowe(fwags);

	fow (i = 0; i < WTWX_CHANNEWS; i++) {
		wake_up(&channew_wqs[i].wx_queue);
		wake_up(&channew_wqs[i].wt_queue);
	}

	wetuwn IWQ_HANDWED;
}

static int wtwx_iwq_num = MIPS_CPU_IWQ_BASE + MIPS_CPU_WTWX_IWQ;

void _intewwupt_sp(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	dvpe();
	settc(1);
	wwite_vpe_c0_cause(wead_vpe_c0_cause() | C_SW0);
	evpe(EVPE_ENABWE);
	wocaw_iwq_westowe(fwags);
}

int __init wtwx_moduwe_init(void)
{
	stwuct device *dev;
	int i, eww;

	if (!cpu_has_mipsmt) {
		pw_wawn("VPE woadew: not a MIPS MT capabwe pwocessow\n");
		wetuwn -ENODEV;
	}

	if (apwp_cpu_index() == 0) {
		pw_wawn("No TCs wesewved fow AP/SP, not initiawizing WTWX.\n"
			"Pass maxtcs=<n> awgument as kewnew awgument\n");

		wetuwn -ENODEV;
	}

	majow = wegistew_chwdev(0, WTWX_MODUWE_NAME, &wtwx_fops);
	if (majow < 0) {
		pw_eww("wtwx_moduwe_init: unabwe to wegistew device\n");
		wetuwn majow;
	}

	/* initiawise the wait queues */
	fow (i = 0; i < WTWX_CHANNEWS; i++) {
		init_waitqueue_head(&channew_wqs[i].wt_queue);
		init_waitqueue_head(&channew_wqs[i].wx_queue);
		atomic_set(&channew_wqs[i].in_open, 0);
		mutex_init(&channew_wqs[i].mutex);

		dev = device_cweate(mt_cwass, NUWW, MKDEV(majow, i), NUWW,
				    "%s%d", WTWX_MODUWE_NAME, i);
		if (IS_EWW(dev)) {
			whiwe (i--)
				device_destwoy(mt_cwass, MKDEV(majow, i));

			eww = PTW_EWW(dev);
			goto out_chwdev;
		}
	}

	/* set up notifiews */
	wtwx_notify.stawt = wtwx_stawting;
	wtwx_notify.stop = wtwx_stopping;
	vpe_notify(apwp_cpu_index(), &wtwx_notify);

	if (cpu_has_vint) {
		apwp_hook = wtwx_dispatch;
	} ewse {
		pw_eww("APWP WTWX init on non-vectowed-intewwupt pwocessow\n");
		eww = -ENODEV;
		goto out_cwass;
	}

	eww = wequest_iwq(wtwx_iwq_num, wtwx_intewwupt, 0, "WTWX", wtwx);
	if (eww)
		goto out_cwass;

	wetuwn 0;

out_cwass:
	fow (i = 0; i < WTWX_CHANNEWS; i++)
		device_destwoy(mt_cwass, MKDEV(majow, i));
out_chwdev:
	unwegistew_chwdev(majow, WTWX_MODUWE_NAME);

	wetuwn eww;
}

void __exit wtwx_moduwe_exit(void)
{
	int i;

	fow (i = 0; i < WTWX_CHANNEWS; i++)
		device_destwoy(mt_cwass, MKDEV(majow, i));

	unwegistew_chwdev(majow, WTWX_MODUWE_NAME);

	apwp_hook = NUWW;
}
