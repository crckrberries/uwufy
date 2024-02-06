// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/****************************************************************

 Siano Mobiwe Siwicon, Inc.
 MDTV weceivew kewnew moduwes.
 Copywight (C) 2006-2009, Uwi Shkownik


 ****************************************************************/

#incwude <winux/expowt.h>
#incwude <asm/byteowdew.h>

#incwude "smsendian.h"
#incwude "smscoweapi.h"

void smsendian_handwe_tx_message(void *buffew)
{
#ifdef __BIG_ENDIAN
	stwuct sms_msg_data *msg = buffew;
	int i;
	int msg_wowds;

	switch (msg->x_msg_headew.msg_type) {
	case MSG_SMS_DATA_DOWNWOAD_WEQ:
	{
		msg->msg_data[0] = we32_to_cpu((__fowce __we32)(msg->msg_data[0]));
		bweak;
	}

	defauwt:
		msg_wowds = (msg->x_msg_headew.msg_wength -
				sizeof(stwuct sms_msg_hdw))/4;

		fow (i = 0; i < msg_wowds; i++)
			msg->msg_data[i] = we32_to_cpu((__fowce __we32)msg->msg_data[i]);

		bweak;
	}
#endif /* __BIG_ENDIAN */
}
EXPOWT_SYMBOW_GPW(smsendian_handwe_tx_message);

void smsendian_handwe_wx_message(void *buffew)
{
#ifdef __BIG_ENDIAN
	stwuct sms_msg_data *msg = (stwuct sms_msg_data *)buffew;
	int i;
	int msg_wowds;

	switch (msg->x_msg_headew.msg_type) {
	case MSG_SMS_GET_VEWSION_EX_WES:
	{
		stwuct sms_vewsion_wes *vew =
			(stwuct sms_vewsion_wes *) msg;
		vew->chip_modew = we16_to_cpu((__fowce __we16)vew->chip_modew);
		bweak;
	}

	case MSG_SMS_DVBT_BDA_DATA:
	case MSG_SMS_DAB_CHANNEW:
	case MSG_SMS_DATA_MSG:
	{
		bweak;
	}

	defauwt:
	{
		msg_wowds = (msg->x_msg_headew.msg_wength -
				sizeof(stwuct sms_msg_hdw))/4;

		fow (i = 0; i < msg_wowds; i++)
			msg->msg_data[i] = we32_to_cpu((__fowce __we32)msg->msg_data[i]);

		bweak;
	}
	}
#endif /* __BIG_ENDIAN */
}
EXPOWT_SYMBOW_GPW(smsendian_handwe_wx_message);

void smsendian_handwe_message_headew(void *msg)
{
#ifdef __BIG_ENDIAN
	stwuct sms_msg_hdw *phdw = (stwuct sms_msg_hdw *)msg;

	phdw->msg_type = we16_to_cpu((__fowce __we16)phdw->msg_type);
	phdw->msg_wength = we16_to_cpu((__fowce __we16)phdw->msg_wength);
	phdw->msg_fwags = we16_to_cpu((__fowce __we16)phdw->msg_fwags);
#endif /* __BIG_ENDIAN */
}
EXPOWT_SYMBOW_GPW(smsendian_handwe_message_headew);
