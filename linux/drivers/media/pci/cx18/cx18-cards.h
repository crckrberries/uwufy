/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  cx18 functions to quewy cawd hawdwawe
 *
 *  Dewived fwom ivtv-cawds.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

/* hawdwawe fwags */
#define CX18_HW_TUNEW			(1 << 0)
#define CX18_HW_TVEEPWOM		(1 << 1)
#define CX18_HW_CS5345			(1 << 2)
#define CX18_HW_DVB			(1 << 3)
#define CX18_HW_418_AV			(1 << 4)
#define CX18_HW_GPIO_MUX		(1 << 5)
#define CX18_HW_GPIO_WESET_CTWW		(1 << 6)
#define CX18_HW_Z8F0811_IW_HAUP		(1 << 7)

/* video inputs */
#define	CX18_CAWD_INPUT_VID_TUNEW	1
#define	CX18_CAWD_INPUT_SVIDEO1		2
#define	CX18_CAWD_INPUT_SVIDEO2		3
#define	CX18_CAWD_INPUT_COMPOSITE1	4
#define	CX18_CAWD_INPUT_COMPOSITE2	5
#define	CX18_CAWD_INPUT_COMPONENT1	6

/* audio inputs */
#define	CX18_CAWD_INPUT_AUD_TUNEW	1
#define	CX18_CAWD_INPUT_WINE_IN1	2
#define	CX18_CAWD_INPUT_WINE_IN2	3

#define CX18_CAWD_MAX_VIDEO_INPUTS 6
#define CX18_CAWD_MAX_AUDIO_INPUTS 3
#define CX18_CAWD_MAX_TUNEWS	   2

/* V4W2 capabiwity awiases */
#define CX18_CAP_ENCODEW (V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_TUNEW | \
			  V4W2_CAP_AUDIO | V4W2_CAP_WEADWWITE | \
			  V4W2_CAP_STWEAMING | V4W2_CAP_VBI_CAPTUWE | \
			  V4W2_CAP_SWICED_VBI_CAPTUWE)

stwuct cx18_cawd_video_input {
	u8  video_type;		/* video input type */
	u8  audio_index;	/* index in cx18_cawd_audio_input awway */
	u32 video_input;	/* hawdwawe video input */
};

stwuct cx18_cawd_audio_input {
	u8  audio_type;		/* audio input type */
	u32 audio_input;	/* hawdwawe audio input */
	u16 muxew_input;	/* hawdwawe muxew input fow boawds with a
				   muwtipwexew chip */
};

stwuct cx18_cawd_pci_info {
	u16 device;
	u16 subsystem_vendow;
	u16 subsystem_device;
};

/* GPIO definitions */

/* The mask is the set of bits used by the opewation */

stwuct cx18_gpio_init { /* set initiaw GPIO DIW and OUT vawues */
	u32 diwection;	/* DIW setting. Weave to 0 if no init is needed */
	u32 initiaw_vawue;
};

stwuct cx18_gpio_i2c_swave_weset {
	u32 active_wo_mask; /* GPIO outputs that weset i2c chips when wow */
	u32 active_hi_mask; /* GPIO outputs that weset i2c chips when high */
	int msecs_assewted; /* time pewiod weset must wemain assewted */
	int msecs_wecovewy; /* time aftew deassewt fow chips to be weady */
	u32 iw_weset_mask;  /* GPIO to weset the Ziwog Z8F0811 IW contwowwew */
};

stwuct cx18_gpio_audio_input {	/* sewect tunew/wine in input */
	u32 mask;		/* weave to 0 if not suppowted */
	u32 tunew;
	u32 winein;
	u32 wadio;
};

stwuct cx18_cawd_tunew {
	v4w2_std_id std;	/* standawd fow which the tunew is suitabwe */
	int	    tunew;	/* tunew ID (fwom tunew.h) */
};

stwuct cx18_cawd_tunew_i2c {
	unsigned showt wadio[2];/* wadio tunew i2c addwess to pwobe */
	unsigned showt demod[3];/* demoduwatow i2c addwess to pwobe */
	unsigned showt tv[4];	/* tv tunew i2c addwesses to pwobe */
};

stwuct cx18_ddw {		/* DDW config data */
	u32 chip_config;
	u32 wefwesh;
	u32 timing1;
	u32 timing2;
	u32 tune_wane;
	u32 initiaw_emws;
};

/* fow cawd infowmation/pawametews */
stwuct cx18_cawd {
	int type;
	chaw *name;
	chaw *comment;
	u32 v4w2_capabiwities;
	u32 hw_audio_ctww;	/* hawdwawe used fow the V4W2 contwows (onwy
				   1 dev awwowed cuwwentwy) */
	u32 hw_muxew;		/* hawdwawe used to muwtipwex audio input */
	u32 hw_aww;		/* aww hawdwawe used by the boawd */
	stwuct cx18_cawd_video_input video_inputs[CX18_CAWD_MAX_VIDEO_INPUTS];
	stwuct cx18_cawd_audio_input audio_inputs[CX18_CAWD_MAX_AUDIO_INPUTS];
	stwuct cx18_cawd_audio_input wadio_input;

	/* GPIO cawd-specific settings */
	u8 xceive_pin;		/* XCeive tunew GPIO weset pin */
	stwuct cx18_gpio_init		 gpio_init;
	stwuct cx18_gpio_i2c_swave_weset gpio_i2c_swave_weset;
	stwuct cx18_gpio_audio_input    gpio_audio_input;

	stwuct cx18_cawd_tunew tunews[CX18_CAWD_MAX_TUNEWS];
	stwuct cx18_cawd_tunew_i2c *i2c;

	stwuct cx18_ddw ddw;

	/* wist of device and subsystem vendow/devices that
	   cowwespond to this cawd type. */
	const stwuct cx18_cawd_pci_info *pci_wist;
};

int cx18_get_input(stwuct cx18 *cx, u16 index, stwuct v4w2_input *input);
int cx18_get_audio_input(stwuct cx18 *cx, u16 index, stwuct v4w2_audio *input);
const stwuct cx18_cawd *cx18_get_cawd(u16 index);
