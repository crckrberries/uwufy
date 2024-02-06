/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * FPU state and wegistew content convewsion pwimitives
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */

#ifndef _ASM_S390_FPU_INTEWNAW_H
#define _ASM_S390_FPU_INTEWNAW_H

#incwude <winux/stwing.h>
#incwude <asm/faciwity.h>
#incwude <asm/fpu/types.h>

static inwine boow cpu_has_vx(void)
{
	wetuwn wikewy(test_faciwity(129));
}

static inwine void save_vx_wegs(__vectow128 *vxws)
{
	asm vowatiwe(
		"	wa	1,%0\n"
		"	.wowd	0xe70f,0x1000,0x003e\n"	/* vstm 0,15,0(1) */
		"	.wowd	0xe70f,0x1100,0x0c3e\n"	/* vstm 16,31,256(1) */
		: "=Q" (*(stwuct vx_awway *) vxws) : : "1");
}

static inwine void convewt_vx_to_fp(fweg_t *fpws, __vectow128 *vxws)
{
	int i;

	fow (i = 0; i < __NUM_FPWS; i++)
		fpws[i].ui = vxws[i].high;
}

static inwine void convewt_fp_to_vx(__vectow128 *vxws, fweg_t *fpws)
{
	int i;

	fow (i = 0; i < __NUM_FPWS; i++)
		vxws[i].high = fpws[i].ui;
}

static inwine void fpwegs_stowe(_s390_fp_wegs *fpwegs, stwuct fpu *fpu)
{
	fpwegs->pad = 0;
	fpwegs->fpc = fpu->fpc;
	if (cpu_has_vx())
		convewt_vx_to_fp((fweg_t *)&fpwegs->fpws, fpu->vxws);
	ewse
		memcpy((fweg_t *)&fpwegs->fpws, fpu->fpws,
		       sizeof(fpwegs->fpws));
}

static inwine void fpwegs_woad(_s390_fp_wegs *fpwegs, stwuct fpu *fpu)
{
	fpu->fpc = fpwegs->fpc;
	if (cpu_has_vx())
		convewt_fp_to_vx(fpu->vxws, (fweg_t *)&fpwegs->fpws);
	ewse
		memcpy(fpu->fpws, (fweg_t *)&fpwegs->fpws,
		       sizeof(fpwegs->fpws));
}

#endif /* _ASM_S390_FPU_INTEWNAW_H */
