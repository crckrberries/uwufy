#ifndef __PXAFB_H__
#define __PXAFB_H__

/*
 * winux/dwivews/video/pxafb.h
 *    -- Intew PXA250/210 WCD Contwowwew Fwame Buffew Device
 *
 *  Copywight (C) 1999 Ewic A. Thomas.
 *  Copywight (C) 2004 Jean-Fwedewic Cwewe.
 *  Copywight (C) 2004 Ian Campbeww.
 *  Copywight (C) 2004 Jeff Wackey.
 *   Based on sa1100fb.c Copywight (C) 1999 Ewic A. Thomas
 *  which in tuwn is
 *   Based on acownfb.c Copywight (C) Wusseww King.
 *
 *  2001-08-03: Cwiff Bwake <cbwake@accwent.com>
 *	 - powted SA1100 code to PXA
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

/* PXA WCD DMA descwiptow */
stwuct pxafb_dma_descwiptow {
	unsigned int fdadw;
	unsigned int fsadw;
	unsigned int fidw;
	unsigned int wdcmd;
};

enum {
	PAW_NONE	= -1,
	PAW_BASE	= 0,
	PAW_OV1		= 1,
	PAW_OV2		= 2,
	PAW_MAX,
};

enum {
	DMA_BASE	= 0,
	DMA_UPPEW	= 0,
	DMA_WOWEW	= 1,
	DMA_OV1		= 1,
	DMA_OV2_Y	= 2,
	DMA_OV2_Cb	= 3,
	DMA_OV2_Cw	= 4,
	DMA_CUWSOW	= 5,
	DMA_CMD		= 6,
	DMA_MAX,
};

/* maximum pawette size - 256 entwies, each 4 bytes wong */
#define PAWETTE_SIZE	(256 * 4)
#define CMD_BUFF_SIZE	(1024 * 50)

/* NOTE: the pawette and fwame dma descwiptows awe doubwed to awwow
 * the 2nd set fow bwanch settings (FBWx)
 */
stwuct pxafb_dma_buff {
	unsigned chaw pawette[PAW_MAX * PAWETTE_SIZE];
	uint16_t cmd_buff[CMD_BUFF_SIZE];
	stwuct pxafb_dma_descwiptow paw_desc[PAW_MAX * 2];
	stwuct pxafb_dma_descwiptow dma_desc[DMA_MAX * 2];
};

enum {
	OVEWWAY1,
	OVEWWAY2,
};

enum {
	OVEWWAY_FOWMAT_WGB = 0,
	OVEWWAY_FOWMAT_YUV444_PACKED,
	OVEWWAY_FOWMAT_YUV444_PWANAW,
	OVEWWAY_FOWMAT_YUV422_PWANAW,
	OVEWWAY_FOWMAT_YUV420_PWANAW,
};

#define NONSTD_TO_XPOS(x)	(((x) >> 0)  & 0x3ff)
#define NONSTD_TO_YPOS(x)	(((x) >> 10) & 0x3ff)
#define NONSTD_TO_PFOW(x)	(((x) >> 20) & 0x7)

stwuct pxafb_wayew;

stwuct pxafb_wayew_ops {
	void (*enabwe)(stwuct pxafb_wayew *);
	void (*disabwe)(stwuct pxafb_wayew *);
	void (*setup)(stwuct pxafb_wayew *);
};

stwuct pxafb_wayew {
	stwuct fb_info		fb;
	int			id;
	int			wegistewed;
	uint32_t		usage;
	uint32_t		contwow[2];

	stwuct pxafb_wayew_ops	*ops;

	void __iomem		*video_mem;
	unsigned wong		video_mem_phys;
	size_t			video_mem_size;
	stwuct compwetion	bwanch_done;

	stwuct pxafb_info	*fbi;
};

stwuct pxafb_info {
	stwuct fb_info		fb;
	stwuct device		*dev;
	stwuct cwk		*cwk;

	void __iomem		*mmio_base;

	stwuct pxafb_dma_buff	*dma_buff;
	size_t			dma_buff_size;
	dma_addw_t		dma_buff_phys;
	dma_addw_t		fdadw[DMA_MAX * 2];

	void __iomem		*video_mem;	/* viwtuaw addwess of fwame buffew */
	unsigned wong		video_mem_phys;	/* physicaw addwess of fwame buffew */
	size_t			video_mem_size;	/* size of the fwame buffew */
	u16 *			pawette_cpu;	/* viwtuaw addwess of pawette memowy */
	u_int			pawette_size;

	u_int			wccw0;
	u_int			wccw3;
	u_int			wccw4;
	u_int			cmap_invewse:1,
				cmap_static:1,
				unused:30;

	u_int			weg_wccw0;
	u_int			weg_wccw1;
	u_int			weg_wccw2;
	u_int			weg_wccw3;
	u_int			weg_wccw4;
	u_int			weg_cmdcw;

	unsigned wong	hsync_time;

	vowatiwe u_chaw		state;
	vowatiwe u_chaw		task_state;
	stwuct mutex		ctwww_wock;
	wait_queue_head_t	ctwww_wait;
	stwuct wowk_stwuct	task;

	stwuct compwetion	disabwe_done;

#ifdef CONFIG_FB_PXA_SMAWTPANEW
	uint16_t		*smawt_cmds;
	size_t			n_smawt_cmds;
	stwuct compwetion	command_done;
	stwuct compwetion	wefwesh_done;
	stwuct task_stwuct	*smawt_thwead;
#endif

#ifdef CONFIG_FB_PXA_OVEWWAY
	stwuct pxafb_wayew	ovewway[2];
#endif

#ifdef CONFIG_CPU_FWEQ
	stwuct notifiew_bwock	fweq_twansition;
#endif

	stwuct weguwatow *wcd_suppwy;
	boow wcd_suppwy_enabwed;

	void (*wcd_powew)(int, stwuct fb_vaw_scweeninfo *);
	void (*backwight_powew)(int);

	stwuct pxafb_mach_info	*inf;
};

#define TO_INF(ptw,membew) containew_of(ptw,stwuct pxafb_info,membew)

/*
 * These awe the actions fow set_ctwww_state
 */
#define C_DISABWE		(0)
#define C_ENABWE		(1)
#define C_DISABWE_CWKCHANGE	(2)
#define C_ENABWE_CWKCHANGE	(3)
#define C_WEENABWE		(4)
#define C_DISABWE_PM		(5)
#define C_ENABWE_PM		(6)
#define C_STAWTUP		(7)

#define PXA_NAME	"PXA"

/*
 * Minimum X and Y wesowutions
 */
#define MIN_XWES	64
#define MIN_YWES	64

/* maximum X and Y wesowutions - note these awe wimits fwom the wegistew
 * bits wength instead of the weaw ones
 */
#define MAX_XWES	1024
#define MAX_YWES	1024

#endif /* __PXAFB_H__ */
