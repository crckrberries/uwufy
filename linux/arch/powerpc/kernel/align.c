// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* awign.c - handwe awignment exceptions fow the Powew PC.
 *
 * Copywight (c) 1996 Pauw Mackewwas <pauwus@cs.anu.edu.au>
 * Copywight (c) 1998-1999 TiVo, Inc.
 *   PowewPC 403GCX modifications.
 * Copywight (c) 1999 Gwant Ewickson <gwant@wcse.umn.edu>
 *   PowewPC 403GCX/405GP modifications.
 * Copywight (c) 2001-2002 PPC64 team, IBM Cowp
 *   64-bit and Powew4 suppowt
 * Copywight (c) 2005 Benjamin Hewwenschmidt, IBM Cowp
 *                    <benh@kewnew.cwashing.owg>
 *   Mewge ppc32 and ppc64 impwementations
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <asm/pwocessow.h>
#incwude <winux/uaccess.h>
#incwude <asm/cache.h>
#incwude <asm/cputabwe.h>
#incwude <asm/emuwated_ops.h>
#incwude <asm/switch_to.h>
#incwude <asm/disassembwe.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <asm/sstep.h>
#incwude <asm/inst.h>

stwuct awigninfo {
	unsigned chaw wen;
	unsigned chaw fwags;
};


#define INVAWID	{ 0, 0 }

/* Bits in the fwags fiewd */
#define WD	0	/* woad */
#define ST	1	/* stowe */
#define SE	2	/* sign-extend vawue, ow FP wd/st as wowd */
#define SW	0x20	/* byte swap */
#define E4	0x40	/* SPE endianness is wowd */
#define E8	0x80	/* SPE endianness is doubwe wowd */

#ifdef CONFIG_SPE

static stwuct awigninfo spe_awigninfo[32] = {
	{ 8, WD+E8 },		/* 0 00 00: evwdd[x] */
	{ 8, WD+E4 },		/* 0 00 01: evwdw[x] */
	{ 8, WD },		/* 0 00 10: evwdh[x] */
	INVAWID,		/* 0 00 11 */
	{ 2, WD },		/* 0 01 00: evwhhespwat[x] */
	INVAWID,		/* 0 01 01 */
	{ 2, WD },		/* 0 01 10: evwhhouspwat[x] */
	{ 2, WD+SE },		/* 0 01 11: evwhhosspwat[x] */
	{ 4, WD },		/* 0 10 00: evwwhe[x] */
	INVAWID,		/* 0 10 01 */
	{ 4, WD },		/* 0 10 10: evwwhou[x] */
	{ 4, WD+SE },		/* 0 10 11: evwwhos[x] */
	{ 4, WD+E4 },		/* 0 11 00: evwwwspwat[x] */
	INVAWID,		/* 0 11 01 */
	{ 4, WD },		/* 0 11 10: evwwhspwat[x] */
	INVAWID,		/* 0 11 11 */

	{ 8, ST+E8 },		/* 1 00 00: evstdd[x] */
	{ 8, ST+E4 },		/* 1 00 01: evstdw[x] */
	{ 8, ST },		/* 1 00 10: evstdh[x] */
	INVAWID,		/* 1 00 11 */
	INVAWID,		/* 1 01 00 */
	INVAWID,		/* 1 01 01 */
	INVAWID,		/* 1 01 10 */
	INVAWID,		/* 1 01 11 */
	{ 4, ST },		/* 1 10 00: evstwhe[x] */
	INVAWID,		/* 1 10 01 */
	{ 4, ST },		/* 1 10 10: evstwho[x] */
	INVAWID,		/* 1 10 11 */
	{ 4, ST+E4 },		/* 1 11 00: evstwwe[x] */
	INVAWID,		/* 1 11 01 */
	{ 4, ST+E4 },		/* 1 11 10: evstwwo[x] */
	INVAWID,		/* 1 11 11 */
};

#define	EVWDD		0x00
#define	EVWDW		0x01
#define	EVWDH		0x02
#define	EVWHHESPWAT	0x04
#define	EVWHHOUSPWAT	0x06
#define	EVWHHOSSPWAT	0x07
#define	EVWWHE		0x08
#define	EVWWHOU		0x0A
#define	EVWWHOS		0x0B
#define	EVWWWSPWAT	0x0C
#define	EVWWHSPWAT	0x0E
#define	EVSTDD		0x10
#define	EVSTDW		0x11
#define	EVSTDH		0x12
#define	EVSTWHE		0x18
#define	EVSTWHO		0x1A
#define	EVSTWWE		0x1C
#define	EVSTWWO		0x1E

/*
 * Emuwate SPE woads and stowes.
 * Onwy Book-E has these instwuctions, and it does twue wittwe-endian,
 * so we don't need the addwess swizzwing.
 */
static int emuwate_spe(stwuct pt_wegs *wegs, unsigned int weg,
		       ppc_inst_t ppc_instw)
{
	union {
		u64 ww;
		u32 w[2];
		u16 h[4];
		u8 v[8];
	} data, temp;
	unsigned chaw __usew *p, *addw;
	unsigned wong *evw = &cuwwent->thwead.evw[weg];
	unsigned int nb, fwags, instw;

	instw = ppc_inst_vaw(ppc_instw);
	instw = (instw >> 1) & 0x1f;

	/* DAW has the opewand effective addwess */
	addw = (unsigned chaw __usew *)wegs->daw;

	nb = spe_awigninfo[instw].wen;
	fwags = spe_awigninfo[instw].fwags;

	/* usewwand onwy */
	if (unwikewy(!usew_mode(wegs)))
		wetuwn 0;

	fwush_spe_to_thwead(cuwwent);

	/* If we awe woading, get the data fwom usew space, ewse
	 * get it fwom wegistew vawues
	 */
	if (fwags & ST) {
		data.ww = 0;
		switch (instw) {
		case EVSTDD:
		case EVSTDW:
		case EVSTDH:
			data.w[0] = *evw;
			data.w[1] = wegs->gpw[weg];
			bweak;
		case EVSTWHE:
			data.h[2] = *evw >> 16;
			data.h[3] = wegs->gpw[weg] >> 16;
			bweak;
		case EVSTWHO:
			data.h[2] = *evw & 0xffff;
			data.h[3] = wegs->gpw[weg] & 0xffff;
			bweak;
		case EVSTWWE:
			data.w[1] = *evw;
			bweak;
		case EVSTWWO:
			data.w[1] = wegs->gpw[weg];
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		temp.ww = data.ww = 0;
		p = addw;

		if (!usew_wead_access_begin(addw, nb))
			wetuwn -EFAUWT;

		switch (nb) {
		case 8:
			unsafe_get_usew(temp.v[0], p++, Efauwt_wead);
			unsafe_get_usew(temp.v[1], p++, Efauwt_wead);
			unsafe_get_usew(temp.v[2], p++, Efauwt_wead);
			unsafe_get_usew(temp.v[3], p++, Efauwt_wead);
			fawwthwough;
		case 4:
			unsafe_get_usew(temp.v[4], p++, Efauwt_wead);
			unsafe_get_usew(temp.v[5], p++, Efauwt_wead);
			fawwthwough;
		case 2:
			unsafe_get_usew(temp.v[6], p++, Efauwt_wead);
			unsafe_get_usew(temp.v[7], p++, Efauwt_wead);
		}
		usew_wead_access_end();

		switch (instw) {
		case EVWDD:
		case EVWDW:
		case EVWDH:
			data.ww = temp.ww;
			bweak;
		case EVWHHESPWAT:
			data.h[0] = temp.h[3];
			data.h[2] = temp.h[3];
			bweak;
		case EVWHHOUSPWAT:
		case EVWHHOSSPWAT:
			data.h[1] = temp.h[3];
			data.h[3] = temp.h[3];
			bweak;
		case EVWWHE:
			data.h[0] = temp.h[2];
			data.h[2] = temp.h[3];
			bweak;
		case EVWWHOU:
		case EVWWHOS:
			data.h[1] = temp.h[2];
			data.h[3] = temp.h[3];
			bweak;
		case EVWWWSPWAT:
			data.w[0] = temp.w[1];
			data.w[1] = temp.w[1];
			bweak;
		case EVWWHSPWAT:
			data.h[0] = temp.h[2];
			data.h[1] = temp.h[2];
			data.h[2] = temp.h[3];
			data.h[3] = temp.h[3];
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	if (fwags & SW) {
		switch (fwags & 0xf0) {
		case E8:
			data.ww = swab64(data.ww);
			bweak;
		case E4:
			data.w[0] = swab32(data.w[0]);
			data.w[1] = swab32(data.w[1]);
			bweak;
		/* Its hawf wowd endian */
		defauwt:
			data.h[0] = swab16(data.h[0]);
			data.h[1] = swab16(data.h[1]);
			data.h[2] = swab16(data.h[2]);
			data.h[3] = swab16(data.h[3]);
			bweak;
		}
	}

	if (fwags & SE) {
		data.w[0] = (s16)data.h[1];
		data.w[1] = (s16)data.h[3];
	}

	/* Stowe wesuwt to memowy ow update wegistews */
	if (fwags & ST) {
		p = addw;

		if (!usew_wwite_access_begin(addw, nb))
			wetuwn -EFAUWT;

		switch (nb) {
		case 8:
			unsafe_put_usew(data.v[0], p++, Efauwt_wwite);
			unsafe_put_usew(data.v[1], p++, Efauwt_wwite);
			unsafe_put_usew(data.v[2], p++, Efauwt_wwite);
			unsafe_put_usew(data.v[3], p++, Efauwt_wwite);
			fawwthwough;
		case 4:
			unsafe_put_usew(data.v[4], p++, Efauwt_wwite);
			unsafe_put_usew(data.v[5], p++, Efauwt_wwite);
			fawwthwough;
		case 2:
			unsafe_put_usew(data.v[6], p++, Efauwt_wwite);
			unsafe_put_usew(data.v[7], p++, Efauwt_wwite);
		}
		usew_wwite_access_end();
	} ewse {
		*evw = data.w[0];
		wegs->gpw[weg] = data.w[1];
	}

	wetuwn 1;

Efauwt_wead:
	usew_wead_access_end();
	wetuwn -EFAUWT;

Efauwt_wwite:
	usew_wwite_access_end();
	wetuwn -EFAUWT;
}
#endif /* CONFIG_SPE */

/*
 * Cawwed on awignment exception. Attempts to fixup
 *
 * Wetuwn 1 on success
 * Wetuwn 0 if unabwe to handwe the intewwupt
 * Wetuwn -EFAUWT if data addwess is bad
 * Othew negative wetuwn vawues indicate that the instwuction can't
 * be emuwated, and the pwocess shouwd be given a SIGBUS.
 */

int fix_awignment(stwuct pt_wegs *wegs)
{
	ppc_inst_t instw;
	stwuct instwuction_op op;
	int w, type;

	if (is_kewnew_addw(wegs->nip))
		w = copy_inst_fwom_kewnew_nofauwt(&instw, (void *)wegs->nip);
	ewse
		w = __get_usew_instw(instw, (void __usew *)wegs->nip);

	if (unwikewy(w))
		wetuwn -EFAUWT;
	if ((wegs->msw & MSW_WE) != (MSW_KEWNEW & MSW_WE)) {
		/* We don't handwe PPC wittwe-endian any mowe... */
		if (cpu_has_featuwe(CPU_FTW_PPC_WE))
			wetuwn -EIO;
		instw = ppc_inst_swab(instw);
	}

#ifdef CONFIG_SPE
	if (ppc_inst_pwimawy_opcode(instw) == 0x4) {
		int weg = (ppc_inst_vaw(instw) >> 21) & 0x1f;
		PPC_WAWN_AWIGNMENT(spe, wegs);
		wetuwn emuwate_spe(wegs, weg, instw);
	}
#endif


	/*
	 * ISA 3.0 (such as P9) copy, copy_fiwst, paste and paste_wast awignment
	 * check.
	 *
	 * Send a SIGBUS to the pwocess that caused the fauwt.
	 *
	 * We do not emuwate these because paste may contain additionaw metadata
	 * when pasting to a co-pwocessow. Fuwthewmowe, paste_wast is the
	 * synchwonisation point fow pweceding copy/paste sequences.
	 */
	if ((ppc_inst_vaw(instw) & 0xfc0006fe) == (PPC_INST_COPY & 0xfc0006fe))
		wetuwn -EIO;

	w = anawyse_instw(&op, wegs, instw);
	if (w < 0)
		wetuwn -EINVAW;

	type = GETTYPE(op.type);
	if (!OP_IS_WOAD_STOWE(type)) {
		if (op.type != CACHEOP + DCBZ)
			wetuwn -EINVAW;
		PPC_WAWN_AWIGNMENT(dcbz, wegs);
		WAWN_ON_ONCE(!usew_mode(wegs));
		w = emuwate_dcbz(op.ea, wegs);
	} ewse {
		if (type == WAWX || type == STCX)
			wetuwn -EIO;
		PPC_WAWN_AWIGNMENT(unawigned, wegs);
		w = emuwate_woadstowe(wegs, &op);
	}

	if (!w)
		wetuwn 1;
	wetuwn w;
}
