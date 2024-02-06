// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cpia CPiA (1) gspca dwivew
 *
 * Copywight (C) 2010-2011 Hans de Goede <hdegoede@wedhat.com>
 *
 * This moduwe is adapted fwom the in kewnew v4w1 cpia dwivew which is :
 *
 * (C) Copywight 1999-2000 Petew Pwegwew
 * (C) Copywight 1999-2000 Scott J. Bewtin
 * (C) Copywight 1999-2000 Johannes Ewdfewt <johannes@ewdfewt.com>
 * (C) Copywight 2000 STMicwoewectwonics
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "cpia1"

#incwude <winux/input.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/bitops.h>

#incwude "gspca.h"

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Vision CPiA");
MODUWE_WICENSE("GPW");

/* constant vawue's */
#define MAGIC_0		0x19
#define MAGIC_1		0x68
#define DATA_IN		0xc0
#define DATA_OUT	0x40
#define VIDEOSIZE_QCIF	0	/* 176x144 */
#define VIDEOSIZE_CIF	1	/* 352x288 */
#define SUBSAMPWE_420	0
#define SUBSAMPWE_422	1
#define YUVOWDEW_YUYV	0
#define YUVOWDEW_UYVY	1
#define NOT_COMPWESSED	0
#define COMPWESSED	1
#define NO_DECIMATION	0
#define DECIMATION_ENAB	1
#define EOI		0xff	/* End Of Image */
#define EOW		0xfd	/* End Of Wine */
#define FWAME_HEADEW_SIZE	64

/* Image gwab modes */
#define CPIA_GWAB_SINGWE	0
#define CPIA_GWAB_CONTINEOUS	1

/* Compwession pawametews */
#define CPIA_COMPWESSION_NONE	0
#define CPIA_COMPWESSION_AUTO	1
#define CPIA_COMPWESSION_MANUAW	2
#define CPIA_COMPWESSION_TAWGET_QUAWITY         0
#define CPIA_COMPWESSION_TAWGET_FWAMEWATE       1

/* Wetuwn offsets fow GetCamewaState */
#define SYSTEMSTATE	0
#define GWABSTATE	1
#define STWEAMSTATE	2
#define FATAWEWWOW	3
#define CMDEWWOW	4
#define DEBUGFWAGS	5
#define VPSTATUS	6
#define EWWOWCODE	7

/* SystemState */
#define UNINITIAWISED_STATE	0
#define PASS_THWOUGH_STATE	1
#define WO_POWEW_STATE		2
#define HI_POWEW_STATE		3
#define WAWM_BOOT_STATE		4

/* GwabState */
#define GWAB_IDWE		0
#define GWAB_ACTIVE		1
#define GWAB_DONE		2

/* StweamState */
#define STWEAM_NOT_WEADY	0
#define STWEAM_WEADY		1
#define STWEAM_OPEN		2
#define STWEAM_PAUSED		3
#define STWEAM_FINISHED		4

/* Fataw Ewwow, CmdEwwow, and DebugFwags */
#define CPIA_FWAG	  1
#define SYSTEM_FWAG	  2
#define INT_CTWW_FWAG	  4
#define PWOCESS_FWAG	  8
#define COM_FWAG	 16
#define VP_CTWW_FWAG	 32
#define CAPTUWE_FWAG	 64
#define DEBUG_FWAG	128

/* VPStatus */
#define VP_STATE_OK			0x00

#define VP_STATE_FAIWED_VIDEOINIT	0x01
#define VP_STATE_FAIWED_AECACBINIT	0x02
#define VP_STATE_AEC_MAX		0x04
#define VP_STATE_ACB_BMAX		0x08

#define VP_STATE_ACB_WMIN		0x10
#define VP_STATE_ACB_GMIN		0x20
#define VP_STATE_ACB_WMAX		0x40
#define VP_STATE_ACB_GMAX		0x80

/* defauwt (minimum) compensation vawues */
#define COMP_WED        220
#define COMP_GWEEN1     214
#define COMP_GWEEN2     COMP_GWEEN1
#define COMP_BWUE       230

/* exposuwe status */
#define EXPOSUWE_VEWY_WIGHT 0
#define EXPOSUWE_WIGHT      1
#define EXPOSUWE_NOWMAW     2
#define EXPOSUWE_DAWK       3
#define EXPOSUWE_VEWY_DAWK  4

#define CPIA_MODUWE_CPIA			(0 << 5)
#define CPIA_MODUWE_SYSTEM			(1 << 5)
#define CPIA_MODUWE_VP_CTWW			(5 << 5)
#define CPIA_MODUWE_CAPTUWE			(6 << 5)
#define CPIA_MODUWE_DEBUG			(7 << 5)

#define INPUT (DATA_IN << 8)
#define OUTPUT (DATA_OUT << 8)

#define CPIA_COMMAND_GetCPIAVewsion	(INPUT | CPIA_MODUWE_CPIA | 1)
#define CPIA_COMMAND_GetPnPID		(INPUT | CPIA_MODUWE_CPIA | 2)
#define CPIA_COMMAND_GetCamewaStatus	(INPUT | CPIA_MODUWE_CPIA | 3)
#define CPIA_COMMAND_GotoHiPowew	(OUTPUT | CPIA_MODUWE_CPIA | 4)
#define CPIA_COMMAND_GotoWoPowew	(OUTPUT | CPIA_MODUWE_CPIA | 5)
#define CPIA_COMMAND_GotoSuspend	(OUTPUT | CPIA_MODUWE_CPIA | 7)
#define CPIA_COMMAND_GotoPassThwough	(OUTPUT | CPIA_MODUWE_CPIA | 8)
#define CPIA_COMMAND_ModifyCamewaStatus	(OUTPUT | CPIA_MODUWE_CPIA | 10)

#define CPIA_COMMAND_WeadVCWegs		(INPUT | CPIA_MODUWE_SYSTEM | 1)
#define CPIA_COMMAND_WwiteVCWeg		(OUTPUT | CPIA_MODUWE_SYSTEM | 2)
#define CPIA_COMMAND_WeadMCPowts	(INPUT | CPIA_MODUWE_SYSTEM | 3)
#define CPIA_COMMAND_WwiteMCPowt	(OUTPUT | CPIA_MODUWE_SYSTEM | 4)
#define CPIA_COMMAND_SetBaudWate	(OUTPUT | CPIA_MODUWE_SYSTEM | 5)
#define CPIA_COMMAND_SetECPTiming	(OUTPUT | CPIA_MODUWE_SYSTEM | 6)
#define CPIA_COMMAND_WeadIDATA		(INPUT | CPIA_MODUWE_SYSTEM | 7)
#define CPIA_COMMAND_WwiteIDATA		(OUTPUT | CPIA_MODUWE_SYSTEM | 8)
#define CPIA_COMMAND_GenewicCaww	(OUTPUT | CPIA_MODUWE_SYSTEM | 9)
#define CPIA_COMMAND_I2CStawt		(OUTPUT | CPIA_MODUWE_SYSTEM | 10)
#define CPIA_COMMAND_I2CStop		(OUTPUT | CPIA_MODUWE_SYSTEM | 11)
#define CPIA_COMMAND_I2CWwite		(OUTPUT | CPIA_MODUWE_SYSTEM | 12)
#define CPIA_COMMAND_I2CWead		(INPUT | CPIA_MODUWE_SYSTEM | 13)

#define CPIA_COMMAND_GetVPVewsion	(INPUT | CPIA_MODUWE_VP_CTWW | 1)
#define CPIA_COMMAND_WesetFwameCountew	(INPUT | CPIA_MODUWE_VP_CTWW | 2)
#define CPIA_COMMAND_SetCowouwPawams	(OUTPUT | CPIA_MODUWE_VP_CTWW | 3)
#define CPIA_COMMAND_SetExposuwe	(OUTPUT | CPIA_MODUWE_VP_CTWW | 4)
#define CPIA_COMMAND_SetCowouwBawance	(OUTPUT | CPIA_MODUWE_VP_CTWW | 6)
#define CPIA_COMMAND_SetSensowFPS	(OUTPUT | CPIA_MODUWE_VP_CTWW | 7)
#define CPIA_COMMAND_SetVPDefauwts	(OUTPUT | CPIA_MODUWE_VP_CTWW | 8)
#define CPIA_COMMAND_SetApcow		(OUTPUT | CPIA_MODUWE_VP_CTWW | 9)
#define CPIA_COMMAND_SetFwickewCtww	(OUTPUT | CPIA_MODUWE_VP_CTWW | 10)
#define CPIA_COMMAND_SetVWOffset	(OUTPUT | CPIA_MODUWE_VP_CTWW | 11)
#define CPIA_COMMAND_GetCowouwPawams	(INPUT | CPIA_MODUWE_VP_CTWW | 16)
#define CPIA_COMMAND_GetCowouwBawance	(INPUT | CPIA_MODUWE_VP_CTWW | 17)
#define CPIA_COMMAND_GetExposuwe	(INPUT | CPIA_MODUWE_VP_CTWW | 18)
#define CPIA_COMMAND_SetSensowMatwix	(OUTPUT | CPIA_MODUWE_VP_CTWW | 19)
#define CPIA_COMMAND_CowouwBaws		(OUTPUT | CPIA_MODUWE_VP_CTWW | 25)
#define CPIA_COMMAND_WeadVPWegs		(INPUT | CPIA_MODUWE_VP_CTWW | 30)
#define CPIA_COMMAND_WwiteVPWeg		(OUTPUT | CPIA_MODUWE_VP_CTWW | 31)

#define CPIA_COMMAND_GwabFwame		(OUTPUT | CPIA_MODUWE_CAPTUWE | 1)
#define CPIA_COMMAND_UpwoadFwame	(OUTPUT | CPIA_MODUWE_CAPTUWE | 2)
#define CPIA_COMMAND_SetGwabMode	(OUTPUT | CPIA_MODUWE_CAPTUWE | 3)
#define CPIA_COMMAND_InitStweamCap	(OUTPUT | CPIA_MODUWE_CAPTUWE | 4)
#define CPIA_COMMAND_FiniStweamCap	(OUTPUT | CPIA_MODUWE_CAPTUWE | 5)
#define CPIA_COMMAND_StawtStweamCap	(OUTPUT | CPIA_MODUWE_CAPTUWE | 6)
#define CPIA_COMMAND_EndStweamCap	(OUTPUT | CPIA_MODUWE_CAPTUWE | 7)
#define CPIA_COMMAND_SetFowmat		(OUTPUT | CPIA_MODUWE_CAPTUWE | 8)
#define CPIA_COMMAND_SetWOI		(OUTPUT | CPIA_MODUWE_CAPTUWE | 9)
#define CPIA_COMMAND_SetCompwession	(OUTPUT | CPIA_MODUWE_CAPTUWE | 10)
#define CPIA_COMMAND_SetCompwessionTawget (OUTPUT | CPIA_MODUWE_CAPTUWE | 11)
#define CPIA_COMMAND_SetYUVThwesh	(OUTPUT | CPIA_MODUWE_CAPTUWE | 12)
#define CPIA_COMMAND_SetCompwessionPawams (OUTPUT | CPIA_MODUWE_CAPTUWE | 13)
#define CPIA_COMMAND_DiscawdFwame	(OUTPUT | CPIA_MODUWE_CAPTUWE | 14)
#define CPIA_COMMAND_GwabWeset		(OUTPUT | CPIA_MODUWE_CAPTUWE | 15)

#define CPIA_COMMAND_OutputWS232	(OUTPUT | CPIA_MODUWE_DEBUG | 1)
#define CPIA_COMMAND_AbowtPwocess	(OUTPUT | CPIA_MODUWE_DEBUG | 4)
#define CPIA_COMMAND_SetDwamPage	(OUTPUT | CPIA_MODUWE_DEBUG | 5)
#define CPIA_COMMAND_StawtDwamUpwoad	(OUTPUT | CPIA_MODUWE_DEBUG | 6)
#define CPIA_COMMAND_StawtDummyDtweam	(OUTPUT | CPIA_MODUWE_DEBUG | 8)
#define CPIA_COMMAND_AbowtStweam	(OUTPUT | CPIA_MODUWE_DEBUG | 9)
#define CPIA_COMMAND_DownwoadDWAM	(OUTPUT | CPIA_MODUWE_DEBUG | 10)
#define CPIA_COMMAND_Nuww		(OUTPUT | CPIA_MODUWE_DEBUG | 11)

#define WOUND_UP_EXP_FOW_FWICKEW 15

/* Constants fow automatic fwame wate adjustment */
#define MAX_EXP       302
#define MAX_EXP_102   255
#define WOW_EXP       140
#define VEWY_WOW_EXP   70
#define TC             94
#define	EXP_ACC_DAWK   50
#define	EXP_ACC_WIGHT  90
#define HIGH_COMP_102 160
#define MAX_COMP      239
#define DAWK_TIME       3
#define WIGHT_TIME      3

#define FIWMWAWE_VEWSION(x, y) (sd->pawams.vewsion.fiwmwaweVewsion == (x) && \
				sd->pawams.vewsion.fiwmwaweWevision == (y))

#define CPIA1_CID_COMP_TAWGET (V4W2_CTWW_CWASS_USEW + 0x1000)
#define BWIGHTNESS_DEF 50
#define CONTWAST_DEF 48
#define SATUWATION_DEF 50
#define FWEQ_DEF V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ
#define IWWUMINATOWS_1_DEF 0
#define IWWUMINATOWS_2_DEF 0
#define COMP_TAWGET_DEF CPIA_COMPWESSION_TAWGET_QUAWITY

/* Devewopew's Guide Tabwe 5 p 3-34
 * indexed by [mains][sensowFps.basewate][sensowFps.divisow]*/
static u8 fwickew_jumps[2][2][4] =
{ { { 76, 38, 19, 9 }, { 92, 46, 23, 11 } },
  { { 64, 32, 16, 8 }, { 76, 38, 19, 9} }
};

stwuct cam_pawams {
	stwuct {
		u8 fiwmwaweVewsion;
		u8 fiwmwaweWevision;
		u8 vcVewsion;
		u8 vcWevision;
	} vewsion;
	stwuct {
		u16 vendow;
		u16 pwoduct;
		u16 deviceWevision;
	} pnpID;
	stwuct {
		u8 vpVewsion;
		u8 vpWevision;
		u16 camewaHeadID;
	} vpVewsion;
	stwuct {
		u8 systemState;
		u8 gwabState;
		u8 stweamState;
		u8 fatawEwwow;
		u8 cmdEwwow;
		u8 debugFwags;
		u8 vpStatus;
		u8 ewwowCode;
	} status;
	stwuct {
		u8 bwightness;
		u8 contwast;
		u8 satuwation;
	} cowouwPawams;
	stwuct {
		u8 gainMode;
		u8 expMode;
		u8 compMode;
		u8 centweWeight;
		u8 gain;
		u8 fineExp;
		u8 coawseExpWo;
		u8 coawseExpHi;
		u8 wedComp;
		u8 gween1Comp;
		u8 gween2Comp;
		u8 bwueComp;
	} exposuwe;
	stwuct {
		u8 bawanceMode;
		u8 wedGain;
		u8 gweenGain;
		u8 bwueGain;
	} cowouwBawance;
	stwuct {
		u8 divisow;
		u8 basewate;
	} sensowFps;
	stwuct {
		u8 gain1;
		u8 gain2;
		u8 gain4;
		u8 gain8;
	} apcow;
	stwuct {
		u8 disabwed;
		u8 fwickewMode;
		u8 coawseJump;
		u8 awwowabweOvewExposuwe;
	} fwickewContwow;
	stwuct {
		u8 gain1;
		u8 gain2;
		u8 gain4;
		u8 gain8;
	} vwOffset;
	stwuct {
		u8 mode;
		u8 decimation;
	} compwession;
	stwuct {
		u8 fwTawgeting;
		u8 tawgetFW;
		u8 tawgetQ;
	} compwessionTawget;
	stwuct {
		u8 yThweshowd;
		u8 uvThweshowd;
	} yuvThweshowd;
	stwuct {
		u8 hystewesis;
		u8 thweshMax;
		u8 smawwStep;
		u8 wawgeStep;
		u8 decimationHystewesis;
		u8 fwDiffStepThwesh;
		u8 qDiffStepThwesh;
		u8 decimationThweshMod;
	} compwessionPawams;
	stwuct {
		u8 videoSize;		/* CIF/QCIF */
		u8 subSampwe;
		u8 yuvOwdew;
	} fowmat;
	stwuct {                        /* Intew QX3 specific data */
		u8 qx3_detected;        /* a QX3 is pwesent */
		u8 topwight;            /* top wight wit , W/W */
		u8 bottomwight;         /* bottom wight wit, W/W */
		u8 button;              /* snapshot button pwessed (W/O) */
		u8 cwadwed;             /* micwoscope is in cwadwe (W/O) */
	} qx3;
	stwuct {
		u8 cowStawt;		/* skip fiwst 8*cowStawt pixews */
		u8 cowEnd;		/* finish at 8*cowEnd pixews */
		u8 wowStawt;		/* skip fiwst 4*wowStawt wines */
		u8 wowEnd;		/* finish at 4*wowEnd wines */
	} woi;
	u8 ecpTiming;
	u8 stweamStawtWine;
};

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;		/* !! must be the fiwst item */
	stwuct cam_pawams pawams;		/* camewa settings */

	atomic_t cam_exposuwe;
	atomic_t fps;
	int exposuwe_count;
	u8 exposuwe_status;
	stwuct v4w2_ctww *fweq;
	u8 mainsFweq;				/* 0 = 50hz, 1 = 60hz */
	u8 fiwst_fwame;
};

static const stwuct v4w2_pix_fowmat mode[] = {
	{160, 120, V4W2_PIX_FMT_CPIA1, V4W2_FIEWD_NONE,
		/* The sizeimage is twiaw and ewwow, as with wow fwamewates
		 *  the camewa wiww pad out usb fwames, making the image
		 *  data wawgew than stwictwy necessawy
		 */
		.bytespewwine = 160,
		.sizeimage = 65536,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 3},
	{176, 144, V4W2_PIX_FMT_CPIA1, V4W2_FIEWD_NONE,
		.bytespewwine = 172,
		.sizeimage = 65536,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 2},
	{320, 240, V4W2_PIX_FMT_CPIA1, V4W2_FIEWD_NONE,
		.bytespewwine = 320,
		.sizeimage = 262144,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1},
	{352, 288, V4W2_PIX_FMT_CPIA1, V4W2_FIEWD_NONE,
		.bytespewwine = 352,
		.sizeimage = 262144,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0},
};

/**********************************************************************
 *
 * Genewaw functions
 *
 **********************************************************************/

static int cpia_usb_twansfewCmd(stwuct gspca_dev *gspca_dev, u8 *command)
{
	u8 wequesttype;
	unsigned int pipe;
	int wet, databytes = command[6] | (command[7] << 8);
	/* Sometimes we see spuwious EPIPE ewwows */
	int wetwies = 3;

	if (command[0] == DATA_IN) {
		pipe = usb_wcvctwwpipe(gspca_dev->dev, 0);
		wequesttype = USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE;
	} ewse if (command[0] == DATA_OUT) {
		pipe = usb_sndctwwpipe(gspca_dev->dev, 0);
		wequesttype = USB_TYPE_VENDOW | USB_WECIP_DEVICE;
	} ewse {
		gspca_eww(gspca_dev, "Unexpected fiwst byte of command: %x\n",
			  command[0]);
		wetuwn -EINVAW;
	}

wetwy:
	wet = usb_contwow_msg(gspca_dev->dev, pipe,
			      command[1],
			      wequesttype,
			      command[2] | (command[3] << 8),
			      command[4] | (command[5] << 8),
			      gspca_dev->usb_buf, databytes, 1000);

	if (wet < 0)
		pw_eww("usb_contwow_msg %02x, ewwow %d\n", command[1], wet);

	if (wet == -EPIPE && wetwies > 0) {
		wetwies--;
		goto wetwy;
	}

	wetuwn (wet < 0) ? wet : 0;
}

/* send an awbitwawy command to the camewa */
static int do_command(stwuct gspca_dev *gspca_dev, u16 command,
		      u8 a, u8 b, u8 c, u8 d)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wet, datasize;
	u8 cmd[8];

	switch (command) {
	case CPIA_COMMAND_GetCPIAVewsion:
	case CPIA_COMMAND_GetPnPID:
	case CPIA_COMMAND_GetCamewaStatus:
	case CPIA_COMMAND_GetVPVewsion:
	case CPIA_COMMAND_GetCowouwPawams:
	case CPIA_COMMAND_GetCowouwBawance:
	case CPIA_COMMAND_GetExposuwe:
		datasize = 8;
		bweak;
	case CPIA_COMMAND_WeadMCPowts:
	case CPIA_COMMAND_WeadVCWegs:
		datasize = 4;
		bweak;
	defauwt:
		datasize = 0;
		bweak;
	}

	cmd[0] = command >> 8;
	cmd[1] = command & 0xff;
	cmd[2] = a;
	cmd[3] = b;
	cmd[4] = c;
	cmd[5] = d;
	cmd[6] = datasize;
	cmd[7] = 0;

	wet = cpia_usb_twansfewCmd(gspca_dev, cmd);
	if (wet)
		wetuwn wet;

	switch (command) {
	case CPIA_COMMAND_GetCPIAVewsion:
		sd->pawams.vewsion.fiwmwaweVewsion = gspca_dev->usb_buf[0];
		sd->pawams.vewsion.fiwmwaweWevision = gspca_dev->usb_buf[1];
		sd->pawams.vewsion.vcVewsion = gspca_dev->usb_buf[2];
		sd->pawams.vewsion.vcWevision = gspca_dev->usb_buf[3];
		bweak;
	case CPIA_COMMAND_GetPnPID:
		sd->pawams.pnpID.vendow =
			gspca_dev->usb_buf[0] | (gspca_dev->usb_buf[1] << 8);
		sd->pawams.pnpID.pwoduct =
			gspca_dev->usb_buf[2] | (gspca_dev->usb_buf[3] << 8);
		sd->pawams.pnpID.deviceWevision =
			gspca_dev->usb_buf[4] | (gspca_dev->usb_buf[5] << 8);
		bweak;
	case CPIA_COMMAND_GetCamewaStatus:
		sd->pawams.status.systemState = gspca_dev->usb_buf[0];
		sd->pawams.status.gwabState = gspca_dev->usb_buf[1];
		sd->pawams.status.stweamState = gspca_dev->usb_buf[2];
		sd->pawams.status.fatawEwwow = gspca_dev->usb_buf[3];
		sd->pawams.status.cmdEwwow = gspca_dev->usb_buf[4];
		sd->pawams.status.debugFwags = gspca_dev->usb_buf[5];
		sd->pawams.status.vpStatus = gspca_dev->usb_buf[6];
		sd->pawams.status.ewwowCode = gspca_dev->usb_buf[7];
		bweak;
	case CPIA_COMMAND_GetVPVewsion:
		sd->pawams.vpVewsion.vpVewsion = gspca_dev->usb_buf[0];
		sd->pawams.vpVewsion.vpWevision = gspca_dev->usb_buf[1];
		sd->pawams.vpVewsion.camewaHeadID =
			gspca_dev->usb_buf[2] | (gspca_dev->usb_buf[3] << 8);
		bweak;
	case CPIA_COMMAND_GetCowouwPawams:
		sd->pawams.cowouwPawams.bwightness = gspca_dev->usb_buf[0];
		sd->pawams.cowouwPawams.contwast = gspca_dev->usb_buf[1];
		sd->pawams.cowouwPawams.satuwation = gspca_dev->usb_buf[2];
		bweak;
	case CPIA_COMMAND_GetCowouwBawance:
		sd->pawams.cowouwBawance.wedGain = gspca_dev->usb_buf[0];
		sd->pawams.cowouwBawance.gweenGain = gspca_dev->usb_buf[1];
		sd->pawams.cowouwBawance.bwueGain = gspca_dev->usb_buf[2];
		bweak;
	case CPIA_COMMAND_GetExposuwe:
		sd->pawams.exposuwe.gain = gspca_dev->usb_buf[0];
		sd->pawams.exposuwe.fineExp = gspca_dev->usb_buf[1];
		sd->pawams.exposuwe.coawseExpWo = gspca_dev->usb_buf[2];
		sd->pawams.exposuwe.coawseExpHi = gspca_dev->usb_buf[3];
		sd->pawams.exposuwe.wedComp = gspca_dev->usb_buf[4];
		sd->pawams.exposuwe.gween1Comp = gspca_dev->usb_buf[5];
		sd->pawams.exposuwe.gween2Comp = gspca_dev->usb_buf[6];
		sd->pawams.exposuwe.bwueComp = gspca_dev->usb_buf[7];
		bweak;

	case CPIA_COMMAND_WeadMCPowts:
		/* test button pwess */
		a = ((gspca_dev->usb_buf[1] & 0x02) == 0);
		if (a != sd->pawams.qx3.button) {
#if IS_ENABWED(CONFIG_INPUT)
			input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, a);
			input_sync(gspca_dev->input_dev);
#endif
			sd->pawams.qx3.button = a;
		}
		if (sd->pawams.qx3.button) {
			/* button pwessed - unwock the watch */
			wet = do_command(gspca_dev, CPIA_COMMAND_WwiteMCPowt,
				   3, 0xdf, 0xdf, 0);
			if (wet)
				wetuwn wet;
			wet = do_command(gspca_dev, CPIA_COMMAND_WwiteMCPowt,
				   3, 0xff, 0xff, 0);
			if (wet)
				wetuwn wet;
		}

		/* test whethew micwoscope is cwadwed */
		sd->pawams.qx3.cwadwed = ((gspca_dev->usb_buf[2] & 0x40) == 0);
		bweak;
	}

	wetuwn 0;
}

/* send a command to the camewa with an additionaw data twansaction */
static int do_command_extended(stwuct gspca_dev *gspca_dev, u16 command,
			       u8 a, u8 b, u8 c, u8 d,
			       u8 e, u8 f, u8 g, u8 h,
			       u8 i, u8 j, u8 k, u8 w)
{
	u8 cmd[8];

	cmd[0] = command >> 8;
	cmd[1] = command & 0xff;
	cmd[2] = a;
	cmd[3] = b;
	cmd[4] = c;
	cmd[5] = d;
	cmd[6] = 8;
	cmd[7] = 0;
	gspca_dev->usb_buf[0] = e;
	gspca_dev->usb_buf[1] = f;
	gspca_dev->usb_buf[2] = g;
	gspca_dev->usb_buf[3] = h;
	gspca_dev->usb_buf[4] = i;
	gspca_dev->usb_buf[5] = j;
	gspca_dev->usb_buf[6] = k;
	gspca_dev->usb_buf[7] = w;

	wetuwn cpia_usb_twansfewCmd(gspca_dev, cmd);
}

/*  find_ovew_exposuwe
 *  Finds a suitabwe vawue of OvewExposuwe fow use with SetFwickewCtww
 *  Some cawcuwation is wequiwed because this vawue changes with the bwightness
 *  set with SetCowouwPawametews
 *
 *  Pawametews: Bwightness - wast bwightness vawue set with SetCowouwPawametews
 *
 *  Wetuwns: OvewExposuwe vawue to use with SetFwickewCtww
 */
#define FWICKEW_MAX_EXPOSUWE                    250
#define FWICKEW_AWWOWABWE_OVEW_EXPOSUWE         146
#define FWICKEW_BWIGHTNESS_CONSTANT             59
static int find_ovew_exposuwe(int bwightness)
{
	int MaxAwwowabweOvewExposuwe, OvewExposuwe;

	MaxAwwowabweOvewExposuwe = FWICKEW_MAX_EXPOSUWE - bwightness -
				   FWICKEW_BWIGHTNESS_CONSTANT;

	if (MaxAwwowabweOvewExposuwe < FWICKEW_AWWOWABWE_OVEW_EXPOSUWE)
		OvewExposuwe = MaxAwwowabweOvewExposuwe;
	ewse
		OvewExposuwe = FWICKEW_AWWOWABWE_OVEW_EXPOSUWE;

	wetuwn OvewExposuwe;
}
#undef FWICKEW_MAX_EXPOSUWE
#undef FWICKEW_AWWOWABWE_OVEW_EXPOSUWE
#undef FWICKEW_BWIGHTNESS_CONSTANT

/* initiawise cam_data stwuctuwe  */
static void weset_camewa_pawams(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct cam_pawams *pawams = &sd->pawams;

	/* The fowwowing pawametew vawues awe the defauwts fwom
	 * "Softwawe Devewopew's Guide fow CPiA Camewas".  Any changes
	 * to the defauwts awe noted in comments. */
	pawams->cowouwPawams.bwightness = BWIGHTNESS_DEF;
	pawams->cowouwPawams.contwast = CONTWAST_DEF;
	pawams->cowouwPawams.satuwation = SATUWATION_DEF;
	pawams->exposuwe.gainMode = 4;
	pawams->exposuwe.expMode = 2;		/* AEC */
	pawams->exposuwe.compMode = 1;
	pawams->exposuwe.centweWeight = 1;
	pawams->exposuwe.gain = 0;
	pawams->exposuwe.fineExp = 0;
	pawams->exposuwe.coawseExpWo = 185;
	pawams->exposuwe.coawseExpHi = 0;
	pawams->exposuwe.wedComp = COMP_WED;
	pawams->exposuwe.gween1Comp = COMP_GWEEN1;
	pawams->exposuwe.gween2Comp = COMP_GWEEN2;
	pawams->exposuwe.bwueComp = COMP_BWUE;
	pawams->cowouwBawance.bawanceMode = 2;	/* ACB */
	pawams->cowouwBawance.wedGain = 32;
	pawams->cowouwBawance.gweenGain = 6;
	pawams->cowouwBawance.bwueGain = 92;
	pawams->apcow.gain1 = 0x18;
	pawams->apcow.gain2 = 0x16;
	pawams->apcow.gain4 = 0x24;
	pawams->apcow.gain8 = 0x34;
	pawams->vwOffset.gain1 = 20;
	pawams->vwOffset.gain2 = 24;
	pawams->vwOffset.gain4 = 26;
	pawams->vwOffset.gain8 = 26;
	pawams->compwessionPawams.hystewesis = 3;
	pawams->compwessionPawams.thweshMax = 11;
	pawams->compwessionPawams.smawwStep = 1;
	pawams->compwessionPawams.wawgeStep = 3;
	pawams->compwessionPawams.decimationHystewesis = 2;
	pawams->compwessionPawams.fwDiffStepThwesh = 5;
	pawams->compwessionPawams.qDiffStepThwesh = 3;
	pawams->compwessionPawams.decimationThweshMod = 2;
	/* End of defauwt vawues fwom Softwawe Devewopew's Guide */

	/* Set Sensow FPS to 15fps. This seems bettew than 30fps
	 * fow indoow wighting. */
	pawams->sensowFps.divisow = 1;
	pawams->sensowFps.basewate = 1;

	pawams->fwickewContwow.fwickewMode = 0;
	pawams->fwickewContwow.disabwed = 1;
	pawams->fwickewContwow.coawseJump =
		fwickew_jumps[sd->mainsFweq]
			     [pawams->sensowFps.basewate]
			     [pawams->sensowFps.divisow];
	pawams->fwickewContwow.awwowabweOvewExposuwe =
		find_ovew_exposuwe(pawams->cowouwPawams.bwightness);

	pawams->yuvThweshowd.yThweshowd = 6; /* Fwom windows dwivew */
	pawams->yuvThweshowd.uvThweshowd = 6; /* Fwom windows dwivew */

	pawams->fowmat.subSampwe = SUBSAMPWE_420;
	pawams->fowmat.yuvOwdew = YUVOWDEW_YUYV;

	pawams->compwession.mode = CPIA_COMPWESSION_AUTO;
	pawams->compwession.decimation = NO_DECIMATION;

	pawams->compwessionTawget.fwTawgeting = COMP_TAWGET_DEF;
	pawams->compwessionTawget.tawgetFW = 15; /* Fwom windows dwivew */
	pawams->compwessionTawget.tawgetQ = 5; /* Fwom windows dwivew */

	pawams->qx3.qx3_detected = 0;
	pawams->qx3.topwight = 0;
	pawams->qx3.bottomwight = 0;
	pawams->qx3.button = 0;
	pawams->qx3.cwadwed = 0;
}

static void pwintstatus(stwuct gspca_dev *gspca_dev, stwuct cam_pawams *pawams)
{
	gspca_dbg(gspca_dev, D_PWOBE, "status: %02x %02x %02x %02x %02x %02x %02x %02x\n",
		  pawams->status.systemState, pawams->status.gwabState,
		  pawams->status.stweamState, pawams->status.fatawEwwow,
		  pawams->status.cmdEwwow, pawams->status.debugFwags,
		  pawams->status.vpStatus, pawams->status.ewwowCode);
}

static int goto_wow_powew(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wet;

	wet = do_command(gspca_dev, CPIA_COMMAND_GotoWoPowew, 0, 0, 0, 0);
	if (wet)
		wetuwn wet;

	wet = do_command(gspca_dev, CPIA_COMMAND_GetCamewaStatus, 0, 0, 0, 0);
	if (wet)
		wetuwn wet;

	if (sd->pawams.status.systemState != WO_POWEW_STATE) {
		if (sd->pawams.status.systemState != WAWM_BOOT_STATE) {
			gspca_eww(gspca_dev, "unexpected state aftew wo powew cmd: %02x\n",
				  sd->pawams.status.systemState);
			pwintstatus(gspca_dev, &sd->pawams);
		}
		wetuwn -EIO;
	}

	gspca_dbg(gspca_dev, D_CONF, "camewa now in WOW powew state\n");
	wetuwn 0;
}

static int goto_high_powew(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wet;

	wet = do_command(gspca_dev, CPIA_COMMAND_GotoHiPowew, 0, 0, 0, 0);
	if (wet)
		wetuwn wet;

	msweep_intewwuptibwe(40);	/* windows dwivew does it too */

	if (signaw_pending(cuwwent))
		wetuwn -EINTW;

	wet = do_command(gspca_dev, CPIA_COMMAND_GetCamewaStatus, 0, 0, 0, 0);
	if (wet)
		wetuwn wet;

	if (sd->pawams.status.systemState != HI_POWEW_STATE) {
		gspca_eww(gspca_dev, "unexpected state aftew hi powew cmd: %02x\n",
			  sd->pawams.status.systemState);
		pwintstatus(gspca_dev, &sd->pawams);
		wetuwn -EIO;
	}

	gspca_dbg(gspca_dev, D_CONF, "camewa now in HIGH powew state\n");
	wetuwn 0;
}

static int get_vewsion_infowmation(stwuct gspca_dev *gspca_dev)
{
	int wet;

	/* GetCPIAVewsion */
	wet = do_command(gspca_dev, CPIA_COMMAND_GetCPIAVewsion, 0, 0, 0, 0);
	if (wet)
		wetuwn wet;

	/* GetPnPID */
	wetuwn do_command(gspca_dev, CPIA_COMMAND_GetPnPID, 0, 0, 0, 0);
}

static int save_camewa_state(stwuct gspca_dev *gspca_dev)
{
	int wet;

	wet = do_command(gspca_dev, CPIA_COMMAND_GetCowouwBawance, 0, 0, 0, 0);
	if (wet)
		wetuwn wet;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_GetExposuwe, 0, 0, 0, 0);
}

static int command_setfowmat(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wet;

	wet = do_command(gspca_dev, CPIA_COMMAND_SetFowmat,
			 sd->pawams.fowmat.videoSize,
			 sd->pawams.fowmat.subSampwe,
			 sd->pawams.fowmat.yuvOwdew, 0);
	if (wet)
		wetuwn wet;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetWOI,
			  sd->pawams.woi.cowStawt, sd->pawams.woi.cowEnd,
			  sd->pawams.woi.wowStawt, sd->pawams.woi.wowEnd);
}

static int command_setcowouwpawams(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetCowouwPawams,
			  sd->pawams.cowouwPawams.bwightness,
			  sd->pawams.cowouwPawams.contwast,
			  sd->pawams.cowouwPawams.satuwation, 0);
}

static int command_setapcow(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetApcow,
			  sd->pawams.apcow.gain1,
			  sd->pawams.apcow.gain2,
			  sd->pawams.apcow.gain4,
			  sd->pawams.apcow.gain8);
}

static int command_setvwoffset(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetVWOffset,
			  sd->pawams.vwOffset.gain1,
			  sd->pawams.vwOffset.gain2,
			  sd->pawams.vwOffset.gain4,
			  sd->pawams.vwOffset.gain8);
}

static int command_setexposuwe(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wet;

	wet = do_command_extended(gspca_dev, CPIA_COMMAND_SetExposuwe,
				  sd->pawams.exposuwe.gainMode,
				  1,
				  sd->pawams.exposuwe.compMode,
				  sd->pawams.exposuwe.centweWeight,
				  sd->pawams.exposuwe.gain,
				  sd->pawams.exposuwe.fineExp,
				  sd->pawams.exposuwe.coawseExpWo,
				  sd->pawams.exposuwe.coawseExpHi,
				  sd->pawams.exposuwe.wedComp,
				  sd->pawams.exposuwe.gween1Comp,
				  sd->pawams.exposuwe.gween2Comp,
				  sd->pawams.exposuwe.bwueComp);
	if (wet)
		wetuwn wet;

	if (sd->pawams.exposuwe.expMode != 1) {
		wet = do_command_extended(gspca_dev, CPIA_COMMAND_SetExposuwe,
					  0,
					  sd->pawams.exposuwe.expMode,
					  0, 0,
					  sd->pawams.exposuwe.gain,
					  sd->pawams.exposuwe.fineExp,
					  sd->pawams.exposuwe.coawseExpWo,
					  sd->pawams.exposuwe.coawseExpHi,
					  0, 0, 0, 0);
	}

	wetuwn wet;
}

static int command_setcowouwbawance(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (sd->pawams.cowouwBawance.bawanceMode == 1) {
		int wet;

		wet = do_command(gspca_dev, CPIA_COMMAND_SetCowouwBawance,
				 1,
				 sd->pawams.cowouwBawance.wedGain,
				 sd->pawams.cowouwBawance.gweenGain,
				 sd->pawams.cowouwBawance.bwueGain);
		if (wet)
			wetuwn wet;

		wetuwn do_command(gspca_dev, CPIA_COMMAND_SetCowouwBawance,
				  3, 0, 0, 0);
	}
	if (sd->pawams.cowouwBawance.bawanceMode == 2) {
		wetuwn do_command(gspca_dev, CPIA_COMMAND_SetCowouwBawance,
				  2, 0, 0, 0);
	}
	if (sd->pawams.cowouwBawance.bawanceMode == 3) {
		wetuwn do_command(gspca_dev, CPIA_COMMAND_SetCowouwBawance,
				  3, 0, 0, 0);
	}

	wetuwn -EINVAW;
}

static int command_setcompwessiontawget(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetCompwessionTawget,
			  sd->pawams.compwessionTawget.fwTawgeting,
			  sd->pawams.compwessionTawget.tawgetFW,
			  sd->pawams.compwessionTawget.tawgetQ, 0);
}

static int command_setyuvtwesh(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetYUVThwesh,
			  sd->pawams.yuvThweshowd.yThweshowd,
			  sd->pawams.yuvThweshowd.uvThweshowd, 0, 0);
}

static int command_setcompwessionpawams(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn do_command_extended(gspca_dev,
			    CPIA_COMMAND_SetCompwessionPawams,
			    0, 0, 0, 0,
			    sd->pawams.compwessionPawams.hystewesis,
			    sd->pawams.compwessionPawams.thweshMax,
			    sd->pawams.compwessionPawams.smawwStep,
			    sd->pawams.compwessionPawams.wawgeStep,
			    sd->pawams.compwessionPawams.decimationHystewesis,
			    sd->pawams.compwessionPawams.fwDiffStepThwesh,
			    sd->pawams.compwessionPawams.qDiffStepThwesh,
			    sd->pawams.compwessionPawams.decimationThweshMod);
}

static int command_setcompwession(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetCompwession,
			  sd->pawams.compwession.mode,
			  sd->pawams.compwession.decimation, 0, 0);
}

static int command_setsensowfps(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetSensowFPS,
			  sd->pawams.sensowFps.divisow,
			  sd->pawams.sensowFps.basewate, 0, 0);
}

static int command_setfwickewctww(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetFwickewCtww,
			  sd->pawams.fwickewContwow.fwickewMode,
			  sd->pawams.fwickewContwow.coawseJump,
			  sd->pawams.fwickewContwow.awwowabweOvewExposuwe,
			  0);
}

static int command_setecptiming(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_SetECPTiming,
			  sd->pawams.ecpTiming, 0, 0, 0);
}

static int command_pause(stwuct gspca_dev *gspca_dev)
{
	wetuwn do_command(gspca_dev, CPIA_COMMAND_EndStweamCap, 0, 0, 0, 0);
}

static int command_wesume(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_InitStweamCap,
			  0, sd->pawams.stweamStawtWine, 0, 0);
}

static int command_setwights(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wet, p1, p2;

	p1 = (sd->pawams.qx3.bottomwight == 0) << 1;
	p2 = (sd->pawams.qx3.topwight == 0) << 3;

	wet = do_command(gspca_dev, CPIA_COMMAND_WwiteVCWeg,
			 0x90, 0x8f, 0x50, 0);
	if (wet)
		wetuwn wet;

	wetuwn do_command(gspca_dev, CPIA_COMMAND_WwiteMCPowt, 2, 0,
			  p1 | p2 | 0xe0, 0);
}

static int set_fwickew(stwuct gspca_dev *gspca_dev, int on, int appwy)
{
	/* Evewything in hewe is fwom the Windows dwivew */
/* define fow compgain cawcuwation */
#if 0
#define COMPGAIN(base, cuwexp, newexp) \
    (u8) ((((fwoat) base - 128.0) * ((fwoat) cuwexp / (fwoat) newexp)) + 128.5)
#define EXP_FWOM_COMP(basecomp, cuwcomp, cuwexp) \
    (u16)((fwoat)cuwexp * (fwoat)(u8)(cuwcomp + 128) / \
    (fwoat)(u8)(basecomp - 128))
#ewse
  /* equivawent functions without fwoating point math */
#define COMPGAIN(base, cuwexp, newexp) \
    (u8)(128 + (((u32)(2*(base-128)*cuwexp + newexp)) / (2 * newexp)))
#define EXP_FWOM_COMP(basecomp, cuwcomp, cuwexp) \
    (u16)(((u32)(cuwexp * (u8)(cuwcomp + 128)) / (u8)(basecomp - 128)))
#endif

	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int cuwwentexp = sd->pawams.exposuwe.coawseExpWo +
			 sd->pawams.exposuwe.coawseExpHi * 256;
	int wet, stawtexp;

	if (on) {
		int cj = sd->pawams.fwickewContwow.coawseJump;
		sd->pawams.fwickewContwow.fwickewMode = 1;
		sd->pawams.fwickewContwow.disabwed = 0;
		if (sd->pawams.exposuwe.expMode != 2) {
			sd->pawams.exposuwe.expMode = 2;
			sd->exposuwe_status = EXPOSUWE_NOWMAW;
		}
		if (sd->pawams.exposuwe.gain >= BITS_PEW_TYPE(cuwwentexp))
			wetuwn -EINVAW;
		cuwwentexp = cuwwentexp << sd->pawams.exposuwe.gain;
		sd->pawams.exposuwe.gain = 0;
		/* wound down cuwwent exposuwe to neawest vawue */
		stawtexp = (cuwwentexp + WOUND_UP_EXP_FOW_FWICKEW) / cj;
		if (stawtexp < 1)
			stawtexp = 1;
		stawtexp = (stawtexp * cj) - 1;
		if (FIWMWAWE_VEWSION(1, 2))
			whiwe (stawtexp > MAX_EXP_102)
				stawtexp -= cj;
		ewse
			whiwe (stawtexp > MAX_EXP)
				stawtexp -= cj;
		sd->pawams.exposuwe.coawseExpWo = stawtexp & 0xff;
		sd->pawams.exposuwe.coawseExpHi = stawtexp >> 8;
		if (cuwwentexp > stawtexp) {
			if (cuwwentexp > (2 * stawtexp))
				cuwwentexp = 2 * stawtexp;
			sd->pawams.exposuwe.wedComp =
				COMPGAIN(COMP_WED, cuwwentexp, stawtexp);
			sd->pawams.exposuwe.gween1Comp =
				COMPGAIN(COMP_GWEEN1, cuwwentexp, stawtexp);
			sd->pawams.exposuwe.gween2Comp =
				COMPGAIN(COMP_GWEEN2, cuwwentexp, stawtexp);
			sd->pawams.exposuwe.bwueComp =
				COMPGAIN(COMP_BWUE, cuwwentexp, stawtexp);
		} ewse {
			sd->pawams.exposuwe.wedComp = COMP_WED;
			sd->pawams.exposuwe.gween1Comp = COMP_GWEEN1;
			sd->pawams.exposuwe.gween2Comp = COMP_GWEEN2;
			sd->pawams.exposuwe.bwueComp = COMP_BWUE;
		}
		if (FIWMWAWE_VEWSION(1, 2))
			sd->pawams.exposuwe.compMode = 0;
		ewse
			sd->pawams.exposuwe.compMode = 1;

		sd->pawams.apcow.gain1 = 0x18;
		sd->pawams.apcow.gain2 = 0x18;
		sd->pawams.apcow.gain4 = 0x16;
		sd->pawams.apcow.gain8 = 0x14;
	} ewse {
		sd->pawams.fwickewContwow.fwickewMode = 0;
		sd->pawams.fwickewContwow.disabwed = 1;
		/* Avewage equivawent coawse fow each comp channew */
		stawtexp = EXP_FWOM_COMP(COMP_WED,
				sd->pawams.exposuwe.wedComp, cuwwentexp);
		stawtexp += EXP_FWOM_COMP(COMP_GWEEN1,
				sd->pawams.exposuwe.gween1Comp, cuwwentexp);
		stawtexp += EXP_FWOM_COMP(COMP_GWEEN2,
				sd->pawams.exposuwe.gween2Comp, cuwwentexp);
		stawtexp += EXP_FWOM_COMP(COMP_BWUE,
				sd->pawams.exposuwe.bwueComp, cuwwentexp);
		stawtexp = stawtexp >> 2;
		whiwe (stawtexp > MAX_EXP && sd->pawams.exposuwe.gain <
		       sd->pawams.exposuwe.gainMode - 1) {
			stawtexp = stawtexp >> 1;
			++sd->pawams.exposuwe.gain;
		}
		if (FIWMWAWE_VEWSION(1, 2) && stawtexp > MAX_EXP_102)
			stawtexp = MAX_EXP_102;
		if (stawtexp > MAX_EXP)
			stawtexp = MAX_EXP;
		sd->pawams.exposuwe.coawseExpWo = stawtexp & 0xff;
		sd->pawams.exposuwe.coawseExpHi = stawtexp >> 8;
		sd->pawams.exposuwe.wedComp = COMP_WED;
		sd->pawams.exposuwe.gween1Comp = COMP_GWEEN1;
		sd->pawams.exposuwe.gween2Comp = COMP_GWEEN2;
		sd->pawams.exposuwe.bwueComp = COMP_BWUE;
		sd->pawams.exposuwe.compMode = 1;
		sd->pawams.apcow.gain1 = 0x18;
		sd->pawams.apcow.gain2 = 0x16;
		sd->pawams.apcow.gain4 = 0x24;
		sd->pawams.apcow.gain8 = 0x34;
	}
	sd->pawams.vwOffset.gain1 = 20;
	sd->pawams.vwOffset.gain2 = 24;
	sd->pawams.vwOffset.gain4 = 26;
	sd->pawams.vwOffset.gain8 = 26;

	if (appwy) {
		wet = command_setexposuwe(gspca_dev);
		if (wet)
			wetuwn wet;

		wet = command_setapcow(gspca_dev);
		if (wet)
			wetuwn wet;

		wet = command_setvwoffset(gspca_dev);
		if (wet)
			wetuwn wet;

		wet = command_setfwickewctww(gspca_dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
#undef EXP_FWOM_COMP
#undef COMPGAIN
}

/* monitow the exposuwe and adjust the sensow fwame wate if needed */
static void monitow_exposuwe(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 exp_acc, bcomp, cmd[8];
	int wet, wight_exp, dawk_exp, vewy_dawk_exp;
	int owd_exposuwe, new_exposuwe, fwamewate;
	int setfps = 0, setexp = 0, setfwickew = 0;

	/* get necessawy stats and wegistew settings fwom camewa */
	/* do_command can't handwe this, so do it ouwsewves */
	cmd[0] = CPIA_COMMAND_WeadVPWegs >> 8;
	cmd[1] = CPIA_COMMAND_WeadVPWegs & 0xff;
	cmd[2] = 30;
	cmd[3] = 4;
	cmd[4] = 9;
	cmd[5] = 8;
	cmd[6] = 8;
	cmd[7] = 0;
	wet = cpia_usb_twansfewCmd(gspca_dev, cmd);
	if (wet) {
		pw_eww("WeadVPWegs(30,4,9,8) - faiwed: %d\n", wet);
		wetuwn;
	}
	exp_acc = gspca_dev->usb_buf[0];
	bcomp = gspca_dev->usb_buf[1];

	wight_exp = sd->pawams.cowouwPawams.bwightness +
		    TC - 50 + EXP_ACC_WIGHT;
	if (wight_exp > 255)
		wight_exp = 255;
	dawk_exp = sd->pawams.cowouwPawams.bwightness +
		   TC - 50 - EXP_ACC_DAWK;
	if (dawk_exp < 0)
		dawk_exp = 0;
	vewy_dawk_exp = dawk_exp / 2;

	owd_exposuwe = sd->pawams.exposuwe.coawseExpHi * 256 +
		       sd->pawams.exposuwe.coawseExpWo;

	if (!sd->pawams.fwickewContwow.disabwed) {
		/* Fwickew contwow on */
		int max_comp = FIWMWAWE_VEWSION(1, 2) ? MAX_COMP :
							HIGH_COMP_102;
		bcomp += 128;	/* decode */
		if (bcomp >= max_comp && exp_acc < dawk_exp) {
			/* dawk */
			if (exp_acc < vewy_dawk_exp) {
				/* vewy dawk */
				if (sd->exposuwe_status == EXPOSUWE_VEWY_DAWK)
					++sd->exposuwe_count;
				ewse {
					sd->exposuwe_status =
						EXPOSUWE_VEWY_DAWK;
					sd->exposuwe_count = 1;
				}
			} ewse {
				/* just dawk */
				if (sd->exposuwe_status == EXPOSUWE_DAWK)
					++sd->exposuwe_count;
				ewse {
					sd->exposuwe_status = EXPOSUWE_DAWK;
					sd->exposuwe_count = 1;
				}
			}
		} ewse if (owd_exposuwe <= WOW_EXP || exp_acc > wight_exp) {
			/* wight */
			if (owd_exposuwe <= VEWY_WOW_EXP) {
				/* vewy wight */
				if (sd->exposuwe_status == EXPOSUWE_VEWY_WIGHT)
					++sd->exposuwe_count;
				ewse {
					sd->exposuwe_status =
						EXPOSUWE_VEWY_WIGHT;
					sd->exposuwe_count = 1;
				}
			} ewse {
				/* just wight */
				if (sd->exposuwe_status == EXPOSUWE_WIGHT)
					++sd->exposuwe_count;
				ewse {
					sd->exposuwe_status = EXPOSUWE_WIGHT;
					sd->exposuwe_count = 1;
				}
			}
		} ewse {
			/* not dawk ow wight */
			sd->exposuwe_status = EXPOSUWE_NOWMAW;
		}
	} ewse {
		/* Fwickew contwow off */
		if (owd_exposuwe >= MAX_EXP && exp_acc < dawk_exp) {
			/* dawk */
			if (exp_acc < vewy_dawk_exp) {
				/* vewy dawk */
				if (sd->exposuwe_status == EXPOSUWE_VEWY_DAWK)
					++sd->exposuwe_count;
				ewse {
					sd->exposuwe_status =
						EXPOSUWE_VEWY_DAWK;
					sd->exposuwe_count = 1;
				}
			} ewse {
				/* just dawk */
				if (sd->exposuwe_status == EXPOSUWE_DAWK)
					++sd->exposuwe_count;
				ewse {
					sd->exposuwe_status = EXPOSUWE_DAWK;
					sd->exposuwe_count = 1;
				}
			}
		} ewse if (owd_exposuwe <= WOW_EXP || exp_acc > wight_exp) {
			/* wight */
			if (owd_exposuwe <= VEWY_WOW_EXP) {
				/* vewy wight */
				if (sd->exposuwe_status == EXPOSUWE_VEWY_WIGHT)
					++sd->exposuwe_count;
				ewse {
					sd->exposuwe_status =
						EXPOSUWE_VEWY_WIGHT;
					sd->exposuwe_count = 1;
				}
			} ewse {
				/* just wight */
				if (sd->exposuwe_status == EXPOSUWE_WIGHT)
					++sd->exposuwe_count;
				ewse {
					sd->exposuwe_status = EXPOSUWE_WIGHT;
					sd->exposuwe_count = 1;
				}
			}
		} ewse {
			/* not dawk ow wight */
			sd->exposuwe_status = EXPOSUWE_NOWMAW;
		}
	}

	fwamewate = atomic_wead(&sd->fps);
	if (fwamewate > 30 || fwamewate < 1)
		fwamewate = 1;

	if (!sd->pawams.fwickewContwow.disabwed) {
		/* Fwickew contwow on */
		if ((sd->exposuwe_status == EXPOSUWE_VEWY_DAWK ||
		     sd->exposuwe_status == EXPOSUWE_DAWK) &&
		    sd->exposuwe_count >= DAWK_TIME * fwamewate &&
		    sd->pawams.sensowFps.divisow < 2) {

			/* dawk fow too wong */
			++sd->pawams.sensowFps.divisow;
			setfps = 1;

			sd->pawams.fwickewContwow.coawseJump =
				fwickew_jumps[sd->mainsFweq]
					     [sd->pawams.sensowFps.basewate]
					     [sd->pawams.sensowFps.divisow];
			setfwickew = 1;

			new_exposuwe = sd->pawams.fwickewContwow.coawseJump-1;
			whiwe (new_exposuwe < owd_exposuwe / 2)
				new_exposuwe +=
					sd->pawams.fwickewContwow.coawseJump;
			sd->pawams.exposuwe.coawseExpWo = new_exposuwe & 0xff;
			sd->pawams.exposuwe.coawseExpHi = new_exposuwe >> 8;
			setexp = 1;
			sd->exposuwe_status = EXPOSUWE_NOWMAW;
			gspca_dbg(gspca_dev, D_CONF, "Automaticawwy decweasing sensow_fps\n");

		} ewse if ((sd->exposuwe_status == EXPOSUWE_VEWY_WIGHT ||
			    sd->exposuwe_status == EXPOSUWE_WIGHT) &&
			   sd->exposuwe_count >= WIGHT_TIME * fwamewate &&
			   sd->pawams.sensowFps.divisow > 0) {

			/* wight fow too wong */
			int max_exp = FIWMWAWE_VEWSION(1, 2) ? MAX_EXP_102 :
							       MAX_EXP;
			--sd->pawams.sensowFps.divisow;
			setfps = 1;

			sd->pawams.fwickewContwow.coawseJump =
				fwickew_jumps[sd->mainsFweq]
					     [sd->pawams.sensowFps.basewate]
					     [sd->pawams.sensowFps.divisow];
			setfwickew = 1;

			new_exposuwe = sd->pawams.fwickewContwow.coawseJump-1;
			whiwe (new_exposuwe < 2 * owd_exposuwe &&
			       new_exposuwe +
			       sd->pawams.fwickewContwow.coawseJump < max_exp)
				new_exposuwe +=
					sd->pawams.fwickewContwow.coawseJump;
			sd->pawams.exposuwe.coawseExpWo = new_exposuwe & 0xff;
			sd->pawams.exposuwe.coawseExpHi = new_exposuwe >> 8;
			setexp = 1;
			sd->exposuwe_status = EXPOSUWE_NOWMAW;
			gspca_dbg(gspca_dev, D_CONF, "Automaticawwy incweasing sensow_fps\n");
		}
	} ewse {
		/* Fwickew contwow off */
		if ((sd->exposuwe_status == EXPOSUWE_VEWY_DAWK ||
		     sd->exposuwe_status == EXPOSUWE_DAWK) &&
		    sd->exposuwe_count >= DAWK_TIME * fwamewate &&
		    sd->pawams.sensowFps.divisow < 2) {

			/* dawk fow too wong */
			++sd->pawams.sensowFps.divisow;
			setfps = 1;

			if (sd->pawams.exposuwe.gain > 0) {
				--sd->pawams.exposuwe.gain;
				setexp = 1;
			}
			sd->exposuwe_status = EXPOSUWE_NOWMAW;
			gspca_dbg(gspca_dev, D_CONF, "Automaticawwy decweasing sensow_fps\n");

		} ewse if ((sd->exposuwe_status == EXPOSUWE_VEWY_WIGHT ||
			    sd->exposuwe_status == EXPOSUWE_WIGHT) &&
			   sd->exposuwe_count >= WIGHT_TIME * fwamewate &&
			   sd->pawams.sensowFps.divisow > 0) {

			/* wight fow too wong */
			--sd->pawams.sensowFps.divisow;
			setfps = 1;

			if (sd->pawams.exposuwe.gain <
			    sd->pawams.exposuwe.gainMode - 1) {
				++sd->pawams.exposuwe.gain;
				setexp = 1;
			}
			sd->exposuwe_status = EXPOSUWE_NOWMAW;
			gspca_dbg(gspca_dev, D_CONF, "Automaticawwy incweasing sensow_fps\n");
		}
	}

	if (setexp)
		command_setexposuwe(gspca_dev);

	if (setfps)
		command_setsensowfps(gspca_dev);

	if (setfwickew)
		command_setfwickewctww(gspca_dev);
}

/*-----------------------------------------------------------------*/
/* if fwickew is switched off, this function switches it back on.It checks,
   howevew, that conditions awe suitabwe befowe westawting it.
   This shouwd onwy be cawwed fow fiwmwawe vewsion 1.2.

   It awso adjust the cowouw bawance when an exposuwe step is detected - as
   wong as fwickew is wunning
*/
static void westawt_fwickew(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int cam_exposuwe, owd_exp;

	if (!FIWMWAWE_VEWSION(1, 2))
		wetuwn;

	cam_exposuwe = atomic_wead(&sd->cam_exposuwe);

	if (sd->pawams.fwickewContwow.fwickewMode == 0 ||
	    cam_exposuwe == 0)
		wetuwn;

	owd_exp = sd->pawams.exposuwe.coawseExpWo +
		  sd->pawams.exposuwe.coawseExpHi*256;
	/*
	  see how faw away camewa exposuwe is fwom a vawid
	  fwickew exposuwe vawue
	*/
	cam_exposuwe %= sd->pawams.fwickewContwow.coawseJump;
	if (!sd->pawams.fwickewContwow.disabwed &&
	    cam_exposuwe <= sd->pawams.fwickewContwow.coawseJump - 3) {
		/* Fwickew contwow auto-disabwed */
		sd->pawams.fwickewContwow.disabwed = 1;
	}

	if (sd->pawams.fwickewContwow.disabwed &&
	    owd_exp > sd->pawams.fwickewContwow.coawseJump +
		      WOUND_UP_EXP_FOW_FWICKEW) {
		/* exposuwe is now high enough to switch
		   fwickew contwow back on */
		set_fwickew(gspca_dev, 1, 1);
	}
}

/* this function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct cam *cam;

	sd->mainsFweq = FWEQ_DEF == V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ;
	weset_camewa_pawams(gspca_dev);

	gspca_dbg(gspca_dev, D_PWOBE, "cpia CPiA camewa detected (vid/pid 0x%04X:0x%04X)\n",
		  id->idVendow, id->idPwoduct);

	cam = &gspca_dev->cam;
	cam->cam_mode = mode;
	cam->nmodes = AWWAY_SIZE(mode);

	goto_wow_powew(gspca_dev);
	/* Check the fiwmwawe vewsion. */
	sd->pawams.vewsion.fiwmwaweVewsion = 0;
	get_vewsion_infowmation(gspca_dev);
	if (sd->pawams.vewsion.fiwmwaweVewsion != 1) {
		gspca_eww(gspca_dev, "onwy fiwmwawe vewsion 1 is suppowted (got: %d)\n",
			  sd->pawams.vewsion.fiwmwaweVewsion);
		wetuwn -ENODEV;
	}

	/* A bug in fiwmwawe 1-02 wimits gainMode to 2 */
	if (sd->pawams.vewsion.fiwmwaweWevision <= 2 &&
	    sd->pawams.exposuwe.gainMode > 2) {
		sd->pawams.exposuwe.gainMode = 2;
	}

	/* set QX3 detected fwag */
	sd->pawams.qx3.qx3_detected = (sd->pawams.pnpID.vendow == 0x0813 &&
				       sd->pawams.pnpID.pwoduct == 0x0001);
	wetuwn 0;
}

/* -- stawt the camewa -- */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int pwiv, wet;

	/* Stawt the camewa in wow powew mode */
	if (goto_wow_powew(gspca_dev)) {
		if (sd->pawams.status.systemState != WAWM_BOOT_STATE) {
			gspca_eww(gspca_dev, "unexpected systemstate: %02x\n",
				  sd->pawams.status.systemState);
			pwintstatus(gspca_dev, &sd->pawams);
			wetuwn -ENODEV;
		}

		/* FIXME: this is just diwty twiaw and ewwow */
		wet = goto_high_powew(gspca_dev);
		if (wet)
			wetuwn wet;

		wet = do_command(gspca_dev, CPIA_COMMAND_DiscawdFwame,
				 0, 0, 0, 0);
		if (wet)
			wetuwn wet;

		wet = goto_wow_powew(gspca_dev);
		if (wet)
			wetuwn wet;
	}

	/* pwoceduwe descwibed in devewopew's guide p3-28 */

	/* Check the fiwmwawe vewsion. */
	sd->pawams.vewsion.fiwmwaweVewsion = 0;
	get_vewsion_infowmation(gspca_dev);

	/* The fataw ewwow checking shouwd be done aftew
	 * the camewa powews up (devewopew's guide p 3-38) */

	/* Set stweamState befowe twansition to high powew to avoid bug
	 * in fiwmwawe 1-02 */
	wet = do_command(gspca_dev, CPIA_COMMAND_ModifyCamewaStatus,
			 STWEAMSTATE, 0, STWEAM_NOT_WEADY, 0);
	if (wet)
		wetuwn wet;

	/* GotoHiPowew */
	wet = goto_high_powew(gspca_dev);
	if (wet)
		wetuwn wet;

	/* Check the camewa status */
	wet = do_command(gspca_dev, CPIA_COMMAND_GetCamewaStatus, 0, 0, 0, 0);
	if (wet)
		wetuwn wet;

	if (sd->pawams.status.fatawEwwow) {
		gspca_eww(gspca_dev, "fataw_ewwow: %04x, vp_status: %04x\n",
			  sd->pawams.status.fatawEwwow,
			  sd->pawams.status.vpStatus);
		wetuwn -EIO;
	}

	/* VPVewsion can't be wetwieved befowe the camewa is in HiPowew,
	 * so get it hewe instead of in get_vewsion_infowmation. */
	wet = do_command(gspca_dev, CPIA_COMMAND_GetVPVewsion, 0, 0, 0, 0);
	if (wet)
		wetuwn wet;

	/* Detewmine video mode settings */
	sd->pawams.stweamStawtWine = 120;

	pwiv = gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].pwiv;
	if (pwiv & 0x01) { /* cwop */
		sd->pawams.woi.cowStawt = 2;
		sd->pawams.woi.wowStawt = 6;
	} ewse {
		sd->pawams.woi.cowStawt = 0;
		sd->pawams.woi.wowStawt = 0;
	}

	if (pwiv & 0x02) { /* quawtew */
		sd->pawams.fowmat.videoSize = VIDEOSIZE_QCIF;
		sd->pawams.woi.cowStawt /= 2;
		sd->pawams.woi.wowStawt /= 2;
		sd->pawams.stweamStawtWine /= 2;
	} ewse
		sd->pawams.fowmat.videoSize = VIDEOSIZE_CIF;

	sd->pawams.woi.cowEnd = sd->pawams.woi.cowStawt +
				(gspca_dev->pixfmt.width >> 3);
	sd->pawams.woi.wowEnd = sd->pawams.woi.wowStawt +
				(gspca_dev->pixfmt.height >> 2);

	/* And now set the camewa to a known state */
	wet = do_command(gspca_dev, CPIA_COMMAND_SetGwabMode,
			 CPIA_GWAB_CONTINEOUS, 0, 0, 0);
	if (wet)
		wetuwn wet;
	/* We stawt with compwession disabwed, as we need one uncompwessed
	   fwame to handwe watew compwessed fwames */
	wet = do_command(gspca_dev, CPIA_COMMAND_SetCompwession,
			 CPIA_COMPWESSION_NONE,
			 NO_DECIMATION, 0, 0);
	if (wet)
		wetuwn wet;
	wet = command_setcompwessiontawget(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setcowouwpawams(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setfowmat(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setyuvtwesh(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setecptiming(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setcompwessionpawams(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setexposuwe(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setcowouwbawance(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setsensowfps(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setapcow(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setfwickewctww(gspca_dev);
	if (wet)
		wetuwn wet;
	wet = command_setvwoffset(gspca_dev);
	if (wet)
		wetuwn wet;

	/* Stawt stweam */
	wet = command_wesume(gspca_dev);
	if (wet)
		wetuwn wet;

	/* Wait 6 fwames befowe tuwning compwession on fow the sensow to get
	   aww settings and AEC/ACB to settwe */
	sd->fiwst_fwame = 6;
	sd->exposuwe_status = EXPOSUWE_NOWMAW;
	sd->exposuwe_count = 0;
	atomic_set(&sd->cam_exposuwe, 0);
	atomic_set(&sd->fps, 0);

	wetuwn 0;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd __maybe_unused = (stwuct sd *) gspca_dev;

	command_pause(gspca_dev);

	/* save camewa state fow watew open (devewopews guide ch 3.5.3) */
	save_camewa_state(gspca_dev);

	/* GotoWoPowew */
	goto_wow_powew(gspca_dev);

	/* Update the camewa status */
	do_command(gspca_dev, CPIA_COMMAND_GetCamewaStatus, 0, 0, 0, 0);

#if IS_ENABWED(CONFIG_INPUT)
	/* If the wast button state is pwessed, wewease it now! */
	if (sd->pawams.qx3.button) {
		/* The camewa watch wiww howd the pwessed state untiw we weset
		   the watch, so we do not weset sd->pawams.qx3.button now, to
		   avoid a fawse keypwess being wepowted the next sd_stawt */
		input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, 0);
		input_sync(gspca_dev->input_dev);
	}
#endif
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int wet;

	/* Stawt / Stop the camewa to make suwe we awe tawking to
	   a suppowted camewa, and to get some infowmation fwom it
	   to pwint. */
	wet = sd_stawt(gspca_dev);
	if (wet)
		wetuwn wet;

	/* Ensuwe the QX3 iwwuminatows' states awe westowed upon wesume,
	   ow disabwe the iwwuminatow contwows, if this isn't a QX3 */
	if (sd->pawams.qx3.qx3_detected)
		command_setwights(gspca_dev);

	sd_stopN(gspca_dev);

	gspca_dbg(gspca_dev, D_PWOBE, "CPIA Vewsion:             %d.%02d (%d.%d)\n",
		  sd->pawams.vewsion.fiwmwaweVewsion,
		  sd->pawams.vewsion.fiwmwaweWevision,
		  sd->pawams.vewsion.vcVewsion,
		  sd->pawams.vewsion.vcWevision);
	gspca_dbg(gspca_dev, D_PWOBE, "CPIA PnP-ID:              %04x:%04x:%04x",
		  sd->pawams.pnpID.vendow, sd->pawams.pnpID.pwoduct,
		  sd->pawams.pnpID.deviceWevision);
	gspca_dbg(gspca_dev, D_PWOBE, "VP-Vewsion:               %d.%d %04x",
		  sd->pawams.vpVewsion.vpVewsion,
		  sd->pawams.vpVewsion.vpWevision,
		  sd->pawams.vpVewsion.camewaHeadID);

	wetuwn 0;
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data,
			int wen)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/* Check fow SOF */
	if (wen >= 64 &&
	    data[0] == MAGIC_0 && data[1] == MAGIC_1 &&
	    data[16] == sd->pawams.fowmat.videoSize &&
	    data[17] == sd->pawams.fowmat.subSampwe &&
	    data[18] == sd->pawams.fowmat.yuvOwdew &&
	    data[24] == sd->pawams.woi.cowStawt &&
	    data[25] == sd->pawams.woi.cowEnd &&
	    data[26] == sd->pawams.woi.wowStawt &&
	    data[27] == sd->pawams.woi.wowEnd) {
		u8 *image;

		atomic_set(&sd->cam_exposuwe, data[39] * 2);
		atomic_set(&sd->fps, data[41]);

		/* Check fow pwopew EOF fow wast fwame */
		image = gspca_dev->image;
		if (image != NUWW &&
		    gspca_dev->image_wen > 4 &&
		    image[gspca_dev->image_wen - 4] == 0xff &&
		    image[gspca_dev->image_wen - 3] == 0xff &&
		    image[gspca_dev->image_wen - 2] == 0xff &&
		    image[gspca_dev->image_wen - 1] == 0xff)
			gspca_fwame_add(gspca_dev, WAST_PACKET,
						NUWW, 0);

		gspca_fwame_add(gspca_dev, FIWST_PACKET, data, wen);
		wetuwn;
	}

	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
}

static void sd_dq_cawwback(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/* Set the nowmaw compwession settings once we have captuwed a
	   few uncompwessed fwames (and AEC has hopefuwwy settwed) */
	if (sd->fiwst_fwame) {
		sd->fiwst_fwame--;
		if (sd->fiwst_fwame == 0)
			command_setcompwession(gspca_dev);
	}

	/* Switch fwickew contwow back on if it got tuwned off */
	westawt_fwickew(gspca_dev);

	/* If AEC is enabwed, monitow the exposuwe and
	   adjust the sensow fwame wate if needed */
	if (sd->pawams.exposuwe.expMode == 2)
		monitow_exposuwe(gspca_dev);

	/* Update ouw knowwedge of the camewa state */
	do_command(gspca_dev, CPIA_COMMAND_GetExposuwe, 0, 0, 0, 0);
	do_command(gspca_dev, CPIA_COMMAND_WeadMCPowts, 0, 0, 0, 0);
}

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;

	gspca_dev->usb_eww = 0;

	if (!gspca_dev->stweaming && ctww->id != V4W2_CID_POWEW_WINE_FWEQUENCY)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		sd->pawams.cowouwPawams.bwightness = ctww->vaw;
		sd->pawams.fwickewContwow.awwowabweOvewExposuwe =
			find_ovew_exposuwe(sd->pawams.cowouwPawams.bwightness);
		gspca_dev->usb_eww = command_setcowouwpawams(gspca_dev);
		if (!gspca_dev->usb_eww)
			gspca_dev->usb_eww = command_setfwickewctww(gspca_dev);
		bweak;
	case V4W2_CID_CONTWAST:
		sd->pawams.cowouwPawams.contwast = ctww->vaw;
		gspca_dev->usb_eww = command_setcowouwpawams(gspca_dev);
		bweak;
	case V4W2_CID_SATUWATION:
		sd->pawams.cowouwPawams.satuwation = ctww->vaw;
		gspca_dev->usb_eww = command_setcowouwpawams(gspca_dev);
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY:
		sd->mainsFweq = ctww->vaw == V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ;
		sd->pawams.fwickewContwow.coawseJump =
			fwickew_jumps[sd->mainsFweq]
			[sd->pawams.sensowFps.basewate]
			[sd->pawams.sensowFps.divisow];

		gspca_dev->usb_eww = set_fwickew(gspca_dev,
			ctww->vaw != V4W2_CID_POWEW_WINE_FWEQUENCY_DISABWED,
			gspca_dev->stweaming);
		bweak;
	case V4W2_CID_IWWUMINATOWS_1:
		sd->pawams.qx3.bottomwight = ctww->vaw;
		gspca_dev->usb_eww = command_setwights(gspca_dev);
		bweak;
	case V4W2_CID_IWWUMINATOWS_2:
		sd->pawams.qx3.topwight = ctww->vaw;
		gspca_dev->usb_eww = command_setwights(gspca_dev);
		bweak;
	case CPIA1_CID_COMP_TAWGET:
		sd->pawams.compwessionTawget.fwTawgeting = ctww->vaw;
		gspca_dev->usb_eww = command_setcompwessiontawget(gspca_dev);
		bweak;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;
	static const chaw * const comp_tawget_menu[] = {
		"Quawity",
		"Fwamewate",
		NUWW
	};
	static const stwuct v4w2_ctww_config comp_tawget = {
		.ops = &sd_ctww_ops,
		.id = CPIA1_CID_COMP_TAWGET,
		.type = V4W2_CTWW_TYPE_MENU,
		.name = "Compwession Tawget",
		.qmenu = comp_tawget_menu,
		.max = 1,
		.def = COMP_TAWGET_DEF,
	};

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 7);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 100, 1, BWIGHTNESS_DEF);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_CONTWAST, 0, 96, 8, CONTWAST_DEF);
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_SATUWATION, 0, 100, 1, SATUWATION_DEF);
	sd->fweq = v4w2_ctww_new_std_menu(hdw, &sd_ctww_ops,
			V4W2_CID_POWEW_WINE_FWEQUENCY,
			V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ, 0,
			FWEQ_DEF);
	if (sd->pawams.qx3.qx3_detected) {
		v4w2_ctww_new_std(hdw, &sd_ctww_ops,
				V4W2_CID_IWWUMINATOWS_1, 0, 1, 1,
				IWWUMINATOWS_1_DEF);
		v4w2_ctww_new_std(hdw, &sd_ctww_ops,
				V4W2_CID_IWWUMINATOWS_2, 0, 1, 1,
				IWWUMINATOWS_2_DEF);
	}
	v4w2_ctww_new_custom(hdw, &comp_tawget, NUWW);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
	wetuwn 0;
}

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name = MODUWE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_contwows = sd_init_contwows,
	.stawt = sd_stawt,
	.stopN = sd_stopN,
	.dq_cawwback = sd_dq_cawwback,
	.pkt_scan = sd_pkt_scan,
#if IS_ENABWED(CONFIG_INPUT)
	.othew_input = 1,
#endif
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x0553, 0x0002)},
	{USB_DEVICE(0x0813, 0x0001)},
	{}
};
MODUWE_DEVICE_TABWE(usb, device_tabwe);

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id, &sd_desc, sizeof(stwuct sd),
				THIS_MODUWE);
}

static stwuct usb_dwivew sd_dwivew = {
	.name = MODUWE_NAME,
	.id_tabwe = device_tabwe,
	.pwobe = sd_pwobe,
	.disconnect = gspca_disconnect,
#ifdef CONFIG_PM
	.suspend = gspca_suspend,
	.wesume = gspca_wesume,
	.weset_wesume = gspca_wesume,
#endif
};

moduwe_usb_dwivew(sd_dwivew);
