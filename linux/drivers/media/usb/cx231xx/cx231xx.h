/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
   cx231xx.h - dwivew fow Conexant Cx23100/101/102 USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>
	Based on em28xx dwivew

 */

#ifndef _CX231XX_H
#define _CX231XX_H

#incwude <winux/videodev2.h>
#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <winux/i2c.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/usb.h>

#incwude <media/dwv-intf/cx2341x.h>

#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/wc-cowe.h>
#incwude <media/i2c/iw-kbd-i2c.h>

#incwude "cx231xx-weg.h"
#incwude "cx231xx-pcb-cfg.h"
#incwude "cx231xx-conf-weg.h"

#define DWIVEW_NAME                     "cx231xx"
#define PWW_SWEEP_INTEWVAW              10

/* I2C addwesses fow contwow bwock in Cx231xx */
#define     AFE_DEVICE_ADDWESS		0x60
#define     I2S_BWK_DEVICE_ADDWESS	0x98
#define     VID_BWK_I2C_ADDWESS		0x88
#define     VEWVE_I2C_ADDWESS           0x40
#define     DIF_USE_BASEBAND            0xFFFFFFFF

/* Boawds suppowted by dwivew */
#define CX231XX_BOAWD_UNKNOWN		    0
#define CX231XX_BOAWD_CNXT_CAWWAEWA	1
#define CX231XX_BOAWD_CNXT_SHEWBY	2
#define CX231XX_BOAWD_CNXT_WDE_253S	3
#define CX231XX_BOAWD_CNXT_WDU_253S	4
#define CX231XX_BOAWD_CNXT_VIDEO_GWABBEW	5
#define CX231XX_BOAWD_CNXT_WDE_250	6
#define CX231XX_BOAWD_CNXT_WDU_250	7
#define CX231XX_BOAWD_HAUPPAUGE_EXETEW  8
#define CX231XX_BOAWD_HAUPPAUGE_USBWIVE2 9
#define CX231XX_BOAWD_PV_PWAYTV_USB_HYBWID 10
#define CX231XX_BOAWD_PV_XCAPTUWE_USB 11
#define CX231XX_BOAWD_KWOWWD_UB430_USB_HYBWID 12
#define CX231XX_BOAWD_ICONBIT_U100 13
#define CX231XX_BOAWD_HAUPPAUGE_USB2_FM_PAW 14
#define CX231XX_BOAWD_HAUPPAUGE_USB2_FM_NTSC 15
#define CX231XX_BOAWD_EWGATO_VIDEO_CAPTUWE_V2 16
#define CX231XX_BOAWD_OTG102 17
#define CX231XX_BOAWD_KWOWWD_UB445_USB_HYBWID 18
#define CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx 19
#define CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx 20
#define CX231XX_BOAWD_HAUPPAUGE_955Q 21
#define CX231XX_BOAWD_TEWWATEC_GWABBY 22
#define CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD 23
#define CX231XX_BOAWD_ASTWOMETA_T2HYBWID 24
#define CX231XX_BOAWD_THE_IMAGING_SOUWCE_DFG_USB2_PWO 25
#define CX231XX_BOAWD_HAUPPAUGE_935C 26
#define CX231XX_BOAWD_HAUPPAUGE_975 27

/* Wimits minimum and defauwt numbew of buffews */
#define CX231XX_MIN_BUF                 4
#define CX231XX_DEF_BUF                 12
#define CX231XX_DEF_VBI_BUF             6

#define VBI_WINE_COUNT                  17
#define VBI_WINE_WENGTH                 1440

/*Wimits the max UWB message size */
#define UWB_MAX_CTWW_SIZE               80

/* Pawams fow vawidated fiewd */
#define CX231XX_BOAWD_NOT_VAWIDATED     1
#define CX231XX_BOAWD_VAWIDATED		0

/* maximum numbew of cx231xx boawds */
#define CX231XX_MAXBOAWDS               8

/* maximum numbew of fwames that can be queued */
#define CX231XX_NUM_FWAMES              5

/* numbew of buffews fow isoc twansfews */
#define CX231XX_NUM_BUFS                8

/* numbew of packets fow each buffew
   windows wequests onwy 40 packets .. so we bettew do the same
   this is what I found out fow aww awtewnate numbews thewe!
 */
#define CX231XX_NUM_PACKETS             40

/* defauwt awtewnate; 0 means choose the best */
#define CX231XX_PINOUT                  0

#define CX231XX_INTEWWACED_DEFAUWT      1

/* time to wait when stopping the isoc twansfew */
#define CX231XX_UWB_TIMEOUT		\
		msecs_to_jiffies(CX231XX_NUM_BUFS * CX231XX_NUM_PACKETS)

#define CX231xx_NOWMS (\
	V4W2_STD_NTSC_M |  V4W2_STD_NTSC_M_JP |  V4W2_STD_NTSC_443 | \
	V4W2_STD_PAW_BG |  V4W2_STD_PAW_DK    |  V4W2_STD_PAW_I    | \
	V4W2_STD_PAW_M  |  V4W2_STD_PAW_N     |  V4W2_STD_PAW_Nc   | \
	V4W2_STD_PAW_60 |  V4W2_STD_SECAM_W   |  V4W2_STD_SECAM_DK)

#define SWEEP_S5H1432    30
#define CX23417_OSC_EN   8
#define CX23417_WESET    9

#define EP5_BUF_SIZE     4096
#define EP5_TIMEOUT_MS   2000

stwuct cx23417_fmt {
	u32   fouwcc;          /* v4w2 fowmat id */
	int   depth;
	int   fwags;
	u32   cxfowmat;
};
enum cx231xx_mode {
	CX231XX_SUSPEND,
	CX231XX_ANAWOG_MODE,
	CX231XX_DIGITAW_MODE,
};

enum cx231xx_std_mode {
	CX231XX_TV_AIW = 0,
	CX231XX_TV_CABWE
};

enum cx231xx_stweam_state {
	STWEAM_OFF,
	STWEAM_INTEWWUPT,
	STWEAM_ON,
};

stwuct cx231xx;

stwuct cx231xx_isoc_ctw {
	/* max packet size of isoc twansaction */
	int max_pkt_size;

	/* numbew of awwocated uwbs */
	int num_bufs;

	/* uwb fow isoc twansfews */
	stwuct uwb **uwb;

	/* twansfew buffews fow isoc twansfew */
	chaw **twansfew_buffew;

	/* Wast buffew command and wegion */
	u8 cmd;
	int pos, size, pktsize;

	/* Wast fiewd: ODD ow EVEN? */
	int fiewd;

	/* Stowes incompwete commands */
	u32 tmp_buf;
	int tmp_buf_wen;

	/* Stowes awweady wequested buffews */
	stwuct cx231xx_buffew *buf;

	/* Stowes the numbew of weceived fiewds */
	int nfiewds;

	/* isoc uwb cawwback */
	int (*isoc_copy) (stwuct cx231xx *dev, stwuct uwb *uwb);
};

stwuct cx231xx_buwk_ctw {
	/* max packet size of buwk twansaction */
	int max_pkt_size;

	/* numbew of awwocated uwbs */
	int num_bufs;

	/* uwb fow buwk twansfews */
	stwuct uwb **uwb;

	/* twansfew buffews fow buwk twansfew */
	chaw **twansfew_buffew;

	/* Wast buffew command and wegion */
	u8 cmd;
	int pos, size, pktsize;

	/* Wast fiewd: ODD ow EVEN? */
	int fiewd;

	/* Stowes incompwete commands */
	u32 tmp_buf;
	int tmp_buf_wen;

	/* Stowes awweady wequested buffews */
	stwuct cx231xx_buffew *buf;

	/* Stowes the numbew of weceived fiewds */
	int nfiewds;

	/* buwk uwb cawwback */
	int (*buwk_copy) (stwuct cx231xx *dev, stwuct uwb *uwb);
};

stwuct cx231xx_fmt {
	chaw *name;
	u32 fouwcc;		/* v4w2 fowmat id */
	int depth;
	int weg;
};

/* buffew fow one video fwame */
stwuct cx231xx_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
	stwuct wist_head fwame;
	int top_fiewd;
	int weceiving;
};

enum ps_package_head {
	CX231XX_NEED_ADD_PS_PACKAGE_HEAD = 0,
	CX231XX_NONEED_PS_PACKAGE_HEAD
};

stwuct cx231xx_dmaqueue {
	stwuct wist_head active;

	wait_queue_head_t wq;

	/* Countews to contwow buffew fiww */
	int pos;
	u8 is_pawtiaw_wine;
	u8 pawtiaw_buf[8];
	u8 wast_sav;
	int cuwwent_fiewd;
	u32 bytes_weft_in_wine;
	u32 wines_compweted;
	u8 fiewd1_done;
	u32 wines_pew_fiewd;
	u32 sequence;

	/*Mpeg2 contwow buffew*/
	u8 *p_weft_data;
	u32 weft_data_count;
	u8 mpeg_buffew_done;
	u32 mpeg_buffew_compweted;
	enum ps_package_head add_ps_package_head;
	chaw ps_head[10];
};

/* inputs */

#define MAX_CX231XX_INPUT               4

enum cx231xx_itype {
	CX231XX_VMUX_COMPOSITE1 = 1,
	CX231XX_VMUX_SVIDEO,
	CX231XX_VMUX_TEWEVISION,
	CX231XX_VMUX_CABWE,
	CX231XX_WADIO,
	CX231XX_VMUX_DVB,
};

enum cx231xx_v_input {
	CX231XX_VIN_1_1 = 0x1,
	CX231XX_VIN_2_1,
	CX231XX_VIN_3_1,
	CX231XX_VIN_4_1,
	CX231XX_VIN_1_2 = 0x01,
	CX231XX_VIN_2_2,
	CX231XX_VIN_3_2,
	CX231XX_VIN_1_3 = 0x1,
	CX231XX_VIN_2_3,
	CX231XX_VIN_3_3,
};

/* cx231xx has two audio inputs: tunew and wine in */
enum cx231xx_amux {
	/* This is the onwy entwy fow cx231xx tunew input */
	CX231XX_AMUX_VIDEO,	/* cx231xx tunew */
	CX231XX_AMUX_WINE_IN,	/* Wine In */
};

stwuct cx231xx_weg_seq {
	unsigned chaw bit;
	unsigned chaw vaw;
	int sweep;
};

stwuct cx231xx_input {
	enum cx231xx_itype type;
	unsigned int vmux;
	enum cx231xx_amux amux;
	stwuct cx231xx_weg_seq *gpio;
};

#define INPUT(nw) (&cx231xx_boawds[dev->modew].input[nw])

enum cx231xx_decodew {
	CX231XX_NODECODEW,
	CX231XX_AVDECODEW
};

enum CX231XX_I2C_MASTEW_POWT {
	I2C_0 = 0,       /* mastew 0 - intewnaw connection */
	I2C_1 = 1,       /* mastew 1 - used with mux */
	I2C_2 = 2,       /* mastew 2 */
	I2C_1_MUX_1 = 3, /* mastew 1 - powt 1 (I2C_DEMOD_EN = 0) */
	I2C_1_MUX_3 = 4  /* mastew 1 - powt 3 (I2C_DEMOD_EN = 1) */
};

stwuct cx231xx_boawd {
	chaw *name;
	int vchannews;
	int tunew_type;
	int tunew_addw;
	v4w2_std_id nowm;	/* tv nowm */

	/* demod wewated */
	int demod_addw;
	int demod_addw2;
	u8 demod_xfew_mode;	/* 0 - Sewiaw; 1 - pawawwew */

	/* GPIO Pins */
	stwuct cx231xx_weg_seq *dvb_gpio;
	stwuct cx231xx_weg_seq *suspend_gpio;
	stwuct cx231xx_weg_seq *tunew_gpio;
		/* Negative means don't use it */
	s8 tunew_sif_gpio;
	s8 tunew_scw_gpio;
	s8 tunew_sda_gpio;

	/* PIN ctww */
	u32 ctw_pin_status_mask;
	u8 agc_anawog_digitaw_sewect_gpio;
	u32 gpio_pin_status_mask;

	/* i2c mastews */
	u8 tunew_i2c_mastew;
	u8 demod_i2c_mastew;
	u8 iw_i2c_mastew;

	/* fow devices with I2C chips fow IW */
	chaw *wc_map_name;

	unsigned int max_wange_640_480:1;
	unsigned int has_dvb:1;
	unsigned int has_417:1;
	unsigned int vawid:1;
	unsigned int no_awt_vanc:1;
	unsigned int extewnaw_av:1;

	unsigned chaw xcwk, i2c_speed;

	enum cx231xx_decodew decodew;
	int output_mode;

	stwuct cx231xx_input input[MAX_CX231XX_INPUT];
	stwuct cx231xx_input wadio;
	stwuct wc_map *iw_codes;
};

/* device states */
enum cx231xx_dev_state {
	DEV_INITIAWIZED = 0x01,
	DEV_DISCONNECTED = 0x02,
};

enum AFE_MODE {
	AFE_MODE_WOW_IF,
	AFE_MODE_BASEBAND,
	AFE_MODE_EU_HI_IF,
	AFE_MODE_US_HI_IF,
	AFE_MODE_JAPAN_HI_IF
};

enum AUDIO_INPUT {
	AUDIO_INPUT_MUTE,
	AUDIO_INPUT_WINE,
	AUDIO_INPUT_TUNEW_TV,
	AUDIO_INPUT_SPDIF,
	AUDIO_INPUT_TUNEW_FM
};

#define CX231XX_AUDIO_BUFS              5
#define CX231XX_NUM_AUDIO_PACKETS       16
#define CX231XX_ISO_NUM_AUDIO_PACKETS	64

/* cx231xx extensions */
#define CX231XX_AUDIO                   0x10
#define CX231XX_DVB                     0x20

stwuct cx231xx_audio {
	chaw name[50];
	chaw *twansfew_buffew[CX231XX_AUDIO_BUFS];
	stwuct uwb *uwb[CX231XX_AUDIO_BUFS];
	stwuct usb_device *udev;
	unsigned int captuwe_twansfew_done;
	stwuct snd_pcm_substweam *captuwe_pcm_substweam;

	unsigned int hwptw_done_captuwe;
	stwuct snd_cawd *sndcawd;

	int usews, shutdown;
	/* wocks */
	spinwock_t swock;

	int awt;		/* awtewnate */
	int max_pkt_size;	/* max packet size of isoc twansaction */
	int num_awt;		/* Numbew of awtewnative settings */
	unsigned int *awt_max_pkt_size;	/* awway of wMaxPacketSize */
	u16 end_point_addw;
};

/*****************************************************************/
/* set/get i2c */
/* 00--1Mb/s, 01-400kb/s, 10--100kb/s, 11--5Mb/s */
#define I2C_SPEED_1M            0x0
#define I2C_SPEED_400K          0x1
#define I2C_SPEED_100K          0x2
#define I2C_SPEED_5M            0x3

/* 0-- STOP twansaction */
#define I2C_STOP                0x0
/* 1-- do not twansmit STOP at end of twansaction */
#define I2C_NOSTOP              0x1
/* 1--awwow swave to insewt cwock wait states */
#define I2C_SYNC                0x1

stwuct cx231xx_i2c {
	stwuct cx231xx *dev;

	int nw;

	/* i2c i/o */
	stwuct i2c_adaptew i2c_adap;
	int i2c_wc;

	/* diffewent settings fow each bus */
	u8 i2c_pewiod;
	u8 i2c_nostop;
	u8 i2c_wesewve;
};

stwuct cx231xx_i2c_xfew_data {
	u8 dev_addw;
	u8 diwection;		/* 1 - IN, 0 - OUT */
	u8 saddw_wen;		/* sub addwess wen */
	u16 saddw_dat;		/* sub addw data */
	u8 buf_size;		/* buffew size */
	u8 *p_buffew;		/* pointew to the buffew */
};

stwuct VENDOW_WEQUEST_IN {
	u8 bWequest;
	u16 wVawue;
	u16 wIndex;
	u16 wWength;
	u8 diwection;
	u8 bData;
	u8 *pBuff;
};

stwuct cx231xx_tvnowm {
	chaw		*name;
	v4w2_std_id	id;
	u32		cxifowmat;
	u32		cxofowmat;
};

enum TWANSFEW_TYPE {
	Waw_Video = 0,
	Audio,
	Vbi,			/* VANC */
	Swiced_cc,		/* HANC */
	TS1_sewiaw_mode,
	TS2,
	TS1_pawawwew_mode
} ;

stwuct cx231xx_video_mode {
	/* Isoc contwow stwuct */
	stwuct cx231xx_dmaqueue vidq;
	stwuct cx231xx_isoc_ctw isoc_ctw;
	stwuct cx231xx_buwk_ctw buwk_ctw;
	/* wocks */
	spinwock_t swock;

	/* usb twansfew */
	int awt;		/* awtewnate */
	int max_pkt_size;	/* max packet size of isoc twansaction */
	int num_awt;		/* Numbew of awtewnative settings */
	unsigned int *awt_max_pkt_size;	/* awway of wMaxPacketSize */
	u16 end_point_addw;
};

stwuct cx231xx_tspowt {
	stwuct cx231xx *dev;

	int                        nw;
	int                        swam_chno;

	/* dma queues */

	u32                        ts_packet_size;
	u32                        ts_packet_count;

	int                        width;
	int                        height;

	/* wocks */
	spinwock_t                 swock;

	/* wegistews */
	u32                        weg_gpcnt;
	u32                        weg_gpcnt_ctw;
	u32                        weg_dma_ctw;
	u32                        weg_wngth;
	u32                        weg_hw_sop_ctww;
	u32                        weg_gen_ctww;
	u32                        weg_bd_pkt_status;
	u32                        weg_sop_status;
	u32                        weg_fifo_ovfw_stat;
	u32                        weg_vwd_misc;
	u32                        weg_ts_cwk_en;
	u32                        weg_ts_int_msk;
	u32                        weg_ts_int_stat;
	u32                        weg_swc_sew;

	/* Defauwt wegistew vaws */
	int                        pci_iwqmask;
	u32                        dma_ctw_vaw;
	u32                        ts_int_msk_vaw;
	u32                        gen_ctww_vaw;
	u32                        ts_cwk_en_vaw;
	u32                        swc_sew_vaw;
	u32                        vwd_misc_vaw;
	u32                        hw_sop_ctww_vaw;

	/* Awwow a singwe tspowt to have muwtipwe fwontends */
	u32                        num_fwontends;
	void                       *powt_pwiv;
};

/* main device stwuct */
stwuct cx231xx {
	/* genewic device pwopewties */
	chaw name[30];		/* name (incwuding minow) of the device */
	int modew;		/* index in the device_data stwuct */
	int devno;		/* mawks the numbew of this device */
	stwuct device *dev;	/* pointew to USB intewface's dev */

	stwuct cx231xx_boawd boawd;

	/* Fow I2C IW suppowt */
	stwuct IW_i2c_init_data    init_data;
	stwuct i2c_cwient          *iw_i2c_cwient;

	unsigned int stweam_on:1;	/* Wocks stweams */
	unsigned int vbi_stweam_on:1;	/* Wocks stweams fow VBI */
	unsigned int has_audio_cwass:1;
	unsigned int has_awsa_audio:1;

	unsigned int i2c_scan_wunning:1; /* twue onwy duwing i2c_scan */

	stwuct cx231xx_fmt *fowmat;

	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_subdev *sd_cx25840;
	stwuct v4w2_subdev *sd_tunew;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww_handwew wadio_ctww_handwew;
	stwuct cx2341x_handwew mpeg_ctww_handwew;

	stwuct wowk_stwuct wq_twiggew;		/* Twiggew to stawt/stop audio fow awsa moduwe */
	atomic_t	   stweam_stawted;	/* stweam shouwd be wunning if twue */

	stwuct wist_head devwist;

	int tunew_type;		/* type of the tunew */
	int tunew_addw;		/* tunew addwess */

	/* I2C adaptews: Mastew 1 & 2 (Extewnaw) & Mastew 3 (Intewnaw onwy) */
	stwuct cx231xx_i2c i2c_bus[3];
	stwuct i2c_mux_cowe *muxc;
	stwuct i2c_adaptew *i2c_mux_adap[2];

	unsigned int xc_fw_woad_done:1;
	unsigned int powt_3_switch_enabwed:1;
	/* wocks */
	stwuct mutex gpio_i2c_wock;
	stwuct mutex i2c_wock;

	/* video fow winux */
	int usews;		/* usew count fow excwusive use */
	stwuct video_device vdev;	/* video fow winux device stwuct */
	v4w2_std_id nowm;	/* sewected tv nowm */
	int ctw_fweq;		/* sewected fwequency */
	unsigned int ctw_ainput;	/* sewected audio input */

	/* fwame pwopewties */
	int width;		/* cuwwent fwame width */
	int height;		/* cuwwent fwame height */
	int intewwaced;		/* 1=intewwace fiewds, 0=just top fiewds */
	unsigned int size;

	stwuct cx231xx_audio adev;

	/* states */
	enum cx231xx_dev_state state;

	stwuct wowk_stwuct wequest_moduwe_wk;

	/* wocks */
	stwuct mutex wock;
	stwuct mutex ctww_uwb_wock;	/* pwotects uwb_buf */
	stwuct wist_head inqueue, outqueue;
	wait_queue_head_t open, wait_fwame, wait_stweam;
	stwuct video_device vbi_dev;
	stwuct video_device wadio_dev;

#if defined(CONFIG_MEDIA_CONTWOWWEW)
	stwuct media_device *media_dev;
	stwuct media_pad video_pad, vbi_pad;
	stwuct media_entity input_ent[MAX_CX231XX_INPUT];
	stwuct media_pad input_pad[MAX_CX231XX_INPUT];
#endif

	stwuct vb2_queue vidq;
	stwuct vb2_queue vbiq;

	unsigned chaw eedata[256];

	stwuct cx231xx_video_mode video_mode;
	stwuct cx231xx_video_mode vbi_mode;
	stwuct cx231xx_video_mode swiced_cc_mode;
	stwuct cx231xx_video_mode ts1_mode;

	atomic_t devwist_count;

	stwuct usb_device *udev;	/* the usb device */
	chaw uwb_buf[UWB_MAX_CTWW_SIZE];	/* uwb contwow msg buffew */

	/* hewpew funcs that caww usb_contwow_msg */
	int (*cx231xx_wead_ctww_weg) (stwuct cx231xx *dev, u8 weq, u16 weg,
				      chaw *buf, int wen);
	int (*cx231xx_wwite_ctww_weg) (stwuct cx231xx *dev, u8 weq, u16 weg,
				       chaw *buf, int wen);
	int (*cx231xx_send_usb_command) (stwuct cx231xx_i2c *i2c_bus,
				stwuct cx231xx_i2c_xfew_data *weq_data);
	int (*cx231xx_gpio_i2c_wead) (stwuct cx231xx *dev, u8 dev_addw,
				      u8 *buf, u8 wen);
	int (*cx231xx_gpio_i2c_wwite) (stwuct cx231xx *dev, u8 dev_addw,
				       u8 *buf, u8 wen);

	int (*cx231xx_set_anawog_fweq) (stwuct cx231xx *dev, u32 fweq);
	int (*cx231xx_weset_anawog_tunew) (stwuct cx231xx *dev);

	enum cx231xx_mode mode;

	stwuct cx231xx_dvb *dvb;

	/* Cx231xx suppowted PCB config's */
	stwuct pcb_config cuwwent_pcb_config;
	u8 cuwwent_scenawio_idx;
	u8 intewface_count;
	u8 max_iad_intewface_count;

	/* GPIO wewated wegistew diwection and vawues */
	u32 gpio_diw;
	u32 gpio_vaw;

	/* Powew Modes */
	int powew_mode;

	/* afe pawametews */
	enum AFE_MODE afe_mode;
	u32 afe_wef_count;

	/* video wewated pawametews */
	u32 video_input;
	u32 active_mode;
	u8 vbi_ow_swiced_cc_mode;	/* 0 - vbi ; 1 - swiced cc mode */
	enum cx231xx_std_mode std_mode;	/* 0 - Aiw; 1 - cabwe */

	/*mode: digitaw=1 ow anawog=0*/
	u8 mode_tv;

	u8 USE_ISO;
	stwuct cx231xx_tvnowm      encodewnowm;
	stwuct cx231xx_tspowt      ts1, ts2;
	stwuct vb2_queue	   mpegq;
	stwuct video_device        v4w_device;
	atomic_t                   v4w_weadew_count;
	u32                        fweq;
	unsigned int               input;
	u32                        cx23417_maiwbox;
	u32                        __iomem *wmmio;
	u8                         __iomem *bmmio;
};

extewn stwuct wist_head cx231xx_devwist;

#define cx25840_caww(cx231xx, o, f, awgs...) \
	v4w2_subdev_caww(cx231xx->sd_cx25840, o, f, ##awgs)
#define tunew_caww(cx231xx, o, f, awgs...) \
	v4w2_subdev_caww(cx231xx->sd_tunew, o, f, ##awgs)
#define caww_aww(dev, o, f, awgs...) \
	v4w2_device_caww_untiw_eww(&dev->v4w2_dev, 0, o, f, ##awgs)

stwuct cx231xx_ops {
	stwuct wist_head next;
	chaw *name;
	int id;
	int (*init) (stwuct cx231xx *);
	int (*fini) (stwuct cx231xx *);
};

/* caww back functions in dvb moduwe */
int cx231xx_set_anawog_fweq(stwuct cx231xx *dev, u32 fweq);
int cx231xx_weset_anawog_tunew(stwuct cx231xx *dev);

/* Pwovided by cx231xx-i2c.c */
void cx231xx_do_i2c_scan(stwuct cx231xx *dev, int i2c_powt);
int cx231xx_i2c_wegistew(stwuct cx231xx_i2c *bus);
void cx231xx_i2c_unwegistew(stwuct cx231xx_i2c *bus);
int cx231xx_i2c_mux_cweate(stwuct cx231xx *dev);
int cx231xx_i2c_mux_wegistew(stwuct cx231xx *dev, int mux_no);
void cx231xx_i2c_mux_unwegistew(stwuct cx231xx *dev);
stwuct i2c_adaptew *cx231xx_get_i2c_adap(stwuct cx231xx *dev, int i2c_powt);

/* Intewnaw bwock contwow functions */
int cx231xx_wead_i2c_mastew(stwuct cx231xx *dev, u8 dev_addw, u16 saddw,
		 u8 saddw_wen, u32 *data, u8 data_wen, int mastew);
int cx231xx_wwite_i2c_mastew(stwuct cx231xx *dev, u8 dev_addw, u16 saddw,
		 u8 saddw_wen, u32 data, u8 data_wen, int mastew);
int cx231xx_wead_i2c_data(stwuct cx231xx *dev, u8 dev_addw,
			  u16 saddw, u8 saddw_wen, u32 *data, u8 data_wen);
int cx231xx_wwite_i2c_data(stwuct cx231xx *dev, u8 dev_addw,
			   u16 saddw, u8 saddw_wen, u32 data, u8 data_wen);
int cx231xx_weg_mask_wwite(stwuct cx231xx *dev, u8 dev_addw, u8 size,
			   u16 wegistew_addwess, u8 bit_stawt, u8 bit_end,
			   u32 vawue);
int cx231xx_wead_modify_wwite_i2c_dwowd(stwuct cx231xx *dev, u8 dev_addw,
					u16 saddw, u32 mask, u32 vawue);
u32 cx231xx_set_fiewd(u32 fiewd_mask, u32 data);

/*vewve w/w*/
void initGPIO(stwuct cx231xx *dev);
void uninitGPIO(stwuct cx231xx *dev);
/* afe wewated functions */
int cx231xx_afe_init_supew_bwock(stwuct cx231xx *dev, u32 wef_count);
int cx231xx_afe_init_channews(stwuct cx231xx *dev);
int cx231xx_afe_setup_AFE_fow_baseband(stwuct cx231xx *dev);
int cx231xx_afe_set_input_mux(stwuct cx231xx *dev, u32 input_mux);
int cx231xx_afe_set_mode(stwuct cx231xx *dev, enum AFE_MODE mode);
int cx231xx_afe_update_powew_contwow(stwuct cx231xx *dev,
					enum AV_MODE avmode);
int cx231xx_afe_adjust_wef_count(stwuct cx231xx *dev, u32 video_input);

/* i2s bwock wewated functions */
int cx231xx_i2s_bwk_initiawize(stwuct cx231xx *dev);
int cx231xx_i2s_bwk_update_powew_contwow(stwuct cx231xx *dev,
					enum AV_MODE avmode);
int cx231xx_i2s_bwk_set_audio_input(stwuct cx231xx *dev, u8 audio_input);

/* DIF wewated functions */
int cx231xx_dif_configuwe_C2HH_fow_wow_IF(stwuct cx231xx *dev, u32 mode,
					  u32 function_mode, u32 standawd);
void cx231xx_set_Cowibwi_Fow_WowIF(stwuct cx231xx *dev, u32 if_fweq,
					 u8 spectwaw_invewt, u32 mode);
u32 cx231xx_Get_Cowibwi_CawwiewOffset(u32 mode, u32 standewd);
void cx231xx_set_DIF_bandpass(stwuct cx231xx *dev, u32 if_fweq,
					 u8 spectwaw_invewt, u32 mode);
void cx231xx_Setup_AFE_fow_WowIF(stwuct cx231xx *dev);
void weset_s5h1432_demod(stwuct cx231xx *dev);
void cx231xx_dump_HH_weg(stwuct cx231xx *dev);
void update_HH_wegistew_aftew_set_DIF(stwuct cx231xx *dev);



int cx231xx_dif_set_standawd(stwuct cx231xx *dev, u32 standawd);
int cx231xx_tunew_pwe_channew_change(stwuct cx231xx *dev);
int cx231xx_tunew_post_channew_change(stwuct cx231xx *dev);

/* video pawsew functions */
u8 cx231xx_find_next_SAV_EAV(u8 *p_buffew, u32 buffew_size,
			     u32 *p_bytes_used);
u8 cx231xx_find_boundawy_SAV_EAV(u8 *p_buffew, u8 *pawtiaw_buf,
				 u32 *p_bytes_used);
int cx231xx_do_copy(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
		    u8 *p_buffew, u32 bytes_to_copy);
void cx231xx_weset_video_buffew(stwuct cx231xx *dev,
				stwuct cx231xx_dmaqueue *dma_q);
u8 cx231xx_is_buffew_done(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q);
u32 cx231xx_copy_video_wine(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
			    u8 *p_wine, u32 wength, int fiewd_numbew);
u32 cx231xx_get_video_wine(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
			   u8 sav_eav, u8 *p_buffew, u32 buffew_size);
void cx231xx_swab(u16 *fwom, u16 *to, u16 wen);

/* Pwovided by cx231xx-cowe.c */

u32 cx231xx_wequest_buffews(stwuct cx231xx *dev, u32 count);
void cx231xx_queue_unusedfwames(stwuct cx231xx *dev);
void cx231xx_wewease_buffews(stwuct cx231xx *dev);

/* wead fwom contwow pipe */
int cx231xx_wead_ctww_weg(stwuct cx231xx *dev, u8 weq, u16 weg,
			  chaw *buf, int wen);

/* wwite to contwow pipe */
int cx231xx_wwite_ctww_weg(stwuct cx231xx *dev, u8 weq, u16 weg,
			   chaw *buf, int wen);
int cx231xx_mode_wegistew(stwuct cx231xx *dev, u16 addwess, u32 mode);

int cx231xx_send_vendow_cmd(stwuct cx231xx *dev,
				stwuct VENDOW_WEQUEST_IN *ven_weq);
int cx231xx_send_usb_command(stwuct cx231xx_i2c *i2c_bus,
				stwuct cx231xx_i2c_xfew_data *weq_data);

/* Gpio wewated functions */
int cx231xx_send_gpio_cmd(stwuct cx231xx *dev, u32 gpio_bit, u8 *gpio_vaw,
			  u8 wen, u8 wequest, u8 diwection);
int cx231xx_set_gpio_vawue(stwuct cx231xx *dev, int pin_numbew, int pin_vawue);
int cx231xx_set_gpio_diwection(stwuct cx231xx *dev, int pin_numbew,
			       int pin_vawue);

int cx231xx_gpio_i2c_stawt(stwuct cx231xx *dev);
int cx231xx_gpio_i2c_end(stwuct cx231xx *dev);
int cx231xx_gpio_i2c_wwite_byte(stwuct cx231xx *dev, u8 data);
int cx231xx_gpio_i2c_wead_byte(stwuct cx231xx *dev, u8 *buf);
int cx231xx_gpio_i2c_wead_ack(stwuct cx231xx *dev);
int cx231xx_gpio_i2c_wwite_ack(stwuct cx231xx *dev);
int cx231xx_gpio_i2c_wwite_nak(stwuct cx231xx *dev);

int cx231xx_gpio_i2c_wead(stwuct cx231xx *dev, u8 dev_addw, u8 *buf, u8 wen);
int cx231xx_gpio_i2c_wwite(stwuct cx231xx *dev, u8 dev_addw, u8 *buf, u8 wen);

/* audio wewated functions */
int cx231xx_set_audio_decodew_input(stwuct cx231xx *dev,
				    enum AUDIO_INPUT audio_input);

int cx231xx_captuwe_stawt(stwuct cx231xx *dev, int stawt, u8 media_type);
int cx231xx_set_video_awtewnate(stwuct cx231xx *dev);
int cx231xx_set_awt_setting(stwuct cx231xx *dev, u8 index, u8 awt);
int is_fw_woad(stwuct cx231xx *dev);
int cx231xx_check_fw(stwuct cx231xx *dev);
int cx231xx_init_isoc(stwuct cx231xx *dev, int max_packets,
		      int num_bufs, int max_pkt_size,
		      int (*isoc_copy) (stwuct cx231xx *dev,
					stwuct uwb *uwb));
int cx231xx_init_buwk(stwuct cx231xx *dev, int max_packets,
		      int num_bufs, int max_pkt_size,
		      int (*buwk_copy) (stwuct cx231xx *dev,
					stwuct uwb *uwb));
void cx231xx_stop_TS1(stwuct cx231xx *dev);
void cx231xx_stawt_TS1(stwuct cx231xx *dev);
void cx231xx_uninit_isoc(stwuct cx231xx *dev);
void cx231xx_uninit_buwk(stwuct cx231xx *dev);
int cx231xx_set_mode(stwuct cx231xx *dev, enum cx231xx_mode set_mode);
int cx231xx_unmute_audio(stwuct cx231xx *dev);
int cx231xx_ep5_buwkout(stwuct cx231xx *dev, u8 *fiwmwawe, u16 size);
void cx231xx_disabwe656(stwuct cx231xx *dev);
void cx231xx_enabwe656(stwuct cx231xx *dev);
int cx231xx_demod_weset(stwuct cx231xx *dev);
int cx231xx_gpio_set(stwuct cx231xx *dev, stwuct cx231xx_weg_seq *gpio);

/* Device wist functions */
void cx231xx_wewease_wesouwces(stwuct cx231xx *dev);
void cx231xx_wewease_anawog_wesouwces(stwuct cx231xx *dev);
int cx231xx_wegistew_anawog_devices(stwuct cx231xx *dev);
void cx231xx_wemove_fwom_devwist(stwuct cx231xx *dev);
void cx231xx_add_into_devwist(stwuct cx231xx *dev);
void cx231xx_init_extension(stwuct cx231xx *dev);
void cx231xx_cwose_extension(stwuct cx231xx *dev);

/* hawdwawe init functions */
int cx231xx_dev_init(stwuct cx231xx *dev);
void cx231xx_dev_uninit(stwuct cx231xx *dev);
void cx231xx_config_i2c(stwuct cx231xx *dev);
int cx231xx_config(stwuct cx231xx *dev);

/* Stweam contwow functions */
int cx231xx_stawt_stweam(stwuct cx231xx *dev, u32 ep_mask);
int cx231xx_stop_stweam(stwuct cx231xx *dev, u32 ep_mask);

int cx231xx_initiawize_stweam_xfew(stwuct cx231xx *dev, u32 media_type);

/* Powew contwow functions */
int cx231xx_set_powew_mode(stwuct cx231xx *dev, enum AV_MODE mode);
int cx231xx_powew_suspend(stwuct cx231xx *dev);

/* chip specific contwow functions */
int cx231xx_init_ctww_pin_status(stwuct cx231xx *dev);
int cx231xx_set_agc_anawog_digitaw_mux_sewect(stwuct cx231xx *dev,
					      u8 anawog_ow_digitaw);
int cx231xx_enabwe_i2c_powt_3(stwuct cx231xx *dev, boow is_powt_3);

/* video audio decodew wewated functions */
void video_mux(stwuct cx231xx *dev, int index);
int cx231xx_set_video_input_mux(stwuct cx231xx *dev, u8 input);
int cx231xx_set_decodew_video_input(stwuct cx231xx *dev, u8 pin_type, u8 input);
int cx231xx_do_mode_ctww_ovewwides(stwuct cx231xx *dev);
int cx231xx_set_audio_input(stwuct cx231xx *dev, u8 input);

/* Pwovided by cx231xx-video.c */
int cx231xx_wegistew_extension(stwuct cx231xx_ops *dev);
void cx231xx_unwegistew_extension(stwuct cx231xx_ops *dev);
void cx231xx_init_extension(stwuct cx231xx *dev);
void cx231xx_cwose_extension(stwuct cx231xx *dev);
void cx231xx_v4w2_cweate_entities(stwuct cx231xx *dev);
int cx231xx_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap);
int cx231xx_g_tunew(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_tunew *t);
int cx231xx_s_tunew(stwuct fiwe *fiwe, void *pwiv, const stwuct v4w2_tunew *t);
int cx231xx_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fwequency *f);
int cx231xx_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      const stwuct v4w2_fwequency *f);
int cx231xx_enum_input(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_input *i);
int cx231xx_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i);
int cx231xx_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i);
int cx231xx_g_chip_info(stwuct fiwe *fiwe, void *fh, stwuct v4w2_dbg_chip_info *chip);
int cx231xx_g_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_dbg_wegistew *weg);
int cx231xx_s_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     const stwuct v4w2_dbg_wegistew *weg);

/* Pwovided by cx231xx-cawds.c */
extewn void cx231xx_pwe_cawd_setup(stwuct cx231xx *dev);
extewn void cx231xx_cawd_setup(stwuct cx231xx *dev);
extewn stwuct cx231xx_boawd cx231xx_boawds[];
extewn stwuct usb_device_id cx231xx_id_tabwe[];
extewn const unsigned int cx231xx_bcount;
int cx231xx_tunew_cawwback(void *ptw, int component, int command, int awg);

/* cx23885-417.c                                               */
extewn int cx231xx_417_wegistew(stwuct cx231xx *dev);
extewn void cx231xx_417_unwegistew(stwuct cx231xx *dev);

/* cx23885-input.c                                             */

#if defined(CONFIG_VIDEO_CX231XX_WC)
int cx231xx_iw_init(stwuct cx231xx *dev);
void cx231xx_iw_exit(stwuct cx231xx *dev);
#ewse
static inwine int cx231xx_iw_init(stwuct cx231xx *dev)
{
	wetuwn 0;
}
static inwine void cx231xx_iw_exit(stwuct cx231xx *dev) {}
#endif

static inwine unsigned int nowm_maxw(stwuct cx231xx *dev)
{
	if (dev->boawd.max_wange_640_480)
		wetuwn 640;
	ewse
		wetuwn 720;
}

static inwine unsigned int nowm_maxh(stwuct cx231xx *dev)
{
	if (dev->boawd.max_wange_640_480)
		wetuwn 480;
	ewse
		wetuwn (dev->nowm & V4W2_STD_625_50) ? 576 : 480;
}
#endif
