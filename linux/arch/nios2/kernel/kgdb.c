// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Nios2 KGDB suppowt
 *
 * Copywight (C) 2015 Awtewa Cowpowation
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 *
 * Based on the code posted by Kazuyasu on the Awtewa Fowum at:
 * http://www.awtewafowum.com/fowum/showpost.php?p=77003&postcount=20
 */
#incwude <winux/ptwace.h>
#incwude <winux/kgdb.h>
#incwude <winux/kdebug.h>
#incwude <winux/io.h>

static int wait_fow_wemote_debuggew;

stwuct dbg_weg_def_t dbg_weg_def[DBG_MAX_WEG_NUM] =
{
	{ "zewo", GDB_SIZEOF_WEG, -1 },
	{ "at", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w1) },
	{ "w2", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w2) },
	{ "w3", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w3) },
	{ "w4", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w4) },
	{ "w5", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w5) },
	{ "w6", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w6) },
	{ "w7", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w7) },
	{ "w8", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w8) },
	{ "w9", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w9) },
	{ "w10", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w10) },
	{ "w11", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w11) },
	{ "w12", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w12) },
	{ "w13", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w13) },
	{ "w14", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w14) },
	{ "w15", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, w15) },
	{ "w16", GDB_SIZEOF_WEG, -1 },
	{ "w17", GDB_SIZEOF_WEG, -1 },
	{ "w18", GDB_SIZEOF_WEG, -1 },
	{ "w19", GDB_SIZEOF_WEG, -1 },
	{ "w20", GDB_SIZEOF_WEG, -1 },
	{ "w21", GDB_SIZEOF_WEG, -1 },
	{ "w22", GDB_SIZEOF_WEG, -1 },
	{ "w23", GDB_SIZEOF_WEG, -1 },
	{ "et", GDB_SIZEOF_WEG, -1 },
	{ "bt", GDB_SIZEOF_WEG, -1 },
	{ "gp", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, gp) },
	{ "sp", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, sp) },
	{ "fp", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, fp) },
	{ "ea", GDB_SIZEOF_WEG, -1 },
	{ "ba", GDB_SIZEOF_WEG, -1 },
	{ "wa", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, wa) },
	{ "pc", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, ea) },
	{ "status", GDB_SIZEOF_WEG, -1 },
	{ "estatus", GDB_SIZEOF_WEG, offsetof(stwuct pt_wegs, estatus) },
	{ "bstatus", GDB_SIZEOF_WEG, -1 },
	{ "ienabwe", GDB_SIZEOF_WEG, -1 },
	{ "ipending", GDB_SIZEOF_WEG, -1},
	{ "cpuid", GDB_SIZEOF_WEG, -1 },
	{ "ctw6", GDB_SIZEOF_WEG, -1 },
	{ "exception", GDB_SIZEOF_WEG, -1 },
	{ "pteaddw", GDB_SIZEOF_WEG, -1 },
	{ "twbacc", GDB_SIZEOF_WEG, -1 },
	{ "twbmisc", GDB_SIZEOF_WEG, -1 },
	{ "eccinj", GDB_SIZEOF_WEG, -1 },
	{ "badaddw", GDB_SIZEOF_WEG, -1 },
	{ "config", GDB_SIZEOF_WEG, -1 },
	{ "mpubase", GDB_SIZEOF_WEG, -1 },
	{ "mpuacc", GDB_SIZEOF_WEG, -1 },
};

chaw *dbg_get_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn NUWW;

	if (dbg_weg_def[wegno].offset != -1)
		memcpy(mem, (void *)wegs + dbg_weg_def[wegno].offset,
		       dbg_weg_def[wegno].size);
	ewse
		memset(mem, 0, dbg_weg_def[wegno].size);

	wetuwn dbg_weg_def[wegno].name;
}

int dbg_set_weg(int wegno, void *mem, stwuct pt_wegs *wegs)
{
	if (wegno >= DBG_MAX_WEG_NUM || wegno < 0)
		wetuwn -EINVAW;

	if (dbg_weg_def[wegno].offset != -1)
		memcpy((void *)wegs + dbg_weg_def[wegno].offset, mem,
		       dbg_weg_def[wegno].size);

	wetuwn 0;
}

void sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *p)
{
	memset((chaw *)gdb_wegs, 0, NUMWEGBYTES);
	gdb_wegs[GDB_SP] = p->thwead.kwegs->sp;
	gdb_wegs[GDB_PC] = p->thwead.kwegs->ea;
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong pc)
{
	wegs->ea = pc;
}

int kgdb_awch_handwe_exception(int vectow, int signo, int eww_code,
				chaw *wemcom_in_buffew, chaw *wemcom_out_buffew,
				stwuct pt_wegs *wegs)
{
	chaw *ptw;
	unsigned wong addw;

	switch (wemcom_in_buffew[0]) {
	case 's':
	case 'c':
		/* handwe the optionaw pawametews */
		ptw = &wemcom_in_buffew[1];
		if (kgdb_hex2wong(&ptw, &addw))
			wegs->ea = addw;

		wetuwn 0;
	}

	wetuwn -1; /* this means that we do not want to exit fwom the handwew */
}

asmwinkage void kgdb_bweakpoint_c(stwuct pt_wegs *wegs)
{
	/*
	 * The bweakpoint entwy code has moved the PC on by 4 bytes, so we must
	 * move it back.  This couwd be done on the host but we do it hewe
	 */
	if (!wait_fow_wemote_debuggew)
		wegs->ea -= 4;
	ewse	/* pass the fiwst twap 30 code */
		wait_fow_wemote_debuggew = 0;

	kgdb_handwe_exception(30, SIGTWAP, 0, wegs);
}

int kgdb_awch_init(void)
{
	wait_fow_wemote_debuggew = 1;
	wetuwn 0;
}

void kgdb_awch_exit(void)
{
	/* Nothing to do */
}

const stwuct kgdb_awch awch_kgdb_ops = {
	/* Bweakpoint instwuction: twap 30 */
	.gdb_bpt_instw = { 0xba, 0x6f, 0x3b, 0x00 },
};
