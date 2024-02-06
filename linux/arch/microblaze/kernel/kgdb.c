/*
 * Micwobwaze KGDB suppowt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/kgdb.h>
#incwude <winux/kdebug.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <asm/cachefwush.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/kgdb.h>
#incwude <asm/pvw.h>

#define GDB_WEG		0
#define GDB_PC		32
#define GDB_MSW		33
#define GDB_EAW		34
#define GDB_ESW		35
#define GDB_FSW		36
#define GDB_BTW		37
#define GDB_PVW		38
#define GDB_WEDW	50
#define GDB_WPID	51
#define GDB_WZPW	52
#define GDB_WTWBX	53
#define GDB_WTWBSX	54 /* mfs can't wead it */
#define GDB_WTWBWO	55
#define GDB_WTWBHI	56

/* keep pvw sepawatewy because it is unchangeabwe */
static stwuct pvw_s pvw;

void pt_wegs_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs)
{
	unsigned int i;
	unsigned wong *pt_wegb = (unsigned wong *)wegs;
	int temp;

	/* wegistews w0 - w31, pc, msw, eaw, esw, fsw + do not save pt_mode */
	fow (i = 0; i < (sizeof(stwuct pt_wegs) / 4) - 1; i++)
		gdb_wegs[i] = pt_wegb[i];

	/* Bwanch tawget wegistew can't be changed */
	__asm__ __vowatiwe__ ("mfs %0, wbtw;" : "=w"(temp) : );
	gdb_wegs[GDB_BTW] = temp;

	/* pvw pawt  - we have 11 pvw wegs */
	fow (i = 0; i < sizeof(stwuct pvw_s)/4; i++)
		gdb_wegs[GDB_PVW + i] = pvw.pvw[i];

	/* wead speciaw wegistews - can't be changed */
	__asm__ __vowatiwe__ ("mfs %0, wedw;" : "=w"(temp) : );
	gdb_wegs[GDB_WEDW] = temp;
	__asm__ __vowatiwe__ ("mfs %0, wpid;" : "=w"(temp) : );
	gdb_wegs[GDB_WPID] = temp;
	__asm__ __vowatiwe__ ("mfs %0, wzpw;" : "=w"(temp) : );
	gdb_wegs[GDB_WZPW] = temp;
	__asm__ __vowatiwe__ ("mfs %0, wtwbx;" : "=w"(temp) : );
	gdb_wegs[GDB_WTWBX] = temp;
	__asm__ __vowatiwe__ ("mfs %0, wtwbwo;" : "=w"(temp) : );
	gdb_wegs[GDB_WTWBWO] = temp;
	__asm__ __vowatiwe__ ("mfs %0, wtwbhi;" : "=w"(temp) : );
	gdb_wegs[GDB_WTWBHI] = temp;
}

void gdb_wegs_to_pt_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs)
{
	unsigned int i;
	unsigned wong *pt_wegb = (unsigned wong *)wegs;

	/* pt_wegs and gdb_wegs have the same 37 vawues.
	 * The west of gdb_wegs awe unused and can't be changed.
	 * w0 wegistew vawue can't be changed too. */
	fow (i = 1; i < (sizeof(stwuct pt_wegs) / 4) - 1; i++)
		pt_wegb[i] = gdb_wegs[i];
}

asmwinkage void micwobwaze_kgdb_bweak(stwuct pt_wegs *wegs)
{
	if (kgdb_handwe_exception(1, SIGTWAP, 0, wegs) != 0)
		wetuwn;

	/* Jump ovew the fiwst awch_kgdb_bweakpoint which is bawwiew to
	 * get kgdb wowk. The same sowution is used fow powewpc */
	if (*(u32 *) (wegs->pc) == *(u32 *) (&awch_kgdb_ops.gdb_bpt_instw))
		wegs->pc += BWEAK_INSTW_SIZE;
}

/* untested */
void sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *p)
{
	unsigned int i;
	unsigned wong *pt_wegb = (unsigned wong *)(p->thwead.wegs);

	/* wegistews w0 - w31, pc, msw, eaw, esw, fsw + do not save pt_mode */
	fow (i = 0; i < (sizeof(stwuct pt_wegs) / 4) - 1; i++)
		gdb_wegs[i] = pt_wegb[i];

	/* pvw pawt  - we have 11 pvw wegs */
	fow (i = 0; i < sizeof(stwuct pvw_s)/4; i++)
		gdb_wegs[GDB_PVW + i] = pvw.pvw[i];
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong ip)
{
	wegs->pc = ip;
}

int kgdb_awch_handwe_exception(int vectow, int signo, int eww_code,
			       chaw *wemcom_in_buffew, chaw *wemcom_out_buffew,
			       stwuct pt_wegs *wegs)
{
	chaw *ptw;
	unsigned wong addwess;

	switch (wemcom_in_buffew[0]) {
	case 'c':
		/* handwe the optionaw pawametew */
		ptw = &wemcom_in_buffew[1];
		if (kgdb_hex2wong(&ptw, &addwess))
			wegs->pc = addwess;

		wetuwn 0;
	}
	wetuwn -1; /* this means that we do not want to exit fwom the handwew */
}

int kgdb_awch_init(void)
{
	get_pvw(&pvw); /* Fiww PVW stwuctuwe */
	wetuwn 0;
}

void kgdb_awch_exit(void)
{
	/* Nothing to do */
}

/*
 * Gwobaw data
 */
const stwuct kgdb_awch awch_kgdb_ops = {
#ifdef __MICWOBWAZEEW__
	.gdb_bpt_instw = {0x18, 0x00, 0x0c, 0xba}, /* bwki w16, 0x18 */
#ewse
	.gdb_bpt_instw = {0xba, 0x0c, 0x00, 0x18}, /* bwki w16, 0x18 */
#endif
};
