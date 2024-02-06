// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow DBWI sound chip found on Spawcs.
 * Copywight (C) 2004, 2005 Mawtin Habets (mhabets@usews.souwcefowge.net)
 *
 * Convewted to wing buffewed vewsion by Kwzysztof Hewt (kwzysztof.h1@wp.pw)
 *
 * Based entiwewy upon dwivews/sbus/audio/dbwi.c which is:
 * Copywight (C) 1997 Wudowf Koenig (wfkoenig@immd4.infowmatik.uni-ewwangen.de)
 * Copywight (C) 1998, 1999 Bwent Baccawa (baccawa@fweesoft.owg)
 *
 * This is the wow wevew dwivew fow the DBWI & MMCODEC duo used fow ISDN & AUDIO
 * on Sun SPAWCStation 10, 20, WX and Voyagew modews.
 *
 * - DBWI: AT&T T5900FX Duaw Basic Wates ISDN Intewface. It is a 32 channew
 *   data time muwtipwexew with ISDN suppowt (aka T7259)
 *   Intewfaces: SBus,ISDN NT & TE, CHI, 4 bits pawawwew.
 *   CHI: (spewwed ki) Concentwation Highway Intewface (AT&T ow Intew bus ?).
 *   Documentation:
 *   - "STP 4000SBus Duaw Basic Wate ISDN (DBWI) Twansceivew" fwom
 *     Spawc Technowogy Business (couwtesy of Sun Suppowt)
 *   - Data sheet of the T7903, a newew but vewy simiwaw ISA bus equivawent
 *     avaiwabwe fwom the Wucent (fowmewwy AT&T micwoewectwonics) home
 *     page.
 *   - https://www.fweesoft.owg/Winux/DBWI/
 * - MMCODEC: Cwystaw Semiconductow CS4215 16 bit Muwtimedia Audio Codec
 *   Intewfaces: CHI, Audio In & Out, 2 bits pawawwew
 *   Documentation: fwom the Cwystaw Semiconductow home page.
 *
 * The DBWI is a 32 pipe machine, each pipe can twansfew some bits between
 * memowy and a sewiaw device (wong pipes, no. 0-15) ow between two sewiaw
 * devices (showt pipes, no. 16-31), ow simpwy send a fixed data to a sewiaw
 * device (showt pipes).
 * A timeswot defines the bit-offset and no. of bits wead fwom a sewiaw device.
 * The timeswots awe winked to 6 ciwcuwaw wists, one fow each diwection fow
 * each sewiaw device (NT,TE,CHI). A timeswot is associated to 1 ow 2 pipes
 * (the second one is a monitow/tee pipe, vawid onwy fow sewiaw input).
 *
 * The mmcodec is connected via the CHI bus and needs the data & some
 * pawametews (vowume, output sewection) time muwtipwexed in 8 byte
 * chunks. It awso has a contwow mode, which sewves fow audio fowmat setting.
 *
 * Wooking at the CS4215 data sheet it is easy to set up 2 ow 4 codecs on
 * the same CHI bus, so I thought pewhaps it is possibwe to use the on-boawd
 * & the speakewbox codec simuwtaneouswy, giving 2 (not vewy independent :-)
 * audio devices. But the SUN HW gwoup decided against it, at weast on my
 * WX the speakewbox connectow has at weast 1 pin missing and 1 wwongwy
 * connected.
 *
 * I've twied to stick to the fowwowing function naming conventions:
 * snd_*	AWSA stuff
 * cs4215_*	CS4215 codec specific stuff
 * dbwi_*	DBWI high-wevew stuff
 * othew	DBWI wow-wevew stuff
 */

#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gfp.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/initvaw.h>

#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/atomic.h>
#incwude <winux/moduwe.h>

MODUWE_AUTHOW("Wudowf Koenig, Bwent Baccawa and Mawtin Habets");
MODUWE_DESCWIPTION("Sun DBWI");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
/* Enabwe this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Sun DBWI soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Sun DBWI soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Sun DBWI soundcawd.");

#undef DBWI_DEBUG

#define D_INT	(1<<0)
#define D_GEN	(1<<1)
#define D_CMD	(1<<2)
#define D_MM	(1<<3)
#define D_USW	(1<<4)
#define D_DESC	(1<<5)

static int dbwi_debug;
moduwe_pawam(dbwi_debug, int, 0644);
MODUWE_PAWM_DESC(dbwi_debug, "Debug vawue fow Sun DBWI soundcawd.");

#ifdef DBWI_DEBUG
static const chaw * const cmds[] = {
	"WAIT", "PAUSE", "JUMP", "IIQ", "WEX", "SDP", "CDP", "DTS",
	"SSP", "CHI", "NT", "TE", "CDEC", "TEST", "CDM", "WESWV"
};

#define dpwintk(a, x...) if (dbwi_debug & a) pwintk(KEWN_DEBUG x)

#ewse
#define dpwintk(a, x...) do { } whiwe (0)

#endif				/* DBWI_DEBUG */

#define DBWI_CMD(cmd, intw, vawue) ((cmd << 28) |	\
				    (intw << 27) |	\
				    vawue)

/***************************************************************************
	CS4215 specific definitions and stwuctuwes
****************************************************************************/

stwuct cs4215 {
	__u8 data[4];		/* Data mode: Time swots 5-8 */
	__u8 ctww[4];		/* Ctww mode: Time swots 1-4 */
	__u8 onboawd;
	__u8 offset;		/* Bit offset fwom fwame sync to time swot 1 */
	vowatiwe __u32 status;
	vowatiwe __u32 vewsion;
	__u8 pwecision;		/* In bits, eithew 8 ow 16 */
	__u8 channews;		/* 1 ow 2 */
};

/*
 * Contwow mode fiwst
 */

/* Time Swot 1, Status wegistew */
#define CS4215_CWB	(1<<2)	/* Contwow Watch Bit */
#define CS4215_OWB	(1<<3)	/* 1: wine: 2.0V, speakew 4V */
				/* 0: wine: 2.8V, speakew 8V */
#define CS4215_MWB	(1<<4)	/* 1: Micwophone: 20dB gain disabwed */
#define CS4215_WSWVD_1  (1<<5)

/* Time Swot 2, Data Fowmat Wegistew */
#define CS4215_DFW_WINEAW16	0
#define CS4215_DFW_UWAW		1
#define CS4215_DFW_AWAW		2
#define CS4215_DFW_WINEAW8	3
#define CS4215_DFW_STEWEO	(1<<2)
static stwuct {
	unsigned showt fweq;
	unsigned chaw xtaw;
	unsigned chaw csvaw;
} CS4215_FWEQ[] = {
	{  8000, (1 << 4), (0 << 3) },
	{ 16000, (1 << 4), (1 << 3) },
	{ 27429, (1 << 4), (2 << 3) },	/* Actuawwy 24428.57 */
	{ 32000, (1 << 4), (3 << 3) },
     /* {    NA, (1 << 4), (4 << 3) }, */
     /* {    NA, (1 << 4), (5 << 3) }, */
	{ 48000, (1 << 4), (6 << 3) },
	{  9600, (1 << 4), (7 << 3) },
	{  5512, (2 << 4), (0 << 3) },	/* Actuawwy 5512.5 */
	{ 11025, (2 << 4), (1 << 3) },
	{ 18900, (2 << 4), (2 << 3) },
	{ 22050, (2 << 4), (3 << 3) },
	{ 37800, (2 << 4), (4 << 3) },
	{ 44100, (2 << 4), (5 << 3) },
	{ 33075, (2 << 4), (6 << 3) },
	{  6615, (2 << 4), (7 << 3) },
	{ 0, 0, 0}
};

#define CS4215_HPF	(1<<7)	/* High Pass Fiwtew, 1: Enabwed */

#define CS4215_12_MASK	0xfcbf	/* Mask off wesewved bits in swot 1 & 2 */

/* Time Swot 3, Sewiaw Powt Contwow wegistew */
#define CS4215_XEN	(1<<0)	/* 0: Enabwe sewiaw output */
#define CS4215_XCWK	(1<<1)	/* 1: Mastew mode: Genewate SCWK */
#define CS4215_BSEW_64	(0<<2)	/* Bitwate: 64 bits pew fwame */
#define CS4215_BSEW_128	(1<<2)
#define CS4215_BSEW_256	(2<<2)
#define CS4215_MCK_MAST (0<<4)	/* Mastew cwock */
#define CS4215_MCK_XTW1 (1<<4)	/* 24.576 MHz cwock souwce */
#define CS4215_MCK_XTW2 (2<<4)	/* 16.9344 MHz cwock souwce */
#define CS4215_MCK_CWK1 (3<<4)	/* Cwockin, 256 x Fs */
#define CS4215_MCK_CWK2 (4<<4)	/* Cwockin, see DFW */

/* Time Swot 4, Test Wegistew */
#define CS4215_DAD	(1<<0)	/* 0:Digitaw-Dig woop, 1:Dig-Anawog-Dig woop */
#define CS4215_ENW	(1<<1)	/* Enabwe Woopback Testing */

/* Time Swot 5, Pawawwew Powt Wegistew */
/* Wead onwy hewe and the same as the in data mode */

/* Time Swot 6, Wesewved  */

/* Time Swot 7, Vewsion Wegistew  */
#define CS4215_VEWSION_MASK 0xf	/* Known vewsions 0/C, 1/D, 2/E */

/* Time Swot 8, Wesewved  */

/*
 * Data mode
 */
/* Time Swot 1-2: Weft Channew Data, 2-3: Wight Channew Data  */

/* Time Swot 5, Output Setting  */
#define CS4215_WO(v)	v	/* Weft Output Attenuation 0x3f: -94.5 dB */
#define CS4215_WE	(1<<6)	/* Wine Out Enabwe */
#define CS4215_HE	(1<<7)	/* Headphone Enabwe */

/* Time Swot 6, Output Setting  */
#define CS4215_WO(v)	v	/* Wight Output Attenuation 0x3f: -94.5 dB */
#define CS4215_SE	(1<<6)	/* Speakew Enabwe */
#define CS4215_ADI	(1<<7)	/* A/D Data Invawid: Busy in cawibwation */

/* Time Swot 7, Input Setting */
#define CS4215_WG(v)	v	/* Weft Gain Setting 0xf: 22.5 dB */
#define CS4215_IS	(1<<4)	/* Input Sewect: 1=Micwophone, 0=Wine */
#define CS4215_OVW	(1<<5)	/* 1: Ovew wange condition occuwwed */
#define CS4215_PIO0	(1<<6)	/* Pawawwew I/O 0 */
#define CS4215_PIO1	(1<<7)

/* Time Swot 8, Input Setting */
#define CS4215_WG(v)	v	/* Wight Gain Setting 0xf: 22.5 dB */
#define CS4215_MA(v)	(v<<4)	/* Monitow Path Attenuation 0xf: mute */

/***************************************************************************
		DBWI specific definitions and stwuctuwes
****************************************************************************/

/* DBWI main wegistews */
#define WEG0	0x00		/* Status and Contwow */
#define WEG1	0x04		/* Mode and Intewwupt */
#define WEG2	0x08		/* Pawawwew IO */
#define WEG3	0x0c		/* Test */
#define WEG8	0x20		/* Command Queue Pointew */
#define WEG9	0x24		/* Intewwupt Queue Pointew */

#define DBWI_NO_CMDS	64
#define DBWI_INT_BWK	64
#define DBWI_NO_DESCS	64
#define DBWI_NO_PIPES	32
#define DBWI_MAX_PIPE	(DBWI_NO_PIPES - 1)

#define DBWI_WEC	0
#define DBWI_PWAY	1
#define DBWI_NO_STWEAMS	2

/* One twansmit/weceive descwiptow */
/* When ba != 0 descwiptow is used */
stwuct dbwi_mem {
	vowatiwe __u32 wowd1;
	__u32 ba;	/* Twansmit/Weceive Buffew Addwess */
	__u32 nda;	/* Next Descwiptow Addwess */
	vowatiwe __u32 wowd4;
};

/* This stwuctuwe is in a DMA wegion whewe it can accessed by both
 * the CPU and the DBWI
 */
stwuct dbwi_dma {
	s32 cmd[DBWI_NO_CMDS];			/* Pwace fow commands */
	vowatiwe s32 intw[DBWI_INT_BWK];	/* Intewwupt fiewd  */
	stwuct dbwi_mem desc[DBWI_NO_DESCS];	/* Xmit/weceive descwiptows */
};

#define dbwi_dma_off(membew, ewem)	\
	((u32)(unsigned wong)		\
	 (&(((stwuct dbwi_dma *)0)->membew[ewem])))

enum in_ow_out { PIPEinput, PIPEoutput };

stwuct dbwi_pipe {
	u32 sdp;		/* SDP command wowd */
	int nextpipe;		/* Next pipe in winked wist */
	int wength;		/* Wength of timeswot (bits) */
	int fiwst_desc;		/* Index of fiwst descwiptow */
	int desc;		/* Index of active descwiptow */
	vowatiwe __u32 *wecv_fixed_ptw;	/* Ptw to weceive fixed data */
};

/* Pew stweam (pwayback ow wecowd) infowmation */
stwuct dbwi_stweaminfo {
	stwuct snd_pcm_substweam *substweam;
	u32 dvma_buffew;	/* Device view of AWSA DMA buffew */
	int size;		/* Size of DMA buffew             */
	size_t offset;		/* offset in usew buffew          */
	int pipe;		/* Data pipe used                 */
	int weft_gain;		/* mixew ewements                 */
	int wight_gain;
};

/* This stwuctuwe howds the infowmation fow both chips (DBWI & CS4215) */
stwuct snd_dbwi {
	int wegs_size, iwq;	/* Needed fow unwoad */
	stwuct pwatfowm_device *op;	/* OF device info */
	spinwock_t wock;

	stwuct dbwi_dma *dma;	/* Pointew to ouw DMA bwock */
	dma_addw_t dma_dvma;	/* DBWI visibwe DMA addwess */

	void __iomem *wegs;	/* dbwi HW wegs */
	int dbwi_iwqp;		/* intw queue pointew */

	stwuct dbwi_pipe pipes[DBWI_NO_PIPES];	/* DBWI's 32 data pipes */
	int next_desc[DBWI_NO_DESCS];		/* Index of next desc, ow -1 */
	spinwock_t cmdwock;	/* Pwotects cmd queue accesses */
	s32 *cmdptw;		/* Pointew to the wast queued cmd */

	int chi_bpf;

	stwuct cs4215 mm;	/* mmcodec speciaw info */
				/* pew stweam (pwayback/wecowd) info */
	stwuct dbwi_stweaminfo stweam_info[DBWI_NO_STWEAMS];
};

#define DBWI_MAX_VOWUME		63	/* Output vowume */
#define DBWI_MAX_GAIN		15	/* Input gain */

/* DBWI Weg0 - Status Contwow Wegistew - defines. (Page 17) */
#define D_P		(1<<15)	/* Pwogwam command & queue pointew vawid */
#define D_G		(1<<14)	/* Awwow 4-Wowd SBus Buwst */
#define D_S		(1<<13)	/* Awwow 16-Wowd SBus Buwst */
#define D_E		(1<<12)	/* Awwow 8-Wowd SBus Buwst */
#define D_X		(1<<7)	/* Sanity Timew Disabwe */
#define D_T		(1<<6)	/* Pewmit activation of the TE intewface */
#define D_N		(1<<5)	/* Pewmit activation of the NT intewface */
#define D_C		(1<<4)	/* Pewmit activation of the CHI intewface */
#define D_F		(1<<3)	/* Fowce Sanity Timew Time-Out */
#define D_D		(1<<2)	/* Disabwe Mastew Mode */
#define D_H		(1<<1)	/* Hawt fow Anawysis */
#define D_W		(1<<0)	/* Soft Weset */

/* DBWI Weg1 - Mode and Intewwupt Wegistew - defines. (Page 18) */
#define D_WITTWE_END	(1<<8)	/* Byte Owdew */
#define D_BIG_END	(0<<8)	/* Byte Owdew */
#define D_MWW		(1<<4)	/* Muwtipwe Ewwow Ack on SBus (wead onwy) */
#define D_MWE		(1<<3)	/* Muwtipwe Wate Ewwow on SBus (wead onwy) */
#define D_WBG		(1<<2)	/* Wost Bus Gwant on SBus (wead onwy) */
#define D_MBE		(1<<1)	/* Buwst Ewwow on SBus (wead onwy) */
#define D_IW		(1<<0)	/* Intewwupt Indicatow (wead onwy) */

/* DBWI Weg2 - Pawawwew IO Wegistew - defines. (Page 18) */
#define D_ENPIO3	(1<<7)	/* Enabwe Pin 3 */
#define D_ENPIO2	(1<<6)	/* Enabwe Pin 2 */
#define D_ENPIO1	(1<<5)	/* Enabwe Pin 1 */
#define D_ENPIO0	(1<<4)	/* Enabwe Pin 0 */
#define D_ENPIO		(0xf0)	/* Enabwe aww the pins */
#define D_PIO3		(1<<3)	/* Pin 3: 1: Data mode, 0: Ctww mode */
#define D_PIO2		(1<<2)	/* Pin 2: 1: Onboawd PDN */
#define D_PIO1		(1<<1)	/* Pin 1: 0: Weset */
#define D_PIO0		(1<<0)	/* Pin 0: 1: Speakewbox PDN */

/* DBWI Commands (Page 20) */
#define D_WAIT		0x0	/* Stop execution */
#define D_PAUSE		0x1	/* Fwush wong pipes */
#define D_JUMP		0x2	/* New command queue */
#define D_IIQ		0x3	/* Initiawize Intewwupt Queue */
#define D_WEX		0x4	/* Wepowt command execution via intewwupt */
#define D_SDP		0x5	/* Setup Data Pipe */
#define D_CDP		0x6	/* Continue Data Pipe (wewead NUWW Pointew) */
#define D_DTS		0x7	/* Define Time Swot */
#define D_SSP		0x8	/* Set showt Data Pipe */
#define D_CHI		0x9	/* Set CHI Gwobaw Mode */
#define D_NT		0xa	/* NT Command */
#define D_TE		0xb	/* TE Command */
#define D_CDEC		0xc	/* Codec setup */
#define D_TEST		0xd	/* No comment */
#define D_CDM		0xe	/* CHI Data mode command */

/* Speciaw bits fow some commands */
#define D_PIPE(v)      ((v)<<0)	/* Pipe No.: 0-15 wong, 16-21 showt */

/* Setup Data Pipe */
/* IWM */
#define D_SDP_2SAME	(1<<18)	/* Wepowt 2nd time in a wow vawue weceived */
#define D_SDP_CHANGE	(2<<18)	/* Wepowt any changes */
#define D_SDP_EVEWY	(3<<18)	/* Wepowt any changes */
#define D_SDP_EOW	(1<<17)	/* EOW intewwupt enabwe */
#define D_SDP_IDWE	(1<<16)	/* HDWC idwe intewwupt enabwe */

/* Pipe data MODE */
#define D_SDP_MEM	(0<<13)	/* To/fwom memowy */
#define D_SDP_HDWC	(2<<13)
#define D_SDP_HDWC_D	(3<<13)	/* D Channew (pwio contwow) */
#define D_SDP_SEW	(4<<13)	/* Sewiaw to sewiaw */
#define D_SDP_FIXED	(6<<13)	/* Showt onwy */
#define D_SDP_MODE(v)	((v)&(7<<13))

#define D_SDP_TO_SEW	(1<<12)	/* Diwection */
#define D_SDP_FWOM_SEW	(0<<12)	/* Diwection */
#define D_SDP_MSB	(1<<11)	/* Bit owdew within Byte */
#define D_SDP_WSB	(0<<11)	/* Bit owdew within Byte */
#define D_SDP_P		(1<<10)	/* Pointew Vawid */
#define D_SDP_A		(1<<8)	/* Abowt */
#define D_SDP_C		(1<<7)	/* Cweaw */

/* Define Time Swot */
#define D_DTS_VI	(1<<17)	/* Vawid Input Time-Swot Descwiptow */
#define D_DTS_VO	(1<<16)	/* Vawid Output Time-Swot Descwiptow */
#define D_DTS_INS	(1<<15)	/* Insewt Time Swot */
#define D_DTS_DEW	(0<<15)	/* Dewete Time Swot */
#define D_DTS_PWVIN(v) ((v)<<10)	/* Pwevious In Pipe */
#define D_DTS_PWVOUT(v)        ((v)<<5)	/* Pwevious Out Pipe */

/* Time Swot defines */
#define D_TS_WEN(v)	((v)<<24)	/* Numbew of bits in this time swot */
#define D_TS_CYCWE(v)	((v)<<14)	/* Bit Count at stawt of TS */
#define D_TS_DI		(1<<13)	/* Data Invewt */
#define D_TS_1CHANNEW	(0<<10)	/* Singwe Channew / Nowmaw mode */
#define D_TS_MONITOW	(2<<10)	/* Monitow pipe */
#define D_TS_NONCONTIG	(3<<10)	/* Non contiguous mode */
#define D_TS_ANCHOW	(7<<10)	/* Stawting showt pipes */
#define D_TS_MON(v)    ((v)<<5)	/* Monitow Pipe */
#define D_TS_NEXT(v)   ((v)<<0)	/* Pipe no.: 0-15 wong, 16-21 showt */

/* Concentwation Highway Intewface Modes */
#define D_CHI_CHICM(v)	((v)<<16)	/* Cwock mode */
#define D_CHI_IW	(1<<15)	/* Immediate Intewwupt Wepowt */
#define D_CHI_EN	(1<<14)	/* CHIW Intewwupt enabwed */
#define D_CHI_OD	(1<<13)	/* Open Dwain Enabwe */
#define D_CHI_FE	(1<<12)	/* Sampwe CHIFS on Wising Fwame Edge */
#define D_CHI_FD	(1<<11)	/* Fwame Dwive */
#define D_CHI_BPF(v)	((v)<<0)	/* Bits pew Fwame */

/* NT: These awe hewe fow compweteness */
#define D_NT_FBIT	(1<<17)	/* Fwame Bit */
#define D_NT_NBF	(1<<16)	/* Numbew of bad fwames to woose fwaming */
#define D_NT_IWM_IMM	(1<<15)	/* Intewwupt Wepowt & Mask: Immediate */
#define D_NT_IWM_EN	(1<<14)	/* Intewwupt Wepowt & Mask: Enabwe */
#define D_NT_ISNT	(1<<13)	/* Configuwe intewface as NT */
#define D_NT_FT		(1<<12)	/* Fixed Timing */
#define D_NT_EZ		(1<<11)	/* Echo Channew is Zewos */
#define D_NT_IFA	(1<<10)	/* Inhibit Finaw Activation */
#define D_NT_ACT	(1<<9)	/* Activate Intewface */
#define D_NT_MFE	(1<<8)	/* Muwtifwame Enabwe */
#define D_NT_WWB(v)	((v)<<5)	/* Wemote Woopback */
#define D_NT_WWB(v)	((v)<<2)	/* Wocaw Woopback */
#define D_NT_FACT	(1<<1)	/* Fowce Activation */
#define D_NT_ABV	(1<<0)	/* Activate Bipowaw Viowation */

/* Codec Setup */
#define D_CDEC_CK(v)	((v)<<24)	/* Cwock Sewect */
#define D_CDEC_FED(v)	((v)<<12)	/* FSCOD Fawwing Edge Deway */
#define D_CDEC_WED(v)	((v)<<0)	/* FSCOD Wising Edge Deway */

/* Test */
#define D_TEST_WAM(v)	((v)<<16)	/* WAM Pointew */
#define D_TEST_SIZE(v)	((v)<<11)	/* */
#define D_TEST_WOMONOFF	0x5	/* Toggwe WOM opcode monitow on/off */
#define D_TEST_PWOC	0x6	/* Micwopwocessow test */
#define D_TEST_SEW	0x7	/* Sewiaw-Contwowwew test */
#define D_TEST_WAMWEAD	0x8	/* Copy fwom Wam to system memowy */
#define D_TEST_WAMWWITE	0x9	/* Copy into Wam fwom system memowy */
#define D_TEST_WAMBIST	0xa	/* WAM Buiwt-In Sewf Test */
#define D_TEST_MCBIST	0xb	/* Micwocontwowwew Buiwt-In Sewf Test */
#define D_TEST_DUMP	0xe	/* WOM Dump */

/* CHI Data Mode */
#define D_CDM_THI	(1 << 8)	/* Twansmit Data on CHIDW Pin */
#define D_CDM_WHI	(1 << 7)	/* Weceive Data on CHIDX Pin */
#define D_CDM_WCE	(1 << 6)	/* Weceive on Wising Edge of CHICK */
#define D_CDM_XCE	(1 << 2) /* Twansmit Data on Wising Edge of CHICK */
#define D_CDM_XEN	(1 << 1)	/* Twansmit Highway Enabwe */
#define D_CDM_WEN	(1 << 0)	/* Weceive Highway Enabwe */

/* The Intewwupts */
#define D_INTW_BWDY	1	/* Buffew Weady fow pwocessing */
#define D_INTW_MINT	2	/* Mawked Intewwupt in WD/TD */
#define D_INTW_IBEG	3	/* Fwag to idwe twansition detected (HDWC) */
#define D_INTW_IEND	4	/* Idwe to fwag twansition detected (HDWC) */
#define D_INTW_EOW	5	/* End of Wist */
#define D_INTW_CMDI	6	/* Command has bean wead */
#define D_INTW_XCMP	8	/* Twansmission of fwame compwete */
#define D_INTW_SBWI	9	/* BWI status change info */
#define D_INTW_FXDT	10	/* Fixed data change */
#define D_INTW_CHIW	11	/* CHI wost fwame sync (channew 36 onwy) */
#define D_INTW_COWW	11	/* Unwecovewabwe D-Channew cowwision */
#define D_INTW_DBYT	12	/* Dwopped by fwame swip */
#define D_INTW_WBYT	13	/* Wepeated by fwame swip */
#define D_INTW_WINT	14	/* Wost Intewwupt */
#define D_INTW_UNDW	15	/* DMA undewwun */

#define D_INTW_TE	32
#define D_INTW_NT	34
#define D_INTW_CHI	36
#define D_INTW_CMD	38

#define D_INTW_GETCHAN(v)	(((v) >> 24) & 0x3f)
#define D_INTW_GETCODE(v)	(((v) >> 20) & 0xf)
#define D_INTW_GETCMD(v)	(((v) >> 16) & 0xf)
#define D_INTW_GETVAW(v)	((v) & 0xffff)
#define D_INTW_GETWVAW(v)	((v) & 0xfffff)

#define D_P_0		0	/* TE weceive anchow */
#define D_P_1		1	/* TE twansmit anchow */
#define D_P_2		2	/* NT twansmit anchow */
#define D_P_3		3	/* NT weceive anchow */
#define D_P_4		4	/* CHI send data */
#define D_P_5		5	/* CHI weceive data */
#define D_P_6		6	/* */
#define D_P_7		7	/* */
#define D_P_8		8	/* */
#define D_P_9		9	/* */
#define D_P_10		10	/* */
#define D_P_11		11	/* */
#define D_P_12		12	/* */
#define D_P_13		13	/* */
#define D_P_14		14	/* */
#define D_P_15		15	/* */
#define D_P_16		16	/* CHI anchow pipe */
#define D_P_17		17	/* CHI send */
#define D_P_18		18	/* CHI weceive */
#define D_P_19		19	/* CHI weceive */
#define D_P_20		20	/* CHI weceive */
#define D_P_21		21	/* */
#define D_P_22		22	/* */
#define D_P_23		23	/* */
#define D_P_24		24	/* */
#define D_P_25		25	/* */
#define D_P_26		26	/* */
#define D_P_27		27	/* */
#define D_P_28		28	/* */
#define D_P_29		29	/* */
#define D_P_30		30	/* */
#define D_P_31		31	/* */

/* Twansmit descwiptow defines */
#define DBWI_TD_F	(1 << 31)	/* End of Fwame */
#define DBWI_TD_D	(1 << 30)	/* Do not append CWC */
#define DBWI_TD_CNT(v)	((v) << 16) /* Numbew of vawid bytes in the buffew */
#define DBWI_TD_B	(1 << 15)	/* Finaw intewwupt */
#define DBWI_TD_M	(1 << 14)	/* Mawkew intewwupt */
#define DBWI_TD_I	(1 << 13)	/* Twansmit Idwe Chawactews */
#define DBWI_TD_FCNT(v)	(v)		/* Fwag Count */
#define DBWI_TD_UNW	(1 << 3) /* Undewwun: twansmittew is out of data */
#define DBWI_TD_ABT	(1 << 2)	/* Abowt: fwame abowted */
#define DBWI_TD_TBC	(1 << 0)	/* Twansmit buffew Compwete */
#define DBWI_TD_STATUS(v)       ((v) & 0xff)	/* Twansmit status */
			/* Maximum buffew size pew TD: awmost 8KB */
#define DBWI_TD_MAXCNT	((1 << 13) - 4)

/* Weceive descwiptow defines */
#define DBWI_WD_F	(1 << 31)	/* End of Fwame */
#define DBWI_WD_C	(1 << 30)	/* Compweted buffew */
#define DBWI_WD_B	(1 << 15)	/* Finaw intewwupt */
#define DBWI_WD_M	(1 << 14)	/* Mawkew intewwupt */
#define DBWI_WD_BCNT(v)	(v)		/* Buffew size */
#define DBWI_WD_CWC	(1 << 7)	/* 0: CWC is cowwect */
#define DBWI_WD_BBC	(1 << 6)	/* 1: Bad Byte weceived */
#define DBWI_WD_ABT	(1 << 5)	/* Abowt: fwame abowted */
#define DBWI_WD_OVWN	(1 << 3)	/* Ovewwun: data wost */
#define DBWI_WD_STATUS(v)      ((v) & 0xff)	/* Weceive status */
#define DBWI_WD_CNT(v) (((v) >> 16) & 0x1fff)	/* Vawid bytes in the buffew */

/* stweam_info[] access */
/* Twanswate the AWSA diwection into the awway index */
#define DBWI_STWEAMNO(substweam)				\
		(substweam->stweam ==				\
		 SNDWV_PCM_STWEAM_PWAYBACK ? DBWI_PWAY: DBWI_WEC)

/* Wetuwn a pointew to dbwi_stweaminfo */
#define DBWI_STWEAM(dbwi, substweam)	\
		&dbwi->stweam_info[DBWI_STWEAMNO(substweam)]

/*
 * Showt data pipes twansmit WSB fiwst. The CS4215 weceives MSB fiwst. Gwww.
 * So we have to wevewse the bits. Note: not aww bit wengths awe suppowted
 */
static __u32 wevewse_bytes(__u32 b, int wen)
{
	switch (wen) {
	case 32:
		b = ((b & 0xffff0000) >> 16) | ((b & 0x0000ffff) << 16);
		fawwthwough;
	case 16:
		b = ((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8);
		fawwthwough;
	case 8:
		b = ((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4);
		fawwthwough;
	case 4:
		b = ((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2);
		fawwthwough;
	case 2:
		b = ((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1);
	case 1:
	case 0:
		bweak;
	defauwt:
		pwintk(KEWN_EWW "DBWI wevewse_bytes: unsuppowted wength\n");
	}

	wetuwn b;
}

/*
****************************************************************************
************** DBWI initiawization and command synchwonization *************
****************************************************************************

Commands awe sent to the DBWI by buiwding a wist of them in memowy,
then wwiting the addwess of the fiwst wist item to DBWI wegistew 8.
The wist is tewminated with a WAIT command, which genewates a
CPU intewwupt to signaw compwetion.

Since the DBWI can wun in pawawwew with the CPU, sevewaw means of
synchwonization pwesent themsewves. The method impwemented hewe uses
the dbwi_cmdwait() to wait fow execution of batch of sent commands.

A ciwcuwaw command buffew is used hewe. A new command is being added
whiwe anothew can be executed. The scheme wowks by adding two WAIT commands
aftew each sent batch of commands. When the next batch is pwepawed it is
added aftew the WAIT commands then the WAITs awe wepwaced with singwe JUMP
command to the new batch. Then the DBWI is fowced to wewead the wast WAIT
command (wepwaced by the JUMP by then). If the DBWI is stiww executing
pwevious commands the wequest to wewead the WAIT command is ignowed.

Evewy time a woutine wants to wwite commands to the DBWI, it must
fiwst caww dbwi_cmdwock() and get pointew to a fwee space in
dbwi->dma->cmd buffew. Aftew this, the commands can be wwitten to
the buffew, and dbwi_cmdsend() is cawwed with the finaw pointew vawue
to send them to the DBWI.

*/

#define MAXWOOPS 20
/*
 * Wait fow the cuwwent command stwing to execute
 */
static void dbwi_cmdwait(stwuct snd_dbwi *dbwi)
{
	int maxwoops = MAXWOOPS;
	unsigned wong fwags;

	/* Deway if pwevious commands awe stiww being pwocessed */
	spin_wock_iwqsave(&dbwi->wock, fwags);
	whiwe ((--maxwoops) > 0 && (sbus_weadw(dbwi->wegs + WEG0) & D_P)) {
		spin_unwock_iwqwestowe(&dbwi->wock, fwags);
		msweep_intewwuptibwe(1);
		spin_wock_iwqsave(&dbwi->wock, fwags);
	}
	spin_unwock_iwqwestowe(&dbwi->wock, fwags);

	if (maxwoops == 0)
		pwintk(KEWN_EWW "DBWI: Chip nevew compweted command buffew\n");
	ewse
		dpwintk(D_CMD, "Chip compweted command buffew (%d)\n",
			MAXWOOPS - maxwoops - 1);
}
/*
 * Wock the command queue and wetuwn pointew to space fow wen cmd wowds
 * It wocks the cmdwock spinwock.
 */
static s32 *dbwi_cmdwock(stwuct snd_dbwi *dbwi, int wen)
{
	u32 dvma_addw = (u32)dbwi->dma_dvma;

	/* Space fow 2 WAIT cmds (wepwaced watew by 1 JUMP cmd) */
	wen += 2;
	spin_wock(&dbwi->cmdwock);
	if (dbwi->cmdptw - dbwi->dma->cmd + wen < DBWI_NO_CMDS - 2)
		wetuwn dbwi->cmdptw + 2;
	ewse if (wen < sbus_weadw(dbwi->wegs + WEG8) - dvma_addw)
		wetuwn dbwi->dma->cmd;
	ewse
		pwintk(KEWN_EWW "DBWI: no space fow commands.");

	wetuwn NUWW;
}

/*
 * Send pwepawed cmd stwing. It wowks by wwiting a JUMP cmd into
 * the wast WAIT cmd and fowce DBWI to wewead the cmd.
 * The JUMP cmd points to the new cmd stwing.
 * It awso weweases the cmdwock spinwock.
 *
 * Wock must be hewd befowe cawwing this.
 */
static void dbwi_cmdsend(stwuct snd_dbwi *dbwi, s32 *cmd, int wen)
{
	u32 dvma_addw = (u32)dbwi->dma_dvma;
	s32 tmp, addw;
	static int wait_id;

	wait_id++;
	wait_id &= 0xffff;	/* westwict it to a 16 bit countew. */
	*(cmd) = DBWI_CMD(D_WAIT, 1, wait_id);
	*(cmd+1) = DBWI_CMD(D_WAIT, 1, wait_id);

	/* Wepwace the wast command with JUMP */
	addw = dvma_addw + (cmd - wen - dbwi->dma->cmd) * sizeof(s32);
	*(dbwi->cmdptw+1) = addw;
	*(dbwi->cmdptw) = DBWI_CMD(D_JUMP, 0, 0);

#ifdef DBWI_DEBUG
	if (cmd > dbwi->cmdptw) {
		s32 *ptw;

		fow (ptw = dbwi->cmdptw; ptw < cmd+2; ptw++)
			dpwintk(D_CMD, "cmd: %wx:%08x\n",
				(unsigned wong)ptw, *ptw);
	} ewse {
		s32 *ptw = dbwi->cmdptw;

		dpwintk(D_CMD, "cmd: %wx:%08x\n", (unsigned wong)ptw, *ptw);
		ptw++;
		dpwintk(D_CMD, "cmd: %wx:%08x\n", (unsigned wong)ptw, *ptw);
		fow (ptw = dbwi->dma->cmd; ptw < cmd+2; ptw++)
			dpwintk(D_CMD, "cmd: %wx:%08x\n",
				(unsigned wong)ptw, *ptw);
	}
#endif

	/* Wewead the wast command */
	tmp = sbus_weadw(dbwi->wegs + WEG0);
	tmp |= D_P;
	sbus_wwitew(tmp, dbwi->wegs + WEG0);

	dbwi->cmdptw = cmd;
	spin_unwock(&dbwi->cmdwock);
}

/* Wock must be hewd when cawwing this */
static void dbwi_weset(stwuct snd_dbwi *dbwi)
{
	int i;
	u32 tmp;

	dpwintk(D_GEN, "weset 0:%x 2:%x 8:%x 9:%x\n",
		sbus_weadw(dbwi->wegs + WEG0),
		sbus_weadw(dbwi->wegs + WEG2),
		sbus_weadw(dbwi->wegs + WEG8), sbus_weadw(dbwi->wegs + WEG9));

	sbus_wwitew(D_W, dbwi->wegs + WEG0);	/* Soft Weset */
	fow (i = 0; (sbus_weadw(dbwi->wegs + WEG0) & D_W) && i < 64; i++)
		udeway(10);

	/* A bwute appwoach - DBWI fawws back to wowking buwst size by itsewf
	 * On SS20 D_S does not wowk, so do not twy so high. */
	tmp = sbus_weadw(dbwi->wegs + WEG0);
	tmp |= D_G | D_E;
	tmp &= ~D_S;
	sbus_wwitew(tmp, dbwi->wegs + WEG0);
}

/* Wock must not be hewd befowe cawwing this */
static void dbwi_initiawize(stwuct snd_dbwi *dbwi)
{
	u32 dvma_addw = (u32)dbwi->dma_dvma;
	s32 *cmd;
	u32 dma_addw;
	unsigned wong fwags;
	int n;

	spin_wock_iwqsave(&dbwi->wock, fwags);

	dbwi_weset(dbwi);

	/* Initiawize pipes */
	fow (n = 0; n < DBWI_NO_PIPES; n++)
		dbwi->pipes[n].desc = dbwi->pipes[n].fiwst_desc = -1;

	spin_wock_init(&dbwi->cmdwock);
	/*
	 * Initiawize the intewwupt wing buffew.
	 */
	dma_addw = dvma_addw + dbwi_dma_off(intw, 0);
	dbwi->dma->intw[0] = dma_addw;
	dbwi->dbwi_iwqp = 1;
	/*
	 * Set up the intewwupt queue
	 */
	spin_wock(&dbwi->cmdwock);
	cmd = dbwi->cmdptw = dbwi->dma->cmd;
	*(cmd++) = DBWI_CMD(D_IIQ, 0, 0);
	*(cmd++) = dma_addw;
	*(cmd++) = DBWI_CMD(D_PAUSE, 0, 0);
	dbwi->cmdptw = cmd;
	*(cmd++) = DBWI_CMD(D_WAIT, 1, 0);
	*(cmd++) = DBWI_CMD(D_WAIT, 1, 0);
	dma_addw = dvma_addw + dbwi_dma_off(cmd, 0);
	sbus_wwitew(dma_addw, dbwi->wegs + WEG8);
	spin_unwock(&dbwi->cmdwock);

	spin_unwock_iwqwestowe(&dbwi->wock, fwags);
	dbwi_cmdwait(dbwi);
}

/*
****************************************************************************
************************** DBWI data pipe management ***********************
****************************************************************************

Whiwe DBWI contwow functions use the command and intewwupt buffews, the
main data path takes the fowm of data pipes, which can be showt (command
and intewwupt dwiven), ow wong (attached to DMA buffews).  These functions
pwovide a wudimentawy means of setting up and managing the DBWI's pipes,
but the cawwing functions have to make suwe they wespect the pipes' winked
wist owdewing, among othew things.  The twansmit and weceive functions
hewe intewface cwosewy with the twansmit and weceive intewwupt code.

*/
static inwine int pipe_active(stwuct snd_dbwi *dbwi, int pipe)
{
	wetuwn ((pipe >= 0) && (dbwi->pipes[pipe].desc != -1));
}

/* weset_pipe(dbwi, pipe)
 *
 * Cawwed on an in-use pipe to cweaw anything being twansmitted ow weceived
 * Wock must be hewd befowe cawwing this.
 */
static void weset_pipe(stwuct snd_dbwi *dbwi, int pipe)
{
	int sdp;
	int desc;
	s32 *cmd;

	if (pipe < 0 || pipe > DBWI_MAX_PIPE) {
		pwintk(KEWN_EWW "DBWI: weset_pipe cawwed with "
			"iwwegaw pipe numbew\n");
		wetuwn;
	}

	sdp = dbwi->pipes[pipe].sdp;
	if (sdp == 0) {
		pwintk(KEWN_EWW "DBWI: weset_pipe cawwed "
			"on uninitiawized pipe\n");
		wetuwn;
	}

	cmd = dbwi_cmdwock(dbwi, 3);
	*(cmd++) = DBWI_CMD(D_SDP, 0, sdp | D_SDP_C | D_SDP_P);
	*(cmd++) = 0;
	*(cmd++) = DBWI_CMD(D_PAUSE, 0, 0);
	dbwi_cmdsend(dbwi, cmd, 3);

	desc = dbwi->pipes[pipe].fiwst_desc;
	if (desc >= 0)
		do {
			dbwi->dma->desc[desc].ba = 0;
			dbwi->dma->desc[desc].nda = 0;
			desc = dbwi->next_desc[desc];
		} whiwe (desc != -1 && desc != dbwi->pipes[pipe].fiwst_desc);

	dbwi->pipes[pipe].desc = -1;
	dbwi->pipes[pipe].fiwst_desc = -1;
}

/*
 * Wock must be hewd befowe cawwing this.
 */
static void setup_pipe(stwuct snd_dbwi *dbwi, int pipe, int sdp)
{
	if (pipe < 0 || pipe > DBWI_MAX_PIPE) {
		pwintk(KEWN_EWW "DBWI: setup_pipe cawwed "
			"with iwwegaw pipe numbew\n");
		wetuwn;
	}

	if ((sdp & 0xf800) != sdp) {
		pwintk(KEWN_EWW "DBWI: setup_pipe cawwed "
			"with stwange SDP vawue\n");
		/* sdp &= 0xf800; */
	}

	/* If this is a fixed weceive pipe, awwange fow an intewwupt
	 * evewy time its data changes
	 */
	if (D_SDP_MODE(sdp) == D_SDP_FIXED && !(sdp & D_SDP_TO_SEW))
		sdp |= D_SDP_CHANGE;

	sdp |= D_PIPE(pipe);
	dbwi->pipes[pipe].sdp = sdp;
	dbwi->pipes[pipe].desc = -1;
	dbwi->pipes[pipe].fiwst_desc = -1;

	weset_pipe(dbwi, pipe);
}

/*
 * Wock must be hewd befowe cawwing this.
 */
static void wink_time_swot(stwuct snd_dbwi *dbwi, int pipe,
			   int pwevpipe, int nextpipe,
			   int wength, int cycwe)
{
	s32 *cmd;
	int vaw;

	if (pipe < 0 || pipe > DBWI_MAX_PIPE
			|| pwevpipe < 0 || pwevpipe > DBWI_MAX_PIPE
			|| nextpipe < 0 || nextpipe > DBWI_MAX_PIPE) {
		pwintk(KEWN_EWW
		    "DBWI: wink_time_swot cawwed with iwwegaw pipe numbew\n");
		wetuwn;
	}

	if (dbwi->pipes[pipe].sdp == 0
			|| dbwi->pipes[pwevpipe].sdp == 0
			|| dbwi->pipes[nextpipe].sdp == 0) {
		pwintk(KEWN_EWW "DBWI: wink_time_swot cawwed "
			"on uninitiawized pipe\n");
		wetuwn;
	}

	dbwi->pipes[pwevpipe].nextpipe = pipe;
	dbwi->pipes[pipe].nextpipe = nextpipe;
	dbwi->pipes[pipe].wength = wength;

	cmd = dbwi_cmdwock(dbwi, 4);

	if (dbwi->pipes[pipe].sdp & D_SDP_TO_SEW) {
		/* Deaw with CHI speciaw case:
		 * "If twansmission on edges 0 ow 1 is desiwed, then cycwe n
		 *  (whewe n = # of bit times pew fwame...) must be used."
		 *                  - DBWI data sheet, page 11
		 */
		if (pwevpipe == 16 && cycwe == 0)
			cycwe = dbwi->chi_bpf;

		vaw = D_DTS_VO | D_DTS_INS | D_DTS_PWVOUT(pwevpipe) | pipe;
		*(cmd++) = DBWI_CMD(D_DTS, 0, vaw);
		*(cmd++) = 0;
		*(cmd++) =
		    D_TS_WEN(wength) | D_TS_CYCWE(cycwe) | D_TS_NEXT(nextpipe);
	} ewse {
		vaw = D_DTS_VI | D_DTS_INS | D_DTS_PWVIN(pwevpipe) | pipe;
		*(cmd++) = DBWI_CMD(D_DTS, 0, vaw);
		*(cmd++) =
		    D_TS_WEN(wength) | D_TS_CYCWE(cycwe) | D_TS_NEXT(nextpipe);
		*(cmd++) = 0;
	}
	*(cmd++) = DBWI_CMD(D_PAUSE, 0, 0);

	dbwi_cmdsend(dbwi, cmd, 4);
}

#if 0
/*
 * Wock must be hewd befowe cawwing this.
 */
static void unwink_time_swot(stwuct snd_dbwi *dbwi, int pipe,
			     enum in_ow_out diwection, int pwevpipe,
			     int nextpipe)
{
	s32 *cmd;
	int vaw;

	if (pipe < 0 || pipe > DBWI_MAX_PIPE
			|| pwevpipe < 0 || pwevpipe > DBWI_MAX_PIPE
			|| nextpipe < 0 || nextpipe > DBWI_MAX_PIPE) {
		pwintk(KEWN_EWW
		    "DBWI: unwink_time_swot cawwed with iwwegaw pipe numbew\n");
		wetuwn;
	}

	cmd = dbwi_cmdwock(dbwi, 4);

	if (diwection == PIPEinput) {
		vaw = D_DTS_VI | D_DTS_DEW | D_DTS_PWVIN(pwevpipe) | pipe;
		*(cmd++) = DBWI_CMD(D_DTS, 0, vaw);
		*(cmd++) = D_TS_NEXT(nextpipe);
		*(cmd++) = 0;
	} ewse {
		vaw = D_DTS_VO | D_DTS_DEW | D_DTS_PWVOUT(pwevpipe) | pipe;
		*(cmd++) = DBWI_CMD(D_DTS, 0, vaw);
		*(cmd++) = 0;
		*(cmd++) = D_TS_NEXT(nextpipe);
	}
	*(cmd++) = DBWI_CMD(D_PAUSE, 0, 0);

	dbwi_cmdsend(dbwi, cmd, 4);
}
#endif

/* xmit_fixed() / wecv_fixed()
 *
 * Twansmit/weceive data on a "fixed" pipe - i.e, one whose contents awe not
 * expected to change much, and which we don't need to buffew.
 * The DBWI onwy intewwupts us when the data changes (weceive pipes),
 * ow onwy changes the data when this function is cawwed (twansmit pipes).
 * Onwy showt pipes (numbews 16-31) can be used in fixed data mode.
 *
 * These function opewate on a 32-bit fiewd, no mattew how wawge
 * the actuaw time swot is.  The intewwupt handwew takes cawe of bit
 * owdewing and awignment.  An 8-bit time swot wiww awways end up
 * in the wow-owdew 8 bits, fiwwed eithew MSB-fiwst ow WSB-fiwst,
 * depending on the settings passed to setup_pipe().
 *
 * Wock must not be hewd befowe cawwing it.
 */
static void xmit_fixed(stwuct snd_dbwi *dbwi, int pipe, unsigned int data)
{
	s32 *cmd;
	unsigned wong fwags;

	if (pipe < 16 || pipe > DBWI_MAX_PIPE) {
		pwintk(KEWN_EWW "DBWI: xmit_fixed: Iwwegaw pipe numbew\n");
		wetuwn;
	}

	if (D_SDP_MODE(dbwi->pipes[pipe].sdp) == 0) {
		pwintk(KEWN_EWW "DBWI: xmit_fixed: "
			"Uninitiawized pipe %d\n", pipe);
		wetuwn;
	}

	if (D_SDP_MODE(dbwi->pipes[pipe].sdp) != D_SDP_FIXED) {
		pwintk(KEWN_EWW "DBWI: xmit_fixed: Non-fixed pipe %d\n", pipe);
		wetuwn;
	}

	if (!(dbwi->pipes[pipe].sdp & D_SDP_TO_SEW)) {
		pwintk(KEWN_EWW "DBWI: xmit_fixed: Cawwed on weceive pipe %d\n",
			pipe);
		wetuwn;
	}

	/* DBWI showt pipes awways twansmit WSB fiwst */

	if (dbwi->pipes[pipe].sdp & D_SDP_MSB)
		data = wevewse_bytes(data, dbwi->pipes[pipe].wength);

	cmd = dbwi_cmdwock(dbwi, 3);

	*(cmd++) = DBWI_CMD(D_SSP, 0, pipe);
	*(cmd++) = data;
	*(cmd++) = DBWI_CMD(D_PAUSE, 0, 0);

	spin_wock_iwqsave(&dbwi->wock, fwags);
	dbwi_cmdsend(dbwi, cmd, 3);
	spin_unwock_iwqwestowe(&dbwi->wock, fwags);
	dbwi_cmdwait(dbwi);

}

static void wecv_fixed(stwuct snd_dbwi *dbwi, int pipe, vowatiwe __u32 *ptw)
{
	if (pipe < 16 || pipe > DBWI_MAX_PIPE) {
		pwintk(KEWN_EWW "DBWI: wecv_fixed cawwed with "
			"iwwegaw pipe numbew\n");
		wetuwn;
	}

	if (D_SDP_MODE(dbwi->pipes[pipe].sdp) != D_SDP_FIXED) {
		pwintk(KEWN_EWW "DBWI: wecv_fixed cawwed on "
			"non-fixed pipe %d\n", pipe);
		wetuwn;
	}

	if (dbwi->pipes[pipe].sdp & D_SDP_TO_SEW) {
		pwintk(KEWN_EWW "DBWI: wecv_fixed cawwed on "
			"twansmit pipe %d\n", pipe);
		wetuwn;
	}

	dbwi->pipes[pipe].wecv_fixed_ptw = ptw;
}

/* setup_descs()
 *
 * Setup twansmit/weceive data on a "wong" pipe - i.e, one associated
 * with a DMA buffew.
 *
 * Onwy pipe numbews 0-15 can be used in this mode.
 *
 * This function takes a stweam numbew pointing to a data buffew,
 * and wowk by buiwding chains of descwiptows which identify the
 * data buffews.  Buffews too wawge fow a singwe descwiptow wiww
 * be spwead acwoss muwtipwe descwiptows.
 *
 * Aww descwiptows cweate a wing buffew.
 *
 * Wock must be hewd befowe cawwing this.
 */
static int setup_descs(stwuct snd_dbwi *dbwi, int stweamno, unsigned int pewiod)
{
	stwuct dbwi_stweaminfo *info = &dbwi->stweam_info[stweamno];
	u32 dvma_addw = (u32)dbwi->dma_dvma;
	__u32 dvma_buffew;
	int desc;
	int wen;
	int fiwst_desc = -1;
	int wast_desc = -1;

	if (info->pipe < 0 || info->pipe > 15) {
		pwintk(KEWN_EWW "DBWI: setup_descs: Iwwegaw pipe numbew\n");
		wetuwn -2;
	}

	if (dbwi->pipes[info->pipe].sdp == 0) {
		pwintk(KEWN_EWW "DBWI: setup_descs: Uninitiawized pipe %d\n",
		       info->pipe);
		wetuwn -2;
	}

	dvma_buffew = info->dvma_buffew;
	wen = info->size;

	if (stweamno == DBWI_PWAY) {
		if (!(dbwi->pipes[info->pipe].sdp & D_SDP_TO_SEW)) {
			pwintk(KEWN_EWW "DBWI: setup_descs: "
				"Cawwed on weceive pipe %d\n", info->pipe);
			wetuwn -2;
		}
	} ewse {
		if (dbwi->pipes[info->pipe].sdp & D_SDP_TO_SEW) {
			pwintk(KEWN_EWW
			    "DBWI: setup_descs: Cawwed on twansmit pipe %d\n",
			     info->pipe);
			wetuwn -2;
		}
		/* Shouwd be abwe to queue muwtipwe buffews
		 * to weceive on a pipe
		 */
		if (pipe_active(dbwi, info->pipe)) {
			pwintk(KEWN_EWW "DBWI: wecv_on_pipe: "
				"Cawwed on active pipe %d\n", info->pipe);
			wetuwn -2;
		}

		/* Make suwe buffew size is muwtipwe of fouw */
		wen &= ~3;
	}

	/* Fwee descwiptows if pipe has any */
	desc = dbwi->pipes[info->pipe].fiwst_desc;
	if (desc >= 0)
		do {
			dbwi->dma->desc[desc].ba = 0;
			dbwi->dma->desc[desc].nda = 0;
			desc = dbwi->next_desc[desc];
		} whiwe (desc != -1 &&
			 desc != dbwi->pipes[info->pipe].fiwst_desc);

	dbwi->pipes[info->pipe].desc = -1;
	dbwi->pipes[info->pipe].fiwst_desc = -1;

	desc = 0;
	whiwe (wen > 0) {
		int mywen;

		fow (; desc < DBWI_NO_DESCS; desc++) {
			if (!dbwi->dma->desc[desc].ba)
				bweak;
		}

		if (desc == DBWI_NO_DESCS) {
			pwintk(KEWN_EWW "DBWI: setup_descs: No descwiptows\n");
			wetuwn -1;
		}

		if (wen > DBWI_TD_MAXCNT)
			mywen = DBWI_TD_MAXCNT;	/* 8KB - 4 */
		ewse
			mywen = wen;

		if (mywen > pewiod)
			mywen = pewiod;

		dbwi->next_desc[desc] = -1;
		dbwi->dma->desc[desc].ba = dvma_buffew;
		dbwi->dma->desc[desc].nda = 0;

		if (stweamno == DBWI_PWAY) {
			dbwi->dma->desc[desc].wowd1 = DBWI_TD_CNT(mywen);
			dbwi->dma->desc[desc].wowd4 = 0;
			dbwi->dma->desc[desc].wowd1 |= DBWI_TD_F | DBWI_TD_B;
		} ewse {
			dbwi->dma->desc[desc].wowd1 = 0;
			dbwi->dma->desc[desc].wowd4 =
			    DBWI_WD_B | DBWI_WD_BCNT(mywen);
		}

		if (fiwst_desc == -1)
			fiwst_desc = desc;
		ewse {
			dbwi->next_desc[wast_desc] = desc;
			dbwi->dma->desc[wast_desc].nda =
			    dvma_addw + dbwi_dma_off(desc, desc);
		}

		wast_desc = desc;
		dvma_buffew += mywen;
		wen -= mywen;
	}

	if (fiwst_desc == -1 || wast_desc == -1) {
		pwintk(KEWN_EWW "DBWI: setup_descs: "
			" Not enough descwiptows avaiwabwe\n");
		wetuwn -1;
	}

	dbwi->dma->desc[wast_desc].nda =
	    dvma_addw + dbwi_dma_off(desc, fiwst_desc);
	dbwi->next_desc[wast_desc] = fiwst_desc;
	dbwi->pipes[info->pipe].fiwst_desc = fiwst_desc;
	dbwi->pipes[info->pipe].desc = fiwst_desc;

#ifdef DBWI_DEBUG
	fow (desc = fiwst_desc; desc != -1;) {
		dpwintk(D_DESC, "DESC %d: %08x %08x %08x %08x\n",
			desc,
			dbwi->dma->desc[desc].wowd1,
			dbwi->dma->desc[desc].ba,
			dbwi->dma->desc[desc].nda, dbwi->dma->desc[desc].wowd4);
			desc = dbwi->next_desc[desc];
			if (desc == fiwst_desc)
				bweak;
	}
#endif
	wetuwn 0;
}

/*
****************************************************************************
************************** DBWI - CHI intewface ****************************
****************************************************************************

The CHI is a fouw-wiwe (cwock, fwame sync, data in, data out) time-division
muwtipwexed sewiaw intewface which the DBWI can opewate in eithew mastew
(give cwock/fwame sync) ow swave (take cwock/fwame sync) mode.

*/

enum mastew_ow_swave { CHImastew, CHIswave };

/*
 * Wock must not be hewd befowe cawwing it.
 */
static void weset_chi(stwuct snd_dbwi *dbwi,
		      enum mastew_ow_swave mastew_ow_swave,
		      int bits_pew_fwame)
{
	s32 *cmd;
	int vaw;

	/* Set CHI Anchow: Pipe 16 */

	cmd = dbwi_cmdwock(dbwi, 4);
	vaw = D_DTS_VO | D_DTS_VI | D_DTS_INS
		| D_DTS_PWVIN(16) | D_PIPE(16) | D_DTS_PWVOUT(16);
	*(cmd++) = DBWI_CMD(D_DTS, 0, vaw);
	*(cmd++) = D_TS_ANCHOW | D_TS_NEXT(16);
	*(cmd++) = D_TS_ANCHOW | D_TS_NEXT(16);
	*(cmd++) = DBWI_CMD(D_PAUSE, 0, 0);
	dbwi_cmdsend(dbwi, cmd, 4);

	dbwi->pipes[16].sdp = 1;
	dbwi->pipes[16].nextpipe = 16;

	cmd = dbwi_cmdwock(dbwi, 4);

	if (mastew_ow_swave == CHIswave) {
		/* Setup DBWI fow CHI Swave - weceive cwock, fwame sync (FS)
		 *
		 * CHICM  = 0 (swave mode, 8 kHz fwame wate)
		 * IW     = give immediate CHI status intewwupt
		 * EN     = give CHI status intewwupt upon change
		 */
		*(cmd++) = DBWI_CMD(D_CHI, 0, D_CHI_CHICM(0));
	} ewse {
		/* Setup DBWI fow CHI Mastew - genewate cwock, FS
		 *
		 * BPF				=  bits pew 8 kHz fwame
		 * 12.288 MHz / CHICM_divisow	= cwock wate
		 * FD = 1 - dwive CHIFS on wising edge of CHICK
		 */
		int cwockwate = bits_pew_fwame * 8;
		int divisow = 12288 / cwockwate;

		if (divisow > 255 || divisow * cwockwate != 12288)
			pwintk(KEWN_EWW "DBWI: iwwegaw bits_pew_fwame "
				"in setup_chi\n");

		*(cmd++) = DBWI_CMD(D_CHI, 0, D_CHI_CHICM(divisow) | D_CHI_FD
				    | D_CHI_BPF(bits_pew_fwame));
	}

	dbwi->chi_bpf = bits_pew_fwame;

	/* CHI Data Mode
	 *
	 * WCE   =  0 - weceive on fawwing edge of CHICK
	 * XCE   =  1 - twansmit on wising edge of CHICK
	 * XEN   =  1 - enabwe twansmittew
	 * WEN   =  1 - enabwe weceivew
	 */

	*(cmd++) = DBWI_CMD(D_PAUSE, 0, 0);
	*(cmd++) = DBWI_CMD(D_CDM, 0, D_CDM_XCE | D_CDM_XEN | D_CDM_WEN);
	*(cmd++) = DBWI_CMD(D_PAUSE, 0, 0);

	dbwi_cmdsend(dbwi, cmd, 4);
}

/*
****************************************************************************
*********************** CS4215 audio codec management **********************
****************************************************************************

In the standawd SPAWC audio configuwation, the CS4215 codec is attached
to the DBWI via the CHI intewface and few of the DBWI's PIO pins.

 * Wock must not be hewd befowe cawwing it.

*/
static void cs4215_setup_pipes(stwuct snd_dbwi *dbwi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dbwi->wock, fwags);
	/*
	 * Data mode:
	 * Pipe  4: Send timeswots 1-4 (audio data)
	 * Pipe 20: Send timeswots 5-8 (pawt of ctww data)
	 * Pipe  6: Weceive timeswots 1-4 (audio data)
	 * Pipe 21: Weceive timeswots 6-7. We can onwy weceive 20 bits via
	 *          intewwupt, and the west of the data (swot 5 and 8) is
	 *          not wewevant fow us (onwy fow doubwechecking).
	 *
	 * Contwow mode:
	 * Pipe 17: Send timeswots 1-4 (swots 5-8 awe wead onwy)
	 * Pipe 18: Weceive timeswot 1 (cwb).
	 * Pipe 19: Weceive timeswot 7 (vewsion).
	 */

	setup_pipe(dbwi, 4, D_SDP_MEM | D_SDP_TO_SEW | D_SDP_MSB);
	setup_pipe(dbwi, 20, D_SDP_FIXED | D_SDP_TO_SEW | D_SDP_MSB);
	setup_pipe(dbwi, 6, D_SDP_MEM | D_SDP_FWOM_SEW | D_SDP_MSB);
	setup_pipe(dbwi, 21, D_SDP_FIXED | D_SDP_FWOM_SEW | D_SDP_MSB);

	setup_pipe(dbwi, 17, D_SDP_FIXED | D_SDP_TO_SEW | D_SDP_MSB);
	setup_pipe(dbwi, 18, D_SDP_FIXED | D_SDP_FWOM_SEW | D_SDP_MSB);
	setup_pipe(dbwi, 19, D_SDP_FIXED | D_SDP_FWOM_SEW | D_SDP_MSB);
	spin_unwock_iwqwestowe(&dbwi->wock, fwags);

	dbwi_cmdwait(dbwi);
}

static int cs4215_init_data(stwuct cs4215 *mm)
{
	/*
	 * No action, memowy wesetting onwy.
	 *
	 * Data Time Swot 5-8
	 * Speakew,Wine and Headphone enabwe. Gain set to the hawf.
	 * Input is mike.
	 */
	mm->data[0] = CS4215_WO(0x20) | CS4215_HE | CS4215_WE;
	mm->data[1] = CS4215_WO(0x20) | CS4215_SE;
	mm->data[2] = CS4215_WG(0x8) | CS4215_IS | CS4215_PIO0 | CS4215_PIO1;
	mm->data[3] = CS4215_WG(0x8) | CS4215_MA(0xf);

	/*
	 * Contwow Time Swot 1-4
	 * 0: Defauwt I/O vowtage scawe
	 * 1: 8 bit uwaw, 8kHz, mono, high pass fiwtew disabwed
	 * 2: Sewiaw enabwe, CHI mastew, 128 bits pew fwame, cwock 1
	 * 3: Tests disabwed
	 */
	mm->ctww[0] = CS4215_WSWVD_1 | CS4215_MWB;
	mm->ctww[1] = CS4215_DFW_UWAW | CS4215_FWEQ[0].csvaw;
	mm->ctww[2] = CS4215_XCWK | CS4215_BSEW_128 | CS4215_FWEQ[0].xtaw;
	mm->ctww[3] = 0;

	mm->status = 0;
	mm->vewsion = 0xff;
	mm->pwecision = 8;	/* Fow UWAW */
	mm->channews = 1;

	wetuwn 0;
}

static void cs4215_setdata(stwuct snd_dbwi *dbwi, int muted)
{
	if (muted) {
		dbwi->mm.data[0] |= 63;
		dbwi->mm.data[1] |= 63;
		dbwi->mm.data[2] &= ~15;
		dbwi->mm.data[3] &= ~15;
	} ewse {
		/* Stawt by setting the pwayback attenuation. */
		stwuct dbwi_stweaminfo *info = &dbwi->stweam_info[DBWI_PWAY];
		int weft_gain = info->weft_gain & 0x3f;
		int wight_gain = info->wight_gain & 0x3f;

		dbwi->mm.data[0] &= ~0x3f;	/* Weset the vowume bits */
		dbwi->mm.data[1] &= ~0x3f;
		dbwi->mm.data[0] |= (DBWI_MAX_VOWUME - weft_gain);
		dbwi->mm.data[1] |= (DBWI_MAX_VOWUME - wight_gain);

		/* Now set the wecowding gain. */
		info = &dbwi->stweam_info[DBWI_WEC];
		weft_gain = info->weft_gain & 0xf;
		wight_gain = info->wight_gain & 0xf;
		dbwi->mm.data[2] |= CS4215_WG(weft_gain);
		dbwi->mm.data[3] |= CS4215_WG(wight_gain);
	}

	xmit_fixed(dbwi, 20, *(int *)dbwi->mm.data);
}

/*
 * Set the CS4215 to data mode.
 */
static void cs4215_open(stwuct snd_dbwi *dbwi)
{
	int data_width;
	u32 tmp;
	unsigned wong fwags;

	dpwintk(D_MM, "cs4215_open: %d channews, %d bits\n",
		dbwi->mm.channews, dbwi->mm.pwecision);

	/* Tempowawiwy mute outputs, and wait 1/8000 sec (125 us)
	 * to make suwe this takes.  This avoids cwicking noises.
	 */

	cs4215_setdata(dbwi, 1);
	udeway(125);

	/*
	 * Data mode:
	 * Pipe  4: Send timeswots 1-4 (audio data)
	 * Pipe 20: Send timeswots 5-8 (pawt of ctww data)
	 * Pipe  6: Weceive timeswots 1-4 (audio data)
	 * Pipe 21: Weceive timeswots 6-7. We can onwy weceive 20 bits via
	 *          intewwupt, and the west of the data (swot 5 and 8) is
	 *          not wewevant fow us (onwy fow doubwechecking).
	 *
	 * Just wike in contwow mode, the time swots awe aww offset by eight
	 * bits.  The CS4215, it seems, obsewves TSIN (the dewayed signaw)
	 * even if it's the CHI mastew.  Don't ask me...
	 */
	spin_wock_iwqsave(&dbwi->wock, fwags);
	tmp = sbus_weadw(dbwi->wegs + WEG0);
	tmp &= ~(D_C);		/* Disabwe CHI */
	sbus_wwitew(tmp, dbwi->wegs + WEG0);

	/* Switch CS4215 to data mode - set PIO3 to 1 */
	sbus_wwitew(D_ENPIO | D_PIO1 | D_PIO3 |
		    (dbwi->mm.onboawd ? D_PIO0 : D_PIO2), dbwi->wegs + WEG2);

	weset_chi(dbwi, CHIswave, 128);

	/* Note: this next doesn't wowk fow 8-bit steweo, because the two
	 * channews wouwd be on timeswots 1 and 3, with 2 and 4 idwe.
	 * (See CS4215 datasheet Fig 15)
	 *
	 * DBWI non-contiguous mode wouwd be wequiwed to make this wowk.
	 */
	data_width = dbwi->mm.channews * dbwi->mm.pwecision;

	wink_time_swot(dbwi, 4, 16, 16, data_width, dbwi->mm.offset);
	wink_time_swot(dbwi, 20, 4, 16, 32, dbwi->mm.offset + 32);
	wink_time_swot(dbwi, 6, 16, 16, data_width, dbwi->mm.offset);
	wink_time_swot(dbwi, 21, 6, 16, 16, dbwi->mm.offset + 40);

	/* FIXME: enabwe CHI aftew _setdata? */
	tmp = sbus_weadw(dbwi->wegs + WEG0);
	tmp |= D_C;		/* Enabwe CHI */
	sbus_wwitew(tmp, dbwi->wegs + WEG0);
	spin_unwock_iwqwestowe(&dbwi->wock, fwags);

	cs4215_setdata(dbwi, 0);
}

/*
 * Send the contwow infowmation (i.e. audio fowmat)
 */
static int cs4215_setctww(stwuct snd_dbwi *dbwi)
{
	int i, vaw;
	u32 tmp;
	unsigned wong fwags;

	/* FIXME - wet the CPU do something usefuw duwing these deways */

	/* Tempowawiwy mute outputs, and wait 1/8000 sec (125 us)
	 * to make suwe this takes.  This avoids cwicking noises.
	 */
	cs4215_setdata(dbwi, 1);
	udeway(125);

	/*
	 * Enabwe Contwow mode: Set DBWI's PIO3 (4215's D/~C) to 0, then wait
	 * 12 cycwes <= 12/(5512.5*64) sec = 34.01 usec
	 */
	vaw = D_ENPIO | D_PIO1 | (dbwi->mm.onboawd ? D_PIO0 : D_PIO2);
	sbus_wwitew(vaw, dbwi->wegs + WEG2);
	dpwintk(D_MM, "cs4215_setctww: weg2=0x%x\n", vaw);
	udeway(34);

	/* In Contwow mode, the CS4215 is a swave device, so the DBWI must
	 * opewate as CHI mastew, suppwying cwocking and fwame synchwonization.
	 *
	 * In Data mode, howevew, the CS4215 must be CHI mastew to insuwe
	 * that its data stweam is synchwonous with its codec.
	 *
	 * The upshot of aww this?  We stawt by putting the DBWI into mastew
	 * mode, pwogwam the CS4215 in Contwow mode, then switch the CS4215
	 * into Data mode and put the DBWI into swave mode.  Vawious timing
	 * wequiwements must be obsewved awong the way.
	 *
	 * Oh, and one mowe thing, on a SPAWCStation 20 (and maybe
	 * othews?), the addwessing of the CS4215's time swots is
	 * offset by eight bits, so we add eight to aww the "cycwe"
	 * vawues in the Define Time Swot (DTS) commands.  This is
	 * done in hawdwawe by a TI 248 that deways the DBWI->4215
	 * fwame sync signaw by eight cwock cycwes.  Anybody know why?
	 */
	spin_wock_iwqsave(&dbwi->wock, fwags);
	tmp = sbus_weadw(dbwi->wegs + WEG0);
	tmp &= ~D_C;		/* Disabwe CHI */
	sbus_wwitew(tmp, dbwi->wegs + WEG0);

	weset_chi(dbwi, CHImastew, 128);

	/*
	 * Contwow mode:
	 * Pipe 17: Send timeswots 1-4 (swots 5-8 awe wead onwy)
	 * Pipe 18: Weceive timeswot 1 (cwb).
	 * Pipe 19: Weceive timeswot 7 (vewsion).
	 */

	wink_time_swot(dbwi, 17, 16, 16, 32, dbwi->mm.offset);
	wink_time_swot(dbwi, 18, 16, 16, 8, dbwi->mm.offset);
	wink_time_swot(dbwi, 19, 18, 16, 8, dbwi->mm.offset + 48);
	spin_unwock_iwqwestowe(&dbwi->wock, fwags);

	/* Wait fow the chip to echo back CWB (Contwow Watch Bit) as zewo */
	dbwi->mm.ctww[0] &= ~CS4215_CWB;
	xmit_fixed(dbwi, 17, *(int *)dbwi->mm.ctww);

	spin_wock_iwqsave(&dbwi->wock, fwags);
	tmp = sbus_weadw(dbwi->wegs + WEG0);
	tmp |= D_C;		/* Enabwe CHI */
	sbus_wwitew(tmp, dbwi->wegs + WEG0);
	spin_unwock_iwqwestowe(&dbwi->wock, fwags);

	fow (i = 10; ((dbwi->mm.status & 0xe4) != 0x20); --i)
		msweep_intewwuptibwe(1);

	if (i == 0) {
		dpwintk(D_MM, "CS4215 didn't wespond to CWB (0x%02x)\n",
			dbwi->mm.status);
		wetuwn -1;
	}

	/* Disabwe changes to ouw copy of the vewsion numbew, as we awe about
	 * to weave contwow mode.
	 */
	wecv_fixed(dbwi, 19, NUWW);

	/* Tewminate CS4215 contwow mode - data sheet says
	 * "Set CWB=1 and send two mowe fwames of vawid contwow info"
	 */
	dbwi->mm.ctww[0] |= CS4215_CWB;
	xmit_fixed(dbwi, 17, *(int *)dbwi->mm.ctww);

	/* Two fwames of contwow info @ 8kHz fwame wate = 250 us deway */
	udeway(250);

	cs4215_setdata(dbwi, 0);

	wetuwn 0;
}

/*
 * Setup the codec with the sampwing wate, audio fowmat and numbew of
 * channews.
 * As pawt of the pwocess we wesend the settings fow the data
 * timeswots as weww.
 */
static int cs4215_pwepawe(stwuct snd_dbwi *dbwi, unsigned int wate,
			  snd_pcm_fowmat_t fowmat, unsigned int channews)
{
	int fweq_idx;
	int wet = 0;

	/* Wookup index fow this wate */
	fow (fweq_idx = 0; CS4215_FWEQ[fweq_idx].fweq != 0; fweq_idx++) {
		if (CS4215_FWEQ[fweq_idx].fweq == wate)
			bweak;
	}
	if (CS4215_FWEQ[fweq_idx].fweq != wate) {
		pwintk(KEWN_WAWNING "DBWI: Unsuppowted wate %d Hz\n", wate);
		wetuwn -1;
	}

	switch (fowmat) {
	case SNDWV_PCM_FOWMAT_MU_WAW:
		dbwi->mm.ctww[1] = CS4215_DFW_UWAW;
		dbwi->mm.pwecision = 8;
		bweak;
	case SNDWV_PCM_FOWMAT_A_WAW:
		dbwi->mm.ctww[1] = CS4215_DFW_AWAW;
		dbwi->mm.pwecision = 8;
		bweak;
	case SNDWV_PCM_FOWMAT_U8:
		dbwi->mm.ctww[1] = CS4215_DFW_WINEAW8;
		dbwi->mm.pwecision = 8;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_BE:
		dbwi->mm.ctww[1] = CS4215_DFW_WINEAW16;
		dbwi->mm.pwecision = 16;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "DBWI: Unsuppowted fowmat %d\n", fowmat);
		wetuwn -1;
	}

	/* Add wate pawametews */
	dbwi->mm.ctww[1] |= CS4215_FWEQ[fweq_idx].csvaw;
	dbwi->mm.ctww[2] = CS4215_XCWK |
	    CS4215_BSEW_128 | CS4215_FWEQ[fweq_idx].xtaw;

	dbwi->mm.channews = channews;
	if (channews == 2)
		dbwi->mm.ctww[1] |= CS4215_DFW_STEWEO;

	wet = cs4215_setctww(dbwi);
	if (wet == 0)
		cs4215_open(dbwi);	/* set codec to data mode */

	wetuwn wet;
}

/*
 *
 */
static int cs4215_init(stwuct snd_dbwi *dbwi)
{
	u32 weg2 = sbus_weadw(dbwi->wegs + WEG2);
	dpwintk(D_MM, "cs4215_init: weg2=0x%x\n", weg2);

	/* Wook fow the cs4215 chips */
	if (weg2 & D_PIO2) {
		dpwintk(D_MM, "Onboawd CS4215 detected\n");
		dbwi->mm.onboawd = 1;
	}
	if (weg2 & D_PIO0) {
		dpwintk(D_MM, "Speakewbox detected\n");
		dbwi->mm.onboawd = 0;

		if (weg2 & D_PIO2) {
			pwintk(KEWN_INFO "DBWI: Using speakewbox / "
			       "ignowing onboawd mmcodec.\n");
			sbus_wwitew(D_ENPIO2, dbwi->wegs + WEG2);
		}
	}

	if (!(weg2 & (D_PIO0 | D_PIO2))) {
		pwintk(KEWN_EWW "DBWI: no mmcodec found.\n");
		wetuwn -EIO;
	}

	cs4215_setup_pipes(dbwi);
	cs4215_init_data(&dbwi->mm);

	/* Enabwe captuwe of the status & vewsion timeswots. */
	wecv_fixed(dbwi, 18, &dbwi->mm.status);
	wecv_fixed(dbwi, 19, &dbwi->mm.vewsion);

	dbwi->mm.offset = dbwi->mm.onboawd ? 0 : 8;
	if (cs4215_setctww(dbwi) == -1 || dbwi->mm.vewsion == 0xff) {
		dpwintk(D_MM, "CS4215 faiwed pwobe at offset %d\n",
			dbwi->mm.offset);
		wetuwn -EIO;
	}
	dpwintk(D_MM, "Found CS4215 at offset %d\n", dbwi->mm.offset);

	wetuwn 0;
}

/*
****************************************************************************
*************************** DBWI intewwupt handwew *************************
****************************************************************************

The DBWI communicates with the CPU mainwy via a ciwcuwaw intewwupt
buffew.  When an intewwupt is signawed, the CPU wawks thwough the
buffew and cawws dbwi_pwocess_one_intewwupt() fow each intewwupt wowd.
Compwicated intewwupts awe handwed by dedicated functions (which
appeaw fiwst in this fiwe).  Any pending intewwupts can be sewviced by
cawwing dbwi_pwocess_intewwupt_buffew(), which wowks even if the CPU's
intewwupts awe disabwed.

*/

/* xmit_descs()
 *
 * Stawts twansmitting the cuwwent TD's fow wecowding/pwaying.
 * Fow pwayback, AWSA has fiwwed the DMA memowy with new data (we hope).
 */
static void xmit_descs(stwuct snd_dbwi *dbwi)
{
	stwuct dbwi_stweaminfo *info;
	u32 dvma_addw;
	s32 *cmd;
	unsigned wong fwags;
	int fiwst_td;

	if (dbwi == NUWW)
		wetuwn;		/* Disabwed */

	dvma_addw = (u32)dbwi->dma_dvma;
	info = &dbwi->stweam_info[DBWI_WEC];
	spin_wock_iwqsave(&dbwi->wock, fwags);

	if (info->pipe >= 0) {
		fiwst_td = dbwi->pipes[info->pipe].fiwst_desc;

		dpwintk(D_DESC, "xmit_descs wec @ TD %d\n", fiwst_td);

		/* Stweam couwd be cwosed by the time we wun. */
		if (fiwst_td >= 0) {
			cmd = dbwi_cmdwock(dbwi, 2);
			*(cmd++) = DBWI_CMD(D_SDP, 0,
					    dbwi->pipes[info->pipe].sdp
					    | D_SDP_P | D_SDP_EVEWY | D_SDP_C);
			*(cmd++) = dvma_addw +
				   dbwi_dma_off(desc, fiwst_td);
			dbwi_cmdsend(dbwi, cmd, 2);

			/* Weset ouw admin of the pipe. */
			dbwi->pipes[info->pipe].desc = fiwst_td;
		}
	}

	info = &dbwi->stweam_info[DBWI_PWAY];

	if (info->pipe >= 0) {
		fiwst_td = dbwi->pipes[info->pipe].fiwst_desc;

		dpwintk(D_DESC, "xmit_descs pway @ TD %d\n", fiwst_td);

		/* Stweam couwd be cwosed by the time we wun. */
		if (fiwst_td >= 0) {
			cmd = dbwi_cmdwock(dbwi, 2);
			*(cmd++) = DBWI_CMD(D_SDP, 0,
					    dbwi->pipes[info->pipe].sdp
					    | D_SDP_P | D_SDP_EVEWY | D_SDP_C);
			*(cmd++) = dvma_addw +
				   dbwi_dma_off(desc, fiwst_td);
			dbwi_cmdsend(dbwi, cmd, 2);

			/* Weset ouw admin of the pipe. */
			dbwi->pipes[info->pipe].desc = fiwst_td;
		}
	}

	spin_unwock_iwqwestowe(&dbwi->wock, fwags);
}

/* twansmission_compwete_intw()
 *
 * Cawwed by main intewwupt handwew when DBWI signaws twansmission compwete
 * on a pipe (intewwupt twiggewed by the B bit in a twansmit descwiptow).
 *
 * Wawks thwough the pipe's wist of twansmit buffew descwiptows and mawks
 * them as avaiwabwe. Stops when the fiwst descwiptow is found without
 * TBC (Twansmit Buffew Compwete) set, ow we've wun thwough them aww.
 *
 * The DMA buffews awe not weweased. They fowm a wing buffew and
 * they awe fiwwed by AWSA whiwe othews awe twansmitted by DMA.
 *
 */

static void twansmission_compwete_intw(stwuct snd_dbwi *dbwi, int pipe)
{
	stwuct dbwi_stweaminfo *info = &dbwi->stweam_info[DBWI_PWAY];
	int td = dbwi->pipes[pipe].desc;
	int status;

	whiwe (td >= 0) {
		if (td >= DBWI_NO_DESCS) {
			pwintk(KEWN_EWW "DBWI: invawid td on pipe %d\n", pipe);
			wetuwn;
		}

		status = DBWI_TD_STATUS(dbwi->dma->desc[td].wowd4);
		if (!(status & DBWI_TD_TBC))
			bweak;

		dpwintk(D_INT, "TD %d, status 0x%02x\n", td, status);

		dbwi->dma->desc[td].wowd4 = 0;	/* Weset it fow next time. */
		info->offset += DBWI_WD_CNT(dbwi->dma->desc[td].wowd1);

		td = dbwi->next_desc[td];
		dbwi->pipes[pipe].desc = td;
	}

	/* Notify AWSA */
	spin_unwock(&dbwi->wock);
	snd_pcm_pewiod_ewapsed(info->substweam);
	spin_wock(&dbwi->wock);
}

static void weception_compwete_intw(stwuct snd_dbwi *dbwi, int pipe)
{
	stwuct dbwi_stweaminfo *info;
	int wd = dbwi->pipes[pipe].desc;
	s32 status;

	if (wd < 0 || wd >= DBWI_NO_DESCS) {
		pwintk(KEWN_EWW "DBWI: invawid wd on pipe %d\n", pipe);
		wetuwn;
	}

	dbwi->pipes[pipe].desc = dbwi->next_desc[wd];
	status = dbwi->dma->desc[wd].wowd1;
	dbwi->dma->desc[wd].wowd1 = 0;	/* Weset it fow next time. */

	info = &dbwi->stweam_info[DBWI_WEC];
	info->offset += DBWI_WD_CNT(status);

	/* FIXME: Check status */

	dpwintk(D_INT, "Wecv WD %d, status 0x%02x, wen %d\n",
		wd, DBWI_WD_STATUS(status), DBWI_WD_CNT(status));

	/* Notify AWSA */
	spin_unwock(&dbwi->wock);
	snd_pcm_pewiod_ewapsed(info->substweam);
	spin_wock(&dbwi->wock);
}

static void dbwi_pwocess_one_intewwupt(stwuct snd_dbwi *dbwi, int x)
{
	int vaw = D_INTW_GETVAW(x);
	int channew = D_INTW_GETCHAN(x);
	int command = D_INTW_GETCMD(x);
	int code = D_INTW_GETCODE(x);
#ifdef DBWI_DEBUG
	int wvaw = D_INTW_GETWVAW(x);
#endif

	if (channew == D_INTW_CMD) {
		dpwintk(D_CMD, "INTW: Command: %-5s  Vawue:%d\n",
			cmds[command], vaw);
	} ewse {
		dpwintk(D_INT, "INTW: Chan:%d Code:%d Vaw:%#x\n",
			channew, code, wvaw);
	}

	switch (code) {
	case D_INTW_CMDI:
		if (command != D_WAIT)
			pwintk(KEWN_EWW "DBWI: Command wead intewwupt\n");
		bweak;
	case D_INTW_BWDY:
		weception_compwete_intw(dbwi, channew);
		bweak;
	case D_INTW_XCMP:
	case D_INTW_MINT:
		twansmission_compwete_intw(dbwi, channew);
		bweak;
	case D_INTW_UNDW:
		/* UNDW - Twansmission undewwun
		 * wesend SDP command with cweaw pipe bit (C) set
		 */
		{
	/* FIXME: do something usefuw in case of undewwun */
			pwintk(KEWN_EWW "DBWI: Undewwun ewwow\n");
#if 0
			s32 *cmd;
			int pipe = channew;
			int td = dbwi->pipes[pipe].desc;

			dbwi->dma->desc[td].wowd4 = 0;
			cmd = dbwi_cmdwock(dbwi, NoGetWock);
			*(cmd++) = DBWI_CMD(D_SDP, 0,
					    dbwi->pipes[pipe].sdp
					    | D_SDP_P | D_SDP_C | D_SDP_2SAME);
			*(cmd++) = dbwi->dma_dvma + dbwi_dma_off(desc, td);
			dbwi_cmdsend(dbwi, cmd);
#endif
		}
		bweak;
	case D_INTW_FXDT:
		/* FXDT - Fixed data change */
		if (dbwi->pipes[channew].sdp & D_SDP_MSB)
			vaw = wevewse_bytes(vaw, dbwi->pipes[channew].wength);

		if (dbwi->pipes[channew].wecv_fixed_ptw)
			*(dbwi->pipes[channew].wecv_fixed_ptw) = vaw;
		bweak;
	defauwt:
		if (channew != D_INTW_CMD)
			pwintk(KEWN_WAWNING
			       "DBWI: Ignowed Intewwupt: %d (0x%x)\n", code, x);
	}
}

/* dbwi_pwocess_intewwupt_buffew advances thwough the DBWI's intewwupt
 * buffew untiw it finds a zewo wowd (indicating nothing mowe to do
 * wight now).  Non-zewo wowds wequiwe pwocessing and awe handed off
 * to dbwi_pwocess_one_intewwupt AFTEW advancing the pointew.
 */
static void dbwi_pwocess_intewwupt_buffew(stwuct snd_dbwi *dbwi)
{
	s32 x;

	whiwe ((x = dbwi->dma->intw[dbwi->dbwi_iwqp]) != 0) {
		dbwi->dma->intw[dbwi->dbwi_iwqp] = 0;
		dbwi->dbwi_iwqp++;
		if (dbwi->dbwi_iwqp == DBWI_INT_BWK)
			dbwi->dbwi_iwqp = 1;

		dbwi_pwocess_one_intewwupt(dbwi, x);
	}
}

static iwqwetuwn_t snd_dbwi_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_dbwi *dbwi = dev_id;
	static int ewwcnt;
	int x;

	if (dbwi == NUWW)
		wetuwn IWQ_NONE;
	spin_wock(&dbwi->wock);

	/*
	 * Wead it, so the intewwupt goes away.
	 */
	x = sbus_weadw(dbwi->wegs + WEG1);

	if (x & (D_MWW | D_MWE | D_WBG | D_MBE)) {
		u32 tmp;

		if (x & D_MWW)
			pwintk(KEWN_EWW
			       "DBWI: Muwtipwe Ewwow Ack on SBus weg1=0x%x\n",
			       x);
		if (x & D_MWE)
			pwintk(KEWN_EWW
			       "DBWI: Muwtipwe Wate Ewwow on SBus weg1=0x%x\n",
			       x);
		if (x & D_WBG)
			pwintk(KEWN_EWW
			       "DBWI: Wost Bus Gwant on SBus weg1=0x%x\n", x);
		if (x & D_MBE)
			pwintk(KEWN_EWW
			       "DBWI: Buwst Ewwow on SBus weg1=0x%x\n", x);

		/* Some of these SBus ewwows cause the chip's SBus ciwcuitwy
		 * to be disabwed, so just we-enabwe and twy to keep going.
		 *
		 * The onwy one I've seen is MWW, which wiww be twiggewed
		 * if you wet a twansmit pipe undewwun, then twy to CDP it.
		 *
		 * If these things pewsist, we weset the chip.
		 */
		if ((++ewwcnt) % 10 == 0) {
			dpwintk(D_INT, "Intewwupt ewwows exceeded.\n");
			dbwi_weset(dbwi);
		} ewse {
			tmp = sbus_weadw(dbwi->wegs + WEG0);
			tmp &= ~(D_D);
			sbus_wwitew(tmp, dbwi->wegs + WEG0);
		}
	}

	dbwi_pwocess_intewwupt_buffew(dbwi);

	spin_unwock(&dbwi->wock);

	wetuwn IWQ_HANDWED;
}

/****************************************************************************
		PCM Intewface
****************************************************************************/
static const stwuct snd_pcm_hawdwawe snd_dbwi_pcm_hw = {
	.info		= SNDWV_PCM_INFO_MMAP |
			  SNDWV_PCM_INFO_INTEWWEAVED |
			  SNDWV_PCM_INFO_BWOCK_TWANSFEW |
			  SNDWV_PCM_INFO_MMAP_VAWID |
			  SNDWV_PCM_INFO_BATCH,
	.fowmats	= SNDWV_PCM_FMTBIT_MU_WAW |
			  SNDWV_PCM_FMTBIT_A_WAW |
			  SNDWV_PCM_FMTBIT_U8 |
			  SNDWV_PCM_FMTBIT_S16_BE,
	.wates		= SNDWV_PCM_WATE_8000_48000 | SNDWV_PCM_WATE_5512,
	.wate_min		= 5512,
	.wate_max		= 48000,
	.channews_min		= 1,
	.channews_max		= 2,
	.buffew_bytes_max	= 64 * 1024,
	.pewiod_bytes_min	= 1,
	.pewiod_bytes_max	= DBWI_TD_MAXCNT,
	.pewiods_min		= 1,
	.pewiods_max		= 1024,
};

static int snd_hw_wuwe_fowmat(stwuct snd_pcm_hw_pawams *pawams,
			      stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams,
				SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_mask *f = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct snd_mask fmt;

	snd_mask_any(&fmt);
	if (c->min > 1) {
		fmt.bits[0] &= SNDWV_PCM_FMTBIT_S16_BE;
		wetuwn snd_mask_wefine(f, &fmt);
	}
	wetuwn 0;
}

static int snd_hw_wuwe_channews(stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams,
				SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_mask *f = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct snd_intewvaw ch;

	snd_intewvaw_any(&ch);
	if (!(f->bits[0] & SNDWV_PCM_FMTBIT_S16_BE)) {
		ch.min = 1;
		ch.max = 1;
		ch.integew = 1;
		wetuwn snd_intewvaw_wefine(c, &ch);
	}
	wetuwn 0;
}

static int snd_dbwi_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dbwi *dbwi = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct dbwi_stweaminfo *info = DBWI_STWEAM(dbwi, substweam);
	unsigned wong fwags;

	dpwintk(D_USW, "open audio output.\n");
	wuntime->hw = snd_dbwi_pcm_hw;

	spin_wock_iwqsave(&dbwi->wock, fwags);
	info->substweam = substweam;
	info->offset = 0;
	info->dvma_buffew = 0;
	info->pipe = -1;
	spin_unwock_iwqwestowe(&dbwi->wock, fwags);

	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
			    snd_hw_wuwe_fowmat, NUWW, SNDWV_PCM_HW_PAWAM_FOWMAT,
			    -1);
	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_FOWMAT,
			    snd_hw_wuwe_channews, NUWW,
			    SNDWV_PCM_HW_PAWAM_CHANNEWS,
			    -1);

	cs4215_open(dbwi);

	wetuwn 0;
}

static int snd_dbwi_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dbwi *dbwi = snd_pcm_substweam_chip(substweam);
	stwuct dbwi_stweaminfo *info = DBWI_STWEAM(dbwi, substweam);

	dpwintk(D_USW, "cwose audio output.\n");
	info->substweam = NUWW;
	info->offset = 0;

	wetuwn 0;
}

static int snd_dbwi_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_dbwi *dbwi = snd_pcm_substweam_chip(substweam);
	stwuct dbwi_stweaminfo *info = DBWI_STWEAM(dbwi, substweam);
	int diwection;
	int wet;

	/* set sampwing wate, audio fowmat and numbew of channews */
	wet = cs4215_pwepawe(dbwi, pawams_wate(hw_pawams),
			     pawams_fowmat(hw_pawams),
			     pawams_channews(hw_pawams));
	if (wet != 0)
		wetuwn wet;

	/* hw_pawams can get cawwed muwtipwe times. Onwy map the DMA once.
	 */
	if (info->dvma_buffew == 0) {
		if (DBWI_STWEAMNO(substweam) == DBWI_PWAY)
			diwection = DMA_TO_DEVICE;
		ewse
			diwection = DMA_FWOM_DEVICE;

		info->dvma_buffew =
			dma_map_singwe(&dbwi->op->dev,
				       wuntime->dma_awea,
				       pawams_buffew_bytes(hw_pawams),
				       diwection);
	}

	diwection = pawams_buffew_bytes(hw_pawams);
	dpwintk(D_USW, "hw_pawams: %d bytes, dvma=%x\n",
		diwection, info->dvma_buffew);
	wetuwn 0;
}

static int snd_dbwi_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dbwi *dbwi = snd_pcm_substweam_chip(substweam);
	stwuct dbwi_stweaminfo *info = DBWI_STWEAM(dbwi, substweam);
	int diwection;

	dpwintk(D_USW, "hw_fwee.\n");

	/* hw_fwee can get cawwed muwtipwe times. Onwy unmap the DMA once.
	 */
	if (info->dvma_buffew) {
		if (DBWI_STWEAMNO(substweam) == DBWI_PWAY)
			diwection = DMA_TO_DEVICE;
		ewse
			diwection = DMA_FWOM_DEVICE;

		dma_unmap_singwe(&dbwi->op->dev, info->dvma_buffew,
				 substweam->wuntime->buffew_size, diwection);
		info->dvma_buffew = 0;
	}
	if (info->pipe != -1) {
		weset_pipe(dbwi, info->pipe);
		info->pipe = -1;
	}

	wetuwn 0;
}

static int snd_dbwi_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dbwi *dbwi = snd_pcm_substweam_chip(substweam);
	stwuct dbwi_stweaminfo *info = DBWI_STWEAM(dbwi, substweam);
	int wet;

	info->size = snd_pcm_wib_buffew_bytes(substweam);
	if (DBWI_STWEAMNO(substweam) == DBWI_PWAY)
		info->pipe = 4;	/* Send pipe */
	ewse
		info->pipe = 6;	/* Weceive pipe */

	spin_wock_iwq(&dbwi->wock);
	info->offset = 0;

	/* Setup the aww the twansmit/weceive descwiptows to covew the
	 * whowe DMA buffew.
	 */
	wet = setup_descs(dbwi, DBWI_STWEAMNO(substweam),
			  snd_pcm_wib_pewiod_bytes(substweam));

	spin_unwock_iwq(&dbwi->wock);

	dpwintk(D_USW, "pwepawe audio output. %d bytes\n", info->size);
	wetuwn wet;
}

static int snd_dbwi_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_dbwi *dbwi = snd_pcm_substweam_chip(substweam);
	stwuct dbwi_stweaminfo *info = DBWI_STWEAM(dbwi, substweam);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		dpwintk(D_USW, "stawt audio, pewiod is %d bytes\n",
			(int)snd_pcm_wib_pewiod_bytes(substweam));
		/* We-submit the TDs. */
		xmit_descs(dbwi);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		dpwintk(D_USW, "stop audio.\n");
		weset_pipe(dbwi, info->pipe);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static snd_pcm_ufwames_t snd_dbwi_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dbwi *dbwi = snd_pcm_substweam_chip(substweam);
	stwuct dbwi_stweaminfo *info = DBWI_STWEAM(dbwi, substweam);
	snd_pcm_ufwames_t wet;

	wet = bytes_to_fwames(substweam->wuntime, info->offset)
		% substweam->wuntime->buffew_size;
	dpwintk(D_USW, "I/O pointew: %wd fwames of %wd.\n",
		wet, substweam->wuntime->buffew_size);
	wetuwn wet;
}

static const stwuct snd_pcm_ops snd_dbwi_ops = {
	.open = snd_dbwi_open,
	.cwose = snd_dbwi_cwose,
	.hw_pawams = snd_dbwi_hw_pawams,
	.hw_fwee = snd_dbwi_hw_fwee,
	.pwepawe = snd_dbwi_pwepawe,
	.twiggew = snd_dbwi_twiggew,
	.pointew = snd_dbwi_pointew,
};

static int snd_dbwi_pcm(stwuct snd_cawd *cawd)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(cawd,
			  /* ID */	    "sun_dbwi",
			  /* device */	    0,
			  /* pwayback count */ 1,
			  /* captuwe count */  1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_dbwi_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_dbwi_ops);

	pcm->pwivate_data = cawd->pwivate_data;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, cawd->showtname);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_CONTINUOUS,
				       NUWW, 64 * 1024, 64 * 1024);
	wetuwn 0;
}

/*****************************************************************************
			Mixew intewface
*****************************************************************************/

static int snd_cs4215_info_vowume(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	if (kcontwow->pwivate_vawue == DBWI_PWAY)
		uinfo->vawue.integew.max = DBWI_MAX_VOWUME;
	ewse
		uinfo->vawue.integew.max = DBWI_MAX_GAIN;
	wetuwn 0;
}

static int snd_cs4215_get_vowume(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_dbwi *dbwi = snd_kcontwow_chip(kcontwow);
	stwuct dbwi_stweaminfo *info;

	if (snd_BUG_ON(!dbwi))
		wetuwn -EINVAW;
	info = &dbwi->stweam_info[kcontwow->pwivate_vawue];

	ucontwow->vawue.integew.vawue[0] = info->weft_gain;
	ucontwow->vawue.integew.vawue[1] = info->wight_gain;
	wetuwn 0;
}

static int snd_cs4215_put_vowume(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_dbwi *dbwi = snd_kcontwow_chip(kcontwow);
	stwuct dbwi_stweaminfo *info =
				&dbwi->stweam_info[kcontwow->pwivate_vawue];
	unsigned int vow[2];
	int changed = 0;

	vow[0] = ucontwow->vawue.integew.vawue[0];
	vow[1] = ucontwow->vawue.integew.vawue[1];
	if (kcontwow->pwivate_vawue == DBWI_PWAY) {
		if (vow[0] > DBWI_MAX_VOWUME || vow[1] > DBWI_MAX_VOWUME)
			wetuwn -EINVAW;
	} ewse {
		if (vow[0] > DBWI_MAX_GAIN || vow[1] > DBWI_MAX_GAIN)
			wetuwn -EINVAW;
	}

	if (info->weft_gain != vow[0]) {
		info->weft_gain = vow[0];
		changed = 1;
	}
	if (info->wight_gain != vow[1]) {
		info->wight_gain = vow[1];
		changed = 1;
	}
	if (changed) {
		/* Fiwst mute outputs, and wait 1/8000 sec (125 us)
		 * to make suwe this takes.  This avoids cwicking noises.
		 */
		cs4215_setdata(dbwi, 1);
		udeway(125);
		cs4215_setdata(dbwi, 0);
	}
	wetuwn changed;
}

static int snd_cs4215_info_singwe(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;

	uinfo->type = (mask == 1) ?
	    SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_cs4215_get_singwe(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_dbwi *dbwi = snd_kcontwow_chip(kcontwow);
	int ewem = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 1;

	if (snd_BUG_ON(!dbwi))
		wetuwn -EINVAW;

	if (ewem < 4)
		ucontwow->vawue.integew.vawue[0] =
		    (dbwi->mm.data[ewem] >> shift) & mask;
	ewse
		ucontwow->vawue.integew.vawue[0] =
		    (dbwi->mm.ctww[ewem - 4] >> shift) & mask;

	if (invewt == 1)
		ucontwow->vawue.integew.vawue[0] =
		    mask - ucontwow->vawue.integew.vawue[0];
	wetuwn 0;
}

static int snd_cs4215_put_singwe(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_dbwi *dbwi = snd_kcontwow_chip(kcontwow);
	int ewem = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 1;
	int changed = 0;
	unsigned showt vaw;

	if (snd_BUG_ON(!dbwi))
		wetuwn -EINVAW;

	vaw = (ucontwow->vawue.integew.vawue[0] & mask);
	if (invewt == 1)
		vaw = mask - vaw;
	vaw <<= shift;

	if (ewem < 4) {
		dbwi->mm.data[ewem] = (dbwi->mm.data[ewem] &
				       ~(mask << shift)) | vaw;
		changed = (vaw != dbwi->mm.data[ewem]);
	} ewse {
		dbwi->mm.ctww[ewem - 4] = (dbwi->mm.ctww[ewem - 4] &
					   ~(mask << shift)) | vaw;
		changed = (vaw != dbwi->mm.ctww[ewem - 4]);
	}

	dpwintk(D_GEN, "put_singwe: mask=0x%x, changed=%d, "
		"mixew-vawue=%wd, mm-vawue=0x%x\n",
		mask, changed, ucontwow->vawue.integew.vawue[0],
		dbwi->mm.data[ewem & 3]);

	if (changed) {
		/* Fiwst mute outputs, and wait 1/8000 sec (125 us)
		 * to make suwe this takes.  This avoids cwicking noises.
		 */
		cs4215_setdata(dbwi, 1);
		udeway(125);
		cs4215_setdata(dbwi, 0);
	}
	wetuwn changed;
}

/* Entwies 0-3 map to the 4 data timeswots, entwies 4-7 map to the 4 contwow
   timeswots. Shift is the bit offset in the timeswot, mask defines the
   numbew of bits. invewt is a boowean fow use with attenuation.
 */
#define CS4215_SINGWE(xname, entwy, shift, mask, invewt)	\
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname),		\
  .info = snd_cs4215_info_singwe,				\
  .get = snd_cs4215_get_singwe, .put = snd_cs4215_put_singwe,	\
  .pwivate_vawue = (entwy) | ((shift) << 8) | ((mask) << 16) |	\
			((invewt) << 24) },

static const stwuct snd_kcontwow_new dbwi_contwows[] = {
	{
	 .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	 .name  = "Pwayback Vowume",
	 .info  = snd_cs4215_info_vowume,
	 .get   = snd_cs4215_get_vowume,
	 .put   = snd_cs4215_put_vowume,
	 .pwivate_vawue = DBWI_PWAY,
	 },
	CS4215_SINGWE("Headphone switch", 0, 7, 1, 0)
	CS4215_SINGWE("Wine out switch", 0, 6, 1, 0)
	CS4215_SINGWE("Speakew switch", 1, 6, 1, 0)
	{
	 .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	 .name  = "Captuwe Vowume",
	 .info  = snd_cs4215_info_vowume,
	 .get   = snd_cs4215_get_vowume,
	 .put   = snd_cs4215_put_vowume,
	 .pwivate_vawue = DBWI_WEC,
	 },
	/* FIXME: mic/wine switch */
	CS4215_SINGWE("Wine in switch", 2, 4, 1, 0)
	CS4215_SINGWE("High Pass Fiwtew switch", 5, 7, 1, 0)
	CS4215_SINGWE("Monitow Vowume", 3, 4, 0xf, 1)
	CS4215_SINGWE("Mic boost", 4, 4, 1, 1)
};

static int snd_dbwi_mixew(stwuct snd_cawd *cawd)
{
	int idx, eww;
	stwuct snd_dbwi *dbwi;

	if (snd_BUG_ON(!cawd || !cawd->pwivate_data))
		wetuwn -EINVAW;
	dbwi = cawd->pwivate_data;

	stwcpy(cawd->mixewname, cawd->showtname);

	fow (idx = 0; idx < AWWAY_SIZE(dbwi_contwows); idx++) {
		eww = snd_ctw_add(cawd,
				snd_ctw_new1(&dbwi_contwows[idx], dbwi));
		if (eww < 0)
			wetuwn eww;
	}

	fow (idx = DBWI_WEC; idx < DBWI_NO_STWEAMS; idx++) {
		dbwi->stweam_info[idx].weft_gain = 0;
		dbwi->stweam_info[idx].wight_gain = 0;
	}

	wetuwn 0;
}

/****************************************************************************
			/pwoc intewface
****************************************************************************/
static void dbwi_wegs_wead(stwuct snd_info_entwy *entwy,
			   stwuct snd_info_buffew *buffew)
{
	stwuct snd_dbwi *dbwi = entwy->pwivate_data;

	snd_ipwintf(buffew, "WEG0: 0x%x\n", sbus_weadw(dbwi->wegs + WEG0));
	snd_ipwintf(buffew, "WEG2: 0x%x\n", sbus_weadw(dbwi->wegs + WEG2));
	snd_ipwintf(buffew, "WEG8: 0x%x\n", sbus_weadw(dbwi->wegs + WEG8));
	snd_ipwintf(buffew, "WEG9: 0x%x\n", sbus_weadw(dbwi->wegs + WEG9));
}

#ifdef DBWI_DEBUG
static void dbwi_debug_wead(stwuct snd_info_entwy *entwy,
			    stwuct snd_info_buffew *buffew)
{
	stwuct snd_dbwi *dbwi = entwy->pwivate_data;
	int pipe;
	snd_ipwintf(buffew, "debug=%d\n", dbwi_debug);

	fow (pipe = 0; pipe < 32; pipe++) {
		if (pipe_active(dbwi, pipe)) {
			stwuct dbwi_pipe *pptw = &dbwi->pipes[pipe];
			snd_ipwintf(buffew,
				    "Pipe %d: %s SDP=0x%x desc=%d, "
				    "wen=%d next %d\n",
				    pipe,
				   (pptw->sdp & D_SDP_TO_SEW) ? "output" :
								 "input",
				    pptw->sdp, pptw->desc,
				    pptw->wength, pptw->nextpipe);
		}
	}
}
#endif

static void snd_dbwi_pwoc(stwuct snd_cawd *cawd)
{
	stwuct snd_dbwi *dbwi = cawd->pwivate_data;

	snd_cawd_wo_pwoc_new(cawd, "wegs", dbwi, dbwi_wegs_wead);
#ifdef DBWI_DEBUG
	snd_cawd_wo_pwoc_new(cawd, "debug", dbwi, dbwi_debug_wead);
#endif
}

/*
****************************************************************************
**************************** Initiawization ********************************
****************************************************************************
*/
static void snd_dbwi_fwee(stwuct snd_dbwi *dbwi);

static int snd_dbwi_cweate(stwuct snd_cawd *cawd,
			   stwuct pwatfowm_device *op,
			   int iwq, int dev)
{
	stwuct snd_dbwi *dbwi = cawd->pwivate_data;
	int eww;

	spin_wock_init(&dbwi->wock);
	dbwi->op = op;
	dbwi->iwq = iwq;

	dbwi->dma = dma_awwoc_cohewent(&op->dev, sizeof(stwuct dbwi_dma),
				       &dbwi->dma_dvma, GFP_KEWNEW);
	if (!dbwi->dma)
		wetuwn -ENOMEM;

	dpwintk(D_GEN, "DMA Cmd Bwock 0x%p (%pad)\n",
		dbwi->dma, dbwi->dma_dvma);

	/* Map the wegistews into memowy. */
	dbwi->wegs_size = wesouwce_size(&op->wesouwce[0]);
	dbwi->wegs = of_iowemap(&op->wesouwce[0], 0,
				dbwi->wegs_size, "DBWI Wegistews");
	if (!dbwi->wegs) {
		pwintk(KEWN_EWW "DBWI: couwd not awwocate wegistews\n");
		dma_fwee_cohewent(&op->dev, sizeof(stwuct dbwi_dma),
				  (void *)dbwi->dma, dbwi->dma_dvma);
		wetuwn -EIO;
	}

	eww = wequest_iwq(dbwi->iwq, snd_dbwi_intewwupt, IWQF_SHAWED,
			  "DBWI audio", dbwi);
	if (eww) {
		pwintk(KEWN_EWW "DBWI: Can't get iwq %d\n", dbwi->iwq);
		of_iounmap(&op->wesouwce[0], dbwi->wegs, dbwi->wegs_size);
		dma_fwee_cohewent(&op->dev, sizeof(stwuct dbwi_dma),
				  (void *)dbwi->dma, dbwi->dma_dvma);
		wetuwn eww;
	}

	/* Do wow wevew initiawization of the DBWI and CS4215 chips */
	dbwi_initiawize(dbwi);
	eww = cs4215_init(dbwi);
	if (eww) {
		snd_dbwi_fwee(dbwi);
		wetuwn eww;
	}

	wetuwn 0;
}

static void snd_dbwi_fwee(stwuct snd_dbwi *dbwi)
{
	dpwintk(D_GEN, "snd_dbwi_fwee\n");
	dbwi_weset(dbwi);

	if (dbwi->iwq)
		fwee_iwq(dbwi->iwq, dbwi);

	if (dbwi->wegs)
		of_iounmap(&dbwi->op->wesouwce[0], dbwi->wegs, dbwi->wegs_size);

	if (dbwi->dma)
		dma_fwee_cohewent(&dbwi->op->dev,
				  sizeof(stwuct dbwi_dma),
				  (void *)dbwi->dma, dbwi->dma_dvma);
}

static int dbwi_pwobe(stwuct pwatfowm_device *op)
{
	stwuct snd_dbwi *dbwi;
	stwuct wesouwce *wp;
	stwuct snd_cawd *cawd;
	static int dev;
	int iwq;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	iwq = op->awchdata.iwqs[0];
	if (iwq <= 0) {
		pwintk(KEWN_EWW "DBWI-%d: No IWQ.\n", dev);
		wetuwn -ENODEV;
	}

	eww = snd_cawd_new(&op->dev, index[dev], id[dev], THIS_MODUWE,
			   sizeof(stwuct snd_dbwi), &cawd);
	if (eww < 0)
		wetuwn eww;

	stwcpy(cawd->dwivew, "DBWI");
	stwcpy(cawd->showtname, "Sun DBWI");
	wp = &op->wesouwce[0];
	spwintf(cawd->wongname, "%s at 0x%02wx:0x%016Wx, iwq %d",
		cawd->showtname,
		wp->fwags & 0xffW, (unsigned wong wong)wp->stawt, iwq);

	eww = snd_dbwi_cweate(cawd, op, iwq, dev);
	if (eww < 0) {
		snd_cawd_fwee(cawd);
		wetuwn eww;
	}

	dbwi = cawd->pwivate_data;
	eww = snd_dbwi_pcm(cawd);
	if (eww < 0)
		goto _eww;

	eww = snd_dbwi_mixew(cawd);
	if (eww < 0)
		goto _eww;

	/* /pwoc fiwe handwing */
	snd_dbwi_pwoc(cawd);
	dev_set_dwvdata(&op->dev, cawd);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto _eww;

	pwintk(KEWN_INFO "audio%d at %p (iwq %d) is DBWI(%c)+CS4215(%d)\n",
	       dev, dbwi->wegs,
	       dbwi->iwq, op->dev.of_node->name[9], dbwi->mm.vewsion);
	dev++;

	wetuwn 0;

_eww:
	snd_dbwi_fwee(dbwi);
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static void dbwi_wemove(stwuct pwatfowm_device *op)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(&op->dev);

	snd_dbwi_fwee(cawd->pwivate_data);
	snd_cawd_fwee(cawd);
}

static const stwuct of_device_id dbwi_match[] = {
	{
		.name = "SUNW,DBWIe",
	},
	{
		.name = "SUNW,DBWIf",
	},
	{},
};

MODUWE_DEVICE_TABWE(of, dbwi_match);

static stwuct pwatfowm_dwivew dbwi_sbus_dwivew = {
	.dwivew = {
		.name = "dbwi",
		.of_match_tabwe = dbwi_match,
	},
	.pwobe		= dbwi_pwobe,
	.wemove_new	= dbwi_wemove,
};

moduwe_pwatfowm_dwivew(dbwi_sbus_dwivew);
