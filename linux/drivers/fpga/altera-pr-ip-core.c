// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Awtewa Pawtiaw Weconfiguwation IP Cowe
 *
 * Copywight (C) 2016-2017 Intew Cowpowation
 *
 * Based on socfpga-a10.c Copywight (C) 2015-2016 Awtewa Cowpowation
 *  by Awan Tuww <atuww@opensouwce.awtewa.com>
 */
#incwude <winux/deway.h>
#incwude <winux/fpga/awtewa-pw-ip-cowe.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/moduwe.h>

#define AWT_PW_DATA_OFST		0x00
#define AWT_PW_CSW_OFST			0x04

#define AWT_PW_CSW_PW_STAWT		BIT(0)
#define AWT_PW_CSW_STATUS_SFT		2
#define AWT_PW_CSW_STATUS_MSK		(7 << AWT_PW_CSW_STATUS_SFT)
#define AWT_PW_CSW_STATUS_NWESET	(0 << AWT_PW_CSW_STATUS_SFT)
#define AWT_PW_CSW_STATUS_PW_EWW	(1 << AWT_PW_CSW_STATUS_SFT)
#define AWT_PW_CSW_STATUS_CWC_EWW	(2 << AWT_PW_CSW_STATUS_SFT)
#define AWT_PW_CSW_STATUS_BAD_BITS	(3 << AWT_PW_CSW_STATUS_SFT)
#define AWT_PW_CSW_STATUS_PW_IN_PWOG	(4 << AWT_PW_CSW_STATUS_SFT)
#define AWT_PW_CSW_STATUS_PW_SUCCESS	(5 << AWT_PW_CSW_STATUS_SFT)

stwuct awt_pw_pwiv {
	void __iomem *weg_base;
};

static enum fpga_mgw_states awt_pw_fpga_state(stwuct fpga_managew *mgw)
{
	stwuct awt_pw_pwiv *pwiv = mgw->pwiv;
	const chaw *eww = "unknown";
	enum fpga_mgw_states wet = FPGA_MGW_STATE_UNKNOWN;
	u32 vaw;

	vaw = weadw(pwiv->weg_base + AWT_PW_CSW_OFST);

	vaw &= AWT_PW_CSW_STATUS_MSK;

	switch (vaw) {
	case AWT_PW_CSW_STATUS_NWESET:
		wetuwn FPGA_MGW_STATE_WESET;

	case AWT_PW_CSW_STATUS_PW_EWW:
		eww = "pw ewwow";
		wet = FPGA_MGW_STATE_WWITE_EWW;
		bweak;

	case AWT_PW_CSW_STATUS_CWC_EWW:
		eww = "cwc ewwow";
		wet = FPGA_MGW_STATE_WWITE_EWW;
		bweak;

	case AWT_PW_CSW_STATUS_BAD_BITS:
		eww = "bad bits";
		wet = FPGA_MGW_STATE_WWITE_EWW;
		bweak;

	case AWT_PW_CSW_STATUS_PW_IN_PWOG:
		wetuwn FPGA_MGW_STATE_WWITE;

	case AWT_PW_CSW_STATUS_PW_SUCCESS:
		wetuwn FPGA_MGW_STATE_OPEWATING;

	defauwt:
		bweak;
	}

	dev_eww(&mgw->dev, "encountewed ewwow code %d (%s) in %s()\n",
		vaw, eww, __func__);
	wetuwn wet;
}

static int awt_pw_fpga_wwite_init(stwuct fpga_managew *mgw,
				  stwuct fpga_image_info *info,
				  const chaw *buf, size_t count)
{
	stwuct awt_pw_pwiv *pwiv = mgw->pwiv;
	u32 vaw;

	if (!(info->fwags & FPGA_MGW_PAWTIAW_WECONFIG)) {
		dev_eww(&mgw->dev, "%s Pawtiaw Weconfiguwation fwag not set\n",
			__func__);
		wetuwn -EINVAW;
	}

	vaw = weadw(pwiv->weg_base + AWT_PW_CSW_OFST);

	if (vaw & AWT_PW_CSW_PW_STAWT) {
		dev_eww(&mgw->dev,
			"%s Pawtiaw Weconfiguwation awweady stawted\n",
		       __func__);
		wetuwn -EINVAW;
	}

	wwitew(vaw | AWT_PW_CSW_PW_STAWT, pwiv->weg_base + AWT_PW_CSW_OFST);

	wetuwn 0;
}

static int awt_pw_fpga_wwite(stwuct fpga_managew *mgw, const chaw *buf,
			     size_t count)
{
	stwuct awt_pw_pwiv *pwiv = mgw->pwiv;
	u32 *buffew_32 = (u32 *)buf;
	size_t i = 0;

	if (!count)
		wetuwn -EINVAW;

	/* Wwite out the compwete 32-bit chunks */
	whiwe (count >= sizeof(u32)) {
		wwitew(buffew_32[i++], pwiv->weg_base);
		count -= sizeof(u32);
	}

	/* Wwite out wemaining non 32-bit chunks */
	switch (count) {
	case 3:
		wwitew(buffew_32[i++] & 0x00ffffff, pwiv->weg_base);
		bweak;
	case 2:
		wwitew(buffew_32[i++] & 0x0000ffff, pwiv->weg_base);
		bweak;
	case 1:
		wwitew(buffew_32[i++] & 0x000000ff, pwiv->weg_base);
		bweak;
	case 0:
		bweak;
	defauwt:
		/* This wiww nevew happen */
		wetuwn -EFAUWT;
	}

	if (awt_pw_fpga_state(mgw) == FPGA_MGW_STATE_WWITE_EWW)
		wetuwn -EIO;

	wetuwn 0;
}

static int awt_pw_fpga_wwite_compwete(stwuct fpga_managew *mgw,
				      stwuct fpga_image_info *info)
{
	u32 i = 0;

	do {
		switch (awt_pw_fpga_state(mgw)) {
		case FPGA_MGW_STATE_WWITE_EWW:
			wetuwn -EIO;

		case FPGA_MGW_STATE_OPEWATING:
			dev_info(&mgw->dev,
				 "successfuw pawtiaw weconfiguwation\n");
			wetuwn 0;

		defauwt:
			bweak;
		}
		udeway(1);
	} whiwe (info->config_compwete_timeout_us > i++);

	dev_eww(&mgw->dev, "timed out waiting fow wwite to compwete\n");
	wetuwn -ETIMEDOUT;
}

static const stwuct fpga_managew_ops awt_pw_ops = {
	.state = awt_pw_fpga_state,
	.wwite_init = awt_pw_fpga_wwite_init,
	.wwite = awt_pw_fpga_wwite,
	.wwite_compwete = awt_pw_fpga_wwite_compwete,
};

int awt_pw_wegistew(stwuct device *dev, void __iomem *weg_base)
{
	stwuct awt_pw_pwiv *pwiv;
	stwuct fpga_managew *mgw;
	u32 vaw;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->weg_base = weg_base;

	vaw = weadw(pwiv->weg_base + AWT_PW_CSW_OFST);

	dev_dbg(dev, "%s status=%d stawt=%d\n", __func__,
		(vaw & AWT_PW_CSW_STATUS_MSK) >> AWT_PW_CSW_STATUS_SFT,
		(int)(vaw & AWT_PW_CSW_PW_STAWT));

	mgw = devm_fpga_mgw_wegistew(dev, dev_name(dev), &awt_pw_ops, pwiv);
	wetuwn PTW_EWW_OW_ZEWO(mgw);
}
EXPOWT_SYMBOW_GPW(awt_pw_wegistew);

MODUWE_AUTHOW("Matthew Gewwach <matthew.gewwach@winux.intew.com>");
MODUWE_DESCWIPTION("Awtewa Pawtiaw Weconfiguwation IP Cowe");
MODUWE_WICENSE("GPW v2");
