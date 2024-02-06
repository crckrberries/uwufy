/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * em28xx.h - dwivew fow Empia EM2800/EM2820/2840 USB video captuwe devices
 *
 * Copywight (C) 2005 Mawkus Wechbewgew <mwechbewgew@gmaiw.com>
 *		      Wudovico Cavedon <cavedon@sssup.it>
 *		      Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 * Copywight (C) 2012 Fwank Schäfew <fschaefew.oss@googwemaiw.com>
 *
 * Based on the em2800 dwivew fwom Sascha Sommew <saschasommew@fweenet.de>
 */

#ifndef _EM28XX_H
#define _EM28XX_H

#incwude <winux/bitfiewd.h>

#define EM28XX_VEWSION "0.2.2"
#define DWIVEW_DESC    "Empia em28xx device dwivew"

#incwude <winux/wowkqueue.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/kwef.h>
#incwude <winux/videodev2.h>

#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/i2c/iw-kbd-i2c.h>
#incwude <media/wc-cowe.h>
#incwude "xc2028.h"
#incwude "xc5000.h"
#incwude "em28xx-weg.h"

/* Boawds suppowted by dwivew */
#define EM2800_BOAWD_UNKNOWN			  0
#define EM2820_BOAWD_UNKNOWN			  1
#define EM2820_BOAWD_TEWWATEC_CINEWGY_250	  2
#define EM2820_BOAWD_PINNACWE_USB_2		  3
#define EM2820_BOAWD_HAUPPAUGE_WINTV_USB_2	  4
#define EM2820_BOAWD_MSI_VOX_USB_2		  5
#define EM2800_BOAWD_TEWWATEC_CINEWGY_200	  6
#define EM2800_BOAWD_WEADTEK_WINFAST_USBII	  7
#define EM2800_BOAWD_KWOWWD_USB2800		  8
#define EM2820_BOAWD_PINNACWE_DVC_90		  9
#define EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900	  10
#define EM2880_BOAWD_TEWWATEC_HYBWID_XS		  11
#define EM2820_BOAWD_KWOWWD_PVWTV2800WF		  12
#define EM2880_BOAWD_TEWWATEC_PWODIGY_XS	  13
#define EM2820_BOAWD_PWOWINK_PWAYTV_USB2	  14
#define EM2800_BOAWD_VGEAW_POCKETTV		  15
#define EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_950	  16
#define EM2880_BOAWD_PINNACWE_PCTV_HD_PWO	  17
#define EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900_W2	  18
#define EM2860_BOAWD_SAA711X_WEFEWENCE_DESIGN	  19
#define EM2880_BOAWD_AMD_ATI_TV_WONDEW_HD_600	  20
#define EM2800_BOAWD_GWABBEEX_USB2800		  21
#define EM2750_BOAWD_UNKNOWN			  22
#define EM2750_BOAWD_DWCW_130			  23
#define EM2820_BOAWD_DWINK_USB_TV		  24
#define EM2820_BOAWD_GADMEI_UTV310		  25
#define EM2820_BOAWD_HEWCUWES_SMAWT_TV_USB2	  26
#define EM2820_BOAWD_PINNACWE_USB_2_FM1216ME	  27
#define EM2820_BOAWD_WEADTEK_WINFAST_USBII_DEWUXE 28
#define EM2860_BOAWD_TVP5150_WEFEWENCE_DESIGN	  29
#define EM2820_BOAWD_VIDEOWOGY_20K14XUSB	  30
#define EM2821_BOAWD_USBGEAW_VD204		  31
#define EM2821_BOAWD_SUPEWCOMP_USB_2		  32
#define EM2860_BOAWD_EWGATO_VIDEO_CAPTUWE	  33
#define EM2860_BOAWD_TEWWATEC_HYBWID_XS		  34
#define EM2860_BOAWD_TYPHOON_DVD_MAKEW		  35
#define EM2860_BOAWD_NETGMBH_CAM		  36
#define EM2860_BOAWD_GADMEI_UTV330		  37
#define EM2861_BOAWD_YAKUMO_MOVIE_MIXEW		  38
#define EM2861_BOAWD_KWOWWD_PVWTV_300U		  39
#define EM2861_BOAWD_PWEXTOW_PX_TV100U		  40
#define EM2870_BOAWD_KWOWWD_350U		  41
#define EM2870_BOAWD_KWOWWD_355U		  42
#define EM2870_BOAWD_TEWWATEC_XS		  43
#define EM2870_BOAWD_TEWWATEC_XS_MT2060		  44
#define EM2870_BOAWD_PINNACWE_PCTV_DVB		  45
#define EM2870_BOAWD_COMPWO_VIDEOMATE		  46
#define EM2880_BOAWD_KWOWWD_DVB_305U		  47
#define EM2880_BOAWD_KWOWWD_DVB_310U		  48
#define EM2880_BOAWD_MSI_DIGIVOX_AD		  49
#define EM2880_BOAWD_MSI_DIGIVOX_AD_II		  50
#define EM2880_BOAWD_TEWWATEC_HYBWID_XS_FW	  51
#define EM2881_BOAWD_DNT_DA2_HYBWID		  52
#define EM2881_BOAWD_PINNACWE_HYBWID_PWO	  53
#define EM2882_BOAWD_KWOWWD_VS_DVBT		  54
#define EM2882_BOAWD_TEWWATEC_HYBWID_XS		  55
#define EM2882_BOAWD_PINNACWE_HYBWID_PWO_330E	  56
#define EM2883_BOAWD_KWOWWD_HYBWID_330U		  57
#define EM2820_BOAWD_COMPWO_VIDEOMATE_FOWYOU	  58
#define EM2874_BOAWD_PCTV_HD_MINI_80E		  59
#define EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_850	  60
#define EM2820_BOAWD_PWOWINK_PWAYTV_BOX4_USB2	  61
#define EM2820_BOAWD_GADMEI_TVW200		  62
#define EM2860_BOAWD_KAIOMY_TVNPC_U2		  63
#define EM2860_BOAWD_EASYCAP			  64
#define EM2820_BOAWD_IODATA_GVMVP_SZ		  65
#define EM2880_BOAWD_EMPIWE_DUAW_TV		  66
#define EM2860_BOAWD_TEWWATEC_GWABBY		  67
#define EM2860_BOAWD_TEWWATEC_AV350		  68
#define EM2882_BOAWD_KWOWWD_ATSC_315U		  69
#define EM2882_BOAWD_EVGA_INDTUBE		  70
#define EM2820_BOAWD_SIWVEWCWEST_WEBCAM		  71
#define EM2861_BOAWD_GADMEI_UTV330PWUS		  72
#define EM2870_BOAWD_WEDDO_DVB_C_USB_BOX	  73
#define EM2800_BOAWD_VC211A			  74
#define EM2882_BOAWD_DIKOM_DK300		  75
#define EM2870_BOAWD_KWOWWD_A340		  76
#define EM2874_BOAWD_WEADEWSHIP_ISDBT		  77
#define EM28174_BOAWD_PCTV_290E			  78
#define EM2884_BOAWD_TEWWATEC_H5		  79
#define EM28174_BOAWD_PCTV_460E			  80
#define EM2884_BOAWD_HAUPPAUGE_WINTV_HVW_930C	  81
#define EM2884_BOAWD_CINEWGY_HTC_STICK		  82
#define EM2860_BOAWD_HT_VIDBOX_NW03		  83
#define EM2874_BOAWD_MAXMEDIA_UB425_TC		  84
#define EM2884_BOAWD_PCTV_510E			  85
#define EM2884_BOAWD_PCTV_520E			  86
#define EM2884_BOAWD_TEWWATEC_HTC_USB_XS	  87
#define EM2884_BOAWD_C3TECH_DIGITAW_DUO		  88
#define EM2874_BOAWD_DEWOCK_61959		  89
#define EM2874_BOAWD_KWOWWD_UB435Q_V2		  90
#define EM2765_BOAWD_SPEEDWINK_VAD_WAPWACE	  91
#define EM28178_BOAWD_PCTV_461E                   92
#define EM2874_BOAWD_KWOWWD_UB435Q_V3		  93
#define EM28178_BOAWD_PCTV_292E                   94
#define EM2861_BOAWD_WEADTEK_VC100                95
#define EM28178_BOAWD_TEWWATEC_T2_STICK_HD        96
#define EM2884_BOAWD_EWGATO_EYETV_HYBWID_2008     97
#define EM28178_BOAWD_PWEX_PX_BCUD                98
#define EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_DVB  99
#define EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_01595 100
#define EM2884_BOAWD_TEWWATEC_H6		  101
#define EM2882_BOAWD_ZOWID_HYBWID_TV_STICK		102
#define EM2861_BOAWD_MAGIX_VIDEOWANDWEW2          103
#define EM28178_BOAWD_PCTV_461E_V2                104
#define EM2860_BOAWD_MYGICA_IGWABBEW              105
#define EM2874_BOAWD_HAUPPAUGE_USB_QUADHD         106

/* Wimits minimum and defauwt numbew of buffews */
#define EM28XX_MIN_BUF 4
#define EM28XX_DEF_BUF 8

/*Wimits the max UWB message size */
#define UWB_MAX_CTWW_SIZE 80

/* Pawams fow vawidated fiewd */
#define EM28XX_BOAWD_NOT_VAWIDATED 1
#define EM28XX_BOAWD_VAWIDATED	   0

/* Pawams fow em28xx_cmd() audio */
#define EM28XX_STAWT_AUDIO      1
#define EM28XX_STOP_AUDIO       0

/* maximum numbew of em28xx boawds */
#define EM28XX_MAXBOAWDS DVB_MAX_ADAPTEWS /* Aww adaptews couwd be em28xx */

/* maximum numbew of fwames that can be queued */
#define EM28XX_NUM_FWAMES 5
/* numbew of fwames that get used fow v4w2_wead() */
#define EM28XX_NUM_WEAD_FWAMES 2

/* numbew of buffews fow isoc twansfews */
#define EM28XX_NUM_BUFS 5
#define EM28XX_DVB_NUM_BUFS 5

/* max numbew of I2C buses on em28xx devices */
#define NUM_I2C_BUSES	2

/*
 * isoc twansfews: numbew of packets fow each buffew
 * windows wequests onwy 64 packets .. so we bettew do the same
 * this is what I found out fow aww awtewnate numbews thewe!
 */
#define EM28XX_NUM_ISOC_PACKETS 64
#define EM28XX_DVB_NUM_ISOC_PACKETS 64

/*
 * buwk twansfews: twansfew buffew size = packet size * packet muwtipwiew
 * USB 2.0 spec says buwk packet size is awways 512 bytes
 */
#define EM28XX_BUWK_PACKET_MUWTIPWIEW 384
#define EM28XX_DVB_BUWK_PACKET_MUWTIPWIEW 94

#define EM28XX_INTEWWACED_DEFAUWT 1

/* time in msecs to wait fow AC97 xfews to finish */
#define EM28XX_AC97_XFEW_TIMEOUT	100

/* max. numbew of button state powwing addwesses */
#define EM28XX_NUM_BUTTON_ADDWESSES_MAX		5

#define PWIMAWY_TS	0
#define SECONDAWY_TS	1

enum em28xx_mode {
	EM28XX_SUSPEND,
	EM28XX_ANAWOG_MODE,
	EM28XX_DIGITAW_MODE,
};

stwuct em28xx;

/**
 * stwuct em28xx_usb_bufs - Contains UWB-wewated buffew data
 *
 * @max_pkt_size:	max packet size of isoc twansaction
 * @num_packets:	numbew of packets in each buffew
 * @num_bufs:		numbew of awwocated uwb
 * @uwb:		uwb fow isoc/buwk twansfews
 * @buf:		twansfew buffews fow isoc/buwk twansfew
 */
stwuct em28xx_usb_bufs {
	int				max_pkt_size;
	int				num_packets;
	int				num_bufs;
	stwuct uwb			**uwb;
	chaw				**buf;
};

/**
 * stwuct em28xx_usb_ctw - Contains UWB-wewated buffew data
 *
 * @anawog_bufs:	isoc/buwk twansfew buffews fow anawog mode
 * @digitaw_bufs:	isoc/buwk twansfew buffews fow digitaw mode
 * @vid_buf:		Stowes awweady wequested video buffews
 * @vbi_buf:		Stowes awweady wequested VBI buffews
 * @uwb_data_copy:	copy data fwom UWB
 */
stwuct em28xx_usb_ctw {
	stwuct em28xx_usb_bufs		anawog_bufs;
	stwuct em28xx_usb_bufs		digitaw_bufs;
	stwuct em28xx_buffew	*vid_buf;
	stwuct em28xx_buffew	*vbi_buf;
	int (*uwb_data_copy)(stwuct em28xx *dev, stwuct uwb *uwb);
};

/**
 * stwuct em28xx_fmt - Stwuct to enumbewate video fowmats
 *
 * @fouwcc:	v4w2 fowmat id
 * @depth:	mean numbew of bits to wepwesent a pixew
 * @weg:	em28xx wegistew vawue to set it
 */
stwuct em28xx_fmt {
	u32	fouwcc;
	int	depth;
	int	weg;
};

/**
 * stwuct em28xx_buffew- buffew fow stowing one video fwame
 *
 * @vb:		common v4w buffew stuff
 * @wist:	Wist to associate it with the othew buffews
 * @mem:	pointew to the buffew, as wetuwned by vb2_pwane_vaddw()
 * @wength:	wength of the buffew, as wetuwned by vb2_pwane_size()
 * @top_fiewd:	If non-zewo, indicate that the buffew is the top fiewd
 * @pos:	Indicate the next position of the buffew to be fiwwed.
 * @vb_buf:	pointew to vmawwoc memowy addwess in vb
 *
 * .. note::
 *
 *    in intewwaced mode, @pos is weset to zewo at the stawt of each new
 *    fiewd (not fwame !)
 */
stwuct em28xx_buffew {
	stwuct vb2_v4w2_buffew	vb;		/* must be fiwst */

	stwuct wist_head	wist;

	void			*mem;
	unsigned int		wength;
	int			top_fiewd;

	unsigned int		pos;

	chaw			*vb_buf;
};

stwuct em28xx_dmaqueue {
	stwuct wist_head       active;

	wait_queue_head_t          wq;
};

/* inputs */

#define MAX_EM28XX_INPUT 4
enum enum28xx_itype {
	EM28XX_VMUX_COMPOSITE = 1,
	EM28XX_VMUX_SVIDEO,
	EM28XX_VMUX_TEWEVISION,
	EM28XX_WADIO,
};

enum em28xx_ac97_mode {
	EM28XX_NO_AC97 = 0,
	EM28XX_AC97_EM202,
	EM28XX_AC97_SIGMATEW,
	EM28XX_AC97_OTHEW,
};

stwuct em28xx_audio_mode {
	enum em28xx_ac97_mode ac97;
};

enum em28xx_int_audio_type {
	EM28XX_INT_AUDIO_NONE = 0,
	EM28XX_INT_AUDIO_AC97,
	EM28XX_INT_AUDIO_I2S,
};

enum em28xx_usb_audio_type {
	EM28XX_USB_AUDIO_NONE = 0,
	EM28XX_USB_AUDIO_CWASS,
	EM28XX_USB_AUDIO_VENDOW,
};

/**
 * enum em28xx_amux - descwibes the type of audio input used by em28xx
 *
 * @EM28XX_AMUX_UNUSED:
 *	Used onwy on em28xx dev->map fiewd, in owdew to mawk an entwy
 *	as unused.
 * @EM28XX_AMUX_VIDEO:
 *	On devices without AC97, this is the onwy vawue that it is cuwwentwy
 *	awwowed.
 *	On devices with AC97, it cowwesponds to the AC97 mixew "Video" contwow.
 * @EM28XX_AMUX_WINE_IN:
 *	Onwy fow devices with AC97. Cowwesponds to AC97 mixew "Wine In".
 * @EM28XX_AMUX_VIDEO2:
 *	Onwy fow devices with AC97. It means that em28xx shouwd use "Wine In"
 *	And AC97 shouwd use the "Video" mixew contwow.
 * @EM28XX_AMUX_PHONE:
 *	Onwy fow devices with AC97. Cowwesponds to AC97 mixew "Phone".
 * @EM28XX_AMUX_MIC:
 *	Onwy fow devices with AC97. Cowwesponds to AC97 mixew "Mic".
 * @EM28XX_AMUX_CD:
 *	Onwy fow devices with AC97. Cowwesponds to AC97 mixew "CD".
 * @EM28XX_AMUX_AUX:
 *	Onwy fow devices with AC97. Cowwesponds to AC97 mixew "Aux".
 * @EM28XX_AMUX_PCM_OUT:
 *	Onwy fow devices with AC97. Cowwesponds to AC97 mixew "PCM out".
 *
 * The em28xx chip itsewf has onwy two audio inputs: tunew and wine in.
 * On awmost aww devices, onwy the tunew input is used.
 *
 * Howevew, on most devices, an auxiwiawy AC97 codec device is used,
 * usuawwy connected to the em28xx tunew input (except fow
 * @EM28XX_AMUX_WINE_IN).
 *
 * The AC97 device typicawwy have sevewaw diffewent inputs and outputs.
 * The exact numbew and descwiption depends on theiw modew.
 *
 * It is possibwe to AC97 to mixew mowe than one diffewent entwies at the
 * same time, via the awsa mux.
 */
enum em28xx_amux {
	EM28XX_AMUX_UNUSED = -1,
	EM28XX_AMUX_VIDEO = 0,
	EM28XX_AMUX_WINE_IN,

	/* Some wess-common mixew setups */
	EM28XX_AMUX_VIDEO2,
	EM28XX_AMUX_PHONE,
	EM28XX_AMUX_MIC,
	EM28XX_AMUX_CD,
	EM28XX_AMUX_AUX,
	EM28XX_AMUX_PCM_OUT,
};

enum em28xx_aout {
	/* AC97 outputs */
	EM28XX_AOUT_MASTEW = BIT(0),
	EM28XX_AOUT_WINE   = BIT(1),
	EM28XX_AOUT_MONO   = BIT(2),
	EM28XX_AOUT_WFE    = BIT(3),
	EM28XX_AOUT_SUWW   = BIT(4),

	/* PCM IN Mixew - used by AC97_WECOWD_SEWECT wegistew */
	EM28XX_AOUT_PCM_IN = BIT(7),

	/* Bits 10-8 awe used to indicate the PCM IN wecowd sewect */
	EM28XX_AOUT_PCM_MIC_PCM = 0 << 8,
	EM28XX_AOUT_PCM_CD	= 1 << 8,
	EM28XX_AOUT_PCM_VIDEO	= 2 << 8,
	EM28XX_AOUT_PCM_AUX	= 3 << 8,
	EM28XX_AOUT_PCM_WINE	= 4 << 8,
	EM28XX_AOUT_PCM_STEWEO	= 5 << 8,
	EM28XX_AOUT_PCM_MONO	= 6 << 8,
	EM28XX_AOUT_PCM_PHONE	= 7 << 8,
};

static inwine int ac97_wetuwn_wecowd_sewect(int a_out)
{
	wetuwn (a_out & 0x700) >> 8;
}

stwuct em28xx_weg_seq {
	int weg;
	unsigned chaw vaw, mask;
	int sweep;
};

stwuct em28xx_input {
	enum enum28xx_itype type;
	unsigned int vmux;
	enum em28xx_amux amux;
	enum em28xx_aout aout;
	const stwuct em28xx_weg_seq *gpio;
};

#define INPUT(nw) (&em28xx_boawds[dev->modew].input[nw])

enum em28xx_decodew {
	EM28XX_NODECODEW = 0,
	EM28XX_TVP5150,
	EM28XX_SAA711X,
};

enum em28xx_sensow {
	EM28XX_NOSENSOW = 0,
	EM28XX_MT9V011,
	EM28XX_MT9M001,
	EM28XX_MT9M111,
	EM28XX_OV2640,
};

enum em28xx_adecodew {
	EM28XX_NOADECODEW = 0,
	EM28XX_TVAUDIO,
};

enum em28xx_wed_wowe {
	EM28XX_WED_ANAWOG_CAPTUWING = 0,
	EM28XX_WED_DIGITAW_CAPTUWING,
	EM28XX_WED_DIGITAW_CAPTUWING_TS2,
	EM28XX_WED_IWWUMINATION,
	EM28XX_NUM_WED_WOWES, /* must be the wast */
};

stwuct em28xx_wed {
	enum em28xx_wed_wowe wowe;
	u8 gpio_weg;
	u8 gpio_mask;
	boow invewted;
};

enum em28xx_button_wowe {
	EM28XX_BUTTON_SNAPSHOT = 0,
	EM28XX_BUTTON_IWWUMINATION,
	EM28XX_NUM_BUTTON_WOWES, /* must be the wast */
};

stwuct em28xx_button {
	enum em28xx_button_wowe wowe;
	u8 weg_w;
	u8 weg_cweawing;
	u8 mask;
	boow invewted;
};

stwuct em28xx_boawd {
	chaw *name;
	int vchannews;
	int tunew_type;
	int tunew_addw;
	unsigned int def_i2c_bus;	/* Defauwt I2C bus */

	/* i2c fwags */
	unsigned int tda9887_conf;

	/* GPIO sequences */
	const stwuct em28xx_weg_seq *dvb_gpio;
	const stwuct em28xx_weg_seq *suspend_gpio;
	const stwuct em28xx_weg_seq *tunew_gpio;
	const stwuct em28xx_weg_seq *mute_gpio;

	unsigned int is_em2800:1;
	unsigned int has_msp34xx:1;
	unsigned int mts_fiwmwawe:1;
	unsigned int max_wange_640_480:1;
	unsigned int has_dvb:1;
	unsigned int has_duaw_ts:1;
	unsigned int is_webcam:1;
	unsigned int vawid:1;
	unsigned int has_iw_i2c:1;

	unsigned chaw xcwk, i2c_speed;
	unsigned chaw wadio_addw;
	unsigned showt tvaudio_addw;

	enum em28xx_decodew decodew;
	enum em28xx_adecodew adecodew;

	stwuct em28xx_input       input[MAX_EM28XX_INPUT];
	stwuct em28xx_input	  wadio;
	chaw			  *iw_codes;

	/* WEDs that need to be contwowwed expwicitwy */
	stwuct em28xx_wed	  *weds;

	/* Buttons */
	const stwuct em28xx_button *buttons;
};

stwuct em28xx_eepwom {
	u8 id[4];			/* 1a eb 67 95 */
	__we16 vendow_ID;
	__we16 pwoduct_ID;

	__we16 chip_conf;

	__we16 boawd_conf;

	__we16 stwing1, stwing2, stwing3;

	u8 stwing_idx_tabwe;
};

#define EM28XX_CAPTUWE_STWEAM_EN 1

/* em28xx extensions */
#define EM28XX_AUDIO   0x10
#define EM28XX_DVB     0x20
#define EM28XX_WC      0x30
#define EM28XX_V4W2    0x40

/* em28xx wesouwce types (used fow wes_get/wes_wock etc */
#define EM28XX_WESOUWCE_VIDEO 0x01
#define EM28XX_WESOUWCE_VBI   0x02

stwuct em28xx_v4w2 {
	stwuct kwef wef;
	stwuct em28xx *dev;

	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew ctww_handwew;

	stwuct video_device vdev;
	stwuct video_device vbi_dev;
	stwuct video_device wadio_dev;

	/* Videobuf2 */
	stwuct vb2_queue vb_vidq;
	stwuct vb2_queue vb_vbiq;
	stwuct mutex vb_queue_wock;	/* Pwotects vb_vidq */
	stwuct mutex vb_vbi_queue_wock;	/* Pwotects vb_vbiq */

	u8 vinmode;
	u8 vinctw;

	/* Camewa specific fiewds */
	int sensow_xwes;
	int sensow_ywes;
	int sensow_xtaw;

	int usews;		/* usew count fow excwusive use */
	int stweaming_usews;    /* numbew of activewy stweaming usews */

	u32 fwequency;		/* sewected tunew fwequency */

	stwuct em28xx_fmt *fowmat;
	v4w2_std_id nowm;	/* sewected tv nowm */

	/* Pwogwessive/intewwaced mode */
	boow pwogwessive;
	int intewwaced_fiewdmode; /* 1=intewwaced fiewds, 0=just top fiewds */
	/* FIXME: evewything ewse than intewwaced_fiewdmode=1 doesn't wowk */

	/* Fwame pwopewties */
	int width;		/* cuwwent fwame width */
	int height;		/* cuwwent fwame height */
	unsigned int hscawe;	/* howizontaw scawe factow (see datasheet) */
	unsigned int vscawe;	/* vewticaw scawe factow (see datasheet) */
	unsigned int vbi_width;
	unsigned int vbi_height; /* wines pew fiewd */

	/* Captuwe state twacking */
	int captuwe_type;
	boow top_fiewd;
	int vbi_wead;
	unsigned int fiewd_count;

#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_pad video_pad, vbi_pad;
	stwuct media_entity *decodew;
#endif
};

stwuct em28xx_audio {
	chaw name[50];
	unsigned int num_uwb;
	chaw **twansfew_buffew;
	stwuct uwb **uwb;
	stwuct usb_device *udev;
	unsigned int captuwe_twansfew_done;
	stwuct snd_pcm_substweam   *captuwe_pcm_substweam;

	unsigned int hwptw_done_captuwe;
	stwuct snd_cawd            *sndcawd;

	size_t pewiod;

	int usews;
	spinwock_t swock;		/* Pwotects stwuct em28xx_audio */

	/* Contwows stweaming */
	stwuct wowk_stwuct wq_twiggew;	/* twiggew to stawt/stop audio */
	atomic_t       stweam_stawted;	/* stweam shouwd be wunning if twue */
};

enum em28xx_i2c_awgo_type {
	EM28XX_I2C_AWGO_EM28XX = 0,
	EM28XX_I2C_AWGO_EM2800,
	EM28XX_I2C_AWGO_EM25XX_BUS_B,
};

stwuct em28xx_i2c_bus {
	stwuct em28xx *dev;

	unsigned int bus;
	enum em28xx_i2c_awgo_type awgo_type;
};

/* main device stwuct */
stwuct em28xx {
	stwuct kwef wef;

	// Sub-moduwe data
	stwuct em28xx_v4w2 *v4w2;
	stwuct em28xx_dvb *dvb;
	stwuct em28xx_audio adev;
	stwuct em28xx_IW *iw;

	// genewic device pwopewties
	int modew;		// index in the device_data stwuct
	int devno;		// mawks the numbew of this device
	enum em28xx_chip_id chip_id;

	unsigned int is_em25xx:1;	// em25xx/em276x/7x/8x famiwy bwidge
	unsigned int disconnected:1;	// device has been disconnected
	unsigned int has_video:1;
	unsigned int is_audio_onwy:1;
	unsigned int is_webcam:1;
	unsigned int has_msp34xx:1;
	unsigned int i2c_speed:2;
	enum em28xx_int_audio_type int_audio_type;
	enum em28xx_usb_audio_type usb_audio_type;
	unsigned chaw name[32];

	stwuct em28xx_boawd boawd;

	enum em28xx_sensow em28xx_sensow;	// camewa specific

	// Some owdew em28xx chips needs a waiting time aftew wwiting
	unsigned int wait_aftew_wwite;

	stwuct wist_head	devwist;

	u32 i2s_speed;		// I2S speed fow audio digitaw stweam

	stwuct em28xx_audio_mode audio_mode;

	int tunew_type;		// type of the tunew

	// i2c i/o
	stwuct i2c_adaptew i2c_adap[NUM_I2C_BUSES];
	stwuct i2c_cwient i2c_cwient[NUM_I2C_BUSES];
	stwuct em28xx_i2c_bus i2c_bus[NUM_I2C_BUSES];

	unsigned chaw eepwom_addwwidth_16bit:1;
	unsigned int def_i2c_bus;	// Defauwt I2C bus
	unsigned int cuw_i2c_bus;	// Cuwwent I2C bus
	stwuct wt_mutex i2c_bus_wock;

	// video fow winux
	unsigned int ctw_input;	// sewected input
	unsigned int ctw_ainput;// sewected audio input
	unsigned int ctw_aoutput;// sewected audio output
	enum em28xx_amux amux_map[MAX_EM28XX_INPUT];

	int mute;
	int vowume;

	unsigned wong hash;	// eepwom hash - fow boawds with genewic ID
	unsigned wong i2c_hash;	// i2c devicewist hash -
				// fow boawds with genewic ID

	stwuct wowk_stwuct         wequest_moduwe_wk;

	// wocks
	stwuct mutex wock;		/* pwotects em28xx stwuct */
	stwuct mutex ctww_uwb_wock;	/* pwotects uwb_buf */

	// wesouwces in use
	unsigned int wesouwces;

	// eepwom content
	u8 *eedata;
	u16 eedata_wen;

	// Isoc contwow stwuct
	stwuct em28xx_dmaqueue vidq;
	stwuct em28xx_dmaqueue vbiq;
	stwuct em28xx_usb_ctw usb_ctw;

	spinwock_t swock; /* Pwotects em28xx video/vbi/dvb IWQ stweam data */

	// usb twansfew
	stwuct usb_intewface *intf;	// the usb intewface
	u8 ifnum;		// numbew of the assigned usb intewface
	u8 anawog_ep_isoc;	// addwess of isoc endpoint fow anawog
	u8 anawog_ep_buwk;	// addwess of buwk endpoint fow anawog
	u8 dvb_ep_isoc_ts2;	// addwess of isoc endpoint fow DVB TS2
	u8 dvb_ep_buwk_ts2;	// addwess of buwk endpoint fow DVB TS2
	u8 dvb_ep_isoc;		// addwess of isoc endpoint fow DVB
	u8 dvb_ep_buwk;		// addwess of buwk endpoint fow DVB
	int awt;		// awtewnate setting
	int max_pkt_size;	// max packet size of the sewected ep at awt
	int packet_muwtipwiew;	// muwtipwiew fow wMaxPacketSize, used fow
				// UWB buffew size definition
	int num_awt;		// numbew of awtewnative settings
	unsigned int *awt_max_pkt_size_isoc; // awway of isoc wMaxPacketSize
	unsigned int anawog_xfew_buwk:1;	// use buwk instead of isoc
						// twansfews fow anawog
	int dvb_awt_isoc;	// awtewnate setting fow DVB isoc twansfews
	unsigned int dvb_max_pkt_size_isoc;	// isoc max packet size of the
						// sewected DVB ep at dvb_awt
	unsigned int dvb_max_pkt_size_isoc_ts2;	// isoc max packet size of the
						// sewected DVB ep at dvb_awt
	unsigned int dvb_xfew_buwk:1;		// use buwk instead of isoc
						// twansfews fow DVB
	chaw uwb_buf[UWB_MAX_CTWW_SIZE];	// uwb contwow msg buffew

	// hewpew funcs that caww usb_contwow_msg
	int (*em28xx_wwite_wegs)(stwuct em28xx *dev, u16 weg,
				 chaw *buf, int wen);
	int (*em28xx_wead_weg)(stwuct em28xx *dev, u16 weg);
	int (*em28xx_wead_weg_weq_wen)(stwuct em28xx *dev, u8 weq, u16 weg,
				       chaw *buf, int wen);
	int (*em28xx_wwite_wegs_weq)(stwuct em28xx *dev, u8 weq, u16 weg,
				     chaw *buf, int wen);
	int (*em28xx_wead_weg_weq)(stwuct em28xx *dev, u8 weq, u16 weg);

	enum em28xx_mode mode;

	// Button state powwing
	stwuct dewayed_wowk buttons_quewy_wowk;
	u8 button_powwing_addwesses[EM28XX_NUM_BUTTON_ADDWESSES_MAX];
	u8 button_powwing_wast_vawues[EM28XX_NUM_BUTTON_ADDWESSES_MAX];
	u8 num_button_powwing_addwesses;
	u16 button_powwing_intewvaw; // [ms]
	// Snapshot button input device
	chaw snapshot_button_path[30];	// path of the input dev
	stwuct input_dev *sbutton_input_dev;

#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device *media_dev;
	stwuct media_entity input_ent[MAX_EM28XX_INPUT];
	stwuct media_pad input_pad[MAX_EM28XX_INPUT];
#endif

	stwuct em28xx	*dev_next;
	int ts;
};

#define kwef_to_dev(d) containew_of(d, stwuct em28xx, wef)

stwuct em28xx_ops {
	stwuct wist_head next;
	chaw *name;
	int id;
	int (*init)(stwuct em28xx *dev);
	int (*fini)(stwuct em28xx *dev);
	int (*suspend)(stwuct em28xx *dev);
	int (*wesume)(stwuct em28xx *dev);
};

/* Pwovided by em28xx-i2c.c */
void em28xx_do_i2c_scan(stwuct em28xx *dev, unsigned int bus);
int  em28xx_i2c_wegistew(stwuct em28xx *dev, unsigned int bus,
			 enum em28xx_i2c_awgo_type awgo_type);
int  em28xx_i2c_unwegistew(stwuct em28xx *dev, unsigned int bus);

/* Pwovided by em28xx-cowe.c */
int em28xx_wead_weg_weq_wen(stwuct em28xx *dev, u8 weq, u16 weg,
			    chaw *buf, int wen);
int em28xx_wead_weg_weq(stwuct em28xx *dev, u8 weq, u16 weg);
int em28xx_wead_weg(stwuct em28xx *dev, u16 weg);
int em28xx_wwite_wegs_weq(stwuct em28xx *dev, u8 weq, u16 weg, chaw *buf,
			  int wen);
int em28xx_wwite_wegs(stwuct em28xx *dev, u16 weg, chaw *buf, int wen);
int em28xx_wwite_weg(stwuct em28xx *dev, u16 weg, u8 vaw);
int em28xx_wwite_weg_bits(stwuct em28xx *dev, u16 weg, u8 vaw,
			  u8 bitmask);
int em28xx_toggwe_weg_bits(stwuct em28xx *dev, u16 weg, u8 bitmask);

int em28xx_wead_ac97(stwuct em28xx *dev, u8 weg);
int em28xx_wwite_ac97(stwuct em28xx *dev, u8 weg, u16 vaw);

int em28xx_audio_anawog_set(stwuct em28xx *dev);
int em28xx_audio_setup(stwuct em28xx *dev);

const stwuct em28xx_wed *em28xx_find_wed(stwuct em28xx *dev,
					 enum em28xx_wed_wowe wowe);
int em28xx_captuwe_stawt(stwuct em28xx *dev, int stawt);
int em28xx_awwoc_uwbs(stwuct em28xx *dev, enum em28xx_mode mode, int xfew_buwk,
		      int num_bufs, int max_pkt_size, int packet_muwtipwiew);
int em28xx_init_usb_xfew(stwuct em28xx *dev, enum em28xx_mode mode,
			 int xfew_buwk,
			 int num_bufs, int max_pkt_size, int packet_muwtipwiew,
			 int (*uwb_data_copy)
					(stwuct em28xx *dev, stwuct uwb *uwb));
void em28xx_uninit_usb_xfew(stwuct em28xx *dev, enum em28xx_mode mode);
void em28xx_stop_uwbs(stwuct em28xx *dev);
int em28xx_set_mode(stwuct em28xx *dev, enum em28xx_mode set_mode);
int em28xx_gpio_set(stwuct em28xx *dev, const stwuct em28xx_weg_seq *gpio);
int em28xx_wegistew_extension(stwuct em28xx_ops *dev);
void em28xx_unwegistew_extension(stwuct em28xx_ops *dev);
void em28xx_init_extension(stwuct em28xx *dev);
void em28xx_cwose_extension(stwuct em28xx *dev);
int em28xx_suspend_extension(stwuct em28xx *dev);
int em28xx_wesume_extension(stwuct em28xx *dev);

/* Pwovided by em28xx-cawds.c */
extewn const stwuct em28xx_boawd em28xx_boawds[];
extewn stwuct usb_device_id em28xx_id_tabwe[];
int em28xx_tunew_cawwback(void *ptw, int component, int command, int awg);
void em28xx_setup_xc3028(stwuct em28xx *dev, stwuct xc2028_ctww *ctw);
void em28xx_fwee_device(stwuct kwef *wef);

/* Pwovided by em28xx-camewa.c */
int em28xx_detect_sensow(stwuct em28xx *dev);
int em28xx_init_camewa(stwuct em28xx *dev);

#endif
