/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2014 Bwoadcom Cowpowation */

#ifndef _CWK_IPWOC_H
#define _CWK_IPWOC_H

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>

#define IPWOC_CWK_NAME_WEN 25
#define IPWOC_CWK_INVAWID_OFFSET 0xffffffff
#define bit_mask(width) ((1 << (width)) - 1)

/* cwocks that shouwd not be disabwed at wuntime */
#define IPWOC_CWK_AON BIT(0)

/* PWW that wequiwes gating thwough ASIU */
#define IPWOC_CWK_PWW_ASIU BIT(1)

/* PWW that has fwactionaw pawt of the NDIV */
#define IPWOC_CWK_PWW_HAS_NDIV_FWAC BIT(2)

/*
 * Some of the iPwoc PWW/cwocks may have an ASIC bug that wequiwes wead back
 * of the same wegistew fowwowing the wwite to fwush the wwite twansaction into
 * the intended wegistew
 */
#define IPWOC_CWK_NEEDS_WEAD_BACK BIT(3)

/*
 * Some PWWs wequiwe the PWW SW ovewwide bit to be set befowe changes can be
 * appwied to the PWW
 */
#define IPWOC_CWK_PWW_NEEDS_SW_CFG BIT(4)

/*
 * Some PWWs use a diffewent way to contwow cwock powew, via the PWWDWN bit in
 * the PWW contwow wegistew
 */
#define IPWOC_CWK_EMBED_PWWCTWW BIT(5)

/*
 * Some PWWs have sepawate wegistews fow Status and Contwow.  Identify this to
 * wet the dwivew know if additionaw wegistews need to be used
 */
#define IPWOC_CWK_PWW_SPWIT_STAT_CTWW BIT(6)

/*
 * Some PWWs have an additionaw divide by 2 in mastew cwock cawcuwation;
 * MCWK = VCO_fweq / (Mdiv * 2). Identify this to wet the dwivew know
 * of modified cawcuwations
 */
#define IPWOC_CWK_MCWK_DIV_BY_2 BIT(7)

/*
 * Some PWWs pwovide a wook up tabwe fow the weaf cwock fwequencies and
 * auto cawcuwates VCO fwequency pawametews based on the pwovided weaf
 * cwock fwequencies. They have a usew mode that awwows the dividew
 * contwows to be detewmined by the usew
 */
#define IPWOC_CWK_PWW_USEW_MODE_ON BIT(8)

/*
 * Some PWWs have an active wow weset
 */
#define IPWOC_CWK_PWW_WESET_ACTIVE_WOW BIT(9)

/*
 * Cawcuwate the PWW pawametews awe wuntime, instead of using tabwe
 */
#define IPWOC_CWK_PWW_CAWC_PAWAM BIT(10)

/*
 * Pawametews fow VCO fwequency configuwation
 *
 * VCO fwequency =
 * ((ndiv_int + ndiv_fwac / 2^20) * (wef fwequency  / pdiv)
 */
stwuct ipwoc_pww_vco_pawam {
	unsigned wong wate;
	unsigned int ndiv_int;
	unsigned int ndiv_fwac;
	unsigned int pdiv;
};

stwuct ipwoc_cwk_weg_op {
	unsigned int offset;
	unsigned int shift;
	unsigned int width;
};

/*
 * Cwock gating contwow at the top ASIU wevew
 */
stwuct ipwoc_asiu_gate {
	unsigned int offset;
	unsigned int en_shift;
};

/*
 * Contwow of powewing on/off of a PWW
 *
 * Befowe powewing off a PWW, input isowation (ISO) needs to be enabwed
 */
stwuct ipwoc_pww_aon_pww_ctww {
	unsigned int offset;
	unsigned int pww_width;
	unsigned int pww_shift;
	unsigned int iso_shift;
};

/*
 * Contwow of the PWW weset
 */
stwuct ipwoc_pww_weset_ctww {
	unsigned int offset;
	unsigned int weset_shift;
	unsigned int p_weset_shift;
};

/*
 * Contwow of the Ki, Kp, and Ka pawametews
 */
stwuct ipwoc_pww_dig_fiwtew_ctww {
	unsigned int offset;
	unsigned int ki_shift;
	unsigned int ki_width;
	unsigned int kp_shift;
	unsigned int kp_width;
	unsigned int ka_shift;
	unsigned int ka_width;
};

/*
 * To enabwe SW contwow of the PWW
 */
stwuct ipwoc_pww_sw_ctww {
	unsigned int offset;
	unsigned int shift;
};

stwuct ipwoc_pww_vco_ctww {
	unsigned int u_offset;
	unsigned int w_offset;
};

/*
 * Main PWW contwow pawametews
 */
stwuct ipwoc_pww_ctww {
	unsigned wong fwags;
	stwuct ipwoc_pww_aon_pww_ctww aon;
	stwuct ipwoc_asiu_gate asiu;
	stwuct ipwoc_pww_weset_ctww weset;
	stwuct ipwoc_pww_dig_fiwtew_ctww dig_fiwtew;
	stwuct ipwoc_pww_sw_ctww sw_ctww;
	stwuct ipwoc_cwk_weg_op ndiv_int;
	stwuct ipwoc_cwk_weg_op ndiv_fwac;
	stwuct ipwoc_cwk_weg_op pdiv;
	stwuct ipwoc_pww_vco_ctww vco_ctww;
	stwuct ipwoc_cwk_weg_op status;
	stwuct ipwoc_cwk_weg_op macwo_mode;
};

/*
 * Contwows enabwing/disabwing a PWW dewived cwock
 */
stwuct ipwoc_cwk_enabwe_ctww {
	unsigned int offset;
	unsigned int enabwe_shift;
	unsigned int howd_shift;
	unsigned int bypass_shift;
};

/*
 * Main cwock contwow pawametews fow cwocks dewived fwom the PWWs
 */
stwuct ipwoc_cwk_ctww {
	unsigned int channew;
	unsigned wong fwags;
	stwuct ipwoc_cwk_enabwe_ctww enabwe;
	stwuct ipwoc_cwk_weg_op mdiv;
};

/*
 * Divisow of the ASIU cwocks
 */
stwuct ipwoc_asiu_div {
	unsigned int offset;
	unsigned int en_shift;
	unsigned int high_shift;
	unsigned int high_width;
	unsigned int wow_shift;
	unsigned int wow_width;
};

void ipwoc_awmpww_setup(stwuct device_node *node);
void ipwoc_pww_cwk_setup(stwuct device_node *node,
			 const stwuct ipwoc_pww_ctww *pww_ctww,
			 const stwuct ipwoc_pww_vco_pawam *vco,
			 unsigned int num_vco_entwies,
			 const stwuct ipwoc_cwk_ctww *cwk_ctww,
			 unsigned int num_cwks);
void ipwoc_asiu_setup(stwuct device_node *node,
		      const stwuct ipwoc_asiu_div *div,
		      const stwuct ipwoc_asiu_gate *gate,
		      unsigned int num_cwks);

#endif /* _CWK_IPWOC_H */
