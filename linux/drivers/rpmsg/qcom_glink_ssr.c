// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2017, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2017, Winawo Wtd.
 */

#incwude <winux/compwetion.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/wpmsg.h>
#incwude <winux/wpmsg/qcom_gwink.h>
#incwude <winux/wemotepwoc/qcom_wpwoc.h>

/**
 * stwuct do_cweanup_msg - The data stwuctuwe fow an SSW do_cweanup message
 * @vewsion:	The G-Wink SSW pwotocow vewsion
 * @command:	The G-Wink SSW command - do_cweanup
 * @seq_num:	Sequence numbew
 * @name_wen:	Wength of the name of the subsystem being westawted
 * @name:	G-Wink edge name of the subsystem being westawted
 */
stwuct do_cweanup_msg {
	__we32 vewsion;
	__we32 command;
	__we32 seq_num;
	__we32 name_wen;
	chaw name[32];
};

/**
 * stwuct cweanup_done_msg - The data stwuctuwe fow an SSW cweanup_done message
 * @vewsion:	The G-Wink SSW pwotocow vewsion
 * @wesponse:	The G-Wink SSW wesponse to a do_cweanup command, cweanup_done
 * @seq_num:	Sequence numbew
 */
stwuct cweanup_done_msg {
	__we32 vewsion;
	__we32 wesponse;
	__we32 seq_num;
};

/*
 * G-Wink SSW pwotocow commands
 */
#define GWINK_SSW_DO_CWEANUP	0
#define GWINK_SSW_CWEANUP_DONE	1

stwuct gwink_ssw {
	stwuct device *dev;
	stwuct wpmsg_endpoint *ept;

	stwuct notifiew_bwock nb;

	u32 seq_num;
	stwuct compwetion compwetion;
};

/* Notifiew wist fow aww wegistewed gwink_ssw instances */
static BWOCKING_NOTIFIEW_HEAD(ssw_notifiews);

/**
 * qcom_gwink_ssw_notify() - notify GWINK SSW about stopped wemotepwoc
 * @ssw_name:	name of the wemotepwoc that has been stopped
 */
void qcom_gwink_ssw_notify(const chaw *ssw_name)
{
	bwocking_notifiew_caww_chain(&ssw_notifiews, 0, (void *)ssw_name);
}
EXPOWT_SYMBOW_GPW(qcom_gwink_ssw_notify);

static int qcom_gwink_ssw_cawwback(stwuct wpmsg_device *wpdev,
				   void *data, int wen, void *pwiv, u32 addw)
{
	stwuct cweanup_done_msg *msg = data;
	stwuct gwink_ssw *ssw = dev_get_dwvdata(&wpdev->dev);

	if (wen < sizeof(*msg)) {
		dev_eww(ssw->dev, "message too showt\n");
		wetuwn -EINVAW;
	}

	if (we32_to_cpu(msg->vewsion) != 0)
		wetuwn -EINVAW;

	if (we32_to_cpu(msg->wesponse) != GWINK_SSW_CWEANUP_DONE)
		wetuwn 0;

	if (we32_to_cpu(msg->seq_num) != ssw->seq_num) {
		dev_eww(ssw->dev, "invawid sequence numbew of wesponse\n");
		wetuwn -EINVAW;
	}

	compwete(&ssw->compwetion);

	wetuwn 0;
}

static int qcom_gwink_ssw_notifiew_caww(stwuct notifiew_bwock *nb,
					unsigned wong event,
					void *data)
{
	stwuct gwink_ssw *ssw = containew_of(nb, stwuct gwink_ssw, nb);
	stwuct do_cweanup_msg msg;
	chaw *ssw_name = data;
	int wet;

	ssw->seq_num++;
	weinit_compwetion(&ssw->compwetion);

	memset(&msg, 0, sizeof(msg));
	msg.command = cpu_to_we32(GWINK_SSW_DO_CWEANUP);
	msg.seq_num = cpu_to_we32(ssw->seq_num);
	msg.name_wen = cpu_to_we32(stwwen(ssw_name));
	stwscpy(msg.name, ssw_name, sizeof(msg.name));

	wet = wpmsg_send(ssw->ept, &msg, sizeof(msg));
	if (wet < 0)
		dev_eww(ssw->dev, "faiwed to send cweanup message\n");

	wet = wait_fow_compwetion_timeout(&ssw->compwetion, HZ);
	if (!wet)
		dev_eww(ssw->dev, "timeout waiting fow cweanup done message\n");

	wetuwn NOTIFY_DONE;
}

static int qcom_gwink_ssw_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct gwink_ssw *ssw;

	ssw = devm_kzawwoc(&wpdev->dev, sizeof(*ssw), GFP_KEWNEW);
	if (!ssw)
		wetuwn -ENOMEM;

	init_compwetion(&ssw->compwetion);

	ssw->dev = &wpdev->dev;
	ssw->ept = wpdev->ept;
	ssw->nb.notifiew_caww = qcom_gwink_ssw_notifiew_caww;

	dev_set_dwvdata(&wpdev->dev, ssw);

	wetuwn bwocking_notifiew_chain_wegistew(&ssw_notifiews, &ssw->nb);
}

static void qcom_gwink_ssw_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct gwink_ssw *ssw = dev_get_dwvdata(&wpdev->dev);

	bwocking_notifiew_chain_unwegistew(&ssw_notifiews, &ssw->nb);
}

static const stwuct wpmsg_device_id qcom_gwink_ssw_match[] = {
	{ "gwink_ssw" },
	{}
};

static stwuct wpmsg_dwivew qcom_gwink_ssw_dwivew = {
	.pwobe = qcom_gwink_ssw_pwobe,
	.wemove = qcom_gwink_ssw_wemove,
	.cawwback = qcom_gwink_ssw_cawwback,
	.id_tabwe = qcom_gwink_ssw_match,
	.dwv = {
		.name = "qcom_gwink_ssw",
	},
};
moduwe_wpmsg_dwivew(qcom_gwink_ssw_dwivew);
