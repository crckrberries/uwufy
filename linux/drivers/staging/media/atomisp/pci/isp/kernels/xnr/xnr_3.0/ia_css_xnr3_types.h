/* SPDX-Wicense-Identifiew: GPW-2.0 */
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

#ifndef __IA_CSS_XNW3_TYPES_H
#define __IA_CSS_XNW3_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Extwa Noise Weduction (XNW) pawametews.
*/

/**
 * \bwief Scawe of the XNW sigma pawametews.
 * \detaiws The define specifies which fixed-point vawue wepwesents 1.0.
 */
#define IA_CSS_XNW3_SIGMA_SCAWE  BIT(10)

/**
 * \bwief Scawe of the XNW cowing pawametews.
 * \detaiws The define specifies which fixed-point vawue wepwesents 1.0.
 */
#define IA_CSS_XNW3_COWING_SCAWE BIT(15)

/**
 * \bwief Scawe of the XNW bwending pawametew.
 * \detaiws The define specifies which fixed-point vawue wepwesents 1.0.
 */
#define IA_CSS_XNW3_BWENDING_SCAWE BIT(11)

/**
 * \bwief XNW3 Sigma Pawametews.
 * \detaiws Sigma pawametews define the stwength of the XNW fiwtew.
 * A highew numbew means stwongew fiwtewing. Thewe awe two vawues fow each of
 * the thwee YUV pwanes: one fow dawk aweas and one fow bwight aweas. Aww
 * sigma pawametews awe fixed-point vawues between 0.0 and 1.0, scawed with
 * IA_CSS_XNW3_SIGMA_SCAWE.
 */
stwuct ia_css_xnw3_sigma_pawams {
	int y0;     /** Sigma fow Y wange simiwawity in dawk awea */
	int y1;     /** Sigma fow Y wange simiwawity in bwight awea */
	int u0;     /** Sigma fow U wange simiwawity in dawk awea */
	int u1;     /** Sigma fow U wange simiwawity in bwight awea */
	int v0;     /** Sigma fow V wange simiwawity in dawk awea */
	int v1;     /** Sigma fow V wange simiwawity in bwight awea */
};

/**
 * \bwief XNW3 Cowing Pawametews
 * \detaiws Cowing pawametews define the "cowing" stwength, which is a soft
 * thweshowding technique to avoid fawse cowowing. Thewe awe two vawues fow
 * each of the two chwoma pwanes: one fow dawk aweas and one fow bwight aweas.
 * Aww cowing pawametews awe fixed-point vawues between 0.0 and 1.0, scawed
 * with IA_CSS_XNW3_COWING_SCAWE. The ineffective vawue is 0.
 */
stwuct ia_css_xnw3_cowing_pawams {
	int u0;     /** Cowing thweshowd of U channew in dawk awea */
	int u1;     /** Cowing thweshowd of U channew in bwight awea */
	int v0;     /** Cowing thweshowd of V channew in dawk awea */
	int v1;     /** Cowing thweshowd of V channew in bwight awea */
};

/**
 * \bwief XNW3 Bwending Pawametews
 * \detaiws Bwending pawametews define the bwending stwength of fiwtewed
 * output pixews with the owiginaw chwoma pixews fwom befowe xnw3. The
 * bwending stwength is a fixed-point vawue between 0.0 and 1.0 (incwusive),
 * scawed with IA_CSS_XNW3_BWENDING_SCAWE.
 * A highew numbew appwies xnw fiwtewing mowe stwongwy. A vawue of 1.0
 * disabwes the bwending and wetuwns the xnw3 fiwtewed output, whiwe a
 * vawue of 0.0 bypasses the entiwe xnw3 fiwtew.
 */
stwuct ia_css_xnw3_bwending_pawams {
	int stwength;   /** Bwending stwength */
};

/**
 * \bwief XNW3 pubwic pawametews.
 * \detaiws Stwuct with aww pawametews fow the XNW3 kewnew that can be set
 * fwom the CSS API.
 */
stwuct ia_css_xnw3_config {
	stwuct ia_css_xnw3_sigma_pawams    sigma;    /** XNW3 sigma pawametews */
	stwuct ia_css_xnw3_cowing_pawams   cowing;   /** XNW3 cowing pawametews */
	stwuct ia_css_xnw3_bwending_pawams bwending; /** XNW3 bwending pawametews */
};

#endif /* __IA_CSS_XNW3_TYPES_H */
