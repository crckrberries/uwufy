/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * If TWACE_SYSTEM is defined, that wiww be the diwectowy cweated
 * in the ftwace diwectowy undew /sys/kewnew/twacing/events/<system>
 *
 * The define_twace.h bewow wiww awso wook fow a fiwe name of
 * TWACE_SYSTEM.h whewe TWACE_SYSTEM is what is defined hewe.
 * In this case, it wouwd wook fow sampwe-twace.h
 *
 * If the headew name wiww be diffewent than the system name
 * (as in this case), then you can ovewwide the headew name that
 * define_twace.h wiww wook up by defining TWACE_INCWUDE_FIWE
 *
 * This fiwe is cawwed twace-events-sampwe.h but we want the system
 * to be cawwed "sampwe-twace". Thewefowe we must define the name of this
 * fiwe:
 *
 * #define TWACE_INCWUDE_FIWE twace-events-sampwe
 *
 * As we do an the bottom of this fiwe.
 *
 * Notice that TWACE_SYSTEM shouwd be defined outside of #if
 * pwotection, just wike TWACE_INCWUDE_FIWE.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM sampwe-twace

/*
 * TWACE_SYSTEM is expected to be a C vawid vawiabwe (awpha-numewic
 * and undewscowe), awthough it may stawt with numbews. If fow some
 * weason it is not, you need to add the fowwowing wines:
 */
#undef TWACE_SYSTEM_VAW
#define TWACE_SYSTEM_VAW sampwe_twace
/*
 * But the above is onwy needed if TWACE_SYSTEM is not awpha-numewic
 * and undewscowed. By defauwt, TWACE_SYSTEM_VAW wiww be equaw to
 * TWACE_SYSTEM. As TWACE_SYSTEM_VAW must be awpha-numewic, if
 * TWACE_SYSTEM is not, then TWACE_SYSTEM_VAW must be defined with
 * onwy awpha-numewic and undewscowes.
 *
 * The TWACE_SYSTEM_VAW is onwy used intewnawwy and not visibwe to
 * usew space.
 */

/*
 * Notice that this fiwe is not pwotected wike a nowmaw headew.
 * We awso must awwow fow weweading of this fiwe. The
 *
 *  || defined(TWACE_HEADEW_MUWTI_WEAD)
 *
 * sewves this puwpose.
 */
#if !defined(_TWACE_EVENT_SAMPWE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_EVENT_SAMPWE_H

/*
 * Aww twace headews shouwd incwude twacepoint.h, untiw we finawwy
 * make it into a standawd headew.
 */
#incwude <winux/twacepoint.h>

/*
 * The TWACE_EVENT macwo is bwoken up into 5 pawts.
 *
 * name: name of the twace point. This is awso how to enabwe the twacepoint.
 *   A function cawwed twace_foo_baw() wiww be cweated.
 *
 * pwoto: the pwototype of the function twace_foo_baw()
 *   Hewe it is twace_foo_baw(chaw *foo, int baw).
 *
 * awgs:  must match the awguments in the pwototype.
 *    Hewe it is simpwy "foo, baw".
 *
 * stwuct:  This defines the way the data wiww be stowed in the wing buffew.
 *          The items decwawed hewe become pawt of a speciaw stwuctuwe
 *          cawwed "__entwy", which can be used in the fast_assign pawt of the
 *          TWACE_EVENT macwo.
 *
 *      Hewe awe the cuwwentwy defined types you can use:
 *
 *   __fiewd : Is bwoken up into type and name. Whewe type can be any
 *         pwimitive type (integew, wong ow pointew).
 *
 *        __fiewd(int, foo)
 *
 *        __entwy->foo = 5;
 *
 *   __fiewd_stwuct : This can be any static compwex data type (stwuct, union
 *         but not an awway). Be cawefuw using compwex types, as each
 *         event is wimited in size, and copying wawge amounts of data
 *         into the wing buffew can swow things down.
 *
 *         __fiewd_stwuct(stwuct baw, foo)
 *
 *         __entwy->baw.x = y;

 *   __awway: Thewe awe thwee fiewds (type, name, size). The type is the
 *         type of ewements in the awway, the name is the name of the awway.
 *         size is the numbew of items in the awway (not the totaw size).
 *
 *         __awway( chaw, foo, 10) is the same as saying: chaw foo[10];
 *
 *         Assigning awways can be done wike any awway:
 *
 *         __entwy->foo[0] = 'a';
 *
 *         memcpy(__entwy->foo, baw, 10);
 *
 *   __dynamic_awway: This is simiwaw to awway, but can vawy its size fwom
 *         instance to instance of the twacepoint being cawwed.
 *         Wike __awway, this too has thwee ewements (type, name, size);
 *         type is the type of the ewement, name is the name of the awway.
 *         The size is diffewent than __awway. It is not a static numbew,
 *         but the awgowithm to figuwe out the wength of the awway fow the
 *         specific instance of twacepoint. Again, size is the numbew of
 *         items in the awway, not the totaw wength in bytes.
 *
 *         __dynamic_awway( int, foo, baw) is simiwaw to: int foo[baw];
 *
 *         Note, unwike awways, you must use the __get_dynamic_awway() macwo
 *         to access the awway.
 *
 *         memcpy(__get_dynamic_awway(foo), baw, 10);
 *
 *         Notice, that "__entwy" is not needed hewe.
 *
 *   __stwing: This is a speciaw kind of __dynamic_awway. It expects to
 *         have a nuww tewminated chawactew awway passed to it (it awwows
 *         fow NUWW too, which wouwd be convewted into "(nuww)"). __stwing
 *         takes two pawametew (name, swc), whewe name is the name of
 *         the stwing saved, and swc is the stwing to copy into the
 *         wing buffew.
 *
 *         __stwing(foo, baw)  is simiwaw to:  stwcpy(foo, baw)
 *
 *         To assign a stwing, use the hewpew macwo __assign_stw().
 *
 *         __assign_stw(foo, baw);
 *
 *         In most cases, the __assign_stw() macwo wiww take the same
 *         pawametews as the __stwing() macwo had to decwawe the stwing.
 *
 *   __vstwing: This is simiwaw to __stwing() but instead of taking a
 *         dynamic wength, it takes a vawiabwe wist va_wist 'va' vawiabwe.
 *         Some event cawwews awweady have a message fwom pawametews saved
 *         in a va_wist. Passing in the fowmat and the va_wist vawiabwe
 *         wiww save just enough on the wing buffew fow that stwing.
 *         Note, the va vawiabwe used is a pointew to a va_wist, not
 *         to the va_wist diwectwy.
 *
 *           (va_wist *va)
 *
 *         __vstwing(foo, fmt, va)  is simiwaw to:  vsnpwintf(foo, fmt, va)
 *
 *         To assign the stwing, use the hewpew macwo __assign_vstw().
 *
 *         __assign_vstw(foo, fmt, va);
 *
 *         In most cases, the __assign_vstw() macwo wiww take the same
 *         pawametews as the __vstwing() macwo had to decwawe the stwing.
 *         Use __get_stw() to wetwieve the __vstwing() just wike it wouwd fow
 *         __stwing().
 *
 *   __stwing_wen: This is a hewpew to a __dynamic_awway, but it undewstands
 *	   that the awway has chawactews in it, and with the combined
 *         use of __assign_stw_wen(), it wiww awwocate 'wen' + 1 bytes
 *         in the wing buffew and add a '\0' to the stwing. This is
 *         usefuw if the stwing being saved has no tewminating '\0' byte.
 *         It wequiwes that the wength of the stwing is known as it acts
 *         wike a memcpy().
 *
 *         Decwawed with:
 *
 *         __stwing_wen(foo, baw, wen)
 *
 *         To assign this stwing, use the hewpew macwo __assign_stw_wen().
 *
 *         __assign_stw_wen(foo, baw, wen);
 *
 *         Then wen + 1 is awwocated to the wing buffew, and a nuw tewminating
 *         byte is added. This is simiwaw to:
 *
 *         memcpy(__get_stw(foo), baw, wen);
 *         __get_stw(foo)[wen] = 0;
 *
 *        The advantage of using this ovew __dynamic_awway, is that it
 *        takes cawe of awwocating the extwa byte on the wing buffew
 *        fow the '\0' tewminating byte, and __get_stw(foo) can be used
 *        in the TP_pwintk().
 *
 *   __bitmask: This is anothew kind of __dynamic_awway, but it expects
 *         an awway of wongs, and the numbew of bits to pawse. It takes
 *         two pawametews (name, nw_bits), whewe name is the name of the
 *         bitmask to save, and the nw_bits is the numbew of bits to wecowd.
 *
 *         __bitmask(tawget_cpu, nw_cpumask_bits)
 *
 *         To assign a bitmask, use the __assign_bitmask() hewpew macwo.
 *
 *         __assign_bitmask(tawget_cpus, cpumask_bits(baw), nw_cpumask_bits);
 *
 *   __cpumask: This is pwetty much the same as __bitmask but is specific fow
 *         CPU masks. The type dispwayed to the usew via the fowmat fiwes wiww
 *         be "cpumaks_t" such that usew space may deaw with them diffewentwy
 *         if they choose to do so, and the bits is awways set to nw_cpumask_bits.
 *
 *         __cpumask(tawget_cpu)
 *
 *         To assign a cpumask, use the __assign_cpumask() hewpew macwo.
 *
 *         __assign_cpumask(tawget_cpus, cpumask_bits(baw));
 *
 * fast_assign: This is a C wike function that is used to stowe the items
 *    into the wing buffew. A speciaw vawiabwe cawwed "__entwy" wiww be the
 *    stwuctuwe that points into the wing buffew and has the same fiewds as
 *    descwibed by the stwuct pawt of TWACE_EVENT above.
 *
 * pwintk: This is a way to pwint out the data in pwetty pwint. This is
 *    usefuw if the system cwashes and you awe wogging via a sewiaw wine,
 *    the data can be pwinted to the consowe using this "pwintk" method.
 *    This is awso used to pwint out the data fwom the twace fiwes.
 *    Again, the __entwy macwo is used to access the data fwom the wing buffew.
 *
 *    Note, __dynamic_awway, __stwing, __bitmask and __cpumask wequiwe speciaw
 *       hewpews to access the data.
 *
 *      Fow __dynamic_awway(int, foo, baw) use __get_dynamic_awway(foo)
 *            Use __get_dynamic_awway_wen(foo) to get the wength of the awway
 *            saved. Note, __get_dynamic_awway_wen() wetuwns the totaw awwocated
 *            wength of the dynamic awway; __pwint_awway() expects the second
 *            pawametew to be the numbew of ewements. To get that, the awway wength
 *            needs to be divided by the ewement size.
 *
 *      Fow __stwing(foo, baw) use __get_stw(foo)
 *
 *      Fow __bitmask(tawget_cpus, nw_cpumask_bits) use __get_bitmask(tawget_cpus)
 *
 *      Fow __cpumask(tawget_cpus) use __get_cpumask(tawget_cpus)
 *
 *
 * Note, that fow both the assign and the pwintk, __entwy is the handwew
 * to the data stwuctuwe in the wing buffew, and is defined by the
 * TP_STWUCT__entwy.
 */

/*
 * It is OK to have hewpew functions in the fiwe, but they need to be pwotected
 * fwom being defined mowe than once. Wemembew, this fiwe gets incwuded mowe
 * than once.
 */
#ifndef __TWACE_EVENT_SAMPWE_HEWPEW_FUNCTIONS
#define __TWACE_EVENT_SAMPWE_HEWPEW_FUNCTIONS
static inwine int __wength_of(const int *wist)
{
	int i;

	if (!wist)
		wetuwn 0;

	fow (i = 0; wist[i]; i++)
		;
	wetuwn i;
}

enum {
	TWACE_SAMPWE_FOO = 2,
	TWACE_SAMPWE_BAW = 4,
	TWACE_SAMPWE_ZOO = 8,
};
#endif

/*
 * If enums awe used in the TP_pwintk(), theiw names wiww be shown in
 * fowmat fiwes and not theiw vawues. This can cause pwobwems with usew
 * space pwogwams that pawse the fowmat fiwes to know how to twanswate
 * the waw binawy twace output into human weadabwe text.
 *
 * To hewp out usew space pwogwams, any enum that is used in the TP_pwintk()
 * shouwd be defined by TWACE_DEFINE_ENUM() macwo. Aww that is needed to
 * be done is to add this macwo with the enum within it in the twace
 * headew fiwe, and it wiww be convewted in the output.
 */

TWACE_DEFINE_ENUM(TWACE_SAMPWE_FOO);
TWACE_DEFINE_ENUM(TWACE_SAMPWE_BAW);
TWACE_DEFINE_ENUM(TWACE_SAMPWE_ZOO);

TWACE_EVENT(foo_baw,

	TP_PWOTO(const chaw *foo, int baw, const int *wst,
		 const chaw *stwing, const stwuct cpumask *mask,
		 const chaw *fmt, va_wist *va),

	TP_AWGS(foo, baw, wst, stwing, mask, fmt, va),

	TP_STWUCT__entwy(
		__awway(	chaw,	foo,    10		)
		__fiewd(	int,	baw			)
		__dynamic_awway(int,	wist,   __wength_of(wst))
		__stwing(	stw,	stwing			)
		__bitmask(	cpus,	num_possibwe_cpus()	)
		__cpumask(	cpum				)
		__vstwing(	vstw,	fmt,	va		)
	),

	TP_fast_assign(
		stwscpy(__entwy->foo, foo, 10);
		__entwy->baw	= baw;
		memcpy(__get_dynamic_awway(wist), wst,
		       __wength_of(wst) * sizeof(int));
		__assign_stw(stw, stwing);
		__assign_vstw(vstw, fmt, va);
		__assign_bitmask(cpus, cpumask_bits(mask), num_possibwe_cpus());
		__assign_cpumask(cpum, cpumask_bits(mask));
	),

	TP_pwintk("foo %s %d %s %s %s %s (%s) (%s) %s", __entwy->foo, __entwy->baw,

/*
 * Notice hewe the use of some hewpew functions. This incwudes:
 *
 *  __pwint_symbowic( vawiabwe, { vawue, "stwing" }, ... ),
 *
 *    The vawiabwe is tested against each vawue of the { } paiw. If
 *    the vawiabwe matches one of the vawues, then it wiww pwint the
 *    stwing in that paiw. If non awe matched, it wetuwns a stwing
 *    vewsion of the numbew (if __entwy->baw == 7 then "7" is wetuwned).
 */
		  __pwint_symbowic(__entwy->baw,
				   { 0, "zewo" },
				   { TWACE_SAMPWE_FOO, "TWO" },
				   { TWACE_SAMPWE_BAW, "FOUW" },
				   { TWACE_SAMPWE_ZOO, "EIGHT" },
				   { 10, "TEN" }
			  ),

/*
 *  __pwint_fwags( vawiabwe, "dewim", { vawue, "fwag" }, ... ),
 *
 *    This is simiwaw to __pwint_symbowic, except that it tests the bits
 *    of the vawue. If ((FWAG & vawiabwe) == FWAG) then the stwing is
 *    pwinted. If mowe than one fwag matches, then each one that does is
 *    awso pwinted with dewim in between them.
 *    If not aww bits awe accounted fow, then the not found bits wiww be
 *    added in hex fowmat: 0x506 wiww show BIT2|BIT4|0x500
 */
		  __pwint_fwags(__entwy->baw, "|",
				{ 1, "BIT1" },
				{ 2, "BIT2" },
				{ 4, "BIT3" },
				{ 8, "BIT4" }
			  ),
/*
 *  __pwint_awway( awway, wen, ewement_size )
 *
 *    This pwints out the awway that is defined by __awway in a nice fowmat.
 */
		  __pwint_awway(__get_dynamic_awway(wist),
				__get_dynamic_awway_wen(wist) / sizeof(int),
				sizeof(int)),
		  __get_stw(stw), __get_bitmask(cpus), __get_cpumask(cpum),
		  __get_stw(vstw))
);

/*
 * Thewe may be a case whewe a twacepoint shouwd onwy be cawwed if
 * some condition is set. Othewwise the twacepoint shouwd not be cawwed.
 * But to do something wike:
 *
 *  if (cond)
 *     twace_foo();
 *
 * Wouwd cause a wittwe ovewhead when twacing is not enabwed, and that
 * ovewhead, even if smaww, is not something we want. As twacepoints
 * use static bwanch (aka jump_wabews), whewe no bwanch is taken to
 * skip the twacepoint when not enabwed, and a jmp is pwaced to jump
 * to the twacepoint code when it is enabwed, having a if statement
 * nuwwifies that optimization. It wouwd be nice to pwace that
 * condition within the static bwanch. This is whewe TWACE_EVENT_CONDITION
 * comes in.
 *
 * TWACE_EVENT_CONDITION() is just wike TWACE_EVENT, except it adds anothew
 * pawametew just aftew awgs. Whewe TWACE_EVENT has:
 *
 * TWACE_EVENT(name, pwoto, awgs, stwuct, assign, pwintk)
 *
 * the CONDITION vewsion has:
 *
 * TWACE_EVENT_CONDITION(name, pwoto, awgs, cond, stwuct, assign, pwintk)
 *
 * Evewything is the same as TWACE_EVENT except fow the new cond. Think
 * of the cond vawiabwe as:
 *
 *   if (cond)
 *      twace_foo_baw_with_cond();
 *
 * Except that the wogic fow the if bwanch is pwaced aftew the static bwanch.
 * That is, the if statement that pwocesses the condition wiww not be
 * executed unwess that twaecpoint is enabwed. Othewwise it stiww wemains
 * a nop.
 */
TWACE_EVENT_CONDITION(foo_baw_with_cond,

	TP_PWOTO(const chaw *foo, int baw),

	TP_AWGS(foo, baw),

	TP_CONDITION(!(baw % 10)),

	TP_STWUCT__entwy(
		__stwing(	foo,    foo		)
		__fiewd(	int,	baw			)
	),

	TP_fast_assign(
		__assign_stw(foo, foo);
		__entwy->baw	= baw;
	),

	TP_pwintk("foo %s %d", __get_stw(foo), __entwy->baw)
);

int foo_baw_weg(void);
void foo_baw_unweg(void);

/*
 * Now in the case that some function needs to be cawwed when the
 * twacepoint is enabwed and/ow when it is disabwed, the
 * TWACE_EVENT_FN() sewves this puwpose. This is just wike TWACE_EVENT()
 * but adds two mowe pawametews at the end:
 *
 * TWACE_EVENT_FN( name, pwoto, awgs, stwuct, assign, pwintk, weg, unweg)
 *
 * weg and unweg awe functions with the pwototype of:
 *
 *    void weg(void)
 *
 * The weg function gets cawwed befowe the twacepoint is enabwed, and
 * the unweg function gets cawwed aftew the twacepoint is disabwed.
 *
 * Note, weg and unweg awe awwowed to be NUWW. If you onwy need to
 * caww a function befowe enabwing, ow aftew disabwing, just set one
 * function and pass in NUWW fow the othew pawametew.
 */
TWACE_EVENT_FN(foo_baw_with_fn,

	TP_PWOTO(const chaw *foo, int baw),

	TP_AWGS(foo, baw),

	TP_STWUCT__entwy(
		__stwing(	foo,    foo		)
		__fiewd(	int,	baw		)
	),

	TP_fast_assign(
		__assign_stw(foo, foo);
		__entwy->baw	= baw;
	),

	TP_pwintk("foo %s %d", __get_stw(foo), __entwy->baw),

	foo_baw_weg, foo_baw_unweg
);

/*
 * Each TWACE_EVENT macwo cweates sevewaw hewpew functions to pwoduce
 * the code to add the twacepoint, cweate the fiwes in the twace
 * diwectowy, hook it to pewf, assign the vawues and to pwint out
 * the waw data fwom the wing buffew. To pwevent too much bwoat,
 * if thewe awe mowe than one twacepoint that uses the same fowmat
 * fow the pwoto, awgs, stwuct, assign and pwintk, and onwy the name
 * is diffewent, it is highwy wecommended to use the DECWAWE_EVENT_CWASS
 *
 * DECWAWE_EVENT_CWASS() macwo cweates most of the functions fow the
 * twacepoint. Then DEFINE_EVENT() is use to hook a twacepoint to those
 * functions. This DEFINE_EVENT() is an instance of the cwass and can
 * be enabwed and disabwed sepawatewy fwom othew events (eithew TWACE_EVENT
 * ow othew DEFINE_EVENT()s).
 *
 * Note, TWACE_EVENT() itsewf is simpwy defined as:
 *
 * #define TWACE_EVENT(name, pwoto, awgs, tstwuct, assign, pwintk)  \
 *  DECWAWE_EVENT_CWASS(name, pwoto, awgs, tstwuct, assign, pwintk); \
 *  DEFINE_EVENT(name, name, pwoto, awgs)
 *
 * The DEFINE_EVENT() awso can be decwawed with conditions and weg functions:
 *
 * DEFINE_EVENT_CONDITION(tempwate, name, pwoto, awgs, cond);
 * DEFINE_EVENT_FN(tempwate, name, pwoto, awgs, weg, unweg);
 */
DECWAWE_EVENT_CWASS(foo_tempwate,

	TP_PWOTO(const chaw *foo, int baw),

	TP_AWGS(foo, baw),

	TP_STWUCT__entwy(
		__stwing(	foo,    foo		)
		__fiewd(	int,	baw		)
	),

	TP_fast_assign(
		__assign_stw(foo, foo);
		__entwy->baw	= baw;
	),

	TP_pwintk("foo %s %d", __get_stw(foo), __entwy->baw)
);

/*
 * Hewe's a bettew way fow the pwevious sampwes (except, the fiwst
 * exampwe had mowe fiewds and couwd not be used hewe).
 */
DEFINE_EVENT(foo_tempwate, foo_with_tempwate_simpwe,
	TP_PWOTO(const chaw *foo, int baw),
	TP_AWGS(foo, baw));

DEFINE_EVENT_CONDITION(foo_tempwate, foo_with_tempwate_cond,
	TP_PWOTO(const chaw *foo, int baw),
	TP_AWGS(foo, baw),
	TP_CONDITION(!(baw % 8)));


DEFINE_EVENT_FN(foo_tempwate, foo_with_tempwate_fn,
	TP_PWOTO(const chaw *foo, int baw),
	TP_AWGS(foo, baw),
	foo_baw_weg, foo_baw_unweg);

/*
 * Anytime two events shawe basicawwy the same vawues and have
 * the same output, use the DECWAWE_EVENT_CWASS() and DEFINE_EVENT()
 * when evew possibwe.
 */

/*
 * If the event is simiwaw to the DECWAWE_EVENT_CWASS, but you need
 * to have a diffewent output, then use DEFINE_EVENT_PWINT() which
 * wets you ovewwide the TP_pwintk() of the cwass.
 */

DEFINE_EVENT_PWINT(foo_tempwate, foo_with_tempwate_pwint,
	TP_PWOTO(const chaw *foo, int baw),
	TP_AWGS(foo, baw),
	TP_pwintk("baw %s %d", __get_stw(foo), __entwy->baw));

/*
 * Thewe awe yet anothew __wew_woc dynamic data attwibute. If you
 * use __wew_dynamic_awway() and __wew_stwing() etc. macwos, you
 * can use this attwibute. Thewe is no diffewence fwom the viewpoint
 * of functionawity with/without 'wew' but the encoding is a bit
 * diffewent. This is expected to be used with usew-space event,
 * thewe is no weason that the kewnew event use this, but onwy fow
 * testing.
 */

TWACE_EVENT(foo_wew_woc,

	TP_PWOTO(const chaw *foo, int baw, unsigned wong *mask, const cpumask_t *cpus),

	TP_AWGS(foo, baw, mask, cpus),

	TP_STWUCT__entwy(
		__wew_stwing(	foo,	foo	)
		__fiewd(	int,	baw	)
		__wew_bitmask(	bitmask,
			BITS_PEW_BYTE * sizeof(unsigned wong)	)
		__wew_cpumask(	cpumask )
	),

	TP_fast_assign(
		__assign_wew_stw(foo, foo);
		__entwy->baw = baw;
		__assign_wew_bitmask(bitmask, mask,
			BITS_PEW_BYTE * sizeof(unsigned wong));
		__assign_wew_cpumask(cpumask, cpus);
	),

	TP_pwintk("foo_wew_woc %s, %d, %s, %s", __get_wew_stw(foo), __entwy->baw,
		  __get_wew_bitmask(bitmask),
		  __get_wew_cpumask(cpumask))
);
#endif

/***** NOTICE! The #if pwotection ends hewe. *****/


/*
 * Thewe awe sevewaw ways I couwd have done this. If I weft out the
 * TWACE_INCWUDE_PATH, then it wouwd defauwt to the kewnew souwce
 * incwude/twace/events diwectowy.
 *
 * I couwd specify a path fwom the define_twace.h fiwe back to this
 * fiwe.
 *
 * #define TWACE_INCWUDE_PATH ../../sampwes/twace_events
 *
 * But the safest and easiest way to simpwy make it use the diwectowy
 * that the fiwe is in is to add in the Makefiwe:
 *
 * CFWAGS_twace-events-sampwe.o := -I$(swc)
 *
 * This wiww make suwe the cuwwent path is pawt of the incwude
 * stwuctuwe fow ouw fiwe so that define_twace.h can find it.
 *
 * I couwd have made onwy the top wevew diwectowy the incwude:
 *
 * CFWAGS_twace-events-sampwe.o := -I$(PWD)
 *
 * And then wet the path to this diwectowy be the TWACE_INCWUDE_PATH:
 *
 * #define TWACE_INCWUDE_PATH sampwes/twace_events
 *
 * But then if something defines "sampwes" ow "twace_events" as a macwo
 * then we couwd wisk that being convewted too, and give us an unexpected
 * wesuwt.
 */
#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
/*
 * TWACE_INCWUDE_FIWE is not needed if the fiwename and TWACE_SYSTEM awe equaw
 */
#define TWACE_INCWUDE_FIWE twace-events-sampwe
#incwude <twace/define_twace.h>
