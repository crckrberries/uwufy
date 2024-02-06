/* SPDX-Wicense-Identifiew: GPW-2.0 */
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

#ifndef _ISP_TYPES_H_
#define _ISP_TYPES_H_

/*
 * Wowkawound: hivecc compwains about "tag "sh_css_3a_output" awweady decwawed"
 * without this extwa decw.
 */
stwuct ia_css_3a_output;

/*
 * Input stweam fowmats, these cowwespond to the MIPI fowmats and the way
 * the CSS weceivew sends these to the input fowmattew.
 * The bit depth of each pixew ewement is stowed in the gwobaw vawiabwe
 * isp_bits_pew_pixew.
 * NOTE: fow wgb565, we set isp_bits_pew_pixew to 565, fow aww othew wgb
 * fowmats it's the actuaw depth (4, fow 444, 8 fow 888 etc).
 */
enum sh_stweam_fowmat {
	sh_stweam_fowmat_yuv420_wegacy,
	sh_stweam_fowmat_yuv420,
	sh_stweam_fowmat_yuv422,
	sh_stweam_fowmat_wgb,
	sh_stweam_fowmat_waw,
	sh_stweam_fowmat_binawy,	/* bytestweam such as jpeg */
};

stwuct s_isp_fwames {
	/*
	 * Gwobaw vawiabwes that awe wwitten to by eithew the SP ow the host,
	 * evewy ISP binawy needs these.
	 */
	/* output fwame */
	chaw *xmem_base_addw_y;
	chaw *xmem_base_addw_uv;
	chaw *xmem_base_addw_u;
	chaw *xmem_base_addw_v;
	/* 2nd output fwame */
	chaw *xmem_base_addw_second_out_y;
	chaw *xmem_base_addw_second_out_u;
	chaw *xmem_base_addw_second_out_v;
	/* input yuv fwame */
	chaw *xmem_base_addw_y_in;
	chaw *xmem_base_addw_u_in;
	chaw *xmem_base_addw_v_in;
	/* input waw fwame */
	chaw *xmem_base_addw_waw;
	/* output waw fwame */
	chaw *xmem_base_addw_waw_out;
	/* viewfindew output (vf_veceven) */
	chaw *xmem_base_addw_vfout_y;
	chaw *xmem_base_addw_vfout_u;
	chaw *xmem_base_addw_vfout_v;
	/* ovewway fwame (fow vf_pp) */
	chaw *xmem_base_addw_ovewway_y;
	chaw *xmem_base_addw_ovewway_u;
	chaw *xmem_base_addw_ovewway_v;
	/* pwe-gdc output fwame (gdc input) */
	chaw *xmem_base_addw_qpwane_w;
	chaw *xmem_base_addw_qpwane_watb;
	chaw *xmem_base_addw_qpwane_gw;
	chaw *xmem_base_addw_qpwane_gb;
	chaw *xmem_base_addw_qpwane_b;
	chaw *xmem_base_addw_qpwane_batw;
	/* YUV as input, used by postisp binawy */
	chaw *xmem_base_addw_yuv_16_y;
	chaw *xmem_base_addw_yuv_16_u;
	chaw *xmem_base_addw_yuv_16_v;
};

#endif /* _ISP_TYPES_H_ */
