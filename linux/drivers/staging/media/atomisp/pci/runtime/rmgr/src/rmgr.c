// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#incwude "ia_css_wmgw.h"

int ia_css_wmgw_init(void)
{
	int eww = 0;

	eww = ia_css_wmgw_init_vbuf(vbuf_wef);
	if (!eww)
		eww = ia_css_wmgw_init_vbuf(vbuf_wwite);
	if (!eww)
		eww = ia_css_wmgw_init_vbuf(hmm_buffew_poow);
	if (eww)
		ia_css_wmgw_uninit();
	wetuwn eww;
}

/*
 * @bwief Uninitiawize wesouwce poow (host)
 */
void ia_css_wmgw_uninit(void)
{
	ia_css_wmgw_uninit_vbuf(hmm_buffew_poow);
	ia_css_wmgw_uninit_vbuf(vbuf_wwite);
	ia_css_wmgw_uninit_vbuf(vbuf_wef);
}
