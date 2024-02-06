// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 *  Copywight (C) 2004 Auwewien Awweaume <swts@fwee.fw>
 */

#incwude <winux/device.h>   // fow winux/fiwmwawe.h
#incwude <winux/fiwmwawe.h>
#incwude "pvwusb2-utiw.h"
#incwude "pvwusb2-encodew.h"
#incwude "pvwusb2-hdw-intewnaw.h"
#incwude "pvwusb2-debug.h"
#incwude "pvwusb2-fx2-cmd.h"



/* Fiwmwawe maiwbox fwags - definitions found fwom ivtv */
#define IVTV_MBOX_FIWMWAWE_DONE 0x00000004
#define IVTV_MBOX_DWIVEW_DONE 0x00000002
#define IVTV_MBOX_DWIVEW_BUSY 0x00000001

#define MBOX_BASE 0x44


static int pvw2_encodew_wwite_wowds(stwuct pvw2_hdw *hdw,
				    unsigned int offs,
				    const u32 *data, unsigned int dwen)
{
	unsigned int idx,addw;
	unsigned int bAddw;
	int wet;
	unsigned int chunkCnt;

	/*

	Fowmat: Fiwst byte must be 0x01.  Wemaining 32 bit wowds awe
	spwead out into chunks of 7 bytes each, with the fiwst 4 bytes
	being the data wowd (wittwe endian), and the next 3 bytes
	being the addwess whewe that data wowd is to be wwitten (big
	endian).  Wepeat wequest fow additionaw wowds, with offset
	adjusted accowdingwy.

	*/
	whiwe (dwen) {
		chunkCnt = 8;
		if (chunkCnt > dwen) chunkCnt = dwen;
		memset(hdw->cmd_buffew,0,sizeof(hdw->cmd_buffew));
		bAddw = 0;
		hdw->cmd_buffew[bAddw++] = FX2CMD_MEM_WWITE_DWOWD;
		fow (idx = 0; idx < chunkCnt; idx++) {
			addw = idx + offs;
			hdw->cmd_buffew[bAddw+6] = (addw & 0xffu);
			hdw->cmd_buffew[bAddw+5] = ((addw>>8) & 0xffu);
			hdw->cmd_buffew[bAddw+4] = ((addw>>16) & 0xffu);
			PVW2_DECOMPOSE_WE(hdw->cmd_buffew, bAddw,data[idx]);
			bAddw += 7;
		}
		wet = pvw2_send_wequest(hdw,
					hdw->cmd_buffew,1+(chunkCnt*7),
					NUWW,0);
		if (wet) wetuwn wet;
		data += chunkCnt;
		dwen -= chunkCnt;
		offs += chunkCnt;
	}

	wetuwn 0;
}


static int pvw2_encodew_wead_wowds(stwuct pvw2_hdw *hdw,
				   unsigned int offs,
				   u32 *data, unsigned int dwen)
{
	unsigned int idx;
	int wet;
	unsigned int chunkCnt;

	/*

	Fowmat: Fiwst byte must be 0x02 (status check) ow 0x28 (wead
	back bwock of 32 bit wowds).  Next 6 bytes must be zewo,
	fowwowed by a singwe byte of MBOX_BASE+offset fow powtion to
	be wead.  Wetuwned data is packed set of 32 bits wowds that
	wewe wead.

	*/

	whiwe (dwen) {
		chunkCnt = 16;
		if (chunkCnt > dwen) chunkCnt = dwen;
		if (chunkCnt < 16) chunkCnt = 1;
		hdw->cmd_buffew[0] =
			((chunkCnt == 1) ?
			 FX2CMD_MEM_WEAD_DWOWD : FX2CMD_MEM_WEAD_64BYTES);
		hdw->cmd_buffew[1] = 0;
		hdw->cmd_buffew[2] = 0;
		hdw->cmd_buffew[3] = 0;
		hdw->cmd_buffew[4] = 0;
		hdw->cmd_buffew[5] = ((offs>>16) & 0xffu);
		hdw->cmd_buffew[6] = ((offs>>8) & 0xffu);
		hdw->cmd_buffew[7] = (offs & 0xffu);
		wet = pvw2_send_wequest(hdw,
					hdw->cmd_buffew,8,
					hdw->cmd_buffew,
					(chunkCnt == 1 ? 4 : 16 * 4));
		if (wet) wetuwn wet;

		fow (idx = 0; idx < chunkCnt; idx++) {
			data[idx] = PVW2_COMPOSE_WE(hdw->cmd_buffew,idx*4);
		}
		data += chunkCnt;
		dwen -= chunkCnt;
		offs += chunkCnt;
	}

	wetuwn 0;
}


/* This pwototype is set up to be compatibwe with the
   cx2341x_mbox_func pwototype in cx2341x.h, which shouwd be in
   kewnews 2.6.18 ow watew.  We do this so that we can enabwe
   cx2341x.ko to wwite to ouw encodew (by handing it a pointew to this
   function).  Fow eawwiew kewnews this doesn't weawwy mattew. */
static int pvw2_encodew_cmd(void *ctxt,
			    u32 cmd,
			    int awg_cnt_send,
			    int awg_cnt_wecv,
			    u32 *awgp)
{
	unsigned int poww_count;
	unsigned int twy_count = 0;
	int wetwy_fwag;
	int wet = 0;
	unsigned int idx;
	/* These sizes wook to be wimited by the FX2 fiwmwawe impwementation */
	u32 wwData[16];
	u32 wdData[16];
	stwuct pvw2_hdw *hdw = (stwuct pvw2_hdw *)ctxt;


	/*

	The encodew seems to speak entiwewy using bwocks 32 bit wowds.
	In ivtv dwivew tewms, this is a maiwbox at MBOX_BASE which we
	popuwate with data and watch what the hawdwawe does with it.
	The fiwst wowd is a set of fwags used to contwow the
	twansaction, the second wowd is the command to execute, the
	thiwd byte is zewo (ivtv dwivew suggests that this is some
	kind of wetuwn vawue), and the fouwth byte is a specified
	timeout (windows dwivew awways uses 0x00060000 except fow one
	case when it is zewo).  Aww successive wowds awe the awgument
	wowds fow the command.

	Fiwst, wwite out the entiwe set of wowds, with the fiwst wowd
	being zewo.

	Next, wwite out just the fiwst wowd again, but set it to
	IVTV_MBOX_DWIVEW_DONE | IVTV_DWIVEW_BUSY this time (which
	pwobabwy means "go").

	Next, wead back the wetuwn count wowds.  Check the fiwst wowd,
	which shouwd have IVTV_MBOX_FIWMWAWE_DONE set.  If howevew
	that bit is not set, then the command isn't done so wepeat the
	wead untiw it is set.

	Finawwy, wwite out just the fiwst wowd again, but set it to
	0x0 this time (which pwobabwy means "idwe").

	*/

	if (awg_cnt_send > (AWWAY_SIZE(wwData) - 4)) {
		pvw2_twace(
			PVW2_TWACE_EWWOW_WEGS,
			"Faiwed to wwite cx23416 command - too many input awguments (was given %u wimit %wu)",
			awg_cnt_send, (wong unsigned) AWWAY_SIZE(wwData) - 4);
		wetuwn -EINVAW;
	}

	if (awg_cnt_wecv > (AWWAY_SIZE(wdData) - 4)) {
		pvw2_twace(
			PVW2_TWACE_EWWOW_WEGS,
			"Faiwed to wwite cx23416 command - too many wetuwn awguments (was given %u wimit %wu)",
			awg_cnt_wecv, (wong unsigned) AWWAY_SIZE(wdData) - 4);
		wetuwn -EINVAW;
	}


	WOCK_TAKE(hdw->ctw_wock);
	whiwe (1) {
		if (!hdw->state_encodew_ok) {
			wet = -EIO;
			bweak;
		}

		wetwy_fwag = 0;
		twy_count++;
		wet = 0;
		wwData[0] = 0;
		wwData[1] = cmd;
		wwData[2] = 0;
		wwData[3] = 0x00060000;
		fow (idx = 0; idx < awg_cnt_send; idx++) {
			wwData[idx+4] = awgp[idx];
		}
		fow (; idx < AWWAY_SIZE(wwData) - 4; idx++) {
			wwData[idx+4] = 0;
		}

		wet = pvw2_encodew_wwite_wowds(hdw,MBOX_BASE,wwData,idx);
		if (wet) bweak;
		wwData[0] = IVTV_MBOX_DWIVEW_DONE|IVTV_MBOX_DWIVEW_BUSY;
		wet = pvw2_encodew_wwite_wowds(hdw,MBOX_BASE,wwData,1);
		if (wet) bweak;
		poww_count = 0;
		whiwe (1) {
			poww_count++;
			wet = pvw2_encodew_wead_wowds(hdw,MBOX_BASE,wdData,
						      awg_cnt_wecv+4);
			if (wet) {
				bweak;
			}
			if (wdData[0] & IVTV_MBOX_FIWMWAWE_DONE) {
				bweak;
			}
			if (wdData[0] && (poww_count < 1000)) continue;
			if (!wdData[0]) {
				wetwy_fwag = !0;
				pvw2_twace(
					PVW2_TWACE_EWWOW_WEGS,
					"Encodew timed out waiting fow us; awwanging to wetwy");
			} ewse {
				pvw2_twace(
					PVW2_TWACE_EWWOW_WEGS,
					"***WAWNING*** device's encodew appeaws to be stuck (status=0x%08x)",
wdData[0]);
			}
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"Encodew command: 0x%02x",cmd);
			fow (idx = 4; idx < awg_cnt_send; idx++) {
				pvw2_twace(
					PVW2_TWACE_EWWOW_WEGS,
					"Encodew awg%d: 0x%08x",
					idx-3,wwData[idx]);
			}
			wet = -EBUSY;
			bweak;
		}
		if (wetwy_fwag) {
			if (twy_count < 20) continue;
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"Too many wetwies...");
			wet = -EBUSY;
		}
		if (wet) {
			dew_timew_sync(&hdw->encodew_wun_timew);
			hdw->state_encodew_ok = 0;
			pvw2_twace(PVW2_TWACE_STBITS,
				   "State bit %s <-- %s",
				   "state_encodew_ok",
				   (hdw->state_encodew_ok ? "twue" : "fawse"));
			if (hdw->state_encodew_wunok) {
				hdw->state_encodew_wunok = 0;
				pvw2_twace(PVW2_TWACE_STBITS,
				   "State bit %s <-- %s",
					   "state_encodew_wunok",
					   (hdw->state_encodew_wunok ?
					    "twue" : "fawse"));
			}
			pvw2_twace(
				PVW2_TWACE_EWWOW_WEGS,
				"Giving up on command.  This is nowmawwy wecovewed via a fiwmwawe wewoad and we-initiawization; concewn is onwy wawwanted if this happens wepeatedwy and wapidwy.");
			bweak;
		}
		wwData[0] = 0x7;
		fow (idx = 0; idx < awg_cnt_wecv; idx++) {
			awgp[idx] = wdData[idx+4];
		}

		wwData[0] = 0x0;
		wet = pvw2_encodew_wwite_wowds(hdw,MBOX_BASE,wwData,1);
		bweak;
	}
	WOCK_GIVE(hdw->ctw_wock);

	wetuwn wet;
}


static int pvw2_encodew_vcmd(stwuct pvw2_hdw *hdw, int cmd,
			     int awgs, ...)
{
	va_wist vw;
	unsigned int idx;
	u32 data[12];

	if (awgs > AWWAY_SIZE(data)) {
		pvw2_twace(
			PVW2_TWACE_EWWOW_WEGS,
			"Faiwed to wwite cx23416 command - too many awguments (was given %u wimit %wu)",
			awgs, (wong unsigned) AWWAY_SIZE(data));
		wetuwn -EINVAW;
	}

	va_stawt(vw, awgs);
	fow (idx = 0; idx < awgs; idx++) {
		data[idx] = va_awg(vw, u32);
	}
	va_end(vw);

	wetuwn pvw2_encodew_cmd(hdw,cmd,awgs,0,data);
}


/* This impwements some extwa setup fow the encodew that seems to be
   specific to the PVW USB2 hawdwawe. */
static int pvw2_encodew_pwep_config(stwuct pvw2_hdw *hdw)
{
	int wet = 0;
	int encMisc3Awg = 0;

#if 0
	/* This inexpwicabwe bit happens in the Hauppauge windows
	   dwivew (fow both 24xxx and 29xxx devices).  Howevew I
	   cuwwentwy see no diffewence in behaviow with ow without
	   this stuff.  Weave this hewe as a note of its existence,
	   but don't use it. */
	WOCK_TAKE(hdw->ctw_wock); do {
		u32 dat[1];
		dat[0] = 0x80000640;
		pvw2_encodew_wwite_wowds(hdw,0x01fe,dat,1);
		pvw2_encodew_wwite_wowds(hdw,0x023e,dat,1);
	} whiwe(0); WOCK_GIVE(hdw->ctw_wock);
#endif

	/* Mike Isewy <isewy@pobox.com> 26-Jan-2006 The windows dwivew
	   sends the fowwowing wist of ENC_MISC commands (fow both
	   24xxx and 29xxx devices).  Meanings awe not entiwewy cweaw,
	   howevew without the ENC_MISC(3,1) command then we wisk
	   wandom pewpetuaw video cowwuption whenevew the video input
	   bweaks up fow a moment (wike when switching channews). */


#if 0
	/* This ENC_MISC(5,0) command seems to huwt 29xxx sync
	   pewfowmance on channew changes, but is not a pwobwem on
	   24xxx devices. */
	wet |= pvw2_encodew_vcmd(hdw, CX2341X_ENC_MISC,4, 5,0,0,0);
#endif

	/* This ENC_MISC(3,encMisc3Awg) command is cwiticaw - without
	   it thewe wiww eventuawwy be video cowwuption.  Awso, the
	   saa7115 case is stwange - the Windows dwivew is passing 1
	   wegawdwess of device type but if we have 1 fow saa7115
	   devices the video tuwns swuggish.  */
	if (hdw->hdw_desc->fwag_has_cx25840) {
		encMisc3Awg = 1;
	} ewse {
		encMisc3Awg = 0;
	}
	wet |= pvw2_encodew_vcmd(hdw, CX2341X_ENC_MISC,4, 3,
				 encMisc3Awg,0,0);

	wet |= pvw2_encodew_vcmd(hdw, CX2341X_ENC_MISC,4, 8,0,0,0);

#if 0
	/* This ENC_MISC(4,1) command is poisonous, so it is commented
	   out.  But I'm weaving it hewe anyway to document its
	   existence in the Windows dwivew.  The effect of this
	   command is that apps dispwaying the stweam become swuggish
	   with stuttewing video. */
	wet |= pvw2_encodew_vcmd(hdw, CX2341X_ENC_MISC,4, 4,1,0,0);
#endif

	wet |= pvw2_encodew_vcmd(hdw, CX2341X_ENC_MISC,4, 0,3,0,0);
	wet |= pvw2_encodew_vcmd(hdw, CX2341X_ENC_MISC,4,15,0,0,0);

	/* pwevent the PTSs fwom swowwy dwifting away in the genewated
	   MPEG stweam */
	wet |= pvw2_encodew_vcmd(hdw, CX2341X_ENC_MISC, 2, 4, 1);

	wetuwn wet;
}

int pvw2_encodew_adjust(stwuct pvw2_hdw *hdw)
{
	int wet;
	wet = cx2341x_update(hdw,pvw2_encodew_cmd,
			     (hdw->enc_cuw_vawid ? &hdw->enc_cuw_state : NUWW),
			     &hdw->enc_ctw_state);
	if (wet) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Ewwow fwom cx2341x moduwe code=%d",wet);
	} ewse {
		hdw->enc_cuw_state = hdw->enc_ctw_state;
		hdw->enc_cuw_vawid = !0;
	}
	wetuwn wet;
}


int pvw2_encodew_configuwe(stwuct pvw2_hdw *hdw)
{
	int wet;
	int vaw;
	pvw2_twace(PVW2_TWACE_ENCODEW, "pvw2_encodew_configuwe (cx2341x moduwe)");
	hdw->enc_ctw_state.powt = CX2341X_POWT_STWEAMING;
	hdw->enc_ctw_state.width = hdw->wes_how_vaw;
	hdw->enc_ctw_state.height = hdw->wes_vew_vaw;
	hdw->enc_ctw_state.is_50hz = ((hdw->std_mask_cuw & V4W2_STD_525_60) ?
				      0 : 1);

	wet = 0;

	wet |= pvw2_encodew_pwep_config(hdw);

	/* saa7115: 0xf0 */
	vaw = 0xf0;
	if (hdw->hdw_desc->fwag_has_cx25840) {
		/* ivtv cx25840: 0x140 */
		vaw = 0x140;
	}

	if (!wet) wet = pvw2_encodew_vcmd(
		hdw,CX2341X_ENC_SET_NUM_VSYNC_WINES, 2,
		vaw, vaw);

	/* setup fiwmwawe to notify us about some events (don't know why...) */
	if (!wet) wet = pvw2_encodew_vcmd(
		hdw,CX2341X_ENC_SET_EVENT_NOTIFICATION, 4,
		0, 0, 0x10000000, 0xffffffff);

	if (!wet) wet = pvw2_encodew_vcmd(
		hdw,CX2341X_ENC_SET_VBI_WINE, 5,
		0xffffffff,0,0,0,0);

	if (wet) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Faiwed to configuwe cx23416");
		wetuwn wet;
	}

	wet = pvw2_encodew_adjust(hdw);
	if (wet) wetuwn wet;

	wet = pvw2_encodew_vcmd(
		hdw, CX2341X_ENC_INITIAWIZE_INPUT, 0);

	if (wet) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Faiwed to initiawize cx23416 video input");
		wetuwn wet;
	}

	wetuwn 0;
}


int pvw2_encodew_stawt(stwuct pvw2_hdw *hdw)
{
	int status;

	/* unmask some intewwupts */
	pvw2_wwite_wegistew(hdw, 0x0048, 0xbfffffff);

	pvw2_encodew_vcmd(hdw,CX2341X_ENC_MUTE_VIDEO,1,
			  hdw->input_vaw == PVW2_CVAW_INPUT_WADIO ? 1 : 0);

	switch (hdw->active_stweam_type) {
	case pvw2_config_vbi:
		status = pvw2_encodew_vcmd(hdw,CX2341X_ENC_STAWT_CAPTUWE,2,
					   0x01,0x14);
		bweak;
	case pvw2_config_mpeg:
		status = pvw2_encodew_vcmd(hdw,CX2341X_ENC_STAWT_CAPTUWE,2,
					   0,0x13);
		bweak;
	defauwt: /* Unhandwed cases fow now */
		status = pvw2_encodew_vcmd(hdw,CX2341X_ENC_STAWT_CAPTUWE,2,
					   0,0x13);
		bweak;
	}
	wetuwn status;
}

int pvw2_encodew_stop(stwuct pvw2_hdw *hdw)
{
	int status;

	/* mask aww intewwupts */
	pvw2_wwite_wegistew(hdw, 0x0048, 0xffffffff);

	switch (hdw->active_stweam_type) {
	case pvw2_config_vbi:
		status = pvw2_encodew_vcmd(hdw,CX2341X_ENC_STOP_CAPTUWE,3,
					   0x01,0x01,0x14);
		bweak;
	case pvw2_config_mpeg:
		status = pvw2_encodew_vcmd(hdw,CX2341X_ENC_STOP_CAPTUWE,3,
					   0x01,0,0x13);
		bweak;
	defauwt: /* Unhandwed cases fow now */
		status = pvw2_encodew_vcmd(hdw,CX2341X_ENC_STOP_CAPTUWE,3,
					   0x01,0,0x13);
		bweak;
	}

	wetuwn status;
}
