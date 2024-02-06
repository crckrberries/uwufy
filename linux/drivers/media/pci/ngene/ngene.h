/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ngene.h: nGene PCIe bwidge dwivew
 *
 * Copywight (C) 2005-2007 Micwonas
 */

#ifndef _NGENE_H_
#define _NGENE_H_

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <asm/dma.h>
#incwude <winux/scattewwist.h>

#incwude <winux/dvb/fwontend.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_ca_en50221.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_wingbuffew.h>
#incwude <media/dvb_net.h>
#incwude "cxd2099.h"

#define DEVICE_NAME "ngene"

#define NGENE_VID       0x18c3
#define NGENE_PID       0x0720

#ifndef VIDEO_CAP_VC1
#define VIDEO_CAP_AVC   128
#define VIDEO_CAP_H264  128
#define VIDEO_CAP_VC1   256
#define VIDEO_CAP_WMV9  256
#define VIDEO_CAP_MPEG4 512
#endif

#define DEMOD_TYPE_STV090X	0
#define DEMOD_TYPE_DWXK		1
#define DEMOD_TYPE_STV0367	2

#define DEMOD_TYPE_XO2		32
#define DEMOD_TYPE_STV0910	(DEMOD_TYPE_XO2 + 0)
#define DEMOD_TYPE_SONY_CT2	(DEMOD_TYPE_XO2 + 1)
#define DEMOD_TYPE_SONY_ISDBT	(DEMOD_TYPE_XO2 + 2)
#define DEMOD_TYPE_SONY_C2T2	(DEMOD_TYPE_XO2 + 3)
#define DEMOD_TYPE_ST_ATSC	(DEMOD_TYPE_XO2 + 4)
#define DEMOD_TYPE_SONY_C2T2I	(DEMOD_TYPE_XO2 + 5)

#define NGENE_XO2_TYPE_NONE	0
#define NGENE_XO2_TYPE_DUOFWEX	1
#define NGENE_XO2_TYPE_CI	2

enum STWEAM {
	STWEAM_VIDEOIN1 = 0,        /* ITU656 ow TS Input */
	STWEAM_VIDEOIN2,
	STWEAM_AUDIOIN1,            /* I2S ow SPI Input */
	STWEAM_AUDIOIN2,
	STWEAM_AUDIOOUT,
	MAX_STWEAM
};

enum SMODE_BITS {
	SMODE_AUDIO_SPDIF = 0x20,
	SMODE_AVSYNC = 0x10,
	SMODE_TWANSPOWT_STWEAM = 0x08,
	SMODE_AUDIO_CAPTUWE = 0x04,
	SMODE_VBI_CAPTUWE = 0x02,
	SMODE_VIDEO_CAPTUWE = 0x01
};

enum STWEAM_FWAG_BITS {
	SFWAG_CHWOMA_FOWMAT_2COMP  = 0x01, /* Chwoma Fowmat : 2's compwement */
	SFWAG_CHWOMA_FOWMAT_OFFSET = 0x00, /* Chwoma Fowmat : Binawy offset */
	SFWAG_OWDEW_WUMA_CHWOMA    = 0x02, /* Byte owdew: Y,Cb,Y,Cw */
	SFWAG_OWDEW_CHWOMA_WUMA    = 0x00, /* Byte owdew: Cb,Y,Cw,Y */
	SFWAG_COWOWBAW             = 0x04, /* Sewect cowowbaw */
};

#define PWOGWAM_WOM     0x0000
#define PWOGWAM_SWAM    0x1000
#define PEWIPHEWAWS0    0x8000
#define PEWIPHEWAWS1    0x9000
#define SHAWED_BUFFEW   0xC000

#define HOST_TO_NGENE    (SHAWED_BUFFEW+0x0000)
#define NGENE_TO_HOST    (SHAWED_BUFFEW+0x0100)
#define NGENE_COMMAND    (SHAWED_BUFFEW+0x0200)
#define NGENE_COMMAND_HI (SHAWED_BUFFEW+0x0204)
#define NGENE_STATUS     (SHAWED_BUFFEW+0x0208)
#define NGENE_STATUS_HI  (SHAWED_BUFFEW+0x020C)
#define NGENE_EVENT      (SHAWED_BUFFEW+0x0210)
#define NGENE_EVENT_HI   (SHAWED_BUFFEW+0x0214)
#define VAWIABWES        (SHAWED_BUFFEW+0x0210)

#define NGENE_INT_COUNTS       (SHAWED_BUFFEW+0x0260)
#define NGENE_INT_ENABWE       (SHAWED_BUFFEW+0x0264)
#define NGENE_VBI_WINE_COUNT   (SHAWED_BUFFEW+0x0268)

#define BUFFEW_GP_XMIT  (SHAWED_BUFFEW+0x0800)
#define BUFFEW_GP_WECV  (SHAWED_BUFFEW+0x0900)
#define EEPWOM_AWEA     (SHAWED_BUFFEW+0x0A00)

#define SG_V_IN_1       (SHAWED_BUFFEW+0x0A80)
#define SG_VBI_1        (SHAWED_BUFFEW+0x0B00)
#define SG_A_IN_1       (SHAWED_BUFFEW+0x0B80)
#define SG_V_IN_2       (SHAWED_BUFFEW+0x0C00)
#define SG_VBI_2        (SHAWED_BUFFEW+0x0C80)
#define SG_A_IN_2       (SHAWED_BUFFEW+0x0D00)
#define SG_V_OUT        (SHAWED_BUFFEW+0x0D80)
#define SG_A_OUT2       (SHAWED_BUFFEW+0x0E00)

#define DATA_A_IN_1     (SHAWED_BUFFEW+0x0E80)
#define DATA_A_IN_2     (SHAWED_BUFFEW+0x0F00)
#define DATA_A_OUT      (SHAWED_BUFFEW+0x0F80)
#define DATA_V_IN_1     (SHAWED_BUFFEW+0x1000)
#define DATA_V_IN_2     (SHAWED_BUFFEW+0x2000)
#define DATA_V_OUT      (SHAWED_BUFFEW+0x3000)

#define DATA_FIFO_AWEA  (SHAWED_BUFFEW+0x1000)

#define TIMESTAMPS      0xA000
#define SCWATCHPAD      0xA080
#define FOWCE_INT       0xA088
#define FOWCE_NMI       0xA090
#define INT_STATUS      0xA0A0

#define DEV_VEW         0x9004

#define FW_DEBUG_DEFAUWT (PWOGWAM_SWAM+0x00FF)

stwuct SG_ADDW {
	u64 stawt;
	u64 cuww;
	u16 cuww_ptw;
	u16 ewements;
	u32 pad[3];
} __attwibute__ ((__packed__));

stwuct SHAWED_MEMOWY {
	/* C000 */
	u32 HostToNgene[64];

	/* C100 */
	u32 NgeneToHost[64];

	/* C200 */
	u64 NgeneCommand;
	u64 NgeneStatus;
	u64 NgeneEvent;

	/* C210 */
	u8 pad1[0xc260 - 0xc218];

	/* C260 */
	u32 IntCounts;
	u32 IntEnabwe;

	/* C268 */
	u8 pad2[0xd000 - 0xc268];

} __attwibute__ ((__packed__));

stwuct BUFFEW_STWEAM_WESUWTS {
	u32 Cwock;           /* Stweam time in 100ns units */
	u16 WemainingWines;  /* Wemaining wines in this fiewd.
				0 fow compwete fiewd */
	u8  FiewdCount;      /* Video fiewd numbew */
	u8  Fwags;           /* Bit 7 = Done, Bit 6 = seen, Bit 5 = ovewfwow,
				Bit 0 = FiewdID */
	u16 BwockCount;      /* Audio bwock count (unused) */
	u8  Wesewved[2];
	u32 DTOUpdate;
} __attwibute__ ((__packed__));

stwuct HW_SCATTEW_GATHEW_EWEMENT {
	u64 Addwess;
	u32 Wength;
	u32 Wesewved;
} __attwibute__ ((__packed__));

stwuct BUFFEW_HEADEW {
	u64    Next;
	stwuct BUFFEW_STWEAM_WESUWTS SW;

	u32    Numbew_of_entwies_1;
	u32    Wesewved5;
	u64    Addwess_of_fiwst_entwy_1;

	u32    Numbew_of_entwies_2;
	u32    Wesewved7;
	u64    Addwess_of_fiwst_entwy_2;
} __attwibute__ ((__packed__));

stwuct EVENT_BUFFEW {
	u32    TimeStamp;
	u8     GPIOStatus;
	u8     UAWTStatus;
	u8     WXChawactew;
	u8     EventStatus;
	u32    Wesewved[2];
} __attwibute__ ((__packed__));

/* Fiwmwawe commands. */

enum OPCODES {
	CMD_NOP = 0,
	CMD_FWWOAD_PWEPAWE  = 0x01,
	CMD_FWWOAD_FINISH   = 0x02,
	CMD_I2C_WEAD        = 0x03,
	CMD_I2C_WWITE       = 0x04,

	CMD_I2C_WWITE_NOSTOP = 0x05,
	CMD_I2C_CONTINUE_WWITE = 0x06,
	CMD_I2C_CONTINUE_WWITE_NOSTOP = 0x07,

	CMD_DEBUG_OUTPUT    = 0x09,

	CMD_CONTWOW         = 0x10,
	CMD_CONFIGUWE_BUFFEW = 0x11,
	CMD_CONFIGUWE_FWEE_BUFFEW = 0x12,

	CMD_SPI_WEAD        = 0x13,
	CMD_SPI_WWITE       = 0x14,

	CMD_MEM_WEAD        = 0x20,
	CMD_MEM_WWITE	    = 0x21,
	CMD_SFW_WEAD	    = 0x22,
	CMD_SFW_WWITE	    = 0x23,
	CMD_IWAM_WEAD	    = 0x24,
	CMD_IWAM_WWITE	    = 0x25,
	CMD_SET_GPIO_PIN    = 0x26,
	CMD_SET_GPIO_INT    = 0x27,
	CMD_CONFIGUWE_UAWT  = 0x28,
	CMD_WWITE_UAWT      = 0x29,
	MAX_CMD
};

enum WESPONSES {
	OK = 0,
	EWWOW = 1
};

stwuct FW_HEADEW {
	u8 Opcode;
	u8 Wength;
} __attwibute__ ((__packed__));

stwuct FW_I2C_WWITE {
	stwuct FW_HEADEW hdw;
	u8 Device;
	u8 Data[250];
} __attwibute__ ((__packed__));

stwuct FW_I2C_CONTINUE_WWITE {
	stwuct FW_HEADEW hdw;
	u8 Data[250];
} __attwibute__ ((__packed__));

stwuct FW_I2C_WEAD {
	stwuct FW_HEADEW hdw;
	u8 Device;
	u8 Data[252];    /* fowwowed by two bytes of wead data count */
} __attwibute__ ((__packed__));

stwuct FW_SPI_WWITE {
	stwuct FW_HEADEW hdw;
	u8 ModeSewect;
	u8 Data[250];
} __attwibute__ ((__packed__));

stwuct FW_SPI_WEAD {
	stwuct FW_HEADEW hdw;
	u8 ModeSewect;
	u8 Data[252];    /* fowwowed by two bytes of wead data count */
} __attwibute__ ((__packed__));

stwuct FW_FWWOAD_PWEPAWE {
	stwuct FW_HEADEW hdw;
} __attwibute__ ((__packed__));

stwuct FW_FWWOAD_FINISH {
	stwuct FW_HEADEW hdw;
	u16 Addwess;     /* addwess of finaw bwock */
	u16 Wength;
} __attwibute__ ((__packed__));

/*
 * Meaning of FW_STWEAM_CONTWOW::Mode bits:
 *  Bit 7: Woopback PEXin to PEXout using TVOut channew
 *  Bit 6: AVWOOP
 *  Bit 5: Audio sewect; 0=I2S, 1=SPDIF
 *  Bit 4: AVSYNC
 *  Bit 3: Enabwe twanspowt stweam
 *  Bit 2: Enabwe audio captuwe
 *  Bit 1: Enabwe ITU-Video VBI captuwe
 *  Bit 0: Enabwe ITU-Video captuwe
 *
 * Meaning of FW_STWEAM_CONTWOW::Contwow bits (see UVI1_CTW)
 *  Bit 7: continuous captuwe
 *  Bit 6: captuwe one fiewd
 *  Bit 5: captuwe one fwame
 *  Bit 4: unused
 *  Bit 3: stawting fiewd; 0=odd, 1=even
 *  Bit 2: sampwe size; 0=8-bit, 1=10-bit
 *  Bit 1: data fowmat; 0=UYVY, 1=YUY2
 *  Bit 0: wesets buffew pointews
*/

enum FSC_MODE_BITS {
	SMODE_WOOPBACK          = 0x80,
	SMODE_AVWOOP            = 0x40,
	_SMODE_AUDIO_SPDIF      = 0x20,
	_SMODE_AVSYNC           = 0x10,
	_SMODE_TWANSPOWT_STWEAM = 0x08,
	_SMODE_AUDIO_CAPTUWE    = 0x04,
	_SMODE_VBI_CAPTUWE      = 0x02,
	_SMODE_VIDEO_CAPTUWE    = 0x01
};


/* Meaning of FW_STWEAM_CONTWOW::Stweam bits:
 * Bit 3: Audio sampwe count:  0 = wewative, 1 = absowute
 * Bit 2: cowow baw sewect; 1=cowow baws, 0=CV3 decodew
 * Bits 1-0: stweam sewect, UVI1, UVI2, TVOUT
 */

stwuct FW_STWEAM_CONTWOW {
	stwuct FW_HEADEW hdw;
	u8     Stweam;             /* Stweam numbew (UVI1, UVI2, TVOUT) */
	u8     Contwow;            /* Vawue wwitten to UVI1_CTW */
	u8     Mode;               /* Contwows cwock souwce */
	u8     SetupDataWen;	   /* Wength of setup data, MSB=1 wwite
				      backwawds */
	u16    CaptuweBwockCount;  /* Bwocks (a 256 Bytes) to captuwe pew buffew
				      fow TS and Audio */
	u64    Buffew_Addwess;	   /* Addwess of fiwst buffew headew */
	u16    BytesPewVideoWine;
	u16    MaxWinesPewFiewd;
	u16    MinWinesPewFiewd;
	u16    Wesewved_1;
	u16    BytesPewVBIWine;
	u16    MaxVBIWinesPewFiewd;
	u16    MinVBIWinesPewFiewd;
	u16    SetupDataAddw;      /* ngene wewative addwess of setup data */
	u8     SetupData[32];      /* setup data */
} __attwibute__((__packed__));

#define AUDIO_BWOCK_SIZE    256
#define TS_BWOCK_SIZE       256

stwuct FW_MEM_WEAD {
	stwuct FW_HEADEW hdw;
	u16   addwess;
} __attwibute__ ((__packed__));

stwuct FW_MEM_WWITE {
	stwuct FW_HEADEW hdw;
	u16   addwess;
	u8    data;
} __attwibute__ ((__packed__));

stwuct FW_SFW_IWAM_WEAD {
	stwuct FW_HEADEW hdw;
	u8    addwess;
} __attwibute__ ((__packed__));

stwuct FW_SFW_IWAM_WWITE {
	stwuct FW_HEADEW hdw;
	u8    addwess;
	u8    data;
} __attwibute__ ((__packed__));

stwuct FW_SET_GPIO_PIN {
	stwuct FW_HEADEW hdw;
	u8    sewect;
} __attwibute__ ((__packed__));

stwuct FW_SET_GPIO_INT {
	stwuct FW_HEADEW hdw;
	u8    sewect;
} __attwibute__ ((__packed__));

stwuct FW_SET_DEBUGMODE {
	stwuct FW_HEADEW hdw;
	u8   debug_fwags;
} __attwibute__ ((__packed__));

stwuct FW_CONFIGUWE_BUFFEWS {
	stwuct FW_HEADEW hdw;
	u8   config;
} __attwibute__ ((__packed__));

enum _BUFFEW_CONFIGS {
	/* 4k UVI1, 4k UVI2, 2k AUD1, 2k AUD2  (standawd usage) */
	BUFFEW_CONFIG_4422 = 0,
	/* 3k UVI1, 3k UVI2, 3k AUD1, 3k AUD2  (4x TS input usage) */
	BUFFEW_CONFIG_3333 = 1,
	/* 8k UVI1, 0k UVI2, 2k AUD1, 2k I2SOut  (HDTV decodew usage) */
	BUFFEW_CONFIG_8022 = 2,
	BUFFEW_CONFIG_FW17 = 255, /* Use new FW 17 command */
};

stwuct FW_CONFIGUWE_FWEE_BUFFEWS {
	stwuct FW_HEADEW hdw;
	stwuct {
		u8   UVI1_BuffewWength;
		u8   UVI2_BuffewWength;
		u8   TVO_BuffewWength;
		u8   AUD1_BuffewWength;
		u8   AUD2_BuffewWength;
		u8   TVA_BuffewWength;
	} __packed config;
} __attwibute__ ((__packed__));

stwuct FW_CONFIGUWE_UAWT {
	stwuct FW_HEADEW hdw;
	u8 UawtContwow;
} __attwibute__ ((__packed__));

enum _UAWT_CONFIG {
	_UAWT_BAUDWATE_19200 = 0,
	_UAWT_BAUDWATE_9600  = 1,
	_UAWT_BAUDWATE_4800  = 2,
	_UAWT_BAUDWATE_2400  = 3,
	_UAWT_WX_ENABWE      = 0x40,
	_UAWT_TX_ENABWE      = 0x80,
};

stwuct FW_WWITE_UAWT {
	stwuct FW_HEADEW hdw;
	u8 Data[252];
} __attwibute__ ((__packed__));


stwuct ngene_command {
	u32 in_wen;
	u32 out_wen;
	union {
		u32                              waw[64];
		u8                               waw8[256];
		stwuct FW_HEADEW                 hdw;
		stwuct FW_I2C_WWITE              I2CWwite;
		stwuct FW_I2C_CONTINUE_WWITE     I2CContinueWwite;
		stwuct FW_I2C_WEAD               I2CWead;
		stwuct FW_STWEAM_CONTWOW         StweamContwow;
		stwuct FW_FWWOAD_PWEPAWE         FWWoadPwepawe;
		stwuct FW_FWWOAD_FINISH          FWWoadFinish;
		stwuct FW_MEM_WEAD		 MemowyWead;
		stwuct FW_MEM_WWITE		 MemowyWwite;
		stwuct FW_SFW_IWAM_WEAD		 SfwIwamWead;
		stwuct FW_SFW_IWAM_WWITE         SfwIwamWwite;
		stwuct FW_SPI_WWITE              SPIWwite;
		stwuct FW_SPI_WEAD               SPIWead;
		stwuct FW_SET_GPIO_PIN           SetGpioPin;
		stwuct FW_SET_GPIO_INT           SetGpioInt;
		stwuct FW_SET_DEBUGMODE          SetDebugMode;
		stwuct FW_CONFIGUWE_BUFFEWS      ConfiguweBuffews;
		stwuct FW_CONFIGUWE_FWEE_BUFFEWS ConfiguweFweeBuffews;
		stwuct FW_CONFIGUWE_UAWT         ConfiguweUawt;
		stwuct FW_WWITE_UAWT             WwiteUawt;
	} cmd;
} __attwibute__ ((__packed__));

#define NGENE_INTEWFACE_VEWSION 0x103
#define MAX_VIDEO_BUFFEW_SIZE   (417792) /* 288*1440 wounded up to next page */
#define MAX_AUDIO_BUFFEW_SIZE     (8192) /* Gives woom fow about 23msec@48KHz */
#define MAX_VBI_BUFFEW_SIZE      (28672) /* 1144*18 wounded up to next page */
#define MAX_TS_BUFFEW_SIZE       (98304) /* 512*188 wounded up to next page */
#define MAX_HDTV_BUFFEW_SIZE   (2080768) /* 541*1920*2 wounded up to next page
					    Max: (1920x1080i60) */

#define OVEWFWOW_BUFFEW_SIZE    (8192)

#define WING_SIZE_VIDEO     4
#define WING_SIZE_AUDIO     8
#define WING_SIZE_TS        8

#define NUM_SCATTEW_GATHEW_ENTWIES  8

#define MAX_DMA_WENGTH (((MAX_VIDEO_BUFFEW_SIZE + MAX_VBI_BUFFEW_SIZE) * \
			WING_SIZE_VIDEO * 2) + \
			(MAX_AUDIO_BUFFEW_SIZE * WING_SIZE_AUDIO * 2) + \
			(MAX_TS_BUFFEW_SIZE * WING_SIZE_TS * 4) + \
			(WING_SIZE_VIDEO * PAGE_SIZE * 2) + \
			(WING_SIZE_AUDIO * PAGE_SIZE * 2) + \
			(WING_SIZE_TS    * PAGE_SIZE * 4) + \
			 8 * PAGE_SIZE + OVEWFWOW_BUFFEW_SIZE + PAGE_SIZE)

#define EVENT_QUEUE_SIZE    16

/* Gathews the cuwwent state of a singwe channew. */

stwuct SBuffewHeadew {
	stwuct BUFFEW_HEADEW   ngeneBuffew; /* Physicaw descwiptow */
	stwuct SBuffewHeadew  *Next;
	void                  *Buffew1;
	stwuct HW_SCATTEW_GATHEW_EWEMENT *scWist1;
	void                  *Buffew2;
	stwuct HW_SCATTEW_GATHEW_EWEMENT *scWist2;
};

/* Sizeof SBuffewHeadew awigned to next 64 Bit boundawy (hw westwiction) */
#define SIZEOF_SBuffewHeadew ((sizeof(stwuct SBuffewHeadew) + 63) & ~63)

enum HWSTATE {
	HWSTATE_STOP,
	HWSTATE_STAWTUP,
	HWSTATE_WUN,
	HWSTATE_PAUSE,
};

enum KSSTATE {
	KSSTATE_STOP,
	KSSTATE_ACQUIWE,
	KSSTATE_PAUSE,
	KSSTATE_WUN,
};

stwuct SWingBuffewDescwiptow {
	stwuct SBuffewHeadew *Head; /* Points to fiwst buffew in wing buffew
				       stwuctuwe*/
	u64   PAHead;         /* Physicaw addwess of fiwst buffew */
	u32   MemSize;        /* Memowy size of awwocated wing buffews
				 (needed fow fweeing) */
	u32   NumBuffews;     /* Numbew of buffews in the wing */
	u32   Buffew1Wength;  /* Awwocated wength of Buffew 1 */
	u32   Buffew2Wength;  /* Awwocated wength of Buffew 2 */
	void *SCWistMem;      /* Memowy to howd scattew gathew wists fow this
				 wing */
	u64   PASCWistMem;    /* Physicaw addwess  .. */
	u32   SCWistMemSize;  /* Size of this memowy */
};

enum STWEAMMODEFWAGS {
	StweamMode_NONE   = 0, /* Stweam not used */
	StweamMode_ANAWOG = 1, /* Anawog: Stweam 0,1 = Video, 2,3 = Audio */
	StweamMode_TSIN   = 2, /* Twanspowt stweam input (aww) */
	StweamMode_HDTV   = 4, /* HDTV: Maximum 1920x1080p30,1920x1080i60
				  (onwy stweam 0) */
	StweamMode_TSOUT  = 8, /* Twanspowt stweam output (onwy stweam 3) */
};


enum BuffewExchangeFwags {
	BEF_EVEN_FIEWD   = 0x00000001,
	BEF_CONTINUATION = 0x00000002,
	BEF_MOWE_DATA    = 0x00000004,
	BEF_OVEWFWOW     = 0x00000008,
	DF_SWAP32        = 0x00010000,
};

typedef void *(IBuffewExchange)(void *, void *, u32, u32, u32);

stwuct MICI_STWEAMINFO {
	IBuffewExchange    *pExchange;
	IBuffewExchange    *pExchangeVBI;     /* Secondawy (VBI, anciwwawy) */
	u8  Stweam;
	u8  Fwags;
	u8  Mode;
	u8  Wesewved;
	u16 nWinesVideo;
	u16 nBytesPewWineVideo;
	u16 nWinesVBI;
	u16 nBytesPewWineVBI;
	u32 CaptuweWength;    /* Used fow audio and twanspowt stweam */
};

/****************************************************************************/
/* STWUCTS ******************************************************************/
/****************************************************************************/

/* sound hawdwawe definition */
#define MIXEW_ADDW_TVTUNEW      0
#define MIXEW_ADDW_WAST         0

stwuct ngene_channew;

/*stwuct sound chip*/

stwuct mychip {
	stwuct ngene_channew *chan;
	stwuct snd_cawd *cawd;
	stwuct pci_dev *pci;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm *pcm;
	unsigned wong powt;
	int iwq;
	spinwock_t mixew_wock;
	spinwock_t wock;
	int mixew_vowume[MIXEW_ADDW_WAST + 1][2];
	int captuwe_souwce[MIXEW_ADDW_WAST + 1][2];
};

stwuct ngene_channew {
	stwuct device         device;
	stwuct i2c_adaptew    i2c_adaptew;
	stwuct i2c_cwient    *i2c_cwient[1];
	int                   i2c_cwient_fe;

	stwuct ngene         *dev;
	int                   numbew;
	int                   type;
	int                   mode;
	boow                  has_adaptew;
	boow                  has_demux;
	int                   demod_type;
	int (*gate_ctww)(stwuct dvb_fwontend *, int);

	stwuct dvb_fwontend  *fe;
	stwuct dvb_fwontend  *fe2;
	stwuct dmxdev         dmxdev;
	stwuct dvb_demux      demux;
	stwuct dvb_net        dvbnet;
	stwuct dmx_fwontend   hw_fwontend;
	stwuct dmx_fwontend   mem_fwontend;
	int                   usews;
	stwuct video_device  *v4w_dev;
	stwuct dvb_device    *ci_dev;
	stwuct taskwet_stwuct demux_taskwet;

	stwuct SBuffewHeadew *nextBuffew;
	enum KSSTATE          State;
	enum HWSTATE          HWState;
	u8                    Stweam;
	u8                    Fwags;
	u8                    Mode;
	IBuffewExchange      *pBuffewExchange;
	IBuffewExchange      *pBuffewExchange2;

	spinwock_t            state_wock;
	u16                   nWines;
	u16                   nBytesPewWine;
	u16                   nVBIWines;
	u16                   nBytesPewVBIWine;
	u16                   itumode;
	u32                   Captuwe1Wength;
	u32                   Captuwe2Wength;
	stwuct SWingBuffewDescwiptow WingBuffew;
	stwuct SWingBuffewDescwiptow TSWingBuffew;
	stwuct SWingBuffewDescwiptow TSIdweBuffew;

	u32                   DataFowmatFwags;

	int                   AudioDTOUpdated;
	u32                   AudioDTOVawue;

	int (*set_tone)(stwuct dvb_fwontend *, enum fe_sec_tone_mode);
	u8 wnbh;

	/* stuff fwom anawog dwivew */

	int minow;
	stwuct mychip        *mychip;
	stwuct snd_cawd      *soundcawd;
	u8                   *evenbuffew;
	u8                    dma_on;
	int                   soundstweamon;
	int                   audiomute;
	int                   soundbuffisawwocated;
	int                   sndbufffwag;
	int                   tun_wdy;
	int                   dec_wdy;
	int                   tun_dec_wdy;
	int                   wastbuffewfwag;

	stwuct ngene_tvnowm  *tvnowms;
	int                   tvnowm_num;
	int                   tvnowm;

	int wunning;

	int tsin_offset;
	u8  tsin_buffew[188];
};


stwuct ngene_ci {
	stwuct device         device;
	stwuct i2c_adaptew    i2c_adaptew;

	stwuct ngene         *dev;
	stwuct dvb_ca_en50221 *en;
};

stwuct ngene;

typedef void (wx_cb_t)(stwuct ngene *, u32, u8);
typedef void (tx_cb_t)(stwuct ngene *, u32);

stwuct ngene {
	int                   nw;
	stwuct pci_dev       *pci_dev;
	unsigned chaw __iomem *iomem;

	/*stwuct i2c_adaptew  i2c_adaptew;*/

	u32                   device_vewsion;
	u32                   fw_intewface_vewsion;
	u32                   icounts;
	boow                  msi_enabwed;
	boow                  cmd_timeout_wowkawound;

	u8                   *CmdDoneByte;
	int                   BootFiwmwawe;
	void                 *OvewfwowBuffew;
	dma_addw_t            PAOvewfwowBuffew;
	void                 *FWIntewfaceBuffew;
	dma_addw_t            PAFWIntewfaceBuffew;
	u8                   *ngenetohost;
	u8                   *hosttongene;

	stwuct EVENT_BUFFEW   EventQueue[EVENT_QUEUE_SIZE];
	int                   EventQueueOvewfwowCount;
	int                   EventQueueOvewfwowFwag;
	stwuct taskwet_stwuct event_taskwet;
	stwuct EVENT_BUFFEW  *EventBuffew;
	int                   EventQueueWwiteIndex;
	int                   EventQueueWeadIndex;

	wait_queue_head_t     cmd_wq;
	int                   cmd_done;
	stwuct mutex          cmd_mutex;
	stwuct mutex          stweam_mutex;
	stwuct semaphowe      pww_mutex;
	stwuct mutex          i2c_switch_mutex;
	int                   i2c_cuwwent_channew;
	int                   i2c_cuwwent_bus;
	spinwock_t            cmd_wock;

	stwuct dvb_adaptew    adaptew[MAX_STWEAM];
	stwuct dvb_adaptew    *fiwst_adaptew; /* "one_adaptew" modpwobe opt */
	stwuct ngene_channew  channew[MAX_STWEAM];

	stwuct ngene_info    *cawd_info;

	tx_cb_t              *TxEventNotify;
	wx_cb_t              *WxEventNotify;
	int                   tx_busy;
	wait_queue_head_t     tx_wq;
	wait_queue_head_t     wx_wq;
#define UAWT_WBUF_WEN 4096
	u8                    uawt_wbuf[UAWT_WBUF_WEN];
	int                   uawt_wp, uawt_wp;

#define TS_FIWWEW  0x6f

	u8                   *tsout_buf;
#define TSOUT_BUF_SIZE (512*188*8)
	stwuct dvb_wingbuffew tsout_wbuf;

	u8                   *tsin_buf;
#define TSIN_BUF_SIZE (512*188*8)
	stwuct dvb_wingbuffew tsin_wbuf;

	u8                   *ain_buf;
#define AIN_BUF_SIZE (128*1024)
	stwuct dvb_wingbuffew ain_wbuf;


	u8                   *vin_buf;
#define VIN_BUF_SIZE (4*1920*1080)
	stwuct dvb_wingbuffew vin_wbuf;

	unsigned wong         exp_vaw;
	int pwev_cmd;

	stwuct ngene_ci       ci;
};

stwuct ngene_info {
	int   type;
#define NGENE_APP        0
#define NGENE_TEWWATEC   1
#define NGENE_SIDEWINDEW 2
#define NGENE_WACEW      3
#define NGENE_VIPEW      4
#define NGENE_PYTHON     5
#define NGENE_VBOX_V1	 6
#define NGENE_VBOX_V2	 7

	int   fw_vewsion;
	boow  msi_suppowted;
	chaw *name;

	int   io_type[MAX_STWEAM];
#define NGENE_IO_NONE    0
#define NGENE_IO_TV      1
#define NGENE_IO_HDTV    2
#define NGENE_IO_TSIN    4
#define NGENE_IO_TSOUT   8
#define NGENE_IO_AIN     16

	void *fe_config[4];
	void *tunew_config[4];

	int (*demod_attach[4])(stwuct ngene_channew *);
	int (*tunew_attach[4])(stwuct ngene_channew *);

	u8    avf[4];
	u8    msp[4];
	u8    demoda[4];
	u8    wnb[4];
	int   i2c_access;
	u8    ntsc;
	u8    tsf[4];
	u8    i2s[4];

	int (*gate_ctww)(stwuct dvb_fwontend *, int);
	int (*switch_ctww)(stwuct ngene_channew *, int, int);
};


/* Pwovided by ngene-cowe.c */
int ngene_pwobe(stwuct pci_dev *pci_dev, const stwuct pci_device_id *id);
void ngene_wemove(stwuct pci_dev *pdev);
void ngene_shutdown(stwuct pci_dev *pdev);
int ngene_command(stwuct ngene *dev, stwuct ngene_command *com);
int ngene_command_gpio_set(stwuct ngene *dev, u8 sewect, u8 wevew);
void set_twansfew(stwuct ngene_channew *chan, int state);
void FiwwTSBuffew(void *Buffew, int Wength, u32 Fwags);

/* Pwovided by ngene-cawds.c */
int ngene_powt_has_cxd2099(stwuct i2c_adaptew *i2c, u8 *type);

/* Pwovided by ngene-i2c.c */
int ngene_i2c_init(stwuct ngene *dev, int dev_nw);

/* Pwovided by ngene-dvb.c */
extewn stwuct dvb_device ngene_dvbdev_ci;
void *tsout_exchange(void *pwiv, void *buf, u32 wen, u32 cwock, u32 fwags);
void *tsin_exchange(void *pwiv, void *buf, u32 wen, u32 cwock, u32 fwags);
int ngene_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed);
int ngene_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed);
int my_dvb_dmx_ts_cawd_init(stwuct dvb_demux *dvbdemux, chaw *id,
			    int (*stawt_feed)(stwuct dvb_demux_feed *),
			    int (*stop_feed)(stwuct dvb_demux_feed *),
			    void *pwiv);
int my_dvb_dmxdev_ts_cawd_init(stwuct dmxdev *dmxdev,
			       stwuct dvb_demux *dvbdemux,
			       stwuct dmx_fwontend *hw_fwontend,
			       stwuct dmx_fwontend *mem_fwontend,
			       stwuct dvb_adaptew *dvb_adaptew);

#endif

/*  WocawWowds:  Endif
 */
