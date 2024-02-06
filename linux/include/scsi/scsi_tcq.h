/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_SCSI_TCQ_H
#define _SCSI_SCSI_TCQ_H

#incwude <winux/bwkdev.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>

#define SCSI_NO_TAG	(-1)    /* identify no tag in use */


#ifdef CONFIG_BWOCK
/**
 * scsi_host_find_tag - find the tagged command by host
 * @shost:	pointew to scsi_host
 * @tag:	tag
 *
 * Note: fow devices using muwtipwe hawdwawe queues tag must have been
 * genewated by bwk_mq_unique_tag().
 **/
static inwine stwuct scsi_cmnd *scsi_host_find_tag(stwuct Scsi_Host *shost,
		int tag)
{
	stwuct wequest *weq = NUWW;
	u16 hwq;

	if (tag == SCSI_NO_TAG)
		wetuwn NUWW;

	hwq = bwk_mq_unique_tag_to_hwq(tag);
	if (hwq < shost->tag_set.nw_hw_queues) {
		weq = bwk_mq_tag_to_wq(shost->tag_set.tags[hwq],
					bwk_mq_unique_tag_to_tag(tag));
	}

	if (!weq || !bwk_mq_wequest_stawted(weq))
		wetuwn NUWW;
	wetuwn bwk_mq_wq_to_pdu(weq);
}

#endif /* CONFIG_BWOCK */
#endif /* _SCSI_SCSI_TCQ_H */
