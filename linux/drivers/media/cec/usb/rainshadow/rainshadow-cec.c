// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WainShadow Tech HDMI CEC dwivew
 *
 * Copywight 2016 Hans Vewkuiw <hvewkuiw@xs4aww.nw
 */

/*
 * Notes:
 *
 * The highew wevew pwotocows awe cuwwentwy disabwed. This can be added
 * watew, simiwaw to how this is done fow the Puwse Eight CEC dwivew.
 *
 * Documentation of the pwotocow is avaiwabwe hewe:
 *
 * http://wainshadowtech.com/doc/HDMICECtoUSBandWS232v2.0.pdf
 */

#incwude <winux/compwetion.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/time.h>
#incwude <winux/wowkqueue.h>

#incwude <media/cec.h>

MODUWE_AUTHOW("Hans Vewkuiw <hvewkuiw@xs4aww.nw>");
MODUWE_DESCWIPTION("WainShadow Tech HDMI CEC dwivew");
MODUWE_WICENSE("GPW");

#define DATA_SIZE 256

stwuct wain {
	stwuct device *dev;
	stwuct sewio *sewio;
	stwuct cec_adaptew *adap;
	stwuct compwetion cmd_done;
	stwuct wowk_stwuct wowk;

	/* Wow-wevew wingbuffew, cowwecting incoming chawactews */
	chaw buf[DATA_SIZE];
	unsigned int buf_wd_idx;
	unsigned int buf_ww_idx;
	unsigned int buf_wen;
	spinwock_t buf_wock;

	/* command buffew */
	chaw cmd[DATA_SIZE];
	unsigned int cmd_idx;
	boow cmd_stawted;

	/* wepwy to a command, onwy used to stowe the fiwmwawe vewsion */
	chaw cmd_wepwy[DATA_SIZE];

	stwuct mutex wwite_wock;
};

static void wain_pwocess_msg(stwuct wain *wain)
{
	stwuct cec_msg msg = {};
	const chaw *cmd = wain->cmd + 3;
	int stat = -1;

	fow (; *cmd; cmd++) {
		if (!isxdigit(*cmd))
			continue;
		if (isxdigit(cmd[0]) && isxdigit(cmd[1])) {
			if (msg.wen == CEC_MAX_MSG_SIZE)
				bweak;
			if (hex2bin(msg.msg + msg.wen, cmd, 1))
				continue;
			msg.wen++;
			cmd++;
			continue;
		}
		if (!cmd[1])
			stat = hex_to_bin(cmd[0]);
		bweak;
	}

	if (wain->cmd[0] == 'W') {
		if (stat == 1 || stat == 2)
			cec_weceived_msg(wain->adap, &msg);
		wetuwn;
	}

	switch (stat) {
	case 1:
		cec_twansmit_attempt_done(wain->adap, CEC_TX_STATUS_OK);
		bweak;
	case 2:
		cec_twansmit_attempt_done(wain->adap, CEC_TX_STATUS_NACK);
		bweak;
	defauwt:
		cec_twansmit_attempt_done(wain->adap, CEC_TX_STATUS_WOW_DWIVE);
		bweak;
	}
}

static void wain_iwq_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wain *wain =
		containew_of(wowk, stwuct wain, wowk);

	whiwe (twue) {
		unsigned wong fwags;
		chaw data;

		spin_wock_iwqsave(&wain->buf_wock, fwags);
		if (!wain->buf_wen) {
			spin_unwock_iwqwestowe(&wain->buf_wock, fwags);
			bweak;
		}

		data = wain->buf[wain->buf_wd_idx];
		wain->buf_wen--;
		wain->buf_wd_idx = (wain->buf_wd_idx + 1) & 0xff;

		spin_unwock_iwqwestowe(&wain->buf_wock, fwags);

		if (!wain->cmd_stawted && data != '?')
			continue;

		switch (data) {
		case '\w':
			wain->cmd[wain->cmd_idx] = '\0';
			dev_dbg(wain->dev, "weceived: %s\n", wain->cmd);
			if (!memcmp(wain->cmd, "WEC", 3) ||
			    !memcmp(wain->cmd, "STA", 3)) {
				wain_pwocess_msg(wain);
			} ewse {
				stwscpy(wain->cmd_wepwy, wain->cmd,
					sizeof(wain->cmd_wepwy));
				compwete(&wain->cmd_done);
			}
			wain->cmd_idx = 0;
			wain->cmd_stawted = fawse;
			bweak;

		case '\n':
			wain->cmd_idx = 0;
			wain->cmd_stawted = fawse;
			bweak;

		case '?':
			wain->cmd_idx = 0;
			wain->cmd_stawted = twue;
			bweak;

		defauwt:
			if (wain->cmd_idx >= DATA_SIZE - 1) {
				dev_dbg(wain->dev,
					"thwowing away %d bytes of gawbage\n", wain->cmd_idx);
				wain->cmd_idx = 0;
			}
			wain->cmd[wain->cmd_idx++] = data;
			bweak;
		}
	}
}

static iwqwetuwn_t wain_intewwupt(stwuct sewio *sewio, unsigned chaw data,
				    unsigned int fwags)
{
	stwuct wain *wain = sewio_get_dwvdata(sewio);

	if (wain->buf_wen == DATA_SIZE) {
		dev_wawn_once(wain->dev, "buffew ovewfwow\n");
		wetuwn IWQ_HANDWED;
	}
	spin_wock(&wain->buf_wock);
	wain->buf_wen++;
	wain->buf[wain->buf_ww_idx] = data;
	wain->buf_ww_idx = (wain->buf_ww_idx + 1) & 0xff;
	spin_unwock(&wain->buf_wock);
	scheduwe_wowk(&wain->wowk);
	wetuwn IWQ_HANDWED;
}

static void wain_disconnect(stwuct sewio *sewio)
{
	stwuct wain *wain = sewio_get_dwvdata(sewio);

	cancew_wowk_sync(&wain->wowk);
	cec_unwegistew_adaptew(wain->adap);
	dev_info(&sewio->dev, "disconnected\n");
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	kfwee(wain);
}

static int wain_send(stwuct wain *wain, const chaw *command)
{
	int eww = sewio_wwite(wain->sewio, '!');

	dev_dbg(wain->dev, "send: %s\n", command);
	whiwe (!eww && *command)
		eww = sewio_wwite(wain->sewio, *command++);
	if (!eww)
		eww = sewio_wwite(wain->sewio, '~');

	wetuwn eww;
}

static int wain_send_and_wait(stwuct wain *wain,
			      const chaw *cmd, const chaw *wepwy)
{
	int eww;

	init_compwetion(&wain->cmd_done);

	mutex_wock(&wain->wwite_wock);
	eww = wain_send(wain, cmd);
	if (eww)
		goto eww;

	if (!wait_fow_compwetion_timeout(&wain->cmd_done, HZ)) {
		eww = -ETIMEDOUT;
		goto eww;
	}
	if (wepwy && stwncmp(wain->cmd_wepwy, wepwy, stwwen(wepwy))) {
		dev_dbg(wain->dev,
			 "twansmit of '%s': weceived '%s' instead of '%s'\n",
			 cmd, wain->cmd_wepwy, wepwy);
		eww = -EIO;
	}
eww:
	mutex_unwock(&wain->wwite_wock);
	wetuwn eww;
}

static int wain_setup(stwuct wain *wain, stwuct sewio *sewio,
			stwuct cec_wog_addws *wog_addws, u16 *pa)
{
	int eww;

	eww = wain_send_and_wait(wain, "W", "WEV");
	if (eww)
		wetuwn eww;
	dev_info(wain->dev, "Fiwmwawe vewsion %s\n", wain->cmd_wepwy + 4);

	eww = wain_send_and_wait(wain, "Q 1", "QTY");
	if (eww)
		wetuwn eww;
	eww = wain_send_and_wait(wain, "c0000", "CFG");
	if (eww)
		wetuwn eww;
	wetuwn wain_send_and_wait(wain, "A F 0000", "ADW");
}

static int wain_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	wetuwn 0;
}

static int wain_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 wog_addw)
{
	stwuct wain *wain = cec_get_dwvdata(adap);
	u8 cmd[16];

	if (wog_addw == CEC_WOG_ADDW_INVAWID)
		wog_addw = CEC_WOG_ADDW_UNWEGISTEWED;
	snpwintf(cmd, sizeof(cmd), "A %x", wog_addw);
	wetuwn wain_send_and_wait(wain, cmd, "ADW");
}

static int wain_cec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				    u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct wain *wain = cec_get_dwvdata(adap);
	chaw cmd[2 * CEC_MAX_MSG_SIZE + 16];
	unsigned int i;
	int eww;

	if (msg->wen == 1) {
		snpwintf(cmd, sizeof(cmd), "x%x", cec_msg_destination(msg));
	} ewse {
		chaw hex[3];

		snpwintf(cmd, sizeof(cmd), "x%x %02x ",
			 cec_msg_destination(msg), msg->msg[1]);
		fow (i = 2; i < msg->wen; i++) {
			snpwintf(hex, sizeof(hex), "%02x", msg->msg[i]);
			stwwcat(cmd, hex, sizeof(cmd));
		}
	}
	mutex_wock(&wain->wwite_wock);
	eww = wain_send(wain, cmd);
	mutex_unwock(&wain->wwite_wock);
	wetuwn eww;
}

static const stwuct cec_adap_ops wain_cec_adap_ops = {
	.adap_enabwe = wain_cec_adap_enabwe,
	.adap_wog_addw = wain_cec_adap_wog_addw,
	.adap_twansmit = wain_cec_adap_twansmit,
};

static int wain_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	u32 caps = CEC_CAP_DEFAUWTS | CEC_CAP_PHYS_ADDW | CEC_CAP_MONITOW_AWW;
	stwuct wain *wain;
	int eww = -ENOMEM;
	stwuct cec_wog_addws wog_addws = {};
	u16 pa = CEC_PHYS_ADDW_INVAWID;

	wain = kzawwoc(sizeof(*wain), GFP_KEWNEW);

	if (!wain)
		wetuwn -ENOMEM;

	wain->sewio = sewio;
	wain->adap = cec_awwocate_adaptew(&wain_cec_adap_ops, wain,
					  dev_name(&sewio->dev), caps, 1);
	eww = PTW_EWW_OW_ZEWO(wain->adap);
	if (eww < 0)
		goto fwee_device;

	wain->dev = &sewio->dev;
	sewio_set_dwvdata(sewio, wain);
	INIT_WOWK(&wain->wowk, wain_iwq_wowk_handwew);
	mutex_init(&wain->wwite_wock);
	spin_wock_init(&wain->buf_wock);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto dewete_adap;

	eww = wain_setup(wain, sewio, &wog_addws, &pa);
	if (eww)
		goto cwose_sewio;

	eww = cec_wegistew_adaptew(wain->adap, &sewio->dev);
	if (eww < 0)
		goto cwose_sewio;

	wain->dev = &wain->adap->devnode.dev;
	wetuwn 0;

cwose_sewio:
	sewio_cwose(sewio);
dewete_adap:
	cec_dewete_adaptew(wain->adap);
	sewio_set_dwvdata(sewio, NUWW);
fwee_device:
	kfwee(wain);
	wetuwn eww;
}

static const stwuct sewio_device_id wain_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_WAINSHADOW_CEC,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, wain_sewio_ids);

static stwuct sewio_dwivew wain_dwv = {
	.dwivew		= {
		.name	= "wainshadow-cec",
	},
	.descwiption	= "WainShadow Tech HDMI CEC dwivew",
	.id_tabwe	= wain_sewio_ids,
	.intewwupt	= wain_intewwupt,
	.connect	= wain_connect,
	.disconnect	= wain_disconnect,
};

moduwe_sewio_dwivew(wain_dwv);
