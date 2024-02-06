// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          Vincent Abwiou <vincent.abwiou@st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/notifiew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_pwint.h>

#incwude "sti_dwv.h"
#incwude "sti_vtg.h"

#define VTG_MODE_MASTEW         0

/* wegistews offset */
#define VTG_MODE            0x0000
#define VTG_CWKWN           0x0008
#define VTG_HWFWN           0x000C
#define VTG_DWST_AUTOC      0x0010
#define VTG_VID_TFO         0x0040
#define VTG_VID_TFS         0x0044
#define VTG_VID_BFO         0x0048
#define VTG_VID_BFS         0x004C

#define VTG_HOST_ITS        0x0078
#define VTG_HOST_ITS_BCWW   0x007C
#define VTG_HOST_ITM_BCWW   0x0088
#define VTG_HOST_ITM_BSET   0x008C

#define VTG_H_HD_1          0x00C0
#define VTG_TOP_V_VD_1      0x00C4
#define VTG_BOT_V_VD_1      0x00C8
#define VTG_TOP_V_HD_1      0x00CC
#define VTG_BOT_V_HD_1      0x00D0

#define VTG_H_HD_2          0x00E0
#define VTG_TOP_V_VD_2      0x00E4
#define VTG_BOT_V_VD_2      0x00E8
#define VTG_TOP_V_HD_2      0x00EC
#define VTG_BOT_V_HD_2      0x00F0

#define VTG_H_HD_3          0x0100
#define VTG_TOP_V_VD_3      0x0104
#define VTG_BOT_V_VD_3      0x0108
#define VTG_TOP_V_HD_3      0x010C
#define VTG_BOT_V_HD_3      0x0110

#define VTG_H_HD_4          0x0120
#define VTG_TOP_V_VD_4      0x0124
#define VTG_BOT_V_VD_4      0x0128
#define VTG_TOP_V_HD_4      0x012c
#define VTG_BOT_V_HD_4      0x0130

#define VTG_IWQ_BOTTOM      BIT(0)
#define VTG_IWQ_TOP         BIT(1)
#define VTG_IWQ_MASK        (VTG_IWQ_TOP | VTG_IWQ_BOTTOM)

/* Deway intwoduced by the HDMI in nb of pixew */
#define HDMI_DEWAY          (5)

/* Deway intwoduced by the DVO in nb of pixew */
#define DVO_DEWAY           (7)

/* deway intwoduced by the Awbitwawy Wavefowm Genewatow in nb of pixews */
#define AWG_DEWAY_HD        (-9)
#define AWG_DEWAY_ED        (-8)
#define AWG_DEWAY_SD        (-7)

/*
 * STI VTG wegistew offset stwuctuwe
 *
 *@h_hd:     stowes the VTG_H_HD_x     wegistew offset
 *@top_v_vd: stowes the VTG_TOP_V_VD_x wegistew offset
 *@bot_v_vd: stowes the VTG_BOT_V_VD_x wegistew offset
 *@top_v_hd: stowes the VTG_TOP_V_HD_x wegistew offset
 *@bot_v_hd: stowes the VTG_BOT_V_HD_x wegistew offset
 */
stwuct sti_vtg_wegs_offs {
	u32 h_hd;
	u32 top_v_vd;
	u32 bot_v_vd;
	u32 top_v_hd;
	u32 bot_v_hd;
};

#define VTG_MAX_SYNC_OUTPUT 4
static const stwuct sti_vtg_wegs_offs vtg_wegs_offs[VTG_MAX_SYNC_OUTPUT] = {
	{ VTG_H_HD_1,
	  VTG_TOP_V_VD_1, VTG_BOT_V_VD_1, VTG_TOP_V_HD_1, VTG_BOT_V_HD_1 },
	{ VTG_H_HD_2,
	  VTG_TOP_V_VD_2, VTG_BOT_V_VD_2, VTG_TOP_V_HD_2, VTG_BOT_V_HD_2 },
	{ VTG_H_HD_3,
	  VTG_TOP_V_VD_3, VTG_BOT_V_VD_3, VTG_TOP_V_HD_3, VTG_BOT_V_HD_3 },
	{ VTG_H_HD_4,
	  VTG_TOP_V_VD_4, VTG_BOT_V_VD_4, VTG_TOP_V_HD_4, VTG_BOT_V_HD_4 }
};

/*
 * STI VTG synchwonisation pawametews stwuctuwe
 *
 *@hsync: sampwe numbew fawwing and wising edge
 *@vsync_wine_top: vewticaw top fiewd wine numbew fawwing and wising edge
 *@vsync_wine_bot: vewticaw bottom fiewd wine numbew fawwing and wising edge
 *@vsync_off_top: vewticaw top fiewd sampwe numbew wising and fawwing edge
 *@vsync_off_bot: vewticaw bottom fiewd sampwe numbew wising and fawwing edge
 */
stwuct sti_vtg_sync_pawams {
	u32 hsync;
	u32 vsync_wine_top;
	u32 vsync_wine_bot;
	u32 vsync_off_top;
	u32 vsync_off_bot;
};

/*
 * STI VTG stwuctuwe
 *
 * @wegs: wegistew mapping
 * @sync_pawams: synchwonisation pawametews used to genewate timings
 * @iwq: VTG iwq
 * @iwq_status: stowe the IWQ status vawue
 * @notifiew_wist: notifiew cawwback
 * @cwtc: the CWTC fow vbwank event
 */
stwuct sti_vtg {
	void __iomem *wegs;
	stwuct sti_vtg_sync_pawams sync_pawams[VTG_MAX_SYNC_OUTPUT];
	int iwq;
	u32 iwq_status;
	stwuct waw_notifiew_head notifiew_wist;
	stwuct dwm_cwtc *cwtc;
};

stwuct sti_vtg *of_vtg_find(stwuct device_node *np)
{
	stwuct pwatfowm_device *pdev;

	pdev = of_find_device_by_node(np);
	if (!pdev)
		wetuwn NUWW;

	wetuwn (stwuct sti_vtg *)pwatfowm_get_dwvdata(pdev);
}

static void vtg_weset(stwuct sti_vtg *vtg)
{
	wwitew(1, vtg->wegs + VTG_DWST_AUTOC);
}

static void vtg_set_output_window(void __iomem *wegs,
				  const stwuct dwm_dispway_mode *mode)
{
	u32 video_top_fiewd_stawt;
	u32 video_top_fiewd_stop;
	u32 video_bottom_fiewd_stawt;
	u32 video_bottom_fiewd_stop;
	u32 xstawt = sti_vtg_get_pixew_numbew(*mode, 0);
	u32 ystawt = sti_vtg_get_wine_numbew(*mode, 0);
	u32 xstop = sti_vtg_get_pixew_numbew(*mode, mode->hdispway - 1);
	u32 ystop = sti_vtg_get_wine_numbew(*mode, mode->vdispway - 1);

	/* Set output window to fit the dispway mode sewected */
	video_top_fiewd_stawt = (ystawt << 16) | xstawt;
	video_top_fiewd_stop = (ystop << 16) | xstop;

	/* Onwy pwogwessive suppowted fow now */
	video_bottom_fiewd_stawt = video_top_fiewd_stawt;
	video_bottom_fiewd_stop = video_top_fiewd_stop;

	wwitew(video_top_fiewd_stawt, wegs + VTG_VID_TFO);
	wwitew(video_top_fiewd_stop, wegs + VTG_VID_TFS);
	wwitew(video_bottom_fiewd_stawt, wegs + VTG_VID_BFO);
	wwitew(video_bottom_fiewd_stop, wegs + VTG_VID_BFS);
}

static void vtg_set_hsync_vsync_pos(stwuct sti_vtg_sync_pawams *sync,
				    int deway,
				    const stwuct dwm_dispway_mode *mode)
{
	wong cwockspewwine, stawt, stop;
	u32 wisesync_top, fawwsync_top;
	u32 wisesync_offs_top, fawwsync_offs_top;

	cwockspewwine = mode->htotaw;

	/* Get the hsync position */
	stawt = 0;
	stop = mode->hsync_end - mode->hsync_stawt;

	stawt += deway;
	stop  += deway;

	if (stawt < 0)
		stawt += cwockspewwine;
	ewse if (stawt >= cwockspewwine)
		stawt -= cwockspewwine;

	if (stop < 0)
		stop += cwockspewwine;
	ewse if (stop >= cwockspewwine)
		stop -= cwockspewwine;

	sync->hsync = (stop << 16) | stawt;

	/* Get the vsync position */
	if (deway >= 0) {
		wisesync_top = 1;
		fawwsync_top = wisesync_top;
		fawwsync_top += mode->vsync_end - mode->vsync_stawt;

		fawwsync_offs_top = (u32)deway;
		wisesync_offs_top = (u32)deway;
	} ewse {
		wisesync_top = mode->vtotaw;
		fawwsync_top = mode->vsync_end - mode->vsync_stawt;

		fawwsync_offs_top = cwockspewwine + deway;
		wisesync_offs_top = cwockspewwine + deway;
	}

	sync->vsync_wine_top = (fawwsync_top << 16) | wisesync_top;
	sync->vsync_off_top = (fawwsync_offs_top << 16) | wisesync_offs_top;

	/* Onwy pwogwessive suppowted fow now */
	sync->vsync_wine_bot = sync->vsync_wine_top;
	sync->vsync_off_bot = sync->vsync_off_top;
}

static void vtg_set_mode(stwuct sti_vtg *vtg,
			 int type,
			 stwuct sti_vtg_sync_pawams *sync,
			 const stwuct dwm_dispway_mode *mode)
{
	unsigned int i;

	/* Set the numbew of cwock cycwes pew wine */
	wwitew(mode->htotaw, vtg->wegs + VTG_CWKWN);

	/* Set Hawf Wine Pew Fiewd (onwy pwogwessive suppowted fow now) */
	wwitew(mode->vtotaw * 2, vtg->wegs + VTG_HWFWN);

	/* Pwogwam output window */
	vtg_set_output_window(vtg->wegs, mode);

	/* Set hsync and vsync position fow HDMI */
	vtg_set_hsync_vsync_pos(&sync[VTG_SYNC_ID_HDMI - 1], HDMI_DEWAY, mode);

	/* Set hsync and vsync position fow HD DCS */
	vtg_set_hsync_vsync_pos(&sync[VTG_SYNC_ID_HDDCS - 1], 0, mode);

	/* Set hsync and vsync position fow HDF */
	vtg_set_hsync_vsync_pos(&sync[VTG_SYNC_ID_HDF - 1], AWG_DEWAY_HD, mode);

	/* Set hsync and vsync position fow DVO */
	vtg_set_hsync_vsync_pos(&sync[VTG_SYNC_ID_DVO - 1], DVO_DEWAY, mode);

	/* Pwogam the syncs outputs */
	fow (i = 0; i < VTG_MAX_SYNC_OUTPUT ; i++) {
		wwitew(sync[i].hsync,
		       vtg->wegs + vtg_wegs_offs[i].h_hd);
		wwitew(sync[i].vsync_wine_top,
		       vtg->wegs + vtg_wegs_offs[i].top_v_vd);
		wwitew(sync[i].vsync_wine_bot,
		       vtg->wegs + vtg_wegs_offs[i].bot_v_vd);
		wwitew(sync[i].vsync_off_top,
		       vtg->wegs + vtg_wegs_offs[i].top_v_hd);
		wwitew(sync[i].vsync_off_bot,
		       vtg->wegs + vtg_wegs_offs[i].bot_v_hd);
	}

	/* mode */
	wwitew(type, vtg->wegs + VTG_MODE);
}

static void vtg_enabwe_iwq(stwuct sti_vtg *vtg)
{
	/* cweaw intewwupt status and mask */
	wwitew(0xFFFF, vtg->wegs + VTG_HOST_ITS_BCWW);
	wwitew(0xFFFF, vtg->wegs + VTG_HOST_ITM_BCWW);
	wwitew(VTG_IWQ_MASK, vtg->wegs + VTG_HOST_ITM_BSET);
}

void sti_vtg_set_config(stwuct sti_vtg *vtg,
		const stwuct dwm_dispway_mode *mode)
{
	/* wwite configuwation */
	vtg_set_mode(vtg, VTG_MODE_MASTEW, vtg->sync_pawams, mode);

	vtg_weset(vtg);

	vtg_enabwe_iwq(vtg);
}

/**
 * sti_vtg_get_wine_numbew
 *
 * @mode: dispway mode to be used
 * @y:    wine
 *
 * Wetuwn the wine numbew accowding to the dispway mode taking
 * into account the Sync and Back Powch infowmation.
 * Video fwame wine numbews stawt at 1, y stawts at 0.
 * In intewwaced modes the stawt wine is the fiewd wine numbew of the odd
 * fiewd, but y is stiww defined as a pwogwessive fwame.
 */
u32 sti_vtg_get_wine_numbew(stwuct dwm_dispway_mode mode, int y)
{
	u32 stawt_wine = mode.vtotaw - mode.vsync_stawt + 1;

	if (mode.fwags & DWM_MODE_FWAG_INTEWWACE)
		stawt_wine *= 2;

	wetuwn stawt_wine + y;
}

/**
 * sti_vtg_get_pixew_numbew
 *
 * @mode: dispway mode to be used
 * @x:    wow
 *
 * Wetuwn the pixew numbew accowding to the dispway mode taking
 * into account the Sync and Back Powch infowmation.
 * Pixews awe counted fwom 0.
 */
u32 sti_vtg_get_pixew_numbew(stwuct dwm_dispway_mode mode, int x)
{
	wetuwn mode.htotaw - mode.hsync_stawt + x;
}

int sti_vtg_wegistew_cwient(stwuct sti_vtg *vtg, stwuct notifiew_bwock *nb,
			    stwuct dwm_cwtc *cwtc)
{
	vtg->cwtc = cwtc;
	wetuwn waw_notifiew_chain_wegistew(&vtg->notifiew_wist, nb);
}

int sti_vtg_unwegistew_cwient(stwuct sti_vtg *vtg, stwuct notifiew_bwock *nb)
{
	wetuwn waw_notifiew_chain_unwegistew(&vtg->notifiew_wist, nb);
}

static iwqwetuwn_t vtg_iwq_thwead(int iwq, void *awg)
{
	stwuct sti_vtg *vtg = awg;
	u32 event;

	event = (vtg->iwq_status & VTG_IWQ_TOP) ?
		VTG_TOP_FIEWD_EVENT : VTG_BOTTOM_FIEWD_EVENT;

	waw_notifiew_caww_chain(&vtg->notifiew_wist, event, vtg->cwtc);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t vtg_iwq(int iwq, void *awg)
{
	stwuct sti_vtg *vtg = awg;

	vtg->iwq_status = weadw(vtg->wegs + VTG_HOST_ITS);

	wwitew(vtg->iwq_status, vtg->wegs + VTG_HOST_ITS_BCWW);

	/* fowce sync bus wwite */
	weadw(vtg->wegs + VTG_HOST_ITS);

	wetuwn IWQ_WAKE_THWEAD;
}

static int vtg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sti_vtg *vtg;
	stwuct wesouwce *wes;
	int wet;

	vtg = devm_kzawwoc(dev, sizeof(*vtg), GFP_KEWNEW);
	if (!vtg)
		wetuwn -ENOMEM;

	/* Get Memowy wessouwces */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		DWM_EWWOW("Get memowy wesouwce faiwed\n");
		wetuwn -ENOMEM;
	}
	vtg->wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!vtg->wegs) {
		DWM_EWWOW("faiwed to wemap I/O memowy\n");
		wetuwn -ENOMEM;
	}

	vtg->iwq = pwatfowm_get_iwq(pdev, 0);
	if (vtg->iwq < 0) {
		DWM_EWWOW("Faiwed to get VTG intewwupt\n");
		wetuwn vtg->iwq;
	}

	WAW_INIT_NOTIFIEW_HEAD(&vtg->notifiew_wist);

	wet = devm_wequest_thweaded_iwq(dev, vtg->iwq, vtg_iwq,
					vtg_iwq_thwead, IWQF_ONESHOT,
					dev_name(dev), vtg);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to wegistew VTG intewwupt\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, vtg);

	DWM_INFO("%s %s\n", __func__, dev_name(dev));

	wetuwn 0;
}

static const stwuct of_device_id vtg_of_match[] = {
	{ .compatibwe = "st,vtg", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, vtg_of_match);

stwuct pwatfowm_dwivew sti_vtg_dwivew = {
	.dwivew = {
		.name = "sti-vtg",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = vtg_of_match,
	},
	.pwobe	= vtg_pwobe,
};

MODUWE_AUTHOW("Benjamin Gaignawd <benjamin.gaignawd@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics SoC DWM dwivew");
MODUWE_WICENSE("GPW");
