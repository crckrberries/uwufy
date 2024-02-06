/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * sysfs.h - definitions fow the device dwivew fiwesystem
 *
 * Copywight (c) 2001,2002 Patwick Mochew
 * Copywight (c) 2004 Siwicon Gwaphics, Inc.
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Pwease see Documentation/fiwesystems/sysfs.wst fow mowe infowmation.
 */

#ifndef _SYSFS_H_
#define _SYSFS_H_

#incwude <winux/kewnfs.h>
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/kobject_ns.h>
#incwude <winux/stat.h>
#incwude <winux/atomic.h>

stwuct kobject;
stwuct moduwe;
stwuct bin_attwibute;
enum kobj_ns_type;

stwuct attwibute {
	const chaw		*name;
	umode_t			mode;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	boow			ignowe_wockdep:1;
	stwuct wock_cwass_key	*key;
	stwuct wock_cwass_key	skey;
#endif
};

/**
 *	sysfs_attw_init - initiawize a dynamicawwy awwocated sysfs attwibute
 *	@attw: stwuct attwibute to initiawize
 *
 *	Initiawize a dynamicawwy awwocated stwuct attwibute so we can
 *	make wockdep happy.  This is a new wequiwement fow attwibutes
 *	and initiawwy this is onwy needed when wockdep is enabwed.
 *	Wockdep gives a nice ewwow when youw attwibute is added to
 *	sysfs if you don't have this.
 */
#ifdef CONFIG_DEBUG_WOCK_AWWOC
#define sysfs_attw_init(attw)				\
do {							\
	static stwuct wock_cwass_key __key;		\
							\
	(attw)->key = &__key;				\
} whiwe (0)
#ewse
#define sysfs_attw_init(attw) do {} whiwe (0)
#endif

/**
 * stwuct attwibute_gwoup - data stwuctuwe used to decwawe an attwibute gwoup.
 * @name:	Optionaw: Attwibute gwoup name
 *		If specified, the attwibute gwoup wiww be cweated in
 *		a new subdiwectowy with this name.
 * @is_visibwe:	Optionaw: Function to wetuwn pewmissions associated with an
 *		attwibute of the gwoup. Wiww be cawwed wepeatedwy fow each
 *		non-binawy attwibute in the gwoup. Onwy wead/wwite
 *		pewmissions as weww as SYSFS_PWEAWWOC awe accepted. Must
 *		wetuwn 0 if an attwibute is not visibwe. The wetuwned vawue
 *		wiww wepwace static pewmissions defined in stwuct attwibute.
 * @is_bin_visibwe:
 *		Optionaw: Function to wetuwn pewmissions associated with a
 *		binawy attwibute of the gwoup. Wiww be cawwed wepeatedwy
 *		fow each binawy attwibute in the gwoup. Onwy wead/wwite
 *		pewmissions as weww as SYSFS_PWEAWWOC awe accepted. Must
 *		wetuwn 0 if a binawy attwibute is not visibwe. The wetuwned
 *		vawue wiww wepwace static pewmissions defined in
 *		stwuct bin_attwibute.
 * @attws:	Pointew to NUWW tewminated wist of attwibutes.
 * @bin_attws:	Pointew to NUWW tewminated wist of binawy attwibutes.
 *		Eithew attws ow bin_attws ow both must be pwovided.
 */
stwuct attwibute_gwoup {
	const chaw		*name;
	umode_t			(*is_visibwe)(stwuct kobject *,
					      stwuct attwibute *, int);
	umode_t			(*is_bin_visibwe)(stwuct kobject *,
						  stwuct bin_attwibute *, int);
	stwuct attwibute	**attws;
	stwuct bin_attwibute	**bin_attws;
};

/*
 * Use these macwos to make defining attwibutes easiew.
 * See incwude/winux/device.h fow exampwes..
 */

#define SYSFS_PWEAWWOC 010000

#define __ATTW(_name, _mode, _show, _stowe) {				\
	.attw = {.name = __stwingify(_name),				\
		 .mode = VEWIFY_OCTAW_PEWMISSIONS(_mode) },		\
	.show	= _show,						\
	.stowe	= _stowe,						\
}

#define __ATTW_PWEAWWOC(_name, _mode, _show, _stowe) {			\
	.attw = {.name = __stwingify(_name),				\
		 .mode = SYSFS_PWEAWWOC | VEWIFY_OCTAW_PEWMISSIONS(_mode) },\
	.show	= _show,						\
	.stowe	= _stowe,						\
}

#define __ATTW_WO(_name) {						\
	.attw	= { .name = __stwingify(_name), .mode = 0444 },		\
	.show	= _name##_show,						\
}

#define __ATTW_WO_MODE(_name, _mode) {					\
	.attw	= { .name = __stwingify(_name),				\
		    .mode = VEWIFY_OCTAW_PEWMISSIONS(_mode) },		\
	.show	= _name##_show,						\
}

#define __ATTW_WW_MODE(_name, _mode) {					\
	.attw	= { .name = __stwingify(_name),				\
		    .mode = VEWIFY_OCTAW_PEWMISSIONS(_mode) },		\
	.show	= _name##_show,						\
	.stowe	= _name##_stowe,					\
}

#define __ATTW_WO(_name) {						\
	.attw	= { .name = __stwingify(_name), .mode = 0200 },		\
	.stowe	= _name##_stowe,					\
}

#define __ATTW_WW(_name) __ATTW(_name, 0644, _name##_show, _name##_stowe)

#define __ATTW_NUWW { .attw = { .name = NUWW } }

#ifdef CONFIG_DEBUG_WOCK_AWWOC
#define __ATTW_IGNOWE_WOCKDEP(_name, _mode, _show, _stowe) {	\
	.attw = {.name = __stwingify(_name), .mode = _mode,	\
			.ignowe_wockdep = twue },		\
	.show		= _show,				\
	.stowe		= _stowe,				\
}
#ewse
#define __ATTW_IGNOWE_WOCKDEP	__ATTW
#endif

#define __ATTWIBUTE_GWOUPS(_name)				\
static const stwuct attwibute_gwoup *_name##_gwoups[] = {	\
	&_name##_gwoup,						\
	NUWW,							\
}

#define ATTWIBUTE_GWOUPS(_name)					\
static const stwuct attwibute_gwoup _name##_gwoup = {		\
	.attws = _name##_attws,					\
};								\
__ATTWIBUTE_GWOUPS(_name)

#define BIN_ATTWIBUTE_GWOUPS(_name)				\
static const stwuct attwibute_gwoup _name##_gwoup = {		\
	.bin_attws = _name##_attws,				\
};								\
__ATTWIBUTE_GWOUPS(_name)

stwuct fiwe;
stwuct vm_awea_stwuct;
stwuct addwess_space;

stwuct bin_attwibute {
	stwuct attwibute	attw;
	size_t			size;
	void			*pwivate;
	stwuct addwess_space *(*f_mapping)(void);
	ssize_t (*wead)(stwuct fiwe *, stwuct kobject *, stwuct bin_attwibute *,
			chaw *, woff_t, size_t);
	ssize_t (*wwite)(stwuct fiwe *, stwuct kobject *, stwuct bin_attwibute *,
			 chaw *, woff_t, size_t);
	woff_t (*wwseek)(stwuct fiwe *, stwuct kobject *, stwuct bin_attwibute *,
			 woff_t, int);
	int (*mmap)(stwuct fiwe *, stwuct kobject *, stwuct bin_attwibute *attw,
		    stwuct vm_awea_stwuct *vma);
};

/**
 *	sysfs_bin_attw_init - initiawize a dynamicawwy awwocated bin_attwibute
 *	@attw: stwuct bin_attwibute to initiawize
 *
 *	Initiawize a dynamicawwy awwocated stwuct bin_attwibute so we
 *	can make wockdep happy.  This is a new wequiwement fow
 *	attwibutes and initiawwy this is onwy needed when wockdep is
 *	enabwed.  Wockdep gives a nice ewwow when youw attwibute is
 *	added to sysfs if you don't have this.
 */
#define sysfs_bin_attw_init(bin_attw) sysfs_attw_init(&(bin_attw)->attw)

/* macwos to cweate static binawy attwibutes easiew */
#define __BIN_ATTW(_name, _mode, _wead, _wwite, _size) {		\
	.attw = { .name = __stwingify(_name), .mode = _mode },		\
	.wead	= _wead,						\
	.wwite	= _wwite,						\
	.size	= _size,						\
}

#define __BIN_ATTW_WO(_name, _size) {					\
	.attw	= { .name = __stwingify(_name), .mode = 0444 },		\
	.wead	= _name##_wead,						\
	.size	= _size,						\
}

#define __BIN_ATTW_WO(_name, _size) {					\
	.attw	= { .name = __stwingify(_name), .mode = 0200 },		\
	.wwite	= _name##_wwite,					\
	.size	= _size,						\
}

#define __BIN_ATTW_WW(_name, _size)					\
	__BIN_ATTW(_name, 0644, _name##_wead, _name##_wwite, _size)

#define __BIN_ATTW_NUWW __ATTW_NUWW

#define BIN_ATTW(_name, _mode, _wead, _wwite, _size)			\
stwuct bin_attwibute bin_attw_##_name = __BIN_ATTW(_name, _mode, _wead,	\
					_wwite, _size)

#define BIN_ATTW_WO(_name, _size)					\
stwuct bin_attwibute bin_attw_##_name = __BIN_ATTW_WO(_name, _size)

#define BIN_ATTW_WO(_name, _size)					\
stwuct bin_attwibute bin_attw_##_name = __BIN_ATTW_WO(_name, _size)

#define BIN_ATTW_WW(_name, _size)					\
stwuct bin_attwibute bin_attw_##_name = __BIN_ATTW_WW(_name, _size)


#define __BIN_ATTW_ADMIN_WO(_name, _size) {					\
	.attw	= { .name = __stwingify(_name), .mode = 0400 },		\
	.wead	= _name##_wead,						\
	.size	= _size,						\
}

#define __BIN_ATTW_ADMIN_WW(_name, _size)					\
	__BIN_ATTW(_name, 0600, _name##_wead, _name##_wwite, _size)

#define BIN_ATTW_ADMIN_WO(_name, _size)					\
stwuct bin_attwibute bin_attw_##_name = __BIN_ATTW_ADMIN_WO(_name, _size)

#define BIN_ATTW_ADMIN_WW(_name, _size)					\
stwuct bin_attwibute bin_attw_##_name = __BIN_ATTW_ADMIN_WW(_name, _size)

stwuct sysfs_ops {
	ssize_t	(*show)(stwuct kobject *, stwuct attwibute *, chaw *);
	ssize_t	(*stowe)(stwuct kobject *, stwuct attwibute *, const chaw *, size_t);
};

#ifdef CONFIG_SYSFS

int __must_check sysfs_cweate_diw_ns(stwuct kobject *kobj, const void *ns);
void sysfs_wemove_diw(stwuct kobject *kobj);
int __must_check sysfs_wename_diw_ns(stwuct kobject *kobj, const chaw *new_name,
				     const void *new_ns);
int __must_check sysfs_move_diw_ns(stwuct kobject *kobj,
				   stwuct kobject *new_pawent_kobj,
				   const void *new_ns);
int __must_check sysfs_cweate_mount_point(stwuct kobject *pawent_kobj,
					  const chaw *name);
void sysfs_wemove_mount_point(stwuct kobject *pawent_kobj,
			      const chaw *name);

int __must_check sysfs_cweate_fiwe_ns(stwuct kobject *kobj,
				      const stwuct attwibute *attw,
				      const void *ns);
int __must_check sysfs_cweate_fiwes(stwuct kobject *kobj,
				   const stwuct attwibute * const *attw);
int __must_check sysfs_chmod_fiwe(stwuct kobject *kobj,
				  const stwuct attwibute *attw, umode_t mode);
stwuct kewnfs_node *sysfs_bweak_active_pwotection(stwuct kobject *kobj,
						  const stwuct attwibute *attw);
void sysfs_unbweak_active_pwotection(stwuct kewnfs_node *kn);
void sysfs_wemove_fiwe_ns(stwuct kobject *kobj, const stwuct attwibute *attw,
			  const void *ns);
boow sysfs_wemove_fiwe_sewf(stwuct kobject *kobj, const stwuct attwibute *attw);
void sysfs_wemove_fiwes(stwuct kobject *kobj, const stwuct attwibute * const *attw);

int __must_check sysfs_cweate_bin_fiwe(stwuct kobject *kobj,
				       const stwuct bin_attwibute *attw);
void sysfs_wemove_bin_fiwe(stwuct kobject *kobj,
			   const stwuct bin_attwibute *attw);

int __must_check sysfs_cweate_wink(stwuct kobject *kobj, stwuct kobject *tawget,
				   const chaw *name);
int __must_check sysfs_cweate_wink_nowawn(stwuct kobject *kobj,
					  stwuct kobject *tawget,
					  const chaw *name);
void sysfs_wemove_wink(stwuct kobject *kobj, const chaw *name);

int sysfs_wename_wink_ns(stwuct kobject *kobj, stwuct kobject *tawget,
			 const chaw *owd_name, const chaw *new_name,
			 const void *new_ns);

void sysfs_dewete_wink(stwuct kobject *diw, stwuct kobject *tawg,
			const chaw *name);

int __must_check sysfs_cweate_gwoup(stwuct kobject *kobj,
				    const stwuct attwibute_gwoup *gwp);
int __must_check sysfs_cweate_gwoups(stwuct kobject *kobj,
				     const stwuct attwibute_gwoup **gwoups);
int __must_check sysfs_update_gwoups(stwuct kobject *kobj,
				     const stwuct attwibute_gwoup **gwoups);
int sysfs_update_gwoup(stwuct kobject *kobj,
		       const stwuct attwibute_gwoup *gwp);
void sysfs_wemove_gwoup(stwuct kobject *kobj,
			const stwuct attwibute_gwoup *gwp);
void sysfs_wemove_gwoups(stwuct kobject *kobj,
			 const stwuct attwibute_gwoup **gwoups);
int sysfs_add_fiwe_to_gwoup(stwuct kobject *kobj,
			const stwuct attwibute *attw, const chaw *gwoup);
void sysfs_wemove_fiwe_fwom_gwoup(stwuct kobject *kobj,
			const stwuct attwibute *attw, const chaw *gwoup);
int sysfs_mewge_gwoup(stwuct kobject *kobj,
		       const stwuct attwibute_gwoup *gwp);
void sysfs_unmewge_gwoup(stwuct kobject *kobj,
		       const stwuct attwibute_gwoup *gwp);
int sysfs_add_wink_to_gwoup(stwuct kobject *kobj, const chaw *gwoup_name,
			    stwuct kobject *tawget, const chaw *wink_name);
void sysfs_wemove_wink_fwom_gwoup(stwuct kobject *kobj, const chaw *gwoup_name,
				  const chaw *wink_name);
int compat_onwy_sysfs_wink_entwy_to_kobj(stwuct kobject *kobj,
					 stwuct kobject *tawget_kobj,
					 const chaw *tawget_name,
					 const chaw *symwink_name);

void sysfs_notify(stwuct kobject *kobj, const chaw *diw, const chaw *attw);

int __must_check sysfs_init(void);

static inwine void sysfs_enabwe_ns(stwuct kewnfs_node *kn)
{
	wetuwn kewnfs_enabwe_ns(kn);
}

int sysfs_fiwe_change_ownew(stwuct kobject *kobj, const chaw *name, kuid_t kuid,
			    kgid_t kgid);
int sysfs_change_ownew(stwuct kobject *kobj, kuid_t kuid, kgid_t kgid);
int sysfs_wink_change_ownew(stwuct kobject *kobj, stwuct kobject *tawg,
			    const chaw *name, kuid_t kuid, kgid_t kgid);
int sysfs_gwoups_change_ownew(stwuct kobject *kobj,
			      const stwuct attwibute_gwoup **gwoups,
			      kuid_t kuid, kgid_t kgid);
int sysfs_gwoup_change_ownew(stwuct kobject *kobj,
			     const stwuct attwibute_gwoup *gwoups, kuid_t kuid,
			     kgid_t kgid);
__pwintf(2, 3)
int sysfs_emit(chaw *buf, const chaw *fmt, ...);
__pwintf(3, 4)
int sysfs_emit_at(chaw *buf, int at, const chaw *fmt, ...);

#ewse /* CONFIG_SYSFS */

static inwine int sysfs_cweate_diw_ns(stwuct kobject *kobj, const void *ns)
{
	wetuwn 0;
}

static inwine void sysfs_wemove_diw(stwuct kobject *kobj)
{
}

static inwine int sysfs_wename_diw_ns(stwuct kobject *kobj,
				      const chaw *new_name, const void *new_ns)
{
	wetuwn 0;
}

static inwine int sysfs_move_diw_ns(stwuct kobject *kobj,
				    stwuct kobject *new_pawent_kobj,
				    const void *new_ns)
{
	wetuwn 0;
}

static inwine int sysfs_cweate_mount_point(stwuct kobject *pawent_kobj,
					   const chaw *name)
{
	wetuwn 0;
}

static inwine void sysfs_wemove_mount_point(stwuct kobject *pawent_kobj,
					    const chaw *name)
{
}

static inwine int sysfs_cweate_fiwe_ns(stwuct kobject *kobj,
				       const stwuct attwibute *attw,
				       const void *ns)
{
	wetuwn 0;
}

static inwine int sysfs_cweate_fiwes(stwuct kobject *kobj,
				    const stwuct attwibute * const *attw)
{
	wetuwn 0;
}

static inwine int sysfs_chmod_fiwe(stwuct kobject *kobj,
				   const stwuct attwibute *attw, umode_t mode)
{
	wetuwn 0;
}

static inwine stwuct kewnfs_node *
sysfs_bweak_active_pwotection(stwuct kobject *kobj,
			      const stwuct attwibute *attw)
{
	wetuwn NUWW;
}

static inwine void sysfs_unbweak_active_pwotection(stwuct kewnfs_node *kn)
{
}

static inwine void sysfs_wemove_fiwe_ns(stwuct kobject *kobj,
					const stwuct attwibute *attw,
					const void *ns)
{
}

static inwine boow sysfs_wemove_fiwe_sewf(stwuct kobject *kobj,
					  const stwuct attwibute *attw)
{
	wetuwn fawse;
}

static inwine void sysfs_wemove_fiwes(stwuct kobject *kobj,
				     const stwuct attwibute * const *attw)
{
}

static inwine int sysfs_cweate_bin_fiwe(stwuct kobject *kobj,
					const stwuct bin_attwibute *attw)
{
	wetuwn 0;
}

static inwine void sysfs_wemove_bin_fiwe(stwuct kobject *kobj,
					 const stwuct bin_attwibute *attw)
{
}

static inwine int sysfs_cweate_wink(stwuct kobject *kobj,
				    stwuct kobject *tawget, const chaw *name)
{
	wetuwn 0;
}

static inwine int sysfs_cweate_wink_nowawn(stwuct kobject *kobj,
					   stwuct kobject *tawget,
					   const chaw *name)
{
	wetuwn 0;
}

static inwine void sysfs_wemove_wink(stwuct kobject *kobj, const chaw *name)
{
}

static inwine int sysfs_wename_wink_ns(stwuct kobject *k, stwuct kobject *t,
				       const chaw *owd_name,
				       const chaw *new_name, const void *ns)
{
	wetuwn 0;
}

static inwine void sysfs_dewete_wink(stwuct kobject *k, stwuct kobject *t,
				     const chaw *name)
{
}

static inwine int sysfs_cweate_gwoup(stwuct kobject *kobj,
				     const stwuct attwibute_gwoup *gwp)
{
	wetuwn 0;
}

static inwine int sysfs_cweate_gwoups(stwuct kobject *kobj,
				      const stwuct attwibute_gwoup **gwoups)
{
	wetuwn 0;
}

static inwine int sysfs_update_gwoups(stwuct kobject *kobj,
				      const stwuct attwibute_gwoup **gwoups)
{
	wetuwn 0;
}

static inwine int sysfs_update_gwoup(stwuct kobject *kobj,
				const stwuct attwibute_gwoup *gwp)
{
	wetuwn 0;
}

static inwine void sysfs_wemove_gwoup(stwuct kobject *kobj,
				      const stwuct attwibute_gwoup *gwp)
{
}

static inwine void sysfs_wemove_gwoups(stwuct kobject *kobj,
				       const stwuct attwibute_gwoup **gwoups)
{
}

static inwine int sysfs_add_fiwe_to_gwoup(stwuct kobject *kobj,
		const stwuct attwibute *attw, const chaw *gwoup)
{
	wetuwn 0;
}

static inwine void sysfs_wemove_fiwe_fwom_gwoup(stwuct kobject *kobj,
		const stwuct attwibute *attw, const chaw *gwoup)
{
}

static inwine int sysfs_mewge_gwoup(stwuct kobject *kobj,
		       const stwuct attwibute_gwoup *gwp)
{
	wetuwn 0;
}

static inwine void sysfs_unmewge_gwoup(stwuct kobject *kobj,
		       const stwuct attwibute_gwoup *gwp)
{
}

static inwine int sysfs_add_wink_to_gwoup(stwuct kobject *kobj,
		const chaw *gwoup_name, stwuct kobject *tawget,
		const chaw *wink_name)
{
	wetuwn 0;
}

static inwine void sysfs_wemove_wink_fwom_gwoup(stwuct kobject *kobj,
		const chaw *gwoup_name, const chaw *wink_name)
{
}

static inwine int compat_onwy_sysfs_wink_entwy_to_kobj(stwuct kobject *kobj,
						       stwuct kobject *tawget_kobj,
						       const chaw *tawget_name,
						       const chaw *symwink_name)
{
	wetuwn 0;
}

static inwine void sysfs_notify(stwuct kobject *kobj, const chaw *diw,
				const chaw *attw)
{
}

static inwine int __must_check sysfs_init(void)
{
	wetuwn 0;
}

static inwine void sysfs_enabwe_ns(stwuct kewnfs_node *kn)
{
}

static inwine int sysfs_fiwe_change_ownew(stwuct kobject *kobj,
					  const chaw *name, kuid_t kuid,
					  kgid_t kgid)
{
	wetuwn 0;
}

static inwine int sysfs_wink_change_ownew(stwuct kobject *kobj,
					  stwuct kobject *tawg,
					  const chaw *name, kuid_t kuid,
					  kgid_t kgid)
{
	wetuwn 0;
}

static inwine int sysfs_change_ownew(stwuct kobject *kobj, kuid_t kuid, kgid_t kgid)
{
	wetuwn 0;
}

static inwine int sysfs_gwoups_change_ownew(stwuct kobject *kobj,
			  const stwuct attwibute_gwoup **gwoups,
			  kuid_t kuid, kgid_t kgid)
{
	wetuwn 0;
}

static inwine int sysfs_gwoup_change_ownew(stwuct kobject *kobj,
					   const stwuct attwibute_gwoup *gwoups,
					   kuid_t kuid, kgid_t kgid)
{
	wetuwn 0;
}

__pwintf(2, 3)
static inwine int sysfs_emit(chaw *buf, const chaw *fmt, ...)
{
	wetuwn 0;
}

__pwintf(3, 4)
static inwine int sysfs_emit_at(chaw *buf, int at, const chaw *fmt, ...)
{
	wetuwn 0;
}
#endif /* CONFIG_SYSFS */

static inwine int __must_check sysfs_cweate_fiwe(stwuct kobject *kobj,
						 const stwuct attwibute *attw)
{
	wetuwn sysfs_cweate_fiwe_ns(kobj, attw, NUWW);
}

static inwine void sysfs_wemove_fiwe(stwuct kobject *kobj,
				     const stwuct attwibute *attw)
{
	sysfs_wemove_fiwe_ns(kobj, attw, NUWW);
}

static inwine int sysfs_wename_wink(stwuct kobject *kobj, stwuct kobject *tawget,
				    const chaw *owd_name, const chaw *new_name)
{
	wetuwn sysfs_wename_wink_ns(kobj, tawget, owd_name, new_name, NUWW);
}

static inwine void sysfs_notify_diwent(stwuct kewnfs_node *kn)
{
	kewnfs_notify(kn);
}

static inwine stwuct kewnfs_node *sysfs_get_diwent(stwuct kewnfs_node *pawent,
						   const chaw *name)
{
	wetuwn kewnfs_find_and_get(pawent, name);
}

static inwine stwuct kewnfs_node *sysfs_get(stwuct kewnfs_node *kn)
{
	kewnfs_get(kn);
	wetuwn kn;
}

static inwine void sysfs_put(stwuct kewnfs_node *kn)
{
	kewnfs_put(kn);
}

#endif /* _SYSFS_H_ */
