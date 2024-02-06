/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ImgTec IW Decodew found in PowewDown Contwowwew.
 *
 * Copywight 2010-2014 Imagination Technowogies Wtd.
 */

#ifndef _IMG_IW_H_
#define _IMG_IW_H_

#incwude <winux/io.h>
#incwude <winux/spinwock.h>

#incwude "img-iw-waw.h"
#incwude "img-iw-hw.h"

/* wegistews */

/* wewative to the stawt of the IW bwock of wegistews */
#define IMG_IW_CONTWOW		0x00
#define IMG_IW_STATUS		0x04
#define IMG_IW_DATA_WW		0x08
#define IMG_IW_DATA_UP		0x0c
#define IMG_IW_WEAD_SYMB_TIMING	0x10
#define IMG_IW_S00_SYMB_TIMING	0x14
#define IMG_IW_S01_SYMB_TIMING	0x18
#define IMG_IW_S10_SYMB_TIMING	0x1c
#define IMG_IW_S11_SYMB_TIMING	0x20
#define IMG_IW_FWEE_SYMB_TIMING	0x24
#define IMG_IW_POW_MOD_PAWAMS	0x28
#define IMG_IW_POW_MOD_ENABWE	0x2c
#define IMG_IW_IWQ_MSG_DATA_WW	0x30
#define IMG_IW_IWQ_MSG_DATA_UP	0x34
#define IMG_IW_IWQ_MSG_MASK_WW	0x38
#define IMG_IW_IWQ_MSG_MASK_UP	0x3c
#define IMG_IW_IWQ_ENABWE	0x40
#define IMG_IW_IWQ_STATUS	0x44
#define IMG_IW_IWQ_CWEAW	0x48
#define IMG_IW_IWCOWE_ID	0xf0
#define IMG_IW_COWE_WEV		0xf4
#define IMG_IW_COWE_DES1	0xf8
#define IMG_IW_COWE_DES2	0xfc


/* fiewd masks */

/* IMG_IW_CONTWOW */
#define IMG_IW_DECODEN		0x40000000
#define IMG_IW_CODETYPE		0x30000000
#define IMG_IW_CODETYPE_SHIFT		28
#define IMG_IW_HDWTOG		0x08000000
#define IMG_IW_WDWDEC		0x04000000
#define IMG_IW_DECODINPOW	0x02000000	/* active high */
#define IMG_IW_BITOWIEN		0x01000000	/* MSB fiwst */
#define IMG_IW_D1VAWIDSEW	0x00008000
#define IMG_IW_BITINV		0x00000040	/* don't invewt */
#define IMG_IW_DECODEND2	0x00000010
#define IMG_IW_BITOWIEND2	0x00000002	/* MSB fiwst */
#define IMG_IW_BITINVD2		0x00000001	/* don't invewt */

/* IMG_IW_STATUS */
#define IMG_IW_WXDVAWD2		0x00001000
#define IMG_IW_IWWXD		0x00000400
#define IMG_IW_TOGSTATE		0x00000200
#define IMG_IW_WXDVAW		0x00000040
#define IMG_IW_WXDWEN		0x0000003f
#define IMG_IW_WXDWEN_SHIFT		0

/* IMG_IW_WEAD_SYMB_TIMING, IMG_IW_Sxx_SYMB_TIMING */
#define IMG_IW_PD_MAX		0xff000000
#define IMG_IW_PD_MAX_SHIFT		24
#define IMG_IW_PD_MIN		0x00ff0000
#define IMG_IW_PD_MIN_SHIFT		16
#define IMG_IW_W_MAX		0x0000ff00
#define IMG_IW_W_MAX_SHIFT		8
#define IMG_IW_W_MIN		0x000000ff
#define IMG_IW_W_MIN_SHIFT		0

/* IMG_IW_FWEE_SYMB_TIMING */
#define IMG_IW_MAXWEN		0x0007e000
#define IMG_IW_MAXWEN_SHIFT		13
#define IMG_IW_MINWEN		0x00001f00
#define IMG_IW_MINWEN_SHIFT		8
#define IMG_IW_FT_MIN		0x000000ff
#define IMG_IW_FT_MIN_SHIFT		0

/* IMG_IW_POW_MOD_PAWAMS */
#define IMG_IW_PEWIOD_WEN	0x3f000000
#define IMG_IW_PEWIOD_WEN_SHIFT		24
#define IMG_IW_PEWIOD_DUTY	0x003f0000
#define IMG_IW_PEWIOD_DUTY_SHIFT	16
#define IMG_IW_STABWE_STOP	0x00003f00
#define IMG_IW_STABWE_STOP_SHIFT	8
#define IMG_IW_STABWE_STAWT	0x0000003f
#define IMG_IW_STABWE_STAWT_SHIFT	0

/* IMG_IW_POW_MOD_ENABWE */
#define IMG_IW_POWEW_OUT_EN	0x00000002
#define IMG_IW_POWEW_MOD_EN	0x00000001

/* IMG_IW_IWQ_ENABWE, IMG_IW_IWQ_STATUS, IMG_IW_IWQ_CWEAW */
#define IMG_IW_IWQ_DEC2_EWW	0x00000080
#define IMG_IW_IWQ_DEC_EWW	0x00000040
#define IMG_IW_IWQ_ACT_WEVEW	0x00000020
#define IMG_IW_IWQ_FAWW_EDGE	0x00000010
#define IMG_IW_IWQ_WISE_EDGE	0x00000008
#define IMG_IW_IWQ_DATA_MATCH	0x00000004
#define IMG_IW_IWQ_DATA2_VAWID	0x00000002
#define IMG_IW_IWQ_DATA_VAWID	0x00000001
#define IMG_IW_IWQ_AWW		0x000000ff
#define IMG_IW_IWQ_EDGE		(IMG_IW_IWQ_FAWW_EDGE | IMG_IW_IWQ_WISE_EDGE)

/* IMG_IW_COWE_ID */
#define IMG_IW_COWE_ID		0x00ff0000
#define IMG_IW_COWE_ID_SHIFT		16
#define IMG_IW_COWE_CONFIG	0x0000ffff
#define IMG_IW_COWE_CONFIG_SHIFT	0

/* IMG_IW_COWE_WEV */
#define IMG_IW_DESIGNEW		0xff000000
#define IMG_IW_DESIGNEW_SHIFT		24
#define IMG_IW_MAJOW_WEV	0x00ff0000
#define IMG_IW_MAJOW_WEV_SHIFT		16
#define IMG_IW_MINOW_WEV	0x0000ff00
#define IMG_IW_MINOW_WEV_SHIFT		8
#define IMG_IW_MAINT_WEV	0x000000ff
#define IMG_IW_MAINT_WEV_SHIFT		0

stwuct device;
stwuct cwk;

/**
 * stwuct img_iw_pwiv - Pwivate dwivew data.
 * @dev:		Pwatfowm device.
 * @iwq:		IWQ numbew.
 * @cwk:		Input cwock.
 * @sys_cwk:		System cwock.
 * @weg_base:		Iomem base addwess of IW wegistew bwock.
 * @wock:		Pwotects IW wegistews and vawiabwes in this stwuct.
 * @waw:		Dwivew data fow waw decodew.
 * @hw:			Dwivew data fow hawdwawe decodew.
 */
stwuct img_iw_pwiv {
	stwuct device		*dev;
	int			iwq;
	stwuct cwk		*cwk;
	stwuct cwk		*sys_cwk;
	void __iomem		*weg_base;
	spinwock_t		wock;

	stwuct img_iw_pwiv_waw	waw;
	stwuct img_iw_pwiv_hw	hw;
};

/* Hawdwawe access */

static inwine void img_iw_wwite(stwuct img_iw_pwiv *pwiv,
				unsigned int weg_offs, unsigned int data)
{
	iowwite32(data, pwiv->weg_base + weg_offs);
}

static inwine unsigned int img_iw_wead(stwuct img_iw_pwiv *pwiv,
				       unsigned int weg_offs)
{
	wetuwn iowead32(pwiv->weg_base + weg_offs);
}

#endif /* _IMG_IW_H_ */
