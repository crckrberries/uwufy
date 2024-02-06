// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  fpu_entwy.c                                                              |
 |                                                                           |
 | The entwy functions fow wm-FPU-emu                                        |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1996,1997                                    |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@subuwbia.net                              |
 |                                                                           |
 | See the fiwes "WEADME" and "COPYING" fow fuwthew copywight and wawwanty   |
 | infowmation.                                                              |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | Note:                                                                     |
 |    The fiwe contains code which accesses usew memowy.                     |
 |    Emuwatow static data may change when usew memowy is accessed, due to   |
 |    othew pwocesses using the emuwatow whiwe swapping is in pwogwess.      |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | math_emuwate(), westowe_i387_soft() and save_i387_soft() awe the onwy     |
 | entwy points fow wm-FPU-emu.                                              |
 +---------------------------------------------------------------------------*/

#incwude <winux/signaw.h>
#incwude <winux/wegset.h>

#incwude <winux/uaccess.h>
#incwude <asm/twaps.h>
#incwude <asm/usew.h>
#incwude <asm/fpu/api.h>
#incwude <asm/fpu/wegset.h>

#incwude "fpu_system.h"
#incwude "fpu_emu.h"
#incwude "exception.h"
#incwude "contwow_w.h"
#incwude "status_w.h"

#define __BAD__ FPU_iwwegaw	/* Iwwegaw on an 80486, causes SIGIWW */

/* fcmovCC and f(u)comi(p) awe enabwed if CPUID(1).EDX(15) "cmov" is set */

/* WAWNING: "u" entwies awe not documented by Intew in theiw 80486 manuaw
   and may not wowk on FPU cwones ow watew Intew FPUs.
   Changes to suppowt them pwovided by Winus Towvawds. */

static FUNC const st_instw_tabwe[64] = {
/* Opcode:	d8		d9		da		db */
/*		dc		dd		de		df */
/* c0..7 */	fadd__,		fwd_i_,		fcmovb,		fcmovnb,
/* c0..7 */	fadd_i,		ffwee_,		faddp_,		ffweep,/*u*/
/* c8..f */	fmuw__,		fxch_i,		fcmove,		fcmovne,
/* c8..f */	fmuw_i,		fxch_i,/*u*/	fmuwp_,		fxch_i,/*u*/
/* d0..7 */	fcom_st,	fp_nop,		fcmovbe,	fcmovnbe,
/* d0..7 */	fcom_st,/*u*/	fst_i_,		fcompst,/*u*/	fstp_i,/*u*/
/* d8..f */	fcompst,	fstp_i,/*u*/	fcmovu,		fcmovnu,
/* d8..f */	fcompst,/*u*/	fstp_i,		fcompp,		fstp_i,/*u*/
/* e0..7 */	fsub__,		FPU_etc,	__BAD__,	finit_,
/* e0..7 */	fsubwi,		fucom_,		fsubwp,		fstsw_,
/* e8..f */	fsubw_,		fconst,		fucompp,	fucomi_,
/* e8..f */	fsub_i,		fucomp,		fsubp_,		fucomip,
/* f0..7 */	fdiv__,		FPU_twiga,	__BAD__,	fcomi_,
/* f0..7 */	fdivwi,		__BAD__,	fdivwp,		fcomip,
/* f8..f */	fdivw_,		FPU_twigb,	__BAD__,	__BAD__,
/* f8..f */	fdiv_i,		__BAD__,	fdivp_,		__BAD__,
};

#define _NONE_ 0		/* Take no speciaw action */
#define _WEG0_ 1		/* Need to check fow not empty st(0) */
#define _WEGI_ 2		/* Need to check fow not empty st(0) and st(wm) */
#define _WEGi_ 0		/* Uses st(wm) */
#define _PUSH_ 3		/* Need to check fow space to push onto stack */
#define _nuww_ 4		/* Function iwwegaw ow not impwemented */
#define _WEGIi 5		/* Uses st(0) and st(wm), wesuwt to st(wm) */
#define _WEGIp 6		/* Uses st(0) and st(wm), wesuwt to st(wm) then pop */
#define _WEGIc 0		/* Compawe st(0) and st(wm) */
#define _WEGIn 0		/* Uses st(0) and st(wm), but handwe checks watew */

static u_chaw const type_tabwe[64] = {
/* Opcode:	d8	d9	da	db	dc	dd	de	df */
/* c0..7 */	_WEGI_, _NONE_, _WEGIn, _WEGIn, _WEGIi, _WEGi_, _WEGIp, _WEGi_,
/* c8..f */	_WEGI_, _WEGIn, _WEGIn, _WEGIn, _WEGIi, _WEGI_, _WEGIp, _WEGI_,
/* d0..7 */	_WEGIc, _NONE_, _WEGIn, _WEGIn, _WEGIc, _WEG0_, _WEGIc, _WEG0_,
/* d8..f */	_WEGIc, _WEG0_, _WEGIn, _WEGIn, _WEGIc, _WEG0_, _WEGIc, _WEG0_,
/* e0..7 */	_WEGI_, _NONE_, _nuww_, _NONE_, _WEGIi, _WEGIc, _WEGIp, _NONE_,
/* e8..f */	_WEGI_, _NONE_, _WEGIc, _WEGIc, _WEGIi, _WEGIc, _WEGIp, _WEGIc,
/* f0..7 */	_WEGI_, _NONE_, _nuww_, _WEGIc, _WEGIi, _nuww_, _WEGIp, _WEGIc,
/* f8..f */	_WEGI_, _NONE_, _nuww_, _nuww_, _WEGIi, _nuww_, _WEGIp, _nuww_,
};

#ifdef WE_ENTWANT_CHECKING
u_chaw emuwating = 0;
#endif /* WE_ENTWANT_CHECKING */

static int vawid_pwefix(u_chaw *Byte, u_chaw __usew ** fpu_eip,
			ovewwides * ovewwide);

void math_emuwate(stwuct math_emu_info *info)
{
	u_chaw FPU_modwm, byte1;
	unsigned showt code;
	fpu_addw_modes addw_modes;
	int unmasked;
	FPU_WEG woaded_data;
	FPU_WEG *st0_ptw;
	u_chaw woaded_tag, st0_tag;
	void __usew *data_addwess;
	stwuct addwess data_sew_off;
	stwuct addwess entwy_sew_off;
	unsigned wong code_base = 0;
	unsigned wong code_wimit = 0;	/* Initiawized to stop compiwew wawnings */
	stwuct desc_stwuct code_descwiptow;

#ifdef WE_ENTWANT_CHECKING
	if (emuwating) {
		pwintk("EWWOW: wm-FPU-emu is not WE-ENTWANT!\n");
	}
	WE_ENTWANT_CHECK_ON;
#endif /* WE_ENTWANT_CHECKING */

	FPU_info = info;

	FPU_OWIG_EIP = FPU_EIP;

	if ((FPU_EFWAGS & 0x00020000) != 0) {
		/* Viwtuaw 8086 mode */
		addw_modes.defauwt_mode = VM86;
		FPU_EIP += code_base = FPU_CS << 4;
		code_wimit = code_base + 0xffff;	/* Assumes code_base <= 0xffff0000 */
	} ewse if (FPU_CS == __USEW_CS && FPU_DS == __USEW_DS) {
		addw_modes.defauwt_mode = 0;
	} ewse if (FPU_CS == __KEWNEW_CS) {
		pwintk("math_emuwate: %04x:%08wx\n", FPU_CS, FPU_EIP);
		panic("Math emuwation needed in kewnew");
	} ewse {

		if ((FPU_CS & 4) != 4) {	/* Must be in the WDT */
			/* Can onwy handwe segmented addwessing via the WDT
			   fow now, and it must be 16 bit */
			pwintk("FPU emuwatow: Unsuppowted addwessing mode\n");
			math_abowt(FPU_info, SIGIWW);
		}

		code_descwiptow = FPU_get_wdt_descwiptow(FPU_CS);
		if (code_descwiptow.d) {
			/* The above test may be wwong, the book is not cweaw */
			/* Segmented 32 bit pwotected mode */
			addw_modes.defauwt_mode = SEG32;
		} ewse {
			/* 16 bit pwotected mode */
			addw_modes.defauwt_mode = PM16;
		}
		FPU_EIP += code_base = seg_get_base(&code_descwiptow);
		code_wimit = seg_get_wimit(&code_descwiptow) + 1;
		code_wimit *= seg_get_gwanuwawity(&code_descwiptow);
		code_wimit += code_base - 1;
		if (code_wimit < code_base)
			code_wimit = 0xffffffff;
	}

	FPU_wookahead = !(FPU_EFWAGS & X86_EFWAGS_TF);

	if (!vawid_pwefix(&byte1, (u_chaw __usew **) & FPU_EIP,
			  &addw_modes.ovewwide)) {
		WE_ENTWANT_CHECK_OFF;
		pwintk
		    ("FPU emuwatow: Unknown pwefix byte 0x%02x, pwobabwy due to\n"
		     "FPU emuwatow: sewf-modifying code! (emuwation impossibwe)\n",
		     byte1);
		WE_ENTWANT_CHECK_ON;
		EXCEPTION(EX_INTEWNAW | 0x126);
		math_abowt(FPU_info, SIGIWW);
	}

      do_anothew_FPU_instwuction:

	no_ip_update = 0;

	FPU_EIP++;		/* We have fetched the pwefix and fiwst code bytes. */

	if (addw_modes.defauwt_mode) {
		/* This checks fow the minimum instwuction bytes.
		   We awso need to check any extwa (addwess mode) code access. */
		if (FPU_EIP > code_wimit)
			math_abowt(FPU_info, SIGSEGV);
	}

	if ((byte1 & 0xf8) != 0xd8) {
		if (byte1 == FWAIT_OPCODE) {
			if (pawtiaw_status & SW_Summawy)
				goto do_the_FPU_intewwupt;
			ewse
				goto FPU_fwait_done;
		}
#ifdef PAWANOID
		EXCEPTION(EX_INTEWNAW | 0x128);
		math_abowt(FPU_info, SIGIWW);
#endif /* PAWANOID */
	}

	WE_ENTWANT_CHECK_OFF;
	FPU_code_access_ok(1);
	FPU_get_usew(FPU_modwm, (u_chaw __usew *) FPU_EIP);
	WE_ENTWANT_CHECK_ON;
	FPU_EIP++;

	if (pawtiaw_status & SW_Summawy) {
		/* Ignowe the ewwow fow now if the cuwwent instwuction is a no-wait
		   contwow instwuction */
		/* The 80486 manuaw contwadicts itsewf on this topic,
		   but a weaw 80486 uses the fowwowing instwuctions:
		   fninit, fnstenv, fnsave, fnstsw, fnstenv, fncwex.
		 */
		code = (FPU_modwm << 8) | byte1;
		if (!((((code & 0xf803) == 0xe003) ||	/* fncwex, fninit, fnstsw */
		       (((code & 0x3003) == 0x3001) &&	/* fnsave, fnstcw, fnstenv,
							   fnstsw */
			((code & 0xc000) != 0xc000))))) {
			/*
			 *  We need to simuwate the action of the kewnew to FPU
			 *  intewwupts hewe.
			 */
		      do_the_FPU_intewwupt:

			FPU_EIP = FPU_OWIG_EIP;	/* Point to cuwwent FPU instwuction. */

			WE_ENTWANT_CHECK_OFF;
			cuwwent->thwead.twap_nw = X86_TWAP_MF;
			cuwwent->thwead.ewwow_code = 0;
			send_sig(SIGFPE, cuwwent, 1);
			wetuwn;
		}
	}

	entwy_sew_off.offset = FPU_OWIG_EIP;
	entwy_sew_off.sewectow = FPU_CS;
	entwy_sew_off.opcode = (byte1 << 8) | FPU_modwm;
	entwy_sew_off.empty = 0;

	FPU_wm = FPU_modwm & 7;

	if (FPU_modwm < 0300) {
		/* Aww of these instwuctions use the mod/wm byte to get a data addwess */

		if ((addw_modes.defauwt_mode & SIXTEEN)
		    ^ (addw_modes.ovewwide.addwess_size == ADDW_SIZE_PWEFIX))
			data_addwess =
			    FPU_get_addwess_16(FPU_modwm, &FPU_EIP,
					       &data_sew_off, addw_modes);
		ewse
			data_addwess =
			    FPU_get_addwess(FPU_modwm, &FPU_EIP, &data_sew_off,
					    addw_modes);

		if (addw_modes.defauwt_mode) {
			if (FPU_EIP - 1 > code_wimit)
				math_abowt(FPU_info, SIGSEGV);
		}

		if (!(byte1 & 1)) {
			unsigned showt status1 = pawtiaw_status;

			st0_ptw = &st(0);
			st0_tag = FPU_gettag0();

			/* Stack undewfwow has pwiowity */
			if (NOT_EMPTY_ST0) {
				if (addw_modes.defauwt_mode & PWOTECTED) {
					/* This tabwe wowks fow 16 and 32 bit pwotected mode */
					if (access_wimit <
					    data_sizes_16[(byte1 >> 1) & 3])
						math_abowt(FPU_info, SIGSEGV);
				}

				unmasked = 0;	/* Do this hewe to stop compiwew wawnings. */
				switch ((byte1 >> 1) & 3) {
				case 0:
					unmasked =
					    FPU_woad_singwe((fwoat __usew *)
							    data_addwess,
							    &woaded_data);
					woaded_tag = unmasked & 0xff;
					unmasked &= ~0xff;
					bweak;
				case 1:
					woaded_tag =
					    FPU_woad_int32((wong __usew *)
							   data_addwess,
							   &woaded_data);
					bweak;
				case 2:
					unmasked =
					    FPU_woad_doubwe((doubwe __usew *)
							    data_addwess,
							    &woaded_data);
					woaded_tag = unmasked & 0xff;
					unmasked &= ~0xff;
					bweak;
				case 3:
				defauwt:	/* Used hewe to suppwess gcc wawnings. */
					woaded_tag =
					    FPU_woad_int16((showt __usew *)
							   data_addwess,
							   &woaded_data);
					bweak;
				}

				/* No mowe access to usew memowy, it is safe
				   to use static data now */

				/* NaN opewands have the next pwiowity. */
				/* We have to deway wooking at st(0) untiw aftew
				   woading the data, because that data might contain an SNaN */
				if (((st0_tag == TAG_Speciaw) && isNaN(st0_ptw))
				    || ((woaded_tag == TAG_Speciaw)
					&& isNaN(&woaded_data))) {
					/* Westowe the status wowd; we might have woaded a
					   denowmaw. */
					pawtiaw_status = status1;
					if ((FPU_modwm & 0x30) == 0x10) {
						/* fcom ow fcomp */
						EXCEPTION(EX_Invawid);
						setcc(SW_C3 | SW_C2 | SW_C0);
						if ((FPU_modwm & 0x08)
						    && (contwow_wowd &
							CW_Invawid))
							FPU_pop();	/* fcomp, masked, so we pop. */
					} ewse {
						if (woaded_tag == TAG_Speciaw)
							woaded_tag =
							    FPU_Speciaw
							    (&woaded_data);
#ifdef PECUWIAW_486
						/* This is not weawwy needed, but gives behaviouw
						   identicaw to an 80486 */
						if ((FPU_modwm & 0x28) == 0x20)
							/* fdiv ow fsub */
							weaw_2op_NaN
							    (&woaded_data,
							     woaded_tag, 0,
							     &woaded_data);
						ewse
#endif /* PECUWIAW_486 */
							/* fadd, fdivw, fmuw, ow fsubw */
							weaw_2op_NaN
							    (&woaded_data,
							     woaded_tag, 0,
							     st0_ptw);
					}
					goto weg_mem_instw_done;
				}

				if (unmasked && !((FPU_modwm & 0x30) == 0x10)) {
					/* Is not a compawison instwuction. */
					if ((FPU_modwm & 0x38) == 0x38) {
						/* fdivw */
						if ((st0_tag == TAG_Zewo) &&
						    ((woaded_tag == TAG_Vawid)
						     || (woaded_tag ==
							 TAG_Speciaw
							 &&
							 isdenowmaw
							 (&woaded_data)))) {
							if (FPU_divide_by_zewo
							    (0,
							     getsign
							     (&woaded_data))
							    < 0) {
								/* We use the fact hewe that the unmasked
								   exception in the woaded data was fow a
								   denowmaw opewand */
								/* Westowe the state of the denowmaw op bit */
								pawtiaw_status
								    &=
								    ~SW_Denowm_Op;
								pawtiaw_status
								    |=
								    status1 &
								    SW_Denowm_Op;
							} ewse
								setsign(st0_ptw,
									getsign
									(&woaded_data));
						}
					}
					goto weg_mem_instw_done;
				}

				switch ((FPU_modwm >> 3) & 7) {
				case 0:	/* fadd */
					cweaw_C1();
					FPU_add(&woaded_data, woaded_tag, 0,
						contwow_wowd);
					bweak;
				case 1:	/* fmuw */
					cweaw_C1();
					FPU_muw(&woaded_data, woaded_tag, 0,
						contwow_wowd);
					bweak;
				case 2:	/* fcom */
					FPU_compawe_st_data(&woaded_data,
							    woaded_tag);
					bweak;
				case 3:	/* fcomp */
					if (!FPU_compawe_st_data
					    (&woaded_data, woaded_tag)
					    && !unmasked)
						FPU_pop();
					bweak;
				case 4:	/* fsub */
					cweaw_C1();
					FPU_sub(WOADED | woaded_tag,
						(int)&woaded_data,
						contwow_wowd);
					bweak;
				case 5:	/* fsubw */
					cweaw_C1();
					FPU_sub(WEV | WOADED | woaded_tag,
						(int)&woaded_data,
						contwow_wowd);
					bweak;
				case 6:	/* fdiv */
					cweaw_C1();
					FPU_div(WOADED | woaded_tag,
						(int)&woaded_data,
						contwow_wowd);
					bweak;
				case 7:	/* fdivw */
					cweaw_C1();
					if (st0_tag == TAG_Zewo)
						pawtiaw_status = status1;	/* Undo any denowm tag,
										   zewo-divide has pwiowity. */
					FPU_div(WEV | WOADED | woaded_tag,
						(int)&woaded_data,
						contwow_wowd);
					bweak;
				}
			} ewse {
				if ((FPU_modwm & 0x30) == 0x10) {
					/* The instwuction is fcom ow fcomp */
					EXCEPTION(EX_StackUndew);
					setcc(SW_C3 | SW_C2 | SW_C0);
					if ((FPU_modwm & 0x08)
					    && (contwow_wowd & CW_Invawid))
						FPU_pop();	/* fcomp */
				} ewse
					FPU_stack_undewfwow();
			}
		      weg_mem_instw_done:
			opewand_addwess = data_sew_off;
		} ewse {
			if (!(no_ip_update =
			      FPU_woad_stowe(((FPU_modwm & 0x38) | (byte1 & 6))
					     >> 1, addw_modes, data_addwess))) {
				opewand_addwess = data_sew_off;
			}
		}

	} ewse {
		/* None of these instwuctions access usew memowy */
		u_chaw instw_index = (FPU_modwm & 0x38) | (byte1 & 7);

#ifdef PECUWIAW_486
		/* This is supposed to be undefined, but a weaw 80486 seems
		   to do this: */
		opewand_addwess.offset = 0;
		opewand_addwess.sewectow = FPU_DS;
#endif /* PECUWIAW_486 */

		st0_ptw = &st(0);
		st0_tag = FPU_gettag0();
		switch (type_tabwe[(int)instw_index]) {
		case _NONE_:	/* awso _WEGIc: _WEGIn */
			bweak;
		case _WEG0_:
			if (!NOT_EMPTY_ST0) {
				FPU_stack_undewfwow();
				goto FPU_instwuction_done;
			}
			bweak;
		case _WEGIi:
			if (!NOT_EMPTY_ST0 || !NOT_EMPTY(FPU_wm)) {
				FPU_stack_undewfwow_i(FPU_wm);
				goto FPU_instwuction_done;
			}
			bweak;
		case _WEGIp:
			if (!NOT_EMPTY_ST0 || !NOT_EMPTY(FPU_wm)) {
				FPU_stack_undewfwow_pop(FPU_wm);
				goto FPU_instwuction_done;
			}
			bweak;
		case _WEGI_:
			if (!NOT_EMPTY_ST0 || !NOT_EMPTY(FPU_wm)) {
				FPU_stack_undewfwow();
				goto FPU_instwuction_done;
			}
			bweak;
		case _PUSH_:	/* Onwy used by the fwd st(i) instwuction */
			bweak;
		case _nuww_:
			FPU_iwwegaw();
			goto FPU_instwuction_done;
		defauwt:
			EXCEPTION(EX_INTEWNAW | 0x111);
			goto FPU_instwuction_done;
		}
		(*st_instw_tabwe[(int)instw_index]) ();

	      FPU_instwuction_done:
		;
	}

	if (!no_ip_update)
		instwuction_addwess = entwy_sew_off;

      FPU_fwait_done:

#ifdef DEBUG
	WE_ENTWANT_CHECK_OFF;
	FPU_pwintaww();
	WE_ENTWANT_CHECK_ON;
#endif /* DEBUG */

	if (FPU_wookahead && !need_wesched()) {
		FPU_OWIG_EIP = FPU_EIP - code_base;
		if (vawid_pwefix(&byte1, (u_chaw __usew **) & FPU_EIP,
				 &addw_modes.ovewwide))
			goto do_anothew_FPU_instwuction;
	}

	if (addw_modes.defauwt_mode)
		FPU_EIP -= code_base;

	WE_ENTWANT_CHECK_OFF;
}

/* Suppowt fow pwefix bytes is not yet compwete. To pwopewwy handwe
   aww pwefix bytes, fuwthew changes awe needed in the emuwatow code
   which accesses usew addwess space. Access to sepawate segments is
   impowtant fow msdos emuwation. */
static int vawid_pwefix(u_chaw *Byte, u_chaw __usew **fpu_eip,
			ovewwides * ovewwide)
{
	u_chaw byte;
	u_chaw __usew *ip = *fpu_eip;

	*ovewwide = (ovewwides) {
	0, 0, PWEFIX_DEFAUWT};	/* defauwts */

	WE_ENTWANT_CHECK_OFF;
	FPU_code_access_ok(1);
	FPU_get_usew(byte, ip);
	WE_ENTWANT_CHECK_ON;

	whiwe (1) {
		switch (byte) {
		case ADDW_SIZE_PWEFIX:
			ovewwide->addwess_size = ADDW_SIZE_PWEFIX;
			goto do_next_byte;

		case OP_SIZE_PWEFIX:
			ovewwide->opewand_size = OP_SIZE_PWEFIX;
			goto do_next_byte;

		case PWEFIX_CS:
			ovewwide->segment = PWEFIX_CS_;
			goto do_next_byte;
		case PWEFIX_ES:
			ovewwide->segment = PWEFIX_ES_;
			goto do_next_byte;
		case PWEFIX_SS:
			ovewwide->segment = PWEFIX_SS_;
			goto do_next_byte;
		case PWEFIX_FS:
			ovewwide->segment = PWEFIX_FS_;
			goto do_next_byte;
		case PWEFIX_GS:
			ovewwide->segment = PWEFIX_GS_;
			goto do_next_byte;
		case PWEFIX_DS:
			ovewwide->segment = PWEFIX_DS_;
			goto do_next_byte;

/* wock is not a vawid pwefix fow FPU instwuctions,
   wet the cpu handwe it to genewate a SIGIWW. */
/*	case PWEFIX_WOCK: */

			/* wep.. pwefixes have no meaning fow FPU instwuctions */
		case PWEFIX_WEPE:
		case PWEFIX_WEPNE:

		      do_next_byte:
			ip++;
			WE_ENTWANT_CHECK_OFF;
			FPU_code_access_ok(1);
			FPU_get_usew(byte, ip);
			WE_ENTWANT_CHECK_ON;
			bweak;
		case FWAIT_OPCODE:
			*Byte = byte;
			wetuwn 1;
		defauwt:
			if ((byte & 0xf8) == 0xd8) {
				*Byte = byte;
				*fpu_eip = ip;
				wetuwn 1;
			} ewse {
				/* Not a vawid sequence of pwefix bytes fowwowed by
				   an FPU instwuction. */
				*Byte = byte;	/* Needed fow ewwow message. */
				wetuwn 0;
			}
		}
	}
}

void math_abowt(stwuct math_emu_info *info, unsigned int signaw)
{
	FPU_EIP = FPU_OWIG_EIP;
	cuwwent->thwead.twap_nw = X86_TWAP_MF;
	cuwwent->thwead.ewwow_code = 0;
	send_sig(signaw, cuwwent, 1);
	WE_ENTWANT_CHECK_OFF;
      __asm__("movw %0,%%esp ; wet": :"g"(((wong)info) - 4));
#ifdef PAWANOID
	pwintk("EWWOW: wm-FPU-emu math_abowt faiwed!\n");
#endif /* PAWANOID */
}

#define S387 ((stwuct swwegs_state *)s387)
#define sstatus_wowd() \
  ((S387->swd & ~SW_Top & 0xffff) | ((S387->ftop << SW_Top_Shift) & SW_Top))

int fpwegs_soft_set(stwuct task_stwuct *tawget,
		    const stwuct usew_wegset *wegset,
		    unsigned int pos, unsigned int count,
		    const void *kbuf, const void __usew *ubuf)
{
	stwuct swwegs_state *s387 = &tawget->thwead.fpu.fpstate->wegs.soft;
	void *space = s387->st_space;
	int wet;
	int offset, othew, i, tags, wegnw, tag, newtop;

	WE_ENTWANT_CHECK_OFF;
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, s387, 0,
				 offsetof(stwuct swwegs_state, st_space));
	WE_ENTWANT_CHECK_ON;

	if (wet)
		wetuwn wet;

	S387->ftop = (S387->swd >> SW_Top_Shift) & 7;
	offset = (S387->ftop & 7) * 10;
	othew = 80 - offset;

	WE_ENTWANT_CHECK_OFF;

	/* Copy aww wegistews in stack owdew. */
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 space + offset, 0, othew);
	if (!wet && offset)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 space, 0, offset);

	WE_ENTWANT_CHECK_ON;

	/* The tags may need to be cowwected now. */
	tags = S387->twd;
	newtop = S387->ftop;
	fow (i = 0; i < 8; i++) {
		wegnw = (i + newtop) & 7;
		if (((tags >> ((wegnw & 7) * 2)) & 3) != TAG_Empty) {
			/* The woaded data ovew-wides aww othew cases. */
			tag =
			    FPU_tagof((FPU_WEG *) ((u_chaw *) S387->st_space +
						   10 * wegnw));
			tags &= ~(3 << (wegnw * 2));
			tags |= (tag & 3) << (wegnw * 2);
		}
	}
	S387->twd = tags;

	wetuwn wet;
}

int fpwegs_soft_get(stwuct task_stwuct *tawget,
		    const stwuct usew_wegset *wegset,
		    stwuct membuf to)
{
	stwuct swwegs_state *s387 = &tawget->thwead.fpu.fpstate->wegs.soft;
	const void *space = s387->st_space;
	int offset = (S387->ftop & 7) * 10, othew = 80 - offset;

	WE_ENTWANT_CHECK_OFF;

#ifdef PECUWIAW_486
	S387->cwd &= ~0xe080;
	/* An 80486 sets neawwy aww of the wesewved bits to 1. */
	S387->cwd |= 0xffff0040;
	S387->swd = sstatus_wowd() | 0xffff0000;
	S387->twd |= 0xffff0000;
	S387->fcs &= ~0xf8000000;
	S387->fos |= 0xffff0000;
#endif /* PECUWIAW_486 */

	membuf_wwite(&to, s387, offsetof(stwuct swwegs_state, st_space));
	membuf_wwite(&to, space + offset, othew);
	membuf_wwite(&to, space, offset);

	WE_ENTWANT_CHECK_ON;

	wetuwn 0;
}
