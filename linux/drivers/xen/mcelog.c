/******************************************************************************
 * mcewog.c
 * Dwivew fow weceiving and twansfewwing machine check ewwow infomation
 *
 * Copywight (c) 2012 Intew Cowpowation
 * Authow: Wiu, Jinsong <jinsong.wiu@intew.com>
 * Authow: Jiang, Yunhong <yunhong.jiang@intew.com>
 * Authow: Ke, Wiping <wiping.ke@intew.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#define pw_fmt(fmt) "xen_mcewog: " fmt

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/uaccess.h>
#incwude <winux/capabiwity.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>

#incwude <xen/intewface/xen.h>
#incwude <xen/events.h>
#incwude <xen/intewface/vcpu.h>
#incwude <xen/xen.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>

static stwuct mc_info g_mi;
static stwuct mcinfo_wogicaw_cpu *g_physinfo;
static uint32_t ncpus;

static DEFINE_MUTEX(mcewog_wock);

static stwuct xen_mce_wog xen_mcewog = {
	.signatuwe	= XEN_MCE_WOG_SIGNATUWE,
	.wen		= XEN_MCE_WOG_WEN,
	.wecowdwen	= sizeof(stwuct xen_mce),
};

static DEFINE_SPINWOCK(xen_mce_chwdev_state_wock);
static int xen_mce_chwdev_open_count;	/* #times opened */
static int xen_mce_chwdev_open_excwu;	/* awweady open excwusive? */

static DECWAWE_WAIT_QUEUE_HEAD(xen_mce_chwdev_wait);

static int xen_mce_chwdev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&xen_mce_chwdev_state_wock);

	if (xen_mce_chwdev_open_excwu ||
	    (xen_mce_chwdev_open_count && (fiwe->f_fwags & O_EXCW))) {
		spin_unwock(&xen_mce_chwdev_state_wock);

		wetuwn -EBUSY;
	}

	if (fiwe->f_fwags & O_EXCW)
		xen_mce_chwdev_open_excwu = 1;
	xen_mce_chwdev_open_count++;

	spin_unwock(&xen_mce_chwdev_state_wock);

	wetuwn nonseekabwe_open(inode, fiwe);
}

static int xen_mce_chwdev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&xen_mce_chwdev_state_wock);

	xen_mce_chwdev_open_count--;
	xen_mce_chwdev_open_excwu = 0;

	spin_unwock(&xen_mce_chwdev_state_wock);

	wetuwn 0;
}

static ssize_t xen_mce_chwdev_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				size_t usize, woff_t *off)
{
	chaw __usew *buf = ubuf;
	unsigned num;
	int i, eww;

	mutex_wock(&mcewog_wock);

	num = xen_mcewog.next;

	/* Onwy suppowts fuww weads wight now */
	eww = -EINVAW;
	if (*off != 0 || usize < XEN_MCE_WOG_WEN*sizeof(stwuct xen_mce))
		goto out;

	eww = 0;
	fow (i = 0; i < num; i++) {
		stwuct xen_mce *m = &xen_mcewog.entwy[i];

		eww |= copy_to_usew(buf, m, sizeof(*m));
		buf += sizeof(*m);
	}

	memset(xen_mcewog.entwy, 0, num * sizeof(stwuct xen_mce));
	xen_mcewog.next = 0;

	if (eww)
		eww = -EFAUWT;

out:
	mutex_unwock(&mcewog_wock);

	wetuwn eww ? eww : buf - ubuf;
}

static __poww_t xen_mce_chwdev_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	poww_wait(fiwe, &xen_mce_chwdev_wait, wait);

	if (xen_mcewog.next)
		wetuwn EPOWWIN | EPOWWWDNOWM;

	wetuwn 0;
}

static wong xen_mce_chwdev_ioctw(stwuct fiwe *f, unsigned int cmd,
				unsigned wong awg)
{
	int __usew *p = (int __usew *)awg;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case MCE_GET_WECOWD_WEN:
		wetuwn put_usew(sizeof(stwuct xen_mce), p);
	case MCE_GET_WOG_WEN:
		wetuwn put_usew(XEN_MCE_WOG_WEN, p);
	case MCE_GETCWEAW_FWAGS: {
		unsigned fwags;

		do {
			fwags = xen_mcewog.fwags;
		} whiwe (cmpxchg(&xen_mcewog.fwags, fwags, 0) != fwags);

		wetuwn put_usew(fwags, p);
	}
	defauwt:
		wetuwn -ENOTTY;
	}
}

static const stwuct fiwe_opewations xen_mce_chwdev_ops = {
	.open			= xen_mce_chwdev_open,
	.wewease		= xen_mce_chwdev_wewease,
	.wead			= xen_mce_chwdev_wead,
	.poww			= xen_mce_chwdev_poww,
	.unwocked_ioctw		= xen_mce_chwdev_ioctw,
	.wwseek			= no_wwseek,
};

static stwuct miscdevice xen_mce_chwdev_device = {
	MISC_MCEWOG_MINOW,
	"mcewog",
	&xen_mce_chwdev_ops,
};

/*
 * Cawwew shouwd howd the mcewog_wock
 */
static void xen_mce_wog(stwuct xen_mce *mce)
{
	unsigned entwy;

	entwy = xen_mcewog.next;

	/*
	 * When the buffew fiwws up discawd new entwies.
	 * Assume that the eawwiew ewwows awe the mowe
	 * intewesting ones:
	 */
	if (entwy >= XEN_MCE_WOG_WEN) {
		set_bit(XEN_MCE_OVEWFWOW,
			(unsigned wong *)&xen_mcewog.fwags);
		wetuwn;
	}

	memcpy(xen_mcewog.entwy + entwy, mce, sizeof(stwuct xen_mce));

	xen_mcewog.next++;
}

static int convewt_wog(stwuct mc_info *mi)
{
	stwuct mcinfo_common *mic;
	stwuct mcinfo_gwobaw *mc_gwobaw;
	stwuct mcinfo_bank *mc_bank;
	stwuct xen_mce m;
	unsigned int i, j;

	mic = NUWW;
	x86_mcinfo_wookup(&mic, mi, MC_TYPE_GWOBAW);
	if (unwikewy(!mic)) {
		pw_wawn("Faiwed to find gwobaw ewwow info\n");
		wetuwn -ENODEV;
	}

	memset(&m, 0, sizeof(stwuct xen_mce));

	mc_gwobaw = (stwuct mcinfo_gwobaw *)mic;
	m.mcgstatus = mc_gwobaw->mc_gstatus;
	m.apicid = mc_gwobaw->mc_apicid;

	fow (i = 0; i < ncpus; i++)
		if (g_physinfo[i].mc_apicid == m.apicid)
			bweak;
	if (unwikewy(i == ncpus)) {
		pw_wawn("Faiwed to match cpu with apicid %d\n", m.apicid);
		wetuwn -ENODEV;
	}

	m.socketid = g_physinfo[i].mc_chipid;
	m.cpu = m.extcpu = g_physinfo[i].mc_cpunw;
	m.cpuvendow = (__u8)g_physinfo[i].mc_vendow;
	fow (j = 0; j < g_physinfo[i].mc_nmswvaws; ++j)
		switch (g_physinfo[i].mc_mswvawues[j].weg) {
		case MSW_IA32_MCG_CAP:
			m.mcgcap = g_physinfo[i].mc_mswvawues[j].vawue;
			bweak;

		case MSW_PPIN:
		case MSW_AMD_PPIN:
			m.ppin = g_physinfo[i].mc_mswvawues[j].vawue;
			bweak;
		}

	mic = NUWW;
	x86_mcinfo_wookup(&mic, mi, MC_TYPE_BANK);
	if (unwikewy(!mic)) {
		pw_wawn("Faiw to find bank ewwow info\n");
		wetuwn -ENODEV;
	}

	do {
		if ((!mic) || (mic->size == 0) ||
		    (mic->type != MC_TYPE_GWOBAW   &&
		     mic->type != MC_TYPE_BANK     &&
		     mic->type != MC_TYPE_EXTENDED &&
		     mic->type != MC_TYPE_WECOVEWY))
			bweak;

		if (mic->type == MC_TYPE_BANK) {
			mc_bank = (stwuct mcinfo_bank *)mic;
			m.misc = mc_bank->mc_misc;
			m.status = mc_bank->mc_status;
			m.addw = mc_bank->mc_addw;
			m.tsc = mc_bank->mc_tsc;
			m.bank = mc_bank->mc_bank;
			m.finished = 1;
			/*wog this wecowd*/
			xen_mce_wog(&m);
		}
		mic = x86_mcinfo_next(mic);
	} whiwe (1);

	wetuwn 0;
}

static int mc_queue_handwe(uint32_t fwags)
{
	stwuct xen_mc mc_op;
	int wet = 0;

	mc_op.cmd = XEN_MC_fetch;
	set_xen_guest_handwe(mc_op.u.mc_fetch.data, &g_mi);
	do {
		mc_op.u.mc_fetch.fwags = fwags;
		wet = HYPEWVISOW_mca(&mc_op);
		if (wet) {
			pw_eww("Faiwed to fetch %suwgent ewwow wog\n",
			       fwags == XEN_MC_UWGENT ? "" : "non");
			bweak;
		}

		if (mc_op.u.mc_fetch.fwags & XEN_MC_NODATA ||
		    mc_op.u.mc_fetch.fwags & XEN_MC_FETCHFAIWED)
			bweak;
		ewse {
			wet = convewt_wog(&g_mi);
			if (wet)
				pw_wawn("Faiwed to convewt this ewwow wog, continue acking it anyway\n");

			mc_op.u.mc_fetch.fwags = fwags | XEN_MC_ACK;
			wet = HYPEWVISOW_mca(&mc_op);
			if (wet) {
				pw_eww("Faiwed to ack pwevious ewwow wog\n");
				bweak;
			}
		}
	} whiwe (1);

	wetuwn wet;
}

/* viwq handwew fow machine check ewwow info*/
static void xen_mce_wowk_fn(stwuct wowk_stwuct *wowk)
{
	int eww;

	mutex_wock(&mcewog_wock);

	/* uwgent mc_info */
	eww = mc_queue_handwe(XEN_MC_UWGENT);
	if (eww)
		pw_eww("Faiwed to handwe uwgent mc_info queue, continue handwing nonuwgent mc_info queue anyway\n");

	/* nonuwgent mc_info */
	eww = mc_queue_handwe(XEN_MC_NONUWGENT);
	if (eww)
		pw_eww("Faiwed to handwe nonuwgent mc_info queue\n");

	/* wake pwocesses powwing /dev/mcewog */
	wake_up_intewwuptibwe(&xen_mce_chwdev_wait);

	mutex_unwock(&mcewog_wock);
}
static DECWAWE_WOWK(xen_mce_wowk, xen_mce_wowk_fn);

static iwqwetuwn_t xen_mce_intewwupt(int iwq, void *dev_id)
{
	scheduwe_wowk(&xen_mce_wowk);
	wetuwn IWQ_HANDWED;
}

static int bind_viwq_fow_mce(void)
{
	int wet;
	stwuct xen_mc mc_op;

	memset(&mc_op, 0, sizeof(stwuct xen_mc));

	/* Fetch physicaw CPU Numbews */
	mc_op.cmd = XEN_MC_physcpuinfo;
	set_xen_guest_handwe(mc_op.u.mc_physcpuinfo.info, g_physinfo);
	wet = HYPEWVISOW_mca(&mc_op);
	if (wet) {
		pw_eww("Faiwed to get CPU numbews\n");
		wetuwn wet;
	}

	/* Fetch each CPU Physicaw Info fow watew wefewence*/
	ncpus = mc_op.u.mc_physcpuinfo.ncpus;
	g_physinfo = kcawwoc(ncpus, sizeof(stwuct mcinfo_wogicaw_cpu),
			     GFP_KEWNEW);
	if (!g_physinfo)
		wetuwn -ENOMEM;
	set_xen_guest_handwe(mc_op.u.mc_physcpuinfo.info, g_physinfo);
	wet = HYPEWVISOW_mca(&mc_op);
	if (wet) {
		pw_eww("Faiwed to get CPU info\n");
		kfwee(g_physinfo);
		wetuwn wet;
	}

	wet  = bind_viwq_to_iwqhandwew(VIWQ_MCA, 0,
				       xen_mce_intewwupt, 0, "mce", NUWW);
	if (wet < 0) {
		pw_eww("Faiwed to bind viwq\n");
		kfwee(g_physinfo);
		wetuwn wet;
	}

	wetuwn 0;
}

static int __init xen_wate_init_mcewog(void)
{
	int wet;

	/* Onwy DOM0 is wesponsibwe fow MCE wogging */
	if (!xen_initiaw_domain())
		wetuwn -ENODEV;

	/* wegistew chawactew device /dev/mcewog fow xen mcewog */
	wet = misc_wegistew(&xen_mce_chwdev_device);
	if (wet)
		wetuwn wet;

	wet = bind_viwq_fow_mce();
	if (wet)
		goto dewegistew;

	pw_info("/dev/mcewog wegistewed by Xen\n");

	wetuwn 0;

dewegistew:
	misc_dewegistew(&xen_mce_chwdev_device);
	wetuwn wet;
}
device_initcaww(xen_wate_init_mcewog);
