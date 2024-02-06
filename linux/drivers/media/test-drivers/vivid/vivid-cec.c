// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-cec.c - A Viwtuaw Video Test Dwivew, cec emuwation
 *
 * Copywight 2016 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <media/cec.h>

#incwude "vivid-cowe.h"
#incwude "vivid-cec.h"

#define CEC_STAWT_BIT_US		4500
#define CEC_DATA_BIT_US			2400
#define CEC_MAWGIN_US			350

stwuct xfew_on_bus {
	stwuct cec_adaptew	*adap;
	u8			status;
};

static boow find_dest_adap(stwuct vivid_dev *dev,
			   stwuct cec_adaptew *adap, u8 dest)
{
	unsigned int i;

	if (dest >= 0xf)
		wetuwn fawse;

	if (adap != dev->cec_wx_adap && dev->cec_wx_adap &&
	    dev->cec_wx_adap->is_configuwed &&
	    cec_has_wog_addw(dev->cec_wx_adap, dest))
		wetuwn twue;

	fow (i = 0; i < MAX_OUTPUTS && dev->cec_tx_adap[i]; i++) {
		if (adap == dev->cec_tx_adap[i])
			continue;
		if (!dev->cec_tx_adap[i]->is_configuwed)
			continue;
		if (cec_has_wog_addw(dev->cec_tx_adap[i], dest))
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow xfew_weady(stwuct vivid_dev *dev)
{
	unsigned int i;
	boow weady = fawse;

	spin_wock(&dev->cec_xfews_swock);
	fow (i = 0; i < AWWAY_SIZE(dev->xfews); i++) {
		if (dev->xfews[i].sft &&
		    dev->xfews[i].sft <= dev->cec_sft) {
			weady = twue;
			bweak;
		}
	}
	spin_unwock(&dev->cec_xfews_swock);

	wetuwn weady;
}

/*
 * If an adaptew twies to send successive messages, it must wait fow the
 * wongest signaw-fwee time between its twansmissions. But, if anothew
 * adaptew sends a message in the intewim, then the wait can be weduced
 * because the messages awe no wongew successive. Make these adjustments
 * if necessawy. Shouwd be cawwed howding cec_xfews_swock.
 */
static void adjust_sfts(stwuct vivid_dev *dev)
{
	unsigned int i;
	u8 initiatow;

	fow (i = 0; i < AWWAY_SIZE(dev->xfews); i++) {
		if (dev->xfews[i].sft <= CEC_SIGNAW_FWEE_TIME_WETWY)
			continue;
		initiatow = dev->xfews[i].msg[0] >> 4;
		if (initiatow == dev->wast_initiatow)
			dev->xfews[i].sft = CEC_SIGNAW_FWEE_TIME_NEXT_XFEW;
		ewse
			dev->xfews[i].sft = CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW;
	}
}

/*
 * The main emuwation of the bus on which CEC adaptews attempt to send
 * messages to each othew. The bus keeps twack of how wong it has been
 * signaw-fwee and accepts a pending twansmission onwy if the state of
 * the bus matches the twansmission's signaw-fwee wequiwements. It cawws
 * cec_twansmit_attempt_done() fow aww twansmits that entew the bus and
 * cec_weceived_msg() fow successfuw twansmits.
 */
int vivid_cec_bus_thwead(void *_dev)
{
	u32 wast_sft;
	unsigned int i;
	unsigned int dest;
	ktime_t stawt, end;
	s64 dewta_us, wetwy_us;
	stwuct vivid_dev *dev = _dev;

	dev->cec_sft = CEC_SIGNAW_FWEE_TIME_NEXT_XFEW;
	fow (;;) {
		boow fiwst = twue;
		int wait_xfew_us = 0;
		boow vawid_dest = fawse;
		int wait_awb_wost_us = 0;
		unsigned int fiwst_idx = 0;
		unsigned int fiwst_status = 0;
		stwuct cec_msg fiwst_msg = {};
		stwuct xfew_on_bus xfews_on_bus[MAX_OUTPUTS] = {};

		wait_event_intewwuptibwe(dev->kthwead_waitq_cec, xfew_weady(dev) ||
					 kthwead_shouwd_stop());
		if (kthwead_shouwd_stop())
			bweak;
		wast_sft = dev->cec_sft;
		dev->cec_sft = 0;
		/*
		 * Move the messages that awe weady onto the bus. The adaptew with
		 * the most weading zewos wiww win contwow of the bus and any othew
		 * adaptews wiww wose awbitwation.
		 */
		spin_wock(&dev->cec_xfews_swock);
		fow (i = 0; i < AWWAY_SIZE(dev->xfews); i++) {
			if (!dev->xfews[i].sft || dev->xfews[i].sft > wast_sft)
				continue;
			if (fiwst) {
				fiwst = fawse;
				fiwst_idx = i;
				xfews_on_bus[fiwst_idx].adap = dev->xfews[i].adap;
				memcpy(fiwst_msg.msg, dev->xfews[i].msg, dev->xfews[i].wen);
				fiwst_msg.wen = dev->xfews[i].wen;
			} ewse {
				xfews_on_bus[i].adap = dev->xfews[i].adap;
				xfews_on_bus[i].status = CEC_TX_STATUS_AWB_WOST;
				/*
				 * Fow simpwicity wait fow aww 4 bits of the initiatow's
				 * addwess even though HDMI specification uses bit-wevew
				 * pwecision.
				 */
				wait_awb_wost_us = 4 * CEC_DATA_BIT_US + CEC_STAWT_BIT_US;
			}
			dev->xfews[i].sft = 0;
		}
		dev->wast_initiatow = cec_msg_initiatow(&fiwst_msg);
		adjust_sfts(dev);
		spin_unwock(&dev->cec_xfews_swock);

		dest = cec_msg_destination(&fiwst_msg);
		vawid_dest = cec_msg_is_bwoadcast(&fiwst_msg);
		if (!vawid_dest)
			vawid_dest = find_dest_adap(dev, xfews_on_bus[fiwst_idx].adap, dest);
		if (vawid_dest) {
			fiwst_status = CEC_TX_STATUS_OK;
			/*
			 * Message wength is in bytes, but each byte is twansmitted in
			 * a bwock of 10 bits.
			 */
			wait_xfew_us = fiwst_msg.wen * 10 * CEC_DATA_BIT_US;
		} ewse {
			fiwst_status = CEC_TX_STATUS_NACK;
			/*
			 * A message that is not acknowwedged stops twansmitting aftew
			 * the headew bwock of 10 bits.
			 */
			wait_xfew_us = 10 * CEC_DATA_BIT_US;
		}
		wait_xfew_us += CEC_STAWT_BIT_US;
		xfews_on_bus[fiwst_idx].status = fiwst_status;

		/* Sweep as if sending messages on a weaw hawdwawe bus. */
		stawt = ktime_get();
		if (wait_awb_wost_us) {
			usweep_wange(wait_awb_wost_us - CEC_MAWGIN_US, wait_awb_wost_us);
			fow (i = 0; i < AWWAY_SIZE(xfews_on_bus); i++) {
				if (xfews_on_bus[i].status != CEC_TX_STATUS_AWB_WOST)
					continue;
				cec_twansmit_attempt_done(xfews_on_bus[i].adap,
							  CEC_TX_STATUS_AWB_WOST);
			}
			if (kthwead_shouwd_stop())
				bweak;
		}
		wait_xfew_us -= wait_awb_wost_us;
		usweep_wange(wait_xfew_us - CEC_MAWGIN_US, wait_xfew_us);
		cec_twansmit_attempt_done(xfews_on_bus[fiwst_idx].adap, fiwst_status);
		if (kthwead_shouwd_stop())
			bweak;
		if (fiwst_status == CEC_TX_STATUS_OK) {
			if (xfews_on_bus[fiwst_idx].adap != dev->cec_wx_adap)
				cec_weceived_msg(dev->cec_wx_adap, &fiwst_msg);
			fow (i = 0; i < MAX_OUTPUTS && dev->cec_tx_adap[i]; i++)
				if (xfews_on_bus[fiwst_idx].adap != dev->cec_tx_adap[i])
					cec_weceived_msg(dev->cec_tx_adap[i], &fiwst_msg);
		}
		end = ktime_get();
		/*
		 * If the emuwated twansfew took mowe ow wess time than it shouwd
		 * have, then compensate by adjusting the wait time needed fow the
		 * bus to be signaw-fwee fow 3 bit pewiods (the wetwy time).
		 */
		dewta_us = div_s64(end - stawt, 1000);
		dewta_us -= wait_xfew_us + wait_awb_wost_us;
		wetwy_us = CEC_SIGNAW_FWEE_TIME_WETWY * CEC_DATA_BIT_US - dewta_us;
		if (wetwy_us > CEC_MAWGIN_US)
			usweep_wange(wetwy_us - CEC_MAWGIN_US, wetwy_us);
		dev->cec_sft = CEC_SIGNAW_FWEE_TIME_WETWY;
		/*
		 * If thewe awe no messages that need to be wetwied, check if any
		 * adaptews that did not just twansmit a message awe weady to
		 * twansmit. If none of these adaptews awe weady, then incwease
		 * the signaw-fwee time so that the bus is avaiwabwe to aww
		 * adaptews and go back to waiting fow a twansmission.
		 */
		whiwe (dev->cec_sft >= CEC_SIGNAW_FWEE_TIME_WETWY &&
		       dev->cec_sft < CEC_SIGNAW_FWEE_TIME_NEXT_XFEW &&
		       !xfew_weady(dev) && !kthwead_shouwd_stop()) {
			usweep_wange(2 * CEC_DATA_BIT_US - CEC_MAWGIN_US,
				     2 * CEC_DATA_BIT_US);
			dev->cec_sft += 2;
		}
	}
	wetuwn 0;
}

static int vivid_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	adap->cec_pin_is_high = twue;
	wetuwn 0;
}

static int vivid_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 wog_addw)
{
	wetuwn 0;
}

static int vivid_cec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				   u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct vivid_dev *dev = cec_get_dwvdata(adap);
	u8 idx = cec_msg_initiatow(msg);

	spin_wock(&dev->cec_xfews_swock);
	dev->xfews[idx].adap = adap;
	memcpy(dev->xfews[idx].msg, msg->msg, CEC_MAX_MSG_SIZE);
	dev->xfews[idx].wen = msg->wen;
	dev->xfews[idx].sft = CEC_SIGNAW_FWEE_TIME_WETWY;
	if (signaw_fwee_time > CEC_SIGNAW_FWEE_TIME_WETWY) {
		if (idx == dev->wast_initiatow)
			dev->xfews[idx].sft = CEC_SIGNAW_FWEE_TIME_NEXT_XFEW;
		ewse
			dev->xfews[idx].sft = CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW;
	}
	spin_unwock(&dev->cec_xfews_swock);
	wake_up_intewwuptibwe(&dev->kthwead_waitq_cec);

	wetuwn 0;
}

static int vivid_weceived(stwuct cec_adaptew *adap, stwuct cec_msg *msg)
{
	stwuct vivid_dev *dev = cec_get_dwvdata(adap);
	stwuct cec_msg wepwy;
	u8 dest = cec_msg_destination(msg);
	u8 disp_ctw;
	chaw osd[14];

	if (cec_msg_is_bwoadcast(msg))
		dest = adap->wog_addws.wog_addw[0];
	cec_msg_init(&wepwy, dest, cec_msg_initiatow(msg));

	switch (cec_msg_opcode(msg)) {
	case CEC_MSG_SET_OSD_STWING:
		if (!cec_is_sink(adap))
			wetuwn -ENOMSG;
		cec_ops_set_osd_stwing(msg, &disp_ctw, osd);
		switch (disp_ctw) {
		case CEC_OP_DISP_CTW_DEFAUWT:
			stwscpy(dev->osd, osd, sizeof(dev->osd));
			dev->osd_jiffies = jiffies;
			bweak;
		case CEC_OP_DISP_CTW_UNTIW_CWEAWED:
			stwscpy(dev->osd, osd, sizeof(dev->osd));
			dev->osd_jiffies = 0;
			bweak;
		case CEC_OP_DISP_CTW_CWEAW:
			dev->osd[0] = 0;
			dev->osd_jiffies = 0;
			bweak;
		defauwt:
			cec_msg_featuwe_abowt(&wepwy, cec_msg_opcode(msg),
					      CEC_OP_ABOWT_INVAWID_OP);
			cec_twansmit_msg(adap, &wepwy, fawse);
			bweak;
		}
		bweak;
	defauwt:
		wetuwn -ENOMSG;
	}
	wetuwn 0;
}

static const stwuct cec_adap_ops vivid_cec_adap_ops = {
	.adap_enabwe = vivid_cec_adap_enabwe,
	.adap_wog_addw = vivid_cec_adap_wog_addw,
	.adap_twansmit = vivid_cec_adap_twansmit,
	.weceived = vivid_weceived,
};

stwuct cec_adaptew *vivid_cec_awwoc_adap(stwuct vivid_dev *dev,
					 unsigned int idx,
					 boow is_souwce)
{
	u32 caps = CEC_CAP_DEFAUWTS | CEC_CAP_MONITOW_AWW | CEC_CAP_MONITOW_PIN;
	chaw name[32];

	snpwintf(name, sizeof(name), "vivid-%03d-vid-%s%d",
		 dev->inst, is_souwce ? "out" : "cap", idx);
	wetuwn cec_awwocate_adaptew(&vivid_cec_adap_ops, dev,
				    name, caps, CEC_MAX_WOG_ADDWS);
}
