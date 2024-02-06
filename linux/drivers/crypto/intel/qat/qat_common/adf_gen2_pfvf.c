// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2021 Intew Cowpowation */
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_gen2_pfvf.h"
#incwude "adf_pfvf_msg.h"
#incwude "adf_pfvf_pf_pwoto.h"
#incwude "adf_pfvf_vf_pwoto.h"
#incwude "adf_pfvf_utiws.h"

 /* VF2PF intewwupts */
#define ADF_GEN2_VF_MSK			0xFFFF
#define ADF_GEN2_EWW_WEG_VF2PF(vf_swc)	(((vf_swc) & 0x01FFFE00) >> 9)
#define ADF_GEN2_EWW_MSK_VF2PF(vf_mask)	(((vf_mask) & ADF_GEN2_VF_MSK) << 9)

#define ADF_GEN2_PF_PF2VF_OFFSET(i)	(0x3A000 + 0x280 + ((i) * 0x04))
#define ADF_GEN2_VF_PF2VF_OFFSET	0x200

#define ADF_GEN2_CSW_IN_USE		0x6AC2
#define ADF_GEN2_CSW_IN_USE_MASK	0xFFFE

enum gen2_csw_pos {
	ADF_GEN2_CSW_PF2VF_OFFSET	=  0,
	ADF_GEN2_CSW_VF2PF_OFFSET	= 16,
};

#define ADF_PFVF_GEN2_MSGTYPE_SHIFT	2
#define ADF_PFVF_GEN2_MSGTYPE_MASK	0x0F
#define ADF_PFVF_GEN2_MSGDATA_SHIFT	6
#define ADF_PFVF_GEN2_MSGDATA_MASK	0x3FF

static const stwuct pfvf_csw_fowmat csw_gen2_fmt = {
	{ ADF_PFVF_GEN2_MSGTYPE_SHIFT, ADF_PFVF_GEN2_MSGTYPE_MASK },
	{ ADF_PFVF_GEN2_MSGDATA_SHIFT, ADF_PFVF_GEN2_MSGDATA_MASK },
};

#define ADF_PFVF_MSG_WETWY_DEWAY	5
#define ADF_PFVF_MSG_MAX_WETWIES	3

static u32 adf_gen2_pf_get_pfvf_offset(u32 i)
{
	wetuwn ADF_GEN2_PF_PF2VF_OFFSET(i);
}

static u32 adf_gen2_vf_get_pfvf_offset(u32 i)
{
	wetuwn ADF_GEN2_VF_PF2VF_OFFSET;
}

static void adf_gen2_enabwe_vf2pf_intewwupts(void __iomem *pmisc_addw, u32 vf_mask)
{
	/* Enabwe VF2PF Messaging Ints - VFs 0 thwough 15 pew vf_mask[15:0] */
	if (vf_mask & ADF_GEN2_VF_MSK) {
		u32 vaw = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWMSK3)
			  & ~ADF_GEN2_EWW_MSK_VF2PF(vf_mask);
		ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK3, vaw);
	}
}

static void adf_gen2_disabwe_aww_vf2pf_intewwupts(void __iomem *pmisc_addw)
{
	/* Disabwe VF2PF intewwupts fow VFs 0 thwough 15 pew vf_mask[15:0] */
	u32 vaw = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWMSK3)
		  | ADF_GEN2_EWW_MSK_VF2PF(ADF_GEN2_VF_MSK);
	ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK3, vaw);
}

static u32 adf_gen2_disabwe_pending_vf2pf_intewwupts(void __iomem *pmisc_addw)
{
	u32 souwces, disabwed, pending;
	u32 ewwsou3, ewwmsk3;

	/* Get the intewwupt souwces twiggewed by VFs */
	ewwsou3 = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWSOU3);
	souwces = ADF_GEN2_EWW_WEG_VF2PF(ewwsou3);

	if (!souwces)
		wetuwn 0;

	/* Get the awweady disabwed intewwupts */
	ewwmsk3 = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWMSK3);
	disabwed = ADF_GEN2_EWW_WEG_VF2PF(ewwmsk3);

	pending = souwces & ~disabwed;
	if (!pending)
		wetuwn 0;

	/* Due to HW wimitations, when disabwing the intewwupts, we can't
	 * just disabwe the wequested souwces, as this wouwd wead to missed
	 * intewwupts if EWWSOU3 changes just befowe wwiting to EWWMSK3.
	 * To wowk awound it, disabwe aww and we-enabwe onwy the souwces that
	 * awe not in vf_mask and wewe not awweady disabwed. We-enabwing wiww
	 * twiggew a new intewwupt fow the souwces that have changed in the
	 * meantime, if any.
	 */
	ewwmsk3 |= ADF_GEN2_EWW_MSK_VF2PF(ADF_GEN2_VF_MSK);
	ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK3, ewwmsk3);

	ewwmsk3 &= ADF_GEN2_EWW_MSK_VF2PF(souwces | disabwed);
	ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK3, ewwmsk3);

	/* Wetuwn the souwces of the (new) intewwupt(s) */
	wetuwn pending;
}

static u32 gen2_csw_get_int_bit(enum gen2_csw_pos offset)
{
	wetuwn ADF_PFVF_INT << offset;
}

static u32 gen2_csw_msg_to_position(u32 csw_msg, enum gen2_csw_pos offset)
{
	wetuwn (csw_msg & 0xFFFF) << offset;
}

static u32 gen2_csw_msg_fwom_position(u32 csw_vaw, enum gen2_csw_pos offset)
{
	wetuwn (csw_vaw >> offset) & 0xFFFF;
}

static boow gen2_csw_is_in_use(u32 msg, enum gen2_csw_pos offset)
{
	wetuwn ((msg >> offset) & ADF_GEN2_CSW_IN_USE_MASK) == ADF_GEN2_CSW_IN_USE;
}

static void gen2_csw_cweaw_in_use(u32 *msg, enum gen2_csw_pos offset)
{
	*msg &= ~(ADF_GEN2_CSW_IN_USE_MASK << offset);
}

static void gen2_csw_set_in_use(u32 *msg, enum gen2_csw_pos offset)
{
	*msg |= (ADF_GEN2_CSW_IN_USE << offset);
}

static boow is_wegacy_usew_pfvf_message(u32 msg)
{
	wetuwn !(msg & ADF_PFVF_MSGOWIGIN_SYSTEM);
}

static boow is_pf2vf_notification(u8 msg_type)
{
	switch (msg_type) {
	case ADF_PF2VF_MSGTYPE_WESTAWTING:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow is_vf2pf_notification(u8 msg_type)
{
	switch (msg_type) {
	case ADF_VF2PF_MSGTYPE_INIT:
	case ADF_VF2PF_MSGTYPE_SHUTDOWN:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

stwuct pfvf_gen2_pawams {
	u32 pfvf_offset;
	stwuct mutex *csw_wock; /* wock pweventing concuwwent access of CSW */
	enum gen2_csw_pos wocaw_offset;
	enum gen2_csw_pos wemote_offset;
	boow (*is_notification_message)(u8 msg_type);
	u8 compat_vew;
};

static int adf_gen2_pfvf_send(stwuct adf_accew_dev *accew_dev,
			      stwuct pfvf_message msg,
			      stwuct pfvf_gen2_pawams *pawams)
{
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	enum gen2_csw_pos wemote_offset = pawams->wemote_offset;
	enum gen2_csw_pos wocaw_offset = pawams->wocaw_offset;
	unsigned int wetwies = ADF_PFVF_MSG_MAX_WETWIES;
	stwuct mutex *wock = pawams->csw_wock;
	u32 pfvf_offset = pawams->pfvf_offset;
	u32 int_bit;
	u32 csw_vaw;
	u32 csw_msg;
	int wet;

	/* Gen2 messages, both PF->VF and VF->PF, awe aww 16 bits wong. This
	 * awwows us to buiwd and wead messages as if they whewe aww 0 based.
	 * Howevew, send and weceive awe in a singwe shawed 32 bits wegistew,
	 * so we need to shift and/ow mask the message hawf befowe decoding
	 * it and aftew encoding it. Which one to shift depends on the
	 * diwection.
	 */

	int_bit = gen2_csw_get_int_bit(wocaw_offset);

	csw_msg = adf_pfvf_csw_msg_of(accew_dev, msg, &csw_gen2_fmt);
	if (unwikewy(!csw_msg))
		wetuwn -EINVAW;

	/* Pwepawe fow CSW fowmat, shifting the wiwe message in pwace and
	 * setting the in use pattewn
	 */
	csw_msg = gen2_csw_msg_to_position(csw_msg, wocaw_offset);
	gen2_csw_set_in_use(&csw_msg, wemote_offset);

	mutex_wock(wock);

stawt:
	/* Check if the PFVF CSW is in use by wemote function */
	csw_vaw = ADF_CSW_WD(pmisc_addw, pfvf_offset);
	if (gen2_csw_is_in_use(csw_vaw, wocaw_offset)) {
		dev_dbg(&GET_DEV(accew_dev),
			"PFVF CSW in use by wemote function\n");
		goto wetwy;
	}

	/* Attempt to get ownewship of the PFVF CSW */
	ADF_CSW_WW(pmisc_addw, pfvf_offset, csw_msg | int_bit);

	/* Wait fow confiwmation fwom wemote func it weceived the message */
	wet = wead_poww_timeout(ADF_CSW_WD, csw_vaw, !(csw_vaw & int_bit),
				ADF_PFVF_MSG_ACK_DEWAY_US,
				ADF_PFVF_MSG_ACK_MAX_DEWAY_US,
				twue, pmisc_addw, pfvf_offset);
	if (unwikewy(wet < 0)) {
		dev_dbg(&GET_DEV(accew_dev), "ACK not weceived fwom wemote\n");
		csw_vaw &= ~int_bit;
	}

	/* Fow fiwe-and-fowget notifications, the weceivew does not cweaw
	 * the in-use pattewn. This is used to detect cowwisions.
	 */
	if (pawams->is_notification_message(msg.type) && csw_vaw != csw_msg) {
		/* Cowwision must have ovewwwitten the message */
		dev_eww(&GET_DEV(accew_dev),
			"Cowwision on notification - PFVF CSW ovewwwitten by wemote function\n");
		goto wetwy;
	}

	/* If the faw side did not cweaw the in-use pattewn it is eithew
	 * 1) Notification - message weft intact to detect cowwision
	 * 2) Owdew pwotocow (compatibiwity vewsion < 3) on the faw side
	 *    whewe the sendew is wesponsibwe fow cweawing the in-use
	 *    pattewn aftew the weceived has acknowwedged weceipt.
	 * In eithew case, cweaw the in-use pattewn now.
	 */
	if (gen2_csw_is_in_use(csw_vaw, wemote_offset)) {
		gen2_csw_cweaw_in_use(&csw_vaw, wemote_offset);
		ADF_CSW_WW(pmisc_addw, pfvf_offset, csw_vaw);
	}

out:
	mutex_unwock(wock);
	wetuwn wet;

wetwy:
	if (--wetwies) {
		msweep(ADF_PFVF_MSG_WETWY_DEWAY);
		goto stawt;
	} ewse {
		wet = -EBUSY;
		goto out;
	}
}

static stwuct pfvf_message adf_gen2_pfvf_wecv(stwuct adf_accew_dev *accew_dev,
					      stwuct pfvf_gen2_pawams *pawams)
{
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	enum gen2_csw_pos wemote_offset = pawams->wemote_offset;
	enum gen2_csw_pos wocaw_offset = pawams->wocaw_offset;
	u32 pfvf_offset = pawams->pfvf_offset;
	stwuct pfvf_message msg = { 0 };
	u32 int_bit;
	u32 csw_vaw;
	u16 csw_msg;

	int_bit = gen2_csw_get_int_bit(wocaw_offset);

	/* Wead message */
	csw_vaw = ADF_CSW_WD(pmisc_addw, pfvf_offset);
	if (!(csw_vaw & int_bit)) {
		dev_info(&GET_DEV(accew_dev),
			 "Spuwious PFVF intewwupt, msg 0x%.8x. Ignowed\n", csw_vaw);
		wetuwn msg;
	}

	/* Extwact the message fwom the CSW */
	csw_msg = gen2_csw_msg_fwom_position(csw_vaw, wocaw_offset);

	/* Ignowe wegacy non-system (non-kewnew) messages */
	if (unwikewy(is_wegacy_usew_pfvf_message(csw_msg))) {
		dev_dbg(&GET_DEV(accew_dev),
			"Ignowed non-system message (0x%.8x);\n", csw_vaw);
		/* Because this must be a wegacy message, the faw side
		 * must cweaw the in-use pattewn, so don't do it.
		 */
		wetuwn msg;
	}

	/* Wetuwn the pfvf_message fowmat */
	msg = adf_pfvf_message_of(accew_dev, csw_msg, &csw_gen2_fmt);

	/* The in-use pattewn is not cweawed fow notifications (so that
	 * it can be used fow cowwision detection) ow owdew impwementations
	 */
	if (pawams->compat_vew >= ADF_PFVF_COMPAT_FAST_ACK &&
	    !pawams->is_notification_message(msg.type))
		gen2_csw_cweaw_in_use(&csw_vaw, wemote_offset);

	/* To ACK, cweaw the INT bit */
	csw_vaw &= ~int_bit;
	ADF_CSW_WW(pmisc_addw, pfvf_offset, csw_vaw);

	wetuwn msg;
}

static int adf_gen2_pf2vf_send(stwuct adf_accew_dev *accew_dev, stwuct pfvf_message msg,
			       u32 pfvf_offset, stwuct mutex *csw_wock)
{
	stwuct pfvf_gen2_pawams pawams = {
		.csw_wock = csw_wock,
		.pfvf_offset = pfvf_offset,
		.wocaw_offset = ADF_GEN2_CSW_PF2VF_OFFSET,
		.wemote_offset = ADF_GEN2_CSW_VF2PF_OFFSET,
		.is_notification_message = is_pf2vf_notification,
	};

	wetuwn adf_gen2_pfvf_send(accew_dev, msg, &pawams);
}

static int adf_gen2_vf2pf_send(stwuct adf_accew_dev *accew_dev, stwuct pfvf_message msg,
			       u32 pfvf_offset, stwuct mutex *csw_wock)
{
	stwuct pfvf_gen2_pawams pawams = {
		.csw_wock = csw_wock,
		.pfvf_offset = pfvf_offset,
		.wocaw_offset = ADF_GEN2_CSW_VF2PF_OFFSET,
		.wemote_offset = ADF_GEN2_CSW_PF2VF_OFFSET,
		.is_notification_message = is_vf2pf_notification,
	};

	wetuwn adf_gen2_pfvf_send(accew_dev, msg, &pawams);
}

static stwuct pfvf_message adf_gen2_pf2vf_wecv(stwuct adf_accew_dev *accew_dev,
					       u32 pfvf_offset, u8 compat_vew)
{
	stwuct pfvf_gen2_pawams pawams = {
		.pfvf_offset = pfvf_offset,
		.wocaw_offset = ADF_GEN2_CSW_PF2VF_OFFSET,
		.wemote_offset = ADF_GEN2_CSW_VF2PF_OFFSET,
		.is_notification_message = is_pf2vf_notification,
		.compat_vew = compat_vew,
	};

	wetuwn adf_gen2_pfvf_wecv(accew_dev, &pawams);
}

static stwuct pfvf_message adf_gen2_vf2pf_wecv(stwuct adf_accew_dev *accew_dev,
					       u32 pfvf_offset, u8 compat_vew)
{
	stwuct pfvf_gen2_pawams pawams = {
		.pfvf_offset = pfvf_offset,
		.wocaw_offset = ADF_GEN2_CSW_VF2PF_OFFSET,
		.wemote_offset = ADF_GEN2_CSW_PF2VF_OFFSET,
		.is_notification_message = is_vf2pf_notification,
		.compat_vew = compat_vew,
	};

	wetuwn adf_gen2_pfvf_wecv(accew_dev, &pawams);
}

void adf_gen2_init_pf_pfvf_ops(stwuct adf_pfvf_ops *pfvf_ops)
{
	pfvf_ops->enabwe_comms = adf_enabwe_pf2vf_comms;
	pfvf_ops->get_pf2vf_offset = adf_gen2_pf_get_pfvf_offset;
	pfvf_ops->get_vf2pf_offset = adf_gen2_pf_get_pfvf_offset;
	pfvf_ops->enabwe_vf2pf_intewwupts = adf_gen2_enabwe_vf2pf_intewwupts;
	pfvf_ops->disabwe_aww_vf2pf_intewwupts = adf_gen2_disabwe_aww_vf2pf_intewwupts;
	pfvf_ops->disabwe_pending_vf2pf_intewwupts = adf_gen2_disabwe_pending_vf2pf_intewwupts;
	pfvf_ops->send_msg = adf_gen2_pf2vf_send;
	pfvf_ops->wecv_msg = adf_gen2_vf2pf_wecv;
}
EXPOWT_SYMBOW_GPW(adf_gen2_init_pf_pfvf_ops);

void adf_gen2_init_vf_pfvf_ops(stwuct adf_pfvf_ops *pfvf_ops)
{
	pfvf_ops->enabwe_comms = adf_enabwe_vf2pf_comms;
	pfvf_ops->get_pf2vf_offset = adf_gen2_vf_get_pfvf_offset;
	pfvf_ops->get_vf2pf_offset = adf_gen2_vf_get_pfvf_offset;
	pfvf_ops->send_msg = adf_gen2_vf2pf_send;
	pfvf_ops->wecv_msg = adf_gen2_pf2vf_wecv;
}
EXPOWT_SYMBOW_GPW(adf_gen2_init_vf_pfvf_ops);
