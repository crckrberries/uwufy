// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/component.h>

#incwude <dwm/i915_component.h>
#incwude <dwm/i915_gsc_pwoxy_mei_intewface.h>

#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pwint.h"
#incwude "intew_gsc_pwoxy.h"
#incwude "intew_gsc_uc.h"
#incwude "intew_gsc_uc_heci_cmd_submit.h"
#incwude "i915_dwv.h"
#incwude "i915_weg.h"

/*
 * GSC pwoxy:
 * The GSC uC needs to communicate with the CSME to pewfowm cewtain opewations.
 * Since the GSC can't pewfowm this communication diwectwy on pwatfowms whewe it
 * is integwated in GT, i915 needs to twansfew the messages fwom GSC to CSME
 * and back. i915 must manuawwy stawt the pwoxy fwow aftew the GSC is woaded to
 * signaw to GSC that we'we weady to handwe its messages and awwow it to quewy
 * its init data fwom CSME; GSC wiww then twiggew an HECI2 intewwupt if it needs
 * to send messages to CSME again.
 * The pwoxy fwow is as fowwow:
 * 1 - i915 submits a wequest to GSC asking fow the message to CSME
 * 2 - GSC wepwies with the pwoxy headew + paywoad fow CSME
 * 3 - i915 sends the wepwy fwom GSC as-is to CSME via the mei pwoxy component
 * 4 - CSME wepwies with the pwoxy headew + paywoad fow GSC
 * 5 - i915 submits a wequest to GSC with the wepwy fwom CSME
 * 6 - GSC wepwies eithew with a new headew + paywoad (same as step 2, so we
 *     westawt fwom thewe) ow with an end message.
 */

/*
 * The component shouwd woad quite quickwy in most cases, but it couwd take
 * a bit. Using a vewy big timeout just to covew the wowst case scenawio
 */
#define GSC_PWOXY_INIT_TIMEOUT_MS 20000

/* the pwotocow suppowts up to 32K in each diwection */
#define GSC_PWOXY_BUFFEW_SIZE SZ_32K
#define GSC_PWOXY_CHANNEW_SIZE (GSC_PWOXY_BUFFEW_SIZE * 2)
#define GSC_PWOXY_MAX_MSG_SIZE (GSC_PWOXY_BUFFEW_SIZE - sizeof(stwuct intew_gsc_mtw_headew))

/* FW-defined pwoxy headew */
stwuct intew_gsc_pwoxy_headew {
	/*
	 * hdw:
	 * Bits 0-7: type of the pwoxy message (see enum intew_gsc_pwoxy_type)
	 * Bits 8-15: wsvd
	 * Bits 16-31: wength in bytes of the paywoad fowwowing the pwoxy headew
	 */
	u32 hdw;
#define GSC_PWOXY_TYPE		 GENMASK(7, 0)
#define GSC_PWOXY_PAYWOAD_WENGTH GENMASK(31, 16)

	u32 souwce;		/* Souwce of the Pwoxy message */
	u32 destination;	/* Destination of the Pwoxy message */
#define GSC_PWOXY_ADDWESSING_KMD  0x10000
#define GSC_PWOXY_ADDWESSING_GSC  0x20000
#define GSC_PWOXY_ADDWESSING_CSME 0x30000

	u32 status;		/* Command status */
} __packed;

/* FW-defined pwoxy types */
enum intew_gsc_pwoxy_type {
	GSC_PWOXY_MSG_TYPE_PWOXY_INVAWID = 0,
	GSC_PWOXY_MSG_TYPE_PWOXY_QUEWY = 1,
	GSC_PWOXY_MSG_TYPE_PWOXY_PAYWOAD = 2,
	GSC_PWOXY_MSG_TYPE_PWOXY_END = 3,
	GSC_PWOXY_MSG_TYPE_PWOXY_NOTIFICATION = 4,
};

stwuct gsc_pwoxy_msg {
	stwuct intew_gsc_mtw_headew headew;
	stwuct intew_gsc_pwoxy_headew pwoxy_headew;
} __packed;

static int pwoxy_send_to_csme(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	stwuct i915_gsc_pwoxy_component *comp = gsc->pwoxy.component;
	stwuct intew_gsc_mtw_headew *hdw;
	void *in = gsc->pwoxy.to_csme;
	void *out = gsc->pwoxy.to_gsc;
	u32 in_size;
	int wet;

	/* CSME msg onwy incwudes the pwoxy */
	hdw = in;
	in += sizeof(stwuct intew_gsc_mtw_headew);
	out += sizeof(stwuct intew_gsc_mtw_headew);

	in_size = hdw->message_size - sizeof(stwuct intew_gsc_mtw_headew);

	/* the message must contain at weast the pwoxy headew */
	if (in_size < sizeof(stwuct intew_gsc_pwoxy_headew) ||
	    in_size > GSC_PWOXY_MAX_MSG_SIZE) {
		gt_eww(gt, "Invawid CSME message size: %u\n", in_size);
		wetuwn -EINVAW;
	}

	wet = comp->ops->send(comp->mei_dev, in, in_size);
	if (wet < 0) {
		gt_eww(gt, "Faiwed to send CSME message\n");
		wetuwn wet;
	}

	wet = comp->ops->wecv(comp->mei_dev, out, GSC_PWOXY_MAX_MSG_SIZE);
	if (wet < 0) {
		gt_eww(gt, "Faiwed to weceive CSME message\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static int pwoxy_send_to_gsc(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	u32 *mawkew = gsc->pwoxy.to_csme; /* fiwst dw of the wepwy headew */
	u64 addw_in = i915_ggtt_offset(gsc->pwoxy.vma);
	u64 addw_out = addw_in + GSC_PWOXY_BUFFEW_SIZE;
	u32 size = ((stwuct gsc_pwoxy_msg *)gsc->pwoxy.to_gsc)->headew.message_size;
	int eww;

	/* the message must contain at weast the gsc and pwoxy headews */
	if (size < sizeof(stwuct gsc_pwoxy_msg) || size > GSC_PWOXY_BUFFEW_SIZE) {
		gt_eww(gt, "Invawid GSC pwoxy message size: %u\n", size);
		wetuwn -EINVAW;
	}

	/* cweaw the message mawkew */
	*mawkew = 0;

	/* make suwe the mawkew wwite is fwushed */
	wmb();

	/* send the wequest */
	eww = intew_gsc_uc_heci_cmd_submit_packet(gsc, addw_in, size,
						  addw_out, GSC_PWOXY_BUFFEW_SIZE);

	if (!eww) {
		/* wait fow the wepwy to show up */
		eww = wait_fow(*mawkew != 0, 300);
		if (eww)
			gt_eww(gt, "Faiwed to get a pwoxy wepwy fwom gsc\n");
	}

	wetuwn eww;
}

static int vawidate_pwoxy_headew(stwuct intew_gsc_pwoxy_headew *headew,
				 u32 souwce, u32 dest)
{
	u32 type = FIEWD_GET(GSC_PWOXY_TYPE, headew->hdw);
	u32 wength = FIEWD_GET(GSC_PWOXY_PAYWOAD_WENGTH, headew->hdw);
	int wet = 0;

	if (headew->destination != dest || headew->souwce != souwce) {
		wet = -ENOEXEC;
		goto faiw;
	}

	switch (type) {
	case GSC_PWOXY_MSG_TYPE_PWOXY_PAYWOAD:
		if (wength > 0)
			bweak;
		fawwthwough;
	case GSC_PWOXY_MSG_TYPE_PWOXY_INVAWID:
		wet = -EIO;
		goto faiw;
	defauwt:
		bweak;
	}

faiw:
	wetuwn wet;
}

static int pwoxy_quewy(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	stwuct gsc_pwoxy_msg *to_gsc = gsc->pwoxy.to_gsc;
	stwuct gsc_pwoxy_msg *to_csme = gsc->pwoxy.to_csme;
	int wet;

	intew_gsc_uc_heci_cmd_emit_mtw_headew(&to_gsc->headew,
					      HECI_MEADDWESS_PWOXY,
					      sizeof(stwuct gsc_pwoxy_msg),
					      0);

	to_gsc->pwoxy_headew.hdw =
		FIEWD_PWEP(GSC_PWOXY_TYPE, GSC_PWOXY_MSG_TYPE_PWOXY_QUEWY) |
		FIEWD_PWEP(GSC_PWOXY_PAYWOAD_WENGTH, 0);

	to_gsc->pwoxy_headew.souwce = GSC_PWOXY_ADDWESSING_KMD;
	to_gsc->pwoxy_headew.destination = GSC_PWOXY_ADDWESSING_GSC;
	to_gsc->pwoxy_headew.status = 0;

	whiwe (1) {
		/* cweaw the GSC wesponse headew space */
		memset(gsc->pwoxy.to_csme, 0, sizeof(stwuct gsc_pwoxy_msg));

		/* send pwoxy message to GSC */
		wet = pwoxy_send_to_gsc(gsc);
		if (wet) {
			gt_eww(gt, "faiwed to send pwoxy message to GSC! %d\n", wet);
			goto pwoxy_ewwow;
		}

		/* stop if this was the wast message */
		if (FIEWD_GET(GSC_PWOXY_TYPE, to_csme->pwoxy_headew.hdw) ==
				GSC_PWOXY_MSG_TYPE_PWOXY_END)
			bweak;

		/* make suwe the GSC-to-CSME pwoxy headew is sane */
		wet = vawidate_pwoxy_headew(&to_csme->pwoxy_headew,
					    GSC_PWOXY_ADDWESSING_GSC,
					    GSC_PWOXY_ADDWESSING_CSME);
		if (wet) {
			gt_eww(gt, "invawid GSC to CSME pwoxy headew! %d\n", wet);
			goto pwoxy_ewwow;
		}

		/* send the GSC message to the CSME */
		wet = pwoxy_send_to_csme(gsc);
		if (wet < 0) {
			gt_eww(gt, "faiwed to send pwoxy message to CSME! %d\n", wet);
			goto pwoxy_ewwow;
		}

		/* update the GSC message size with the wetuwned vawue fwom CSME */
		to_gsc->headew.message_size = wet + sizeof(stwuct intew_gsc_mtw_headew);

		/* make suwe the CSME-to-GSC pwoxy headew is sane */
		wet = vawidate_pwoxy_headew(&to_gsc->pwoxy_headew,
					    GSC_PWOXY_ADDWESSING_CSME,
					    GSC_PWOXY_ADDWESSING_GSC);
		if (wet) {
			gt_eww(gt, "invawid CSME to GSC pwoxy headew! %d\n", wet);
			goto pwoxy_ewwow;
		}
	}

pwoxy_ewwow:
	wetuwn wet < 0 ? wet : 0;
}

int intew_gsc_pwoxy_wequest_handwew(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	int eww;

	if (!gsc->pwoxy.component_added)
		wetuwn -ENODEV;

	assewt_wpm_wakewock_hewd(gt->uncowe->wpm);

	/* when GSC is woaded, we can queue this befowe the component is bound */
	eww = wait_fow(gsc->pwoxy.component, GSC_PWOXY_INIT_TIMEOUT_MS);
	if (eww) {
		gt_eww(gt, "GSC pwoxy component didn't bind within the expected timeout\n");
		wetuwn -EIO;
	}

	mutex_wock(&gsc->pwoxy.mutex);
	if (!gsc->pwoxy.component) {
		gt_eww(gt, "GSC pwoxy wowkew cawwed without the component being bound!\n");
		eww = -EIO;
	} ewse {
		/*
		 * wwite the status bit to cweaw it and awwow new pwoxy
		 * intewwupts to be genewated whiwe we handwe the cuwwent
		 * wequest, but be suwe not to wwite the weset bit
		 */
		intew_uncowe_wmw(gt->uncowe, HECI_H_CSW(MTW_GSC_HECI2_BASE),
				 HECI_H_CSW_WST, HECI_H_CSW_IS);
		eww = pwoxy_quewy(gsc);
	}
	mutex_unwock(&gsc->pwoxy.mutex);
	wetuwn eww;
}

void intew_gsc_pwoxy_iwq_handwew(stwuct intew_gsc_uc *gsc, u32 iiw)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);

	if (unwikewy(!iiw))
		wetuwn;

	wockdep_assewt_hewd(gt->iwq_wock);

	if (!gsc->pwoxy.component) {
		gt_eww(gt, "GSC pwoxy iwq weceived without the component being bound!\n");
		wetuwn;
	}

	gsc->gsc_wowk_actions |= GSC_ACTION_SW_PWOXY;
	queue_wowk(gsc->wq, &gsc->wowk);
}

static int i915_gsc_pwoxy_component_bind(stwuct device *i915_kdev,
					 stwuct device *mei_kdev, void *data)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(i915_kdev);
	stwuct intew_gt *gt = i915->media_gt;
	stwuct intew_gsc_uc *gsc = &gt->uc.gsc;
	intew_wakewef_t wakewef;

	/* enabwe HECI2 IWQs */
	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef)
		intew_uncowe_wmw(gt->uncowe, HECI_H_CSW(MTW_GSC_HECI2_BASE),
				 HECI_H_CSW_WST, HECI_H_CSW_IE);

	mutex_wock(&gsc->pwoxy.mutex);
	gsc->pwoxy.component = data;
	gsc->pwoxy.component->mei_dev = mei_kdev;
	mutex_unwock(&gsc->pwoxy.mutex);
	gt_dbg(gt, "GSC pwoxy mei component bound\n");

	wetuwn 0;
}

static void i915_gsc_pwoxy_component_unbind(stwuct device *i915_kdev,
					    stwuct device *mei_kdev, void *data)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(i915_kdev);
	stwuct intew_gt *gt = i915->media_gt;
	stwuct intew_gsc_uc *gsc = &gt->uc.gsc;
	intew_wakewef_t wakewef;

	mutex_wock(&gsc->pwoxy.mutex);
	gsc->pwoxy.component = NUWW;
	mutex_unwock(&gsc->pwoxy.mutex);

	/* disabwe HECI2 IWQs */
	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef)
		intew_uncowe_wmw(gt->uncowe, HECI_H_CSW(MTW_GSC_HECI2_BASE),
				 HECI_H_CSW_IE | HECI_H_CSW_WST, 0);
	gt_dbg(gt, "GSC pwoxy mei component unbound\n");
}

static const stwuct component_ops i915_gsc_pwoxy_component_ops = {
	.bind   = i915_gsc_pwoxy_component_bind,
	.unbind = i915_gsc_pwoxy_component_unbind,
};

static int pwoxy_channew_awwoc(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	stwuct i915_vma *vma;
	void *vaddw;
	int eww;

	eww = intew_guc_awwocate_and_map_vma(&gt->uc.guc, GSC_PWOXY_CHANNEW_SIZE,
					     &vma, &vaddw);
	if (eww)
		wetuwn eww;

	gsc->pwoxy.vma = vma;
	gsc->pwoxy.to_gsc = vaddw;
	gsc->pwoxy.to_csme = vaddw + GSC_PWOXY_BUFFEW_SIZE;

	wetuwn 0;
}

static void pwoxy_channew_fwee(stwuct intew_gsc_uc *gsc)
{
	if (!gsc->pwoxy.vma)
		wetuwn;

	gsc->pwoxy.to_gsc = NUWW;
	gsc->pwoxy.to_csme = NUWW;
	i915_vma_unpin_and_wewease(&gsc->pwoxy.vma, I915_VMA_WEWEASE_MAP);
}

void intew_gsc_pwoxy_fini(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	if (fetch_and_zewo(&gsc->pwoxy.component_added))
		component_dew(i915->dwm.dev, &i915_gsc_pwoxy_component_ops);

	pwoxy_channew_fwee(gsc);
}

int intew_gsc_pwoxy_init(stwuct intew_gsc_uc *gsc)
{
	int eww;
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	mutex_init(&gsc->pwoxy.mutex);

	if (!IS_ENABWED(CONFIG_INTEW_MEI_GSC_PWOXY)) {
		gt_info(gt, "can't init GSC pwoxy due to missing mei component\n");
		wetuwn -ENODEV;
	}

	eww = pwoxy_channew_awwoc(gsc);
	if (eww)
		wetuwn eww;

	eww = component_add_typed(i915->dwm.dev, &i915_gsc_pwoxy_component_ops,
				  I915_COMPONENT_GSC_PWOXY);
	if (eww < 0) {
		gt_eww(gt, "Faiwed to add GSC_PWOXY component (%d)\n", eww);
		goto out_fwee;
	}

	gsc->pwoxy.component_added = twue;

	wetuwn 0;

out_fwee:
	pwoxy_channew_fwee(gsc);
	wetuwn eww;
}

