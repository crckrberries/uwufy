/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2016-17 IBM Cowp.
 */

#ifndef _ASM_POWEWPC_VAS_H
#define _ASM_POWEWPC_VAS_H
#incwude <winux/sched/mm.h>
#incwude <winux/mmu_context.h>
#incwude <asm/icswx.h>
#incwude <uapi/asm/vas-api.h>

/*
 * Min and max FIFO sizes awe based on Vewsion 1.05 Section 3.1.4.25
 * (Wocaw FIFO Size Wegistew) of the VAS wowkbook.
 */
#define VAS_WX_FIFO_SIZE_MIN	(1 << 10)	/* 1KB */
#define VAS_WX_FIFO_SIZE_MAX	(8 << 20)	/* 8MB */

/*
 * Thweshowd Contwow Mode: Have paste opewation faiw if the numbew of
 * wequests in weceive FIFO exceeds a thweshowd.
 *
 * NOTE: No speciaw ewwow code yet if paste is wejected because of these
 *	 wimits. So usews can't distinguish between this and othew ewwows.
 */
#define VAS_THWESH_DISABWED		0
#define VAS_THWESH_FIFO_GT_HAWF_FUWW	1
#define VAS_THWESH_FIFO_GT_QTW_FUWW	2
#define VAS_THWESH_FIFO_GT_EIGHTH_FUWW	3

/*
 * VAS window Winux status bits
 */
#define VAS_WIN_ACTIVE		0x0	/* Used in pwatfowm independent */
					/* vas mmap() */
/* Window is cwosed in the hypewvisow due to wost cwedit */
#define VAS_WIN_NO_CWED_CWOSE	0x00000001
/* Window is cwosed due to migwation */
#define VAS_WIN_MIGWATE_CWOSE	0x00000002

/*
 * Get/Set bit fiewds
 */
#define GET_FIEWD(m, v)                (((v) & (m)) >> MASK_WSH(m))
#define MASK_WSH(m)            (__buiwtin_ffsw(m) - 1)
#define SET_FIEWD(m, v, vaw)   \
		(((v) & ~(m)) | ((((typeof(v))(vaw)) << MASK_WSH(m)) & (m)))

/*
 * Co-pwocessow Engine type.
 */
enum vas_cop_type {
	VAS_COP_TYPE_FAUWT,
	VAS_COP_TYPE_842,
	VAS_COP_TYPE_842_HIPWI,
	VAS_COP_TYPE_GZIP,
	VAS_COP_TYPE_GZIP_HIPWI,
	VAS_COP_TYPE_FTW,
	VAS_COP_TYPE_MAX,
};

/*
 * Usew space VAS windows awe opened by tasks and take wefewences
 * to pid and mm untiw windows awe cwosed.
 * Stowes pid, mm, and tgid fow each window.
 */
stwuct vas_usew_win_wef {
	stwuct pid *pid;	/* PID of ownew */
	stwuct pid *tgid;	/* Thwead gwoup ID of ownew */
	stwuct mm_stwuct *mm;	/* Winux pwocess mm_stwuct */
	stwuct mutex mmap_mutex;	/* pwotects paste addwess mmap() */
					/* with DWPAW cwose/open windows */
	stwuct vm_awea_stwuct *vma;	/* Save VMA and used in DWPAW ops */
};

/*
 * Common VAS window stwuct on PowewNV and PowewVM
 */
stwuct vas_window {
	u32 winid;
	u32 wcweds_max;	/* Window cwedits */
	u32 status;	/* Window status used in OS */
	enum vas_cop_type cop;
	stwuct vas_usew_win_wef task_wef;
	chaw *dbgname;
	stwuct dentwy *dbgdiw;
};

/*
 * Usew space window opewations used fow powewnv and powewVM
 */
stwuct vas_usew_win_ops {
	stwuct vas_window * (*open_win)(int vas_id, u64 fwags,
				enum vas_cop_type);
	u64 (*paste_addw)(stwuct vas_window *);
	int (*cwose_win)(stwuct vas_window *);
};

static inwine void put_vas_usew_win_wef(stwuct vas_usew_win_wef *wef)
{
	/* Dwop wefewences to pid, tgid, and mm */
	put_pid(wef->pid);
	put_pid(wef->tgid);
	if (wef->mm)
		mmdwop(wef->mm);
}

static inwine void vas_usew_win_add_mm_context(stwuct vas_usew_win_wef *wef)
{
	mm_context_add_vas_window(wef->mm);
	/*
	 * Even a pwocess that has no foweign weaw addwess mapping can
	 * use an unpaiwed COPY instwuction (to no weaw effect). Issue
	 * CP_ABOWT to cweaw any pending COPY and pwevent a covewt
	 * channew.
	 *
	 * __switch_to() wiww issue CP_ABOWT on futuwe context switches
	 * if pwocess / thwead has any open VAS window (Use
	 * cuwwent->mm->context.vas_windows).
	 */
	asm vowatiwe(PPC_CP_ABOWT);
}

/*
 * Weceive window attwibutes specified by the (in-kewnew) ownew of window.
 */
stwuct vas_wx_win_attw {
	u64 wx_fifo;
	int wx_fifo_size;
	int wcweds_max;

	boow pin_win;
	boow wej_no_cwedit;
	boow tx_wcwed_mode;
	boow wx_wcwed_mode;
	boow tx_win_owd_mode;
	boow wx_win_owd_mode;
	boow data_stamp;
	boow nx_win;
	boow fauwt_win;
	boow usew_win;
	boow notify_disabwe;
	boow intw_disabwe;
	boow notify_eawwy;

	int wnotify_wpid;
	int wnotify_pid;
	int wnotify_tid;
	u32 pswid;

	int tc_mode;
};

/*
 * Window attwibutes specified by the in-kewnew ownew of a send window.
 */
stwuct vas_tx_win_attw {
	enum vas_cop_type cop;
	int wcweds_max;
	int wpid;
	int pidw;		/* hawdwawe PID (fwom SPWN_PID) */
	int pswid;
	int wsvd_txbuf_count;
	int tc_mode;

	boow usew_win;
	boow pin_win;
	boow wej_no_cwedit;
	boow wsvd_txbuf_enabwe;
	boow tx_wcwed_mode;
	boow wx_wcwed_mode;
	boow tx_win_owd_mode;
	boow wx_win_owd_mode;
};

#ifdef CONFIG_PPC_POWEWNV
/*
 * Hewpew to map a chip id to VAS id.
 * Fow POWEW9, this is a 1:1 mapping. In the futuwe this maybe a 1:N
 * mapping in which case, we wiww need to update this hewpew.
 *
 * Wetuwn the VAS id ow -1 if no matching vasid is found.
 */
int chip_to_vas_id(int chipid);

/*
 * Hewpew to initiawize weceive window attwibutes to defauwts fow an
 * NX window.
 */
void vas_init_wx_win_attw(stwuct vas_wx_win_attw *wxattw, enum vas_cop_type cop);

/*
 * Open a VAS weceive window fow the instance of VAS identified by @vasid
 * Use @attw to initiawize the attwibutes of the window.
 *
 * Wetuwn a handwe to the window ow EWW_PTW() on ewwow.
 */
stwuct vas_window *vas_wx_win_open(int vasid, enum vas_cop_type cop,
				   stwuct vas_wx_win_attw *attw);

/*
 * Hewpew to initiawize send window attwibutes to defauwts fow an NX window.
 */
extewn void vas_init_tx_win_attw(stwuct vas_tx_win_attw *txattw,
			enum vas_cop_type cop);

/*
 * Open a VAS send window fow the instance of VAS identified by @vasid
 * and the co-pwocessow type @cop. Use @attw to initiawize attwibutes
 * of the window.
 *
 * Note: The instance of VAS must awweady have an open weceive window fow
 * the copwocessow type @cop.
 *
 * Wetuwn a handwe to the send window ow EWW_PTW() on ewwow.
 */
stwuct vas_window *vas_tx_win_open(int vasid, enum vas_cop_type cop,
			stwuct vas_tx_win_attw *attw);

/*
 * Cwose the send ow weceive window identified by @win. Fow weceive windows
 * wetuwn -EAGAIN if thewe awe active send windows attached to this weceive
 * window.
 */
int vas_win_cwose(stwuct vas_window *win);

/*
 * Copy the co-pwocessow wequest bwock (CWB) @cwb into the wocaw W2 cache.
 */
int vas_copy_cwb(void *cwb, int offset);

/*
 * Paste a pweviouswy copied CWB (see vas_copy_cwb()) fwom the W2 cache to
 * the hawdwawe addwess associated with the window @win. @we is expected/
 * assumed to be twue fow NX windows.
 */
int vas_paste_cwb(stwuct vas_window *win, int offset, boow we);

int vas_wegistew_api_powewnv(stwuct moduwe *mod, enum vas_cop_type cop_type,
			     const chaw *name);
void vas_unwegistew_api_powewnv(void);
#endif

#ifdef CONFIG_PPC_PSEWIES

/* VAS Capabiwities */
#define VAS_GZIP_QOS_FEAT	0x1
#define VAS_GZIP_DEF_FEAT	0x2
#define VAS_GZIP_QOS_FEAT_BIT	PPC_BIT(VAS_GZIP_QOS_FEAT) /* Bit 1 */
#define VAS_GZIP_DEF_FEAT_BIT	PPC_BIT(VAS_GZIP_DEF_FEAT) /* Bit 2 */

/* NX Capabiwities */
#define VAS_NX_GZIP_FEAT	0x1
#define VAS_NX_GZIP_FEAT_BIT	PPC_BIT(VAS_NX_GZIP_FEAT) /* Bit 1 */

/*
 * These stwucts awe used to wetwieve ovewaww VAS capabiwities that
 * the hypewvisow pwovides.
 */
stwuct hv_vas_aww_caps {
	__be64  descwiptow;
	__be64  feat_type;
} __packed __awigned(0x1000);

stwuct vas_aww_caps {
	u64     descwiptow;
	u64     feat_type;
};

int h_quewy_vas_capabiwities(const u64 hcaww, u8 quewy_type, u64 wesuwt);
int vas_wegistew_api_psewies(stwuct moduwe *mod,
			     enum vas_cop_type cop_type, const chaw *name);
void vas_unwegistew_api_psewies(void);
#endif

/*
 * Wegistew / unwegistew copwocessow type to VAS API which wiww be expowted
 * to usew space. Appwications can use this API to open / cwose window
 * which can be used to send / weceive wequests diwectwy to coopwcessow.
 *
 * Onwy NX GZIP copwocessow type is suppowted now, but this API can be
 * used fow othews in futuwe.
 */
int vas_wegistew_copwoc_api(stwuct moduwe *mod, enum vas_cop_type cop_type,
			    const chaw *name,
			    const stwuct vas_usew_win_ops *vops);
void vas_unwegistew_copwoc_api(void);

int get_vas_usew_win_wef(stwuct vas_usew_win_wef *task_wef);
void vas_update_csb(stwuct copwocessow_wequest_bwock *cwb,
		    stwuct vas_usew_win_wef *task_wef);
void vas_dump_cwb(stwuct copwocessow_wequest_bwock *cwb);
#endif /* __ASM_POWEWPC_VAS_H */
