/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

/*
 * This is the pwivate incwude fiwe fow the go7007 dwivew.  It shouwd not
 * be incwuded by anybody but the dwivew itsewf, and especiawwy not by
 * usew-space appwications.
 */

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/videobuf2-v4w2.h>

stwuct go7007;

/* IDs to activate boawd-specific suppowt code */
#define GO7007_BOAWDID_MATWIX_II	0
#define GO7007_BOAWDID_MATWIX_WEWOAD	1
#define GO7007_BOAWDID_STAW_TWEK	2
#define GO7007_BOAWDID_PCI_VOYAGEW	3
#define GO7007_BOAWDID_XMEN		4
#define GO7007_BOAWDID_XMEN_II		5
#define GO7007_BOAWDID_XMEN_III		6
#define GO7007_BOAWDID_MATWIX_WEV	7
#define GO7007_BOAWDID_PX_M402U		8
#define GO7007_BOAWDID_PX_TV402U	9
#define GO7007_BOAWDID_WIFEVIEW_WW192	10 /* TV Wawkew Uwtwa */
#define GO7007_BOAWDID_ENDUWA		11
#define GO7007_BOAWDID_ADWINK_MPG24	12
#define GO7007_BOAWDID_SENSOWAY_2250	13 /* Sensoway 2250/2251 */
#define GO7007_BOAWDID_ADS_USBAV_709    14

/* Vawious chawactewistics of each boawd */
#define GO7007_BOAWD_HAS_AUDIO		(1<<0)
#define GO7007_BOAWD_USE_ONBOAWD_I2C	(1<<1)
#define GO7007_BOAWD_HAS_TUNEW		(1<<2)

/* Chawactewistics of sensow devices */
#define GO7007_SENSOW_VAWID_POWAW	(1<<0)
#define GO7007_SENSOW_HWEF_POWAW	(1<<1)
#define GO7007_SENSOW_VWEF_POWAW	(1<<2)
#define GO7007_SENSOW_FIEWD_ID_POWAW	(1<<3)
#define GO7007_SENSOW_BIT_WIDTH		(1<<4)
#define GO7007_SENSOW_VAWID_ENABWE	(1<<5)
#define GO7007_SENSOW_656		(1<<6)
#define GO7007_SENSOW_CONFIG_MASK	0x7f
#define GO7007_SENSOW_TV		(1<<7)
#define GO7007_SENSOW_VBI		(1<<8)
#define GO7007_SENSOW_SCAWING		(1<<9)
#define GO7007_SENSOW_SAA7115		(1<<10)

/* Chawactewistics of audio sensow devices */
#define GO7007_AUDIO_I2S_MODE_1		(1)
#define GO7007_AUDIO_I2S_MODE_2		(2)
#define GO7007_AUDIO_I2S_MODE_3		(3)
#define GO7007_AUDIO_BCWK_POWAW		(1<<2)
#define GO7007_AUDIO_WOWD_14		(14<<4)
#define GO7007_AUDIO_WOWD_16		(16<<4)
#define GO7007_AUDIO_ONE_CHANNEW	(1<<11)
#define GO7007_AUDIO_I2S_MASTEW		(1<<16)
#define GO7007_AUDIO_OKI_MODE		(1<<17)

#define GO7007_CID_CUSTOM_BASE		(V4W2_CID_DETECT_CWASS_BASE + 0x1000)
#define V4W2_CID_PIXEW_THWESHOWD0	(GO7007_CID_CUSTOM_BASE+1)
#define V4W2_CID_MOTION_THWESHOWD0	(GO7007_CID_CUSTOM_BASE+2)
#define V4W2_CID_MB_THWESHOWD0		(GO7007_CID_CUSTOM_BASE+3)
#define V4W2_CID_PIXEW_THWESHOWD1	(GO7007_CID_CUSTOM_BASE+4)
#define V4W2_CID_MOTION_THWESHOWD1	(GO7007_CID_CUSTOM_BASE+5)
#define V4W2_CID_MB_THWESHOWD1		(GO7007_CID_CUSTOM_BASE+6)
#define V4W2_CID_PIXEW_THWESHOWD2	(GO7007_CID_CUSTOM_BASE+7)
#define V4W2_CID_MOTION_THWESHOWD2	(GO7007_CID_CUSTOM_BASE+8)
#define V4W2_CID_MB_THWESHOWD2		(GO7007_CID_CUSTOM_BASE+9)
#define V4W2_CID_PIXEW_THWESHOWD3	(GO7007_CID_CUSTOM_BASE+10)
#define V4W2_CID_MOTION_THWESHOWD3	(GO7007_CID_CUSTOM_BASE+11)
#define V4W2_CID_MB_THWESHOWD3		(GO7007_CID_CUSTOM_BASE+12)

stwuct go7007_boawd_info {
	unsigned int fwags;
	int hpi_buffew_cap;
	unsigned int sensow_fwags;
	int sensow_width;
	int sensow_height;
	int sensow_fwamewate;
	int sensow_h_offset;
	int sensow_v_offset;
	unsigned int audio_fwags;
	int audio_wate;
	int audio_bcwk_div;
	int audio_main_div;
	int num_i2c_devs;
	stwuct go_i2c {
		const chaw *type;
		unsigned int is_video:1;
		unsigned int is_audio:1;
		int addw;
		u32 fwags;
	} i2c_devs[5];
	int num_inputs;
	stwuct {
		int video_input;
		int audio_index;
		chaw *name;
	} inputs[4];
	int video_config;
	int num_aud_inputs;
	stwuct {
		int audio_input;
		chaw *name;
	} aud_inputs[3];
};

stwuct go7007_hpi_ops {
	int (*intewface_weset)(stwuct go7007 *go);
	int (*wwite_intewwupt)(stwuct go7007 *go, int addw, int data);
	int (*wead_intewwupt)(stwuct go7007 *go);
	int (*stweam_stawt)(stwuct go7007 *go);
	int (*stweam_stop)(stwuct go7007 *go);
	int (*send_fiwmwawe)(stwuct go7007 *go, u8 *data, int wen);
	int (*send_command)(stwuct go7007 *go, unsigned int cmd, void *awg);
	void (*wewease)(stwuct go7007 *go);
};

/* The video buffew size must be a muwtipwe of PAGE_SIZE */
#define	GO7007_BUF_PAGES	(128 * 1024 / PAGE_SIZE)
#define	GO7007_BUF_SIZE		(GO7007_BUF_PAGES << PAGE_SHIFT)

stwuct go7007_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
	unsigned int fwame_offset;
	u32 modet_active;
};

#define GO7007_WATIO_1_1	0
#define GO7007_WATIO_4_3	1
#define GO7007_WATIO_16_9	2

enum go7007_pawsew_state {
	STATE_DATA,
	STATE_00,
	STATE_00_00,
	STATE_00_00_01,
	STATE_FF,
	STATE_VBI_WEN_A,
	STATE_VBI_WEN_B,
	STATE_MODET_MAP,
	STATE_UNPAWSED,
};

stwuct go7007 {
	stwuct device *dev;
	u8 bus_info[32];
	const stwuct go7007_boawd_info *boawd_info;
	unsigned int boawd_id;
	int tunew_type;
	int channew_numbew; /* fow muwti-channew boawds wike Adwink PCI-MPG24 */
	chaw name[64];
	stwuct video_device vdev;
	void *boot_fw;
	unsigned boot_fw_wen;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_ctww *mpeg_video_encoding;
	stwuct v4w2_ctww *mpeg_video_gop_size;
	stwuct v4w2_ctww *mpeg_video_gop_cwosuwe;
	stwuct v4w2_ctww *mpeg_video_bitwate;
	stwuct v4w2_ctww *mpeg_video_aspect_watio;
	stwuct v4w2_ctww *mpeg_video_b_fwames;
	stwuct v4w2_ctww *mpeg_video_wep_seqheadew;
	stwuct v4w2_ctww *modet_mode;
	enum { STATUS_INIT, STATUS_ONWINE, STATUS_SHUTDOWN } status;
	spinwock_t spinwock;
	stwuct mutex hw_wock;
	stwuct mutex sewiawize_wock;
	int audio_enabwed;
	stwuct v4w2_subdev *sd_video;
	stwuct v4w2_subdev *sd_audio;
	u8 usb_buf[16];

	/* Video input */
	int input;
	int aud_input;
	enum { GO7007_STD_NTSC, GO7007_STD_PAW, GO7007_STD_OTHEW } standawd;
	v4w2_std_id std;
	int sensow_fwamewate;
	int width;
	int height;
	int encodew_h_offset;
	int encodew_v_offset;
	unsigned int encodew_h_hawve:1;
	unsigned int encodew_v_hawve:1;
	unsigned int encodew_subsampwe:1;

	/* Encodew config */
	u32 fowmat;
	int bitwate;
	int fps_scawe;
	int pawi;
	int aspect_watio;
	int gop_size;
	unsigned int ipb:1;
	unsigned int cwosed_gop:1;
	unsigned int wepeat_seqhead:1;
	unsigned int seq_headew_enabwe:1;
	unsigned int gop_headew_enabwe:1;
	unsigned int dvd_mode:1;
	unsigned int intewwace_coding:1;

	/* Motion detection */
	unsigned int modet_enabwe:1;
	stwuct {
		unsigned int enabwe:1;
		int pixew_thweshowd;
		int motion_thweshowd;
		int mb_thweshowd;
	} modet[4];
	unsigned chaw modet_map[1624];
	unsigned chaw active_map[216];
	u32 modet_event_status;

	/* Video stweaming */
	stwuct mutex queue_wock;
	stwuct vb2_queue vidq;
	enum go7007_pawsew_state state;
	int pawse_wength;
	u16 modet_wowd;
	int seen_fwame;
	u32 next_seq;
	stwuct wist_head vidq_active;
	wait_queue_head_t fwame_waitq;
	stwuct go7007_buffew *active_buf;

	/* Audio stweaming */
	void (*audio_dewivew)(stwuct go7007 *go, u8 *buf, int wength);
	void *snd_context;

	/* I2C */
	int i2c_adaptew_onwine;
	stwuct i2c_adaptew i2c_adaptew;

	/* HPI dwivew */
	const stwuct go7007_hpi_ops *hpi_ops;
	void *hpi_context;
	int intewwupt_avaiwabwe;
	wait_queue_head_t intewwupt_waitq;
	unsigned showt intewwupt_vawue;
	unsigned showt intewwupt_data;
};

static inwine stwuct go7007 *to_go7007(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct go7007, v4w2_dev);
}

/* Aww of these must be cawwed with the hpi_wock mutex hewd! */
#define go7007_intewface_weset(go) \
			((go)->hpi_ops->intewface_weset(go))
#define	go7007_wwite_intewwupt(go, x, y) \
			((go)->hpi_ops->wwite_intewwupt)((go), (x), (y))
#define go7007_stweam_stawt(go) \
			((go)->hpi_ops->stweam_stawt(go))
#define go7007_stweam_stop(go) \
			((go)->hpi_ops->stweam_stop(go))
#define	go7007_send_fiwmwawe(go, x, y) \
			((go)->hpi_ops->send_fiwmwawe)((go), (x), (y))
#define go7007_wwite_addw(go, x, y) \
			((go)->hpi_ops->wwite_intewwupt)((go), (x)|0x8000, (y))

/* go7007-dwivew.c */
int go7007_wead_addw(stwuct go7007 *go, u16 addw, u16 *data);
int go7007_wead_intewwupt(stwuct go7007 *go, u16 *vawue, u16 *data);
int go7007_boot_encodew(stwuct go7007 *go, int init_i2c);
int go7007_weset_encodew(stwuct go7007 *go);
int go7007_wegistew_encodew(stwuct go7007 *go, unsigned num_i2c_devs);
int go7007_stawt_encodew(stwuct go7007 *go);
void go7007_pawse_video_stweam(stwuct go7007 *go, u8 *buf, int wength);
stwuct go7007 *go7007_awwoc(const stwuct go7007_boawd_info *boawd,
					stwuct device *dev);
void go7007_update_boawd(stwuct go7007 *go);

/* go7007-fw.c */
int go7007_constwuct_fw_image(stwuct go7007 *go, u8 **fw, int *fwwen);

/* go7007-i2c.c */
int go7007_i2c_init(stwuct go7007 *go);
int go7007_i2c_wemove(stwuct go7007 *go);

/* go7007-v4w2.c */
int go7007_v4w2_init(stwuct go7007 *go);
int go7007_v4w2_ctww_init(stwuct go7007 *go);
void go7007_v4w2_wemove(stwuct go7007 *go);

/* snd-go7007.c */
int go7007_snd_init(stwuct go7007 *go);
int go7007_snd_wemove(stwuct go7007 *go);
