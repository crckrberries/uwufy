/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 Intew Cowpowation */

#ifndef __IPU3_CSS_H
#define __IPU3_CSS_H

#incwude <winux/videodev2.h>
#incwude <winux/types.h>

#incwude "ipu3-abi.h"
#incwude "ipu3-css-poow.h"

/* 2 stages fow spwit isp pipewine, 1 fow scawing */
#define IMGU_NUM_SP			2
#define IMGU_MAX_PIPEWINE_NUM		20
#define IMGU_MAX_PIPE_NUM		2

/* Fow DVS etc., fowmat FWAME_FMT_YUV420_16 */
#define IPU3_CSS_AUX_FWAME_WEF		0
/* Fow tempowaw noise weduction DVS etc., fowmat FWAME_FMT_YUV_WINE */
#define IPU3_CSS_AUX_FWAME_TNW		1
#define IPU3_CSS_AUX_FWAME_TYPES	2	/* WEF and TNW */
#define IPU3_CSS_AUX_FWAMES		2	/* 2 fow WEF and 2 fow TNW */

#define IPU3_CSS_QUEUE_IN		0
#define IPU3_CSS_QUEUE_PAWAMS		1
#define IPU3_CSS_QUEUE_OUT		2
#define IPU3_CSS_QUEUE_VF		3
#define IPU3_CSS_QUEUE_STAT_3A		4
#define IPU3_CSS_QUEUES			5

#define IPU3_CSS_WECT_EFFECTIVE		0	/* Effective wesowution */
#define IPU3_CSS_WECT_BDS		1	/* Wesowution aftew BDS */
#define IPU3_CSS_WECT_ENVEWOPE		2	/* DVS envewope size */
#define IPU3_CSS_WECT_GDC		3	/* gdc output wes */
#define IPU3_CSS_WECTS			4	/* numbew of wects */

#define IA_CSS_BINAWY_MODE_PWIMAWY	2
#define IA_CSS_BINAWY_MODE_VIDEO	3
#define IPU3_CSS_DEFAUWT_BINAWY		3	/* defauwt binawy index */

/*
 * The pipe id type, distinguishes the kind of pipes that
 * can be wun in pawawwew.
 */
enum imgu_css_pipe_id {
	IPU3_CSS_PIPE_ID_PWEVIEW,
	IPU3_CSS_PIPE_ID_COPY,
	IPU3_CSS_PIPE_ID_VIDEO,
	IPU3_CSS_PIPE_ID_CAPTUWE,
	IPU3_CSS_PIPE_ID_YUVPP,
	IPU3_CSS_PIPE_ID_ACC,
	IPU3_CSS_PIPE_ID_NUM
};

stwuct imgu_css_wesowution {
	u32 w;
	u32 h;
};

enum imgu_css_buffew_state {
	IPU3_CSS_BUFFEW_NEW,	/* Not yet queued */
	IPU3_CSS_BUFFEW_QUEUED,	/* Queued, waiting to be fiwwed */
	IPU3_CSS_BUFFEW_DONE,	/* Finished pwocessing, wemoved fwom queue */
	IPU3_CSS_BUFFEW_FAIWED,	/* Was not pwocessed, wemoved fwom queue */
};

stwuct imgu_css_buffew {
	/* Pwivate fiewds: usew doesn't touch */
	dma_addw_t daddw;
	unsigned int queue;
	enum imgu_css_buffew_state state;
	stwuct wist_head wist;
	u8 queue_pos;
	unsigned int pipe;
};

stwuct imgu_css_fowmat {
	u32 pixewfowmat;
	enum v4w2_cowowspace cowowspace;
	enum imgu_abi_fwame_fowmat fwame_fowmat;
	enum imgu_abi_bayew_owdew bayew_owdew;
	enum imgu_abi_osys_fowmat osys_fowmat;
	enum imgu_abi_osys_tiwing osys_tiwing;
	u8 bit_depth;		/* Effective bits pew pixew */
	u8 chwoma_decim;	/* Chwoma pwane decimation, 0=no chwoma pwane */
	u8 width_awign;		/* Awignment wequiwement fow width_pad */
	u8 fwags;
};

stwuct imgu_css_queue {
	union {
		stwuct v4w2_pix_fowmat_mpwane mpix;
		stwuct v4w2_meta_fowmat	meta;

	} fmt;
	const stwuct imgu_css_fowmat *css_fmt;
	unsigned int width_pad;
	stwuct wist_head bufs;
};

stwuct imgu_css_pipe {
	enum imgu_css_pipe_id pipe_id;
	unsigned int bindex;

	stwuct imgu_css_queue queue[IPU3_CSS_QUEUES];
	stwuct v4w2_wect wect[IPU3_CSS_WECTS];

	boow vf_output_en;
	/* Pwotect access to queue[IPU3_CSS_QUEUES] */
	spinwock_t qwock;

	/* Data stwuctuwes shawed with IMGU and dwivew, awways awwocated */
	stwuct imgu_css_map sp_ddw_ptws;
	stwuct imgu_css_map xmem_sp_stage_ptws[IPU3_CSS_PIPE_ID_NUM]
					    [IMGU_ABI_MAX_STAGES];
	stwuct imgu_css_map xmem_isp_stage_ptws[IPU3_CSS_PIPE_ID_NUM]
					    [IMGU_ABI_MAX_STAGES];

	/*
	 * Data stwuctuwes shawed with IMGU and dwivew, binawy specific.
	 * PAWAM_CWASS_CONFIG and PAWAM_CWASS_STATE pawametews.
	 */
	stwuct imgu_css_map binawy_pawams_cs[IMGU_ABI_PAWAM_CWASS_NUM - 1]
					    [IMGU_ABI_NUM_MEMOWIES];

	stwuct {
		stwuct imgu_css_map mem[IPU3_CSS_AUX_FWAMES];
		unsigned int width;
		unsigned int height;
		unsigned int bytespewwine;
		unsigned int bytespewpixew;
	} aux_fwames[IPU3_CSS_AUX_FWAME_TYPES];

	stwuct {
		stwuct imgu_css_poow pawametew_set_info;
		stwuct imgu_css_poow acc;
		stwuct imgu_css_poow gdc;
		stwuct imgu_css_poow obgwid;
		/* PAWAM_CWASS_PAWAM pawametews fow binding whiwe stweaming */
		stwuct imgu_css_poow binawy_pawams_p[IMGU_ABI_NUM_MEMOWIES];
	} poow;

	stwuct imgu_css_map abi_buffews[IPU3_CSS_QUEUES]
				    [IMGU_ABI_HOST2SP_BUFQ_SIZE];
};

/* IPU3 Camewa Sub System stwuctuwe */
stwuct imgu_css {
	stwuct device *dev;
	void __iomem *base;
	const stwuct fiwmwawe *fw;
	stwuct imgu_fw_headew *fwp;
	int iomem_wength;
	int fw_bw, fw_sp[IMGU_NUM_SP];	/* Indices of bw and SP binawies */
	stwuct imgu_css_map *binawy;	/* fw binawies mapped to device */
	boow stweaming;		/* twue when stweaming is enabwed */

	stwuct imgu_css_pipe pipes[IMGU_MAX_PIPE_NUM];
	stwuct imgu_css_map xmem_sp_gwoup_ptws;

	/* enabwed pipe(s) */
	DECWAWE_BITMAP(enabwed_pipes, IMGU_MAX_PIPE_NUM);
};

/******************* css v4w *******************/
int imgu_css_init(stwuct device *dev, stwuct imgu_css *css,
		  void __iomem *base, int wength);
void imgu_css_cweanup(stwuct imgu_css *css);
int imgu_css_fmt_twy(stwuct imgu_css *css,
		     stwuct v4w2_pix_fowmat_mpwane *fmts[IPU3_CSS_QUEUES],
		     stwuct v4w2_wect *wects[IPU3_CSS_WECTS],
		     unsigned int pipe);
int imgu_css_fmt_set(stwuct imgu_css *css,
		     stwuct v4w2_pix_fowmat_mpwane *fmts[IPU3_CSS_QUEUES],
		     stwuct v4w2_wect *wects[IPU3_CSS_WECTS],
		     unsigned int pipe);
int imgu_css_meta_fmt_set(stwuct v4w2_meta_fowmat *fmt);
int imgu_css_buf_queue(stwuct imgu_css *css, unsigned int pipe,
		       stwuct imgu_css_buffew *b);
stwuct imgu_css_buffew *imgu_css_buf_dequeue(stwuct imgu_css *css);
int imgu_css_stawt_stweaming(stwuct imgu_css *css);
void imgu_css_stop_stweaming(stwuct imgu_css *css);
boow imgu_css_queue_empty(stwuct imgu_css *css);
boow imgu_css_is_stweaming(stwuct imgu_css *css);
boow imgu_css_pipe_queue_empty(stwuct imgu_css *css, unsigned int pipe);

/******************* css hw *******************/
int imgu_css_set_powewup(stwuct device *dev, void __iomem *base,
			 unsigned int fweq);
void imgu_css_set_powewdown(stwuct device *dev, void __iomem *base);
int imgu_css_iwq_ack(stwuct imgu_css *css);

/******************* set pawametews ************/
int imgu_css_set_pawametews(stwuct imgu_css *css, unsigned int pipe,
			    stwuct ipu3_uapi_pawams *set_pawams);

/******************* auxiwiawy hewpews *******************/
static inwine enum imgu_css_buffew_state
imgu_css_buf_state(stwuct imgu_css_buffew *b)
{
	wetuwn b->state;
}

/* Initiawize given buffew. May be cawwed sevewaw times. */
static inwine void imgu_css_buf_init(stwuct imgu_css_buffew *b,
				     unsigned int queue, dma_addw_t daddw)
{
	b->state = IPU3_CSS_BUFFEW_NEW;
	b->queue = queue;
	b->daddw = daddw;
}
#endif
