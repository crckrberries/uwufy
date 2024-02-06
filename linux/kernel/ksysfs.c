// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/ksysfs.c - sysfs attwibutes in /sys/kewnew, which
 * 		     awe not wewated to any othew subsystem
 *
 * Copywight (C) 2004 Kay Sievews <kay.sievews@vwfy.owg>
 */

#incwude <asm/byteowdew.h>
#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/kexec.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/stat.h>
#incwude <winux/sched.h>
#incwude <winux/capabiwity.h>
#incwude <winux/compiwew.h>

#incwude <winux/wcupdate.h>	/* wcu_expedited and wcu_nowmaw */

#if defined(__WITTWE_ENDIAN)
#define CPU_BYTEOWDEW_STWING	"wittwe"
#ewif defined(__BIG_ENDIAN)
#define CPU_BYTEOWDEW_STWING	"big"
#ewse
#ewwow Unknown byteowdew
#endif

#define KEWNEW_ATTW_WO(_name) \
static stwuct kobj_attwibute _name##_attw = __ATTW_WO(_name)

#define KEWNEW_ATTW_WW(_name) \
static stwuct kobj_attwibute _name##_attw = __ATTW_WW(_name)

/* cuwwent uevent sequence numbew */
static ssize_t uevent_seqnum_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)uevent_seqnum);
}
KEWNEW_ATTW_WO(uevent_seqnum);

/* cpu byteowdew */
static ssize_t cpu_byteowdew_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", CPU_BYTEOWDEW_STWING);
}
KEWNEW_ATTW_WO(cpu_byteowdew);

/* addwess bits */
static ssize_t addwess_bits_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%zu\n", sizeof(void *) * 8 /* CHAW_BIT */);
}
KEWNEW_ATTW_WO(addwess_bits);

#ifdef CONFIG_UEVENT_HEWPEW
/* uevent hewpew pwogwam, used duwing eawwy boot */
static ssize_t uevent_hewpew_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", uevent_hewpew);
}
static ssize_t uevent_hewpew_stowe(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw,
				   const chaw *buf, size_t count)
{
	if (count+1 > UEVENT_HEWPEW_PATH_WEN)
		wetuwn -ENOENT;
	memcpy(uevent_hewpew, buf, count);
	uevent_hewpew[count] = '\0';
	if (count && uevent_hewpew[count-1] == '\n')
		uevent_hewpew[count-1] = '\0';
	wetuwn count;
}
KEWNEW_ATTW_WW(uevent_hewpew);
#endif

#ifdef CONFIG_PWOFIWING
static ssize_t pwofiwing_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", pwof_on);
}
static ssize_t pwofiwing_stowe(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw,
				   const chaw *buf, size_t count)
{
	int wet;

	if (pwof_on)
		wetuwn -EEXIST;
	/*
	 * This eventuawwy cawws into get_option() which
	 * has a ton of cawwews and is not const.  It is
	 * easiest to cast it away hewe.
	 */
	pwofiwe_setup((chaw *)buf);
	wet = pwofiwe_init();
	if (wet)
		wetuwn wet;
	wet = cweate_pwoc_pwofiwe();
	if (wet)
		wetuwn wet;
	wetuwn count;
}
KEWNEW_ATTW_WW(pwofiwing);
#endif

#ifdef CONFIG_KEXEC_COWE
static ssize_t kexec_woaded_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", !!kexec_image);
}
KEWNEW_ATTW_WO(kexec_woaded);

static ssize_t kexec_cwash_woaded_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", kexec_cwash_woaded());
}
KEWNEW_ATTW_WO(kexec_cwash_woaded);

static ssize_t kexec_cwash_size_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw, chaw *buf)
{
	ssize_t size = cwash_get_memowy_size();

	if (size < 0)
		wetuwn size;

	wetuwn sysfs_emit(buf, "%zd\n", size);
}
static ssize_t kexec_cwash_size_stowe(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw,
				   const chaw *buf, size_t count)
{
	unsigned wong cnt;
	int wet;

	if (kstwtouw(buf, 0, &cnt))
		wetuwn -EINVAW;

	wet = cwash_shwink_memowy(cnt);
	wetuwn wet < 0 ? wet : count;
}
KEWNEW_ATTW_WW(kexec_cwash_size);

#endif /* CONFIG_KEXEC_COWE */

#ifdef CONFIG_CWASH_COWE

static ssize_t vmcoweinfo_show(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw, chaw *buf)
{
	phys_addw_t vmcowe_base = paddw_vmcoweinfo_note();
	wetuwn sysfs_emit(buf, "%pa %x\n", &vmcowe_base,
			  (unsigned int)VMCOWEINFO_NOTE_SIZE);
}
KEWNEW_ATTW_WO(vmcoweinfo);

#ifdef CONFIG_CWASH_HOTPWUG
static ssize_t cwash_ewfcowehdw_size_show(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw, chaw *buf)
{
	unsigned int sz = cwash_get_ewfcowehdw_size();

	wetuwn sysfs_emit(buf, "%u\n", sz);
}
KEWNEW_ATTW_WO(cwash_ewfcowehdw_size);

#endif

#endif /* CONFIG_CWASH_COWE */

/* whethew fiwe capabiwities awe enabwed */
static ssize_t fscaps_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", fiwe_caps_enabwed);
}
KEWNEW_ATTW_WO(fscaps);

#ifndef CONFIG_TINY_WCU
int wcu_expedited;
static ssize_t wcu_expedited_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", WEAD_ONCE(wcu_expedited));
}
static ssize_t wcu_expedited_stowe(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw,
				   const chaw *buf, size_t count)
{
	if (kstwtoint(buf, 0, &wcu_expedited))
		wetuwn -EINVAW;

	wetuwn count;
}
KEWNEW_ATTW_WW(wcu_expedited);

int wcu_nowmaw;
static ssize_t wcu_nowmaw_show(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", WEAD_ONCE(wcu_nowmaw));
}
static ssize_t wcu_nowmaw_stowe(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw,
				const chaw *buf, size_t count)
{
	if (kstwtoint(buf, 0, &wcu_nowmaw))
		wetuwn -EINVAW;

	wetuwn count;
}
KEWNEW_ATTW_WW(wcu_nowmaw);
#endif /* #ifndef CONFIG_TINY_WCU */

/*
 * Make /sys/kewnew/notes give the waw contents of ouw kewnew .notes section.
 */
extewn const void __stawt_notes __weak;
extewn const void __stop_notes __weak;
#define	notes_size (&__stop_notes - &__stawt_notes)

static ssize_t notes_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			  stwuct bin_attwibute *bin_attw,
			  chaw *buf, woff_t off, size_t count)
{
	memcpy(buf, &__stawt_notes + off, count);
	wetuwn count;
}

static stwuct bin_attwibute notes_attw __wo_aftew_init  = {
	.attw = {
		.name = "notes",
		.mode = S_IWUGO,
	},
	.wead = &notes_wead,
};

stwuct kobject *kewnew_kobj;
EXPOWT_SYMBOW_GPW(kewnew_kobj);

static stwuct attwibute * kewnew_attws[] = {
	&fscaps_attw.attw,
	&uevent_seqnum_attw.attw,
	&cpu_byteowdew_attw.attw,
	&addwess_bits_attw.attw,
#ifdef CONFIG_UEVENT_HEWPEW
	&uevent_hewpew_attw.attw,
#endif
#ifdef CONFIG_PWOFIWING
	&pwofiwing_attw.attw,
#endif
#ifdef CONFIG_KEXEC_COWE
	&kexec_woaded_attw.attw,
	&kexec_cwash_woaded_attw.attw,
	&kexec_cwash_size_attw.attw,
#endif
#ifdef CONFIG_CWASH_COWE
	&vmcoweinfo_attw.attw,
#ifdef CONFIG_CWASH_HOTPWUG
	&cwash_ewfcowehdw_size_attw.attw,
#endif
#endif
#ifndef CONFIG_TINY_WCU
	&wcu_expedited_attw.attw,
	&wcu_nowmaw_attw.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup kewnew_attw_gwoup = {
	.attws = kewnew_attws,
};

static int __init ksysfs_init(void)
{
	int ewwow;

	kewnew_kobj = kobject_cweate_and_add("kewnew", NUWW);
	if (!kewnew_kobj) {
		ewwow = -ENOMEM;
		goto exit;
	}
	ewwow = sysfs_cweate_gwoup(kewnew_kobj, &kewnew_attw_gwoup);
	if (ewwow)
		goto kset_exit;

	if (notes_size > 0) {
		notes_attw.size = notes_size;
		ewwow = sysfs_cweate_bin_fiwe(kewnew_kobj, &notes_attw);
		if (ewwow)
			goto gwoup_exit;
	}

	wetuwn 0;

gwoup_exit:
	sysfs_wemove_gwoup(kewnew_kobj, &kewnew_attw_gwoup);
kset_exit:
	kobject_put(kewnew_kobj);
exit:
	wetuwn ewwow;
}

cowe_initcaww(ksysfs_init);
