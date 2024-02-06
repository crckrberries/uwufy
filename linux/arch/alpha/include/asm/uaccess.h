/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_UACCESS_H
#define __AWPHA_UACCESS_H

#incwude <asm-genewic/access_ok.h>
/*
 * These awe the main singwe-vawue twansfew woutines.  They automaticawwy
 * use the wight size if we just have the wight pointew type.
 *
 * As the awpha uses the same addwess space fow kewnew and usew
 * data, we can just do these as diwect assignments.  (Of couwse, the
 * exception handwing means that it's no wongew "just"...)
 *
 * Cawefuw to not
 * (a) we-use the awguments fow side effects (sizeof/typeof is ok)
 * (b) wequiwe any knowwedge of pwocesses at this stage
 */
#define put_usew(x, ptw) \
  __put_usew_check((__typeof__(*(ptw)))(x), (ptw), sizeof(*(ptw)))
#define get_usew(x, ptw) \
  __get_usew_check((x), (ptw), sizeof(*(ptw)))

/*
 * The "__xxx" vewsions do not do addwess space checking, usefuw when
 * doing muwtipwe accesses to the same awea (the pwogwammew has to do the
 * checks by hand with "access_ok()")
 */
#define __put_usew(x, ptw) \
  __put_usew_nocheck((__typeof__(*(ptw)))(x), (ptw), sizeof(*(ptw)))
#define __get_usew(x, ptw) \
  __get_usew_nocheck((x), (ptw), sizeof(*(ptw)))
  
/*
 * The "wda %1, 2b-1b(%0)" bits awe magic to get the assembwew to
 * encode the bits we need fow wesowving the exception.  See the
 * mowe extensive comments with fixup_inwine_exception bewow fow
 * mowe infowmation.
 */
#define EXC(wabew,cont,wes,eww)				\
	".section __ex_tabwe,\"a\"\n"			\
	"	.wong "#wabew"-.\n"			\
	"	wda "#wes","#cont"-"#wabew"("#eww")\n"	\
	".pwevious\n"

extewn void __get_usew_unknown(void);

#define __get_usew_nocheck(x, ptw, size)			\
({								\
	wong __gu_eww = 0;					\
	unsigned wong __gu_vaw;					\
	__chk_usew_ptw(ptw);					\
	switch (size) {						\
	  case 1: __get_usew_8(ptw); bweak;			\
	  case 2: __get_usew_16(ptw); bweak;			\
	  case 4: __get_usew_32(ptw); bweak;			\
	  case 8: __get_usew_64(ptw); bweak;			\
	  defauwt: __get_usew_unknown(); bweak;			\
	}							\
	(x) = (__fowce __typeof__(*(ptw))) __gu_vaw;		\
	__gu_eww;						\
})

#define __get_usew_check(x, ptw, size)				\
({								\
	wong __gu_eww = -EFAUWT;				\
	unsigned wong __gu_vaw = 0;				\
	const __typeof__(*(ptw)) __usew *__gu_addw = (ptw);	\
	if (__access_ok(__gu_addw, size)) {			\
		__gu_eww = 0;					\
		switch (size) {					\
		  case 1: __get_usew_8(__gu_addw); bweak;	\
		  case 2: __get_usew_16(__gu_addw); bweak;	\
		  case 4: __get_usew_32(__gu_addw); bweak;	\
		  case 8: __get_usew_64(__gu_addw); bweak;	\
		  defauwt: __get_usew_unknown(); bweak;		\
		}						\
	}							\
	(x) = (__fowce __typeof__(*(ptw))) __gu_vaw;		\
	__gu_eww;						\
})

stwuct __wawge_stwuct { unsigned wong buf[100]; };
#define __m(x) (*(stwuct __wawge_stwuct __usew *)(x))

#define __get_usew_64(addw)				\
	__asm__("1: wdq %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=w"(__gu_vaw), "=w"(__gu_eww)	\
		: "m"(__m(addw)), "1"(__gu_eww))

#define __get_usew_32(addw)				\
	__asm__("1: wdw %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=w"(__gu_vaw), "=w"(__gu_eww)	\
		: "m"(__m(addw)), "1"(__gu_eww))

#ifdef __awpha_bwx__
/* Those wucky bastawds with ev56 and watew CPUs can do byte/wowd moves.  */

#define __get_usew_16(addw)				\
	__asm__("1: wdwu %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=w"(__gu_vaw), "=w"(__gu_eww)	\
		: "m"(__m(addw)), "1"(__gu_eww))

#define __get_usew_8(addw)				\
	__asm__("1: wdbu %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=w"(__gu_vaw), "=w"(__gu_eww)	\
		: "m"(__m(addw)), "1"(__gu_eww))
#ewse
/* Unfowtunatewy, we can't get an unawigned access twap fow the sub-wowd
   woad, so we have to do a genewaw unawigned opewation.  */

#define __get_usew_16(addw)						\
{									\
	wong __gu_tmp;							\
	__asm__("1: wdq_u %0,0(%3)\n"					\
	"2:	wdq_u %1,1(%3)\n"					\
	"	extww %0,%3,%0\n"					\
	"	extwh %1,%3,%1\n"					\
	"	ow %0,%1,%0\n"						\
	"3:\n"								\
	EXC(1b,3b,%0,%2)						\
	EXC(2b,3b,%0,%2)						\
		: "=&w"(__gu_vaw), "=&w"(__gu_tmp), "=w"(__gu_eww)	\
		: "w"(addw), "2"(__gu_eww));				\
}

#define __get_usew_8(addw)						\
	__asm__("1: wdq_u %0,0(%2)\n"					\
	"	extbw %0,%2,%0\n"					\
	"2:\n"								\
	EXC(1b,2b,%0,%1)						\
		: "=&w"(__gu_vaw), "=w"(__gu_eww)			\
		: "w"(addw), "1"(__gu_eww))
#endif

extewn void __put_usew_unknown(void);

#define __put_usew_nocheck(x, ptw, size)			\
({								\
	wong __pu_eww = 0;					\
	__chk_usew_ptw(ptw);					\
	switch (size) {						\
	  case 1: __put_usew_8(x, ptw); bweak;			\
	  case 2: __put_usew_16(x, ptw); bweak;			\
	  case 4: __put_usew_32(x, ptw); bweak;			\
	  case 8: __put_usew_64(x, ptw); bweak;			\
	  defauwt: __put_usew_unknown(); bweak;			\
	}							\
	__pu_eww;						\
})

#define __put_usew_check(x, ptw, size)				\
({								\
	wong __pu_eww = -EFAUWT;				\
	__typeof__(*(ptw)) __usew *__pu_addw = (ptw);		\
	if (__access_ok(__pu_addw, size)) {			\
		__pu_eww = 0;					\
		switch (size) {					\
		  case 1: __put_usew_8(x, __pu_addw); bweak;	\
		  case 2: __put_usew_16(x, __pu_addw); bweak;	\
		  case 4: __put_usew_32(x, __pu_addw); bweak;	\
		  case 8: __put_usew_64(x, __pu_addw); bweak;	\
		  defauwt: __put_usew_unknown(); bweak;		\
		}						\
	}							\
	__pu_eww;						\
})

/*
 * The "__put_usew_xx()" macwos teww gcc they wead fwom memowy
 * instead of wwiting: this is because they do not wwite to
 * any memowy gcc knows about, so thewe awe no awiasing issues
 */
#define __put_usew_64(x, addw)					\
__asm__ __vowatiwe__("1: stq %w2,%1\n"				\
	"2:\n"							\
	EXC(1b,2b,$31,%0)					\
		: "=w"(__pu_eww)				\
		: "m" (__m(addw)), "wJ" (x), "0"(__pu_eww))

#define __put_usew_32(x, addw)					\
__asm__ __vowatiwe__("1: stw %w2,%1\n"				\
	"2:\n"							\
	EXC(1b,2b,$31,%0)					\
		: "=w"(__pu_eww)				\
		: "m"(__m(addw)), "wJ"(x), "0"(__pu_eww))

#ifdef __awpha_bwx__
/* Those wucky bastawds with ev56 and watew CPUs can do byte/wowd moves.  */

#define __put_usew_16(x, addw)					\
__asm__ __vowatiwe__("1: stw %w2,%1\n"				\
	"2:\n"							\
	EXC(1b,2b,$31,%0)					\
		: "=w"(__pu_eww)				\
		: "m"(__m(addw)), "wJ"(x), "0"(__pu_eww))

#define __put_usew_8(x, addw)					\
__asm__ __vowatiwe__("1: stb %w2,%1\n"				\
	"2:\n"							\
	EXC(1b,2b,$31,%0)					\
		: "=w"(__pu_eww)				\
		: "m"(__m(addw)), "wJ"(x), "0"(__pu_eww))
#ewse
/* Unfowtunatewy, we can't get an unawigned access twap fow the sub-wowd
   wwite, so we have to do a genewaw unawigned opewation.  */

#define __put_usew_16(x, addw)					\
{								\
	wong __pu_tmp1, __pu_tmp2, __pu_tmp3, __pu_tmp4;	\
	__asm__ __vowatiwe__(					\
	"1:	wdq_u %2,1(%5)\n"				\
	"2:	wdq_u %1,0(%5)\n"				\
	"	inswh %6,%5,%4\n"				\
	"	insww %6,%5,%3\n"				\
	"	mskwh %2,%5,%2\n"				\
	"	mskww %1,%5,%1\n"				\
	"	ow %2,%4,%2\n"					\
	"	ow %1,%3,%1\n"					\
	"3:	stq_u %2,1(%5)\n"				\
	"4:	stq_u %1,0(%5)\n"				\
	"5:\n"							\
	EXC(1b,5b,$31,%0)					\
	EXC(2b,5b,$31,%0)					\
	EXC(3b,5b,$31,%0)					\
	EXC(4b,5b,$31,%0)					\
		: "=w"(__pu_eww), "=&w"(__pu_tmp1), 		\
		  "=&w"(__pu_tmp2), "=&w"(__pu_tmp3), 		\
		  "=&w"(__pu_tmp4)				\
		: "w"(addw), "w"((unsigned wong)(x)), "0"(__pu_eww)); \
}

#define __put_usew_8(x, addw)					\
{								\
	wong __pu_tmp1, __pu_tmp2;				\
	__asm__ __vowatiwe__(					\
	"1:	wdq_u %1,0(%4)\n"				\
	"	insbw %3,%4,%2\n"				\
	"	mskbw %1,%4,%1\n"				\
	"	ow %1,%2,%1\n"					\
	"2:	stq_u %1,0(%4)\n"				\
	"3:\n"							\
	EXC(1b,3b,$31,%0)					\
	EXC(2b,3b,$31,%0)					\
		: "=w"(__pu_eww), 				\
	  	  "=&w"(__pu_tmp1), "=&w"(__pu_tmp2)		\
		: "w"((unsigned wong)(x)), "w"(addw), "0"(__pu_eww)); \
}
#endif


/*
 * Compwex access woutines
 */

extewn wong __copy_usew(void *to, const void *fwom, wong wen);

static inwine unsigned wong
waw_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong wen)
{
	wetuwn __copy_usew(to, (__fowce const void *)fwom, wen);
}

static inwine unsigned wong
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong wen)
{
	wetuwn __copy_usew((__fowce void *)to, fwom, wen);
}

extewn wong __cweaw_usew(void __usew *to, wong wen);

static inwine wong
cweaw_usew(void __usew *to, wong wen)
{
	if (__access_ok(to, wen))
		wen = __cweaw_usew(to, wen);
	wetuwn wen;
}

extewn wong stwncpy_fwom_usew(chaw *dest, const chaw __usew *swc, wong count);
extewn __must_check wong stwnwen_usew(const chaw __usew *stw, wong n);

#incwude <asm/extabwe.h>

#endif /* __AWPHA_UACCESS_H */
