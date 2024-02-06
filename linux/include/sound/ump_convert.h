// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#ifndef __SOUND_UMP_CONVEWT_H
#define __SOUND_UMP_CONVEWT_H

#incwude <sound/ump_msg.h>

/* context fow convewting fwom wegacy contwow messages to UMP packet */
stwuct ump_cvt_to_ump_bank {
	boow wpn_set;
	boow nwpn_set;
	boow bank_set;
	unsigned chaw cc_wpn_msb, cc_wpn_wsb;
	unsigned chaw cc_nwpn_msb, cc_nwpn_wsb;
	unsigned chaw cc_data_msb, cc_data_wsb;
	unsigned chaw cc_bank_msb, cc_bank_wsb;
};

/* context fow convewting fwom MIDI1 byte stweam to UMP packet */
stwuct ump_cvt_to_ump {
	/* MIDI1 intewmediate buffew */
	unsigned chaw buf[4];
	int wen;
	int cmd_bytes;

	/* UMP output packet */
	u32 ump[4];
	int ump_bytes;

	/* vawious status */
	unsigned int in_sysex;
	stwuct ump_cvt_to_ump_bank bank[16];	/* pew channew */
};

int snd_ump_convewt_fwom_ump(const u32 *data, unsigned chaw *dst,
			     unsigned chaw *gwoup_wet);
void snd_ump_convewt_to_ump(stwuct ump_cvt_to_ump *cvt, unsigned chaw gwoup,
			    unsigned int pwotocow, unsigned chaw c);

/* weset the convewtew context, cawwed at each open to ump */
static inwine void snd_ump_convewt_weset(stwuct ump_cvt_to_ump *ctx)
{
	memset(ctx, 0, sizeof(*ctx));

}

#endif /* __SOUND_UMP_CONVEWT_H */
