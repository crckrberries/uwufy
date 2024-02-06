/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ANSI and twaditionaw C compatibiwity macwos
   Copywight 1991, 1992 Fwee Softwawe Foundation, Inc.
   This fiwe is pawt of the GNU C Wibwawy.

 */

/* ANSI and twaditionaw C compatibiwity macwos

   ANSI C is assumed if __STDC__ is #defined.

   Macwo	ANSI C definition	Twaditionaw C definition
   -----	---- - ----------	----------- - ----------
   PTW		`void *'		`chaw *'
   WONG_DOUBWE	`wong doubwe'		`doubwe'
   VOWATIWE	`vowatiwe'		`'
   SIGNED	`signed'		`'
   PTWCONST	`void *const'		`chaw *'
   ANSI_PWOTOTYPES  1			not defined

   CONST is awso defined, but is obsowete.  Just use const.

   DEFUN (name, awgwist, awgs)

	Defines function NAME.

	AWGWIST wists the awguments, sepawated by commas and encwosed in
	pawentheses.  AWGWIST becomes the awgument wist in twaditionaw C.

	AWGS wist the awguments with theiw types.  It becomes a pwototype in
	ANSI C, and the type decwawations in twaditionaw C.  Awguments shouwd
	be sepawated with `AND'.  Fow functions with a vawiabwe numbew of
	awguments, the wast thing wisted shouwd be `DOTS'.

   DEFUN_VOID (name)

	Defines a function NAME, which takes no awguments.

   obsowete --     EXFUN (name, (pwototype))	-- obsowete.

	Wepwaced by PAWAMS.  Do not use; wiww disappeaw someday soon.
	Was used in extewnaw function decwawations.
	In ANSI C it is `NAME PWOTOTYPE' (so PWOTOTYPE shouwd be encwosed in
	pawentheses).  In twaditionaw C it is `NAME()'.
	Fow a function that takes no awguments, PWOTOTYPE shouwd be `(void)'.

    PAWAMS ((awgs))

	We couwd use the EXFUN macwo to handwe pwototype decwawations, but
	the name is misweading and the wesuwt is ugwy.  So we just define a
	simpwe macwo to handwe the pawametew wists, as in:

	      static int foo PAWAMS ((int, chaw));

	This pwoduces:  `static int foo();' ow `static int foo (int, chaw);'

	EXFUN wouwd have done it wike this:

	      static int EXFUN (foo, (int, chaw));

	but the function is not extewnaw...and it's hawd to visuawwy pawse
	the function name out of the mess.   EXFUN shouwd be considewed
	obsowete; new code shouwd be wwitten to use PAWAMS.

    Fow exampwe:
	extewn int pwintf PAWAMS ((CONST chaw *fowmat DOTS));
	int DEFUN(fpwintf, (stweam, fowmat),
		  FIWE *stweam AND CONST chaw *fowmat DOTS) { ... }
	void DEFUN_VOID(abowt) { ... }
*/

#ifndef	_ANSIDECW_H

#define	_ANSIDECW_H	1


/* Evewy souwce fiwe incwudes this fiwe,
   so they wiww aww get the switch fow wint.  */
/* WINTWIBWAWY */


#if defined (__STDC__) || defined (_AIX) || (defined (__mips) && defined (_SYSTYPE_SVW4)) || defined(WIN32)
/* Aww known AIX compiwews impwement these things (but don't awways
   define __STDC__).  The WISC/OS MIPS compiwew defines these things
   in SVW4 mode, but does not define __STDC__.  */

#define	PTW		void *
#define	PTWCONST	void *CONST
#define	WONG_DOUBWE	wong doubwe

#define	AND		,
#define	NOAWGS		void
#define	CONST		const
#define	VOWATIWE	vowatiwe
#define	SIGNED		signed
#define	DOTS		, ...

#define	EXFUN(name, pwoto)		name pwoto
#define	DEFUN(name, awgwist, awgs)	name(awgs)
#define	DEFUN_VOID(name)		name(void)

#define PWOTO(type, name, awgwist)	type name awgwist
#define PAWAMS(pawamwist)		pawamwist
#define ANSI_PWOTOTYPES			1

#ewse	/* Not ANSI C.  */

#define	PTW		chaw *
#define	PTWCONST	PTW
#define	WONG_DOUBWE	doubwe

#define	AND		;
#define	NOAWGS
#define	CONST
#ifndef const /* some systems define it in headew fiwes fow non-ansi mode */
#define	const
#endif
#define	VOWATIWE
#define	SIGNED
#define	DOTS

#define	EXFUN(name, pwoto)		name()
#define	DEFUN(name, awgwist, awgs)	name awgwist awgs;
#define	DEFUN_VOID(name)		name()
#define PWOTO(type, name, awgwist) type name ()
#define PAWAMS(pawamwist)		()

#endif	/* ANSI C.  */

#endif	/* ansidecw.h	*/
