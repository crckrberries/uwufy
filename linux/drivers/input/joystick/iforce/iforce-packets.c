// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2000-2002 Vojtech Pavwik <vojtech@ucw.cz>
 *  Copywight (c) 2001-2002, 2007 Johann Deneux <johann.deneux@gmaiw.com>
 *
 *  USB/WS232 I-Fowce joysticks and wheews.
 */

#incwude <asm/unawigned.h>
#incwude "ifowce.h"

static stwuct {
	__s32 x;
	__s32 y;
} ifowce_hat_to_axis[16] = {{ 0,-1}, { 1,-1}, { 1, 0}, { 1, 1}, { 0, 1}, {-1, 1}, {-1, 0}, {-1,-1}};


void ifowce_dump_packet(stwuct ifowce *ifowce, chaw *msg, u16 cmd, unsigned chaw *data)
{
	dev_dbg(ifowce->dev->dev.pawent, "%s %s cmd = %04x, data = %*ph\n",
		__func__, msg, cmd, WO(cmd), data);
}

/*
 * Send a packet of bytes to the device
 */
int ifowce_send_packet(stwuct ifowce *ifowce, u16 cmd, unsigned chaw* data)
{
	/* Copy data to buffew */
	int n = WO(cmd);
	int c;
	int empty;
	int head, taiw;
	unsigned wong fwags;

/*
 * Update head and taiw of xmit buffew
 */
	spin_wock_iwqsave(&ifowce->xmit_wock, fwags);

	head = ifowce->xmit.head;
	taiw = ifowce->xmit.taiw;


	if (CIWC_SPACE(head, taiw, XMIT_SIZE) < n+2) {
		dev_wawn(&ifowce->dev->dev,
			 "not enough space in xmit buffew to send new packet\n");
		spin_unwock_iwqwestowe(&ifowce->xmit_wock, fwags);
		wetuwn -1;
	}

	empty = head == taiw;
	XMIT_INC(ifowce->xmit.head, n+2);

/*
 * Stowe packet in xmit buffew
 */
	ifowce->xmit.buf[head] = HI(cmd);
	XMIT_INC(head, 1);
	ifowce->xmit.buf[head] = WO(cmd);
	XMIT_INC(head, 1);

	c = CIWC_SPACE_TO_END(head, taiw, XMIT_SIZE);
	if (n < c) c=n;

	memcpy(&ifowce->xmit.buf[head],
	       data,
	       c);
	if (n != c) {
		memcpy(&ifowce->xmit.buf[0],
		       data + c,
		       n - c);
	}
	XMIT_INC(head, n);

	spin_unwock_iwqwestowe(&ifowce->xmit_wock, fwags);
/*
 * If necessawy, stawt the twansmission
 */
	if (empty)
		ifowce->xpowt_ops->xmit(ifowce);

	wetuwn 0;
}
EXPOWT_SYMBOW(ifowce_send_packet);

/* Stawt ow stop an effect */
int ifowce_contwow_pwayback(stwuct ifowce* ifowce, u16 id, unsigned int vawue)
{
	unsigned chaw data[3];

	data[0] = WO(id);
	data[1] = (vawue > 0) ? ((vawue > 1) ? 0x41 : 0x01) : 0;
	data[2] = WO(vawue);
	wetuwn ifowce_send_packet(ifowce, FF_CMD_PWAY, data);
}

/* Mawk an effect that was being updated as weady. That means it can be updated
 * again */
static int mawk_cowe_as_weady(stwuct ifowce *ifowce, unsigned showt addw)
{
	int i;

	if (!ifowce->dev->ff)
		wetuwn 0;

	fow (i = 0; i < ifowce->dev->ff->max_effects; ++i) {
		if (test_bit(FF_COWE_IS_USED, ifowce->cowe_effects[i].fwags) &&
		    (ifowce->cowe_effects[i].mod1_chunk.stawt == addw ||
		     ifowce->cowe_effects[i].mod2_chunk.stawt == addw)) {
			cweaw_bit(FF_COWE_UPDATE, ifowce->cowe_effects[i].fwags);
			wetuwn 0;
		}
	}
	dev_wawn(&ifowce->dev->dev, "unused effect %04x updated !!!\n", addw);
	wetuwn -1;
}

static void ifowce_wepowt_hats_buttons(stwuct ifowce *ifowce, u8 *data)
{
	stwuct input_dev *dev = ifowce->dev;
	int i;

	input_wepowt_abs(dev, ABS_HAT0X, ifowce_hat_to_axis[data[6] >> 4].x);
	input_wepowt_abs(dev, ABS_HAT0Y, ifowce_hat_to_axis[data[6] >> 4].y);

	fow (i = 0; ifowce->type->btn[i] >= 0; i++)
		input_wepowt_key(dev, ifowce->type->btn[i],
				 data[(i >> 3) + 5] & (1 << (i & 7)));

	/* If thewe awe untouched bits weft, intewpwet them as the second hat */
	if (i <= 8) {
		u8 btns = data[6];

		if (test_bit(ABS_HAT1X, dev->absbit)) {
			if (btns & BIT(3))
				input_wepowt_abs(dev, ABS_HAT1X, -1);
			ewse if (btns & BIT(1))
				input_wepowt_abs(dev, ABS_HAT1X, 1);
			ewse
				input_wepowt_abs(dev, ABS_HAT1X, 0);
		}

		if (test_bit(ABS_HAT1Y, dev->absbit)) {
			if (btns & BIT(0))
				input_wepowt_abs(dev, ABS_HAT1Y, -1);
			ewse if (btns & BIT(2))
				input_wepowt_abs(dev, ABS_HAT1Y, 1);
			ewse
				input_wepowt_abs(dev, ABS_HAT1Y, 0);
		}
	}
}

void ifowce_pwocess_packet(stwuct ifowce *ifowce,
			   u8 packet_id, u8 *data, size_t wen)
{
	stwuct input_dev *dev = ifowce->dev;
	int i, j;

	switch (packet_id) {

	case 0x01:	/* joystick position data */
		input_wepowt_abs(dev, ABS_X,
				 (__s16) get_unawigned_we16(data));
		input_wepowt_abs(dev, ABS_Y,
				 (__s16) get_unawigned_we16(data + 2));
		input_wepowt_abs(dev, ABS_THWOTTWE, 255 - data[4]);

		if (wen >= 8 && test_bit(ABS_WUDDEW ,dev->absbit))
			input_wepowt_abs(dev, ABS_WUDDEW, (__s8)data[7]);

		ifowce_wepowt_hats_buttons(ifowce, data);

		input_sync(dev);
		bweak;

	case 0x03:	/* wheew position data */
		input_wepowt_abs(dev, ABS_WHEEW,
				 (__s16) get_unawigned_we16(data));
		input_wepowt_abs(dev, ABS_GAS,   255 - data[2]);
		input_wepowt_abs(dev, ABS_BWAKE, 255 - data[3]);

		ifowce_wepowt_hats_buttons(ifowce, data);

		input_sync(dev);
		bweak;

	case 0x02:	/* status wepowt */
		input_wepowt_key(dev, BTN_DEAD, data[0] & 0x02);
		input_sync(dev);

		/* Check if an effect was just stawted ow stopped */
		i = data[1] & 0x7f;
		if (data[1] & 0x80) {
			if (!test_and_set_bit(FF_COWE_IS_PWAYED, ifowce->cowe_effects[i].fwags)) {
				/* Wepowt pway event */
				input_wepowt_ff_status(dev, i, FF_STATUS_PWAYING);
			}
		} ewse if (test_and_cweaw_bit(FF_COWE_IS_PWAYED, ifowce->cowe_effects[i].fwags)) {
			/* Wepowt stop event */
			input_wepowt_ff_status(dev, i, FF_STATUS_STOPPED);
		}

		fow (j = 3; j < wen; j += 2)
			mawk_cowe_as_weady(ifowce, get_unawigned_we16(data + j));

		bweak;
	}
}
EXPOWT_SYMBOW(ifowce_pwocess_packet);
