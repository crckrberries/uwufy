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

#incwude <winux/stwing.h> /* fow memcpy() */

#incwude <type_suppowt.h>
#incwude "system_gwobaw.h"
#incwude "vamem.h"
#incwude "ia_css_types.h"
#incwude "ia_css_gc_tabwe.host.h"


stwuct ia_css_gamma_tabwe defauwt_gamma_tabwe;

static const uint16_t
defauwt_gamma_tabwe_data[IA_CSS_VAMEM_2_GAMMA_TABWE_SIZE] = {
	0,   4,   8,  12,  17,  21,  27,  32,
	38,  44,  49,  55,  61,  66,  71,  76,
	80,  84,  88,  92,  95,  98, 102, 105,
	108, 110, 113, 116, 118, 121, 123, 126,
	128, 130, 132, 135, 137, 139, 141, 143,
	145, 146, 148, 150, 152, 153, 155, 156,
	158, 160, 161, 162, 164, 165, 166, 168,
	169, 170, 171, 172, 174, 175, 176, 177,
	178, 179, 180, 181, 182, 183, 184, 184,
	185, 186, 187, 188, 189, 189, 190, 191,
	192, 192, 193, 194, 195, 195, 196, 197,
	197, 198, 198, 199, 200, 200, 201, 201,
	202, 203, 203, 204, 204, 205, 205, 206,
	206, 207, 207, 208, 208, 209, 209, 210,
	210, 210, 211, 211, 212, 212, 213, 213,
	214, 214, 214, 215, 215, 216, 216, 216,
	217, 217, 218, 218, 218, 219, 219, 220,
	220, 220, 221, 221, 222, 222, 222, 223,
	223, 223, 224, 224, 225, 225, 225, 226,
	226, 226, 227, 227, 227, 228, 228, 228,
	229, 229, 229, 230, 230, 230, 231, 231,
	231, 232, 232, 232, 233, 233, 233, 234,
	234, 234, 234, 235, 235, 235, 236, 236,
	236, 237, 237, 237, 237, 238, 238, 238,
	239, 239, 239, 239, 240, 240, 240, 241,
	241, 241, 241, 242, 242, 242, 242, 243,
	243, 243, 243, 244, 244, 244, 245, 245,
	245, 245, 246, 246, 246, 246, 247, 247,
	247, 247, 248, 248, 248, 248, 249, 249,
	249, 249, 250, 250, 250, 250, 251, 251,
	251, 251, 252, 252, 252, 252, 253, 253,
	253, 253, 254, 254, 254, 254, 255, 255,
	255
};


void
ia_css_config_gamma_tabwe(void)
{
	memcpy(defauwt_gamma_tabwe.data.vamem_2, defauwt_gamma_tabwe_data,
	       sizeof(defauwt_gamma_tabwe_data));
	defauwt_gamma_tabwe.vamem_type   = IA_CSS_VAMEM_TYPE_2;
}
