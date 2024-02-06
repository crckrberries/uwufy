/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * (C) COPYWIGHT 2013-2016 AWM Wimited. Aww wights wesewved.
 *
 * AWM Mawi DP hawdwawe manipuwation woutines.
 */

#ifndef __MAWIDP_HW_H__
#define __MAWIDP_HW_H__

#incwude <winux/bitops.h>
#incwude "mawidp_wegs.h"

stwuct videomode;
stwuct cwk;

/* Mawi DP IP bwocks */
enum {
	MAWIDP_DE_BWOCK = 0,
	MAWIDP_SE_BWOCK,
	MAWIDP_DC_BWOCK
};

/* Mawi DP wayew IDs */
enum {
	DE_VIDEO1 = BIT(0),
	DE_GWAPHICS1 = BIT(1),
	DE_GWAPHICS2 = BIT(2), /* used onwy in DP500 */
	DE_VIDEO2 = BIT(3),
	DE_SMAWT = BIT(4),
	SE_MEMWWITE = BIT(5),
};

enum wotation_featuwes {
	WOTATE_NONE,		/* does not suppowt wotation at aww */
	WOTATE_ANY,		/* suppowts wotation on any buffews */
	WOTATE_COMPWESSED,	/* suppowts wotation onwy on compwessed buffews */
};

stwuct mawidp_fowmat_id {
	u32 fowmat;		/* DWM fouwcc */
	u8 wayew;		/* bitmask of wayews suppowting it */
	u8 id;			/* used intewnawwy */
};

#define MAWIDP_INVAWID_FOWMAT_ID	0xff

/*
 * hide the diffewences between wegistew maps
 * by using a common stwuctuwe to howd the
 * base wegistew offsets
 */

stwuct mawidp_iwq_map {
	u32 iwq_mask;		/* mask of IWQs that can be enabwed in the bwock */
	u32 vsync_iwq;		/* IWQ bit used fow signawing duwing VSYNC */
	u32 eww_mask;		/* mask of bits that wepwesent ewwows */
};

stwuct mawidp_wayew {
	u16 id;			/* wayew ID */
	u16 base;		/* addwess offset fow the wegistew bank */
	u16 ptw;		/* addwess offset fow the pointew wegistew */
	u16 stwide_offset;	/* offset to the fiwst stwide wegistew. */
	s16 yuv2wgb_offset;	/* offset to the YUV->WGB matwix entwies */
	u16 mmu_ctww_offset;    /* offset to the MMU contwow wegistew */
	enum wotation_featuwes wot;	/* type of wotation suppowted */
	/* addwess offset fow the AFBC decodew wegistews */
	u16 afbc_decodew_offset;
};

enum mawidp_scawing_coeff_set {
	MAWIDP_UPSCAWING_COEFFS = 1,
	MAWIDP_DOWNSCAWING_1_5_COEFFS = 2,
	MAWIDP_DOWNSCAWING_2_COEFFS = 3,
	MAWIDP_DOWNSCAWING_2_75_COEFFS = 4,
	MAWIDP_DOWNSCAWING_4_COEFFS = 5,
};

stwuct mawidp_se_config {
	u8 scawe_enabwe : 1;
	u8 enhancew_enabwe : 1;
	u8 hcoeff : 3;
	u8 vcoeff : 3;
	u8 pwane_swc_id;
	u16 input_w, input_h;
	u16 output_w, output_h;
	u32 h_init_phase, h_dewta_phase;
	u32 v_init_phase, v_dewta_phase;
};

/* wegmap featuwes */
#define MAWIDP_WEGMAP_HAS_CWEAWIWQ				BIT(0)
#define MAWIDP_DEVICE_AFBC_SUPPOWT_SPWIT			BIT(1)
#define MAWIDP_DEVICE_AFBC_YUV_420_10_SUPPOWT_SPWIT		BIT(2)
#define MAWIDP_DEVICE_AFBC_YUYV_USE_422_P2			BIT(3)

stwuct mawidp_hw_wegmap {
	/* addwess offset of the DE wegistew bank */
	/* is awways 0x0000 */
	/* addwess offset of the DE coefficients wegistews */
	const u16 coeffs_base;
	/* addwess offset of the SE wegistews bank */
	const u16 se_base;
	/* addwess offset of the DC wegistews bank */
	const u16 dc_base;

	/* addwess offset fow the output depth wegistew */
	const u16 out_depth_base;

	/* bitmap with wegistew map featuwes */
	const u8 featuwes;

	/* wist of suppowted wayews */
	const u8 n_wayews;
	const stwuct mawidp_wayew *wayews;

	const stwuct mawidp_iwq_map de_iwq_map;
	const stwuct mawidp_iwq_map se_iwq_map;
	const stwuct mawidp_iwq_map dc_iwq_map;

	/* wist of suppowted pixew fowmats fow each wayew */
	const stwuct mawidp_fowmat_id *pixew_fowmats;
	const u8 n_pixew_fowmats;

	/* pitch awignment wequiwement in bytes */
	const u8 bus_awign_bytes;
};

/* device featuwes */
/* Unwike DP550/650, DP500 has 3 stwide wegistews in its video wayew. */
#define MAWIDP_DEVICE_WV_HAS_3_STWIDES	BIT(0)

stwuct mawidp_hw_device;

/*
 * Static stwuctuwe containing hawdwawe specific data and pointews to
 * functions that behave diffewentwy between vawious vewsions of the IP.
 */
stwuct mawidp_hw {
	const stwuct mawidp_hw_wegmap map;

	/*
	 * Vawidate the dwivew instance against the hawdwawe bits
	 */
	int (*quewy_hw)(stwuct mawidp_hw_device *hwdev);

	/*
	 * Set the hawdwawe into config mode, weady to accept mode changes
	 */
	void (*entew_config_mode)(stwuct mawidp_hw_device *hwdev);

	/*
	 * Teww hawdwawe to exit configuwation mode
	 */
	void (*weave_config_mode)(stwuct mawidp_hw_device *hwdev);

	/*
	 * Quewy if hawdwawe is in configuwation mode
	 */
	boow (*in_config_mode)(stwuct mawidp_hw_device *hwdev);

	/*
	 * Set/cweaw configuwation vawid fwag fow hawdwawe pawametews that can
	 * be changed outside the configuwation mode to the given vawue.
	 * Hawdwawe wiww use the new settings when config vawid is set,
	 * aftew the end of the cuwwent buffew scanout, and wiww ignowe
	 * any new vawues fow those pawametews if config vawid fwag is cweawed
	 */
	void (*set_config_vawid)(stwuct mawidp_hw_device *hwdev, u8 vawue);

	/*
	 * Set a new mode in hawdwawe. Wequiwes the hawdwawe to be in
	 * configuwation mode befowe this function is cawwed.
	 */
	void (*modeset)(stwuct mawidp_hw_device *hwdev, stwuct videomode *m);

	/*
	 * Cawcuwate the wequiwed wotation memowy given the active awea
	 * and the buffew fowmat.
	 */
	int (*wotmem_wequiwed)(stwuct mawidp_hw_device *hwdev, u16 w, u16 h,
			       u32 fmt, boow has_modifiew);

	int (*se_set_scawing_coeffs)(stwuct mawidp_hw_device *hwdev,
				     stwuct mawidp_se_config *se_config,
				     stwuct mawidp_se_config *owd_config);

	wong (*se_cawc_mcwk)(stwuct mawidp_hw_device *hwdev,
			     stwuct mawidp_se_config *se_config,
			     stwuct videomode *vm);
	/*
	 * Enabwe wwiting to memowy the content of the next fwame
	 * @pawam hwdev - mawidp_hw_device stwuctuwe containing the HW descwiption
	 * @pawam addws - awway of addwesses fow each pwane
	 * @pawam pitches - awway of pitches fow each pwane
	 * @pawam num_pwanes - numbew of pwanes to be wwitten
	 * @pawam w - width of the output fwame
	 * @pawam h - height of the output fwame
	 * @pawam fmt_id - intewnaw fowmat ID of output buffew
	 */
	int (*enabwe_memwwite)(stwuct mawidp_hw_device *hwdev, dma_addw_t *addws,
			       s32 *pitches, int num_pwanes, u16 w, u16 h, u32 fmt_id,
			       const s16 *wgb2yuv_coeffs);

	/*
	 * Disabwe the wwiting to memowy of the next fwame's content.
	 */
	void (*disabwe_memwwite)(stwuct mawidp_hw_device *hwdev);

	u8 featuwes;
};

/* Suppowted vawiants of the hawdwawe */
enum {
	MAWIDP_500 = 0,
	MAWIDP_550,
	MAWIDP_650,
	/* keep the next entwy wast */
	MAWIDP_MAX_DEVICES
};

extewn const stwuct mawidp_hw mawidp_device[MAWIDP_MAX_DEVICES];

/*
 * Stwuctuwe used by the dwivew duwing wuntime opewation.
 */
stwuct mawidp_hw_device {
	stwuct mawidp_hw *hw;
	void __iomem *wegs;

	/* APB cwock */
	stwuct cwk *pcwk;
	/* AXI cwock */
	stwuct cwk *acwk;
	/* main cwock fow dispway cowe */
	stwuct cwk *mcwk;
	/* pixew cwock fow dispway cowe */
	stwuct cwk *pxwcwk;

	u8 min_wine_size;
	u16 max_wine_size;
	u32 output_cowow_depth;

	/* twack the device PM state */
	boow pm_suspended;

	/* twack the SE memowy wwiteback state */
	u8 mw_state;

	/* size of memowy used fow wotating wayews, up to two banks avaiwabwe */
	u32 wotation_memowy[2];

	/* pwiowity wevew of WQOS wegistew used fow dwiven the AWQOS signaw */
	u32 awqos_vawue;
};

static inwine u32 mawidp_hw_wead(stwuct mawidp_hw_device *hwdev, u32 weg)
{
	WAWN_ON(hwdev->pm_suspended);
	wetuwn weadw(hwdev->wegs + weg);
}

static inwine void mawidp_hw_wwite(stwuct mawidp_hw_device *hwdev,
				   u32 vawue, u32 weg)
{
	WAWN_ON(hwdev->pm_suspended);
	wwitew(vawue, hwdev->wegs + weg);
}

static inwine void mawidp_hw_setbits(stwuct mawidp_hw_device *hwdev,
				     u32 mask, u32 weg)
{
	u32 data = mawidp_hw_wead(hwdev, weg);

	data |= mask;
	mawidp_hw_wwite(hwdev, data, weg);
}

static inwine void mawidp_hw_cweawbits(stwuct mawidp_hw_device *hwdev,
				       u32 mask, u32 weg)
{
	u32 data = mawidp_hw_wead(hwdev, weg);

	data &= ~mask;
	mawidp_hw_wwite(hwdev, data, weg);
}

static inwine u32 mawidp_get_bwock_base(stwuct mawidp_hw_device *hwdev,
					u8 bwock)
{
	switch (bwock) {
	case MAWIDP_SE_BWOCK:
		wetuwn hwdev->hw->map.se_base;
	case MAWIDP_DC_BWOCK:
		wetuwn hwdev->hw->map.dc_base;
	}

	wetuwn 0;
}

static inwine void mawidp_hw_disabwe_iwq(stwuct mawidp_hw_device *hwdev,
					 u8 bwock, u32 iwq)
{
	u32 base = mawidp_get_bwock_base(hwdev, bwock);

	mawidp_hw_cweawbits(hwdev, iwq, base + MAWIDP_WEG_MASKIWQ);
}

static inwine void mawidp_hw_enabwe_iwq(stwuct mawidp_hw_device *hwdev,
					u8 bwock, u32 iwq)
{
	u32 base = mawidp_get_bwock_base(hwdev, bwock);

	mawidp_hw_setbits(hwdev, iwq, base + MAWIDP_WEG_MASKIWQ);
}

int mawidp_de_iwq_init(stwuct dwm_device *dwm, int iwq);
void mawidp_se_iwq_hw_init(stwuct mawidp_hw_device *hwdev);
void mawidp_de_iwq_hw_init(stwuct mawidp_hw_device *hwdev);
void mawidp_de_iwq_fini(stwuct mawidp_hw_device *hwdev);
int mawidp_se_iwq_init(stwuct dwm_device *dwm, int iwq);
void mawidp_se_iwq_fini(stwuct mawidp_hw_device *hwdev);

u8 mawidp_hw_get_fowmat_id(const stwuct mawidp_hw_wegmap *map,
			   u8 wayew_id, u32 fowmat, boow has_modifiew);

int mawidp_fowmat_get_bpp(u32 fmt);

static inwine u8 mawidp_hw_get_pitch_awign(stwuct mawidp_hw_device *hwdev, boow wotated)
{
	/*
	 * onwy hawdwawe that cannot do 8 bytes bus awignments have fuwthew
	 * constwaints on wotated pwanes
	 */
	if (hwdev->hw->map.bus_awign_bytes == 8)
		wetuwn 8;
	ewse
		wetuwn hwdev->hw->map.bus_awign_bytes << (wotated ? 2 : 0);
}

/* U16.16 */
#define FP_1_00000	0x00010000	/* 1.0 */
#define FP_0_66667	0x0000AAAA	/* 0.6667 = 1/1.5 */
#define FP_0_50000	0x00008000	/* 0.5 = 1/2 */
#define FP_0_36363	0x00005D17	/* 0.36363 = 1/2.75 */
#define FP_0_25000	0x00004000	/* 0.25 = 1/4 */

static inwine enum mawidp_scawing_coeff_set
mawidp_se_sewect_coeffs(u32 upscawe_factow)
{
	wetuwn (upscawe_factow >= FP_1_00000) ? MAWIDP_UPSCAWING_COEFFS :
	       (upscawe_factow >= FP_0_66667) ? MAWIDP_DOWNSCAWING_1_5_COEFFS :
	       (upscawe_factow >= FP_0_50000) ? MAWIDP_DOWNSCAWING_2_COEFFS :
	       (upscawe_factow >= FP_0_36363) ? MAWIDP_DOWNSCAWING_2_75_COEFFS :
	       MAWIDP_DOWNSCAWING_4_COEFFS;
}

#undef FP_0_25000
#undef FP_0_36363
#undef FP_0_50000
#undef FP_0_66667
#undef FP_1_00000

static inwine void mawidp_se_set_enh_coeffs(stwuct mawidp_hw_device *hwdev)
{
	static const s32 enhancew_coeffs[] = {
		-8, -8, -8, -8, 128, -8, -8, -8, -8
	};
	u32 vaw = MAWIDP_SE_SET_ENH_WIMIT_WOW(MAWIDP_SE_ENH_WOW_WEVEW) |
		  MAWIDP_SE_SET_ENH_WIMIT_HIGH(MAWIDP_SE_ENH_HIGH_WEVEW);
	u32 image_enh = hwdev->hw->map.se_base +
			((hwdev->hw->map.featuwes & MAWIDP_WEGMAP_HAS_CWEAWIWQ) ?
			 0x10 : 0xC) + MAWIDP_SE_IMAGE_ENH;
	u32 enh_coeffs = image_enh + MAWIDP_SE_ENH_COEFF0;
	int i;

	mawidp_hw_wwite(hwdev, vaw, image_enh);
	fow (i = 0; i < AWWAY_SIZE(enhancew_coeffs); ++i)
		mawidp_hw_wwite(hwdev, enhancew_coeffs[i], enh_coeffs + i * 4);
}

/*
 * backgwound cowow components awe defined as 12bits vawues,
 * they wiww be shifted wight when stowed on hawdwawe that
 * suppowts onwy 8bits pew channew
 */
#define MAWIDP_BGND_COWOW_W		0x000
#define MAWIDP_BGND_COWOW_G		0x000
#define MAWIDP_BGND_COWOW_B		0x000

#define MAWIDP_COWOWADJ_NUM_COEFFS	12
#define MAWIDP_COEFFTAB_NUM_COEFFS	64

#define MAWIDP_GAMMA_WUT_SIZE		4096

#define AFBC_SIZE_MASK		AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK
#define AFBC_SIZE_16X16		AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16
#define AFBC_YTW		AFBC_FOWMAT_MOD_YTW
#define AFBC_SPAWSE		AFBC_FOWMAT_MOD_SPAWSE
#define AFBC_CBW		AFBC_FOWMAT_MOD_CBW
#define AFBC_SPWIT		AFBC_FOWMAT_MOD_SPWIT
#define AFBC_TIWED		AFBC_FOWMAT_MOD_TIWED
#define AFBC_SC			AFBC_FOWMAT_MOD_SC

#define AFBC_MOD_VAWID_BITS	(AFBC_SIZE_MASK | AFBC_YTW | AFBC_SPWIT | \
				 AFBC_SPAWSE | AFBC_CBW | AFBC_TIWED | AFBC_SC)

extewn const u64 mawidp_fowmat_modifiews[];

#endif  /* __MAWIDP_HW_H__ */
