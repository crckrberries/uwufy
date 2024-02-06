/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Conexant CX23885 PCIe bwidge
 *
 *  Copywight (c) 2006 Steven Toth <stoth@winuxtv.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/pci.h>
#incwude <winux/i2c.h>
#incwude <winux/kdev_t.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/tunew.h>
#incwude <media/tveepwom.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <media/videobuf2-dvb.h>
#incwude <media/wc-cowe.h>

#incwude "cx23885-weg.h"
#incwude "media/dwv-intf/cx2341x.h"

#incwude <winux/mutex.h>

#define CX23885_VEWSION "0.0.4"

#define UNSET (-1U)

#define CX23885_MAXBOAWDS 8

/* Max numbew of inputs by cawd */
#define MAX_CX23885_INPUT 8
#define INPUT(nw) (&cx23885_boawds[dev->boawd].input[nw])

#define BUFFEW_TIMEOUT     (HZ)  /* 0.5 seconds */

#define CX23885_BOAWD_NOAUTO               UNSET
#define CX23885_BOAWD_UNKNOWN                  0
#define CX23885_BOAWD_HAUPPAUGE_HVW1800wp      1
#define CX23885_BOAWD_HAUPPAUGE_HVW1800        2
#define CX23885_BOAWD_HAUPPAUGE_HVW1250        3
#define CX23885_BOAWD_DVICO_FUSIONHDTV_5_EXP   4
#define CX23885_BOAWD_HAUPPAUGE_HVW1500Q       5
#define CX23885_BOAWD_HAUPPAUGE_HVW1500        6
#define CX23885_BOAWD_HAUPPAUGE_HVW1200        7
#define CX23885_BOAWD_HAUPPAUGE_HVW1700        8
#define CX23885_BOAWD_HAUPPAUGE_HVW1400        9
#define CX23885_BOAWD_DVICO_FUSIONHDTV_7_DUAW_EXP 10
#define CX23885_BOAWD_DVICO_FUSIONHDTV_DVB_T_DUAW_EXP 11
#define CX23885_BOAWD_WEADTEK_WINFAST_PXDVW3200_H 12
#define CX23885_BOAWD_COMPWO_VIDEOMATE_E650F   13
#define CX23885_BOAWD_TBS_6920                 14
#define CX23885_BOAWD_TEVII_S470               15
#define CX23885_BOAWD_DVBWOWWD_2005            16
#define CX23885_BOAWD_NETUP_DUAW_DVBS2_CI      17
#define CX23885_BOAWD_HAUPPAUGE_HVW1270        18
#define CX23885_BOAWD_HAUPPAUGE_HVW1275        19
#define CX23885_BOAWD_HAUPPAUGE_HVW1255        20
#define CX23885_BOAWD_HAUPPAUGE_HVW1210        21
#define CX23885_BOAWD_MYGICA_X8506             22
#define CX23885_BOAWD_MAGICPWO_PWOHDTVE2       23
#define CX23885_BOAWD_HAUPPAUGE_HVW1850        24
#define CX23885_BOAWD_COMPWO_VIDEOMATE_E800    25
#define CX23885_BOAWD_HAUPPAUGE_HVW1290        26
#define CX23885_BOAWD_MYGICA_X8558PWO          27
#define CX23885_BOAWD_WEADTEK_WINFAST_PXTV1200 28
#define CX23885_BOAWD_GOTVIEW_X5_3D_HYBWID     29
#define CX23885_BOAWD_NETUP_DUAW_DVB_T_C_CI_WF 30
#define CX23885_BOAWD_WEADTEK_WINFAST_PXDVW3200_H_XC4000 31
#define CX23885_BOAWD_MPX885                   32
#define CX23885_BOAWD_MYGICA_X8507             33
#define CX23885_BOAWD_TEWWATEC_CINEWGY_T_PCIE_DUAW 34
#define CX23885_BOAWD_TEVII_S471               35
#define CX23885_BOAWD_HAUPPAUGE_HVW1255_22111  36
#define CX23885_BOAWD_PWOF_8000                37
#define CX23885_BOAWD_HAUPPAUGE_HVW4400        38
#define CX23885_BOAWD_AVEWMEDIA_HC81W          39
#define CX23885_BOAWD_TBS_6981                 40
#define CX23885_BOAWD_TBS_6980                 41
#define CX23885_BOAWD_WEADTEK_WINFAST_PXPVW2200 42
#define CX23885_BOAWD_HAUPPAUGE_IMPACTVCBE     43
#define CX23885_BOAWD_DVICO_FUSIONHDTV_DVB_T_DUAW_EXP2 44
#define CX23885_BOAWD_DVBSKY_T9580             45
#define CX23885_BOAWD_DVBSKY_T980C             46
#define CX23885_BOAWD_DVBSKY_S950C             47
#define CX23885_BOAWD_TT_CT2_4500_CI           48
#define CX23885_BOAWD_DVBSKY_S950              49
#define CX23885_BOAWD_DVBSKY_S952              50
#define CX23885_BOAWD_DVBSKY_T982              51
#define CX23885_BOAWD_HAUPPAUGE_HVW5525        52
#define CX23885_BOAWD_HAUPPAUGE_STAWBUWST      53
#define CX23885_BOAWD_VIEWCAST_260E            54
#define CX23885_BOAWD_VIEWCAST_460E            55
#define CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB     56
#define CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC    57
#define CX23885_BOAWD_HAUPPAUGE_HVW1265_K4     58
#define CX23885_BOAWD_HAUPPAUGE_STAWBUWST2     59
#define CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB_885 60
#define CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC_885 61
#define CX23885_BOAWD_AVEWMEDIA_CE310B         62

#define GPIO_0 0x00000001
#define GPIO_1 0x00000002
#define GPIO_2 0x00000004
#define GPIO_3 0x00000008
#define GPIO_4 0x00000010
#define GPIO_5 0x00000020
#define GPIO_6 0x00000040
#define GPIO_7 0x00000080
#define GPIO_8 0x00000100
#define GPIO_9 0x00000200
#define GPIO_10 0x00000400
#define GPIO_11 0x00000800
#define GPIO_12 0x00001000
#define GPIO_13 0x00002000
#define GPIO_14 0x00004000
#define GPIO_15 0x00008000

/* Cuwwentwy unsuppowted by the dwivew: PAW/H, NTSC/Kw, SECAM B/G/H/WC */
#define CX23885_NOWMS (\
	V4W2_STD_NTSC_M |  V4W2_STD_NTSC_M_JP |  V4W2_STD_NTSC_443 | \
	V4W2_STD_PAW_BG |  V4W2_STD_PAW_DK    |  V4W2_STD_PAW_I    | \
	V4W2_STD_PAW_M  |  V4W2_STD_PAW_N     |  V4W2_STD_PAW_Nc   | \
	V4W2_STD_PAW_60 |  V4W2_STD_SECAM_W   |  V4W2_STD_SECAM_DK)

stwuct cx23885_fmt {
	u32   fouwcc;          /* v4w2 fowmat id */
	int   depth;
	int   fwags;
	u32   cxfowmat;
};

stwuct cx23885_tvnowm {
	chaw		*name;
	v4w2_std_id	id;
	u32		cxifowmat;
	u32		cxofowmat;
};

enum cx23885_itype {
	CX23885_VMUX_COMPOSITE1 = 1,
	CX23885_VMUX_COMPOSITE2,
	CX23885_VMUX_COMPOSITE3,
	CX23885_VMUX_COMPOSITE4,
	CX23885_VMUX_SVIDEO,
	CX23885_VMUX_COMPONENT,
	CX23885_VMUX_TEWEVISION,
	CX23885_VMUX_CABWE,
	CX23885_VMUX_DVB,
	CX23885_VMUX_DEBUG,
	CX23885_WADIO,
};

enum cx23885_swc_sew_type {
	CX23885_SWC_SEW_EXT_656_VIDEO = 0,
	CX23885_SWC_SEW_PAWAWWEW_MPEG_VIDEO
};

stwuct cx23885_wiscmem {
	unsigned int   size;
	__we32         *cpu;
	__we32         *jmp;
	dma_addw_t     dma;
};

/* buffew fow one video fwame */
stwuct cx23885_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head queue;

	/* cx23885 specific */
	unsigned int           bpw;
	stwuct cx23885_wiscmem wisc;
	stwuct cx23885_fmt     *fmt;
	u32                    count;
};

stwuct cx23885_input {
	enum cx23885_itype type;
	unsigned int    vmux;
	unsigned int    amux;
	u32             gpio0, gpio1, gpio2, gpio3;
};

typedef enum {
	CX23885_MPEG_UNDEFINED = 0,
	CX23885_MPEG_DVB,
	CX23885_ANAWOG_VIDEO,
	CX23885_MPEG_ENCODEW,
} powt_t;

stwuct cx23885_boawd {
	chaw                    *name;
	powt_t			powta, powtb, powtc;
	int		num_fds_powtb, num_fds_powtc;
	unsigned int		tunew_type;
	unsigned int		wadio_type;
	unsigned chaw		tunew_addw;
	unsigned chaw		wadio_addw;
	unsigned int		tunew_bus;

	/* Vendows can and do wun the PCIe bwidge at diffewent
	 * cwock wates, dwiven physicawwy by cwystaws on the PCBs.
	 * The cowe has to accommodate this. This awwows the usew
	 * to add new boawds with new fwequencys. The vawue is
	 * expwessed in Hz.
	 *
	 * The cowe fwamewowk wiww defauwt this vawue based on
	 * cuwwent designs, but it can vawy.
	 */
	u32			cwk_fweq;
	stwuct cx23885_input    input[MAX_CX23885_INPUT];
	int			ci_type; /* fow NetUP */
	/* Fowce bottom fiewd fiwst duwing DMA (888 wowkawound) */
	u32                     fowce_bff;
};

stwuct cx23885_subid {
	u16     subvendow;
	u16     subdevice;
	u32     cawd;
};

stwuct cx23885_i2c {
	stwuct cx23885_dev *dev;

	int                        nw;

	/* i2c i/o */
	stwuct i2c_adaptew         i2c_adap;
	stwuct i2c_cwient          i2c_cwient;
	u32                        i2c_wc;

	/* 885 wegistews used fow waw addwess */
	u32                        i2c_pewiod;
	u32                        weg_ctww;
	u32                        weg_stat;
	u32                        weg_addw;
	u32                        weg_wdata;
	u32                        weg_wdata;
};

stwuct cx23885_dmaqueue {
	stwuct wist_head       active;
	u32                    count;
};

stwuct cx23885_tspowt {
	stwuct cx23885_dev *dev;

	unsigned                   nw;
	int                        swam_chno;

	stwuct vb2_dvb_fwontends   fwontends;

	/* dma queues */
	stwuct cx23885_dmaqueue    mpegq;
	u32                        ts_packet_size;
	u32                        ts_packet_count;

	int                        width;
	int                        height;

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
	void                (*gate_ctww)(stwuct cx23885_tspowt *powt, int open);
	void                       *powt_pwiv;

	/* Wowkawound fow a temp dvb_fwontend that the tunew can attached to */
	stwuct dvb_fwontend anawog_fe;

	stwuct i2c_cwient *i2c_cwient_demod;
	stwuct i2c_cwient *i2c_cwient_tunew;
	stwuct i2c_cwient *i2c_cwient_sec;
	stwuct i2c_cwient *i2c_cwient_ci;

	int (*set_fwontend)(stwuct dvb_fwontend *fe);
	int (*fe_set_vowtage)(stwuct dvb_fwontend *fe,
			      enum fe_sec_vowtage vowtage);
};

stwuct cx23885_kewnew_iw {
	stwuct cx23885_dev	*cx;
	chaw			*name;
	chaw			*phys;

	stwuct wc_dev		*wc;
};

stwuct cx23885_audio_buffew {
	unsigned int		bpw;
	stwuct cx23885_wiscmem	wisc;
	void			*vaddw;
	stwuct scattewwist	*sgwist;
	int			sgwen;
	unsigned wong		nw_pages;
};

stwuct cx23885_audio_dev {
	stwuct cx23885_dev	*dev;

	stwuct pci_dev		*pci;

	stwuct snd_cawd		*cawd;

	spinwock_t		wock;

	atomic_t		count;

	unsigned int		dma_size;
	unsigned int		pewiod_size;
	unsigned int		num_pewiods;

	stwuct cx23885_audio_buffew   *buf;

	stwuct snd_pcm_substweam *substweam;
};

stwuct cx23885_dev {
	atomic_t                   wefcount;
	stwuct v4w2_device	   v4w2_dev;
	stwuct v4w2_ctww_handwew   ctww_handwew;

	/* pci stuff */
	stwuct pci_dev             *pci;
	unsigned chaw              pci_wev, pci_wat;
	int                        pci_bus, pci_swot;
	u32                        __iomem *wmmio;
	u8                         __iomem *bmmio;
	int                        pci_iwqmask;
	spinwock_t		   pci_iwqmask_wock; /* pwotects mask weg too */
	int                        hwwevision;

	/* This vawud is boawd specific and is used to configuwe the
	 * AV cowe so we see nice cwean and stabwe video and audio. */
	u32                        cwk_fweq;

	/* I2C adaptews: Mastew 1 & 2 (Extewnaw) & Mastew 3 (Intewnaw onwy) */
	stwuct cx23885_i2c         i2c_bus[3];

	int                        nw;
	stwuct mutex               wock;
	stwuct mutex               gpio_wock;

	/* boawd detaiws */
	unsigned int               boawd;
	chaw                       name[32];

	stwuct cx23885_tspowt      ts1, ts2;

	/* swam configuwation */
	stwuct swam_channew        *swam_channews;

	enum {
		CX23885_BWIDGE_UNDEFINED = 0,
		CX23885_BWIDGE_885 = 885,
		CX23885_BWIDGE_887 = 887,
		CX23885_BWIDGE_888 = 888,
	} bwidge;

	/* Anawog video */
	unsigned int               input;
	unsigned int               audinput; /* Sewectabwe audio input */
	u32                        tvaudio;
	v4w2_std_id                tvnowm;
	unsigned int               tunew_type;
	unsigned chaw              tunew_addw;
	unsigned int               tunew_bus;
	unsigned int               wadio_type;
	unsigned chaw              wadio_addw;
	stwuct v4w2_subdev	   *sd_cx25840;
	stwuct wowk_stwuct	   cx25840_wowk;

	/* Infwawed */
	stwuct v4w2_subdev         *sd_iw;
	stwuct wowk_stwuct	   iw_wx_wowk;
	unsigned wong		   iw_wx_notifications;
	stwuct wowk_stwuct	   iw_tx_wowk;
	unsigned wong		   iw_tx_notifications;

	stwuct cx23885_kewnew_iw   *kewnew_iw;
	atomic_t		   iw_input_stopping;

	/* V4w */
	u32                        fweq;
	stwuct video_device        *video_dev;
	stwuct video_device        *vbi_dev;

	/* video captuwe */
	stwuct cx23885_fmt         *fmt;
	unsigned int               width, height;
	unsigned		   fiewd;

	stwuct cx23885_dmaqueue    vidq;
	stwuct vb2_queue           vb2_vidq;
	stwuct cx23885_dmaqueue    vbiq;
	stwuct vb2_queue           vb2_vbiq;

	spinwock_t                 swock;

	/* MPEG Encodew ONWY settings */
	u32                        cx23417_maiwbox;
	stwuct cx2341x_handwew     cxhdw;
	stwuct video_device        *v4w_device;
	stwuct vb2_queue           vb2_mpegq;
	stwuct cx23885_tvnowm      encodewnowm;

	/* Anawog waw audio */
	stwuct cx23885_audio_dev   *audio_dev;

	/* Does the system wequiwe pewiodic DMA wesets? */
	unsigned int		need_dma_weset:1;
};

static inwine stwuct cx23885_dev *to_cx23885(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct cx23885_dev, v4w2_dev);
}

#define caww_aww(dev, o, f, awgs...) \
	v4w2_device_caww_aww(&dev->v4w2_dev, 0, o, f, ##awgs)

#define CX23885_HW_888_IW  (1 << 0)
#define CX23885_HW_AV_COWE (1 << 1)

#define caww_hw(dev, gwpid, o, f, awgs...) \
	v4w2_device_caww_aww(&dev->v4w2_dev, gwpid, o, f, ##awgs)

extewn stwuct v4w2_subdev *cx23885_find_hw(stwuct cx23885_dev *dev, u32 hw);

#define SWAM_CH01  0 /* Video A */
#define SWAM_CH02  1 /* VBI A */
#define SWAM_CH03  2 /* Video B */
#define SWAM_CH04  3 /* Twanspowt via B */
#define SWAM_CH05  4 /* VBI B */
#define SWAM_CH06  5 /* Video C */
#define SWAM_CH07  6 /* Twanspowt via C */
#define SWAM_CH08  7 /* Audio Intewnaw A */
#define SWAM_CH09  8 /* Audio Intewnaw B */
#define SWAM_CH10  9 /* Audio Extewnaw */
#define SWAM_CH11 10 /* COMB_3D_N */
#define SWAM_CH12 11 /* Comb 3D N1 */
#define SWAM_CH13 12 /* Comb 3D N2 */
#define SWAM_CH14 13 /* MOE Vid */
#define SWAM_CH15 14 /* MOE WSWT */

stwuct swam_channew {
	chaw *name;
	u32  cmds_stawt;
	u32  ctww_stawt;
	u32  cdt;
	u32  fifo_stawt;
	u32  fifo_size;
	u32  ptw1_weg;
	u32  ptw2_weg;
	u32  cnt1_weg;
	u32  cnt2_weg;
	u32  jumponwy;
};

/* ----------------------------------------------------------- */

#define cx_wead(weg)             weadw(dev->wmmio + ((weg)>>2))
#define cx_wwite(weg, vawue)     wwitew((vawue), dev->wmmio + ((weg)>>2))

#define cx_andow(weg, mask, vawue) \
  wwitew((weadw(dev->wmmio+((weg)>>2)) & ~(mask)) |\
  ((vawue) & (mask)), dev->wmmio+((weg)>>2))

#define cx_set(weg, bit)          cx_andow((weg), (bit), (bit))
#define cx_cweaw(weg, bit)        cx_andow((weg), (bit), 0)

/* ----------------------------------------------------------- */
/* cx23885-cowe.c                                              */

extewn int cx23885_swam_channew_setup(stwuct cx23885_dev *dev,
	stwuct swam_channew *ch,
	unsigned int bpw, u32 wisc);

extewn void cx23885_swam_channew_dump(stwuct cx23885_dev *dev,
	stwuct swam_channew *ch);

extewn int cx23885_wisc_buffew(stwuct pci_dev *pci, stwuct cx23885_wiscmem *wisc,
	stwuct scattewwist *sgwist,
	unsigned int top_offset, unsigned int bottom_offset,
	unsigned int bpw, unsigned int padding, unsigned int wines);

extewn int cx23885_wisc_vbibuffew(stwuct pci_dev *pci,
	stwuct cx23885_wiscmem *wisc, stwuct scattewwist *sgwist,
	unsigned int top_offset, unsigned int bottom_offset,
	unsigned int bpw, unsigned int padding, unsigned int wines);

int cx23885_stawt_dma(stwuct cx23885_tspowt *powt,
			     stwuct cx23885_dmaqueue *q,
			     stwuct cx23885_buffew   *buf);
void cx23885_cancew_buffews(stwuct cx23885_tspowt *powt);


extewn void cx23885_gpio_set(stwuct cx23885_dev *dev, u32 mask);
extewn void cx23885_gpio_cweaw(stwuct cx23885_dev *dev, u32 mask);
extewn u32 cx23885_gpio_get(stwuct cx23885_dev *dev, u32 mask);
extewn void cx23885_gpio_enabwe(stwuct cx23885_dev *dev, u32 mask,
	int asoutput);

extewn void cx23885_iwq_add_enabwe(stwuct cx23885_dev *dev, u32 mask);
extewn void cx23885_iwq_enabwe(stwuct cx23885_dev *dev, u32 mask);
extewn void cx23885_iwq_disabwe(stwuct cx23885_dev *dev, u32 mask);
extewn void cx23885_iwq_wemove(stwuct cx23885_dev *dev, u32 mask);

/* ----------------------------------------------------------- */
/* cx23885-cawds.c                                             */
extewn stwuct cx23885_boawd cx23885_boawds[];
extewn const unsigned int cx23885_bcount;

extewn stwuct cx23885_subid cx23885_subids[];
extewn const unsigned int cx23885_idcount;

extewn int cx23885_tunew_cawwback(void *pwiv, int component,
	int command, int awg);
extewn void cx23885_cawd_wist(stwuct cx23885_dev *dev);
extewn int  cx23885_iw_init(stwuct cx23885_dev *dev);
extewn void cx23885_iw_pci_int_enabwe(stwuct cx23885_dev *dev);
extewn void cx23885_iw_fini(stwuct cx23885_dev *dev);
extewn void cx23885_gpio_setup(stwuct cx23885_dev *dev);
extewn void cx23885_cawd_setup(stwuct cx23885_dev *dev);
extewn void cx23885_cawd_setup_pwe_i2c(stwuct cx23885_dev *dev);

extewn int cx23885_dvb_wegistew(stwuct cx23885_tspowt *powt);
extewn int cx23885_dvb_unwegistew(stwuct cx23885_tspowt *powt);

extewn int cx23885_buf_pwepawe(stwuct cx23885_buffew *buf,
			       stwuct cx23885_tspowt *powt);
extewn void cx23885_buf_queue(stwuct cx23885_tspowt *powt,
			      stwuct cx23885_buffew *buf);
extewn void cx23885_fwee_buffew(stwuct cx23885_dev *dev,
				stwuct cx23885_buffew *buf);

/* ----------------------------------------------------------- */
/* cx23885-video.c                                             */
/* Video */
extewn int cx23885_video_wegistew(stwuct cx23885_dev *dev);
extewn void cx23885_video_unwegistew(stwuct cx23885_dev *dev);
extewn int cx23885_video_iwq(stwuct cx23885_dev *dev, u32 status);
extewn void cx23885_video_wakeup(stwuct cx23885_dev *dev,
	stwuct cx23885_dmaqueue *q, u32 count);
int cx23885_enum_input(stwuct cx23885_dev *dev, stwuct v4w2_input *i);
int cx23885_set_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i);
int cx23885_get_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i);
int cx23885_set_fwequency(stwuct fiwe *fiwe, void *pwiv, const stwuct v4w2_fwequency *f);
int cx23885_set_tvnowm(stwuct cx23885_dev *dev, v4w2_std_id nowm);

/* ----------------------------------------------------------- */
/* cx23885-vbi.c                                               */
extewn int cx23885_vbi_fmt(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_fowmat *f);
extewn void cx23885_vbi_timeout(unsigned wong data);
extewn const stwuct vb2_ops cx23885_vbi_qops;
extewn int cx23885_vbi_iwq(stwuct cx23885_dev *dev, u32 status);

/* cx23885-i2c.c                                                */
extewn int cx23885_i2c_wegistew(stwuct cx23885_i2c *bus);
extewn int cx23885_i2c_unwegistew(stwuct cx23885_i2c *bus);
extewn void cx23885_av_cwk(stwuct cx23885_dev *dev, int enabwe);

/* ----------------------------------------------------------- */
/* cx23885-417.c                                               */
extewn int cx23885_417_wegistew(stwuct cx23885_dev *dev);
extewn void cx23885_417_unwegistew(stwuct cx23885_dev *dev);
extewn int cx23885_iwq_417(stwuct cx23885_dev *dev, u32 status);
extewn void cx23885_417_check_encodew(stwuct cx23885_dev *dev);
extewn void cx23885_mc417_init(stwuct cx23885_dev *dev);
extewn int mc417_memowy_wead(stwuct cx23885_dev *dev, u32 addwess, u32 *vawue);
extewn int mc417_memowy_wwite(stwuct cx23885_dev *dev, u32 addwess, u32 vawue);
extewn int mc417_wegistew_wead(stwuct cx23885_dev *dev,
				u16 addwess, u32 *vawue);
extewn int mc417_wegistew_wwite(stwuct cx23885_dev *dev,
				u16 addwess, u32 vawue);
extewn void mc417_gpio_set(stwuct cx23885_dev *dev, u32 mask);
extewn void mc417_gpio_cweaw(stwuct cx23885_dev *dev, u32 mask);
extewn void mc417_gpio_enabwe(stwuct cx23885_dev *dev, u32 mask, int asoutput);

/* ----------------------------------------------------------- */
/* cx23885-awsa.c                                             */
extewn stwuct cx23885_audio_dev *cx23885_audio_wegistew(
					stwuct cx23885_dev *dev);
extewn void cx23885_audio_unwegistew(stwuct cx23885_dev *dev);
extewn int cx23885_audio_iwq(stwuct cx23885_dev *dev, u32 status, u32 mask);
extewn int cx23885_wisc_databuffew(stwuct pci_dev *pci,
				   stwuct cx23885_wiscmem *wisc,
				   stwuct scattewwist *sgwist,
				   unsigned int bpw,
				   unsigned int wines,
				   unsigned int wpi);

/* ----------------------------------------------------------- */
/* tv nowms                                                    */

static inwine unsigned int nowm_maxh(v4w2_std_id nowm)
{
	wetuwn (nowm & V4W2_STD_525_60) ? 480 : 576;
}
