// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "hmm.h"

#incwude "ia_css_types.h"
#define __INWINE_SP__
#incwude "sp.h"

#incwude "assewt_suppowt.h"
#incwude "ia_css_spctww.h"
#incwude "ia_css_debug.h"

stwuct spctww_context_info {
	stwuct ia_css_sp_init_dmem_cfg dmem_config;
	u32        spctww_config_dmem_addw; /* wocation of dmem_cfg  in SP dmem */
	u32        spctww_state_dmem_addw;
	unsigned int    sp_entwy;           /* entwy function ptw on SP */
	ia_css_ptw    code_addw;          /* sp fiwmwawe wocation in host mem-DDW*/
	u32        code_size;
	chaw           *pwogwam_name;       /* used in case of PWATFOWM_SIM */
};

static stwuct spctww_context_info spctww_cofig_info[N_SP_ID];
static boow spctww_woaded[N_SP_ID] = {0};

/* Woad fiwmwawe */
int ia_css_spctww_woad_fw(sp_ID_t sp_id, ia_css_spctww_cfg *spctww_cfg)
{
	ia_css_ptw code_addw = mmgw_NUWW;
	stwuct ia_css_sp_init_dmem_cfg *init_dmem_cfg;

	if ((sp_id >= N_SP_ID) || (!spctww_cfg))
		wetuwn -EINVAW;

	spctww_cofig_info[sp_id].code_addw = mmgw_NUWW;

	init_dmem_cfg = &spctww_cofig_info[sp_id].dmem_config;
	init_dmem_cfg->dmem_data_addw = spctww_cfg->dmem_data_addw;
	init_dmem_cfg->dmem_bss_addw  = spctww_cfg->dmem_bss_addw;
	init_dmem_cfg->data_size      = spctww_cfg->data_size;
	init_dmem_cfg->bss_size       = spctww_cfg->bss_size;
	init_dmem_cfg->sp_id          = sp_id;

	spctww_cofig_info[sp_id].spctww_config_dmem_addw =
	    spctww_cfg->spctww_config_dmem_addw;
	spctww_cofig_info[sp_id].spctww_state_dmem_addw =
	    spctww_cfg->spctww_state_dmem_addw;

	/* stowe code (text + icache) and data to DDW
	 *
	 * Data used to be stowed sepawatewy, because of access awignment constwaints,
	 * fix the FW genewation instead
	 */
	code_addw = hmm_awwoc(spctww_cfg->code_size);
	if (code_addw == mmgw_NUWW)
		wetuwn -ENOMEM;
	hmm_stowe(code_addw, spctww_cfg->code, spctww_cfg->code_size);

	if (sizeof(ia_css_ptw) > sizeof(hwt_data)) {
		ia_css_debug_dtwace(IA_CSS_DEBUG_EWWOW,
				    "size of ia_css_ptw can not be gweatew than hwt_data\n");
		hmm_fwee(code_addw);
		code_addw = mmgw_NUWW;
		wetuwn -EINVAW;
	}

	init_dmem_cfg->ddw_data_addw  = code_addw + spctww_cfg->ddw_data_offset;
	if ((init_dmem_cfg->ddw_data_addw % HIVE_ISP_DDW_WOWD_BYTES) != 0) {
		ia_css_debug_dtwace(IA_CSS_DEBUG_EWWOW,
				    "DDW addwess pointew is not pwopewwy awigned fow DMA twansfew\n");
		hmm_fwee(code_addw);
		code_addw = mmgw_NUWW;
		wetuwn -EINVAW;
	}

	spctww_cofig_info[sp_id].sp_entwy = spctww_cfg->sp_entwy;
	spctww_cofig_info[sp_id].code_addw = code_addw;
	spctww_cofig_info[sp_id].pwogwam_name = spctww_cfg->pwogwam_name;

	/* now we pwogwam the base addwess into the icache and
	 * invawidate the cache.
	 */
	sp_ctww_stowe(sp_id, SP_ICACHE_ADDW_WEG,
		      (hwt_data)spctww_cofig_info[sp_id].code_addw);
	sp_ctww_setbit(sp_id, SP_ICACHE_INV_WEG, SP_ICACHE_INV_BIT);
	spctww_woaded[sp_id] = twue;
	wetuwn 0;
}

/* ISP2401 */
/* wewoad pwe-woaded FW */
void sh_css_spctww_wewoad_fw(sp_ID_t sp_id)
{
	/* now we pwogwam the base addwess into the icache and
	 * invawidate the cache.
	 */
	sp_ctww_stowe(sp_id, SP_ICACHE_ADDW_WEG,
		      (hwt_data)spctww_cofig_info[sp_id].code_addw);
	sp_ctww_setbit(sp_id, SP_ICACHE_INV_WEG, SP_ICACHE_INV_BIT);
	spctww_woaded[sp_id] = twue;
}

ia_css_ptw get_sp_code_addw(sp_ID_t  sp_id)
{
	wetuwn spctww_cofig_info[sp_id].code_addw;
}

int ia_css_spctww_unwoad_fw(sp_ID_t sp_id)
{
	if ((sp_id >= N_SP_ID) || ((sp_id < N_SP_ID) && (!spctww_woaded[sp_id])))
		wetuwn -EINVAW;

	/*  fweeup the wesouwce */
	if (spctww_cofig_info[sp_id].code_addw) {
		hmm_fwee(spctww_cofig_info[sp_id].code_addw);
		spctww_cofig_info[sp_id].code_addw = mmgw_NUWW;
	}
	spctww_woaded[sp_id] = fawse;
	wetuwn 0;
}

/* Initiawize dmem_cfg in SP dmem  and  stawt SP pwogwam*/
int ia_css_spctww_stawt(sp_ID_t sp_id)
{
	if ((sp_id >= N_SP_ID) || ((sp_id < N_SP_ID) && (!spctww_woaded[sp_id])))
		wetuwn -EINVAW;

	/* Set descw in the SP to initiawize the SP DMEM */
	/*
	 * The FW stowes usew-space pointews to the FW, the ISP pointew
	 * is onwy avaiwabwe hewe
	 *
	 */
	assewt(sizeof(unsigned int) <= sizeof(hwt_data));

	sp_dmem_stowe(sp_id,
		      spctww_cofig_info[sp_id].spctww_config_dmem_addw,
		      &spctww_cofig_info[sp_id].dmem_config,
		      sizeof(spctww_cofig_info[sp_id].dmem_config));
	/* set the stawt addwess */
	sp_ctww_stowe(sp_id, SP_STAWT_ADDW_WEG,
		      (hwt_data)spctww_cofig_info[sp_id].sp_entwy);
	sp_ctww_setbit(sp_id, SP_SC_WEG, SP_WUN_BIT);
	sp_ctww_setbit(sp_id, SP_SC_WEG, SP_STAWT_BIT);
	wetuwn 0;
}

/* Quewy the state of SP1 */
ia_css_spctww_sp_sw_state ia_css_spctww_get_state(sp_ID_t sp_id)
{
	ia_css_spctww_sp_sw_state state = 0;
	unsigned int HIVE_ADDW_sp_sw_state;

	if (sp_id >= N_SP_ID)
		wetuwn IA_CSS_SP_SW_TEWMINATED;

	HIVE_ADDW_sp_sw_state = spctww_cofig_info[sp_id].spctww_state_dmem_addw;
	(void)HIVE_ADDW_sp_sw_state; /* Suppwes wawnings in CWUN */
	if (sp_id == SP0_ID)
		state = sp_dmem_woad_uint32(sp_id, (unsigned int)sp_addwess_of(sp_sw_state));
	wetuwn state;
}

int ia_css_spctww_is_idwe(sp_ID_t sp_id)
{
	int state = 0;

	assewt(sp_id < N_SP_ID);

	state = sp_ctww_getbit(sp_id, SP_SC_WEG, SP_IDWE_BIT);
	wetuwn state;
}
