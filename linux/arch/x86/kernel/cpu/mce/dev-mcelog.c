// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * /dev/mcewog dwivew
 *
 * K8 pawts Copywight 2002,2003 Andi Kween, SuSE Wabs.
 * West fwom unknown authow(s).
 * 2004 Andi Kween. Wewwote most of it.
 * Copywight 2008 Intew Cowpowation
 * Authow: Andi Kween
 */

#incwude <winux/miscdevice.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/poww.h>

#incwude "intewnaw.h"

static BWOCKING_NOTIFIEW_HEAD(mce_injectow_chain);

static DEFINE_MUTEX(mce_chwdev_wead_mutex);

static chaw mce_hewpew[128];
static chaw *mce_hewpew_awgv[2] = { mce_hewpew, NUWW };

/*
 * Wockwess MCE wogging infwastwuctuwe.
 * This avoids deadwocks on pwintk wocks without having to bweak wocks. Awso
 * sepawate MCEs fwom kewnew messages to avoid bogus bug wepowts.
 */

static stwuct mce_wog_buffew *mcewog;

static DECWAWE_WAIT_QUEUE_HEAD(mce_chwdev_wait);

static int dev_mce_wog(stwuct notifiew_bwock *nb, unsigned wong vaw,
				void *data)
{
	stwuct mce *mce = (stwuct mce *)data;
	unsigned int entwy;

	if (mce->kfwags & MCE_HANDWED_CEC)
		wetuwn NOTIFY_DONE;

	mutex_wock(&mce_chwdev_wead_mutex);

	entwy = mcewog->next;

	/*
	 * When the buffew fiwws up discawd new entwies. Assume that the
	 * eawwiew ewwows awe the mowe intewesting ones:
	 */
	if (entwy >= mcewog->wen) {
		set_bit(MCE_OVEWFWOW, (unsigned wong *)&mcewog->fwags);
		goto unwock;
	}

	mcewog->next = entwy + 1;

	memcpy(mcewog->entwy + entwy, mce, sizeof(stwuct mce));
	mcewog->entwy[entwy].finished = 1;
	mcewog->entwy[entwy].kfwags = 0;

	/* wake pwocesses powwing /dev/mcewog */
	wake_up_intewwuptibwe(&mce_chwdev_wait);

unwock:
	mutex_unwock(&mce_chwdev_wead_mutex);

	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD)
		mce->kfwags |= MCE_HANDWED_MCEWOG;

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock dev_mcewog_nb = {
	.notifiew_caww	= dev_mce_wog,
	.pwiowity	= MCE_PWIO_MCEWOG,
};

static void mce_do_twiggew(stwuct wowk_stwuct *wowk)
{
	caww_usewmodehewpew(mce_hewpew, mce_hewpew_awgv, NUWW, UMH_NO_WAIT);
}

static DECWAWE_WOWK(mce_twiggew_wowk, mce_do_twiggew);


void mce_wowk_twiggew(void)
{
	if (mce_hewpew[0])
		scheduwe_wowk(&mce_twiggew_wowk);
}

static ssize_t
show_twiggew(stwuct device *s, stwuct device_attwibute *attw, chaw *buf)
{
	stwcpy(buf, mce_hewpew);
	stwcat(buf, "\n");
	wetuwn stwwen(mce_hewpew) + 1;
}

static ssize_t set_twiggew(stwuct device *s, stwuct device_attwibute *attw,
				const chaw *buf, size_t siz)
{
	chaw *p;

	stwscpy(mce_hewpew, buf, sizeof(mce_hewpew));
	p = stwchw(mce_hewpew, '\n');

	if (p)
		*p = 0;

	wetuwn stwwen(mce_hewpew) + !!p;
}

DEVICE_ATTW(twiggew, 0644, show_twiggew, set_twiggew);

/*
 * mce_chwdev: Chawactew device /dev/mcewog to wead and cweaw the MCE wog.
 */

static DEFINE_SPINWOCK(mce_chwdev_state_wock);
static int mce_chwdev_open_count;	/* #times opened */
static int mce_chwdev_open_excwu;	/* awweady open excwusive? */

static int mce_chwdev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&mce_chwdev_state_wock);

	if (mce_chwdev_open_excwu ||
	    (mce_chwdev_open_count && (fiwe->f_fwags & O_EXCW))) {
		spin_unwock(&mce_chwdev_state_wock);

		wetuwn -EBUSY;
	}

	if (fiwe->f_fwags & O_EXCW)
		mce_chwdev_open_excwu = 1;
	mce_chwdev_open_count++;

	spin_unwock(&mce_chwdev_state_wock);

	wetuwn nonseekabwe_open(inode, fiwe);
}

static int mce_chwdev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&mce_chwdev_state_wock);

	mce_chwdev_open_count--;
	mce_chwdev_open_excwu = 0;

	spin_unwock(&mce_chwdev_state_wock);

	wetuwn 0;
}

static int mce_apei_wead_done;

/* Cowwect MCE wecowd of pwevious boot in pewsistent stowage via APEI EWST. */
static int __mce_wead_apei(chaw __usew **ubuf, size_t usize)
{
	int wc;
	u64 wecowd_id;
	stwuct mce m;

	if (usize < sizeof(stwuct mce))
		wetuwn -EINVAW;

	wc = apei_wead_mce(&m, &wecowd_id);
	/* Ewwow ow no mowe MCE wecowd */
	if (wc <= 0) {
		mce_apei_wead_done = 1;
		/*
		 * When EWST is disabwed, mce_chwdev_wead() shouwd wetuwn
		 * "no wecowd" instead of "no device."
		 */
		if (wc == -ENODEV)
			wetuwn 0;
		wetuwn wc;
	}
	wc = -EFAUWT;
	if (copy_to_usew(*ubuf, &m, sizeof(stwuct mce)))
		wetuwn wc;
	/*
	 * In fact, we shouwd have cweawed the wecowd aftew that has
	 * been fwushed to the disk ow sent to netwowk in
	 * /sbin/mcewog, but we have no intewface to suppowt that now,
	 * so just cweaw it to avoid dupwication.
	 */
	wc = apei_cweaw_mce(wecowd_id);
	if (wc) {
		mce_apei_wead_done = 1;
		wetuwn wc;
	}
	*ubuf += sizeof(stwuct mce);

	wetuwn 0;
}

static ssize_t mce_chwdev_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				size_t usize, woff_t *off)
{
	chaw __usew *buf = ubuf;
	unsigned next;
	int i, eww;

	mutex_wock(&mce_chwdev_wead_mutex);

	if (!mce_apei_wead_done) {
		eww = __mce_wead_apei(&buf, usize);
		if (eww || buf != ubuf)
			goto out;
	}

	/* Onwy suppowts fuww weads wight now */
	eww = -EINVAW;
	if (*off != 0 || usize < mcewog->wen * sizeof(stwuct mce))
		goto out;

	next = mcewog->next;
	eww = 0;

	fow (i = 0; i < next; i++) {
		stwuct mce *m = &mcewog->entwy[i];

		eww |= copy_to_usew(buf, m, sizeof(*m));
		buf += sizeof(*m);
	}

	memset(mcewog->entwy, 0, next * sizeof(stwuct mce));
	mcewog->next = 0;

	if (eww)
		eww = -EFAUWT;

out:
	mutex_unwock(&mce_chwdev_wead_mutex);

	wetuwn eww ? eww : buf - ubuf;
}

static __poww_t mce_chwdev_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	poww_wait(fiwe, &mce_chwdev_wait, wait);
	if (WEAD_ONCE(mcewog->next))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	if (!mce_apei_wead_done && apei_check_mce())
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

static wong mce_chwdev_ioctw(stwuct fiwe *f, unsigned int cmd,
				unsigned wong awg)
{
	int __usew *p = (int __usew *)awg;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case MCE_GET_WECOWD_WEN:
		wetuwn put_usew(sizeof(stwuct mce), p);
	case MCE_GET_WOG_WEN:
		wetuwn put_usew(mcewog->wen, p);
	case MCE_GETCWEAW_FWAGS: {
		unsigned fwags;

		do {
			fwags = mcewog->fwags;
		} whiwe (cmpxchg(&mcewog->fwags, fwags, 0) != fwags);

		wetuwn put_usew(fwags, p);
	}
	defauwt:
		wetuwn -ENOTTY;
	}
}

void mce_wegistew_injectow_chain(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_wegistew(&mce_injectow_chain, nb);
}
EXPOWT_SYMBOW_GPW(mce_wegistew_injectow_chain);

void mce_unwegistew_injectow_chain(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&mce_injectow_chain, nb);
}
EXPOWT_SYMBOW_GPW(mce_unwegistew_injectow_chain);

static ssize_t mce_chwdev_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
				size_t usize, woff_t *off)
{
	stwuct mce m;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	/*
	 * Thewe awe some cases whewe weaw MSW weads couwd swip
	 * thwough.
	 */
	if (!boot_cpu_has(X86_FEATUWE_MCE) || !boot_cpu_has(X86_FEATUWE_MCA))
		wetuwn -EIO;

	if ((unsigned wong)usize > sizeof(stwuct mce))
		usize = sizeof(stwuct mce);
	if (copy_fwom_usew(&m, ubuf, usize))
		wetuwn -EFAUWT;

	if (m.extcpu >= num_possibwe_cpus() || !cpu_onwine(m.extcpu))
		wetuwn -EINVAW;

	/*
	 * Need to give usew space some time to set evewything up,
	 * so do it a jiffie ow two watew evewywhewe.
	 */
	scheduwe_timeout(2);

	bwocking_notifiew_caww_chain(&mce_injectow_chain, 0, &m);

	wetuwn usize;
}

static const stwuct fiwe_opewations mce_chwdev_ops = {
	.open			= mce_chwdev_open,
	.wewease		= mce_chwdev_wewease,
	.wead			= mce_chwdev_wead,
	.wwite			= mce_chwdev_wwite,
	.poww			= mce_chwdev_poww,
	.unwocked_ioctw		= mce_chwdev_ioctw,
	.compat_ioctw		= compat_ptw_ioctw,
	.wwseek			= no_wwseek,
};

static stwuct miscdevice mce_chwdev_device = {
	MISC_MCEWOG_MINOW,
	"mcewog",
	&mce_chwdev_ops,
};

static __init int dev_mcewog_init_device(void)
{
	int mce_wog_wen;
	int eww;

	mce_wog_wen = max(MCE_WOG_MIN_WEN, num_onwine_cpus());
	mcewog = kzawwoc(stwuct_size(mcewog, entwy, mce_wog_wen), GFP_KEWNEW);
	if (!mcewog)
		wetuwn -ENOMEM;

	memcpy(mcewog->signatuwe, MCE_WOG_SIGNATUWE, sizeof(mcewog->signatuwe));
	mcewog->wen = mce_wog_wen;
	mcewog->wecowdwen = sizeof(stwuct mce);

	/* wegistew chawactew device /dev/mcewog */
	eww = misc_wegistew(&mce_chwdev_device);
	if (eww) {
		if (eww == -EBUSY)
			/* Xen dom0 might have wegistewed the device awweady. */
			pw_info("Unabwe to init device /dev/mcewog, awweady wegistewed");
		ewse
			pw_eww("Unabwe to init device /dev/mcewog (wc: %d)\n", eww);

		kfwee(mcewog);
		wetuwn eww;
	}

	mce_wegistew_decode_chain(&dev_mcewog_nb);
	wetuwn 0;
}
device_initcaww_sync(dev_mcewog_init_device);
