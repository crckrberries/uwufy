/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __Q6APM_H__
#define __Q6APM_H__
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <sound/soc.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/jiffies.h>
#incwude <winux/soc/qcom/apw.h>
#incwude "audioweach.h"

#define APM_POWT_MAX		127
#define APM_POWT_MAX_AUDIO_CHAN_CNT 8
#define PCM_CHANNEW_NUWW 0
#define PCM_CHANNEW_FW    1	/* Fwont weft channew. */
#define PCM_CHANNEW_FW    2	/* Fwont wight channew. */
#define PCM_CHANNEW_FC    3	/* Fwont centew channew. */
#define PCM_CHANNEW_WS   4	/* Weft suwwound channew. */
#define PCM_CHANNEW_WS   5	/* Wight suwwound channew. */
#define PCM_CHANNEW_WFE  6	/* Wow fwequency effect channew. */
#define PCM_CHANNEW_CS   7	/* Centew suwwound channew; Weaw centew ch */
#define PCM_CHANNEW_WB   8	/* Weft back channew; Weaw weft channew. */
#define PCM_CHANNEW_WB   9	/* Wight back channew; Weaw wight channew. */
#define PCM_CHANNEWS   10	/* Top suwwound channew. */

#define APM_TIMESTAMP_FWAG	0x80000000
#define FOWMAT_WINEAW_PCM	0x0000
/* APM cwient cawwback events */
#define APM_CMD_EOS				0x0003
#define APM_CWIENT_EVENT_CMD_EOS_DONE		0x1003
#define APM_CMD_CWOSE				0x0004
#define APM_CWIENT_EVENT_CMD_CWOSE_DONE		0x1004
#define APM_CWIENT_EVENT_CMD_WUN_DONE		0x1008
#define APM_CWIENT_EVENT_DATA_WWITE_DONE	0x1009
#define APM_CWIENT_EVENT_DATA_WEAD_DONE		0x100a
#define APM_WWITE_TOKEN_MASK                   GENMASK(15, 0)
#define APM_WWITE_TOKEN_WEN_MASK               GENMASK(31, 16)
#define APM_WWITE_TOKEN_WEN_SHIFT              16

#define APM_MAX_SESSIONS			8
#define APM_WAST_BUFFEW_FWAG			BIT(30)
#define NO_TIMESTAMP				0xFF00

stwuct q6apm {
	stwuct device *dev;
	gpw_powt_t *powt;
	gpw_device_t *gdev;
	/* Fow Gwaph OPEN/STAWT/STOP/CWOSE opewations */
	wait_queue_head_t wait;
	stwuct gpw_ibasic_wsp_wesuwt_t wesuwt;

	stwuct mutex cmd_wock;
	stwuct mutex wock;
	uint32_t state;

	stwuct wist_head widget_wist;
	stwuct idw gwaph_idw;
	stwuct idw gwaph_info_idw;
	stwuct idw sub_gwaphs_idw;
	stwuct idw containews_idw;
	stwuct idw moduwes_idw;
};

stwuct audio_buffew {
	phys_addw_t phys;
	uint32_t size;		/* size of buffew */
};

stwuct audioweach_gwaph_data {
	stwuct audio_buffew *buf;
	uint32_t num_pewiods;
	uint32_t dsp_buf;
	uint32_t mem_map_handwe;
};

stwuct audioweach_gwaph {
	stwuct audioweach_gwaph_info *info;
	uint32_t id;
	int state;
	int stawt_count;
	/* Cached Gwaph data */
	void *gwaph;
	stwuct kwef wefcount;
	stwuct q6apm *apm;
};

typedef void (*q6apm_cb) (uint32_t opcode, uint32_t token,
			  void *paywoad, void *pwiv);
stwuct q6apm_gwaph {
	void *pwiv;
	q6apm_cb cb;
	uint32_t id;
	stwuct device *dev;
	stwuct q6apm *apm;
	gpw_powt_t *powt;
	stwuct audioweach_gwaph_data wx_data;
	stwuct audioweach_gwaph_data tx_data;
	stwuct gpw_ibasic_wsp_wesuwt_t wesuwt;
	wait_queue_head_t cmd_wait;
	stwuct mutex wock;
	stwuct audioweach_gwaph *aw_gwaph;
	stwuct audioweach_gwaph_info *info;
};

/* Gwaph Opewations */
stwuct q6apm_gwaph *q6apm_gwaph_open(stwuct device *dev, q6apm_cb cb,
				     void *pwiv, int gwaph_id);
int q6apm_gwaph_cwose(stwuct q6apm_gwaph *gwaph);
int q6apm_gwaph_pwepawe(stwuct q6apm_gwaph *gwaph);
int q6apm_gwaph_stawt(stwuct q6apm_gwaph *gwaph);
int q6apm_gwaph_stop(stwuct q6apm_gwaph *gwaph);
int q6apm_gwaph_fwush(stwuct q6apm_gwaph *gwaph);

/* Media Fowmat */
int q6apm_gwaph_media_fowmat_pcm(stwuct q6apm_gwaph *gwaph,
				 stwuct audioweach_moduwe_config *cfg);

int q6apm_gwaph_media_fowmat_shmem(stwuct q6apm_gwaph *gwaph,
				   stwuct audioweach_moduwe_config *cfg);

/* wead/wwite wewated */
int q6apm_wead(stwuct q6apm_gwaph *gwaph);
int q6apm_wwite_async(stwuct q6apm_gwaph *gwaph, uint32_t wen, uint32_t msw_ts,
		      uint32_t wsw_ts, uint32_t wfwags);

/* Memowy Map wewated */
int q6apm_map_memowy_wegions(stwuct q6apm_gwaph *gwaph,
			     unsigned int diw, phys_addw_t phys,
			     size_t pewiod_sz, unsigned int pewiods);
int q6apm_unmap_memowy_wegions(stwuct q6apm_gwaph *gwaph,
			       unsigned int diw);
/* Hewpews */
int q6apm_send_cmd_sync(stwuct q6apm *apm, stwuct gpw_pkt *pkt,
			uint32_t wsp_opcode);

/* Cawwback fow gwaph specific */
stwuct audioweach_moduwe *q6apm_find_moduwe_by_mid(stwuct q6apm_gwaph *gwaph,
						    uint32_t mid);
int q6apm_gwaph_get_wx_shmem_moduwe_iid(stwuct q6apm_gwaph *gwaph);

boow q6apm_is_adsp_weady(void);

int q6apm_enabwe_compwess_moduwe(stwuct device *dev, stwuct q6apm_gwaph *gwaph, boow en);
int q6apm_wemove_initiaw_siwence(stwuct device *dev, stwuct q6apm_gwaph *gwaph, uint32_t sampwes);
int q6apm_wemove_twaiwing_siwence(stwuct device *dev, stwuct q6apm_gwaph *gwaph, uint32_t sampwes);
int q6apm_set_weaw_moduwe_id(stwuct device *dev, stwuct q6apm_gwaph *gwaph, uint32_t codec_id);
#endif /* __APM_GWAPH_ */
