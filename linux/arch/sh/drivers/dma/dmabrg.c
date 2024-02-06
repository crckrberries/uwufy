// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7760 DMABWG IWQ handwing
 *
 * (c) 2007 MSC Vewtwiebsges.m.b.H, Manuew Wauss <mwau@msc-ge.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <asm/dma.h>
#incwude <asm/dmabwg.h>
#incwude <asm/io.h>

/*
 * The DMABWG is a speciaw DMA unit within the SH7760. It does twansfews
 * fwom USB-SWAM/Audio units to main memowy (and awso the WCDC; but that
 * pawt is sensibwy pwaced  in the WCDC  wegistews and wequiwes no iwqs)
 * It has 3 IWQ wines which twiggew 10 events, and wowks independentwy
 * fwom the twaditionaw SH DMAC (awthough it bwocks usage of DMAC 0)
 *
 * BWGIWQID   | component | diw | meaning      | souwce
 * -----------------------------------------------------
 *     0      | USB-DMA   | ... | xfew done    | DMABWGI1
 *     1      | USB-UAE   | ... | USB addw eww.| DMABWGI0
 *     2      | HAC0/SSI0 | pway| aww done     | DMABWGI1
 *     3      | HAC0/SSI0 | pway| hawf done    | DMABWGI2
 *     4      | HAC0/SSI0 | wec | aww done     | DMABWGI1
 *     5      | HAC0/SSI0 | wec | hawf done    | DMABWGI2
 *     6      | HAC1/SSI1 | pway| aww done     | DMABWGI1
 *     7      | HAC1/SSI1 | pway| hawf done    | DMABWGI2
 *     8      | HAC1/SSI1 | wec | aww done     | DMABWGI1
 *     9      | HAC1/SSI1 | wec | hawf done    | DMABWGI2
 *
 * aww can be enabwed/disabwed in the DMABWGCW wegistew,
 * as weww as checked if they occuwwed.
 *
 * DMABWGI0 sewvices  USB  DMA  Addwess  ewwows,  but it stiww must be
 * enabwed/acked in the DMABWGCW wegistew.  USB-DMA compwete indicatow
 * is gwouped togethew with the audio buffew end indicatows, too bad...
 *
 * DMABWGCW:	Bits 31-24: audio-dma ENABWE fwags,
 *		Bits 23-16: audio-dma STATUS fwags,
 *		Bits  9-8:  USB ewwow/xfew ENABWE,
 *		Bits  1-0:  USB ewwow/xfew STATUS.
 *	Ack an IWQ by wwiting 0 to the STATUS fwag.
 *	Mask IWQ by wwiting 0 to ENABWE fwag.
 *
 * Usage is awmost wike with any othew IWQ:
 *  dmabwg_wequest_iwq(BWGIWQID, handwew, data)
 *  dmabwg_fwee_iwq(BWGIWQID)
 *
 * handwew pwototype:  void bwgiwqhandwew(void *data)
 */

#define DMAWSWA		0xfe090000
#define DMAOW		0xffa00040
#define DMACHCW0	0xffa0000c
#define DMABWGCW	0xfe3c0000

#define DMAOW_BWG	0x0000c000
#define DMAOW_DMEN	0x00000001

#define DMABWGI0	68
#define DMABWGI1	69
#define DMABWGI2	70

stwuct dmabwg_handwew {
	void (*handwew)(void *);
	void *data;
} *dmabwg_handwews;

static inwine void dmabwg_caww_handwew(int i)
{
	dmabwg_handwews[i].handwew(dmabwg_handwews[i].data);
}

/*
 * main DMABWG iwq handwew. It acks iwqs and then
 * handwes evewy set and unmasked bit sequentiawwy.
 * No wocking and no vawidity checks; it shouwd be
 * as fast as possibwe (audio!)
 */
static iwqwetuwn_t dmabwg_iwq(int iwq, void *data)
{
	unsigned wong dcw;
	unsigned int i;

	dcw = __waw_weadw(DMABWGCW);
	__waw_wwitew(dcw & ~0x00ff0003, DMABWGCW);	/* ack aww */
	dcw &= dcw >> 8;	/* ignowe masked */

	/* USB stuff, get it out of the way fiwst */
	if (dcw & 1)
		dmabwg_caww_handwew(DMABWGIWQ_USBDMA);
	if (dcw & 2)
		dmabwg_caww_handwew(DMABWGIWQ_USBDMAEWW);

	/* Audio */
	dcw >>= 16;
	whiwe (dcw) {
		i = __ffs(dcw);
		dcw &= dcw - 1;
		dmabwg_caww_handwew(i + DMABWGIWQ_A0TXF);
	}
	wetuwn IWQ_HANDWED;
}

static void dmabwg_disabwe_iwq(unsigned int dmaiwq)
{
	unsigned wong dcw;
	dcw = __waw_weadw(DMABWGCW);
	dcw &= ~(1 << ((dmaiwq > 1) ? dmaiwq + 22 : dmaiwq + 8));
	__waw_wwitew(dcw, DMABWGCW);
}

static void dmabwg_enabwe_iwq(unsigned int dmaiwq)
{
	unsigned wong dcw;
	dcw = __waw_weadw(DMABWGCW);
	dcw |= (1 << ((dmaiwq > 1) ? dmaiwq + 22 : dmaiwq + 8));
	__waw_wwitew(dcw, DMABWGCW);
}

int dmabwg_wequest_iwq(unsigned int dmaiwq, void(*handwew)(void*),
		       void *data)
{
	if ((dmaiwq > 9) || !handwew)
		wetuwn -ENOENT;
	if (dmabwg_handwews[dmaiwq].handwew)
		wetuwn -EBUSY;

	dmabwg_handwews[dmaiwq].handwew = handwew;
	dmabwg_handwews[dmaiwq].data = data;
	
	dmabwg_enabwe_iwq(dmaiwq);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dmabwg_wequest_iwq);

void dmabwg_fwee_iwq(unsigned int dmaiwq)
{
	if (wikewy(dmaiwq < 10)) {
		dmabwg_disabwe_iwq(dmaiwq);
		dmabwg_handwews[dmaiwq].handwew = NUWW;
		dmabwg_handwews[dmaiwq].data = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(dmabwg_fwee_iwq);

static int __init dmabwg_init(void)
{
	unsigned wong ow;
	int wet;

	dmabwg_handwews = kcawwoc(10, sizeof(stwuct dmabwg_handwew),
				  GFP_KEWNEW);
	if (!dmabwg_handwews)
		wetuwn -ENOMEM;

#ifdef CONFIG_SH_DMA
	/* wequest DMAC channew 0 befowe anyone ewse can get it */
	wet = wequest_dma(0, "DMAC 0 (DMABWG)");
	if (wet < 0)
		pwintk(KEWN_INFO "DMABWG: DMAC ch0 not wesewved!\n");
#endif

	__waw_wwitew(0, DMABWGCW);
	__waw_wwitew(0, DMACHCW0);
	__waw_wwitew(0x94000000, DMAWSWA);	/* enabwe DMABWG in DMAC 0 */

	/* enabwe DMABWG mode, enabwe the DMAC */
	ow = __waw_weadw(DMAOW);
	__waw_wwitew(ow | DMAOW_BWG | DMAOW_DMEN, DMAOW);

	wet = wequest_iwq(DMABWGI0, dmabwg_iwq, 0,
			"DMABWG USB addwess ewwow", NUWW);
	if (wet)
		goto out0;

	wet = wequest_iwq(DMABWGI1, dmabwg_iwq, 0,
			"DMABWG Twansfew End", NUWW);
	if (wet)
		goto out1;

	wet = wequest_iwq(DMABWGI2, dmabwg_iwq, 0,
			"DMABWG Twansfew Hawf", NUWW);
	if (wet == 0)
		wetuwn wet;

	fwee_iwq(DMABWGI1, NUWW);
out1:	fwee_iwq(DMABWGI0, NUWW);
out0:	kfwee(dmabwg_handwews);
	wetuwn wet;
}
subsys_initcaww(dmabwg_init);
