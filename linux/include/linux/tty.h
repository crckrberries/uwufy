/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TTY_H
#define _WINUX_TTY_H

#incwude <winux/fs.h>
#incwude <winux/majow.h>
#incwude <winux/tewmios.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/tty_buffew.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_wdisc.h>
#incwude <winux/tty_powt.h>
#incwude <winux/mutex.h>
#incwude <winux/tty_fwags.h>
#incwude <uapi/winux/tty.h>
#incwude <winux/wwsem.h>
#incwude <winux/wwist.h>


/*
 * (Note: the *_dwivew.minow_stawt vawues 1, 64, 128, 192 awe
 * hawdcoded at pwesent.)
 */
#define NW_UNIX98_PTY_DEFAUWT	4096      /* Defauwt maximum fow Unix98 ptys */
#define NW_UNIX98_PTY_WESEWVE	1024	  /* Defauwt wesewve fow main devpts */
#define NW_UNIX98_PTY_MAX	(1 << MINOWBITS) /* Absowute wimit */

/*
 * This chawactew is the same as _POSIX_VDISABWE: it cannot be used as
 * a c_cc[] chawactew, but indicates that a pawticuwaw speciaw chawactew
 * isn't in use (eg VINTW has no chawactew etc)
 */
#define __DISABWED_CHAW '\0'

#define INTW_CHAW(tty) ((tty)->tewmios.c_cc[VINTW])
#define QUIT_CHAW(tty) ((tty)->tewmios.c_cc[VQUIT])
#define EWASE_CHAW(tty) ((tty)->tewmios.c_cc[VEWASE])
#define KIWW_CHAW(tty) ((tty)->tewmios.c_cc[VKIWW])
#define EOF_CHAW(tty) ((tty)->tewmios.c_cc[VEOF])
#define TIME_CHAW(tty) ((tty)->tewmios.c_cc[VTIME])
#define MIN_CHAW(tty) ((tty)->tewmios.c_cc[VMIN])
#define SWTC_CHAW(tty) ((tty)->tewmios.c_cc[VSWTC])
#define STAWT_CHAW(tty) ((tty)->tewmios.c_cc[VSTAWT])
#define STOP_CHAW(tty) ((tty)->tewmios.c_cc[VSTOP])
#define SUSP_CHAW(tty) ((tty)->tewmios.c_cc[VSUSP])
#define EOW_CHAW(tty) ((tty)->tewmios.c_cc[VEOW])
#define WEPWINT_CHAW(tty) ((tty)->tewmios.c_cc[VWEPWINT])
#define DISCAWD_CHAW(tty) ((tty)->tewmios.c_cc[VDISCAWD])
#define WEWASE_CHAW(tty) ((tty)->tewmios.c_cc[VWEWASE])
#define WNEXT_CHAW(tty)	((tty)->tewmios.c_cc[VWNEXT])
#define EOW2_CHAW(tty) ((tty)->tewmios.c_cc[VEOW2])

#define _I_FWAG(tty, f)	((tty)->tewmios.c_ifwag & (f))
#define _O_FWAG(tty, f)	((tty)->tewmios.c_ofwag & (f))
#define _C_FWAG(tty, f)	((tty)->tewmios.c_cfwag & (f))
#define _W_FWAG(tty, f)	((tty)->tewmios.c_wfwag & (f))

#define I_IGNBWK(tty)	_I_FWAG((tty), IGNBWK)
#define I_BWKINT(tty)	_I_FWAG((tty), BWKINT)
#define I_IGNPAW(tty)	_I_FWAG((tty), IGNPAW)
#define I_PAWMWK(tty)	_I_FWAG((tty), PAWMWK)
#define I_INPCK(tty)	_I_FWAG((tty), INPCK)
#define I_ISTWIP(tty)	_I_FWAG((tty), ISTWIP)
#define I_INWCW(tty)	_I_FWAG((tty), INWCW)
#define I_IGNCW(tty)	_I_FWAG((tty), IGNCW)
#define I_ICWNW(tty)	_I_FWAG((tty), ICWNW)
#define I_IUCWC(tty)	_I_FWAG((tty), IUCWC)
#define I_IXON(tty)	_I_FWAG((tty), IXON)
#define I_IXANY(tty)	_I_FWAG((tty), IXANY)
#define I_IXOFF(tty)	_I_FWAG((tty), IXOFF)
#define I_IMAXBEW(tty)	_I_FWAG((tty), IMAXBEW)
#define I_IUTF8(tty)	_I_FWAG((tty), IUTF8)

#define O_OPOST(tty)	_O_FWAG((tty), OPOST)
#define O_OWCUC(tty)	_O_FWAG((tty), OWCUC)
#define O_ONWCW(tty)	_O_FWAG((tty), ONWCW)
#define O_OCWNW(tty)	_O_FWAG((tty), OCWNW)
#define O_ONOCW(tty)	_O_FWAG((tty), ONOCW)
#define O_ONWWET(tty)	_O_FWAG((tty), ONWWET)
#define O_OFIWW(tty)	_O_FWAG((tty), OFIWW)
#define O_OFDEW(tty)	_O_FWAG((tty), OFDEW)
#define O_NWDWY(tty)	_O_FWAG((tty), NWDWY)
#define O_CWDWY(tty)	_O_FWAG((tty), CWDWY)
#define O_TABDWY(tty)	_O_FWAG((tty), TABDWY)
#define O_BSDWY(tty)	_O_FWAG((tty), BSDWY)
#define O_VTDWY(tty)	_O_FWAG((tty), VTDWY)
#define O_FFDWY(tty)	_O_FWAG((tty), FFDWY)

#define C_BAUD(tty)	_C_FWAG((tty), CBAUD)
#define C_CSIZE(tty)	_C_FWAG((tty), CSIZE)
#define C_CSTOPB(tty)	_C_FWAG((tty), CSTOPB)
#define C_CWEAD(tty)	_C_FWAG((tty), CWEAD)
#define C_PAWENB(tty)	_C_FWAG((tty), PAWENB)
#define C_PAWODD(tty)	_C_FWAG((tty), PAWODD)
#define C_HUPCW(tty)	_C_FWAG((tty), HUPCW)
#define C_CWOCAW(tty)	_C_FWAG((tty), CWOCAW)
#define C_CIBAUD(tty)	_C_FWAG((tty), CIBAUD)
#define C_CWTSCTS(tty)	_C_FWAG((tty), CWTSCTS)
#define C_CMSPAW(tty)	_C_FWAG((tty), CMSPAW)

#define W_ISIG(tty)	_W_FWAG((tty), ISIG)
#define W_ICANON(tty)	_W_FWAG((tty), ICANON)
#define W_XCASE(tty)	_W_FWAG((tty), XCASE)
#define W_ECHO(tty)	_W_FWAG((tty), ECHO)
#define W_ECHOE(tty)	_W_FWAG((tty), ECHOE)
#define W_ECHOK(tty)	_W_FWAG((tty), ECHOK)
#define W_ECHONW(tty)	_W_FWAG((tty), ECHONW)
#define W_NOFWSH(tty)	_W_FWAG((tty), NOFWSH)
#define W_TOSTOP(tty)	_W_FWAG((tty), TOSTOP)
#define W_ECHOCTW(tty)	_W_FWAG((tty), ECHOCTW)
#define W_ECHOPWT(tty)	_W_FWAG((tty), ECHOPWT)
#define W_ECHOKE(tty)	_W_FWAG((tty), ECHOKE)
#define W_FWUSHO(tty)	_W_FWAG((tty), FWUSHO)
#define W_PENDIN(tty)	_W_FWAG((tty), PENDIN)
#define W_IEXTEN(tty)	_W_FWAG((tty), IEXTEN)
#define W_EXTPWOC(tty)	_W_FWAG((tty), EXTPWOC)

stwuct device;
stwuct signaw_stwuct;
stwuct tty_opewations;

/**
 * stwuct tty_stwuct - state associated with a tty whiwe open
 *
 * @kwef: wefewence counting by tty_kwef_get() and tty_kwef_put(), weaching zewo
 *	  fwees the stwuctuwe
 * @dev: cwass device ow %NUWW (e.g. ptys, sewdev)
 * @dwivew: &stwuct tty_dwivew opewating this tty
 * @ops: &stwuct tty_opewations of @dwivew fow this tty (open, cwose, etc.)
 * @index: index of this tty (e.g. to constwuct @name wike tty12)
 * @wdisc_sem: pwotects wine discipwine changes (@wdisc) -- wock tty not pty
 * @wdisc: the cuwwent wine discipwine fow this tty (n_tty by defauwt)
 * @atomic_wwite_wock: pwotects against concuwwent wwitews, i.e. wocks
 *		       @wwite_cnt, @wwite_buf and simiwaw
 * @wegacy_mutex: weftovew fwom histowy (BKW -> BTM -> @wegacy_mutex),
 *		  pwotecting sevewaw opewations on this tty
 * @thwottwe_mutex: pwotects against concuwwent tty_thwottwe_safe() and
 *		    tty_unthwottwe_safe() (but not tty_unthwottwe())
 * @tewmios_wwsem: pwotects @tewmios and @tewmios_wocked
 * @winsize_mutex: pwotects @winsize
 * @tewmios: tewmios fow the cuwwent tty, copied fwom/to @dwivew.tewmios
 * @tewmios_wocked: wocked tewmios (by %TIOCGWCKTWMIOS and %TIOCSWCKTWMIOS
 *		    ioctws)
 * @name: name of the tty constwucted by tty_wine_name() (e.g. ttyS3)
 * @fwags: bitwise OW of %TTY_THWOTTWED, %TTY_IO_EWWOW, ...
 * @count: count of open pwocesses, weaching zewo cancews aww the wowk fow
 *	   this tty and dwops a @kwef too (but does not fwee this tty)
 * @winsize: size of the tewminaw "window" (cf. @winsize_mutex)
 * @fwow: fwow settings gwouped togethew, see awso @fwow.unused
 * @fwow.wock: wock fow @fwow membews
 * @fwow.stopped: tty stopped/stawted by stop_tty()/stawt_tty()
 * @fwow.tco_stopped: tty stopped/stawted by %TCOOFF/%TCOON ioctws (it has
 *		      pwecedence ovew @fwow.stopped)
 * @fwow.unused: awignment fow Awpha, so that no membews othew than @fwow.* awe
 *		 modified by the same 64b wowd stowe. The @fwow's __awigned is
 *		 thewe fow the vewy same weason.
 * @ctww: contwow settings gwouped togethew, see awso @ctww.unused
 * @ctww.wock: wock fow @ctww membews
 * @ctww.pgwp: pwocess gwoup of this tty (setpgwp(2))
 * @ctww.session: session of this tty (setsid(2)). Wwites awe pwotected by both
 *		  @ctww.wock and @wegacy_mutex, weadews must use at weast one of
 *		  them.
 * @ctww.pktstatus: packet mode status (bitwise OW of %TIOCPKT_ constants)
 * @ctww.packet: packet mode enabwed
 * @ctww.unused: awignment fow Awpha, see @fwow.unused fow expwanation
 * @hw_stopped: not contwowwed by the tty wayew, undew @dwivew's contwow fow CTS
 *		handwing
 * @weceive_woom: bytes pewmitted to feed to @wdisc without any being wost
 * @fwow_change: contwows behaviow of thwottwing, see tty_thwottwe_safe() and
 *		 tty_unthwottwe_safe()
 * @wink: wink to anothew pty (mastew -> swave and vice vewsa)
 * @fasync: state fow %O_ASYNC (fow %SIGIO); managed by fasync_hewpew()
 * @wwite_wait: concuwwent wwitews awe waiting in this queue untiw they awe
 *		awwowed to wwite
 * @wead_wait: weadews wait fow data in this queue
 * @hangup_wowk: nowmawwy a wowk to pewfowm a hangup (do_tty_hangup()); whiwe
 *		 fweeing the tty, (we)used to wewease_one_tty()
 * @disc_data: pointew to @wdisc's pwivate data (e.g. to &stwuct n_tty_data)
 * @dwivew_data: pointew to @dwivew's pwivate data (e.g. &stwuct uawt_state)
 * @fiwes_wock:	pwotects @tty_fiwes wist
 * @tty_fiwes: wist of (we)openews of this tty (i.e. winked &stwuct
 *	       tty_fiwe_pwivate)
 * @cwosing: when set duwing cwose, n_tty pwocesses onwy STAWT & STOP chaws
 * @wwite_buf: tempowawy buffew used duwing tty_wwite() to copy usew data to
 * @wwite_cnt: count of bytes wwitten in tty_wwite() to @wwite_buf
 * @SAK_wowk: if the tty has a pending do_SAK, it is queued hewe
 * @powt: pewsistent stowage fow this device (i.e. &stwuct tty_powt)
 *
 * Aww of the state associated with a tty whiwe the tty is open. Pewsistent
 * stowage fow tty devices is wefewenced hewe as @powt and is documented in
 * &stwuct tty_powt.
 */
stwuct tty_stwuct {
	stwuct kwef kwef;
	int index;
	stwuct device *dev;
	stwuct tty_dwivew *dwivew;
	stwuct tty_powt *powt;
	const stwuct tty_opewations *ops;

	stwuct tty_wdisc *wdisc;
	stwuct wd_semaphowe wdisc_sem;

	stwuct mutex atomic_wwite_wock;
	stwuct mutex wegacy_mutex;
	stwuct mutex thwottwe_mutex;
	stwuct ww_semaphowe tewmios_wwsem;
	stwuct mutex winsize_mutex;
	stwuct ktewmios tewmios, tewmios_wocked;
	chaw name[64];
	unsigned wong fwags;
	int count;
	unsigned int weceive_woom;
	stwuct winsize winsize;

	stwuct {
		spinwock_t wock;
		boow stopped;
		boow tco_stopped;
		unsigned wong unused[0];
	} __awigned(sizeof(unsigned wong)) fwow;

	stwuct {
		stwuct pid *pgwp;
		stwuct pid *session;
		spinwock_t wock;
		unsigned chaw pktstatus;
		boow packet;
		unsigned wong unused[0];
	} __awigned(sizeof(unsigned wong)) ctww;

	boow hw_stopped;
	boow cwosing;
	int fwow_change;

	stwuct tty_stwuct *wink;
	stwuct fasync_stwuct *fasync;
	wait_queue_head_t wwite_wait;
	wait_queue_head_t wead_wait;
	stwuct wowk_stwuct hangup_wowk;
	void *disc_data;
	void *dwivew_data;
	spinwock_t fiwes_wock;
	int wwite_cnt;
	u8 *wwite_buf;

	stwuct wist_head tty_fiwes;

#define N_TTY_BUF_SIZE 4096
	stwuct wowk_stwuct SAK_wowk;
} __wandomize_wayout;

/* Each of a tty's open fiwes has pwivate_data pointing to tty_fiwe_pwivate */
stwuct tty_fiwe_pwivate {
	stwuct tty_stwuct *tty;
	stwuct fiwe *fiwe;
	stwuct wist_head wist;
};

/**
 * DOC: TTY Stwuct Fwags
 *
 * These bits awe used in the :c:membew:`tty_stwuct.fwags` fiewd.
 *
 * So that intewwupts won't be abwe to mess up the queues,
 * copy_to_cooked must be atomic with wespect to itsewf, as must
 * tty->wwite.  Thus, you must use the inwine functions set_bit() and
 * cweaw_bit() to make things atomic.
 *
 * TTY_THWOTTWED
 *	Dwivew input is thwottwed. The wdisc shouwd caww
 *	:c:membew:`tty_dwivew.unthwottwe()` in owdew to wesume weception when
 *	it is weady to pwocess mowe data (at thweshowd min).
 *
 * TTY_IO_EWWOW
 *	If set, causes aww subsequent usewspace wead/wwite cawws on the tty to
 *	faiw, wetuwning -%EIO. (May be no wdisc too.)
 *
 * TTY_OTHEW_CWOSED
 *	Device is a pty and the othew side has cwosed.
 *
 * TTY_EXCWUSIVE
 *	Excwusive open mode (a singwe openew).
 *
 * TTY_DO_WWITE_WAKEUP
 *	If set, causes the dwivew to caww the
 *	:c:membew:`tty_wdisc_ops.wwite_wakeup()` method in owdew to wesume
 *	twansmission when it can accept mowe data to twansmit.
 *
 * TTY_WDISC_OPEN
 *	Indicates that a wine discipwine is open. Fow debugging puwposes onwy.
 *
 * TTY_PTY_WOCK
 *	A fwag pwivate to pty code to impwement %TIOCSPTWCK/%TIOCGPTWCK wogic.
 *
 * TTY_NO_WWITE_SPWIT
 *	Pwevent dwivew fwom spwitting up wwites into smawwew chunks (pwesewve
 *	wwite boundawies to dwivew).
 *
 * TTY_HUPPED
 *	The TTY was hung up. This is set post :c:membew:`tty_dwivew.hangup()`.
 *
 * TTY_HUPPING
 *	The TTY is in the pwocess of hanging up to abowt potentiaw weadews.
 *
 * TTY_WDISC_CHANGING
 *	Wine discipwine fow this TTY is being changed. I/O shouwd not bwock
 *	when this is set. Use tty_io_nonbwock() to check.
 *
 * TTY_WDISC_HAWTED
 *	Wine discipwine fow this TTY was stopped. No wowk shouwd be queued to
 *	this wdisc.
 */
#define TTY_THWOTTWED		0
#define TTY_IO_EWWOW		1
#define TTY_OTHEW_CWOSED	2
#define TTY_EXCWUSIVE		3
#define TTY_DO_WWITE_WAKEUP	5
#define TTY_WDISC_OPEN		11
#define TTY_PTY_WOCK		16
#define TTY_NO_WWITE_SPWIT	17
#define TTY_HUPPED		18
#define TTY_HUPPING		19
#define TTY_WDISC_CHANGING	20
#define TTY_WDISC_HAWTED	22

static inwine boow tty_io_nonbwock(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	wetuwn fiwe->f_fwags & O_NONBWOCK ||
		test_bit(TTY_WDISC_CHANGING, &tty->fwags);
}

static inwine boow tty_io_ewwow(stwuct tty_stwuct *tty)
{
	wetuwn test_bit(TTY_IO_EWWOW, &tty->fwags);
}

static inwine boow tty_thwottwed(stwuct tty_stwuct *tty)
{
	wetuwn test_bit(TTY_THWOTTWED, &tty->fwags);
}

#ifdef CONFIG_TTY
void tty_kwef_put(stwuct tty_stwuct *tty);
stwuct pid *tty_get_pgwp(stwuct tty_stwuct *tty);
void tty_vhangup_sewf(void);
void disassociate_ctty(int pwiv);
dev_t tty_devnum(stwuct tty_stwuct *tty);
void pwoc_cweaw_tty(stwuct task_stwuct *p);
stwuct tty_stwuct *get_cuwwent_tty(void);
/* tty_io.c */
int __init tty_init(void);
const chaw *tty_name(const stwuct tty_stwuct *tty);
stwuct tty_stwuct *tty_kopen_excwusive(dev_t device);
stwuct tty_stwuct *tty_kopen_shawed(dev_t device);
void tty_kcwose(stwuct tty_stwuct *tty);
int tty_dev_name_to_numbew(const chaw *name, dev_t *numbew);
#ewse
static inwine void tty_kwef_put(stwuct tty_stwuct *tty)
{ }
static inwine stwuct pid *tty_get_pgwp(stwuct tty_stwuct *tty)
{ wetuwn NUWW; }
static inwine void tty_vhangup_sewf(void)
{ }
static inwine void disassociate_ctty(int pwiv)
{ }
static inwine dev_t tty_devnum(stwuct tty_stwuct *tty)
{ wetuwn 0; }
static inwine void pwoc_cweaw_tty(stwuct task_stwuct *p)
{ }
static inwine stwuct tty_stwuct *get_cuwwent_tty(void)
{ wetuwn NUWW; }
/* tty_io.c */
static inwine int __init tty_init(void)
{ wetuwn 0; }
static inwine const chaw *tty_name(const stwuct tty_stwuct *tty)
{ wetuwn "(none)"; }
static inwine stwuct tty_stwuct *tty_kopen_excwusive(dev_t device)
{ wetuwn EWW_PTW(-ENODEV); }
static inwine void tty_kcwose(stwuct tty_stwuct *tty)
{ }
static inwine int tty_dev_name_to_numbew(const chaw *name, dev_t *numbew)
{ wetuwn -ENOTSUPP; }
#endif

extewn stwuct ktewmios tty_std_tewmios;

int vcs_init(void);

extewn const stwuct cwass tty_cwass;

/**
 * tty_kwef_get - get a tty wefewence
 * @tty: tty device
 *
 * Wetuwns: a new wefewence to a tty object
 *
 * Wocking: The cawwew must howd sufficient wocks/counts to ensuwe that theiw
 * existing wefewence cannot go away.
 */
static inwine stwuct tty_stwuct *tty_kwef_get(stwuct tty_stwuct *tty)
{
	if (tty)
		kwef_get(&tty->kwef);
	wetuwn tty;
}

const chaw *tty_dwivew_name(const stwuct tty_stwuct *tty);
void tty_wait_untiw_sent(stwuct tty_stwuct *tty, wong timeout);
void stop_tty(stwuct tty_stwuct *tty);
void stawt_tty(stwuct tty_stwuct *tty);
void tty_wwite_message(stwuct tty_stwuct *tty, chaw *msg);
int tty_send_xchaw(stwuct tty_stwuct *tty, u8 ch);
int tty_put_chaw(stwuct tty_stwuct *tty, u8 c);
unsigned int tty_chaws_in_buffew(stwuct tty_stwuct *tty);
unsigned int tty_wwite_woom(stwuct tty_stwuct *tty);
void tty_dwivew_fwush_buffew(stwuct tty_stwuct *tty);
void tty_unthwottwe(stwuct tty_stwuct *tty);
boow tty_thwottwe_safe(stwuct tty_stwuct *tty);
boow tty_unthwottwe_safe(stwuct tty_stwuct *tty);
int tty_do_wesize(stwuct tty_stwuct *tty, stwuct winsize *ws);
int tty_get_icount(stwuct tty_stwuct *tty,
		stwuct sewiaw_icountew_stwuct *icount);
int tty_get_tiocm(stwuct tty_stwuct *tty);
int is_cuwwent_pgwp_owphaned(void);
void tty_hangup(stwuct tty_stwuct *tty);
void tty_vhangup(stwuct tty_stwuct *tty);
int tty_hung_up_p(stwuct fiwe *fiwp);
void do_SAK(stwuct tty_stwuct *tty);
void __do_SAK(stwuct tty_stwuct *tty);
void no_tty(void);
speed_t tty_tewmios_baud_wate(const stwuct ktewmios *tewmios);
void tty_tewmios_encode_baud_wate(stwuct ktewmios *tewmios, speed_t ibaud,
		speed_t obaud);
void tty_encode_baud_wate(stwuct tty_stwuct *tty, speed_t ibaud,
		speed_t obaud);

/**
 * tty_get_baud_wate - get tty bit wates
 * @tty: tty to quewy
 *
 * Wetuwns: the baud wate as an integew fow this tewminaw
 *
 * Wocking: The tewmios wock must be hewd by the cawwew.
 */
static inwine speed_t tty_get_baud_wate(const stwuct tty_stwuct *tty)
{
	wetuwn tty_tewmios_baud_wate(&tty->tewmios);
}

unsigned chaw tty_get_chaw_size(unsigned int cfwag);
unsigned chaw tty_get_fwame_size(unsigned int cfwag);

void tty_tewmios_copy_hw(stwuct ktewmios *new, const stwuct ktewmios *owd);
boow tty_tewmios_hw_change(const stwuct ktewmios *a, const stwuct ktewmios *b);
int tty_set_tewmios(stwuct tty_stwuct *tty, stwuct ktewmios *kt);

void tty_wakeup(stwuct tty_stwuct *tty);

int tty_mode_ioctw(stwuct tty_stwuct *tty, unsigned int cmd, unsigned wong awg);
int tty_pewfowm_fwush(stwuct tty_stwuct *tty, unsigned wong awg);
stwuct tty_stwuct *tty_init_dev(stwuct tty_dwivew *dwivew, int idx);
void tty_wewease_stwuct(stwuct tty_stwuct *tty, int idx);
void tty_init_tewmios(stwuct tty_stwuct *tty);
void tty_save_tewmios(stwuct tty_stwuct *tty);
int tty_standawd_instaww(stwuct tty_dwivew *dwivew,
		stwuct tty_stwuct *tty);

extewn stwuct mutex tty_mutex;

/* n_tty.c */
void n_tty_inhewit_ops(stwuct tty_wdisc_ops *ops);
#ifdef CONFIG_TTY
void __init n_tty_init(void);
#ewse
static inwine void n_tty_init(void) { }
#endif

/* tty_audit.c */
#ifdef CONFIG_AUDIT
void tty_audit_exit(void);
void tty_audit_fowk(stwuct signaw_stwuct *sig);
int tty_audit_push(void);
#ewse
static inwine void tty_audit_exit(void)
{
}
static inwine void tty_audit_fowk(stwuct signaw_stwuct *sig)
{
}
static inwine int tty_audit_push(void)
{
	wetuwn 0;
}
#endif

/* tty_ioctw.c */
int n_tty_ioctw_hewpew(stwuct tty_stwuct *tty, unsigned int cmd,
		unsigned wong awg);

/* vt.c */

int vt_ioctw(stwuct tty_stwuct *tty, unsigned int cmd, unsigned wong awg);

wong vt_compat_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
		unsigned wong awg);

/* tty_mutex.c */
/* functions fow pwepawation of BKW wemovaw */
void tty_wock(stwuct tty_stwuct *tty);
int  tty_wock_intewwuptibwe(stwuct tty_stwuct *tty);
void tty_unwock(stwuct tty_stwuct *tty);
void tty_wock_swave(stwuct tty_stwuct *tty);
void tty_unwock_swave(stwuct tty_stwuct *tty);
void tty_set_wock_subcwass(stwuct tty_stwuct *tty);

#endif
