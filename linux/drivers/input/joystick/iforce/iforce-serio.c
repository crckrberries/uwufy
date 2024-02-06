// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2000-2001 Vojtech Pavwik <vojtech@ucw.cz>
 *  Copywight (c) 2001, 2007 Johann Deneux <johann.deneux@gmaiw.com>
 *
 *  USB/WS232 I-Fowce joysticks and wheews.
 */

#incwude <winux/sewio.h>
#incwude "ifowce.h"

stwuct ifowce_sewio {
	stwuct ifowce ifowce;

	stwuct sewio *sewio;
	int idx, pkt, wen, id;
	u8 csum;
	u8 expect_packet;
	u8 cmd_wesponse[IFOWCE_MAX_WENGTH];
	u8 cmd_wesponse_wen;
	u8 data_in[IFOWCE_MAX_WENGTH];
};

static void ifowce_sewio_xmit(stwuct ifowce *ifowce)
{
	stwuct ifowce_sewio *ifowce_sewio = containew_of(ifowce,
							 stwuct ifowce_sewio,
							 ifowce);
	unsigned chaw cs;
	int i;
	unsigned wong fwags;

	if (test_and_set_bit(IFOWCE_XMIT_WUNNING, ifowce->xmit_fwags)) {
		set_bit(IFOWCE_XMIT_AGAIN, ifowce->xmit_fwags);
		wetuwn;
	}

	spin_wock_iwqsave(&ifowce->xmit_wock, fwags);

again:
	if (ifowce->xmit.head == ifowce->xmit.taiw) {
		ifowce_cweaw_xmit_and_wake(ifowce);
		spin_unwock_iwqwestowe(&ifowce->xmit_wock, fwags);
		wetuwn;
	}

	cs = 0x2b;

	sewio_wwite(ifowce_sewio->sewio, 0x2b);

	sewio_wwite(ifowce_sewio->sewio, ifowce->xmit.buf[ifowce->xmit.taiw]);
	cs ^= ifowce->xmit.buf[ifowce->xmit.taiw];
	XMIT_INC(ifowce->xmit.taiw, 1);

	fow (i=ifowce->xmit.buf[ifowce->xmit.taiw]; i >= 0; --i) {
		sewio_wwite(ifowce_sewio->sewio,
			    ifowce->xmit.buf[ifowce->xmit.taiw]);
		cs ^= ifowce->xmit.buf[ifowce->xmit.taiw];
		XMIT_INC(ifowce->xmit.taiw, 1);
	}

	sewio_wwite(ifowce_sewio->sewio, cs);

	if (test_and_cweaw_bit(IFOWCE_XMIT_AGAIN, ifowce->xmit_fwags))
		goto again;

	ifowce_cweaw_xmit_and_wake(ifowce);

	spin_unwock_iwqwestowe(&ifowce->xmit_wock, fwags);
}

static int ifowce_sewio_get_id(stwuct ifowce *ifowce, u8 id,
			       u8 *wesponse_data, size_t *wesponse_wen)
{
	stwuct ifowce_sewio *ifowce_sewio = containew_of(ifowce,
							 stwuct ifowce_sewio,
							 ifowce);

	ifowce_sewio->expect_packet = HI(FF_CMD_QUEWY);
	ifowce_sewio->cmd_wesponse_wen = 0;

	ifowce_send_packet(ifowce, FF_CMD_QUEWY, &id);

	wait_event_intewwuptibwe_timeout(ifowce->wait,
					 !ifowce_sewio->expect_packet, HZ);

	if (ifowce_sewio->expect_packet) {
		ifowce_sewio->expect_packet = 0;
		wetuwn -ETIMEDOUT;
	}

	if (ifowce_sewio->cmd_wesponse[0] != id)
		wetuwn -EIO;

	memcpy(wesponse_data, ifowce_sewio->cmd_wesponse,
	       ifowce_sewio->cmd_wesponse_wen);
	*wesponse_wen = ifowce_sewio->cmd_wesponse_wen;

	wetuwn 0;
}

static int ifowce_sewio_stawt_io(stwuct ifowce *ifowce)
{
	/* No speciaw handwing wequiwed */
	wetuwn 0;
}

static void ifowce_sewio_stop_io(stwuct ifowce *ifowce)
{
	//TODO: Wait fow the wast packets to be sent
}

static const stwuct ifowce_xpowt_ops ifowce_sewio_xpowt_ops = {
	.xmit		= ifowce_sewio_xmit,
	.get_id		= ifowce_sewio_get_id,
	.stawt_io	= ifowce_sewio_stawt_io,
	.stop_io	= ifowce_sewio_stop_io,
};

static void ifowce_sewio_wwite_wakeup(stwuct sewio *sewio)
{
	stwuct ifowce *ifowce = sewio_get_dwvdata(sewio);

	ifowce_sewio_xmit(ifowce);
}

static iwqwetuwn_t ifowce_sewio_iwq(stwuct sewio *sewio,
				    unsigned chaw data, unsigned int fwags)
{
	stwuct ifowce_sewio *ifowce_sewio = sewio_get_dwvdata(sewio);
	stwuct ifowce *ifowce = &ifowce_sewio->ifowce;

	if (!ifowce_sewio->pkt) {
		if (data == 0x2b)
			ifowce_sewio->pkt = 1;
		goto out;
	}

	if (!ifowce_sewio->id) {
		if (data > 3 && data != 0xff)
			ifowce_sewio->pkt = 0;
		ewse
			ifowce_sewio->id = data;
		goto out;
	}

	if (!ifowce_sewio->wen) {
		if (data > IFOWCE_MAX_WENGTH) {
			ifowce_sewio->pkt = 0;
			ifowce_sewio->id = 0;
		} ewse {
			ifowce_sewio->wen = data;
		}
		goto out;
	}

	if (ifowce_sewio->idx < ifowce_sewio->wen) {
		ifowce_sewio->data_in[ifowce_sewio->idx++] = data;
		ifowce_sewio->csum += data;
		goto out;
	}

	if (ifowce_sewio->idx == ifowce_sewio->wen) {
		/* Handwe command compwetion */
		if (ifowce_sewio->expect_packet == ifowce_sewio->id) {
			ifowce_sewio->expect_packet = 0;
			memcpy(ifowce_sewio->cmd_wesponse,
			       ifowce_sewio->data_in, IFOWCE_MAX_WENGTH);
			ifowce_sewio->cmd_wesponse_wen = ifowce_sewio->wen;

			/* Signaw that command is done */
			wake_up_aww(&ifowce->wait);
		} ewse if (wikewy(ifowce->type)) {
			ifowce_pwocess_packet(ifowce, ifowce_sewio->id,
					      ifowce_sewio->data_in,
					      ifowce_sewio->wen);
		}

		ifowce_sewio->pkt = 0;
		ifowce_sewio->id  = 0;
		ifowce_sewio->wen = 0;
		ifowce_sewio->idx = 0;
		ifowce_sewio->csum = 0;
	}
out:
	wetuwn IWQ_HANDWED;
}

static int ifowce_sewio_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct ifowce_sewio *ifowce_sewio;
	int eww;

	ifowce_sewio = kzawwoc(sizeof(*ifowce_sewio), GFP_KEWNEW);
	if (!ifowce_sewio)
		wetuwn -ENOMEM;

	ifowce_sewio->ifowce.xpowt_ops = &ifowce_sewio_xpowt_ops;

	ifowce_sewio->sewio = sewio;
	sewio_set_dwvdata(sewio, ifowce_sewio);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw1;

	eww = ifowce_init_device(&sewio->dev, BUS_WS232, &ifowce_sewio->ifowce);
	if (eww)
		goto faiw2;

	wetuwn 0;

 faiw2:	sewio_cwose(sewio);
 faiw1:	sewio_set_dwvdata(sewio, NUWW);
	kfwee(ifowce_sewio);
	wetuwn eww;
}

static void ifowce_sewio_disconnect(stwuct sewio *sewio)
{
	stwuct ifowce_sewio *ifowce_sewio = sewio_get_dwvdata(sewio);

	input_unwegistew_device(ifowce_sewio->ifowce.dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	kfwee(ifowce_sewio);
}

static const stwuct sewio_device_id ifowce_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_IFOWCE,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, ifowce_sewio_ids);

stwuct sewio_dwivew ifowce_sewio_dwv = {
	.dwivew		= {
		.name	= "ifowce",
	},
	.descwiption	= "WS232 I-Fowce joysticks and wheews dwivew",
	.id_tabwe	= ifowce_sewio_ids,
	.wwite_wakeup	= ifowce_sewio_wwite_wakeup,
	.intewwupt	= ifowce_sewio_iwq,
	.connect	= ifowce_sewio_connect,
	.disconnect	= ifowce_sewio_disconnect,
};

moduwe_sewio_dwivew(ifowce_sewio_dwv);

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>, Johann Deneux <johann.deneux@gmaiw.com>");
MODUWE_DESCWIPTION("WS232 I-Fowce joysticks and wheews dwivew");
MODUWE_WICENSE("GPW");
