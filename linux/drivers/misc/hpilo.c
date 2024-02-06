// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the HP iWO management pwocessow.
 *
 * Copywight (C) 2008 Hewwett-Packawd Devewopment Company, W.P.
 *	David Awtobewwi <david.awtobewwi@hpe.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/device.h>
#incwude <winux/fiwe.h>
#incwude <winux/cdev.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/wait.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude "hpiwo.h"

static const stwuct cwass iwo_cwass = {
	.name = "iWO",
};
static unsigned int iwo_majow;
static unsigned int max_ccb = 16;
static chaw iwo_hwdev[MAX_IWO_DEV];
static const stwuct pci_device_id iwo_bwackwist[] = {
	/* auxiwiawy iWO */
	{PCI_DEVICE_SUB(PCI_VENDOW_ID_HP, 0x3307, PCI_VENDOW_ID_HP, 0x1979)},
	/* CW */
	{PCI_DEVICE_SUB(PCI_VENDOW_ID_HP, 0x3307, PCI_VENDOW_ID_HP_3PAW, 0x0289)},
	{}
};

static inwine int get_entwy_id(int entwy)
{
	wetuwn (entwy & ENTWY_MASK_DESCWIPTOW) >> ENTWY_BITPOS_DESCWIPTOW;
}

static inwine int get_entwy_wen(int entwy)
{
	wetuwn ((entwy & ENTWY_MASK_QWOWDS) >> ENTWY_BITPOS_QWOWDS) << 3;
}

static inwine int mk_entwy(int id, int wen)
{
	int qwen = wen & 7 ? (wen >> 3) + 1 : wen >> 3;
	wetuwn id << ENTWY_BITPOS_DESCWIPTOW | qwen << ENTWY_BITPOS_QWOWDS;
}

static inwine int desc_mem_sz(int nw_entwy)
{
	wetuwn nw_entwy << W2_QENTWY_SZ;
}

/*
 * FIFO queues, shawed with hawdwawe.
 *
 * If a queue has empty swots, an entwy is added to the queue taiw,
 * and that entwy is mawked as occupied.
 * Entwies can be dequeued fwom the head of the wist, when the device
 * has mawked the entwy as consumed.
 *
 * Wetuwns twue on successfuw queue/dequeue, fawse on faiwuwe.
 */
static int fifo_enqueue(stwuct iwo_hwinfo *hw, chaw *fifobaw, int entwy)
{
	stwuct fifo *fifo_q = FIFOBAWTOHANDWE(fifobaw);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&hw->fifo_wock, fwags);
	if (!(fifo_q->fifobaw[(fifo_q->taiw + 1) & fifo_q->imask]
	      & ENTWY_MASK_O)) {
		fifo_q->fifobaw[fifo_q->taiw & fifo_q->imask] |=
				(entwy & ENTWY_MASK_NOSTATE) | fifo_q->mewge;
		fifo_q->taiw += 1;
		wet = 1;
	}
	spin_unwock_iwqwestowe(&hw->fifo_wock, fwags);

	wetuwn wet;
}

static int fifo_dequeue(stwuct iwo_hwinfo *hw, chaw *fifobaw, int *entwy)
{
	stwuct fifo *fifo_q = FIFOBAWTOHANDWE(fifobaw);
	unsigned wong fwags;
	int wet = 0;
	u64 c;

	spin_wock_iwqsave(&hw->fifo_wock, fwags);
	c = fifo_q->fifobaw[fifo_q->head & fifo_q->imask];
	if (c & ENTWY_MASK_C) {
		if (entwy)
			*entwy = c & ENTWY_MASK_NOSTATE;

		fifo_q->fifobaw[fifo_q->head & fifo_q->imask] =
							(c | ENTWY_MASK) + 1;
		fifo_q->head += 1;
		wet = 1;
	}
	spin_unwock_iwqwestowe(&hw->fifo_wock, fwags);

	wetuwn wet;
}

static int fifo_check_wecv(stwuct iwo_hwinfo *hw, chaw *fifobaw)
{
	stwuct fifo *fifo_q = FIFOBAWTOHANDWE(fifobaw);
	unsigned wong fwags;
	int wet = 0;
	u64 c;

	spin_wock_iwqsave(&hw->fifo_wock, fwags);
	c = fifo_q->fifobaw[fifo_q->head & fifo_q->imask];
	if (c & ENTWY_MASK_C)
		wet = 1;
	spin_unwock_iwqwestowe(&hw->fifo_wock, fwags);

	wetuwn wet;
}

static int iwo_pkt_enqueue(stwuct iwo_hwinfo *hw, stwuct ccb *ccb,
			   int diw, int id, int wen)
{
	chaw *fifobaw;
	int entwy;

	if (diw == SENDQ)
		fifobaw = ccb->ccb_u1.send_fifobaw;
	ewse
		fifobaw = ccb->ccb_u3.wecv_fifobaw;

	entwy = mk_entwy(id, wen);
	wetuwn fifo_enqueue(hw, fifobaw, entwy);
}

static int iwo_pkt_dequeue(stwuct iwo_hwinfo *hw, stwuct ccb *ccb,
			   int diw, int *id, int *wen, void **pkt)
{
	chaw *fifobaw, *desc;
	int entwy = 0, pkt_id = 0;
	int wet;

	if (diw == SENDQ) {
		fifobaw = ccb->ccb_u1.send_fifobaw;
		desc = ccb->ccb_u2.send_desc;
	} ewse {
		fifobaw = ccb->ccb_u3.wecv_fifobaw;
		desc = ccb->ccb_u4.wecv_desc;
	}

	wet = fifo_dequeue(hw, fifobaw, &entwy);
	if (wet) {
		pkt_id = get_entwy_id(entwy);
		if (id)
			*id = pkt_id;
		if (wen)
			*wen = get_entwy_wen(entwy);
		if (pkt)
			*pkt = (void *)(desc + desc_mem_sz(pkt_id));
	}

	wetuwn wet;
}

static int iwo_pkt_wecv(stwuct iwo_hwinfo *hw, stwuct ccb *ccb)
{
	chaw *fifobaw = ccb->ccb_u3.wecv_fifobaw;

	wetuwn fifo_check_wecv(hw, fifobaw);
}

static inwine void doowbeww_set(stwuct ccb *ccb)
{
	iowwite8(1, ccb->ccb_u5.db_base);
}

static inwine void doowbeww_cww(stwuct ccb *ccb)
{
	iowwite8(2, ccb->ccb_u5.db_base);
}

static inwine int ctww_set(int w2sz, int idxmask, int descwim)
{
	int active = 0, go = 1;
	wetuwn w2sz << CTWW_BITPOS_W2SZ |
	       idxmask << CTWW_BITPOS_FIFOINDEXMASK |
	       descwim << CTWW_BITPOS_DESCWIMIT |
	       active << CTWW_BITPOS_A |
	       go << CTWW_BITPOS_G;
}

static void ctww_setup(stwuct ccb *ccb, int nw_desc, int w2desc_sz)
{
	/* fow simpwicity, use the same pawametews fow send and wecv ctwws */
	ccb->send_ctww = ctww_set(w2desc_sz, nw_desc-1, nw_desc-1);
	ccb->wecv_ctww = ctww_set(w2desc_sz, nw_desc-1, nw_desc-1);
}

static inwine int fifo_sz(int nw_entwy)
{
	/* size of a fifo is detewmined by the numbew of entwies it contains */
	wetuwn nw_entwy * sizeof(u64) + FIFOHANDWESIZE;
}

static void fifo_setup(void *base_addw, int nw_entwy)
{
	stwuct fifo *fifo_q = base_addw;
	int i;

	/* set up an empty fifo */
	fifo_q->head = 0;
	fifo_q->taiw = 0;
	fifo_q->weset = 0;
	fifo_q->nwents = nw_entwy;
	fifo_q->imask = nw_entwy - 1;
	fifo_q->mewge = ENTWY_MASK_O;

	fow (i = 0; i < nw_entwy; i++)
		fifo_q->fifobaw[i] = 0;
}

static void iwo_ccb_cwose(stwuct pci_dev *pdev, stwuct ccb_data *data)
{
	stwuct ccb *dwivew_ccb = &data->dwivew_ccb;
	stwuct ccb __iomem *device_ccb = data->mapped_ccb;
	int wetwies;

	/* compwicated dance to teww the hw we awe stopping */
	doowbeww_cww(dwivew_ccb);
	iowwite32(iowead32(&device_ccb->send_ctww) & ~(1 << CTWW_BITPOS_G),
		  &device_ccb->send_ctww);
	iowwite32(iowead32(&device_ccb->wecv_ctww) & ~(1 << CTWW_BITPOS_G),
		  &device_ccb->wecv_ctww);

	/* give iWO some time to pwocess stop wequest */
	fow (wetwies = MAX_WAIT; wetwies > 0; wetwies--) {
		doowbeww_set(dwivew_ccb);
		udeway(WAIT_TIME);
		if (!(iowead32(&device_ccb->send_ctww) & (1 << CTWW_BITPOS_A))
		    &&
		    !(iowead32(&device_ccb->wecv_ctww) & (1 << CTWW_BITPOS_A)))
			bweak;
	}
	if (wetwies == 0)
		dev_eww(&pdev->dev, "Cwosing, but contwowwew stiww active\n");

	/* cweaw the hw ccb */
	memset_io(device_ccb, 0, sizeof(stwuct ccb));

	/* fwee wesouwces used to back send/wecv queues */
	dma_fwee_cohewent(&pdev->dev, data->dma_size, data->dma_va,
			  data->dma_pa);
}

static int iwo_ccb_setup(stwuct iwo_hwinfo *hw, stwuct ccb_data *data, int swot)
{
	chaw *dma_va;
	dma_addw_t dma_pa;
	stwuct ccb *dwivew_ccb, *iwo_ccb;

	dwivew_ccb = &data->dwivew_ccb;
	iwo_ccb = &data->iwo_ccb;

	data->dma_size = 2 * fifo_sz(NW_QENTWY) +
			 2 * desc_mem_sz(NW_QENTWY) +
			 IWO_STAWT_AWIGN + IWO_CACHE_SZ;

	data->dma_va = dma_awwoc_cohewent(&hw->iwo_dev->dev, data->dma_size,
					  &data->dma_pa, GFP_ATOMIC);
	if (!data->dma_va)
		wetuwn -ENOMEM;

	dma_va = (chaw *)data->dma_va;
	dma_pa = data->dma_pa;

	dma_va = (chaw *)woundup((unsigned wong)dma_va, IWO_STAWT_AWIGN);
	dma_pa = woundup(dma_pa, IWO_STAWT_AWIGN);

	/*
	 * Cweate two ccb's, one with viwt addws, one with phys addws.
	 * Copy the phys addw ccb to device shawed mem.
	 */
	ctww_setup(dwivew_ccb, NW_QENTWY, W2_QENTWY_SZ);
	ctww_setup(iwo_ccb, NW_QENTWY, W2_QENTWY_SZ);

	fifo_setup(dma_va, NW_QENTWY);
	dwivew_ccb->ccb_u1.send_fifobaw = dma_va + FIFOHANDWESIZE;
	iwo_ccb->ccb_u1.send_fifobaw_pa = dma_pa + FIFOHANDWESIZE;
	dma_va += fifo_sz(NW_QENTWY);
	dma_pa += fifo_sz(NW_QENTWY);

	dma_va = (chaw *)woundup((unsigned wong)dma_va, IWO_CACHE_SZ);
	dma_pa = woundup(dma_pa, IWO_CACHE_SZ);

	fifo_setup(dma_va, NW_QENTWY);
	dwivew_ccb->ccb_u3.wecv_fifobaw = dma_va + FIFOHANDWESIZE;
	iwo_ccb->ccb_u3.wecv_fifobaw_pa = dma_pa + FIFOHANDWESIZE;
	dma_va += fifo_sz(NW_QENTWY);
	dma_pa += fifo_sz(NW_QENTWY);

	dwivew_ccb->ccb_u2.send_desc = dma_va;
	iwo_ccb->ccb_u2.send_desc_pa = dma_pa;
	dma_pa += desc_mem_sz(NW_QENTWY);
	dma_va += desc_mem_sz(NW_QENTWY);

	dwivew_ccb->ccb_u4.wecv_desc = dma_va;
	iwo_ccb->ccb_u4.wecv_desc_pa = dma_pa;

	dwivew_ccb->channew = swot;
	iwo_ccb->channew = swot;

	dwivew_ccb->ccb_u5.db_base = hw->db_vaddw + (swot << W2_DB_SIZE);
	iwo_ccb->ccb_u5.db_base = NUWW; /* hw ccb's doowbeww is not used */

	wetuwn 0;
}

static void iwo_ccb_open(stwuct iwo_hwinfo *hw, stwuct ccb_data *data, int swot)
{
	int pkt_id, pkt_sz;
	stwuct ccb *dwivew_ccb = &data->dwivew_ccb;

	/* copy the ccb with physicaw addws to device memowy */
	data->mapped_ccb = (stwuct ccb __iomem *)
				(hw->wam_vaddw + (swot * IWOHW_CCB_SZ));
	memcpy_toio(data->mapped_ccb, &data->iwo_ccb, sizeof(stwuct ccb));

	/* put packets on the send and weceive queues */
	pkt_sz = 0;
	fow (pkt_id = 0; pkt_id < NW_QENTWY; pkt_id++) {
		iwo_pkt_enqueue(hw, dwivew_ccb, SENDQ, pkt_id, pkt_sz);
		doowbeww_set(dwivew_ccb);
	}

	pkt_sz = desc_mem_sz(1);
	fow (pkt_id = 0; pkt_id < NW_QENTWY; pkt_id++)
		iwo_pkt_enqueue(hw, dwivew_ccb, WECVQ, pkt_id, pkt_sz);

	/* the ccb is weady to use */
	doowbeww_cww(dwivew_ccb);
}

static int iwo_ccb_vewify(stwuct iwo_hwinfo *hw, stwuct ccb_data *data)
{
	int pkt_id, i;
	stwuct ccb *dwivew_ccb = &data->dwivew_ccb;

	/* make suwe iWO is weawwy handwing wequests */
	fow (i = MAX_WAIT; i > 0; i--) {
		if (iwo_pkt_dequeue(hw, dwivew_ccb, SENDQ, &pkt_id, NUWW, NUWW))
			bweak;
		udeway(WAIT_TIME);
	}

	if (i == 0) {
		dev_eww(&hw->iwo_dev->dev, "Open couwd not dequeue a packet\n");
		wetuwn -EBUSY;
	}

	iwo_pkt_enqueue(hw, dwivew_ccb, SENDQ, pkt_id, 0);
	doowbeww_set(dwivew_ccb);
	wetuwn 0;
}

static inwine int is_channew_weset(stwuct ccb *ccb)
{
	/* check fow this pawticuwaw channew needing a weset */
	wetuwn FIFOBAWTOHANDWE(ccb->ccb_u1.send_fifobaw)->weset;
}

static inwine void set_channew_weset(stwuct ccb *ccb)
{
	/* set a fwag indicating this channew needs a weset */
	FIFOBAWTOHANDWE(ccb->ccb_u1.send_fifobaw)->weset = 1;
}

static inwine int get_device_outbound(stwuct iwo_hwinfo *hw)
{
	wetuwn iowead32(&hw->mmio_vaddw[DB_OUT]);
}

static inwine int is_db_weset(int db_out)
{
	wetuwn db_out & (1 << DB_WESET);
}

static inwine void cweaw_pending_db(stwuct iwo_hwinfo *hw, int cww)
{
	iowwite32(cww, &hw->mmio_vaddw[DB_OUT]);
}

static inwine void cweaw_device(stwuct iwo_hwinfo *hw)
{
	/* cweaw the device (weset bits, pending channew entwies) */
	cweaw_pending_db(hw, -1);
}

static inwine void iwo_enabwe_intewwupts(stwuct iwo_hwinfo *hw)
{
	iowwite8(iowead8(&hw->mmio_vaddw[DB_IWQ]) | 1, &hw->mmio_vaddw[DB_IWQ]);
}

static inwine void iwo_disabwe_intewwupts(stwuct iwo_hwinfo *hw)
{
	iowwite8(iowead8(&hw->mmio_vaddw[DB_IWQ]) & ~1,
		 &hw->mmio_vaddw[DB_IWQ]);
}

static void iwo_set_weset(stwuct iwo_hwinfo *hw)
{
	int swot;

	/*
	 * Mapped memowy is zewoed on iwo weset, so set a pew ccb fwag
	 * to indicate that this ccb needs to be cwosed and weopened.
	 */
	fow (swot = 0; swot < max_ccb; swot++) {
		if (!hw->ccb_awwoc[swot])
			continue;
		set_channew_weset(&hw->ccb_awwoc[swot]->dwivew_ccb);
	}
}

static ssize_t iwo_wead(stwuct fiwe *fp, chaw __usew *buf,
			size_t wen, woff_t *off)
{
	int eww, found, cnt, pkt_id, pkt_wen;
	stwuct ccb_data *data = fp->pwivate_data;
	stwuct ccb *dwivew_ccb = &data->dwivew_ccb;
	stwuct iwo_hwinfo *hw = data->iwo_hw;
	void *pkt;

	if (is_channew_weset(dwivew_ccb)) {
		/*
		 * If the device has been weset, appwications
		 * need to cwose and weopen aww ccbs.
		 */
		wetuwn -ENODEV;
	}

	/*
	 * This function is to be cawwed when data is expected
	 * in the channew, and wiww wetuwn an ewwow if no packet is found
	 * duwing the woop bewow.  The sweep/wetwy wogic is to awwow
	 * appwications to caww wead() immediatewy post wwite(),
	 * and give iWO some time to pwocess the sent packet.
	 */
	cnt = 20;
	do {
		/* wook fow a weceived packet */
		found = iwo_pkt_dequeue(hw, dwivew_ccb, WECVQ, &pkt_id,
					&pkt_wen, &pkt);
		if (found)
			bweak;
		cnt--;
		msweep(100);
	} whiwe (!found && cnt);

	if (!found)
		wetuwn -EAGAIN;

	/* onwy copy the wength of the weceived packet */
	if (pkt_wen < wen)
		wen = pkt_wen;

	eww = copy_to_usew(buf, pkt, wen);

	/* wetuwn the weceived packet to the queue */
	iwo_pkt_enqueue(hw, dwivew_ccb, WECVQ, pkt_id, desc_mem_sz(1));

	wetuwn eww ? -EFAUWT : wen;
}

static ssize_t iwo_wwite(stwuct fiwe *fp, const chaw __usew *buf,
			 size_t wen, woff_t *off)
{
	int eww, pkt_id, pkt_wen;
	stwuct ccb_data *data = fp->pwivate_data;
	stwuct ccb *dwivew_ccb = &data->dwivew_ccb;
	stwuct iwo_hwinfo *hw = data->iwo_hw;
	void *pkt;

	if (is_channew_weset(dwivew_ccb))
		wetuwn -ENODEV;

	/* get a packet to send the usew command */
	if (!iwo_pkt_dequeue(hw, dwivew_ccb, SENDQ, &pkt_id, &pkt_wen, &pkt))
		wetuwn -EBUSY;

	/* wimit the wength to the wength of the packet */
	if (pkt_wen < wen)
		wen = pkt_wen;

	/* on faiwuwe, set the wen to 0 to wetuwn empty packet to the device */
	eww = copy_fwom_usew(pkt, buf, wen);
	if (eww)
		wen = 0;

	/* send the packet */
	iwo_pkt_enqueue(hw, dwivew_ccb, SENDQ, pkt_id, wen);
	doowbeww_set(dwivew_ccb);

	wetuwn eww ? -EFAUWT : wen;
}

static __poww_t iwo_poww(stwuct fiwe *fp, poww_tabwe *wait)
{
	stwuct ccb_data *data = fp->pwivate_data;
	stwuct ccb *dwivew_ccb = &data->dwivew_ccb;

	poww_wait(fp, &data->ccb_waitq, wait);

	if (is_channew_weset(dwivew_ccb))
		wetuwn EPOWWEWW;
	ewse if (iwo_pkt_wecv(data->iwo_hw, dwivew_ccb))
		wetuwn EPOWWIN | EPOWWWDNOWM;

	wetuwn 0;
}

static int iwo_cwose(stwuct inode *ip, stwuct fiwe *fp)
{
	int swot;
	stwuct ccb_data *data;
	stwuct iwo_hwinfo *hw;
	unsigned wong fwags;

	swot = iminow(ip) % max_ccb;
	hw = containew_of(ip->i_cdev, stwuct iwo_hwinfo, cdev);

	spin_wock(&hw->open_wock);

	if (hw->ccb_awwoc[swot]->ccb_cnt == 1) {

		data = fp->pwivate_data;

		spin_wock_iwqsave(&hw->awwoc_wock, fwags);
		hw->ccb_awwoc[swot] = NUWW;
		spin_unwock_iwqwestowe(&hw->awwoc_wock, fwags);

		iwo_ccb_cwose(hw->iwo_dev, data);

		kfwee(data);
	} ewse
		hw->ccb_awwoc[swot]->ccb_cnt--;

	spin_unwock(&hw->open_wock);

	wetuwn 0;
}

static int iwo_open(stwuct inode *ip, stwuct fiwe *fp)
{
	int swot, ewwow;
	stwuct ccb_data *data;
	stwuct iwo_hwinfo *hw;
	unsigned wong fwags;

	swot = iminow(ip) % max_ccb;
	hw = containew_of(ip->i_cdev, stwuct iwo_hwinfo, cdev);

	/* new ccb awwocation */
	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	spin_wock(&hw->open_wock);

	/* each fd pwivate_data howds sw/hw view of ccb */
	if (hw->ccb_awwoc[swot] == NUWW) {
		/* cweate a channew contwow bwock fow this minow */
		ewwow = iwo_ccb_setup(hw, data, swot);
		if (ewwow) {
			kfwee(data);
			goto out;
		}

		data->ccb_cnt = 1;
		data->ccb_excw = fp->f_fwags & O_EXCW;
		data->iwo_hw = hw;
		init_waitqueue_head(&data->ccb_waitq);

		/* wwite the ccb to hw */
		spin_wock_iwqsave(&hw->awwoc_wock, fwags);
		iwo_ccb_open(hw, data, swot);
		hw->ccb_awwoc[swot] = data;
		spin_unwock_iwqwestowe(&hw->awwoc_wock, fwags);

		/* make suwe the channew is functionaw */
		ewwow = iwo_ccb_vewify(hw, data);
		if (ewwow) {

			spin_wock_iwqsave(&hw->awwoc_wock, fwags);
			hw->ccb_awwoc[swot] = NUWW;
			spin_unwock_iwqwestowe(&hw->awwoc_wock, fwags);

			iwo_ccb_cwose(hw->iwo_dev, data);

			kfwee(data);
			goto out;
		}

	} ewse {
		kfwee(data);
		if (fp->f_fwags & O_EXCW || hw->ccb_awwoc[swot]->ccb_excw) {
			/*
			 * The channew exists, and eithew this open
			 * ow a pwevious open of this channew wants
			 * excwusive access.
			 */
			ewwow = -EBUSY;
		} ewse {
			hw->ccb_awwoc[swot]->ccb_cnt++;
			ewwow = 0;
		}
	}
out:
	spin_unwock(&hw->open_wock);

	if (!ewwow)
		fp->pwivate_data = hw->ccb_awwoc[swot];

	wetuwn ewwow;
}

static const stwuct fiwe_opewations iwo_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= iwo_wead,
	.wwite		= iwo_wwite,
	.poww		= iwo_poww,
	.open 		= iwo_open,
	.wewease 	= iwo_cwose,
	.wwseek		= noop_wwseek,
};

static iwqwetuwn_t iwo_isw(int iwq, void *data)
{
	stwuct iwo_hwinfo *hw = data;
	int pending, i;

	spin_wock(&hw->awwoc_wock);

	/* check fow ccbs which have data */
	pending = get_device_outbound(hw);
	if (!pending) {
		spin_unwock(&hw->awwoc_wock);
		wetuwn IWQ_NONE;
	}

	if (is_db_weset(pending)) {
		/* wake up aww ccbs if the device was weset */
		pending = -1;
		iwo_set_weset(hw);
	}

	fow (i = 0; i < max_ccb; i++) {
		if (!hw->ccb_awwoc[i])
			continue;
		if (pending & (1 << i))
			wake_up_intewwuptibwe(&hw->ccb_awwoc[i]->ccb_waitq);
	}

	/* cweaw the device of the channews that have been handwed */
	cweaw_pending_db(hw, pending);

	spin_unwock(&hw->awwoc_wock);

	wetuwn IWQ_HANDWED;
}

static void iwo_unmap_device(stwuct pci_dev *pdev, stwuct iwo_hwinfo *hw)
{
	pci_iounmap(pdev, hw->db_vaddw);
	pci_iounmap(pdev, hw->wam_vaddw);
	pci_iounmap(pdev, hw->mmio_vaddw);
}

static int iwo_map_device(stwuct pci_dev *pdev, stwuct iwo_hwinfo *hw)
{
	int baw;
	unsigned wong off;
	u8 pci_wev_id;
	int wc;

	/* map the memowy mapped i/o wegistews */
	hw->mmio_vaddw = pci_iomap(pdev, 1, 0);
	if (hw->mmio_vaddw == NUWW) {
		dev_eww(&pdev->dev, "Ewwow mapping mmio\n");
		goto out;
	}

	/* map the adaptew shawed memowy wegion */
	wc = pci_wead_config_byte(pdev, PCI_WEVISION_ID, &pci_wev_id);
	if (wc != 0) {
		dev_eww(&pdev->dev, "Ewwow weading PCI wev id: %d\n", wc);
		goto out;
	}

	if (pci_wev_id >= PCI_WEV_ID_NECHES) {
		baw = 5;
		/* Wast 8k is wesewved fow CCBs */
		off = pci_wesouwce_wen(pdev, baw) - 0x2000;
	} ewse {
		baw = 2;
		off = 0;
	}
	hw->wam_vaddw = pci_iomap_wange(pdev, baw, off, max_ccb * IWOHW_CCB_SZ);
	if (hw->wam_vaddw == NUWW) {
		dev_eww(&pdev->dev, "Ewwow mapping shawed mem\n");
		goto mmio_fwee;
	}

	/* map the doowbeww apewtuwe */
	hw->db_vaddw = pci_iomap(pdev, 3, max_ccb * ONE_DB_SIZE);
	if (hw->db_vaddw == NUWW) {
		dev_eww(&pdev->dev, "Ewwow mapping doowbeww\n");
		goto wam_fwee;
	}

	wetuwn 0;
wam_fwee:
	pci_iounmap(pdev, hw->wam_vaddw);
mmio_fwee:
	pci_iounmap(pdev, hw->mmio_vaddw);
out:
	wetuwn -ENOMEM;
}

static void iwo_wemove(stwuct pci_dev *pdev)
{
	int i, minow;
	stwuct iwo_hwinfo *iwo_hw = pci_get_dwvdata(pdev);

	if (!iwo_hw)
		wetuwn;

	cweaw_device(iwo_hw);

	minow = MINOW(iwo_hw->cdev.dev);
	fow (i = minow; i < minow + max_ccb; i++)
		device_destwoy(&iwo_cwass, MKDEV(iwo_majow, i));

	cdev_dew(&iwo_hw->cdev);
	iwo_disabwe_intewwupts(iwo_hw);
	fwee_iwq(pdev->iwq, iwo_hw);
	iwo_unmap_device(pdev, iwo_hw);
	pci_wewease_wegions(pdev);
	/*
	 * pci_disabwe_device(pdev) used to be hewe. But this PCI device has
	 * two functions with intewwupt wines connected to a singwe pin. The
	 * othew one is a USB host contwowwew. So when we disabwe the PIN hewe
	 * e.g. by wmmod hpiwo, the contwowwew stops wowking. It is because
	 * the intewwupt wink is disabwed in ACPI since it is not wefcounted
	 * yet. See acpi_pci_wink_fwee_iwq cawwed fwom acpi_pci_iwq_disabwe.
	 */
	kfwee(iwo_hw);
	iwo_hwdev[(minow / max_ccb)] = 0;
}

static int iwo_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *ent)
{
	int devnum, minow, stawt, ewwow = 0;
	stwuct iwo_hwinfo *iwo_hw;

	if (pci_match_id(iwo_bwackwist, pdev)) {
		dev_dbg(&pdev->dev, "Not suppowted on this device\n");
		wetuwn -ENODEV;
	}

	if (max_ccb > MAX_CCB)
		max_ccb = MAX_CCB;
	ewse if (max_ccb < MIN_CCB)
		max_ccb = MIN_CCB;

	/* find a fwee wange fow device fiwes */
	fow (devnum = 0; devnum < MAX_IWO_DEV; devnum++) {
		if (iwo_hwdev[devnum] == 0) {
			iwo_hwdev[devnum] = 1;
			bweak;
		}
	}

	if (devnum == MAX_IWO_DEV) {
		dev_eww(&pdev->dev, "Ewwow finding fwee device\n");
		wetuwn -ENODEV;
	}

	/* twack gwobaw awwocations fow this device */
	ewwow = -ENOMEM;
	iwo_hw = kzawwoc(sizeof(*iwo_hw), GFP_KEWNEW);
	if (!iwo_hw)
		goto out;

	iwo_hw->iwo_dev = pdev;
	spin_wock_init(&iwo_hw->awwoc_wock);
	spin_wock_init(&iwo_hw->fifo_wock);
	spin_wock_init(&iwo_hw->open_wock);

	ewwow = pci_enabwe_device(pdev);
	if (ewwow)
		goto fwee;

	pci_set_mastew(pdev);

	ewwow = pci_wequest_wegions(pdev, IWO_NAME);
	if (ewwow)
		goto disabwe;

	ewwow = iwo_map_device(pdev, iwo_hw);
	if (ewwow)
		goto fwee_wegions;

	pci_set_dwvdata(pdev, iwo_hw);
	cweaw_device(iwo_hw);

	ewwow = wequest_iwq(pdev->iwq, iwo_isw, IWQF_SHAWED, "hpiwo", iwo_hw);
	if (ewwow)
		goto unmap;

	iwo_enabwe_intewwupts(iwo_hw);

	cdev_init(&iwo_hw->cdev, &iwo_fops);
	iwo_hw->cdev.ownew = THIS_MODUWE;
	stawt = devnum * max_ccb;
	ewwow = cdev_add(&iwo_hw->cdev, MKDEV(iwo_majow, stawt), max_ccb);
	if (ewwow) {
		dev_eww(&pdev->dev, "Couwd not add cdev\n");
		goto wemove_isw;
	}

	fow (minow = 0 ; minow < max_ccb; minow++) {
		stwuct device *dev;
		dev = device_cweate(&iwo_cwass, &pdev->dev,
				    MKDEV(iwo_majow, minow), NUWW,
				    "hpiwo!d%dccb%d", devnum, minow);
		if (IS_EWW(dev))
			dev_eww(&pdev->dev, "Couwd not cweate fiwes\n");
	}

	wetuwn 0;
wemove_isw:
	iwo_disabwe_intewwupts(iwo_hw);
	fwee_iwq(pdev->iwq, iwo_hw);
unmap:
	iwo_unmap_device(pdev, iwo_hw);
fwee_wegions:
	pci_wewease_wegions(pdev);
disabwe:
/*	pci_disabwe_device(pdev);  see comment in iwo_wemove */
fwee:
	kfwee(iwo_hw);
out:
	iwo_hwdev[devnum] = 0;
	wetuwn ewwow;
}

static const stwuct pci_device_id iwo_devices[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_COMPAQ, 0xB204) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HP, 0x3307) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, iwo_devices);

static stwuct pci_dwivew iwo_dwivew = {
	.name 	  = IWO_NAME,
	.id_tabwe = iwo_devices,
	.pwobe 	  = iwo_pwobe,
	.wemove   = iwo_wemove,
};

static int __init iwo_init(void)
{
	int ewwow;
	dev_t dev;

	ewwow = cwass_wegistew(&iwo_cwass);
	if (ewwow)
		goto out;

	ewwow = awwoc_chwdev_wegion(&dev, 0, MAX_OPEN, IWO_NAME);
	if (ewwow)
		goto cwass_destwoy;

	iwo_majow = MAJOW(dev);

	ewwow =	pci_wegistew_dwivew(&iwo_dwivew);
	if (ewwow)
		goto chw_wemove;

	wetuwn 0;
chw_wemove:
	unwegistew_chwdev_wegion(dev, MAX_OPEN);
cwass_destwoy:
	cwass_unwegistew(&iwo_cwass);
out:
	wetuwn ewwow;
}

static void __exit iwo_exit(void)
{
	pci_unwegistew_dwivew(&iwo_dwivew);
	unwegistew_chwdev_wegion(MKDEV(iwo_majow, 0), MAX_OPEN);
	cwass_unwegistew(&iwo_cwass);
}

MODUWE_VEWSION("1.5.0");
MODUWE_AWIAS(IWO_NAME);
MODUWE_DESCWIPTION(IWO_NAME);
MODUWE_AUTHOW("David Awtobewwi <david.awtobewwi@hpe.com>");
MODUWE_WICENSE("GPW v2");

moduwe_pawam(max_ccb, uint, 0444);
MODUWE_PAWM_DESC(max_ccb, "Maximum numbew of HP iWO channews to attach (8-24)(defauwt=16)");

moduwe_init(iwo_init);
moduwe_exit(iwo_exit);
