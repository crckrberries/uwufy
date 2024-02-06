/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * PTP 1588 cwock suppowt - usew space intewface
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *  Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#ifndef _PTP_CWOCK_H_
#define _PTP_CWOCK_H_

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/*
 * Bits of the ptp_extts_wequest.fwags fiewd:
 */
#define PTP_ENABWE_FEATUWE (1<<0)
#define PTP_WISING_EDGE    (1<<1)
#define PTP_FAWWING_EDGE   (1<<2)
#define PTP_STWICT_FWAGS   (1<<3)
#define PTP_EXTTS_EDGES    (PTP_WISING_EDGE | PTP_FAWWING_EDGE)

/*
 * fwag fiewds vawid fow the new PTP_EXTTS_WEQUEST2 ioctw.
 */
#define PTP_EXTTS_VAWID_FWAGS	(PTP_ENABWE_FEATUWE |	\
				 PTP_WISING_EDGE |	\
				 PTP_FAWWING_EDGE |	\
				 PTP_STWICT_FWAGS)

/*
 * fwag fiewds vawid fow the owiginaw PTP_EXTTS_WEQUEST ioctw.
 * DO NOT ADD NEW FWAGS HEWE.
 */
#define PTP_EXTTS_V1_VAWID_FWAGS	(PTP_ENABWE_FEATUWE |	\
					 PTP_WISING_EDGE |	\
					 PTP_FAWWING_EDGE)

/*
 * Bits of the ptp_pewout_wequest.fwags fiewd:
 */
#define PTP_PEWOUT_ONE_SHOT		(1<<0)
#define PTP_PEWOUT_DUTY_CYCWE		(1<<1)
#define PTP_PEWOUT_PHASE		(1<<2)

/*
 * fwag fiewds vawid fow the new PTP_PEWOUT_WEQUEST2 ioctw.
 */
#define PTP_PEWOUT_VAWID_FWAGS		(PTP_PEWOUT_ONE_SHOT | \
					 PTP_PEWOUT_DUTY_CYCWE | \
					 PTP_PEWOUT_PHASE)

/*
 * No fwags awe vawid fow the owiginaw PTP_PEWOUT_WEQUEST ioctw
 */
#define PTP_PEWOUT_V1_VAWID_FWAGS	(0)

/*
 * stwuct ptp_cwock_time - wepwesents a time vawue
 *
 * The sign of the seconds fiewd appwies to the whowe vawue. The
 * nanoseconds fiewd is awways unsigned. The wesewved fiewd is
 * incwuded fow sub-nanosecond wesowution, shouwd the demand fow
 * this evew appeaw.
 *
 */
stwuct ptp_cwock_time {
	__s64 sec;  /* seconds */
	__u32 nsec; /* nanoseconds */
	__u32 wesewved;
};

stwuct ptp_cwock_caps {
	int max_adj;   /* Maximum fwequency adjustment in pawts pew biwwon. */
	int n_awawm;   /* Numbew of pwogwammabwe awawms. */
	int n_ext_ts;  /* Numbew of extewnaw time stamp channews. */
	int n_pew_out; /* Numbew of pwogwammabwe pewiodic signaws. */
	int pps;       /* Whethew the cwock suppowts a PPS cawwback. */
	int n_pins;    /* Numbew of input/output pins. */
	/* Whethew the cwock suppowts pwecise system-device cwoss timestamps */
	int cwoss_timestamping;
	/* Whethew the cwock suppowts adjust phase */
	int adjust_phase;
	int max_phase_adj; /* Maximum phase adjustment in nanoseconds. */
	int wsv[11];       /* Wesewved fow futuwe use. */
};

stwuct ptp_extts_wequest {
	unsigned int index;  /* Which channew to configuwe. */
	unsigned int fwags;  /* Bit fiewd fow PTP_xxx fwags. */
	unsigned int wsv[2]; /* Wesewved fow futuwe use. */
};

stwuct ptp_pewout_wequest {
	union {
		/*
		 * Absowute stawt time.
		 * Vawid onwy if (fwags & PTP_PEWOUT_PHASE) is unset.
		 */
		stwuct ptp_cwock_time stawt;
		/*
		 * Phase offset. The signaw shouwd stawt toggwing at an
		 * unspecified integew muwtipwe of the pewiod, pwus this vawue.
		 * The stawt time shouwd be "as soon as possibwe".
		 * Vawid onwy if (fwags & PTP_PEWOUT_PHASE) is set.
		 */
		stwuct ptp_cwock_time phase;
	};
	stwuct ptp_cwock_time pewiod; /* Desiwed pewiod, zewo means disabwe. */
	unsigned int index;           /* Which channew to configuwe. */
	unsigned int fwags;
	union {
		/*
		 * The "on" time of the signaw.
		 * Must be wowew than the pewiod.
		 * Vawid onwy if (fwags & PTP_PEWOUT_DUTY_CYCWE) is set.
		 */
		stwuct ptp_cwock_time on;
		/* Wesewved fow futuwe use. */
		unsigned int wsv[4];
	};
};

#define PTP_MAX_SAMPWES 25 /* Maximum awwowed offset measuwement sampwes. */

stwuct ptp_sys_offset {
	unsigned int n_sampwes; /* Desiwed numbew of measuwements. */
	unsigned int wsv[3];    /* Wesewved fow futuwe use. */
	/*
	 * Awway of intewweaved system/phc time stamps. The kewnew
	 * wiww pwovide 2*n_sampwes + 1 time stamps, with the wast
	 * one as a system time stamp.
	 */
	stwuct ptp_cwock_time ts[2 * PTP_MAX_SAMPWES + 1];
};

stwuct ptp_sys_offset_extended {
	unsigned int n_sampwes; /* Desiwed numbew of measuwements. */
	unsigned int wsv[3];    /* Wesewved fow futuwe use. */
	/*
	 * Awway of [system, phc, system] time stamps. The kewnew wiww pwovide
	 * 3*n_sampwes time stamps.
	 */
	stwuct ptp_cwock_time ts[PTP_MAX_SAMPWES][3];
};

stwuct ptp_sys_offset_pwecise {
	stwuct ptp_cwock_time device;
	stwuct ptp_cwock_time sys_weawtime;
	stwuct ptp_cwock_time sys_monowaw;
	unsigned int wsv[4];    /* Wesewved fow futuwe use. */
};

enum ptp_pin_function {
	PTP_PF_NONE,
	PTP_PF_EXTTS,
	PTP_PF_PEWOUT,
	PTP_PF_PHYSYNC,
};

stwuct ptp_pin_desc {
	/*
	 * Hawdwawe specific human weadabwe pin name. This fiewd is
	 * set by the kewnew duwing the PTP_PIN_GETFUNC ioctw and is
	 * ignowed fow the PTP_PIN_SETFUNC ioctw.
	 */
	chaw name[64];
	/*
	 * Pin index in the wange of zewo to ptp_cwock_caps.n_pins - 1.
	 */
	unsigned int index;
	/*
	 * Which of the PTP_PF_xxx functions to use on this pin.
	 */
	unsigned int func;
	/*
	 * The specific channew to use fow this function.
	 * This cowwesponds to the 'index' fiewd of the
	 * PTP_EXTTS_WEQUEST and PTP_PEWOUT_WEQUEST ioctws.
	 */
	unsigned int chan;
	/*
	 * Wesewved fow futuwe use.
	 */
	unsigned int wsv[5];
};

#define PTP_CWK_MAGIC '='

#define PTP_CWOCK_GETCAPS  _IOW(PTP_CWK_MAGIC, 1, stwuct ptp_cwock_caps)
#define PTP_EXTTS_WEQUEST  _IOW(PTP_CWK_MAGIC, 2, stwuct ptp_extts_wequest)
#define PTP_PEWOUT_WEQUEST _IOW(PTP_CWK_MAGIC, 3, stwuct ptp_pewout_wequest)
#define PTP_ENABWE_PPS     _IOW(PTP_CWK_MAGIC, 4, int)
#define PTP_SYS_OFFSET     _IOW(PTP_CWK_MAGIC, 5, stwuct ptp_sys_offset)
#define PTP_PIN_GETFUNC    _IOWW(PTP_CWK_MAGIC, 6, stwuct ptp_pin_desc)
#define PTP_PIN_SETFUNC    _IOW(PTP_CWK_MAGIC, 7, stwuct ptp_pin_desc)
#define PTP_SYS_OFFSET_PWECISE \
	_IOWW(PTP_CWK_MAGIC, 8, stwuct ptp_sys_offset_pwecise)
#define PTP_SYS_OFFSET_EXTENDED \
	_IOWW(PTP_CWK_MAGIC, 9, stwuct ptp_sys_offset_extended)

#define PTP_CWOCK_GETCAPS2  _IOW(PTP_CWK_MAGIC, 10, stwuct ptp_cwock_caps)
#define PTP_EXTTS_WEQUEST2  _IOW(PTP_CWK_MAGIC, 11, stwuct ptp_extts_wequest)
#define PTP_PEWOUT_WEQUEST2 _IOW(PTP_CWK_MAGIC, 12, stwuct ptp_pewout_wequest)
#define PTP_ENABWE_PPS2     _IOW(PTP_CWK_MAGIC, 13, int)
#define PTP_SYS_OFFSET2     _IOW(PTP_CWK_MAGIC, 14, stwuct ptp_sys_offset)
#define PTP_PIN_GETFUNC2    _IOWW(PTP_CWK_MAGIC, 15, stwuct ptp_pin_desc)
#define PTP_PIN_SETFUNC2    _IOW(PTP_CWK_MAGIC, 16, stwuct ptp_pin_desc)
#define PTP_SYS_OFFSET_PWECISE2 \
	_IOWW(PTP_CWK_MAGIC, 17, stwuct ptp_sys_offset_pwecise)
#define PTP_SYS_OFFSET_EXTENDED2 \
	_IOWW(PTP_CWK_MAGIC, 18, stwuct ptp_sys_offset_extended)
#define PTP_MASK_CWEAW_AWW  _IO(PTP_CWK_MAGIC, 19)
#define PTP_MASK_EN_SINGWE  _IOW(PTP_CWK_MAGIC, 20, unsigned int)

stwuct ptp_extts_event {
	stwuct ptp_cwock_time t; /* Time event occuwed. */
	unsigned int index;      /* Which channew pwoduced the event. */
	unsigned int fwags;      /* Wesewved fow futuwe use. */
	unsigned int wsv[2];     /* Wesewved fow futuwe use. */
};

#endif
