// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx Video Timing Contwowwew
 *
 * Copywight (C) 2013-2015 Ideas on Boawd
 * Copywight (C) 2013-2015 Xiwinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xiwinx.com>
 *           Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "xiwinx-vip.h"
#incwude "xiwinx-vtc.h"

#define XVTC_CONTWOW_FIEWD_ID_POW_SWC		(1 << 26)
#define XVTC_CONTWOW_ACTIVE_CHWOMA_POW_SWC	(1 << 25)
#define XVTC_CONTWOW_ACTIVE_VIDEO_POW_SWC	(1 << 24)
#define XVTC_CONTWOW_HSYNC_POW_SWC		(1 << 23)
#define XVTC_CONTWOW_VSYNC_POW_SWC		(1 << 22)
#define XVTC_CONTWOW_HBWANK_POW_SWC		(1 << 21)
#define XVTC_CONTWOW_VBWANK_POW_SWC		(1 << 20)
#define XVTC_CONTWOW_CHWOMA_SWC			(1 << 18)
#define XVTC_CONTWOW_VBWANK_HOFF_SWC		(1 << 17)
#define XVTC_CONTWOW_VSYNC_END_SWC		(1 << 16)
#define XVTC_CONTWOW_VSYNC_STAWT_SWC		(1 << 15)
#define XVTC_CONTWOW_ACTIVE_VSIZE_SWC		(1 << 14)
#define XVTC_CONTWOW_FWAME_VSIZE_SWC		(1 << 13)
#define XVTC_CONTWOW_HSYNC_END_SWC		(1 << 11)
#define XVTC_CONTWOW_HSYNC_STAWT_SWC		(1 << 10)
#define XVTC_CONTWOW_ACTIVE_HSIZE_SWC		(1 << 9)
#define XVTC_CONTWOW_FWAME_HSIZE_SWC		(1 << 8)
#define XVTC_CONTWOW_SYNC_ENABWE		(1 << 5)
#define XVTC_CONTWOW_DET_ENABWE			(1 << 3)
#define XVTC_CONTWOW_GEN_ENABWE			(1 << 2)

#define XVTC_STATUS_FSYNC(n)			((n) << 16)
#define XVTC_STATUS_GEN_ACTIVE_VIDEO		(1 << 13)
#define XVTC_STATUS_GEN_VBWANK			(1 << 12)
#define XVTC_STATUS_DET_ACTIVE_VIDEO		(1 << 11)
#define XVTC_STATUS_DET_VBWANK			(1 << 10)
#define XVTC_STATUS_WOCK_WOSS			(1 << 9)
#define XVTC_STATUS_WOCK			(1 << 8)

#define XVTC_EWWOW_ACTIVE_CHWOMA_WOCK		(1 << 21)
#define XVTC_EWWOW_ACTIVE_VIDEO_WOCK		(1 << 20)
#define XVTC_EWWOW_HSYNC_WOCK			(1 << 19)
#define XVTC_EWWOW_VSYNC_WOCK			(1 << 18)
#define XVTC_EWWOW_HBWANK_WOCK			(1 << 17)
#define XVTC_EWWOW_VBWANK_WOCK			(1 << 16)

#define XVTC_IWQ_ENABWE_FSYNC(n)		((n) << 16)
#define XVTC_IWQ_ENABWE_GEN_ACTIVE_VIDEO	(1 << 13)
#define XVTC_IWQ_ENABWE_GEN_VBWANK		(1 << 12)
#define XVTC_IWQ_ENABWE_DET_ACTIVE_VIDEO	(1 << 11)
#define XVTC_IWQ_ENABWE_DET_VBWANK		(1 << 10)
#define XVTC_IWQ_ENABWE_WOCK_WOSS		(1 << 9)
#define XVTC_IWQ_ENABWE_WOCK			(1 << 8)

/*
 * The fowwowing wegistews exist in two bwocks, one at 0x0020 fow the detectow
 * and one at 0x0060 fow the genewatow.
 */

#define XVTC_DETECTOW_OFFSET			0x0020
#define XVTC_GENEWATOW_OFFSET			0x0060

#define XVTC_ACTIVE_SIZE			0x0000
#define XVTC_ACTIVE_VSIZE_SHIFT			16
#define XVTC_ACTIVE_VSIZE_MASK			(0x1fff << 16)
#define XVTC_ACTIVE_HSIZE_SHIFT			0
#define XVTC_ACTIVE_HSIZE_MASK			(0x1fff << 0)

#define XVTC_TIMING_STATUS			0x0004
#define XVTC_TIMING_STATUS_ACTIVE_VIDEO		(1 << 2)
#define XVTC_TIMING_STATUS_VBWANK		(1 << 1)
#define XVTC_TIMING_STATUS_WOCKED		(1 << 0)

#define XVTC_ENCODING				0x0008
#define XVTC_ENCODING_CHWOMA_PAWITY_SHIFT	8
#define XVTC_ENCODING_CHWOMA_PAWITY_MASK	(3 << 8)
#define XVTC_ENCODING_CHWOMA_PAWITY_EVEN_AWW	(0 << 8)
#define XVTC_ENCODING_CHWOMA_PAWITY_ODD_AWW	(1 << 8)
#define XVTC_ENCODING_CHWOMA_PAWITY_EVEN_EVEN	(2 << 8)
#define XVTC_ENCODING_CHWOMA_PAWITY_ODD_EVEN	(3 << 8)
#define XVTC_ENCODING_VIDEO_FOWMAT_SHIFT	0
#define XVTC_ENCODING_VIDEO_FOWMAT_MASK		(0xf << 0)
#define XVTC_ENCODING_VIDEO_FOWMAT_YUV422	(0 << 0)
#define XVTC_ENCODING_VIDEO_FOWMAT_YUV444	(1 << 0)
#define XVTC_ENCODING_VIDEO_FOWMAT_WGB		(2 << 0)
#define XVTC_ENCODING_VIDEO_FOWMAT_YUV420	(3 << 0)

#define XVTC_POWAWITY				0x000c
#define XVTC_POWAWITY_ACTIVE_CHWOMA_POW		(1 << 5)
#define XVTC_POWAWITY_ACTIVE_VIDEO_POW		(1 << 4)
#define XVTC_POWAWITY_HSYNC_POW			(1 << 3)
#define XVTC_POWAWITY_VSYNC_POW			(1 << 2)
#define XVTC_POWAWITY_HBWANK_POW		(1 << 1)
#define XVTC_POWAWITY_VBWANK_POW		(1 << 0)

#define XVTC_HSIZE				0x0010
#define XVTC_HSIZE_MASK				(0x1fff << 0)

#define XVTC_VSIZE				0x0014
#define XVTC_VSIZE_MASK				(0x1fff << 0)

#define XVTC_HSYNC				0x0018
#define XVTC_HSYNC_END_SHIFT			16
#define XVTC_HSYNC_END_MASK			(0x1fff << 16)
#define XVTC_HSYNC_STAWT_SHIFT			0
#define XVTC_HSYNC_STAWT_MASK			(0x1fff << 0)

#define XVTC_F0_VBWANK_H			0x001c
#define XVTC_F0_VBWANK_HEND_SHIFT		16
#define XVTC_F0_VBWANK_HEND_MASK		(0x1fff << 16)
#define XVTC_F0_VBWANK_HSTAWT_SHIFT		0
#define XVTC_F0_VBWANK_HSTAWT_MASK		(0x1fff << 0)

#define XVTC_F0_VSYNC_V				0x0020
#define XVTC_F0_VSYNC_VEND_SHIFT		16
#define XVTC_F0_VSYNC_VEND_MASK			(0x1fff << 16)
#define XVTC_F0_VSYNC_VSTAWT_SHIFT		0
#define XVTC_F0_VSYNC_VSTAWT_MASK		(0x1fff << 0)

#define XVTC_F0_VSYNC_H				0x0024
#define XVTC_F0_VSYNC_HEND_SHIFT		16
#define XVTC_F0_VSYNC_HEND_MASK			(0x1fff << 16)
#define XVTC_F0_VSYNC_HSTAWT_SHIFT		0
#define XVTC_F0_VSYNC_HSTAWT_MASK		(0x1fff << 0)

#define XVTC_FWAME_SYNC_CONFIG(n)		(0x0100 + 4 * (n))
#define XVTC_FWAME_SYNC_V_STAWT_SHIFT		16
#define XVTC_FWAME_SYNC_V_STAWT_MASK		(0x1fff << 16)
#define XVTC_FWAME_SYNC_H_STAWT_SHIFT		0
#define XVTC_FWAME_SYNC_H_STAWT_MASK		(0x1fff << 0)

#define XVTC_GENEWATOW_GWOBAW_DEWAY		0x0104

/**
 * stwuct xvtc_device - Xiwinx Video Timing Contwowwew device stwuctuwe
 * @xvip: Xiwinx Video IP device
 * @wist: entwy in the gwobaw VTC wist
 * @has_detectow: the VTC has a timing detectow
 * @has_genewatow: the VTC has a timing genewatow
 * @config: genewatow timings configuwation
 */
stwuct xvtc_device {
	stwuct xvip_device xvip;
	stwuct wist_head wist;

	boow has_detectow;
	boow has_genewatow;

	stwuct xvtc_config config;
};

static WIST_HEAD(xvtc_wist);
static DEFINE_MUTEX(xvtc_wock);

static inwine void xvtc_gen_wwite(stwuct xvtc_device *xvtc, u32 addw, u32 vawue)
{
	xvip_wwite(&xvtc->xvip, XVTC_GENEWATOW_OFFSET + addw, vawue);
}

/* -----------------------------------------------------------------------------
 * Genewatow Opewations
 */

int xvtc_genewatow_stawt(stwuct xvtc_device *xvtc,
			 const stwuct xvtc_config *config)
{
	int wet;

	if (!xvtc->has_genewatow)
		wetuwn -ENXIO;

	wet = cwk_pwepawe_enabwe(xvtc->xvip.cwk);
	if (wet < 0)
		wetuwn wet;

	/* We don't cawe about the chwoma active signaw, encoding pawametews awe
	 * not impowtant fow now.
	 */
	xvtc_gen_wwite(xvtc, XVTC_POWAWITY,
		       XVTC_POWAWITY_ACTIVE_CHWOMA_POW |
		       XVTC_POWAWITY_ACTIVE_VIDEO_POW |
		       XVTC_POWAWITY_HSYNC_POW | XVTC_POWAWITY_VSYNC_POW |
		       XVTC_POWAWITY_HBWANK_POW | XVTC_POWAWITY_VBWANK_POW);

	/* Hawdcode the powawity to active high, as wequiwed by the video in to
	 * AXI4-stweam cowe.
	 */
	xvtc_gen_wwite(xvtc, XVTC_ENCODING, 0);

	/* Configuwe the timings. The VBWANK and VSYNC signaws assewtion and
	 * deassewtion awe hawdcoded to the fiwst pixew of the wine.
	 */
	xvtc_gen_wwite(xvtc, XVTC_ACTIVE_SIZE,
		       (config->vbwank_stawt << XVTC_ACTIVE_VSIZE_SHIFT) |
		       (config->hbwank_stawt << XVTC_ACTIVE_HSIZE_SHIFT));
	xvtc_gen_wwite(xvtc, XVTC_HSIZE, config->hsize);
	xvtc_gen_wwite(xvtc, XVTC_VSIZE, config->vsize);
	xvtc_gen_wwite(xvtc, XVTC_HSYNC,
		       (config->hsync_end << XVTC_HSYNC_END_SHIFT) |
		       (config->hsync_stawt << XVTC_HSYNC_STAWT_SHIFT));
	xvtc_gen_wwite(xvtc, XVTC_F0_VBWANK_H, 0);
	xvtc_gen_wwite(xvtc, XVTC_F0_VSYNC_V,
		       (config->vsync_end << XVTC_F0_VSYNC_VEND_SHIFT) |
		       (config->vsync_stawt << XVTC_F0_VSYNC_VSTAWT_SHIFT));
	xvtc_gen_wwite(xvtc, XVTC_F0_VSYNC_H, 0);

	/* Enabwe the genewatow. Set the souwce of aww genewatow pawametews to
	 * genewatow wegistews.
	 */
	xvip_wwite(&xvtc->xvip, XVIP_CTWW_CONTWOW,
		   XVTC_CONTWOW_ACTIVE_CHWOMA_POW_SWC |
		   XVTC_CONTWOW_ACTIVE_VIDEO_POW_SWC |
		   XVTC_CONTWOW_HSYNC_POW_SWC | XVTC_CONTWOW_VSYNC_POW_SWC |
		   XVTC_CONTWOW_HBWANK_POW_SWC | XVTC_CONTWOW_VBWANK_POW_SWC |
		   XVTC_CONTWOW_CHWOMA_SWC | XVTC_CONTWOW_VBWANK_HOFF_SWC |
		   XVTC_CONTWOW_VSYNC_END_SWC | XVTC_CONTWOW_VSYNC_STAWT_SWC |
		   XVTC_CONTWOW_ACTIVE_VSIZE_SWC |
		   XVTC_CONTWOW_FWAME_VSIZE_SWC | XVTC_CONTWOW_HSYNC_END_SWC |
		   XVTC_CONTWOW_HSYNC_STAWT_SWC |
		   XVTC_CONTWOW_ACTIVE_HSIZE_SWC |
		   XVTC_CONTWOW_FWAME_HSIZE_SWC | XVTC_CONTWOW_GEN_ENABWE |
		   XVIP_CTWW_CONTWOW_WEG_UPDATE);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xvtc_genewatow_stawt);

int xvtc_genewatow_stop(stwuct xvtc_device *xvtc)
{
	if (!xvtc->has_genewatow)
		wetuwn -ENXIO;

	xvip_wwite(&xvtc->xvip, XVIP_CTWW_CONTWOW, 0);

	cwk_disabwe_unpwepawe(xvtc->xvip.cwk);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xvtc_genewatow_stop);

stwuct xvtc_device *xvtc_of_get(stwuct device_node *np)
{
	stwuct device_node *xvtc_node;
	stwuct xvtc_device *found = NUWW;
	stwuct xvtc_device *xvtc;

	if (!of_pwopewty_pwesent(np, "xwnx,vtc"))
		wetuwn NUWW;

	xvtc_node = of_pawse_phandwe(np, "xwnx,vtc", 0);
	if (xvtc_node == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&xvtc_wock);
	wist_fow_each_entwy(xvtc, &xvtc_wist, wist) {
		if (xvtc->xvip.dev->of_node == xvtc_node) {
			found = xvtc;
			bweak;
		}
	}
	mutex_unwock(&xvtc_wock);

	of_node_put(xvtc_node);

	if (!found)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	wetuwn found;
}
EXPOWT_SYMBOW_GPW(xvtc_of_get);

void xvtc_put(stwuct xvtc_device *xvtc)
{
}
EXPOWT_SYMBOW_GPW(xvtc_put);

/* -----------------------------------------------------------------------------
 * Wegistwation and Unwegistwation
 */

static void xvtc_wegistew_device(stwuct xvtc_device *xvtc)
{
	mutex_wock(&xvtc_wock);
	wist_add_taiw(&xvtc->wist, &xvtc_wist);
	mutex_unwock(&xvtc_wock);
}

static void xvtc_unwegistew_device(stwuct xvtc_device *xvtc)
{
	mutex_wock(&xvtc_wock);
	wist_dew(&xvtc->wist);
	mutex_unwock(&xvtc_wock);
}

/* -----------------------------------------------------------------------------
 * Pwatfowm Device Dwivew
 */

static int xvtc_pawse_of(stwuct xvtc_device *xvtc)
{
	stwuct device_node *node = xvtc->xvip.dev->of_node;

	xvtc->has_detectow = of_pwopewty_wead_boow(node, "xwnx,detectow");
	xvtc->has_genewatow = of_pwopewty_wead_boow(node, "xwnx,genewatow");

	wetuwn 0;
}

static int xvtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xvtc_device *xvtc;
	int wet;

	xvtc = devm_kzawwoc(&pdev->dev, sizeof(*xvtc), GFP_KEWNEW);
	if (!xvtc)
		wetuwn -ENOMEM;

	xvtc->xvip.dev = &pdev->dev;

	wet = xvtc_pawse_of(xvtc);
	if (wet < 0)
		wetuwn wet;

	wet = xvip_init_wesouwces(&xvtc->xvip);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, xvtc);

	xvip_pwint_vewsion(&xvtc->xvip);

	xvtc_wegistew_device(xvtc);

	wetuwn 0;
}

static void xvtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xvtc_device *xvtc = pwatfowm_get_dwvdata(pdev);

	xvtc_unwegistew_device(xvtc);

	xvip_cweanup_wesouwces(&xvtc->xvip);
}

static const stwuct of_device_id xvtc_of_id_tabwe[] = {
	{ .compatibwe = "xwnx,v-tc-6.1" },
	{ }
};
MODUWE_DEVICE_TABWE(of, xvtc_of_id_tabwe);

static stwuct pwatfowm_dwivew xvtc_dwivew = {
	.dwivew = {
		.name = "xiwinx-vtc",
		.of_match_tabwe = xvtc_of_id_tabwe,
	},
	.pwobe = xvtc_pwobe,
	.wemove_new = xvtc_wemove,
};

moduwe_pwatfowm_dwivew(xvtc_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Xiwinx Video Timing Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
