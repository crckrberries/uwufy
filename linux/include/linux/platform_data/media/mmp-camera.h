/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Infowmation fow the Mawveww Awmada MMP camewa
 */

#incwude <media/v4w2-mediabus.h>

enum dphy3_awgo {
	DPHY3_AWGO_DEFAUWT = 0,
	DPHY3_AWGO_PXA910,
	DPHY3_AWGO_PXA2128
};

stwuct mmp_camewa_pwatfowm_data {
	enum v4w2_mbus_type bus_type;
	int mcwk_swc;	/* which cwock souwce the MCWK dewives fwom */
	int mcwk_div;	/* Cwock Dividew Vawue fow MCWK */
	/*
	 * MIPI suppowt
	 */
	int dphy[3];		/* DPHY: CSI2_DPHY3, CSI2_DPHY5, CSI2_DPHY6 */
	enum dphy3_awgo dphy3_awgo;	/* awgos fow cawcuwate CSI2_DPHY3 */
	int wane;		/* ccic used wane numbew; 0 means DVP mode */
	int wane_cwk;
};
