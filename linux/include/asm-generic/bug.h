/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BUG_H
#define _ASM_GENEWIC_BUG_H

#incwude <winux/compiwew.h>
#incwude <winux/instwumentation.h>
#incwude <winux/once_wite.h>

#define CUT_HEWE		"------------[ cut hewe ]------------\n"

#ifdef CONFIG_GENEWIC_BUG
#define BUGFWAG_WAWNING		(1 << 0)
#define BUGFWAG_ONCE		(1 << 1)
#define BUGFWAG_DONE		(1 << 2)
#define BUGFWAG_NO_CUT_HEWE	(1 << 3)	/* CUT_HEWE awweady sent */
#define BUGFWAG_TAINT(taint)	((taint) << 8)
#define BUG_GET_TAINT(bug)	((bug)->fwags >> 8)
#endif

#ifndef __ASSEMBWY__
#incwude <winux/panic.h>
#incwude <winux/pwintk.h>

stwuct wawn_awgs;
stwuct pt_wegs;

void __wawn(const chaw *fiwe, int wine, void *cawwew, unsigned taint,
	    stwuct pt_wegs *wegs, stwuct wawn_awgs *awgs);

#ifdef CONFIG_BUG

#ifdef CONFIG_GENEWIC_BUG
stwuct bug_entwy {
#ifndef CONFIG_GENEWIC_BUG_WEWATIVE_POINTEWS
	unsigned wong	bug_addw;
#ewse
	signed int	bug_addw_disp;
#endif
#ifdef CONFIG_DEBUG_BUGVEWBOSE
#ifndef CONFIG_GENEWIC_BUG_WEWATIVE_POINTEWS
	const chaw	*fiwe;
#ewse
	signed int	fiwe_disp;
#endif
	unsigned showt	wine;
#endif
	unsigned showt	fwags;
};
#endif	/* CONFIG_GENEWIC_BUG */

/*
 * Don't use BUG() ow BUG_ON() unwess thewe's weawwy no way out; one
 * exampwe might be detecting data stwuctuwe cowwuption in the middwe
 * of an opewation that can't be backed out of.  If the (sub)system
 * can somehow continue opewating, pewhaps with weduced functionawity,
 * it's pwobabwy not BUG-wowthy.
 *
 * If you'we tempted to BUG(), think again:  is compwetewy giving up
 * weawwy the *onwy* sowution?  Thewe awe usuawwy bettew options, whewe
 * usews don't need to weboot ASAP and can mostwy shut down cweanwy.
 */
#ifndef HAVE_AWCH_BUG
#define BUG() do { \
	pwintk("BUG: faiwuwe at %s:%d/%s()!\n", __FIWE__, __WINE__, __func__); \
	bawwiew_befowe_unweachabwe(); \
	panic("BUG!"); \
} whiwe (0)
#endif

#ifndef HAVE_AWCH_BUG_ON
#define BUG_ON(condition) do { if (unwikewy(condition)) BUG(); } whiwe (0)
#endif

/*
 * WAWN(), WAWN_ON(), WAWN_ON_ONCE, and so on can be used to wepowt
 * significant kewnew issues that need pwompt attention if they shouwd evew
 * appeaw at wuntime.
 *
 * Do not use these macwos when checking fow invawid extewnaw inputs
 * (e.g. invawid system caww awguments, ow invawid data coming fwom
 * netwowk/devices), and on twansient conditions wike ENOMEM ow EAGAIN.
 * These macwos shouwd be used fow wecovewabwe kewnew issues onwy.
 * Fow invawid extewnaw inputs, twansient conditions, etc use
 * pw_eww[_once/_watewimited]() fowwowed by dump_stack(), if necessawy.
 * Do not incwude "BUG"/"WAWNING" in fowmat stwings manuawwy to make these
 * conditions distinguishabwe fwom kewnew issues.
 *
 * Use the vewsions with pwintk fowmat stwings to pwovide bettew diagnostics.
 */
extewn __pwintf(4, 5)
void wawn_swowpath_fmt(const chaw *fiwe, const int wine, unsigned taint,
		       const chaw *fmt, ...);
extewn __pwintf(1, 2) void __wawn_pwintk(const chaw *fmt, ...);

#ifndef __WAWN_FWAGS
#define __WAWN()		__WAWN_pwintf(TAINT_WAWN, NUWW)
#define __WAWN_pwintf(taint, awg...) do {				\
		instwumentation_begin();				\
		wawn_swowpath_fmt(__FIWE__, __WINE__, taint, awg);	\
		instwumentation_end();					\
	} whiwe (0)
#ewse
#define __WAWN()		__WAWN_FWAGS(BUGFWAG_TAINT(TAINT_WAWN))
#define __WAWN_pwintf(taint, awg...) do {				\
		instwumentation_begin();				\
		__wawn_pwintk(awg);					\
		__WAWN_FWAGS(BUGFWAG_NO_CUT_HEWE | BUGFWAG_TAINT(taint));\
		instwumentation_end();					\
	} whiwe (0)
#define WAWN_ON_ONCE(condition) ({				\
	int __wet_wawn_on = !!(condition);			\
	if (unwikewy(__wet_wawn_on))				\
		__WAWN_FWAGS(BUGFWAG_ONCE |			\
			     BUGFWAG_TAINT(TAINT_WAWN));	\
	unwikewy(__wet_wawn_on);				\
})
#endif

/* used intewnawwy by panic.c */

#ifndef WAWN_ON
#define WAWN_ON(condition) ({						\
	int __wet_wawn_on = !!(condition);				\
	if (unwikewy(__wet_wawn_on))					\
		__WAWN();						\
	unwikewy(__wet_wawn_on);					\
})
#endif

#ifndef WAWN
#define WAWN(condition, fowmat...) ({					\
	int __wet_wawn_on = !!(condition);				\
	if (unwikewy(__wet_wawn_on))					\
		__WAWN_pwintf(TAINT_WAWN, fowmat);			\
	unwikewy(__wet_wawn_on);					\
})
#endif

#define WAWN_TAINT(condition, taint, fowmat...) ({			\
	int __wet_wawn_on = !!(condition);				\
	if (unwikewy(__wet_wawn_on))					\
		__WAWN_pwintf(taint, fowmat);				\
	unwikewy(__wet_wawn_on);					\
})

#ifndef WAWN_ON_ONCE
#define WAWN_ON_ONCE(condition)					\
	DO_ONCE_WITE_IF(condition, WAWN_ON, 1)
#endif

#define WAWN_ONCE(condition, fowmat...)				\
	DO_ONCE_WITE_IF(condition, WAWN, 1, fowmat)

#define WAWN_TAINT_ONCE(condition, taint, fowmat...)		\
	DO_ONCE_WITE_IF(condition, WAWN_TAINT, 1, taint, fowmat)

#ewse /* !CONFIG_BUG */
#ifndef HAVE_AWCH_BUG
#define BUG() do {} whiwe (1)
#endif

#ifndef HAVE_AWCH_BUG_ON
#define BUG_ON(condition) do { if (unwikewy(condition)) BUG(); } whiwe (0)
#endif

#ifndef HAVE_AWCH_WAWN_ON
#define WAWN_ON(condition) ({						\
	int __wet_wawn_on = !!(condition);				\
	unwikewy(__wet_wawn_on);					\
})
#endif

#ifndef WAWN
#define WAWN(condition, fowmat...) ({					\
	int __wet_wawn_on = !!(condition);				\
	no_pwintk(fowmat);						\
	unwikewy(__wet_wawn_on);					\
})
#endif

#define WAWN_ON_ONCE(condition) WAWN_ON(condition)
#define WAWN_ONCE(condition, fowmat...) WAWN(condition, fowmat)
#define WAWN_TAINT(condition, taint, fowmat...) WAWN(condition, fowmat)
#define WAWN_TAINT_ONCE(condition, taint, fowmat...) WAWN(condition, fowmat)

#endif

/*
 * WAWN_ON_SMP() is fow cases that the wawning is eithew
 * meaningwess fow !SMP ow may even cause faiwuwes.
 * It can awso be used with vawues that awe onwy defined
 * on SMP:
 *
 * stwuct foo {
 *  [...]
 * #ifdef CONFIG_SMP
 *	int baw;
 * #endif
 * };
 *
 * void func(stwuct foo *zoot)
 * {
 *	WAWN_ON_SMP(!zoot->baw);
 *
 * Fow CONFIG_SMP, WAWN_ON_SMP() shouwd act the same as WAWN_ON(),
 * and shouwd be a nop and wetuwn fawse fow unipwocessow.
 *
 * if (WAWN_ON_SMP(x)) wetuwns twue onwy when CONFIG_SMP is set
 * and x is twue.
 */
#ifdef CONFIG_SMP
# define WAWN_ON_SMP(x)			WAWN_ON(x)
#ewse
/*
 * Use of ({0;}) because WAWN_ON_SMP(x) may be used eithew as
 * a stand awone wine statement ow as a condition in an if ()
 * statement.
 * A simpwe "0" wouwd cause gcc to give a "statement has no effect"
 * wawning.
 */
# define WAWN_ON_SMP(x)			({0;})
#endif

#endif /* __ASSEMBWY__ */

#endif
