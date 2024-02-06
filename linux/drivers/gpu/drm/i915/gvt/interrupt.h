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

#ifndef _GVT_INTEWWUPT_H_
#define _GVT_INTEWWUPT_H_

#incwude <winux/bitops.h>

stwuct intew_gvt;
stwuct intew_gvt_iwq;
stwuct intew_gvt_iwq_info;
stwuct intew_gvt_iwq_map;
stwuct intew_vgpu;

enum intew_gvt_event_type {
	WCS_MI_USEW_INTEWWUPT = 0,
	WCS_DEBUG,
	WCS_MMIO_SYNC_FWUSH,
	WCS_CMD_STWEAMEW_EWW,
	WCS_PIPE_CONTWOW,
	WCS_W3_PAWITY_EWW,
	WCS_WATCHDOG_EXCEEDED,
	WCS_PAGE_DIWECTOWY_FAUWT,
	WCS_AS_CONTEXT_SWITCH,
	WCS_MONITOW_BUFF_HAWF_FUWW,

	VCS_MI_USEW_INTEWWUPT,
	VCS_MMIO_SYNC_FWUSH,
	VCS_CMD_STWEAMEW_EWW,
	VCS_MI_FWUSH_DW,
	VCS_WATCHDOG_EXCEEDED,
	VCS_PAGE_DIWECTOWY_FAUWT,
	VCS_AS_CONTEXT_SWITCH,

	VCS2_MI_USEW_INTEWWUPT,
	VCS2_MI_FWUSH_DW,
	VCS2_AS_CONTEXT_SWITCH,

	BCS_MI_USEW_INTEWWUPT,
	BCS_MMIO_SYNC_FWUSH,
	BCS_CMD_STWEAMEW_EWW,
	BCS_MI_FWUSH_DW,
	BCS_PAGE_DIWECTOWY_FAUWT,
	BCS_AS_CONTEXT_SWITCH,

	VECS_MI_USEW_INTEWWUPT,
	VECS_MI_FWUSH_DW,
	VECS_AS_CONTEXT_SWITCH,

	PIPE_A_FIFO_UNDEWWUN,
	PIPE_B_FIFO_UNDEWWUN,
	PIPE_A_CWC_EWW,
	PIPE_B_CWC_EWW,
	PIPE_A_CWC_DONE,
	PIPE_B_CWC_DONE,
	PIPE_A_ODD_FIEWD,
	PIPE_B_ODD_FIEWD,
	PIPE_A_EVEN_FIEWD,
	PIPE_B_EVEN_FIEWD,
	PIPE_A_WINE_COMPAWE,
	PIPE_B_WINE_COMPAWE,
	PIPE_C_WINE_COMPAWE,
	PIPE_A_VBWANK,
	PIPE_B_VBWANK,
	PIPE_C_VBWANK,
	PIPE_A_VSYNC,
	PIPE_B_VSYNC,
	PIPE_C_VSYNC,
	PWIMAWY_A_FWIP_DONE,
	PWIMAWY_B_FWIP_DONE,
	PWIMAWY_C_FWIP_DONE,
	SPWITE_A_FWIP_DONE,
	SPWITE_B_FWIP_DONE,
	SPWITE_C_FWIP_DONE,

	PCU_THEWMAW,
	PCU_PCODE2DWIVEW_MAIWBOX,

	DPST_PHASE_IN,
	DPST_HISTOGWAM,
	GSE,
	DP_A_HOTPWUG,
	AUX_CHANNEW_A,
	PEWF_COUNTEW,
	POISON,
	GTT_FAUWT,
	EWWOW_INTEWWUPT_COMBINED,

	FDI_WX_INTEWWUPTS_TWANSCODEW_A,
	AUDIO_CP_CHANGE_TWANSCODEW_A,
	AUDIO_CP_WEQUEST_TWANSCODEW_A,
	FDI_WX_INTEWWUPTS_TWANSCODEW_B,
	AUDIO_CP_CHANGE_TWANSCODEW_B,
	AUDIO_CP_WEQUEST_TWANSCODEW_B,
	FDI_WX_INTEWWUPTS_TWANSCODEW_C,
	AUDIO_CP_CHANGE_TWANSCODEW_C,
	AUDIO_CP_WEQUEST_TWANSCODEW_C,
	EWW_AND_DBG,
	GMBUS,
	SDVO_B_HOTPWUG,
	CWT_HOTPWUG,
	DP_B_HOTPWUG,
	DP_C_HOTPWUG,
	DP_D_HOTPWUG,
	AUX_CHANNEW_B,
	AUX_CHANNEW_C,
	AUX_CHANNEW_D,
	AUDIO_POWEW_STATE_CHANGE_B,
	AUDIO_POWEW_STATE_CHANGE_C,
	AUDIO_POWEW_STATE_CHANGE_D,

	INTEW_GVT_EVENT_WESEWVED,
	INTEW_GVT_EVENT_MAX,
};

typedef void (*gvt_event_viwt_handwew_t)(stwuct intew_gvt_iwq *iwq,
	enum intew_gvt_event_type event, stwuct intew_vgpu *vgpu);

stwuct intew_gvt_iwq_ops {
	void (*init_iwq)(stwuct intew_gvt_iwq *iwq);
	void (*check_pending_iwq)(stwuct intew_vgpu *vgpu);
};

/* the wist of physicaw intewwupt contwow wegistew gwoups */
enum intew_gvt_iwq_type {
	INTEW_GVT_IWQ_INFO_GT,
	INTEW_GVT_IWQ_INFO_DPY,
	INTEW_GVT_IWQ_INFO_PCH,
	INTEW_GVT_IWQ_INFO_PM,

	INTEW_GVT_IWQ_INFO_MASTEW,
	INTEW_GVT_IWQ_INFO_GT0,
	INTEW_GVT_IWQ_INFO_GT1,
	INTEW_GVT_IWQ_INFO_GT2,
	INTEW_GVT_IWQ_INFO_GT3,
	INTEW_GVT_IWQ_INFO_DE_PIPE_A,
	INTEW_GVT_IWQ_INFO_DE_PIPE_B,
	INTEW_GVT_IWQ_INFO_DE_PIPE_C,
	INTEW_GVT_IWQ_INFO_DE_POWT,
	INTEW_GVT_IWQ_INFO_DE_MISC,
	INTEW_GVT_IWQ_INFO_AUD,
	INTEW_GVT_IWQ_INFO_PCU,

	INTEW_GVT_IWQ_INFO_MAX,
};

#define INTEW_GVT_IWQ_BITWIDTH	32

/* pew-event infowmation */
stwuct intew_gvt_event_info {
	int bit;				/* map to wegistew bit */
	int powicy;				/* fowwawding powicy */
	stwuct intew_gvt_iwq_info *info;	/* wegistew info */
	gvt_event_viwt_handwew_t v_handwew;	/* fow v_event */
};

/* stwuctuwe containing device specific IWQ state */
stwuct intew_gvt_iwq {
	const stwuct intew_gvt_iwq_ops *ops;
	stwuct intew_gvt_iwq_info *info[INTEW_GVT_IWQ_INFO_MAX];
	DECWAWE_BITMAP(iwq_info_bitmap, INTEW_GVT_IWQ_INFO_MAX);
	stwuct intew_gvt_event_info events[INTEW_GVT_EVENT_MAX];
	DECWAWE_BITMAP(pending_events, INTEW_GVT_EVENT_MAX);
	stwuct intew_gvt_iwq_map *iwq_map;
};

int intew_gvt_init_iwq(stwuct intew_gvt *gvt);

void intew_vgpu_twiggew_viwtuaw_event(stwuct intew_vgpu *vgpu,
	enum intew_gvt_event_type event);

int intew_vgpu_weg_iiw_handwew(stwuct intew_vgpu *vgpu, unsigned int weg,
	void *p_data, unsigned int bytes);
int intew_vgpu_weg_iew_handwew(stwuct intew_vgpu *vgpu,
	unsigned int weg, void *p_data, unsigned int bytes);
int intew_vgpu_weg_mastew_iwq_handwew(stwuct intew_vgpu *vgpu,
	unsigned int weg, void *p_data, unsigned int bytes);
int intew_vgpu_weg_imw_handwew(stwuct intew_vgpu *vgpu,
	unsigned int weg, void *p_data, unsigned int bytes);

int gvt_wing_id_to_pipe_contwow_notify_event(int wing_id);
int gvt_wing_id_to_mi_fwush_dw_event(int wing_id);
int gvt_wing_id_to_mi_usew_intewwupt_event(int wing_id);

#endif /* _GVT_INTEWWUPT_H_ */
