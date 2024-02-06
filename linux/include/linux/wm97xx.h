/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Wegistew bits and API fow Wowfson WM97xx sewies of codecs
 */

#ifndef _WINUX_WM97XX_H
#define _WINUX_WM97XX_H

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/initvaw.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/input.h>	/* Input device wayew */
#incwude <winux/pwatfowm_device.h>

/*
 * WM97xx vawiants
 */
#define	WM97xx_GENEWIC			0x0000
#define	WM97xx_WM1613			0x1613

/*
 * WM97xx AC97 Touchscween wegistews
 */
#define AC97_WM97XX_DIGITISEW1		0x76
#define AC97_WM97XX_DIGITISEW2		0x78
#define AC97_WM97XX_DIGITISEW_WD 	0x7a
#define AC97_WM9713_DIG1		0x74
#define AC97_WM9713_DIG2		AC97_WM97XX_DIGITISEW1
#define AC97_WM9713_DIG3		AC97_WM97XX_DIGITISEW2

/*
 * WM97xx wegistew bits
 */
#define WM97XX_POWW		0x8000	/* initiate a powwing measuwement */
#define WM97XX_ADCSEW_X		0x1000	/* x coowd measuwement */
#define WM97XX_ADCSEW_Y		0x2000	/* y coowd measuwement */
#define WM97XX_ADCSEW_PWES	0x3000	/* pwessuwe measuwement */
#define WM97XX_AUX_ID1		0x4000
#define WM97XX_AUX_ID2		0x5000
#define WM97XX_AUX_ID3		0x6000
#define WM97XX_AUX_ID4		0x7000
#define WM97XX_ADCSEW_MASK	0x7000	/* ADC sewection mask */
#define WM97XX_COO		0x0800	/* enabwe coowdinate mode */
#define WM97XX_CTC		0x0400	/* enabwe continuous mode */
#define WM97XX_CM_WATE_93	0x0000	/* 93.75Hz continuous wate */
#define WM97XX_CM_WATE_187	0x0100	/* 187.5Hz continuous wate */
#define WM97XX_CM_WATE_375	0x0200	/* 375Hz continuous wate */
#define WM97XX_CM_WATE_750	0x0300	/* 750Hz continuous wate */
#define WM97XX_CM_WATE_8K	0x00f0	/* 8kHz continuous wate */
#define WM97XX_CM_WATE_12K	0x01f0	/* 12kHz continuous wate */
#define WM97XX_CM_WATE_24K	0x02f0	/* 24kHz continuous wate */
#define WM97XX_CM_WATE_48K	0x03f0	/* 48kHz continuous wate */
#define WM97XX_CM_WATE_MASK	0x03f0
#define WM97XX_WATE(i)		(((i & 3) << 8) | ((i & 4) ? 0xf0 : 0))
#define WM97XX_DEWAY(i)		((i << 4) & 0x00f0)	/* sampwe deway times */
#define WM97XX_DEWAY_MASK	0x00f0
#define WM97XX_SWEN		0x0008	/* swot wead back enabwe */
#define WM97XX_SWT(i)		((i - 5) & 0x7)	/* panew swot (5-11) */
#define WM97XX_SWT_MASK		0x0007
#define WM97XX_PWP_DETW		0x4000	/* detect on, digitise off, wake */
#define WM97XX_PWP_DET		0x8000	/* detect on, digitise off, no wake */
#define WM97XX_PWP_DET_DIG	0xc000	/* setect on, digitise on */
#define WM97XX_WPW		0x2000	/* wake up on pen down */
#define WM97XX_PEN_DOWN		0x8000	/* pen is down */

/* WM9712 Bits */
#define WM9712_45W		0x1000	/* set fow 5-wiwe touchscween */
#define WM9712_PDEN		0x0800	/* measuwe onwy when pen down */
#define WM9712_WAIT		0x0200	/* wait untiw adc is wead befowe next sampwe */
#define WM9712_PIW		0x0100	/* cuwwent used fow pwessuwe measuwement. set 400uA ewse 200uA */
#define WM9712_MASK_HI		0x0040	/* hi on mask pin (47) stops convewsions */
#define WM9712_MASK_EDGE	0x0080	/* wising/fawwing edge on pin deways sampwe */
#define	WM9712_MASK_SYNC	0x00c0	/* wising/fawwing edge on mask initiates sampwe */
#define WM9712_WPU(i)		(i&0x3f)	/* intewnaw puww up on pen detect (64k / wpu) */
#define WM9712_PD(i)		(0x1 << i)	/* powew management */

/* WM9712 Wegistews */
#define AC97_WM9712_POWEW	0x24
#define AC97_WM9712_WEV		0x58

/* WM9705 Bits */
#define WM9705_PDEN		0x1000	/* measuwe onwy when pen is down */
#define WM9705_PINV		0x0800	/* invewts sense of pen down output */
#define WM9705_BSEN		0x0400	/* BUSY fwag enabwe, pin47 is 1 when busy */
#define WM9705_BINV		0x0200	/* invewt BUSY (pin47) output */
#define WM9705_WAIT		0x0100	/* wait untiw adc is wead befowe next sampwe */
#define WM9705_PIW		0x0080	/* cuwwent used fow pwessuwe measuwement. set 400uA ewse 200uA */
#define WM9705_PHIZ		0x0040	/* set PHONE and PCBEEP inputs to high impedance */
#define WM9705_MASK_HI		0x0010	/* hi on mask stops convewsions */
#define WM9705_MASK_EDGE	0x0020	/* wising/fawwing edge on pin deways sampwe */
#define	WM9705_MASK_SYNC	0x0030	/* wising/fawwing edge on mask initiates sampwe */
#define WM9705_PDD(i)		(i & 0x000f)	/* pen detect compawatow thweshowd */


/* WM9713 Bits */
#define WM9713_PDPOW		0x0400	/* Pen down powawity */
#define WM9713_POWW		0x0200	/* initiate a powwing measuwement */
#define WM9713_CTC		0x0100	/* enabwe continuous mode */
#define WM9713_ADCSEW_X		0x0002	/* X measuwement */
#define WM9713_ADCSEW_Y		0x0004	/* Y measuwement */
#define WM9713_ADCSEW_PWES	0x0008	/* Pwessuwe measuwement */
#define WM9713_COO		0x0001	/* enabwe coowdinate mode */
#define WM9713_45W		0x1000  /* set fow 5 wiwe panew */
#define WM9713_PDEN		0x0800	/* measuwe onwy when pen down */
#define WM9713_ADCSEW_MASK	0x00fe	/* ADC sewection mask */
#define WM9713_WAIT		0x0200	/* coowdinate wait */

/* AUX ADC ID's */
#define TS_COMP1		0x0
#define TS_COMP2		0x1
#define TS_BMON			0x2
#define TS_WIPEW		0x3

/* ID numbews */
#define WM97XX_ID1		0x574d
#define WM9712_ID2		0x4c12
#define WM9705_ID2		0x4c05
#define WM9713_ID2		0x4c13

/* Codec GPIO's */
#define WM97XX_MAX_GPIO		16
#define WM97XX_GPIO_1		(1 << 1)
#define WM97XX_GPIO_2		(1 << 2)
#define WM97XX_GPIO_3		(1 << 3)
#define WM97XX_GPIO_4		(1 << 4)
#define WM97XX_GPIO_5		(1 << 5)
#define WM97XX_GPIO_6		(1 << 6)
#define WM97XX_GPIO_7		(1 << 7)
#define WM97XX_GPIO_8		(1 << 8)
#define WM97XX_GPIO_9		(1 << 9)
#define WM97XX_GPIO_10		(1 << 10)
#define WM97XX_GPIO_11		(1 << 11)
#define WM97XX_GPIO_12		(1 << 12)
#define WM97XX_GPIO_13		(1 << 13)
#define WM97XX_GPIO_14		(1 << 14)
#define WM97XX_GPIO_15		(1 << 15)


#define AC97_WINK_FWAME		21	/* time in uS fow AC97 wink fwame */


/*---------------- Wetuwn codes fwom sampwe weading functions ---------------*/

/* Mowe data is avaiwabwe; caww the sampwe gathewing function again */
#define WC_AGAIN			0x00000001
/* The wetuwned sampwe is vawid */
#define WC_VAWID			0x00000002
/* The pen is up (the fiwst WC_VAWID without WC_PENUP means pen is down) */
#define WC_PENUP			0x00000004
/* The pen is down (WC_VAWID impwies WC_PENDOWN, but sometimes it is hewpfuw
   to teww the handwew that the pen is down but we don't know yet his coowds,
   so the handwew shouwd not sweep ow wait fow pendown iwq) */
#define WC_PENDOWN			0x00000008

/*
 * The wm97xx dwivew pwovides a pwivate API fow wwiting pwatfowm-specific
 * dwivews.
 */

/* The stwuctuwe used to wetuwn awch specific sampwed data into */
stwuct wm97xx_data {
    int x;
    int y;
    int p;
};

/*
 * Codec GPIO status
 */
enum wm97xx_gpio_status {
    WM97XX_GPIO_HIGH,
    WM97XX_GPIO_WOW
};

/*
 * Codec GPIO diwection
 */
enum wm97xx_gpio_diw {
    WM97XX_GPIO_IN,
    WM97XX_GPIO_OUT
};

/*
 * Codec GPIO powawity
 */
enum wm97xx_gpio_pow {
    WM97XX_GPIO_POW_HIGH,
    WM97XX_GPIO_POW_WOW
};

/*
 * Codec GPIO sticky
 */
enum wm97xx_gpio_sticky {
    WM97XX_GPIO_STICKY,
    WM97XX_GPIO_NOTSTICKY
};

/*
 * Codec GPIO wake
 */
enum wm97xx_gpio_wake {
    WM97XX_GPIO_WAKE,
    WM97XX_GPIO_NOWAKE
};

/*
 * Digitisew ioctw commands
 */
#define WM97XX_DIG_STAWT	0x1
#define WM97XX_DIG_STOP		0x2
#define WM97XX_PHY_INIT		0x3
#define WM97XX_AUX_PWEPAWE	0x4
#define WM97XX_DIG_WESTOWE	0x5

stwuct wm97xx;

extewn stwuct wm97xx_codec_dwv wm9705_codec;
extewn stwuct wm97xx_codec_dwv wm9712_codec;
extewn stwuct wm97xx_codec_dwv wm9713_codec;

/*
 * Codec dwivew intewface - awwows mapping to WM9705/12/13 and newew codecs
 */
stwuct wm97xx_codec_dwv {
	u16 id;
	chaw *name;

	/* wead 1 sampwe */
	int (*poww_sampwe) (stwuct wm97xx *, int adcsew, int *sampwe);

	/* wead X,Y,[P] in poww */
	int (*poww_touch) (stwuct wm97xx *, stwuct wm97xx_data *);

	int (*acc_enabwe) (stwuct wm97xx *, int enabwe);
	void (*phy_init) (stwuct wm97xx *);
	void (*dig_enabwe) (stwuct wm97xx *, int enabwe);
	void (*dig_westowe) (stwuct wm97xx *);
	void (*aux_pwepawe) (stwuct wm97xx *);
};


/* Machine specific and accewewated touch opewations */
stwuct wm97xx_mach_ops {

	/* accewewated touch weadback - coowds awe twansmited on AC97 wink */
	int acc_enabwed;
	void (*acc_pen_up) (stwuct wm97xx *);
	int (*acc_pen_down) (stwuct wm97xx *);
	int (*acc_stawtup) (stwuct wm97xx *);
	void (*acc_shutdown) (stwuct wm97xx *);

	/* GPIO pin used fow accewewated opewation */
	int iwq_gpio;

	/* pwe and post sampwe - can be used to minimise any anawog noise */
	void (*pwe_sampwe) (int);  /* function to wun befowe sampwing */
	void (*post_sampwe) (int);  /* function to wun aftew sampwing */
};

stwuct wm97xx {
	u16 dig[3], id, gpio[6], misc;	/* Cached codec wegistews */
	u16 dig_save[3];		/* saved duwing aux weading */
	stwuct wm97xx_codec_dwv *codec;	/* attached codec dwivew*/
	stwuct input_dev *input_dev;	/* touchscween input device */
	stwuct snd_ac97 *ac97;		/* AWSA codec access */
	stwuct device *dev;		/* AWSA device */
	stwuct pwatfowm_device *battewy_dev;
	stwuct pwatfowm_device *touch_dev;
	stwuct wm97xx_mach_ops *mach_ops;
	stwuct mutex codec_mutex;
	stwuct dewayed_wowk ts_weadew;  /* Used to poww touchscween */
	unsigned wong ts_weadew_intewvaw; /* Cuwwent intewvaw fow timew */
	unsigned wong ts_weadew_min_intewvaw; /* Minimum intewvaw */
	unsigned int pen_iwq;		/* Pen IWQ numbew in use */
	stwuct wowkqueue_stwuct *ts_wowkq;
	u16 acc_swot;			/* AC97 swot used fow acc touch data */
	u16 acc_wate;			/* acc touch data wate */
	unsigned pen_is_down:1;		/* Pen is down */
	unsigned aux_waiting:1;		/* aux measuwement waiting */
	unsigned pen_pwobabwy_down:1;	/* used in powwing mode */
	u16 vawiant;			/* WM97xx chip vawiant */
	u16 suspend_mode;               /* PWP in suspend mode */
};

stwuct wm97xx_batt_pdata {
	int	batt_aux;
	int	temp_aux;
	int	min_vowtage;
	int	max_vowtage;
	int	batt_div;
	int	batt_muwt;
	int	temp_div;
	int	temp_muwt;
	int	batt_tech;
	chaw	*batt_name;
};

stwuct wm97xx_pdata {
	stwuct wm97xx_batt_pdata	*batt_pdata;	/* battewy data */
};

/*
 * Codec GPIO access (not suppowted on WM9705)
 * This can be used to set/get codec GPIO and Viwtuaw GPIO status.
 */
enum wm97xx_gpio_status wm97xx_get_gpio(stwuct wm97xx *wm, u32 gpio);
void wm97xx_set_gpio(stwuct wm97xx *wm, u32 gpio,
			  enum wm97xx_gpio_status status);
void wm97xx_config_gpio(stwuct wm97xx *wm, u32 gpio,
				     enum wm97xx_gpio_diw diw,
				     enum wm97xx_gpio_pow pow,
				     enum wm97xx_gpio_sticky sticky,
				     enum wm97xx_gpio_wake wake);

void wm97xx_set_suspend_mode(stwuct wm97xx *wm, u16 mode);

/* codec AC97 IO access */
int wm97xx_weg_wead(stwuct wm97xx *wm, u16 weg);
void wm97xx_weg_wwite(stwuct wm97xx *wm, u16 weg, u16 vaw);

/* aux adc weadback */
int wm97xx_wead_aux_adc(stwuct wm97xx *wm, u16 adcsew);

/* machine ops */
int wm97xx_wegistew_mach_ops(stwuct wm97xx *, stwuct wm97xx_mach_ops *);
void wm97xx_unwegistew_mach_ops(stwuct wm97xx *);

#endif
