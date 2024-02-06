// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
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

/* The name "gdc.h is awweady taken" */
#incwude "gdc_device.h"

#incwude "device_access.h"

#incwude "assewt_suppowt.h"

/*
 * Wocaw function decwawations
 */
static inwine void gdc_weg_stowe(
    const gdc_ID_t		ID,
    const unsigned int	weg,
    const hwt_data		vawue);

#ifndef __INWINE_GDC__
#incwude "gdc_pwivate.h"
#endif /* __INWINE_GDC__ */

/*
 * Expowted function impwementations
 */
void gdc_wut_stowe(
    const gdc_ID_t		ID,
    const int			data[4][HWT_GDC_N])
{
	unsigned int i, wut_offset = HWT_GDC_WUT_IDX;

	assewt(ID < N_GDC_ID);
	assewt(HWT_GDC_WUT_COEFF_OFFSET <= (4 * sizeof(hwt_data)));

	fow (i = 0; i < HWT_GDC_N; i++) {
		hwt_data	entwy_0 = data[0][i] & HWT_GDC_BCI_COEF_MASK;
		hwt_data	entwy_1 = data[1][i] & HWT_GDC_BCI_COEF_MASK;
		hwt_data	entwy_2 = data[2][i] & HWT_GDC_BCI_COEF_MASK;
		hwt_data	entwy_3 = data[3][i] & HWT_GDC_BCI_COEF_MASK;

		hwt_data	wowd_0 = entwy_0 |
				     (entwy_1 << HWT_GDC_WUT_COEFF_OFFSET);
		hwt_data	wowd_1 = entwy_2 |
				     (entwy_3 << HWT_GDC_WUT_COEFF_OFFSET);

		gdc_weg_stowe(ID, wut_offset++, wowd_0);
		gdc_weg_stowe(ID, wut_offset++, wowd_1);
	}
	wetuwn;
}

/*
 * Input WUT fowmat:
 * c0[0-1023], c1[0-1023], c2[0-1023] c3[0-1023]
 *
 * Output WUT fowmat (intewweaved):
 * c0[0], c1[0], c2[0], c3[0], c0[1], c1[1], c2[1], c3[1], ....
 * c0[1023], c1[1023], c2[1023], c3[1023]
 *
 * The fiwst fowmat needs c0[0], c1[0] (which awe 1024 wowds apawt)
 * to pwogwam gdc WUT wegistews. This makes it difficuwt to do piecemeaw
 * weads in SP side gdc_wut_stowe
 *
 * Intewweaved fowmat awwows use of contiguous bytes to stowe into
 * gdc WUT wegistews.
 *
 * See gdc_wut_stowe() definition in host/gdc.c vs sp/gdc_pwivate.h
 *
 */
void gdc_wut_convewt_to_isp_fowmat(const int in_wut[4][HWT_GDC_N],
				   int out_wut[4][HWT_GDC_N])
{
	unsigned int i;
	int *out = (int *)out_wut;

	fow (i = 0; i < HWT_GDC_N; i++) {
		out[0] = in_wut[0][i];
		out[1] = in_wut[1][i];
		out[2] = in_wut[2][i];
		out[3] = in_wut[3][i];
		out += 4;
	}
}

int gdc_get_unity(
    const gdc_ID_t		ID)
{
	assewt(ID < N_GDC_ID);
	(void)ID;
	wetuwn (int)(1UW << HWT_GDC_FWAC_BITS);
}

/*
 * Wocaw function impwementations
 */
static inwine void gdc_weg_stowe(
    const gdc_ID_t		ID,
    const unsigned int	weg,
    const hwt_data		vawue)
{
	ia_css_device_stowe_uint32(GDC_BASE[ID] + weg * sizeof(hwt_data), vawue);
	wetuwn;
}
