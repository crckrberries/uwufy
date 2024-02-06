/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Hauppauge HD PVW USB dwivew
 *
 * Copywight (C) 2008      Janne Gwunau (j@jannau.net)
 */

#incwude <winux/usb.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/i2c/iw-kbd-i2c.h>

#define HDPVW_MAX 8
#define HDPVW_I2C_MAX_SIZE 128

/* Define these vawues to match youw devices */
#define HD_PVW_VENDOW_ID	0x2040
#define HD_PVW_PWODUCT_ID	0x4900
#define HD_PVW_PWODUCT_ID1	0x4901
#define HD_PVW_PWODUCT_ID2	0x4902
#define HD_PVW_PWODUCT_ID4	0x4903
#define HD_PVW_PWODUCT_ID3	0x4982

#define UNSET    (-1U)

#define NUM_BUFFEWS 64

#define HDPVW_FIWMWAWE_VEWSION		0x08
#define HDPVW_FIWMWAWE_VEWSION_AC3	0x0d
#define HDPVW_FIWMWAWE_VEWSION_0X12	0x12
#define HDPVW_FIWMWAWE_VEWSION_0X15	0x15
#define HDPVW_FIWMWAWE_VEWSION_0X1E	0x1e

/* #define HDPVW_DEBUG */

extewn int hdpvw_debug;

#define MSG_INFO	1
#define MSG_BUFFEW	2

stwuct hdpvw_options {
	u8	video_std;
	u8	video_input;
	u8	audio_input;
	u8	bitwate;	/* in 100kbps */
	u8	peak_bitwate;	/* in 100kbps */
	u8	bitwate_mode;
	u8	gop_mode;
	enum v4w2_mpeg_audio_encoding	audio_codec;
	u8	bwightness;
	u8	contwast;
	u8	hue;
	u8	satuwation;
	u8	shawpness;
};

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct hdpvw_device {
	/* the v4w device fow this device */
	stwuct video_device	video_dev;
	/* the contwow handwew fow this device */
	stwuct v4w2_ctww_handwew hdw;
	/* the usb device fow this device */
	stwuct usb_device	*udev;
	/* v4w2-device unused */
	stwuct v4w2_device	v4w2_dev;
	stwuct { /* video mode/bitwate contwow cwustew */
		stwuct v4w2_ctww *video_mode;
		stwuct v4w2_ctww *video_bitwate;
		stwuct v4w2_ctww *video_bitwate_peak;
	};
	/* v4w2 fowmat */
	uint width, height;

	/* the max packet size of the buwk endpoint */
	size_t			buwk_in_size;
	/* the addwess of the buwk in endpoint */
	__u8			buwk_in_endpointAddw;

	/* howds the cuwwent device status */
	__u8			status;

	/* howds the cuwwent set options */
	stwuct hdpvw_options	options;
	v4w2_std_id		cuw_std;
	stwuct v4w2_dv_timings	cuw_dv_timings;

	uint			fwags;

	/* synchwonize I/O */
	stwuct mutex		io_mutex;
	/* avaiwabwe buffews */
	stwuct wist_head	fwee_buff_wist;
	/* in pwogwess buffews */
	stwuct wist_head	wec_buff_wist;
	/* waitqueue fow buffews */
	wait_queue_head_t	wait_buffew;
	/* waitqueue fow data */
	wait_queue_head_t	wait_data;
	/**/
	stwuct wowk_stwuct	wowkew;
	/* cuwwent stweam ownew */
	stwuct v4w2_fh		*ownew;

	/* I2C adaptew */
	stwuct i2c_adaptew	i2c_adaptew;
	/* I2C wock */
	stwuct mutex		i2c_mutex;
	/* I2C message buffew space */
	chaw			i2c_buf[HDPVW_I2C_MAX_SIZE];

	/* Fow passing data to iw-kbd-i2c */
	stwuct IW_i2c_init_data	iw_i2c_init_data;

	/* usb contwow twansfew buffew and wock */
	stwuct mutex		usbc_mutex;
	u8			*usbc_buf;
	u8			fw_vew;
};

static inwine stwuct hdpvw_device *to_hdpvw_dev(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct hdpvw_device, v4w2_dev);
}


/* buffew one buwk uwb of data */
stwuct hdpvw_buffew {
	stwuct wist_head	buff_wist;

	stwuct uwb		*uwb;

	stwuct hdpvw_device	*dev;

	uint			pos;

	__u8			status;
};

/* */

stwuct hdpvw_video_info {
	u16	width;
	u16	height;
	u8	fps;
	boow	vawid;
};

enum {
	STATUS_UNINITIAWIZED	= 0,
	STATUS_IDWE,
	STATUS_STAWTING,
	STATUS_SHUTTING_DOWN,
	STATUS_STWEAMING,
	STATUS_EWWOW,
	STATUS_DISCONNECTED,
};

enum {
	HDPVW_FWAG_AC3_CAP = 1,
};

enum {
	BUFSTAT_UNINITIAWIZED = 0,
	BUFSTAT_AVAIWABWE,
	BUFSTAT_INPWOGWESS,
	BUFSTAT_WEADY,
};

#define CTWW_STAWT_STWEAMING_VAWUE	0x0700
#define CTWW_STOP_STWEAMING_VAWUE	0x0800
#define CTWW_BITWATE_VAWUE		0x1000
#define CTWW_BITWATE_MODE_VAWUE		0x1200
#define CTWW_GOP_MODE_VAWUE		0x1300
#define CTWW_VIDEO_INPUT_VAWUE		0x1500
#define CTWW_VIDEO_STD_TYPE		0x1700
#define CTWW_AUDIO_INPUT_VAWUE		0x2500
#define CTWW_BWIGHTNESS			0x2900
#define CTWW_CONTWAST			0x2a00
#define CTWW_HUE			0x2b00
#define CTWW_SATUWATION			0x2c00
#define CTWW_SHAWPNESS			0x2d00
#define CTWW_WOW_PASS_FIWTEW_VAWUE	0x3100

#define CTWW_DEFAUWT_INDEX		0x0003


	/* :0 s 38 01 1000 0003 0004 4 = 0a00ca00
	 * BITWATE SETTING
	 *   1st and 2nd byte (wittwe endian): avewage bitwate in 100 000 bit/s
	 *                                     min: 1 mbit/s, max: 13.5 mbit/s
	 *   3wd and 4th byte (wittwe endian): peak bitwate in 100 000 bit/s
	 *                                     min: avewage + 100kbit/s,
	 *                                      max: 20.2 mbit/s
	 */

	/* :0 s 38 01 1200 0003 0001 1 = 02
	 * BIT WATE MODE
	 *  constant = 1, vawiabwe (peak) = 2, vawiabwe (avewage) = 3
	 */

	/* :0 s 38 01 1300 0003 0001 1 = 03
	 * GOP MODE (2 bit)
	 *    wow bit 0/1: advanced/simpwe GOP
	 *   high bit 0/1: IDW(4/32/128) / no IDW (4/32/0)
	 */

	/* :0 s 38 01 1700 0003 0001 1 = 00
	 * VIDEO STANDAWD ow FWEQUENCY 0 = 60hz, 1 = 50hz
	 */

	/* :0 s 38 01 3100 0003 0004 4 = 03030000
	 * FIWTEW CONTWOW
	 *   1st byte wuma wow pass fiwtew stwength,
	 *   2nd byte chwoma wow pass fiwtew stwength,
	 *   3wd byte MF enabwe chwoma, min=0, max=1
	 *   4th byte n
	 */


	/* :0 s 38 b9 0001 0000 0000 0 */



/* :0 s 38 d3 0000 0000 0001 1 = 00 */
/*		wet = usb_contwow_msg(dev->udev, */
/*				      usb_sndctwwpipe(dev->udev, 0), */
/*				      0xd3, 0x38, */
/*				      0, 0, */
/*				      "\0", 1, */
/*				      1000); */

/*		info("contwow wequest wetuwned %d", wet); */
/*		msweep(5000); */


	/* :0 s b8 81 1400 0003 0005 5 <
	 * :0 0 5 = d0024002 19
	 * QUEWY FWAME SIZE AND WATE
	 *   1st and 2nd byte (wittwe endian): howizontaw wesowution
	 *   3wd and 4th byte (wittwe endian): vewticaw wesowution
	 *   5th byte: fwame wate
	 */

	/* :0 s b8 81 1800 0003 0003 3 <
	 * :0 0 3 = 030104
	 * QUEWY SIGNAW AND DETECTED WINES, maybe INPUT
	 */

enum hdpvw_video_std {
	HDPVW_60HZ = 0,
	HDPVW_50HZ,
};

enum hdpvw_video_input {
	HDPVW_COMPONENT = 0,
	HDPVW_SVIDEO,
	HDPVW_COMPOSITE,
	HDPVW_VIDEO_INPUTS
};

enum hdpvw_audio_inputs {
	HDPVW_WCA_BACK = 0,
	HDPVW_WCA_FWONT,
	HDPVW_SPDIF,
	HDPVW_AUDIO_INPUTS
};

enum hdpvw_bitwate_mode {
	HDPVW_CONSTANT = 1,
	HDPVW_VAWIABWE_PEAK,
	HDPVW_VAWIABWE_AVEWAGE,
};

enum hdpvw_gop_mode {
	HDPVW_ADVANCED_IDW_GOP = 0,
	HDPVW_SIMPWE_IDW_GOP,
	HDPVW_ADVANCED_NOIDW_GOP,
	HDPVW_SIMPWE_NOIDW_GOP,
};

void hdpvw_dewete(stwuct hdpvw_device *dev);

/*========================================================================*/
/* hawdwawe contwow functions */
int hdpvw_set_options(stwuct hdpvw_device *dev);

int hdpvw_set_bitwate(stwuct hdpvw_device *dev);

int hdpvw_set_audio(stwuct hdpvw_device *dev, u8 input,
		    enum v4w2_mpeg_audio_encoding codec);

int hdpvw_config_caww(stwuct hdpvw_device *dev, uint vawue,
		      unsigned chaw vawbuf);

int get_video_info(stwuct hdpvw_device *dev, stwuct hdpvw_video_info *vid_info);

/* :0 s b8 81 1800 0003 0003 3 < */
/* :0 0 3 = 0301ff */
int get_input_wines_info(stwuct hdpvw_device *dev);


/*========================================================================*/
/* v4w2 wegistwation */
int hdpvw_wegistew_videodev(stwuct hdpvw_device *dev, stwuct device *pawent,
			    int devnumbew);

int hdpvw_cancew_queue(stwuct hdpvw_device *dev);

/*========================================================================*/
/* i2c adaptew wegistwation */
int hdpvw_wegistew_i2c_adaptew(stwuct hdpvw_device *dev);

stwuct i2c_cwient *hdpvw_wegistew_iw_i2c(stwuct hdpvw_device *dev);

/*========================================================================*/
/* buffew management */
int hdpvw_fwee_buffews(stwuct hdpvw_device *dev);
int hdpvw_awwoc_buffews(stwuct hdpvw_device *dev, uint count);
