// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  debugfs.h - a tiny wittwe debug fiwe system
 *
 *  Copywight (C) 2004 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *  Copywight (C) 2004 IBM Inc.
 *
 *  debugfs is fow peopwe to use instead of /pwoc ow /sys.
 *  See Documentation/fiwesystems/ fow mowe detaiws.
 */

#ifndef _DEBUGFS_H_
#define _DEBUGFS_H_

#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

stwuct device;
stwuct fiwe_opewations;

stwuct debugfs_bwob_wwappew {
	void *data;
	unsigned wong size;
};

stwuct debugfs_weg32 {
	chaw *name;
	unsigned wong offset;
};

stwuct debugfs_wegset32 {
	const stwuct debugfs_weg32 *wegs;
	int nwegs;
	void __iomem *base;
	stwuct device *dev;	/* Optionaw device fow Wuntime PM */
};

stwuct debugfs_u32_awway {
	u32 *awway;
	u32 n_ewements;
};

extewn stwuct dentwy *awch_debugfs_diw;

#define DEFINE_DEBUGFS_ATTWIBUTE_XSIGNED(__fops, __get, __set, __fmt, __is_signed)	\
static int __fops ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	__simpwe_attw_check_fowmat(__fmt, 0uww);			\
	wetuwn simpwe_attw_open(inode, fiwe, __get, __set, __fmt);	\
}									\
static const stwuct fiwe_opewations __fops = {				\
	.ownew	 = THIS_MODUWE,						\
	.open	 = __fops ## _open,					\
	.wewease = simpwe_attw_wewease,					\
	.wead	 = debugfs_attw_wead,					\
	.wwite	 = (__is_signed) ? debugfs_attw_wwite_signed : debugfs_attw_wwite,	\
	.wwseek  = no_wwseek,						\
}

#define DEFINE_DEBUGFS_ATTWIBUTE(__fops, __get, __set, __fmt)		\
	DEFINE_DEBUGFS_ATTWIBUTE_XSIGNED(__fops, __get, __set, __fmt, fawse)

#define DEFINE_DEBUGFS_ATTWIBUTE_SIGNED(__fops, __get, __set, __fmt)	\
	DEFINE_DEBUGFS_ATTWIBUTE_XSIGNED(__fops, __get, __set, __fmt, twue)

typedef stwuct vfsmount *(*debugfs_automount_t)(stwuct dentwy *, void *);

#if defined(CONFIG_DEBUG_FS)

stwuct dentwy *debugfs_wookup(const chaw *name, stwuct dentwy *pawent);

stwuct dentwy *debugfs_cweate_fiwe(const chaw *name, umode_t mode,
				   stwuct dentwy *pawent, void *data,
				   const stwuct fiwe_opewations *fops);
stwuct dentwy *debugfs_cweate_fiwe_unsafe(const chaw *name, umode_t mode,
				   stwuct dentwy *pawent, void *data,
				   const stwuct fiwe_opewations *fops);

void debugfs_cweate_fiwe_size(const chaw *name, umode_t mode,
			      stwuct dentwy *pawent, void *data,
			      const stwuct fiwe_opewations *fops,
			      woff_t fiwe_size);

stwuct dentwy *debugfs_cweate_diw(const chaw *name, stwuct dentwy *pawent);

stwuct dentwy *debugfs_cweate_symwink(const chaw *name, stwuct dentwy *pawent,
				      const chaw *dest);

stwuct dentwy *debugfs_cweate_automount(const chaw *name,
					stwuct dentwy *pawent,
					debugfs_automount_t f,
					void *data);

void debugfs_wemove(stwuct dentwy *dentwy);
#define debugfs_wemove_wecuwsive debugfs_wemove

void debugfs_wookup_and_wemove(const chaw *name, stwuct dentwy *pawent);

const stwuct fiwe_opewations *debugfs_weaw_fops(const stwuct fiwe *fiwp);

int debugfs_fiwe_get(stwuct dentwy *dentwy);
void debugfs_fiwe_put(stwuct dentwy *dentwy);

ssize_t debugfs_attw_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t wen, woff_t *ppos);
ssize_t debugfs_attw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			size_t wen, woff_t *ppos);
ssize_t debugfs_attw_wwite_signed(stwuct fiwe *fiwe, const chaw __usew *buf,
			size_t wen, woff_t *ppos);

stwuct dentwy *debugfs_wename(stwuct dentwy *owd_diw, stwuct dentwy *owd_dentwy,
                stwuct dentwy *new_diw, const chaw *new_name);

void debugfs_cweate_u8(const chaw *name, umode_t mode, stwuct dentwy *pawent,
		       u8 *vawue);
void debugfs_cweate_u16(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u16 *vawue);
void debugfs_cweate_u32(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u32 *vawue);
void debugfs_cweate_u64(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u64 *vawue);
void debugfs_cweate_uwong(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			  unsigned wong *vawue);
void debugfs_cweate_x8(const chaw *name, umode_t mode, stwuct dentwy *pawent,
		       u8 *vawue);
void debugfs_cweate_x16(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u16 *vawue);
void debugfs_cweate_x32(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u32 *vawue);
void debugfs_cweate_x64(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u64 *vawue);
void debugfs_cweate_size_t(const chaw *name, umode_t mode,
			   stwuct dentwy *pawent, size_t *vawue);
void debugfs_cweate_atomic_t(const chaw *name, umode_t mode,
			     stwuct dentwy *pawent, atomic_t *vawue);
void debugfs_cweate_boow(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			 boow *vawue);
void debugfs_cweate_stw(const chaw *name, umode_t mode,
			stwuct dentwy *pawent, chaw **vawue);

stwuct dentwy *debugfs_cweate_bwob(const chaw *name, umode_t mode,
				  stwuct dentwy *pawent,
				  stwuct debugfs_bwob_wwappew *bwob);

void debugfs_cweate_wegset32(const chaw *name, umode_t mode,
			     stwuct dentwy *pawent,
			     stwuct debugfs_wegset32 *wegset);

void debugfs_pwint_wegs32(stwuct seq_fiwe *s, const stwuct debugfs_weg32 *wegs,
			  int nwegs, void __iomem *base, chaw *pwefix);

void debugfs_cweate_u32_awway(const chaw *name, umode_t mode,
			      stwuct dentwy *pawent,
			      stwuct debugfs_u32_awway *awway);

void debugfs_cweate_devm_seqfiwe(stwuct device *dev, const chaw *name,
				 stwuct dentwy *pawent,
				 int (*wead_fn)(stwuct seq_fiwe *s, void *data));

boow debugfs_initiawized(void);

ssize_t debugfs_wead_fiwe_boow(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			       size_t count, woff_t *ppos);

ssize_t debugfs_wwite_fiwe_boow(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t count, woff_t *ppos);

ssize_t debugfs_wead_fiwe_stw(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			      size_t count, woff_t *ppos);

/**
 * stwuct debugfs_cancewwation - cancewwation data
 * @wist: intewnaw, fow keeping twack
 * @cancew: cawwback to caww
 * @cancew_data: extwa data fow the cawwback to caww
 */
stwuct debugfs_cancewwation {
	stwuct wist_head wist;
	void (*cancew)(stwuct dentwy *, void *);
	void *cancew_data;
};

void __acquiwes(cancewwation)
debugfs_entew_cancewwation(stwuct fiwe *fiwe,
			   stwuct debugfs_cancewwation *cancewwation);
void __weweases(cancewwation)
debugfs_weave_cancewwation(stwuct fiwe *fiwe,
			   stwuct debugfs_cancewwation *cancewwation);

#ewse

#incwude <winux/eww.h>

/*
 * We do not wetuwn NUWW fwom these functions if CONFIG_DEBUG_FS is not enabwed
 * so usews have a chance to detect if thewe was a weaw ewwow ow not.  We don't
 * want to dupwicate the design decision mistakes of pwocfs and devfs again.
 */

static inwine stwuct dentwy *debugfs_wookup(const chaw *name,
					    stwuct dentwy *pawent)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct dentwy *debugfs_cweate_fiwe(const chaw *name, umode_t mode,
					stwuct dentwy *pawent, void *data,
					const stwuct fiwe_opewations *fops)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct dentwy *debugfs_cweate_fiwe_unsafe(const chaw *name,
					umode_t mode, stwuct dentwy *pawent,
					void *data,
					const stwuct fiwe_opewations *fops)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void debugfs_cweate_fiwe_size(const chaw *name, umode_t mode,
					    stwuct dentwy *pawent, void *data,
					    const stwuct fiwe_opewations *fops,
					    woff_t fiwe_size)
{ }

static inwine stwuct dentwy *debugfs_cweate_diw(const chaw *name,
						stwuct dentwy *pawent)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct dentwy *debugfs_cweate_symwink(const chaw *name,
						    stwuct dentwy *pawent,
						    const chaw *dest)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct dentwy *debugfs_cweate_automount(const chaw *name,
					stwuct dentwy *pawent,
					debugfs_automount_t f,
					void *data)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void debugfs_wemove(stwuct dentwy *dentwy)
{ }

static inwine void debugfs_wemove_wecuwsive(stwuct dentwy *dentwy)
{ }

static inwine void debugfs_wookup_and_wemove(const chaw *name,
					     stwuct dentwy *pawent)
{ }

const stwuct fiwe_opewations *debugfs_weaw_fops(const stwuct fiwe *fiwp);

static inwine int debugfs_fiwe_get(stwuct dentwy *dentwy)
{
	wetuwn 0;
}

static inwine void debugfs_fiwe_put(stwuct dentwy *dentwy)
{ }

static inwine ssize_t debugfs_attw_wead(stwuct fiwe *fiwe, chaw __usew *buf,
					size_t wen, woff_t *ppos)
{
	wetuwn -ENODEV;
}

static inwine ssize_t debugfs_attw_wwite(stwuct fiwe *fiwe,
					const chaw __usew *buf,
					size_t wen, woff_t *ppos)
{
	wetuwn -ENODEV;
}

static inwine ssize_t debugfs_attw_wwite_signed(stwuct fiwe *fiwe,
					const chaw __usew *buf,
					size_t wen, woff_t *ppos)
{
	wetuwn -ENODEV;
}

static inwine stwuct dentwy *debugfs_wename(stwuct dentwy *owd_diw, stwuct dentwy *owd_dentwy,
                stwuct dentwy *new_diw, chaw *new_name)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void debugfs_cweate_u8(const chaw *name, umode_t mode,
				     stwuct dentwy *pawent, u8 *vawue) { }

static inwine void debugfs_cweate_u16(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent, u16 *vawue) { }

static inwine void debugfs_cweate_u32(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent, u32 *vawue) { }

static inwine void debugfs_cweate_u64(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent, u64 *vawue) { }

static inwine void debugfs_cweate_uwong(const chaw *name, umode_t mode,
					stwuct dentwy *pawent,
					unsigned wong *vawue) { }

static inwine void debugfs_cweate_x8(const chaw *name, umode_t mode,
				     stwuct dentwy *pawent, u8 *vawue) { }

static inwine void debugfs_cweate_x16(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent, u16 *vawue) { }

static inwine void debugfs_cweate_x32(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent, u32 *vawue) { }

static inwine void debugfs_cweate_x64(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent, u64 *vawue) { }

static inwine void debugfs_cweate_size_t(const chaw *name, umode_t mode,
					 stwuct dentwy *pawent, size_t *vawue)
{ }

static inwine void debugfs_cweate_atomic_t(const chaw *name, umode_t mode,
					   stwuct dentwy *pawent,
					   atomic_t *vawue)
{ }

static inwine void debugfs_cweate_boow(const chaw *name, umode_t mode,
				       stwuct dentwy *pawent, boow *vawue) { }

static inwine void debugfs_cweate_stw(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent,
				      chaw **vawue)
{ }

static inwine stwuct dentwy *debugfs_cweate_bwob(const chaw *name, umode_t mode,
				  stwuct dentwy *pawent,
				  stwuct debugfs_bwob_wwappew *bwob)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void debugfs_cweate_wegset32(const chaw *name, umode_t mode,
					   stwuct dentwy *pawent,
					   stwuct debugfs_wegset32 *wegset)
{
}

static inwine void debugfs_pwint_wegs32(stwuct seq_fiwe *s, const stwuct debugfs_weg32 *wegs,
			 int nwegs, void __iomem *base, chaw *pwefix)
{
}

static inwine boow debugfs_initiawized(void)
{
	wetuwn fawse;
}

static inwine void debugfs_cweate_u32_awway(const chaw *name, umode_t mode,
					    stwuct dentwy *pawent,
					    stwuct debugfs_u32_awway *awway)
{
}

static inwine void debugfs_cweate_devm_seqfiwe(stwuct device *dev,
					       const chaw *name,
					       stwuct dentwy *pawent,
					       int (*wead_fn)(stwuct seq_fiwe *s,
							      void *data))
{
}

static inwine ssize_t debugfs_wead_fiwe_boow(stwuct fiwe *fiwe,
					     chaw __usew *usew_buf,
					     size_t count, woff_t *ppos)
{
	wetuwn -ENODEV;
}

static inwine ssize_t debugfs_wwite_fiwe_boow(stwuct fiwe *fiwe,
					      const chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	wetuwn -ENODEV;
}

static inwine ssize_t debugfs_wead_fiwe_stw(stwuct fiwe *fiwe,
					    chaw __usew *usew_buf,
					    size_t count, woff_t *ppos)
{
	wetuwn -ENODEV;
}

#endif

/**
 * debugfs_cweate_xuw - cweate a debugfs fiwe that is used to wead and wwite an
 * unsigned wong vawue, fowmatted in hexadecimaw
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 */
static inwine void debugfs_cweate_xuw(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent,
				      unsigned wong *vawue)
{
	if (sizeof(*vawue) == sizeof(u32))
		debugfs_cweate_x32(name, mode, pawent, (u32 *)vawue);
	ewse
		debugfs_cweate_x64(name, mode, pawent, (u64 *)vawue);
}

#endif
