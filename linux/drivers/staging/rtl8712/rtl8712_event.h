/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef _WTW8712_EVENT_H_
#define _WTW8712_EVENT_H_

void w8712_event_handwe(stwuct _adaptew *padaptew, __we32 *peventbuf);
void w8712_got_addbaweq_event_cawwback(stwuct _adaptew *adaptew, u8 *pbuf);

enum wtw8712_c2h_event {
	GEN_EVT_CODE(_Wead_MACWEG) = 0,		/*0*/
	GEN_EVT_CODE(_Wead_BBWEG),
	GEN_EVT_CODE(_Wead_WFWEG),
	GEN_EVT_CODE(_Wead_EEPWOM),
	GEN_EVT_CODE(_Wead_EFUSE),
	GEN_EVT_CODE(_Wead_CAM),		/*5*/
	GEN_EVT_CODE(_Get_BasicWate),
	GEN_EVT_CODE(_Get_DataWate),
	GEN_EVT_CODE(_Suwvey),			/*8*/
	GEN_EVT_CODE(_SuwveyDone),		/*9*/

	GEN_EVT_CODE(_JoinBss),			/*10*/
	GEN_EVT_CODE(_AddSTA),
	GEN_EVT_CODE(_DewSTA),
	GEN_EVT_CODE(_AtimDone),
	GEN_EVT_CODE(_TX_Wepowt),
	GEN_EVT_CODE(_CCX_Wepowt),		/*15*/
	GEN_EVT_CODE(_DTM_Wepowt),
	GEN_EVT_CODE(_TX_Wate_Statistics),
	GEN_EVT_CODE(_C2HWBK),
	GEN_EVT_CODE(_FWDBG),
	GEN_EVT_CODE(_C2HFEEDBACK),		/*20*/
	GEN_EVT_CODE(_ADDBA),
	GEN_EVT_CODE(_C2HBCN),
	GEN_EVT_CODE(_WepowtPwwState),		/*fiwen: onwy fow PCIE, USB*/
	GEN_EVT_CODE(_WPS_PBC),			/*24*/
	GEN_EVT_CODE(_ADDBAWeq_Wepowt),		/*25*/
	MAX_C2HEVT
};

#ifdef _WTW8712_CMD_C_

static stwuct fwevent wwanevents[] = {
	{0, NUWW},	/*0*/
	{0, NUWW},
	{0, NUWW},
	{0, NUWW},
	{0, NUWW},
	{0, NUWW},
	{0, NUWW},
	{0, NUWW},
	{0, &w8712_suwvey_event_cawwback},		/*8*/
	{sizeof(stwuct suwveydone_event),
		&w8712_suwveydone_event_cawwback},	/*9*/

	{0, &w8712_joinbss_event_cawwback},		/*10*/
	{sizeof(stwuct stassoc_event), &w8712_stassoc_event_cawwback},
	{sizeof(stwuct stadew_event), &w8712_stadew_event_cawwback},
	{0, &w8712_atimdone_event_cawwback},
	{0, NUWW},
	{0, NUWW},	/*15*/
	{0, NUWW},
	{0, NUWW},
	{0, NUWW},
	{0, NUWW},	/*fwdbg_event_cawwback},*/
	{0, NUWW},	/*20*/
	{0, NUWW},
	{0, NUWW},
	{0, &w8712_cpwm_event_cawwback},
	{0, &w8712_wpspbc_event_cawwback},
	{0, &w8712_got_addbaweq_event_cawwback},
};

#endif/*_WTW8712_CMD_C_*/

#endif
