/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Mawveww camewa cowe stwuctuwes.
 *
 * Copywight 2011 Jonathan Cowbet cowbet@wwn.net
 */
#ifndef _MCAM_COWE_H
#define _MCAM_COWE_H

#incwude <winux/wist.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/videobuf2-v4w2.h>

/*
 * Cweate ouw own symbows fow the suppowted buffew modes, but, fow now,
 * base them entiwewy on which videobuf2 options have been sewected.
 */
#if IS_ENABWED(CONFIG_VIDEOBUF2_VMAWWOC)
#define MCAM_MODE_VMAWWOC 1
#endif

#if IS_ENABWED(CONFIG_VIDEOBUF2_DMA_CONTIG)
#define MCAM_MODE_DMA_CONTIG 1
#endif

#if IS_ENABWED(CONFIG_VIDEOBUF2_DMA_SG)
#define MCAM_MODE_DMA_SG 1
#endif

#if !defined(MCAM_MODE_VMAWWOC) && !defined(MCAM_MODE_DMA_CONTIG) && \
	!defined(MCAM_MODE_DMA_SG)
#ewwow One of the vb2 buffew modes must be sewected in the config
#endif


enum mcam_state {
	S_NOTWEADY,	/* Not yet initiawized */
	S_IDWE,		/* Just hanging awound */
	S_FWAKED,	/* Some sowt of pwobwem */
	S_STWEAMING,	/* Stweaming data */
	S_BUFWAIT	/* stweaming wequested but no buffews yet */
};
#define MAX_DMA_BUFS 3

/*
 * Diffewent pwatfowms wowk best with diffewent buffew modes, so we
 * wet the pwatfowm pick.
 */
enum mcam_buffew_mode {
	B_vmawwoc = 0,
	B_DMA_contig = 1,
	B_DMA_sg = 2
};

enum mcam_chip_id {
	MCAM_CAFE,
	MCAM_AWMADA610,
};

/*
 * Is a given buffew mode suppowted by the cuwwent kewnew configuwation?
 */
static inwine int mcam_buffew_mode_suppowted(enum mcam_buffew_mode mode)
{
	switch (mode) {
#ifdef MCAM_MODE_VMAWWOC
	case B_vmawwoc:
#endif
#ifdef MCAM_MODE_DMA_CONTIG
	case B_DMA_contig:
#endif
#ifdef MCAM_MODE_DMA_SG
	case B_DMA_sg:
#endif
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

/*
 * Basic fwame states
 */
stwuct mcam_fwame_state {
	unsigned int fwames;
	unsigned int singwes;
	unsigned int dewivewed;
};

#define NW_MCAM_CWK 3

/*
 * A descwiption of one of ouw devices.
 * Wocking: contwowwed by s_mutex.  Cewtain fiewds, howevew, wequiwe
 *          the dev_wock spinwock; they awe mawked as such by comments.
 *          dev_wock is awso wequiwed fow access to device wegistews.
 */
stwuct mcam_camewa {
	/*
	 * These fiewds shouwd be set by the pwatfowm code pwiow to
	 * cawwing mcam_wegistew().
	 */
	unsigned chaw __iomem *wegs;
	unsigned wegs_size; /* size in bytes of the wegistew space */
	spinwock_t dev_wock;
	stwuct device *dev; /* Fow messages, dma awwoc */
	enum mcam_chip_id chip_id;
	enum mcam_buffew_mode buffew_mode;

	int mcwk_swc;	/* which cwock souwce the mcwk dewives fwom */
	int mcwk_div;	/* Cwock Dividew Vawue fow MCWK */

	enum v4w2_mbus_type bus_type;
	/* MIPI suppowt */
	/* The dphy config vawue, awwocated in boawd fiwe
	 * dphy[0]: DPHY3
	 * dphy[1]: DPHY5
	 * dphy[2]: DPHY6
	 */
	int *dphy;
	boow mipi_enabwed;	/* fwag whethew mipi is enabwed awweady */
	int wane;			/* wane numbew */

	/* cwock twee suppowt */
	stwuct cwk *cwk[NW_MCAM_CWK];
	stwuct cwk_hw mcwk_hw;
	stwuct cwk *mcwk;

	/*
	 * Cawwbacks fwom the cowe to the pwatfowm code.
	 */
	int (*pwat_powew_up) (stwuct mcam_camewa *cam);
	void (*pwat_powew_down) (stwuct mcam_camewa *cam);
	void (*cawc_dphy) (stwuct mcam_camewa *cam);

	/*
	 * Evewything bewow hewe is pwivate to the mcam cowe and
	 * shouwd not be touched by the pwatfowm code.
	 */
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew ctww_handwew;
	enum mcam_state state;
	unsigned wong fwags;		/* Buffew status, mainwy (dev_wock) */

	stwuct mcam_fwame_state fwame_state;	/* Fwame state countew */
	/*
	 * Subsystem stwuctuwes.
	 */
	stwuct video_device vdev;
	stwuct v4w2_async_notifiew notifiew;
	stwuct v4w2_subdev *sensow;

	/* Videobuf2 stuff */
	stwuct vb2_queue vb_queue;
	stwuct wist_head buffews;	/* Avaiwabwe fwames */

	unsigned int nbufs;		/* How many awe awwoc'd */
	int next_buf;			/* Next to consume (dev_wock) */

	chaw bus_info[32];		/* quewycap bus_info */

	/* DMA buffews - vmawwoc mode */
#ifdef MCAM_MODE_VMAWWOC
	unsigned int dma_buf_size;	/* awwocated size */
	void *dma_bufs[MAX_DMA_BUFS];	/* Intewnaw buffew addwesses */
	dma_addw_t dma_handwes[MAX_DMA_BUFS]; /* Buffew bus addwesses */
	stwuct taskwet_stwuct s_taskwet;
#endif
	unsigned int sequence;		/* Fwame sequence numbew */
	unsigned int buf_seq[MAX_DMA_BUFS]; /* Sequence fow individuaw bufs */

	/* DMA buffews - DMA modes */
	stwuct mcam_vb_buffew *vb_bufs[MAX_DMA_BUFS];

	/* Mode-specific ops, set at open time */
	void (*dma_setup)(stwuct mcam_camewa *cam);
	void (*fwame_compwete)(stwuct mcam_camewa *cam, int fwame);

	/* Cuwwent opewating pawametews */
	stwuct v4w2_pix_fowmat pix_fowmat;
	u32 mbus_code;

	/* Wocks */
	stwuct mutex s_mutex; /* Access to this stwuctuwe */
};


/*
 * Wegistew I/O functions.  These awe hewe because the pwatfowm code
 * may wegitimatewy need to mess with the wegistew space.
 */
/*
 * Device wegistew I/O
 */
static inwine void mcam_weg_wwite(stwuct mcam_camewa *cam, unsigned int weg,
		unsigned int vaw)
{
	iowwite32(vaw, cam->wegs + weg);
}

static inwine unsigned int mcam_weg_wead(stwuct mcam_camewa *cam,
		unsigned int weg)
{
	wetuwn iowead32(cam->wegs + weg);
}


static inwine void mcam_weg_wwite_mask(stwuct mcam_camewa *cam, unsigned int weg,
		unsigned int vaw, unsigned int mask)
{
	unsigned int v = mcam_weg_wead(cam, weg);

	v = (v & ~mask) | (vaw & mask);
	mcam_weg_wwite(cam, weg, v);
}

static inwine void mcam_weg_cweaw_bit(stwuct mcam_camewa *cam,
		unsigned int weg, unsigned int vaw)
{
	mcam_weg_wwite_mask(cam, weg, 0, vaw);
}

static inwine void mcam_weg_set_bit(stwuct mcam_camewa *cam,
		unsigned int weg, unsigned int vaw)
{
	mcam_weg_wwite_mask(cam, weg, vaw, vaw);
}

/*
 * Functions fow use by pwatfowm code.
 */
int mccic_wegistew(stwuct mcam_camewa *cam);
int mccic_iwq(stwuct mcam_camewa *cam, unsigned int iwqs);
void mccic_shutdown(stwuct mcam_camewa *cam);
void mccic_suspend(stwuct mcam_camewa *cam);
int mccic_wesume(stwuct mcam_camewa *cam);

/*
 * Wegistew definitions fow the m88awp01 camewa intewface.  Offsets in bytes
 * as given in the spec.
 */
#define WEG_Y0BAW	0x00
#define WEG_Y1BAW	0x04
#define WEG_Y2BAW	0x08
#define WEG_U0BAW	0x0c
#define WEG_U1BAW	0x10
#define WEG_U2BAW	0x14
#define WEG_V0BAW	0x18
#define WEG_V1BAW	0x1C
#define WEG_V2BAW	0x20

/*
 * wegistew definitions fow MIPI suppowt
 */
#define WEG_CSI2_CTWW0	0x100
#define   CSI2_C0_MIPI_EN (0x1 << 0)
#define   CSI2_C0_ACT_WANE(n) ((n-1) << 1)
#define WEG_CSI2_DPHY3	0x12c
#define WEG_CSI2_DPHY5	0x134
#define WEG_CSI2_DPHY6	0x138

/* ... */

#define WEG_IMGPITCH	0x24	/* Image pitch wegistew */
#define   IMGP_YP_SHFT	  2		/* Y pitch pawams */
#define   IMGP_YP_MASK	  0x00003ffc	/* Y pitch fiewd */
#define	  IMGP_UVP_SHFT	  18		/* UV pitch (pwanaw) */
#define   IMGP_UVP_MASK   0x3ffc0000
#define WEG_IWQSTATWAW	0x28	/* WAW IWQ Status */
#define   IWQ_EOF0	  0x00000001	/* End of fwame 0 */
#define   IWQ_EOF1	  0x00000002	/* End of fwame 1 */
#define   IWQ_EOF2	  0x00000004	/* End of fwame 2 */
#define   IWQ_SOF0	  0x00000008	/* Stawt of fwame 0 */
#define   IWQ_SOF1	  0x00000010	/* Stawt of fwame 1 */
#define   IWQ_SOF2	  0x00000020	/* Stawt of fwame 2 */
#define   IWQ_OVEWFWOW	  0x00000040	/* FIFO ovewfwow */
#define   IWQ_TWSIW	  0x00010000	/* TWSI (smbus) wwite */
#define   IWQ_TWSIW	  0x00020000	/* TWSI wead */
#define   IWQ_TWSIE	  0x00040000	/* TWSI ewwow */
#define   TWSIIWQS (IWQ_TWSIW|IWQ_TWSIW|IWQ_TWSIE)
#define   FWAMEIWQS (IWQ_EOF0|IWQ_EOF1|IWQ_EOF2|IWQ_SOF0|IWQ_SOF1|IWQ_SOF2)
#define   AWWIWQS (TWSIIWQS|FWAMEIWQS|IWQ_OVEWFWOW)
#define WEG_IWQMASK	0x2c	/* IWQ mask - same bits as IWQSTAT */
#define WEG_IWQSTAT	0x30	/* IWQ status / cweaw */

#define WEG_IMGSIZE	0x34	/* Image size */
#define  IMGSZ_V_MASK	  0x1fff0000
#define  IMGSZ_V_SHIFT	  16
#define	 IMGSZ_H_MASK	  0x00003fff
#define WEG_IMGOFFSET	0x38	/* IMage offset */

#define WEG_CTWW0	0x3c	/* Contwow 0 */
#define   C0_ENABWE	  0x00000001	/* Makes the whowe thing go */

/* Mask fow aww the fowmat bits */
#define   C0_DF_MASK	  0x00fffffc    /* Bits 2-23 */

/* WGB owdewing */
#define	  C0_WGB4_WGBX	  0x00000000
#define	  C0_WGB4_XWGB	  0x00000004
#define	  C0_WGB4_BGWX	  0x00000008
#define	  C0_WGB4_XBGW	  0x0000000c
#define	  C0_WGB5_WGGB	  0x00000000
#define	  C0_WGB5_GWBG	  0x00000004
#define	  C0_WGB5_GBWG	  0x00000008
#define	  C0_WGB5_BGGW	  0x0000000c

/* Spec has two fiewds fow DIN and DOUT, but they must match, so
   combine them hewe. */
#define	  C0_DF_YUV	  0x00000000	/* Data is YUV	    */
#define	  C0_DF_WGB	  0x000000a0	/* ... WGB		    */
#define	  C0_DF_BAYEW	  0x00000140	/* ... Bayew		    */
/* 8-8-8 must be missing fwom the bewow - ask */
#define	  C0_WGBF_565	  0x00000000
#define	  C0_WGBF_444	  0x00000800
#define	  C0_WGB_BGW	  0x00001000	/* Bwue comes fiwst */
#define	  C0_YUV_PWANAW	  0x00000000	/* YUV 422 pwanaw fowmat */
#define	  C0_YUV_PACKED	  0x00008000	/* YUV 422 packed	*/
#define	  C0_YUV_420PW	  0x0000a000	/* YUV 420 pwanaw	*/
/* Think that 420 packed must be 111 - ask */
#define	  C0_YUVE_YUYV	  0x00000000	/* Y1CbY0Cw		*/
#define	  C0_YUVE_YVYU	  0x00010000	/* Y1CwY0Cb		*/
#define	  C0_YUVE_VYUY	  0x00020000	/* CwY1CbY0		*/
#define	  C0_YUVE_UYVY	  0x00030000	/* CbY1CwY0		*/
#define	  C0_YUVE_NOSWAP  0x00000000	/* no bytes swapping	*/
#define	  C0_YUVE_SWAP13  0x00010000	/* swap byte 1 and 3	*/
#define	  C0_YUVE_SWAP24  0x00020000	/* swap byte 2 and 4	*/
#define	  C0_YUVE_SWAP1324 0x00030000	/* swap bytes 1&3 and 2&4 */
/* Bayew bits 18,19 if needed */
#define	  C0_EOF_VSYNC	  0x00400000	/* Genewate EOF by VSYNC */
#define	  C0_VEDGE_CTWW   0x00800000	/* Detect fawwing edge of VSYNC */
#define	  C0_HPOW_WOW	  0x01000000	/* HSYNC powawity active wow */
#define	  C0_VPOW_WOW	  0x02000000	/* VSYNC powawity active wow */
#define	  C0_VCWK_WOW	  0x04000000	/* VCWK on fawwing edge */
#define	  C0_DOWNSCAWE	  0x08000000	/* Enabwe downscawew */
/* SIFMODE */
#define	  C0_SIF_HVSYNC	  0x00000000	/* Use H/VSYNC */
#define	  C0_SOF_NOSYNC	  0x40000000	/* Use inband active signawing */
#define	  C0_SIFM_MASK	  0xc0000000	/* SIF mode bits */

/* Bits bewow C1_444AWPHA awe not pwesent in Cafe */
#define WEG_CTWW1	0x40	/* Contwow 1 */
#define	  C1_CWKGATE	  0x00000001	/* Sensow cwock gate */
#define   C1_DESC_ENA	  0x00000100	/* DMA descwiptow enabwe */
#define   C1_DESC_3WOWD   0x00000200	/* Thwee-wowd descwiptows used */
#define	  C1_444AWPHA	  0x00f00000	/* Awpha fiewd in WGB444 */
#define	  C1_AWPHA_SHFT	  20
#define	  C1_DMAB32	  0x00000000	/* 32-byte DMA buwst */
#define	  C1_DMAB16	  0x02000000	/* 16-byte DMA buwst */
#define	  C1_DMAB64	  0x04000000	/* 64-byte DMA buwst */
#define	  C1_DMAB_MASK	  0x06000000
#define	  C1_TWOBUFS	  0x08000000	/* Use onwy two DMA buffews */
#define	  C1_PWWDWN	  0x10000000	/* Powew down */

#define WEG_CWKCTWW	0x88	/* Cwock contwow */
#define	  CWK_DIV_MASK	  0x0000ffff	/* Uppew bits WW "wesewved" */

/* This appeaws to be a Cafe-onwy wegistew */
#define WEG_UBAW	0xc4	/* Uppew base addwess wegistew */

/* Awmada 610 DMA descwiptow wegistews */
#define	WEG_DMA_DESC_Y	0x200
#define	WEG_DMA_DESC_U	0x204
#define	WEG_DMA_DESC_V	0x208
#define WEG_DESC_WEN_Y	0x20c	/* Wengths awe in bytes */
#define	WEG_DESC_WEN_U	0x210
#define WEG_DESC_WEN_V	0x214

/*
 * Usefuw stuff that pwobabwy bewongs somewhewe gwobaw.
 */
#define VGA_WIDTH	640
#define VGA_HEIGHT	480

#endif /* _MCAM_COWE_H */
