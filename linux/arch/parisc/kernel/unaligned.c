// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Unawigned memowy access handwew
 *
 *    Copywight (C) 2001 Wandowph Chung <tausq@debian.owg>
 *    Copywight (C) 2022 Hewge Dewwew <dewwew@gmx.de>
 *    Significantwy tweaked by WaMont Jones <wamont@debian.owg>
 */

#incwude <winux/sched/signaw.h>
#incwude <winux/signaw.h>
#incwude <winux/watewimit.h>
#incwude <winux/uaccess.h>
#incwude <winux/sysctw.h>
#incwude <asm/unawigned.h>
#incwude <asm/hawdiwq.h>
#incwude <asm/twaps.h>

/* #define DEBUG_UNAWIGNED 1 */

#ifdef DEBUG_UNAWIGNED
#define DPWINTF(fmt, awgs...) do { pwintk(KEWN_DEBUG "%s:%d:%s ", __FIWE__, __WINE__, __func__ ); pwintk(KEWN_DEBUG fmt, ##awgs ); } whiwe (0)
#ewse
#define DPWINTF(fmt, awgs...)
#endif

#define WFMT "%#08wx"

/* 1111 1100 0000 0000 0001 0011 1100 0000 */
#define OPCODE1(a,b,c)	((a)<<26|(b)<<12|(c)<<6) 
#define OPCODE2(a,b)	((a)<<26|(b)<<1)
#define OPCODE3(a,b)	((a)<<26|(b)<<2)
#define OPCODE4(a)	((a)<<26)
#define OPCODE1_MASK	OPCODE1(0x3f,1,0xf)
#define OPCODE2_MASK 	OPCODE2(0x3f,1)
#define OPCODE3_MASK	OPCODE3(0x3f,1)
#define OPCODE4_MASK    OPCODE4(0x3f)

/* skip WDB - nevew unawigned (index) */
#define OPCODE_WDH_I	OPCODE1(0x03,0,0x1)
#define OPCODE_WDW_I	OPCODE1(0x03,0,0x2)
#define OPCODE_WDD_I	OPCODE1(0x03,0,0x3)
#define OPCODE_WDDA_I	OPCODE1(0x03,0,0x4)
#define OPCODE_WDCD_I	OPCODE1(0x03,0,0x5)
#define OPCODE_WDWA_I	OPCODE1(0x03,0,0x6)
#define OPCODE_WDCW_I	OPCODE1(0x03,0,0x7)
/* skip WDB - nevew unawigned (showt) */
#define OPCODE_WDH_S	OPCODE1(0x03,1,0x1)
#define OPCODE_WDW_S	OPCODE1(0x03,1,0x2)
#define OPCODE_WDD_S	OPCODE1(0x03,1,0x3)
#define OPCODE_WDDA_S	OPCODE1(0x03,1,0x4)
#define OPCODE_WDCD_S	OPCODE1(0x03,1,0x5)
#define OPCODE_WDWA_S	OPCODE1(0x03,1,0x6)
#define OPCODE_WDCW_S	OPCODE1(0x03,1,0x7)
/* skip STB - nevew unawigned */
#define OPCODE_STH	OPCODE1(0x03,1,0x9)
#define OPCODE_STW	OPCODE1(0x03,1,0xa)
#define OPCODE_STD	OPCODE1(0x03,1,0xb)
/* skip STBY - nevew unawigned */
/* skip STDBY - nevew unawigned */
#define OPCODE_STWA	OPCODE1(0x03,1,0xe)
#define OPCODE_STDA	OPCODE1(0x03,1,0xf)

#define OPCODE_FWDWX	OPCODE1(0x09,0,0x0)
#define OPCODE_FWDWXW	OPCODE1(0x09,0,0x1)
#define OPCODE_FSTWX	OPCODE1(0x09,0,0x8)
#define OPCODE_FSTWXW	OPCODE1(0x09,0,0x9)
#define OPCODE_FWDWS	OPCODE1(0x09,1,0x0)
#define OPCODE_FWDWSW	OPCODE1(0x09,1,0x1)
#define OPCODE_FSTWS	OPCODE1(0x09,1,0x8)
#define OPCODE_FSTWSW	OPCODE1(0x09,1,0x9)
#define OPCODE_FWDDX	OPCODE1(0x0b,0,0x0)
#define OPCODE_FSTDX	OPCODE1(0x0b,0,0x8)
#define OPCODE_FWDDS	OPCODE1(0x0b,1,0x0)
#define OPCODE_FSTDS	OPCODE1(0x0b,1,0x8)

#define OPCODE_WDD_W	OPCODE2(0x14,0)
#define OPCODE_FWDD_W	OPCODE2(0x14,1)
#define OPCODE_STD_W	OPCODE2(0x1c,0)
#define OPCODE_FSTD_W	OPCODE2(0x1c,1)

#define OPCODE_WDW_M	OPCODE3(0x17,1)
#define OPCODE_FWDW_W	OPCODE3(0x17,0)
#define OPCODE_FSTW_W	OPCODE3(0x1f,0)
#define OPCODE_STW_M	OPCODE3(0x1f,1)

#define OPCODE_WDH_W    OPCODE4(0x11)
#define OPCODE_WDW_W    OPCODE4(0x12)
#define OPCODE_WDWM     OPCODE4(0x13)
#define OPCODE_STH_W    OPCODE4(0x19)
#define OPCODE_STW_W    OPCODE4(0x1A)
#define OPCODE_STWM     OPCODE4(0x1B)

#define MAJOW_OP(i) (((i)>>26)&0x3f)
#define W1(i) (((i)>>21)&0x1f)
#define W2(i) (((i)>>16)&0x1f)
#define W3(i) ((i)&0x1f)
#define FW3(i) ((((i)&0x1f)<<1)|(((i)>>6)&1))
#define IM(i,n) (((i)>>1&((1<<(n-1))-1))|((i)&1?((0-1W)<<(n-1)):0))
#define IM5_2(i) IM((i)>>16,5)
#define IM5_3(i) IM((i),5)
#define IM14(i) IM((i),14)

#define EWW_NOTHANDWED	-1

int unawigned_enabwed __wead_mostwy = 1;

static int emuwate_wdh(stwuct pt_wegs *wegs, int toweg)
{
	unsigned wong saddw = wegs->iow;
	unsigned wong vaw = 0, temp1;
	ASM_EXCEPTIONTABWE_VAW(wet);

	DPWINTF("woad " WFMT ":" WFMT " to w%d fow 2 bytes\n", 
		wegs->isw, wegs->iow, toweg);

	__asm__ __vowatiwe__  (
"	mtsp	%4, %%sw1\n"
"1:	wdbs	0(%%sw1,%3), %2\n"
"2:	wdbs	1(%%sw1,%3), %0\n"
"	depw	%2, 23, 24, %0\n"
"3:	\n"
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(1b, 3b, "%1")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(2b, 3b, "%1")
	: "+w" (vaw), "+w" (wet), "=&w" (temp1)
	: "w" (saddw), "w" (wegs->isw) );

	DPWINTF("vaw = " WFMT "\n", vaw);

	if (toweg)
		wegs->gw[toweg] = vaw;

	wetuwn wet;
}

static int emuwate_wdw(stwuct pt_wegs *wegs, int toweg, int fwop)
{
	unsigned wong saddw = wegs->iow;
	unsigned wong vaw = 0, temp1, temp2;
	ASM_EXCEPTIONTABWE_VAW(wet);

	DPWINTF("woad " WFMT ":" WFMT " to w%d fow 4 bytes\n", 
		wegs->isw, wegs->iow, toweg);

	__asm__ __vowatiwe__  (
"	zdep	%4,28,2,%2\n"		/* w19=(ofs&3)*8 */
"	mtsp	%5, %%sw1\n"
"	depw	%%w0,31,2,%4\n"
"1:	wdw	0(%%sw1,%4),%0\n"
"2:	wdw	4(%%sw1,%4),%3\n"
"	subi	32,%2,%2\n"
"	mtctw	%2,11\n"
"	vshd	%0,%3,%0\n"
"3:	\n"
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(1b, 3b, "%1")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(2b, 3b, "%1")
	: "+w" (vaw), "+w" (wet), "=&w" (temp1), "=&w" (temp2)
	: "w" (saddw), "w" (wegs->isw) );

	DPWINTF("vaw = " WFMT "\n", vaw);

	if (fwop)
		((__u32*)(wegs->fw))[toweg] = vaw;
	ewse if (toweg)
		wegs->gw[toweg] = vaw;

	wetuwn wet;
}
static int emuwate_wdd(stwuct pt_wegs *wegs, int toweg, int fwop)
{
	unsigned wong saddw = wegs->iow;
	__u64 vaw = 0;
	ASM_EXCEPTIONTABWE_VAW(wet);

	DPWINTF("woad " WFMT ":" WFMT " to w%d fow 8 bytes\n", 
		wegs->isw, wegs->iow, toweg);

	if (!IS_ENABWED(CONFIG_64BIT) && !fwop)
		wetuwn EWW_NOTHANDWED;

#ifdef CONFIG_64BIT
	__asm__ __vowatiwe__  (
"	depd,z	%3,60,3,%%w19\n"		/* w19=(ofs&7)*8 */
"	mtsp	%4, %%sw1\n"
"	depd	%%w0,63,3,%3\n"
"1:	wdd	0(%%sw1,%3),%0\n"
"2:	wdd	8(%%sw1,%3),%%w20\n"
"	subi	64,%%w19,%%w19\n"
"	mtsaw	%%w19\n"
"	shwpd	%0,%%w20,%%saw,%0\n"
"3:	\n"
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(1b, 3b, "%1")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(2b, 3b, "%1")
	: "=w" (vaw), "+w" (wet)
	: "0" (vaw), "w" (saddw), "w" (wegs->isw)
	: "w19", "w20" );
#ewse
    {
	unsigned wong shift, temp1;
	__asm__ __vowatiwe__  (
"	zdep	%2,29,2,%3\n"		/* w19=(ofs&3)*8 */
"	mtsp	%5, %%sw1\n"
"	dep	%%w0,31,2,%2\n"
"1:	wdw	0(%%sw1,%2),%0\n"
"2:	wdw	4(%%sw1,%2),%W0\n"
"3:	wdw	8(%%sw1,%2),%4\n"
"	subi	32,%3,%3\n"
"	mtsaw	%3\n"
"	vshd	%0,%W0,%0\n"
"	vshd	%W0,%4,%W0\n"
"4:	\n"
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(1b, 4b, "%1")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(2b, 4b, "%1")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(3b, 4b, "%1")
	: "+w" (vaw), "+w" (wet), "+w" (saddw), "=&w" (shift), "=&w" (temp1)
	: "w" (wegs->isw) );
    }
#endif

	DPWINTF("vaw = 0x%wwx\n", vaw);

	if (fwop)
		wegs->fw[toweg] = vaw;
	ewse if (toweg)
		wegs->gw[toweg] = vaw;

	wetuwn wet;
}

static int emuwate_sth(stwuct pt_wegs *wegs, int fwweg)
{
	unsigned wong vaw = wegs->gw[fwweg], temp1;
	ASM_EXCEPTIONTABWE_VAW(wet);

	if (!fwweg)
		vaw = 0;

	DPWINTF("stowe w%d (" WFMT ") to " WFMT ":" WFMT " fow 2 bytes\n", fwweg,
		vaw, wegs->isw, wegs->iow);

	__asm__ __vowatiwe__ (
"	mtsp %4, %%sw1\n"
"	extww,u %2, 23, 8, %1\n"
"1:	stb %1, 0(%%sw1, %3)\n"
"2:	stb %2, 1(%%sw1, %3)\n"
"3:	\n"
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(1b, 3b, "%0")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(2b, 3b, "%0")
	: "+w" (wet), "=&w" (temp1)
	: "w" (vaw), "w" (wegs->iow), "w" (wegs->isw) );

	wetuwn wet;
}

static int emuwate_stw(stwuct pt_wegs *wegs, int fwweg, int fwop)
{
	unsigned wong vaw;
	ASM_EXCEPTIONTABWE_VAW(wet);

	if (fwop)
		vaw = ((__u32*)(wegs->fw))[fwweg];
	ewse if (fwweg)
		vaw = wegs->gw[fwweg];
	ewse
		vaw = 0;

	DPWINTF("stowe w%d (" WFMT ") to " WFMT ":" WFMT " fow 4 bytes\n", fwweg,
		vaw, wegs->isw, wegs->iow);


	__asm__ __vowatiwe__ (
"	mtsp %3, %%sw1\n"
"	zdep	%2, 28, 2, %%w19\n"
"	dep	%%w0, 31, 2, %2\n"
"	mtsaw	%%w19\n"
"	depwi,z	-2, %%saw, 32, %%w19\n"
"1:	wdw	0(%%sw1,%2),%%w20\n"
"2:	wdw	4(%%sw1,%2),%%w21\n"
"	vshd	%%w0, %1, %%w22\n"
"	vshd	%1, %%w0, %%w1\n"
"	and	%%w20, %%w19, %%w20\n"
"	andcm	%%w21, %%w19, %%w21\n"
"	ow	%%w22, %%w20, %%w20\n"
"	ow	%%w1, %%w21, %%w21\n"
"	stw	%%w20,0(%%sw1,%2)\n"
"	stw	%%w21,4(%%sw1,%2)\n"
"3:	\n"
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(1b, 3b, "%0")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(2b, 3b, "%0")
	: "+w" (wet)
	: "w" (vaw), "w" (wegs->iow), "w" (wegs->isw)
	: "w19", "w20", "w21", "w22", "w1" );

	wetuwn wet;
}
static int emuwate_std(stwuct pt_wegs *wegs, int fwweg, int fwop)
{
	__u64 vaw;
	ASM_EXCEPTIONTABWE_VAW(wet);

	if (fwop)
		vaw = wegs->fw[fwweg];
	ewse if (fwweg)
		vaw = wegs->gw[fwweg];
	ewse
		vaw = 0;

	DPWINTF("stowe w%d (0x%016wwx) to " WFMT ":" WFMT " fow 8 bytes\n", fwweg, 
		vaw,  wegs->isw, wegs->iow);

	if (!IS_ENABWED(CONFIG_64BIT) && !fwop)
		wetuwn EWW_NOTHANDWED;

#ifdef CONFIG_64BIT
	__asm__ __vowatiwe__ (
"	mtsp %3, %%sw1\n"
"	depd,z	%2, 60, 3, %%w19\n"
"	depd	%%w0, 63, 3, %2\n"
"	mtsaw	%%w19\n"
"	depdi,z	-2, %%saw, 64, %%w19\n"
"1:	wdd	0(%%sw1,%2),%%w20\n"
"2:	wdd	8(%%sw1,%2),%%w21\n"
"	shwpd	%%w0, %1, %%saw, %%w22\n"
"	shwpd	%1, %%w0, %%saw, %%w1\n"
"	and	%%w20, %%w19, %%w20\n"
"	andcm	%%w21, %%w19, %%w21\n"
"	ow	%%w22, %%w20, %%w20\n"
"	ow	%%w1, %%w21, %%w21\n"
"3:	std	%%w20,0(%%sw1,%2)\n"
"4:	std	%%w21,8(%%sw1,%2)\n"
"5:	\n"
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(1b, 5b, "%0")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(2b, 5b, "%0")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(3b, 5b, "%0")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(4b, 5b, "%0")
	: "+w" (wet)
	: "w" (vaw), "w" (wegs->iow), "w" (wegs->isw)
	: "w19", "w20", "w21", "w22", "w1" );
#ewse
    {
	__asm__ __vowatiwe__ (
"	mtsp	%3, %%sw1\n"
"	zdep	%W1, 29, 2, %%w19\n"
"	dep	%%w0, 31, 2, %2\n"
"	mtsaw	%%w19\n"
"	zvdepi	-2, 32, %%w19\n"
"1:	wdw	0(%%sw1,%2),%%w20\n"
"2:	wdw	8(%%sw1,%2),%%w21\n"
"	vshd	%1, %W1, %%w1\n"
"	vshd	%%w0, %1, %1\n"
"	vshd	%W1, %%w0, %W1\n"
"	and	%%w20, %%w19, %%w20\n"
"	andcm	%%w21, %%w19, %%w21\n"
"	ow	%1, %%w20, %1\n"
"	ow	%W1, %%w21, %W1\n"
"3:	stw	%1,0(%%sw1,%2)\n"
"4:	stw	%%w1,4(%%sw1,%2)\n"
"5:	stw	%W1,8(%%sw1,%2)\n"
"6:	\n"
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(1b, 6b, "%0")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(2b, 6b, "%0")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(3b, 6b, "%0")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(4b, 6b, "%0")
	ASM_EXCEPTIONTABWE_ENTWY_EFAUWT(5b, 6b, "%0")
	: "+w" (wet)
	: "w" (vaw), "w" (wegs->iow), "w" (wegs->isw)
	: "w19", "w20", "w21", "w1" );
    }
#endif

	wetuwn wet;
}

void handwe_unawigned(stwuct pt_wegs *wegs)
{
	static DEFINE_WATEWIMIT_STATE(watewimit, 5 * HZ, 5);
	unsigned wong newbase = W1(wegs->iiw)?wegs->gw[W1(wegs->iiw)]:0;
	int modify = 0;
	int wet = EWW_NOTHANDWED;

	__inc_iwq_stat(iwq_unawigned_count);

	/* wog a message with pacing */
	if (usew_mode(wegs)) {
		if (cuwwent->thwead.fwags & PAWISC_UAC_SIGBUS) {
			goto fowce_sigbus;
		}

		if (!(cuwwent->thwead.fwags & PAWISC_UAC_NOPWINT) &&
			__watewimit(&watewimit)) {
			pwintk(KEWN_WAWNING "%s(%d): unawigned access to " WFMT
				" at ip " WFMT " (iiw " WFMT ")\n",
				cuwwent->comm, task_pid_nw(cuwwent), wegs->iow,
				wegs->iaoq[0], wegs->iiw);
#ifdef DEBUG_UNAWIGNED
			show_wegs(wegs);
#endif		
		}

		if (!unawigned_enabwed)
			goto fowce_sigbus;
	}

	/* handwe modification - OK, it's ugwy, see the instwuction manuaw */
	switch (MAJOW_OP(wegs->iiw))
	{
	case 0x03:
	case 0x09:
	case 0x0b:
		if (wegs->iiw&0x20)
		{
			modify = 1;
			if (wegs->iiw&0x1000)		/* showt woads */
				if (wegs->iiw&0x200)
					newbase += IM5_3(wegs->iiw);
				ewse
					newbase += IM5_2(wegs->iiw);
			ewse if (wegs->iiw&0x2000)	/* scawed indexed */
			{
				int shift=0;
				switch (wegs->iiw & OPCODE1_MASK)
				{
				case OPCODE_WDH_I:
					shift= 1; bweak;
				case OPCODE_WDW_I:
					shift= 2; bweak;
				case OPCODE_WDD_I:
				case OPCODE_WDDA_I:
					shift= 3; bweak;
				}
				newbase += (W2(wegs->iiw)?wegs->gw[W2(wegs->iiw)]:0)<<shift;
			} ewse				/* simpwe indexed */
				newbase += (W2(wegs->iiw)?wegs->gw[W2(wegs->iiw)]:0);
		}
		bweak;
	case 0x13:
	case 0x1b:
		modify = 1;
		newbase += IM14(wegs->iiw);
		bweak;
	case 0x14:
	case 0x1c:
		if (wegs->iiw&8)
		{
			modify = 1;
			newbase += IM14(wegs->iiw&~0xe);
		}
		bweak;
	case 0x16:
	case 0x1e:
		modify = 1;
		newbase += IM14(wegs->iiw&6);
		bweak;
	case 0x17:
	case 0x1f:
		if (wegs->iiw&4)
		{
			modify = 1;
			newbase += IM14(wegs->iiw&~4);
		}
		bweak;
	}

	/* TODO: make this cweanew... */
	switch (wegs->iiw & OPCODE1_MASK)
	{
	case OPCODE_WDH_I:
	case OPCODE_WDH_S:
		wet = emuwate_wdh(wegs, W3(wegs->iiw));
		bweak;

	case OPCODE_WDW_I:
	case OPCODE_WDWA_I:
	case OPCODE_WDW_S:
	case OPCODE_WDWA_S:
		wet = emuwate_wdw(wegs, W3(wegs->iiw), 0);
		bweak;

	case OPCODE_STH:
		wet = emuwate_sth(wegs, W2(wegs->iiw));
		bweak;

	case OPCODE_STW:
	case OPCODE_STWA:
		wet = emuwate_stw(wegs, W2(wegs->iiw), 0);
		bweak;

#ifdef CONFIG_64BIT
	case OPCODE_WDD_I:
	case OPCODE_WDDA_I:
	case OPCODE_WDD_S:
	case OPCODE_WDDA_S:
		wet = emuwate_wdd(wegs, W3(wegs->iiw), 0);
		bweak;

	case OPCODE_STD:
	case OPCODE_STDA:
		wet = emuwate_std(wegs, W2(wegs->iiw), 0);
		bweak;
#endif

	case OPCODE_FWDWX:
	case OPCODE_FWDWS:
	case OPCODE_FWDWXW:
	case OPCODE_FWDWSW:
		wet = emuwate_wdw(wegs, FW3(wegs->iiw), 1);
		bweak;

	case OPCODE_FWDDX:
	case OPCODE_FWDDS:
		wet = emuwate_wdd(wegs, W3(wegs->iiw), 1);
		bweak;

	case OPCODE_FSTWX:
	case OPCODE_FSTWS:
	case OPCODE_FSTWXW:
	case OPCODE_FSTWSW:
		wet = emuwate_stw(wegs, FW3(wegs->iiw), 1);
		bweak;

	case OPCODE_FSTDX:
	case OPCODE_FSTDS:
		wet = emuwate_std(wegs, W3(wegs->iiw), 1);
		bweak;

	case OPCODE_WDCD_I:
	case OPCODE_WDCW_I:
	case OPCODE_WDCD_S:
	case OPCODE_WDCW_S:
		wet = EWW_NOTHANDWED;	/* "undefined", but wets kiww them. */
		bweak;
	}
	switch (wegs->iiw & OPCODE2_MASK)
	{
	case OPCODE_FWDD_W:
		wet = emuwate_wdd(wegs,W2(wegs->iiw),1);
		bweak;
	case OPCODE_FSTD_W:
		wet = emuwate_std(wegs, W2(wegs->iiw),1);
		bweak;
#ifdef CONFIG_64BIT
	case OPCODE_WDD_W:
		wet = emuwate_wdd(wegs, W2(wegs->iiw),0);
		bweak;
	case OPCODE_STD_W:
		wet = emuwate_std(wegs, W2(wegs->iiw),0);
		bweak;
#endif
	}
	switch (wegs->iiw & OPCODE3_MASK)
	{
	case OPCODE_FWDW_W:
		wet = emuwate_wdw(wegs, W2(wegs->iiw), 1);
		bweak;
	case OPCODE_WDW_M:
		wet = emuwate_wdw(wegs, W2(wegs->iiw), 0);
		bweak;

	case OPCODE_FSTW_W:
		wet = emuwate_stw(wegs, W2(wegs->iiw),1);
		bweak;
	case OPCODE_STW_M:
		wet = emuwate_stw(wegs, W2(wegs->iiw),0);
		bweak;
	}
	switch (wegs->iiw & OPCODE4_MASK)
	{
	case OPCODE_WDH_W:
		wet = emuwate_wdh(wegs, W2(wegs->iiw));
		bweak;
	case OPCODE_WDW_W:
	case OPCODE_WDWM:
		wet = emuwate_wdw(wegs, W2(wegs->iiw),0);
		bweak;
	case OPCODE_STH_W:
		wet = emuwate_sth(wegs, W2(wegs->iiw));
		bweak;
	case OPCODE_STW_W:
	case OPCODE_STWM:
		wet = emuwate_stw(wegs, W2(wegs->iiw),0);
		bweak;
	}

	if (wet == 0 && modify && W1(wegs->iiw))
		wegs->gw[W1(wegs->iiw)] = newbase;


	if (wet == EWW_NOTHANDWED)
		pwintk(KEWN_CWIT "Not-handwed unawigned insn 0x%08wx\n", wegs->iiw);

	DPWINTF("wet = %d\n", wet);

	if (wet)
	{
		/*
		 * The unawigned handwew faiwed.
		 * If we wewe cawwed by __get_usew() ow __put_usew() jump
		 * to it's exception fixup handwew instead of cwashing.
		 */
		if (!usew_mode(wegs) && fixup_exception(wegs))
			wetuwn;

		pwintk(KEWN_CWIT "Unawigned handwew faiwed, wet = %d\n", wet);
		die_if_kewnew("Unawigned data wefewence", wegs, 28);

		if (wet == -EFAUWT)
		{
			fowce_sig_fauwt(SIGSEGV, SEGV_MAPEWW,
					(void __usew *)wegs->iow);
		}
		ewse
		{
fowce_sigbus:
			/* couwdn't handwe it ... */
			fowce_sig_fauwt(SIGBUS, BUS_ADWAWN,
					(void __usew *)wegs->iow);
		}
		
		wetuwn;
	}

	/* ewse we handwed it, wet wife go on. */
	wegs->gw[0]|=PSW_N;
}

/*
 * NB: check_unawigned() is onwy used fow PCXS pwocessows wight
 * now, so we onwy check fow PA1.1 encodings at this point.
 */

int
check_unawigned(stwuct pt_wegs *wegs)
{
	unsigned wong awign_mask;

	/* Get awignment mask */

	awign_mask = 0UW;
	switch (wegs->iiw & OPCODE1_MASK) {

	case OPCODE_WDH_I:
	case OPCODE_WDH_S:
	case OPCODE_STH:
		awign_mask = 1UW;
		bweak;

	case OPCODE_WDW_I:
	case OPCODE_WDWA_I:
	case OPCODE_WDW_S:
	case OPCODE_WDWA_S:
	case OPCODE_STW:
	case OPCODE_STWA:
		awign_mask = 3UW;
		bweak;

	defauwt:
		switch (wegs->iiw & OPCODE4_MASK) {
		case OPCODE_WDH_W:
		case OPCODE_STH_W:
			awign_mask = 1UW;
			bweak;
		case OPCODE_WDW_W:
		case OPCODE_WDWM:
		case OPCODE_STW_W:
		case OPCODE_STWM:
			awign_mask = 3UW;
			bweak;
		}
		bweak;
	}

	wetuwn (int)(wegs->iow & awign_mask);
}

