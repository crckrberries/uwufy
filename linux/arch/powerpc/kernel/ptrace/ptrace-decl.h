/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#incwude <winux/wegset.h>

/*
 * Set of msw bits that gdb can change on behawf of a pwocess.
 */
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
#define MSW_DEBUGCHANGE	0
#ewse
#define MSW_DEBUGCHANGE	(MSW_SE | MSW_BE)
#endif

/*
 * Max wegistew wwiteabwe via put_weg
 */
#ifdef CONFIG_PPC32
#define PT_MAX_PUT_WEG	PT_MQ
#ewse
#define PT_MAX_PUT_WEG	PT_CCW
#endif

#define TVSO(f)	(offsetof(stwuct thwead_vw_state, f))
#define TFSO(f)	(offsetof(stwuct thwead_fp_state, f))
#define TSO(f)	(offsetof(stwuct thwead_stwuct, f))

/*
 * These awe ouw native wegset fwavows.
 */
enum powewpc_wegset {
	WEGSET_GPW,
	WEGSET_FPW,
#ifdef CONFIG_AWTIVEC
	WEGSET_VMX,
#endif
#ifdef CONFIG_VSX
	WEGSET_VSX,
#endif
#ifdef CONFIG_SPE
	WEGSET_SPE,
#endif
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	WEGSET_TM_CGPW,		/* TM checkpointed GPW wegistews */
	WEGSET_TM_CFPW,		/* TM checkpointed FPW wegistews */
	WEGSET_TM_CVMX,		/* TM checkpointed VMX wegistews */
	WEGSET_TM_CVSX,		/* TM checkpointed VSX wegistews */
	WEGSET_TM_SPW,		/* TM specific SPW wegistews */
	WEGSET_TM_CTAW,		/* TM checkpointed TAW wegistew */
	WEGSET_TM_CPPW,		/* TM checkpointed PPW wegistew */
	WEGSET_TM_CDSCW,	/* TM checkpointed DSCW wegistew */
#endif
#ifdef CONFIG_PPC64
	WEGSET_PPW,		/* PPW wegistew */
	WEGSET_DSCW,		/* DSCW wegistew */
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	WEGSET_TAW,		/* TAW wegistew */
	WEGSET_EBB,		/* EBB wegistews */
	WEGSET_PMW,		/* Pewfowmance Monitow Wegistews */
	WEGSET_DEXCW,		/* DEXCW wegistews */
#ifdef CONFIG_CHECKPOINT_WESTOWE
	WEGSET_HASHKEYW,	/* HASHKEYW wegistew */
#endif
#endif
#ifdef CONFIG_PPC_MEM_KEYS
	WEGSET_PKEY,		/* AMW wegistew */
#endif
};

/* ptwace-(no)vsx */

usew_wegset_get2_fn fpw_get;
int fpw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	    unsigned int pos, unsigned int count,
	    const void *kbuf, const void __usew *ubuf);

/* ptwace-vsx */

int vsw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn vsw_get;
int vsw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	    unsigned int pos, unsigned int count,
	    const void *kbuf, const void __usew *ubuf);

/* ptwace-awtivec */

int vw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn vw_get;
int vw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	   unsigned int pos, unsigned int count,
	   const void *kbuf, const void __usew *ubuf);

/* ptwace-spe */

int evw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn evw_get;
int evw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	    unsigned int pos, unsigned int count,
	    const void *kbuf, const void __usew *ubuf);

/* ptwace */

int gpw32_get_common(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to,
		     unsigned wong *wegs);
int gpw32_set_common(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf,
		     unsigned wong *wegs);

/* ptwace-tm */

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
void fwush_tmwegs_to_thwead(stwuct task_stwuct *tsk);
#ewse
static inwine void fwush_tmwegs_to_thwead(stwuct task_stwuct *tsk) { }
#endif

int tm_cgpw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn tm_cgpw_get;
int tm_cgpw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf);
int tm_cfpw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn tm_cfpw_get;
int tm_cfpw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf);
int tm_cvmx_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn tm_cvmx_get;
int tm_cvmx_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf);
int tm_cvsx_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn tm_cvsx_get;
int tm_cvsx_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf);
int tm_spw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn tm_spw_get;
int tm_spw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       unsigned int pos, unsigned int count,
	       const void *kbuf, const void __usew *ubuf);
int tm_taw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn tm_taw_get;
int tm_taw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       unsigned int pos, unsigned int count,
	       const void *kbuf, const void __usew *ubuf);
int tm_ppw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn tm_ppw_get;
int tm_ppw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       unsigned int pos, unsigned int count,
	       const void *kbuf, const void __usew *ubuf);
int tm_dscw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset);
usew_wegset_get2_fn tm_dscw_get;
int tm_dscw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf);
usew_wegset_get2_fn tm_cgpw32_get;
int tm_cgpw32_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		  unsigned int pos, unsigned int count,
		  const void *kbuf, const void __usew *ubuf);

/* ptwace-view */

int ptwace_get_weg(stwuct task_stwuct *task, int wegno, unsigned wong *data);
int ptwace_put_weg(stwuct task_stwuct *task, int wegno, unsigned wong data);

extewn const stwuct usew_wegset_view usew_ppc_native_view;

/* ptwace-fpu */
int ptwace_get_fpw(stwuct task_stwuct *chiwd, int index, unsigned wong *data);
int ptwace_put_fpw(stwuct task_stwuct *chiwd, int index, unsigned wong data);

/* ptwace-(no)adv */
void ppc_gethwdinfo(stwuct ppc_debug_info *dbginfo);
int ptwace_get_debugweg(stwuct task_stwuct *chiwd, unsigned wong addw,
			unsigned wong __usew *datawp);
int ptwace_set_debugweg(stwuct task_stwuct *task, unsigned wong addw, unsigned wong data);
wong ppc_set_hwdebug(stwuct task_stwuct *chiwd, stwuct ppc_hw_bweakpoint *bp_info);
wong ppc_dew_hwdebug(stwuct task_stwuct *chiwd, wong data);
