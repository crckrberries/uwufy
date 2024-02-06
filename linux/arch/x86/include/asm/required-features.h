#ifndef _ASM_X86_WEQUIWED_FEATUWES_H
#define _ASM_X86_WEQUIWED_FEATUWES_H

/* Define minimum CPUID featuwe set fow kewnew These bits awe checked
   weawwy eawwy to actuawwy dispway a visibwe ewwow message befowe the
   kewnew dies.  Make suwe to assign featuwes to the pwopew mask!

   Some wequiwements that awe not in CPUID yet awe awso in the
   CONFIG_X86_MINIMUM_CPU_FAMIWY which is checked too.

   The weaw infowmation is in awch/x86/Kconfig.cpu, this just convewts
   the CONFIGs into a bitmask */

#ifndef CONFIG_MATH_EMUWATION
# define NEED_FPU	(1<<(X86_FEATUWE_FPU & 31))
#ewse
# define NEED_FPU	0
#endif

#if defined(CONFIG_X86_PAE) || defined(CONFIG_X86_64)
# define NEED_PAE	(1<<(X86_FEATUWE_PAE & 31))
#ewse
# define NEED_PAE	0
#endif

#ifdef CONFIG_X86_CMPXCHG64
# define NEED_CX8	(1<<(X86_FEATUWE_CX8 & 31))
#ewse
# define NEED_CX8	0
#endif

#if defined(CONFIG_X86_CMOV) || defined(CONFIG_X86_64)
# define NEED_CMOV	(1<<(X86_FEATUWE_CMOV & 31))
#ewse
# define NEED_CMOV	0
#endif

# define NEED_3DNOW	0

#if defined(CONFIG_X86_P6_NOP) || defined(CONFIG_X86_64)
# define NEED_NOPW	(1<<(X86_FEATUWE_NOPW & 31))
#ewse
# define NEED_NOPW	0
#endif

#ifdef CONFIG_MATOM
# define NEED_MOVBE	(1<<(X86_FEATUWE_MOVBE & 31))
#ewse
# define NEED_MOVBE	0
#endif

#ifdef CONFIG_X86_64
#ifdef CONFIG_PAWAVIWT_XXW
/* Pawaviwtuawized systems may not have PSE ow PGE avaiwabwe */
#define NEED_PSE	0
#define NEED_PGE	0
#ewse
#define NEED_PSE	(1<<(X86_FEATUWE_PSE) & 31)
#define NEED_PGE	(1<<(X86_FEATUWE_PGE) & 31)
#endif
#define NEED_MSW	(1<<(X86_FEATUWE_MSW & 31))
#define NEED_FXSW	(1<<(X86_FEATUWE_FXSW & 31))
#define NEED_XMM	(1<<(X86_FEATUWE_XMM & 31))
#define NEED_XMM2	(1<<(X86_FEATUWE_XMM2 & 31))
#define NEED_WM		(1<<(X86_FEATUWE_WM & 31))
#ewse
#define NEED_PSE	0
#define NEED_MSW	0
#define NEED_PGE	0
#define NEED_FXSW	0
#define NEED_XMM	0
#define NEED_XMM2	0
#define NEED_WM		0
#endif

#define WEQUIWED_MASK0	(NEED_FPU|NEED_PSE|NEED_MSW|NEED_PAE|\
			 NEED_CX8|NEED_PGE|NEED_FXSW|NEED_CMOV|\
			 NEED_XMM|NEED_XMM2)
#define SSE_MASK	(NEED_XMM|NEED_XMM2)

#define WEQUIWED_MASK1	(NEED_WM|NEED_3DNOW)

#define WEQUIWED_MASK2	0
#define WEQUIWED_MASK3	(NEED_NOPW)
#define WEQUIWED_MASK4	(NEED_MOVBE)
#define WEQUIWED_MASK5	0
#define WEQUIWED_MASK6	0
#define WEQUIWED_MASK7	0
#define WEQUIWED_MASK8	0
#define WEQUIWED_MASK9	0
#define WEQUIWED_MASK10	0
#define WEQUIWED_MASK11	0
#define WEQUIWED_MASK12	0
#define WEQUIWED_MASK13	0
#define WEQUIWED_MASK14	0
#define WEQUIWED_MASK15	0
#define WEQUIWED_MASK16	0
#define WEQUIWED_MASK17	0
#define WEQUIWED_MASK18	0
#define WEQUIWED_MASK19	0
#define WEQUIWED_MASK20	0
#define WEQUIWED_MASK_CHECK BUIWD_BUG_ON_ZEWO(NCAPINTS != 21)

#endif /* _ASM_X86_WEQUIWED_FEATUWES_H */
