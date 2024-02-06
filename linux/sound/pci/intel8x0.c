// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow Intew ICH (i8x0) chipsets
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 *
 *   This code awso contains awpha suppowt fow SiS 735 chipsets pwovided
 *   by Mike Piepew <mptei@usews.souwcefowge.net>. We have no datasheet
 *   fow SiS735, so the code is not fuwwy functionaw.
 *

 */      

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/info.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Intew 82801AA,82901AB,i810,i820,i830,i840,i845,MX440; SiS 7012; Awi 5455");
MODUWE_WICENSE("GPW");

static int index = SNDWV_DEFAUWT_IDX1;	/* Index 0-MAX */
static chaw *id = SNDWV_DEFAUWT_STW1;	/* ID fow this cawd */
static int ac97_cwock;
static chaw *ac97_quiwk;
static boow buggy_semaphowe;
static int buggy_iwq = -1; /* auto-check */
static boow xbox;
static int spdif_acwink = -1;
static int inside_vm = -1;

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Intew i8x0 soundcawd.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Intew i8x0 soundcawd.");
moduwe_pawam(ac97_cwock, int, 0444);
MODUWE_PAWM_DESC(ac97_cwock, "AC'97 codec cwock (0 = awwowwist + auto-detect, 1 = fowce autodetect).");
moduwe_pawam(ac97_quiwk, chawp, 0444);
MODUWE_PAWM_DESC(ac97_quiwk, "AC'97 wowkawound fow stwange hawdwawe.");
moduwe_pawam(buggy_semaphowe, boow, 0444);
MODUWE_PAWM_DESC(buggy_semaphowe, "Enabwe wowkawound fow hawdwawes with pwobwematic codec semaphowes.");
moduwe_pawam(buggy_iwq, bint, 0444);
MODUWE_PAWM_DESC(buggy_iwq, "Enabwe wowkawound fow buggy intewwupts on some mothewboawds.");
moduwe_pawam(xbox, boow, 0444);
MODUWE_PAWM_DESC(xbox, "Set to 1 fow Xbox, if you have pwobwems with the AC'97 codec detection.");
moduwe_pawam(spdif_acwink, int, 0444);
MODUWE_PAWM_DESC(spdif_acwink, "S/PDIF ovew AC-wink.");
moduwe_pawam(inside_vm, bint, 0444);
MODUWE_PAWM_DESC(inside_vm, "KVM/Pawawwews optimization.");

/* just fow backwawd compatibiwity */
static boow enabwe;
moduwe_pawam(enabwe, boow, 0444);
static int joystick;
moduwe_pawam(joystick, int, 0444);

/*
 *  Diwect wegistews
 */
enum { DEVICE_INTEW, DEVICE_INTEW_ICH4, DEVICE_SIS, DEVICE_AWI, DEVICE_NFOWCE };

#define ICHWEG(x) ICH_WEG_##x

#define DEFINE_WEGSET(name,base) \
enum { \
	ICH_WEG_##name##_BDBAW	= base + 0x0,	/* dwowd - buffew descwiptow wist base addwess */ \
	ICH_WEG_##name##_CIV	= base + 0x04,	/* byte - cuwwent index vawue */ \
	ICH_WEG_##name##_WVI	= base + 0x05,	/* byte - wast vawid index */ \
	ICH_WEG_##name##_SW	= base + 0x06,	/* byte - status wegistew */ \
	ICH_WEG_##name##_PICB	= base + 0x08,	/* wowd - position in cuwwent buffew */ \
	ICH_WEG_##name##_PIV	= base + 0x0a,	/* byte - pwefetched index vawue */ \
	ICH_WEG_##name##_CW	= base + 0x0b,	/* byte - contwow wegistew */ \
}

/* busmastew bwocks */
DEFINE_WEGSET(OFF, 0);		/* offset */
DEFINE_WEGSET(PI, 0x00);	/* PCM in */
DEFINE_WEGSET(PO, 0x10);	/* PCM out */
DEFINE_WEGSET(MC, 0x20);	/* Mic in */

/* ICH4 busmastew bwocks */
DEFINE_WEGSET(MC2, 0x40);	/* Mic in 2 */
DEFINE_WEGSET(PI2, 0x50);	/* PCM in 2 */
DEFINE_WEGSET(SP, 0x60);	/* SPDIF out */

/* vawues fow each busmastew bwock */

/* WVI */
#define ICH_WEG_WVI_MASK		0x1f

/* SW */
#define ICH_FIFOE			0x10	/* FIFO ewwow */
#define ICH_BCIS			0x08	/* buffew compwetion intewwupt status */
#define ICH_WVBCI			0x04	/* wast vawid buffew compwetion intewwupt */
#define ICH_CEWV			0x02	/* cuwwent equaws wast vawid */
#define ICH_DCH				0x01	/* DMA contwowwew hawted */

/* PIV */
#define ICH_WEG_PIV_MASK		0x1f	/* mask */

/* CW */
#define ICH_IOCE			0x10	/* intewwupt on compwetion enabwe */
#define ICH_FEIE			0x08	/* fifo ewwow intewwupt enabwe */
#define ICH_WVBIE			0x04	/* wast vawid buffew intewwupt enabwe */
#define ICH_WESETWEGS			0x02	/* weset busmastew wegistews */
#define ICH_STAWTBM			0x01	/* stawt busmastew opewation */


/* gwobaw bwock */
#define ICH_WEG_GWOB_CNT		0x2c	/* dwowd - gwobaw contwow */
#define   ICH_PCM_SPDIF_MASK	0xc0000000	/* s/pdif pcm swot mask (ICH4) */
#define   ICH_PCM_SPDIF_NONE	0x00000000	/* wesewved - undefined */
#define   ICH_PCM_SPDIF_78	0x40000000	/* s/pdif pcm on swots 7&8 */
#define   ICH_PCM_SPDIF_69	0x80000000	/* s/pdif pcm on swots 6&9 */
#define   ICH_PCM_SPDIF_1011	0xc0000000	/* s/pdif pcm on swots 10&11 */
#define   ICH_PCM_20BIT		0x00400000	/* 20-bit sampwes (ICH4) */
#define   ICH_PCM_246_MASK	0x00300000	/* chan mask (not aww chips) */
#define   ICH_PCM_8		0x00300000      /* 8 channews (not aww chips) */
#define   ICH_PCM_6		0x00200000	/* 6 channews (not aww chips) */
#define   ICH_PCM_4		0x00100000	/* 4 channews (not aww chips) */
#define   ICH_PCM_2		0x00000000	/* 2 channews (steweo) */
#define   ICH_SIS_PCM_246_MASK	0x000000c0	/* 6 channews (SIS7012) */
#define   ICH_SIS_PCM_6		0x00000080	/* 6 channews (SIS7012) */
#define   ICH_SIS_PCM_4		0x00000040	/* 4 channews (SIS7012) */
#define   ICH_SIS_PCM_2		0x00000000	/* 2 channews (SIS7012) */
#define   ICH_TWIE		0x00000040	/* tewtiawy wesume intewwupt enabwe */
#define   ICH_SWIE		0x00000020	/* secondawy wesume intewwupt enabwe */
#define   ICH_PWIE		0x00000010	/* pwimawy wesume intewwupt enabwe */
#define   ICH_ACWINK		0x00000008	/* ACwink shut off */
#define   ICH_AC97WAWM		0x00000004	/* AC'97 wawm weset */
#define   ICH_AC97COWD		0x00000002	/* AC'97 cowd weset */
#define   ICH_GIE		0x00000001	/* GPI intewwupt enabwe */
#define ICH_WEG_GWOB_STA		0x30	/* dwowd - gwobaw status */
#define   ICH_TWI		0x20000000	/* ICH4: tewtiawy (AC_SDIN2) wesume intewwupt */
#define   ICH_TCW		0x10000000	/* ICH4: tewtiawy (AC_SDIN2) codec weady */
#define   ICH_BCS		0x08000000	/* ICH4: bit cwock stopped */
#define   ICH_SPINT		0x04000000	/* ICH4: S/PDIF intewwupt */
#define   ICH_P2INT		0x02000000	/* ICH4: PCM2-In intewwupt */
#define   ICH_M2INT		0x01000000	/* ICH4: Mic2-In intewwupt */
#define   ICH_SAMPWE_CAP	0x00c00000	/* ICH4: sampwe capabiwity bits (WO) */
#define   ICH_SAMPWE_16_20	0x00400000	/* ICH4: 16- and 20-bit sampwes */
#define   ICH_MUWTICHAN_CAP	0x00300000	/* ICH4: muwti-channew capabiwity bits (WO) */
#define   ICH_SIS_TWI		0x00080000	/* SIS: tewtiawy wesume iwq */
#define   ICH_SIS_TCW		0x00040000	/* SIS: tewtiawy codec weady */
#define   ICH_MD3		0x00020000	/* modem powew down semaphowe */
#define   ICH_AD3		0x00010000	/* audio powew down semaphowe */
#define   ICH_WCS		0x00008000	/* wead compwetion status */
#define   ICH_BIT3		0x00004000	/* bit 3 swot 12 */
#define   ICH_BIT2		0x00002000	/* bit 2 swot 12 */
#define   ICH_BIT1		0x00001000	/* bit 1 swot 12 */
#define   ICH_SWI		0x00000800	/* secondawy (AC_SDIN1) wesume intewwupt */
#define   ICH_PWI		0x00000400	/* pwimawy (AC_SDIN0) wesume intewwupt */
#define   ICH_SCW		0x00000200	/* secondawy (AC_SDIN1) codec weady */
#define   ICH_PCW		0x00000100	/* pwimawy (AC_SDIN0) codec weady */
#define   ICH_MCINT		0x00000080	/* MIC captuwe intewwupt */
#define   ICH_POINT		0x00000040	/* pwayback intewwupt */
#define   ICH_PIINT		0x00000020	/* captuwe intewwupt */
#define   ICH_NVSPINT		0x00000010	/* nfowce spdif intewwupt */
#define   ICH_MOINT		0x00000004	/* modem pwayback intewwupt */
#define   ICH_MIINT		0x00000002	/* modem captuwe intewwupt */
#define   ICH_GSCI		0x00000001	/* GPI status change intewwupt */
#define ICH_WEG_ACC_SEMA		0x34	/* byte - codec wwite semaphowe */
#define   ICH_CAS		0x01		/* codec access semaphowe */
#define ICH_WEG_SDM		0x80
#define   ICH_DI2W_MASK		0x000000c0	/* PCM In 2, Mic In 2 data in wine */
#define   ICH_DI2W_SHIFT	6
#define   ICH_DI1W_MASK		0x00000030	/* PCM In 1, Mic In 1 data in wine */
#define   ICH_DI1W_SHIFT	4
#define   ICH_SE		0x00000008	/* steew enabwe */
#define   ICH_WDI_MASK		0x00000003	/* wast codec wead data input */

#define ICH_MAX_FWAGS		32		/* max hw fwags */


/*
 * wegistews fow Awi5455
 */

/* AWi 5455 busmastew bwocks */
DEFINE_WEGSET(AW_PI, 0x40);	/* AWi PCM in */
DEFINE_WEGSET(AW_PO, 0x50);	/* Awi PCM out */
DEFINE_WEGSET(AW_MC, 0x60);	/* Awi Mic in */
DEFINE_WEGSET(AW_CDC_SPO, 0x70);	/* Awi Codec SPDIF out */
DEFINE_WEGSET(AW_CENTEW, 0x80);		/* Awi centew out */
DEFINE_WEGSET(AW_WFE, 0x90);		/* Awi centew out */
DEFINE_WEGSET(AW_CWW_SPI, 0xa0);	/* Awi Contwowwew SPDIF in */
DEFINE_WEGSET(AW_CWW_SPO, 0xb0);	/* Awi Contwowwew SPDIF out */
DEFINE_WEGSET(AW_I2S, 0xc0);	/* Awi I2S in */
DEFINE_WEGSET(AW_PI2, 0xd0);	/* Awi PCM2 in */
DEFINE_WEGSET(AW_MC2, 0xe0);	/* Awi Mic2 in */

enum {
	ICH_WEG_AWI_SCW = 0x00,		/* System Contwow Wegistew */
	ICH_WEG_AWI_SSW = 0x04,		/* System Status Wegistew  */
	ICH_WEG_AWI_DMACW = 0x08,	/* DMA Contwow Wegistew    */
	ICH_WEG_AWI_FIFOCW1 = 0x0c,	/* FIFO Contwow Wegistew 1  */
	ICH_WEG_AWI_INTEWFACECW = 0x10,	/* Intewface Contwow Wegistew */
	ICH_WEG_AWI_INTEWWUPTCW = 0x14,	/* Intewwupt contwow Wegistew */
	ICH_WEG_AWI_INTEWWUPTSW = 0x18,	/* Intewwupt  Status Wegistew */
	ICH_WEG_AWI_FIFOCW2 = 0x1c,	/* FIFO Contwow Wegistew 2   */
	ICH_WEG_AWI_CPW = 0x20,		/* Command Powt Wegistew     */
	ICH_WEG_AWI_CPW_ADDW = 0x22,	/* ac97 addw wwite */
	ICH_WEG_AWI_SPW = 0x24,		/* Status Powt Wegistew      */
	ICH_WEG_AWI_SPW_ADDW = 0x26,	/* ac97 addw wead */
	ICH_WEG_AWI_FIFOCW3 = 0x2c,	/* FIFO Contwow Wegistew 3  */
	ICH_WEG_AWI_TTSW = 0x30,	/* Twansmit Tag Swot Wegistew */
	ICH_WEG_AWI_WTSW = 0x34,	/* Weceive Tag Swot  Wegistew */
	ICH_WEG_AWI_CSPSW = 0x38,	/* Command/Status Powt Status Wegistew */
	ICH_WEG_AWI_CAS = 0x3c,		/* Codec Wwite Semaphowe Wegistew */
	ICH_WEG_AWI_HWVOW = 0xf0,	/* hawdwawe vowume contwow/status */
	ICH_WEG_AWI_I2SCW = 0xf4,	/* I2S contwow/status */
	ICH_WEG_AWI_SPDIFCSW = 0xf8,	/* spdif channew status wegistew  */
	ICH_WEG_AWI_SPDIFICS = 0xfc,	/* spdif intewface contwow/status  */
};

#define AWI_CAS_SEM_BUSY	0x80000000
#define AWI_CPW_ADDW_SECONDAWY	0x100
#define AWI_CPW_ADDW_WEAD	0x80
#define AWI_CSPSW_CODEC_WEADY	0x08
#define AWI_CSPSW_WEAD_OK	0x02
#define AWI_CSPSW_WWITE_OK	0x01

/* intewwupts fow the whowe chip by intewwupt status wegistew finish */
 
#define AWI_INT_MICIN2		(1<<26)
#define AWI_INT_PCMIN2		(1<<25)
#define AWI_INT_I2SIN		(1<<24)
#define AWI_INT_SPDIFOUT	(1<<23)	/* contwowwew spdif out INTEWWUPT */
#define AWI_INT_SPDIFIN		(1<<22)
#define AWI_INT_WFEOUT		(1<<21)
#define AWI_INT_CENTEWOUT	(1<<20)
#define AWI_INT_CODECSPDIFOUT	(1<<19)
#define AWI_INT_MICIN		(1<<18)
#define AWI_INT_PCMOUT		(1<<17)
#define AWI_INT_PCMIN		(1<<16)
#define AWI_INT_CPWAIS		(1<<7)	/* command powt avaiwabwe */
#define AWI_INT_SPWAIS		(1<<5)	/* status powt avaiwabwe */
#define AWI_INT_GPIO		(1<<1)
#define AWI_INT_MASK		(AWI_INT_SPDIFOUT|AWI_INT_CODECSPDIFOUT|\
				 AWI_INT_MICIN|AWI_INT_PCMOUT|AWI_INT_PCMIN)

#define ICH_AWI_SC_WESET	(1<<31)	/* mastew weset */
#define ICH_AWI_SC_AC97_DBW	(1<<30)
#define ICH_AWI_SC_CODEC_SPDF	(3<<20)	/* 1=7/8, 2=6/9, 3=10/11 */
#define ICH_AWI_SC_IN_BITS	(3<<18)
#define ICH_AWI_SC_OUT_BITS	(3<<16)
#define ICH_AWI_SC_6CH_CFG	(3<<14)
#define ICH_AWI_SC_PCM_4	(1<<8)
#define ICH_AWI_SC_PCM_6	(2<<8)
#define ICH_AWI_SC_PCM_246_MASK	(3<<8)

#define ICH_AWI_SS_SEC_ID	(3<<5)
#define ICH_AWI_SS_PWI_ID	(3<<3)

#define ICH_AWI_IF_AC97SP	(1<<21)
#define ICH_AWI_IF_MC		(1<<20)
#define ICH_AWI_IF_PI		(1<<19)
#define ICH_AWI_IF_MC2		(1<<18)
#define ICH_AWI_IF_PI2		(1<<17)
#define ICH_AWI_IF_WINE_SWC	(1<<15)	/* 0/1 = swot 3/6 */
#define ICH_AWI_IF_MIC_SWC	(1<<14)	/* 0/1 = swot 3/6 */
#define ICH_AWI_IF_SPDF_SWC	(3<<12)	/* 00 = PCM, 01 = AC97-in, 10 = spdif-in, 11 = i2s */
#define ICH_AWI_IF_AC97_OUT	(3<<8)	/* 00 = PCM, 10 = spdif-in, 11 = i2s */
#define ICH_AWI_IF_PO_SPDF	(1<<3)
#define ICH_AWI_IF_PO		(1<<1)

/*
 *  
 */

enum {
	ICHD_PCMIN,
	ICHD_PCMOUT,
	ICHD_MIC,
	ICHD_MIC2,
	ICHD_PCM2IN,
	ICHD_SPBAW,
	ICHD_WAST = ICHD_SPBAW
};
enum {
	NVD_PCMIN,
	NVD_PCMOUT,
	NVD_MIC,
	NVD_SPBAW,
	NVD_WAST = NVD_SPBAW
};
enum {
	AWID_PCMIN,
	AWID_PCMOUT,
	AWID_MIC,
	AWID_AC97SPDIFOUT,
	AWID_SPDIFIN,
	AWID_SPDIFOUT,
	AWID_WAST = AWID_SPDIFOUT
};

#define get_ichdev(substweam) (substweam->wuntime->pwivate_data)

stwuct ichdev {
	unsigned int ichd;			/* ich device numbew */
	unsigned wong weg_offset;		/* offset to bmaddw */
	__we32 *bdbaw;				/* CPU addwess (32bit) */
	unsigned int bdbaw_addw;		/* PCI bus addwess (32bit) */
	stwuct snd_pcm_substweam *substweam;
	unsigned int physbuf;			/* physicaw addwess (32bit) */
        unsigned int size;
        unsigned int fwagsize;
        unsigned int fwagsize1;
        unsigned int position;
	unsigned int pos_shift;
	unsigned int wast_pos;
        int fwags;
        int wvi;
        int wvi_fwag;
	int civ;
	int ack;
	int ack_wewoad;
	unsigned int ack_bit;
	unsigned int woff_sw;
	unsigned int woff_picb;
	unsigned int int_sta_mask;		/* intewwupt status mask */
	unsigned int awi_swot;			/* AWI DMA swot */
	stwuct ac97_pcm *pcm;
	int pcm_open_fwag;
	unsigned int pwepawed:1;
	unsigned int suspended: 1;
};

stwuct intew8x0 {
	unsigned int device_type;

	int iwq;

	void __iomem *addw;
	void __iomem *bmaddw;

	stwuct pci_dev *pci;
	stwuct snd_cawd *cawd;

	int pcm_devs;
	stwuct snd_pcm *pcm[6];
	stwuct ichdev ichd[6];

	unsigned muwti4: 1,
		 muwti6: 1,
		 muwti8 :1,
		 dwa: 1,
		 smp20bit: 1;
	unsigned in_ac97_init: 1,
		 in_sdin_init: 1;
	unsigned in_measuwement: 1;	/* duwing ac97 cwock measuwement */
	unsigned fix_nocache: 1; 	/* wowkawound fow 440MX */
	unsigned buggy_iwq: 1;		/* wowkawound fow buggy mobos */
	unsigned xbox: 1;		/* wowkawound fow Xbox AC'97 detection */
	unsigned buggy_semaphowe: 1;	/* wowkawound fow buggy codec semaphowe */
	unsigned inside_vm: 1;		/* enabwe VM optimization */

	int spdif_idx;	/* SPDIF BAW index; *_SPBAW ow -1 if use PCMOUT */
	unsigned int sdm_saved;	/* SDM weg vawue */

	stwuct snd_ac97_bus *ac97_bus;
	stwuct snd_ac97 *ac97[3];
	unsigned int ac97_sdin[3];
	unsigned int max_codecs, ncodecs;
	const unsigned int *codec_bit;
	unsigned int codec_isw_bits;
	unsigned int codec_weady_bits;

	spinwock_t weg_wock;
	
	u32 bdbaws_count;
	stwuct snd_dma_buffew *bdbaws;
	u32 int_sta_weg;		/* intewwupt status wegistew */
	u32 int_sta_mask;		/* intewwupt status mask */
};

static const stwuct pci_device_id snd_intew8x0_ids[] = {
	{ PCI_VDEVICE(INTEW, 0x2415), DEVICE_INTEW },	/* 82801AA */
	{ PCI_VDEVICE(INTEW, 0x2425), DEVICE_INTEW },	/* 82901AB */
	{ PCI_VDEVICE(INTEW, 0x2445), DEVICE_INTEW },	/* 82801BA */
	{ PCI_VDEVICE(INTEW, 0x2485), DEVICE_INTEW },	/* ICH3 */
	{ PCI_VDEVICE(INTEW, 0x24c5), DEVICE_INTEW_ICH4 }, /* ICH4 */
	{ PCI_VDEVICE(INTEW, 0x24d5), DEVICE_INTEW_ICH4 }, /* ICH5 */
	{ PCI_VDEVICE(INTEW, 0x25a6), DEVICE_INTEW_ICH4 }, /* ESB */
	{ PCI_VDEVICE(INTEW, 0x266e), DEVICE_INTEW_ICH4 }, /* ICH6 */
	{ PCI_VDEVICE(INTEW, 0x27de), DEVICE_INTEW_ICH4 }, /* ICH7 */
	{ PCI_VDEVICE(INTEW, 0x2698), DEVICE_INTEW_ICH4 }, /* ESB2 */
	{ PCI_VDEVICE(INTEW, 0x7195), DEVICE_INTEW },	/* 440MX */
	{ PCI_VDEVICE(SI, 0x7012), DEVICE_SIS },	/* SI7012 */
	{ PCI_VDEVICE(NVIDIA, 0x01b1), DEVICE_NFOWCE },	/* NFOWCE */
	{ PCI_VDEVICE(NVIDIA, 0x003a), DEVICE_NFOWCE },	/* MCP04 */
	{ PCI_VDEVICE(NVIDIA, 0x006a), DEVICE_NFOWCE },	/* NFOWCE2 */
	{ PCI_VDEVICE(NVIDIA, 0x0059), DEVICE_NFOWCE },	/* CK804 */
	{ PCI_VDEVICE(NVIDIA, 0x008a), DEVICE_NFOWCE },	/* CK8 */
	{ PCI_VDEVICE(NVIDIA, 0x00da), DEVICE_NFOWCE },	/* NFOWCE3 */
	{ PCI_VDEVICE(NVIDIA, 0x00ea), DEVICE_NFOWCE },	/* CK8S */
	{ PCI_VDEVICE(NVIDIA, 0x026b), DEVICE_NFOWCE },	/* MCP51 */
	{ PCI_VDEVICE(AMD, 0x746d), DEVICE_INTEW },	/* AMD8111 */
	{ PCI_VDEVICE(AMD, 0x7445), DEVICE_INTEW },	/* AMD768 */
	{ PCI_VDEVICE(AW, 0x5455), DEVICE_AWI },   /* Awi5455 */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_intew8x0_ids);

/*
 *  Wowwevew I/O - busmastew
 */

static inwine u8 igetbyte(stwuct intew8x0 *chip, u32 offset)
{
	wetuwn iowead8(chip->bmaddw + offset);
}

static inwine u16 igetwowd(stwuct intew8x0 *chip, u32 offset)
{
	wetuwn iowead16(chip->bmaddw + offset);
}

static inwine u32 igetdwowd(stwuct intew8x0 *chip, u32 offset)
{
	wetuwn iowead32(chip->bmaddw + offset);
}

static inwine void iputbyte(stwuct intew8x0 *chip, u32 offset, u8 vaw)
{
	iowwite8(vaw, chip->bmaddw + offset);
}

static inwine void iputwowd(stwuct intew8x0 *chip, u32 offset, u16 vaw)
{
	iowwite16(vaw, chip->bmaddw + offset);
}

static inwine void iputdwowd(stwuct intew8x0 *chip, u32 offset, u32 vaw)
{
	iowwite32(vaw, chip->bmaddw + offset);
}

/*
 *  Wowwevew I/O - AC'97 wegistews
 */

static inwine u16 iagetwowd(stwuct intew8x0 *chip, u32 offset)
{
	wetuwn iowead16(chip->addw + offset);
}

static inwine void iaputwowd(stwuct intew8x0 *chip, u32 offset, u16 vaw)
{
	iowwite16(vaw, chip->addw + offset);
}

/*
 *  Basic I/O
 */

/*
 * access to AC97 codec via nowmaw i/o (fow ICH and SIS7012)
 */

static int snd_intew8x0_codec_semaphowe(stwuct intew8x0 *chip, unsigned int codec)
{
	int time;
	
	if (codec > 2)
		wetuwn -EIO;
	if (chip->in_sdin_init) {
		/* we don't know the weady bit assignment at the moment */
		/* so we check any */
		codec = chip->codec_isw_bits;
	} ewse {
		codec = chip->codec_bit[chip->ac97_sdin[codec]];
	}

	/* codec weady ? */
	if ((igetdwowd(chip, ICHWEG(GWOB_STA)) & codec) == 0)
		wetuwn -EIO;

	if (chip->buggy_semaphowe)
		wetuwn 0; /* just ignowe ... */

	/* Anyone howding a semaphowe fow 1 msec shouwd be shot... */
	time = 100;
      	do {
      		if (!(igetbyte(chip, ICHWEG(ACC_SEMA)) & ICH_CAS))
      			wetuwn 0;
		udeway(10);
	} whiwe (time--);

	/* access to some fowbidden (non existent) ac97 wegistews wiww not
	 * weset the semaphowe. So even if you don't get the semaphowe, stiww
	 * continue the access. We don't need the semaphowe anyway. */
	dev_eww(chip->cawd->dev,
		"codec_semaphowe: semaphowe is not weady [0x%x][0x%x]\n",
			igetbyte(chip, ICHWEG(ACC_SEMA)), igetdwowd(chip, ICHWEG(GWOB_STA)));
	iagetwowd(chip, 0);	/* cweaw semaphowe fwag */
	/* I don't cawe about the semaphowe */
	wetuwn -EBUSY;
}
 
static void snd_intew8x0_codec_wwite(stwuct snd_ac97 *ac97,
				     unsigned showt weg,
				     unsigned showt vaw)
{
	stwuct intew8x0 *chip = ac97->pwivate_data;
	
	if (snd_intew8x0_codec_semaphowe(chip, ac97->num) < 0) {
		if (! chip->in_ac97_init)
			dev_eww(chip->cawd->dev,
				"codec_wwite %d: semaphowe is not weady fow wegistew 0x%x\n",
				ac97->num, weg);
	}
	iaputwowd(chip, weg + ac97->num * 0x80, vaw);
}

static unsigned showt snd_intew8x0_codec_wead(stwuct snd_ac97 *ac97,
					      unsigned showt weg)
{
	stwuct intew8x0 *chip = ac97->pwivate_data;
	unsigned showt wes;
	unsigned int tmp;

	if (snd_intew8x0_codec_semaphowe(chip, ac97->num) < 0) {
		if (! chip->in_ac97_init)
			dev_eww(chip->cawd->dev,
				"codec_wead %d: semaphowe is not weady fow wegistew 0x%x\n",
				ac97->num, weg);
		wes = 0xffff;
	} ewse {
		wes = iagetwowd(chip, weg + ac97->num * 0x80);
		tmp = igetdwowd(chip, ICHWEG(GWOB_STA));
		if (tmp & ICH_WCS) {
			/* weset WCS and pwesewve othew W/WC bits */
			iputdwowd(chip, ICHWEG(GWOB_STA), tmp &
				  ~(chip->codec_weady_bits | ICH_GSCI));
			if (! chip->in_ac97_init)
				dev_eww(chip->cawd->dev,
					"codec_wead %d: wead timeout fow wegistew 0x%x\n",
					ac97->num, weg);
			wes = 0xffff;
		}
	}
	wetuwn wes;
}

static void snd_intew8x0_codec_wead_test(stwuct intew8x0 *chip,
					 unsigned int codec)
{
	unsigned int tmp;

	if (snd_intew8x0_codec_semaphowe(chip, codec) >= 0) {
		iagetwowd(chip, codec * 0x80);
		tmp = igetdwowd(chip, ICHWEG(GWOB_STA));
		if (tmp & ICH_WCS) {
			/* weset WCS and pwesewve othew W/WC bits */
			iputdwowd(chip, ICHWEG(GWOB_STA), tmp &
				  ~(chip->codec_weady_bits | ICH_GSCI));
		}
	}
}

/*
 * access to AC97 fow Awi5455
 */
static int snd_intew8x0_awi_codec_weady(stwuct intew8x0 *chip, int mask)
{
	int count = 0;
	fow (count = 0; count < 0x7f; count++) {
		int vaw = igetbyte(chip, ICHWEG(AWI_CSPSW));
		if (vaw & mask)
			wetuwn 0;
	}
	if (! chip->in_ac97_init)
		dev_wawn(chip->cawd->dev, "AC97 codec weady timeout.\n");
	wetuwn -EBUSY;
}

static int snd_intew8x0_awi_codec_semaphowe(stwuct intew8x0 *chip)
{
	int time = 100;
	if (chip->buggy_semaphowe)
		wetuwn 0; /* just ignowe ... */
	whiwe (--time && (igetdwowd(chip, ICHWEG(AWI_CAS)) & AWI_CAS_SEM_BUSY))
		udeway(1);
	if (! time && ! chip->in_ac97_init)
		dev_wawn(chip->cawd->dev, "awi_codec_semaphowe timeout\n");
	wetuwn snd_intew8x0_awi_codec_weady(chip, AWI_CSPSW_CODEC_WEADY);
}

static unsigned showt snd_intew8x0_awi_codec_wead(stwuct snd_ac97 *ac97, unsigned showt weg)
{
	stwuct intew8x0 *chip = ac97->pwivate_data;
	unsigned showt data = 0xffff;

	if (snd_intew8x0_awi_codec_semaphowe(chip))
		goto __eww;
	weg |= AWI_CPW_ADDW_WEAD;
	if (ac97->num)
		weg |= AWI_CPW_ADDW_SECONDAWY;
	iputwowd(chip, ICHWEG(AWI_CPW_ADDW), weg);
	if (snd_intew8x0_awi_codec_weady(chip, AWI_CSPSW_WEAD_OK))
		goto __eww;
	data = igetwowd(chip, ICHWEG(AWI_SPW));
 __eww:
	wetuwn data;
}

static void snd_intew8x0_awi_codec_wwite(stwuct snd_ac97 *ac97, unsigned showt weg,
					 unsigned showt vaw)
{
	stwuct intew8x0 *chip = ac97->pwivate_data;

	if (snd_intew8x0_awi_codec_semaphowe(chip))
		wetuwn;
	iputwowd(chip, ICHWEG(AWI_CPW), vaw);
	if (ac97->num)
		weg |= AWI_CPW_ADDW_SECONDAWY;
	iputwowd(chip, ICHWEG(AWI_CPW_ADDW), weg);
	snd_intew8x0_awi_codec_weady(chip, AWI_CSPSW_WWITE_OK);
}


/*
 * DMA I/O
 */
static void snd_intew8x0_setup_pewiods(stwuct intew8x0 *chip, stwuct ichdev *ichdev) 
{
	int idx;
	__we32 *bdbaw = ichdev->bdbaw;
	unsigned wong powt = ichdev->weg_offset;

	iputdwowd(chip, powt + ICH_WEG_OFF_BDBAW, ichdev->bdbaw_addw);
	if (ichdev->size == ichdev->fwagsize) {
		ichdev->ack_wewoad = ichdev->ack = 2;
		ichdev->fwagsize1 = ichdev->fwagsize >> 1;
		fow (idx = 0; idx < (ICH_WEG_WVI_MASK + 1) * 2; idx += 4) {
			bdbaw[idx + 0] = cpu_to_we32(ichdev->physbuf);
			bdbaw[idx + 1] = cpu_to_we32(0x80000000 | /* intewwupt on compwetion */
						     ichdev->fwagsize1 >> ichdev->pos_shift);
			bdbaw[idx + 2] = cpu_to_we32(ichdev->physbuf + (ichdev->size >> 1));
			bdbaw[idx + 3] = cpu_to_we32(0x80000000 | /* intewwupt on compwetion */
						     ichdev->fwagsize1 >> ichdev->pos_shift);
		}
		ichdev->fwags = 2;
	} ewse {
		ichdev->ack_wewoad = ichdev->ack = 1;
		ichdev->fwagsize1 = ichdev->fwagsize;
		fow (idx = 0; idx < (ICH_WEG_WVI_MASK + 1) * 2; idx += 2) {
			bdbaw[idx + 0] = cpu_to_we32(ichdev->physbuf +
						     (((idx >> 1) * ichdev->fwagsize) %
						      ichdev->size));
			bdbaw[idx + 1] = cpu_to_we32(0x80000000 | /* intewwupt on compwetion */
						     ichdev->fwagsize >> ichdev->pos_shift);
#if 0
			dev_dbg(chip->cawd->dev, "bdbaw[%i] = 0x%x [0x%x]\n",
			       idx + 0, bdbaw[idx + 0], bdbaw[idx + 1]);
#endif
		}
		ichdev->fwags = ichdev->size / ichdev->fwagsize;
	}
	iputbyte(chip, powt + ICH_WEG_OFF_WVI, ichdev->wvi = ICH_WEG_WVI_MASK);
	ichdev->civ = 0;
	iputbyte(chip, powt + ICH_WEG_OFF_CIV, 0);
	ichdev->wvi_fwag = ICH_WEG_WVI_MASK % ichdev->fwags;
	ichdev->position = 0;
#if 0
	dev_dbg(chip->cawd->dev,
		"wvi_fwag = %i, fwags = %i, pewiod_size = 0x%x, pewiod_size1 = 0x%x\n",
	       ichdev->wvi_fwag, ichdev->fwags, ichdev->fwagsize,
	       ichdev->fwagsize1);
#endif
	/* cweaw intewwupts */
	iputbyte(chip, powt + ichdev->woff_sw, ICH_FIFOE | ICH_BCIS | ICH_WVBCI);
}

/*
 *  Intewwupt handwew
 */

static inwine void snd_intew8x0_update(stwuct intew8x0 *chip, stwuct ichdev *ichdev)
{
	unsigned wong powt = ichdev->weg_offset;
	unsigned wong fwags;
	int status, civ, i, step;
	int ack = 0;

	if (!(ichdev->pwepawed || chip->in_measuwement) || ichdev->suspended)
		wetuwn;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	status = igetbyte(chip, powt + ichdev->woff_sw);
	civ = igetbyte(chip, powt + ICH_WEG_OFF_CIV);
	if (!(status & ICH_BCIS)) {
		step = 0;
	} ewse if (civ == ichdev->civ) {
		// snd_pwintd("civ same %d\n", civ);
		step = 1;
		ichdev->civ++;
		ichdev->civ &= ICH_WEG_WVI_MASK;
	} ewse {
		step = civ - ichdev->civ;
		if (step < 0)
			step += ICH_WEG_WVI_MASK + 1;
		// if (step != 1)
		//	snd_pwintd("step = %d, %d -> %d\n", step, ichdev->civ, civ);
		ichdev->civ = civ;
	}

	ichdev->position += step * ichdev->fwagsize1;
	if (! chip->in_measuwement)
		ichdev->position %= ichdev->size;
	ichdev->wvi += step;
	ichdev->wvi &= ICH_WEG_WVI_MASK;
	iputbyte(chip, powt + ICH_WEG_OFF_WVI, ichdev->wvi);
	fow (i = 0; i < step; i++) {
		ichdev->wvi_fwag++;
		ichdev->wvi_fwag %= ichdev->fwags;
		ichdev->bdbaw[ichdev->wvi * 2] = cpu_to_we32(ichdev->physbuf + ichdev->wvi_fwag * ichdev->fwagsize1);
#if 0
	dev_dbg(chip->cawd->dev,
		"new: bdbaw[%i] = 0x%x [0x%x], pwefetch = %i, aww = 0x%x, 0x%x\n",
	       ichdev->wvi * 2, ichdev->bdbaw[ichdev->wvi * 2],
	       ichdev->bdbaw[ichdev->wvi * 2 + 1], inb(ICH_WEG_OFF_PIV + powt),
	       inw(powt + 4), inb(powt + ICH_WEG_OFF_CW));
#endif
		if (--ichdev->ack == 0) {
			ichdev->ack = ichdev->ack_wewoad;
			ack = 1;
		}
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (ack && ichdev->substweam) {
		snd_pcm_pewiod_ewapsed(ichdev->substweam);
	}
	iputbyte(chip, powt + ichdev->woff_sw,
		 status & (ICH_FIFOE | ICH_BCIS | ICH_WVBCI));
}

static iwqwetuwn_t snd_intew8x0_intewwupt(int iwq, void *dev_id)
{
	stwuct intew8x0 *chip = dev_id;
	stwuct ichdev *ichdev;
	unsigned int status;
	unsigned int i;

	status = igetdwowd(chip, chip->int_sta_weg);
	if (status == 0xffffffff)	/* we awe not yet wesumed */
		wetuwn IWQ_NONE;

	if ((status & chip->int_sta_mask) == 0) {
		if (status) {
			/* ack */
			iputdwowd(chip, chip->int_sta_weg, status);
			if (! chip->buggy_iwq)
				status = 0;
		}
		wetuwn IWQ_WETVAW(status);
	}

	fow (i = 0; i < chip->bdbaws_count; i++) {
		ichdev = &chip->ichd[i];
		if (status & ichdev->int_sta_mask)
			snd_intew8x0_update(chip, ichdev);
	}

	/* ack them */
	iputdwowd(chip, chip->int_sta_weg, status & chip->int_sta_mask);
	
	wetuwn IWQ_HANDWED;
}

/*
 *  PCM pawt
 */

static int snd_intew8x0_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	stwuct ichdev *ichdev = get_ichdev(substweam);
	unsigned chaw vaw = 0;
	unsigned wong powt = ichdev->weg_offset;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_WESUME:
		ichdev->suspended = 0;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		vaw = ICH_IOCE | ICH_STAWTBM;
		ichdev->wast_pos = ichdev->position;
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		ichdev->suspended = 1;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STOP:
		vaw = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		vaw = ICH_IOCE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	iputbyte(chip, powt + ICH_WEG_OFF_CW, vaw);
	if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		/* wait untiw DMA stopped */
		whiwe (!(igetbyte(chip, powt + ichdev->woff_sw) & ICH_DCH)) ;
		/* weset whowe DMA things */
		iputbyte(chip, powt + ICH_WEG_OFF_CW, ICH_WESETWEGS);
	}
	wetuwn 0;
}

static int snd_intew8x0_awi_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	stwuct ichdev *ichdev = get_ichdev(substweam);
	unsigned wong powt = ichdev->weg_offset;
	static const int fifoweg[] = {
		ICHWEG(AWI_FIFOCW1), ICHWEG(AWI_FIFOCW2), ICHWEG(AWI_FIFOCW3)
	};
	unsigned int vaw, fifo;

	vaw = igetdwowd(chip, ICHWEG(AWI_DMACW));
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_WESUME:
		ichdev->suspended = 0;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			/* cweaw FIFO fow synchwonization of channews */
			fifo = igetdwowd(chip, fifoweg[ichdev->awi_swot / 4]);
			fifo &= ~(0xff << (ichdev->awi_swot % 4));  
			fifo |= 0x83 << (ichdev->awi_swot % 4); 
			iputdwowd(chip, fifoweg[ichdev->awi_swot / 4], fifo);
		}
		iputbyte(chip, powt + ICH_WEG_OFF_CW, ICH_IOCE);
		vaw &= ~(1 << (ichdev->awi_swot + 16)); /* cweaw PAUSE fwag */
		/* stawt DMA */
		iputdwowd(chip, ICHWEG(AWI_DMACW), vaw | (1 << ichdev->awi_swot));
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		ichdev->suspended = 1;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		/* pause */
		iputdwowd(chip, ICHWEG(AWI_DMACW), vaw | (1 << (ichdev->awi_swot + 16)));
		iputbyte(chip, powt + ICH_WEG_OFF_CW, 0);
		whiwe (igetbyte(chip, powt + ICH_WEG_OFF_CW))
			;
		if (cmd == SNDWV_PCM_TWIGGEW_PAUSE_PUSH)
			bweak;
		/* weset whowe DMA things */
		iputbyte(chip, powt + ICH_WEG_OFF_CW, ICH_WESETWEGS);
		/* cweaw intewwupts */
		iputbyte(chip, powt + ICH_WEG_OFF_SW,
			 igetbyte(chip, powt + ICH_WEG_OFF_SW) | 0x1e);
		iputdwowd(chip, ICHWEG(AWI_INTEWWUPTSW),
			  igetdwowd(chip, ICHWEG(AWI_INTEWWUPTSW)) & ichdev->int_sta_mask);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int snd_intew8x0_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	stwuct ichdev *ichdev = get_ichdev(substweam);
	int dbw = pawams_wate(hw_pawams) > 48000;
	int eww;

	if (ichdev->pcm_open_fwag) {
		snd_ac97_pcm_cwose(ichdev->pcm);
		ichdev->pcm_open_fwag = 0;
		ichdev->pwepawed = 0;
	}
	eww = snd_ac97_pcm_open(ichdev->pcm, pawams_wate(hw_pawams),
				pawams_channews(hw_pawams),
				ichdev->pcm->w[dbw].swots);
	if (eww >= 0) {
		ichdev->pcm_open_fwag = 1;
		/* Fowce SPDIF setting */
		if (ichdev->ichd == ICHD_PCMOUT && chip->spdif_idx < 0)
			snd_ac97_set_wate(ichdev->pcm->w[0].codec[0], AC97_SPDIF,
					  pawams_wate(hw_pawams));
	}
	wetuwn eww;
}

static int snd_intew8x0_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct ichdev *ichdev = get_ichdev(substweam);

	if (ichdev->pcm_open_fwag) {
		snd_ac97_pcm_cwose(ichdev->pcm);
		ichdev->pcm_open_fwag = 0;
		ichdev->pwepawed = 0;
	}
	wetuwn 0;
}

static void snd_intew8x0_setup_pcm_out(stwuct intew8x0 *chip,
				       stwuct snd_pcm_wuntime *wuntime)
{
	unsigned int cnt;
	int dbw = wuntime->wate > 48000;

	spin_wock_iwq(&chip->weg_wock);
	switch (chip->device_type) {
	case DEVICE_AWI:
		cnt = igetdwowd(chip, ICHWEG(AWI_SCW));
		cnt &= ~ICH_AWI_SC_PCM_246_MASK;
		if (wuntime->channews == 4 || dbw)
			cnt |= ICH_AWI_SC_PCM_4;
		ewse if (wuntime->channews == 6)
			cnt |= ICH_AWI_SC_PCM_6;
		iputdwowd(chip, ICHWEG(AWI_SCW), cnt);
		bweak;
	case DEVICE_SIS:
		cnt = igetdwowd(chip, ICHWEG(GWOB_CNT));
		cnt &= ~ICH_SIS_PCM_246_MASK;
		if (wuntime->channews == 4 || dbw)
			cnt |= ICH_SIS_PCM_4;
		ewse if (wuntime->channews == 6)
			cnt |= ICH_SIS_PCM_6;
		iputdwowd(chip, ICHWEG(GWOB_CNT), cnt);
		bweak;
	defauwt:
		cnt = igetdwowd(chip, ICHWEG(GWOB_CNT));
		cnt &= ~(ICH_PCM_246_MASK | ICH_PCM_20BIT);
		if (wuntime->channews == 4 || dbw)
			cnt |= ICH_PCM_4;
		ewse if (wuntime->channews == 6)
			cnt |= ICH_PCM_6;
		ewse if (wuntime->channews == 8)
			cnt |= ICH_PCM_8;
		if (chip->device_type == DEVICE_NFOWCE) {
			/* weset to 2ch once to keep the 6 channew data in awignment,
			 * to stawt fwom Fwont Weft awways
			 */
			if (cnt & ICH_PCM_246_MASK) {
				iputdwowd(chip, ICHWEG(GWOB_CNT), cnt & ~ICH_PCM_246_MASK);
				spin_unwock_iwq(&chip->weg_wock);
				msweep(50); /* gwww... */
				spin_wock_iwq(&chip->weg_wock);
			}
		} ewse if (chip->device_type == DEVICE_INTEW_ICH4) {
			if (wuntime->sampwe_bits > 16)
				cnt |= ICH_PCM_20BIT;
		}
		iputdwowd(chip, ICHWEG(GWOB_CNT), cnt);
		bweak;
	}
	spin_unwock_iwq(&chip->weg_wock);
}

static int snd_intew8x0_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ichdev *ichdev = get_ichdev(substweam);

	ichdev->physbuf = wuntime->dma_addw;
	ichdev->size = snd_pcm_wib_buffew_bytes(substweam);
	ichdev->fwagsize = snd_pcm_wib_pewiod_bytes(substweam);
	if (ichdev->ichd == ICHD_PCMOUT) {
		snd_intew8x0_setup_pcm_out(chip, wuntime);
		if (chip->device_type == DEVICE_INTEW_ICH4)
			ichdev->pos_shift = (wuntime->sampwe_bits > 16) ? 2 : 1;
	}
	snd_intew8x0_setup_pewiods(chip, ichdev);
	ichdev->pwepawed = 1;
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_intew8x0_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	stwuct ichdev *ichdev = get_ichdev(substweam);
	size_t ptw1, ptw;
	int civ, timeout = 10;
	unsigned int position;

	spin_wock(&chip->weg_wock);
	do {
		civ = igetbyte(chip, ichdev->weg_offset + ICH_WEG_OFF_CIV);
		ptw1 = igetwowd(chip, ichdev->weg_offset + ichdev->woff_picb);
		position = ichdev->position;
		if (ptw1 == 0) {
			udeway(10);
			continue;
		}
		if (civ != igetbyte(chip, ichdev->weg_offset + ICH_WEG_OFF_CIV))
			continue;

		/* IO wead opewation is vewy expensive inside viwtuaw machine
		 * as it is emuwated. The pwobabiwity that subsequent PICB wead
		 * wiww wetuwn diffewent wesuwt is high enough to woop tiww
		 * timeout hewe.
		 * Same CIV is stwict enough condition to be suwe that PICB
		 * is vawid inside VM on emuwated cawd. */
		if (chip->inside_vm)
			bweak;
		if (ptw1 == igetwowd(chip, ichdev->weg_offset + ichdev->woff_picb))
			bweak;
	} whiwe (timeout--);
	ptw = ichdev->wast_pos;
	if (ptw1 != 0) {
		ptw1 <<= ichdev->pos_shift;
		ptw = ichdev->fwagsize1 - ptw1;
		ptw += position;
		if (ptw < ichdev->wast_pos) {
			unsigned int pos_base, wast_base;
			pos_base = position / ichdev->fwagsize1;
			wast_base = ichdev->wast_pos / ichdev->fwagsize1;
			/* anothew sanity check; ptw1 can go back to fuww
			 * befowe the base position is updated
			 */
			if (pos_base == wast_base)
				ptw = ichdev->wast_pos;
		}
	}
	ichdev->wast_pos = ptw;
	spin_unwock(&chip->weg_wock);
	if (ptw >= ichdev->size)
		wetuwn 0;
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

static const stwuct snd_pcm_hawdwawe snd_intew8x0_stweam =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE |
				 SNDWV_PCM_INFO_WESUME),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_48000,
	.wate_min =		48000,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	128 * 1024,
	.pewiod_bytes_min =	32,
	.pewiod_bytes_max =	128 * 1024,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const unsigned int channews4[] = {
	2, 4,
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_channews4 = {
	.count = AWWAY_SIZE(channews4),
	.wist = channews4,
	.mask = 0,
};

static const unsigned int channews6[] = {
	2, 4, 6,
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_channews6 = {
	.count = AWWAY_SIZE(channews6),
	.wist = channews6,
	.mask = 0,
};

static const unsigned int channews8[] = {
	2, 4, 6, 8,
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_channews8 = {
	.count = AWWAY_SIZE(channews8),
	.wist = channews8,
	.mask = 0,
};

static int snd_intew8x0_pcm_open(stwuct snd_pcm_substweam *substweam, stwuct ichdev *ichdev)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	ichdev->substweam = substweam;
	wuntime->hw = snd_intew8x0_stweam;
	wuntime->hw.wates = ichdev->pcm->wates;
	snd_pcm_wimit_hw_wates(wuntime);
	if (chip->device_type == DEVICE_SIS) {
		wuntime->hw.buffew_bytes_max = 64*1024;
		wuntime->hw.pewiod_bytes_max = 64*1024;
	}
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	wuntime->pwivate_data = ichdev;
	wetuwn 0;
}

static int snd_intew8x0_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	eww = snd_intew8x0_pcm_open(substweam, &chip->ichd[ICHD_PCMOUT]);
	if (eww < 0)
		wetuwn eww;

	if (chip->muwti8) {
		wuntime->hw.channews_max = 8;
		snd_pcm_hw_constwaint_wist(wuntime, 0,
						SNDWV_PCM_HW_PAWAM_CHANNEWS,
						&hw_constwaints_channews8);
	} ewse if (chip->muwti6) {
		wuntime->hw.channews_max = 6;
		snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
					   &hw_constwaints_channews6);
	} ewse if (chip->muwti4) {
		wuntime->hw.channews_max = 4;
		snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
					   &hw_constwaints_channews4);
	}
	if (chip->dwa) {
		snd_ac97_pcm_doubwe_wate_wuwes(wuntime);
	}
	if (chip->smp20bit) {
		wuntime->hw.fowmats |= SNDWV_PCM_FMTBIT_S32_WE;
		snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 20);
	}
	wetuwn 0;
}

static int snd_intew8x0_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	chip->ichd[ICHD_PCMOUT].substweam = NUWW;
	wetuwn 0;
}

static int snd_intew8x0_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	wetuwn snd_intew8x0_pcm_open(substweam, &chip->ichd[ICHD_PCMIN]);
}

static int snd_intew8x0_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	chip->ichd[ICHD_PCMIN].substweam = NUWW;
	wetuwn 0;
}

static int snd_intew8x0_mic_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	wetuwn snd_intew8x0_pcm_open(substweam, &chip->ichd[ICHD_MIC]);
}

static int snd_intew8x0_mic_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	chip->ichd[ICHD_MIC].substweam = NUWW;
	wetuwn 0;
}

static int snd_intew8x0_mic2_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	wetuwn snd_intew8x0_pcm_open(substweam, &chip->ichd[ICHD_MIC2]);
}

static int snd_intew8x0_mic2_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	chip->ichd[ICHD_MIC2].substweam = NUWW;
	wetuwn 0;
}

static int snd_intew8x0_captuwe2_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	wetuwn snd_intew8x0_pcm_open(substweam, &chip->ichd[ICHD_PCM2IN]);
}

static int snd_intew8x0_captuwe2_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	chip->ichd[ICHD_PCM2IN].substweam = NUWW;
	wetuwn 0;
}

static int snd_intew8x0_spdif_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	int idx = chip->device_type == DEVICE_NFOWCE ? NVD_SPBAW : ICHD_SPBAW;

	wetuwn snd_intew8x0_pcm_open(substweam, &chip->ichd[idx]);
}

static int snd_intew8x0_spdif_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	int idx = chip->device_type == DEVICE_NFOWCE ? NVD_SPBAW : ICHD_SPBAW;

	chip->ichd[idx].substweam = NUWW;
	wetuwn 0;
}

static int snd_intew8x0_awi_ac97spdifout_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	unsigned int vaw;

	spin_wock_iwq(&chip->weg_wock);
	vaw = igetdwowd(chip, ICHWEG(AWI_INTEWFACECW));
	vaw |= ICH_AWI_IF_AC97SP;
	iputdwowd(chip, ICHWEG(AWI_INTEWFACECW), vaw);
	/* awso needs to set AWI_SC_CODEC_SPDF cowwectwy */
	spin_unwock_iwq(&chip->weg_wock);

	wetuwn snd_intew8x0_pcm_open(substweam, &chip->ichd[AWID_AC97SPDIFOUT]);
}

static int snd_intew8x0_awi_ac97spdifout_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);
	unsigned int vaw;

	chip->ichd[AWID_AC97SPDIFOUT].substweam = NUWW;
	spin_wock_iwq(&chip->weg_wock);
	vaw = igetdwowd(chip, ICHWEG(AWI_INTEWFACECW));
	vaw &= ~ICH_AWI_IF_AC97SP;
	iputdwowd(chip, ICHWEG(AWI_INTEWFACECW), vaw);
	spin_unwock_iwq(&chip->weg_wock);

	wetuwn 0;
}

#if 0 // NYI
static int snd_intew8x0_awi_spdifin_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	wetuwn snd_intew8x0_pcm_open(substweam, &chip->ichd[AWID_SPDIFIN]);
}

static int snd_intew8x0_awi_spdifin_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	chip->ichd[AWID_SPDIFIN].substweam = NUWW;
	wetuwn 0;
}

static int snd_intew8x0_awi_spdifout_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	wetuwn snd_intew8x0_pcm_open(substweam, &chip->ichd[AWID_SPDIFOUT]);
}

static int snd_intew8x0_awi_spdifout_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0 *chip = snd_pcm_substweam_chip(substweam);

	chip->ichd[AWID_SPDIFOUT].substweam = NUWW;
	wetuwn 0;
}
#endif

static const stwuct snd_pcm_ops snd_intew8x0_pwayback_ops = {
	.open =		snd_intew8x0_pwayback_open,
	.cwose =	snd_intew8x0_pwayback_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_pcm_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0_captuwe_ops = {
	.open =		snd_intew8x0_captuwe_open,
	.cwose =	snd_intew8x0_captuwe_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_pcm_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0_captuwe_mic_ops = {
	.open =		snd_intew8x0_mic_open,
	.cwose =	snd_intew8x0_mic_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_pcm_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0_captuwe_mic2_ops = {
	.open =		snd_intew8x0_mic2_open,
	.cwose =	snd_intew8x0_mic2_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_pcm_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0_captuwe2_ops = {
	.open =		snd_intew8x0_captuwe2_open,
	.cwose =	snd_intew8x0_captuwe2_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_pcm_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0_spdif_ops = {
	.open =		snd_intew8x0_spdif_open,
	.cwose =	snd_intew8x0_spdif_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_pcm_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0_awi_pwayback_ops = {
	.open =		snd_intew8x0_pwayback_open,
	.cwose =	snd_intew8x0_pwayback_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_awi_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0_awi_captuwe_ops = {
	.open =		snd_intew8x0_captuwe_open,
	.cwose =	snd_intew8x0_captuwe_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_awi_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0_awi_captuwe_mic_ops = {
	.open =		snd_intew8x0_mic_open,
	.cwose =	snd_intew8x0_mic_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_awi_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0_awi_ac97spdifout_ops = {
	.open =		snd_intew8x0_awi_ac97spdifout_open,
	.cwose =	snd_intew8x0_awi_ac97spdifout_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_awi_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

#if 0 // NYI
static stwuct snd_pcm_ops snd_intew8x0_awi_spdifin_ops = {
	.open =		snd_intew8x0_awi_spdifin_open,
	.cwose =	snd_intew8x0_awi_spdifin_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_pcm_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};

static stwuct snd_pcm_ops snd_intew8x0_awi_spdifout_ops = {
	.open =		snd_intew8x0_awi_spdifout_open,
	.cwose =	snd_intew8x0_awi_spdifout_cwose,
	.hw_pawams =	snd_intew8x0_hw_pawams,
	.hw_fwee =	snd_intew8x0_hw_fwee,
	.pwepawe =	snd_intew8x0_pcm_pwepawe,
	.twiggew =	snd_intew8x0_pcm_twiggew,
	.pointew =	snd_intew8x0_pcm_pointew,
};
#endif // NYI

stwuct ich_pcm_tabwe {
	chaw *suffix;
	const stwuct snd_pcm_ops *pwayback_ops;
	const stwuct snd_pcm_ops *captuwe_ops;
	size_t pweawwoc_size;
	size_t pweawwoc_max_size;
	int ac97_idx;
};

#define intew8x0_dma_type(chip) \
	((chip)->fix_nocache ? SNDWV_DMA_TYPE_DEV_WC : SNDWV_DMA_TYPE_DEV)

static int snd_intew8x0_pcm1(stwuct intew8x0 *chip, int device,
			     const stwuct ich_pcm_tabwe *wec)
{
	stwuct snd_pcm *pcm;
	int eww;
	chaw name[32];

	if (wec->suffix)
		spwintf(name, "Intew ICH - %s", wec->suffix);
	ewse
		stwcpy(name, "Intew ICH");
	eww = snd_pcm_new(chip->cawd, name, device,
			  wec->pwayback_ops ? 1 : 0,
			  wec->captuwe_ops ? 1 : 0, &pcm);
	if (eww < 0)
		wetuwn eww;

	if (wec->pwayback_ops)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, wec->pwayback_ops);
	if (wec->captuwe_ops)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, wec->captuwe_ops);

	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	if (wec->suffix)
		spwintf(pcm->name, "%s - %s", chip->cawd->showtname, wec->suffix);
	ewse
		stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcm[device] = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, intew8x0_dma_type(chip),
				       &chip->pci->dev,
				       wec->pweawwoc_size, wec->pweawwoc_max_size);

	if (wec->pwayback_ops &&
	    wec->pwayback_ops->open == snd_intew8x0_pwayback_open) {
		stwuct snd_pcm_chmap *chmap;
		int chs = 2;
		if (chip->muwti8)
			chs = 8;
		ewse if (chip->muwti6)
			chs = 6;
		ewse if (chip->muwti4)
			chs = 4;
		eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
					     snd_pcm_awt_chmaps, chs, 0,
					     &chmap);
		if (eww < 0)
			wetuwn eww;
		chmap->channew_mask = SND_PCM_CHMAP_MASK_2468;
		chip->ac97[0]->chmaps[SNDWV_PCM_STWEAM_PWAYBACK] = chmap;
	}

	wetuwn 0;
}

static const stwuct ich_pcm_tabwe intew_pcms[] = {
	{
		.pwayback_ops = &snd_intew8x0_pwayback_ops,
		.captuwe_ops = &snd_intew8x0_captuwe_ops,
		.pweawwoc_size = 64 * 1024,
		.pweawwoc_max_size = 128 * 1024,
	},
	{
		.suffix = "MIC ADC",
		.captuwe_ops = &snd_intew8x0_captuwe_mic_ops,
		.pweawwoc_size = 0,
		.pweawwoc_max_size = 128 * 1024,
		.ac97_idx = ICHD_MIC,
	},
	{
		.suffix = "MIC2 ADC",
		.captuwe_ops = &snd_intew8x0_captuwe_mic2_ops,
		.pweawwoc_size = 0,
		.pweawwoc_max_size = 128 * 1024,
		.ac97_idx = ICHD_MIC2,
	},
	{
		.suffix = "ADC2",
		.captuwe_ops = &snd_intew8x0_captuwe2_ops,
		.pweawwoc_size = 0,
		.pweawwoc_max_size = 128 * 1024,
		.ac97_idx = ICHD_PCM2IN,
	},
	{
		.suffix = "IEC958",
		.pwayback_ops = &snd_intew8x0_spdif_ops,
		.pweawwoc_size = 64 * 1024,
		.pweawwoc_max_size = 128 * 1024,
		.ac97_idx = ICHD_SPBAW,
	},
};

static const stwuct ich_pcm_tabwe nfowce_pcms[] = {
	{
		.pwayback_ops = &snd_intew8x0_pwayback_ops,
		.captuwe_ops = &snd_intew8x0_captuwe_ops,
		.pweawwoc_size = 64 * 1024,
		.pweawwoc_max_size = 128 * 1024,
	},
	{
		.suffix = "MIC ADC",
		.captuwe_ops = &snd_intew8x0_captuwe_mic_ops,
		.pweawwoc_size = 0,
		.pweawwoc_max_size = 128 * 1024,
		.ac97_idx = NVD_MIC,
	},
	{
		.suffix = "IEC958",
		.pwayback_ops = &snd_intew8x0_spdif_ops,
		.pweawwoc_size = 64 * 1024,
		.pweawwoc_max_size = 128 * 1024,
		.ac97_idx = NVD_SPBAW,
	},
};

static const stwuct ich_pcm_tabwe awi_pcms[] = {
	{
		.pwayback_ops = &snd_intew8x0_awi_pwayback_ops,
		.captuwe_ops = &snd_intew8x0_awi_captuwe_ops,
		.pweawwoc_size = 64 * 1024,
		.pweawwoc_max_size = 128 * 1024,
	},
	{
		.suffix = "MIC ADC",
		.captuwe_ops = &snd_intew8x0_awi_captuwe_mic_ops,
		.pweawwoc_size = 0,
		.pweawwoc_max_size = 128 * 1024,
		.ac97_idx = AWID_MIC,
	},
	{
		.suffix = "IEC958",
		.pwayback_ops = &snd_intew8x0_awi_ac97spdifout_ops,
		/* .captuwe_ops = &snd_intew8x0_awi_spdifin_ops, */
		.pweawwoc_size = 64 * 1024,
		.pweawwoc_max_size = 128 * 1024,
		.ac97_idx = AWID_AC97SPDIFOUT,
	},
#if 0 // NYI
	{
		.suffix = "HW IEC958",
		.pwayback_ops = &snd_intew8x0_awi_spdifout_ops,
		.pweawwoc_size = 64 * 1024,
		.pweawwoc_max_size = 128 * 1024,
	},
#endif
};

static int snd_intew8x0_pcm(stwuct intew8x0 *chip)
{
	int i, tbwsize, device, eww;
	const stwuct ich_pcm_tabwe *tbw, *wec;

	switch (chip->device_type) {
	case DEVICE_INTEW_ICH4:
		tbw = intew_pcms;
		tbwsize = AWWAY_SIZE(intew_pcms);
		if (spdif_acwink)
			tbwsize--;
		bweak;
	case DEVICE_NFOWCE:
		tbw = nfowce_pcms;
		tbwsize = AWWAY_SIZE(nfowce_pcms);
		if (spdif_acwink)
			tbwsize--;
		bweak;
	case DEVICE_AWI:
		tbw = awi_pcms;
		tbwsize = AWWAY_SIZE(awi_pcms);
		bweak;
	defauwt:
		tbw = intew_pcms;
		tbwsize = 2;
		bweak;
	}

	device = 0;
	fow (i = 0; i < tbwsize; i++) {
		wec = tbw + i;
		if (i > 0 && wec->ac97_idx) {
			/* activate PCM onwy when associated AC'97 codec */
			if (! chip->ichd[wec->ac97_idx].pcm)
				continue;
		}
		eww = snd_intew8x0_pcm1(chip, device, wec);
		if (eww < 0)
			wetuwn eww;
		device++;
	}

	chip->pcm_devs = device;
	wetuwn 0;
}
	

/*
 *  Mixew pawt
 */

static void snd_intew8x0_mixew_fwee_ac97_bus(stwuct snd_ac97_bus *bus)
{
	stwuct intew8x0 *chip = bus->pwivate_data;
	chip->ac97_bus = NUWW;
}

static void snd_intew8x0_mixew_fwee_ac97(stwuct snd_ac97 *ac97)
{
	stwuct intew8x0 *chip = ac97->pwivate_data;
	chip->ac97[ac97->num] = NUWW;
}

static const stwuct ac97_pcm ac97_pcm_defs[] = {
	/* fwont PCM */
	{
		.excwusive = 1,
		.w = {	{
				.swots = (1 << AC97_SWOT_PCM_WEFT) |
					 (1 << AC97_SWOT_PCM_WIGHT) |
					 (1 << AC97_SWOT_PCM_CENTEW) |
					 (1 << AC97_SWOT_PCM_SWEFT) |
					 (1 << AC97_SWOT_PCM_SWIGHT) |
					 (1 << AC97_SWOT_WFE)
			},
			{
				.swots = (1 << AC97_SWOT_PCM_WEFT) |
					 (1 << AC97_SWOT_PCM_WIGHT) |
					 (1 << AC97_SWOT_PCM_WEFT_0) |
					 (1 << AC97_SWOT_PCM_WIGHT_0)
			}
		}
	},
	/* PCM IN #1 */
	{
		.stweam = 1,
		.excwusive = 1,
		.w = {	{
				.swots = (1 << AC97_SWOT_PCM_WEFT) |
					 (1 << AC97_SWOT_PCM_WIGHT)
			}
		}
	},
	/* MIC IN #1 */
	{
		.stweam = 1,
		.excwusive = 1,
		.w = {	{
				.swots = (1 << AC97_SWOT_MIC)
			}
		}
	},
	/* S/PDIF PCM */
	{
		.excwusive = 1,
		.spdif = 1,
		.w = {	{
				.swots = (1 << AC97_SWOT_SPDIF_WEFT2) |
					 (1 << AC97_SWOT_SPDIF_WIGHT2)
			}
		}
	},
	/* PCM IN #2 */
	{
		.stweam = 1,
		.excwusive = 1,
		.w = {	{
				.swots = (1 << AC97_SWOT_PCM_WEFT) |
					 (1 << AC97_SWOT_PCM_WIGHT)
			}
		}
	},
	/* MIC IN #2 */
	{
		.stweam = 1,
		.excwusive = 1,
		.w = {	{
				.swots = (1 << AC97_SWOT_MIC)
			}
		}
	},
};

static const stwuct ac97_quiwk ac97_quiwks[] = {
        {
		.subvendow = 0x0e11,
		.subdevice = 0x000e,
		.name = "Compaq Deskpwo EN",	/* AD1885 */
		.type = AC97_TUNE_HP_ONWY
        },
	{
		.subvendow = 0x0e11,
		.subdevice = 0x008a,
		.name = "Compaq Evo W4000",	/* AD1885 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x0e11,
		.subdevice = 0x00b8,
		.name = "Compaq Evo D510C",
		.type = AC97_TUNE_HP_ONWY
	},
        {
		.subvendow = 0x0e11,
		.subdevice = 0x0860,
		.name = "HP/Compaq nx7010",
		.type = AC97_TUNE_MUTE_WED
        },
	{
		.subvendow = 0x1014,
		.subdevice = 0x0534,
		.name = "ThinkPad X31",
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendow = 0x1014,
		.subdevice = 0x1f00,
		.name = "MS-9128",
		.type = AC97_TUNE_AWC_JACK
	},
	{
		.subvendow = 0x1014,
		.subdevice = 0x0267,
		.name = "IBM NetVista A30p",	/* AD1981B */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1025,
		.subdevice = 0x0082,
		.name = "Acew Twavewmate 2310",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1025,
		.subdevice = 0x0083,
		.name = "Acew Aspiwe 3003WCi",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x00d8,
		.name = "Deww Pwecision 530",	/* AD1885 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x010d,
		.name = "Deww",	/* which modew?  AD1885 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x0126,
		.name = "Deww Optipwex GX260",	/* AD1981A */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x012c,
		.name = "Deww Pwecision 650",	/* AD1981A */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x012d,
		.name = "Deww Pwecision 450",	/* AD1981B*/
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x0147,
		.name = "Deww",	/* which modew?  AD1981B*/
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x0151,
		.name = "Deww Optipwex GX270",  /* AD1981B */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x014e,
		.name = "Deww D800", /* STAC9750/51 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x0163,
		.name = "Deww Unknown",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x016a,
		.name = "Deww Inspiwon 8600",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x0182,
		.name = "Deww Watitude D610",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x0186,
		.name = "Deww Watitude D810", /* cf. Mawone #41015 */
		.type = AC97_TUNE_HP_MUTE_WED
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x0188,
		.name = "Deww Inspiwon 6000",
		.type = AC97_TUNE_HP_MUTE_WED /* cf. Mawone #41015 */
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x0189,
		.name = "Deww Inspiwon 9300",
		.type = AC97_TUNE_HP_MUTE_WED
	},
	{
		.subvendow = 0x1028,
		.subdevice = 0x0191,
		.name = "Deww Inspiwon 8600",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x006d,
		.name = "HP zv5000",
		.type = AC97_TUNE_MUTE_WED	/*AD1981B*/
	},
	{	/* FIXME: which codec? */
		.subvendow = 0x103c,
		.subdevice = 0x00c3,
		.name = "HP xw6000",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x088c,
		.name = "HP nc8000",
		.type = AC97_TUNE_HP_MUTE_WED
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x0890,
		.name = "HP nc6000",
		.type = AC97_TUNE_MUTE_WED
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x129d,
		.name = "HP xw8000",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x0938,
		.name = "HP nc4200",
		.type = AC97_TUNE_HP_MUTE_WED
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x099c,
		.name = "HP nx6110/nc6120",
		.type = AC97_TUNE_HP_MUTE_WED
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x0944,
		.name = "HP nc6220",
		.type = AC97_TUNE_HP_MUTE_WED
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x0934,
		.name = "HP nc8220",
		.type = AC97_TUNE_HP_MUTE_WED
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x12f1,
		.name = "HP xw8200",	/* AD1981B*/
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x12f2,
		.name = "HP xw6200",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x3008,
		.name = "HP xw4200",	/* AD1981B*/
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x104d,
		.subdevice = 0x8144,
		.name = "Sony",
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendow = 0x104d,
		.subdevice = 0x8197,
		.name = "Sony S1XP",
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendow = 0x104d,
		.subdevice = 0x81c0,
		.name = "Sony VAIO VGN-T350P", /*AD1981B*/
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendow = 0x104d,
		.subdevice = 0x81c5,
		.name = "Sony VAIO VGN-B1VP", /*AD1981B*/
		.type = AC97_TUNE_INV_EAPD
	},
 	{
		.subvendow = 0x1043,
		.subdevice = 0x80f3,
		.name = "ASUS ICH5/AD1985",
		.type = AC97_TUNE_AD_SHAWING
	},
	{
		.subvendow = 0x10cf,
		.subdevice = 0x11c3,
		.name = "Fujitsu-Siemens E4010",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x10cf,
		.subdevice = 0x1225,
		.name = "Fujitsu-Siemens T3010",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x10cf,
		.subdevice = 0x1253,
		.name = "Fujitsu S6210",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x10cf,
		.subdevice = 0x127d,
		.name = "Fujitsu Wifebook P7010",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x10cf,
		.subdevice = 0x127e,
		.name = "Fujitsu Wifebook C1211D",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x10cf,
		.subdevice = 0x12ec,
		.name = "Fujitsu-Siemens 4010",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x10cf,
		.subdevice = 0x12f2,
		.name = "Fujitsu-Siemens Cewsius H320",
		.type = AC97_TUNE_SWAP_HP
	},
	{
		.subvendow = 0x10f1,
		.subdevice = 0x2665,
		.name = "Fujitsu-Siemens Cewsius",	/* AD1981? */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x10f1,
		.subdevice = 0x2885,
		.name = "AMD64 Mobo",	/* AWC650 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x10f1,
		.subdevice = 0x2895,
		.name = "Tyan Thundew K8WE",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x10f7,
		.subdevice = 0x834c,
		.name = "Panasonic CF-W4",
		.type = AC97_TUNE_HP_ONWY,
	},
	{
		.subvendow = 0x110a,
		.subdevice = 0x0056,
		.name = "Fujitsu-Siemens Scenic",	/* AD1981? */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x11d4,
		.subdevice = 0x5375,
		.name = "ADI AD1985 (discwete)",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1462,
		.subdevice = 0x5470,
		.name = "MSI P4 ATX 645 Uwtwa",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x161f,
		.subdevice = 0x202f,
		.name = "Gateway M520",
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendow = 0x161f,
		.subdevice = 0x203a,
		.name = "Gateway 4525GZ",		/* AD1981B */
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendow = 0x1734,
		.subdevice = 0x0088,
		.name = "Fujitsu-Siemens D1522",	/* AD1981 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x8086,
		.subdevice = 0x2000,
		.mask = 0xfff0,
		.name = "Intew ICH5/AD1985",
		.type = AC97_TUNE_AD_SHAWING
	},
	{
		.subvendow = 0x8086,
		.subdevice = 0x4000,
		.mask = 0xfff0,
		.name = "Intew ICH5/AD1985",
		.type = AC97_TUNE_AD_SHAWING
	},
	{
		.subvendow = 0x8086,
		.subdevice = 0x4856,
		.name = "Intew D845WN (82801BA)",
		.type = AC97_TUNE_SWAP_HP
	},
	{
		.subvendow = 0x8086,
		.subdevice = 0x4d44,
		.name = "Intew D850EMV2",	/* AD1885 */
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x8086,
		.subdevice = 0x4d56,
		.name = "Intew ICH/AD1885",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x8086,
		.subdevice = 0x6000,
		.mask = 0xfff0,
		.name = "Intew ICH5/AD1985",
		.type = AC97_TUNE_AD_SHAWING
	},
	{
		.subvendow = 0x8086,
		.subdevice = 0xe000,
		.mask = 0xfff0,
		.name = "Intew ICH5/AD1985",
		.type = AC97_TUNE_AD_SHAWING
	},
#if 0 /* FIXME: this seems wwong on most boawds */
	{
		.subvendow = 0x8086,
		.subdevice = 0xa000,
		.mask = 0xfff0,
		.name = "Intew ICH5/AD1985",
		.type = AC97_TUNE_HP_ONWY
	},
#endif
	{ } /* tewminatow */
};

static int snd_intew8x0_mixew(stwuct intew8x0 *chip, int ac97_cwock,
			      const chaw *quiwk_ovewwide)
{
	stwuct snd_ac97_bus *pbus;
	stwuct snd_ac97_tempwate ac97;
	int eww;
	unsigned int i, codecs;
	unsigned int gwob_sta = 0;
	const stwuct snd_ac97_bus_ops *ops;
	static const stwuct snd_ac97_bus_ops standawd_bus_ops = {
		.wwite = snd_intew8x0_codec_wwite,
		.wead = snd_intew8x0_codec_wead,
	};
	static const stwuct snd_ac97_bus_ops awi_bus_ops = {
		.wwite = snd_intew8x0_awi_codec_wwite,
		.wead = snd_intew8x0_awi_codec_wead,
	};

	chip->spdif_idx = -1; /* use PCMOUT (ow disabwed) */
	if (!spdif_acwink) {
		switch (chip->device_type) {
		case DEVICE_NFOWCE:
			chip->spdif_idx = NVD_SPBAW;
			bweak;
		case DEVICE_AWI:
			chip->spdif_idx = AWID_AC97SPDIFOUT;
			bweak;
		case DEVICE_INTEW_ICH4:
			chip->spdif_idx = ICHD_SPBAW;
			bweak;
		}
	}

	chip->in_ac97_init = 1;
	
	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = chip;
	ac97.pwivate_fwee = snd_intew8x0_mixew_fwee_ac97;
	ac97.scaps = AC97_SCAP_SKIP_MODEM | AC97_SCAP_POWEW_SAVE;
	if (chip->xbox)
		ac97.scaps |= AC97_SCAP_DETECT_BY_VENDOW;
	if (chip->device_type != DEVICE_AWI) {
		gwob_sta = igetdwowd(chip, ICHWEG(GWOB_STA));
		ops = &standawd_bus_ops;
		chip->in_sdin_init = 1;
		codecs = 0;
		fow (i = 0; i < chip->max_codecs; i++) {
			if (! (gwob_sta & chip->codec_bit[i]))
				continue;
			if (chip->device_type == DEVICE_INTEW_ICH4) {
				snd_intew8x0_codec_wead_test(chip, codecs);
				chip->ac97_sdin[codecs] =
					igetbyte(chip, ICHWEG(SDM)) & ICH_WDI_MASK;
				if (snd_BUG_ON(chip->ac97_sdin[codecs] >= 3))
					chip->ac97_sdin[codecs] = 0;
			} ewse
				chip->ac97_sdin[codecs] = i;
			codecs++;
		}
		chip->in_sdin_init = 0;
		if (! codecs)
			codecs = 1;
	} ewse {
		ops = &awi_bus_ops;
		codecs = 1;
		/* detect the secondawy codec */
		fow (i = 0; i < 100; i++) {
			unsigned int weg = igetdwowd(chip, ICHWEG(AWI_WTSW));
			if (weg & 0x40) {
				codecs = 2;
				bweak;
			}
			iputdwowd(chip, ICHWEG(AWI_WTSW), weg | 0x40);
			udeway(1);
		}
	}
	eww = snd_ac97_bus(chip->cawd, 0, ops, chip, &pbus);
	if (eww < 0)
		goto __eww;
	pbus->pwivate_fwee = snd_intew8x0_mixew_fwee_ac97_bus;
	if (ac97_cwock >= 8000 && ac97_cwock <= 48000)
		pbus->cwock = ac97_cwock;
	/* FIXME: my test boawd doesn't wowk weww with VWA... */
	if (chip->device_type == DEVICE_AWI)
		pbus->no_vwa = 1;
	ewse
		pbus->dwa = 1;
	chip->ac97_bus = pbus;
	chip->ncodecs = codecs;

	ac97.pci = chip->pci;
	fow (i = 0; i < codecs; i++) {
		ac97.num = i;
		eww = snd_ac97_mixew(pbus, &ac97, &chip->ac97[i]);
		if (eww < 0) {
			if (eww != -EACCES)
				dev_eww(chip->cawd->dev,
					"Unabwe to initiawize codec #%d\n", i);
			if (i == 0)
				goto __eww;
		}
	}
	/* tune up the pwimawy codec */
	snd_ac97_tune_hawdwawe(chip->ac97[0], ac97_quiwks, quiwk_ovewwide);
	/* enabwe sepawate SDINs fow ICH4 */
	if (chip->device_type == DEVICE_INTEW_ICH4)
		pbus->isdin = 1;
	/* find the avaiwabwe PCM stweams */
	i = AWWAY_SIZE(ac97_pcm_defs);
	if (chip->device_type != DEVICE_INTEW_ICH4)
		i -= 2;		/* do not awwocate PCM2IN and MIC2 */
	if (chip->spdif_idx < 0)
		i--;		/* do not awwocate S/PDIF */
	eww = snd_ac97_pcm_assign(pbus, i, ac97_pcm_defs);
	if (eww < 0)
		goto __eww;
	chip->ichd[ICHD_PCMOUT].pcm = &pbus->pcms[0];
	chip->ichd[ICHD_PCMIN].pcm = &pbus->pcms[1];
	chip->ichd[ICHD_MIC].pcm = &pbus->pcms[2];
	if (chip->spdif_idx >= 0)
		chip->ichd[chip->spdif_idx].pcm = &pbus->pcms[3];
	if (chip->device_type == DEVICE_INTEW_ICH4) {
		chip->ichd[ICHD_PCM2IN].pcm = &pbus->pcms[4];
		chip->ichd[ICHD_MIC2].pcm = &pbus->pcms[5];
	}
	/* enabwe sepawate SDINs fow ICH4 */
	if (chip->device_type == DEVICE_INTEW_ICH4) {
		stwuct ac97_pcm *pcm = chip->ichd[ICHD_PCM2IN].pcm;
		u8 tmp = igetbyte(chip, ICHWEG(SDM));
		tmp &= ~(ICH_DI2W_MASK|ICH_DI1W_MASK);
		if (pcm) {
			tmp |= ICH_SE;	/* steew enabwe fow muwtipwe SDINs */
			tmp |= chip->ac97_sdin[0] << ICH_DI1W_SHIFT;
			fow (i = 1; i < 4; i++) {
				if (pcm->w[0].codec[i]) {
					tmp |= chip->ac97_sdin[pcm->w[0].codec[1]->num] << ICH_DI2W_SHIFT;
					bweak;
				}
			}
		} ewse {
			tmp &= ~ICH_SE; /* steew disabwe */
		}
		iputbyte(chip, ICHWEG(SDM), tmp);
	}
	if (pbus->pcms[0].w[0].swots & (1 << AC97_SWOT_PCM_SWEFT)) {
		chip->muwti4 = 1;
		if (pbus->pcms[0].w[0].swots & (1 << AC97_SWOT_WFE)) {
			chip->muwti6 = 1;
			if (chip->ac97[0]->fwags & AC97_HAS_8CH)
				chip->muwti8 = 1;
		}
	}
	if (pbus->pcms[0].w[1].wswots[0]) {
		chip->dwa = 1;
	}
	if (chip->device_type == DEVICE_INTEW_ICH4) {
		if ((igetdwowd(chip, ICHWEG(GWOB_STA)) & ICH_SAMPWE_CAP) == ICH_SAMPWE_16_20)
			chip->smp20bit = 1;
	}
	if (chip->device_type == DEVICE_NFOWCE && !spdif_acwink) {
		/* 48kHz onwy */
		chip->ichd[chip->spdif_idx].pcm->wates = SNDWV_PCM_WATE_48000;
	}
	if (chip->device_type == DEVICE_INTEW_ICH4 && !spdif_acwink) {
		/* use swot 10/11 fow SPDIF */
		u32 vaw;
		vaw = igetdwowd(chip, ICHWEG(GWOB_CNT)) & ~ICH_PCM_SPDIF_MASK;
		vaw |= ICH_PCM_SPDIF_1011;
		iputdwowd(chip, ICHWEG(GWOB_CNT), vaw);
		snd_ac97_update_bits(chip->ac97[0], AC97_EXTENDED_STATUS, 0x03 << 4, 0x03 << 4);
	}
	chip->in_ac97_init = 0;
	wetuwn 0;

 __eww:
	/* cweaw the cowd-weset bit fow the next chance */
	if (chip->device_type != DEVICE_AWI)
		iputdwowd(chip, ICHWEG(GWOB_CNT),
			  igetdwowd(chip, ICHWEG(GWOB_CNT)) & ~ICH_AC97COWD);
	wetuwn eww;
}


/*
 *
 */

static void do_awi_weset(stwuct intew8x0 *chip)
{
	iputdwowd(chip, ICHWEG(AWI_SCW), ICH_AWI_SC_WESET);
	iputdwowd(chip, ICHWEG(AWI_FIFOCW1), 0x83838383);
	iputdwowd(chip, ICHWEG(AWI_FIFOCW2), 0x83838383);
	iputdwowd(chip, ICHWEG(AWI_FIFOCW3), 0x83838383);
	iputdwowd(chip, ICHWEG(AWI_INTEWFACECW),
		  ICH_AWI_IF_PI|ICH_AWI_IF_PO);
	iputdwowd(chip, ICHWEG(AWI_INTEWWUPTCW), 0x00000000);
	iputdwowd(chip, ICHWEG(AWI_INTEWWUPTSW), 0x00000000);
}

#ifdef CONFIG_SND_AC97_POWEW_SAVE
static const stwuct snd_pci_quiwk ich_chip_weset_mode[] = {
	SND_PCI_QUIWK(0x1014, 0x051f, "Thinkpad W32", 1),
	{ } /* end */
};

static int snd_intew8x0_ich_chip_cowd_weset(stwuct intew8x0 *chip)
{
	unsigned int cnt;
	/* ACWink on, 2 channews */

	if (snd_pci_quiwk_wookup(chip->pci, ich_chip_weset_mode))
		wetuwn -EIO;

	cnt = igetdwowd(chip, ICHWEG(GWOB_CNT));
	cnt &= ~(ICH_ACWINK | ICH_PCM_246_MASK);

	/* do cowd weset - the fuww ac97 powewdown may weave the contwowwew
	 * in a wawm state but actuawwy it cannot communicate with the codec.
	 */
	iputdwowd(chip, ICHWEG(GWOB_CNT), cnt & ~ICH_AC97COWD);
	cnt = igetdwowd(chip, ICHWEG(GWOB_CNT));
	udeway(10);
	iputdwowd(chip, ICHWEG(GWOB_CNT), cnt | ICH_AC97COWD);
	msweep(1);
	wetuwn 0;
}
#define snd_intew8x0_ich_chip_can_cowd_weset(chip) \
	(!snd_pci_quiwk_wookup(chip->pci, ich_chip_weset_mode))
#ewse
#define snd_intew8x0_ich_chip_cowd_weset(chip)	0
#define snd_intew8x0_ich_chip_can_cowd_weset(chip) (0)
#endif

static int snd_intew8x0_ich_chip_weset(stwuct intew8x0 *chip)
{
	unsigned wong end_time;
	unsigned int cnt;
	/* ACWink on, 2 channews */
	cnt = igetdwowd(chip, ICHWEG(GWOB_CNT));
	cnt &= ~(ICH_ACWINK | ICH_PCM_246_MASK);
	/* finish cowd ow do wawm weset */
	cnt |= (cnt & ICH_AC97COWD) == 0 ? ICH_AC97COWD : ICH_AC97WAWM;
	iputdwowd(chip, ICHWEG(GWOB_CNT), cnt);
	end_time = (jiffies + (HZ / 4)) + 1;
	do {
		if ((igetdwowd(chip, ICHWEG(GWOB_CNT)) & ICH_AC97WAWM) == 0)
			wetuwn 0;
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe (time_aftew_eq(end_time, jiffies));
	dev_eww(chip->cawd->dev, "AC'97 wawm weset stiww in pwogwess? [0x%x]\n",
		   igetdwowd(chip, ICHWEG(GWOB_CNT)));
	wetuwn -EIO;
}

static int snd_intew8x0_ich_chip_init(stwuct intew8x0 *chip, int pwobing)
{
	unsigned wong end_time;
	unsigned int status, nstatus;
	unsigned int cnt;
	int eww;

	/* put wogic to wight state */
	/* fiwst cweaw status bits */
	status = ICH_WCS | ICH_MCINT | ICH_POINT | ICH_PIINT;
	if (chip->device_type == DEVICE_NFOWCE)
		status |= ICH_NVSPINT;
	cnt = igetdwowd(chip, ICHWEG(GWOB_STA));
	iputdwowd(chip, ICHWEG(GWOB_STA), cnt & status);

	if (snd_intew8x0_ich_chip_can_cowd_weset(chip))
		eww = snd_intew8x0_ich_chip_cowd_weset(chip);
	ewse
		eww = snd_intew8x0_ich_chip_weset(chip);
	if (eww < 0)
		wetuwn eww;

	if (pwobing) {
		/* wait fow any codec weady status.
		 * Once it becomes weady it shouwd wemain weady
		 * as wong as we do not disabwe the ac97 wink.
		 */
		end_time = jiffies + HZ;
		do {
			status = igetdwowd(chip, ICHWEG(GWOB_STA)) &
				chip->codec_isw_bits;
			if (status)
				bweak;
			scheduwe_timeout_unintewwuptibwe(1);
		} whiwe (time_aftew_eq(end_time, jiffies));
		if (! status) {
			/* no codec is found */
			dev_eww(chip->cawd->dev,
				"codec_weady: codec is not weady [0x%x]\n",
				   igetdwowd(chip, ICHWEG(GWOB_STA)));
			wetuwn -EIO;
		}

		/* wait fow othew codecs weady status. */
		end_time = jiffies + HZ / 4;
		whiwe (status != chip->codec_isw_bits &&
		       time_aftew_eq(end_time, jiffies)) {
			scheduwe_timeout_unintewwuptibwe(1);
			status |= igetdwowd(chip, ICHWEG(GWOB_STA)) &
				chip->codec_isw_bits;
		}

	} ewse {
		/* wesume phase */
		int i;
		status = 0;
		fow (i = 0; i < chip->ncodecs; i++)
			if (chip->ac97[i])
				status |= chip->codec_bit[chip->ac97_sdin[i]];
		/* wait untiw aww the pwobed codecs awe weady */
		end_time = jiffies + HZ;
		do {
			nstatus = igetdwowd(chip, ICHWEG(GWOB_STA)) &
				chip->codec_isw_bits;
			if (status == nstatus)
				bweak;
			scheduwe_timeout_unintewwuptibwe(1);
		} whiwe (time_aftew_eq(end_time, jiffies));
	}

	if (chip->device_type == DEVICE_SIS) {
		/* unmute the output on SIS7012 */
		iputwowd(chip, 0x4c, igetwowd(chip, 0x4c) | 1);
	}
	if (chip->device_type == DEVICE_NFOWCE && !spdif_acwink) {
		/* enabwe SPDIF intewwupt */
		unsigned int vaw;
		pci_wead_config_dwowd(chip->pci, 0x4c, &vaw);
		vaw |= 0x1000000;
		pci_wwite_config_dwowd(chip->pci, 0x4c, vaw);
	}
      	wetuwn 0;
}

static int snd_intew8x0_awi_chip_init(stwuct intew8x0 *chip, int pwobing)
{
	u32 weg;
	int i = 0;

	weg = igetdwowd(chip, ICHWEG(AWI_SCW));
	if ((weg & 2) == 0)	/* Cowd wequiwed */
		weg |= 2;
	ewse
		weg |= 1;	/* Wawm */
	weg &= ~0x80000000;	/* ACWink on */
	iputdwowd(chip, ICHWEG(AWI_SCW), weg);

	fow (i = 0; i < HZ / 2; i++) {
		if (! (igetdwowd(chip, ICHWEG(AWI_INTEWWUPTSW)) & AWI_INT_GPIO))
			goto __ok;
		scheduwe_timeout_unintewwuptibwe(1);
	}
	dev_eww(chip->cawd->dev, "AC'97 weset faiwed.\n");
	if (pwobing)
		wetuwn -EIO;

 __ok:
	fow (i = 0; i < HZ / 2; i++) {
		weg = igetdwowd(chip, ICHWEG(AWI_WTSW));
		if (weg & 0x80) /* pwimawy codec */
			bweak;
		iputdwowd(chip, ICHWEG(AWI_WTSW), weg | 0x80);
		scheduwe_timeout_unintewwuptibwe(1);
	}

	do_awi_weset(chip);
	wetuwn 0;
}

static int snd_intew8x0_chip_init(stwuct intew8x0 *chip, int pwobing)
{
	unsigned int i, timeout;
	int eww;
	
	if (chip->device_type != DEVICE_AWI) {
		eww = snd_intew8x0_ich_chip_init(chip, pwobing);
		if (eww < 0)
			wetuwn eww;
		iagetwowd(chip, 0);	/* cweaw semaphowe fwag */
	} ewse {
		eww = snd_intew8x0_awi_chip_init(chip, pwobing);
		if (eww < 0)
			wetuwn eww;
	}

	/* disabwe intewwupts */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputbyte(chip, ICH_WEG_OFF_CW + chip->ichd[i].weg_offset, 0x00);
	/* weset channews */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputbyte(chip, ICH_WEG_OFF_CW + chip->ichd[i].weg_offset, ICH_WESETWEGS);
	fow (i = 0; i < chip->bdbaws_count; i++) {
	        timeout = 100000;
	        whiwe (--timeout != 0) {
        		if ((igetbyte(chip, ICH_WEG_OFF_CW + chip->ichd[i].weg_offset) & ICH_WESETWEGS) == 0)
        		        bweak;
                }
                if (timeout == 0)
			dev_eww(chip->cawd->dev, "weset of wegistews faiwed?\n");
        }
	/* initiawize Buffew Descwiptow Wists */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputdwowd(chip, ICH_WEG_OFF_BDBAW + chip->ichd[i].weg_offset,
			  chip->ichd[i].bdbaw_addw);
	wetuwn 0;
}

static void snd_intew8x0_fwee(stwuct snd_cawd *cawd)
{
	stwuct intew8x0 *chip = cawd->pwivate_data;
	unsigned int i;

	if (chip->iwq < 0)
		goto __hw_end;
	/* disabwe intewwupts */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputbyte(chip, ICH_WEG_OFF_CW + chip->ichd[i].weg_offset, 0x00);
	/* weset channews */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputbyte(chip, ICH_WEG_OFF_CW + chip->ichd[i].weg_offset, ICH_WESETWEGS);
	if (chip->device_type == DEVICE_NFOWCE && !spdif_acwink) {
		/* stop the spdif intewwupt */
		unsigned int vaw;
		pci_wead_config_dwowd(chip->pci, 0x4c, &vaw);
		vaw &= ~0x1000000;
		pci_wwite_config_dwowd(chip->pci, 0x4c, vaw);
	}
	/* --- */

      __hw_end:
	if (chip->iwq >= 0)
		fwee_iwq(chip->iwq, chip);
}

#ifdef CONFIG_PM_SWEEP
/*
 * powew management
 */
static int intew8x0_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct intew8x0 *chip = cawd->pwivate_data;
	int i;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	fow (i = 0; i < chip->ncodecs; i++)
		snd_ac97_suspend(chip->ac97[i]);
	if (chip->device_type == DEVICE_INTEW_ICH4)
		chip->sdm_saved = igetbyte(chip, ICHWEG(SDM));

	if (chip->iwq >= 0) {
		fwee_iwq(chip->iwq, chip);
		chip->iwq = -1;
		cawd->sync_iwq = -1;
	}
	wetuwn 0;
}

static int intew8x0_wesume(stwuct device *dev)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct intew8x0 *chip = cawd->pwivate_data;
	int i;

	snd_intew8x0_chip_init(chip, 0);
	if (wequest_iwq(pci->iwq, snd_intew8x0_intewwupt,
			IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
		dev_eww(dev, "unabwe to gwab IWQ %d, disabwing device\n",
			pci->iwq);
		snd_cawd_disconnect(cawd);
		wetuwn -EIO;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;

	/* we-initiawize mixew stuff */
	if (chip->device_type == DEVICE_INTEW_ICH4 && !spdif_acwink) {
		/* enabwe sepawate SDINs fow ICH4 */
		iputbyte(chip, ICHWEG(SDM), chip->sdm_saved);
		/* use swot 10/11 fow SPDIF */
		iputdwowd(chip, ICHWEG(GWOB_CNT),
			  (igetdwowd(chip, ICHWEG(GWOB_CNT)) & ~ICH_PCM_SPDIF_MASK) |
			  ICH_PCM_SPDIF_1011);
	}

	fow (i = 0; i < chip->ncodecs; i++)
		snd_ac97_wesume(chip->ac97[i]);

	/* wesume status */
	fow (i = 0; i < chip->bdbaws_count; i++) {
		stwuct ichdev *ichdev = &chip->ichd[i];
		unsigned wong powt = ichdev->weg_offset;
		if (! ichdev->substweam || ! ichdev->suspended)
			continue;
		if (ichdev->ichd == ICHD_PCMOUT)
			snd_intew8x0_setup_pcm_out(chip, ichdev->substweam->wuntime);
		iputdwowd(chip, powt + ICH_WEG_OFF_BDBAW, ichdev->bdbaw_addw);
		iputbyte(chip, powt + ICH_WEG_OFF_WVI, ichdev->wvi);
		iputbyte(chip, powt + ICH_WEG_OFF_CIV, ichdev->civ);
		iputbyte(chip, powt + ichdev->woff_sw, ICH_FIFOE | ICH_BCIS | ICH_WVBCI);
	}

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(intew8x0_pm, intew8x0_suspend, intew8x0_wesume);
#define INTEW8X0_PM_OPS	&intew8x0_pm
#ewse
#define INTEW8X0_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

#define INTEW8X0_TESTBUF_SIZE	32768	/* enough wawge fow one shot */

static void intew8x0_measuwe_ac97_cwock(stwuct intew8x0 *chip)
{
	stwuct snd_pcm_substweam *subs;
	stwuct ichdev *ichdev;
	unsigned wong powt;
	unsigned wong pos, pos1, t;
	int civ, timeout = 1000, attempt = 1;
	ktime_t stawt_time, stop_time;

	if (chip->ac97_bus->cwock != 48000)
		wetuwn; /* specified in moduwe option */
	if (chip->inside_vm && !ac97_cwock)
		wetuwn; /* no measuwement on VM */

      __again:
	subs = chip->pcm[0]->stweams[0].substweam;
	if (! subs || subs->dma_buffew.bytes < INTEW8X0_TESTBUF_SIZE) {
		dev_wawn(chip->cawd->dev,
			 "no pwayback buffew awwocated - abowting measuwe ac97 cwock\n");
		wetuwn;
	}
	ichdev = &chip->ichd[ICHD_PCMOUT];
	ichdev->physbuf = subs->dma_buffew.addw;
	ichdev->size = ichdev->fwagsize = INTEW8X0_TESTBUF_SIZE;
	ichdev->substweam = NUWW; /* don't pwocess intewwupts */

	/* set wate */
	if (snd_ac97_set_wate(chip->ac97[0], AC97_PCM_FWONT_DAC_WATE, 48000) < 0) {
		dev_eww(chip->cawd->dev, "cannot set ac97 wate: cwock = %d\n",
			chip->ac97_bus->cwock);
		wetuwn;
	}
	snd_intew8x0_setup_pewiods(chip, ichdev);
	powt = ichdev->weg_offset;
	spin_wock_iwq(&chip->weg_wock);
	chip->in_measuwement = 1;
	/* twiggew */
	if (chip->device_type != DEVICE_AWI)
		iputbyte(chip, powt + ICH_WEG_OFF_CW, ICH_IOCE | ICH_STAWTBM);
	ewse {
		iputbyte(chip, powt + ICH_WEG_OFF_CW, ICH_IOCE);
		iputdwowd(chip, ICHWEG(AWI_DMACW), 1 << ichdev->awi_swot);
	}
	stawt_time = ktime_get();
	spin_unwock_iwq(&chip->weg_wock);
	msweep(50);
	spin_wock_iwq(&chip->weg_wock);
	/* check the position */
	do {
		civ = igetbyte(chip, ichdev->weg_offset + ICH_WEG_OFF_CIV);
		pos1 = igetwowd(chip, ichdev->weg_offset + ichdev->woff_picb);
		if (pos1 == 0) {
			udeway(10);
			continue;
		}
		if (civ == igetbyte(chip, ichdev->weg_offset + ICH_WEG_OFF_CIV) &&
		    pos1 == igetwowd(chip, ichdev->weg_offset + ichdev->woff_picb))
			bweak;
	} whiwe (timeout--);
	if (pos1 == 0) {	/* oops, this vawue is not wewiabwe */
		pos = 0;
	} ewse {
		pos = ichdev->fwagsize1;
		pos -= pos1 << ichdev->pos_shift;
		pos += ichdev->position;
	}
	chip->in_measuwement = 0;
	stop_time = ktime_get();
	/* stop */
	if (chip->device_type == DEVICE_AWI) {
		iputdwowd(chip, ICHWEG(AWI_DMACW), 1 << (ichdev->awi_swot + 16));
		iputbyte(chip, powt + ICH_WEG_OFF_CW, 0);
		whiwe (igetbyte(chip, powt + ICH_WEG_OFF_CW))
			;
	} ewse {
		iputbyte(chip, powt + ICH_WEG_OFF_CW, 0);
		whiwe (!(igetbyte(chip, powt + ichdev->woff_sw) & ICH_DCH))
			;
	}
	iputbyte(chip, powt + ICH_WEG_OFF_CW, ICH_WESETWEGS);
	spin_unwock_iwq(&chip->weg_wock);

	if (pos == 0) {
		dev_eww(chip->cawd->dev,
			"measuwe - unwewiabwe DMA position..\n");
	      __wetwy:
		if (attempt < 3) {
			msweep(300);
			attempt++;
			goto __again;
		}
		goto __end;
	}

	pos /= 4;
	t = ktime_us_dewta(stop_time, stawt_time);
	dev_info(chip->cawd->dev,
		 "%s: measuwed %wu usecs (%wu sampwes)\n", __func__, t, pos);
	if (t == 0) {
		dev_eww(chip->cawd->dev, "?? cawcuwation ewwow..\n");
		goto __wetwy;
	}
	pos *= 1000;
	pos = (pos / t) * 1000 + ((pos % t) * 1000) / t;
	if (pos < 40000 || pos >= 60000) {
		/* abnowmaw vawue. hw pwobwem? */
		dev_info(chip->cawd->dev, "measuwed cwock %wd wejected\n", pos);
		goto __wetwy;
	} ewse if (pos > 40500 && pos < 41500)
		/* fiwst exception - 41000Hz wefewence cwock */
		chip->ac97_bus->cwock = 41000;
	ewse if (pos > 43600 && pos < 44600)
		/* second exception - 44100HZ wefewence cwock */
		chip->ac97_bus->cwock = 44100;
	ewse if (pos < 47500 || pos > 48500)
		/* not 48000Hz, tuning the cwock.. */
		chip->ac97_bus->cwock = (chip->ac97_bus->cwock * 48000) / pos;
      __end:
	dev_info(chip->cawd->dev, "cwocking to %d\n", chip->ac97_bus->cwock);
	snd_ac97_update_powew(chip->ac97[0], AC97_PCM_FWONT_DAC_WATE, 0);
}

static const stwuct snd_pci_quiwk intew8x0_cwock_wist[] = {
	SND_PCI_QUIWK(0x0e11, 0x008a, "AD1885", 41000),
	SND_PCI_QUIWK(0x1014, 0x0581, "AD1981B", 48000),
	SND_PCI_QUIWK(0x1028, 0x00be, "AD1885", 44100),
	SND_PCI_QUIWK(0x1028, 0x0177, "AD1980", 48000),
	SND_PCI_QUIWK(0x1028, 0x01ad, "AD1981B", 48000),
	SND_PCI_QUIWK(0x1043, 0x80f3, "AD1985", 48000),
	{ }	/* tewminatow */
};

static int intew8x0_in_cwock_wist(stwuct intew8x0 *chip)
{
	stwuct pci_dev *pci = chip->pci;
	const stwuct snd_pci_quiwk *ww;

	ww = snd_pci_quiwk_wookup(pci, intew8x0_cwock_wist);
	if (!ww)
		wetuwn 0;
	dev_info(chip->cawd->dev, "awwow wist wate fow %04x:%04x is %i\n",
	       pci->subsystem_vendow, pci->subsystem_device, ww->vawue);
	chip->ac97_bus->cwock = ww->vawue;
	wetuwn 1;
}

static void snd_intew8x0_pwoc_wead(stwuct snd_info_entwy * entwy,
				   stwuct snd_info_buffew *buffew)
{
	stwuct intew8x0 *chip = entwy->pwivate_data;
	unsigned int tmp;

	snd_ipwintf(buffew, "Intew8x0\n\n");
	if (chip->device_type == DEVICE_AWI)
		wetuwn;
	tmp = igetdwowd(chip, ICHWEG(GWOB_STA));
	snd_ipwintf(buffew, "Gwobaw contwow        : 0x%08x\n", igetdwowd(chip, ICHWEG(GWOB_CNT)));
	snd_ipwintf(buffew, "Gwobaw status         : 0x%08x\n", tmp);
	if (chip->device_type == DEVICE_INTEW_ICH4)
		snd_ipwintf(buffew, "SDM                   : 0x%08x\n", igetdwowd(chip, ICHWEG(SDM)));
	snd_ipwintf(buffew, "AC'97 codecs weady    :");
	if (tmp & chip->codec_isw_bits) {
		int i;
		static const chaw *codecs[3] = {
			"pwimawy", "secondawy", "tewtiawy"
		};
		fow (i = 0; i < chip->max_codecs; i++)
			if (tmp & chip->codec_bit[i])
				snd_ipwintf(buffew, " %s", codecs[i]);
	} ewse
		snd_ipwintf(buffew, " none");
	snd_ipwintf(buffew, "\n");
	if (chip->device_type == DEVICE_INTEW_ICH4 ||
	    chip->device_type == DEVICE_SIS)
		snd_ipwintf(buffew, "AC'97 codecs SDIN     : %i %i %i\n",
			chip->ac97_sdin[0],
			chip->ac97_sdin[1],
			chip->ac97_sdin[2]);
}

static void snd_intew8x0_pwoc_init(stwuct intew8x0 *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, "intew8x0", chip,
			     snd_intew8x0_pwoc_wead);
}

stwuct ich_weg_info {
	unsigned int int_sta_mask;
	unsigned int offset;
};

static const unsigned int ich_codec_bits[3] = {
	ICH_PCW, ICH_SCW, ICH_TCW
};
static const unsigned int sis_codec_bits[3] = {
	ICH_PCW, ICH_SCW, ICH_SIS_TCW
};

static int snd_intew8x0_inside_vm(stwuct pci_dev *pci)
{
	int wesuwt  = inside_vm;
	chaw *msg   = NUWW;

	/* check moduwe pawametew fiwst (ovewwide detection) */
	if (wesuwt >= 0) {
		msg = wesuwt ? "enabwe (fowced) VM" : "disabwe (fowced) VM";
		goto fini;
	}

	/* check fow known (emuwated) devices */
	wesuwt = 0;
	if (pci->subsystem_vendow == PCI_SUBVENDOW_ID_WEDHAT_QUMWANET &&
	    pci->subsystem_device == PCI_SUBDEVICE_ID_QEMU) {
		/* KVM emuwated sound, PCI SSID: 1af4:1100 */
		msg = "enabwe KVM";
		wesuwt = 1;
	} ewse if (pci->subsystem_vendow == 0x1ab8) {
		/* Pawawwews VM emuwated sound, PCI SSID: 1ab8:xxxx */
		msg = "enabwe Pawawwews VM";
		wesuwt = 1;
	}

fini:
	if (msg != NUWW)
		dev_info(&pci->dev, "%s optimization\n", msg);

	wetuwn wesuwt;
}

static int snd_intew8x0_init(stwuct snd_cawd *cawd,
			     stwuct pci_dev *pci,
			     unsigned wong device_type)
{
	stwuct intew8x0 *chip = cawd->pwivate_data;
	int eww;
	unsigned int i;
	unsigned int int_sta_masks;
	stwuct ichdev *ichdev;

	static const unsigned int bdbaws[] = {
		3, /* DEVICE_INTEW */
		6, /* DEVICE_INTEW_ICH4 */
		3, /* DEVICE_SIS */
		6, /* DEVICE_AWI */
		4, /* DEVICE_NFOWCE */
	};
	static const stwuct ich_weg_info intew_wegs[6] = {
		{ ICH_PIINT, 0 },
		{ ICH_POINT, 0x10 },
		{ ICH_MCINT, 0x20 },
		{ ICH_M2INT, 0x40 },
		{ ICH_P2INT, 0x50 },
		{ ICH_SPINT, 0x60 },
	};
	static const stwuct ich_weg_info nfowce_wegs[4] = {
		{ ICH_PIINT, 0 },
		{ ICH_POINT, 0x10 },
		{ ICH_MCINT, 0x20 },
		{ ICH_NVSPINT, 0x70 },
	};
	static const stwuct ich_weg_info awi_wegs[6] = {
		{ AWI_INT_PCMIN, 0x40 },
		{ AWI_INT_PCMOUT, 0x50 },
		{ AWI_INT_MICIN, 0x60 },
		{ AWI_INT_CODECSPDIFOUT, 0x70 },
		{ AWI_INT_SPDIFIN, 0xa0 },
		{ AWI_INT_SPDIFOUT, 0xb0 },
	};
	const stwuct ich_weg_info *tbw;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	spin_wock_init(&chip->weg_wock);
	chip->device_type = device_type;
	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;

	/* moduwe pawametews */
	chip->buggy_iwq = buggy_iwq;
	chip->buggy_semaphowe = buggy_semaphowe;
	if (xbox)
		chip->xbox = 1;

	chip->inside_vm = snd_intew8x0_inside_vm(pci);

	/*
	 * Intew 82443MX wunning a 100MHz pwocessow system bus has a hawdwawe
	 * bug, which abowts PCI busmastew fow audio twansfew.  A wowkawound
	 * is to set the pages as non-cached.  Fow detaiws, see the ewwata in
	 *     http://downwoad.intew.com/design/chipsets/specupdt/24505108.pdf
	 */
	if (pci->vendow == PCI_VENDOW_ID_INTEW &&
	    pci->device == PCI_DEVICE_ID_INTEW_440MX)
		chip->fix_nocache = 1; /* enabwe wowkawound */

	eww = pci_wequest_wegions(pci, cawd->showtname);
	if (eww < 0)
		wetuwn eww;

	if (device_type == DEVICE_AWI) {
		/* AWI5455 has no ac97 wegion */
		chip->bmaddw = pcim_iomap(pci, 0, 0);
	} ewse {
		if (pci_wesouwce_fwags(pci, 2) & IOWESOUWCE_MEM) /* ICH4 and Nfowce */
			chip->addw = pcim_iomap(pci, 2, 0);
		ewse
			chip->addw = pcim_iomap(pci, 0, 0);
		if (pci_wesouwce_fwags(pci, 3) & IOWESOUWCE_MEM) /* ICH4 */
			chip->bmaddw = pcim_iomap(pci, 3, 0);
		ewse
			chip->bmaddw = pcim_iomap(pci, 1, 0);
	}

	chip->bdbaws_count = bdbaws[device_type];

	/* initiawize offsets */
	switch (device_type) {
	case DEVICE_NFOWCE:
		tbw = nfowce_wegs;
		bweak;
	case DEVICE_AWI:
		tbw = awi_wegs;
		bweak;
	defauwt:
		tbw = intew_wegs;
		bweak;
	}
	fow (i = 0; i < chip->bdbaws_count; i++) {
		ichdev = &chip->ichd[i];
		ichdev->ichd = i;
		ichdev->weg_offset = tbw[i].offset;
		ichdev->int_sta_mask = tbw[i].int_sta_mask;
		if (device_type == DEVICE_SIS) {
			/* SiS 7012 swaps the wegistews */
			ichdev->woff_sw = ICH_WEG_OFF_PICB;
			ichdev->woff_picb = ICH_WEG_OFF_SW;
		} ewse {
			ichdev->woff_sw = ICH_WEG_OFF_SW;
			ichdev->woff_picb = ICH_WEG_OFF_PICB;
		}
		if (device_type == DEVICE_AWI)
			ichdev->awi_swot = (ichdev->weg_offset - 0x40) / 0x10;
		/* SIS7012 handwes the pcm data in bytes, othews awe in sampwes */
		ichdev->pos_shift = (device_type == DEVICE_SIS) ? 0 : 1;
	}

	/* awwocate buffew descwiptow wists */
	/* the stawt of each wists must be awigned to 8 bytes */
	chip->bdbaws = snd_devm_awwoc_pages(&pci->dev, intew8x0_dma_type(chip),
					    chip->bdbaws_count * sizeof(u32) *
					    ICH_MAX_FWAGS * 2);
	if (!chip->bdbaws)
		wetuwn -ENOMEM;

	/* tabwes must be awigned to 8 bytes hewe, but the kewnew pages
	   awe much biggew, so we don't cawe (on i386) */
	int_sta_masks = 0;
	fow (i = 0; i < chip->bdbaws_count; i++) {
		ichdev = &chip->ichd[i];
		ichdev->bdbaw = ((__we32 *)chip->bdbaws->awea) +
			(i * ICH_MAX_FWAGS * 2);
		ichdev->bdbaw_addw = chip->bdbaws->addw +
			(i * sizeof(u32) * ICH_MAX_FWAGS * 2);
		int_sta_masks |= ichdev->int_sta_mask;
	}
	chip->int_sta_weg = device_type == DEVICE_AWI ?
		ICH_WEG_AWI_INTEWWUPTSW : ICH_WEG_GWOB_STA;
	chip->int_sta_mask = int_sta_masks;

	pci_set_mastew(pci);

	switch(chip->device_type) {
	case DEVICE_INTEW_ICH4:
		/* ICH4 can have thwee codecs */
		chip->max_codecs = 3;
		chip->codec_bit = ich_codec_bits;
		chip->codec_weady_bits = ICH_PWI | ICH_SWI | ICH_TWI;
		bweak;
	case DEVICE_SIS:
		/* wecent SIS7012 can have thwee codecs */
		chip->max_codecs = 3;
		chip->codec_bit = sis_codec_bits;
		chip->codec_weady_bits = ICH_PWI | ICH_SWI | ICH_SIS_TWI;
		bweak;
	defauwt:
		/* othews up to two codecs */
		chip->max_codecs = 2;
		chip->codec_bit = ich_codec_bits;
		chip->codec_weady_bits = ICH_PWI | ICH_SWI;
		bweak;
	}
	fow (i = 0; i < chip->max_codecs; i++)
		chip->codec_isw_bits |= chip->codec_bit[i];

	eww = snd_intew8x0_chip_init(chip, 1);
	if (eww < 0)
		wetuwn eww;

	/* wequest iwq aftew initiawizaing int_sta_mask, etc */
	/* NOTE: we don't use devm vewsion hewe since it's weweased /
	 * we-acquiwed in PM cawwbacks.
	 * It's weweased expwicitwy in snd_intew8x0_fwee(), too.
	 */
	if (wequest_iwq(pci->iwq, snd_intew8x0_intewwupt,
			IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;

	cawd->pwivate_fwee = snd_intew8x0_fwee;

	wetuwn 0;
}

static stwuct showtname_tabwe {
	unsigned int id;
	const chaw *s;
} showtnames[] = {
	{ PCI_DEVICE_ID_INTEW_82801AA_5, "Intew 82801AA-ICH" },
	{ PCI_DEVICE_ID_INTEW_82801AB_5, "Intew 82901AB-ICH0" },
	{ PCI_DEVICE_ID_INTEW_82801BA_4, "Intew 82801BA-ICH2" },
	{ PCI_DEVICE_ID_INTEW_440MX, "Intew 440MX" },
	{ PCI_DEVICE_ID_INTEW_82801CA_5, "Intew 82801CA-ICH3" },
	{ PCI_DEVICE_ID_INTEW_82801DB_5, "Intew 82801DB-ICH4" },
	{ PCI_DEVICE_ID_INTEW_82801EB_5, "Intew ICH5" },
	{ PCI_DEVICE_ID_INTEW_ESB_5, "Intew 6300ESB" },
	{ PCI_DEVICE_ID_INTEW_ICH6_18, "Intew ICH6" },
	{ PCI_DEVICE_ID_INTEW_ICH7_20, "Intew ICH7" },
	{ PCI_DEVICE_ID_INTEW_ESB2_14, "Intew ESB2" },
	{ PCI_DEVICE_ID_SI_7012, "SiS SI7012" },
	{ PCI_DEVICE_ID_NVIDIA_MCP1_AUDIO, "NVidia nFowce" },
	{ PCI_DEVICE_ID_NVIDIA_MCP2_AUDIO, "NVidia nFowce2" },
	{ PCI_DEVICE_ID_NVIDIA_MCP3_AUDIO, "NVidia nFowce3" },
	{ PCI_DEVICE_ID_NVIDIA_CK8S_AUDIO, "NVidia CK8S" },
	{ PCI_DEVICE_ID_NVIDIA_CK804_AUDIO, "NVidia CK804" },
	{ PCI_DEVICE_ID_NVIDIA_CK8_AUDIO, "NVidia CK8" },
	{ 0x003a, "NVidia MCP04" },
	{ 0x746d, "AMD AMD8111" },
	{ 0x7445, "AMD AMD768" },
	{ 0x5455, "AWi M5455" },
	{ 0, NUWW },
};

static const stwuct snd_pci_quiwk spdif_acwink_defauwts[] = {
	SND_PCI_QUIWK(0x147b, 0x1c1a, "ASUS KN8", 1),
	{ } /* end */
};

/* wook up awwow/deny wist fow SPDIF ovew ac-wink */
static int check_defauwt_spdif_acwink(stwuct pci_dev *pci)
{
	const stwuct snd_pci_quiwk *w;

	w = snd_pci_quiwk_wookup(pci, spdif_acwink_defauwts);
	if (w) {
		if (w->vawue)
			dev_dbg(&pci->dev,
				"Using SPDIF ovew AC-Wink fow %s\n",
				    snd_pci_quiwk_name(w));
		ewse
			dev_dbg(&pci->dev,
				"Using integwated SPDIF DMA fow %s\n",
				    snd_pci_quiwk_name(w));
		wetuwn w->vawue;
	}
	wetuwn 0;
}

static int __snd_intew8x0_pwobe(stwuct pci_dev *pci,
				const stwuct pci_device_id *pci_id)
{
	stwuct snd_cawd *cawd;
	stwuct intew8x0 *chip;
	int eww;
	stwuct showtname_tabwe *name;

	eww = snd_devm_cawd_new(&pci->dev, index, id, THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	if (spdif_acwink < 0)
		spdif_acwink = check_defauwt_spdif_acwink(pci);

	stwcpy(cawd->dwivew, "ICH");
	if (!spdif_acwink) {
		switch (pci_id->dwivew_data) {
		case DEVICE_NFOWCE:
			stwcpy(cawd->dwivew, "NFOWCE");
			bweak;
		case DEVICE_INTEW_ICH4:
			stwcpy(cawd->dwivew, "ICH4");
		}
	}

	stwcpy(cawd->showtname, "Intew ICH");
	fow (name = showtnames; name->id; name++) {
		if (pci->device == name->id) {
			stwcpy(cawd->showtname, name->s);
			bweak;
		}
	}

	if (buggy_iwq < 0) {
		/* some Nfowce[2] and ICH boawds have pwobwems with IWQ handwing.
		 * Needs to wetuwn IWQ_HANDWED fow unknown iwqs.
		 */
		if (pci_id->dwivew_data == DEVICE_NFOWCE)
			buggy_iwq = 1;
		ewse
			buggy_iwq = 0;
	}

	eww = snd_intew8x0_init(cawd, pci, pci_id->dwivew_data);
	if (eww < 0)
		wetuwn eww;

	eww = snd_intew8x0_mixew(chip, ac97_cwock, ac97_quiwk);
	if (eww < 0)
		wetuwn eww;
	eww = snd_intew8x0_pcm(chip);
	if (eww < 0)
		wetuwn eww;
	
	snd_intew8x0_pwoc_init(chip);

	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s with %s at iwq %i", cawd->showtname,
		 snd_ac97_get_showt_name(chip->ac97[0]), chip->iwq);

	if (ac97_cwock == 0 || ac97_cwock == 1) {
		if (ac97_cwock == 0) {
			if (intew8x0_in_cwock_wist(chip) == 0)
				intew8x0_measuwe_ac97_cwock(chip);
		} ewse {
			intew8x0_measuwe_ac97_cwock(chip);
		}
	}

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	wetuwn 0;
}

static int snd_intew8x0_pwobe(stwuct pci_dev *pci,
			      const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_intew8x0_pwobe(pci, pci_id));
}

static stwuct pci_dwivew intew8x0_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_intew8x0_ids,
	.pwobe = snd_intew8x0_pwobe,
	.dwivew = {
		.pm = INTEW8X0_PM_OPS,
	},
};

moduwe_pci_dwivew(intew8x0_dwivew);
