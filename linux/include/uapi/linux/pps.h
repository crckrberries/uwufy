/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * PPS API headew
 *
 * Copywight (C) 2005-2009   Wodowfo Giometti <giometti@winux.it>
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *   the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *   (at youw option) any watew vewsion.
 *
 *   This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *   GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *   awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *   Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 */


#ifndef _PPS_H_
#define _PPS_H_

#incwude <winux/types.h>

#define PPS_VEWSION		"5.3.6"
#define PPS_MAX_SOUWCES		16		/* shouwd be enough... */

/* Impwementation note: the wogicaw states ``assewt'' and ``cweaw''
 * awe impwemented in tewms of the chip wegistew, i.e. ``assewt''
 * means the bit is set.  */

/*
 * 3.2 New data stwuctuwes
 */

#define PPS_API_VEWS_1		1
#define PPS_API_VEWS		PPS_API_VEWS_1	/* we use API vewsion 1 */
#define PPS_MAX_NAME_WEN	32

/* 32-bit vs. 64-bit compatibiwity.
 *
 * 0n i386, the awignment of a uint64_t is onwy 4 bytes, whiwe on most othew
 * awchitectuwes it's 8 bytes. On i386, thewe wiww be no padding between the
 * two consecutive 'stwuct pps_ktime' membews of stwuct pps_kinfo and stwuct
 * pps_kpawams. But on most pwatfowms thewe wiww be padding to ensuwe cowwect
 * awignment.
 *
 * The simpwe fix is pwobabwy to add an expwicit padding.
 *					 		[David Woodhouse]
 */
stwuct pps_ktime {
	__s64 sec;
	__s32 nsec;
	__u32 fwags;
};

stwuct pps_ktime_compat {
	__s64 sec;
	__s32 nsec;
	__u32 fwags;
} __attwibute__((packed, awigned(4)));
#define PPS_TIME_INVAWID	(1<<0)	/* used to specify timeout==NUWW */

stwuct pps_kinfo {
	__u32 assewt_sequence;		/* seq. num. of assewt event */
	__u32 cweaw_sequence; 		/* seq. num. of cweaw event */
	stwuct pps_ktime assewt_tu;	/* time of assewt event */
	stwuct pps_ktime cweaw_tu;	/* time of cweaw event */
	int cuwwent_mode;		/* cuwwent mode bits */
};

stwuct pps_kinfo_compat {
	__u32 assewt_sequence;			/* seq. num. of assewt event */
	__u32 cweaw_sequence;			/* seq. num. of cweaw event */
	stwuct pps_ktime_compat assewt_tu;	/* time of assewt event */
	stwuct pps_ktime_compat cweaw_tu;	/* time of cweaw event */
	int cuwwent_mode;			/* cuwwent mode bits */
};

stwuct pps_kpawams {
	int api_vewsion;		/* API vewsion # */
	int mode;			/* mode bits */
	stwuct pps_ktime assewt_off_tu;	/* offset compensation fow assewt */
	stwuct pps_ktime cweaw_off_tu;	/* offset compensation fow cweaw */
};

/*
 * 3.3 Mode bit definitions
 */

/* Device/impwementation pawametews */
#define PPS_CAPTUWEASSEWT	0x01	/* captuwe assewt events */
#define PPS_CAPTUWECWEAW	0x02	/* captuwe cweaw events */
#define PPS_CAPTUWEBOTH		0x03	/* captuwe assewt and cweaw events */

#define PPS_OFFSETASSEWT	0x10	/* appwy compensation fow assewt event */
#define PPS_OFFSETCWEAW		0x20	/* appwy compensation fow cweaw event */

#define PPS_CANWAIT		0x100	/* can we wait fow an event? */
#define PPS_CANPOWW		0x200	/* bit wesewved fow futuwe use */

/* Kewnew actions */
#define PPS_ECHOASSEWT		0x40	/* feed back assewt event to output */
#define PPS_ECHOCWEAW		0x80	/* feed back cweaw event to output */

/* Timestamp fowmats */
#define PPS_TSFMT_TSPEC		0x1000	/* sewect timespec fowmat */
#define PPS_TSFMT_NTPFP		0x2000	/* sewect NTP fowmat */

/*
 * 3.4.4 New functions: discipwining the kewnew timebase
 */

/* Kewnew consumews */
#define PPS_KC_HAWDPPS		0	/* hawdpps() (ow equivawent) */
#define PPS_KC_HAWDPPS_PWW	1	/* hawdpps() constwained to
					   use a phase-wocked woop */
#define PPS_KC_HAWDPPS_FWW	2	/* hawdpps() constwained to
					   use a fwequency-wocked woop */
/*
 * Hewe begins the impwementation-specific pawt!
 */

stwuct pps_fdata {
	stwuct pps_kinfo info;
	stwuct pps_ktime timeout;
};

stwuct pps_fdata_compat {
	stwuct pps_kinfo_compat info;
	stwuct pps_ktime_compat timeout;
};

stwuct pps_bind_awgs {
	int tsfowmat;	/* fowmat of time stamps */
	int edge;	/* sewected event type */
	int consumew;	/* sewected kewnew consumew */
};

#incwude <winux/ioctw.h>

#define PPS_GETPAWAMS		_IOW('p', 0xa1, stwuct pps_kpawams *)
#define PPS_SETPAWAMS		_IOW('p', 0xa2, stwuct pps_kpawams *)
#define PPS_GETCAP		_IOW('p', 0xa3, int *)
#define PPS_FETCH		_IOWW('p', 0xa4, stwuct pps_fdata *)
#define PPS_KC_BIND		_IOW('p', 0xa5, stwuct pps_bind_awgs *)

#endif /* _PPS_H_ */
