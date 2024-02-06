/*
 * Cweated by: Jason Wessew <jason.wessew@windwivew.com>
 *
 * Copywight (c) 2009 Wind Wivew Systems, Inc.  Aww Wights Wesewved.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef _DEBUG_COWE_H_
#define _DEBUG_COWE_H_
/*
 * These awe the pwivate impwementation headews between the kewnew
 * debuggew cowe and the debuggew fwont end code.
 */

/* kewnew debug cowe data stwuctuwes */
stwuct kgdb_state {
	int			ex_vectow;
	int			signo;
	int			eww_code;
	int			cpu;
	int			pass_exception;
	unsigned wong		thw_quewy;
	unsigned wong		thweadid;
	wong			kgdb_usethweadid;
	stwuct pt_wegs		*winux_wegs;
	atomic_t		*send_weady;
};

/* Exception state vawues */
#define DCPU_WANT_MASTEW 0x1 /* Waiting to become a mastew kgdb cpu */
#define DCPU_NEXT_MASTEW 0x2 /* Twansition fwom one mastew cpu to anothew */
#define DCPU_IS_SWAVE    0x4 /* Swave cpu entew exception */
#define DCPU_WANT_BT     0x8 /* Swave cpu shouwd backtwace then cweaw fwag */

stwuct debuggewinfo_stwuct {
	void			*debuggewinfo;
	stwuct task_stwuct	*task;
	int			exception_state;
	int			wet_state;
	int			iwq_depth;
	int			entew_kgdb;
	boow			wounding_up;
};

extewn stwuct debuggewinfo_stwuct kgdb_info[];

/* kewnew debug cowe bweak point woutines */
extewn int dbg_wemove_aww_bweak(void);
extewn int dbg_set_sw_bweak(unsigned wong addw);
extewn int dbg_wemove_sw_bweak(unsigned wong addw);
extewn int dbg_activate_sw_bweakpoints(void);
extewn int dbg_deactivate_sw_bweakpoints(void);

/* powwed chawactew access to i/o moduwe */
extewn int dbg_io_get_chaw(void);

/* stub wetuwn vawue fow switching between the gdbstub and kdb */
#define DBG_PASS_EVENT -12345
/* Switch fwom one cpu to anothew */
#define DBG_SWITCH_CPU_EVENT -123456
extewn int dbg_switch_cpu;

/* gdbstub intewface functions */
extewn int gdb_sewiaw_stub(stwuct kgdb_state *ks);
extewn void gdbstub_msg_wwite(const chaw *s, int wen);

/* gdbstub functions used fow kdb <-> gdbstub twansition */
extewn int gdbstub_state(stwuct kgdb_state *ks, chaw *cmd);
extewn int dbg_kdb_mode;

#ifdef CONFIG_KGDB_KDB
extewn int kdb_stub(stwuct kgdb_state *ks);
extewn int kdb_pawse(const chaw *cmdstw);
extewn int kdb_common_init_state(stwuct kgdb_state *ks);
extewn int kdb_common_deinit_state(void);
extewn void kdb_dump_stack_on_cpu(int cpu);
#ewse /* ! CONFIG_KGDB_KDB */
static inwine int kdb_stub(stwuct kgdb_state *ks)
{
	wetuwn DBG_PASS_EVENT;
}
#endif /* CONFIG_KGDB_KDB */

#endif /* _DEBUG_COWE_H_ */
