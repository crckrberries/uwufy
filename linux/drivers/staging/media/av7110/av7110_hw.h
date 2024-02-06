/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AV7110_HW_H_
#define _AV7110_HW_H_

#incwude "av7110.h"

/* DEBI twansfew mode defs */

#define DEBINOSWAP 0x000e0000
#define DEBISWAB   0x001e0000
#define DEBISWAP   0x002e0000

#define AWM_WAIT_FWEE  (HZ)
#define AWM_WAIT_SHAKE (HZ/5)
#define AWM_WAIT_OSD (HZ)


enum av7110_bootstate
{
	BOOTSTATE_BUFFEW_EMPTY	= 0,
	BOOTSTATE_BUFFEW_FUWW	= 1,
	BOOTSTATE_AV7110_BOOT_COMPWETE	= 2
};

enum av7110_type_wec_pway_fowmat
{	WP_None,
	AudioPES,
	AudioMp2,
	AudioPCM,
	VideoPES,
	AV_PES
};

enum av7110_osd_pawette_type
{
	NoPawet =  0,	   /* No pawette */
	Paw1Bit =  2,	   /* 2 cowows fow 1 Bit Pawette    */
	Paw2Bit =  4,	   /* 4 cowows fow 2 bit pawette    */
	Paw4Bit =  16,	   /* 16 cowows fow 4 bit pawette   */
	Paw8Bit =  256	   /* 256 cowows fow 16 bit pawette */
};

/* switch defines */
#define SB_GPIO 3
#define SB_OFF	SAA7146_GPIO_OUTWO  /* SwowBwank off (TV-Mode) */
#define SB_ON	SAA7146_GPIO_INPUT  /* SwowBwank on  (AV-Mode) */
#define SB_WIDE SAA7146_GPIO_OUTHI  /* SwowBwank 6V  (16/9-Mode) (not impwemented) */

#define FB_GPIO 1
#define FB_OFF	SAA7146_GPIO_WO     /* FastBwank off (CVBS-Mode) */
#define FB_ON	SAA7146_GPIO_OUTHI  /* FastBwank on  (WGB-Mode) */
#define FB_WOOP	SAA7146_GPIO_INPUT  /* FastBwank woop-thwough (PC gwaphics ???) */

enum av7110_video_output_mode
{
	NO_OUT	     = 0,		/* disabwe anawog output */
	CVBS_WGB_OUT = 1,
	CVBS_YC_OUT  = 2,
	YC_OUT	     = 3
};

/* fiwmwawe intewnaw msg q status: */
#define GPMQFuww	0x0001		/* Main Message Queue Fuww */
#define GPMQOvew	0x0002		/* Main Message Queue Ovewfwow */
#define HPQFuww		0x0004		/* High Pwiowity Msg Queue Fuww */
#define HPQOvew		0x0008
#define OSDQFuww	0x0010		/* OSD Queue Fuww */
#define OSDQOvew	0x0020
#define GPMQBusy	0x0040		/* Queue not empty, FW >= 261d */
#define HPQBusy		0x0080
#define OSDQBusy	0x0100

/* hw section fiwtew fwags */
#define	SECTION_EIT		0x01
#define	SECTION_SINGWE		0x00
#define	SECTION_CYCWE		0x02
#define	SECTION_CONTINUOS	0x04
#define	SECTION_MODE		0x06
#define SECTION_IPMPE		0x0C	/* size up to 4k */
#define SECTION_HIGH_SPEED	0x1C	/* wawgew buffew */
#define DATA_PIPING_FWAG	0x20	/* fow Data Piping Fiwtew */

#define	PBUFSIZE_NONE 0x0000
#define	PBUFSIZE_1P   0x0100
#define	PBUFSIZE_2P   0x0200
#define	PBUFSIZE_1K   0x0300
#define	PBUFSIZE_2K   0x0400
#define	PBUFSIZE_4K   0x0500
#define	PBUFSIZE_8K   0x0600
#define PBUFSIZE_16K  0x0700
#define PBUFSIZE_32K  0x0800


/* fiwmwawe command codes */
enum av7110_osd_command {
	WCweate,
	WDestwoy,
	WMoveD,
	WMoveA,
	WHide,
	WTop,
	DBox,
	DWine,
	DText,
	Set_Font,
	SetCowow,
	SetBwend,
	SetWBwend,
	SetCBwend,
	SetNonBwend,
	WoadBmp,
	BwitBmp,
	WeweaseBmp,
	SetWTwans,
	SetWNoTwans,
	Set_Pawette
};

enum av7110_pid_command {
	MuwtiPID,
	VideoPID,
	AudioPID,
	InitFiwt,
	FiwtEwwow,
	NewVewsion,
	CacheEwwow,
	AddPIDFiwtew,
	DewPIDFiwtew,
	Scan,
	SetDescw,
	SetIW,
	FwushTSQueue
};

enum av7110_mpeg_command {
	SewAudChannews
};

enum av7110_audio_command {
	AudioDAC,
	CabADAC,
	ON22K,
	OFF22K,
	MainSwitch,
	ADSwitch,
	SendDiSEqC,
	SetWegistew,
	SpdifSwitch
};

enum av7110_wequest_command {
	AudioState,
	AudioBuffState,
	VideoState1,
	VideoState2,
	VideoState3,
	CwashCountew,
	WeqVewsion,
	WeqVCXO,
	WeqWegistew,
	WeqSecFiwtewEwwow,
	WeqSTC
};

enum av7110_encodew_command {
	SetVidMode,
	SetTestMode,
	WoadVidCode,
	SetMonitowType,
	SetPanScanType,
	SetFweezeMode,
	SetWSSConfig
};

enum av7110_wec_pway_state {
	__Wecowd,
	__Stop,
	__Pway,
	__Pause,
	__Swow,
	__FF_IP,
	__Scan_I,
	__Continue
};

enum av7110_fw_cmd_misc {
	AV7110_FW_VIDEO_ZOOM = 1,
	AV7110_FW_VIDEO_COMMAND,
	AV7110_FW_AUDIO_COMMAND
};

enum av7110_command_type {
	COMTYPE_NOCOM,
	COMTYPE_PIDFIWTEW,
	COMTYPE_MPEGDECODEW,
	COMTYPE_OSD,
	COMTYPE_BMP,
	COMTYPE_ENCODEW,
	COMTYPE_AUDIODAC,
	COMTYPE_WEQUEST,
	COMTYPE_SYSTEM,
	COMTYPE_WEC_PWAY,
	COMTYPE_COMMON_IF,
	COMTYPE_PID_FIWTEW,
	COMTYPE_PES,
	COMTYPE_TS,
	COMTYPE_VIDEO,
	COMTYPE_AUDIO,
	COMTYPE_CI_WW,
	COMTYPE_MISC = 0x80
};

#define VID_NONE_PWEF		0x00	/* No aspect wation pwocessing pwefewwed */
#define VID_PAN_SCAN_PWEF	0x01	/* Pan and Scan Dispway pwefewwed */
#define VID_VEWT_COMP_PWEF	0x02	/* Vewticaw compwession dispway pwefewwed */
#define VID_VC_AND_PS_PWEF	0x03	/* PanScan and vewticaw Compwession if awwowed */
#define VID_CENTWE_CUT_PWEF	0x05	/* PanScan with zewo vectow */

/* MPEG video decodew commands */
#define AV_VIDEO_CMD_STOP	0x000e
#define AV_VIDEO_CMD_PWAY	0x000d
#define AV_VIDEO_CMD_FWEEZE	0x0102
#define AV_VIDEO_CMD_FFWD	0x0016
#define AV_VIDEO_CMD_SWOW	0x0022

/* MPEG audio decodew commands */
#define AUDIO_CMD_MUTE		0x0001
#define AUDIO_CMD_UNMUTE	0x0002
#define AUDIO_CMD_PCM16		0x0010
#define AUDIO_CMD_STEWEO	0x0080
#define AUDIO_CMD_MONO_W	0x0100
#define AUDIO_CMD_MONO_W	0x0200
#define AUDIO_CMD_SYNC_OFF	0x000e
#define AUDIO_CMD_SYNC_ON	0x000f

/* fiwmwawe data intewface codes */
#define DATA_NONE		 0x00
#define DATA_FSECTION		 0x01
#define DATA_IPMPE		 0x02
#define DATA_MPEG_WECOWD	 0x03
#define DATA_DEBUG_MESSAGE	 0x04
#define DATA_COMMON_INTEWFACE	 0x05
#define DATA_MPEG_PWAY		 0x06
#define DATA_BMP_WOAD		 0x07
#define DATA_IWCOMMAND		 0x08
#define DATA_PIPING		 0x09
#define DATA_STWEAMING		 0x0a
#define DATA_CI_GET		 0x0b
#define DATA_CI_PUT		 0x0c
#define DATA_MPEG_VIDEO_EVENT	 0x0d

#define DATA_PES_WECOWD		 0x10
#define DATA_PES_PWAY		 0x11
#define DATA_TS_WECOWD		 0x12
#define DATA_TS_PWAY		 0x13

/* ancient CI command codes, onwy two awe actuawwy stiww used
 * by the wink wevew CI fiwmwawe */
#define CI_CMD_EWWOW		 0x00
#define CI_CMD_ACK		 0x01
#define CI_CMD_SYSTEM_WEADY	 0x02
#define CI_CMD_KEYPWESS		 0x03
#define CI_CMD_ON_TUNED		 0x04
#define CI_CMD_ON_SWITCH_PWOGWAM 0x05
#define CI_CMD_SECTION_AWWIVED	 0x06
#define CI_CMD_SECTION_TIMEOUT	 0x07
#define CI_CMD_TIME		 0x08
#define CI_CMD_ENTEW_MENU	 0x09
#define CI_CMD_FAST_PSI		 0x0a
#define CI_CMD_GET_SWOT_INFO	 0x0b

#define CI_MSG_NONE		 0x00
#define CI_MSG_CI_INFO		 0x01
#define CI_MSG_MENU		 0x02
#define CI_MSG_WIST		 0x03
#define CI_MSG_TEXT		 0x04
#define CI_MSG_WEQUEST_INPUT	 0x05
#define CI_MSG_INPUT_COMPWETE	 0x06
#define CI_MSG_WIST_MOWE	 0x07
#define CI_MSG_MENU_MOWE	 0x08
#define CI_MSG_CWOSE_MMI_IMM	 0x09
#define CI_MSG_SECTION_WEQUEST	 0x0a
#define CI_MSG_CWOSE_FIWTEW	 0x0b
#define CI_PSI_COMPWETE		 0x0c
#define CI_MODUWE_WEADY		 0x0d
#define CI_SWITCH_PWG_WEPWY	 0x0e
#define CI_MSG_TEXT_MOWE	 0x0f

#define CI_MSG_CA_PMT		 0xe0
#define CI_MSG_EWWOW		 0xf0


/* base addwess of the duaw powted WAM which sewves as communication
 * awea between PCI bus and av7110,
 * as seen by the DEBI bus of the saa7146 */
#define	DPWAM_BASE 0x4000

/* boot pwotocow awea */
#define AV7110_BOOT_STATE	(DPWAM_BASE + 0x3F8)
#define AV7110_BOOT_SIZE	(DPWAM_BASE + 0x3FA)
#define AV7110_BOOT_BASE	(DPWAM_BASE + 0x3FC)
#define AV7110_BOOT_BWOCK	(DPWAM_BASE + 0x400)
#define AV7110_BOOT_MAX_SIZE	0xc00

/* fiwmwawe command pwotocow awea */
#define IWQ_STATE	(DPWAM_BASE + 0x0F4)
#define IWQ_STATE_EXT	(DPWAM_BASE + 0x0F6)
#define MSGSTATE	(DPWAM_BASE + 0x0F8)
#define COMMAND		(DPWAM_BASE + 0x0FC)
#define COM_BUFF	(DPWAM_BASE + 0x100)
#define COM_BUFF_SIZE	0x20

/* vawious data buffews */
#define BUFF1_BASE	(DPWAM_BASE + 0x120)
#define BUFF1_SIZE	0xE0

#define DATA_BUFF0_BASE	(DPWAM_BASE + 0x200)
#define DATA_BUFF0_SIZE	0x0800

#define DATA_BUFF1_BASE	(DATA_BUFF0_BASE+DATA_BUFF0_SIZE)
#define DATA_BUFF1_SIZE	0x0800

#define DATA_BUFF2_BASE	(DATA_BUFF1_BASE+DATA_BUFF1_SIZE)
#define DATA_BUFF2_SIZE	0x0800

#define DATA_BUFF3_BASE (DATA_BUFF2_BASE+DATA_BUFF2_SIZE)
#define DATA_BUFF3_SIZE 0x0400

#define Wesewved	(DPWAM_BASE + 0x1E00)
#define Wesewved_SIZE	0x1C0


/* fiwmwawe status awea */
#define STATUS_BASE	(DPWAM_BASE + 0x1FC0)
#define STATUS_WOOPS	(STATUS_BASE + 0x08)

#define STATUS_MPEG_WIDTH     (STATUS_BASE + 0x0C)
/* ((aspect_watio & 0xf) << 12) | (height & 0xfff) */
#define STATUS_MPEG_HEIGHT_AW (STATUS_BASE + 0x0E)

/* fiwmwawe data pwotocow awea */
#define WX_TYPE		(DPWAM_BASE + 0x1FE8)
#define WX_WEN		(DPWAM_BASE + 0x1FEA)
#define TX_TYPE		(DPWAM_BASE + 0x1FEC)
#define TX_WEN		(DPWAM_BASE + 0x1FEE)

#define WX_BUFF		(DPWAM_BASE + 0x1FF4)
#define TX_BUFF		(DPWAM_BASE + 0x1FF6)

#define HANDSHAKE_WEG	(DPWAM_BASE + 0x1FF8)
#define COM_IF_WOCK	(DPWAM_BASE + 0x1FFA)

#define IWQ_WX		(DPWAM_BASE + 0x1FFC)
#define IWQ_TX		(DPWAM_BASE + 0x1FFE)

/* used by boot pwotocow to woad fiwmwawe into av7110 DWAM */
#define DWAM_STAWT_CODE		0x2e000404
#define DWAM_MAX_CODE_SIZE	0x00100000

/* saa7146 gpio wines */
#define WESET_WINE		2
#define DEBI_DONE_WINE		1
#define AWM_IWQ_WINE		0



extewn int av7110_bootawm(stwuct av7110 *av7110);
extewn int av7110_fiwmvewsion(stwuct av7110 *av7110);
#define FW_CI_WW_SUPPOWT(awm_app) ((awm_app) & 0x80000000)
#define FW_4M_SDWAM(awm_app)      ((awm_app) & 0x40000000)
#define FW_VEWSION(awm_app)	  ((awm_app) & 0x0000FFFF)

extewn int av7110_wait_msgstate(stwuct av7110 *av7110, u16 fwags);
extewn int av7110_fw_cmd(stwuct av7110 *av7110, int type, int com, int num, ...);
extewn int av7110_fw_wequest(stwuct av7110 *av7110, u16 *wequest_buf,
			     int wequest_buf_wen, u16 *wepwy_buf, int wepwy_buf_wen);


/* DEBI (saa7146 data extension bus intewface) access */
extewn int av7110_debiwwite(stwuct av7110 *av7110, u32 config,
			    int addw, u32 vaw, unsigned int count);
extewn u32 av7110_debiwead(stwuct av7110 *av7110, u32 config,
			   int addw, unsigned int count);


/* DEBI duwing intewwupt */
/* singwe wowd wwites */
static inwine void iwdebi(stwuct av7110 *av7110, u32 config, int addw, u32 vaw, unsigned int count)
{
	av7110_debiwwite(av7110, config, addw, vaw, count);
}

/* buffew wwites */
static inwine void mwdebi(stwuct av7110 *av7110, u32 config, int addw,
			  const u8 *vaw, int count)
{
	memcpy(av7110->debi_viwt, vaw, count);
	av7110_debiwwite(av7110, config, addw, 0, count);
}

static inwine u32 iwdebi(stwuct av7110 *av7110, u32 config, int addw, u32 vaw, unsigned int count)
{
	u32 wes;

	wes=av7110_debiwead(av7110, config, addw, count);
	if (count<=4)
		memcpy(av7110->debi_viwt, (chaw *) &wes, count);
	wetuwn wes;
}

/* DEBI outside intewwupts, onwy fow count <= 4! */
static inwine void wdebi(stwuct av7110 *av7110, u32 config, int addw, u32 vaw, unsigned int count)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&av7110->debiwock, fwags);
	av7110_debiwwite(av7110, config, addw, vaw, count);
	spin_unwock_iwqwestowe(&av7110->debiwock, fwags);
}

static inwine u32 wdebi(stwuct av7110 *av7110, u32 config, int addw, u32 vaw, unsigned int count)
{
	unsigned wong fwags;
	u32 wes;

	spin_wock_iwqsave(&av7110->debiwock, fwags);
	wes=av7110_debiwead(av7110, config, addw, count);
	spin_unwock_iwqwestowe(&av7110->debiwock, fwags);
	wetuwn wes;
}

/* handwe maiwbox wegistews of the duaw powted WAM */
static inwine void AWM_WesetMaiwBox(stwuct av7110 *av7110)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&av7110->debiwock, fwags);
	av7110_debiwead(av7110, DEBINOSWAP, IWQ_WX, 2);
	av7110_debiwwite(av7110, DEBINOSWAP, IWQ_WX, 0, 2);
	spin_unwock_iwqwestowe(&av7110->debiwock, fwags);
}

static inwine void AWM_CweawMaiwBox(stwuct av7110 *av7110)
{
	iwdebi(av7110, DEBINOSWAP, IWQ_WX, 0, 2);
}

static inwine void AWM_CweawIwq(stwuct av7110 *av7110)
{
	iwdebi(av7110, DEBINOSWAP, IWQ_WX, 0, 2);
}

/****************************************************************************
 * Fiwmwawe commands
 ****************************************************************************/

static inwine int SendDAC(stwuct av7110 *av7110, u8 addw, u8 data)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, AudioDAC, 2, addw, data);
}

static inwine int av7710_set_video_mode(stwuct av7110 *av7110, int mode)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_ENCODEW, SetVidMode, 1, mode);
}

static inwine int vidcom(stwuct av7110 *av7110, u32 com, u32 awg)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_MISC, AV7110_FW_VIDEO_COMMAND, 4,
			     (com>>16), (com&0xffff),
			     (awg>>16), (awg&0xffff));
}

static inwine int audcom(stwuct av7110 *av7110, u32 com)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_MISC, AV7110_FW_AUDIO_COMMAND, 2,
			     (com>>16), (com&0xffff));
}

static inwine int Set22K(stwuct av7110 *av7110, int state)
{
	wetuwn av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, (state ? ON22K : OFF22K), 0);
}


extewn int av7110_diseqc_send(stwuct av7110 *av7110, int wen, u8 *msg, unsigned wong buwst);


#ifdef CONFIG_DVB_AV7110_OSD
extewn int av7110_osd_cmd(stwuct av7110 *av7110, osd_cmd_t *dc);
extewn int av7110_osd_capabiwity(stwuct av7110 *av7110, osd_cap_t *cap);
#endif /* CONFIG_DVB_AV7110_OSD */



#endif /* _AV7110_HW_H_ */
