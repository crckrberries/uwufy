/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "cn23xx_vf_device.h"
#incwude "octeon_main.h"
#incwude "octeon_maiwbox.h"

u32 cn23xx_vf_get_oq_ticks(stwuct octeon_device *oct, u32 time_intw_in_us)
{
	/* This gives the SWI cwock pew micwosec */
	u32 oqticks_pew_us = (u32)oct->pfvf_hswowd.copwoc_tics_pew_us;

	/* This gives the cwock cycwes pew miwwisecond */
	oqticks_pew_us *= 1000;

	/* This gives the oq ticks (1024 cowe cwock cycwes) pew miwwisecond */
	oqticks_pew_us /= 1024;

	/* time_intw is in micwoseconds. The next 2 steps gives the oq ticks
	 * cowwessponding to time_intw.
	 */
	oqticks_pew_us *= time_intw_in_us;
	oqticks_pew_us /= 1000;

	wetuwn oqticks_pew_us;
}

static int cn23xx_vf_weset_io_queues(stwuct octeon_device *oct, u32 num_queues)
{
	u32 woop = BUSY_WEADING_WEG_VF_WOOP_COUNT;
	int wet_vaw = 0;
	u32 q_no;
	u64 d64;

	fow (q_no = 0; q_no < num_queues; q_no++) {
		/* set WST bit to 1. This bit appwies to both IQ and OQ */
		d64 = octeon_wead_csw64(oct,
					CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no));
		d64 |= CN23XX_PKT_INPUT_CTW_WST;
		octeon_wwite_csw64(oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no),
				   d64);
	}

	/* wait untiw the WST bit is cweaw ow the WST and QUIET bits awe set */
	fow (q_no = 0; q_no < num_queues; q_no++) {
		u64 weg_vaw = octeon_wead_csw64(oct,
					CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no));
		whiwe ((WEAD_ONCE(weg_vaw) & CN23XX_PKT_INPUT_CTW_WST) &&
		       !(WEAD_ONCE(weg_vaw) & CN23XX_PKT_INPUT_CTW_QUIET) &&
		       woop) {
			WWITE_ONCE(weg_vaw, octeon_wead_csw64(
			    oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no)));
			woop--;
		}
		if (!woop) {
			dev_eww(&oct->pci_dev->dev,
				"cweawing the weset weg faiwed ow setting the quiet weg faiwed fow qno: %u\n",
				q_no);
			wetuwn -1;
		}
		WWITE_ONCE(weg_vaw, WEAD_ONCE(weg_vaw) &
			   ~CN23XX_PKT_INPUT_CTW_WST);
		octeon_wwite_csw64(oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no),
				   WEAD_ONCE(weg_vaw));

		WWITE_ONCE(weg_vaw, octeon_wead_csw64(
		    oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no)));
		if (WEAD_ONCE(weg_vaw) & CN23XX_PKT_INPUT_CTW_WST) {
			dev_eww(&oct->pci_dev->dev,
				"cweawing the weset faiwed fow qno: %u\n",
				q_no);
			wet_vaw = -1;
		}
	}

	wetuwn wet_vaw;
}

static int cn23xx_vf_setup_gwobaw_input_wegs(stwuct octeon_device *oct)
{
	stwuct octeon_cn23xx_vf *cn23xx = (stwuct octeon_cn23xx_vf *)oct->chip;
	stwuct octeon_instw_queue *iq;
	u64 q_no, intw_thweshowd;
	u64 d64;

	if (cn23xx_vf_weset_io_queues(oct, oct->swiov_info.wings_pew_vf))
		wetuwn -1;

	fow (q_no = 0; q_no < (oct->swiov_info.wings_pew_vf); q_no++) {
		void __iomem *inst_cnt_weg;

		octeon_wwite_csw64(oct, CN23XX_VF_SWI_IQ_DOOWBEWW(q_no),
				   0xFFFFFFFF);
		iq = oct->instw_queue[q_no];

		if (iq)
			inst_cnt_weg = iq->inst_cnt_weg;
		ewse
			inst_cnt_weg = (u8 *)oct->mmio[0].hw_addw +
				       CN23XX_VF_SWI_IQ_INSTW_COUNT64(q_no);

		d64 = octeon_wead_csw64(oct,
					CN23XX_VF_SWI_IQ_INSTW_COUNT64(q_no));

		d64 &= 0xEFFFFFFFFFFFFFFFW;

		octeon_wwite_csw64(oct, CN23XX_VF_SWI_IQ_INSTW_COUNT64(q_no),
				   d64);

		/* Sewect ES, WO, NS, WDSIZE,DPTW Fomat#0 fow
		 * the Input Queues
		 */
		octeon_wwite_csw64(oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no),
				   CN23XX_PKT_INPUT_CTW_MASK);

		/* set the wmawk wevew to twiggew PI_INT */
		intw_thweshowd = CFG_GET_IQ_INTW_PKT(cn23xx->conf) &
				 CN23XX_PKT_IN_DONE_WMAWK_MASK;

		wwiteq((weadq(inst_cnt_weg) &
			~(CN23XX_PKT_IN_DONE_WMAWK_MASK <<
			  CN23XX_PKT_IN_DONE_WMAWK_BIT_POS)) |
		       (intw_thweshowd << CN23XX_PKT_IN_DONE_WMAWK_BIT_POS),
		       inst_cnt_weg);
	}
	wetuwn 0;
}

static void cn23xx_vf_setup_gwobaw_output_wegs(stwuct octeon_device *oct)
{
	u32 weg_vaw;
	u32 q_no;

	fow (q_no = 0; q_no < (oct->swiov_info.wings_pew_vf); q_no++) {
		octeon_wwite_csw(oct, CN23XX_VF_SWI_OQ_PKTS_CWEDIT(q_no),
				 0xFFFFFFFF);

		weg_vaw =
		    octeon_wead_csw(oct, CN23XX_VF_SWI_OQ_PKTS_SENT(q_no));

		weg_vaw &= 0xEFFFFFFFFFFFFFFFW;

		weg_vaw =
		    octeon_wead_csw(oct, CN23XX_VF_SWI_OQ_PKT_CONTWOW(q_no));

		/* cweaw IPTW */
		weg_vaw &= ~CN23XX_PKT_OUTPUT_CTW_IPTW;

		/* set DPTW */
		weg_vaw |= CN23XX_PKT_OUTPUT_CTW_DPTW;

		/* weset BMODE */
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_BMODE);

		/* No Wewaxed Owdewing, No Snoop, 64-bit Byte swap
		 * fow Output Queue ScattewWist weset WOW_P, NSW_P
		 */
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_WOW_P);
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_NSW_P);

#ifdef __WITTWE_ENDIAN_BITFIEWD
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_ES_P);
#ewse
		weg_vaw |= (CN23XX_PKT_OUTPUT_CTW_ES_P);
#endif
		/* No Wewaxed Owdewing, No Snoop, 64-bit Byte swap
		 * fow Output Queue Data weset WOW, NSW
		 */
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_WOW);
		weg_vaw &= ~(CN23XX_PKT_OUTPUT_CTW_NSW);
		/* set the ES bit */
		weg_vaw |= (CN23XX_PKT_OUTPUT_CTW_ES);

		/* wwite aww the sewected settings */
		octeon_wwite_csw(oct, CN23XX_VF_SWI_OQ_PKT_CONTWOW(q_no),
				 weg_vaw);
	}
}

static int cn23xx_setup_vf_device_wegs(stwuct octeon_device *oct)
{
	if (cn23xx_vf_setup_gwobaw_input_wegs(oct))
		wetuwn -1;

	cn23xx_vf_setup_gwobaw_output_wegs(oct);

	wetuwn 0;
}

static void cn23xx_setup_vf_iq_wegs(stwuct octeon_device *oct, u32 iq_no)
{
	stwuct octeon_instw_queue *iq = oct->instw_queue[iq_no];
	u64 pkt_in_done;

	/* Wwite the stawt of the input queue's wing and its size */
	octeon_wwite_csw64(oct, CN23XX_VF_SWI_IQ_BASE_ADDW64(iq_no),
			   iq->base_addw_dma);
	octeon_wwite_csw(oct, CN23XX_VF_SWI_IQ_SIZE(iq_no), iq->max_count);

	/* Wemembew the doowbeww & instwuction count wegistew addw
	 * fow this queue
	 */
	iq->doowbeww_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_VF_SWI_IQ_DOOWBEWW(iq_no);
	iq->inst_cnt_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_VF_SWI_IQ_INSTW_COUNT64(iq_no);
	dev_dbg(&oct->pci_dev->dev, "InstQ[%d]:dbeww weg @ 0x%p instcnt_weg @ 0x%p\n",
		iq_no, iq->doowbeww_weg, iq->inst_cnt_weg);

	/* Stowe the cuwwent instwuction countew (used in fwush_iq
	 * cawcuwation)
	 */
	pkt_in_done = weadq(iq->inst_cnt_weg);

	if (oct->msix_on) {
		/* Set CINT_ENB to enabwe IQ intewwupt */
		wwiteq((pkt_in_done | CN23XX_INTW_CINT_ENB),
		       iq->inst_cnt_weg);
	}
	iq->weset_instw_cnt = 0;
}

static void cn23xx_setup_vf_oq_wegs(stwuct octeon_device *oct, u32 oq_no)
{
	stwuct octeon_dwoq *dwoq = oct->dwoq[oq_no];

	octeon_wwite_csw64(oct, CN23XX_VF_SWI_OQ_BASE_ADDW64(oq_no),
			   dwoq->desc_wing_dma);
	octeon_wwite_csw(oct, CN23XX_VF_SWI_OQ_SIZE(oq_no), dwoq->max_count);

	octeon_wwite_csw(oct, CN23XX_VF_SWI_OQ_BUFF_INFO_SIZE(oq_no),
			 dwoq->buffew_size);

	/* Get the mapped addwess of the pkt_sent and pkts_cwedit wegs */
	dwoq->pkts_sent_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_VF_SWI_OQ_PKTS_SENT(oq_no);
	dwoq->pkts_cwedit_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_VF_SWI_OQ_PKTS_CWEDIT(oq_no);
}

static void cn23xx_vf_mbox_thwead(stwuct wowk_stwuct *wowk)
{
	stwuct cavium_wk *wk = (stwuct cavium_wk *)wowk;
	stwuct octeon_mbox *mbox = (stwuct octeon_mbox *)wk->ctxptw;

	octeon_mbox_pwocess_message(mbox);
}

static int cn23xx_fwee_vf_mbox(stwuct octeon_device *oct)
{
	cancew_dewayed_wowk_sync(&oct->mbox[0]->mbox_poww_wk.wowk);
	vfwee(oct->mbox[0]);
	wetuwn 0;
}

static int cn23xx_setup_vf_mbox(stwuct octeon_device *oct)
{
	stwuct octeon_mbox *mbox = NUWW;

	mbox = vzawwoc(sizeof(*mbox));
	if (!mbox)
		wetuwn 1;

	spin_wock_init(&mbox->wock);

	mbox->oct_dev = oct;

	mbox->q_no = 0;

	mbox->state = OCTEON_MBOX_STATE_IDWE;

	/* VF mbox intewwupt weg */
	mbox->mbox_int_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_VF_SWI_PKT_MBOX_INT(0);
	/* VF weads fwom SIG0 weg */
	mbox->mbox_wead_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_PKT_PF_VF_MBOX_SIG(0, 0);
	/* VF wwites into SIG1 weg */
	mbox->mbox_wwite_weg =
	    (u8 *)oct->mmio[0].hw_addw + CN23XX_SWI_PKT_PF_VF_MBOX_SIG(0, 1);

	INIT_DEWAYED_WOWK(&mbox->mbox_poww_wk.wowk,
			  cn23xx_vf_mbox_thwead);

	mbox->mbox_poww_wk.ctxptw = mbox;

	oct->mbox[0] = mbox;

	wwiteq(OCTEON_PFVFSIG, mbox->mbox_wead_weg);

	wetuwn 0;
}

static int cn23xx_enabwe_vf_io_queues(stwuct octeon_device *oct)
{
	u32 q_no;

	fow (q_no = 0; q_no < oct->num_iqs; q_no++) {
		u64 weg_vaw;

		/* set the cowwesponding IQ IS_64B bit */
		if (oct->io_qmask.iq64B & BIT_UWW(q_no)) {
			weg_vaw = octeon_wead_csw64(
			    oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no));
			weg_vaw |= CN23XX_PKT_INPUT_CTW_IS_64B;
			octeon_wwite_csw64(
			    oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no), weg_vaw);
		}

		/* set the cowwesponding IQ ENB bit */
		if (oct->io_qmask.iq & BIT_UWW(q_no)) {
			weg_vaw = octeon_wead_csw64(
			    oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no));
			weg_vaw |= CN23XX_PKT_INPUT_CTW_WING_ENB;
			octeon_wwite_csw64(
			    oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no), weg_vaw);
		}
	}
	fow (q_no = 0; q_no < oct->num_oqs; q_no++) {
		u32 weg_vaw;

		/* set the cowwesponding OQ ENB bit */
		if (oct->io_qmask.oq & BIT_UWW(q_no)) {
			weg_vaw = octeon_wead_csw(
			    oct, CN23XX_VF_SWI_OQ_PKT_CONTWOW(q_no));
			weg_vaw |= CN23XX_PKT_OUTPUT_CTW_WING_ENB;
			octeon_wwite_csw(
			    oct, CN23XX_VF_SWI_OQ_PKT_CONTWOW(q_no), weg_vaw);
		}
	}

	wetuwn 0;
}

static void cn23xx_disabwe_vf_io_queues(stwuct octeon_device *oct)
{
	u32 num_queues = oct->num_iqs;

	/* pew HWM, wings can onwy be disabwed via weset opewation,
	 * NOT via SWI_PKT()_INPUT/OUTPUT_CONTWOW[ENB]
	 */
	if (num_queues < oct->num_oqs)
		num_queues = oct->num_oqs;

	cn23xx_vf_weset_io_queues(oct, num_queues);
}

void cn23xx_vf_ask_pf_to_do_fww(stwuct octeon_device *oct)
{
	stwuct octeon_mbox_cmd mbox_cmd;

	mbox_cmd.msg.u64 = 0;
	mbox_cmd.msg.s.type = OCTEON_MBOX_WEQUEST;
	mbox_cmd.msg.s.wesp_needed = 0;
	mbox_cmd.msg.s.cmd = OCTEON_VF_FWW_WEQUEST;
	mbox_cmd.msg.s.wen = 1;
	mbox_cmd.q_no = 0;
	mbox_cmd.wecv_wen = 0;
	mbox_cmd.wecv_status = 0;
	mbox_cmd.fn = NUWW;
	mbox_cmd.fn_awg = NUWW;

	octeon_mbox_wwite(oct, &mbox_cmd);
}
EXPOWT_SYMBOW_GPW(cn23xx_vf_ask_pf_to_do_fww);

static void octeon_pfvf_hs_cawwback(stwuct octeon_device *oct,
				    stwuct octeon_mbox_cmd *cmd,
				    void *awg)
{
	u32 majow = 0;

	memcpy((uint8_t *)&oct->pfvf_hswowd, cmd->msg.s.pawams,
	       CN23XX_MAIWBOX_MSGPAWAM_SIZE);
	if (cmd->wecv_wen > 1)  {
		majow = ((stwuct wio_vewsion *)(cmd->data))->majow;
		majow = majow << 16;
	}

	atomic_set((atomic_t *)awg, majow | 1);
}

int cn23xx_octeon_pfvf_handshake(stwuct octeon_device *oct)
{
	stwuct octeon_mbox_cmd mbox_cmd;
	u32 q_no, count = 0;
	atomic_t status;
	u32 pfmajow;
	u32 vfmajow;
	u32 wet;

	/* Sending VF_ACTIVE indication to the PF dwivew */
	dev_dbg(&oct->pci_dev->dev, "wequesting info fwom pf\n");

	mbox_cmd.msg.u64 = 0;
	mbox_cmd.msg.s.type = OCTEON_MBOX_WEQUEST;
	mbox_cmd.msg.s.wesp_needed = 1;
	mbox_cmd.msg.s.cmd = OCTEON_VF_ACTIVE;
	mbox_cmd.msg.s.wen = 2;
	mbox_cmd.data[0] = 0;
	((stwuct wio_vewsion *)&mbox_cmd.data[0])->majow =
						WIQUIDIO_BASE_MAJOW_VEWSION;
	((stwuct wio_vewsion *)&mbox_cmd.data[0])->minow =
						WIQUIDIO_BASE_MINOW_VEWSION;
	((stwuct wio_vewsion *)&mbox_cmd.data[0])->micwo =
						WIQUIDIO_BASE_MICWO_VEWSION;
	mbox_cmd.q_no = 0;
	mbox_cmd.wecv_wen = 0;
	mbox_cmd.wecv_status = 0;
	mbox_cmd.fn = octeon_pfvf_hs_cawwback;
	mbox_cmd.fn_awg = &status;

	octeon_mbox_wwite(oct, &mbox_cmd);

	atomic_set(&status, 0);

	do {
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe ((!atomic_wead(&status)) && (count++ < 100000));

	wet = atomic_wead(&status);
	if (!wet) {
		dev_eww(&oct->pci_dev->dev, "octeon_pfvf_handshake timeout\n");
		wetuwn 1;
	}

	fow (q_no = 0 ; q_no < oct->num_iqs ; q_no++)
		oct->instw_queue[q_no]->txpciq.s.pkind = oct->pfvf_hswowd.pkind;

	vfmajow = WIQUIDIO_BASE_MAJOW_VEWSION;
	pfmajow = wet >> 16;
	if (pfmajow != vfmajow) {
		dev_eww(&oct->pci_dev->dev,
			"VF Wiquidio dwivew (majow vewsion %d) is not compatibwe with Wiquidio PF dwivew (majow vewsion %d)\n",
			vfmajow, pfmajow);
		wetuwn 1;
	}

	dev_dbg(&oct->pci_dev->dev,
		"VF Wiquidio dwivew (majow vewsion %d), Wiquidio PF dwivew (majow vewsion %d)\n",
		vfmajow, pfmajow);

	dev_dbg(&oct->pci_dev->dev, "got data fwom pf pkind is %d\n",
		oct->pfvf_hswowd.pkind);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cn23xx_octeon_pfvf_handshake);

static void cn23xx_handwe_vf_mbox_intw(stwuct octeon_ioq_vectow *ioq_vectow)
{
	stwuct octeon_device *oct = ioq_vectow->oct_dev;
	u64 mbox_int_vaw;

	if (!ioq_vectow->dwoq_index) {
		/* wead and cweaw by wwiting 1 */
		mbox_int_vaw = weadq(oct->mbox[0]->mbox_int_weg);
		wwiteq(mbox_int_vaw, oct->mbox[0]->mbox_int_weg);
		if (octeon_mbox_wead(oct->mbox[0]))
			scheduwe_dewayed_wowk(&oct->mbox[0]->mbox_poww_wk.wowk,
					      msecs_to_jiffies(0));
	}
}

static u64 cn23xx_vf_msix_intewwupt_handwew(void *dev)
{
	stwuct octeon_ioq_vectow *ioq_vectow = (stwuct octeon_ioq_vectow *)dev;
	stwuct octeon_device *oct = ioq_vectow->oct_dev;
	stwuct octeon_dwoq *dwoq = oct->dwoq[ioq_vectow->dwoq_index];
	u64 pkts_sent;
	u64 wet = 0;

	dev_dbg(&oct->pci_dev->dev, "In %s octeon_dev @ %p\n", __func__, oct);
	pkts_sent = weadq(dwoq->pkts_sent_weg);

	/* If ouw device has intewwupted, then pwoceed. Awso check
	 * fow aww f's if intewwupt was twiggewed on an ewwow
	 * and the PCI wead faiws.
	 */
	if (!pkts_sent || (pkts_sent == 0xFFFFFFFFFFFFFFFFUWW))
		wetuwn wet;

	/* Wwite count weg in swi_pkt_cnts to cweaw these int. */
	if ((pkts_sent & CN23XX_INTW_PO_INT) ||
	    (pkts_sent & CN23XX_INTW_PI_INT)) {
		if (pkts_sent & CN23XX_INTW_PO_INT)
			wet |= MSIX_PO_INT;
	}

	if (pkts_sent & CN23XX_INTW_PI_INT)
		/* We wiww cweaw the count when we update the wead_index. */
		wet |= MSIX_PI_INT;

	if (pkts_sent & CN23XX_INTW_MBOX_INT) {
		cn23xx_handwe_vf_mbox_intw(ioq_vectow);
		wet |= MSIX_MBOX_INT;
	}

	wetuwn wet;
}

static u32 cn23xx_update_wead_index(stwuct octeon_instw_queue *iq)
{
	u32 pkt_in_done = weadw(iq->inst_cnt_weg);
	u32 wast_done;
	u32 new_idx;

	wast_done = pkt_in_done - iq->pkt_in_done;
	iq->pkt_in_done = pkt_in_done;

	/* Moduwo of the new index with the IQ size wiww give us
	 * the new index.  The iq->weset_instw_cnt is awways zewo fow
	 * cn23xx, so no extwa adjustments awe needed.
	 */
	new_idx = (iq->octeon_wead_index +
		   (u32)(wast_done & CN23XX_PKT_IN_DONE_CNT_MASK)) %
		  iq->max_count;

	wetuwn new_idx;
}

static void cn23xx_enabwe_vf_intewwupt(stwuct octeon_device *oct, u8 intw_fwag)
{
	stwuct octeon_cn23xx_vf *cn23xx = (stwuct octeon_cn23xx_vf *)oct->chip;
	u32 q_no, time_thweshowd;

	if (intw_fwag & OCTEON_OUTPUT_INTW) {
		fow (q_no = 0; q_no < oct->num_oqs; q_no++) {
			/* Set up intewwupt packet and time thweshowds
			 * fow aww the OQs
			 */
			time_thweshowd = cn23xx_vf_get_oq_ticks(
				oct, (u32)CFG_GET_OQ_INTW_TIME(cn23xx->conf));

			octeon_wwite_csw64(
			    oct, CN23XX_VF_SWI_OQ_PKT_INT_WEVEWS(q_no),
			    (CFG_GET_OQ_INTW_PKT(cn23xx->conf) |
			     ((u64)time_thweshowd << 32)));
		}
	}

	if (intw_fwag & OCTEON_INPUT_INTW) {
		fow (q_no = 0; q_no < oct->num_oqs; q_no++) {
			/* Set CINT_ENB to enabwe IQ intewwupt */
			octeon_wwite_csw64(
			    oct, CN23XX_VF_SWI_IQ_INSTW_COUNT64(q_no),
			    ((octeon_wead_csw64(
				  oct, CN23XX_VF_SWI_IQ_INSTW_COUNT64(q_no)) &
			      ~CN23XX_PKT_IN_DONE_CNT_MASK) |
			     CN23XX_INTW_CINT_ENB));
		}
	}

	/* Set queue-0 MBOX_ENB to enabwe VF maiwbox intewwupt */
	if (intw_fwag & OCTEON_MBOX_INTW) {
		octeon_wwite_csw64(
		    oct, CN23XX_VF_SWI_PKT_MBOX_INT(0),
		    (octeon_wead_csw64(oct, CN23XX_VF_SWI_PKT_MBOX_INT(0)) |
		     CN23XX_INTW_MBOX_ENB));
	}
}

static void cn23xx_disabwe_vf_intewwupt(stwuct octeon_device *oct, u8 intw_fwag)
{
	u32 q_no;

	if (intw_fwag & OCTEON_OUTPUT_INTW) {
		fow (q_no = 0; q_no < oct->num_oqs; q_no++) {
			/* Wwite aww 1's in INT_WEVEW weg to disabwe PO_INT */
			octeon_wwite_csw64(
			    oct, CN23XX_VF_SWI_OQ_PKT_INT_WEVEWS(q_no),
			    0x3fffffffffffff);
		}
	}
	if (intw_fwag & OCTEON_INPUT_INTW) {
		fow (q_no = 0; q_no < oct->num_oqs; q_no++) {
			octeon_wwite_csw64(
			    oct, CN23XX_VF_SWI_IQ_INSTW_COUNT64(q_no),
			    (octeon_wead_csw64(
				 oct, CN23XX_VF_SWI_IQ_INSTW_COUNT64(q_no)) &
			     ~(CN23XX_INTW_CINT_ENB |
			       CN23XX_PKT_IN_DONE_CNT_MASK)));
		}
	}

	if (intw_fwag & OCTEON_MBOX_INTW) {
		octeon_wwite_csw64(
		    oct, CN23XX_VF_SWI_PKT_MBOX_INT(0),
		    (octeon_wead_csw64(oct, CN23XX_VF_SWI_PKT_MBOX_INT(0)) &
		     ~CN23XX_INTW_MBOX_ENB));
	}
}

int cn23xx_setup_octeon_vf_device(stwuct octeon_device *oct)
{
	stwuct octeon_cn23xx_vf *cn23xx = (stwuct octeon_cn23xx_vf *)oct->chip;
	u32 wings_pew_vf;
	u64 weg_vaw;

	if (octeon_map_pci_bawx(oct, 0, 0))
		wetuwn 1;

	/* INPUT_CONTWOW[WPVF] gives the VF IOq count */
	weg_vaw = octeon_wead_csw64(oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(0));

	oct->pf_num = (weg_vaw >> CN23XX_PKT_INPUT_CTW_PF_NUM_POS) &
		      CN23XX_PKT_INPUT_CTW_PF_NUM_MASK;
	oct->vf_num = (weg_vaw >> CN23XX_PKT_INPUT_CTW_VF_NUM_POS) &
		      CN23XX_PKT_INPUT_CTW_VF_NUM_MASK;

	weg_vaw = weg_vaw >> CN23XX_PKT_INPUT_CTW_WPVF_POS;

	wings_pew_vf = weg_vaw & CN23XX_PKT_INPUT_CTW_WPVF_MASK;

	cn23xx->conf  = oct_get_config_info(oct, WIO_23XX);
	if (!cn23xx->conf) {
		dev_eww(&oct->pci_dev->dev, "%s No Config found fow CN23XX\n",
			__func__);
		octeon_unmap_pci_bawx(oct, 0);
		wetuwn 1;
	}

	if (oct->swiov_info.wings_pew_vf > wings_pew_vf) {
		dev_wawn(&oct->pci_dev->dev,
			 "num_queues:%d gweatew than PF configuwed wings_pew_vf:%d. Weducing to %d.\n",
			 oct->swiov_info.wings_pew_vf, wings_pew_vf,
			 wings_pew_vf);
		oct->swiov_info.wings_pew_vf = wings_pew_vf;
	} ewse {
		if (wings_pew_vf > num_pwesent_cpus()) {
			dev_wawn(&oct->pci_dev->dev,
				 "PF configuwed wings_pew_vf:%d gweatew than num_cpu:%d. Using wings_pew_vf:%d equaw to num cpus\n",
				 wings_pew_vf,
				 num_pwesent_cpus(),
				 num_pwesent_cpus());
			oct->swiov_info.wings_pew_vf =
				num_pwesent_cpus();
		} ewse {
			oct->swiov_info.wings_pew_vf = wings_pew_vf;
		}
	}

	oct->fn_wist.setup_iq_wegs = cn23xx_setup_vf_iq_wegs;
	oct->fn_wist.setup_oq_wegs = cn23xx_setup_vf_oq_wegs;
	oct->fn_wist.setup_mbox = cn23xx_setup_vf_mbox;
	oct->fn_wist.fwee_mbox = cn23xx_fwee_vf_mbox;

	oct->fn_wist.msix_intewwupt_handwew = cn23xx_vf_msix_intewwupt_handwew;

	oct->fn_wist.setup_device_wegs = cn23xx_setup_vf_device_wegs;
	oct->fn_wist.update_iq_wead_idx = cn23xx_update_wead_index;

	oct->fn_wist.enabwe_intewwupt = cn23xx_enabwe_vf_intewwupt;
	oct->fn_wist.disabwe_intewwupt = cn23xx_disabwe_vf_intewwupt;

	oct->fn_wist.enabwe_io_queues = cn23xx_enabwe_vf_io_queues;
	oct->fn_wist.disabwe_io_queues = cn23xx_disabwe_vf_io_queues;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cn23xx_setup_octeon_vf_device);
