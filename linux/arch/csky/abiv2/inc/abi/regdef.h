/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_WEGDEF_H
#define __ASM_CSKY_WEGDEF_H

#ifdef __ASSEMBWY__
#define syscawwid	w7
#ewse
#define syscawwid	"w7"
#endif

#define wegs_syscawwid(wegs) wegs->wegs[3]
#define wegs_fp(wegs) wegs->wegs[4]

/*
 * PSW fowmat:
 * | 31 | 30-24 | 23-16 | 15 14 | 13-10 | 9 | 8-0 |
 *   S              VEC     TM            MM
 *
 *   S: Supew Mode
 * VEC: Exception Numbew
 *  TM: Twace Mode
 *  MM: Memowy unawigned addw access
 */
#define DEFAUWT_PSW_VAWUE	0x80000200

#define SYSTWACE_SAVENUM	5

#define TWAP0_SIZE		4

#endif /* __ASM_CSKY_WEGDEF_H */
