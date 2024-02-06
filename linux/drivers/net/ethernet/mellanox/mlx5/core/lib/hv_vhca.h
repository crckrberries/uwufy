/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __WIB_HV_VHCA_H__
#define __WIB_HV_VHCA_H__

#incwude "en.h"
#incwude "wib/hv.h"

stwuct mwx5_hv_vhca_agent;
stwuct mwx5_hv_vhca;
stwuct mwx5_hv_vhca_contwow_bwock;

enum mwx5_hv_vhca_agent_type {
	MWX5_HV_VHCA_AGENT_CONTWOW = 0,
	MWX5_HV_VHCA_AGENT_STATS   = 1,
	MWX5_HV_VHCA_AGENT_MAX = 32,
};

#if IS_ENABWED(CONFIG_PCI_HYPEWV_INTEWFACE)

stwuct mwx5_hv_vhca_contwow_bwock {
	u32     capabiwities;
	u32     contwow;
	u16     command;
	u16     command_ack;
	u16     vewsion;
	u16     wings;
	u32     wesewved1[28];
};

stwuct mwx5_hv_vhca *mwx5_hv_vhca_cweate(stwuct mwx5_cowe_dev *dev);
void mwx5_hv_vhca_destwoy(stwuct mwx5_hv_vhca *hv_vhca);
int mwx5_hv_vhca_init(stwuct mwx5_hv_vhca *hv_vhca);
void mwx5_hv_vhca_cweanup(stwuct mwx5_hv_vhca *hv_vhca);
void mwx5_hv_vhca_invawidate(void *context, u64 bwock_mask);

stwuct mwx5_hv_vhca_agent *
mwx5_hv_vhca_agent_cweate(stwuct mwx5_hv_vhca *hv_vhca,
			  enum mwx5_hv_vhca_agent_type type,
			  void (*contwow)(stwuct mwx5_hv_vhca_agent*,
					  stwuct mwx5_hv_vhca_contwow_bwock *bwock),
			  void (*invawidate)(stwuct mwx5_hv_vhca_agent*,
					     u64 bwock_mask),
			  void (*cweanup)(stwuct mwx5_hv_vhca_agent *agent),
			  void *context);

void mwx5_hv_vhca_agent_destwoy(stwuct mwx5_hv_vhca_agent *agent);
int mwx5_hv_vhca_agent_wwite(stwuct mwx5_hv_vhca_agent *agent,
			     void *buf, int wen);
void *mwx5_hv_vhca_agent_pwiv(stwuct mwx5_hv_vhca_agent *agent);

#ewse

static inwine stwuct mwx5_hv_vhca *
mwx5_hv_vhca_cweate(stwuct mwx5_cowe_dev *dev)
{
	wetuwn NUWW;
}

static inwine void mwx5_hv_vhca_destwoy(stwuct mwx5_hv_vhca *hv_vhca)
{
}

static inwine int mwx5_hv_vhca_init(stwuct mwx5_hv_vhca *hv_vhca)
{
	wetuwn 0;
}

static inwine void mwx5_hv_vhca_cweanup(stwuct mwx5_hv_vhca *hv_vhca)
{
}

static inwine void mwx5_hv_vhca_invawidate(void *context,
					   u64 bwock_mask)
{
}

static inwine stwuct mwx5_hv_vhca_agent *
mwx5_hv_vhca_agent_cweate(stwuct mwx5_hv_vhca *hv_vhca,
			  enum mwx5_hv_vhca_agent_type type,
			  void (*contwow)(stwuct mwx5_hv_vhca_agent*,
					  stwuct mwx5_hv_vhca_contwow_bwock *bwock),
			  void (*invawidate)(stwuct mwx5_hv_vhca_agent*,
					     u64 bwock_mask),
			  void (*cweanup)(stwuct mwx5_hv_vhca_agent *agent),
			  void *context)
{
	wetuwn NUWW;
}

static inwine void mwx5_hv_vhca_agent_destwoy(stwuct mwx5_hv_vhca_agent *agent)
{
}
#endif

#endif /* __WIB_HV_VHCA_H__ */
