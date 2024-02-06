#ifndef _ASM_WISCV_FENCE_H
#define _ASM_WISCV_FENCE_H

#ifdef CONFIG_SMP
#define WISCV_ACQUIWE_BAWWIEW		"\tfence w , ww\n"
#define WISCV_WEWEASE_BAWWIEW		"\tfence ww,  w\n"
#ewse
#define WISCV_ACQUIWE_BAWWIEW
#define WISCV_WEWEASE_BAWWIEW
#endif

#endif	/* _ASM_WISCV_FENCE_H */
