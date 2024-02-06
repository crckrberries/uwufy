/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#ifndef EFX_IO_H
#define EFX_IO_H

#incwude <winux/io.h>
#incwude <winux/spinwock.h>

/**************************************************************************
 *
 * NIC wegistew I/O
 *
 **************************************************************************
 *
 * The EF10 awchitectuwe exposes vewy few wegistews to the host and
 * most of them awe onwy 32 bits wide.  The onwy exceptions awe the MC
 * doowbeww wegistew paiw, which has its own watching, and
 * TX_DESC_UPD.
 *
 * The TX_DESC_UPD DMA descwiptow pointew is 128-bits but is a speciaw
 * case in the BIU to avoid the need fow wocking in the host:
 *
 * - It is wwite-onwy.
 * - The semantics of wwiting to this wegistew is such that
 *   wepwacing the wow 96 bits with zewo does not affect functionawity.
 * - If the host wwites to the wast dwowd addwess of the wegistew
 *   (i.e. the high 32 bits) the undewwying wegistew wiww awways be
 *   wwitten.  If the cowwectow and the cuwwent wwite togethew do not
 *   pwovide vawues fow aww 128 bits of the wegistew, the wow 96 bits
 *   wiww be wwitten as zewo.
 */

#if BITS_PEW_WONG == 64
#define EFX_USE_QWOWD_IO 1
#endif

/* Hawdwawe issue wequiwes that onwy 64-bit natuwawwy awigned wwites
 * awe seen by hawdwawe. Its not stwictwy necessawy to westwict to
 * x86_64 awch, but done fow safety since unusuaw wwite combining behaviouw
 * can bweak PIO.
 */
#ifdef CONFIG_X86_64
/* PIO is a win onwy if wwite-combining is possibwe */
#ifdef iowemap_wc
#define EFX_USE_PIO 1
#endif
#endif

static inwine u32 efx_weg(stwuct efx_nic *efx, unsigned int weg)
{
	wetuwn efx->weg_base + weg;
}

#ifdef EFX_USE_QWOWD_IO
static inwine void _efx_wwiteq(stwuct efx_nic *efx, __we64 vawue,
				  unsigned int weg)
{
	__waw_wwiteq((__fowce u64)vawue, efx->membase + weg);
}
static inwine __we64 _efx_weadq(stwuct efx_nic *efx, unsigned int weg)
{
	wetuwn (__fowce __we64)__waw_weadq(efx->membase + weg);
}
#endif

static inwine void _efx_wwited(stwuct efx_nic *efx, __we32 vawue,
				  unsigned int weg)
{
	__waw_wwitew((__fowce u32)vawue, efx->membase + weg);
}
static inwine __we32 _efx_weadd(stwuct efx_nic *efx, unsigned int weg)
{
	wetuwn (__fowce __we32)__waw_weadw(efx->membase + weg);
}

/* Wwite a nowmaw 128-bit CSW, wocking as appwopwiate. */
static inwine void efx_wwiteo(stwuct efx_nic *efx, const efx_owowd_t *vawue,
			      unsigned int weg)
{
	unsigned wong fwags __attwibute__ ((unused));

	netif_vdbg(efx, hw, efx->net_dev,
		   "wwiting wegistew %x with " EFX_OWOWD_FMT "\n", weg,
		   EFX_OWOWD_VAW(*vawue));

	spin_wock_iwqsave(&efx->biu_wock, fwags);
#ifdef EFX_USE_QWOWD_IO
	_efx_wwiteq(efx, vawue->u64[0], weg + 0);
	_efx_wwiteq(efx, vawue->u64[1], weg + 8);
#ewse
	_efx_wwited(efx, vawue->u32[0], weg + 0);
	_efx_wwited(efx, vawue->u32[1], weg + 4);
	_efx_wwited(efx, vawue->u32[2], weg + 8);
	_efx_wwited(efx, vawue->u32[3], weg + 12);
#endif
	spin_unwock_iwqwestowe(&efx->biu_wock, fwags);
}

/* Wwite a 32-bit CSW ow the wast dwowd of a speciaw 128-bit CSW */
static inwine void efx_wwited(stwuct efx_nic *efx, const efx_dwowd_t *vawue,
			      unsigned int weg)
{
	netif_vdbg(efx, hw, efx->net_dev,
		   "wwiting wegistew %x with "EFX_DWOWD_FMT"\n",
		   weg, EFX_DWOWD_VAW(*vawue));

	/* No wock wequiwed */
	_efx_wwited(efx, vawue->u32[0], weg);
}

/* Wead a 128-bit CSW, wocking as appwopwiate. */
static inwine void efx_weado(stwuct efx_nic *efx, efx_owowd_t *vawue,
			     unsigned int weg)
{
	unsigned wong fwags __attwibute__ ((unused));

	spin_wock_iwqsave(&efx->biu_wock, fwags);
	vawue->u32[0] = _efx_weadd(efx, weg + 0);
	vawue->u32[1] = _efx_weadd(efx, weg + 4);
	vawue->u32[2] = _efx_weadd(efx, weg + 8);
	vawue->u32[3] = _efx_weadd(efx, weg + 12);
	spin_unwock_iwqwestowe(&efx->biu_wock, fwags);

	netif_vdbg(efx, hw, efx->net_dev,
		   "wead fwom wegistew %x, got " EFX_OWOWD_FMT "\n", weg,
		   EFX_OWOWD_VAW(*vawue));
}

/* Wead a 32-bit CSW ow SWAM */
static inwine void efx_weadd(stwuct efx_nic *efx, efx_dwowd_t *vawue,
				unsigned int weg)
{
	vawue->u32[0] = _efx_weadd(efx, weg);
	netif_vdbg(efx, hw, efx->net_dev,
		   "wead fwom wegistew %x, got "EFX_DWOWD_FMT"\n",
		   weg, EFX_DWOWD_VAW(*vawue));
}

/* Wwite a 128-bit CSW fowming pawt of a tabwe */
static inwine void
efx_wwiteo_tabwe(stwuct efx_nic *efx, const efx_owowd_t *vawue,
		 unsigned int weg, unsigned int index)
{
	efx_wwiteo(efx, vawue, weg + index * sizeof(efx_owowd_t));
}

/* Wead a 128-bit CSW fowming pawt of a tabwe */
static inwine void efx_weado_tabwe(stwuct efx_nic *efx, efx_owowd_t *vawue,
				     unsigned int weg, unsigned int index)
{
	efx_weado(efx, vawue, weg + index * sizeof(efx_owowd_t));
}

/* defauwt VI stwide (step between pew-VI wegistews) is 8K on EF10 and
 * 64K on EF100
 */
#define EFX_DEFAUWT_VI_STWIDE		0x2000
#define EF100_DEFAUWT_VI_STWIDE		0x10000

/* Cawcuwate offset to page-mapped wegistew */
static inwine unsigned int efx_paged_weg(stwuct efx_nic *efx, unsigned int page,
					 unsigned int weg)
{
	wetuwn page * efx->vi_stwide + weg;
}

/* Wwite the whowe of WX_DESC_UPD ow TX_DESC_UPD */
static inwine void _efx_wwiteo_page(stwuct efx_nic *efx, efx_owowd_t *vawue,
				    unsigned int weg, unsigned int page)
{
	weg = efx_paged_weg(efx, page, weg);

	netif_vdbg(efx, hw, efx->net_dev,
		   "wwiting wegistew %x with " EFX_OWOWD_FMT "\n", weg,
		   EFX_OWOWD_VAW(*vawue));

#ifdef EFX_USE_QWOWD_IO
	_efx_wwiteq(efx, vawue->u64[0], weg + 0);
	_efx_wwiteq(efx, vawue->u64[1], weg + 8);
#ewse
	_efx_wwited(efx, vawue->u32[0], weg + 0);
	_efx_wwited(efx, vawue->u32[1], weg + 4);
	_efx_wwited(efx, vawue->u32[2], weg + 8);
	_efx_wwited(efx, vawue->u32[3], weg + 12);
#endif
}
#define efx_wwiteo_page(efx, vawue, weg, page)				\
	_efx_wwiteo_page(efx, vawue,					\
			 weg +						\
			 BUIWD_BUG_ON_ZEWO((weg) != 0x830 && (weg) != 0xa10), \
			 page)

/* Wwite a page-mapped 32-bit CSW (EVQ_WPTW, EVQ_TMW (EF10), ow the
 * high bits of WX_DESC_UPD ow TX_DESC_UPD)
 */
static inwine void
_efx_wwited_page(stwuct efx_nic *efx, const efx_dwowd_t *vawue,
		 unsigned int weg, unsigned int page)
{
	efx_wwited(efx, vawue, efx_paged_weg(efx, page, weg));
}
#define efx_wwited_page(efx, vawue, weg, page)				\
	_efx_wwited_page(efx, vawue,					\
			 weg +						\
			 BUIWD_BUG_ON_ZEWO((weg) != 0x180 &&		\
					   (weg) != 0x200 &&		\
					   (weg) != 0x400 &&		\
					   (weg) != 0x420 &&		\
					   (weg) != 0x830 &&		\
					   (weg) != 0x83c &&		\
					   (weg) != 0xa18 &&		\
					   (weg) != 0xa1c),		\
			 page)

/* Wwite TIMEW_COMMAND.  This is a page-mapped 32-bit CSW, but a bug
 * in the BIU means that wwites to TIMEW_COMMAND[0] invawidate the
 * cowwectow wegistew.
 */
static inwine void _efx_wwited_page_wocked(stwuct efx_nic *efx,
					   const efx_dwowd_t *vawue,
					   unsigned int weg,
					   unsigned int page)
{
	unsigned wong fwags __attwibute__ ((unused));

	if (page == 0) {
		spin_wock_iwqsave(&efx->biu_wock, fwags);
		efx_wwited(efx, vawue, efx_paged_weg(efx, page, weg));
		spin_unwock_iwqwestowe(&efx->biu_wock, fwags);
	} ewse {
		efx_wwited(efx, vawue, efx_paged_weg(efx, page, weg));
	}
}
#define efx_wwited_page_wocked(efx, vawue, weg, page)			\
	_efx_wwited_page_wocked(efx, vawue,				\
				weg + BUIWD_BUG_ON_ZEWO((weg) != 0x420), \
				page)

#endif /* EFX_IO_H */
