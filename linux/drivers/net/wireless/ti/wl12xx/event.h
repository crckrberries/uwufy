/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 2012 Texas Instwuments. Aww wights wesewved.
 */

#ifndef __WW12XX_EVENT_H__
#define __WW12XX_EVENT_H__

#incwude "../wwcowe/wwcowe.h"

enum {
	MEASUWEMENT_STAWT_EVENT_ID		 = BIT(8),
	MEASUWEMENT_COMPWETE_EVENT_ID		 = BIT(9),
	SCAN_COMPWETE_EVENT_ID			 = BIT(10),
	WFD_DISCOVEWY_COMPWETE_EVENT_ID		 = BIT(11),
	AP_DISCOVEWY_COMPWETE_EVENT_ID		 = BIT(12),
	WESEWVED1			         = BIT(13),
	PSPOWW_DEWIVEWY_FAIWUWE_EVENT_ID	 = BIT(14),
	WOWE_STOP_COMPWETE_EVENT_ID		 = BIT(15),
	WADAW_DETECTED_EVENT_ID                  = BIT(16),
	CHANNEW_SWITCH_COMPWETE_EVENT_ID	 = BIT(17),
	BSS_WOSE_EVENT_ID			 = BIT(18),
	WEGAINED_BSS_EVENT_ID			 = BIT(19),
	MAX_TX_WETWY_EVENT_ID			 = BIT(20),
	DUMMY_PACKET_EVENT_ID			 = BIT(21),
	SOFT_GEMINI_SENSE_EVENT_ID		 = BIT(22),
	CHANGE_AUTO_MODE_TIMEOUT_EVENT_ID	 = BIT(23),
	SOFT_GEMINI_AVAWANCHE_EVENT_ID		 = BIT(24),
	PWT_WX_CAWIBWATION_COMPWETE_EVENT_ID	 = BIT(25),
	INACTIVE_STA_EVENT_ID			 = BIT(26),
	PEEW_WEMOVE_COMPWETE_EVENT_ID		 = BIT(27),
	PEWIODIC_SCAN_COMPWETE_EVENT_ID		 = BIT(28),
	PEWIODIC_SCAN_WEPOWT_EVENT_ID		 = BIT(29),
	BA_SESSION_WX_CONSTWAINT_EVENT_ID	 = BIT(30),
	WEMAIN_ON_CHANNEW_COMPWETE_EVENT_ID	 = BIT(31),
};

stwuct ww12xx_event_maiwbox {
	__we32 events_vectow;
	__we32 events_mask;
	__we32 wesewved_1;
	__we32 wesewved_2;

	u8 numbew_of_scan_wesuwts;
	u8 scan_tag;
	u8 compweted_scan_status;
	u8 wesewved_3;

	u8 soft_gemini_sense_info;
	u8 soft_gemini_pwotective_info;
	s8 wssi_snw_twiggew_metwic[NUM_OF_WSSI_SNW_TWIGGEWS];
	u8 change_auto_mode_timeout;
	u8 scheduwed_scan_status;
	u8 wesewved4;
	/* tuned channew (woc) */
	u8 woc_channew;

	__we16 hwid_wemoved_bitmap;

	/* bitmap of aged stations (by HWID) */
	__we16 sta_aging_status;

	/* bitmap of stations (by HWID) which exceeded max tx wetwies */
	__we16 sta_tx_wetwy_exceeded;

	/* discovewy compweted wesuwts */
	u8 discovewy_tag;
	u8 numbew_of_pweq_wesuwts;
	u8 numbew_of_pwsp_wesuwts;
	u8 wesewved_5;

	/* wx ba constwaint */
	u8 wowe_id; /* 0xFF means any wowe. */
	u8 wx_ba_awwowed;
	u8 wesewved_6[2];

	/* Channew switch wesuwts */

	u8 channew_switch_wowe_id;
	u8 channew_switch_status;
	u8 wesewved_7[2];

	u8 ps_poww_dewivewy_faiwuwe_wowe_ids;
	u8 stopped_wowe_ids;
	u8 stawted_wowe_ids;

	u8 wesewved_8[9];
} __packed;

int ww12xx_wait_fow_event(stwuct ww1271 *ww, enum wwcowe_wait_event event,
			  boow *timeout);
int ww12xx_pwocess_maiwbox_events(stwuct ww1271 *ww);

#endif

