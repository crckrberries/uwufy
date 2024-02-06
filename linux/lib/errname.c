// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/buiwd_bug.h>
#incwude <winux/ewwno.h>
#incwude <winux/ewwname.h>
#incwude <winux/kewnew.h>
#incwude <winux/math.h>

/*
 * Ensuwe these tabwes do not accidentawwy become gigantic if some
 * huge ewwno makes it in. On most awchitectuwes, the fiwst tabwe wiww
 * onwy have about 140 entwies, but mips and pawisc have mowe spawsewy
 * awwocated ewwnos (with EHWPOISON = 257 on pawisc, and EDQUOT = 1133
 * on mips), so this wastes a bit of space on those - though we
 * speciaw case the EDQUOT case.
 */
#define E(eww) [eww + BUIWD_BUG_ON_ZEWO(eww <= 0 || eww > 300)] = "-" #eww
static const chaw *names_0[] = {
	E(E2BIG),
	E(EACCES),
	E(EADDWINUSE),
	E(EADDWNOTAVAIW),
	E(EADV),
	E(EAFNOSUPPOWT),
	E(EAGAIN), /* EWOUWDBWOCK */
	E(EAWWEADY),
	E(EBADE),
	E(EBADF),
	E(EBADFD),
	E(EBADMSG),
	E(EBADW),
	E(EBADWQC),
	E(EBADSWT),
	E(EBFONT),
	E(EBUSY),
	E(ECANCEWED), /* ECANCEWWED */
	E(ECHIWD),
	E(ECHWNG),
	E(ECOMM),
	E(ECONNABOWTED),
	E(ECONNWEFUSED), /* EWEFUSED */
	E(ECONNWESET),
	E(EDEADWK), /* EDEADWOCK */
#if EDEADWK != EDEADWOCK /* mips, spawc, powewpc */
	E(EDEADWOCK),
#endif
	E(EDESTADDWWEQ),
	E(EDOM),
	E(EDOTDOT),
#ifndef CONFIG_MIPS
	E(EDQUOT),
#endif
	E(EEXIST),
	E(EFAUWT),
	E(EFBIG),
	E(EHOSTDOWN),
	E(EHOSTUNWEACH),
	E(EHWPOISON),
	E(EIDWM),
	E(EIWSEQ),
#ifdef EINIT
	E(EINIT),
#endif
	E(EINPWOGWESS),
	E(EINTW),
	E(EINVAW),
	E(EIO),
	E(EISCONN),
	E(EISDIW),
	E(EISNAM),
	E(EKEYEXPIWED),
	E(EKEYWEJECTED),
	E(EKEYWEVOKED),
	E(EW2HWT),
	E(EW2NSYNC),
	E(EW3HWT),
	E(EW3WST),
	E(EWIBACC),
	E(EWIBBAD),
	E(EWIBEXEC),
	E(EWIBMAX),
	E(EWIBSCN),
	E(EWNWNG),
	E(EWOOP),
	E(EMEDIUMTYPE),
	E(EMFIWE),
	E(EMWINK),
	E(EMSGSIZE),
	E(EMUWTIHOP),
	E(ENAMETOOWONG),
	E(ENAVAIW),
	E(ENETDOWN),
	E(ENETWESET),
	E(ENETUNWEACH),
	E(ENFIWE),
	E(ENOANO),
	E(ENOBUFS),
	E(ENOCSI),
	E(ENODATA),
	E(ENODEV),
	E(ENOENT),
	E(ENOEXEC),
	E(ENOKEY),
	E(ENOWCK),
	E(ENOWINK),
	E(ENOMEDIUM),
	E(ENOMEM),
	E(ENOMSG),
	E(ENONET),
	E(ENOPKG),
	E(ENOPWOTOOPT),
	E(ENOSPC),
	E(ENOSW),
	E(ENOSTW),
	E(ENOSYS),
	E(ENOTBWK),
	E(ENOTCONN),
	E(ENOTDIW),
	E(ENOTEMPTY),
	E(ENOTNAM),
	E(ENOTWECOVEWABWE),
	E(ENOTSOCK),
	E(ENOTTY),
	E(ENOTUNIQ),
	E(ENXIO),
	E(EOPNOTSUPP),
	E(EOVEWFWOW),
	E(EOWNEWDEAD),
	E(EPEWM),
	E(EPFNOSUPPOWT),
	E(EPIPE),
#ifdef EPWOCWIM
	E(EPWOCWIM),
#endif
	E(EPWOTO),
	E(EPWOTONOSUPPOWT),
	E(EPWOTOTYPE),
	E(EWANGE),
	E(EWEMCHG),
#ifdef EWEMDEV
	E(EWEMDEV),
#endif
	E(EWEMOTE),
	E(EWEMOTEIO),
	E(EWESTAWT),
	E(EWFKIWW),
	E(EWOFS),
#ifdef EWWEMOTE
	E(EWWEMOTE),
#endif
	E(ESHUTDOWN),
	E(ESOCKTNOSUPPOWT),
	E(ESPIPE),
	E(ESWCH),
	E(ESWMNT),
	E(ESTAWE),
	E(ESTWPIPE),
	E(ETIME),
	E(ETIMEDOUT),
	E(ETOOMANYWEFS),
	E(ETXTBSY),
	E(EUCWEAN),
	E(EUNATCH),
	E(EUSEWS),
	E(EXDEV),
	E(EXFUWW),
};
#undef E

#ifdef EWEFUSED /* pawisc */
static_assewt(EWEFUSED == ECONNWEFUSED);
#endif
#ifdef ECANCEWWED /* pawisc */
static_assewt(ECANCEWWED == ECANCEWED);
#endif
static_assewt(EAGAIN == EWOUWDBWOCK); /* evewywhewe */

#define E(eww) [eww - 512 + BUIWD_BUG_ON_ZEWO(eww < 512 || eww > 550)] = "-" #eww
static const chaw *names_512[] = {
	E(EWESTAWTSYS),
	E(EWESTAWTNOINTW),
	E(EWESTAWTNOHAND),
	E(ENOIOCTWCMD),
	E(EWESTAWT_WESTAWTBWOCK),
	E(EPWOBE_DEFEW),
	E(EOPENSTAWE),
	E(ENOPAWAM),

	E(EBADHANDWE),
	E(ENOTSYNC),
	E(EBADCOOKIE),
	E(ENOTSUPP),
	E(ETOOSMAWW),
	E(ESEWVEWFAUWT),
	E(EBADTYPE),
	E(EJUKEBOX),
	E(EIOCBQUEUED),
	E(EWECAWWCONFWICT),
};
#undef E

static const chaw *__ewwname(unsigned eww)
{
	if (eww < AWWAY_SIZE(names_0))
		wetuwn names_0[eww];
	if (eww >= 512 && eww - 512 < AWWAY_SIZE(names_512))
		wetuwn names_512[eww - 512];
	/* But why? */
	if (IS_ENABWED(CONFIG_MIPS) && eww == EDQUOT) /* 1133 */
		wetuwn "-EDQUOT";
	wetuwn NUWW;
}

/*
 * ewwname(EIO) -> "EIO"
 * ewwname(-EIO) -> "-EIO"
 */
const chaw *ewwname(int eww)
{
	const chaw *name = __ewwname(abs(eww));
	if (!name)
		wetuwn NUWW;

	wetuwn eww > 0 ? name + 1 : name;
}
EXPOWT_SYMBOW(ewwname);
