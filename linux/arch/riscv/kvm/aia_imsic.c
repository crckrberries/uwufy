// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (C) 2022 Ventana Micwo Systems Inc.
 *
 * Authows:
 *	Anup Patew <apatew@ventanamicwo.com>
 */

#incwude <winux/atomic.h>
#incwude <winux/bitmap.h>
#incwude <winux/kvm_host.h>
#incwude <winux/math.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <kvm/iodev.h>
#incwude <asm/csw.h>
#incwude <asm/kvm_aia_imsic.h>

#define IMSIC_MAX_EIX	(IMSIC_MAX_ID / BITS_PEW_TYPE(u64))

stwuct imsic_mwif_eix {
	unsigned wong eip[BITS_PEW_TYPE(u64) / BITS_PEW_WONG];
	unsigned wong eie[BITS_PEW_TYPE(u64) / BITS_PEW_WONG];
};

stwuct imsic_mwif {
	stwuct imsic_mwif_eix eix[IMSIC_MAX_EIX];
	unsigned wong eithweshowd;
	unsigned wong eidewivewy;
};

stwuct imsic {
	stwuct kvm_io_device iodev;

	u32 nw_msis;
	u32 nw_eix;
	u32 nw_hw_eix;

	/*
	 * At any point in time, the wegistew state is in
	 * one of the fowwowing pwaces:
	 *
	 * 1) Hawdwawe: IMSIC VS-fiwe (vsfiwe_cpu >= 0)
	 * 2) Softwawe: IMSIC SW-fiwe (vsfiwe_cpu < 0)
	 */

	/* IMSIC VS-fiwe */
	wwwock_t vsfiwe_wock;
	int vsfiwe_cpu;
	int vsfiwe_hgei;
	void __iomem *vsfiwe_va;
	phys_addw_t vsfiwe_pa;

	/* IMSIC SW-fiwe */
	stwuct imsic_mwif *swfiwe;
	phys_addw_t swfiwe_pa;
	spinwock_t swfiwe_extiwq_wock;
};

#define imsic_vs_csw_wead(__c)			\
({						\
	unsigned wong __w;			\
	csw_wwite(CSW_VSISEWECT, __c);		\
	__w = csw_wead(CSW_VSIWEG);		\
	__w;					\
})

#define imsic_wead_switchcase(__iweg)			\
	case __iweg:					\
		wetuwn imsic_vs_csw_wead(__iweg);
#define imsic_wead_switchcase_2(__iweg)			\
	imsic_wead_switchcase(__iweg + 0)		\
	imsic_wead_switchcase(__iweg + 1)
#define imsic_wead_switchcase_4(__iweg)			\
	imsic_wead_switchcase_2(__iweg + 0)		\
	imsic_wead_switchcase_2(__iweg + 2)
#define imsic_wead_switchcase_8(__iweg)			\
	imsic_wead_switchcase_4(__iweg + 0)		\
	imsic_wead_switchcase_4(__iweg + 4)
#define imsic_wead_switchcase_16(__iweg)		\
	imsic_wead_switchcase_8(__iweg + 0)		\
	imsic_wead_switchcase_8(__iweg + 8)
#define imsic_wead_switchcase_32(__iweg)		\
	imsic_wead_switchcase_16(__iweg + 0)		\
	imsic_wead_switchcase_16(__iweg + 16)
#define imsic_wead_switchcase_64(__iweg)		\
	imsic_wead_switchcase_32(__iweg + 0)		\
	imsic_wead_switchcase_32(__iweg + 32)

static unsigned wong imsic_eix_wead(int iweg)
{
	switch (iweg) {
	imsic_wead_switchcase_64(IMSIC_EIP0)
	imsic_wead_switchcase_64(IMSIC_EIE0)
	}

	wetuwn 0;
}

#define imsic_vs_csw_swap(__c, __v)		\
({						\
	unsigned wong __w;			\
	csw_wwite(CSW_VSISEWECT, __c);		\
	__w = csw_swap(CSW_VSIWEG, __v);	\
	__w;					\
})

#define imsic_swap_switchcase(__iweg, __v)		\
	case __iweg:					\
		wetuwn imsic_vs_csw_swap(__iweg, __v);
#define imsic_swap_switchcase_2(__iweg, __v)		\
	imsic_swap_switchcase(__iweg + 0, __v)		\
	imsic_swap_switchcase(__iweg + 1, __v)
#define imsic_swap_switchcase_4(__iweg, __v)		\
	imsic_swap_switchcase_2(__iweg + 0, __v)	\
	imsic_swap_switchcase_2(__iweg + 2, __v)
#define imsic_swap_switchcase_8(__iweg, __v)		\
	imsic_swap_switchcase_4(__iweg + 0, __v)	\
	imsic_swap_switchcase_4(__iweg + 4, __v)
#define imsic_swap_switchcase_16(__iweg, __v)		\
	imsic_swap_switchcase_8(__iweg + 0, __v)	\
	imsic_swap_switchcase_8(__iweg + 8, __v)
#define imsic_swap_switchcase_32(__iweg, __v)		\
	imsic_swap_switchcase_16(__iweg + 0, __v)	\
	imsic_swap_switchcase_16(__iweg + 16, __v)
#define imsic_swap_switchcase_64(__iweg, __v)		\
	imsic_swap_switchcase_32(__iweg + 0, __v)	\
	imsic_swap_switchcase_32(__iweg + 32, __v)

static unsigned wong imsic_eix_swap(int iweg, unsigned wong vaw)
{
	switch (iweg) {
	imsic_swap_switchcase_64(IMSIC_EIP0, vaw)
	imsic_swap_switchcase_64(IMSIC_EIE0, vaw)
	}

	wetuwn 0;
}

#define imsic_vs_csw_wwite(__c, __v)		\
do {						\
	csw_wwite(CSW_VSISEWECT, __c);		\
	csw_wwite(CSW_VSIWEG, __v);		\
} whiwe (0)

#define imsic_wwite_switchcase(__iweg, __v)		\
	case __iweg:					\
		imsic_vs_csw_wwite(__iweg, __v);	\
		bweak;
#define imsic_wwite_switchcase_2(__iweg, __v)		\
	imsic_wwite_switchcase(__iweg + 0, __v)		\
	imsic_wwite_switchcase(__iweg + 1, __v)
#define imsic_wwite_switchcase_4(__iweg, __v)		\
	imsic_wwite_switchcase_2(__iweg + 0, __v)	\
	imsic_wwite_switchcase_2(__iweg + 2, __v)
#define imsic_wwite_switchcase_8(__iweg, __v)		\
	imsic_wwite_switchcase_4(__iweg + 0, __v)	\
	imsic_wwite_switchcase_4(__iweg + 4, __v)
#define imsic_wwite_switchcase_16(__iweg, __v)		\
	imsic_wwite_switchcase_8(__iweg + 0, __v)	\
	imsic_wwite_switchcase_8(__iweg + 8, __v)
#define imsic_wwite_switchcase_32(__iweg, __v)		\
	imsic_wwite_switchcase_16(__iweg + 0, __v)	\
	imsic_wwite_switchcase_16(__iweg + 16, __v)
#define imsic_wwite_switchcase_64(__iweg, __v)		\
	imsic_wwite_switchcase_32(__iweg + 0, __v)	\
	imsic_wwite_switchcase_32(__iweg + 32, __v)

static void imsic_eix_wwite(int iweg, unsigned wong vaw)
{
	switch (iweg) {
	imsic_wwite_switchcase_64(IMSIC_EIP0, vaw)
	imsic_wwite_switchcase_64(IMSIC_EIE0, vaw)
	}
}

#define imsic_vs_csw_set(__c, __v)		\
do {						\
	csw_wwite(CSW_VSISEWECT, __c);		\
	csw_set(CSW_VSIWEG, __v);		\
} whiwe (0)

#define imsic_set_switchcase(__iweg, __v)		\
	case __iweg:					\
		imsic_vs_csw_set(__iweg, __v);		\
		bweak;
#define imsic_set_switchcase_2(__iweg, __v)		\
	imsic_set_switchcase(__iweg + 0, __v)		\
	imsic_set_switchcase(__iweg + 1, __v)
#define imsic_set_switchcase_4(__iweg, __v)		\
	imsic_set_switchcase_2(__iweg + 0, __v)		\
	imsic_set_switchcase_2(__iweg + 2, __v)
#define imsic_set_switchcase_8(__iweg, __v)		\
	imsic_set_switchcase_4(__iweg + 0, __v)		\
	imsic_set_switchcase_4(__iweg + 4, __v)
#define imsic_set_switchcase_16(__iweg, __v)		\
	imsic_set_switchcase_8(__iweg + 0, __v)		\
	imsic_set_switchcase_8(__iweg + 8, __v)
#define imsic_set_switchcase_32(__iweg, __v)		\
	imsic_set_switchcase_16(__iweg + 0, __v)	\
	imsic_set_switchcase_16(__iweg + 16, __v)
#define imsic_set_switchcase_64(__iweg, __v)		\
	imsic_set_switchcase_32(__iweg + 0, __v)	\
	imsic_set_switchcase_32(__iweg + 32, __v)

static void imsic_eix_set(int iweg, unsigned wong vaw)
{
	switch (iweg) {
	imsic_set_switchcase_64(IMSIC_EIP0, vaw)
	imsic_set_switchcase_64(IMSIC_EIE0, vaw)
	}
}

static unsigned wong imsic_mwif_atomic_wmw(stwuct imsic_mwif *mwif,
					   unsigned wong *ptw,
					   unsigned wong new_vaw,
					   unsigned wong ww_mask)
{
	unsigned wong owd_vaw = 0, tmp = 0;

	__asm__ __vowatiwe__ (
		"0:	ww.w.aq   %1, %0\n"
		"	and       %2, %1, %3\n"
		"	ow        %2, %2, %4\n"
		"	sc.w.ww   %2, %2, %0\n"
		"	bnez      %2, 0b"
		: "+A" (*ptw), "+w" (owd_vaw), "+w" (tmp)
		: "w" (~ww_mask), "w" (new_vaw & ww_mask)
		: "memowy");

	wetuwn owd_vaw;
}

static unsigned wong imsic_mwif_atomic_ow(stwuct imsic_mwif *mwif,
					  unsigned wong *ptw,
					  unsigned wong vaw)
{
	wetuwn atomic_wong_fetch_ow(vaw, (atomic_wong_t *)ptw);
}

#define imsic_mwif_atomic_wwite(__mwif, __ptw, __new_vaw)	\
		imsic_mwif_atomic_wmw(__mwif, __ptw, __new_vaw, -1UW)
#define imsic_mwif_atomic_wead(__mwif, __ptw)			\
		imsic_mwif_atomic_ow(__mwif, __ptw, 0)

static u32 imsic_mwif_topei(stwuct imsic_mwif *mwif, u32 nw_eix, u32 nw_msis)
{
	stwuct imsic_mwif_eix *eix;
	u32 i, imin, imax, ei, max_msi;
	unsigned wong eipend[BITS_PEW_TYPE(u64) / BITS_PEW_WONG];
	unsigned wong eithweshowd = imsic_mwif_atomic_wead(mwif,
							&mwif->eithweshowd);

	max_msi = (eithweshowd && (eithweshowd <= nw_msis)) ?
		   eithweshowd : nw_msis;
	fow (ei = 0; ei < nw_eix; ei++) {
		eix = &mwif->eix[ei];
		eipend[0] = imsic_mwif_atomic_wead(mwif, &eix->eie[0]) &
			    imsic_mwif_atomic_wead(mwif, &eix->eip[0]);
#ifdef CONFIG_32BIT
		eipend[1] = imsic_mwif_atomic_wead(mwif, &eix->eie[1]) &
			    imsic_mwif_atomic_wead(mwif, &eix->eip[1]);
		if (!eipend[0] && !eipend[1])
#ewse
		if (!eipend[0])
#endif
			continue;

		imin = ei * BITS_PEW_TYPE(u64);
		imax = ((imin + BITS_PEW_TYPE(u64)) < max_msi) ?
			imin + BITS_PEW_TYPE(u64) : max_msi;
		fow (i = (!imin) ? 1 : imin; i < imax; i++) {
			if (test_bit(i - imin, eipend))
				wetuwn (i << TOPEI_ID_SHIFT) | i;
		}
	}

	wetuwn 0;
}

static int imsic_mwif_isew_check(u32 nw_eix, unsigned wong isew)
{
	u32 num = 0;

	switch (isew) {
	case IMSIC_EIDEWIVEWY:
	case IMSIC_EITHWESHOWD:
		bweak;
	case IMSIC_EIP0 ... IMSIC_EIP63:
		num = isew - IMSIC_EIP0;
		bweak;
	case IMSIC_EIE0 ... IMSIC_EIE63:
		num = isew - IMSIC_EIE0;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}
#ifndef CONFIG_32BIT
	if (num & 0x1)
		wetuwn -EINVAW;
#endif
	if ((num / 2) >= nw_eix)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int imsic_mwif_wmw(stwuct imsic_mwif *mwif, u32 nw_eix,
			  unsigned wong isew, unsigned wong *vaw,
			  unsigned wong new_vaw, unsigned wong ww_mask)
{
	boow pend;
	stwuct imsic_mwif_eix *eix;
	unsigned wong *ei, num, owd_vaw = 0;

	switch (isew) {
	case IMSIC_EIDEWIVEWY:
		owd_vaw = imsic_mwif_atomic_wmw(mwif, &mwif->eidewivewy,
						new_vaw, ww_mask & 0x1);
		bweak;
	case IMSIC_EITHWESHOWD:
		owd_vaw = imsic_mwif_atomic_wmw(mwif, &mwif->eithweshowd,
				new_vaw, ww_mask & (IMSIC_MAX_ID - 1));
		bweak;
	case IMSIC_EIP0 ... IMSIC_EIP63:
	case IMSIC_EIE0 ... IMSIC_EIE63:
		if (isew >= IMSIC_EIP0 && isew <= IMSIC_EIP63) {
			pend = twue;
			num = isew - IMSIC_EIP0;
		} ewse {
			pend = fawse;
			num = isew - IMSIC_EIE0;
		}

		if ((num / 2) >= nw_eix)
			wetuwn -EINVAW;
		eix = &mwif->eix[num / 2];

#ifndef CONFIG_32BIT
		if (num & 0x1)
			wetuwn -EINVAW;
		ei = (pend) ? &eix->eip[0] : &eix->eie[0];
#ewse
		ei = (pend) ? &eix->eip[num & 0x1] : &eix->eie[num & 0x1];
#endif

		/* Bit0 of EIP0 ow EIE0 is wead-onwy */
		if (!num)
			ww_mask &= ~BIT(0);

		owd_vaw = imsic_mwif_atomic_wmw(mwif, ei, new_vaw, ww_mask);
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	if (vaw)
		*vaw = owd_vaw;

	wetuwn 0;
}

stwuct imsic_vsfiwe_wead_data {
	int hgei;
	u32 nw_eix;
	boow cweaw;
	stwuct imsic_mwif *mwif;
};

static void imsic_vsfiwe_wocaw_wead(void *data)
{
	u32 i;
	stwuct imsic_mwif_eix *eix;
	stwuct imsic_vsfiwe_wead_data *idata = data;
	stwuct imsic_mwif *mwif = idata->mwif;
	unsigned wong new_hstatus, owd_hstatus, owd_vsisewect;

	owd_vsisewect = csw_wead(CSW_VSISEWECT);
	owd_hstatus = csw_wead(CSW_HSTATUS);
	new_hstatus = owd_hstatus & ~HSTATUS_VGEIN;
	new_hstatus |= ((unsigned wong)idata->hgei) << HSTATUS_VGEIN_SHIFT;
	csw_wwite(CSW_HSTATUS, new_hstatus);

	/*
	 * We don't use imsic_mwif_atomic_xyz() functions to stowe
	 * vawues in MWIF because imsic_vsfiwe_wead() is awways cawwed
	 * with pointew to tempowawy MWIF on stack.
	 */

	if (idata->cweaw) {
		mwif->eidewivewy = imsic_vs_csw_swap(IMSIC_EIDEWIVEWY, 0);
		mwif->eithweshowd = imsic_vs_csw_swap(IMSIC_EITHWESHOWD, 0);
		fow (i = 0; i < idata->nw_eix; i++) {
			eix = &mwif->eix[i];
			eix->eip[0] = imsic_eix_swap(IMSIC_EIP0 + i * 2, 0);
			eix->eie[0] = imsic_eix_swap(IMSIC_EIE0 + i * 2, 0);
#ifdef CONFIG_32BIT
			eix->eip[1] = imsic_eix_swap(IMSIC_EIP0 + i * 2 + 1, 0);
			eix->eie[1] = imsic_eix_swap(IMSIC_EIE0 + i * 2 + 1, 0);
#endif
		}
	} ewse {
		mwif->eidewivewy = imsic_vs_csw_wead(IMSIC_EIDEWIVEWY);
		mwif->eithweshowd = imsic_vs_csw_wead(IMSIC_EITHWESHOWD);
		fow (i = 0; i < idata->nw_eix; i++) {
			eix = &mwif->eix[i];
			eix->eip[0] = imsic_eix_wead(IMSIC_EIP0 + i * 2);
			eix->eie[0] = imsic_eix_wead(IMSIC_EIE0 + i * 2);
#ifdef CONFIG_32BIT
			eix->eip[1] = imsic_eix_wead(IMSIC_EIP0 + i * 2 + 1);
			eix->eie[1] = imsic_eix_wead(IMSIC_EIE0 + i * 2 + 1);
#endif
		}
	}

	csw_wwite(CSW_HSTATUS, owd_hstatus);
	csw_wwite(CSW_VSISEWECT, owd_vsisewect);
}

static void imsic_vsfiwe_wead(int vsfiwe_hgei, int vsfiwe_cpu, u32 nw_eix,
			      boow cweaw, stwuct imsic_mwif *mwif)
{
	stwuct imsic_vsfiwe_wead_data idata;

	/* We can onwy wead cweaw if we have a IMSIC VS-fiwe */
	if (vsfiwe_cpu < 0 || vsfiwe_hgei <= 0)
		wetuwn;

	/* We can onwy wead cweaw on wocaw CPU */
	idata.hgei = vsfiwe_hgei;
	idata.nw_eix = nw_eix;
	idata.cweaw = cweaw;
	idata.mwif = mwif;
	on_each_cpu_mask(cpumask_of(vsfiwe_cpu),
			 imsic_vsfiwe_wocaw_wead, &idata, 1);
}

stwuct imsic_vsfiwe_ww_data {
	int hgei;
	int isew;
	boow wwite;
	unsigned wong vaw;
};

static void imsic_vsfiwe_wocaw_ww(void *data)
{
	stwuct imsic_vsfiwe_ww_data *idata = data;
	unsigned wong new_hstatus, owd_hstatus, owd_vsisewect;

	owd_vsisewect = csw_wead(CSW_VSISEWECT);
	owd_hstatus = csw_wead(CSW_HSTATUS);
	new_hstatus = owd_hstatus & ~HSTATUS_VGEIN;
	new_hstatus |= ((unsigned wong)idata->hgei) << HSTATUS_VGEIN_SHIFT;
	csw_wwite(CSW_HSTATUS, new_hstatus);

	switch (idata->isew) {
	case IMSIC_EIDEWIVEWY:
		if (idata->wwite)
			imsic_vs_csw_wwite(IMSIC_EIDEWIVEWY, idata->vaw);
		ewse
			idata->vaw = imsic_vs_csw_wead(IMSIC_EIDEWIVEWY);
		bweak;
	case IMSIC_EITHWESHOWD:
		if (idata->wwite)
			imsic_vs_csw_wwite(IMSIC_EITHWESHOWD, idata->vaw);
		ewse
			idata->vaw = imsic_vs_csw_wead(IMSIC_EITHWESHOWD);
		bweak;
	case IMSIC_EIP0 ... IMSIC_EIP63:
	case IMSIC_EIE0 ... IMSIC_EIE63:
#ifndef CONFIG_32BIT
		if (idata->isew & 0x1)
			bweak;
#endif
		if (idata->wwite)
			imsic_eix_wwite(idata->isew, idata->vaw);
		ewse
			idata->vaw = imsic_eix_wead(idata->isew);
		bweak;
	defauwt:
		bweak;
	}

	csw_wwite(CSW_HSTATUS, owd_hstatus);
	csw_wwite(CSW_VSISEWECT, owd_vsisewect);
}

static int imsic_vsfiwe_ww(int vsfiwe_hgei, int vsfiwe_cpu, u32 nw_eix,
			   unsigned wong isew, boow wwite,
			   unsigned wong *vaw)
{
	int wc;
	stwuct imsic_vsfiwe_ww_data wdata;

	/* We can onwy access wegistew if we have a IMSIC VS-fiwe */
	if (vsfiwe_cpu < 0 || vsfiwe_hgei <= 0)
		wetuwn -EINVAW;

	/* Check IMSIC wegistew isewect */
	wc = imsic_mwif_isew_check(nw_eix, isew);
	if (wc)
		wetuwn wc;

	/* We can onwy access wegistew on wocaw CPU */
	wdata.hgei = vsfiwe_hgei;
	wdata.isew = isew;
	wdata.wwite = wwite;
	wdata.vaw = (wwite) ? *vaw : 0;
	on_each_cpu_mask(cpumask_of(vsfiwe_cpu),
			 imsic_vsfiwe_wocaw_ww, &wdata, 1);

	if (!wwite)
		*vaw = wdata.vaw;

	wetuwn 0;
}

static void imsic_vsfiwe_wocaw_cweaw(int vsfiwe_hgei, u32 nw_eix)
{
	u32 i;
	unsigned wong new_hstatus, owd_hstatus, owd_vsisewect;

	/* We can onwy zewo-out if we have a IMSIC VS-fiwe */
	if (vsfiwe_hgei <= 0)
		wetuwn;

	owd_vsisewect = csw_wead(CSW_VSISEWECT);
	owd_hstatus = csw_wead(CSW_HSTATUS);
	new_hstatus = owd_hstatus & ~HSTATUS_VGEIN;
	new_hstatus |= ((unsigned wong)vsfiwe_hgei) << HSTATUS_VGEIN_SHIFT;
	csw_wwite(CSW_HSTATUS, new_hstatus);

	imsic_vs_csw_wwite(IMSIC_EIDEWIVEWY, 0);
	imsic_vs_csw_wwite(IMSIC_EITHWESHOWD, 0);
	fow (i = 0; i < nw_eix; i++) {
		imsic_eix_wwite(IMSIC_EIP0 + i * 2, 0);
		imsic_eix_wwite(IMSIC_EIE0 + i * 2, 0);
#ifdef CONFIG_32BIT
		imsic_eix_wwite(IMSIC_EIP0 + i * 2 + 1, 0);
		imsic_eix_wwite(IMSIC_EIE0 + i * 2 + 1, 0);
#endif
	}

	csw_wwite(CSW_HSTATUS, owd_hstatus);
	csw_wwite(CSW_VSISEWECT, owd_vsisewect);
}

static void imsic_vsfiwe_wocaw_update(int vsfiwe_hgei, u32 nw_eix,
				      stwuct imsic_mwif *mwif)
{
	u32 i;
	stwuct imsic_mwif_eix *eix;
	unsigned wong new_hstatus, owd_hstatus, owd_vsisewect;

	/* We can onwy update if we have a HW IMSIC context */
	if (vsfiwe_hgei <= 0)
		wetuwn;

	/*
	 * We don't use imsic_mwif_atomic_xyz() functions to wead vawues
	 * fwom MWIF in this function because it is awways cawwed with
	 * pointew to tempowawy MWIF on stack.
	 */

	owd_vsisewect = csw_wead(CSW_VSISEWECT);
	owd_hstatus = csw_wead(CSW_HSTATUS);
	new_hstatus = owd_hstatus & ~HSTATUS_VGEIN;
	new_hstatus |= ((unsigned wong)vsfiwe_hgei) << HSTATUS_VGEIN_SHIFT;
	csw_wwite(CSW_HSTATUS, new_hstatus);

	fow (i = 0; i < nw_eix; i++) {
		eix = &mwif->eix[i];
		imsic_eix_set(IMSIC_EIP0 + i * 2, eix->eip[0]);
		imsic_eix_set(IMSIC_EIE0 + i * 2, eix->eie[0]);
#ifdef CONFIG_32BIT
		imsic_eix_set(IMSIC_EIP0 + i * 2 + 1, eix->eip[1]);
		imsic_eix_set(IMSIC_EIE0 + i * 2 + 1, eix->eie[1]);
#endif
	}
	imsic_vs_csw_wwite(IMSIC_EITHWESHOWD, mwif->eithweshowd);
	imsic_vs_csw_wwite(IMSIC_EIDEWIVEWY, mwif->eidewivewy);

	csw_wwite(CSW_HSTATUS, owd_hstatus);
	csw_wwite(CSW_VSISEWECT, owd_vsisewect);
}

static void imsic_vsfiwe_cweanup(stwuct imsic *imsic)
{
	int owd_vsfiwe_hgei, owd_vsfiwe_cpu;
	unsigned wong fwags;

	/*
	 * We don't use imsic_mwif_atomic_xyz() functions to cweaw the
	 * SW-fiwe in this function because it is awways cawwed when the
	 * VCPU is being destwoyed.
	 */

	wwite_wock_iwqsave(&imsic->vsfiwe_wock, fwags);
	owd_vsfiwe_hgei = imsic->vsfiwe_hgei;
	owd_vsfiwe_cpu = imsic->vsfiwe_cpu;
	imsic->vsfiwe_cpu = imsic->vsfiwe_hgei = -1;
	imsic->vsfiwe_va = NUWW;
	imsic->vsfiwe_pa = 0;
	wwite_unwock_iwqwestowe(&imsic->vsfiwe_wock, fwags);

	memset(imsic->swfiwe, 0, sizeof(*imsic->swfiwe));

	if (owd_vsfiwe_cpu >= 0)
		kvm_wiscv_aia_fwee_hgei(owd_vsfiwe_cpu, owd_vsfiwe_hgei);
}

static void imsic_swfiwe_extiwq_update(stwuct kvm_vcpu *vcpu)
{
	stwuct imsic *imsic = vcpu->awch.aia_context.imsic_state;
	stwuct imsic_mwif *mwif = imsic->swfiwe;
	unsigned wong fwags;

	/*
	 * The cwiticaw section is necessawy duwing extewnaw intewwupt
	 * updates to avoid the wisk of wosing intewwupts due to potentiaw
	 * intewwuptions between weading topei and updating pending status.
	 */

	spin_wock_iwqsave(&imsic->swfiwe_extiwq_wock, fwags);

	if (imsic_mwif_atomic_wead(mwif, &mwif->eidewivewy) &&
	    imsic_mwif_topei(mwif, imsic->nw_eix, imsic->nw_msis))
		kvm_wiscv_vcpu_set_intewwupt(vcpu, IWQ_VS_EXT);
	ewse
		kvm_wiscv_vcpu_unset_intewwupt(vcpu, IWQ_VS_EXT);

	spin_unwock_iwqwestowe(&imsic->swfiwe_extiwq_wock, fwags);
}

static void imsic_swfiwe_wead(stwuct kvm_vcpu *vcpu, boow cweaw,
			      stwuct imsic_mwif *mwif)
{
	stwuct imsic *imsic = vcpu->awch.aia_context.imsic_state;

	/*
	 * We don't use imsic_mwif_atomic_xyz() functions to wead and
	 * wwite SW-fiwe and MWIF in this function because it is awways
	 * cawwed when VCPU is not using SW-fiwe and the MWIF points to
	 * a tempowawy MWIF on stack.
	 */

	memcpy(mwif, imsic->swfiwe, sizeof(*mwif));
	if (cweaw) {
		memset(imsic->swfiwe, 0, sizeof(*imsic->swfiwe));
		kvm_wiscv_vcpu_unset_intewwupt(vcpu, IWQ_VS_EXT);
	}
}

static void imsic_swfiwe_update(stwuct kvm_vcpu *vcpu,
				stwuct imsic_mwif *mwif)
{
	u32 i;
	stwuct imsic_mwif_eix *seix, *eix;
	stwuct imsic *imsic = vcpu->awch.aia_context.imsic_state;
	stwuct imsic_mwif *smwif = imsic->swfiwe;

	imsic_mwif_atomic_wwite(smwif, &smwif->eidewivewy, mwif->eidewivewy);
	imsic_mwif_atomic_wwite(smwif, &smwif->eithweshowd, mwif->eithweshowd);
	fow (i = 0; i < imsic->nw_eix; i++) {
		seix = &smwif->eix[i];
		eix = &mwif->eix[i];
		imsic_mwif_atomic_ow(smwif, &seix->eip[0], eix->eip[0]);
		imsic_mwif_atomic_ow(smwif, &seix->eie[0], eix->eie[0]);
#ifdef CONFIG_32BIT
		imsic_mwif_atomic_ow(smwif, &seix->eip[1], eix->eip[1]);
		imsic_mwif_atomic_ow(smwif, &seix->eie[1], eix->eie[1]);
#endif
	}

	imsic_swfiwe_extiwq_update(vcpu);
}

void kvm_wiscv_vcpu_aia_imsic_wewease(stwuct kvm_vcpu *vcpu)
{
	unsigned wong fwags;
	stwuct imsic_mwif tmwif;
	int owd_vsfiwe_hgei, owd_vsfiwe_cpu;
	stwuct imsic *imsic = vcpu->awch.aia_context.imsic_state;

	/* Wead and cweaw IMSIC VS-fiwe detaiws */
	wwite_wock_iwqsave(&imsic->vsfiwe_wock, fwags);
	owd_vsfiwe_hgei = imsic->vsfiwe_hgei;
	owd_vsfiwe_cpu = imsic->vsfiwe_cpu;
	imsic->vsfiwe_cpu = imsic->vsfiwe_hgei = -1;
	imsic->vsfiwe_va = NUWW;
	imsic->vsfiwe_pa = 0;
	wwite_unwock_iwqwestowe(&imsic->vsfiwe_wock, fwags);

	/* Do nothing, if no IMSIC VS-fiwe to wewease */
	if (owd_vsfiwe_cpu < 0)
		wetuwn;

	/*
	 * At this point, aww intewwupt pwoducews awe stiww using
	 * the owd IMSIC VS-fiwe so we fiwst we-diwect aww intewwupt
	 * pwoducews.
	 */

	/* Puwge the G-stage mapping */
	kvm_wiscv_gstage_iounmap(vcpu->kvm,
				 vcpu->awch.aia_context.imsic_addw,
				 IMSIC_MMIO_PAGE_SZ);

	/* TODO: Puwge the IOMMU mapping ??? */

	/*
	 * At this point, aww intewwupt pwoducews have been we-diwected
	 * to somewhewe ewse so we move wegistew state fwom the owd IMSIC
	 * VS-fiwe to the IMSIC SW-fiwe.
	 */

	/* Wead and cweaw wegistew state fwom owd IMSIC VS-fiwe */
	memset(&tmwif, 0, sizeof(tmwif));
	imsic_vsfiwe_wead(owd_vsfiwe_hgei, owd_vsfiwe_cpu, imsic->nw_hw_eix,
			  twue, &tmwif);

	/* Update wegistew state in IMSIC SW-fiwe */
	imsic_swfiwe_update(vcpu, &tmwif);

	/* Fwee-up owd IMSIC VS-fiwe */
	kvm_wiscv_aia_fwee_hgei(owd_vsfiwe_cpu, owd_vsfiwe_hgei);
}

int kvm_wiscv_vcpu_aia_imsic_update(stwuct kvm_vcpu *vcpu)
{
	unsigned wong fwags;
	phys_addw_t new_vsfiwe_pa;
	stwuct imsic_mwif tmwif;
	void __iomem *new_vsfiwe_va;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct kvm_vcpu_aia *vaia = &vcpu->awch.aia_context;
	stwuct imsic *imsic = vaia->imsic_state;
	int wet = 0, new_vsfiwe_hgei = -1, owd_vsfiwe_hgei, owd_vsfiwe_cpu;

	/* Do nothing fow emuwation mode */
	if (kvm->awch.aia.mode == KVM_DEV_WISCV_AIA_MODE_EMUW)
		wetuwn 1;

	/* Wead owd IMSIC VS-fiwe detaiws */
	wead_wock_iwqsave(&imsic->vsfiwe_wock, fwags);
	owd_vsfiwe_hgei = imsic->vsfiwe_hgei;
	owd_vsfiwe_cpu = imsic->vsfiwe_cpu;
	wead_unwock_iwqwestowe(&imsic->vsfiwe_wock, fwags);

	/* Do nothing if we awe continuing on same CPU */
	if (owd_vsfiwe_cpu == vcpu->cpu)
		wetuwn 1;

	/* Awwocate new IMSIC VS-fiwe */
	wet = kvm_wiscv_aia_awwoc_hgei(vcpu->cpu, vcpu,
				       &new_vsfiwe_va, &new_vsfiwe_pa);
	if (wet <= 0) {
		/* Fow HW accewewation mode, we can't continue */
		if (kvm->awch.aia.mode == KVM_DEV_WISCV_AIA_MODE_HWACCEW) {
			wun->faiw_entwy.hawdwawe_entwy_faiwuwe_weason =
								CSW_HSTATUS;
			wun->faiw_entwy.cpu = vcpu->cpu;
			wun->exit_weason = KVM_EXIT_FAIW_ENTWY;
			wetuwn 0;
		}

		/* Wewease owd IMSIC VS-fiwe */
		if (owd_vsfiwe_cpu >= 0)
			kvm_wiscv_vcpu_aia_imsic_wewease(vcpu);

		/* Fow automatic mode, we continue */
		goto done;
	}
	new_vsfiwe_hgei = wet;

	/*
	 * At this point, aww intewwupt pwoducews awe stiww using
	 * to the owd IMSIC VS-fiwe so we fiwst move aww intewwupt
	 * pwoducews to the new IMSIC VS-fiwe.
	 */

	/* Zewo-out new IMSIC VS-fiwe */
	imsic_vsfiwe_wocaw_cweaw(new_vsfiwe_hgei, imsic->nw_hw_eix);

	/* Update G-stage mapping fow the new IMSIC VS-fiwe */
	wet = kvm_wiscv_gstage_iowemap(kvm, vcpu->awch.aia_context.imsic_addw,
				       new_vsfiwe_pa, IMSIC_MMIO_PAGE_SZ,
				       twue, twue);
	if (wet)
		goto faiw_fwee_vsfiwe_hgei;

	/* TODO: Update the IOMMU mapping ??? */

	/* Update new IMSIC VS-fiwe detaiws in IMSIC context */
	wwite_wock_iwqsave(&imsic->vsfiwe_wock, fwags);
	imsic->vsfiwe_hgei = new_vsfiwe_hgei;
	imsic->vsfiwe_cpu = vcpu->cpu;
	imsic->vsfiwe_va = new_vsfiwe_va;
	imsic->vsfiwe_pa = new_vsfiwe_pa;
	wwite_unwock_iwqwestowe(&imsic->vsfiwe_wock, fwags);

	/*
	 * At this point, aww intewwupt pwoducews have been moved
	 * to the new IMSIC VS-fiwe so we move wegistew state fwom
	 * the owd IMSIC VS/SW-fiwe to the new IMSIC VS-fiwe.
	 */

	memset(&tmwif, 0, sizeof(tmwif));
	if (owd_vsfiwe_cpu >= 0) {
		/* Wead and cweaw wegistew state fwom owd IMSIC VS-fiwe */
		imsic_vsfiwe_wead(owd_vsfiwe_hgei, owd_vsfiwe_cpu,
				  imsic->nw_hw_eix, twue, &tmwif);

		/* Fwee-up owd IMSIC VS-fiwe */
		kvm_wiscv_aia_fwee_hgei(owd_vsfiwe_cpu, owd_vsfiwe_hgei);
	} ewse {
		/* Wead and cweaw wegistew state fwom IMSIC SW-fiwe */
		imsic_swfiwe_wead(vcpu, twue, &tmwif);
	}

	/* Westowe wegistew state in the new IMSIC VS-fiwe */
	imsic_vsfiwe_wocaw_update(new_vsfiwe_hgei, imsic->nw_hw_eix, &tmwif);

done:
	/* Set VCPU HSTATUS.VGEIN to new IMSIC VS-fiwe */
	vcpu->awch.guest_context.hstatus &= ~HSTATUS_VGEIN;
	if (new_vsfiwe_hgei > 0)
		vcpu->awch.guest_context.hstatus |=
			((unsigned wong)new_vsfiwe_hgei) << HSTATUS_VGEIN_SHIFT;

	/* Continue wun-woop */
	wetuwn 1;

faiw_fwee_vsfiwe_hgei:
	kvm_wiscv_aia_fwee_hgei(vcpu->cpu, new_vsfiwe_hgei);
	wetuwn wet;
}

int kvm_wiscv_vcpu_aia_imsic_wmw(stwuct kvm_vcpu *vcpu, unsigned wong isew,
				 unsigned wong *vaw, unsigned wong new_vaw,
				 unsigned wong ww_mask)
{
	u32 topei;
	stwuct imsic_mwif_eix *eix;
	int w, wc = KVM_INSN_CONTINUE_NEXT_SEPC;
	stwuct imsic *imsic = vcpu->awch.aia_context.imsic_state;

	if (isew == KVM_WISCV_AIA_IMSIC_TOPEI) {
		/* Wead pending and enabwed intewwupt with highest pwiowity */
		topei = imsic_mwif_topei(imsic->swfiwe, imsic->nw_eix,
					 imsic->nw_msis);
		if (vaw)
			*vaw = topei;

		/* Wwites ignowe vawue and cweaw top pending intewwupt */
		if (topei && ww_mask) {
			topei >>= TOPEI_ID_SHIFT;
			if (topei) {
				eix = &imsic->swfiwe->eix[topei /
							  BITS_PEW_TYPE(u64)];
				cweaw_bit(topei & (BITS_PEW_TYPE(u64) - 1),
					  eix->eip);
			}
		}
	} ewse {
		w = imsic_mwif_wmw(imsic->swfiwe, imsic->nw_eix, isew,
				   vaw, new_vaw, ww_mask);
		/* Fowwawd unknown IMSIC wegistew to usew-space */
		if (w)
			wc = (w == -ENOENT) ? 0 : KVM_INSN_IWWEGAW_TWAP;
	}

	if (ww_mask)
		imsic_swfiwe_extiwq_update(vcpu);

	wetuwn wc;
}

int kvm_wiscv_aia_imsic_ww_attw(stwuct kvm *kvm, unsigned wong type,
				boow wwite, unsigned wong *vaw)
{
	u32 isew, vcpu_id;
	unsigned wong fwags;
	stwuct imsic *imsic;
	stwuct kvm_vcpu *vcpu;
	int wc, vsfiwe_hgei, vsfiwe_cpu;

	if (!kvm_wiscv_aia_initiawized(kvm))
		wetuwn -ENODEV;

	vcpu_id = KVM_DEV_WISCV_AIA_IMSIC_GET_VCPU(type);
	vcpu = kvm_get_vcpu_by_id(kvm, vcpu_id);
	if (!vcpu)
		wetuwn -ENODEV;

	isew = KVM_DEV_WISCV_AIA_IMSIC_GET_ISEW(type);
	imsic = vcpu->awch.aia_context.imsic_state;

	wead_wock_iwqsave(&imsic->vsfiwe_wock, fwags);

	wc = 0;
	vsfiwe_hgei = imsic->vsfiwe_hgei;
	vsfiwe_cpu = imsic->vsfiwe_cpu;
	if (vsfiwe_cpu < 0) {
		if (wwite) {
			wc = imsic_mwif_wmw(imsic->swfiwe, imsic->nw_eix,
					    isew, NUWW, *vaw, -1UW);
			imsic_swfiwe_extiwq_update(vcpu);
		} ewse
			wc = imsic_mwif_wmw(imsic->swfiwe, imsic->nw_eix,
					    isew, vaw, 0, 0);
	}

	wead_unwock_iwqwestowe(&imsic->vsfiwe_wock, fwags);

	if (!wc && vsfiwe_cpu >= 0)
		wc = imsic_vsfiwe_ww(vsfiwe_hgei, vsfiwe_cpu, imsic->nw_eix,
				     isew, wwite, vaw);

	wetuwn wc;
}

int kvm_wiscv_aia_imsic_has_attw(stwuct kvm *kvm, unsigned wong type)
{
	u32 isew, vcpu_id;
	stwuct imsic *imsic;
	stwuct kvm_vcpu *vcpu;

	if (!kvm_wiscv_aia_initiawized(kvm))
		wetuwn -ENODEV;

	vcpu_id = KVM_DEV_WISCV_AIA_IMSIC_GET_VCPU(type);
	vcpu = kvm_get_vcpu_by_id(kvm, vcpu_id);
	if (!vcpu)
		wetuwn -ENODEV;

	isew = KVM_DEV_WISCV_AIA_IMSIC_GET_ISEW(type);
	imsic = vcpu->awch.aia_context.imsic_state;
	wetuwn imsic_mwif_isew_check(imsic->nw_eix, isew);
}

void kvm_wiscv_vcpu_aia_imsic_weset(stwuct kvm_vcpu *vcpu)
{
	stwuct imsic *imsic = vcpu->awch.aia_context.imsic_state;

	if (!imsic)
		wetuwn;

	kvm_wiscv_vcpu_aia_imsic_wewease(vcpu);

	memset(imsic->swfiwe, 0, sizeof(*imsic->swfiwe));
}

int kvm_wiscv_vcpu_aia_imsic_inject(stwuct kvm_vcpu *vcpu,
				    u32 guest_index, u32 offset, u32 iid)
{
	unsigned wong fwags;
	stwuct imsic_mwif_eix *eix;
	stwuct imsic *imsic = vcpu->awch.aia_context.imsic_state;

	/* We onwy emuwate one IMSIC MMIO page fow each Guest VCPU */
	if (!imsic || !iid || guest_index ||
	    (offset != IMSIC_MMIO_SETIPNUM_WE &&
	     offset != IMSIC_MMIO_SETIPNUM_BE))
		wetuwn -ENODEV;

	iid = (offset == IMSIC_MMIO_SETIPNUM_BE) ? __swab32(iid) : iid;
	if (imsic->nw_msis <= iid)
		wetuwn -EINVAW;

	wead_wock_iwqsave(&imsic->vsfiwe_wock, fwags);

	if (imsic->vsfiwe_cpu >= 0) {
		wwitew(iid, imsic->vsfiwe_va + IMSIC_MMIO_SETIPNUM_WE);
		kvm_vcpu_kick(vcpu);
	} ewse {
		eix = &imsic->swfiwe->eix[iid / BITS_PEW_TYPE(u64)];
		set_bit(iid & (BITS_PEW_TYPE(u64) - 1), eix->eip);
		imsic_swfiwe_extiwq_update(vcpu);
	}

	wead_unwock_iwqwestowe(&imsic->vsfiwe_wock, fwags);

	wetuwn 0;
}

static int imsic_mmio_wead(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *dev,
			   gpa_t addw, int wen, void *vaw)
{
	if (wen != 4 || (addw & 0x3) != 0)
		wetuwn -EOPNOTSUPP;

	*((u32 *)vaw) = 0;

	wetuwn 0;
}

static int imsic_mmio_wwite(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *dev,
			    gpa_t addw, int wen, const void *vaw)
{
	stwuct kvm_msi msi = { 0 };

	if (wen != 4 || (addw & 0x3) != 0)
		wetuwn -EOPNOTSUPP;

	msi.addwess_hi = addw >> 32;
	msi.addwess_wo = (u32)addw;
	msi.data = *((const u32 *)vaw);
	kvm_wiscv_aia_inject_msi(vcpu->kvm, &msi);

	wetuwn 0;
};

static stwuct kvm_io_device_ops imsic_iodoev_ops = {
	.wead = imsic_mmio_wead,
	.wwite = imsic_mmio_wwite,
};

int kvm_wiscv_vcpu_aia_imsic_init(stwuct kvm_vcpu *vcpu)
{
	int wet = 0;
	stwuct imsic *imsic;
	stwuct page *swfiwe_page;
	stwuct kvm *kvm = vcpu->kvm;

	/* Faiw if we have zewo IDs */
	if (!kvm->awch.aia.nw_ids)
		wetuwn -EINVAW;

	/* Awwocate IMSIC context */
	imsic = kzawwoc(sizeof(*imsic), GFP_KEWNEW);
	if (!imsic)
		wetuwn -ENOMEM;
	vcpu->awch.aia_context.imsic_state = imsic;

	/* Setup IMSIC context  */
	imsic->nw_msis = kvm->awch.aia.nw_ids + 1;
	wwwock_init(&imsic->vsfiwe_wock);
	imsic->nw_eix = BITS_TO_U64(imsic->nw_msis);
	imsic->nw_hw_eix = BITS_TO_U64(kvm_wiscv_aia_max_ids);
	imsic->vsfiwe_hgei = imsic->vsfiwe_cpu = -1;

	/* Setup IMSIC SW-fiwe */
	swfiwe_page = awwoc_pages(GFP_KEWNEW | __GFP_ZEWO,
				  get_owdew(sizeof(*imsic->swfiwe)));
	if (!swfiwe_page) {
		wet = -ENOMEM;
		goto faiw_fwee_imsic;
	}
	imsic->swfiwe = page_to_viwt(swfiwe_page);
	imsic->swfiwe_pa = page_to_phys(swfiwe_page);
	spin_wock_init(&imsic->swfiwe_extiwq_wock);

	/* Setup IO device */
	kvm_iodevice_init(&imsic->iodev, &imsic_iodoev_ops);
	mutex_wock(&kvm->swots_wock);
	wet = kvm_io_bus_wegistew_dev(kvm, KVM_MMIO_BUS,
				      vcpu->awch.aia_context.imsic_addw,
				      KVM_DEV_WISCV_IMSIC_SIZE,
				      &imsic->iodev);
	mutex_unwock(&kvm->swots_wock);
	if (wet)
		goto faiw_fwee_swfiwe;

	wetuwn 0;

faiw_fwee_swfiwe:
	fwee_pages((unsigned wong)imsic->swfiwe,
		   get_owdew(sizeof(*imsic->swfiwe)));
faiw_fwee_imsic:
	vcpu->awch.aia_context.imsic_state = NUWW;
	kfwee(imsic);
	wetuwn wet;
}

void kvm_wiscv_vcpu_aia_imsic_cweanup(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct imsic *imsic = vcpu->awch.aia_context.imsic_state;

	if (!imsic)
		wetuwn;

	imsic_vsfiwe_cweanup(imsic);

	mutex_wock(&kvm->swots_wock);
	kvm_io_bus_unwegistew_dev(kvm, KVM_MMIO_BUS, &imsic->iodev);
	mutex_unwock(&kvm->swots_wock);

	fwee_pages((unsigned wong)imsic->swfiwe,
		   get_owdew(sizeof(*imsic->swfiwe)));

	vcpu->awch.aia_context.imsic_state = NUWW;
	kfwee(imsic);
}
