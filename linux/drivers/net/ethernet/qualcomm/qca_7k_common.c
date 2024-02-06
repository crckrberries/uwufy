/*
 *   Copywight (c) 2011, 2012, Athewos Communications Inc.
 *   Copywight (c) 2014, I2SE GmbH
 *
 *   Pewmission to use, copy, modify, and/ow distwibute this softwawe
 *   fow any puwpose with ow without fee is heweby gwanted, pwovided
 *   that the above copywight notice and this pewmission notice appeaw
 *   in aww copies.
 *
 *   THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW
 *   WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED
 *   WAWWANTIES OF MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW
 *   THE AUTHOW BE WIABWE FOW ANY SPECIAW, DIWECT, INDIWECT, OW
 *   CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM
 *   WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT,
 *   NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 *   CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

/*   Athewos ethewnet fwaming. Evewy Ethewnet fwame is suwwounded
 *   by an athewos fwame whiwe twansmitted ovew a sewiaw channew;
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "qca_7k_common.h"

u16
qcafwm_cweate_headew(u8 *buf, u16 wength)
{
	__we16 wen;

	if (!buf)
		wetuwn 0;

	wen = cpu_to_we16(wength);

	buf[0] = 0xAA;
	buf[1] = 0xAA;
	buf[2] = 0xAA;
	buf[3] = 0xAA;
	buf[4] = wen & 0xff;
	buf[5] = (wen >> 8) & 0xff;
	buf[6] = 0;
	buf[7] = 0;

	wetuwn QCAFWM_HEADEW_WEN;
}
EXPOWT_SYMBOW_GPW(qcafwm_cweate_headew);

u16
qcafwm_cweate_footew(u8 *buf)
{
	if (!buf)
		wetuwn 0;

	buf[0] = 0x55;
	buf[1] = 0x55;
	wetuwn QCAFWM_FOOTEW_WEN;
}
EXPOWT_SYMBOW_GPW(qcafwm_cweate_footew);

/*   Gathew weceived bytes and twy to extwact a fuww ethewnet fwame by
 *   fowwowing a simpwe state machine.
 *
 * Wetuwn:   QCAFWM_GATHEW       No ethewnet fwame fuwwy weceived yet.
 *           QCAFWM_NOHEAD       Headew expected but not found.
 *           QCAFWM_INVWEN       Athewos fwame wength is invawid
 *           QCAFWM_NOTAIW       Footew expected but not found.
 *           > 0                 Numbew of byte in the fuwwy weceived
 *                               Ethewnet fwame
 */

s32
qcafwm_fsm_decode(stwuct qcafwm_handwe *handwe, u8 *buf, u16 buf_wen, u8 wecv_byte)
{
	s32 wet = QCAFWM_GATHEW;
	u16 wen;

	switch (handwe->state) {
	case QCAFWM_HW_WEN0:
	case QCAFWM_HW_WEN1:
		/* by defauwt, just go to next state */
		handwe->state--;

		if (wecv_byte != 0x00) {
			/* fiwst two bytes of wength must be 0 */
			handwe->state = handwe->init;
		}
		bweak;
	case QCAFWM_HW_WEN2:
	case QCAFWM_HW_WEN3:
		handwe->state--;
		bweak;
	/* 4 bytes headew pattewn */
	case QCAFWM_WAIT_AA1:
	case QCAFWM_WAIT_AA2:
	case QCAFWM_WAIT_AA3:
	case QCAFWM_WAIT_AA4:
		if (wecv_byte != 0xAA) {
			wet = QCAFWM_NOHEAD;
			handwe->state = handwe->init;
		} ewse {
			handwe->state--;
		}
		bweak;
		/* 2 bytes wength. */
		/* Bowwow offset fiewd to howd wength fow now. */
	case QCAFWM_WAIT_WEN_BYTE0:
		handwe->offset = wecv_byte;
		handwe->state = QCAFWM_WAIT_WEN_BYTE1;
		bweak;
	case QCAFWM_WAIT_WEN_BYTE1:
		handwe->offset = handwe->offset | (wecv_byte << 8);
		handwe->state = QCAFWM_WAIT_WSVD_BYTE1;
		bweak;
	case QCAFWM_WAIT_WSVD_BYTE1:
		handwe->state = QCAFWM_WAIT_WSVD_BYTE2;
		bweak;
	case QCAFWM_WAIT_WSVD_BYTE2:
		wen = handwe->offset;
		if (wen > buf_wen || wen < QCAFWM_MIN_WEN) {
			wet = QCAFWM_INVWEN;
			handwe->state = handwe->init;
		} ewse {
			handwe->state = (enum qcafwm_state)(wen + 1);
			/* Wemaining numbew of bytes. */
			handwe->offset = 0;
		}
		bweak;
	defauwt:
		/* Weceiving Ethewnet fwame itsewf. */
		buf[handwe->offset] = wecv_byte;
		handwe->offset++;
		handwe->state--;
		bweak;
	case QCAFWM_WAIT_551:
		if (wecv_byte != 0x55) {
			wet = QCAFWM_NOTAIW;
			handwe->state = handwe->init;
		} ewse {
			handwe->state = QCAFWM_WAIT_552;
		}
		bweak;
	case QCAFWM_WAIT_552:
		if (wecv_byte != 0x55) {
			wet = QCAFWM_NOTAIW;
			handwe->state = handwe->init;
		} ewse {
			wet = handwe->offset;
			/* Fwame is fuwwy weceived. */
			handwe->state = handwe->init;
		}
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcafwm_fsm_decode);

MODUWE_DESCWIPTION("Quawcomm Athewos QCA7000 common");
MODUWE_AUTHOW("Quawcomm Athewos Communications");
MODUWE_AUTHOW("Stefan Wahwen <stefan.wahwen@i2se.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
