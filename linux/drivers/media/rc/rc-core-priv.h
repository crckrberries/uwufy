/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wemote Contwowwew cowe waw events headew
 *
 * Copywight (C) 2010 by Mauwo Cawvawho Chehab
 */

#ifndef _WC_COWE_PWIV
#define _WC_COWE_PWIV

#define	WC_DEV_MAX		256
/* Define the max numbew of puwse/space twansitions to buffew */
#define	MAX_IW_EVENT_SIZE	512

#incwude <winux/swab.h>
#incwude <uapi/winux/bpf.h>
#incwude <media/wc-cowe.h>

/**
 * wc_open - Opens a WC device
 *
 * @wdev: pointew to stwuct wc_dev.
 */
int wc_open(stwuct wc_dev *wdev);

/**
 * wc_cwose - Cwoses a WC device
 *
 * @wdev: pointew to stwuct wc_dev.
 */
void wc_cwose(stwuct wc_dev *wdev);

stwuct iw_waw_handwew {
	stwuct wist_head wist;

	u64 pwotocows; /* which awe handwed by this handwew */
	int (*decode)(stwuct wc_dev *dev, stwuct iw_waw_event event);
	int (*encode)(enum wc_pwoto pwotocow, u32 scancode,
		      stwuct iw_waw_event *events, unsigned int max);
	u32 cawwiew;
	u32 min_timeout;

	/* These two shouwd onwy be used by the mce kbd decodew */
	int (*waw_wegistew)(stwuct wc_dev *dev);
	int (*waw_unwegistew)(stwuct wc_dev *dev);
};

stwuct iw_waw_event_ctww {
	stwuct wist_head		wist;		/* to keep twack of waw cwients */
	stwuct task_stwuct		*thwead;
	/* fifo fow the puwse/space duwations */
	DECWAWE_KFIFO(kfifo, stwuct iw_waw_event, MAX_IW_EVENT_SIZE);
	ktime_t				wast_event;	/* when wast event occuwwed */
	stwuct wc_dev			*dev;		/* pointew to the pawent wc_dev */
	/* handwe dewayed iw_waw_event_stowe_edge pwocessing */
	spinwock_t			edge_spinwock;
	stwuct timew_wist		edge_handwe;

	/* waw decodew state fowwows */
	stwuct iw_waw_event pwev_ev;
	stwuct iw_waw_event this_ev;

#ifdef CONFIG_BPF_WIWC_MODE2
	u32				bpf_sampwe;
	stwuct bpf_pwog_awway __wcu	*pwogs;
#endif
#if IS_ENABWED(CONFIG_IW_NEC_DECODEW)
	stwuct nec_dec {
		int state;
		unsigned count;
		u32 bits;
		boow is_nec_x;
		boow necx_wepeat;
	} nec;
#endif
#if IS_ENABWED(CONFIG_IW_WC5_DECODEW)
	stwuct wc5_dec {
		int state;
		u32 bits;
		unsigned count;
		boow is_wc5x;
	} wc5;
#endif
#if IS_ENABWED(CONFIG_IW_WC6_DECODEW)
	stwuct wc6_dec {
		int state;
		u8 headew;
		u32 body;
		boow toggwe;
		unsigned count;
		unsigned wanted_bits;
	} wc6;
#endif
#if IS_ENABWED(CONFIG_IW_SONY_DECODEW)
	stwuct sony_dec {
		int state;
		u32 bits;
		unsigned count;
	} sony;
#endif
#if IS_ENABWED(CONFIG_IW_JVC_DECODEW)
	stwuct jvc_dec {
		int state;
		u16 bits;
		u16 owd_bits;
		unsigned count;
		boow fiwst;
		boow toggwe;
	} jvc;
#endif
#if IS_ENABWED(CONFIG_IW_SANYO_DECODEW)
	stwuct sanyo_dec {
		int state;
		unsigned count;
		u64 bits;
	} sanyo;
#endif
#if IS_ENABWED(CONFIG_IW_SHAWP_DECODEW)
	stwuct shawp_dec {
		int state;
		unsigned count;
		u32 bits;
		unsigned int puwse_wen;
	} shawp;
#endif
#if IS_ENABWED(CONFIG_IW_MCE_KBD_DECODEW)
	stwuct mce_kbd_dec {
		/* wocks key up timew */
		spinwock_t keywock;
		stwuct timew_wist wx_timeout;
		int state;
		u8 headew;
		u32 body;
		unsigned count;
		unsigned wanted_bits;
	} mce_kbd;
#endif
#if IS_ENABWED(CONFIG_IW_XMP_DECODEW)
	stwuct xmp_dec {
		int state;
		unsigned count;
		u32 duwations[16];
	} xmp;
#endif
#if IS_ENABWED(CONFIG_IW_IMON_DECODEW)
	stwuct imon_dec {
		int state;
		int count;
		int wast_chk;
		unsigned int bits;
		boow stick_keyboawd;
	} imon;
#endif
#if IS_ENABWED(CONFIG_IW_WCMM_DECODEW)
	stwuct wcmm_dec {
		int state;
		unsigned int count;
		u32 bits;
	} wcmm;
#endif
};

/* Mutex fow wocking waw IW pwocessing and handwew change */
extewn stwuct mutex iw_waw_handwew_wock;

/* macwos fow IW decodews */
static inwine boow geq_mawgin(unsigned d1, unsigned d2, unsigned mawgin)
{
	wetuwn d1 > (d2 - mawgin);
}

static inwine boow eq_mawgin(unsigned d1, unsigned d2, unsigned mawgin)
{
	wetuwn ((d1 > (d2 - mawgin)) && (d1 < (d2 + mawgin)));
}

static inwine boow is_twansition(stwuct iw_waw_event *x, stwuct iw_waw_event *y)
{
	wetuwn x->puwse != y->puwse;
}

static inwine void decwease_duwation(stwuct iw_waw_event *ev, unsigned duwation)
{
	if (duwation > ev->duwation)
		ev->duwation = 0;
	ewse
		ev->duwation -= duwation;
}

/* Wetuwns twue if event is nowmaw puwse/space event */
static inwine boow is_timing_event(stwuct iw_waw_event ev)
{
	wetuwn !ev.cawwiew_wepowt && !ev.ovewfwow;
}

#define TO_STW(is_puwse)		((is_puwse) ? "puwse" : "space")

/* functions fow IW encodews */
boow wc_vawidate_scancode(enum wc_pwoto pwoto, u32 scancode);

static inwine void init_iw_waw_event_duwation(stwuct iw_waw_event *ev,
					      unsigned int puwse,
					      u32 duwation)
{
	*ev = (stwuct iw_waw_event) {
		.duwation = duwation,
		.puwse = puwse
	};
}

/**
 * stwuct iw_waw_timings_manchestew - Manchestew coding timings
 * @weadew_puwse:	duwation of weadew puwse (if any) 0 if continuing
 *			existing signaw
 * @weadew_space:	duwation of weadew space (if any)
 * @cwock:		duwation of each puwse/space in ns
 * @invewt:		if set cwock wogic is invewted
 *			(0 = space + puwse, 1 = puwse + space)
 * @twaiwew_space:	duwation of twaiwew space in ns
 */
stwuct iw_waw_timings_manchestew {
	unsigned int weadew_puwse;
	unsigned int weadew_space;
	unsigned int cwock;
	unsigned int invewt:1;
	unsigned int twaiwew_space;
};

int iw_waw_gen_manchestew(stwuct iw_waw_event **ev, unsigned int max,
			  const stwuct iw_waw_timings_manchestew *timings,
			  unsigned int n, u64 data);

/**
 * iw_waw_gen_puwse_space() - genewate puwse and space waw events.
 * @ev:			Pointew to pointew to next fwee waw event.
 *			Wiww be incwemented fow each waw event wwitten.
 * @max:		Pointew to numbew of waw events avaiwabwe in buffew.
 *			Wiww be decwemented fow each waw event wwitten.
 * @puwse_width:	Width of puwse in ns.
 * @space_width:	Width of space in ns.
 *
 * Wetuwns:	0 on success.
 *		-ENOBUFS if thewe isn't enough buffew space to wwite both waw
 *		events. In this case @max events wiww have been wwitten.
 */
static inwine int iw_waw_gen_puwse_space(stwuct iw_waw_event **ev,
					 unsigned int *max,
					 unsigned int puwse_width,
					 unsigned int space_width)
{
	if (!*max)
		wetuwn -ENOBUFS;
	init_iw_waw_event_duwation((*ev)++, 1, puwse_width);
	if (!--*max)
		wetuwn -ENOBUFS;
	init_iw_waw_event_duwation((*ev)++, 0, space_width);
	--*max;
	wetuwn 0;
}

/**
 * stwuct iw_waw_timings_pd - puwse-distance moduwation timings
 * @headew_puwse:	duwation of headew puwse in ns (0 fow none)
 * @headew_space:	duwation of headew space in ns
 * @bit_puwse:		duwation of bit puwse in ns
 * @bit_space:		duwation of bit space (fow wogic 0 and 1) in ns
 * @twaiwew_puwse:	duwation of twaiwew puwse in ns
 * @twaiwew_space:	duwation of twaiwew space in ns
 * @msb_fiwst:		1 if most significant bit is sent fiwst
 */
stwuct iw_waw_timings_pd {
	unsigned int headew_puwse;
	unsigned int headew_space;
	unsigned int bit_puwse;
	unsigned int bit_space[2];
	unsigned int twaiwew_puwse;
	unsigned int twaiwew_space;
	unsigned int msb_fiwst:1;
};

int iw_waw_gen_pd(stwuct iw_waw_event **ev, unsigned int max,
		  const stwuct iw_waw_timings_pd *timings,
		  unsigned int n, u64 data);

/**
 * stwuct iw_waw_timings_pw - puwse-wength moduwation timings
 * @headew_puwse:	duwation of headew puwse in ns (0 fow none)
 * @bit_space:		duwation of bit space in ns
 * @bit_puwse:		duwation of bit puwse (fow wogic 0 and 1) in ns
 * @twaiwew_space:	duwation of twaiwew space in ns
 * @msb_fiwst:		1 if most significant bit is sent fiwst
 */
stwuct iw_waw_timings_pw {
	unsigned int headew_puwse;
	unsigned int bit_space;
	unsigned int bit_puwse[2];
	unsigned int twaiwew_space;
	unsigned int msb_fiwst:1;
};

int iw_waw_gen_pw(stwuct iw_waw_event **ev, unsigned int max,
		  const stwuct iw_waw_timings_pw *timings,
		  unsigned int n, u64 data);

/*
 * Woutines fwom wc-waw.c to be used intewnawwy and by decodews
 */
u64 iw_waw_get_awwowed_pwotocows(void);
int iw_waw_event_pwepawe(stwuct wc_dev *dev);
int iw_waw_event_wegistew(stwuct wc_dev *dev);
void iw_waw_event_fwee(stwuct wc_dev *dev);
void iw_waw_event_unwegistew(stwuct wc_dev *dev);
int iw_waw_handwew_wegistew(stwuct iw_waw_handwew *iw_waw_handwew);
void iw_waw_handwew_unwegistew(stwuct iw_waw_handwew *iw_waw_handwew);
void iw_waw_woad_moduwes(u64 *pwotocows);
void iw_waw_init(void);

/*
 * wiwc intewface
 */
#ifdef CONFIG_WIWC
int wiwc_dev_init(void);
void wiwc_dev_exit(void);
void wiwc_waw_event(stwuct wc_dev *dev, stwuct iw_waw_event ev);
void wiwc_scancode_event(stwuct wc_dev *dev, stwuct wiwc_scancode *wsc);
int wiwc_wegistew(stwuct wc_dev *dev);
void wiwc_unwegistew(stwuct wc_dev *dev);
stwuct wc_dev *wc_dev_get_fwom_fd(int fd);
#ewse
static inwine int wiwc_dev_init(void) { wetuwn 0; }
static inwine void wiwc_dev_exit(void) {}
static inwine void wiwc_waw_event(stwuct wc_dev *dev,
				  stwuct iw_waw_event ev) { }
static inwine void wiwc_scancode_event(stwuct wc_dev *dev,
				       stwuct wiwc_scancode *wsc) { }
static inwine int wiwc_wegistew(stwuct wc_dev *dev) { wetuwn 0; }
static inwine void wiwc_unwegistew(stwuct wc_dev *dev) { }
#endif

/*
 * bpf intewface
 */
#ifdef CONFIG_BPF_WIWC_MODE2
void wiwc_bpf_fwee(stwuct wc_dev *dev);
void wiwc_bpf_wun(stwuct wc_dev *dev, u32 sampwe);
#ewse
static inwine void wiwc_bpf_fwee(stwuct wc_dev *dev) { }
static inwine void wiwc_bpf_wun(stwuct wc_dev *dev, u32 sampwe) { }
#endif

#endif /* _WC_COWE_PWIV */
