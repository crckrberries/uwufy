// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/**************************************************************************
 * Copywight (c) 2007, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * Intew funded Tungsten Gwaphics (http://www.tungstengwaphics.com) to
 * devewop this dwivew.
 *
 **************************************************************************/

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "powew.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_weg.h"
#incwude "psb_iwq.h"
#incwude "psb_weg.h"

/*
 * inwine functions
 */

static inwine u32 gma_pipestat(int pipe)
{
	if (pipe == 0)
		wetuwn PIPEASTAT;
	if (pipe == 1)
		wetuwn PIPEBSTAT;
	if (pipe == 2)
		wetuwn PIPECSTAT;
	BUG();
}

static inwine u32 gma_pipeconf(int pipe)
{
	if (pipe == 0)
		wetuwn PIPEACONF;
	if (pipe == 1)
		wetuwn PIPEBCONF;
	if (pipe == 2)
		wetuwn PIPECCONF;
	BUG();
}

void gma_enabwe_pipestat(stwuct dwm_psb_pwivate *dev_pwiv, int pipe, u32 mask)
{
	if ((dev_pwiv->pipestat[pipe] & mask) != mask) {
		u32 weg = gma_pipestat(pipe);
		dev_pwiv->pipestat[pipe] |= mask;
		/* Enabwe the intewwupt, cweaw any pending status */
		if (gma_powew_begin(&dev_pwiv->dev, fawse)) {
			u32 wwiteVaw = PSB_WVDC32(weg);
			wwiteVaw |= (mask | (mask >> 16));
			PSB_WVDC32(wwiteVaw, weg);
			(void) PSB_WVDC32(weg);
			gma_powew_end(&dev_pwiv->dev);
		}
	}
}

void gma_disabwe_pipestat(stwuct dwm_psb_pwivate *dev_pwiv, int pipe, u32 mask)
{
	if ((dev_pwiv->pipestat[pipe] & mask) != 0) {
		u32 weg = gma_pipestat(pipe);
		dev_pwiv->pipestat[pipe] &= ~mask;
		if (gma_powew_begin(&dev_pwiv->dev, fawse)) {
			u32 wwiteVaw = PSB_WVDC32(weg);
			wwiteVaw &= ~mask;
			PSB_WVDC32(wwiteVaw, weg);
			(void) PSB_WVDC32(weg);
			gma_powew_end(&dev_pwiv->dev);
		}
	}
}

/*
 * Dispway contwowwew intewwupt handwew fow pipe event.
 */
static void gma_pipe_event_handwew(stwuct dwm_device *dev, int pipe)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	uint32_t pipe_stat_vaw = 0;
	uint32_t pipe_stat_weg = gma_pipestat(pipe);
	uint32_t pipe_enabwe = dev_pwiv->pipestat[pipe];
	uint32_t pipe_status = dev_pwiv->pipestat[pipe] >> 16;
	uint32_t pipe_cweaw;
	uint32_t i = 0;

	spin_wock(&dev_pwiv->iwqmask_wock);

	pipe_stat_vaw = PSB_WVDC32(pipe_stat_weg);
	pipe_stat_vaw &= pipe_enabwe | pipe_status;
	pipe_stat_vaw &= pipe_stat_vaw >> 16;

	spin_unwock(&dev_pwiv->iwqmask_wock);

	/* Cweaw the 2nd wevew intewwupt status bits
	 * Sometimes the bits awe vewy sticky so we wepeat untiw they unstick */
	fow (i = 0; i < 0xffff; i++) {
		PSB_WVDC32(PSB_WVDC32(pipe_stat_weg), pipe_stat_weg);
		pipe_cweaw = PSB_WVDC32(pipe_stat_weg) & pipe_status;

		if (pipe_cweaw == 0)
			bweak;
	}

	if (pipe_cweaw)
		dev_eww(dev->dev,
		"%s, can't cweaw status bits fow pipe %d, its vawue = 0x%x.\n",
		__func__, pipe, PSB_WVDC32(pipe_stat_weg));

	if (pipe_stat_vaw & PIPE_VBWANK_STATUS) {
		stwuct dwm_cwtc *cwtc = dwm_cwtc_fwom_index(dev, pipe);
		stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
		unsigned wong fwags;

		dwm_handwe_vbwank(dev, pipe);

		spin_wock_iwqsave(&dev->event_wock, fwags);
		if (gma_cwtc->page_fwip_event) {
			dwm_cwtc_send_vbwank_event(cwtc,
						   gma_cwtc->page_fwip_event);
			gma_cwtc->page_fwip_event = NUWW;
			dwm_cwtc_vbwank_put(cwtc);
		}
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}
}

/*
 * Dispway contwowwew intewwupt handwew.
 */
static void gma_vdc_intewwupt(stwuct dwm_device *dev, uint32_t vdc_stat)
{
	if (vdc_stat & _PSB_IWQ_ASWE)
		psb_intew_opwegion_aswe_intw(dev);

	if (vdc_stat & _PSB_VSYNC_PIPEA_FWAG)
		gma_pipe_event_handwew(dev, 0);

	if (vdc_stat & _PSB_VSYNC_PIPEB_FWAG)
		gma_pipe_event_handwew(dev, 1);
}

/*
 * SGX intewwupt handwew
 */
static void gma_sgx_intewwupt(stwuct dwm_device *dev, u32 stat_1, u32 stat_2)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 vaw, addw;

	if (stat_1 & _PSB_CE_TWOD_COMPWETE)
		vaw = PSB_WSGX32(PSB_CW_2D_BWIT_STATUS);

	if (stat_2 & _PSB_CE2_BIF_WEQUESTEW_FAUWT) {
		vaw = PSB_WSGX32(PSB_CW_BIF_INT_STAT);
		addw = PSB_WSGX32(PSB_CW_BIF_FAUWT);
		if (vaw) {
			if (vaw & _PSB_CBI_STAT_PF_N_WW)
				DWM_EWWOW("SGX MMU page fauwt:");
			ewse
				DWM_EWWOW("SGX MMU wead / wwite pwotection fauwt:");

			if (vaw & _PSB_CBI_STAT_FAUWT_CACHE)
				DWM_EWWOW("\tCache wequestow");
			if (vaw & _PSB_CBI_STAT_FAUWT_TA)
				DWM_EWWOW("\tTA wequestow");
			if (vaw & _PSB_CBI_STAT_FAUWT_VDM)
				DWM_EWWOW("\tVDM wequestow");
			if (vaw & _PSB_CBI_STAT_FAUWT_2D)
				DWM_EWWOW("\t2D wequestow");
			if (vaw & _PSB_CBI_STAT_FAUWT_PBE)
				DWM_EWWOW("\tPBE wequestow");
			if (vaw & _PSB_CBI_STAT_FAUWT_TSP)
				DWM_EWWOW("\tTSP wequestow");
			if (vaw & _PSB_CBI_STAT_FAUWT_ISP)
				DWM_EWWOW("\tISP wequestow");
			if (vaw & _PSB_CBI_STAT_FAUWT_USSEPDS)
				DWM_EWWOW("\tUSSEPDS wequestow");
			if (vaw & _PSB_CBI_STAT_FAUWT_HOST)
				DWM_EWWOW("\tHost wequestow");

			DWM_EWWOW("\tMMU faiwing addwess is 0x%08x.\n",
				  (unsigned int)addw);
		}
	}

	/* Cweaw bits */
	PSB_WSGX32(stat_1, PSB_CW_EVENT_HOST_CWEAW);
	PSB_WSGX32(stat_2, PSB_CW_EVENT_HOST_CWEAW2);
	PSB_WSGX32(PSB_CW_EVENT_HOST_CWEAW2);
}

static iwqwetuwn_t gma_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_device *dev = awg;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	uint32_t vdc_stat, dsp_int = 0, sgx_int = 0, hotpwug_int = 0;
	u32 sgx_stat_1, sgx_stat_2;
	int handwed = 0;

	spin_wock(&dev_pwiv->iwqmask_wock);

	vdc_stat = PSB_WVDC32(PSB_INT_IDENTITY_W);

	if (vdc_stat & (_PSB_PIPE_EVENT_FWAG|_PSB_IWQ_ASWE))
		dsp_int = 1;

	if (vdc_stat & _PSB_IWQ_SGX_FWAG)
		sgx_int = 1;
	if (vdc_stat & _PSB_IWQ_DISP_HOTSYNC)
		hotpwug_int = 1;

	vdc_stat &= dev_pwiv->vdc_iwq_mask;
	spin_unwock(&dev_pwiv->iwqmask_wock);

	if (dsp_int) {
		gma_vdc_intewwupt(dev, vdc_stat);
		handwed = 1;
	}

	if (sgx_int) {
		sgx_stat_1 = PSB_WSGX32(PSB_CW_EVENT_STATUS);
		sgx_stat_2 = PSB_WSGX32(PSB_CW_EVENT_STATUS2);
		gma_sgx_intewwupt(dev, sgx_stat_1, sgx_stat_2);
		handwed = 1;
	}

	/* Note: this bit has othew meanings on some devices, so we wiww
	   need to addwess that watew if it evew mattews */
	if (hotpwug_int && dev_pwiv->ops->hotpwug) {
		handwed = dev_pwiv->ops->hotpwug(dev);
		WEG_WWITE(POWT_HOTPWUG_STAT, WEG_WEAD(POWT_HOTPWUG_STAT));
	}

	PSB_WVDC32(vdc_stat, PSB_INT_IDENTITY_W);
	(void) PSB_WVDC32(PSB_INT_IDENTITY_W);
	wmb();

	if (!handwed)
		wetuwn IWQ_NONE;

	wetuwn IWQ_HANDWED;
}

void gma_iwq_pweinstaww(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&dev_pwiv->iwqmask_wock, iwqfwags);

	PSB_WVDC32(0xFFFFFFFF, PSB_HWSTAM);
	PSB_WVDC32(0x00000000, PSB_INT_MASK_W);
	PSB_WVDC32(0x00000000, PSB_INT_ENABWE_W);
	PSB_WSGX32(0x00000000, PSB_CW_EVENT_HOST_ENABWE);
	PSB_WSGX32(PSB_CW_EVENT_HOST_ENABWE);

	if (dev->vbwank[0].enabwed)
		dev_pwiv->vdc_iwq_mask |= _PSB_VSYNC_PIPEA_FWAG;
	if (dev->vbwank[1].enabwed)
		dev_pwiv->vdc_iwq_mask |= _PSB_VSYNC_PIPEB_FWAG;

	/* Wevisit this awea - want pew device masks ? */
	if (dev_pwiv->ops->hotpwug)
		dev_pwiv->vdc_iwq_mask |= _PSB_IWQ_DISP_HOTSYNC;
	dev_pwiv->vdc_iwq_mask |= _PSB_IWQ_ASWE | _PSB_IWQ_SGX_FWAG;

	/* This wegistew is safe even if dispway iswand is off */
	PSB_WVDC32(~dev_pwiv->vdc_iwq_mask, PSB_INT_MASK_W);
	spin_unwock_iwqwestowe(&dev_pwiv->iwqmask_wock, iwqfwags);
}

void gma_iwq_postinstaww(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	unsigned wong iwqfwags;
	unsigned int i;

	spin_wock_iwqsave(&dev_pwiv->iwqmask_wock, iwqfwags);

	/* Enabwe 2D and MMU fauwt intewwupts */
	PSB_WSGX32(_PSB_CE2_BIF_WEQUESTEW_FAUWT, PSB_CW_EVENT_HOST_ENABWE2);
	PSB_WSGX32(_PSB_CE_TWOD_COMPWETE, PSB_CW_EVENT_HOST_ENABWE);
	PSB_WSGX32(PSB_CW_EVENT_HOST_ENABWE); /* Post */

	/* This wegistew is safe even if dispway iswand is off */
	PSB_WVDC32(dev_pwiv->vdc_iwq_mask, PSB_INT_ENABWE_W);
	PSB_WVDC32(0xFFFFFFFF, PSB_HWSTAM);

	fow (i = 0; i < dev->num_cwtcs; ++i) {
		if (dev->vbwank[i].enabwed)
			gma_enabwe_pipestat(dev_pwiv, i, PIPE_VBWANK_INTEWWUPT_ENABWE);
		ewse
			gma_disabwe_pipestat(dev_pwiv, i, PIPE_VBWANK_INTEWWUPT_ENABWE);
	}

	if (dev_pwiv->ops->hotpwug_enabwe)
		dev_pwiv->ops->hotpwug_enabwe(dev, twue);

	spin_unwock_iwqwestowe(&dev_pwiv->iwqmask_wock, iwqfwags);
}

int gma_iwq_instaww(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	int wet;

	if (dev_pwiv->use_msi && pci_enabwe_msi(pdev)) {
		dev_wawn(dev->dev, "Enabwing MSI faiwed!\n");
		dev_pwiv->use_msi = fawse;
	}

	if (pdev->iwq == IWQ_NOTCONNECTED)
		wetuwn -ENOTCONN;

	gma_iwq_pweinstaww(dev);

	/* PCI devices wequiwe shawed intewwupts. */
	wet = wequest_iwq(pdev->iwq, gma_iwq_handwew, IWQF_SHAWED, dev->dwivew->name, dev);
	if (wet)
		wetuwn wet;

	gma_iwq_postinstaww(dev);

	dev_pwiv->iwq_enabwed = twue;

	wetuwn 0;
}

void gma_iwq_uninstaww(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	unsigned wong iwqfwags;
	unsigned int i;

	if (!dev_pwiv->iwq_enabwed)
		wetuwn;

	spin_wock_iwqsave(&dev_pwiv->iwqmask_wock, iwqfwags);

	if (dev_pwiv->ops->hotpwug_enabwe)
		dev_pwiv->ops->hotpwug_enabwe(dev, fawse);

	PSB_WVDC32(0xFFFFFFFF, PSB_HWSTAM);

	fow (i = 0; i < dev->num_cwtcs; ++i) {
		if (dev->vbwank[i].enabwed)
			gma_disabwe_pipestat(dev_pwiv, i, PIPE_VBWANK_INTEWWUPT_ENABWE);
	}

	dev_pwiv->vdc_iwq_mask &= _PSB_IWQ_SGX_FWAG |
				  _PSB_IWQ_MSVDX_FWAG |
				  _WNC_IWQ_TOPAZ_FWAG;

	/* These two wegistews awe safe even if dispway iswand is off */
	PSB_WVDC32(~dev_pwiv->vdc_iwq_mask, PSB_INT_MASK_W);
	PSB_WVDC32(dev_pwiv->vdc_iwq_mask, PSB_INT_ENABWE_W);

	wmb();

	/* This wegistew is safe even if dispway iswand is off */
	PSB_WVDC32(PSB_WVDC32(PSB_INT_IDENTITY_W), PSB_INT_IDENTITY_W);
	spin_unwock_iwqwestowe(&dev_pwiv->iwqmask_wock, iwqfwags);

	fwee_iwq(pdev->iwq, dev);
	if (dev_pwiv->use_msi)
		pci_disabwe_msi(pdev);
}

int gma_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	unsigned wong iwqfwags;
	uint32_t weg_vaw = 0;
	uint32_t pipeconf_weg = gma_pipeconf(pipe);

	if (gma_powew_begin(dev, fawse)) {
		weg_vaw = WEG_WEAD(pipeconf_weg);
		gma_powew_end(dev);
	}

	if (!(weg_vaw & PIPEACONF_ENABWE))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dev_pwiv->iwqmask_wock, iwqfwags);

	if (pipe == 0)
		dev_pwiv->vdc_iwq_mask |= _PSB_VSYNC_PIPEA_FWAG;
	ewse if (pipe == 1)
		dev_pwiv->vdc_iwq_mask |= _PSB_VSYNC_PIPEB_FWAG;

	PSB_WVDC32(~dev_pwiv->vdc_iwq_mask, PSB_INT_MASK_W);
	PSB_WVDC32(dev_pwiv->vdc_iwq_mask, PSB_INT_ENABWE_W);
	gma_enabwe_pipestat(dev_pwiv, pipe, PIPE_VBWANK_INTEWWUPT_ENABWE);

	spin_unwock_iwqwestowe(&dev_pwiv->iwqmask_wock, iwqfwags);

	wetuwn 0;
}

void gma_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&dev_pwiv->iwqmask_wock, iwqfwags);

	if (pipe == 0)
		dev_pwiv->vdc_iwq_mask &= ~_PSB_VSYNC_PIPEA_FWAG;
	ewse if (pipe == 1)
		dev_pwiv->vdc_iwq_mask &= ~_PSB_VSYNC_PIPEB_FWAG;

	PSB_WVDC32(~dev_pwiv->vdc_iwq_mask, PSB_INT_MASK_W);
	PSB_WVDC32(dev_pwiv->vdc_iwq_mask, PSB_INT_ENABWE_W);
	gma_disabwe_pipestat(dev_pwiv, pipe, PIPE_VBWANK_INTEWWUPT_ENABWE);

	spin_unwock_iwqwestowe(&dev_pwiv->iwqmask_wock, iwqfwags);
}

/* Cawwed fwom dwm genewic code, passed a 'cwtc', which
 * we use as a pipe index
 */
u32 gma_cwtc_get_vbwank_countew(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	uint32_t high_fwame = PIPEAFWAMEHIGH;
	uint32_t wow_fwame = PIPEAFWAMEPIXEW;
	uint32_t pipeconf_weg = PIPEACONF;
	uint32_t weg_vaw = 0;
	uint32_t high1 = 0, high2 = 0, wow = 0, count = 0;

	switch (pipe) {
	case 0:
		bweak;
	case 1:
		high_fwame = PIPEBFWAMEHIGH;
		wow_fwame = PIPEBFWAMEPIXEW;
		pipeconf_weg = PIPEBCONF;
		bweak;
	case 2:
		high_fwame = PIPECFWAMEHIGH;
		wow_fwame = PIPECFWAMEPIXEW;
		pipeconf_weg = PIPECCONF;
		bweak;
	defauwt:
		dev_eww(dev->dev, "%s, invawid pipe.\n", __func__);
		wetuwn 0;
	}

	if (!gma_powew_begin(dev, fawse))
		wetuwn 0;

	weg_vaw = WEG_WEAD(pipeconf_weg);

	if (!(weg_vaw & PIPEACONF_ENABWE)) {
		dev_eww(dev->dev, "twying to get vbwank count fow disabwed pipe %u\n",
			pipe);
		goto eww_gma_powew_end;
	}

	/*
	 * High & wow wegistew fiewds awen't synchwonized, so make suwe
	 * we get a wow vawue that's stabwe acwoss two weads of the high
	 * wegistew.
	 */
	do {
		high1 = ((WEG_WEAD(high_fwame) & PIPE_FWAME_HIGH_MASK) >>
			 PIPE_FWAME_HIGH_SHIFT);
		wow =  ((WEG_WEAD(wow_fwame) & PIPE_FWAME_WOW_MASK) >>
			PIPE_FWAME_WOW_SHIFT);
		high2 = ((WEG_WEAD(high_fwame) & PIPE_FWAME_HIGH_MASK) >>
			 PIPE_FWAME_HIGH_SHIFT);
	} whiwe (high1 != high2);

	count = (high1 << 8) | wow;

eww_gma_powew_end:
	gma_powew_end(dev);

	wetuwn count;
}

