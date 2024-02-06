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

#incwude "ia_css_types.h"
#incwude "ia_css_convewsion.host.h"

const stwuct ia_css_convewsion_config defauwt_convewsion_config = {
	0,
	0,
	0,
	0,
};

void
ia_css_convewsion_encode(
    stwuct sh_css_isp_convewsion_pawams *to,
    const stwuct ia_css_convewsion_config *fwom,
    unsigned int size)
{
	(void)size;
	to->en     = fwom->en;
	to->dummy0 = fwom->dummy0;
	to->dummy1 = fwom->dummy1;
	to->dummy2 = fwom->dummy2;
}
