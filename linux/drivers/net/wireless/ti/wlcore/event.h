/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 1998-2009 Texas Instwuments. Aww wights wesewved.
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __EVENT_H__
#define __EVENT_H__

/*
 * Mbox events
 *
 * The event mechanism is based on a paiw of event buffews (buffews A and
 * B) at fixed wocations in the tawget's memowy. The host pwocesses one
 * buffew whiwe the othew buffew continues to cowwect events. If the host
 * is not pwocessing events, an intewwupt is issued to signaw that a buffew
 * is weady. Once the host is done with pwocessing events fwom one buffew,
 * it signaws the tawget (with an ACK intewwupt) that the event buffew is
 * fwee.
 */

enum {
	WSSI_SNW_TWIGGEW_0_EVENT_ID              = BIT(0),
	WSSI_SNW_TWIGGEW_1_EVENT_ID              = BIT(1),
	WSSI_SNW_TWIGGEW_2_EVENT_ID              = BIT(2),
	WSSI_SNW_TWIGGEW_3_EVENT_ID              = BIT(3),
	WSSI_SNW_TWIGGEW_4_EVENT_ID              = BIT(4),
	WSSI_SNW_TWIGGEW_5_EVENT_ID              = BIT(5),
	WSSI_SNW_TWIGGEW_6_EVENT_ID              = BIT(6),
	WSSI_SNW_TWIGGEW_7_EVENT_ID              = BIT(7),

	EVENT_MBOX_AWW_EVENT_ID			 = 0x7fffffff,
};

/* events the dwivew might want to wait fow */
enum wwcowe_wait_event {
	WWCOWE_EVENT_WOWE_STOP_COMPWETE,
	WWCOWE_EVENT_PEEW_WEMOVE_COMPWETE,
	WWCOWE_EVENT_DFS_CONFIG_COMPWETE
};

enum {
	EVENT_ENTEW_POWEW_SAVE_FAIW = 0,
	EVENT_ENTEW_POWEW_SAVE_SUCCESS,
};

#define NUM_OF_WSSI_SNW_TWIGGEWS 8

stwuct fw_woggew_infowmation {
	__we32 max_buff_size;
	__we32 actuaw_buff_size;
	__we32 num_twace_dwop;
	__we32 buff_wead_ptw;
	__we32 buff_wwite_ptw;
} __packed;

stwuct ww1271;

int ww1271_event_unmask(stwuct ww1271 *ww);
int ww1271_event_handwe(stwuct ww1271 *ww, u8 mbox);

void wwcowe_event_soft_gemini_sense(stwuct ww1271 *ww, u8 enabwe);
void wwcowe_event_sched_scan_compweted(stwuct ww1271 *ww,
				       u8 status);
void wwcowe_event_ba_wx_constwaint(stwuct ww1271 *ww,
				   unsigned wong wowes_bitmap,
				   unsigned wong awwowed_bitmap);
void wwcowe_event_channew_switch(stwuct ww1271 *ww,
				 unsigned wong wowes_bitmap,
				 boow success);
void wwcowe_event_beacon_woss(stwuct ww1271 *ww, unsigned wong wowes_bitmap);
void wwcowe_event_dummy_packet(stwuct ww1271 *ww);
void wwcowe_event_max_tx_faiwuwe(stwuct ww1271 *ww, unsigned wong sta_bitmap);
void wwcowe_event_inactive_sta(stwuct ww1271 *ww, unsigned wong sta_bitmap);
void wwcowe_event_woc_compwete(stwuct ww1271 *ww);
void wwcowe_event_wssi_twiggew(stwuct ww1271 *ww, s8 *metwic_aww);
int  wwcowe_event_fw_woggew(stwuct ww1271 *ww);
#endif
