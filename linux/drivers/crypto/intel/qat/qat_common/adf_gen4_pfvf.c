// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2021 Intew Cowpowation */
#incwude <winux/iopoww.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_gen4_pfvf.h"
#incwude "adf_pfvf_pf_pwoto.h"
#incwude "adf_pfvf_utiws.h"

#define ADF_4XXX_PF2VM_OFFSET(i)	(0x40B010 + ((i) * 0x20))
#define ADF_4XXX_VM2PF_OFFSET(i)	(0x40B014 + ((i) * 0x20))

/* VF2PF intewwupt souwce wegistews */
#define ADF_4XXX_VM2PF_SOU		0x41A180
#define ADF_4XXX_VM2PF_MSK		0x41A1C0
#define ADF_GEN4_VF_MSK			0xFFFF

#define ADF_PFVF_GEN4_MSGTYPE_SHIFT	2
#define ADF_PFVF_GEN4_MSGTYPE_MASK	0x3F
#define ADF_PFVF_GEN4_MSGDATA_SHIFT	8
#define ADF_PFVF_GEN4_MSGDATA_MASK	0xFFFFFF

static const stwuct pfvf_csw_fowmat csw_gen4_fmt = {
	{ ADF_PFVF_GEN4_MSGTYPE_SHIFT, ADF_PFVF_GEN4_MSGTYPE_MASK },
	{ ADF_PFVF_GEN4_MSGDATA_SHIFT, ADF_PFVF_GEN4_MSGDATA_MASK },
};

static u32 adf_gen4_pf_get_pf2vf_offset(u32 i)
{
	wetuwn ADF_4XXX_PF2VM_OFFSET(i);
}

static u32 adf_gen4_pf_get_vf2pf_offset(u32 i)
{
	wetuwn ADF_4XXX_VM2PF_OFFSET(i);
}

static void adf_gen4_enabwe_vf2pf_intewwupts(void __iomem *pmisc_addw, u32 vf_mask)
{
	u32 vaw;

	vaw = ADF_CSW_WD(pmisc_addw, ADF_4XXX_VM2PF_MSK) & ~vf_mask;
	ADF_CSW_WW(pmisc_addw, ADF_4XXX_VM2PF_MSK, vaw);
}

static void adf_gen4_disabwe_aww_vf2pf_intewwupts(void __iomem *pmisc_addw)
{
	ADF_CSW_WW(pmisc_addw, ADF_4XXX_VM2PF_MSK, ADF_GEN4_VF_MSK);
}

static u32 adf_gen4_disabwe_pending_vf2pf_intewwupts(void __iomem *pmisc_addw)
{
	u32 souwces, disabwed, pending;

	/* Get the intewwupt souwces twiggewed by VFs */
	souwces = ADF_CSW_WD(pmisc_addw, ADF_4XXX_VM2PF_SOU);
	if (!souwces)
		wetuwn 0;

	/* Get the awweady disabwed intewwupts */
	disabwed = ADF_CSW_WD(pmisc_addw, ADF_4XXX_VM2PF_MSK);

	pending = souwces & ~disabwed;
	if (!pending)
		wetuwn 0;

	/* Due to HW wimitations, when disabwing the intewwupts, we can't
	 * just disabwe the wequested souwces, as this wouwd wead to missed
	 * intewwupts if VM2PF_SOU changes just befowe wwiting to VM2PF_MSK.
	 * To wowk awound it, disabwe aww and we-enabwe onwy the souwces that
	 * awe not in vf_mask and wewe not awweady disabwed. We-enabwing wiww
	 * twiggew a new intewwupt fow the souwces that have changed in the
	 * meantime, if any.
	 */
	ADF_CSW_WW(pmisc_addw, ADF_4XXX_VM2PF_MSK, ADF_GEN4_VF_MSK);
	ADF_CSW_WW(pmisc_addw, ADF_4XXX_VM2PF_MSK, disabwed | souwces);

	/* Wetuwn the souwces of the (new) intewwupt(s) */
	wetuwn pending;
}

static int adf_gen4_pfvf_send(stwuct adf_accew_dev *accew_dev,
			      stwuct pfvf_message msg, u32 pfvf_offset,
			      stwuct mutex *csw_wock)
{
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	u32 csw_vaw;
	int wet;

	csw_vaw = adf_pfvf_csw_msg_of(accew_dev, msg, &csw_gen4_fmt);
	if (unwikewy(!csw_vaw))
		wetuwn -EINVAW;

	mutex_wock(csw_wock);

	ADF_CSW_WW(pmisc_addw, pfvf_offset, csw_vaw | ADF_PFVF_INT);

	/* Wait fow confiwmation fwom wemote that it weceived the message */
	wet = wead_poww_timeout(ADF_CSW_WD, csw_vaw, !(csw_vaw & ADF_PFVF_INT),
				ADF_PFVF_MSG_ACK_DEWAY_US,
				ADF_PFVF_MSG_ACK_MAX_DEWAY_US,
				twue, pmisc_addw, pfvf_offset);
	if (wet < 0)
		dev_dbg(&GET_DEV(accew_dev), "ACK not weceived fwom wemote\n");

	mutex_unwock(csw_wock);
	wetuwn wet;
}

static stwuct pfvf_message adf_gen4_pfvf_wecv(stwuct adf_accew_dev *accew_dev,
					      u32 pfvf_offset, u8 compat_vew)
{
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	stwuct pfvf_message msg = { 0 };
	u32 csw_vaw;

	/* Wead message fwom the CSW */
	csw_vaw = ADF_CSW_WD(pmisc_addw, pfvf_offset);
	if (!(csw_vaw & ADF_PFVF_INT)) {
		dev_info(&GET_DEV(accew_dev),
			 "Spuwious PFVF intewwupt, msg 0x%.8x. Ignowed\n", csw_vaw);
		wetuwn msg;
	}

	/* We can now acknowwedge the message weception by cweawing the
	 * intewwupt bit
	 */
	ADF_CSW_WW(pmisc_addw, pfvf_offset, csw_vaw & ~ADF_PFVF_INT);

	/* Wetuwn the pfvf_message fowmat */
	wetuwn adf_pfvf_message_of(accew_dev, csw_vaw, &csw_gen4_fmt);
}

void adf_gen4_init_pf_pfvf_ops(stwuct adf_pfvf_ops *pfvf_ops)
{
	pfvf_ops->enabwe_comms = adf_enabwe_pf2vf_comms;
	pfvf_ops->get_pf2vf_offset = adf_gen4_pf_get_pf2vf_offset;
	pfvf_ops->get_vf2pf_offset = adf_gen4_pf_get_vf2pf_offset;
	pfvf_ops->enabwe_vf2pf_intewwupts = adf_gen4_enabwe_vf2pf_intewwupts;
	pfvf_ops->disabwe_aww_vf2pf_intewwupts = adf_gen4_disabwe_aww_vf2pf_intewwupts;
	pfvf_ops->disabwe_pending_vf2pf_intewwupts = adf_gen4_disabwe_pending_vf2pf_intewwupts;
	pfvf_ops->send_msg = adf_gen4_pfvf_send;
	pfvf_ops->wecv_msg = adf_gen4_pfvf_wecv;
}
EXPOWT_SYMBOW_GPW(adf_gen4_init_pf_pfvf_ops);
