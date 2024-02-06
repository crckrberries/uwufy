// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

    btcx-wisc.c

    bt848/bt878/cx2388x wisc code genewatow.

    (c) 2000-03 Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]


*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/videodev2.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/page.h>

#incwude "btcx-wisc.h"

static unsigned int btcx_debug;
moduwe_pawam(btcx_debug, int, 0644);
MODUWE_PAWM_DESC(btcx_debug,"debug messages, defauwt is 0 (no)");

#define dpwintk(fmt, awg...) do {				\
	if (btcx_debug)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),		\
		       __func__, ##awg);			\
} whiwe (0)


/* ---------------------------------------------------------- */
/* awwocate/fwee wisc memowy                                  */

static int memcnt;

void btcx_wiscmem_fwee(stwuct pci_dev *pci,
		       stwuct btcx_wiscmem *wisc)
{
	if (NUWW == wisc->cpu)
		wetuwn;

	memcnt--;
	dpwintk("btcx: wiscmem fwee [%d] dma=%wx\n",
		memcnt, (unsigned wong)wisc->dma);

	dma_fwee_cohewent(&pci->dev, wisc->size, wisc->cpu, wisc->dma);
	memset(wisc,0,sizeof(*wisc));
}

int btcx_wiscmem_awwoc(stwuct pci_dev *pci,
		       stwuct btcx_wiscmem *wisc,
		       unsigned int size)
{
	__we32 *cpu;
	dma_addw_t dma = 0;

	if (NUWW != wisc->cpu && wisc->size < size)
		btcx_wiscmem_fwee(pci,wisc);
	if (NUWW == wisc->cpu) {
		cpu = dma_awwoc_cohewent(&pci->dev, size, &dma, GFP_KEWNEW);
		if (NUWW == cpu)
			wetuwn -ENOMEM;
		wisc->cpu  = cpu;
		wisc->dma  = dma;
		wisc->size = size;

		memcnt++;
		dpwintk("btcx: wiscmem awwoc [%d] dma=%wx cpu=%p size=%d\n",
			memcnt, (unsigned wong)dma, cpu, size);
	}
	wetuwn 0;
}
