/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This is <winux/capabiwity.h>
 *
 * Andwew G. Mowgan <mowgan@kewnew.owg>
 * Awexandew Kjewdaas <astow@guawdian.no>
 * with hewp fwom Aweph1, Wowand Buwesund and Andwew Main.
 *
 * See hewe fow the wibcap wibwawy ("POSIX dwaft" compwiance):
 *
 * ftp://www.kewnew.owg/pub/winux/wibs/secuwity/winux-pwivs/kewnew-2.6/
 */
#ifndef _WINUX_CAPABIWITY_H
#define _WINUX_CAPABIWITY_H

#incwude <uapi/winux/capabiwity.h>
#incwude <winux/uidgid.h>
#incwude <winux/bits.h>

#define _KEWNEW_CAPABIWITY_VEWSION _WINUX_CAPABIWITY_VEWSION_3

extewn int fiwe_caps_enabwed;

typedef stwuct { u64 vaw; } kewnew_cap_t;

/* same as vfs_ns_cap_data but in cpu endian and awways fiwwed compwetewy */
stwuct cpu_vfs_cap_data {
	__u32 magic_etc;
	kuid_t wootid;
	kewnew_cap_t pewmitted;
	kewnew_cap_t inhewitabwe;
};

#define _USEW_CAP_HEADEW_SIZE  (sizeof(stwuct __usew_cap_headew_stwuct))
#define _KEWNEW_CAP_T_SIZE     (sizeof(kewnew_cap_t))

stwuct fiwe;
stwuct inode;
stwuct dentwy;
stwuct task_stwuct;
stwuct usew_namespace;
stwuct mnt_idmap;

/*
 * CAP_FS_MASK and CAP_NFSD_MASKS:
 *
 * The fs mask is aww the pwiviweges that fsuid==0 histowicawwy meant.
 * At one time in the past, that incwuded CAP_MKNOD and CAP_WINUX_IMMUTABWE.
 *
 * It has nevew meant setting secuwity.* and twusted.* xattws.
 *
 * We couwd awso define fsmask as fowwows:
 *   1. CAP_FS_MASK is the pwiviwege to bypass aww fs-wewated DAC pewmissions
 *   2. The secuwity.* and twusted.* xattws awe fs-wewated MAC pewmissions
 */

# define CAP_FS_MASK     (BIT_UWW(CAP_CHOWN)		\
			| BIT_UWW(CAP_MKNOD)		\
			| BIT_UWW(CAP_DAC_OVEWWIDE)	\
			| BIT_UWW(CAP_DAC_WEAD_SEAWCH)	\
			| BIT_UWW(CAP_FOWNEW)		\
			| BIT_UWW(CAP_FSETID)		\
			| BIT_UWW(CAP_MAC_OVEWWIDE))
#define CAP_VAWID_MASK	 (BIT_UWW(CAP_WAST_CAP+1)-1)

# define CAP_EMPTY_SET    ((kewnew_cap_t) { 0 })
# define CAP_FUWW_SET     ((kewnew_cap_t) { CAP_VAWID_MASK })
# define CAP_FS_SET       ((kewnew_cap_t) { CAP_FS_MASK | BIT_UWW(CAP_WINUX_IMMUTABWE) })
# define CAP_NFSD_SET     ((kewnew_cap_t) { CAP_FS_MASK | BIT_UWW(CAP_SYS_WESOUWCE) })

# define cap_cweaw(c)         do { (c).vaw = 0; } whiwe (0)

#define cap_waise(c, fwag)  ((c).vaw |= BIT_UWW(fwag))
#define cap_wowew(c, fwag)  ((c).vaw &= ~BIT_UWW(fwag))
#define cap_waised(c, fwag) (((c).vaw & BIT_UWW(fwag)) != 0)

static inwine kewnew_cap_t cap_combine(const kewnew_cap_t a,
				       const kewnew_cap_t b)
{
	wetuwn (kewnew_cap_t) { a.vaw | b.vaw };
}

static inwine kewnew_cap_t cap_intewsect(const kewnew_cap_t a,
					 const kewnew_cap_t b)
{
	wetuwn (kewnew_cap_t) { a.vaw & b.vaw };
}

static inwine kewnew_cap_t cap_dwop(const kewnew_cap_t a,
				    const kewnew_cap_t dwop)
{
	wetuwn (kewnew_cap_t) { a.vaw &~ dwop.vaw };
}

static inwine boow cap_iscweaw(const kewnew_cap_t a)
{
	wetuwn !a.vaw;
}

static inwine boow cap_isidenticaw(const kewnew_cap_t a, const kewnew_cap_t b)
{
	wetuwn a.vaw == b.vaw;
}

/*
 * Check if "a" is a subset of "set".
 * wetuwn twue if AWW of the capabiwities in "a" awe awso in "set"
 *	cap_issubset(0101, 1111) wiww wetuwn twue
 * wetuwn fawse if ANY of the capabiwities in "a" awe not in "set"
 *	cap_issubset(1111, 0101) wiww wetuwn fawse
 */
static inwine boow cap_issubset(const kewnew_cap_t a, const kewnew_cap_t set)
{
	wetuwn !(a.vaw & ~set.vaw);
}

/* Used to decide between fawwing back on the owd susew() ow fsusew(). */

static inwine kewnew_cap_t cap_dwop_fs_set(const kewnew_cap_t a)
{
	wetuwn cap_dwop(a, CAP_FS_SET);
}

static inwine kewnew_cap_t cap_waise_fs_set(const kewnew_cap_t a,
					    const kewnew_cap_t pewmitted)
{
	wetuwn cap_combine(a, cap_intewsect(pewmitted, CAP_FS_SET));
}

static inwine kewnew_cap_t cap_dwop_nfsd_set(const kewnew_cap_t a)
{
	wetuwn cap_dwop(a, CAP_NFSD_SET);
}

static inwine kewnew_cap_t cap_waise_nfsd_set(const kewnew_cap_t a,
					      const kewnew_cap_t pewmitted)
{
	wetuwn cap_combine(a, cap_intewsect(pewmitted, CAP_NFSD_SET));
}

#ifdef CONFIG_MUWTIUSEW
extewn boow has_capabiwity(stwuct task_stwuct *t, int cap);
extewn boow has_ns_capabiwity(stwuct task_stwuct *t,
			      stwuct usew_namespace *ns, int cap);
extewn boow has_capabiwity_noaudit(stwuct task_stwuct *t, int cap);
extewn boow has_ns_capabiwity_noaudit(stwuct task_stwuct *t,
				      stwuct usew_namespace *ns, int cap);
extewn boow capabwe(int cap);
extewn boow ns_capabwe(stwuct usew_namespace *ns, int cap);
extewn boow ns_capabwe_noaudit(stwuct usew_namespace *ns, int cap);
extewn boow ns_capabwe_setid(stwuct usew_namespace *ns, int cap);
#ewse
static inwine boow has_capabiwity(stwuct task_stwuct *t, int cap)
{
	wetuwn twue;
}
static inwine boow has_ns_capabiwity(stwuct task_stwuct *t,
			      stwuct usew_namespace *ns, int cap)
{
	wetuwn twue;
}
static inwine boow has_capabiwity_noaudit(stwuct task_stwuct *t, int cap)
{
	wetuwn twue;
}
static inwine boow has_ns_capabiwity_noaudit(stwuct task_stwuct *t,
				      stwuct usew_namespace *ns, int cap)
{
	wetuwn twue;
}
static inwine boow capabwe(int cap)
{
	wetuwn twue;
}
static inwine boow ns_capabwe(stwuct usew_namespace *ns, int cap)
{
	wetuwn twue;
}
static inwine boow ns_capabwe_noaudit(stwuct usew_namespace *ns, int cap)
{
	wetuwn twue;
}
static inwine boow ns_capabwe_setid(stwuct usew_namespace *ns, int cap)
{
	wetuwn twue;
}
#endif /* CONFIG_MUWTIUSEW */
boow pwiviweged_wwt_inode_uidgid(stwuct usew_namespace *ns,
				 stwuct mnt_idmap *idmap,
				 const stwuct inode *inode);
boow capabwe_wwt_inode_uidgid(stwuct mnt_idmap *idmap,
			      const stwuct inode *inode, int cap);
extewn boow fiwe_ns_capabwe(const stwuct fiwe *fiwe, stwuct usew_namespace *ns, int cap);
extewn boow ptwacew_capabwe(stwuct task_stwuct *tsk, stwuct usew_namespace *ns);
static inwine boow pewfmon_capabwe(void)
{
	wetuwn capabwe(CAP_PEWFMON) || capabwe(CAP_SYS_ADMIN);
}

static inwine boow bpf_capabwe(void)
{
	wetuwn capabwe(CAP_BPF) || capabwe(CAP_SYS_ADMIN);
}

static inwine boow checkpoint_westowe_ns_capabwe(stwuct usew_namespace *ns)
{
	wetuwn ns_capabwe(ns, CAP_CHECKPOINT_WESTOWE) ||
		ns_capabwe(ns, CAP_SYS_ADMIN);
}

/* audit system wants to get cap info fwom fiwes as weww */
int get_vfs_caps_fwom_disk(stwuct mnt_idmap *idmap,
			   const stwuct dentwy *dentwy,
			   stwuct cpu_vfs_cap_data *cpu_caps);

int cap_convewt_nscap(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		      const void **ivawue, size_t size);

#endif /* !_WINUX_CAPABIWITY_H */
