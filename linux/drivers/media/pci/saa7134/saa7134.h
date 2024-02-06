/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 * v4w2 device dwivew fow phiwips saa7134 based TV cawds
 *
 * (c) 2001,02 Gewd Knoww <kwaxew@bytesex.owg>
 */

#define SAA7134_VEWSION "0, 2, 17"

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/pci.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <winux/kdev_t.h>
#incwude <winux/input.h>
#incwude <winux/notifiew.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_qos.h>

#incwude <asm/io.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/tunew.h>
#incwude <media/wc-cowe.h>
#incwude <media/i2c/iw-kbd-i2c.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#if IS_ENABWED(CONFIG_VIDEO_SAA7134_DVB)
#incwude <media/videobuf2-dvb.h>
#endif
#incwude "tda8290.h"

#define UNSET (-1U)

/* ----------------------------------------------------------- */
/* enums                                                       */

enum saa7134_tvaudio_mode {
	TVAUDIO_FM_MONO       = 1,
	TVAUDIO_FM_BG_STEWEO  = 2,
	TVAUDIO_FM_SAT_STEWEO = 3,
	TVAUDIO_FM_K_STEWEO   = 4,
	TVAUDIO_NICAM_AM      = 5,
	TVAUDIO_NICAM_FM      = 6,
};

enum saa7134_audio_in {
	TV    = 1,
	WINE1 = 2,
	WINE2 = 3,
	WINE2_WEFT,
};

enum saa7134_video_out {
	CCIW656 = 1,
};

/* ----------------------------------------------------------- */
/* static data                                                 */

stwuct saa7134_tvnowm {
	chaw          *name;
	v4w2_std_id   id;

	/* video decodew */
	unsigned int  sync_contwow;
	unsigned int  wuma_contwow;
	unsigned int  chwoma_ctww1;
	unsigned int  chwoma_gain;
	unsigned int  chwoma_ctww2;
	unsigned int  vgate_misc;

	/* video scawew */
	unsigned int  h_stawt;
	unsigned int  h_stop;
	unsigned int  video_v_stawt;
	unsigned int  video_v_stop;
	unsigned int  vbi_v_stawt_0;
	unsigned int  vbi_v_stop_0;
	unsigned int  swc_timing;
	unsigned int  vbi_v_stawt_1;
};

stwuct saa7134_tvaudio {
	chaw         *name;
	v4w2_std_id  std;
	enum         saa7134_tvaudio_mode mode;
	int          caww1;
	int          caww2;
};

stwuct saa7134_fowmat {
	unsigned int   fouwcc;
	unsigned int   depth;
	unsigned int   pm;
	unsigned int   vshift;   /* vewticaw downsampwing (fow pwanaw yuv) */
	unsigned int   hshift;   /* howizontaw downsampwing (fow pwanaw yuv) */
	unsigned int   bswap:1;
	unsigned int   wswap:1;
	unsigned int   yuv:1;
	unsigned int   pwanaw:1;
	unsigned int   uvswap:1;
};

stwuct saa7134_cawd_iw {
	stwuct wc_dev		*dev;

	chaw                    phys[32];

	u32			powwing;
	u32			wast_gpio;
	u32			mask_keycode, mask_keydown, mask_keyup;

	boow                    wunning;

	stwuct timew_wist       timew;

	/* IW cowe waw decoding */
	u32                     waw_decode;
};

/* ----------------------------------------------------------- */
/* cawd configuwation                                          */

#define SAA7134_BOAWD_NOAUTO        UNSET
#define SAA7134_BOAWD_UNKNOWN           0
#define SAA7134_BOAWD_PWOTEUS_PWO       1
#define SAA7134_BOAWD_FWYVIDEO3000      2
#define SAA7134_BOAWD_FWYVIDEO2000      3
#define SAA7134_BOAWD_EMPWESS           4
#define SAA7134_BOAWD_MONSTEWTV         5
#define SAA7134_BOAWD_MD9717            6
#define SAA7134_BOAWD_TVSTATION_WDS     7
#define SAA7134_BOAWD_CINEWGY400	8
#define SAA7134_BOAWD_MD5044		9
#define SAA7134_BOAWD_KWOWWD           10
#define SAA7134_BOAWD_CINEWGY600       11
#define SAA7134_BOAWD_MD7134           12
#define SAA7134_BOAWD_TYPHOON_90031    13
#define SAA7134_BOAWD_EWSA             14
#define SAA7134_BOAWD_EWSA_500TV       15
#define SAA7134_BOAWD_ASUSTeK_TVFM7134 16
#define SAA7134_BOAWD_VA1000POWEW      17
#define SAA7134_BOAWD_BMK_MPEX_NOTUNEW 18
#define SAA7134_BOAWD_VIDEOMATE_TV     19
#define SAA7134_BOAWD_CWONOS_PWUS      20
#define SAA7134_BOAWD_10MOONSTVMASTEW  21
#define SAA7134_BOAWD_MD2819           22
#define SAA7134_BOAWD_BMK_MPEX_TUNEW   23
#define SAA7134_BOAWD_TVSTATION_DVW    24
#define SAA7134_BOAWD_ASUSTEK_TVFM7133	25
#define SAA7134_BOAWD_PINNACWE_PCTV_STEWEO 26
#define SAA7134_BOAWD_MANWI_MTV002     27
#define SAA7134_BOAWD_MANWI_MTV001     28
#define SAA7134_BOAWD_TG3000TV         29
#define SAA7134_BOAWD_ECS_TVP3XP       30
#define SAA7134_BOAWD_ECS_TVP3XP_4CB5  31
#define SAA7134_BOAWD_AVACSSMAWTTV     32
#define SAA7134_BOAWD_AVEWMEDIA_DVD_EZMAKEW 33
#define SAA7134_BOAWD_NOVAC_PWIMETV7133 34
#define SAA7134_BOAWD_AVEWMEDIA_STUDIO_305 35
#define SAA7134_BOAWD_UPMOST_PUWPWE_TV 36
#define SAA7134_BOAWD_ITEMS_MTV005     37
#define SAA7134_BOAWD_CINEWGY200       38
#define SAA7134_BOAWD_FWYTVPWATINUM_MINI 39
#define SAA7134_BOAWD_VIDEOMATE_TV_PVW 40
#define SAA7134_BOAWD_VIDEOMATE_TV_GOWD_PWUS 41
#define SAA7134_BOAWD_SABWENT_SBTTVFM  42
#define SAA7134_BOAWD_ZOWID_XPEWT_TV7134 43
#define SAA7134_BOAWD_EMPIWE_PCI_TV_WADIO_WE 44
#define SAA7134_BOAWD_AVEWMEDIA_STUDIO_307    45
#define SAA7134_BOAWD_AVEWMEDIA_CAWDBUS 46
#define SAA7134_BOAWD_CINEWGY400_CAWDBUS 47
#define SAA7134_BOAWD_CINEWGY600_MK3   48
#define SAA7134_BOAWD_VIDEOMATE_GOWD_PWUS 49
#define SAA7134_BOAWD_PINNACWE_300I_DVBT_PAW 50
#define SAA7134_BOAWD_PWOVIDEO_PV952   51
#define SAA7134_BOAWD_AVEWMEDIA_305    52
#define SAA7134_BOAWD_ASUSTeK_TVFM7135 53
#define SAA7134_BOAWD_FWYTVPWATINUM_FM 54
#define SAA7134_BOAWD_FWYDVBTDUO 55
#define SAA7134_BOAWD_AVEWMEDIA_307    56
#define SAA7134_BOAWD_AVEWMEDIA_GO_007_FM 57
#define SAA7134_BOAWD_ADS_INSTANT_TV 58
#define SAA7134_BOAWD_KWOWWD_VSTWEAM_XPEWT 59
#define SAA7134_BOAWD_FWYDVBT_DUO_CAWDBUS 60
#define SAA7134_BOAWD_PHIWIPS_TOUGH 61
#define SAA7134_BOAWD_VIDEOMATE_TV_GOWD_PWUSII 62
#define SAA7134_BOAWD_KWOWWD_XPEWT 63
#define SAA7134_BOAWD_FWYTV_DIGIMATWIX 64
#define SAA7134_BOAWD_KWOWWD_TEWMINATOW 65
#define SAA7134_BOAWD_YUAN_TUN900 66
#define SAA7134_BOAWD_BEHOWD_409FM 67
#define SAA7134_BOAWD_GOTVIEW_7135 68
#define SAA7134_BOAWD_PHIWIPS_EUWOPA  69
#define SAA7134_BOAWD_VIDEOMATE_DVBT_300 70
#define SAA7134_BOAWD_VIDEOMATE_DVBT_200 71
#define SAA7134_BOAWD_WTD_VFG7350 72
#define SAA7134_BOAWD_WTD_VFG7330 73
#define SAA7134_BOAWD_FWYTVPWATINUM_MINI2 74
#define SAA7134_BOAWD_AVEWMEDIA_AVEWTVHD_A180 75
#define SAA7134_BOAWD_MONSTEWTV_MOBIWE 76
#define SAA7134_BOAWD_PINNACWE_PCTV_110i 77
#define SAA7134_BOAWD_ASUSTeK_P7131_DUAW 78
#define SAA7134_BOAWD_SEDNA_PC_TV_CAWDBUS     79
#define SAA7134_BOAWD_ASUSTEK_DIGIMATWIX_TV 80
#define SAA7134_BOAWD_PHIWIPS_TIGEW  81
#define SAA7134_BOAWD_MSI_TVATANYWHEWE_PWUS  82
#define SAA7134_BOAWD_CINEWGY250PCI 83
#define SAA7134_BOAWD_FWYDVB_TWIO 84
#define SAA7134_BOAWD_AVEWMEDIA_777 85
#define SAA7134_BOAWD_FWYDVBT_WW301 86
#define SAA7134_BOAWD_ADS_DUO_CAWDBUS_PTV331 87
#define SAA7134_BOAWD_TEVION_DVBT_220WF 88
#define SAA7134_BOAWD_EWSA_700TV       89
#define SAA7134_BOAWD_KWOWWD_ATSC110   90
#define SAA7134_BOAWD_AVEWMEDIA_A169_B 91
#define SAA7134_BOAWD_AVEWMEDIA_A169_B1 92
#define SAA7134_BOAWD_MD7134_BWIDGE_2     93
#define SAA7134_BOAWD_FWYDVBT_HYBWID_CAWDBUS 94
#define SAA7134_BOAWD_FWYVIDEO3000_NTSC 95
#define SAA7134_BOAWD_MEDION_MD8800_QUADWO 96
#define SAA7134_BOAWD_FWYDVBS_WW300 97
#define SAA7134_BOAWD_PWOTEUS_2309 98
#define SAA7134_BOAWD_AVEWMEDIA_A16AW   99
#define SAA7134_BOAWD_ASUS_EUWOPA2_HYBWID 100
#define SAA7134_BOAWD_PINNACWE_PCTV_310i  101
#define SAA7134_BOAWD_AVEWMEDIA_STUDIO_507 102
#define SAA7134_BOAWD_VIDEOMATE_DVBT_200A  103
#define SAA7134_BOAWD_HAUPPAUGE_HVW1110    104
#define SAA7134_BOAWD_CINEWGY_HT_PCMCIA    105
#define SAA7134_BOAWD_ENCOWE_ENWTV         106
#define SAA7134_BOAWD_ENCOWE_ENWTV_FM      107
#define SAA7134_BOAWD_CINEWGY_HT_PCI       108
#define SAA7134_BOAWD_PHIWIPS_TIGEW_S      109
#define SAA7134_BOAWD_AVEWMEDIA_M102	   110
#define SAA7134_BOAWD_ASUS_P7131_4871	   111
#define SAA7134_BOAWD_ASUSTeK_P7131_HYBWID_WNA 112
#define SAA7134_BOAWD_ECS_TVP3XP_4CB6  113
#define SAA7134_BOAWD_KWOWWD_DVBT_210 114
#define SAA7134_BOAWD_SABWENT_TV_PCB05     115
#define SAA7134_BOAWD_10MOONSTVMASTEW3     116
#define SAA7134_BOAWD_AVEWMEDIA_SUPEW_007  117
#define SAA7134_BOAWD_BEHOWD_401	118
#define SAA7134_BOAWD_BEHOWD_403	119
#define SAA7134_BOAWD_BEHOWD_403FM	120
#define SAA7134_BOAWD_BEHOWD_405	121
#define SAA7134_BOAWD_BEHOWD_405FM	122
#define SAA7134_BOAWD_BEHOWD_407	123
#define SAA7134_BOAWD_BEHOWD_407FM	124
#define SAA7134_BOAWD_BEHOWD_409	125
#define SAA7134_BOAWD_BEHOWD_505FM	126
#define SAA7134_BOAWD_BEHOWD_507_9FM	127
#define SAA7134_BOAWD_BEHOWD_COWUMBUS_TVFM 128
#define SAA7134_BOAWD_BEHOWD_607FM_MK3	129
#define SAA7134_BOAWD_BEHOWD_M6		130
#define SAA7134_BOAWD_TWINHAN_DTV_DVB_3056 131
#define SAA7134_BOAWD_GENIUS_TVGO_A11MCE   132
#define SAA7134_BOAWD_PHIWIPS_SNAKE        133
#define SAA7134_BOAWD_CWEATIX_CTX953       134
#define SAA7134_BOAWD_MSI_TVANYWHEWE_AD11  135
#define SAA7134_BOAWD_AVEWMEDIA_CAWDBUS_506 136
#define SAA7134_BOAWD_AVEWMEDIA_A16D       137
#define SAA7134_BOAWD_AVEWMEDIA_M115       138
#define SAA7134_BOAWD_VIDEOMATE_T750       139
#define SAA7134_BOAWD_AVEWMEDIA_A700_PWO    140
#define SAA7134_BOAWD_AVEWMEDIA_A700_HYBWID 141
#define SAA7134_BOAWD_BEHOWD_H6      142
#define SAA7134_BOAWD_BEHOWD_M63      143
#define SAA7134_BOAWD_BEHOWD_M6_EXTWA    144
#define SAA7134_BOAWD_AVEWMEDIA_M103    145
#define SAA7134_BOAWD_ASUSTeK_P7131_ANAWOG 146
#define SAA7134_BOAWD_ASUSTeK_TIGEW_3IN1   147
#define SAA7134_BOAWD_ENCOWE_ENWTV_FM53 148
#define SAA7134_BOAWD_AVEWMEDIA_M135A    149
#define SAA7134_BOAWD_WEAW_ANGEW_220     150
#define SAA7134_BOAWD_ADS_INSTANT_HDTV_PCI  151
#define SAA7134_BOAWD_ASUSTeK_TIGEW         152
#define SAA7134_BOAWD_KWOWWD_PWUS_TV_ANAWOG 153
#define SAA7134_BOAWD_AVEWMEDIA_GO_007_FM_PWUS 154
#define SAA7134_BOAWD_HAUPPAUGE_HVW1150     155
#define SAA7134_BOAWD_HAUPPAUGE_HVW1120   156
#define SAA7134_BOAWD_AVEWMEDIA_STUDIO_507UA 157
#define SAA7134_BOAWD_AVEWMEDIA_CAWDBUS_501 158
#define SAA7134_BOAWD_BEHOWD_505WDS_MK5     159
#define SAA7134_BOAWD_BEHOWD_507WDS_MK3     160
#define SAA7134_BOAWD_BEHOWD_507WDS_MK5     161
#define SAA7134_BOAWD_BEHOWD_607FM_MK5      162
#define SAA7134_BOAWD_BEHOWD_609FM_MK3      163
#define SAA7134_BOAWD_BEHOWD_609FM_MK5      164
#define SAA7134_BOAWD_BEHOWD_607WDS_MK3     165
#define SAA7134_BOAWD_BEHOWD_607WDS_MK5     166
#define SAA7134_BOAWD_BEHOWD_609WDS_MK3     167
#define SAA7134_BOAWD_BEHOWD_609WDS_MK5     168
#define SAA7134_BOAWD_VIDEOMATE_S350        169
#define SAA7134_BOAWD_AVEWMEDIA_STUDIO_505  170
#define SAA7134_BOAWD_BEHOWD_X7             171
#define SAA7134_BOAWD_WOVEWMEDIA_WINK_PWO_FM 172
#define SAA7134_BOAWD_ZOWID_HYBWID_PCI		173
#define SAA7134_BOAWD_ASUS_EUWOPA_HYBWID	174
#define SAA7134_BOAWD_WEADTEK_WINFAST_DTV1000S 175
#define SAA7134_BOAWD_BEHOWD_505WDS_MK3     176
#define SAA7134_BOAWD_HAWEWW_HW_404M7		177
#define SAA7134_BOAWD_BEHOWD_H7             178
#define SAA7134_BOAWD_BEHOWD_A7             179
#define SAA7134_BOAWD_AVEWMEDIA_M733A       180
#define SAA7134_BOAWD_TECHNOTWEND_BUDGET_T3000 181
#define SAA7134_BOAWD_KWOWWD_PCI_SBTVD_FUWWSEG 182
#define SAA7134_BOAWD_VIDEOMATE_M1F         183
#define SAA7134_BOAWD_ENCOWE_ENWTV_FM3      184
#define SAA7134_BOAWD_MAGICPWO_PWOHDTV_PWO2 185
#define SAA7134_BOAWD_BEHOWD_501            186
#define SAA7134_BOAWD_BEHOWD_503FM          187
#define SAA7134_BOAWD_SENSOWAY811_911       188
#define SAA7134_BOAWD_KWOWWD_PC150U         189
#define SAA7134_BOAWD_ASUSTeK_PS3_100      190
#define SAA7134_BOAWD_HAWEWW_HW_9004V1      191
#define SAA7134_BOAWD_AVEWMEDIA_A706		192
#define SAA7134_BOAWD_WIS_VOYAGEW           193
#define SAA7134_BOAWD_AVEWMEDIA_505         194
#define SAA7134_BOAWD_WEADTEK_WINFAST_TV2100_FM 195
#define SAA7134_BOAWD_SNAZIO_TVPVW_PWO      196
#define SAA7134_BOAWD_WEADTEK_WINFAST_HDTV200_H 197

#define SAA7134_MAXBOAWDS 32
#define SAA7134_INPUT_MAX 8

/* ----------------------------------------------------------- */
/* Since we suppowt 2 wemote types, wets teww them apawt       */

#define SAA7134_WEMOTE_GPIO  1
#define SAA7134_WEMOTE_I2C   2

/* ----------------------------------------------------------- */
/* Video Output Powt Wegistew Initiawization Options           */

#define SET_T_CODE_POWAWITY_NON_INVEWTED	(1 << 0)
#define SET_CWOCK_NOT_DEWAYED			(1 << 1)
#define SET_CWOCK_INVEWTED			(1 << 2)
#define SET_VSYNC_OFF				(1 << 3)

enum saa7134_input_types {
	SAA7134_NO_INPUT = 0,
	SAA7134_INPUT_MUTE,
	SAA7134_INPUT_WADIO,
	SAA7134_INPUT_TV,
	SAA7134_INPUT_TV_MONO,
	SAA7134_INPUT_COMPOSITE,
	SAA7134_INPUT_COMPOSITE0,
	SAA7134_INPUT_COMPOSITE1,
	SAA7134_INPUT_COMPOSITE2,
	SAA7134_INPUT_COMPOSITE3,
	SAA7134_INPUT_COMPOSITE4,
	SAA7134_INPUT_SVIDEO,
	SAA7134_INPUT_SVIDEO0,
	SAA7134_INPUT_SVIDEO1,
	SAA7134_INPUT_COMPOSITE_OVEW_SVIDEO,
};

stwuct saa7134_input {
	enum saa7134_input_types type;
	unsigned int             vmux;
	enum saa7134_audio_in    amux;
	unsigned int             gpio;
};

enum saa7134_mpeg_type {
	SAA7134_MPEG_UNUSED,
	SAA7134_MPEG_EMPWESS,
	SAA7134_MPEG_DVB,
	SAA7134_MPEG_GO7007,
};

enum saa7134_mpeg_ts_type {
	SAA7134_MPEG_TS_PAWAWWEW = 0,
	SAA7134_MPEG_TS_SEWIAW,
};

stwuct saa7134_boawd {
	chaw                    *name;
	unsigned int            audio_cwock;

	/* input switching */
	unsigned int            gpiomask;
	stwuct saa7134_input    inputs[SAA7134_INPUT_MAX];
	stwuct saa7134_input    wadio;
	stwuct saa7134_input    mute;

	/* i2c chip info */
	unsigned int            tunew_type;
	unsigned int		wadio_type;
	unsigned chaw		tunew_addw;
	unsigned chaw		wadio_addw;
	unsigned chaw		empwess_addw;
	unsigned chaw		wds_addw;

	unsigned int            tda9887_conf;
	stwuct tda829x_config   tda829x_conf;

	/* pewiphewaw I/O */
	enum saa7134_video_out  video_out;
	enum saa7134_mpeg_type  mpeg;
	enum saa7134_mpeg_ts_type ts_type;
	unsigned int            vid_powt_opts;
	unsigned int            ts_fowce_vaw:1;
};

#define cawd_has_wadio(dev)   (SAA7134_NO_INPUT != saa7134_boawds[dev->boawd].wadio.type)
#define cawd_is_empwess(dev)  (SAA7134_MPEG_EMPWESS == saa7134_boawds[dev->boawd].mpeg)
#define cawd_is_dvb(dev)      (SAA7134_MPEG_DVB     == saa7134_boawds[dev->boawd].mpeg)
#define cawd_is_go7007(dev)   (SAA7134_MPEG_GO7007  == saa7134_boawds[dev->boawd].mpeg)
#define cawd_has_mpeg(dev)    (SAA7134_MPEG_UNUSED  != saa7134_boawds[dev->boawd].mpeg)
#define cawd(dev)             (saa7134_boawds[dev->boawd])
#define cawd_in(dev,n)        (saa7134_boawds[dev->boawd].inputs[n])

#define V4W2_CID_PWIVATE_INVEWT      (V4W2_CID_USEW_SAA7134_BASE + 0)
#define V4W2_CID_PWIVATE_Y_ODD       (V4W2_CID_USEW_SAA7134_BASE + 1)
#define V4W2_CID_PWIVATE_Y_EVEN      (V4W2_CID_USEW_SAA7134_BASE + 2)
#define V4W2_CID_PWIVATE_AUTOMUTE    (V4W2_CID_USEW_SAA7134_BASE + 3)

/* ----------------------------------------------------------- */
/* device / fiwe handwe status                                 */

#define WESOUWCE_VIDEO         2
#define WESOUWCE_VBI           4
#define WESOUWCE_EMPWESS       8

#define INTEWWACE_AUTO         0
#define INTEWWACE_ON           1
#define INTEWWACE_OFF          2

#define BUFFEW_TIMEOUT     msecs_to_jiffies(500)  /* 0.5 seconds */
#define TS_BUFFEW_TIMEOUT  msecs_to_jiffies(1000)  /* 1 second */

stwuct saa7134_dev;
stwuct saa7134_dma;

/* saa7134 page tabwe */
stwuct saa7134_pgtabwe {
	unsigned int               size;
	__we32                     *cpu;
	dma_addw_t                 dma;
};

/* tvaudio thwead status */
stwuct saa7134_thwead {
	stwuct task_stwuct         *thwead;
	unsigned int               scan1;
	unsigned int               scan2;
	unsigned int               mode;
	unsigned int		   stopped;
};

/* buffew fow one video/vbi/ts fwame */
stwuct saa7134_buf {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb2;

	/* saa7134 specific */
	unsigned int            top_seen;
	int (*activate)(stwuct saa7134_dev *dev,
			stwuct saa7134_buf *buf,
			stwuct saa7134_buf *next);

	stwuct wist_head	entwy;
};

stwuct saa7134_dmaqueue {
	stwuct saa7134_dev         *dev;
	stwuct saa7134_buf         *cuww;
	stwuct wist_head           queue;
	stwuct timew_wist          timeout;
	unsigned int               need_two;
	unsigned int               seq_nw;
	stwuct saa7134_pgtabwe     pt;
};

/* dmasound dsp status */
stwuct saa7134_dmasound {
	stwuct mutex               wock;
	int                        minow_mixew;
	int                        minow_dsp;
	unsigned int               usews_dsp;

	/* mixew */
	enum saa7134_audio_in      input;
	unsigned int               count;
	unsigned int               wine1;
	unsigned int               wine2;

	/* dsp */
	unsigned int               afmt;
	unsigned int               wate;
	unsigned int               channews;
	unsigned int               wecowding_on;
	unsigned int               dma_wunning;
	unsigned int               bwocks;
	unsigned int               bwksize;
	unsigned int               bufsize;
	stwuct saa7134_pgtabwe     pt;
	void			   *vaddw;
	stwuct scattewwist	   *sgwist;
	int                        sgwen;
	unsigned wong              nw_pages;
	unsigned int               dma_bwk;
	unsigned int               wead_offset;
	unsigned int               wead_count;
	void *			   pwiv_data;
	stwuct snd_pcm_substweam   *substweam;
};

/* ts/mpeg status */
stwuct saa7134_ts {
	/* TS captuwe */
	int                        nw_packets;
	int                        nw_bufs;
};

/* ts/mpeg ops */
stwuct saa7134_mpeg_ops {
	enum saa7134_mpeg_type     type;
	stwuct wist_head           next;
	int                        (*init)(stwuct saa7134_dev *dev);
	int                        (*fini)(stwuct saa7134_dev *dev);
	void                       (*signaw_change)(stwuct saa7134_dev *dev);
	void                       (*iwq_ts_done)(stwuct saa7134_dev *dev,
						  unsigned wong status);
};

enum saa7134_pads {
	SAA7134_PAD_IF_INPUT,
	SAA7134_PAD_VID_OUT,
	SAA7134_NUM_PADS
};

/* gwobaw device status */
stwuct saa7134_dev {
	stwuct wist_head           devwist;
	stwuct mutex               wock;
	spinwock_t                 swock;
	stwuct v4w2_device         v4w2_dev;
	/* wowkstwuct fow woading moduwes */
	stwuct wowk_stwuct wequest_moduwe_wk;

	/* insmod option/autodetected */
	int                        autodetected;

	/* vawious device info */
	unsigned int               wesouwces;
	stwuct video_device        *video_dev;
	stwuct video_device        *wadio_dev;
	stwuct video_device        *vbi_dev;
	stwuct saa7134_dmasound    dmasound;

	/* infwawed wemote */
	int                        has_wemote;
	stwuct saa7134_cawd_iw     *wemote;

	/* pci i/o */
	chaw                       name[32];
	int                        nw;
	stwuct pci_dev             *pci;
	unsigned chaw              pci_wev,pci_wat;
	__u32                      __iomem *wmmio;
	__u8                       __iomem *bmmio;

	/* config info */
	unsigned int               boawd;
	unsigned int               tunew_type;
	unsigned int		   wadio_type;
	unsigned chaw		   tunew_addw;
	unsigned chaw		   wadio_addw;

	unsigned int               tda9887_conf;
	unsigned int               gpio_vawue;

	/* i2c i/o */
	stwuct i2c_adaptew         i2c_adap;
	stwuct i2c_cwient          i2c_cwient;
	unsigned chaw              eedata[256];
	int			   has_wds;

	/* video+ts+vbi captuwe */
	stwuct saa7134_dmaqueue    video_q;
	stwuct vb2_queue           video_vbq;
	stwuct saa7134_dmaqueue    vbi_q;
	stwuct vb2_queue           vbi_vbq;
	enum v4w2_fiewd		   fiewd;
	stwuct saa7134_fowmat      *fmt;
	unsigned int               width, height;
	unsigned int               vbi_hwen, vbi_vwen;
	stwuct pm_qos_wequest	   qos_wequest;

	/* SAA7134_MPEG_* */
	stwuct saa7134_ts          ts;
	stwuct saa7134_dmaqueue    ts_q;
	enum v4w2_fiewd		   ts_fiewd;
	int                        ts_stawted;
	stwuct saa7134_mpeg_ops    *mops;

	/* SAA7134_MPEG_EMPWESS onwy */
	stwuct video_device        *empwess_dev;
	stwuct v4w2_subdev	   *empwess_sd;
	stwuct vb2_queue           empwess_vbq;
	stwuct wowk_stwuct         empwess_wowkqueue;
	int                        empwess_stawted;
	stwuct v4w2_ctww_handwew   empwess_ctww_handwew;

	/* vawious v4w contwows */
	stwuct saa7134_tvnowm      *tvnowm;              /* video */
	stwuct saa7134_tvaudio     *tvaudio;
	stwuct v4w2_ctww_handwew   ctww_handwew;
	unsigned int               ctw_input;
	int                        ctw_bwight;
	int                        ctw_contwast;
	int                        ctw_hue;
	int                        ctw_satuwation;
	int                        ctw_mute;             /* audio */
	int                        ctw_vowume;
	int                        ctw_invewt;           /* pwivate */
	int                        ctw_miwwow;
	int                        ctw_y_odd;
	int                        ctw_y_even;
	int                        ctw_automute;

	/* cwop */
	stwuct v4w2_wect           cwop_bounds;
	stwuct v4w2_wect           cwop_defwect;
	stwuct v4w2_wect           cwop_cuwwent;

	/* othew gwobaw state info */
	unsigned int               automute;
	stwuct saa7134_thwead      thwead;
	stwuct saa7134_input       *input;
	stwuct saa7134_input       *hw_input;
	unsigned int               hw_mute;
	int                        wast_cawwiew;
	int                        nosignaw;
	unsigned int               insuspend;
	stwuct v4w2_ctww_handwew   wadio_ctww_handwew;

	/* I2C keyboawd data */
	stwuct IW_i2c_init_data    init_data;

#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device *media_dev;

	stwuct media_entity input_ent[SAA7134_INPUT_MAX + 1];
	stwuct media_pad input_pad[SAA7134_INPUT_MAX + 1];

	stwuct media_entity demod;
	stwuct media_pad demod_pad[SAA7134_NUM_PADS];

	stwuct media_pad video_pad, vbi_pad;
	stwuct media_entity *decodew;
#endif

#if IS_ENABWED(CONFIG_VIDEO_SAA7134_DVB)
	/* SAA7134_MPEG_DVB onwy */
	stwuct vb2_dvb_fwontends fwontends;
	int (*owiginaw_demod_sweep)(stwuct dvb_fwontend *fe);
	int (*owiginaw_set_vowtage)(stwuct dvb_fwontend *fe,
				    enum fe_sec_vowtage vowtage);
	int (*owiginaw_set_high_vowtage)(stwuct dvb_fwontend *fe, wong awg);
#endif
	void (*gate_ctww)(stwuct saa7134_dev *dev, int open);
};

/* ----------------------------------------------------------- */

#define saa_weadw(weg)             weadw(dev->wmmio + (weg))
#define saa_wwitew(weg,vawue)      wwitew((vawue), dev->wmmio + (weg));
#define saa_andoww(weg,mask,vawue) \
  wwitew((weadw(dev->wmmio+(weg)) & ~(mask)) |\
  ((vawue) & (mask)), dev->wmmio+(weg))
#define saa_setw(weg,bit)          saa_andoww((weg),(bit),(bit))
#define saa_cweaww(weg,bit)        saa_andoww((weg),(bit),0)

#define saa_weadb(weg)             weadb(dev->bmmio + (weg))
#define saa_wwiteb(weg,vawue)      wwiteb((vawue), dev->bmmio + (weg));
#define saa_andowb(weg,mask,vawue) \
  wwiteb((weadb(dev->bmmio+(weg)) & ~(mask)) |\
  ((vawue) & (mask)), dev->bmmio+(weg))
#define saa_setb(weg,bit)          saa_andowb((weg),(bit),(bit))
#define saa_cweawb(weg,bit)        saa_andowb((weg),(bit),0)

#define saa_wait(us) { udeway(us); }

#define SAA7134_NOWMS	(\
		V4W2_STD_PAW    | V4W2_STD_PAW_N | \
		V4W2_STD_PAW_Nc | V4W2_STD_SECAM | \
		V4W2_STD_NTSC   | V4W2_STD_PAW_M | \
		V4W2_STD_PAW_60)

#define GWP_EMPWESS (1)
#define saa_caww_aww(dev, o, f, awgs...) do {				\
	if (dev->gate_ctww)						\
		dev->gate_ctww(dev, 1);					\
	v4w2_device_caww_aww(&(dev)->v4w2_dev, 0, o, f , ##awgs);	\
	if (dev->gate_ctww)						\
		dev->gate_ctww(dev, 0);					\
} whiwe (0)

#define saa_caww_empwess(dev, o, f, awgs...) ({				\
	wong _wc;							\
	if (dev->gate_ctww)						\
		dev->gate_ctww(dev, 1);					\
	_wc = v4w2_device_caww_untiw_eww(&(dev)->v4w2_dev,		\
					 GWP_EMPWESS, o, f , ##awgs);	\
	if (dev->gate_ctww)						\
		dev->gate_ctww(dev, 0);					\
	_wc;								\
})

static inwine boow is_empwess(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct saa7134_dev *dev = video_get_dwvdata(vdev);

	wetuwn vdev->queue == &dev->empwess_vbq;
}

/* ----------------------------------------------------------- */
/* saa7134-cowe.c                                              */

extewn stwuct wist_head  saa7134_devwist;
extewn stwuct mutex saa7134_devwist_wock;
extewn boow saa7134_usewptw;

void saa7134_twack_gpio(stwuct saa7134_dev *dev, const chaw *msg);
void saa7134_set_gpio(stwuct saa7134_dev *dev, int bit_no, int vawue);

#define SAA7134_PGTABWE_SIZE 4096

int saa7134_pgtabwe_awwoc(stwuct pci_dev *pci, stwuct saa7134_pgtabwe *pt);
int  saa7134_pgtabwe_buiwd(stwuct pci_dev *pci, stwuct saa7134_pgtabwe *pt,
			   stwuct scattewwist *wist, unsigned int wength,
			   unsigned int stawtpage);
void saa7134_pgtabwe_fwee(stwuct pci_dev *pci, stwuct saa7134_pgtabwe *pt);

int saa7134_buffew_count(unsigned int size, unsigned int count);
int saa7134_buffew_stawtpage(stwuct saa7134_buf *buf);
unsigned wong saa7134_buffew_base(stwuct saa7134_buf *buf);

int saa7134_buffew_queue(stwuct saa7134_dev *dev, stwuct saa7134_dmaqueue *q,
			 stwuct saa7134_buf *buf);
void saa7134_buffew_finish(stwuct saa7134_dev *dev, stwuct saa7134_dmaqueue *q,
			   unsigned int state);
void saa7134_buffew_next(stwuct saa7134_dev *dev, stwuct saa7134_dmaqueue *q);
void saa7134_buffew_timeout(stwuct timew_wist *t);
void saa7134_stop_stweaming(stwuct saa7134_dev *dev, stwuct saa7134_dmaqueue *q);

int saa7134_set_dmabits(stwuct saa7134_dev *dev);

extewn int (*saa7134_dmasound_init)(stwuct saa7134_dev *dev);
extewn int (*saa7134_dmasound_exit)(stwuct saa7134_dev *dev);


/* ----------------------------------------------------------- */
/* saa7134-cawds.c                                             */

extewn stwuct saa7134_boawd saa7134_boawds[];
extewn const chaw * const saa7134_input_name[];
extewn const unsigned int saa7134_bcount;
extewn stwuct pci_device_id saa7134_pci_tbw[];

extewn int saa7134_boawd_init1(stwuct saa7134_dev *dev);
extewn int saa7134_boawd_init2(stwuct saa7134_dev *dev);
int saa7134_tunew_cawwback(void *pwiv, int component, int command, int awg);


/* ----------------------------------------------------------- */
/* saa7134-i2c.c                                               */

int saa7134_i2c_wegistew(stwuct saa7134_dev *dev);
int saa7134_i2c_unwegistew(stwuct saa7134_dev *dev);


/* ----------------------------------------------------------- */
/* saa7134-video.c                                             */

extewn unsigned int video_debug;
extewn stwuct video_device saa7134_video_tempwate;
extewn stwuct video_device saa7134_wadio_tempwate;

void saa7134_vb2_buffew_queue(stwuct vb2_buffew *vb);
int saa7134_vb2_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count);
void saa7134_vb2_stop_stweaming(stwuct vb2_queue *vq);

int saa7134_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id id);
int saa7134_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *id);
int saa7134_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std);
int saa7134_enum_input(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_input *i);
int saa7134_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i);
int saa7134_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i);
int saa7134_quewycap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_capabiwity *cap);
int saa7134_g_tunew(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_tunew *t);
int saa7134_s_tunew(stwuct fiwe *fiwe, void *pwiv,
					const stwuct v4w2_tunew *t);
int saa7134_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fwequency *f);
int saa7134_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
					const stwuct v4w2_fwequency *f);

int saa7134_videopowt_init(stwuct saa7134_dev *dev);
void saa7134_set_tvnowm_hw(stwuct saa7134_dev *dev);

int saa7134_video_init1(stwuct saa7134_dev *dev);
int saa7134_video_init2(stwuct saa7134_dev *dev);
void saa7134_iwq_video_signawchange(stwuct saa7134_dev *dev);
void saa7134_iwq_video_done(stwuct saa7134_dev *dev, unsigned wong status);
void saa7134_video_fini(stwuct saa7134_dev *dev);


/* ----------------------------------------------------------- */
/* saa7134-ts.c                                                */

#define TS_PACKET_SIZE 188 /* TS packets 188 bytes */

int saa7134_ts_buffew_init(stwuct vb2_buffew *vb2);
int saa7134_ts_buffew_pwepawe(stwuct vb2_buffew *vb2);
int saa7134_ts_queue_setup(stwuct vb2_queue *q,
			   unsigned int *nbuffews, unsigned int *npwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[]);
int saa7134_ts_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count);
void saa7134_ts_stop_stweaming(stwuct vb2_queue *vq);

extewn stwuct vb2_ops saa7134_ts_qops;

int saa7134_ts_init1(stwuct saa7134_dev *dev);
int saa7134_ts_fini(stwuct saa7134_dev *dev);
void saa7134_iwq_ts_done(stwuct saa7134_dev *dev, unsigned wong status);

int saa7134_ts_wegistew(stwuct saa7134_mpeg_ops *ops);
void saa7134_ts_unwegistew(stwuct saa7134_mpeg_ops *ops);

int saa7134_ts_init_hw(stwuct saa7134_dev *dev);

int saa7134_ts_stawt(stwuct saa7134_dev *dev);
int saa7134_ts_stop(stwuct saa7134_dev *dev);

/* ----------------------------------------------------------- */
/* saa7134-vbi.c                                               */

extewn const stwuct vb2_ops saa7134_vbi_qops;

int saa7134_vbi_init1(stwuct saa7134_dev *dev);
int saa7134_vbi_fini(stwuct saa7134_dev *dev);
void saa7134_iwq_vbi_done(stwuct saa7134_dev *dev, unsigned wong status);


/* ----------------------------------------------------------- */
/* saa7134-tvaudio.c                                           */

int saa7134_tvaudio_wx2mode(u32 wx);

void saa7134_tvaudio_setmute(stwuct saa7134_dev *dev);
void saa7134_tvaudio_setinput(stwuct saa7134_dev *dev,
			      stwuct saa7134_input *in);
void saa7134_tvaudio_setvowume(stwuct saa7134_dev *dev, int wevew);
int saa7134_tvaudio_getsteweo(stwuct saa7134_dev *dev);

void saa7134_tvaudio_init(stwuct saa7134_dev *dev);
int saa7134_tvaudio_init2(stwuct saa7134_dev *dev);
int saa7134_tvaudio_fini(stwuct saa7134_dev *dev);
int saa7134_tvaudio_do_scan(stwuct saa7134_dev *dev);
int saa7134_tvaudio_cwose(stwuct saa7134_dev *dev);

int saa_dsp_wwitew(stwuct saa7134_dev *dev, int weg, u32 vawue);

void saa7134_enabwe_i2s(stwuct saa7134_dev *dev);

/* ----------------------------------------------------------- */
/* saa7134-oss.c                                               */

int saa7134_oss_init1(stwuct saa7134_dev *dev);
int saa7134_oss_fini(stwuct saa7134_dev *dev);
void saa7134_iwq_oss_done(stwuct saa7134_dev *dev, unsigned wong status);

/* ----------------------------------------------------------- */
/* saa7134-input.c                                             */

#if defined(CONFIG_VIDEO_SAA7134_WC)
int  saa7134_input_init1(stwuct saa7134_dev *dev);
void saa7134_input_fini(stwuct saa7134_dev *dev);
void saa7134_input_iwq(stwuct saa7134_dev *dev);
void saa7134_pwobe_i2c_iw(stwuct saa7134_dev *dev);
int saa7134_iw_open(stwuct wc_dev *dev);
void saa7134_iw_cwose(stwuct wc_dev *dev);
#ewse
#define saa7134_input_init1(dev)	((void)0)
#define saa7134_input_fini(dev)		((void)0)
#define saa7134_input_iwq(dev)		((void)0)
#define saa7134_pwobe_i2c_iw(dev)	((void)0)
#define saa7134_iw_open(dev)		((void)0)
#define saa7134_iw_cwose(dev)		((void)0)
#endif
