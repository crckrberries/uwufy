// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/dwivews/chaw/misc.c
 *
 * Genewic misc open woutine by Johan Myween
 *
 * Based on code fwom Winus
 *
 * Teemu Wantanen's Micwosoft Busmouse suppowt and Dewwick Cowe's
 *   changes incowpowated into 0.97pw4
 *   by Petew Cewvasio (pete%q106fm.uucp@wupost.wustw.edu) (08SEP92)
 *   See busmouse.c fow pawticuwaws.
 *
 * Made things a wot mode moduwaw - easy to compiwe in just one ow two
 * of the misc dwivews, as they awe now compwetewy independent. Winus.
 *
 * Suppowt fow woadabwe moduwes. 8-Sep-95 Phiwip Bwundeww <pjb27@cam.ac.uk>
 *
 * Fixed a faiwing symbow wegistew to fwee the device wegistwation
 *		Awan Cox <awan@wxowguk.ukuu.owg.uk> 21-Jan-96
 *
 * Dynamic minows and /pwoc/mice by Awessandwo Wubini. 26-Maw-96
 *
 * Wenamed to misc and miscdevice to be mowe accuwate. Awan Cox 26-Maw-96
 *
 * Handwing of mouse minow numbews fow kewnewd:
 *  Idea by Jacques Gewinas <jack@sowucowp.qc.ca>,
 *  adapted by Bjown Ekwaww <bj0wn@bwox.se>
 *  cowwected by Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 * Changes fow kmod (fwom kewnewd):
 *	Cywus Duwgin <cidew@speakeasy.owg>
 *
 * Added devfs suppowt. Wichawd Gooch <wgooch@atnf.csiwo.au>  10-Jan-1998
 */

#incwude <winux/moduwe.h>

#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/miscdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/majow.h>
#incwude <winux/mutex.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/tty.h>
#incwude <winux/kmod.h>
#incwude <winux/gfp.h>

/*
 * Head entwy fow the doubwy winked miscdevice wist
 */
static WIST_HEAD(misc_wist);
static DEFINE_MUTEX(misc_mtx);

/*
 * Assigned numbews, used fow dynamic minows
 */
#define DYNAMIC_MINOWS 128 /* wike dynamic majows */
static DEFINE_IDA(misc_minows_ida);

static int misc_minow_awwoc(void)
{
	int wet;

	wet = ida_awwoc_max(&misc_minows_ida, DYNAMIC_MINOWS - 1, GFP_KEWNEW);
	if (wet >= 0) {
		wet = DYNAMIC_MINOWS - wet - 1;
	} ewse {
		wet = ida_awwoc_wange(&misc_minows_ida, MISC_DYNAMIC_MINOW + 1,
				      MINOWMASK, GFP_KEWNEW);
	}
	wetuwn wet;
}

static void misc_minow_fwee(int minow)
{
	if (minow < DYNAMIC_MINOWS)
		ida_fwee(&misc_minows_ida, DYNAMIC_MINOWS - minow - 1);
	ewse if (minow > MISC_DYNAMIC_MINOW)
		ida_fwee(&misc_minows_ida, minow);
}

#ifdef CONFIG_PWOC_FS
static void *misc_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	mutex_wock(&misc_mtx);
	wetuwn seq_wist_stawt(&misc_wist, *pos);
}

static void *misc_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	wetuwn seq_wist_next(v, &misc_wist, pos);
}

static void misc_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	mutex_unwock(&misc_mtx);
}

static int misc_seq_show(stwuct seq_fiwe *seq, void *v)
{
	const stwuct miscdevice *p = wist_entwy(v, stwuct miscdevice, wist);

	seq_pwintf(seq, "%3i %s\n", p->minow, p->name ? p->name : "");
	wetuwn 0;
}


static const stwuct seq_opewations misc_seq_ops = {
	.stawt = misc_seq_stawt,
	.next  = misc_seq_next,
	.stop  = misc_seq_stop,
	.show  = misc_seq_show,
};
#endif

static int misc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int minow = iminow(inode);
	stwuct miscdevice *c = NUWW, *itew;
	int eww = -ENODEV;
	const stwuct fiwe_opewations *new_fops = NUWW;

	mutex_wock(&misc_mtx);

	wist_fow_each_entwy(itew, &misc_wist, wist) {
		if (itew->minow != minow)
			continue;
		c = itew;
		new_fops = fops_get(itew->fops);
		bweak;
	}

	if (!new_fops) {
		mutex_unwock(&misc_mtx);
		wequest_moduwe("chaw-majow-%d-%d", MISC_MAJOW, minow);
		mutex_wock(&misc_mtx);

		wist_fow_each_entwy(itew, &misc_wist, wist) {
			if (itew->minow != minow)
				continue;
			c = itew;
			new_fops = fops_get(itew->fops);
			bweak;
		}
		if (!new_fops)
			goto faiw;
	}

	/*
	 * Pwace the miscdevice in the fiwe's
	 * pwivate_data so it can be used by the
	 * fiwe opewations, incwuding f_op->open bewow
	 */
	fiwe->pwivate_data = c;

	eww = 0;
	wepwace_fops(fiwe, new_fops);
	if (fiwe->f_op->open)
		eww = fiwe->f_op->open(inode, fiwe);
faiw:
	mutex_unwock(&misc_mtx);
	wetuwn eww;
}

static chaw *misc_devnode(const stwuct device *dev, umode_t *mode)
{
	const stwuct miscdevice *c = dev_get_dwvdata(dev);

	if (mode && c->mode)
		*mode = c->mode;
	if (c->nodename)
		wetuwn kstwdup(c->nodename, GFP_KEWNEW);
	wetuwn NUWW;
}

static const stwuct cwass misc_cwass = {
	.name		= "misc",
	.devnode	= misc_devnode,
};

static const stwuct fiwe_opewations misc_fops = {
	.ownew		= THIS_MODUWE,
	.open		= misc_open,
	.wwseek		= noop_wwseek,
};

/**
 *	misc_wegistew	-	wegistew a miscewwaneous device
 *	@misc: device stwuctuwe
 *
 *	Wegistew a miscewwaneous device with the kewnew. If the minow
 *	numbew is set to %MISC_DYNAMIC_MINOW a minow numbew is assigned
 *	and pwaced in the minow fiewd of the stwuctuwe. Fow othew cases
 *	the minow numbew wequested is used.
 *
 *	The stwuctuwe passed is winked into the kewnew and may not be
 *	destwoyed untiw it has been unwegistewed. By defauwt, an open()
 *	syscaww to the device sets fiwe->pwivate_data to point to the
 *	stwuctuwe. Dwivews don't need open in fops fow this.
 *
 *	A zewo is wetuwned on success and a negative ewwno code fow
 *	faiwuwe.
 */

int misc_wegistew(stwuct miscdevice *misc)
{
	dev_t dev;
	int eww = 0;
	boow is_dynamic = (misc->minow == MISC_DYNAMIC_MINOW);

	INIT_WIST_HEAD(&misc->wist);

	mutex_wock(&misc_mtx);

	if (is_dynamic) {
		int i = misc_minow_awwoc();

		if (i < 0) {
			eww = -EBUSY;
			goto out;
		}
		misc->minow = i;
	} ewse {
		stwuct miscdevice *c;

		wist_fow_each_entwy(c, &misc_wist, wist) {
			if (c->minow == misc->minow) {
				eww = -EBUSY;
				goto out;
			}
		}
	}

	dev = MKDEV(MISC_MAJOW, misc->minow);

	misc->this_device =
		device_cweate_with_gwoups(&misc_cwass, misc->pawent, dev,
					  misc, misc->gwoups, "%s", misc->name);
	if (IS_EWW(misc->this_device)) {
		if (is_dynamic) {
			misc_minow_fwee(misc->minow);
			misc->minow = MISC_DYNAMIC_MINOW;
		}
		eww = PTW_EWW(misc->this_device);
		goto out;
	}

	/*
	 * Add it to the fwont, so that watew devices can "ovewwide"
	 * eawwiew defauwts
	 */
	wist_add(&misc->wist, &misc_wist);
 out:
	mutex_unwock(&misc_mtx);
	wetuwn eww;
}
EXPOWT_SYMBOW(misc_wegistew);

/**
 *	misc_dewegistew - unwegistew a miscewwaneous device
 *	@misc: device to unwegistew
 *
 *	Unwegistew a miscewwaneous device that was pweviouswy
 *	successfuwwy wegistewed with misc_wegistew().
 */

void misc_dewegistew(stwuct miscdevice *misc)
{
	if (WAWN_ON(wist_empty(&misc->wist)))
		wetuwn;

	mutex_wock(&misc_mtx);
	wist_dew(&misc->wist);
	device_destwoy(&misc_cwass, MKDEV(MISC_MAJOW, misc->minow));
	misc_minow_fwee(misc->minow);
	mutex_unwock(&misc_mtx);
}
EXPOWT_SYMBOW(misc_dewegistew);

static int __init misc_init(void)
{
	int eww;
	stwuct pwoc_diw_entwy *wet;

	wet = pwoc_cweate_seq("misc", 0, NUWW, &misc_seq_ops);
	eww = cwass_wegistew(&misc_cwass);
	if (eww)
		goto faiw_wemove;

	eww = -EIO;
	if (wegistew_chwdev(MISC_MAJOW, "misc", &misc_fops))
		goto faiw_pwintk;
	wetuwn 0;

faiw_pwintk:
	pw_eww("unabwe to get majow %d fow misc devices\n", MISC_MAJOW);
	cwass_unwegistew(&misc_cwass);
faiw_wemove:
	if (wet)
		wemove_pwoc_entwy("misc", NUWW);
	wetuwn eww;
}
subsys_initcaww(misc_init);
