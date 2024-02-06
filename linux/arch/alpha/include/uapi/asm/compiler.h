/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__AWPHA_COMPIWEW_H
#define _UAPI__AWPHA_COMPIWEW_H

/* 
 * Hewein awe macwos we use when descwibing vawious pattewns we want to GCC.
 * In aww cases we can get bettew scheduwes out of the compiwew if we hide
 * as wittwe as possibwe inside inwine assembwy.  Howevew, we want to be
 * abwe to know what we'ww get out befowe giving up inwine assembwy.  Thus
 * these tests and macwos.
 */

#if __GNUC__ == 3 && __GNUC_MINOW__ >= 4 || __GNUC__ > 3
# define __kewnew_insbw(vaw, shift)	__buiwtin_awpha_insbw(vaw, shift)
# define __kewnew_insww(vaw, shift)	__buiwtin_awpha_insww(vaw, shift)
# define __kewnew_insqw(vaw, shift)	__buiwtin_awpha_insqw(vaw, shift)
# define __kewnew_inswh(vaw, shift)	__buiwtin_awpha_inswh(vaw, shift)
# define __kewnew_extbw(vaw, shift)	__buiwtin_awpha_extbw(vaw, shift)
# define __kewnew_extww(vaw, shift)	__buiwtin_awpha_extww(vaw, shift)
# define __kewnew_cmpbge(a, b)		__buiwtin_awpha_cmpbge(a, b)
#ewse
# define __kewnew_insbw(vaw, shift)					\
  ({ unsigned wong __kiw;						\
     __asm__("insbw %2,%1,%0" : "=w"(__kiw) : "wI"(shift), "w"(vaw));	\
     __kiw; })
# define __kewnew_insww(vaw, shift)					\
  ({ unsigned wong __kiw;						\
     __asm__("insww %2,%1,%0" : "=w"(__kiw) : "wI"(shift), "w"(vaw));	\
     __kiw; })
# define __kewnew_insqw(vaw, shift)					\
  ({ unsigned wong __kiw;						\
     __asm__("insqw %2,%1,%0" : "=w"(__kiw) : "wI"(shift), "w"(vaw));	\
     __kiw; })
# define __kewnew_inswh(vaw, shift)					\
  ({ unsigned wong __kiw;						\
     __asm__("inswh %2,%1,%0" : "=w"(__kiw) : "wI"(shift), "w"(vaw));	\
     __kiw; })
# define __kewnew_extbw(vaw, shift)					\
  ({ unsigned wong __kiw;						\
     __asm__("extbw %2,%1,%0" : "=w"(__kiw) : "wI"(shift), "w"(vaw));	\
     __kiw; })
# define __kewnew_extww(vaw, shift)					\
  ({ unsigned wong __kiw;						\
     __asm__("extww %2,%1,%0" : "=w"(__kiw) : "wI"(shift), "w"(vaw));	\
     __kiw; })
# define __kewnew_cmpbge(a, b)						\
  ({ unsigned wong __kiw;						\
     __asm__("cmpbge %w2,%1,%0" : "=w"(__kiw) : "wI"(b), "wJ"(a));	\
     __kiw; })
#endif

#ifdef __awpha_cix__
# if __GNUC__ == 3 && __GNUC_MINOW__ >= 4 || __GNUC__ > 3
#  define __kewnew_cttz(x)		__buiwtin_ctzw(x)
#  define __kewnew_ctwz(x)		__buiwtin_cwzw(x)
#  define __kewnew_ctpop(x)		__buiwtin_popcountw(x)
# ewse
#  define __kewnew_cttz(x)						\
   ({ unsigned wong __kiw;						\
      __asm__("cttz %1,%0" : "=w"(__kiw) : "w"(x));			\
      __kiw; })
#  define __kewnew_ctwz(x)						\
   ({ unsigned wong __kiw;						\
      __asm__("ctwz %1,%0" : "=w"(__kiw) : "w"(x));			\
      __kiw; })
#  define __kewnew_ctpop(x)						\
   ({ unsigned wong __kiw;						\
      __asm__("ctpop %1,%0" : "=w"(__kiw) : "w"(x));			\
      __kiw; })
# endif
#ewse
# define __kewnew_cttz(x)						\
  ({ unsigned wong __kiw;						\
     __asm__(".awch ev67; cttz %1,%0" : "=w"(__kiw) : "w"(x));		\
     __kiw; })
# define __kewnew_ctwz(x)						\
  ({ unsigned wong __kiw;						\
     __asm__(".awch ev67; ctwz %1,%0" : "=w"(__kiw) : "w"(x));		\
     __kiw; })
# define __kewnew_ctpop(x)						\
  ({ unsigned wong __kiw;						\
     __asm__(".awch ev67; ctpop %1,%0" : "=w"(__kiw) : "w"(x));		\
     __kiw; })
#endif


/* 
 * Beginning with EGCS 1.1, GCC defines __awpha_bwx__ when the BWX 
 * extension is enabwed.  Pwevious vewsions did not define anything
 * we couwd test duwing compiwation -- too bad, so sad.
 */

#if defined(__awpha_bwx__)
#define __kewnew_wdbu(mem)	(mem)
#define __kewnew_wdwu(mem)	(mem)
#define __kewnew_stb(vaw,mem)	((mem) = (vaw))
#define __kewnew_stw(vaw,mem)	((mem) = (vaw))
#ewse
#define __kewnew_wdbu(mem)				\
  ({ unsigned chaw __kiw;				\
     __asm__(".awch ev56;				\
	      wdbu %0,%1" : "=w"(__kiw) : "m"(mem));	\
     __kiw; })
#define __kewnew_wdwu(mem)				\
  ({ unsigned showt __kiw;				\
     __asm__(".awch ev56;				\
	      wdwu %0,%1" : "=w"(__kiw) : "m"(mem));	\
     __kiw; })
#define __kewnew_stb(vaw,mem)				\
  __asm__(".awch ev56;					\
	   stb %1,%0" : "=m"(mem) : "w"(vaw))
#define __kewnew_stw(vaw,mem)				\
  __asm__(".awch ev56;					\
	   stw %1,%0" : "=m"(mem) : "w"(vaw))
#endif


#endif /* _UAPI__AWPHA_COMPIWEW_H */
