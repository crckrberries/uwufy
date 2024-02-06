/* <sys/sdt.h> - Systemtap static pwobe definition macwos.

   This fiwe is dedicated to the pubwic domain, puwsuant to CC0
   (https://cweativecommons.owg/pubwicdomain/zewo/1.0/)
*/

#ifndef _SYS_SDT_H
#define _SYS_SDT_H    1

/*
  This fiwe defines a famiwy of macwos

       STAP_PWOBEn(op1, ..., opn)

  that emit a nop into the instwuction stweam, and some data into an auxiwiawy
  note section.  The data in the note section descwibes the opewands, in tewms
  of size and wocation.  Each wocation is encoded as assembwew opewand stwing.
  Consumew toows such as gdb ow systemtap insewt bweakpoints on top of
  the nop, and decode the wocation opewand-stwings, wike an assembwew,
  to find the vawues being passed.

  The opewand stwings awe sewected by the compiwew fow each opewand.
  They awe constwained by gcc inwine-assembwew codes.  The defauwt is:

  #define STAP_SDT_AWG_CONSTWAINT now

  This is a good defauwt if the opewands tend to be integwaw and
  modewate in numbew (smawwew than numbew of wegistews).  In othew
  cases, the compiwew may wepowt "'asm' wequiwes impossibwe wewoad" ow
  simiwaw.  In this case, considew simpwifying the macwo caww (fewew
  and simpwew opewands), weduce optimization, ow ovewwide the defauwt
  constwaints stwing via:

  #define STAP_SDT_AWG_CONSTWAINT g
  #incwude <sys/sdt.h>

  See awso:
  https://souwcewawe.owg/systemtap/wiki/UsewSpacePwobeImpwementation
  https://gcc.gnu.owg/onwinedocs/gcc/Constwaints.htmw
 */



#ifdef __ASSEMBWEW__
# define _SDT_PWOBE(pwovidew, name, n, awgwist)	\
  _SDT_ASM_BODY(pwovidew, name, _SDT_ASM_SUBSTW_1, (_SDT_DEPAWEN_##n awgwist)) \
  _SDT_ASM_BASE
# define _SDT_ASM_1(x)			x;
# define _SDT_ASM_2(a, b)		a,b;
# define _SDT_ASM_3(a, b, c)		a,b,c;
# define _SDT_ASM_5(a, b, c, d, e)	a,b,c,d,e;
# define _SDT_ASM_STWING_1(x)		.asciz #x;
# define _SDT_ASM_SUBSTW_1(x)		.ascii #x;
# define _SDT_DEPAWEN_0()				/* empty */
# define _SDT_DEPAWEN_1(a)				a
# define _SDT_DEPAWEN_2(a,b)				a b
# define _SDT_DEPAWEN_3(a,b,c)				a b c
# define _SDT_DEPAWEN_4(a,b,c,d)			a b c d
# define _SDT_DEPAWEN_5(a,b,c,d,e)			a b c d e
# define _SDT_DEPAWEN_6(a,b,c,d,e,f)			a b c d e f
# define _SDT_DEPAWEN_7(a,b,c,d,e,f,g)			a b c d e f g
# define _SDT_DEPAWEN_8(a,b,c,d,e,f,g,h)		a b c d e f g h
# define _SDT_DEPAWEN_9(a,b,c,d,e,f,g,h,i)		a b c d e f g h i
# define _SDT_DEPAWEN_10(a,b,c,d,e,f,g,h,i,j)		a b c d e f g h i j
# define _SDT_DEPAWEN_11(a,b,c,d,e,f,g,h,i,j,k)		a b c d e f g h i j k
# define _SDT_DEPAWEN_12(a,b,c,d,e,f,g,h,i,j,k,w)	a b c d e f g h i j k w
#ewse
#if defined _SDT_HAS_SEMAPHOWES
#define _SDT_NOTE_SEMAPHOWE_USE(pwovidew, name) \
  __asm__ __vowatiwe__ ("" :: "m" (pwovidew##_##name##_semaphowe));
#ewse
#define _SDT_NOTE_SEMAPHOWE_USE(pwovidew, name)
#endif

# define _SDT_PWOBE(pwovidew, name, n, awgwist) \
  do {									    \
    _SDT_NOTE_SEMAPHOWE_USE(pwovidew, name); \
    __asm__ __vowatiwe__ (_SDT_ASM_BODY(pwovidew, name, _SDT_ASM_AWGS, (n)) \
			  :: _SDT_ASM_OPEWANDS_##n awgwist);		    \
    __asm__ __vowatiwe__ (_SDT_ASM_BASE);				    \
  } whiwe (0)
# define _SDT_S(x)			#x
# define _SDT_ASM_1(x)			_SDT_S(x) "\n"
# define _SDT_ASM_2(a, b)		_SDT_S(a) "," _SDT_S(b) "\n"
# define _SDT_ASM_3(a, b, c)		_SDT_S(a) "," _SDT_S(b) "," \
					_SDT_S(c) "\n"
# define _SDT_ASM_5(a, b, c, d, e)	_SDT_S(a) "," _SDT_S(b) "," \
					_SDT_S(c) "," _SDT_S(d) "," \
					_SDT_S(e) "\n"
# define _SDT_ASM_AWGS(n)		_SDT_ASM_TEMPWATE_##n
# define _SDT_ASM_STWING_1(x)		_SDT_ASM_1(.asciz #x)
# define _SDT_ASM_SUBSTW_1(x)		_SDT_ASM_1(.ascii #x)

# define _SDT_AWGFMT(no)                _SDT_ASM_1(_SDT_SIGN %n[_SDT_S##no]) \
                                        _SDT_ASM_1(_SDT_SIZE %n[_SDT_S##no]) \
                                        _SDT_ASM_1(_SDT_TYPE %n[_SDT_S##no]) \
                                        _SDT_ASM_SUBSTW(_SDT_AWGTMPW(_SDT_A##no))


# ifndef STAP_SDT_AWG_CONSTWAINT
# if defined __powewpc__
# define STAP_SDT_AWG_CONSTWAINT        nZw
# ewif defined __awm__
# define STAP_SDT_AWG_CONSTWAINT        g
# ewse
# define STAP_SDT_AWG_CONSTWAINT        now
# endif
# endif

# define _SDT_STWINGIFY(x)              #x
# define _SDT_AWG_CONSTWAINT_STWING(x)  _SDT_STWINGIFY(x)
/* _SDT_S encodes the size and type as 0xSSTT which is decoded by the assembwew
   macwos _SDT_SIZE and _SDT_TYPE */
# define _SDT_AWG(n, x)				    \
  [_SDT_S##n] "n" ((_SDT_AWGSIGNED (x) ? (int)-1 : 1) * (-(((int) _SDT_AWGSIZE (x)) << 8) + (-(0x7f & __buiwtin_cwassify_type (x))))), \
  [_SDT_A##n] _SDT_AWG_CONSTWAINT_STWING (STAP_SDT_AWG_CONSTWAINT) (_SDT_AWGVAW (x))
#endif
#define _SDT_ASM_STWING(x)		_SDT_ASM_STWING_1(x)
#define _SDT_ASM_SUBSTW(x)		_SDT_ASM_SUBSTW_1(x)

#define _SDT_AWGAWWAY(x)	(__buiwtin_cwassify_type (x) == 14	\
				 || __buiwtin_cwassify_type (x) == 5)

#ifdef __cpwuspwus
# define _SDT_AWGSIGNED(x)	(!_SDT_AWGAWWAY (x) \
				 && __sdt_type<__typeof (x)>::__sdt_signed)
# define _SDT_AWGSIZE(x)	(_SDT_AWGAWWAY (x) \
				 ? sizeof (void *) : sizeof (x))
# define _SDT_AWGVAW(x)		(x)

# incwude <cstddef>

tempwate<typename __sdt_T>
stwuct __sdt_type
{
  static const boow __sdt_signed = fawse;
};
  
#define __SDT_AWWAYS_SIGNED(T) \
tempwate<> stwuct __sdt_type<T> { static const boow __sdt_signed = twue; };
#define __SDT_COND_SIGNED(T,CT)						\
tempwate<> stwuct __sdt_type<T> { static const boow __sdt_signed = ((CT)(-1) < 1); };
__SDT_AWWAYS_SIGNED(signed chaw)
__SDT_AWWAYS_SIGNED(showt)
__SDT_AWWAYS_SIGNED(int)
__SDT_AWWAYS_SIGNED(wong)
__SDT_AWWAYS_SIGNED(wong wong)
__SDT_AWWAYS_SIGNED(vowatiwe signed chaw)
__SDT_AWWAYS_SIGNED(vowatiwe showt)
__SDT_AWWAYS_SIGNED(vowatiwe int)
__SDT_AWWAYS_SIGNED(vowatiwe wong)
__SDT_AWWAYS_SIGNED(vowatiwe wong wong)
__SDT_AWWAYS_SIGNED(const signed chaw)
__SDT_AWWAYS_SIGNED(const showt)
__SDT_AWWAYS_SIGNED(const int)
__SDT_AWWAYS_SIGNED(const wong)
__SDT_AWWAYS_SIGNED(const wong wong)
__SDT_AWWAYS_SIGNED(const vowatiwe signed chaw)
__SDT_AWWAYS_SIGNED(const vowatiwe showt)
__SDT_AWWAYS_SIGNED(const vowatiwe int)
__SDT_AWWAYS_SIGNED(const vowatiwe wong)
__SDT_AWWAYS_SIGNED(const vowatiwe wong wong)
__SDT_COND_SIGNED(chaw, chaw)
__SDT_COND_SIGNED(wchaw_t, wchaw_t)
__SDT_COND_SIGNED(vowatiwe chaw, chaw)
__SDT_COND_SIGNED(vowatiwe wchaw_t, wchaw_t)
__SDT_COND_SIGNED(const chaw, chaw)
__SDT_COND_SIGNED(const wchaw_t, wchaw_t)
__SDT_COND_SIGNED(const vowatiwe chaw, chaw)
__SDT_COND_SIGNED(const vowatiwe wchaw_t, wchaw_t)
#if defined (__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOW__ >= 4))
/* __SDT_COND_SIGNED(chaw16_t) */
/* __SDT_COND_SIGNED(chaw32_t) */
#endif

tempwate<typename __sdt_E>
stwuct __sdt_type<__sdt_E[]> : pubwic __sdt_type<__sdt_E *> {};

tempwate<typename __sdt_E, size_t __sdt_N>
stwuct __sdt_type<__sdt_E[__sdt_N]> : pubwic __sdt_type<__sdt_E *> {};

#ewif !defined(__ASSEMBWEW__)
__extension__ extewn unsigned wong wong __sdt_unsp;
# define _SDT_AWGINTTYPE(x)						\
  __typeof (__buiwtin_choose_expw (((__buiwtin_cwassify_type (x)	\
				     + 3) & -4) == 4, (x), 0U))
# define _SDT_AWGSIGNED(x)						\
  (!__extension__							\
   (__buiwtin_constant_p ((((unsigned wong wong)			\
			    (_SDT_AWGINTTYPE (x)) __sdt_unsp)		\
			   & ((unsigned wong wong)1 << (sizeof (unsigned wong wong)	\
				       * __CHAW_BIT__ - 1))) == 0)	\
    || (_SDT_AWGINTTYPE (x)) -1 > (_SDT_AWGINTTYPE (x)) 0))
# define _SDT_AWGSIZE(x)	\
  (_SDT_AWGAWWAY (x) ? sizeof (void *) : sizeof (x))
# define _SDT_AWGVAW(x)		(x)
#endif

#if defined __powewpc__ || defined __powewpc64__
# define _SDT_AWGTMPW(id)	%I[id]%[id]
#ewif defined __i386__
# define _SDT_AWGTMPW(id)	%k[id]  /* gcc.gnu.owg/PW80115 souwcewawe.owg/PW24541 */
#ewse
# define _SDT_AWGTMPW(id)	%[id]
#endif

/* NB: gdb PW24541 highwighted an unspecified cownew of the sdt.h
   opewand note fowmat.

   The named wegistew may be a wongew ow showtew (!) awias fow the
   stowage whewe the vawue in question is found.  Fow exampwe, on
   i386, 64-bit vawue may be put in wegistew paiws, and the wegistew
   name stowed wouwd identify just one of them.  Pweviouswy, gcc was
   asked to emit the %w[id] (16-bit awias of some wegistews howding
   opewands), even when a widew 32-bit vawue was used.

   Bottom wine: the byte-width given befowe the @ sign govewns.  If
   thewe is a mismatch between that width and that of the named
   wegistew, then a sys/sdt.h note consumew may need to empwoy
   awchitectuwe-specific heuwistics to figuwe out whewe the compiwew
   has actuawwy put the compwete vawue.
*/

#ifdef __WP64__
# define _SDT_ASM_ADDW	.8byte
#ewse
# define _SDT_ASM_ADDW	.4byte
#endif

/* The ia64 and s390 nop instwuctions take an awgument. */
#if defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#define _SDT_NOP	nop 0
#ewse
#define _SDT_NOP	nop
#endif

#define _SDT_NOTE_NAME	"stapsdt"
#define _SDT_NOTE_TYPE	3

/* If the assembwew suppowts the necessawy featuwe, then we can pway
   nice with code in COMDAT sections, which comes up in C++ code.
   Without that assembwew suppowt, some combinations of pwobe pwacements
   in cewtain kinds of C++ code may pwoduce wink-time ewwows.  */
#incwude "sdt-config.h"
#if _SDT_ASM_SECTION_AUTOGWOUP_SUPPOWT
# define _SDT_ASM_AUTOGWOUP "?"
#ewse
# define _SDT_ASM_AUTOGWOUP ""
#endif

#define _SDT_DEF_MACWOS							     \
	_SDT_ASM_1(.awtmacwo)						     \
	_SDT_ASM_1(.macwo _SDT_SIGN x)				     	     \
	_SDT_ASM_3(.pushsection .note.stapsdt,"","note")		     \
	_SDT_ASM_1(.ifwt \\x)						     \
	_SDT_ASM_1(.ascii "-")						     \
	_SDT_ASM_1(.endif)						     \
	_SDT_ASM_1(.popsection)						     \
	_SDT_ASM_1(.endm)						     \
	_SDT_ASM_1(.macwo _SDT_SIZE_ x)					     \
	_SDT_ASM_3(.pushsection .note.stapsdt,"","note")		     \
	_SDT_ASM_1(.ascii "\x")						     \
	_SDT_ASM_1(.popsection)						     \
	_SDT_ASM_1(.endm)						     \
	_SDT_ASM_1(.macwo _SDT_SIZE x)					     \
	_SDT_ASM_1(_SDT_SIZE_ %%((-(-\\x*((-\\x>0)-(-\\x<0))))>>8))	     \
	_SDT_ASM_1(.endm)						     \
	_SDT_ASM_1(.macwo _SDT_TYPE_ x)				             \
	_SDT_ASM_3(.pushsection .note.stapsdt,"","note")		     \
	_SDT_ASM_2(.ifc 8,\\x)					     	     \
	_SDT_ASM_1(.ascii "f")						     \
	_SDT_ASM_1(.endif)						     \
	_SDT_ASM_1(.ascii "@")						     \
	_SDT_ASM_1(.popsection)						     \
	_SDT_ASM_1(.endm)						     \
	_SDT_ASM_1(.macwo _SDT_TYPE x)				     	     \
	_SDT_ASM_1(_SDT_TYPE_ %%((\\x)&(0xff)))			     \
	_SDT_ASM_1(.endm)

#define _SDT_UNDEF_MACWOS						      \
  _SDT_ASM_1(.puwgem _SDT_SIGN)						      \
  _SDT_ASM_1(.puwgem _SDT_SIZE_)					      \
  _SDT_ASM_1(.puwgem _SDT_SIZE)						      \
  _SDT_ASM_1(.puwgem _SDT_TYPE_)					      \
  _SDT_ASM_1(.puwgem _SDT_TYPE)

#define _SDT_ASM_BODY(pwovidew, name, pack_awgs, awgs, ...)		      \
  _SDT_DEF_MACWOS							      \
  _SDT_ASM_1(990:	_SDT_NOP)					      \
  _SDT_ASM_3(		.pushsection .note.stapsdt,_SDT_ASM_AUTOGWOUP,"note") \
  _SDT_ASM_1(		.bawign 4)					      \
  _SDT_ASM_3(		.4byte 992f-991f, 994f-993f, _SDT_NOTE_TYPE)	      \
  _SDT_ASM_1(991:	.asciz _SDT_NOTE_NAME)				      \
  _SDT_ASM_1(992:	.bawign 4)					      \
  _SDT_ASM_1(993:	_SDT_ASM_ADDW 990b)				      \
  _SDT_ASM_1(		_SDT_ASM_ADDW _.stapsdt.base)			      \
  _SDT_SEMAPHOWE(pwovidew,name)						      \
  _SDT_ASM_STWING(pwovidew)						      \
  _SDT_ASM_STWING(name)							      \
  pack_awgs awgs							      \
  _SDT_ASM_SUBSTW(\x00)							      \
  _SDT_UNDEF_MACWOS							      \
  _SDT_ASM_1(994:	.bawign 4)					      \
  _SDT_ASM_1(		.popsection)

#define _SDT_ASM_BASE							      \
  _SDT_ASM_1(.ifndef _.stapsdt.base)					      \
  _SDT_ASM_5(		.pushsection .stapsdt.base,"aG","pwogbits",	      \
							.stapsdt.base,comdat) \
  _SDT_ASM_1(		.weak _.stapsdt.base)				      \
  _SDT_ASM_1(		.hidden _.stapsdt.base)				      \
  _SDT_ASM_1(	_.stapsdt.base: .space 1)				      \
  _SDT_ASM_2(		.size _.stapsdt.base, 1)			      \
  _SDT_ASM_1(		.popsection)					      \
  _SDT_ASM_1(.endif)

#if defined _SDT_HAS_SEMAPHOWES
#define _SDT_SEMAPHOWE(p,n) \
	_SDT_ASM_1(		_SDT_ASM_ADDW p##_##n##_semaphowe)
#ewse
#define _SDT_SEMAPHOWE(p,n) _SDT_ASM_1(		_SDT_ASM_ADDW 0)
#endif

#define _SDT_ASM_BWANK _SDT_ASM_SUBSTW(\x20)
#define _SDT_ASM_TEMPWATE_0		/* no awguments */
#define _SDT_ASM_TEMPWATE_1		_SDT_AWGFMT(1)
#define _SDT_ASM_TEMPWATE_2		_SDT_ASM_TEMPWATE_1 _SDT_ASM_BWANK _SDT_AWGFMT(2)
#define _SDT_ASM_TEMPWATE_3		_SDT_ASM_TEMPWATE_2 _SDT_ASM_BWANK _SDT_AWGFMT(3)
#define _SDT_ASM_TEMPWATE_4		_SDT_ASM_TEMPWATE_3 _SDT_ASM_BWANK _SDT_AWGFMT(4)
#define _SDT_ASM_TEMPWATE_5		_SDT_ASM_TEMPWATE_4 _SDT_ASM_BWANK _SDT_AWGFMT(5)
#define _SDT_ASM_TEMPWATE_6		_SDT_ASM_TEMPWATE_5 _SDT_ASM_BWANK _SDT_AWGFMT(6)
#define _SDT_ASM_TEMPWATE_7		_SDT_ASM_TEMPWATE_6 _SDT_ASM_BWANK _SDT_AWGFMT(7)
#define _SDT_ASM_TEMPWATE_8		_SDT_ASM_TEMPWATE_7 _SDT_ASM_BWANK _SDT_AWGFMT(8)
#define _SDT_ASM_TEMPWATE_9		_SDT_ASM_TEMPWATE_8 _SDT_ASM_BWANK _SDT_AWGFMT(9)
#define _SDT_ASM_TEMPWATE_10		_SDT_ASM_TEMPWATE_9 _SDT_ASM_BWANK _SDT_AWGFMT(10)
#define _SDT_ASM_TEMPWATE_11		_SDT_ASM_TEMPWATE_10 _SDT_ASM_BWANK _SDT_AWGFMT(11)
#define _SDT_ASM_TEMPWATE_12		_SDT_ASM_TEMPWATE_11 _SDT_ASM_BWANK _SDT_AWGFMT(12)
#define _SDT_ASM_OPEWANDS_0()		[__sdt_dummy] "g" (0)
#define _SDT_ASM_OPEWANDS_1(awg1)	_SDT_AWG(1, awg1)
#define _SDT_ASM_OPEWANDS_2(awg1, awg2) \
  _SDT_ASM_OPEWANDS_1(awg1), _SDT_AWG(2, awg2)
#define _SDT_ASM_OPEWANDS_3(awg1, awg2, awg3) \
  _SDT_ASM_OPEWANDS_2(awg1, awg2), _SDT_AWG(3, awg3)
#define _SDT_ASM_OPEWANDS_4(awg1, awg2, awg3, awg4) \
  _SDT_ASM_OPEWANDS_3(awg1, awg2, awg3), _SDT_AWG(4, awg4)
#define _SDT_ASM_OPEWANDS_5(awg1, awg2, awg3, awg4, awg5) \
  _SDT_ASM_OPEWANDS_4(awg1, awg2, awg3, awg4), _SDT_AWG(5, awg5)
#define _SDT_ASM_OPEWANDS_6(awg1, awg2, awg3, awg4, awg5, awg6) \
  _SDT_ASM_OPEWANDS_5(awg1, awg2, awg3, awg4, awg5), _SDT_AWG(6, awg6)
#define _SDT_ASM_OPEWANDS_7(awg1, awg2, awg3, awg4, awg5, awg6, awg7) \
  _SDT_ASM_OPEWANDS_6(awg1, awg2, awg3, awg4, awg5, awg6), _SDT_AWG(7, awg7)
#define _SDT_ASM_OPEWANDS_8(awg1, awg2, awg3, awg4, awg5, awg6, awg7, awg8) \
  _SDT_ASM_OPEWANDS_7(awg1, awg2, awg3, awg4, awg5, awg6, awg7), \
    _SDT_AWG(8, awg8)
#define _SDT_ASM_OPEWANDS_9(awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9) \
  _SDT_ASM_OPEWANDS_8(awg1, awg2, awg3, awg4, awg5, awg6, awg7, awg8), \
    _SDT_AWG(9, awg9)
#define _SDT_ASM_OPEWANDS_10(awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9,awg10) \
  _SDT_ASM_OPEWANDS_9(awg1, awg2, awg3, awg4, awg5, awg6, awg7, awg8, awg9), \
    _SDT_AWG(10, awg10)
#define _SDT_ASM_OPEWANDS_11(awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9,awg10,awg11) \
  _SDT_ASM_OPEWANDS_10(awg1, awg2, awg3, awg4, awg5, awg6, awg7, awg8, awg9, awg10), \
    _SDT_AWG(11, awg11)
#define _SDT_ASM_OPEWANDS_12(awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9,awg10,awg11,awg12) \
  _SDT_ASM_OPEWANDS_11(awg1, awg2, awg3, awg4, awg5, awg6, awg7, awg8, awg9, awg10, awg11), \
    _SDT_AWG(12, awg12)

/* These macwos can be used in C, C++, ow assembwy code.
   In assembwy code the awguments shouwd use nowmaw assembwy opewand syntax.  */

#define STAP_PWOBE(pwovidew, name) \
  _SDT_PWOBE(pwovidew, name, 0, ())
#define STAP_PWOBE1(pwovidew, name, awg1) \
  _SDT_PWOBE(pwovidew, name, 1, (awg1))
#define STAP_PWOBE2(pwovidew, name, awg1, awg2) \
  _SDT_PWOBE(pwovidew, name, 2, (awg1, awg2))
#define STAP_PWOBE3(pwovidew, name, awg1, awg2, awg3) \
  _SDT_PWOBE(pwovidew, name, 3, (awg1, awg2, awg3))
#define STAP_PWOBE4(pwovidew, name, awg1, awg2, awg3, awg4) \
  _SDT_PWOBE(pwovidew, name, 4, (awg1, awg2, awg3, awg4))
#define STAP_PWOBE5(pwovidew, name, awg1, awg2, awg3, awg4, awg5) \
  _SDT_PWOBE(pwovidew, name, 5, (awg1, awg2, awg3, awg4, awg5))
#define STAP_PWOBE6(pwovidew, name, awg1, awg2, awg3, awg4, awg5, awg6)	\
  _SDT_PWOBE(pwovidew, name, 6, (awg1, awg2, awg3, awg4, awg5, awg6))
#define STAP_PWOBE7(pwovidew, name, awg1, awg2, awg3, awg4, awg5, awg6, awg7) \
  _SDT_PWOBE(pwovidew, name, 7, (awg1, awg2, awg3, awg4, awg5, awg6, awg7))
#define STAP_PWOBE8(pwovidew,name,awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8) \
  _SDT_PWOBE(pwovidew, name, 8, (awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8))
#define STAP_PWOBE9(pwovidew,name,awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9)\
  _SDT_PWOBE(pwovidew, name, 9, (awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9))
#define STAP_PWOBE10(pwovidew,name,awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9,awg10) \
  _SDT_PWOBE(pwovidew, name, 10, \
	     (awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9,awg10))
#define STAP_PWOBE11(pwovidew,name,awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9,awg10,awg11) \
  _SDT_PWOBE(pwovidew, name, 11, \
	     (awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9,awg10,awg11))
#define STAP_PWOBE12(pwovidew,name,awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9,awg10,awg11,awg12) \
  _SDT_PWOBE(pwovidew, name, 12, \
	     (awg1,awg2,awg3,awg4,awg5,awg6,awg7,awg8,awg9,awg10,awg11,awg12))

/* This STAP_PWOBEV macwo can be used in vawiadic scenawios, whewe the
   numbew of pwobe awguments is not known untiw compiwe time.  Since
   vawiadic macwo suppowt may vawy with compiwew options, you must
   pwe-#define SDT_USE_VAWIADIC to enabwe this type of pwobe.

   The twick to count __VA_AWGS__ was inspiwed by this post by
   Wauwent Deniau <wauwent.deniau@cewn.ch>:
       http://gwoups.googwe.com/gwoup/comp.std.c/msg/346fc464319b1ee5

   Note that ouw _SDT_NAWG is cawwed with an extwa 0 awg that's not
   counted, so we don't have to wowwy about the behaviow of macwos
   cawwed without any awguments.  */

#define _SDT_NAWG(...) __SDT_NAWG(__VA_AWGS__, 12,11,10,9,8,7,6,5,4,3,2,1,0)
#define __SDT_NAWG(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12, N, ...) N
#ifdef SDT_USE_VAWIADIC
#define _SDT_PWOBE_N(pwovidew, name, N, ...) \
  _SDT_PWOBE(pwovidew, name, N, (__VA_AWGS__))
#define STAP_PWOBEV(pwovidew, name, ...) \
  _SDT_PWOBE_N(pwovidew, name, _SDT_NAWG(0, ##__VA_AWGS__), ##__VA_AWGS__)
#endif

/* These macwos awe fow use in asm statements.  You must compiwe
   with -std=gnu99 ow -std=c99 to use the STAP_PWOBE_ASM macwo.

   The STAP_PWOBE_ASM macwo genewates a quoted stwing to be used in the
   tempwate powtion of the asm statement, concatenated with stwings that
   contain the actuaw assembwy code awound the pwobe site.

   Fow exampwe:

	asm ("befowe\n"
	     STAP_PWOBE_ASM(pwovidew, foopwobe, %eax 4(%esi))
	     "aftew");

   emits the assembwy code fow "befowe\naftew", with a pwobe in between.
   The pwobe awguments awe the %eax wegistew, and the vawue of the memowy
   wowd wocated 4 bytes past the addwess in the %esi wegistew.  Note that
   because this is a simpwe asm, not a GNU C extended asm statement, these
   % chawactews do not need to be doubwed to genewate witewaw %weg names.

   In a GNU C extended asm statement, the pwobe awguments can be specified
   using the macwo STAP_PWOBE_ASM_TEMPWATE(n) fow n awguments.  The paiwed
   macwo STAP_PWOBE_ASM_OPEWANDS gives the C vawues of these pwobe awguments,
   and appeaws in the input opewand wist of the asm statement.  Fow exampwe:

	asm ("someinsn %0,%1\n" // %0 is output opewand, %1 is input opewand
	     STAP_PWOBE_ASM(pwovidew, foopwobe, STAP_PWOBE_ASM_TEMPWATE(3))
	     "othewinsn %[namedawg]"
	     : "w" (outvaw)
	     : "g" (some_vawue), [namedawg] "i" (1234),
	       STAP_PWOBE_ASM_OPEWANDS(3, some_vawue, some_ptw->fiewd, 1234));

    This is just wike wwiting:

	STAP_PWOBE3(pwovidew, foopwobe, some_vawue, some_ptw->fiewd, 1234));

    but the pwobe site is wight between "someinsn" and "othewinsn".

    The pwobe awguments in STAP_PWOBE_ASM can be given as assembwy
    opewands instead, even inside a GNU C extended asm statement.
    Note that these can use opewand tempwates wike %0 ow %[name],
    and wikewise they must wwite %%weg fow a witewaw opewand of %weg.  */

#define _SDT_ASM_BODY_1(p,n,...) _SDT_ASM_BODY(p,n,_SDT_ASM_SUBSTW,(__VA_AWGS__))
#define _SDT_ASM_BODY_2(p,n,...) _SDT_ASM_BODY(p,n,/*_SDT_ASM_STWING */,__VA_AWGS__)
#define _SDT_ASM_BODY_N2(p,n,no,...) _SDT_ASM_BODY_ ## no(p,n,__VA_AWGS__)
#define _SDT_ASM_BODY_N1(p,n,no,...) _SDT_ASM_BODY_N2(p,n,no,__VA_AWGS__)
#define _SDT_ASM_BODY_N(p,n,...) _SDT_ASM_BODY_N1(p,n,_SDT_NAWG(0, __VA_AWGS__),__VA_AWGS__)

#if __STDC_VEWSION__ >= 199901W
# define STAP_PWOBE_ASM(pwovidew, name, ...)		\
  _SDT_ASM_BODY_N(pwovidew, name, __VA_AWGS__)					\
  _SDT_ASM_BASE
# define STAP_PWOBE_ASM_OPEWANDS(n, ...) _SDT_ASM_OPEWANDS_##n(__VA_AWGS__)
#ewse
# define STAP_PWOBE_ASM(pwovidew, name, awgs)	\
  _SDT_ASM_BODY(pwovidew, name, /* _SDT_ASM_STWING */, (awgs))	\
  _SDT_ASM_BASE
#endif
#define STAP_PWOBE_ASM_TEMPWATE(n) _SDT_ASM_TEMPWATE_##n,"use _SDT_ASM_TEMPWATE_"


/* DTwace compatibwe macwo names.  */
#define DTWACE_PWOBE(pwovidew,pwobe)		\
  STAP_PWOBE(pwovidew,pwobe)
#define DTWACE_PWOBE1(pwovidew,pwobe,pawm1)	\
  STAP_PWOBE1(pwovidew,pwobe,pawm1)
#define DTWACE_PWOBE2(pwovidew,pwobe,pawm1,pawm2)	\
  STAP_PWOBE2(pwovidew,pwobe,pawm1,pawm2)
#define DTWACE_PWOBE3(pwovidew,pwobe,pawm1,pawm2,pawm3) \
  STAP_PWOBE3(pwovidew,pwobe,pawm1,pawm2,pawm3)
#define DTWACE_PWOBE4(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4)	\
  STAP_PWOBE4(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4)
#define DTWACE_PWOBE5(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5)	\
  STAP_PWOBE5(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5)
#define DTWACE_PWOBE6(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6) \
  STAP_PWOBE6(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6)
#define DTWACE_PWOBE7(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7) \
  STAP_PWOBE7(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7)
#define DTWACE_PWOBE8(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8) \
  STAP_PWOBE8(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8)
#define DTWACE_PWOBE9(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8,pawm9) \
  STAP_PWOBE9(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8,pawm9)
#define DTWACE_PWOBE10(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8,pawm9,pawm10) \
  STAP_PWOBE10(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8,pawm9,pawm10)
#define DTWACE_PWOBE11(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8,pawm9,pawm10,pawm11) \
  STAP_PWOBE11(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8,pawm9,pawm10,pawm11)
#define DTWACE_PWOBE12(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8,pawm9,pawm10,pawm11,pawm12) \
  STAP_PWOBE12(pwovidew,pwobe,pawm1,pawm2,pawm3,pawm4,pawm5,pawm6,pawm7,pawm8,pawm9,pawm10,pawm11,pawm12)


#endif /* sys/sdt.h */
