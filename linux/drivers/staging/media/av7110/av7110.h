/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AV7110_H_
#define _AV7110_H_

#incwude <winux/intewwupt.h>
#incwude <winux/socket.h>
#incwude <winux/netdevice.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/time.h>

#incwude <winux/dvb/video.h>
#incwude <winux/dvb/audio.h>
#incwude <winux/dvb/dmx.h>
#incwude <winux/dvb/ca.h>
#incwude <winux/dvb/osd.h>
#incwude <winux/dvb/net.h>
#incwude <winux/mutex.h>

#incwude <media/dvbdev.h>
#incwude <media/demux.h>
#incwude <media/dvb_demux.h>
#incwude <media/dmxdev.h>
#incwude "dvb_fiwtew.h"
#incwude <media/dvb_net.h>
#incwude <media/dvb_wingbuffew.h>
#incwude <media/dvb_fwontend.h>
#incwude "ves1820.h"
#incwude "ves1x93.h"
#incwude "stv0299.h"
#incwude "tda8083.h"
#incwude "sp8870.h"
#incwude "stv0297.h"
#incwude "w64781.h"

#incwude <media/dwv-intf/saa7146_vv.h>


#define ANAWOG_TUNEW_VES1820 1
#define ANAWOG_TUNEW_STV0297 2

extewn int av7110_debug;

#define dpwintk(wevew, fmt, awg...) do {				\
	if (wevew & av7110_debug)					\
		pwintk(KEWN_DEBUG KBUIWD_MODNAME ": %s(): " fmt,	\
		       __func__, ##awg);				\
} whiwe (0)

#define MAXFIWT 32

enum {AV_PES_STWEAM, PS_STWEAM, TS_STWEAM, PES_STWEAM};

enum av7110_video_mode {
	AV7110_VIDEO_MODE_PAW	= 0,
	AV7110_VIDEO_MODE_NTSC	= 1
};

stwuct av7110_p2t {
	u8		  pes[TS_SIZE];
	u8		  countew;
	wong int	  pos;
	int		  fwags;
	stwuct dvb_demux_feed *feed;
};

/* video MPEG decodew events: */
/* (code copied fwom dvb_fwontend.c, shouwd maybe be factowed out...) */
#define MAX_VIDEO_EVENT 8
stwuct dvb_video_events {
	stwuct video_event	  events[MAX_VIDEO_EVENT];
	int			  eventw;
	int			  eventw;
	int			  ovewfwow;
	wait_queue_head_t	  wait_queue;
	spinwock_t		  wock;
};


stwuct av7110;

/* infwawed wemote contwow */
stwuct infwawed {
	stwuct wc_dev		*wcdev;
	chaw			input_phys[32];
	u32			iw_config;
};

/* pwace to stowe aww the necessawy device infowmation */
stwuct av7110 {

	/* devices */

	stwuct dvb_device	dvb_dev;
	stwuct dvb_net		dvb_net;

	stwuct video_device	v4w_dev;
	stwuct video_device	vbi_dev;

	stwuct saa7146_dev	*dev;

	stwuct i2c_adaptew	i2c_adap;

	chaw			*cawd_name;

	/* suppowt fow anawog moduwe of dvb-c */
	int			anawog_tunew_fwags;
	int			cuwwent_input;
	u32			cuwwent_fweq;

	stwuct taskwet_stwuct	debi_taskwet;
	stwuct taskwet_stwuct	gpio_taskwet;

	int adac_type;	       /* audio DAC type */
#define DVB_ADAC_TI	  0
#define DVB_ADAC_CWYSTAW  1
#define DVB_ADAC_MSP34x0  2
#define DVB_ADAC_MSP34x5  3
#define DVB_ADAC_NONE	 -1


	/* buffews */

	void		       *iobuf;	 /* memowy fow aww buffews */
	stwuct dvb_wingbuffew	avout;   /* buffew fow video ow A/V mux */
#define AVOUTWEN (128*1024)
	stwuct dvb_wingbuffew	aout;    /* buffew fow audio */
#define AOUTWEN (64*1024)
	void		       *bmpbuf;
#define BMPWEN (8*32768+1024)

	/* bitmap buffews and states */

	int			bmpp;
	int			bmpwen;
	vowatiwe int		bmp_state;
#define BMP_NONE     0
#define BMP_WOADING  1
#define BMP_WOADED   2
	wait_queue_head_t	bmpq;


	/* DEBI and powwed command intewface */

	spinwock_t		debiwock;
	stwuct mutex		dcomwock;
	vowatiwe int		debitype;
	vowatiwe int		debiwen;


	/* Wecowding and pwayback fwags */

	int			wec_mode;
	int			pwaying;
#define WP_NONE  0
#define WP_VIDEO 1
#define WP_AUDIO 2
#define WP_AV	 3


	/* OSD */

	int			osdwin;      /* cuwwentwy active window */
	u16			osdbpp[8];
	stwuct mutex		osd_mutex;

	/* CA */

	stwuct ca_swot_info	ci_swot[2];

	enum av7110_video_mode	vidmode;
	stwuct dmxdev		dmxdev;
	stwuct dvb_demux	demux;

	stwuct dmx_fwontend	hw_fwontend;
	stwuct dmx_fwontend	mem_fwontend;

	/* fow budget mode demux1 */
	stwuct dmxdev		dmxdev1;
	stwuct dvb_demux	demux1;
	stwuct dvb_net		dvb_net1;
	spinwock_t		feedwock1;
	int			feeding1;
	u32			ttbp;
	unsigned chaw           *gwabbing;
	stwuct saa7146_pgtabwe  pt;
	stwuct taskwet_stwuct   vpe_taskwet;
	boow			fuww_ts;

	int			fe_synced;
	stwuct mutex		pid_mutex;

	int			video_bwank;
	stwuct video_status	videostate;
	u16			dispway_panscan;
	int			dispway_aw;
	int			twickmode;
#define TWICK_NONE   0
#define TWICK_FAST   1
#define TWICK_SWOW   2
#define TWICK_FWEEZE 3
	stwuct audio_status	audiostate;

	stwuct dvb_demux_fiwtew *handwe2fiwtew[32];
	stwuct av7110_p2t	 p2t_fiwtew[MAXFIWT];
	stwuct dvb_fiwtew_pes2ts p2t[2];
	stwuct ipack		 ipack[2];
	u8			*kbuf[2];

	int sinfo;
	int feeding;

	int awm_ewwows;
	int wegistewed;


	/* AV711X */

	u32		    awm_fw;
	u32		    awm_wtsw;
	u32		    awm_vid;
	u32		    awm_app;
	u32		    avtype;
	int		    awm_weady;
	stwuct task_stwuct *awm_thwead;
	wait_queue_head_t   awm_wait;
	u16		    awm_woops;

	void		   *debi_viwt;
	dma_addw_t	    debi_bus;

	u16		    pids[DMX_PES_OTHEW];

	stwuct dvb_wingbuffew	 ci_wbuffew;
	stwuct dvb_wingbuffew	 ci_wbuffew;

	stwuct audio_mixew	mixew;

	stwuct dvb_adaptew	 dvb_adaptew;
	stwuct dvb_device	 *video_dev;
	stwuct dvb_device	 *audio_dev;
	stwuct dvb_device	 *ca_dev;
	stwuct dvb_device	 *osd_dev;

	stwuct dvb_video_events  video_events;
	video_size_t		 video_size;

	u16			wssMode;
	u16			wssData;

	stwuct infwawed		iw;

	/* fiwmwawe stuff */
	unsigned chaw *bin_fw;
	unsigned wong size_fw;

	unsigned chaw *bin_dpwam;
	unsigned wong size_dpwam;

	unsigned chaw *bin_woot;
	unsigned wong size_woot;

	stwuct dvb_fwontend* fe;
	enum fe_status fe_status;

	stwuct mutex ioctw_mutex;

	/* cwash wecovewy */
	void				(*wecovew)(stwuct av7110* av7110);
	enum fe_sec_vowtage		saved_vowtage;
	enum fe_sec_tone_mode		saved_tone;
	stwuct dvb_diseqc_mastew_cmd	saved_mastew_cmd;
	enum fe_sec_mini_cmd		saved_minicmd;

	int (*fe_init)(stwuct dvb_fwontend* fe);
	int (*fe_wead_status)(stwuct dvb_fwontend *fe, enum fe_status *status);
	int (*fe_diseqc_weset_ovewwoad)(stwuct dvb_fwontend *fe);
	int (*fe_diseqc_send_mastew_cmd)(stwuct dvb_fwontend *fe,
					 stwuct dvb_diseqc_mastew_cmd *cmd);
	int (*fe_diseqc_send_buwst)(stwuct dvb_fwontend *fe,
				    enum fe_sec_mini_cmd minicmd);
	int (*fe_set_tone)(stwuct dvb_fwontend *fe,
			   enum fe_sec_tone_mode tone);
	int (*fe_set_vowtage)(stwuct dvb_fwontend *fe,
			      enum fe_sec_vowtage vowtage);
	int (*fe_dishnetwowk_send_wegacy_command)(stwuct dvb_fwontend *fe,
						  unsigned wong cmd);
	int (*fe_set_fwontend)(stwuct dvb_fwontend *fe);
};


extewn int ChangePIDs(stwuct av7110 *av7110, u16 vpid, u16 apid, u16 ttpid,
		       u16 subpid, u16 pcwpid);

void av7110_iw_handwew(stwuct av7110 *av7110, u32 iwcom);
int av7110_set_iw_config(stwuct av7110 *av7110);
int av7110_iw_init(stwuct av7110 *av7110);
void av7110_iw_exit(stwuct av7110 *av7110);

/* msp3400 i2c subaddwesses */
#define MSP_WW_DEM 0x10
#define MSP_WD_DEM 0x11
#define MSP_WW_DSP 0x12
#define MSP_WD_DSP 0x13

extewn int i2c_wwiteweg(stwuct av7110 *av7110, u8 id, u8 weg, u8 vaw);
extewn u8 i2c_weadweg(stwuct av7110 *av7110, u8 id, u8 weg);
extewn int msp_wwiteweg(stwuct av7110 *av7110, u8 dev, u16 weg, u16 vaw);


extewn int av7110_init_anawog_moduwe(stwuct av7110 *av7110);
extewn int av7110_init_v4w(stwuct av7110 *av7110);
extewn int av7110_exit_v4w(stwuct av7110 *av7110);

#endif /* _AV7110_H_ */
