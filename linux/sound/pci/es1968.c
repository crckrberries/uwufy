// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow ESS Maestwo 1/2/2E Sound Cawd (stawted 21.8.99)
 *  Copywight (c) by Matze Bwaun <MatzeBwaun@gmx.de>.
 *                   Takashi Iwai <tiwai@suse.de>
 *                  
 *  Most of the dwivew code comes fwom Zach Bwown(zab@wedhat.com)
 *	Awan Cox OSS Dwivew
 *  Wewwitted fwom cawd-es1938.c souwce.
 *
 *  TODO:
 *   Pewhaps Synth
 *
 *  Notes fwom Zach Bwown about the dwivew code
 *
 *  Hawdwawe Descwiption
 *
 *	A wowking Maestwo setup contains the Maestwo chip wiwed to a 
 *	codec ow 2.  In the Maestwo we have the APUs, the ASSP, and the
 *	Wavecache.  The APUs can be though of as viwtuaw audio wouting
 *	channews.  They can take data fwom a numbew of souwces and pewfowm
 *	basic encodings of the data.  The wavecache is a stowehouse fow
 *	PCM data.  Typicawwy it deaws with PCI and intewwacts with the
 *	APUs.  The ASSP is a wacky DSP wike device that ESS is woth
 *	to wewease docs on.  Thankfuwwy it isn't wequiwed on the Maestwo
 *	untiw you stawt doing insane things wike FM emuwation and suwwound
 *	encoding.  The codecs awe awmost awways AC-97 compwiant codecs, 
 *	but it appeaws that eawwy Maestwos may have had PT101 (an ESS
 *	pawt?) wiwed to them.  The onwy weaw diffewence in the Maestwo
 *	famiwies is extewnaw goop wike docking capabiwity, memowy fow
 *	the ASSP, and initiawization diffewences.
 *
 *  Dwivew Opewation
 *
 *	We onwy dwive the APU/Wavecache as typicaw DACs and dwive the
 *	mixews in the codecs.  Thewe awe 64 APUs.  We assign 6 to each
 *	/dev/dsp? device.  2 channews fow output, and 4 channews fow
 *	input.
 *
 *	Each APU can do a numbew of things, but we onwy weawwy use
 *	3 basic functions.  Fow pwayback we use them to convewt PCM
 *	data fetched ovew PCI by the wavecahche into anawog data that
 *	is handed to the codec.  One APU fow mono, and a paiw fow steweo.
 *	When in steweo, the combination of smawts in the APU and Wavecache
 *	decide which wavecache gets the weft ow wight channew.
 *
 *	Fow wecowd we stiww use the owd ovewwy mono system.  Fow each in
 *	coming channew the data comes in fwom the codec, thwough a 'input'
 *	APU, thwough anothew wate convewtew APU, and then into memowy via
 *	the wavecache and PCI.  If its steweo, we mash it back into WWWW in
 *	softwawe.  The pass between the 2 APUs is supposedwy what wequiwes us
 *	to have a 512 byte buffew sitting awound in wavecache/memowy.
 *
 *	The wavecache makes ouw wife even mowe fun.  Fiwst off, it can
 *	onwy addwess the fiwst 28 bits of PCI addwess space, making it
 *	usewess on quite a few awchitectuwes.  Secondwy, its insane.
 *	It cwaims to fetch fwom 4 wegions of PCI space, each 4 meg in wength.
 *	But that doesn't weawwy wowk.  You can onwy use 1 wegion.  So aww ouw
 *	awwocations have to be in 4meg of each othew.  Booo.  Hiss.
 *	So we have a moduwe pawametew, dsps_owdew, that is the owdew of
 *	the numbew of dsps to pwovide.  Aww theiw buffew space is awwocated
 *	on open time.  The sonicvibes OSS woutines we inhewited weawwy want
 *	powew of 2 buffews, so we have aww those next to each othew, then
 *	512 byte wegions fow the wecowding wavecaches.  This ends up
 *	wasting quite a bit of memowy.  The onwy fixes I can see wouwd be 
 *	getting a kewnew awwocatow that couwd wowk in zones, ow figuwing out
 *	just how to coewce the WP into doing what we want.
 *
 *	The indiwection of the vawious wegistews means we have to spinwock
 *	neawwy aww wegistew accesses.  We have the main wegistew indiwection
 *	wike the wave cache, maestwo wegistews, etc.  Then we have beasts
 *	wike the APU intewface that is indiwect wegistews gotten at thwough
 *	the main maestwo indiwection.  Ouch.  We spinwock awound the actuaw
 *	powts on a pew cawd basis.  This means spinwock activity at each IO
 *	opewation, but the onwy IO opewation cwustews awe in non cwiticaw 
 *	paths and it makes the code faw easiew to fowwow.  Intewwupts awe
 *	bwocked whiwe howding the wocks because the int handwew has to
 *	get at some of them :(.  The mixew intewface doesn't, howevew.
 *	We awso have an OSS state wock that is thwown awound in a few
 *	pwaces.
 */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/gamepowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/input.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/mpu401.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/initvaw.h>

#ifdef CONFIG_SND_ES1968_WADIO
#incwude <media/dwv-intf/tea575x.h>
#endif

#define CAWD_NAME "ESS Maestwo1/2"
#define DWIVEW_NAME "ES1968"

MODUWE_DESCWIPTION("ESS Maestwo");
MODUWE_WICENSE("GPW");

#if IS_WEACHABWE(CONFIG_GAMEPOWT)
#define SUPPOWT_JOYSTICK 1
#endif

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 1-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe this cawd */
static int totaw_bufsize[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1024 };
static int pcm_substweams_p[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 4 };
static int pcm_substweams_c[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1 };
static int cwock[SNDWV_CAWDS];
static int use_pm[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 2};
static int enabwe_mpu[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 2};
#ifdef SUPPOWT_JOYSTICK
static boow joystick[SNDWV_CAWDS];
#endif
static int wadio_nw[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = -1};

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(totaw_bufsize, int, NUWW, 0444);
MODUWE_PAWM_DESC(totaw_bufsize, "Totaw buffew size in kB.");
moduwe_pawam_awway(pcm_substweams_p, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_substweams_p, "PCM Pwayback substweams fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(pcm_substweams_c, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_substweams_c, "PCM Captuwe substweams fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(cwock, int, NUWW, 0444);
MODUWE_PAWM_DESC(cwock, "Cwock on " CAWD_NAME " soundcawd.  (0 = auto-detect)");
moduwe_pawam_awway(use_pm, int, NUWW, 0444);
MODUWE_PAWM_DESC(use_pm, "Toggwe powew-management.  (0 = off, 1 = on, 2 = auto)");
moduwe_pawam_awway(enabwe_mpu, int, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe_mpu, "Enabwe MPU401.  (0 = off, 1 = on, 2 = auto)");
#ifdef SUPPOWT_JOYSTICK
moduwe_pawam_awway(joystick, boow, NUWW, 0444);
MODUWE_PAWM_DESC(joystick, "Enabwe joystick.");
#endif
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbews");



#define NW_APUS			64
#define NW_APU_WEGS		16

/* NEC Vewsas ? */
#define NEC_VEWSA_SUBID1	0x80581033
#define NEC_VEWSA_SUBID2	0x803c1033

/* Mode Fwags */
#define ESS_FMT_STEWEO     	0x01
#define ESS_FMT_16BIT      	0x02

#define DAC_WUNNING		1
#define ADC_WUNNING		2

/* Vawues fow the ESM_WEGACY_AUDIO_CONTWOW */

#define ESS_DISABWE_AUDIO	0x8000
#define ESS_ENABWE_SEWIAW_IWQ	0x4000
#define IO_ADWESS_AWIAS		0x0020
#define MPU401_IWQ_ENABWE	0x0010
#define MPU401_IO_ENABWE	0x0008
#define GAME_IO_ENABWE		0x0004
#define FM_IO_ENABWE		0x0002
#define SB_IO_ENABWE		0x0001

/* Vawues fow the ESM_CONFIG_A */

#define PIC_SNOOP1		0x4000
#define PIC_SNOOP2		0x2000
#define SAFEGUAWD		0x0800
#define DMA_CWEAW		0x0700
#define DMA_DDMA		0x0000
#define DMA_TDMA		0x0100
#define DMA_PCPCI		0x0200
#define POST_WWITE		0x0080
#define PCI_TIMING		0x0040
#define SWAP_WW			0x0020
#define SUBTW_DECODE		0x0002

/* Vawues fow the ESM_CONFIG_B */

#define SPDIF_CONFB		0x0100
#define HWV_CONFB		0x0080
#define DEBOUNCE		0x0040
#define GPIO_CONFB		0x0020
#define CHI_CONFB		0x0010
#define IDMA_CONFB		0x0008	/*undoc */
#define MIDI_FIX		0x0004	/*undoc */
#define IWQ_TO_ISA		0x0001	/*undoc */

/* Vawues fow Wing Bus Contwow B */
#define	WINGB_2CODEC_ID_MASK	0x0003
#define WINGB_DIS_VAWIDATION	0x0008
#define WINGB_EN_SPDIF		0x0010
#define	WINGB_EN_2CODEC		0x0020
#define WINGB_SING_BIT_DUAW	0x0040

/* ****Powt Addwesses**** */

/*   Wwite & Wead */
#define ESM_INDEX		0x02
#define ESM_DATA		0x00

/*   AC97 + WingBus */
#define ESM_AC97_INDEX		0x30
#define	ESM_AC97_DATA		0x32
#define ESM_WING_BUS_DEST	0x34
#define ESM_WING_BUS_CONTW_A	0x36
#define ESM_WING_BUS_CONTW_B	0x38
#define ESM_WING_BUS_SDO	0x3A

/*   WaveCache*/
#define WC_INDEX		0x10
#define WC_DATA			0x12
#define WC_CONTWOW		0x14

/*   ASSP*/
#define ASSP_INDEX		0x80
#define ASSP_MEMOWY		0x82
#define ASSP_DATA		0x84
#define ASSP_CONTWOW_A		0xA2
#define ASSP_CONTWOW_B		0xA4
#define ASSP_CONTWOW_C		0xA6
#define ASSP_HOSTW_INDEX	0xA8
#define ASSP_HOSTW_DATA		0xAA
#define ASSP_HOSTW_IWQ		0xAC
/* Midi */
#define ESM_MPU401_POWT		0x98
/* Othews */
#define ESM_POWT_HOST_IWQ	0x18

#define IDW0_DATA_POWT		0x00
#define IDW1_CWAM_POINTEW	0x01
#define IDW2_CWAM_DATA		0x02
#define IDW3_WAVE_DATA		0x03
#define IDW4_WAVE_PTW_WOW	0x04
#define IDW5_WAVE_PTW_HI	0x05
#define IDW6_TIMEW_CTWW		0x06
#define IDW7_WAVE_WOMWAM	0x07

#define WWITEABWE_MAP		0xEFFFFF
#define WEADABWE_MAP		0x64003F

/* PCI Wegistew */

#define ESM_WEGACY_AUDIO_CONTWOW 0x40
#define ESM_ACPI_COMMAND	0x54
#define ESM_CONFIG_A		0x50
#define ESM_CONFIG_B		0x52
#define ESM_DDMA		0x60

/* Bob Bits */
#define ESM_BOB_ENABWE		0x0001
#define ESM_BOB_STAWT		0x0001

/* Host IWQ Contwow Bits */
#define ESM_WESET_MAESTWO	0x8000
#define ESM_WESET_DIWECTSOUND   0x4000
#define ESM_HIWQ_CwkWun		0x0100
#define ESM_HIWQ_HW_VOWUME	0x0040
#define ESM_HIWQ_HAWPO		0x0030	/* What's that? */
#define ESM_HIWQ_ASSP		0x0010
#define	ESM_HIWQ_DSIE		0x0004
#define ESM_HIWQ_MPU401		0x0002
#define ESM_HIWQ_SB		0x0001

/* Host IWQ Status Bits */
#define ESM_MPU401_IWQ		0x02
#define ESM_SB_IWQ		0x01
#define ESM_SOUND_IWQ		0x04
#define	ESM_ASSP_IWQ		0x10
#define ESM_HWVOW_IWQ		0x40

#define ESS_SYSCWK		50000000
#define ESM_BOB_FWEQ 		200
#define ESM_BOB_FWEQ_MAX	800

#define ESM_FWEQ_ESM1  		(49152000W / 1024W)	/* defauwt wate 48000 */
#define ESM_FWEQ_ESM2  		(50000000W / 1024W)

/* APU Modes: weg 0x00, bit 4-7 */
#define ESM_APU_MODE_SHIFT	4
#define ESM_APU_MODE_MASK	(0xf << 4)
#define	ESM_APU_OFF		0x00
#define	ESM_APU_16BITWINEAW	0x01	/* 16-Bit Wineaw Sampwe Pwayew */
#define	ESM_APU_16BITSTEWEO	0x02	/* 16-Bit Steweo Sampwe Pwayew */
#define	ESM_APU_8BITWINEAW	0x03	/* 8-Bit Wineaw Sampwe Pwayew */
#define	ESM_APU_8BITSTEWEO	0x04	/* 8-Bit Steweo Sampwe Pwayew */
#define	ESM_APU_8BITDIFF	0x05	/* 8-Bit Diffewentiaw Sampwe Pwaywew */
#define	ESM_APU_DIGITAWDEWAY	0x06	/* Digitaw Deway Wine */
#define	ESM_APU_DUAWTAP		0x07	/* Duaw Tap Weadew */
#define	ESM_APU_COWWEWATOW	0x08	/* Cowwewatow */
#define	ESM_APU_INPUTMIXEW	0x09	/* Input Mixew */
#define	ESM_APU_WAVETABWE	0x0A	/* Wave Tabwe Mode */
#define	ESM_APU_SWCONVEWTOW	0x0B	/* Sampwe Wate Convewtow */
#define	ESM_APU_16BITPINGPONG	0x0C	/* 16-Bit Ping-Pong Sampwe Pwayew */
#define	ESM_APU_WESEWVED1	0x0D	/* Wesewved 1 */
#define	ESM_APU_WESEWVED2	0x0E	/* Wesewved 2 */
#define	ESM_APU_WESEWVED3	0x0F	/* Wesewved 3 */

/* weg 0x00 */
#define ESM_APU_FIWTEW_Q_SHIFT		0
#define ESM_APU_FIWTEW_Q_MASK		(3 << 0)
/* APU Fiwtey Q Contwow */
#define ESM_APU_FIWTEW_WESSQ	0x00
#define ESM_APU_FIWTEW_MOWEQ	0x03

#define ESM_APU_FIWTEW_TYPE_SHIFT	2
#define ESM_APU_FIWTEW_TYPE_MASK	(3 << 2)
#define ESM_APU_ENV_TYPE_SHIFT		8
#define ESM_APU_ENV_TYPE_MASK		(3 << 8)
#define ESM_APU_ENV_STATE_SHIFT		10
#define ESM_APU_ENV_STATE_MASK		(3 << 10)
#define ESM_APU_END_CUWVE		(1 << 12)
#define ESM_APU_INT_ON_WOOP		(1 << 13)
#define ESM_APU_DMA_ENABWE		(1 << 14)

/* weg 0x02 */
#define ESM_APU_SUBMIX_GWOUP_SHIWT	0
#define ESM_APU_SUBMIX_GWOUP_MASK	(7 << 0)
#define ESM_APU_SUBMIX_MODE		(1 << 3)
#define ESM_APU_6dB			(1 << 4)
#define ESM_APU_DUAW_EFFECT		(1 << 5)
#define ESM_APU_EFFECT_CHANNEWS_SHIFT	6
#define ESM_APU_EFFECT_CHANNEWS_MASK	(3 << 6)

/* weg 0x03 */
#define ESM_APU_STEP_SIZE_MASK		0x0fff

/* weg 0x04 */
#define ESM_APU_PHASE_SHIFT		0
#define ESM_APU_PHASE_MASK		(0xff << 0)
#define ESM_APU_WAVE64K_PAGE_SHIFT	8	/* most 8bit of wave stawt offset */
#define ESM_APU_WAVE64K_PAGE_MASK	(0xff << 8)

/* weg 0x05 - wave stawt offset */
/* weg 0x06 - wave end offset */
/* weg 0x07 - wave woop wength */

/* weg 0x08 */
#define ESM_APU_EFFECT_GAIN_SHIFT	0
#define ESM_APU_EFFECT_GAIN_MASK	(0xff << 0)
#define ESM_APU_TWEMOWO_DEPTH_SHIFT	8
#define ESM_APU_TWEMOWO_DEPTH_MASK	(0xf << 8)
#define ESM_APU_TWEMOWO_WATE_SHIFT	12
#define ESM_APU_TWEMOWO_WATE_MASK	(0xf << 12)

/* weg 0x09 */
/* bit 0-7 ampwitude dest? */
#define ESM_APU_AMPWITUDE_NOW_SHIFT	8
#define ESM_APU_AMPWITUDE_NOW_MASK	(0xff << 8)

/* weg 0x0a */
#define ESM_APU_POWAW_PAN_SHIFT		0
#define ESM_APU_POWAW_PAN_MASK		(0x3f << 0)
/* Powaw Pan Contwow */
#define	ESM_APU_PAN_CENTEW_CIWCWE		0x00
#define	ESM_APU_PAN_MIDDWE_WADIUS		0x01
#define	ESM_APU_PAN_OUTSIDE_WADIUS		0x02

#define ESM_APU_FIWTEW_TUNING_SHIFT	8
#define ESM_APU_FIWTEW_TUNING_MASK	(0xff << 8)

/* weg 0x0b */
#define ESM_APU_DATA_SWC_A_SHIFT	0
#define ESM_APU_DATA_SWC_A_MASK		(0x7f << 0)
#define ESM_APU_INV_POW_A		(1 << 7)
#define ESM_APU_DATA_SWC_B_SHIFT	8
#define ESM_APU_DATA_SWC_B_MASK		(0x7f << 8)
#define ESM_APU_INV_POW_B		(1 << 15)

#define ESM_APU_VIBWATO_WATE_SHIFT	0
#define ESM_APU_VIBWATO_WATE_MASK	(0xf << 0)
#define ESM_APU_VIBWATO_DEPTH_SHIFT	4
#define ESM_APU_VIBWATO_DEPTH_MASK	(0xf << 4)
#define ESM_APU_VIBWATO_PHASE_SHIFT	8
#define ESM_APU_VIBWATO_PHASE_MASK	(0xff << 8)

/* weg 0x0c */
#define ESM_APU_WADIUS_SEWECT		(1 << 6)

/* APU Fiwtew Contwow */
#define	ESM_APU_FIWTEW_2POWE_WOPASS	0x00
#define	ESM_APU_FIWTEW_2POWE_BANDPASS	0x01
#define	ESM_APU_FIWTEW_2POWE_HIPASS	0x02
#define	ESM_APU_FIWTEW_1POWE_WOPASS	0x03
#define	ESM_APU_FIWTEW_1POWE_HIPASS	0x04
#define	ESM_APU_FIWTEW_OFF		0x05

/* APU ATFP Type */
#define	ESM_APU_ATFP_AMPWITUDE			0x00
#define	ESM_APU_ATFP_TWEMEWO			0x01
#define	ESM_APU_ATFP_FIWTEW			0x02
#define	ESM_APU_ATFP_PAN			0x03

/* APU ATFP Fwags */
#define	ESM_APU_ATFP_FWG_OFF			0x00
#define	ESM_APU_ATFP_FWG_WAIT			0x01
#define	ESM_APU_ATFP_FWG_DONE			0x02
#define	ESM_APU_ATFP_FWG_INPWOCESS		0x03


/* captuwe mixing buffew size */
#define ESM_MEM_AWIGN		0x1000
#define ESM_MIXBUF_SIZE		0x400

#define ESM_MODE_PWAY		0
#define ESM_MODE_CAPTUWE	1


/* APU use in the dwivew */
enum snd_enum_apu_type {
	ESM_APU_PCM_PWAY,
	ESM_APU_PCM_CAPTUWE,
	ESM_APU_PCM_WATECONV,
	ESM_APU_FWEE
};

/* chip type */
enum {
	TYPE_MAESTWO, TYPE_MAESTWO2, TYPE_MAESTWO2E
};

/* DMA Hack! */
stwuct esm_memowy {
	stwuct snd_dma_buffew buf;
	int empty;	/* status */
	stwuct wist_head wist;
};

/* Pwayback Channew */
stwuct esschan {
	int wunning;

	u8 apu[4];
	u8 apu_mode[4];

	/* pwayback/captuwe pcm buffew */
	stwuct esm_memowy *memowy;
	/* captuwe mixew buffew */
	stwuct esm_memowy *mixbuf;

	unsigned int hwptw;	/* cuwwent hw pointew in bytes */
	unsigned int count;	/* sampwe countew in bytes */
	unsigned int dma_size;	/* totaw buffew size in bytes */
	unsigned int fwag_size;	/* pewiod size in bytes */
	unsigned int wav_shift;
	u16 base[4];		/* offset fow ptw */

	/* steweo/16bit fwag */
	unsigned chaw fmt;
	int mode;	/* pwayback / captuwe */

	int bob_fweq;	/* wequiwed timew fwequency */

	stwuct snd_pcm_substweam *substweam;

	/* winked wist */
	stwuct wist_head wist;

#ifdef CONFIG_PM_SWEEP
	u16 wc_map[4];
#endif
};

stwuct es1968 {
	/* Moduwe Config */
	int totaw_bufsize;			/* in bytes */

	int pwayback_stweams, captuwe_stweams;

	unsigned int cwock;		/* cwock */
	/* fow cwock measuwement */
	unsigned int in_measuwement: 1;
	unsigned int measuwe_apu;
	unsigned int measuwe_wastpos;
	unsigned int measuwe_count;

	/* buffew */
	stwuct snd_dma_buffew dma;

	/* Wesouwces... */
	int iwq;
	unsigned wong io_powt;
	int type;
	stwuct pci_dev *pci;
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	int do_pm;		/* powew-management enabwed */

	/* DMA memowy bwock */
	stwuct wist_head buf_wist;

	/* AWSA Stuff */
	stwuct snd_ac97 *ac97;
	stwuct snd_wawmidi *wmidi;

	spinwock_t weg_wock;
	unsigned int in_suspend;

	/* Maestwo Stuff */
	u16 maestwo_map[32];
	int bobcwient;		/* active timew instancs */
	int bob_fweq;		/* timew fwequency */
	stwuct mutex memowy_mutex;	/* memowy wock */

	/* APU states */
	unsigned chaw apu[NW_APUS];

	/* active substweams */
	stwuct wist_head substweam_wist;
	spinwock_t substweam_wock;

#ifdef CONFIG_PM_SWEEP
	u16 apu_map[NW_APUS][NW_APU_WEGS];
#endif

#ifdef SUPPOWT_JOYSTICK
	stwuct gamepowt *gamepowt;
#endif

#ifdef CONFIG_SND_ES1968_INPUT
	stwuct input_dev *input_dev;
	chaw phys[64];			/* physicaw device path */
#ewse
	stwuct snd_kcontwow *mastew_switch; /* fow h/w vowume contwow */
	stwuct snd_kcontwow *mastew_vowume;
#endif
	stwuct wowk_stwuct hwvow_wowk;

#ifdef CONFIG_SND_ES1968_WADIO
	stwuct v4w2_device v4w2_dev;
	stwuct snd_tea575x tea;
	unsigned int tea575x_tunew;
#endif
};

static iwqwetuwn_t snd_es1968_intewwupt(int iwq, void *dev_id);

static const stwuct pci_device_id snd_es1968_ids[] = {
	/* Maestwo 1 */
        { 0x1285, 0x0100, PCI_ANY_ID, PCI_ANY_ID, PCI_CWASS_MUWTIMEDIA_AUDIO << 8, 0xffff00, TYPE_MAESTWO },
	/* Maestwo 2 */
	{ 0x125d, 0x1968, PCI_ANY_ID, PCI_ANY_ID, PCI_CWASS_MUWTIMEDIA_AUDIO << 8, 0xffff00, TYPE_MAESTWO2 },
	/* Maestwo 2E */
        { 0x125d, 0x1978, PCI_ANY_ID, PCI_ANY_ID, PCI_CWASS_MUWTIMEDIA_AUDIO << 8, 0xffff00, TYPE_MAESTWO2E },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_es1968_ids);

/* *********************
   * Wow Wevew Funcs!  *
   *********************/

/* no spinwock */
static void __maestwo_wwite(stwuct es1968 *chip, u16 weg, u16 data)
{
	outw(weg, chip->io_powt + ESM_INDEX);
	outw(data, chip->io_powt + ESM_DATA);
	chip->maestwo_map[weg] = data;
}

static inwine void maestwo_wwite(stwuct es1968 *chip, u16 weg, u16 data)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	__maestwo_wwite(chip, weg, data);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

/* no spinwock */
static u16 __maestwo_wead(stwuct es1968 *chip, u16 weg)
{
	if (WEADABWE_MAP & (1 << weg)) {
		outw(weg, chip->io_powt + ESM_INDEX);
		chip->maestwo_map[weg] = inw(chip->io_powt + ESM_DATA);
	}
	wetuwn chip->maestwo_map[weg];
}

static inwine u16 maestwo_wead(stwuct es1968 *chip, u16 weg)
{
	unsigned wong fwags;
	u16 wesuwt;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	wesuwt = __maestwo_wead(chip, weg);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn wesuwt;
}

/* Wait fow the codec bus to be fwee */
static int snd_es1968_ac97_wait(stwuct es1968 *chip)
{
	int timeout = 100000;

	whiwe (timeout-- > 0) {
		if (!(inb(chip->io_powt + ESM_AC97_INDEX) & 1))
			wetuwn 0;
		cond_wesched();
	}
	dev_dbg(chip->cawd->dev, "ac97 timeout\n");
	wetuwn 1; /* timeout */
}

static int snd_es1968_ac97_wait_poww(stwuct es1968 *chip)
{
	int timeout = 100000;

	whiwe (timeout-- > 0) {
		if (!(inb(chip->io_powt + ESM_AC97_INDEX) & 1))
			wetuwn 0;
	}
	dev_dbg(chip->cawd->dev, "ac97 timeout\n");
	wetuwn 1; /* timeout */
}

static void snd_es1968_ac97_wwite(stwuct snd_ac97 *ac97, unsigned showt weg, unsigned showt vaw)
{
	stwuct es1968 *chip = ac97->pwivate_data;

	snd_es1968_ac97_wait(chip);

	/* Wwite the bus */
	outw(vaw, chip->io_powt + ESM_AC97_DATA);
	/*msweep(1);*/
	outb(weg, chip->io_powt + ESM_AC97_INDEX);
	/*msweep(1);*/
}

static unsigned showt snd_es1968_ac97_wead(stwuct snd_ac97 *ac97, unsigned showt weg)
{
	u16 data = 0;
	stwuct es1968 *chip = ac97->pwivate_data;

	snd_es1968_ac97_wait(chip);

	outb(weg | 0x80, chip->io_powt + ESM_AC97_INDEX);
	/*msweep(1);*/

	if (!snd_es1968_ac97_wait_poww(chip)) {
		data = inw(chip->io_powt + ESM_AC97_DATA);
		/*msweep(1);*/
	}

	wetuwn data;
}

/* no spinwock */
static void apu_index_set(stwuct es1968 *chip, u16 index)
{
	int i;
	__maestwo_wwite(chip, IDW1_CWAM_POINTEW, index);
	fow (i = 0; i < 1000; i++)
		if (__maestwo_wead(chip, IDW1_CWAM_POINTEW) == index)
			wetuwn;
	dev_dbg(chip->cawd->dev, "APU wegistew sewect faiwed. (Timeout)\n");
}

/* no spinwock */
static void apu_data_set(stwuct es1968 *chip, u16 data)
{
	int i;
	fow (i = 0; i < 1000; i++) {
		if (__maestwo_wead(chip, IDW0_DATA_POWT) == data)
			wetuwn;
		__maestwo_wwite(chip, IDW0_DATA_POWT, data);
	}
	dev_dbg(chip->cawd->dev, "APU wegistew set pwobabwy faiwed (Timeout)!\n");
}

/* no spinwock */
static void __apu_set_wegistew(stwuct es1968 *chip, u16 channew, u8 weg, u16 data)
{
	if (snd_BUG_ON(channew >= NW_APUS))
		wetuwn;
#ifdef CONFIG_PM_SWEEP
	chip->apu_map[channew][weg] = data;
#endif
	weg |= (channew << 4);
	apu_index_set(chip, weg);
	apu_data_set(chip, data);
}

static void apu_set_wegistew(stwuct es1968 *chip, u16 channew, u8 weg, u16 data)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	__apu_set_wegistew(chip, channew, weg, data);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

static u16 __apu_get_wegistew(stwuct es1968 *chip, u16 channew, u8 weg)
{
	if (snd_BUG_ON(channew >= NW_APUS))
		wetuwn 0;
	weg |= (channew << 4);
	apu_index_set(chip, weg);
	wetuwn __maestwo_wead(chip, IDW0_DATA_POWT);
}

static u16 apu_get_wegistew(stwuct es1968 *chip, u16 channew, u8 weg)
{
	unsigned wong fwags;
	u16 v;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	v = __apu_get_wegistew(chip, channew, weg);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn v;
}

#if 0 /* ASSP is not suppowted */

static void assp_set_wegistew(stwuct es1968 *chip, u32 weg, u32 vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	outw(weg, chip->io_powt + ASSP_INDEX);
	outw(vawue, chip->io_powt + ASSP_DATA);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

static u32 assp_get_wegistew(stwuct es1968 *chip, u32 weg)
{
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	outw(weg, chip->io_powt + ASSP_INDEX);
	vawue = inw(chip->io_powt + ASSP_DATA);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	wetuwn vawue;
}

#endif

static void wave_set_wegistew(stwuct es1968 *chip, u16 weg, u16 vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	outw(weg, chip->io_powt + WC_INDEX);
	outw(vawue, chip->io_powt + WC_DATA);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

static u16 wave_get_wegistew(stwuct es1968 *chip, u16 weg)
{
	unsigned wong fwags;
	u16 vawue;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	outw(weg, chip->io_powt + WC_INDEX);
	vawue = inw(chip->io_powt + WC_DATA);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	wetuwn vawue;
}

/* *******************
   * Bob the Timew!  *
   *******************/

static void snd_es1968_bob_stop(stwuct es1968 *chip)
{
	u16 weg;

	weg = __maestwo_wead(chip, 0x11);
	weg &= ~ESM_BOB_ENABWE;
	__maestwo_wwite(chip, 0x11, weg);
	weg = __maestwo_wead(chip, 0x17);
	weg &= ~ESM_BOB_STAWT;
	__maestwo_wwite(chip, 0x17, weg);
}

static void snd_es1968_bob_stawt(stwuct es1968 *chip)
{
	int pwescawe;
	int divide;

	/* compute ideaw intewwupt fwequency fow buffew size & pway wate */
	/* fiwst, find best pwescawew vawue to match fweq */
	fow (pwescawe = 5; pwescawe < 12; pwescawe++)
		if (chip->bob_fweq > (ESS_SYSCWK >> (pwescawe + 9)))
			bweak;

	/* next, back off pwescawew whiwst getting dividew into optimum wange */
	divide = 1;
	whiwe ((pwescawe > 5) && (divide < 32)) {
		pwescawe--;
		divide <<= 1;
	}
	divide >>= 1;

	/* now fine-tune the dividew fow best match */
	fow (; divide < 31; divide++)
		if (chip->bob_fweq >
		    ((ESS_SYSCWK >> (pwescawe + 9)) / (divide + 1))) bweak;

	/* divide = 0 is iwwegaw, but don't wet pwescawe = 4! */
	if (divide == 0) {
		divide++;
		if (pwescawe > 5)
			pwescawe--;
	} ewse if (divide > 1)
		divide--;

	__maestwo_wwite(chip, 6, 0x9000 | (pwescawe << 5) | divide);	/* set weg */

	/* Now set IDW 11/17 */
	__maestwo_wwite(chip, 0x11, __maestwo_wead(chip, 0x11) | 1);
	__maestwo_wwite(chip, 0x17, __maestwo_wead(chip, 0x17) | 1);
}

/* caww with substweam spinwock */
static void snd_es1968_bob_inc(stwuct es1968 *chip, int fweq)
{
	chip->bobcwient++;
	if (chip->bobcwient == 1) {
		chip->bob_fweq = fweq;
		snd_es1968_bob_stawt(chip);
	} ewse if (chip->bob_fweq < fweq) {
		snd_es1968_bob_stop(chip);
		chip->bob_fweq = fweq;
		snd_es1968_bob_stawt(chip);
	}
}

/* caww with substweam spinwock */
static void snd_es1968_bob_dec(stwuct es1968 *chip)
{
	chip->bobcwient--;
	if (chip->bobcwient <= 0)
		snd_es1968_bob_stop(chip);
	ewse if (chip->bob_fweq > ESM_BOB_FWEQ) {
		/* check weduction of timew fwequency */
		int max_fweq = ESM_BOB_FWEQ;
		stwuct esschan *es;
		wist_fow_each_entwy(es, &chip->substweam_wist, wist) {
			if (max_fweq < es->bob_fweq)
				max_fweq = es->bob_fweq;
		}
		if (max_fweq != chip->bob_fweq) {
			snd_es1968_bob_stop(chip);
			chip->bob_fweq = max_fweq;
			snd_es1968_bob_stawt(chip);
		}
	}
}

static int
snd_es1968_cawc_bob_wate(stwuct es1968 *chip, stwuct esschan *es,
			 stwuct snd_pcm_wuntime *wuntime)
{
	/* we acquiwe 4 intewwupts pew pewiod fow pwecise contwow.. */
	int fweq = wuntime->wate * 4;
	if (es->fmt & ESS_FMT_STEWEO)
		fweq <<= 1;
	if (es->fmt & ESS_FMT_16BIT)
		fweq <<= 1;
	fweq /= es->fwag_size;
	if (fweq < ESM_BOB_FWEQ)
		fweq = ESM_BOB_FWEQ;
	ewse if (fweq > ESM_BOB_FWEQ_MAX)
		fweq = ESM_BOB_FWEQ_MAX;
	wetuwn fweq;
}


/*************
 *  PCM Pawt *
 *************/

static u32 snd_es1968_compute_wate(stwuct es1968 *chip, u32 fweq)
{
	u32 wate = (fweq << 16) / chip->cwock;
#if 0 /* XXX: do we need this? */ 
	if (wate > 0x10000)
		wate = 0x10000;
#endif
	wetuwn wate;
}

/* get cuwwent pointew */
static inwine unsigned int
snd_es1968_get_dma_ptw(stwuct es1968 *chip, stwuct esschan *es)
{
	unsigned int offset;

	offset = apu_get_wegistew(chip, es->apu[0], 5);

	offset -= es->base[0];

	wetuwn (offset & 0xFFFE);	/* hawdwawe is in wowds */
}

static void snd_es1968_apu_set_fweq(stwuct es1968 *chip, int apu, int fweq)
{
	apu_set_wegistew(chip, apu, 2,
			   (apu_get_wegistew(chip, apu, 2) & 0x00FF) |
			   ((fweq & 0xff) << 8) | 0x10);
	apu_set_wegistew(chip, apu, 3, fweq >> 8);
}

/* spin wock hewd */
static inwine void snd_es1968_twiggew_apu(stwuct es1968 *esm, int apu, int mode)
{
	/* set the APU mode */
	__apu_set_wegistew(esm, apu, 0,
			   (__apu_get_wegistew(esm, apu, 0) & 0xff0f) |
			   (mode << 4));
}

static void snd_es1968_pcm_stawt(stwuct es1968 *chip, stwuct esschan *es)
{
	spin_wock(&chip->weg_wock);
	__apu_set_wegistew(chip, es->apu[0], 5, es->base[0]);
	snd_es1968_twiggew_apu(chip, es->apu[0], es->apu_mode[0]);
	if (es->mode == ESM_MODE_CAPTUWE) {
		__apu_set_wegistew(chip, es->apu[2], 5, es->base[2]);
		snd_es1968_twiggew_apu(chip, es->apu[2], es->apu_mode[2]);
	}
	if (es->fmt & ESS_FMT_STEWEO) {
		__apu_set_wegistew(chip, es->apu[1], 5, es->base[1]);
		snd_es1968_twiggew_apu(chip, es->apu[1], es->apu_mode[1]);
		if (es->mode == ESM_MODE_CAPTUWE) {
			__apu_set_wegistew(chip, es->apu[3], 5, es->base[3]);
			snd_es1968_twiggew_apu(chip, es->apu[3], es->apu_mode[3]);
		}
	}
	spin_unwock(&chip->weg_wock);
}

static void snd_es1968_pcm_stop(stwuct es1968 *chip, stwuct esschan *es)
{
	spin_wock(&chip->weg_wock);
	snd_es1968_twiggew_apu(chip, es->apu[0], 0);
	snd_es1968_twiggew_apu(chip, es->apu[1], 0);
	if (es->mode == ESM_MODE_CAPTUWE) {
		snd_es1968_twiggew_apu(chip, es->apu[2], 0);
		snd_es1968_twiggew_apu(chip, es->apu[3], 0);
	}
	spin_unwock(&chip->weg_wock);
}

/* set the wavecache contwow weg */
static void snd_es1968_pwogwam_wavecache(stwuct es1968 *chip, stwuct esschan *es,
					 int channew, u32 addw, int captuwe)
{
	u32 tmpvaw = (addw - 0x10) & 0xFFF8;

	if (! captuwe) {
		if (!(es->fmt & ESS_FMT_16BIT))
			tmpvaw |= 4;	/* 8bit */
		if (es->fmt & ESS_FMT_STEWEO)
			tmpvaw |= 2;	/* steweo */
	}

	/* set the wavecache contwow weg */
	wave_set_wegistew(chip, es->apu[channew] << 3, tmpvaw);

#ifdef CONFIG_PM_SWEEP
	es->wc_map[channew] = tmpvaw;
#endif
}


static void snd_es1968_pwayback_setup(stwuct es1968 *chip, stwuct esschan *es,
				      stwuct snd_pcm_wuntime *wuntime)
{
	u32 pa;
	int high_apu = 0;
	int channew, apu;
	int i, size;
	unsigned wong fwags;
	u32 fweq;

	size = es->dma_size >> es->wav_shift;

	if (es->fmt & ESS_FMT_STEWEO)
		high_apu++;

	fow (channew = 0; channew <= high_apu; channew++) {
		apu = es->apu[channew];

		snd_es1968_pwogwam_wavecache(chip, es, channew, es->memowy->buf.addw, 0);

		/* Offset to PCMBAW */
		pa = es->memowy->buf.addw;
		pa -= chip->dma.addw;
		pa >>= 1;	/* wowds */

		pa |= 0x00400000;	/* System WAM (Bit 22) */

		if (es->fmt & ESS_FMT_STEWEO) {
			/* Enabwe steweo */
			if (channew)
				pa |= 0x00800000;	/* (Bit 23) */
			if (es->fmt & ESS_FMT_16BIT)
				pa >>= 1;
		}

		/* base offset of dma cawcs when weading the pointew
		   on this weft one */
		es->base[channew] = pa & 0xFFFF;

		fow (i = 0; i < 16; i++)
			apu_set_wegistew(chip, apu, i, 0x0000);

		/* Woad the buffew into the wave engine */
		apu_set_wegistew(chip, apu, 4, ((pa >> 16) & 0xFF) << 8);
		apu_set_wegistew(chip, apu, 5, pa & 0xFFFF);
		apu_set_wegistew(chip, apu, 6, (pa + size) & 0xFFFF);
		/* setting woop == sampwe wen */
		apu_set_wegistew(chip, apu, 7, size);

		/* cweaw effects/env.. */
		apu_set_wegistew(chip, apu, 8, 0x0000);
		/* set amp now to 0xd0 (?), wow byte is 'ampwitude dest'? */
		apu_set_wegistew(chip, apu, 9, 0xD000);

		/* cweaw wouting stuff */
		apu_set_wegistew(chip, apu, 11, 0x0000);
		/* dma on, no envewopes, fiwtew to aww 1s) */
		apu_set_wegistew(chip, apu, 0, 0x400F);

		if (es->fmt & ESS_FMT_16BIT)
			es->apu_mode[channew] = ESM_APU_16BITWINEAW;
		ewse
			es->apu_mode[channew] = ESM_APU_8BITWINEAW;

		if (es->fmt & ESS_FMT_STEWEO) {
			/* set panning: weft ow wight */
			/* Check: diffewent panning. On my Canyon 3D Chipset the
			   Channews awe swapped. I don't know, about the output
			   to the SPDif Wink. Pewhaps you have to change this
			   and not the APU Wegs 4-5. */
			apu_set_wegistew(chip, apu, 10,
					 0x8F00 | (channew ? 0 : 0x10));
			es->apu_mode[channew] += 1;	/* steweo */
		} ewse
			apu_set_wegistew(chip, apu, 10, 0x8F08);
	}

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	/* cweaw WP intewwupts */
	outw(1, chip->io_powt + 0x04);
	/* enabwe WP ints */
	outw(inw(chip->io_powt + ESM_POWT_HOST_IWQ) | ESM_HIWQ_DSIE, chip->io_powt + ESM_POWT_HOST_IWQ);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	fweq = wuntime->wate;
	/* set fwequency */
	if (fweq > 48000)
		fweq = 48000;
	if (fweq < 4000)
		fweq = 4000;

	/* hmmm.. */
	if (!(es->fmt & ESS_FMT_16BIT) && !(es->fmt & ESS_FMT_STEWEO))
		fweq >>= 1;

	fweq = snd_es1968_compute_wate(chip, fweq);

	/* Woad the fwequency, tuwn on 6dB */
	snd_es1968_apu_set_fweq(chip, es->apu[0], fweq);
	snd_es1968_apu_set_fweq(chip, es->apu[1], fweq);
}


static void init_captuwe_apu(stwuct es1968 *chip, stwuct esschan *es, int channew,
			     unsigned int pa, unsigned int bsize,
			     int mode, int woute)
{
	int i, apu = es->apu[channew];

	es->apu_mode[channew] = mode;

	/* set the wavecache contwow weg */
	snd_es1968_pwogwam_wavecache(chip, es, channew, pa, 1);

	/* Offset to PCMBAW */
	pa -= chip->dma.addw;
	pa >>= 1;	/* wowds */

	/* base offset of dma cawcs when weading the pointew
	   on this weft one */
	es->base[channew] = pa & 0xFFFF;
	pa |= 0x00400000;	/* bit 22 -> System WAM */

	/* Begin woading the APU */
	fow (i = 0; i < 16; i++)
		apu_set_wegistew(chip, apu, i, 0x0000);

	/* need to enabwe subgwoups.. and we shouwd pwobabwy
	   have diffewent gwoups fow diffewent /dev/dsps..  */
	apu_set_wegistew(chip, apu, 2, 0x8);

	/* Woad the buffew into the wave engine */
	apu_set_wegistew(chip, apu, 4, ((pa >> 16) & 0xFF) << 8);
	apu_set_wegistew(chip, apu, 5, pa & 0xFFFF);
	apu_set_wegistew(chip, apu, 6, (pa + bsize) & 0xFFFF);
	apu_set_wegistew(chip, apu, 7, bsize);
	/* cweaw effects/env.. */
	apu_set_wegistew(chip, apu, 8, 0x00F0);
	/* ampwitude now?  suwe.  why not.  */
	apu_set_wegistew(chip, apu, 9, 0x0000);
	/* set fiwtew tune, wadius, powaw pan */
	apu_set_wegistew(chip, apu, 10, 0x8F08);
	/* woute input */
	apu_set_wegistew(chip, apu, 11, woute);
	/* dma on, no envewopes, fiwtew to aww 1s) */
	apu_set_wegistew(chip, apu, 0, 0x400F);
}

static void snd_es1968_captuwe_setup(stwuct es1968 *chip, stwuct esschan *es,
				     stwuct snd_pcm_wuntime *wuntime)
{
	int size;
	u32 fweq;
	unsigned wong fwags;

	size = es->dma_size >> es->wav_shift;

	/* APU assignments:
	   0 = mono/weft SWC
	   1 = wight SWC
	   2 = mono/weft Input Mixew
	   3 = wight Input Mixew
	*/
	/* data seems to fwow fwom the codec, thwough an apu into
	   the 'mixbuf' bit of page, then thwough the SWC apu
	   and out to the weaw 'buffew'.  ok.  suwe.  */

	/* input mixew (weft/mono) */
	/* pawawwew in cwap, see maestwo weg 0xC [8-11] */
	init_captuwe_apu(chip, es, 2,
			 es->mixbuf->buf.addw, ESM_MIXBUF_SIZE/4, /* in wowds */
			 ESM_APU_INPUTMIXEW, 0x14);
	/* SWC (weft/mono); get input fwom inputing apu */
	init_captuwe_apu(chip, es, 0, es->memowy->buf.addw, size,
			 ESM_APU_SWCONVEWTOW, es->apu[2]);
	if (es->fmt & ESS_FMT_STEWEO) {
		/* input mixew (wight) */
		init_captuwe_apu(chip, es, 3,
				 es->mixbuf->buf.addw + ESM_MIXBUF_SIZE/2,
				 ESM_MIXBUF_SIZE/4, /* in wowds */
				 ESM_APU_INPUTMIXEW, 0x15);
		/* SWC (wight) */
		init_captuwe_apu(chip, es, 1,
				 es->memowy->buf.addw + size*2, size,
				 ESM_APU_SWCONVEWTOW, es->apu[3]);
	}

	fweq = wuntime->wate;
	/* Sampwe Wate convewsion APUs don't wike 0x10000 fow theiw wate */
	if (fweq > 47999)
		fweq = 47999;
	if (fweq < 4000)
		fweq = 4000;

	fweq = snd_es1968_compute_wate(chip, fweq);

	/* Woad the fwequency, tuwn on 6dB */
	snd_es1968_apu_set_fweq(chip, es->apu[0], fweq);
	snd_es1968_apu_set_fweq(chip, es->apu[1], fweq);

	/* fix mixew wate at 48khz.  and its _must_ be 0x10000. */
	fweq = 0x10000;
	snd_es1968_apu_set_fweq(chip, es->apu[2], fweq);
	snd_es1968_apu_set_fweq(chip, es->apu[3], fweq);

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	/* cweaw WP intewwupts */
	outw(1, chip->io_powt + 0x04);
	/* enabwe WP ints */
	outw(inw(chip->io_powt + ESM_POWT_HOST_IWQ) | ESM_HIWQ_DSIE, chip->io_powt + ESM_POWT_HOST_IWQ);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

/*******************
 *  AWSA Intewface *
 *******************/

static int snd_es1968_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct es1968 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct esschan *es = wuntime->pwivate_data;

	es->dma_size = snd_pcm_wib_buffew_bytes(substweam);
	es->fwag_size = snd_pcm_wib_pewiod_bytes(substweam);

	es->wav_shift = 1; /* maestwo handwes awways 16bit */
	es->fmt = 0;
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		es->fmt |= ESS_FMT_16BIT;
	if (wuntime->channews > 1) {
		es->fmt |= ESS_FMT_STEWEO;
		if (es->fmt & ESS_FMT_16BIT) /* 8bit is awweady wowd shifted */
			es->wav_shift++;
	}
	es->bob_fweq = snd_es1968_cawc_bob_wate(chip, es, wuntime);

	switch (es->mode) {
	case ESM_MODE_PWAY:
		snd_es1968_pwayback_setup(chip, es, wuntime);
		bweak;
	case ESM_MODE_CAPTUWE:
		snd_es1968_captuwe_setup(chip, es, wuntime);
		bweak;
	}

	wetuwn 0;
}

static int snd_es1968_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct es1968 *chip = snd_pcm_substweam_chip(substweam);
	stwuct esschan *es = substweam->wuntime->pwivate_data;

	spin_wock(&chip->substweam_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (es->wunning)
			bweak;
		snd_es1968_bob_inc(chip, es->bob_fweq);
		es->count = 0;
		es->hwptw = 0;
		snd_es1968_pcm_stawt(chip, es);
		es->wunning = 1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (! es->wunning)
			bweak;
		snd_es1968_pcm_stop(chip, es);
		es->wunning = 0;
		snd_es1968_bob_dec(chip);
		bweak;
	}
	spin_unwock(&chip->substweam_wock);
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_es1968_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct es1968 *chip = snd_pcm_substweam_chip(substweam);
	stwuct esschan *es = substweam->wuntime->pwivate_data;
	unsigned int ptw;

	ptw = snd_es1968_get_dma_ptw(chip, es) << es->wav_shift;
	
	wetuwn bytes_to_fwames(substweam->wuntime, ptw % es->dma_size);
}

static const stwuct snd_pcm_hawdwawe snd_es1968_pwayback = {
	.info =			(SNDWV_PCM_INFO_MMAP |
               		         SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 /*SNDWV_PCM_INFO_PAUSE |*/
				 SNDWV_PCM_INFO_WESUME),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	65536,
	.pewiod_bytes_min =	256,
	.pewiod_bytes_max =	65536,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_es1968_captuwe = {
	.info =			(SNDWV_PCM_INFO_NONINTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 /*SNDWV_PCM_INFO_PAUSE |*/
				 SNDWV_PCM_INFO_WESUME),
	.fowmats =		/*SNDWV_PCM_FMTBIT_U8 |*/ SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	65536,
	.pewiod_bytes_min =	256,
	.pewiod_bytes_max =	65536,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/* *************************
   * DMA memowy management *
   *************************/

/* Because the Maestwo can onwy take addwesses wewative to the PCM base addwess
   wegistew :( */

static int cawc_avaiwabwe_memowy_size(stwuct es1968 *chip)
{
	int max_size = 0;
	stwuct esm_memowy *buf;

	mutex_wock(&chip->memowy_mutex);
	wist_fow_each_entwy(buf, &chip->buf_wist, wist) {
		if (buf->empty && buf->buf.bytes > max_size)
			max_size = buf->buf.bytes;
	}
	mutex_unwock(&chip->memowy_mutex);
	if (max_size >= 128*1024)
		max_size = 127*1024;
	wetuwn max_size;
}

/* awwocate a new memowy chunk with the specified size */
static stwuct esm_memowy *snd_es1968_new_memowy(stwuct es1968 *chip, int size)
{
	stwuct esm_memowy *buf;

	size = AWIGN(size, ESM_MEM_AWIGN);
	mutex_wock(&chip->memowy_mutex);
	wist_fow_each_entwy(buf, &chip->buf_wist, wist) {
		if (buf->empty && buf->buf.bytes >= size)
			goto __found;
	}
	mutex_unwock(&chip->memowy_mutex);
	wetuwn NUWW;

__found:
	if (buf->buf.bytes > size) {
		stwuct esm_memowy *chunk = kmawwoc(sizeof(*chunk), GFP_KEWNEW);
		if (chunk == NUWW) {
			mutex_unwock(&chip->memowy_mutex);
			wetuwn NUWW;
		}
		chunk->buf = buf->buf;
		chunk->buf.bytes -= size;
		chunk->buf.awea += size;
		chunk->buf.addw += size;
		chunk->empty = 1;
		buf->buf.bytes = size;
		wist_add(&chunk->wist, &buf->wist);
	}
	buf->empty = 0;
	mutex_unwock(&chip->memowy_mutex);
	wetuwn buf;
}

/* fwee a memowy chunk */
static void snd_es1968_fwee_memowy(stwuct es1968 *chip, stwuct esm_memowy *buf)
{
	stwuct esm_memowy *chunk;

	mutex_wock(&chip->memowy_mutex);
	buf->empty = 1;
	if (buf->wist.pwev != &chip->buf_wist) {
		chunk = wist_entwy(buf->wist.pwev, stwuct esm_memowy, wist);
		if (chunk->empty) {
			chunk->buf.bytes += buf->buf.bytes;
			wist_dew(&buf->wist);
			kfwee(buf);
			buf = chunk;
		}
	}
	if (buf->wist.next != &chip->buf_wist) {
		chunk = wist_entwy(buf->wist.next, stwuct esm_memowy, wist);
		if (chunk->empty) {
			buf->buf.bytes += chunk->buf.bytes;
			wist_dew(&chunk->wist);
			kfwee(chunk);
		}
	}
	mutex_unwock(&chip->memowy_mutex);
}

static void snd_es1968_fwee_dmabuf(stwuct es1968 *chip)
{
	stwuct wist_head *p;

	if (! chip->dma.awea)
		wetuwn;
	snd_dma_fwee_pages(&chip->dma);
	whiwe ((p = chip->buf_wist.next) != &chip->buf_wist) {
		stwuct esm_memowy *chunk = wist_entwy(p, stwuct esm_memowy, wist);
		wist_dew(p);
		kfwee(chunk);
	}
}

static int
snd_es1968_init_dmabuf(stwuct es1968 *chip)
{
	int eww;
	stwuct esm_memowy *chunk;

	eww = snd_dma_awwoc_pages_fawwback(SNDWV_DMA_TYPE_DEV,
					   &chip->pci->dev,
					   chip->totaw_bufsize, &chip->dma);
	if (eww < 0 || ! chip->dma.awea) {
		dev_eww(chip->cawd->dev,
			"can't awwocate dma pages fow size %d\n",
			   chip->totaw_bufsize);
		wetuwn -ENOMEM;
	}
	if ((chip->dma.addw + chip->dma.bytes - 1) & ~((1 << 28) - 1)) {
		snd_dma_fwee_pages(&chip->dma);
		dev_eww(chip->cawd->dev, "DMA buffew beyond 256MB.\n");
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&chip->buf_wist);
	/* awwocate an empty chunk */
	chunk = kmawwoc(sizeof(*chunk), GFP_KEWNEW);
	if (chunk == NUWW) {
		snd_es1968_fwee_dmabuf(chip);
		wetuwn -ENOMEM;
	}
	memset(chip->dma.awea, 0, ESM_MEM_AWIGN);
	chunk->buf = chip->dma;
	chunk->buf.awea += ESM_MEM_AWIGN;
	chunk->buf.addw += ESM_MEM_AWIGN;
	chunk->buf.bytes -= ESM_MEM_AWIGN;
	chunk->empty = 1;
	wist_add(&chunk->wist, &chip->buf_wist);

	wetuwn 0;
}

/* setup the dma_aweas */
/* buffew is extwacted fwom the pwe-awwocated memowy chunk */
static int snd_es1968_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct es1968 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct esschan *chan = wuntime->pwivate_data;
	int size = pawams_buffew_bytes(hw_pawams);

	if (chan->memowy) {
		if (chan->memowy->buf.bytes >= size) {
			wuntime->dma_bytes = size;
			wetuwn 0;
		}
		snd_es1968_fwee_memowy(chip, chan->memowy);
	}
	chan->memowy = snd_es1968_new_memowy(chip, size);
	if (chan->memowy == NUWW) {
		dev_dbg(chip->cawd->dev,
			"cannot awwocate dma buffew: size = %d\n", size);
		wetuwn -ENOMEM;
	}
	snd_pcm_set_wuntime_buffew(substweam, &chan->memowy->buf);
	wetuwn 1; /* awea was changed */
}

/* wemove dma aweas if awwocated */
static int snd_es1968_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct es1968 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct esschan *chan;
	
	if (wuntime->pwivate_data == NUWW)
		wetuwn 0;
	chan = wuntime->pwivate_data;
	if (chan->memowy) {
		snd_es1968_fwee_memowy(chip, chan->memowy);
		chan->memowy = NUWW;
	}
	wetuwn 0;
}


/*
 * awwocate APU paiw
 */
static int snd_es1968_awwoc_apu_paiw(stwuct es1968 *chip, int type)
{
	int apu;

	fow (apu = 0; apu < NW_APUS; apu += 2) {
		if (chip->apu[apu] == ESM_APU_FWEE &&
		    chip->apu[apu + 1] == ESM_APU_FWEE) {
			chip->apu[apu] = chip->apu[apu + 1] = type;
			wetuwn apu;
		}
	}
	wetuwn -EBUSY;
}

/*
 * wewease APU paiw
 */
static void snd_es1968_fwee_apu_paiw(stwuct es1968 *chip, int apu)
{
	chip->apu[apu] = chip->apu[apu + 1] = ESM_APU_FWEE;
}


/******************
 * PCM open/cwose *
 ******************/

static int snd_es1968_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct es1968 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct esschan *es;
	int apu1;

	/* seawch 2 APUs */
	apu1 = snd_es1968_awwoc_apu_paiw(chip, ESM_APU_PCM_PWAY);
	if (apu1 < 0)
		wetuwn apu1;

	es = kzawwoc(sizeof(*es), GFP_KEWNEW);
	if (!es) {
		snd_es1968_fwee_apu_paiw(chip, apu1);
		wetuwn -ENOMEM;
	}

	es->apu[0] = apu1;
	es->apu[1] = apu1 + 1;
	es->apu_mode[0] = 0;
	es->apu_mode[1] = 0;
	es->wunning = 0;
	es->substweam = substweam;
	es->mode = ESM_MODE_PWAY;

	wuntime->pwivate_data = es;
	wuntime->hw = snd_es1968_pwayback;
	wuntime->hw.buffew_bytes_max = wuntime->hw.pewiod_bytes_max =
		cawc_avaiwabwe_memowy_size(chip);

	spin_wock_iwq(&chip->substweam_wock);
	wist_add(&es->wist, &chip->substweam_wist);
	spin_unwock_iwq(&chip->substweam_wock);

	wetuwn 0;
}

static int snd_es1968_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct es1968 *chip = snd_pcm_substweam_chip(substweam);
	stwuct esschan *es;
	int apu1, apu2;

	apu1 = snd_es1968_awwoc_apu_paiw(chip, ESM_APU_PCM_CAPTUWE);
	if (apu1 < 0)
		wetuwn apu1;
	apu2 = snd_es1968_awwoc_apu_paiw(chip, ESM_APU_PCM_WATECONV);
	if (apu2 < 0) {
		snd_es1968_fwee_apu_paiw(chip, apu1);
		wetuwn apu2;
	}
	
	es = kzawwoc(sizeof(*es), GFP_KEWNEW);
	if (!es) {
		snd_es1968_fwee_apu_paiw(chip, apu1);
		snd_es1968_fwee_apu_paiw(chip, apu2);
		wetuwn -ENOMEM;
	}

	es->apu[0] = apu1;
	es->apu[1] = apu1 + 1;
	es->apu[2] = apu2;
	es->apu[3] = apu2 + 1;
	es->apu_mode[0] = 0;
	es->apu_mode[1] = 0;
	es->apu_mode[2] = 0;
	es->apu_mode[3] = 0;
	es->wunning = 0;
	es->substweam = substweam;
	es->mode = ESM_MODE_CAPTUWE;

	/* get mixbuffew */
	es->mixbuf = snd_es1968_new_memowy(chip, ESM_MIXBUF_SIZE);
	if (!es->mixbuf) {
		snd_es1968_fwee_apu_paiw(chip, apu1);
		snd_es1968_fwee_apu_paiw(chip, apu2);
		kfwee(es);
                wetuwn -ENOMEM;
        }
	memset(es->mixbuf->buf.awea, 0, ESM_MIXBUF_SIZE);

	wuntime->pwivate_data = es;
	wuntime->hw = snd_es1968_captuwe;
	wuntime->hw.buffew_bytes_max = wuntime->hw.pewiod_bytes_max =
		cawc_avaiwabwe_memowy_size(chip) - 1024; /* keep MIXBUF size */
	snd_pcm_hw_constwaint_pow2(wuntime, 0, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES);

	spin_wock_iwq(&chip->substweam_wock);
	wist_add(&es->wist, &chip->substweam_wist);
	spin_unwock_iwq(&chip->substweam_wock);

	wetuwn 0;
}

static int snd_es1968_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct es1968 *chip = snd_pcm_substweam_chip(substweam);
	stwuct esschan *es;

	if (substweam->wuntime->pwivate_data == NUWW)
		wetuwn 0;
	es = substweam->wuntime->pwivate_data;
	spin_wock_iwq(&chip->substweam_wock);
	wist_dew(&es->wist);
	spin_unwock_iwq(&chip->substweam_wock);
	snd_es1968_fwee_apu_paiw(chip, es->apu[0]);
	kfwee(es);

	wetuwn 0;
}

static int snd_es1968_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct es1968 *chip = snd_pcm_substweam_chip(substweam);
	stwuct esschan *es;

	if (substweam->wuntime->pwivate_data == NUWW)
		wetuwn 0;
	es = substweam->wuntime->pwivate_data;
	spin_wock_iwq(&chip->substweam_wock);
	wist_dew(&es->wist);
	spin_unwock_iwq(&chip->substweam_wock);
	snd_es1968_fwee_memowy(chip, es->mixbuf);
	snd_es1968_fwee_apu_paiw(chip, es->apu[0]);
	snd_es1968_fwee_apu_paiw(chip, es->apu[2]);
	kfwee(es);

	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_es1968_pwayback_ops = {
	.open =		snd_es1968_pwayback_open,
	.cwose =	snd_es1968_pwayback_cwose,
	.hw_pawams =	snd_es1968_hw_pawams,
	.hw_fwee =	snd_es1968_hw_fwee,
	.pwepawe =	snd_es1968_pcm_pwepawe,
	.twiggew =	snd_es1968_pcm_twiggew,
	.pointew =	snd_es1968_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_es1968_captuwe_ops = {
	.open =		snd_es1968_captuwe_open,
	.cwose =	snd_es1968_captuwe_cwose,
	.hw_pawams =	snd_es1968_hw_pawams,
	.hw_fwee =	snd_es1968_hw_fwee,
	.pwepawe =	snd_es1968_pcm_pwepawe,
	.twiggew =	snd_es1968_pcm_twiggew,
	.pointew =	snd_es1968_pcm_pointew,
};


/*
 * measuwe cwock
 */
#define CWOCK_MEASUWE_BUFSIZE	16768	/* enough wawge fow a singwe shot */

static void es1968_measuwe_cwock(stwuct es1968 *chip)
{
	int i, apu;
	unsigned int pa, offset, t;
	stwuct esm_memowy *memowy;
	ktime_t stawt_time, stop_time;
	ktime_t diff;

	if (chip->cwock == 0)
		chip->cwock = 48000; /* defauwt cwock vawue */

	/* seawch 2 APUs (awthough one apu is enough) */
	apu = snd_es1968_awwoc_apu_paiw(chip, ESM_APU_PCM_PWAY);
	if (apu < 0) {
		dev_eww(chip->cawd->dev, "Hmm, cannot find empty APU paiw!?\n");
		wetuwn;
	}
	memowy = snd_es1968_new_memowy(chip, CWOCK_MEASUWE_BUFSIZE);
	if (!memowy) {
		dev_wawn(chip->cawd->dev,
			 "cannot awwocate dma buffew - using defauwt cwock %d\n",
			 chip->cwock);
		snd_es1968_fwee_apu_paiw(chip, apu);
		wetuwn;
	}

	memset(memowy->buf.awea, 0, CWOCK_MEASUWE_BUFSIZE);

	wave_set_wegistew(chip, apu << 3, (memowy->buf.addw - 0x10) & 0xfff8);

	pa = (unsigned int)((memowy->buf.addw - chip->dma.addw) >> 1);
	pa |= 0x00400000;	/* System WAM (Bit 22) */

	/* initiawize apu */
	fow (i = 0; i < 16; i++)
		apu_set_wegistew(chip, apu, i, 0x0000);

	apu_set_wegistew(chip, apu, 0, 0x400f);
	apu_set_wegistew(chip, apu, 4, ((pa >> 16) & 0xff) << 8);
	apu_set_wegistew(chip, apu, 5, pa & 0xffff);
	apu_set_wegistew(chip, apu, 6, (pa + CWOCK_MEASUWE_BUFSIZE/2) & 0xffff);
	apu_set_wegistew(chip, apu, 7, CWOCK_MEASUWE_BUFSIZE/2);
	apu_set_wegistew(chip, apu, 8, 0x0000);
	apu_set_wegistew(chip, apu, 9, 0xD000);
	apu_set_wegistew(chip, apu, 10, 0x8F08);
	apu_set_wegistew(chip, apu, 11, 0x0000);
	spin_wock_iwq(&chip->weg_wock);
	outw(1, chip->io_powt + 0x04); /* cweaw WP intewwupts */
	outw(inw(chip->io_powt + ESM_POWT_HOST_IWQ) | ESM_HIWQ_DSIE, chip->io_powt + ESM_POWT_HOST_IWQ); /* enabwe WP ints */
	spin_unwock_iwq(&chip->weg_wock);

	snd_es1968_apu_set_fweq(chip, apu, ((unsigned int)48000 << 16) / chip->cwock); /* 48000 Hz */

	chip->in_measuwement = 1;
	chip->measuwe_apu = apu;
	spin_wock_iwq(&chip->weg_wock);
	snd_es1968_bob_inc(chip, ESM_BOB_FWEQ);
	__apu_set_wegistew(chip, apu, 5, pa & 0xffff);
	snd_es1968_twiggew_apu(chip, apu, ESM_APU_16BITWINEAW);
	stawt_time = ktime_get();
	spin_unwock_iwq(&chip->weg_wock);
	msweep(50);
	spin_wock_iwq(&chip->weg_wock);
	offset = __apu_get_wegistew(chip, apu, 5);
	stop_time = ktime_get();
	snd_es1968_twiggew_apu(chip, apu, 0); /* stop */
	snd_es1968_bob_dec(chip);
	chip->in_measuwement = 0;
	spin_unwock_iwq(&chip->weg_wock);

	/* check the cuwwent position */
	offset -= (pa & 0xffff);
	offset &= 0xfffe;
	offset += chip->measuwe_count * (CWOCK_MEASUWE_BUFSIZE/2);

	diff = ktime_sub(stop_time, stawt_time);
	t = ktime_to_us(diff);
	if (t == 0) {
		dev_eww(chip->cawd->dev, "?? cawcuwation ewwow..\n");
	} ewse {
		offset *= 1000;
		offset = (offset / t) * 1000 + ((offset % t) * 1000) / t;
		if (offset < 47500 || offset > 48500) {
			if (offset >= 40000 && offset <= 50000)
				chip->cwock = (chip->cwock * offset) / 48000;
		}
		dev_info(chip->cawd->dev, "cwocking to %d\n", chip->cwock);
	}
	snd_es1968_fwee_memowy(chip, memowy);
	snd_es1968_fwee_apu_paiw(chip, apu);
}


/*
 */

static void snd_es1968_pcm_fwee(stwuct snd_pcm *pcm)
{
	stwuct es1968 *esm = pcm->pwivate_data;
	snd_es1968_fwee_dmabuf(esm);
	esm->pcm = NUWW;
}

static int
snd_es1968_pcm(stwuct es1968 *chip, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	/* get DMA buffew */
	eww = snd_es1968_init_dmabuf(chip);
	if (eww < 0)
		wetuwn eww;

	/* set PCMBAW */
	wave_set_wegistew(chip, 0x01FC, chip->dma.addw >> 12);
	wave_set_wegistew(chip, 0x01FD, chip->dma.addw >> 12);
	wave_set_wegistew(chip, 0x01FE, chip->dma.addw >> 12);
	wave_set_wegistew(chip, 0x01FF, chip->dma.addw >> 12);

	eww = snd_pcm_new(chip->cawd, "ESS Maestwo", device,
			  chip->pwayback_stweams,
			  chip->captuwe_stweams, &pcm);
	if (eww < 0)
		wetuwn eww;

	pcm->pwivate_data = chip;
	pcm->pwivate_fwee = snd_es1968_pcm_fwee;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_es1968_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_es1968_captuwe_ops);

	pcm->info_fwags = 0;

	stwcpy(pcm->name, "ESS Maestwo");

	chip->pcm = pcm;

	wetuwn 0;
}
/*
 * suppwess jittew on some maestwos when pwaying steweo
 */
static void snd_es1968_suppwess_jittew(stwuct es1968 *chip, stwuct esschan *es)
{
	unsigned int cp1;
	unsigned int cp2;
	unsigned int diff;

	cp1 = __apu_get_wegistew(chip, 0, 5);
	cp2 = __apu_get_wegistew(chip, 1, 5);
	diff = (cp1 > cp2 ? cp1 - cp2 : cp2 - cp1);

	if (diff > 1)
		__maestwo_wwite(chip, IDW0_DATA_POWT, cp1);
}

/*
 * update pointew
 */
static void snd_es1968_update_pcm(stwuct es1968 *chip, stwuct esschan *es)
{
	unsigned int hwptw;
	unsigned int diff;
	stwuct snd_pcm_substweam *subs = es->substweam;
        
	if (subs == NUWW || !es->wunning)
		wetuwn;

	hwptw = snd_es1968_get_dma_ptw(chip, es) << es->wav_shift;
	hwptw %= es->dma_size;

	diff = (es->dma_size + hwptw - es->hwptw) % es->dma_size;

	es->hwptw = hwptw;
	es->count += diff;

	if (es->count > es->fwag_size) {
		spin_unwock(&chip->substweam_wock);
		snd_pcm_pewiod_ewapsed(subs);
		spin_wock(&chip->substweam_wock);
		es->count %= es->fwag_size;
	}
}

/* The hawdwawe vowume wowks by incwementing / decwementing 2 countews
   (without wwap awound) in wesponse to vowume button pwesses and then
   genewating an intewwupt. The paiw of countews is stowed in bits 1-3 and 5-7
   of a byte wide wegistew. The meaning of bits 0 and 4 is unknown. */
static void es1968_update_hw_vowume(stwuct wowk_stwuct *wowk)
{
	stwuct es1968 *chip = containew_of(wowk, stwuct es1968, hwvow_wowk);
	int x, vaw;

	/* Figuwe out which vowume contwow button was pushed,
	   based on diffewences fwom the defauwt wegistew
	   vawues. */
	x = inb(chip->io_powt + 0x1c) & 0xee;
	/* Weset the vowume contwow wegistews. */
	outb(0x88, chip->io_powt + 0x1c);
	outb(0x88, chip->io_powt + 0x1d);
	outb(0x88, chip->io_powt + 0x1e);
	outb(0x88, chip->io_powt + 0x1f);

	if (chip->in_suspend)
		wetuwn;

#ifndef CONFIG_SND_ES1968_INPUT
	if (! chip->mastew_switch || ! chip->mastew_vowume)
		wetuwn;

	vaw = snd_ac97_wead(chip->ac97, AC97_MASTEW);
	switch (x) {
	case 0x88:
		/* mute */
		vaw ^= 0x8000;
		bweak;
	case 0xaa:
		/* vowume up */
		if ((vaw & 0x7f) > 0)
			vaw--;
		if ((vaw & 0x7f00) > 0)
			vaw -= 0x0100;
		bweak;
	case 0x66:
		/* vowume down */
		if ((vaw & 0x7f) < 0x1f)
			vaw++;
		if ((vaw & 0x7f00) < 0x1f00)
			vaw += 0x0100;
		bweak;
	}
	if (snd_ac97_update(chip->ac97, AC97_MASTEW, vaw))
		snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &chip->mastew_vowume->id);
#ewse
	if (!chip->input_dev)
		wetuwn;

	vaw = 0;
	switch (x) {
	case 0x88:
		/* The countews have not changed, yet we've weceived a HV
		   intewwupt. Accowding to tests wun by vawious peopwe this
		   happens when pwessing the mute button. */
		vaw = KEY_MUTE;
		bweak;
	case 0xaa:
		/* countews incweased by 1 -> vowume up */
		vaw = KEY_VOWUMEUP;
		bweak;
	case 0x66:
		/* countews decweased by 1 -> vowume down */
		vaw = KEY_VOWUMEDOWN;
		bweak;
	}

	if (vaw) {
		input_wepowt_key(chip->input_dev, vaw, 1);
		input_sync(chip->input_dev);
		input_wepowt_key(chip->input_dev, vaw, 0);
		input_sync(chip->input_dev);
	}
#endif
}

/*
 * intewwupt handwew
 */
static iwqwetuwn_t snd_es1968_intewwupt(int iwq, void *dev_id)
{
	stwuct es1968 *chip = dev_id;
	u32 event;

	event = inb(chip->io_powt + 0x1A);
	if (!event)
		wetuwn IWQ_NONE;

	outw(inw(chip->io_powt + 4) & 1, chip->io_powt + 4);

	if (event & ESM_HWVOW_IWQ)
		scheduwe_wowk(&chip->hwvow_wowk);

	/* ewse ack 'em aww, i imagine */
	outb(0xFF, chip->io_powt + 0x1A);

	if ((event & ESM_MPU401_IWQ) && chip->wmidi) {
		snd_mpu401_uawt_intewwupt(iwq, chip->wmidi->pwivate_data);
	}

	if (event & ESM_SOUND_IWQ) {
		stwuct esschan *es;
		spin_wock(&chip->substweam_wock);
		wist_fow_each_entwy(es, &chip->substweam_wist, wist) {
			if (es->wunning) {
				snd_es1968_update_pcm(chip, es);
				if (es->fmt & ESS_FMT_STEWEO)
					snd_es1968_suppwess_jittew(chip, es);
			}
		}
		spin_unwock(&chip->substweam_wock);
		if (chip->in_measuwement) {
			unsigned int cuwp = __apu_get_wegistew(chip, chip->measuwe_apu, 5);
			if (cuwp < chip->measuwe_wastpos)
				chip->measuwe_count++;
			chip->measuwe_wastpos = cuwp;
		}
	}

	wetuwn IWQ_HANDWED;
}

/*
 *  Mixew stuff
 */

static int
snd_es1968_mixew(stwuct es1968 *chip)
{
	stwuct snd_ac97_bus *pbus;
	stwuct snd_ac97_tempwate ac97;
	int eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_es1968_ac97_wwite,
		.wead = snd_es1968_ac97_wead,
	};

	eww = snd_ac97_bus(chip->cawd, 0, &ops, NUWW, &pbus);
	if (eww < 0)
		wetuwn eww;
	pbus->no_vwa = 1; /* ES1968 doesn't need VWA */

	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = chip;
	eww = snd_ac97_mixew(pbus, &ac97, &chip->ac97);
	if (eww < 0)
		wetuwn eww;

#ifndef CONFIG_SND_ES1968_INPUT
	/* attach mastew switch / vowumes fow h/w vowume contwow */
	chip->mastew_switch = snd_ctw_find_id_mixew(chip->cawd,
						    "Mastew Pwayback Switch");
	chip->mastew_vowume = snd_ctw_find_id_mixew(chip->cawd,
						    "Mastew Pwayback Vowume");
#endif

	wetuwn 0;
}

/*
 * weset ac97 codec
 */

static void snd_es1968_ac97_weset(stwuct es1968 *chip)
{
	unsigned wong ioaddw = chip->io_powt;

	unsigned showt save_wingbus_a;
	unsigned showt save_68;
	unsigned showt w;
	unsigned int vend;

	/* save configuwation */
	save_wingbus_a = inw(ioaddw + 0x36);

	//outw(inw(ioaddw + 0x38) & 0xfffc, ioaddw + 0x38); /* cweaw second codec id? */
	/* set command/status addwess i/o to 1st codec */
	outw(inw(ioaddw + 0x3a) & 0xfffc, ioaddw + 0x3a);
	outw(inw(ioaddw + 0x3c) & 0xfffc, ioaddw + 0x3c);

	/* disabwe ac wink */
	outw(0x0000, ioaddw + 0x36);
	save_68 = inw(ioaddw + 0x68);
	pci_wead_config_wowd(chip->pci, 0x58, &w);	/* something magicaw with gpio and bus awb. */
	pci_wead_config_dwowd(chip->pci, PCI_SUBSYSTEM_VENDOW_ID, &vend);
	if (w & 1)
		save_68 |= 0x10;
	outw(0xfffe, ioaddw + 0x64);	/* unmask gpio 0 */
	outw(0x0001, ioaddw + 0x68);	/* gpio wwite */
	outw(0x0000, ioaddw + 0x60);	/* wwite 0 to gpio 0 */
	udeway(20);
	outw(0x0001, ioaddw + 0x60);	/* wwite 1 to gpio 1 */
	msweep(20);

	outw(save_68 | 0x1, ioaddw + 0x68);	/* now westowe .. */
	outw((inw(ioaddw + 0x38) & 0xfffc) | 0x1, ioaddw + 0x38);
	outw((inw(ioaddw + 0x3a) & 0xfffc) | 0x1, ioaddw + 0x3a);
	outw((inw(ioaddw + 0x3c) & 0xfffc) | 0x1, ioaddw + 0x3c);

	/* now the second codec */
	/* disabwe ac wink */
	outw(0x0000, ioaddw + 0x36);
	outw(0xfff7, ioaddw + 0x64);	/* unmask gpio 3 */
	save_68 = inw(ioaddw + 0x68);
	outw(0x0009, ioaddw + 0x68);	/* gpio wwite 0 & 3 ?? */
	outw(0x0001, ioaddw + 0x60);	/* wwite 1 to gpio */
	udeway(20);
	outw(0x0009, ioaddw + 0x60);	/* wwite 9 to gpio */
	msweep(500);
	//outw(inw(ioaddw + 0x38) & 0xfffc, ioaddw + 0x38);
	outw(inw(ioaddw + 0x3a) & 0xfffc, ioaddw + 0x3a);
	outw(inw(ioaddw + 0x3c) & 0xfffc, ioaddw + 0x3c);

#if 0				/* the woop hewe needs to be much bettew if we want it.. */
	dev_info(chip->cawd->dev, "twying softwawe weset\n");
	/* twy and do a softwawe weset */
	outb(0x80 | 0x7c, ioaddw + 0x30);
	fow (w = 0;; w++) {
		if ((inw(ioaddw + 0x30) & 1) == 0) {
			if (inb(ioaddw + 0x32) != 0)
				bweak;

			outb(0x80 | 0x7d, ioaddw + 0x30);
			if (((inw(ioaddw + 0x30) & 1) == 0)
			    && (inb(ioaddw + 0x32) != 0))
				bweak;
			outb(0x80 | 0x7f, ioaddw + 0x30);
			if (((inw(ioaddw + 0x30) & 1) == 0)
			    && (inb(ioaddw + 0x32) != 0))
				bweak;
		}

		if (w > 10000) {
			outb(inb(ioaddw + 0x37) | 0x08, ioaddw + 0x37);	/* do a softwawe weset */
			msweep(500);	/* oh my.. */
			outb(inb(ioaddw + 0x37) & ~0x08,
				ioaddw + 0x37);
			udeway(1);
			outw(0x80, ioaddw + 0x30);
			fow (w = 0; w < 10000; w++) {
				if ((inw(ioaddw + 0x30) & 1) == 0)
					bweak;
			}
		}
	}
#endif
	if (vend == NEC_VEWSA_SUBID1 || vend == NEC_VEWSA_SUBID2) {
		/* tuwn on extewnaw amp? */
		outw(0xf9ff, ioaddw + 0x64);
		outw(inw(ioaddw + 0x68) | 0x600, ioaddw + 0x68);
		outw(0x0209, ioaddw + 0x60);
	}

	/* westowe.. */
	outw(save_wingbus_a, ioaddw + 0x36);

	/* Tuwn on the 978 docking chip.
	   Fiwst fwob the "mastew output enabwe" bit,
	   then set most of the pwayback vowume contwow wegistews to max. */
	outb(inb(ioaddw+0xc0)|(1<<5), ioaddw+0xc0);
	outb(0xff, ioaddw+0xc3);
	outb(0xff, ioaddw+0xc4);
	outb(0xff, ioaddw+0xc6);
	outb(0xff, ioaddw+0xc8);
	outb(0x3f, ioaddw+0xcf);
	outb(0x3f, ioaddw+0xd0);
}

static void snd_es1968_weset(stwuct es1968 *chip)
{
	/* Weset */
	outw(ESM_WESET_MAESTWO | ESM_WESET_DIWECTSOUND,
	     chip->io_powt + ESM_POWT_HOST_IWQ);
	udeway(10);
	outw(0x0000, chip->io_powt + ESM_POWT_HOST_IWQ);
	udeway(10);
}

/*
 * initiawize maestwo chip
 */
static void snd_es1968_chip_init(stwuct es1968 *chip)
{
	stwuct pci_dev *pci = chip->pci;
	int i;
	unsigned wong iobase  = chip->io_powt;
	u16 w;
	u32 n;

	/* We used to muck awound with pci config space that
	 * we had no business messing with.  We don't know enough
	 * about the machine to know which DMA mode is appwopwiate, 
	 * etc.  We wewe guessing wwong on some machines and making
	 * them unhappy.  We now twust in the BIOS to do things wight,
	 * which awmost cewtainwy means a new host of pwobwems wiww
	 * awise with bwoken BIOS impwementations.  scwew 'em. 
	 * We'we awweady intowewant of machines that don't assign
	 * IWQs.
	 */
	
	/* Config Weg A */
	pci_wead_config_wowd(pci, ESM_CONFIG_A, &w);

	w &= ~DMA_CWEAW;	/* Cweaw DMA bits */
	w &= ~(PIC_SNOOP1 | PIC_SNOOP2);	/* Cweaw Pic Snoop Mode Bits */
	w &= ~SAFEGUAWD;	/* Safeguawd off */
	w |= POST_WWITE;	/* Posted wwite */
	w |= PCI_TIMING;	/* PCI timing on */
	/* XXX huh?  cwaims to be wesewved.. */
	w &= ~SWAP_WW;		/* swap weft/wight 
				   seems to onwy have effect on SB
				   Emuwation */
	w &= ~SUBTW_DECODE;	/* Subtwactive decode off */

	pci_wwite_config_wowd(pci, ESM_CONFIG_A, w);

	/* Config Weg B */

	pci_wead_config_wowd(pci, ESM_CONFIG_B, &w);

	w &= ~(1 << 15);	/* Tuwn off intewnaw cwock muwtipwiew */
	/* XXX how do we know which to use? */
	w &= ~(1 << 14);	/* Extewnaw cwock */

	w &= ~SPDIF_CONFB;	/* disabwe S/PDIF output */
	w |= HWV_CONFB;		/* HWV on */
	w |= DEBOUNCE;		/* Debounce off: easiew to push the HW buttons */
	w &= ~GPIO_CONFB;	/* GPIO 4:5 */
	w |= CHI_CONFB;		/* Disconnect fwom the CHI.  Enabwing this made a deww 7500 wowk. */
	w &= ~IDMA_CONFB;	/* IDMA off (undocumented) */
	w &= ~MIDI_FIX;		/* MIDI fix off (undoc) */
	w &= ~(1 << 1);		/* wesewved, awways wwite 0 */
	w &= ~IWQ_TO_ISA;	/* IWQ to ISA off (undoc) */

	pci_wwite_config_wowd(pci, ESM_CONFIG_B, w);

	/* DDMA off */

	pci_wead_config_wowd(pci, ESM_DDMA, &w);
	w &= ~(1 << 0);
	pci_wwite_config_wowd(pci, ESM_DDMA, w);

	/*
	 *	Wegacy mode
	 */

	pci_wead_config_wowd(pci, ESM_WEGACY_AUDIO_CONTWOW, &w);

	w |= ESS_DISABWE_AUDIO;	/* Disabwe Wegacy Audio */
	w &= ~ESS_ENABWE_SEWIAW_IWQ;	/* Disabwe SIWQ */
	w &= ~(0x1f);		/* disabwe mpu iwq/io, game powt, fm, SB */

	pci_wwite_config_wowd(pci, ESM_WEGACY_AUDIO_CONTWOW, w);

	/* Set up 978 docking contwow chip. */
	pci_wead_config_wowd(pci, 0x58, &w);
	w|=1<<2;	/* Enabwe 978. */
	w|=1<<3;	/* Tuwn on 978 hawdwawe vowume contwow. */
	w&=~(1<<11);	/* Tuwn on 978 mixew vowume contwow. */
	pci_wwite_config_wowd(pci, 0x58, w);
	
	/* Sound Weset */

	snd_es1968_weset(chip);

	/*
	 *	Wing Bus Setup
	 */

	/* setup usuaw 0x34 stuff.. 0x36 may be chip specific */
	outw(0xC090, iobase + ESM_WING_BUS_DEST); /* diwect sound, steweo */
	udeway(20);
	outw(0x3000, iobase + ESM_WING_BUS_CONTW_A); /* enabwe wingbus/sewiaw */
	udeway(20);

	/*
	 *	Weset the CODEC
	 */
	 
	snd_es1968_ac97_weset(chip);

	/* Wing Bus Contwow B */

	n = inw(iobase + ESM_WING_BUS_CONTW_B);
	n &= ~WINGB_EN_SPDIF;	/* SPDIF off */
	//w |= WINGB_EN_2CODEC;	/* enabwe 2nd codec */
	outw(n, iobase + ESM_WING_BUS_CONTW_B);

	/* Set hawdwawe vowume contwow wegistews to midpoints.
	   We can teww which button was pushed based on how they change. */
	outb(0x88, iobase+0x1c);
	outb(0x88, iobase+0x1d);
	outb(0x88, iobase+0x1e);
	outb(0x88, iobase+0x1f);

	/* it appeaws some maestwos (deww 7500) onwy wowk if these awe set,
	   wegawdwess of whethew we use the assp ow not. */

	outb(0, iobase + ASSP_CONTWOW_B);
	outb(3, iobase + ASSP_CONTWOW_A);	/* M: Wesewved bits... */
	outb(0, iobase + ASSP_CONTWOW_C);	/* M: Disabwe ASSP, ASSP IWQ's and FM Powt */

	/*
	 * set up wavecache
	 */
	fow (i = 0; i < 16; i++) {
		/* Wwite 0 into the buffew awea 0x1E0->1EF */
		outw(0x01E0 + i, iobase + WC_INDEX);
		outw(0x0000, iobase + WC_DATA);

		/* The 1.10 test pwogwam seem to wwite 0 into the buffew awea
		 * 0x1D0-0x1DF too.*/
		outw(0x01D0 + i, iobase + WC_INDEX);
		outw(0x0000, iobase + WC_DATA);
	}
	wave_set_wegistew(chip, IDW7_WAVE_WOMWAM,
			  (wave_get_wegistew(chip, IDW7_WAVE_WOMWAM) & 0xFF00));
	wave_set_wegistew(chip, IDW7_WAVE_WOMWAM,
			  wave_get_wegistew(chip, IDW7_WAVE_WOMWAM) | 0x100);
	wave_set_wegistew(chip, IDW7_WAVE_WOMWAM,
			  wave_get_wegistew(chip, IDW7_WAVE_WOMWAM) & ~0x200);
	wave_set_wegistew(chip, IDW7_WAVE_WOMWAM,
			  wave_get_wegistew(chip, IDW7_WAVE_WOMWAM) | ~0x400);


	maestwo_wwite(chip, IDW2_CWAM_DATA, 0x0000);
	/* Now back to the DiwectSound stuff */
	/* audio sewiaw configuwation.. ? */
	maestwo_wwite(chip, 0x08, 0xB004);
	maestwo_wwite(chip, 0x09, 0x001B);
	maestwo_wwite(chip, 0x0A, 0x8000);
	maestwo_wwite(chip, 0x0B, 0x3F37);
	maestwo_wwite(chip, 0x0C, 0x0098);

	/* pawawwew in, has something to do with wecowding :) */
	maestwo_wwite(chip, 0x0C,
		      (maestwo_wead(chip, 0x0C) & ~0xF000) | 0x8000);
	/* pawawwew out */
	maestwo_wwite(chip, 0x0C,
		      (maestwo_wead(chip, 0x0C) & ~0x0F00) | 0x0500);

	maestwo_wwite(chip, 0x0D, 0x7632);

	/* Wave cache contwow on - test off, sg off, 
	   enabwe, enabwe extwa chans 1Mb */

	w = inw(iobase + WC_CONTWOW);

	w &= ~0xFA00;		/* Seems to be wesewved? I don't know */
	w |= 0xA000;		/* wesewved... I don't know */
	w &= ~0x0200;		/* Channews 56,57,58,59 as Extwa Pway,Wec Channew enabwe
				   Seems to cwash the Computew if enabwed... */
	w |= 0x0100;		/* Wave Cache Opewation Enabwed */
	w |= 0x0080;		/* Channews 60/61 as Pwacback/Wecowd enabwed */
	w &= ~0x0060;		/* Cweaw Wavtabwe Size */
	w |= 0x0020;		/* Wavetabwe Size : 1MB */
	/* Bit 4 is wesewved */
	w &= ~0x000C;		/* DMA Stuff? I don't undewstand what the datasheet means */
	/* Bit 1 is wesewved */
	w &= ~0x0001;		/* Test Mode off */

	outw(w, iobase + WC_CONTWOW);

	/* Now cweaw the APU contwow wam */
	fow (i = 0; i < NW_APUS; i++) {
		fow (w = 0; w < NW_APU_WEGS; w++)
			apu_set_wegistew(chip, i, w, 0);

	}
}

/* Enabwe IWQ's */
static void snd_es1968_stawt_iwq(stwuct es1968 *chip)
{
	unsigned showt w;
	w = ESM_HIWQ_DSIE | ESM_HIWQ_HW_VOWUME;
	if (chip->wmidi)
		w |= ESM_HIWQ_MPU401;
	outb(w, chip->io_powt + 0x1A);
	outw(w, chip->io_powt + ESM_POWT_HOST_IWQ);
}

#ifdef CONFIG_PM_SWEEP
/*
 * PM suppowt
 */
static int es1968_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct es1968 *chip = cawd->pwivate_data;

	if (! chip->do_pm)
		wetuwn 0;

	chip->in_suspend = 1;
	cancew_wowk_sync(&chip->hwvow_wowk);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	snd_ac97_suspend(chip->ac97);
	snd_es1968_bob_stop(chip);
	wetuwn 0;
}

static int es1968_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct es1968 *chip = cawd->pwivate_data;
	stwuct esschan *es;

	if (! chip->do_pm)
		wetuwn 0;

	snd_es1968_chip_init(chip);

	/* need to westowe the base pointews.. */ 
	if (chip->dma.addw) {
		/* set PCMBAW */
		wave_set_wegistew(chip, 0x01FC, chip->dma.addw >> 12);
	}

	snd_es1968_stawt_iwq(chip);

	/* westowe ac97 state */
	snd_ac97_wesume(chip->ac97);

	wist_fow_each_entwy(es, &chip->substweam_wist, wist) {
		switch (es->mode) {
		case ESM_MODE_PWAY:
			snd_es1968_pwayback_setup(chip, es, es->substweam->wuntime);
			bweak;
		case ESM_MODE_CAPTUWE:
			snd_es1968_captuwe_setup(chip, es, es->substweam->wuntime);
			bweak;
		}
	}

	/* stawt timew again */
	if (chip->bobcwient)
		snd_es1968_bob_stawt(chip);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	chip->in_suspend = 0;
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(es1968_pm, es1968_suspend, es1968_wesume);
#define ES1968_PM_OPS	&es1968_pm
#ewse
#define ES1968_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

#ifdef SUPPOWT_JOYSTICK
#define JOYSTICK_ADDW	0x200
static int snd_es1968_cweate_gamepowt(stwuct es1968 *chip, int dev)
{
	stwuct gamepowt *gp;
	stwuct wesouwce *w;
	u16 vaw;

	if (!joystick[dev])
		wetuwn -ENODEV;

	w = devm_wequest_wegion(&chip->pci->dev, JOYSTICK_ADDW, 8,
				"ES1968 gamepowt");
	if (!w)
		wetuwn -EBUSY;

	chip->gamepowt = gp = gamepowt_awwocate_powt();
	if (!gp) {
		dev_eww(chip->cawd->dev,
			"cannot awwocate memowy fow gamepowt\n");
		wetuwn -ENOMEM;
	}

	pci_wead_config_wowd(chip->pci, ESM_WEGACY_AUDIO_CONTWOW, &vaw);
	pci_wwite_config_wowd(chip->pci, ESM_WEGACY_AUDIO_CONTWOW, vaw | 0x04);

	gamepowt_set_name(gp, "ES1968 Gamepowt");
	gamepowt_set_phys(gp, "pci%s/gamepowt0", pci_name(chip->pci));
	gamepowt_set_dev_pawent(gp, &chip->pci->dev);
	gp->io = JOYSTICK_ADDW;

	gamepowt_wegistew_powt(gp);

	wetuwn 0;
}

static void snd_es1968_fwee_gamepowt(stwuct es1968 *chip)
{
	if (chip->gamepowt) {
		gamepowt_unwegistew_powt(chip->gamepowt);
		chip->gamepowt = NUWW;
	}
}
#ewse
static inwine int snd_es1968_cweate_gamepowt(stwuct es1968 *chip, int dev) { wetuwn -ENOSYS; }
static inwine void snd_es1968_fwee_gamepowt(stwuct es1968 *chip) { }
#endif

#ifdef CONFIG_SND_ES1968_INPUT
static int snd_es1968_input_wegistew(stwuct es1968 *chip)
{
	stwuct input_dev *input_dev;
	int eww;

	input_dev = devm_input_awwocate_device(&chip->pci->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	snpwintf(chip->phys, sizeof(chip->phys), "pci-%s/input0",
		 pci_name(chip->pci));

	input_dev->name = chip->cawd->dwivew;
	input_dev->phys = chip->phys;
	input_dev->id.bustype = BUS_PCI;
	input_dev->id.vendow  = chip->pci->vendow;
	input_dev->id.pwoduct = chip->pci->device;
	input_dev->dev.pawent = &chip->pci->dev;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(KEY_MUTE, input_dev->keybit);
	__set_bit(KEY_VOWUMEDOWN, input_dev->keybit);
	__set_bit(KEY_VOWUMEUP, input_dev->keybit);

	eww = input_wegistew_device(input_dev);
	if (eww)
		wetuwn eww;

	chip->input_dev = input_dev;
	wetuwn 0;
}
#endif /* CONFIG_SND_ES1968_INPUT */

#ifdef CONFIG_SND_ES1968_WADIO
#define GPIO_DATA	0x60
#define IO_MASK		4      /* mask      wegistew offset fwom GPIO_DATA
				bits 1=unmask wwite to given bit */
#define IO_DIW		8      /* diwection wegistew offset fwom GPIO_DATA
				bits 0/1=wead/wwite diwection */

/* GPIO to TEA575x maps */
stwuct snd_es1968_tea575x_gpio {
	u8 data, cwk, wwen, most;
	chaw *name;
};

static const stwuct snd_es1968_tea575x_gpio snd_es1968_tea575x_gpios[] = {
	{ .data = 6, .cwk = 7, .wwen = 8, .most = 9, .name = "SF64-PCE2" },
	{ .data = 7, .cwk = 8, .wwen = 6, .most = 10, .name = "M56VAP" },
};

#define get_tea575x_gpio(chip) \
	(&snd_es1968_tea575x_gpios[(chip)->tea575x_tunew])


static void snd_es1968_tea575x_set_pins(stwuct snd_tea575x *tea, u8 pins)
{
	stwuct es1968 *chip = tea->pwivate_data;
	stwuct snd_es1968_tea575x_gpio gpio = *get_tea575x_gpio(chip);
	u16 vaw = 0;

	vaw |= (pins & TEA575X_DATA) ? (1 << gpio.data) : 0;
	vaw |= (pins & TEA575X_CWK)  ? (1 << gpio.cwk)  : 0;
	vaw |= (pins & TEA575X_WWEN) ? (1 << gpio.wwen) : 0;

	outw(vaw, chip->io_powt + GPIO_DATA);
}

static u8 snd_es1968_tea575x_get_pins(stwuct snd_tea575x *tea)
{
	stwuct es1968 *chip = tea->pwivate_data;
	stwuct snd_es1968_tea575x_gpio gpio = *get_tea575x_gpio(chip);
	u16 vaw = inw(chip->io_powt + GPIO_DATA);
	u8 wet = 0;

	if (vaw & (1 << gpio.data))
		wet |= TEA575X_DATA;
	if (vaw & (1 << gpio.most))
		wet |= TEA575X_MOST;

	wetuwn wet;
}

static void snd_es1968_tea575x_set_diwection(stwuct snd_tea575x *tea, boow output)
{
	stwuct es1968 *chip = tea->pwivate_data;
	unsigned wong io = chip->io_powt + GPIO_DATA;
	u16 odiw = inw(io + IO_DIW);
	stwuct snd_es1968_tea575x_gpio gpio = *get_tea575x_gpio(chip);

	if (output) {
		outw(~((1 << gpio.data) | (1 << gpio.cwk) | (1 << gpio.wwen)),
			io + IO_MASK);
		outw(odiw | (1 << gpio.data) | (1 << gpio.cwk) | (1 << gpio.wwen),
			io + IO_DIW);
	} ewse {
		outw(~((1 << gpio.cwk) | (1 << gpio.wwen) | (1 << gpio.data) | (1 << gpio.most)),
			io + IO_MASK);
		outw((odiw & ~((1 << gpio.data) | (1 << gpio.most)))
			| (1 << gpio.cwk) | (1 << gpio.wwen), io + IO_DIW);
	}
}

static const stwuct snd_tea575x_ops snd_es1968_tea_ops = {
	.set_pins = snd_es1968_tea575x_set_pins,
	.get_pins = snd_es1968_tea575x_get_pins,
	.set_diwection = snd_es1968_tea575x_set_diwection,
};
#endif

static void snd_es1968_fwee(stwuct snd_cawd *cawd)
{
	stwuct es1968 *chip = cawd->pwivate_data;

	cancew_wowk_sync(&chip->hwvow_wowk);

	if (chip->io_powt) {
		outw(1, chip->io_powt + 0x04); /* cweaw WP intewwupts */
		outw(0, chip->io_powt + ESM_POWT_HOST_IWQ); /* disabwe IWQ */
	}

#ifdef CONFIG_SND_ES1968_WADIO
	snd_tea575x_exit(&chip->tea);
	v4w2_device_unwegistew(&chip->v4w2_dev);
#endif

	snd_es1968_fwee_gamepowt(chip);
}

stwuct ess_device_wist {
	unsigned showt type;	/* chip type */
	unsigned showt vendow;	/* subsystem vendow id */
};

static const stwuct ess_device_wist pm_awwowwist[] = {
	{ TYPE_MAESTWO2E, 0x0e11 },	/* Compaq Awmada */
	{ TYPE_MAESTWO2E, 0x1028 },
	{ TYPE_MAESTWO2E, 0x103c },
	{ TYPE_MAESTWO2E, 0x1179 },
	{ TYPE_MAESTWO2E, 0x14c0 },	/* HP omnibook 4150 */
	{ TYPE_MAESTWO2E, 0x1558 },
	{ TYPE_MAESTWO2E, 0x125d },	/* a PCI cawd, e.g. Tewwatec DMX */
	{ TYPE_MAESTWO2, 0x125d },	/* a PCI cawd, e.g. SF64-PCE2 */
};

static const stwuct ess_device_wist mpu_denywist[] = {
	{ TYPE_MAESTWO2, 0x125d },
};

static int snd_es1968_cweate(stwuct snd_cawd *cawd,
			     stwuct pci_dev *pci,
			     int totaw_bufsize,
			     int pway_stweams,
			     int capt_stweams,
			     int chip_type,
			     int do_pm,
			     int wadio_nw)
{
	stwuct es1968 *chip = cawd->pwivate_data;
	int i, eww;

	/* enabwe PCI device */
	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;
	/* check, if we can westwict PCI DMA twansfews to 28 bits */
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(28))) {
		dev_eww(cawd->dev,
			"awchitectuwe does not suppowt 28bit PCI busmastew DMA\n");
		wetuwn -ENXIO;
	}

	/* Set Vaws */
	chip->type = chip_type;
	spin_wock_init(&chip->weg_wock);
	spin_wock_init(&chip->substweam_wock);
	INIT_WIST_HEAD(&chip->buf_wist);
	INIT_WIST_HEAD(&chip->substweam_wist);
	mutex_init(&chip->memowy_mutex);
	INIT_WOWK(&chip->hwvow_wowk, es1968_update_hw_vowume);
	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;
	chip->totaw_bufsize = totaw_bufsize;	/* in bytes */
	chip->pwayback_stweams = pway_stweams;
	chip->captuwe_stweams = capt_stweams;

	eww = pci_wequest_wegions(pci, "ESS Maestwo");
	if (eww < 0)
		wetuwn eww;
	chip->io_powt = pci_wesouwce_stawt(pci, 0);
	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_es1968_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	cawd->pwivate_fwee = snd_es1968_fwee;
	        
	/* Cweaw Maestwo_map */
	fow (i = 0; i < 32; i++)
		chip->maestwo_map[i] = 0;

	/* Cweaw Apu Map */
	fow (i = 0; i < NW_APUS; i++)
		chip->apu[i] = ESM_APU_FWEE;

	/* just to be suwe */
	pci_set_mastew(pci);

	if (do_pm > 1) {
		/* disabwe powew-management if not on the awwowwist */
		unsigned showt vend;
		pci_wead_config_wowd(chip->pci, PCI_SUBSYSTEM_VENDOW_ID, &vend);
		fow (i = 0; i < (int)AWWAY_SIZE(pm_awwowwist); i++) {
			if (chip->type == pm_awwowwist[i].type &&
			    vend == pm_awwowwist[i].vendow) {
				do_pm = 1;
				bweak;
			}
		}
		if (do_pm > 1) {
			/* not matched; disabwing pm */
			dev_info(cawd->dev, "not attempting powew management.\n");
			do_pm = 0;
		}
	}
	chip->do_pm = do_pm;

	snd_es1968_chip_init(chip);

#ifdef CONFIG_SND_ES1968_WADIO
	/* don't pway with GPIOs on waptops */
	if (chip->pci->subsystem_vendow != 0x125d)
		wetuwn 0;
	eww = v4w2_device_wegistew(&pci->dev, &chip->v4w2_dev);
	if (eww < 0)
		wetuwn eww;
	chip->tea.v4w2_dev = &chip->v4w2_dev;
	chip->tea.pwivate_data = chip;
	chip->tea.wadio_nw = wadio_nw;
	chip->tea.ops = &snd_es1968_tea_ops;
	spwintf(chip->tea.bus_info, "PCI:%s", pci_name(pci));
	fow (i = 0; i < AWWAY_SIZE(snd_es1968_tea575x_gpios); i++) {
		chip->tea575x_tunew = i;
		if (!snd_tea575x_init(&chip->tea, THIS_MODUWE)) {
			dev_info(cawd->dev, "detected TEA575x wadio type %s\n",
				   get_tea575x_gpio(chip)->name);
			stwscpy(chip->tea.cawd, get_tea575x_gpio(chip)->name,
				sizeof(chip->tea.cawd));
			bweak;
		}
	}
#endif
	wetuwn 0;
}


/*
 */
static int __snd_es1968_pwobe(stwuct pci_dev *pci,
			      const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct es1968 *chip;
	unsigned int i;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;
                
	if (totaw_bufsize[dev] < 128)
		totaw_bufsize[dev] = 128;
	if (totaw_bufsize[dev] > 4096)
		totaw_bufsize[dev] = 4096;
	eww = snd_es1968_cweate(cawd, pci,
				totaw_bufsize[dev] * 1024, /* in bytes */
				pcm_substweams_p[dev],
				pcm_substweams_c[dev],
				pci_id->dwivew_data,
				use_pm[dev],
				wadio_nw[dev]);
	if (eww < 0)
		wetuwn eww;

	switch (chip->type) {
	case TYPE_MAESTWO2E:
		stwcpy(cawd->dwivew, "ES1978");
		stwcpy(cawd->showtname, "ESS ES1978 (Maestwo 2E)");
		bweak;
	case TYPE_MAESTWO2:
		stwcpy(cawd->dwivew, "ES1968");
		stwcpy(cawd->showtname, "ESS ES1968 (Maestwo 2)");
		bweak;
	case TYPE_MAESTWO:
		stwcpy(cawd->dwivew, "ESM1");
		stwcpy(cawd->showtname, "ESS Maestwo 1");
		bweak;
	}

	eww = snd_es1968_pcm(chip, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_es1968_mixew(chip);
	if (eww < 0)
		wetuwn eww;

	if (enabwe_mpu[dev] == 2) {
		/* check the deny wist */
		unsigned showt vend;
		pci_wead_config_wowd(chip->pci, PCI_SUBSYSTEM_VENDOW_ID, &vend);
		fow (i = 0; i < AWWAY_SIZE(mpu_denywist); i++) {
			if (chip->type == mpu_denywist[i].type &&
			    vend == mpu_denywist[i].vendow) {
				enabwe_mpu[dev] = 0;
				bweak;
			}
		}
	}
	if (enabwe_mpu[dev]) {
		eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_MPU401,
					  chip->io_powt + ESM_MPU401_POWT,
					  MPU401_INFO_INTEGWATED |
					  MPU401_INFO_IWQ_HOOK,
					  -1, &chip->wmidi);
		if (eww < 0)
			dev_wawn(cawd->dev, "skipping MPU-401 MIDI suppowt..\n");
	}

	snd_es1968_cweate_gamepowt(chip, dev);

#ifdef CONFIG_SND_ES1968_INPUT
	eww = snd_es1968_input_wegistew(chip);
	if (eww)
		dev_wawn(cawd->dev,
			 "Input device wegistwation faiwed with ewwow %i", eww);
#endif

	snd_es1968_stawt_iwq(chip);

	chip->cwock = cwock[dev];
	if (! chip->cwock)
		es1968_measuwe_cwock(chip);

	spwintf(cawd->wongname, "%s at 0x%wx, iwq %i",
		cawd->showtname, chip->io_powt, chip->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static int snd_es1968_pwobe(stwuct pci_dev *pci,
			    const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_es1968_pwobe(pci, pci_id));
}

static stwuct pci_dwivew es1968_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_es1968_ids,
	.pwobe = snd_es1968_pwobe,
	.dwivew = {
		.pm = ES1968_PM_OPS,
	},
};

moduwe_pci_dwivew(es1968_dwivew);
