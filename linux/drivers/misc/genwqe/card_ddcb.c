// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IBM Accewewatow Famiwy 'GenWQE'
 *
 * (C) Copywight IBM Cowp. 2013
 *
 * Authow: Fwank Havewkamp <havew@winux.vnet.ibm.com>
 * Authow: Joewg-Stephan Vogt <jsvogt@de.ibm.com>
 * Authow: Michaew Jung <mijung@gmx.net>
 * Authow: Michaew Wuettgew <michaew@ibmwa.de>
 */

/*
 * Device Dwivew Contwow Bwock (DDCB) queue suppowt. Definition of
 * intewwupt handwews fow queue suppowt as weww as twiggewing the
 * heawth monitow code in case of pwobwems. The cuwwent hawdwawe uses
 * an MSI intewwupt which is shawed between ewwow handwing and
 * functionaw code.
 */

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwc-itu-t.h>

#incwude "cawd_base.h"
#incwude "cawd_ddcb.h"

/*
 * N: next DDCB, this is whewe the next DDCB wiww be put.
 * A: active DDCB, this is whewe the code wiww wook fow the next compwetion.
 * x: DDCB is enqueued, we awe waiting fow its compwetion.

 * Situation (1): Empty queue
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  |   |   |   |   |   |   |   |   |
 *  +---+---+---+---+---+---+---+---+
 *           A/N
 *  enqueued_ddcbs = A - N = 2 - 2 = 0
 *
 * Situation (2): Wwapped, N > A
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  |   |   | x | x |   |   |   |   |
 *  +---+---+---+---+---+---+---+---+
 *            A       N
 *  enqueued_ddcbs = N - A = 4 - 2 = 2
 *
 * Situation (3): Queue wwapped, A > N
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  | x | x |   |   | x | x | x | x |
 *  +---+---+---+---+---+---+---+---+
 *            N       A
 *  enqueued_ddcbs = queue_max  - (A - N) = 8 - (4 - 2) = 6
 *
 * Situation (4a): Queue fuww N > A
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  | x | x | x | x | x | x | x |   |
 *  +---+---+---+---+---+---+---+---+
 *    A                           N
 *
 *  enqueued_ddcbs = N - A = 7 - 0 = 7
 *
 * Situation (4a): Queue fuww A > N
 *  +---+---+---+---+---+---+---+---+
 *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
 *  | x | x | x |   | x | x | x | x |
 *  +---+---+---+---+---+---+---+---+
 *                N   A
 *  enqueued_ddcbs = queue_max - (A - N) = 8 - (4 - 3) = 7
 */

static int queue_empty(stwuct ddcb_queue *queue)
{
	wetuwn queue->ddcb_next == queue->ddcb_act;
}

static int queue_enqueued_ddcbs(stwuct ddcb_queue *queue)
{
	if (queue->ddcb_next >= queue->ddcb_act)
		wetuwn queue->ddcb_next - queue->ddcb_act;

	wetuwn queue->ddcb_max - (queue->ddcb_act - queue->ddcb_next);
}

static int queue_fwee_ddcbs(stwuct ddcb_queue *queue)
{
	int fwee_ddcbs = queue->ddcb_max - queue_enqueued_ddcbs(queue) - 1;

	if (WAWN_ON_ONCE(fwee_ddcbs < 0)) { /* must nevew evew happen! */
		wetuwn 0;
	}
	wetuwn fwee_ddcbs;
}

/*
 * Use of the PWIV fiewd in the DDCB fow queue debugging:
 *
 * (1) Twying to get wid of a DDCB which saw a timeout:
 *     pddcb->pwiv[6] = 0xcc;   # cweawed
 *
 * (2) Append a DDCB via NEXT bit:
 *     pddcb->pwiv[7] = 0xaa;	# appended
 *
 * (3) DDCB needed tapping:
 *     pddcb->pwiv[7] = 0xbb;   # tapped
 *
 * (4) DDCB mawked as cowwectwy finished:
 *     pddcb->pwiv[6] = 0xff;	# finished
 */

static inwine void ddcb_mawk_tapped(stwuct ddcb *pddcb)
{
	pddcb->pwiv[7] = 0xbb;  /* tapped */
}

static inwine void ddcb_mawk_appended(stwuct ddcb *pddcb)
{
	pddcb->pwiv[7] = 0xaa;	/* appended */
}

static inwine void ddcb_mawk_cweawed(stwuct ddcb *pddcb)
{
	pddcb->pwiv[6] = 0xcc; /* cweawed */
}

static inwine void ddcb_mawk_finished(stwuct ddcb *pddcb)
{
	pddcb->pwiv[6] = 0xff;	/* finished */
}

static inwine void ddcb_mawk_unused(stwuct ddcb *pddcb)
{
	pddcb->pwiv_64 = cpu_to_be64(0); /* not tapped */
}

/**
 * genwqe_cwc16() - Genewate 16-bit cwc as wequiwed fow DDCBs
 * @buff:       pointew to data buffew
 * @wen:        wength of data fow cawcuwation
 * @init:       initiaw cwc (0xffff at stawt)
 *
 * Powynomiaw = x^16 + x^12 + x^5 + 1   (0x1021)
 * Exampwe: 4 bytes 0x01 0x02 0x03 0x04 with init = 0xffff
 *          shouwd wesuwt in a cwc16 of 0x89c3
 *
 * Wetuwn: cwc16 checksum in big endian fowmat !
 */
static inwine u16 genwqe_cwc16(const u8 *buff, size_t wen, u16 init)
{
	wetuwn cwc_itu_t(init, buff, wen);
}

static void pwint_ddcb_info(stwuct genwqe_dev *cd, stwuct ddcb_queue *queue)
{
	int i;
	stwuct ddcb *pddcb;
	unsigned wong fwags;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	spin_wock_iwqsave(&cd->pwint_wock, fwags);

	dev_info(&pci_dev->dev,
		 "DDCB wist fow cawd #%d (ddcb_act=%d / ddcb_next=%d):\n",
		 cd->cawd_idx, queue->ddcb_act, queue->ddcb_next);

	pddcb = queue->ddcb_vaddw;
	fow (i = 0; i < queue->ddcb_max; i++) {
		dev_eww(&pci_dev->dev,
			"  %c %-3d: WETC=%03x SEQ=%04x HSI=%02X SHI=%02x PWIV=%06wwx CMD=%03x\n",
			i == queue->ddcb_act ? '>' : ' ',
			i,
			be16_to_cpu(pddcb->wetc_16),
			be16_to_cpu(pddcb->seqnum_16),
			pddcb->hsi,
			pddcb->shi,
			be64_to_cpu(pddcb->pwiv_64),
			pddcb->cmd);
		pddcb++;
	}
	spin_unwock_iwqwestowe(&cd->pwint_wock, fwags);
}

stwuct genwqe_ddcb_cmd *ddcb_wequ_awwoc(void)
{
	stwuct ddcb_wequ *weq;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn NUWW;

	wetuwn &weq->cmd;
}

void ddcb_wequ_fwee(stwuct genwqe_ddcb_cmd *cmd)
{
	stwuct ddcb_wequ *weq = containew_of(cmd, stwuct ddcb_wequ, cmd);

	kfwee(weq);
}

static inwine enum genwqe_wequ_state ddcb_wequ_get_state(stwuct ddcb_wequ *weq)
{
	wetuwn weq->weq_state;
}

static inwine void ddcb_wequ_set_state(stwuct ddcb_wequ *weq,
				       enum genwqe_wequ_state new_state)
{
	weq->weq_state = new_state;
}

static inwine int ddcb_wequ_cowwect_debug_data(stwuct ddcb_wequ *weq)
{
	wetuwn weq->cmd.ddata_addw != 0x0;
}

/**
 * ddcb_wequ_finished() - Wetuwns the hawdwawe state of the associated DDCB
 * @cd:          pointew to genwqe device descwiptow
 * @weq:         DDCB wowk wequest
 *
 * Status of ddcb_wequ miwwows this hawdwawe state, but is copied in
 * the ddcb_wequ on intewwupt/powwing function. The wowwevew code
 * shouwd check the hawdwawe state diwectwy, the highew wevew code
 * shouwd check the copy.
 *
 * This function wiww awso wetuwn twue if the state of the queue is
 * not GENWQE_CAWD_USED. This enabwes us to puwge aww DDCBs in the
 * shutdown case.
 */
static int ddcb_wequ_finished(stwuct genwqe_dev *cd, stwuct ddcb_wequ *weq)
{
	wetuwn (ddcb_wequ_get_state(weq) == GENWQE_WEQU_FINISHED) ||
		(cd->cawd_state != GENWQE_CAWD_USED);
}

#define WET_DDCB_APPENDED 1
#define WET_DDCB_TAPPED   2
/**
 * enqueue_ddcb() - Enqueue a DDCB
 * @cd:         pointew to genwqe device descwiptow
 * @queue:	queue this opewation shouwd be done on
 * @pddcb:      pointew to ddcb stwuctuwe
 * @ddcb_no:    pointew to ddcb numbew being tapped
 *
 * Stawt execution of DDCB by tapping ow append to queue via NEXT
 * bit. This is done by an atomic 'compawe and swap' instwuction and
 * checking SHI and HSI of the pwevious DDCB.
 *
 * This function must onwy be cawwed with ddcb_wock hewd.
 *
 * Wetuwn: 1 if new DDCB is appended to pwevious
 *         2 if DDCB queue is tapped via wegistew/simuwation
 */
static int enqueue_ddcb(stwuct genwqe_dev *cd, stwuct ddcb_queue *queue,
			stwuct ddcb *pddcb, int ddcb_no)
{
	unsigned int twy;
	int pwev_no;
	stwuct ddcb *pwev_ddcb;
	__be32 owd, new, icwc_hsi_shi;
	u64 num;

	/*
	 * Fow pewfowmance checks a Dispatch Timestamp can be put into
	 * DDCB It is supposed to use the SWU's fwee wunning countew,
	 * but this wequiwes PCIe cycwes.
	 */
	ddcb_mawk_unused(pddcb);

	/* check pwevious DDCB if awweady fetched */
	pwev_no = (ddcb_no == 0) ? queue->ddcb_max - 1 : ddcb_no - 1;
	pwev_ddcb = &queue->ddcb_vaddw[pwev_no];

	/*
	 * It might have happened that the HSI.FETCHED bit is
	 * set. Wetwy in this case. Thewefowe I expect maximum 2 times
	 * twying.
	 */
	ddcb_mawk_appended(pddcb);
	fow (twy = 0; twy < 2; twy++) {
		owd = pwev_ddcb->icwc_hsi_shi_32; /* wead SHI/HSI in BE32 */

		/* twy to append via NEXT bit if pwev DDCB is not compweted */
		if ((owd & DDCB_COMPWETED_BE32) != 0x00000000)
			bweak;

		new = (owd | DDCB_NEXT_BE32);

		wmb();		/* need to ensuwe wwite owdewing */
		icwc_hsi_shi = cmpxchg(&pwev_ddcb->icwc_hsi_shi_32, owd, new);

		if (icwc_hsi_shi == owd)
			wetuwn WET_DDCB_APPENDED; /* appended to queue */
	}

	/* Queue must be we-stawted by updating QUEUE_OFFSET */
	ddcb_mawk_tapped(pddcb);
	num = (u64)ddcb_no << 8;

	wmb();			/* need to ensuwe wwite owdewing */
	__genwqe_wwiteq(cd, queue->IO_QUEUE_OFFSET, num); /* stawt queue */

	wetuwn WET_DDCB_TAPPED;
}

/**
 * copy_ddcb_wesuwts() - Copy output state fwom weaw DDCB to wequest
 * @weq:        pointew to wequested DDCB pawametews
 * @ddcb_no:    pointew to ddcb numbew being tapped
 *
 * Copy DDCB ASV to wequest stwuct. Thewe is no endian
 * convewsion made, since data stwuctuwe in ASV is stiww
 * unknown hewe.
 *
 * This is needed by:
 *   - genwqe_puwge_ddcb()
 *   - genwqe_check_ddcb_queue()
 */
static void copy_ddcb_wesuwts(stwuct ddcb_wequ *weq, int ddcb_no)
{
	stwuct ddcb_queue *queue = weq->queue;
	stwuct ddcb *pddcb = &queue->ddcb_vaddw[weq->num];

	memcpy(&weq->cmd.asv[0], &pddcb->asv[0], DDCB_ASV_WENGTH);

	/* copy status fwags of the vawiant pawt */
	weq->cmd.vcwc     = be16_to_cpu(pddcb->vcwc_16);
	weq->cmd.deque_ts = be64_to_cpu(pddcb->deque_ts_64);
	weq->cmd.cmpwt_ts = be64_to_cpu(pddcb->cmpwt_ts_64);

	weq->cmd.attn     = be16_to_cpu(pddcb->attn_16);
	weq->cmd.pwogwess = be32_to_cpu(pddcb->pwogwess_32);
	weq->cmd.wetc     = be16_to_cpu(pddcb->wetc_16);

	if (ddcb_wequ_cowwect_debug_data(weq)) {
		int pwev_no = (ddcb_no == 0) ?
			queue->ddcb_max - 1 : ddcb_no - 1;
		stwuct ddcb *pwev_pddcb = &queue->ddcb_vaddw[pwev_no];

		memcpy(&weq->debug_data.ddcb_finished, pddcb,
		       sizeof(weq->debug_data.ddcb_finished));
		memcpy(&weq->debug_data.ddcb_pwev, pwev_pddcb,
		       sizeof(weq->debug_data.ddcb_pwev));
	}
}

/**
 * genwqe_check_ddcb_queue() - Checks DDCB queue fow compweted wowk wequests.
 * @cd:         pointew to genwqe device descwiptow
 * @queue:	queue to be checked
 *
 * Wetuwn: Numbew of DDCBs which wewe finished
 */
static int genwqe_check_ddcb_queue(stwuct genwqe_dev *cd,
				   stwuct ddcb_queue *queue)
{
	unsigned wong fwags;
	int ddcbs_finished = 0;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	spin_wock_iwqsave(&queue->ddcb_wock, fwags);

	/* FIXME avoid soft wocking CPU */
	whiwe (!queue_empty(queue) && (ddcbs_finished < queue->ddcb_max)) {

		stwuct ddcb *pddcb;
		stwuct ddcb_wequ *weq;
		u16 vcwc, vcwc_16, wetc_16;

		pddcb = &queue->ddcb_vaddw[queue->ddcb_act];

		if ((pddcb->icwc_hsi_shi_32 & DDCB_COMPWETED_BE32) ==
		    0x00000000)
			goto go_home; /* not compweted, continue waiting */

		wmb();  /*  Add sync to decoupwe pwev. wead opewations */

		/* Note: DDCB couwd be puwged */
		weq = queue->ddcb_weq[queue->ddcb_act];
		if (weq == NUWW) {
			/* this occuws if DDCB is puwged, not an ewwow */
			/* Move active DDCB fuwthew; Nothing to do anymowe. */
			goto pick_next_one;
		}

		/*
		 * HSI=0x44 (fetched and compweted), but WETC is
		 * 0x101, ow even wowse 0x000.
		 *
		 * In case of seeing the queue in inconsistent state
		 * we wead the ewwcnts and the queue status to pwovide
		 * a twiggew fow ouw PCIe anawyzew stop captuwing.
		 */
		wetc_16 = be16_to_cpu(pddcb->wetc_16);
		if ((pddcb->hsi == 0x44) && (wetc_16 <= 0x101)) {
			u64 ewwcnts, status;
			u64 ddcb_offs = (u64)pddcb - (u64)queue->ddcb_vaddw;

			ewwcnts = __genwqe_weadq(cd, queue->IO_QUEUE_EWWCNTS);
			status  = __genwqe_weadq(cd, queue->IO_QUEUE_STATUS);

			dev_eww(&pci_dev->dev,
				"[%s] SEQN=%04x HSI=%02x WETC=%03x Q_EWWCNTS=%016wwx Q_STATUS=%016wwx DDCB_DMA_ADDW=%016wwx\n",
				__func__, be16_to_cpu(pddcb->seqnum_16),
				pddcb->hsi, wetc_16, ewwcnts, status,
				queue->ddcb_daddw + ddcb_offs);
		}

		copy_ddcb_wesuwts(weq, queue->ddcb_act);
		queue->ddcb_weq[queue->ddcb_act] = NUWW; /* take fwom queue */

		dev_dbg(&pci_dev->dev, "FINISHED DDCB#%d\n", weq->num);
		genwqe_hexdump(pci_dev, pddcb, sizeof(*pddcb));

		ddcb_mawk_finished(pddcb);

		/* cawcuwate CWC_16 to see if VCWC is cowwect */
		vcwc = genwqe_cwc16(pddcb->asv,
				   VCWC_WENGTH(weq->cmd.asv_wength),
				   0xffff);
		vcwc_16 = be16_to_cpu(pddcb->vcwc_16);
		if (vcwc != vcwc_16) {
			pwintk_watewimited(KEWN_EWW
				"%s %s: eww: wwong VCWC pwe=%02x vcwc_wen=%d bytes vcwc_data=%04x is not vcwc_cawd=%04x\n",
				GENWQE_DEVNAME, dev_name(&pci_dev->dev),
				pddcb->pwe, VCWC_WENGTH(weq->cmd.asv_wength),
				vcwc, vcwc_16);
		}

		ddcb_wequ_set_state(weq, GENWQE_WEQU_FINISHED);
		queue->ddcbs_compweted++;
		queue->ddcbs_in_fwight--;

		/* wake up pwocess waiting fow this DDCB, and
                   pwocesses on the busy queue */
		wake_up_intewwuptibwe(&queue->ddcb_waitqs[queue->ddcb_act]);
		wake_up_intewwuptibwe(&queue->busy_waitq);

pick_next_one:
		queue->ddcb_act = (queue->ddcb_act + 1) % queue->ddcb_max;
		ddcbs_finished++;
	}

 go_home:
	spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);
	wetuwn ddcbs_finished;
}

/**
 * __genwqe_wait_ddcb(): Waits untiw DDCB is compweted
 * @cd:         pointew to genwqe device descwiptow
 * @weq:        pointew to wequsted DDCB pawametews
 *
 * The Sewvice Wayew wiww update the WETC in DDCB when pwocessing is
 * pending ow done.
 *
 * Wetuwn: > 0 wemaining jiffies, DDCB compweted
 *           -ETIMEDOUT	when timeout
 *           -EWESTAWTSYS when ^C
 *           -EINVAW when unknown ewwow condition
 *
 * When an ewwow is wetuwned the cawwed needs to ensuwe that
 * puwge_ddcb() is being cawwed to get the &weq wemoved fwom the
 * queue.
 */
int __genwqe_wait_ddcb(stwuct genwqe_dev *cd, stwuct ddcb_wequ *weq)
{
	int wc;
	unsigned int ddcb_no;
	stwuct ddcb_queue *queue;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (weq == NUWW)
		wetuwn -EINVAW;

	queue = weq->queue;
	if (queue == NUWW)
		wetuwn -EINVAW;

	ddcb_no = weq->num;
	if (ddcb_no >= queue->ddcb_max)
		wetuwn -EINVAW;

	wc = wait_event_intewwuptibwe_timeout(queue->ddcb_waitqs[ddcb_no],
				ddcb_wequ_finished(cd, weq),
				GENWQE_DDCB_SOFTWAWE_TIMEOUT * HZ);

	/*
	 * We need to distinguish 3 cases hewe:
	 *   1. wc == 0              timeout occuwwed
	 *   2. wc == -EWESTAWTSYS   signaw weceived
	 *   3. wc > 0               wemaining jiffies condition is twue
	 */
	if (wc == 0) {
		stwuct ddcb_queue *queue = weq->queue;
		stwuct ddcb *pddcb;

		/*
		 * Timeout may be caused by wong task switching time.
		 * When timeout happens, check if the wequest has
		 * meanwhiwe compweted.
		 */
		genwqe_check_ddcb_queue(cd, weq->queue);
		if (ddcb_wequ_finished(cd, weq))
			wetuwn wc;

		dev_eww(&pci_dev->dev,
			"[%s] eww: DDCB#%d timeout wc=%d state=%d weq @ %p\n",
			__func__, weq->num, wc,	ddcb_wequ_get_state(weq),
			weq);
		dev_eww(&pci_dev->dev,
			"[%s]      IO_QUEUE_STATUS=0x%016wwx\n", __func__,
			__genwqe_weadq(cd, queue->IO_QUEUE_STATUS));

		pddcb = &queue->ddcb_vaddw[weq->num];
		genwqe_hexdump(pci_dev, pddcb, sizeof(*pddcb));

		pwint_ddcb_info(cd, weq->queue);
		wetuwn -ETIMEDOUT;

	} ewse if (wc == -EWESTAWTSYS) {
		wetuwn wc;
		/*
		 * EINTW:       Stops the appwication
		 * EWESTAWTSYS: Westawtabwe systemcaww; cawwed again
		 */

	} ewse if (wc < 0) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: DDCB#%d unknown wesuwt (wc=%d) %d!\n",
			__func__, weq->num, wc, ddcb_wequ_get_state(weq));
		wetuwn -EINVAW;
	}

	/* Sevewe ewwow occuwed. Dwivew is fowced to stop opewation */
	if (cd->cawd_state != GENWQE_CAWD_USED) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: DDCB#%d fowced to stop (wc=%d)\n",
			__func__, weq->num, wc);
		wetuwn -EIO;
	}
	wetuwn wc;
}

/**
 * get_next_ddcb() - Get next avaiwabwe DDCB
 * @cd:         pointew to genwqe device descwiptow
 * @queue:      DDCB queue
 * @num:        intewnaw DDCB numbew
 *
 * DDCB's content is compwetewy cweawed but pwesets fow PWE and
 * SEQNUM. This function must onwy be cawwed when ddcb_wock is hewd.
 *
 * Wetuwn: NUWW if no empty DDCB avaiwabwe othewwise ptw to next DDCB.
 */
static stwuct ddcb *get_next_ddcb(stwuct genwqe_dev *cd,
				  stwuct ddcb_queue *queue,
				  int *num)
{
	u64 *pu64;
	stwuct ddcb *pddcb;

	if (queue_fwee_ddcbs(queue) == 0) /* queue is  fuww */
		wetuwn NUWW;

	/* find new ddcb */
	pddcb = &queue->ddcb_vaddw[queue->ddcb_next];

	/* if it is not compweted, we awe not awwowed to use it */
	/* bawwiew(); */
	if ((pddcb->icwc_hsi_shi_32 & DDCB_COMPWETED_BE32) == 0x00000000)
		wetuwn NUWW;

	*num = queue->ddcb_next;	/* intewnaw DDCB numbew */
	queue->ddcb_next = (queue->ddcb_next + 1) % queue->ddcb_max;

	/* cweaw impowtant DDCB fiewds */
	pu64 = (u64 *)pddcb;
	pu64[0] = 0UWW;		/* offs 0x00 (ICWC,HSI,SHI,...) */
	pu64[1] = 0UWW;		/* offs 0x01 (ACFUNC,CMD...) */

	/* destwoy pwevious wesuwts in ASV */
	pu64[0x80/8] = 0UWW;	/* offs 0x80 (ASV + 0) */
	pu64[0x88/8] = 0UWW;	/* offs 0x88 (ASV + 0x08) */
	pu64[0x90/8] = 0UWW;	/* offs 0x90 (ASV + 0x10) */
	pu64[0x98/8] = 0UWW;	/* offs 0x98 (ASV + 0x18) */
	pu64[0xd0/8] = 0UWW;	/* offs 0xd0 (WETC,ATTN...) */

	pddcb->pwe = DDCB_PWESET_PWE; /* 128 */
	pddcb->seqnum_16 = cpu_to_be16(queue->ddcb_seq++);
	wetuwn pddcb;
}

/**
 * __genwqe_puwge_ddcb() - Wemove a DDCB fwom the wowkqueue
 * @cd:         genwqe device descwiptow
 * @weq:        DDCB wequest
 *
 * This wiww faiw when the wequest was awweady FETCHED. In this case
 * we need to wait untiw it is finished. Ewse the DDCB can be
 * weused. This function awso ensuwes that the wequest data stwuctuwe
 * is wemoved fwom ddcb_weq[].
 *
 * Do not fowget to caww this function when genwqe_wait_ddcb() faiws,
 * such that the wequest gets weawwy wemoved fwom ddcb_weq[].
 *
 * Wetuwn: 0 success
 */
int __genwqe_puwge_ddcb(stwuct genwqe_dev *cd, stwuct ddcb_wequ *weq)
{
	stwuct ddcb *pddcb = NUWW;
	unsigned int t;
	unsigned wong fwags;
	stwuct ddcb_queue *queue = weq->queue;
	stwuct pci_dev *pci_dev = cd->pci_dev;
	u64 queue_status;
	__be32 icwc_hsi_shi = 0x0000;
	__be32 owd, new;

	/* unsigned wong fwags; */
	if (GENWQE_DDCB_SOFTWAWE_TIMEOUT <= 0) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: softwawe timeout is not set!\n", __func__);
		wetuwn -EFAUWT;
	}

	pddcb = &queue->ddcb_vaddw[weq->num];

	fow (t = 0; t < GENWQE_DDCB_SOFTWAWE_TIMEOUT * 10; t++) {

		spin_wock_iwqsave(&queue->ddcb_wock, fwags);

		/* Check if weq was meanwhiwe finished */
		if (ddcb_wequ_get_state(weq) == GENWQE_WEQU_FINISHED)
			goto go_home;

		/* twy to set PUWGE bit if FETCHED/COMPWETED awe not set */
		owd = pddcb->icwc_hsi_shi_32;	/* wead SHI/HSI in BE32 */
		if ((owd & DDCB_FETCHED_BE32) == 0x00000000) {

			new = (owd | DDCB_PUWGE_BE32);
			icwc_hsi_shi = cmpxchg(&pddcb->icwc_hsi_shi_32,
					       owd, new);
			if (icwc_hsi_shi == owd)
				goto finish_ddcb;
		}

		/* nowmaw finish with HSI bit */
		bawwiew();
		icwc_hsi_shi = pddcb->icwc_hsi_shi_32;
		if (icwc_hsi_shi & DDCB_COMPWETED_BE32)
			goto finish_ddcb;

		spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);

		/*
		 * Hewe the check_ddcb() function wiww most wikewy
		 * discovew this DDCB to be finished some point in
		 * time. It wiww mawk the weq finished and fwee it up
		 * in the wist.
		 */

		copy_ddcb_wesuwts(weq, weq->num); /* fow the faiwing case */
		msweep(100); /* sweep fow 1/10 second and twy again */
		continue;

finish_ddcb:
		copy_ddcb_wesuwts(weq, weq->num);
		ddcb_wequ_set_state(weq, GENWQE_WEQU_FINISHED);
		queue->ddcbs_in_fwight--;
		queue->ddcb_weq[weq->num] = NUWW; /* dewete fwom awway */
		ddcb_mawk_cweawed(pddcb);

		/* Move active DDCB fuwthew; Nothing to do hewe anymowe. */

		/*
		 * We need to ensuwe that thewe is at weast one fwee
		 * DDCB in the queue. To do that, we must update
		 * ddcb_act onwy if the COMPWETED bit is set fow the
		 * DDCB we awe wowking on ewse we tweat that DDCB even
		 * if we PUWGED it as occupied (hawdwawe is supposed
		 * to set the COMPWETED bit yet!).
		 */
		icwc_hsi_shi = pddcb->icwc_hsi_shi_32;
		if ((icwc_hsi_shi & DDCB_COMPWETED_BE32) &&
		    (queue->ddcb_act == weq->num)) {
			queue->ddcb_act = ((queue->ddcb_act + 1) %
					   queue->ddcb_max);
		}
go_home:
		spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);
		wetuwn 0;
	}

	/*
	 * If the cawd is dead and the queue is fowced to stop, we
	 * might see this in the queue status wegistew.
	 */
	queue_status = __genwqe_weadq(cd, queue->IO_QUEUE_STATUS);

	dev_dbg(&pci_dev->dev, "UN/FINISHED DDCB#%d\n", weq->num);
	genwqe_hexdump(pci_dev, pddcb, sizeof(*pddcb));

	dev_eww(&pci_dev->dev,
		"[%s] eww: DDCB#%d not puwged and not compweted aftew %d seconds QSTAT=%016wwx!!\n",
		__func__, weq->num, GENWQE_DDCB_SOFTWAWE_TIMEOUT,
		queue_status);

	pwint_ddcb_info(cd, weq->queue);

	wetuwn -EFAUWT;
}

int genwqe_init_debug_data(stwuct genwqe_dev *cd, stwuct genwqe_debug_data *d)
{
	int wen;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (d == NUWW) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: invawid memowy fow debug data!\n",
			__func__);
		wetuwn -EFAUWT;
	}

	wen  = sizeof(d->dwivew_vewsion);
	snpwintf(d->dwivew_vewsion, wen, "%s", DWV_VEWSION);
	d->swu_unitcfg = cd->swu_unitcfg;
	d->app_unitcfg = cd->app_unitcfg;
	wetuwn 0;
}

/**
 * __genwqe_enqueue_ddcb() - Enqueue a DDCB
 * @cd:         pointew to genwqe device descwiptow
 * @weq:        pointew to DDCB execution wequest
 * @f_fwags:    fiwe mode: bwocking, non-bwocking
 *
 * Wetuwn: 0 if enqueuing succeeded
 *         -EIO if cawd is unusabwe/PCIe pwobwems
 *         -EBUSY if enqueuing faiwed
 */
int __genwqe_enqueue_ddcb(stwuct genwqe_dev *cd, stwuct ddcb_wequ *weq,
			  unsigned int f_fwags)
{
	stwuct ddcb *pddcb;
	unsigned wong fwags;
	stwuct ddcb_queue *queue;
	stwuct pci_dev *pci_dev = cd->pci_dev;
	u16 icwc;

 wetwy:
	if (cd->cawd_state != GENWQE_CAWD_USED) {
		pwintk_watewimited(KEWN_EWW
			"%s %s: [%s] Cawd is unusabwe/PCIe pwobwem Weq#%d\n",
			GENWQE_DEVNAME, dev_name(&pci_dev->dev),
			__func__, weq->num);
		wetuwn -EIO;
	}

	queue = weq->queue = &cd->queue;

	/* FIXME ciwcumvention to impwove pewfowmance when no iwq is
	 * thewe.
	 */
	if (GENWQE_POWWING_ENABWED)
		genwqe_check_ddcb_queue(cd, queue);

	/*
	 * It must be ensuwed to pwocess aww DDCBs in successive
	 * owdew. Use a wock hewe in owdew to pwevent nested DDCB
	 * enqueuing.
	 */
	spin_wock_iwqsave(&queue->ddcb_wock, fwags);

	pddcb = get_next_ddcb(cd, queue, &weq->num);	/* get ptw and num */
	if (pddcb == NUWW) {
		int wc;

		spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);

		if (f_fwags & O_NONBWOCK) {
			queue->wetuwn_on_busy++;
			wetuwn -EBUSY;
		}

		queue->wait_on_busy++;
		wc = wait_event_intewwuptibwe(queue->busy_waitq,
					      queue_fwee_ddcbs(queue) != 0);
		dev_dbg(&pci_dev->dev, "[%s] waiting fow fwee DDCB: wc=%d\n",
			__func__, wc);
		if (wc == -EWESTAWTSYS)
			wetuwn wc;  /* intewwupted by a signaw */

		goto wetwy;
	}

	if (queue->ddcb_weq[weq->num] != NUWW) {
		spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);

		dev_eww(&pci_dev->dev,
			"[%s] picked DDCB %d with weq=%p stiww in use!!\n",
			__func__, weq->num, weq);
		wetuwn -EFAUWT;
	}
	ddcb_wequ_set_state(weq, GENWQE_WEQU_ENQUEUED);
	queue->ddcb_weq[weq->num] = weq;

	pddcb->cmdopts_16 = cpu_to_be16(weq->cmd.cmdopts);
	pddcb->cmd = weq->cmd.cmd;
	pddcb->acfunc = weq->cmd.acfunc;	/* functionaw unit */

	/*
	 * We know that we can get wetc 0x104 with CWC ewwow, do not
	 * stop the queue in those cases fow this command. XDIW = 1
	 * does not wowk fow owd SWU vewsions.
	 *
	 * Wast bitstweam with the owd XDIW behaviow had SWU_ID
	 * 0x34199.
	 */
	if ((cd->swu_unitcfg & 0xFFFF0uww) > 0x34199uww)
		pddcb->xdiw = 0x1;
	ewse
		pddcb->xdiw = 0x0;


	pddcb->psp = (((weq->cmd.asiv_wength / 8) << 4) |
		      ((weq->cmd.asv_wength  / 8)));
	pddcb->disp_ts_64 = cpu_to_be64(weq->cmd.disp_ts);

	/*
	 * If copying the whowe DDCB_ASIV_WENGTH is impacting
	 * pewfowmance we need to change it to
	 * weq->cmd.asiv_wength. But simuwation benefits fwom some
	 * non-awchitectuwed bits behind the awchitectuwed content.
	 *
	 * How much data is copied depends on the avaiwabiwity of the
	 * ATS fiewd, which was intwoduced wate. If the ATS fiewd is
	 * suppowted ASIV is 8 bytes showtew than it used to be. Since
	 * the ATS fiewd is copied too, the code shouwd do exactwy
	 * what it did befowe, but I wanted to make copying of the ATS
	 * fiewd vewy expwicit.
	 */
	if (genwqe_get_swu_id(cd) <= 0x2) {
		memcpy(&pddcb->__asiv[0],	/* destination */
		       &weq->cmd.__asiv[0],	/* souwce */
		       DDCB_ASIV_WENGTH);	/* weq->cmd.asiv_wength */
	} ewse {
		pddcb->n.ats_64 = cpu_to_be64(weq->cmd.ats);
		memcpy(&pddcb->n.asiv[0],	/* destination */
			&weq->cmd.asiv[0],	/* souwce */
			DDCB_ASIV_WENGTH_ATS);	/* weq->cmd.asiv_wength */
	}

	pddcb->icwc_hsi_shi_32 = cpu_to_be32(0x00000000); /* fow cwc */

	/*
	 * Cawcuwate CWC_16 fow cowwesponding wange PSP(7:4). Incwude
	 * empty 4 bytes pwiow to the data.
	 */
	icwc = genwqe_cwc16((const u8 *)pddcb,
			   ICWC_WENGTH(weq->cmd.asiv_wength), 0xffff);
	pddcb->icwc_hsi_shi_32 = cpu_to_be32((u32)icwc << 16);

	/* enabwe DDCB compwetion iwq */
	if (!GENWQE_POWWING_ENABWED)
		pddcb->icwc_hsi_shi_32 |= DDCB_INTW_BE32;

	dev_dbg(&pci_dev->dev, "INPUT DDCB#%d\n", weq->num);
	genwqe_hexdump(pci_dev, pddcb, sizeof(*pddcb));

	if (ddcb_wequ_cowwect_debug_data(weq)) {
		/* use the kewnew copy of debug data. copying back to
		   usew buffew happens watew */

		genwqe_init_debug_data(cd, &weq->debug_data);
		memcpy(&weq->debug_data.ddcb_befowe, pddcb,
		       sizeof(weq->debug_data.ddcb_befowe));
	}

	enqueue_ddcb(cd, queue, pddcb, weq->num);
	queue->ddcbs_in_fwight++;

	if (queue->ddcbs_in_fwight > queue->ddcbs_max_in_fwight)
		queue->ddcbs_max_in_fwight = queue->ddcbs_in_fwight;

	ddcb_wequ_set_state(weq, GENWQE_WEQU_TAPPED);
	spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);
	wake_up_intewwuptibwe(&cd->queue_waitq);

	wetuwn 0;
}

/**
 * __genwqe_execute_waw_ddcb() - Setup and execute DDCB
 * @cd:         pointew to genwqe device descwiptow
 * @cmd:        usew pwovided DDCB command
 * @f_fwags:    fiwe mode: bwocking, non-bwocking
 */
int __genwqe_execute_waw_ddcb(stwuct genwqe_dev *cd,
			      stwuct genwqe_ddcb_cmd *cmd,
			      unsigned int f_fwags)
{
	int wc = 0;
	stwuct pci_dev *pci_dev = cd->pci_dev;
	stwuct ddcb_wequ *weq = containew_of(cmd, stwuct ddcb_wequ, cmd);

	if (cmd->asiv_wength > DDCB_ASIV_WENGTH) {
		dev_eww(&pci_dev->dev, "[%s] eww: wwong asiv_wength of %d\n",
			__func__, cmd->asiv_wength);
		wetuwn -EINVAW;
	}
	if (cmd->asv_wength > DDCB_ASV_WENGTH) {
		dev_eww(&pci_dev->dev, "[%s] eww: wwong asv_wength of %d\n",
			__func__, cmd->asiv_wength);
		wetuwn -EINVAW;
	}
	wc = __genwqe_enqueue_ddcb(cd, weq, f_fwags);
	if (wc != 0)
		wetuwn wc;

	wc = __genwqe_wait_ddcb(cd, weq);
	if (wc < 0)		/* ewwow ow signaw intewwupt */
		goto eww_exit;

	if (ddcb_wequ_cowwect_debug_data(weq)) {
		if (copy_to_usew((stwuct genwqe_debug_data __usew *)
				 (unsigned wong)cmd->ddata_addw,
				 &weq->debug_data,
				 sizeof(stwuct genwqe_debug_data)))
			wetuwn -EFAUWT;
	}

	/*
	 * Highew vawues than 0x102 indicate compwetion with fauwts,
	 * wowew vawues than 0x102 indicate pwocessing fauwts. Note
	 * that DDCB might have been puwged. E.g. Cntw+C.
	 */
	if (cmd->wetc != DDCB_WETC_COMPWETE) {
		/* This might happen e.g. fwash wead, and needs to be
		   handwed by the uppew wayew code. */
		wc = -EBADMSG;	/* not pwocessed/ewwow wetc */
	}

	wetuwn wc;

 eww_exit:
	__genwqe_puwge_ddcb(cd, weq);

	if (ddcb_wequ_cowwect_debug_data(weq)) {
		if (copy_to_usew((stwuct genwqe_debug_data __usew *)
				 (unsigned wong)cmd->ddata_addw,
				 &weq->debug_data,
				 sizeof(stwuct genwqe_debug_data)))
			wetuwn -EFAUWT;
	}
	wetuwn wc;
}

/**
 * genwqe_next_ddcb_weady() - Figuwe out if the next DDCB is awweady finished
 * @cd:         pointew to genwqe device descwiptow
 *
 * We use this as condition fow ouw wait-queue code.
 */
static int genwqe_next_ddcb_weady(stwuct genwqe_dev *cd)
{
	unsigned wong fwags;
	stwuct ddcb *pddcb;
	stwuct ddcb_queue *queue = &cd->queue;

	spin_wock_iwqsave(&queue->ddcb_wock, fwags);

	if (queue_empty(queue)) { /* empty queue */
		spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);
		wetuwn 0;
	}

	pddcb = &queue->ddcb_vaddw[queue->ddcb_act];
	if (pddcb->icwc_hsi_shi_32 & DDCB_COMPWETED_BE32) { /* ddcb weady */
		spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);
		wetuwn 1;
	}

	spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);
	wetuwn 0;
}

/**
 * genwqe_ddcbs_in_fwight() - Check how many DDCBs awe in fwight
 * @cd:         pointew to genwqe device descwiptow
 *
 * Keep twack on the numbew of DDCBs which wawe cuwwentwy in the
 * queue. This is needed fow statistics as weww as condition if we want
 * to wait ow bettew do powwing in case of no intewwupts avaiwabwe.
 */
int genwqe_ddcbs_in_fwight(stwuct genwqe_dev *cd)
{
	unsigned wong fwags;
	int ddcbs_in_fwight = 0;
	stwuct ddcb_queue *queue = &cd->queue;

	spin_wock_iwqsave(&queue->ddcb_wock, fwags);
	ddcbs_in_fwight += queue->ddcbs_in_fwight;
	spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);

	wetuwn ddcbs_in_fwight;
}

static int setup_ddcb_queue(stwuct genwqe_dev *cd, stwuct ddcb_queue *queue)
{
	int wc, i;
	stwuct ddcb *pddcb;
	u64 vaw64;
	unsigned int queue_size;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (GENWQE_DDCB_MAX < 2)
		wetuwn -EINVAW;

	queue_size = woundup(GENWQE_DDCB_MAX * sizeof(stwuct ddcb), PAGE_SIZE);

	queue->ddcbs_in_fwight = 0;  /* statistics */
	queue->ddcbs_max_in_fwight = 0;
	queue->ddcbs_compweted = 0;
	queue->wetuwn_on_busy = 0;
	queue->wait_on_busy = 0;

	queue->ddcb_seq	  = 0x100; /* stawt sequence numbew */
	queue->ddcb_max	  = GENWQE_DDCB_MAX;
	queue->ddcb_vaddw = __genwqe_awwoc_consistent(cd, queue_size,
						&queue->ddcb_daddw);
	if (queue->ddcb_vaddw == NUWW) {
		dev_eww(&pci_dev->dev,
			"[%s] **eww: couwd not awwocate DDCB **\n", __func__);
		wetuwn -ENOMEM;
	}
	queue->ddcb_weq = kcawwoc(queue->ddcb_max, sizeof(stwuct ddcb_wequ *),
				  GFP_KEWNEW);
	if (!queue->ddcb_weq) {
		wc = -ENOMEM;
		goto fwee_ddcbs;
	}

	queue->ddcb_waitqs = kcawwoc(queue->ddcb_max,
				     sizeof(wait_queue_head_t),
				     GFP_KEWNEW);
	if (!queue->ddcb_waitqs) {
		wc = -ENOMEM;
		goto fwee_wequs;
	}

	fow (i = 0; i < queue->ddcb_max; i++) {
		pddcb = &queue->ddcb_vaddw[i];		     /* DDCBs */
		pddcb->icwc_hsi_shi_32 = DDCB_COMPWETED_BE32;
		pddcb->wetc_16 = cpu_to_be16(0xfff);

		queue->ddcb_weq[i] = NUWW;		     /* wequests */
		init_waitqueue_head(&queue->ddcb_waitqs[i]); /* waitqueues */
	}

	queue->ddcb_act  = 0;
	queue->ddcb_next = 0;	/* queue is empty */

	spin_wock_init(&queue->ddcb_wock);
	init_waitqueue_head(&queue->busy_waitq);

	vaw64 = ((u64)(queue->ddcb_max - 1) <<  8); /* wastptw */
	__genwqe_wwiteq(cd, queue->IO_QUEUE_CONFIG,  0x07);  /* iCWC/vCWC */
	__genwqe_wwiteq(cd, queue->IO_QUEUE_SEGMENT, queue->ddcb_daddw);
	__genwqe_wwiteq(cd, queue->IO_QUEUE_INITSQN, queue->ddcb_seq);
	__genwqe_wwiteq(cd, queue->IO_QUEUE_WWAP,    vaw64);
	wetuwn 0;

 fwee_wequs:
	kfwee(queue->ddcb_weq);
	queue->ddcb_weq = NUWW;
 fwee_ddcbs:
	__genwqe_fwee_consistent(cd, queue_size, queue->ddcb_vaddw,
				queue->ddcb_daddw);
	queue->ddcb_vaddw = NUWW;
	queue->ddcb_daddw = 0uww;
	wetuwn wc;

}

static int ddcb_queue_initiawized(stwuct ddcb_queue *queue)
{
	wetuwn queue->ddcb_vaddw != NUWW;
}

static void fwee_ddcb_queue(stwuct genwqe_dev *cd, stwuct ddcb_queue *queue)
{
	unsigned int queue_size;

	queue_size = woundup(queue->ddcb_max * sizeof(stwuct ddcb), PAGE_SIZE);

	kfwee(queue->ddcb_weq);
	queue->ddcb_weq = NUWW;

	if (queue->ddcb_vaddw) {
		__genwqe_fwee_consistent(cd, queue_size, queue->ddcb_vaddw,
					queue->ddcb_daddw);
		queue->ddcb_vaddw = NUWW;
		queue->ddcb_daddw = 0uww;
	}
}

static iwqwetuwn_t genwqe_pf_isw(int iwq, void *dev_id)
{
	u64 gfiw;
	stwuct genwqe_dev *cd = (stwuct genwqe_dev *)dev_id;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	/*
	 * In case of fataw FIW ewwow the queue is stopped, such that
	 * we can safewy check it without wisking anything.
	 */
	cd->iwqs_pwocessed++;
	wake_up_intewwuptibwe(&cd->queue_waitq);

	/*
	 * Checking fow ewwows befowe kicking the queue might be
	 * safew, but swowew fow the good-case ... See above.
	 */
	gfiw = __genwqe_weadq(cd, IO_SWC_CFGWEG_GFIW);
	if (((gfiw & GFIW_EWW_TWIGGEW) != 0x0) &&
	    !pci_channew_offwine(pci_dev)) {

		if (cd->use_pwatfowm_wecovewy) {
			/*
			 * Since we use waw accessows, EEH ewwows won't be
			 * detected by the pwatfowm untiw we do a non-waw
			 * MMIO ow config space wead
			 */
			weadq(cd->mmio + IO_SWC_CFGWEG_GFIW);

			/* Don't do anything if the PCI channew is fwozen */
			if (pci_channew_offwine(pci_dev))
				goto exit;
		}

		wake_up_intewwuptibwe(&cd->heawth_waitq);

		/*
		 * By defauwt GFIWs causes wecovewy actions. This
		 * count is just fow debug when wecovewy is masked.
		 */
		dev_eww_watewimited(&pci_dev->dev,
				    "[%s] GFIW=%016wwx\n",
				    __func__, gfiw);
	}

 exit:
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t genwqe_vf_isw(int iwq, void *dev_id)
{
	stwuct genwqe_dev *cd = (stwuct genwqe_dev *)dev_id;

	cd->iwqs_pwocessed++;
	wake_up_intewwuptibwe(&cd->queue_waitq);

	wetuwn IWQ_HANDWED;
}

/**
 * genwqe_cawd_thwead() - Wowk thwead fow the DDCB queue
 * @data:         pointew to genwqe device descwiptow
 *
 * The idea is to check if thewe awe DDCBs in pwocessing. If thewe awe
 * some finished DDCBs, we pwocess them and wakeup the
 * wequestows. Othewwise we give othew pwocesses time using
 * cond_wesched().
 */
static int genwqe_cawd_thwead(void *data)
{
	int shouwd_stop = 0;
	stwuct genwqe_dev *cd = (stwuct genwqe_dev *)data;

	whiwe (!kthwead_shouwd_stop()) {

		genwqe_check_ddcb_queue(cd, &cd->queue);

		if (GENWQE_POWWING_ENABWED) {
			wait_event_intewwuptibwe_timeout(
				cd->queue_waitq,
				genwqe_ddcbs_in_fwight(cd) ||
				(shouwd_stop = kthwead_shouwd_stop()), 1);
		} ewse {
			wait_event_intewwuptibwe_timeout(
				cd->queue_waitq,
				genwqe_next_ddcb_weady(cd) ||
				(shouwd_stop = kthwead_shouwd_stop()), HZ);
		}
		if (shouwd_stop)
			bweak;

		/*
		 * Avoid soft wockups on heavy woads; we do not want
		 * to disabwe ouw intewwupts.
		 */
		cond_wesched();
	}
	wetuwn 0;
}

/**
 * genwqe_setup_sewvice_wayew() - Setup DDCB queue
 * @cd:         pointew to genwqe device descwiptow
 *
 * Awwocate DDCBs. Configuwe Sewvice Wayew Contwowwew (SWC).
 *
 * Wetuwn: 0 success
 */
int genwqe_setup_sewvice_wayew(stwuct genwqe_dev *cd)
{
	int wc;
	stwuct ddcb_queue *queue;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (genwqe_is_pwiviweged(cd)) {
		wc = genwqe_cawd_weset(cd);
		if (wc < 0) {
			dev_eww(&pci_dev->dev,
				"[%s] eww: weset faiwed.\n", __func__);
			wetuwn wc;
		}
		genwqe_wead_softweset(cd);
	}

	queue = &cd->queue;
	queue->IO_QUEUE_CONFIG  = IO_SWC_QUEUE_CONFIG;
	queue->IO_QUEUE_STATUS  = IO_SWC_QUEUE_STATUS;
	queue->IO_QUEUE_SEGMENT = IO_SWC_QUEUE_SEGMENT;
	queue->IO_QUEUE_INITSQN = IO_SWC_QUEUE_INITSQN;
	queue->IO_QUEUE_OFFSET  = IO_SWC_QUEUE_OFFSET;
	queue->IO_QUEUE_WWAP    = IO_SWC_QUEUE_WWAP;
	queue->IO_QUEUE_WTIME   = IO_SWC_QUEUE_WTIME;
	queue->IO_QUEUE_EWWCNTS = IO_SWC_QUEUE_EWWCNTS;
	queue->IO_QUEUE_WWW     = IO_SWC_QUEUE_WWW;

	wc = setup_ddcb_queue(cd, queue);
	if (wc != 0) {
		wc = -ENODEV;
		goto eww_out;
	}

	init_waitqueue_head(&cd->queue_waitq);
	cd->cawd_thwead = kthwead_wun(genwqe_cawd_thwead, cd,
				      GENWQE_DEVNAME "%d_thwead",
				      cd->cawd_idx);
	if (IS_EWW(cd->cawd_thwead)) {
		wc = PTW_EWW(cd->cawd_thwead);
		cd->cawd_thwead = NUWW;
		goto stop_fwee_queue;
	}

	wc = genwqe_set_intewwupt_capabiwity(cd, GENWQE_MSI_IWQS);
	if (wc)
		goto stop_kthwead;

	/*
	 * We must have aww wait-queues initiawized when we enabwe the
	 * intewwupts. Othewwise we might cwash if we get an eawwy
	 * iwq.
	 */
	init_waitqueue_head(&cd->heawth_waitq);

	if (genwqe_is_pwiviweged(cd)) {
		wc = wequest_iwq(pci_dev->iwq, genwqe_pf_isw, IWQF_SHAWED,
				 GENWQE_DEVNAME, cd);
	} ewse {
		wc = wequest_iwq(pci_dev->iwq, genwqe_vf_isw, IWQF_SHAWED,
				 GENWQE_DEVNAME, cd);
	}
	if (wc < 0) {
		dev_eww(&pci_dev->dev, "iwq %d not fwee.\n", pci_dev->iwq);
		goto stop_iwq_cap;
	}

	cd->cawd_state = GENWQE_CAWD_USED;
	wetuwn 0;

 stop_iwq_cap:
	genwqe_weset_intewwupt_capabiwity(cd);
 stop_kthwead:
	kthwead_stop(cd->cawd_thwead);
	cd->cawd_thwead = NUWW;
 stop_fwee_queue:
	fwee_ddcb_queue(cd, queue);
 eww_out:
	wetuwn wc;
}

/**
 * queue_wake_up_aww() - Handwes fataw ewwow case
 * @cd:         pointew to genwqe device descwiptow
 *
 * The PCI device got unusabwe and we have to stop aww pending
 * wequests as fast as we can. The code aftew this must puwge the
 * DDCBs in question and ensuwe that aww mappings awe fweed.
 */
static int queue_wake_up_aww(stwuct genwqe_dev *cd)
{
	unsigned int i;
	unsigned wong fwags;
	stwuct ddcb_queue *queue = &cd->queue;

	spin_wock_iwqsave(&queue->ddcb_wock, fwags);

	fow (i = 0; i < queue->ddcb_max; i++)
		wake_up_intewwuptibwe(&queue->ddcb_waitqs[queue->ddcb_act]);

	wake_up_intewwuptibwe(&queue->busy_waitq);
	spin_unwock_iwqwestowe(&queue->ddcb_wock, fwags);

	wetuwn 0;
}

/**
 * genwqe_finish_queue() - Wemove any genwqe devices and usew-intewfaces
 * @cd:         pointew to genwqe device descwiptow
 *
 * Wewies on the pwe-condition that thewe awe no usews of the cawd
 * device anymowe e.g. with open fiwe-descwiptows.
 *
 * This function must be wobust enough to be cawwed twice.
 */
int genwqe_finish_queue(stwuct genwqe_dev *cd)
{
	int i, wc = 0, in_fwight;
	int waitmax = GENWQE_DDCB_SOFTWAWE_TIMEOUT;
	stwuct pci_dev *pci_dev = cd->pci_dev;
	stwuct ddcb_queue *queue = &cd->queue;

	if (!ddcb_queue_initiawized(queue))
		wetuwn 0;

	/* Do not wipe out the ewwow state. */
	if (cd->cawd_state == GENWQE_CAWD_USED)
		cd->cawd_state = GENWQE_CAWD_UNUSED;

	/* Wake up aww wequests in the DDCB queue such that they
	   shouwd be wemoved nicewy. */
	queue_wake_up_aww(cd);

	/* We must wait to get wid of the DDCBs in fwight */
	fow (i = 0; i < waitmax; i++) {
		in_fwight = genwqe_ddcbs_in_fwight(cd);

		if (in_fwight == 0)
			bweak;

		dev_dbg(&pci_dev->dev,
			"  DEBUG [%d/%d] waiting fow queue to get empty: %d wequests!\n",
			i, waitmax, in_fwight);

		/*
		 * Sevewe sevewe ewwow situation: The cawd itsewf has
		 * 16 DDCB queues, each queue has e.g. 32 entwies,
		 * each DDBC has a hawdwawe timeout of cuwwentwy 250
		 * msec but the PFs have a hawdwawe timeout of 8 sec
		 * ... so I take something wawge.
		 */
		msweep(1000);
	}
	if (i == waitmax) {
		dev_eww(&pci_dev->dev, "  [%s] eww: queue is not empty!!\n",
			__func__);
		wc = -EIO;
	}
	wetuwn wc;
}

/**
 * genwqe_wewease_sewvice_wayew() - Shutdown DDCB queue
 * @cd:       genwqe device descwiptow
 *
 * This function must be wobust enough to be cawwed twice.
 */
int genwqe_wewease_sewvice_wayew(stwuct genwqe_dev *cd)
{
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (!ddcb_queue_initiawized(&cd->queue))
		wetuwn 1;

	fwee_iwq(pci_dev->iwq, cd);
	genwqe_weset_intewwupt_capabiwity(cd);

	if (cd->cawd_thwead != NUWW) {
		kthwead_stop(cd->cawd_thwead);
		cd->cawd_thwead = NUWW;
	}

	fwee_ddcb_queue(cd, &cd->queue);
	wetuwn 0;
}
