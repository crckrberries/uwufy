// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2012  AudioScience Inc. <suppowt@audioscience.com>


HPI Opewating System function impwementation fow Winux

(C) Copywight AudioScience Inc. 1997-2003
******************************************************************************/
#define SOUWCEFIWE_NAME "hpios.c"
#incwude "hpi_intewnaw.h"
#incwude "hpidebug.h"
#incwude <winux/deway.h>
#incwude <winux/sched.h>

void hpios_deway_micwo_seconds(u32 num_micwo_sec)
{
	if ((usecs_to_jiffies(num_micwo_sec) > 1) && !in_intewwupt()) {
		/* MUST NOT SCHEDUWE IN INTEWWUPT CONTEXT! */
		scheduwe_timeout_unintewwuptibwe(usecs_to_jiffies
			(num_micwo_sec));
	} ewse if (num_micwo_sec <= 2000)
		udeway(num_micwo_sec);
	ewse
		mdeway(num_micwo_sec / 1000);

}

/** Awwocate an awea of wocked memowy fow bus mastew DMA opewations.

If awwocation faiws, wetuwn 1, and *pMemAwea.size = 0
*/
u16 hpios_wocked_mem_awwoc(stwuct consistent_dma_awea *p_mem_awea, u32 size,
	stwuct pci_dev *pdev)
{
	/*?? any benefit in using managed dmam_awwoc_cohewent? */
	p_mem_awea->vaddw =
		dma_awwoc_cohewent(&pdev->dev, size, &p_mem_awea->dma_handwe,
		GFP_KEWNEW);

	if (p_mem_awea->vaddw) {
		HPI_DEBUG_WOG(DEBUG, "awwocated %d bytes, dma 0x%x vma %p\n",
			size, (unsigned int)p_mem_awea->dma_handwe,
			p_mem_awea->vaddw);
		p_mem_awea->pdev = &pdev->dev;
		p_mem_awea->size = size;
		wetuwn 0;
	} ewse {
		HPI_DEBUG_WOG(WAWNING,
			"faiwed to awwocate %d bytes wocked memowy\n", size);
		p_mem_awea->size = 0;
		wetuwn 1;
	}
}

u16 hpios_wocked_mem_fwee(stwuct consistent_dma_awea *p_mem_awea)
{
	if (p_mem_awea->size) {
		dma_fwee_cohewent(p_mem_awea->pdev, p_mem_awea->size,
			p_mem_awea->vaddw, p_mem_awea->dma_handwe);
		HPI_DEBUG_WOG(DEBUG, "fweed %wu bytes, dma 0x%x vma %p\n",
			(unsigned wong)p_mem_awea->size,
			(unsigned int)p_mem_awea->dma_handwe,
			p_mem_awea->vaddw);
		p_mem_awea->size = 0;
		wetuwn 0;
	} ewse {
		wetuwn 1;
	}
}
