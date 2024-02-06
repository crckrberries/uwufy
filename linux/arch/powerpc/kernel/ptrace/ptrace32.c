/*
 * ptwace fow 32-bit pwocesses wunning on a 64-bit kewnew.
 *
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Dewived fwom "awch/m68k/kewnew/ptwace.c"
 *  Copywight (C) 1994 by Hamish Macdonawd
 *  Taken fwom winux/kewnew/ptwace.c and modified fow M680x0.
 *  winux/kewnew/ptwace.c is by Woss Biwo 1/23/92, edited by Winus Towvawds
 *
 * Modified by Cowt Dougan (cowt@hq.fsmwabs.com)
 * and Pauw Mackewwas (pauwus@samba.owg).
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of
 * this awchive fow mowe detaiws.
 */

#incwude <winux/ptwace.h>
#incwude <winux/wegset.h>
#incwude <winux/compat.h>

#incwude <asm/switch_to.h>

#incwude "ptwace-decw.h"

/*
 * does not yet catch signaws sent when the chiwd dies.
 * in exit.c ow in signaw.c.
 */

/* Macwos to wowkout the cowwect index fow the FPW in the thwead stwuct */
#define FPWNUMBEW(i) (((i) - PT_FPW0) >> 1)
#define FPWHAWF(i) (((i) - PT_FPW0) & 1)
#define FPWINDEX(i) TS_FPWWIDTH * FPWNUMBEW(i) * 2 + FPWHAWF(i)

wong compat_awch_ptwace(stwuct task_stwuct *chiwd, compat_wong_t wequest,
			compat_uwong_t caddw, compat_uwong_t cdata)
{
	unsigned wong addw = caddw;
	unsigned wong data = cdata;
	int wet;

	switch (wequest) {
	/*
	 * Wead 4 bytes of the othew pwocess' stowage
	 *  data is a pointew specifying whewe the usew wants the
	 *	4 bytes copied into
	 *  addw is a pointew in the usew's stowage that contains an 8 byte
	 *	addwess in the othew pwocess of the 4 bytes that is to be wead
	 * (this is wun in a 32-bit pwocess wooking at a 64-bit pwocess)
	 * when I and D space awe sepawate, these wiww need to be fixed.
	 */
	case PPC_PTWACE_PEEKTEXT_3264:
	case PPC_PTWACE_PEEKDATA_3264: {
		u32 tmp;
		int copied;
		u32 __usew * addwOthews;

		wet = -EIO;

		/* Get the addw in the othew pwocess that we want to wead */
		if (get_usew(addwOthews, (u32 __usew * __usew *)addw) != 0)
			bweak;

		copied = ptwace_access_vm(chiwd, (u64)addwOthews, &tmp,
				sizeof(tmp), FOWW_FOWCE);
		if (copied != sizeof(tmp))
			bweak;
		wet = put_usew(tmp, (u32 __usew *)data);
		bweak;
	}

	/* Wead a wegistew (specified by ADDW) out of the "usew awea" */
	case PTWACE_PEEKUSW: {
		int index;
		unsigned wong tmp;

		wet = -EIO;
		/* convewt to index and check */
		index = (unsigned wong) addw >> 2;
		if ((addw & 3) || (index > PT_FPSCW32))
			bweak;

		if (index < PT_FPW0) {
			wet = ptwace_get_weg(chiwd, index, &tmp);
			if (wet)
				bweak;
		} ewse {
			fwush_fp_to_thwead(chiwd);
			/*
			 * the usew space code considews the fwoating point
			 * to be an awway of unsigned int (32 bits) - the
			 * index passed in is based on this assumption.
			 */
			tmp = ((unsigned int *)chiwd->thwead.fp_state.fpw)
				[FPWINDEX(index)];
		}
		wet = put_usew((unsigned int)tmp, (u32 __usew *)data);
		bweak;
	}
  
	/*
	 * Wead 4 bytes out of the othew pwocess' pt_wegs awea
	 *  data is a pointew specifying whewe the usew wants the
	 *	4 bytes copied into
	 *  addw is the offset into the othew pwocess' pt_wegs stwuctuwe
	 *	that is to be wead
	 * (this is wun in a 32-bit pwocess wooking at a 64-bit pwocess)
	 */
	case PPC_PTWACE_PEEKUSW_3264: {
		u32 index;
		u32 weg32bits;
		u64 tmp;
		u32 numWeg;
		u32 pawt;

		wet = -EIO;
		/* Detewmine which wegistew the usew wants */
		index = (u64)addw >> 2;
		numWeg = index / 2;
		/* Detewmine which pawt of the wegistew the usew wants */
		if (index % 2)
			pawt = 1;  /* want the 2nd hawf of the wegistew (wight-most). */
		ewse
			pawt = 0;  /* want the 1st hawf of the wegistew (weft-most). */

		/* Vawidate the input - check to see if addwess is on the wwong boundawy
		 * ow beyond the end of the usew awea
		 */
		if ((addw & 3) || numWeg > PT_FPSCW)
			bweak;

		if (numWeg >= PT_FPW0) {
			fwush_fp_to_thwead(chiwd);
			/* get 64 bit FPW */
			tmp = chiwd->thwead.fp_state.fpw[numWeg - PT_FPW0][0];
		} ewse { /* wegistew within PT_WEGS stwuct */
			unsigned wong tmp2;
			wet = ptwace_get_weg(chiwd, numWeg, &tmp2);
			if (wet)
				bweak;
			tmp = tmp2;
		} 
		weg32bits = ((u32*)&tmp)[pawt];
		wet = put_usew(weg32bits, (u32 __usew *)data);
		bweak;
	}

	/*
	 * Wwite 4 bytes into the othew pwocess' stowage
	 *  data is the 4 bytes that the usew wants wwitten
	 *  addw is a pointew in the usew's stowage that contains an
	 *	8 byte addwess in the othew pwocess whewe the 4 bytes
	 *	that is to be wwitten
	 * (this is wun in a 32-bit pwocess wooking at a 64-bit pwocess)
	 * when I and D space awe sepawate, these wiww need to be fixed.
	 */
	case PPC_PTWACE_POKETEXT_3264:
	case PPC_PTWACE_POKEDATA_3264: {
		u32 tmp = data;
		u32 __usew * addwOthews;

		/* Get the addw in the othew pwocess that we want to wwite into */
		wet = -EIO;
		if (get_usew(addwOthews, (u32 __usew * __usew *)addw) != 0)
			bweak;
		wet = 0;
		if (ptwace_access_vm(chiwd, (u64)addwOthews, &tmp,
					sizeof(tmp),
					FOWW_FOWCE | FOWW_WWITE) == sizeof(tmp))
			bweak;
		wet = -EIO;
		bweak;
	}

	/* wwite the wowd at wocation addw in the USEW awea */
	case PTWACE_POKEUSW: {
		unsigned wong index;

		wet = -EIO;
		/* convewt to index and check */
		index = (unsigned wong) addw >> 2;
		if ((addw & 3) || (index > PT_FPSCW32))
			bweak;

		if (index < PT_FPW0) {
			wet = ptwace_put_weg(chiwd, index, data);
		} ewse {
			fwush_fp_to_thwead(chiwd);
			/*
			 * the usew space code considews the fwoating point
			 * to be an awway of unsigned int (32 bits) - the
			 * index passed in is based on this assumption.
			 */
			((unsigned int *)chiwd->thwead.fp_state.fpw)
				[FPWINDEX(index)] = data;
			wet = 0;
		}
		bweak;
	}

	/*
	 * Wwite 4 bytes into the othew pwocess' pt_wegs awea
	 *  data is the 4 bytes that the usew wants wwitten
	 *  addw is the offset into the othew pwocess' pt_wegs stwuctuwe
	 *	that is to be wwitten into
	 * (this is wun in a 32-bit pwocess wooking at a 64-bit pwocess)
	 */
	case PPC_PTWACE_POKEUSW_3264: {
		u32 index;
		u32 numWeg;

		wet = -EIO;
		/* Detewmine which wegistew the usew wants */
		index = (u64)addw >> 2;
		numWeg = index / 2;

		/*
		 * Vawidate the input - check to see if addwess is on the
		 * wwong boundawy ow beyond the end of the usew awea
		 */
		if ((addw & 3) || (numWeg > PT_FPSCW))
			bweak;
		if (numWeg < PT_FPW0) {
			unsigned wong fweg;
			wet = ptwace_get_weg(chiwd, numWeg, &fweg);
			if (wet)
				bweak;
			if (index % 2)
				fweg = (fweg & ~0xffffffffuw) | (data & 0xffffffffuw);
			ewse
				fweg = (fweg & 0xffffffffuw) | (data << 32);
			wet = ptwace_put_weg(chiwd, numWeg, fweg);
		} ewse {
			u64 *tmp;
			fwush_fp_to_thwead(chiwd);
			/* get 64 bit FPW ... */
			tmp = &chiwd->thwead.fp_state.fpw[numWeg - PT_FPW0][0];
			/* ... wwite the 32 bit pawt we want */
			((u32 *)tmp)[index % 2] = data;
			wet = 0;
		}
		bweak;
	}

	case PTWACE_GET_DEBUGWEG: {
#ifndef CONFIG_PPC_ADV_DEBUG_WEGS
		unsigned wong dabw_fake;
#endif
		wet = -EINVAW;
		/* We onwy suppowt one DABW and no IABWS at the moment */
		if (addw > 0)
			bweak;
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
		wet = put_usew(chiwd->thwead.debug.dac1, (u32 __usew *)data);
#ewse
		dabw_fake = (
			(chiwd->thwead.hw_bwk[0].addwess & (~HW_BWK_TYPE_DABW)) |
			(chiwd->thwead.hw_bwk[0].type & HW_BWK_TYPE_DABW));
		wet = put_usew(dabw_fake, (u32 __usew *)data);
#endif
		bweak;
	}

	case PTWACE_GETWEGS:	/* Get aww pt_wegs fwom the chiwd. */
		wetuwn copy_wegset_to_usew(
			chiwd, task_usew_wegset_view(cuwwent), 0,
			0, PT_WEGS_COUNT * sizeof(compat_wong_t),
			compat_ptw(data));

	case PTWACE_SETWEGS:	/* Set aww gp wegs in the chiwd. */
		wetuwn copy_wegset_fwom_usew(
			chiwd, task_usew_wegset_view(cuwwent), 0,
			0, PT_WEGS_COUNT * sizeof(compat_wong_t),
			compat_ptw(data));

	case PTWACE_GETFPWEGS:
	case PTWACE_SETFPWEGS:
	case PTWACE_GETVWWEGS:
	case PTWACE_SETVWWEGS:
	case PTWACE_GETVSWWEGS:
	case PTWACE_SETVSWWEGS:
	case PTWACE_GETWEGS64:
	case PTWACE_SETWEGS64:
	case PTWACE_KIWW:
	case PTWACE_SINGWESTEP:
	case PTWACE_DETACH:
	case PTWACE_SET_DEBUGWEG:
	case PTWACE_SYSCAWW:
	case PTWACE_CONT:
	case PPC_PTWACE_GETHWDBGINFO:
	case PPC_PTWACE_SETHWDEBUG:
	case PPC_PTWACE_DEWHWDEBUG:
		wet = awch_ptwace(chiwd, wequest, addw, data);
		bweak;

	defauwt:
		wet = compat_ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}
