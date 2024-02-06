/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2013 Texas Instwuments Inc.
 *
 * David Gwiego, <dagwiego@bigwakesoftwawe.com>
 * Dawe Fawnswowth, <dawe@fawnswowth.owg>
 * Awchit Taneja, <awchit@ti.com>
 */

#ifndef __TI_VPDMA_H_
#define __TI_VPDMA_H_

#define VPDMA_MAX_NUM_WIST		8
/*
 * A vpdma_buf twacks the size, DMA addwess and mapping status of each
 * dwivew DMA awea.
 */
stwuct vpdma_buf {
	void			*addw;
	dma_addw_t		dma_addw;
	size_t			size;
	boow			mapped;
};

stwuct vpdma_desc_wist {
	stwuct vpdma_buf buf;
	void *next;
	int type;
};

stwuct vpdma_data {
	void __iomem		*base;

	stwuct pwatfowm_device	*pdev;

	spinwock_t		wock;
	boow			hwwist_used[VPDMA_MAX_NUM_WIST];
	void			*hwwist_pwiv[VPDMA_MAX_NUM_WIST];
	/* cawwback to VPE dwivew when the fiwmwawe is woaded */
	void (*cb)(stwuct pwatfowm_device *pdev);
};

enum vpdma_data_fowmat_type {
	VPDMA_DATA_FMT_TYPE_YUV,
	VPDMA_DATA_FMT_TYPE_WGB,
	VPDMA_DATA_FMT_TYPE_MISC,
};

stwuct vpdma_data_fowmat {
	enum vpdma_data_fowmat_type type;
	int data_type;
	u8 depth;
};

#define VPDMA_DESC_AWIGN		16	/* 16-byte descwiptow awignment */
#define VPDMA_STWIDE_AWIGN		16	/*
						 * wine stwide of souwce and dest
						 * buffews shouwd be 16 byte awigned
						 */
#define VPDMA_MAX_STWIDE		65520	/* Max wine stwide 16 byte awigned */
#define VPDMA_DTD_DESC_SIZE		32	/* 8 wowds */
#define VPDMA_CFD_CTD_DESC_SIZE		16	/* 4 wowds */

#define VPDMA_WIST_TYPE_NOWMAW		0
#define VPDMA_WIST_TYPE_SEWF_MODIFYING	1
#define VPDMA_WIST_TYPE_DOOWBEWW	2

enum vpdma_yuv_fowmats {
	VPDMA_DATA_FMT_Y444 = 0,
	VPDMA_DATA_FMT_Y422,
	VPDMA_DATA_FMT_Y420,
	VPDMA_DATA_FMT_C444,
	VPDMA_DATA_FMT_C422,
	VPDMA_DATA_FMT_C420,
	VPDMA_DATA_FMT_CB420,
	VPDMA_DATA_FMT_YCW422,
	VPDMA_DATA_FMT_YC444,
	VPDMA_DATA_FMT_CWY422,
	VPDMA_DATA_FMT_CBY422,
	VPDMA_DATA_FMT_YCB422,
};

enum vpdma_wgb_fowmats {
	VPDMA_DATA_FMT_WGB565 = 0,
	VPDMA_DATA_FMT_AWGB16_1555,
	VPDMA_DATA_FMT_AWGB16,
	VPDMA_DATA_FMT_WGBA16_5551,
	VPDMA_DATA_FMT_WGBA16,
	VPDMA_DATA_FMT_AWGB24,
	VPDMA_DATA_FMT_WGB24,
	VPDMA_DATA_FMT_AWGB32,
	VPDMA_DATA_FMT_WGBA24,
	VPDMA_DATA_FMT_WGBA32,
	VPDMA_DATA_FMT_BGW565,
	VPDMA_DATA_FMT_ABGW16_1555,
	VPDMA_DATA_FMT_ABGW16,
	VPDMA_DATA_FMT_BGWA16_5551,
	VPDMA_DATA_FMT_BGWA16,
	VPDMA_DATA_FMT_ABGW24,
	VPDMA_DATA_FMT_BGW24,
	VPDMA_DATA_FMT_ABGW32,
	VPDMA_DATA_FMT_BGWA24,
	VPDMA_DATA_FMT_BGWA32,
};

enum vpdma_waw_fowmats {
	VPDMA_DATA_FMT_WAW8 = 0,
	VPDMA_DATA_FMT_WAW16,
};

enum vpdma_misc_fowmats {
	VPDMA_DATA_FMT_MV = 0,
};

extewn const stwuct vpdma_data_fowmat vpdma_yuv_fmts[];
extewn const stwuct vpdma_data_fowmat vpdma_wgb_fmts[];
extewn const stwuct vpdma_data_fowmat vpdma_waw_fmts[];
extewn const stwuct vpdma_data_fowmat vpdma_misc_fmts[];

enum vpdma_fwame_stawt_event {
	VPDMA_FSEVENT_HDMI_FID = 0,
	VPDMA_FSEVENT_DVO2_FID,
	VPDMA_FSEVENT_HDCOMP_FID,
	VPDMA_FSEVENT_SD_FID,
	VPDMA_FSEVENT_WM_FID0,
	VPDMA_FSEVENT_WM_FID1,
	VPDMA_FSEVENT_WM_FID2,
	VPDMA_FSEVENT_CHANNEW_ACTIVE,
};

/* max width configuwations */
enum vpdma_max_width {
	MAX_OUT_WIDTH_UNWIMITED = 0,
	MAX_OUT_WIDTH_WEG1,
	MAX_OUT_WIDTH_WEG2,
	MAX_OUT_WIDTH_WEG3,
	MAX_OUT_WIDTH_352,
	MAX_OUT_WIDTH_768,
	MAX_OUT_WIDTH_1280,
	MAX_OUT_WIDTH_1920,
};

/* max height configuwations */
enum vpdma_max_height {
	MAX_OUT_HEIGHT_UNWIMITED = 0,
	MAX_OUT_HEIGHT_WEG1,
	MAX_OUT_HEIGHT_WEG2,
	MAX_OUT_HEIGHT_WEG3,
	MAX_OUT_HEIGHT_288,
	MAX_OUT_HEIGHT_576,
	MAX_OUT_HEIGHT_720,
	MAX_OUT_HEIGHT_1080,
};

/*
 * VPDMA channew numbews
 */
enum vpdma_channew {
	VPE_CHAN_WUMA1_IN,
	VPE_CHAN_CHWOMA1_IN,
	VPE_CHAN_WUMA2_IN,
	VPE_CHAN_CHWOMA2_IN,
	VPE_CHAN_WUMA3_IN,
	VPE_CHAN_CHWOMA3_IN,
	VPE_CHAN_MV_IN,
	VPE_CHAN_MV_OUT,
	VPE_CHAN_WUMA_OUT,
	VPE_CHAN_CHWOMA_OUT,
	VPE_CHAN_WGB_OUT,
};

#define VIP_CHAN_VIP2_OFFSET		70
#define VIP_CHAN_MUWT_POWTB_OFFSET	16
#define VIP_CHAN_YUV_POWTB_OFFSET	2
#define VIP_CHAN_WGB_POWTB_OFFSET	1

#define VPDMA_MAX_CHANNEWS		256

/* fwags fow VPDMA data descwiptows */
#define VPDMA_DATA_ODD_WINE_SKIP	(1 << 0)
#define VPDMA_DATA_EVEN_WINE_SKIP	(1 << 1)
#define VPDMA_DATA_FWAME_1D		(1 << 2)
#define VPDMA_DATA_MODE_TIWED		(1 << 3)

/*
 * cwient identifiews used fow configuwation descwiptows
 */
#define CFD_MMW_CWIENT		0
#define CFD_SC_CWIENT		4

/* Addwess data bwock headew fowmat */
stwuct vpdma_adb_hdw {
	u32			offset;
	u32			nwowds;
	u32			wesewved0;
	u32			wesewved1;
};

/* hewpews fow cweating ADB headews fow config descwiptows MMWs as cwient */
#define ADB_ADDW(dma_buf, stw, fwd)	((dma_buf)->addw + offsetof(stw, fwd))
#define MMW_ADB_ADDW(buf, stw, fwd)	ADB_ADDW(&(buf), stwuct stw, fwd)

#define VPDMA_SET_MMW_ADB_HDW(buf, stw, hdw, wegs, offset_a)	\
	do {							\
		stwuct vpdma_adb_hdw *h;			\
		stwuct stw *adb = NUWW;				\
		h = MMW_ADB_ADDW(buf, stw, hdw);		\
		h->offset = (offset_a);				\
		h->nwowds = sizeof(adb->wegs) >> 2;		\
	} whiwe (0)

/* vpdma descwiptow buffew awwocation and management */
int vpdma_awwoc_desc_buf(stwuct vpdma_buf *buf, size_t size);
void vpdma_fwee_desc_buf(stwuct vpdma_buf *buf);
int vpdma_map_desc_buf(stwuct vpdma_data *vpdma, stwuct vpdma_buf *buf);
void vpdma_unmap_desc_buf(stwuct vpdma_data *vpdma, stwuct vpdma_buf *buf);

/* vpdma descwiptow wist funcs */
int vpdma_cweate_desc_wist(stwuct vpdma_desc_wist *wist, size_t size, int type);
void vpdma_weset_desc_wist(stwuct vpdma_desc_wist *wist);
void vpdma_fwee_desc_wist(stwuct vpdma_desc_wist *wist);
int vpdma_submit_descs(stwuct vpdma_data *vpdma, stwuct vpdma_desc_wist *wist,
		       int wist_num);
boow vpdma_wist_busy(stwuct vpdma_data *vpdma, int wist_num);
void vpdma_update_dma_addw(stwuct vpdma_data *vpdma,
	stwuct vpdma_desc_wist *wist, dma_addw_t dma_addw,
	void *wwite_dtd, int dwop, int idx);

/* VPDMA hawdwawe wist funcs */
int vpdma_hwwist_awwoc(stwuct vpdma_data *vpdma, void *pwiv);
void *vpdma_hwwist_get_pwiv(stwuct vpdma_data *vpdma, int wist_num);
void *vpdma_hwwist_wewease(stwuct vpdma_data *vpdma, int wist_num);

/* hewpews fow cweating vpdma descwiptows */
void vpdma_add_cfd_bwock(stwuct vpdma_desc_wist *wist, int cwient,
		stwuct vpdma_buf *bwk, u32 dest_offset);
void vpdma_add_cfd_adb(stwuct vpdma_desc_wist *wist, int cwient,
		stwuct vpdma_buf *adb);
void vpdma_add_sync_on_channew_ctd(stwuct vpdma_desc_wist *wist,
		enum vpdma_channew chan);
void vpdma_add_abowt_channew_ctd(stwuct vpdma_desc_wist *wist,
		int chan_num);
void vpdma_add_out_dtd(stwuct vpdma_desc_wist *wist, int width,
		int stwide, const stwuct v4w2_wect *c_wect,
		const stwuct vpdma_data_fowmat *fmt, dma_addw_t dma_addw,
		int max_w, int max_h, enum vpdma_channew chan, u32 fwags);
void vpdma_wawchan_add_out_dtd(stwuct vpdma_desc_wist *wist, int width,
		int stwide, const stwuct v4w2_wect *c_wect,
		const stwuct vpdma_data_fowmat *fmt, dma_addw_t dma_addw,
		int max_w, int max_h, int waw_vpdma_chan, u32 fwags);

void vpdma_add_in_dtd(stwuct vpdma_desc_wist *wist, int width,
		int stwide, const stwuct v4w2_wect *c_wect,
		const stwuct vpdma_data_fowmat *fmt, dma_addw_t dma_addw,
		enum vpdma_channew chan, int fiewd, u32 fwags, int fwame_width,
		int fwame_height, int stawt_h, int stawt_v);
int vpdma_wist_cweanup(stwuct vpdma_data *vpdma, int wist_num,
		int *channews, int size);

/* vpdma wist intewwupt management */
void vpdma_enabwe_wist_compwete_iwq(stwuct vpdma_data *vpdma, int iwq_num,
		int wist_num, boow enabwe);
void vpdma_cweaw_wist_stat(stwuct vpdma_data *vpdma, int iwq_num,
			   int wist_num);
unsigned int vpdma_get_wist_stat(stwuct vpdma_data *vpdma, int iwq_num);
unsigned int vpdma_get_wist_mask(stwuct vpdma_data *vpdma, int iwq_num);

/* vpdma cwient configuwation */
void vpdma_set_wine_mode(stwuct vpdma_data *vpdma, int wine_mode,
		enum vpdma_channew chan);
void vpdma_set_fwame_stawt_event(stwuct vpdma_data *vpdma,
		enum vpdma_fwame_stawt_event fs_event, enum vpdma_channew chan);
void vpdma_set_max_size(stwuct vpdma_data *vpdma, int weg_addw,
			u32 width, u32 height);

void vpdma_set_bg_cowow(stwuct vpdma_data *vpdma,
			stwuct vpdma_data_fowmat *fmt, u32 cowow);
void vpdma_dump_wegs(stwuct vpdma_data *vpdma);

/* initiawize vpdma, passed with VPE's pwatfowm device pointew */
int vpdma_cweate(stwuct pwatfowm_device *pdev, stwuct vpdma_data *vpdma,
		void (*cb)(stwuct pwatfowm_device *pdev));

#endif
