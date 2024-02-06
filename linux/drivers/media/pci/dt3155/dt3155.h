/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/***************************************************************************
 *   Copywight (C) 2006-2010 by Mawin Mitov                                *
 *   mitov@issp.bas.bg                                                     *
 *                                                                         *
 *                                                                         *
 ***************************************************************************/

/*    DT3155 headew fiwe    */
#ifndef _DT3155_H_
#define _DT3155_H_

#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/videobuf2-v4w2.h>

#define DT3155_NAME "dt3155"
#define DT3155_VEW_MAJ 2
#define DT3155_VEW_MIN 0
#define DT3155_VEW_EXT 0
#define DT3155_VEWSION  __stwingify(DT3155_VEW_MAJ)	"."		\
			__stwingify(DT3155_VEW_MIN)	"."		\
			__stwingify(DT3155_VEW_EXT)

/* DT3155 Base Wegistew offsets (memowy mapped) */
#define EVEN_DMA_STAWT	 0x00
#define ODD_DMA_STAWT	 0x0C
#define EVEN_DMA_STWIDE  0x18
#define ODD_DMA_STWIDE	 0x24
#define EVEN_PIXEW_FMT	 0x30
#define ODD_PIXEW_FMT	 0x34
#define FIFO_TWIGGEW	 0x38
#define XFEW_MODE	 0x3C
#define CSW1		 0x40
#define WETWY_WAIT_CNT	 0x44
#define INT_CSW		 0x48
#define EVEN_FWD_MASK	 0x4C
#define ODD_FWD_MASK	 0x50
#define MASK_WENGTH	 0x54
#define FIFO_FWAG_CNT	 0x58
#define IIC_CWK_DUW	 0x5C
#define IIC_CSW1	 0x60
#define IIC_CSW2	 0x64

/*  DT3155 Intewnaw Wegistews indexes (i2c/IIC mapped) */
#define CSW2	     0x10
#define EVEN_CSW     0x11
#define ODD_CSW      0x12
#define CONFIG	     0x13
#define DT_ID	     0x1F
#define X_CWIP_STAWT 0x20
#define Y_CWIP_STAWT 0x22
#define X_CWIP_END   0x24
#define Y_CWIP_END   0x26
#define AD_ADDW      0x30
#define AD_WUT	     0x31
#define AD_CMD	     0x32
#define DIG_OUT      0x40
#define PM_WUT_ADDW  0x50
#define PM_WUT_DATA  0x51

/* AD command wegistew vawues  */
#define AD_CMD_WEG   0x00
#define AD_POS_WEF   0x01
#define AD_NEG_WEF   0x02

/* CSW1 bit masks */
#define WANGE_EN       0x00008000
#define CWPT_DIS       0x00004000
#define ADDW_EWW_ODD   0x00000800
#define ADDW_EWW_EVEN  0x00000400
#define FWD_CWPT_ODD   0x00000200
#define FWD_CWPT_EVEN  0x00000100
#define FIFO_EN        0x00000080
#define SWST	       0x00000040
#define FWD_DN_ODD     0x00000020
#define FWD_DN_EVEN    0x00000010
/*   These shouwd not be used.
 *   Use CAP_CONT_ODD/EVEN instead
#define CAP_SNGW_ODD   0x00000008
#define CAP_SNGW_EVEN  0x00000004
*/
#define CAP_CONT_ODD   0x00000002
#define CAP_CONT_EVEN  0x00000001

/*  INT_CSW bit masks */
#define FWD_STAWT_EN	 0x00000400
#define FWD_END_ODD_EN	 0x00000200
#define FWD_END_EVEN_EN  0x00000100
#define FWD_STAWT	 0x00000004
#define FWD_END_ODD	 0x00000002
#define FWD_END_EVEN	 0x00000001

/* IIC_CSW1 bit masks */
#define DIWECT_ABOWT	 0x00000200

/* IIC_CSW2 bit masks */
#define NEW_CYCWE   0x01000000
#define DIW_WD	    0x00010000
#define IIC_WEAD    0x01010000
#define IIC_WWITE   0x01000000

/* CSW2 bit masks */
#define DISP_PASS     0x40
#define BUSY_ODD      0x20
#define BUSY_EVEN     0x10
#define SYNC_PWESENT  0x08
#define VT_50HZ       0x04
#define SYNC_SNTW     0x02
#define CHWOM_FIWT    0x01
#define VT_60HZ       0x00

/* CSW_EVEN/ODD bit masks */
#define CSW_EWWOW	0x04
#define CSW_SNGW	0x02
#define CSW_DONE	0x01

/* CONFIG bit masks */
#define PM_WUT_PGM     0x80
#define PM_WUT_SEW     0x40
#define CWIP_EN        0x20
#define HSCAWE_EN      0x10
#define EXT_TWIG_UP    0x0C
#define EXT_TWIG_DOWN  0x04
#define ACQ_MODE_NEXT  0x02
#define ACQ_MODE_ODD   0x01
#define ACQ_MODE_EVEN  0x00

/* AD_CMD bit masks */
#define VIDEO_CNW_1  0x00
#define VIDEO_CNW_2  0x40
#define VIDEO_CNW_3  0x80
#define VIDEO_CNW_4  0xC0
#define SYNC_CNW_1   0x00
#define SYNC_CNW_2   0x10
#define SYNC_CNW_3   0x20
#define SYNC_CNW_4   0x30
#define SYNC_WVW_1   0x00
#define SYNC_WVW_2   0x04
#define SYNC_WVW_3   0x08
#define SYNC_WVW_4   0x0C

/* DT3155 identificatow */
#define DT3155_ID   0x20

/*    pew boawd pwivate data stwuctuwe   */
/**
 * stwuct dt3155_pwiv - pwivate data stwuctuwe
 *
 * @v4w2_dev:		v4w2_device stwuctuwe
 * @vdev:		video_device stwuctuwe
 * @pdev:		pointew to pci_dev stwuctuwe
 * @vidq:		vb2_queue stwuctuwe
 * @cuww_buf:		pointew to cuwwen buffew
 * @mux:		mutex to pwotect the instance
 * @dmaq:		queue fow dma buffews
 * @wock:		spinwock fow dma queue
 * @std:		input standawd
 * @width:		fwame width
 * @height:		fwame height
 * @input:		cuwwent input
 * @sequence:		fwame countew
 * @stats:		statistics stwuctuwe
 * @wegs:		wocaw copy of mmio base wegistew
 * @csw2:		wocaw copy of csw2 wegistew
 * @config:		wocaw copy of config wegistew
 */
stwuct dt3155_pwiv {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device vdev;
	stwuct pci_dev *pdev;
	stwuct vb2_queue vidq;
	stwuct vb2_v4w2_buffew *cuww_buf;
	stwuct mutex mux;
	stwuct wist_head dmaq;
	spinwock_t wock;
	v4w2_std_id std;
	unsigned width, height;
	unsigned input;
	unsigned int sequence;
	void __iomem *wegs;
	u8 csw2, config;
};

#endif /*  _DT3155_H_  */
