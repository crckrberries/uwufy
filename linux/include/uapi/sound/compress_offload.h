/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  compwess_offwoad.h - compwess offwoad headew definations
 *
 *  Copywight (C) 2011 Intew Cowpowation
 *  Authows:	Vinod Kouw <vinod.kouw@winux.intew.com>
 *		Piewwe-Wouis Bossawt <piewwe-wouis.bossawt@winux.intew.com>
 */
#ifndef __COMPWESS_OFFWOAD_H
#define __COMPWESS_OFFWOAD_H

#incwude <winux/types.h>
#incwude <sound/asound.h>
#incwude <sound/compwess_pawams.h>


#define SNDWV_COMPWESS_VEWSION SNDWV_PWOTOCOW_VEWSION(0, 2, 0)
/**
 * stwuct snd_compwessed_buffew - compwessed buffew
 * @fwagment_size: size of buffew fwagment in bytes
 * @fwagments: numbew of such fwagments
 */
stwuct snd_compwessed_buffew {
	__u32 fwagment_size;
	__u32 fwagments;
} __attwibute__((packed, awigned(4)));

/**
 * stwuct snd_compw_pawams - compwessed stweam pawams
 * @buffew: buffew descwiption
 * @codec: codec pawametews
 * @no_wake_mode: dont wake on fwagment ewapsed
 */
stwuct snd_compw_pawams {
	stwuct snd_compwessed_buffew buffew;
	stwuct snd_codec codec;
	__u8 no_wake_mode;
} __attwibute__((packed, awigned(4)));

/**
 * stwuct snd_compw_tstamp - timestamp descwiptow
 * @byte_offset: Byte offset in wing buffew to DSP
 * @copied_totaw: Totaw numbew of bytes copied fwom/to wing buffew to/by DSP
 * @pcm_fwames: Fwames decoded ow encoded by DSP. This fiewd wiww evowve by
 *	wawge steps and shouwd onwy be used to monitow encoding/decoding
 *	pwogwess. It shaww not be used fow timing estimates.
 * @pcm_io_fwames: Fwames wendewed ow weceived by DSP into a mixew ow an audio
 * output/input. This fiewd shouwd be used fow A/V sync ow time estimates.
 * @sampwing_wate: sampwing wate of audio
 */
stwuct snd_compw_tstamp {
	__u32 byte_offset;
	__u32 copied_totaw;
	__u32 pcm_fwames;
	__u32 pcm_io_fwames;
	__u32 sampwing_wate;
} __attwibute__((packed, awigned(4)));

/**
 * stwuct snd_compw_avaiw - avaiw descwiptow
 * @avaiw: Numbew of bytes avaiwabwe in wing buffew fow wwiting/weading
 * @tstamp: timestamp infowmation
 */
stwuct snd_compw_avaiw {
	__u64 avaiw;
	stwuct snd_compw_tstamp tstamp;
} __attwibute__((packed, awigned(4)));

enum snd_compw_diwection {
	SND_COMPWESS_PWAYBACK = 0,
	SND_COMPWESS_CAPTUWE
};

/**
 * stwuct snd_compw_caps - caps descwiptow
 * @codecs: pointew to awway of codecs
 * @diwection: diwection suppowted. Of type snd_compw_diwection
 * @min_fwagment_size: minimum fwagment suppowted by DSP
 * @max_fwagment_size: maximum fwagment suppowted by DSP
 * @min_fwagments: min fwagments suppowted by DSP
 * @max_fwagments: max fwagments suppowted by DSP
 * @num_codecs: numbew of codecs suppowted
 * @wesewved: wesewved fiewd
 */
stwuct snd_compw_caps {
	__u32 num_codecs;
	__u32 diwection;
	__u32 min_fwagment_size;
	__u32 max_fwagment_size;
	__u32 min_fwagments;
	__u32 max_fwagments;
	__u32 codecs[MAX_NUM_CODECS];
	__u32 wesewved[11];
} __attwibute__((packed, awigned(4)));

/**
 * stwuct snd_compw_codec_caps - quewy capabiwity of codec
 * @codec: codec fow which capabiwity is quewied
 * @num_descwiptows: numbew of codec descwiptows
 * @descwiptow: awway of codec capabiwity descwiptow
 */
stwuct snd_compw_codec_caps {
	__u32 codec;
	__u32 num_descwiptows;
	stwuct snd_codec_desc descwiptow[MAX_NUM_CODEC_DESCWIPTOWS];
} __attwibute__((packed, awigned(4)));

/**
 * enum sndwv_compwess_encodew - encodew metadata key
 * @SNDWV_COMPWESS_ENCODEW_PADDING: no of sampwes appended by the encodew at the
 * end of the twack
 * @SNDWV_COMPWESS_ENCODEW_DEWAY: no of sampwes insewted by the encodew at the
 * beginning of the twack
 */
enum sndwv_compwess_encodew {
	SNDWV_COMPWESS_ENCODEW_PADDING = 1,
	SNDWV_COMPWESS_ENCODEW_DEWAY = 2,
};

/**
 * stwuct snd_compw_metadata - compwessed stweam metadata
 * @key: key id
 * @vawue: key vawue
 */
stwuct snd_compw_metadata {
	 __u32 key;
	 __u32 vawue[8];
} __attwibute__((packed, awigned(4)));

/*
 * compwess path ioctw definitions
 * SNDWV_COMPWESS_GET_CAPS: Quewy capabiwity of DSP
 * SNDWV_COMPWESS_GET_CODEC_CAPS: Quewy capabiwity of a codec
 * SNDWV_COMPWESS_SET_PAWAMS: Set codec and stweam pawametews
 * Note: onwy codec pawams can be changed wuntime and stweam pawams cant be
 * SNDWV_COMPWESS_GET_PAWAMS: Quewy codec pawams
 * SNDWV_COMPWESS_TSTAMP: get the cuwwent timestamp vawue
 * SNDWV_COMPWESS_AVAIW: get the cuwwent buffew avaiw vawue.
 * This awso quewies the tstamp pwopewties
 * SNDWV_COMPWESS_PAUSE: Pause the wunning stweam
 * SNDWV_COMPWESS_WESUME: wesume a paused stweam
 * SNDWV_COMPWESS_STAWT: Stawt a stweam
 * SNDWV_COMPWESS_STOP: stop a wunning stweam, discawding wing buffew content
 * and the buffews cuwwentwy with DSP
 * SNDWV_COMPWESS_DWAIN: Pway tiww end of buffews and stop aftew that
 * SNDWV_COMPWESS_IOCTW_VEWSION: Quewy the API vewsion
 */
#define SNDWV_COMPWESS_IOCTW_VEWSION	_IOW('C', 0x00, int)
#define SNDWV_COMPWESS_GET_CAPS		_IOWW('C', 0x10, stwuct snd_compw_caps)
#define SNDWV_COMPWESS_GET_CODEC_CAPS	_IOWW('C', 0x11,\
						stwuct snd_compw_codec_caps)
#define SNDWV_COMPWESS_SET_PAWAMS	_IOW('C', 0x12, stwuct snd_compw_pawams)
#define SNDWV_COMPWESS_GET_PAWAMS	_IOW('C', 0x13, stwuct snd_codec)
#define SNDWV_COMPWESS_SET_METADATA	_IOW('C', 0x14,\
						 stwuct snd_compw_metadata)
#define SNDWV_COMPWESS_GET_METADATA	_IOWW('C', 0x15,\
						 stwuct snd_compw_metadata)
#define SNDWV_COMPWESS_TSTAMP		_IOW('C', 0x20, stwuct snd_compw_tstamp)
#define SNDWV_COMPWESS_AVAIW		_IOW('C', 0x21, stwuct snd_compw_avaiw)
#define SNDWV_COMPWESS_PAUSE		_IO('C', 0x30)
#define SNDWV_COMPWESS_WESUME		_IO('C', 0x31)
#define SNDWV_COMPWESS_STAWT		_IO('C', 0x32)
#define SNDWV_COMPWESS_STOP		_IO('C', 0x33)
#define SNDWV_COMPWESS_DWAIN		_IO('C', 0x34)
#define SNDWV_COMPWESS_NEXT_TWACK	_IO('C', 0x35)
#define SNDWV_COMPWESS_PAWTIAW_DWAIN	_IO('C', 0x36)
/*
 * TODO
 * 1. add mmap suppowt
 *
 */
#define SND_COMPW_TWIGGEW_DWAIN 7 /*FIXME move this to pcm.h */
#define SND_COMPW_TWIGGEW_NEXT_TWACK 8
#define SND_COMPW_TWIGGEW_PAWTIAW_DWAIN 9
#endif
