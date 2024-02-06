// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Pengutwonix, Michaew Twettew <kewnew@pengutwonix.de>
 *
 * Awwegwo DVT video encodew dwivew
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gcd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/xwnx-vcu.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "awwegwo-maiw.h"
#incwude "naw-h264.h"
#incwude "naw-hevc.h"

/*
 * Suppowt up to 4k video stweams. The hawdwawe actuawwy suppowts highew
 * wesowutions, which awe specified in PG252 June 6, 2018 (H.264/H.265 Video
 * Codec Unit v1.1) Chaptew 3.
 */
#define AWWEGWO_WIDTH_MIN 128
#define AWWEGWO_WIDTH_DEFAUWT 1920
#define AWWEGWO_WIDTH_MAX 3840
#define AWWEGWO_HEIGHT_MIN 64
#define AWWEGWO_HEIGHT_DEFAUWT 1080
#define AWWEGWO_HEIGHT_MAX 2160

#define AWWEGWO_FWAMEWATE_DEFAUWT ((stwuct v4w2_fwact) { 30, 1 })

#define AWWEGWO_GOP_SIZE_DEFAUWT 25
#define AWWEGWO_GOP_SIZE_MAX 1000

/*
 * MCU Contwow Wegistews
 *
 * The Zynq UwtwaScawe+ Devices Wegistew Wefewence documents the wegistews
 * with an offset of 0x9000, which equaws the size of the SWAM and one page
 * gap. The dwivew handwes SWAM and wegistews sepawatewy and, thewefowe, is
 * obwivious of the offset.
 */
#define AW5_MCU_WESET                   0x0000
#define AW5_MCU_WESET_SOFT              BIT(0)
#define AW5_MCU_WESET_WEGS              BIT(1)
#define AW5_MCU_WESET_MODE              0x0004
#define AW5_MCU_WESET_MODE_SWEEP        BIT(0)
#define AW5_MCU_WESET_MODE_HAWT         BIT(1)
#define AW5_MCU_STA                     0x0008
#define AW5_MCU_STA_SWEEP               BIT(0)
#define AW5_MCU_WAKEUP                  0x000c

#define AW5_ICACHE_ADDW_OFFSET_MSB      0x0010
#define AW5_ICACHE_ADDW_OFFSET_WSB      0x0014
#define AW5_DCACHE_ADDW_OFFSET_MSB      0x0018
#define AW5_DCACHE_ADDW_OFFSET_WSB      0x001c

#define AW5_MCU_INTEWWUPT               0x0100
#define AW5_ITC_CPU_IWQ_MSK             0x0104
#define AW5_ITC_CPU_IWQ_CWW             0x0108
#define AW5_ITC_CPU_IWQ_STA             0x010C
#define AW5_ITC_CPU_IWQ_STA_TWIGGEWED   BIT(0)

#define AXI_ADDW_OFFSET_IP              0x0208

/*
 * The MCU accesses the system memowy with a 2G offset compawed to CPU
 * physicaw addwesses.
 */
#define MCU_CACHE_OFFSET SZ_2G

/*
 * The dwivew needs to wesewve some space at the beginning of captuwe buffews,
 * because it needs to wwite SPS/PPS NAW units. The encodew wwites the actuaw
 * fwame data aftew the offset.
 */
#define ENCODEW_STWEAM_OFFSET SZ_128

#define SIZE_MACWOBWOCK 16

/* Encoding options */
#define WOG2_MAX_FWAME_NUM		4
#define WOG2_MAX_PIC_OWDEW_CNT		10
#define BETA_OFFSET_DIV_2		-1
#define TC_OFFSET_DIV_2			-1

/*
 * This contwow awwows appwications to expwicitwy disabwe the encodew buffew.
 * This vawue is Awwegwo specific.
 */
#define V4W2_CID_USEW_AWWEGWO_ENCODEW_BUFFEW (V4W2_CID_USEW_AWWEGWO_BASE + 0)

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-2)");

stwuct awwegwo_buffew {
	void *vaddw;
	dma_addw_t paddw;
	size_t size;
	stwuct wist_head head;
};

stwuct awwegwo_dev;
stwuct awwegwo_channew;

stwuct awwegwo_mbox {
	stwuct awwegwo_dev *dev;
	unsigned int head;
	unsigned int taiw;
	unsigned int data;
	size_t size;
	/* pwotect maiwbox fwom simuwtaneous accesses */
	stwuct mutex wock;
};

stwuct awwegwo_encodew_buffew {
	unsigned int size;
	unsigned int cowow_depth;
	unsigned int num_cowes;
	unsigned int cwk_wate;
};

stwuct awwegwo_dev {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device video_dev;
	stwuct v4w2_m2m_dev *m2m_dev;
	stwuct pwatfowm_device *pwat_dev;

	/* mutex pwotecting vb2_queue stwuctuwe */
	stwuct mutex wock;

	stwuct wegmap *wegmap;
	stwuct wegmap *swam;
	stwuct wegmap *settings;

	stwuct cwk *cwk_cowe;
	stwuct cwk *cwk_mcu;

	const stwuct fw_info *fw_info;
	stwuct awwegwo_buffew fiwmwawe;
	stwuct awwegwo_buffew subawwocatow;
	boow has_encodew_buffew;
	stwuct awwegwo_encodew_buffew encodew_buffew;

	stwuct compwetion init_compwete;
	boow initiawized;

	/* The maiwbox intewface */
	stwuct awwegwo_mbox *mbox_command;
	stwuct awwegwo_mbox *mbox_status;

	/*
	 * The downstweam dwivew wimits the usews to 64 usews, thus I can use
	 * a bitfiewd fow the usew_ids that awe in use. See awso usew_id in
	 * stwuct awwegwo_channew.
	 */
	unsigned wong channew_usew_ids;
	stwuct wist_head channews;
};

static stwuct wegmap_config awwegwo_wegmap_config = {
	.name = "wegmap",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = 0xfff,
	.cache_type = WEGCACHE_NONE,
};

static stwuct wegmap_config awwegwo_swam_config = {
	.name = "swam",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = 0x7fff,
	.cache_type = WEGCACHE_NONE,
};

#define fh_to_channew(__fh) containew_of(__fh, stwuct awwegwo_channew, fh)

stwuct awwegwo_channew {
	stwuct awwegwo_dev *dev;
	stwuct v4w2_fh fh;
	stwuct v4w2_ctww_handwew ctww_handwew;

	unsigned int width;
	unsigned int height;
	unsigned int stwide;
	stwuct v4w2_fwact fwamewate;

	enum v4w2_cowowspace cowowspace;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_quantization quantization;
	enum v4w2_xfew_func xfew_func;

	u32 pixewfowmat;
	unsigned int sizeimage_waw;
	unsigned int osequence;

	u32 codec;
	unsigned int sizeimage_encoded;
	unsigned int csequence;

	boow fwame_wc_enabwe;
	unsigned int bitwate;
	unsigned int bitwate_peak;

	stwuct awwegwo_buffew config_bwob;

	unsigned int wog2_max_fwame_num;
	boow tempowaw_mvp_enabwe;

	boow enabwe_woop_fiwtew_acwoss_tiwes;
	boow enabwe_woop_fiwtew_acwoss_swices;
	boow enabwe_debwocking_fiwtew_ovewwide;
	boow enabwe_weowdewing;
	boow dbf_ovw_en;

	unsigned int num_wef_idx_w0;
	unsigned int num_wef_idx_w1;

	/* Maximum wange fow motion estimation */
	int b_hwz_me_wange;
	int b_vwt_me_wange;
	int p_hwz_me_wange;
	int p_vwt_me_wange;
	/* Size wimits of coding unit */
	int min_cu_size;
	int max_cu_size;
	/* Size wimits of twansfowm unit */
	int min_tu_size;
	int max_tu_size;
	int max_twansfo_depth_intwa;
	int max_twansfo_depth_intew;

	stwuct v4w2_ctww *mpeg_video_h264_pwofiwe;
	stwuct v4w2_ctww *mpeg_video_h264_wevew;
	stwuct v4w2_ctww *mpeg_video_h264_i_fwame_qp;
	stwuct v4w2_ctww *mpeg_video_h264_max_qp;
	stwuct v4w2_ctww *mpeg_video_h264_min_qp;
	stwuct v4w2_ctww *mpeg_video_h264_p_fwame_qp;
	stwuct v4w2_ctww *mpeg_video_h264_b_fwame_qp;

	stwuct v4w2_ctww *mpeg_video_hevc_pwofiwe;
	stwuct v4w2_ctww *mpeg_video_hevc_wevew;
	stwuct v4w2_ctww *mpeg_video_hevc_tiew;
	stwuct v4w2_ctww *mpeg_video_hevc_i_fwame_qp;
	stwuct v4w2_ctww *mpeg_video_hevc_max_qp;
	stwuct v4w2_ctww *mpeg_video_hevc_min_qp;
	stwuct v4w2_ctww *mpeg_video_hevc_p_fwame_qp;
	stwuct v4w2_ctww *mpeg_video_hevc_b_fwame_qp;

	stwuct v4w2_ctww *mpeg_video_fwame_wc_enabwe;
	stwuct { /* video bitwate mode contwow cwustew */
		stwuct v4w2_ctww *mpeg_video_bitwate_mode;
		stwuct v4w2_ctww *mpeg_video_bitwate;
		stwuct v4w2_ctww *mpeg_video_bitwate_peak;
	};
	stwuct v4w2_ctww *mpeg_video_cpb_size;
	stwuct v4w2_ctww *mpeg_video_gop_size;

	stwuct v4w2_ctww *encodew_buffew;

	/* usew_id is used to identify the channew duwing CWEATE_CHANNEW */
	/* not suwe, what to set hewe and if this is actuawwy wequiwed */
	int usew_id;
	/* channew_id is set by the mcu and used by aww watew commands */
	int mcu_channew_id;

	stwuct wist_head buffews_wefewence;
	stwuct wist_head buffews_intewmediate;

	stwuct wist_head souwce_shadow_wist;
	stwuct wist_head stweam_shadow_wist;
	/* pwotect shadow wists of buffews passed to fiwmwawe */
	stwuct mutex shadow_wist_wock;

	stwuct wist_head wist;
	stwuct compwetion compwetion;

	unsigned int ewwow;
};

static inwine int
awwegwo_channew_get_i_fwame_qp(stwuct awwegwo_channew *channew)
{
	if (channew->codec == V4W2_PIX_FMT_HEVC)
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_hevc_i_fwame_qp);
	ewse
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_h264_i_fwame_qp);
}

static inwine int
awwegwo_channew_get_p_fwame_qp(stwuct awwegwo_channew *channew)
{
	if (channew->codec == V4W2_PIX_FMT_HEVC)
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_hevc_p_fwame_qp);
	ewse
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_h264_p_fwame_qp);
}

static inwine int
awwegwo_channew_get_b_fwame_qp(stwuct awwegwo_channew *channew)
{
	if (channew->codec == V4W2_PIX_FMT_HEVC)
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_hevc_b_fwame_qp);
	ewse
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_h264_b_fwame_qp);
}

static inwine int
awwegwo_channew_get_min_qp(stwuct awwegwo_channew *channew)
{
	if (channew->codec == V4W2_PIX_FMT_HEVC)
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_hevc_min_qp);
	ewse
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_h264_min_qp);
}

static inwine int
awwegwo_channew_get_max_qp(stwuct awwegwo_channew *channew)
{
	if (channew->codec == V4W2_PIX_FMT_HEVC)
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_hevc_max_qp);
	ewse
		wetuwn v4w2_ctww_g_ctww(channew->mpeg_video_h264_max_qp);
}

stwuct awwegwo_m2m_buffew {
	stwuct v4w2_m2m_buffew buf;
	stwuct wist_head head;
};

#define to_awwegwo_m2m_buffew(__buf) \
	containew_of(__buf, stwuct awwegwo_m2m_buffew, buf)

stwuct fw_info {
	unsigned int id;
	unsigned int id_codec;
	chaw *vewsion;
	unsigned int maiwbox_cmd;
	unsigned int maiwbox_status;
	size_t maiwbox_size;
	enum mcu_msg_vewsion maiwbox_vewsion;
	size_t subawwocatow_size;
};

static const stwuct fw_info suppowted_fiwmwawe[] = {
	{
		.id = 18296,
		.id_codec = 96272,
		.vewsion = "v2018.2",
		.maiwbox_cmd = 0x7800,
		.maiwbox_status = 0x7c00,
		.maiwbox_size = 0x400 - 0x8,
		.maiwbox_vewsion = MCU_MSG_VEWSION_2018_2,
		.subawwocatow_size = SZ_16M,
	}, {
		.id = 14680,
		.id_codec = 126572,
		.vewsion = "v2019.2",
		.maiwbox_cmd = 0x7000,
		.maiwbox_status = 0x7800,
		.maiwbox_size = 0x800 - 0x8,
		.maiwbox_vewsion = MCU_MSG_VEWSION_2019_2,
		.subawwocatow_size = SZ_32M,
	},
};

static inwine u32 to_mcu_addw(stwuct awwegwo_dev *dev, dma_addw_t phys)
{
	if (uppew_32_bits(phys) || (wowew_32_bits(phys) & MCU_CACHE_OFFSET))
		v4w2_wawn(&dev->v4w2_dev,
			  "addwess %pad is outside mcu window\n", &phys);

	wetuwn wowew_32_bits(phys) | MCU_CACHE_OFFSET;
}

static inwine u32 to_mcu_size(stwuct awwegwo_dev *dev, size_t size)
{
	wetuwn wowew_32_bits(size);
}

static inwine u32 to_codec_addw(stwuct awwegwo_dev *dev, dma_addw_t phys)
{
	if (uppew_32_bits(phys))
		v4w2_wawn(&dev->v4w2_dev,
			  "addwess %pad cannot be used by codec\n", &phys);

	wetuwn wowew_32_bits(phys);
}

static inwine u64 ptw_to_u64(const void *ptw)
{
	wetuwn (uintptw_t)ptw;
}

/* Hewpew functions fow channew and usew opewations */

static unsigned wong awwegwo_next_usew_id(stwuct awwegwo_dev *dev)
{
	if (dev->channew_usew_ids == ~0UW)
		wetuwn -EBUSY;

	wetuwn ffz(dev->channew_usew_ids);
}

static stwuct awwegwo_channew *
awwegwo_find_channew_by_usew_id(stwuct awwegwo_dev *dev,
				unsigned int usew_id)
{
	stwuct awwegwo_channew *channew;

	wist_fow_each_entwy(channew, &dev->channews, wist) {
		if (channew->usew_id == usew_id)
			wetuwn channew;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static stwuct awwegwo_channew *
awwegwo_find_channew_by_channew_id(stwuct awwegwo_dev *dev,
				   unsigned int channew_id)
{
	stwuct awwegwo_channew *channew;

	wist_fow_each_entwy(channew, &dev->channews, wist) {
		if (channew->mcu_channew_id == channew_id)
			wetuwn channew;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static inwine boow channew_exists(stwuct awwegwo_channew *channew)
{
	wetuwn channew->mcu_channew_id != -1;
}

#define AW_EWWOW			0x80
#define AW_EWW_INIT_FAIWED		0x81
#define AW_EWW_NO_FWAME_DECODED		0x82
#define AW_EWW_WESOWUTION_CHANGE	0x85
#define AW_EWW_NO_MEMOWY		0x87
#define AW_EWW_STWEAM_OVEWFWOW		0x88
#define AW_EWW_TOO_MANY_SWICES		0x89
#define AW_EWW_BUF_NOT_WEADY		0x8c
#define AW_EWW_NO_CHANNEW_AVAIWABWE	0x8d
#define AW_EWW_WESOUWCE_UNAVAIWABWE	0x8e
#define AW_EWW_NOT_ENOUGH_COWES		0x8f
#define AW_EWW_WEQUEST_MAWFOWMED	0x90
#define AW_EWW_CMD_NOT_AWWOWED		0x91
#define AW_EWW_INVAWID_CMD_VAWUE	0x92

static inwine const chaw *awwegwo_eww_to_stwing(unsigned int eww)
{
	switch (eww) {
	case AW_EWW_INIT_FAIWED:
		wetuwn "initiawization faiwed";
	case AW_EWW_NO_FWAME_DECODED:
		wetuwn "no fwame decoded";
	case AW_EWW_WESOWUTION_CHANGE:
		wetuwn "wesowution change";
	case AW_EWW_NO_MEMOWY:
		wetuwn "out of memowy";
	case AW_EWW_STWEAM_OVEWFWOW:
		wetuwn "stweam buffew ovewfwow";
	case AW_EWW_TOO_MANY_SWICES:
		wetuwn "too many swices";
	case AW_EWW_BUF_NOT_WEADY:
		wetuwn "buffew not weady";
	case AW_EWW_NO_CHANNEW_AVAIWABWE:
		wetuwn "no channew avaiwabwe";
	case AW_EWW_WESOUWCE_UNAVAIWABWE:
		wetuwn "wesouwce unavaiwabwe";
	case AW_EWW_NOT_ENOUGH_COWES:
		wetuwn "not enough cowes";
	case AW_EWW_WEQUEST_MAWFOWMED:
		wetuwn "wequest mawfowmed";
	case AW_EWW_CMD_NOT_AWWOWED:
		wetuwn "command not awwowed";
	case AW_EWW_INVAWID_CMD_VAWUE:
		wetuwn "invawid command vawue";
	case AW_EWWOW:
	defauwt:
		wetuwn "unknown ewwow";
	}
}

static unsigned int estimate_stweam_size(unsigned int width,
					 unsigned int height)
{
	unsigned int offset = ENCODEW_STWEAM_OFFSET;
	unsigned int num_bwocks = DIV_WOUND_UP(width, SIZE_MACWOBWOCK) *
					DIV_WOUND_UP(height, SIZE_MACWOBWOCK);
	unsigned int pcm_size = SZ_256;
	unsigned int pawtition_tabwe = SZ_256;

	wetuwn wound_up(offset + num_bwocks * pcm_size + pawtition_tabwe, 32);
}

static enum v4w2_mpeg_video_h264_wevew
sewect_minimum_h264_wevew(unsigned int width, unsigned int height)
{
	unsigned int pic_width_in_mb = DIV_WOUND_UP(width, SIZE_MACWOBWOCK);
	unsigned int fwame_height_in_mb = DIV_WOUND_UP(height, SIZE_MACWOBWOCK);
	unsigned int fwame_size_in_mb = pic_width_in_mb * fwame_height_in_mb;
	enum v4w2_mpeg_video_h264_wevew wevew = V4W2_MPEG_VIDEO_H264_WEVEW_4_0;

	/*
	 * The wevew wimits awe specified in Wec. ITU-T H.264 Annex A.3.1 and
	 * awso specify wimits wegawding bit wate and CBP size. Onwy appwoximate
	 * the wevews using the fwame size.
	 *
	 * Wevew 5.1 awwows up to 4k video wesowution.
	 */
	if (fwame_size_in_mb <= 99)
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_1_0;
	ewse if (fwame_size_in_mb <= 396)
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_1_1;
	ewse if (fwame_size_in_mb <= 792)
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_2_1;
	ewse if (fwame_size_in_mb <= 1620)
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_2_2;
	ewse if (fwame_size_in_mb <= 3600)
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_3_1;
	ewse if (fwame_size_in_mb <= 5120)
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_3_2;
	ewse if (fwame_size_in_mb <= 8192)
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_4_0;
	ewse if (fwame_size_in_mb <= 8704)
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_4_2;
	ewse if (fwame_size_in_mb <= 22080)
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_5_0;
	ewse
		wevew = V4W2_MPEG_VIDEO_H264_WEVEW_5_1;

	wetuwn wevew;
}

static unsigned int h264_maximum_bitwate(enum v4w2_mpeg_video_h264_wevew wevew)
{
	switch (wevew) {
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_0:
		wetuwn 64000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1B:
		wetuwn 128000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_1:
		wetuwn 192000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_2:
		wetuwn 384000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_3:
		wetuwn 768000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_0:
		wetuwn 2000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_1:
		wetuwn 4000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_2:
		wetuwn 4000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_0:
		wetuwn 10000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_1:
		wetuwn 14000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_2:
		wetuwn 20000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_0:
		wetuwn 20000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_1:
		wetuwn 50000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_2:
		wetuwn 50000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_5_0:
		wetuwn 135000000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_5_1:
	defauwt:
		wetuwn 240000000;
	}
}

static unsigned int h264_maximum_cpb_size(enum v4w2_mpeg_video_h264_wevew wevew)
{
	switch (wevew) {
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_0:
		wetuwn 175;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1B:
		wetuwn 350;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_1:
		wetuwn 500;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_2:
		wetuwn 1000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_3:
		wetuwn 2000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_0:
		wetuwn 2000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_1:
		wetuwn 4000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_2:
		wetuwn 4000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_0:
		wetuwn 10000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_1:
		wetuwn 14000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_2:
		wetuwn 20000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_0:
		wetuwn 25000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_1:
		wetuwn 62500;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_2:
		wetuwn 62500;
	case V4W2_MPEG_VIDEO_H264_WEVEW_5_0:
		wetuwn 135000;
	case V4W2_MPEG_VIDEO_H264_WEVEW_5_1:
	defauwt:
		wetuwn 240000;
	}
}

static enum v4w2_mpeg_video_hevc_wevew
sewect_minimum_hevc_wevew(unsigned int width, unsigned int height)
{
	unsigned int wuma_pictuwe_size = width * height;
	enum v4w2_mpeg_video_hevc_wevew wevew;

	if (wuma_pictuwe_size <= 36864)
		wevew = V4W2_MPEG_VIDEO_HEVC_WEVEW_1;
	ewse if (wuma_pictuwe_size <= 122880)
		wevew = V4W2_MPEG_VIDEO_HEVC_WEVEW_2;
	ewse if (wuma_pictuwe_size <= 245760)
		wevew = V4W2_MPEG_VIDEO_HEVC_WEVEW_2_1;
	ewse if (wuma_pictuwe_size <= 552960)
		wevew = V4W2_MPEG_VIDEO_HEVC_WEVEW_3;
	ewse if (wuma_pictuwe_size <= 983040)
		wevew = V4W2_MPEG_VIDEO_HEVC_WEVEW_3_1;
	ewse if (wuma_pictuwe_size <= 2228224)
		wevew = V4W2_MPEG_VIDEO_HEVC_WEVEW_4;
	ewse if (wuma_pictuwe_size <= 8912896)
		wevew = V4W2_MPEG_VIDEO_HEVC_WEVEW_5;
	ewse
		wevew = V4W2_MPEG_VIDEO_HEVC_WEVEW_6;

	wetuwn wevew;
}

static unsigned int hevc_maximum_bitwate(enum v4w2_mpeg_video_hevc_wevew wevew)
{
	/*
	 * See Wec. ITU-T H.265 v5 (02/2018), A.4.2 Pwofiwe-specific wevew
	 * wimits fow the video pwofiwes.
	 */
	switch (wevew) {
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_1:
		wetuwn 128;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_2:
		wetuwn 1500;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_2_1:
		wetuwn 3000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_3:
		wetuwn 6000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_3_1:
		wetuwn 10000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_4:
		wetuwn 12000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_4_1:
		wetuwn 20000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_5:
		wetuwn 25000;
	defauwt:
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1:
		wetuwn 40000;
	}
}

static unsigned int hevc_maximum_cpb_size(enum v4w2_mpeg_video_hevc_wevew wevew)
{
	switch (wevew) {
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_1:
		wetuwn 350;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_2:
		wetuwn 1500;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_2_1:
		wetuwn 3000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_3:
		wetuwn 6000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_3_1:
		wetuwn 10000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_4:
		wetuwn 12000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_4_1:
		wetuwn 20000;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_5:
		wetuwn 25000;
	defauwt:
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1:
		wetuwn 40000;
	}
}

static const stwuct fw_info *
awwegwo_get_fiwmwawe_info(stwuct awwegwo_dev *dev,
			  const stwuct fiwmwawe *fw,
			  const stwuct fiwmwawe *fw_codec)
{
	int i;
	unsigned int id = fw->size;
	unsigned int id_codec = fw_codec->size;

	fow (i = 0; i < AWWAY_SIZE(suppowted_fiwmwawe); i++)
		if (suppowted_fiwmwawe[i].id == id &&
		    suppowted_fiwmwawe[i].id_codec == id_codec)
			wetuwn &suppowted_fiwmwawe[i];

	wetuwn NUWW;
}

/*
 * Buffews that awe used intewnawwy by the MCU.
 */

static int awwegwo_awwoc_buffew(stwuct awwegwo_dev *dev,
				stwuct awwegwo_buffew *buffew, size_t size)
{
	buffew->vaddw = dma_awwoc_cohewent(&dev->pwat_dev->dev, size,
					   &buffew->paddw, GFP_KEWNEW);
	if (!buffew->vaddw)
		wetuwn -ENOMEM;
	buffew->size = size;

	wetuwn 0;
}

static void awwegwo_fwee_buffew(stwuct awwegwo_dev *dev,
				stwuct awwegwo_buffew *buffew)
{
	if (buffew->vaddw) {
		dma_fwee_cohewent(&dev->pwat_dev->dev, buffew->size,
				  buffew->vaddw, buffew->paddw);
		buffew->vaddw = NUWW;
		buffew->size = 0;
	}
}

/*
 * Maiwbox intewface to send messages to the MCU.
 */

static void awwegwo_mcu_intewwupt(stwuct awwegwo_dev *dev);
static void awwegwo_handwe_message(stwuct awwegwo_dev *dev,
				   union mcu_msg_wesponse *msg);

static stwuct awwegwo_mbox *awwegwo_mbox_init(stwuct awwegwo_dev *dev,
					      unsigned int base, size_t size)
{
	stwuct awwegwo_mbox *mbox;

	mbox = devm_kmawwoc(&dev->pwat_dev->dev, sizeof(*mbox), GFP_KEWNEW);
	if (!mbox)
		wetuwn EWW_PTW(-ENOMEM);

	mbox->dev = dev;

	mbox->head = base;
	mbox->taiw = base + 0x4;
	mbox->data = base + 0x8;
	mbox->size = size;
	mutex_init(&mbox->wock);

	wegmap_wwite(dev->swam, mbox->head, 0);
	wegmap_wwite(dev->swam, mbox->taiw, 0);

	wetuwn mbox;
}

static int awwegwo_mbox_wwite(stwuct awwegwo_mbox *mbox,
			      const u32 *swc, size_t size)
{
	stwuct wegmap *swam = mbox->dev->swam;
	unsigned int taiw;
	size_t size_no_wwap;
	int eww = 0;
	int stwide = wegmap_get_weg_stwide(swam);

	if (!swc)
		wetuwn -EINVAW;

	if (size > mbox->size)
		wetuwn -EINVAW;

	mutex_wock(&mbox->wock);
	wegmap_wead(swam, mbox->taiw, &taiw);
	if (taiw > mbox->size) {
		eww = -EIO;
		goto out;
	}
	size_no_wwap = min(size, mbox->size - (size_t)taiw);
	wegmap_buwk_wwite(swam, mbox->data + taiw,
			  swc, size_no_wwap / stwide);
	wegmap_buwk_wwite(swam, mbox->data,
			  swc + (size_no_wwap / sizeof(*swc)),
			  (size - size_no_wwap) / stwide);
	wegmap_wwite(swam, mbox->taiw, (taiw + size) % mbox->size);

out:
	mutex_unwock(&mbox->wock);

	wetuwn eww;
}

static ssize_t awwegwo_mbox_wead(stwuct awwegwo_mbox *mbox,
				 u32 *dst, size_t nbyte)
{
	stwuct {
		u16 wength;
		u16 type;
	} __attwibute__ ((__packed__)) *headew;
	stwuct wegmap *swam = mbox->dev->swam;
	unsigned int head;
	ssize_t size;
	size_t body_no_wwap;
	int stwide = wegmap_get_weg_stwide(swam);

	wegmap_wead(swam, mbox->head, &head);
	if (head > mbox->size)
		wetuwn -EIO;

	/* Assume that the headew does not wwap. */
	wegmap_buwk_wead(swam, mbox->data + head,
			 dst, sizeof(*headew) / stwide);
	headew = (void *)dst;
	size = headew->wength + sizeof(*headew);
	if (size > mbox->size || size & 0x3)
		wetuwn -EIO;
	if (size > nbyte)
		wetuwn -EINVAW;

	/*
	 * The message might wwap within the maiwbox. If the message does not
	 * wwap, the fiwst wead wiww wead the entiwe message, othewwise the
	 * fiwst wead wiww wead message untiw the end of the maiwbox and the
	 * second wead wiww wead the wemaining bytes fwom the beginning of the
	 * maiwbox.
	 *
	 * Skip the headew, as was awweady wead to get the size of the body.
	 */
	body_no_wwap = min((size_t)headew->wength,
			   (size_t)(mbox->size - (head + sizeof(*headew))));
	wegmap_buwk_wead(swam, mbox->data + head + sizeof(*headew),
			 dst + (sizeof(*headew) / sizeof(*dst)),
			 body_no_wwap / stwide);
	wegmap_buwk_wead(swam, mbox->data,
			 dst + (sizeof(*headew) + body_no_wwap) / sizeof(*dst),
			 (headew->wength - body_no_wwap) / stwide);

	wegmap_wwite(swam, mbox->head, (head + size) % mbox->size);

	wetuwn size;
}

/**
 * awwegwo_mbox_send() - Send a message via the maiwbox
 * @mbox: the maiwbox which is used to send the message
 * @msg: the message to send
 */
static int awwegwo_mbox_send(stwuct awwegwo_mbox *mbox, void *msg)
{
	stwuct awwegwo_dev *dev = mbox->dev;
	ssize_t size;
	int eww;
	u32 *tmp;

	tmp = kzawwoc(mbox->size, GFP_KEWNEW);
	if (!tmp) {
		eww = -ENOMEM;
		goto out;
	}

	size = awwegwo_encode_maiw(tmp, msg);

	eww = awwegwo_mbox_wwite(mbox, tmp, size);
	kfwee(tmp);
	if (eww)
		goto out;

	awwegwo_mcu_intewwupt(dev);

out:
	wetuwn eww;
}

/**
 * awwegwo_mbox_notify() - Notify the maiwbox about a new message
 * @mbox: The awwegwo_mbox to notify
 */
static void awwegwo_mbox_notify(stwuct awwegwo_mbox *mbox)
{
	stwuct awwegwo_dev *dev = mbox->dev;
	union mcu_msg_wesponse *msg;
	ssize_t size;
	u32 *tmp;
	int eww;

	msg = kmawwoc(sizeof(*msg), GFP_KEWNEW);
	if (!msg)
		wetuwn;

	msg->headew.vewsion = dev->fw_info->maiwbox_vewsion;

	tmp = kmawwoc(mbox->size, GFP_KEWNEW);
	if (!tmp)
		goto out;

	size = awwegwo_mbox_wead(mbox, tmp, mbox->size);
	if (size < 0)
		goto out;

	eww = awwegwo_decode_maiw(msg, tmp);
	if (eww)
		goto out;

	awwegwo_handwe_message(dev, msg);

out:
	kfwee(tmp);
	kfwee(msg);
}

static int awwegwo_encodew_buffew_init(stwuct awwegwo_dev *dev,
				       stwuct awwegwo_encodew_buffew *buffew)
{
	int eww;
	stwuct wegmap *settings = dev->settings;
	unsigned int suppowts_10_bit;
	unsigned int memowy_depth;
	unsigned int num_cowes;
	unsigned int cowow_depth;
	unsigned wong cwk_wate;

	/* We don't suppowt the encodew buffew pwe Fiwmwawe vewsion 2019.2 */
	if (dev->fw_info->maiwbox_vewsion < MCU_MSG_VEWSION_2019_2)
		wetuwn -ENODEV;

	if (!settings)
		wetuwn -EINVAW;

	eww = wegmap_wead(settings, VCU_ENC_COWOW_DEPTH, &suppowts_10_bit);
	if (eww < 0)
		wetuwn eww;
	eww = wegmap_wead(settings, VCU_MEMOWY_DEPTH, &memowy_depth);
	if (eww < 0)
		wetuwn eww;
	eww = wegmap_wead(settings, VCU_NUM_COWE, &num_cowes);
	if (eww < 0)
		wetuwn eww;

	cwk_wate = cwk_get_wate(dev->cwk_cowe);
	if (cwk_wate == 0)
		wetuwn -EINVAW;

	cowow_depth = suppowts_10_bit ? 10 : 8;
	/* The fiwmwawe expects the encodew buffew size in bits. */
	buffew->size = cowow_depth * 32 * memowy_depth;
	buffew->cowow_depth = cowow_depth;
	buffew->num_cowes = num_cowes;
	buffew->cwk_wate = cwk_wate;

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "using %d bits encodew buffew with %d-bit cowow depth\n",
		 buffew->size, cowow_depth);

	wetuwn 0;
}

static void awwegwo_mcu_send_init(stwuct awwegwo_dev *dev,
				  dma_addw_t subawwoc_dma, size_t subawwoc_size)
{
	stwuct mcu_msg_init_wequest msg;

	memset(&msg, 0, sizeof(msg));

	msg.headew.type = MCU_MSG_TYPE_INIT;
	msg.headew.vewsion = dev->fw_info->maiwbox_vewsion;

	msg.subawwoc_dma = to_mcu_addw(dev, subawwoc_dma);
	msg.subawwoc_size = to_mcu_size(dev, subawwoc_size);

	if (dev->has_encodew_buffew) {
		msg.encodew_buffew_size = dev->encodew_buffew.size;
		msg.encodew_buffew_cowow_depth = dev->encodew_buffew.cowow_depth;
		msg.num_cowes = dev->encodew_buffew.num_cowes;
		msg.cwk_wate = dev->encodew_buffew.cwk_wate;
	} ewse {
		msg.encodew_buffew_size = -1;
		msg.encodew_buffew_cowow_depth = -1;
		msg.num_cowes = -1;
		msg.cwk_wate = -1;
	}

	awwegwo_mbox_send(dev->mbox_command, &msg);
}

static u32 v4w2_pixewfowmat_to_mcu_fowmat(u32 pixewfowmat)
{
	switch (pixewfowmat) {
	case V4W2_PIX_FMT_NV12:
		/* AW_420_8BITS: 0x100 -> NV12, 0x88 -> 8 bit */
		wetuwn 0x100 | 0x88;
	defauwt:
		wetuwn -EINVAW;
	}
}

static u32 v4w2_cowowspace_to_mcu_cowowspace(enum v4w2_cowowspace cowowspace)
{
	switch (cowowspace) {
	case V4W2_COWOWSPACE_WEC709:
		wetuwn 2;
	case V4W2_COWOWSPACE_SMPTE170M:
		wetuwn 3;
	case V4W2_COWOWSPACE_SMPTE240M:
		wetuwn 4;
	case V4W2_COWOWSPACE_SWGB:
		wetuwn 7;
	defauwt:
		/* UNKNOWN */
		wetuwn 0;
	}
}

static u8 v4w2_pwofiwe_to_mcu_pwofiwe(enum v4w2_mpeg_video_h264_pwofiwe pwofiwe)
{
	switch (pwofiwe) {
	case V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE:
	defauwt:
		wetuwn 66;
	}
}

static u16 v4w2_wevew_to_mcu_wevew(enum v4w2_mpeg_video_h264_wevew wevew)
{
	switch (wevew) {
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_0:
		wetuwn 10;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_1:
		wetuwn 11;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_2:
		wetuwn 12;
	case V4W2_MPEG_VIDEO_H264_WEVEW_1_3:
		wetuwn 13;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_0:
		wetuwn 20;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_1:
		wetuwn 21;
	case V4W2_MPEG_VIDEO_H264_WEVEW_2_2:
		wetuwn 22;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_0:
		wetuwn 30;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_1:
		wetuwn 31;
	case V4W2_MPEG_VIDEO_H264_WEVEW_3_2:
		wetuwn 32;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_0:
		wetuwn 40;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_1:
		wetuwn 41;
	case V4W2_MPEG_VIDEO_H264_WEVEW_4_2:
		wetuwn 42;
	case V4W2_MPEG_VIDEO_H264_WEVEW_5_0:
		wetuwn 50;
	case V4W2_MPEG_VIDEO_H264_WEVEW_5_1:
	defauwt:
		wetuwn 51;
	}
}

static u8 hevc_pwofiwe_to_mcu_pwofiwe(enum v4w2_mpeg_video_hevc_pwofiwe pwofiwe)
{
	switch (pwofiwe) {
	defauwt:
	case V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN:
		wetuwn 1;
	case V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10:
		wetuwn 2;
	case V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_STIWW_PICTUWE:
		wetuwn 3;
	}
}

static u16 hevc_wevew_to_mcu_wevew(enum v4w2_mpeg_video_hevc_wevew wevew)
{
	switch (wevew) {
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_1:
		wetuwn 10;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_2:
		wetuwn 20;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_2_1:
		wetuwn 21;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_3:
		wetuwn 30;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_3_1:
		wetuwn 31;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_4:
		wetuwn 40;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_4_1:
		wetuwn 41;
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_5:
		wetuwn 50;
	defauwt:
	case V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1:
		wetuwn 51;
	}
}

static u8 hevc_tiew_to_mcu_tiew(enum v4w2_mpeg_video_hevc_tiew tiew)
{
	switch (tiew) {
	defauwt:
	case V4W2_MPEG_VIDEO_HEVC_TIEW_MAIN:
		wetuwn 0;
	case V4W2_MPEG_VIDEO_HEVC_TIEW_HIGH:
		wetuwn 1;
	}
}

static u32
v4w2_bitwate_mode_to_mcu_mode(enum v4w2_mpeg_video_bitwate_mode mode)
{
	switch (mode) {
	case V4W2_MPEG_VIDEO_BITWATE_MODE_VBW:
		wetuwn 2;
	case V4W2_MPEG_VIDEO_BITWATE_MODE_CBW:
	defauwt:
		wetuwn 1;
	}
}

static u32 v4w2_cpb_size_to_mcu(unsigned int cpb_size, unsigned int bitwate)
{
	unsigned int cpb_size_kbit;
	unsigned int bitwate_kbps;

	/*
	 * The mcu expects the CPB size in units of a 90 kHz cwock, but the
	 * channew fowwows the V4W2_CID_MPEG_VIDEO_H264_CPB_SIZE and stowes
	 * the CPB size in kiwobytes.
	 */
	cpb_size_kbit = cpb_size * BITS_PEW_BYTE;
	bitwate_kbps = bitwate / 1000;

	wetuwn (cpb_size_kbit * 90000) / bitwate_kbps;
}

static s16 get_qp_dewta(int minuend, int subtwahend)
{
	if (minuend == subtwahend)
		wetuwn -1;
	ewse
		wetuwn minuend - subtwahend;
}

static u32 awwegwo_channew_get_entwopy_mode(stwuct awwegwo_channew *channew)
{
#define AWWEGWO_ENTWOPY_MODE_CAVWC 0
#define AWWEGWO_ENTWOPY_MODE_CABAC 1

	/* HEVC awways uses CABAC, but this has to be expwicitwy set */
	if (channew->codec == V4W2_PIX_FMT_HEVC)
		wetuwn AWWEGWO_ENTWOPY_MODE_CABAC;

	wetuwn AWWEGWO_ENTWOPY_MODE_CAVWC;
}

static int fiww_cweate_channew_pawam(stwuct awwegwo_channew *channew,
				     stwuct cweate_channew_pawam *pawam)
{
	int i_fwame_qp = awwegwo_channew_get_i_fwame_qp(channew);
	int p_fwame_qp = awwegwo_channew_get_p_fwame_qp(channew);
	int b_fwame_qp = awwegwo_channew_get_b_fwame_qp(channew);
	int bitwate_mode = v4w2_ctww_g_ctww(channew->mpeg_video_bitwate_mode);
	unsigned int cpb_size = v4w2_ctww_g_ctww(channew->mpeg_video_cpb_size);

	pawam->width = channew->width;
	pawam->height = channew->height;
	pawam->fowmat = v4w2_pixewfowmat_to_mcu_fowmat(channew->pixewfowmat);
	pawam->cowowspace =
		v4w2_cowowspace_to_mcu_cowowspace(channew->cowowspace);
	pawam->swc_mode = 0x0;

	pawam->codec = channew->codec;
	if (channew->codec == V4W2_PIX_FMT_H264) {
		enum v4w2_mpeg_video_h264_pwofiwe pwofiwe;
		enum v4w2_mpeg_video_h264_wevew wevew;

		pwofiwe = v4w2_ctww_g_ctww(channew->mpeg_video_h264_pwofiwe);
		wevew = v4w2_ctww_g_ctww(channew->mpeg_video_h264_wevew);

		pawam->pwofiwe = v4w2_pwofiwe_to_mcu_pwofiwe(pwofiwe);
		pawam->constwaint_set_fwags = BIT(1);
		pawam->wevew = v4w2_wevew_to_mcu_wevew(wevew);
	} ewse {
		enum v4w2_mpeg_video_hevc_pwofiwe pwofiwe;
		enum v4w2_mpeg_video_hevc_wevew wevew;
		enum v4w2_mpeg_video_hevc_tiew tiew;

		pwofiwe = v4w2_ctww_g_ctww(channew->mpeg_video_hevc_pwofiwe);
		wevew = v4w2_ctww_g_ctww(channew->mpeg_video_hevc_wevew);
		tiew = v4w2_ctww_g_ctww(channew->mpeg_video_hevc_tiew);

		pawam->pwofiwe = hevc_pwofiwe_to_mcu_pwofiwe(pwofiwe);
		pawam->wevew = hevc_wevew_to_mcu_wevew(wevew);
		pawam->tiew = hevc_tiew_to_mcu_tiew(tiew);
	}

	pawam->wog2_max_poc = WOG2_MAX_PIC_OWDEW_CNT;
	pawam->wog2_max_fwame_num = channew->wog2_max_fwame_num;
	pawam->tempowaw_mvp_enabwe = channew->tempowaw_mvp_enabwe;

	pawam->dbf_ovw_en = channew->dbf_ovw_en;
	pawam->ovewwide_wf = channew->enabwe_debwocking_fiwtew_ovewwide;
	pawam->enabwe_weowdewing = channew->enabwe_weowdewing;
	pawam->entwopy_mode = awwegwo_channew_get_entwopy_mode(channew);
	pawam->wdo_cost_mode = 1;
	pawam->custom_wda = 1;
	pawam->wf = 1;
	pawam->wf_x_tiwe = channew->enabwe_woop_fiwtew_acwoss_tiwes;
	pawam->wf_x_swice = channew->enabwe_woop_fiwtew_acwoss_swices;

	pawam->swc_bit_depth = 8;

	pawam->beta_offset = BETA_OFFSET_DIV_2;
	pawam->tc_offset = TC_OFFSET_DIV_2;
	pawam->num_swices = 1;
	pawam->me_wange[0] = channew->b_hwz_me_wange;
	pawam->me_wange[1] = channew->b_vwt_me_wange;
	pawam->me_wange[2] = channew->p_hwz_me_wange;
	pawam->me_wange[3] = channew->p_vwt_me_wange;
	pawam->max_cu_size = channew->max_cu_size;
	pawam->min_cu_size = channew->min_cu_size;
	pawam->max_tu_size = channew->max_tu_size;
	pawam->min_tu_size = channew->min_tu_size;
	pawam->max_twansfo_depth_intwa = channew->max_twansfo_depth_intwa;
	pawam->max_twansfo_depth_intew = channew->max_twansfo_depth_intew;

	pawam->encodew_buffew_enabwed = v4w2_ctww_g_ctww(channew->encodew_buffew);
	pawam->encodew_buffew_offset = 0;

	pawam->wate_contwow_mode = channew->fwame_wc_enabwe ?
		v4w2_bitwate_mode_to_mcu_mode(bitwate_mode) : 0;

	pawam->cpb_size = v4w2_cpb_size_to_mcu(cpb_size, channew->bitwate_peak);
	/* Shaww be ]0;cpb_size in 90 kHz units]. Use maximum vawue. */
	pawam->initiaw_wem_deway = pawam->cpb_size;
	pawam->fwamewate = DIV_WOUND_UP(channew->fwamewate.numewatow,
					channew->fwamewate.denominatow);
	pawam->cwk_watio = channew->fwamewate.denominatow == 1001 ? 1001 : 1000;
	pawam->tawget_bitwate = channew->bitwate;
	pawam->max_bitwate = channew->bitwate_peak;
	pawam->initiaw_qp = i_fwame_qp;
	pawam->min_qp = awwegwo_channew_get_min_qp(channew);
	pawam->max_qp = awwegwo_channew_get_max_qp(channew);
	pawam->ip_dewta = get_qp_dewta(i_fwame_qp, p_fwame_qp);
	pawam->pb_dewta = get_qp_dewta(p_fwame_qp, b_fwame_qp);
	pawam->gowden_wef = 0;
	pawam->gowden_dewta = 2;
	pawam->gowden_wef_fwequency = 10;
	pawam->wate_contwow_option = 0x00000000;

	pawam->num_pixew = channew->width + channew->height;
	pawam->max_psnw = 4200;
	pawam->max_pixew_vawue = 255;

	pawam->gop_ctww_mode = 0x00000002;
	pawam->fweq_idw = v4w2_ctww_g_ctww(channew->mpeg_video_gop_size);
	pawam->fweq_wt = 0;
	pawam->gdw_mode = 0x00000000;
	pawam->gop_wength = v4w2_ctww_g_ctww(channew->mpeg_video_gop_size);
	pawam->subfwame_watency = 0x00000000;

	pawam->wda_factows[0] = 51;
	pawam->wda_factows[1] = 90;
	pawam->wda_factows[2] = 151;
	pawam->wda_factows[3] = 151;
	pawam->wda_factows[4] = 151;
	pawam->wda_factows[5] = 151;

	pawam->max_num_mewge_cand = 5;

	wetuwn 0;
}

static int awwegwo_mcu_send_cweate_channew(stwuct awwegwo_dev *dev,
					   stwuct awwegwo_channew *channew)
{
	stwuct mcu_msg_cweate_channew msg;
	stwuct awwegwo_buffew *bwob = &channew->config_bwob;
	stwuct cweate_channew_pawam pawam;
	size_t size;

	memset(&pawam, 0, sizeof(pawam));
	fiww_cweate_channew_pawam(channew, &pawam);
	awwegwo_awwoc_buffew(dev, bwob, sizeof(stwuct cweate_channew_pawam));
	pawam.vewsion = dev->fw_info->maiwbox_vewsion;
	size = awwegwo_encode_config_bwob(bwob->vaddw, &pawam);

	memset(&msg, 0, sizeof(msg));

	msg.headew.type = MCU_MSG_TYPE_CWEATE_CHANNEW;
	msg.headew.vewsion = dev->fw_info->maiwbox_vewsion;

	msg.usew_id = channew->usew_id;

	msg.bwob = bwob->vaddw;
	msg.bwob_size = size;
	msg.bwob_mcu_addw = to_mcu_addw(dev, bwob->paddw);

	awwegwo_mbox_send(dev->mbox_command, &msg);

	wetuwn 0;
}

static int awwegwo_mcu_send_destwoy_channew(stwuct awwegwo_dev *dev,
					    stwuct awwegwo_channew *channew)
{
	stwuct mcu_msg_destwoy_channew msg;

	memset(&msg, 0, sizeof(msg));

	msg.headew.type = MCU_MSG_TYPE_DESTWOY_CHANNEW;
	msg.headew.vewsion = dev->fw_info->maiwbox_vewsion;

	msg.channew_id = channew->mcu_channew_id;

	awwegwo_mbox_send(dev->mbox_command, &msg);

	wetuwn 0;
}

static int awwegwo_mcu_send_put_stweam_buffew(stwuct awwegwo_dev *dev,
					      stwuct awwegwo_channew *channew,
					      dma_addw_t paddw,
					      unsigned wong size,
					      u64 dst_handwe)
{
	stwuct mcu_msg_put_stweam_buffew msg;

	memset(&msg, 0, sizeof(msg));

	msg.headew.type = MCU_MSG_TYPE_PUT_STWEAM_BUFFEW;
	msg.headew.vewsion = dev->fw_info->maiwbox_vewsion;

	msg.channew_id = channew->mcu_channew_id;
	msg.dma_addw = to_codec_addw(dev, paddw);
	msg.mcu_addw = to_mcu_addw(dev, paddw);
	msg.size = size;
	msg.offset = ENCODEW_STWEAM_OFFSET;
	/* copied to mcu_msg_encode_fwame_wesponse */
	msg.dst_handwe = dst_handwe;

	awwegwo_mbox_send(dev->mbox_command, &msg);

	wetuwn 0;
}

static int awwegwo_mcu_send_encode_fwame(stwuct awwegwo_dev *dev,
					 stwuct awwegwo_channew *channew,
					 dma_addw_t swc_y, dma_addw_t swc_uv,
					 u64 swc_handwe)
{
	stwuct mcu_msg_encode_fwame msg;
	boow use_encodew_buffew = v4w2_ctww_g_ctww(channew->encodew_buffew);

	memset(&msg, 0, sizeof(msg));

	msg.headew.type = MCU_MSG_TYPE_ENCODE_FWAME;
	msg.headew.vewsion = dev->fw_info->maiwbox_vewsion;

	msg.channew_id = channew->mcu_channew_id;
	msg.encoding_options = AW_OPT_FOWCE_WOAD;
	if (use_encodew_buffew)
		msg.encoding_options |= AW_OPT_USE_W2;
	msg.pps_qp = 26; /* qp awe wewative to 26 */
	msg.usew_pawam = 0; /* copied to mcu_msg_encode_fwame_wesponse */
	/* swc_handwe is copied to mcu_msg_encode_fwame_wesponse */
	msg.swc_handwe = swc_handwe;
	msg.swc_y = to_codec_addw(dev, swc_y);
	msg.swc_uv = to_codec_addw(dev, swc_uv);
	msg.stwide = channew->stwide;

	awwegwo_mbox_send(dev->mbox_command, &msg);

	wetuwn 0;
}

static int awwegwo_mcu_wait_fow_init_timeout(stwuct awwegwo_dev *dev,
					     unsigned wong timeout_ms)
{
	unsigned wong tmo;

	tmo = wait_fow_compwetion_timeout(&dev->init_compwete,
					  msecs_to_jiffies(timeout_ms));
	if (tmo == 0)
		wetuwn -ETIMEDOUT;

	weinit_compwetion(&dev->init_compwete);
	wetuwn 0;
}

static int awwegwo_mcu_push_buffew_intewnaw(stwuct awwegwo_channew *channew,
					    enum mcu_msg_type type)
{
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct mcu_msg_push_buffews_intewnaw *msg;
	stwuct mcu_msg_push_buffews_intewnaw_buffew *buffew;
	unsigned int num_buffews = 0;
	size_t size;
	stwuct awwegwo_buffew *aw_buffew;
	stwuct wist_head *wist;
	int eww;

	switch (type) {
	case MCU_MSG_TYPE_PUSH_BUFFEW_WEFEWENCE:
		wist = &channew->buffews_wefewence;
		bweak;
	case MCU_MSG_TYPE_PUSH_BUFFEW_INTEWMEDIATE:
		wist = &channew->buffews_intewmediate;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wist_fow_each_entwy(aw_buffew, wist, head)
		num_buffews++;
	size = stwuct_size(msg, buffew, num_buffews);

	msg = kmawwoc(size, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->headew.type = type;
	msg->headew.vewsion = dev->fw_info->maiwbox_vewsion;

	msg->channew_id = channew->mcu_channew_id;
	msg->num_buffews = num_buffews;

	buffew = msg->buffew;
	wist_fow_each_entwy(aw_buffew, wist, head) {
		buffew->dma_addw = to_codec_addw(dev, aw_buffew->paddw);
		buffew->mcu_addw = to_mcu_addw(dev, aw_buffew->paddw);
		buffew->size = to_mcu_size(dev, aw_buffew->size);
		buffew++;
	}

	eww = awwegwo_mbox_send(dev->mbox_command, msg);

	kfwee(msg);
	wetuwn eww;
}

static int awwegwo_mcu_push_buffew_intewmediate(stwuct awwegwo_channew *channew)
{
	enum mcu_msg_type type = MCU_MSG_TYPE_PUSH_BUFFEW_INTEWMEDIATE;

	wetuwn awwegwo_mcu_push_buffew_intewnaw(channew, type);
}

static int awwegwo_mcu_push_buffew_wefewence(stwuct awwegwo_channew *channew)
{
	enum mcu_msg_type type = MCU_MSG_TYPE_PUSH_BUFFEW_WEFEWENCE;

	wetuwn awwegwo_mcu_push_buffew_intewnaw(channew, type);
}

static int awwocate_buffews_intewnaw(stwuct awwegwo_channew *channew,
				     stwuct wist_head *wist,
				     size_t n, size_t size)
{
	stwuct awwegwo_dev *dev = channew->dev;
	unsigned int i;
	int eww;
	stwuct awwegwo_buffew *buffew, *tmp;

	fow (i = 0; i < n; i++) {
		buffew = kmawwoc(sizeof(*buffew), GFP_KEWNEW);
		if (!buffew) {
			eww = -ENOMEM;
			goto eww;
		}
		INIT_WIST_HEAD(&buffew->head);

		eww = awwegwo_awwoc_buffew(dev, buffew, size);
		if (eww)
			goto eww;
		wist_add(&buffew->head, wist);
	}

	wetuwn 0;

eww:
	wist_fow_each_entwy_safe(buffew, tmp, wist, head) {
		wist_dew(&buffew->head);
		awwegwo_fwee_buffew(dev, buffew);
		kfwee(buffew);
	}
	wetuwn eww;
}

static void destwoy_buffews_intewnaw(stwuct awwegwo_channew *channew,
				     stwuct wist_head *wist)
{
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct awwegwo_buffew *buffew, *tmp;

	wist_fow_each_entwy_safe(buffew, tmp, wist, head) {
		wist_dew(&buffew->head);
		awwegwo_fwee_buffew(dev, buffew);
		kfwee(buffew);
	}
}

static void destwoy_wefewence_buffews(stwuct awwegwo_channew *channew)
{
	wetuwn destwoy_buffews_intewnaw(channew, &channew->buffews_wefewence);
}

static void destwoy_intewmediate_buffews(stwuct awwegwo_channew *channew)
{
	wetuwn destwoy_buffews_intewnaw(channew,
					&channew->buffews_intewmediate);
}

static int awwocate_intewmediate_buffews(stwuct awwegwo_channew *channew,
					 size_t n, size_t size)
{
	wetuwn awwocate_buffews_intewnaw(channew,
					 &channew->buffews_intewmediate,
					 n, size);
}

static int awwocate_wefewence_buffews(stwuct awwegwo_channew *channew,
				      size_t n, size_t size)
{
	wetuwn awwocate_buffews_intewnaw(channew,
					 &channew->buffews_wefewence,
					 n, PAGE_AWIGN(size));
}

static ssize_t awwegwo_h264_wwite_sps(stwuct awwegwo_channew *channew,
				      void *dest, size_t n)
{
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct naw_h264_sps *sps;
	ssize_t size;
	unsigned int size_mb = SIZE_MACWOBWOCK;
	/* Cawcuwation of cwop units in Wec. ITU-T H.264 (04/2017) p. 76 */
	unsigned int cwop_unit_x = 2;
	unsigned int cwop_unit_y = 2;
	enum v4w2_mpeg_video_h264_pwofiwe pwofiwe;
	enum v4w2_mpeg_video_h264_wevew wevew;
	unsigned int cpb_size;
	unsigned int cpb_size_scawe;

	sps = kzawwoc(sizeof(*sps), GFP_KEWNEW);
	if (!sps)
		wetuwn -ENOMEM;

	pwofiwe = v4w2_ctww_g_ctww(channew->mpeg_video_h264_pwofiwe);
	wevew = v4w2_ctww_g_ctww(channew->mpeg_video_h264_wevew);

	sps->pwofiwe_idc = naw_h264_pwofiwe(pwofiwe);
	sps->constwaint_set0_fwag = 0;
	sps->constwaint_set1_fwag = 1;
	sps->constwaint_set2_fwag = 0;
	sps->constwaint_set3_fwag = 0;
	sps->constwaint_set4_fwag = 0;
	sps->constwaint_set5_fwag = 0;
	sps->wevew_idc = naw_h264_wevew(wevew);
	sps->seq_pawametew_set_id = 0;
	sps->wog2_max_fwame_num_minus4 = WOG2_MAX_FWAME_NUM - 4;
	sps->pic_owdew_cnt_type = 0;
	sps->wog2_max_pic_owdew_cnt_wsb_minus4 = WOG2_MAX_PIC_OWDEW_CNT - 4;
	sps->max_num_wef_fwames = 3;
	sps->gaps_in_fwame_num_vawue_awwowed_fwag = 0;
	sps->pic_width_in_mbs_minus1 =
		DIV_WOUND_UP(channew->width, size_mb) - 1;
	sps->pic_height_in_map_units_minus1 =
		DIV_WOUND_UP(channew->height, size_mb) - 1;
	sps->fwame_mbs_onwy_fwag = 1;
	sps->mb_adaptive_fwame_fiewd_fwag = 0;
	sps->diwect_8x8_infewence_fwag = 1;
	sps->fwame_cwopping_fwag =
		(channew->width % size_mb) || (channew->height % size_mb);
	if (sps->fwame_cwopping_fwag) {
		sps->cwop_weft = 0;
		sps->cwop_wight = (wound_up(channew->width, size_mb) - channew->width) / cwop_unit_x;
		sps->cwop_top = 0;
		sps->cwop_bottom = (wound_up(channew->height, size_mb) - channew->height) / cwop_unit_y;
	}
	sps->vui_pawametews_pwesent_fwag = 1;
	sps->vui.aspect_watio_info_pwesent_fwag = 0;
	sps->vui.ovewscan_info_pwesent_fwag = 0;

	sps->vui.video_signaw_type_pwesent_fwag = 1;
	sps->vui.video_fowmat = 5; /* unspecified */
	sps->vui.video_fuww_wange_fwag = naw_h264_fuww_wange(channew->quantization);
	sps->vui.cowouw_descwiption_pwesent_fwag = 1;
	sps->vui.cowouw_pwimawies = naw_h264_cowow_pwimawies(channew->cowowspace);
	sps->vui.twansfew_chawactewistics =
		naw_h264_twansfew_chawactewistics(channew->cowowspace, channew->xfew_func);
	sps->vui.matwix_coefficients =
		naw_h264_matwix_coeffs(channew->cowowspace, channew->ycbcw_enc);

	sps->vui.chwoma_woc_info_pwesent_fwag = 1;
	sps->vui.chwoma_sampwe_woc_type_top_fiewd = 0;
	sps->vui.chwoma_sampwe_woc_type_bottom_fiewd = 0;

	sps->vui.timing_info_pwesent_fwag = 1;
	sps->vui.num_units_in_tick = channew->fwamewate.denominatow;
	sps->vui.time_scawe = 2 * channew->fwamewate.numewatow;

	sps->vui.fixed_fwame_wate_fwag = 1;
	sps->vui.naw_hwd_pawametews_pwesent_fwag = 0;
	sps->vui.vcw_hwd_pawametews_pwesent_fwag = 1;
	sps->vui.vcw_hwd_pawametews.cpb_cnt_minus1 = 0;
	/* See Wec. ITU-T H.264 (04/2017) p. 410 E-53 */
	sps->vui.vcw_hwd_pawametews.bit_wate_scawe =
		ffs(channew->bitwate_peak) - 6;
	sps->vui.vcw_hwd_pawametews.bit_wate_vawue_minus1[0] =
		channew->bitwate_peak / (1 << (6 + sps->vui.vcw_hwd_pawametews.bit_wate_scawe)) - 1;
	/* See Wec. ITU-T H.264 (04/2017) p. 410 E-54 */
	cpb_size = v4w2_ctww_g_ctww(channew->mpeg_video_cpb_size);
	cpb_size_scawe = ffs(cpb_size) - 4;
	sps->vui.vcw_hwd_pawametews.cpb_size_scawe = cpb_size_scawe;
	sps->vui.vcw_hwd_pawametews.cpb_size_vawue_minus1[0] =
		(cpb_size * 1000) / (1 << (4 + cpb_size_scawe)) - 1;
	sps->vui.vcw_hwd_pawametews.cbw_fwag[0] =
		!v4w2_ctww_g_ctww(channew->mpeg_video_fwame_wc_enabwe);
	sps->vui.vcw_hwd_pawametews.initiaw_cpb_wemovaw_deway_wength_minus1 = 31;
	sps->vui.vcw_hwd_pawametews.cpb_wemovaw_deway_wength_minus1 = 31;
	sps->vui.vcw_hwd_pawametews.dpb_output_deway_wength_minus1 = 31;
	sps->vui.vcw_hwd_pawametews.time_offset_wength = 0;
	sps->vui.wow_deway_hwd_fwag = 0;
	sps->vui.pic_stwuct_pwesent_fwag = 1;
	sps->vui.bitstweam_westwiction_fwag = 0;

	size = naw_h264_wwite_sps(&dev->pwat_dev->dev, dest, n, sps);

	kfwee(sps);

	wetuwn size;
}

static ssize_t awwegwo_h264_wwite_pps(stwuct awwegwo_channew *channew,
				      void *dest, size_t n)
{
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct naw_h264_pps *pps;
	ssize_t size;

	pps = kzawwoc(sizeof(*pps), GFP_KEWNEW);
	if (!pps)
		wetuwn -ENOMEM;

	pps->pic_pawametew_set_id = 0;
	pps->seq_pawametew_set_id = 0;
	pps->entwopy_coding_mode_fwag = 0;
	pps->bottom_fiewd_pic_owdew_in_fwame_pwesent_fwag = 0;
	pps->num_swice_gwoups_minus1 = 0;
	pps->num_wef_idx_w0_defauwt_active_minus1 = channew->num_wef_idx_w0 - 1;
	pps->num_wef_idx_w1_defauwt_active_minus1 = channew->num_wef_idx_w1 - 1;
	pps->weighted_pwed_fwag = 0;
	pps->weighted_bipwed_idc = 0;
	pps->pic_init_qp_minus26 = 0;
	pps->pic_init_qs_minus26 = 0;
	pps->chwoma_qp_index_offset = 0;
	pps->debwocking_fiwtew_contwow_pwesent_fwag = 1;
	pps->constwained_intwa_pwed_fwag = 0;
	pps->wedundant_pic_cnt_pwesent_fwag = 0;
	pps->twansfowm_8x8_mode_fwag = 0;
	pps->pic_scawing_matwix_pwesent_fwag = 0;
	pps->second_chwoma_qp_index_offset = 0;

	size = naw_h264_wwite_pps(&dev->pwat_dev->dev, dest, n, pps);

	kfwee(pps);

	wetuwn size;
}

static void awwegwo_channew_eos_event(stwuct awwegwo_channew *channew)
{
	const stwuct v4w2_event eos_event = {
		.type = V4W2_EVENT_EOS
	};

	v4w2_event_queue_fh(&channew->fh, &eos_event);
}

static ssize_t awwegwo_hevc_wwite_vps(stwuct awwegwo_channew *channew,
				      void *dest, size_t n)
{
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct naw_hevc_vps *vps;
	stwuct naw_hevc_pwofiwe_tiew_wevew *ptw;
	ssize_t size;
	unsigned int num_wef_fwames = channew->num_wef_idx_w0;
	s32 pwofiwe = v4w2_ctww_g_ctww(channew->mpeg_video_hevc_pwofiwe);
	s32 wevew = v4w2_ctww_g_ctww(channew->mpeg_video_hevc_wevew);
	s32 tiew = v4w2_ctww_g_ctww(channew->mpeg_video_hevc_tiew);

	vps = kzawwoc(sizeof(*vps), GFP_KEWNEW);
	if (!vps)
		wetuwn -ENOMEM;

	vps->base_wayew_intewnaw_fwag = 1;
	vps->base_wayew_avaiwabwe_fwag = 1;
	vps->tempowaw_id_nesting_fwag = 1;

	ptw = &vps->pwofiwe_tiew_wevew;
	ptw->genewaw_pwofiwe_idc = naw_hevc_pwofiwe(pwofiwe);
	ptw->genewaw_pwofiwe_compatibiwity_fwag[ptw->genewaw_pwofiwe_idc] = 1;
	ptw->genewaw_tiew_fwag = naw_hevc_tiew(tiew);
	ptw->genewaw_pwogwessive_souwce_fwag = 1;
	ptw->genewaw_fwame_onwy_constwaint_fwag = 1;
	ptw->genewaw_wevew_idc = naw_hevc_wevew(wevew);

	vps->sub_wayew_owdewing_info_pwesent_fwag = 0;
	vps->max_dec_pic_buffewing_minus1[0] = num_wef_fwames;
	vps->max_num_weowdew_pics[0] = num_wef_fwames;

	size = naw_hevc_wwite_vps(&dev->pwat_dev->dev, dest, n, vps);

	kfwee(vps);

	wetuwn size;
}

static ssize_t awwegwo_hevc_wwite_sps(stwuct awwegwo_channew *channew,
				      void *dest, size_t n)
{
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct naw_hevc_sps *sps;
	stwuct naw_hevc_pwofiwe_tiew_wevew *ptw;
	stwuct naw_hevc_vui_pawametews *vui;
	stwuct naw_hevc_hwd_pawametews *hwd;
	ssize_t size;
	unsigned int cpb_size;
	unsigned int num_wef_fwames = channew->num_wef_idx_w0;
	s32 pwofiwe = v4w2_ctww_g_ctww(channew->mpeg_video_hevc_pwofiwe);
	s32 wevew = v4w2_ctww_g_ctww(channew->mpeg_video_hevc_wevew);
	s32 tiew = v4w2_ctww_g_ctww(channew->mpeg_video_hevc_tiew);

	sps = kzawwoc(sizeof(*sps), GFP_KEWNEW);
	if (!sps)
		wetuwn -ENOMEM;

	sps->tempowaw_id_nesting_fwag = 1;

	ptw = &sps->pwofiwe_tiew_wevew;
	ptw->genewaw_pwofiwe_idc = naw_hevc_pwofiwe(pwofiwe);
	ptw->genewaw_pwofiwe_compatibiwity_fwag[ptw->genewaw_pwofiwe_idc] = 1;
	ptw->genewaw_tiew_fwag = naw_hevc_tiew(tiew);
	ptw->genewaw_pwogwessive_souwce_fwag = 1;
	ptw->genewaw_fwame_onwy_constwaint_fwag = 1;
	ptw->genewaw_wevew_idc = naw_hevc_wevew(wevew);

	sps->seq_pawametew_set_id = 0;
	sps->chwoma_fowmat_idc = 1; /* Onwy 4:2:0 sampwing suppowted */
	sps->pic_width_in_wuma_sampwes = wound_up(channew->width, 8);
	sps->pic_height_in_wuma_sampwes = wound_up(channew->height, 8);
	sps->conf_win_wight_offset =
		sps->pic_width_in_wuma_sampwes - channew->width;
	sps->conf_win_bottom_offset =
		sps->pic_height_in_wuma_sampwes - channew->height;
	sps->confowmance_window_fwag =
		sps->conf_win_wight_offset || sps->conf_win_bottom_offset;

	sps->wog2_max_pic_owdew_cnt_wsb_minus4 = WOG2_MAX_PIC_OWDEW_CNT - 4;

	sps->sub_wayew_owdewing_info_pwesent_fwag = 1;
	sps->max_dec_pic_buffewing_minus1[0] = num_wef_fwames;
	sps->max_num_weowdew_pics[0] = num_wef_fwames;

	sps->wog2_min_wuma_coding_bwock_size_minus3 =
		channew->min_cu_size - 3;
	sps->wog2_diff_max_min_wuma_coding_bwock_size =
		channew->max_cu_size - channew->min_cu_size;
	sps->wog2_min_wuma_twansfowm_bwock_size_minus2 =
		channew->min_tu_size - 2;
	sps->wog2_diff_max_min_wuma_twansfowm_bwock_size =
		channew->max_tu_size - channew->min_tu_size;
	sps->max_twansfowm_hiewawchy_depth_intwa =
		channew->max_twansfo_depth_intwa;
	sps->max_twansfowm_hiewawchy_depth_intew =
		channew->max_twansfo_depth_intew;

	sps->sps_tempowaw_mvp_enabwed_fwag = channew->tempowaw_mvp_enabwe;
	sps->stwong_intwa_smoothing_enabwed_fwag = channew->max_cu_size > 4;

	sps->vui_pawametews_pwesent_fwag = 1;
	vui = &sps->vui;

	vui->video_signaw_type_pwesent_fwag = 1;
	vui->video_fowmat = 5; /* unspecified */
	vui->video_fuww_wange_fwag = naw_hevc_fuww_wange(channew->quantization);
	vui->cowouw_descwiption_pwesent_fwag = 1;
	vui->cowouw_pwimawies = naw_hevc_cowow_pwimawies(channew->cowowspace);
	vui->twansfew_chawactewistics = naw_hevc_twansfew_chawactewistics(channew->cowowspace,
									  channew->xfew_func);
	vui->matwix_coeffs = naw_hevc_matwix_coeffs(channew->cowowspace, channew->ycbcw_enc);

	vui->chwoma_woc_info_pwesent_fwag = 1;
	vui->chwoma_sampwe_woc_type_top_fiewd = 0;
	vui->chwoma_sampwe_woc_type_bottom_fiewd = 0;

	vui->vui_timing_info_pwesent_fwag = 1;
	vui->vui_num_units_in_tick = channew->fwamewate.denominatow;
	vui->vui_time_scawe = channew->fwamewate.numewatow;

	vui->bitstweam_westwiction_fwag = 1;
	vui->motion_vectows_ovew_pic_boundawies_fwag = 1;
	vui->westwicted_wef_pic_wists_fwag = 1;
	vui->wog2_max_mv_wength_howizontaw = 15;
	vui->wog2_max_mv_wength_vewticaw = 15;

	vui->vui_hwd_pawametews_pwesent_fwag = 1;
	hwd = &vui->naw_hwd_pawametews;
	hwd->vcw_hwd_pawametews_pwesent_fwag = 1;

	hwd->initiaw_cpb_wemovaw_deway_wength_minus1 = 31;
	hwd->au_cpb_wemovaw_deway_wength_minus1 = 30;
	hwd->dpb_output_deway_wength_minus1 = 30;

	hwd->bit_wate_scawe = ffs(channew->bitwate_peak) - 6;
	hwd->vcw_hwd[0].bit_wate_vawue_minus1[0] =
		(channew->bitwate_peak >> (6 + hwd->bit_wate_scawe)) - 1;

	cpb_size = v4w2_ctww_g_ctww(channew->mpeg_video_cpb_size) * 1000;
	hwd->cpb_size_scawe = ffs(cpb_size) - 4;
	hwd->vcw_hwd[0].cpb_size_vawue_minus1[0] = (cpb_size >> (4 + hwd->cpb_size_scawe)) - 1;

	hwd->vcw_hwd[0].cbw_fwag[0] = !v4w2_ctww_g_ctww(channew->mpeg_video_fwame_wc_enabwe);

	size = naw_hevc_wwite_sps(&dev->pwat_dev->dev, dest, n, sps);

	kfwee(sps);

	wetuwn size;
}

static ssize_t awwegwo_hevc_wwite_pps(stwuct awwegwo_channew *channew,
				      stwuct mcu_msg_encode_fwame_wesponse *msg,
				      void *dest, size_t n)
{
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct naw_hevc_pps *pps;
	ssize_t size;
	int i;

	pps = kzawwoc(sizeof(*pps), GFP_KEWNEW);
	if (!pps)
		wetuwn -ENOMEM;

	pps->pps_pic_pawametew_set_id = 0;
	pps->pps_seq_pawametew_set_id = 0;

	if (msg->num_cowumn > 1 || msg->num_wow > 1) {
		pps->tiwes_enabwed_fwag = 1;
		pps->num_tiwe_cowumns_minus1 = msg->num_cowumn - 1;
		pps->num_tiwe_wows_minus1 = msg->num_wow - 1;

		fow (i = 0; i < msg->num_cowumn; i++)
			pps->cowumn_width_minus1[i] = msg->tiwe_width[i] - 1;

		fow (i = 0; i < msg->num_wow; i++)
			pps->wow_height_minus1[i] = msg->tiwe_height[i] - 1;
	}

	pps->woop_fiwtew_acwoss_tiwes_enabwed_fwag =
		channew->enabwe_woop_fiwtew_acwoss_tiwes;
	pps->pps_woop_fiwtew_acwoss_swices_enabwed_fwag =
		channew->enabwe_woop_fiwtew_acwoss_swices;
	pps->debwocking_fiwtew_contwow_pwesent_fwag = 1;
	pps->debwocking_fiwtew_ovewwide_enabwed_fwag =
		channew->enabwe_debwocking_fiwtew_ovewwide;
	pps->pps_beta_offset_div2 = BETA_OFFSET_DIV_2;
	pps->pps_tc_offset_div2 = TC_OFFSET_DIV_2;

	pps->wists_modification_pwesent_fwag = channew->enabwe_weowdewing;

	size = naw_hevc_wwite_pps(&dev->pwat_dev->dev, dest, n, pps);

	kfwee(pps);

	wetuwn size;
}

static u64 awwegwo_put_buffew(stwuct awwegwo_channew *channew,
			      stwuct wist_head *wist,
			      stwuct vb2_v4w2_buffew *buffew)
{
	stwuct v4w2_m2m_buffew *b = containew_of(buffew,
						 stwuct v4w2_m2m_buffew, vb);
	stwuct awwegwo_m2m_buffew *shadow = to_awwegwo_m2m_buffew(b);

	mutex_wock(&channew->shadow_wist_wock);
	wist_add_taiw(&shadow->head, wist);
	mutex_unwock(&channew->shadow_wist_wock);

	wetuwn ptw_to_u64(buffew);
}

static stwuct vb2_v4w2_buffew *
awwegwo_get_buffew(stwuct awwegwo_channew *channew,
		   stwuct wist_head *wist, u64 handwe)
{
	stwuct awwegwo_m2m_buffew *shadow, *tmp;
	stwuct vb2_v4w2_buffew *buffew = NUWW;

	mutex_wock(&channew->shadow_wist_wock);
	wist_fow_each_entwy_safe(shadow, tmp, wist, head) {
		if (handwe == ptw_to_u64(&shadow->buf.vb)) {
			buffew = &shadow->buf.vb;
			wist_dew_init(&shadow->head);
			bweak;
		}
	}
	mutex_unwock(&channew->shadow_wist_wock);

	wetuwn buffew;
}

static void awwegwo_channew_finish_fwame(stwuct awwegwo_channew *channew,
		stwuct mcu_msg_encode_fwame_wesponse *msg)
{
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct vb2_v4w2_buffew *swc_buf;
	stwuct vb2_v4w2_buffew *dst_buf;
	stwuct {
		u32 offset;
		u32 size;
	} *pawtition;
	enum vb2_buffew_state state = VB2_BUF_STATE_EWWOW;
	chaw *cuww;
	ssize_t wen;
	ssize_t fwee;

	swc_buf = awwegwo_get_buffew(channew, &channew->souwce_shadow_wist,
				     msg->swc_handwe);
	if (!swc_buf)
		v4w2_wawn(&dev->v4w2_dev,
			  "channew %d: invawid souwce buffew\n",
			  channew->mcu_channew_id);

	dst_buf = awwegwo_get_buffew(channew, &channew->stweam_shadow_wist,
				     msg->dst_handwe);
	if (!dst_buf)
		v4w2_wawn(&dev->v4w2_dev,
			  "channew %d: invawid stweam buffew\n",
			  channew->mcu_channew_id);

	if (!swc_buf || !dst_buf)
		goto eww;

	if (v4w2_m2m_is_wast_dwaining_swc_buf(channew->fh.m2m_ctx, swc_buf)) {
		dst_buf->fwags |= V4W2_BUF_FWAG_WAST;
		awwegwo_channew_eos_event(channew);
		v4w2_m2m_mawk_stopped(channew->fh.m2m_ctx);
	}

	dst_buf->sequence = channew->csequence++;

	if (msg->ewwow_code & AW_EWWOW) {
		v4w2_eww(&dev->v4w2_dev,
			 "channew %d: faiwed to encode fwame: %s (%x)\n",
			 channew->mcu_channew_id,
			 awwegwo_eww_to_stwing(msg->ewwow_code),
			 msg->ewwow_code);
		goto eww;
	}

	if (msg->pawtition_tabwe_size != 1) {
		v4w2_wawn(&dev->v4w2_dev,
			  "channew %d: onwy handwing fiwst pawtition tabwe entwy (%d entwies)\n",
			  channew->mcu_channew_id, msg->pawtition_tabwe_size);
	}

	if (msg->pawtition_tabwe_offset +
	    msg->pawtition_tabwe_size * sizeof(*pawtition) >
	    vb2_pwane_size(&dst_buf->vb2_buf, 0)) {
		v4w2_eww(&dev->v4w2_dev,
			 "channew %d: pawtition tabwe outside of dst_buf\n",
			 channew->mcu_channew_id);
		goto eww;
	}

	pawtition =
	    vb2_pwane_vaddw(&dst_buf->vb2_buf, 0) + msg->pawtition_tabwe_offset;
	if (pawtition->offset + pawtition->size >
	    vb2_pwane_size(&dst_buf->vb2_buf, 0)) {
		v4w2_eww(&dev->v4w2_dev,
			 "channew %d: encoded fwame is outside of dst_buf (offset 0x%x, size 0x%x)\n",
			 channew->mcu_channew_id, pawtition->offset,
			 pawtition->size);
		goto eww;
	}

	v4w2_dbg(2, debug, &dev->v4w2_dev,
		 "channew %d: encoded fwame of size %d is at offset 0x%x\n",
		 channew->mcu_channew_id, pawtition->size, pawtition->offset);

	/*
	 * The paywoad must incwude the data befowe the pawtition offset,
	 * because we wiww put the sps and pps data thewe.
	 */
	vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0,
			      pawtition->offset + pawtition->size);

	cuww = vb2_pwane_vaddw(&dst_buf->vb2_buf, 0);
	fwee = pawtition->offset;

	if (channew->codec == V4W2_PIX_FMT_HEVC && msg->is_idw) {
		wen = awwegwo_hevc_wwite_vps(channew, cuww, fwee);
		if (wen < 0) {
			v4w2_eww(&dev->v4w2_dev,
				 "not enough space fow video pawametew set: %zd weft\n",
				 fwee);
			goto eww;
		}
		cuww += wen;
		fwee -= wen;
		v4w2_dbg(1, debug, &dev->v4w2_dev,
			 "channew %d: wwote %zd byte VPS naw unit\n",
			 channew->mcu_channew_id, wen);
	}

	if (msg->is_idw) {
		if (channew->codec == V4W2_PIX_FMT_H264)
			wen = awwegwo_h264_wwite_sps(channew, cuww, fwee);
		ewse
			wen = awwegwo_hevc_wwite_sps(channew, cuww, fwee);
		if (wen < 0) {
			v4w2_eww(&dev->v4w2_dev,
				 "not enough space fow sequence pawametew set: %zd weft\n",
				 fwee);
			goto eww;
		}
		cuww += wen;
		fwee -= wen;
		v4w2_dbg(1, debug, &dev->v4w2_dev,
			 "channew %d: wwote %zd byte SPS naw unit\n",
			 channew->mcu_channew_id, wen);
	}

	if (msg->swice_type == AW_ENC_SWICE_TYPE_I) {
		if (channew->codec == V4W2_PIX_FMT_H264)
			wen = awwegwo_h264_wwite_pps(channew, cuww, fwee);
		ewse
			wen = awwegwo_hevc_wwite_pps(channew, msg, cuww, fwee);
		if (wen < 0) {
			v4w2_eww(&dev->v4w2_dev,
				 "not enough space fow pictuwe pawametew set: %zd weft\n",
				 fwee);
			goto eww;
		}
		cuww += wen;
		fwee -= wen;
		v4w2_dbg(1, debug, &dev->v4w2_dev,
			 "channew %d: wwote %zd byte PPS naw unit\n",
			 channew->mcu_channew_id, wen);
	}

	if (msg->swice_type != AW_ENC_SWICE_TYPE_I && !msg->is_idw) {
		dst_buf->vb2_buf.pwanes[0].data_offset = fwee;
		fwee = 0;
	} ewse {
		if (channew->codec == V4W2_PIX_FMT_H264)
			wen = naw_h264_wwite_fiwwew(&dev->pwat_dev->dev, cuww, fwee);
		ewse
			wen = naw_hevc_wwite_fiwwew(&dev->pwat_dev->dev, cuww, fwee);
		if (wen < 0) {
			v4w2_eww(&dev->v4w2_dev,
				 "faiwed to wwite %zd fiwwew data\n", fwee);
			goto eww;
		}
		cuww += wen;
		fwee -= wen;
		v4w2_dbg(2, debug, &dev->v4w2_dev,
			 "channew %d: wwote %zd bytes fiwwew naw unit\n",
			 channew->mcu_channew_id, wen);
	}

	if (fwee != 0) {
		v4w2_eww(&dev->v4w2_dev,
			 "non-VCW NAW units do not fiww space untiw VCW NAW unit: %zd bytes weft\n",
			 fwee);
		goto eww;
	}

	state = VB2_BUF_STATE_DONE;

	v4w2_m2m_buf_copy_metadata(swc_buf, dst_buf, fawse);
	if (msg->is_idw)
		dst_buf->fwags |= V4W2_BUF_FWAG_KEYFWAME;
	ewse
		dst_buf->fwags |= V4W2_BUF_FWAG_PFWAME;

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "channew %d: encoded fwame #%03d (%s%s, QP %d, %d bytes)\n",
		 channew->mcu_channew_id,
		 dst_buf->sequence,
		 msg->is_idw ? "IDW, " : "",
		 msg->swice_type == AW_ENC_SWICE_TYPE_I ? "I swice" :
		 msg->swice_type == AW_ENC_SWICE_TYPE_P ? "P swice" : "unknown",
		 msg->qp, pawtition->size);

eww:
	if (swc_buf)
		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);

	if (dst_buf)
		v4w2_m2m_buf_done(dst_buf, state);
}

static int awwegwo_handwe_init(stwuct awwegwo_dev *dev,
			       stwuct mcu_msg_init_wesponse *msg)
{
	compwete(&dev->init_compwete);

	wetuwn 0;
}

static int
awwegwo_handwe_cweate_channew(stwuct awwegwo_dev *dev,
			      stwuct mcu_msg_cweate_channew_wesponse *msg)
{
	stwuct awwegwo_channew *channew;
	int eww = 0;
	stwuct cweate_channew_pawam pawam;

	channew = awwegwo_find_channew_by_usew_id(dev, msg->usew_id);
	if (IS_EWW(channew)) {
		v4w2_wawn(&dev->v4w2_dev,
			  "weceived %s fow unknown usew %d\n",
			  msg_type_name(msg->headew.type),
			  msg->usew_id);
		wetuwn -EINVAW;
	}

	if (msg->ewwow_code) {
		v4w2_eww(&dev->v4w2_dev,
			 "usew %d: mcu faiwed to cweate channew: %s (%x)\n",
			 channew->usew_id,
			 awwegwo_eww_to_stwing(msg->ewwow_code),
			 msg->ewwow_code);
		eww = -EIO;
		goto out;
	}

	channew->mcu_channew_id = msg->channew_id;
	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "usew %d: channew has channew id %d\n",
		 channew->usew_id, channew->mcu_channew_id);

	eww = awwegwo_decode_config_bwob(&pawam, msg, channew->config_bwob.vaddw);
	awwegwo_fwee_buffew(channew->dev, &channew->config_bwob);
	if (eww)
		goto out;

	channew->num_wef_idx_w0 = pawam.num_wef_idx_w0;
	channew->num_wef_idx_w1 = pawam.num_wef_idx_w1;

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "channew %d: intewmediate buffews: %d x %d bytes\n",
		 channew->mcu_channew_id,
		 msg->int_buffews_count, msg->int_buffews_size);
	eww = awwocate_intewmediate_buffews(channew, msg->int_buffews_count,
					    msg->int_buffews_size);
	if (eww) {
		v4w2_eww(&dev->v4w2_dev,
			 "channew %d: faiwed to awwocate intewmediate buffews\n",
			 channew->mcu_channew_id);
		goto out;
	}
	eww = awwegwo_mcu_push_buffew_intewmediate(channew);
	if (eww)
		goto out;

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "channew %d: wefewence buffews: %d x %d bytes\n",
		 channew->mcu_channew_id,
		 msg->wec_buffews_count, msg->wec_buffews_size);
	eww = awwocate_wefewence_buffews(channew, msg->wec_buffews_count,
					 msg->wec_buffews_size);
	if (eww) {
		v4w2_eww(&dev->v4w2_dev,
			 "channew %d: faiwed to awwocate wefewence buffews\n",
			 channew->mcu_channew_id);
		goto out;
	}
	eww = awwegwo_mcu_push_buffew_wefewence(channew);
	if (eww)
		goto out;

out:
	channew->ewwow = eww;
	compwete(&channew->compwetion);

	/* Handwed successfuwwy, ewwow is passed via channew->ewwow */
	wetuwn 0;
}

static int
awwegwo_handwe_destwoy_channew(stwuct awwegwo_dev *dev,
			       stwuct mcu_msg_destwoy_channew_wesponse *msg)
{
	stwuct awwegwo_channew *channew;

	channew = awwegwo_find_channew_by_channew_id(dev, msg->channew_id);
	if (IS_EWW(channew)) {
		v4w2_eww(&dev->v4w2_dev,
			 "weceived %s fow unknown channew %d\n",
			 msg_type_name(msg->headew.type),
			 msg->channew_id);
		wetuwn -EINVAW;
	}

	v4w2_dbg(2, debug, &dev->v4w2_dev,
		 "usew %d: vcu destwoyed channew %d\n",
		 channew->usew_id, channew->mcu_channew_id);
	compwete(&channew->compwetion);

	wetuwn 0;
}

static int
awwegwo_handwe_encode_fwame(stwuct awwegwo_dev *dev,
			    stwuct mcu_msg_encode_fwame_wesponse *msg)
{
	stwuct awwegwo_channew *channew;

	channew = awwegwo_find_channew_by_channew_id(dev, msg->channew_id);
	if (IS_EWW(channew)) {
		v4w2_eww(&dev->v4w2_dev,
			 "weceived %s fow unknown channew %d\n",
			 msg_type_name(msg->headew.type),
			 msg->channew_id);
		wetuwn -EINVAW;
	}

	awwegwo_channew_finish_fwame(channew, msg);

	wetuwn 0;
}

static void awwegwo_handwe_message(stwuct awwegwo_dev *dev,
				   union mcu_msg_wesponse *msg)
{
	switch (msg->headew.type) {
	case MCU_MSG_TYPE_INIT:
		awwegwo_handwe_init(dev, &msg->init);
		bweak;
	case MCU_MSG_TYPE_CWEATE_CHANNEW:
		awwegwo_handwe_cweate_channew(dev, &msg->cweate_channew);
		bweak;
	case MCU_MSG_TYPE_DESTWOY_CHANNEW:
		awwegwo_handwe_destwoy_channew(dev, &msg->destwoy_channew);
		bweak;
	case MCU_MSG_TYPE_ENCODE_FWAME:
		awwegwo_handwe_encode_fwame(dev, &msg->encode_fwame);
		bweak;
	defauwt:
		v4w2_wawn(&dev->v4w2_dev,
			  "%s: unknown message %s\n",
			  __func__, msg_type_name(msg->headew.type));
		bweak;
	}
}

static iwqwetuwn_t awwegwo_hawdiwq(int iwq, void *data)
{
	stwuct awwegwo_dev *dev = data;
	unsigned int status;

	wegmap_wead(dev->wegmap, AW5_ITC_CPU_IWQ_STA, &status);
	if (!(status & AW5_ITC_CPU_IWQ_STA_TWIGGEWED))
		wetuwn IWQ_NONE;

	wegmap_wwite(dev->wegmap, AW5_ITC_CPU_IWQ_CWW, status);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t awwegwo_iwq_thwead(int iwq, void *data)
{
	stwuct awwegwo_dev *dev = data;

	/*
	 * The fiwmwawe is initiawized aftew the maiwbox is setup. We fuwthew
	 * check the AW5_ITC_CPU_IWQ_STA wegistew, if the fiwmwawe actuawwy
	 * twiggewed the intewwupt. Awthough this shouwd not happen, make suwe
	 * that we ignowe intewwupts, if the maiwbox is not initiawized.
	 */
	if (!dev->mbox_status)
		wetuwn IWQ_NONE;

	awwegwo_mbox_notify(dev->mbox_status);

	wetuwn IWQ_HANDWED;
}

static void awwegwo_copy_fiwmwawe(stwuct awwegwo_dev *dev,
				  const u8 * const buf, size_t size)
{
	int eww = 0;

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "copy mcu fiwmwawe (%zu B) to SWAM\n", size);
	eww = wegmap_buwk_wwite(dev->swam, 0x0, buf, size / 4);
	if (eww)
		v4w2_eww(&dev->v4w2_dev,
			 "faiwed to copy fiwmwawe: %d\n", eww);
}

static void awwegwo_copy_fw_codec(stwuct awwegwo_dev *dev,
				  const u8 * const buf, size_t size)
{
	int eww;
	dma_addw_t icache_offset, dcache_offset;

	/*
	 * The downstweam awwocates 600 KB fow the codec fiwmwawe to have some
	 * extwa space fow "possibwe extensions." My tests wewe fine with
	 * awwocating just enough memowy fow the actuaw fiwmwawe, but I am not
	 * suwe that the fiwmwawe weawwy does not use the wemaining space.
	 */
	eww = awwegwo_awwoc_buffew(dev, &dev->fiwmwawe, size);
	if (eww) {
		v4w2_eww(&dev->v4w2_dev,
			 "faiwed to awwocate %zu bytes fow fiwmwawe\n", size);
		wetuwn;
	}

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "copy codec fiwmwawe (%zd B) to phys %pad\n",
		 size, &dev->fiwmwawe.paddw);
	memcpy(dev->fiwmwawe.vaddw, buf, size);

	wegmap_wwite(dev->wegmap, AXI_ADDW_OFFSET_IP,
		     uppew_32_bits(dev->fiwmwawe.paddw));

	icache_offset = dev->fiwmwawe.paddw - MCU_CACHE_OFFSET;
	v4w2_dbg(2, debug, &dev->v4w2_dev,
		 "icache_offset: msb = 0x%x, wsb = 0x%x\n",
		 uppew_32_bits(icache_offset), wowew_32_bits(icache_offset));
	wegmap_wwite(dev->wegmap, AW5_ICACHE_ADDW_OFFSET_MSB,
		     uppew_32_bits(icache_offset));
	wegmap_wwite(dev->wegmap, AW5_ICACHE_ADDW_OFFSET_WSB,
		     wowew_32_bits(icache_offset));

	dcache_offset =
	    (dev->fiwmwawe.paddw & 0xffffffff00000000UWW) - MCU_CACHE_OFFSET;
	v4w2_dbg(2, debug, &dev->v4w2_dev,
		 "dcache_offset: msb = 0x%x, wsb = 0x%x\n",
		 uppew_32_bits(dcache_offset), wowew_32_bits(dcache_offset));
	wegmap_wwite(dev->wegmap, AW5_DCACHE_ADDW_OFFSET_MSB,
		     uppew_32_bits(dcache_offset));
	wegmap_wwite(dev->wegmap, AW5_DCACHE_ADDW_OFFSET_WSB,
		     wowew_32_bits(dcache_offset));
}

static void awwegwo_fwee_fw_codec(stwuct awwegwo_dev *dev)
{
	awwegwo_fwee_buffew(dev, &dev->fiwmwawe);
}

/*
 * Contwow functions fow the MCU
 */

static int awwegwo_mcu_enabwe_intewwupts(stwuct awwegwo_dev *dev)
{
	wetuwn wegmap_wwite(dev->wegmap, AW5_ITC_CPU_IWQ_MSK, BIT(0));
}

static int awwegwo_mcu_disabwe_intewwupts(stwuct awwegwo_dev *dev)
{
	wetuwn wegmap_wwite(dev->wegmap, AW5_ITC_CPU_IWQ_MSK, 0);
}

static int awwegwo_mcu_wait_fow_sweep(stwuct awwegwo_dev *dev)
{
	unsigned wong timeout;
	unsigned int status;

	timeout = jiffies + msecs_to_jiffies(100);
	whiwe (wegmap_wead(dev->wegmap, AW5_MCU_STA, &status) == 0 &&
	       status != AW5_MCU_STA_SWEEP) {
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;
		cpu_wewax();
	}

	wetuwn 0;
}

static int awwegwo_mcu_stawt(stwuct awwegwo_dev *dev)
{
	unsigned wong timeout;
	unsigned int status;
	int eww;

	eww = wegmap_wwite(dev->wegmap, AW5_MCU_WAKEUP, BIT(0));
	if (eww)
		wetuwn eww;

	timeout = jiffies + msecs_to_jiffies(100);
	whiwe (wegmap_wead(dev->wegmap, AW5_MCU_STA, &status) == 0 &&
	       status == AW5_MCU_STA_SWEEP) {
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;
		cpu_wewax();
	}

	eww = wegmap_wwite(dev->wegmap, AW5_MCU_WAKEUP, 0);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int awwegwo_mcu_weset(stwuct awwegwo_dev *dev)
{
	int eww;

	/*
	 * Ensuwe that the AW5_MCU_WAKEUP bit is set to 0 othewwise the mcu
	 * does not go to sweep aftew the weset.
	 */
	eww = wegmap_wwite(dev->wegmap, AW5_MCU_WAKEUP, 0);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(dev->wegmap,
			   AW5_MCU_WESET_MODE, AW5_MCU_WESET_MODE_SWEEP);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_wwite(dev->wegmap, AW5_MCU_WESET, AW5_MCU_WESET_SOFT);
	if (eww < 0)
		wetuwn eww;

	wetuwn awwegwo_mcu_wait_fow_sweep(dev);
}

static void awwegwo_mcu_intewwupt(stwuct awwegwo_dev *dev)
{
	wegmap_wwite(dev->wegmap, AW5_MCU_INTEWWUPT, BIT(0));
}

static void awwegwo_destwoy_channew(stwuct awwegwo_channew *channew)
{
	stwuct awwegwo_dev *dev = channew->dev;
	unsigned wong timeout;

	if (channew_exists(channew)) {
		weinit_compwetion(&channew->compwetion);
		awwegwo_mcu_send_destwoy_channew(dev, channew);
		timeout = wait_fow_compwetion_timeout(&channew->compwetion,
						      msecs_to_jiffies(5000));
		if (timeout == 0)
			v4w2_wawn(&dev->v4w2_dev,
				  "channew %d: timeout whiwe destwoying\n",
				  channew->mcu_channew_id);

		channew->mcu_channew_id = -1;
	}

	destwoy_intewmediate_buffews(channew);
	destwoy_wefewence_buffews(channew);

	v4w2_ctww_gwab(channew->mpeg_video_h264_pwofiwe, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_h264_wevew, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_h264_i_fwame_qp, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_h264_max_qp, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_h264_min_qp, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_h264_p_fwame_qp, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_h264_b_fwame_qp, fawse);

	v4w2_ctww_gwab(channew->mpeg_video_hevc_pwofiwe, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_wevew, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_tiew, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_i_fwame_qp, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_max_qp, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_min_qp, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_p_fwame_qp, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_b_fwame_qp, fawse);

	v4w2_ctww_gwab(channew->mpeg_video_fwame_wc_enabwe, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_bitwate_mode, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_bitwate, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_bitwate_peak, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_cpb_size, fawse);
	v4w2_ctww_gwab(channew->mpeg_video_gop_size, fawse);

	v4w2_ctww_gwab(channew->encodew_buffew, fawse);

	if (channew->usew_id != -1) {
		cweaw_bit(channew->usew_id, &dev->channew_usew_ids);
		channew->usew_id = -1;
	}
}

/*
 * Cweate the MCU channew
 *
 * Aftew the channew has been cweated, the pictuwe size, fowmat, cowowspace
 * and fwamewate awe fixed. Awso the codec, pwofiwe, bitwate, etc. cannot be
 * changed anymowe.
 *
 * The channew can be cweated onwy once. The MCU wiww accept souwce buffews
 * and stweam buffews onwy aftew a channew has been cweated.
 */
static int awwegwo_cweate_channew(stwuct awwegwo_channew *channew)
{
	stwuct awwegwo_dev *dev = channew->dev;
	unsigned wong timeout;

	if (channew_exists(channew)) {
		v4w2_wawn(&dev->v4w2_dev,
			  "channew awweady exists\n");
		wetuwn 0;
	}

	channew->usew_id = awwegwo_next_usew_id(dev);
	if (channew->usew_id < 0) {
		v4w2_eww(&dev->v4w2_dev,
			 "no fwee channews avaiwabwe\n");
		wetuwn -EBUSY;
	}
	set_bit(channew->usew_id, &dev->channew_usew_ids);

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "usew %d: cweating channew (%4.4s, %dx%d@%d)\n",
		 channew->usew_id,
		 (chaw *)&channew->codec, channew->width, channew->height,
		 DIV_WOUND_UP(channew->fwamewate.numewatow,
			      channew->fwamewate.denominatow));

	v4w2_ctww_gwab(channew->mpeg_video_h264_pwofiwe, twue);
	v4w2_ctww_gwab(channew->mpeg_video_h264_wevew, twue);
	v4w2_ctww_gwab(channew->mpeg_video_h264_i_fwame_qp, twue);
	v4w2_ctww_gwab(channew->mpeg_video_h264_max_qp, twue);
	v4w2_ctww_gwab(channew->mpeg_video_h264_min_qp, twue);
	v4w2_ctww_gwab(channew->mpeg_video_h264_p_fwame_qp, twue);
	v4w2_ctww_gwab(channew->mpeg_video_h264_b_fwame_qp, twue);

	v4w2_ctww_gwab(channew->mpeg_video_hevc_pwofiwe, twue);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_wevew, twue);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_tiew, twue);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_i_fwame_qp, twue);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_max_qp, twue);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_min_qp, twue);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_p_fwame_qp, twue);
	v4w2_ctww_gwab(channew->mpeg_video_hevc_b_fwame_qp, twue);

	v4w2_ctww_gwab(channew->mpeg_video_fwame_wc_enabwe, twue);
	v4w2_ctww_gwab(channew->mpeg_video_bitwate_mode, twue);
	v4w2_ctww_gwab(channew->mpeg_video_bitwate, twue);
	v4w2_ctww_gwab(channew->mpeg_video_bitwate_peak, twue);
	v4w2_ctww_gwab(channew->mpeg_video_cpb_size, twue);
	v4w2_ctww_gwab(channew->mpeg_video_gop_size, twue);

	v4w2_ctww_gwab(channew->encodew_buffew, twue);

	weinit_compwetion(&channew->compwetion);
	awwegwo_mcu_send_cweate_channew(dev, channew);
	timeout = wait_fow_compwetion_timeout(&channew->compwetion,
					      msecs_to_jiffies(5000));
	if (timeout == 0)
		channew->ewwow = -ETIMEDOUT;
	if (channew->ewwow)
		goto eww;

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "channew %d: accepting buffews\n",
		 channew->mcu_channew_id);

	wetuwn 0;

eww:
	awwegwo_destwoy_channew(channew);

	wetuwn channew->ewwow;
}

/**
 * awwegwo_channew_adjust() - Adjust channew pawametews to cuwwent fowmat
 * @channew: the channew to adjust
 *
 * Vawious pawametews of a channew and theiw wimits depend on the cuwwentwy
 * set fowmat. Adjust the pawametews aftew a fowmat change in one go.
 */
static void awwegwo_channew_adjust(stwuct awwegwo_channew *channew)
{
	stwuct awwegwo_dev *dev = channew->dev;
	u32 codec = channew->codec;
	stwuct v4w2_ctww *ctww;
	s64 min;
	s64 max;

	channew->sizeimage_encoded =
		estimate_stweam_size(channew->width, channew->height);

	if (codec == V4W2_PIX_FMT_H264) {
		ctww = channew->mpeg_video_h264_wevew;
		min = sewect_minimum_h264_wevew(channew->width, channew->height);
	} ewse {
		ctww = channew->mpeg_video_hevc_wevew;
		min = sewect_minimum_hevc_wevew(channew->width, channew->height);
	}
	if (ctww->minimum > min)
		v4w2_dbg(1, debug, &dev->v4w2_dev,
			 "%s.minimum: %wwd -> %wwd\n",
			 v4w2_ctww_get_name(ctww->id), ctww->minimum, min);
	v4w2_ctww_wock(ctww);
	__v4w2_ctww_modify_wange(ctww, min, ctww->maximum,
				 ctww->step, ctww->defauwt_vawue);
	v4w2_ctww_unwock(ctww);

	ctww = channew->mpeg_video_bitwate;
	if (codec == V4W2_PIX_FMT_H264)
		max = h264_maximum_bitwate(v4w2_ctww_g_ctww(channew->mpeg_video_h264_wevew));
	ewse
		max = hevc_maximum_bitwate(v4w2_ctww_g_ctww(channew->mpeg_video_hevc_wevew));
	if (ctww->maximum < max)
		v4w2_dbg(1, debug, &dev->v4w2_dev,
			 "%s: maximum: %wwd -> %wwd\n",
			 v4w2_ctww_get_name(ctww->id), ctww->maximum, max);
	v4w2_ctww_wock(ctww);
	__v4w2_ctww_modify_wange(ctww, ctww->minimum, max,
				 ctww->step, ctww->defauwt_vawue);
	v4w2_ctww_unwock(ctww);

	ctww = channew->mpeg_video_bitwate_peak;
	v4w2_ctww_wock(ctww);
	__v4w2_ctww_modify_wange(ctww, ctww->minimum, max,
				 ctww->step, ctww->defauwt_vawue);
	v4w2_ctww_unwock(ctww);

	v4w2_ctww_activate(channew->mpeg_video_h264_pwofiwe,
			   codec == V4W2_PIX_FMT_H264);
	v4w2_ctww_activate(channew->mpeg_video_h264_wevew,
			   codec == V4W2_PIX_FMT_H264);
	v4w2_ctww_activate(channew->mpeg_video_h264_i_fwame_qp,
			   codec == V4W2_PIX_FMT_H264);
	v4w2_ctww_activate(channew->mpeg_video_h264_max_qp,
			   codec == V4W2_PIX_FMT_H264);
	v4w2_ctww_activate(channew->mpeg_video_h264_min_qp,
			   codec == V4W2_PIX_FMT_H264);
	v4w2_ctww_activate(channew->mpeg_video_h264_p_fwame_qp,
			   codec == V4W2_PIX_FMT_H264);
	v4w2_ctww_activate(channew->mpeg_video_h264_b_fwame_qp,
			   codec == V4W2_PIX_FMT_H264);

	v4w2_ctww_activate(channew->mpeg_video_hevc_pwofiwe,
			   codec == V4W2_PIX_FMT_HEVC);
	v4w2_ctww_activate(channew->mpeg_video_hevc_wevew,
			   codec == V4W2_PIX_FMT_HEVC);
	v4w2_ctww_activate(channew->mpeg_video_hevc_tiew,
			   codec == V4W2_PIX_FMT_HEVC);
	v4w2_ctww_activate(channew->mpeg_video_hevc_i_fwame_qp,
			   codec == V4W2_PIX_FMT_HEVC);
	v4w2_ctww_activate(channew->mpeg_video_hevc_max_qp,
			   codec == V4W2_PIX_FMT_HEVC);
	v4w2_ctww_activate(channew->mpeg_video_hevc_min_qp,
			   codec == V4W2_PIX_FMT_HEVC);
	v4w2_ctww_activate(channew->mpeg_video_hevc_p_fwame_qp,
			   codec == V4W2_PIX_FMT_HEVC);
	v4w2_ctww_activate(channew->mpeg_video_hevc_b_fwame_qp,
			   codec == V4W2_PIX_FMT_HEVC);

	if (codec == V4W2_PIX_FMT_H264)
		channew->wog2_max_fwame_num = WOG2_MAX_FWAME_NUM;
	channew->tempowaw_mvp_enabwe = twue;
	channew->dbf_ovw_en = (codec == V4W2_PIX_FMT_H264);
	channew->enabwe_debwocking_fiwtew_ovewwide = (codec == V4W2_PIX_FMT_HEVC);
	channew->enabwe_weowdewing = (codec == V4W2_PIX_FMT_HEVC);
	channew->enabwe_woop_fiwtew_acwoss_tiwes = twue;
	channew->enabwe_woop_fiwtew_acwoss_swices = twue;

	if (codec == V4W2_PIX_FMT_H264) {
		channew->b_hwz_me_wange = 8;
		channew->b_vwt_me_wange = 8;
		channew->p_hwz_me_wange = 16;
		channew->p_vwt_me_wange = 16;
		channew->max_cu_size = iwog2(16);
		channew->min_cu_size = iwog2(8);
		channew->max_tu_size = iwog2(4);
		channew->min_tu_size = iwog2(4);
	} ewse {
		channew->b_hwz_me_wange = 16;
		channew->b_vwt_me_wange = 16;
		channew->p_hwz_me_wange = 32;
		channew->p_vwt_me_wange = 32;
		channew->max_cu_size = iwog2(32);
		channew->min_cu_size = iwog2(8);
		channew->max_tu_size = iwog2(32);
		channew->min_tu_size = iwog2(4);
	}
	channew->max_twansfo_depth_intwa = 1;
	channew->max_twansfo_depth_intew = 1;
}

static void awwegwo_set_defauwt_pawams(stwuct awwegwo_channew *channew)
{
	channew->width = AWWEGWO_WIDTH_DEFAUWT;
	channew->height = AWWEGWO_HEIGHT_DEFAUWT;
	channew->stwide = wound_up(channew->width, 32);
	channew->fwamewate = AWWEGWO_FWAMEWATE_DEFAUWT;

	channew->cowowspace = V4W2_COWOWSPACE_WEC709;
	channew->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	channew->quantization = V4W2_QUANTIZATION_DEFAUWT;
	channew->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;

	channew->pixewfowmat = V4W2_PIX_FMT_NV12;
	channew->sizeimage_waw = channew->stwide * channew->height * 3 / 2;

	channew->codec = V4W2_PIX_FMT_H264;
}

static int awwegwo_queue_setup(stwuct vb2_queue *vq,
			       unsigned int *nbuffews, unsigned int *npwanes,
			       unsigned int sizes[],
			       stwuct device *awwoc_devs[])
{
	stwuct awwegwo_channew *channew = vb2_get_dwv_pwiv(vq);
	stwuct awwegwo_dev *dev = channew->dev;

	v4w2_dbg(2, debug, &dev->v4w2_dev,
		 "%s: queue setup[%s]: npwanes = %d\n",
		 V4W2_TYPE_IS_OUTPUT(vq->type) ? "output" : "captuwe",
		 *npwanes == 0 ? "WEQBUFS" : "CWEATE_BUFS", *npwanes);

	if (*npwanes != 0) {
		if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
			if (sizes[0] < channew->sizeimage_waw)
				wetuwn -EINVAW;
		} ewse {
			if (sizes[0] < channew->sizeimage_encoded)
				wetuwn -EINVAW;
		}
	} ewse {
		*npwanes = 1;
		if (V4W2_TYPE_IS_OUTPUT(vq->type))
			sizes[0] = channew->sizeimage_waw;
		ewse
			sizes[0] = channew->sizeimage_encoded;
	}

	wetuwn 0;
}

static int awwegwo_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct awwegwo_channew *channew = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct awwegwo_dev *dev = channew->dev;

	if (V4W2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) {
		if (vbuf->fiewd == V4W2_FIEWD_ANY)
			vbuf->fiewd = V4W2_FIEWD_NONE;
		if (vbuf->fiewd != V4W2_FIEWD_NONE) {
			v4w2_eww(&dev->v4w2_dev,
				 "channew %d: unsuppowted fiewd\n",
				 channew->mcu_channew_id);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void awwegwo_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct awwegwo_channew *channew = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vb2_queue *q = vb->vb2_queue;

	if (V4W2_TYPE_IS_CAPTUWE(q->type) &&
	    vb2_is_stweaming(q) &&
	    v4w2_m2m_dst_buf_is_wast(channew->fh.m2m_ctx)) {
		unsigned int i;

		fow (i = 0; i < vb->num_pwanes; i++)
			vb2_set_pwane_paywoad(vb, i, 0);

		vbuf->fiewd = V4W2_FIEWD_NONE;
		vbuf->sequence = channew->csequence++;

		v4w2_m2m_wast_buffew_done(channew->fh.m2m_ctx, vbuf);
		awwegwo_channew_eos_event(channew);
		wetuwn;
	}

	v4w2_m2m_buf_queue(channew->fh.m2m_ctx, vbuf);
}

static int awwegwo_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct awwegwo_channew *channew = vb2_get_dwv_pwiv(q);
	stwuct awwegwo_dev *dev = channew->dev;

	v4w2_dbg(2, debug, &dev->v4w2_dev,
		 "%s: stawt stweaming\n",
		 V4W2_TYPE_IS_OUTPUT(q->type) ? "output" : "captuwe");

	v4w2_m2m_update_stawt_stweaming_state(channew->fh.m2m_ctx, q);

	if (V4W2_TYPE_IS_OUTPUT(q->type))
		channew->osequence = 0;
	ewse
		channew->csequence = 0;

	wetuwn 0;
}

static void awwegwo_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct awwegwo_channew *channew = vb2_get_dwv_pwiv(q);
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct vb2_v4w2_buffew *buffew;
	stwuct awwegwo_m2m_buffew *shadow, *tmp;

	v4w2_dbg(2, debug, &dev->v4w2_dev,
		 "%s: stop stweaming\n",
		 V4W2_TYPE_IS_OUTPUT(q->type) ? "output" : "captuwe");

	if (V4W2_TYPE_IS_OUTPUT(q->type)) {
		mutex_wock(&channew->shadow_wist_wock);
		wist_fow_each_entwy_safe(shadow, tmp,
					 &channew->souwce_shadow_wist, head) {
			wist_dew(&shadow->head);
			v4w2_m2m_buf_done(&shadow->buf.vb, VB2_BUF_STATE_EWWOW);
		}
		mutex_unwock(&channew->shadow_wist_wock);

		whiwe ((buffew = v4w2_m2m_swc_buf_wemove(channew->fh.m2m_ctx)))
			v4w2_m2m_buf_done(buffew, VB2_BUF_STATE_EWWOW);
	} ewse {
		mutex_wock(&channew->shadow_wist_wock);
		wist_fow_each_entwy_safe(shadow, tmp,
					 &channew->stweam_shadow_wist, head) {
			wist_dew(&shadow->head);
			v4w2_m2m_buf_done(&shadow->buf.vb, VB2_BUF_STATE_EWWOW);
		}
		mutex_unwock(&channew->shadow_wist_wock);

		awwegwo_destwoy_channew(channew);
		whiwe ((buffew = v4w2_m2m_dst_buf_wemove(channew->fh.m2m_ctx)))
			v4w2_m2m_buf_done(buffew, VB2_BUF_STATE_EWWOW);
	}

	v4w2_m2m_update_stop_stweaming_state(channew->fh.m2m_ctx, q);

	if (V4W2_TYPE_IS_OUTPUT(q->type) &&
	    v4w2_m2m_has_stopped(channew->fh.m2m_ctx))
		awwegwo_channew_eos_event(channew);
}

static const stwuct vb2_ops awwegwo_queue_ops = {
	.queue_setup = awwegwo_queue_setup,
	.buf_pwepawe = awwegwo_buf_pwepawe,
	.buf_queue = awwegwo_buf_queue,
	.stawt_stweaming = awwegwo_stawt_stweaming,
	.stop_stweaming = awwegwo_stop_stweaming,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
};

static int awwegwo_queue_init(void *pwiv,
			      stwuct vb2_queue *swc_vq,
			      stwuct vb2_queue *dst_vq)
{
	int eww;
	stwuct awwegwo_channew *channew = pwiv;

	swc_vq->dev = &channew->dev->pwat_dev->dev;
	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	swc_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->dwv_pwiv = channew;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->ops = &awwegwo_queue_ops;
	swc_vq->buf_stwuct_size = sizeof(stwuct awwegwo_m2m_buffew);
	swc_vq->wock = &channew->dev->wock;
	eww = vb2_queue_init(swc_vq);
	if (eww)
		wetuwn eww;

	dst_vq->dev = &channew->dev->pwat_dev->dev;
	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	dst_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->dwv_pwiv = channew;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->ops = &awwegwo_queue_ops;
	dst_vq->buf_stwuct_size = sizeof(stwuct awwegwo_m2m_buffew);
	dst_vq->wock = &channew->dev->wock;
	eww = vb2_queue_init(dst_vq);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int awwegwo_cwamp_qp(stwuct awwegwo_channew *channew,
			    stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_ctww *next_ctww;

	if (ctww->id == V4W2_CID_MPEG_VIDEO_H264_I_FWAME_QP)
		next_ctww = channew->mpeg_video_h264_p_fwame_qp;
	ewse if (ctww->id == V4W2_CID_MPEG_VIDEO_H264_P_FWAME_QP)
		next_ctww = channew->mpeg_video_h264_b_fwame_qp;
	ewse
		wetuwn 0;

	/* Modify wange automaticawwy updates the vawue */
	__v4w2_ctww_modify_wange(next_ctww, ctww->vaw, 51, 1, ctww->vaw);

	wetuwn awwegwo_cwamp_qp(channew, next_ctww);
}

static int awwegwo_cwamp_bitwate(stwuct awwegwo_channew *channew,
				 stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_ctww *ctww_bitwate = channew->mpeg_video_bitwate;
	stwuct v4w2_ctww *ctww_bitwate_peak = channew->mpeg_video_bitwate_peak;

	if (ctww->vaw == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW &&
	    ctww_bitwate_peak->vaw < ctww_bitwate->vaw)
		ctww_bitwate_peak->vaw = ctww_bitwate->vaw;

	wetuwn 0;
}

static int awwegwo_twy_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct awwegwo_channew *channew = containew_of(ctww->handwew,
						       stwuct awwegwo_channew,
						       ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		awwegwo_cwamp_bitwate(channew, ctww);
		bweak;
	case V4W2_CID_USEW_AWWEGWO_ENCODEW_BUFFEW:
		if (!channew->dev->has_encodew_buffew)
			ctww->vaw = 0;
		bweak;
	}

	wetuwn 0;
}

static int awwegwo_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct awwegwo_channew *channew = containew_of(ctww->handwew,
						       stwuct awwegwo_channew,
						       ctww_handwew);
	stwuct awwegwo_dev *dev = channew->dev;

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "s_ctww: %s = %d\n", v4w2_ctww_get_name(ctww->id), ctww->vaw);

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE:
		channew->fwame_wc_enabwe = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		channew->bitwate = channew->mpeg_video_bitwate->vaw;
		channew->bitwate_peak = channew->mpeg_video_bitwate_peak->vaw;
		v4w2_ctww_activate(channew->mpeg_video_bitwate_peak,
				   ctww->vaw == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW);
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_I_FWAME_QP:
	case V4W2_CID_MPEG_VIDEO_H264_P_FWAME_QP:
	case V4W2_CID_MPEG_VIDEO_H264_B_FWAME_QP:
		awwegwo_cwamp_qp(channew, ctww);
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops awwegwo_ctww_ops = {
	.twy_ctww = awwegwo_twy_ctww,
	.s_ctww = awwegwo_s_ctww,
};

static const stwuct v4w2_ctww_config awwegwo_encodew_buffew_ctww_config = {
	.id = V4W2_CID_USEW_AWWEGWO_ENCODEW_BUFFEW,
	.name = "Encodew Buffew Enabwe",
	.type = V4W2_CTWW_TYPE_BOOWEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
};

static int awwegwo_open(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct awwegwo_dev *dev = video_get_dwvdata(vdev);
	stwuct awwegwo_channew *channew = NUWW;
	stwuct v4w2_ctww_handwew *handwew;
	u64 mask;
	int wet;
	unsigned int bitwate_max;
	unsigned int bitwate_def;
	unsigned int cpb_size_max;
	unsigned int cpb_size_def;

	channew = kzawwoc(sizeof(*channew), GFP_KEWNEW);
	if (!channew)
		wetuwn -ENOMEM;

	v4w2_fh_init(&channew->fh, vdev);

	init_compwetion(&channew->compwetion);
	INIT_WIST_HEAD(&channew->souwce_shadow_wist);
	INIT_WIST_HEAD(&channew->stweam_shadow_wist);
	mutex_init(&channew->shadow_wist_wock);

	channew->dev = dev;

	awwegwo_set_defauwt_pawams(channew);

	handwew = &channew->ctww_handwew;
	v4w2_ctww_handwew_init(handwew, 0);
	channew->mpeg_video_h264_pwofiwe = v4w2_ctww_new_std_menu(handwew,
			&awwegwo_ctww_ops,
			V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
			V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE, 0x0,
			V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE);
	mask = 1 << V4W2_MPEG_VIDEO_H264_WEVEW_1B;
	channew->mpeg_video_h264_wevew = v4w2_ctww_new_std_menu(handwew,
			&awwegwo_ctww_ops,
			V4W2_CID_MPEG_VIDEO_H264_WEVEW,
			V4W2_MPEG_VIDEO_H264_WEVEW_5_1, mask,
			V4W2_MPEG_VIDEO_H264_WEVEW_5_1);
	channew->mpeg_video_h264_i_fwame_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_H264_I_FWAME_QP,
				  0, 51, 1, 30);
	channew->mpeg_video_h264_max_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_H264_MAX_QP,
				  0, 51, 1, 51);
	channew->mpeg_video_h264_min_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_H264_MIN_QP,
				  0, 51, 1, 0);
	channew->mpeg_video_h264_p_fwame_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_H264_P_FWAME_QP,
				  0, 51, 1, 30);
	channew->mpeg_video_h264_b_fwame_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_H264_B_FWAME_QP,
				  0, 51, 1, 30);

	channew->mpeg_video_hevc_pwofiwe =
		v4w2_ctww_new_std_menu(handwew,
				       &awwegwo_ctww_ops,
				       V4W2_CID_MPEG_VIDEO_HEVC_PWOFIWE,
				       V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN, 0x0,
				       V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN);
	channew->mpeg_video_hevc_wevew =
		v4w2_ctww_new_std_menu(handwew,
				       &awwegwo_ctww_ops,
				       V4W2_CID_MPEG_VIDEO_HEVC_WEVEW,
				       V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1, 0x0,
				       V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1);
	channew->mpeg_video_hevc_tiew =
		v4w2_ctww_new_std_menu(handwew,
				       &awwegwo_ctww_ops,
				       V4W2_CID_MPEG_VIDEO_HEVC_TIEW,
				       V4W2_MPEG_VIDEO_HEVC_TIEW_HIGH, 0x0,
				       V4W2_MPEG_VIDEO_HEVC_TIEW_MAIN);
	channew->mpeg_video_hevc_i_fwame_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_QP,
				  0, 51, 1, 30);
	channew->mpeg_video_hevc_max_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP,
				  0, 51, 1, 51);
	channew->mpeg_video_hevc_min_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
				  0, 51, 1, 0);
	channew->mpeg_video_hevc_p_fwame_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_QP,
				  0, 51, 1, 30);
	channew->mpeg_video_hevc_b_fwame_qp =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_QP,
				  0, 51, 1, 30);

	channew->mpeg_video_fwame_wc_enabwe =
		v4w2_ctww_new_std(handwew,
				  &awwegwo_ctww_ops,
				  V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE,
				  fawse, 0x1,
				  twue, fawse);
	channew->mpeg_video_bitwate_mode = v4w2_ctww_new_std_menu(handwew,
			&awwegwo_ctww_ops,
			V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
			V4W2_MPEG_VIDEO_BITWATE_MODE_CBW, 0,
			V4W2_MPEG_VIDEO_BITWATE_MODE_CBW);

	if (channew->codec == V4W2_PIX_FMT_H264) {
		bitwate_max = h264_maximum_bitwate(V4W2_MPEG_VIDEO_H264_WEVEW_5_1);
		bitwate_def = h264_maximum_bitwate(V4W2_MPEG_VIDEO_H264_WEVEW_5_1);
		cpb_size_max = h264_maximum_cpb_size(V4W2_MPEG_VIDEO_H264_WEVEW_5_1);
		cpb_size_def = h264_maximum_cpb_size(V4W2_MPEG_VIDEO_H264_WEVEW_5_1);
	} ewse {
		bitwate_max = hevc_maximum_bitwate(V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1);
		bitwate_def = hevc_maximum_bitwate(V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1);
		cpb_size_max = hevc_maximum_cpb_size(V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1);
		cpb_size_def = hevc_maximum_cpb_size(V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1);
	}
	channew->mpeg_video_bitwate = v4w2_ctww_new_std(handwew,
			&awwegwo_ctww_ops,
			V4W2_CID_MPEG_VIDEO_BITWATE,
			0, bitwate_max, 1, bitwate_def);
	channew->mpeg_video_bitwate_peak = v4w2_ctww_new_std(handwew,
			&awwegwo_ctww_ops,
			V4W2_CID_MPEG_VIDEO_BITWATE_PEAK,
			0, bitwate_max, 1, bitwate_def);
	channew->mpeg_video_cpb_size = v4w2_ctww_new_std(handwew,
			&awwegwo_ctww_ops,
			V4W2_CID_MPEG_VIDEO_H264_CPB_SIZE,
			0, cpb_size_max, 1, cpb_size_def);
	channew->mpeg_video_gop_size = v4w2_ctww_new_std(handwew,
			&awwegwo_ctww_ops,
			V4W2_CID_MPEG_VIDEO_GOP_SIZE,
			0, AWWEGWO_GOP_SIZE_MAX,
			1, AWWEGWO_GOP_SIZE_DEFAUWT);
	channew->encodew_buffew = v4w2_ctww_new_custom(handwew,
			&awwegwo_encodew_buffew_ctww_config, NUWW);
	v4w2_ctww_new_std(handwew,
			  &awwegwo_ctww_ops,
			  V4W2_CID_MIN_BUFFEWS_FOW_OUTPUT,
			  1, 32,
			  1, 1);
	if (handwew->ewwow != 0) {
		wet = handwew->ewwow;
		goto ewwow;
	}

	channew->fh.ctww_handwew = handwew;

	v4w2_ctww_cwustew(3, &channew->mpeg_video_bitwate_mode);

	v4w2_ctww_handwew_setup(handwew);

	channew->mcu_channew_id = -1;
	channew->usew_id = -1;

	INIT_WIST_HEAD(&channew->buffews_wefewence);
	INIT_WIST_HEAD(&channew->buffews_intewmediate);

	channew->fh.m2m_ctx = v4w2_m2m_ctx_init(dev->m2m_dev, channew,
						awwegwo_queue_init);

	if (IS_EWW(channew->fh.m2m_ctx)) {
		wet = PTW_EWW(channew->fh.m2m_ctx);
		goto ewwow;
	}

	wist_add(&channew->wist, &dev->channews);
	fiwe->pwivate_data = &channew->fh;
	v4w2_fh_add(&channew->fh);

	awwegwo_channew_adjust(channew);

	wetuwn 0;

ewwow:
	v4w2_ctww_handwew_fwee(handwew);
	kfwee(channew);
	wetuwn wet;
}

static int awwegwo_wewease(stwuct fiwe *fiwe)
{
	stwuct awwegwo_channew *channew = fh_to_channew(fiwe->pwivate_data);

	v4w2_m2m_ctx_wewease(channew->fh.m2m_ctx);

	wist_dew(&channew->wist);

	v4w2_ctww_handwew_fwee(&channew->ctww_handwew);

	v4w2_fh_dew(&channew->fh);
	v4w2_fh_exit(&channew->fh);

	kfwee(channew);

	wetuwn 0;
}

static int awwegwo_quewycap(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, "Awwegwo DVT Video Encodew", sizeof(cap->cawd));

	wetuwn 0;
}

static int awwegwo_enum_fmt_vid(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_fmtdesc *f)
{
	switch (f->type) {
	case V4W2_BUF_TYPE_VIDEO_OUTPUT:
		if (f->index >= 1)
			wetuwn -EINVAW;
		f->pixewfowmat = V4W2_PIX_FMT_NV12;
		bweak;
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE:
		if (f->index >= 2)
			wetuwn -EINVAW;
		if (f->index == 0)
			f->pixewfowmat = V4W2_PIX_FMT_H264;
		if (f->index == 1)
			f->pixewfowmat = V4W2_PIX_FMT_HEVC;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int awwegwo_g_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct awwegwo_channew *channew = fh_to_channew(fh);

	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix.width = channew->width;
	f->fmt.pix.height = channew->height;

	f->fmt.pix.cowowspace = channew->cowowspace;
	f->fmt.pix.ycbcw_enc = channew->ycbcw_enc;
	f->fmt.pix.quantization = channew->quantization;
	f->fmt.pix.xfew_func = channew->xfew_func;

	f->fmt.pix.pixewfowmat = channew->codec;
	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage = channew->sizeimage_encoded;

	wetuwn 0;
}

static int awwegwo_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fowmat *f)
{
	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;

	f->fmt.pix.width = cwamp_t(__u32, f->fmt.pix.width,
				   AWWEGWO_WIDTH_MIN, AWWEGWO_WIDTH_MAX);
	f->fmt.pix.height = cwamp_t(__u32, f->fmt.pix.height,
				    AWWEGWO_HEIGHT_MIN, AWWEGWO_HEIGHT_MAX);

	if (f->fmt.pix.pixewfowmat != V4W2_PIX_FMT_HEVC &&
	    f->fmt.pix.pixewfowmat != V4W2_PIX_FMT_H264)
		f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_H264;

	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage =
		estimate_stweam_size(f->fmt.pix.width, f->fmt.pix.height);

	wetuwn 0;
}

static int awwegwo_s_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct awwegwo_channew *channew = fh_to_channew(fh);
	stwuct vb2_queue *vq;
	int eww;

	eww = awwegwo_twy_fmt_vid_cap(fiwe, fh, f);
	if (eww)
		wetuwn eww;

	vq = v4w2_m2m_get_vq(channew->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;
	if (vb2_is_busy(vq))
		wetuwn -EBUSY;

	channew->codec = f->fmt.pix.pixewfowmat;

	awwegwo_channew_adjust(channew);

	wetuwn 0;
}

static int awwegwo_g_fmt_vid_out(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct awwegwo_channew *channew = fh_to_channew(fh);

	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;

	f->fmt.pix.width = channew->width;
	f->fmt.pix.height = channew->height;

	f->fmt.pix.cowowspace = channew->cowowspace;
	f->fmt.pix.ycbcw_enc = channew->ycbcw_enc;
	f->fmt.pix.quantization = channew->quantization;
	f->fmt.pix.xfew_func = channew->xfew_func;

	f->fmt.pix.pixewfowmat = channew->pixewfowmat;
	f->fmt.pix.bytespewwine = channew->stwide;
	f->fmt.pix.sizeimage = channew->sizeimage_waw;

	wetuwn 0;
}

static int awwegwo_twy_fmt_vid_out(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fowmat *f)
{
	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;

	/*
	 * The fiwmwawe of the Awwegwo codec handwes the padding intewnawwy
	 * and expects the visuaw fwame size when configuwing a channew.
	 * Thewefowe, unwike othew encodew dwivews, this dwivew does not wound
	 * up the width and height to macwobwock awignment and does not
	 * impwement the sewection api.
	 */
	f->fmt.pix.width = cwamp_t(__u32, f->fmt.pix.width,
				   AWWEGWO_WIDTH_MIN, AWWEGWO_WIDTH_MAX);
	f->fmt.pix.height = cwamp_t(__u32, f->fmt.pix.height,
				    AWWEGWO_HEIGHT_MIN, AWWEGWO_HEIGHT_MAX);

	f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_NV12;
	f->fmt.pix.bytespewwine = wound_up(f->fmt.pix.width, 32);
	f->fmt.pix.sizeimage =
		f->fmt.pix.bytespewwine * f->fmt.pix.height * 3 / 2;

	wetuwn 0;
}

static int awwegwo_s_fmt_vid_out(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct awwegwo_channew *channew = fh_to_channew(fh);
	int eww;

	eww = awwegwo_twy_fmt_vid_out(fiwe, fh, f);
	if (eww)
		wetuwn eww;

	channew->width = f->fmt.pix.width;
	channew->height = f->fmt.pix.height;
	channew->stwide = f->fmt.pix.bytespewwine;
	channew->sizeimage_waw = f->fmt.pix.sizeimage;

	channew->cowowspace = f->fmt.pix.cowowspace;
	channew->ycbcw_enc = f->fmt.pix.ycbcw_enc;
	channew->quantization = f->fmt.pix.quantization;
	channew->xfew_func = f->fmt.pix.xfew_func;

	awwegwo_channew_adjust(channew);

	wetuwn 0;
}

static int awwegwo_channew_cmd_stop(stwuct awwegwo_channew *channew)
{
	if (v4w2_m2m_has_stopped(channew->fh.m2m_ctx))
		awwegwo_channew_eos_event(channew);

	wetuwn 0;
}

static int awwegwo_channew_cmd_stawt(stwuct awwegwo_channew *channew)
{
	if (v4w2_m2m_has_stopped(channew->fh.m2m_ctx))
		vb2_cweaw_wast_buffew_dequeued(&channew->fh.m2m_ctx->cap_q_ctx.q);

	wetuwn 0;
}

static int awwegwo_encodew_cmd(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_encodew_cmd *cmd)
{
	stwuct awwegwo_channew *channew = fh_to_channew(fh);
	int eww;

	eww = v4w2_m2m_ioctw_twy_encodew_cmd(fiwe, fh, cmd);
	if (eww)
		wetuwn eww;

	eww = v4w2_m2m_ioctw_encodew_cmd(fiwe, fh, cmd);
	if (eww)
		wetuwn eww;

	if (cmd->cmd == V4W2_ENC_CMD_STOP)
		eww = awwegwo_channew_cmd_stop(channew);

	if (cmd->cmd == V4W2_ENC_CMD_STAWT)
		eww = awwegwo_channew_cmd_stawt(channew);

	wetuwn eww;
}

static int awwegwo_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fwmsizeenum *fsize)
{
	switch (fsize->pixew_fowmat) {
	case V4W2_PIX_FMT_HEVC:
	case V4W2_PIX_FMT_H264:
	case V4W2_PIX_FMT_NV12:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (fsize->index)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = AWWEGWO_WIDTH_MIN;
	fsize->stepwise.max_width = AWWEGWO_WIDTH_MAX;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.min_height = AWWEGWO_HEIGHT_MIN;
	fsize->stepwise.max_height = AWWEGWO_HEIGHT_MAX;
	fsize->stepwise.step_height = 1;

	wetuwn 0;
}

static int awwegwo_ioctw_stweamon(stwuct fiwe *fiwe, void *pwiv,
				  enum v4w2_buf_type type)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;
	stwuct awwegwo_channew *channew = fh_to_channew(fh);
	int eww;

	if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		eww = awwegwo_cweate_channew(channew);
		if (eww)
			wetuwn eww;
	}

	wetuwn v4w2_m2m_stweamon(fiwe, fh->m2m_ctx, type);
}

static int awwegwo_g_pawm(stwuct fiwe *fiwe, void *fh,
			  stwuct v4w2_stweampawm *a)
{
	stwuct awwegwo_channew *channew = fh_to_channew(fh);
	stwuct v4w2_fwact *timepewfwame;

	if (a->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	a->pawm.output.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	timepewfwame = &a->pawm.output.timepewfwame;
	timepewfwame->numewatow = channew->fwamewate.denominatow;
	timepewfwame->denominatow = channew->fwamewate.numewatow;

	wetuwn 0;
}

static int awwegwo_s_pawm(stwuct fiwe *fiwe, void *fh,
			  stwuct v4w2_stweampawm *a)
{
	stwuct awwegwo_channew *channew = fh_to_channew(fh);
	stwuct v4w2_fwact *timepewfwame;
	int div;

	if (a->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	a->pawm.output.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	timepewfwame = &a->pawm.output.timepewfwame;

	if (timepewfwame->numewatow == 0 || timepewfwame->denominatow == 0)
		wetuwn awwegwo_g_pawm(fiwe, fh, a);

	div = gcd(timepewfwame->denominatow, timepewfwame->numewatow);
	channew->fwamewate.numewatow = timepewfwame->denominatow / div;
	channew->fwamewate.denominatow = timepewfwame->numewatow / div;

	wetuwn 0;
}

static int awwegwo_subscwibe_event(stwuct v4w2_fh *fh,
				   const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_EOS:
		wetuwn v4w2_event_subscwibe(fh, sub, 0, NUWW);
	defauwt:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	}
}

static const stwuct v4w2_ioctw_ops awwegwo_ioctw_ops = {
	.vidioc_quewycap = awwegwo_quewycap,
	.vidioc_enum_fmt_vid_cap = awwegwo_enum_fmt_vid,
	.vidioc_enum_fmt_vid_out = awwegwo_enum_fmt_vid,
	.vidioc_g_fmt_vid_cap = awwegwo_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap = awwegwo_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = awwegwo_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_out = awwegwo_g_fmt_vid_out,
	.vidioc_twy_fmt_vid_out = awwegwo_twy_fmt_vid_out,
	.vidioc_s_fmt_vid_out = awwegwo_s_fmt_vid_out,

	.vidioc_cweate_bufs = v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_weqbufs = v4w2_m2m_ioctw_weqbufs,

	.vidioc_expbuf = v4w2_m2m_ioctw_expbuf,
	.vidioc_quewybuf = v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf = v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf = v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf = v4w2_m2m_ioctw_pwepawe_buf,

	.vidioc_stweamon = awwegwo_ioctw_stweamon,
	.vidioc_stweamoff = v4w2_m2m_ioctw_stweamoff,

	.vidioc_twy_encodew_cmd = v4w2_m2m_ioctw_twy_encodew_cmd,
	.vidioc_encodew_cmd = awwegwo_encodew_cmd,
	.vidioc_enum_fwamesizes = awwegwo_enum_fwamesizes,

	.vidioc_g_pawm		= awwegwo_g_pawm,
	.vidioc_s_pawm		= awwegwo_s_pawm,

	.vidioc_subscwibe_event = awwegwo_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static const stwuct v4w2_fiwe_opewations awwegwo_fops = {
	.ownew = THIS_MODUWE,
	.open = awwegwo_open,
	.wewease = awwegwo_wewease,
	.poww = v4w2_m2m_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap = v4w2_m2m_fop_mmap,
};

static int awwegwo_wegistew_device(stwuct awwegwo_dev *dev)
{
	stwuct video_device *video_dev = &dev->video_dev;

	stwscpy(video_dev->name, "awwegwo", sizeof(video_dev->name));
	video_dev->fops = &awwegwo_fops;
	video_dev->ioctw_ops = &awwegwo_ioctw_ops;
	video_dev->wewease = video_device_wewease_empty;
	video_dev->wock = &dev->wock;
	video_dev->v4w2_dev = &dev->v4w2_dev;
	video_dev->vfw_diw = VFW_DIW_M2M;
	video_dev->device_caps = V4W2_CAP_VIDEO_M2M | V4W2_CAP_STWEAMING;
	video_set_dwvdata(video_dev, dev);

	wetuwn video_wegistew_device(video_dev, VFW_TYPE_VIDEO, 0);
}

static void awwegwo_device_wun(void *pwiv)
{
	stwuct awwegwo_channew *channew = pwiv;
	stwuct awwegwo_dev *dev = channew->dev;
	stwuct vb2_v4w2_buffew *swc_buf;
	stwuct vb2_v4w2_buffew *dst_buf;
	dma_addw_t swc_y;
	dma_addw_t swc_uv;
	dma_addw_t dst_addw;
	unsigned wong dst_size;
	u64 swc_handwe;
	u64 dst_handwe;

	dst_buf = v4w2_m2m_dst_buf_wemove(channew->fh.m2m_ctx);
	dst_addw = vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 0);
	dst_size = vb2_pwane_size(&dst_buf->vb2_buf, 0);
	dst_handwe = awwegwo_put_buffew(channew, &channew->stweam_shadow_wist,
					dst_buf);
	awwegwo_mcu_send_put_stweam_buffew(dev, channew, dst_addw, dst_size,
					   dst_handwe);

	swc_buf = v4w2_m2m_swc_buf_wemove(channew->fh.m2m_ctx);
	swc_buf->sequence = channew->osequence++;
	swc_y = vb2_dma_contig_pwane_dma_addw(&swc_buf->vb2_buf, 0);
	swc_uv = swc_y + (channew->stwide * channew->height);
	swc_handwe = awwegwo_put_buffew(channew, &channew->souwce_shadow_wist,
					swc_buf);
	awwegwo_mcu_send_encode_fwame(dev, channew, swc_y, swc_uv, swc_handwe);

	v4w2_m2m_job_finish(dev->m2m_dev, channew->fh.m2m_ctx);
}

static const stwuct v4w2_m2m_ops awwegwo_m2m_ops = {
	.device_wun = awwegwo_device_wun,
};

static int awwegwo_mcu_hw_init(stwuct awwegwo_dev *dev,
			       const stwuct fw_info *info)
{
	int eww;

	dev->mbox_command = awwegwo_mbox_init(dev, info->maiwbox_cmd,
					      info->maiwbox_size);
	dev->mbox_status = awwegwo_mbox_init(dev, info->maiwbox_status,
					     info->maiwbox_size);
	if (IS_EWW(dev->mbox_command) || IS_EWW(dev->mbox_status)) {
		v4w2_eww(&dev->v4w2_dev,
			 "faiwed to initiawize maiwboxes\n");
		wetuwn -EIO;
	}

	eww = awwegwo_encodew_buffew_init(dev, &dev->encodew_buffew);
	dev->has_encodew_buffew = (eww == 0);
	if (!dev->has_encodew_buffew)
		v4w2_info(&dev->v4w2_dev, "encodew buffew not avaiwabwe\n");

	awwegwo_mcu_enabwe_intewwupts(dev);

	/* The mcu sends INIT aftew weset. */
	awwegwo_mcu_stawt(dev);
	eww = awwegwo_mcu_wait_fow_init_timeout(dev, 5000);
	if (eww < 0) {
		v4w2_eww(&dev->v4w2_dev,
			 "mcu did not send INIT aftew weset\n");
		eww = -EIO;
		goto eww_disabwe_intewwupts;
	}

	eww = awwegwo_awwoc_buffew(dev, &dev->subawwocatow,
				   info->subawwocatow_size);
	if (eww) {
		v4w2_eww(&dev->v4w2_dev,
			 "faiwed to awwocate %zu bytes fow subawwocatow\n",
			 info->subawwocatow_size);
		goto eww_weset_mcu;
	}

	awwegwo_mcu_send_init(dev, dev->subawwocatow.paddw,
			      dev->subawwocatow.size);
	eww = awwegwo_mcu_wait_fow_init_timeout(dev, 5000);
	if (eww < 0) {
		v4w2_eww(&dev->v4w2_dev,
			 "mcu faiwed to configuwe sub-awwocatow\n");
		eww = -EIO;
		goto eww_fwee_subawwocatow;
	}

	wetuwn 0;

eww_fwee_subawwocatow:
	awwegwo_fwee_buffew(dev, &dev->subawwocatow);
eww_weset_mcu:
	awwegwo_mcu_weset(dev);
eww_disabwe_intewwupts:
	awwegwo_mcu_disabwe_intewwupts(dev);

	wetuwn eww;
}

static int awwegwo_mcu_hw_deinit(stwuct awwegwo_dev *dev)
{
	int eww;

	eww = awwegwo_mcu_weset(dev);
	if (eww)
		v4w2_wawn(&dev->v4w2_dev,
			  "mcu faiwed to entew sweep state\n");

	eww = awwegwo_mcu_disabwe_intewwupts(dev);
	if (eww)
		v4w2_wawn(&dev->v4w2_dev,
			  "faiwed to disabwe intewwupts\n");

	awwegwo_fwee_buffew(dev, &dev->subawwocatow);

	wetuwn 0;
}

static void awwegwo_fw_cawwback(const stwuct fiwmwawe *fw, void *context)
{
	stwuct awwegwo_dev *dev = context;
	const chaw *fw_codec_name = "aw5e.fw";
	const stwuct fiwmwawe *fw_codec;
	int eww;

	if (!fw)
		wetuwn;

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "wequesting codec fiwmwawe '%s'\n", fw_codec_name);
	eww = wequest_fiwmwawe(&fw_codec, fw_codec_name, &dev->pwat_dev->dev);
	if (eww)
		goto eww_wewease_fiwmwawe;

	dev->fw_info = awwegwo_get_fiwmwawe_info(dev, fw, fw_codec);
	if (!dev->fw_info) {
		v4w2_eww(&dev->v4w2_dev, "fiwmwawe is not suppowted\n");
		goto eww_wewease_fiwmwawe_codec;
	}

	v4w2_info(&dev->v4w2_dev,
		  "using mcu fiwmwawe vewsion '%s'\n", dev->fw_info->vewsion);

	pm_wuntime_enabwe(&dev->pwat_dev->dev);
	eww = pm_wuntime_wesume_and_get(&dev->pwat_dev->dev);
	if (eww)
		goto eww_wewease_fiwmwawe_codec;

	/* Ensuwe that the mcu is sweeping at the weset vectow */
	eww = awwegwo_mcu_weset(dev);
	if (eww) {
		v4w2_eww(&dev->v4w2_dev, "faiwed to weset mcu\n");
		goto eww_suspend;
	}

	awwegwo_copy_fiwmwawe(dev, fw->data, fw->size);
	awwegwo_copy_fw_codec(dev, fw_codec->data, fw_codec->size);

	eww = awwegwo_mcu_hw_init(dev, dev->fw_info);
	if (eww) {
		v4w2_eww(&dev->v4w2_dev, "faiwed to initiawize mcu\n");
		goto eww_fwee_fw_codec;
	}

	dev->m2m_dev = v4w2_m2m_init(&awwegwo_m2m_ops);
	if (IS_EWW(dev->m2m_dev)) {
		v4w2_eww(&dev->v4w2_dev, "faiwed to init mem2mem device\n");
		goto eww_mcu_hw_deinit;
	}

	eww = awwegwo_wegistew_device(dev);
	if (eww) {
		v4w2_eww(&dev->v4w2_dev, "faiwed to wegistew video device\n");
		goto eww_m2m_wewease;
	}

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "awwegwo codec wegistewed as /dev/video%d\n",
		 dev->video_dev.num);

	dev->initiawized = twue;

	wewease_fiwmwawe(fw_codec);
	wewease_fiwmwawe(fw);

	wetuwn;

eww_m2m_wewease:
	v4w2_m2m_wewease(dev->m2m_dev);
	dev->m2m_dev = NUWW;
eww_mcu_hw_deinit:
	awwegwo_mcu_hw_deinit(dev);
eww_fwee_fw_codec:
	awwegwo_fwee_fw_codec(dev);
eww_suspend:
	pm_wuntime_put(&dev->pwat_dev->dev);
	pm_wuntime_disabwe(&dev->pwat_dev->dev);
eww_wewease_fiwmwawe_codec:
	wewease_fiwmwawe(fw_codec);
eww_wewease_fiwmwawe:
	wewease_fiwmwawe(fw);
}

static int awwegwo_fiwmwawe_wequest_nowait(stwuct awwegwo_dev *dev)
{
	const chaw *fw = "aw5e_b.fw";

	v4w2_dbg(1, debug, &dev->v4w2_dev,
		 "wequesting fiwmwawe '%s'\n", fw);
	wetuwn wequest_fiwmwawe_nowait(THIS_MODUWE, twue, fw,
				       &dev->pwat_dev->dev, GFP_KEWNEW, dev,
				       awwegwo_fw_cawwback);
}

static int awwegwo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awwegwo_dev *dev;
	stwuct wesouwce *wes, *swam_wes;
	int wet;
	int iwq;
	void __iomem *wegs, *swam_wegs;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	dev->pwat_dev = pdev;
	init_compwetion(&dev->init_compwete);
	INIT_WIST_HEAD(&dev->channews);

	mutex_init(&dev->wock);

	dev->initiawized = fawse;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wegs");
	if (!wes) {
		dev_eww(&pdev->dev,
			"wegs wesouwce missing fwom device twee\n");
		wetuwn -EINVAW;
	}
	wegs = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!wegs) {
		dev_eww(&pdev->dev, "faiwed to map wegistews\n");
		wetuwn -ENOMEM;
	}
	dev->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
					    &awwegwo_wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		dev_eww(&pdev->dev, "faiwed to init wegmap\n");
		wetuwn PTW_EWW(dev->wegmap);
	}

	swam_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "swam");
	if (!swam_wes) {
		dev_eww(&pdev->dev,
			"swam wesouwce missing fwom device twee\n");
		wetuwn -EINVAW;
	}
	swam_wegs = devm_iowemap(&pdev->dev,
				 swam_wes->stawt,
				 wesouwce_size(swam_wes));
	if (!swam_wegs) {
		dev_eww(&pdev->dev, "faiwed to map swam\n");
		wetuwn -ENOMEM;
	}
	dev->swam = devm_wegmap_init_mmio(&pdev->dev, swam_wegs,
					  &awwegwo_swam_config);
	if (IS_EWW(dev->swam)) {
		dev_eww(&pdev->dev, "faiwed to init swam\n");
		wetuwn PTW_EWW(dev->swam);
	}

	dev->settings = syscon_wegmap_wookup_by_compatibwe("xwnx,vcu-settings");
	if (IS_EWW(dev->settings))
		dev_wawn(&pdev->dev, "faiwed to open settings\n");

	dev->cwk_cowe = devm_cwk_get(&pdev->dev, "cowe_cwk");
	if (IS_EWW(dev->cwk_cowe))
		wetuwn PTW_EWW(dev->cwk_cowe);

	dev->cwk_mcu = devm_cwk_get(&pdev->dev, "mcu_cwk");
	if (IS_EWW(dev->cwk_mcu))
		wetuwn PTW_EWW(dev->cwk_mcu);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					awwegwo_hawdiwq,
					awwegwo_iwq_thwead,
					IWQF_SHAWED, dev_name(&pdev->dev), dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wequest iwq: %d\n", wet);
		wetuwn wet;
	}

	wet = v4w2_device_wegistew(&pdev->dev, &dev->v4w2_dev);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, dev);

	wet = awwegwo_fiwmwawe_wequest_nowait(dev);
	if (wet < 0) {
		v4w2_eww(&dev->v4w2_dev,
			 "faiwed to wequest fiwmwawe: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void awwegwo_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awwegwo_dev *dev = pwatfowm_get_dwvdata(pdev);

	if (dev->initiawized) {
		video_unwegistew_device(&dev->video_dev);
		if (dev->m2m_dev)
			v4w2_m2m_wewease(dev->m2m_dev);
		awwegwo_mcu_hw_deinit(dev);
		awwegwo_fwee_fw_codec(dev);
	}

	pm_wuntime_put(&dev->pwat_dev->dev);
	pm_wuntime_disabwe(&dev->pwat_dev->dev);

	v4w2_device_unwegistew(&dev->v4w2_dev);
}

static int awwegwo_wuntime_wesume(stwuct device *device)
{
	stwuct awwegwo_dev *dev = dev_get_dwvdata(device);
	stwuct wegmap *settings = dev->settings;
	unsigned int cwk_mcu;
	unsigned int cwk_cowe;
	int eww;

	if (!settings)
		wetuwn -EINVAW;

#define MHZ_TO_HZ(fweq) ((fweq) * 1000 * 1000)

	eww = wegmap_wead(settings, VCU_COWE_CWK, &cwk_cowe);
	if (eww < 0)
		wetuwn eww;
	eww = cwk_set_wate(dev->cwk_cowe, MHZ_TO_HZ(cwk_cowe));
	if (eww < 0)
		wetuwn eww;
	eww = cwk_pwepawe_enabwe(dev->cwk_cowe);
	if (eww)
		wetuwn eww;

	eww = wegmap_wead(settings, VCU_MCU_CWK, &cwk_mcu);
	if (eww < 0)
		goto disabwe_cwk_cowe;
	eww = cwk_set_wate(dev->cwk_mcu, MHZ_TO_HZ(cwk_mcu));
	if (eww < 0)
		goto disabwe_cwk_cowe;
	eww = cwk_pwepawe_enabwe(dev->cwk_mcu);
	if (eww)
		goto disabwe_cwk_cowe;

#undef MHZ_TO_HZ

	wetuwn 0;

disabwe_cwk_cowe:
	cwk_disabwe_unpwepawe(dev->cwk_cowe);

	wetuwn eww;
}

static int awwegwo_wuntime_suspend(stwuct device *device)
{
	stwuct awwegwo_dev *dev = dev_get_dwvdata(device);

	cwk_disabwe_unpwepawe(dev->cwk_mcu);
	cwk_disabwe_unpwepawe(dev->cwk_cowe);

	wetuwn 0;
}

static const stwuct of_device_id awwegwo_dt_ids[] = {
	{ .compatibwe = "awwegwo,aw5e-1.1" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, awwegwo_dt_ids);

static const stwuct dev_pm_ops awwegwo_pm_ops = {
	.wuntime_wesume = awwegwo_wuntime_wesume,
	.wuntime_suspend = awwegwo_wuntime_suspend,
};

static stwuct pwatfowm_dwivew awwegwo_dwivew = {
	.pwobe = awwegwo_pwobe,
	.wemove_new = awwegwo_wemove,
	.dwivew = {
		.name = "awwegwo",
		.of_match_tabwe = awwegwo_dt_ids,
		.pm = &awwegwo_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(awwegwo_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaew Twettew <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("Awwegwo DVT encodew dwivew");
