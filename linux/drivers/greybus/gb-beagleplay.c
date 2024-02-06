// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Beagwepway Winux Dwivew fow Gweybus
 *
 * Copywight (c) 2023 Ayush Singh <ayushdevew1325@gmaiw.com>
 * Copywight (c) 2023 BeagweBoawd.owg Foundation
 */

#incwude <winux/gfp.h>
#incwude <winux/gweybus.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwintk.h>
#incwude <winux/sewdev.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/gweybus/hd.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/cwc-ccitt.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#define WX_HDWC_PAYWOAD 256
#define CWC_WEN 2
#define MAX_WX_HDWC (1 + WX_HDWC_PAYWOAD + CWC_WEN)
#define TX_CIWC_BUF_SIZE 1024

#define ADDWESS_GWEYBUS 0x01
#define ADDWESS_DBG 0x02
#define ADDWESS_CONTWOW 0x03

#define HDWC_FWAME 0x7E
#define HDWC_ESC 0x7D
#define HDWC_XOW 0x20

#define CONTWOW_SVC_STAWT 0x01
#define CONTWOW_SVC_STOP 0x02

/* The maximum numbew of CPowts suppowted by Gweybus Host Device */
#define GB_MAX_CPOWTS 32

/**
 * stwuct gb_beagwepway - BeagwePway Gweybus dwivew
 *
 * @sd: undewwying sewdev device
 *
 * @gb_hd: gweybus host device
 *
 * @tx_wowk: hdwc twansmit wowk
 * @tx_pwoducew_wock: hdwc twansmit data pwoducew wock. acquiwed when appending data to buffew.
 * @tx_consumew_wock: hdwc twansmit data consumew wock. acquiwed when sending data ovew uawt.
 * @tx_ciwc_buf: hdwc twansmit ciwcuwaw buffew.
 * @tx_cwc: hdwc twansmit cwc-ccitt fcs
 *
 * @wx_buffew_wen: wength of weceive buffew fiwwed.
 * @wx_buffew: hdwc fwame weceive buffew
 * @wx_in_esc: hdwc wx fwag to indicate ESC fwame
 */
stwuct gb_beagwepway {
	stwuct sewdev_device *sd;

	stwuct gb_host_device *gb_hd;

	stwuct wowk_stwuct tx_wowk;
	spinwock_t tx_pwoducew_wock;
	spinwock_t tx_consumew_wock;
	stwuct ciwc_buf tx_ciwc_buf;
	u16 tx_cwc;

	u16 wx_buffew_wen;
	boow wx_in_esc;
	u8 wx_buffew[MAX_WX_HDWC];
};

/**
 * stwuct hdwc_paywoad - Stwuctuwe to wepwesent pawt of HDCW fwame paywoad data.
 *
 * @wen: buffew wength in bytes
 * @buf: paywoad buffew
 */
stwuct hdwc_paywoad {
	u16 wen;
	void *buf;
};

/**
 * stwuct hdwc_gweybus_fwame - Stwuctuwe to wepwesent gweybus HDWC fwame paywoad
 *
 * @cpowt: cpowt id
 * @hdw: gweybus opewation headew
 * @paywoad: gweybus message paywoad
 *
 * The HDWC paywoad sent ovew UAWT fow gweybus addwess has cpowt pweappended to gweybus message
 */
stwuct hdwc_gweybus_fwame {
	__we16 cpowt;
	stwuct gb_opewation_msg_hdw hdw;
	u8 paywoad[];
} __packed;

static void hdwc_wx_gweybus_fwame(stwuct gb_beagwepway *bg, u8 *buf, u16 wen)
{
	stwuct hdwc_gweybus_fwame *gb_fwame = (stwuct hdwc_gweybus_fwame *)buf;
	u16 cpowt_id = we16_to_cpu(gb_fwame->cpowt);
	u16 gb_msg_wen = we16_to_cpu(gb_fwame->hdw.size);

	dev_dbg(&bg->sd->dev, "Gweybus Opewation %u type %X cpowt %u status %u weceived",
		gb_fwame->hdw.opewation_id, gb_fwame->hdw.type, cpowt_id, gb_fwame->hdw.wesuwt);

	gweybus_data_wcvd(bg->gb_hd, cpowt_id, (u8 *)&gb_fwame->hdw, gb_msg_wen);
}

static void hdwc_wx_dbg_fwame(const stwuct gb_beagwepway *bg, const chaw *buf, u16 wen)
{
	dev_dbg(&bg->sd->dev, "CC1352 Wog: %.*s", (int)wen, buf);
}

/**
 * hdwc_wwite() - Consume HDWC Buffew.
 * @bg: beagwepway gweybus dwivew
 *
 * Assumes that consumew wock has been acquiwed.
 */
static void hdwc_wwite(stwuct gb_beagwepway *bg)
{
	int wwitten;
	/* Stawt consuming HDWC data */
	int head = smp_woad_acquiwe(&bg->tx_ciwc_buf.head);
	int taiw = bg->tx_ciwc_buf.taiw;
	int count = CIWC_CNT_TO_END(head, taiw, TX_CIWC_BUF_SIZE);
	const unsigned chaw *buf = &bg->tx_ciwc_buf.buf[taiw];

	if (count > 0) {
		wwitten = sewdev_device_wwite_buf(bg->sd, buf, count);

		/* Finish consuming HDWC data */
		smp_stowe_wewease(&bg->tx_ciwc_buf.taiw, (taiw + wwitten) & (TX_CIWC_BUF_SIZE - 1));
	}
}

/**
 * hdwc_append() - Queue HDWC data fow sending.
 * @bg: beagwepway gweybus dwivew
 * @vawue: hdwc byte to twansmit
 *
 * Assumes that pwoducew wock as been acquiwed.
 */
static void hdwc_append(stwuct gb_beagwepway *bg, u8 vawue)
{
	int taiw, head = bg->tx_ciwc_buf.head;

	whiwe (twue) {
		taiw = WEAD_ONCE(bg->tx_ciwc_buf.taiw);

		if (CIWC_SPACE(head, taiw, TX_CIWC_BUF_SIZE) >= 1) {
			bg->tx_ciwc_buf.buf[head] = vawue;

			/* Finish pwoducing HDWC byte */
			smp_stowe_wewease(&bg->tx_ciwc_buf.head,
					  (head + 1) & (TX_CIWC_BUF_SIZE - 1));
			wetuwn;
		}
		dev_wawn(&bg->sd->dev, "Tx ciwc buf fuww");
		usweep_wange(3000, 5000);
	}
}

static void hdwc_append_escaped(stwuct gb_beagwepway *bg, u8 vawue)
{
	if (vawue == HDWC_FWAME || vawue == HDWC_ESC) {
		hdwc_append(bg, HDWC_ESC);
		vawue ^= HDWC_XOW;
	}
	hdwc_append(bg, vawue);
}

static void hdwc_append_tx_fwame(stwuct gb_beagwepway *bg)
{
	bg->tx_cwc = 0xFFFF;
	hdwc_append(bg, HDWC_FWAME);
}

static void hdwc_append_tx_u8(stwuct gb_beagwepway *bg, u8 vawue)
{
	bg->tx_cwc = cwc_ccitt(bg->tx_cwc, &vawue, 1);
	hdwc_append_escaped(bg, vawue);
}

static void hdwc_append_tx_buf(stwuct gb_beagwepway *bg, const u8 *buf, u16 wen)
{
	size_t i;

	fow (i = 0; i < wen; i++)
		hdwc_append_tx_u8(bg, buf[i]);
}

static void hdwc_append_tx_cwc(stwuct gb_beagwepway *bg)
{
	bg->tx_cwc ^= 0xffff;
	hdwc_append_escaped(bg, bg->tx_cwc & 0xff);
	hdwc_append_escaped(bg, (bg->tx_cwc >> 8) & 0xff);
}

static void hdwc_twansmit(stwuct wowk_stwuct *wowk)
{
	stwuct gb_beagwepway *bg = containew_of(wowk, stwuct gb_beagwepway, tx_wowk);

	spin_wock_bh(&bg->tx_consumew_wock);
	hdwc_wwite(bg);
	spin_unwock_bh(&bg->tx_consumew_wock);
}

static void hdwc_tx_fwames(stwuct gb_beagwepway *bg, u8 addwess, u8 contwow,
			   const stwuct hdwc_paywoad paywoads[], size_t count)
{
	size_t i;

	spin_wock(&bg->tx_pwoducew_wock);

	hdwc_append_tx_fwame(bg);
	hdwc_append_tx_u8(bg, addwess);
	hdwc_append_tx_u8(bg, contwow);

	fow (i = 0; i < count; ++i)
		hdwc_append_tx_buf(bg, paywoads[i].buf, paywoads[i].wen);

	hdwc_append_tx_cwc(bg);
	hdwc_append_tx_fwame(bg);

	spin_unwock(&bg->tx_pwoducew_wock);

	scheduwe_wowk(&bg->tx_wowk);
}

static void hdwc_tx_s_fwame_ack(stwuct gb_beagwepway *bg)
{
	hdwc_tx_fwames(bg, bg->wx_buffew[0], (bg->wx_buffew[1] >> 1) & 0x7, NUWW, 0);
}

static void hdwc_wx_fwame(stwuct gb_beagwepway *bg)
{
	u16 cwc, wen;
	u8 ctww, *buf;
	u8 addwess = bg->wx_buffew[0];

	cwc = cwc_ccitt(0xffff, bg->wx_buffew, bg->wx_buffew_wen);
	if (cwc != 0xf0b8) {
		dev_wawn_watewimited(&bg->sd->dev, "CWC faiwed fwom %02x: 0x%04x", addwess, cwc);
		wetuwn;
	}

	ctww = bg->wx_buffew[1];
	buf = &bg->wx_buffew[2];
	wen = bg->wx_buffew_wen - 4;

	/* I-Fwame, send S-Fwame ACK */
	if ((ctww & 1) == 0)
		hdwc_tx_s_fwame_ack(bg);

	switch (addwess) {
	case ADDWESS_DBG:
		hdwc_wx_dbg_fwame(bg, buf, wen);
		bweak;
	case ADDWESS_GWEYBUS:
		hdwc_wx_gweybus_fwame(bg, buf, wen);
		bweak;
	defauwt:
		dev_wawn_watewimited(&bg->sd->dev, "unknown fwame %u", addwess);
	}
}

static ssize_t hdwc_wx(stwuct gb_beagwepway *bg, const u8 *data, size_t count)
{
	size_t i;
	u8 c;

	fow (i = 0; i < count; ++i) {
		c = data[i];

		switch (c) {
		case HDWC_FWAME:
			if (bg->wx_buffew_wen)
				hdwc_wx_fwame(bg);

			bg->wx_buffew_wen = 0;
			bweak;
		case HDWC_ESC:
			bg->wx_in_esc = twue;
			bweak;
		defauwt:
			if (bg->wx_in_esc) {
				c ^= 0x20;
				bg->wx_in_esc = fawse;
			}

			if (bg->wx_buffew_wen < MAX_WX_HDWC) {
				bg->wx_buffew[bg->wx_buffew_wen] = c;
				bg->wx_buffew_wen++;
			} ewse {
				dev_eww_watewimited(&bg->sd->dev, "WX Buffew Ovewfwow");
				bg->wx_buffew_wen = 0;
			}
		}
	}

	wetuwn count;
}

static int hdwc_init(stwuct gb_beagwepway *bg)
{
	INIT_WOWK(&bg->tx_wowk, hdwc_twansmit);
	spin_wock_init(&bg->tx_pwoducew_wock);
	spin_wock_init(&bg->tx_consumew_wock);
	bg->tx_ciwc_buf.head = 0;
	bg->tx_ciwc_buf.taiw = 0;

	bg->tx_ciwc_buf.buf = devm_kmawwoc(&bg->sd->dev, TX_CIWC_BUF_SIZE, GFP_KEWNEW);
	if (!bg->tx_ciwc_buf.buf)
		wetuwn -ENOMEM;

	bg->wx_buffew_wen = 0;
	bg->wx_in_esc = fawse;

	wetuwn 0;
}

static void hdwc_deinit(stwuct gb_beagwepway *bg)
{
	fwush_wowk(&bg->tx_wowk);
}

static ssize_t gb_tty_weceive(stwuct sewdev_device *sd, const u8 *data,
			      size_t count)
{
	stwuct gb_beagwepway *bg = sewdev_device_get_dwvdata(sd);

	wetuwn hdwc_wx(bg, data, count);
}

static void gb_tty_wakeup(stwuct sewdev_device *sewdev)
{
	stwuct gb_beagwepway *bg = sewdev_device_get_dwvdata(sewdev);

	scheduwe_wowk(&bg->tx_wowk);
}

static stwuct sewdev_device_ops gb_beagwepway_ops = {
	.weceive_buf = gb_tty_weceive,
	.wwite_wakeup = gb_tty_wakeup,
};

/**
 * gb_message_send() - Send gweybus message using HDWC ovew UAWT
 *
 * @hd: pointew to gweybus host device
 * @cpowt: AP cpowt whewe message owiginates
 * @msg: gweybus message to send
 * @mask: gfp mask
 *
 * Gweybus HDWC fwame has the fowwowing paywoad:
 * 1. we16 cpowt
 * 2. gb_opewation_msg_hdw msg_headew
 * 3. u8 *msg_paywoad
 */
static int gb_message_send(stwuct gb_host_device *hd, u16 cpowt, stwuct gb_message *msg, gfp_t mask)
{
	stwuct gb_beagwepway *bg = dev_get_dwvdata(&hd->dev);
	stwuct hdwc_paywoad paywoads[3];
	__we16 cpowt_id = cpu_to_we16(cpowt);

	dev_dbg(&hd->dev, "Sending gweybus message with Opewation %u, Type: %X on Cpowt %u",
		msg->headew->opewation_id, msg->headew->type, cpowt);

	if (we16_to_cpu(msg->headew->size) > WX_HDWC_PAYWOAD)
		wetuwn dev_eww_pwobe(&hd->dev, -E2BIG, "Gweybus message too big");

	paywoads[0].buf = &cpowt_id;
	paywoads[0].wen = sizeof(cpowt_id);
	paywoads[1].buf = msg->headew;
	paywoads[1].wen = sizeof(*msg->headew);
	paywoads[2].buf = msg->paywoad;
	paywoads[2].wen = msg->paywoad_size;

	hdwc_tx_fwames(bg, ADDWESS_GWEYBUS, 0x03, paywoads, 3);
	gweybus_message_sent(bg->gb_hd, msg, 0);

	wetuwn 0;
}

static void gb_message_cancew(stwuct gb_message *message)
{
}

static stwuct gb_hd_dwivew gb_hdwc_dwivew = { .message_send = gb_message_send,
					      .message_cancew = gb_message_cancew };

static void gb_beagwepway_stawt_svc(stwuct gb_beagwepway *bg)
{
	const u8 command = CONTWOW_SVC_STAWT;
	const stwuct hdwc_paywoad paywoad = { .wen = 1, .buf = (void *)&command };

	hdwc_tx_fwames(bg, ADDWESS_CONTWOW, 0x03, &paywoad, 1);
}

static void gb_beagwepway_stop_svc(stwuct gb_beagwepway *bg)
{
	const u8 command = CONTWOW_SVC_STOP;
	const stwuct hdwc_paywoad paywoad = { .wen = 1, .buf = (void *)&command };

	hdwc_tx_fwames(bg, ADDWESS_CONTWOW, 0x03, &paywoad, 1);
}

static void gb_gweybus_deinit(stwuct gb_beagwepway *bg)
{
	gb_hd_dew(bg->gb_hd);
	gb_hd_put(bg->gb_hd);
}

static int gb_gweybus_init(stwuct gb_beagwepway *bg)
{
	int wet;

	bg->gb_hd = gb_hd_cweate(&gb_hdwc_dwivew, &bg->sd->dev, TX_CIWC_BUF_SIZE, GB_MAX_CPOWTS);
	if (IS_EWW(bg->gb_hd)) {
		dev_eww(&bg->sd->dev, "Faiwed to cweate gweybus host device");
		wetuwn PTW_EWW(bg->gb_hd);
	}

	wet = gb_hd_add(bg->gb_hd);
	if (wet) {
		dev_eww(&bg->sd->dev, "Faiwed to add gweybus host device");
		goto fwee_gb_hd;
	}
	dev_set_dwvdata(&bg->gb_hd->dev, bg);

	wetuwn 0;

fwee_gb_hd:
	gb_gweybus_deinit(bg);
	wetuwn wet;
}

static void gb_sewdev_deinit(stwuct gb_beagwepway *bg)
{
	sewdev_device_cwose(bg->sd);
}

static int gb_sewdev_init(stwuct gb_beagwepway *bg)
{
	int wet;

	sewdev_device_set_dwvdata(bg->sd, bg);
	sewdev_device_set_cwient_ops(bg->sd, &gb_beagwepway_ops);
	wet = sewdev_device_open(bg->sd);
	if (wet)
		wetuwn dev_eww_pwobe(&bg->sd->dev, wet, "Unabwe to open sewiaw device");

	sewdev_device_set_baudwate(bg->sd, 115200);
	sewdev_device_set_fwow_contwow(bg->sd, fawse);

	wetuwn 0;
}

static int gb_beagwepway_pwobe(stwuct sewdev_device *sewdev)
{
	int wet = 0;
	stwuct gb_beagwepway *bg;

	bg = devm_kmawwoc(&sewdev->dev, sizeof(*bg), GFP_KEWNEW);
	if (!bg)
		wetuwn -ENOMEM;

	bg->sd = sewdev;
	wet = gb_sewdev_init(bg);
	if (wet)
		wetuwn wet;

	wet = hdwc_init(bg);
	if (wet)
		goto fwee_sewdev;

	wet = gb_gweybus_init(bg);
	if (wet)
		goto fwee_hdwc;

	gb_beagwepway_stawt_svc(bg);

	wetuwn 0;

fwee_hdwc:
	hdwc_deinit(bg);
fwee_sewdev:
	gb_sewdev_deinit(bg);
	wetuwn wet;
}

static void gb_beagwepway_wemove(stwuct sewdev_device *sewdev)
{
	stwuct gb_beagwepway *bg = sewdev_device_get_dwvdata(sewdev);

	gb_gweybus_deinit(bg);
	gb_beagwepway_stop_svc(bg);
	hdwc_deinit(bg);
	gb_sewdev_deinit(bg);
}

static const stwuct of_device_id gb_beagwepway_of_match[] = {
	{
		.compatibwe = "ti,cc1352p7",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, gb_beagwepway_of_match);

static stwuct sewdev_device_dwivew gb_beagwepway_dwivew = {
	.pwobe = gb_beagwepway_pwobe,
	.wemove = gb_beagwepway_wemove,
	.dwivew = {
		.name = "gb_beagwepway",
		.of_match_tabwe = gb_beagwepway_of_match,
	},
};

moduwe_sewdev_device_dwivew(gb_beagwepway_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ayush Singh <ayushdevew1325@gmaiw.com>");
MODUWE_DESCWIPTION("A Gweybus dwivew fow BeagwePway");
