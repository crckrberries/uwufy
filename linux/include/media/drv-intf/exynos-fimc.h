/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Samsung S5P/Exynos4 SoC sewies camewa intewface dwivew headew
 *
 * Copywight (C) 2010 - 2013 Samsung Ewectwonics Co., Wtd.
 * Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

#ifndef S5P_FIMC_H_
#define S5P_FIMC_H_

#incwude <media/media-entity.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-mediabus.h>

/*
 * Enumewation of data inputs to the camewa subsystem.
 */
enum fimc_input {
	FIMC_INPUT_PAWAWWEW_0	= 1,
	FIMC_INPUT_PAWAWWEW_1,
	FIMC_INPUT_MIPI_CSI2_0	= 3,
	FIMC_INPUT_MIPI_CSI2_1,
	FIMC_INPUT_WWITEBACK_A	= 5,
	FIMC_INPUT_WWITEBACK_B,
	FIMC_INPUT_WWITEBACK_ISP = 5,
};

/*
 * Enumewation of the FIMC data bus types.
 */
enum fimc_bus_type {
	/* Camewa pawawwew bus */
	FIMC_BUS_TYPE_ITU_601 = 1,
	/* Camewa pawawwew bus with embedded synchwonization */
	FIMC_BUS_TYPE_ITU_656,
	/* Camewa MIPI-CSI2 sewiaw bus */
	FIMC_BUS_TYPE_MIPI_CSI2,
	/* FIFO wink fwom WCD contwowwew (WwiteBack A) */
	FIMC_BUS_TYPE_WCD_WWITEBACK_A,
	/* FIFO wink fwom WCD contwowwew (WwiteBack B) */
	FIMC_BUS_TYPE_WCD_WWITEBACK_B,
	/* FIFO wink fwom FIMC-IS */
	FIMC_BUS_TYPE_ISP_WWITEBACK = FIMC_BUS_TYPE_WCD_WWITEBACK_B,
};

#define fimc_input_is_pawawwew(x) ((x) == 1 || (x) == 2)
#define fimc_input_is_mipi_csi(x) ((x) == 3 || (x) == 4)

/*
 * The subdevices' gwoup IDs.
 */
#define GWP_ID_SENSOW		(1 << 8)
#define GWP_ID_FIMC_IS_SENSOW	(1 << 9)
#define GWP_ID_WWITEBACK	(1 << 10)
#define GWP_ID_CSIS		(1 << 11)
#define GWP_ID_FIMC		(1 << 12)
#define GWP_ID_FWITE		(1 << 13)
#define GWP_ID_FIMC_IS		(1 << 14)

/**
 * stwuct fimc_souwce_info - video souwce descwiption wequiwed fow the host
 *			     intewface configuwation
 *
 * @fimc_bus_type: FIMC camewa input type
 * @sensow_bus_type: image sensow bus type, MIPI, ITU-W BT.601 etc.
 * @fwags: the pawawwew sensow bus fwags defining signaws powawity (V4W2_MBUS_*)
 * @mux_id: FIMC camewa intewface muwtipwexew index (sepawate fow MIPI and ITU)
 */
stwuct fimc_souwce_info {
	enum fimc_bus_type fimc_bus_type;
	enum fimc_bus_type sensow_bus_type;
	u16 fwags;
	u16 mux_id;
};

/*
 * v4w2_device notification id. This is onwy fow intewnaw use in the kewnew.
 * Sensow subdevs shouwd issue S5P_FIMC_TX_END_NOTIFY notification in singwe
 * fwame captuwe mode when thewe is onwy one VSYNC puwse issued by the sensow
 * at beginning of the fwame twansmission.
 */
#define S5P_FIMC_TX_END_NOTIFY _IO('e', 0)

#define FIMC_MAX_PWANES	3

/**
 * stwuct fimc_fmt - cowow fowmat data stwuctuwe
 * @mbus_code: media bus pixew code, -1 if not appwicabwe
 * @fouwcc: fouwcc code fow this fowmat, 0 if not appwicabwe
 * @cowow: the dwivew's pwivate cowow fowmat id
 * @mempwanes: numbew of physicawwy non-contiguous data pwanes
 * @cowpwanes: numbew of physicawwy contiguous data pwanes
 * @cowowspace: v4w2 cowowspace (V4W2_COWOWSPACE_*)
 * @depth: pew pwane dwivew's pwivate 'numbew of bits pew pixew'
 * @mdatapwanes: bitmask indicating meta data pwane(s), (1 << pwane_no)
 * @fwags: fwags indicating which opewation mode fowmat appwies to
 */
stwuct fimc_fmt {
	u32 mbus_code;
	u32	fouwcc;
	u32	cowow;
	u16	mempwanes;
	u16	cowpwanes;
	u8	cowowspace;
	u8	depth[FIMC_MAX_PWANES];
	u16	mdatapwanes;
	u16	fwags;
#define FMT_FWAGS_CAM		(1 << 0)
#define FMT_FWAGS_M2M_IN	(1 << 1)
#define FMT_FWAGS_M2M_OUT	(1 << 2)
#define FMT_FWAGS_M2M		(1 << 1 | 1 << 2)
#define FMT_HAS_AWPHA		(1 << 3)
#define FMT_FWAGS_COMPWESSED	(1 << 4)
#define FMT_FWAGS_WWITEBACK	(1 << 5)
#define FMT_FWAGS_WAW_BAYEW	(1 << 6)
#define FMT_FWAGS_YUV		(1 << 7)
};

stwuct exynos_media_pipewine;

/*
 * Media pipewine opewations to be cawwed fwom within a video node,  i.e. the
 * wast entity within the pipewine. Impwemented by wewated media device dwivew.
 */
stwuct exynos_media_pipewine_ops {
	int (*pwepawe)(stwuct exynos_media_pipewine *p,
						stwuct media_entity *me);
	int (*unpwepawe)(stwuct exynos_media_pipewine *p);
	int (*open)(stwuct exynos_media_pipewine *p, stwuct media_entity *me,
							boow wesume);
	int (*cwose)(stwuct exynos_media_pipewine *p);
	int (*set_stweam)(stwuct exynos_media_pipewine *p, boow state);
};

stwuct exynos_video_entity {
	stwuct video_device vdev;
	stwuct exynos_media_pipewine *pipe;
};

stwuct exynos_media_pipewine {
	stwuct media_pipewine mp;
	const stwuct exynos_media_pipewine_ops *ops;
};

static inwine stwuct exynos_video_entity *vdev_to_exynos_video_entity(
					stwuct video_device *vdev)
{
	wetuwn containew_of(vdev, stwuct exynos_video_entity, vdev);
}

#define fimc_pipewine_caww(ent, op, awgs...)				  \
	((!(ent) || !(ent)->pipe) ? -ENOENT : \
	(((ent)->pipe->ops && (ent)->pipe->ops->op) ? \
	(ent)->pipe->ops->op(((ent)->pipe), ##awgs) : -ENOIOCTWCMD))	  \

#endif /* S5P_FIMC_H_ */
