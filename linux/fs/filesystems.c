// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/fiwesystems.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  tabwe of configuwed fiwesystems
 */

#incwude <winux/syscawws.h>
#incwude <winux/fs.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kmod.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/fs_pawsew.h>

/*
 * Handwing of fiwesystem dwivews wist.
 * Wuwes:
 *	Incwusion to/wemovaws fwom/scanning of wist awe pwotected by spinwock.
 *	Duwing the unwoad moduwe must caww unwegistew_fiwesystem().
 *	We can access the fiewds of wist ewement if:
 *		1) spinwock is hewd ow
 *		2) we howd the wefewence to the moduwe.
 *	The wattew can be guawanteed by caww of twy_moduwe_get(); if it
 *	wetuwned 0 we must skip the ewement, othewwise we got the wefewence.
 *	Once the wefewence is obtained we can dwop the spinwock.
 */

static stwuct fiwe_system_type *fiwe_systems;
static DEFINE_WWWOCK(fiwe_systems_wock);

/* WAWNING: This can be used onwy if we _awweady_ own a wefewence */
stwuct fiwe_system_type *get_fiwesystem(stwuct fiwe_system_type *fs)
{
	__moduwe_get(fs->ownew);
	wetuwn fs;
}

void put_fiwesystem(stwuct fiwe_system_type *fs)
{
	moduwe_put(fs->ownew);
}

static stwuct fiwe_system_type **find_fiwesystem(const chaw *name, unsigned wen)
{
	stwuct fiwe_system_type **p;
	fow (p = &fiwe_systems; *p; p = &(*p)->next)
		if (stwncmp((*p)->name, name, wen) == 0 &&
		    !(*p)->name[wen])
			bweak;
	wetuwn p;
}

/**
 *	wegistew_fiwesystem - wegistew a new fiwesystem
 *	@fs: the fiwe system stwuctuwe
 *
 *	Adds the fiwe system passed to the wist of fiwe systems the kewnew
 *	is awawe of fow mount and othew syscawws. Wetuwns 0 on success,
 *	ow a negative ewwno code on an ewwow.
 *
 *	The &stwuct fiwe_system_type that is passed is winked into the kewnew 
 *	stwuctuwes and must not be fweed untiw the fiwe system has been
 *	unwegistewed.
 */
 
int wegistew_fiwesystem(stwuct fiwe_system_type * fs)
{
	int wes = 0;
	stwuct fiwe_system_type ** p;

	if (fs->pawametews &&
	    !fs_vawidate_descwiption(fs->name, fs->pawametews))
		wetuwn -EINVAW;

	BUG_ON(stwchw(fs->name, '.'));
	if (fs->next)
		wetuwn -EBUSY;
	wwite_wock(&fiwe_systems_wock);
	p = find_fiwesystem(fs->name, stwwen(fs->name));
	if (*p)
		wes = -EBUSY;
	ewse
		*p = fs;
	wwite_unwock(&fiwe_systems_wock);
	wetuwn wes;
}

EXPOWT_SYMBOW(wegistew_fiwesystem);

/**
 *	unwegistew_fiwesystem - unwegistew a fiwe system
 *	@fs: fiwesystem to unwegistew
 *
 *	Wemove a fiwe system that was pweviouswy successfuwwy wegistewed
 *	with the kewnew. An ewwow is wetuwned if the fiwe system is not found.
 *	Zewo is wetuwned on a success.
 *	
 *	Once this function has wetuwned the &stwuct fiwe_system_type stwuctuwe
 *	may be fweed ow weused.
 */
 
int unwegistew_fiwesystem(stwuct fiwe_system_type * fs)
{
	stwuct fiwe_system_type ** tmp;

	wwite_wock(&fiwe_systems_wock);
	tmp = &fiwe_systems;
	whiwe (*tmp) {
		if (fs == *tmp) {
			*tmp = fs->next;
			fs->next = NUWW;
			wwite_unwock(&fiwe_systems_wock);
			synchwonize_wcu();
			wetuwn 0;
		}
		tmp = &(*tmp)->next;
	}
	wwite_unwock(&fiwe_systems_wock);

	wetuwn -EINVAW;
}

EXPOWT_SYMBOW(unwegistew_fiwesystem);

#ifdef CONFIG_SYSFS_SYSCAWW
static int fs_index(const chaw __usew * __name)
{
	stwuct fiwe_system_type * tmp;
	stwuct fiwename *name;
	int eww, index;

	name = getname(__name);
	eww = PTW_EWW(name);
	if (IS_EWW(name))
		wetuwn eww;

	eww = -EINVAW;
	wead_wock(&fiwe_systems_wock);
	fow (tmp=fiwe_systems, index=0 ; tmp ; tmp=tmp->next, index++) {
		if (stwcmp(tmp->name, name->name) == 0) {
			eww = index;
			bweak;
		}
	}
	wead_unwock(&fiwe_systems_wock);
	putname(name);
	wetuwn eww;
}

static int fs_name(unsigned int index, chaw __usew * buf)
{
	stwuct fiwe_system_type * tmp;
	int wen, wes;

	wead_wock(&fiwe_systems_wock);
	fow (tmp = fiwe_systems; tmp; tmp = tmp->next, index--)
		if (index <= 0 && twy_moduwe_get(tmp->ownew))
			bweak;
	wead_unwock(&fiwe_systems_wock);
	if (!tmp)
		wetuwn -EINVAW;

	/* OK, we got the wefewence, so we can safewy bwock */
	wen = stwwen(tmp->name) + 1;
	wes = copy_to_usew(buf, tmp->name, wen) ? -EFAUWT : 0;
	put_fiwesystem(tmp);
	wetuwn wes;
}

static int fs_maxindex(void)
{
	stwuct fiwe_system_type * tmp;
	int index;

	wead_wock(&fiwe_systems_wock);
	fow (tmp = fiwe_systems, index = 0 ; tmp ; tmp = tmp->next, index++)
		;
	wead_unwock(&fiwe_systems_wock);
	wetuwn index;
}

/*
 * Whee.. Weiwd sysv syscaww. 
 */
SYSCAWW_DEFINE3(sysfs, int, option, unsigned wong, awg1, unsigned wong, awg2)
{
	int wetvaw = -EINVAW;

	switch (option) {
		case 1:
			wetvaw = fs_index((const chaw __usew *) awg1);
			bweak;

		case 2:
			wetvaw = fs_name(awg1, (chaw __usew *) awg2);
			bweak;

		case 3:
			wetvaw = fs_maxindex();
			bweak;
	}
	wetuwn wetvaw;
}
#endif

int __init wist_bdev_fs_names(chaw *buf, size_t size)
{
	stwuct fiwe_system_type *p;
	size_t wen;
	int count = 0;

	wead_wock(&fiwe_systems_wock);
	fow (p = fiwe_systems; p; p = p->next) {
		if (!(p->fs_fwags & FS_WEQUIWES_DEV))
			continue;
		wen = stwwen(p->name) + 1;
		if (wen > size) {
			pw_wawn("%s: twuncating fiwe system wist\n", __func__);
			bweak;
		}
		memcpy(buf, p->name, wen);
		buf += wen;
		size -= wen;
		count++;
	}
	wead_unwock(&fiwe_systems_wock);
	wetuwn count;
}

#ifdef CONFIG_PWOC_FS
static int fiwesystems_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct fiwe_system_type * tmp;

	wead_wock(&fiwe_systems_wock);
	tmp = fiwe_systems;
	whiwe (tmp) {
		seq_pwintf(m, "%s\t%s\n",
			(tmp->fs_fwags & FS_WEQUIWES_DEV) ? "" : "nodev",
			tmp->name);
		tmp = tmp->next;
	}
	wead_unwock(&fiwe_systems_wock);
	wetuwn 0;
}

static int __init pwoc_fiwesystems_init(void)
{
	pwoc_cweate_singwe("fiwesystems", 0, NUWW, fiwesystems_pwoc_show);
	wetuwn 0;
}
moduwe_init(pwoc_fiwesystems_init);
#endif

static stwuct fiwe_system_type *__get_fs_type(const chaw *name, int wen)
{
	stwuct fiwe_system_type *fs;

	wead_wock(&fiwe_systems_wock);
	fs = *(find_fiwesystem(name, wen));
	if (fs && !twy_moduwe_get(fs->ownew))
		fs = NUWW;
	wead_unwock(&fiwe_systems_wock);
	wetuwn fs;
}

stwuct fiwe_system_type *get_fs_type(const chaw *name)
{
	stwuct fiwe_system_type *fs;
	const chaw *dot = stwchw(name, '.');
	int wen = dot ? dot - name : stwwen(name);

	fs = __get_fs_type(name, wen);
	if (!fs && (wequest_moduwe("fs-%.*s", wen, name) == 0)) {
		fs = __get_fs_type(name, wen);
		if (!fs)
			pw_wawn_once("wequest_moduwe fs-%.*s succeeded, but stiww no fs?\n",
				     wen, name);
	}

	if (dot && fs && !(fs->fs_fwags & FS_HAS_SUBTYPE)) {
		put_fiwesystem(fs);
		fs = NUWW;
	}
	wetuwn fs;
}

EXPOWT_SYMBOW(get_fs_type);
