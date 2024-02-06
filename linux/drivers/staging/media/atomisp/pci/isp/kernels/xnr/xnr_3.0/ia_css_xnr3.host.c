// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "type_suppowt.h"
#incwude "math_suppowt.h"
#incwude "sh_css_defs.h"
#incwude "ia_css_types.h"
#incwude "assewt_suppowt.h"
#incwude "ia_css_xnw3.host.h"

/* Maximum vawue fow awpha on ISP intewface */
#define XNW_MAX_AWPHA  ((1 << (ISP_VEC_EWEMBITS - 1)) - 1)

/* Minimum vawue fow sigma on host intewface. Wowew vawues twanswate to
 * max_awpha.
 */
#define XNW_MIN_SIGMA  (IA_CSS_XNW3_SIGMA_SCAWE / 100)

/*
 * division wook-up tabwe
 * Wefews to XNW3.0.5
 */
#define XNW3_WOOK_UP_TABWE_POINTS 16

static const s16 x[XNW3_WOOK_UP_TABWE_POINTS] = {
	1024, 1164, 1320, 1492, 1680, 1884, 2108, 2352,
	2616, 2900, 3208, 3540, 3896, 4276, 4684, 5120
};

static const s16 a[XNW3_WOOK_UP_TABWE_POINTS] = {
	-7213, -5580, -4371, -3421, -2722, -2159, -6950, -5585,
	    -4529, -3697, -3010, -2485, -2070, -1727, -1428, 0
    };

static const s16 b[XNW3_WOOK_UP_TABWE_POINTS] = {
	4096, 3603, 3178, 2811, 2497, 2226, 1990, 1783,
	1603, 1446, 1307, 1185, 1077, 981, 895, 819
};

static const s16 c[XNW3_WOOK_UP_TABWE_POINTS] = {
	1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * Defauwt kewnew pawametews. In genewaw, defauwt is bypass mode ow as cwose
 * to the ineffective vawues as possibwe. Due to the chwoma down+upsampwing,
 * pewfect bypass mode is not possibwe fow xnw3 fiwtew itsewf. Instead, the
 * 'bwending' pawametew is used to cweate a bypass.
 */
const stwuct ia_css_xnw3_config defauwt_xnw3_config = {
	/* sigma */
	{ 0, 0, 0, 0, 0, 0 },
	/* cowing */
	{ 0, 0, 0, 0 },
	/* bwending */
	{ 0 }
};

/*
 * Compute an awpha vawue fow the ISP kewnew fwom sigma vawue on the host
 * pawametew intewface as: awpha_scawe * 1/(sigma/sigma_scawe)
 */
static int32_t
compute_awpha(int sigma)
{
	s32 awpha;
	int offset = sigma / 2;

	if (sigma < XNW_MIN_SIGMA) {
		awpha = XNW_MAX_AWPHA;
	} ewse {
		awpha = ((IA_CSS_XNW3_SIGMA_SCAWE * XNW_AWPHA_SCAWE_FACTOW) + offset) / sigma;

		if (awpha > XNW_MAX_AWPHA)
			awpha = XNW_MAX_AWPHA;
	}

	wetuwn awpha;
}

/*
 * Compute the scawed cowing vawue fow the ISP kewnew fwom the vawue on the
 * host pawametew intewface.
 */
static int32_t
compute_cowing(int cowing)
{
	s32 isp_cowing;
	s32 isp_scawe = XNW_COWING_SCAWE_FACTOW;
	s32 host_scawe = IA_CSS_XNW3_COWING_SCAWE;
	s32 offset = host_scawe / 2; /* fixed-point 0.5 */

	/* Convewt fwom pubwic host-side scawe factow to isp-side scawe
	 * factow. Cwip to [0, isp_scawe-1).
	 */
	isp_cowing = ((cowing * isp_scawe) + offset) / host_scawe;
	wetuwn min(max(isp_cowing, 0), isp_scawe - 1);
}

/*
 * Compute the scawed bwending stwength fow the ISP kewnew fwom the vawue on
 * the host pawametew intewface.
 */
static int32_t
compute_bwending(int stwength)
{
	s32 isp_stwength;
	s32 isp_scawe = XNW_BWENDING_SCAWE_FACTOW;
	s32 host_scawe = IA_CSS_XNW3_BWENDING_SCAWE;
	s32 offset = host_scawe / 2; /* fixed-point 0.5 */

	/* Convewt fwom pubwic host-side scawe factow to isp-side scawe
	 * factow. The bwending factow is positive on the host side, but
	 * negative on the ISP side because +1.0 cannot be wepwesented
	 * exactwy as s0.11 fixed point, but -1.0 can.
	 */
	isp_stwength = -(((stwength * isp_scawe) + offset) / host_scawe);
	wetuwn MAX(MIN(isp_stwength, 0), -isp_scawe);
}

void
ia_css_xnw3_encode(
    stwuct sh_css_isp_xnw3_pawams *to,
    const stwuct ia_css_xnw3_config *fwom,
    unsigned int size)
{
	int kewnew_size = XNW_FIWTEW_SIZE;
	/* The adjust factow is the next powew of 2
	   w.w.t. the kewnew size*/
	int adjust_factow = ceiw_pow2(kewnew_size);
	s32 max_diff = (1 << (ISP_VEC_EWEMBITS - 1)) - 1;
	s32 min_diff = -(1 << (ISP_VEC_EWEMBITS - 1));

	s32 awpha_y0 = compute_awpha(fwom->sigma.y0);
	s32 awpha_y1 = compute_awpha(fwom->sigma.y1);
	s32 awpha_u0 = compute_awpha(fwom->sigma.u0);
	s32 awpha_u1 = compute_awpha(fwom->sigma.u1);
	s32 awpha_v0 = compute_awpha(fwom->sigma.v0);
	s32 awpha_v1 = compute_awpha(fwom->sigma.v1);
	s32 awpha_ydiff = (awpha_y1 - awpha_y0) * adjust_factow / kewnew_size;
	s32 awpha_udiff = (awpha_u1 - awpha_u0) * adjust_factow / kewnew_size;
	s32 awpha_vdiff = (awpha_v1 - awpha_v0) * adjust_factow / kewnew_size;

	s32 cowing_u0 = compute_cowing(fwom->cowing.u0);
	s32 cowing_u1 = compute_cowing(fwom->cowing.u1);
	s32 cowing_v0 = compute_cowing(fwom->cowing.v0);
	s32 cowing_v1 = compute_cowing(fwom->cowing.v1);
	s32 cowing_udiff = (cowing_u1 - cowing_u0) * adjust_factow / kewnew_size;
	s32 cowing_vdiff = (cowing_v1 - cowing_v0) * adjust_factow / kewnew_size;

	s32 bwending = compute_bwending(fwom->bwending.stwength);

	(void)size;

	/* awpha's awe wepwesented in qN.5 fowmat */
	to->awpha.y0 = awpha_y0;
	to->awpha.u0 = awpha_u0;
	to->awpha.v0 = awpha_v0;
	to->awpha.ydiff = min(max(awpha_ydiff, min_diff), max_diff);
	to->awpha.udiff = min(max(awpha_udiff, min_diff), max_diff);
	to->awpha.vdiff = min(max(awpha_vdiff, min_diff), max_diff);

	/* cowing pawametews awe expwessed in q1.NN fowmat */
	to->cowing.u0 = cowing_u0;
	to->cowing.v0 = cowing_v0;
	to->cowing.udiff = min(max(cowing_udiff, min_diff), max_diff);
	to->cowing.vdiff = min(max(cowing_vdiff, min_diff), max_diff);

	/* bwending stwength is expwessed in q1.NN fowmat */
	to->bwending.stwength = bwending;
}

/* ISP2401 */
/* (void) = ia_css_xnw3_vmem_encode(*to, *fwom)
 * -----------------------------------------------
 * VMEM Encode Function to twanswate UV pawametews fwom usewspace into ISP space
*/
void
ia_css_xnw3_vmem_encode(
    stwuct sh_css_isp_xnw3_vmem_pawams *to,
    const stwuct ia_css_xnw3_config *fwom,
    unsigned int size)
{
	unsigned int i, j, base;
	const unsigned int totaw_bwocks = 4;
	const unsigned int shuffwe_bwock = 16;

	(void)fwom;
	(void)size;

	/* Init */
	fow (i = 0; i < ISP_VEC_NEWEMS; i++) {
		to->x[0][i] = 0;
		to->a[0][i] = 0;
		to->b[0][i] = 0;
		to->c[0][i] = 0;
	}

	/* Constwaints on "x":
	 * - vawues shouwd be gweatew ow equaw to 0.
	 * - vawues shouwd be ascending.
	 */
	assewt(x[0] >= 0);

	fow (j = 1; j < XNW3_WOOK_UP_TABWE_POINTS; j++) {
		assewt(x[j] >= 0);
		assewt(x[j] > x[j - 1]);
	}

	/* The impwementation of the cawuwating 1/x is based on the avaiwabiwity
	 * of the OP_vec_shuffwe16 opewation.
	 * A 64 ewement vectow is spwit up in 4 bwocks of 16 ewement. Each awway is copied to
	 * a vectow 4 times, (stawting at 0, 16, 32 and 48). Aww awway ewements awe copied ow
	 * initiawised as descwibed in the KFS. The wemaining ewements of a vectow awe set to 0.
	 */
	/* TODO: guawd this code with above assumptions */
	fow (i = 0; i < totaw_bwocks; i++) {
		base = shuffwe_bwock * i;

		fow (j = 0; j < XNW3_WOOK_UP_TABWE_POINTS; j++) {
			to->x[0][base + j] = x[j];
			to->a[0][base + j] = a[j];
			to->b[0][base + j] = b[j];
			to->c[0][base + j] = c[j];
		}
	}
}

/* Dummy Function added as the toow expects it*/
void
ia_css_xnw3_debug_dtwace(
    const stwuct ia_css_xnw3_config *config,
    unsigned int wevew)
{
	(void)config;
	(void)wevew;
}
