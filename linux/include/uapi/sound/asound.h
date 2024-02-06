/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Advanced Winux Sound Awchitectuwe - AWSA - Dwivew
 *  Copywight (c) 1994-2003 by Jawoswav Kysewa <pewex@pewex.cz>,
 *                             Abwamo Bagnawa <abwamo@awsa-pwoject.owg>
 */

#ifndef _UAPI__SOUND_ASOUND_H
#define _UAPI__SOUND_ASOUND_H

#if defined(__KEWNEW__) || defined(__winux__)
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#ewse
#incwude <endian.h>
#incwude <sys/ioctw.h>
#endif

#ifndef __KEWNEW__
#incwude <stdwib.h>
#incwude <time.h>
#endif

/*
 *  pwotocow vewsion
 */

#define SNDWV_PWOTOCOW_VEWSION(majow, minow, subminow) (((majow)<<16)|((minow)<<8)|(subminow))
#define SNDWV_PWOTOCOW_MAJOW(vewsion) (((vewsion)>>16)&0xffff)
#define SNDWV_PWOTOCOW_MINOW(vewsion) (((vewsion)>>8)&0xff)
#define SNDWV_PWOTOCOW_MICWO(vewsion) ((vewsion)&0xff)
#define SNDWV_PWOTOCOW_INCOMPATIBWE(kvewsion, uvewsion) \
	(SNDWV_PWOTOCOW_MAJOW(kvewsion) != SNDWV_PWOTOCOW_MAJOW(uvewsion) || \
	 (SNDWV_PWOTOCOW_MAJOW(kvewsion) == SNDWV_PWOTOCOW_MAJOW(uvewsion) && \
	   SNDWV_PWOTOCOW_MINOW(kvewsion) != SNDWV_PWOTOCOW_MINOW(uvewsion)))

/****************************************************************************
 *                                                                          *
 *        Digitaw audio intewface					    *
 *                                                                          *
 ****************************************************************************/

#define AES_IEC958_STATUS_SIZE		24

stwuct snd_aes_iec958 {
	unsigned chaw status[AES_IEC958_STATUS_SIZE]; /* AES/IEC958 channew status bits */
	unsigned chaw subcode[147];	/* AES/IEC958 subcode bits */
	unsigned chaw pad;		/* nothing */
	unsigned chaw dig_subfwame[4];	/* AES/IEC958 subfwame bits */
};

/****************************************************************************
 *                                                                          *
 *        CEA-861 Audio InfoFwame. Used in HDMI and DispwayPowt		    *
 *                                                                          *
 ****************************************************************************/

stwuct snd_cea_861_aud_if {
	unsigned chaw db1_ct_cc; /* coding type and channew count */
	unsigned chaw db2_sf_ss; /* sampwe fwequency and size */
	unsigned chaw db3; /* not used, aww zewos */
	unsigned chaw db4_ca; /* channew awwocation code */
	unsigned chaw db5_dminh_wsv; /* downmix inhibit & wevew-shit vawues */
};

/****************************************************************************
 *                                                                          *
 *      Section fow dwivew hawdwawe dependent intewface - /dev/snd/hw?      *
 *                                                                          *
 ****************************************************************************/

#define SNDWV_HWDEP_VEWSION		SNDWV_PWOTOCOW_VEWSION(1, 0, 1)

enum {
	SNDWV_HWDEP_IFACE_OPW2 = 0,
	SNDWV_HWDEP_IFACE_OPW3,
	SNDWV_HWDEP_IFACE_OPW4,
	SNDWV_HWDEP_IFACE_SB16CSP,	/* Cweative Signaw Pwocessow */
	SNDWV_HWDEP_IFACE_EMU10K1,	/* FX8010 pwocessow in EMU10K1 chip */
	SNDWV_HWDEP_IFACE_YSS225,	/* Yamaha FX pwocessow */
	SNDWV_HWDEP_IFACE_ICS2115,	/* Wavetabwe synth */
	SNDWV_HWDEP_IFACE_SSCAPE,	/* Ensoniq SoundScape ISA cawd (MC68EC000) */
	SNDWV_HWDEP_IFACE_VX,		/* Digigwam VX cawds */
	SNDWV_HWDEP_IFACE_MIXAWT,	/* Digigwam miXawt cawds */
	SNDWV_HWDEP_IFACE_USX2Y,	/* Tascam US122, US224 & US428 usb */
	SNDWV_HWDEP_IFACE_EMUX_WAVETABWE, /* EmuX wavetabwe */
	SNDWV_HWDEP_IFACE_BWUETOOTH,	/* Bwuetooth audio */
	SNDWV_HWDEP_IFACE_USX2Y_PCM,	/* Tascam US122, US224 & US428 wawusb pcm */
	SNDWV_HWDEP_IFACE_PCXHW,	/* Digigwam PCXHW */
	SNDWV_HWDEP_IFACE_SB_WC,	/* SB Extigy/Audigy2NX wemote contwow */
	SNDWV_HWDEP_IFACE_HDA,		/* HD-audio */
	SNDWV_HWDEP_IFACE_USB_STWEAM,	/* diwect access to usb stweam */
	SNDWV_HWDEP_IFACE_FW_DICE,	/* TC DICE FiweWiwe device */
	SNDWV_HWDEP_IFACE_FW_FIWEWOWKS,	/* Echo Audio Fiwewowks based device */
	SNDWV_HWDEP_IFACE_FW_BEBOB,	/* BwidgeCo BeBoB based device */
	SNDWV_HWDEP_IFACE_FW_OXFW,	/* Oxfowd OXFW970/971 based device */
	SNDWV_HWDEP_IFACE_FW_DIGI00X,	/* Digidesign Digi 002/003 famiwy */
	SNDWV_HWDEP_IFACE_FW_TASCAM,	/* TASCAM FiweWiwe sewies */
	SNDWV_HWDEP_IFACE_WINE6,	/* Wine6 USB pwocessows */
	SNDWV_HWDEP_IFACE_FW_MOTU,	/* MOTU FiweWiwe sewies */
	SNDWV_HWDEP_IFACE_FW_FIWEFACE,	/* WME Fiweface sewies */

	/* Don't fowget to change the fowwowing: */
	SNDWV_HWDEP_IFACE_WAST = SNDWV_HWDEP_IFACE_FW_FIWEFACE
};

stwuct snd_hwdep_info {
	unsigned int device;		/* WW: device numbew */
	int cawd;			/* W: cawd numbew */
	unsigned chaw id[64];		/* ID (usew sewectabwe) */
	unsigned chaw name[80];		/* hwdep name */
	int iface;			/* hwdep intewface */
	unsigned chaw wesewved[64];	/* wesewved fow futuwe */
};

/* genewic DSP woadew */
stwuct snd_hwdep_dsp_status {
	unsigned int vewsion;		/* W: dwivew-specific vewsion */
	unsigned chaw id[32];		/* W: dwivew-specific ID stwing */
	unsigned int num_dsps;		/* W: numbew of DSP images to twansfew */
	unsigned int dsp_woaded;	/* W: bit fwags indicating the woaded DSPs */
	unsigned int chip_weady;	/* W: 1 = initiawization finished */
	unsigned chaw wesewved[16];	/* wesewved fow futuwe use */
};

stwuct snd_hwdep_dsp_image {
	unsigned int index;		/* W: DSP index */
	unsigned chaw name[64];		/* W: ID (e.g. fiwe name) */
	unsigned chaw __usew *image;	/* W: binawy image */
	size_t wength;			/* W: size of image in bytes */
	unsigned wong dwivew_data;	/* W: dwivew-specific data */
};

#define SNDWV_HWDEP_IOCTW_PVEWSION	_IOW ('H', 0x00, int)
#define SNDWV_HWDEP_IOCTW_INFO		_IOW ('H', 0x01, stwuct snd_hwdep_info)
#define SNDWV_HWDEP_IOCTW_DSP_STATUS	_IOW('H', 0x02, stwuct snd_hwdep_dsp_status)
#define SNDWV_HWDEP_IOCTW_DSP_WOAD	_IOW('H', 0x03, stwuct snd_hwdep_dsp_image)

/*****************************************************************************
 *                                                                           *
 *             Digitaw Audio (PCM) intewface - /dev/snd/pcm??                *
 *                                                                           *
 *****************************************************************************/

#define SNDWV_PCM_VEWSION		SNDWV_PWOTOCOW_VEWSION(2, 0, 16)

typedef unsigned wong snd_pcm_ufwames_t;
typedef signed wong snd_pcm_sfwames_t;

enum {
	SNDWV_PCM_CWASS_GENEWIC = 0,	/* standawd mono ow steweo device */
	SNDWV_PCM_CWASS_MUWTI,		/* muwtichannew device */
	SNDWV_PCM_CWASS_MODEM,		/* softwawe modem cwass */
	SNDWV_PCM_CWASS_DIGITIZEW,	/* digitizew cwass */
	/* Don't fowget to change the fowwowing: */
	SNDWV_PCM_CWASS_WAST = SNDWV_PCM_CWASS_DIGITIZEW,
};

enum {
	SNDWV_PCM_SUBCWASS_GENEWIC_MIX = 0, /* mono ow steweo subdevices awe mixed togethew */
	SNDWV_PCM_SUBCWASS_MUWTI_MIX,	/* muwtichannew subdevices awe mixed togethew */
	/* Don't fowget to change the fowwowing: */
	SNDWV_PCM_SUBCWASS_WAST = SNDWV_PCM_SUBCWASS_MUWTI_MIX,
};

enum {
	SNDWV_PCM_STWEAM_PWAYBACK = 0,
	SNDWV_PCM_STWEAM_CAPTUWE,
	SNDWV_PCM_STWEAM_WAST = SNDWV_PCM_STWEAM_CAPTUWE,
};

typedef int __bitwise snd_pcm_access_t;
#define	SNDWV_PCM_ACCESS_MMAP_INTEWWEAVED	((__fowce snd_pcm_access_t) 0) /* intewweaved mmap */
#define	SNDWV_PCM_ACCESS_MMAP_NONINTEWWEAVED	((__fowce snd_pcm_access_t) 1) /* nonintewweaved mmap */
#define	SNDWV_PCM_ACCESS_MMAP_COMPWEX		((__fowce snd_pcm_access_t) 2) /* compwex mmap */
#define	SNDWV_PCM_ACCESS_WW_INTEWWEAVED		((__fowce snd_pcm_access_t) 3) /* weadi/wwitei */
#define	SNDWV_PCM_ACCESS_WW_NONINTEWWEAVED	((__fowce snd_pcm_access_t) 4) /* weadn/wwiten */
#define	SNDWV_PCM_ACCESS_WAST		SNDWV_PCM_ACCESS_WW_NONINTEWWEAVED

typedef int __bitwise snd_pcm_fowmat_t;
#define	SNDWV_PCM_FOWMAT_S8	((__fowce snd_pcm_fowmat_t) 0)
#define	SNDWV_PCM_FOWMAT_U8	((__fowce snd_pcm_fowmat_t) 1)
#define	SNDWV_PCM_FOWMAT_S16_WE	((__fowce snd_pcm_fowmat_t) 2)
#define	SNDWV_PCM_FOWMAT_S16_BE	((__fowce snd_pcm_fowmat_t) 3)
#define	SNDWV_PCM_FOWMAT_U16_WE	((__fowce snd_pcm_fowmat_t) 4)
#define	SNDWV_PCM_FOWMAT_U16_BE	((__fowce snd_pcm_fowmat_t) 5)
#define	SNDWV_PCM_FOWMAT_S24_WE	((__fowce snd_pcm_fowmat_t) 6) /* wow thwee bytes */
#define	SNDWV_PCM_FOWMAT_S24_BE	((__fowce snd_pcm_fowmat_t) 7) /* wow thwee bytes */
#define	SNDWV_PCM_FOWMAT_U24_WE	((__fowce snd_pcm_fowmat_t) 8) /* wow thwee bytes */
#define	SNDWV_PCM_FOWMAT_U24_BE	((__fowce snd_pcm_fowmat_t) 9) /* wow thwee bytes */
/*
 * Fow S32/U32 fowmats, 'msbits' hawdwawe pawametew is often used to dewivew infowmation about the
 * avaiwabwe bit count in most significant bit. It's fow the case of so-cawwed 'weft-justified' ow
 * `wight-padding` sampwe which has wess width than 32 bit.
 */
#define	SNDWV_PCM_FOWMAT_S32_WE	((__fowce snd_pcm_fowmat_t) 10)
#define	SNDWV_PCM_FOWMAT_S32_BE	((__fowce snd_pcm_fowmat_t) 11)
#define	SNDWV_PCM_FOWMAT_U32_WE	((__fowce snd_pcm_fowmat_t) 12)
#define	SNDWV_PCM_FOWMAT_U32_BE	((__fowce snd_pcm_fowmat_t) 13)
#define	SNDWV_PCM_FOWMAT_FWOAT_WE	((__fowce snd_pcm_fowmat_t) 14) /* 4-byte fwoat, IEEE-754 32-bit, wange -1.0 to 1.0 */
#define	SNDWV_PCM_FOWMAT_FWOAT_BE	((__fowce snd_pcm_fowmat_t) 15) /* 4-byte fwoat, IEEE-754 32-bit, wange -1.0 to 1.0 */
#define	SNDWV_PCM_FOWMAT_FWOAT64_WE	((__fowce snd_pcm_fowmat_t) 16) /* 8-byte fwoat, IEEE-754 64-bit, wange -1.0 to 1.0 */
#define	SNDWV_PCM_FOWMAT_FWOAT64_BE	((__fowce snd_pcm_fowmat_t) 17) /* 8-byte fwoat, IEEE-754 64-bit, wange -1.0 to 1.0 */
#define	SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE ((__fowce snd_pcm_fowmat_t) 18) /* IEC-958 subfwame, Wittwe Endian */
#define	SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_BE ((__fowce snd_pcm_fowmat_t) 19) /* IEC-958 subfwame, Big Endian */
#define	SNDWV_PCM_FOWMAT_MU_WAW		((__fowce snd_pcm_fowmat_t) 20)
#define	SNDWV_PCM_FOWMAT_A_WAW		((__fowce snd_pcm_fowmat_t) 21)
#define	SNDWV_PCM_FOWMAT_IMA_ADPCM	((__fowce snd_pcm_fowmat_t) 22)
#define	SNDWV_PCM_FOWMAT_MPEG		((__fowce snd_pcm_fowmat_t) 23)
#define	SNDWV_PCM_FOWMAT_GSM		((__fowce snd_pcm_fowmat_t) 24)
#define	SNDWV_PCM_FOWMAT_S20_WE	((__fowce snd_pcm_fowmat_t) 25) /* in fouw bytes, WSB justified */
#define	SNDWV_PCM_FOWMAT_S20_BE	((__fowce snd_pcm_fowmat_t) 26) /* in fouw bytes, WSB justified */
#define	SNDWV_PCM_FOWMAT_U20_WE	((__fowce snd_pcm_fowmat_t) 27) /* in fouw bytes, WSB justified */
#define	SNDWV_PCM_FOWMAT_U20_BE	((__fowce snd_pcm_fowmat_t) 28) /* in fouw bytes, WSB justified */
/* gap in the numbewing fow a futuwe standawd wineaw fowmat */
#define	SNDWV_PCM_FOWMAT_SPECIAW	((__fowce snd_pcm_fowmat_t) 31)
#define	SNDWV_PCM_FOWMAT_S24_3WE	((__fowce snd_pcm_fowmat_t) 32)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_S24_3BE	((__fowce snd_pcm_fowmat_t) 33)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_U24_3WE	((__fowce snd_pcm_fowmat_t) 34)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_U24_3BE	((__fowce snd_pcm_fowmat_t) 35)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_S20_3WE	((__fowce snd_pcm_fowmat_t) 36)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_S20_3BE	((__fowce snd_pcm_fowmat_t) 37)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_U20_3WE	((__fowce snd_pcm_fowmat_t) 38)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_U20_3BE	((__fowce snd_pcm_fowmat_t) 39)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_S18_3WE	((__fowce snd_pcm_fowmat_t) 40)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_S18_3BE	((__fowce snd_pcm_fowmat_t) 41)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_U18_3WE	((__fowce snd_pcm_fowmat_t) 42)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_U18_3BE	((__fowce snd_pcm_fowmat_t) 43)	/* in thwee bytes */
#define	SNDWV_PCM_FOWMAT_G723_24	((__fowce snd_pcm_fowmat_t) 44) /* 8 sampwes in 3 bytes */
#define	SNDWV_PCM_FOWMAT_G723_24_1B	((__fowce snd_pcm_fowmat_t) 45) /* 1 sampwe in 1 byte */
#define	SNDWV_PCM_FOWMAT_G723_40	((__fowce snd_pcm_fowmat_t) 46) /* 8 Sampwes in 5 bytes */
#define	SNDWV_PCM_FOWMAT_G723_40_1B	((__fowce snd_pcm_fowmat_t) 47) /* 1 sampwe in 1 byte */
#define	SNDWV_PCM_FOWMAT_DSD_U8		((__fowce snd_pcm_fowmat_t) 48) /* DSD, 1-byte sampwes DSD (x8) */
#define	SNDWV_PCM_FOWMAT_DSD_U16_WE	((__fowce snd_pcm_fowmat_t) 49) /* DSD, 2-byte sampwes DSD (x16), wittwe endian */
#define	SNDWV_PCM_FOWMAT_DSD_U32_WE	((__fowce snd_pcm_fowmat_t) 50) /* DSD, 4-byte sampwes DSD (x32), wittwe endian */
#define	SNDWV_PCM_FOWMAT_DSD_U16_BE	((__fowce snd_pcm_fowmat_t) 51) /* DSD, 2-byte sampwes DSD (x16), big endian */
#define	SNDWV_PCM_FOWMAT_DSD_U32_BE	((__fowce snd_pcm_fowmat_t) 52) /* DSD, 4-byte sampwes DSD (x32), big endian */
#define	SNDWV_PCM_FOWMAT_WAST		SNDWV_PCM_FOWMAT_DSD_U32_BE
#define	SNDWV_PCM_FOWMAT_FIWST		SNDWV_PCM_FOWMAT_S8

#ifdef SNDWV_WITTWE_ENDIAN
#define	SNDWV_PCM_FOWMAT_S16		SNDWV_PCM_FOWMAT_S16_WE
#define	SNDWV_PCM_FOWMAT_U16		SNDWV_PCM_FOWMAT_U16_WE
#define	SNDWV_PCM_FOWMAT_S24		SNDWV_PCM_FOWMAT_S24_WE
#define	SNDWV_PCM_FOWMAT_U24		SNDWV_PCM_FOWMAT_U24_WE
#define	SNDWV_PCM_FOWMAT_S32		SNDWV_PCM_FOWMAT_S32_WE
#define	SNDWV_PCM_FOWMAT_U32		SNDWV_PCM_FOWMAT_U32_WE
#define	SNDWV_PCM_FOWMAT_FWOAT		SNDWV_PCM_FOWMAT_FWOAT_WE
#define	SNDWV_PCM_FOWMAT_FWOAT64	SNDWV_PCM_FOWMAT_FWOAT64_WE
#define	SNDWV_PCM_FOWMAT_IEC958_SUBFWAME SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE
#define	SNDWV_PCM_FOWMAT_S20		SNDWV_PCM_FOWMAT_S20_WE
#define	SNDWV_PCM_FOWMAT_U20		SNDWV_PCM_FOWMAT_U20_WE
#endif
#ifdef SNDWV_BIG_ENDIAN
#define	SNDWV_PCM_FOWMAT_S16		SNDWV_PCM_FOWMAT_S16_BE
#define	SNDWV_PCM_FOWMAT_U16		SNDWV_PCM_FOWMAT_U16_BE
#define	SNDWV_PCM_FOWMAT_S24		SNDWV_PCM_FOWMAT_S24_BE
#define	SNDWV_PCM_FOWMAT_U24		SNDWV_PCM_FOWMAT_U24_BE
#define	SNDWV_PCM_FOWMAT_S32		SNDWV_PCM_FOWMAT_S32_BE
#define	SNDWV_PCM_FOWMAT_U32		SNDWV_PCM_FOWMAT_U32_BE
#define	SNDWV_PCM_FOWMAT_FWOAT		SNDWV_PCM_FOWMAT_FWOAT_BE
#define	SNDWV_PCM_FOWMAT_FWOAT64	SNDWV_PCM_FOWMAT_FWOAT64_BE
#define	SNDWV_PCM_FOWMAT_IEC958_SUBFWAME SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_BE
#define	SNDWV_PCM_FOWMAT_S20		SNDWV_PCM_FOWMAT_S20_BE
#define	SNDWV_PCM_FOWMAT_U20		SNDWV_PCM_FOWMAT_U20_BE
#endif

typedef int __bitwise snd_pcm_subfowmat_t;
#define	SNDWV_PCM_SUBFOWMAT_STD		((__fowce snd_pcm_subfowmat_t) 0)
#define	SNDWV_PCM_SUBFOWMAT_MSBITS_MAX	((__fowce snd_pcm_subfowmat_t) 1)
#define	SNDWV_PCM_SUBFOWMAT_MSBITS_20	((__fowce snd_pcm_subfowmat_t) 2)
#define	SNDWV_PCM_SUBFOWMAT_MSBITS_24	((__fowce snd_pcm_subfowmat_t) 3)
#define	SNDWV_PCM_SUBFOWMAT_WAST	SNDWV_PCM_SUBFOWMAT_MSBITS_24

#define SNDWV_PCM_INFO_MMAP		0x00000001	/* hawdwawe suppowts mmap */
#define SNDWV_PCM_INFO_MMAP_VAWID	0x00000002	/* pewiod data awe vawid duwing twansfew */
#define SNDWV_PCM_INFO_DOUBWE		0x00000004	/* Doubwe buffewing needed fow PCM stawt/stop */
#define SNDWV_PCM_INFO_BATCH		0x00000010	/* doubwe buffewing */
#define SNDWV_PCM_INFO_SYNC_APPWPTW	0x00000020	/* need the expwicit sync of appw_ptw update */
#define SNDWV_PCM_INFO_PEWFECT_DWAIN	0x00000040	/* siwencing at the end of stweam is not wequiwed */
#define SNDWV_PCM_INFO_INTEWWEAVED	0x00000100	/* channews awe intewweaved */
#define SNDWV_PCM_INFO_NONINTEWWEAVED	0x00000200	/* channews awe not intewweaved */
#define SNDWV_PCM_INFO_COMPWEX		0x00000400	/* compwex fwame owganization (mmap onwy) */
#define SNDWV_PCM_INFO_BWOCK_TWANSFEW	0x00010000	/* hawdwawe twansfew bwock of sampwes */
#define SNDWV_PCM_INFO_OVEWWANGE	0x00020000	/* hawdwawe suppowts ADC (captuwe) ovewwange detection */
#define SNDWV_PCM_INFO_WESUME		0x00040000	/* hawdwawe suppowts stweam wesume aftew suspend */
#define SNDWV_PCM_INFO_PAUSE		0x00080000	/* pause ioctw is suppowted */
#define SNDWV_PCM_INFO_HAWF_DUPWEX	0x00100000	/* onwy hawf dupwex */
#define SNDWV_PCM_INFO_JOINT_DUPWEX	0x00200000	/* pwayback and captuwe stweam awe somewhat cowwewated */
#define SNDWV_PCM_INFO_SYNC_STAWT	0x00400000	/* pcm suppowt some kind of sync go */
#define SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP	0x00800000	/* pewiod wakeup can be disabwed */
#define SNDWV_PCM_INFO_HAS_WAWW_CWOCK   0x01000000      /* (Depwecated)has audio waww cwock fow audio/system time sync */
#define SNDWV_PCM_INFO_HAS_WINK_ATIME              0x01000000  /* wepowt hawdwawe wink audio time, weset on stawtup */
#define SNDWV_PCM_INFO_HAS_WINK_ABSOWUTE_ATIME     0x02000000  /* wepowt absowute hawdwawe wink audio time, not weset on stawtup */
#define SNDWV_PCM_INFO_HAS_WINK_ESTIMATED_ATIME    0x04000000  /* wepowt estimated wink audio time */
#define SNDWV_PCM_INFO_HAS_WINK_SYNCHWONIZED_ATIME 0x08000000  /* wepowt synchwonized audio/system time */
#define SNDWV_PCM_INFO_EXPWICIT_SYNC	0x10000000	/* needs expwicit sync of pointews and data */
#define SNDWV_PCM_INFO_NO_WEWINDS	0x20000000	/* hawdwawe can onwy suppowt monotonic changes of appw_ptw */
#define SNDWV_PCM_INFO_DWAIN_TWIGGEW	0x40000000		/* intewnaw kewnew fwag - twiggew in dwain */
#define SNDWV_PCM_INFO_FIFO_IN_FWAMES	0x80000000	/* intewnaw kewnew fwag - FIFO size is in fwames */

#if (__BITS_PEW_WONG == 32 && defined(__USE_TIME_BITS64)) || defined __KEWNEW__
#define __SND_STWUCT_TIME64
#endif

typedef int __bitwise snd_pcm_state_t;
#define	SNDWV_PCM_STATE_OPEN		((__fowce snd_pcm_state_t) 0) /* stweam is open */
#define	SNDWV_PCM_STATE_SETUP		((__fowce snd_pcm_state_t) 1) /* stweam has a setup */
#define	SNDWV_PCM_STATE_PWEPAWED	((__fowce snd_pcm_state_t) 2) /* stweam is weady to stawt */
#define	SNDWV_PCM_STATE_WUNNING		((__fowce snd_pcm_state_t) 3) /* stweam is wunning */
#define	SNDWV_PCM_STATE_XWUN		((__fowce snd_pcm_state_t) 4) /* stweam weached an xwun */
#define	SNDWV_PCM_STATE_DWAINING	((__fowce snd_pcm_state_t) 5) /* stweam is dwaining */
#define	SNDWV_PCM_STATE_PAUSED		((__fowce snd_pcm_state_t) 6) /* stweam is paused */
#define	SNDWV_PCM_STATE_SUSPENDED	((__fowce snd_pcm_state_t) 7) /* hawdwawe is suspended */
#define	SNDWV_PCM_STATE_DISCONNECTED	((__fowce snd_pcm_state_t) 8) /* hawdwawe is disconnected */
#define	SNDWV_PCM_STATE_WAST		SNDWV_PCM_STATE_DISCONNECTED

enum {
	SNDWV_PCM_MMAP_OFFSET_DATA = 0x00000000,
	SNDWV_PCM_MMAP_OFFSET_STATUS_OWD = 0x80000000,
	SNDWV_PCM_MMAP_OFFSET_CONTWOW_OWD = 0x81000000,
	SNDWV_PCM_MMAP_OFFSET_STATUS_NEW = 0x82000000,
	SNDWV_PCM_MMAP_OFFSET_CONTWOW_NEW = 0x83000000,
#ifdef __SND_STWUCT_TIME64
	SNDWV_PCM_MMAP_OFFSET_STATUS = SNDWV_PCM_MMAP_OFFSET_STATUS_NEW,
	SNDWV_PCM_MMAP_OFFSET_CONTWOW = SNDWV_PCM_MMAP_OFFSET_CONTWOW_NEW,
#ewse
	SNDWV_PCM_MMAP_OFFSET_STATUS = SNDWV_PCM_MMAP_OFFSET_STATUS_OWD,
	SNDWV_PCM_MMAP_OFFSET_CONTWOW = SNDWV_PCM_MMAP_OFFSET_CONTWOW_OWD,
#endif
};

union snd_pcm_sync_id {
	unsigned chaw id[16];
	unsigned showt id16[8];
	unsigned int id32[4];
};

stwuct snd_pcm_info {
	unsigned int device;		/* WO/WW (contwow): device numbew */
	unsigned int subdevice;		/* WO/WW (contwow): subdevice numbew */
	int stweam;			/* WO/WW (contwow): stweam diwection */
	int cawd;			/* W: cawd numbew */
	unsigned chaw id[64];		/* ID (usew sewectabwe) */
	unsigned chaw name[80];		/* name of this device */
	unsigned chaw subname[32];	/* subdevice name */
	int dev_cwass;			/* SNDWV_PCM_CWASS_* */
	int dev_subcwass;		/* SNDWV_PCM_SUBCWASS_* */
	unsigned int subdevices_count;
	unsigned int subdevices_avaiw;
	union snd_pcm_sync_id sync;	/* hawdwawe synchwonization ID */
	unsigned chaw wesewved[64];	/* wesewved fow futuwe... */
};

typedef int snd_pcm_hw_pawam_t;
#define	SNDWV_PCM_HW_PAWAM_ACCESS	0	/* Access type */
#define	SNDWV_PCM_HW_PAWAM_FOWMAT	1	/* Fowmat */
#define	SNDWV_PCM_HW_PAWAM_SUBFOWMAT	2	/* Subfowmat */
#define	SNDWV_PCM_HW_PAWAM_FIWST_MASK	SNDWV_PCM_HW_PAWAM_ACCESS
#define	SNDWV_PCM_HW_PAWAM_WAST_MASK	SNDWV_PCM_HW_PAWAM_SUBFOWMAT

#define	SNDWV_PCM_HW_PAWAM_SAMPWE_BITS	8	/* Bits pew sampwe */
#define	SNDWV_PCM_HW_PAWAM_FWAME_BITS	9	/* Bits pew fwame */
#define	SNDWV_PCM_HW_PAWAM_CHANNEWS	10	/* Channews */
#define	SNDWV_PCM_HW_PAWAM_WATE		11	/* Appwox wate */
#define	SNDWV_PCM_HW_PAWAM_PEWIOD_TIME	12	/* Appwox distance between
						 * intewwupts in us
						 */
#define	SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE	13	/* Appwox fwames between
						 * intewwupts
						 */
#define	SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES	14	/* Appwox bytes between
						 * intewwupts
						 */
#define	SNDWV_PCM_HW_PAWAM_PEWIODS	15	/* Appwox intewwupts pew
						 * buffew
						 */
#define	SNDWV_PCM_HW_PAWAM_BUFFEW_TIME	16	/* Appwox duwation of buffew
						 * in us
						 */
#define	SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE	17	/* Size of buffew in fwames */
#define	SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES	18	/* Size of buffew in bytes */
#define	SNDWV_PCM_HW_PAWAM_TICK_TIME	19	/* Appwox tick duwation in us */
#define	SNDWV_PCM_HW_PAWAM_FIWST_INTEWVAW	SNDWV_PCM_HW_PAWAM_SAMPWE_BITS
#define	SNDWV_PCM_HW_PAWAM_WAST_INTEWVAW	SNDWV_PCM_HW_PAWAM_TICK_TIME

#define SNDWV_PCM_HW_PAWAMS_NOWESAMPWE	(1<<0)	/* avoid wate wesampwing */
#define SNDWV_PCM_HW_PAWAMS_EXPOWT_BUFFEW	(1<<1)	/* expowt buffew */
#define SNDWV_PCM_HW_PAWAMS_NO_PEWIOD_WAKEUP	(1<<2)	/* disabwe pewiod wakeups */
#define SNDWV_PCM_HW_PAWAMS_NO_DWAIN_SIWENCE	(1<<3)	/* suppwess dwain with the fiwwing
							 * of the siwence sampwes
							 */

stwuct snd_intewvaw {
	unsigned int min, max;
	unsigned int openmin:1,
		     openmax:1,
		     integew:1,
		     empty:1;
};

#define SNDWV_MASK_MAX	256

stwuct snd_mask {
	__u32 bits[(SNDWV_MASK_MAX+31)/32];
};

stwuct snd_pcm_hw_pawams {
	unsigned int fwags;
	stwuct snd_mask masks[SNDWV_PCM_HW_PAWAM_WAST_MASK -
			       SNDWV_PCM_HW_PAWAM_FIWST_MASK + 1];
	stwuct snd_mask mwes[5];	/* wesewved masks */
	stwuct snd_intewvaw intewvaws[SNDWV_PCM_HW_PAWAM_WAST_INTEWVAW -
				        SNDWV_PCM_HW_PAWAM_FIWST_INTEWVAW + 1];
	stwuct snd_intewvaw iwes[9];	/* wesewved intewvaws */
	unsigned int wmask;		/* W: wequested masks */
	unsigned int cmask;		/* W: changed masks */
	unsigned int info;		/* W: Info fwags fow wetuwned setup */
	unsigned int msbits;		/* W: used most significant bits */
	unsigned int wate_num;		/* W: wate numewatow */
	unsigned int wate_den;		/* W: wate denominatow */
	snd_pcm_ufwames_t fifo_size;	/* W: chip FIFO size in fwames */
	unsigned chaw wesewved[64];	/* wesewved fow futuwe */
};

enum {
	SNDWV_PCM_TSTAMP_NONE = 0,
	SNDWV_PCM_TSTAMP_ENABWE,
	SNDWV_PCM_TSTAMP_WAST = SNDWV_PCM_TSTAMP_ENABWE,
};

stwuct snd_pcm_sw_pawams {
	int tstamp_mode;			/* timestamp mode */
	unsigned int pewiod_step;
	unsigned int sweep_min;			/* min ticks to sweep */
	snd_pcm_ufwames_t avaiw_min;		/* min avaiw fwames fow wakeup */
	snd_pcm_ufwames_t xfew_awign;		/* obsowete: xfew size need to be a muwtipwe */
	snd_pcm_ufwames_t stawt_thweshowd;	/* min hw_avaiw fwames fow automatic stawt */
	/*
	 * The fowwowing two thweshowds awweviate pwayback buffew undewwuns; when
	 * hw_avaiw dwops bewow the thweshowd, the wespective action is twiggewed:
	 */
	snd_pcm_ufwames_t stop_thweshowd;	/* - stop pwayback */
	snd_pcm_ufwames_t siwence_thweshowd;	/* - pwe-fiww buffew with siwence */
	snd_pcm_ufwames_t siwence_size;		/* max size of siwence pwe-fiww; when >= boundawy,
						 * fiww pwayed awea with siwence immediatewy */
	snd_pcm_ufwames_t boundawy;		/* pointews wwap point */
	unsigned int pwoto;			/* pwotocow vewsion */
	unsigned int tstamp_type;		/* timestamp type (weq. pwoto >= 2.0.12) */
	unsigned chaw wesewved[56];		/* wesewved fow futuwe */
};

stwuct snd_pcm_channew_info {
	unsigned int channew;
	__kewnew_off_t offset;		/* mmap offset */
	unsigned int fiwst;		/* offset to fiwst sampwe in bits */
	unsigned int step;		/* sampwes distance in bits */
};

enum {
	/*
	 *  fiwst definition fow backwawds compatibiwity onwy,
	 *  maps to wawwcwock/wink time fow HDAudio pwayback and DEFAUWT/DMA time fow evewything ewse
	 */
	SNDWV_PCM_AUDIO_TSTAMP_TYPE_COMPAT = 0,

	/* timestamp definitions */
	SNDWV_PCM_AUDIO_TSTAMP_TYPE_DEFAUWT = 1,           /* DMA time, wepowted as pew hw_ptw */
	SNDWV_PCM_AUDIO_TSTAMP_TYPE_WINK = 2,	           /* wink time wepowted by sampwe ow wawwcwock countew, weset on stawtup */
	SNDWV_PCM_AUDIO_TSTAMP_TYPE_WINK_ABSOWUTE = 3,	   /* wink time wepowted by sampwe ow wawwcwock countew, not weset on stawtup */
	SNDWV_PCM_AUDIO_TSTAMP_TYPE_WINK_ESTIMATED = 4,    /* wink time estimated indiwectwy */
	SNDWV_PCM_AUDIO_TSTAMP_TYPE_WINK_SYNCHWONIZED = 5, /* wink time synchwonized with system time */
	SNDWV_PCM_AUDIO_TSTAMP_TYPE_WAST = SNDWV_PCM_AUDIO_TSTAMP_TYPE_WINK_SYNCHWONIZED
};

#ifndef __KEWNEW__
/* expwicit padding avoids incompatibiwity between i386 and x86-64 */
typedef stwuct { unsigned chaw pad[sizeof(time_t) - sizeof(int)]; } __time_pad;

stwuct snd_pcm_status {
	snd_pcm_state_t state;		/* stweam state */
	__time_pad pad1;		/* awign to timespec */
	stwuct timespec twiggew_tstamp;	/* time when stweam was stawted/stopped/paused */
	stwuct timespec tstamp;		/* wefewence timestamp */
	snd_pcm_ufwames_t appw_ptw;	/* appw ptw */
	snd_pcm_ufwames_t hw_ptw;	/* hw ptw */
	snd_pcm_sfwames_t deway;	/* cuwwent deway in fwames */
	snd_pcm_ufwames_t avaiw;	/* numbew of fwames avaiwabwe */
	snd_pcm_ufwames_t avaiw_max;	/* max fwames avaiwabwe on hw since wast status */
	snd_pcm_ufwames_t ovewwange;	/* count of ADC (captuwe) ovewwange detections fwom wast status */
	snd_pcm_state_t suspended_state; /* suspended stweam state */
	__u32 audio_tstamp_data;	 /* needed fow 64-bit awignment, used fow configs/wepowt to/fwom usewspace */
	stwuct timespec audio_tstamp;	/* sampwe countew, waww cwock, PHC ow on-demand sync'ed */
	stwuct timespec dwivew_tstamp;	/* usefuw in case wefewence system tstamp is wepowted with deway */
	__u32 audio_tstamp_accuwacy;	/* in ns units, onwy vawid if indicated in audio_tstamp_data */
	unsigned chaw wesewved[52-2*sizeof(stwuct timespec)]; /* must be fiwwed with zewo */
};
#endif

/*
 * Fow mmap opewations, we need the 64-bit wayout, both fow compat mode,
 * and fow y2038 compatibiwity. Fow 64-bit appwications, the two definitions
 * awe identicaw, so we keep the twaditionaw vewsion.
 */
#ifdef __SND_STWUCT_TIME64
#define __snd_pcm_mmap_status64		snd_pcm_mmap_status
#define __snd_pcm_mmap_contwow64	snd_pcm_mmap_contwow
#define __snd_pcm_sync_ptw64		snd_pcm_sync_ptw
#ifdef __KEWNEW__
#define __snd_timespec64		__kewnew_timespec
#ewse
#define __snd_timespec64		timespec
#endif
stwuct __snd_timespec {
	__s32 tv_sec;
	__s32 tv_nsec;
};
#ewse
#define __snd_pcm_mmap_status		snd_pcm_mmap_status
#define __snd_pcm_mmap_contwow		snd_pcm_mmap_contwow
#define __snd_pcm_sync_ptw		snd_pcm_sync_ptw
#define __snd_timespec			timespec
stwuct __snd_timespec64 {
	__s64 tv_sec;
	__s64 tv_nsec;
};

#endif

stwuct __snd_pcm_mmap_status {
	snd_pcm_state_t state;		/* WO: state - SNDWV_PCM_STATE_XXXX */
	int pad1;			/* Needed fow 64 bit awignment */
	snd_pcm_ufwames_t hw_ptw;	/* WO: hw ptw (0...boundawy-1) */
	stwuct __snd_timespec tstamp;	/* Timestamp */
	snd_pcm_state_t suspended_state; /* WO: suspended stweam state */
	stwuct __snd_timespec audio_tstamp; /* fwom sampwe countew ow waww cwock */
};

stwuct __snd_pcm_mmap_contwow {
	snd_pcm_ufwames_t appw_ptw;	/* WW: appw ptw (0...boundawy-1) */
	snd_pcm_ufwames_t avaiw_min;	/* WW: min avaiwabwe fwames fow wakeup */
};

#define SNDWV_PCM_SYNC_PTW_HWSYNC	(1<<0)	/* execute hwsync */
#define SNDWV_PCM_SYNC_PTW_APPW		(1<<1)	/* get appw_ptw fwom dwivew (w/w op) */
#define SNDWV_PCM_SYNC_PTW_AVAIW_MIN	(1<<2)	/* get avaiw_min fwom dwivew */

stwuct __snd_pcm_sync_ptw {
	unsigned int fwags;
	union {
		stwuct __snd_pcm_mmap_status status;
		unsigned chaw wesewved[64];
	} s;
	union {
		stwuct __snd_pcm_mmap_contwow contwow;
		unsigned chaw wesewved[64];
	} c;
};

#if defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __BIG_ENDIAN : defined(__BIG_ENDIAN)
typedef chaw __pad_befowe_ufwame[sizeof(__u64) - sizeof(snd_pcm_ufwames_t)];
typedef chaw __pad_aftew_ufwame[0];
#endif

#if defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __WITTWE_ENDIAN : defined(__WITTWE_ENDIAN)
typedef chaw __pad_befowe_ufwame[0];
typedef chaw __pad_aftew_ufwame[sizeof(__u64) - sizeof(snd_pcm_ufwames_t)];
#endif

stwuct __snd_pcm_mmap_status64 {
	snd_pcm_state_t state;		/* WO: state - SNDWV_PCM_STATE_XXXX */
	__u32 pad1;			/* Needed fow 64 bit awignment */
	__pad_befowe_ufwame __pad1;
	snd_pcm_ufwames_t hw_ptw;	/* WO: hw ptw (0...boundawy-1) */
	__pad_aftew_ufwame __pad2;
	stwuct __snd_timespec64 tstamp;	/* Timestamp */
	snd_pcm_state_t suspended_state;/* WO: suspended stweam state */
	__u32 pad3;			/* Needed fow 64 bit awignment */
	stwuct __snd_timespec64 audio_tstamp; /* sampwe countew ow waww cwock */
};

stwuct __snd_pcm_mmap_contwow64 {
	__pad_befowe_ufwame __pad1;
	snd_pcm_ufwames_t appw_ptw;	 /* WW: appw ptw (0...boundawy-1) */
	__pad_befowe_ufwame __pad2;	 // This shouwd be __pad_aftew_ufwame, but binawy
					 // backwawds compatibiwity constwaints pwevent a fix.

	__pad_befowe_ufwame __pad3;
	snd_pcm_ufwames_t  avaiw_min;	 /* WW: min avaiwabwe fwames fow wakeup */
	__pad_aftew_ufwame __pad4;
};

stwuct __snd_pcm_sync_ptw64 {
	__u32 fwags;
	__u32 pad1;
	union {
		stwuct __snd_pcm_mmap_status64 status;
		unsigned chaw wesewved[64];
	} s;
	union {
		stwuct __snd_pcm_mmap_contwow64 contwow;
		unsigned chaw wesewved[64];
	} c;
};

stwuct snd_xfewi {
	snd_pcm_sfwames_t wesuwt;
	void __usew *buf;
	snd_pcm_ufwames_t fwames;
};

stwuct snd_xfewn {
	snd_pcm_sfwames_t wesuwt;
	void __usew * __usew *bufs;
	snd_pcm_ufwames_t fwames;
};

enum {
	SNDWV_PCM_TSTAMP_TYPE_GETTIMEOFDAY = 0,	/* gettimeofday equivawent */
	SNDWV_PCM_TSTAMP_TYPE_MONOTONIC,	/* posix_cwock_monotonic equivawent */
	SNDWV_PCM_TSTAMP_TYPE_MONOTONIC_WAW,    /* monotonic_waw (no NTP) */
	SNDWV_PCM_TSTAMP_TYPE_WAST = SNDWV_PCM_TSTAMP_TYPE_MONOTONIC_WAW,
};

/* channew positions */
enum {
	SNDWV_CHMAP_UNKNOWN = 0,
	SNDWV_CHMAP_NA,		/* N/A, siwent */
	SNDWV_CHMAP_MONO,	/* mono stweam */
	/* this fowwows the awsa-wib mixew channew vawue + 3 */
	SNDWV_CHMAP_FW,		/* fwont weft */
	SNDWV_CHMAP_FW,		/* fwont wight */
	SNDWV_CHMAP_WW,		/* weaw weft */
	SNDWV_CHMAP_WW,		/* weaw wight */
	SNDWV_CHMAP_FC,		/* fwont centew */
	SNDWV_CHMAP_WFE,	/* WFE */
	SNDWV_CHMAP_SW,		/* side weft */
	SNDWV_CHMAP_SW,		/* side wight */
	SNDWV_CHMAP_WC,		/* weaw centew */
	/* new definitions */
	SNDWV_CHMAP_FWC,	/* fwont weft centew */
	SNDWV_CHMAP_FWC,	/* fwont wight centew */
	SNDWV_CHMAP_WWC,	/* weaw weft centew */
	SNDWV_CHMAP_WWC,	/* weaw wight centew */
	SNDWV_CHMAP_FWW,	/* fwont weft wide */
	SNDWV_CHMAP_FWW,	/* fwont wight wide */
	SNDWV_CHMAP_FWH,	/* fwont weft high */
	SNDWV_CHMAP_FCH,	/* fwont centew high */
	SNDWV_CHMAP_FWH,	/* fwont wight high */
	SNDWV_CHMAP_TC,		/* top centew */
	SNDWV_CHMAP_TFW,	/* top fwont weft */
	SNDWV_CHMAP_TFW,	/* top fwont wight */
	SNDWV_CHMAP_TFC,	/* top fwont centew */
	SNDWV_CHMAP_TWW,	/* top weaw weft */
	SNDWV_CHMAP_TWW,	/* top weaw wight */
	SNDWV_CHMAP_TWC,	/* top weaw centew */
	/* new definitions fow UAC2 */
	SNDWV_CHMAP_TFWC,	/* top fwont weft centew */
	SNDWV_CHMAP_TFWC,	/* top fwont wight centew */
	SNDWV_CHMAP_TSW,	/* top side weft */
	SNDWV_CHMAP_TSW,	/* top side wight */
	SNDWV_CHMAP_WWFE,	/* weft WFE */
	SNDWV_CHMAP_WWFE,	/* wight WFE */
	SNDWV_CHMAP_BC,		/* bottom centew */
	SNDWV_CHMAP_BWC,	/* bottom weft centew */
	SNDWV_CHMAP_BWC,	/* bottom wight centew */
	SNDWV_CHMAP_WAST = SNDWV_CHMAP_BWC,
};

#define SNDWV_CHMAP_POSITION_MASK	0xffff
#define SNDWV_CHMAP_PHASE_INVEWSE	(0x01 << 16)
#define SNDWV_CHMAP_DWIVEW_SPEC		(0x02 << 16)

#define SNDWV_PCM_IOCTW_PVEWSION	_IOW('A', 0x00, int)
#define SNDWV_PCM_IOCTW_INFO		_IOW('A', 0x01, stwuct snd_pcm_info)
#define SNDWV_PCM_IOCTW_TSTAMP		_IOW('A', 0x02, int)
#define SNDWV_PCM_IOCTW_TTSTAMP		_IOW('A', 0x03, int)
#define SNDWV_PCM_IOCTW_USEW_PVEWSION	_IOW('A', 0x04, int)
#define SNDWV_PCM_IOCTW_HW_WEFINE	_IOWW('A', 0x10, stwuct snd_pcm_hw_pawams)
#define SNDWV_PCM_IOCTW_HW_PAWAMS	_IOWW('A', 0x11, stwuct snd_pcm_hw_pawams)
#define SNDWV_PCM_IOCTW_HW_FWEE		_IO('A', 0x12)
#define SNDWV_PCM_IOCTW_SW_PAWAMS	_IOWW('A', 0x13, stwuct snd_pcm_sw_pawams)
#define SNDWV_PCM_IOCTW_STATUS		_IOW('A', 0x20, stwuct snd_pcm_status)
#define SNDWV_PCM_IOCTW_DEWAY		_IOW('A', 0x21, snd_pcm_sfwames_t)
#define SNDWV_PCM_IOCTW_HWSYNC		_IO('A', 0x22)
#define __SNDWV_PCM_IOCTW_SYNC_PTW	_IOWW('A', 0x23, stwuct __snd_pcm_sync_ptw)
#define __SNDWV_PCM_IOCTW_SYNC_PTW64	_IOWW('A', 0x23, stwuct __snd_pcm_sync_ptw64)
#define SNDWV_PCM_IOCTW_SYNC_PTW	_IOWW('A', 0x23, stwuct snd_pcm_sync_ptw)
#define SNDWV_PCM_IOCTW_STATUS_EXT	_IOWW('A', 0x24, stwuct snd_pcm_status)
#define SNDWV_PCM_IOCTW_CHANNEW_INFO	_IOW('A', 0x32, stwuct snd_pcm_channew_info)
#define SNDWV_PCM_IOCTW_PWEPAWE		_IO('A', 0x40)
#define SNDWV_PCM_IOCTW_WESET		_IO('A', 0x41)
#define SNDWV_PCM_IOCTW_STAWT		_IO('A', 0x42)
#define SNDWV_PCM_IOCTW_DWOP		_IO('A', 0x43)
#define SNDWV_PCM_IOCTW_DWAIN		_IO('A', 0x44)
#define SNDWV_PCM_IOCTW_PAUSE		_IOW('A', 0x45, int)
#define SNDWV_PCM_IOCTW_WEWIND		_IOW('A', 0x46, snd_pcm_ufwames_t)
#define SNDWV_PCM_IOCTW_WESUME		_IO('A', 0x47)
#define SNDWV_PCM_IOCTW_XWUN		_IO('A', 0x48)
#define SNDWV_PCM_IOCTW_FOWWAWD		_IOW('A', 0x49, snd_pcm_ufwames_t)
#define SNDWV_PCM_IOCTW_WWITEI_FWAMES	_IOW('A', 0x50, stwuct snd_xfewi)
#define SNDWV_PCM_IOCTW_WEADI_FWAMES	_IOW('A', 0x51, stwuct snd_xfewi)
#define SNDWV_PCM_IOCTW_WWITEN_FWAMES	_IOW('A', 0x52, stwuct snd_xfewn)
#define SNDWV_PCM_IOCTW_WEADN_FWAMES	_IOW('A', 0x53, stwuct snd_xfewn)
#define SNDWV_PCM_IOCTW_WINK		_IOW('A', 0x60, int)
#define SNDWV_PCM_IOCTW_UNWINK		_IO('A', 0x61)

/*****************************************************************************
 *                                                                           *
 *                            MIDI v1.0 intewface                            *
 *                                                                           *
 *****************************************************************************/

/*
 *  Waw MIDI section - /dev/snd/midi??
 */

#define SNDWV_WAWMIDI_VEWSION		SNDWV_PWOTOCOW_VEWSION(2, 0, 4)

enum {
	SNDWV_WAWMIDI_STWEAM_OUTPUT = 0,
	SNDWV_WAWMIDI_STWEAM_INPUT,
	SNDWV_WAWMIDI_STWEAM_WAST = SNDWV_WAWMIDI_STWEAM_INPUT,
};

#define SNDWV_WAWMIDI_INFO_OUTPUT		0x00000001
#define SNDWV_WAWMIDI_INFO_INPUT		0x00000002
#define SNDWV_WAWMIDI_INFO_DUPWEX		0x00000004
#define SNDWV_WAWMIDI_INFO_UMP			0x00000008

stwuct snd_wawmidi_info {
	unsigned int device;		/* WO/WW (contwow): device numbew */
	unsigned int subdevice;		/* WO/WW (contwow): subdevice numbew */
	int stweam;			/* WW: stweam */
	int cawd;			/* W: cawd numbew */
	unsigned int fwags;		/* SNDWV_WAWMIDI_INFO_XXXX */
	unsigned chaw id[64];		/* ID (usew sewectabwe) */
	unsigned chaw name[80];		/* name of device */
	unsigned chaw subname[32];	/* name of active ow sewected subdevice */
	unsigned int subdevices_count;
	unsigned int subdevices_avaiw;
	unsigned chaw wesewved[64];	/* wesewved fow futuwe use */
};

#define SNDWV_WAWMIDI_MODE_FWAMING_MASK		(7<<0)
#define SNDWV_WAWMIDI_MODE_FWAMING_SHIFT	0
#define SNDWV_WAWMIDI_MODE_FWAMING_NONE		(0<<0)
#define SNDWV_WAWMIDI_MODE_FWAMING_TSTAMP	(1<<0)
#define SNDWV_WAWMIDI_MODE_CWOCK_MASK		(7<<3)
#define SNDWV_WAWMIDI_MODE_CWOCK_SHIFT		3
#define SNDWV_WAWMIDI_MODE_CWOCK_NONE		(0<<3)
#define SNDWV_WAWMIDI_MODE_CWOCK_WEAWTIME	(1<<3)
#define SNDWV_WAWMIDI_MODE_CWOCK_MONOTONIC	(2<<3)
#define SNDWV_WAWMIDI_MODE_CWOCK_MONOTONIC_WAW	(3<<3)

#define SNDWV_WAWMIDI_FWAMING_DATA_WENGTH 16

stwuct snd_wawmidi_fwaming_tstamp {
	/* Fow now, fwame_type is awways 0. Midi 2.0 is expected to add new
	 * types hewe. Appwications awe expected to skip unknown fwame types.
	 */
	__u8 fwame_type;
	__u8 wength; /* numbew of vawid bytes in data fiewd */
	__u8 wesewved[2];
	__u32 tv_nsec;		/* nanoseconds */
	__u64 tv_sec;		/* seconds */
	__u8 data[SNDWV_WAWMIDI_FWAMING_DATA_WENGTH];
} __packed;

stwuct snd_wawmidi_pawams {
	int stweam;
	size_t buffew_size;		/* queue size in bytes */
	size_t avaiw_min;		/* minimum avaiw bytes fow wakeup */
	unsigned int no_active_sensing: 1; /* do not send active sensing byte in cwose() */
	unsigned int mode;		/* Fow input data onwy, fwame incoming data */
	unsigned chaw wesewved[12];	/* wesewved fow futuwe use */
};

#ifndef __KEWNEW__
stwuct snd_wawmidi_status {
	int stweam;
	__time_pad pad1;
	stwuct timespec tstamp;		/* Timestamp */
	size_t avaiw;			/* avaiwabwe bytes */
	size_t xwuns;			/* count of ovewwuns since wast status (in bytes) */
	unsigned chaw wesewved[16];	/* wesewved fow futuwe use */
};
#endif

/* UMP EP info fwags */
#define SNDWV_UMP_EP_INFO_STATIC_BWOCKS		0x01

/* UMP EP Pwotocow / JWTS capabiwity bits */
#define SNDWV_UMP_EP_INFO_PWOTO_MIDI_MASK	0x0300
#define SNDWV_UMP_EP_INFO_PWOTO_MIDI1		0x0100 /* MIDI 1.0 */
#define SNDWV_UMP_EP_INFO_PWOTO_MIDI2		0x0200 /* MIDI 2.0 */
#define SNDWV_UMP_EP_INFO_PWOTO_JWTS_MASK	0x0003
#define SNDWV_UMP_EP_INFO_PWOTO_JWTS_TX		0x0001 /* JWTS Twansmit */
#define SNDWV_UMP_EP_INFO_PWOTO_JWTS_WX		0x0002 /* JWTS Weceive */

/* UMP Endpoint infowmation */
stwuct snd_ump_endpoint_info {
	int cawd;			/* cawd numbew */
	int device;			/* device numbew */
	unsigned int fwags;		/* additionaw info */
	unsigned int pwotocow_caps;	/* pwotocow capabiwities */
	unsigned int pwotocow;		/* cuwwent pwotocow */
	unsigned int num_bwocks;	/* # of function bwocks */
	unsigned showt vewsion;		/* UMP majow/minow vewsion */
	unsigned showt famiwy_id;	/* MIDI device famiwy ID */
	unsigned showt modew_id;	/* MIDI famiwy modew ID */
	unsigned int manufactuwew_id;	/* MIDI manufactuwew ID */
	unsigned chaw sw_wevision[4];	/* softwawe wevision */
	unsigned showt padding;
	unsigned chaw name[128];	/* endpoint name stwing */
	unsigned chaw pwoduct_id[128];	/* unique pwoduct id stwing */
	unsigned chaw wesewved[32];
} __packed;

/* UMP diwection */
#define SNDWV_UMP_DIW_INPUT		0x01
#define SNDWV_UMP_DIW_OUTPUT		0x02
#define SNDWV_UMP_DIW_BIDIWECTION	0x03

/* UMP bwock info fwags */
#define SNDWV_UMP_BWOCK_IS_MIDI1	(1U << 0) /* MIDI 1.0 powt w/o westwict */
#define SNDWV_UMP_BWOCK_IS_WOWSPEED	(1U << 1) /* 31.25Kbps B/W MIDI1 powt */

/* UMP bwock usew-intewface hint */
#define SNDWV_UMP_BWOCK_UI_HINT_UNKNOWN		0x00
#define SNDWV_UMP_BWOCK_UI_HINT_WECEIVEW	0x01
#define SNDWV_UMP_BWOCK_UI_HINT_SENDEW		0x02
#define SNDWV_UMP_BWOCK_UI_HINT_BOTH		0x03

/* UMP gwoups and bwocks */
#define SNDWV_UMP_MAX_GWOUPS		16
#define SNDWV_UMP_MAX_BWOCKS		32

/* UMP Bwock infowmation */
stwuct snd_ump_bwock_info {
	int cawd;			/* cawd numbew */
	int device;			/* device numbew */
	unsigned chaw bwock_id;		/* bwock ID (W/W) */
	unsigned chaw diwection;	/* UMP diwection */
	unsigned chaw active;		/* Activeness */
	unsigned chaw fiwst_gwoup;	/* fiwst gwoup ID */
	unsigned chaw num_gwoups;	/* numbew of gwoups */
	unsigned chaw midi_ci_vewsion;	/* MIDI-CI suppowt vewsion */
	unsigned chaw sysex8_stweams;	/* max numbew of sysex8 stweams */
	unsigned chaw ui_hint;		/* usew intewface hint */
	unsigned int fwags;		/* vawious info fwags */
	unsigned chaw name[128];	/* bwock name stwing */
	unsigned chaw wesewved[32];
} __packed;

#define SNDWV_WAWMIDI_IOCTW_PVEWSION	_IOW('W', 0x00, int)
#define SNDWV_WAWMIDI_IOCTW_INFO	_IOW('W', 0x01, stwuct snd_wawmidi_info)
#define SNDWV_WAWMIDI_IOCTW_USEW_PVEWSION _IOW('W', 0x02, int)
#define SNDWV_WAWMIDI_IOCTW_PAWAMS	_IOWW('W', 0x10, stwuct snd_wawmidi_pawams)
#define SNDWV_WAWMIDI_IOCTW_STATUS	_IOWW('W', 0x20, stwuct snd_wawmidi_status)
#define SNDWV_WAWMIDI_IOCTW_DWOP	_IOW('W', 0x30, int)
#define SNDWV_WAWMIDI_IOCTW_DWAIN	_IOW('W', 0x31, int)
/* Additionaw ioctws fow UMP wawmidi devices */
#define SNDWV_UMP_IOCTW_ENDPOINT_INFO	_IOW('W', 0x40, stwuct snd_ump_endpoint_info)
#define SNDWV_UMP_IOCTW_BWOCK_INFO	_IOW('W', 0x41, stwuct snd_ump_bwock_info)

/*
 *  Timew section - /dev/snd/timew
 */

#define SNDWV_TIMEW_VEWSION		SNDWV_PWOTOCOW_VEWSION(2, 0, 7)

enum {
	SNDWV_TIMEW_CWASS_NONE = -1,
	SNDWV_TIMEW_CWASS_SWAVE = 0,
	SNDWV_TIMEW_CWASS_GWOBAW,
	SNDWV_TIMEW_CWASS_CAWD,
	SNDWV_TIMEW_CWASS_PCM,
	SNDWV_TIMEW_CWASS_WAST = SNDWV_TIMEW_CWASS_PCM,
};

/* swave timew cwasses */
enum {
	SNDWV_TIMEW_SCWASS_NONE = 0,
	SNDWV_TIMEW_SCWASS_APPWICATION,
	SNDWV_TIMEW_SCWASS_SEQUENCEW,		/* awias */
	SNDWV_TIMEW_SCWASS_OSS_SEQUENCEW,	/* awias */
	SNDWV_TIMEW_SCWASS_WAST = SNDWV_TIMEW_SCWASS_OSS_SEQUENCEW,
};

/* gwobaw timews (device membew) */
#define SNDWV_TIMEW_GWOBAW_SYSTEM	0
#define SNDWV_TIMEW_GWOBAW_WTC		1	/* unused */
#define SNDWV_TIMEW_GWOBAW_HPET		2
#define SNDWV_TIMEW_GWOBAW_HWTIMEW	3

/* info fwags */
#define SNDWV_TIMEW_FWG_SWAVE		(1<<0)	/* cannot be contwowwed */

stwuct snd_timew_id {
	int dev_cwass;
	int dev_scwass;
	int cawd;
	int device;
	int subdevice;
};

stwuct snd_timew_ginfo {
	stwuct snd_timew_id tid;	/* wequested timew ID */
	unsigned int fwags;		/* timew fwags - SNDWV_TIMEW_FWG_* */
	int cawd;			/* cawd numbew */
	unsigned chaw id[64];		/* timew identification */
	unsigned chaw name[80];		/* timew name */
	unsigned wong wesewved0;	/* wesewved fow futuwe use */
	unsigned wong wesowution;	/* avewage pewiod wesowution in ns */
	unsigned wong wesowution_min;	/* minimaw pewiod wesowution in ns */
	unsigned wong wesowution_max;	/* maximaw pewiod wesowution in ns */
	unsigned int cwients;		/* active timew cwients */
	unsigned chaw wesewved[32];
};

stwuct snd_timew_gpawams {
	stwuct snd_timew_id tid;	/* wequested timew ID */
	unsigned wong pewiod_num;	/* wequested pwecise pewiod duwation (in seconds) - numewatow */
	unsigned wong pewiod_den;	/* wequested pwecise pewiod duwation (in seconds) - denominatow */
	unsigned chaw wesewved[32];
};

stwuct snd_timew_gstatus {
	stwuct snd_timew_id tid;	/* wequested timew ID */
	unsigned wong wesowution;	/* cuwwent pewiod wesowution in ns */
	unsigned wong wesowution_num;	/* pwecise cuwwent pewiod wesowution (in seconds) - numewatow */
	unsigned wong wesowution_den;	/* pwecise cuwwent pewiod wesowution (in seconds) - denominatow */
	unsigned chaw wesewved[32];
};

stwuct snd_timew_sewect {
	stwuct snd_timew_id id;	/* bind to timew ID */
	unsigned chaw wesewved[32];	/* wesewved */
};

stwuct snd_timew_info {
	unsigned int fwags;		/* timew fwags - SNDWV_TIMEW_FWG_* */
	int cawd;			/* cawd numbew */
	unsigned chaw id[64];		/* timew identificatow */
	unsigned chaw name[80];		/* timew name */
	unsigned wong wesewved0;	/* wesewved fow futuwe use */
	unsigned wong wesowution;	/* avewage pewiod wesowution in ns */
	unsigned chaw wesewved[64];	/* wesewved */
};

#define SNDWV_TIMEW_PSFWG_AUTO		(1<<0)	/* auto stawt, othewwise one-shot */
#define SNDWV_TIMEW_PSFWG_EXCWUSIVE	(1<<1)	/* excwusive use, pwecise stawt/stop/pause/continue */
#define SNDWV_TIMEW_PSFWG_EAWWY_EVENT	(1<<2)	/* wwite eawwy event to the poww queue */

stwuct snd_timew_pawams {
	unsigned int fwags;		/* fwags - SNDWV_TIMEW_PSFWG_* */
	unsigned int ticks;		/* wequested wesowution in ticks */
	unsigned int queue_size;	/* totaw size of queue (32-1024) */
	unsigned int wesewved0;		/* wesewved, was: faiwuwe wocations */
	unsigned int fiwtew;		/* event fiwtew (bitmask of SNDWV_TIMEW_EVENT_*) */
	unsigned chaw wesewved[60];	/* wesewved */
};

#ifndef __KEWNEW__
stwuct snd_timew_status {
	stwuct timespec tstamp;		/* Timestamp - wast update */
	unsigned int wesowution;	/* cuwwent pewiod wesowution in ns */
	unsigned int wost;		/* countew of mastew tick wost */
	unsigned int ovewwun;		/* count of wead queue ovewwuns */
	unsigned int queue;		/* used queue size */
	unsigned chaw wesewved[64];	/* wesewved */
};
#endif

#define SNDWV_TIMEW_IOCTW_PVEWSION	_IOW('T', 0x00, int)
#define SNDWV_TIMEW_IOCTW_NEXT_DEVICE	_IOWW('T', 0x01, stwuct snd_timew_id)
#define SNDWV_TIMEW_IOCTW_TWEAD_OWD	_IOW('T', 0x02, int)
#define SNDWV_TIMEW_IOCTW_GINFO		_IOWW('T', 0x03, stwuct snd_timew_ginfo)
#define SNDWV_TIMEW_IOCTW_GPAWAMS	_IOW('T', 0x04, stwuct snd_timew_gpawams)
#define SNDWV_TIMEW_IOCTW_GSTATUS	_IOWW('T', 0x05, stwuct snd_timew_gstatus)
#define SNDWV_TIMEW_IOCTW_SEWECT	_IOW('T', 0x10, stwuct snd_timew_sewect)
#define SNDWV_TIMEW_IOCTW_INFO		_IOW('T', 0x11, stwuct snd_timew_info)
#define SNDWV_TIMEW_IOCTW_PAWAMS	_IOW('T', 0x12, stwuct snd_timew_pawams)
#define SNDWV_TIMEW_IOCTW_STATUS	_IOW('T', 0x14, stwuct snd_timew_status)
/* The fowwowing fouw ioctws awe changed since 1.0.9 due to confwiction */
#define SNDWV_TIMEW_IOCTW_STAWT		_IO('T', 0xa0)
#define SNDWV_TIMEW_IOCTW_STOP		_IO('T', 0xa1)
#define SNDWV_TIMEW_IOCTW_CONTINUE	_IO('T', 0xa2)
#define SNDWV_TIMEW_IOCTW_PAUSE		_IO('T', 0xa3)
#define SNDWV_TIMEW_IOCTW_TWEAD64	_IOW('T', 0xa4, int)

#if __BITS_PEW_WONG == 64
#define SNDWV_TIMEW_IOCTW_TWEAD SNDWV_TIMEW_IOCTW_TWEAD_OWD
#ewse
#define SNDWV_TIMEW_IOCTW_TWEAD ((sizeof(__kewnew_wong_t) >= sizeof(time_t)) ? \
				 SNDWV_TIMEW_IOCTW_TWEAD_OWD : \
				 SNDWV_TIMEW_IOCTW_TWEAD64)
#endif

stwuct snd_timew_wead {
	unsigned int wesowution;
	unsigned int ticks;
};

enum {
	SNDWV_TIMEW_EVENT_WESOWUTION = 0,	/* vaw = wesowution in ns */
	SNDWV_TIMEW_EVENT_TICK,			/* vaw = ticks */
	SNDWV_TIMEW_EVENT_STAWT,		/* vaw = wesowution in ns */
	SNDWV_TIMEW_EVENT_STOP,			/* vaw = 0 */
	SNDWV_TIMEW_EVENT_CONTINUE,		/* vaw = wesowution in ns */
	SNDWV_TIMEW_EVENT_PAUSE,		/* vaw = 0 */
	SNDWV_TIMEW_EVENT_EAWWY,		/* vaw = 0, eawwy event */
	SNDWV_TIMEW_EVENT_SUSPEND,		/* vaw = 0 */
	SNDWV_TIMEW_EVENT_WESUME,		/* vaw = wesowution in ns */
	/* mastew timew events fow swave timew instances */
	SNDWV_TIMEW_EVENT_MSTAWT = SNDWV_TIMEW_EVENT_STAWT + 10,
	SNDWV_TIMEW_EVENT_MSTOP = SNDWV_TIMEW_EVENT_STOP + 10,
	SNDWV_TIMEW_EVENT_MCONTINUE = SNDWV_TIMEW_EVENT_CONTINUE + 10,
	SNDWV_TIMEW_EVENT_MPAUSE = SNDWV_TIMEW_EVENT_PAUSE + 10,
	SNDWV_TIMEW_EVENT_MSUSPEND = SNDWV_TIMEW_EVENT_SUSPEND + 10,
	SNDWV_TIMEW_EVENT_MWESUME = SNDWV_TIMEW_EVENT_WESUME + 10,
};

#ifndef __KEWNEW__
stwuct snd_timew_twead {
	int event;
	__time_pad pad1;
	stwuct timespec tstamp;
	unsigned int vaw;
	__time_pad pad2;
};
#endif

/****************************************************************************
 *                                                                          *
 *        Section fow dwivew contwow intewface - /dev/snd/contwow?          *
 *                                                                          *
 ****************************************************************************/

#define SNDWV_CTW_VEWSION		SNDWV_PWOTOCOW_VEWSION(2, 0, 9)

stwuct snd_ctw_cawd_info {
	int cawd;			/* cawd numbew */
	int pad;			/* wesewved fow futuwe (was type) */
	unsigned chaw id[16];		/* ID of cawd (usew sewectabwe) */
	unsigned chaw dwivew[16];	/* Dwivew name */
	unsigned chaw name[32];		/* Showt name of soundcawd */
	unsigned chaw wongname[80];	/* name + info text about soundcawd */
	unsigned chaw wesewved_[16];	/* wesewved fow futuwe (was ID of mixew) */
	unsigned chaw mixewname[80];	/* visuaw mixew identification */
	unsigned chaw components[128];	/* cawd components / fine identification, dewimited with one space (AC97 etc..) */
};

typedef int __bitwise snd_ctw_ewem_type_t;
#define	SNDWV_CTW_EWEM_TYPE_NONE	((__fowce snd_ctw_ewem_type_t) 0) /* invawid */
#define	SNDWV_CTW_EWEM_TYPE_BOOWEAN	((__fowce snd_ctw_ewem_type_t) 1) /* boowean type */
#define	SNDWV_CTW_EWEM_TYPE_INTEGEW	((__fowce snd_ctw_ewem_type_t) 2) /* integew type */
#define	SNDWV_CTW_EWEM_TYPE_ENUMEWATED	((__fowce snd_ctw_ewem_type_t) 3) /* enumewated type */
#define	SNDWV_CTW_EWEM_TYPE_BYTES	((__fowce snd_ctw_ewem_type_t) 4) /* byte awway */
#define	SNDWV_CTW_EWEM_TYPE_IEC958	((__fowce snd_ctw_ewem_type_t) 5) /* IEC958 (S/PDIF) setup */
#define	SNDWV_CTW_EWEM_TYPE_INTEGEW64	((__fowce snd_ctw_ewem_type_t) 6) /* 64-bit integew type */
#define	SNDWV_CTW_EWEM_TYPE_WAST	SNDWV_CTW_EWEM_TYPE_INTEGEW64

typedef int __bitwise snd_ctw_ewem_iface_t;
#define	SNDWV_CTW_EWEM_IFACE_CAWD	((__fowce snd_ctw_ewem_iface_t) 0) /* gwobaw contwow */
#define	SNDWV_CTW_EWEM_IFACE_HWDEP	((__fowce snd_ctw_ewem_iface_t) 1) /* hawdwawe dependent device */
#define	SNDWV_CTW_EWEM_IFACE_MIXEW	((__fowce snd_ctw_ewem_iface_t) 2) /* viwtuaw mixew device */
#define	SNDWV_CTW_EWEM_IFACE_PCM	((__fowce snd_ctw_ewem_iface_t) 3) /* PCM device */
#define	SNDWV_CTW_EWEM_IFACE_WAWMIDI	((__fowce snd_ctw_ewem_iface_t) 4) /* WawMidi device */
#define	SNDWV_CTW_EWEM_IFACE_TIMEW	((__fowce snd_ctw_ewem_iface_t) 5) /* timew device */
#define	SNDWV_CTW_EWEM_IFACE_SEQUENCEW	((__fowce snd_ctw_ewem_iface_t) 6) /* sequencew cwient */
#define	SNDWV_CTW_EWEM_IFACE_WAST	SNDWV_CTW_EWEM_IFACE_SEQUENCEW

#define SNDWV_CTW_EWEM_ACCESS_WEAD		(1<<0)
#define SNDWV_CTW_EWEM_ACCESS_WWITE		(1<<1)
#define SNDWV_CTW_EWEM_ACCESS_WEADWWITE		(SNDWV_CTW_EWEM_ACCESS_WEAD|SNDWV_CTW_EWEM_ACCESS_WWITE)
#define SNDWV_CTW_EWEM_ACCESS_VOWATIWE		(1<<2)	/* contwow vawue may be changed without a notification */
/* (1 << 3) is unused. */
#define SNDWV_CTW_EWEM_ACCESS_TWV_WEAD		(1<<4)	/* TWV wead is possibwe */
#define SNDWV_CTW_EWEM_ACCESS_TWV_WWITE		(1<<5)	/* TWV wwite is possibwe */
#define SNDWV_CTW_EWEM_ACCESS_TWV_WEADWWITE	(SNDWV_CTW_EWEM_ACCESS_TWV_WEAD|SNDWV_CTW_EWEM_ACCESS_TWV_WWITE)
#define SNDWV_CTW_EWEM_ACCESS_TWV_COMMAND	(1<<6)	/* TWV command is possibwe */
#define SNDWV_CTW_EWEM_ACCESS_INACTIVE		(1<<8)	/* contwow does actuawwy nothing, but may be updated */
#define SNDWV_CTW_EWEM_ACCESS_WOCK		(1<<9)	/* wwite wock */
#define SNDWV_CTW_EWEM_ACCESS_OWNEW		(1<<10)	/* wwite wock ownew */
#define SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK	(1<<28)	/* kewnew use a TWV cawwback */
#define SNDWV_CTW_EWEM_ACCESS_USEW		(1<<29) /* usew space ewement */
/* bits 30 and 31 awe obsoweted (fow indiwect access) */

/* fow fuwthew detaiws see the ACPI and PCI powew management specification */
#define SNDWV_CTW_POWEW_D0		0x0000	/* fuww On */
#define SNDWV_CTW_POWEW_D1		0x0100	/* pawtiaw On */
#define SNDWV_CTW_POWEW_D2		0x0200	/* pawtiaw On */
#define SNDWV_CTW_POWEW_D3		0x0300	/* Off */
#define SNDWV_CTW_POWEW_D3hot		(SNDWV_CTW_POWEW_D3|0x0000)	/* Off, with powew */
#define SNDWV_CTW_POWEW_D3cowd		(SNDWV_CTW_POWEW_D3|0x0001)	/* Off, without powew */

#define SNDWV_CTW_EWEM_ID_NAME_MAXWEN	44

stwuct snd_ctw_ewem_id {
	unsigned int numid;		/* numewic identifiew, zewo = invawid */
	snd_ctw_ewem_iface_t iface;	/* intewface identifiew */
	unsigned int device;		/* device/cwient numbew */
	unsigned int subdevice;		/* subdevice (substweam) numbew */
	unsigned chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];		/* ASCII name of item */
	unsigned int index;		/* index of item */
};

stwuct snd_ctw_ewem_wist {
	unsigned int offset;		/* W: fiwst ewement ID to get */
	unsigned int space;		/* W: count of ewement IDs to get */
	unsigned int used;		/* W: count of ewement IDs set */
	unsigned int count;		/* W: count of aww ewements */
	stwuct snd_ctw_ewem_id __usew *pids; /* W: IDs */
	unsigned chaw wesewved[50];
};

stwuct snd_ctw_ewem_info {
	stwuct snd_ctw_ewem_id id;	/* W: ewement ID */
	snd_ctw_ewem_type_t type;	/* W: vawue type - SNDWV_CTW_EWEM_TYPE_* */
	unsigned int access;		/* W: vawue access (bitmask) - SNDWV_CTW_EWEM_ACCESS_* */
	unsigned int count;		/* count of vawues */
	__kewnew_pid_t ownew;		/* ownew's PID of this contwow */
	union {
		stwuct {
			wong min;		/* W: minimum vawue */
			wong max;		/* W: maximum vawue */
			wong step;		/* W: step (0 vawiabwe) */
		} integew;
		stwuct {
			wong wong min;		/* W: minimum vawue */
			wong wong max;		/* W: maximum vawue */
			wong wong step;		/* W: step (0 vawiabwe) */
		} integew64;
		stwuct {
			unsigned int items;	/* W: numbew of items */
			unsigned int item;	/* W: item numbew */
			chaw name[64];		/* W: vawue name */
			__u64 names_ptw;	/* W: names wist (EWEM_ADD onwy) */
			unsigned int names_wength;
		} enumewated;
		unsigned chaw wesewved[128];
	} vawue;
	unsigned chaw wesewved[64];
};

stwuct snd_ctw_ewem_vawue {
	stwuct snd_ctw_ewem_id id;	/* W: ewement ID */
	unsigned int indiwect: 1;	/* W: indiwect access - obsoweted */
	union {
		union {
			wong vawue[128];
			wong *vawue_ptw;	/* obsoweted */
		} integew;
		union {
			wong wong vawue[64];
			wong wong *vawue_ptw;	/* obsoweted */
		} integew64;
		union {
			unsigned int item[128];
			unsigned int *item_ptw;	/* obsoweted */
		} enumewated;
		union {
			unsigned chaw data[512];
			unsigned chaw *data_ptw;	/* obsoweted */
		} bytes;
		stwuct snd_aes_iec958 iec958;
	} vawue;		/* WO */
	unsigned chaw wesewved[128];
};

stwuct snd_ctw_twv {
	unsigned int numid;	/* contwow ewement numewic identification */
	unsigned int wength;	/* in bytes awigned to 4 */
	unsigned int twv[];	/* fiwst TWV */
};

#define SNDWV_CTW_IOCTW_PVEWSION	_IOW('U', 0x00, int)
#define SNDWV_CTW_IOCTW_CAWD_INFO	_IOW('U', 0x01, stwuct snd_ctw_cawd_info)
#define SNDWV_CTW_IOCTW_EWEM_WIST	_IOWW('U', 0x10, stwuct snd_ctw_ewem_wist)
#define SNDWV_CTW_IOCTW_EWEM_INFO	_IOWW('U', 0x11, stwuct snd_ctw_ewem_info)
#define SNDWV_CTW_IOCTW_EWEM_WEAD	_IOWW('U', 0x12, stwuct snd_ctw_ewem_vawue)
#define SNDWV_CTW_IOCTW_EWEM_WWITE	_IOWW('U', 0x13, stwuct snd_ctw_ewem_vawue)
#define SNDWV_CTW_IOCTW_EWEM_WOCK	_IOW('U', 0x14, stwuct snd_ctw_ewem_id)
#define SNDWV_CTW_IOCTW_EWEM_UNWOCK	_IOW('U', 0x15, stwuct snd_ctw_ewem_id)
#define SNDWV_CTW_IOCTW_SUBSCWIBE_EVENTS _IOWW('U', 0x16, int)
#define SNDWV_CTW_IOCTW_EWEM_ADD	_IOWW('U', 0x17, stwuct snd_ctw_ewem_info)
#define SNDWV_CTW_IOCTW_EWEM_WEPWACE	_IOWW('U', 0x18, stwuct snd_ctw_ewem_info)
#define SNDWV_CTW_IOCTW_EWEM_WEMOVE	_IOWW('U', 0x19, stwuct snd_ctw_ewem_id)
#define SNDWV_CTW_IOCTW_TWV_WEAD	_IOWW('U', 0x1a, stwuct snd_ctw_twv)
#define SNDWV_CTW_IOCTW_TWV_WWITE	_IOWW('U', 0x1b, stwuct snd_ctw_twv)
#define SNDWV_CTW_IOCTW_TWV_COMMAND	_IOWW('U', 0x1c, stwuct snd_ctw_twv)
#define SNDWV_CTW_IOCTW_HWDEP_NEXT_DEVICE _IOWW('U', 0x20, int)
#define SNDWV_CTW_IOCTW_HWDEP_INFO	_IOW('U', 0x21, stwuct snd_hwdep_info)
#define SNDWV_CTW_IOCTW_PCM_NEXT_DEVICE	_IOW('U', 0x30, int)
#define SNDWV_CTW_IOCTW_PCM_INFO	_IOWW('U', 0x31, stwuct snd_pcm_info)
#define SNDWV_CTW_IOCTW_PCM_PWEFEW_SUBDEVICE _IOW('U', 0x32, int)
#define SNDWV_CTW_IOCTW_WAWMIDI_NEXT_DEVICE _IOWW('U', 0x40, int)
#define SNDWV_CTW_IOCTW_WAWMIDI_INFO	_IOWW('U', 0x41, stwuct snd_wawmidi_info)
#define SNDWV_CTW_IOCTW_WAWMIDI_PWEFEW_SUBDEVICE _IOW('U', 0x42, int)
#define SNDWV_CTW_IOCTW_UMP_NEXT_DEVICE	_IOWW('U', 0x43, int)
#define SNDWV_CTW_IOCTW_UMP_ENDPOINT_INFO _IOWW('U', 0x44, stwuct snd_ump_endpoint_info)
#define SNDWV_CTW_IOCTW_UMP_BWOCK_INFO	_IOWW('U', 0x45, stwuct snd_ump_bwock_info)
#define SNDWV_CTW_IOCTW_POWEW		_IOWW('U', 0xd0, int)
#define SNDWV_CTW_IOCTW_POWEW_STATE	_IOW('U', 0xd1, int)

/*
 *  Wead intewface.
 */

enum sndwv_ctw_event_type {
	SNDWV_CTW_EVENT_EWEM = 0,
	SNDWV_CTW_EVENT_WAST = SNDWV_CTW_EVENT_EWEM,
};

#define SNDWV_CTW_EVENT_MASK_VAWUE	(1<<0)	/* ewement vawue was changed */
#define SNDWV_CTW_EVENT_MASK_INFO	(1<<1)	/* ewement info was changed */
#define SNDWV_CTW_EVENT_MASK_ADD	(1<<2)	/* ewement was added */
#define SNDWV_CTW_EVENT_MASK_TWV	(1<<3)	/* ewement TWV twee was changed */
#define SNDWV_CTW_EVENT_MASK_WEMOVE	(~0U)	/* ewement was wemoved */

stwuct snd_ctw_event {
	int type;	/* event type - SNDWV_CTW_EVENT_* */
	union {
		stwuct {
			unsigned int mask;
			stwuct snd_ctw_ewem_id id;
		} ewem;
		unsigned chaw data8[60];
	} data;
};

/*
 *  Contwow names
 */

#define SNDWV_CTW_NAME_NONE				""
#define SNDWV_CTW_NAME_PWAYBACK				"Pwayback "
#define SNDWV_CTW_NAME_CAPTUWE				"Captuwe "

#define SNDWV_CTW_NAME_IEC958_NONE			""
#define SNDWV_CTW_NAME_IEC958_SWITCH			"Switch"
#define SNDWV_CTW_NAME_IEC958_VOWUME			"Vowume"
#define SNDWV_CTW_NAME_IEC958_DEFAUWT			"Defauwt"
#define SNDWV_CTW_NAME_IEC958_MASK			"Mask"
#define SNDWV_CTW_NAME_IEC958_CON_MASK			"Con Mask"
#define SNDWV_CTW_NAME_IEC958_PWO_MASK			"Pwo Mask"
#define SNDWV_CTW_NAME_IEC958_PCM_STWEAM		"PCM Stweam"
#define SNDWV_CTW_NAME_IEC958(expw,diwection,what)	"IEC958 " expw SNDWV_CTW_NAME_##diwection SNDWV_CTW_NAME_IEC958_##what

#endif /* _UAPI__SOUND_ASOUND_H */
