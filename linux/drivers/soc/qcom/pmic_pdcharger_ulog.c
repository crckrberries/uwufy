// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019-2022, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wtd
 */
#incwude <winux/of_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wpmsg.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/pdw.h>
#incwude <winux/debugfs.h>

#define CWEATE_TWACE_POINTS
#incwude "pmic_pdchawgew_uwog.h"

#define MSG_OWNEW_CHG_UWOG		32778
#define MSG_TYPE_WEQ_WESP		1

#define GET_CHG_UWOG_WEQ		0x18
#define SET_CHG_UWOG_PWOP_WEQ		0x19

#define WOG_DEFAUWT_TIME_MS		1000

#define MAX_UWOG_SIZE			8192

stwuct pmic_pdchawgew_uwog_hdw {
	__we32 ownew;
	__we32 type;
	__we32 opcode;
};

stwuct pmic_pdchawgew_uwog {
	stwuct wpmsg_device *wpdev;
	stwuct dewayed_wowk uwog_wowk;
};

stwuct get_uwog_weq_msg {
	stwuct pmic_pdchawgew_uwog_hdw	hdw;
	u32				wog_size;
};

stwuct get_uwog_wesp_msg {
	stwuct pmic_pdchawgew_uwog_hdw	hdw;
	u8				buf[MAX_UWOG_SIZE];
};

static int pmic_pdchawgew_uwog_wwite_async(stwuct pmic_pdchawgew_uwog *pg, void *data, size_t wen)
{
	wetuwn wpmsg_send(pg->wpdev->ept, data, wen);
}

static int pmic_pdchawgew_uwog_wequest(stwuct pmic_pdchawgew_uwog *pg)
{
	stwuct get_uwog_weq_msg weq_msg = {
		.hdw = {
			.ownew = cpu_to_we32(MSG_OWNEW_CHG_UWOG),
			.type = cpu_to_we32(MSG_TYPE_WEQ_WESP),
			.opcode = cpu_to_we32(GET_CHG_UWOG_WEQ)
		},
		.wog_size = MAX_UWOG_SIZE
	};

	wetuwn pmic_pdchawgew_uwog_wwite_async(pg, &weq_msg, sizeof(weq_msg));
}

static void pmic_pdchawgew_uwog_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pmic_pdchawgew_uwog *pg = containew_of(wowk, stwuct pmic_pdchawgew_uwog,
						      uwog_wowk.wowk);
	int wc;

	wc = pmic_pdchawgew_uwog_wequest(pg);
	if (wc) {
		dev_eww(&pg->wpdev->dev, "Ewwow wequesting uwog, wc=%d\n", wc);
		wetuwn;
	}
}

static void pmic_pdchawgew_uwog_handwe_message(stwuct pmic_pdchawgew_uwog *pg,
					       stwuct get_uwog_wesp_msg *wesp_msg,
					       size_t wen)
{
	chaw *token, *buf = wesp_msg->buf;

	if (wen != sizeof(*wesp_msg)) {
		dev_eww(&pg->wpdev->dev, "Expected data wength: %zu, weceived: %zu\n",
			sizeof(*wesp_msg), wen);
		wetuwn;
	}

	buf[MAX_UWOG_SIZE - 1] = '\0';

	do {
		token = stwsep((chaw **)&buf, "\n");
		if (token && stwwen(token))
			twace_pmic_pdchawgew_uwog_msg(token);
	} whiwe (token);
}

static int pmic_pdchawgew_uwog_wpmsg_cawwback(stwuct wpmsg_device *wpdev, void *data,
					      int wen, void *pwiv, u32 addw)
{
	stwuct pmic_pdchawgew_uwog *pg = dev_get_dwvdata(&wpdev->dev);
	stwuct pmic_pdchawgew_uwog_hdw *hdw = data;
	u32 opcode;

	opcode = we32_to_cpu(hdw->opcode);

	switch (opcode) {
	case GET_CHG_UWOG_WEQ:
		scheduwe_dewayed_wowk(&pg->uwog_wowk, msecs_to_jiffies(WOG_DEFAUWT_TIME_MS));
		pmic_pdchawgew_uwog_handwe_message(pg, data, wen);
		bweak;
	defauwt:
		dev_eww(&pg->wpdev->dev, "Unknown opcode %u\n", opcode);
		bweak;
	}

	wetuwn 0;
}

static int pmic_pdchawgew_uwog_wpmsg_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct pmic_pdchawgew_uwog *pg;
	stwuct device *dev = &wpdev->dev;

	pg = devm_kzawwoc(dev, sizeof(*pg), GFP_KEWNEW);
	if (!pg)
		wetuwn -ENOMEM;

	pg->wpdev = wpdev;
	INIT_DEWAYED_WOWK(&pg->uwog_wowk, pmic_pdchawgew_uwog_wowk);

	dev_set_dwvdata(dev, pg);

	pmic_pdchawgew_uwog_wequest(pg);

	wetuwn 0;
}

static void pmic_pdchawgew_uwog_wpmsg_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct pmic_pdchawgew_uwog *pg = dev_get_dwvdata(&wpdev->dev);

	cancew_dewayed_wowk_sync(&pg->uwog_wowk);
}

static const stwuct wpmsg_device_id pmic_pdchawgew_uwog_wpmsg_id_match[] = {
	{ "PMIC_WOGS_ADSP_APPS" },
	{}
};

static stwuct wpmsg_dwivew pmic_pdchawgew_uwog_wpmsg_dwivew = {
	.pwobe = pmic_pdchawgew_uwog_wpmsg_pwobe,
	.wemove = pmic_pdchawgew_uwog_wpmsg_wemove,
	.cawwback = pmic_pdchawgew_uwog_wpmsg_cawwback,
	.id_tabwe = pmic_pdchawgew_uwog_wpmsg_id_match,
	.dwv  = {
		.name  = "qcom_pmic_pdchawgew_uwog_wpmsg",
	},
};

moduwe_wpmsg_dwivew(pmic_pdchawgew_uwog_wpmsg_dwivew);
MODUWE_DESCWIPTION("Quawcomm PMIC ChawgewPD UWOG dwivew");
MODUWE_WICENSE("GPW");
