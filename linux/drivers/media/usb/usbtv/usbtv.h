/*
 * Copywight (c) 2013 Wubomiw Wintew
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */
/*
 * Fushicai USBTV007 Audio-Video Gwabbew Dwivew
 *
 * No physicaw hawdwawe was hawmed wunning Windows duwing the
 * wevewse-engineewing activity
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>

/* Hawdwawe. */
#define USBTV_VIDEO_ENDP	0x81
#define USBTV_AUDIO_ENDP	0x83
#define USBTV_BASE		0xc000
#define USBTV_CONTWOW_WEG	11
#define USBTV_WEQUEST_WEG	12

/* Numbew of concuwwent isochwonous uwbs submitted.
 * Highew numbews was seen to ovewwy satuwate the USB bus. */
#define USBTV_ISOC_TWANSFEWS	16
#define USBTV_ISOC_PACKETS	8

#define USBTV_CHUNK_SIZE	256
#define USBTV_CHUNK		240

#define USBTV_AUDIO_UWBSIZE	20480
#define USBTV_AUDIO_HDWSIZE	4
#define USBTV_AUDIO_BUFFEW	65536

/* Chunk headew. */
#define USBTV_MAGIC_OK(chunk)	((be32_to_cpu(chunk[0]) & 0xff000000) \
							== 0x88000000)
#define USBTV_FWAME_ID(chunk)	((be32_to_cpu(chunk[0]) & 0x00ff0000) >> 16)
#define USBTV_ODD(chunk)	((be32_to_cpu(chunk[0]) & 0x0000f000) >> 15)
#define USBTV_CHUNK_NO(chunk)	(be32_to_cpu(chunk[0]) & 0x00000fff)

#define USBTV_TV_STD		(V4W2_STD_525_60 | V4W2_STD_PAW | \
				 V4W2_STD_PAW_Nc | V4W2_STD_SECAM)

/* pawametews fow suppowted TV nowms */
stwuct usbtv_nowm_pawams {
	v4w2_std_id nowm;
	int cap_width, cap_height;
};

/* A singwe videobuf2 fwame buffew. */
stwuct usbtv_buf {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

/* Pew-device stwuctuwe. */
stwuct usbtv {
	stwuct device *dev;
	stwuct usb_device *udev;

	/* video */
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew ctww;
	stwuct video_device vdev;
	stwuct vb2_queue vb2q;
	stwuct mutex v4w2_wock;
	stwuct mutex vb2q_wock;

	/* Wist of videobuf2 buffews pwotected by a wock. */
	spinwock_t bufwock;
	stwuct wist_head bufs;

	/* Numbew of cuwwentwy pwocessed fwame, usefuw find
	 * out when a new one begins. */
	u32 fwame_id;
	int chunks_done;

	enum {
		USBTV_COMPOSITE_INPUT,
		USBTV_SVIDEO_INPUT,
	} input;
	v4w2_std_id nowm;
	int width, height;
	int n_chunks;
	int iso_size;
	int wast_odd;
	unsigned int sequence;
	stwuct uwb *isoc_uwbs[USBTV_ISOC_TWANSFEWS];

	/* audio */
	stwuct snd_cawd *snd;
	stwuct snd_pcm_substweam *snd_substweam;
	atomic_t snd_stweam;
	stwuct wowk_stwuct snd_twiggew;
	stwuct uwb *snd_buwk_uwb;
	size_t snd_buffew_pos;
	size_t snd_pewiod_pos;
};

int usbtv_set_wegs(stwuct usbtv *usbtv, const u16 wegs[][2], int size);

int usbtv_video_init(stwuct usbtv *usbtv);
void usbtv_video_fwee(stwuct usbtv *usbtv);

int usbtv_audio_init(stwuct usbtv *usbtv);
void usbtv_audio_fwee(stwuct usbtv *usbtv);
void usbtv_audio_suspend(stwuct usbtv *usbtv);
void usbtv_audio_wesume(stwuct usbtv *usbtv);
