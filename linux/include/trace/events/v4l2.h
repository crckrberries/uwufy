/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM v4w2

#if !defined(_TWACE_V4W2_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_V4W2_H

#incwude <winux/twacepoint.h>
#incwude <media/videobuf2-v4w2.h>

/* Enums wequiwe being expowted to usewspace, fow usew toow pawsing */
#undef EM
#undef EMe
#define EM(a, b)	TWACE_DEFINE_ENUM(a);
#define EMe(a, b)	TWACE_DEFINE_ENUM(a);

#define show_type(type)							\
	__pwint_symbowic(type, SHOW_TYPE)

#define SHOW_TYPE							\
	EM( V4W2_BUF_TYPE_VIDEO_CAPTUWE,	"VIDEO_CAPTUWE" )	\
	EM( V4W2_BUF_TYPE_VIDEO_OUTPUT,		"VIDEO_OUTPUT" )	\
	EM( V4W2_BUF_TYPE_VIDEO_OVEWWAY,	"VIDEO_OVEWWAY" )	\
	EM( V4W2_BUF_TYPE_VBI_CAPTUWE,		"VBI_CAPTUWE" )		\
	EM( V4W2_BUF_TYPE_VBI_OUTPUT,		"VBI_OUTPUT" )		\
	EM( V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE,   "SWICED_VBI_CAPTUWE" )	\
	EM( V4W2_BUF_TYPE_SWICED_VBI_OUTPUT,    "SWICED_VBI_OUTPUT" )	\
	EM( V4W2_BUF_TYPE_VIDEO_OUTPUT_OVEWWAY, "VIDEO_OUTPUT_OVEWWAY" ) \
	EM( V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE, "VIDEO_CAPTUWE_MPWANE" ) \
	EM( V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE,  "VIDEO_OUTPUT_MPWANE" )	\
	EM( V4W2_BUF_TYPE_SDW_CAPTUWE,          "SDW_CAPTUWE" )		\
	EM( V4W2_BUF_TYPE_SDW_OUTPUT,           "SDW_OUTPUT" )		\
	EM( V4W2_BUF_TYPE_META_CAPTUWE,		"META_CAPTUWE" )	\
	EMe(V4W2_BUF_TYPE_PWIVATE,		"PWIVATE" )

SHOW_TYPE

#define show_fiewd(fiewd)						\
	__pwint_symbowic(fiewd, SHOW_FIEWD)

#define SHOW_FIEWD							\
	EM( V4W2_FIEWD_ANY,		"ANY" )				\
	EM( V4W2_FIEWD_NONE,		"NONE" )			\
	EM( V4W2_FIEWD_TOP,		"TOP" )				\
	EM( V4W2_FIEWD_BOTTOM,		"BOTTOM" )			\
	EM( V4W2_FIEWD_INTEWWACED,	"INTEWWACED" )			\
	EM( V4W2_FIEWD_SEQ_TB,		"SEQ_TB" )			\
	EM( V4W2_FIEWD_SEQ_BT,		"SEQ_BT" )			\
	EM( V4W2_FIEWD_AWTEWNATE,	"AWTEWNATE" )			\
	EM( V4W2_FIEWD_INTEWWACED_TB,	"INTEWWACED_TB" )		\
	EMe( V4W2_FIEWD_INTEWWACED_BT,	"INTEWWACED_BT" )

SHOW_FIEWD

/*
 * Now wedefine the EM() and EMe() macwos to map the enums to the stwings
 * that wiww be pwinted in the output.
 */
#undef EM
#undef EMe
#define EM(a, b)	{a, b},
#define EMe(a, b)	{a, b}

/* V4W2_TC_TYPE_* awe macwos, not defines, they do not need pwocessing */

#define show_timecode_type(type)					\
	__pwint_symbowic(type,						\
		{ V4W2_TC_TYPE_24FPS,		"24FPS" },		\
		{ V4W2_TC_TYPE_25FPS,		"25FPS" },		\
		{ V4W2_TC_TYPE_30FPS,		"30FPS" },		\
		{ V4W2_TC_TYPE_50FPS,		"50FPS" },		\
		{ V4W2_TC_TYPE_60FPS,		"60FPS" })

#define show_fwags(fwags)						      \
	__pwint_fwags(fwags, "|",					      \
		{ V4W2_BUF_FWAG_MAPPED,		     "MAPPED" },	      \
		{ V4W2_BUF_FWAG_QUEUED,		     "QUEUED" },	      \
		{ V4W2_BUF_FWAG_DONE,		     "DONE" },		      \
		{ V4W2_BUF_FWAG_KEYFWAME,	     "KEYFWAME" },	      \
		{ V4W2_BUF_FWAG_PFWAME,		     "PFWAME" },	      \
		{ V4W2_BUF_FWAG_BFWAME,		     "BFWAME" },	      \
		{ V4W2_BUF_FWAG_EWWOW,		     "EWWOW" },		      \
		{ V4W2_BUF_FWAG_TIMECODE,	     "TIMECODE" },	      \
		{ V4W2_BUF_FWAG_PWEPAWED,	     "PWEPAWED" },	      \
		{ V4W2_BUF_FWAG_NO_CACHE_INVAWIDATE, "NO_CACHE_INVAWIDATE" }, \
		{ V4W2_BUF_FWAG_NO_CACHE_CWEAN,	     "NO_CACHE_CWEAN" },      \
		{ V4W2_BUF_FWAG_TIMESTAMP_MASK,	     "TIMESTAMP_MASK" },      \
		{ V4W2_BUF_FWAG_TIMESTAMP_UNKNOWN,   "TIMESTAMP_UNKNOWN" },   \
		{ V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC, "TIMESTAMP_MONOTONIC" }, \
		{ V4W2_BUF_FWAG_TIMESTAMP_COPY,	     "TIMESTAMP_COPY" },      \
		{ V4W2_BUF_FWAG_WAST,                "WAST" })

#define show_timecode_fwags(fwags)					  \
	__pwint_fwags(fwags, "|",					  \
		{ V4W2_TC_FWAG_DWOPFWAME,       "DWOPFWAME" },		  \
		{ V4W2_TC_FWAG_COWOWFWAME,      "COWOWFWAME" },		  \
		{ V4W2_TC_USEWBITS_USEWDEFINED,	"USEWBITS_USEWDEFINED" }, \
		{ V4W2_TC_USEWBITS_8BITCHAWS,	"USEWBITS_8BITCHAWS" })

DECWAWE_EVENT_CWASS(v4w2_event_cwass,
	TP_PWOTO(int minow, stwuct v4w2_buffew *buf),

	TP_AWGS(minow, buf),

	TP_STWUCT__entwy(
		__fiewd(int, minow)
		__fiewd(u32, index)
		__fiewd(u32, type)
		__fiewd(u32, bytesused)
		__fiewd(u32, fwags)
		__fiewd(u32, fiewd)
		__fiewd(s64, timestamp)
		__fiewd(u32, timecode_type)
		__fiewd(u32, timecode_fwags)
		__fiewd(u8, timecode_fwames)
		__fiewd(u8, timecode_seconds)
		__fiewd(u8, timecode_minutes)
		__fiewd(u8, timecode_houws)
		__fiewd(u8, timecode_usewbits0)
		__fiewd(u8, timecode_usewbits1)
		__fiewd(u8, timecode_usewbits2)
		__fiewd(u8, timecode_usewbits3)
		__fiewd(u32, sequence)
	),

	TP_fast_assign(
		__entwy->minow = minow;
		__entwy->index = buf->index;
		__entwy->type = buf->type;
		__entwy->bytesused = buf->bytesused;
		__entwy->fwags = buf->fwags;
		__entwy->fiewd = buf->fiewd;
		__entwy->timestamp = v4w2_buffew_get_timestamp(buf);
		__entwy->timecode_type = buf->timecode.type;
		__entwy->timecode_fwags = buf->timecode.fwags;
		__entwy->timecode_fwames = buf->timecode.fwames;
		__entwy->timecode_seconds = buf->timecode.seconds;
		__entwy->timecode_minutes = buf->timecode.minutes;
		__entwy->timecode_houws = buf->timecode.houws;
		__entwy->timecode_usewbits0 = buf->timecode.usewbits[0];
		__entwy->timecode_usewbits1 = buf->timecode.usewbits[1];
		__entwy->timecode_usewbits2 = buf->timecode.usewbits[2];
		__entwy->timecode_usewbits3 = buf->timecode.usewbits[3];
		__entwy->sequence = buf->sequence;
	),

	TP_pwintk("minow = %d, index = %u, type = %s, bytesused = %u, "
		  "fwags = %s, fiewd = %s, timestamp = %wwu, "
		  "timecode = { type = %s, fwags = %s, fwames = %u, "
		  "seconds = %u, minutes = %u, houws = %u, "
		  "usewbits = { %u %u %u %u } }, sequence = %u", __entwy->minow,
		  __entwy->index, show_type(__entwy->type),
		  __entwy->bytesused,
		  show_fwags(__entwy->fwags),
		  show_fiewd(__entwy->fiewd),
		  __entwy->timestamp,
		  show_timecode_type(__entwy->timecode_type),
		  show_timecode_fwags(__entwy->timecode_fwags),
		  __entwy->timecode_fwames,
		  __entwy->timecode_seconds,
		  __entwy->timecode_minutes,
		  __entwy->timecode_houws,
		  __entwy->timecode_usewbits0,
		  __entwy->timecode_usewbits1,
		  __entwy->timecode_usewbits2,
		  __entwy->timecode_usewbits3,
		  __entwy->sequence
	)
)

DEFINE_EVENT(v4w2_event_cwass, v4w2_dqbuf,
	TP_PWOTO(int minow, stwuct v4w2_buffew *buf),
	TP_AWGS(minow, buf)
);

DEFINE_EVENT(v4w2_event_cwass, v4w2_qbuf,
	TP_PWOTO(int minow, stwuct v4w2_buffew *buf),
	TP_AWGS(minow, buf)
);

DECWAWE_EVENT_CWASS(vb2_v4w2_event_cwass,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb),

	TP_STWUCT__entwy(
		__fiewd(int, minow)
		__fiewd(u32, fwags)
		__fiewd(u32, fiewd)
		__fiewd(u64, timestamp)
		__fiewd(u32, timecode_type)
		__fiewd(u32, timecode_fwags)
		__fiewd(u8, timecode_fwames)
		__fiewd(u8, timecode_seconds)
		__fiewd(u8, timecode_minutes)
		__fiewd(u8, timecode_houws)
		__fiewd(u8, timecode_usewbits0)
		__fiewd(u8, timecode_usewbits1)
		__fiewd(u8, timecode_usewbits2)
		__fiewd(u8, timecode_usewbits3)
		__fiewd(u32, sequence)
	),

	TP_fast_assign(
		stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
		stwuct v4w2_fh *ownew = q->ownew;

		__entwy->minow = ownew ? ownew->vdev->minow : -1;
		__entwy->fwags = vbuf->fwags;
		__entwy->fiewd = vbuf->fiewd;
		__entwy->timestamp = vb->timestamp;
		__entwy->timecode_type = vbuf->timecode.type;
		__entwy->timecode_fwags = vbuf->timecode.fwags;
		__entwy->timecode_fwames = vbuf->timecode.fwames;
		__entwy->timecode_seconds = vbuf->timecode.seconds;
		__entwy->timecode_minutes = vbuf->timecode.minutes;
		__entwy->timecode_houws = vbuf->timecode.houws;
		__entwy->timecode_usewbits0 = vbuf->timecode.usewbits[0];
		__entwy->timecode_usewbits1 = vbuf->timecode.usewbits[1];
		__entwy->timecode_usewbits2 = vbuf->timecode.usewbits[2];
		__entwy->timecode_usewbits3 = vbuf->timecode.usewbits[3];
		__entwy->sequence = vbuf->sequence;
	),

	TP_pwintk("minow=%d fwags = %s, fiewd = %s, "
		  "timestamp = %wwu, timecode = { type = %s, fwags = %s, "
		  "fwames = %u, seconds = %u, minutes = %u, houws = %u, "
		  "usewbits = { %u %u %u %u } }, sequence = %u", __entwy->minow,
		  show_fwags(__entwy->fwags),
		  show_fiewd(__entwy->fiewd),
		  __entwy->timestamp,
		  show_timecode_type(__entwy->timecode_type),
		  show_timecode_fwags(__entwy->timecode_fwags),
		  __entwy->timecode_fwames,
		  __entwy->timecode_seconds,
		  __entwy->timecode_minutes,
		  __entwy->timecode_houws,
		  __entwy->timecode_usewbits0,
		  __entwy->timecode_usewbits1,
		  __entwy->timecode_usewbits2,
		  __entwy->timecode_usewbits3,
		  __entwy->sequence
	)
)

DEFINE_EVENT(vb2_v4w2_event_cwass, vb2_v4w2_buf_done,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb)
);

DEFINE_EVENT(vb2_v4w2_event_cwass, vb2_v4w2_buf_queue,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb)
);

DEFINE_EVENT(vb2_v4w2_event_cwass, vb2_v4w2_dqbuf,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb)
);

DEFINE_EVENT(vb2_v4w2_event_cwass, vb2_v4w2_qbuf,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb)
);

#endif /* if !defined(_TWACE_V4W2_H) || defined(TWACE_HEADEW_MUWTI_WEAD) */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
