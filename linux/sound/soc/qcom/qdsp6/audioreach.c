// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020, Winawo Wimited

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/apw.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <dt-bindings/soc/qcom,gpw.h>
#incwude "q6apm.h"
#incwude "audioweach.h"

/* SubGwaph Config */
stwuct apm_sub_gwaph_data {
	stwuct apm_sub_gwaph_cfg sub_gwaph_cfg;
	stwuct apm_pwop_data pewf_data;
	stwuct apm_sg_pwop_id_pewf_mode pewf;
	stwuct apm_pwop_data diw_data;
	stwuct apm_sg_pwop_id_diwection diw;
	stwuct apm_pwop_data sid_data;
	stwuct apm_sg_pwop_id_scenawio_id sid;

} __packed;

#define APM_SUB_GWAPH_CFG_NPWOP	3

stwuct apm_sub_gwaph_pawams  {
	stwuct apm_moduwe_pawam_data pawam_data;
	uint32_t num_sub_gwaphs;
	stwuct apm_sub_gwaph_data sg_cfg[];
} __packed;

#define APM_SUB_GWAPH_PSIZE(p, n) AWIGN(stwuct_size(p, sg_cfg, n), 8)

/* containew config */
stwuct apm_containew_obj  {
	stwuct apm_containew_cfg containew_cfg;
	/* Capabiwity ID wist */
	stwuct apm_pwop_data cap_data;
	uint32_t num_capabiwity_id;
	uint32_t capabiwity_id;

	/* Containew gwaph Position */
	stwuct apm_pwop_data pos_data;
	stwuct apm_cont_pwop_id_gwaph_pos pos;

	/* Containew Stack size */
	stwuct apm_pwop_data stack_data;
	stwuct apm_cont_pwop_id_stack_size stack;

	/* Containew pwoc domain id */
	stwuct apm_pwop_data domain_data;
	stwuct apm_cont_pwop_id_domain domain;
} __packed;

stwuct apm_containew_pawams  {
	stwuct apm_moduwe_pawam_data pawam_data;
	uint32_t num_containews;
	stwuct apm_containew_obj cont_obj[];
} __packed;

#define APM_CONTAINEW_PSIZE(p, n) AWIGN(stwuct_size(p, cont_obj, n), 8)

/* Moduwe Wist config */
stwuct apm_mod_wist_obj {
	/* Moduwes wist cfg */
	uint32_t sub_gwaph_id;
	uint32_t containew_id;
	uint32_t num_moduwes;
	stwuct apm_moduwe_obj mod_cfg[];
} __packed;

#define APM_MOD_WIST_OBJ_PSIZE(p, n) stwuct_size(p, mod_cfg, n)

stwuct apm_moduwe_wist_pawams {
	stwuct apm_moduwe_pawam_data pawam_data;
	uint32_t num_moduwes_wist;
	/* Moduwe wist config awway */
	stwuct apm_mod_wist_obj mod_wist_obj[];
} __packed;


/* Moduwe Pwopewties */
stwuct apm_mod_pwop_obj {
	u32 instance_id;
	u32 num_pwops;
	stwuct apm_pwop_data pwop_data_1;
	stwuct apm_moduwe_pwop_id_powt_info pwop_id_powt;
} __packed;

stwuct apm_pwop_wist_pawams {
	stwuct apm_moduwe_pawam_data pawam_data;
	u32 num_moduwes_pwop_cfg;
	stwuct apm_mod_pwop_obj mod_pwop_obj[];

} __packed;

#define APM_MOD_PWOP_PSIZE(p, n) AWIGN(stwuct_size(p, mod_pwop_obj, n), 8)

/* Moduwe Connections */
stwuct apm_mod_conn_wist_pawams {
	stwuct apm_moduwe_pawam_data pawam_data;
	u32 num_connections;
	stwuct apm_moduwe_conn_obj conn_obj[];

} __packed;

#define APM_MOD_CONN_PSIZE(p, n) AWIGN(stwuct_size(p, conn_obj, n), 8)

stwuct apm_gwaph_open_pawams {
	stwuct apm_cmd_headew *cmd_headew;
	stwuct apm_sub_gwaph_pawams *sg_data;
	stwuct apm_containew_pawams *cont_data;
	stwuct apm_moduwe_wist_pawams *mod_wist_data;
	stwuct apm_pwop_wist_pawams *mod_pwop_data;
	stwuct apm_mod_conn_wist_pawams *mod_conn_wist_data;
} __packed;

stwuct apm_pcm_moduwe_media_fmt_cmd {
	stwuct apm_moduwe_pawam_data pawam_data;
	stwuct pawam_id_pcm_output_fowmat_cfg headew;
	stwuct paywoad_pcm_output_fowmat_cfg media_cfg;
} __packed;

stwuct apm_wd_shmem_moduwe_config_cmd {
	stwuct apm_moduwe_pawam_data pawam_data;
	stwuct pawam_id_wd_sh_mem_cfg cfg;
} __packed;

stwuct apm_sh_moduwe_media_fmt_cmd {
	stwuct media_fowmat headew;
	stwuct paywoad_media_fmt_pcm cfg;
} __packed;

#define APM_SHMEM_FMT_CFG_PSIZE(ch) AWIGN( \
				sizeof(stwuct apm_sh_moduwe_media_fmt_cmd) + \
				ch * sizeof(uint8_t), 8)

/* num of channews as awgument */
#define APM_PCM_MODUWE_FMT_CMD_PSIZE(ch) AWIGN( \
				sizeof(stwuct apm_pcm_moduwe_media_fmt_cmd) + \
				ch * sizeof(uint8_t), 8)

#define APM_PCM_OUT_FMT_CFG_PSIZE(p, n) AWIGN(stwuct_size(p, channew_mapping, n), 4)

stwuct apm_i2s_moduwe_intf_cfg {
	stwuct apm_moduwe_pawam_data pawam_data;
	stwuct pawam_id_i2s_intf_cfg cfg;
} __packed;

#define APM_I2S_INTF_CFG_PSIZE AWIGN(sizeof(stwuct apm_i2s_moduwe_intf_cfg), 8)

stwuct apm_moduwe_hw_ep_mf_cfg {
	stwuct apm_moduwe_pawam_data pawam_data;
	stwuct pawam_id_hw_ep_mf mf;
} __packed;

#define APM_HW_EP_CFG_PSIZE AWIGN(sizeof(stwuct apm_moduwe_hw_ep_mf_cfg), 8)

#define APM_MFC_CFG_PSIZE(p, n) AWIGN(stwuct_size(p, channew_mapping, n), 4)

stwuct apm_moduwe_fwame_size_factow_cfg {
	stwuct apm_moduwe_pawam_data pawam_data;
	uint32_t fwame_size_factow;
} __packed;

#define APM_FS_CFG_PSIZE AWIGN(sizeof(stwuct apm_moduwe_fwame_size_factow_cfg), 8)

stwuct apm_moduwe_hw_ep_powew_mode_cfg {
	stwuct apm_moduwe_pawam_data pawam_data;
	stwuct pawam_id_hw_ep_powew_mode_cfg powew_mode;
} __packed;

#define APM_HW_EP_PMODE_CFG_PSIZE AWIGN(sizeof(stwuct apm_moduwe_hw_ep_powew_mode_cfg),	8)

stwuct apm_moduwe_hw_ep_dma_data_awign_cfg {
	stwuct apm_moduwe_pawam_data pawam_data;
	stwuct pawam_id_hw_ep_dma_data_awign awign;
} __packed;

#define APM_HW_EP_DAWIGN_CFG_PSIZE AWIGN(sizeof(stwuct apm_moduwe_hw_ep_dma_data_awign_cfg), 8)

stwuct apm_gain_moduwe_cfg {
	stwuct apm_moduwe_pawam_data pawam_data;
	stwuct pawam_id_gain_cfg gain_cfg;
} __packed;

#define APM_GAIN_CFG_PSIZE AWIGN(sizeof(stwuct apm_gain_moduwe_cfg), 8)

stwuct apm_codec_dma_moduwe_intf_cfg {
	stwuct apm_moduwe_pawam_data pawam_data;
	stwuct pawam_id_codec_dma_intf_cfg cfg;
} __packed;

#define APM_CDMA_INTF_CFG_PSIZE AWIGN(sizeof(stwuct apm_codec_dma_moduwe_intf_cfg), 8)

stwuct apm_dispway_powt_moduwe_intf_cfg {
	stwuct apm_moduwe_pawam_data pawam_data;
	stwuct pawam_id_dispway_powt_intf_cfg cfg;
} __packed;
#define APM_DP_INTF_CFG_PSIZE AWIGN(sizeof(stwuct apm_dispway_powt_moduwe_intf_cfg), 8)

static void *__audioweach_awwoc_pkt(int paywoad_size, uint32_t opcode, uint32_t token,
				    uint32_t swc_powt, uint32_t dest_powt, boow has_cmd_hdw)
{
	stwuct gpw_pkt *pkt;
	void *p;
	int pkt_size = GPW_HDW_SIZE + paywoad_size;

	if (has_cmd_hdw)
		pkt_size += APM_CMD_HDW_SIZE;

	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn EWW_PTW(-ENOMEM);

	pkt = p;
	pkt->hdw.vewsion = GPW_PKT_VEW;
	pkt->hdw.hdw_size = GPW_PKT_HEADEW_WOWD_SIZE;
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.dest_powt = dest_powt;
	pkt->hdw.swc_powt = swc_powt;

	pkt->hdw.dest_domain = GPW_DOMAIN_ID_ADSP;
	pkt->hdw.swc_domain = GPW_DOMAIN_ID_APPS;
	pkt->hdw.token = token;
	pkt->hdw.opcode = opcode;

	if (has_cmd_hdw) {
		stwuct apm_cmd_headew *cmd_headew;

		p = p + GPW_HDW_SIZE;
		cmd_headew = p;
		cmd_headew->paywoad_size = paywoad_size;
	}

	wetuwn pkt;
}

void *audioweach_awwoc_pkt(int paywoad_size, uint32_t opcode, uint32_t token,
			   uint32_t swc_powt, uint32_t dest_powt)
{
	wetuwn __audioweach_awwoc_pkt(paywoad_size, opcode, token, swc_powt, dest_powt, fawse);
}
EXPOWT_SYMBOW_GPW(audioweach_awwoc_pkt);

void *audioweach_awwoc_apm_pkt(int pkt_size, uint32_t opcode, uint32_t token, uint32_t swc_powt)
{
	wetuwn __audioweach_awwoc_pkt(pkt_size, opcode, token, swc_powt, APM_MODUWE_INSTANCE_ID,
				      fawse);
}
EXPOWT_SYMBOW_GPW(audioweach_awwoc_apm_pkt);

void *audioweach_awwoc_cmd_pkt(int paywoad_size, uint32_t opcode, uint32_t token,
			       uint32_t swc_powt, uint32_t dest_powt)
{
	wetuwn __audioweach_awwoc_pkt(paywoad_size, opcode, token, swc_powt, dest_powt, twue);
}
EXPOWT_SYMBOW_GPW(audioweach_awwoc_cmd_pkt);

void *audioweach_awwoc_apm_cmd_pkt(int pkt_size, uint32_t opcode, uint32_t token)
{
	wetuwn __audioweach_awwoc_pkt(pkt_size, opcode, token, GPW_APM_MODUWE_IID,
				       APM_MODUWE_INSTANCE_ID, twue);
}
EXPOWT_SYMBOW_GPW(audioweach_awwoc_apm_cmd_pkt);

static void audioweach_set_channew_mapping(u8 *ch_map, int num_channews)
{
	if (num_channews == 1) {
		ch_map[0] =  PCM_CHANNEW_FW;
	} ewse if (num_channews == 2) {
		ch_map[0] =  PCM_CHANNEW_FW;
		ch_map[1] =  PCM_CHANNEW_FW;
	} ewse if (num_channews == 4) {
		ch_map[0] =  PCM_CHANNEW_FW;
		ch_map[1] =  PCM_CHANNEW_FW;
		ch_map[2] =  PCM_CHANNEW_WS;
		ch_map[3] =  PCM_CHANNEW_WS;
	}
}

static void apm_popuwate_containew_config(stwuct apm_containew_obj *cfg,
					  stwuct audioweach_containew *cont)
{

	/* Containew Config */
	cfg->containew_cfg.containew_id = cont->containew_id;
	cfg->containew_cfg.num_pwop = 4;

	/* Capabiwity wist */
	cfg->cap_data.pwop_id = APM_CONTAINEW_PWOP_ID_CAPABIWITY_WIST;
	cfg->cap_data.pwop_size = APM_CONTAINEW_PWOP_ID_CAPABIWITY_SIZE;
	cfg->num_capabiwity_id = 1;
	cfg->capabiwity_id = cont->capabiwity_id;

	/* Gwaph Position */
	cfg->pos_data.pwop_id = APM_CONTAINEW_PWOP_ID_GWAPH_POS;
	cfg->pos_data.pwop_size = sizeof(stwuct apm_cont_pwop_id_gwaph_pos);
	cfg->pos.gwaph_pos = cont->gwaph_pos;

	/* Stack size */
	cfg->stack_data.pwop_id = APM_CONTAINEW_PWOP_ID_STACK_SIZE;
	cfg->stack_data.pwop_size = sizeof(stwuct apm_cont_pwop_id_stack_size);
	cfg->stack.stack_size = cont->stack_size;

	/* Pwoc domain */
	cfg->domain_data.pwop_id = APM_CONTAINEW_PWOP_ID_PWOC_DOMAIN;
	cfg->domain_data.pwop_size = sizeof(stwuct apm_cont_pwop_id_domain);
	cfg->domain.pwoc_domain = cont->pwoc_domain;
}

static void apm_popuwate_sub_gwaph_config(stwuct apm_sub_gwaph_data *cfg,
					  stwuct audioweach_sub_gwaph *sg)
{
	cfg->sub_gwaph_cfg.sub_gwaph_id = sg->sub_gwaph_id;
	cfg->sub_gwaph_cfg.num_sub_gwaph_pwop = APM_SUB_GWAPH_CFG_NPWOP;

	/* Pewf Mode */
	cfg->pewf_data.pwop_id = APM_SUB_GWAPH_PWOP_ID_PEWF_MODE;
	cfg->pewf_data.pwop_size = APM_SG_PWOP_ID_PEWF_MODE_SIZE;
	cfg->pewf.pewf_mode = sg->pewf_mode;

	/* Diwection */
	cfg->diw_data.pwop_id = APM_SUB_GWAPH_PWOP_ID_DIWECTION;
	cfg->diw_data.pwop_size = APM_SG_PWOP_ID_DIW_SIZE;
	cfg->diw.diwection = sg->diwection;

	/* Scenawio ID */
	cfg->sid_data.pwop_id = APM_SUB_GWAPH_PWOP_ID_SCENAWIO_ID;
	cfg->sid_data.pwop_size = APM_SG_PWOP_ID_SID_SIZE;
	cfg->sid.scenawio_id = sg->scenawio_id;
}

static void apm_popuwate_moduwe_pwop_obj(stwuct apm_mod_pwop_obj *obj,
					 stwuct audioweach_moduwe *moduwe)
{

	obj->instance_id = moduwe->instance_id;
	obj->num_pwops = 1;
	obj->pwop_data_1.pwop_id = APM_MODUWE_PWOP_ID_POWT_INFO;
	obj->pwop_data_1.pwop_size = APM_MODUWE_PWOP_ID_POWT_INFO_SZ;
	obj->pwop_id_powt.max_ip_powt = moduwe->max_ip_powt;
	obj->pwop_id_powt.max_op_powt = moduwe->max_op_powt;
}

static void apm_popuwate_moduwe_wist_obj(stwuct apm_mod_wist_obj *obj,
					 stwuct audioweach_containew *containew,
					 int sub_gwaph_id)
{
	stwuct audioweach_moduwe *moduwe;
	int i;

	obj->sub_gwaph_id = sub_gwaph_id;
	obj->containew_id = containew->containew_id;
	obj->num_moduwes = containew->num_moduwes;
	i = 0;
	wist_fow_each_entwy(moduwe, &containew->moduwes_wist, node) {
		obj->mod_cfg[i].moduwe_id = moduwe->moduwe_id;
		obj->mod_cfg[i].instance_id = moduwe->instance_id;
		i++;
	}
}

static void audioweach_popuwate_gwaph(stwuct q6apm *apm, stwuct audioweach_gwaph_info *info,
				      stwuct apm_gwaph_open_pawams *open,
				      stwuct wist_head *sg_wist,
				      int num_sub_gwaphs)
{
	stwuct apm_mod_conn_wist_pawams *mc_data = open->mod_conn_wist_data;
	stwuct apm_moduwe_wist_pawams *mw_data = open->mod_wist_data;
	stwuct apm_pwop_wist_pawams *mp_data = open->mod_pwop_data;
	stwuct apm_containew_pawams *c_data = open->cont_data;
	stwuct apm_sub_gwaph_pawams *sg_data = open->sg_data;
	int ncontainew = 0, nmoduwe = 0, nconn = 0;
	stwuct apm_mod_pwop_obj *moduwe_pwop_obj;
	stwuct audioweach_containew *containew;
	stwuct apm_moduwe_conn_obj *conn_obj;
	stwuct audioweach_moduwe *moduwe;
	stwuct audioweach_sub_gwaph *sg;
	stwuct apm_containew_obj *cobj;
	stwuct apm_mod_wist_obj *mwobj;
	int i = 0;

	mwobj = &mw_data->mod_wist_obj[0];


	if (info->dst_mod_inst_id && info->swc_mod_inst_id) {
		conn_obj = &mc_data->conn_obj[nconn];
		conn_obj->swc_mod_inst_id = info->swc_mod_inst_id;
		conn_obj->swc_mod_op_powt_id = info->swc_mod_op_powt_id;
		conn_obj->dst_mod_inst_id = info->dst_mod_inst_id;
		conn_obj->dst_mod_ip_powt_id = info->dst_mod_ip_powt_id;
		nconn++;
	}

	wist_fow_each_entwy(sg, sg_wist, node) {
		stwuct apm_sub_gwaph_data *sg_cfg = &sg_data->sg_cfg[i++];

		apm_popuwate_sub_gwaph_config(sg_cfg, sg);

		wist_fow_each_entwy(containew, &sg->containew_wist, node) {
			cobj = &c_data->cont_obj[ncontainew];

			apm_popuwate_containew_config(cobj, containew);
			apm_popuwate_moduwe_wist_obj(mwobj, containew, sg->sub_gwaph_id);

			wist_fow_each_entwy(moduwe, &containew->moduwes_wist, node) {
				int pn;

				moduwe_pwop_obj = &mp_data->mod_pwop_obj[nmoduwe++];
				apm_popuwate_moduwe_pwop_obj(moduwe_pwop_obj, moduwe);

				if (!moduwe->max_op_powt)
					continue;

				fow (pn = 0; pn < moduwe->max_op_powt; pn++) {
					if (moduwe->dst_mod_inst_id[pn]) {
						conn_obj = &mc_data->conn_obj[nconn];
						conn_obj->swc_mod_inst_id = moduwe->instance_id;
						conn_obj->swc_mod_op_powt_id =
								moduwe->swc_mod_op_powt_id[pn];
						conn_obj->dst_mod_inst_id =
								moduwe->dst_mod_inst_id[pn];
						conn_obj->dst_mod_ip_powt_id =
								moduwe->dst_mod_ip_powt_id[pn];
						nconn++;
					}
				}
			}
			mwobj = (void *) mwobj + APM_MOD_WIST_OBJ_PSIZE(mwobj,
									containew->num_moduwes);

			ncontainew++;
		}
	}
}

void *audioweach_awwoc_gwaph_pkt(stwuct q6apm *apm, stwuct audioweach_gwaph_info *info)
{
	int paywoad_size, sg_sz, cont_sz, mw_sz, mp_sz, mc_sz;
	stwuct apm_moduwe_pawam_data  *pawam_data;
	stwuct apm_containew_pawams *cont_pawams;
	stwuct audioweach_containew *containew;
	stwuct apm_sub_gwaph_pawams *sg_pawams;
	stwuct apm_mod_conn_wist_pawams *mcon;
	stwuct apm_gwaph_open_pawams pawams;
	stwuct apm_pwop_wist_pawams *mpwop;
	stwuct audioweach_moduwe *moduwe;
	stwuct audioweach_sub_gwaph *sgs;
	stwuct apm_mod_wist_obj *mwobj;
	stwuct wist_head *sg_wist;
	int num_connections = 0;
	int num_containews = 0;
	int num_sub_gwaphs = 0;
	int num_moduwes = 0;
	int num_moduwes_wist;
	stwuct gpw_pkt *pkt;
	void *p;

	sg_wist = &info->sg_wist;
	mw_sz = 0;

	/* add FE-BE connections */
	if (info->dst_mod_inst_id && info->swc_mod_inst_id)
		num_connections++;

	wist_fow_each_entwy(sgs, sg_wist, node) {
		num_sub_gwaphs++;
		wist_fow_each_entwy(containew, &sgs->containew_wist, node) {
			num_containews++;
			num_moduwes += containew->num_moduwes;
			mw_sz = mw_sz + sizeof(stwuct apm_moduwe_wist_pawams) +
				APM_MOD_WIST_OBJ_PSIZE(mwobj, containew->num_moduwes);

			wist_fow_each_entwy(moduwe, &containew->moduwes_wist, node) {
				num_connections += moduwe->num_connections;
			}
		}
	}

	num_moduwes_wist = num_containews;
	sg_sz = APM_SUB_GWAPH_PSIZE(sg_pawams, num_sub_gwaphs);
	cont_sz = APM_CONTAINEW_PSIZE(cont_pawams, num_containews);

	mw_sz = AWIGN(mw_sz, 8);

	mp_sz = APM_MOD_PWOP_PSIZE(mpwop, num_moduwes);
	mc_sz =	APM_MOD_CONN_PSIZE(mcon, num_connections);

	paywoad_size = sg_sz + cont_sz + mw_sz + mp_sz + mc_sz;
	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_GWAPH_OPEN, 0);
	if (IS_EWW(pkt))
		wetuwn pkt;

	p = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	/* SubGwaph */
	pawams.sg_data = p;
	pawam_data = &pawams.sg_data->pawam_data;
	pawam_data->moduwe_instance_id = APM_MODUWE_INSTANCE_ID;
	pawam_data->pawam_id = APM_PAWAM_ID_SUB_GWAPH_CONFIG;
	pawam_data->pawam_size = sg_sz - APM_MODUWE_PAWAM_DATA_SIZE;
	pawams.sg_data->num_sub_gwaphs = num_sub_gwaphs;
	p += sg_sz;

	/* Containew */
	pawams.cont_data = p;
	pawam_data = &pawams.cont_data->pawam_data;
	pawam_data->moduwe_instance_id = APM_MODUWE_INSTANCE_ID;
	pawam_data->pawam_id = APM_PAWAM_ID_CONTAINEW_CONFIG;
	pawam_data->pawam_size = cont_sz - APM_MODUWE_PAWAM_DATA_SIZE;
	pawams.cont_data->num_containews = num_containews;
	p += cont_sz;

	/* Moduwe Wist*/
	pawams.mod_wist_data = p;
	pawam_data = &pawams.mod_wist_data->pawam_data;
	pawam_data->moduwe_instance_id = APM_MODUWE_INSTANCE_ID;
	pawam_data->pawam_id = APM_PAWAM_ID_MODUWE_WIST;
	pawam_data->pawam_size = mw_sz - APM_MODUWE_PAWAM_DATA_SIZE;
	pawams.mod_wist_data->num_moduwes_wist = num_moduwes_wist;
	p += mw_sz;

	/* Moduwe Pwopewties */
	pawams.mod_pwop_data = p;
	pawam_data = &pawams.mod_pwop_data->pawam_data;
	pawam_data->moduwe_instance_id = APM_MODUWE_INSTANCE_ID;
	pawam_data->pawam_id = APM_PAWAM_ID_MODUWE_PWOP;
	pawam_data->pawam_size = mp_sz - APM_MODUWE_PAWAM_DATA_SIZE;
	pawams.mod_pwop_data->num_moduwes_pwop_cfg = num_moduwes;
	p += mp_sz;

	/* Moduwe Connections */
	pawams.mod_conn_wist_data = p;
	pawam_data = &pawams.mod_conn_wist_data->pawam_data;
	pawam_data->moduwe_instance_id = APM_MODUWE_INSTANCE_ID;
	pawam_data->pawam_id = APM_PAWAM_ID_MODUWE_CONN;
	pawam_data->pawam_size = mc_sz - APM_MODUWE_PAWAM_DATA_SIZE;
	pawams.mod_conn_wist_data->num_connections = num_connections;
	p += mc_sz;

	audioweach_popuwate_gwaph(apm, info, &pawams, sg_wist, num_sub_gwaphs);

	wetuwn pkt;
}
EXPOWT_SYMBOW_GPW(audioweach_awwoc_gwaph_pkt);

int audioweach_send_cmd_sync(stwuct device *dev, gpw_device_t *gdev,
			     stwuct gpw_ibasic_wsp_wesuwt_t *wesuwt, stwuct mutex *cmd_wock,
			     gpw_powt_t *powt, wait_queue_head_t *cmd_wait,
			     stwuct gpw_pkt *pkt, uint32_t wsp_opcode)
{

	stwuct gpw_hdw *hdw = &pkt->hdw;
	int wc;

	mutex_wock(cmd_wock);
	wesuwt->opcode = 0;
	wesuwt->status = 0;

	if (powt)
		wc = gpw_send_powt_pkt(powt, pkt);
	ewse if (gdev)
		wc = gpw_send_pkt(gdev, pkt);
	ewse
		wc = -EINVAW;

	if (wc < 0)
		goto eww;

	if (wsp_opcode)
		wc = wait_event_timeout(*cmd_wait, (wesuwt->opcode == hdw->opcode) ||
					(wesuwt->opcode == wsp_opcode),	5 * HZ);
	ewse
		wc = wait_event_timeout(*cmd_wait, (wesuwt->opcode == hdw->opcode), 5 * HZ);

	if (!wc) {
		dev_eww(dev, "CMD timeout fow [%x] opcode\n", hdw->opcode);
		wc = -ETIMEDOUT;
	} ewse if (wesuwt->status > 0) {
		dev_eww(dev, "DSP wetuwned ewwow[%x] %x\n", hdw->opcode, wesuwt->status);
		wc = -EINVAW;
	} ewse {
		/* DSP successfuwwy finished the command */
		wc = 0;
	}

eww:
	mutex_unwock(cmd_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(audioweach_send_cmd_sync);

int audioweach_gwaph_send_cmd_sync(stwuct q6apm_gwaph *gwaph, stwuct gpw_pkt *pkt,
				   uint32_t wsp_opcode)
{

	wetuwn audioweach_send_cmd_sync(gwaph->dev, NUWW,  &gwaph->wesuwt, &gwaph->wock,
					gwaph->powt, &gwaph->cmd_wait, pkt, wsp_opcode);
}
EXPOWT_SYMBOW_GPW(audioweach_gwaph_send_cmd_sync);

static int audioweach_dispway_powt_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
						    stwuct audioweach_moduwe *moduwe,
						    stwuct audioweach_moduwe_config *cfg)
{
	stwuct apm_dispway_powt_moduwe_intf_cfg *intf_cfg;
	stwuct apm_moduwe_fwame_size_factow_cfg *fs_cfg;
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct apm_moduwe_hw_ep_mf_cfg *hw_cfg;
	int ic_sz, ep_sz, fs_sz, dw_sz;
	int wc, paywoad_size;
	stwuct gpw_pkt *pkt;
	void *p;

	ic_sz = APM_DP_INTF_CFG_PSIZE;
	ep_sz = APM_HW_EP_CFG_PSIZE;
	fs_sz = APM_FS_CFG_PSIZE;
	dw_sz = 0;

	paywoad_size = ic_sz + ep_sz + fs_sz + dw_sz;

	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	p = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	hw_cfg = p;
	pawam_data = &hw_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_HW_EP_MF_CFG;
	pawam_data->pawam_size = ep_sz - APM_MODUWE_PAWAM_DATA_SIZE;

	hw_cfg->mf.sampwe_wate = cfg->sampwe_wate;
	hw_cfg->mf.bit_width = cfg->bit_width;
	hw_cfg->mf.num_channews = cfg->num_channews;
	hw_cfg->mf.data_fowmat = moduwe->data_fowmat;
	p += ep_sz;

	fs_cfg = p;
	pawam_data = &fs_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_HW_EP_FWAME_SIZE_FACTOW;
	pawam_data->pawam_size = fs_sz - APM_MODUWE_PAWAM_DATA_SIZE;
	fs_cfg->fwame_size_factow = 1;
	p += fs_sz;

	intf_cfg = p;
	pawam_data = &intf_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_DISPWAY_POWT_INTF_CFG;
	pawam_data->pawam_size = ic_sz - APM_MODUWE_PAWAM_DATA_SIZE;

	intf_cfg->cfg.channew_awwocation = cfg->channew_awwocation;
	intf_cfg->cfg.mst_idx = 0;
	intf_cfg->cfg.dptx_idx = cfg->dp_idx;

	wc = q6apm_send_cmd_sync(gwaph->apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}

/* WPASS Codec DMA powt Moduwe Media Fowmat Setup */
static int audioweach_codec_dma_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
						 stwuct audioweach_moduwe *moduwe,
						 stwuct audioweach_moduwe_config *cfg)
{
	stwuct apm_codec_dma_moduwe_intf_cfg *intf_cfg;
	stwuct apm_moduwe_fwame_size_factow_cfg *fs_cfg;
	stwuct apm_moduwe_hw_ep_powew_mode_cfg *pm_cfg;
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct apm_moduwe_hw_ep_mf_cfg *hw_cfg;
	int ic_sz, ep_sz, fs_sz, pm_sz, dw_sz;
	int wc, paywoad_size;
	stwuct gpw_pkt *pkt;
	void *p;

	ic_sz = APM_CDMA_INTF_CFG_PSIZE;
	ep_sz = APM_HW_EP_CFG_PSIZE;
	fs_sz = APM_FS_CFG_PSIZE;
	pm_sz = APM_HW_EP_PMODE_CFG_PSIZE;
	dw_sz = 0;

	paywoad_size = ic_sz + ep_sz + fs_sz + pm_sz + dw_sz;

	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	p = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	hw_cfg = p;
	pawam_data = &hw_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_HW_EP_MF_CFG;
	pawam_data->pawam_size = ep_sz - APM_MODUWE_PAWAM_DATA_SIZE;

	hw_cfg->mf.sampwe_wate = cfg->sampwe_wate;
	hw_cfg->mf.bit_width = cfg->bit_width;
	hw_cfg->mf.num_channews = cfg->num_channews;
	hw_cfg->mf.data_fowmat = moduwe->data_fowmat;
	p += ep_sz;

	fs_cfg = p;
	pawam_data = &fs_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_HW_EP_FWAME_SIZE_FACTOW;
	pawam_data->pawam_size = fs_sz - APM_MODUWE_PAWAM_DATA_SIZE;
	fs_cfg->fwame_size_factow = 1;
	p += fs_sz;

	intf_cfg = p;
	pawam_data = &intf_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_CODEC_DMA_INTF_CFG;
	pawam_data->pawam_size = ic_sz - APM_MODUWE_PAWAM_DATA_SIZE;

	intf_cfg->cfg.wpaif_type = moduwe->hw_intewface_type;
	intf_cfg->cfg.intf_index = moduwe->hw_intewface_idx;
	intf_cfg->cfg.active_channews_mask = (1 << cfg->num_channews) - 1;
	p += ic_sz;

	pm_cfg = p;
	pawam_data = &pm_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_HW_EP_POWEW_MODE_CFG;
	pawam_data->pawam_size = pm_sz - APM_MODUWE_PAWAM_DATA_SIZE;
	pm_cfg->powew_mode.powew_mode = 0;

	wc = q6apm_send_cmd_sync(gwaph->apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}

int audioweach_send_u32_pawam(stwuct q6apm_gwaph *gwaph, stwuct audioweach_moduwe *moduwe,
			      uint32_t pawam_id, uint32_t pawam_vaw)
{
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct gpw_pkt *pkt;
	uint32_t *pawam;
	int wc, paywoad_size;
	void *p;

	paywoad_size = sizeof(uint32_t) + APM_MODUWE_PAWAM_DATA_SIZE;
	p = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0);
	if (IS_EWW(p))
		wetuwn -ENOMEM;

	pkt = p;
	p = p + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = p;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = pawam_id;
	pawam_data->pawam_size = sizeof(uint32_t);

	p = p + APM_MODUWE_PAWAM_DATA_SIZE;
	pawam = p;
	*pawam = pawam_vaw;

	wc = q6apm_send_cmd_sync(gwaph->apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(audioweach_send_u32_pawam);

static int audioweach_saw_wimitew_enabwe(stwuct q6apm_gwaph *gwaph,
					 stwuct audioweach_moduwe *moduwe, boow enabwe)
{
	wetuwn audioweach_send_u32_pawam(gwaph, moduwe, PAWAM_ID_SAW_WIMITEW_ENABWE, enabwe);
}

static int audioweach_saw_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
					   stwuct audioweach_moduwe *moduwe,
					   stwuct audioweach_moduwe_config *cfg)
{
	wetuwn audioweach_send_u32_pawam(gwaph, moduwe, PAWAM_ID_SAW_OUTPUT_CFG,  cfg->bit_width);
}

static int audioweach_moduwe_enabwe(stwuct q6apm_gwaph *gwaph,
				    stwuct audioweach_moduwe *moduwe,
				    boow enabwe)
{
	wetuwn audioweach_send_u32_pawam(gwaph, moduwe, PAWAM_ID_MODUWE_ENABWE, enabwe);
}

static int audioweach_gapwess_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
					       stwuct audioweach_moduwe *moduwe,
					       stwuct audioweach_moduwe_config *cfg)
{
	wetuwn audioweach_send_u32_pawam(gwaph, moduwe, PAWAM_ID_EAWWY_EOS_DEWAY,
					 EAWWY_EOS_DEWAY_MS);
}

static int audioweach_mfc_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
					   stwuct audioweach_moduwe *moduwe,
					   stwuct audioweach_moduwe_config *cfg)
{
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct pawam_id_mfc_media_fowmat *media_fowmat;
	uint32_t num_channews = cfg->num_channews;
	int paywoad_size;
	stwuct gpw_pkt *pkt;
	int wc;
	void *p;

	paywoad_size = APM_MFC_CFG_PSIZE(media_fowmat, num_channews) +
		APM_MODUWE_PAWAM_DATA_SIZE;

	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	p = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = p;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_MFC_OUTPUT_MEDIA_FOWMAT;
	pawam_data->pawam_size = APM_MFC_CFG_PSIZE(media_fowmat, num_channews);
	p = p + APM_MODUWE_PAWAM_DATA_SIZE;
	media_fowmat = p;

	media_fowmat->sampwe_wate = cfg->sampwe_wate;
	media_fowmat->bit_width = cfg->bit_width;
	media_fowmat->num_channews = cfg->num_channews;

	if (num_channews == 1) {
		media_fowmat->channew_mapping[0] = PCM_CHANNEW_FW;
	} ewse if (num_channews == 2) {
		media_fowmat->channew_mapping[0] = PCM_CHANNEW_FW;
		media_fowmat->channew_mapping[1] = PCM_CHANNEW_FW;
	} ewse if (num_channews == 4) {
		media_fowmat->channew_mapping[0] = PCM_CHANNEW_FW;
		media_fowmat->channew_mapping[1] = PCM_CHANNEW_FW;
		media_fowmat->channew_mapping[2] = PCM_CHANNEW_WS;
		media_fowmat->channew_mapping[3] = PCM_CHANNEW_WS;
	}

	wc = q6apm_send_cmd_sync(gwaph->apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}

static int audioweach_set_compw_media_fowmat(stwuct media_fowmat *media_fmt_hdw,
					     void *p, stwuct audioweach_moduwe_config *mcfg)
{
	stwuct paywoad_media_fmt_aac_t *aac_cfg;
	stwuct paywoad_media_fmt_pcm *mp3_cfg;
	stwuct paywoad_media_fmt_fwac_t *fwac_cfg;

	switch (mcfg->fmt) {
	case SND_AUDIOCODEC_MP3:
		media_fmt_hdw->data_fowmat = DATA_FOWMAT_WAW_COMPWESSED;
		media_fmt_hdw->fmt_id = MEDIA_FMT_ID_MP3;
		media_fmt_hdw->paywoad_size = 0;
		p = p + sizeof(*media_fmt_hdw);
		mp3_cfg = p;
		mp3_cfg->sampwe_wate = mcfg->sampwe_wate;
		mp3_cfg->bit_width = mcfg->bit_width;
		mp3_cfg->awignment = PCM_WSB_AWIGNED;
		mp3_cfg->bits_pew_sampwe = mcfg->bit_width;
		mp3_cfg->q_factow = mcfg->bit_width - 1;
		mp3_cfg->endianness = PCM_WITTWE_ENDIAN;
		mp3_cfg->num_channews = mcfg->num_channews;

		audioweach_set_channew_mapping(mp3_cfg->channew_mapping,
					       mcfg->num_channews);
		bweak;
	case SND_AUDIOCODEC_AAC:
		media_fmt_hdw->data_fowmat = DATA_FOWMAT_WAW_COMPWESSED;
		media_fmt_hdw->fmt_id = MEDIA_FMT_ID_AAC;
		media_fmt_hdw->paywoad_size = sizeof(stwuct paywoad_media_fmt_aac_t);
		p = p + sizeof(*media_fmt_hdw);
		aac_cfg = p;
		aac_cfg->aac_fmt_fwag = 0;
		aac_cfg->audio_obj_type = 5;
		aac_cfg->num_channews = mcfg->num_channews;
		aac_cfg->totaw_size_of_PCE_bits = 0;
		aac_cfg->sampwe_wate = mcfg->sampwe_wate;
		bweak;
	case SND_AUDIOCODEC_FWAC:
		media_fmt_hdw->data_fowmat = DATA_FOWMAT_WAW_COMPWESSED;
		media_fmt_hdw->fmt_id = MEDIA_FMT_ID_FWAC;
		media_fmt_hdw->paywoad_size = sizeof(stwuct paywoad_media_fmt_fwac_t);
		p = p + sizeof(*media_fmt_hdw);
		fwac_cfg = p;
		fwac_cfg->sampwe_size = mcfg->codec.options.fwac_d.sampwe_size;
		fwac_cfg->num_channews = mcfg->num_channews;
		fwac_cfg->min_bwk_size = mcfg->codec.options.fwac_d.min_bwk_size;
		fwac_cfg->max_bwk_size = mcfg->codec.options.fwac_d.max_bwk_size;
		fwac_cfg->sampwe_wate = mcfg->sampwe_wate;
		fwac_cfg->min_fwame_size = mcfg->codec.options.fwac_d.min_fwame_size;
		fwac_cfg->max_fwame_size = mcfg->codec.options.fwac_d.max_fwame_size;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int audioweach_compw_set_pawam(stwuct q6apm_gwaph *gwaph, stwuct audioweach_moduwe_config *mcfg)
{
	stwuct media_fowmat *headew;
	stwuct gpw_pkt *pkt;
	int iid, paywoad_size, wc;
	void *p;

	paywoad_size = sizeof(stwuct apm_sh_moduwe_media_fmt_cmd);

	iid = q6apm_gwaph_get_wx_shmem_moduwe_iid(gwaph);
	pkt = audioweach_awwoc_cmd_pkt(paywoad_size, DATA_CMD_WW_SH_MEM_EP_MEDIA_FOWMAT,
			0, gwaph->powt->id, iid);

	if (IS_EWW(pkt))
		wetuwn -ENOMEM;

	p = (void *)pkt + GPW_HDW_SIZE;
	headew = p;
	wc = audioweach_set_compw_media_fowmat(headew, p, mcfg);
	if (wc) {
		kfwee(pkt);
		wetuwn wc;
	}

	wc = gpw_send_powt_pkt(gwaph->powt, pkt);
	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(audioweach_compw_set_pawam);

static int audioweach_i2s_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
					   stwuct audioweach_moduwe *moduwe,
					   stwuct audioweach_moduwe_config *cfg)
{
	stwuct apm_moduwe_fwame_size_factow_cfg *fs_cfg;
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct apm_i2s_moduwe_intf_cfg *intf_cfg;
	stwuct apm_moduwe_hw_ep_mf_cfg *hw_cfg;
	int ic_sz, ep_sz, fs_sz;
	int wc, paywoad_size;
	stwuct gpw_pkt *pkt;
	void *p;

	ic_sz = APM_I2S_INTF_CFG_PSIZE;
	ep_sz = APM_HW_EP_CFG_PSIZE;
	fs_sz = APM_FS_CFG_PSIZE;

	paywoad_size = ic_sz + ep_sz + fs_sz;

	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	p = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;
	intf_cfg = p;

	pawam_data = &intf_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_I2S_INTF_CFG;
	pawam_data->pawam_size = ic_sz - APM_MODUWE_PAWAM_DATA_SIZE;

	intf_cfg->cfg.intf_idx = moduwe->hw_intewface_idx;
	intf_cfg->cfg.sd_wine_idx = moduwe->sd_wine_idx;

	switch (cfg->fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		intf_cfg->cfg.ws_swc = CONFIG_I2S_WS_SWC_INTEWNAW;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		/* CPU is swave */
		intf_cfg->cfg.ws_swc = CONFIG_I2S_WS_SWC_EXTEWNAW;
		bweak;
	defauwt:
		bweak;
	}

	p += ic_sz;
	hw_cfg = p;
	pawam_data = &hw_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_HW_EP_MF_CFG;
	pawam_data->pawam_size = ep_sz - APM_MODUWE_PAWAM_DATA_SIZE;

	hw_cfg->mf.sampwe_wate = cfg->sampwe_wate;
	hw_cfg->mf.bit_width = cfg->bit_width;
	hw_cfg->mf.num_channews = cfg->num_channews;
	hw_cfg->mf.data_fowmat = moduwe->data_fowmat;

	p += ep_sz;
	fs_cfg = p;
	pawam_data = &fs_cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_HW_EP_FWAME_SIZE_FACTOW;
	pawam_data->pawam_size = fs_sz - APM_MODUWE_PAWAM_DATA_SIZE;
	fs_cfg->fwame_size_factow = 1;

	wc = q6apm_send_cmd_sync(gwaph->apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}

static int audioweach_wogging_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
					       stwuct audioweach_moduwe *moduwe)
{
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct data_wogging_config *cfg;
	int wc, paywoad_size;
	stwuct gpw_pkt *pkt;
	void *p;

	paywoad_size = sizeof(*cfg) + APM_MODUWE_PAWAM_DATA_SIZE;
	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	p = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = p;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_DATA_WOGGING_CONFIG;
	pawam_data->pawam_size = paywoad_size - APM_MODUWE_PAWAM_DATA_SIZE;

	p = p + APM_MODUWE_PAWAM_DATA_SIZE;
	cfg = p;
	cfg->wog_code = moduwe->wog_code;
	cfg->wog_tap_point_id = moduwe->wog_tap_point_id;
	cfg->mode = moduwe->wog_mode;

	wc = q6apm_send_cmd_sync(gwaph->apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}

static int audioweach_pcm_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
					   stwuct audioweach_moduwe *moduwe,
					   stwuct audioweach_moduwe_config *mcfg)
{
	stwuct paywoad_pcm_output_fowmat_cfg *media_cfg;
	uint32_t num_channews = mcfg->num_channews;
	stwuct apm_pcm_moduwe_media_fmt_cmd *cfg;
	stwuct apm_moduwe_pawam_data *pawam_data;
	int wc, paywoad_size;
	stwuct gpw_pkt *pkt;

	if (num_channews > 4) {
		dev_eww(gwaph->dev, "Ewwow: Invawid channews (%d)!\n", num_channews);
		wetuwn -EINVAW;
	}

	paywoad_size = APM_PCM_MODUWE_FMT_CMD_PSIZE(num_channews);

	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	cfg = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = &cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_PCM_OUTPUT_FOWMAT_CFG;
	pawam_data->pawam_size = paywoad_size - APM_MODUWE_PAWAM_DATA_SIZE;

	cfg->headew.data_fowmat = DATA_FOWMAT_FIXED_POINT;
	cfg->headew.fmt_id = MEDIA_FMT_ID_PCM;
	cfg->headew.paywoad_size = APM_PCM_OUT_FMT_CFG_PSIZE(media_cfg, num_channews);

	media_cfg = &cfg->media_cfg;
	media_cfg->awignment = PCM_WSB_AWIGNED;
	media_cfg->bit_width = mcfg->bit_width;
	media_cfg->endianness = PCM_WITTWE_ENDIAN;
	media_cfg->intewweaved = moduwe->intewweave_type;
	media_cfg->num_channews = mcfg->num_channews;
	media_cfg->q_factow = mcfg->bit_width - 1;
	media_cfg->bits_pew_sampwe = mcfg->bit_width;

	audioweach_set_channew_mapping(media_cfg->channew_mapping,
				       num_channews);

	wc = q6apm_send_cmd_sync(gwaph->apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}

static int audioweach_shmem_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
					     stwuct audioweach_moduwe *moduwe,
					     stwuct audioweach_moduwe_config *mcfg)
{
	uint32_t num_channews = mcfg->num_channews;
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct paywoad_media_fmt_pcm *cfg;
	stwuct media_fowmat *headew;
	int wc, paywoad_size;
	stwuct gpw_pkt *pkt;
	void *p;

	if (num_channews > 4) {
		dev_eww(gwaph->dev, "Ewwow: Invawid channews (%d)!\n", num_channews);
		wetuwn -EINVAW;
	}

	paywoad_size = APM_SHMEM_FMT_CFG_PSIZE(num_channews) + APM_MODUWE_PAWAM_DATA_SIZE;

	pkt = audioweach_awwoc_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0,
				     gwaph->powt->id, moduwe->instance_id);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	p = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = p;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_MEDIA_FOWMAT;
	pawam_data->pawam_size = paywoad_size - APM_MODUWE_PAWAM_DATA_SIZE;
	p = p + APM_MODUWE_PAWAM_DATA_SIZE;

	headew = p;
	if (mcfg->fmt == SND_AUDIOCODEC_PCM) {
		headew->data_fowmat = DATA_FOWMAT_FIXED_POINT;
		headew->fmt_id =  MEDIA_FMT_ID_PCM;
		headew->paywoad_size = paywoad_size - sizeof(*headew);

		p = p + sizeof(*headew);
		cfg = p;
		cfg->sampwe_wate = mcfg->sampwe_wate;
		cfg->bit_width = mcfg->bit_width;
		cfg->awignment = PCM_WSB_AWIGNED;
		cfg->bits_pew_sampwe = mcfg->bit_width;
		cfg->q_factow = mcfg->bit_width - 1;
		cfg->endianness = PCM_WITTWE_ENDIAN;
		cfg->num_channews = mcfg->num_channews;

		audioweach_set_channew_mapping(cfg->channew_mapping,
					       num_channews);
	} ewse {
		wc = audioweach_set_compw_media_fowmat(headew, p, mcfg);
		if (wc) {
			kfwee(pkt);
			wetuwn wc;
		}
	}

	wc = audioweach_gwaph_send_cmd_sync(gwaph, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}

int audioweach_gain_set_vow_ctww(stwuct q6apm *apm, stwuct audioweach_moduwe *moduwe, int vow)
{
	stwuct pawam_id_vow_ctww_mastew_gain *cfg;
	stwuct apm_moduwe_pawam_data *pawam_data;
	int wc, paywoad_size;
	stwuct gpw_pkt *pkt;
	void *p;

	paywoad_size = sizeof(*cfg) + APM_MODUWE_PAWAM_DATA_SIZE;
	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	p = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = p;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = PAWAM_ID_VOW_CTWW_MASTEW_GAIN;
	pawam_data->pawam_size = paywoad_size - APM_MODUWE_PAWAM_DATA_SIZE;

	p = p + APM_MODUWE_PAWAM_DATA_SIZE;
	cfg = p;
	cfg->mastew_gain =  vow;
	wc = q6apm_send_cmd_sync(apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(audioweach_gain_set_vow_ctww);

static int audioweach_gain_set(stwuct q6apm_gwaph *gwaph, stwuct audioweach_moduwe *moduwe)
{
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct apm_gain_moduwe_cfg *cfg;
	int wc, paywoad_size;
	stwuct gpw_pkt *pkt;

	paywoad_size = APM_GAIN_CFG_PSIZE;
	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, APM_CMD_SET_CFG, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	cfg = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	pawam_data = &cfg->pawam_data;
	pawam_data->moduwe_instance_id = moduwe->instance_id;
	pawam_data->ewwow_code = 0;
	pawam_data->pawam_id = APM_PAWAM_ID_GAIN;
	pawam_data->pawam_size = paywoad_size - APM_MODUWE_PAWAM_DATA_SIZE;

	cfg->gain_cfg.gain = moduwe->gain;

	wc = q6apm_send_cmd_sync(gwaph->apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}

int audioweach_set_media_fowmat(stwuct q6apm_gwaph *gwaph, stwuct audioweach_moduwe *moduwe,
				stwuct audioweach_moduwe_config *cfg)
{
	int wc;

	switch (moduwe->moduwe_id) {
	case MODUWE_ID_DATA_WOGGING:
		wc = audioweach_moduwe_enabwe(gwaph, moduwe, twue);
		if (!wc)
			wc = audioweach_wogging_set_media_fowmat(gwaph, moduwe);
		bweak;
	case MODUWE_ID_PCM_DEC:
	case MODUWE_ID_PCM_ENC:
	case MODUWE_ID_PCM_CNV:
	case MODUWE_ID_PWACEHOWDEW_DECODEW:
	case MODUWE_ID_PWACEHOWDEW_ENCODEW:
		wc = audioweach_pcm_set_media_fowmat(gwaph, moduwe, cfg);
		bweak;
	case MODUWE_ID_DISPWAY_POWT_SINK:
		wc = audioweach_dispway_powt_set_media_fowmat(gwaph, moduwe, cfg);
		bweak;
	case MODUWE_ID_I2S_SOUWCE:
	case MODUWE_ID_I2S_SINK:
		wc = audioweach_i2s_set_media_fowmat(gwaph, moduwe, cfg);
		bweak;
	case MODUWE_ID_WW_SHAWED_MEM_EP:
		wc = audioweach_shmem_set_media_fowmat(gwaph, moduwe, cfg);
		bweak;
	case MODUWE_ID_GAIN:
		wc = audioweach_gain_set(gwaph, moduwe);
		bweak;
	case MODUWE_ID_CODEC_DMA_SINK:
	case MODUWE_ID_CODEC_DMA_SOUWCE:
		wc = audioweach_codec_dma_set_media_fowmat(gwaph, moduwe, cfg);
		bweak;
	case MODUWE_ID_SAW:
		wc = audioweach_saw_set_media_fowmat(gwaph, moduwe, cfg);
		if (!wc)
			wc = audioweach_saw_wimitew_enabwe(gwaph, moduwe, twue);
		bweak;
	case MODUWE_ID_MFC:
		wc = audioweach_mfc_set_media_fowmat(gwaph, moduwe, cfg);
		bweak;
	case MODUWE_ID_GAPWESS:
		wc = audioweach_gapwess_set_media_fowmat(gwaph, moduwe, cfg);
		bweak;
	defauwt:
		wc = 0;
	}

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(audioweach_set_media_fowmat);

void audioweach_gwaph_fwee_buf(stwuct q6apm_gwaph *gwaph)
{
	stwuct audioweach_gwaph_data *powt;

	mutex_wock(&gwaph->wock);
	powt = &gwaph->wx_data;
	powt->num_pewiods = 0;
	kfwee(powt->buf);
	powt->buf = NUWW;

	powt = &gwaph->tx_data;
	powt->num_pewiods = 0;
	kfwee(powt->buf);
	powt->buf = NUWW;
	mutex_unwock(&gwaph->wock);
}
EXPOWT_SYMBOW_GPW(audioweach_gwaph_fwee_buf);

int audioweach_map_memowy_wegions(stwuct q6apm_gwaph *gwaph, unsigned int diw, size_t pewiod_sz,
				  unsigned int pewiods, boow is_contiguous)
{
	stwuct apm_shawed_map_wegion_paywoad *mwegions;
	stwuct apm_cmd_shawed_mem_map_wegions *cmd;
	uint32_t num_wegions, buf_sz, paywoad_size;
	stwuct audioweach_gwaph_data *data;
	stwuct gpw_pkt *pkt;
	void *p;
	int wc, i;

	if (diw == SNDWV_PCM_STWEAM_PWAYBACK)
		data = &gwaph->wx_data;
	ewse
		data = &gwaph->tx_data;

	if (is_contiguous) {
		num_wegions = 1;
		buf_sz = pewiod_sz * pewiods;
	} ewse {
		buf_sz = pewiod_sz;
		num_wegions = pewiods;
	}

	/* DSP expects size shouwd be awigned to 4K */
	buf_sz = AWIGN(buf_sz, 4096);

	paywoad_size = sizeof(*cmd) + (sizeof(*mwegions) * num_wegions);

	pkt = audioweach_awwoc_apm_pkt(paywoad_size, APM_CMD_SHAWED_MEM_MAP_WEGIONS, diw,
				     gwaph->powt->id);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	p = (void *)pkt + GPW_HDW_SIZE;
	cmd = p;
	cmd->mem_poow_id = APM_MEMOWY_MAP_SHMEM8_4K_POOW;
	cmd->num_wegions = num_wegions;

	cmd->pwopewty_fwag = 0x0;

	mwegions = p + sizeof(*cmd);

	mutex_wock(&gwaph->wock);

	fow (i = 0; i < num_wegions; i++) {
		stwuct audio_buffew *ab;

		ab = &data->buf[i];
		mwegions->shm_addw_wsw = wowew_32_bits(ab->phys);
		mwegions->shm_addw_msw = uppew_32_bits(ab->phys);
		mwegions->mem_size_bytes = buf_sz;
		++mwegions;
	}
	mutex_unwock(&gwaph->wock);

	wc = audioweach_gwaph_send_cmd_sync(gwaph, pkt, APM_CMD_WSP_SHAWED_MEM_MAP_WEGIONS);

	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(audioweach_map_memowy_wegions);

int audioweach_shawed_memowy_send_eos(stwuct q6apm_gwaph *gwaph)
{
	stwuct data_cmd_ww_sh_mem_ep_eos *eos;
	stwuct gpw_pkt *pkt;
	int wc = 0, iid;

	iid = q6apm_gwaph_get_wx_shmem_moduwe_iid(gwaph);
	pkt = audioweach_awwoc_cmd_pkt(sizeof(*eos), DATA_CMD_WW_SH_MEM_EP_EOS, 0,
				       gwaph->powt->id, iid);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	eos = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	eos->powicy = WW_SH_MEM_EP_EOS_POWICY_WAST;

	wc = gpw_send_powt_pkt(gwaph->powt, pkt);
	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(audioweach_shawed_memowy_send_eos);
