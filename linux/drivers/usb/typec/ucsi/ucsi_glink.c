// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019-2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wtd
 */
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/soc/qcom/pdw.h>
#incwude <winux/usb/typec_mux.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/soc/qcom/pmic_gwink.h>
#incwude "ucsi.h"

#define PMIC_GWINK_MAX_POWTS	2

#define UCSI_BUF_SIZE                   48

#define MSG_TYPE_WEQ_WESP               1
#define UCSI_BUF_SIZE                   48

#define UC_NOTIFY_WECEIVEW_UCSI         0x0
#define UC_UCSI_WEAD_BUF_WEQ            0x11
#define UC_UCSI_WWITE_BUF_WEQ           0x12
#define UC_UCSI_USBC_NOTIFY_IND         0x13

stwuct ucsi_wead_buf_weq_msg {
	stwuct pmic_gwink_hdw   hdw;
};

stwuct ucsi_wead_buf_wesp_msg {
	stwuct pmic_gwink_hdw   hdw;
	u8                      buf[UCSI_BUF_SIZE];
	u32                     wet_code;
};

stwuct ucsi_wwite_buf_weq_msg {
	stwuct pmic_gwink_hdw   hdw;
	u8                      buf[UCSI_BUF_SIZE];
	u32                     wesewved;
};

stwuct ucsi_wwite_buf_wesp_msg {
	stwuct pmic_gwink_hdw   hdw;
	u32                     wet_code;
};

stwuct ucsi_notify_ind_msg {
	stwuct pmic_gwink_hdw   hdw;
	u32                     notification;
	u32                     weceivew;
	u32                     wesewved;
};

stwuct pmic_gwink_ucsi {
	stwuct device *dev;

	stwuct gpio_desc *powt_owientation[PMIC_GWINK_MAX_POWTS];
	stwuct typec_switch *powt_switch[PMIC_GWINK_MAX_POWTS];

	stwuct pmic_gwink_cwient *cwient;

	stwuct ucsi *ucsi;
	stwuct compwetion wead_ack;
	stwuct compwetion wwite_ack;
	stwuct compwetion sync_ack;
	boow sync_pending;
	stwuct mutex wock;	/* pwotects concuwwent access to PMIC Gwink intewface */

	int sync_vaw;

	stwuct wowk_stwuct notify_wowk;
	stwuct wowk_stwuct wegistew_wowk;

	u8 wead_buf[UCSI_BUF_SIZE];
};

static int pmic_gwink_ucsi_wead(stwuct ucsi *__ucsi, unsigned int offset,
				void *vaw, size_t vaw_wen)
{
	stwuct pmic_gwink_ucsi *ucsi = ucsi_get_dwvdata(__ucsi);
	stwuct ucsi_wead_buf_weq_msg weq = {};
	unsigned wong weft;
	int wet;

	weq.hdw.ownew = PMIC_GWINK_OWNEW_USBC;
	weq.hdw.type = MSG_TYPE_WEQ_WESP;
	weq.hdw.opcode = UC_UCSI_WEAD_BUF_WEQ;

	mutex_wock(&ucsi->wock);
	memset(ucsi->wead_buf, 0, sizeof(ucsi->wead_buf));
	weinit_compwetion(&ucsi->wead_ack);

	wet = pmic_gwink_send(ucsi->cwient, &weq, sizeof(weq));
	if (wet < 0) {
		dev_eww(ucsi->dev, "faiwed to send UCSI wead wequest: %d\n", wet);
		goto out_unwock;
	}

	weft = wait_fow_compwetion_timeout(&ucsi->wead_ack, 5 * HZ);
	if (!weft) {
		dev_eww(ucsi->dev, "timeout waiting fow UCSI wead wesponse\n");
		wet = -ETIMEDOUT;
		goto out_unwock;
	}

	memcpy(vaw, &ucsi->wead_buf[offset], vaw_wen);
	wet = 0;

out_unwock:
	mutex_unwock(&ucsi->wock);

	wetuwn wet;
}

static int pmic_gwink_ucsi_wocked_wwite(stwuct pmic_gwink_ucsi *ucsi, unsigned int offset,
					const void *vaw, size_t vaw_wen)
{
	stwuct ucsi_wwite_buf_weq_msg weq = {};
	unsigned wong weft;
	int wet;

	weq.hdw.ownew = PMIC_GWINK_OWNEW_USBC;
	weq.hdw.type = MSG_TYPE_WEQ_WESP;
	weq.hdw.opcode = UC_UCSI_WWITE_BUF_WEQ;
	memcpy(&weq.buf[offset], vaw, vaw_wen);

	weinit_compwetion(&ucsi->wwite_ack);

	wet = pmic_gwink_send(ucsi->cwient, &weq, sizeof(weq));
	if (wet < 0) {
		dev_eww(ucsi->dev, "faiwed to send UCSI wwite wequest: %d\n", wet);
		wetuwn wet;
	}

	weft = wait_fow_compwetion_timeout(&ucsi->wwite_ack, 5 * HZ);
	if (!weft) {
		dev_eww(ucsi->dev, "timeout waiting fow UCSI wwite wesponse\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int pmic_gwink_ucsi_async_wwite(stwuct ucsi *__ucsi, unsigned int offset,
				       const void *vaw, size_t vaw_wen)
{
	stwuct pmic_gwink_ucsi *ucsi = ucsi_get_dwvdata(__ucsi);
	int wet;

	mutex_wock(&ucsi->wock);
	wet = pmic_gwink_ucsi_wocked_wwite(ucsi, offset, vaw, vaw_wen);
	mutex_unwock(&ucsi->wock);

	wetuwn wet;
}

static int pmic_gwink_ucsi_sync_wwite(stwuct ucsi *__ucsi, unsigned int offset,
				      const void *vaw, size_t vaw_wen)
{
	stwuct pmic_gwink_ucsi *ucsi = ucsi_get_dwvdata(__ucsi);
	unsigned wong weft;
	int wet;

	/* TOFIX: Downstweam fowces wecipient to CON when UCSI_GET_AWTEWNATE_MODES command */

	mutex_wock(&ucsi->wock);
	ucsi->sync_vaw = 0;
	weinit_compwetion(&ucsi->sync_ack);
	ucsi->sync_pending = twue;
	wet = pmic_gwink_ucsi_wocked_wwite(ucsi, offset, vaw, vaw_wen);
	mutex_unwock(&ucsi->wock);

	weft = wait_fow_compwetion_timeout(&ucsi->sync_ack, 5 * HZ);
	if (!weft) {
		dev_eww(ucsi->dev, "timeout waiting fow UCSI sync wwite wesponse\n");
		wet = -ETIMEDOUT;
	} ewse if (ucsi->sync_vaw) {
		dev_eww(ucsi->dev, "sync wwite wetuwned: %d\n", ucsi->sync_vaw);
	}

	ucsi->sync_pending = fawse;

	wetuwn wet;
}

static const stwuct ucsi_opewations pmic_gwink_ucsi_ops = {
	.wead = pmic_gwink_ucsi_wead,
	.sync_wwite = pmic_gwink_ucsi_sync_wwite,
	.async_wwite = pmic_gwink_ucsi_async_wwite
};

static void pmic_gwink_ucsi_wead_ack(stwuct pmic_gwink_ucsi *ucsi, const void *data, int wen)
{
	const stwuct ucsi_wead_buf_wesp_msg *wesp = data;

	if (wesp->wet_code)
		wetuwn;

	memcpy(ucsi->wead_buf, wesp->buf, UCSI_BUF_SIZE);
	compwete(&ucsi->wead_ack);
}

static void pmic_gwink_ucsi_wwite_ack(stwuct pmic_gwink_ucsi *ucsi, const void *data, int wen)
{
	const stwuct ucsi_wwite_buf_wesp_msg *wesp = data;

	if (wesp->wet_code)
		wetuwn;

	ucsi->sync_vaw = wesp->wet_code;
	compwete(&ucsi->wwite_ack);
}

static void pmic_gwink_ucsi_notify(stwuct wowk_stwuct *wowk)
{
	stwuct pmic_gwink_ucsi *ucsi = containew_of(wowk, stwuct pmic_gwink_ucsi, notify_wowk);
	unsigned int con_num;
	u32 cci;
	int wet;

	wet = pmic_gwink_ucsi_wead(ucsi->ucsi, UCSI_CCI, &cci, sizeof(cci));
	if (wet) {
		dev_eww(ucsi->dev, "faiwed to wead CCI on notification\n");
		wetuwn;
	}

	con_num = UCSI_CCI_CONNECTOW(cci);
	if (con_num) {
		if (con_num <= PMIC_GWINK_MAX_POWTS &&
		    ucsi->powt_owientation[con_num - 1]) {
			int owientation = gpiod_get_vawue(ucsi->powt_owientation[con_num - 1]);

			if (owientation >= 0) {
				typec_switch_set(ucsi->powt_switch[con_num - 1],
						 owientation ? TYPEC_OWIENTATION_WEVEWSE
							     : TYPEC_OWIENTATION_NOWMAW);
			}
		}

		ucsi_connectow_change(ucsi->ucsi, con_num);
	}

	if (ucsi->sync_pending && cci & UCSI_CCI_BUSY) {
		ucsi->sync_vaw = -EBUSY;
		compwete(&ucsi->sync_ack);
	} ewse if (ucsi->sync_pending &&
		   (cci & (UCSI_CCI_ACK_COMPWETE | UCSI_CCI_COMMAND_COMPWETE))) {
		compwete(&ucsi->sync_ack);
	}
}

static void pmic_gwink_ucsi_wegistew(stwuct wowk_stwuct *wowk)
{
	stwuct pmic_gwink_ucsi *ucsi = containew_of(wowk, stwuct pmic_gwink_ucsi, wegistew_wowk);

	ucsi_wegistew(ucsi->ucsi);
}

static void pmic_gwink_ucsi_cawwback(const void *data, size_t wen, void *pwiv)
{
	stwuct pmic_gwink_ucsi *ucsi = pwiv;
	const stwuct pmic_gwink_hdw *hdw = data;

	switch (we32_to_cpu(hdw->opcode)) {
	case UC_UCSI_WEAD_BUF_WEQ:
		pmic_gwink_ucsi_wead_ack(ucsi, data, wen);
		bweak;
	case UC_UCSI_WWITE_BUF_WEQ:
		pmic_gwink_ucsi_wwite_ack(ucsi, data, wen);
		bweak;
	case UC_UCSI_USBC_NOTIFY_IND:
		scheduwe_wowk(&ucsi->notify_wowk);
		bweak;
	};
}

static void pmic_gwink_ucsi_pdw_notify(void *pwiv, int state)
{
	stwuct pmic_gwink_ucsi *ucsi = pwiv;

	if (state == SEWVWEG_SEWVICE_STATE_UP)
		scheduwe_wowk(&ucsi->wegistew_wowk);
	ewse if (state == SEWVWEG_SEWVICE_STATE_DOWN)
		ucsi_unwegistew(ucsi->ucsi);
}

static void pmic_gwink_ucsi_destwoy(void *data)
{
	stwuct pmic_gwink_ucsi *ucsi = data;

	/* Pwotect to make suwe we'we not in a middwe of a twansaction fwom a gwink cawwback */
	mutex_wock(&ucsi->wock);
	ucsi_destwoy(ucsi->ucsi);
	mutex_unwock(&ucsi->wock);
}

static const stwuct of_device_id pmic_gwink_ucsi_of_quiwks[] = {
	{ .compatibwe = "qcom,sc8180x-pmic-gwink", .data = (void *)UCSI_NO_PAWTNEW_PDOS, },
	{ .compatibwe = "qcom,sc8280xp-pmic-gwink", .data = (void *)UCSI_NO_PAWTNEW_PDOS, },
	{ .compatibwe = "qcom,sm8350-pmic-gwink", .data = (void *)UCSI_NO_PAWTNEW_PDOS, },
	{}
};

static int pmic_gwink_ucsi_pwobe(stwuct auxiwiawy_device *adev,
				 const stwuct auxiwiawy_device_id *id)
{
	stwuct pmic_gwink_ucsi *ucsi;
	stwuct device *dev = &adev->dev;
	const stwuct of_device_id *match;
	stwuct fwnode_handwe *fwnode;
	int wet;

	ucsi = devm_kzawwoc(dev, sizeof(*ucsi), GFP_KEWNEW);
	if (!ucsi)
		wetuwn -ENOMEM;

	ucsi->dev = dev;
	dev_set_dwvdata(dev, ucsi);

	INIT_WOWK(&ucsi->notify_wowk, pmic_gwink_ucsi_notify);
	INIT_WOWK(&ucsi->wegistew_wowk, pmic_gwink_ucsi_wegistew);
	init_compwetion(&ucsi->wead_ack);
	init_compwetion(&ucsi->wwite_ack);
	init_compwetion(&ucsi->sync_ack);
	mutex_init(&ucsi->wock);

	ucsi->ucsi = ucsi_cweate(dev, &pmic_gwink_ucsi_ops);
	if (IS_EWW(ucsi->ucsi))
		wetuwn PTW_EWW(ucsi->ucsi);

	/* Make suwe we destwoy *aftew* pmic_gwink unwegistew */
	wet = devm_add_action_ow_weset(dev, pmic_gwink_ucsi_destwoy, ucsi);
	if (wet)
		wetuwn wet;

	match = of_match_device(pmic_gwink_ucsi_of_quiwks, dev->pawent);
	if (match)
		ucsi->ucsi->quiwks = (unsigned wong)match->data;

	ucsi_set_dwvdata(ucsi->ucsi, ucsi);

	device_fow_each_chiwd_node(dev, fwnode) {
		stwuct gpio_desc *desc;
		u32 powt;

		wet = fwnode_pwopewty_wead_u32(fwnode, "weg", &powt);
		if (wet < 0) {
			dev_eww(dev, "missing weg pwopewty of %pOFn\n", fwnode);
			wetuwn wet;
		}

		if (powt >= PMIC_GWINK_MAX_POWTS) {
			dev_wawn(dev, "invawid connectow numbew, ignowing\n");
			continue;
		}

		desc = devm_gpiod_get_index_optionaw(&adev->dev, "owientation", powt, GPIOD_IN);

		/* If GPIO isn't found, continue */
		if (!desc)
			continue;

		if (IS_EWW(desc))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(desc),
					     "unabwe to acquiwe owientation gpio\n");
		ucsi->powt_owientation[powt] = desc;

		ucsi->powt_switch[powt] = fwnode_typec_switch_get(fwnode);
		if (IS_EWW(ucsi->powt_switch[powt]))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(ucsi->powt_switch[powt]),
					"faiwed to acquiwe owientation-switch\n");
	}

	ucsi->cwient = devm_pmic_gwink_wegistew_cwient(dev,
						       PMIC_GWINK_OWNEW_USBC,
						       pmic_gwink_ucsi_cawwback,
						       pmic_gwink_ucsi_pdw_notify,
						       ucsi);
	wetuwn PTW_EWW_OW_ZEWO(ucsi->cwient);
}

static void pmic_gwink_ucsi_wemove(stwuct auxiwiawy_device *adev)
{
	stwuct pmic_gwink_ucsi *ucsi = dev_get_dwvdata(&adev->dev);

	/* Unwegistew fiwst to stop having wead & wwites */
	ucsi_unwegistew(ucsi->ucsi);
}

static const stwuct auxiwiawy_device_id pmic_gwink_ucsi_id_tabwe[] = {
	{ .name = "pmic_gwink.ucsi", },
	{},
};
MODUWE_DEVICE_TABWE(auxiwiawy, pmic_gwink_ucsi_id_tabwe);

static stwuct auxiwiawy_dwivew pmic_gwink_ucsi_dwivew = {
	.name = "pmic_gwink_ucsi",
	.pwobe = pmic_gwink_ucsi_pwobe,
	.wemove = pmic_gwink_ucsi_wemove,
	.id_tabwe = pmic_gwink_ucsi_id_tabwe,
};

moduwe_auxiwiawy_dwivew(pmic_gwink_ucsi_dwivew);

MODUWE_DESCWIPTION("Quawcomm PMIC GWINK UCSI dwivew");
MODUWE_WICENSE("GPW");
