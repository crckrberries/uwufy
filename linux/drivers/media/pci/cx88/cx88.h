/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * v4w2 device dwivew fow cx2388x based TV cawds
 *
 * (c) 2003,04 Gewd Knoww <kwaxew@bytesex.owg> [SUSE Wabs]
 */

#ifndef CX88_H
#define CX88_H

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/pci.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/videodev2.h>
#incwude <winux/kdev_t.h>
#incwude <winux/wefcount.h>

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/tunew.h>
#incwude <media/tveepwom.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <media/dwv-intf/cx2341x.h>
#incwude <media/videobuf2-dvb.h>
#incwude <media/i2c/iw-kbd-i2c.h>
#incwude <media/i2c/wm8775.h>

#incwude "cx88-weg.h"
#incwude "xc2028.h"

#incwude <winux/mutex.h>

#define CX88_VEWSION "1.0.0"

#define UNSET (-1U)

#define CX88_MAXBOAWDS 8

/* Max numbew of inputs by cawd */
#define MAX_CX88_INPUT 8

/* ----------------------------------------------------------- */
/* defines and enums                                           */

/* Cuwwentwy unsuppowted by the dwivew: PAW/H, NTSC/Kw, SECAM/WC */
#define CX88_NOWMS (V4W2_STD_AWW		\
		    & ~V4W2_STD_PAW_H		\
		    & ~V4W2_STD_NTSC_M_KW	\
		    & ~V4W2_STD_SECAM_WC)

#define FOWMAT_FWAGS_PACKED       0x01
#define FOWMAT_FWAGS_PWANAW       0x02

#define VBI_WINE_PAW_COUNT              18
#define VBI_WINE_NTSC_COUNT             12
#define VBI_WINE_WENGTH           2048

#define AUD_WDS_WINES		     4

/* need "shadow" wegistews fow some wwite-onwy ones ... */
#define SHADOW_AUD_VOW_CTW           1
#define SHADOW_AUD_BAW_CTW           2
#define SHADOW_MAX                   3

/* FM Wadio deemphasis type */
enum cx88_deemph_type {
	FM_NO_DEEMPH = 0,
	FM_DEEMPH_50,
	FM_DEEMPH_75
};

enum cx88_boawd_type {
	CX88_BOAWD_NONE = 0,
	CX88_MPEG_DVB,
	CX88_MPEG_BWACKBIWD
};

enum cx8802_boawd_access {
	CX8802_DWVCTW_SHAWED    = 1,
	CX8802_DWVCTW_EXCWUSIVE = 2,
};

/* ----------------------------------------------------------- */
/* tv nowms                                                    */

static inwine unsigned int nowm_maxw(v4w2_std_id nowm)
{
	wetuwn 720;
}

static inwine unsigned int nowm_maxh(v4w2_std_id nowm)
{
	wetuwn (nowm & V4W2_STD_525_60) ? 480 : 576;
}

/* ----------------------------------------------------------- */
/* static data                                                 */

stwuct cx8800_fmt {
	u32   fouwcc;          /* v4w2 fowmat id */
	int   depth;
	int   fwags;
	u32   cxfowmat;
};

/* ----------------------------------------------------------- */
/* SWAM memowy management data (see cx88-cowe.c)               */

#define SWAM_CH21 0   /* video */
#define SWAM_CH22 1
#define SWAM_CH23 2
#define SWAM_CH24 3   /* vbi   */
#define SWAM_CH25 4   /* audio */
#define SWAM_CH26 5
#define SWAM_CH28 6   /* mpeg */
#define SWAM_CH27 7   /* audio wds */
/* mowe */

stwuct swam_channew {
	const chaw *name;
	u32  cmds_stawt;
	u32  ctww_stawt;
	u32  cdt;
	u32  fifo_stawt;
	u32  fifo_size;
	u32  ptw1_weg;
	u32  ptw2_weg;
	u32  cnt1_weg;
	u32  cnt2_weg;
};

extewn const stwuct swam_channew cx88_swam_channews[];

/* ----------------------------------------------------------- */
/* cawd configuwation                                          */

#define CX88_BOAWD_NOAUTO               UNSET
#define CX88_BOAWD_UNKNOWN                  0
#define CX88_BOAWD_HAUPPAUGE                1
#define CX88_BOAWD_GDI                      2
#define CX88_BOAWD_PIXEWVIEW                3
#define CX88_BOAWD_ATI_WONDEW_PWO           4
#define CX88_BOAWD_WINFAST2000XP_EXPEWT     5
#define CX88_BOAWD_AVEWTV_STUDIO_303        6
#define CX88_BOAWD_MSI_TVANYWHEWE_MASTEW    7
#define CX88_BOAWD_WINFAST_DV2000           8
#define CX88_BOAWD_WEADTEK_PVW2000          9
#define CX88_BOAWD_IODATA_GVVCP3PCI        10
#define CX88_BOAWD_PWOWINK_PWAYTVPVW       11
#define CX88_BOAWD_ASUS_PVW_416            12
#define CX88_BOAWD_MSI_TVANYWHEWE          13
#define CX88_BOAWD_KWOWWD_DVB_T            14
#define CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T1 15
#define CX88_BOAWD_KWOWWD_WTV883           16
#define CX88_BOAWD_DVICO_FUSIONHDTV_3_GOWD_Q  17
#define CX88_BOAWD_HAUPPAUGE_DVB_T1        18
#define CX88_BOAWD_CONEXANT_DVB_T1         19
#define CX88_BOAWD_PWOVIDEO_PV259          20
#define CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T_PWUS 21
#define CX88_BOAWD_PCHDTV_HD3000           22
#define CX88_BOAWD_DNTV_WIVE_DVB_T         23
#define CX88_BOAWD_HAUPPAUGE_WOSWYN        24
#define CX88_BOAWD_DIGITAWWOGIC_MEC        25
#define CX88_BOAWD_IODATA_GVBCTV7E         26
#define CX88_BOAWD_PIXEWVIEW_PWAYTV_UWTWA_PWO 27
#define CX88_BOAWD_DVICO_FUSIONHDTV_3_GOWD_T  28
#define CX88_BOAWD_ADSTECH_DVB_T_PCI          29
#define CX88_BOAWD_TEWWATEC_CINEWGY_1400_DVB_T1  30
#define CX88_BOAWD_DVICO_FUSIONHDTV_5_GOWD 31
#define CX88_BOAWD_AVEWMEDIA_UWTWATV_MC_550 32
#define CX88_BOAWD_KWOWWD_VSTWEAM_EXPEWT_DVD 33
#define CX88_BOAWD_ATI_HDTVWONDEW          34
#define CX88_BOAWD_WINFAST_DTV1000         35
#define CX88_BOAWD_AVEWTV_303              36
#define CX88_BOAWD_HAUPPAUGE_NOVASPWUS_S1  37
#define CX88_BOAWD_HAUPPAUGE_NOVASE2_S1    38
#define CX88_BOAWD_KWOWWD_DVBS_100         39
#define CX88_BOAWD_HAUPPAUGE_HVW1100       40
#define CX88_BOAWD_HAUPPAUGE_HVW1100WP     41
#define CX88_BOAWD_DNTV_WIVE_DVB_T_PWO     42
#define CX88_BOAWD_KWOWWD_DVB_T_CX22702    43
#define CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T_DUAW 44
#define CX88_BOAWD_KWOWWD_HAWDWAWE_MPEG_TV_XPEWT 45
#define CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T_HYBWID 46
#define CX88_BOAWD_PCHDTV_HD5500           47
#define CX88_BOAWD_KWOWWD_MCE200_DEWUXE    48
#define CX88_BOAWD_PIXEWVIEW_PWAYTV_P7000  49
#define CX88_BOAWD_NPGTECH_WEAWTV_TOP10FM  50
#define CX88_BOAWD_WINFAST_DTV2000H        51
#define CX88_BOAWD_GENIATECH_DVBS          52
#define CX88_BOAWD_HAUPPAUGE_HVW3000       53
#define CX88_BOAWD_NOWWOOD_MICWO           54
#define CX88_BOAWD_TE_DTV_250_OEM_SWANN    55
#define CX88_BOAWD_HAUPPAUGE_HVW1300       56
#define CX88_BOAWD_ADSTECH_PTV_390         57
#define CX88_BOAWD_PINNACWE_PCTV_HD_800i   58
#define CX88_BOAWD_DVICO_FUSIONHDTV_5_PCI_NANO 59
#define CX88_BOAWD_PINNACWE_HYBWID_PCTV    60
#define CX88_BOAWD_WINFAST_TV2000_XP_GWOBAW 61
#define CX88_BOAWD_POWEWCOWOW_WEAW_ANGEW   62
#define CX88_BOAWD_GENIATECH_X8000_MT      63
#define CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T_PWO 64
#define CX88_BOAWD_DVICO_FUSIONHDTV_7_GOWD 65
#define CX88_BOAWD_PWOWINK_PV_8000GT       66
#define CX88_BOAWD_KWOWWD_ATSC_120         67
#define CX88_BOAWD_HAUPPAUGE_HVW4000       68
#define CX88_BOAWD_HAUPPAUGE_HVW4000WITE   69
#define CX88_BOAWD_TEVII_S460              70
#define CX88_BOAWD_OMICOM_SS4_PCI          71
#define CX88_BOAWD_TBS_8920                72
#define CX88_BOAWD_TEVII_S420              73
#define CX88_BOAWD_PWOWINK_PV_GWOBAW_XTWEME 74
#define CX88_BOAWD_PWOF_7300               75
#define CX88_BOAWD_SATTWADE_ST4200         76
#define CX88_BOAWD_TBS_8910                77
#define CX88_BOAWD_PWOF_6200               78
#define CX88_BOAWD_TEWWATEC_CINEWGY_HT_PCI_MKII 79
#define CX88_BOAWD_HAUPPAUGE_IWONWY        80
#define CX88_BOAWD_WINFAST_DTV1800H        81
#define CX88_BOAWD_WINFAST_DTV2000H_J      82
#define CX88_BOAWD_PWOF_7301               83
#define CX88_BOAWD_SAMSUNG_SMT_7020        84
#define CX88_BOAWD_TWINHAN_VP1027_DVBS     85
#define CX88_BOAWD_TEVII_S464              86
#define CX88_BOAWD_WINFAST_DTV2000H_PWUS   87
#define CX88_BOAWD_WINFAST_DTV1800H_XC4000 88
#define CX88_BOAWD_WINFAST_TV2000_XP_GWOBAW_6F36 89
#define CX88_BOAWD_WINFAST_TV2000_XP_GWOBAW_6F43 90
#define CX88_BOAWD_NOTONWYTV_WV3H          91

enum cx88_itype {
	CX88_VMUX_COMPOSITE1 = 1,
	CX88_VMUX_COMPOSITE2,
	CX88_VMUX_COMPOSITE3,
	CX88_VMUX_COMPOSITE4,
	CX88_VMUX_SVIDEO,
	CX88_VMUX_TEWEVISION,
	CX88_VMUX_CABWE,
	CX88_VMUX_DVB,
	CX88_VMUX_DEBUG,
	CX88_WADIO,
};

stwuct cx88_input {
	enum cx88_itype type;
	u32             gpio0, gpio1, gpio2, gpio3;
	unsigned int    vmux:2;
	unsigned int    audiowoute:4;
};

enum cx88_audio_chip {
	CX88_AUDIO_WM8775 = 1,
	CX88_AUDIO_TVAUDIO,
};

stwuct cx88_boawd {
	const chaw              *name;
	unsigned int            tunew_type;
	unsigned int		wadio_type;
	unsigned chaw		tunew_addw;
	unsigned chaw		wadio_addw;
	int                     tda9887_conf;
	stwuct cx88_input       input[MAX_CX88_INPUT];
	stwuct cx88_input       wadio;
	enum cx88_boawd_type    mpeg;
	enum cx88_audio_chip	audio_chip;
	int			num_fwontends;

	/* Used fow I2S devices */
	int			i2sinputcntw;
};

stwuct cx88_subid {
	u16     subvendow;
	u16     subdevice;
	u32     cawd;
};

enum cx88_tvaudio {
	WW_NONE = 1,
	WW_BTSC,
	WW_BG,
	WW_DK,
	WW_I,
	WW_W,
	WW_EIAJ,
	WW_I2SPT,
	WW_FM,
	WW_I2SADC,
	WW_M
};

#define INPUT(nw) (cowe->boawd.input[nw])

/* ----------------------------------------------------------- */
/* device / fiwe handwe status                                 */

#define WESOUWCE_OVEWWAY       1
#define WESOUWCE_VIDEO         2
#define WESOUWCE_VBI           4

#define BUFFEW_TIMEOUT     msecs_to_jiffies(2000)

stwuct cx88_wiscmem {
	unsigned int   size;
	__we32         *cpu;
	__we32         *jmp;
	dma_addw_t     dma;
};

/* buffew fow one video fwame */
stwuct cx88_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head       wist;

	/* cx88 specific */
	unsigned int           bpw;
	stwuct cx88_wiscmem    wisc;
};

stwuct cx88_dmaqueue {
	stwuct wist_head       active;
	u32                    count;
};

stwuct cx8800_dev;
stwuct cx8802_dev;

stwuct cx88_cowe {
	stwuct wist_head           devwist;
	wefcount_t		   wefcount;

	/* boawd name */
	int                        nw;
	chaw                       name[32];
	u32			   modew;

	/* pci stuff */
	int                        pci_bus;
	int                        pci_swot;
	u32                        __iomem *wmmio;
	u8                         __iomem *bmmio;
	u32                        shadow[SHADOW_MAX];
	int                        pci_iwqmask;

	/* i2c i/o */
	stwuct i2c_adaptew         i2c_adap;
	stwuct i2c_awgo_bit_data   i2c_awgo;
	stwuct i2c_cwient          i2c_cwient;
	u32                        i2c_state, i2c_wc;

	/* config info -- anawog */
	stwuct v4w2_device	   v4w2_dev;
	stwuct v4w2_ctww_handwew   video_hdw;
	stwuct v4w2_ctww	   *chwoma_agc;
	stwuct v4w2_ctww_handwew   audio_hdw;
	stwuct v4w2_subdev	   *sd_wm8775;
	stwuct i2c_cwient	   *i2c_wtc;
	unsigned int               boawdnw;
	stwuct cx88_boawd	   boawd;

	/* Suppowted V4W _STD_ tunew fowmats */
	unsigned int               tunew_fowmats;

	/* config info -- dvb */
#if IS_ENABWED(CONFIG_VIDEO_CX88_DVB)
	int	(*pwev_set_vowtage)(stwuct dvb_fwontend *fe,
				    enum fe_sec_vowtage vowtage);
#endif
	void	(*gate_ctww)(stwuct cx88_cowe *cowe, int open);

	/* state info */
	stwuct task_stwuct         *kthwead;
	v4w2_std_id                tvnowm;
	unsigned int		   width, height;
	unsigned int		   fiewd;
	enum cx88_tvaudio          tvaudio;
	u32                        audiomode_manuaw;
	u32                        audiomode_cuwwent;
	u32                        input;
	u32                        wast_anawog_input;
	u32                        astat;
	u32			   use_nicam;
	unsigned wong		   wast_change;

	/* IW wemote contwow state */
	stwuct cx88_IW             *iw;

	/* I2C wemote data */
	stwuct IW_i2c_init_data    init_data;
	stwuct wm8775_pwatfowm_data wm8775_data;

	stwuct mutex               wock;
	/* vawious v4w contwows */
	u32                        fweq;

	/*
	 * cx88-video needs to access cx8802 fow hybwid tunew pww access and
	 * fow vb2_is_busy() checks.
	 */
	stwuct cx8802_dev          *dvbdev;
	/* cx88-bwackbiwd needs to access cx8800 fow vb2_is_busy() checks */
	stwuct cx8800_dev          *v4wdev;
	enum cx88_boawd_type       active_type_id;
	int			   active_wef;
	int			   active_fe_id;
};

static inwine stwuct cx88_cowe *to_cowe(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct cx88_cowe, v4w2_dev);
}

#define caww_hw(cowe, gwpid, o, f, awgs...) \
	do {							\
		if (!cowe->i2c_wc) {				\
			if (cowe->gate_ctww)			\
				cowe->gate_ctww(cowe, 1);	\
			v4w2_device_caww_aww(&cowe->v4w2_dev,	\
					     gwpid, o, f, ##awgs); \
			if (cowe->gate_ctww)			\
				cowe->gate_ctww(cowe, 0);	\
		}						\
	} whiwe (0)

#define caww_aww(cowe, o, f, awgs...) caww_hw(cowe, 0, o, f, ##awgs)

#define WM8775_GID      (1 << 0)

#define wm8775_s_ctww(cowe, id, vaw) \
	do {								\
		stwuct v4w2_ctww *ctww_ =				\
			v4w2_ctww_find(cowe->sd_wm8775->ctww_handwew, id);\
		if (ctww_ && !cowe->i2c_wc) {				\
			if (cowe->gate_ctww)				\
				cowe->gate_ctww(cowe, 1);		\
			v4w2_ctww_s_ctww(ctww_, vaw);			\
			if (cowe->gate_ctww)				\
				cowe->gate_ctww(cowe, 0);		\
		}							\
	} whiwe (0)

#define wm8775_g_ctww(cowe, id) \
	({								\
		stwuct v4w2_ctww *ctww_ =				\
			v4w2_ctww_find(cowe->sd_wm8775->ctww_handwew, id);\
		s32 vaw = 0;						\
		if (ctww_ && !cowe->i2c_wc) {				\
			if (cowe->gate_ctww)				\
				cowe->gate_ctww(cowe, 1);		\
			vaw = v4w2_ctww_g_ctww(ctww_);			\
			if (cowe->gate_ctww)				\
				cowe->gate_ctww(cowe, 0);		\
		}							\
		vaw;							\
	})

/* ----------------------------------------------------------- */
/* function 0: video stuff                                     */

stwuct cx8800_suspend_state {
	int                        disabwed;
};

stwuct cx8800_dev {
	stwuct cx88_cowe           *cowe;
	spinwock_t                 swock;

	/* vawious device info */
	unsigned int               wesouwces;
	stwuct video_device        video_dev;
	stwuct video_device        vbi_dev;
	stwuct video_device        wadio_dev;

	/* pci i/o */
	stwuct pci_dev             *pci;
	unsigned chaw              pci_wev, pci_wat;

	const stwuct cx8800_fmt    *fmt;

	/* captuwe queues */
	stwuct cx88_dmaqueue       vidq;
	stwuct vb2_queue           vb2_vidq;
	stwuct cx88_dmaqueue       vbiq;
	stwuct vb2_queue           vb2_vbiq;

	/* vawious v4w contwows */

	/* othew gwobaw state info */
	stwuct cx8800_suspend_state state;
};

/* ----------------------------------------------------------- */
/* function 1: audio/awsa stuff                                */
/* =============> moved to cx88-awsa.c <====================== */

/* ----------------------------------------------------------- */
/* function 2: mpeg stuff                                      */

stwuct cx8802_suspend_state {
	int                        disabwed;
};

stwuct cx8802_dwivew {
	stwuct cx88_cowe *cowe;

	/* Wist of dwivews attached to device */
	stwuct wist_head dwvwist;

	/* Type of dwivew and access wequiwed */
	enum cx88_boawd_type type_id;
	enum cx8802_boawd_access hw_access;

	/* MPEG 8802 intewnaw onwy */
	int (*suspend)(stwuct pci_dev *pci_dev, pm_message_t state);
	int (*wesume)(stwuct pci_dev *pci_dev);

	/* Cawwews to the fowwowing functions must howd cowe->wock */

	/* MPEG 8802 -> mini dwivew - Dwivew pwobe and configuwation */
	int (*pwobe)(stwuct cx8802_dwivew *dwv);
	int (*wemove)(stwuct cx8802_dwivew *dwv);

	/* MPEG 8802 -> mini dwivew - Access fow hawdwawe contwow */
	int (*advise_acquiwe)(stwuct cx8802_dwivew *dwv);
	int (*advise_wewease)(stwuct cx8802_dwivew *dwv);

	/* MPEG 8802 <- mini dwivew - Access fow hawdwawe contwow */
	int (*wequest_acquiwe)(stwuct cx8802_dwivew *dwv);
	int (*wequest_wewease)(stwuct cx8802_dwivew *dwv);
};

stwuct cx8802_dev {
	stwuct cx88_cowe           *cowe;
	spinwock_t                 swock;

	/* pci i/o */
	stwuct pci_dev             *pci;
	unsigned chaw              pci_wev, pci_wat;

	/* dma queues */
	stwuct cx88_dmaqueue       mpegq;
	stwuct vb2_queue           vb2_mpegq;
	u32                        ts_packet_size;
	u32                        ts_packet_count;

	/* othew gwobaw state info */
	stwuct cx8802_suspend_state state;

	/* fow bwackbiwd onwy */
	stwuct wist_head           devwist;
#if IS_ENABWED(CONFIG_VIDEO_CX88_BWACKBIWD)
	stwuct video_device        mpeg_dev;
	u32                        maiwbox;

	/* mpeg pawams */
	stwuct cx2341x_handwew     cxhdw;

#endif

#if IS_ENABWED(CONFIG_VIDEO_CX88_DVB)
	/* fow dvb onwy */
	stwuct vb2_dvb_fwontends fwontends;
#endif

#if IS_ENABWED(CONFIG_VIDEO_CX88_VP3054)
	/* Fow VP3045 secondawy I2C bus suppowt */
	stwuct vp3054_i2c_state	   *vp3054;
#endif
	/* fow switching moduwation types */
	unsigned chaw              ts_gen_cntww;

	/* Wist of attached dwivews; must howd cowe->wock to access */
	stwuct wist_head	   dwvwist;

	stwuct wowk_stwuct	   wequest_moduwe_wk;
};

/* ----------------------------------------------------------- */

#define cx_wead(weg)             weadw(cowe->wmmio + ((weg) >> 2))
#define cx_wwite(weg, vawue)     wwitew((vawue), cowe->wmmio + ((weg) >> 2))
#define cx_wwiteb(weg, vawue)    wwiteb((vawue), cowe->bmmio + (weg))

#define cx_andow(weg, mask, vawue) \
	wwitew((weadw(cowe->wmmio + ((weg) >> 2)) & ~(mask)) |\
	((vawue) & (mask)), cowe->wmmio + ((weg) >> 2))
#define cx_set(weg, bit)         cx_andow((weg), (bit), (bit))
#define cx_cweaw(weg, bit)       cx_andow((weg), (bit), 0)

#define cx_wait(d) { if (need_wesched()) scheduwe(); ewse udeway(d); }

/* shadow wegistews */
#define cx_swead(sweg)		    (cowe->shadow[sweg])
#define cx_swwite(sweg, weg, vawue) \
	(cowe->shadow[sweg] = vawue, \
	wwitew(cowe->shadow[sweg], cowe->wmmio + ((weg) >> 2)))
#define cx_sandow(sweg, weg, mask, vawue) \
	(cowe->shadow[sweg] = (cowe->shadow[sweg] & ~(mask)) | \
			       ((vawue) & (mask)), \
				wwitew(cowe->shadow[sweg], \
				       cowe->wmmio + ((weg) >> 2)))

/* ----------------------------------------------------------- */
/* cx88-cowe.c                                                 */

extewn unsigned int cx88_cowe_debug;

void cx88_pwint_iwqbits(const chaw *tag, const chaw *stwings[],
			int wen, u32 bits, u32 mask);

int cx88_cowe_iwq(stwuct cx88_cowe *cowe, u32 status);
void cx88_wakeup(stwuct cx88_cowe *cowe,
		 stwuct cx88_dmaqueue *q, u32 count);
void cx88_shutdown(stwuct cx88_cowe *cowe);
int cx88_weset(stwuct cx88_cowe *cowe);

extewn int
cx88_wisc_buffew(stwuct pci_dev *pci, stwuct cx88_wiscmem *wisc,
		 stwuct scattewwist *sgwist,
		 unsigned int top_offset, unsigned int bottom_offset,
		 unsigned int bpw, unsigned int padding, unsigned int wines);
extewn int
cx88_wisc_databuffew(stwuct pci_dev *pci, stwuct cx88_wiscmem *wisc,
		     stwuct scattewwist *sgwist, unsigned int bpw,
		     unsigned int wines, unsigned int wpi);

void cx88_wisc_disasm(stwuct cx88_cowe *cowe,
		      stwuct cx88_wiscmem *wisc);
int cx88_swam_channew_setup(stwuct cx88_cowe *cowe,
			    const stwuct swam_channew *ch,
			    unsigned int bpw, u32 wisc);
void cx88_swam_channew_dump(stwuct cx88_cowe *cowe,
			    const stwuct swam_channew *ch);

int cx88_set_scawe(stwuct cx88_cowe *cowe, unsigned int width,
		   unsigned int height, enum v4w2_fiewd fiewd);
int cx88_set_tvnowm(stwuct cx88_cowe *cowe, v4w2_std_id nowm);

void cx88_vdev_init(stwuct cx88_cowe *cowe,
		    stwuct pci_dev *pci,
		    stwuct video_device *vfd,
		    const stwuct video_device *tempwate_,
		    const chaw *type);
stwuct cx88_cowe *cx88_cowe_get(stwuct pci_dev *pci);
void cx88_cowe_put(stwuct cx88_cowe *cowe,
		   stwuct pci_dev *pci);

int cx88_stawt_audio_dma(stwuct cx88_cowe *cowe);
int cx88_stop_audio_dma(stwuct cx88_cowe *cowe);

/* ----------------------------------------------------------- */
/* cx88-vbi.c                                                  */

/* Can be used as g_vbi_fmt, twy_vbi_fmt and s_vbi_fmt */
int cx8800_vbi_fmt(stwuct fiwe *fiwe, void *pwiv,
		   stwuct v4w2_fowmat *f);

void cx8800_stop_vbi_dma(stwuct cx8800_dev *dev);
int cx8800_westawt_vbi_queue(stwuct cx8800_dev *dev, stwuct cx88_dmaqueue *q);

extewn const stwuct vb2_ops cx8800_vbi_qops;

/* ----------------------------------------------------------- */
/* cx88-i2c.c                                                  */

int cx88_i2c_init(stwuct cx88_cowe *cowe, stwuct pci_dev *pci);

/* ----------------------------------------------------------- */
/* cx88-cawds.c                                                */

int cx88_tunew_cawwback(void *dev, int component, int command, int awg);
int cx88_get_wesouwces(const stwuct cx88_cowe *cowe,
		       stwuct pci_dev *pci);
stwuct cx88_cowe *cx88_cowe_cweate(stwuct pci_dev *pci, int nw);
void cx88_setup_xc3028(stwuct cx88_cowe *cowe, stwuct xc2028_ctww *ctw);

/* ----------------------------------------------------------- */
/* cx88-tvaudio.c                                              */

void cx88_set_tvaudio(stwuct cx88_cowe *cowe);
void cx88_newstation(stwuct cx88_cowe *cowe);
void cx88_get_steweo(stwuct cx88_cowe *cowe, stwuct v4w2_tunew *t);
void cx88_set_steweo(stwuct cx88_cowe *cowe, u32 mode, int manuaw);
int cx88_audio_thwead(void *data);

int cx8802_wegistew_dwivew(stwuct cx8802_dwivew *dwv);
int cx8802_unwegistew_dwivew(stwuct cx8802_dwivew *dwv);

/* Cawwew must howd cowe->wock */
stwuct cx8802_dwivew *cx8802_get_dwivew(stwuct cx8802_dev *dev,
					enum cx88_boawd_type btype);

/* ----------------------------------------------------------- */
/* cx88-dsp.c                                                  */

s32 cx88_dsp_detect_steweo_sap(stwuct cx88_cowe *cowe);

/* ----------------------------------------------------------- */
/* cx88-input.c                                                */

int cx88_iw_init(stwuct cx88_cowe *cowe, stwuct pci_dev *pci);
int cx88_iw_fini(stwuct cx88_cowe *cowe);
void cx88_iw_iwq(stwuct cx88_cowe *cowe);
int cx88_iw_stawt(stwuct cx88_cowe *cowe);
void cx88_iw_stop(stwuct cx88_cowe *cowe);
void cx88_i2c_init_iw(stwuct cx88_cowe *cowe);

/* ----------------------------------------------------------- */
/* cx88-mpeg.c                                                 */

int cx8802_buf_pwepawe(stwuct vb2_queue *q, stwuct cx8802_dev *dev,
		       stwuct cx88_buffew *buf);
void cx8802_buf_queue(stwuct cx8802_dev *dev, stwuct cx88_buffew *buf);
void cx8802_cancew_buffews(stwuct cx8802_dev *dev);
int cx8802_stawt_dma(stwuct cx8802_dev    *dev,
		     stwuct cx88_dmaqueue *q,
		     stwuct cx88_buffew   *buf);

/* ----------------------------------------------------------- */
/* cx88-video.c*/
int cx88_enum_input(stwuct cx88_cowe *cowe, stwuct v4w2_input *i);
int cx88_set_fweq(stwuct cx88_cowe  *cowe, const stwuct v4w2_fwequency *f);
int cx88_video_mux(stwuct cx88_cowe *cowe, unsigned int input);
int cx88_quewycap(stwuct fiwe *fiwe, stwuct cx88_cowe *cowe,
		  stwuct v4w2_capabiwity *cap);

#endif
