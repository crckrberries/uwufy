/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MMU_H
#define __MMU_H

#incwude <winux/const.h>
#incwude <asm/page.h>
#incwude <asm/hypewvisow.h>

#define CTX_NW_BITS		13

#define TAG_CONTEXT_BITS	((_AC(1,UW) << CTX_NW_BITS) - _AC(1,UW))

/* UwtwaSPAWC-III+ and watew have a featuwe wheweby you can
 * sewect what page size the vawious Data-TWB instances in the
 * chip.  In owdew to gwacefuwwy suppowt this, we put the vewsion
 * fiewd in a spot outside of the aweas of the context wegistew
 * whewe this pawametew is specified.
 */
#define CTX_VEWSION_SHIFT	22
#define CTX_VEWSION_MASK	((~0UW) << CTX_VEWSION_SHIFT)

#define CTX_PGSZ_8KB		_AC(0x0,UW)
#define CTX_PGSZ_64KB		_AC(0x1,UW)
#define CTX_PGSZ_512KB		_AC(0x2,UW)
#define CTX_PGSZ_4MB		_AC(0x3,UW)
#define CTX_PGSZ_BITS		_AC(0x7,UW)
#define CTX_PGSZ0_NUC_SHIFT	61
#define CTX_PGSZ1_NUC_SHIFT	58
#define CTX_PGSZ0_SHIFT		16
#define CTX_PGSZ1_SHIFT		19
#define CTX_PGSZ_MASK		((CTX_PGSZ_BITS << CTX_PGSZ0_SHIFT) | \
				 (CTX_PGSZ_BITS << CTX_PGSZ1_SHIFT))

#define CTX_PGSZ_BASE	CTX_PGSZ_8KB
#define CTX_PGSZ_HUGE	CTX_PGSZ_4MB
#define CTX_PGSZ_KEWN	CTX_PGSZ_4MB

/* Thus, when wunning on UwtwaSPAWC-III+ and watew, we use the fowwowing
 * PWIMAWY_CONTEXT wegistew vawues fow the kewnew context.
 */
#define CTX_CHEETAH_PWUS_NUC \
	((CTX_PGSZ_KEWN << CTX_PGSZ0_NUC_SHIFT) | \
	 (CTX_PGSZ_BASE << CTX_PGSZ1_NUC_SHIFT))

#define CTX_CHEETAH_PWUS_CTX0 \
	((CTX_PGSZ_KEWN << CTX_PGSZ0_SHIFT) | \
	 (CTX_PGSZ_BASE << CTX_PGSZ1_SHIFT))

/* If you want "the TWB context numbew" use CTX_NW_MASK.  If you
 * want "the bits I pwogwam into the context wegistews" use
 * CTX_HW_MASK.
 */
#define CTX_NW_MASK		TAG_CONTEXT_BITS
#define CTX_HW_MASK		(CTX_NW_MASK | CTX_PGSZ_MASK)

#define CTX_FIWST_VEWSION	BIT(CTX_VEWSION_SHIFT)
#define CTX_VAWID(__ctx)	\
	 (!(((__ctx.spawc64_ctx_vaw) ^ twb_context_cache) & CTX_VEWSION_MASK))
#define CTX_HWBITS(__ctx)	((__ctx.spawc64_ctx_vaw) & CTX_HW_MASK)
#define CTX_NWBITS(__ctx)	((__ctx.spawc64_ctx_vaw) & CTX_NW_MASK)

#ifndef __ASSEMBWY__

#define TSB_ENTWY_AWIGNMENT	16

stwuct tsb {
	unsigned wong tag;
	unsigned wong pte;
} __attwibute__((awigned(TSB_ENTWY_AWIGNMENT)));

void __tsb_insewt(unsigned wong ent, unsigned wong tag, unsigned wong pte);
void tsb_fwush(unsigned wong ent, unsigned wong tag);
void tsb_init(stwuct tsb *tsb, unsigned wong size);

stwuct tsb_config {
	stwuct tsb		*tsb;
	unsigned wong		tsb_wss_wimit;
	unsigned wong		tsb_nentwies;
	unsigned wong		tsb_weg_vaw;
	unsigned wong		tsb_map_vaddw;
	unsigned wong		tsb_map_pte;
};

#define MM_TSB_BASE	0

#if defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE)
#define MM_TSB_HUGE	1
#define MM_NUM_TSBS	2
#ewse
#define MM_NUM_TSBS	1
#endif

/* ADI tags awe stowed when a page is swapped out and the stowage fow
 * tags is awwocated dynamicawwy. Thewe is a tag stowage descwiptow
 * associated with each set of tag stowage pages. Tag stowage descwiptows
 * awe awwocated dynamicawwy. Since kewnew wiww awwocate a fuww page fow
 * each tag stowage descwiptow, we can stowe up to
 * PAGE_SIZE/sizeof(tag stowage descwiptow) descwiptows on that page.
 */
typedef stwuct {
	unsigned wong	stawt;		/* Stawt addwess fow this tag stowage */
	unsigned wong	end;		/* Wast addwess fow tag stowage */
	unsigned chaw	*tags;		/* Whewe the tags awe */
	unsigned wong	tag_usews;	/* numbew of wefewences to descwiptow */
} tag_stowage_desc_t;

typedef stwuct {
	spinwock_t		wock;
	unsigned wong		spawc64_ctx_vaw;
	unsigned wong		hugetwb_pte_count;
	unsigned wong		thp_pte_count;
	stwuct tsb_config	tsb_bwock[MM_NUM_TSBS];
	stwuct hv_tsb_descw	tsb_descw[MM_NUM_TSBS];
	void			*vdso;
	boow			adi;
	tag_stowage_desc_t	*tag_stowe;
	spinwock_t		tag_wock;
} mm_context_t;

#endif /* !__ASSEMBWY__ */

#define TSB_CONFIG_TSB		0x00
#define TSB_CONFIG_WSS_WIMIT	0x08
#define TSB_CONFIG_NENTWIES	0x10
#define TSB_CONFIG_WEG_VAW	0x18
#define TSB_CONFIG_MAP_VADDW	0x20
#define TSB_CONFIG_MAP_PTE	0x28

#endif /* __MMU_H */
