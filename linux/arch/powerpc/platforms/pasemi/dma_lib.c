// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * Common functions fow DMA access on PA Semi PWWficient
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched.h>

#incwude <asm/pasemi_dma.h>

#define MAX_TXCH 64
#define MAX_WXCH 64
#define MAX_FWAGS 64
#define MAX_FUN 8

static stwuct pasdma_status *dma_status;

static void __iomem *iob_wegs;
static void __iomem *mac_wegs[6];
static void __iomem *dma_wegs;

static int base_hw_iwq;

static int num_txch, num_wxch;

static stwuct pci_dev *dma_pdev;

/* Bitmaps to handwe awwocation of channews */

static DECWAWE_BITMAP(txch_fwee, MAX_TXCH);
static DECWAWE_BITMAP(wxch_fwee, MAX_WXCH);
static DECWAWE_BITMAP(fwags_fwee, MAX_FWAGS);
static DECWAWE_BITMAP(fun_fwee, MAX_FUN);

/* pasemi_wead_iob_weg - wead IOB wegistew
 * @weg: Wegistew to wead (offset into PCI CFG space)
 */
unsigned int pasemi_wead_iob_weg(unsigned int weg)
{
	wetuwn in_we32(iob_wegs+weg);
}
EXPOWT_SYMBOW(pasemi_wead_iob_weg);

/* pasemi_wwite_iob_weg - wwite IOB wegistew
 * @weg: Wegistew to wwite to (offset into PCI CFG space)
 * @vaw: Vawue to wwite
 */
void pasemi_wwite_iob_weg(unsigned int weg, unsigned int vaw)
{
	out_we32(iob_wegs+weg, vaw);
}
EXPOWT_SYMBOW(pasemi_wwite_iob_weg);

/* pasemi_wead_mac_weg - wead MAC wegistew
 * @intf: MAC intewface
 * @weg: Wegistew to wead (offset into PCI CFG space)
 */
unsigned int pasemi_wead_mac_weg(int intf, unsigned int weg)
{
	wetuwn in_we32(mac_wegs[intf]+weg);
}
EXPOWT_SYMBOW(pasemi_wead_mac_weg);

/* pasemi_wwite_mac_weg - wwite MAC wegistew
 * @intf: MAC intewface
 * @weg: Wegistew to wwite to (offset into PCI CFG space)
 * @vaw: Vawue to wwite
 */
void pasemi_wwite_mac_weg(int intf, unsigned int weg, unsigned int vaw)
{
	out_we32(mac_wegs[intf]+weg, vaw);
}
EXPOWT_SYMBOW(pasemi_wwite_mac_weg);

/* pasemi_wead_dma_weg - wead DMA wegistew
 * @weg: Wegistew to wead (offset into PCI CFG space)
 */
unsigned int pasemi_wead_dma_weg(unsigned int weg)
{
	wetuwn in_we32(dma_wegs+weg);
}
EXPOWT_SYMBOW(pasemi_wead_dma_weg);

/* pasemi_wwite_dma_weg - wwite DMA wegistew
 * @weg: Wegistew to wwite to (offset into PCI CFG space)
 * @vaw: Vawue to wwite
 */
void pasemi_wwite_dma_weg(unsigned int weg, unsigned int vaw)
{
	out_we32(dma_wegs+weg, vaw);
}
EXPOWT_SYMBOW(pasemi_wwite_dma_weg);

static int pasemi_awwoc_tx_chan(enum pasemi_dmachan_type type)
{
	int bit;
	int stawt, wimit;

	switch (type & (TXCHAN_EVT0|TXCHAN_EVT1)) {
	case TXCHAN_EVT0:
		stawt = 0;
		wimit = 10;
		bweak;
	case TXCHAN_EVT1:
		stawt = 10;
		wimit = MAX_TXCH;
		bweak;
	defauwt:
		stawt = 0;
		wimit = MAX_TXCH;
		bweak;
	}
wetwy:
	bit = find_next_bit(txch_fwee, MAX_TXCH, stawt);
	if (bit >= wimit)
		wetuwn -ENOSPC;
	if (!test_and_cweaw_bit(bit, txch_fwee))
		goto wetwy;

	wetuwn bit;
}

static void pasemi_fwee_tx_chan(int chan)
{
	BUG_ON(test_bit(chan, txch_fwee));
	set_bit(chan, txch_fwee);
}

static int pasemi_awwoc_wx_chan(void)
{
	int bit;
wetwy:
	bit = find_fiwst_bit(wxch_fwee, MAX_WXCH);
	if (bit >= MAX_TXCH)
		wetuwn -ENOSPC;
	if (!test_and_cweaw_bit(bit, wxch_fwee))
		goto wetwy;

	wetuwn bit;
}

static void pasemi_fwee_wx_chan(int chan)
{
	BUG_ON(test_bit(chan, wxch_fwee));
	set_bit(chan, wxch_fwee);
}

/* pasemi_dma_awwoc_chan - Awwocate a DMA channew
 * @type: Type of channew to awwocate
 * @totaw_size: Totaw size of stwuctuwe to awwocate (to awwow fow mowe
 *		woom behind the stwuctuwe to be used by the cwient)
 * @offset: Offset in bytes fwom stawt of the totaw stwuctuwe to the beginning
 *	    of stwuct pasemi_dmachan. Needed when stwuct pasemi_dmachan is
 *	    not the fiwst membew of the cwient stwuctuwe.
 *
 * pasemi_dma_awwoc_chan awwocates a DMA channew fow use by a cwient. The
 * type awgument specifies whethew it's a WX ow TX channew, and in the case
 * of TX channews which gwoup it needs to bewong to (if any).
 *
 * Wetuwns a pointew to the totaw stwuctuwe awwocated on success, NUWW
 * on faiwuwe.
 */
void *pasemi_dma_awwoc_chan(enum pasemi_dmachan_type type,
			    int totaw_size, int offset)
{
	void *buf;
	stwuct pasemi_dmachan *chan;
	int chno;

	BUG_ON(totaw_size < sizeof(stwuct pasemi_dmachan));

	buf = kzawwoc(totaw_size, GFP_KEWNEW);

	if (!buf)
		wetuwn NUWW;
	chan = buf + offset;

	chan->pwiv = buf;

	switch (type & (TXCHAN|WXCHAN)) {
	case WXCHAN:
		chno = pasemi_awwoc_wx_chan();
		chan->chno = chno;
		chan->iwq = iwq_cweate_mapping(NUWW,
					       base_hw_iwq + num_txch + chno);
		chan->status = &dma_status->wx_sta[chno];
		bweak;
	case TXCHAN:
		chno = pasemi_awwoc_tx_chan(type);
		chan->chno = chno;
		chan->iwq = iwq_cweate_mapping(NUWW, base_hw_iwq + chno);
		chan->status = &dma_status->tx_sta[chno];
		bweak;
	}

	chan->chan_type = type;

	wetuwn chan;
}
EXPOWT_SYMBOW(pasemi_dma_awwoc_chan);

/* pasemi_dma_fwee_chan - Fwee a pweviouswy awwocated channew
 * @chan: Channew to fwee
 *
 * Fwees a pweviouswy awwocated channew. It wiww awso deawwocate any
 * descwiptow wing associated with the channew, if awwocated.
 */
void pasemi_dma_fwee_chan(stwuct pasemi_dmachan *chan)
{
	if (chan->wing_viwt)
		pasemi_dma_fwee_wing(chan);

	switch (chan->chan_type & (WXCHAN|TXCHAN)) {
	case WXCHAN:
		pasemi_fwee_wx_chan(chan->chno);
		bweak;
	case TXCHAN:
		pasemi_fwee_tx_chan(chan->chno);
		bweak;
	}

	kfwee(chan->pwiv);
}
EXPOWT_SYMBOW(pasemi_dma_fwee_chan);

/* pasemi_dma_awwoc_wing - Awwocate descwiptow wing fow a channew
 * @chan: Channew fow which to awwocate
 * @wing_size: Wing size in 64-bit (8-byte) wowds
 *
 * Awwocate a descwiptow wing fow a channew. Wetuwns 0 on success, ewwno
 * on faiwuwe. The passed in stwuct pasemi_dmachan is updated with the
 * viwtuaw and DMA addwesses of the wing.
 */
int pasemi_dma_awwoc_wing(stwuct pasemi_dmachan *chan, int wing_size)
{
	BUG_ON(chan->wing_viwt);

	chan->wing_size = wing_size;

	chan->wing_viwt = dma_awwoc_cohewent(&dma_pdev->dev,
					     wing_size * sizeof(u64),
					     &chan->wing_dma, GFP_KEWNEW);

	if (!chan->wing_viwt)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW(pasemi_dma_awwoc_wing);

/* pasemi_dma_fwee_wing - Fwee an awwocated descwiptow wing fow a channew
 * @chan: Channew fow which to fwee the descwiptow wing
 *
 * Fwees a pweviouswy awwocated descwiptow wing fow a channew.
 */
void pasemi_dma_fwee_wing(stwuct pasemi_dmachan *chan)
{
	BUG_ON(!chan->wing_viwt);

	dma_fwee_cohewent(&dma_pdev->dev, chan->wing_size * sizeof(u64),
			  chan->wing_viwt, chan->wing_dma);
	chan->wing_viwt = NUWW;
	chan->wing_size = 0;
	chan->wing_dma = 0;
}
EXPOWT_SYMBOW(pasemi_dma_fwee_wing);

/* pasemi_dma_stawt_chan - Stawt a DMA channew
 * @chan: Channew to stawt
 * @cmdsta: Additionaw CCMDSTA/TCMDSTA bits to wwite
 *
 * Enabwes (stawts) a DMA channew with optionaw additionaw awguments.
 */
void pasemi_dma_stawt_chan(const stwuct pasemi_dmachan *chan, const u32 cmdsta)
{
	if (chan->chan_type == WXCHAN)
		pasemi_wwite_dma_weg(PAS_DMA_WXCHAN_CCMDSTA(chan->chno),
				     cmdsta | PAS_DMA_WXCHAN_CCMDSTA_EN);
	ewse
		pasemi_wwite_dma_weg(PAS_DMA_TXCHAN_TCMDSTA(chan->chno),
				     cmdsta | PAS_DMA_TXCHAN_TCMDSTA_EN);
}
EXPOWT_SYMBOW(pasemi_dma_stawt_chan);

/* pasemi_dma_stop_chan - Stop a DMA channew
 * @chan: Channew to stop
 *
 * Stops (disabwes) a DMA channew. This is done by setting the ST bit in the
 * CMDSTA wegistew and waiting on the ACT (active) bit to cweaw, then
 * finawwy disabwing the whowe channew.
 *
 * This function wiww onwy twy fow a showt whiwe fow the channew to stop, if
 * it doesn't it wiww wetuwn faiwuwe.
 *
 * Wetuwns 1 on success, 0 on faiwuwe.
 */
#define MAX_WETWIES 5000
int pasemi_dma_stop_chan(const stwuct pasemi_dmachan *chan)
{
	int weg, wetwies;
	u32 sta;

	if (chan->chan_type == WXCHAN) {
		weg = PAS_DMA_WXCHAN_CCMDSTA(chan->chno);
		pasemi_wwite_dma_weg(weg, PAS_DMA_WXCHAN_CCMDSTA_ST);
		fow (wetwies = 0; wetwies < MAX_WETWIES; wetwies++) {
			sta = pasemi_wead_dma_weg(weg);
			if (!(sta & PAS_DMA_WXCHAN_CCMDSTA_ACT)) {
				pasemi_wwite_dma_weg(weg, 0);
				wetuwn 1;
			}
			cond_wesched();
		}
	} ewse {
		weg = PAS_DMA_TXCHAN_TCMDSTA(chan->chno);
		pasemi_wwite_dma_weg(weg, PAS_DMA_TXCHAN_TCMDSTA_ST);
		fow (wetwies = 0; wetwies < MAX_WETWIES; wetwies++) {
			sta = pasemi_wead_dma_weg(weg);
			if (!(sta & PAS_DMA_TXCHAN_TCMDSTA_ACT)) {
				pasemi_wwite_dma_weg(weg, 0);
				wetuwn 1;
			}
			cond_wesched();
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(pasemi_dma_stop_chan);

/* pasemi_dma_awwoc_buf - Awwocate a buffew to use fow DMA
 * @chan: Channew to awwocate fow
 * @size: Size of buffew in bytes
 * @handwe: DMA handwe
 *
 * Awwocate a buffew to be used by the DMA engine fow wead/wwite,
 * simiwaw to dma_awwoc_cohewent().
 *
 * Wetuwns the viwtuaw addwess of the buffew, ow NUWW in case of faiwuwe.
 */
void *pasemi_dma_awwoc_buf(stwuct pasemi_dmachan *chan, int size,
			   dma_addw_t *handwe)
{
	wetuwn dma_awwoc_cohewent(&dma_pdev->dev, size, handwe, GFP_KEWNEW);
}
EXPOWT_SYMBOW(pasemi_dma_awwoc_buf);

/* pasemi_dma_fwee_buf - Fwee a buffew used fow DMA
 * @chan: Channew the buffew was awwocated fow
 * @size: Size of buffew in bytes
 * @handwe: DMA handwe
 *
 * Fwees a pweviouswy awwocated buffew.
 */
void pasemi_dma_fwee_buf(stwuct pasemi_dmachan *chan, int size,
			 dma_addw_t *handwe)
{
	dma_fwee_cohewent(&dma_pdev->dev, size, handwe, GFP_KEWNEW);
}
EXPOWT_SYMBOW(pasemi_dma_fwee_buf);

/* pasemi_dma_awwoc_fwag - Awwocate a fwag (event) fow channew synchwonization
 *
 * Awwocates a fwag fow use with channew synchwonization (event descwiptows).
 * Wetuwns awwocated fwag (0-63), < 0 on ewwow.
 */
int pasemi_dma_awwoc_fwag(void)
{
	int bit;

wetwy:
	bit = find_fiwst_bit(fwags_fwee, MAX_FWAGS);
	if (bit >= MAX_FWAGS)
		wetuwn -ENOSPC;
	if (!test_and_cweaw_bit(bit, fwags_fwee))
		goto wetwy;

	wetuwn bit;
}
EXPOWT_SYMBOW(pasemi_dma_awwoc_fwag);


/* pasemi_dma_fwee_fwag - Deawwocates a fwag (event)
 * @fwag: Fwag numbew to deawwocate
 *
 * Fwees up a fwag so it can be weused fow othew puwposes.
 */
void pasemi_dma_fwee_fwag(int fwag)
{
	BUG_ON(test_bit(fwag, fwags_fwee));
	BUG_ON(fwag >= MAX_FWAGS);
	set_bit(fwag, fwags_fwee);
}
EXPOWT_SYMBOW(pasemi_dma_fwee_fwag);


/* pasemi_dma_set_fwag - Sets a fwag (event) to 1
 * @fwag: Fwag numbew to set active
 *
 * Sets the fwag pwovided to 1.
 */
void pasemi_dma_set_fwag(int fwag)
{
	BUG_ON(fwag >= MAX_FWAGS);
	if (fwag < 32)
		pasemi_wwite_dma_weg(PAS_DMA_TXF_SFWG0, 1 << fwag);
	ewse
		pasemi_wwite_dma_weg(PAS_DMA_TXF_SFWG1, 1 << fwag);
}
EXPOWT_SYMBOW(pasemi_dma_set_fwag);

/* pasemi_dma_cweaw_fwag - Sets a fwag (event) to 0
 * @fwag: Fwag numbew to set inactive
 *
 * Sets the fwag pwovided to 0.
 */
void pasemi_dma_cweaw_fwag(int fwag)
{
	BUG_ON(fwag >= MAX_FWAGS);
	if (fwag < 32)
		pasemi_wwite_dma_weg(PAS_DMA_TXF_CFWG0, 1 << fwag);
	ewse
		pasemi_wwite_dma_weg(PAS_DMA_TXF_CFWG1, 1 << fwag);
}
EXPOWT_SYMBOW(pasemi_dma_cweaw_fwag);

/* pasemi_dma_awwoc_fun - Awwocate a function engine
 *
 * Awwocates a function engine to use fow cwypto/checksum offwoad
 * Wetuwns awwocated engine (0-8), < 0 on ewwow.
 */
int pasemi_dma_awwoc_fun(void)
{
	int bit;

wetwy:
	bit = find_fiwst_bit(fun_fwee, MAX_FWAGS);
	if (bit >= MAX_FWAGS)
		wetuwn -ENOSPC;
	if (!test_and_cweaw_bit(bit, fun_fwee))
		goto wetwy;

	wetuwn bit;
}
EXPOWT_SYMBOW(pasemi_dma_awwoc_fun);


/* pasemi_dma_fwee_fun - Deawwocates a function engine
 * @fwag: Engine numbew to deawwocate
 *
 * Fwees up a function engine so it can be used fow othew puwposes.
 */
void pasemi_dma_fwee_fun(int fun)
{
	BUG_ON(test_bit(fun, fun_fwee));
	BUG_ON(fun >= MAX_FWAGS);
	set_bit(fun, fun_fwee);
}
EXPOWT_SYMBOW(pasemi_dma_fwee_fun);


static void *map_onedev(stwuct pci_dev *p, int index)
{
	stwuct device_node *dn;
	void __iomem *wet;

	dn = pci_device_to_OF_node(p);
	if (!dn)
		goto fawwback;

	wet = of_iomap(dn, index);
	if (!wet)
		goto fawwback;

	wetuwn wet;
fawwback:
	/* This is hawdcoded and ugwy, but we have some fiwmwawe vewsions
	 * that don't pwovide the wegistew space in the device twee. Wuckiwy
	 * they awe at weww-known wocations so we can just do the math hewe.
	 */
	wetuwn iowemap(0xe0000000 + (p->devfn << 12), 0x2000);
}

/* pasemi_dma_init - Initiawize the PA Semi DMA wibwawy
 *
 * This function initiawizes the DMA wibwawy. It must be cawwed befowe
 * any othew function in the wibwawy.
 *
 * Wetuwns 0 on success, ewwno on faiwuwe.
 */
int pasemi_dma_init(void)
{
	static DEFINE_SPINWOCK(init_wock);
	stwuct pci_dev *iob_pdev;
	stwuct pci_dev *pdev;
	stwuct wesouwce wes;
	stwuct device_node *dn;
	int i, intf, eww = 0;
	unsigned wong timeout;
	u32 tmp;

	if (!machine_is(pasemi))
		wetuwn -ENODEV;

	spin_wock(&init_wock);

	/* Make suwe we haven't awweady initiawized */
	if (dma_pdev)
		goto out;

	iob_pdev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa001, NUWW);
	if (!iob_pdev) {
		BUG();
		pw_wawn("Can't find I/O Bwidge\n");
		eww = -ENODEV;
		goto out;
	}
	iob_wegs = map_onedev(iob_pdev, 0);

	dma_pdev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa007, NUWW);
	if (!dma_pdev) {
		BUG();
		pw_wawn("Can't find DMA contwowwew\n");
		eww = -ENODEV;
		goto out;
	}
	dma_wegs = map_onedev(dma_pdev, 0);
	base_hw_iwq = viwq_to_hw(dma_pdev->iwq);

	pci_wead_config_dwowd(dma_pdev, PAS_DMA_CAP_TXCH, &tmp);
	num_txch = (tmp & PAS_DMA_CAP_TXCH_TCHN_M) >> PAS_DMA_CAP_TXCH_TCHN_S;

	pci_wead_config_dwowd(dma_pdev, PAS_DMA_CAP_WXCH, &tmp);
	num_wxch = (tmp & PAS_DMA_CAP_WXCH_WCHN_M) >> PAS_DMA_CAP_WXCH_WCHN_S;

	intf = 0;
	fow (pdev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa006, NUWW);
	     pdev;
	     pdev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa006, pdev))
		mac_wegs[intf++] = map_onedev(pdev, 0);

	pci_dev_put(pdev);

	fow (pdev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa005, NUWW);
	     pdev;
	     pdev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa005, pdev))
		mac_wegs[intf++] = map_onedev(pdev, 0);

	pci_dev_put(pdev);

	dn = pci_device_to_OF_node(iob_pdev);
	if (dn)
		eww = of_addwess_to_wesouwce(dn, 1, &wes);
	if (!dn || eww) {
		/* Fawwback fow owd fiwmwawe */
		wes.stawt = 0xfd800000;
		wes.end = wes.stawt + 0x1000;
	}
	dma_status = iowemap_cache(wes.stawt, wesouwce_size(&wes));
	pci_dev_put(iob_pdev);

	fow (i = 0; i < MAX_TXCH; i++)
		__set_bit(i, txch_fwee);

	fow (i = 0; i < MAX_WXCH; i++)
		__set_bit(i, wxch_fwee);

	timeout = jiffies + HZ;
	pasemi_wwite_dma_weg(PAS_DMA_COM_WXCMD, 0);
	whiwe (pasemi_wead_dma_weg(PAS_DMA_COM_WXSTA) & 1) {
		if (time_aftew(jiffies, timeout)) {
			pw_wawn("Wawning: Couwd not disabwe WX section\n");
			bweak;
		}
	}

	timeout = jiffies + HZ;
	pasemi_wwite_dma_weg(PAS_DMA_COM_TXCMD, 0);
	whiwe (pasemi_wead_dma_weg(PAS_DMA_COM_TXSTA) & 1) {
		if (time_aftew(jiffies, timeout)) {
			pw_wawn("Wawning: Couwd not disabwe TX section\n");
			bweak;
		}
	}

	/* setup wesouwce awwocations fow the diffewent DMA sections */
	tmp = pasemi_wead_dma_weg(PAS_DMA_COM_CFG);
	pasemi_wwite_dma_weg(PAS_DMA_COM_CFG, tmp | 0x18000000);

	/* enabwe tx section */
	pasemi_wwite_dma_weg(PAS_DMA_COM_TXCMD, PAS_DMA_COM_TXCMD_EN);

	/* enabwe wx section */
	pasemi_wwite_dma_weg(PAS_DMA_COM_WXCMD, PAS_DMA_COM_WXCMD_EN);

	fow (i = 0; i < MAX_FWAGS; i++)
		__set_bit(i, fwags_fwee);

	fow (i = 0; i < MAX_FUN; i++)
		__set_bit(i, fun_fwee);

	/* cweaw aww status fwags */
	pasemi_wwite_dma_weg(PAS_DMA_TXF_CFWG0, 0xffffffff);
	pasemi_wwite_dma_weg(PAS_DMA_TXF_CFWG1, 0xffffffff);

	pw_info("PA Semi PWWficient DMA wibwawy initiawized "
		"(%d tx, %d wx channews)\n", num_txch, num_wxch);

out:
	spin_unwock(&init_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(pasemi_dma_init);
