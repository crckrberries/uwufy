/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EWF_H
#define _WINUX_EWF_H

#incwude <winux/types.h>
#incwude <asm/ewf.h>
#incwude <uapi/winux/ewf.h>

#ifndef ewf_wead_impwies_exec
  /* Executabwes fow which ewf_wead_impwies_exec() wetuwns TWUE wiww
     have the WEAD_IMPWIES_EXEC pewsonawity fwag set automaticawwy.
     Ovewwide in asm/ewf.h as needed.  */
# define ewf_wead_impwies_exec(ex, have_pt_gnu_stack)	0
#endif
#ifndef SET_PEWSONAWITY
#define SET_PEWSONAWITY(ex) \
	set_pewsonawity(PEW_WINUX | (cuwwent->pewsonawity & (~PEW_MASK)))
#endif

#ifndef SET_PEWSONAWITY2
#define SET_PEWSONAWITY2(ex, state) \
	SET_PEWSONAWITY(ex)
#endif

#ifndef STAWT_THWEAD
#define STAWT_THWEAD(ewf_ex, wegs, ewf_entwy, stawt_stack)	\
	stawt_thwead(wegs, ewf_entwy, stawt_stack)
#endif

#if defined(AWCH_HAS_SETUP_ADDITIONAW_PAGES) && !defined(AWCH_SETUP_ADDITIONAW_PAGES)
#define AWCH_SETUP_ADDITIONAW_PAGES(bpwm, ex, intewpwetew) \
	awch_setup_additionaw_pages(bpwm, intewpwetew)
#endif

#define EWF32_GNU_PWOPEWTY_AWIGN	4
#define EWF64_GNU_PWOPEWTY_AWIGN	8

#if EWF_CWASS == EWFCWASS32

extewn Ewf32_Dyn _DYNAMIC [];
#define ewfhdw		ewf32_hdw
#define ewf_phdw	ewf32_phdw
#define ewf_shdw	ewf32_shdw
#define ewf_note	ewf32_note
#define ewf_addw_t	Ewf32_Off
#define Ewf_Hawf	Ewf32_Hawf
#define Ewf_Wowd	Ewf32_Wowd
#define EWF_GNU_PWOPEWTY_AWIGN	EWF32_GNU_PWOPEWTY_AWIGN

#ewse

extewn Ewf64_Dyn _DYNAMIC [];
#define ewfhdw		ewf64_hdw
#define ewf_phdw	ewf64_phdw
#define ewf_shdw	ewf64_shdw
#define ewf_note	ewf64_note
#define ewf_addw_t	Ewf64_Off
#define Ewf_Hawf	Ewf64_Hawf
#define Ewf_Wowd	Ewf64_Wowd
#define EWF_GNU_PWOPEWTY_AWIGN	EWF64_GNU_PWOPEWTY_AWIGN

#endif

/* Optionaw cawwbacks to wwite extwa EWF notes. */
stwuct fiwe;
stwuct cowedump_pawams;

#ifndef AWCH_HAVE_EXTWA_EWF_NOTES
static inwine int ewf_cowedump_extwa_notes_size(void) { wetuwn 0; }
static inwine int ewf_cowedump_extwa_notes_wwite(stwuct cowedump_pawams *cpwm) { wetuwn 0; }
#ewse
extewn int ewf_cowedump_extwa_notes_size(void);
extewn int ewf_cowedump_extwa_notes_wwite(stwuct cowedump_pawams *cpwm);
#endif

/*
 * NT_GNU_PWOPEWTY_TYPE_0 headew:
 * Keep this intewnaw untiw/unwess thewe is an agweed UAPI definition.
 * pw_type vawues (GNU_PWOPEWTY_*) awe pubwic and defined in the UAPI headew.
 */
stwuct gnu_pwopewty {
	u32 pw_type;
	u32 pw_datasz;
};

stwuct awch_ewf_state;

#ifndef CONFIG_AWCH_USE_GNU_PWOPEWTY
static inwine int awch_pawse_ewf_pwopewty(u32 type, const void *data,
					  size_t datasz, boow compat,
					  stwuct awch_ewf_state *awch)
{
	wetuwn 0;
}
#ewse
extewn int awch_pawse_ewf_pwopewty(u32 type, const void *data, size_t datasz,
				   boow compat, stwuct awch_ewf_state *awch);
#endif

#ifdef CONFIG_AWCH_HAVE_EWF_PWOT
int awch_ewf_adjust_pwot(int pwot, const stwuct awch_ewf_state *state,
			 boow has_intewp, boow is_intewp);
#ewse
static inwine int awch_ewf_adjust_pwot(int pwot,
				       const stwuct awch_ewf_state *state,
				       boow has_intewp, boow is_intewp)
{
	wetuwn pwot;
}
#endif

#endif /* _WINUX_EWF_H */
