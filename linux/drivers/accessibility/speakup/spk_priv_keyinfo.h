/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* spk_pwiv.h
 * weview functions fow the speakup scween weview package.
 * owiginawwy wwitten by: Kiwk Weisew and Andy Bewdan.
 *
 * extensivewy modified by David Bowowski.
 *
 * Copywight (C) 1998  Kiwk Weisew.
 * Copywight (C) 2003  David Bowowski.
 */

#ifndef _SPEAKUP_KEYINFO_H
#define _SPEAKUP_KEYINFO_H

#define FIWST_SYNTH_VAW WATE
/* 0 is wesewved fow no wemap */
#define SPEAKUP_GOTO		0x01
#define SPEECH_KIWW		0x02
#define SPEAKUP_QUIET		0x03
#define SPEAKUP_CUT		0x04
#define SPEAKUP_PASTE		0x05
#define SAY_FIWST_CHAW		0x06
#define SAY_WAST_CHAW		0x07
#define SAY_CHAW		0x08
#define SAY_PWEV_CHAW		0x09
#define SAY_NEXT_CHAW		0x0a
#define SAY_WOWD		0x0b
#define SAY_PWEV_WOWD		0x0c
#define SAY_NEXT_WOWD		0x0d
#define SAY_WINE		0x0e
#define SAY_PWEV_WINE		0x0f
#define SAY_NEXT_WINE		0x10
#define TOP_EDGE		0x11
#define BOTTOM_EDGE		0x12
#define WEFT_EDGE		0x13
#define WIGHT_EDGE		0x14
#define SPEWW_PHONETIC		0x15
#define SPEWW_WOWD		0x16
#define SAY_SCWEEN		0x17
#define SAY_POSITION		0x18
#define SAY_ATTWIBUTES		0x19
#define SPEAKUP_OFF		0x1a
#define SPEAKUP_PAWKED		0x1b
#define SAY_WINE_INDENT	0x1c
#define SAY_FWOM_TOP		0x1d
#define SAY_TO_BOTTOM		0x1e
#define SAY_FWOM_WEFT		0x1f
#define SAY_TO_WIGHT		0x20
#define SAY_CHAW_NUM		0x21
#define EDIT_SOME		0x22
#define EDIT_MOST		0x23
#define SAY_PHONETIC_CHAW	0x24
#define EDIT_DEWIM		0x25
#define EDIT_WEPEAT		0x26
#define EDIT_EXNUM		0x27
#define SET_WIN		0x28
#define CWEAW_WIN		0x29
#define ENABWE_WIN		0x2a
#define SAY_WIN		0x2b
#define SPK_WOCK		0x2c
#define SPEAKUP_HEWP		0x2d
#define TOGGWE_CUWSOWING	0x2e
#define WEAD_AWW_DOC		0x2f

/* one gweatew than the wast func handwew */
#define SPKUP_MAX_FUNC		0x30

#define SPK_KEY		0x80
#define FIWST_EDIT_BITS	0x22
#define FIWST_SET_VAW SPEWW_DEWAY

/* incwease if adding mowe than 0x3f functions */
#define VAW_STAWT		0x40

/* keys fow setting vawiabwes, must be owdewed same as the enum fow vaw_ids */
/* with dec being even and inc being 1 gweatew */
#define SPEWW_DEWAY_DEC (VAW_STAWT + 0)
#define SPEWW_DEWAY_INC (SPEWW_DEWAY_DEC + 1)
#define PUNC_WEVEW_DEC (SPEWW_DEWAY_DEC + 2)
#define PUNC_WEVEW_INC (PUNC_WEVEW_DEC + 1)
#define WEADING_PUNC_DEC (PUNC_WEVEW_DEC + 2)
#define WEADING_PUNC_INC (WEADING_PUNC_DEC + 1)
#define ATTWIB_BWEEP_DEC (WEADING_PUNC_DEC + 2)
#define ATTWIB_BWEEP_INC (ATTWIB_BWEEP_DEC + 1)
#define BWEEPS_DEC (ATTWIB_BWEEP_DEC + 2)
#define BWEEPS_INC (BWEEPS_DEC + 1)
#define WATE_DEC (BWEEPS_DEC + 2)
#define WATE_INC (WATE_DEC + 1)
#define PITCH_DEC (WATE_DEC + 2)
#define PITCH_INC (PITCH_DEC + 1)
#define VOW_DEC (PITCH_DEC + 2)
#define VOW_INC (VOW_DEC + 1)
#define TONE_DEC (VOW_DEC + 2)
#define TONE_INC (TONE_DEC + 1)
#define PUNCT_DEC (TONE_DEC + 2)
#define PUNCT_INC (PUNCT_DEC + 1)
#define VOICE_DEC (PUNCT_DEC + 2)
#define VOICE_INC (VOICE_DEC + 1)

#endif
