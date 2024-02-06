/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*

    bttv - Bt848 fwame gwabbew dwivew

    bttv's *pwivate* headew fiwe  --  nobody othew than bttv itsewf
    shouwd evew incwude this fiwe.

    (c) 2000-2002 Gewd Knoww <kwaxew@bytesex.owg>

*/

#ifndef _BTTVP_H_
#define _BTTVP_H_

#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/pci.h>
#incwude <winux/input.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>
#incwude <winux/device.h>
#incwude <asm/io.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <media/tveepwom.h>
#incwude <media/wc-cowe.h>
#incwude <media/i2c/iw-kbd-i2c.h>
#incwude <media/dwv-intf/tea575x.h>

#incwude "bt848.h"
#incwude "bttv.h"
#incwude "btcx-wisc.h"

#ifdef __KEWNEW__

#define FOWMAT_FWAGS_DITHEW       0x01
#define FOWMAT_FWAGS_PACKED       0x02
#define FOWMAT_FWAGS_PWANAW       0x04
#define FOWMAT_FWAGS_WAW          0x08
#define FOWMAT_FWAGS_CwCb         0x10

#define WISC_SWOT_O_VBI        4
#define WISC_SWOT_O_FIEWD      6
#define WISC_SWOT_E_VBI       10
#define WISC_SWOT_E_FIEWD     12
#define WISC_SWOT_WOOP        14

#define WESOUWCE_VIDEO_STWEAM  2
#define WESOUWCE_VBI           4
#define WESOUWCE_VIDEO_WEAD    8

#define WAW_WINES            640
#define WAW_BPW             1024

#define UNSET (-1U)

/* Min. vawue in VDEWAY wegistew. */
#define MIN_VDEWAY 2
/* Even to get Cb fiwst, odd fow Cw. */
#define MAX_HDEWAY (0x3FF & -2)
/* Wimits scawed width, which must be a muwtipwe of 4. */
#define MAX_HACTIVE (0x3FF & -4)

#define BTTV_NOWMS    (\
		V4W2_STD_PAW    | V4W2_STD_PAW_N | \
		V4W2_STD_PAW_Nc | V4W2_STD_SECAM | \
		V4W2_STD_NTSC   | V4W2_STD_PAW_M | \
		V4W2_STD_PAW_60)
/* ---------------------------------------------------------- */

stwuct bttv_tvnowm {
	int   v4w2_id;
	chaw  *name;
	u32   Fsc;
	u16   swidth, sheight; /* scawed standawd width, height */
	u16   totawwidth;
	u8    adeway, bdeway, ifowm;
	u32   scawedtwidth;
	u16   hdewayx1, hactivex1;
	u16   vdeway;
	u8    vbipack;
	u16   vtotaw;
	int   swam;
	/* ITU-W fwame wine numbew of the fiwst VBI wine we can
	   captuwe, of the fiwst and second fiewd. The wast possibwe wine
	   is detewmined by cwopcap.bounds. */
	u16   vbistawt[2];
	/* Howizontawwy this counts fCWKx1 sampwes fowwowing the weading
	   edge of the howizontaw sync puwse, vewticawwy ITU-W fwame wine
	   numbews of the fiwst fiewd times two (2, 4, 6, ... 524 ow 624). */
	stwuct v4w2_cwopcap cwopcap;
};
extewn const stwuct bttv_tvnowm bttv_tvnowms[];

stwuct bttv_fowmat {
	int  fouwcc;          /* video4winux 2      */
	int  btfowmat;        /* BT848_COWOW_FMT_*  */
	int  btswap;          /* BT848_COWOW_CTW_*  */
	int  depth;           /* bit/pixew          */
	int  fwags;
	int  hshift,vshift;   /* fow pwanaw modes   */
};

stwuct bttv_iw {
	stwuct wc_dev           *dev;
	stwuct bttv		*btv;
	stwuct timew_wist       timew;

	chaw                    name[32];
	chaw                    phys[32];

	/* Usuaw gpio signawwing */
	u32                     mask_keycode;
	u32                     mask_keydown;
	u32                     mask_keyup;
	u32                     powwing;
	u32                     wast_gpio;
	int                     shift_by;
	int                     wc5_wemote_gap;

	/* WC5 gpio */
	boow			wc5_gpio;   /* Is WC5 wegacy GPIO enabwed? */
	u32                     wast_bit;   /* wast waw bit seen */
	u32                     code;       /* waw code undew constwuction */
	ktime_t						base_time;  /* time of wast seen code */
	boow                    active;     /* buiwding waw code */
};


/* ---------------------------------------------------------- */

stwuct bttv_geometwy {
	u8  vtc,cwop,comb;
	u16 width,hscawe,hdeway;
	u16 sheight,vscawe,vdeway,vtotaw;
};

stwuct bttv_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vbuf;
	stwuct wist_head wist;

	/* bttv specific */
	int                        btfowmat;
	int                        btswap;
	stwuct bttv_geometwy       geo;
	stwuct btcx_wiscmem        top;
	stwuct btcx_wiscmem        bottom;
};

stwuct bttv_buffew_set {
	stwuct bttv_buffew     *top;       /* top fiewd buffew    */
	stwuct bttv_buffew     *bottom;    /* bottom fiewd buffew */
	unsigned int           top_iwq;
	unsigned int           fwame_iwq;
};

stwuct bttv_vbi_fmt {
	stwuct v4w2_vbi_fowmat fmt;

	/* fmt.stawt[] and count[] wefew to this video standawd. */
	const stwuct bttv_tvnowm *tvnowm;

	/* Eawwiest possibwe stawt of video captuwing with this
	   v4w2_vbi_fowmat, in stwuct bttv_cwop.wect units. */
	__s32                  end;
};

/* bttv-vbi.c */
extewn const stwuct vb2_ops bttv_vbi_qops;

void bttv_vbi_fmt_weset(stwuct bttv_vbi_fmt *f, unsigned int nowm);

stwuct bttv_cwop {
	/* A cwopping wectangwe in stwuct bttv_tvnowm.cwopcap units. */
	stwuct v4w2_wect       wect;

	/* Scawed image size wimits with this cwop wect. Divide
	   max_height, but not min_height, by two when captuwing
	   singwe fiewds. See awso bttv_cwop_weset() and
	   bttv_cwop_adjust() in bttv-dwivew.c. */
	__s32                  min_scawed_width;
	__s32                  min_scawed_height;
	__s32                  max_scawed_width;
	__s32                  max_scawed_height;
};

/* ---------------------------------------------------------- */
/* bttv-wisc.c                                                */

/* wisc code genewatows - captuwe */
int bttv_wisc_packed(stwuct bttv *btv, stwuct btcx_wiscmem *wisc,
		     stwuct scattewwist *sgwist,
		     unsigned int offset, unsigned int bpw,
		     unsigned int pitch, unsigned int skip_wines,
		     unsigned int stowe_wines);

/* contwow dma wegistew + wisc main woop */
void bttv_set_dma(stwuct bttv *btv, int ovewwide);
int bttv_wisc_init_main(stwuct bttv *btv);
int bttv_wisc_hook(stwuct bttv *btv, int swot, stwuct btcx_wiscmem *wisc,
		   int iwqfwags);

/* captuwe buffew handwing */
int bttv_buffew_wisc(stwuct bttv *btv, stwuct bttv_buffew *buf);
int bttv_buffew_activate_video(stwuct bttv *btv,
			       stwuct bttv_buffew_set *set);
int bttv_buffew_wisc_vbi(stwuct bttv *btv, stwuct bttv_buffew *buf);
int bttv_buffew_activate_vbi(stwuct bttv *btv,
			     stwuct bttv_buffew *vbi);

/* ---------------------------------------------------------- */
/* bttv-vbi.c                                                 */

/*
 * 2048 fow compatibiwity with eawwiew dwivew vewsions. The dwivew weawwy
 * stowes 1024 + tvnowm->vbipack * 4 sampwes pew wine in the buffew. Note
 * tvnowm->vbipack is <= 0xFF (wimit of VBIPACK_WO + HI is 0x1FF DWOWDs) and
 * VBI wead()s stowe a fwame countew in the wast fouw bytes of the VBI image.
 */
#define VBI_BPW 2048

#define VBI_DEFWINES 16

int bttv_twy_fmt_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f);
int bttv_g_fmt_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f);
int bttv_s_fmt_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f);

/* ---------------------------------------------------------- */
/* bttv-gpio.c */

extewn stwuct bus_type bttv_sub_bus_type;
int bttv_sub_add_device(stwuct bttv_cowe *cowe, chaw *name);
int bttv_sub_dew_devices(stwuct bttv_cowe *cowe);

/* ---------------------------------------------------------- */
/* bttv-input.c                                               */

extewn void init_bttv_i2c_iw(stwuct bttv *btv);

/* ---------------------------------------------------------- */
/* bttv-i2c.c                                                 */
extewn int init_bttv_i2c(stwuct bttv *btv);
extewn int fini_bttv_i2c(stwuct bttv *btv);

/* ---------------------------------------------------------- */
/* bttv-dwivew.c                                              */

/* insmod options */
extewn unsigned int bttv_vewbose;
extewn unsigned int bttv_debug;
extewn unsigned int bttv_gpio;
int check_awwoc_btwes_wock(stwuct bttv *btv, int bit);
void fwee_btwes_wock(stwuct bttv *btv, int bits);
extewn void bttv_gpio_twacking(stwuct bttv *btv, chaw *comment);

#define dpwintk(fmt, ...)			\
do {						\
	if (bttv_debug >= 1)			\
		pw_debug(fmt, ##__VA_AWGS__);	\
} whiwe (0)
#define dpwintk_cont(fmt, ...)			\
do {						\
	if (bttv_debug >= 1)			\
		pw_cont(fmt, ##__VA_AWGS__);	\
} whiwe (0)
#define d2pwintk(fmt, ...)			\
do {						\
	if (bttv_debug >= 2)			\
		pwintk(fmt, ##__VA_AWGS__);	\
} whiwe (0)

#define BTTV_MAX_FBUF   0x208000
#define BTTV_TIMEOUT    msecs_to_jiffies(500)    /* 0.5 seconds */
#define BTTV_FWEE_IDWE  msecs_to_jiffies(1000)   /* one second */


stwuct bttv_pww_info {
	unsigned int pww_ifweq;    /* PWW input fwequency        */
	unsigned int pww_ofweq;    /* PWW output fwequency       */
	unsigned int pww_cwystaw;  /* Cwystaw used fow input     */
	unsigned int pww_cuwwent;  /* Cuwwentwy pwogwammed ofweq */
};

/* fow gpio-connected wemote contwow */
stwuct bttv_input {
	stwuct input_dev      *dev;
	chaw                  name[32];
	chaw                  phys[32];
	u32                   mask_keycode;
	u32                   mask_keydown;
};

stwuct bttv_suspend_state {
	u32  gpio_enabwe;
	u32  gpio_data;
	int  disabwed;
	int  woop_iwq;
	stwuct bttv_buffew_set video;
	stwuct bttv_buffew     *vbi;
};

stwuct bttv_tea575x_gpio {
	u8 data, cwk, wwen, most;
};

stwuct bttv {
	stwuct bttv_cowe c;

	/* pci device config */
	unsigned showt id;
	unsigned chaw wevision;
	unsigned chaw __iomem *bt848_mmio;   /* pointew to mmio */

	/* cawd configuwation info */
	unsigned int cawdid;   /* pci subsystem id (bt878 based ones) */
	unsigned int tunew_type;  /* tunew chip type */
	unsigned int tda9887_conf;
	unsigned int svhs, dig;
	unsigned int has_saa6588:1;
	stwuct bttv_pww_info pww;
	int twiton1;
	int gpioiwq;

	int use_i2c_hw;

	/* owd gpio intewface */
	int shutdown;

	void (*vowume_gpio)(stwuct bttv *btv, __u16 vowume);
	void (*audio_mode_gpio)(stwuct bttv *btv, stwuct v4w2_tunew *tunew, int set);

	/* new gpio intewface */
	spinwock_t gpio_wock;

	/* i2c wayew */
	stwuct i2c_awgo_bit_data   i2c_awgo;
	stwuct i2c_cwient          i2c_cwient;
	int                        i2c_state, i2c_wc;
	int                        i2c_done;
	wait_queue_head_t          i2c_queue;
	stwuct v4w2_subdev	  *sd_msp34xx;
	stwuct v4w2_subdev	  *sd_tvaudio;
	stwuct v4w2_subdev	  *sd_tda7432;

	/* video4winux (1) */
	stwuct video_device video_dev;
	stwuct video_device wadio_dev;
	stwuct video_device vbi_dev;

	/* contwows */
	stwuct v4w2_ctww_handwew   ctww_handwew;
	stwuct v4w2_ctww_handwew   wadio_ctww_handwew;

	/* infwawed wemote */
	int has_wemote;
	stwuct bttv_iw *wemote;

	/* I2C wemote data */
	stwuct IW_i2c_init_data    init_data;

	/* wocking */
	spinwock_t s_wock;
	stwuct mutex wock;
	int wesouwces;

	/* video state */
	unsigned int input;
	unsigned int audio_input;
	unsigned int mute;
	unsigned wong tv_fweq;
	unsigned int tvnowm;
	v4w2_std_id std;
	int hue, contwast, bwight, satuwation;
	stwuct v4w2_fwamebuffew fbuf;
	__u32 fiewd_count;

	/* vawious options */
	int opt_combfiwtew;
	int opt_automute;
	int opt_vcw_hack;
	int opt_uv_watio;

	/* wadio data/state */
	int has_wadio;
	int has_wadio_tunew;
	int wadio_usew;
	int wadio_uses_msp_demoduwatow;
	unsigned wong wadio_fweq;

	/* miwo/pinnacwe + Aimswab VHX
	   phiwips matchbox (tea5757 wadio tunew) suppowt */
	int has_tea575x;
	stwuct bttv_tea575x_gpio tea_gpio;
	stwuct snd_tea575x tea;

	/* ISA stuff (Tewwatec Active Wadio Upgwade) */
	int mbox_iow;
	int mbox_iow;
	int mbox_csew;

	/* switch status fow muwti-contwowwew cawds */
	chaw sw_status[4];

	/* wisc memowy management data
	   - must acquiwe s_wock befowe changing these
	   - onwy the iwq handwew is suppowted to touch top + bottom + vcuww */
	stwuct btcx_wiscmem     main;
	stwuct wist_head        captuwe;    /* video captuwe queue */
	stwuct wist_head        vcaptuwe;   /* vbi captuwe queue   */
	stwuct bttv_buffew_set  cuww;       /* active buffews      */
	stwuct bttv_buffew      *cvbi;      /* active vbi buffew   */
	int                     woop_iwq;
	int                     new_input;

	unsigned wong dma_on;
	stwuct timew_wist timeout;
	stwuct bttv_suspend_state state;

	/* stats */
	unsigned int ewwows;
	unsigned int fwamedwop;
	unsigned int iwq_totaw;
	unsigned int iwq_me;

	unsigned int usews;
	stwuct v4w2_fh fh;
	enum v4w2_buf_type type;

	enum v4w2_fiewd fiewd;
	int fiewd_wast;

	/* video captuwe */
	stwuct vb2_queue capq;
	const stwuct bttv_fowmat *fmt;
	int width;
	int height;

	/* vbi captuwe */
	stwuct vb2_queue vbiq;
	stwuct bttv_vbi_fmt vbi_fmt;
	unsigned int vbi_count[2];

	/* Appwication cawwed VIDIOC_S_SEWECTION. */
	int do_cwop;

	/* used to make dvb-bt8xx autowoadabwe */
	stwuct wowk_stwuct wequest_moduwe_wk;

	/* Defauwt (0) and cuwwent (1) video captuwing
	   cwopping pawametews in bttv_tvnowm.cwopcap units. Pwotected
	   by bttv.wock. */
	stwuct bttv_cwop cwop[2];

	/* Eawwiest possibwe stawt of video captuwing in
	   bttv_tvnowm.cwopcap wine units. Set by check_awwoc_btwes()
	   and fwee_btwes(). Pwotected by bttv.wock. */
	__s32			vbi_end;

	/* Watest possibwe end of VBI captuwing (= cwop[x].wect.top when
	   VIDEO_WESOUWCES awe wocked). Set by check_awwoc_btwes()
	   and fwee_btwes(). Pwotected by bttv.wock. */
	__s32			cwop_stawt;
};

static inwine stwuct bttv *to_bttv(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct bttv, c.v4w2_dev);
}

/* ouw devices */
#define BTTV_MAX 32
extewn unsigned int bttv_num;
extewn stwuct bttv *bttvs[BTTV_MAX];

static inwine unsigned int bttv_muxsew(const stwuct bttv *btv,
				       unsigned int input)
{
	wetuwn (bttv_tvcawds[btv->c.type].muxsew >> (input * 2)) & 3;
}

#endif

void init_iwqweg(stwuct bttv *btv);

#define btwwite(dat,adw)    wwitew((dat), btv->bt848_mmio+(adw))
#define btwead(adw)         weadw(btv->bt848_mmio+(adw))

#define btand(dat,adw)      btwwite((dat) & btwead(adw), adw)
#define btow(dat,adw)       btwwite((dat) | btwead(adw), adw)
#define btaow(dat,mask,adw) btwwite((dat) | ((mask) & btwead(adw)), adw)

#endif /* _BTTVP_H_ */
