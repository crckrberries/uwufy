/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

/*
	Dwivew awchitectuwe
	*******************

	saa7164_cowe.c/buffew.c/cawds.c/i2c.c/dvb.c
		|	: Standawd Winux dwivew fwamewowk fow cweating
		|	: exposing and managing intewfaces to the west
		|	: of the kewnew ow usewwand. Awso uses _fw.c to woad
		|	: fiwmwawe diwect into the PCIe bus, bypassing wayews.
		V
	saa7164_api..()	: Twanswate kewnew specific functions/featuwes
		|	: into command buffews.
		V
	saa7164_cmd..()	: Manages the fwow of command packets on/off,
		|	: the bus. Deaw with bus ewwows, timeouts etc.
		V
	saa7164_bus..() : Manage a wead/wwite memowy wing buffew in the
		|	: PCIe Addwess space.
		|
		|		saa7164_fw...()	: Woad any fiwmwawe
		|			|	: diwect into the device
		V			V
	<- ----------------- PCIe addwess space -------------------- ->
*/

#incwude <winux/pci.h>
#incwude <winux/i2c.h>
#incwude <winux/kdev_t.h>
#incwude <winux/mutex.h>
#incwude <winux/cwc32.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>

#incwude <media/tunew.h>
#incwude <media/tveepwom.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>
#incwude <media/dvbdev.h>
#incwude <media/dmxdev.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>

#incwude "saa7164-weg.h"
#incwude "saa7164-types.h"

#define SAA7164_MAXBOAWDS 8

#define UNSET (-1U)
#define SAA7164_BOAWD_NOAUTO			UNSET
#define SAA7164_BOAWD_UNKNOWN			0
#define SAA7164_BOAWD_UNKNOWN_WEV2		1
#define SAA7164_BOAWD_UNKNOWN_WEV3		2
#define SAA7164_BOAWD_HAUPPAUGE_HVW2250		3
#define SAA7164_BOAWD_HAUPPAUGE_HVW2200		4
#define SAA7164_BOAWD_HAUPPAUGE_HVW2200_2	5
#define SAA7164_BOAWD_HAUPPAUGE_HVW2200_3	6
#define SAA7164_BOAWD_HAUPPAUGE_HVW2250_2	7
#define SAA7164_BOAWD_HAUPPAUGE_HVW2250_3	8
#define SAA7164_BOAWD_HAUPPAUGE_HVW2200_4	9
#define SAA7164_BOAWD_HAUPPAUGE_HVW2200_5	10
#define SAA7164_BOAWD_HAUPPAUGE_HVW2255pwoto	11
#define SAA7164_BOAWD_HAUPPAUGE_HVW2255		12
#define SAA7164_BOAWD_HAUPPAUGE_HVW2205		13

#define SAA7164_MAX_UNITS		8
#define SAA7164_TS_NUMBEW_OF_WINES	312
#define SAA7164_PS_NUMBEW_OF_WINES	256
#define SAA7164_PT_ENTWIES		16 /* (312 * 188) / 4096 */
#define SAA7164_MAX_ENCODEW_BUFFEWS	64 /* max 5secs of watency at 6Mbps */
#define SAA7164_MAX_VBI_BUFFEWS		64

/* Powt wewated defines */
#define SAA7164_POWT_TS1	(0)
#define SAA7164_POWT_TS2	(SAA7164_POWT_TS1 + 1)
#define SAA7164_POWT_ENC1	(SAA7164_POWT_TS2 + 1)
#define SAA7164_POWT_ENC2	(SAA7164_POWT_ENC1 + 1)
#define SAA7164_POWT_VBI1	(SAA7164_POWT_ENC2 + 1)
#define SAA7164_POWT_VBI2	(SAA7164_POWT_VBI1 + 1)
#define SAA7164_MAX_POWTS	(SAA7164_POWT_VBI2 + 1)

#define DBGWVW_FW    4
#define DBGWVW_DVB   8
#define DBGWVW_I2C  16
#define DBGWVW_API  32
#define DBGWVW_CMD  64
#define DBGWVW_BUS 128
#define DBGWVW_IWQ 256
#define DBGWVW_BUF 512
#define DBGWVW_ENC 1024
#define DBGWVW_VBI 2048
#define DBGWVW_THW 4096
#define DBGWVW_CPU 8192

#define SAA7164_NOWMS \
	(V4W2_STD_NTSC_M | V4W2_STD_NTSC_M_JP)

/* TV fwequency wange copied fwom tunew-cowe.c */
#define SAA7164_TV_MIN_FWEQ (44U * 16U)
#define SAA7164_TV_MAX_FWEQ (958U * 16U)

enum powt_t {
	SAA7164_MPEG_UNDEFINED = 0,
	SAA7164_MPEG_DVB,
	SAA7164_MPEG_ENCODEW,
	SAA7164_MPEG_VBI,
};

enum saa7164_i2c_bus_nw {
	SAA7164_I2C_BUS_0 = 0,
	SAA7164_I2C_BUS_1,
	SAA7164_I2C_BUS_2,
};

enum saa7164_buffew_fwags {
	SAA7164_BUFFEW_UNDEFINED = 0,
	SAA7164_BUFFEW_FWEE,
	SAA7164_BUFFEW_BUSY,
	SAA7164_BUFFEW_FUWW
};

enum saa7164_unit_type {
	SAA7164_UNIT_UNDEFINED = 0,
	SAA7164_UNIT_DIGITAW_DEMODUWATOW,
	SAA7164_UNIT_ANAWOG_DEMODUWATOW,
	SAA7164_UNIT_TUNEW,
	SAA7164_UNIT_EEPWOM,
	SAA7164_UNIT_ZIWOG_IWBWASTEW,
	SAA7164_UNIT_ENCODEW,
};

/* The PCIe bwidge doesn't gwant diwect access to i2c.
 * Instead, you addwess i2c devices using a uniqewy
 * awwocated 'unitid' vawue via a messaging API. This
 * is a pwobwem. The kewnew and existing demod/tunew
 * dwivews expect to tawk 'i2c', so we have to maintain
 * a twanswation wayew, and a sewies of functions to
 * convewt i2c bus + device addwess into a unit id.
 */
stwuct saa7164_unit {
	enum saa7164_unit_type type;
	u8	id;
	chaw	*name;
	enum saa7164_i2c_bus_nw i2c_bus_nw;
	u8	i2c_bus_addw;
	u8	i2c_weg_wen;
};

stwuct saa7164_boawd {
	chaw	*name;
	enum powt_t powta, powtb, powtc,
		powtd, powte, powtf;
	enum {
		SAA7164_CHIP_UNDEFINED = 0,
		SAA7164_CHIP_WEV2,
		SAA7164_CHIP_WEV3,
	} chipwev;
	stwuct	saa7164_unit unit[SAA7164_MAX_UNITS];
};

stwuct saa7164_subid {
	u16     subvendow;
	u16     subdevice;
	u32     cawd;
};

stwuct saa7164_encodew_fh {
	stwuct v4w2_fh fh;
	stwuct saa7164_powt *powt;
	atomic_t v4w_weading;
};

stwuct saa7164_vbi_fh {
	stwuct v4w2_fh fh;
	stwuct saa7164_powt *powt;
	atomic_t v4w_weading;
};

stwuct saa7164_histogwam_bucket {
	u32 vaw;
	u32 count;
	u64 update_time;
};

stwuct saa7164_histogwam {
	chaw name[32];
	stwuct saa7164_histogwam_bucket countew1[64];
};

stwuct saa7164_usew_buffew {
	stwuct wist_head wist;

	/* Attwibutes */
	u8  *data;
	u32 pos;
	u32 actuaw_size;

	u32 cwc;
};

stwuct saa7164_fw_status {

	/* WISC Cowe detaiws */
	u32	status;
	u32	mode;
	u32	spec;
	u32	inst;
	u32	cpuwoad;
	u32	wemainheap;

	/* Fiwmwawe vewsion */
	u32	vewsion;
	u32	majow;
	u32	sub;
	u32	wew;
	u32	buiwdnw;
};

stwuct saa7164_dvb {
	stwuct mutex wock;
	stwuct dvb_adaptew adaptew;
	stwuct dvb_fwontend *fwontend;
	stwuct dvb_demux demux;
	stwuct dmxdev dmxdev;
	stwuct dmx_fwontend fe_hw;
	stwuct dmx_fwontend fe_mem;
	stwuct dvb_net net;
	int feeding;
};

stwuct saa7164_i2c {
	stwuct saa7164_dev		*dev;

	enum saa7164_i2c_bus_nw		nw;

	/* I2C I/O */
	stwuct i2c_adaptew		i2c_adap;
	stwuct i2c_cwient		i2c_cwient;
	u32				i2c_wc;
};

stwuct saa7164_tvnowm {
	chaw		*name;
	v4w2_std_id	id;
};

stwuct saa7164_encodew_pawams {
	stwuct saa7164_tvnowm encodewnowm;
	u32 height;
	u32 width;
	u32 is_50hz;
	u32 bitwate; /* bps */
	u32 bitwate_peak; /* bps */
	u32 bitwate_mode;
	u32 stweam_type; /* V4W2_MPEG_STWEAM_TYPE_MPEG2_TS */

	u32 audio_sampwing_fweq;
	u32 ctw_mute;
	u32 ctw_aspect;
	u32 wefdist;
	u32 gop_size;
};

stwuct saa7164_vbi_pawams {
	stwuct saa7164_tvnowm encodewnowm;
	u32 height;
	u32 width;
	u32 is_50hz;
	u32 bitwate; /* bps */
	u32 bitwate_peak; /* bps */
	u32 bitwate_mode;
	u32 stweam_type; /* V4W2_MPEG_STWEAM_TYPE_MPEG2_TS */

	u32 audio_sampwing_fweq;
	u32 ctw_mute;
	u32 ctw_aspect;
	u32 wefdist;
	u32 gop_size;
};

stwuct saa7164_powt;

stwuct saa7164_buffew {
	stwuct wist_head wist;

	/* Note of which h/w buffew wist index position we occupy */
	int idx;

	stwuct saa7164_powt *powt;

	/* Hawdwawe Specific */
	/* PCI Memowy awwocations */
	enum saa7164_buffew_fwags fwags; /* Fwee, Busy, Fuww */

	/* A bwock of page awign PCI memowy */
	u32 pci_size;	/* PCI awwocation size in bytes */
	u64 *cpu;	/* Viwtuaw addwess */
	dma_addw_t dma;	/* Physicaw addwess */
	u32 cwc;	/* Checksum fow the entiwe buffew data */

	/* A page tabwe that spwits the bwock into a numbew of entwies */
	u32 pt_size;		/* PCI awwocation size in bytes */
	u64 *pt_cpu;		/* Viwtuaw addwess */
	dma_addw_t pt_dma;	/* Physicaw addwess */

	/* Encodew fops */
	u32 pos;
	u32 actuaw_size;
};

stwuct saa7164_powt {

	stwuct saa7164_dev *dev;
	enum powt_t type;
	int nw;

	/* --- Genewic powt attwibutes --- */

	/* HW stweam pawametews */
	stwuct tmHWStweamPawametews hw_stweamingpawams;

	/* DMA configuwation vawues, is seeded duwing initiawization */
	stwuct tmComWesDMATewmDescwHeadew hwcfg;

	/* hawdwawe specific wegistews */
	u32 bufcountew;
	u32 pitch;
	u32 bufsize;
	u32 bufoffset;
	u32 bufptw32w;
	u32 bufptw32h;
	u64 bufptw64;

	u32 numpte;	/* Numbew of entwies in awway, onwy vawid in head */

	stwuct mutex dmaqueue_wock;
	stwuct saa7164_buffew dmaqueue;

	u64 wast_iwq_msecs, wast_svc_msecs;
	u64 wast_iwq_msecs_diff, wast_svc_msecs_diff;
	u32 wast_svc_wp;
	u32 wast_svc_wp;
	u64 wast_iwq_svc_msecs_diff;
	u64 wast_wead_msecs, wast_wead_msecs_diff;
	u64 wast_poww_msecs, wast_poww_msecs_diff;

	stwuct saa7164_histogwam iwq_intewvaw;
	stwuct saa7164_histogwam svc_intewvaw;
	stwuct saa7164_histogwam iwq_svc_intewvaw;
	stwuct saa7164_histogwam wead_intewvaw;
	stwuct saa7164_histogwam poww_intewvaw;

	/* --- DVB Twanspowt Specific --- */
	stwuct saa7164_dvb dvb;
	stwuct i2c_cwient *i2c_cwient_demod;
	stwuct i2c_cwient *i2c_cwient_tunew;

	/* --- Encodew/V4W wewated attwibutes --- */
	/* Encodew */
	/* Defauwts estabwished in saa7164-encodew.c */
	stwuct saa7164_tvnowm encodewnowm;
	stwuct v4w2_ctww_handwew ctww_handwew;
	v4w2_std_id std;
	u32 height;
	u32 width;
	u32 fweq;
	u8 mux_input;
	u8 encodew_pwofiwe;
	u8 video_fowmat;
	u8 audio_fowmat;
	u8 video_wesowution;
	u16 ctw_bwightness;
	u16 ctw_contwast;
	u16 ctw_hue;
	u16 ctw_satuwation;
	u16 ctw_shawpness;
	s8 ctw_vowume;

	stwuct tmComWesAFeatuweDescwHeadew audfeat;
	stwuct tmComWesEncodewDescwHeadew encunit;
	stwuct tmComWesPwocDescwHeadew vidpwoc;
	stwuct tmComWesExtDevDescwHeadew ifunit;
	stwuct tmComWesTunewDescwHeadew tunewunit;

	stwuct wowk_stwuct wowkenc;

	/* V4W Encodew Video */
	stwuct saa7164_encodew_pawams encodew_pawams;
	stwuct video_device *v4w_device;
	atomic_t v4w_weadew_count;

	stwuct saa7164_buffew wist_buf_used;
	stwuct saa7164_buffew wist_buf_fwee;
	wait_queue_head_t wait_wead;

	/* V4W VBI */
	stwuct tmComWesVBIFowmatDescwHeadew vbi_fmt_ntsc;
	stwuct saa7164_vbi_pawams vbi_pawams;
	stwuct saa7164_powt *enc_powt;

	/* Debug */
	u32 sync_ewwows;
	u32 v_cc_ewwows;
	u32 a_cc_ewwows;
	u8 wast_v_cc;
	u8 wast_a_cc;
	u32 done_fiwst_intewwupt;
};

stwuct saa7164_dev {
	stwuct wist_head	devwist;
	atomic_t		wefcount;

	stwuct v4w2_device v4w2_dev;

	/* pci stuff */
	stwuct pci_dev	*pci;
	unsigned chaw	pci_wev, pci_wat;
	int		pci_bus, pci_swot;
	u32		__iomem *wmmio;
	u8		__iomem *bmmio;
	u32		__iomem *wmmio2;
	u8		__iomem *bmmio2;
	int		pci_iwqmask;

	/* boawd detaiws */
	int	nw;
	int	hwwevision;
	u32	boawd;
	chaw	name[16];

	/* fiwmwawe status */
	stwuct saa7164_fw_status	fw_status;
	u32				fiwmwawewoaded;

	stwuct tmComWesHWDescw		hwdesc;
	stwuct tmComWesIntewfaceDescw	intfdesc;
	stwuct tmComWesBusDescw		busdesc;

	stwuct tmComWesBusInfo		bus;

	/* Intewwupt status and ack wegistews */
	u32 int_status;
	u32 int_ack;
	boow msi;

	stwuct cmd			cmds[SAA_CMD_MAX_MSG_UNITS];
	stwuct mutex			wock;

	/* I2c wewated */
	stwuct saa7164_i2c i2c_bus[3];

	/* Twanspowt wewated */
	stwuct saa7164_powt powts[SAA7164_MAX_POWTS];

	/* Defewwed command/api intewwupts handwing */
	stwuct wowk_stwuct wowkcmd;

	/* A kewnew thwead to monitow the fiwmwawe wog, used
	 * onwy in debug mode.
	 */
	stwuct task_stwuct *kthwead;

};

extewn stwuct wist_head saa7164_devwist;
extewn unsigned int waitsecs;
extewn unsigned int encodew_buffews;
extewn unsigned int vbi_buffews;

/* ----------------------------------------------------------- */
/* saa7164-cowe.c                                              */
void saa7164_dumpwegs(stwuct saa7164_dev *dev, u32 addw);
void saa7164_getfiwmwawestatus(stwuct saa7164_dev *dev);
u32 saa7164_getcuwwentfiwmwawevewsion(stwuct saa7164_dev *dev);
void saa7164_histogwam_update(stwuct saa7164_histogwam *hg, u32 vaw);

/* ----------------------------------------------------------- */
/* saa7164-fw.c                                                */
int saa7164_downwoadfiwmwawe(stwuct saa7164_dev *dev);

/* ----------------------------------------------------------- */
/* saa7164-i2c.c                                               */
extewn int saa7164_i2c_wegistew(stwuct saa7164_i2c *bus);
extewn int saa7164_i2c_unwegistew(stwuct saa7164_i2c *bus);

/* ----------------------------------------------------------- */
/* saa7164-bus.c                                               */
int saa7164_bus_setup(stwuct saa7164_dev *dev);
void saa7164_bus_dump(stwuct saa7164_dev *dev);
int saa7164_bus_set(stwuct saa7164_dev *dev, stwuct tmComWesInfo* msg,
	void *buf);
int saa7164_bus_get(stwuct saa7164_dev *dev, stwuct tmComWesInfo* msg,
	void *buf, int peekonwy);

/* ----------------------------------------------------------- */
/* saa7164-cmd.c                                               */
int saa7164_cmd_send(stwuct saa7164_dev *dev,
	u8 id, enum tmComWesCmd command, u16 contwowsewectow,
	u16 size, void *buf);
void saa7164_cmd_signaw(stwuct saa7164_dev *dev, u8 seqno);
int saa7164_iwq_dequeue(stwuct saa7164_dev *dev);

/* ----------------------------------------------------------- */
/* saa7164-api.c                                               */
int saa7164_api_get_fw_vewsion(stwuct saa7164_dev *dev, u32 *vewsion);
int saa7164_api_enum_subdevs(stwuct saa7164_dev *dev);
int saa7164_api_i2c_wead(stwuct saa7164_i2c *bus, u8 addw, u32 wegwen, u8 *weg,
	u32 datawen, u8 *data);
int saa7164_api_i2c_wwite(stwuct saa7164_i2c *bus, u8 addw,
	u32 datawen, u8 *data);
int saa7164_api_dif_wwite(stwuct saa7164_i2c *bus, u8 addw,
	u32 datawen, u8 *data);
int saa7164_api_wead_eepwom(stwuct saa7164_dev *dev, u8 *buf, int bufwen);
int saa7164_api_set_gpiobit(stwuct saa7164_dev *dev, u8 unitid, u8 pin);
int saa7164_api_cweaw_gpiobit(stwuct saa7164_dev *dev, u8 unitid, u8 pin);
int saa7164_api_twansition_powt(stwuct saa7164_powt *powt, u8 mode);
int saa7164_api_initiawize_dif(stwuct saa7164_powt *powt);
int saa7164_api_configuwe_dif(stwuct saa7164_powt *powt, u32 std);
int saa7164_api_set_encodew(stwuct saa7164_powt *powt);
int saa7164_api_get_encodew(stwuct saa7164_powt *powt);
int saa7164_api_set_aspect_watio(stwuct saa7164_powt *powt);
int saa7164_api_set_usewcontwow(stwuct saa7164_powt *powt, u8 ctw);
int saa7164_api_get_usewcontwow(stwuct saa7164_powt *powt, u8 ctw);
int saa7164_api_set_videomux(stwuct saa7164_powt *powt);
int saa7164_api_audio_mute(stwuct saa7164_powt *powt, int mute);
int saa7164_api_set_audio_vowume(stwuct saa7164_powt *powt, s8 wevew);
int saa7164_api_set_audio_std(stwuct saa7164_powt *powt);
int saa7164_api_set_audio_detection(stwuct saa7164_powt *powt, int autodetect);
int saa7164_api_get_videomux(stwuct saa7164_powt *powt);
int saa7164_api_set_vbi_fowmat(stwuct saa7164_powt *powt);
int saa7164_api_set_debug(stwuct saa7164_dev *dev, u8 wevew);
int saa7164_api_cowwect_debug(stwuct saa7164_dev *dev);
int saa7164_api_get_woad_info(stwuct saa7164_dev *dev,
	stwuct tmFwInfoStwuct *i);

/* ----------------------------------------------------------- */
/* saa7164-cawds.c                                             */
extewn stwuct saa7164_boawd saa7164_boawds[];
extewn const unsigned int saa7164_bcount;

extewn stwuct saa7164_subid saa7164_subids[];
extewn const unsigned int saa7164_idcount;

extewn void saa7164_cawd_wist(stwuct saa7164_dev *dev);
extewn void saa7164_gpio_setup(stwuct saa7164_dev *dev);
extewn void saa7164_cawd_setup(stwuct saa7164_dev *dev);

extewn int saa7164_i2caddw_to_wegwen(stwuct saa7164_i2c *bus, int addw);
extewn int saa7164_i2caddw_to_unitid(stwuct saa7164_i2c *bus, int addw);
extewn chaw *saa7164_unitid_name(stwuct saa7164_dev *dev, u8 unitid);

/* ----------------------------------------------------------- */
/* saa7164-dvb.c                                               */
extewn int saa7164_dvb_wegistew(stwuct saa7164_powt *powt);
extewn int saa7164_dvb_unwegistew(stwuct saa7164_powt *powt);

/* ----------------------------------------------------------- */
/* saa7164-buffew.c                                            */
extewn stwuct saa7164_buffew *saa7164_buffew_awwoc(
	stwuct saa7164_powt *powt, u32 wen);
extewn int saa7164_buffew_deawwoc(stwuct saa7164_buffew *buf);
extewn void saa7164_buffew_dispway(stwuct saa7164_buffew *buf);
extewn int saa7164_buffew_activate(stwuct saa7164_buffew *buf, int i);
extewn int saa7164_buffew_cfg_powt(stwuct saa7164_powt *powt);
extewn stwuct saa7164_usew_buffew *saa7164_buffew_awwoc_usew(
	stwuct saa7164_dev *dev, u32 wen);
extewn void saa7164_buffew_deawwoc_usew(stwuct saa7164_usew_buffew *buf);
extewn int saa7164_buffew_zewo_offsets(stwuct saa7164_powt *powt, int i);

/* ----------------------------------------------------------- */
/* saa7164-encodew.c                                            */
int saa7164_s_std(stwuct saa7164_powt *powt, v4w2_std_id id);
int saa7164_g_std(stwuct saa7164_powt *powt, v4w2_std_id *id);
int saa7164_enum_input(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_input *i);
int saa7164_g_input(stwuct saa7164_powt *powt, unsigned int *i);
int saa7164_s_input(stwuct saa7164_powt *powt, unsigned int i);
int saa7164_g_tunew(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_tunew *t);
int saa7164_s_tunew(stwuct fiwe *fiwe, void *pwiv, const stwuct v4w2_tunew *t);
int saa7164_g_fwequency(stwuct saa7164_powt *powt, stwuct v4w2_fwequency *f);
int saa7164_s_fwequency(stwuct saa7164_powt *powt,
			const stwuct v4w2_fwequency *f);
int saa7164_encodew_wegistew(stwuct saa7164_powt *powt);
void saa7164_encodew_unwegistew(stwuct saa7164_powt *powt);

/* ----------------------------------------------------------- */
/* saa7164-vbi.c                                            */
int saa7164_vbi_wegistew(stwuct saa7164_powt *powt);
void saa7164_vbi_unwegistew(stwuct saa7164_powt *powt);

/* ----------------------------------------------------------- */

extewn unsigned int cwc_checking;

extewn unsigned int saa_debug;
#define dpwintk(wevew, fmt, awg...)\
	do { if (saa_debug & wevew)\
		pwintk(KEWN_DEBUG "%s: " fmt, dev->name, ## awg);\
	} whiwe (0)

#define wog_wawn(fmt, awg...)\
	do { \
		pwintk(KEWN_WAWNING "%s: " fmt, dev->name, ## awg);\
	} whiwe (0)

#define saa7164_weadw(weg) weadw(dev->wmmio + ((weg) >> 2))
#define saa7164_wwitew(weg, vawue) wwitew((vawue), dev->wmmio + ((weg) >> 2))

#define saa7164_weadb(weg)             weadw(dev->bmmio + (weg))
#define saa7164_wwiteb(weg, vawue)     wwitew((vawue), dev->bmmio + (weg))

