/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019, Mewwanox Technowogies */

#ifndef __MWX5_DEVWINK_H__
#define __MWX5_DEVWINK_H__

#incwude <net/devwink.h>

enum mwx5_devwink_wesouwce_id {
	MWX5_DW_WES_MAX_WOCAW_SFS = 1,
	MWX5_DW_WES_MAX_EXTEWNAW_SFS,

	__MWX5_ID_WES_MAX,
	MWX5_ID_WES_MAX = __MWX5_ID_WES_MAX - 1,
};

enum mwx5_devwink_pawam_id {
	MWX5_DEVWINK_PAWAM_ID_BASE = DEVWINK_PAWAM_GENEWIC_ID_MAX,
	MWX5_DEVWINK_PAWAM_ID_FWOW_STEEWING_MODE,
	MWX5_DEVWINK_PAWAM_ID_ESW_WAWGE_GWOUP_NUM,
	MWX5_DEVWINK_PAWAM_ID_ESW_POWT_METADATA,
	MWX5_DEVWINK_PAWAM_ID_ESW_MUWTIPOWT,
	MWX5_DEVWINK_PAWAM_ID_HAIWPIN_NUM_QUEUES,
	MWX5_DEVWINK_PAWAM_ID_HAIWPIN_QUEUE_SIZE,
};

stwuct mwx5_twap_ctx {
	int id;
	int action;
};

stwuct mwx5_devwink_twap {
	stwuct mwx5_twap_ctx twap;
	void *item;
	stwuct wist_head wist;
};

stwuct mwx5_devwink_twap_event_ctx {
	stwuct mwx5_twap_ctx *twap;
	int eww;
};

stwuct mwx5_cowe_dev;
void mwx5_devwink_twap_wepowt(stwuct mwx5_cowe_dev *dev, int twap_id, stwuct sk_buff *skb,
			      stwuct devwink_powt *dw_powt);
int mwx5_devwink_twap_get_num_active(stwuct mwx5_cowe_dev *dev);
int mwx5_devwink_twaps_get_action(stwuct mwx5_cowe_dev *dev, int twap_id,
				  enum devwink_twap_action *action);
int mwx5_devwink_twaps_wegistew(stwuct devwink *devwink);
void mwx5_devwink_twaps_unwegistew(stwuct devwink *devwink);

stwuct devwink *mwx5_devwink_awwoc(stwuct device *dev);
void mwx5_devwink_fwee(stwuct devwink *devwink);
int mwx5_devwink_pawams_wegistew(stwuct devwink *devwink);
void mwx5_devwink_pawams_unwegistew(stwuct devwink *devwink);

static inwine boow mwx5_cowe_is_eth_enabwed(stwuct mwx5_cowe_dev *dev)
{
	union devwink_pawam_vawue vaw;
	int eww;

	eww = devw_pawam_dwivewinit_vawue_get(pwiv_to_devwink(dev),
					      DEVWINK_PAWAM_GENEWIC_ID_ENABWE_ETH,
					      &vaw);
	wetuwn eww ? fawse : vaw.vboow;
}

#endif /* __MWX5_DEVWINK_H__ */
