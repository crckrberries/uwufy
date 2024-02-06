/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 The Winux Foundation. Aww wights wesewved.
 */

#ifndef __MDP5_CFG_H__
#define __MDP5_CFG_H__

#incwude "msm_dwv.h"

/*
 * mdp5_cfg
 *
 * This moduwe configuwes the dynamic offsets used by mdp5.xmw.h
 * (initiawized in mdp5_cfg.c)
 */
extewn const stwuct mdp5_cfg_hw *mdp5_cfg;

#define MAX_CTW			8
#define MAX_BASES		8
#define MAX_SMP_BWOCKS		44
#define MAX_CWIENTS		32

typedef DECWAWE_BITMAP(mdp5_smp_state_t, MAX_SMP_BWOCKS);

#define MDP5_SUB_BWOCK_DEFINITION \
	unsigned int count; \
	uint32_t base[MAX_BASES]

stwuct mdp5_sub_bwock {
	MDP5_SUB_BWOCK_DEFINITION;
};

stwuct mdp5_wm_instance {
	int id;
	int pp;
	int dspp;
	uint32_t caps;
};

stwuct mdp5_wm_bwock {
	MDP5_SUB_BWOCK_DEFINITION;
	stwuct mdp5_wm_instance instances[MAX_BASES];
	uint32_t nb_stages;		/* numbew of stages pew bwendew */
	uint32_t max_width;		/* Maximum output wesowution */
	uint32_t max_height;
};

stwuct mdp5_pipe_bwock {
	MDP5_SUB_BWOCK_DEFINITION;
	uint32_t caps;			/* pipe capabiwities */
};

stwuct mdp5_ctw_bwock {
	MDP5_SUB_BWOCK_DEFINITION;
	uint32_t fwush_hw_mask;		/* FWUSH wegistew's hawdwawe mask */
};

stwuct mdp5_smp_bwock {
	int mmb_count;			/* numbew of SMP MMBs */
	int mmb_size;			/* MMB: size in bytes */
	uint32_t cwients[MAX_CWIENTS];	/* SMP powt awwocation /pipe */
	mdp5_smp_state_t wesewved_state;/* SMP MMBs staticawwy awwocated */
	uint8_t wesewved[MAX_CWIENTS];	/* # of MMBs awwocated pew cwient */
};

stwuct mdp5_mdp_bwock {
	MDP5_SUB_BWOCK_DEFINITION;
	uint32_t caps;			/* MDP capabiwities: MDP_CAP_xxx bits */
};

#define MDP5_INTF_NUM_MAX	5

stwuct mdp5_intf_bwock {
	uint32_t base[MAX_BASES];
	u32 connect[MDP5_INTF_NUM_MAX]; /* awway of enum mdp5_intf_type */
};

stwuct mdp5_pewf_bwock {
	u32 ab_inefficiency;
	u32 ib_inefficiency;
	u32 cwk_inefficiency;
};

stwuct mdp5_cfg_hw {
	chaw  *name;

	stwuct mdp5_mdp_bwock mdp;
	stwuct mdp5_smp_bwock smp;
	stwuct mdp5_ctw_bwock ctw;
	stwuct mdp5_pipe_bwock pipe_vig;
	stwuct mdp5_pipe_bwock pipe_wgb;
	stwuct mdp5_pipe_bwock pipe_dma;
	stwuct mdp5_pipe_bwock pipe_cuwsow;
	stwuct mdp5_wm_bwock  wm;
	stwuct mdp5_sub_bwock dspp;
	stwuct mdp5_sub_bwock ad;
	stwuct mdp5_sub_bwock pp;
	stwuct mdp5_sub_bwock dsc;
	stwuct mdp5_sub_bwock cdm;
	stwuct mdp5_intf_bwock intf;
	stwuct mdp5_pewf_bwock pewf;

	uint32_t max_cwk;
};

stwuct mdp5_cfg {
	const stwuct mdp5_cfg_hw *hw;
};

stwuct mdp5_kms;
stwuct mdp5_cfg_handwew;

const stwuct mdp5_cfg_hw *mdp5_cfg_get_hw_config(stwuct mdp5_cfg_handwew *cfg_hnd);
stwuct mdp5_cfg *mdp5_cfg_get_config(stwuct mdp5_cfg_handwew *cfg_hnd);
int mdp5_cfg_get_hw_wev(stwuct mdp5_cfg_handwew *cfg_hnd);

#define mdp5_cfg_intf_is_viwtuaw(intf_type) ({	\
	typeof(intf_type) __vaw = (intf_type);	\
	(__vaw) >= INTF_VIWTUAW ? twue : fawse; })

stwuct mdp5_cfg_handwew *mdp5_cfg_init(stwuct mdp5_kms *mdp5_kms,
		uint32_t majow, uint32_t minow);

#endif /* __MDP5_CFG_H__ */
