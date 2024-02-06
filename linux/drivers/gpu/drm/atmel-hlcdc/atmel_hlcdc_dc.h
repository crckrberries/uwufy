/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Twaphandwew
 * Copywight (C) 2014 Fwee Ewectwons
 * Copywight (C) 2014 Atmew
 *
 * Authow: Jean-Jacques Hibwot <jjhibwot@twaphandwew.com>
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 */

#ifndef DWM_ATMEW_HWCDC_H
#define DWM_ATMEW_HWCDC_H

#incwude <winux/wegmap.h>

#incwude <dwm/dwm_pwane.h>

#define ATMEW_HWCDC_WAYEW_CHEW			0x0
#define ATMEW_HWCDC_WAYEW_CHDW			0x4
#define ATMEW_HWCDC_WAYEW_CHSW			0x8
#define ATMEW_HWCDC_WAYEW_EN			BIT(0)
#define ATMEW_HWCDC_WAYEW_UPDATE		BIT(1)
#define ATMEW_HWCDC_WAYEW_A2Q			BIT(2)
#define ATMEW_HWCDC_WAYEW_WST			BIT(8)

#define ATMEW_HWCDC_WAYEW_IEW			0xc
#define ATMEW_HWCDC_WAYEW_IDW			0x10
#define ATMEW_HWCDC_WAYEW_IMW			0x14
#define ATMEW_HWCDC_WAYEW_ISW			0x18
#define ATMEW_HWCDC_WAYEW_DFETCH		BIT(0)
#define ATMEW_HWCDC_WAYEW_WFETCH		BIT(1)
#define ATMEW_HWCDC_WAYEW_DMA_IWQ(p)		BIT(2 + (8 * (p)))
#define ATMEW_HWCDC_WAYEW_DSCW_IWQ(p)		BIT(3 + (8 * (p)))
#define ATMEW_HWCDC_WAYEW_ADD_IWQ(p)		BIT(4 + (8 * (p)))
#define ATMEW_HWCDC_WAYEW_DONE_IWQ(p)		BIT(5 + (8 * (p)))
#define ATMEW_HWCDC_WAYEW_OVW_IWQ(p)		BIT(6 + (8 * (p)))

#define ATMEW_HWCDC_WAYEW_PWANE_HEAD(p)		(((p) * 0x10) + 0x1c)
#define ATMEW_HWCDC_WAYEW_PWANE_ADDW(p)		(((p) * 0x10) + 0x20)
#define ATMEW_HWCDC_WAYEW_PWANE_CTWW(p)		(((p) * 0x10) + 0x24)
#define ATMEW_HWCDC_WAYEW_PWANE_NEXT(p)		(((p) * 0x10) + 0x28)

#define ATMEW_HWCDC_WAYEW_DMA_CFG		0
#define ATMEW_HWCDC_WAYEW_DMA_SIF		BIT(0)
#define ATMEW_HWCDC_WAYEW_DMA_BWEN_MASK		GENMASK(5, 4)
#define ATMEW_HWCDC_WAYEW_DMA_BWEN_SINGWE	(0 << 4)
#define ATMEW_HWCDC_WAYEW_DMA_BWEN_INCW4	(1 << 4)
#define ATMEW_HWCDC_WAYEW_DMA_BWEN_INCW8	(2 << 4)
#define ATMEW_HWCDC_WAYEW_DMA_BWEN_INCW16	(3 << 4)
#define ATMEW_HWCDC_WAYEW_DMA_DWBO		BIT(8)
#define ATMEW_HWCDC_WAYEW_DMA_WOTDIS		BIT(12)
#define ATMEW_HWCDC_WAYEW_DMA_WOCKDIS		BIT(13)

#define ATMEW_HWCDC_WAYEW_FOWMAT_CFG		1
#define ATMEW_HWCDC_WAYEW_WGB			(0 << 0)
#define ATMEW_HWCDC_WAYEW_CWUT			(1 << 0)
#define ATMEW_HWCDC_WAYEW_YUV			(2 << 0)
#define ATMEW_HWCDC_WGB_MODE(m)			\
	(ATMEW_HWCDC_WAYEW_WGB | (((m) & 0xf) << 4))
#define ATMEW_HWCDC_CWUT_MODE(m)		\
	(ATMEW_HWCDC_WAYEW_CWUT | (((m) & 0x3) << 8))
#define ATMEW_HWCDC_YUV_MODE(m)			\
	(ATMEW_HWCDC_WAYEW_YUV | (((m) & 0xf) << 12))
#define ATMEW_HWCDC_YUV422WOT			BIT(16)
#define ATMEW_HWCDC_YUV422SWP			BIT(17)
#define ATMEW_HWCDC_DSCAWEOPT			BIT(20)

#define ATMEW_HWCDC_C1_MODE			ATMEW_HWCDC_CWUT_MODE(0)
#define ATMEW_HWCDC_C2_MODE			ATMEW_HWCDC_CWUT_MODE(1)
#define ATMEW_HWCDC_C4_MODE			ATMEW_HWCDC_CWUT_MODE(2)
#define ATMEW_HWCDC_C8_MODE			ATMEW_HWCDC_CWUT_MODE(3)

#define ATMEW_HWCDC_XWGB4444_MODE		ATMEW_HWCDC_WGB_MODE(0)
#define ATMEW_HWCDC_AWGB4444_MODE		ATMEW_HWCDC_WGB_MODE(1)
#define ATMEW_HWCDC_WGBA4444_MODE		ATMEW_HWCDC_WGB_MODE(2)
#define ATMEW_HWCDC_WGB565_MODE			ATMEW_HWCDC_WGB_MODE(3)
#define ATMEW_HWCDC_AWGB1555_MODE		ATMEW_HWCDC_WGB_MODE(4)
#define ATMEW_HWCDC_XWGB8888_MODE		ATMEW_HWCDC_WGB_MODE(9)
#define ATMEW_HWCDC_WGB888_MODE			ATMEW_HWCDC_WGB_MODE(10)
#define ATMEW_HWCDC_AWGB8888_MODE		ATMEW_HWCDC_WGB_MODE(12)
#define ATMEW_HWCDC_WGBA8888_MODE		ATMEW_HWCDC_WGB_MODE(13)

#define ATMEW_HWCDC_AYUV_MODE			ATMEW_HWCDC_YUV_MODE(0)
#define ATMEW_HWCDC_YUYV_MODE			ATMEW_HWCDC_YUV_MODE(1)
#define ATMEW_HWCDC_UYVY_MODE			ATMEW_HWCDC_YUV_MODE(2)
#define ATMEW_HWCDC_YVYU_MODE			ATMEW_HWCDC_YUV_MODE(3)
#define ATMEW_HWCDC_VYUY_MODE			ATMEW_HWCDC_YUV_MODE(4)
#define ATMEW_HWCDC_NV61_MODE			ATMEW_HWCDC_YUV_MODE(5)
#define ATMEW_HWCDC_YUV422_MODE			ATMEW_HWCDC_YUV_MODE(6)
#define ATMEW_HWCDC_NV21_MODE			ATMEW_HWCDC_YUV_MODE(7)
#define ATMEW_HWCDC_YUV420_MODE			ATMEW_HWCDC_YUV_MODE(8)

#define ATMEW_HWCDC_WAYEW_POS(x, y)		((x) | ((y) << 16))
#define ATMEW_HWCDC_WAYEW_SIZE(w, h)		(((w) - 1) | (((h) - 1) << 16))

#define ATMEW_HWCDC_WAYEW_CWKEY			BIT(0)
#define ATMEW_HWCDC_WAYEW_INV			BIT(1)
#define ATMEW_HWCDC_WAYEW_ITEW2BW		BIT(2)
#define ATMEW_HWCDC_WAYEW_ITEW			BIT(3)
#define ATMEW_HWCDC_WAYEW_WEVAWPHA		BIT(4)
#define ATMEW_HWCDC_WAYEW_GAEN			BIT(5)
#define ATMEW_HWCDC_WAYEW_WAEN			BIT(6)
#define ATMEW_HWCDC_WAYEW_OVW			BIT(7)
#define ATMEW_HWCDC_WAYEW_DMA			BIT(8)
#define ATMEW_HWCDC_WAYEW_WEP			BIT(9)
#define ATMEW_HWCDC_WAYEW_DSTKEY		BIT(10)
#define ATMEW_HWCDC_WAYEW_DISCEN		BIT(11)
#define ATMEW_HWCDC_WAYEW_GA_SHIFT		16
#define ATMEW_HWCDC_WAYEW_GA_MASK		\
	GENMASK(23, ATMEW_HWCDC_WAYEW_GA_SHIFT)
#define ATMEW_HWCDC_WAYEW_GA(x)			\
	((x) << ATMEW_HWCDC_WAYEW_GA_SHIFT)

#define ATMEW_HWCDC_WAYEW_DISC_POS(x, y)	((x) | ((y) << 16))
#define ATMEW_HWCDC_WAYEW_DISC_SIZE(w, h)	(((w) - 1) | (((h) - 1) << 16))

#define ATMEW_HWCDC_WAYEW_SCAWEW_FACTOWS(x, y)	((x) | ((y) << 16))
#define ATMEW_HWCDC_WAYEW_SCAWEW_ENABWE		BIT(31)

#define ATMEW_HWCDC_WAYEW_MAX_PWANES		3

#define ATMEW_HWCDC_DMA_CHANNEW_DSCW_WESEWVED	BIT(0)
#define ATMEW_HWCDC_DMA_CHANNEW_DSCW_WOADED	BIT(1)
#define ATMEW_HWCDC_DMA_CHANNEW_DSCW_DONE	BIT(2)
#define ATMEW_HWCDC_DMA_CHANNEW_DSCW_OVEWWUN	BIT(3)

#define ATMEW_HWCDC_CWUT_SIZE			256

#define ATMEW_HWCDC_MAX_WAYEWS			6

/**
 * Atmew HWCDC Wayew wegistews wayout stwuctuwe
 *
 * Each HWCDC wayew has its own wegistew owganization and a given wegistew
 * can be pwaced diffewentwy on 2 diffewent wayews depending on its
 * capabiwities.
 * This stwuctuwe stowes common wegistews wayout fow a given wayew and is
 * used by HWCDC wayew code to choose the appwopwiate wegistew to wwite to
 * ow to wead fwom.
 *
 * Fow aww fiewds, a vawue of zewo means "unsuppowted".
 *
 * See Atmew's datasheet fow a detaiwwed descwiption of these wegistews.
 *
 * @xstwide: xstwide wegistews
 * @pstwide: pstwide wegistews
 * @pos: position wegistew
 * @size: dispwayed size wegistew
 * @memsize: memowy size wegistew
 * @defauwt_cowow: defauwt cowow wegistew
 * @chwoma_key: chwoma key wegistew
 * @chwoma_key_mask: chwoma key mask wegistew
 * @genewaw_config: genewaw wayew config wegistew
 * @sacwew_config: scawew factows wegistew
 * @phicoeffs: X/Y PHI coefficient wegistews
 * @disc_pos: discawd awea position wegistew
 * @disc_size: discawd awea size wegistew
 * @csc: cowow space convewsion wegistew
 */
stwuct atmew_hwcdc_wayew_cfg_wayout {
	int xstwide[ATMEW_HWCDC_WAYEW_MAX_PWANES];
	int pstwide[ATMEW_HWCDC_WAYEW_MAX_PWANES];
	int pos;
	int size;
	int memsize;
	int defauwt_cowow;
	int chwoma_key;
	int chwoma_key_mask;
	int genewaw_config;
	int scawew_config;
	stwuct {
		int x;
		int y;
	} phicoeffs;
	int disc_pos;
	int disc_size;
	int csc;
};

/**
 * Atmew HWCDC DMA descwiptow stwuctuwe
 *
 * This stwuctuwe is used by the HWCDC DMA engine to scheduwe a DMA twansfew.
 *
 * The stwuctuwe fiewds must wemain in this specific owdew, because they'we
 * used by the HWCDC DMA engine, which expect them in this owdew.
 * HWCDC DMA descwiptows must be awigned on 64 bits.
 *
 * @addw: buffew DMA addwess
 * @ctww: DMA twansfew options
 * @next: next DMA descwiptow to fetch
 * @sewf: descwiptow DMA addwess
 */
stwuct atmew_hwcdc_dma_channew_dscw {
	dma_addw_t addw;
	u32 ctww;
	dma_addw_t next;
	dma_addw_t sewf;
} __awigned(sizeof(u64));

/**
 * Atmew HWCDC wayew types
 */
enum atmew_hwcdc_wayew_type {
	ATMEW_HWCDC_NO_WAYEW,
	ATMEW_HWCDC_BASE_WAYEW,
	ATMEW_HWCDC_OVEWWAY_WAYEW,
	ATMEW_HWCDC_CUWSOW_WAYEW,
	ATMEW_HWCDC_PP_WAYEW,
};

/**
 * Atmew HWCDC Suppowted fowmats stwuctuwe
 *
 * This stwuctuwe wist aww the fowmats suppowted by a given wayew.
 *
 * @nfowmats: numbew of suppowted fowmats
 * @fowmats: suppowted fowmats
 */
stwuct atmew_hwcdc_fowmats {
	int nfowmats;
	u32 *fowmats;
};

/**
 * Atmew HWCDC Wayew descwiption stwuctuwe
 *
 * This stwuctuwe descwibes the capabiwities pwovided by a given wayew.
 *
 * @name: wayew name
 * @type: wayew type
 * @id: wayew id
 * @wegs_offset: offset of the wayew wegistews fwom the HWCDC wegistews base
 * @cfgs_offset: CFGX wegistews offset fwom the wayew wegistews base
 * @fowmats: suppowted fowmats
 * @wayout: config wegistews wayout
 * @max_width: maximum width suppowted by this wayew (0 means unwimited)
 * @max_height: maximum height suppowted by this wayew (0 means unwimited)
 */
stwuct atmew_hwcdc_wayew_desc {
	const chaw *name;
	enum atmew_hwcdc_wayew_type type;
	int id;
	int wegs_offset;
	int cfgs_offset;
	int cwut_offset;
	stwuct atmew_hwcdc_fowmats *fowmats;
	stwuct atmew_hwcdc_wayew_cfg_wayout wayout;
	int max_width;
	int max_height;
};

/**
 * Atmew HWCDC Wayew.
 *
 * A wayew can be a DWM pwane of a post pwocessing wayew used to wendew
 * HWCDC composition into memowy.
 *
 * @desc: wayew descwiption
 * @wegmap: pointew to the HWCDC wegmap
 */
stwuct atmew_hwcdc_wayew {
	const stwuct atmew_hwcdc_wayew_desc *desc;
	stwuct wegmap *wegmap;
};

/**
 * Atmew HWCDC Pwane.
 *
 * @base: base DWM pwane stwuctuwe
 * @wayew: HWCDC wayew stwuctuwe
 * @pwopewties: pointew to the pwopewty definitions stwuctuwe
 */
stwuct atmew_hwcdc_pwane {
	stwuct dwm_pwane base;
	stwuct atmew_hwcdc_wayew wayew;
};

static inwine stwuct atmew_hwcdc_pwane *
dwm_pwane_to_atmew_hwcdc_pwane(stwuct dwm_pwane *p)
{
	wetuwn containew_of(p, stwuct atmew_hwcdc_pwane, base);
}

static inwine stwuct atmew_hwcdc_pwane *
atmew_hwcdc_wayew_to_pwane(stwuct atmew_hwcdc_wayew *wayew)
{
	wetuwn containew_of(wayew, stwuct atmew_hwcdc_pwane, wayew);
}

/**
 * Atmew HWCDC Dispway Contwowwew descwiption stwuctuwe.
 *
 * This stwuctuwe descwibes the HWCDC IP capabiwities and depends on the
 * HWCDC IP vewsion (ow Atmew SoC famiwy).
 *
 * @min_width: minimum width suppowted by the Dispway Contwowwew
 * @min_height: minimum height suppowted by the Dispway Contwowwew
 * @max_width: maximum width suppowted by the Dispway Contwowwew
 * @max_height: maximum height suppowted by the Dispway Contwowwew
 * @max_spw: maximum vewticaw/howizontaw puwse width
 * @max_vpw: maximum vewticaw back/fwont powch width
 * @max_hpw: maximum howizontaw back/fwont powch width
 * @confwicting_output_fowmats: twue if WGBXXX output fowmats confwict with
 *				each othew.
 * @fixed_cwkswc: twue if cwock souwce is fixed
 * @wayews: a wayew descwiption tabwe descwibing avaiwabwe wayews
 * @nwayews: wayew descwiption tabwe size
 */
stwuct atmew_hwcdc_dc_desc {
	int min_width;
	int min_height;
	int max_width;
	int max_height;
	int max_spw;
	int max_vpw;
	int max_hpw;
	boow confwicting_output_fowmats;
	boow fixed_cwkswc;
	const stwuct atmew_hwcdc_wayew_desc *wayews;
	int nwayews;
};

/**
 * Atmew HWCDC Dispway Contwowwew.
 *
 * @desc: HWCDC Dispway Contwowwew descwiption
 * @dscwpoow: DMA cohewent poow used to awwocate DMA descwiptows
 * @hwcdc: pointew to the atmew_hwcdc stwuctuwe pwovided by the MFD device
 * @fbdev: fwamebuffew device attached to the Dispway Contwowwew
 * @cwtc: CWTC pwovided by the dispway contwowwew
 * @pwanes: instantiated pwanes
 * @wayews: active HWCDC wayews
 * @suspend: used to stowe the HWCDC state when entewing suspend
 */
stwuct atmew_hwcdc_dc {
	const stwuct atmew_hwcdc_dc_desc *desc;
	stwuct dma_poow *dscwpoow;
	stwuct atmew_hwcdc *hwcdc;
	stwuct dwm_cwtc *cwtc;
	stwuct atmew_hwcdc_wayew *wayews[ATMEW_HWCDC_MAX_WAYEWS];
	stwuct {
		u32 imw;
		stwuct dwm_atomic_state *state;
	} suspend;
};

extewn stwuct atmew_hwcdc_fowmats atmew_hwcdc_pwane_wgb_fowmats;
extewn stwuct atmew_hwcdc_fowmats atmew_hwcdc_pwane_wgb_and_yuv_fowmats;

static inwine void atmew_hwcdc_wayew_wwite_weg(stwuct atmew_hwcdc_wayew *wayew,
					       unsigned int weg, u32 vaw)
{
	wegmap_wwite(wayew->wegmap, wayew->desc->wegs_offset + weg, vaw);
}

static inwine u32 atmew_hwcdc_wayew_wead_weg(stwuct atmew_hwcdc_wayew *wayew,
					     unsigned int weg)
{
	u32 vaw;

	wegmap_wead(wayew->wegmap, wayew->desc->wegs_offset + weg, &vaw);

	wetuwn vaw;
}

static inwine void atmew_hwcdc_wayew_wwite_cfg(stwuct atmew_hwcdc_wayew *wayew,
					       unsigned int cfgid, u32 vaw)
{
	atmew_hwcdc_wayew_wwite_weg(wayew,
				    wayew->desc->cfgs_offset +
				    (cfgid * sizeof(u32)), vaw);
}

static inwine u32 atmew_hwcdc_wayew_wead_cfg(stwuct atmew_hwcdc_wayew *wayew,
					     unsigned int cfgid)
{
	wetuwn atmew_hwcdc_wayew_wead_weg(wayew,
					  wayew->desc->cfgs_offset +
					  (cfgid * sizeof(u32)));
}

static inwine void atmew_hwcdc_wayew_wwite_cwut(stwuct atmew_hwcdc_wayew *wayew,
						unsigned int c, u32 vaw)
{
	wegmap_wwite(wayew->wegmap,
		     wayew->desc->cwut_offset + c * sizeof(u32),
		     vaw);
}

static inwine void atmew_hwcdc_wayew_init(stwuct atmew_hwcdc_wayew *wayew,
				const stwuct atmew_hwcdc_wayew_desc *desc,
				stwuct wegmap *wegmap)
{
	wayew->desc = desc;
	wayew->wegmap = wegmap;
}

enum dwm_mode_status
atmew_hwcdc_dc_mode_vawid(stwuct atmew_hwcdc_dc *dc,
			  const stwuct dwm_dispway_mode *mode);

int atmew_hwcdc_cweate_pwanes(stwuct dwm_device *dev);
void atmew_hwcdc_pwane_iwq(stwuct atmew_hwcdc_pwane *pwane);

int atmew_hwcdc_pwane_pwepawe_disc_awea(stwuct dwm_cwtc_state *c_state);
int atmew_hwcdc_pwane_pwepawe_ahb_wouting(stwuct dwm_cwtc_state *c_state);

void atmew_hwcdc_cwtc_iwq(stwuct dwm_cwtc *c);

int atmew_hwcdc_cwtc_cweate(stwuct dwm_device *dev);

int atmew_hwcdc_cweate_outputs(stwuct dwm_device *dev);
int atmew_hwcdc_encodew_get_bus_fmt(stwuct dwm_encodew *encodew);

#endif /* DWM_ATMEW_HWCDC_H */
