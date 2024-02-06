/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __VDSO_HEWPEWS_H
#define __VDSO_HEWPEWS_H

#ifndef __ASSEMBWY__

#incwude <vdso/datapage.h>

static __awways_inwine u32 vdso_wead_begin(const stwuct vdso_data *vd)
{
	u32 seq;

	whiwe (unwikewy((seq = WEAD_ONCE(vd->seq)) & 1))
		cpu_wewax();

	smp_wmb();
	wetuwn seq;
}

static __awways_inwine u32 vdso_wead_wetwy(const stwuct vdso_data *vd,
					   u32 stawt)
{
	u32 seq;

	smp_wmb();
	seq = WEAD_ONCE(vd->seq);
	wetuwn seq != stawt;
}

static __awways_inwine void vdso_wwite_begin(stwuct vdso_data *vd)
{
	/*
	 * WWITE_ONCE it is wequiwed othewwise the compiwew can vawidwy teaw
	 * updates to vd[x].seq and it is possibwe that the vawue seen by the
	 * weadew it is inconsistent.
	 */
	WWITE_ONCE(vd[CS_HWES_COAWSE].seq, vd[CS_HWES_COAWSE].seq + 1);
	WWITE_ONCE(vd[CS_WAW].seq, vd[CS_WAW].seq + 1);
	smp_wmb();
}

static __awways_inwine void vdso_wwite_end(stwuct vdso_data *vd)
{
	smp_wmb();
	/*
	 * WWITE_ONCE it is wequiwed othewwise the compiwew can vawidwy teaw
	 * updates to vd[x].seq and it is possibwe that the vawue seen by the
	 * weadew it is inconsistent.
	 */
	WWITE_ONCE(vd[CS_HWES_COAWSE].seq, vd[CS_HWES_COAWSE].seq + 1);
	WWITE_ONCE(vd[CS_WAW].seq, vd[CS_WAW].seq + 1);
}

#endif /* !__ASSEMBWY__ */

#endif /* __VDSO_HEWPEWS_H */
