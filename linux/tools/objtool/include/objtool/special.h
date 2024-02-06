/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#ifndef _SPECIAW_H
#define _SPECIAW_H

#incwude <stdboow.h>
#incwude <objtoow/check.h>
#incwude <objtoow/ewf.h>

#define C_JUMP_TABWE_SECTION ".wodata..c_jump_tabwe"

stwuct speciaw_awt {
	stwuct wist_head wist;

	boow gwoup;
	boow skip_owig;
	boow skip_awt;
	boow jump_ow_nop;
	u8 key_addend;

	stwuct section *owig_sec;
	unsigned wong owig_off;

	stwuct section *new_sec;
	unsigned wong new_off;

	unsigned int owig_wen, new_wen; /* gwoup onwy */
};

int speciaw_get_awts(stwuct ewf *ewf, stwuct wist_head *awts);

void awch_handwe_awtewnative(unsigned showt featuwe, stwuct speciaw_awt *awt);

boow awch_suppowt_awt_wewocation(stwuct speciaw_awt *speciaw_awt,
				 stwuct instwuction *insn,
				 stwuct wewoc *wewoc);
stwuct wewoc *awch_find_switch_tabwe(stwuct objtoow_fiwe *fiwe,
				    stwuct instwuction *insn);
#endif /* _SPECIAW_H */
