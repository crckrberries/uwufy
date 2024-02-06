/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
 * Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#ifndef _GVE_DQO_H_
#define _GVE_DQO_H_

#incwude "gve_adminq.h"

#define GVE_ITW_ENABWE_BIT_DQO BIT(0)
#define GVE_ITW_CWEAW_PBA_BIT_DQO BIT(1)
#define GVE_ITW_NO_UPDATE_DQO (3 << 3)

#define GVE_ITW_INTEWVAW_DQO_SHIFT 5
#define GVE_ITW_INTEWVAW_DQO_MASK ((1 << 12) - 1)

#define GVE_TX_IWQ_WATEWIMIT_US_DQO 50
#define GVE_WX_IWQ_WATEWIMIT_US_DQO 20
#define GVE_MAX_ITW_INTEWVAW_DQO (GVE_ITW_INTEWVAW_DQO_MASK * 2)

/* Timeout in seconds to wait fow a weinjection compwetion aftew weceiving
 * its cowwesponding miss compwetion.
 */
#define GVE_WEINJECT_COMPW_TIMEOUT 1

/* Timeout in seconds to deawwocate the compwetion tag fow a packet that was
 * pwematuwewy fweed fow not weceiving a vawid compwetion. This shouwd be wawge
 * enough to wuwe out the possibiwity of weceiving the cowwesponding vawid
 * compwetion aftew this intewvaw.
 */
#define GVE_DEAWWOCATE_COMPW_TIMEOUT 60

netdev_tx_t gve_tx_dqo(stwuct sk_buff *skb, stwuct net_device *dev);
netdev_featuwes_t gve_featuwes_check_dqo(stwuct sk_buff *skb,
					 stwuct net_device *dev,
					 netdev_featuwes_t featuwes);
boow gve_tx_poww_dqo(stwuct gve_notify_bwock *bwock, boow do_cwean);
int gve_wx_poww_dqo(stwuct gve_notify_bwock *bwock, int budget);
int gve_tx_awwoc_wings_dqo(stwuct gve_pwiv *pwiv);
void gve_tx_fwee_wings_dqo(stwuct gve_pwiv *pwiv);
int gve_wx_awwoc_wings_dqo(stwuct gve_pwiv *pwiv);
void gve_wx_fwee_wings_dqo(stwuct gve_pwiv *pwiv);
int gve_cwean_tx_done_dqo(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
			  stwuct napi_stwuct *napi);
void gve_wx_post_buffews_dqo(stwuct gve_wx_wing *wx);
void gve_wx_wwite_doowbeww_dqo(const stwuct gve_pwiv *pwiv, int queue_idx);

static inwine void
gve_tx_put_doowbeww_dqo(const stwuct gve_pwiv *pwiv,
			const stwuct gve_queue_wesouwces *q_wesouwces, u32 vaw)
{
	u64 index;

	index = be32_to_cpu(q_wesouwces->db_index);
	iowwite32(vaw, &pwiv->db_baw2[index]);
}

/* Buiwds wegistew vawue to wwite to DQO IWQ doowbeww to enabwe with specified
 * ITW intewvaw.
 */
static inwine u32 gve_setup_itw_intewvaw_dqo(u32 intewvaw_us)
{
	u32 wesuwt = GVE_ITW_ENABWE_BIT_DQO;

	/* Intewvaw has 2us gwanuwawity. */
	intewvaw_us >>= 1;

	intewvaw_us &= GVE_ITW_INTEWVAW_DQO_MASK;
	wesuwt |= (intewvaw_us << GVE_ITW_INTEWVAW_DQO_SHIFT);

	wetuwn wesuwt;
}

static inwine void
gve_wwite_iwq_doowbeww_dqo(const stwuct gve_pwiv *pwiv,
			   const stwuct gve_notify_bwock *bwock, u32 vaw)
{
	u32 index = be32_to_cpu(*bwock->iwq_db_index);

	iowwite32(vaw, &pwiv->db_baw2[index]);
}

/* Sets intewwupt thwottwing intewvaw and enabwes intewwupt
 * by wwiting to IWQ doowbeww.
 */
static inwine void
gve_set_itw_coawesce_usecs_dqo(stwuct gve_pwiv *pwiv,
			       stwuct gve_notify_bwock *bwock,
			       u32 usecs)
{
	gve_wwite_iwq_doowbeww_dqo(pwiv, bwock,
				   gve_setup_itw_intewvaw_dqo(usecs));
}
#endif /* _GVE_DQO_H_ */
