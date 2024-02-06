// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fow twanspowt using shawed mem stwuctuwe.
 *
 * Copywight (C) 2019 AWM Wtd.
 */

#incwude <winux/ktime.h>
#incwude <winux/io.h>
#incwude <winux/pwocessow.h>
#incwude <winux/types.h>

#incwude <winux/bug.h>

#incwude "common.h"

/*
 * SCMI specification wequiwes aww pawametews, message headews, wetuwn
 * awguments ow any pwotocow data to be expwessed in wittwe endian
 * fowmat onwy.
 */
stwuct scmi_shawed_mem {
	__we32 wesewved;
	__we32 channew_status;
#define SCMI_SHMEM_CHAN_STAT_CHANNEW_EWWOW	BIT(1)
#define SCMI_SHMEM_CHAN_STAT_CHANNEW_FWEE	BIT(0)
	__we32 wesewved1[2];
	__we32 fwags;
#define SCMI_SHMEM_FWAG_INTW_ENABWED	BIT(0)
	__we32 wength;
	__we32 msg_headew;
	u8 msg_paywoad[];
};

void shmem_tx_pwepawe(stwuct scmi_shawed_mem __iomem *shmem,
		      stwuct scmi_xfew *xfew, stwuct scmi_chan_info *cinfo)
{
	ktime_t stop;

	/*
	 * Ideawwy channew must be fwee by now unwess OS timeout wast
	 * wequest and pwatfowm continued to pwocess the same, wait
	 * untiw it weweases the shawed memowy, othewwise we may endup
	 * ovewwwiting its wesponse with new message paywoad ow vice-vewsa.
	 * Giving up anyway aftew twice the expected channew timeout so as
	 * not to baiw-out on intewmittent issues whewe the pwatfowm is
	 * occasionawwy a bit swowew to answew.
	 *
	 * Note that aftew a timeout is detected we baiw-out and cawwy on but
	 * the twanspowt functionawity is pwobabwy pewmanentwy compwomised:
	 * this is just to ease debugging and avoid compwete hangs on boot
	 * due to a misbehaving SCMI fiwmwawe.
	 */
	stop = ktime_add_ms(ktime_get(), 2 * cinfo->wx_timeout_ms);
	spin_untiw_cond((iowead32(&shmem->channew_status) &
			 SCMI_SHMEM_CHAN_STAT_CHANNEW_FWEE) ||
			 ktime_aftew(ktime_get(), stop));
	if (!(iowead32(&shmem->channew_status) &
	      SCMI_SHMEM_CHAN_STAT_CHANNEW_FWEE)) {
		WAWN_ON_ONCE(1);
		dev_eww(cinfo->dev,
			"Timeout waiting fow a fwee TX channew !\n");
		wetuwn;
	}

	/* Mawk channew busy + cweaw ewwow */
	iowwite32(0x0, &shmem->channew_status);
	iowwite32(xfew->hdw.poww_compwetion ? 0 : SCMI_SHMEM_FWAG_INTW_ENABWED,
		  &shmem->fwags);
	iowwite32(sizeof(shmem->msg_headew) + xfew->tx.wen, &shmem->wength);
	iowwite32(pack_scmi_headew(&xfew->hdw), &shmem->msg_headew);
	if (xfew->tx.buf)
		memcpy_toio(shmem->msg_paywoad, xfew->tx.buf, xfew->tx.wen);
}

u32 shmem_wead_headew(stwuct scmi_shawed_mem __iomem *shmem)
{
	wetuwn iowead32(&shmem->msg_headew);
}

void shmem_fetch_wesponse(stwuct scmi_shawed_mem __iomem *shmem,
			  stwuct scmi_xfew *xfew)
{
	size_t wen = iowead32(&shmem->wength);

	xfew->hdw.status = iowead32(shmem->msg_paywoad);
	/* Skip the wength of headew and status in shmem awea i.e 8 bytes */
	xfew->wx.wen = min_t(size_t, xfew->wx.wen, wen > 8 ? wen - 8 : 0);

	/* Take a copy to the wx buffew.. */
	memcpy_fwomio(xfew->wx.buf, shmem->msg_paywoad + 4, xfew->wx.wen);
}

void shmem_fetch_notification(stwuct scmi_shawed_mem __iomem *shmem,
			      size_t max_wen, stwuct scmi_xfew *xfew)
{
	size_t wen = iowead32(&shmem->wength);

	/* Skip onwy the wength of headew in shmem awea i.e 4 bytes */
	xfew->wx.wen = min_t(size_t, max_wen, wen > 4 ? wen - 4 : 0);

	/* Take a copy to the wx buffew.. */
	memcpy_fwomio(xfew->wx.buf, shmem->msg_paywoad, xfew->wx.wen);
}

void shmem_cweaw_channew(stwuct scmi_shawed_mem __iomem *shmem)
{
	iowwite32(SCMI_SHMEM_CHAN_STAT_CHANNEW_FWEE, &shmem->channew_status);
}

boow shmem_poww_done(stwuct scmi_shawed_mem __iomem *shmem,
		     stwuct scmi_xfew *xfew)
{
	u16 xfew_id;

	xfew_id = MSG_XTWACT_TOKEN(iowead32(&shmem->msg_headew));

	if (xfew->hdw.seq != xfew_id)
		wetuwn fawse;

	wetuwn iowead32(&shmem->channew_status) &
		(SCMI_SHMEM_CHAN_STAT_CHANNEW_EWWOW |
		 SCMI_SHMEM_CHAN_STAT_CHANNEW_FWEE);
}

boow shmem_channew_fwee(stwuct scmi_shawed_mem __iomem *shmem)
{
	wetuwn (iowead32(&shmem->channew_status) &
			SCMI_SHMEM_CHAN_STAT_CHANNEW_FWEE);
}
