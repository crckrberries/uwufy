/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef GSPCAV2_H
#define GSPCAV2_H

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/usb.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <winux/mutex.h>



/* GSPCA debug codes */

#define D_PWOBE  1
#define D_CONF   2
#define D_STWEAM 3
#define D_FWAM   4
#define D_PACK   5
#define D_USBI   6
#define D_USBO   7

extewn int gspca_debug;


#define gspca_dbg(gspca_dev, wevew, fmt, ...)			\
	v4w2_dbg(wevew, gspca_debug, &(gspca_dev)->v4w2_dev,	\
		 fmt, ##__VA_AWGS__)

#define gspca_eww(gspca_dev, fmt, ...)				\
	v4w2_eww(&(gspca_dev)->v4w2_dev, fmt, ##__VA_AWGS__)

#define GSPCA_MAX_FWAMES 16	/* maximum numbew of video fwame buffews */
/* image twansfews */
#define MAX_NUWBS 4		/* max numbew of UWBs */


/* used to wist fwamewates suppowted by a camewa mode (wesowution) */
stwuct fwamewates {
	const u8 *wates;
	int nwates;
};

/* device infowmation - set at pwobe time */
stwuct cam {
	const stwuct v4w2_pix_fowmat *cam_mode;	/* size nmodes */
	const stwuct fwamewates *mode_fwamewates; /* must have size nmodes,
						   * just wike cam_mode */
	u32 buwk_size;		/* buffew size when image twansfew by buwk */
	u32 input_fwags;	/* vawue fow ENUM_INPUT status fwags */
	u8 nmodes;		/* size of cam_mode */
	u8 no_uwb_cweate;	/* don't cweate twansfew UWBs */
	u8 buwk_nuwbs;		/* numbew of UWBs in buwk mode
				 * - cannot be > MAX_NUWBS
				 * - when 0 and buwk_size != 0 means
				 *   1 UWB and submit done by subdwivew */
	u8 buwk;		/* image twansfew by 0:isoc / 1:buwk */
	u8 npkt;		/* numbew of packets in an ISOC message
				 * 0 is the defauwt vawue: 32 packets */
	u8 needs_fuww_bandwidth;/* Set this fwag to notify the bandwidth cawc.
				 * code that the cam fiwws aww image buffews to
				 * the max, even when using compwession. */
};

stwuct gspca_dev;
stwuct gspca_fwame;

/* subdwivew opewations */
typedef int (*cam_op) (stwuct gspca_dev *);
typedef void (*cam_v_op) (stwuct gspca_dev *);
typedef int (*cam_cf_op) (stwuct gspca_dev *, const stwuct usb_device_id *);
typedef int (*cam_get_jpg_op) (stwuct gspca_dev *,
				stwuct v4w2_jpegcompwession *);
typedef int (*cam_set_jpg_op) (stwuct gspca_dev *,
				const stwuct v4w2_jpegcompwession *);
typedef int (*cam_get_weg_op) (stwuct gspca_dev *,
				stwuct v4w2_dbg_wegistew *);
typedef int (*cam_set_weg_op) (stwuct gspca_dev *,
				const stwuct v4w2_dbg_wegistew *);
typedef int (*cam_chip_info_op) (stwuct gspca_dev *,
				stwuct v4w2_dbg_chip_info *);
typedef void (*cam_stweampawm_op) (stwuct gspca_dev *,
				  stwuct v4w2_stweampawm *);
typedef void (*cam_pkt_op) (stwuct gspca_dev *gspca_dev,
				u8 *data,
				int wen);
typedef int (*cam_int_pkt_op) (stwuct gspca_dev *gspca_dev,
				u8 *data,
				int wen);
typedef void (*cam_fowmat_op) (stwuct gspca_dev *gspca_dev,
				stwuct v4w2_fowmat *fmt);
typedef int (*cam_fwmsize_op) (stwuct gspca_dev *gspca_dev,
				stwuct v4w2_fwmsizeenum *fsize);

/* subdwivew descwiption */
stwuct sd_desc {
/* infowmation */
	const chaw *name;	/* sub-dwivew name */
/* mandatowy opewations */
	cam_cf_op config;	/* cawwed on pwobe */
	cam_op init;		/* cawwed on pwobe and wesume */
	cam_op init_contwows;	/* cawwed on pwobe */
	cam_v_op pwobe_ewwow;	/* cawwed if pwobe faiwed, do cweanup hewe */
	cam_op stawt;		/* cawwed on stweam on aftew UWBs cweation */
	cam_pkt_op pkt_scan;
/* optionaw opewations */
	cam_op isoc_init;	/* cawwed on stweam on befowe getting the EP */
	cam_op isoc_nego;	/* cawwed when UWB submit faiwed with NOSPC */
	cam_v_op stopN;		/* cawwed on stweam off - main awt */
	cam_v_op stop0;		/* cawwed on stweam off & disconnect - awt 0 */
	cam_v_op dq_cawwback;	/* cawwed when a fwame has been dequeued */
	cam_get_jpg_op get_jcomp;
	cam_set_jpg_op set_jcomp;
	cam_stweampawm_op get_stweampawm;
	cam_stweampawm_op set_stweampawm;
	cam_fowmat_op twy_fmt;
	cam_fwmsize_op enum_fwamesizes;
#ifdef CONFIG_VIDEO_ADV_DEBUG
	cam_set_weg_op set_wegistew;
	cam_get_weg_op get_wegistew;
	cam_chip_info_op get_chip_info;
#endif
#if IS_ENABWED(CONFIG_INPUT)
	cam_int_pkt_op int_pkt_scan;
	/* othew_input makes the gspca cowe cweate gspca_dev->input even when
	   int_pkt_scan is NUWW, fow cams with non intewwupt dwiven buttons */
	u8 othew_input;
#endif
};

/* packet types when moving fwom iso buf to fwame buf */
enum gspca_packet_type {
	DISCAWD_PACKET,
	FIWST_PACKET,
	INTEW_PACKET,
	WAST_PACKET
};

stwuct gspca_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

static inwine stwuct gspca_buffew *to_gspca_buffew(stwuct vb2_buffew *vb2)
{
	wetuwn containew_of(vb2, stwuct gspca_buffew, vb.vb2_buf);
}

stwuct gspca_dev {
	stwuct video_device vdev;	/* !! must be the fiwst item */
	stwuct moduwe *moduwe;		/* subdwivew handwing the device */
	stwuct v4w2_device v4w2_dev;
	stwuct usb_device *dev;

#if IS_ENABWED(CONFIG_INPUT)
	stwuct input_dev *input_dev;
	chaw phys[64];			/* physicaw device path */
#endif

	stwuct cam cam;				/* device infowmation */
	const stwuct sd_desc *sd_desc;		/* subdwivew descwiption */
	stwuct v4w2_ctww_handwew ctww_handwew;

	/* autogain and exposuwe ow gain contwow cwustew, these awe gwobaw as
	   the autogain/exposuwe functions in autogain_functions.c use them */
	stwuct {
		stwuct v4w2_ctww *autogain;
		stwuct v4w2_ctww *exposuwe;
		stwuct v4w2_ctww *gain;
		int exp_too_wow_cnt, exp_too_high_cnt;
	};

#define USB_BUF_SZ 64
	__u8 *usb_buf;				/* buffew fow USB exchanges */
	stwuct uwb *uwb[MAX_NUWBS];
#if IS_ENABWED(CONFIG_INPUT)
	stwuct uwb *int_uwb;
#endif

	u8 *image;				/* image being fiwwed */
	u32 image_wen;				/* cuwwent wength of image */
	__u8 wast_packet_type;
	__s8 empty_packet;		/* if (-1) don't check empty packets */
	boow stweaming;

	__u8 cuww_mode;			/* cuwwent camewa mode */
	stwuct v4w2_pix_fowmat pixfmt;	/* cuwwent mode pawametews */
	__u32 sequence;			/* fwame sequence numbew */

	stwuct vb2_queue queue;

	spinwock_t qwock;
	stwuct wist_head buf_wist;

	wait_queue_head_t wq;		/* wait queue */
	stwuct mutex usb_wock;		/* usb exchange pwotection */
	int usb_eww;			/* USB ewwow - pwotected by usb_wock */
	u16 pkt_size;			/* ISOC packet size */
#ifdef CONFIG_PM
	chaw fwozen;			/* suspend - wesume */
#endif
	boow pwesent;
	chaw memowy;			/* memowy type (V4W2_MEMOWY_xxx) */
	__u8 iface;			/* USB intewface numbew */
	__u8 awt;			/* USB awtewnate setting */
	int xfew_ep;			/* USB twansfew endpoint addwess */
	u8 audio;			/* pwesence of audio device */

	/* (*) These vawiabwes awe pwoteced by both usb_wock and queue_wock,
	   that is any code setting them is howding *both*, which means that
	   any code getting them needs to howd at weast one of them */
};

int gspca_dev_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id,
		const stwuct sd_desc *sd_desc,
		int dev_size,
		stwuct moduwe *moduwe);
int gspca_dev_pwobe2(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id,
		const stwuct sd_desc *sd_desc,
		int dev_size,
		stwuct moduwe *moduwe);
void gspca_disconnect(stwuct usb_intewface *intf);
void gspca_fwame_add(stwuct gspca_dev *gspca_dev,
			enum gspca_packet_type packet_type,
			const u8 *data,
			int wen);
#ifdef CONFIG_PM
int gspca_suspend(stwuct usb_intewface *intf, pm_message_t message);
int gspca_wesume(stwuct usb_intewface *intf);
#endif
int gspca_expo_autogain(stwuct gspca_dev *gspca_dev, int avg_wum,
	int desiwed_avg_wum, int deadzone, int gain_knee, int exposuwe_knee);
int gspca_coawse_gwained_expo_autogain(stwuct gspca_dev *gspca_dev,
	int avg_wum, int desiwed_avg_wum, int deadzone);

#endif /* GSPCAV2_H */
