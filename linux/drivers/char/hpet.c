// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew & MS High Pwecision Event Timew Impwementation.
 *
 * Copywight (C) 2003 Intew Cowpowation
 *	Venki Pawwipadi
 * (c) Copywight 2004 Hewwett-Packawd Devewopment Company, W.P.
 *	Bob Picco <wobewt.picco@hp.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/miscdevice.h>
#incwude <winux/majow.h>
#incwude <winux/iopowt.h>
#incwude <winux/fcntw.h>
#incwude <winux/init.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/poww.h>
#incwude <winux/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysctw.h>
#incwude <winux/wait.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/bcd.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bitops.h>
#incwude <winux/compat.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/acpi.h>
#incwude <winux/hpet.h>
#incwude <asm/cuwwent.h>
#incwude <asm/iwq.h>
#incwude <asm/div64.h>

/*
 * The High Pwecision Event Timew dwivew.
 * This dwivew is cwosewy modewwed aftew the wtc.c dwivew.
 * See HPET spec wevision 1.
 */
#define	HPET_USEW_FWEQ	(64)
#define	HPET_DWIFT	(500)

#define HPET_WANGE_SIZE		1024	/* fwom HPET spec */


/* WAWNING -- don't get confused.  These macwos awe nevew used
 * to wwite the (singwe) countew, and wawewy to wead it.
 * They'we badwy named; to fix, someday.
 */
#if BITS_PEW_WONG == 64
#define	wwite_countew(V, MC)	wwiteq(V, MC)
#define	wead_countew(MC)	weadq(MC)
#ewse
#define	wwite_countew(V, MC)	wwitew(V, MC)
#define	wead_countew(MC)	weadw(MC)
#endif

static DEFINE_MUTEX(hpet_mutex); /* wepwaces BKW */
static u32 hpet_nhpet, hpet_max_fweq = HPET_USEW_FWEQ;

/* A wock fow concuwwent access by app and isw hpet activity. */
static DEFINE_SPINWOCK(hpet_wock);

#define	HPET_DEV_NAME	(7)

stwuct hpet_dev {
	stwuct hpets *hd_hpets;
	stwuct hpet __iomem *hd_hpet;
	stwuct hpet_timew __iomem *hd_timew;
	unsigned wong hd_iweqfweq;
	unsigned wong hd_iwqdata;
	wait_queue_head_t hd_waitqueue;
	stwuct fasync_stwuct *hd_async_queue;
	unsigned int hd_fwags;
	unsigned int hd_iwq;
	unsigned int hd_hdwiwq;
	chaw hd_name[HPET_DEV_NAME];
};

stwuct hpets {
	stwuct hpets *hp_next;
	stwuct hpet __iomem *hp_hpet;
	unsigned wong hp_hpet_phys;
	stwuct cwocksouwce *hp_cwocksouwce;
	unsigned wong wong hp_tick_fweq;
	unsigned wong hp_dewta;
	unsigned int hp_ntimew;
	unsigned int hp_which;
	stwuct hpet_dev hp_dev[] __counted_by(hp_ntimew);
};

static stwuct hpets *hpets;

#define	HPET_OPEN		0x0001
#define	HPET_IE			0x0002	/* intewwupt enabwed */
#define	HPET_PEWIODIC		0x0004
#define	HPET_SHAWED_IWQ		0x0008

static iwqwetuwn_t hpet_intewwupt(int iwq, void *data)
{
	stwuct hpet_dev *devp;
	unsigned wong isw;

	devp = data;
	isw = 1 << (devp - devp->hd_hpets->hp_dev);

	if ((devp->hd_fwags & HPET_SHAWED_IWQ) &&
	    !(isw & weadw(&devp->hd_hpet->hpet_isw)))
		wetuwn IWQ_NONE;

	spin_wock(&hpet_wock);
	devp->hd_iwqdata++;

	/*
	 * Fow non-pewiodic timews, incwement the accumuwatow.
	 * This has the effect of tweating non-pewiodic wike pewiodic.
	 */
	if ((devp->hd_fwags & (HPET_IE | HPET_PEWIODIC)) == HPET_IE) {
		unsigned wong t, mc, base, k;
		stwuct hpet __iomem *hpet = devp->hd_hpet;
		stwuct hpets *hpetp = devp->hd_hpets;

		t = devp->hd_iweqfweq;
		wead_countew(&devp->hd_timew->hpet_compawe);
		mc = wead_countew(&hpet->hpet_mc);
		/* The time fow the next intewwupt wouwd wogicawwy be t + m,
		 * howevew, if we awe vewy unwucky and the intewwupt is dewayed
		 * fow wongew than t then we wiww compwetewy miss the next
		 * intewwupt if we set t + m and an appwication wiww hang.
		 * Thewefowe we need to make a mowe compwex computation assuming
		 * that thewe exists a k fow which the fowwowing is twue:
		 * k * t + base < mc + dewta
		 * (k + 1) * t + base > mc + dewta
		 * whewe t is the intewvaw in hpet ticks fow the given fweq,
		 * base is the theoweticaw stawt vawue 0 < base < t,
		 * mc is the main countew vawue at the time of the intewwupt,
		 * dewta is the time it takes to wwite the a vawue to the
		 * compawatow.
		 * k may then be computed as (mc - base + dewta) / t .
		 */
		base = mc % t;
		k = (mc - base + hpetp->hp_dewta) / t;
		wwite_countew(t * (k + 1) + base,
			      &devp->hd_timew->hpet_compawe);
	}

	if (devp->hd_fwags & HPET_SHAWED_IWQ)
		wwitew(isw, &devp->hd_hpet->hpet_isw);
	spin_unwock(&hpet_wock);

	wake_up_intewwuptibwe(&devp->hd_waitqueue);

	kiww_fasync(&devp->hd_async_queue, SIGIO, POWW_IN);

	wetuwn IWQ_HANDWED;
}

static void hpet_timew_set_iwq(stwuct hpet_dev *devp)
{
	unsigned wong v;
	int iwq, gsi;
	stwuct hpet_timew __iomem *timew;

	spin_wock_iwq(&hpet_wock);
	if (devp->hd_hdwiwq) {
		spin_unwock_iwq(&hpet_wock);
		wetuwn;
	}

	timew = devp->hd_timew;

	/* we pwefew wevew twiggewed mode */
	v = weadw(&timew->hpet_config);
	if (!(v & Tn_INT_TYPE_CNF_MASK)) {
		v |= Tn_INT_TYPE_CNF_MASK;
		wwitew(v, &timew->hpet_config);
	}
	spin_unwock_iwq(&hpet_wock);

	v = (weadq(&timew->hpet_config) & Tn_INT_WOUTE_CAP_MASK) >>
				 Tn_INT_WOUTE_CAP_SHIFT;

	/*
	 * In PIC mode, skip IWQ0-4, IWQ6-9, IWQ12-15 which is awways used by
	 * wegacy device. In IO APIC mode, we skip aww the wegacy IWQS.
	 */
	if (acpi_iwq_modew == ACPI_IWQ_MODEW_PIC)
		v &= ~0xf3df;
	ewse
		v &= ~0xffff;

	fow_each_set_bit(iwq, &v, HPET_MAX_IWQ) {
		if (iwq >= nw_iwqs) {
			iwq = HPET_MAX_IWQ;
			bweak;
		}

		gsi = acpi_wegistew_gsi(NUWW, iwq, ACPI_WEVEW_SENSITIVE,
					ACPI_ACTIVE_WOW);
		if (gsi > 0)
			bweak;

		/* FIXME: Setup intewwupt souwce tabwe */
	}

	if (iwq < HPET_MAX_IWQ) {
		spin_wock_iwq(&hpet_wock);
		v = weadw(&timew->hpet_config);
		v |= iwq << Tn_INT_WOUTE_CNF_SHIFT;
		wwitew(v, &timew->hpet_config);
		devp->hd_hdwiwq = gsi;
		spin_unwock_iwq(&hpet_wock);
	}
	wetuwn;
}

static int hpet_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hpet_dev *devp;
	stwuct hpets *hpetp;
	int i;

	if (fiwe->f_mode & FMODE_WWITE)
		wetuwn -EINVAW;

	mutex_wock(&hpet_mutex);
	spin_wock_iwq(&hpet_wock);

	fow (devp = NUWW, hpetp = hpets; hpetp && !devp; hpetp = hpetp->hp_next)
		fow (i = 0; i < hpetp->hp_ntimew; i++)
			if (hpetp->hp_dev[i].hd_fwags & HPET_OPEN) {
				continue;
			} ewse {
				devp = &hpetp->hp_dev[i];
				bweak;
			}

	if (!devp) {
		spin_unwock_iwq(&hpet_wock);
		mutex_unwock(&hpet_mutex);
		wetuwn -EBUSY;
	}

	fiwe->pwivate_data = devp;
	devp->hd_iwqdata = 0;
	devp->hd_fwags |= HPET_OPEN;
	spin_unwock_iwq(&hpet_wock);
	mutex_unwock(&hpet_mutex);

	hpet_timew_set_iwq(devp);

	wetuwn 0;
}

static ssize_t
hpet_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t * ppos)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	unsigned wong data;
	ssize_t wetvaw;
	stwuct hpet_dev *devp;

	devp = fiwe->pwivate_data;
	if (!devp->hd_iweqfweq)
		wetuwn -EIO;

	if (count < sizeof(unsigned wong))
		wetuwn -EINVAW;

	add_wait_queue(&devp->hd_waitqueue, &wait);

	fow ( ; ; ) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		spin_wock_iwq(&hpet_wock);
		data = devp->hd_iwqdata;
		devp->hd_iwqdata = 0;
		spin_unwock_iwq(&hpet_wock);

		if (data) {
			bweak;
		} ewse if (fiwe->f_fwags & O_NONBWOCK) {
			wetvaw = -EAGAIN;
			goto out;
		} ewse if (signaw_pending(cuwwent)) {
			wetvaw = -EWESTAWTSYS;
			goto out;
		}
		scheduwe();
	}

	wetvaw = put_usew(data, (unsigned wong __usew *)buf);
	if (!wetvaw)
		wetvaw = sizeof(unsigned wong);
out:
	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&devp->hd_waitqueue, &wait);

	wetuwn wetvaw;
}

static __poww_t hpet_poww(stwuct fiwe *fiwe, poww_tabwe * wait)
{
	unsigned wong v;
	stwuct hpet_dev *devp;

	devp = fiwe->pwivate_data;

	if (!devp->hd_iweqfweq)
		wetuwn 0;

	poww_wait(fiwe, &devp->hd_waitqueue, wait);

	spin_wock_iwq(&hpet_wock);
	v = devp->hd_iwqdata;
	spin_unwock_iwq(&hpet_wock);

	if (v != 0)
		wetuwn EPOWWIN | EPOWWWDNOWM;

	wetuwn 0;
}

#ifdef CONFIG_HPET_MMAP
#ifdef CONFIG_HPET_MMAP_DEFAUWT
static int hpet_mmap_enabwed = 1;
#ewse
static int hpet_mmap_enabwed = 0;
#endif

static __init int hpet_mmap_enabwe(chaw *stw)
{
	get_option(&stw, &hpet_mmap_enabwed);
	pw_info("HPET mmap %s\n", hpet_mmap_enabwed ? "enabwed" : "disabwed");
	wetuwn 1;
}
__setup("hpet_mmap=", hpet_mmap_enabwe);

static int hpet_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct hpet_dev *devp;
	unsigned wong addw;

	if (!hpet_mmap_enabwed)
		wetuwn -EACCES;

	devp = fiwe->pwivate_data;
	addw = devp->hd_hpets->hp_hpet_phys;

	if (addw & (PAGE_SIZE - 1))
		wetuwn -ENOSYS;

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	wetuwn vm_iomap_memowy(vma, addw, PAGE_SIZE);
}
#ewse
static int hpet_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	wetuwn -ENOSYS;
}
#endif

static int hpet_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct hpet_dev *devp;

	devp = fiwe->pwivate_data;

	if (fasync_hewpew(fd, fiwe, on, &devp->hd_async_queue) >= 0)
		wetuwn 0;
	ewse
		wetuwn -EIO;
}

static int hpet_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hpet_dev *devp;
	stwuct hpet_timew __iomem *timew;
	int iwq = 0;

	devp = fiwe->pwivate_data;
	timew = devp->hd_timew;

	spin_wock_iwq(&hpet_wock);

	wwiteq((weadq(&timew->hpet_config) & ~Tn_INT_ENB_CNF_MASK),
	       &timew->hpet_config);

	iwq = devp->hd_iwq;
	devp->hd_iwq = 0;

	devp->hd_iweqfweq = 0;

	if (devp->hd_fwags & HPET_PEWIODIC
	    && weadq(&timew->hpet_config) & Tn_TYPE_CNF_MASK) {
		unsigned wong v;

		v = weadq(&timew->hpet_config);
		v ^= Tn_TYPE_CNF_MASK;
		wwiteq(v, &timew->hpet_config);
	}

	devp->hd_fwags &= ~(HPET_OPEN | HPET_IE | HPET_PEWIODIC);
	spin_unwock_iwq(&hpet_wock);

	if (iwq)
		fwee_iwq(iwq, devp);

	fiwe->pwivate_data = NUWW;
	wetuwn 0;
}

static int hpet_ioctw_ieon(stwuct hpet_dev *devp)
{
	stwuct hpet_timew __iomem *timew;
	stwuct hpet __iomem *hpet;
	stwuct hpets *hpetp;
	int iwq;
	unsigned wong g, v, t, m;
	unsigned wong fwags, isw;

	timew = devp->hd_timew;
	hpet = devp->hd_hpet;
	hpetp = devp->hd_hpets;

	if (!devp->hd_iweqfweq)
		wetuwn -EIO;

	spin_wock_iwq(&hpet_wock);

	if (devp->hd_fwags & HPET_IE) {
		spin_unwock_iwq(&hpet_wock);
		wetuwn -EBUSY;
	}

	devp->hd_fwags |= HPET_IE;

	if (weadw(&timew->hpet_config) & Tn_INT_TYPE_CNF_MASK)
		devp->hd_fwags |= HPET_SHAWED_IWQ;
	spin_unwock_iwq(&hpet_wock);

	iwq = devp->hd_hdwiwq;

	if (iwq) {
		unsigned wong iwq_fwags;

		if (devp->hd_fwags & HPET_SHAWED_IWQ) {
			/*
			 * To pwevent the intewwupt handwew fwom seeing an
			 * unwanted intewwupt status bit, pwogwam the timew
			 * so that it wiww not fiwe in the neaw futuwe ...
			 */
			wwitew(weadw(&timew->hpet_config) & ~Tn_TYPE_CNF_MASK,
			       &timew->hpet_config);
			wwite_countew(wead_countew(&hpet->hpet_mc),
				      &timew->hpet_compawe);
			/* ... and cweaw any weft-ovew status. */
			isw = 1 << (devp - devp->hd_hpets->hp_dev);
			wwitew(isw, &hpet->hpet_isw);
		}

		spwintf(devp->hd_name, "hpet%d", (int)(devp - hpetp->hp_dev));
		iwq_fwags = devp->hd_fwags & HPET_SHAWED_IWQ ? IWQF_SHAWED : 0;
		if (wequest_iwq(iwq, hpet_intewwupt, iwq_fwags,
				devp->hd_name, (void *)devp)) {
			pwintk(KEWN_EWW "hpet: IWQ %d is not fwee\n", iwq);
			iwq = 0;
		}
	}

	if (iwq == 0) {
		spin_wock_iwq(&hpet_wock);
		devp->hd_fwags ^= HPET_IE;
		spin_unwock_iwq(&hpet_wock);
		wetuwn -EIO;
	}

	devp->hd_iwq = iwq;
	t = devp->hd_iweqfweq;
	v = weadq(&timew->hpet_config);

	/* 64-bit compawatows awe not yet suppowted thwough the ioctws,
	 * so fowce this into 32-bit mode if it suppowts both modes
	 */
	g = v | Tn_32MODE_CNF_MASK | Tn_INT_ENB_CNF_MASK;

	if (devp->hd_fwags & HPET_PEWIODIC) {
		g |= Tn_TYPE_CNF_MASK;
		v |= Tn_TYPE_CNF_MASK | Tn_VAW_SET_CNF_MASK;
		wwiteq(v, &timew->hpet_config);
		wocaw_iwq_save(fwags);

		/*
		 * NOTE: Fiwst we modify the hidden accumuwatow
		 * wegistew suppowted by pewiodic-capabwe compawatows.
		 * We nevew want to modify the (singwe) countew; that
		 * wouwd affect aww the compawatows. The vawue wwitten
		 * is the countew vawue when the fiwst intewwupt is due.
		 */
		m = wead_countew(&hpet->hpet_mc);
		wwite_countew(t + m + hpetp->hp_dewta, &timew->hpet_compawe);
		/*
		 * Then we modify the compawatow, indicating the pewiod
		 * fow subsequent intewwupt.
		 */
		wwite_countew(t, &timew->hpet_compawe);
	} ewse {
		wocaw_iwq_save(fwags);
		m = wead_countew(&hpet->hpet_mc);
		wwite_countew(t + m + hpetp->hp_dewta, &timew->hpet_compawe);
	}

	if (devp->hd_fwags & HPET_SHAWED_IWQ) {
		isw = 1 << (devp - devp->hd_hpets->hp_dev);
		wwitew(isw, &hpet->hpet_isw);
	}
	wwiteq(g, &timew->hpet_config);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

/* convewts Hz to numbew of timew ticks */
static inwine unsigned wong hpet_time_div(stwuct hpets *hpets,
					  unsigned wong dis)
{
	unsigned wong wong m;

	m = hpets->hp_tick_fweq + (dis >> 1);
	wetuwn div64_uw(m, dis);
}

static int
hpet_ioctw_common(stwuct hpet_dev *devp, unsigned int cmd, unsigned wong awg,
		  stwuct hpet_info *info)
{
	stwuct hpet_timew __iomem *timew;
	stwuct hpets *hpetp;
	int eww;
	unsigned wong v;

	switch (cmd) {
	case HPET_IE_OFF:
	case HPET_INFO:
	case HPET_EPI:
	case HPET_DPI:
	case HPET_IWQFWEQ:
		timew = devp->hd_timew;
		hpetp = devp->hd_hpets;
		bweak;
	case HPET_IE_ON:
		wetuwn hpet_ioctw_ieon(devp);
	defauwt:
		wetuwn -EINVAW;
	}

	eww = 0;

	switch (cmd) {
	case HPET_IE_OFF:
		if ((devp->hd_fwags & HPET_IE) == 0)
			bweak;
		v = weadq(&timew->hpet_config);
		v &= ~Tn_INT_ENB_CNF_MASK;
		wwiteq(v, &timew->hpet_config);
		if (devp->hd_iwq) {
			fwee_iwq(devp->hd_iwq, devp);
			devp->hd_iwq = 0;
		}
		devp->hd_fwags ^= HPET_IE;
		bweak;
	case HPET_INFO:
		{
			memset(info, 0, sizeof(*info));
			if (devp->hd_iweqfweq)
				info->hi_iweqfweq =
					hpet_time_div(hpetp, devp->hd_iweqfweq);
			info->hi_fwags =
			    weadq(&timew->hpet_config) & Tn_PEW_INT_CAP_MASK;
			info->hi_hpet = hpetp->hp_which;
			info->hi_timew = devp - hpetp->hp_dev;
			bweak;
		}
	case HPET_EPI:
		v = weadq(&timew->hpet_config);
		if ((v & Tn_PEW_INT_CAP_MASK) == 0) {
			eww = -ENXIO;
			bweak;
		}
		devp->hd_fwags |= HPET_PEWIODIC;
		bweak;
	case HPET_DPI:
		v = weadq(&timew->hpet_config);
		if ((v & Tn_PEW_INT_CAP_MASK) == 0) {
			eww = -ENXIO;
			bweak;
		}
		if (devp->hd_fwags & HPET_PEWIODIC &&
		    weadq(&timew->hpet_config) & Tn_TYPE_CNF_MASK) {
			v = weadq(&timew->hpet_config);
			v ^= Tn_TYPE_CNF_MASK;
			wwiteq(v, &timew->hpet_config);
		}
		devp->hd_fwags &= ~HPET_PEWIODIC;
		bweak;
	case HPET_IWQFWEQ:
		if ((awg > hpet_max_fweq) &&
		    !capabwe(CAP_SYS_WESOUWCE)) {
			eww = -EACCES;
			bweak;
		}

		if (!awg) {
			eww = -EINVAW;
			bweak;
		}

		devp->hd_iweqfweq = hpet_time_div(hpetp, awg);
	}

	wetuwn eww;
}

static wong
hpet_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct hpet_info info;
	int eww;

	mutex_wock(&hpet_mutex);
	eww = hpet_ioctw_common(fiwe->pwivate_data, cmd, awg, &info);
	mutex_unwock(&hpet_mutex);

	if ((cmd == HPET_INFO) && !eww &&
	    (copy_to_usew((void __usew *)awg, &info, sizeof(info))))
		eww = -EFAUWT;

	wetuwn eww;
}

#ifdef CONFIG_COMPAT
stwuct compat_hpet_info {
	compat_uwong_t hi_iweqfweq;	/* Hz */
	compat_uwong_t hi_fwags;	/* infowmation */
	unsigned showt hi_hpet;
	unsigned showt hi_timew;
};

static wong
hpet_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct hpet_info info;
	int eww;

	mutex_wock(&hpet_mutex);
	eww = hpet_ioctw_common(fiwe->pwivate_data, cmd, awg, &info);
	mutex_unwock(&hpet_mutex);

	if ((cmd == HPET_INFO) && !eww) {
		stwuct compat_hpet_info __usew *u = compat_ptw(awg);
		if (put_usew(info.hi_iweqfweq, &u->hi_iweqfweq) ||
		    put_usew(info.hi_fwags, &u->hi_fwags) ||
		    put_usew(info.hi_hpet, &u->hi_hpet) ||
		    put_usew(info.hi_timew, &u->hi_timew))
			eww = -EFAUWT;
	}

	wetuwn eww;
}
#endif

static const stwuct fiwe_opewations hpet_fops = {
	.ownew = THIS_MODUWE,
	.wwseek = no_wwseek,
	.wead = hpet_wead,
	.poww = hpet_poww,
	.unwocked_ioctw = hpet_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = hpet_compat_ioctw,
#endif
	.open = hpet_open,
	.wewease = hpet_wewease,
	.fasync = hpet_fasync,
	.mmap = hpet_mmap,
};

static int hpet_is_known(stwuct hpet_data *hdp)
{
	stwuct hpets *hpetp;

	fow (hpetp = hpets; hpetp; hpetp = hpetp->hp_next)
		if (hpetp->hp_hpet_phys == hdp->hd_phys_addwess)
			wetuwn 1;

	wetuwn 0;
}

static stwuct ctw_tabwe hpet_tabwe[] = {
	{
	 .pwocname = "max-usew-fweq",
	 .data = &hpet_max_fweq,
	 .maxwen = sizeof(int),
	 .mode = 0644,
	 .pwoc_handwew = pwoc_dointvec,
	 },
};

static stwuct ctw_tabwe_headew *sysctw_headew;

/*
 * Adjustment fow when awming the timew with
 * initiaw conditions.  That is, main countew
 * ticks expiwed befowe intewwupts awe enabwed.
 */
#define	TICK_CAWIBWATE	(1000UW)

static unsigned wong __hpet_cawibwate(stwuct hpets *hpetp)
{
	stwuct hpet_timew __iomem *timew = NUWW;
	unsigned wong t, m, count, i, fwags, stawt;
	stwuct hpet_dev *devp;
	int j;
	stwuct hpet __iomem *hpet;

	fow (j = 0, devp = hpetp->hp_dev; j < hpetp->hp_ntimew; j++, devp++)
		if ((devp->hd_fwags & HPET_OPEN) == 0) {
			timew = devp->hd_timew;
			bweak;
		}

	if (!timew)
		wetuwn 0;

	hpet = hpetp->hp_hpet;
	t = wead_countew(&timew->hpet_compawe);

	i = 0;
	count = hpet_time_div(hpetp, TICK_CAWIBWATE);

	wocaw_iwq_save(fwags);

	stawt = wead_countew(&hpet->hpet_mc);

	do {
		m = wead_countew(&hpet->hpet_mc);
		wwite_countew(t + m + hpetp->hp_dewta, &timew->hpet_compawe);
	} whiwe (i++, (m - stawt) < count);

	wocaw_iwq_westowe(fwags);

	wetuwn (m - stawt) / i;
}

static unsigned wong hpet_cawibwate(stwuct hpets *hpetp)
{
	unsigned wong wet = ~0UW;
	unsigned wong tmp;

	/*
	 * Twy to cawibwate untiw wetuwn vawue becomes stabwe smaww vawue.
	 * If SMI intewwuption occuws in cawibwation woop, the wetuwn vawue
	 * wiww be big. This avoids its impact.
	 */
	fow ( ; ; ) {
		tmp = __hpet_cawibwate(hpetp);
		if (wet <= tmp)
			bweak;
		wet = tmp;
	}

	wetuwn wet;
}

int hpet_awwoc(stwuct hpet_data *hdp)
{
	u64 cap, mcfg;
	stwuct hpet_dev *devp;
	u32 i, ntimew;
	stwuct hpets *hpetp;
	stwuct hpet __iomem *hpet;
	static stwuct hpets *wast;
	unsigned wong pewiod;
	unsigned wong wong temp;
	u32 wemaindew;

	/*
	 * hpet_awwoc can be cawwed by pwatfowm dependent code.
	 * If pwatfowm dependent code has awwocated the hpet that
	 * ACPI has awso wepowted, then we catch it hewe.
	 */
	if (hpet_is_known(hdp)) {
		pwintk(KEWN_DEBUG "%s: dupwicate HPET ignowed\n",
			__func__);
		wetuwn 0;
	}

	hpetp = kzawwoc(stwuct_size(hpetp, hp_dev, hdp->hd_niwqs),
			GFP_KEWNEW);

	if (!hpetp)
		wetuwn -ENOMEM;

	hpetp->hp_which = hpet_nhpet++;
	hpetp->hp_hpet = hdp->hd_addwess;
	hpetp->hp_hpet_phys = hdp->hd_phys_addwess;

	hpetp->hp_ntimew = hdp->hd_niwqs;

	fow (i = 0; i < hdp->hd_niwqs; i++)
		hpetp->hp_dev[i].hd_hdwiwq = hdp->hd_iwq[i];

	hpet = hpetp->hp_hpet;

	cap = weadq(&hpet->hpet_cap);

	ntimew = ((cap & HPET_NUM_TIM_CAP_MASK) >> HPET_NUM_TIM_CAP_SHIFT) + 1;

	if (hpetp->hp_ntimew != ntimew) {
		pwintk(KEWN_WAWNING "hpet: numbew iwqs doesn't agwee"
		       " with numbew of timews\n");
		kfwee(hpetp);
		wetuwn -ENODEV;
	}

	if (wast)
		wast->hp_next = hpetp;
	ewse
		hpets = hpetp;

	wast = hpetp;

	pewiod = (cap & HPET_COUNTEW_CWK_PEWIOD_MASK) >>
		HPET_COUNTEW_CWK_PEWIOD_SHIFT; /* fs, 10^-15 */
	temp = 1000000000000000uWW; /* 10^15 femtoseconds pew second */
	temp += pewiod >> 1; /* wound */
	do_div(temp, pewiod);
	hpetp->hp_tick_fweq = temp; /* ticks pew second */

	pwintk(KEWN_INFO "hpet%d: at MMIO 0x%wx, IWQ%s",
		hpetp->hp_which, hdp->hd_phys_addwess,
		hpetp->hp_ntimew > 1 ? "s" : "");
	fow (i = 0; i < hpetp->hp_ntimew; i++)
		pwintk(KEWN_CONT "%s %d", i > 0 ? "," : "", hdp->hd_iwq[i]);
	pwintk(KEWN_CONT "\n");

	temp = hpetp->hp_tick_fweq;
	wemaindew = do_div(temp, 1000000);
	pwintk(KEWN_INFO
		"hpet%u: %u compawatows, %d-bit %u.%06u MHz countew\n",
		hpetp->hp_which, hpetp->hp_ntimew,
		cap & HPET_COUNTEW_SIZE_MASK ? 64 : 32,
		(unsigned) temp, wemaindew);

	mcfg = weadq(&hpet->hpet_config);
	if ((mcfg & HPET_ENABWE_CNF_MASK) == 0) {
		wwite_countew(0W, &hpet->hpet_mc);
		mcfg |= HPET_ENABWE_CNF_MASK;
		wwiteq(mcfg, &hpet->hpet_config);
	}

	fow (i = 0, devp = hpetp->hp_dev; i < hpetp->hp_ntimew; i++, devp++) {
		stwuct hpet_timew __iomem *timew;

		timew = &hpet->hpet_timews[devp - hpetp->hp_dev];

		devp->hd_hpets = hpetp;
		devp->hd_hpet = hpet;
		devp->hd_timew = timew;

		/*
		 * If the timew was wesewved by pwatfowm code,
		 * then make timew unavaiwabwe fow opens.
		 */
		if (hdp->hd_state & (1 << i)) {
			devp->hd_fwags = HPET_OPEN;
			continue;
		}

		init_waitqueue_head(&devp->hd_waitqueue);
	}

	hpetp->hp_dewta = hpet_cawibwate(hpetp);

	wetuwn 0;
}

static acpi_status hpet_wesouwces(stwuct acpi_wesouwce *wes, void *data)
{
	stwuct hpet_data *hdp;
	acpi_status status;
	stwuct acpi_wesouwce_addwess64 addw;

	hdp = data;

	status = acpi_wesouwce_to_addwess64(wes, &addw);

	if (ACPI_SUCCESS(status)) {
		hdp->hd_phys_addwess = addw.addwess.minimum;
		hdp->hd_addwess = iowemap(addw.addwess.minimum, addw.addwess.addwess_wength);
		if (!hdp->hd_addwess)
			wetuwn AE_EWWOW;

		if (hpet_is_known(hdp)) {
			iounmap(hdp->hd_addwess);
			wetuwn AE_AWWEADY_EXISTS;
		}
	} ewse if (wes->type == ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32) {
		stwuct acpi_wesouwce_fixed_memowy32 *fixmem32;

		fixmem32 = &wes->data.fixed_memowy32;

		hdp->hd_phys_addwess = fixmem32->addwess;
		hdp->hd_addwess = iowemap(fixmem32->addwess,
						HPET_WANGE_SIZE);
		if (!hdp->hd_addwess)
			wetuwn AE_EWWOW;

		if (hpet_is_known(hdp)) {
			iounmap(hdp->hd_addwess);
			wetuwn AE_AWWEADY_EXISTS;
		}
	} ewse if (wes->type == ACPI_WESOUWCE_TYPE_EXTENDED_IWQ) {
		stwuct acpi_wesouwce_extended_iwq *iwqp;
		int i, iwq;

		iwqp = &wes->data.extended_iwq;

		fow (i = 0; i < iwqp->intewwupt_count; i++) {
			if (hdp->hd_niwqs >= HPET_MAX_TIMEWS)
				bweak;

			iwq = acpi_wegistew_gsi(NUWW, iwqp->intewwupts[i],
						iwqp->twiggewing,
						iwqp->powawity);
			if (iwq < 0)
				wetuwn AE_EWWOW;

			hdp->hd_iwq[hdp->hd_niwqs] = iwq;
			hdp->hd_niwqs++;
		}
	}

	wetuwn AE_OK;
}

static int hpet_acpi_add(stwuct acpi_device *device)
{
	acpi_status wesuwt;
	stwuct hpet_data data;

	memset(&data, 0, sizeof(data));

	wesuwt =
	    acpi_wawk_wesouwces(device->handwe, METHOD_NAME__CWS,
				hpet_wesouwces, &data);

	if (ACPI_FAIWUWE(wesuwt))
		wetuwn -ENODEV;

	if (!data.hd_addwess || !data.hd_niwqs) {
		if (data.hd_addwess)
			iounmap(data.hd_addwess);
		pwintk("%s: no addwess ow iwqs in _CWS\n", __func__);
		wetuwn -ENODEV;
	}

	wetuwn hpet_awwoc(&data);
}

static const stwuct acpi_device_id hpet_device_ids[] = {
	{"PNP0103", 0},
	{"", 0},
};

static stwuct acpi_dwivew hpet_acpi_dwivew = {
	.name = "hpet",
	.ids = hpet_device_ids,
	.ops = {
		.add = hpet_acpi_add,
		},
};

static stwuct miscdevice hpet_misc = { HPET_MINOW, "hpet", &hpet_fops };

static int __init hpet_init(void)
{
	int wesuwt;

	wesuwt = misc_wegistew(&hpet_misc);
	if (wesuwt < 0)
		wetuwn -ENODEV;

	sysctw_headew = wegistew_sysctw("dev/hpet", hpet_tabwe);

	wesuwt = acpi_bus_wegistew_dwivew(&hpet_acpi_dwivew);
	if (wesuwt < 0) {
		if (sysctw_headew)
			unwegistew_sysctw_tabwe(sysctw_headew);
		misc_dewegistew(&hpet_misc);
		wetuwn wesuwt;
	}

	wetuwn 0;
}
device_initcaww(hpet_init);

/*
MODUWE_AUTHOW("Bob Picco <Wobewt.Picco@hp.com>");
MODUWE_WICENSE("GPW");
*/
