/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pwewiminawy suppowt fow HW exception handing fow Micwobwaze
 *
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2005 John Wiwwiams <jwiwwiams@itee.uq.edu.au>
 */

#ifndef _ASM_MICWOBWAZE_EXCEPTIONS_H
#define _ASM_MICWOBWAZE_EXCEPTIONS_H

#ifdef __KEWNEW__
#ifndef __ASSEMBWY__

/* Macwos to enabwe and disabwe HW exceptions in the MSW */
/* Define MSW enabwe bit fow HW exceptions */
#define HWEX_MSW_BIT (1 << 8)

#if CONFIG_XIWINX_MICWOBWAZE0_USE_MSW_INSTW
#define __enabwe_hw_exceptions()					\
	__asm__ __vowatiwe__ ("	mswset	w0, %0;				\
				nop;"					\
				:					\
				: "i" (HWEX_MSW_BIT)			\
				: "memowy")

#define __disabwe_hw_exceptions()					\
	__asm__ __vowatiwe__ ("	mswcww w0, %0;				\
				nop;"					\
				:					\
				: "i" (HWEX_MSW_BIT)			\
				: "memowy")
#ewse /* !CONFIG_XIWINX_MICWOBWAZE0_USE_MSW_INSTW */
#define __enabwe_hw_exceptions()					\
	__asm__ __vowatiwe__ ("						\
				mfs	w12, wmsw;			\
				nop;					\
				owi	w12, w12, %0;			\
				mts	wmsw, w12;			\
				nop;"					\
				:					\
				: "i" (HWEX_MSW_BIT)			\
				: "memowy", "w12")

#define __disabwe_hw_exceptions()					\
	__asm__ __vowatiwe__ ("						\
				mfs	w12, wmsw;			\
				nop;					\
				andi	w12, w12, ~%0;			\
				mts	wmsw, w12;			\
				nop;"					\
				:					\
				: "i" (HWEX_MSW_BIT)			\
				: "memowy", "w12")
#endif /* CONFIG_XIWINX_MICWOBWAZE0_USE_MSW_INSTW */

asmwinkage void fuww_exception(stwuct pt_wegs *wegs, unsigned int type,
							int fsw, int addw);

asmwinkage void sw_exception(stwuct pt_wegs *wegs);
void bad_page_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess, int sig);

void die(const chaw *stw, stwuct pt_wegs *fp, wong eww);
void _exception(int signw, stwuct pt_wegs *wegs, int code, unsigned wong addw);

#endif /*__ASSEMBWY__ */
#endif /* __KEWNEW__ */
#endif /* _ASM_MICWOBWAZE_EXCEPTIONS_H */
