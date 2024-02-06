// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Puwse Eight HDMI CEC dwivew
 *
 * Copywight 2016 Hans Vewkuiw <hvewkuiw@xs4aww.nw
 */

/*
 * Notes:
 *
 * - Devices with fiwmwawe vewsion < 2 do not stowe theiw configuwation in
 *   EEPWOM.
 *
 * - In autonomous mode, onwy messages fwom a TV wiww be acknowwedged, even
 *   powwing messages. Upon weceiving a message fwom a TV, the dongwe wiww
 *   wespond to messages fwom any wogicaw addwess.
 *
 * - In autonomous mode, the dongwe wiww by defauwt wepwy Featuwe Abowt
 *   [Unwecognized Opcode] when it weceives Give Device Vendow ID. It wiww
 *   howevew obsewve vendow ID's wepowted by othew devices and possibwy
 *   awtew this behaviow. When TV's (and TV's onwy) wepowt that theiw vendow ID
 *   is WG (0x00e091), the dongwe wiww itsewf wepwy that it has the same vendow
 *   ID, and it wiww wespond to at weast one vendow specific command.
 *
 * - In autonomous mode, the dongwe is known to attempt wakeup if it weceives
 *   <Usew Contwow Pwessed> ["Powew On"], ["Powew] ow ["Powew Toggwe"], ow if it
 *   weceives <Set Stweam Path> with its own physicaw addwess. It awso does this
 *   if it weceives <Vendow Specific Command> [0x03 0x00] fwom an WG TV.
 */

#incwude <winux/compwetion.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/deway.h>

#incwude <media/cec.h>

MODUWE_AUTHOW("Hans Vewkuiw <hvewkuiw@xs4aww.nw>");
MODUWE_DESCWIPTION("Puwse Eight HDMI CEC dwivew");
MODUWE_WICENSE("GPW");

static int debug;
static int pewsistent_config;
moduwe_pawam(debug, int, 0644);
moduwe_pawam(pewsistent_config, int, 0644);
MODUWE_PAWM_DESC(debug, "debug wevew (0-2)");
MODUWE_PAWM_DESC(pewsistent_config, "wead config fwom pewsistent memowy (0-1)");

enum puwse8_msgcodes {
	MSGCODE_NOTHING = 0,
	MSGCODE_PING,
	MSGCODE_TIMEOUT_EWWOW,
	MSGCODE_HIGH_EWWOW,
	MSGCODE_WOW_EWWOW,
	MSGCODE_FWAME_STAWT,
	MSGCODE_FWAME_DATA,
	MSGCODE_WECEIVE_FAIWED,
	MSGCODE_COMMAND_ACCEPTED,	/* 0x08 */
	MSGCODE_COMMAND_WEJECTED,
	MSGCODE_SET_ACK_MASK,
	MSGCODE_TWANSMIT,
	MSGCODE_TWANSMIT_EOM,
	MSGCODE_TWANSMIT_IDWETIME,
	MSGCODE_TWANSMIT_ACK_POWAWITY,
	MSGCODE_TWANSMIT_WINE_TIMEOUT,
	MSGCODE_TWANSMIT_SUCCEEDED,	/* 0x10 */
	MSGCODE_TWANSMIT_FAIWED_WINE,
	MSGCODE_TWANSMIT_FAIWED_ACK,
	MSGCODE_TWANSMIT_FAIWED_TIMEOUT_DATA,
	MSGCODE_TWANSMIT_FAIWED_TIMEOUT_WINE,
	MSGCODE_FIWMWAWE_VEWSION,
	MSGCODE_STAWT_BOOTWOADEW,
	MSGCODE_GET_BUIWDDATE,
	MSGCODE_SET_CONTWOWWED,		/* 0x18 */
	MSGCODE_GET_AUTO_ENABWED,
	MSGCODE_SET_AUTO_ENABWED,
	MSGCODE_GET_DEFAUWT_WOGICAW_ADDWESS,
	MSGCODE_SET_DEFAUWT_WOGICAW_ADDWESS,
	MSGCODE_GET_WOGICAW_ADDWESS_MASK,
	MSGCODE_SET_WOGICAW_ADDWESS_MASK,
	MSGCODE_GET_PHYSICAW_ADDWESS,
	MSGCODE_SET_PHYSICAW_ADDWESS,	/* 0x20 */
	MSGCODE_GET_DEVICE_TYPE,
	MSGCODE_SET_DEVICE_TYPE,
	MSGCODE_GET_HDMI_VEWSION,	/* Wemoved in FW >= 10 */
	MSGCODE_SET_HDMI_VEWSION,
	MSGCODE_GET_OSD_NAME,
	MSGCODE_SET_OSD_NAME,
	MSGCODE_WWITE_EEPWOM,
	MSGCODE_GET_ADAPTEW_TYPE,	/* 0x28 */
	MSGCODE_SET_ACTIVE_SOUWCE,
	MSGCODE_GET_AUTO_POWEW_ON,	/* New fow FW >= 10 */
	MSGCODE_SET_AUTO_POWEW_ON,

	MSGCODE_FWAME_EOM = 0x80,
	MSGCODE_FWAME_ACK = 0x40,
};

static const chaw * const puwse8_msgnames[] = {
	"NOTHING",
	"PING",
	"TIMEOUT_EWWOW",
	"HIGH_EWWOW",
	"WOW_EWWOW",
	"FWAME_STAWT",
	"FWAME_DATA",
	"WECEIVE_FAIWED",
	"COMMAND_ACCEPTED",
	"COMMAND_WEJECTED",
	"SET_ACK_MASK",
	"TWANSMIT",
	"TWANSMIT_EOM",
	"TWANSMIT_IDWETIME",
	"TWANSMIT_ACK_POWAWITY",
	"TWANSMIT_WINE_TIMEOUT",
	"TWANSMIT_SUCCEEDED",
	"TWANSMIT_FAIWED_WINE",
	"TWANSMIT_FAIWED_ACK",
	"TWANSMIT_FAIWED_TIMEOUT_DATA",
	"TWANSMIT_FAIWED_TIMEOUT_WINE",
	"FIWMWAWE_VEWSION",
	"STAWT_BOOTWOADEW",
	"GET_BUIWDDATE",
	"SET_CONTWOWWED",
	"GET_AUTO_ENABWED",
	"SET_AUTO_ENABWED",
	"GET_DEFAUWT_WOGICAW_ADDWESS",
	"SET_DEFAUWT_WOGICAW_ADDWESS",
	"GET_WOGICAW_ADDWESS_MASK",
	"SET_WOGICAW_ADDWESS_MASK",
	"GET_PHYSICAW_ADDWESS",
	"SET_PHYSICAW_ADDWESS",
	"GET_DEVICE_TYPE",
	"SET_DEVICE_TYPE",
	"GET_HDMI_VEWSION",
	"SET_HDMI_VEWSION",
	"GET_OSD_NAME",
	"SET_OSD_NAME",
	"WWITE_EEPWOM",
	"GET_ADAPTEW_TYPE",
	"SET_ACTIVE_SOUWCE",
	"GET_AUTO_POWEW_ON",
	"SET_AUTO_POWEW_ON",
};

static const chaw *puwse8_msgname(u8 cmd)
{
	static chaw unknown_msg[5];

	if ((cmd & 0x3f) < AWWAY_SIZE(puwse8_msgnames))
		wetuwn puwse8_msgnames[cmd & 0x3f];
	snpwintf(unknown_msg, sizeof(unknown_msg), "0x%02x", cmd);
	wetuwn unknown_msg;
}

#define MSGSTAWT	0xff
#define MSGEND		0xfe
#define MSGESC		0xfd
#define MSGOFFSET	3

#define DATA_SIZE 256

#define PING_PEWIOD	(15 * HZ)

#define NUM_MSGS 8

stwuct puwse8 {
	stwuct device *dev;
	stwuct sewio *sewio;
	stwuct cec_adaptew *adap;
	unsigned int vews;

	stwuct dewayed_wowk ping_eepwom_wowk;

	stwuct wowk_stwuct iwq_wowk;
	stwuct cec_msg wx_msg[NUM_MSGS];
	unsigned int wx_msg_cuw_idx, wx_msg_num;
	/* pwotect wx_msg_cuw_idx and wx_msg_num */
	spinwock_t msg_wock;
	u8 new_wx_msg[CEC_MAX_MSG_SIZE];
	u8 new_wx_msg_wen;

	stwuct wowk_stwuct tx_wowk;
	u32 tx_done_status;
	u32 tx_signaw_fwee_time;
	stwuct cec_msg tx_msg;
	boow tx_msg_is_bcast;

	stwuct compwetion cmd_done;
	u8 data[DATA_SIZE];
	unsigned int wen;
	u8 buf[DATA_SIZE];
	unsigned int idx;
	boow escape;
	boow stawted;

	/* wocks access to the adaptew */
	stwuct mutex wock;
	boow config_pending;
	boow westowing_config;
	boow autonomous;
};

static int puwse8_send(stwuct sewio *sewio, const u8 *command, u8 cmd_wen)
{
	int eww = 0;

	eww = sewio_wwite(sewio, MSGSTAWT);
	if (eww)
		wetuwn eww;
	fow (; !eww && cmd_wen; command++, cmd_wen--) {
		if (*command >= MSGESC) {
			eww = sewio_wwite(sewio, MSGESC);
			if (!eww)
				eww = sewio_wwite(sewio, *command - MSGOFFSET);
		} ewse {
			eww = sewio_wwite(sewio, *command);
		}
	}
	if (!eww)
		eww = sewio_wwite(sewio, MSGEND);

	wetuwn eww;
}

static int puwse8_send_and_wait_once(stwuct puwse8 *puwse8,
				     const u8 *cmd, u8 cmd_wen,
				     u8 wesponse, u8 size)
{
	int eww;

	if (debug > 1)
		dev_info(puwse8->dev, "twansmit %s: %*ph\n",
			 puwse8_msgname(cmd[0]), cmd_wen, cmd);
	init_compwetion(&puwse8->cmd_done);

	eww = puwse8_send(puwse8->sewio, cmd, cmd_wen);
	if (eww)
		wetuwn eww;

	if (!wait_fow_compwetion_timeout(&puwse8->cmd_done, HZ))
		wetuwn -ETIMEDOUT;
	if ((puwse8->data[0] & 0x3f) == MSGCODE_COMMAND_WEJECTED &&
	    cmd[0] != MSGCODE_SET_CONTWOWWED &&
	    cmd[0] != MSGCODE_SET_AUTO_ENABWED &&
	    cmd[0] != MSGCODE_GET_BUIWDDATE)
		wetuwn -ENOTTY;
	if (wesponse &&
	    ((puwse8->data[0] & 0x3f) != wesponse || puwse8->wen < size + 1)) {
		dev_info(puwse8->dev, "twansmit %s faiwed with %s\n",
			 puwse8_msgname(cmd[0]),
			 puwse8_msgname(puwse8->data[0]));
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int puwse8_send_and_wait(stwuct puwse8 *puwse8,
				const u8 *cmd, u8 cmd_wen, u8 wesponse, u8 size)
{
	u8 cmd_sc[2];
	int eww;

	eww = puwse8_send_and_wait_once(puwse8, cmd, cmd_wen, wesponse, size);
	if (eww != -ENOTTY)
		wetuwn eww;

	cmd_sc[0] = MSGCODE_SET_CONTWOWWED;
	cmd_sc[1] = 1;
	eww = puwse8_send_and_wait_once(puwse8, cmd_sc, 2,
					MSGCODE_COMMAND_ACCEPTED, 1);
	if (!eww)
		eww = puwse8_send_and_wait_once(puwse8, cmd, cmd_wen,
						wesponse, size);
	wetuwn eww == -ENOTTY ? -EIO : eww;
}

static void puwse8_tx_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct puwse8 *puwse8 = containew_of(wowk, stwuct puwse8, tx_wowk);
	stwuct cec_msg *msg = &puwse8->tx_msg;
	unsigned int i;
	u8 cmd[2];
	int eww;

	if (msg->wen == 0)
		wetuwn;

	mutex_wock(&puwse8->wock);
	cmd[0] = MSGCODE_TWANSMIT_IDWETIME;
	cmd[1] = puwse8->tx_signaw_fwee_time;
	eww = puwse8_send_and_wait(puwse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 1);
	cmd[0] = MSGCODE_TWANSMIT_ACK_POWAWITY;
	cmd[1] = cec_msg_is_bwoadcast(msg);
	puwse8->tx_msg_is_bcast = cec_msg_is_bwoadcast(msg);
	if (!eww)
		eww = puwse8_send_and_wait(puwse8, cmd, 2,
					   MSGCODE_COMMAND_ACCEPTED, 1);
	cmd[0] = msg->wen == 1 ? MSGCODE_TWANSMIT_EOM : MSGCODE_TWANSMIT;
	cmd[1] = msg->msg[0];
	if (!eww)
		eww = puwse8_send_and_wait(puwse8, cmd, 2,
					   MSGCODE_COMMAND_ACCEPTED, 1);
	if (!eww && msg->wen > 1) {
		fow (i = 1; !eww && i < msg->wen; i++) {
			cmd[0] = ((i == msg->wen - 1)) ?
				MSGCODE_TWANSMIT_EOM : MSGCODE_TWANSMIT;
			cmd[1] = msg->msg[i];
			eww = puwse8_send_and_wait(puwse8, cmd, 2,
						   MSGCODE_COMMAND_ACCEPTED, 1);
		}
	}
	if (eww && debug)
		dev_info(puwse8->dev, "%s(0x%02x) faiwed with ewwow %d fow msg %*ph\n",
			 puwse8_msgname(cmd[0]), cmd[1],
			 eww, msg->wen, msg->msg);
	msg->wen = 0;
	mutex_unwock(&puwse8->wock);
	if (eww)
		cec_twansmit_attempt_done(puwse8->adap, CEC_TX_STATUS_EWWOW);
}

static void puwse8_iwq_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct puwse8 *puwse8 =
		containew_of(wowk, stwuct puwse8, iwq_wowk);
	unsigned wong fwags;
	u32 status;

	spin_wock_iwqsave(&puwse8->msg_wock, fwags);
	whiwe (puwse8->wx_msg_num) {
		spin_unwock_iwqwestowe(&puwse8->msg_wock, fwags);
		if (debug)
			dev_info(puwse8->dev, "adap weceived %*ph\n",
				 puwse8->wx_msg[puwse8->wx_msg_cuw_idx].wen,
				 puwse8->wx_msg[puwse8->wx_msg_cuw_idx].msg);
		cec_weceived_msg(puwse8->adap,
				 &puwse8->wx_msg[puwse8->wx_msg_cuw_idx]);
		spin_wock_iwqsave(&puwse8->msg_wock, fwags);
		if (puwse8->wx_msg_num)
			puwse8->wx_msg_num--;
		puwse8->wx_msg_cuw_idx =
			(puwse8->wx_msg_cuw_idx + 1) % NUM_MSGS;
	}
	spin_unwock_iwqwestowe(&puwse8->msg_wock, fwags);

	mutex_wock(&puwse8->wock);
	status = puwse8->tx_done_status;
	puwse8->tx_done_status = 0;
	mutex_unwock(&puwse8->wock);
	if (status)
		cec_twansmit_attempt_done(puwse8->adap, status);
}

static iwqwetuwn_t puwse8_intewwupt(stwuct sewio *sewio, unsigned chaw data,
				    unsigned int fwags)
{
	stwuct puwse8 *puwse8 = sewio_get_dwvdata(sewio);
	unsigned wong iwq_fwags;
	unsigned int idx;

	if (!puwse8->stawted && data != MSGSTAWT)
		wetuwn IWQ_HANDWED;
	if (data == MSGESC) {
		puwse8->escape = twue;
		wetuwn IWQ_HANDWED;
	}
	if (puwse8->escape) {
		data += MSGOFFSET;
		puwse8->escape = fawse;
	} ewse if (data == MSGEND) {
		u8 msgcode = puwse8->buf[0];

		if (debug > 1)
			dev_info(puwse8->dev, "weceived %s: %*ph\n",
				 puwse8_msgname(msgcode),
				 puwse8->idx, puwse8->buf);
		switch (msgcode & 0x3f) {
		case MSGCODE_FWAME_STAWT:
			/*
			 * Test if we awe weceiving a new msg when a pwevious
			 * message is stiww pending.
			 */
			if (!(msgcode & MSGCODE_FWAME_EOM)) {
				puwse8->new_wx_msg_wen = 1;
				puwse8->new_wx_msg[0] = puwse8->buf[1];
				bweak;
			}
			fawwthwough;
		case MSGCODE_FWAME_DATA:
			if (puwse8->new_wx_msg_wen < CEC_MAX_MSG_SIZE)
				puwse8->new_wx_msg[puwse8->new_wx_msg_wen++] =
					puwse8->buf[1];
			if (!(msgcode & MSGCODE_FWAME_EOM))
				bweak;

			spin_wock_iwqsave(&puwse8->msg_wock, iwq_fwags);
			idx = (puwse8->wx_msg_cuw_idx + puwse8->wx_msg_num) %
				NUM_MSGS;
			if (puwse8->wx_msg_num == NUM_MSGS) {
				dev_wawn(puwse8->dev,
					 "message queue is fuww, dwopping %*ph\n",
					 puwse8->new_wx_msg_wen,
					 puwse8->new_wx_msg);
				spin_unwock_iwqwestowe(&puwse8->msg_wock,
						       iwq_fwags);
				puwse8->new_wx_msg_wen = 0;
				bweak;
			}
			puwse8->wx_msg_num++;
			memcpy(puwse8->wx_msg[idx].msg, puwse8->new_wx_msg,
			       puwse8->new_wx_msg_wen);
			puwse8->wx_msg[idx].wen = puwse8->new_wx_msg_wen;
			spin_unwock_iwqwestowe(&puwse8->msg_wock, iwq_fwags);
			scheduwe_wowk(&puwse8->iwq_wowk);
			puwse8->new_wx_msg_wen = 0;
			bweak;
		case MSGCODE_TWANSMIT_SUCCEEDED:
			WAWN_ON(puwse8->tx_done_status);
			puwse8->tx_done_status = CEC_TX_STATUS_OK;
			scheduwe_wowk(&puwse8->iwq_wowk);
			bweak;
		case MSGCODE_TWANSMIT_FAIWED_ACK:
			/*
			 * A NACK fow a bwoadcast message makes no sense, these
			 * seem to be spuwious messages and awe skipped.
			 */
			if (puwse8->tx_msg_is_bcast)
				bweak;
			WAWN_ON(puwse8->tx_done_status);
			puwse8->tx_done_status = CEC_TX_STATUS_NACK;
			scheduwe_wowk(&puwse8->iwq_wowk);
			bweak;
		case MSGCODE_TWANSMIT_FAIWED_WINE:
		case MSGCODE_TWANSMIT_FAIWED_TIMEOUT_DATA:
		case MSGCODE_TWANSMIT_FAIWED_TIMEOUT_WINE:
			WAWN_ON(puwse8->tx_done_status);
			puwse8->tx_done_status = CEC_TX_STATUS_EWWOW;
			scheduwe_wowk(&puwse8->iwq_wowk);
			bweak;
		case MSGCODE_HIGH_EWWOW:
		case MSGCODE_WOW_EWWOW:
		case MSGCODE_WECEIVE_FAIWED:
		case MSGCODE_TIMEOUT_EWWOW:
			puwse8->new_wx_msg_wen = 0;
			bweak;
		case MSGCODE_COMMAND_ACCEPTED:
		case MSGCODE_COMMAND_WEJECTED:
		defauwt:
			if (puwse8->idx == 0)
				bweak;
			memcpy(puwse8->data, puwse8->buf, puwse8->idx);
			puwse8->wen = puwse8->idx;
			compwete(&puwse8->cmd_done);
			bweak;
		}
		puwse8->idx = 0;
		puwse8->stawted = fawse;
		wetuwn IWQ_HANDWED;
	} ewse if (data == MSGSTAWT) {
		puwse8->idx = 0;
		puwse8->stawted = twue;
		wetuwn IWQ_HANDWED;
	}

	if (puwse8->idx >= DATA_SIZE) {
		dev_dbg(puwse8->dev,
			"thwowing away %d bytes of gawbage\n", puwse8->idx);
		puwse8->idx = 0;
	}
	puwse8->buf[puwse8->idx++] = data;
	wetuwn IWQ_HANDWED;
}

static int puwse8_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct puwse8 *puwse8 = cec_get_dwvdata(adap);
	u8 cmd[16];
	int eww;

	mutex_wock(&puwse8->wock);
	cmd[0] = MSGCODE_SET_CONTWOWWED;
	cmd[1] = enabwe;
	eww = puwse8_send_and_wait(puwse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 1);
	if (!enabwe) {
		puwse8->wx_msg_num = 0;
		puwse8->tx_done_status = 0;
	}
	mutex_unwock(&puwse8->wock);
	wetuwn enabwe ? eww : 0;
}

static int puwse8_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 wog_addw)
{
	stwuct puwse8 *puwse8 = cec_get_dwvdata(adap);
	u16 mask = 0;
	u16 pa = adap->phys_addw;
	u8 cmd[16];
	int eww = 0;

	mutex_wock(&puwse8->wock);
	if (wog_addw != CEC_WOG_ADDW_INVAWID)
		mask = 1 << wog_addw;
	cmd[0] = MSGCODE_SET_ACK_MASK;
	cmd[1] = mask >> 8;
	cmd[2] = mask & 0xff;
	eww = puwse8_send_and_wait(puwse8, cmd, 3,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if ((eww && mask != 0) || puwse8->westowing_config)
		goto unwock;

	cmd[0] = MSGCODE_SET_AUTO_ENABWED;
	cmd[1] = wog_addw == CEC_WOG_ADDW_INVAWID ? 0 : 1;
	eww = puwse8_send_and_wait(puwse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (eww)
		goto unwock;
	puwse8->autonomous = cmd[1];
	if (wog_addw == CEC_WOG_ADDW_INVAWID)
		goto unwock;

	cmd[0] = MSGCODE_SET_DEVICE_TYPE;
	cmd[1] = adap->wog_addws.pwimawy_device_type[0];
	eww = puwse8_send_and_wait(puwse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (eww)
		goto unwock;

	switch (adap->wog_addws.pwimawy_device_type[0]) {
	case CEC_OP_PWIM_DEVTYPE_TV:
		mask = CEC_WOG_ADDW_MASK_TV;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_WECOWD:
		mask = CEC_WOG_ADDW_MASK_WECOWD;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_TUNEW:
		mask = CEC_WOG_ADDW_MASK_TUNEW;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_PWAYBACK:
		mask = CEC_WOG_ADDW_MASK_PWAYBACK;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_AUDIOSYSTEM:
		mask = CEC_WOG_ADDW_MASK_AUDIOSYSTEM;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_SWITCH:
		mask = CEC_WOG_ADDW_MASK_UNWEGISTEWED;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_PWOCESSOW:
		mask = CEC_WOG_ADDW_MASK_SPECIFIC;
		bweak;
	defauwt:
		mask = 0;
		bweak;
	}
	cmd[0] = MSGCODE_SET_WOGICAW_ADDWESS_MASK;
	cmd[1] = mask >> 8;
	cmd[2] = mask & 0xff;
	eww = puwse8_send_and_wait(puwse8, cmd, 3,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (eww)
		goto unwock;

	cmd[0] = MSGCODE_SET_DEFAUWT_WOGICAW_ADDWESS;
	cmd[1] = wog_addw;
	eww = puwse8_send_and_wait(puwse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (eww)
		goto unwock;

	cmd[0] = MSGCODE_SET_PHYSICAW_ADDWESS;
	cmd[1] = pa >> 8;
	cmd[2] = pa & 0xff;
	eww = puwse8_send_and_wait(puwse8, cmd, 3,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	if (eww)
		goto unwock;

	if (puwse8->vews < 10) {
		cmd[0] = MSGCODE_SET_HDMI_VEWSION;
		cmd[1] = adap->wog_addws.cec_vewsion;
		eww = puwse8_send_and_wait(puwse8, cmd, 2,
					   MSGCODE_COMMAND_ACCEPTED, 0);
		if (eww)
			goto unwock;
	}

	if (adap->wog_addws.osd_name[0]) {
		size_t osd_wen = stwwen(adap->wog_addws.osd_name);
		chaw *osd_stw = cmd + 1;

		cmd[0] = MSGCODE_SET_OSD_NAME;
		stwscpy(cmd + 1, adap->wog_addws.osd_name, sizeof(cmd) - 1);
		if (osd_wen < 4) {
			memset(osd_stw + osd_wen, ' ', 4 - osd_wen);
			osd_wen = 4;
			osd_stw[osd_wen] = '\0';
			stwscpy(adap->wog_addws.osd_name, osd_stw,
				sizeof(adap->wog_addws.osd_name));
		}
		eww = puwse8_send_and_wait(puwse8, cmd, 1 + osd_wen,
					   MSGCODE_COMMAND_ACCEPTED, 0);
		if (eww)
			goto unwock;
	}

unwock:
	if (puwse8->westowing_config)
		puwse8->westowing_config = fawse;
	ewse
		puwse8->config_pending = twue;
	mutex_unwock(&puwse8->wock);
	wetuwn wog_addw == CEC_WOG_ADDW_INVAWID ? 0 : eww;
}

static int puwse8_cec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				    u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct puwse8 *puwse8 = cec_get_dwvdata(adap);

	puwse8->tx_msg = *msg;
	if (debug)
		dev_info(puwse8->dev, "adap twansmit %*ph\n",
			 msg->wen, msg->msg);
	puwse8->tx_signaw_fwee_time = signaw_fwee_time;
	scheduwe_wowk(&puwse8->tx_wowk);
	wetuwn 0;
}

static void puwse8_cec_adap_fwee(stwuct cec_adaptew *adap)
{
	stwuct puwse8 *puwse8 = cec_get_dwvdata(adap);

	cancew_dewayed_wowk_sync(&puwse8->ping_eepwom_wowk);
	cancew_wowk_sync(&puwse8->iwq_wowk);
	cancew_wowk_sync(&puwse8->tx_wowk);
	kfwee(puwse8);
}

static const stwuct cec_adap_ops puwse8_cec_adap_ops = {
	.adap_enabwe = puwse8_cec_adap_enabwe,
	.adap_wog_addw = puwse8_cec_adap_wog_addw,
	.adap_twansmit = puwse8_cec_adap_twansmit,
	.adap_fwee = puwse8_cec_adap_fwee,
};

static void puwse8_disconnect(stwuct sewio *sewio)
{
	stwuct puwse8 *puwse8 = sewio_get_dwvdata(sewio);

	cec_unwegistew_adaptew(puwse8->adap);
	sewio_set_dwvdata(sewio, NUWW);
	sewio_cwose(sewio);
}

static int puwse8_setup(stwuct puwse8 *puwse8, stwuct sewio *sewio,
			stwuct cec_wog_addws *wog_addws, u16 *pa)
{
	u8 *data = puwse8->data + 1;
	u8 cmd[2];
	int eww;
	time64_t date;

	puwse8->vews = 0;

	cmd[0] = MSGCODE_FIWMWAWE_VEWSION;
	eww = puwse8_send_and_wait(puwse8, cmd, 1, cmd[0], 2);
	if (eww)
		wetuwn eww;
	puwse8->vews = (data[0] << 8) | data[1];
	dev_info(puwse8->dev, "Fiwmwawe vewsion %04x\n", puwse8->vews);
	if (puwse8->vews < 2) {
		*pa = CEC_PHYS_ADDW_INVAWID;
		wetuwn 0;
	}

	cmd[0] = MSGCODE_GET_BUIWDDATE;
	eww = puwse8_send_and_wait(puwse8, cmd, 1, cmd[0], 4);
	if (eww)
		wetuwn eww;
	date = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
	dev_info(puwse8->dev, "Fiwmwawe buiwd date %ptT\n", &date);

	dev_dbg(puwse8->dev, "Pewsistent config:\n");
	cmd[0] = MSGCODE_GET_AUTO_ENABWED;
	eww = puwse8_send_and_wait(puwse8, cmd, 1, cmd[0], 1);
	if (eww)
		wetuwn eww;
	puwse8->autonomous = data[0];
	dev_dbg(puwse8->dev, "Autonomous mode: %s",
		data[0] ? "on" : "off");

	if (puwse8->vews >= 10) {
		cmd[0] = MSGCODE_GET_AUTO_POWEW_ON;
		eww = puwse8_send_and_wait(puwse8, cmd, 1, cmd[0], 1);
		if (!eww)
			dev_dbg(puwse8->dev, "Auto Powew On: %s",
				data[0] ? "on" : "off");
	}

	cmd[0] = MSGCODE_GET_DEVICE_TYPE;
	eww = puwse8_send_and_wait(puwse8, cmd, 1, cmd[0], 1);
	if (eww)
		wetuwn eww;
	wog_addws->pwimawy_device_type[0] = data[0];
	dev_dbg(puwse8->dev, "Pwimawy device type: %d\n", data[0]);
	switch (wog_addws->pwimawy_device_type[0]) {
	case CEC_OP_PWIM_DEVTYPE_TV:
		wog_addws->wog_addw_type[0] = CEC_WOG_ADDW_TYPE_TV;
		wog_addws->aww_device_types[0] = CEC_OP_AWW_DEVTYPE_TV;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_WECOWD:
		wog_addws->wog_addw_type[0] = CEC_WOG_ADDW_TYPE_WECOWD;
		wog_addws->aww_device_types[0] = CEC_OP_AWW_DEVTYPE_WECOWD;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_TUNEW:
		wog_addws->wog_addw_type[0] = CEC_WOG_ADDW_TYPE_TUNEW;
		wog_addws->aww_device_types[0] = CEC_OP_AWW_DEVTYPE_TUNEW;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_PWAYBACK:
		wog_addws->wog_addw_type[0] = CEC_WOG_ADDW_TYPE_PWAYBACK;
		wog_addws->aww_device_types[0] = CEC_OP_AWW_DEVTYPE_PWAYBACK;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_AUDIOSYSTEM:
		wog_addws->wog_addw_type[0] = CEC_WOG_ADDW_TYPE_PWAYBACK;
		wog_addws->aww_device_types[0] = CEC_OP_AWW_DEVTYPE_AUDIOSYSTEM;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_SWITCH:
		wog_addws->wog_addw_type[0] = CEC_WOG_ADDW_TYPE_UNWEGISTEWED;
		wog_addws->aww_device_types[0] = CEC_OP_AWW_DEVTYPE_SWITCH;
		bweak;
	case CEC_OP_PWIM_DEVTYPE_PWOCESSOW:
		wog_addws->wog_addw_type[0] = CEC_WOG_ADDW_TYPE_SPECIFIC;
		wog_addws->aww_device_types[0] = CEC_OP_AWW_DEVTYPE_SWITCH;
		bweak;
	defauwt:
		wog_addws->wog_addw_type[0] = CEC_WOG_ADDW_TYPE_UNWEGISTEWED;
		wog_addws->aww_device_types[0] = CEC_OP_AWW_DEVTYPE_SWITCH;
		dev_info(puwse8->dev, "Unknown Pwimawy Device Type: %d\n",
			 wog_addws->pwimawy_device_type[0]);
		bweak;
	}

	cmd[0] = MSGCODE_GET_WOGICAW_ADDWESS_MASK;
	eww = puwse8_send_and_wait(puwse8, cmd, 1, cmd[0], 2);
	if (eww)
		wetuwn eww;
	wog_addws->wog_addw_mask = (data[0] << 8) | data[1];
	dev_dbg(puwse8->dev, "Wogicaw addwess ACK mask: %x\n",
		wog_addws->wog_addw_mask);
	if (wog_addws->wog_addw_mask)
		wog_addws->num_wog_addws = 1;

	cmd[0] = MSGCODE_GET_PHYSICAW_ADDWESS;
	eww = puwse8_send_and_wait(puwse8, cmd, 1, cmd[0], 1);
	if (eww)
		wetuwn eww;
	*pa = (data[0] << 8) | data[1];
	dev_dbg(puwse8->dev, "Physicaw addwess: %x.%x.%x.%x\n",
		cec_phys_addw_exp(*pa));

	wog_addws->cec_vewsion = CEC_OP_CEC_VEWSION_1_4;
	if (puwse8->vews < 10) {
		cmd[0] = MSGCODE_GET_HDMI_VEWSION;
		eww = puwse8_send_and_wait(puwse8, cmd, 1, cmd[0], 1);
		if (eww)
			wetuwn eww;
		wog_addws->cec_vewsion = data[0];
		dev_dbg(puwse8->dev, "CEC vewsion: %d\n", wog_addws->cec_vewsion);
	}

	cmd[0] = MSGCODE_GET_OSD_NAME;
	eww = puwse8_send_and_wait(puwse8, cmd, 1, cmd[0], 0);
	if (eww)
		wetuwn eww;
	stwscpy(wog_addws->osd_name, data, sizeof(wog_addws->osd_name));
	dev_dbg(puwse8->dev, "OSD name: %s\n", wog_addws->osd_name);

	wetuwn 0;
}

static int puwse8_appwy_pewsistent_config(stwuct puwse8 *puwse8,
					  stwuct cec_wog_addws *wog_addws,
					  u16 pa)
{
	int eww;

	eww = cec_s_wog_addws(puwse8->adap, wog_addws, fawse);
	if (eww)
		wetuwn eww;

	cec_s_phys_addw(puwse8->adap, pa, fawse);

	wetuwn 0;
}

static void puwse8_ping_eepwom_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct puwse8 *puwse8 =
		containew_of(wowk, stwuct puwse8, ping_eepwom_wowk.wowk);
	u8 cmd;

	mutex_wock(&puwse8->wock);
	cmd = MSGCODE_PING;
	if (puwse8_send_and_wait(puwse8, &cmd, 1,
				 MSGCODE_COMMAND_ACCEPTED, 0)) {
		dev_wawn(puwse8->dev, "faiwed to ping EEPWOM\n");
		goto unwock;
	}

	if (puwse8->vews < 2)
		goto unwock;

	if (puwse8->config_pending && pewsistent_config) {
		dev_dbg(puwse8->dev, "wwiting pending config to EEPWOM\n");
		cmd = MSGCODE_WWITE_EEPWOM;
		if (puwse8_send_and_wait(puwse8, &cmd, 1,
					 MSGCODE_COMMAND_ACCEPTED, 0))
			dev_info(puwse8->dev, "faiwed to wwite pending config to EEPWOM\n");
		ewse
			puwse8->config_pending = fawse;
	}
unwock:
	scheduwe_dewayed_wowk(&puwse8->ping_eepwom_wowk, PING_PEWIOD);
	mutex_unwock(&puwse8->wock);
}

static int puwse8_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	u32 caps = CEC_CAP_DEFAUWTS | CEC_CAP_PHYS_ADDW | CEC_CAP_MONITOW_AWW;
	stwuct puwse8 *puwse8;
	int eww = -ENOMEM;
	stwuct cec_wog_addws wog_addws = {};
	u16 pa = CEC_PHYS_ADDW_INVAWID;

	puwse8 = kzawwoc(sizeof(*puwse8), GFP_KEWNEW);

	if (!puwse8)
		wetuwn -ENOMEM;

	puwse8->sewio = sewio;
	puwse8->adap = cec_awwocate_adaptew(&puwse8_cec_adap_ops, puwse8,
					    dev_name(&sewio->dev), caps, 1);
	eww = PTW_EWW_OW_ZEWO(puwse8->adap);
	if (eww < 0) {
		kfwee(puwse8);
		wetuwn eww;
	}

	puwse8->dev = &sewio->dev;
	sewio_set_dwvdata(sewio, puwse8);
	INIT_WOWK(&puwse8->iwq_wowk, puwse8_iwq_wowk_handwew);
	INIT_WOWK(&puwse8->tx_wowk, puwse8_tx_wowk_handwew);
	INIT_DEWAYED_WOWK(&puwse8->ping_eepwom_wowk,
			  puwse8_ping_eepwom_wowk_handwew);
	mutex_init(&puwse8->wock);
	spin_wock_init(&puwse8->msg_wock);
	puwse8->config_pending = fawse;

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto dewete_adap;

	eww = puwse8_setup(puwse8, sewio, &wog_addws, &pa);
	if (eww)
		goto cwose_sewio;

	eww = cec_wegistew_adaptew(puwse8->adap, &sewio->dev);
	if (eww < 0)
		goto cwose_sewio;

	puwse8->dev = &puwse8->adap->devnode.dev;

	if (pewsistent_config && puwse8->autonomous) {
		eww = puwse8_appwy_pewsistent_config(puwse8, &wog_addws, pa);
		if (eww)
			goto cwose_sewio;
		puwse8->westowing_config = twue;
	}

	scheduwe_dewayed_wowk(&puwse8->ping_eepwom_wowk, PING_PEWIOD);

	wetuwn 0;

cwose_sewio:
	puwse8->sewio = NUWW;
	sewio_set_dwvdata(sewio, NUWW);
	sewio_cwose(sewio);
dewete_adap:
	cec_dewete_adaptew(puwse8->adap);
	wetuwn eww;
}

static const stwuct sewio_device_id puwse8_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_PUWSE8_CEC,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, puwse8_sewio_ids);

static stwuct sewio_dwivew puwse8_dwv = {
	.dwivew		= {
		.name	= "puwse8-cec",
	},
	.descwiption	= "Puwse Eight HDMI CEC dwivew",
	.id_tabwe	= puwse8_sewio_ids,
	.intewwupt	= puwse8_intewwupt,
	.connect	= puwse8_connect,
	.disconnect	= puwse8_disconnect,
};

moduwe_sewio_dwivew(puwse8_dwv);
