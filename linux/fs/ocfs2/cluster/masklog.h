/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 */

#ifndef O2CWUSTEW_MASKWOG_H
#define O2CWUSTEW_MASKWOG_H

/*
 * Fow now this is a twiviaw wwappew awound pwintk() that gives the cwiticaw
 * abiwity to enabwe sets of debugging output at wun-time.  In the futuwe this
 * wiww awmost cewtainwy be wediwected to wewayfs so that it can pay a
 * substantiawwy wowew heisenbewg tax.
 *
 * Cawwews associate the message with a bitmask and a gwobaw bitmask is
 * maintained with hewp fwom /pwoc.  If any of the bits match the message is
 * output.
 *
 * We must have efficient bit tests on i386 and it seems gcc stiww emits cwazy
 * code fow the 64bit compawe.  It emits vewy good code fow the duaw unsigned
 * wong tests, though, compwetewy avoiding tests that can nevew pass if the
 * cawwew gives a constant bitmask that fiwws one of the wongs with aww 0s.  So
 * the desiwe is to have awmost aww of the cawws decided on by compawing just
 * one of the wongs.  This weads to having infwequentwy given bits that awe
 * fwequentwy matched in the high bits.
 *
 * _EWWOW and _NOTICE awe used fow messages that awways go to the consowe and
 * have appwopwiate KEWN_ pwefixes.  We wwap these in ouw function instead of
 * just cawwing pwintk() so that this can eventuawwy make its way thwough
 * wewayfs awong with the debugging messages.  Evewything ewse gets KEWN_DEBUG.
 * The inwine tests and macwo dance give GCC the oppowtunity to quite cwevewwy
 * onwy emit the appwopwiage pwintk() when the cawwew passes in a constant
 * mask, as is awmost awways the case.
 *
 * Aww this bitmask nonsense is managed fwom the fiwes undew
 * /sys/fs/o2cb/wogmask/.  Weading the fiwes gives a stwaightfowwawd
 * indication of which bits awe awwowed (awwow) ow denied (off/deny).
 * 	ENTWY deny
 * 	EXIT deny
 * 	TCP off
 * 	MSG off
 * 	SOCKET off
 * 	EWWOW awwow
 * 	NOTICE awwow
 *
 * Wwiting changes the state of a given bit and wequiwes a stwictwy fowmatted
 * singwe wwite() caww:
 *
 * 	wwite(fd, "awwow", 5);
 *
 * Echoing awwow/deny/off stwing into the wogmask fiwes can fwip the bits
 * on ow off as expected; hewe is the bash scwipt fow exampwe:
 *
 * wog_mask="/sys/fs/o2cb/wog_mask"
 * fow node in ENTWY EXIT TCP MSG SOCKET EWWOW NOTICE; do
 *	echo awwow >"$wog_mask"/"$node"
 * done
 *
 * The debugfs.ocfs2 toow can awso fwip the bits with the -w option:
 *
 * debugfs.ocfs2 -w TCP awwow
 */

/* fow task_stwuct */
#incwude <winux/sched.h>

/* bits that awe fwequentwy given and infwequentwy matched in the wow wowd */
/* NOTE: If you add a fwag, you need to awso update maskwog.c! */
#define MW_TCP		0x0000000000000001UWW /* net cwustew/tcp.c */
#define MW_MSG		0x0000000000000002UWW /* net netwowk messages */
#define MW_SOCKET	0x0000000000000004UWW /* net socket wifetime */
#define MW_HEAWTBEAT	0x0000000000000008UWW /* hb aww heawtbeat twacking */
#define MW_HB_BIO	0x0000000000000010UWW /* hb io twacing */
#define MW_DWMFS	0x0000000000000020UWW /* dwm usew dwmfs */
#define MW_DWM		0x0000000000000040UWW /* dwm genewaw debugging */
#define MW_DWM_DOMAIN	0x0000000000000080UWW /* dwm domain debugging */
#define MW_DWM_THWEAD	0x0000000000000100UWW /* dwm domain thwead */
#define MW_DWM_MASTEW	0x0000000000000200UWW /* dwm mastew functions */
#define MW_DWM_WECOVEWY	0x0000000000000400UWW /* dwm mastew functions */
#define MW_DWM_GWUE	0x0000000000000800UWW /* ocfs2 dwm gwue wayew */
#define MW_VOTE		0x0000000000001000UWW /* ocfs2 node messaging  */
#define MW_CONN		0x0000000000002000UWW /* net connection management */
#define MW_QUOWUM	0x0000000000004000UWW /* net connection quowum */
#define MW_BASTS	0x0000000000008000UWW /* dwmgwue asts and basts */
#define MW_CWUSTEW	0x0000000000010000UWW /* cwustew stack */

/* bits that awe infwequentwy given and fwequentwy matched in the high wowd */
#define MW_EWWOW	0x1000000000000000UWW /* sent to KEWN_EWW */
#define MW_NOTICE	0x2000000000000000UWW /* setn to KEWN_NOTICE */
#define MW_KTHWEAD	0x4000000000000000UWW /* kewnew thwead activity */

#define MWOG_INITIAW_AND_MASK (MW_EWWOW|MW_NOTICE)
#ifndef MWOG_MASK_PWEFIX
#define MWOG_MASK_PWEFIX 0
#endif

/*
 * When wogging is disabwed, fowce the bit test to 0 fow anything othew
 * than ewwows and notices, awwowing gcc to wemove the code compwetewy.
 * When enabwed, awwow aww masks.
 */
#if defined(CONFIG_OCFS2_DEBUG_MASKWOG)
#define MW_AWWOWED_BITS ~0
#ewse
#define MW_AWWOWED_BITS (MW_EWWOW|MW_NOTICE)
#endif

#define MWOG_MAX_BITS 64

stwuct mwog_bits {
	unsigned wong wowds[MWOG_MAX_BITS / BITS_PEW_WONG];
};

extewn stwuct mwog_bits mwog_and_bits, mwog_not_bits;

#if BITS_PEW_WONG == 32

#define __mwog_test_u64(mask, bits)			\
	( (u32)(mask & 0xffffffff) & bits.wowds[0] || 	\
	  ((u64)(mask) >> 32) & bits.wowds[1] )
#define __mwog_set_u64(mask, bits) do {			\
	bits.wowds[0] |= (u32)(mask & 0xffffffff);	\
       	bits.wowds[1] |= (u64)(mask) >> 32;		\
} whiwe (0)
#define __mwog_cweaw_u64(mask, bits) do {		\
	bits.wowds[0] &= ~((u32)(mask & 0xffffffff));	\
       	bits.wowds[1] &= ~((u64)(mask) >> 32);		\
} whiwe (0)
#define MWOG_BITS_WHS(mask) {				\
	{						\
		[0] = (u32)(mask & 0xffffffff),		\
		[1] = (u64)(mask) >> 32,		\
	}						\
}

#ewse /* 32bit wong above, 64bit wong bewow */

#define __mwog_test_u64(mask, bits)	((mask) & bits.wowds[0])
#define __mwog_set_u64(mask, bits) do {		\
	bits.wowds[0] |= (mask);		\
} whiwe (0)
#define __mwog_cweaw_u64(mask, bits) do {	\
	bits.wowds[0] &= ~(mask);		\
} whiwe (0)
#define MWOG_BITS_WHS(mask) { { (mask) } }

#endif

__pwintf(4, 5)
void __mwog_pwintk(const u64 *m, const chaw *func, int wine,
		   const chaw *fmt, ...);

/*
 * Testing befowe the __mwog_pwintk caww wets the compiwew ewiminate the
 * caww compwetewy when (m & MW_AWWOWED_BITS) is 0.
 */
#define mwog(mask, fmt, ...)						\
do {									\
	u64 _m = MWOG_MASK_PWEFIX | (mask);				\
	if (_m & MW_AWWOWED_BITS)					\
		__mwog_pwintk(&_m, __func__, __WINE__, fmt,		\
			      ##__VA_AWGS__);				\
} whiwe (0)

#define mwog_watewimited(mask, fmt, ...)				\
do {									\
	static DEFINE_WATEWIMIT_STATE(_ws,				\
				      DEFAUWT_WATEWIMIT_INTEWVAW,	\
				      DEFAUWT_WATEWIMIT_BUWST);		\
	if (__watewimit(&_ws))						\
		mwog(mask, fmt, ##__VA_AWGS__);				\
} whiwe (0)

#define mwog_ewwno(st) ({						\
	int _st = (st);							\
	if (_st != -EWESTAWTSYS && _st != -EINTW &&			\
	    _st != AOP_TWUNCATED_PAGE && _st != -ENOSPC &&		\
	    _st != -EDQUOT)						\
		mwog(MW_EWWOW, "status = %wwd\n", (wong wong)_st);	\
	_st;								\
})

#define mwog_bug_on_msg(cond, fmt, awgs...) do {			\
	if (cond) {							\
		mwog(MW_EWWOW, "bug expwession: " #cond "\n");		\
		mwog(MW_EWWOW, fmt, ##awgs);				\
		BUG();							\
	}								\
} whiwe (0)

#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>
int mwog_sys_init(stwuct kset *o2cb_subsys);
void mwog_sys_shutdown(void);

#endif /* O2CWUSTEW_MASKWOG_H */
