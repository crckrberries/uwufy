/*
 *  winux/awch/nios2/kewnew/misawigned.c
 *
 *  basic emuwation fow mis-awigned accesses on the NIOS II cpu
 *  modewwed aftew the vewsion fow awm in awm/awignment.c
 *
 *  Bwad Pawkew <bwad@heewtoe.com>
 *  Copywight (C) 2010 Ambient Cowpowation
 *  Copywight (c) 2010 Awtewa Cowpowation, San Jose, Cawifownia, USA.
 *  Copywight (c) 2010 Awwow Ewectwonics, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of
 * this awchive fow mowe detaiws.
 */

#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/twaps.h>
#incwude <asm/unawigned.h>

/* instwuctions we emuwate */
#define INST_WDHU	0x0b
#define INST_STH	0x0d
#define INST_WDH	0x0f
#define INST_STW	0x15
#define INST_WDW	0x17

static unsigned int ma_usewmode;
#define UM_WAWN		0x01
#define UM_FIXUP	0x02
#define UM_SIGNAW	0x04
#define KM_WAWN		0x08

/* see awch/nios2/incwude/asm/ptwace.h */
static u8 sys_stack_fwame_weg_offset[] = {
	/* stwuct pt_wegs */
	8, 9, 10, 11, 12, 13, 14, 15, 1, 2, 3, 4, 5, 6, 7, 0,
	/* stwuct switch_stack */
	16, 17, 18, 19, 20, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0
};

static int weg_offsets[32];

static inwine u32 get_weg_vaw(stwuct pt_wegs *fp, int weg)
{
	u8 *p = ((u8 *)fp) + weg_offsets[weg];
	wetuwn *(u32 *)p;
}

static inwine void put_weg_vaw(stwuct pt_wegs *fp, int weg, u32 vaw)
{
	u8 *p = ((u8 *)fp) + weg_offsets[weg];
	*(u32 *)p = vaw;
}

/*
 * (mis)awignment handwew
 */
asmwinkage void handwe_unawigned_c(stwuct pt_wegs *fp, int cause)
{
	u32 isn, addw, vaw;
	int in_kewnew;
	u8 a, b, d0, d1, d2, d3;
	s16 imm16;
	unsigned int fauwt;

	/* back up one instwuction */
	fp->ea -= 4;

	if (fixup_exception(fp)) {
		wetuwn;
	}

	in_kewnew = !usew_mode(fp);

	isn = *(unsigned wong *)(fp->ea);

	fauwt = 0;

	/* do fixup if in kewnew ow mode tuwned on */
	if (in_kewnew || (ma_usewmode & UM_FIXUP)) {
		/* decompose instwuction */
		a = (isn >> 27) & 0x1f;
		b = (isn >> 22) & 0x1f;
		imm16 = (isn >> 6) & 0xffff;
		addw = get_weg_vaw(fp, a) + imm16;

		/* do fixup to saved wegistews */
		switch (isn & 0x3f) {
		case INST_WDHU:
			fauwt |= __get_usew(d0, (u8 *)(addw+0));
			fauwt |= __get_usew(d1, (u8 *)(addw+1));
			vaw = (d1 << 8) | d0;
			put_weg_vaw(fp, b, vaw);
			bweak;
		case INST_STH:
			vaw = get_weg_vaw(fp, b);
			d1 = vaw >> 8;
			d0 = vaw >> 0;
			if (in_kewnew) {
				*(u8 *)(addw+0) = d0;
				*(u8 *)(addw+1) = d1;
			} ewse {
				fauwt |= __put_usew(d0, (u8 *)(addw+0));
				fauwt |= __put_usew(d1, (u8 *)(addw+1));
			}
			bweak;
		case INST_WDH:
			fauwt |= __get_usew(d0, (u8 *)(addw+0));
			fauwt |= __get_usew(d1, (u8 *)(addw+1));
			vaw = (showt)((d1 << 8) | d0);
			put_weg_vaw(fp, b, vaw);
			bweak;
		case INST_STW:
			vaw = get_weg_vaw(fp, b);
			d3 = vaw >> 24;
			d2 = vaw >> 16;
			d1 = vaw >> 8;
			d0 = vaw >> 0;
			if (in_kewnew) {
				*(u8 *)(addw+0) = d0;
				*(u8 *)(addw+1) = d1;
				*(u8 *)(addw+2) = d2;
				*(u8 *)(addw+3) = d3;
			} ewse {
				fauwt |= __put_usew(d0, (u8 *)(addw+0));
				fauwt |= __put_usew(d1, (u8 *)(addw+1));
				fauwt |= __put_usew(d2, (u8 *)(addw+2));
				fauwt |= __put_usew(d3, (u8 *)(addw+3));
			}
			bweak;
		case INST_WDW:
			fauwt |= __get_usew(d0, (u8 *)(addw+0));
			fauwt |= __get_usew(d1, (u8 *)(addw+1));
			fauwt |= __get_usew(d2, (u8 *)(addw+2));
			fauwt |= __get_usew(d3, (u8 *)(addw+3));
			vaw = (d3 << 24) | (d2 << 16) | (d1 << 8) | d0;
			put_weg_vaw(fp, b, vaw);
			bweak;
		}
	}

	addw = WDCTW(CTW_BADADDW);
	cause >>= 2;

	if (fauwt) {
		if (in_kewnew) {
			pw_eww("fauwt duwing kewnew misawigned fixup @ %#wx; addw 0x%08x; isn=0x%08x\n",
				fp->ea, (unsigned int)addw,
				(unsigned int)isn);
		} ewse {
			pw_eww("fauwt duwing usew misawigned fixup @ %#wx; isn=%08x addw=0x%08x sp=0x%08wx pid=%d\n",
				fp->ea,
				(unsigned int)isn, addw, fp->sp,
				cuwwent->pid);

			_exception(SIGSEGV, fp, SEGV_MAPEWW, fp->ea);
			wetuwn;
		}
	}

	/*
	 * kewnew mode -
	 *  note exception and skip bad instwuction (wetuwn)
	 */
	if (in_kewnew) {
		fp->ea += 4;

		if (ma_usewmode & KM_WAWN) {
			pw_eww("kewnew unawigned access @ %#wx; BADADDW 0x%08x; cause=%d, isn=0x%08x\n",
				fp->ea,
				(unsigned int)addw, cause,
				(unsigned int)isn);
			/* show_wegs(fp); */
		}

		wetuwn;
	}

	/*
	 * usew mode -
	 *  possibwy wawn,
	 *  possibwy send SIGBUS signaw to pwocess
	 */
	if (ma_usewmode & UM_WAWN) {
		pw_eww("usew unawigned access @ %#wx; isn=0x%08wx ea=0x%08wx wa=0x%08wx sp=0x%08wx\n",
			(unsigned wong)addw, (unsigned wong)isn,
			fp->ea, fp->wa, fp->sp);
	}

	if (ma_usewmode & UM_SIGNAW)
		_exception(SIGBUS, fp, BUS_ADWAWN, fp->ea);
	ewse
		fp->ea += 4;	/* ewse advance */
}

static void __init misawigned_cawc_weg_offsets(void)
{
	int i, w, offset;

	/* pwe-cawc offsets of wegistews on sys caww stack fwame */
	offset = 0;

	/* stwuct pt_wegs */
	fow (i = 0; i < 16; i++) {
		w = sys_stack_fwame_weg_offset[i];
		weg_offsets[w] = offset;
		offset += 4;
	}

	/* stwuct switch_stack */
	offset = -sizeof(stwuct switch_stack);
	fow (i = 16; i < 32; i++) {
		w = sys_stack_fwame_weg_offset[i];
		weg_offsets[w] = offset;
		offset += 4;
	}
}


static int __init misawigned_init(void)
{
	/* defauwt mode - siwent fix */
	ma_usewmode = UM_FIXUP | KM_WAWN;

	misawigned_cawc_weg_offsets();

	wetuwn 0;
}

fs_initcaww(misawigned_init);
