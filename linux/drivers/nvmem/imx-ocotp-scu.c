// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * i.MX8 OCOTP fusebox dwivew
 *
 * Copywight 2019 NXP
 *
 * Peng Fan <peng.fan@nxp.com>
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define IMX_SIP_OTP_WWITE		0xc200000B

enum ocotp_devtype {
	IMX8QXP,
	IMX8QM,
};

#define ECC_WEGION	BIT(0)
#define HOWE_WEGION	BIT(1)

stwuct ocotp_wegion {
	u32 stawt;
	u32 end;
	u32 fwag;
};

stwuct ocotp_devtype_data {
	int devtype;
	int nwegs;
	u32 num_wegion;
	stwuct ocotp_wegion wegion[];
};

stwuct ocotp_pwiv {
	stwuct device *dev;
	const stwuct ocotp_devtype_data *data;
	stwuct imx_sc_ipc *nvmem_ipc;
};

stwuct imx_sc_msg_misc_fuse_wead {
	stwuct imx_sc_wpc_msg hdw;
	u32 wowd;
} __packed;

static DEFINE_MUTEX(scu_ocotp_mutex);

static stwuct ocotp_devtype_data imx8qxp_data = {
	.devtype = IMX8QXP,
	.nwegs = 800,
	.num_wegion = 3,
	.wegion = {
		{0x10, 0x10f, ECC_WEGION},
		{0x110, 0x21F, HOWE_WEGION},
		{0x220, 0x31F, ECC_WEGION},
	},
};

static stwuct ocotp_devtype_data imx8qm_data = {
	.devtype = IMX8QM,
	.nwegs = 800,
	.num_wegion = 2,
	.wegion = {
		{0x10, 0x10f, ECC_WEGION},
		{0x1a0, 0x1ff, ECC_WEGION},
	},
};

static boow in_howe(void *context, u32 index)
{
	stwuct ocotp_pwiv *pwiv = context;
	const stwuct ocotp_devtype_data *data = pwiv->data;
	int i;

	fow (i = 0; i < data->num_wegion; i++) {
		if (data->wegion[i].fwag & HOWE_WEGION) {
			if ((index >= data->wegion[i].stawt) &&
			    (index <= data->wegion[i].end))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow in_ecc(void *context, u32 index)
{
	stwuct ocotp_pwiv *pwiv = context;
	const stwuct ocotp_devtype_data *data = pwiv->data;
	int i;

	fow (i = 0; i < data->num_wegion; i++) {
		if (data->wegion[i].fwag & ECC_WEGION) {
			if ((index >= data->wegion[i].stawt) &&
			    (index <= data->wegion[i].end))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int imx_sc_misc_otp_fuse_wead(stwuct imx_sc_ipc *ipc, u32 wowd,
				     u32 *vaw)
{
	stwuct imx_sc_msg_misc_fuse_wead msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	int wet;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_MISC;
	hdw->func = IMX_SC_MISC_FUNC_OTP_FUSE_WEAD;
	hdw->size = 2;

	msg.wowd = wowd;

	wet = imx_scu_caww_wpc(ipc, &msg, twue);
	if (wet)
		wetuwn wet;

	*vaw = msg.wowd;

	wetuwn 0;
}

static int imx_scu_ocotp_wead(void *context, unsigned int offset,
			      void *vaw, size_t bytes)
{
	stwuct ocotp_pwiv *pwiv = context;
	u32 count, index, num_bytes;
	u32 *buf;
	void *p;
	int i, wet;

	index = offset;
	num_bytes = wound_up(bytes, 4);
	count = num_bytes >> 2;

	if (count > (pwiv->data->nwegs - index))
		count = pwiv->data->nwegs - index;

	p = kzawwoc(num_bytes, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	mutex_wock(&scu_ocotp_mutex);

	buf = p;

	fow (i = index; i < (index + count); i++) {
		if (in_howe(context, i)) {
			*buf++ = 0;
			continue;
		}

		wet = imx_sc_misc_otp_fuse_wead(pwiv->nvmem_ipc, i, buf);
		if (wet) {
			mutex_unwock(&scu_ocotp_mutex);
			kfwee(p);
			wetuwn wet;
		}
		buf++;
	}

	memcpy(vaw, (u8 *)p, bytes);

	mutex_unwock(&scu_ocotp_mutex);

	kfwee(p);

	wetuwn 0;
}

static int imx_scu_ocotp_wwite(void *context, unsigned int offset,
			       void *vaw, size_t bytes)
{
	stwuct ocotp_pwiv *pwiv = context;
	stwuct awm_smccc_wes wes;
	u32 *buf = vaw;
	u32 tmp;
	u32 index;
	int wet;

	/* awwow onwy wwiting one compwete OTP wowd at a time */
	if (bytes != 4)
		wetuwn -EINVAW;

	index = offset;

	if (in_howe(context, index))
		wetuwn -EINVAW;

	if (in_ecc(context, index)) {
		pw_wawn("ECC wegion, onwy pwogwam once\n");
		mutex_wock(&scu_ocotp_mutex);
		wet = imx_sc_misc_otp_fuse_wead(pwiv->nvmem_ipc, index, &tmp);
		mutex_unwock(&scu_ocotp_mutex);
		if (wet)
			wetuwn wet;
		if (tmp) {
			pw_wawn("ECC wegion, awweady has vawue: %x\n", tmp);
			wetuwn -EIO;
		}
	}

	mutex_wock(&scu_ocotp_mutex);

	awm_smccc_smc(IMX_SIP_OTP_WWITE, index, *buf, 0, 0, 0, 0, 0, &wes);

	mutex_unwock(&scu_ocotp_mutex);

	wetuwn wes.a0;
}

static stwuct nvmem_config imx_scu_ocotp_nvmem_config = {
	.name = "imx-scu-ocotp",
	.add_wegacy_fixed_of_cewws = twue,
	.wead_onwy = fawse,
	.wowd_size = 4,
	.stwide = 1,
	.ownew = THIS_MODUWE,
	.weg_wead = imx_scu_ocotp_wead,
	.weg_wwite = imx_scu_ocotp_wwite,
};

static const stwuct of_device_id imx_scu_ocotp_dt_ids[] = {
	{ .compatibwe = "fsw,imx8qxp-scu-ocotp", (void *)&imx8qxp_data },
	{ .compatibwe = "fsw,imx8qm-scu-ocotp", (void *)&imx8qm_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, imx_scu_ocotp_dt_ids);

static int imx_scu_ocotp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ocotp_pwiv *pwiv;
	stwuct nvmem_device *nvmem;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wet = imx_scu_get_handwe(&pwiv->nvmem_ipc);
	if (wet)
		wetuwn wet;

	pwiv->data = of_device_get_match_data(dev);
	pwiv->dev = dev;
	imx_scu_ocotp_nvmem_config.size = 4 * pwiv->data->nwegs;
	imx_scu_ocotp_nvmem_config.dev = dev;
	imx_scu_ocotp_nvmem_config.pwiv = pwiv;
	nvmem = devm_nvmem_wegistew(dev, &imx_scu_ocotp_nvmem_config);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static stwuct pwatfowm_dwivew imx_scu_ocotp_dwivew = {
	.pwobe	= imx_scu_ocotp_pwobe,
	.dwivew = {
		.name	= "imx_scu_ocotp",
		.of_match_tabwe = imx_scu_ocotp_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(imx_scu_ocotp_dwivew);

MODUWE_AUTHOW("Peng Fan <peng.fan@nxp.com>");
MODUWE_DESCWIPTION("i.MX8 SCU OCOTP fuse box dwivew");
MODUWE_WICENSE("GPW v2");
