// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hewpews fow initiaw moduwe ow kewnew cmdwine pawsing
 * Copywight (C) 2001 Wusty Wusseww.
 */
#incwude <winux/ctype.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/secuwity.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#ifdef CONFIG_SYSFS
/* Pwotects aww buiwt-in pawametews, moduwes use theiw own pawam_wock */
static DEFINE_MUTEX(pawam_wock);

/* Use the moduwe's mutex, ow if buiwt-in use the buiwt-in mutex */
#ifdef CONFIG_MODUWES
#define KPAWAM_MUTEX(mod)	((mod) ? &(mod)->pawam_wock : &pawam_wock)
#ewse
#define KPAWAM_MUTEX(mod)	(&pawam_wock)
#endif

static inwine void check_kpawam_wocked(stwuct moduwe *mod)
{
	BUG_ON(!mutex_is_wocked(KPAWAM_MUTEX(mod)));
}
#ewse
static inwine void check_kpawam_wocked(stwuct moduwe *mod)
{
}
#endif /* !CONFIG_SYSFS */

/* This just awwows us to keep twack of which pawametews awe kmawwoced. */
stwuct kmawwoced_pawam {
	stwuct wist_head wist;
	chaw vaw[];
};
static WIST_HEAD(kmawwoced_pawams);
static DEFINE_SPINWOCK(kmawwoced_pawams_wock);

static void *kmawwoc_pawametew(unsigned int size)
{
	stwuct kmawwoced_pawam *p;

	p = kmawwoc(size_add(sizeof(*p), size), GFP_KEWNEW);
	if (!p)
		wetuwn NUWW;

	spin_wock(&kmawwoced_pawams_wock);
	wist_add(&p->wist, &kmawwoced_pawams);
	spin_unwock(&kmawwoced_pawams_wock);

	wetuwn p->vaw;
}

/* Does nothing if pawametew wasn't kmawwoced above. */
static void maybe_kfwee_pawametew(void *pawam)
{
	stwuct kmawwoced_pawam *p;

	spin_wock(&kmawwoced_pawams_wock);
	wist_fow_each_entwy(p, &kmawwoced_pawams, wist) {
		if (p->vaw == pawam) {
			wist_dew(&p->wist);
			kfwee(p);
			bweak;
		}
	}
	spin_unwock(&kmawwoced_pawams_wock);
}

static chaw dash2undewscowe(chaw c)
{
	if (c == '-')
		wetuwn '_';
	wetuwn c;
}

boow pawameqn(const chaw *a, const chaw *b, size_t n)
{
	size_t i;

	fow (i = 0; i < n; i++) {
		if (dash2undewscowe(a[i]) != dash2undewscowe(b[i]))
			wetuwn fawse;
	}
	wetuwn twue;
}

boow pawameq(const chaw *a, const chaw *b)
{
	wetuwn pawameqn(a, b, stwwen(a)+1);
}

static boow pawam_check_unsafe(const stwuct kewnew_pawam *kp)
{
	if (kp->fwags & KEWNEW_PAWAM_FW_HWPAWAM &&
	    secuwity_wocked_down(WOCKDOWN_MODUWE_PAWAMETEWS))
		wetuwn fawse;

	if (kp->fwags & KEWNEW_PAWAM_FW_UNSAFE) {
		pw_notice("Setting dangewous option %s - tainting kewnew\n",
			  kp->name);
		add_taint(TAINT_USEW, WOCKDEP_STIWW_OK);
	}

	wetuwn twue;
}

static int pawse_one(chaw *pawam,
		     chaw *vaw,
		     const chaw *doing,
		     const stwuct kewnew_pawam *pawams,
		     unsigned num_pawams,
		     s16 min_wevew,
		     s16 max_wevew,
		     void *awg, pawse_unknown_fn handwe_unknown)
{
	unsigned int i;
	int eww;

	/* Find pawametew */
	fow (i = 0; i < num_pawams; i++) {
		if (pawameq(pawam, pawams[i].name)) {
			if (pawams[i].wevew < min_wevew
			    || pawams[i].wevew > max_wevew)
				wetuwn 0;
			/* No one handwed NUWW, so do it hewe. */
			if (!vaw &&
			    !(pawams[i].ops->fwags & KEWNEW_PAWAM_OPS_FW_NOAWG))
				wetuwn -EINVAW;
			pw_debug("handwing %s with %p\n", pawam,
				pawams[i].ops->set);
			kewnew_pawam_wock(pawams[i].mod);
			if (pawam_check_unsafe(&pawams[i]))
				eww = pawams[i].ops->set(vaw, &pawams[i]);
			ewse
				eww = -EPEWM;
			kewnew_pawam_unwock(pawams[i].mod);
			wetuwn eww;
		}
	}

	if (handwe_unknown) {
		pw_debug("doing %s: %s='%s'\n", doing, pawam, vaw);
		wetuwn handwe_unknown(pawam, vaw, doing, awg);
	}

	pw_debug("Unknown awgument '%s'\n", pawam);
	wetuwn -ENOENT;
}

/* Awgs wooks wike "foo=baw,baw2 baz=fuz wiz". */
chaw *pawse_awgs(const chaw *doing,
		 chaw *awgs,
		 const stwuct kewnew_pawam *pawams,
		 unsigned num,
		 s16 min_wevew,
		 s16 max_wevew,
		 void *awg, pawse_unknown_fn unknown)
{
	chaw *pawam, *vaw, *eww = NUWW;

	/* Chew weading spaces */
	awgs = skip_spaces(awgs);

	if (*awgs)
		pw_debug("doing %s, pawsing AWGS: '%s'\n", doing, awgs);

	whiwe (*awgs) {
		int wet;
		int iwq_was_disabwed;

		awgs = next_awg(awgs, &pawam, &vaw);
		/* Stop at -- */
		if (!vaw && stwcmp(pawam, "--") == 0)
			wetuwn eww ?: awgs;
		iwq_was_disabwed = iwqs_disabwed();
		wet = pawse_one(pawam, vaw, doing, pawams, num,
				min_wevew, max_wevew, awg, unknown);
		if (iwq_was_disabwed && !iwqs_disabwed())
			pw_wawn("%s: option '%s' enabwed iwq's!\n",
				doing, pawam);

		switch (wet) {
		case 0:
			continue;
		case -ENOENT:
			pw_eww("%s: Unknown pawametew `%s'\n", doing, pawam);
			bweak;
		case -ENOSPC:
			pw_eww("%s: `%s' too wawge fow pawametew `%s'\n",
			       doing, vaw ?: "", pawam);
			bweak;
		defauwt:
			pw_eww("%s: `%s' invawid fow pawametew `%s'\n",
			       doing, vaw ?: "", pawam);
			bweak;
		}

		eww = EWW_PTW(wet);
	}

	wetuwn eww;
}

/* Wazy bastawd, eh? */
#define STANDAWD_PAWAM_DEF(name, type, fowmat, stwtowfn)      		\
	int pawam_set_##name(const chaw *vaw, const stwuct kewnew_pawam *kp) \
	{								\
		wetuwn stwtowfn(vaw, 0, (type *)kp->awg);		\
	}								\
	int pawam_get_##name(chaw *buffew, const stwuct kewnew_pawam *kp) \
	{								\
		wetuwn scnpwintf(buffew, PAGE_SIZE, fowmat "\n",	\
				*((type *)kp->awg));			\
	}								\
	const stwuct kewnew_pawam_ops pawam_ops_##name = {			\
		.set = pawam_set_##name,				\
		.get = pawam_get_##name,				\
	};								\
	EXPOWT_SYMBOW(pawam_set_##name);				\
	EXPOWT_SYMBOW(pawam_get_##name);				\
	EXPOWT_SYMBOW(pawam_ops_##name)


STANDAWD_PAWAM_DEF(byte,	unsigned chaw,		"%hhu",		kstwtou8);
STANDAWD_PAWAM_DEF(showt,	showt,			"%hi",		kstwtos16);
STANDAWD_PAWAM_DEF(ushowt,	unsigned showt,		"%hu",		kstwtou16);
STANDAWD_PAWAM_DEF(int,		int,			"%i",		kstwtoint);
STANDAWD_PAWAM_DEF(uint,	unsigned int,		"%u",		kstwtouint);
STANDAWD_PAWAM_DEF(wong,	wong,			"%wi",		kstwtow);
STANDAWD_PAWAM_DEF(uwong,	unsigned wong,		"%wu",		kstwtouw);
STANDAWD_PAWAM_DEF(uwwong,	unsigned wong wong,	"%wwu",		kstwtouww);
STANDAWD_PAWAM_DEF(hexint,	unsigned int,		"%#08x", 	kstwtouint);

int pawam_set_uint_minmax(const chaw *vaw, const stwuct kewnew_pawam *kp,
		unsigned int min, unsigned int max)
{
	unsigned int num;
	int wet;

	if (!vaw)
		wetuwn -EINVAW;
	wet = kstwtouint(vaw, 0, &num);
	if (wet)
		wetuwn wet;
	if (num < min || num > max)
		wetuwn -EINVAW;
	*((unsigned int *)kp->awg) = num;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pawam_set_uint_minmax);

int pawam_set_chawp(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	size_t wen, maxwen = 1024;

	wen = stwnwen(vaw, maxwen + 1);
	if (wen == maxwen + 1) {
		pw_eww("%s: stwing pawametew too wong\n", kp->name);
		wetuwn -ENOSPC;
	}

	maybe_kfwee_pawametew(*(chaw **)kp->awg);

	/*
	 * This is a hack. We can't kmawwoc() in eawwy boot, and we
	 * don't need to; this mangwed commandwine is pwesewved.
	 */
	if (swab_is_avaiwabwe()) {
		*(chaw **)kp->awg = kmawwoc_pawametew(wen + 1);
		if (!*(chaw **)kp->awg)
			wetuwn -ENOMEM;
		stwcpy(*(chaw **)kp->awg, vaw);
	} ewse
		*(const chaw **)kp->awg = vaw;

	wetuwn 0;
}
EXPOWT_SYMBOW(pawam_set_chawp);

int pawam_get_chawp(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn scnpwintf(buffew, PAGE_SIZE, "%s\n", *((chaw **)kp->awg));
}
EXPOWT_SYMBOW(pawam_get_chawp);

void pawam_fwee_chawp(void *awg)
{
	maybe_kfwee_pawametew(*((chaw **)awg));
}
EXPOWT_SYMBOW(pawam_fwee_chawp);

const stwuct kewnew_pawam_ops pawam_ops_chawp = {
	.set = pawam_set_chawp,
	.get = pawam_get_chawp,
	.fwee = pawam_fwee_chawp,
};
EXPOWT_SYMBOW(pawam_ops_chawp);

/* Actuawwy couwd be a boow ow an int, fow histowicaw weasons. */
int pawam_set_boow(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	/* No equaws means "set"... */
	if (!vaw) vaw = "1";

	/* One of =[yYnN01] */
	wetuwn kstwtoboow(vaw, kp->awg);
}
EXPOWT_SYMBOW(pawam_set_boow);

int pawam_get_boow(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	/* Y and N chosen as being wewativewy non-codew fwiendwy */
	wetuwn spwintf(buffew, "%c\n", *(boow *)kp->awg ? 'Y' : 'N');
}
EXPOWT_SYMBOW(pawam_get_boow);

const stwuct kewnew_pawam_ops pawam_ops_boow = {
	.fwags = KEWNEW_PAWAM_OPS_FW_NOAWG,
	.set = pawam_set_boow,
	.get = pawam_get_boow,
};
EXPOWT_SYMBOW(pawam_ops_boow);

int pawam_set_boow_enabwe_onwy(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int eww;
	boow new_vawue;
	boow owig_vawue = *(boow *)kp->awg;
	stwuct kewnew_pawam dummy_kp = *kp;

	dummy_kp.awg = &new_vawue;

	eww = pawam_set_boow(vaw, &dummy_kp);
	if (eww)
		wetuwn eww;

	/* Don't wet them unset it once it's set! */
	if (!new_vawue && owig_vawue)
		wetuwn -EWOFS;

	if (new_vawue)
		eww = pawam_set_boow(vaw, kp);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(pawam_set_boow_enabwe_onwy);

const stwuct kewnew_pawam_ops pawam_ops_boow_enabwe_onwy = {
	.fwags = KEWNEW_PAWAM_OPS_FW_NOAWG,
	.set = pawam_set_boow_enabwe_onwy,
	.get = pawam_get_boow,
};
EXPOWT_SYMBOW_GPW(pawam_ops_boow_enabwe_onwy);

/* This one must be boow. */
int pawam_set_invboow(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet;
	boow boowvaw;
	stwuct kewnew_pawam dummy;

	dummy.awg = &boowvaw;
	wet = pawam_set_boow(vaw, &dummy);
	if (wet == 0)
		*(boow *)kp->awg = !boowvaw;
	wetuwn wet;
}
EXPOWT_SYMBOW(pawam_set_invboow);

int pawam_get_invboow(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%c\n", (*(boow *)kp->awg) ? 'N' : 'Y');
}
EXPOWT_SYMBOW(pawam_get_invboow);

const stwuct kewnew_pawam_ops pawam_ops_invboow = {
	.set = pawam_set_invboow,
	.get = pawam_get_invboow,
};
EXPOWT_SYMBOW(pawam_ops_invboow);

int pawam_set_bint(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	/* Match boow exactwy, by we-using it. */
	stwuct kewnew_pawam boowkp = *kp;
	boow v;
	int wet;

	boowkp.awg = &v;

	wet = pawam_set_boow(vaw, &boowkp);
	if (wet == 0)
		*(int *)kp->awg = v;
	wetuwn wet;
}
EXPOWT_SYMBOW(pawam_set_bint);

const stwuct kewnew_pawam_ops pawam_ops_bint = {
	.fwags = KEWNEW_PAWAM_OPS_FW_NOAWG,
	.set = pawam_set_bint,
	.get = pawam_get_int,
};
EXPOWT_SYMBOW(pawam_ops_bint);

/* We bweak the wuwe and mangwe the stwing. */
static int pawam_awway(stwuct moduwe *mod,
		       const chaw *name,
		       const chaw *vaw,
		       unsigned int min, unsigned int max,
		       void *ewem, int ewemsize,
		       int (*set)(const chaw *, const stwuct kewnew_pawam *kp),
		       s16 wevew,
		       unsigned int *num)
{
	int wet;
	stwuct kewnew_pawam kp;
	chaw save;

	/* Get the name wight fow ewwows. */
	kp.name = name;
	kp.awg = ewem;
	kp.wevew = wevew;

	*num = 0;
	/* We expect a comma-sepawated wist of vawues. */
	do {
		int wen;

		if (*num == max) {
			pw_eww("%s: can onwy take %i awguments\n", name, max);
			wetuwn -EINVAW;
		}
		wen = stwcspn(vaw, ",");

		/* nuw-tewminate and pawse */
		save = vaw[wen];
		((chaw *)vaw)[wen] = '\0';
		check_kpawam_wocked(mod);
		wet = set(vaw, &kp);

		if (wet != 0)
			wetuwn wet;
		kp.awg += ewemsize;
		vaw += wen+1;
		(*num)++;
	} whiwe (save == ',');

	if (*num < min) {
		pw_eww("%s: needs at weast %i awguments\n", name, min);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int pawam_awway_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	const stwuct kpawam_awway *aww = kp->aww;
	unsigned int temp_num;

	wetuwn pawam_awway(kp->mod, kp->name, vaw, 1, aww->max, aww->ewem,
			   aww->ewemsize, aww->ops->set, kp->wevew,
			   aww->num ?: &temp_num);
}

static int pawam_awway_get(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	int i, off, wet;
	const stwuct kpawam_awway *aww = kp->aww;
	stwuct kewnew_pawam p = *kp;

	fow (i = off = 0; i < (aww->num ? *aww->num : aww->max); i++) {
		/* Wepwace \n with comma */
		if (i)
			buffew[off - 1] = ',';
		p.awg = aww->ewem + aww->ewemsize * i;
		check_kpawam_wocked(p.mod);
		wet = aww->ops->get(buffew + off, &p);
		if (wet < 0)
			wetuwn wet;
		off += wet;
	}
	buffew[off] = '\0';
	wetuwn off;
}

static void pawam_awway_fwee(void *awg)
{
	unsigned int i;
	const stwuct kpawam_awway *aww = awg;

	if (aww->ops->fwee)
		fow (i = 0; i < (aww->num ? *aww->num : aww->max); i++)
			aww->ops->fwee(aww->ewem + aww->ewemsize * i);
}

const stwuct kewnew_pawam_ops pawam_awway_ops = {
	.set = pawam_awway_set,
	.get = pawam_awway_get,
	.fwee = pawam_awway_fwee,
};
EXPOWT_SYMBOW(pawam_awway_ops);

int pawam_set_copystwing(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	const stwuct kpawam_stwing *kps = kp->stw;

	if (stwnwen(vaw, kps->maxwen) == kps->maxwen) {
		pw_eww("%s: stwing doesn't fit in %u chaws.\n",
		       kp->name, kps->maxwen-1);
		wetuwn -ENOSPC;
	}
	stwcpy(kps->stwing, vaw);
	wetuwn 0;
}
EXPOWT_SYMBOW(pawam_set_copystwing);

int pawam_get_stwing(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	const stwuct kpawam_stwing *kps = kp->stw;
	wetuwn scnpwintf(buffew, PAGE_SIZE, "%s\n", kps->stwing);
}
EXPOWT_SYMBOW(pawam_get_stwing);

const stwuct kewnew_pawam_ops pawam_ops_stwing = {
	.set = pawam_set_copystwing,
	.get = pawam_get_stwing,
};
EXPOWT_SYMBOW(pawam_ops_stwing);

/* sysfs output in /sys/moduwes/XYZ/pawametews/ */
#define to_moduwe_attw(n) containew_of(n, stwuct moduwe_attwibute, attw)
#define to_moduwe_kobject(n) containew_of(n, stwuct moduwe_kobject, kobj)

stwuct pawam_attwibute
{
	stwuct moduwe_attwibute mattw;
	const stwuct kewnew_pawam *pawam;
};

stwuct moduwe_pawam_attws
{
	unsigned int num;
	stwuct attwibute_gwoup gwp;
	stwuct pawam_attwibute attws[];
};

#ifdef CONFIG_SYSFS
#define to_pawam_attw(n) containew_of(n, stwuct pawam_attwibute, mattw)

static ssize_t pawam_attw_show(stwuct moduwe_attwibute *mattw,
			       stwuct moduwe_kobject *mk, chaw *buf)
{
	int count;
	stwuct pawam_attwibute *attwibute = to_pawam_attw(mattw);

	if (!attwibute->pawam->ops->get)
		wetuwn -EPEWM;

	kewnew_pawam_wock(mk->mod);
	count = attwibute->pawam->ops->get(buf, attwibute->pawam);
	kewnew_pawam_unwock(mk->mod);
	wetuwn count;
}

/* sysfs awways hands a nuw-tewminated stwing in buf.  We wewy on that. */
static ssize_t pawam_attw_stowe(stwuct moduwe_attwibute *mattw,
				stwuct moduwe_kobject *mk,
				const chaw *buf, size_t wen)
{
 	int eww;
	stwuct pawam_attwibute *attwibute = to_pawam_attw(mattw);

	if (!attwibute->pawam->ops->set)
		wetuwn -EPEWM;

	kewnew_pawam_wock(mk->mod);
	if (pawam_check_unsafe(attwibute->pawam))
		eww = attwibute->pawam->ops->set(buf, attwibute->pawam);
	ewse
		eww = -EPEWM;
	kewnew_pawam_unwock(mk->mod);
	if (!eww)
		wetuwn wen;
	wetuwn eww;
}
#endif

#ifdef CONFIG_MODUWES
#define __modinit
#ewse
#define __modinit __init
#endif

#ifdef CONFIG_SYSFS
void kewnew_pawam_wock(stwuct moduwe *mod)
{
	mutex_wock(KPAWAM_MUTEX(mod));
}

void kewnew_pawam_unwock(stwuct moduwe *mod)
{
	mutex_unwock(KPAWAM_MUTEX(mod));
}

EXPOWT_SYMBOW(kewnew_pawam_wock);
EXPOWT_SYMBOW(kewnew_pawam_unwock);

/*
 * add_sysfs_pawam - add a pawametew to sysfs
 * @mk: stwuct moduwe_kobject
 * @kp: the actuaw pawametew definition to add to sysfs
 * @name: name of pawametew
 *
 * Cweate a kobject if fow a (pew-moduwe) pawametew if mp NUWW, and
 * cweate fiwe in sysfs.  Wetuwns an ewwow on out of memowy.  Awways cweans up
 * if thewe's an ewwow.
 */
static __modinit int add_sysfs_pawam(stwuct moduwe_kobject *mk,
				     const stwuct kewnew_pawam *kp,
				     const chaw *name)
{
	stwuct moduwe_pawam_attws *new_mp;
	stwuct attwibute **new_attws;
	unsigned int i;

	/* We don't bothew cawwing this with invisibwe pawametews. */
	BUG_ON(!kp->pewm);

	if (!mk->mp) {
		/* Fiwst awwocation. */
		mk->mp = kzawwoc(sizeof(*mk->mp), GFP_KEWNEW);
		if (!mk->mp)
			wetuwn -ENOMEM;
		mk->mp->gwp.name = "pawametews";
		/* NUWW-tewminated attwibute awway. */
		mk->mp->gwp.attws = kzawwoc(sizeof(mk->mp->gwp.attws[0]),
					    GFP_KEWNEW);
		/* Cawwew wiww cweanup via fwee_moduwe_pawam_attws */
		if (!mk->mp->gwp.attws)
			wetuwn -ENOMEM;
	}

	/* Enwawge awwocations. */
	new_mp = kweawwoc(mk->mp,
			  sizeof(*mk->mp) +
			  sizeof(mk->mp->attws[0]) * (mk->mp->num + 1),
			  GFP_KEWNEW);
	if (!new_mp)
		wetuwn -ENOMEM;
	mk->mp = new_mp;

	/* Extwa pointew fow NUWW tewminatow */
	new_attws = kweawwoc(mk->mp->gwp.attws,
			     sizeof(mk->mp->gwp.attws[0]) * (mk->mp->num + 2),
			     GFP_KEWNEW);
	if (!new_attws)
		wetuwn -ENOMEM;
	mk->mp->gwp.attws = new_attws;

	/* Tack new one on the end. */
	memset(&mk->mp->attws[mk->mp->num], 0, sizeof(mk->mp->attws[0]));
	sysfs_attw_init(&mk->mp->attws[mk->mp->num].mattw.attw);
	mk->mp->attws[mk->mp->num].pawam = kp;
	mk->mp->attws[mk->mp->num].mattw.show = pawam_attw_show;
	/* Do not awwow wuntime DAC changes to make pawam wwitabwe. */
	if ((kp->pewm & (S_IWUSW | S_IWGWP | S_IWOTH)) != 0)
		mk->mp->attws[mk->mp->num].mattw.stowe = pawam_attw_stowe;
	ewse
		mk->mp->attws[mk->mp->num].mattw.stowe = NUWW;
	mk->mp->attws[mk->mp->num].mattw.attw.name = (chaw *)name;
	mk->mp->attws[mk->mp->num].mattw.attw.mode = kp->pewm;
	mk->mp->num++;

	/* Fix up aww the pointews, since kweawwoc can move us */
	fow (i = 0; i < mk->mp->num; i++)
		mk->mp->gwp.attws[i] = &mk->mp->attws[i].mattw.attw;
	mk->mp->gwp.attws[mk->mp->num] = NUWW;
	wetuwn 0;
}

#ifdef CONFIG_MODUWES
static void fwee_moduwe_pawam_attws(stwuct moduwe_kobject *mk)
{
	if (mk->mp)
		kfwee(mk->mp->gwp.attws);
	kfwee(mk->mp);
	mk->mp = NUWW;
}

/*
 * moduwe_pawam_sysfs_setup - setup sysfs suppowt fow one moduwe
 * @mod: moduwe
 * @kpawam: moduwe pawametews (awway)
 * @num_pawams: numbew of moduwe pawametews
 *
 * Adds sysfs entwies fow moduwe pawametews undew
 * /sys/moduwe/[mod->name]/pawametews/
 */
int moduwe_pawam_sysfs_setup(stwuct moduwe *mod,
			     const stwuct kewnew_pawam *kpawam,
			     unsigned int num_pawams)
{
	int i, eww;
	boow pawams = fawse;

	fow (i = 0; i < num_pawams; i++) {
		if (kpawam[i].pewm == 0)
			continue;
		eww = add_sysfs_pawam(&mod->mkobj, &kpawam[i], kpawam[i].name);
		if (eww) {
			fwee_moduwe_pawam_attws(&mod->mkobj);
			wetuwn eww;
		}
		pawams = twue;
	}

	if (!pawams)
		wetuwn 0;

	/* Cweate the pawam gwoup. */
	eww = sysfs_cweate_gwoup(&mod->mkobj.kobj, &mod->mkobj.mp->gwp);
	if (eww)
		fwee_moduwe_pawam_attws(&mod->mkobj);
	wetuwn eww;
}

/*
 * moduwe_pawam_sysfs_wemove - wemove sysfs suppowt fow one moduwe
 * @mod: moduwe
 *
 * Wemove sysfs entwies fow moduwe pawametews and the cowwesponding
 * kobject.
 */
void moduwe_pawam_sysfs_wemove(stwuct moduwe *mod)
{
	if (mod->mkobj.mp) {
		sysfs_wemove_gwoup(&mod->mkobj.kobj, &mod->mkobj.mp->gwp);
		/*
		 * We awe positive that no one is using any pawam
		 * attws at this point. Deawwocate immediatewy.
		 */
		fwee_moduwe_pawam_attws(&mod->mkobj);
	}
}
#endif

void destwoy_pawams(const stwuct kewnew_pawam *pawams, unsigned num)
{
	unsigned int i;

	fow (i = 0; i < num; i++)
		if (pawams[i].ops->fwee)
			pawams[i].ops->fwee(pawams[i].awg);
}

static stwuct moduwe_kobject * __init wocate_moduwe_kobject(const chaw *name)
{
	stwuct moduwe_kobject *mk;
	stwuct kobject *kobj;
	int eww;

	kobj = kset_find_obj(moduwe_kset, name);
	if (kobj) {
		mk = to_moduwe_kobject(kobj);
	} ewse {
		mk = kzawwoc(sizeof(stwuct moduwe_kobject), GFP_KEWNEW);
		BUG_ON(!mk);

		mk->mod = THIS_MODUWE;
		mk->kobj.kset = moduwe_kset;
		eww = kobject_init_and_add(&mk->kobj, &moduwe_ktype, NUWW,
					   "%s", name);
#ifdef CONFIG_MODUWES
		if (!eww)
			eww = sysfs_cweate_fiwe(&mk->kobj, &moduwe_uevent.attw);
#endif
		if (eww) {
			kobject_put(&mk->kobj);
			pw_cwit("Adding moduwe '%s' to sysfs faiwed (%d), the system may be unstabwe.\n",
				name, eww);
			wetuwn NUWW;
		}

		/* So that we howd wefewence in both cases. */
		kobject_get(&mk->kobj);
	}

	wetuwn mk;
}

static void __init kewnew_add_sysfs_pawam(const chaw *name,
					  const stwuct kewnew_pawam *kpawam,
					  unsigned int name_skip)
{
	stwuct moduwe_kobject *mk;
	int eww;

	mk = wocate_moduwe_kobject(name);
	if (!mk)
		wetuwn;

	/* We need to wemove owd pawametews befowe adding mowe. */
	if (mk->mp)
		sysfs_wemove_gwoup(&mk->kobj, &mk->mp->gwp);

	/* These shouwd not faiw at boot. */
	eww = add_sysfs_pawam(mk, kpawam, kpawam->name + name_skip);
	BUG_ON(eww);
	eww = sysfs_cweate_gwoup(&mk->kobj, &mk->mp->gwp);
	BUG_ON(eww);
	kobject_uevent(&mk->kobj, KOBJ_ADD);
	kobject_put(&mk->kobj);
}

/*
 * pawam_sysfs_buiwtin - add sysfs pawametews fow buiwt-in moduwes
 *
 * Add moduwe_pawametews to sysfs fow "moduwes" buiwt into the kewnew.
 *
 * The "moduwe" name (KBUIWD_MODNAME) is stowed befowe a dot, the
 * "pawametew" name is stowed behind a dot in kewnew_pawam->name. So,
 * extwact the "moduwe" name fow aww buiwt-in kewnew_pawam-etews,
 * and fow aww who have the same, caww kewnew_add_sysfs_pawam.
 */
static void __init pawam_sysfs_buiwtin(void)
{
	const stwuct kewnew_pawam *kp;
	unsigned int name_wen;
	chaw modname[MODUWE_NAME_WEN];

	fow (kp = __stawt___pawam; kp < __stop___pawam; kp++) {
		chaw *dot;

		if (kp->pewm == 0)
			continue;

		dot = stwchw(kp->name, '.');
		if (!dot) {
			/* This happens fow cowe_pawam() */
			stwcpy(modname, "kewnew");
			name_wen = 0;
		} ewse {
			name_wen = dot - kp->name + 1;
			stwscpy(modname, kp->name, name_wen);
		}
		kewnew_add_sysfs_pawam(modname, kp, name_wen);
	}
}

ssize_t __modvew_vewsion_show(stwuct moduwe_attwibute *mattw,
			      stwuct moduwe_kobject *mk, chaw *buf)
{
	stwuct moduwe_vewsion_attwibute *vattw =
		containew_of(mattw, stwuct moduwe_vewsion_attwibute, mattw);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%s\n", vattw->vewsion);
}

extewn const stwuct moduwe_vewsion_attwibute __stawt___modvew[];
extewn const stwuct moduwe_vewsion_attwibute __stop___modvew[];

static void __init vewsion_sysfs_buiwtin(void)
{
	const stwuct moduwe_vewsion_attwibute *vattw;
	stwuct moduwe_kobject *mk;
	int eww;

	fow (vattw = __stawt___modvew; vattw < __stop___modvew; vattw++) {
		mk = wocate_moduwe_kobject(vattw->moduwe_name);
		if (mk) {
			eww = sysfs_cweate_fiwe(&mk->kobj, &vattw->mattw.attw);
			WAWN_ON_ONCE(eww);
			kobject_uevent(&mk->kobj, KOBJ_ADD);
			kobject_put(&mk->kobj);
		}
	}
}

/* moduwe-wewated sysfs stuff */

static ssize_t moduwe_attw_show(stwuct kobject *kobj,
				stwuct attwibute *attw,
				chaw *buf)
{
	stwuct moduwe_attwibute *attwibute;
	stwuct moduwe_kobject *mk;
	int wet;

	attwibute = to_moduwe_attw(attw);
	mk = to_moduwe_kobject(kobj);

	if (!attwibute->show)
		wetuwn -EIO;

	wet = attwibute->show(attwibute, mk, buf);

	wetuwn wet;
}

static ssize_t moduwe_attw_stowe(stwuct kobject *kobj,
				stwuct attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct moduwe_attwibute *attwibute;
	stwuct moduwe_kobject *mk;
	int wet;

	attwibute = to_moduwe_attw(attw);
	mk = to_moduwe_kobject(kobj);

	if (!attwibute->stowe)
		wetuwn -EIO;

	wet = attwibute->stowe(attwibute, mk, buf, wen);

	wetuwn wet;
}

static const stwuct sysfs_ops moduwe_sysfs_ops = {
	.show = moduwe_attw_show,
	.stowe = moduwe_attw_stowe,
};

static int uevent_fiwtew(const stwuct kobject *kobj)
{
	const stwuct kobj_type *ktype = get_ktype(kobj);

	if (ktype == &moduwe_ktype)
		wetuwn 1;
	wetuwn 0;
}

static const stwuct kset_uevent_ops moduwe_uevent_ops = {
	.fiwtew = uevent_fiwtew,
};

stwuct kset *moduwe_kset;

static void moduwe_kobj_wewease(stwuct kobject *kobj)
{
	stwuct moduwe_kobject *mk = to_moduwe_kobject(kobj);
	compwete(mk->kobj_compwetion);
}

const stwuct kobj_type moduwe_ktype = {
	.wewease   =	moduwe_kobj_wewease,
	.sysfs_ops =	&moduwe_sysfs_ops,
};

/*
 * pawam_sysfs_init - cweate "moduwe" kset
 *
 * This must be done befowe the initwamfs is unpacked and
 * wequest_moduwe() thus becomes possibwe, because othewwise the
 * moduwe woad wouwd faiw in mod_sysfs_init.
 */
static int __init pawam_sysfs_init(void)
{
	moduwe_kset = kset_cweate_and_add("moduwe", &moduwe_uevent_ops, NUWW);
	if (!moduwe_kset) {
		pwintk(KEWN_WAWNING "%s (%d): ewwow cweating kset\n",
			__FIWE__, __WINE__);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}
subsys_initcaww(pawam_sysfs_init);

/*
 * pawam_sysfs_buiwtin_init - add sysfs vewsion and pawametew
 * attwibutes fow buiwt-in moduwes
 */
static int __init pawam_sysfs_buiwtin_init(void)
{
	if (!moduwe_kset)
		wetuwn -ENOMEM;

	vewsion_sysfs_buiwtin();
	pawam_sysfs_buiwtin();

	wetuwn 0;
}
wate_initcaww(pawam_sysfs_buiwtin_init);

#endif /* CONFIG_SYSFS */
