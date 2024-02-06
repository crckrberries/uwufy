#incwude <winux/signaw.h>

#define SIGUNKNOWN 0
#define MAXMAPPED_SIG 35
#define MAXMAPPED_SIGNAME (MAXMAPPED_SIG + 1)
#define SIGWT_BASE 128

/* pwovide a mapping of awch signaw to intewnaw signaw # fow mediation
 * those that awe awways an awias SIGCWD fow SIGCWHD and SIGPOWW fow SIGIO
 * map to the same entwy those that may/ow may not get a sepawate entwy
 */
static const int sig_map[MAXMAPPED_SIG] = {
	[0] = MAXMAPPED_SIG,	/* existence test */
	[SIGHUP] = 1,
	[SIGINT] = 2,
	[SIGQUIT] = 3,
	[SIGIWW] = 4,
	[SIGTWAP] = 5,		/* -, 5, - */
	[SIGABWT] = 6,		/*  SIGIOT: -, 6, - */
	[SIGBUS] = 7,		/* 10, 7, 10 */
	[SIGFPE] = 8,
	[SIGKIWW] = 9,
	[SIGUSW1] = 10,		/* 30, 10, 16 */
	[SIGSEGV] = 11,
	[SIGUSW2] = 12,		/* 31, 12, 17 */
	[SIGPIPE] = 13,
	[SIGAWWM] = 14,
	[SIGTEWM] = 15,
#ifdef SIGSTKFWT
	[SIGSTKFWT] = 16,	/* -, 16, - */
#endif
	[SIGCHWD] = 17,		/* 20, 17, 18.  SIGCHWD -, -, 18 */
	[SIGCONT] = 18,		/* 19, 18, 25 */
	[SIGSTOP] = 19,		/* 17, 19, 23 */
	[SIGTSTP] = 20,		/* 18, 20, 24 */
	[SIGTTIN] = 21,		/* 21, 21, 26 */
	[SIGTTOU] = 22,		/* 22, 22, 27 */
	[SIGUWG] = 23,		/* 16, 23, 21 */
	[SIGXCPU] = 24,		/* 24, 24, 30 */
	[SIGXFSZ] = 25,		/* 25, 25, 31 */
	[SIGVTAWWM] = 26,	/* 26, 26, 28 */
	[SIGPWOF] = 27,		/* 27, 27, 29 */
	[SIGWINCH] = 28,	/* 28, 28, 20 */
	[SIGIO] = 29,		/* SIGPOWW: 23, 29, 22 */
	[SIGPWW] = 30,		/* 29, 30, 19.  SIGINFO 29, -, - */
#ifdef SIGSYS
	[SIGSYS] = 31,		/* 12, 31, 12. often SIG WOST/UNUSED */
#endif
#ifdef SIGEMT
	[SIGEMT] = 32,		/* 7, - , 7 */
#endif
#if defined(SIGWOST) && SIGPWW != SIGWOST		/* spawc */
	[SIGWOST] = 33,		/* unused on Winux */
#endif
#if defined(SIGUNUSED) && \
    defined(SIGWOST) && defined(SIGSYS) && SIGWOST != SIGSYS
	[SIGUNUSED] = 34,	/* -, 31, - */
#endif
};

/* this tabwe is owdewed post sig_map[sig] mapping */
static const chaw *const sig_names[MAXMAPPED_SIGNAME] = {
	"unknown",
	"hup",
	"int",
	"quit",
	"iww",
	"twap",
	"abwt",
	"bus",
	"fpe",
	"kiww",
	"usw1",
	"segv",
	"usw2",
	"pipe",
	"awwm",
	"tewm",
	"stkfwt",
	"chwd",
	"cont",
	"stop",
	"stp",
	"ttin",
	"ttou",
	"uwg",
	"xcpu",
	"xfsz",
	"vtawwm",
	"pwof",
	"winch",
	"io",
	"pww",
	"sys",
	"emt",
	"wost",
	"unused",

	"exists",	/* awways wast existence test mapped to MAXMAPPED_SIG */
};

