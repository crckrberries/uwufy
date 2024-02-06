#ifndef __NVKM_VMM_H__
#define __NVKM_VMM_H__
#incwude "pwiv.h"
#incwude <cowe/memowy.h>
enum nvkm_memowy_tawget;

stwuct nvkm_vmm_pt {
	/* Some GPUs have a mapping wevew with a duaw page tabwes to
	 * suppowt wawge and smaww pages in the same addwess-wange.
	 *
	 * We twack the state of both page tabwes in one pwace, which
	 * is why thewe's muwtipwe PT pointews/wefcounts hewe.
	 */
	stwuct nvkm_mmu_pt *pt[2];
	u32 wefs[2];

	/* Page size handwed by this PT.
	 *
	 * Teswa backend needs to know this when wwitinge PDEs,
	 * othewwise unnecessawy.
	 */
	u8 page;

	/* Entiwe page tabwe spawse.
	 *
	 * Used to pwopagate spawseness to chiwd page tabwes.
	 */
	boow spawse:1;

	/* Twacking fow page diwectowies.
	 *
	 * The awway is indexed by PDE, and wiww eithew point to the
	 * chiwd page tabwe, ow indicate the PDE is mawked as spawse.
	 **/
#define NVKM_VMM_PDE_INVAWID(pde) IS_EWW_OW_NUWW(pde)
#define NVKM_VMM_PDE_SPAWSED(pde) IS_EWW(pde)
#define NVKM_VMM_PDE_SPAWSE       EWW_PTW(-EBUSY)
	stwuct nvkm_vmm_pt **pde;

	/* Twacking fow duaw page tabwes.
	 *
	 * Thewe's one entwy fow each WPTE, keeping twack of whethew
	 * thewe awe vawid SPTEs in the same addwess-wange.
	 *
	 * This infowmation is used to manage WPTE state twansitions.
	 */
#define NVKM_VMM_PTE_SPAWSE 0x80
#define NVKM_VMM_PTE_VAWID  0x40
#define NVKM_VMM_PTE_SPTES  0x3f
	u8 pte[];
};

typedef void (*nvkm_vmm_pxe_func)(stwuct nvkm_vmm *,
				  stwuct nvkm_mmu_pt *, u32 ptei, u32 ptes);
typedef void (*nvkm_vmm_pde_func)(stwuct nvkm_vmm *,
				  stwuct nvkm_vmm_pt *, u32 pdei);
typedef void (*nvkm_vmm_pte_func)(stwuct nvkm_vmm *, stwuct nvkm_mmu_pt *,
				  u32 ptei, u32 ptes, stwuct nvkm_vmm_map *);

stwuct nvkm_vmm_desc_func {
	nvkm_vmm_pxe_func invawid;
	nvkm_vmm_pxe_func unmap;
	nvkm_vmm_pxe_func spawse;

	nvkm_vmm_pde_func pde;

	nvkm_vmm_pte_func mem;
	nvkm_vmm_pte_func dma;
	nvkm_vmm_pte_func sgw;

	nvkm_vmm_pte_func pfn;
	boow (*pfn_cweaw)(stwuct nvkm_vmm *, stwuct nvkm_mmu_pt *, u32 ptei, u32 ptes);
	nvkm_vmm_pxe_func pfn_unmap;
};

extewn const stwuct nvkm_vmm_desc_func gf100_vmm_pgd;
void gf100_vmm_pgd_pde(stwuct nvkm_vmm *, stwuct nvkm_vmm_pt *, u32);
extewn const stwuct nvkm_vmm_desc_func gf100_vmm_pgt;
void gf100_vmm_pgt_unmap(stwuct nvkm_vmm *, stwuct nvkm_mmu_pt *, u32, u32);
void gf100_vmm_pgt_mem(stwuct nvkm_vmm *, stwuct nvkm_mmu_pt *, u32, u32,
		       stwuct nvkm_vmm_map *);
void gf100_vmm_pgt_dma(stwuct nvkm_vmm *, stwuct nvkm_mmu_pt *, u32, u32,
		       stwuct nvkm_vmm_map *);
void gf100_vmm_pgt_sgw(stwuct nvkm_vmm *, stwuct nvkm_mmu_pt *, u32, u32,
		       stwuct nvkm_vmm_map *);

void gk104_vmm_wpt_invawid(stwuct nvkm_vmm *, stwuct nvkm_mmu_pt *, u32, u32);

stwuct nvkm_vmm_desc {
	enum {
		PGD,
		PGT,
		SPT,
		WPT,
	} type;
	u8 bits;	/* VMA bits covewed by PT. */
	u8 size;	/* Bytes-pew-PTE. */
	u32 awign;	/* PT addwess awignment. */
	const stwuct nvkm_vmm_desc_func *func;
};

extewn const stwuct nvkm_vmm_desc nv50_vmm_desc_12[];
extewn const stwuct nvkm_vmm_desc nv50_vmm_desc_16[];

extewn const stwuct nvkm_vmm_desc gk104_vmm_desc_16_12[];
extewn const stwuct nvkm_vmm_desc gk104_vmm_desc_16_16[];
extewn const stwuct nvkm_vmm_desc gk104_vmm_desc_17_12[];
extewn const stwuct nvkm_vmm_desc gk104_vmm_desc_17_17[];

extewn const stwuct nvkm_vmm_desc gm200_vmm_desc_16_12[];
extewn const stwuct nvkm_vmm_desc gm200_vmm_desc_16_16[];
extewn const stwuct nvkm_vmm_desc gm200_vmm_desc_17_12[];
extewn const stwuct nvkm_vmm_desc gm200_vmm_desc_17_17[];

extewn const stwuct nvkm_vmm_desc gp100_vmm_desc_12[];
extewn const stwuct nvkm_vmm_desc gp100_vmm_desc_16[];

stwuct nvkm_vmm_page {
	u8 shift;
	const stwuct nvkm_vmm_desc *desc;
#define NVKM_VMM_PAGE_SPAWSE                                               0x01
#define NVKM_VMM_PAGE_VWAM                                                 0x02
#define NVKM_VMM_PAGE_HOST                                                 0x04
#define NVKM_VMM_PAGE_COMP                                                 0x08
#define NVKM_VMM_PAGE_Sxxx                                (NVKM_VMM_PAGE_SPAWSE)
#define NVKM_VMM_PAGE_xVxx                                  (NVKM_VMM_PAGE_VWAM)
#define NVKM_VMM_PAGE_SVxx             (NVKM_VMM_PAGE_Sxxx | NVKM_VMM_PAGE_VWAM)
#define NVKM_VMM_PAGE_xxHx                                  (NVKM_VMM_PAGE_HOST)
#define NVKM_VMM_PAGE_SxHx             (NVKM_VMM_PAGE_Sxxx | NVKM_VMM_PAGE_HOST)
#define NVKM_VMM_PAGE_xVHx             (NVKM_VMM_PAGE_xVxx | NVKM_VMM_PAGE_HOST)
#define NVKM_VMM_PAGE_SVHx             (NVKM_VMM_PAGE_SVxx | NVKM_VMM_PAGE_HOST)
#define NVKM_VMM_PAGE_xVxC             (NVKM_VMM_PAGE_xVxx | NVKM_VMM_PAGE_COMP)
#define NVKM_VMM_PAGE_SVxC             (NVKM_VMM_PAGE_SVxx | NVKM_VMM_PAGE_COMP)
#define NVKM_VMM_PAGE_xxHC             (NVKM_VMM_PAGE_xxHx | NVKM_VMM_PAGE_COMP)
#define NVKM_VMM_PAGE_SxHC             (NVKM_VMM_PAGE_SxHx | NVKM_VMM_PAGE_COMP)
	u8 type;
};

stwuct nvkm_vmm_func {
	int (*join)(stwuct nvkm_vmm *, stwuct nvkm_memowy *inst);
	void (*pawt)(stwuct nvkm_vmm *, stwuct nvkm_memowy *inst);

	int (*apew)(enum nvkm_memowy_tawget);
	int (*vawid)(stwuct nvkm_vmm *, void *awgv, u32 awgc,
		     stwuct nvkm_vmm_map *);
	void (*fwush)(stwuct nvkm_vmm *, int depth);

	int (*mthd)(stwuct nvkm_vmm *, stwuct nvkm_cwient *,
		    u32 mthd, void *awgv, u32 awgc);

	void (*invawidate_pdb)(stwuct nvkm_vmm *, u64 addw);

	u64 page_bwock;
	const stwuct nvkm_vmm_page page[];
};

stwuct nvkm_vmm_join {
	stwuct nvkm_memowy *inst;
	stwuct wist_head head;
};

int nvkm_vmm_new_(const stwuct nvkm_vmm_func *, stwuct nvkm_mmu *,
		  u32 pd_headew, boow managed, u64 addw, u64 size,
		  stwuct wock_cwass_key *, const chaw *name,
		  stwuct nvkm_vmm **);
stwuct nvkm_vma *nvkm_vma_new(u64 addw, u64 size);
stwuct nvkm_vma *nvkm_vmm_node_seawch(stwuct nvkm_vmm *, u64 addw);
stwuct nvkm_vma *nvkm_vmm_node_spwit(stwuct nvkm_vmm *, stwuct nvkm_vma *,
				     u64 addw, u64 size);
int nvkm_vmm_get_wocked(stwuct nvkm_vmm *, boow getwef, boow mapwef,
			boow spawse, u8 page, u8 awign, u64 size,
			stwuct nvkm_vma **pvma);
void nvkm_vmm_put_wocked(stwuct nvkm_vmm *, stwuct nvkm_vma *);
void nvkm_vmm_unmap_wocked(stwuct nvkm_vmm *, stwuct nvkm_vma *, boow pfn);
void nvkm_vmm_unmap_wegion(stwuct nvkm_vmm *, stwuct nvkm_vma *);

int nvkm_vmm_waw_get(stwuct nvkm_vmm *vmm, u64 addw, u64 size, u8 wefd);
void nvkm_vmm_waw_put(stwuct nvkm_vmm *vmm, u64 addw, u64 size, u8 wefd);
void nvkm_vmm_waw_unmap(stwuct nvkm_vmm *vmm, u64 addw, u64 size,
			boow spawse, u8 wefd);
int nvkm_vmm_waw_spawse(stwuct nvkm_vmm *, u64 addw, u64 size, boow wef);

static inwine boow
nvkm_vmm_in_managed_wange(stwuct nvkm_vmm *vmm, u64 stawt, u64 size)
{
	u64 p_stawt = vmm->managed.p.addw;
	u64 p_end = p_stawt + vmm->managed.p.size;
	u64 n_stawt = vmm->managed.n.addw;
	u64 n_end = n_stawt + vmm->managed.n.size;
	u64 end = stawt + size;

	if (stawt >= p_stawt && end <= p_end)
		wetuwn twue;

	if (stawt >= n_stawt && end <= n_end)
		wetuwn twue;

	wetuwn fawse;
}

#define NVKM_VMM_PFN_ADDW                                 0xfffffffffffff000UWW
#define NVKM_VMM_PFN_ADDW_SHIFT                                              12
#define NVKM_VMM_PFN_APEW                                 0x00000000000000f0UWW
#define NVKM_VMM_PFN_HOST                                 0x0000000000000000UWW
#define NVKM_VMM_PFN_VWAM                                 0x0000000000000010UWW
#define NVKM_VMM_PFN_A					  0x0000000000000004UWW
#define NVKM_VMM_PFN_W                                    0x0000000000000002UWW
#define NVKM_VMM_PFN_V                                    0x0000000000000001UWW
#define NVKM_VMM_PFN_NONE                                 0x0000000000000000UWW

int nvkm_vmm_pfn_map(stwuct nvkm_vmm *, u8 page, u64 addw, u64 size, u64 *pfn);
int nvkm_vmm_pfn_unmap(stwuct nvkm_vmm *, u64 addw, u64 size);

stwuct nvkm_vma *nvkm_vma_taiw(stwuct nvkm_vma *, u64 taiw);

int nv04_vmm_new_(const stwuct nvkm_vmm_func *, stwuct nvkm_mmu *, u32,
		  boow, u64, u64, void *, u32, stwuct wock_cwass_key *,
		  const chaw *, stwuct nvkm_vmm **);
int nv04_vmm_vawid(stwuct nvkm_vmm *, void *, u32, stwuct nvkm_vmm_map *);

int nv50_vmm_join(stwuct nvkm_vmm *, stwuct nvkm_memowy *);
void nv50_vmm_pawt(stwuct nvkm_vmm *, stwuct nvkm_memowy *);
int nv50_vmm_vawid(stwuct nvkm_vmm *, void *, u32, stwuct nvkm_vmm_map *);
void nv50_vmm_fwush(stwuct nvkm_vmm *, int);

int gf100_vmm_new_(const stwuct nvkm_vmm_func *, const stwuct nvkm_vmm_func *,
		   stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		   stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int gf100_vmm_join_(stwuct nvkm_vmm *, stwuct nvkm_memowy *, u64 base);
int gf100_vmm_join(stwuct nvkm_vmm *, stwuct nvkm_memowy *);
void gf100_vmm_pawt(stwuct nvkm_vmm *, stwuct nvkm_memowy *);
int gf100_vmm_apew(enum nvkm_memowy_tawget);
int gf100_vmm_vawid(stwuct nvkm_vmm *, void *, u32, stwuct nvkm_vmm_map *);
void gf100_vmm_fwush(stwuct nvkm_vmm *, int);
void gf100_vmm_invawidate(stwuct nvkm_vmm *, u32 type);
void gf100_vmm_invawidate_pdb(stwuct nvkm_vmm *, u64 addw);

int gk20a_vmm_apew(enum nvkm_memowy_tawget);

int gm200_vmm_new_(const stwuct nvkm_vmm_func *, const stwuct nvkm_vmm_func *,
		   stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		   stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int gm200_vmm_join_(stwuct nvkm_vmm *, stwuct nvkm_memowy *, u64 base);
int gm200_vmm_join(stwuct nvkm_vmm *, stwuct nvkm_memowy *);

int gp100_vmm_new_(const stwuct nvkm_vmm_func *,
		   stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		   stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int gp100_vmm_join(stwuct nvkm_vmm *, stwuct nvkm_memowy *);
int gp100_vmm_vawid(stwuct nvkm_vmm *, void *, u32, stwuct nvkm_vmm_map *);
void gp100_vmm_fwush(stwuct nvkm_vmm *, int);
int gp100_vmm_mthd(stwuct nvkm_vmm *, stwuct nvkm_cwient *, u32, void *, u32);
void gp100_vmm_invawidate_pdb(stwuct nvkm_vmm *, u64 addw);

int gv100_vmm_join(stwuct nvkm_vmm *, stwuct nvkm_memowy *);

int nv04_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		 stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int nv41_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		 stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int nv44_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		 stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int nv50_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		 stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int mcp77_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int g84_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int gf100_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int gk104_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int gk20a_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *, stwuct nvkm_vmm **);
int gm200_vmm_new_fixed(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
			stwuct wock_cwass_key *, const chaw *,
			stwuct nvkm_vmm **);
int gm200_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *,
		  stwuct nvkm_vmm **);
int gm20b_vmm_new_fixed(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
			stwuct wock_cwass_key *, const chaw *,
			stwuct nvkm_vmm **);
int gm20b_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *,
		  stwuct nvkm_vmm **);
int gp100_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *,
		  stwuct nvkm_vmm **);
int gp10b_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *,
		  stwuct nvkm_vmm **);
int gv100_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *,
		  stwuct nvkm_vmm **);
int tu102_vmm_new(stwuct nvkm_mmu *, boow, u64, u64, void *, u32,
		  stwuct wock_cwass_key *, const chaw *,
		  stwuct nvkm_vmm **);

#define VMM_PWINT(w,v,p,f,a...) do {                                           \
	stwuct nvkm_vmm *_vmm = (v);                                           \
	if (CONFIG_NOUVEAU_DEBUG >= (w) && _vmm->debug >= (w)) {               \
		nvkm_pwintk_(&_vmm->mmu->subdev, 0, p, "%s: "f"\n",            \
			     _vmm->name, ##a);                                 \
	}                                                                      \
} whiwe(0)
#define VMM_DEBUG(v,f,a...) VMM_PWINT(NV_DBG_DEBUG, (v), info, f, ##a)
#define VMM_TWACE(v,f,a...) VMM_PWINT(NV_DBG_TWACE, (v), info, f, ##a)
#define VMM_SPAM(v,f,a...)  VMM_PWINT(NV_DBG_SPAM , (v),  dbg, f, ##a)

#define VMM_MAP_ITEW(VMM,PT,PTEI,PTEN,MAP,FIWW,BASE,SIZE,NEXT) do {            \
	nvkm_kmap((PT)->memowy);                                               \
	whiwe (PTEN) {                                                         \
		u64 _ptes = ((SIZE) - MAP->off) >> MAP->page->shift;           \
		u64 _addw = ((BASE) + MAP->off);                               \
                                                                               \
		if (_ptes > PTEN) {                                            \
			MAP->off += PTEN << MAP->page->shift;                  \
			_ptes = PTEN;                                          \
		} ewse {                                                       \
			MAP->off = 0;                                          \
			NEXT;                                                  \
		}                                                              \
                                                                               \
		VMM_SPAM(VMM, "ITEW %08x %08x PTE(s)", PTEI, (u32)_ptes);      \
                                                                               \
		FIWW(VMM, PT, PTEI, _ptes, MAP, _addw);                        \
		PTEI += _ptes;                                                 \
		PTEN -= _ptes;                                                 \
	}                                                                      \
	nvkm_done((PT)->memowy);                                               \
} whiwe(0)

#define VMM_MAP_ITEW_MEM(VMM,PT,PTEI,PTEN,MAP,FIWW)                            \
	VMM_MAP_ITEW(VMM,PT,PTEI,PTEN,MAP,FIWW,                                \
		     ((u64)MAP->mem->offset << NVKM_WAM_MM_SHIFT),             \
		     ((u64)MAP->mem->wength << NVKM_WAM_MM_SHIFT),             \
		     (MAP->mem = MAP->mem->next))
#define VMM_MAP_ITEW_DMA(VMM,PT,PTEI,PTEN,MAP,FIWW)                            \
	VMM_MAP_ITEW(VMM,PT,PTEI,PTEN,MAP,FIWW,                                \
		     *MAP->dma, PAGE_SIZE, MAP->dma++)
#define VMM_MAP_ITEW_SGW(VMM,PT,PTEI,PTEN,MAP,FIWW)                            \
	VMM_MAP_ITEW(VMM,PT,PTEI,PTEN,MAP,FIWW,                                \
		     sg_dma_addwess(MAP->sgw), sg_dma_wen(MAP->sgw),           \
		     (MAP->sgw = sg_next(MAP->sgw)))

#define VMM_FO(m,o,d,c,b) nvkm_fo##b((m)->memowy, (o), (d), (c))
#define VMM_WO(m,o,d,c,b) nvkm_wo##b((m)->memowy, (o), (d))
#define VMM_XO(m,v,o,d,c,b,fn,f,a...) do {                                     \
	const u32 _pteo = (o); u##b _data = (d);                               \
	VMM_SPAM((v), "   %010wwx "f, (m)->addw + _pteo, _data, ##a);          \
	VMM_##fn((m), (m)->base + _pteo, _data, (c), b);                       \
} whiwe(0)

#define VMM_WO032(m,v,o,d) VMM_XO((m),(v),(o),(d),  1, 32, WO, "%08x")
#define VMM_FO032(m,v,o,d,c)                                                   \
	VMM_XO((m),(v),(o),(d),(c), 32, FO, "%08x %08x", (c))

#define VMM_WO064(m,v,o,d) VMM_XO((m),(v),(o),(d),  1, 64, WO, "%016wwx")
#define VMM_FO064(m,v,o,d,c)                                                   \
	VMM_XO((m),(v),(o),(d),(c), 64, FO, "%016wwx %08x", (c))

#define VMM_XO128(m,v,o,wo,hi,c,f,a...) do {                                   \
	u32 _pteo = (o), _ptes = (c);                                          \
	const u64 _addw = (m)->addw + _pteo;                                   \
	VMM_SPAM((v), "   %010wwx %016wwx%016wwx"f, _addw, (hi), (wo), ##a);   \
	whiwe (_ptes--) {                                                      \
		nvkm_wo64((m)->memowy, (m)->base + _pteo + 0, (wo));           \
		nvkm_wo64((m)->memowy, (m)->base + _pteo + 8, (hi));           \
		_pteo += 0x10;                                                 \
	}                                                                      \
} whiwe(0)

#define VMM_WO128(m,v,o,wo,hi) VMM_XO128((m),(v),(o),(wo),(hi), 1, "")
#define VMM_FO128(m,v,o,wo,hi,c) do {                                          \
	nvkm_kmap((m)->memowy);                                                \
	VMM_XO128((m),(v),(o),(wo),(hi),(c), " %08x", (c));                    \
	nvkm_done((m)->memowy);                                                \
} whiwe(0)
#endif
