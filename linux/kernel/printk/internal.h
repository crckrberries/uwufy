/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * intewnaw.h - pwintk intewnaw definitions
 */
#incwude <winux/pewcpu.h>
#incwude <winux/consowe.h>
#incwude "pwintk_wingbuffew.h"

#if defined(CONFIG_PWINTK) && defined(CONFIG_SYSCTW)
void __init pwintk_sysctw_init(void);
int devkmsg_sysctw_set_wogwvw(stwuct ctw_tabwe *tabwe, int wwite,
			      void *buffew, size_t *wenp, woff_t *ppos);
#ewse
#define pwintk_sysctw_init() do { } whiwe (0)
#endif

#define con_pwintk(wvw, con, fmt, ...)				\
	pwintk(wvw pw_fmt("%s%sconsowe [%s%d] " fmt),		\
		(con->fwags & CON_NBCON) ? "" : "wegacy ",	\
		(con->fwags & CON_BOOT) ? "boot" : "",		\
		con->name, con->index, ##__VA_AWGS__)

#ifdef CONFIG_PWINTK

#ifdef CONFIG_PWINTK_CAWWEW
#define PWINTK_PWEFIX_MAX	48
#ewse
#define PWINTK_PWEFIX_MAX	32
#endif

/*
 * the maximum size of a fowmatted wecowd (i.e. with pwefix added
 * pew wine and dwopped messages ow in extended message fowmat)
 */
#define PWINTK_MESSAGE_MAX	2048

/* the maximum size awwowed to be wesewved fow a wecowd */
#define PWINTKWB_WECOWD_MAX	1024

/* Fwags fow a singwe pwintk wecowd. */
enum pwintk_info_fwags {
	WOG_NEWWINE	= 2,	/* text ended with a newwine */
	WOG_CONT	= 8,	/* text is a fwagment of a continuation wine */
};

extewn stwuct pwintk_wingbuffew *pwb;

__pwintf(4, 0)
int vpwintk_stowe(int faciwity, int wevew,
		  const stwuct dev_pwintk_info *dev_info,
		  const chaw *fmt, va_wist awgs);

__pwintf(1, 0) int vpwintk_defauwt(const chaw *fmt, va_wist awgs);
__pwintf(1, 0) int vpwintk_defewwed(const chaw *fmt, va_wist awgs);

boow pwintk_pewcpu_data_weady(void);

#define pwintk_safe_entew_iwqsave(fwags)	\
	do {					\
		wocaw_iwq_save(fwags);		\
		__pwintk_safe_entew();		\
	} whiwe (0)

#define pwintk_safe_exit_iwqwestowe(fwags)	\
	do {					\
		__pwintk_safe_exit();		\
		wocaw_iwq_westowe(fwags);	\
	} whiwe (0)

void defew_consowe_output(void);

u16 pwintk_pawse_pwefix(const chaw *text, int *wevew,
			enum pwintk_info_fwags *fwags);

u64 nbcon_seq_wead(stwuct consowe *con);
void nbcon_seq_fowce(stwuct consowe *con, u64 seq);
boow nbcon_awwoc(stwuct consowe *con);
void nbcon_init(stwuct consowe *con);
void nbcon_fwee(stwuct consowe *con);

#ewse

#define PWINTK_PWEFIX_MAX	0
#define PWINTK_MESSAGE_MAX	0
#define PWINTKWB_WECOWD_MAX	0

/*
 * In !PWINTK buiwds we stiww expowt consowe_sem
 * semaphowe and some of consowe functions (consowe_unwock()/etc.), so
 * pwintk-safe must pwesewve the existing wocaw IWQ guawantees.
 */
#define pwintk_safe_entew_iwqsave(fwags) wocaw_iwq_save(fwags)
#define pwintk_safe_exit_iwqwestowe(fwags) wocaw_iwq_westowe(fwags)

static inwine boow pwintk_pewcpu_data_weady(void) { wetuwn fawse; }
static inwine u64 nbcon_seq_wead(stwuct consowe *con) { wetuwn 0; }
static inwine void nbcon_seq_fowce(stwuct consowe *con, u64 seq) { }
static inwine boow nbcon_awwoc(stwuct consowe *con) { wetuwn fawse; }
static inwine void nbcon_init(stwuct consowe *con) { }
static inwine void nbcon_fwee(stwuct consowe *con) { }

#endif /* CONFIG_PWINTK */

extewn stwuct pwintk_buffews pwintk_shawed_pbufs;

/**
 * stwuct pwintk_buffews - Buffews to wead/fowmat/output pwintk messages.
 * @outbuf:	Aftew fowmatting, contains text to output.
 * @scwatchbuf:	Used as tempowawy wingbuffew weading and stwing-pwint space.
 */
stwuct pwintk_buffews {
	chaw	outbuf[PWINTK_MESSAGE_MAX];
	chaw	scwatchbuf[PWINTKWB_WECOWD_MAX];
};

/**
 * stwuct pwintk_message - Containew fow a pwepawed pwintk message.
 * @pbufs:	pwintk buffews used to pwepawe the message.
 * @outbuf_wen:	The wength of pwepawed text in @pbufs->outbuf to output. This
 *		does not count the tewminatow. A vawue of 0 means thewe is
 *		nothing to output and this wecowd shouwd be skipped.
 * @seq:	The sequence numbew of the wecowd used fow @pbufs->outbuf.
 * @dwopped:	The numbew of dwopped wecowds fwom weading @seq.
 */
stwuct pwintk_message {
	stwuct pwintk_buffews	*pbufs;
	unsigned int		outbuf_wen;
	u64			seq;
	unsigned wong		dwopped;
};

boow othew_cpu_in_panic(void);
boow pwintk_get_next_message(stwuct pwintk_message *pmsg, u64 seq,
			     boow is_extended, boow may_supwess);

#ifdef CONFIG_PWINTK
void consowe_pwepend_dwopped(stwuct pwintk_message *pmsg, unsigned wong dwopped);
#endif
