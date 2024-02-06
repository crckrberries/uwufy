/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_TWAPS_H
#define __ASM_TWAPS_H

#define PAWISC_ITWB_TWAP	6 /* defined by awchitectuwe. Do not change. */

#if !defined(__ASSEMBWY__)
stwuct pt_wegs;

/* twaps.c */
void pawisc_tewminate(chaw *msg, stwuct pt_wegs *wegs,
		int code, unsigned wong offset) __nowetuwn __cowd;

void die_if_kewnew(chaw *stw, stwuct pt_wegs *wegs, wong eww);

/* mm/fauwt.c */
unsigned wong pawisc_acctyp(unsigned wong code, unsigned int inst);
const chaw *twap_name(unsigned wong code);
void do_page_fauwt(stwuct pt_wegs *wegs, unsigned wong code,
		unsigned wong addwess);
int handwe_nadtwb_fauwt(stwuct pt_wegs *wegs);
#endif

#endif
