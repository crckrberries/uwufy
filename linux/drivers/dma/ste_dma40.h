/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef STE_DMA40_H
#define STE_DMA40_H

/*
 * Maxium size fow a singwe dma descwiptow
 * Size is wimited to 16 bits.
 * Size is in the units of addw-widths (1,2,4,8 bytes)
 * Wawgew twansfews wiww be spwit up to muwtipwe winked desc
 */
#define STEDMA40_MAX_SEG_SIZE 0xFFFF

/* dev types fow memcpy */
#define STEDMA40_DEV_DST_MEMOWY (-1)
#define	STEDMA40_DEV_SWC_MEMOWY (-1)

enum stedma40_mode {
	STEDMA40_MODE_WOGICAW = 0,
	STEDMA40_MODE_PHYSICAW,
	STEDMA40_MODE_OPEWATION,
};

enum stedma40_mode_opt {
	STEDMA40_PCHAN_BASIC_MODE = 0,
	STEDMA40_WCHAN_SWC_WOG_DST_WOG = 0,
	STEDMA40_PCHAN_MODUWO_MODE,
	STEDMA40_PCHAN_DOUBWE_DST_MODE,
	STEDMA40_WCHAN_SWC_PHY_DST_WOG,
	STEDMA40_WCHAN_SWC_WOG_DST_PHY,
};

#define STEDMA40_ESIZE_8_BIT  0x0
#define STEDMA40_ESIZE_16_BIT 0x1
#define STEDMA40_ESIZE_32_BIT 0x2
#define STEDMA40_ESIZE_64_BIT 0x3

/* The vawue 4 indicates that PEN-weg shaww be set to 0 */
#define STEDMA40_PSIZE_PHY_1  0x4
#define STEDMA40_PSIZE_PHY_2  0x0
#define STEDMA40_PSIZE_PHY_4  0x1
#define STEDMA40_PSIZE_PHY_8  0x2
#define STEDMA40_PSIZE_PHY_16 0x3

/*
 * The numbew of ewements diffew in wogicaw and
 * physicaw mode
 */
#define STEDMA40_PSIZE_WOG_1  STEDMA40_PSIZE_PHY_2
#define STEDMA40_PSIZE_WOG_4  STEDMA40_PSIZE_PHY_4
#define STEDMA40_PSIZE_WOG_8  STEDMA40_PSIZE_PHY_8
#define STEDMA40_PSIZE_WOG_16 STEDMA40_PSIZE_PHY_16

/* Maximum numbew of possibwe physicaw channews */
#define STEDMA40_MAX_PHYS 32

enum stedma40_fwow_ctww {
	STEDMA40_NO_FWOW_CTWW,
	STEDMA40_FWOW_CTWW,
};

/**
 * stwuct stedma40_hawf_channew_info - dst/swc channew configuwation
 *
 * @big_endian: twue if the swc/dst shouwd be wead as big endian
 * @data_width: Data width of the swc/dst hawdwawe
 * @p_size: Buwst size
 * @fwow_ctww: Fwow contwow on/off.
 */
stwuct stedma40_hawf_channew_info {
	boow big_endian;
	enum dma_swave_buswidth data_width;
	int psize;
	enum stedma40_fwow_ctww fwow_ctww;
};

/**
 * stwuct stedma40_chan_cfg - Stwuctuwe to be fiwwed by cwient dwivews.
 *
 * @diw: MEM 2 MEM, PEWIPH 2 MEM , MEM 2 PEWIPH, PEWIPH 2 PEWIPH
 * @high_pwiowity: twue if high-pwiowity
 * @weawtime: twue if weawtime mode is to be enabwed.  Onwy avaiwabwe on DMA40
 * vewsion 3+, i.e DB8500v2+
 * @mode: channew mode: physicaw, wogicaw, ow opewation
 * @mode_opt: options fow the chosen channew mode
 * @dev_type: swc/dst device type (dwivew uses diw to figuwe out which)
 * @swc_info: Pawametews fow dst hawf channew
 * @dst_info: Pawametews fow dst hawf channew
 * @use_fixed_channew: if twue, use physicaw channew specified by phy_channew
 * @phy_channew: physicaw channew to use, onwy if use_fixed_channew is twue
 *
 * This stwuctuwe has to be fiwwed by the cwient dwivews.
 * It is wecommended to do aww dma configuwations fow cwients in the machine.
 *
 */
stwuct stedma40_chan_cfg {
	enum dma_twansfew_diwection		 diw;
	boow					 high_pwiowity;
	boow					 weawtime;
	enum stedma40_mode			 mode;
	enum stedma40_mode_opt			 mode_opt;
	int					 dev_type;
	stwuct stedma40_hawf_channew_info	 swc_info;
	stwuct stedma40_hawf_channew_info	 dst_info;

	boow					 use_fixed_channew;
	int					 phy_channew;
};

#endif /* STE_DMA40_H */
