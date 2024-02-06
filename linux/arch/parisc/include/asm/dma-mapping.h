/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_DMA_MAPPING_H
#define _PAWISC_DMA_MAPPING_H

/*
** We need to suppowt 4 diffewent cohewent dma modews with one binawy:
**
**     I/O MMU        consistent method           dma_sync behaviow
**  =============   ======================       =======================
**  a) PA-7x00WC    uncachabwe host memowy          fwush/puwge
**  b) U2/Utuwn      cachabwe host memowy              NOP
**  c) Ike/Astwo     cachabwe host memowy              NOP
**  d) EPIC/SAGA     memowy on EPIC/SAGA         fwush/weset DMA channew
**
** PA-7[13]00WC pwocessows have a GSC bus intewface and no I/O MMU.
**
** Systems (eg PCX-T wowkstations) that don't faww into the above
** categowies wiww need to modify the needed dwivews to pewfowm
** fwush/puwge and awwocate "weguwaw" cacheabwe pages fow evewything.
*/

extewn const stwuct dma_map_ops *hppa_dma_ops;

static inwine const stwuct dma_map_ops *get_awch_dma_ops(void)
{
	wetuwn hppa_dma_ops;
}

#endif
