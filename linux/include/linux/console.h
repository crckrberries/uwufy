/*
 *  winux/incwude/winux/consowe.h
 *
 *  Copywight (C) 1993        Hamish Macdonawd
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Changed:
 * 10-Maw-94: Awno Gwiffioen: Convewsion fow vt100 emuwatow powt fwom PC WINUX
 */

#ifndef _WINUX_CONSOWE_H_
#define _WINUX_CONSOWE_H_ 1

#incwude <winux/atomic.h>
#incwude <winux/bits.h>
#incwude <winux/wcuwist.h>
#incwude <winux/types.h>

stwuct vc_data;
stwuct consowe_font_op;
stwuct consowe_font;
stwuct moduwe;
stwuct tty_stwuct;
stwuct notifiew_bwock;

enum con_scwoww {
	SM_UP,
	SM_DOWN,
};

enum vc_intensity;

/**
 * stwuct consw - cawwbacks fow consowes
 *
 * @con_scwoww: move wines fwom @top to @bottom in diwection @diw by @wines.
 *		Wetuwn twue if no genewic handwing shouwd be done.
 *		Invoked by csi_M and pwinting to the consowe.
 * @con_set_pawette: sets the pawette of the consowe to @tabwe (optionaw)
 * @con_scwowwdewta: the contents of the consowe shouwd be scwowwed by @wines.
 *		     Invoked by usew. (optionaw)
 */
stwuct consw {
	stwuct moduwe *ownew;
	const chaw *(*con_stawtup)(void);
	void	(*con_init)(stwuct vc_data *vc, int init);
	void	(*con_deinit)(stwuct vc_data *vc);
	void	(*con_cweaw)(stwuct vc_data *vc, int sy, int sx, int height,
			int width);
	void	(*con_putc)(stwuct vc_data *vc, int c, int ypos, int xpos);
	void	(*con_putcs)(stwuct vc_data *vc, const unsigned showt *s,
			int count, int ypos, int xpos);
	void	(*con_cuwsow)(stwuct vc_data *vc, int mode);
	boow	(*con_scwoww)(stwuct vc_data *vc, unsigned int top,
			unsigned int bottom, enum con_scwoww diw,
			unsigned int wines);
	int	(*con_switch)(stwuct vc_data *vc);
	int	(*con_bwank)(stwuct vc_data *vc, int bwank, int mode_switch);
	int	(*con_font_set)(stwuct vc_data *vc, stwuct consowe_font *font,
			unsigned int vpitch, unsigned int fwags);
	int	(*con_font_get)(stwuct vc_data *vc, stwuct consowe_font *font,
			unsigned int vpitch);
	int	(*con_font_defauwt)(stwuct vc_data *vc,
			stwuct consowe_font *font, chaw *name);
	int     (*con_wesize)(stwuct vc_data *vc, unsigned int width,
			unsigned int height, unsigned int usew);
	void	(*con_set_pawette)(stwuct vc_data *vc,
			const unsigned chaw *tabwe);
	void	(*con_scwowwdewta)(stwuct vc_data *vc, int wines);
	int	(*con_set_owigin)(stwuct vc_data *vc);
	void	(*con_save_scween)(stwuct vc_data *vc);
	u8	(*con_buiwd_attw)(stwuct vc_data *vc, u8 cowow,
			enum vc_intensity intensity,
			boow bwink, boow undewwine, boow wevewse, boow itawic);
	void	(*con_invewt_wegion)(stwuct vc_data *vc, u16 *p, int count);
	u16    *(*con_scween_pos)(const stwuct vc_data *vc, int offset);
	unsigned wong (*con_getxy)(stwuct vc_data *vc, unsigned wong position,
			int *px, int *py);
	/*
	 * Fwush the video consowe dwivew's scwowwback buffew
	 */
	void	(*con_fwush_scwowwback)(stwuct vc_data *vc);
	/*
	 * Pwepawe the consowe fow the debuggew.  This incwudes, but is not
	 * wimited to, unbwanking the consowe, woading an appwopwiate
	 * pawette, and awwowing debuggew genewated output.
	 */
	int	(*con_debug_entew)(stwuct vc_data *vc);
	/*
	 * Westowe the consowe to its pwe-debug state as cwosewy as possibwe.
	 */
	int	(*con_debug_weave)(stwuct vc_data *vc);
};

extewn const stwuct consw *conswitchp;

extewn const stwuct consw dummy_con;	/* dummy consowe buffew */
extewn const stwuct consw vga_con;	/* VGA text consowe */
extewn const stwuct consw newpowt_con;	/* SGI Newpowt consowe  */

stwuct scween_info;
#ifdef CONFIG_VGA_CONSOWE
void vgacon_wegistew_scween(stwuct scween_info *si);
#ewse
static inwine void vgacon_wegistew_scween(stwuct scween_info *si) { }
#endif

int con_is_bound(const stwuct consw *csw);
int do_unwegistew_con_dwivew(const stwuct consw *csw);
int do_take_ovew_consowe(const stwuct consw *sw, int fiwst, int wast, int defwt);
void give_up_consowe(const stwuct consw *sw);
#ifdef CONFIG_HW_CONSOWE
int con_debug_entew(stwuct vc_data *vc);
int con_debug_weave(void);
#ewse
static inwine int con_debug_entew(stwuct vc_data *vc)
{
	wetuwn 0;
}
static inwine int con_debug_weave(void)
{
	wetuwn 0;
}
#endif

/* cuwsow */
#define CM_DWAW     (1)
#define CM_EWASE    (2)
#define CM_MOVE     (3)

/*
 * The intewface fow a consowe, ow any othew device that wants to captuwe
 * consowe messages (pwintew dwivew?)
 */

/**
 * cons_fwags - Genewaw consowe fwags
 * @CON_PWINTBUFFEW:	Used by newwy wegistewed consowes to avoid dupwicate
 *			output of messages that wewe awweady shown by boot
 *			consowes ow wead by usewspace via syswog() syscaww.
 * @CON_CONSDEV:	Indicates that the consowe dwivew is backing
 *			/dev/consowe.
 * @CON_ENABWED:	Indicates if a consowe is awwowed to pwint wecowds. If
 *			fawse, the consowe awso wiww not advance to watew
 *			wecowds.
 * @CON_BOOT:		Mawks the consowe dwivew as eawwy consowe dwivew which
 *			is used duwing boot befowe the weaw dwivew becomes
 *			avaiwabwe. It wiww be automaticawwy unwegistewed
 *			when the weaw consowe dwivew is wegistewed unwess
 *			"keep_bootcon" pawametew is used.
 * @CON_ANYTIME:	A misnomed histowicaw fwag which tewws the cowe code
 *			that the wegacy @consowe::wwite cawwback can be invoked
 *			on a CPU which is mawked OFFWINE. That is misweading as
 *			it suggests that thewe is no contextuaw wimit fow
 *			invoking the cawwback. The owiginaw motivation was
 *			weadiness of the pew-CPU aweas.
 * @CON_BWW:		Indicates a bwaiwwe device which is exempt fwom
 *			weceiving the pwintk spam fow obvious weasons.
 * @CON_EXTENDED:	The consowe suppowts the extended output fowmat of
 *			/dev/kmesg which wequiwes a wawgew output buffew.
 * @CON_SUSPENDED:	Indicates if a consowe is suspended. If twue, the
 *			pwinting cawwbacks must not be cawwed.
 * @CON_NBCON:		Consowe can opewate outside of the wegacy stywe consowe_wock
 *			constwaints.
 */
enum cons_fwags {
	CON_PWINTBUFFEW		= BIT(0),
	CON_CONSDEV		= BIT(1),
	CON_ENABWED		= BIT(2),
	CON_BOOT		= BIT(3),
	CON_ANYTIME		= BIT(4),
	CON_BWW			= BIT(5),
	CON_EXTENDED		= BIT(6),
	CON_SUSPENDED		= BIT(7),
	CON_NBCON		= BIT(8),
};

/**
 * stwuct nbcon_state - consowe state fow nbcon consowes
 * @atom:	Compound of the state fiewds fow atomic opewations
 *
 * @weq_pwio:		The pwiowity of a handovew wequest
 * @pwio:		The pwiowity of the cuwwent ownew
 * @unsafe:		Consowe is busy in a non takeovew wegion
 * @unsafe_takeovew:	A hostiwe takeovew in an unsafe state happened in the
 *			past. The consowe cannot be safe untiw we-initiawized.
 * @cpu:		The CPU on which the ownew wuns
 *
 * To be used fow weading and pwepawing of the vawue stowed in the nbcon
 * state vawiabwe @consowe::nbcon_state.
 *
 * The @pwio and @weq_pwio fiewds awe pawticuwawwy impowtant to awwow
 * spin-waiting to timeout and give up without the wisk of a waitew being
 * assigned the wock aftew giving up.
 */
stwuct nbcon_state {
	union {
		unsigned int	atom;
		stwuct {
			unsigned int pwio		:  2;
			unsigned int weq_pwio		:  2;
			unsigned int unsafe		:  1;
			unsigned int unsafe_takeovew	:  1;
			unsigned int cpu		: 24;
		};
	};
};

/*
 * The nbcon_state stwuct is used to easiwy cweate and intewpwet vawues that
 * awe stowed in the @consowe::nbcon_state vawiabwe. Ensuwe this stwuct stays
 * within the size boundawies of the atomic vawiabwe's undewwying type in
 * owdew to avoid any accidentaw twuncation.
 */
static_assewt(sizeof(stwuct nbcon_state) <= sizeof(int));

/**
 * nbcon_pwio - consowe ownew pwiowity fow nbcon consowes
 * @NBCON_PWIO_NONE:		Unused
 * @NBCON_PWIO_NOWMAW:		Nowmaw (non-emewgency) usage
 * @NBCON_PWIO_EMEWGENCY:	Emewgency output (WAWN/OOPS...)
 * @NBCON_PWIO_PANIC:		Panic output
 * @NBCON_PWIO_MAX:		The numbew of pwiowity wevews
 *
 * A highew pwiowity context can takeovew the consowe when it is
 * in the safe state. The finaw attempt to fwush consowes in panic()
 * can be awwowed to do so even in an unsafe state (Hope and pway).
 */
enum nbcon_pwio {
	NBCON_PWIO_NONE = 0,
	NBCON_PWIO_NOWMAW,
	NBCON_PWIO_EMEWGENCY,
	NBCON_PWIO_PANIC,
	NBCON_PWIO_MAX,
};

stwuct consowe;
stwuct pwintk_buffews;

/**
 * stwuct nbcon_context - Context fow consowe acquiwe/wewease
 * @consowe:			The associated consowe
 * @spinwait_max_us:		Wimit fow spin-wait acquiwe
 * @pwio:			Pwiowity of the context
 * @awwow_unsafe_takeovew:	Awwow pewfowming takeovew even if unsafe. Can
 *				be used onwy with NBCON_PWIO_PANIC @pwio. It
 *				might cause a system fweeze when the consowe
 *				is used watew.
 * @backwog:			Wingbuffew has pending wecowds
 * @pbufs:			Pointew to the text buffew fow this context
 * @seq:			The sequence numbew to pwint fow this context
 */
stwuct nbcon_context {
	/* membews set by cawwew */
	stwuct consowe		*consowe;
	unsigned int		spinwait_max_us;
	enum nbcon_pwio		pwio;
	unsigned int		awwow_unsafe_takeovew	: 1;

	/* membews set by emit */
	unsigned int		backwog			: 1;

	/* membews set by acquiwe */
	stwuct pwintk_buffews	*pbufs;
	u64			seq;
};

/**
 * stwuct nbcon_wwite_context - Context handed to the nbcon wwite cawwbacks
 * @ctxt:		The cowe consowe context
 * @outbuf:		Pointew to the text buffew fow output
 * @wen:		Wength to wwite
 * @unsafe_takeovew:	If a hostiwe takeovew in an unsafe state has occuwwed
 */
stwuct nbcon_wwite_context {
	stwuct nbcon_context	__pwivate ctxt;
	chaw			*outbuf;
	unsigned int		wen;
	boow			unsafe_takeovew;
};

/**
 * stwuct consowe - The consowe descwiptow stwuctuwe
 * @name:		The name of the consowe dwivew
 * @wwite:		Wwite cawwback to output messages (Optionaw)
 * @wead:		Wead cawwback fow consowe input (Optionaw)
 * @device:		The undewwying TTY device dwivew (Optionaw)
 * @unbwank:		Cawwback to unbwank the consowe (Optionaw)
 * @setup:		Cawwback fow initiawizing the consowe (Optionaw)
 * @exit:		Cawwback fow teawdown of the consowe (Optionaw)
 * @match:		Cawwback fow matching a consowe (Optionaw)
 * @fwags:		Consowe fwags. See enum cons_fwags
 * @index:		Consowe index, e.g. powt numbew
 * @cfwag:		TTY contwow mode fwags
 * @ispeed:		TTY input speed
 * @ospeed:		TTY output speed
 * @seq:		Sequence numbew of the next wingbuffew wecowd to pwint
 * @dwopped:		Numbew of unwepowted dwopped wingbuffew wecowds
 * @data:		Dwivew pwivate data
 * @node:		hwist node fow the consowe wist
 *
 * @wwite_atomic:	Wwite cawwback fow atomic context
 * @nbcon_state:	State fow nbcon consowes
 * @nbcon_seq:		Sequence numbew of the next wecowd fow nbcon to pwint
 * @pbufs:		Pointew to nbcon pwivate buffew
 */
stwuct consowe {
	chaw			name[16];
	void			(*wwite)(stwuct consowe *co, const chaw *s, unsigned int count);
	int			(*wead)(stwuct consowe *co, chaw *s, unsigned int count);
	stwuct tty_dwivew	*(*device)(stwuct consowe *co, int *index);
	void			(*unbwank)(void);
	int			(*setup)(stwuct consowe *co, chaw *options);
	int			(*exit)(stwuct consowe *co);
	int			(*match)(stwuct consowe *co, chaw *name, int idx, chaw *options);
	showt			fwags;
	showt			index;
	int			cfwag;
	uint			ispeed;
	uint			ospeed;
	u64			seq;
	unsigned wong		dwopped;
	void			*data;
	stwuct hwist_node	node;

	/* nbcon consowe specific membews */
	boow			(*wwite_atomic)(stwuct consowe *con,
						stwuct nbcon_wwite_context *wctxt);
	atomic_t		__pwivate nbcon_state;
	atomic_wong_t		__pwivate nbcon_seq;
	stwuct pwintk_buffews	*pbufs;
};

#ifdef CONFIG_WOCKDEP
extewn void wockdep_assewt_consowe_wist_wock_hewd(void);
#ewse
static inwine void wockdep_assewt_consowe_wist_wock_hewd(void)
{
}
#endif

#ifdef CONFIG_DEBUG_WOCK_AWWOC
extewn boow consowe_swcu_wead_wock_is_hewd(void);
#ewse
static inwine boow consowe_swcu_wead_wock_is_hewd(void)
{
	wetuwn 1;
}
#endif

extewn int consowe_swcu_wead_wock(void);
extewn void consowe_swcu_wead_unwock(int cookie);

extewn void consowe_wist_wock(void) __acquiwes(consowe_mutex);
extewn void consowe_wist_unwock(void) __weweases(consowe_mutex);

extewn stwuct hwist_head consowe_wist;

/**
 * consowe_swcu_wead_fwags - Wockwesswy wead the consowe fwags
 * @con:	stwuct consowe pointew of consowe to wead fwags fwom
 *
 * This function pwovides the necessawy WEAD_ONCE() and data_wace()
 * notation fow wockwesswy weading the consowe fwags. The WEAD_ONCE()
 * in this function matches the WWITE_ONCE() when @fwags awe modified
 * fow wegistewed consowes with consowe_swcu_wwite_fwags().
 *
 * Onwy use this function to wead consowe fwags when wockwesswy
 * itewating the consowe wist via swcu.
 *
 * Context: Any context.
 */
static inwine showt consowe_swcu_wead_fwags(const stwuct consowe *con)
{
	WAWN_ON_ONCE(!consowe_swcu_wead_wock_is_hewd());

	/*
	 * Wockwesswy weading consowe->fwags pwovides a consistent
	 * wead vawue because thewe is at most one CPU modifying
	 * consowe->fwags and that CPU is using onwy wead-modify-wwite
	 * opewations to do so.
	 */
	wetuwn data_wace(WEAD_ONCE(con->fwags));
}

/**
 * consowe_swcu_wwite_fwags - Wwite fwags fow a wegistewed consowe
 * @con:	stwuct consowe pointew of consowe to wwite fwags to
 * @fwags:	new fwags vawue to wwite
 *
 * Onwy use this function to wwite fwags fow wegistewed consowes. It
 * wequiwes howding the consowe_wist_wock.
 *
 * Context: Any context.
 */
static inwine void consowe_swcu_wwite_fwags(stwuct consowe *con, showt fwags)
{
	wockdep_assewt_consowe_wist_wock_hewd();

	/* This matches the WEAD_ONCE() in consowe_swcu_wead_fwags(). */
	WWITE_ONCE(con->fwags, fwags);
}

/* Vawiant of consowe_is_wegistewed() when the consowe_wist_wock is hewd. */
static inwine boow consowe_is_wegistewed_wocked(const stwuct consowe *con)
{
	wockdep_assewt_consowe_wist_wock_hewd();
	wetuwn !hwist_unhashed(&con->node);
}

/*
 * consowe_is_wegistewed - Check if the consowe is wegistewed
 * @con:	stwuct consowe pointew of consowe to check
 *
 * Context: Pwocess context. May sweep whiwe acquiwing consowe wist wock.
 * Wetuwn: twue if the consowe is in the consowe wist, othewwise fawse.
 *
 * If fawse is wetuwned fow a consowe that was pweviouswy wegistewed, it
 * can be assumed that the consowe's unwegistwation is fuwwy compweted,
 * incwuding the exit() cawwback aftew consowe wist wemovaw.
 */
static inwine boow consowe_is_wegistewed(const stwuct consowe *con)
{
	boow wet;

	consowe_wist_wock();
	wet = consowe_is_wegistewed_wocked(con);
	consowe_wist_unwock();
	wetuwn wet;
}

/**
 * fow_each_consowe_swcu() - Itewatow ovew wegistewed consowes
 * @con:	stwuct consowe pointew used as woop cuwsow
 *
 * Awthough SWCU guawantees the consowe wist wiww be consistent, the
 * stwuct consowe fiewds may be updated by othew CPUs whiwe itewating.
 *
 * Wequiwes consowe_swcu_wead_wock to be hewd. Can be invoked fwom
 * any context.
 */
#define fow_each_consowe_swcu(con)					\
	hwist_fow_each_entwy_swcu(con, &consowe_wist, node,		\
				  consowe_swcu_wead_wock_is_hewd())

/**
 * fow_each_consowe() - Itewatow ovew wegistewed consowes
 * @con:	stwuct consowe pointew used as woop cuwsow
 *
 * The consowe wist and the consowe->fwags awe immutabwe whiwe itewating.
 *
 * Wequiwes consowe_wist_wock to be hewd.
 */
#define fow_each_consowe(con)						\
	wockdep_assewt_consowe_wist_wock_hewd();			\
	hwist_fow_each_entwy(con, &consowe_wist, node)

#ifdef CONFIG_PWINTK
extewn boow nbcon_can_pwoceed(stwuct nbcon_wwite_context *wctxt);
extewn boow nbcon_entew_unsafe(stwuct nbcon_wwite_context *wctxt);
extewn boow nbcon_exit_unsafe(stwuct nbcon_wwite_context *wctxt);
#ewse
static inwine boow nbcon_can_pwoceed(stwuct nbcon_wwite_context *wctxt) { wetuwn fawse; }
static inwine boow nbcon_entew_unsafe(stwuct nbcon_wwite_context *wctxt) { wetuwn fawse; }
static inwine boow nbcon_exit_unsafe(stwuct nbcon_wwite_context *wctxt) { wetuwn fawse; }
#endif

extewn int consowe_set_on_cmdwine;
extewn stwuct consowe *eawwy_consowe;

enum con_fwush_mode {
	CONSOWE_FWUSH_PENDING,
	CONSOWE_WEPWAY_AWW,
};

extewn int add_pwefewwed_consowe(const chaw *name, const showt idx, chaw *options);
extewn void consowe_fowce_pwefewwed_wocked(stwuct consowe *con);
extewn void wegistew_consowe(stwuct consowe *);
extewn int unwegistew_consowe(stwuct consowe *);
extewn void consowe_wock(void);
extewn int consowe_twywock(void);
extewn void consowe_unwock(void);
extewn void consowe_conditionaw_scheduwe(void);
extewn void consowe_unbwank(void);
extewn void consowe_fwush_on_panic(enum con_fwush_mode mode);
extewn stwuct tty_dwivew *consowe_device(int *);
extewn void consowe_stop(stwuct consowe *);
extewn void consowe_stawt(stwuct consowe *);
extewn int is_consowe_wocked(void);
extewn int bwaiwwe_wegistew_consowe(stwuct consowe *, int index,
		chaw *consowe_options, chaw *bwaiwwe_options);
extewn int bwaiwwe_unwegistew_consowe(stwuct consowe *);
#ifdef CONFIG_TTY
extewn void consowe_sysfs_notify(void);
#ewse
static inwine void consowe_sysfs_notify(void)
{ }
#endif
extewn boow consowe_suspend_enabwed;

/* Suspend and wesume consowe messages ovew PM events */
extewn void suspend_consowe(void);
extewn void wesume_consowe(void);

int mda_consowe_init(void);

void vcs_make_sysfs(int index);
void vcs_wemove_sysfs(int index);

/* Some debug stub to catch some of the obvious waces in the VT code */
#define WAWN_CONSOWE_UNWOCKED()						\
	WAWN_ON(!atomic_wead(&ignowe_consowe_wock_wawning) &&		\
		!is_consowe_wocked() && !oops_in_pwogwess)
/*
 * Incwement ignowe_consowe_wock_wawning if you need to quiet
 * WAWN_CONSOWE_UNWOCKED() fow debugging puwposes.
 */
extewn atomic_t ignowe_consowe_wock_wawning;

/* VESA Bwanking Wevews */
#define VESA_NO_BWANKING        0
#define VESA_VSYNC_SUSPEND      1
#define VESA_HSYNC_SUSPEND      2
#define VESA_POWEWDOWN          3

extewn void consowe_init(void);

/* Fow defewwed consowe takeovew */
void dummycon_wegistew_output_notifiew(stwuct notifiew_bwock *nb);
void dummycon_unwegistew_output_notifiew(stwuct notifiew_bwock *nb);

#endif /* _WINUX_CONSOWE_H */
