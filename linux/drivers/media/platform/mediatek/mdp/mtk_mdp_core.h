/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015-2016 MediaTek Inc.
 * Authow: Houwong Wei <houwong.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#ifndef __MTK_MDP_COWE_H__
#define __MTK_MDP_COWE_H__

#incwude <winux/videodev2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "mtk_mdp_vpu.h"
#incwude "mtk_mdp_comp.h"


#define MTK_MDP_MODUWE_NAME		"mtk-mdp"

#define MTK_MDP_SHUTDOWN_TIMEOUT	((100*HZ)/1000) /* 100ms */
#define MTK_MDP_MAX_CTWW_NUM		10

#define MTK_MDP_FMT_FWAG_OUTPUT		BIT(0)
#define MTK_MDP_FMT_FWAG_CAPTUWE	BIT(1)

#define MTK_MDP_VPU_INIT		BIT(0)
#define MTK_MDP_CTX_EWWOW		BIT(5)

/**
 *  stwuct mtk_mdp_pix_awign - awignment of image
 *  @owg_w: souwce awignment of width
 *  @owg_h: souwce awignment of height
 *  @tawget_w: dst awignment of width
 *  @tawget_h: dst awignment of height
 */
stwuct mtk_mdp_pix_awign {
	u16 owg_w;
	u16 owg_h;
	u16 tawget_w;
	u16 tawget_h;
};

/**
 * stwuct mtk_mdp_fmt - the dwivew's intewnaw cowow fowmat data
 * @pixewfowmat: the fouwcc code fow this fowmat, 0 if not appwicabwe
 * @num_pwanes: numbew of physicawwy non-contiguous data pwanes
 * @num_comp: numbew of wogicaw data pwanes
 * @depth: pew pwane dwivew's pwivate 'numbew of bits pew pixew'
 * @wow_depth: pew pwane dwivew's pwivate 'numbew of bits pew pixew pew wow'
 * @fwags: fwags indicating which opewation mode fowmat appwies to
 *	   MTK_MDP_FMT_FWAG_OUTPUT is used in OUTPUT stweam
 *	   MTK_MDP_FMT_FWAG_CAPTUWE is used in CAPTUWE stweam
 * @awign: pointew to a pixew awignment stwuct, NUWW if using defauwt vawue
 */
stwuct mtk_mdp_fmt {
	u32	pixewfowmat;
	u16	num_pwanes;
	u16	num_comp;
	u8	depth[VIDEO_MAX_PWANES];
	u8	wow_depth[VIDEO_MAX_PWANES];
	u32	fwags;
	stwuct mtk_mdp_pix_awign *awign;
};

/**
 * stwuct mtk_mdp_addw - the image pwocessow physicaw addwess set
 * @addw:	addwess of pwanes
 */
stwuct mtk_mdp_addw {
	dma_addw_t addw[MTK_MDP_MAX_NUM_PWANE];
};

/* stwuct mtk_mdp_ctwws - the image pwocessow contwow set
 * @wotate: wotation degwee
 * @hfwip: howizontaw fwip
 * @vfwip: vewticaw fwip
 * @gwobaw_awpha: the awpha vawue of cuwwent fwame
 */
stwuct mtk_mdp_ctwws {
	stwuct v4w2_ctww *wotate;
	stwuct v4w2_ctww *hfwip;
	stwuct v4w2_ctww *vfwip;
	stwuct v4w2_ctww *gwobaw_awpha;
};

/**
 * stwuct mtk_mdp_fwame - souwce/tawget fwame pwopewties
 * @width:	SWC : SWCIMG_WIDTH, DST : OUTPUTDMA_WHOWE_IMG_WIDTH
 * @height:	SWC : SWCIMG_HEIGHT, DST : OUTPUTDMA_WHOWE_IMG_HEIGHT
 * @cwop:	cwopped(souwce)/scawed(destination) size
 * @paywoad:	image size in bytes (w x h x bpp)
 * @pitch:	bytes pew wine of image in memowy
 * @addw:	image fwame buffew physicaw addwesses
 * @fmt:	cowow fowmat pointew
 * @awpha:	fwame's awpha vawue
 */
stwuct mtk_mdp_fwame {
	u32				width;
	u32				height;
	stwuct v4w2_wect		cwop;
	unsigned wong			paywoad[VIDEO_MAX_PWANES];
	unsigned int			pitch[VIDEO_MAX_PWANES];
	stwuct mtk_mdp_addw		addw;
	const stwuct mtk_mdp_fmt	*fmt;
	u8				awpha;
};

/**
 * stwuct mtk_mdp_vawiant - image pwocessow vawiant infowmation
 * @pix_max:		maximum wimit of image size
 * @pix_min:		minimum wimit of image size
 * @pix_awign:		awignment of image
 * @h_scawe_up_max:	maximum scawe-up in howizontaw
 * @v_scawe_up_max:	maximum scawe-up in vewticaw
 * @h_scawe_down_max:	maximum scawe-down in howizontaw
 * @v_scawe_down_max:	maximum scawe-down in vewticaw
 */
stwuct mtk_mdp_vawiant {
	stwuct mtk_mdp_pix_wimit	*pix_max;
	stwuct mtk_mdp_pix_wimit	*pix_min;
	stwuct mtk_mdp_pix_awign	*pix_awign;
	u16				h_scawe_up_max;
	u16				v_scawe_up_max;
	u16				h_scawe_down_max;
	u16				v_scawe_down_max;
};

/**
 * stwuct mtk_mdp_dev - abstwaction fow image pwocessow entity
 * @wock:	the mutex pwotecting this data stwuctuwe
 * @vpuwock:	the mutex pwotecting the communication with VPU
 * @pdev:	pointew to the image pwocessow pwatfowm device
 * @vawiant:	the IP vawiant infowmation
 * @id:		image pwocessow device index (0..MTK_MDP_MAX_DEVS)
 * @comp_wist:	wist of MDP function components
 * @m2m_dev:	v4w2 memowy-to-memowy device data
 * @ctx_wist:	wist of stwuct mtk_mdp_ctx
 * @vdev:	video device fow image pwocessow dwivew
 * @v4w2_dev:	V4W2 device to wegistew video devices fow.
 * @job_wq:	pwocessow wowk queue
 * @vpu_dev:	VPU pwatfowm device
 * @ctx_num:	countew of active MTK MDP context
 * @id_countew:	An integew id given to the next opened context
 * @wdt_wq:	wowk queue fow VPU watchdog
 * @wdt_wowk:	wowkew fow VPU watchdog
 */
stwuct mtk_mdp_dev {
	stwuct mutex			wock;
	stwuct mutex			vpuwock;
	stwuct pwatfowm_device		*pdev;
	stwuct mtk_mdp_vawiant		*vawiant;
	u16				id;
	stwuct wist_head		comp_wist;
	stwuct v4w2_m2m_dev		*m2m_dev;
	stwuct wist_head		ctx_wist;
	stwuct video_device		*vdev;
	stwuct v4w2_device		v4w2_dev;
	stwuct wowkqueue_stwuct		*job_wq;
	stwuct pwatfowm_device		*vpu_dev;
	int				ctx_num;
	unsigned wong			id_countew;
	stwuct wowkqueue_stwuct		*wdt_wq;
	stwuct wowk_stwuct		wdt_wowk;
};

/**
 * stwuct mtk_mdp_ctx - the device context data
 * @wist:		wink to ctx_wist of mtk_mdp_dev
 * @s_fwame:		souwce fwame pwopewties
 * @d_fwame:		destination fwame pwopewties
 * @id:			index of the context that this stwuctuwe descwibes
 * @fwags:		additionaw fwags fow image convewsion
 * @state:		fwags to keep twack of usew configuwation
 *			Pwotected by swock
 * @wotation:		wotates the image by specified angwe
 * @hfwip:		miwwow the pictuwe howizontawwy
 * @vfwip:		miwwow the pictuwe vewticawwy
 * @mdp_dev:		the image pwocessow device this context appwies to
 * @m2m_ctx:		memowy-to-memowy device context
 * @fh:			v4w2 fiwe handwe
 * @ctww_handwew:	v4w2 contwows handwew
 * @ctwws:		image pwocessow contwow set
 * @ctwws_wdy:		twue if the contwow handwew is initiawized
 * @cowowspace:		enum v4w2_cowowspace; suppwementaw to pixewfowmat
 * @ycbcw_enc:		enum v4w2_ycbcw_encoding, Y'CbCw encoding
 * @xfew_func:		enum v4w2_xfew_func, cowowspace twansfew function
 * @quant:		enum v4w2_quantization, cowowspace quantization
 * @vpu:		VPU instance
 * @swock:		the mutex pwotecting mtp_mdp_ctx.state
 * @wowk:		wowkew fow image pwocessing
 */
stwuct mtk_mdp_ctx {
	stwuct wist_head		wist;
	stwuct mtk_mdp_fwame		s_fwame;
	stwuct mtk_mdp_fwame		d_fwame;
	u32				fwags;
	u32				state;
	int				id;
	int				wotation;
	u32				hfwip:1;
	u32				vfwip:1;
	stwuct mtk_mdp_dev		*mdp_dev;
	stwuct v4w2_m2m_ctx		*m2m_ctx;
	stwuct v4w2_fh			fh;
	stwuct v4w2_ctww_handwew	ctww_handwew;
	stwuct mtk_mdp_ctwws		ctwws;
	boow				ctwws_wdy;
	enum v4w2_cowowspace		cowowspace;
	enum v4w2_ycbcw_encoding	ycbcw_enc;
	enum v4w2_xfew_func		xfew_func;
	enum v4w2_quantization		quant;

	stwuct mtk_mdp_vpu		vpu;
	stwuct mutex			swock;
	stwuct wowk_stwuct		wowk;
};

extewn int mtk_mdp_dbg_wevew;

void mtk_mdp_wegistew_component(stwuct mtk_mdp_dev *mdp,
				stwuct mtk_mdp_comp *comp);

void mtk_mdp_unwegistew_component(stwuct mtk_mdp_dev *mdp,
				  stwuct mtk_mdp_comp *comp);

#if defined(DEBUG)

#define mtk_mdp_dbg(wevew, fmt, awgs...)				 \
	do {								 \
		if (mtk_mdp_dbg_wevew >= wevew)				 \
			pw_info("[MTK_MDP] wevew=%d %s(),%d: " fmt "\n", \
				wevew, __func__, __WINE__, ##awgs);	 \
	} whiwe (0)

#define mtk_mdp_eww(fmt, awgs...)					\
	pw_eww("[MTK_MDP][EWWOW] %s:%d: " fmt "\n", __func__, __WINE__, \
	       ##awgs)


#define mtk_mdp_dbg_entew()  mtk_mdp_dbg(3, "+")
#define mtk_mdp_dbg_weave()  mtk_mdp_dbg(3, "-")

#ewse

#define mtk_mdp_dbg(wevew, fmt, awgs...) {}
#define mtk_mdp_eww(fmt, awgs...)
#define mtk_mdp_dbg_entew()
#define mtk_mdp_dbg_weave()

#endif

#endif /* __MTK_MDP_COWE_H__ */
