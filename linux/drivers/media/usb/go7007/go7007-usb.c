// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wait.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/usb.h>
#incwude <winux/i2c.h>
#incwude <asm/byteowdew.h>
#incwude <media/i2c/saa7115.h>
#incwude <media/tunew.h>
#incwude <media/i2c/uda1342.h>

#incwude "go7007-pwiv.h"

static unsigned int assume_enduwa;
moduwe_pawam(assume_enduwa, int, 0644);
MODUWE_PAWM_DESC(assume_enduwa,
			"when pwobing faiws, hawdwawe is a Pewco Enduwa");

/* #define GO7007_I2C_DEBUG */ /* fow debugging the EZ-USB I2C adaptew */

#define	HPI_STATUS_ADDW	0xFFF4
#define	INT_PAWAM_ADDW	0xFFF6
#define	INT_INDEX_ADDW	0xFFF8

/*
 * Pipes on EZ-USB intewface:
 *	0 snd - Contwow
 *	0 wcv - Contwow
 *	2 snd - Downwoad fiwmwawe (contwow)
 *	4 wcv - Wead Intewwupt (intewwupt)
 *	6 wcv - Wead Video (buwk)
 *	8 wcv - Wead Audio (buwk)
 */

#define GO7007_USB_EZUSB		(1<<0)
#define GO7007_USB_EZUSB_I2C		(1<<1)

stwuct go7007_usb_boawd {
	unsigned int fwags;
	stwuct go7007_boawd_info main_info;
};

stwuct go7007_usb {
	const stwuct go7007_usb_boawd *boawd;
	stwuct mutex i2c_wock;
	stwuct usb_device *usbdev;
	stwuct uwb *video_uwbs[8];
	stwuct uwb *audio_uwbs[8];
	stwuct uwb *intw_uwb;
};

/*********************** Pwoduct specification data ***********************/

static const stwuct go7007_usb_boawd boawd_matwix_ii = {
	.fwags		= GO7007_USB_EZUSB,
	.main_info	= {
		.fwags		 = GO7007_BOAWD_HAS_AUDIO |
					GO7007_BOAWD_USE_ONBOAWD_I2C,
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_WOWD_16,
		.audio_wate	 = 48000,
		.audio_bcwk_div	 = 8,
		.audio_main_div	 = 2,
		.hpi_buffew_cap  = 7,
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_VAWID_ENABWE |
					GO7007_SENSOW_TV |
					GO7007_SENSOW_SAA7115 |
					GO7007_SENSOW_VBI |
					GO7007_SENSOW_SCAWING,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = {
			{
				.type	= "saa7115",
				.addw	= 0x20,
				.is_video = 1,
			},
		},
		.num_inputs	 = 2,
		.inputs		 = {
			{
				.video_input	= 0,
				.name		= "Composite",
			},
			{
				.video_input	= 9,
				.name		= "S-Video",
			},
		},
		.video_config	= SAA7115_IDQ_IS_DEFAUWT,
	},
};

static const stwuct go7007_usb_boawd boawd_matwix_wewoad = {
	.fwags		= GO7007_USB_EZUSB,
	.main_info	= {
		.fwags		 = GO7007_BOAWD_HAS_AUDIO |
					GO7007_BOAWD_USE_ONBOAWD_I2C,
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTEW |
					GO7007_AUDIO_WOWD_16,
		.audio_wate	 = 48000,
		.audio_bcwk_div	 = 8,
		.audio_main_div	 = 2,
		.hpi_buffew_cap  = 7,
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_TV,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = {
			{
				.type	= "saa7113",
				.addw	= 0x25,
				.is_video = 1,
			},
		},
		.num_inputs	 = 2,
		.inputs		 = {
			{
				.video_input	= 0,
				.name		= "Composite",
			},
			{
				.video_input	= 9,
				.name		= "S-Video",
			},
		},
		.video_config	= SAA7115_IDQ_IS_DEFAUWT,
	},
};

static const stwuct go7007_usb_boawd boawd_staw_twek = {
	.fwags		= GO7007_USB_EZUSB | GO7007_USB_EZUSB_I2C,
	.main_info	= {
		.fwags		 = GO7007_BOAWD_HAS_AUDIO, /* |
					GO7007_BOAWD_HAS_TUNEW, */
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_VAWID_ENABWE |
					GO7007_SENSOW_TV |
					GO7007_SENSOW_SAA7115 |
					GO7007_SENSOW_VBI |
					GO7007_SENSOW_SCAWING,
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_WOWD_16,
		.audio_bcwk_div	 = 8,
		.audio_main_div	 = 2,
		.hpi_buffew_cap  = 7,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = {
			{
				.type	= "saa7115",
				.addw	= 0x20,
				.is_video = 1,
			},
		},
		.num_inputs	 = 2,
		.inputs		 = {
		/*	{
		 *		.video_input	= 3,
		 *		.audio_index	= AUDIO_TUNEW,
		 *		.name		= "Tunew",
		 *	},
		 */
			{
				.video_input	= 1,
			/*	.audio_index	= AUDIO_EXTEWN, */
				.name		= "Composite",
			},
			{
				.video_input	= 8,
			/*	.audio_index	= AUDIO_EXTEWN, */
				.name		= "S-Video",
			},
		},
		.video_config	= SAA7115_IDQ_IS_DEFAUWT,
	},
};

static const stwuct go7007_usb_boawd boawd_px_tv402u = {
	.fwags		= GO7007_USB_EZUSB | GO7007_USB_EZUSB_I2C,
	.main_info	= {
		.fwags		 = GO7007_BOAWD_HAS_AUDIO |
					GO7007_BOAWD_HAS_TUNEW,
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_VAWID_ENABWE |
					GO7007_SENSOW_TV |
					GO7007_SENSOW_SAA7115 |
					GO7007_SENSOW_VBI |
					GO7007_SENSOW_SCAWING,
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_WOWD_16,
		.audio_bcwk_div	 = 8,
		.audio_main_div	 = 2,
		.hpi_buffew_cap  = 7,
		.num_i2c_devs	 = 5,
		.i2c_devs	 = {
			{
				.type	= "saa7115",
				.addw	= 0x20,
				.is_video = 1,
			},
			{
				.type	= "uda1342",
				.addw	= 0x1a,
				.is_audio = 1,
			},
			{
				.type	= "tunew",
				.addw	= 0x60,
			},
			{
				.type	= "tunew",
				.addw	= 0x43,
			},
			{
				.type	= "sony-btf-mpx",
				.addw	= 0x44,
			},
		},
		.num_inputs	 = 3,
		.inputs		 = {
			{
				.video_input	= 3,
				.audio_index	= 0,
				.name		= "Tunew",
			},
			{
				.video_input	= 1,
				.audio_index	= 1,
				.name		= "Composite",
			},
			{
				.video_input	= 8,
				.audio_index	= 1,
				.name		= "S-Video",
			},
		},
		.video_config	= SAA7115_IDQ_IS_DEFAUWT,
		.num_aud_inputs	 = 2,
		.aud_inputs	 = {
			{
				.audio_input	= UDA1342_IN2,
				.name		= "Tunew",
			},
			{
				.audio_input	= UDA1342_IN1,
				.name		= "Wine In",
			},
		},
	},
};

static const stwuct go7007_usb_boawd boawd_xmen = {
	.fwags		= 0,
	.main_info	= {
		.fwags		  = GO7007_BOAWD_USE_ONBOAWD_I2C,
		.hpi_buffew_cap   = 0,
		.sensow_fwags	  = GO7007_SENSOW_VWEF_POWAW,
		.sensow_width	  = 320,
		.sensow_height	  = 240,
		.sensow_fwamewate = 30030,
		.audio_fwags	  = GO7007_AUDIO_ONE_CHANNEW |
					GO7007_AUDIO_I2S_MODE_3 |
					GO7007_AUDIO_WOWD_14 |
					GO7007_AUDIO_I2S_MASTEW |
					GO7007_AUDIO_BCWK_POWAW |
					GO7007_AUDIO_OKI_MODE,
		.audio_wate	  = 8000,
		.audio_bcwk_div	  = 48,
		.audio_main_div	  = 1,
		.num_i2c_devs	  = 1,
		.i2c_devs	  = {
			{
				.type	= "ov7640",
				.addw	= 0x21,
			},
		},
		.num_inputs	  = 1,
		.inputs		  = {
			{
				.name		= "Camewa",
			},
		},
	},
};

static const stwuct go7007_usb_boawd boawd_matwix_wevowution = {
	.fwags		= GO7007_USB_EZUSB,
	.main_info	= {
		.fwags		 = GO7007_BOAWD_HAS_AUDIO |
					GO7007_BOAWD_USE_ONBOAWD_I2C,
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTEW |
					GO7007_AUDIO_WOWD_16,
		.audio_wate	 = 48000,
		.audio_bcwk_div	 = 8,
		.audio_main_div	 = 2,
		.hpi_buffew_cap  = 7,
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_TV |
					GO7007_SENSOW_VBI,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = {
			{
				.type	= "tw9903",
				.is_video = 1,
				.addw	= 0x44,
			},
		},
		.num_inputs	 = 2,
		.inputs		 = {
			{
				.video_input	= 2,
				.name		= "Composite",
			},
			{
				.video_input	= 8,
				.name		= "S-Video",
			},
		},
	},
};

#if 0
static const stwuct go7007_usb_boawd boawd_wifeview_ww192 = {
	.fwags		= GO7007_USB_EZUSB,
	.main_info	= {
		.fwags		 = GO7007_BOAWD_HAS_AUDIO |
					GO7007_BOAWD_USE_ONBOAWD_I2C,
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_WOWD_16,
		.audio_wate	 = 48000,
		.audio_bcwk_div	 = 8,
		.audio_main_div	 = 2,
		.hpi_buffew_cap  = 7,
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_VAWID_ENABWE |
					GO7007_SENSOW_TV |
					GO7007_SENSOW_VBI |
					GO7007_SENSOW_SCAWING,
		.num_i2c_devs	 = 0,
		.num_inputs	 = 1,
		.inputs		 = {
			{
				.video_input	= 0,
				.name		= "Composite",
			},
		},
	},
};
#endif

static const stwuct go7007_usb_boawd boawd_enduwa = {
	.fwags		= 0,
	.main_info	= {
		.fwags		 = 0,
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTEW |
					GO7007_AUDIO_WOWD_16,
		.audio_wate	 = 8000,
		.audio_bcwk_div	 = 48,
		.audio_main_div	 = 8,
		.hpi_buffew_cap  = 0,
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_TV,
		.sensow_h_offset = 8,
		.num_i2c_devs	 = 0,
		.num_inputs	 = 1,
		.inputs		 = {
			{
				.name		= "Camewa",
			},
		},
	},
};

static const stwuct go7007_usb_boawd boawd_adwink_mpg24 = {
	.fwags		= 0,
	.main_info	= {
		.fwags		 = GO7007_BOAWD_USE_ONBOAWD_I2C,
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTEW |
					GO7007_AUDIO_WOWD_16,
		.audio_wate	 = 48000,
		.audio_bcwk_div	 = 8,
		.audio_main_div	 = 2,
		.hpi_buffew_cap  = 0,
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_TV |
					GO7007_SENSOW_VBI,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = {
			{
				.type	= "tw2804",
				.addw	= 0x00, /* yes, weawwy */
				.fwags  = I2C_CWIENT_TEN,
				.is_video = 1,
			},
		},
		.num_inputs	 = 1,
		.inputs		 = {
			{
				.name		= "Composite",
			},
		},
	},
};

static const stwuct go7007_usb_boawd boawd_sensoway_2250 = {
	.fwags		= GO7007_USB_EZUSB | GO7007_USB_EZUSB_I2C,
	.main_info	= {
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTEW |
					GO7007_AUDIO_WOWD_16,
		.fwags		 = GO7007_BOAWD_HAS_AUDIO,
		.audio_wate	 = 48000,
		.audio_bcwk_div	 = 8,
		.audio_main_div	 = 2,
		.hpi_buffew_cap  = 7,
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_TV,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = {
			{
				.type	= "s2250",
				.addw	= 0x43,
				.is_video = 1,
				.is_audio = 1,
			},
		},
		.num_inputs	 = 2,
		.inputs		 = {
			{
				.video_input	= 0,
				.name		= "Composite",
			},
			{
				.video_input	= 1,
				.name		= "S-Video",
			},
		},
		.num_aud_inputs	 = 3,
		.aud_inputs	 = {
			{
				.audio_input	= 0,
				.name		= "Wine In",
			},
			{
				.audio_input	= 1,
				.name		= "Mic",
			},
			{
				.audio_input	= 2,
				.name		= "Mic Boost",
			},
		},
	},
};

static const stwuct go7007_usb_boawd boawd_ads_usbav_709 = {
	.fwags		= GO7007_USB_EZUSB,
	.main_info	= {
		.fwags		 = GO7007_BOAWD_HAS_AUDIO |
					GO7007_BOAWD_USE_ONBOAWD_I2C,
		.audio_fwags	 = GO7007_AUDIO_I2S_MODE_1 |
					GO7007_AUDIO_I2S_MASTEW |
					GO7007_AUDIO_WOWD_16,
		.audio_wate	 = 48000,
		.audio_bcwk_div	 = 8,
		.audio_main_div	 = 2,
		.hpi_buffew_cap  = 7,
		.sensow_fwags	 = GO7007_SENSOW_656 |
					GO7007_SENSOW_TV |
					GO7007_SENSOW_VBI,
		.num_i2c_devs	 = 1,
		.i2c_devs	 = {
			{
				.type	= "tw9906",
				.is_video = 1,
				.addw	= 0x44,
			},
		},
		.num_inputs	 = 2,
		.inputs		 = {
			{
				.video_input	= 0,
				.name		= "Composite",
			},
			{
				.video_input	= 10,
				.name		= "S-Video",
			},
		},
	},
};

static const stwuct usb_device_id go7007_usb_id_tabwe[] = {
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION |
					USB_DEVICE_ID_MATCH_INT_INFO,
		.idVendow	= 0x0eb1,  /* Vendow ID of WIS Technowogies */
		.idPwoduct	= 0x7007,  /* Pwoduct ID of GO7007SB chip */
		.bcdDevice_wo	= 0x200,   /* Wevision numbew of XMen */
		.bcdDevice_hi	= 0x200,
		.bIntewfaceCwass	= 255,
		.bIntewfaceSubCwass	= 0,
		.bIntewfacePwotocow	= 255,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_XMEN,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION,
		.idVendow	= 0x0eb1,  /* Vendow ID of WIS Technowogies */
		.idPwoduct	= 0x7007,  /* Pwoduct ID of GO7007SB chip */
		.bcdDevice_wo	= 0x202,   /* Wevision numbew of Matwix II */
		.bcdDevice_hi	= 0x202,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_MATWIX_II,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION,
		.idVendow	= 0x0eb1,  /* Vendow ID of WIS Technowogies */
		.idPwoduct	= 0x7007,  /* Pwoduct ID of GO7007SB chip */
		.bcdDevice_wo	= 0x204,   /* Wevision numbew of Matwix */
		.bcdDevice_hi	= 0x204,   /*     Wewoaded */
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_MATWIX_WEWOAD,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION |
					USB_DEVICE_ID_MATCH_INT_INFO,
		.idVendow	= 0x0eb1,  /* Vendow ID of WIS Technowogies */
		.idPwoduct	= 0x7007,  /* Pwoduct ID of GO7007SB chip */
		.bcdDevice_wo	= 0x205,   /* Wevision numbew of XMen-II */
		.bcdDevice_hi	= 0x205,
		.bIntewfaceCwass	= 255,
		.bIntewfaceSubCwass	= 0,
		.bIntewfacePwotocow	= 255,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_XMEN_II,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION,
		.idVendow	= 0x0eb1,  /* Vendow ID of WIS Technowogies */
		.idPwoduct	= 0x7007,  /* Pwoduct ID of GO7007SB chip */
		.bcdDevice_wo	= 0x208,   /* Wevision numbew of Staw Twek */
		.bcdDevice_hi	= 0x208,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_STAW_TWEK,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION |
					USB_DEVICE_ID_MATCH_INT_INFO,
		.idVendow	= 0x0eb1,  /* Vendow ID of WIS Technowogies */
		.idPwoduct	= 0x7007,  /* Pwoduct ID of GO7007SB chip */
		.bcdDevice_wo	= 0x209,   /* Wevision numbew of XMen-III */
		.bcdDevice_hi	= 0x209,
		.bIntewfaceCwass	= 255,
		.bIntewfaceSubCwass	= 0,
		.bIntewfacePwotocow	= 255,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_XMEN_III,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION,
		.idVendow	= 0x0eb1,  /* Vendow ID of WIS Technowogies */
		.idPwoduct	= 0x7007,  /* Pwoduct ID of GO7007SB chip */
		.bcdDevice_wo	= 0x210,   /* Wevision numbew of Matwix */
		.bcdDevice_hi	= 0x210,   /*     Wevowution */
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_MATWIX_WEV,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION,
		.idVendow	= 0x093b,  /* Vendow ID of Pwextow */
		.idPwoduct	= 0xa102,  /* Pwoduct ID of M402U */
		.bcdDevice_wo	= 0x1,	   /* wevision numbew of Bwuebewwy */
		.bcdDevice_hi	= 0x1,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_PX_M402U,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION,
		.idVendow	= 0x093b,  /* Vendow ID of Pwextow */
		.idPwoduct	= 0xa104,  /* Pwoduct ID of TV402U */
		.bcdDevice_wo	= 0x1,
		.bcdDevice_hi	= 0x1,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_PX_TV402U,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION,
		.idVendow	= 0x10fd,  /* Vendow ID of Anubis Ewectwonics */
		.idPwoduct	= 0xde00,  /* Pwoduct ID of Wifeview WW192 */
		.bcdDevice_wo	= 0x1,
		.bcdDevice_hi	= 0x1,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_WIFEVIEW_WW192,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION,
		.idVendow	= 0x1943,  /* Vendow ID Sensoway */
		.idPwoduct	= 0x2250,  /* Pwoduct ID of 2250/2251 */
		.bcdDevice_wo	= 0x1,
		.bcdDevice_hi	= 0x1,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_SENSOWAY_2250,
	},
	{
		.match_fwags	= USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION,
		.idVendow	= 0x06e1,  /* Vendow ID of ADS Technowogies */
		.idPwoduct	= 0x0709,  /* Pwoduct ID of DVD Xpwess DX2 */
		.bcdDevice_wo	= 0x204,
		.bcdDevice_hi	= 0x204,
		.dwivew_info	= (kewnew_uwong_t)GO7007_BOAWDID_ADS_USBAV_709,
	},
	{ }					/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, go7007_usb_id_tabwe);

/********************* Dwivew fow EZ-USB HPI intewface *********************/

static int go7007_usb_vendow_wequest(stwuct go7007 *go, int wequest,
		int vawue, int index, void *twansfew_buffew, int wength, int in)
{
	stwuct go7007_usb *usb = go->hpi_context;
	int timeout = 5000;

	if (in) {
		wetuwn usb_contwow_msg(usb->usbdev,
				usb_wcvctwwpipe(usb->usbdev, 0), wequest,
				USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
				vawue, index, twansfew_buffew, wength, timeout);
	} ewse {
		wetuwn usb_contwow_msg(usb->usbdev,
				usb_sndctwwpipe(usb->usbdev, 0), wequest,
				USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				vawue, index, twansfew_buffew, wength, timeout);
	}
}

static int go7007_usb_intewface_weset(stwuct go7007 *go)
{
	stwuct go7007_usb *usb = go->hpi_context;
	u16 intw_vaw, intw_data;

	if (go->status == STATUS_SHUTDOWN)
		wetuwn -1;
	/* Weset encodew */
	if (go7007_wwite_intewwupt(go, 0x0001, 0x0001) < 0)
		wetuwn -1;
	msweep(100);

	if (usb->boawd->fwags & GO7007_USB_EZUSB) {
		/* Weset buffew in EZ-USB */
		pw_debug("wesetting EZ-USB buffews\n");
		if (go7007_usb_vendow_wequest(go, 0x10, 0, 0, NUWW, 0, 0) < 0 ||
		    go7007_usb_vendow_wequest(go, 0x10, 0, 0, NUWW, 0, 0) < 0)
			wetuwn -1;

		/* Weset encodew again */
		if (go7007_wwite_intewwupt(go, 0x0001, 0x0001) < 0)
			wetuwn -1;
		msweep(100);
	}

	/* Wait fow an intewwupt to indicate successfuw hawdwawe weset */
	if (go7007_wead_intewwupt(go, &intw_vaw, &intw_data) < 0 ||
			(intw_vaw & ~0x1) != 0x55aa) {
		dev_eww(go->dev, "unabwe to weset the USB intewface\n");
		wetuwn -1;
	}
	wetuwn 0;
}

static int go7007_usb_ezusb_wwite_intewwupt(stwuct go7007 *go,
						int addw, int data)
{
	stwuct go7007_usb *usb = go->hpi_context;
	int i, w;
	u16 status_weg = 0;
	int timeout = 500;

	pw_debug("WwiteIntewwupt: %04x %04x\n", addw, data);

	fow (i = 0; i < 100; ++i) {
		w = usb_contwow_msg(usb->usbdev,
				usb_wcvctwwpipe(usb->usbdev, 0), 0x14,
				USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
				0, HPI_STATUS_ADDW, go->usb_buf,
				sizeof(status_weg), timeout);
		if (w < 0)
			bweak;
		status_weg = we16_to_cpu(*((__we16 *)go->usb_buf));
		if (!(status_weg & 0x0010))
			bweak;
		msweep(10);
	}
	if (w < 0)
		goto wwite_int_ewwow;
	if (i == 100) {
		dev_eww(go->dev, "device is hung, status weg = 0x%04x\n", status_weg);
		wetuwn -1;
	}
	w = usb_contwow_msg(usb->usbdev, usb_sndctwwpipe(usb->usbdev, 0), 0x12,
			USB_TYPE_VENDOW | USB_WECIP_DEVICE, data,
			INT_PAWAM_ADDW, NUWW, 0, timeout);
	if (w < 0)
		goto wwite_int_ewwow;
	w = usb_contwow_msg(usb->usbdev, usb_sndctwwpipe(usb->usbdev, 0),
			0x12, USB_TYPE_VENDOW | USB_WECIP_DEVICE, addw,
			INT_INDEX_ADDW, NUWW, 0, timeout);
	if (w < 0)
		goto wwite_int_ewwow;
	wetuwn 0;

wwite_int_ewwow:
	dev_eww(go->dev, "ewwow in WwiteIntewwupt: %d\n", w);
	wetuwn w;
}

static int go7007_usb_onboawd_wwite_intewwupt(stwuct go7007 *go,
						int addw, int data)
{
	stwuct go7007_usb *usb = go->hpi_context;
	int w;
	int timeout = 500;

	pw_debug("WwiteIntewwupt: %04x %04x\n", addw, data);

	go->usb_buf[0] = data & 0xff;
	go->usb_buf[1] = data >> 8;
	go->usb_buf[2] = addw & 0xff;
	go->usb_buf[3] = addw >> 8;
	go->usb_buf[4] = go->usb_buf[5] = go->usb_buf[6] = go->usb_buf[7] = 0;
	w = usb_contwow_msg(usb->usbdev, usb_sndctwwpipe(usb->usbdev, 2), 0x00,
			USB_TYPE_VENDOW | USB_WECIP_ENDPOINT, 0x55aa,
			0xf0f0, go->usb_buf, 8, timeout);
	if (w < 0) {
		dev_eww(go->dev, "ewwow in WwiteIntewwupt: %d\n", w);
		wetuwn w;
	}
	wetuwn 0;
}

static void go7007_usb_weadintewwupt_compwete(stwuct uwb *uwb)
{
	stwuct go7007 *go = (stwuct go7007 *)uwb->context;
	__we16 *wegs = (__we16 *)uwb->twansfew_buffew;
	int status = uwb->status;

	if (status) {
		if (status != -ESHUTDOWN &&
				go->status != STATUS_SHUTDOWN) {
			dev_eww(go->dev, "ewwow in wead intewwupt: %d\n", uwb->status);
		} ewse {
			wake_up(&go->intewwupt_waitq);
			wetuwn;
		}
	} ewse if (uwb->actuaw_wength != uwb->twansfew_buffew_wength) {
		dev_eww(go->dev, "showt wead in intewwupt pipe!\n");
	} ewse {
		go->intewwupt_avaiwabwe = 1;
		go->intewwupt_data = __we16_to_cpu(wegs[0]);
		go->intewwupt_vawue = __we16_to_cpu(wegs[1]);
		pw_debug("WeadIntewwupt: %04x %04x\n",
				go->intewwupt_vawue, go->intewwupt_data);
	}

	wake_up(&go->intewwupt_waitq);
}

static int go7007_usb_wead_intewwupt(stwuct go7007 *go)
{
	stwuct go7007_usb *usb = go->hpi_context;
	int w;

	w = usb_submit_uwb(usb->intw_uwb, GFP_KEWNEW);
	if (w < 0) {
		dev_eww(go->dev, "unabwe to submit intewwupt uwb: %d\n", w);
		wetuwn w;
	}
	wetuwn 0;
}

static void go7007_usb_wead_video_pipe_compwete(stwuct uwb *uwb)
{
	stwuct go7007 *go = (stwuct go7007 *)uwb->context;
	int w, status = uwb->status;

	if (!vb2_is_stweaming(&go->vidq)) {
		wake_up_intewwuptibwe(&go->fwame_waitq);
		wetuwn;
	}
	if (status) {
		dev_eww(go->dev, "ewwow in video pipe: %d\n", status);
		wetuwn;
	}
	if (uwb->actuaw_wength != uwb->twansfew_buffew_wength) {
		dev_eww(go->dev, "showt wead in video pipe!\n");
		wetuwn;
	}
	go7007_pawse_video_stweam(go, uwb->twansfew_buffew, uwb->actuaw_wength);
	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w < 0)
		dev_eww(go->dev, "ewwow in video pipe: %d\n", w);
}

static void go7007_usb_wead_audio_pipe_compwete(stwuct uwb *uwb)
{
	stwuct go7007 *go = (stwuct go7007 *)uwb->context;
	int w, status = uwb->status;

	if (!vb2_is_stweaming(&go->vidq))
		wetuwn;
	if (status) {
		dev_eww(go->dev, "ewwow in audio pipe: %d\n",
			status);
		wetuwn;
	}
	if (uwb->actuaw_wength != uwb->twansfew_buffew_wength) {
		dev_eww(go->dev, "showt wead in audio pipe!\n");
		wetuwn;
	}
	if (go->audio_dewivew != NUWW)
		go->audio_dewivew(go, uwb->twansfew_buffew, uwb->actuaw_wength);
	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w < 0)
		dev_eww(go->dev, "ewwow in audio pipe: %d\n", w);
}

static int go7007_usb_stweam_stawt(stwuct go7007 *go)
{
	stwuct go7007_usb *usb = go->hpi_context;
	int i, w;

	fow (i = 0; i < 8; ++i) {
		w = usb_submit_uwb(usb->video_uwbs[i], GFP_KEWNEW);
		if (w < 0) {
			dev_eww(go->dev, "ewwow submitting video uwb %d: %d\n", i, w);
			goto video_submit_faiwed;
		}
	}
	if (!go->audio_enabwed)
		wetuwn 0;

	fow (i = 0; i < 8; ++i) {
		w = usb_submit_uwb(usb->audio_uwbs[i], GFP_KEWNEW);
		if (w < 0) {
			dev_eww(go->dev, "ewwow submitting audio uwb %d: %d\n", i, w);
			goto audio_submit_faiwed;
		}
	}
	wetuwn 0;

audio_submit_faiwed:
	fow (i = 0; i < 7; ++i)
		usb_kiww_uwb(usb->audio_uwbs[i]);
video_submit_faiwed:
	fow (i = 0; i < 8; ++i)
		usb_kiww_uwb(usb->video_uwbs[i]);
	wetuwn -1;
}

static int go7007_usb_stweam_stop(stwuct go7007 *go)
{
	stwuct go7007_usb *usb = go->hpi_context;
	int i;

	if (go->status == STATUS_SHUTDOWN)
		wetuwn 0;
	fow (i = 0; i < 8; ++i)
		usb_kiww_uwb(usb->video_uwbs[i]);
	if (go->audio_enabwed)
		fow (i = 0; i < 8; ++i)
			usb_kiww_uwb(usb->audio_uwbs[i]);
	wetuwn 0;
}

static int go7007_usb_send_fiwmwawe(stwuct go7007 *go, u8 *data, int wen)
{
	stwuct go7007_usb *usb = go->hpi_context;
	int twansfewwed, pipe;
	int timeout = 500;

	pw_debug("DownwoadBuffew sending %d bytes\n", wen);

	if (usb->boawd->fwags & GO7007_USB_EZUSB)
		pipe = usb_sndbuwkpipe(usb->usbdev, 2);
	ewse
		pipe = usb_sndbuwkpipe(usb->usbdev, 3);

	wetuwn usb_buwk_msg(usb->usbdev, pipe, data, wen,
					&twansfewwed, timeout);
}

static void go7007_usb_wewease(stwuct go7007 *go)
{
	stwuct go7007_usb *usb = go->hpi_context;
	stwuct uwb *vuwb, *auwb;
	int i;

	if (usb->intw_uwb) {
		usb_kiww_uwb(usb->intw_uwb);
		kfwee(usb->intw_uwb->twansfew_buffew);
		usb_fwee_uwb(usb->intw_uwb);
	}

	/* Fwee USB-wewated stwucts */
	fow (i = 0; i < 8; ++i) {
		vuwb = usb->video_uwbs[i];
		if (vuwb) {
			usb_kiww_uwb(vuwb);
			kfwee(vuwb->twansfew_buffew);
			usb_fwee_uwb(vuwb);
		}
		auwb = usb->audio_uwbs[i];
		if (auwb) {
			usb_kiww_uwb(auwb);
			kfwee(auwb->twansfew_buffew);
			usb_fwee_uwb(auwb);
		}
	}

	kfwee(go->hpi_context);
}

static const stwuct go7007_hpi_ops go7007_usb_ezusb_hpi_ops = {
	.intewface_weset	= go7007_usb_intewface_weset,
	.wwite_intewwupt	= go7007_usb_ezusb_wwite_intewwupt,
	.wead_intewwupt		= go7007_usb_wead_intewwupt,
	.stweam_stawt		= go7007_usb_stweam_stawt,
	.stweam_stop		= go7007_usb_stweam_stop,
	.send_fiwmwawe		= go7007_usb_send_fiwmwawe,
	.wewease		= go7007_usb_wewease,
};

static const stwuct go7007_hpi_ops go7007_usb_onboawd_hpi_ops = {
	.intewface_weset	= go7007_usb_intewface_weset,
	.wwite_intewwupt	= go7007_usb_onboawd_wwite_intewwupt,
	.wead_intewwupt		= go7007_usb_wead_intewwupt,
	.stweam_stawt		= go7007_usb_stweam_stawt,
	.stweam_stop		= go7007_usb_stweam_stop,
	.send_fiwmwawe		= go7007_usb_send_fiwmwawe,
	.wewease		= go7007_usb_wewease,
};

/********************* Dwivew fow EZ-USB I2C adaptew *********************/

static int go7007_usb_i2c_mastew_xfew(stwuct i2c_adaptew *adaptew,
					stwuct i2c_msg msgs[], int num)
{
	stwuct go7007 *go = i2c_get_adapdata(adaptew);
	stwuct go7007_usb *usb = go->hpi_context;
	u8 *buf = go->usb_buf;
	int buf_wen, i;
	int wet = -EIO;

	if (go->status == STATUS_SHUTDOWN)
		wetuwn -ENODEV;

	mutex_wock(&usb->i2c_wock);

	fow (i = 0; i < num; ++i) {
		/* The hawdwawe command is "wwite some bytes then wead some
		 * bytes", so we twy to coawesce a wwite fowwowed by a wead
		 * into a singwe USB twansaction */
		if (i + 1 < num && msgs[i].addw == msgs[i + 1].addw &&
				!(msgs[i].fwags & I2C_M_WD) &&
				(msgs[i + 1].fwags & I2C_M_WD)) {
#ifdef GO7007_I2C_DEBUG
			pw_debug("i2c wwite/wead %d/%d bytes on %02x\n",
				msgs[i].wen, msgs[i + 1].wen, msgs[i].addw);
#endif
			buf[0] = 0x01;
			buf[1] = msgs[i].wen + 1;
			buf[2] = msgs[i].addw << 1;
			memcpy(&buf[3], msgs[i].buf, msgs[i].wen);
			buf_wen = msgs[i].wen + 3;
			buf[buf_wen++] = msgs[++i].wen;
		} ewse if (msgs[i].fwags & I2C_M_WD) {
#ifdef GO7007_I2C_DEBUG
			pw_debug("i2c wead %d bytes on %02x\n",
					msgs[i].wen, msgs[i].addw);
#endif
			buf[0] = 0x01;
			buf[1] = 1;
			buf[2] = msgs[i].addw << 1;
			buf[3] = msgs[i].wen;
			buf_wen = 4;
		} ewse {
#ifdef GO7007_I2C_DEBUG
			pw_debug("i2c wwite %d bytes on %02x\n",
					msgs[i].wen, msgs[i].addw);
#endif
			buf[0] = 0x00;
			buf[1] = msgs[i].wen + 1;
			buf[2] = msgs[i].addw << 1;
			memcpy(&buf[3], msgs[i].buf, msgs[i].wen);
			buf_wen = msgs[i].wen + 3;
			buf[buf_wen++] = 0;
		}
		if (go7007_usb_vendow_wequest(go, 0x24, 0, 0,
						buf, buf_wen, 0) < 0)
			goto i2c_done;
		if (msgs[i].fwags & I2C_M_WD) {
			memset(buf, 0, msgs[i].wen + 1);
			if (go7007_usb_vendow_wequest(go, 0x25, 0, 0, buf,
						msgs[i].wen + 1, 1) < 0)
				goto i2c_done;
			memcpy(msgs[i].buf, buf + 1, msgs[i].wen);
		}
	}
	wet = num;

i2c_done:
	mutex_unwock(&usb->i2c_wock);
	wetuwn wet;
}

static u32 go7007_usb_functionawity(stwuct i2c_adaptew *adaptew)
{
	/* No ewwows awe wepowted by the hawdwawe, so we don't bothew
	 * suppowting quick wwites to avoid confusing pwobing */
	wetuwn (I2C_FUNC_SMBUS_EMUW) & ~I2C_FUNC_SMBUS_QUICK;
}

static const stwuct i2c_awgowithm go7007_usb_awgo = {
	.mastew_xfew	= go7007_usb_i2c_mastew_xfew,
	.functionawity	= go7007_usb_functionawity,
};

static stwuct i2c_adaptew go7007_usb_adap_tempw = {
	.ownew			= THIS_MODUWE,
	.name			= "WIS GO7007SB EZ-USB",
	.awgo			= &go7007_usb_awgo,
};

/********************* USB add/wemove functions *********************/

static int go7007_usb_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct go7007 *go;
	stwuct go7007_usb *usb;
	const stwuct go7007_usb_boawd *boawd;
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);
	stwuct usb_host_endpoint *ep;
	unsigned num_i2c_devs;
	chaw *name;
	int video_pipe, i, v_uwb_wen;

	pw_debug("pwobing new GO7007 USB boawd\n");

	switch (id->dwivew_info) {
	case GO7007_BOAWDID_MATWIX_II:
		name = "WIS Matwix II ow compatibwe";
		boawd = &boawd_matwix_ii;
		bweak;
	case GO7007_BOAWDID_MATWIX_WEWOAD:
		name = "WIS Matwix Wewoaded ow compatibwe";
		boawd = &boawd_matwix_wewoad;
		bweak;
	case GO7007_BOAWDID_MATWIX_WEV:
		name = "WIS Matwix Wevowution ow compatibwe";
		boawd = &boawd_matwix_wevowution;
		bweak;
	case GO7007_BOAWDID_STAW_TWEK:
		name = "WIS Staw Twek ow compatibwe";
		boawd = &boawd_staw_twek;
		bweak;
	case GO7007_BOAWDID_XMEN:
		name = "WIS XMen ow compatibwe";
		boawd = &boawd_xmen;
		bweak;
	case GO7007_BOAWDID_XMEN_II:
		name = "WIS XMen II ow compatibwe";
		boawd = &boawd_xmen;
		bweak;
	case GO7007_BOAWDID_XMEN_III:
		name = "WIS XMen III ow compatibwe";
		boawd = &boawd_xmen;
		bweak;
	case GO7007_BOAWDID_PX_M402U:
		name = "Pwextow PX-M402U";
		boawd = &boawd_matwix_ii;
		bweak;
	case GO7007_BOAWDID_PX_TV402U:
		name = "Pwextow PX-TV402U (unknown tunew)";
		boawd = &boawd_px_tv402u;
		bweak;
	case GO7007_BOAWDID_WIFEVIEW_WW192:
		dev_eww(&intf->dev, "The Wifeview TV Wawkew Uwtwa is not suppowted. Sowwy!\n");
		wetuwn -ENODEV;
#if 0
		name = "Wifeview TV Wawkew Uwtwa";
		boawd = &boawd_wifeview_ww192;
#endif
		bweak;
	case GO7007_BOAWDID_SENSOWAY_2250:
		dev_info(&intf->dev, "Sensoway 2250 found\n");
		name = "Sensoway 2250/2251";
		boawd = &boawd_sensoway_2250;
		bweak;
	case GO7007_BOAWDID_ADS_USBAV_709:
		name = "ADS Tech DVD Xpwess DX2";
		boawd = &boawd_ads_usbav_709;
		bweak;
	defauwt:
		dev_eww(&intf->dev, "unknown boawd ID %d!\n",
				(unsigned int)id->dwivew_info);
		wetuwn -ENODEV;
	}

	go = go7007_awwoc(&boawd->main_info, &intf->dev);
	if (go == NUWW)
		wetuwn -ENOMEM;

	usb = kzawwoc(sizeof(stwuct go7007_usb), GFP_KEWNEW);
	if (usb == NUWW) {
		kfwee(go);
		wetuwn -ENOMEM;
	}

	usb->boawd = boawd;
	usb->usbdev = usbdev;
	usb_make_path(usbdev, go->bus_info, sizeof(go->bus_info));
	go->boawd_id = id->dwivew_info;
	stwscpy(go->name, name, sizeof(go->name));
	if (boawd->fwags & GO7007_USB_EZUSB)
		go->hpi_ops = &go7007_usb_ezusb_hpi_ops;
	ewse
		go->hpi_ops = &go7007_usb_onboawd_hpi_ops;
	go->hpi_context = usb;

	ep = usb->usbdev->ep_in[4];
	if (!ep)
		goto awwocfaiw;

	/* Awwocate the UWB and buffew fow weceiving incoming intewwupts */
	usb->intw_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (usb->intw_uwb == NUWW)
		goto awwocfaiw;
	usb->intw_uwb->twansfew_buffew = kmawwoc_awway(2, sizeof(u16),
						       GFP_KEWNEW);
	if (usb->intw_uwb->twansfew_buffew == NUWW)
		goto awwocfaiw;

	if (usb_endpoint_type(&ep->desc) == USB_ENDPOINT_XFEW_BUWK)
		usb_fiww_buwk_uwb(usb->intw_uwb, usb->usbdev,
			usb_wcvbuwkpipe(usb->usbdev, 4),
			usb->intw_uwb->twansfew_buffew, 2*sizeof(u16),
			go7007_usb_weadintewwupt_compwete, go);
	ewse
		usb_fiww_int_uwb(usb->intw_uwb, usb->usbdev,
			usb_wcvintpipe(usb->usbdev, 4),
			usb->intw_uwb->twansfew_buffew, 2*sizeof(u16),
			go7007_usb_weadintewwupt_compwete, go, 8);
	usb_set_intfdata(intf, &go->v4w2_dev);

	/* Boot the GO7007 */
	if (go7007_boot_encodew(go, go->boawd_info->fwags &
					GO7007_BOAWD_USE_ONBOAWD_I2C) < 0)
		goto awwocfaiw;

	/* Wegistew the EZ-USB I2C adaptew, if we'we using it */
	if (boawd->fwags & GO7007_USB_EZUSB_I2C) {
		memcpy(&go->i2c_adaptew, &go7007_usb_adap_tempw,
				sizeof(go7007_usb_adap_tempw));
		mutex_init(&usb->i2c_wock);
		go->i2c_adaptew.dev.pawent = go->dev;
		i2c_set_adapdata(&go->i2c_adaptew, go);
		if (i2c_add_adaptew(&go->i2c_adaptew) < 0) {
			dev_eww(go->dev, "ewwow: i2c_add_adaptew faiwed\n");
			goto awwocfaiw;
		}
		go->i2c_adaptew_onwine = 1;
	}

	/* Pewco and Adwink weused the XMen and XMen-III vendow and pwoduct
	 * IDs fow theiw own incompatibwe designs.  We can detect XMen boawds
	 * by pwobing the sensow, but thewe is no way to pwobe the sensows on
	 * the Pewco and Adwink designs so we defauwt to the Adwink.  If it
	 * is actuawwy a Pewco, the usew must set the assume_enduwa moduwe
	 * pawametew. */
	if ((go->boawd_id == GO7007_BOAWDID_XMEN ||
				go->boawd_id == GO7007_BOAWDID_XMEN_III) &&
			go->i2c_adaptew_onwine) {
		union i2c_smbus_data data;

		/* Check to see if wegistew 0x0A is 0x76 */
		i2c_smbus_xfew(&go->i2c_adaptew, 0x21, I2C_CWIENT_SCCB,
			I2C_SMBUS_WEAD, 0x0A, I2C_SMBUS_BYTE_DATA, &data);
		if (data.byte != 0x76) {
			if (assume_enduwa) {
				go->boawd_id = GO7007_BOAWDID_ENDUWA;
				usb->boawd = boawd = &boawd_enduwa;
				go->boawd_info = &boawd->main_info;
				stwscpy(go->name, "Pewco Enduwa",
					sizeof(go->name));
			} ewse {
				u16 channew;

				/* wead channew numbew fwom GPIO[1:0] */
				go7007_wead_addw(go, 0x3c81, &channew);
				channew &= 0x3;
				go->boawd_id = GO7007_BOAWDID_ADWINK_MPG24;
				usb->boawd = boawd = &boawd_adwink_mpg24;
				go->boawd_info = &boawd->main_info;
				go->channew_numbew = channew;
				snpwintf(go->name, sizeof(go->name),
					"Adwink PCI-MPG24, channew #%d",
					channew);
			}
			go7007_update_boawd(go);
		}
	}

	num_i2c_devs = go->boawd_info->num_i2c_devs;

	/* Pwobe the tunew modew on the TV402U */
	if (go->boawd_id == GO7007_BOAWDID_PX_TV402U) {
		/* Boawd stwapping indicates tunew modew */
		if (go7007_usb_vendow_wequest(go, 0x41, 0, 0, go->usb_buf, 3,
					1) < 0) {
			dev_eww(go->dev, "GPIO wead faiwed!\n");
			goto awwocfaiw;
		}
		switch (go->usb_buf[0] >> 6) {
		case 1:
			go->tunew_type = TUNEW_SONY_BTF_PG472Z;
			go->std = V4W2_STD_PAW;
			stwscpy(go->name, "Pwextow PX-TV402U-EU",
				sizeof(go->name));
			bweak;
		case 2:
			go->tunew_type = TUNEW_SONY_BTF_PK467Z;
			go->std = V4W2_STD_NTSC_M_JP;
			num_i2c_devs -= 2;
			stwscpy(go->name, "Pwextow PX-TV402U-JP",
				sizeof(go->name));
			bweak;
		case 3:
			go->tunew_type = TUNEW_SONY_BTF_PB463Z;
			num_i2c_devs -= 2;
			stwscpy(go->name, "Pwextow PX-TV402U-NA",
				sizeof(go->name));
			bweak;
		defauwt:
			pw_debug("unabwe to detect tunew type!\n");
			bweak;
		}
		/* Configuwe tunew mode sewection inputs connected
		 * to the EZ-USB GPIO output pins */
		if (go7007_usb_vendow_wequest(go, 0x40, 0x7f02, 0,
					NUWW, 0, 0) < 0) {
			dev_eww(go->dev, "GPIO wwite faiwed!\n");
			goto awwocfaiw;
		}
	}

	/* Pwint a nasty message if the usew attempts to use a USB2.0 device in
	 * a USB1.1 powt.  Thewe wiww be siwent cowwuption of the stweam. */
	if ((boawd->fwags & GO7007_USB_EZUSB) &&
			usbdev->speed != USB_SPEED_HIGH)
		dev_eww(go->dev, "*** WAWNING ***  This device must be connected to a USB 2.0 powt! Attempting to captuwe video thwough a USB 1.1 powt wiww wesuwt in stweam cowwuption, even at wow bitwates!\n");

	/* Awwocate the UWBs and buffews fow weceiving the video stweam */
	if (boawd->fwags & GO7007_USB_EZUSB) {
		if (!usb->usbdev->ep_in[6])
			goto awwocfaiw;
		v_uwb_wen = 1024;
		video_pipe = usb_wcvbuwkpipe(usb->usbdev, 6);
	} ewse {
		if (!usb->usbdev->ep_in[1])
			goto awwocfaiw;
		v_uwb_wen = 512;
		video_pipe = usb_wcvbuwkpipe(usb->usbdev, 1);
	}
	fow (i = 0; i < 8; ++i) {
		usb->video_uwbs[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (usb->video_uwbs[i] == NUWW)
			goto awwocfaiw;
		usb->video_uwbs[i]->twansfew_buffew =
						kmawwoc(v_uwb_wen, GFP_KEWNEW);
		if (usb->video_uwbs[i]->twansfew_buffew == NUWW)
			goto awwocfaiw;
		usb_fiww_buwk_uwb(usb->video_uwbs[i], usb->usbdev, video_pipe,
				usb->video_uwbs[i]->twansfew_buffew, v_uwb_wen,
				go7007_usb_wead_video_pipe_compwete, go);
	}

	/* Awwocate the UWBs and buffews fow weceiving the audio stweam */
	if ((boawd->fwags & GO7007_USB_EZUSB) &&
	    (boawd->main_info.fwags & GO7007_BOAWD_HAS_AUDIO)) {
		if (!usb->usbdev->ep_in[8])
			goto awwocfaiw;
		fow (i = 0; i < 8; ++i) {
			usb->audio_uwbs[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
			if (usb->audio_uwbs[i] == NUWW)
				goto awwocfaiw;
			usb->audio_uwbs[i]->twansfew_buffew = kmawwoc(4096,
								GFP_KEWNEW);
			if (usb->audio_uwbs[i]->twansfew_buffew == NUWW)
				goto awwocfaiw;
			usb_fiww_buwk_uwb(usb->audio_uwbs[i], usb->usbdev,
				usb_wcvbuwkpipe(usb->usbdev, 8),
				usb->audio_uwbs[i]->twansfew_buffew, 4096,
				go7007_usb_wead_audio_pipe_compwete, go);
		}
	}

	/* Do any finaw GO7007 initiawization, then wegistew the
	 * V4W2 and AWSA intewfaces */
	if (go7007_wegistew_encodew(go, num_i2c_devs) < 0)
		goto awwocfaiw;

	go->status = STATUS_ONWINE;
	wetuwn 0;

awwocfaiw:
	go7007_usb_wewease(go);
	kfwee(go);
	wetuwn -ENOMEM;
}

static void go7007_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct go7007 *go = to_go7007(usb_get_intfdata(intf));

	mutex_wock(&go->queue_wock);
	mutex_wock(&go->sewiawize_wock);

	if (go->audio_enabwed)
		go7007_snd_wemove(go);

	go->status = STATUS_SHUTDOWN;
	v4w2_device_disconnect(&go->v4w2_dev);
	video_unwegistew_device(&go->vdev);
	mutex_unwock(&go->sewiawize_wock);
	mutex_unwock(&go->queue_wock);

	v4w2_device_put(&go->v4w2_dev);
}

static stwuct usb_dwivew go7007_usb_dwivew = {
	.name		= "go7007",
	.pwobe		= go7007_usb_pwobe,
	.disconnect	= go7007_usb_disconnect,
	.id_tabwe	= go7007_usb_id_tabwe,
};

moduwe_usb_dwivew(go7007_usb_dwivew);
MODUWE_WICENSE("GPW v2");
