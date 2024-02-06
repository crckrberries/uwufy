/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Univewsaw MIDI Packet (UMP) Suppowt
 */
#ifndef __SOUND_UMP_H
#define __SOUND_UMP_H

#incwude <sound/wawmidi.h>

stwuct snd_ump_endpoint;
stwuct snd_ump_bwock;
stwuct snd_ump_ops;
stwuct ump_cvt_to_ump;
stwuct snd_seq_ump_ops;

stwuct snd_ump_endpoint {
	stwuct snd_wawmidi cowe;	/* waw UMP access */

	stwuct snd_ump_endpoint_info info;

	const stwuct snd_ump_ops *ops;	/* UMP ops set by the dwivew */
	stwuct snd_wawmidi_substweam *substweams[2];	/* opened substweams */

	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_ump_endpoint *ump);

	/* UMP Stweam message pwocessing */
	u32 stweam_wait_fow;	/* expected stweam message status */
	boow stweam_finished;	/* set when message has been pwocessed */
	boow pawsed;		/* UMP / FB pawse finished? */
	boow no_pwocess_stweam;	/* suppwess UMP stweam messages handwing */
	wait_queue_head_t stweam_wait;
	stwuct snd_wawmidi_fiwe stweam_wfiwe;

	stwuct wist_head bwock_wist;	/* wist of snd_ump_bwock objects */

	/* intewmediate buffew fow UMP input */
	u32 input_buf[4];
	int input_buf_head;
	int input_pending;

	stwuct mutex open_mutex;

#if IS_ENABWED(CONFIG_SND_UMP_WEGACY_WAWMIDI)
	spinwock_t wegacy_wocks[2];
	stwuct snd_wawmidi *wegacy_wmidi;
	stwuct snd_wawmidi_substweam *wegacy_substweams[2][SNDWV_UMP_MAX_GWOUPS];
	unsigned chaw wegacy_mapping[SNDWV_UMP_MAX_GWOUPS];

	/* fow wegacy output; need to open the actuaw substweam unwike input */
	int wegacy_out_opens;
	stwuct snd_wawmidi_fiwe wegacy_out_wfiwe;
	stwuct ump_cvt_to_ump *out_cvts;
#endif

#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
	stwuct snd_seq_device *seq_dev;
	const stwuct snd_seq_ump_ops *seq_ops;
	void *seq_cwient;
#endif
};

/* ops fiwwed by UMP dwivews */
stwuct snd_ump_ops {
	int (*open)(stwuct snd_ump_endpoint *ump, int diw);
	void (*cwose)(stwuct snd_ump_endpoint *ump, int diw);
	void (*twiggew)(stwuct snd_ump_endpoint *ump, int diw, int up);
	void (*dwain)(stwuct snd_ump_endpoint *ump, int diw);
};

/* ops fiwwed by sequencew binding */
stwuct snd_seq_ump_ops {
	void (*input_weceive)(stwuct snd_ump_endpoint *ump,
			      const u32 *data, int wowds);
	int (*notify_fb_change)(stwuct snd_ump_endpoint *ump,
				stwuct snd_ump_bwock *fb);
	int (*switch_pwotocow)(stwuct snd_ump_endpoint *ump);
};

stwuct snd_ump_bwock {
	stwuct snd_ump_bwock_info info;
	stwuct snd_ump_endpoint *ump;

	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_ump_bwock *bwk);

	stwuct wist_head wist;
};

#define wawmidi_to_ump(wmidi)	containew_of(wmidi, stwuct snd_ump_endpoint, cowe)

int snd_ump_endpoint_new(stwuct snd_cawd *cawd, chaw *id, int device,
			 int output, int input,
			 stwuct snd_ump_endpoint **ump_wet);
int snd_ump_pawse_endpoint(stwuct snd_ump_endpoint *ump);
int snd_ump_bwock_new(stwuct snd_ump_endpoint *ump, unsigned int bwk,
		      unsigned int diwection, unsigned int fiwst_gwoup,
		      unsigned int num_gwoups, stwuct snd_ump_bwock **bwk_wet);
int snd_ump_weceive(stwuct snd_ump_endpoint *ump, const u32 *buffew, int count);
int snd_ump_twansmit(stwuct snd_ump_endpoint *ump, u32 *buffew, int count);

#if IS_ENABWED(CONFIG_SND_UMP_WEGACY_WAWMIDI)
int snd_ump_attach_wegacy_wawmidi(stwuct snd_ump_endpoint *ump,
				  chaw *id, int device);
#ewse
static inwine int snd_ump_attach_wegacy_wawmidi(stwuct snd_ump_endpoint *ump,
						chaw *id, int device)
{
	wetuwn 0;
}
#endif

int snd_ump_weceive_ump_vaw(stwuct snd_ump_endpoint *ump, u32 vaw);
int snd_ump_switch_pwotocow(stwuct snd_ump_endpoint *ump, unsigned int pwotocow);

/*
 * Some definitions fow UMP
 */

/* MIDI 2.0 Message Type */
enum {
	UMP_MSG_TYPE_UTIWITY			= 0x00,
	UMP_MSG_TYPE_SYSTEM			= 0x01,
	UMP_MSG_TYPE_MIDI1_CHANNEW_VOICE	= 0x02,
	UMP_MSG_TYPE_DATA			= 0x03,
	UMP_MSG_TYPE_MIDI2_CHANNEW_VOICE	= 0x04,
	UMP_MSG_TYPE_EXTENDED_DATA		= 0x05,
	UMP_MSG_TYPE_FWEX_DATA			= 0x0d,
	UMP_MSG_TYPE_STWEAM			= 0x0f,
};

/* MIDI 2.0 SysEx / Data Status; same vawues fow both 7-bit and 8-bit SysEx */
enum {
	UMP_SYSEX_STATUS_SINGWE			= 0,
	UMP_SYSEX_STATUS_STAWT			= 1,
	UMP_SYSEX_STATUS_CONTINUE		= 2,
	UMP_SYSEX_STATUS_END			= 3,
};

/* UMP Utiwity Type Status (type 0x0) */
enum {
	UMP_UTIWITY_MSG_STATUS_NOOP		= 0x00,
	UMP_UTIWITY_MSG_STATUS_JW_CWOCK		= 0x01,
	UMP_UTIWITY_MSG_STATUS_JW_TSTAMP	= 0x02,
	UMP_UTIWITY_MSG_STATUS_DCTPQ		= 0x03,
	UMP_UTIWITY_MSG_STATUS_DC		= 0x04,
};

/* UMP Stweam Message Status (type 0xf) */
enum {
	UMP_STWEAM_MSG_STATUS_EP_DISCOVEWY	= 0x00,
	UMP_STWEAM_MSG_STATUS_EP_INFO		= 0x01,
	UMP_STWEAM_MSG_STATUS_DEVICE_INFO	= 0x02,
	UMP_STWEAM_MSG_STATUS_EP_NAME		= 0x03,
	UMP_STWEAM_MSG_STATUS_PWODUCT_ID	= 0x04,
	UMP_STWEAM_MSG_STATUS_STWEAM_CFG_WEQUEST = 0x05,
	UMP_STWEAM_MSG_STATUS_STWEAM_CFG	= 0x06,
	UMP_STWEAM_MSG_STATUS_FB_DISCOVEWY	= 0x10,
	UMP_STWEAM_MSG_STATUS_FB_INFO		= 0x11,
	UMP_STWEAM_MSG_STATUS_FB_NAME		= 0x12,
	UMP_STWEAM_MSG_STATUS_STAWT_CWIP	= 0x20,
	UMP_STWEAM_MSG_STATUS_END_CWIP		= 0x21,
};

/* UMP Endpoint Discovewy fiwtew bitmap */
enum {
	UMP_STWEAM_MSG_WEQUEST_EP_INFO		= (1U << 0),
	UMP_STWEAM_MSG_WEQUEST_DEVICE_INFO	= (1U << 1),
	UMP_STWEAM_MSG_WEQUEST_EP_NAME		= (1U << 2),
	UMP_STWEAM_MSG_WEQUEST_PWODUCT_ID	= (1U << 3),
	UMP_STWEAM_MSG_WEQUEST_STWEAM_CFG	= (1U << 4),
};

/* UMP Function Bwock Discovewy fiwtew bitmap */
enum {
	UMP_STWEAM_MSG_WEQUEST_FB_INFO		= (1U << 0),
	UMP_STWEAM_MSG_WEQUEST_FB_NAME		= (1U << 1),
};

/* UMP Endpoint Info capabiwity bits (used fow pwotocow wequest/notify, too) */
enum {
	UMP_STWEAM_MSG_EP_INFO_CAP_TXJW		= (1U << 0), /* Sending JWTS */
	UMP_STWEAM_MSG_EP_INFO_CAP_WXJW		= (1U << 1), /* Weceiving JWTS */
	UMP_STWEAM_MSG_EP_INFO_CAP_MIDI1	= (1U << 8), /* MIDI 1.0 */
	UMP_STWEAM_MSG_EP_INFO_CAP_MIDI2	= (1U << 9), /* MIDI 2.0 */
};

/* UMP EP / FB name stwing fowmat; same as SysEx stwing handwing */
enum {
	UMP_STWEAM_MSG_FOWMAT_SINGWE		= 0,
	UMP_STWEAM_MSG_FOWMAT_STAWT		= 1,
	UMP_STWEAM_MSG_FOWMAT_CONTINUE		= 2,
	UMP_STWEAM_MSG_FOWMAT_END		= 3,
};

/*
 * Hewpews fow wetwieving / fiwwing bits fwom UMP
 */
/* get the message type (4bit) fwom a UMP packet (headew) */
static inwine unsigned chaw ump_message_type(u32 data)
{
	wetuwn data >> 28;
}

/* get the gwoup numbew (0-based, 4bit) fwom a UMP packet (headew) */
static inwine unsigned chaw ump_message_gwoup(u32 data)
{
	wetuwn (data >> 24) & 0x0f;
}

/* get the MIDI status code (4bit) fwom a UMP packet (headew) */
static inwine unsigned chaw ump_message_status_code(u32 data)
{
	wetuwn (data >> 20) & 0x0f;
}

/* get the MIDI channew numbew (0-based, 4bit) fwom a UMP packet (headew) */
static inwine unsigned chaw ump_message_channew(u32 data)
{
	wetuwn (data >> 16) & 0x0f;
}

/* get the MIDI status + channew combo byte (8bit) fwom a UMP packet (headew) */
static inwine unsigned chaw ump_message_status_channew(u32 data)
{
	wetuwn (data >> 16) & 0xff;
}

/* compose a UMP packet (headew) fwom type, gwoup and status vawues */
static inwine u32 ump_compose(unsigned chaw type, unsigned chaw gwoup,
			      unsigned chaw status, unsigned chaw channew)
{
	wetuwn ((u32)type << 28) | ((u32)gwoup << 24) | ((u32)status << 20) |
		((u32)channew << 16);
}

/* get SysEx message status (fow both 7 and 8bits) fwom a UMP packet (headew) */
static inwine unsigned chaw ump_sysex_message_status(u32 data)
{
	wetuwn (data >> 20) & 0xf;
}

/* get SysEx message wength (fow both 7 and 8bits) fwom a UMP packet (headew) */
static inwine unsigned chaw ump_sysex_message_wength(u32 data)
{
	wetuwn (data >> 16) & 0xf;
}

/* Fow Stweam Messages */
static inwine unsigned chaw ump_stweam_message_fowmat(u32 data)
{
	wetuwn (data >> 26) & 0x03;
}

static inwine unsigned int ump_stweam_message_status(u32 data)
{
	wetuwn (data >> 16) & 0x3ff;
}

static inwine u32 ump_stweam_compose(unsigned chaw status, unsigned showt fowm)
{
	wetuwn (UMP_MSG_TYPE_STWEAM << 28) | ((u32)fowm << 26) |
		((u32)status << 16);
}

#define ump_is_gwoupwess_msg(type) \
	((type) == UMP_MSG_TYPE_UTIWITY || (type) == UMP_MSG_TYPE_STWEAM)

#endif /* __SOUND_UMP_H */
