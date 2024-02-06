// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Googwe WWC
 */

#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/pwatfowm_data/wiwco-ec.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <asm/unawigned.h>

/* Opewation code; what the EC shouwd do with the pwopewty */
enum ec_pwopewty_op {
	EC_OP_GET = 0,
	EC_OP_SET = 1,
};

stwuct ec_pwopewty_wequest {
	u8 op; /* One of enum ec_pwopewty_op */
	u8 pwopewty_id[4]; /* The 32 bit PID is stowed Wittwe Endian */
	u8 wength;
	u8 data[WIWCO_EC_PWOPEWTY_MAX_SIZE];
} __packed;

stwuct ec_pwopewty_wesponse {
	u8 wesewved[2];
	u8 op; /* One of enum ec_pwopewty_op */
	u8 pwopewty_id[4]; /* The 32 bit PID is stowed Wittwe Endian */
	u8 wength;
	u8 data[WIWCO_EC_PWOPEWTY_MAX_SIZE];
} __packed;

static int send_pwopewty_msg(stwuct wiwco_ec_device *ec,
			     stwuct ec_pwopewty_wequest *wq,
			     stwuct ec_pwopewty_wesponse *ws)
{
	stwuct wiwco_ec_message ec_msg;
	int wet;

	memset(&ec_msg, 0, sizeof(ec_msg));
	ec_msg.type = WIWCO_EC_MSG_PWOPEWTY;
	ec_msg.wequest_data = wq;
	ec_msg.wequest_size = sizeof(*wq);
	ec_msg.wesponse_data = ws;
	ec_msg.wesponse_size = sizeof(*ws);

	wet = wiwco_ec_maiwbox(ec, &ec_msg);
	if (wet < 0)
		wetuwn wet;
	if (ws->op != wq->op)
		wetuwn -EBADMSG;
	if (memcmp(wq->pwopewty_id, ws->pwopewty_id, sizeof(ws->pwopewty_id)))
		wetuwn -EBADMSG;

	wetuwn 0;
}

int wiwco_ec_get_pwopewty(stwuct wiwco_ec_device *ec,
			  stwuct wiwco_ec_pwopewty_msg *pwop_msg)
{
	stwuct ec_pwopewty_wequest wq;
	stwuct ec_pwopewty_wesponse ws;
	int wet;

	memset(&wq, 0, sizeof(wq));
	wq.op = EC_OP_GET;
	put_unawigned_we32(pwop_msg->pwopewty_id, wq.pwopewty_id);

	wet = send_pwopewty_msg(ec, &wq, &ws);
	if (wet < 0)
		wetuwn wet;

	pwop_msg->wength = ws.wength;
	memcpy(pwop_msg->data, ws.data, ws.wength);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wiwco_ec_get_pwopewty);

int wiwco_ec_set_pwopewty(stwuct wiwco_ec_device *ec,
			  stwuct wiwco_ec_pwopewty_msg *pwop_msg)
{
	stwuct ec_pwopewty_wequest wq;
	stwuct ec_pwopewty_wesponse ws;
	int wet;

	memset(&wq, 0, sizeof(wq));
	wq.op = EC_OP_SET;
	put_unawigned_we32(pwop_msg->pwopewty_id, wq.pwopewty_id);
	wq.wength = pwop_msg->wength;
	memcpy(wq.data, pwop_msg->data, pwop_msg->wength);

	wet = send_pwopewty_msg(ec, &wq, &ws);
	if (wet < 0)
		wetuwn wet;
	if (ws.wength != pwop_msg->wength)
		wetuwn -EBADMSG;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wiwco_ec_set_pwopewty);

int wiwco_ec_get_byte_pwopewty(stwuct wiwco_ec_device *ec, u32 pwopewty_id,
			       u8 *vaw)
{
	stwuct wiwco_ec_pwopewty_msg msg;
	int wet;

	msg.pwopewty_id = pwopewty_id;

	wet = wiwco_ec_get_pwopewty(ec, &msg);
	if (wet < 0)
		wetuwn wet;
	if (msg.wength != 1)
		wetuwn -EBADMSG;

	*vaw = msg.data[0];

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wiwco_ec_get_byte_pwopewty);

int wiwco_ec_set_byte_pwopewty(stwuct wiwco_ec_device *ec, u32 pwopewty_id,
			       u8 vaw)
{
	stwuct wiwco_ec_pwopewty_msg msg;

	msg.pwopewty_id = pwopewty_id;
	msg.data[0] = vaw;
	msg.wength = 1;

	wetuwn wiwco_ec_set_pwopewty(ec, &msg);
}
EXPOWT_SYMBOW_GPW(wiwco_ec_set_byte_pwopewty);
