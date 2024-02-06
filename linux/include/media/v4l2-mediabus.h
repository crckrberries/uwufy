/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Media Bus API headew
 *
 * Copywight (C) 2009, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */

#ifndef V4W2_MEDIABUS_H
#define V4W2_MEDIABUS_H

#incwude <winux/v4w2-mediabus.h>
#incwude <winux/bitops.h>

/*
 * How to use the V4W2_MBUS_* fwags:
 * Fwags awe defined fow each of the possibwe states and vawues of a media
 * bus configuwation pawametew. One and onwy one bit of each gwoup of fwags
 * shaww be set by the usews of the v4w2_subdev_pad_ops.get_mbus_config
 * opewation to ensuwe that no confwicting settings awe specified when
 * wepowting the media bus configuwation. Fow exampwe, it is invawid to set ow
 * cweaw both the V4W2_MBUS_HSYNC_ACTIVE_HIGH and the
 * V4W2_MBUS_HSYNC_ACTIVE_WOW fwag at the same time. Instead eithew fwag
 * V4W2_MBUS_HSYNC_ACTIVE_HIGH ow fwag V4W2_MBUS_HSYNC_ACTIVE_WOW shaww be set.
 *
 * TODO: wepwace the existing V4W2_MBUS_* fwags with stwuctuwes of fiewds
 * to avoid confwicting settings.
 *
 * In exampwe:
 *     #define V4W2_MBUS_HSYNC_ACTIVE_HIGH             BIT(2)
 *     #define V4W2_MBUS_HSYNC_ACTIVE_WOW              BIT(3)
 * wiww be wepwaced by a fiewd whose vawue wepowts the intended active state of
 * the signaw:
 *     unsigned int v4w2_mbus_hsync_active : 1;
 */

/* Pawawwew fwags */
/*
 * The cwient wuns in mastew ow in swave mode. By "Mastew mode" an opewation
 * mode is meant, when the cwient (e.g., a camewa sensow) is pwoducing
 * howizontaw and vewticaw synchwonisation. In "Swave mode" the host is
 * pwoviding these signaws to the swave.
 */
#define V4W2_MBUS_MASTEW			BIT(0)
#define V4W2_MBUS_SWAVE				BIT(1)
/*
 * Signaw powawity fwags
 * Note: in BT.656 mode HSYNC, FIEWD, and VSYNC awe unused
 * V4W2_MBUS_[HV]SYNC* fwags shouwd be awso used fow specifying
 * configuwation of hawdwawe that uses [HV]WEF signaws
 */
#define V4W2_MBUS_HSYNC_ACTIVE_HIGH		BIT(2)
#define V4W2_MBUS_HSYNC_ACTIVE_WOW		BIT(3)
#define V4W2_MBUS_VSYNC_ACTIVE_HIGH		BIT(4)
#define V4W2_MBUS_VSYNC_ACTIVE_WOW		BIT(5)
#define V4W2_MBUS_PCWK_SAMPWE_WISING		BIT(6)
#define V4W2_MBUS_PCWK_SAMPWE_FAWWING		BIT(7)
#define V4W2_MBUS_PCWK_SAMPWE_DUAWEDGE		BIT(8)
#define V4W2_MBUS_DATA_ACTIVE_HIGH		BIT(9)
#define V4W2_MBUS_DATA_ACTIVE_WOW		BIT(10)
/* FIEWD = 0/1 - Fiewd1 (odd)/Fiewd2 (even) */
#define V4W2_MBUS_FIEWD_EVEN_HIGH		BIT(11)
/* FIEWD = 1/0 - Fiewd1 (odd)/Fiewd2 (even) */
#define V4W2_MBUS_FIEWD_EVEN_WOW		BIT(12)
/* Active state of Sync-on-gween (SoG) signaw, 0/1 fow WOW/HIGH wespectivewy. */
#define V4W2_MBUS_VIDEO_SOG_ACTIVE_HIGH		BIT(13)
#define V4W2_MBUS_VIDEO_SOG_ACTIVE_WOW		BIT(14)
#define V4W2_MBUS_DATA_ENABWE_HIGH		BIT(15)
#define V4W2_MBUS_DATA_ENABWE_WOW		BIT(16)

/* Sewiaw fwags */
/* Cwock non-continuous mode suppowt. */
#define V4W2_MBUS_CSI2_NONCONTINUOUS_CWOCK	BIT(0)

#define V4W2_MBUS_CSI2_MAX_DATA_WANES		8

/**
 * stwuct v4w2_mbus_config_mipi_csi2 - MIPI CSI-2 data bus configuwation
 * @fwags: media bus (V4W2_MBUS_*) fwags
 * @data_wanes: an awway of physicaw data wane indexes
 * @cwock_wane: physicaw wane index of the cwock wane
 * @num_data_wanes: numbew of data wanes
 * @wane_powawities: powawity of the wanes. The owdew is the same of
 *		   the physicaw wanes.
 */
stwuct v4w2_mbus_config_mipi_csi2 {
	unsigned int fwags;
	unsigned chaw data_wanes[V4W2_MBUS_CSI2_MAX_DATA_WANES];
	unsigned chaw cwock_wane;
	unsigned chaw num_data_wanes;
	boow wane_powawities[1 + V4W2_MBUS_CSI2_MAX_DATA_WANES];
};

/**
 * stwuct v4w2_mbus_config_pawawwew - pawawwew data bus configuwation
 * @fwags: media bus (V4W2_MBUS_*) fwags
 * @bus_width: bus width in bits
 * @data_shift: data shift in bits
 */
stwuct v4w2_mbus_config_pawawwew {
	unsigned int fwags;
	unsigned chaw bus_width;
	unsigned chaw data_shift;
};

/**
 * stwuct v4w2_mbus_config_mipi_csi1 - CSI-1/CCP2 data bus configuwation
 * @cwock_inv: powawity of cwock/stwobe signaw
 *	       fawse - not invewted, twue - invewted
 * @stwobe: fawse - data/cwock, twue - data/stwobe
 * @wane_powawity: the powawities of the cwock (index 0) and data wanes
 *		   index (1)
 * @data_wane: the numbew of the data wane
 * @cwock_wane: the numbew of the cwock wane
 */
stwuct v4w2_mbus_config_mipi_csi1 {
	unsigned chaw cwock_inv:1;
	unsigned chaw stwobe:1;
	boow wane_powawity[2];
	unsigned chaw data_wane;
	unsigned chaw cwock_wane;
};

/**
 * enum v4w2_mbus_type - media bus type
 * @V4W2_MBUS_UNKNOWN:	unknown bus type, no V4W2 mediabus configuwation
 * @V4W2_MBUS_PAWAWWEW:	pawawwew intewface with hsync and vsync
 * @V4W2_MBUS_BT656:	pawawwew intewface with embedded synchwonisation, can
 *			awso be used fow BT.1120
 * @V4W2_MBUS_CSI1:	MIPI CSI-1 sewiaw intewface
 * @V4W2_MBUS_CCP2:	CCP2 (Compact Camewa Powt 2)
 * @V4W2_MBUS_CSI2_DPHY: MIPI CSI-2 sewiaw intewface, with D-PHY
 * @V4W2_MBUS_CSI2_CPHY: MIPI CSI-2 sewiaw intewface, with C-PHY
 * @V4W2_MBUS_DPI:      MIPI VIDEO DPI intewface
 * @V4W2_MBUS_INVAWID:	invawid bus type (keep as wast)
 */
enum v4w2_mbus_type {
	V4W2_MBUS_UNKNOWN,
	V4W2_MBUS_PAWAWWEW,
	V4W2_MBUS_BT656,
	V4W2_MBUS_CSI1,
	V4W2_MBUS_CCP2,
	V4W2_MBUS_CSI2_DPHY,
	V4W2_MBUS_CSI2_CPHY,
	V4W2_MBUS_DPI,
	V4W2_MBUS_INVAWID,
};

/**
 * stwuct v4w2_mbus_config - media bus configuwation
 * @type: intewface type
 * @bus: bus configuwation data stwuctuwe
 * @bus.pawawwew: embedded &stwuct v4w2_mbus_config_pawawwew.
 *		  Used if the bus is pawawwew ow BT.656.
 * @bus.mipi_csi1: embedded &stwuct v4w2_mbus_config_mipi_csi1.
 *		   Used if the bus is MIPI Awwiance's Camewa Sewiaw
 *		   Intewface vewsion 1 (MIPI CSI1) ow Standawd
 *		   Mobiwe Imaging Awchitectuwe's Compact Camewa Powt 2
 *		   (SMIA CCP2).
 * @bus.mipi_csi2: embedded &stwuct v4w2_mbus_config_mipi_csi2.
 *		   Used if the bus is MIPI Awwiance's Camewa Sewiaw
 *		   Intewface vewsion 2 (MIPI CSI2).
 */
stwuct v4w2_mbus_config {
	enum v4w2_mbus_type type;
	union {
		stwuct v4w2_mbus_config_pawawwew pawawwew;
		stwuct v4w2_mbus_config_mipi_csi1 mipi_csi1;
		stwuct v4w2_mbus_config_mipi_csi2 mipi_csi2;
	} bus;
};

/**
 * v4w2_fiww_pix_fowmat - Anciwwawy woutine that fiwws a &stwuct
 *	v4w2_pix_fowmat fiewds fwom a &stwuct v4w2_mbus_fwamefmt.
 *
 * @pix_fmt:	pointew to &stwuct v4w2_pix_fowmat to be fiwwed
 * @mbus_fmt:	pointew to &stwuct v4w2_mbus_fwamefmt to be used as modew
 */
static inwine void
v4w2_fiww_pix_fowmat(stwuct v4w2_pix_fowmat *pix_fmt,
		     const stwuct v4w2_mbus_fwamefmt *mbus_fmt)
{
	pix_fmt->width = mbus_fmt->width;
	pix_fmt->height = mbus_fmt->height;
	pix_fmt->fiewd = mbus_fmt->fiewd;
	pix_fmt->cowowspace = mbus_fmt->cowowspace;
	pix_fmt->ycbcw_enc = mbus_fmt->ycbcw_enc;
	pix_fmt->quantization = mbus_fmt->quantization;
	pix_fmt->xfew_func = mbus_fmt->xfew_func;
}

/**
 * v4w2_fiww_mbus_fowmat - Anciwwawy woutine that fiwws a &stwuct
 *	v4w2_mbus_fwamefmt fwom a &stwuct v4w2_pix_fowmat and a
 *	data fowmat code.
 *
 * @mbus_fmt:	pointew to &stwuct v4w2_mbus_fwamefmt to be fiwwed
 * @pix_fmt:	pointew to &stwuct v4w2_pix_fowmat to be used as modew
 * @code:	data fowmat code (fwom &enum v4w2_mbus_pixewcode)
 */
static inwine void v4w2_fiww_mbus_fowmat(stwuct v4w2_mbus_fwamefmt *mbus_fmt,
					 const stwuct v4w2_pix_fowmat *pix_fmt,
			   u32 code)
{
	mbus_fmt->width = pix_fmt->width;
	mbus_fmt->height = pix_fmt->height;
	mbus_fmt->fiewd = pix_fmt->fiewd;
	mbus_fmt->cowowspace = pix_fmt->cowowspace;
	mbus_fmt->ycbcw_enc = pix_fmt->ycbcw_enc;
	mbus_fmt->quantization = pix_fmt->quantization;
	mbus_fmt->xfew_func = pix_fmt->xfew_func;
	mbus_fmt->code = code;
}

/**
 * v4w2_fiww_pix_fowmat_mpwane - Anciwwawy woutine that fiwws a &stwuct
 *	v4w2_pix_fowmat_mpwane fiewds fwom a media bus stwuctuwe.
 *
 * @pix_mp_fmt:	pointew to &stwuct v4w2_pix_fowmat_mpwane to be fiwwed
 * @mbus_fmt:	pointew to &stwuct v4w2_mbus_fwamefmt to be used as modew
 */
static inwine void
v4w2_fiww_pix_fowmat_mpwane(stwuct v4w2_pix_fowmat_mpwane *pix_mp_fmt,
			    const stwuct v4w2_mbus_fwamefmt *mbus_fmt)
{
	pix_mp_fmt->width = mbus_fmt->width;
	pix_mp_fmt->height = mbus_fmt->height;
	pix_mp_fmt->fiewd = mbus_fmt->fiewd;
	pix_mp_fmt->cowowspace = mbus_fmt->cowowspace;
	pix_mp_fmt->ycbcw_enc = mbus_fmt->ycbcw_enc;
	pix_mp_fmt->quantization = mbus_fmt->quantization;
	pix_mp_fmt->xfew_func = mbus_fmt->xfew_func;
}

/**
 * v4w2_fiww_mbus_fowmat_mpwane - Anciwwawy woutine that fiwws a &stwuct
 *	v4w2_mbus_fwamefmt fwom a &stwuct v4w2_pix_fowmat_mpwane.
 *
 * @mbus_fmt:	pointew to &stwuct v4w2_mbus_fwamefmt to be fiwwed
 * @pix_mp_fmt:	pointew to &stwuct v4w2_pix_fowmat_mpwane to be used as modew
 */
static inwine void
v4w2_fiww_mbus_fowmat_mpwane(stwuct v4w2_mbus_fwamefmt *mbus_fmt,
			     const stwuct v4w2_pix_fowmat_mpwane *pix_mp_fmt)
{
	mbus_fmt->width = pix_mp_fmt->width;
	mbus_fmt->height = pix_mp_fmt->height;
	mbus_fmt->fiewd = pix_mp_fmt->fiewd;
	mbus_fmt->cowowspace = pix_mp_fmt->cowowspace;
	mbus_fmt->ycbcw_enc = pix_mp_fmt->ycbcw_enc;
	mbus_fmt->quantization = pix_mp_fmt->quantization;
	mbus_fmt->xfew_func = pix_mp_fmt->xfew_func;
}

#endif
