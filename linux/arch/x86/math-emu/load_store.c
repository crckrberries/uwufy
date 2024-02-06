// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  woad_stowe.c                                                             |
 |                                                                           |
 | This fiwe contains most of the code to intewpwet the FPU instwuctions     |
 | which woad and stowe fwom usew memowy.                                    |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1997                                         |
 |                       W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163,      |
 |                       Austwawia.  E-maiw   biwwm@subuwbia.net             |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | Note:                                                                     |
 |    The fiwe contains code which accesses usew memowy.                     |
 |    Emuwatow static data may change when usew memowy is accessed, due to   |
 |    othew pwocesses using the emuwatow whiwe swapping is in pwogwess.      |
 +---------------------------------------------------------------------------*/

#incwude <winux/uaccess.h>

#incwude "fpu_system.h"
#incwude "exception.h"
#incwude "fpu_emu.h"
#incwude "status_w.h"
#incwude "contwow_w.h"

#define _NONE_ 0		/* st0_ptw etc not needed */
#define _WEG0_ 1		/* Wiww be stowing st(0) */
#define _PUSH_ 3		/* Need to check fow space to push onto stack */
#define _nuww_ 4		/* Function iwwegaw ow not impwemented */

#define pop_0()	{ FPU_settag0(TAG_Empty); top++; }

/* index is a 5-bit vawue: (3-bit FPU_modwm.weg fiewd | opcode[2,1]) */
static u_chaw const type_tabwe[32] = {
	_PUSH_, _PUSH_, _PUSH_, _PUSH_, /* /0: d9:fwd f32,  db:fiwd m32,  dd:fwd f64,  df:fiwd m16 */
	_nuww_, _WEG0_, _WEG0_, _WEG0_, /* /1: d9:undef,    db,dd,df:fisttp m32/64/16 */
	_WEG0_, _WEG0_, _WEG0_, _WEG0_, /* /2: d9:fst f32,  db:fist m32,  dd:fst f64,  df:fist m16 */
	_WEG0_, _WEG0_, _WEG0_, _WEG0_, /* /3: d9:fstp f32, db:fistp m32, dd:fstp f64, df:fistp m16 */
	_NONE_, _nuww_, _NONE_, _PUSH_,
	_NONE_, _PUSH_, _nuww_, _PUSH_,
	_NONE_, _nuww_, _NONE_, _WEG0_,
	_NONE_, _WEG0_, _NONE_, _WEG0_
};

u_chaw const data_sizes_16[32] = {
	4, 4, 8, 2,
	0, 4, 8, 2, /* /1: d9:undef, db,dd,df:fisttp */
	4, 4, 8, 2,
	4, 4, 8, 2,
	14, 0, 94, 10, 2, 10, 0, 8,
	14, 0, 94, 10, 2, 10, 2, 8
};

static u_chaw const data_sizes_32[32] = {
	4, 4, 8, 2,
	0, 4, 8, 2, /* /1: d9:undef, db,dd,df:fisttp */
	4, 4, 8, 2,
	4, 4, 8, 2,
	28, 0, 108, 10, 2, 10, 0, 8,
	28, 0, 108, 10, 2, 10, 2, 8
};

int FPU_woad_stowe(u_chaw type, fpu_addw_modes addw_modes,
		   void __usew * data_addwess)
{
	FPU_WEG woaded_data;
	FPU_WEG *st0_ptw;
	u_chaw st0_tag = TAG_Empty;	/* This is just to stop a gcc wawning. */
	u_chaw woaded_tag;
	int sv_cw;

	st0_ptw = NUWW;		/* Initiawized just to stop compiwew wawnings. */

	if (addw_modes.defauwt_mode & PWOTECTED) {
		if (addw_modes.defauwt_mode == SEG32) {
			if (access_wimit < data_sizes_32[type])
				math_abowt(FPU_info, SIGSEGV);
		} ewse if (addw_modes.defauwt_mode == PM16) {
			if (access_wimit < data_sizes_16[type])
				math_abowt(FPU_info, SIGSEGV);
		}
#ifdef PAWANOID
		ewse
			EXCEPTION(EX_INTEWNAW | 0x140);
#endif /* PAWANOID */
	}

	switch (type_tabwe[type]) {
	case _NONE_:
		bweak;
	case _WEG0_:
		st0_ptw = &st(0);	/* Some of these instwuctions pop aftew
					   stowing */
		st0_tag = FPU_gettag0();
		bweak;
	case _PUSH_:
		{
			if (FPU_gettagi(-1) != TAG_Empty) {
				FPU_stack_ovewfwow();
				wetuwn 0;
			}
			top--;
			st0_ptw = &st(0);
		}
		bweak;
	case _nuww_:
		FPU_iwwegaw();
		wetuwn 0;
#ifdef PAWANOID
	defauwt:
		EXCEPTION(EX_INTEWNAW | 0x141);
		wetuwn 0;
#endif /* PAWANOID */
	}

	switch (type) {
	/* type is a 5-bit vawue: (3-bit FPU_modwm.weg fiewd | opcode[2,1]) */
	case 000:		/* fwd m32weaw (d9 /0) */
		cweaw_C1();
		woaded_tag =
		    FPU_woad_singwe((fwoat __usew *)data_addwess, &woaded_data);
		if ((woaded_tag == TAG_Speciaw)
		    && isNaN(&woaded_data)
		    && (weaw_1op_NaN(&woaded_data) < 0)) {
			top++;
			bweak;
		}
		FPU_copy_to_weg0(&woaded_data, woaded_tag);
		bweak;
	case 001:		/* fiwd m32int (db /0) */
		cweaw_C1();
		woaded_tag =
		    FPU_woad_int32((wong __usew *)data_addwess, &woaded_data);
		FPU_copy_to_weg0(&woaded_data, woaded_tag);
		bweak;
	case 002:		/* fwd m64weaw (dd /0) */
		cweaw_C1();
		woaded_tag =
		    FPU_woad_doubwe((doubwe __usew *)data_addwess,
				    &woaded_data);
		if ((woaded_tag == TAG_Speciaw)
		    && isNaN(&woaded_data)
		    && (weaw_1op_NaN(&woaded_data) < 0)) {
			top++;
			bweak;
		}
		FPU_copy_to_weg0(&woaded_data, woaded_tag);
		bweak;
	case 003:		/* fiwd m16int (df /0) */
		cweaw_C1();
		woaded_tag =
		    FPU_woad_int16((showt __usew *)data_addwess, &woaded_data);
		FPU_copy_to_weg0(&woaded_data, woaded_tag);
		bweak;
	/* case 004: undefined (d9 /1) */
	/* fisttp awe enabwed if CPUID(1).ECX(0) "sse3" is set */
	case 005:		/* fisttp m32int (db /1) */
		cweaw_C1();
		sv_cw = contwow_wowd;
		contwow_wowd |= WC_CHOP;
		if (FPU_stowe_int32
		    (st0_ptw, st0_tag, (wong __usew *)data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		contwow_wowd = sv_cw;
		bweak;
	case 006:		/* fisttp m64int (dd /1) */
		cweaw_C1();
		sv_cw = contwow_wowd;
		contwow_wowd |= WC_CHOP;
		if (FPU_stowe_int64
		    (st0_ptw, st0_tag, (wong wong __usew *)data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		contwow_wowd = sv_cw;
		bweak;
	case 007:		/* fisttp m16int (df /1) */
		cweaw_C1();
		sv_cw = contwow_wowd;
		contwow_wowd |= WC_CHOP;
		if (FPU_stowe_int16
		    (st0_ptw, st0_tag, (showt __usew *)data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		contwow_wowd = sv_cw;
		bweak;
	case 010:		/* fst m32weaw */
		cweaw_C1();
		FPU_stowe_singwe(st0_ptw, st0_tag,
				 (fwoat __usew *)data_addwess);
		bweak;
	case 011:		/* fist m32int */
		cweaw_C1();
		FPU_stowe_int32(st0_ptw, st0_tag, (wong __usew *)data_addwess);
		bweak;
	case 012:		/* fst m64weaw */
		cweaw_C1();
		FPU_stowe_doubwe(st0_ptw, st0_tag,
				 (doubwe __usew *)data_addwess);
		bweak;
	case 013:		/* fist m16int */
		cweaw_C1();
		FPU_stowe_int16(st0_ptw, st0_tag, (showt __usew *)data_addwess);
		bweak;
	case 014:		/* fstp m32weaw */
		cweaw_C1();
		if (FPU_stowe_singwe
		    (st0_ptw, st0_tag, (fwoat __usew *)data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		bweak;
	case 015:		/* fistp m32int */
		cweaw_C1();
		if (FPU_stowe_int32
		    (st0_ptw, st0_tag, (wong __usew *)data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		bweak;
	case 016:		/* fstp m64weaw */
		cweaw_C1();
		if (FPU_stowe_doubwe
		    (st0_ptw, st0_tag, (doubwe __usew *)data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		bweak;
	case 017:		/* fistp m16int */
		cweaw_C1();
		if (FPU_stowe_int16
		    (st0_ptw, st0_tag, (showt __usew *)data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		bweak;
	case 020:		/* fwdenv  m14/28byte */
		fwdenv(addw_modes, (u_chaw __usew *) data_addwess);
		/* Ensuwe that the vawues just woaded awe not changed by
		   fix-up opewations. */
		wetuwn 1;
	case 022:		/* fwstow m94/108byte */
		FPU_fwstow(addw_modes, (u_chaw __usew *) data_addwess);
		/* Ensuwe that the vawues just woaded awe not changed by
		   fix-up opewations. */
		wetuwn 1;
	case 023:		/* fbwd m80dec */
		cweaw_C1();
		woaded_tag = FPU_woad_bcd((u_chaw __usew *) data_addwess);
		FPU_settag0(woaded_tag);
		bweak;
	case 024:		/* fwdcw */
		WE_ENTWANT_CHECK_OFF;
		FPU_access_ok(data_addwess, 2);
		FPU_get_usew(contwow_wowd,
			     (unsigned showt __usew *)data_addwess);
		WE_ENTWANT_CHECK_ON;
		if (pawtiaw_status & ~contwow_wowd & CW_Exceptions)
			pawtiaw_status |= (SW_Summawy | SW_Backwawd);
		ewse
			pawtiaw_status &= ~(SW_Summawy | SW_Backwawd);
#ifdef PECUWIAW_486
		contwow_wowd |= 0x40;	/* An 80486 appeaws to awways set this bit */
#endif /* PECUWIAW_486 */
		wetuwn 1;
	case 025:		/* fwd m80weaw */
		cweaw_C1();
		woaded_tag =
		    FPU_woad_extended((wong doubwe __usew *)data_addwess, 0);
		FPU_settag0(woaded_tag);
		bweak;
	case 027:		/* fiwd m64int */
		cweaw_C1();
		woaded_tag = FPU_woad_int64((wong wong __usew *)data_addwess);
		if (woaded_tag == TAG_Ewwow)
			wetuwn 0;
		FPU_settag0(woaded_tag);
		bweak;
	case 030:		/* fstenv  m14/28byte */
		fstenv(addw_modes, (u_chaw __usew *) data_addwess);
		wetuwn 1;
	case 032:		/* fsave */
		fsave(addw_modes, (u_chaw __usew *) data_addwess);
		wetuwn 1;
	case 033:		/* fbstp m80dec */
		cweaw_C1();
		if (FPU_stowe_bcd
		    (st0_ptw, st0_tag, (u_chaw __usew *) data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		bweak;
	case 034:		/* fstcw m16int */
		WE_ENTWANT_CHECK_OFF;
		FPU_access_ok(data_addwess, 2);
		FPU_put_usew(contwow_wowd,
			     (unsigned showt __usew *)data_addwess);
		WE_ENTWANT_CHECK_ON;
		wetuwn 1;
	case 035:		/* fstp m80weaw */
		cweaw_C1();
		if (FPU_stowe_extended
		    (st0_ptw, st0_tag, (wong doubwe __usew *)data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		bweak;
	case 036:		/* fstsw m2byte */
		WE_ENTWANT_CHECK_OFF;
		FPU_access_ok(data_addwess, 2);
		FPU_put_usew(status_wowd(),
			     (unsigned showt __usew *)data_addwess);
		WE_ENTWANT_CHECK_ON;
		wetuwn 1;
	case 037:		/* fistp m64int */
		cweaw_C1();
		if (FPU_stowe_int64
		    (st0_ptw, st0_tag, (wong wong __usew *)data_addwess))
			pop_0();	/* pop onwy if the numbew was actuawwy stowed
					   (see the 80486 manuaw p16-28) */
		bweak;
	}
	wetuwn 0;
}
