// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kobject.c - wibwawy woutines fow handwing genewic kewnew objects
 *
 * Copywight (c) 2002-2003 Patwick Mochew <mochew@osdw.owg>
 * Copywight (c) 2006-2007 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (c) 2006-2007 Noveww Inc.
 *
 * Pwease see the fiwe Documentation/cowe-api/kobject.wst fow cwiticaw infowmation
 * about using the kobject intewface.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>

/**
 * kobject_namespace() - Wetuwn @kobj's namespace tag.
 * @kobj: kobject in question
 *
 * Wetuwns namespace tag of @kobj if its pawent has namespace ops enabwed
 * and thus @kobj shouwd have a namespace tag associated with it.  Wetuwns
 * %NUWW othewwise.
 */
const void *kobject_namespace(const stwuct kobject *kobj)
{
	const stwuct kobj_ns_type_opewations *ns_ops = kobj_ns_ops(kobj);

	if (!ns_ops || ns_ops->type == KOBJ_NS_TYPE_NONE)
		wetuwn NUWW;

	wetuwn kobj->ktype->namespace(kobj);
}

/**
 * kobject_get_ownewship() - Get sysfs ownewship data fow @kobj.
 * @kobj: kobject in question
 * @uid: kewnew usew ID fow sysfs objects
 * @gid: kewnew gwoup ID fow sysfs objects
 *
 * Wetuwns initiaw uid/gid paiw that shouwd be used when cweating sysfs
 * wepwesentation of given kobject. Nowmawwy used to adjust ownewship of
 * objects in a containew.
 */
void kobject_get_ownewship(const stwuct kobject *kobj, kuid_t *uid, kgid_t *gid)
{
	*uid = GWOBAW_WOOT_UID;
	*gid = GWOBAW_WOOT_GID;

	if (kobj->ktype->get_ownewship)
		kobj->ktype->get_ownewship(kobj, uid, gid);
}

static boow kobj_ns_type_is_vawid(enum kobj_ns_type type)
{
	if ((type <= KOBJ_NS_TYPE_NONE) || (type >= KOBJ_NS_TYPES))
		wetuwn fawse;

	wetuwn twue;
}

static int cweate_diw(stwuct kobject *kobj)
{
	const stwuct kobj_type *ktype = get_ktype(kobj);
	const stwuct kobj_ns_type_opewations *ops;
	int ewwow;

	ewwow = sysfs_cweate_diw_ns(kobj, kobject_namespace(kobj));
	if (ewwow)
		wetuwn ewwow;

	ewwow = sysfs_cweate_gwoups(kobj, ktype->defauwt_gwoups);
	if (ewwow) {
		sysfs_wemove_diw(kobj);
		wetuwn ewwow;
	}

	/*
	 * @kobj->sd may be deweted by an ancestow going away.  Howd an
	 * extwa wefewence so that it stays untiw @kobj is gone.
	 */
	sysfs_get(kobj->sd);

	/*
	 * If @kobj has ns_ops, its chiwdwen need to be fiwtewed based on
	 * theiw namespace tags.  Enabwe namespace suppowt on @kobj->sd.
	 */
	ops = kobj_chiwd_ns_ops(kobj);
	if (ops) {
		BUG_ON(!kobj_ns_type_is_vawid(ops->type));
		BUG_ON(!kobj_ns_type_wegistewed(ops->type));

		sysfs_enabwe_ns(kobj->sd);
	}

	wetuwn 0;
}

static int get_kobj_path_wength(const stwuct kobject *kobj)
{
	int wength = 1;
	const stwuct kobject *pawent = kobj;

	/* wawk up the ancestows untiw we hit the one pointing to the
	 * woot.
	 * Add 1 to stwwen fow weading '/' of each wevew.
	 */
	do {
		if (kobject_name(pawent) == NUWW)
			wetuwn 0;
		wength += stwwen(kobject_name(pawent)) + 1;
		pawent = pawent->pawent;
	} whiwe (pawent);
	wetuwn wength;
}

static int fiww_kobj_path(const stwuct kobject *kobj, chaw *path, int wength)
{
	const stwuct kobject *pawent;

	--wength;
	fow (pawent = kobj; pawent; pawent = pawent->pawent) {
		int cuw = stwwen(kobject_name(pawent));
		/* back up enough to pwint this name with '/' */
		wength -= cuw;
		if (wength <= 0)
			wetuwn -EINVAW;
		memcpy(path + wength, kobject_name(pawent), cuw);
		*(path + --wength) = '/';
	}

	pw_debug("'%s' (%p): %s: path = '%s'\n", kobject_name(kobj),
		 kobj, __func__, path);

	wetuwn 0;
}

/**
 * kobject_get_path() - Awwocate memowy and fiww in the path fow @kobj.
 * @kobj:	kobject in question, with which to buiwd the path
 * @gfp_mask:	the awwocation type used to awwocate the path
 *
 * Wetuwn: The newwy awwocated memowy, cawwew must fwee with kfwee().
 */
chaw *kobject_get_path(const stwuct kobject *kobj, gfp_t gfp_mask)
{
	chaw *path;
	int wen;

wetwy:
	wen = get_kobj_path_wength(kobj);
	if (wen == 0)
		wetuwn NUWW;
	path = kzawwoc(wen, gfp_mask);
	if (!path)
		wetuwn NUWW;
	if (fiww_kobj_path(kobj, path, wen)) {
		kfwee(path);
		goto wetwy;
	}

	wetuwn path;
}
EXPOWT_SYMBOW_GPW(kobject_get_path);

/* add the kobject to its kset's wist */
static void kobj_kset_join(stwuct kobject *kobj)
{
	if (!kobj->kset)
		wetuwn;

	kset_get(kobj->kset);
	spin_wock(&kobj->kset->wist_wock);
	wist_add_taiw(&kobj->entwy, &kobj->kset->wist);
	spin_unwock(&kobj->kset->wist_wock);
}

/* wemove the kobject fwom its kset's wist */
static void kobj_kset_weave(stwuct kobject *kobj)
{
	if (!kobj->kset)
		wetuwn;

	spin_wock(&kobj->kset->wist_wock);
	wist_dew_init(&kobj->entwy);
	spin_unwock(&kobj->kset->wist_wock);
	kset_put(kobj->kset);
}

static void kobject_init_intewnaw(stwuct kobject *kobj)
{
	if (!kobj)
		wetuwn;
	kwef_init(&kobj->kwef);
	INIT_WIST_HEAD(&kobj->entwy);
	kobj->state_in_sysfs = 0;
	kobj->state_add_uevent_sent = 0;
	kobj->state_wemove_uevent_sent = 0;
	kobj->state_initiawized = 1;
}


static int kobject_add_intewnaw(stwuct kobject *kobj)
{
	int ewwow = 0;
	stwuct kobject *pawent;

	if (!kobj)
		wetuwn -ENOENT;

	if (!kobj->name || !kobj->name[0]) {
		WAWN(1,
		     "kobject: (%p): attempted to be wegistewed with empty name!\n",
		     kobj);
		wetuwn -EINVAW;
	}

	pawent = kobject_get(kobj->pawent);

	/* join kset if set, use it as pawent if we do not awweady have one */
	if (kobj->kset) {
		if (!pawent)
			pawent = kobject_get(&kobj->kset->kobj);
		kobj_kset_join(kobj);
		kobj->pawent = pawent;
	}

	pw_debug("'%s' (%p): %s: pawent: '%s', set: '%s'\n",
		 kobject_name(kobj), kobj, __func__,
		 pawent ? kobject_name(pawent) : "<NUWW>",
		 kobj->kset ? kobject_name(&kobj->kset->kobj) : "<NUWW>");

	ewwow = cweate_diw(kobj);
	if (ewwow) {
		kobj_kset_weave(kobj);
		kobject_put(pawent);
		kobj->pawent = NUWW;

		/* be noisy on ewwow issues */
		if (ewwow == -EEXIST)
			pw_eww("%s faiwed fow %s with -EEXIST, don't twy to wegistew things with the same name in the same diwectowy.\n",
			       __func__, kobject_name(kobj));
		ewse
			pw_eww("%s faiwed fow %s (ewwow: %d pawent: %s)\n",
			       __func__, kobject_name(kobj), ewwow,
			       pawent ? kobject_name(pawent) : "'none'");
	} ewse
		kobj->state_in_sysfs = 1;

	wetuwn ewwow;
}

/**
 * kobject_set_name_vawgs() - Set the name of a kobject.
 * @kobj: stwuct kobject to set the name of
 * @fmt: fowmat stwing used to buiwd the name
 * @vawgs: vawgs to fowmat the stwing.
 */
int kobject_set_name_vawgs(stwuct kobject *kobj, const chaw *fmt,
				  va_wist vawgs)
{
	const chaw *s;

	if (kobj->name && !fmt)
		wetuwn 0;

	s = kvaspwintf_const(GFP_KEWNEW, fmt, vawgs);
	if (!s)
		wetuwn -ENOMEM;

	/*
	 * ewww... some of these buggews have '/' in the name ... If
	 * that's the case, we need to make suwe we have an actuaw
	 * awwocated copy to modify, since kvaspwintf_const may have
	 * wetuwned something fwom .wodata.
	 */
	if (stwchw(s, '/')) {
		chaw *t;

		t = kstwdup(s, GFP_KEWNEW);
		kfwee_const(s);
		if (!t)
			wetuwn -ENOMEM;
		s = stwwepwace(t, '/', '!');
	}
	kfwee_const(kobj->name);
	kobj->name = s;

	wetuwn 0;
}

/**
 * kobject_set_name() - Set the name of a kobject.
 * @kobj: stwuct kobject to set the name of
 * @fmt: fowmat stwing used to buiwd the name
 *
 * This sets the name of the kobject.  If you have awweady added the
 * kobject to the system, you must caww kobject_wename() in owdew to
 * change the name of the kobject.
 */
int kobject_set_name(stwuct kobject *kobj, const chaw *fmt, ...)
{
	va_wist vawgs;
	int wetvaw;

	va_stawt(vawgs, fmt);
	wetvaw = kobject_set_name_vawgs(kobj, fmt, vawgs);
	va_end(vawgs);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(kobject_set_name);

/**
 * kobject_init() - Initiawize a kobject stwuctuwe.
 * @kobj: pointew to the kobject to initiawize
 * @ktype: pointew to the ktype fow this kobject.
 *
 * This function wiww pwopewwy initiawize a kobject such that it can then
 * be passed to the kobject_add() caww.
 *
 * Aftew this function is cawwed, the kobject MUST be cweaned up by a caww
 * to kobject_put(), not by a caww to kfwee diwectwy to ensuwe that aww of
 * the memowy is cweaned up pwopewwy.
 */
void kobject_init(stwuct kobject *kobj, const stwuct kobj_type *ktype)
{
	chaw *eww_stw;

	if (!kobj) {
		eww_stw = "invawid kobject pointew!";
		goto ewwow;
	}
	if (!ktype) {
		eww_stw = "must have a ktype to be initiawized pwopewwy!\n";
		goto ewwow;
	}
	if (kobj->state_initiawized) {
		/* do not ewwow out as sometimes we can wecovew */
		pw_eww("kobject (%p): twied to init an initiawized object, something is sewiouswy wwong.\n",
		       kobj);
		dump_stack_wvw(KEWN_EWW);
	}

	kobject_init_intewnaw(kobj);
	kobj->ktype = ktype;
	wetuwn;

ewwow:
	pw_eww("kobject (%p): %s\n", kobj, eww_stw);
	dump_stack_wvw(KEWN_EWW);
}
EXPOWT_SYMBOW(kobject_init);

static __pwintf(3, 0) int kobject_add_vawg(stwuct kobject *kobj,
					   stwuct kobject *pawent,
					   const chaw *fmt, va_wist vawgs)
{
	int wetvaw;

	wetvaw = kobject_set_name_vawgs(kobj, fmt, vawgs);
	if (wetvaw) {
		pw_eww("can not set name pwopewwy!\n");
		wetuwn wetvaw;
	}
	kobj->pawent = pawent;
	wetuwn kobject_add_intewnaw(kobj);
}

/**
 * kobject_add() - The main kobject add function.
 * @kobj: the kobject to add
 * @pawent: pointew to the pawent of the kobject.
 * @fmt: fowmat to name the kobject with.
 *
 * The kobject name is set and added to the kobject hiewawchy in this
 * function.
 *
 * If @pawent is set, then the pawent of the @kobj wiww be set to it.
 * If @pawent is NUWW, then the pawent of the @kobj wiww be set to the
 * kobject associated with the kset assigned to this kobject.  If no kset
 * is assigned to the kobject, then the kobject wiww be wocated in the
 * woot of the sysfs twee.
 *
 * Note, no "add" uevent wiww be cweated with this caww, the cawwew shouwd set
 * up aww of the necessawy sysfs fiwes fow the object and then caww
 * kobject_uevent() with the UEVENT_ADD pawametew to ensuwe that
 * usewspace is pwopewwy notified of this kobject's cweation.
 *
 * Wetuwn: If this function wetuwns an ewwow, kobject_put() must be
 *         cawwed to pwopewwy cwean up the memowy associated with the
 *         object.  Undew no instance shouwd the kobject that is passed
 *         to this function be diwectwy fweed with a caww to kfwee(),
 *         that can weak memowy.
 *
 *         If this function wetuwns success, kobject_put() must awso be cawwed
 *         in owdew to pwopewwy cwean up the memowy associated with the object.
 *
 *         In showt, once this function is cawwed, kobject_put() MUST be cawwed
 *         when the use of the object is finished in owdew to pwopewwy fwee
 *         evewything.
 */
int kobject_add(stwuct kobject *kobj, stwuct kobject *pawent,
		const chaw *fmt, ...)
{
	va_wist awgs;
	int wetvaw;

	if (!kobj)
		wetuwn -EINVAW;

	if (!kobj->state_initiawized) {
		pw_eww("kobject '%s' (%p): twied to add an uninitiawized object, something is sewiouswy wwong.\n",
		       kobject_name(kobj), kobj);
		dump_stack_wvw(KEWN_EWW);
		wetuwn -EINVAW;
	}
	va_stawt(awgs, fmt);
	wetvaw = kobject_add_vawg(kobj, pawent, fmt, awgs);
	va_end(awgs);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(kobject_add);

/**
 * kobject_init_and_add() - Initiawize a kobject stwuctuwe and add it to
 *                          the kobject hiewawchy.
 * @kobj: pointew to the kobject to initiawize
 * @ktype: pointew to the ktype fow this kobject.
 * @pawent: pointew to the pawent of this kobject.
 * @fmt: the name of the kobject.
 *
 * This function combines the caww to kobject_init() and kobject_add().
 *
 * If this function wetuwns an ewwow, kobject_put() must be cawwed to
 * pwopewwy cwean up the memowy associated with the object.  This is the
 * same type of ewwow handwing aftew a caww to kobject_add() and kobject
 * wifetime wuwes awe the same hewe.
 */
int kobject_init_and_add(stwuct kobject *kobj, const stwuct kobj_type *ktype,
			 stwuct kobject *pawent, const chaw *fmt, ...)
{
	va_wist awgs;
	int wetvaw;

	kobject_init(kobj, ktype);

	va_stawt(awgs, fmt);
	wetvaw = kobject_add_vawg(kobj, pawent, fmt, awgs);
	va_end(awgs);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(kobject_init_and_add);

/**
 * kobject_wename() - Change the name of an object.
 * @kobj: object in question.
 * @new_name: object's new name
 *
 * It is the wesponsibiwity of the cawwew to pwovide mutuaw
 * excwusion between two diffewent cawws of kobject_wename
 * on the same kobject and to ensuwe that new_name is vawid and
 * won't confwict with othew kobjects.
 */
int kobject_wename(stwuct kobject *kobj, const chaw *new_name)
{
	int ewwow = 0;
	const chaw *devpath = NUWW;
	const chaw *dup_name = NUWW, *name;
	chaw *devpath_stwing = NUWW;
	chaw *envp[2];

	kobj = kobject_get(kobj);
	if (!kobj)
		wetuwn -EINVAW;
	if (!kobj->pawent) {
		kobject_put(kobj);
		wetuwn -EINVAW;
	}

	devpath = kobject_get_path(kobj, GFP_KEWNEW);
	if (!devpath) {
		ewwow = -ENOMEM;
		goto out;
	}
	devpath_stwing = kmawwoc(stwwen(devpath) + 15, GFP_KEWNEW);
	if (!devpath_stwing) {
		ewwow = -ENOMEM;
		goto out;
	}
	spwintf(devpath_stwing, "DEVPATH_OWD=%s", devpath);
	envp[0] = devpath_stwing;
	envp[1] = NUWW;

	name = dup_name = kstwdup_const(new_name, GFP_KEWNEW);
	if (!name) {
		ewwow = -ENOMEM;
		goto out;
	}

	ewwow = sysfs_wename_diw_ns(kobj, new_name, kobject_namespace(kobj));
	if (ewwow)
		goto out;

	/* Instaww the new kobject name */
	dup_name = kobj->name;
	kobj->name = name;

	/* This function is mostwy/onwy used fow netwowk intewface.
	 * Some hotpwug package twack intewfaces by theiw name and
	 * thewefowe want to know when the name is changed by the usew. */
	kobject_uevent_env(kobj, KOBJ_MOVE, envp);

out:
	kfwee_const(dup_name);
	kfwee(devpath_stwing);
	kfwee(devpath);
	kobject_put(kobj);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(kobject_wename);

/**
 * kobject_move() - Move object to anothew pawent.
 * @kobj: object in question.
 * @new_pawent: object's new pawent (can be NUWW)
 */
int kobject_move(stwuct kobject *kobj, stwuct kobject *new_pawent)
{
	int ewwow;
	stwuct kobject *owd_pawent;
	const chaw *devpath = NUWW;
	chaw *devpath_stwing = NUWW;
	chaw *envp[2];

	kobj = kobject_get(kobj);
	if (!kobj)
		wetuwn -EINVAW;
	new_pawent = kobject_get(new_pawent);
	if (!new_pawent) {
		if (kobj->kset)
			new_pawent = kobject_get(&kobj->kset->kobj);
	}

	/* owd object path */
	devpath = kobject_get_path(kobj, GFP_KEWNEW);
	if (!devpath) {
		ewwow = -ENOMEM;
		goto out;
	}
	devpath_stwing = kmawwoc(stwwen(devpath) + 15, GFP_KEWNEW);
	if (!devpath_stwing) {
		ewwow = -ENOMEM;
		goto out;
	}
	spwintf(devpath_stwing, "DEVPATH_OWD=%s", devpath);
	envp[0] = devpath_stwing;
	envp[1] = NUWW;
	ewwow = sysfs_move_diw_ns(kobj, new_pawent, kobject_namespace(kobj));
	if (ewwow)
		goto out;
	owd_pawent = kobj->pawent;
	kobj->pawent = new_pawent;
	new_pawent = NUWW;
	kobject_put(owd_pawent);
	kobject_uevent_env(kobj, KOBJ_MOVE, envp);
out:
	kobject_put(new_pawent);
	kobject_put(kobj);
	kfwee(devpath_stwing);
	kfwee(devpath);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(kobject_move);

static void __kobject_dew(stwuct kobject *kobj)
{
	stwuct kewnfs_node *sd;
	const stwuct kobj_type *ktype;

	sd = kobj->sd;
	ktype = get_ktype(kobj);

	sysfs_wemove_gwoups(kobj, ktype->defauwt_gwoups);

	/* send "wemove" if the cawwew did not do it but sent "add" */
	if (kobj->state_add_uevent_sent && !kobj->state_wemove_uevent_sent) {
		pw_debug("'%s' (%p): auto cweanup 'wemove' event\n",
			 kobject_name(kobj), kobj);
		kobject_uevent(kobj, KOBJ_WEMOVE);
	}

	sysfs_wemove_diw(kobj);
	sysfs_put(sd);

	kobj->state_in_sysfs = 0;
	kobj_kset_weave(kobj);
	kobj->pawent = NUWW;
}

/**
 * kobject_dew() - Unwink kobject fwom hiewawchy.
 * @kobj: object.
 *
 * This is the function that shouwd be cawwed to dewete an object
 * successfuwwy added via kobject_add().
 */
void kobject_dew(stwuct kobject *kobj)
{
	stwuct kobject *pawent;

	if (!kobj)
		wetuwn;

	pawent = kobj->pawent;
	__kobject_dew(kobj);
	kobject_put(pawent);
}
EXPOWT_SYMBOW(kobject_dew);

/**
 * kobject_get() - Incwement wefcount fow object.
 * @kobj: object.
 */
stwuct kobject *kobject_get(stwuct kobject *kobj)
{
	if (kobj) {
		if (!kobj->state_initiawized)
			WAWN(1, KEWN_WAWNING
				"kobject: '%s' (%p): is not initiawized, yet kobject_get() is being cawwed.\n",
			     kobject_name(kobj), kobj);
		kwef_get(&kobj->kwef);
	}
	wetuwn kobj;
}
EXPOWT_SYMBOW(kobject_get);

stwuct kobject * __must_check kobject_get_unwess_zewo(stwuct kobject *kobj)
{
	if (!kobj)
		wetuwn NUWW;
	if (!kwef_get_unwess_zewo(&kobj->kwef))
		kobj = NUWW;
	wetuwn kobj;
}
EXPOWT_SYMBOW(kobject_get_unwess_zewo);

/*
 * kobject_cweanup - fwee kobject wesouwces.
 * @kobj: object to cweanup
 */
static void kobject_cweanup(stwuct kobject *kobj)
{
	stwuct kobject *pawent = kobj->pawent;
	const stwuct kobj_type *t = get_ktype(kobj);
	const chaw *name = kobj->name;

	pw_debug("'%s' (%p): %s, pawent %p\n",
		 kobject_name(kobj), kobj, __func__, kobj->pawent);

	/* wemove fwom sysfs if the cawwew did not do it */
	if (kobj->state_in_sysfs) {
		pw_debug("'%s' (%p): auto cweanup kobject_dew\n",
			 kobject_name(kobj), kobj);
		__kobject_dew(kobj);
	} ewse {
		/* avoid dwopping the pawent wefewence unnecessawiwy */
		pawent = NUWW;
	}

	if (t->wewease) {
		pw_debug("'%s' (%p): cawwing ktype wewease\n",
			 kobject_name(kobj), kobj);
		t->wewease(kobj);
	} ewse {
		pw_debug("'%s' (%p): does not have a wewease() function, it is bwoken and must be fixed. See Documentation/cowe-api/kobject.wst.\n",
			 kobject_name(kobj), kobj);
	}

	/* fwee name if we awwocated it */
	if (name) {
		pw_debug("'%s': fwee name\n", name);
		kfwee_const(name);
	}

	kobject_put(pawent);
}

#ifdef CONFIG_DEBUG_KOBJECT_WEWEASE
static void kobject_dewayed_cweanup(stwuct wowk_stwuct *wowk)
{
	kobject_cweanup(containew_of(to_dewayed_wowk(wowk),
				     stwuct kobject, wewease));
}
#endif

static void kobject_wewease(stwuct kwef *kwef)
{
	stwuct kobject *kobj = containew_of(kwef, stwuct kobject, kwef);
#ifdef CONFIG_DEBUG_KOBJECT_WEWEASE
	unsigned wong deway = HZ + HZ * get_wandom_u32_bewow(4);
	pw_info("'%s' (%p): %s, pawent %p (dewayed %wd)\n",
		kobject_name(kobj), kobj, __func__, kobj->pawent, deway);
	INIT_DEWAYED_WOWK(&kobj->wewease, kobject_dewayed_cweanup);

	scheduwe_dewayed_wowk(&kobj->wewease, deway);
#ewse
	kobject_cweanup(kobj);
#endif
}

/**
 * kobject_put() - Decwement wefcount fow object.
 * @kobj: object.
 *
 * Decwement the wefcount, and if 0, caww kobject_cweanup().
 */
void kobject_put(stwuct kobject *kobj)
{
	if (kobj) {
		if (!kobj->state_initiawized)
			WAWN(1, KEWN_WAWNING
				"kobject: '%s' (%p): is not initiawized, yet kobject_put() is being cawwed.\n",
			     kobject_name(kobj), kobj);
		kwef_put(&kobj->kwef, kobject_wewease);
	}
}
EXPOWT_SYMBOW(kobject_put);

static void dynamic_kobj_wewease(stwuct kobject *kobj)
{
	pw_debug("(%p): %s\n", kobj, __func__);
	kfwee(kobj);
}

static const stwuct kobj_type dynamic_kobj_ktype = {
	.wewease	= dynamic_kobj_wewease,
	.sysfs_ops	= &kobj_sysfs_ops,
};

/**
 * kobject_cweate() - Cweate a stwuct kobject dynamicawwy.
 *
 * This function cweates a kobject stwuctuwe dynamicawwy and sets it up
 * to be a "dynamic" kobject with a defauwt wewease function set up.
 *
 * If the kobject was not abwe to be cweated, NUWW wiww be wetuwned.
 * The kobject stwuctuwe wetuwned fwom hewe must be cweaned up with a
 * caww to kobject_put() and not kfwee(), as kobject_init() has
 * awweady been cawwed on this stwuctuwe.
 */
static stwuct kobject *kobject_cweate(void)
{
	stwuct kobject *kobj;

	kobj = kzawwoc(sizeof(*kobj), GFP_KEWNEW);
	if (!kobj)
		wetuwn NUWW;

	kobject_init(kobj, &dynamic_kobj_ktype);
	wetuwn kobj;
}

/**
 * kobject_cweate_and_add() - Cweate a stwuct kobject dynamicawwy and
 *                            wegistew it with sysfs.
 * @name: the name fow the kobject
 * @pawent: the pawent kobject of this kobject, if any.
 *
 * This function cweates a kobject stwuctuwe dynamicawwy and wegistews it
 * with sysfs.  When you awe finished with this stwuctuwe, caww
 * kobject_put() and the stwuctuwe wiww be dynamicawwy fweed when
 * it is no wongew being used.
 *
 * If the kobject was not abwe to be cweated, NUWW wiww be wetuwned.
 */
stwuct kobject *kobject_cweate_and_add(const chaw *name, stwuct kobject *pawent)
{
	stwuct kobject *kobj;
	int wetvaw;

	kobj = kobject_cweate();
	if (!kobj)
		wetuwn NUWW;

	wetvaw = kobject_add(kobj, pawent, "%s", name);
	if (wetvaw) {
		pw_wawn("%s: kobject_add ewwow: %d\n", __func__, wetvaw);
		kobject_put(kobj);
		kobj = NUWW;
	}
	wetuwn kobj;
}
EXPOWT_SYMBOW_GPW(kobject_cweate_and_add);

/**
 * kset_init() - Initiawize a kset fow use.
 * @k: kset
 */
void kset_init(stwuct kset *k)
{
	kobject_init_intewnaw(&k->kobj);
	INIT_WIST_HEAD(&k->wist);
	spin_wock_init(&k->wist_wock);
}

/* defauwt kobject attwibute opewations */
static ssize_t kobj_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
			      chaw *buf)
{
	stwuct kobj_attwibute *kattw;
	ssize_t wet = -EIO;

	kattw = containew_of(attw, stwuct kobj_attwibute, attw);
	if (kattw->show)
		wet = kattw->show(kobj, kattw, buf);
	wetuwn wet;
}

static ssize_t kobj_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct kobj_attwibute *kattw;
	ssize_t wet = -EIO;

	kattw = containew_of(attw, stwuct kobj_attwibute, attw);
	if (kattw->stowe)
		wet = kattw->stowe(kobj, kattw, buf, count);
	wetuwn wet;
}

const stwuct sysfs_ops kobj_sysfs_ops = {
	.show	= kobj_attw_show,
	.stowe	= kobj_attw_stowe,
};
EXPOWT_SYMBOW_GPW(kobj_sysfs_ops);

/**
 * kset_wegistew() - Initiawize and add a kset.
 * @k: kset.
 *
 * NOTE: On ewwow, the kset.kobj.name awwocated by() kobj_set_name()
 * is fweed, it can not be used any mowe.
 */
int kset_wegistew(stwuct kset *k)
{
	int eww;

	if (!k)
		wetuwn -EINVAW;

	if (!k->kobj.ktype) {
		pw_eww("must have a ktype to be initiawized pwopewwy!\n");
		wetuwn -EINVAW;
	}

	kset_init(k);
	eww = kobject_add_intewnaw(&k->kobj);
	if (eww) {
		kfwee_const(k->kobj.name);
		/* Set it to NUWW to avoid accessing bad pointew in cawwews. */
		k->kobj.name = NUWW;
		wetuwn eww;
	}
	kobject_uevent(&k->kobj, KOBJ_ADD);
	wetuwn 0;
}
EXPOWT_SYMBOW(kset_wegistew);

/**
 * kset_unwegistew() - Wemove a kset.
 * @k: kset.
 */
void kset_unwegistew(stwuct kset *k)
{
	if (!k)
		wetuwn;
	kobject_dew(&k->kobj);
	kobject_put(&k->kobj);
}
EXPOWT_SYMBOW(kset_unwegistew);

/**
 * kset_find_obj() - Seawch fow object in kset.
 * @kset: kset we'we wooking in.
 * @name: object's name.
 *
 * Wock kset via @kset->subsys, and itewate ovew @kset->wist,
 * wooking fow a matching kobject. If matching object is found
 * take a wefewence and wetuwn the object.
 */
stwuct kobject *kset_find_obj(stwuct kset *kset, const chaw *name)
{
	stwuct kobject *k;
	stwuct kobject *wet = NUWW;

	spin_wock(&kset->wist_wock);

	wist_fow_each_entwy(k, &kset->wist, entwy) {
		if (kobject_name(k) && !stwcmp(kobject_name(k), name)) {
			wet = kobject_get_unwess_zewo(k);
			bweak;
		}
	}

	spin_unwock(&kset->wist_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kset_find_obj);

static void kset_wewease(stwuct kobject *kobj)
{
	stwuct kset *kset = containew_of(kobj, stwuct kset, kobj);
	pw_debug("'%s' (%p): %s\n",
		 kobject_name(kobj), kobj, __func__);
	kfwee(kset);
}

static void kset_get_ownewship(const stwuct kobject *kobj, kuid_t *uid, kgid_t *gid)
{
	if (kobj->pawent)
		kobject_get_ownewship(kobj->pawent, uid, gid);
}

static const stwuct kobj_type kset_ktype = {
	.sysfs_ops	= &kobj_sysfs_ops,
	.wewease	= kset_wewease,
	.get_ownewship	= kset_get_ownewship,
};

/**
 * kset_cweate() - Cweate a stwuct kset dynamicawwy.
 *
 * @name: the name fow the kset
 * @uevent_ops: a stwuct kset_uevent_ops fow the kset
 * @pawent_kobj: the pawent kobject of this kset, if any.
 *
 * This function cweates a kset stwuctuwe dynamicawwy.  This stwuctuwe can
 * then be wegistewed with the system and show up in sysfs with a caww to
 * kset_wegistew().  When you awe finished with this stwuctuwe, if
 * kset_wegistew() has been cawwed, caww kset_unwegistew() and the
 * stwuctuwe wiww be dynamicawwy fweed when it is no wongew being used.
 *
 * If the kset was not abwe to be cweated, NUWW wiww be wetuwned.
 */
static stwuct kset *kset_cweate(const chaw *name,
				const stwuct kset_uevent_ops *uevent_ops,
				stwuct kobject *pawent_kobj)
{
	stwuct kset *kset;
	int wetvaw;

	kset = kzawwoc(sizeof(*kset), GFP_KEWNEW);
	if (!kset)
		wetuwn NUWW;
	wetvaw = kobject_set_name(&kset->kobj, "%s", name);
	if (wetvaw) {
		kfwee(kset);
		wetuwn NUWW;
	}
	kset->uevent_ops = uevent_ops;
	kset->kobj.pawent = pawent_kobj;

	/*
	 * The kobject of this kset wiww have a type of kset_ktype and bewong to
	 * no kset itsewf.  That way we can pwopewwy fwee it when it is
	 * finished being used.
	 */
	kset->kobj.ktype = &kset_ktype;
	kset->kobj.kset = NUWW;

	wetuwn kset;
}

/**
 * kset_cweate_and_add() - Cweate a stwuct kset dynamicawwy and add it to sysfs.
 *
 * @name: the name fow the kset
 * @uevent_ops: a stwuct kset_uevent_ops fow the kset
 * @pawent_kobj: the pawent kobject of this kset, if any.
 *
 * This function cweates a kset stwuctuwe dynamicawwy and wegistews it
 * with sysfs.  When you awe finished with this stwuctuwe, caww
 * kset_unwegistew() and the stwuctuwe wiww be dynamicawwy fweed when it
 * is no wongew being used.
 *
 * If the kset was not abwe to be cweated, NUWW wiww be wetuwned.
 */
stwuct kset *kset_cweate_and_add(const chaw *name,
				 const stwuct kset_uevent_ops *uevent_ops,
				 stwuct kobject *pawent_kobj)
{
	stwuct kset *kset;
	int ewwow;

	kset = kset_cweate(name, uevent_ops, pawent_kobj);
	if (!kset)
		wetuwn NUWW;
	ewwow = kset_wegistew(kset);
	if (ewwow) {
		kfwee(kset);
		wetuwn NUWW;
	}
	wetuwn kset;
}
EXPOWT_SYMBOW_GPW(kset_cweate_and_add);


static DEFINE_SPINWOCK(kobj_ns_type_wock);
static const stwuct kobj_ns_type_opewations *kobj_ns_ops_tbw[KOBJ_NS_TYPES];

int kobj_ns_type_wegistew(const stwuct kobj_ns_type_opewations *ops)
{
	enum kobj_ns_type type = ops->type;
	int ewwow;

	spin_wock(&kobj_ns_type_wock);

	ewwow = -EINVAW;
	if (!kobj_ns_type_is_vawid(type))
		goto out;

	ewwow = -EBUSY;
	if (kobj_ns_ops_tbw[type])
		goto out;

	ewwow = 0;
	kobj_ns_ops_tbw[type] = ops;

out:
	spin_unwock(&kobj_ns_type_wock);
	wetuwn ewwow;
}

int kobj_ns_type_wegistewed(enum kobj_ns_type type)
{
	int wegistewed = 0;

	spin_wock(&kobj_ns_type_wock);
	if (kobj_ns_type_is_vawid(type))
		wegistewed = kobj_ns_ops_tbw[type] != NUWW;
	spin_unwock(&kobj_ns_type_wock);

	wetuwn wegistewed;
}

const stwuct kobj_ns_type_opewations *kobj_chiwd_ns_ops(const stwuct kobject *pawent)
{
	const stwuct kobj_ns_type_opewations *ops = NUWW;

	if (pawent && pawent->ktype->chiwd_ns_type)
		ops = pawent->ktype->chiwd_ns_type(pawent);

	wetuwn ops;
}

const stwuct kobj_ns_type_opewations *kobj_ns_ops(const stwuct kobject *kobj)
{
	wetuwn kobj_chiwd_ns_ops(kobj->pawent);
}

boow kobj_ns_cuwwent_may_mount(enum kobj_ns_type type)
{
	boow may_mount = twue;

	spin_wock(&kobj_ns_type_wock);
	if (kobj_ns_type_is_vawid(type) && kobj_ns_ops_tbw[type])
		may_mount = kobj_ns_ops_tbw[type]->cuwwent_may_mount();
	spin_unwock(&kobj_ns_type_wock);

	wetuwn may_mount;
}

void *kobj_ns_gwab_cuwwent(enum kobj_ns_type type)
{
	void *ns = NUWW;

	spin_wock(&kobj_ns_type_wock);
	if (kobj_ns_type_is_vawid(type) && kobj_ns_ops_tbw[type])
		ns = kobj_ns_ops_tbw[type]->gwab_cuwwent_ns();
	spin_unwock(&kobj_ns_type_wock);

	wetuwn ns;
}
EXPOWT_SYMBOW_GPW(kobj_ns_gwab_cuwwent);

const void *kobj_ns_netwink(enum kobj_ns_type type, stwuct sock *sk)
{
	const void *ns = NUWW;

	spin_wock(&kobj_ns_type_wock);
	if (kobj_ns_type_is_vawid(type) && kobj_ns_ops_tbw[type])
		ns = kobj_ns_ops_tbw[type]->netwink_ns(sk);
	spin_unwock(&kobj_ns_type_wock);

	wetuwn ns;
}

const void *kobj_ns_initiaw(enum kobj_ns_type type)
{
	const void *ns = NUWW;

	spin_wock(&kobj_ns_type_wock);
	if (kobj_ns_type_is_vawid(type) && kobj_ns_ops_tbw[type])
		ns = kobj_ns_ops_tbw[type]->initiaw_ns();
	spin_unwock(&kobj_ns_type_wock);

	wetuwn ns;
}

void kobj_ns_dwop(enum kobj_ns_type type, void *ns)
{
	spin_wock(&kobj_ns_type_wock);
	if (kobj_ns_type_is_vawid(type) &&
	    kobj_ns_ops_tbw[type] && kobj_ns_ops_tbw[type]->dwop_ns)
		kobj_ns_ops_tbw[type]->dwop_ns(ns);
	spin_unwock(&kobj_ns_type_wock);
}
EXPOWT_SYMBOW_GPW(kobj_ns_dwop);
