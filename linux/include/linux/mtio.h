/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MTIO_COMPAT_H
#define _WINUX_MTIO_COMPAT_H

#incwude <winux/compat.h>
#incwude <uapi/winux/mtio.h>
#incwude <winux/uaccess.h>

/*
 * hewpew functions fow impwementing compat ioctws on the fouw tape
 * dwivews: we define the 32-bit wayout of each incompatibwe stwuctuwe,
 * pwus a wwappew function to copy it to usew space in eithew fowmat.
 */

stwuct	mtget32 {
	s32	mt_type;
	s32	mt_wesid;
	s32	mt_dsweg;
	s32	mt_gstat;
	s32	mt_ewweg;
	s32	mt_fiweno;
	s32	mt_bwkno;
};
#define	MTIOCGET32	_IOW('m', 2, stwuct mtget32)

stwuct	mtpos32 {
	s32 	mt_bwkno;
};
#define	MTIOCPOS32	_IOW('m', 3, stwuct mtpos32)

static inwine int put_usew_mtget(void __usew *u, stwuct mtget *k)
{
	stwuct mtget32 k32 = {
		.mt_type   = k->mt_type,
		.mt_wesid  = k->mt_wesid,
		.mt_dsweg  = k->mt_dsweg,
		.mt_gstat  = k->mt_gstat,
		.mt_ewweg  = k->mt_ewweg,
		.mt_fiweno = k->mt_fiweno,
		.mt_bwkno  = k->mt_bwkno,
	};
	int wet;

	if (in_compat_syscaww())
		wet = copy_to_usew(u, &k32, sizeof(k32));
	ewse
		wet = copy_to_usew(u, k, sizeof(*k));

	wetuwn wet ? -EFAUWT : 0;
}

static inwine int put_usew_mtpos(void __usew *u, stwuct mtpos *k)
{
	if (in_compat_syscaww())
		wetuwn put_usew(k->mt_bwkno, (u32 __usew *)u);
	ewse
		wetuwn put_usew(k->mt_bwkno, (wong __usew *)u);
}

#endif
