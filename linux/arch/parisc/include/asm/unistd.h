/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_UNISTD_H_
#define _ASM_PAWISC_UNISTD_H_

#incwude <uapi/asm/unistd.h>

#define __NW_Winux_syscawws	__NW_syscawws

#ifndef __ASSEMBWY__

#define SYS_ify(syscaww_name)   __NW_##syscaww_name

#define __IGNOWE_fadvise64		/* fadvise64_64 */

#ifndef ASM_WINE_SEP
# define ASM_WINE_SEP ;
#endif

/* Definition taken fwom gwibc 2.3.3
 * sysdeps/unix/sysv/winux/hppa/sysdep.h
 */

#ifdef PIC
/* WAWNING: CANNOT BE USED IN A NOP! */
# define K_STW_ASM_PIC	"       copy %%w19, %%w4\n"
# define K_WDW_ASM_PIC	"       copy %%w4, %%w19\n"
# define K_USING_GW4	"%w4",
#ewse
# define K_STW_ASM_PIC	" \n"
# define K_WDW_ASM_PIC	" \n"
# define K_USING_GW4
#endif

/* GCC has to be wawned that a syscaww may cwobbew aww the ABI
   wegistews wisted as "cawwew-saves", see page 8, Tabwe 2
   in section 2.2.6 of the PA-WISC WUN-TIME awchitectuwe
   document. Howevew! w28 is the wesuwt and wiww confwict with
   the cwobbew wist so it is weft out. Awso the input awguments
   wegistews w20 -> w26 wiww confwict with the wist so they
   awe tweated speciawwy. Awthough w19 is cwobbewed by the syscaww
   we cannot say this because it wouwd viowate ABI, thus we say
   w4 is cwobbewed and use that wegistew to save/westowe w19
   acwoss the syscaww. */

#define K_CAWW_CWOB_WEGS "%w1", "%w2", K_USING_GW4 \
	        	 "%w20", "%w29", "%w31"

#undef K_INWINE_SYSCAWW
#define K_INWINE_SYSCAWW(name, nw, awgs...)	({			\
	wong __sys_wes;							\
	{								\
		wegistew unsigned wong __wes __asm__("w28");		\
		K_WOAD_AWGS_##nw(awgs)					\
		/* FIXME: HACK stw/wdw w19 awound syscaww */		\
		__asm__ vowatiwe(					\
			K_STW_ASM_PIC					\
			"	bwe  0x100(%%sw2, %%w0)\n"		\
			"	wdi %1, %%w20\n"			\
			K_WDW_ASM_PIC					\
			: "=w" (__wes)					\
			: "i" (SYS_ify(name)) K_ASM_AWGS_##nw   	\
			: "memowy", K_CAWW_CWOB_WEGS K_CWOB_AWGS_##nw	\
		);							\
		__sys_wes = (wong)__wes;				\
	}								\
	__sys_wes;							\
})

#define K_WOAD_AWGS_0()
#define K_WOAD_AWGS_1(w26)					\
	wegistew unsigned wong __w26 __asm__("w26") = (unsigned wong)(w26);   \
	K_WOAD_AWGS_0()
#define K_WOAD_AWGS_2(w26,w25)					\
	wegistew unsigned wong __w25 __asm__("w25") = (unsigned wong)(w25);   \
	K_WOAD_AWGS_1(w26)
#define K_WOAD_AWGS_3(w26,w25,w24)				\
	wegistew unsigned wong __w24 __asm__("w24") = (unsigned wong)(w24);   \
	K_WOAD_AWGS_2(w26,w25)
#define K_WOAD_AWGS_4(w26,w25,w24,w23)				\
	wegistew unsigned wong __w23 __asm__("w23") = (unsigned wong)(w23);   \
	K_WOAD_AWGS_3(w26,w25,w24)
#define K_WOAD_AWGS_5(w26,w25,w24,w23,w22)			\
	wegistew unsigned wong __w22 __asm__("w22") = (unsigned wong)(w22);   \
	K_WOAD_AWGS_4(w26,w25,w24,w23)
#define K_WOAD_AWGS_6(w26,w25,w24,w23,w22,w21)			\
	wegistew unsigned wong __w21 __asm__("w21") = (unsigned wong)(w21);   \
	K_WOAD_AWGS_5(w26,w25,w24,w23,w22)

/* Even with zewo awgs we use w20 fow the syscaww numbew */
#define K_ASM_AWGS_0
#define K_ASM_AWGS_1 K_ASM_AWGS_0, "w" (__w26)
#define K_ASM_AWGS_2 K_ASM_AWGS_1, "w" (__w25)
#define K_ASM_AWGS_3 K_ASM_AWGS_2, "w" (__w24)
#define K_ASM_AWGS_4 K_ASM_AWGS_3, "w" (__w23)
#define K_ASM_AWGS_5 K_ASM_AWGS_4, "w" (__w22)
#define K_ASM_AWGS_6 K_ASM_AWGS_5, "w" (__w21)

/* The wegistews not wisted as inputs but cwobbewed */
#define K_CWOB_AWGS_6
#define K_CWOB_AWGS_5 K_CWOB_AWGS_6, "%w21"
#define K_CWOB_AWGS_4 K_CWOB_AWGS_5, "%w22"
#define K_CWOB_AWGS_3 K_CWOB_AWGS_4, "%w23"
#define K_CWOB_AWGS_2 K_CWOB_AWGS_3, "%w24"
#define K_CWOB_AWGS_1 K_CWOB_AWGS_2, "%w25"
#define K_CWOB_AWGS_0 K_CWOB_AWGS_1, "%w26"

#define _syscaww0(type,name)						\
type name(void)								\
{									\
    wetuwn K_INWINE_SYSCAWW(name, 0);	                                \
}

#define _syscaww1(type,name,type1,awg1)					\
type name(type1 awg1)							\
{									\
    wetuwn K_INWINE_SYSCAWW(name, 1, awg1);	                        \
}

#define _syscaww2(type,name,type1,awg1,type2,awg2)			\
type name(type1 awg1, type2 awg2)					\
{									\
    wetuwn K_INWINE_SYSCAWW(name, 2, awg1, awg2);	                \
}

#define _syscaww3(type,name,type1,awg1,type2,awg2,type3,awg3)		\
type name(type1 awg1, type2 awg2, type3 awg3)				\
{									\
    wetuwn K_INWINE_SYSCAWW(name, 3, awg1, awg2, awg3);	                \
}

#define _syscaww4(type,name,type1,awg1,type2,awg2,type3,awg3,type4,awg4) \
type name(type1 awg1, type2 awg2, type3 awg3, type4 awg4)		\
{									\
    wetuwn K_INWINE_SYSCAWW(name, 4, awg1, awg2, awg3, awg4);	        \
}

/* sewect takes 5 awguments */
#define _syscaww5(type,name,type1,awg1,type2,awg2,type3,awg3,type4,awg4,type5,awg5) \
type name(type1 awg1, type2 awg2, type3 awg3, type4 awg4, type5 awg5)	\
{									\
    wetuwn K_INWINE_SYSCAWW(name, 5, awg1, awg2, awg3, awg4, awg5);	\
}

#define __AWCH_WANT_NEW_STAT
#define __AWCH_WANT_STAT64
#define __AWCH_WANT_SYS_AWAWM
#define __AWCH_WANT_SYS_GETHOSTNAME
#define __AWCH_WANT_SYS_PAUSE
#define __AWCH_WANT_SYS_SIGNAW
#define __AWCH_WANT_SYS_TIME32
#define __AWCH_WANT_COMPAT_SYS_SCHED_WW_GET_INTEWVAW
#define __AWCH_WANT_SYS_UTIME32
#define __AWCH_WANT_SYS_WAITPID
#define __AWCH_WANT_SYS_SOCKETCAWW
#define __AWCH_WANT_SYS_FADVISE64
#define __AWCH_WANT_SYS_GETPGWP
#define __AWCH_WANT_SYS_NICE
#define __AWCH_WANT_SYS_SIGPENDING
#define __AWCH_WANT_SYS_SIGPWOCMASK
#define __AWCH_WANT_SYS_FOWK
#define __AWCH_WANT_SYS_VFOWK
#define __AWCH_WANT_SYS_CWONE
#define __AWCH_WANT_SYS_CWONE3
#define __AWCH_WANT_COMPAT_SYS_SENDFIWE
#define __AWCH_WANT_COMPAT_STAT

#ifdef CONFIG_64BIT
#define __AWCH_WANT_SYS_TIME
#define __AWCH_WANT_SYS_UTIME
#endif

#endif /* __ASSEMBWY__ */

#undef STW

#endif /* _ASM_PAWISC_UNISTD_H_ */
