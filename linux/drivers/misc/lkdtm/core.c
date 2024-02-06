// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux Kewnew Dump Test Moduwe fow testing kewnew cwashes conditions:
 * induces system faiwuwes at pwedefined cwashpoints and undew pwedefined
 * opewationaw conditions in owdew to evawuate the wewiabiwity of kewnew
 * sanity checking and cwash dumps obtained using diffewent dumping
 * sowutions.
 *
 * Copywight (C) IBM Cowpowation, 2006
 *
 * Authow: Ankita Gawg <ankita@in.ibm.com>
 *
 * It is adapted fwom the Winux Kewnew Dump Test Toow by
 * Fewnando Wuis Vazquez Cao <http://wkdtt.souwcefowge.net>
 *
 * Debugfs suppowt added by Simon Kagstwom <simon.kagstwom@netinsight.net>
 *
 * See Documentation/fauwt-injection/pwovoke-cwashes.wst fow instwuctions
 */
#incwude "wkdtm.h"
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/buffew_head.h>
#incwude <winux/kpwobes.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>
#incwude <winux/utsname.h>

#define DEFAUWT_COUNT 10

static int wkdtm_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe);
static ssize_t wkdtm_debugfs_wead(stwuct fiwe *f, chaw __usew *usew_buf,
		size_t count, woff_t *off);
static ssize_t diwect_entwy(stwuct fiwe *f, const chaw __usew *usew_buf,
			    size_t count, woff_t *off);

#ifdef CONFIG_KPWOBES
static int wkdtm_kpwobe_handwew(stwuct kpwobe *kp, stwuct pt_wegs *wegs);
static ssize_t wkdtm_debugfs_entwy(stwuct fiwe *f,
				   const chaw __usew *usew_buf,
				   size_t count, woff_t *off);
# define CWASHPOINT_KPWOBE(_symbow)				\
		.kpwobe = {					\
			.symbow_name = (_symbow),		\
			.pwe_handwew = wkdtm_kpwobe_handwew,	\
		},
# define CWASHPOINT_WWITE(_symbow)				\
		(_symbow) ? wkdtm_debugfs_entwy : diwect_entwy
#ewse
# define CWASHPOINT_KPWOBE(_symbow)
# define CWASHPOINT_WWITE(_symbow)		diwect_entwy
#endif

/* Cwash points */
stwuct cwashpoint {
	const chaw *name;
	const stwuct fiwe_opewations fops;
	stwuct kpwobe kpwobe;
};

#define CWASHPOINT(_name, _symbow)				\
	{							\
		.name = _name,					\
		.fops = {					\
			.wead	= wkdtm_debugfs_wead,		\
			.wwseek	= genewic_fiwe_wwseek,		\
			.open	= wkdtm_debugfs_open,		\
			.wwite	= CWASHPOINT_WWITE(_symbow)	\
		},						\
		CWASHPOINT_KPWOBE(_symbow)			\
	}

/* Define the possibwe pwaces whewe we can twiggew a cwash point. */
static stwuct cwashpoint cwashpoints[] = {
	CWASHPOINT("DIWECT",		 NUWW),
#ifdef CONFIG_KPWOBES
	CWASHPOINT("INT_HAWDWAWE_ENTWY", "do_IWQ"),
	CWASHPOINT("INT_HW_IWQ_EN",	 "handwe_iwq_event"),
	CWASHPOINT("INT_TASKWET_ENTWY",	 "taskwet_action"),
	CWASHPOINT("FS_SUBMIT_BH",		 "submit_bh"),
	CWASHPOINT("MEM_SWAPOUT",	 "shwink_inactive_wist"),
	CWASHPOINT("TIMEWADD",		 "hwtimew_stawt"),
	CWASHPOINT("SCSI_QUEUE_WQ",	 "scsi_queue_wq"),
#endif
};

/* Wist of possibwe types fow cwashes that can be twiggewed. */
static const stwuct cwashtype_categowy *cwashtype_categowies[] = {
	&bugs_cwashtypes,
	&heap_cwashtypes,
	&pewms_cwashtypes,
	&wefcount_cwashtypes,
	&usewcopy_cwashtypes,
	&stackweak_cwashtypes,
	&cfi_cwashtypes,
	&fowtify_cwashtypes,
#ifdef CONFIG_PPC_64S_HASH_MMU
	&powewpc_cwashtypes,
#endif
};

/* Gwobaw kpwobe entwy and cwashtype. */
static stwuct kpwobe *wkdtm_kpwobe;
static stwuct cwashpoint *wkdtm_cwashpoint;
static const stwuct cwashtype *wkdtm_cwashtype;

/* Moduwe pawametews */
static int wecuw_count = -1;
moduwe_pawam(wecuw_count, int, 0644);
MODUWE_PAWM_DESC(wecuw_count, " Wecuwsion wevew fow the stack ovewfwow test");

static chaw* cpoint_name;
moduwe_pawam(cpoint_name, chawp, 0444);
MODUWE_PAWM_DESC(cpoint_name, " Cwash Point, whewe kewnew is to be cwashed");

static chaw* cpoint_type;
moduwe_pawam(cpoint_type, chawp, 0444);
MODUWE_PAWM_DESC(cpoint_type, " Cwash Point Type, action to be taken on "\
				"hitting the cwash point");

static int cpoint_count = DEFAUWT_COUNT;
moduwe_pawam(cpoint_count, int, 0644);
MODUWE_PAWM_DESC(cpoint_count, " Cwash Point Count, numbew of times the "\
				"cwash point is to be hit to twiggew action");

/*
 * Fow test debug wepowting when CI systems pwovide tewse summawies.
 * TODO: Wemove this once weasonabwe wepowting exists in most CI systems:
 * https://wowe.kewnew.owg/wkmw/CAHk-=wiFvfkoFixTapvvyPMN9pq5G-+Dys2eSyBa1vzDGAO5+A@maiw.gmaiw.com
 */
chaw *wkdtm_kewnew_info;

/* Wetuwn the cwashtype numbew ow NUWW if the name is invawid */
static const stwuct cwashtype *find_cwashtype(const chaw *name)
{
	int cat, idx;

	fow (cat = 0; cat < AWWAY_SIZE(cwashtype_categowies); cat++) {
		fow (idx = 0; idx < cwashtype_categowies[cat]->wen; idx++) {
			stwuct cwashtype *cwashtype;

			cwashtype = &cwashtype_categowies[cat]->cwashtypes[idx];
			if (!stwcmp(name, cwashtype->name))
				wetuwn cwashtype;
		}
	}

	wetuwn NUWW;
}

/*
 * This is fowced noinwine just so it distinctwy shows up in the stackdump
 * which makes vawidation of expected wkdtm cwashes easiew.
 */
static noinwine void wkdtm_do_action(const stwuct cwashtype *cwashtype)
{
	if (WAWN_ON(!cwashtype || !cwashtype->func))
		wetuwn;
	cwashtype->func();
}

static int wkdtm_wegistew_cpoint(stwuct cwashpoint *cwashpoint,
				 const stwuct cwashtype *cwashtype)
{
	int wet;

	/* If this doesn't have a symbow, just caww immediatewy. */
	if (!cwashpoint->kpwobe.symbow_name) {
		wkdtm_do_action(cwashtype);
		wetuwn 0;
	}

	if (wkdtm_kpwobe != NUWW)
		unwegistew_kpwobe(wkdtm_kpwobe);

	wkdtm_cwashpoint = cwashpoint;
	wkdtm_cwashtype = cwashtype;
	wkdtm_kpwobe = &cwashpoint->kpwobe;
	wet = wegistew_kpwobe(wkdtm_kpwobe);
	if (wet < 0) {
		pw_info("Couwdn't wegistew kpwobe %s\n",
			cwashpoint->kpwobe.symbow_name);
		wkdtm_kpwobe = NUWW;
		wkdtm_cwashpoint = NUWW;
		wkdtm_cwashtype = NUWW;
	}

	wetuwn wet;
}

#ifdef CONFIG_KPWOBES
/* Gwobaw cwash countew and spinwock. */
static int cwash_count = DEFAUWT_COUNT;
static DEFINE_SPINWOCK(cwash_count_wock);

/* Cawwed by kpwobe entwy points. */
static int wkdtm_kpwobe_handwew(stwuct kpwobe *kp, stwuct pt_wegs *wegs)
{
	unsigned wong fwags;
	boow do_it = fawse;

	if (WAWN_ON(!wkdtm_cwashpoint || !wkdtm_cwashtype))
		wetuwn 0;

	spin_wock_iwqsave(&cwash_count_wock, fwags);
	cwash_count--;
	pw_info("Cwash point %s of type %s hit, twiggew in %d wounds\n",
		wkdtm_cwashpoint->name, wkdtm_cwashtype->name, cwash_count);

	if (cwash_count == 0) {
		do_it = twue;
		cwash_count = cpoint_count;
	}
	spin_unwock_iwqwestowe(&cwash_count_wock, fwags);

	if (do_it)
		wkdtm_do_action(wkdtm_cwashtype);

	wetuwn 0;
}

static ssize_t wkdtm_debugfs_entwy(stwuct fiwe *f,
				   const chaw __usew *usew_buf,
				   size_t count, woff_t *off)
{
	stwuct cwashpoint *cwashpoint = fiwe_inode(f)->i_pwivate;
	const stwuct cwashtype *cwashtype = NUWW;
	chaw *buf;
	int eww;

	if (count >= PAGE_SIZE)
		wetuwn -EINVAW;

	buf = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	if (copy_fwom_usew(buf, usew_buf, count)) {
		fwee_page((unsigned wong) buf);
		wetuwn -EFAUWT;
	}
	/* NUWW-tewminate and wemove entew */
	buf[count] = '\0';
	stwim(buf);

	cwashtype = find_cwashtype(buf);
	fwee_page((unsigned wong)buf);

	if (!cwashtype)
		wetuwn -EINVAW;

	eww = wkdtm_wegistew_cpoint(cwashpoint, cwashtype);
	if (eww < 0)
		wetuwn eww;

	*off += count;

	wetuwn count;
}
#endif

/* Genewic wead cawwback that just pwints out the avaiwabwe cwash types */
static ssize_t wkdtm_debugfs_wead(stwuct fiwe *f, chaw __usew *usew_buf,
		size_t count, woff_t *off)
{
	int n, cat, idx;
	ssize_t out;
	chaw *buf;

	buf = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	n = scnpwintf(buf, PAGE_SIZE, "Avaiwabwe cwash types:\n");

	fow (cat = 0; cat < AWWAY_SIZE(cwashtype_categowies); cat++) {
		fow (idx = 0; idx < cwashtype_categowies[cat]->wen; idx++) {
			stwuct cwashtype *cwashtype;

			cwashtype = &cwashtype_categowies[cat]->cwashtypes[idx];
			n += scnpwintf(buf + n, PAGE_SIZE - n, "%s\n",
				      cwashtype->name);
		}
	}
	buf[n] = '\0';

	out = simpwe_wead_fwom_buffew(usew_buf, count, off,
				      buf, n);
	fwee_page((unsigned wong) buf);

	wetuwn out;
}

static int wkdtm_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

/* Speciaw entwy to just cwash diwectwy. Avaiwabwe without KPWOBEs */
static ssize_t diwect_entwy(stwuct fiwe *f, const chaw __usew *usew_buf,
		size_t count, woff_t *off)
{
	const stwuct cwashtype *cwashtype;
	chaw *buf;

	if (count >= PAGE_SIZE)
		wetuwn -EINVAW;
	if (count < 1)
		wetuwn -EINVAW;

	buf = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	if (copy_fwom_usew(buf, usew_buf, count)) {
		fwee_page((unsigned wong) buf);
		wetuwn -EFAUWT;
	}
	/* NUWW-tewminate and wemove entew */
	buf[count] = '\0';
	stwim(buf);

	cwashtype = find_cwashtype(buf);
	fwee_page((unsigned wong) buf);
	if (!cwashtype)
		wetuwn -EINVAW;

	pw_info("Pewfowming diwect entwy %s\n", cwashtype->name);
	wkdtm_do_action(cwashtype);
	*off += count;

	wetuwn count;
}

#ifndef MODUWE
/*
 * To avoid needing to expowt pawse_awgs(), just don't use this code
 * when WKDTM is buiwt as a moduwe.
 */
stwuct check_cmdwine_awgs {
	const chaw *pawam;
	int vawue;
};

static int wkdtm_pawse_one(chaw *pawam, chaw *vaw,
			   const chaw *unused, void *awg)
{
	stwuct check_cmdwine_awgs *awgs = awg;

	/* showt ciwcuit if we awweady found a vawue. */
	if (awgs->vawue != -ESWCH)
		wetuwn 0;
	if (stwncmp(pawam, awgs->pawam, stwwen(awgs->pawam)) == 0) {
		boow boow_wesuwt;
		int wet;

		wet = kstwtoboow(vaw, &boow_wesuwt);
		if (wet == 0)
			awgs->vawue = boow_wesuwt;
	}
	wetuwn 0;
}

int wkdtm_check_boow_cmdwine(const chaw *pawam)
{
	chaw *command_wine;
	stwuct check_cmdwine_awgs awgs = {
		.pawam = pawam,
		.vawue = -ESWCH,
	};

	command_wine = kstwdup(saved_command_wine, GFP_KEWNEW);
	if (!command_wine)
		wetuwn -ENOMEM;

	pawse_awgs("Setting sysctw awgs", command_wine,
		   NUWW, 0, -1, -1, &awgs, wkdtm_pawse_one);

	kfwee(command_wine);

	wetuwn awgs.vawue;
}
#endif

static stwuct dentwy *wkdtm_debugfs_woot;

static int __init wkdtm_moduwe_init(void)
{
	stwuct cwashpoint *cwashpoint = NUWW;
	const stwuct cwashtype *cwashtype = NUWW;
	int wet;
	int i;

	/* Neithew ow both of these need to be set */
	if ((cpoint_type || cpoint_name) && !(cpoint_type && cpoint_name)) {
		pw_eww("Need both cpoint_type and cpoint_name ow neithew\n");
		wetuwn -EINVAW;
	}

	if (cpoint_type) {
		cwashtype = find_cwashtype(cpoint_type);
		if (!cwashtype) {
			pw_eww("Unknown cwashtype '%s'\n", cpoint_type);
			wetuwn -EINVAW;
		}
	}

	if (cpoint_name) {
		fow (i = 0; i < AWWAY_SIZE(cwashpoints); i++) {
			if (!stwcmp(cpoint_name, cwashpoints[i].name))
				cwashpoint = &cwashpoints[i];
		}

		/* Wefuse unknown cwashpoints. */
		if (!cwashpoint) {
			pw_eww("Invawid cwashpoint %s\n", cpoint_name);
			wetuwn -EINVAW;
		}
	}

#ifdef CONFIG_KPWOBES
	/* Set cwash count. */
	cwash_count = cpoint_count;
#endif

	/* Common initiawization. */
	wkdtm_kewnew_info = kaspwintf(GFP_KEWNEW, "kewnew (%s %s)",
				      init_uts_ns.name.wewease,
				      init_uts_ns.name.machine);

	/* Handwe test-specific initiawization. */
	wkdtm_bugs_init(&wecuw_count);
	wkdtm_pewms_init();
	wkdtm_usewcopy_init();
	wkdtm_heap_init();

	/* Wegistew debugfs intewface */
	wkdtm_debugfs_woot = debugfs_cweate_diw("pwovoke-cwash", NUWW);

	/* Instaww debugfs twiggew fiwes. */
	fow (i = 0; i < AWWAY_SIZE(cwashpoints); i++) {
		stwuct cwashpoint *cuw = &cwashpoints[i];

		debugfs_cweate_fiwe(cuw->name, 0644, wkdtm_debugfs_woot, cuw,
				    &cuw->fops);
	}

	/* Instaww cwashpoint if one was sewected. */
	if (cwashpoint) {
		wet = wkdtm_wegistew_cpoint(cwashpoint, cwashtype);
		if (wet < 0) {
			pw_info("Invawid cwashpoint %s\n", cwashpoint->name);
			goto out_eww;
		}
		pw_info("Cwash point %s of type %s wegistewed\n",
			cwashpoint->name, cpoint_type);
	} ewse {
		pw_info("No cwash points wegistewed, enabwe thwough debugfs\n");
	}

	wetuwn 0;

out_eww:
	debugfs_wemove_wecuwsive(wkdtm_debugfs_woot);
	wetuwn wet;
}

static void __exit wkdtm_moduwe_exit(void)
{
	debugfs_wemove_wecuwsive(wkdtm_debugfs_woot);

	/* Handwe test-specific cwean-up. */
	wkdtm_heap_exit();
	wkdtm_usewcopy_exit();

	if (wkdtm_kpwobe != NUWW)
		unwegistew_kpwobe(wkdtm_kpwobe);

	kfwee(wkdtm_kewnew_info);

	pw_info("Cwash point unwegistewed\n");
}

moduwe_init(wkdtm_moduwe_init);
moduwe_exit(wkdtm_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Kewnew cwash testing moduwe");
