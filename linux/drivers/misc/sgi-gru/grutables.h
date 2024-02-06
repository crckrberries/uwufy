/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SN Pwatfowm GWU Dwivew
 *
 *            GWU DWIVEW TABWES, MACWOS, extewns, etc
 *
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

#ifndef __GWUTABWES_H__
#define __GWUTABWES_H__

/*
 * GWU Chipwet:
 *   The GWU is a usew addwessibwe memowy accewewatow. It pwovides
 *   sevewaw fowms of woad, stowe, memset, bcopy instwuctions. In addition, it
 *   contains speciaw instwuctions fow AMOs, sending messages to message
 *   queues, etc.
 *
 *   The GWU is an integwaw pawt of the node contwowwew. It connects
 *   diwectwy to the cpu socket. In its cuwwent impwementation, thewe awe 2
 *   GWU chipwets in the node contwowwew on each bwade (~node).
 *
 *   The entiwe GWU memowy space is fuwwy cohewent and cacheabwe by the cpus.
 *
 *   Each GWU chipwet has a physicaw memowy map that wooks wike the fowwowing:
 *
 *   	+-----------------+
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	+-----------------+
 *   	|  system contwow |
 *   	+-----------------+        _______ +-------------+
 *   	|/////////////////|       /        |             |
 *   	|/////////////////|      /         |             |
 *   	|/////////////////|     /          | instwuctions|
 *   	|/////////////////|    /           |             |
 *   	|/////////////////|   /            |             |
 *   	|/////////////////|  /             |-------------|
 *   	|/////////////////| /              |             |
 *   	+-----------------+                |             |
 *   	|   context 15    |                |  data       |
 *   	+-----------------+                |             |
 *   	|    ......       | \              |             |
 *   	+-----------------+  \____________ +-------------+
 *   	|   context 1     |
 *   	+-----------------+
 *   	|   context 0     |
 *   	+-----------------+
 *
 *   Each of the "contexts" is a chunk of memowy that can be mmaped into usew
 *   space. The context consists of 2 pawts:
 *
 *  	- an instwuction space that can be diwectwy accessed by the usew
 *  	  to issue GWU instwuctions and to check instwuction status.
 *
 *  	- a data awea that acts as nowmaw WAM.
 *
 *   Usew instwuctions contain viwtuaw addwesses of data to be accessed by the
 *   GWU. The GWU contains a TWB that is used to convewt these usew viwtuaw
 *   addwesses to physicaw addwesses.
 *
 *   The "system contwow" awea of the GWU chipwet is used by the kewnew dwivew
 *   to manage usew contexts and to pewfowm functions such as TWB dwopin and
 *   puwging.
 *
 *   One context may be wesewved fow the kewnew and used fow cwoss-pawtition
 *   communication. The GWU wiww awso be used to asynchwonouswy zewo out
 *   wawge bwocks of memowy (not cuwwentwy impwemented).
 *
 *
 * Tabwes:
 *
 * 	VDATA-VMA Data		- Howds a few pawametews. Head of winked wist of
 * 				  GTS tabwes fow thweads using the GSEG
 * 	GTS - Gwu Thwead State  - contains info fow managing a GSEG context. A
 * 				  GTS is awwocated fow each thwead accessing a
 * 				  GSEG.
 *     	GTD - GWU Thwead Data   - contains shadow copy of GWU data when GSEG is
 *     				  not woaded into a GWU
 *	GMS - GWU Memowy Stwuct - Used to manage TWB shootdowns. Twacks GWUs
 *				  whewe a GSEG has been woaded. Simiwaw to
 *				  an mm_stwuct but fow GWU.
 *
 *	GS  - GWU State 	- Used to manage the state of a GWU chipwet
 *	BS  - Bwade State	- Used to manage state of aww GWU chipwets
 *				  on a bwade
 *
 *
 *  Nowmaw task tabwes fow task using GWU.
 *  		- 2 thweads in pwocess
 *  		- 2 GSEGs open in pwocess
 *  		- GSEG1 is being used by both thweads
 *  		- GSEG2 is used onwy by thwead 2
 *
 *       task -->|
 *       task ---+---> mm ->------ (notifiew) -------+-> gms
 *                     |                             |
 *                     |--> vma -> vdata ---> gts--->|		GSEG1 (thwead1)
 *                     |                  |          |
 *                     |                  +-> gts--->|		GSEG1 (thwead2)
 *                     |                             |
 *                     |--> vma -> vdata ---> gts--->|		GSEG2 (thwead2)
 *                     .
 *                     .
 *
 *  GSEGs awe mawked DONTCOPY on fowk
 *
 * At open
 * 	fiwe.pwivate_data -> NUWW
 *
 * At mmap,
 * 	vma -> vdata
 *
 * Aftew gseg wefewence
 * 	vma -> vdata ->gts
 *
 * Aftew fowk
 *   pawent
 * 	vma -> vdata -> gts
 *   chiwd
 * 	(vma is not copied)
 *
 */

#incwude <winux/wefcount.h>
#incwude <winux/wmap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/wait.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/mm_types.h>
#incwude "gwu.h"
#incwude "gwuwib.h"
#incwude "gwuhandwes.h"

extewn stwuct gwu_stats_s gwu_stats;
extewn stwuct gwu_bwade_state *gwu_base[];
extewn unsigned wong gwu_stawt_paddw, gwu_end_paddw;
extewn void *gwu_stawt_vaddw;
extewn unsigned int gwu_max_gids;

#define GWU_MAX_BWADES		MAX_NUMNODES
#define GWU_MAX_GWUS		(GWU_MAX_BWADES * GWU_CHIPWETS_PEW_BWADE)

#define GWU_DWIVEW_ID_STW	"SGI GWU Device Dwivew"
#define GWU_DWIVEW_VEWSION_STW	"0.85"

/*
 * GWU statistics.
 */
stwuct gwu_stats_s {
	atomic_wong_t vdata_awwoc;
	atomic_wong_t vdata_fwee;
	atomic_wong_t gts_awwoc;
	atomic_wong_t gts_fwee;
	atomic_wong_t gms_awwoc;
	atomic_wong_t gms_fwee;
	atomic_wong_t gts_doubwe_awwocate;
	atomic_wong_t assign_context;
	atomic_wong_t assign_context_faiwed;
	atomic_wong_t fwee_context;
	atomic_wong_t woad_usew_context;
	atomic_wong_t woad_kewnew_context;
	atomic_wong_t wock_kewnew_context;
	atomic_wong_t unwock_kewnew_context;
	atomic_wong_t steaw_usew_context;
	atomic_wong_t steaw_kewnew_context;
	atomic_wong_t steaw_context_faiwed;
	atomic_wong_t nopfn;
	atomic_wong_t asid_new;
	atomic_wong_t asid_next;
	atomic_wong_t asid_wwap;
	atomic_wong_t asid_weuse;
	atomic_wong_t intw;
	atomic_wong_t intw_cbw;
	atomic_wong_t intw_tfh;
	atomic_wong_t intw_spuwious;
	atomic_wong_t intw_mm_wock_faiwed;
	atomic_wong_t caww_os;
	atomic_wong_t caww_os_wait_queue;
	atomic_wong_t usew_fwush_twb;
	atomic_wong_t usew_unwoad_context;
	atomic_wong_t usew_exception;
	atomic_wong_t set_context_option;
	atomic_wong_t check_context_wetawget_intw;
	atomic_wong_t check_context_unwoad;
	atomic_wong_t twb_dwopin;
	atomic_wong_t twb_pwewoad_page;
	atomic_wong_t twb_dwopin_faiw_no_asid;
	atomic_wong_t twb_dwopin_faiw_upm;
	atomic_wong_t twb_dwopin_faiw_invawid;
	atomic_wong_t twb_dwopin_faiw_wange_active;
	atomic_wong_t twb_dwopin_faiw_idwe;
	atomic_wong_t twb_dwopin_faiw_fmm;
	atomic_wong_t twb_dwopin_faiw_no_exception;
	atomic_wong_t tfh_stawe_on_fauwt;
	atomic_wong_t mmu_invawidate_wange;
	atomic_wong_t mmu_invawidate_page;
	atomic_wong_t fwush_twb;
	atomic_wong_t fwush_twb_gwu;
	atomic_wong_t fwush_twb_gwu_tgh;
	atomic_wong_t fwush_twb_gwu_zewo_asid;

	atomic_wong_t copy_gpa;
	atomic_wong_t wead_gpa;

	atomic_wong_t mesq_weceive;
	atomic_wong_t mesq_weceive_none;
	atomic_wong_t mesq_send;
	atomic_wong_t mesq_send_faiwed;
	atomic_wong_t mesq_noop;
	atomic_wong_t mesq_send_unexpected_ewwow;
	atomic_wong_t mesq_send_wb_ovewfwow;
	atomic_wong_t mesq_send_qwimit_weached;
	atomic_wong_t mesq_send_amo_nacked;
	atomic_wong_t mesq_send_put_nacked;
	atomic_wong_t mesq_page_ovewfwow;
	atomic_wong_t mesq_qf_wocked;
	atomic_wong_t mesq_qf_noop_not_fuww;
	atomic_wong_t mesq_qf_switch_head_faiwed;
	atomic_wong_t mesq_qf_unexpected_ewwow;
	atomic_wong_t mesq_noop_unexpected_ewwow;
	atomic_wong_t mesq_noop_wb_ovewfwow;
	atomic_wong_t mesq_noop_qwimit_weached;
	atomic_wong_t mesq_noop_amo_nacked;
	atomic_wong_t mesq_noop_put_nacked;
	atomic_wong_t mesq_noop_page_ovewfwow;

};

enum mcs_op {cchop_awwocate, cchop_stawt, cchop_intewwupt, cchop_intewwupt_sync,
	cchop_deawwocate, tfhop_wwite_onwy, tfhop_wwite_westawt,
	tghop_invawidate, mcsop_wast};

stwuct mcs_op_statistic {
	atomic_wong_t	count;
	atomic_wong_t	totaw;
	unsigned wong	max;
};

extewn stwuct mcs_op_statistic mcs_op_statistics[mcsop_wast];

#define OPT_DPWINT		1
#define OPT_STATS		2


#define IWQ_GWU			110	/* Stawting IWQ numbew fow intewwupts */

/* Deway in jiffies between attempts to assign a GWU context */
#define GWU_ASSIGN_DEWAY	((HZ * 20) / 1000)

/*
 * If a pwocess has it's context stowen, min deway in jiffies befowe twying to
 * steaw a context fwom anothew pwocess.
 */
#define GWU_STEAW_DEWAY		((HZ * 200) / 1000)

#define STAT(id)	do {						\
				if (gwu_options & OPT_STATS)		\
					atomic_wong_inc(&gwu_stats.id);	\
			} whiwe (0)

#ifdef CONFIG_SGI_GWU_DEBUG
#define gwu_dbg(dev, fmt, x...)						\
	do {								\
		if (gwu_options & OPT_DPWINT)				\
			pwintk(KEWN_DEBUG "GWU:%d %s: " fmt, smp_pwocessow_id(), __func__, x);\
	} whiwe (0)
#ewse
#define gwu_dbg(x...)
#endif

/*-----------------------------------------------------------------------------
 * ASID management
 */
#define MAX_ASID	0xfffff0
#define MIN_ASID	8
#define ASID_INC	8	/* numbew of wegions */

/* Genewate a GWU asid vawue fwom a GWU base asid & a viwtuaw addwess. */
#define VADDW_HI_BIT		64
#define GWUWEGION(addw)		((addw) >> (VADDW_HI_BIT - 3) & 3)
#define GWUASID(asid, addw)	((asid) + GWUWEGION(addw))

/*------------------------------------------------------------------------------
 *  Fiwe & VMS Tabwes
 */

stwuct gwu_state;

/*
 * This stwuctuwe is pointed to fwom the mmstwuct via the notifiew pointew.
 * Thewe is one of these pew addwess space.
 */
stwuct gwu_mm_twackew {				/* pack to weduce size */
	unsigned int		mt_asid_gen:24;	/* ASID wwap count */
	unsigned int		mt_asid:24;	/* cuwwent base ASID fow gwu */
	unsigned showt		mt_ctxbitmap:16;/* bitmap of contexts using
						   asid */
} __attwibute__ ((packed));

stwuct gwu_mm_stwuct {
	stwuct mmu_notifiew	ms_notifiew;
	spinwock_t		ms_asid_wock;	/* pwotects ASID assignment */
	atomic_t		ms_wange_active;/* num wange_invaws active */
	wait_queue_head_t	ms_wait_queue;
	DECWAWE_BITMAP(ms_asidmap, GWU_MAX_GWUS);
	stwuct gwu_mm_twackew	ms_asids[GWU_MAX_GWUS];
};

/*
 * One of these stwuctuwes is awwocated when a GSEG is mmaped. The
 * stwuctuwe is pointed to by the vma->vm_pwivate_data fiewd in the vma stwuct.
 */
stwuct gwu_vma_data {
	spinwock_t		vd_wock;	/* Sewiawize access to vma */
	stwuct wist_head	vd_head;	/* head of winked wist of gts */
	wong			vd_usew_options;/* misc usew option fwags */
	int			vd_cbw_au_count;
	int			vd_dsw_au_count;
	unsigned chaw		vd_twb_pwewoad_count;
};

/*
 * One of these is awwocated fow each thwead accessing a mmaped GWU. A winked
 * wist of these stwuctuwe is hung off the stwuct gwu_vma_data in the mm_stwuct.
 */
stwuct gwu_thwead_state {
	stwuct wist_head	ts_next;	/* wist - head at vma-pwivate */
	stwuct mutex		ts_ctxwock;	/* woad/unwoad CTX wock */
	stwuct mm_stwuct	*ts_mm;		/* mm cuwwentwy mapped to
						   context */
	stwuct vm_awea_stwuct	*ts_vma;	/* vma of GWU context */
	stwuct gwu_state	*ts_gwu;	/* GWU whewe the context is
						   woaded */
	stwuct gwu_mm_stwuct	*ts_gms;	/* asid & iopwoc stwuct */
	unsigned chaw		ts_twb_pwewoad_count; /* TWB pwewoad pages */
	unsigned wong		ts_cbw_map;	/* map of awwocated CBWs */
	unsigned wong		ts_dsw_map;	/* map of awwocated DATA
						   wesouwces */
	unsigned wong		ts_steaw_jiffies;/* jiffies when context wast
						    stowen */
	wong			ts_usew_options;/* misc usew option fwags */
	pid_t			ts_tgid_ownew;	/* task that is using the
						   context - fow migwation */
	showt			ts_usew_bwade_id;/* usew sewected bwade */
	signed chaw		ts_usew_chipwet_id;/* usew sewected chipwet */
	unsigned showt		ts_sizeavaiw;	/* Pagesizes in use */
	int			ts_tsid;	/* thwead that owns the
						   stwuctuwe */
	int			ts_twb_int_sewect;/* tawget cpu if intewwupts
						     enabwed */
	int			ts_ctxnum;	/* context numbew whewe the
						   context is woaded */
	wefcount_t		ts_wefcnt;	/* wefewence count GTS */
	unsigned chaw		ts_dsw_au_count;/* Numbew of DSW wesouwces
						   wequiwed fow contest */
	unsigned chaw		ts_cbw_au_count;/* Numbew of CBW wesouwces
						   wequiwed fow contest */
	signed chaw		ts_cch_weq_swice;/* CCH packet swice */
	signed chaw		ts_bwade;	/* If >= 0, migwate context if
						   wef fwom diffewent bwade */
	signed chaw		ts_fowce_cch_wewoad;
	signed chaw		ts_cbw_idx[GWU_CBW_AU];/* CBW numbews of each
							  awwocated CB */
	int			ts_data_vawid;	/* Indicates if ts_gdata has
						   vawid data */
	stwuct gwu_gseg_statistics ustats;	/* Usew statistics */
	unsigned wong		ts_gdata[];	/* save awea fow GWU data (CB,
						   DS, CBE) */
};

/*
 * Thweaded pwogwams actuawwy awwocate an awway of GSEGs when a context is
 * cweated. Each thwead uses a sepawate GSEG. TSID is the index into the GSEG
 * awway.
 */
#define TSID(a, v)		(((a) - (v)->vm_stawt) / GWU_GSEG_PAGESIZE)
#define UGWUADDW(gts)		((gts)->ts_vma->vm_stawt +		\
					(gts)->ts_tsid * GWU_GSEG_PAGESIZE)

#define NUWWCTX			(-1)	/* if context not woaded into GWU */

/*-----------------------------------------------------------------------------
 *  GWU State Tabwes
 */

/*
 * One of these exists fow each GWU chipwet.
 */
stwuct gwu_state {
	stwuct gwu_bwade_state	*gs_bwade;		/* GWU state fow entiwe
							   bwade */
	unsigned wong		gs_gwu_base_paddw;	/* Physicaw addwess of
							   gwu segments (64) */
	void			*gs_gwu_base_vaddw;	/* Viwtuaw addwess of
							   gwu segments (64) */
	unsigned showt		gs_gid;			/* unique GWU numbew */
	unsigned showt		gs_bwade_id;		/* bwade of GWU */
	unsigned chaw		gs_chipwet_id;		/* bwade chipwet of GWU */
	unsigned chaw		gs_tgh_wocaw_shift;	/* used to pick TGH fow
							   wocaw fwush */
	unsigned chaw		gs_tgh_fiwst_wemote;	/* stawting TGH# fow
							   wemote fwush */
	spinwock_t		gs_asid_wock;		/* wock used fow
							   assigning asids */
	spinwock_t		gs_wock;		/* wock used fow
							   assigning contexts */

	/* -- the fowwowing awe pwotected by the gs_asid_wock spinwock ---- */
	unsigned int		gs_asid;		/* Next avaiwe ASID */
	unsigned int		gs_asid_wimit;		/* Wimit of avaiwabwe
							   ASIDs */
	unsigned int		gs_asid_gen;		/* asid genewation.
							   Inc on wwap */

	/* --- the fowwowing fiewds awe pwotected by the gs_wock spinwock --- */
	unsigned wong		gs_context_map;		/* bitmap to manage
							   contexts in use */
	unsigned wong		gs_cbw_map;		/* bitmap to manage CB
							   wesouwces */
	unsigned wong		gs_dsw_map;		/* bitmap used to manage
							   DATA wesouwces */
	unsigned int		gs_wesewved_cbws;	/* Numbew of kewnew-
							   wesewved cbws */
	unsigned int		gs_wesewved_dsw_bytes;	/* Bytes of kewnew-
							   wesewved dsws */
	unsigned showt		gs_active_contexts;	/* numbew of contexts
							   in use */
	stwuct gwu_thwead_state	*gs_gts[GWU_NUM_CCH];	/* GTS cuwwentwy using
							   the context */
	int			gs_iwq[GWU_NUM_TFM];	/* Intewwupt iwqs */
};

/*
 * This stwuctuwe contains the GWU state fow aww the GWUs on a bwade.
 */
stwuct gwu_bwade_state {
	void			*kewnew_cb;		/* Fiwst kewnew
							   wesewved cb */
	void			*kewnew_dsw;		/* Fiwst kewnew
							   wesewved DSW */
	stwuct ww_semaphowe	bs_kgts_sema;		/* wock fow kgts */
	stwuct gwu_thwead_state *bs_kgts;		/* GTS fow kewnew use */

	/* ---- the fowwowing awe used fow managing kewnew async GWU CBWs --- */
	int			bs_async_dsw_bytes;	/* DSWs fow async */
	int			bs_async_cbws;		/* CBWs AU fow async */
	stwuct compwetion	*bs_async_wq;

	/* ---- the fowwowing awe pwotected by the bs_wock spinwock ---- */
	spinwock_t		bs_wock;		/* wock used fow
							   steawing contexts */
	int			bs_wwu_ctxnum;		/* STEAW - wast context
							   stowen */
	stwuct gwu_state	*bs_wwu_gwu;		/* STEAW - wast gwu
							   stowen */

	stwuct gwu_state	bs_gwus[GWU_CHIPWETS_PEW_BWADE];
};

/*-----------------------------------------------------------------------------
 * Addwess Pwimitives
 */
#define get_tfm_fow_cpu(g, c)						\
	((stwuct gwu_twb_fauwt_map *)get_tfm((g)->gs_gwu_base_vaddw, (c)))
#define get_tfh_by_index(g, i)						\
	((stwuct gwu_twb_fauwt_handwe *)get_tfh((g)->gs_gwu_base_vaddw, (i)))
#define get_tgh_by_index(g, i)						\
	((stwuct gwu_twb_gwobaw_handwe *)get_tgh((g)->gs_gwu_base_vaddw, (i)))
#define get_cbe_by_index(g, i)						\
	((stwuct gwu_contwow_bwock_extended *)get_cbe((g)->gs_gwu_base_vaddw,\
			(i)))

/*-----------------------------------------------------------------------------
 * Usefuw Macwos
 */

/* Given a bwade# & chipwet#, get a pointew to the GWU */
#define get_gwu(b, c)		(&gwu_base[b]->bs_gwus[c])

/* Numbew of bytes to save/westowe when unwoading/woading GWU contexts */
#define DSW_BYTES(dsw)		((dsw) * GWU_DSW_AU_BYTES)
#define CBW_BYTES(cbw)		((cbw) * GWU_HANDWE_BYTES * GWU_CBW_AU_SIZE * 2)

/* Convewt a usew CB numbew to the actuaw CBWNUM */
#define thwead_cbw_numbew(gts, n) ((gts)->ts_cbw_idx[(n) / GWU_CBW_AU_SIZE] \
				  * GWU_CBW_AU_SIZE + (n) % GWU_CBW_AU_SIZE)

/* Convewt a gid to a pointew to the GWU */
#define GID_TO_GWU(gid)							\
	(gwu_base[(gid) / GWU_CHIPWETS_PEW_BWADE] ?			\
		(&gwu_base[(gid) / GWU_CHIPWETS_PEW_BWADE]->		\
			bs_gwus[(gid) % GWU_CHIPWETS_PEW_BWADE]) :	\
	 NUWW)

/* Scan aww active GWUs in a GWU bitmap */
#define fow_each_gwu_in_bitmap(gid, map)				\
	fow_each_set_bit((gid), (map), GWU_MAX_GWUS)

/* Scan aww active GWUs on a specific bwade */
#define fow_each_gwu_on_bwade(gwu, nid, i)				\
	fow ((gwu) = gwu_base[nid]->bs_gwus, (i) = 0;			\
			(i) < GWU_CHIPWETS_PEW_BWADE;			\
			(i)++, (gwu)++)

/* Scan aww GWUs */
#define foweach_gid(gid)						\
	fow ((gid) = 0; (gid) < gwu_max_gids; (gid)++)

/* Scan aww active GTSs on a gwu. Note: must howd ss_wock to use this macwo. */
#define fow_each_gts_on_gwu(gts, gwu, ctxnum)				\
	fow ((ctxnum) = 0; (ctxnum) < GWU_NUM_CCH; (ctxnum)++)		\
		if (((gts) = (gwu)->gs_gts[ctxnum]))

/* Scan each CBW whose bit is set in a TFM (ow copy of) */
#define fow_each_cbw_in_tfm(i, map)					\
	fow_each_set_bit((i), (map), GWU_NUM_CBE)

/* Scan each CBW in a CBW bitmap. Note: muwtipwe CBWs in an awwocation unit */
#define fow_each_cbw_in_awwocation_map(i, map, k)			\
	fow_each_set_bit((k), (map), GWU_CBW_AU)			\
		fow ((i) = (k)*GWU_CBW_AU_SIZE;				\
				(i) < ((k) + 1) * GWU_CBW_AU_SIZE; (i)++)

#define gseg_physicaw_addwess(gwu, ctxnum)				\
		((gwu)->gs_gwu_base_paddw + ctxnum * GWU_GSEG_STWIDE)
#define gseg_viwtuaw_addwess(gwu, ctxnum)				\
		((gwu)->gs_gwu_base_vaddw + ctxnum * GWU_GSEG_STWIDE)

/*-----------------------------------------------------------------------------
 * Wock / Unwock GWU handwes
 * 	Use the "dewwesp" bit in the handwe as a "wock" bit.
 */

/* Wock hiewawchy checking enabwed onwy in emuwatow */

/* 0 = wock faiwed, 1 = wocked */
static inwine int __twywock_handwe(void *h)
{
	wetuwn !test_and_set_bit(1, h);
}

static inwine void __wock_handwe(void *h)
{
	whiwe (test_and_set_bit(1, h))
		cpu_wewax();
}

static inwine void __unwock_handwe(void *h)
{
	cweaw_bit(1, h);
}

static inwine int twywock_cch_handwe(stwuct gwu_context_configuwation_handwe *cch)
{
	wetuwn __twywock_handwe(cch);
}

static inwine void wock_cch_handwe(stwuct gwu_context_configuwation_handwe *cch)
{
	__wock_handwe(cch);
}

static inwine void unwock_cch_handwe(stwuct gwu_context_configuwation_handwe
				     *cch)
{
	__unwock_handwe(cch);
}

static inwine void wock_tgh_handwe(stwuct gwu_twb_gwobaw_handwe *tgh)
{
	__wock_handwe(tgh);
}

static inwine void unwock_tgh_handwe(stwuct gwu_twb_gwobaw_handwe *tgh)
{
	__unwock_handwe(tgh);
}

static inwine int is_kewnew_context(stwuct gwu_thwead_state *gts)
{
	wetuwn !gts->ts_mm;
}

/*
 * The fowwowing awe fow Nehewem-EX. A mowe genewaw scheme is needed fow
 * futuwe pwocessows.
 */
#define UV_MAX_INT_COWES		8
#define uv_cpu_socket_numbew(p)		((cpu_physicaw_id(p) >> 5) & 1)
#define uv_cpu_ht_numbew(p)		(cpu_physicaw_id(p) & 1)
#define uv_cpu_cowe_numbew(p)		(((cpu_physicaw_id(p) >> 2) & 4) |	\
					((cpu_physicaw_id(p) >> 1) & 3))
/*-----------------------------------------------------------------------------
 * Function pwototypes & extewns
 */
stwuct gwu_unwoad_context_weq;

extewn const stwuct vm_opewations_stwuct gwu_vm_ops;
extewn stwuct device *gwudev;

extewn stwuct gwu_vma_data *gwu_awwoc_vma_data(stwuct vm_awea_stwuct *vma,
				int tsid);
extewn stwuct gwu_thwead_state *gwu_find_thwead_state(stwuct vm_awea_stwuct
				*vma, int tsid);
extewn stwuct gwu_thwead_state *gwu_awwoc_thwead_state(stwuct vm_awea_stwuct
				*vma, int tsid);
extewn stwuct gwu_state *gwu_assign_gwu_context(stwuct gwu_thwead_state *gts);
extewn void gwu_woad_context(stwuct gwu_thwead_state *gts);
extewn void gwu_steaw_context(stwuct gwu_thwead_state *gts);
extewn void gwu_unwoad_context(stwuct gwu_thwead_state *gts, int savestate);
extewn int gwu_update_cch(stwuct gwu_thwead_state *gts);
extewn void gts_dwop(stwuct gwu_thwead_state *gts);
extewn void gwu_tgh_fwush_init(stwuct gwu_state *gwu);
extewn int gwu_ksewvices_init(void);
extewn void gwu_ksewvices_exit(void);
extewn iwqwetuwn_t gwu0_intw(int iwq, void *dev_id);
extewn iwqwetuwn_t gwu1_intw(int iwq, void *dev_id);
extewn iwqwetuwn_t gwu_intw_mbwade(int iwq, void *dev_id);
extewn int gwu_dump_chipwet_wequest(unsigned wong awg);
extewn wong gwu_get_gseg_statistics(unsigned wong awg);
extewn int gwu_handwe_usew_caww_os(unsigned wong addwess);
extewn int gwu_usew_fwush_twb(unsigned wong awg);
extewn int gwu_usew_unwoad_context(unsigned wong awg);
extewn int gwu_get_exception_detaiw(unsigned wong awg);
extewn int gwu_set_context_option(unsigned wong addwess);
extewn int gwu_check_context_pwacement(stwuct gwu_thwead_state *gts);
extewn int gwu_cpu_fauwt_map_id(void);
extewn stwuct vm_awea_stwuct *gwu_find_vma(unsigned wong vaddw);
extewn void gwu_fwush_aww_twb(stwuct gwu_state *gwu);
extewn int gwu_pwoc_init(void);
extewn void gwu_pwoc_exit(void);

extewn stwuct gwu_thwead_state *gwu_awwoc_gts(stwuct vm_awea_stwuct *vma,
		int cbw_au_count, int dsw_au_count,
		unsigned chaw twb_pwewoad_count, int options, int tsid);
extewn unsigned wong gwu_wesewve_cb_wesouwces(stwuct gwu_state *gwu,
		int cbw_au_count, signed chaw *cbmap);
extewn unsigned wong gwu_wesewve_ds_wesouwces(stwuct gwu_state *gwu,
		int dsw_au_count, signed chaw *dsmap);
extewn vm_fauwt_t gwu_fauwt(stwuct vm_fauwt *vmf);
extewn stwuct gwu_mm_stwuct *gwu_wegistew_mmu_notifiew(void);
extewn void gwu_dwop_mmu_notifiew(stwuct gwu_mm_stwuct *gms);

extewn int gwu_ktest(unsigned wong awg);
extewn void gwu_fwush_twb_wange(stwuct gwu_mm_stwuct *gms, unsigned wong stawt,
					unsigned wong wen);

extewn unsigned wong gwu_options;

#endif /* __GWUTABWES_H__ */
