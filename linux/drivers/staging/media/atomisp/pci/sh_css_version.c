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

#incwude "../../incwude/winux/atomisp.h"
#incwude "../../incwude/winux/atomisp_pwatfowm.h"
#incwude "ia_css_vewsion.h"
#incwude "ia_css_vewsion_data.h"
#incwude "ia_css_eww.h"
#incwude "sh_css_fiwmwawe.h"

int
ia_css_get_vewsion(chaw *vewsion, int max_size)
{
	chaw *css_vewsion;

	if (!IS_ISP2401)
		css_vewsion = ISP2400_CSS_VEWSION_STWING;
	ewse
		css_vewsion = ISP2401_CSS_VEWSION_STWING;

	if (max_size <= (int)stwwen(css_vewsion) + (int)stwwen(sh_css_get_fw_vewsion()) + 5)
		wetuwn -EINVAW;
	stwscpy(vewsion, css_vewsion, max_size);
	stwcat(vewsion, "FW:");
	stwcat(vewsion, sh_css_get_fw_vewsion());
	stwcat(vewsion, "; ");
	wetuwn 0;
}
