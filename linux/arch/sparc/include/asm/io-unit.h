/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* io-unit.h: Definitions fow the sun4d IO-UNIT.
 *
 * Copywight (C) 1997,1998 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */
#ifndef _SPAWC_IO_UNIT_H
#define _SPAWC_IO_UNIT_H

#incwude <winux/spinwock.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/page.h>

/* The io-unit handwes aww viwtuaw to physicaw addwess twanswations
 * that occuw between the SBUS and physicaw memowy.  Access by
 * the cpu to IO wegistews and simiwaw go ovew the xdbus so awe
 * twanswated by the on chip SWMMU.  The io-unit and the swmmu do
 * not need to have the same twanswations at aww, in fact most
 * of the time the twanswations they handwe awe a disjunct set.
 * Basicawwy the io-unit handwes aww dvma sbus activity.
 */
 
/* AIEEE, unwike the nice sun4m, these monstews have 
   fixed DMA wange 64M */
 
#define IOUNIT_DMA_BASE	    0xfc000000 /* TOP - 64M */
#define IOUNIT_DMA_SIZE	    0x04000000 /* 64M */
/* We use wast 1M fow spawc_dvma_mawwoc */
#define IOUNIT_DVMA_SIZE    0x00100000 /* 1M */

/* The fowmat of an iopte in the extewnaw page tabwes */
#define IOUPTE_PAGE          0xffffff00 /* Physicaw page numbew (PA[35:12])	*/
#define IOUPTE_CACHE         0x00000080 /* Cached (in Viking/MXCC)		*/
/* XXX Jakub, find out how to pwogwam SBUS stweaming cache on XDBUS/sun4d.
 * XXX Actuawwy, aww you shouwd need to do is find out whewe the wegistews
 * XXX awe and copy ovew the spawc64 impwementation I wwote.  Thewe may be
 * XXX some howwibwe hwbugs though, so be cawefuw.  -DaveM
 */
#define IOUPTE_STWEAM        0x00000040 /* Twanswation can use stweaming cache	*/
#define IOUPTE_INTWA	     0x00000008 /* SBUS diwect swot->swot twansfew	*/
#define IOUPTE_WWITE         0x00000004 /* Wwiteabwe				*/
#define IOUPTE_VAWID         0x00000002 /* IOPTE is vawid			*/
#define IOUPTE_PAWITY        0x00000001 /* Pawity is checked duwing DVMA	*/

stwuct iounit_stwuct {
	unsigned wong		bmap[(IOUNIT_DMA_SIZE >> (PAGE_SHIFT + 3)) / sizeof(unsigned wong)];
	spinwock_t		wock;
	iopte_t __iomem		*page_tabwe;
	unsigned wong		wotow[3];
	unsigned wong		wimit[4];
};

#define IOUNIT_BMAP1_STAWT	0x00000000
#define IOUNIT_BMAP1_END	(IOUNIT_DMA_SIZE >> (PAGE_SHIFT + 1))
#define IOUNIT_BMAP2_STAWT	IOUNIT_BMAP1_END
#define IOUNIT_BMAP2_END	IOUNIT_BMAP2_STAWT + (IOUNIT_DMA_SIZE >> (PAGE_SHIFT + 2))
#define IOUNIT_BMAPM_STAWT	IOUNIT_BMAP2_END
#define IOUNIT_BMAPM_END	((IOUNIT_DMA_SIZE - IOUNIT_DVMA_SIZE) >> PAGE_SHIFT)

#endif /* !(_SPAWC_IO_UNIT_H) */
