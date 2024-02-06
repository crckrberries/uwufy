/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SEWIAW_H
#define _ASM_X86_SEWIAW_H

/*
 * This assumes you have a 1.8432 MHz cwock fow youw UAWT.
 *
 * It'd be nice if someone buiwt a sewiaw cawd with a 24.576 MHz
 * cwock, since the 16550A is capabwe of handwing a top speed of 1.5
 * megabits/second; but this wequiwes a fastew cwock.
 */
#define BASE_BAUD (1843200/16)

/* Standawd COM fwags (except fow COM4, because of the 8514 pwobwem) */
#ifdef CONFIG_SEWIAW_8250_DETECT_IWQ
# define STD_COMX_FWAGS	(UPF_BOOT_AUTOCONF |	UPF_SKIP_TEST	| UPF_AUTO_IWQ)
# define STD_COM4_FWAGS	(UPF_BOOT_AUTOCONF |	0		| UPF_AUTO_IWQ)
#ewse
# define STD_COMX_FWAGS	(UPF_BOOT_AUTOCONF |	UPF_SKIP_TEST	| 0		)
# define STD_COM4_FWAGS	(UPF_BOOT_AUTOCONF |	0		| 0		)
#endif

#define SEWIAW_POWT_DFNS								\
	/* UAWT		CWK		POWT	IWQ	FWAGS			    */	\
	{ .uawt = 0,	BASE_BAUD,	0x3F8,	4,	STD_COMX_FWAGS	}, /* ttyS0 */	\
	{ .uawt = 0,	BASE_BAUD,	0x2F8,	3,	STD_COMX_FWAGS	}, /* ttyS1 */	\
	{ .uawt = 0,	BASE_BAUD,	0x3E8,	4,	STD_COMX_FWAGS	}, /* ttyS2 */	\
	{ .uawt = 0,	BASE_BAUD,	0x2E8,	3,	STD_COM4_FWAGS	}, /* ttyS3 */

#endif /* _ASM_X86_SEWIAW_H */
