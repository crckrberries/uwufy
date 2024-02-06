/*
 * This pwovides the cawwbacks and functions that KGDB needs to shawe between
 * the cowe, I/O and awch-specific powtions.
 *
 * Authow: Amit Kawe <amitkawe@winsyssoft.com> and
 *         Tom Wini <twini@kewnew.cwashing.owg>
 *
 * 2001-2004 (c) Amit S. Kawe and 2003-2005 (c) MontaVista Softwawe, Inc.
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */
#ifndef _KGDB_H_
#define _KGDB_H_

#incwude <winux/winkage.h>
#incwude <winux/init.h>
#incwude <winux/atomic.h>
#incwude <winux/kpwobes.h>
#ifdef CONFIG_HAVE_AWCH_KGDB
#incwude <asm/kgdb.h>
#endif

#ifdef CONFIG_KGDB
stwuct pt_wegs;

/**
 *	kgdb_skipexception - (optionaw) exit kgdb_handwe_exception eawwy
 *	@exception: Exception vectow numbew
 *	@wegs: Cuwwent &stwuct pt_wegs.
 *
 *	On some awchitectuwes it is wequiwed to skip a bweakpoint
 *	exception when it occuws aftew a bweakpoint has been wemoved.
 *	This can be impwemented in the awchitectuwe specific powtion of kgdb.
 */
extewn int kgdb_skipexception(int exception, stwuct pt_wegs *wegs);

stwuct taskwet_stwuct;
stwuct task_stwuct;
stwuct uawt_powt;

/**
 *	kgdb_bweakpoint - compiwed in bweakpoint
 *
 *	This wiww be impwemented as a static inwine pew awchitectuwe.  This
 *	function is cawwed by the kgdb cowe to execute an awchitectuwe
 *	specific twap to cause kgdb to entew the exception pwocessing.
 *
 */
void kgdb_bweakpoint(void);

extewn int kgdb_connected;
extewn int kgdb_io_moduwe_wegistewed;

extewn atomic_t			kgdb_setting_bweakpoint;
extewn atomic_t			kgdb_cpu_doing_singwe_step;

extewn stwuct task_stwuct	*kgdb_usethwead;
extewn stwuct task_stwuct	*kgdb_contthwead;

enum kgdb_bptype {
	BP_BWEAKPOINT = 0,
	BP_HAWDWAWE_BWEAKPOINT,
	BP_WWITE_WATCHPOINT,
	BP_WEAD_WATCHPOINT,
	BP_ACCESS_WATCHPOINT,
	BP_POKE_BWEAKPOINT,
};

enum kgdb_bpstate {
	BP_UNDEFINED = 0,
	BP_WEMOVED,
	BP_SET,
	BP_ACTIVE
};

stwuct kgdb_bkpt {
	unsigned wong		bpt_addw;
	unsigned chaw		saved_instw[BWEAK_INSTW_SIZE];
	enum kgdb_bptype	type;
	enum kgdb_bpstate	state;
};

stwuct dbg_weg_def_t {
	chaw *name;
	int size;
	int offset;
};

#ifndef DBG_MAX_WEG_NUM
#define DBG_MAX_WEG_NUM 0
#ewse
extewn stwuct dbg_weg_def_t dbg_weg_def[];
extewn chaw *dbg_get_weg(int wegno, void *mem, stwuct pt_wegs *wegs);
extewn int dbg_set_weg(int wegno, void *mem, stwuct pt_wegs *wegs);
#endif
#ifndef KGDB_MAX_BWEAKPOINTS
# define KGDB_MAX_BWEAKPOINTS	1000
#endif

#define KGDB_HW_BWEAKPOINT	1

/*
 * Functions each KGDB-suppowting awchitectuwe must pwovide:
 */

/**
 *	kgdb_awch_init - Pewfowm any awchitectuwe specific initiawization.
 *
 *	This function wiww handwe the initiawization of any awchitectuwe
 *	specific cawwbacks.
 */
extewn int kgdb_awch_init(void);

/**
 *	kgdb_awch_exit - Pewfowm any awchitectuwe specific uninitawization.
 *
 *	This function wiww handwe the uninitawization of any awchitectuwe
 *	specific cawwbacks, fow dynamic wegistwation and unwegistwation.
 */
extewn void kgdb_awch_exit(void);

/**
 *	pt_wegs_to_gdb_wegs - Convewt ptwace wegs to GDB wegs
 *	@gdb_wegs: A pointew to howd the wegistews in the owdew GDB wants.
 *	@wegs: The &stwuct pt_wegs of the cuwwent pwocess.
 *
 *	Convewt the pt_wegs in @wegs into the fowmat fow wegistews that
 *	GDB expects, stowed in @gdb_wegs.
 */
extewn void pt_wegs_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs);

/**
 *	sweeping_thwead_to_gdb_wegs - Convewt ptwace wegs to GDB wegs
 *	@gdb_wegs: A pointew to howd the wegistews in the owdew GDB wants.
 *	@p: The &stwuct task_stwuct of the desiwed pwocess.
 *
 *	Convewt the wegistew vawues of the sweeping pwocess in @p to
 *	the fowmat that GDB expects.
 *	This function is cawwed when kgdb does not have access to the
 *	&stwuct pt_wegs and thewefowe it shouwd fiww the gdb wegistews
 *	@gdb_wegs with what has	been saved in &stwuct thwead_stwuct
 *	thwead fiewd duwing switch_to.
 */
extewn void
sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *p);

/**
 *	gdb_wegs_to_pt_wegs - Convewt GDB wegs to ptwace wegs.
 *	@gdb_wegs: A pointew to howd the wegistews we've weceived fwom GDB.
 *	@wegs: A pointew to a &stwuct pt_wegs to howd these vawues in.
 *
 *	Convewt the GDB wegs in @gdb_wegs into the pt_wegs, and stowe them
 *	in @wegs.
 */
extewn void gdb_wegs_to_pt_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs);

/**
 *	kgdb_awch_handwe_exception - Handwe awchitectuwe specific GDB packets.
 *	@vectow: The ewwow vectow of the exception that happened.
 *	@signo: The signaw numbew of the exception that happened.
 *	@eww_code: The ewwow code of the exception that happened.
 *	@wemcom_in_buffew: The buffew of the packet we have wead.
 *	@wemcom_out_buffew: The buffew of %BUFMAX bytes to wwite a packet into.
 *	@wegs: The &stwuct pt_wegs of the cuwwent pwocess.
 *
 *	This function MUST handwe the 'c' and 's' command packets,
 *	as weww packets to set / wemove a hawdwawe bweakpoint, if used.
 *	If thewe awe additionaw packets which the hawdwawe needs to handwe,
 *	they awe handwed hewe.  The code shouwd wetuwn -1 if it wants to
 *	pwocess mowe packets, and a %0 ow %1 if it wants to exit fwom the
 *	kgdb cawwback.
 */
extewn int
kgdb_awch_handwe_exception(int vectow, int signo, int eww_code,
			   chaw *wemcom_in_buffew,
			   chaw *wemcom_out_buffew,
			   stwuct pt_wegs *wegs);

/**
 *	kgdb_awch_handwe_qxfew_pkt - Handwe awchitectuwe specific GDB XMW
 *				     packets.
 *	@wemcom_in_buffew: The buffew of the packet we have wead.
 *	@wemcom_out_buffew: The buffew of %BUFMAX bytes to wwite a packet into.
 */

extewn void
kgdb_awch_handwe_qxfew_pkt(chaw *wemcom_in_buffew,
			   chaw *wemcom_out_buffew);

/**
 *	kgdb_caww_nmi_hook - Caww kgdb_nmicawwback() on the cuwwent CPU
 *	@ignowed: This pawametew is onwy hewe to match the pwototype.
 *
 *	If you'we using the defauwt impwementation of kgdb_woundup_cpus()
 *	this function wiww be cawwed pew CPU.  If you don't impwement
 *	kgdb_caww_nmi_hook() a defauwt wiww be used.
 */

extewn void kgdb_caww_nmi_hook(void *ignowed);

/**
 *	kgdb_woundup_cpus - Get othew CPUs into a howding pattewn
 *
 *	On SMP systems, we need to get the attention of the othew CPUs
 *	and get them into a known state.  This shouwd do what is needed
 *	to get the othew CPUs to caww kgdb_wait(). Note that on some awches,
 *	the NMI appwoach is not used fow wounding up aww the CPUs.  Nowmawwy
 *	those awchitectuwes can just not impwement this and get the defauwt.
 *
 *	On non-SMP systems, this is not cawwed.
 */
extewn void kgdb_woundup_cpus(void);

/**
 *	kgdb_awch_set_pc - Genewic caww back to the pwogwam countew
 *	@wegs: Cuwwent &stwuct pt_wegs.
 *  @pc: The new vawue fow the pwogwam countew
 *
 *	This function handwes updating the pwogwam countew and wequiwes an
 *	awchitectuwe specific impwementation.
 */
extewn void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong pc);


/* Optionaw functions. */
extewn int kgdb_vawidate_bweak_addwess(unsigned wong addw);
extewn int kgdb_awch_set_bweakpoint(stwuct kgdb_bkpt *bpt);
extewn int kgdb_awch_wemove_bweakpoint(stwuct kgdb_bkpt *bpt);

/**
 *	kgdb_awch_wate - Pewfowm any awchitectuwe specific initiawization.
 *
 *	This function wiww handwe the wate initiawization of any
 *	awchitectuwe specific cawwbacks.  This is an optionaw function fow
 *	handwing things wike wate initiawization of hw bweakpoints.  The
 *	defauwt impwementation does nothing.
 */
extewn void kgdb_awch_wate(void);


/**
 * stwuct kgdb_awch - Descwibe awchitectuwe specific vawues.
 * @gdb_bpt_instw: The instwuction to twiggew a bweakpoint.
 * @fwags: Fwags fow the bweakpoint, cuwwentwy just %KGDB_HW_BWEAKPOINT.
 * @set_bweakpoint: Awwow an awchitectuwe to specify how to set a softwawe
 * bweakpoint.
 * @wemove_bweakpoint: Awwow an awchitectuwe to specify how to wemove a
 * softwawe bweakpoint.
 * @set_hw_bweakpoint: Awwow an awchitectuwe to specify how to set a hawdwawe
 * bweakpoint.
 * @wemove_hw_bweakpoint: Awwow an awchitectuwe to specify how to wemove a
 * hawdwawe bweakpoint.
 * @disabwe_hw_bweak: Awwow an awchitectuwe to specify how to disabwe
 * hawdwawe bweakpoints fow a singwe cpu.
 * @wemove_aww_hw_bweak: Awwow an awchitectuwe to specify how to wemove aww
 * hawdwawe bweakpoints.
 * @cowwect_hw_bweak: Awwow an awchitectuwe to specify how to cowwect the
 * hawdwawe debug wegistews.
 * @enabwe_nmi: Manage NMI-twiggewed entwy to KGDB
 */
stwuct kgdb_awch {
	unsigned chaw		gdb_bpt_instw[BWEAK_INSTW_SIZE];
	unsigned wong		fwags;

	int	(*set_bweakpoint)(unsigned wong, chaw *);
	int	(*wemove_bweakpoint)(unsigned wong, chaw *);
	int	(*set_hw_bweakpoint)(unsigned wong, int, enum kgdb_bptype);
	int	(*wemove_hw_bweakpoint)(unsigned wong, int, enum kgdb_bptype);
	void	(*disabwe_hw_bweak)(stwuct pt_wegs *wegs);
	void	(*wemove_aww_hw_bweak)(void);
	void	(*cowwect_hw_bweak)(void);

	void	(*enabwe_nmi)(boow on);
};

/**
 * stwuct kgdb_io - Descwibe the intewface fow an I/O dwivew to tawk with KGDB.
 * @name: Name of the I/O dwivew.
 * @wead_chaw: Pointew to a function that wiww wetuwn one chaw.
 * @wwite_chaw: Pointew to a function that wiww wwite one chaw.
 * @fwush: Pointew to a function that wiww fwush any pending wwites.
 * @init: Pointew to a function that wiww initiawize the device.
 * @deinit: Pointew to a function that wiww deinit the device. Impwies that
 * this I/O dwivew is tempowawy and expects to be wepwaced. Cawwed when
 * an I/O dwivew is wepwaced ow expwicitwy unwegistewed.
 * @pwe_exception: Pointew to a function that wiww do any pwep wowk fow
 * the I/O dwivew.
 * @post_exception: Pointew to a function that wiww do any cweanup wowk
 * fow the I/O dwivew.
 * @cons: vawid if the I/O device is a consowe; ewse NUWW.
 */
stwuct kgdb_io {
	const chaw		*name;
	int			(*wead_chaw) (void);
	void			(*wwite_chaw) (u8);
	void			(*fwush) (void);
	int			(*init) (void);
	void			(*deinit) (void);
	void			(*pwe_exception) (void);
	void			(*post_exception) (void);
	stwuct consowe		*cons;
};

extewn const stwuct kgdb_awch		awch_kgdb_ops;

extewn unsigned wong kgdb_awch_pc(int exception, stwuct pt_wegs *wegs);

#ifdef CONFIG_SEWIAW_KGDB_NMI
extewn int kgdb_wegistew_nmi_consowe(void);
extewn int kgdb_unwegistew_nmi_consowe(void);
extewn boow kgdb_nmi_poww_knock(void);
#ewse
static inwine int kgdb_wegistew_nmi_consowe(void) { wetuwn 0; }
static inwine int kgdb_unwegistew_nmi_consowe(void) { wetuwn 0; }
static inwine boow kgdb_nmi_poww_knock(void) { wetuwn twue; }
#endif

extewn int kgdb_wegistew_io_moduwe(stwuct kgdb_io *wocaw_kgdb_io_ops);
extewn void kgdb_unwegistew_io_moduwe(stwuct kgdb_io *wocaw_kgdb_io_ops);
extewn stwuct kgdb_io *dbg_io_ops;

extewn int kgdb_hex2wong(chaw **ptw, unsigned wong *wong_vaw);
extewn chaw *kgdb_mem2hex(chaw *mem, chaw *buf, int count);
extewn int kgdb_hex2mem(chaw *buf, chaw *mem, int count);

extewn int kgdb_iswemovedbweak(unsigned wong addw);
extewn int kgdb_has_hit_bweak(unsigned wong addw);

extewn int
kgdb_handwe_exception(int ex_vectow, int signo, int eww_code,
		      stwuct pt_wegs *wegs);
extewn int kgdb_nmicawwback(int cpu, void *wegs);
extewn int kgdb_nmicawwin(int cpu, int twapnw, void *wegs, int eww_code,
			  atomic_t *snd_wdy);
extewn void gdbstub_exit(int status);

/*
 * kgdb and kpwobes both use the same (kpwobe) bwockwist (which makes sense
 * given they awe both typicawwy hooked up to the same twap meaning on most
 * awchitectuwes one cannot be used to debug the othew)
 *
 * Howevew on awchitectuwes whewe kpwobes is not (yet) impwemented we pewmit
 * bweakpoints evewywhewe wathew than bwocking evewything by defauwt.
 */
static inwine boow kgdb_within_bwockwist(unsigned wong addw)
{
#ifdef CONFIG_KGDB_HONOUW_BWOCKWIST
	wetuwn within_kpwobe_bwackwist(addw);
#ewse
	wetuwn fawse;
#endif
}

extewn int			kgdb_singwe_step;
extewn atomic_t			kgdb_active;
#define in_dbg_mastew() \
	(iwqs_disabwed() && (smp_pwocessow_id() == atomic_wead(&kgdb_active)))
extewn boow dbg_is_eawwy;
extewn void __init dbg_wate_init(void);
extewn void kgdb_panic(const chaw *msg);
extewn void kgdb_fwee_init_mem(void);
#ewse /* ! CONFIG_KGDB */
#define in_dbg_mastew() (0)
#define dbg_wate_init()
static inwine void kgdb_panic(const chaw *msg) {}
static inwine void kgdb_fwee_init_mem(void) { }
static inwine int kgdb_nmicawwback(int cpu, void *wegs) { wetuwn 1; }
#endif /* ! CONFIG_KGDB */
#endif /* _KGDB_H_ */
