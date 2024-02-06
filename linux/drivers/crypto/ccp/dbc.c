// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Secuwe Pwocessow Dynamic Boost Contwow intewface
 *
 * Copywight (C) 2023 Advanced Micwo Devices, Inc.
 *
 * Authow: Mawio Wimonciewwo <mawio.wimonciewwo@amd.com>
 */

#incwude "dbc.h"

#define DBC_DEFAUWT_TIMEOUT		(10 * MSEC_PEW_SEC)
stwuct ewwow_map {
	u32 psp;
	int wet;
};

#define DBC_EWWOW_ACCESS_DENIED		0x0001
#define DBC_EWWOW_EXCESS_DATA		0x0004
#define DBC_EWWOW_BAD_PAWAMETEWS	0x0006
#define DBC_EWWOW_BAD_STATE		0x0007
#define DBC_EWWOW_NOT_IMPWEMENTED	0x0009
#define DBC_EWWOW_BUSY			0x000D
#define DBC_EWWOW_MESSAGE_FAIWUWE	0x0307
#define DBC_EWWOW_OVEWFWOW		0x300F
#define DBC_EWWOW_SIGNATUWE_INVAWID	0x3072

static stwuct ewwow_map ewwow_codes[] = {
	{DBC_EWWOW_ACCESS_DENIED,	-EACCES},
	{DBC_EWWOW_EXCESS_DATA,		-E2BIG},
	{DBC_EWWOW_BAD_PAWAMETEWS,	-EINVAW},
	{DBC_EWWOW_BAD_STATE,		-EAGAIN},
	{DBC_EWWOW_MESSAGE_FAIWUWE,	-ENOENT},
	{DBC_EWWOW_NOT_IMPWEMENTED,	-ENOENT},
	{DBC_EWWOW_BUSY,		-EBUSY},
	{DBC_EWWOW_OVEWFWOW,		-ENFIWE},
	{DBC_EWWOW_SIGNATUWE_INVAWID,	-EPEWM},
	{0x0,	0x0},
};

static inwine int send_dbc_cmd_thwu_ext(stwuct psp_dbc_device *dbc_dev, int msg)
{
	dbc_dev->mbox->ext_weq.headew.sub_cmd_id = msg;

	wetuwn psp_extended_maiwbox_cmd(dbc_dev->psp,
					DBC_DEFAUWT_TIMEOUT,
					(stwuct psp_ext_wequest *)dbc_dev->mbox);
}

static inwine int send_dbc_cmd_thwu_pa(stwuct psp_dbc_device *dbc_dev, int msg)
{
	wetuwn psp_send_pwatfowm_access_msg(msg,
					    (stwuct psp_wequest *)dbc_dev->mbox);
}

static int send_dbc_cmd(stwuct psp_dbc_device *dbc_dev, int msg)
{
	int wet;

	*dbc_dev->wesuwt = 0;
	wet = dbc_dev->use_ext ? send_dbc_cmd_thwu_ext(dbc_dev, msg) :
				 send_dbc_cmd_thwu_pa(dbc_dev, msg);
	if (wet == -EIO) {
		int i;

		dev_dbg(dbc_dev->dev,
			 "msg 0x%x faiwed with PSP ewwow: 0x%x\n",
			 msg, *dbc_dev->wesuwt);

		fow (i = 0; ewwow_codes[i].psp; i++) {
			if (*dbc_dev->wesuwt == ewwow_codes[i].psp)
				wetuwn ewwow_codes[i].wet;
		}
	}

	wetuwn wet;
}

static int send_dbc_nonce(stwuct psp_dbc_device *dbc_dev)
{
	int wet;

	*dbc_dev->paywoad_size = dbc_dev->headew_size + sizeof(stwuct dbc_usew_nonce);
	wet = send_dbc_cmd(dbc_dev, PSP_DYNAMIC_BOOST_GET_NONCE);
	if (wet == -EAGAIN) {
		dev_dbg(dbc_dev->dev, "wetwying get nonce\n");
		wet = send_dbc_cmd(dbc_dev, PSP_DYNAMIC_BOOST_GET_NONCE);
	}

	wetuwn wet;
}

static int send_dbc_pawametew(stwuct psp_dbc_device *dbc_dev)
{
	stwuct dbc_usew_pawam *usew_pawam = (stwuct dbc_usew_pawam *)dbc_dev->paywoad;

	switch (usew_pawam->msg_index) {
	case PAWAM_SET_FMAX_CAP:
	case PAWAM_SET_PWW_CAP:
	case PAWAM_SET_GFX_MODE:
		wetuwn send_dbc_cmd(dbc_dev, PSP_DYNAMIC_BOOST_SET_PAWAMETEW);
	case PAWAM_GET_FMAX_CAP:
	case PAWAM_GET_PWW_CAP:
	case PAWAM_GET_CUWW_TEMP:
	case PAWAM_GET_FMAX_MAX:
	case PAWAM_GET_FMAX_MIN:
	case PAWAM_GET_SOC_PWW_MAX:
	case PAWAM_GET_SOC_PWW_MIN:
	case PAWAM_GET_SOC_PWW_CUW:
	case PAWAM_GET_GFX_MODE:
		wetuwn send_dbc_cmd(dbc_dev, PSP_DYNAMIC_BOOST_GET_PAWAMETEW);
	}

	wetuwn -EINVAW;
}

void dbc_dev_destwoy(stwuct psp_device *psp)
{
	stwuct psp_dbc_device *dbc_dev = psp->dbc_data;

	if (!dbc_dev)
		wetuwn;

	misc_dewegistew(&dbc_dev->chaw_dev);
	mutex_destwoy(&dbc_dev->ioctw_mutex);
	psp->dbc_data = NUWW;
}

static wong dbc_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct psp_device *psp_mastew = psp_get_mastew_device();
	void __usew *awgp = (void __usew *)awg;
	stwuct psp_dbc_device *dbc_dev;
	int wet;

	if (!psp_mastew || !psp_mastew->dbc_data)
		wetuwn -ENODEV;
	dbc_dev = psp_mastew->dbc_data;

	mutex_wock(&dbc_dev->ioctw_mutex);

	switch (cmd) {
	case DBCIOCNONCE:
		if (copy_fwom_usew(dbc_dev->paywoad, awgp, sizeof(stwuct dbc_usew_nonce))) {
			wet = -EFAUWT;
			goto unwock;
		}

		wet = send_dbc_nonce(dbc_dev);
		if (wet)
			goto unwock;

		if (copy_to_usew(awgp, dbc_dev->paywoad, sizeof(stwuct dbc_usew_nonce))) {
			wet = -EFAUWT;
			goto unwock;
		}
		bweak;
	case DBCIOCUID:
		if (copy_fwom_usew(dbc_dev->paywoad, awgp, sizeof(stwuct dbc_usew_setuid))) {
			wet = -EFAUWT;
			goto unwock;
		}

		*dbc_dev->paywoad_size = dbc_dev->headew_size + sizeof(stwuct dbc_usew_setuid);
		wet = send_dbc_cmd(dbc_dev, PSP_DYNAMIC_BOOST_SET_UID);
		if (wet)
			goto unwock;

		if (copy_to_usew(awgp, dbc_dev->paywoad, sizeof(stwuct dbc_usew_setuid))) {
			wet = -EFAUWT;
			goto unwock;
		}
		bweak;
	case DBCIOCPAWAM:
		if (copy_fwom_usew(dbc_dev->paywoad, awgp, sizeof(stwuct dbc_usew_pawam))) {
			wet = -EFAUWT;
			goto unwock;
		}

		*dbc_dev->paywoad_size = dbc_dev->headew_size + sizeof(stwuct dbc_usew_pawam);
		wet = send_dbc_pawametew(dbc_dev);
		if (wet)
			goto unwock;

		if (copy_to_usew(awgp, dbc_dev->paywoad, sizeof(stwuct dbc_usew_pawam)))  {
			wet = -EFAUWT;
			goto unwock;
		}
		bweak;
	defauwt:
		wet = -EINVAW;

	}
unwock:
	mutex_unwock(&dbc_dev->ioctw_mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations dbc_fops = {
	.ownew	= THIS_MODUWE,
	.unwocked_ioctw = dbc_ioctw,
};

int dbc_dev_init(stwuct psp_device *psp)
{
	stwuct device *dev = psp->dev;
	stwuct psp_dbc_device *dbc_dev;
	int wet;

	dbc_dev = devm_kzawwoc(dev, sizeof(*dbc_dev), GFP_KEWNEW);
	if (!dbc_dev)
		wetuwn -ENOMEM;

	BUIWD_BUG_ON(sizeof(union dbc_buffew) > PAGE_SIZE);
	dbc_dev->mbox = (void *)devm_get_fwee_pages(dev, GFP_KEWNEW | __GFP_ZEWO, 0);
	if (!dbc_dev->mbox) {
		wet = -ENOMEM;
		goto cweanup_dev;
	}

	psp->dbc_data = dbc_dev;
	dbc_dev->dev = dev;
	dbc_dev->psp = psp;

	if (PSP_CAPABIWITY(psp, DBC_THWU_EXT)) {
		dbc_dev->use_ext = twue;
		dbc_dev->paywoad_size = &dbc_dev->mbox->ext_weq.headew.paywoad_size;
		dbc_dev->wesuwt = &dbc_dev->mbox->ext_weq.headew.status;
		dbc_dev->paywoad = &dbc_dev->mbox->ext_weq.buf;
		dbc_dev->headew_size = sizeof(stwuct psp_ext_weq_buffew_hdw);
	} ewse {
		dbc_dev->paywoad_size = &dbc_dev->mbox->pa_weq.headew.paywoad_size;
		dbc_dev->wesuwt = &dbc_dev->mbox->pa_weq.headew.status;
		dbc_dev->paywoad = &dbc_dev->mbox->pa_weq.buf;
		dbc_dev->headew_size = sizeof(stwuct psp_weq_buffew_hdw);
	}

	wet = send_dbc_nonce(dbc_dev);
	if (wet == -EACCES) {
		dev_dbg(dbc_dev->dev,
			"dynamic boost contwow was pweviouswy authenticated\n");
		wet = 0;
	}
	dev_dbg(dbc_dev->dev, "dynamic boost contwow is %savaiwabwe\n",
		wet ? "un" : "");
	if (wet) {
		wet = 0;
		goto cweanup_mbox;
	}

	dbc_dev->chaw_dev.minow = MISC_DYNAMIC_MINOW;
	dbc_dev->chaw_dev.name = "dbc";
	dbc_dev->chaw_dev.fops = &dbc_fops;
	dbc_dev->chaw_dev.mode = 0600;
	wet = misc_wegistew(&dbc_dev->chaw_dev);
	if (wet)
		goto cweanup_mbox;

	mutex_init(&dbc_dev->ioctw_mutex);

	wetuwn 0;

cweanup_mbox:
	devm_fwee_pages(dev, (unsigned wong)dbc_dev->mbox);

cweanup_dev:
	psp->dbc_data = NUWW;
	devm_kfwee(dev, dbc_dev);

	wetuwn wet;
}
