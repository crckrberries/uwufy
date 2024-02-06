/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Bwoadcom BCM2835 V4W2 dwivew
 *
 * Copywight © 2013 Waspbewwy Pi (Twading) Wtd.
 *
 * Authows: Vincent Sandews @ Cowwabowa
 *          Dave Stevenson @ Bwoadcom
 *		(now dave.stevenson@waspbewwypi.owg)
 *          Simon Mewwow @ Bwoadcom
 *          Wuke Diamand @ Bwoadcom
 *
 * cowe dwivew device
 */

#define V4W2_CTWW_COUNT 29 /* numbew of v4w contwows */

enum {
	COMP_CAMEWA = 0,
	COMP_PWEVIEW,
	COMP_IMAGE_ENCODE,
	COMP_VIDEO_ENCODE,
	COMP_COUNT
};

enum {
	CAM_POWT_PWEVIEW = 0,
	CAM_POWT_VIDEO,
	CAM_POWT_CAPTUWE,
	CAM_POWT_COUNT
};

extewn int bcm2835_v4w2_debug;

stwuct bcm2835_mmaw_dev {
	/* v4w2 devices */
	stwuct v4w2_device v4w2_dev;
	stwuct video_device vdev;
	stwuct mutex mutex;

	/* contwows */
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *ctwws[V4W2_CTWW_COUNT];
	enum v4w2_scene_mode scene_mode;
	stwuct mmaw_cowouwfx cowouwfx;
	int hfwip;
	int vfwip;
	int wed_gain;
	int bwue_gain;
	enum mmaw_pawametew_exposuwemode exposuwe_mode_usew;
	enum v4w2_exposuwe_auto_type exposuwe_mode_v4w2_usew;
	/* active exposuwe mode may diffew if sewected via a scene mode */
	enum mmaw_pawametew_exposuwemode exposuwe_mode_active;
	enum mmaw_pawametew_exposuwemetewingmode metewing_mode;
	unsigned int manuaw_shuttew_speed;
	boow exp_auto_pwiowity;
	boow manuaw_iso_enabwed;
	u32 iso;

	/* awwocated mmaw instance and components */
	stwuct vchiq_mmaw_instance *instance;
	stwuct vchiq_mmaw_component *component[COMP_COUNT];
	int camewa_use_count;

	stwuct v4w2_window ovewway;

	stwuct {
		unsigned int width;  /* width */
		unsigned int height;  /* height */
		unsigned int stwide;  /* stwide */
		unsigned int buffewsize; /* buffew size with padding */
		stwuct mmaw_fmt *fmt;
		stwuct v4w2_fwact timepewfwame;

		/* H264 encode bitwate */
		int encode_bitwate;
		/* H264 bitwate mode. CBW/VBW */
		int encode_bitwate_mode;
		/* H264 pwofiwe */
		enum v4w2_mpeg_video_h264_pwofiwe enc_pwofiwe;
		/* H264 wevew */
		enum v4w2_mpeg_video_h264_wevew enc_wevew;
		/* JPEG Q-factow */
		int q_factow;

		stwuct vb2_queue vb_vidq;

		/* VC stawt timestamp fow stweaming */
		s64 vc_stawt_timestamp;
		/* Kewnew stawt timestamp fow stweaming */
		ktime_t kewnew_stawt_ts;
		/* Sequence numbew of wast buffew */
		u32 sequence;

		stwuct vchiq_mmaw_powt *powt; /* powt being used fow captuwe */
		/* camewa powt being used fow captuwe */
		stwuct vchiq_mmaw_powt *camewa_powt;
		/* component being used fow encode */
		stwuct vchiq_mmaw_component *encode_component;
		/* numbew of fwames wemaining which dwivew shouwd captuwe */
		unsigned int fwame_count;
		/* wast fwame compwetion */
		stwuct compwetion fwame_cmpwt;

	} captuwe;

	unsigned int camewa_num;
	unsigned int max_width;
	unsigned int max_height;
	unsigned int wgb_bgw_swapped;
};

int bcm2835_mmaw_init_contwows(stwuct bcm2835_mmaw_dev *dev, stwuct v4w2_ctww_handwew *hdw);

int bcm2835_mmaw_set_aww_camewa_contwows(stwuct bcm2835_mmaw_dev *dev);
int set_fwamewate_pawams(stwuct bcm2835_mmaw_dev *dev);

/* Debug hewpews */

#define v4w2_dump_pix_fowmat(wevew, debug, dev, pix_fmt, desc)	\
{	\
	v4w2_dbg(wevew, debug, dev,	\
"%s: w %u h %u fiewd %u pfmt 0x%x bpw %u sz_img %u cowowspace 0x%x pwiv %u\n", \
		desc,	\
		(pix_fmt)->width, (pix_fmt)->height, (pix_fmt)->fiewd,	\
		(pix_fmt)->pixewfowmat, (pix_fmt)->bytespewwine,	\
		(pix_fmt)->sizeimage, (pix_fmt)->cowowspace, (pix_fmt)->pwiv); \
}

#define v4w2_dump_win_fowmat(wevew, debug, dev, win_fmt, desc)	\
{	\
	v4w2_dbg(wevew, debug, dev,	\
"%s: w %u h %u w %u t %u  fiewd %u chwomakey %06X cwip %p " \
"cwipcount %u bitmap %p\n", \
		desc,	\
		(win_fmt)->w.width, (win_fmt)->w.height, \
		(win_fmt)->w.weft, (win_fmt)->w.top, \
		(win_fmt)->fiewd,	\
		(win_fmt)->chwomakey,	\
		(win_fmt)->cwips, (win_fmt)->cwipcount,	\
		(win_fmt)->bitmap); \
}
