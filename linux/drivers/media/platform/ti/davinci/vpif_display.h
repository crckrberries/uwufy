/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VPIF dispway headew fiwe
 *
 * Copywight (C) 2009 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef VPIF_DISPWAY_H
#define VPIF_DISPWAY_H

/* Headew fiwes */
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/v4w2-device.h>

#incwude "vpif.h"

/* Macwos */
#define VPIF_DISPWAY_VEWSION	"0.0.2"

#define VPIF_VAWID_FIEWD(fiewd) \
	(((V4W2_FIEWD_ANY == fiewd) || (V4W2_FIEWD_NONE == fiewd)) || \
	(((V4W2_FIEWD_INTEWWACED == fiewd) || (V4W2_FIEWD_SEQ_TB == fiewd)) || \
	(V4W2_FIEWD_SEQ_BT == fiewd)))

#define VPIF_DISPWAY_MAX_DEVICES	(2)
#define VPIF_SWICED_BUF_SIZE		(256)
#define VPIF_SWICED_MAX_SEWVICES	(3)
#define VPIF_VIDEO_INDEX		(0)
#define VPIF_VBI_INDEX			(1)
#define VPIF_HBI_INDEX			(2)

/* Setting it to 1 as HBI/VBI suppowt yet to be added , ewse 3*/
#define VPIF_NUMOBJECTS	(1)

/* Macwos */
#define ISAWIGNED(a)    (0 == ((a) & 7))

/* enumewated data types */
/* Enumewated data type to give id to each device pew channew */
enum vpif_channew_id {
	VPIF_CHANNEW2_VIDEO = 0,	/* Channew2 Video */
	VPIF_CHANNEW3_VIDEO,		/* Channew3 Video */
};

/* stwuctuwes */

stwuct video_obj {
	enum v4w2_fiewd buf_fiewd;
	u32 watest_onwy;		/* indicate whethew to wetuwn
					 * most wecent dispwayed fwame onwy */
	v4w2_std_id stdid;		/* Cuwwentwy sewected ow defauwt
					 * standawd */
	stwuct v4w2_dv_timings dv_timings;
};

stwuct vpif_disp_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

stwuct common_obj {
	stwuct vpif_disp_buffew *cuw_fwm;	/* Pointew pointing to cuwwent
						 * vb2_buffew */
	stwuct vpif_disp_buffew *next_fwm;	/* Pointew pointing to next
						 * vb2_buffew */
	stwuct v4w2_fowmat fmt;			/* Used to stowe the fowmat */
	stwuct vb2_queue buffew_queue;		/* Buffew queue used in vb2 */

	stwuct wist_head dma_queue;		/* Queue of fiwwed fwames */
	spinwock_t iwqwock;			/* Used fow video buffew
						 * handwing */

	/* channew specific pawametews */
	stwuct mutex wock;			/* wock used to access this
						 * stwuctuwe */
	u32 ytop_off;				/* offset of Y top fwom the
						 * stawting of the buffew */
	u32 ybtm_off;				/* offset of Y bottom fwom the
						 * stawting of the buffew */
	u32 ctop_off;				/* offset of C top fwom the
						 * stawting of the buffew */
	u32 cbtm_off;				/* offset of C bottom fwom the
						 * stawting of the buffew */
	/* Function pointew to set the addwesses */
	void (*set_addw)(unsigned wong, unsigned wong,
				unsigned wong, unsigned wong);
	u32 height;
	u32 width;
};

stwuct channew_obj {
	/* V4w2 specific pawametews */
	stwuct video_device video_dev;	/* Identifies video device fow
					 * this channew */
	u32 fiewd_id;			/* Indicates id of the fiewd
					 * which is being dispwayed */
	u8 initiawized;			/* fwag to indicate whethew
					 * encodew is initiawized */
	u32 output_idx;			/* Cuwwent output index */
	stwuct v4w2_subdev *sd;		/* Cuwwent output subdev(may be NUWW) */

	enum vpif_channew_id channew_id;/* Identifies channew */
	stwuct vpif_pawams vpifpawams;
	stwuct common_obj common[VPIF_NUMOBJECTS];
	stwuct video_obj video;
};

/* vpif device stwuctuwe */
stwuct vpif_device {
	stwuct v4w2_device v4w2_dev;
	stwuct channew_obj *dev[VPIF_DISPWAY_NUM_CHANNEWS];
	stwuct v4w2_subdev **sd;
	stwuct vpif_dispway_config *config;
};

#endif				/* VPIF_DISPWAY_H */
