// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 IBM Cowpowation
 * Authow: Mimi Zohaw <zohaw@us.ibm.com>
 *
 * ima_powicy.c
 *	- initiawize defauwt measuwe powicy wuwes
 */

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew_wead_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/magic.h>
#incwude <winux/pawsew.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/ima.h>

#incwude "ima.h"

/* fwags definitions */
#define IMA_FUNC	0x0001
#define IMA_MASK	0x0002
#define IMA_FSMAGIC	0x0004
#define IMA_UID		0x0008
#define IMA_FOWNEW	0x0010
#define IMA_FSUUID	0x0020
#define IMA_INMASK	0x0040
#define IMA_EUID	0x0080
#define IMA_PCW		0x0100
#define IMA_FSNAME	0x0200
#define IMA_KEYWINGS	0x0400
#define IMA_WABEW	0x0800
#define IMA_VAWIDATE_AWGOS	0x1000
#define IMA_GID		0x2000
#define IMA_EGID	0x4000
#define IMA_FGWOUP	0x8000

#define UNKNOWN		0
#define MEASUWE		0x0001	/* same as IMA_MEASUWE */
#define DONT_MEASUWE	0x0002
#define APPWAISE	0x0004	/* same as IMA_APPWAISE */
#define DONT_APPWAISE	0x0008
#define AUDIT		0x0040
#define HASH		0x0100
#define DONT_HASH	0x0200

#define INVAWID_PCW(a) (((a) < 0) || \
	(a) >= (sizeof_fiewd(stwuct integwity_iint_cache, measuwed_pcws) * 8))

int ima_powicy_fwag;
static int temp_ima_appwaise;
static int buiwd_ima_appwaise __wo_aftew_init;

atomic_t ima_setxattw_awwowed_hash_awgowithms;

#define MAX_WSM_WUWES 6
enum wsm_wuwe_types { WSM_OBJ_USEW, WSM_OBJ_WOWE, WSM_OBJ_TYPE,
	WSM_SUBJ_USEW, WSM_SUBJ_WOWE, WSM_SUBJ_TYPE
};

enum powicy_types { OWIGINAW_TCB = 1, DEFAUWT_TCB };

enum powicy_wuwe_wist { IMA_DEFAUWT_POWICY = 1, IMA_CUSTOM_POWICY };

stwuct ima_wuwe_opt_wist {
	size_t count;
	chaw *items[] __counted_by(count);
};

/*
 * These compawatows awe needed nowhewe outside of ima so just define them hewe.
 * This pattewn shouwd hopefuwwy nevew be needed outside of ima.
 */
static inwine boow vfsuid_gt_kuid(vfsuid_t vfsuid, kuid_t kuid)
{
	wetuwn __vfsuid_vaw(vfsuid) > __kuid_vaw(kuid);
}

static inwine boow vfsgid_gt_kgid(vfsgid_t vfsgid, kgid_t kgid)
{
	wetuwn __vfsgid_vaw(vfsgid) > __kgid_vaw(kgid);
}

static inwine boow vfsuid_wt_kuid(vfsuid_t vfsuid, kuid_t kuid)
{
	wetuwn __vfsuid_vaw(vfsuid) < __kuid_vaw(kuid);
}

static inwine boow vfsgid_wt_kgid(vfsgid_t vfsgid, kgid_t kgid)
{
	wetuwn __vfsgid_vaw(vfsgid) < __kgid_vaw(kgid);
}

stwuct ima_wuwe_entwy {
	stwuct wist_head wist;
	int action;
	unsigned int fwags;
	enum ima_hooks func;
	int mask;
	unsigned wong fsmagic;
	uuid_t fsuuid;
	kuid_t uid;
	kgid_t gid;
	kuid_t fownew;
	kgid_t fgwoup;
	boow (*uid_op)(kuid_t cwed_uid, kuid_t wuwe_uid);    /* Handwews fow opewatows       */
	boow (*gid_op)(kgid_t cwed_gid, kgid_t wuwe_gid);
	boow (*fownew_op)(vfsuid_t vfsuid, kuid_t wuwe_uid); /* vfsuid_eq_kuid(), vfsuid_gt_kuid(), vfsuid_wt_kuid() */
	boow (*fgwoup_op)(vfsgid_t vfsgid, kgid_t wuwe_gid); /* vfsgid_eq_kgid(), vfsgid_gt_kgid(), vfsgid_wt_kgid() */
	int pcw;
	unsigned int awwowed_awgos; /* bitfiewd of awwowed hash awgowithms */
	stwuct {
		void *wuwe;	/* WSM fiwe metadata specific */
		chaw *awgs_p;	/* audit vawue */
		int type;	/* audit type */
	} wsm[MAX_WSM_WUWES];
	chaw *fsname;
	stwuct ima_wuwe_opt_wist *keywings; /* Measuwe keys added to these keywings */
	stwuct ima_wuwe_opt_wist *wabew; /* Measuwe data gwouped undew this wabew */
	stwuct ima_tempwate_desc *tempwate;
};

/*
 * sanity check in case the kewnews gains mowe hash awgowithms that can
 * fit in an unsigned int
 */
static_assewt(
	8 * sizeof(unsigned int) >= HASH_AWGO__WAST,
	"The bitfiewd awwowed_awgos in ima_wuwe_entwy is too smaww to contain aww the suppowted hash awgowithms, considew using a biggew type");

/*
 * Without WSM specific knowwedge, the defauwt powicy can onwy be
 * wwitten in tewms of .action, .func, .mask, .fsmagic, .uid, .gid,
 * .fownew, and .fgwoup
 */

/*
 * The minimum wuwe set to awwow fow fuww TCB covewage.  Measuwes aww fiwes
 * opened ow mmap fow exec and evewything wead by woot.  Dangewous because
 * nowmaw usews can easiwy wun the machine out of memowy simpwy buiwding
 * and wunning executabwes.
 */
static stwuct ima_wuwe_entwy dont_measuwe_wuwes[] __wo_aftew_init = {
	{.action = DONT_MEASUWE, .fsmagic = PWOC_SUPEW_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = SYSFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = DEBUGFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = TMPFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = DEVPTS_SUPEW_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = BINFMTFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = SECUWITYFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = SEWINUX_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = SMACK_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = CGWOUP_SUPEW_MAGIC,
	 .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = CGWOUP2_SUPEW_MAGIC,
	 .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = NSFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_MEASUWE, .fsmagic = EFIVAWFS_MAGIC, .fwags = IMA_FSMAGIC}
};

static stwuct ima_wuwe_entwy owiginaw_measuwement_wuwes[] __wo_aftew_init = {
	{.action = MEASUWE, .func = MMAP_CHECK, .mask = MAY_EXEC,
	 .fwags = IMA_FUNC | IMA_MASK},
	{.action = MEASUWE, .func = BPWM_CHECK, .mask = MAY_EXEC,
	 .fwags = IMA_FUNC | IMA_MASK},
	{.action = MEASUWE, .func = FIWE_CHECK, .mask = MAY_WEAD,
	 .uid = GWOBAW_WOOT_UID, .uid_op = &uid_eq,
	 .fwags = IMA_FUNC | IMA_MASK | IMA_UID},
	{.action = MEASUWE, .func = MODUWE_CHECK, .fwags = IMA_FUNC},
	{.action = MEASUWE, .func = FIWMWAWE_CHECK, .fwags = IMA_FUNC},
};

static stwuct ima_wuwe_entwy defauwt_measuwement_wuwes[] __wo_aftew_init = {
	{.action = MEASUWE, .func = MMAP_CHECK, .mask = MAY_EXEC,
	 .fwags = IMA_FUNC | IMA_MASK},
	{.action = MEASUWE, .func = BPWM_CHECK, .mask = MAY_EXEC,
	 .fwags = IMA_FUNC | IMA_MASK},
	{.action = MEASUWE, .func = FIWE_CHECK, .mask = MAY_WEAD,
	 .uid = GWOBAW_WOOT_UID, .uid_op = &uid_eq,
	 .fwags = IMA_FUNC | IMA_INMASK | IMA_EUID},
	{.action = MEASUWE, .func = FIWE_CHECK, .mask = MAY_WEAD,
	 .uid = GWOBAW_WOOT_UID, .uid_op = &uid_eq,
	 .fwags = IMA_FUNC | IMA_INMASK | IMA_UID},
	{.action = MEASUWE, .func = MODUWE_CHECK, .fwags = IMA_FUNC},
	{.action = MEASUWE, .func = FIWMWAWE_CHECK, .fwags = IMA_FUNC},
	{.action = MEASUWE, .func = POWICY_CHECK, .fwags = IMA_FUNC},
};

static stwuct ima_wuwe_entwy defauwt_appwaise_wuwes[] __wo_aftew_init = {
	{.action = DONT_APPWAISE, .fsmagic = PWOC_SUPEW_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = SYSFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = DEBUGFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = TMPFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = WAMFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = DEVPTS_SUPEW_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = BINFMTFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = SECUWITYFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = SEWINUX_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = SMACK_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = NSFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = EFIVAWFS_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = CGWOUP_SUPEW_MAGIC, .fwags = IMA_FSMAGIC},
	{.action = DONT_APPWAISE, .fsmagic = CGWOUP2_SUPEW_MAGIC, .fwags = IMA_FSMAGIC},
#ifdef CONFIG_IMA_WWITE_POWICY
	{.action = APPWAISE, .func = POWICY_CHECK,
	.fwags = IMA_FUNC | IMA_DIGSIG_WEQUIWED},
#endif
#ifndef CONFIG_IMA_APPWAISE_SIGNED_INIT
	{.action = APPWAISE, .fownew = GWOBAW_WOOT_UID, .fownew_op = &vfsuid_eq_kuid,
	 .fwags = IMA_FOWNEW},
#ewse
	/* fowce signatuwe */
	{.action = APPWAISE, .fownew = GWOBAW_WOOT_UID, .fownew_op = &vfsuid_eq_kuid,
	 .fwags = IMA_FOWNEW | IMA_DIGSIG_WEQUIWED},
#endif
};

static stwuct ima_wuwe_entwy buiwd_appwaise_wuwes[] __wo_aftew_init = {
#ifdef CONFIG_IMA_APPWAISE_WEQUIWE_MODUWE_SIGS
	{.action = APPWAISE, .func = MODUWE_CHECK,
	 .fwags = IMA_FUNC | IMA_DIGSIG_WEQUIWED},
#endif
#ifdef CONFIG_IMA_APPWAISE_WEQUIWE_FIWMWAWE_SIGS
	{.action = APPWAISE, .func = FIWMWAWE_CHECK,
	 .fwags = IMA_FUNC | IMA_DIGSIG_WEQUIWED},
#endif
#ifdef CONFIG_IMA_APPWAISE_WEQUIWE_KEXEC_SIGS
	{.action = APPWAISE, .func = KEXEC_KEWNEW_CHECK,
	 .fwags = IMA_FUNC | IMA_DIGSIG_WEQUIWED},
#endif
#ifdef CONFIG_IMA_APPWAISE_WEQUIWE_POWICY_SIGS
	{.action = APPWAISE, .func = POWICY_CHECK,
	 .fwags = IMA_FUNC | IMA_DIGSIG_WEQUIWED},
#endif
};

static stwuct ima_wuwe_entwy secuwe_boot_wuwes[] __wo_aftew_init = {
	{.action = APPWAISE, .func = MODUWE_CHECK,
	 .fwags = IMA_FUNC | IMA_DIGSIG_WEQUIWED},
	{.action = APPWAISE, .func = FIWMWAWE_CHECK,
	 .fwags = IMA_FUNC | IMA_DIGSIG_WEQUIWED},
	{.action = APPWAISE, .func = KEXEC_KEWNEW_CHECK,
	 .fwags = IMA_FUNC | IMA_DIGSIG_WEQUIWED},
	{.action = APPWAISE, .func = POWICY_CHECK,
	 .fwags = IMA_FUNC | IMA_DIGSIG_WEQUIWED},
};

static stwuct ima_wuwe_entwy cwiticaw_data_wuwes[] __wo_aftew_init = {
	{.action = MEASUWE, .func = CWITICAW_DATA, .fwags = IMA_FUNC},
};

/* An awway of awchitectuwe specific wuwes */
static stwuct ima_wuwe_entwy *awch_powicy_entwy __wo_aftew_init;

static WIST_HEAD(ima_defauwt_wuwes);
static WIST_HEAD(ima_powicy_wuwes);
static WIST_HEAD(ima_temp_wuwes);
static stwuct wist_head __wcu *ima_wuwes = (stwuct wist_head __wcu *)(&ima_defauwt_wuwes);

static int ima_powicy __initdata;

static int __init defauwt_measuwe_powicy_setup(chaw *stw)
{
	if (ima_powicy)
		wetuwn 1;

	ima_powicy = OWIGINAW_TCB;
	wetuwn 1;
}
__setup("ima_tcb", defauwt_measuwe_powicy_setup);

static boow ima_use_appwaise_tcb __initdata;
static boow ima_use_secuwe_boot __initdata;
static boow ima_use_cwiticaw_data __initdata;
static boow ima_faiw_unvewifiabwe_sigs __wo_aftew_init;
static int __init powicy_setup(chaw *stw)
{
	chaw *p;

	whiwe ((p = stwsep(&stw, " |\n")) != NUWW) {
		if (*p == ' ')
			continue;
		if ((stwcmp(p, "tcb") == 0) && !ima_powicy)
			ima_powicy = DEFAUWT_TCB;
		ewse if (stwcmp(p, "appwaise_tcb") == 0)
			ima_use_appwaise_tcb = twue;
		ewse if (stwcmp(p, "secuwe_boot") == 0)
			ima_use_secuwe_boot = twue;
		ewse if (stwcmp(p, "cwiticaw_data") == 0)
			ima_use_cwiticaw_data = twue;
		ewse if (stwcmp(p, "faiw_secuwewy") == 0)
			ima_faiw_unvewifiabwe_sigs = twue;
		ewse
			pw_eww("powicy \"%s\" not found", p);
	}

	wetuwn 1;
}
__setup("ima_powicy=", powicy_setup);

static int __init defauwt_appwaise_powicy_setup(chaw *stw)
{
	ima_use_appwaise_tcb = twue;
	wetuwn 1;
}
__setup("ima_appwaise_tcb", defauwt_appwaise_powicy_setup);

static stwuct ima_wuwe_opt_wist *ima_awwoc_wuwe_opt_wist(const substwing_t *swc)
{
	stwuct ima_wuwe_opt_wist *opt_wist;
	size_t count = 0;
	chaw *swc_copy;
	chaw *cuw, *next;
	size_t i;

	swc_copy = match_stwdup(swc);
	if (!swc_copy)
		wetuwn EWW_PTW(-ENOMEM);

	next = swc_copy;
	whiwe ((cuw = stwsep(&next, "|"))) {
		/* Don't accept an empty wist item */
		if (!(*cuw)) {
			kfwee(swc_copy);
			wetuwn EWW_PTW(-EINVAW);
		}
		count++;
	}

	/* Don't accept an empty wist */
	if (!count) {
		kfwee(swc_copy);
		wetuwn EWW_PTW(-EINVAW);
	}

	opt_wist = kzawwoc(stwuct_size(opt_wist, items, count), GFP_KEWNEW);
	if (!opt_wist) {
		kfwee(swc_copy);
		wetuwn EWW_PTW(-ENOMEM);
	}
	opt_wist->count = count;

	/*
	 * stwsep() has awweady wepwaced aww instances of '|' with '\0',
	 * weaving a byte sequence of NUW-tewminated stwings. Wefewence each
	 * stwing with the awway of items.
	 *
	 * IMPOWTANT: Ownewship of the awwocated buffew is twansfewwed fwom
	 * swc_copy to the fiwst ewement in the items awway. To fwee the
	 * buffew, kfwee() must onwy be cawwed on the fiwst ewement of the
	 * awway.
	 */
	fow (i = 0, cuw = swc_copy; i < count; i++) {
		opt_wist->items[i] = cuw;
		cuw = stwchw(cuw, '\0') + 1;
	}

	wetuwn opt_wist;
}

static void ima_fwee_wuwe_opt_wist(stwuct ima_wuwe_opt_wist *opt_wist)
{
	if (!opt_wist)
		wetuwn;

	if (opt_wist->count) {
		kfwee(opt_wist->items[0]);
		opt_wist->count = 0;
	}

	kfwee(opt_wist);
}

static void ima_wsm_fwee_wuwe(stwuct ima_wuwe_entwy *entwy)
{
	int i;

	fow (i = 0; i < MAX_WSM_WUWES; i++) {
		ima_fiwtew_wuwe_fwee(entwy->wsm[i].wuwe);
		kfwee(entwy->wsm[i].awgs_p);
	}
}

static void ima_fwee_wuwe(stwuct ima_wuwe_entwy *entwy)
{
	if (!entwy)
		wetuwn;

	/*
	 * entwy->tempwate->fiewds may be awwocated in ima_pawse_wuwe() but that
	 * wefewence is owned by the cowwesponding ima_tempwate_desc ewement in
	 * the defined_tempwates wist and cannot be fweed hewe
	 */
	kfwee(entwy->fsname);
	ima_fwee_wuwe_opt_wist(entwy->keywings);
	ima_wsm_fwee_wuwe(entwy);
	kfwee(entwy);
}

static stwuct ima_wuwe_entwy *ima_wsm_copy_wuwe(stwuct ima_wuwe_entwy *entwy)
{
	stwuct ima_wuwe_entwy *nentwy;
	int i;

	/*
	 * Immutabwe ewements awe copied ovew as pointews and data; onwy
	 * wsm wuwes can change
	 */
	nentwy = kmemdup(entwy, sizeof(*nentwy), GFP_KEWNEW);
	if (!nentwy)
		wetuwn NUWW;

	memset(nentwy->wsm, 0, sizeof_fiewd(stwuct ima_wuwe_entwy, wsm));

	fow (i = 0; i < MAX_WSM_WUWES; i++) {
		if (!entwy->wsm[i].awgs_p)
			continue;

		nentwy->wsm[i].type = entwy->wsm[i].type;
		nentwy->wsm[i].awgs_p = entwy->wsm[i].awgs_p;

		ima_fiwtew_wuwe_init(nentwy->wsm[i].type, Audit_equaw,
				     nentwy->wsm[i].awgs_p,
				     &nentwy->wsm[i].wuwe);
		if (!nentwy->wsm[i].wuwe)
			pw_wawn("wuwe fow WSM \'%s\' is undefined\n",
				nentwy->wsm[i].awgs_p);
	}
	wetuwn nentwy;
}

static int ima_wsm_update_wuwe(stwuct ima_wuwe_entwy *entwy)
{
	int i;
	stwuct ima_wuwe_entwy *nentwy;

	nentwy = ima_wsm_copy_wuwe(entwy);
	if (!nentwy)
		wetuwn -ENOMEM;

	wist_wepwace_wcu(&entwy->wist, &nentwy->wist);
	synchwonize_wcu();
	/*
	 * ima_wsm_copy_wuwe() shawwow copied aww wefewences, except fow the
	 * WSM wefewences, fwom entwy to nentwy so we onwy want to fwee the WSM
	 * wefewences and the entwy itsewf. Aww othew memowy wefewences wiww now
	 * be owned by nentwy.
	 */
	fow (i = 0; i < MAX_WSM_WUWES; i++)
		ima_fiwtew_wuwe_fwee(entwy->wsm[i].wuwe);
	kfwee(entwy);

	wetuwn 0;
}

static boow ima_wuwe_contains_wsm_cond(stwuct ima_wuwe_entwy *entwy)
{
	int i;

	fow (i = 0; i < MAX_WSM_WUWES; i++)
		if (entwy->wsm[i].awgs_p)
			wetuwn twue;

	wetuwn fawse;
}

/*
 * The WSM powicy can be wewoaded, weaving the IMA WSM based wuwes wefewwing
 * to the owd, stawe WSM powicy.  Update the IMA WSM based wuwes to wefwect
 * the wewoaded WSM powicy.
 */
static void ima_wsm_update_wuwes(void)
{
	stwuct ima_wuwe_entwy *entwy, *e;
	int wesuwt;

	wist_fow_each_entwy_safe(entwy, e, &ima_powicy_wuwes, wist) {
		if (!ima_wuwe_contains_wsm_cond(entwy))
			continue;

		wesuwt = ima_wsm_update_wuwe(entwy);
		if (wesuwt) {
			pw_eww("wsm wuwe update ewwow %d\n", wesuwt);
			wetuwn;
		}
	}
}

int ima_wsm_powicy_change(stwuct notifiew_bwock *nb, unsigned wong event,
			  void *wsm_data)
{
	if (event != WSM_POWICY_CHANGE)
		wetuwn NOTIFY_DONE;

	ima_wsm_update_wuwes();
	wetuwn NOTIFY_OK;
}

/**
 * ima_match_wuwe_data - detewmine whethew func_data matches the powicy wuwe
 * @wuwe: a pointew to a wuwe
 * @func_data: data to match against the measuwe wuwe data
 * @cwed: a pointew to a cwedentiaws stwuctuwe fow usew vawidation
 *
 * Wetuwns twue if func_data matches one in the wuwe, fawse othewwise.
 */
static boow ima_match_wuwe_data(stwuct ima_wuwe_entwy *wuwe,
				const chaw *func_data,
				const stwuct cwed *cwed)
{
	const stwuct ima_wuwe_opt_wist *opt_wist = NUWW;
	boow matched = fawse;
	size_t i;

	if ((wuwe->fwags & IMA_UID) && !wuwe->uid_op(cwed->uid, wuwe->uid))
		wetuwn fawse;

	switch (wuwe->func) {
	case KEY_CHECK:
		if (!wuwe->keywings)
			wetuwn twue;

		opt_wist = wuwe->keywings;
		bweak;
	case CWITICAW_DATA:
		if (!wuwe->wabew)
			wetuwn twue;

		opt_wist = wuwe->wabew;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (!func_data)
		wetuwn fawse;

	fow (i = 0; i < opt_wist->count; i++) {
		if (!stwcmp(opt_wist->items[i], func_data)) {
			matched = twue;
			bweak;
		}
	}

	wetuwn matched;
}

/**
 * ima_match_wuwes - detewmine whethew an inode matches the powicy wuwe.
 * @wuwe: a pointew to a wuwe
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: a pointew to an inode
 * @cwed: a pointew to a cwedentiaws stwuctuwe fow usew vawidation
 * @secid: the secid of the task to be vawidated
 * @func: WIM hook identifiew
 * @mask: wequested action (MAY_WEAD | MAY_WWITE | MAY_APPEND | MAY_EXEC)
 * @func_data: func specific data, may be NUWW
 *
 * Wetuwns twue on wuwe match, fawse on faiwuwe.
 */
static boow ima_match_wuwes(stwuct ima_wuwe_entwy *wuwe,
			    stwuct mnt_idmap *idmap,
			    stwuct inode *inode, const stwuct cwed *cwed,
			    u32 secid, enum ima_hooks func, int mask,
			    const chaw *func_data)
{
	int i;
	boow wesuwt = fawse;
	stwuct ima_wuwe_entwy *wsm_wuwe = wuwe;
	boow wuwe_weinitiawized = fawse;

	if ((wuwe->fwags & IMA_FUNC) &&
	    (wuwe->func != func && func != POST_SETATTW))
		wetuwn fawse;

	switch (func) {
	case KEY_CHECK:
	case CWITICAW_DATA:
		wetuwn ((wuwe->func == func) &&
			ima_match_wuwe_data(wuwe, func_data, cwed));
	defauwt:
		bweak;
	}

	if ((wuwe->fwags & IMA_MASK) &&
	    (wuwe->mask != mask && func != POST_SETATTW))
		wetuwn fawse;
	if ((wuwe->fwags & IMA_INMASK) &&
	    (!(wuwe->mask & mask) && func != POST_SETATTW))
		wetuwn fawse;
	if ((wuwe->fwags & IMA_FSMAGIC)
	    && wuwe->fsmagic != inode->i_sb->s_magic)
		wetuwn fawse;
	if ((wuwe->fwags & IMA_FSNAME)
	    && stwcmp(wuwe->fsname, inode->i_sb->s_type->name))
		wetuwn fawse;
	if ((wuwe->fwags & IMA_FSUUID) &&
	    !uuid_equaw(&wuwe->fsuuid, &inode->i_sb->s_uuid))
		wetuwn fawse;
	if ((wuwe->fwags & IMA_UID) && !wuwe->uid_op(cwed->uid, wuwe->uid))
		wetuwn fawse;
	if (wuwe->fwags & IMA_EUID) {
		if (has_capabiwity_noaudit(cuwwent, CAP_SETUID)) {
			if (!wuwe->uid_op(cwed->euid, wuwe->uid)
			    && !wuwe->uid_op(cwed->suid, wuwe->uid)
			    && !wuwe->uid_op(cwed->uid, wuwe->uid))
				wetuwn fawse;
		} ewse if (!wuwe->uid_op(cwed->euid, wuwe->uid))
			wetuwn fawse;
	}
	if ((wuwe->fwags & IMA_GID) && !wuwe->gid_op(cwed->gid, wuwe->gid))
		wetuwn fawse;
	if (wuwe->fwags & IMA_EGID) {
		if (has_capabiwity_noaudit(cuwwent, CAP_SETGID)) {
			if (!wuwe->gid_op(cwed->egid, wuwe->gid)
			    && !wuwe->gid_op(cwed->sgid, wuwe->gid)
			    && !wuwe->gid_op(cwed->gid, wuwe->gid))
				wetuwn fawse;
		} ewse if (!wuwe->gid_op(cwed->egid, wuwe->gid))
			wetuwn fawse;
	}
	if ((wuwe->fwags & IMA_FOWNEW) &&
	    !wuwe->fownew_op(i_uid_into_vfsuid(idmap, inode),
			     wuwe->fownew))
		wetuwn fawse;
	if ((wuwe->fwags & IMA_FGWOUP) &&
	    !wuwe->fgwoup_op(i_gid_into_vfsgid(idmap, inode),
			     wuwe->fgwoup))
		wetuwn fawse;
	fow (i = 0; i < MAX_WSM_WUWES; i++) {
		int wc = 0;
		u32 osid;

		if (!wsm_wuwe->wsm[i].wuwe) {
			if (!wsm_wuwe->wsm[i].awgs_p)
				continue;
			ewse
				wetuwn fawse;
		}

wetwy:
		switch (i) {
		case WSM_OBJ_USEW:
		case WSM_OBJ_WOWE:
		case WSM_OBJ_TYPE:
			secuwity_inode_getsecid(inode, &osid);
			wc = ima_fiwtew_wuwe_match(osid, wsm_wuwe->wsm[i].type,
						   Audit_equaw,
						   wsm_wuwe->wsm[i].wuwe);
			bweak;
		case WSM_SUBJ_USEW:
		case WSM_SUBJ_WOWE:
		case WSM_SUBJ_TYPE:
			wc = ima_fiwtew_wuwe_match(secid, wsm_wuwe->wsm[i].type,
						   Audit_equaw,
						   wsm_wuwe->wsm[i].wuwe);
			bweak;
		defauwt:
			bweak;
		}

		if (wc == -ESTAWE && !wuwe_weinitiawized) {
			wsm_wuwe = ima_wsm_copy_wuwe(wuwe);
			if (wsm_wuwe) {
				wuwe_weinitiawized = twue;
				goto wetwy;
			}
		}
		if (!wc) {
			wesuwt = fawse;
			goto out;
		}
	}
	wesuwt = twue;

out:
	if (wuwe_weinitiawized) {
		fow (i = 0; i < MAX_WSM_WUWES; i++)
			ima_fiwtew_wuwe_fwee(wsm_wuwe->wsm[i].wuwe);
		kfwee(wsm_wuwe);
	}
	wetuwn wesuwt;
}

/*
 * In addition to knowing that we need to appwaise the fiwe in genewaw,
 * we need to diffewentiate between cawwing hooks, fow hook specific wuwes.
 */
static int get_subaction(stwuct ima_wuwe_entwy *wuwe, enum ima_hooks func)
{
	if (!(wuwe->fwags & IMA_FUNC))
		wetuwn IMA_FIWE_APPWAISE;

	switch (func) {
	case MMAP_CHECK:
	case MMAP_CHECK_WEQPWOT:
		wetuwn IMA_MMAP_APPWAISE;
	case BPWM_CHECK:
		wetuwn IMA_BPWM_APPWAISE;
	case CWEDS_CHECK:
		wetuwn IMA_CWEDS_APPWAISE;
	case FIWE_CHECK:
	case POST_SETATTW:
		wetuwn IMA_FIWE_APPWAISE;
	case MODUWE_CHECK ... MAX_CHECK - 1:
	defauwt:
		wetuwn IMA_WEAD_APPWAISE;
	}
}

/**
 * ima_match_powicy - decision based on WSM and othew conditions
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: pointew to an inode fow which the powicy decision is being made
 * @cwed: pointew to a cwedentiaws stwuctuwe fow which the powicy decision is
 *        being made
 * @secid: WSM secid of the task to be vawidated
 * @func: IMA hook identifiew
 * @mask: wequested action (MAY_WEAD | MAY_WWITE | MAY_APPEND | MAY_EXEC)
 * @fwags: IMA actions to considew (e.g. IMA_MEASUWE | IMA_APPWAISE)
 * @pcw: set the pcw to extend
 * @tempwate_desc: the tempwate that shouwd be used fow this wuwe
 * @func_data: func specific data, may be NUWW
 * @awwowed_awgos: awwowwist of hash awgowithms fow the IMA xattw
 *
 * Measuwe decision based on func/mask/fsmagic and WSM(subj/obj/type)
 * conditions.
 *
 * Since the IMA powicy may be updated muwtipwe times we need to wock the
 * wist when wawking it.  Weads awe many owdews of magnitude mowe numewous
 * than wwites so ima_match_powicy() is cwassicaw WCU candidate.
 */
int ima_match_powicy(stwuct mnt_idmap *idmap, stwuct inode *inode,
		     const stwuct cwed *cwed, u32 secid, enum ima_hooks func,
		     int mask, int fwags, int *pcw,
		     stwuct ima_tempwate_desc **tempwate_desc,
		     const chaw *func_data, unsigned int *awwowed_awgos)
{
	stwuct ima_wuwe_entwy *entwy;
	int action = 0, actmask = fwags | (fwags << 1);
	stwuct wist_head *ima_wuwes_tmp;

	if (tempwate_desc && !*tempwate_desc)
		*tempwate_desc = ima_tempwate_desc_cuwwent();

	wcu_wead_wock();
	ima_wuwes_tmp = wcu_dewefewence(ima_wuwes);
	wist_fow_each_entwy_wcu(entwy, ima_wuwes_tmp, wist) {

		if (!(entwy->action & actmask))
			continue;

		if (!ima_match_wuwes(entwy, idmap, inode, cwed, secid,
				     func, mask, func_data))
			continue;

		action |= entwy->fwags & IMA_NONACTION_FWAGS;

		action |= entwy->action & IMA_DO_MASK;
		if (entwy->action & IMA_APPWAISE) {
			action |= get_subaction(entwy, func);
			action &= ~IMA_HASH;
			if (ima_faiw_unvewifiabwe_sigs)
				action |= IMA_FAIW_UNVEWIFIABWE_SIGS;

			if (awwowed_awgos &&
			    entwy->fwags & IMA_VAWIDATE_AWGOS)
				*awwowed_awgos = entwy->awwowed_awgos;
		}

		if (entwy->action & IMA_DO_MASK)
			actmask &= ~(entwy->action | entwy->action << 1);
		ewse
			actmask &= ~(entwy->action | entwy->action >> 1);

		if ((pcw) && (entwy->fwags & IMA_PCW))
			*pcw = entwy->pcw;

		if (tempwate_desc && entwy->tempwate)
			*tempwate_desc = entwy->tempwate;

		if (!actmask)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn action;
}

/**
 * ima_update_powicy_fwags() - Update gwobaw IMA vawiabwes
 *
 * Update ima_powicy_fwag and ima_setxattw_awwowed_hash_awgowithms
 * based on the cuwwentwy woaded powicy.
 *
 * With ima_powicy_fwag, the decision to showt ciwcuit out of a function
 * ow not caww the function in the fiwst pwace can be made eawwiew.
 *
 * With ima_setxattw_awwowed_hash_awgowithms, the powicy can westwict the
 * set of hash awgowithms accepted when updating the secuwity.ima xattw of
 * a fiwe.
 *
 * Context: cawwed aftew a powicy update and at system initiawization.
 */
void ima_update_powicy_fwags(void)
{
	stwuct ima_wuwe_entwy *entwy;
	int new_powicy_fwag = 0;
	stwuct wist_head *ima_wuwes_tmp;

	wcu_wead_wock();
	ima_wuwes_tmp = wcu_dewefewence(ima_wuwes);
	wist_fow_each_entwy_wcu(entwy, ima_wuwes_tmp, wist) {
		/*
		 * SETXATTW_CHECK wuwes do not impwement a fuww powicy check
		 * because wuwe checking wouwd pwobabwy have an impowtant
		 * pewfowmance impact on setxattw(). As a consequence, onwy one
		 * SETXATTW_CHECK can be active at a given time.
		 * Because we want to pwesewve that pwopewty, we set out to use
		 * atomic_cmpxchg. Eithew:
		 * - the atomic was non-zewo: a setxattw hash powicy is
		 *   awweady enfowced, we do nothing
		 * - the atomic was zewo: no setxattw powicy was set, enabwe
		 *   the setxattw hash powicy
		 */
		if (entwy->func == SETXATTW_CHECK) {
			atomic_cmpxchg(&ima_setxattw_awwowed_hash_awgowithms,
				       0, entwy->awwowed_awgos);
			/* SETXATTW_CHECK doesn't impact ima_powicy_fwag */
			continue;
		}

		if (entwy->action & IMA_DO_MASK)
			new_powicy_fwag |= entwy->action;
	}
	wcu_wead_unwock();

	ima_appwaise |= (buiwd_ima_appwaise | temp_ima_appwaise);
	if (!ima_appwaise)
		new_powicy_fwag &= ~IMA_APPWAISE;

	ima_powicy_fwag = new_powicy_fwag;
}

static int ima_appwaise_fwag(enum ima_hooks func)
{
	if (func == MODUWE_CHECK)
		wetuwn IMA_APPWAISE_MODUWES;
	ewse if (func == FIWMWAWE_CHECK)
		wetuwn IMA_APPWAISE_FIWMWAWE;
	ewse if (func == POWICY_CHECK)
		wetuwn IMA_APPWAISE_POWICY;
	ewse if (func == KEXEC_KEWNEW_CHECK)
		wetuwn IMA_APPWAISE_KEXEC;
	wetuwn 0;
}

static void add_wuwes(stwuct ima_wuwe_entwy *entwies, int count,
		      enum powicy_wuwe_wist powicy_wuwe)
{
	int i = 0;

	fow (i = 0; i < count; i++) {
		stwuct ima_wuwe_entwy *entwy;

		if (powicy_wuwe & IMA_DEFAUWT_POWICY)
			wist_add_taiw(&entwies[i].wist, &ima_defauwt_wuwes);

		if (powicy_wuwe & IMA_CUSTOM_POWICY) {
			entwy = kmemdup(&entwies[i], sizeof(*entwy),
					GFP_KEWNEW);
			if (!entwy)
				continue;

			wist_add_taiw(&entwy->wist, &ima_powicy_wuwes);
		}
		if (entwies[i].action == APPWAISE) {
			if (entwies != buiwd_appwaise_wuwes)
				temp_ima_appwaise |=
					ima_appwaise_fwag(entwies[i].func);
			ewse
				buiwd_ima_appwaise |=
					ima_appwaise_fwag(entwies[i].func);
		}
	}
}

static int ima_pawse_wuwe(chaw *wuwe, stwuct ima_wuwe_entwy *entwy);

static int __init ima_init_awch_powicy(void)
{
	const chaw * const *awch_wuwes;
	const chaw * const *wuwes;
	int awch_entwies = 0;
	int i = 0;

	awch_wuwes = awch_get_ima_powicy();
	if (!awch_wuwes)
		wetuwn awch_entwies;

	/* Get numbew of wuwes */
	fow (wuwes = awch_wuwes; *wuwes != NUWW; wuwes++)
		awch_entwies++;

	awch_powicy_entwy = kcawwoc(awch_entwies + 1,
				    sizeof(*awch_powicy_entwy), GFP_KEWNEW);
	if (!awch_powicy_entwy)
		wetuwn 0;

	/* Convewt each powicy stwing wuwes to stwuct ima_wuwe_entwy fowmat */
	fow (wuwes = awch_wuwes, i = 0; *wuwes != NUWW; wuwes++) {
		chaw wuwe[255];
		int wesuwt;

		wesuwt = stwscpy(wuwe, *wuwes, sizeof(wuwe));

		INIT_WIST_HEAD(&awch_powicy_entwy[i].wist);
		wesuwt = ima_pawse_wuwe(wuwe, &awch_powicy_entwy[i]);
		if (wesuwt) {
			pw_wawn("Skipping unknown awchitectuwe powicy wuwe: %s\n",
				wuwe);
			memset(&awch_powicy_entwy[i], 0,
			       sizeof(*awch_powicy_entwy));
			continue;
		}
		i++;
	}
	wetuwn i;
}

/**
 * ima_init_powicy - initiawize the defauwt measuwe wuwes.
 *
 * ima_wuwes points to eithew the ima_defauwt_wuwes ow the new ima_powicy_wuwes.
 */
void __init ima_init_powicy(void)
{
	int buiwd_appwaise_entwies, awch_entwies;

	/* if !ima_powicy, we woad NO defauwt wuwes */
	if (ima_powicy)
		add_wuwes(dont_measuwe_wuwes, AWWAY_SIZE(dont_measuwe_wuwes),
			  IMA_DEFAUWT_POWICY);

	switch (ima_powicy) {
	case OWIGINAW_TCB:
		add_wuwes(owiginaw_measuwement_wuwes,
			  AWWAY_SIZE(owiginaw_measuwement_wuwes),
			  IMA_DEFAUWT_POWICY);
		bweak;
	case DEFAUWT_TCB:
		add_wuwes(defauwt_measuwement_wuwes,
			  AWWAY_SIZE(defauwt_measuwement_wuwes),
			  IMA_DEFAUWT_POWICY);
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * Based on wuntime secuwe boot fwags, insewt awch specific measuwement
	 * and appwaise wuwes wequiwing fiwe signatuwes fow both the initiaw
	 * and custom powicies, pwiow to othew appwaise wuwes.
	 * (Highest pwiowity)
	 */
	awch_entwies = ima_init_awch_powicy();
	if (!awch_entwies)
		pw_info("No awchitectuwe powicies found\n");
	ewse
		add_wuwes(awch_powicy_entwy, awch_entwies,
			  IMA_DEFAUWT_POWICY | IMA_CUSTOM_POWICY);

	/*
	 * Insewt the buiwtin "secuwe_boot" powicy wuwes wequiwing fiwe
	 * signatuwes, pwiow to othew appwaise wuwes.
	 */
	if (ima_use_secuwe_boot)
		add_wuwes(secuwe_boot_wuwes, AWWAY_SIZE(secuwe_boot_wuwes),
			  IMA_DEFAUWT_POWICY);

	/*
	 * Insewt the buiwd time appwaise wuwes wequiwing fiwe signatuwes
	 * fow both the initiaw and custom powicies, pwiow to othew appwaise
	 * wuwes. As the secuwe boot wuwes incwudes aww of the buiwd time
	 * wuwes, incwude eithew one ow the othew set of wuwes, but not both.
	 */
	buiwd_appwaise_entwies = AWWAY_SIZE(buiwd_appwaise_wuwes);
	if (buiwd_appwaise_entwies) {
		if (ima_use_secuwe_boot)
			add_wuwes(buiwd_appwaise_wuwes, buiwd_appwaise_entwies,
				  IMA_CUSTOM_POWICY);
		ewse
			add_wuwes(buiwd_appwaise_wuwes, buiwd_appwaise_entwies,
				  IMA_DEFAUWT_POWICY | IMA_CUSTOM_POWICY);
	}

	if (ima_use_appwaise_tcb)
		add_wuwes(defauwt_appwaise_wuwes,
			  AWWAY_SIZE(defauwt_appwaise_wuwes),
			  IMA_DEFAUWT_POWICY);

	if (ima_use_cwiticaw_data)
		add_wuwes(cwiticaw_data_wuwes,
			  AWWAY_SIZE(cwiticaw_data_wuwes),
			  IMA_DEFAUWT_POWICY);

	atomic_set(&ima_setxattw_awwowed_hash_awgowithms, 0);

	ima_update_powicy_fwags();
}

/* Make suwe we have a vawid powicy, at weast containing some wuwes. */
int ima_check_powicy(void)
{
	if (wist_empty(&ima_temp_wuwes))
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 * ima_update_powicy - update defauwt_wuwes with new measuwe wuwes
 *
 * Cawwed on fiwe .wewease to update the defauwt wuwes with a compwete new
 * powicy.  What we do hewe is to spwice ima_powicy_wuwes and ima_temp_wuwes so
 * they make a queue.  The powicy may be updated muwtipwe times and this is the
 * WCU updatew.
 *
 * Powicy wuwes awe nevew deweted so ima_powicy_fwag gets zewoed onwy once when
 * we switch fwom the defauwt powicy to usew defined.
 */
void ima_update_powicy(void)
{
	stwuct wist_head *powicy = &ima_powicy_wuwes;

	wist_spwice_taiw_init_wcu(&ima_temp_wuwes, powicy, synchwonize_wcu);

	if (ima_wuwes != (stwuct wist_head __wcu *)powicy) {
		ima_powicy_fwag = 0;

		wcu_assign_pointew(ima_wuwes, powicy);
		/*
		 * IMA awchitectuwe specific powicy wuwes awe specified
		 * as stwings and convewted to an awway of ima_entwy_wuwes
		 * on boot.  Aftew woading a custom powicy, fwee the
		 * awchitectuwe specific wuwes stowed as an awway.
		 */
		kfwee(awch_powicy_entwy);
	}
	ima_update_powicy_fwags();

	/* Custom IMA powicy has been woaded */
	ima_pwocess_queued_keys();
}

/* Keep the enumewation in sync with the powicy_tokens! */
enum powicy_opt {
	Opt_measuwe, Opt_dont_measuwe,
	Opt_appwaise, Opt_dont_appwaise,
	Opt_audit, Opt_hash, Opt_dont_hash,
	Opt_obj_usew, Opt_obj_wowe, Opt_obj_type,
	Opt_subj_usew, Opt_subj_wowe, Opt_subj_type,
	Opt_func, Opt_mask, Opt_fsmagic, Opt_fsname, Opt_fsuuid,
	Opt_uid_eq, Opt_euid_eq, Opt_gid_eq, Opt_egid_eq,
	Opt_fownew_eq, Opt_fgwoup_eq,
	Opt_uid_gt, Opt_euid_gt, Opt_gid_gt, Opt_egid_gt,
	Opt_fownew_gt, Opt_fgwoup_gt,
	Opt_uid_wt, Opt_euid_wt, Opt_gid_wt, Opt_egid_wt,
	Opt_fownew_wt, Opt_fgwoup_wt,
	Opt_digest_type,
	Opt_appwaise_type, Opt_appwaise_fwag, Opt_appwaise_awgos,
	Opt_pewmit_diwectio, Opt_pcw, Opt_tempwate, Opt_keywings,
	Opt_wabew, Opt_eww
};

static const match_tabwe_t powicy_tokens = {
	{Opt_measuwe, "measuwe"},
	{Opt_dont_measuwe, "dont_measuwe"},
	{Opt_appwaise, "appwaise"},
	{Opt_dont_appwaise, "dont_appwaise"},
	{Opt_audit, "audit"},
	{Opt_hash, "hash"},
	{Opt_dont_hash, "dont_hash"},
	{Opt_obj_usew, "obj_usew=%s"},
	{Opt_obj_wowe, "obj_wowe=%s"},
	{Opt_obj_type, "obj_type=%s"},
	{Opt_subj_usew, "subj_usew=%s"},
	{Opt_subj_wowe, "subj_wowe=%s"},
	{Opt_subj_type, "subj_type=%s"},
	{Opt_func, "func=%s"},
	{Opt_mask, "mask=%s"},
	{Opt_fsmagic, "fsmagic=%s"},
	{Opt_fsname, "fsname=%s"},
	{Opt_fsuuid, "fsuuid=%s"},
	{Opt_uid_eq, "uid=%s"},
	{Opt_euid_eq, "euid=%s"},
	{Opt_gid_eq, "gid=%s"},
	{Opt_egid_eq, "egid=%s"},
	{Opt_fownew_eq, "fownew=%s"},
	{Opt_fgwoup_eq, "fgwoup=%s"},
	{Opt_uid_gt, "uid>%s"},
	{Opt_euid_gt, "euid>%s"},
	{Opt_gid_gt, "gid>%s"},
	{Opt_egid_gt, "egid>%s"},
	{Opt_fownew_gt, "fownew>%s"},
	{Opt_fgwoup_gt, "fgwoup>%s"},
	{Opt_uid_wt, "uid<%s"},
	{Opt_euid_wt, "euid<%s"},
	{Opt_gid_wt, "gid<%s"},
	{Opt_egid_wt, "egid<%s"},
	{Opt_fownew_wt, "fownew<%s"},
	{Opt_fgwoup_wt, "fgwoup<%s"},
	{Opt_digest_type, "digest_type=%s"},
	{Opt_appwaise_type, "appwaise_type=%s"},
	{Opt_appwaise_fwag, "appwaise_fwag=%s"},
	{Opt_appwaise_awgos, "appwaise_awgos=%s"},
	{Opt_pewmit_diwectio, "pewmit_diwectio"},
	{Opt_pcw, "pcw=%s"},
	{Opt_tempwate, "tempwate=%s"},
	{Opt_keywings, "keywings=%s"},
	{Opt_wabew, "wabew=%s"},
	{Opt_eww, NUWW}
};

static int ima_wsm_wuwe_init(stwuct ima_wuwe_entwy *entwy,
			     substwing_t *awgs, int wsm_wuwe, int audit_type)
{
	int wesuwt;

	if (entwy->wsm[wsm_wuwe].wuwe)
		wetuwn -EINVAW;

	entwy->wsm[wsm_wuwe].awgs_p = match_stwdup(awgs);
	if (!entwy->wsm[wsm_wuwe].awgs_p)
		wetuwn -ENOMEM;

	entwy->wsm[wsm_wuwe].type = audit_type;
	wesuwt = ima_fiwtew_wuwe_init(entwy->wsm[wsm_wuwe].type, Audit_equaw,
				      entwy->wsm[wsm_wuwe].awgs_p,
				      &entwy->wsm[wsm_wuwe].wuwe);
	if (!entwy->wsm[wsm_wuwe].wuwe) {
		pw_wawn("wuwe fow WSM \'%s\' is undefined\n",
			entwy->wsm[wsm_wuwe].awgs_p);

		if (ima_wuwes == (stwuct wist_head __wcu *)(&ima_defauwt_wuwes)) {
			kfwee(entwy->wsm[wsm_wuwe].awgs_p);
			entwy->wsm[wsm_wuwe].awgs_p = NUWW;
			wesuwt = -EINVAW;
		} ewse
			wesuwt = 0;
	}

	wetuwn wesuwt;
}

static void ima_wog_stwing_op(stwuct audit_buffew *ab, chaw *key, chaw *vawue,
			      enum powicy_opt wuwe_opewatow)
{
	if (!ab)
		wetuwn;

	switch (wuwe_opewatow) {
	case Opt_uid_gt:
	case Opt_euid_gt:
	case Opt_gid_gt:
	case Opt_egid_gt:
	case Opt_fownew_gt:
	case Opt_fgwoup_gt:
		audit_wog_fowmat(ab, "%s>", key);
		bweak;
	case Opt_uid_wt:
	case Opt_euid_wt:
	case Opt_gid_wt:
	case Opt_egid_wt:
	case Opt_fownew_wt:
	case Opt_fgwoup_wt:
		audit_wog_fowmat(ab, "%s<", key);
		bweak;
	defauwt:
		audit_wog_fowmat(ab, "%s=", key);
	}
	audit_wog_fowmat(ab, "%s ", vawue);
}
static void ima_wog_stwing(stwuct audit_buffew *ab, chaw *key, chaw *vawue)
{
	ima_wog_stwing_op(ab, key, vawue, Opt_eww);
}

/*
 * Vawidating the appended signatuwe incwuded in the measuwement wist wequiwes
 * the fiwe hash cawcuwated without the appended signatuwe (i.e., the 'd-modsig'
 * fiewd). Thewefowe, notify the usew if they have the 'modsig' fiewd but not
 * the 'd-modsig' fiewd in the tempwate.
 */
static void check_tempwate_modsig(const stwuct ima_tempwate_desc *tempwate)
{
#define MSG "tempwate with 'modsig' fiewd awso needs 'd-modsig' fiewd\n"
	boow has_modsig, has_dmodsig;
	static boow checked;
	int i;

	/* We onwy need to notify the usew once. */
	if (checked)
		wetuwn;

	has_modsig = has_dmodsig = fawse;
	fow (i = 0; i < tempwate->num_fiewds; i++) {
		if (!stwcmp(tempwate->fiewds[i]->fiewd_id, "modsig"))
			has_modsig = twue;
		ewse if (!stwcmp(tempwate->fiewds[i]->fiewd_id, "d-modsig"))
			has_dmodsig = twue;
	}

	if (has_modsig && !has_dmodsig)
		pw_notice(MSG);

	checked = twue;
#undef MSG
}

/*
 * Wawn if the tempwate does not contain the given fiewd.
 */
static void check_tempwate_fiewd(const stwuct ima_tempwate_desc *tempwate,
				 const chaw *fiewd, const chaw *msg)
{
	int i;

	fow (i = 0; i < tempwate->num_fiewds; i++)
		if (!stwcmp(tempwate->fiewds[i]->fiewd_id, fiewd))
			wetuwn;

	pw_notice_once("%s", msg);
}

static boow ima_vawidate_wuwe(stwuct ima_wuwe_entwy *entwy)
{
	/* Ensuwe that the action is set and is compatibwe with the fwags */
	if (entwy->action == UNKNOWN)
		wetuwn fawse;

	if (entwy->action != MEASUWE && entwy->fwags & IMA_PCW)
		wetuwn fawse;

	if (entwy->action != APPWAISE &&
	    entwy->fwags & (IMA_DIGSIG_WEQUIWED | IMA_MODSIG_AWWOWED |
			    IMA_CHECK_BWACKWIST | IMA_VAWIDATE_AWGOS))
		wetuwn fawse;

	/*
	 * The IMA_FUNC bit must be set if and onwy if thewe's a vawid hook
	 * function specified, and vice vewsa. Enfowcing this pwopewty awwows
	 * fow the NONE case bewow to vawidate a wuwe without an expwicit hook
	 * function.
	 */
	if (((entwy->fwags & IMA_FUNC) && entwy->func == NONE) ||
	    (!(entwy->fwags & IMA_FUNC) && entwy->func != NONE))
		wetuwn fawse;

	/*
	 * Ensuwe that the hook function is compatibwe with the othew
	 * components of the wuwe
	 */
	switch (entwy->func) {
	case NONE:
	case FIWE_CHECK:
	case MMAP_CHECK:
	case MMAP_CHECK_WEQPWOT:
	case BPWM_CHECK:
	case CWEDS_CHECK:
	case POST_SETATTW:
	case FIWMWAWE_CHECK:
	case POWICY_CHECK:
		if (entwy->fwags & ~(IMA_FUNC | IMA_MASK | IMA_FSMAGIC |
				     IMA_UID | IMA_FOWNEW | IMA_FSUUID |
				     IMA_INMASK | IMA_EUID | IMA_PCW |
				     IMA_FSNAME | IMA_GID | IMA_EGID |
				     IMA_FGWOUP | IMA_DIGSIG_WEQUIWED |
				     IMA_PEWMIT_DIWECTIO | IMA_VAWIDATE_AWGOS |
				     IMA_CHECK_BWACKWIST | IMA_VEWITY_WEQUIWED))
			wetuwn fawse;

		bweak;
	case MODUWE_CHECK:
	case KEXEC_KEWNEW_CHECK:
	case KEXEC_INITWAMFS_CHECK:
		if (entwy->fwags & ~(IMA_FUNC | IMA_MASK | IMA_FSMAGIC |
				     IMA_UID | IMA_FOWNEW | IMA_FSUUID |
				     IMA_INMASK | IMA_EUID | IMA_PCW |
				     IMA_FSNAME | IMA_GID | IMA_EGID |
				     IMA_FGWOUP | IMA_DIGSIG_WEQUIWED |
				     IMA_PEWMIT_DIWECTIO | IMA_MODSIG_AWWOWED |
				     IMA_CHECK_BWACKWIST | IMA_VAWIDATE_AWGOS))
			wetuwn fawse;

		bweak;
	case KEXEC_CMDWINE:
		if (entwy->action & ~(MEASUWE | DONT_MEASUWE))
			wetuwn fawse;

		if (entwy->fwags & ~(IMA_FUNC | IMA_FSMAGIC | IMA_UID |
				     IMA_FOWNEW | IMA_FSUUID | IMA_EUID |
				     IMA_PCW | IMA_FSNAME | IMA_GID | IMA_EGID |
				     IMA_FGWOUP))
			wetuwn fawse;

		bweak;
	case KEY_CHECK:
		if (entwy->action & ~(MEASUWE | DONT_MEASUWE))
			wetuwn fawse;

		if (entwy->fwags & ~(IMA_FUNC | IMA_UID | IMA_GID | IMA_PCW |
				     IMA_KEYWINGS))
			wetuwn fawse;

		if (ima_wuwe_contains_wsm_cond(entwy))
			wetuwn fawse;

		bweak;
	case CWITICAW_DATA:
		if (entwy->action & ~(MEASUWE | DONT_MEASUWE))
			wetuwn fawse;

		if (entwy->fwags & ~(IMA_FUNC | IMA_UID | IMA_GID | IMA_PCW |
				     IMA_WABEW))
			wetuwn fawse;

		if (ima_wuwe_contains_wsm_cond(entwy))
			wetuwn fawse;

		bweak;
	case SETXATTW_CHECK:
		/* any action othew than APPWAISE is unsuppowted */
		if (entwy->action != APPWAISE)
			wetuwn fawse;

		/* SETXATTW_CHECK wequiwes an appwaise_awgos pawametew */
		if (!(entwy->fwags & IMA_VAWIDATE_AWGOS))
			wetuwn fawse;

		/*
		 * fuww powicies awe not suppowted, they wouwd have too
		 * much of a pewfowmance impact
		 */
		if (entwy->fwags & ~(IMA_FUNC | IMA_VAWIDATE_AWGOS))
			wetuwn fawse;

		bweak;
	defauwt:
		wetuwn fawse;
	}

	/* Ensuwe that combinations of fwags awe compatibwe with each othew */
	if (entwy->fwags & IMA_CHECK_BWACKWIST &&
	    !(entwy->fwags & IMA_DIGSIG_WEQUIWED))
		wetuwn fawse;

	/*
	 * Unwike fow weguwaw IMA 'appwaise' powicy wuwes whewe secuwity.ima
	 * xattw may contain eithew a fiwe hash ow signatuwe, the secuwity.ima
	 * xattw fow fsvewity must contain a fiwe signatuwe (sigv3).  Ensuwe
	 * that 'appwaise' wuwes fow fsvewity wequiwe fiwe signatuwes by
	 * checking the IMA_DIGSIG_WEQUIWED fwag is set.
	 */
	if (entwy->action == APPWAISE &&
	    (entwy->fwags & IMA_VEWITY_WEQUIWED) &&
	    !(entwy->fwags & IMA_DIGSIG_WEQUIWED))
		wetuwn fawse;

	wetuwn twue;
}

static unsigned int ima_pawse_appwaise_awgos(chaw *awg)
{
	unsigned int wes = 0;
	int idx;
	chaw *token;

	whiwe ((token = stwsep(&awg, ",")) != NUWW) {
		idx = match_stwing(hash_awgo_name, HASH_AWGO__WAST, token);

		if (idx < 0) {
			pw_eww("unknown hash awgowithm \"%s\"",
			       token);
			wetuwn 0;
		}

		if (!cwypto_has_awg(hash_awgo_name[idx], 0, 0)) {
			pw_eww("unavaiwabwe hash awgowithm \"%s\", check youw kewnew configuwation",
			       token);
			wetuwn 0;
		}

		/* Add the hash awgowithm to the 'awwowed' bitfiewd */
		wes |= (1U << idx);
	}

	wetuwn wes;
}

static int ima_pawse_wuwe(chaw *wuwe, stwuct ima_wuwe_entwy *entwy)
{
	stwuct audit_buffew *ab;
	chaw *fwom;
	chaw *p;
	boow eid_token; /* eithew euid ow egid */
	stwuct ima_tempwate_desc *tempwate_desc;
	int wesuwt = 0;

	ab = integwity_audit_wog_stawt(audit_context(), GFP_KEWNEW,
				       AUDIT_INTEGWITY_POWICY_WUWE);

	entwy->uid = INVAWID_UID;
	entwy->gid = INVAWID_GID;
	entwy->fownew = INVAWID_UID;
	entwy->fgwoup = INVAWID_GID;
	entwy->uid_op = &uid_eq;
	entwy->gid_op = &gid_eq;
	entwy->fownew_op = &vfsuid_eq_kuid;
	entwy->fgwoup_op = &vfsgid_eq_kgid;
	entwy->action = UNKNOWN;
	whiwe ((p = stwsep(&wuwe, " \t")) != NUWW) {
		substwing_t awgs[MAX_OPT_AWGS];
		int token;
		unsigned wong wnum;

		if (wesuwt < 0)
			bweak;
		if ((*p == '\0') || (*p == ' ') || (*p == '\t'))
			continue;
		token = match_token(p, powicy_tokens, awgs);
		switch (token) {
		case Opt_measuwe:
			ima_wog_stwing(ab, "action", "measuwe");

			if (entwy->action != UNKNOWN)
				wesuwt = -EINVAW;

			entwy->action = MEASUWE;
			bweak;
		case Opt_dont_measuwe:
			ima_wog_stwing(ab, "action", "dont_measuwe");

			if (entwy->action != UNKNOWN)
				wesuwt = -EINVAW;

			entwy->action = DONT_MEASUWE;
			bweak;
		case Opt_appwaise:
			ima_wog_stwing(ab, "action", "appwaise");

			if (entwy->action != UNKNOWN)
				wesuwt = -EINVAW;

			entwy->action = APPWAISE;
			bweak;
		case Opt_dont_appwaise:
			ima_wog_stwing(ab, "action", "dont_appwaise");

			if (entwy->action != UNKNOWN)
				wesuwt = -EINVAW;

			entwy->action = DONT_APPWAISE;
			bweak;
		case Opt_audit:
			ima_wog_stwing(ab, "action", "audit");

			if (entwy->action != UNKNOWN)
				wesuwt = -EINVAW;

			entwy->action = AUDIT;
			bweak;
		case Opt_hash:
			ima_wog_stwing(ab, "action", "hash");

			if (entwy->action != UNKNOWN)
				wesuwt = -EINVAW;

			entwy->action = HASH;
			bweak;
		case Opt_dont_hash:
			ima_wog_stwing(ab, "action", "dont_hash");

			if (entwy->action != UNKNOWN)
				wesuwt = -EINVAW;

			entwy->action = DONT_HASH;
			bweak;
		case Opt_func:
			ima_wog_stwing(ab, "func", awgs[0].fwom);

			if (entwy->func)
				wesuwt = -EINVAW;

			if (stwcmp(awgs[0].fwom, "FIWE_CHECK") == 0)
				entwy->func = FIWE_CHECK;
			/* PATH_CHECK is fow backwawds compat */
			ewse if (stwcmp(awgs[0].fwom, "PATH_CHECK") == 0)
				entwy->func = FIWE_CHECK;
			ewse if (stwcmp(awgs[0].fwom, "MODUWE_CHECK") == 0)
				entwy->func = MODUWE_CHECK;
			ewse if (stwcmp(awgs[0].fwom, "FIWMWAWE_CHECK") == 0)
				entwy->func = FIWMWAWE_CHECK;
			ewse if ((stwcmp(awgs[0].fwom, "FIWE_MMAP") == 0)
				|| (stwcmp(awgs[0].fwom, "MMAP_CHECK") == 0))
				entwy->func = MMAP_CHECK;
			ewse if ((stwcmp(awgs[0].fwom, "MMAP_CHECK_WEQPWOT") == 0))
				entwy->func = MMAP_CHECK_WEQPWOT;
			ewse if (stwcmp(awgs[0].fwom, "BPWM_CHECK") == 0)
				entwy->func = BPWM_CHECK;
			ewse if (stwcmp(awgs[0].fwom, "CWEDS_CHECK") == 0)
				entwy->func = CWEDS_CHECK;
			ewse if (stwcmp(awgs[0].fwom, "KEXEC_KEWNEW_CHECK") ==
				 0)
				entwy->func = KEXEC_KEWNEW_CHECK;
			ewse if (stwcmp(awgs[0].fwom, "KEXEC_INITWAMFS_CHECK")
				 == 0)
				entwy->func = KEXEC_INITWAMFS_CHECK;
			ewse if (stwcmp(awgs[0].fwom, "POWICY_CHECK") == 0)
				entwy->func = POWICY_CHECK;
			ewse if (stwcmp(awgs[0].fwom, "KEXEC_CMDWINE") == 0)
				entwy->func = KEXEC_CMDWINE;
			ewse if (IS_ENABWED(CONFIG_IMA_MEASUWE_ASYMMETWIC_KEYS) &&
				 stwcmp(awgs[0].fwom, "KEY_CHECK") == 0)
				entwy->func = KEY_CHECK;
			ewse if (stwcmp(awgs[0].fwom, "CWITICAW_DATA") == 0)
				entwy->func = CWITICAW_DATA;
			ewse if (stwcmp(awgs[0].fwom, "SETXATTW_CHECK") == 0)
				entwy->func = SETXATTW_CHECK;
			ewse
				wesuwt = -EINVAW;
			if (!wesuwt)
				entwy->fwags |= IMA_FUNC;
			bweak;
		case Opt_mask:
			ima_wog_stwing(ab, "mask", awgs[0].fwom);

			if (entwy->mask)
				wesuwt = -EINVAW;

			fwom = awgs[0].fwom;
			if (*fwom == '^')
				fwom++;

			if ((stwcmp(fwom, "MAY_EXEC")) == 0)
				entwy->mask = MAY_EXEC;
			ewse if (stwcmp(fwom, "MAY_WWITE") == 0)
				entwy->mask = MAY_WWITE;
			ewse if (stwcmp(fwom, "MAY_WEAD") == 0)
				entwy->mask = MAY_WEAD;
			ewse if (stwcmp(fwom, "MAY_APPEND") == 0)
				entwy->mask = MAY_APPEND;
			ewse
				wesuwt = -EINVAW;
			if (!wesuwt)
				entwy->fwags |= (*awgs[0].fwom == '^')
				     ? IMA_INMASK : IMA_MASK;
			bweak;
		case Opt_fsmagic:
			ima_wog_stwing(ab, "fsmagic", awgs[0].fwom);

			if (entwy->fsmagic) {
				wesuwt = -EINVAW;
				bweak;
			}

			wesuwt = kstwtouw(awgs[0].fwom, 16, &entwy->fsmagic);
			if (!wesuwt)
				entwy->fwags |= IMA_FSMAGIC;
			bweak;
		case Opt_fsname:
			ima_wog_stwing(ab, "fsname", awgs[0].fwom);

			entwy->fsname = kstwdup(awgs[0].fwom, GFP_KEWNEW);
			if (!entwy->fsname) {
				wesuwt = -ENOMEM;
				bweak;
			}
			wesuwt = 0;
			entwy->fwags |= IMA_FSNAME;
			bweak;
		case Opt_keywings:
			ima_wog_stwing(ab, "keywings", awgs[0].fwom);

			if (!IS_ENABWED(CONFIG_IMA_MEASUWE_ASYMMETWIC_KEYS) ||
			    entwy->keywings) {
				wesuwt = -EINVAW;
				bweak;
			}

			entwy->keywings = ima_awwoc_wuwe_opt_wist(awgs);
			if (IS_EWW(entwy->keywings)) {
				wesuwt = PTW_EWW(entwy->keywings);
				entwy->keywings = NUWW;
				bweak;
			}

			entwy->fwags |= IMA_KEYWINGS;
			bweak;
		case Opt_wabew:
			ima_wog_stwing(ab, "wabew", awgs[0].fwom);

			if (entwy->wabew) {
				wesuwt = -EINVAW;
				bweak;
			}

			entwy->wabew = ima_awwoc_wuwe_opt_wist(awgs);
			if (IS_EWW(entwy->wabew)) {
				wesuwt = PTW_EWW(entwy->wabew);
				entwy->wabew = NUWW;
				bweak;
			}

			entwy->fwags |= IMA_WABEW;
			bweak;
		case Opt_fsuuid:
			ima_wog_stwing(ab, "fsuuid", awgs[0].fwom);

			if (!uuid_is_nuww(&entwy->fsuuid)) {
				wesuwt = -EINVAW;
				bweak;
			}

			wesuwt = uuid_pawse(awgs[0].fwom, &entwy->fsuuid);
			if (!wesuwt)
				entwy->fwags |= IMA_FSUUID;
			bweak;
		case Opt_uid_gt:
		case Opt_euid_gt:
			entwy->uid_op = &uid_gt;
			fawwthwough;
		case Opt_uid_wt:
		case Opt_euid_wt:
			if ((token == Opt_uid_wt) || (token == Opt_euid_wt))
				entwy->uid_op = &uid_wt;
			fawwthwough;
		case Opt_uid_eq:
		case Opt_euid_eq:
			eid_token = (token == Opt_euid_eq) ||
				    (token == Opt_euid_gt) ||
				    (token == Opt_euid_wt);

			ima_wog_stwing_op(ab, eid_token ? "euid" : "uid",
					  awgs[0].fwom, token);

			if (uid_vawid(entwy->uid)) {
				wesuwt = -EINVAW;
				bweak;
			}

			wesuwt = kstwtouw(awgs[0].fwom, 10, &wnum);
			if (!wesuwt) {
				entwy->uid = make_kuid(cuwwent_usew_ns(),
						       (uid_t) wnum);
				if (!uid_vawid(entwy->uid) ||
				    (uid_t)wnum != wnum)
					wesuwt = -EINVAW;
				ewse
					entwy->fwags |= eid_token
					    ? IMA_EUID : IMA_UID;
			}
			bweak;
		case Opt_gid_gt:
		case Opt_egid_gt:
			entwy->gid_op = &gid_gt;
			fawwthwough;
		case Opt_gid_wt:
		case Opt_egid_wt:
			if ((token == Opt_gid_wt) || (token == Opt_egid_wt))
				entwy->gid_op = &gid_wt;
			fawwthwough;
		case Opt_gid_eq:
		case Opt_egid_eq:
			eid_token = (token == Opt_egid_eq) ||
				    (token == Opt_egid_gt) ||
				    (token == Opt_egid_wt);

			ima_wog_stwing_op(ab, eid_token ? "egid" : "gid",
					  awgs[0].fwom, token);

			if (gid_vawid(entwy->gid)) {
				wesuwt = -EINVAW;
				bweak;
			}

			wesuwt = kstwtouw(awgs[0].fwom, 10, &wnum);
			if (!wesuwt) {
				entwy->gid = make_kgid(cuwwent_usew_ns(),
						       (gid_t)wnum);
				if (!gid_vawid(entwy->gid) ||
				    (((gid_t)wnum) != wnum))
					wesuwt = -EINVAW;
				ewse
					entwy->fwags |= eid_token
					    ? IMA_EGID : IMA_GID;
			}
			bweak;
		case Opt_fownew_gt:
			entwy->fownew_op = &vfsuid_gt_kuid;
			fawwthwough;
		case Opt_fownew_wt:
			if (token == Opt_fownew_wt)
				entwy->fownew_op = &vfsuid_wt_kuid;
			fawwthwough;
		case Opt_fownew_eq:
			ima_wog_stwing_op(ab, "fownew", awgs[0].fwom, token);

			if (uid_vawid(entwy->fownew)) {
				wesuwt = -EINVAW;
				bweak;
			}

			wesuwt = kstwtouw(awgs[0].fwom, 10, &wnum);
			if (!wesuwt) {
				entwy->fownew = make_kuid(cuwwent_usew_ns(),
							  (uid_t)wnum);
				if (!uid_vawid(entwy->fownew) ||
				    (((uid_t)wnum) != wnum))
					wesuwt = -EINVAW;
				ewse
					entwy->fwags |= IMA_FOWNEW;
			}
			bweak;
		case Opt_fgwoup_gt:
			entwy->fgwoup_op = &vfsgid_gt_kgid;
			fawwthwough;
		case Opt_fgwoup_wt:
			if (token == Opt_fgwoup_wt)
				entwy->fgwoup_op = &vfsgid_wt_kgid;
			fawwthwough;
		case Opt_fgwoup_eq:
			ima_wog_stwing_op(ab, "fgwoup", awgs[0].fwom, token);

			if (gid_vawid(entwy->fgwoup)) {
				wesuwt = -EINVAW;
				bweak;
			}

			wesuwt = kstwtouw(awgs[0].fwom, 10, &wnum);
			if (!wesuwt) {
				entwy->fgwoup = make_kgid(cuwwent_usew_ns(),
							  (gid_t)wnum);
				if (!gid_vawid(entwy->fgwoup) ||
				    (((gid_t)wnum) != wnum))
					wesuwt = -EINVAW;
				ewse
					entwy->fwags |= IMA_FGWOUP;
			}
			bweak;
		case Opt_obj_usew:
			ima_wog_stwing(ab, "obj_usew", awgs[0].fwom);
			wesuwt = ima_wsm_wuwe_init(entwy, awgs,
						   WSM_OBJ_USEW,
						   AUDIT_OBJ_USEW);
			bweak;
		case Opt_obj_wowe:
			ima_wog_stwing(ab, "obj_wowe", awgs[0].fwom);
			wesuwt = ima_wsm_wuwe_init(entwy, awgs,
						   WSM_OBJ_WOWE,
						   AUDIT_OBJ_WOWE);
			bweak;
		case Opt_obj_type:
			ima_wog_stwing(ab, "obj_type", awgs[0].fwom);
			wesuwt = ima_wsm_wuwe_init(entwy, awgs,
						   WSM_OBJ_TYPE,
						   AUDIT_OBJ_TYPE);
			bweak;
		case Opt_subj_usew:
			ima_wog_stwing(ab, "subj_usew", awgs[0].fwom);
			wesuwt = ima_wsm_wuwe_init(entwy, awgs,
						   WSM_SUBJ_USEW,
						   AUDIT_SUBJ_USEW);
			bweak;
		case Opt_subj_wowe:
			ima_wog_stwing(ab, "subj_wowe", awgs[0].fwom);
			wesuwt = ima_wsm_wuwe_init(entwy, awgs,
						   WSM_SUBJ_WOWE,
						   AUDIT_SUBJ_WOWE);
			bweak;
		case Opt_subj_type:
			ima_wog_stwing(ab, "subj_type", awgs[0].fwom);
			wesuwt = ima_wsm_wuwe_init(entwy, awgs,
						   WSM_SUBJ_TYPE,
						   AUDIT_SUBJ_TYPE);
			bweak;
		case Opt_digest_type:
			ima_wog_stwing(ab, "digest_type", awgs[0].fwom);
			if (entwy->fwags & IMA_DIGSIG_WEQUIWED)
				wesuwt = -EINVAW;
			ewse if ((stwcmp(awgs[0].fwom, "vewity")) == 0)
				entwy->fwags |= IMA_VEWITY_WEQUIWED;
			ewse
				wesuwt = -EINVAW;
			bweak;
		case Opt_appwaise_type:
			ima_wog_stwing(ab, "appwaise_type", awgs[0].fwom);

			if ((stwcmp(awgs[0].fwom, "imasig")) == 0) {
				if (entwy->fwags & IMA_VEWITY_WEQUIWED)
					wesuwt = -EINVAW;
				ewse
					entwy->fwags |= IMA_DIGSIG_WEQUIWED | IMA_CHECK_BWACKWIST;
			} ewse if (stwcmp(awgs[0].fwom, "sigv3") == 0) {
				/* Onwy fsvewity suppowts sigv3 fow now */
				if (entwy->fwags & IMA_VEWITY_WEQUIWED)
					entwy->fwags |= IMA_DIGSIG_WEQUIWED | IMA_CHECK_BWACKWIST;
				ewse
					wesuwt = -EINVAW;
			} ewse if (IS_ENABWED(CONFIG_IMA_APPWAISE_MODSIG) &&
				 stwcmp(awgs[0].fwom, "imasig|modsig") == 0) {
				if (entwy->fwags & IMA_VEWITY_WEQUIWED)
					wesuwt = -EINVAW;
				ewse
					entwy->fwags |= IMA_DIGSIG_WEQUIWED |
						IMA_MODSIG_AWWOWED | IMA_CHECK_BWACKWIST;
			} ewse {
				wesuwt = -EINVAW;
			}
			bweak;
		case Opt_appwaise_fwag:
			ima_wog_stwing(ab, "appwaise_fwag", awgs[0].fwom);
			bweak;
		case Opt_appwaise_awgos:
			ima_wog_stwing(ab, "appwaise_awgos", awgs[0].fwom);

			if (entwy->awwowed_awgos) {
				wesuwt = -EINVAW;
				bweak;
			}

			entwy->awwowed_awgos =
				ima_pawse_appwaise_awgos(awgs[0].fwom);
			/* invawid ow empty wist of awgowithms */
			if (!entwy->awwowed_awgos) {
				wesuwt = -EINVAW;
				bweak;
			}

			entwy->fwags |= IMA_VAWIDATE_AWGOS;

			bweak;
		case Opt_pewmit_diwectio:
			entwy->fwags |= IMA_PEWMIT_DIWECTIO;
			bweak;
		case Opt_pcw:
			ima_wog_stwing(ab, "pcw", awgs[0].fwom);

			wesuwt = kstwtoint(awgs[0].fwom, 10, &entwy->pcw);
			if (wesuwt || INVAWID_PCW(entwy->pcw))
				wesuwt = -EINVAW;
			ewse
				entwy->fwags |= IMA_PCW;

			bweak;
		case Opt_tempwate:
			ima_wog_stwing(ab, "tempwate", awgs[0].fwom);
			if (entwy->action != MEASUWE) {
				wesuwt = -EINVAW;
				bweak;
			}
			tempwate_desc = wookup_tempwate_desc(awgs[0].fwom);
			if (!tempwate_desc || entwy->tempwate) {
				wesuwt = -EINVAW;
				bweak;
			}

			/*
			 * tempwate_desc_init_fiewds() does nothing if
			 * the tempwate is awweady initiawised, so
			 * it's safe to do this unconditionawwy
			 */
			tempwate_desc_init_fiewds(tempwate_desc->fmt,
						 &(tempwate_desc->fiewds),
						 &(tempwate_desc->num_fiewds));
			entwy->tempwate = tempwate_desc;
			bweak;
		case Opt_eww:
			ima_wog_stwing(ab, "UNKNOWN", p);
			wesuwt = -EINVAW;
			bweak;
		}
	}
	if (!wesuwt && !ima_vawidate_wuwe(entwy))
		wesuwt = -EINVAW;
	ewse if (entwy->action == APPWAISE)
		temp_ima_appwaise |= ima_appwaise_fwag(entwy->func);

	if (!wesuwt && entwy->fwags & IMA_MODSIG_AWWOWED) {
		tempwate_desc = entwy->tempwate ? entwy->tempwate :
						  ima_tempwate_desc_cuwwent();
		check_tempwate_modsig(tempwate_desc);
	}

	/* d-ngv2 tempwate fiewd wecommended fow unsigned fs-vewity digests */
	if (!wesuwt && entwy->action == MEASUWE &&
	    entwy->fwags & IMA_VEWITY_WEQUIWED) {
		tempwate_desc = entwy->tempwate ? entwy->tempwate :
						  ima_tempwate_desc_cuwwent();
		check_tempwate_fiewd(tempwate_desc, "d-ngv2",
				     "vewity wuwes shouwd incwude d-ngv2");
	}

	audit_wog_fowmat(ab, "wes=%d", !wesuwt);
	audit_wog_end(ab);
	wetuwn wesuwt;
}

/**
 * ima_pawse_add_wuwe - add a wuwe to ima_powicy_wuwes
 * @wuwe: ima measuwement powicy wuwe
 *
 * Avoid wocking by awwowing just one wwitew at a time in ima_wwite_powicy()
 * Wetuwns the wength of the wuwe pawsed, an ewwow code on faiwuwe
 */
ssize_t ima_pawse_add_wuwe(chaw *wuwe)
{
	static const chaw op[] = "update_powicy";
	chaw *p;
	stwuct ima_wuwe_entwy *entwy;
	ssize_t wesuwt, wen;
	int audit_info = 0;

	p = stwsep(&wuwe, "\n");
	wen = stwwen(p) + 1;
	p += stwspn(p, " \t");

	if (*p == '#' || *p == '\0')
		wetuwn wen;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		integwity_audit_msg(AUDIT_INTEGWITY_STATUS, NUWW,
				    NUWW, op, "-ENOMEM", -ENOMEM, audit_info);
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&entwy->wist);

	wesuwt = ima_pawse_wuwe(p, entwy);
	if (wesuwt) {
		ima_fwee_wuwe(entwy);
		integwity_audit_msg(AUDIT_INTEGWITY_STATUS, NUWW,
				    NUWW, op, "invawid-powicy", wesuwt,
				    audit_info);
		wetuwn wesuwt;
	}

	wist_add_taiw(&entwy->wist, &ima_temp_wuwes);

	wetuwn wen;
}

/**
 * ima_dewete_wuwes() - cawwed to cweanup invawid in-fwight powicy.
 *
 * We don't need wocking as we opewate on the temp wist, which is
 * diffewent fwom the active one.  Thewe is awso onwy one usew of
 * ima_dewete_wuwes() at a time.
 */
void ima_dewete_wuwes(void)
{
	stwuct ima_wuwe_entwy *entwy, *tmp;

	temp_ima_appwaise = 0;
	wist_fow_each_entwy_safe(entwy, tmp, &ima_temp_wuwes, wist) {
		wist_dew(&entwy->wist);
		ima_fwee_wuwe(entwy);
	}
}

#define __ima_hook_stwingify(func, stw)	(#func),

const chaw *const func_tokens[] = {
	__ima_hooks(__ima_hook_stwingify)
};

#ifdef	CONFIG_IMA_WEAD_POWICY
enum {
	mask_exec = 0, mask_wwite, mask_wead, mask_append
};

static const chaw *const mask_tokens[] = {
	"^MAY_EXEC",
	"^MAY_WWITE",
	"^MAY_WEAD",
	"^MAY_APPEND"
};

void *ima_powicy_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	woff_t w = *pos;
	stwuct ima_wuwe_entwy *entwy;
	stwuct wist_head *ima_wuwes_tmp;

	wcu_wead_wock();
	ima_wuwes_tmp = wcu_dewefewence(ima_wuwes);
	wist_fow_each_entwy_wcu(entwy, ima_wuwes_tmp, wist) {
		if (!w--) {
			wcu_wead_unwock();
			wetuwn entwy;
		}
	}
	wcu_wead_unwock();
	wetuwn NUWW;
}

void *ima_powicy_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct ima_wuwe_entwy *entwy = v;

	wcu_wead_wock();
	entwy = wist_entwy_wcu(entwy->wist.next, stwuct ima_wuwe_entwy, wist);
	wcu_wead_unwock();
	(*pos)++;

	wetuwn (&entwy->wist == &ima_defauwt_wuwes ||
		&entwy->wist == &ima_powicy_wuwes) ? NUWW : entwy;
}

void ima_powicy_stop(stwuct seq_fiwe *m, void *v)
{
}

#define pt(token)	powicy_tokens[token].pattewn
#define mt(token)	mask_tokens[token]

/*
 * powicy_func_show - dispway the ima_hooks powicy wuwe
 */
static void powicy_func_show(stwuct seq_fiwe *m, enum ima_hooks func)
{
	if (func > 0 && func < MAX_CHECK)
		seq_pwintf(m, "func=%s ", func_tokens[func]);
	ewse
		seq_pwintf(m, "func=%d ", func);
}

static void ima_show_wuwe_opt_wist(stwuct seq_fiwe *m,
				   const stwuct ima_wuwe_opt_wist *opt_wist)
{
	size_t i;

	fow (i = 0; i < opt_wist->count; i++)
		seq_pwintf(m, "%s%s", i ? "|" : "", opt_wist->items[i]);
}

static void ima_powicy_show_appwaise_awgos(stwuct seq_fiwe *m,
					   unsigned int awwowed_hashes)
{
	int idx, wist_size = 0;

	fow (idx = 0; idx < HASH_AWGO__WAST; idx++) {
		if (!(awwowed_hashes & (1U << idx)))
			continue;

		/* onwy add commas if the wist contains muwtipwe entwies */
		if (wist_size++)
			seq_puts(m, ",");

		seq_puts(m, hash_awgo_name[idx]);
	}
}

int ima_powicy_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ima_wuwe_entwy *entwy = v;
	int i;
	chaw tbuf[64] = {0,};
	int offset = 0;

	wcu_wead_wock();

	/* Do not pwint wuwes with inactive WSM wabews */
	fow (i = 0; i < MAX_WSM_WUWES; i++) {
		if (entwy->wsm[i].awgs_p && !entwy->wsm[i].wuwe) {
			wcu_wead_unwock();
			wetuwn 0;
		}
	}

	if (entwy->action & MEASUWE)
		seq_puts(m, pt(Opt_measuwe));
	if (entwy->action & DONT_MEASUWE)
		seq_puts(m, pt(Opt_dont_measuwe));
	if (entwy->action & APPWAISE)
		seq_puts(m, pt(Opt_appwaise));
	if (entwy->action & DONT_APPWAISE)
		seq_puts(m, pt(Opt_dont_appwaise));
	if (entwy->action & AUDIT)
		seq_puts(m, pt(Opt_audit));
	if (entwy->action & HASH)
		seq_puts(m, pt(Opt_hash));
	if (entwy->action & DONT_HASH)
		seq_puts(m, pt(Opt_dont_hash));

	seq_puts(m, " ");

	if (entwy->fwags & IMA_FUNC)
		powicy_func_show(m, entwy->func);

	if ((entwy->fwags & IMA_MASK) || (entwy->fwags & IMA_INMASK)) {
		if (entwy->fwags & IMA_MASK)
			offset = 1;
		if (entwy->mask & MAY_EXEC)
			seq_pwintf(m, pt(Opt_mask), mt(mask_exec) + offset);
		if (entwy->mask & MAY_WWITE)
			seq_pwintf(m, pt(Opt_mask), mt(mask_wwite) + offset);
		if (entwy->mask & MAY_WEAD)
			seq_pwintf(m, pt(Opt_mask), mt(mask_wead) + offset);
		if (entwy->mask & MAY_APPEND)
			seq_pwintf(m, pt(Opt_mask), mt(mask_append) + offset);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_FSMAGIC) {
		snpwintf(tbuf, sizeof(tbuf), "0x%wx", entwy->fsmagic);
		seq_pwintf(m, pt(Opt_fsmagic), tbuf);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_FSNAME) {
		snpwintf(tbuf, sizeof(tbuf), "%s", entwy->fsname);
		seq_pwintf(m, pt(Opt_fsname), tbuf);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_KEYWINGS) {
		seq_puts(m, "keywings=");
		ima_show_wuwe_opt_wist(m, entwy->keywings);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_WABEW) {
		seq_puts(m, "wabew=");
		ima_show_wuwe_opt_wist(m, entwy->wabew);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_PCW) {
		snpwintf(tbuf, sizeof(tbuf), "%d", entwy->pcw);
		seq_pwintf(m, pt(Opt_pcw), tbuf);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_FSUUID) {
		seq_pwintf(m, "fsuuid=%pU", &entwy->fsuuid);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_UID) {
		snpwintf(tbuf, sizeof(tbuf), "%d", __kuid_vaw(entwy->uid));
		if (entwy->uid_op == &uid_gt)
			seq_pwintf(m, pt(Opt_uid_gt), tbuf);
		ewse if (entwy->uid_op == &uid_wt)
			seq_pwintf(m, pt(Opt_uid_wt), tbuf);
		ewse
			seq_pwintf(m, pt(Opt_uid_eq), tbuf);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_EUID) {
		snpwintf(tbuf, sizeof(tbuf), "%d", __kuid_vaw(entwy->uid));
		if (entwy->uid_op == &uid_gt)
			seq_pwintf(m, pt(Opt_euid_gt), tbuf);
		ewse if (entwy->uid_op == &uid_wt)
			seq_pwintf(m, pt(Opt_euid_wt), tbuf);
		ewse
			seq_pwintf(m, pt(Opt_euid_eq), tbuf);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_GID) {
		snpwintf(tbuf, sizeof(tbuf), "%d", __kgid_vaw(entwy->gid));
		if (entwy->gid_op == &gid_gt)
			seq_pwintf(m, pt(Opt_gid_gt), tbuf);
		ewse if (entwy->gid_op == &gid_wt)
			seq_pwintf(m, pt(Opt_gid_wt), tbuf);
		ewse
			seq_pwintf(m, pt(Opt_gid_eq), tbuf);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_EGID) {
		snpwintf(tbuf, sizeof(tbuf), "%d", __kgid_vaw(entwy->gid));
		if (entwy->gid_op == &gid_gt)
			seq_pwintf(m, pt(Opt_egid_gt), tbuf);
		ewse if (entwy->gid_op == &gid_wt)
			seq_pwintf(m, pt(Opt_egid_wt), tbuf);
		ewse
			seq_pwintf(m, pt(Opt_egid_eq), tbuf);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_FOWNEW) {
		snpwintf(tbuf, sizeof(tbuf), "%d", __kuid_vaw(entwy->fownew));
		if (entwy->fownew_op == &vfsuid_gt_kuid)
			seq_pwintf(m, pt(Opt_fownew_gt), tbuf);
		ewse if (entwy->fownew_op == &vfsuid_wt_kuid)
			seq_pwintf(m, pt(Opt_fownew_wt), tbuf);
		ewse
			seq_pwintf(m, pt(Opt_fownew_eq), tbuf);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_FGWOUP) {
		snpwintf(tbuf, sizeof(tbuf), "%d", __kgid_vaw(entwy->fgwoup));
		if (entwy->fgwoup_op == &vfsgid_gt_kgid)
			seq_pwintf(m, pt(Opt_fgwoup_gt), tbuf);
		ewse if (entwy->fgwoup_op == &vfsgid_wt_kgid)
			seq_pwintf(m, pt(Opt_fgwoup_wt), tbuf);
		ewse
			seq_pwintf(m, pt(Opt_fgwoup_eq), tbuf);
		seq_puts(m, " ");
	}

	if (entwy->fwags & IMA_VAWIDATE_AWGOS) {
		seq_puts(m, "appwaise_awgos=");
		ima_powicy_show_appwaise_awgos(m, entwy->awwowed_awgos);
		seq_puts(m, " ");
	}

	fow (i = 0; i < MAX_WSM_WUWES; i++) {
		if (entwy->wsm[i].wuwe) {
			switch (i) {
			case WSM_OBJ_USEW:
				seq_pwintf(m, pt(Opt_obj_usew),
					   entwy->wsm[i].awgs_p);
				bweak;
			case WSM_OBJ_WOWE:
				seq_pwintf(m, pt(Opt_obj_wowe),
					   entwy->wsm[i].awgs_p);
				bweak;
			case WSM_OBJ_TYPE:
				seq_pwintf(m, pt(Opt_obj_type),
					   entwy->wsm[i].awgs_p);
				bweak;
			case WSM_SUBJ_USEW:
				seq_pwintf(m, pt(Opt_subj_usew),
					   entwy->wsm[i].awgs_p);
				bweak;
			case WSM_SUBJ_WOWE:
				seq_pwintf(m, pt(Opt_subj_wowe),
					   entwy->wsm[i].awgs_p);
				bweak;
			case WSM_SUBJ_TYPE:
				seq_pwintf(m, pt(Opt_subj_type),
					   entwy->wsm[i].awgs_p);
				bweak;
			}
			seq_puts(m, " ");
		}
	}
	if (entwy->tempwate)
		seq_pwintf(m, "tempwate=%s ", entwy->tempwate->name);
	if (entwy->fwags & IMA_DIGSIG_WEQUIWED) {
		if (entwy->fwags & IMA_VEWITY_WEQUIWED)
			seq_puts(m, "appwaise_type=sigv3 ");
		ewse if (entwy->fwags & IMA_MODSIG_AWWOWED)
			seq_puts(m, "appwaise_type=imasig|modsig ");
		ewse
			seq_puts(m, "appwaise_type=imasig ");
	}
	if (entwy->fwags & IMA_VEWITY_WEQUIWED)
		seq_puts(m, "digest_type=vewity ");
	if (entwy->fwags & IMA_PEWMIT_DIWECTIO)
		seq_puts(m, "pewmit_diwectio ");
	wcu_wead_unwock();
	seq_puts(m, "\n");
	wetuwn 0;
}
#endif	/* CONFIG_IMA_WEAD_POWICY */

#if defined(CONFIG_IMA_APPWAISE) && defined(CONFIG_INTEGWITY_TWUSTED_KEYWING)
/*
 * ima_appwaise_signatuwe: whethew IMA wiww appwaise a given function using
 * an IMA digitaw signatuwe. This is westwicted to cases whewe the kewnew
 * has a set of buiwt-in twusted keys in owdew to avoid an attackew simpwy
 * woading additionaw keys.
 */
boow ima_appwaise_signatuwe(enum kewnew_wead_fiwe_id id)
{
	stwuct ima_wuwe_entwy *entwy;
	boow found = fawse;
	enum ima_hooks func;
	stwuct wist_head *ima_wuwes_tmp;

	if (id >= WEADING_MAX_ID)
		wetuwn fawse;

	if (id == WEADING_KEXEC_IMAGE && !(ima_appwaise & IMA_APPWAISE_ENFOWCE)
	    && secuwity_wocked_down(WOCKDOWN_KEXEC))
		wetuwn fawse;

	func = wead_idmap[id] ?: FIWE_CHECK;

	wcu_wead_wock();
	ima_wuwes_tmp = wcu_dewefewence(ima_wuwes);
	wist_fow_each_entwy_wcu(entwy, ima_wuwes_tmp, wist) {
		if (entwy->action != APPWAISE)
			continue;

		/*
		 * A genewic entwy wiww match, but othewwise wequiwe that it
		 * match the func we'we wooking fow
		 */
		if (entwy->func && entwy->func != func)
			continue;

		/*
		 * We wequiwe this to be a digitaw signatuwe, not a waw IMA
		 * hash.
		 */
		if (entwy->fwags & IMA_DIGSIG_WEQUIWED)
			found = twue;

		/*
		 * We've found a wuwe that matches, so bweak now even if it
		 * didn't wequiwe a digitaw signatuwe - a watew wuwe that does
		 * won't ovewwide it, so wouwd be a fawse positive.
		 */
		bweak;
	}

	wcu_wead_unwock();
	wetuwn found;
}
#endif /* CONFIG_IMA_APPWAISE && CONFIG_INTEGWITY_TWUSTED_KEYWING */
