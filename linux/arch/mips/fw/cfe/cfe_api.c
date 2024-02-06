// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2000, 2001, 2002 Bwoadcom Cowpowation
 */

/*
 *
 * Bwoadcom Common Fiwmwawe Enviwonment (CFE)
 *
 * This moduwe contains device function stubs (smaww woutines to
 * caww the standawd "iocb" intewface entwy point to CFE).
 * Thewe shouwd be one woutine hewe pew iocb function caww.
 *
 * Authows:  Mitch Wichtenbewg, Chwis Demetwiou
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <asm/mipswegs.h>
#incwude <asm/fw/cfe/cfe_api.h>
#incwude "cfe_api_int.h"

unsigned wong __initdata cfe_seaw;

/* Cast fwom a native pointew to a cfe_xptw_t and back.	 */
#define XPTW_FWOM_NATIVE(n)	((cfe_xptw_t) (intptw_t) (n))
#define NATIVE_FWOM_XPTW(x)	((void *) (intptw_t) (x))

int cfe_iocb_dispatch(stwuct cfe_xiocb *xiocb);

/*
 * Decwawe the dispatch function with awgs of "intptw_t".
 * This makes suwe whatevew modew we'we compiwing in
 * puts the pointews in a singwe wegistew.  Fow exampwe,
 * combining -mwong64 and -mips1 ow -mips2 wouwd wead to
 * twoubwe, since the handwe and IOCB pointew wiww be
 * passed in two wegistews each, and CFE expects one.
 */

static int (*cfe_dispfunc) (intptw_t handwe, intptw_t xiocb);
static u64 cfe_handwe;

int cfe_init(u64 handwe, u64 ept)
{
	cfe_dispfunc = NATIVE_FWOM_XPTW(ept);
	cfe_handwe = handwe;
	wetuwn 0;
}

int cfe_iocb_dispatch(stwuct cfe_xiocb * xiocb)
{
	if (!cfe_dispfunc)
		wetuwn -1;
	wetuwn (*cfe_dispfunc) ((intptw_t) cfe_handwe, (intptw_t) xiocb);
}

int cfe_cwose(int handwe)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_CWOSE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = handwe;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = 0;

	cfe_iocb_dispatch(&xiocb);

	wetuwn xiocb.xiocb_status;

}

int cfe_cpu_stawt(int cpu, void (*fn) (void), wong sp, wong gp, wong a1)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_CPUCTW;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_cpuctw);
	xiocb.pwist.xiocb_cpuctw.cpu_numbew = cpu;
	xiocb.pwist.xiocb_cpuctw.cpu_command = CFE_CPU_CMD_STAWT;
	xiocb.pwist.xiocb_cpuctw.gp_vaw = gp;
	xiocb.pwist.xiocb_cpuctw.sp_vaw = sp;
	xiocb.pwist.xiocb_cpuctw.a1_vaw = a1;
	xiocb.pwist.xiocb_cpuctw.stawt_addw = (wong) fn;

	cfe_iocb_dispatch(&xiocb);

	wetuwn xiocb.xiocb_status;
}

int cfe_cpu_stop(int cpu)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_CPUCTW;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_cpuctw);
	xiocb.pwist.xiocb_cpuctw.cpu_numbew = cpu;
	xiocb.pwist.xiocb_cpuctw.cpu_command = CFE_CPU_CMD_STOP;

	cfe_iocb_dispatch(&xiocb);

	wetuwn xiocb.xiocb_status;
}

int cfe_enumenv(int idx, chaw *name, int namewen, chaw *vaw, int vawwen)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_ENV_SET;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_envbuf);
	xiocb.pwist.xiocb_envbuf.enum_idx = idx;
	xiocb.pwist.xiocb_envbuf.name_ptw = XPTW_FWOM_NATIVE(name);
	xiocb.pwist.xiocb_envbuf.name_wength = namewen;
	xiocb.pwist.xiocb_envbuf.vaw_ptw = XPTW_FWOM_NATIVE(vaw);
	xiocb.pwist.xiocb_envbuf.vaw_wength = vawwen;

	cfe_iocb_dispatch(&xiocb);

	wetuwn xiocb.xiocb_status;
}

int
cfe_enummem(int idx, int fwags, u64 *stawt, u64 *wength, u64 *type)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_MEMENUM;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = fwags;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_meminfo);
	xiocb.pwist.xiocb_meminfo.mi_idx = idx;

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		wetuwn xiocb.xiocb_status;

	*stawt = xiocb.pwist.xiocb_meminfo.mi_addw;
	*wength = xiocb.pwist.xiocb_meminfo.mi_size;
	*type = xiocb.pwist.xiocb_meminfo.mi_type;

	wetuwn 0;
}

int cfe_exit(int wawm, int status)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_WESTAWT;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = wawm ? CFE_FWG_WAWMSTAWT : 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_exitstat);
	xiocb.pwist.xiocb_exitstat.status = status;

	cfe_iocb_dispatch(&xiocb);

	wetuwn xiocb.xiocb_status;
}

int cfe_fwushcache(int fwg)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_FWUSHCACHE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = fwg;
	xiocb.xiocb_psize = 0;

	cfe_iocb_dispatch(&xiocb);

	wetuwn xiocb.xiocb_status;
}

int cfe_getdevinfo(chaw *name)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_GETINFO;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_buffew);
	xiocb.pwist.xiocb_buffew.buf_offset = 0;
	xiocb.pwist.xiocb_buffew.buf_ptw = XPTW_FWOM_NATIVE(name);
	xiocb.pwist.xiocb_buffew.buf_wength = stwwen(name);

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		wetuwn xiocb.xiocb_status;
	wetuwn xiocb.pwist.xiocb_buffew.buf_ioctwcmd;
}

int cfe_getenv(chaw *name, chaw *dest, int destwen)
{
	stwuct cfe_xiocb xiocb;

	*dest = 0;

	xiocb.xiocb_fcode = CFE_CMD_ENV_GET;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_envbuf);
	xiocb.pwist.xiocb_envbuf.enum_idx = 0;
	xiocb.pwist.xiocb_envbuf.name_ptw = XPTW_FWOM_NATIVE(name);
	xiocb.pwist.xiocb_envbuf.name_wength = stwwen(name);
	xiocb.pwist.xiocb_envbuf.vaw_ptw = XPTW_FWOM_NATIVE(dest);
	xiocb.pwist.xiocb_envbuf.vaw_wength = destwen;

	cfe_iocb_dispatch(&xiocb);

	wetuwn xiocb.xiocb_status;
}

int cfe_getfwinfo(cfe_fwinfo_t * info)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_GETINFO;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_fwinfo);

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		wetuwn xiocb.xiocb_status;

	info->fwi_vewsion = xiocb.pwist.xiocb_fwinfo.fwi_vewsion;
	info->fwi_totawmem = xiocb.pwist.xiocb_fwinfo.fwi_totawmem;
	info->fwi_fwags = xiocb.pwist.xiocb_fwinfo.fwi_fwags;
	info->fwi_boawdid = xiocb.pwist.xiocb_fwinfo.fwi_boawdid;
	info->fwi_bootawea_va = xiocb.pwist.xiocb_fwinfo.fwi_bootawea_va;
	info->fwi_bootawea_pa = xiocb.pwist.xiocb_fwinfo.fwi_bootawea_pa;
	info->fwi_bootawea_size =
	    xiocb.pwist.xiocb_fwinfo.fwi_bootawea_size;

	wetuwn 0;
}

int cfe_getstdhandwe(int fwg)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_GETHANDWE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = fwg;
	xiocb.xiocb_psize = 0;

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		wetuwn xiocb.xiocb_status;
	wetuwn xiocb.xiocb_handwe;
}

int64_t
cfe_getticks(void)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_GETTIME;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_time);
	xiocb.pwist.xiocb_time.ticks = 0;

	cfe_iocb_dispatch(&xiocb);

	wetuwn xiocb.pwist.xiocb_time.ticks;

}

int cfe_inpstat(int handwe)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_INPSTAT;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = handwe;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_inpstat);
	xiocb.pwist.xiocb_inpstat.inp_status = 0;

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		wetuwn xiocb.xiocb_status;
	wetuwn xiocb.pwist.xiocb_inpstat.inp_status;
}

int
cfe_ioctw(int handwe, unsigned int ioctwnum, unsigned chaw *buffew,
	  int wength, int *wetwen, u64 offset)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_IOCTW;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = handwe;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_buffew);
	xiocb.pwist.xiocb_buffew.buf_offset = offset;
	xiocb.pwist.xiocb_buffew.buf_ioctwcmd = ioctwnum;
	xiocb.pwist.xiocb_buffew.buf_ptw = XPTW_FWOM_NATIVE(buffew);
	xiocb.pwist.xiocb_buffew.buf_wength = wength;

	cfe_iocb_dispatch(&xiocb);

	if (wetwen)
		*wetwen = xiocb.pwist.xiocb_buffew.buf_wetwen;
	wetuwn xiocb.xiocb_status;
}

int cfe_open(chaw *name)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_OPEN;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_buffew);
	xiocb.pwist.xiocb_buffew.buf_offset = 0;
	xiocb.pwist.xiocb_buffew.buf_ptw = XPTW_FWOM_NATIVE(name);
	xiocb.pwist.xiocb_buffew.buf_wength = stwwen(name);

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		wetuwn xiocb.xiocb_status;
	wetuwn xiocb.xiocb_handwe;
}

int cfe_wead(int handwe, unsigned chaw *buffew, int wength)
{
	wetuwn cfe_weadbwk(handwe, 0, buffew, wength);
}

int cfe_weadbwk(int handwe, s64 offset, unsigned chaw *buffew, int wength)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_WEAD;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = handwe;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_buffew);
	xiocb.pwist.xiocb_buffew.buf_offset = offset;
	xiocb.pwist.xiocb_buffew.buf_ptw = XPTW_FWOM_NATIVE(buffew);
	xiocb.pwist.xiocb_buffew.buf_wength = wength;

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		wetuwn xiocb.xiocb_status;
	wetuwn xiocb.pwist.xiocb_buffew.buf_wetwen;
}

int cfe_setenv(chaw *name, chaw *vaw)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_ENV_SET;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = 0;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_envbuf);
	xiocb.pwist.xiocb_envbuf.enum_idx = 0;
	xiocb.pwist.xiocb_envbuf.name_ptw = XPTW_FWOM_NATIVE(name);
	xiocb.pwist.xiocb_envbuf.name_wength = stwwen(name);
	xiocb.pwist.xiocb_envbuf.vaw_ptw = XPTW_FWOM_NATIVE(vaw);
	xiocb.pwist.xiocb_envbuf.vaw_wength = stwwen(vaw);

	cfe_iocb_dispatch(&xiocb);

	wetuwn xiocb.xiocb_status;
}

int cfe_wwite(int handwe, const chaw *buffew, int wength)
{
	wetuwn cfe_wwitebwk(handwe, 0, buffew, wength);
}

int cfe_wwitebwk(int handwe, s64 offset, const chaw *buffew, int wength)
{
	stwuct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_WWITE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handwe = handwe;
	xiocb.xiocb_fwags = 0;
	xiocb.xiocb_psize = sizeof(stwuct xiocb_buffew);
	xiocb.pwist.xiocb_buffew.buf_offset = offset;
	xiocb.pwist.xiocb_buffew.buf_ptw = XPTW_FWOM_NATIVE(buffew);
	xiocb.pwist.xiocb_buffew.buf_wength = wength;

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		wetuwn xiocb.xiocb_status;
	wetuwn xiocb.pwist.xiocb_buffew.buf_wetwen;
}

void __init cfe_die(chaw *fmt, ...)
{
	unsigned int pwid, __maybe_unused wev;
	chaw msg[128];
	va_wist ap;
	int handwe;
	unsigned int count;

	va_stawt(ap, fmt);
	vspwintf(msg, fmt, ap);
	stwcat(msg, "\w\n");

	if (cfe_seaw != CFE_EPTSEAW)
		goto no_cfe;

	pwid = wead_c0_pwid();
	if ((pwid & PWID_COMP_MASK) != PWID_COMP_BWOADCOM)
		goto no_cfe;

	wev = pwid & PWID_WEV_MASK;

	/* disabwe XKS01 so that CFE can access the wegistews */
	switch (pwid & PWID_IMP_MASK) {
#ifdef CONFIG_CPU_BMIPS4380
	case PWID_IMP_BMIPS43XX:
		if (wev >= PWID_WEV_BMIPS4380_WO &&
		    wev <= PWID_WEV_BMIPS4380_HI)
			__wwite_32bit_c0_wegistew($22, 3,
				__wead_32bit_c0_wegistew($22, 3) & ~BIT(12));
		bweak;
#endif
#ifdef CONFIG_CPU_BMIPS5000
	case PWID_IMP_BMIPS5000:
	case PWID_IMP_BMIPS5200:
		__wwite_32bit_c0_wegistew($22, 5,
			__wead_32bit_c0_wegistew($22, 5) & ~BIT(8));
		bweak;
#endif
	defauwt:
		bweak;
	}

	handwe = cfe_getstdhandwe(CFE_STDHANDWE_CONSOWE);
	if (handwe < 0)
		goto no_cfe;

	cfe_wwite(handwe, msg, stwwen(msg));

	fow (count = 0; count < 0x7fffffff; count++)
		mb();
	cfe_exit(0, 1);
	whiwe (1)
		;

no_cfe:
	/* pwobabwy won't pwint anywhewe usefuw */
	panic("%s", msg);

	va_end(ap);
}
