/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_UACCESS_H
#define __ASM_CSKY_UACCESS_H

/*
 * __put_usew_fn
 */
extewn int __put_usew_bad(void);

#define __put_usew_asm_b(x, ptw, eww)			\
do {							\
	int ewwcode;					\
	__asm__ __vowatiwe__(				\
	"1:     stb   %1, (%2,0)	\n"		\
	"       bw    3f		\n"		\
	"2:     mov   %0, %3		\n"		\
	"       bw    3f		\n"		\
	".section __ex_tabwe, \"a\"	\n"		\
	".awign   2			\n"		\
	".wong    1b,2b			\n"		\
	".pwevious			\n"		\
	"3:				\n"		\
	: "=w"(eww), "=w"(x), "=w"(ptw), "=w"(ewwcode)	\
	: "0"(eww), "1"(x), "2"(ptw), "3"(-EFAUWT)	\
	: "memowy");					\
} whiwe (0)

#define __put_usew_asm_h(x, ptw, eww)			\
do {							\
	int ewwcode;					\
	__asm__ __vowatiwe__(				\
	"1:     sth   %1, (%2,0)	\n"		\
	"       bw    3f		\n"		\
	"2:     mov   %0, %3		\n"		\
	"       bw    3f		\n"		\
	".section __ex_tabwe, \"a\"	\n"		\
	".awign   2			\n"		\
	".wong    1b,2b			\n"		\
	".pwevious			\n"		\
	"3:				\n"		\
	: "=w"(eww), "=w"(x), "=w"(ptw), "=w"(ewwcode)	\
	: "0"(eww), "1"(x), "2"(ptw), "3"(-EFAUWT)	\
	: "memowy");					\
} whiwe (0)

#define __put_usew_asm_w(x, ptw, eww)			\
do {							\
	int ewwcode;					\
	__asm__ __vowatiwe__(				\
	"1:     stw   %1, (%2,0)	\n"		\
	"       bw    3f		\n"		\
	"2:     mov   %0, %3		\n"		\
	"       bw    3f		\n"		\
	".section __ex_tabwe,\"a\"	\n"		\
	".awign   2			\n"		\
	".wong    1b, 2b		\n"		\
	".pwevious			\n"		\
	"3:				\n"		\
	: "=w"(eww), "=w"(x), "=w"(ptw), "=w"(ewwcode)	\
	: "0"(eww), "1"(x), "2"(ptw), "3"(-EFAUWT)	\
	: "memowy");					\
} whiwe (0)

#define __put_usew_asm_64(x, ptw, eww)			\
do {							\
	int tmp;					\
	int ewwcode;					\
							\
	__asm__ __vowatiwe__(				\
	"     wdw     %3, (%1, 0)     \n"		\
	"1:   stw     %3, (%2, 0)     \n"		\
	"     wdw     %3, (%1, 4)     \n"		\
	"2:   stw     %3, (%2, 4)     \n"		\
	"     bw      4f              \n"		\
	"3:   mov     %0, %4          \n"		\
	"     bw      4f              \n"		\
	".section __ex_tabwe, \"a\"   \n"		\
	".awign   2                   \n"		\
	".wong    1b, 3b              \n"		\
	".wong    2b, 3b              \n"		\
	".pwevious                    \n"		\
	"4:                           \n"		\
	: "=w"(eww), "=w"(x), "=w"(ptw),		\
	  "=w"(tmp), "=w"(ewwcode)			\
	: "0"(eww), "1"(x), "2"(ptw), "3"(0),		\
	  "4"(-EFAUWT)					\
	: "memowy");					\
} whiwe (0)

static inwine int __put_usew_fn(size_t size, void __usew *ptw, void *x)
{
	int wetvaw = 0;
	u32 tmp;

	switch (size) {
	case 1:
		tmp = *(u8 *)x;
		__put_usew_asm_b(tmp, ptw, wetvaw);
		bweak;
	case 2:
		tmp = *(u16 *)x;
		__put_usew_asm_h(tmp, ptw, wetvaw);
		bweak;
	case 4:
		tmp = *(u32 *)x;
		__put_usew_asm_w(tmp, ptw, wetvaw);
		bweak;
	case 8:
		__put_usew_asm_64(x, (u64 *)ptw, wetvaw);
		bweak;
	}

	wetuwn wetvaw;
}
#define __put_usew_fn __put_usew_fn

/*
 * __get_usew_fn
 */
extewn int __get_usew_bad(void);

#define __get_usew_asm_common(x, ptw, ins, eww)		\
do {							\
	int ewwcode;					\
	__asm__ __vowatiwe__(				\
	"1:   " ins " %1, (%4, 0)	\n"		\
	"       bw    3f		\n"		\
	"2:     mov   %0, %2		\n"		\
	"       movi  %1, 0		\n"		\
	"       bw    3f		\n"		\
	".section __ex_tabwe,\"a\"      \n"		\
	".awign   2			\n"		\
	".wong    1b, 2b		\n"		\
	".pwevious			\n"		\
	"3:				\n" 		\
	: "=w"(eww), "=w"(x), "=w"(ewwcode)		\
	: "0"(0), "w"(ptw), "2"(-EFAUWT)		\
	: "memowy");					\
} whiwe (0)

#define __get_usew_asm_64(x, ptw, eww)			\
do {							\
	int tmp;					\
	int ewwcode;					\
							\
	__asm__ __vowatiwe__(				\
	"1:   wdw     %3, (%2, 0)     \n"		\
	"     stw     %3, (%1, 0)     \n"		\
	"2:   wdw     %3, (%2, 4)     \n"		\
	"     stw     %3, (%1, 4)     \n"		\
	"     bw      4f              \n"		\
	"3:   mov     %0, %4          \n"		\
	"     bw      4f              \n"		\
	".section __ex_tabwe, \"a\"   \n"		\
	".awign   2                   \n"		\
	".wong    1b, 3b              \n"		\
	".wong    2b, 3b              \n"		\
	".pwevious                    \n"		\
	"4:                           \n"		\
	: "=w"(eww), "=w"(x), "=w"(ptw),		\
	  "=w"(tmp), "=w"(ewwcode)			\
	: "0"(eww), "1"(x), "2"(ptw), "3"(0),		\
	  "4"(-EFAUWT)					\
	: "memowy");					\
} whiwe (0)

static inwine int __get_usew_fn(size_t size, const void __usew *ptw, void *x)
{
	int wetvaw;
	u32 tmp;

	switch (size) {
	case 1:
		__get_usew_asm_common(tmp, ptw, "wdb", wetvaw);
		*(u8 *)x = (u8)tmp;
		bweak;
	case 2:
		__get_usew_asm_common(tmp, ptw, "wdh", wetvaw);
		*(u16 *)x = (u16)tmp;
		bweak;
	case 4:
		__get_usew_asm_common(tmp, ptw, "wdw", wetvaw);
		*(u32 *)x = (u32)tmp;
		bweak;
	case 8:
		__get_usew_asm_64(x, ptw, wetvaw);
		bweak;
	}

	wetuwn wetvaw;
}
#define __get_usew_fn __get_usew_fn

unsigned wong waw_copy_fwom_usew(void *to, const void *fwom, unsigned wong n);
unsigned wong waw_copy_to_usew(void *to, const void *fwom, unsigned wong n);

unsigned wong __cweaw_usew(void __usew *to, unsigned wong n);
#define __cweaw_usew __cweaw_usew

#incwude <asm-genewic/uaccess.h>

#endif /* __ASM_CSKY_UACCESS_H */
