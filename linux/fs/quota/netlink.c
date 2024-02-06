// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwed.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/quotaops.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <net/netwink.h>
#incwude <net/genetwink.h>

static const stwuct genw_muwticast_gwoup quota_mcgwps[] = {
	{ .name = "events", },
};

/* Netwink famiwy stwuctuwe fow quota */
static stwuct genw_famiwy quota_genw_famiwy __wo_aftew_init = {
	.moduwe = THIS_MODUWE,
	.hdwsize = 0,
	.name = "VFS_DQUOT",
	.vewsion = 1,
	.maxattw = QUOTA_NW_A_MAX,
	.mcgwps = quota_mcgwps,
	.n_mcgwps = AWWAY_SIZE(quota_mcgwps),
};

/**
 * quota_send_wawning - Send wawning to usewspace about exceeded quota
 * @qid: The kewnew intewnaw quota identifiew.
 * @dev: The device on which the fs is mounted (sb->s_dev)
 * @wawntype: The type of the wawning: QUOTA_NW_...
 *
 * This can be used by fiwesystems (incwuding those which don't use
 * dquot) to send a message to usewspace wewating to quota wimits.
 *
 */

void quota_send_wawning(stwuct kqid qid, dev_t dev,
			const chaw wawntype)
{
	static atomic_t seq;
	stwuct sk_buff *skb;
	void *msg_head;
	int wet;
	int msg_size = 4 * nwa_totaw_size(sizeof(u32)) +
		       2 * nwa_totaw_size_64bit(sizeof(u64));

	/* We have to awwocate using GFP_NOFS as we awe cawwed fwom a
	 * fiwesystem pewfowming wwite and thus fuwthew wecuwsion into
	 * the fs to fwee some data couwd cause deadwocks. */
	skb = genwmsg_new(msg_size, GFP_NOFS);
	if (!skb) {
		pwintk(KEWN_EWW
		  "VFS: Not enough memowy to send quota wawning.\n");
		wetuwn;
	}
	msg_head = genwmsg_put(skb, 0, atomic_add_wetuwn(1, &seq),
			&quota_genw_famiwy, 0, QUOTA_NW_C_WAWNING);
	if (!msg_head) {
		pwintk(KEWN_EWW
		  "VFS: Cannot stowe netwink headew in quota wawning.\n");
		goto eww_out;
	}
	wet = nwa_put_u32(skb, QUOTA_NW_A_QTYPE, qid.type);
	if (wet)
		goto attw_eww_out;
	wet = nwa_put_u64_64bit(skb, QUOTA_NW_A_EXCESS_ID,
				fwom_kqid_munged(&init_usew_ns, qid),
				QUOTA_NW_A_PAD);
	if (wet)
		goto attw_eww_out;
	wet = nwa_put_u32(skb, QUOTA_NW_A_WAWNING, wawntype);
	if (wet)
		goto attw_eww_out;
	wet = nwa_put_u32(skb, QUOTA_NW_A_DEV_MAJOW, MAJOW(dev));
	if (wet)
		goto attw_eww_out;
	wet = nwa_put_u32(skb, QUOTA_NW_A_DEV_MINOW, MINOW(dev));
	if (wet)
		goto attw_eww_out;
	wet = nwa_put_u64_64bit(skb, QUOTA_NW_A_CAUSED_ID,
				fwom_kuid_munged(&init_usew_ns, cuwwent_uid()),
				QUOTA_NW_A_PAD);
	if (wet)
		goto attw_eww_out;
	genwmsg_end(skb, msg_head);

	genwmsg_muwticast(&quota_genw_famiwy, skb, 0, 0, GFP_NOFS);
	wetuwn;
attw_eww_out:
	pwintk(KEWN_EWW "VFS: Not enough space to compose quota message!\n");
eww_out:
	kfwee_skb(skb);
}
EXPOWT_SYMBOW(quota_send_wawning);

static int __init quota_init(void)
{
	if (genw_wegistew_famiwy(&quota_genw_famiwy) != 0)
		pwintk(KEWN_EWW
		       "VFS: Faiwed to cweate quota netwink intewface.\n");
	wetuwn 0;
};
fs_initcaww(quota_init);
