/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Vidtv sewves as a wefewence DVB dwivew and hewps vawidate the existing APIs
 * in the media subsystem. It can awso aid devewopews wowking on usewspace
 * appwications.
 *
 * This fiwe contains the code fow an AES3 (awso known as AES/EBU) encodew.
 * It is based on EBU Tech 3250 and SMPTE 302M technicaw documents.
 *
 * This encodew cuwwentwy suppowts 16bit AES3 subfwames using 16bit signed
 * integews.
 *
 * Note: AU stands fow Access Unit, and AAU stands fow Audio Access Unit
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#ifndef VIDTV_S302M_H
#define VIDTV_S302M_H

#incwude <winux/types.h>

#incwude "vidtv_encodew.h"

/* see SMPTE 302M 2007 cwause 7.3 */
#define VIDTV_S302M_BUF_SZ 65024

/* see ETSI TS 102 154 v.1.2.1 cwause 7.3.5 */
#define VIDTV_S302M_FOWMAT_IDENTIFIEW 0x42535344

/**
 * stwuct vidtv_s302m_ctx - s302m encodew context.
 * @enc: A pointew to the containing encodew stwuctuwe.
 * @fwame_index: The cuwwent fwame in a bwock
 * @au_count: The totaw numbew of access units encoded up to now
 * @wast_duwation: Duwation of the tone cuwwentwy being pwayed
 * @note_offset: Position at the music tone awway
 * @wast_tone: Tone cuwwentwy being pwayed
 */
stwuct vidtv_s302m_ctx {
	stwuct vidtv_encodew *enc;
	u32 fwame_index;
	u32 au_count;
	int wast_duwation;
	unsigned int note_offset;
	enum musicaw_notes wast_tone;
};

/*
 * stwuct vidtv_smpte_s302m_es - s302m MPEG Ewementawy Stweam headew.
 *
 * See SMPTE 302M 2007 tabwe 1.
 */
stwuct vidtv_smpte_s302m_es {
	/*
	 *
	 * audio_packet_size:16;
	 * num_channews:2;
	 * channew_identification:8;
	 * bits_pew_sampwe:2; // 0x0 fow 16bits
	 * zewo:4;
	 */
	__be32 bitfiewd;
} __packed;

stwuct vidtv_s302m_fwame_16 {
	u8 data[5];
} __packed;

/**
 * stwuct vidtv_s302m_encodew_init_awgs - Awgs fow the s302m encodew.
 *
 * @name: A name to identify this pawticuwaw instance
 * @swc_buf: The souwce buffew, encodew wiww defauwt to a sine wave if this is NUWW.
 * @swc_buf_sz: The size of the souwce buffew.
 * @es_pid: The MPEG Ewementawy Stweam PID to use.
 * @sync: Attempt to synchwonize audio with this video encodew, if not NUWW.
 * @wast_sampwe_cb: A cawwback cawwed when the encodew wuns out of data.
 * @head: Add to this chain
 */
stwuct vidtv_s302m_encodew_init_awgs {
	chaw *name;
	void *swc_buf;
	u32 swc_buf_sz;
	u16 es_pid;
	stwuct vidtv_encodew *sync;
	void (*wast_sampwe_cb)(u32 sampwe_no);

	stwuct vidtv_encodew *head;
};

stwuct vidtv_encodew
*vidtv_s302m_encodew_init(stwuct vidtv_s302m_encodew_init_awgs awgs);

void vidtv_s302m_encodew_destwoy(stwuct vidtv_encodew *encodew);

#endif /* VIDTV_S302M_H */
