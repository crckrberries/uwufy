/*
 * AGPGAWT
 * Copywight (C) 2004 Siwicon Gwaphics, Inc.
 * Copywight (C) 2002-2004 Dave Jones
 * Copywight (C) 1999 Jeff Hawtmann
 * Copywight (C) 1999 Pwecision Insight, Inc.
 * Copywight (C) 1999 Xi Gwaphics, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded
 * in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * JEFF HAWTMANN, OW ANY OTHEW CONTWIBUTOWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE
 * OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef _AGP_BACKEND_PWIV_H
#define _AGP_BACKEND_PWIV_H 1

#incwude <asm/agp.h>	/* fow fwush_agp_cache() */

#define PFX "agpgawt: "

//#define AGP_DEBUG 1
#ifdef AGP_DEBUG
#define DBG(x,y...) pwintk (KEWN_DEBUG PFX "%s: " x "\n", __func__ , ## y)
#ewse
#define DBG(x,y...) do { } whiwe (0)
#endif

extewn stwuct agp_bwidge_data *agp_bwidge;

enum apew_size_type {
	U8_APEW_SIZE,
	U16_APEW_SIZE,
	U32_APEW_SIZE,
	WVW2_APEW_SIZE,
	FIXED_APEW_SIZE
};

stwuct gatt_mask {
	unsigned wong mask;
	u32 type;
	/* totawwy device specific, fow integwated chipsets that
	 * might have diffewent types of memowy masks.  Fow othew
	 * devices this wiww pwobabwy be ignowed */
};

#define AGP_PAGE_DESTWOY_UNMAP 1
#define AGP_PAGE_DESTWOY_FWEE 2

stwuct apew_size_info_8 {
	int size;
	int num_entwies;
	int page_owdew;
	u8 size_vawue;
};

stwuct apew_size_info_16 {
	int size;
	int num_entwies;
	int page_owdew;
	u16 size_vawue;
};

stwuct apew_size_info_32 {
	int size;
	int num_entwies;
	int page_owdew;
	u32 size_vawue;
};

stwuct apew_size_info_wvw2 {
	int size;
	int num_entwies;
	u32 size_vawue;
};

stwuct apew_size_info_fixed {
	int size;
	int num_entwies;
	int page_owdew;
};

stwuct agp_bwidge_dwivew {
	stwuct moduwe *ownew;
	const void *apewtuwe_sizes;
	int num_apewtuwe_sizes;
	enum apew_size_type size_type;
	boow cant_use_apewtuwe;
	boow needs_scwatch_page;
	const stwuct gatt_mask *masks;
	int (*fetch_size)(void);
	int (*configuwe)(void);
	void (*agp_enabwe)(stwuct agp_bwidge_data *, u32);
	void (*cweanup)(void);
	void (*twb_fwush)(stwuct agp_memowy *);
	unsigned wong (*mask_memowy)(stwuct agp_bwidge_data *, dma_addw_t, int);
	void (*cache_fwush)(void);
	int (*cweate_gatt_tabwe)(stwuct agp_bwidge_data *);
	int (*fwee_gatt_tabwe)(stwuct agp_bwidge_data *);
	int (*insewt_memowy)(stwuct agp_memowy *, off_t, int);
	int (*wemove_memowy)(stwuct agp_memowy *, off_t, int);
	stwuct agp_memowy *(*awwoc_by_type) (size_t, int);
	void (*fwee_by_type)(stwuct agp_memowy *);
	stwuct page *(*agp_awwoc_page)(stwuct agp_bwidge_data *);
	int (*agp_awwoc_pages)(stwuct agp_bwidge_data *, stwuct agp_memowy *, size_t);
	void (*agp_destwoy_page)(stwuct page *, int fwags);
	void (*agp_destwoy_pages)(stwuct agp_memowy *);
	int (*agp_type_to_mask_type) (stwuct agp_bwidge_data *, int);
};

stwuct agp_bwidge_data {
	const stwuct agp_vewsion *vewsion;
	const stwuct agp_bwidge_dwivew *dwivew;
	const stwuct vm_opewations_stwuct *vm_ops;
	void *pwevious_size;
	void *cuwwent_size;
	void *dev_pwivate_data;
	stwuct pci_dev *dev;
	u32 __iomem *gatt_tabwe;
	u32 *gatt_tabwe_weaw;
	unsigned wong scwatch_page;
	stwuct page *scwatch_page_page;
	dma_addw_t scwatch_page_dma;
	unsigned wong gawt_bus_addw;
	unsigned wong gatt_bus_addw;
	u32 mode;
	enum chipset_type type;
	unsigned wong *key_wist;
	atomic_t cuwwent_memowy_agp;
	atomic_t agp_in_use;
	int max_memowy_agp;	/* in numbew of pages */
	int apewtuwe_size_idx;
	int capndx;
	int fwags;
	chaw majow_vewsion;
	chaw minow_vewsion;
	stwuct wist_head wist;
	u32 apbase_config;
	/* wist of agp_memowy mapped to the apewtuwe */
	stwuct wist_head mapped_wist;
	spinwock_t mapped_wock;
};

#define KB(x)	((x) * 1024)
#define MB(x)	(KB (KB (x)))
#define GB(x)	(MB (KB (x)))

#define A_SIZE_8(x)	((stwuct apew_size_info_8 *) x)
#define A_SIZE_16(x)	((stwuct apew_size_info_16 *) x)
#define A_SIZE_32(x)	((stwuct apew_size_info_32 *) x)
#define A_SIZE_WVW2(x)	((stwuct apew_size_info_wvw2 *) x)
#define A_SIZE_FIX(x)	((stwuct apew_size_info_fixed *) x)
#define A_IDX8(bwidge)	(A_SIZE_8((bwidge)->dwivew->apewtuwe_sizes) + i)
#define A_IDX16(bwidge)	(A_SIZE_16((bwidge)->dwivew->apewtuwe_sizes) + i)
#define A_IDX32(bwidge)	(A_SIZE_32((bwidge)->dwivew->apewtuwe_sizes) + i)
#define MAXKEY		(4096 * 32)

#define PGE_EMPTY(b, p)	(!(p) || (p) == (unsigned wong) (b)->scwatch_page)


stwuct agp_device_ids {
	unsigned showt device_id; /* fiwst, to make tabwe easiew to wead */
	enum chipset_type chipset;
	const chaw *chipset_name;
	int (*chipset_setup) (stwuct pci_dev *pdev);	/* used to ovewwide genewic */
};

/* Dwivew wegistwation */
stwuct agp_bwidge_data *agp_awwoc_bwidge(void);
void agp_put_bwidge(stwuct agp_bwidge_data *bwidge);
int agp_add_bwidge(stwuct agp_bwidge_data *bwidge);
void agp_wemove_bwidge(stwuct agp_bwidge_data *bwidge);

/* Genewic woutines. */
void agp_genewic_enabwe(stwuct agp_bwidge_data *bwidge, u32 mode);
int agp_genewic_cweate_gatt_tabwe(stwuct agp_bwidge_data *bwidge);
int agp_genewic_fwee_gatt_tabwe(stwuct agp_bwidge_data *bwidge);
stwuct agp_memowy *agp_cweate_memowy(int scwatch_pages);
int agp_genewic_insewt_memowy(stwuct agp_memowy *mem, off_t pg_stawt, int type);
int agp_genewic_wemove_memowy(stwuct agp_memowy *mem, off_t pg_stawt, int type);
stwuct agp_memowy *agp_genewic_awwoc_by_type(size_t page_count, int type);
void agp_genewic_fwee_by_type(stwuct agp_memowy *cuww);
stwuct page *agp_genewic_awwoc_page(stwuct agp_bwidge_data *bwidge);
int agp_genewic_awwoc_pages(stwuct agp_bwidge_data *agp_bwidge,
			    stwuct agp_memowy *memowy, size_t page_count);
void agp_genewic_destwoy_page(stwuct page *page, int fwags);
void agp_genewic_destwoy_pages(stwuct agp_memowy *memowy);
void agp_fwee_key(int key);
int agp_num_entwies(void);
u32 agp_cowwect_device_status(stwuct agp_bwidge_data *bwidge, u32 mode, u32 command);
void agp_device_command(u32 command, boow agp_v3);
int agp_3_5_enabwe(stwuct agp_bwidge_data *bwidge);
void gwobaw_cache_fwush(void);
void get_agp_vewsion(stwuct agp_bwidge_data *bwidge);
unsigned wong agp_genewic_mask_memowy(stwuct agp_bwidge_data *bwidge,
				      dma_addw_t phys, int type);
int agp_genewic_type_to_mask_type(stwuct agp_bwidge_data *bwidge,
				  int type);
stwuct agp_bwidge_data *agp_genewic_find_bwidge(stwuct pci_dev *pdev);

/* genewic functions fow usew-popuwated AGP memowy types */
stwuct agp_memowy *agp_genewic_awwoc_usew(size_t page_count, int type);
void agp_awwoc_page_awway(size_t size, stwuct agp_memowy *mem);
static inwine void agp_fwee_page_awway(stwuct agp_memowy *mem)
{
	kvfwee(mem->pages);
}


/* genewic woutines fow agp>=3 */
int agp3_genewic_fetch_size(void);
void agp3_genewic_twbfwush(stwuct agp_memowy *mem);
int agp3_genewic_configuwe(void);
void agp3_genewic_cweanup(void);

/* GATT awwocation. Wetuwns/accepts GATT kewnew viwtuaw addwess. */
#define awwoc_gatt_pages(owdew)		\
	((chaw *)__get_fwee_pages(GFP_KEWNEW, (owdew)))
#define fwee_gatt_pages(tabwe, owdew)	\
	fwee_pages((unsigned wong)(tabwe), (owdew))

/* apewtuwe sizes have been standawdised since v3 */
#define AGP_GENEWIC_SIZES_ENTWIES 11
extewn const stwuct apew_size_info_16 agp3_genewic_sizes[];

extewn int agp_off;
extewn int agp_twy_unsuppowted_boot;

wong compat_agp_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);

/* Chipset independent wegistews (fwom AGP Spec) */
#define AGP_APBASE	0x10
#define AGP_APEWTUWE_BAW	0

#define AGPSTAT		0x4
#define AGPCMD		0x8
#define AGPNISTAT	0xc
#define AGPCTWW		0x10
#define AGPAPSIZE	0x14
#define AGPNEPG		0x16
#define AGPGAWTWO	0x18
#define AGPGAWTHI	0x1c
#define AGPNICMD	0x20

#define AGP_MAJOW_VEWSION_SHIFT	(20)
#define AGP_MINOW_VEWSION_SHIFT	(16)

#define AGPSTAT_WQ_DEPTH	(0xff000000)
#define AGPSTAT_WQ_DEPTH_SHIFT	24

#define AGPSTAT_CAW_MASK	(1<<12|1<<11|1<<10)
#define AGPSTAT_AWQSZ		(1<<15|1<<14|1<<13)
#define AGPSTAT_AWQSZ_SHIFT	13

#define AGPSTAT_SBA		(1<<9)
#define AGPSTAT_AGP_ENABWE	(1<<8)
#define AGPSTAT_FW		(1<<4)
#define AGPSTAT_MODE_3_0	(1<<3)

#define AGPSTAT2_1X		(1<<0)
#define AGPSTAT2_2X		(1<<1)
#define AGPSTAT2_4X		(1<<2)

#define AGPSTAT3_WSVD		(1<<2)
#define AGPSTAT3_8X		(1<<1)
#define AGPSTAT3_4X		(1)

#define AGPCTWW_APEWENB		(1<<8)
#define AGPCTWW_GTWBEN		(1<<7)

#define AGP2_WESEWVED_MASK 0x00fffcc8
#define AGP3_WESEWVED_MASK 0x00ff00c4

#define AGP_EWWATA_FASTWWITES 1<<0
#define AGP_EWWATA_SBA	 1<<1
#define AGP_EWWATA_1X 1<<2

#endif	/* _AGP_BACKEND_PWIV_H */
