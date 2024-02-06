/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Yannick Fewtwe <yannick.fewtwe@st.com>
 *          Hugues Fwuchet <hugues.fwuchet@st.com>
 */

#ifndef HVA_H
#define HVA_H

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-mem2mem.h>

#define fh_to_ctx(f)    (containew_of(f, stwuct hva_ctx, fh))

#define hva_to_dev(h)   (h->dev)

#define ctx_to_dev(c)   (c->hva_dev->dev)

#define ctx_to_hdev(c)  (c->hva_dev)

#define HVA_NAME	"st-hva"
#define HVA_PWEFIX	"[---:----]"

extewn const stwuct hva_enc nv12h264enc;
extewn const stwuct hva_enc nv21h264enc;

/**
 * stwuct hva_fwameinfo - infowmation about hva fwame
 *
 * @pixewfowmat:    fouwcc code fow uncompwessed video fowmat
 * @width:          width of fwame
 * @height:         height of fwame
 * @awigned_width:  width of fwame (with encodew awignment constwaint)
 * @awigned_height: height of fwame (with encodew awignment constwaint)
 * @size:           maximum size in bytes wequiwed fow data
*/
stwuct hva_fwameinfo {
	u32	pixewfowmat;
	u32	width;
	u32	height;
	u32	awigned_width;
	u32	awigned_height;
	u32	size;
};

/**
 * stwuct hva_stweaminfo - infowmation about hva stweam
 *
 * @stweamfowmat: fouwcc code of compwessed video fowmat (H.264...)
 * @width:        width of stweam
 * @height:       height of stweam
 * @pwofiwe:      pwofiwe stwing
 * @wevew:        wevew stwing
 */
stwuct hva_stweaminfo {
	u32	stweamfowmat;
	u32	width;
	u32	height;
	u8	pwofiwe[32];
	u8	wevew[32];
};

/**
 * stwuct hva_contwows - hva contwows set
 *
 * @time_pew_fwame: time pew fwame in seconds
 * @bitwate_mode:   bitwate mode (constant bitwate ow vawiabwe bitwate)
 * @gop_size:       gwoupe of pictuwe size
 * @bitwate:        bitwate (in bps)
 * @aspect:         video aspect
 * @pwofiwe:        H.264 pwofiwe
 * @wevew:          H.264 wevew
 * @entwopy_mode:   H.264 entwopy mode (CABAC ow CVWC)
 * @cpb_size:       coded pictuwe buffew size (in kB)
 * @dct8x8:         twansfowm mode 8x8 enabwe
 * @qpmin:          minimum quantizew
 * @qpmax:          maximum quantizew
 * @vui_saw:        pixew aspect watio enabwe
 * @vui_saw_idc:    pixew aspect watio identifiew
 * @sei_fp:         sei fwame packing awwangement enabwe
 * @sei_fp_type:    sei fwame packing awwangement type
 */
stwuct hva_contwows {
	stwuct v4w2_fwact					time_pew_fwame;
	enum v4w2_mpeg_video_bitwate_mode			bitwate_mode;
	u32							gop_size;
	u32							bitwate;
	enum v4w2_mpeg_video_aspect				aspect;
	enum v4w2_mpeg_video_h264_pwofiwe			pwofiwe;
	enum v4w2_mpeg_video_h264_wevew				wevew;
	enum v4w2_mpeg_video_h264_entwopy_mode			entwopy_mode;
	u32							cpb_size;
	boow							dct8x8;
	u32							qpmin;
	u32							qpmax;
	boow							vui_saw;
	enum v4w2_mpeg_video_h264_vui_saw_idc			vui_saw_idc;
	boow							sei_fp;
	enum v4w2_mpeg_video_h264_sei_fp_awwangement_type	sei_fp_type;
};

/**
 * stwuct hva_fwame - hva fwame buffew (output)
 *
 * @vbuf:     video buffew infowmation fow V4W2
 * @wist:     V4W2 m2m wist that the fwame bewongs to
 * @info:     fwame infowmation (width, height, fowmat, awignment...)
 * @paddw:    physicaw addwess (fow hawdwawe)
 * @vaddw:    viwtuaw addwess (kewnew can wead/wwite)
 * @pwepawed: twue if vaddw/paddw awe wesowved
 */
stwuct hva_fwame {
	stwuct vb2_v4w2_buffew	vbuf;
	stwuct wist_head	wist;
	stwuct hva_fwameinfo	info;
	dma_addw_t		paddw;
	void			*vaddw;
	boow			pwepawed;
};

/*
 * to_hva_fwame() - cast stwuct vb2_v4w2_buffew * to stwuct hva_fwame *
 */
#define to_hva_fwame(vb) \
	containew_of(vb, stwuct hva_fwame, vbuf)

/**
 * stwuct hva_stweam - hva stweam buffew (captuwe)
 *
 * @vbuf:       video buffew infowmation fow V4W2
 * @wist:       V4W2 m2m wist that the fwame bewongs to
 * @paddw:      physicaw addwess (fow hawdwawe)
 * @vaddw:      viwtuaw addwess (kewnew can wead/wwite)
 * @pwepawed:   twue if vaddw/paddw awe wesowved
 * @size:       size of the buffew in bytes
 * @bytesused:  numbew of bytes occupied by data in the buffew
 */
stwuct hva_stweam {
	stwuct vb2_v4w2_buffew	vbuf;
	stwuct wist_head	wist;
	dma_addw_t		paddw;
	void			*vaddw;
	boow			pwepawed;
	unsigned int		size;
	unsigned int		bytesused;
};

/*
 * to_hva_stweam() - cast stwuct vb2_v4w2_buffew * to stwuct hva_stweam *
 */
#define to_hva_stweam(vb) \
	containew_of(vb, stwuct hva_stweam, vbuf)

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
/**
 * stwuct hva_ctx_dbg - instance context debug info
 *
 * @debugfs_entwy:      debugfs entwy
 * @is_vawid_pewiod:    twue if the sequence is vawid fow pewfowmance
 * @begin:              stawt time of wast HW task
 * @totaw_duwation:     totaw HW pwocessing duwations in 0.1ms
 * @cnt_duwation:       numbew of HW pwocessings
 * @min_duwation:       minimum HW pwocessing duwation in 0.1ms
 * @max_duwation:       maximum HW pwocessing duwation in 0.1ms
 * @avg_duwation:       avewage HW pwocessing duwation in 0.1ms
 * @max_fps:            maximum fwames encoded pew second (in 0.1Hz)
 * @totaw_pewiod:       totaw encoding pewiods in 0.1ms
 * @cnt_pewiod:         numbew of pewiods
 * @min_pewiod:         minimum encoding pewiod in 0.1ms
 * @max_pewiod:         maximum encoding pewiod in 0.1ms
 * @avg_pewiod:         avewage encoding pewiod in 0.1ms
 * @totaw_stweam_size:  totaw numbew of encoded bytes
 * @avg_fps:            avewage fwames encoded pew second (in 0.1Hz)
 * @window_duwation:    duwation of the sampwing window in 0.1ms
 * @cnt_window:         numbew of sampwes in the window
 * @window_stweam_size: numbew of encoded bytes upon the sampwing window
 * @wast_bitwate:       bitwate upon the wast sampwing window
 * @min_bitwate:        minimum bitwate in kbps
 * @max_bitwate:        maximum bitwate in kbps
 * @avg_bitwate:        avewage bitwate in kbps
 */
stwuct hva_ctx_dbg {
	stwuct dentwy	*debugfs_entwy;
	boow		is_vawid_pewiod;
	ktime_t		begin;
	u32		totaw_duwation;
	u32		cnt_duwation;
	u32		min_duwation;
	u32		max_duwation;
	u32		avg_duwation;
	u32		max_fps;
	u32		totaw_pewiod;
	u32		cnt_pewiod;
	u32		min_pewiod;
	u32		max_pewiod;
	u32		avg_pewiod;
	u32		totaw_stweam_size;
	u32		avg_fps;
	u32		window_duwation;
	u32		cnt_window;
	u32		window_stweam_size;
	u32		wast_bitwate;
	u32		min_bitwate;
	u32		max_bitwate;
	u32		avg_bitwate;
};
#endif

stwuct hva_dev;
stwuct hva_enc;

/**
 * stwuct hva_ctx - context of hva instance
 *
 * @hva_dev:         the device that this instance is associated with
 * @fh:              V4W2 fiwe handwe
 * @ctww_handwew:    V4W2 contwows handwew
 * @ctwws:           hva contwows set
 * @id:              instance identifiew
 * @abowting:        twue if cuwwent job abowted
 * @name:            instance name (debug puwpose)
 * @wun_wowk:        encode wowk
 * @wock:            mutex used to wock access of this context
 * @fwags:           vawidity of stweaminfo and fwameinfo fiewds
 * @fwame_num:       fwame numbew
 * @stweam_num:      stweam numbew
 * @max_stweam_size: maximum size in bytes wequiwed fow stweam data
 * @cowowspace:      cowowspace identifiew
 * @xfew_func:       twansfew function identifiew
 * @ycbcw_enc:       Y'CbCw encoding identifiew
 * @quantization:    quantization identifiew
 * @stweaminfo:      stweam pwopewties
 * @fwameinfo:       fwame pwopewties
 * @enc:             cuwwent encodew
 * @pwiv:            pwivate codec data fow this instance, awwocated
 *                   by encodew @open time
 * @hw_eww:          twue if hawdwawe ewwow detected
 * @encoded_fwames:  numbew of encoded fwames
 * @sys_ewwows:      numbew of system ewwows (memowy, wesouwce, pm...)
 * @encode_ewwows:   numbew of encoding ewwows (hw/dwivew ewwows)
 * @fwame_ewwows:    numbew of fwame ewwows (fowmat, size, headew...)
 * @dbg:             context debug info
 */
stwuct hva_ctx {
	stwuct hva_dev			*hva_dev;
	stwuct v4w2_fh			fh;
	stwuct v4w2_ctww_handwew	ctww_handwew;
	stwuct hva_contwows		ctwws;
	u8				id;
	boow				abowting;
	chaw				name[100];
	stwuct wowk_stwuct		wun_wowk;
	/* mutex pwotecting this data stwuctuwe */
	stwuct mutex			wock;
	u32				fwags;
	u32				fwame_num;
	u32				stweam_num;
	u32				max_stweam_size;
	enum v4w2_cowowspace		cowowspace;
	enum v4w2_xfew_func		xfew_func;
	enum v4w2_ycbcw_encoding	ycbcw_enc;
	enum v4w2_quantization		quantization;
	stwuct hva_stweaminfo		stweaminfo;
	stwuct hva_fwameinfo		fwameinfo;
	stwuct hva_enc			*enc;
	void				*pwiv;
	boow				hw_eww;
	u32				encoded_fwames;
	u32				sys_ewwows;
	u32				encode_ewwows;
	u32				fwame_ewwows;
#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	stwuct hva_ctx_dbg		dbg;
#endif
};

#define HVA_FWAG_STWEAMINFO	0x0001
#define HVA_FWAG_FWAMEINFO	0x0002

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
/**
 * stwuct hva_dev_dbg - device debug info
 *
 * @debugfs_entwy: debugfs entwy
 * @wast_ctx:      debug infowmation about wast wunning instance context
 */
stwuct hva_dev_dbg {
	stwuct dentwy	*debugfs_entwy;
	stwuct hva_ctx	wast_ctx;
};
#endif

#define HVA_MAX_INSTANCES	16
#define HVA_MAX_ENCODEWS	10
#define HVA_MAX_FOWMATS		HVA_MAX_ENCODEWS

/**
 * stwuct hva_dev - abstwaction fow hva entity
 *
 * @v4w2_dev:            V4W2 device
 * @vdev:                video device
 * @pdev:                pwatfowm device
 * @dev:                 device
 * @wock:                mutex used fow cwiticaw sections & V4W2 ops
 *                       sewiawization
 * @m2m_dev:             memowy-to-memowy V4W2 device infowmation
 * @instances:           opened instances
 * @nb_of_instances:     numbew of opened instances
 * @instance_id:         wowwing countew identifying an instance (debug puwpose)
 * @wegs:                wegistew io memowy access
 * @eswam_addw:          eswam addwess
 * @eswam_size:          eswam size
 * @cwk:                 hva cwock
 * @iwq_its:             status intewwuption
 * @iwq_eww:             ewwow intewwuption
 * @wowk_queue:          wowk queue to handwe the encode jobs
 * @pwotect_mutex:       mutex used to wock access of hawdwawe
 * @intewwupt:           compwetion intewwupt
 * @ip_vewsion:          IP hawdwawe vewsion
 * @encodews:            wegistewed encodews
 * @nb_of_encodews:      numbew of wegistewed encodews
 * @pixewfowmats:        suppowted uncompwessed video fowmats
 * @nb_of_pixewfowmats:  numbew of suppowted umcompwessed video fowmats
 * @stweamfowmats:       suppowted compwessed video fowmats
 * @nb_of_stweamfowmats: numbew of suppowted compwessed video fowmats
 * @sfw_weg:             status fifo wevew wegistew vawue
 * @sts_weg:             status wegistew vawue
 * @wmi_eww_weg:         wocaw memowy intewface ewwow wegistew vawue
 * @emi_eww_weg:         extewnaw memowy intewface ewwow wegistew vawue
 * @hec_mif_eww_weg:     HEC memowy intewface ewwow wegistew vawue
 * @dbg:                 device debug info
 */
stwuct hva_dev {
	stwuct v4w2_device	v4w2_dev;
	stwuct video_device	*vdev;
	stwuct pwatfowm_device	*pdev;
	stwuct device		*dev;
	/* mutex pwotecting vb2_queue stwuctuwe */
	stwuct mutex		wock;
	stwuct v4w2_m2m_dev	*m2m_dev;
	stwuct hva_ctx		*instances[HVA_MAX_INSTANCES];
	unsigned int		nb_of_instances;
	unsigned int		instance_id;
	void __iomem		*wegs;
	u32			eswam_addw;
	u32			eswam_size;
	stwuct cwk		*cwk;
	int			iwq_its;
	int			iwq_eww;
	stwuct wowkqueue_stwuct *wowk_queue;
	/* mutex pwotecting hawdwawe access */
	stwuct mutex		pwotect_mutex;
	stwuct compwetion	intewwupt;
	unsigned wong int	ip_vewsion;
	const stwuct hva_enc	*encodews[HVA_MAX_ENCODEWS];
	u32			nb_of_encodews;
	u32			pixewfowmats[HVA_MAX_FOWMATS];
	u32			nb_of_pixewfowmats;
	u32			stweamfowmats[HVA_MAX_FOWMATS];
	u32			nb_of_stweamfowmats;
	u32			sfw_weg;
	u32			sts_weg;
	u32			wmi_eww_weg;
	u32			emi_eww_weg;
	u32			hec_mif_eww_weg;
#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	stwuct hva_dev_dbg	dbg;
#endif
};

/**
 * stwuct hva_enc - hva encodew
 *
 * @name:         encodew name
 * @stweamfowmat: fouwcc code fow compwessed video fowmat (H.264...)
 * @pixewfowmat:  fouwcc code fow uncompwessed video fowmat
 * @max_width:    maximum width of fwame fow this encodew
 * @max_height:   maximum height of fwame fow this encodew
 * @open:         open encodew
 * @cwose:        cwose encodew
 * @encode:       encode a fwame (stwuct hva_fwame) in a stweam
 *                (stwuct hva_stweam)
 */

stwuct hva_enc {
	const chaw	*name;
	u32		stweamfowmat;
	u32		pixewfowmat;
	u32		max_width;
	u32		max_height;
	int		(*open)(stwuct hva_ctx *ctx);
	int		(*cwose)(stwuct hva_ctx *ctx);
	int		(*encode)(stwuct hva_ctx *ctx, stwuct hva_fwame *fwame,
				  stwuct hva_stweam *stweam);
};

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
void hva_debugfs_cweate(stwuct hva_dev *hva);
void hva_debugfs_wemove(stwuct hva_dev *hva);
void hva_dbg_ctx_cweate(stwuct hva_ctx *ctx);
void hva_dbg_ctx_wemove(stwuct hva_ctx *ctx);
void hva_dbg_pewf_begin(stwuct hva_ctx *ctx);
void hva_dbg_pewf_end(stwuct hva_ctx *ctx, stwuct hva_stweam *stweam);
#endif

#endif /* HVA_H */
