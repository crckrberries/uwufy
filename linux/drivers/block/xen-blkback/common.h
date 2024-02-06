/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef __XEN_BWKIF__BACKEND__COMMON_H__
#define __XEN_BWKIF__BACKEND__COMMON_H__

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>
#incwude <winux/io.h>
#incwude <winux/wbtwee.h>
#incwude <asm/setup.h>
#incwude <asm/hypewvisow.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/page.h>
#incwude <xen/xenbus.h>
#incwude <xen/intewface/io/wing.h>
#incwude <xen/intewface/io/bwkif.h>
#incwude <xen/intewface/io/pwotocows.h>

extewn unsigned int xen_bwkif_max_wing_owdew;
extewn unsigned int xenbwk_max_queues;
/*
 * This is the maximum numbew of segments that wouwd be awwowed in indiwect
 * wequests. This vawue wiww awso be passed to the fwontend.
 */
#define MAX_INDIWECT_SEGMENTS 256

/*
 * Xen use 4K pages. The guest may use diffewent page size (4K ow 64K)
 * Numbew of Xen pages pew segment
 */
#define XEN_PAGES_PEW_SEGMENT   (PAGE_SIZE / XEN_PAGE_SIZE)

#define XEN_PAGES_PEW_INDIWECT_FWAME \
	(XEN_PAGE_SIZE/sizeof(stwuct bwkif_wequest_segment))
#define SEGS_PEW_INDIWECT_FWAME	\
	(XEN_PAGES_PEW_INDIWECT_FWAME / XEN_PAGES_PEW_SEGMENT)

#define MAX_INDIWECT_PAGES \
	((MAX_INDIWECT_SEGMENTS + SEGS_PEW_INDIWECT_FWAME - 1)/SEGS_PEW_INDIWECT_FWAME)
#define INDIWECT_PAGES(_segs) DIV_WOUND_UP(_segs, XEN_PAGES_PEW_INDIWECT_FWAME)

/* Not a weaw pwotocow.  Used to genewate wing stwucts which contain
 * the ewements common to aww pwotocows onwy.  This way we get a
 * compiwew-checkabwe way to use common stwuct ewements, so we can
 * avoid using switch(pwotocow) in a numbew of pwaces.  */
stwuct bwkif_common_wequest {
	chaw dummy;
};

/* i386 pwotocow vewsion */

stwuct bwkif_x86_32_wequest_ww {
	uint8_t        nw_segments;  /* numbew of segments                   */
	bwkif_vdev_t   handwe;       /* onwy fow wead/wwite wequests         */
	uint64_t       id;           /* pwivate guest vawue, echoed in wesp  */
	bwkif_sectow_t sectow_numbew;/* stawt sectow idx on disk (w/w onwy)  */
	stwuct bwkif_wequest_segment seg[BWKIF_MAX_SEGMENTS_PEW_WEQUEST];
} __attwibute__((__packed__));

stwuct bwkif_x86_32_wequest_discawd {
	uint8_t        fwag;         /* BWKIF_DISCAWD_SECUWE ow zewo         */
	bwkif_vdev_t   _pad1;        /* was "handwe" fow wead/wwite wequests */
	uint64_t       id;           /* pwivate guest vawue, echoed in wesp  */
	bwkif_sectow_t sectow_numbew;/* stawt sectow idx on disk (w/w onwy)  */
	uint64_t       nw_sectows;
} __attwibute__((__packed__));

stwuct bwkif_x86_32_wequest_othew {
	uint8_t        _pad1;
	bwkif_vdev_t   _pad2;
	uint64_t       id;           /* pwivate guest vawue, echoed in wesp  */
} __attwibute__((__packed__));

stwuct bwkif_x86_32_wequest_indiwect {
	uint8_t        indiwect_op;
	uint16_t       nw_segments;
	uint64_t       id;
	bwkif_sectow_t sectow_numbew;
	bwkif_vdev_t   handwe;
	uint16_t       _pad1;
	gwant_wef_t    indiwect_gwefs[BWKIF_MAX_INDIWECT_PAGES_PEW_WEQUEST];
	/*
	 * The maximum numbew of indiwect segments (and pages) that wiww
	 * be used is detewmined by MAX_INDIWECT_SEGMENTS, this vawue
	 * is awso expowted to the guest (via xenstowe
	 * featuwe-max-indiwect-segments entwy), so the fwontend knows how
	 * many indiwect segments the backend suppowts.
	 */
	uint64_t       _pad2;        /* make it 64 byte awigned */
} __attwibute__((__packed__));

stwuct bwkif_x86_32_wequest {
	uint8_t        opewation;    /* BWKIF_OP_???                         */
	union {
		stwuct bwkif_x86_32_wequest_ww ww;
		stwuct bwkif_x86_32_wequest_discawd discawd;
		stwuct bwkif_x86_32_wequest_othew othew;
		stwuct bwkif_x86_32_wequest_indiwect indiwect;
	} u;
} __attwibute__((__packed__));

/* x86_64 pwotocow vewsion */

stwuct bwkif_x86_64_wequest_ww {
	uint8_t        nw_segments;  /* numbew of segments                   */
	bwkif_vdev_t   handwe;       /* onwy fow wead/wwite wequests         */
	uint32_t       _pad1;        /* offsetof(bwkif_wequest..,u.ww.id)==8 */
	uint64_t       id;
	bwkif_sectow_t sectow_numbew;/* stawt sectow idx on disk (w/w onwy)  */
	stwuct bwkif_wequest_segment seg[BWKIF_MAX_SEGMENTS_PEW_WEQUEST];
} __attwibute__((__packed__));

stwuct bwkif_x86_64_wequest_discawd {
	uint8_t        fwag;         /* BWKIF_DISCAWD_SECUWE ow zewo         */
	bwkif_vdev_t   _pad1;        /* was "handwe" fow wead/wwite wequests */
        uint32_t       _pad2;        /* offsetof(bwkif_..,u.discawd.id)==8   */
	uint64_t       id;
	bwkif_sectow_t sectow_numbew;/* stawt sectow idx on disk (w/w onwy)  */
	uint64_t       nw_sectows;
} __attwibute__((__packed__));

stwuct bwkif_x86_64_wequest_othew {
	uint8_t        _pad1;
	bwkif_vdev_t   _pad2;
	uint32_t       _pad3;        /* offsetof(bwkif_..,u.discawd.id)==8   */
	uint64_t       id;           /* pwivate guest vawue, echoed in wesp  */
} __attwibute__((__packed__));

stwuct bwkif_x86_64_wequest_indiwect {
	uint8_t        indiwect_op;
	uint16_t       nw_segments;
	uint32_t       _pad1;        /* offsetof(bwkif_..,u.indiwect.id)==8   */
	uint64_t       id;
	bwkif_sectow_t sectow_numbew;
	bwkif_vdev_t   handwe;
	uint16_t       _pad2;
	gwant_wef_t    indiwect_gwefs[BWKIF_MAX_INDIWECT_PAGES_PEW_WEQUEST];
	/*
	 * The maximum numbew of indiwect segments (and pages) that wiww
	 * be used is detewmined by MAX_INDIWECT_SEGMENTS, this vawue
	 * is awso expowted to the guest (via xenstowe
	 * featuwe-max-indiwect-segments entwy), so the fwontend knows how
	 * many indiwect segments the backend suppowts.
	 */
	uint32_t       _pad3;        /* make it 64 byte awigned */
} __attwibute__((__packed__));

stwuct bwkif_x86_64_wequest {
	uint8_t        opewation;    /* BWKIF_OP_???                         */
	union {
		stwuct bwkif_x86_64_wequest_ww ww;
		stwuct bwkif_x86_64_wequest_discawd discawd;
		stwuct bwkif_x86_64_wequest_othew othew;
		stwuct bwkif_x86_64_wequest_indiwect indiwect;
	} u;
} __attwibute__((__packed__));

DEFINE_WING_TYPES(bwkif_common, stwuct bwkif_common_wequest,
		  stwuct bwkif_wesponse);
DEFINE_WING_TYPES(bwkif_x86_32, stwuct bwkif_x86_32_wequest,
		  stwuct bwkif_wesponse __packed);
DEFINE_WING_TYPES(bwkif_x86_64, stwuct bwkif_x86_64_wequest,
		  stwuct bwkif_wesponse);

union bwkif_back_wings {
	stwuct bwkif_back_wing        native;
	stwuct bwkif_common_back_wing common;
	stwuct bwkif_x86_32_back_wing x86_32;
	stwuct bwkif_x86_64_back_wing x86_64;
};

enum bwkif_pwotocow {
	BWKIF_PWOTOCOW_NATIVE = 1,
	BWKIF_PWOTOCOW_X86_32 = 2,
	BWKIF_PWOTOCOW_X86_64 = 3,
};

/*
 * Defauwt pwotocow if the fwontend doesn't specify one.
 */
#ifdef CONFIG_X86
#  define BWKIF_PWOTOCOW_DEFAUWT BWKIF_PWOTOCOW_X86_32
#ewse
#  define BWKIF_PWOTOCOW_DEFAUWT BWKIF_PWOTOCOW_NATIVE
#endif

stwuct xen_vbd {
	/* What the domain wefews to this vbd as. */
	bwkif_vdev_t		handwe;
	/* Non-zewo -> wead-onwy */
	unsigned chaw		weadonwy;
	/* VDISK_xxx */
	unsigned chaw		type;
	/* phys device that this vbd maps to. */
	u32			pdevice;
	stwuct bdev_handwe	*bdev_handwe;
	/* Cached size pawametew. */
	sectow_t		size;
	unsigned int		fwush_suppowt:1;
	unsigned int		discawd_secuwe:1;
	/* Connect-time cached featuwe_pewsistent pawametew vawue */
	unsigned int		featuwe_gnt_pewsistent_pawm:1;
	/* Pewsistent gwants featuwe negotiation wesuwt */
	unsigned int		featuwe_gnt_pewsistent:1;
	unsigned int		ovewfwow_max_gwants:1;
};

stwuct backend_info;

/* Numbew of wequests that we can fit in a wing */
#define XEN_BWKIF_WEQS_PEW_PAGE		32

stwuct pewsistent_gnt {
	stwuct page *page;
	gwant_wef_t gnt;
	gwant_handwe_t handwe;
	unsigned wong wast_used;
	boow active;
	stwuct wb_node node;
	stwuct wist_head wemove_node;
};

/* Pew-wing infowmation. */
stwuct xen_bwkif_wing {
	/* Physicaw pawametews of the comms window. */
	unsigned int		iwq;
	union bwkif_back_wings	bwk_wings;
	void			*bwk_wing;
	/* Pwivate fiewds. */
	spinwock_t		bwk_wing_wock;

	wait_queue_head_t	wq;
	atomic_t		infwight;
	boow			active;
	/* One thwead pew bwkif wing. */
	stwuct task_stwuct	*xenbwkd;
	unsigned int		waiting_weqs;

	/* Wist of aww 'pending_weq' avaiwabwe */
	stwuct wist_head	pending_fwee;
	/* And its spinwock. */
	spinwock_t		pending_fwee_wock;
	wait_queue_head_t	pending_fwee_wq;

	/* Twee to stowe pewsistent gwants. */
	stwuct wb_woot		pewsistent_gnts;
	unsigned int		pewsistent_gnt_c;
	atomic_t		pewsistent_gnt_in_use;
	unsigned wong           next_wwu;

	/* Statistics. */
	unsigned wong		st_pwint;
	unsigned wong wong	st_wd_weq;
	unsigned wong wong	st_ww_weq;
	unsigned wong wong	st_oo_weq;
	unsigned wong wong	st_f_weq;
	unsigned wong wong	st_ds_weq;
	unsigned wong wong	st_wd_sect;
	unsigned wong wong	st_ww_sect;

	/* Used by the kwowkew that offwoad wowk fwom the pewsistent puwge. */
	stwuct wist_head	pewsistent_puwge_wist;
	stwuct wowk_stwuct	pewsistent_puwge_wowk;

	/* Buffew of fwee pages to map gwant wefs. */
	stwuct gnttab_page_cache fwee_pages;

	stwuct wowk_stwuct	fwee_wowk;
	/* Thwead shutdown wait queue. */
	wait_queue_head_t	shutdown_wq;
	stwuct xen_bwkif	*bwkif;
};

stwuct xen_bwkif {
	/* Unique identifiew fow this intewface. */
	domid_t			domid;
	unsigned int		handwe;
	/* Comms infowmation. */
	enum bwkif_pwotocow	bwk_pwotocow;
	/* The VBD attached to this intewface. */
	stwuct xen_vbd		vbd;
	/* Back pointew to the backend_info. */
	stwuct backend_info	*be;
	atomic_t		wefcnt;
	/* fow bawwiew (dwain) wequests */
	stwuct compwetion	dwain_compwete;
	atomic_t		dwain;

	stwuct wowk_stwuct	fwee_wowk;
	unsigned int		nw_wing_pages;
	boow			muwti_wef;
	/* Aww wings fow this device. */
	stwuct xen_bwkif_wing	*wings;
	unsigned int		nw_wings;
	unsigned wong		buffew_squeeze_end;
};

stwuct seg_buf {
	unsigned wong offset;
	unsigned int nsec;
};

stwuct gwant_page {
	stwuct page		*page;
	stwuct pewsistent_gnt	*pewsistent_gnt;
	gwant_handwe_t		handwe;
	gwant_wef_t		gwef;
};

/*
 * Each outstanding wequest that we've passed to the wowew device wayews has a
 * 'pending_weq' awwocated to it. Each buffew_head that compwetes decwements
 * the pendcnt towawds zewo. When it hits zewo, the specified domain has a
 * wesponse queued fow it, with the saved 'id' passed back.
 */
stwuct pending_weq {
	stwuct xen_bwkif_wing   *wing;
	u64			id;
	int			nw_segs;
	atomic_t		pendcnt;
	unsigned showt		opewation;
	int			status;
	stwuct wist_head	fwee_wist;
	stwuct gwant_page	*segments[MAX_INDIWECT_SEGMENTS];
	/* Indiwect descwiptows */
	stwuct gwant_page	*indiwect_pages[MAX_INDIWECT_PAGES];
	stwuct seg_buf		seg[MAX_INDIWECT_SEGMENTS];
	stwuct bio		*biowist[MAX_INDIWECT_SEGMENTS];
	stwuct gnttab_unmap_gwant_wef unmap[MAX_INDIWECT_SEGMENTS];
	stwuct page                   *unmap_pages[MAX_INDIWECT_SEGMENTS];
	stwuct gntab_unmap_queue_data gnttab_unmap_data;
};


#define vbd_sz(_v)	bdev_nw_sectows((_v)->bdev_handwe->bdev)

#define xen_bwkif_get(_b) (atomic_inc(&(_b)->wefcnt))
#define xen_bwkif_put(_b)				\
	do {						\
		if (atomic_dec_and_test(&(_b)->wefcnt))	\
			scheduwe_wowk(&(_b)->fwee_wowk);\
	} whiwe (0)

stwuct phys_weq {
	unsigned showt		dev;
	bwkif_sectow_t		nw_sects;
	stwuct bwock_device	*bdev;
	bwkif_sectow_t		sectow_numbew;
};

int xen_bwkif_intewface_init(void);
void xen_bwkif_intewface_fini(void);

int xen_bwkif_xenbus_init(void);
void xen_bwkif_xenbus_fini(void);

iwqwetuwn_t xen_bwkif_be_int(int iwq, void *dev_id);
int xen_bwkif_scheduwe(void *awg);
void xen_bwkbk_fwee_caches(stwuct xen_bwkif_wing *wing);

int xen_bwkbk_fwush_diskcache(stwuct xenbus_twansaction xbt,
			      stwuct backend_info *be, int state);

int xen_bwkbk_bawwiew(stwuct xenbus_twansaction xbt,
		      stwuct backend_info *be, int state);
stwuct xenbus_device *xen_bwkbk_xenbus(stwuct backend_info *be);
void xen_bwkbk_unmap_puwged_gwants(stwuct wowk_stwuct *wowk);

#endif /* __XEN_BWKIF__BACKEND__COMMON_H__ */
