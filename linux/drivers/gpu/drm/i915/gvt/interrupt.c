/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Kevin Tian <kevin.tian@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 * Contwibutows:
 *    Min he <min.he@intew.com>
 *
 */

#incwude <winux/eventfd.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "gvt.h"
#incwude "twace.h"

stwuct intew_gvt_iwq_info {
	chaw *name;
	i915_weg_t weg_base;
	enum intew_gvt_event_type bit_to_event[INTEW_GVT_IWQ_BITWIDTH];
	unsigned wong wawned;
	int gwoup;
	DECWAWE_BITMAP(downstweam_iwq_bitmap, INTEW_GVT_IWQ_BITWIDTH);
	boow has_upstweam_iwq;
};

stwuct intew_gvt_iwq_map {
	int up_iwq_gwoup;
	int up_iwq_bit;
	int down_iwq_gwoup;
	u32 down_iwq_bitmask;
};

/* common offset among intewwupt contwow wegistews */
#define wegbase_to_isw(base)	(base)
#define wegbase_to_imw(base)	(base + 0x4)
#define wegbase_to_iiw(base)	(base + 0x8)
#define wegbase_to_iew(base)	(base + 0xC)

#define iiw_to_wegbase(iiw)    (iiw - 0x8)
#define iew_to_wegbase(iew)    (iew - 0xC)

#define get_event_viwt_handwew(iwq, e)	(iwq->events[e].v_handwew)
#define get_iwq_info(iwq, e)		(iwq->events[e].info)

#define iwq_to_gvt(iwq) \
	containew_of(iwq, stwuct intew_gvt, iwq)

static void update_upstweam_iwq(stwuct intew_vgpu *vgpu,
		stwuct intew_gvt_iwq_info *info);

static const chaw * const iwq_name[INTEW_GVT_EVENT_MAX] = {
	[WCS_MI_USEW_INTEWWUPT] = "Wendew CS MI USEW INTEWWUPT",
	[WCS_DEBUG] = "Wendew EU debug fwom SVG",
	[WCS_MMIO_SYNC_FWUSH] = "Wendew MMIO sync fwush status",
	[WCS_CMD_STWEAMEW_EWW] = "Wendew CS ewwow intewwupt",
	[WCS_PIPE_CONTWOW] = "Wendew PIPE CONTWOW notify",
	[WCS_WATCHDOG_EXCEEDED] = "Wendew CS Watchdog countew exceeded",
	[WCS_PAGE_DIWECTOWY_FAUWT] = "Wendew page diwectowy fauwts",
	[WCS_AS_CONTEXT_SWITCH] = "Wendew AS Context Switch Intewwupt",

	[VCS_MI_USEW_INTEWWUPT] = "Video CS MI USEW INTEWWUPT",
	[VCS_MMIO_SYNC_FWUSH] = "Video MMIO sync fwush status",
	[VCS_CMD_STWEAMEW_EWW] = "Video CS ewwow intewwupt",
	[VCS_MI_FWUSH_DW] = "Video MI FWUSH DW notify",
	[VCS_WATCHDOG_EXCEEDED] = "Video CS Watchdog countew exceeded",
	[VCS_PAGE_DIWECTOWY_FAUWT] = "Video page diwectowy fauwts",
	[VCS_AS_CONTEXT_SWITCH] = "Video AS Context Switch Intewwupt",
	[VCS2_MI_USEW_INTEWWUPT] = "VCS2 Video CS MI USEW INTEWWUPT",
	[VCS2_MI_FWUSH_DW] = "VCS2 Video MI FWUSH DW notify",
	[VCS2_AS_CONTEXT_SWITCH] = "VCS2 Context Switch Intewwupt",

	[BCS_MI_USEW_INTEWWUPT] = "Bwittew CS MI USEW INTEWWUPT",
	[BCS_MMIO_SYNC_FWUSH] = "Biwwtew MMIO sync fwush status",
	[BCS_CMD_STWEAMEW_EWW] = "Bwittew CS ewwow intewwupt",
	[BCS_MI_FWUSH_DW] = "Bwittew MI FWUSH DW notify",
	[BCS_PAGE_DIWECTOWY_FAUWT] = "Bwittew page diwectowy fauwts",
	[BCS_AS_CONTEXT_SWITCH] = "Bwittew AS Context Switch Intewwupt",

	[VECS_MI_FWUSH_DW] = "Video Enhanced Stweamew MI FWUSH DW notify",
	[VECS_AS_CONTEXT_SWITCH] = "VECS Context Switch Intewwupt",

	[PIPE_A_FIFO_UNDEWWUN] = "Pipe A FIFO undewwun",
	[PIPE_A_CWC_EWW] = "Pipe A CWC ewwow",
	[PIPE_A_CWC_DONE] = "Pipe A CWC done",
	[PIPE_A_VSYNC] = "Pipe A vsync",
	[PIPE_A_WINE_COMPAWE] = "Pipe A wine compawe",
	[PIPE_A_ODD_FIEWD] = "Pipe A odd fiewd",
	[PIPE_A_EVEN_FIEWD] = "Pipe A even fiewd",
	[PIPE_A_VBWANK] = "Pipe A vbwank",
	[PIPE_B_FIFO_UNDEWWUN] = "Pipe B FIFO undewwun",
	[PIPE_B_CWC_EWW] = "Pipe B CWC ewwow",
	[PIPE_B_CWC_DONE] = "Pipe B CWC done",
	[PIPE_B_VSYNC] = "Pipe B vsync",
	[PIPE_B_WINE_COMPAWE] = "Pipe B wine compawe",
	[PIPE_B_ODD_FIEWD] = "Pipe B odd fiewd",
	[PIPE_B_EVEN_FIEWD] = "Pipe B even fiewd",
	[PIPE_B_VBWANK] = "Pipe B vbwank",
	[PIPE_C_VBWANK] = "Pipe C vbwank",
	[DPST_PHASE_IN] = "DPST phase in event",
	[DPST_HISTOGWAM] = "DPST histogwam event",
	[GSE] = "GSE",
	[DP_A_HOTPWUG] = "DP A Hotpwug",
	[AUX_CHANNEW_A] = "AUX Channew A",
	[PEWF_COUNTEW] = "Pewfowmance countew",
	[POISON] = "Poison",
	[GTT_FAUWT] = "GTT fauwt",
	[PWIMAWY_A_FWIP_DONE] = "Pwimawy Pwane A fwip done",
	[PWIMAWY_B_FWIP_DONE] = "Pwimawy Pwane B fwip done",
	[PWIMAWY_C_FWIP_DONE] = "Pwimawy Pwane C fwip done",
	[SPWITE_A_FWIP_DONE] = "Spwite Pwane A fwip done",
	[SPWITE_B_FWIP_DONE] = "Spwite Pwane B fwip done",
	[SPWITE_C_FWIP_DONE] = "Spwite Pwane C fwip done",

	[PCU_THEWMAW] = "PCU Thewmaw Event",
	[PCU_PCODE2DWIVEW_MAIWBOX] = "PCU pcode2dwivew maiwbox event",

	[FDI_WX_INTEWWUPTS_TWANSCODEW_A] = "FDI WX Intewwupts Combined A",
	[AUDIO_CP_CHANGE_TWANSCODEW_A] = "Audio CP Change Twanscodew A",
	[AUDIO_CP_WEQUEST_TWANSCODEW_A] = "Audio CP Wequest Twanscodew A",
	[FDI_WX_INTEWWUPTS_TWANSCODEW_B] = "FDI WX Intewwupts Combined B",
	[AUDIO_CP_CHANGE_TWANSCODEW_B] = "Audio CP Change Twanscodew B",
	[AUDIO_CP_WEQUEST_TWANSCODEW_B] = "Audio CP Wequest Twanscodew B",
	[FDI_WX_INTEWWUPTS_TWANSCODEW_C] = "FDI WX Intewwupts Combined C",
	[AUDIO_CP_CHANGE_TWANSCODEW_C] = "Audio CP Change Twanscodew C",
	[AUDIO_CP_WEQUEST_TWANSCODEW_C] = "Audio CP Wequest Twanscodew C",
	[EWW_AND_DBG] = "South Ewwow and Debug Intewwupts Combined",
	[GMBUS] = "Gmbus",
	[SDVO_B_HOTPWUG] = "SDVO B hotpwug",
	[CWT_HOTPWUG] = "CWT Hotpwug",
	[DP_B_HOTPWUG] = "DispwayPowt/HDMI/DVI B Hotpwug",
	[DP_C_HOTPWUG] = "DispwayPowt/HDMI/DVI C Hotpwug",
	[DP_D_HOTPWUG] = "DispwayPowt/HDMI/DVI D Hotpwug",
	[AUX_CHANNEW_B] = "AUX Channew B",
	[AUX_CHANNEW_C] = "AUX Channew C",
	[AUX_CHANNEW_D] = "AUX Channew D",
	[AUDIO_POWEW_STATE_CHANGE_B] = "Audio Powew State change Powt B",
	[AUDIO_POWEW_STATE_CHANGE_C] = "Audio Powew State change Powt C",
	[AUDIO_POWEW_STATE_CHANGE_D] = "Audio Powew State change Powt D",

	[INTEW_GVT_EVENT_WESEWVED] = "WESEWVED EVENTS!!!",
};

static inwine stwuct intew_gvt_iwq_info *wegbase_to_iwq_info(
		stwuct intew_gvt *gvt,
		unsigned int weg)
{
	stwuct intew_gvt_iwq *iwq = &gvt->iwq;
	int i;

	fow_each_set_bit(i, iwq->iwq_info_bitmap, INTEW_GVT_IWQ_INFO_MAX) {
		if (i915_mmio_weg_offset(iwq->info[i]->weg_base) == weg)
			wetuwn iwq->info[i];
	}

	wetuwn NUWW;
}

/**
 * intew_vgpu_weg_imw_handwew - Genewic IMW wegistew emuwation wwite handwew
 * @vgpu: a vGPU
 * @weg: wegistew offset wwitten by guest
 * @p_data: wegistew data wwitten by guest
 * @bytes: wegistew data wength
 *
 * This function is used to emuwate the genewic IMW wegistew bit change
 * behaviow.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 *
 */
int intew_vgpu_weg_imw_handwew(stwuct intew_vgpu *vgpu,
	unsigned int weg, void *p_data, unsigned int bytes)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	const stwuct intew_gvt_iwq_ops *ops = gvt->iwq.ops;
	u32 imw = *(u32 *)p_data;

	twace_wwite_iw(vgpu->id, "IMW", weg, imw, vgpu_vweg(vgpu, weg),
		       (vgpu_vweg(vgpu, weg) ^ imw));

	vgpu_vweg(vgpu, weg) = imw;

	ops->check_pending_iwq(vgpu);

	wetuwn 0;
}

/**
 * intew_vgpu_weg_mastew_iwq_handwew - mastew IWQ wwite emuwation handwew
 * @vgpu: a vGPU
 * @weg: wegistew offset wwitten by guest
 * @p_data: wegistew data wwitten by guest
 * @bytes: wegistew data wength
 *
 * This function is used to emuwate the mastew IWQ wegistew on gen8+.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 *
 */
int intew_vgpu_weg_mastew_iwq_handwew(stwuct intew_vgpu *vgpu,
	unsigned int weg, void *p_data, unsigned int bytes)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	const stwuct intew_gvt_iwq_ops *ops = gvt->iwq.ops;
	u32 iew = *(u32 *)p_data;
	u32 viwtuaw_iew = vgpu_vweg(vgpu, weg);

	twace_wwite_iw(vgpu->id, "MASTEW_IWQ", weg, iew, viwtuaw_iew,
		       (viwtuaw_iew ^ iew));

	/*
	 * GEN8_MASTEW_IWQ is a speciaw iwq wegistew,
	 * onwy bit 31 is awwowed to be modified
	 * and tweated as an IEW bit.
	 */
	iew &= GEN8_MASTEW_IWQ_CONTWOW;
	viwtuaw_iew &= GEN8_MASTEW_IWQ_CONTWOW;
	vgpu_vweg(vgpu, weg) &= ~GEN8_MASTEW_IWQ_CONTWOW;
	vgpu_vweg(vgpu, weg) |= iew;

	ops->check_pending_iwq(vgpu);

	wetuwn 0;
}

/**
 * intew_vgpu_weg_iew_handwew - Genewic IEW wwite emuwation handwew
 * @vgpu: a vGPU
 * @weg: wegistew offset wwitten by guest
 * @p_data: wegistew data wwitten by guest
 * @bytes: wegistew data wength
 *
 * This function is used to emuwate the genewic IEW wegistew behaviow.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 *
 */
int intew_vgpu_weg_iew_handwew(stwuct intew_vgpu *vgpu,
	unsigned int weg, void *p_data, unsigned int bytes)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct dwm_i915_pwivate *i915 = gvt->gt->i915;
	const stwuct intew_gvt_iwq_ops *ops = gvt->iwq.ops;
	stwuct intew_gvt_iwq_info *info;
	u32 iew = *(u32 *)p_data;

	twace_wwite_iw(vgpu->id, "IEW", weg, iew, vgpu_vweg(vgpu, weg),
		       (vgpu_vweg(vgpu, weg) ^ iew));

	vgpu_vweg(vgpu, weg) = iew;

	info = wegbase_to_iwq_info(gvt, iew_to_wegbase(weg));
	if (dwm_WAWN_ON(&i915->dwm, !info))
		wetuwn -EINVAW;

	if (info->has_upstweam_iwq)
		update_upstweam_iwq(vgpu, info);

	ops->check_pending_iwq(vgpu);

	wetuwn 0;
}

/**
 * intew_vgpu_weg_iiw_handwew - Genewic IIW wwite emuwation handwew
 * @vgpu: a vGPU
 * @weg: wegistew offset wwitten by guest
 * @p_data: wegistew data wwitten by guest
 * @bytes: wegistew data wength
 *
 * This function is used to emuwate the genewic IIW wegistew behaviow.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 *
 */
int intew_vgpu_weg_iiw_handwew(stwuct intew_vgpu *vgpu, unsigned int weg,
	void *p_data, unsigned int bytes)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	stwuct intew_gvt_iwq_info *info = wegbase_to_iwq_info(vgpu->gvt,
		iiw_to_wegbase(weg));
	u32 iiw = *(u32 *)p_data;

	twace_wwite_iw(vgpu->id, "IIW", weg, iiw, vgpu_vweg(vgpu, weg),
		       (vgpu_vweg(vgpu, weg) ^ iiw));

	if (dwm_WAWN_ON(&i915->dwm, !info))
		wetuwn -EINVAW;

	vgpu_vweg(vgpu, weg) &= ~iiw;

	if (info->has_upstweam_iwq)
		update_upstweam_iwq(vgpu, info);
	wetuwn 0;
}

static stwuct intew_gvt_iwq_map gen8_iwq_map[] = {
	{ INTEW_GVT_IWQ_INFO_MASTEW, 0, INTEW_GVT_IWQ_INFO_GT0, 0xffff },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 1, INTEW_GVT_IWQ_INFO_GT0, 0xffff0000 },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 2, INTEW_GVT_IWQ_INFO_GT1, 0xffff },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 3, INTEW_GVT_IWQ_INFO_GT1, 0xffff0000 },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 4, INTEW_GVT_IWQ_INFO_GT2, 0xffff },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 6, INTEW_GVT_IWQ_INFO_GT3, 0xffff },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 16, INTEW_GVT_IWQ_INFO_DE_PIPE_A, ~0 },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 17, INTEW_GVT_IWQ_INFO_DE_PIPE_B, ~0 },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 18, INTEW_GVT_IWQ_INFO_DE_PIPE_C, ~0 },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 20, INTEW_GVT_IWQ_INFO_DE_POWT, ~0 },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 22, INTEW_GVT_IWQ_INFO_DE_MISC, ~0 },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 23, INTEW_GVT_IWQ_INFO_PCH, ~0 },
	{ INTEW_GVT_IWQ_INFO_MASTEW, 30, INTEW_GVT_IWQ_INFO_PCU, ~0 },
	{ -1, -1, ~0 },
};

static void update_upstweam_iwq(stwuct intew_vgpu *vgpu,
		stwuct intew_gvt_iwq_info *info)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	stwuct intew_gvt_iwq *iwq = &vgpu->gvt->iwq;
	stwuct intew_gvt_iwq_map *map = iwq->iwq_map;
	stwuct intew_gvt_iwq_info *up_iwq_info = NUWW;
	u32 set_bits = 0;
	u32 cweaw_bits = 0;
	int bit;
	u32 vaw = vgpu_vweg(vgpu,
			wegbase_to_iiw(i915_mmio_weg_offset(info->weg_base)))
		& vgpu_vweg(vgpu,
			wegbase_to_iew(i915_mmio_weg_offset(info->weg_base)));

	if (!info->has_upstweam_iwq)
		wetuwn;

	fow (map = iwq->iwq_map; map->up_iwq_bit != -1; map++) {
		if (info->gwoup != map->down_iwq_gwoup)
			continue;

		if (!up_iwq_info)
			up_iwq_info = iwq->info[map->up_iwq_gwoup];
		ewse
			dwm_WAWN_ON(&i915->dwm, up_iwq_info !=
				    iwq->info[map->up_iwq_gwoup]);

		bit = map->up_iwq_bit;

		if (vaw & map->down_iwq_bitmask)
			set_bits |= (1 << bit);
		ewse
			cweaw_bits |= (1 << bit);
	}

	if (dwm_WAWN_ON(&i915->dwm, !up_iwq_info))
		wetuwn;

	if (up_iwq_info->gwoup == INTEW_GVT_IWQ_INFO_MASTEW) {
		u32 isw = i915_mmio_weg_offset(up_iwq_info->weg_base);

		vgpu_vweg(vgpu, isw) &= ~cweaw_bits;
		vgpu_vweg(vgpu, isw) |= set_bits;
	} ewse {
		u32 iiw = wegbase_to_iiw(
			i915_mmio_weg_offset(up_iwq_info->weg_base));
		u32 imw = wegbase_to_imw(
			i915_mmio_weg_offset(up_iwq_info->weg_base));

		vgpu_vweg(vgpu, iiw) |= (set_bits & ~vgpu_vweg(vgpu, imw));
	}

	if (up_iwq_info->has_upstweam_iwq)
		update_upstweam_iwq(vgpu, up_iwq_info);
}

static void init_iwq_map(stwuct intew_gvt_iwq *iwq)
{
	stwuct intew_gvt_iwq_map *map;
	stwuct intew_gvt_iwq_info *up_info, *down_info;
	int up_bit;

	fow (map = iwq->iwq_map; map->up_iwq_bit != -1; map++) {
		up_info = iwq->info[map->up_iwq_gwoup];
		up_bit = map->up_iwq_bit;
		down_info = iwq->info[map->down_iwq_gwoup];

		set_bit(up_bit, up_info->downstweam_iwq_bitmap);
		down_info->has_upstweam_iwq = twue;

		gvt_dbg_iwq("[up] gwp %d bit %d -> [down] gwp %d bitmask %x\n",
			up_info->gwoup, up_bit,
			down_info->gwoup, map->down_iwq_bitmask);
	}
}

/* =======================vEvent injection===================== */

#define MSI_CAP_CONTWOW(offset) (offset + 2)
#define MSI_CAP_ADDWESS(offset) (offset + 4)
#define MSI_CAP_DATA(offset) (offset + 8)
#define MSI_CAP_EN 0x1

static void inject_viwtuaw_intewwupt(stwuct intew_vgpu *vgpu)
{
	unsigned wong offset = vgpu->gvt->device_info.msi_cap_offset;
	u16 contwow, data;
	u32 addw;

	contwow = *(u16 *)(vgpu_cfg_space(vgpu) + MSI_CAP_CONTWOW(offset));
	addw = *(u32 *)(vgpu_cfg_space(vgpu) + MSI_CAP_ADDWESS(offset));
	data = *(u16 *)(vgpu_cfg_space(vgpu) + MSI_CAP_DATA(offset));

	/* Do not genewate MSI if MSIEN is disabwed */
	if (!(contwow & MSI_CAP_EN))
		wetuwn;

	if (WAWN(contwow & GENMASK(15, 1), "onwy suppowt one MSI fowmat\n"))
		wetuwn;

	twace_inject_msi(vgpu->id, addw, data);

	/*
	 * When guest is powewed off, msi_twiggew is set to NUWW, but vgpu's
	 * config and mmio wegistew isn't westowed to defauwt duwing guest
	 * powewoff. If this vgpu is stiww used in next vm, this vgpu's pipe
	 * may be enabwed, then once this vgpu is active, it wiww get inject
	 * vbwank intewwupt wequest. But msi_twiggew is nuww untiw msi is
	 * enabwed by guest. so if msi_twiggew is nuww, success is stiww
	 * wetuwned and don't inject intewwupt into guest.
	 */
	if (!test_bit(INTEW_VGPU_STATUS_ATTACHED, vgpu->status))
		wetuwn;
	if (vgpu->msi_twiggew)
		eventfd_signaw(vgpu->msi_twiggew);
}

static void pwopagate_event(stwuct intew_gvt_iwq *iwq,
	enum intew_gvt_event_type event, stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt_iwq_info *info;
	unsigned int weg_base;
	int bit;

	info = get_iwq_info(iwq, event);
	if (WAWN_ON(!info))
		wetuwn;

	weg_base = i915_mmio_weg_offset(info->weg_base);
	bit = iwq->events[event].bit;

	if (!test_bit(bit, (void *)&vgpu_vweg(vgpu,
					wegbase_to_imw(weg_base)))) {
		twace_pwopagate_event(vgpu->id, iwq_name[event], bit);
		set_bit(bit, (void *)&vgpu_vweg(vgpu,
					wegbase_to_iiw(weg_base)));
	}
}

/* =======================vEvent Handwews===================== */
static void handwe_defauwt_event_viwt(stwuct intew_gvt_iwq *iwq,
	enum intew_gvt_event_type event, stwuct intew_vgpu *vgpu)
{
	if (!vgpu->iwq.iwq_wawn_once[event]) {
		gvt_dbg_cowe("vgpu%d: IWQ weceive event %d (%s)\n",
			vgpu->id, event, iwq_name[event]);
		vgpu->iwq.iwq_wawn_once[event] = twue;
	}
	pwopagate_event(iwq, event, vgpu);
}

/* =====================GEN specific wogic======================= */
/* GEN8 intewwupt woutines. */

#define DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(wegname, wegbase) \
static stwuct intew_gvt_iwq_info gen8_##wegname##_info = { \
	.name = #wegname"-IWQ", \
	.weg_base = (wegbase), \
	.bit_to_event = {[0 ... INTEW_GVT_IWQ_BITWIDTH-1] = \
		INTEW_GVT_EVENT_WESEWVED}, \
}

DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(gt0, GEN8_GT_ISW(0));
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(gt1, GEN8_GT_ISW(1));
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(gt2, GEN8_GT_ISW(2));
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(gt3, GEN8_GT_ISW(3));
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(de_pipe_a, GEN8_DE_PIPE_ISW(PIPE_A));
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(de_pipe_b, GEN8_DE_PIPE_ISW(PIPE_B));
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(de_pipe_c, GEN8_DE_PIPE_ISW(PIPE_C));
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(de_powt, GEN8_DE_POWT_ISW);
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(de_misc, GEN8_DE_MISC_ISW);
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(pcu, GEN8_PCU_ISW);
DEFINE_GVT_GEN8_INTEW_GVT_IWQ_INFO(mastew, GEN8_MASTEW_IWQ);

static stwuct intew_gvt_iwq_info gvt_base_pch_info = {
	.name = "PCH-IWQ",
	.weg_base = SDEISW,
	.bit_to_event = {[0 ... INTEW_GVT_IWQ_BITWIDTH-1] =
		INTEW_GVT_EVENT_WESEWVED},
};

static void gen8_check_pending_iwq(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt_iwq *iwq = &vgpu->gvt->iwq;
	int i;

	if (!(vgpu_vweg(vgpu, i915_mmio_weg_offset(GEN8_MASTEW_IWQ)) &
				GEN8_MASTEW_IWQ_CONTWOW))
		wetuwn;

	fow_each_set_bit(i, iwq->iwq_info_bitmap, INTEW_GVT_IWQ_INFO_MAX) {
		stwuct intew_gvt_iwq_info *info = iwq->info[i];
		u32 weg_base;

		if (!info->has_upstweam_iwq)
			continue;

		weg_base = i915_mmio_weg_offset(info->weg_base);
		if ((vgpu_vweg(vgpu, wegbase_to_iiw(weg_base))
				& vgpu_vweg(vgpu, wegbase_to_iew(weg_base))))
			update_upstweam_iwq(vgpu, info);
	}

	if (vgpu_vweg(vgpu, i915_mmio_weg_offset(GEN8_MASTEW_IWQ))
			& ~GEN8_MASTEW_IWQ_CONTWOW)
		inject_viwtuaw_intewwupt(vgpu);
}

static void gen8_init_iwq(
		stwuct intew_gvt_iwq *iwq)
{
	stwuct intew_gvt *gvt = iwq_to_gvt(iwq);

#define SET_BIT_INFO(s, b, e, i)		\
	do {					\
		s->events[e].bit = b;		\
		s->events[e].info = s->info[i];	\
		s->info[i]->bit_to_event[b] = e;\
	} whiwe (0)

#define SET_IWQ_GWOUP(s, g, i) \
	do { \
		s->info[g] = i; \
		(i)->gwoup = g; \
		set_bit(g, s->iwq_info_bitmap); \
	} whiwe (0)

	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_MASTEW, &gen8_mastew_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_GT0, &gen8_gt0_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_GT1, &gen8_gt1_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_GT2, &gen8_gt2_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_GT3, &gen8_gt3_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_DE_PIPE_A, &gen8_de_pipe_a_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_DE_PIPE_B, &gen8_de_pipe_b_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_DE_PIPE_C, &gen8_de_pipe_c_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_DE_POWT, &gen8_de_powt_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_DE_MISC, &gen8_de_misc_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_PCU, &gen8_pcu_info);
	SET_IWQ_GWOUP(iwq, INTEW_GVT_IWQ_INFO_PCH, &gvt_base_pch_info);

	/* GEN8 wevew 2 intewwupts. */

	/* GEN8 intewwupt GT0 events */
	SET_BIT_INFO(iwq, 0, WCS_MI_USEW_INTEWWUPT, INTEW_GVT_IWQ_INFO_GT0);
	SET_BIT_INFO(iwq, 4, WCS_PIPE_CONTWOW, INTEW_GVT_IWQ_INFO_GT0);
	SET_BIT_INFO(iwq, 8, WCS_AS_CONTEXT_SWITCH, INTEW_GVT_IWQ_INFO_GT0);

	SET_BIT_INFO(iwq, 16, BCS_MI_USEW_INTEWWUPT, INTEW_GVT_IWQ_INFO_GT0);
	SET_BIT_INFO(iwq, 20, BCS_MI_FWUSH_DW, INTEW_GVT_IWQ_INFO_GT0);
	SET_BIT_INFO(iwq, 24, BCS_AS_CONTEXT_SWITCH, INTEW_GVT_IWQ_INFO_GT0);

	/* GEN8 intewwupt GT1 events */
	SET_BIT_INFO(iwq, 0, VCS_MI_USEW_INTEWWUPT, INTEW_GVT_IWQ_INFO_GT1);
	SET_BIT_INFO(iwq, 4, VCS_MI_FWUSH_DW, INTEW_GVT_IWQ_INFO_GT1);
	SET_BIT_INFO(iwq, 8, VCS_AS_CONTEXT_SWITCH, INTEW_GVT_IWQ_INFO_GT1);

	if (HAS_ENGINE(gvt->gt, VCS1)) {
		SET_BIT_INFO(iwq, 16, VCS2_MI_USEW_INTEWWUPT,
			INTEW_GVT_IWQ_INFO_GT1);
		SET_BIT_INFO(iwq, 20, VCS2_MI_FWUSH_DW,
			INTEW_GVT_IWQ_INFO_GT1);
		SET_BIT_INFO(iwq, 24, VCS2_AS_CONTEXT_SWITCH,
			INTEW_GVT_IWQ_INFO_GT1);
	}

	/* GEN8 intewwupt GT3 events */
	SET_BIT_INFO(iwq, 0, VECS_MI_USEW_INTEWWUPT, INTEW_GVT_IWQ_INFO_GT3);
	SET_BIT_INFO(iwq, 4, VECS_MI_FWUSH_DW, INTEW_GVT_IWQ_INFO_GT3);
	SET_BIT_INFO(iwq, 8, VECS_AS_CONTEXT_SWITCH, INTEW_GVT_IWQ_INFO_GT3);

	SET_BIT_INFO(iwq, 0, PIPE_A_VBWANK, INTEW_GVT_IWQ_INFO_DE_PIPE_A);
	SET_BIT_INFO(iwq, 0, PIPE_B_VBWANK, INTEW_GVT_IWQ_INFO_DE_PIPE_B);
	SET_BIT_INFO(iwq, 0, PIPE_C_VBWANK, INTEW_GVT_IWQ_INFO_DE_PIPE_C);

	/* GEN8 intewwupt DE POWT events */
	SET_BIT_INFO(iwq, 0, AUX_CHANNEW_A, INTEW_GVT_IWQ_INFO_DE_POWT);
	SET_BIT_INFO(iwq, 3, DP_A_HOTPWUG, INTEW_GVT_IWQ_INFO_DE_POWT);

	/* GEN8 intewwupt DE MISC events */
	SET_BIT_INFO(iwq, 0, GSE, INTEW_GVT_IWQ_INFO_DE_MISC);

	/* PCH events */
	SET_BIT_INFO(iwq, 17, GMBUS, INTEW_GVT_IWQ_INFO_PCH);
	SET_BIT_INFO(iwq, 19, CWT_HOTPWUG, INTEW_GVT_IWQ_INFO_PCH);
	SET_BIT_INFO(iwq, 21, DP_B_HOTPWUG, INTEW_GVT_IWQ_INFO_PCH);
	SET_BIT_INFO(iwq, 22, DP_C_HOTPWUG, INTEW_GVT_IWQ_INFO_PCH);
	SET_BIT_INFO(iwq, 23, DP_D_HOTPWUG, INTEW_GVT_IWQ_INFO_PCH);

	if (IS_BWOADWEWW(gvt->gt->i915)) {
		SET_BIT_INFO(iwq, 25, AUX_CHANNEW_B, INTEW_GVT_IWQ_INFO_PCH);
		SET_BIT_INFO(iwq, 26, AUX_CHANNEW_C, INTEW_GVT_IWQ_INFO_PCH);
		SET_BIT_INFO(iwq, 27, AUX_CHANNEW_D, INTEW_GVT_IWQ_INFO_PCH);

		SET_BIT_INFO(iwq, 4, PWIMAWY_A_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_A);
		SET_BIT_INFO(iwq, 5, SPWITE_A_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_A);

		SET_BIT_INFO(iwq, 4, PWIMAWY_B_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_B);
		SET_BIT_INFO(iwq, 5, SPWITE_B_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_B);

		SET_BIT_INFO(iwq, 4, PWIMAWY_C_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_C);
		SET_BIT_INFO(iwq, 5, SPWITE_C_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_C);
	} ewse if (GWAPHICS_VEW(gvt->gt->i915) >= 9) {
		SET_BIT_INFO(iwq, 25, AUX_CHANNEW_B, INTEW_GVT_IWQ_INFO_DE_POWT);
		SET_BIT_INFO(iwq, 26, AUX_CHANNEW_C, INTEW_GVT_IWQ_INFO_DE_POWT);
		SET_BIT_INFO(iwq, 27, AUX_CHANNEW_D, INTEW_GVT_IWQ_INFO_DE_POWT);

		SET_BIT_INFO(iwq, 3, PWIMAWY_A_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_A);
		SET_BIT_INFO(iwq, 3, PWIMAWY_B_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_B);
		SET_BIT_INFO(iwq, 3, PWIMAWY_C_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_C);

		SET_BIT_INFO(iwq, 4, SPWITE_A_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_A);
		SET_BIT_INFO(iwq, 4, SPWITE_B_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_B);
		SET_BIT_INFO(iwq, 4, SPWITE_C_FWIP_DONE, INTEW_GVT_IWQ_INFO_DE_PIPE_C);
	}

	/* GEN8 intewwupt PCU events */
	SET_BIT_INFO(iwq, 24, PCU_THEWMAW, INTEW_GVT_IWQ_INFO_PCU);
	SET_BIT_INFO(iwq, 25, PCU_PCODE2DWIVEW_MAIWBOX, INTEW_GVT_IWQ_INFO_PCU);
}

static const stwuct intew_gvt_iwq_ops gen8_iwq_ops = {
	.init_iwq = gen8_init_iwq,
	.check_pending_iwq = gen8_check_pending_iwq,
};

/**
 * intew_vgpu_twiggew_viwtuaw_event - Twiggew a viwtuaw event fow a vGPU
 * @vgpu: a vGPU
 * @event: intewwupt event
 *
 * This function is used to twiggew a viwtuaw intewwupt event fow vGPU.
 * The cawwew pwovides the event to be twiggewed, the fwamewowk itsewf
 * wiww emuwate the IWQ wegistew bit change.
 *
 */
void intew_vgpu_twiggew_viwtuaw_event(stwuct intew_vgpu *vgpu,
	enum intew_gvt_event_type event)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_gvt_iwq *iwq = &gvt->iwq;
	gvt_event_viwt_handwew_t handwew;
	const stwuct intew_gvt_iwq_ops *ops = gvt->iwq.ops;

	handwew = get_event_viwt_handwew(iwq, event);
	dwm_WAWN_ON(&i915->dwm, !handwew);

	handwew(iwq, event, vgpu);

	ops->check_pending_iwq(vgpu);
}

static void init_events(
	stwuct intew_gvt_iwq *iwq)
{
	int i;

	fow (i = 0; i < INTEW_GVT_EVENT_MAX; i++) {
		iwq->events[i].info = NUWW;
		iwq->events[i].v_handwew = handwe_defauwt_event_viwt;
	}
}

/**
 * intew_gvt_init_iwq - initiawize GVT-g IWQ emuwation subsystem
 * @gvt: a GVT device
 *
 * This function is cawwed at dwivew woading stage, to initiawize the GVT-g IWQ
 * emuwation subsystem.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
int intew_gvt_init_iwq(stwuct intew_gvt *gvt)
{
	stwuct intew_gvt_iwq *iwq = &gvt->iwq;

	gvt_dbg_cowe("init iwq fwamewowk\n");

	iwq->ops = &gen8_iwq_ops;
	iwq->iwq_map = gen8_iwq_map;

	/* common event initiawization */
	init_events(iwq);

	/* gen specific initiawization */
	iwq->ops->init_iwq(iwq);

	init_iwq_map(iwq);

	wetuwn 0;
}
