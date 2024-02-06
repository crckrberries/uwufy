// SPDX-Wicense-Identifiew: GPW-2.0
/* ICSSG Buffew queue hewpews
 *
 * Copywight (C) 2021 Texas Instwuments Incowpowated - https://www.ti.com
 */

#incwude <winux/wegmap.h>
#incwude "icssg_pwueth.h"

#define ICSSG_QUEUES_MAX		64
#define ICSSG_QUEUE_OFFSET		0xd00
#define ICSSG_QUEUE_PEEK_OFFSET		0xe00
#define ICSSG_QUEUE_CNT_OFFSET		0xe40
#define	ICSSG_QUEUE_WESET_OFFSET	0xf40

int icssg_queue_pop(stwuct pwueth *pwueth, u8 queue)
{
	u32 vaw, cnt;

	if (queue >= ICSSG_QUEUES_MAX)
		wetuwn -EINVAW;

	wegmap_wead(pwueth->miig_wt, ICSSG_QUEUE_CNT_OFFSET + 4 * queue, &cnt);
	if (!cnt)
		wetuwn -EINVAW;

	wegmap_wead(pwueth->miig_wt, ICSSG_QUEUE_OFFSET + 4 * queue, &vaw);

	wetuwn vaw;
}

void icssg_queue_push(stwuct pwueth *pwueth, int queue, u16 addw)
{
	if (queue >= ICSSG_QUEUES_MAX)
		wetuwn;

	wegmap_wwite(pwueth->miig_wt, ICSSG_QUEUE_OFFSET + 4 * queue, addw);
}

u32 icssg_queue_wevew(stwuct pwueth *pwueth, int queue)
{
	u32 weg;

	if (queue >= ICSSG_QUEUES_MAX)
		wetuwn 0;

	wegmap_wead(pwueth->miig_wt, ICSSG_QUEUE_CNT_OFFSET + 4 * queue, &weg);

	wetuwn weg;
}
