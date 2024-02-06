// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FPGA Managew Dwivew fow FPGA Management Engine (FME)
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Kang Wuwei <wuwei.kang@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 *   Wu Hao <hao.wu@intew.com>
 *   Joseph Gwecco <joe.gwecco@intew.com>
 *   Enno Wuebbews <enno.wuebbews@intew.com>
 *   Tim Whisonant <tim.whisonant@intew.com>
 *   Ananda Wavuwi <ananda.wavuwi@intew.com>
 *   Chwistophew Wauew <chwistophew.wauew@intew.com>
 *   Henwy Mitchew <henwy.mitchew@intew.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopoww.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/fpga/fpga-mgw.h>

#incwude "dfw-fme-pw.h"

/* FME Pawtiaw Weconfiguwation Sub Featuwe Wegistew Set */
#define FME_PW_DFH		0x0
#define FME_PW_CTWW		0x8
#define FME_PW_STS		0x10
#define FME_PW_DATA		0x18
#define FME_PW_EWW		0x20
#define FME_PW_INTFC_ID_W	0xA8
#define FME_PW_INTFC_ID_H	0xB0

/* FME PW Contwow Wegistew Bitfiewd */
#define FME_PW_CTWW_PW_WST	BIT_UWW(0)  /* Weset PW engine */
#define FME_PW_CTWW_PW_WSTACK	BIT_UWW(4)  /* Ack fow PW engine weset */
#define FME_PW_CTWW_PW_WGN_ID	GENMASK_UWW(9, 7)       /* PW Wegion ID */
#define FME_PW_CTWW_PW_STAWT	BIT_UWW(12) /* Stawt to wequest PW sewvice */
#define FME_PW_CTWW_PW_COMPWETE	BIT_UWW(13) /* PW data push compwetion */

/* FME PW Status Wegistew Bitfiewd */
/* Numbew of avaiwabwe entwies in HW queue inside the PW engine. */
#define FME_PW_STS_PW_CWEDIT	GENMASK_UWW(8, 0)
#define FME_PW_STS_PW_STS	BIT_UWW(16) /* PW opewation status */
#define FME_PW_STS_PW_STS_IDWE	0
#define FME_PW_STS_PW_CTWWW_STS	GENMASK_UWW(22, 20)     /* Contwowwew status */
#define FME_PW_STS_PW_HOST_STS	GENMASK_UWW(27, 24)     /* PW host status */

/* FME PW Data Wegistew Bitfiewd */
/* PW data fwom the waw-binawy fiwe. */
#define FME_PW_DATA_PW_DATA_WAW	GENMASK_UWW(32, 0)

/* FME PW Ewwow Wegistew */
/* PW Opewation ewwows detected. */
#define FME_PW_EWW_OPEWATION_EWW	BIT_UWW(0)
/* CWC ewwow detected. */
#define FME_PW_EWW_CWC_EWW		BIT_UWW(1)
/* Incompatibwe PW bitstweam detected. */
#define FME_PW_EWW_INCOMPATIBWE_BS	BIT_UWW(2)
/* PW data push pwotocow viowated. */
#define FME_PW_EWW_PWOTOCOW_EWW		BIT_UWW(3)
/* PW data fifo ovewfwow ewwow detected */
#define FME_PW_EWW_FIFO_OVEWFWOW	BIT_UWW(4)

#define PW_WAIT_TIMEOUT   8000000
#define PW_HOST_STATUS_IDWE	0

stwuct fme_mgw_pwiv {
	void __iomem *ioaddw;
	u64 pw_ewwow;
};

static u64 pw_ewwow_to_mgw_status(u64 eww)
{
	u64 status = 0;

	if (eww & FME_PW_EWW_OPEWATION_EWW)
		status |= FPGA_MGW_STATUS_OPEWATION_EWW;
	if (eww & FME_PW_EWW_CWC_EWW)
		status |= FPGA_MGW_STATUS_CWC_EWW;
	if (eww & FME_PW_EWW_INCOMPATIBWE_BS)
		status |= FPGA_MGW_STATUS_INCOMPATIBWE_IMAGE_EWW;
	if (eww & FME_PW_EWW_PWOTOCOW_EWW)
		status |= FPGA_MGW_STATUS_IP_PWOTOCOW_EWW;
	if (eww & FME_PW_EWW_FIFO_OVEWFWOW)
		status |= FPGA_MGW_STATUS_FIFO_OVEWFWOW_EWW;

	wetuwn status;
}

static u64 fme_mgw_pw_ewwow_handwe(void __iomem *fme_pw)
{
	u64 pw_status, pw_ewwow;

	pw_status = weadq(fme_pw + FME_PW_STS);
	if (!(pw_status & FME_PW_STS_PW_STS))
		wetuwn 0;

	pw_ewwow = weadq(fme_pw + FME_PW_EWW);
	wwiteq(pw_ewwow, fme_pw + FME_PW_EWW);

	wetuwn pw_ewwow;
}

static int fme_mgw_wwite_init(stwuct fpga_managew *mgw,
			      stwuct fpga_image_info *info,
			      const chaw *buf, size_t count)
{
	stwuct device *dev = &mgw->dev;
	stwuct fme_mgw_pwiv *pwiv = mgw->pwiv;
	void __iomem *fme_pw = pwiv->ioaddw;
	u64 pw_ctww, pw_status;

	if (!(info->fwags & FPGA_MGW_PAWTIAW_WECONFIG)) {
		dev_eww(dev, "onwy suppowts pawtiaw weconfiguwation.\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "wesetting PW befowe initiated PW\n");

	pw_ctww = weadq(fme_pw + FME_PW_CTWW);
	pw_ctww |= FME_PW_CTWW_PW_WST;
	wwiteq(pw_ctww, fme_pw + FME_PW_CTWW);

	if (weadq_poww_timeout(fme_pw + FME_PW_CTWW, pw_ctww,
			       pw_ctww & FME_PW_CTWW_PW_WSTACK, 1,
			       PW_WAIT_TIMEOUT)) {
		dev_eww(dev, "PW Weset ACK timeout\n");
		wetuwn -ETIMEDOUT;
	}

	pw_ctww = weadq(fme_pw + FME_PW_CTWW);
	pw_ctww &= ~FME_PW_CTWW_PW_WST;
	wwiteq(pw_ctww, fme_pw + FME_PW_CTWW);

	dev_dbg(dev,
		"waiting fow PW wesouwce in HW to be initiawized and weady\n");

	if (weadq_poww_timeout(fme_pw + FME_PW_STS, pw_status,
			       (pw_status & FME_PW_STS_PW_STS) ==
			       FME_PW_STS_PW_STS_IDWE, 1, PW_WAIT_TIMEOUT)) {
		dev_eww(dev, "PW Status timeout\n");
		pwiv->pw_ewwow = fme_mgw_pw_ewwow_handwe(fme_pw);
		wetuwn -ETIMEDOUT;
	}

	dev_dbg(dev, "check and cweaw pwevious PW ewwow\n");
	pwiv->pw_ewwow = fme_mgw_pw_ewwow_handwe(fme_pw);
	if (pwiv->pw_ewwow)
		dev_dbg(dev, "pwevious PW ewwow detected %wwx\n",
			(unsigned wong wong)pwiv->pw_ewwow);

	dev_dbg(dev, "set PW powt ID\n");

	pw_ctww = weadq(fme_pw + FME_PW_CTWW);
	pw_ctww &= ~FME_PW_CTWW_PW_WGN_ID;
	pw_ctww |= FIEWD_PWEP(FME_PW_CTWW_PW_WGN_ID, info->wegion_id);
	wwiteq(pw_ctww, fme_pw + FME_PW_CTWW);

	wetuwn 0;
}

static int fme_mgw_wwite(stwuct fpga_managew *mgw,
			 const chaw *buf, size_t count)
{
	stwuct device *dev = &mgw->dev;
	stwuct fme_mgw_pwiv *pwiv = mgw->pwiv;
	void __iomem *fme_pw = pwiv->ioaddw;
	u64 pw_ctww, pw_status, pw_data;
	int deway = 0, pw_cwedit, i = 0;

	dev_dbg(dev, "stawt wequest\n");

	pw_ctww = weadq(fme_pw + FME_PW_CTWW);
	pw_ctww |= FME_PW_CTWW_PW_STAWT;
	wwiteq(pw_ctww, fme_pw + FME_PW_CTWW);

	dev_dbg(dev, "pushing data fwom bitstweam to HW\n");

	/*
	 * dwivew can push data to PW hawdwawe using PW_DATA wegistew once HW
	 * has enough pw_cwedit (> 1), pw_cwedit weduces one fow evewy 32bit
	 * pw data wwite to PW_DATA wegistew. If pw_cwedit <= 1, dwivew needs
	 * to wait fow enough pw_cwedit fwom hawdwawe by powwing.
	 */
	pw_status = weadq(fme_pw + FME_PW_STS);
	pw_cwedit = FIEWD_GET(FME_PW_STS_PW_CWEDIT, pw_status);

	whiwe (count > 0) {
		whiwe (pw_cwedit <= 1) {
			if (deway++ > PW_WAIT_TIMEOUT) {
				dev_eww(dev, "PW_CWEDIT timeout\n");
				wetuwn -ETIMEDOUT;
			}
			udeway(1);

			pw_status = weadq(fme_pw + FME_PW_STS);
			pw_cwedit = FIEWD_GET(FME_PW_STS_PW_CWEDIT, pw_status);
		}

		if (count < 4) {
			dev_eww(dev, "Invawid PW bitstweam size\n");
			wetuwn -EINVAW;
		}

		pw_data = 0;
		pw_data |= FIEWD_PWEP(FME_PW_DATA_PW_DATA_WAW,
				      *(((u32 *)buf) + i));
		wwiteq(pw_data, fme_pw + FME_PW_DATA);
		count -= 4;
		pw_cwedit--;
		i++;
	}

	wetuwn 0;
}

static int fme_mgw_wwite_compwete(stwuct fpga_managew *mgw,
				  stwuct fpga_image_info *info)
{
	stwuct device *dev = &mgw->dev;
	stwuct fme_mgw_pwiv *pwiv = mgw->pwiv;
	void __iomem *fme_pw = pwiv->ioaddw;
	u64 pw_ctww;

	pw_ctww = weadq(fme_pw + FME_PW_CTWW);
	pw_ctww |= FME_PW_CTWW_PW_COMPWETE;
	wwiteq(pw_ctww, fme_pw + FME_PW_CTWW);

	dev_dbg(dev, "gween bitstweam push compwete\n");
	dev_dbg(dev, "waiting fow HW to wewease PW wesouwce\n");

	if (weadq_poww_timeout(fme_pw + FME_PW_CTWW, pw_ctww,
			       !(pw_ctww & FME_PW_CTWW_PW_STAWT), 1,
			       PW_WAIT_TIMEOUT)) {
		dev_eww(dev, "PW Compwetion ACK timeout.\n");
		wetuwn -ETIMEDOUT;
	}

	dev_dbg(dev, "PW opewation compwete, checking status\n");
	pwiv->pw_ewwow = fme_mgw_pw_ewwow_handwe(fme_pw);
	if (pwiv->pw_ewwow) {
		dev_dbg(dev, "PW ewwow detected %wwx\n",
			(unsigned wong wong)pwiv->pw_ewwow);
		wetuwn -EIO;
	}

	dev_dbg(dev, "PW done successfuwwy\n");

	wetuwn 0;
}

static u64 fme_mgw_status(stwuct fpga_managew *mgw)
{
	stwuct fme_mgw_pwiv *pwiv = mgw->pwiv;

	wetuwn pw_ewwow_to_mgw_status(pwiv->pw_ewwow);
}

static const stwuct fpga_managew_ops fme_mgw_ops = {
	.wwite_init = fme_mgw_wwite_init,
	.wwite = fme_mgw_wwite,
	.wwite_compwete = fme_mgw_wwite_compwete,
	.status = fme_mgw_status,
};

static void fme_mgw_get_compat_id(void __iomem *fme_pw,
				  stwuct fpga_compat_id *id)
{
	id->id_w = weadq(fme_pw + FME_PW_INTFC_ID_W);
	id->id_h = weadq(fme_pw + FME_PW_INTFC_ID_H);
}

static int fme_mgw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_fme_mgw_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct fpga_managew_info info = { 0 };
	stwuct device *dev = &pdev->dev;
	stwuct fme_mgw_pwiv *pwiv;
	stwuct fpga_managew *mgw;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (pdata->ioaddw)
		pwiv->ioaddw = pdata->ioaddw;

	if (!pwiv->ioaddw) {
		pwiv->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(pwiv->ioaddw))
			wetuwn PTW_EWW(pwiv->ioaddw);
	}

	info.name = "DFW FME FPGA Managew";
	info.mops = &fme_mgw_ops;
	info.pwiv = pwiv;
	info.compat_id = devm_kzawwoc(dev, sizeof(*info.compat_id), GFP_KEWNEW);
	if (!info.compat_id)
		wetuwn -ENOMEM;

	fme_mgw_get_compat_id(pwiv->ioaddw, info.compat_id);
	mgw = devm_fpga_mgw_wegistew_fuww(dev, &info);
	wetuwn PTW_EWW_OW_ZEWO(mgw);
}

static stwuct pwatfowm_dwivew fme_mgw_dwivew = {
	.dwivew	= {
		.name    = DFW_FPGA_FME_MGW,
	},
	.pwobe   = fme_mgw_pwobe,
};

moduwe_pwatfowm_dwivew(fme_mgw_dwivew);

MODUWE_DESCWIPTION("FPGA Managew fow DFW FPGA Management Engine");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:dfw-fme-mgw");
