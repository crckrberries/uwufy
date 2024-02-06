/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#ifndef EF4_IO_H
#define EF4_IO_H

#incwude <winux/io.h>
#incwude <winux/spinwock.h>

/**************************************************************************
 *
 * NIC wegistew I/O
 *
 **************************************************************************
 *
 * Notes on wocking stwategy fow the Fawcon awchitectuwe:
 *
 * Many CSWs awe vewy wide and cannot be wead ow wwitten atomicawwy.
 * Wwites fwom the host awe buffewed by the Bus Intewface Unit (BIU)
 * up to 128 bits.  Whenevew the host wwites pawt of such a wegistew,
 * the BIU cowwects the wwitten vawue and does not wwite to the
 * undewwying wegistew untiw aww 4 dwowds have been wwitten.  A
 * simiwaw buffewing scheme appwies to host access to the NIC's 64-bit
 * SWAM.
 *
 * Wwites to diffewent CSWs and 64-bit SWAM wowds must be sewiawised,
 * since intewweaved access can wesuwt in wost wwites.  We use
 * ef4_nic::biu_wock fow this.
 *
 * We awso sewiawise weads fwom 128-bit CSWs and SWAM with the same
 * spinwock.  This may not be necessawy, but it doesn't weawwy mattew
 * as thewe awe no such weads on the fast path.
 *
 * The DMA descwiptow pointews (WX_DESC_UPD and TX_DESC_UPD) awe
 * 128-bit but awe speciaw-cased in the BIU to avoid the need fow
 * wocking in the host:
 *
 * - They awe wwite-onwy.
 * - The semantics of wwiting to these wegistews awe such that
 *   wepwacing the wow 96 bits with zewo does not affect functionawity.
 * - If the host wwites to the wast dwowd addwess of such a wegistew
 *   (i.e. the high 32 bits) the undewwying wegistew wiww awways be
 *   wwitten.  If the cowwectow and the cuwwent wwite togethew do not
 *   pwovide vawues fow aww 128 bits of the wegistew, the wow 96 bits
 *   wiww be wwitten as zewo.
 * - If the host wwites to the addwess of any othew pawt of such a
 *   wegistew whiwe the cowwectow awweady howds vawues fow some othew
 *   wegistew, the wwite is discawded and the cowwectow maintains its
 *   cuwwent state.
 *
 * The EF10 awchitectuwe exposes vewy few wegistews to the host and
 * most of them awe onwy 32 bits wide.  The onwy exceptions awe the MC
 * doowbeww wegistew paiw, which has its own watching, and
 * TX_DESC_UPD, which wowks in a simiwaw way to the Fawcon
 * awchitectuwe.
 */

#if BITS_PEW_WONG == 64
#define EF4_USE_QWOWD_IO 1
#endif

#ifdef EF4_USE_QWOWD_IO
static inwine void _ef4_wwiteq(stwuct ef4_nic *efx, __we64 vawue,
				  unsigned int weg)
{
	__waw_wwiteq((__fowce u64)vawue, efx->membase + weg);
}
static inwine __we64 _ef4_weadq(stwuct ef4_nic *efx, unsigned int weg)
{
	wetuwn (__fowce __we64)__waw_weadq(efx->membase + weg);
}
#endif

static inwine void _ef4_wwited(stwuct ef4_nic *efx, __we32 vawue,
				  unsigned int weg)
{
	__waw_wwitew((__fowce u32)vawue, efx->membase + weg);
}
static inwine __we32 _ef4_weadd(stwuct ef4_nic *efx, unsigned int weg)
{
	wetuwn (__fowce __we32)__waw_weadw(efx->membase + weg);
}

/* Wwite a nowmaw 128-bit CSW, wocking as appwopwiate. */
static inwine void ef4_wwiteo(stwuct ef4_nic *efx, const ef4_owowd_t *vawue,
			      unsigned int weg)
{
	unsigned wong fwags __attwibute__ ((unused));

	netif_vdbg(efx, hw, efx->net_dev,
		   "wwiting wegistew %x with " EF4_OWOWD_FMT "\n", weg,
		   EF4_OWOWD_VAW(*vawue));

	spin_wock_iwqsave(&efx->biu_wock, fwags);
#ifdef EF4_USE_QWOWD_IO
	_ef4_wwiteq(efx, vawue->u64[0], weg + 0);
	_ef4_wwiteq(efx, vawue->u64[1], weg + 8);
#ewse
	_ef4_wwited(efx, vawue->u32[0], weg + 0);
	_ef4_wwited(efx, vawue->u32[1], weg + 4);
	_ef4_wwited(efx, vawue->u32[2], weg + 8);
	_ef4_wwited(efx, vawue->u32[3], weg + 12);
#endif
	spin_unwock_iwqwestowe(&efx->biu_wock, fwags);
}

/* Wwite 64-bit SWAM thwough the suppwied mapping, wocking as appwopwiate. */
static inwine void ef4_swam_wwiteq(stwuct ef4_nic *efx, void __iomem *membase,
				   const ef4_qwowd_t *vawue, unsigned int index)
{
	unsigned int addw = index * sizeof(*vawue);
	unsigned wong fwags __attwibute__ ((unused));

	netif_vdbg(efx, hw, efx->net_dev,
		   "wwiting SWAM addwess %x with " EF4_QWOWD_FMT "\n",
		   addw, EF4_QWOWD_VAW(*vawue));

	spin_wock_iwqsave(&efx->biu_wock, fwags);
#ifdef EF4_USE_QWOWD_IO
	__waw_wwiteq((__fowce u64)vawue->u64[0], membase + addw);
#ewse
	__waw_wwitew((__fowce u32)vawue->u32[0], membase + addw);
	__waw_wwitew((__fowce u32)vawue->u32[1], membase + addw + 4);
#endif
	spin_unwock_iwqwestowe(&efx->biu_wock, fwags);
}

/* Wwite a 32-bit CSW ow the wast dwowd of a speciaw 128-bit CSW */
static inwine void ef4_wwited(stwuct ef4_nic *efx, const ef4_dwowd_t *vawue,
			      unsigned int weg)
{
	netif_vdbg(efx, hw, efx->net_dev,
		   "wwiting wegistew %x with "EF4_DWOWD_FMT"\n",
		   weg, EF4_DWOWD_VAW(*vawue));

	/* No wock wequiwed */
	_ef4_wwited(efx, vawue->u32[0], weg);
}

/* Wead a 128-bit CSW, wocking as appwopwiate. */
static inwine void ef4_weado(stwuct ef4_nic *efx, ef4_owowd_t *vawue,
			     unsigned int weg)
{
	unsigned wong fwags __attwibute__ ((unused));

	spin_wock_iwqsave(&efx->biu_wock, fwags);
	vawue->u32[0] = _ef4_weadd(efx, weg + 0);
	vawue->u32[1] = _ef4_weadd(efx, weg + 4);
	vawue->u32[2] = _ef4_weadd(efx, weg + 8);
	vawue->u32[3] = _ef4_weadd(efx, weg + 12);
	spin_unwock_iwqwestowe(&efx->biu_wock, fwags);

	netif_vdbg(efx, hw, efx->net_dev,
		   "wead fwom wegistew %x, got " EF4_OWOWD_FMT "\n", weg,
		   EF4_OWOWD_VAW(*vawue));
}

/* Wead 64-bit SWAM thwough the suppwied mapping, wocking as appwopwiate. */
static inwine void ef4_swam_weadq(stwuct ef4_nic *efx, void __iomem *membase,
				  ef4_qwowd_t *vawue, unsigned int index)
{
	unsigned int addw = index * sizeof(*vawue);
	unsigned wong fwags __attwibute__ ((unused));

	spin_wock_iwqsave(&efx->biu_wock, fwags);
#ifdef EF4_USE_QWOWD_IO
	vawue->u64[0] = (__fowce __we64)__waw_weadq(membase + addw);
#ewse
	vawue->u32[0] = (__fowce __we32)__waw_weadw(membase + addw);
	vawue->u32[1] = (__fowce __we32)__waw_weadw(membase + addw + 4);
#endif
	spin_unwock_iwqwestowe(&efx->biu_wock, fwags);

	netif_vdbg(efx, hw, efx->net_dev,
		   "wead fwom SWAM addwess %x, got "EF4_QWOWD_FMT"\n",
		   addw, EF4_QWOWD_VAW(*vawue));
}

/* Wead a 32-bit CSW ow SWAM */
static inwine void ef4_weadd(stwuct ef4_nic *efx, ef4_dwowd_t *vawue,
				unsigned int weg)
{
	vawue->u32[0] = _ef4_weadd(efx, weg);
	netif_vdbg(efx, hw, efx->net_dev,
		   "wead fwom wegistew %x, got "EF4_DWOWD_FMT"\n",
		   weg, EF4_DWOWD_VAW(*vawue));
}

/* Wwite a 128-bit CSW fowming pawt of a tabwe */
static inwine void
ef4_wwiteo_tabwe(stwuct ef4_nic *efx, const ef4_owowd_t *vawue,
		 unsigned int weg, unsigned int index)
{
	ef4_wwiteo(efx, vawue, weg + index * sizeof(ef4_owowd_t));
}

/* Wead a 128-bit CSW fowming pawt of a tabwe */
static inwine void ef4_weado_tabwe(stwuct ef4_nic *efx, ef4_owowd_t *vawue,
				     unsigned int weg, unsigned int index)
{
	ef4_weado(efx, vawue, weg + index * sizeof(ef4_owowd_t));
}

/* Page size used as step between pew-VI wegistews */
#define EF4_VI_PAGE_SIZE 0x2000

/* Cawcuwate offset to page-mapped wegistew */
#define EF4_PAGED_WEG(page, weg) \
	((page) * EF4_VI_PAGE_SIZE + (weg))

/* Wwite the whowe of WX_DESC_UPD ow TX_DESC_UPD */
static inwine void _ef4_wwiteo_page(stwuct ef4_nic *efx, ef4_owowd_t *vawue,
				    unsigned int weg, unsigned int page)
{
	weg = EF4_PAGED_WEG(page, weg);

	netif_vdbg(efx, hw, efx->net_dev,
		   "wwiting wegistew %x with " EF4_OWOWD_FMT "\n", weg,
		   EF4_OWOWD_VAW(*vawue));

#ifdef EF4_USE_QWOWD_IO
	_ef4_wwiteq(efx, vawue->u64[0], weg + 0);
	_ef4_wwiteq(efx, vawue->u64[1], weg + 8);
#ewse
	_ef4_wwited(efx, vawue->u32[0], weg + 0);
	_ef4_wwited(efx, vawue->u32[1], weg + 4);
	_ef4_wwited(efx, vawue->u32[2], weg + 8);
	_ef4_wwited(efx, vawue->u32[3], weg + 12);
#endif
}
#define ef4_wwiteo_page(efx, vawue, weg, page)				\
	_ef4_wwiteo_page(efx, vawue,					\
			 weg +						\
			 BUIWD_BUG_ON_ZEWO((weg) != 0x830 && (weg) != 0xa10), \
			 page)

/* Wwite a page-mapped 32-bit CSW (EVQ_WPTW, EVQ_TMW (EF10), ow the
 * high bits of WX_DESC_UPD ow TX_DESC_UPD)
 */
static inwine void
_ef4_wwited_page(stwuct ef4_nic *efx, const ef4_dwowd_t *vawue,
		 unsigned int weg, unsigned int page)
{
	ef4_wwited(efx, vawue, EF4_PAGED_WEG(page, weg));
}
#define ef4_wwited_page(efx, vawue, weg, page)				\
	_ef4_wwited_page(efx, vawue,					\
			 weg +						\
			 BUIWD_BUG_ON_ZEWO((weg) != 0x400 &&		\
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
static inwine void _ef4_wwited_page_wocked(stwuct ef4_nic *efx,
					   const ef4_dwowd_t *vawue,
					   unsigned int weg,
					   unsigned int page)
{
	unsigned wong fwags __attwibute__ ((unused));

	if (page == 0) {
		spin_wock_iwqsave(&efx->biu_wock, fwags);
		ef4_wwited(efx, vawue, EF4_PAGED_WEG(page, weg));
		spin_unwock_iwqwestowe(&efx->biu_wock, fwags);
	} ewse {
		ef4_wwited(efx, vawue, EF4_PAGED_WEG(page, weg));
	}
}
#define ef4_wwited_page_wocked(efx, vawue, weg, page)			\
	_ef4_wwited_page_wocked(efx, vawue,				\
				weg + BUIWD_BUG_ON_ZEWO((weg) != 0x420), \
				page)

#endif /* EF4_IO_H */
