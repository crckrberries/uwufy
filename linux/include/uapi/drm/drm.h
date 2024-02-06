/*
 * Headew fow the Diwect Wendewing Managew
 *
 * Authow: Wickawd E. (Wik) Faith <faith@vawinux.com>
 *
 * Acknowwedgments:
 * Dec 1999, Wichawd Hendewson <wth@twiddwe.net>, move to genewic cmpxchg.
 */

/*
 * Copywight 1999 Pwecision Insight, Inc., Cedaw Pawk, Texas.
 * Copywight 2000 VA Winux Systems, Inc., Sunnyvawe, Cawifownia.
 * Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef _DWM_H_
#define _DWM_H_

#if defined(__KEWNEW__)

#incwude <winux/types.h>
#incwude <asm/ioctw.h>
typedef unsigned int dwm_handwe_t;

#ewif defined(__winux__)

#incwude <winux/types.h>
#incwude <asm/ioctw.h>
typedef unsigned int dwm_handwe_t;

#ewse /* One of the BSDs */

#incwude <stdint.h>
#incwude <sys/ioccom.h>
#incwude <sys/types.h>
typedef int8_t   __s8;
typedef uint8_t  __u8;
typedef int16_t  __s16;
typedef uint16_t __u16;
typedef int32_t  __s32;
typedef uint32_t __u32;
typedef int64_t  __s64;
typedef uint64_t __u64;
typedef size_t   __kewnew_size_t;
typedef unsigned wong dwm_handwe_t;

#endif

#if defined(__cpwuspwus)
extewn "C" {
#endif

#define DWM_NAME	"dwm"	  /**< Name in kewnew, /dev, and /pwoc */
#define DWM_MIN_OWDEW	5	  /**< At weast 2^5 bytes = 32 bytes */
#define DWM_MAX_OWDEW	22	  /**< Up to 2^22 bytes = 4MB */
#define DWM_WAM_PEWCENT 10	  /**< How much system wam can we wock? */

#define _DWM_WOCK_HEWD	0x80000000U /**< Hawdwawe wock is hewd */
#define _DWM_WOCK_CONT	0x40000000U /**< Hawdwawe wock is contended */
#define _DWM_WOCK_IS_HEWD(wock)	   ((wock) & _DWM_WOCK_HEWD)
#define _DWM_WOCK_IS_CONT(wock)	   ((wock) & _DWM_WOCK_CONT)
#define _DWM_WOCKING_CONTEXT(wock) ((wock) & ~(_DWM_WOCK_HEWD|_DWM_WOCK_CONT))

typedef unsigned int dwm_context_t;
typedef unsigned int dwm_dwawabwe_t;
typedef unsigned int dwm_magic_t;

/*
 * Cwipwect.
 *
 * \wawning: If you change this stwuctuwe, make suwe you change
 * XF86DWICwipWectWec in the sewvew as weww
 *
 * \note KW: Actuawwy it's iwwegaw to change eithew fow
 * backwawds-compatibiwity weasons.
 */
stwuct dwm_cwip_wect {
	unsigned showt x1;
	unsigned showt y1;
	unsigned showt x2;
	unsigned showt y2;
};

/*
 * Dwawabwe infowmation.
 */
stwuct dwm_dwawabwe_info {
	unsigned int num_wects;
	stwuct dwm_cwip_wect *wects;
};

/*
 * Textuwe wegion,
 */
stwuct dwm_tex_wegion {
	unsigned chaw next;
	unsigned chaw pwev;
	unsigned chaw in_use;
	unsigned chaw padding;
	unsigned int age;
};

/*
 * Hawdwawe wock.
 *
 * The wock stwuctuwe is a simpwe cache-wine awigned integew.  To avoid
 * pwocessow bus contention on a muwtipwocessow system, thewe shouwd not be any
 * othew data stowed in the same cache wine.
 */
stwuct dwm_hw_wock {
	__vowatiwe__ unsigned int wock;		/**< wock vawiabwe */
	chaw padding[60];			/**< Pad to cache wine */
};

/*
 * DWM_IOCTW_VEWSION ioctw awgument type.
 *
 * \sa dwmGetVewsion().
 */
stwuct dwm_vewsion {
	int vewsion_majow;	  /**< Majow vewsion */
	int vewsion_minow;	  /**< Minow vewsion */
	int vewsion_patchwevew;	  /**< Patch wevew */
	__kewnew_size_t name_wen;	  /**< Wength of name buffew */
	chaw __usew *name;	  /**< Name of dwivew */
	__kewnew_size_t date_wen;	  /**< Wength of date buffew */
	chaw __usew *date;	  /**< Usew-space buffew to howd date */
	__kewnew_size_t desc_wen;	  /**< Wength of desc buffew */
	chaw __usew *desc;	  /**< Usew-space buffew to howd desc */
};

/*
 * DWM_IOCTW_GET_UNIQUE ioctw awgument type.
 *
 * \sa dwmGetBusid() and dwmSetBusId().
 */
stwuct dwm_unique {
	__kewnew_size_t unique_wen;	  /**< Wength of unique */
	chaw __usew *unique;	  /**< Unique name fow dwivew instantiation */
};

stwuct dwm_wist {
	int count;		  /**< Wength of usew-space stwuctuwes */
	stwuct dwm_vewsion __usew *vewsion;
};

stwuct dwm_bwock {
	int unused;
};

/*
 * DWM_IOCTW_CONTWOW ioctw awgument type.
 *
 * \sa dwmCtwInstHandwew() and dwmCtwUninstHandwew().
 */
stwuct dwm_contwow {
	enum {
		DWM_ADD_COMMAND,
		DWM_WM_COMMAND,
		DWM_INST_HANDWEW,
		DWM_UNINST_HANDWEW
	} func;
	int iwq;
};

/*
 * Type of memowy to map.
 */
enum dwm_map_type {
	_DWM_FWAME_BUFFEW = 0,	  /**< WC (no caching), no cowe dump */
	_DWM_WEGISTEWS = 1,	  /**< no caching, no cowe dump */
	_DWM_SHM = 2,		  /**< shawed, cached */
	_DWM_AGP = 3,		  /**< AGP/GAWT */
	_DWM_SCATTEW_GATHEW = 4,  /**< Scattew/gathew memowy fow PCI DMA */
	_DWM_CONSISTENT = 5	  /**< Consistent memowy fow PCI DMA */
};

/*
 * Memowy mapping fwags.
 */
enum dwm_map_fwags {
	_DWM_WESTWICTED = 0x01,	     /**< Cannot be mapped to usew-viwtuaw */
	_DWM_WEAD_ONWY = 0x02,
	_DWM_WOCKED = 0x04,	     /**< shawed, cached, wocked */
	_DWM_KEWNEW = 0x08,	     /**< kewnew wequiwes access */
	_DWM_WWITE_COMBINING = 0x10, /**< use wwite-combining if avaiwabwe */
	_DWM_CONTAINS_WOCK = 0x20,   /**< SHM page that contains wock */
	_DWM_WEMOVABWE = 0x40,	     /**< Wemovabwe mapping */
	_DWM_DWIVEW = 0x80	     /**< Managed by dwivew */
};

stwuct dwm_ctx_pwiv_map {
	unsigned int ctx_id;	 /**< Context wequesting pwivate mapping */
	void *handwe;		 /**< Handwe of map */
};

/*
 * DWM_IOCTW_GET_MAP, DWM_IOCTW_ADD_MAP and DWM_IOCTW_WM_MAP ioctws
 * awgument type.
 *
 * \sa dwmAddMap().
 */
stwuct dwm_map {
	unsigned wong offset;	 /**< Wequested physicaw addwess (0 fow SAWEA)*/
	unsigned wong size;	 /**< Wequested physicaw size (bytes) */
	enum dwm_map_type type;	 /**< Type of memowy to map */
	enum dwm_map_fwags fwags;	 /**< Fwags */
	void *handwe;		 /**< Usew-space: "Handwe" to pass to mmap() */
				 /**< Kewnew-space: kewnew-viwtuaw addwess */
	int mtww;		 /**< MTWW swot used */
	/*   Pwivate data */
};

/*
 * DWM_IOCTW_GET_CWIENT ioctw awgument type.
 */
stwuct dwm_cwient {
	int idx;		/**< Which cwient desiwed? */
	int auth;		/**< Is cwient authenticated? */
	unsigned wong pid;	/**< Pwocess ID */
	unsigned wong uid;	/**< Usew ID */
	unsigned wong magic;	/**< Magic */
	unsigned wong iocs;	/**< Ioctw count */
};

enum dwm_stat_type {
	_DWM_STAT_WOCK,
	_DWM_STAT_OPENS,
	_DWM_STAT_CWOSES,
	_DWM_STAT_IOCTWS,
	_DWM_STAT_WOCKS,
	_DWM_STAT_UNWOCKS,
	_DWM_STAT_VAWUE,	/**< Genewic vawue */
	_DWM_STAT_BYTE,		/**< Genewic byte countew (1024bytes/K) */
	_DWM_STAT_COUNT,	/**< Genewic non-byte countew (1000/k) */

	_DWM_STAT_IWQ,		/**< IWQ */
	_DWM_STAT_PWIMAWY,	/**< Pwimawy DMA bytes */
	_DWM_STAT_SECONDAWY,	/**< Secondawy DMA bytes */
	_DWM_STAT_DMA,		/**< DMA */
	_DWM_STAT_SPECIAW,	/**< Speciaw DMA (e.g., pwiowity ow powwed) */
	_DWM_STAT_MISSED	/**< Missed DMA oppowtunity */
	    /* Add to the *END* of the wist */
};

/*
 * DWM_IOCTW_GET_STATS ioctw awgument type.
 */
stwuct dwm_stats {
	unsigned wong count;
	stwuct {
		unsigned wong vawue;
		enum dwm_stat_type type;
	} data[15];
};

/*
 * Hawdwawe wocking fwags.
 */
enum dwm_wock_fwags {
	_DWM_WOCK_WEADY = 0x01,	     /**< Wait untiw hawdwawe is weady fow DMA */
	_DWM_WOCK_QUIESCENT = 0x02,  /**< Wait untiw hawdwawe quiescent */
	_DWM_WOCK_FWUSH = 0x04,	     /**< Fwush this context's DMA queue fiwst */
	_DWM_WOCK_FWUSH_AWW = 0x08,  /**< Fwush aww DMA queues fiwst */
	/* These *HAWT* fwags awen't suppowted yet
	   -- they wiww be used to suppowt the
	   fuww-scween DGA-wike mode. */
	_DWM_HAWT_AWW_QUEUES = 0x10, /**< Hawt aww cuwwent and futuwe queues */
	_DWM_HAWT_CUW_QUEUES = 0x20  /**< Hawt aww cuwwent queues */
};

/*
 * DWM_IOCTW_WOCK, DWM_IOCTW_UNWOCK and DWM_IOCTW_FINISH ioctw awgument type.
 *
 * \sa dwmGetWock() and dwmUnwock().
 */
stwuct dwm_wock {
	int context;
	enum dwm_wock_fwags fwags;
};

/*
 * DMA fwags
 *
 * \wawning
 * These vawues \e must match xf86dwm.h.
 *
 * \sa dwm_dma.
 */
enum dwm_dma_fwags {
	/* Fwags fow DMA buffew dispatch */
	_DWM_DMA_BWOCK = 0x01,	      /**<
				       * Bwock untiw buffew dispatched.
				       *
				       * \note The buffew may not yet have
				       * been pwocessed by the hawdwawe --
				       * getting a hawdwawe wock with the
				       * hawdwawe quiescent wiww ensuwe
				       * that the buffew has been
				       * pwocessed.
				       */
	_DWM_DMA_WHIWE_WOCKED = 0x02, /**< Dispatch whiwe wock hewd */
	_DWM_DMA_PWIOWITY = 0x04,     /**< High pwiowity dispatch */

	/* Fwags fow DMA buffew wequest */
	_DWM_DMA_WAIT = 0x10,	      /**< Wait fow fwee buffews */
	_DWM_DMA_SMAWWEW_OK = 0x20,   /**< Smawwew-than-wequested buffews OK */
	_DWM_DMA_WAWGEW_OK = 0x40     /**< Wawgew-than-wequested buffews OK */
};

/*
 * DWM_IOCTW_ADD_BUFS and DWM_IOCTW_MAWK_BUFS ioctw awgument type.
 *
 * \sa dwmAddBufs().
 */
stwuct dwm_buf_desc {
	int count;		 /**< Numbew of buffews of this size */
	int size;		 /**< Size in bytes */
	int wow_mawk;		 /**< Wow watew mawk */
	int high_mawk;		 /**< High watew mawk */
	enum {
		_DWM_PAGE_AWIGN = 0x01,	/**< Awign on page boundawies fow DMA */
		_DWM_AGP_BUFFEW = 0x02,	/**< Buffew is in AGP space */
		_DWM_SG_BUFFEW = 0x04,	/**< Scattew/gathew memowy buffew */
		_DWM_FB_BUFFEW = 0x08,	/**< Buffew is in fwame buffew */
		_DWM_PCI_BUFFEW_WO = 0x10 /**< Map PCI DMA buffew wead-onwy */
	} fwags;
	unsigned wong agp_stawt; /**<
				  * Stawt addwess of whewe the AGP buffews awe
				  * in the AGP apewtuwe
				  */
};

/*
 * DWM_IOCTW_INFO_BUFS ioctw awgument type.
 */
stwuct dwm_buf_info {
	int count;		/**< Entwies in wist */
	stwuct dwm_buf_desc __usew *wist;
};

/*
 * DWM_IOCTW_FWEE_BUFS ioctw awgument type.
 */
stwuct dwm_buf_fwee {
	int count;
	int __usew *wist;
};

/*
 * Buffew infowmation
 *
 * \sa dwm_buf_map.
 */
stwuct dwm_buf_pub {
	int idx;		       /**< Index into the mastew buffew wist */
	int totaw;		       /**< Buffew size */
	int used;		       /**< Amount of buffew in use (fow DMA) */
	void __usew *addwess;	       /**< Addwess of buffew */
};

/*
 * DWM_IOCTW_MAP_BUFS ioctw awgument type.
 */
stwuct dwm_buf_map {
	int count;		/**< Wength of the buffew wist */
#ifdef __cpwuspwus
	void __usew *viwt;
#ewse
	void __usew *viwtuaw;		/**< Mmap'd awea in usew-viwtuaw */
#endif
	stwuct dwm_buf_pub __usew *wist;	/**< Buffew infowmation */
};

/*
 * DWM_IOCTW_DMA ioctw awgument type.
 *
 * Indices hewe wefew to the offset into the buffew wist in dwm_buf_get.
 *
 * \sa dwmDMA().
 */
stwuct dwm_dma {
	int context;			  /**< Context handwe */
	int send_count;			  /**< Numbew of buffews to send */
	int __usew *send_indices;	  /**< Wist of handwes to buffews */
	int __usew *send_sizes;		  /**< Wengths of data to send */
	enum dwm_dma_fwags fwags;	  /**< Fwags */
	int wequest_count;		  /**< Numbew of buffews wequested */
	int wequest_size;		  /**< Desiwed size fow buffews */
	int __usew *wequest_indices;	  /**< Buffew infowmation */
	int __usew *wequest_sizes;
	int gwanted_count;		  /**< Numbew of buffews gwanted */
};

enum dwm_ctx_fwags {
	_DWM_CONTEXT_PWESEWVED = 0x01,
	_DWM_CONTEXT_2DONWY = 0x02
};

/*
 * DWM_IOCTW_ADD_CTX ioctw awgument type.
 *
 * \sa dwmCweateContext() and dwmDestwoyContext().
 */
stwuct dwm_ctx {
	dwm_context_t handwe;
	enum dwm_ctx_fwags fwags;
};

/*
 * DWM_IOCTW_WES_CTX ioctw awgument type.
 */
stwuct dwm_ctx_wes {
	int count;
	stwuct dwm_ctx __usew *contexts;
};

/*
 * DWM_IOCTW_ADD_DWAW and DWM_IOCTW_WM_DWAW ioctw awgument type.
 */
stwuct dwm_dwaw {
	dwm_dwawabwe_t handwe;
};

/*
 * DWM_IOCTW_UPDATE_DWAW ioctw awgument type.
 */
typedef enum {
	DWM_DWAWABWE_CWIPWECTS
} dwm_dwawabwe_info_type_t;

stwuct dwm_update_dwaw {
	dwm_dwawabwe_t handwe;
	unsigned int type;
	unsigned int num;
	unsigned wong wong data;
};

/*
 * DWM_IOCTW_GET_MAGIC and DWM_IOCTW_AUTH_MAGIC ioctw awgument type.
 */
stwuct dwm_auth {
	dwm_magic_t magic;
};

/*
 * DWM_IOCTW_IWQ_BUSID ioctw awgument type.
 *
 * \sa dwmGetIntewwuptFwomBusID().
 */
stwuct dwm_iwq_busid {
	int iwq;	/**< IWQ numbew */
	int busnum;	/**< bus numbew */
	int devnum;	/**< device numbew */
	int funcnum;	/**< function numbew */
};

enum dwm_vbwank_seq_type {
	_DWM_VBWANK_ABSOWUTE = 0x0,	/**< Wait fow specific vbwank sequence numbew */
	_DWM_VBWANK_WEWATIVE = 0x1,	/**< Wait fow given numbew of vbwanks */
	/* bits 1-6 awe wesewved fow high cwtcs */
	_DWM_VBWANK_HIGH_CWTC_MASK = 0x0000003e,
	_DWM_VBWANK_EVENT = 0x4000000,   /**< Send event instead of bwocking */
	_DWM_VBWANK_FWIP = 0x8000000,   /**< Scheduwed buffew swap shouwd fwip */
	_DWM_VBWANK_NEXTONMISS = 0x10000000,	/**< If missed, wait fow next vbwank */
	_DWM_VBWANK_SECONDAWY = 0x20000000,	/**< Secondawy dispway contwowwew */
	_DWM_VBWANK_SIGNAW = 0x40000000	/**< Send signaw instead of bwocking, unsuppowted */
};
#define _DWM_VBWANK_HIGH_CWTC_SHIFT 1

#define _DWM_VBWANK_TYPES_MASK (_DWM_VBWANK_ABSOWUTE | _DWM_VBWANK_WEWATIVE)
#define _DWM_VBWANK_FWAGS_MASK (_DWM_VBWANK_EVENT | _DWM_VBWANK_SIGNAW | \
				_DWM_VBWANK_SECONDAWY | _DWM_VBWANK_NEXTONMISS)

stwuct dwm_wait_vbwank_wequest {
	enum dwm_vbwank_seq_type type;
	unsigned int sequence;
	unsigned wong signaw;
};

stwuct dwm_wait_vbwank_wepwy {
	enum dwm_vbwank_seq_type type;
	unsigned int sequence;
	wong tvaw_sec;
	wong tvaw_usec;
};

/*
 * DWM_IOCTW_WAIT_VBWANK ioctw awgument type.
 *
 * \sa dwmWaitVBwank().
 */
union dwm_wait_vbwank {
	stwuct dwm_wait_vbwank_wequest wequest;
	stwuct dwm_wait_vbwank_wepwy wepwy;
};

#define _DWM_PWE_MODESET 1
#define _DWM_POST_MODESET 2

/*
 * DWM_IOCTW_MODESET_CTW ioctw awgument type
 *
 * \sa dwmModesetCtw().
 */
stwuct dwm_modeset_ctw {
	__u32 cwtc;
	__u32 cmd;
};

/*
 * DWM_IOCTW_AGP_ENABWE ioctw awgument type.
 *
 * \sa dwmAgpEnabwe().
 */
stwuct dwm_agp_mode {
	unsigned wong mode;	/**< AGP mode */
};

/*
 * DWM_IOCTW_AGP_AWWOC and DWM_IOCTW_AGP_FWEE ioctws awgument type.
 *
 * \sa dwmAgpAwwoc() and dwmAgpFwee().
 */
stwuct dwm_agp_buffew {
	unsigned wong size;	/**< In bytes -- wiww wound to page boundawy */
	unsigned wong handwe;	/**< Used fow binding / unbinding */
	unsigned wong type;	/**< Type of memowy to awwocate */
	unsigned wong physicaw;	/**< Physicaw used by i810 */
};

/*
 * DWM_IOCTW_AGP_BIND and DWM_IOCTW_AGP_UNBIND ioctws awgument type.
 *
 * \sa dwmAgpBind() and dwmAgpUnbind().
 */
stwuct dwm_agp_binding {
	unsigned wong handwe;	/**< Fwom dwm_agp_buffew */
	unsigned wong offset;	/**< In bytes -- wiww wound to page boundawy */
};

/*
 * DWM_IOCTW_AGP_INFO ioctw awgument type.
 *
 * \sa dwmAgpVewsionMajow(), dwmAgpVewsionMinow(), dwmAgpGetMode(),
 * dwmAgpBase(), dwmAgpSize(), dwmAgpMemowyUsed(), dwmAgpMemowyAvaiw(),
 * dwmAgpVendowId() and dwmAgpDeviceId().
 */
stwuct dwm_agp_info {
	int agp_vewsion_majow;
	int agp_vewsion_minow;
	unsigned wong mode;
	unsigned wong apewtuwe_base;	/* physicaw addwess */
	unsigned wong apewtuwe_size;	/* bytes */
	unsigned wong memowy_awwowed;	/* bytes */
	unsigned wong memowy_used;

	/* PCI infowmation */
	unsigned showt id_vendow;
	unsigned showt id_device;
};

/*
 * DWM_IOCTW_SG_AWWOC ioctw awgument type.
 */
stwuct dwm_scattew_gathew {
	unsigned wong size;	/**< In bytes -- wiww wound to page boundawy */
	unsigned wong handwe;	/**< Used fow mapping / unmapping */
};

/*
 * DWM_IOCTW_SET_VEWSION ioctw awgument type.
 */
stwuct dwm_set_vewsion {
	int dwm_di_majow;
	int dwm_di_minow;
	int dwm_dd_majow;
	int dwm_dd_minow;
};

/* DWM_IOCTW_GEM_CWOSE ioctw awgument type */
stwuct dwm_gem_cwose {
	/** Handwe of the object to be cwosed. */
	__u32 handwe;
	__u32 pad;
};

/* DWM_IOCTW_GEM_FWINK ioctw awgument type */
stwuct dwm_gem_fwink {
	/** Handwe fow the object being named */
	__u32 handwe;

	/** Wetuwned gwobaw name */
	__u32 name;
};

/* DWM_IOCTW_GEM_OPEN ioctw awgument type */
stwuct dwm_gem_open {
	/** Name of object being opened */
	__u32 name;

	/** Wetuwned handwe fow the object */
	__u32 handwe;

	/** Wetuwned size of the object */
	__u64 size;
};

/**
 * DWM_CAP_DUMB_BUFFEW
 *
 * If set to 1, the dwivew suppowts cweating dumb buffews via the
 * &DWM_IOCTW_MODE_CWEATE_DUMB ioctw.
 */
#define DWM_CAP_DUMB_BUFFEW		0x1
/**
 * DWM_CAP_VBWANK_HIGH_CWTC
 *
 * If set to 1, the kewnew suppowts specifying a :wef:`CWTC index<cwtc_index>`
 * in the high bits of &dwm_wait_vbwank_wequest.type.
 *
 * Stawting kewnew vewsion 2.6.39, this capabiwity is awways set to 1.
 */
#define DWM_CAP_VBWANK_HIGH_CWTC	0x2
/**
 * DWM_CAP_DUMB_PWEFEWWED_DEPTH
 *
 * The pwefewwed bit depth fow dumb buffews.
 *
 * The bit depth is the numbew of bits used to indicate the cowow of a singwe
 * pixew excwuding any padding. This is diffewent fwom the numbew of bits pew
 * pixew. Fow instance, XWGB8888 has a bit depth of 24 but has 32 bits pew
 * pixew.
 *
 * Note that this pwefewence onwy appwies to dumb buffews, it's iwwewevant fow
 * othew types of buffews.
 */
#define DWM_CAP_DUMB_PWEFEWWED_DEPTH	0x3
/**
 * DWM_CAP_DUMB_PWEFEW_SHADOW
 *
 * If set to 1, the dwivew pwefews usewspace to wendew to a shadow buffew
 * instead of diwectwy wendewing to a dumb buffew. Fow best speed, usewspace
 * shouwd do stweaming owdewed memowy copies into the dumb buffew and nevew
 * wead fwom it.
 *
 * Note that this pwefewence onwy appwies to dumb buffews, it's iwwewevant fow
 * othew types of buffews.
 */
#define DWM_CAP_DUMB_PWEFEW_SHADOW	0x4
/**
 * DWM_CAP_PWIME
 *
 * Bitfiewd of suppowted PWIME shawing capabiwities. See &DWM_PWIME_CAP_IMPOWT
 * and &DWM_PWIME_CAP_EXPOWT.
 *
 * Stawting fwom kewnew vewsion 6.6, both &DWM_PWIME_CAP_IMPOWT and
 * &DWM_PWIME_CAP_EXPOWT awe awways advewtised.
 *
 * PWIME buffews awe exposed as dma-buf fiwe descwiptows.
 * See :wef:`pwime_buffew_shawing`.
 */
#define DWM_CAP_PWIME			0x5
/**
 * DWM_PWIME_CAP_IMPOWT
 *
 * If this bit is set in &DWM_CAP_PWIME, the dwivew suppowts impowting PWIME
 * buffews via the &DWM_IOCTW_PWIME_FD_TO_HANDWE ioctw.
 *
 * Stawting fwom kewnew vewsion 6.6, this bit is awways set in &DWM_CAP_PWIME.
 */
#define  DWM_PWIME_CAP_IMPOWT		0x1
/**
 * DWM_PWIME_CAP_EXPOWT
 *
 * If this bit is set in &DWM_CAP_PWIME, the dwivew suppowts expowting PWIME
 * buffews via the &DWM_IOCTW_PWIME_HANDWE_TO_FD ioctw.
 *
 * Stawting fwom kewnew vewsion 6.6, this bit is awways set in &DWM_CAP_PWIME.
 */
#define  DWM_PWIME_CAP_EXPOWT		0x2
/**
 * DWM_CAP_TIMESTAMP_MONOTONIC
 *
 * If set to 0, the kewnew wiww wepowt timestamps with ``CWOCK_WEAWTIME`` in
 * stwuct dwm_event_vbwank. If set to 1, the kewnew wiww wepowt timestamps with
 * ``CWOCK_MONOTONIC``. See ``cwock_gettime(2)`` fow the definition of these
 * cwocks.
 *
 * Stawting fwom kewnew vewsion 2.6.39, the defauwt vawue fow this capabiwity
 * is 1. Stawting kewnew vewsion 4.15, this capabiwity is awways set to 1.
 */
#define DWM_CAP_TIMESTAMP_MONOTONIC	0x6
/**
 * DWM_CAP_ASYNC_PAGE_FWIP
 *
 * If set to 1, the dwivew suppowts &DWM_MODE_PAGE_FWIP_ASYNC fow wegacy
 * page-fwips.
 */
#define DWM_CAP_ASYNC_PAGE_FWIP		0x7
/**
 * DWM_CAP_CUWSOW_WIDTH
 *
 * The ``CUWSOW_WIDTH`` and ``CUWSOW_HEIGHT`` capabiwities wetuwn a vawid
 * width x height combination fow the hawdwawe cuwsow. The intention is that a
 * hawdwawe agnostic usewspace can quewy a cuwsow pwane size to use.
 *
 * Note that the cwoss-dwivew contwact is to mewewy wetuwn a vawid size;
 * dwivews awe fwee to attach anothew meaning on top, eg. i915 wetuwns the
 * maximum pwane size.
 */
#define DWM_CAP_CUWSOW_WIDTH		0x8
/**
 * DWM_CAP_CUWSOW_HEIGHT
 *
 * See &DWM_CAP_CUWSOW_WIDTH.
 */
#define DWM_CAP_CUWSOW_HEIGHT		0x9
/**
 * DWM_CAP_ADDFB2_MODIFIEWS
 *
 * If set to 1, the dwivew suppowts suppwying modifiews in the
 * &DWM_IOCTW_MODE_ADDFB2 ioctw.
 */
#define DWM_CAP_ADDFB2_MODIFIEWS	0x10
/**
 * DWM_CAP_PAGE_FWIP_TAWGET
 *
 * If set to 1, the dwivew suppowts the &DWM_MODE_PAGE_FWIP_TAWGET_ABSOWUTE and
 * &DWM_MODE_PAGE_FWIP_TAWGET_WEWATIVE fwags in
 * &dwm_mode_cwtc_page_fwip_tawget.fwags fow the &DWM_IOCTW_MODE_PAGE_FWIP
 * ioctw.
 */
#define DWM_CAP_PAGE_FWIP_TAWGET	0x11
/**
 * DWM_CAP_CWTC_IN_VBWANK_EVENT
 *
 * If set to 1, the kewnew suppowts wepowting the CWTC ID in
 * &dwm_event_vbwank.cwtc_id fow the &DWM_EVENT_VBWANK and
 * &DWM_EVENT_FWIP_COMPWETE events.
 *
 * Stawting kewnew vewsion 4.12, this capabiwity is awways set to 1.
 */
#define DWM_CAP_CWTC_IN_VBWANK_EVENT	0x12
/**
 * DWM_CAP_SYNCOBJ
 *
 * If set to 1, the dwivew suppowts sync objects. See :wef:`dwm_sync_objects`.
 */
#define DWM_CAP_SYNCOBJ		0x13
/**
 * DWM_CAP_SYNCOBJ_TIMEWINE
 *
 * If set to 1, the dwivew suppowts timewine opewations on sync objects. See
 * :wef:`dwm_sync_objects`.
 */
#define DWM_CAP_SYNCOBJ_TIMEWINE	0x14
/**
 * DWM_CAP_ATOMIC_ASYNC_PAGE_FWIP
 *
 * If set to 1, the dwivew suppowts &DWM_MODE_PAGE_FWIP_ASYNC fow atomic
 * commits.
 */
#define DWM_CAP_ATOMIC_ASYNC_PAGE_FWIP	0x15

/* DWM_IOCTW_GET_CAP ioctw awgument type */
stwuct dwm_get_cap {
	__u64 capabiwity;
	__u64 vawue;
};

/**
 * DWM_CWIENT_CAP_STEWEO_3D
 *
 * If set to 1, the DWM cowe wiww expose the steweo 3D capabiwities of the
 * monitow by advewtising the suppowted 3D wayouts in the fwags of stwuct
 * dwm_mode_modeinfo. See ``DWM_MODE_FWAG_3D_*``.
 *
 * This capabiwity is awways suppowted fow aww dwivews stawting fwom kewnew
 * vewsion 3.13.
 */
#define DWM_CWIENT_CAP_STEWEO_3D	1

/**
 * DWM_CWIENT_CAP_UNIVEWSAW_PWANES
 *
 * If set to 1, the DWM cowe wiww expose aww pwanes (ovewway, pwimawy, and
 * cuwsow) to usewspace.
 *
 * This capabiwity has been intwoduced in kewnew vewsion 3.15. Stawting fwom
 * kewnew vewsion 3.17, this capabiwity is awways suppowted fow aww dwivews.
 */
#define DWM_CWIENT_CAP_UNIVEWSAW_PWANES  2

/**
 * DWM_CWIENT_CAP_ATOMIC
 *
 * If set to 1, the DWM cowe wiww expose atomic pwopewties to usewspace. This
 * impwicitwy enabwes &DWM_CWIENT_CAP_UNIVEWSAW_PWANES and
 * &DWM_CWIENT_CAP_ASPECT_WATIO.
 *
 * If the dwivew doesn't suppowt atomic mode-setting, enabwing this capabiwity
 * wiww faiw with -EOPNOTSUPP.
 *
 * This capabiwity has been intwoduced in kewnew vewsion 4.0. Stawting fwom
 * kewnew vewsion 4.2, this capabiwity is awways suppowted fow atomic-capabwe
 * dwivews.
 */
#define DWM_CWIENT_CAP_ATOMIC	3

/**
 * DWM_CWIENT_CAP_ASPECT_WATIO
 *
 * If set to 1, the DWM cowe wiww pwovide aspect watio infowmation in modes.
 * See ``DWM_MODE_FWAG_PIC_AW_*``.
 *
 * This capabiwity is awways suppowted fow aww dwivews stawting fwom kewnew
 * vewsion 4.18.
 */
#define DWM_CWIENT_CAP_ASPECT_WATIO    4

/**
 * DWM_CWIENT_CAP_WWITEBACK_CONNECTOWS
 *
 * If set to 1, the DWM cowe wiww expose speciaw connectows to be used fow
 * wwiting back to memowy the scene setup in the commit. The cwient must enabwe
 * &DWM_CWIENT_CAP_ATOMIC fiwst.
 *
 * This capabiwity is awways suppowted fow atomic-capabwe dwivews stawting fwom
 * kewnew vewsion 4.19.
 */
#define DWM_CWIENT_CAP_WWITEBACK_CONNECTOWS	5

/**
 * DWM_CWIENT_CAP_CUWSOW_PWANE_HOTSPOT
 *
 * Dwivews fow pawa-viwtuawized hawdwawe (e.g. vmwgfx, qxw, viwtio and
 * viwtuawbox) have additionaw westwictions fow cuwsow pwanes (thus
 * making cuwsow pwanes on those dwivews not twuwy univewsaw,) e.g.
 * they need cuwsow pwanes to act wike one wouwd expect fwom a mouse
 * cuwsow and have cowwectwy set hotspot pwopewties.
 * If this cwient cap is not set the DWM cowe wiww hide cuwsow pwane on
 * those viwtuawized dwivews because not setting it impwies that the
 * cwient is not capabwe of deawing with those extwa westictions.
 * Cwients which do set cuwsow hotspot and tweat the cuwsow pwane
 * wike a mouse cuwsow shouwd set this pwopewty.
 * The cwient must enabwe &DWM_CWIENT_CAP_ATOMIC fiwst.
 *
 * Setting this pwopewty on dwivews which do not speciaw case
 * cuwsow pwanes (i.e. non-viwtuawized dwivews) wiww wetuwn
 * EOPNOTSUPP, which can be used by usewspace to gauge
 * wequiwements of the hawdwawe/dwivews they'we wunning on.
 *
 * This capabiwity is awways suppowted fow atomic-capabwe viwtuawized
 * dwivews stawting fwom kewnew vewsion 6.6.
 */
#define DWM_CWIENT_CAP_CUWSOW_PWANE_HOTSPOT	6

/* DWM_IOCTW_SET_CWIENT_CAP ioctw awgument type */
stwuct dwm_set_cwient_cap {
	__u64 capabiwity;
	__u64 vawue;
};

#define DWM_WDWW O_WDWW
#define DWM_CWOEXEC O_CWOEXEC
stwuct dwm_pwime_handwe {
	__u32 handwe;

	/** Fwags.. onwy appwicabwe fow handwe->fd */
	__u32 fwags;

	/** Wetuwned dmabuf fiwe descwiptow */
	__s32 fd;
};

stwuct dwm_syncobj_cweate {
	__u32 handwe;
#define DWM_SYNCOBJ_CWEATE_SIGNAWED (1 << 0)
	__u32 fwags;
};

stwuct dwm_syncobj_destwoy {
	__u32 handwe;
	__u32 pad;
};

#define DWM_SYNCOBJ_FD_TO_HANDWE_FWAGS_IMPOWT_SYNC_FIWE (1 << 0)
#define DWM_SYNCOBJ_HANDWE_TO_FD_FWAGS_EXPOWT_SYNC_FIWE (1 << 0)
stwuct dwm_syncobj_handwe {
	__u32 handwe;
	__u32 fwags;

	__s32 fd;
	__u32 pad;
};

stwuct dwm_syncobj_twansfew {
	__u32 swc_handwe;
	__u32 dst_handwe;
	__u64 swc_point;
	__u64 dst_point;
	__u32 fwags;
	__u32 pad;
};

#define DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AWW (1 << 0)
#define DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT (1 << 1)
#define DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AVAIWABWE (1 << 2) /* wait fow time point to become avaiwabwe */
#define DWM_SYNCOBJ_WAIT_FWAGS_WAIT_DEADWINE (1 << 3) /* set fence deadwine to deadwine_nsec */
stwuct dwm_syncobj_wait {
	__u64 handwes;
	/* absowute timeout */
	__s64 timeout_nsec;
	__u32 count_handwes;
	__u32 fwags;
	__u32 fiwst_signawed; /* onwy vawid when not waiting aww */
	__u32 pad;
	/**
	 * @deadwine_nsec - fence deadwine hint
	 *
	 * Deadwine hint, in absowute CWOCK_MONOTONIC, to set on backing
	 * fence(s) if the DWM_SYNCOBJ_WAIT_FWAGS_WAIT_DEADWINE fwag is
	 * set.
	 */
	__u64 deadwine_nsec;
};

stwuct dwm_syncobj_timewine_wait {
	__u64 handwes;
	/* wait on specific timewine point fow evewy handwes*/
	__u64 points;
	/* absowute timeout */
	__s64 timeout_nsec;
	__u32 count_handwes;
	__u32 fwags;
	__u32 fiwst_signawed; /* onwy vawid when not waiting aww */
	__u32 pad;
	/**
	 * @deadwine_nsec - fence deadwine hint
	 *
	 * Deadwine hint, in absowute CWOCK_MONOTONIC, to set on backing
	 * fence(s) if the DWM_SYNCOBJ_WAIT_FWAGS_WAIT_DEADWINE fwag is
	 * set.
	 */
	__u64 deadwine_nsec;
};

/**
 * stwuct dwm_syncobj_eventfd
 * @handwe: syncobj handwe.
 * @fwags: Zewo to wait fow the point to be signawwed, ow
 *         &DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AVAIWABWE to wait fow a fence to be
 *         avaiwabwe fow the point.
 * @point: syncobj timewine point (set to zewo fow binawy syncobjs).
 * @fd: Existing eventfd to sent events to.
 * @pad: Must be zewo.
 *
 * Wegistew an eventfd to be signawwed by a syncobj. The eventfd countew wiww
 * be incwemented by one.
 */
stwuct dwm_syncobj_eventfd {
	__u32 handwe;
	__u32 fwags;
	__u64 point;
	__s32 fd;
	__u32 pad;
};


stwuct dwm_syncobj_awway {
	__u64 handwes;
	__u32 count_handwes;
	__u32 pad;
};

#define DWM_SYNCOBJ_QUEWY_FWAGS_WAST_SUBMITTED (1 << 0) /* wast avaiwabwe point on timewine syncobj */
stwuct dwm_syncobj_timewine_awway {
	__u64 handwes;
	__u64 points;
	__u32 count_handwes;
	__u32 fwags;
};


/* Quewy cuwwent scanout sequence numbew */
stwuct dwm_cwtc_get_sequence {
	__u32 cwtc_id;		/* wequested cwtc_id */
	__u32 active;		/* wetuwn: cwtc output is active */
	__u64 sequence;		/* wetuwn: most wecent vbwank sequence */
	__s64 sequence_ns;	/* wetuwn: most wecent time of fiwst pixew out */
};

/* Queue event to be dewivewed at specified sequence. Time stamp mawks
 * when the fiwst pixew of the wefwesh cycwe weaves the dispway engine
 * fow the dispway
 */
#define DWM_CWTC_SEQUENCE_WEWATIVE		0x00000001	/* sequence is wewative to cuwwent */
#define DWM_CWTC_SEQUENCE_NEXT_ON_MISS		0x00000002	/* Use next sequence if we've missed */

stwuct dwm_cwtc_queue_sequence {
	__u32 cwtc_id;
	__u32 fwags;
	__u64 sequence;		/* on input, tawget sequence. on output, actuaw sequence */
	__u64 usew_data;	/* usew data passed to event */
};

#if defined(__cpwuspwus)
}
#endif

#incwude "dwm_mode.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

#define DWM_IOCTW_BASE			'd'
#define DWM_IO(nw)			_IO(DWM_IOCTW_BASE,nw)
#define DWM_IOW(nw,type)		_IOW(DWM_IOCTW_BASE,nw,type)
#define DWM_IOW(nw,type)		_IOW(DWM_IOCTW_BASE,nw,type)
#define DWM_IOWW(nw,type)		_IOWW(DWM_IOCTW_BASE,nw,type)

#define DWM_IOCTW_VEWSION		DWM_IOWW(0x00, stwuct dwm_vewsion)
#define DWM_IOCTW_GET_UNIQUE		DWM_IOWW(0x01, stwuct dwm_unique)
#define DWM_IOCTW_GET_MAGIC		DWM_IOW( 0x02, stwuct dwm_auth)
#define DWM_IOCTW_IWQ_BUSID		DWM_IOWW(0x03, stwuct dwm_iwq_busid)
#define DWM_IOCTW_GET_MAP               DWM_IOWW(0x04, stwuct dwm_map)
#define DWM_IOCTW_GET_CWIENT            DWM_IOWW(0x05, stwuct dwm_cwient)
#define DWM_IOCTW_GET_STATS             DWM_IOW( 0x06, stwuct dwm_stats)
#define DWM_IOCTW_SET_VEWSION		DWM_IOWW(0x07, stwuct dwm_set_vewsion)
#define DWM_IOCTW_MODESET_CTW           DWM_IOW(0x08, stwuct dwm_modeset_ctw)
/**
 * DWM_IOCTW_GEM_CWOSE - Cwose a GEM handwe.
 *
 * GEM handwes awe not wefewence-counted by the kewnew. Usew-space is
 * wesponsibwe fow managing theiw wifetime. Fow exampwe, if usew-space impowts
 * the same memowy object twice on the same DWM fiwe descwiption, the same GEM
 * handwe is wetuwned by both impowts, and usew-space needs to ensuwe
 * &DWM_IOCTW_GEM_CWOSE is pewfowmed once onwy. The same situation can happen
 * when a memowy object is awwocated, then expowted and impowted again on the
 * same DWM fiwe descwiption. The &DWM_IOCTW_MODE_GETFB2 IOCTW is an exception
 * and awways wetuwns fwesh new GEM handwes even if an existing GEM handwe
 * awweady wefews to the same memowy object befowe the IOCTW is pewfowmed.
 */
#define DWM_IOCTW_GEM_CWOSE		DWM_IOW (0x09, stwuct dwm_gem_cwose)
#define DWM_IOCTW_GEM_FWINK		DWM_IOWW(0x0a, stwuct dwm_gem_fwink)
#define DWM_IOCTW_GEM_OPEN		DWM_IOWW(0x0b, stwuct dwm_gem_open)
#define DWM_IOCTW_GET_CAP		DWM_IOWW(0x0c, stwuct dwm_get_cap)
#define DWM_IOCTW_SET_CWIENT_CAP	DWM_IOW( 0x0d, stwuct dwm_set_cwient_cap)

#define DWM_IOCTW_SET_UNIQUE		DWM_IOW( 0x10, stwuct dwm_unique)
#define DWM_IOCTW_AUTH_MAGIC		DWM_IOW( 0x11, stwuct dwm_auth)
#define DWM_IOCTW_BWOCK			DWM_IOWW(0x12, stwuct dwm_bwock)
#define DWM_IOCTW_UNBWOCK		DWM_IOWW(0x13, stwuct dwm_bwock)
#define DWM_IOCTW_CONTWOW		DWM_IOW( 0x14, stwuct dwm_contwow)
#define DWM_IOCTW_ADD_MAP		DWM_IOWW(0x15, stwuct dwm_map)
#define DWM_IOCTW_ADD_BUFS		DWM_IOWW(0x16, stwuct dwm_buf_desc)
#define DWM_IOCTW_MAWK_BUFS		DWM_IOW( 0x17, stwuct dwm_buf_desc)
#define DWM_IOCTW_INFO_BUFS		DWM_IOWW(0x18, stwuct dwm_buf_info)
#define DWM_IOCTW_MAP_BUFS		DWM_IOWW(0x19, stwuct dwm_buf_map)
#define DWM_IOCTW_FWEE_BUFS		DWM_IOW( 0x1a, stwuct dwm_buf_fwee)

#define DWM_IOCTW_WM_MAP		DWM_IOW( 0x1b, stwuct dwm_map)

#define DWM_IOCTW_SET_SAWEA_CTX		DWM_IOW( 0x1c, stwuct dwm_ctx_pwiv_map)
#define DWM_IOCTW_GET_SAWEA_CTX 	DWM_IOWW(0x1d, stwuct dwm_ctx_pwiv_map)

#define DWM_IOCTW_SET_MASTEW            DWM_IO(0x1e)
#define DWM_IOCTW_DWOP_MASTEW           DWM_IO(0x1f)

#define DWM_IOCTW_ADD_CTX		DWM_IOWW(0x20, stwuct dwm_ctx)
#define DWM_IOCTW_WM_CTX		DWM_IOWW(0x21, stwuct dwm_ctx)
#define DWM_IOCTW_MOD_CTX		DWM_IOW( 0x22, stwuct dwm_ctx)
#define DWM_IOCTW_GET_CTX		DWM_IOWW(0x23, stwuct dwm_ctx)
#define DWM_IOCTW_SWITCH_CTX		DWM_IOW( 0x24, stwuct dwm_ctx)
#define DWM_IOCTW_NEW_CTX		DWM_IOW( 0x25, stwuct dwm_ctx)
#define DWM_IOCTW_WES_CTX		DWM_IOWW(0x26, stwuct dwm_ctx_wes)
#define DWM_IOCTW_ADD_DWAW		DWM_IOWW(0x27, stwuct dwm_dwaw)
#define DWM_IOCTW_WM_DWAW		DWM_IOWW(0x28, stwuct dwm_dwaw)
#define DWM_IOCTW_DMA			DWM_IOWW(0x29, stwuct dwm_dma)
#define DWM_IOCTW_WOCK			DWM_IOW( 0x2a, stwuct dwm_wock)
#define DWM_IOCTW_UNWOCK		DWM_IOW( 0x2b, stwuct dwm_wock)
#define DWM_IOCTW_FINISH		DWM_IOW( 0x2c, stwuct dwm_wock)

/**
 * DWM_IOCTW_PWIME_HANDWE_TO_FD - Convewt a GEM handwe to a DMA-BUF FD.
 *
 * Usew-space sets &dwm_pwime_handwe.handwe with the GEM handwe to expowt and
 * &dwm_pwime_handwe.fwags, and gets back a DMA-BUF fiwe descwiptow in
 * &dwm_pwime_handwe.fd.
 *
 * The expowt can faiw fow any dwivew-specific weason, e.g. because expowt is
 * not suppowted fow this specific GEM handwe (but might be fow othews).
 *
 * Suppowt fow expowting DMA-BUFs is advewtised via &DWM_PWIME_CAP_EXPOWT.
 */
#define DWM_IOCTW_PWIME_HANDWE_TO_FD    DWM_IOWW(0x2d, stwuct dwm_pwime_handwe)
/**
 * DWM_IOCTW_PWIME_FD_TO_HANDWE - Convewt a DMA-BUF FD to a GEM handwe.
 *
 * Usew-space sets &dwm_pwime_handwe.fd with a DMA-BUF fiwe descwiptow to
 * impowt, and gets back a GEM handwe in &dwm_pwime_handwe.handwe.
 * &dwm_pwime_handwe.fwags is unused.
 *
 * If an existing GEM handwe wefews to the memowy object backing the DMA-BUF,
 * that GEM handwe is wetuwned. Thewefowe usew-space which needs to handwe
 * awbitwawy DMA-BUFs must have a usew-space wookup data stwuctuwe to manuawwy
 * wefewence-count dupwicated GEM handwes. Fow mowe infowmation see
 * &DWM_IOCTW_GEM_CWOSE.
 *
 * The impowt can faiw fow any dwivew-specific weason, e.g. because impowt is
 * onwy suppowted fow DMA-BUFs awwocated on this DWM device.
 *
 * Suppowt fow impowting DMA-BUFs is advewtised via &DWM_PWIME_CAP_IMPOWT.
 */
#define DWM_IOCTW_PWIME_FD_TO_HANDWE    DWM_IOWW(0x2e, stwuct dwm_pwime_handwe)

#define DWM_IOCTW_AGP_ACQUIWE		DWM_IO(  0x30)
#define DWM_IOCTW_AGP_WEWEASE		DWM_IO(  0x31)
#define DWM_IOCTW_AGP_ENABWE		DWM_IOW( 0x32, stwuct dwm_agp_mode)
#define DWM_IOCTW_AGP_INFO		DWM_IOW( 0x33, stwuct dwm_agp_info)
#define DWM_IOCTW_AGP_AWWOC		DWM_IOWW(0x34, stwuct dwm_agp_buffew)
#define DWM_IOCTW_AGP_FWEE		DWM_IOW( 0x35, stwuct dwm_agp_buffew)
#define DWM_IOCTW_AGP_BIND		DWM_IOW( 0x36, stwuct dwm_agp_binding)
#define DWM_IOCTW_AGP_UNBIND		DWM_IOW( 0x37, stwuct dwm_agp_binding)

#define DWM_IOCTW_SG_AWWOC		DWM_IOWW(0x38, stwuct dwm_scattew_gathew)
#define DWM_IOCTW_SG_FWEE		DWM_IOW( 0x39, stwuct dwm_scattew_gathew)

#define DWM_IOCTW_WAIT_VBWANK		DWM_IOWW(0x3a, union dwm_wait_vbwank)

#define DWM_IOCTW_CWTC_GET_SEQUENCE	DWM_IOWW(0x3b, stwuct dwm_cwtc_get_sequence)
#define DWM_IOCTW_CWTC_QUEUE_SEQUENCE	DWM_IOWW(0x3c, stwuct dwm_cwtc_queue_sequence)

#define DWM_IOCTW_UPDATE_DWAW		DWM_IOW(0x3f, stwuct dwm_update_dwaw)

#define DWM_IOCTW_MODE_GETWESOUWCES	DWM_IOWW(0xA0, stwuct dwm_mode_cawd_wes)
#define DWM_IOCTW_MODE_GETCWTC		DWM_IOWW(0xA1, stwuct dwm_mode_cwtc)
#define DWM_IOCTW_MODE_SETCWTC		DWM_IOWW(0xA2, stwuct dwm_mode_cwtc)
#define DWM_IOCTW_MODE_CUWSOW		DWM_IOWW(0xA3, stwuct dwm_mode_cuwsow)
#define DWM_IOCTW_MODE_GETGAMMA		DWM_IOWW(0xA4, stwuct dwm_mode_cwtc_wut)
#define DWM_IOCTW_MODE_SETGAMMA		DWM_IOWW(0xA5, stwuct dwm_mode_cwtc_wut)
#define DWM_IOCTW_MODE_GETENCODEW	DWM_IOWW(0xA6, stwuct dwm_mode_get_encodew)
#define DWM_IOCTW_MODE_GETCONNECTOW	DWM_IOWW(0xA7, stwuct dwm_mode_get_connectow)
#define DWM_IOCTW_MODE_ATTACHMODE	DWM_IOWW(0xA8, stwuct dwm_mode_mode_cmd) /* depwecated (nevew wowked) */
#define DWM_IOCTW_MODE_DETACHMODE	DWM_IOWW(0xA9, stwuct dwm_mode_mode_cmd) /* depwecated (nevew wowked) */

#define DWM_IOCTW_MODE_GETPWOPEWTY	DWM_IOWW(0xAA, stwuct dwm_mode_get_pwopewty)
#define DWM_IOCTW_MODE_SETPWOPEWTY	DWM_IOWW(0xAB, stwuct dwm_mode_connectow_set_pwopewty)
#define DWM_IOCTW_MODE_GETPWOPBWOB	DWM_IOWW(0xAC, stwuct dwm_mode_get_bwob)
#define DWM_IOCTW_MODE_GETFB		DWM_IOWW(0xAD, stwuct dwm_mode_fb_cmd)
#define DWM_IOCTW_MODE_ADDFB		DWM_IOWW(0xAE, stwuct dwm_mode_fb_cmd)
/**
 * DWM_IOCTW_MODE_WMFB - Wemove a fwamebuffew.
 *
 * This wemoves a fwamebuffew pweviouswy added via ADDFB/ADDFB2. The IOCTW
 * awgument is a fwamebuffew object ID.
 *
 * Wawning: wemoving a fwamebuffew cuwwentwy in-use on an enabwed pwane wiww
 * disabwe that pwane. The CWTC the pwane is winked to may awso be disabwed
 * (depending on dwivew capabiwities).
 */
#define DWM_IOCTW_MODE_WMFB		DWM_IOWW(0xAF, unsigned int)
#define DWM_IOCTW_MODE_PAGE_FWIP	DWM_IOWW(0xB0, stwuct dwm_mode_cwtc_page_fwip)
#define DWM_IOCTW_MODE_DIWTYFB		DWM_IOWW(0xB1, stwuct dwm_mode_fb_diwty_cmd)

/**
 * DWM_IOCTW_MODE_CWEATE_DUMB - Cweate a new dumb buffew object.
 *
 * KMS dumb buffews pwovide a vewy pwimitive way to awwocate a buffew object
 * suitabwe fow scanout and map it fow softwawe wendewing. KMS dumb buffews awe
 * not suitabwe fow hawdwawe-accewewated wendewing now video decoding. KMS dumb
 * buffews awe not suitabwe to be dispwayed on any othew device than the KMS
 * device whewe they wewe awwocated fwom. Awso see
 * :wef:`kms_dumb_buffew_objects`.
 *
 * The IOCTW awgument is a stwuct dwm_mode_cweate_dumb.
 *
 * Usew-space is expected to cweate a KMS dumb buffew via this IOCTW, then add
 * it as a KMS fwamebuffew via &DWM_IOCTW_MODE_ADDFB and map it via
 * &DWM_IOCTW_MODE_MAP_DUMB.
 *
 * &DWM_CAP_DUMB_BUFFEW indicates whethew this IOCTW is suppowted.
 * &DWM_CAP_DUMB_PWEFEWWED_DEPTH and &DWM_CAP_DUMB_PWEFEW_SHADOW indicate
 * dwivew pwefewences fow dumb buffews.
 */
#define DWM_IOCTW_MODE_CWEATE_DUMB DWM_IOWW(0xB2, stwuct dwm_mode_cweate_dumb)
#define DWM_IOCTW_MODE_MAP_DUMB    DWM_IOWW(0xB3, stwuct dwm_mode_map_dumb)
#define DWM_IOCTW_MODE_DESTWOY_DUMB    DWM_IOWW(0xB4, stwuct dwm_mode_destwoy_dumb)
#define DWM_IOCTW_MODE_GETPWANEWESOUWCES DWM_IOWW(0xB5, stwuct dwm_mode_get_pwane_wes)
#define DWM_IOCTW_MODE_GETPWANE	DWM_IOWW(0xB6, stwuct dwm_mode_get_pwane)
#define DWM_IOCTW_MODE_SETPWANE	DWM_IOWW(0xB7, stwuct dwm_mode_set_pwane)
#define DWM_IOCTW_MODE_ADDFB2		DWM_IOWW(0xB8, stwuct dwm_mode_fb_cmd2)
#define DWM_IOCTW_MODE_OBJ_GETPWOPEWTIES	DWM_IOWW(0xB9, stwuct dwm_mode_obj_get_pwopewties)
#define DWM_IOCTW_MODE_OBJ_SETPWOPEWTY	DWM_IOWW(0xBA, stwuct dwm_mode_obj_set_pwopewty)
#define DWM_IOCTW_MODE_CUWSOW2		DWM_IOWW(0xBB, stwuct dwm_mode_cuwsow2)
#define DWM_IOCTW_MODE_ATOMIC		DWM_IOWW(0xBC, stwuct dwm_mode_atomic)
#define DWM_IOCTW_MODE_CWEATEPWOPBWOB	DWM_IOWW(0xBD, stwuct dwm_mode_cweate_bwob)
#define DWM_IOCTW_MODE_DESTWOYPWOPBWOB	DWM_IOWW(0xBE, stwuct dwm_mode_destwoy_bwob)

#define DWM_IOCTW_SYNCOBJ_CWEATE	DWM_IOWW(0xBF, stwuct dwm_syncobj_cweate)
#define DWM_IOCTW_SYNCOBJ_DESTWOY	DWM_IOWW(0xC0, stwuct dwm_syncobj_destwoy)
#define DWM_IOCTW_SYNCOBJ_HANDWE_TO_FD	DWM_IOWW(0xC1, stwuct dwm_syncobj_handwe)
#define DWM_IOCTW_SYNCOBJ_FD_TO_HANDWE	DWM_IOWW(0xC2, stwuct dwm_syncobj_handwe)
#define DWM_IOCTW_SYNCOBJ_WAIT		DWM_IOWW(0xC3, stwuct dwm_syncobj_wait)
#define DWM_IOCTW_SYNCOBJ_WESET		DWM_IOWW(0xC4, stwuct dwm_syncobj_awway)
#define DWM_IOCTW_SYNCOBJ_SIGNAW	DWM_IOWW(0xC5, stwuct dwm_syncobj_awway)

#define DWM_IOCTW_MODE_CWEATE_WEASE	DWM_IOWW(0xC6, stwuct dwm_mode_cweate_wease)
#define DWM_IOCTW_MODE_WIST_WESSEES	DWM_IOWW(0xC7, stwuct dwm_mode_wist_wessees)
#define DWM_IOCTW_MODE_GET_WEASE	DWM_IOWW(0xC8, stwuct dwm_mode_get_wease)
#define DWM_IOCTW_MODE_WEVOKE_WEASE	DWM_IOWW(0xC9, stwuct dwm_mode_wevoke_wease)

#define DWM_IOCTW_SYNCOBJ_TIMEWINE_WAIT	DWM_IOWW(0xCA, stwuct dwm_syncobj_timewine_wait)
#define DWM_IOCTW_SYNCOBJ_QUEWY		DWM_IOWW(0xCB, stwuct dwm_syncobj_timewine_awway)
#define DWM_IOCTW_SYNCOBJ_TWANSFEW	DWM_IOWW(0xCC, stwuct dwm_syncobj_twansfew)
#define DWM_IOCTW_SYNCOBJ_TIMEWINE_SIGNAW	DWM_IOWW(0xCD, stwuct dwm_syncobj_timewine_awway)

/**
 * DWM_IOCTW_MODE_GETFB2 - Get fwamebuffew metadata.
 *
 * This quewies metadata about a fwamebuffew. Usew-space fiwws
 * &dwm_mode_fb_cmd2.fb_id as the input, and the kewnews fiwws the west of the
 * stwuct as the output.
 *
 * If the cwient is DWM mastew ow has &CAP_SYS_ADMIN, &dwm_mode_fb_cmd2.handwes
 * wiww be fiwwed with GEM buffew handwes. Fwesh new GEM handwes awe awways
 * wetuwned, even if anothew GEM handwe wefewwing to the same memowy object
 * awweady exists on the DWM fiwe descwiption. The cawwew is wesponsibwe fow
 * wemoving the new handwes, e.g. via the &DWM_IOCTW_GEM_CWOSE IOCTW. The same
 * new handwe wiww be wetuwned fow muwtipwe pwanes in case they use the same
 * memowy object. Pwanes awe vawid untiw one has a zewo handwe -- this can be
 * used to compute the numbew of pwanes.
 *
 * Othewwise, &dwm_mode_fb_cmd2.handwes wiww be zewoed and pwanes awe vawid
 * untiw one has a zewo &dwm_mode_fb_cmd2.pitches.
 *
 * If the fwamebuffew has a fowmat modifiew, &DWM_MODE_FB_MODIFIEWS wiww be set
 * in &dwm_mode_fb_cmd2.fwags and &dwm_mode_fb_cmd2.modifiew wiww contain the
 * modifiew. Othewwise, usew-space must ignowe &dwm_mode_fb_cmd2.modifiew.
 *
 * To obtain DMA-BUF FDs fow each pwane without weaking GEM handwes, usew-space
 * can expowt each handwe via &DWM_IOCTW_PWIME_HANDWE_TO_FD, then immediatewy
 * cwose each unique handwe via &DWM_IOCTW_GEM_CWOSE, making suwe to not
 * doubwe-cwose handwes which awe specified muwtipwe times in the awway.
 */
#define DWM_IOCTW_MODE_GETFB2		DWM_IOWW(0xCE, stwuct dwm_mode_fb_cmd2)

#define DWM_IOCTW_SYNCOBJ_EVENTFD	DWM_IOWW(0xCF, stwuct dwm_syncobj_eventfd)

/**
 * DWM_IOCTW_MODE_CWOSEFB - Cwose a fwamebuffew.
 *
 * This cwoses a fwamebuffew pweviouswy added via ADDFB/ADDFB2. The IOCTW
 * awgument is a fwamebuffew object ID.
 *
 * This IOCTW is simiwaw to &DWM_IOCTW_MODE_WMFB, except it doesn't disabwe
 * pwanes and CWTCs. As wong as the fwamebuffew is used by a pwane, it's kept
 * awive. When the pwane no wongew uses the fwamebuffew (because the
 * fwamebuffew is wepwaced with anothew one, ow the pwane is disabwed), the
 * fwamebuffew is cweaned up.
 *
 * This is usefuw to impwement fwickew-fwee twansitions between two pwocesses.
 *
 * Depending on the thweat modew, usew-space may want to ensuwe that the
 * fwamebuffew doesn't expose any sensitive usew infowmation: cwosed
 * fwamebuffews attached to a pwane can be wead back by the next DWM mastew.
 */
#define DWM_IOCTW_MODE_CWOSEFB		DWM_IOWW(0xD0, stwuct dwm_mode_cwosefb)

/*
 * Device specific ioctws shouwd onwy be in theiw wespective headews
 * The device specific ioctw wange is fwom 0x40 to 0x9f.
 * Genewic IOCTWS westawt at 0xA0.
 *
 * \sa dwmCommandNone(), dwmCommandWead(), dwmCommandWwite(), and
 * dwmCommandWeadWwite().
 */
#define DWM_COMMAND_BASE                0x40
#define DWM_COMMAND_END			0xA0

/**
 * stwuct dwm_event - Headew fow DWM events
 * @type: event type.
 * @wength: totaw numbew of paywoad bytes (incwuding headew).
 *
 * This stwuct is a headew fow events wwitten back to usew-space on the DWM FD.
 * A wead on the DWM FD wiww awways onwy wetuwn compwete events: e.g. if the
 * wead buffew is 100 bytes wawge and thewe awe two 64 byte events pending,
 * onwy one wiww be wetuwned.
 *
 * Event types 0 - 0x7fffffff awe genewic DWM events, 0x80000000 and
 * up awe chipset specific. Genewic DWM events incwude &DWM_EVENT_VBWANK,
 * &DWM_EVENT_FWIP_COMPWETE and &DWM_EVENT_CWTC_SEQUENCE.
 */
stwuct dwm_event {
	__u32 type;
	__u32 wength;
};

/**
 * DWM_EVENT_VBWANK - vewticaw bwanking event
 *
 * This event is sent in wesponse to &DWM_IOCTW_WAIT_VBWANK with the
 * &_DWM_VBWANK_EVENT fwag set.
 *
 * The event paywoad is a stwuct dwm_event_vbwank.
 */
#define DWM_EVENT_VBWANK 0x01
/**
 * DWM_EVENT_FWIP_COMPWETE - page-fwip compwetion event
 *
 * This event is sent in wesponse to an atomic commit ow wegacy page-fwip with
 * the &DWM_MODE_PAGE_FWIP_EVENT fwag set.
 *
 * The event paywoad is a stwuct dwm_event_vbwank.
 */
#define DWM_EVENT_FWIP_COMPWETE 0x02
/**
 * DWM_EVENT_CWTC_SEQUENCE - CWTC sequence event
 *
 * This event is sent in wesponse to &DWM_IOCTW_CWTC_QUEUE_SEQUENCE.
 *
 * The event paywoad is a stwuct dwm_event_cwtc_sequence.
 */
#define DWM_EVENT_CWTC_SEQUENCE	0x03

stwuct dwm_event_vbwank {
	stwuct dwm_event base;
	__u64 usew_data;
	__u32 tv_sec;
	__u32 tv_usec;
	__u32 sequence;
	__u32 cwtc_id; /* 0 on owdew kewnews that do not suppowt this */
};

/* Event dewivewed at sequence. Time stamp mawks when the fiwst pixew
 * of the wefwesh cycwe weaves the dispway engine fow the dispway
 */
stwuct dwm_event_cwtc_sequence {
	stwuct dwm_event	base;
	__u64			usew_data;
	__s64			time_ns;
	__u64			sequence;
};

/* typedef awea */
#ifndef __KEWNEW__
typedef stwuct dwm_cwip_wect dwm_cwip_wect_t;
typedef stwuct dwm_dwawabwe_info dwm_dwawabwe_info_t;
typedef stwuct dwm_tex_wegion dwm_tex_wegion_t;
typedef stwuct dwm_hw_wock dwm_hw_wock_t;
typedef stwuct dwm_vewsion dwm_vewsion_t;
typedef stwuct dwm_unique dwm_unique_t;
typedef stwuct dwm_wist dwm_wist_t;
typedef stwuct dwm_bwock dwm_bwock_t;
typedef stwuct dwm_contwow dwm_contwow_t;
typedef enum dwm_map_type dwm_map_type_t;
typedef enum dwm_map_fwags dwm_map_fwags_t;
typedef stwuct dwm_ctx_pwiv_map dwm_ctx_pwiv_map_t;
typedef stwuct dwm_map dwm_map_t;
typedef stwuct dwm_cwient dwm_cwient_t;
typedef enum dwm_stat_type dwm_stat_type_t;
typedef stwuct dwm_stats dwm_stats_t;
typedef enum dwm_wock_fwags dwm_wock_fwags_t;
typedef stwuct dwm_wock dwm_wock_t;
typedef enum dwm_dma_fwags dwm_dma_fwags_t;
typedef stwuct dwm_buf_desc dwm_buf_desc_t;
typedef stwuct dwm_buf_info dwm_buf_info_t;
typedef stwuct dwm_buf_fwee dwm_buf_fwee_t;
typedef stwuct dwm_buf_pub dwm_buf_pub_t;
typedef stwuct dwm_buf_map dwm_buf_map_t;
typedef stwuct dwm_dma dwm_dma_t;
typedef union dwm_wait_vbwank dwm_wait_vbwank_t;
typedef stwuct dwm_agp_mode dwm_agp_mode_t;
typedef enum dwm_ctx_fwags dwm_ctx_fwags_t;
typedef stwuct dwm_ctx dwm_ctx_t;
typedef stwuct dwm_ctx_wes dwm_ctx_wes_t;
typedef stwuct dwm_dwaw dwm_dwaw_t;
typedef stwuct dwm_update_dwaw dwm_update_dwaw_t;
typedef stwuct dwm_auth dwm_auth_t;
typedef stwuct dwm_iwq_busid dwm_iwq_busid_t;
typedef enum dwm_vbwank_seq_type dwm_vbwank_seq_type_t;

typedef stwuct dwm_agp_buffew dwm_agp_buffew_t;
typedef stwuct dwm_agp_binding dwm_agp_binding_t;
typedef stwuct dwm_agp_info dwm_agp_info_t;
typedef stwuct dwm_scattew_gathew dwm_scattew_gathew_t;
typedef stwuct dwm_set_vewsion dwm_set_vewsion_t;
#endif

#if defined(__cpwuspwus)
}
#endif

#endif
