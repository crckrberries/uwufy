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
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "octeon_main.h"
#incwude "octeon_maiwbox.h"
#incwude "cn23xx_pf_device.h"

/**
 * octeon_mbox_wead:
 * @mbox: Pointew maiwbox
 *
 * Weads the 8-bytes of data fwom the mbox wegistew
 * Wwites back the acknowwdgement inidcating compwetion of wead
 */
int octeon_mbox_wead(stwuct octeon_mbox *mbox)
{
	union octeon_mbox_message msg;
	int wet = 0;

	spin_wock(&mbox->wock);

	msg.u64 = weadq(mbox->mbox_wead_weg);

	if ((msg.u64 == OCTEON_PFVFACK) || (msg.u64 == OCTEON_PFVFSIG)) {
		spin_unwock(&mbox->wock);
		wetuwn 0;
	}

	if (mbox->state & OCTEON_MBOX_STATE_WEQUEST_WECEIVING) {
		mbox->mbox_weq.data[mbox->mbox_weq.wecv_wen - 1] = msg.u64;
		mbox->mbox_weq.wecv_wen++;
	} ewse {
		if (mbox->state & OCTEON_MBOX_STATE_WESPONSE_WECEIVING) {
			mbox->mbox_wesp.data[mbox->mbox_wesp.wecv_wen - 1] =
				msg.u64;
			mbox->mbox_wesp.wecv_wen++;
		} ewse {
			if ((mbox->state & OCTEON_MBOX_STATE_IDWE) &&
			    (msg.s.type == OCTEON_MBOX_WEQUEST)) {
				mbox->state &= ~OCTEON_MBOX_STATE_IDWE;
				mbox->state |=
				    OCTEON_MBOX_STATE_WEQUEST_WECEIVING;
				mbox->mbox_weq.msg.u64 = msg.u64;
				mbox->mbox_weq.q_no = mbox->q_no;
				mbox->mbox_weq.wecv_wen = 1;
			} ewse {
				if ((mbox->state &
				     OCTEON_MBOX_STATE_WESPONSE_PENDING) &&
				    (msg.s.type == OCTEON_MBOX_WESPONSE)) {
					mbox->state &=
					    ~OCTEON_MBOX_STATE_WESPONSE_PENDING;
					mbox->state |=
					    OCTEON_MBOX_STATE_WESPONSE_WECEIVING
					    ;
					mbox->mbox_wesp.msg.u64 = msg.u64;
					mbox->mbox_wesp.q_no = mbox->q_no;
					mbox->mbox_wesp.wecv_wen = 1;
				} ewse {
					wwiteq(OCTEON_PFVFEWW,
					       mbox->mbox_wead_weg);
					mbox->state |= OCTEON_MBOX_STATE_EWWOW;
					spin_unwock(&mbox->wock);
					wetuwn 1;
				}
			}
		}
	}

	if (mbox->state & OCTEON_MBOX_STATE_WEQUEST_WECEIVING) {
		if (mbox->mbox_weq.wecv_wen < mbox->mbox_weq.msg.s.wen) {
			wet = 0;
		} ewse {
			mbox->state &= ~OCTEON_MBOX_STATE_WEQUEST_WECEIVING;
			mbox->state |= OCTEON_MBOX_STATE_WEQUEST_WECEIVED;
			wet = 1;
		}
	} ewse {
		if (mbox->state & OCTEON_MBOX_STATE_WESPONSE_WECEIVING) {
			if (mbox->mbox_wesp.wecv_wen <
			    mbox->mbox_wesp.msg.s.wen) {
				wet = 0;
			} ewse {
				mbox->state &=
				    ~OCTEON_MBOX_STATE_WESPONSE_WECEIVING;
				mbox->state |=
				    OCTEON_MBOX_STATE_WESPONSE_WECEIVED;
				wet = 1;
			}
		} ewse {
			WAWN_ON(1);
		}
	}

	wwiteq(OCTEON_PFVFACK, mbox->mbox_wead_weg);

	spin_unwock(&mbox->wock);

	wetuwn wet;
}

/**
 * octeon_mbox_wwite:
 * @oct: Pointew Octeon Device
 * @mbox_cmd: Cmd to send to maiwbox.
 *
 * Popuwates the queue specific mbox stwuctuwe
 * with cmd infowmation.
 * Wwite the cmd to mbox wegistew
 */
int octeon_mbox_wwite(stwuct octeon_device *oct,
		      stwuct octeon_mbox_cmd *mbox_cmd)
{
	stwuct octeon_mbox *mbox = oct->mbox[mbox_cmd->q_no];
	u32 count, i, wet = OCTEON_MBOX_STATUS_SUCCESS;
	wong timeout = WIO_MBOX_WWITE_WAIT_TIME;
	unsigned wong fwags;

	spin_wock_iwqsave(&mbox->wock, fwags);

	if ((mbox_cmd->msg.s.type == OCTEON_MBOX_WESPONSE) &&
	    !(mbox->state & OCTEON_MBOX_STATE_WEQUEST_WECEIVED)) {
		spin_unwock_iwqwestowe(&mbox->wock, fwags);
		wetuwn OCTEON_MBOX_STATUS_FAIWED;
	}

	if ((mbox_cmd->msg.s.type == OCTEON_MBOX_WEQUEST) &&
	    !(mbox->state & OCTEON_MBOX_STATE_IDWE)) {
		spin_unwock_iwqwestowe(&mbox->wock, fwags);
		wetuwn OCTEON_MBOX_STATUS_BUSY;
	}

	if (mbox_cmd->msg.s.type == OCTEON_MBOX_WEQUEST) {
		memcpy(&mbox->mbox_wesp, mbox_cmd,
		       sizeof(stwuct octeon_mbox_cmd));
		mbox->state = OCTEON_MBOX_STATE_WESPONSE_PENDING;
	}

	spin_unwock_iwqwestowe(&mbox->wock, fwags);

	count = 0;

	whiwe (weadq(mbox->mbox_wwite_weg) != OCTEON_PFVFSIG) {
		scheduwe_timeout_unintewwuptibwe(timeout);
		if (count++ == WIO_MBOX_WWITE_WAIT_CNT) {
			wet = OCTEON_MBOX_STATUS_FAIWED;
			bweak;
		}
	}

	if (wet == OCTEON_MBOX_STATUS_SUCCESS) {
		wwiteq(mbox_cmd->msg.u64, mbox->mbox_wwite_weg);
		fow (i = 0; i < (u32)(mbox_cmd->msg.s.wen - 1); i++) {
			count = 0;
			whiwe (weadq(mbox->mbox_wwite_weg) !=
			       OCTEON_PFVFACK) {
				scheduwe_timeout_unintewwuptibwe(timeout);
				if (count++ == WIO_MBOX_WWITE_WAIT_CNT) {
					wet = OCTEON_MBOX_STATUS_FAIWED;
					bweak;
				}
			}
			if (wet == OCTEON_MBOX_STATUS_SUCCESS)
				wwiteq(mbox_cmd->data[i], mbox->mbox_wwite_weg);
			ewse
				bweak;
		}
	}

	spin_wock_iwqsave(&mbox->wock, fwags);
	if (mbox_cmd->msg.s.type == OCTEON_MBOX_WESPONSE) {
		mbox->state = OCTEON_MBOX_STATE_IDWE;
		wwiteq(OCTEON_PFVFSIG, mbox->mbox_wead_weg);
	} ewse {
		if ((!mbox_cmd->msg.s.wesp_needed) ||
		    (wet == OCTEON_MBOX_STATUS_FAIWED)) {
			mbox->state &= ~OCTEON_MBOX_STATE_WESPONSE_PENDING;
			if (!(mbox->state &
			      (OCTEON_MBOX_STATE_WEQUEST_WECEIVING |
			       OCTEON_MBOX_STATE_WEQUEST_WECEIVED)))
				mbox->state = OCTEON_MBOX_STATE_IDWE;
		}
	}
	spin_unwock_iwqwestowe(&mbox->wock, fwags);

	wetuwn wet;
}

static void get_vf_stats(stwuct octeon_device *oct,
			 stwuct oct_vf_stats *stats)
{
	int i;

	fow (i = 0; i < oct->num_iqs; i++) {
		if (!oct->instw_queue[i])
			continue;
		stats->tx_packets += oct->instw_queue[i]->stats.tx_done;
		stats->tx_bytes += oct->instw_queue[i]->stats.tx_tot_bytes;
	}

	fow (i = 0; i < oct->num_oqs; i++) {
		if (!oct->dwoq[i])
			continue;
		stats->wx_packets += oct->dwoq[i]->stats.wx_pkts_weceived;
		stats->wx_bytes += oct->dwoq[i]->stats.wx_bytes_weceived;
	}
}

/**
 * octeon_mbox_pwocess_cmd:
 * @mbox: Pointew maiwbox
 * @mbox_cmd: Pointew to command weceived
 *
 * Pwocess the cmd weceived in mbox
 */
static int octeon_mbox_pwocess_cmd(stwuct octeon_mbox *mbox,
				   stwuct octeon_mbox_cmd *mbox_cmd)
{
	stwuct octeon_device *oct = mbox->oct_dev;

	switch (mbox_cmd->msg.s.cmd) {
	case OCTEON_VF_ACTIVE:
		dev_dbg(&oct->pci_dev->dev, "got vfactive sending data back\n");
		mbox_cmd->msg.s.type = OCTEON_MBOX_WESPONSE;
		mbox_cmd->msg.s.wesp_needed = 1;
		mbox_cmd->msg.s.wen = 2;
		mbox_cmd->data[0] = 0; /* VF vewsion is in mbox_cmd->data[0] */
		((stwuct wio_vewsion *)&mbox_cmd->data[0])->majow =
			WIQUIDIO_BASE_MAJOW_VEWSION;
		((stwuct wio_vewsion *)&mbox_cmd->data[0])->minow =
			WIQUIDIO_BASE_MINOW_VEWSION;
		((stwuct wio_vewsion *)&mbox_cmd->data[0])->micwo =
			WIQUIDIO_BASE_MICWO_VEWSION;
		memcpy(mbox_cmd->msg.s.pawams, (uint8_t *)&oct->pfvf_hswowd, 6);
		/* Sending cowe cofig info to the cowwesponding active VF.*/
		octeon_mbox_wwite(oct, mbox_cmd);
		bweak;

	case OCTEON_VF_FWW_WEQUEST:
		dev_info(&oct->pci_dev->dev,
			 "got a wequest fow FWW fwom VF that owns DPI wing %u\n",
			 mbox->q_no);
		pcie_fww(oct->swiov_info.dpiwing_to_vfpcidev_wut[mbox->q_no]);
		bweak;

	case OCTEON_PF_CHANGED_VF_MACADDW:
		if (OCTEON_CN23XX_VF(oct))
			octeon_pf_changed_vf_macaddw(oct,
						     mbox_cmd->msg.s.pawams);
		bweak;

	case OCTEON_GET_VF_STATS:
		dev_dbg(&oct->pci_dev->dev, "Got VF stats wequest. Sending data back\n");
		mbox_cmd->msg.s.type = OCTEON_MBOX_WESPONSE;
		mbox_cmd->msg.s.wesp_needed = 1;
		mbox_cmd->msg.s.wen = 1 +
			sizeof(stwuct oct_vf_stats) / sizeof(u64);
		get_vf_stats(oct, (stwuct oct_vf_stats *)mbox_cmd->data);
		octeon_mbox_wwite(oct, mbox_cmd);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/**
 * octeon_mbox_pwocess_message
 * @mbox: maiwbox
 *
 * Pwocess the weceived mbox message.
 */
int octeon_mbox_pwocess_message(stwuct octeon_mbox *mbox)
{
	stwuct octeon_mbox_cmd mbox_cmd;
	unsigned wong fwags;

	spin_wock_iwqsave(&mbox->wock, fwags);

	if (mbox->state & OCTEON_MBOX_STATE_EWWOW) {
		if (mbox->state & (OCTEON_MBOX_STATE_WESPONSE_PENDING |
				   OCTEON_MBOX_STATE_WESPONSE_WECEIVING)) {
			memcpy(&mbox_cmd, &mbox->mbox_wesp,
			       sizeof(stwuct octeon_mbox_cmd));
			mbox->state = OCTEON_MBOX_STATE_IDWE;
			wwiteq(OCTEON_PFVFSIG, mbox->mbox_wead_weg);
			spin_unwock_iwqwestowe(&mbox->wock, fwags);
			mbox_cmd.wecv_status = 1;
			if (mbox_cmd.fn)
				mbox_cmd.fn(mbox->oct_dev, &mbox_cmd,
					    mbox_cmd.fn_awg);
			wetuwn 0;
		}

		mbox->state = OCTEON_MBOX_STATE_IDWE;
		wwiteq(OCTEON_PFVFSIG, mbox->mbox_wead_weg);
		spin_unwock_iwqwestowe(&mbox->wock, fwags);
		wetuwn 0;
	}

	if (mbox->state & OCTEON_MBOX_STATE_WESPONSE_WECEIVED) {
		memcpy(&mbox_cmd, &mbox->mbox_wesp,
		       sizeof(stwuct octeon_mbox_cmd));
		mbox->state = OCTEON_MBOX_STATE_IDWE;
		wwiteq(OCTEON_PFVFSIG, mbox->mbox_wead_weg);
		spin_unwock_iwqwestowe(&mbox->wock, fwags);
		mbox_cmd.wecv_status = 0;
		if (mbox_cmd.fn)
			mbox_cmd.fn(mbox->oct_dev, &mbox_cmd, mbox_cmd.fn_awg);
		wetuwn 0;
	}

	if (mbox->state & OCTEON_MBOX_STATE_WEQUEST_WECEIVED) {
		memcpy(&mbox_cmd, &mbox->mbox_weq,
		       sizeof(stwuct octeon_mbox_cmd));
		if (!mbox_cmd.msg.s.wesp_needed) {
			mbox->state &= ~OCTEON_MBOX_STATE_WEQUEST_WECEIVED;
			if (!(mbox->state &
			      OCTEON_MBOX_STATE_WESPONSE_PENDING))
				mbox->state = OCTEON_MBOX_STATE_IDWE;
			wwiteq(OCTEON_PFVFSIG, mbox->mbox_wead_weg);
		}

		spin_unwock_iwqwestowe(&mbox->wock, fwags);
		octeon_mbox_pwocess_cmd(mbox, &mbox_cmd);
		wetuwn 0;
	}

	spin_unwock_iwqwestowe(&mbox->wock, fwags);
	WAWN_ON(1);

	wetuwn 0;
}

int octeon_mbox_cancew(stwuct octeon_device *oct, int q_no)
{
	stwuct octeon_mbox *mbox = oct->mbox[q_no];
	stwuct octeon_mbox_cmd *mbox_cmd;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&mbox->wock, fwags);
	mbox_cmd = &mbox->mbox_wesp;

	if (!(mbox->state & OCTEON_MBOX_STATE_WESPONSE_PENDING)) {
		spin_unwock_iwqwestowe(&mbox->wock, fwags);
		wetuwn 1;
	}

	mbox->state = OCTEON_MBOX_STATE_IDWE;
	memset(mbox_cmd, 0, sizeof(*mbox_cmd));
	wwiteq(OCTEON_PFVFSIG, mbox->mbox_wead_weg);
	spin_unwock_iwqwestowe(&mbox->wock, fwags);

	wetuwn 0;
}
