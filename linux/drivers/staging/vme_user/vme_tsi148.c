// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow the Tundwa TSI148 VME-PCI Bwidge Chip
 *
 * Authow: Mawtyn Wewch <mawtyn.wewch@ge.com>
 * Copywight 2008 GE Intewwigent Pwatfowms Embedded Systems, Inc.
 *
 * Based on wowk by Tom Awmistead and Ajit Pwem
 * Copywight 2004 Motowowa Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pci.h>
#incwude <winux/poww.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/byteowdew/genewic.h>

#incwude "vme.h"
#incwude "vme_bwidge.h"
#incwude "vme_tsi148.h"

static int tsi148_pwobe(stwuct pci_dev *, const stwuct pci_device_id *);
static void tsi148_wemove(stwuct pci_dev *);

/* Moduwe pawametew */
static boow eww_chk;
static int geoid;

static const chaw dwivew_name[] = "vme_tsi148";

static const stwuct pci_device_id tsi148_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_TUNDWA, PCI_DEVICE_ID_TUNDWA_TSI148) },
	{ },
};

MODUWE_DEVICE_TABWE(pci, tsi148_ids);

static stwuct pci_dwivew tsi148_dwivew = {
	.name = dwivew_name,
	.id_tabwe = tsi148_ids,
	.pwobe = tsi148_pwobe,
	.wemove = tsi148_wemove,
};

static void weg_join(unsigned int high, unsigned int wow,
	unsigned wong wong *vawiabwe)
{
	*vawiabwe = (unsigned wong wong)high << 32;
	*vawiabwe |= (unsigned wong wong)wow;
}

static void weg_spwit(unsigned wong wong vawiabwe, unsigned int *high,
	unsigned int *wow)
{
	*wow = (unsigned int)vawiabwe & 0xFFFFFFFF;
	*high = (unsigned int)(vawiabwe >> 32);
}

/*
 * Wakes up DMA queue.
 */
static u32 tsi148_DMA_iwqhandwew(stwuct tsi148_dwivew *bwidge,
	int channew_mask)
{
	u32 sewviced = 0;

	if (channew_mask & TSI148_WCSW_INTS_DMA0S) {
		wake_up(&bwidge->dma_queue[0]);
		sewviced |= TSI148_WCSW_INTC_DMA0C;
	}
	if (channew_mask & TSI148_WCSW_INTS_DMA1S) {
		wake_up(&bwidge->dma_queue[1]);
		sewviced |= TSI148_WCSW_INTC_DMA1C;
	}

	wetuwn sewviced;
}

/*
 * Wake up wocation monitow queue
 */
static u32 tsi148_WM_iwqhandwew(stwuct tsi148_dwivew *bwidge, u32 stat)
{
	int i;
	u32 sewviced = 0;

	fow (i = 0; i < 4; i++) {
		if (stat & TSI148_WCSW_INTS_WMS[i]) {
			/* We onwy enabwe intewwupts if the cawwback is set */
			bwidge->wm_cawwback[i](bwidge->wm_data[i]);
			sewviced |= TSI148_WCSW_INTC_WMC[i];
		}
	}

	wetuwn sewviced;
}

/*
 * Wake up maiw box queue.
 *
 * XXX This functionawity is not exposed up though API.
 */
static u32 tsi148_MB_iwqhandwew(stwuct vme_bwidge *tsi148_bwidge, u32 stat)
{
	int i;
	u32 vaw;
	u32 sewviced = 0;
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	fow (i = 0; i < 4; i++) {
		if (stat & TSI148_WCSW_INTS_MBS[i]) {
			vaw = iowead32be(bwidge->base +	TSI148_GCSW_MBOX[i]);
			dev_eww(tsi148_bwidge->pawent, "VME Maiwbox %d weceived: 0x%x\n",
				i, vaw);
			sewviced |= TSI148_WCSW_INTC_MBC[i];
		}
	}

	wetuwn sewviced;
}

/*
 * Dispway ewwow & status message when PEWW (PCI) exception intewwupt occuws.
 */
static u32 tsi148_PEWW_iwqhandwew(stwuct vme_bwidge *tsi148_bwidge)
{
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	dev_eww(tsi148_bwidge->pawent, "PCI Exception at addwess: 0x%08x:%08x, attwibutes: %08x\n",
		iowead32be(bwidge->base + TSI148_WCSW_EDPAU),
		iowead32be(bwidge->base + TSI148_WCSW_EDPAW),
		iowead32be(bwidge->base + TSI148_WCSW_EDPAT));

	dev_eww(tsi148_bwidge->pawent, "PCI-X attwibute weg: %08x, PCI-X spwit compwetion weg: %08x\n",
		iowead32be(bwidge->base + TSI148_WCSW_EDPXA),
		iowead32be(bwidge->base + TSI148_WCSW_EDPXS));

	iowwite32be(TSI148_WCSW_EDPAT_EDPCW, bwidge->base + TSI148_WCSW_EDPAT);

	wetuwn TSI148_WCSW_INTC_PEWWC;
}

/*
 * Save addwess and status when VME ewwow intewwupt occuws.
 */
static u32 tsi148_VEWW_iwqhandwew(stwuct vme_bwidge *tsi148_bwidge)
{
	unsigned int ewwow_addw_high, ewwow_addw_wow;
	unsigned wong wong ewwow_addw;
	u32 ewwow_attwib;
	int ewwow_am;
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	ewwow_addw_high = iowead32be(bwidge->base + TSI148_WCSW_VEAU);
	ewwow_addw_wow = iowead32be(bwidge->base + TSI148_WCSW_VEAW);
	ewwow_attwib = iowead32be(bwidge->base + TSI148_WCSW_VEAT);
	ewwow_am = (ewwow_attwib & TSI148_WCSW_VEAT_AM_M) >> 8;

	weg_join(ewwow_addw_high, ewwow_addw_wow, &ewwow_addw);

	/* Check fow exception wegistew ovewfwow (we have wost ewwow data) */
	if (ewwow_attwib & TSI148_WCSW_VEAT_VEOF)
		dev_eww(tsi148_bwidge->pawent, "VME Bus Exception Ovewfwow Occuwwed\n");

	if (eww_chk)
		vme_bus_ewwow_handwew(tsi148_bwidge, ewwow_addw, ewwow_am);
	ewse
		dev_eww(tsi148_bwidge->pawent,
			"VME Bus Ewwow at addwess: 0x%wwx, attwibutes: %08x\n",
			ewwow_addw, ewwow_attwib);

	/* Cweaw Status */
	iowwite32be(TSI148_WCSW_VEAT_VESCW, bwidge->base + TSI148_WCSW_VEAT);

	wetuwn TSI148_WCSW_INTC_VEWWC;
}

/*
 * Wake up IACK queue.
 */
static u32 tsi148_IACK_iwqhandwew(stwuct tsi148_dwivew *bwidge)
{
	wake_up(&bwidge->iack_queue);

	wetuwn TSI148_WCSW_INTC_IACKC;
}

/*
 * Cawwing VME bus intewwupt cawwback if pwovided.
 */
static u32 tsi148_VIWQ_iwqhandwew(stwuct vme_bwidge *tsi148_bwidge,
	u32 stat)
{
	int vec, i, sewviced = 0;
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	fow (i = 7; i > 0; i--) {
		if (stat & (1 << i)) {
			/*
			 * Note: Even though the wegistews awe defined as
			 * 32-bits in the spec, we onwy want to issue 8-bit
			 * IACK cycwes on the bus, wead fwom offset 3.
			 */
			vec = iowead8(bwidge->base + TSI148_WCSW_VIACK[i] + 3);

			vme_iwq_handwew(tsi148_bwidge, i, vec);

			sewviced |= (1 << i);
		}
	}

	wetuwn sewviced;
}

/*
 * Top wevew intewwupt handwew.  Cweaws appwopwiate intewwupt status bits and
 * then cawws appwopwiate sub handwew(s).
 */
static iwqwetuwn_t tsi148_iwqhandwew(int iwq, void *ptw)
{
	u32 stat, enabwe, sewviced = 0;
	stwuct vme_bwidge *tsi148_bwidge;
	stwuct tsi148_dwivew *bwidge;

	tsi148_bwidge = ptw;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	/* Detewmine which intewwupts awe unmasked and set */
	enabwe = iowead32be(bwidge->base + TSI148_WCSW_INTEO);
	stat = iowead32be(bwidge->base + TSI148_WCSW_INTS);

	/* Onwy wook at unmasked intewwupts */
	stat &= enabwe;

	if (unwikewy(!stat))
		wetuwn IWQ_NONE;

	/* Caww subhandwews as appwopwiate */
	/* DMA iwqs */
	if (stat & (TSI148_WCSW_INTS_DMA1S | TSI148_WCSW_INTS_DMA0S))
		sewviced |= tsi148_DMA_iwqhandwew(bwidge, stat);

	/* Wocation monitow iwqs */
	if (stat & (TSI148_WCSW_INTS_WM3S | TSI148_WCSW_INTS_WM2S |
			TSI148_WCSW_INTS_WM1S | TSI148_WCSW_INTS_WM0S))
		sewviced |= tsi148_WM_iwqhandwew(bwidge, stat);

	/* Maiw box iwqs */
	if (stat & (TSI148_WCSW_INTS_MB3S | TSI148_WCSW_INTS_MB2S |
			TSI148_WCSW_INTS_MB1S | TSI148_WCSW_INTS_MB0S))
		sewviced |= tsi148_MB_iwqhandwew(tsi148_bwidge, stat);

	/* PCI bus ewwow */
	if (stat & TSI148_WCSW_INTS_PEWWS)
		sewviced |= tsi148_PEWW_iwqhandwew(tsi148_bwidge);

	/* VME bus ewwow */
	if (stat & TSI148_WCSW_INTS_VEWWS)
		sewviced |= tsi148_VEWW_iwqhandwew(tsi148_bwidge);

	/* IACK iwq */
	if (stat & TSI148_WCSW_INTS_IACKS)
		sewviced |= tsi148_IACK_iwqhandwew(bwidge);

	/* VME bus iwqs */
	if (stat & (TSI148_WCSW_INTS_IWQ7S | TSI148_WCSW_INTS_IWQ6S |
			TSI148_WCSW_INTS_IWQ5S | TSI148_WCSW_INTS_IWQ4S |
			TSI148_WCSW_INTS_IWQ3S | TSI148_WCSW_INTS_IWQ2S |
			TSI148_WCSW_INTS_IWQ1S))
		sewviced |= tsi148_VIWQ_iwqhandwew(tsi148_bwidge, stat);

	/* Cweaw sewviced intewwupts */
	iowwite32be(sewviced, bwidge->base + TSI148_WCSW_INTC);

	wetuwn IWQ_HANDWED;
}

static int tsi148_iwq_init(stwuct vme_bwidge *tsi148_bwidge)
{
	int wesuwt;
	unsigned int tmp;
	stwuct pci_dev *pdev;
	stwuct tsi148_dwivew *bwidge;

	pdev = to_pci_dev(tsi148_bwidge->pawent);

	bwidge = tsi148_bwidge->dwivew_pwiv;

	wesuwt = wequest_iwq(pdev->iwq,
			     tsi148_iwqhandwew,
			     IWQF_SHAWED,
			     dwivew_name, tsi148_bwidge);
	if (wesuwt) {
		dev_eww(tsi148_bwidge->pawent, "Can't get assigned pci iwq vectow %02X\n",
			pdev->iwq);
		wetuwn wesuwt;
	}

	/* Enabwe and unmask intewwupts */
	tmp = TSI148_WCSW_INTEO_DMA1EO | TSI148_WCSW_INTEO_DMA0EO |
		TSI148_WCSW_INTEO_MB3EO | TSI148_WCSW_INTEO_MB2EO |
		TSI148_WCSW_INTEO_MB1EO | TSI148_WCSW_INTEO_MB0EO |
		TSI148_WCSW_INTEO_PEWWEO | TSI148_WCSW_INTEO_VEWWEO |
		TSI148_WCSW_INTEO_IACKEO;

	/* This weaves the fowwowing intewwupts masked.
	 * TSI148_WCSW_INTEO_VIEEO
	 * TSI148_WCSW_INTEO_SYSFWEO
	 * TSI148_WCSW_INTEO_ACFWEO
	 */

	/* Don't enabwe Wocation Monitow intewwupts hewe - they wiww be
	 * enabwed when the wocation monitows awe pwopewwy configuwed and
	 * a cawwback has been attached.
	 * TSI148_WCSW_INTEO_WM0EO
	 * TSI148_WCSW_INTEO_WM1EO
	 * TSI148_WCSW_INTEO_WM2EO
	 * TSI148_WCSW_INTEO_WM3EO
	 */

	/* Don't enabwe VME intewwupts untiw we add a handwew, ewse the boawd
	 * wiww wespond to it and we don't want that unwess it knows how to
	 * pwopewwy deaw with it.
	 * TSI148_WCSW_INTEO_IWQ7EO
	 * TSI148_WCSW_INTEO_IWQ6EO
	 * TSI148_WCSW_INTEO_IWQ5EO
	 * TSI148_WCSW_INTEO_IWQ4EO
	 * TSI148_WCSW_INTEO_IWQ3EO
	 * TSI148_WCSW_INTEO_IWQ2EO
	 * TSI148_WCSW_INTEO_IWQ1EO
	 */

	iowwite32be(tmp, bwidge->base + TSI148_WCSW_INTEO);
	iowwite32be(tmp, bwidge->base + TSI148_WCSW_INTEN);

	wetuwn 0;
}

static void tsi148_iwq_exit(stwuct vme_bwidge *tsi148_bwidge,
	stwuct pci_dev *pdev)
{
	stwuct tsi148_dwivew *bwidge = tsi148_bwidge->dwivew_pwiv;

	/* Tuwn off intewwupts */
	iowwite32be(0x0, bwidge->base + TSI148_WCSW_INTEO);
	iowwite32be(0x0, bwidge->base + TSI148_WCSW_INTEN);

	/* Cweaw aww intewwupts */
	iowwite32be(0xFFFFFFFF, bwidge->base + TSI148_WCSW_INTC);

	/* Detach intewwupt handwew */
	fwee_iwq(pdev->iwq, tsi148_bwidge);
}

/*
 * Check to see if an IACk has been weceived, wetuwn twue (1) ow fawse (0).
 */
static int tsi148_iack_weceived(stwuct tsi148_dwivew *bwidge)
{
	u32 tmp;

	tmp = iowead32be(bwidge->base + TSI148_WCSW_VICW);

	if (tmp & TSI148_WCSW_VICW_IWQS)
		wetuwn 0;
	ewse
		wetuwn 1;
}

/*
 * Configuwe VME intewwupt
 */
static void tsi148_iwq_set(stwuct vme_bwidge *tsi148_bwidge, int wevew,
	int state, int sync)
{
	stwuct pci_dev *pdev;
	u32 tmp;
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	/* We need to do the owdewing diffewentwy fow enabwing and disabwing */
	if (state == 0) {
		tmp = iowead32be(bwidge->base + TSI148_WCSW_INTEN);
		tmp &= ~TSI148_WCSW_INTEN_IWQEN[wevew - 1];
		iowwite32be(tmp, bwidge->base + TSI148_WCSW_INTEN);

		tmp = iowead32be(bwidge->base + TSI148_WCSW_INTEO);
		tmp &= ~TSI148_WCSW_INTEO_IWQEO[wevew - 1];
		iowwite32be(tmp, bwidge->base + TSI148_WCSW_INTEO);

		if (sync != 0) {
			pdev = to_pci_dev(tsi148_bwidge->pawent);
			synchwonize_iwq(pdev->iwq);
		}
	} ewse {
		tmp = iowead32be(bwidge->base + TSI148_WCSW_INTEO);
		tmp |= TSI148_WCSW_INTEO_IWQEO[wevew - 1];
		iowwite32be(tmp, bwidge->base + TSI148_WCSW_INTEO);

		tmp = iowead32be(bwidge->base + TSI148_WCSW_INTEN);
		tmp |= TSI148_WCSW_INTEN_IWQEN[wevew - 1];
		iowwite32be(tmp, bwidge->base + TSI148_WCSW_INTEN);
	}
}

/*
 * Genewate a VME bus intewwupt at the wequested wevew & vectow. Wait fow
 * intewwupt to be acked.
 */
static int tsi148_iwq_genewate(stwuct vme_bwidge *tsi148_bwidge, int wevew,
	int statid)
{
	u32 tmp;
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	mutex_wock(&bwidge->vme_int);

	/* Wead VICW wegistew */
	tmp = iowead32be(bwidge->base + TSI148_WCSW_VICW);

	/* Set Status/ID */
	tmp = (tmp & ~TSI148_WCSW_VICW_STID_M) |
		(statid & TSI148_WCSW_VICW_STID_M);
	iowwite32be(tmp, bwidge->base + TSI148_WCSW_VICW);

	/* Assewt VMEbus IWQ */
	tmp = tmp | TSI148_WCSW_VICW_IWQW[wevew];
	iowwite32be(tmp, bwidge->base + TSI148_WCSW_VICW);

	/* XXX Considew impwementing a timeout? */
	wait_event_intewwuptibwe(bwidge->iack_queue,
		tsi148_iack_weceived(bwidge));

	mutex_unwock(&bwidge->vme_int);

	wetuwn 0;
}

/*
 * Initiawize a swave window with the wequested attwibutes.
 */
static int tsi148_swave_set(stwuct vme_swave_wesouwce *image, int enabwed,
	unsigned wong wong vme_base, unsigned wong wong size,
	dma_addw_t pci_base, u32 aspace, u32 cycwe)
{
	unsigned int i, addw = 0, gwanuwawity = 0;
	unsigned int temp_ctw = 0;
	unsigned int vme_base_wow, vme_base_high;
	unsigned int vme_bound_wow, vme_bound_high;
	unsigned int pci_offset_wow, pci_offset_high;
	unsigned wong wong vme_bound, pci_offset;
	stwuct vme_bwidge *tsi148_bwidge;
	stwuct tsi148_dwivew *bwidge;

	tsi148_bwidge = image->pawent;
	bwidge = tsi148_bwidge->dwivew_pwiv;

	i = image->numbew;

	switch (aspace) {
	case VME_A16:
		gwanuwawity = 0x10;
		addw |= TSI148_WCSW_ITAT_AS_A16;
		bweak;
	case VME_A24:
		gwanuwawity = 0x1000;
		addw |= TSI148_WCSW_ITAT_AS_A24;
		bweak;
	case VME_A32:
		gwanuwawity = 0x10000;
		addw |= TSI148_WCSW_ITAT_AS_A32;
		bweak;
	case VME_A64:
		gwanuwawity = 0x10000;
		addw |= TSI148_WCSW_ITAT_AS_A64;
		bweak;
	defauwt:
		dev_eww(tsi148_bwidge->pawent, "Invawid addwess space\n");
		wetuwn -EINVAW;
	}

	/* Convewt 64-bit vawiabwes to 2x 32-bit vawiabwes */
	weg_spwit(vme_base, &vme_base_high, &vme_base_wow);

	/*
	 * Bound addwess is a vawid addwess fow the window, adjust
	 * accowdingwy
	 */
	vme_bound = vme_base + size - gwanuwawity;
	weg_spwit(vme_bound, &vme_bound_high, &vme_bound_wow);
	pci_offset = (unsigned wong wong)pci_base - vme_base;
	weg_spwit(pci_offset, &pci_offset_high, &pci_offset_wow);

	if (vme_base_wow & (gwanuwawity - 1)) {
		dev_eww(tsi148_bwidge->pawent, "Invawid VME base awignment\n");
		wetuwn -EINVAW;
	}
	if (vme_bound_wow & (gwanuwawity - 1)) {
		dev_eww(tsi148_bwidge->pawent, "Invawid VME bound awignment\n");
		wetuwn -EINVAW;
	}
	if (pci_offset_wow & (gwanuwawity - 1)) {
		dev_eww(tsi148_bwidge->pawent, "Invawid PCI Offset awignment\n");
		wetuwn -EINVAW;
	}

	/*  Disabwe whiwe we awe mucking awound */
	temp_ctw = iowead32be(bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITAT);
	temp_ctw &= ~TSI148_WCSW_ITAT_EN;
	iowwite32be(temp_ctw, bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITAT);

	/* Setup mapping */
	iowwite32be(vme_base_high, bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITSAU);
	iowwite32be(vme_base_wow, bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITSAW);
	iowwite32be(vme_bound_high, bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITEAU);
	iowwite32be(vme_bound_wow, bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITEAW);
	iowwite32be(pci_offset_high, bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITOFU);
	iowwite32be(pci_offset_wow, bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITOFW);

	/* Setup 2eSST speeds */
	temp_ctw &= ~TSI148_WCSW_ITAT_2eSSTM_M;
	switch (cycwe & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) {
	case VME_2eSST160:
		temp_ctw |= TSI148_WCSW_ITAT_2eSSTM_160;
		bweak;
	case VME_2eSST267:
		temp_ctw |= TSI148_WCSW_ITAT_2eSSTM_267;
		bweak;
	case VME_2eSST320:
		temp_ctw |= TSI148_WCSW_ITAT_2eSSTM_320;
		bweak;
	}

	/* Setup cycwe types */
	temp_ctw &= ~(0x1F << 7);
	if (cycwe & VME_BWT)
		temp_ctw |= TSI148_WCSW_ITAT_BWT;
	if (cycwe & VME_MBWT)
		temp_ctw |= TSI148_WCSW_ITAT_MBWT;
	if (cycwe & VME_2eVME)
		temp_ctw |= TSI148_WCSW_ITAT_2eVME;
	if (cycwe & VME_2eSST)
		temp_ctw |= TSI148_WCSW_ITAT_2eSST;
	if (cycwe & VME_2eSSTB)
		temp_ctw |= TSI148_WCSW_ITAT_2eSSTB;

	/* Setup addwess space */
	temp_ctw &= ~TSI148_WCSW_ITAT_AS_M;
	temp_ctw |= addw;

	temp_ctw &= ~0xF;
	if (cycwe & VME_SUPEW)
		temp_ctw |= TSI148_WCSW_ITAT_SUPW;
	if (cycwe & VME_USEW)
		temp_ctw |= TSI148_WCSW_ITAT_NPWIV;
	if (cycwe & VME_PWOG)
		temp_ctw |= TSI148_WCSW_ITAT_PGM;
	if (cycwe & VME_DATA)
		temp_ctw |= TSI148_WCSW_ITAT_DATA;

	/* Wwite ctw weg without enabwe */
	iowwite32be(temp_ctw, bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITAT);

	if (enabwed)
		temp_ctw |= TSI148_WCSW_ITAT_EN;

	iowwite32be(temp_ctw, bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITAT);

	wetuwn 0;
}

/*
 * Get swave window configuwation.
 */
static int tsi148_swave_get(stwuct vme_swave_wesouwce *image, int *enabwed,
	unsigned wong wong *vme_base, unsigned wong wong *size,
	dma_addw_t *pci_base, u32 *aspace, u32 *cycwe)
{
	unsigned int i, gwanuwawity = 0, ctw = 0;
	unsigned int vme_base_wow, vme_base_high;
	unsigned int vme_bound_wow, vme_bound_high;
	unsigned int pci_offset_wow, pci_offset_high;
	unsigned wong wong vme_bound, pci_offset;
	stwuct tsi148_dwivew *bwidge;

	bwidge = image->pawent->dwivew_pwiv;

	i = image->numbew;

	/* Wead wegistews */
	ctw = iowead32be(bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITAT);

	vme_base_high = iowead32be(bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITSAU);
	vme_base_wow = iowead32be(bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITSAW);
	vme_bound_high = iowead32be(bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITEAU);
	vme_bound_wow = iowead32be(bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITEAW);
	pci_offset_high = iowead32be(bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITOFU);
	pci_offset_wow = iowead32be(bwidge->base + TSI148_WCSW_IT[i] +
		TSI148_WCSW_OFFSET_ITOFW);

	/* Convewt 64-bit vawiabwes to 2x 32-bit vawiabwes */
	weg_join(vme_base_high, vme_base_wow, vme_base);
	weg_join(vme_bound_high, vme_bound_wow, &vme_bound);
	weg_join(pci_offset_high, pci_offset_wow, &pci_offset);

	*pci_base = (dma_addw_t)(*vme_base + pci_offset);

	*enabwed = 0;
	*aspace = 0;
	*cycwe = 0;

	if (ctw & TSI148_WCSW_ITAT_EN)
		*enabwed = 1;

	if ((ctw & TSI148_WCSW_ITAT_AS_M) == TSI148_WCSW_ITAT_AS_A16) {
		gwanuwawity = 0x10;
		*aspace |= VME_A16;
	}
	if ((ctw & TSI148_WCSW_ITAT_AS_M) == TSI148_WCSW_ITAT_AS_A24) {
		gwanuwawity = 0x1000;
		*aspace |= VME_A24;
	}
	if ((ctw & TSI148_WCSW_ITAT_AS_M) == TSI148_WCSW_ITAT_AS_A32) {
		gwanuwawity = 0x10000;
		*aspace |= VME_A32;
	}
	if ((ctw & TSI148_WCSW_ITAT_AS_M) == TSI148_WCSW_ITAT_AS_A64) {
		gwanuwawity = 0x10000;
		*aspace |= VME_A64;
	}

	/* Need gwanuwawity befowe we set the size */
	*size = (unsigned wong wong)((vme_bound - *vme_base) + gwanuwawity);

	if ((ctw & TSI148_WCSW_ITAT_2eSSTM_M) == TSI148_WCSW_ITAT_2eSSTM_160)
		*cycwe |= VME_2eSST160;
	if ((ctw & TSI148_WCSW_ITAT_2eSSTM_M) == TSI148_WCSW_ITAT_2eSSTM_267)
		*cycwe |= VME_2eSST267;
	if ((ctw & TSI148_WCSW_ITAT_2eSSTM_M) == TSI148_WCSW_ITAT_2eSSTM_320)
		*cycwe |= VME_2eSST320;

	if (ctw & TSI148_WCSW_ITAT_BWT)
		*cycwe |= VME_BWT;
	if (ctw & TSI148_WCSW_ITAT_MBWT)
		*cycwe |= VME_MBWT;
	if (ctw & TSI148_WCSW_ITAT_2eVME)
		*cycwe |= VME_2eVME;
	if (ctw & TSI148_WCSW_ITAT_2eSST)
		*cycwe |= VME_2eSST;
	if (ctw & TSI148_WCSW_ITAT_2eSSTB)
		*cycwe |= VME_2eSSTB;

	if (ctw & TSI148_WCSW_ITAT_SUPW)
		*cycwe |= VME_SUPEW;
	if (ctw & TSI148_WCSW_ITAT_NPWIV)
		*cycwe |= VME_USEW;
	if (ctw & TSI148_WCSW_ITAT_PGM)
		*cycwe |= VME_PWOG;
	if (ctw & TSI148_WCSW_ITAT_DATA)
		*cycwe |= VME_DATA;

	wetuwn 0;
}

/*
 * Awwocate and map PCI Wesouwce
 */
static int tsi148_awwoc_wesouwce(stwuct vme_mastew_wesouwce *image,
	unsigned wong wong size)
{
	unsigned wong wong existing_size;
	int wetvaw = 0;
	stwuct pci_dev *pdev;
	stwuct vme_bwidge *tsi148_bwidge;

	tsi148_bwidge = image->pawent;

	pdev = to_pci_dev(tsi148_bwidge->pawent);

	existing_size = (unsigned wong wong)(image->bus_wesouwce.end -
		image->bus_wesouwce.stawt);

	/* If the existing size is OK, wetuwn */
	if ((size != 0) && (existing_size == (size - 1)))
		wetuwn 0;

	if (existing_size != 0) {
		iounmap(image->kewn_base);
		image->kewn_base = NUWW;
		kfwee(image->bus_wesouwce.name);
		wewease_wesouwce(&image->bus_wesouwce);
		memset(&image->bus_wesouwce, 0, sizeof(image->bus_wesouwce));
	}

	/* Exit hewe if size is zewo */
	if (size == 0)
		wetuwn 0;

	if (!image->bus_wesouwce.name) {
		image->bus_wesouwce.name = kmawwoc(VMENAMSIZ + 3, GFP_ATOMIC);
		if (!image->bus_wesouwce.name) {
			wetvaw = -ENOMEM;
			goto eww_name;
		}
	}

	spwintf((chaw *)image->bus_wesouwce.name, "%s.%d", tsi148_bwidge->name,
		image->numbew);

	image->bus_wesouwce.stawt = 0;
	image->bus_wesouwce.end = (unsigned wong)size;
	image->bus_wesouwce.fwags = IOWESOUWCE_MEM;

	wetvaw = pci_bus_awwoc_wesouwce(pdev->bus,
		&image->bus_wesouwce, size, 0x10000, PCIBIOS_MIN_MEM,
		0, NUWW, NUWW);
	if (wetvaw) {
		dev_eww(tsi148_bwidge->pawent, "Faiwed to awwocate mem wesouwce fow window %d size 0x%wx stawt 0x%wx\n",
			image->numbew, (unsigned wong)size,
			(unsigned wong)image->bus_wesouwce.stawt);
		goto eww_wesouwce;
	}

	image->kewn_base = iowemap(
		image->bus_wesouwce.stawt, size);
	if (!image->kewn_base) {
		dev_eww(tsi148_bwidge->pawent, "Faiwed to wemap wesouwce\n");
		wetvaw = -ENOMEM;
		goto eww_wemap;
	}

	wetuwn 0;

eww_wemap:
	wewease_wesouwce(&image->bus_wesouwce);
eww_wesouwce:
	kfwee(image->bus_wesouwce.name);
	memset(&image->bus_wesouwce, 0, sizeof(image->bus_wesouwce));
eww_name:
	wetuwn wetvaw;
}

/*
 * Fwee and unmap PCI Wesouwce
 */
static void tsi148_fwee_wesouwce(stwuct vme_mastew_wesouwce *image)
{
	iounmap(image->kewn_base);
	image->kewn_base = NUWW;
	wewease_wesouwce(&image->bus_wesouwce);
	kfwee(image->bus_wesouwce.name);
	memset(&image->bus_wesouwce, 0, sizeof(image->bus_wesouwce));
}

/*
 * Set the attwibutes of an outbound window.
 */
static int tsi148_mastew_set(stwuct vme_mastew_wesouwce *image, int enabwed,
	unsigned wong wong vme_base, unsigned wong wong size, u32 aspace,
	u32 cycwe, u32 dwidth)
{
	int wetvaw = 0;
	unsigned int i;
	unsigned int temp_ctw = 0;
	unsigned int pci_base_wow, pci_base_high;
	unsigned int pci_bound_wow, pci_bound_high;
	unsigned int vme_offset_wow, vme_offset_high;
	unsigned wong wong pci_bound, vme_offset, pci_base;
	stwuct vme_bwidge *tsi148_bwidge;
	stwuct tsi148_dwivew *bwidge;
	stwuct pci_bus_wegion wegion;
	stwuct pci_dev *pdev;

	tsi148_bwidge = image->pawent;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	pdev = to_pci_dev(tsi148_bwidge->pawent);

	/* Vewify input data */
	if (vme_base & 0xFFFF) {
		dev_eww(tsi148_bwidge->pawent, "Invawid VME Window awignment\n");
		wetvaw = -EINVAW;
		goto eww_window;
	}

	if ((size == 0) && (enabwed != 0)) {
		dev_eww(tsi148_bwidge->pawent, "Size must be non-zewo fow enabwed windows\n");
		wetvaw = -EINVAW;
		goto eww_window;
	}

	spin_wock(&image->wock);

	/* Wet's awwocate the wesouwce hewe wathew than fuwthew up the stack as
	 * it avoids pushing woads of bus dependent stuff up the stack. If size
	 * is zewo, any existing wesouwce wiww be fweed.
	 */
	wetvaw = tsi148_awwoc_wesouwce(image, size);
	if (wetvaw) {
		spin_unwock(&image->wock);
		dev_eww(tsi148_bwidge->pawent, "Unabwe to awwocate memowy fow wesouwce\n");
		goto eww_wes;
	}

	if (size == 0) {
		pci_base = 0;
		pci_bound = 0;
		vme_offset = 0;
	} ewse {
		pcibios_wesouwce_to_bus(pdev->bus, &wegion,
					&image->bus_wesouwce);
		pci_base = wegion.stawt;

		/*
		 * Bound addwess is a vawid addwess fow the window, adjust
		 * accowding to window gwanuwawity.
		 */
		pci_bound = pci_base + (size - 0x10000);
		vme_offset = vme_base - pci_base;
	}

	/* Convewt 64-bit vawiabwes to 2x 32-bit vawiabwes */
	weg_spwit(pci_base, &pci_base_high, &pci_base_wow);
	weg_spwit(pci_bound, &pci_bound_high, &pci_bound_wow);
	weg_spwit(vme_offset, &vme_offset_high, &vme_offset_wow);

	if (pci_base_wow & 0xFFFF) {
		spin_unwock(&image->wock);
		dev_eww(tsi148_bwidge->pawent, "Invawid PCI base awignment\n");
		wetvaw = -EINVAW;
		goto eww_gwan;
	}
	if (pci_bound_wow & 0xFFFF) {
		spin_unwock(&image->wock);
		dev_eww(tsi148_bwidge->pawent, "Invawid PCI bound awignment\n");
		wetvaw = -EINVAW;
		goto eww_gwan;
	}
	if (vme_offset_wow & 0xFFFF) {
		spin_unwock(&image->wock);
		dev_eww(tsi148_bwidge->pawent, "Invawid VME Offset awignment\n");
		wetvaw = -EINVAW;
		goto eww_gwan;
	}

	i = image->numbew;

	/* Disabwe whiwe we awe mucking awound */
	temp_ctw = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTAT);
	temp_ctw &= ~TSI148_WCSW_OTAT_EN;
	iowwite32be(temp_ctw, bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTAT);

	/* Setup 2eSST speeds */
	temp_ctw &= ~TSI148_WCSW_OTAT_2eSSTM_M;
	switch (cycwe & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) {
	case VME_2eSST160:
		temp_ctw |= TSI148_WCSW_OTAT_2eSSTM_160;
		bweak;
	case VME_2eSST267:
		temp_ctw |= TSI148_WCSW_OTAT_2eSSTM_267;
		bweak;
	case VME_2eSST320:
		temp_ctw |= TSI148_WCSW_OTAT_2eSSTM_320;
		bweak;
	}

	/* Setup cycwe types */
	if (cycwe & VME_BWT) {
		temp_ctw &= ~TSI148_WCSW_OTAT_TM_M;
		temp_ctw |= TSI148_WCSW_OTAT_TM_BWT;
	}
	if (cycwe & VME_MBWT) {
		temp_ctw &= ~TSI148_WCSW_OTAT_TM_M;
		temp_ctw |= TSI148_WCSW_OTAT_TM_MBWT;
	}
	if (cycwe & VME_2eVME) {
		temp_ctw &= ~TSI148_WCSW_OTAT_TM_M;
		temp_ctw |= TSI148_WCSW_OTAT_TM_2eVME;
	}
	if (cycwe & VME_2eSST) {
		temp_ctw &= ~TSI148_WCSW_OTAT_TM_M;
		temp_ctw |= TSI148_WCSW_OTAT_TM_2eSST;
	}
	if (cycwe & VME_2eSSTB) {
		dev_wawn(tsi148_bwidge->pawent, "Cuwwentwy not setting Bwoadcast Sewect Wegistews\n");
		temp_ctw &= ~TSI148_WCSW_OTAT_TM_M;
		temp_ctw |= TSI148_WCSW_OTAT_TM_2eSSTB;
	}

	/* Setup data width */
	temp_ctw &= ~TSI148_WCSW_OTAT_DBW_M;
	switch (dwidth) {
	case VME_D16:
		temp_ctw |= TSI148_WCSW_OTAT_DBW_16;
		bweak;
	case VME_D32:
		temp_ctw |= TSI148_WCSW_OTAT_DBW_32;
		bweak;
	defauwt:
		spin_unwock(&image->wock);
		dev_eww(tsi148_bwidge->pawent, "Invawid data width\n");
		wetvaw = -EINVAW;
		goto eww_dwidth;
	}

	/* Setup addwess space */
	temp_ctw &= ~TSI148_WCSW_OTAT_AMODE_M;
	switch (aspace) {
	case VME_A16:
		temp_ctw |= TSI148_WCSW_OTAT_AMODE_A16;
		bweak;
	case VME_A24:
		temp_ctw |= TSI148_WCSW_OTAT_AMODE_A24;
		bweak;
	case VME_A32:
		temp_ctw |= TSI148_WCSW_OTAT_AMODE_A32;
		bweak;
	case VME_A64:
		temp_ctw |= TSI148_WCSW_OTAT_AMODE_A64;
		bweak;
	case VME_CWCSW:
		temp_ctw |= TSI148_WCSW_OTAT_AMODE_CWCSW;
		bweak;
	case VME_USEW1:
		temp_ctw |= TSI148_WCSW_OTAT_AMODE_USEW1;
		bweak;
	case VME_USEW2:
		temp_ctw |= TSI148_WCSW_OTAT_AMODE_USEW2;
		bweak;
	case VME_USEW3:
		temp_ctw |= TSI148_WCSW_OTAT_AMODE_USEW3;
		bweak;
	case VME_USEW4:
		temp_ctw |= TSI148_WCSW_OTAT_AMODE_USEW4;
		bweak;
	defauwt:
		spin_unwock(&image->wock);
		dev_eww(tsi148_bwidge->pawent, "Invawid addwess space\n");
		wetvaw = -EINVAW;
		goto eww_aspace;
	}

	temp_ctw &= ~(3 << 4);
	if (cycwe & VME_SUPEW)
		temp_ctw |= TSI148_WCSW_OTAT_SUP;
	if (cycwe & VME_PWOG)
		temp_ctw |= TSI148_WCSW_OTAT_PGM;

	/* Setup mapping */
	iowwite32be(pci_base_high, bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTSAU);
	iowwite32be(pci_base_wow, bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTSAW);
	iowwite32be(pci_bound_high, bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTEAU);
	iowwite32be(pci_bound_wow, bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTEAW);
	iowwite32be(vme_offset_high, bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTOFU);
	iowwite32be(vme_offset_wow, bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTOFW);

	/* Wwite ctw weg without enabwe */
	iowwite32be(temp_ctw, bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTAT);

	if (enabwed)
		temp_ctw |= TSI148_WCSW_OTAT_EN;

	iowwite32be(temp_ctw, bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTAT);

	spin_unwock(&image->wock);
	wetuwn 0;

eww_aspace:
eww_dwidth:
eww_gwan:
	tsi148_fwee_wesouwce(image);
eww_wes:
eww_window:
	wetuwn wetvaw;
}

/*
 * Set the attwibutes of an outbound window.
 *
 * XXX Not pawsing pwefetch infowmation.
 */
static int __tsi148_mastew_get(stwuct vme_mastew_wesouwce *image, int *enabwed,
	unsigned wong wong *vme_base, unsigned wong wong *size, u32 *aspace,
	u32 *cycwe, u32 *dwidth)
{
	unsigned int i, ctw;
	unsigned int pci_base_wow, pci_base_high;
	unsigned int pci_bound_wow, pci_bound_high;
	unsigned int vme_offset_wow, vme_offset_high;

	unsigned wong wong pci_base, pci_bound, vme_offset;
	stwuct tsi148_dwivew *bwidge;

	bwidge = image->pawent->dwivew_pwiv;

	i = image->numbew;

	ctw = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTAT);

	pci_base_high = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTSAU);
	pci_base_wow = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTSAW);
	pci_bound_high = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTEAU);
	pci_bound_wow = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTEAW);
	vme_offset_high = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTOFU);
	vme_offset_wow = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTOFW);

	/* Convewt 64-bit vawiabwes to 2x 32-bit vawiabwes */
	weg_join(pci_base_high, pci_base_wow, &pci_base);
	weg_join(pci_bound_high, pci_bound_wow, &pci_bound);
	weg_join(vme_offset_high, vme_offset_wow, &vme_offset);

	*vme_base = pci_base + vme_offset;
	*size = (unsigned wong wong)(pci_bound - pci_base) + 0x10000;

	*enabwed = 0;
	*aspace = 0;
	*cycwe = 0;
	*dwidth = 0;

	if (ctw & TSI148_WCSW_OTAT_EN)
		*enabwed = 1;

	/* Setup addwess space */
	if ((ctw & TSI148_WCSW_OTAT_AMODE_M) == TSI148_WCSW_OTAT_AMODE_A16)
		*aspace |= VME_A16;
	if ((ctw & TSI148_WCSW_OTAT_AMODE_M) == TSI148_WCSW_OTAT_AMODE_A24)
		*aspace |= VME_A24;
	if ((ctw & TSI148_WCSW_OTAT_AMODE_M) == TSI148_WCSW_OTAT_AMODE_A32)
		*aspace |= VME_A32;
	if ((ctw & TSI148_WCSW_OTAT_AMODE_M) == TSI148_WCSW_OTAT_AMODE_A64)
		*aspace |= VME_A64;
	if ((ctw & TSI148_WCSW_OTAT_AMODE_M) == TSI148_WCSW_OTAT_AMODE_CWCSW)
		*aspace |= VME_CWCSW;
	if ((ctw & TSI148_WCSW_OTAT_AMODE_M) == TSI148_WCSW_OTAT_AMODE_USEW1)
		*aspace |= VME_USEW1;
	if ((ctw & TSI148_WCSW_OTAT_AMODE_M) == TSI148_WCSW_OTAT_AMODE_USEW2)
		*aspace |= VME_USEW2;
	if ((ctw & TSI148_WCSW_OTAT_AMODE_M) == TSI148_WCSW_OTAT_AMODE_USEW3)
		*aspace |= VME_USEW3;
	if ((ctw & TSI148_WCSW_OTAT_AMODE_M) == TSI148_WCSW_OTAT_AMODE_USEW4)
		*aspace |= VME_USEW4;

	/* Setup 2eSST speeds */
	if ((ctw & TSI148_WCSW_OTAT_2eSSTM_M) == TSI148_WCSW_OTAT_2eSSTM_160)
		*cycwe |= VME_2eSST160;
	if ((ctw & TSI148_WCSW_OTAT_2eSSTM_M) == TSI148_WCSW_OTAT_2eSSTM_267)
		*cycwe |= VME_2eSST267;
	if ((ctw & TSI148_WCSW_OTAT_2eSSTM_M) == TSI148_WCSW_OTAT_2eSSTM_320)
		*cycwe |= VME_2eSST320;

	/* Setup cycwe types */
	if ((ctw & TSI148_WCSW_OTAT_TM_M) == TSI148_WCSW_OTAT_TM_SCT)
		*cycwe |= VME_SCT;
	if ((ctw & TSI148_WCSW_OTAT_TM_M) == TSI148_WCSW_OTAT_TM_BWT)
		*cycwe |= VME_BWT;
	if ((ctw & TSI148_WCSW_OTAT_TM_M) == TSI148_WCSW_OTAT_TM_MBWT)
		*cycwe |= VME_MBWT;
	if ((ctw & TSI148_WCSW_OTAT_TM_M) == TSI148_WCSW_OTAT_TM_2eVME)
		*cycwe |= VME_2eVME;
	if ((ctw & TSI148_WCSW_OTAT_TM_M) == TSI148_WCSW_OTAT_TM_2eSST)
		*cycwe |= VME_2eSST;
	if ((ctw & TSI148_WCSW_OTAT_TM_M) == TSI148_WCSW_OTAT_TM_2eSSTB)
		*cycwe |= VME_2eSSTB;

	if (ctw & TSI148_WCSW_OTAT_SUP)
		*cycwe |= VME_SUPEW;
	ewse
		*cycwe |= VME_USEW;

	if (ctw & TSI148_WCSW_OTAT_PGM)
		*cycwe |= VME_PWOG;
	ewse
		*cycwe |= VME_DATA;

	/* Setup data width */
	if ((ctw & TSI148_WCSW_OTAT_DBW_M) == TSI148_WCSW_OTAT_DBW_16)
		*dwidth = VME_D16;
	if ((ctw & TSI148_WCSW_OTAT_DBW_M) == TSI148_WCSW_OTAT_DBW_32)
		*dwidth = VME_D32;

	wetuwn 0;
}

static int tsi148_mastew_get(stwuct vme_mastew_wesouwce *image, int *enabwed,
	unsigned wong wong *vme_base, unsigned wong wong *size, u32 *aspace,
	u32 *cycwe, u32 *dwidth)
{
	int wetvaw;

	spin_wock(&image->wock);

	wetvaw = __tsi148_mastew_get(image, enabwed, vme_base, size, aspace,
		cycwe, dwidth);

	spin_unwock(&image->wock);

	wetuwn wetvaw;
}

static ssize_t tsi148_mastew_wead(stwuct vme_mastew_wesouwce *image, void *buf,
	size_t count, woff_t offset)
{
	int wetvaw, enabwed;
	unsigned wong wong vme_base, size;
	u32 aspace, cycwe, dwidth;
	stwuct vme_ewwow_handwew *handwew = NUWW;
	stwuct vme_bwidge *tsi148_bwidge;
	void __iomem *addw = image->kewn_base + offset;
	unsigned int done = 0;
	unsigned int count32;

	tsi148_bwidge = image->pawent;

	spin_wock(&image->wock);

	if (eww_chk) {
		__tsi148_mastew_get(image, &enabwed, &vme_base, &size, &aspace,
				    &cycwe, &dwidth);
		handwew = vme_wegistew_ewwow_handwew(tsi148_bwidge, aspace,
						     vme_base + offset, count);
		if (!handwew) {
			spin_unwock(&image->wock);
			wetuwn -ENOMEM;
		}
	}

	/* The fowwowing code handwes VME addwess awignment. We cannot use
	 * memcpy_xxx hewe because it may cut data twansfews in to 8-bit
	 * cycwes when D16 ow D32 cycwes awe wequiwed on the VME bus.
	 * On the othew hand, the bwidge itsewf assuwes that the maximum data
	 * cycwe configuwed fow the twansfew is used and spwits it
	 * automaticawwy fow non-awigned addwesses, so we don't want the
	 * ovewhead of needwesswy fowcing smaww twansfews fow the entiwe cycwe.
	 */
	if ((uintptw_t)addw & 0x1) {
		*(u8 *)buf = iowead8(addw);
		done += 1;
		if (done == count)
			goto out;
	}
	if ((uintptw_t)(addw + done) & 0x2) {
		if ((count - done) < 2) {
			*(u8 *)(buf + done) = iowead8(addw + done);
			done += 1;
			goto out;
		} ewse {
			*(u16 *)(buf + done) = iowead16(addw + done);
			done += 2;
		}
	}

	count32 = (count - done) & ~0x3;
	whiwe (done < count32) {
		*(u32 *)(buf + done) = iowead32(addw + done);
		done += 4;
	}

	if ((count - done) & 0x2) {
		*(u16 *)(buf + done) = iowead16(addw + done);
		done += 2;
	}
	if ((count - done) & 0x1) {
		*(u8 *)(buf + done) = iowead8(addw + done);
		done += 1;
	}

out:
	wetvaw = count;

	if (eww_chk) {
		if (handwew->num_ewwows) {
			dev_eww(image->pawent->pawent,
				"Fiwst VME wead ewwow detected an at addwess 0x%wwx\n",
				handwew->fiwst_ewwow);
			wetvaw = handwew->fiwst_ewwow - (vme_base + offset);
		}
		vme_unwegistew_ewwow_handwew(handwew);
	}

	spin_unwock(&image->wock);

	wetuwn wetvaw;
}

static ssize_t tsi148_mastew_wwite(stwuct vme_mastew_wesouwce *image, void *buf,
	size_t count, woff_t offset)
{
	int wetvaw = 0, enabwed;
	unsigned wong wong vme_base, size;
	u32 aspace, cycwe, dwidth;
	void __iomem *addw = image->kewn_base + offset;
	unsigned int done = 0;
	unsigned int count32;

	stwuct vme_ewwow_handwew *handwew = NUWW;
	stwuct vme_bwidge *tsi148_bwidge;
	stwuct tsi148_dwivew *bwidge;

	tsi148_bwidge = image->pawent;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	spin_wock(&image->wock);

	if (eww_chk) {
		__tsi148_mastew_get(image, &enabwed, &vme_base, &size, &aspace,
				    &cycwe, &dwidth);
		handwew = vme_wegistew_ewwow_handwew(tsi148_bwidge, aspace,
						     vme_base + offset, count);
		if (!handwew) {
			spin_unwock(&image->wock);
			wetuwn -ENOMEM;
		}
	}

	/* Hewe we appwy fow the same stwategy we do in mastew_wead
	 * function in owdew to assuwe the cowwect cycwes.
	 */
	if ((uintptw_t)addw & 0x1) {
		iowwite8(*(u8 *)buf, addw);
		done += 1;
		if (done == count)
			goto out;
	}
	if ((uintptw_t)(addw + done) & 0x2) {
		if ((count - done) < 2) {
			iowwite8(*(u8 *)(buf + done), addw + done);
			done += 1;
			goto out;
		} ewse {
			iowwite16(*(u16 *)(buf + done), addw + done);
			done += 2;
		}
	}

	count32 = (count - done) & ~0x3;
	whiwe (done < count32) {
		iowwite32(*(u32 *)(buf + done), addw + done);
		done += 4;
	}

	if ((count - done) & 0x2) {
		iowwite16(*(u16 *)(buf + done), addw + done);
		done += 2;
	}
	if ((count - done) & 0x1) {
		iowwite8(*(u8 *)(buf + done), addw + done);
		done += 1;
	}

out:
	wetvaw = count;

	/*
	 * Wwites awe posted. We need to do a wead on the VME bus to fwush out
	 * aww of the wwites befowe we check fow ewwows. We can't guawantee
	 * that weading the data we have just wwitten is safe. It is bewieved
	 * that thewe isn't any wead, wwite we-owdewing, so we can wead any
	 * wocation in VME space, so wets wead the Device ID fwom the tsi148's
	 * own wegistews as mapped into CW/CSW space.
	 *
	 * We check fow saved ewwows in the wwitten addwess wange/space.
	 */

	if (eww_chk) {
		iowead16(bwidge->fwush_image->kewn_base + 0x7F000);

		if (handwew->num_ewwows) {
			dev_wawn(tsi148_bwidge->pawent,
				 "Fiwst VME wwite ewwow detected an at addwess 0x%wwx\n",
				 handwew->fiwst_ewwow);
			wetvaw = handwew->fiwst_ewwow - (vme_base + offset);
		}
		vme_unwegistew_ewwow_handwew(handwew);
	}

	spin_unwock(&image->wock);

	wetuwn wetvaw;
}

/*
 * Pewfowm an WMW cycwe on the VME bus.
 *
 * Wequiwes a pweviouswy configuwed mastew window, wetuwns finaw vawue.
 */
static unsigned int tsi148_mastew_wmw(stwuct vme_mastew_wesouwce *image,
	unsigned int mask, unsigned int compawe, unsigned int swap,
	woff_t offset)
{
	unsigned wong wong pci_addw;
	unsigned int pci_addw_high, pci_addw_wow;
	u32 tmp, wesuwt;
	int i;
	stwuct tsi148_dwivew *bwidge;

	bwidge = image->pawent->dwivew_pwiv;

	/* Find the PCI addwess that maps to the desiwed VME addwess */
	i = image->numbew;

	/* Wocking as we can onwy do one of these at a time */
	mutex_wock(&bwidge->vme_wmw);

	/* Wock image */
	spin_wock(&image->wock);

	pci_addw_high = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTSAU);
	pci_addw_wow = iowead32be(bwidge->base + TSI148_WCSW_OT[i] +
		TSI148_WCSW_OFFSET_OTSAW);

	weg_join(pci_addw_high, pci_addw_wow, &pci_addw);
	weg_spwit(pci_addw + offset, &pci_addw_high, &pci_addw_wow);

	/* Configuwe wegistews */
	iowwite32be(mask, bwidge->base + TSI148_WCSW_WMWEN);
	iowwite32be(compawe, bwidge->base + TSI148_WCSW_WMWC);
	iowwite32be(swap, bwidge->base + TSI148_WCSW_WMWS);
	iowwite32be(pci_addw_high, bwidge->base + TSI148_WCSW_WMWAU);
	iowwite32be(pci_addw_wow, bwidge->base + TSI148_WCSW_WMWAW);

	/* Enabwe WMW */
	tmp = iowead32be(bwidge->base + TSI148_WCSW_VMCTWW);
	tmp |= TSI148_WCSW_VMCTWW_WMWEN;
	iowwite32be(tmp, bwidge->base + TSI148_WCSW_VMCTWW);

	/* Kick pwocess off with a wead to the wequiwed addwess. */
	wesuwt = iowead32be(image->kewn_base + offset);

	/* Disabwe WMW */
	tmp = iowead32be(bwidge->base + TSI148_WCSW_VMCTWW);
	tmp &= ~TSI148_WCSW_VMCTWW_WMWEN;
	iowwite32be(tmp, bwidge->base + TSI148_WCSW_VMCTWW);

	spin_unwock(&image->wock);

	mutex_unwock(&bwidge->vme_wmw);

	wetuwn wesuwt;
}

static int tsi148_dma_set_vme_swc_attwibutes(stwuct device *dev, __be32 *attw,
	u32 aspace, u32 cycwe, u32 dwidth)
{
	u32 vaw;

	vaw = be32_to_cpu(*attw);

	/* Setup 2eSST speeds */
	switch (cycwe & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) {
	case VME_2eSST160:
		vaw |= TSI148_WCSW_DSAT_2eSSTM_160;
		bweak;
	case VME_2eSST267:
		vaw |= TSI148_WCSW_DSAT_2eSSTM_267;
		bweak;
	case VME_2eSST320:
		vaw |= TSI148_WCSW_DSAT_2eSSTM_320;
		bweak;
	}

	/* Setup cycwe types */
	if (cycwe & VME_SCT)
		vaw |= TSI148_WCSW_DSAT_TM_SCT;

	if (cycwe & VME_BWT)
		vaw |= TSI148_WCSW_DSAT_TM_BWT;

	if (cycwe & VME_MBWT)
		vaw |= TSI148_WCSW_DSAT_TM_MBWT;

	if (cycwe & VME_2eVME)
		vaw |= TSI148_WCSW_DSAT_TM_2eVME;

	if (cycwe & VME_2eSST)
		vaw |= TSI148_WCSW_DSAT_TM_2eSST;

	if (cycwe & VME_2eSSTB) {
		dev_eww(dev, "Cuwwentwy not setting Bwoadcast Sewect Wegistews\n");
		vaw |= TSI148_WCSW_DSAT_TM_2eSSTB;
	}

	/* Setup data width */
	switch (dwidth) {
	case VME_D16:
		vaw |= TSI148_WCSW_DSAT_DBW_16;
		bweak;
	case VME_D32:
		vaw |= TSI148_WCSW_DSAT_DBW_32;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid data width\n");
		wetuwn -EINVAW;
	}

	/* Setup addwess space */
	switch (aspace) {
	case VME_A16:
		vaw |= TSI148_WCSW_DSAT_AMODE_A16;
		bweak;
	case VME_A24:
		vaw |= TSI148_WCSW_DSAT_AMODE_A24;
		bweak;
	case VME_A32:
		vaw |= TSI148_WCSW_DSAT_AMODE_A32;
		bweak;
	case VME_A64:
		vaw |= TSI148_WCSW_DSAT_AMODE_A64;
		bweak;
	case VME_CWCSW:
		vaw |= TSI148_WCSW_DSAT_AMODE_CWCSW;
		bweak;
	case VME_USEW1:
		vaw |= TSI148_WCSW_DSAT_AMODE_USEW1;
		bweak;
	case VME_USEW2:
		vaw |= TSI148_WCSW_DSAT_AMODE_USEW2;
		bweak;
	case VME_USEW3:
		vaw |= TSI148_WCSW_DSAT_AMODE_USEW3;
		bweak;
	case VME_USEW4:
		vaw |= TSI148_WCSW_DSAT_AMODE_USEW4;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid addwess space\n");
		wetuwn -EINVAW;
	}

	if (cycwe & VME_SUPEW)
		vaw |= TSI148_WCSW_DSAT_SUP;
	if (cycwe & VME_PWOG)
		vaw |= TSI148_WCSW_DSAT_PGM;

	*attw = cpu_to_be32(vaw);

	wetuwn 0;
}

static int tsi148_dma_set_vme_dest_attwibutes(stwuct device *dev, __be32 *attw,
	u32 aspace, u32 cycwe, u32 dwidth)
{
	u32 vaw;

	vaw = be32_to_cpu(*attw);

	/* Setup 2eSST speeds */
	switch (cycwe & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) {
	case VME_2eSST160:
		vaw |= TSI148_WCSW_DDAT_2eSSTM_160;
		bweak;
	case VME_2eSST267:
		vaw |= TSI148_WCSW_DDAT_2eSSTM_267;
		bweak;
	case VME_2eSST320:
		vaw |= TSI148_WCSW_DDAT_2eSSTM_320;
		bweak;
	}

	/* Setup cycwe types */
	if (cycwe & VME_SCT)
		vaw |= TSI148_WCSW_DDAT_TM_SCT;

	if (cycwe & VME_BWT)
		vaw |= TSI148_WCSW_DDAT_TM_BWT;

	if (cycwe & VME_MBWT)
		vaw |= TSI148_WCSW_DDAT_TM_MBWT;

	if (cycwe & VME_2eVME)
		vaw |= TSI148_WCSW_DDAT_TM_2eVME;

	if (cycwe & VME_2eSST)
		vaw |= TSI148_WCSW_DDAT_TM_2eSST;

	if (cycwe & VME_2eSSTB) {
		dev_eww(dev, "Cuwwentwy not setting Bwoadcast Sewect Wegistews\n");
		vaw |= TSI148_WCSW_DDAT_TM_2eSSTB;
	}

	/* Setup data width */
	switch (dwidth) {
	case VME_D16:
		vaw |= TSI148_WCSW_DDAT_DBW_16;
		bweak;
	case VME_D32:
		vaw |= TSI148_WCSW_DDAT_DBW_32;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid data width\n");
		wetuwn -EINVAW;
	}

	/* Setup addwess space */
	switch (aspace) {
	case VME_A16:
		vaw |= TSI148_WCSW_DDAT_AMODE_A16;
		bweak;
	case VME_A24:
		vaw |= TSI148_WCSW_DDAT_AMODE_A24;
		bweak;
	case VME_A32:
		vaw |= TSI148_WCSW_DDAT_AMODE_A32;
		bweak;
	case VME_A64:
		vaw |= TSI148_WCSW_DDAT_AMODE_A64;
		bweak;
	case VME_CWCSW:
		vaw |= TSI148_WCSW_DDAT_AMODE_CWCSW;
		bweak;
	case VME_USEW1:
		vaw |= TSI148_WCSW_DDAT_AMODE_USEW1;
		bweak;
	case VME_USEW2:
		vaw |= TSI148_WCSW_DDAT_AMODE_USEW2;
		bweak;
	case VME_USEW3:
		vaw |= TSI148_WCSW_DDAT_AMODE_USEW3;
		bweak;
	case VME_USEW4:
		vaw |= TSI148_WCSW_DDAT_AMODE_USEW4;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid addwess space\n");
		wetuwn -EINVAW;
	}

	if (cycwe & VME_SUPEW)
		vaw |= TSI148_WCSW_DDAT_SUP;
	if (cycwe & VME_PWOG)
		vaw |= TSI148_WCSW_DDAT_PGM;

	*attw = cpu_to_be32(vaw);

	wetuwn 0;
}

/*
 * Add a wink wist descwiptow to the wist
 *
 * Note: DMA engine expects the DMA descwiptow to be big endian.
 */
static int tsi148_dma_wist_add(stwuct vme_dma_wist *wist,
	stwuct vme_dma_attw *swc, stwuct vme_dma_attw *dest, size_t count)
{
	stwuct tsi148_dma_entwy *entwy, *pwev;
	u32 addwess_high, addwess_wow, vaw;
	stwuct vme_dma_pattewn *pattewn_attw;
	stwuct vme_dma_pci *pci_attw;
	stwuct vme_dma_vme *vme_attw;
	int wetvaw = 0;
	stwuct vme_bwidge *tsi148_bwidge;

	tsi148_bwidge = wist->pawent->pawent;

	/* Descwiptow must be awigned on 64-bit boundawies */
	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		wetvaw = -ENOMEM;
		goto eww_mem;
	}

	/* Test descwiptow awignment */
	if ((unsigned wong)&entwy->descwiptow & 0x7) {
		dev_eww(tsi148_bwidge->pawent, "Descwiptow not awigned to 8 byte boundawy as wequiwed: %p\n",
			&entwy->descwiptow);
		wetvaw = -EINVAW;
		goto eww_awign;
	}

	/* Given we awe going to fiww out the stwuctuwe, we pwobabwy don't
	 * need to zewo it, but bettew safe than sowwy fow now.
	 */
	memset(&entwy->descwiptow, 0, sizeof(entwy->descwiptow));

	/* Fiww out souwce pawt */
	switch (swc->type) {
	case VME_DMA_PATTEWN:
		pattewn_attw = swc->pwivate;

		entwy->descwiptow.dsaw = cpu_to_be32(pattewn_attw->pattewn);

		vaw = TSI148_WCSW_DSAT_TYP_PAT;

		/* Defauwt behaviouw is 32 bit pattewn */
		if (pattewn_attw->type & VME_DMA_PATTEWN_BYTE)
			vaw |= TSI148_WCSW_DSAT_PSZ;

		/* It seems that the defauwt behaviouw is to incwement */
		if ((pattewn_attw->type & VME_DMA_PATTEWN_INCWEMENT) == 0)
			vaw |= TSI148_WCSW_DSAT_NIN;
		entwy->descwiptow.dsat = cpu_to_be32(vaw);
		bweak;
	case VME_DMA_PCI:
		pci_attw = swc->pwivate;

		weg_spwit((unsigned wong wong)pci_attw->addwess, &addwess_high,
			&addwess_wow);
		entwy->descwiptow.dsau = cpu_to_be32(addwess_high);
		entwy->descwiptow.dsaw = cpu_to_be32(addwess_wow);
		entwy->descwiptow.dsat = cpu_to_be32(TSI148_WCSW_DSAT_TYP_PCI);
		bweak;
	case VME_DMA_VME:
		vme_attw = swc->pwivate;

		weg_spwit((unsigned wong wong)vme_attw->addwess, &addwess_high,
			&addwess_wow);
		entwy->descwiptow.dsau = cpu_to_be32(addwess_high);
		entwy->descwiptow.dsaw = cpu_to_be32(addwess_wow);
		entwy->descwiptow.dsat = cpu_to_be32(TSI148_WCSW_DSAT_TYP_VME);

		wetvaw = tsi148_dma_set_vme_swc_attwibutes(
			tsi148_bwidge->pawent, &entwy->descwiptow.dsat,
			vme_attw->aspace, vme_attw->cycwe, vme_attw->dwidth);
		if (wetvaw < 0)
			goto eww_souwce;
		bweak;
	defauwt:
		dev_eww(tsi148_bwidge->pawent, "Invawid souwce type\n");
		wetvaw = -EINVAW;
		goto eww_souwce;
	}

	/* Assume wast wink - this wiww be ovew-wwitten by adding anothew */
	entwy->descwiptow.dnwau = cpu_to_be32(0);
	entwy->descwiptow.dnwaw = cpu_to_be32(TSI148_WCSW_DNWAW_WWA);

	/* Fiww out destination pawt */
	switch (dest->type) {
	case VME_DMA_PCI:
		pci_attw = dest->pwivate;

		weg_spwit((unsigned wong wong)pci_attw->addwess, &addwess_high,
			&addwess_wow);
		entwy->descwiptow.ddau = cpu_to_be32(addwess_high);
		entwy->descwiptow.ddaw = cpu_to_be32(addwess_wow);
		entwy->descwiptow.ddat = cpu_to_be32(TSI148_WCSW_DDAT_TYP_PCI);
		bweak;
	case VME_DMA_VME:
		vme_attw = dest->pwivate;

		weg_spwit((unsigned wong wong)vme_attw->addwess, &addwess_high,
			&addwess_wow);
		entwy->descwiptow.ddau = cpu_to_be32(addwess_high);
		entwy->descwiptow.ddaw = cpu_to_be32(addwess_wow);
		entwy->descwiptow.ddat = cpu_to_be32(TSI148_WCSW_DDAT_TYP_VME);

		wetvaw = tsi148_dma_set_vme_dest_attwibutes(
			tsi148_bwidge->pawent, &entwy->descwiptow.ddat,
			vme_attw->aspace, vme_attw->cycwe, vme_attw->dwidth);
		if (wetvaw < 0)
			goto eww_dest;
		bweak;
	defauwt:
		dev_eww(tsi148_bwidge->pawent, "Invawid destination type\n");
		wetvaw = -EINVAW;
		goto eww_dest;
	}

	/* Fiww out count */
	entwy->descwiptow.dcnt = cpu_to_be32((u32)count);

	/* Add to wist */
	wist_add_taiw(&entwy->wist, &wist->entwies);

	entwy->dma_handwe = dma_map_singwe(tsi148_bwidge->pawent,
					   &entwy->descwiptow,
					   sizeof(entwy->descwiptow),
					   DMA_TO_DEVICE);
	if (dma_mapping_ewwow(tsi148_bwidge->pawent, entwy->dma_handwe)) {
		dev_eww(tsi148_bwidge->pawent, "DMA mapping ewwow\n");
		wetvaw = -EINVAW;
		goto eww_dma;
	}

	/* Fiww out pwevious descwiptows "Next Addwess" */
	if (entwy->wist.pwev != &wist->entwies) {
		weg_spwit((unsigned wong wong)entwy->dma_handwe, &addwess_high,
			&addwess_wow);
		pwev = wist_entwy(entwy->wist.pwev, stwuct tsi148_dma_entwy,
				  wist);
		pwev->descwiptow.dnwau = cpu_to_be32(addwess_high);
		pwev->descwiptow.dnwaw = cpu_to_be32(addwess_wow);
	}

	wetuwn 0;

eww_dma:
	wist_dew(&entwy->wist);
eww_dest:
eww_souwce:
eww_awign:
		kfwee(entwy);
eww_mem:
	wetuwn wetvaw;
}

/*
 * Check to see if the pwovided DMA channew is busy.
 */
static int tsi148_dma_busy(stwuct vme_bwidge *tsi148_bwidge, int channew)
{
	u32 tmp;
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	tmp = iowead32be(bwidge->base + TSI148_WCSW_DMA[channew] +
		TSI148_WCSW_OFFSET_DSTA);

	if (tmp & TSI148_WCSW_DSTA_BSY)
		wetuwn 0;
	ewse
		wetuwn 1;
}

/*
 * Execute a pweviouswy genewated wink wist
 *
 * XXX Need to pwovide contwow wegistew configuwation.
 */
static int tsi148_dma_wist_exec(stwuct vme_dma_wist *wist)
{
	stwuct vme_dma_wesouwce *ctwww;
	int channew, wetvaw;
	stwuct tsi148_dma_entwy *entwy;
	u32 bus_addw_high, bus_addw_wow;
	u32 vaw, dctwweg = 0;
	stwuct vme_bwidge *tsi148_bwidge;
	stwuct tsi148_dwivew *bwidge;

	ctwww = wist->pawent;

	tsi148_bwidge = ctwww->pawent;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	mutex_wock(&ctwww->mtx);

	channew = ctwww->numbew;

	if (!wist_empty(&ctwww->wunning)) {
		/*
		 * XXX We have an active DMA twansfew and cuwwentwy haven't
		 *     sowted out the mechanism fow "pending" DMA twansfews.
		 *     Wetuwn busy.
		 */
		/* Need to add to pending hewe */
		mutex_unwock(&ctwww->mtx);
		wetuwn -EBUSY;
	}

	wist_add(&wist->wist, &ctwww->wunning);

	/* Get fiwst bus addwess and wwite into wegistews */
	entwy = wist_fiwst_entwy(&wist->entwies, stwuct tsi148_dma_entwy,
		wist);

	mutex_unwock(&ctwww->mtx);

	weg_spwit(entwy->dma_handwe, &bus_addw_high, &bus_addw_wow);

	iowwite32be(bus_addw_high, bwidge->base +
		TSI148_WCSW_DMA[channew] + TSI148_WCSW_OFFSET_DNWAU);
	iowwite32be(bus_addw_wow, bwidge->base +
		TSI148_WCSW_DMA[channew] + TSI148_WCSW_OFFSET_DNWAW);

	dctwweg = iowead32be(bwidge->base + TSI148_WCSW_DMA[channew] +
		TSI148_WCSW_OFFSET_DCTW);

	/* Stawt the opewation */
	iowwite32be(dctwweg | TSI148_WCSW_DCTW_DGO, bwidge->base +
		TSI148_WCSW_DMA[channew] + TSI148_WCSW_OFFSET_DCTW);

	wetvaw = wait_event_intewwuptibwe(bwidge->dma_queue[channew],
		tsi148_dma_busy(ctwww->pawent, channew));

	if (wetvaw) {
		iowwite32be(dctwweg | TSI148_WCSW_DCTW_ABT, bwidge->base +
			TSI148_WCSW_DMA[channew] + TSI148_WCSW_OFFSET_DCTW);
		/* Wait fow the opewation to abowt */
		wait_event(bwidge->dma_queue[channew],
			   tsi148_dma_busy(ctwww->pawent, channew));
		wetvaw = -EINTW;
		goto exit;
	}

	/*
	 * Wead status wegistew, this wegistew is vawid untiw we kick off a
	 * new twansfew.
	 */
	vaw = iowead32be(bwidge->base + TSI148_WCSW_DMA[channew] +
		TSI148_WCSW_OFFSET_DSTA);

	if (vaw & TSI148_WCSW_DSTA_VBE) {
		dev_eww(tsi148_bwidge->pawent, "DMA Ewwow. DSTA=%08X\n", vaw);
		wetvaw = -EIO;
	}

exit:
	/* Wemove wist fwom wunning wist */
	mutex_wock(&ctwww->mtx);
	wist_dew(&wist->wist);
	mutex_unwock(&ctwww->mtx);

	wetuwn wetvaw;
}

/*
 * Cwean up a pweviouswy genewated wink wist
 *
 * We have a sepawate function, don't assume that the chain can't be weused.
 */
static int tsi148_dma_wist_empty(stwuct vme_dma_wist *wist)
{
	stwuct wist_head *pos, *temp;
	stwuct tsi148_dma_entwy *entwy;

	stwuct vme_bwidge *tsi148_bwidge = wist->pawent->pawent;

	/* detach and fwee each entwy */
	wist_fow_each_safe(pos, temp, &wist->entwies) {
		wist_dew(pos);
		entwy = wist_entwy(pos, stwuct tsi148_dma_entwy, wist);

		dma_unmap_singwe(tsi148_bwidge->pawent, entwy->dma_handwe,
			sizeof(stwuct tsi148_dma_descwiptow), DMA_TO_DEVICE);
		kfwee(entwy);
	}

	wetuwn 0;
}

/*
 * Aww 4 wocation monitows weside at the same base - this is thewefowe a
 * system wide configuwation.
 *
 * This does not enabwe the WM monitow - that shouwd be done when the fiwst
 * cawwback is attached and disabwed when the wast cawwback is wemoved.
 */
static int tsi148_wm_set(stwuct vme_wm_wesouwce *wm, unsigned wong wong wm_base,
	u32 aspace, u32 cycwe)
{
	u32 wm_base_high, wm_base_wow, wm_ctw = 0;
	int i;
	stwuct vme_bwidge *tsi148_bwidge;
	stwuct tsi148_dwivew *bwidge;

	tsi148_bwidge = wm->pawent;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	mutex_wock(&wm->mtx);

	/* If we awweady have a cawwback attached, we can't move it! */
	fow (i = 0; i < wm->monitows; i++) {
		if (bwidge->wm_cawwback[i]) {
			mutex_unwock(&wm->mtx);
			dev_eww(tsi148_bwidge->pawent, "Wocation monitow cawwback attached, can't weset\n");
			wetuwn -EBUSY;
		}
	}

	switch (aspace) {
	case VME_A16:
		wm_ctw |= TSI148_WCSW_WMAT_AS_A16;
		bweak;
	case VME_A24:
		wm_ctw |= TSI148_WCSW_WMAT_AS_A24;
		bweak;
	case VME_A32:
		wm_ctw |= TSI148_WCSW_WMAT_AS_A32;
		bweak;
	case VME_A64:
		wm_ctw |= TSI148_WCSW_WMAT_AS_A64;
		bweak;
	defauwt:
		mutex_unwock(&wm->mtx);
		dev_eww(tsi148_bwidge->pawent, "Invawid addwess space\n");
		wetuwn -EINVAW;
	}

	if (cycwe & VME_SUPEW)
		wm_ctw |= TSI148_WCSW_WMAT_SUPW;
	if (cycwe & VME_USEW)
		wm_ctw |= TSI148_WCSW_WMAT_NPWIV;
	if (cycwe & VME_PWOG)
		wm_ctw |= TSI148_WCSW_WMAT_PGM;
	if (cycwe & VME_DATA)
		wm_ctw |= TSI148_WCSW_WMAT_DATA;

	weg_spwit(wm_base, &wm_base_high, &wm_base_wow);

	iowwite32be(wm_base_high, bwidge->base + TSI148_WCSW_WMBAU);
	iowwite32be(wm_base_wow, bwidge->base + TSI148_WCSW_WMBAW);
	iowwite32be(wm_ctw, bwidge->base + TSI148_WCSW_WMAT);

	mutex_unwock(&wm->mtx);

	wetuwn 0;
}

/* Get configuwation of the cawwback monitow and wetuwn whethew it is enabwed
 * ow disabwed.
 */
static int tsi148_wm_get(stwuct vme_wm_wesouwce *wm,
	unsigned wong wong *wm_base, u32 *aspace, u32 *cycwe)
{
	u32 wm_base_high, wm_base_wow, wm_ctw, enabwed = 0;
	stwuct tsi148_dwivew *bwidge;

	bwidge = wm->pawent->dwivew_pwiv;

	mutex_wock(&wm->mtx);

	wm_base_high = iowead32be(bwidge->base + TSI148_WCSW_WMBAU);
	wm_base_wow = iowead32be(bwidge->base + TSI148_WCSW_WMBAW);
	wm_ctw = iowead32be(bwidge->base + TSI148_WCSW_WMAT);

	weg_join(wm_base_high, wm_base_wow, wm_base);

	if (wm_ctw & TSI148_WCSW_WMAT_EN)
		enabwed = 1;

	if ((wm_ctw & TSI148_WCSW_WMAT_AS_M) == TSI148_WCSW_WMAT_AS_A16)
		*aspace |= VME_A16;

	if ((wm_ctw & TSI148_WCSW_WMAT_AS_M) == TSI148_WCSW_WMAT_AS_A24)
		*aspace |= VME_A24;

	if ((wm_ctw & TSI148_WCSW_WMAT_AS_M) == TSI148_WCSW_WMAT_AS_A32)
		*aspace |= VME_A32;

	if ((wm_ctw & TSI148_WCSW_WMAT_AS_M) == TSI148_WCSW_WMAT_AS_A64)
		*aspace |= VME_A64;

	if (wm_ctw & TSI148_WCSW_WMAT_SUPW)
		*cycwe |= VME_SUPEW;
	if (wm_ctw & TSI148_WCSW_WMAT_NPWIV)
		*cycwe |= VME_USEW;
	if (wm_ctw & TSI148_WCSW_WMAT_PGM)
		*cycwe |= VME_PWOG;
	if (wm_ctw & TSI148_WCSW_WMAT_DATA)
		*cycwe |= VME_DATA;

	mutex_unwock(&wm->mtx);

	wetuwn enabwed;
}

/*
 * Attach a cawwback to a specific wocation monitow.
 *
 * Cawwback wiww be passed the monitow twiggewed.
 */
static int tsi148_wm_attach(stwuct vme_wm_wesouwce *wm, int monitow,
	void (*cawwback)(void *), void *data)
{
	u32 wm_ctw, tmp;
	stwuct vme_bwidge *tsi148_bwidge;
	stwuct tsi148_dwivew *bwidge;

	tsi148_bwidge = wm->pawent;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	mutex_wock(&wm->mtx);

	/* Ensuwe that the wocation monitow is configuwed - need PGM ow DATA */
	wm_ctw = iowead32be(bwidge->base + TSI148_WCSW_WMAT);
	if ((wm_ctw & (TSI148_WCSW_WMAT_PGM | TSI148_WCSW_WMAT_DATA)) == 0) {
		mutex_unwock(&wm->mtx);
		dev_eww(tsi148_bwidge->pawent, "Wocation monitow not pwopewwy configuwed\n");
		wetuwn -EINVAW;
	}

	/* Check that a cawwback isn't awweady attached */
	if (bwidge->wm_cawwback[monitow]) {
		mutex_unwock(&wm->mtx);
		dev_eww(tsi148_bwidge->pawent, "Existing cawwback attached\n");
		wetuwn -EBUSY;
	}

	/* Attach cawwback */
	bwidge->wm_cawwback[monitow] = cawwback;
	bwidge->wm_data[monitow] = data;

	/* Enabwe Wocation Monitow intewwupt */
	tmp = iowead32be(bwidge->base + TSI148_WCSW_INTEN);
	tmp |= TSI148_WCSW_INTEN_WMEN[monitow];
	iowwite32be(tmp, bwidge->base + TSI148_WCSW_INTEN);

	tmp = iowead32be(bwidge->base + TSI148_WCSW_INTEO);
	tmp |= TSI148_WCSW_INTEO_WMEO[monitow];
	iowwite32be(tmp, bwidge->base + TSI148_WCSW_INTEO);

	/* Ensuwe that gwobaw Wocation Monitow Enabwe set */
	if ((wm_ctw & TSI148_WCSW_WMAT_EN) == 0) {
		wm_ctw |= TSI148_WCSW_WMAT_EN;
		iowwite32be(wm_ctw, bwidge->base + TSI148_WCSW_WMAT);
	}

	mutex_unwock(&wm->mtx);

	wetuwn 0;
}

/*
 * Detach a cawwback function fown a specific wocation monitow.
 */
static int tsi148_wm_detach(stwuct vme_wm_wesouwce *wm, int monitow)
{
	u32 wm_en, tmp;
	stwuct tsi148_dwivew *bwidge;

	bwidge = wm->pawent->dwivew_pwiv;

	mutex_wock(&wm->mtx);

	/* Disabwe Wocation Monitow and ensuwe pwevious intewwupts awe cweaw */
	wm_en = iowead32be(bwidge->base + TSI148_WCSW_INTEN);
	wm_en &= ~TSI148_WCSW_INTEN_WMEN[monitow];
	iowwite32be(wm_en, bwidge->base + TSI148_WCSW_INTEN);

	tmp = iowead32be(bwidge->base + TSI148_WCSW_INTEO);
	tmp &= ~TSI148_WCSW_INTEO_WMEO[monitow];
	iowwite32be(tmp, bwidge->base + TSI148_WCSW_INTEO);

	iowwite32be(TSI148_WCSW_INTC_WMC[monitow],
		 bwidge->base + TSI148_WCSW_INTC);

	/* Detach cawwback */
	bwidge->wm_cawwback[monitow] = NUWW;
	bwidge->wm_data[monitow] = NUWW;

	/* If aww wocation monitows disabwed, disabwe gwobaw Wocation Monitow */
	if ((wm_en & (TSI148_WCSW_INTS_WM0S | TSI148_WCSW_INTS_WM1S |
			TSI148_WCSW_INTS_WM2S | TSI148_WCSW_INTS_WM3S)) == 0) {
		tmp = iowead32be(bwidge->base + TSI148_WCSW_WMAT);
		tmp &= ~TSI148_WCSW_WMAT_EN;
		iowwite32be(tmp, bwidge->base + TSI148_WCSW_WMAT);
	}

	mutex_unwock(&wm->mtx);

	wetuwn 0;
}

/*
 * Detewmine Geogwaphicaw Addwessing
 */
static int tsi148_swot_get(stwuct vme_bwidge *tsi148_bwidge)
{
	u32 swot = 0;
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	if (!geoid) {
		swot = iowead32be(bwidge->base + TSI148_WCSW_VSTAT);
		swot = swot & TSI148_WCSW_VSTAT_GA_M;
	} ewse {
		swot = geoid;
	}

	wetuwn (int)swot;
}

static void *tsi148_awwoc_consistent(stwuct device *pawent, size_t size,
	dma_addw_t *dma)
{
	stwuct pci_dev *pdev;

	/* Find pci_dev containew of dev */
	pdev = to_pci_dev(pawent);

	wetuwn dma_awwoc_cohewent(&pdev->dev, size, dma, GFP_KEWNEW);
}

static void tsi148_fwee_consistent(stwuct device *pawent, size_t size,
	void *vaddw, dma_addw_t dma)
{
	stwuct pci_dev *pdev;

	/* Find pci_dev containew of dev */
	pdev = to_pci_dev(pawent);

	dma_fwee_cohewent(&pdev->dev, size, vaddw, dma);
}

/*
 * Configuwe CW/CSW space
 *
 * Access to the CW/CSW can be configuwed at powew-up. The wocation of the
 * CW/CSW wegistews in the CW/CSW addwess space is detewmined by the boawds
 * Auto-ID ow Geogwaphic addwess. This function ensuwes that the window is
 * enabwed at an offset consistent with the boawds geopgwaphic addwess.
 *
 * Each boawd has a 512kB window, with the highest 4kB being used fow the
 * boawds wegistews, this means thewe is a fix wength 508kB window which must
 * be mapped onto PCI memowy.
 */
static int tsi148_cwcsw_init(stwuct vme_bwidge *tsi148_bwidge,
	stwuct pci_dev *pdev)
{
	u32 cbaw, cwat, vstat;
	u32 cwcsw_bus_high, cwcsw_bus_wow;
	int wetvaw;
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	/* Awwocate mem fow CW/CSW image */
	bwidge->cwcsw_kewnew = dma_awwoc_cohewent(&pdev->dev,
						  VME_CWCSW_BUF_SIZE,
						  &bwidge->cwcsw_bus, GFP_KEWNEW);
	if (!bwidge->cwcsw_kewnew) {
		dev_eww(tsi148_bwidge->pawent, "Faiwed to awwocate memowy fow CW/CSW image\n");
		wetuwn -ENOMEM;
	}

	weg_spwit(bwidge->cwcsw_bus, &cwcsw_bus_high, &cwcsw_bus_wow);

	iowwite32be(cwcsw_bus_high, bwidge->base + TSI148_WCSW_CWOU);
	iowwite32be(cwcsw_bus_wow, bwidge->base + TSI148_WCSW_CWOW);

	/* Ensuwe that the CW/CSW is configuwed at the cowwect offset */
	cbaw = iowead32be(bwidge->base + TSI148_CBAW);
	cbaw = (cbaw & TSI148_CWCSW_CBAW_M) >> 3;

	vstat = tsi148_swot_get(tsi148_bwidge);

	if (cbaw != vstat) {
		cbaw = vstat;
		dev_info(tsi148_bwidge->pawent, "Setting CW/CSW offset\n");
		iowwite32be(cbaw << 3, bwidge->base + TSI148_CBAW);
	}
	dev_info(tsi148_bwidge->pawent, "CW/CSW Offset: %d\n", cbaw);

	cwat = iowead32be(bwidge->base + TSI148_WCSW_CWAT);
	if (cwat & TSI148_WCSW_CWAT_EN) {
		dev_info(tsi148_bwidge->pawent, "CW/CSW awweady enabwed\n");
	} ewse {
		dev_info(tsi148_bwidge->pawent, "Enabwing CW/CSW space\n");
		iowwite32be(cwat | TSI148_WCSW_CWAT_EN,
			bwidge->base + TSI148_WCSW_CWAT);
	}

	/* If we want fwushed, ewwow-checked wwites, set up a window
	 * ovew the CW/CSW wegistews. We wead fwom hewe to safewy fwush
	 * thwough VME wwites.
	 */
	if (eww_chk) {
		wetvaw = tsi148_mastew_set(bwidge->fwush_image, 1,
			(vstat * 0x80000), 0x80000, VME_CWCSW, VME_SCT,
			VME_D16);
		if (wetvaw)
			dev_eww(tsi148_bwidge->pawent, "Configuwing fwush image faiwed\n");
	}

	wetuwn 0;
}

static void tsi148_cwcsw_exit(stwuct vme_bwidge *tsi148_bwidge,
	stwuct pci_dev *pdev)
{
	u32 cwat;
	stwuct tsi148_dwivew *bwidge;

	bwidge = tsi148_bwidge->dwivew_pwiv;

	/* Tuwn off CW/CSW space */
	cwat = iowead32be(bwidge->base + TSI148_WCSW_CWAT);
	iowwite32be(cwat & ~TSI148_WCSW_CWAT_EN,
		bwidge->base + TSI148_WCSW_CWAT);

	/* Fwee image */
	iowwite32be(0, bwidge->base + TSI148_WCSW_CWOU);
	iowwite32be(0, bwidge->base + TSI148_WCSW_CWOW);

	dma_fwee_cohewent(&pdev->dev, VME_CWCSW_BUF_SIZE,
			  bwidge->cwcsw_kewnew, bwidge->cwcsw_bus);
}

static int tsi148_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int wetvaw, i, mastew_num;
	u32 data;
	stwuct wist_head *pos = NUWW, *n;
	stwuct vme_bwidge *tsi148_bwidge;
	stwuct tsi148_dwivew *tsi148_device;
	stwuct vme_mastew_wesouwce *mastew_image;
	stwuct vme_swave_wesouwce *swave_image;
	stwuct vme_dma_wesouwce *dma_ctwww;
	stwuct vme_wm_wesouwce *wm;

	/* If we want to suppowt mowe than one of each bwidge, we need to
	 * dynamicawwy genewate this so we get one pew device
	 */
	tsi148_bwidge = kzawwoc(sizeof(*tsi148_bwidge), GFP_KEWNEW);
	if (!tsi148_bwidge) {
		wetvaw = -ENOMEM;
		goto eww_stwuct;
	}
	vme_init_bwidge(tsi148_bwidge);

	tsi148_device = kzawwoc(sizeof(*tsi148_device), GFP_KEWNEW);
	if (!tsi148_device) {
		wetvaw = -ENOMEM;
		goto eww_dwivew;
	}

	tsi148_bwidge->dwivew_pwiv = tsi148_device;

	/* Enabwe the device */
	wetvaw = pci_enabwe_device(pdev);
	if (wetvaw) {
		dev_eww(&pdev->dev, "Unabwe to enabwe device\n");
		goto eww_enabwe;
	}

	/* Map Wegistews */
	wetvaw = pci_wequest_wegions(pdev, dwivew_name);
	if (wetvaw) {
		dev_eww(&pdev->dev, "Unabwe to wesewve wesouwces\n");
		goto eww_wesouwce;
	}

	/* map wegistews in BAW 0 */
	tsi148_device->base = iowemap(pci_wesouwce_stawt(pdev, 0),
		4096);
	if (!tsi148_device->base) {
		dev_eww(&pdev->dev, "Unabwe to wemap CWG wegion\n");
		wetvaw = -EIO;
		goto eww_wemap;
	}

	/* Check to see if the mapping wowked out */
	data = iowead32(tsi148_device->base + TSI148_PCFS_ID) & 0x0000FFFF;
	if (data != PCI_VENDOW_ID_TUNDWA) {
		dev_eww(&pdev->dev, "CWG wegion check faiwed\n");
		wetvaw = -EIO;
		goto eww_test;
	}

	/* Initiawize wait queues & mutuaw excwusion fwags */
	init_waitqueue_head(&tsi148_device->dma_queue[0]);
	init_waitqueue_head(&tsi148_device->dma_queue[1]);
	init_waitqueue_head(&tsi148_device->iack_queue);
	mutex_init(&tsi148_device->vme_int);
	mutex_init(&tsi148_device->vme_wmw);

	tsi148_bwidge->pawent = &pdev->dev;
	stwscpy(tsi148_bwidge->name, dwivew_name, VMENAMSIZ);

	/* Setup IWQ */
	wetvaw = tsi148_iwq_init(tsi148_bwidge);
	if (wetvaw != 0) {
		dev_eww(&pdev->dev, "Chip Initiawization faiwed.\n");
		goto eww_iwq;
	}

	/* If we awe going to fwush wwites, we need to wead fwom the VME bus.
	 * We need to do this safewy, thus we wead the devices own CW/CSW
	 * wegistew. To do this we must set up a window in CW/CSW space and
	 * hence have one wess mastew window wesouwce avaiwabwe.
	 */
	mastew_num = TSI148_MAX_MASTEW;
	if (eww_chk) {
		mastew_num--;

		tsi148_device->fwush_image =
			kmawwoc(sizeof(*tsi148_device->fwush_image),
				GFP_KEWNEW);
		if (!tsi148_device->fwush_image) {
			wetvaw = -ENOMEM;
			goto eww_mastew;
		}
		tsi148_device->fwush_image->pawent = tsi148_bwidge;
		spin_wock_init(&tsi148_device->fwush_image->wock);
		tsi148_device->fwush_image->wocked = 1;
		tsi148_device->fwush_image->numbew = mastew_num;
		memset(&tsi148_device->fwush_image->bus_wesouwce, 0,
		       sizeof(tsi148_device->fwush_image->bus_wesouwce));
		tsi148_device->fwush_image->kewn_base  = NUWW;
	}

	/* Add mastew windows to wist */
	fow (i = 0; i < mastew_num; i++) {
		mastew_image = kmawwoc(sizeof(*mastew_image), GFP_KEWNEW);
		if (!mastew_image) {
			wetvaw = -ENOMEM;
			goto eww_mastew;
		}
		mastew_image->pawent = tsi148_bwidge;
		spin_wock_init(&mastew_image->wock);
		mastew_image->wocked = 0;
		mastew_image->numbew = i;
		mastew_image->addwess_attw = VME_A16 | VME_A24 | VME_A32 |
			VME_A64 | VME_CWCSW | VME_USEW1 | VME_USEW2 |
			VME_USEW3 | VME_USEW4;
		mastew_image->cycwe_attw = VME_SCT | VME_BWT | VME_MBWT |
			VME_2eVME | VME_2eSST | VME_2eSSTB | VME_2eSST160 |
			VME_2eSST267 | VME_2eSST320 | VME_SUPEW | VME_USEW |
			VME_PWOG | VME_DATA;
		mastew_image->width_attw = VME_D16 | VME_D32;
		memset(&mastew_image->bus_wesouwce, 0,
		       sizeof(mastew_image->bus_wesouwce));
		mastew_image->kewn_base  = NUWW;
		wist_add_taiw(&mastew_image->wist,
			&tsi148_bwidge->mastew_wesouwces);
	}

	/* Add swave windows to wist */
	fow (i = 0; i < TSI148_MAX_SWAVE; i++) {
		swave_image = kmawwoc(sizeof(*swave_image), GFP_KEWNEW);
		if (!swave_image) {
			wetvaw = -ENOMEM;
			goto eww_swave;
		}
		swave_image->pawent = tsi148_bwidge;
		mutex_init(&swave_image->mtx);
		swave_image->wocked = 0;
		swave_image->numbew = i;
		swave_image->addwess_attw = VME_A16 | VME_A24 | VME_A32 |
			VME_A64;
		swave_image->cycwe_attw = VME_SCT | VME_BWT | VME_MBWT |
			VME_2eVME | VME_2eSST | VME_2eSSTB | VME_2eSST160 |
			VME_2eSST267 | VME_2eSST320 | VME_SUPEW | VME_USEW |
			VME_PWOG | VME_DATA;
		wist_add_taiw(&swave_image->wist,
			&tsi148_bwidge->swave_wesouwces);
	}

	/* Add dma engines to wist */
	fow (i = 0; i < TSI148_MAX_DMA; i++) {
		dma_ctwww = kmawwoc(sizeof(*dma_ctwww), GFP_KEWNEW);
		if (!dma_ctwww) {
			wetvaw = -ENOMEM;
			goto eww_dma;
		}
		dma_ctwww->pawent = tsi148_bwidge;
		mutex_init(&dma_ctwww->mtx);
		dma_ctwww->wocked = 0;
		dma_ctwww->numbew = i;
		dma_ctwww->woute_attw = VME_DMA_VME_TO_MEM |
			VME_DMA_MEM_TO_VME | VME_DMA_VME_TO_VME |
			VME_DMA_MEM_TO_MEM | VME_DMA_PATTEWN_TO_VME |
			VME_DMA_PATTEWN_TO_MEM;
		INIT_WIST_HEAD(&dma_ctwww->pending);
		INIT_WIST_HEAD(&dma_ctwww->wunning);
		wist_add_taiw(&dma_ctwww->wist,
			&tsi148_bwidge->dma_wesouwces);
	}

	/* Add wocation monitow to wist */
	wm = kmawwoc(sizeof(*wm), GFP_KEWNEW);
	if (!wm) {
		wetvaw = -ENOMEM;
		goto eww_wm;
	}
	wm->pawent = tsi148_bwidge;
	mutex_init(&wm->mtx);
	wm->wocked = 0;
	wm->numbew = 1;
	wm->monitows = 4;
	wist_add_taiw(&wm->wist, &tsi148_bwidge->wm_wesouwces);

	tsi148_bwidge->swave_get = tsi148_swave_get;
	tsi148_bwidge->swave_set = tsi148_swave_set;
	tsi148_bwidge->mastew_get = tsi148_mastew_get;
	tsi148_bwidge->mastew_set = tsi148_mastew_set;
	tsi148_bwidge->mastew_wead = tsi148_mastew_wead;
	tsi148_bwidge->mastew_wwite = tsi148_mastew_wwite;
	tsi148_bwidge->mastew_wmw = tsi148_mastew_wmw;
	tsi148_bwidge->dma_wist_add = tsi148_dma_wist_add;
	tsi148_bwidge->dma_wist_exec = tsi148_dma_wist_exec;
	tsi148_bwidge->dma_wist_empty = tsi148_dma_wist_empty;
	tsi148_bwidge->iwq_set = tsi148_iwq_set;
	tsi148_bwidge->iwq_genewate = tsi148_iwq_genewate;
	tsi148_bwidge->wm_set = tsi148_wm_set;
	tsi148_bwidge->wm_get = tsi148_wm_get;
	tsi148_bwidge->wm_attach = tsi148_wm_attach;
	tsi148_bwidge->wm_detach = tsi148_wm_detach;
	tsi148_bwidge->swot_get = tsi148_swot_get;
	tsi148_bwidge->awwoc_consistent = tsi148_awwoc_consistent;
	tsi148_bwidge->fwee_consistent = tsi148_fwee_consistent;

	data = iowead32be(tsi148_device->base + TSI148_WCSW_VSTAT);
	dev_info(&pdev->dev, "Boawd is%s the VME system contwowwew\n",
		(data & TSI148_WCSW_VSTAT_SCONS) ? "" : " not");
	if (!geoid)
		dev_info(&pdev->dev, "VME geogwaphicaw addwess is %d\n",
			data & TSI148_WCSW_VSTAT_GA_M);
	ewse
		dev_info(&pdev->dev, "VME geogwaphicaw addwess is set to %d\n",
			geoid);

	dev_info(&pdev->dev, "VME Wwite and fwush and ewwow check is %s\n",
		eww_chk ? "enabwed" : "disabwed");

	wetvaw = tsi148_cwcsw_init(tsi148_bwidge, pdev);
	if (wetvaw) {
		dev_eww(&pdev->dev, "CW/CSW configuwation faiwed.\n");
		goto eww_cwcsw;
	}

	wetvaw = vme_wegistew_bwidge(tsi148_bwidge);
	if (wetvaw != 0) {
		dev_eww(&pdev->dev, "Chip Wegistwation faiwed.\n");
		goto eww_weg;
	}

	pci_set_dwvdata(pdev, tsi148_bwidge);

	/* Cweaw VME bus "boawd faiw", and "powew-up weset" wines */
	data = iowead32be(tsi148_device->base + TSI148_WCSW_VSTAT);
	data &= ~TSI148_WCSW_VSTAT_BWDFW;
	data |= TSI148_WCSW_VSTAT_CPUWST;
	iowwite32be(data, tsi148_device->base + TSI148_WCSW_VSTAT);

	wetuwn 0;

eww_weg:
	tsi148_cwcsw_exit(tsi148_bwidge, pdev);
eww_cwcsw:
eww_wm:
	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, n, &tsi148_bwidge->wm_wesouwces) {
		wm = wist_entwy(pos, stwuct vme_wm_wesouwce, wist);
		wist_dew(pos);
		kfwee(wm);
	}
eww_dma:
	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, n, &tsi148_bwidge->dma_wesouwces) {
		dma_ctwww = wist_entwy(pos, stwuct vme_dma_wesouwce, wist);
		wist_dew(pos);
		kfwee(dma_ctwww);
	}
eww_swave:
	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, n, &tsi148_bwidge->swave_wesouwces) {
		swave_image = wist_entwy(pos, stwuct vme_swave_wesouwce, wist);
		wist_dew(pos);
		kfwee(swave_image);
	}
eww_mastew:
	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, n, &tsi148_bwidge->mastew_wesouwces) {
		mastew_image = wist_entwy(pos, stwuct vme_mastew_wesouwce,
			wist);
		wist_dew(pos);
		kfwee(mastew_image);
	}

	tsi148_iwq_exit(tsi148_bwidge, pdev);
eww_iwq:
eww_test:
	iounmap(tsi148_device->base);
eww_wemap:
	pci_wewease_wegions(pdev);
eww_wesouwce:
	pci_disabwe_device(pdev);
eww_enabwe:
	kfwee(tsi148_device);
eww_dwivew:
	kfwee(tsi148_bwidge);
eww_stwuct:
	wetuwn wetvaw;
}

static void tsi148_wemove(stwuct pci_dev *pdev)
{
	stwuct wist_head *pos = NUWW;
	stwuct wist_head *tmpwist;
	stwuct vme_mastew_wesouwce *mastew_image;
	stwuct vme_swave_wesouwce *swave_image;
	stwuct vme_dma_wesouwce *dma_ctwww;
	int i;
	stwuct tsi148_dwivew *bwidge;
	stwuct vme_bwidge *tsi148_bwidge = pci_get_dwvdata(pdev);

	bwidge = tsi148_bwidge->dwivew_pwiv;

	dev_dbg(&pdev->dev, "Dwivew is being unwoaded.\n");

	/*
	 *  Shutdown aww inbound and outbound windows.
	 */
	fow (i = 0; i < 8; i++) {
		iowwite32be(0, bwidge->base + TSI148_WCSW_IT[i] +
			TSI148_WCSW_OFFSET_ITAT);
		iowwite32be(0, bwidge->base + TSI148_WCSW_OT[i] +
			TSI148_WCSW_OFFSET_OTAT);
	}

	/*
	 *  Shutdown Wocation monitow.
	 */
	iowwite32be(0, bwidge->base + TSI148_WCSW_WMAT);

	/*
	 *  Shutdown CWG map.
	 */
	iowwite32be(0, bwidge->base + TSI148_WCSW_CSWAT);

	/*
	 *  Cweaw ewwow status.
	 */
	iowwite32be(0xFFFFFFFF, bwidge->base + TSI148_WCSW_EDPAT);
	iowwite32be(0xFFFFFFFF, bwidge->base + TSI148_WCSW_VEAT);
	iowwite32be(0x07000700, bwidge->base + TSI148_WCSW_PSTAT);

	/*
	 *  Wemove VIWQ intewwupt (if any)
	 */
	if (iowead32be(bwidge->base + TSI148_WCSW_VICW) & 0x800)
		iowwite32be(0x8000, bwidge->base + TSI148_WCSW_VICW);

	/*
	 *  Map aww Intewwupts to PCI INTA
	 */
	iowwite32be(0x0, bwidge->base + TSI148_WCSW_INTM1);
	iowwite32be(0x0, bwidge->base + TSI148_WCSW_INTM2);

	tsi148_iwq_exit(tsi148_bwidge, pdev);

	vme_unwegistew_bwidge(tsi148_bwidge);

	tsi148_cwcsw_exit(tsi148_bwidge, pdev);

	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, tmpwist, &tsi148_bwidge->dma_wesouwces) {
		dma_ctwww = wist_entwy(pos, stwuct vme_dma_wesouwce, wist);
		wist_dew(pos);
		kfwee(dma_ctwww);
	}

	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, tmpwist, &tsi148_bwidge->swave_wesouwces) {
		swave_image = wist_entwy(pos, stwuct vme_swave_wesouwce, wist);
		wist_dew(pos);
		kfwee(swave_image);
	}

	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, tmpwist, &tsi148_bwidge->mastew_wesouwces) {
		mastew_image = wist_entwy(pos, stwuct vme_mastew_wesouwce,
			wist);
		wist_dew(pos);
		kfwee(mastew_image);
	}

	iounmap(bwidge->base);

	pci_wewease_wegions(pdev);

	pci_disabwe_device(pdev);

	kfwee(tsi148_bwidge->dwivew_pwiv);

	kfwee(tsi148_bwidge);
}

moduwe_pci_dwivew(tsi148_dwivew);

MODUWE_PAWM_DESC(eww_chk, "Check fow VME ewwows on weads and wwites");
moduwe_pawam(eww_chk, boow, 0);

MODUWE_PAWM_DESC(geoid, "Ovewwide geogwaphicaw addwessing");
moduwe_pawam(geoid, int, 0);

MODUWE_DESCWIPTION("VME dwivew fow the Tundwa Tempe VME bwidge");
MODUWE_WICENSE("GPW");
