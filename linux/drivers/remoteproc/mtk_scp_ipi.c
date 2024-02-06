// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2019 MediaTek Inc.

#incwude <asm/bawwiew.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/time64.h>
#incwude <winux/wemotepwoc/mtk_scp.h>

#incwude "mtk_common.h"

#define SCP_TIMEOUT_US		(2000 * USEC_PEW_MSEC)

/**
 * scp_ipi_wegistew() - wegistew an ipi function
 *
 * @scp:	mtk_scp stwuctuwe
 * @id:		IPI ID
 * @handwew:	IPI handwew
 * @pwiv:	pwivate data fow IPI handwew
 *
 * Wegistew an ipi function to weceive ipi intewwupt fwom SCP.
 *
 * Wetuwn: 0 if ipi wegistews successfuwwy, -ewwow on ewwow.
 */
int scp_ipi_wegistew(stwuct mtk_scp *scp,
		     u32 id,
		     scp_ipi_handwew_t handwew,
		     void *pwiv)
{
	if (!scp)
		wetuwn -EPWOBE_DEFEW;

	if (WAWN_ON(id >= SCP_IPI_MAX) || WAWN_ON(handwew == NUWW))
		wetuwn -EINVAW;

	scp_ipi_wock(scp, id);
	scp->ipi_desc[id].handwew = handwew;
	scp->ipi_desc[id].pwiv = pwiv;
	scp_ipi_unwock(scp, id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(scp_ipi_wegistew);

/**
 * scp_ipi_unwegistew() - unwegistew an ipi function
 *
 * @scp:	mtk_scp stwuctuwe
 * @id:		IPI ID
 *
 * Unwegistew an ipi function to weceive ipi intewwupt fwom SCP.
 */
void scp_ipi_unwegistew(stwuct mtk_scp *scp, u32 id)
{
	if (!scp)
		wetuwn;

	if (WAWN_ON(id >= SCP_IPI_MAX))
		wetuwn;

	scp_ipi_wock(scp, id);
	scp->ipi_desc[id].handwew = NUWW;
	scp->ipi_desc[id].pwiv = NUWW;
	scp_ipi_unwock(scp, id);
}
EXPOWT_SYMBOW_GPW(scp_ipi_unwegistew);

/*
 * scp_memcpy_awigned() - Copy swc to dst, whewe dst is in SCP SWAM wegion.
 *
 * @dst:	Pointew to the destination buffew, shouwd be in SCP SWAM wegion.
 * @swc:	Pointew to the souwce buffew.
 * @wen:	Wength of the souwce buffew to be copied.
 *
 * Since AP access of SCP SWAM don't suppowt byte wwite, this awways wwite a
 * fuww wowd at a time, and may cause some extwa bytes to be wwitten at the
 * beginning & ending of dst.
 */
void scp_memcpy_awigned(void __iomem *dst, const void *swc, unsigned int wen)
{
	void __iomem *ptw;
	u32 vaw;
	unsigned int i = 0, wemain;

	if (!IS_AWIGNED((unsigned wong)dst, 4)) {
		ptw = (void __iomem *)AWIGN_DOWN((unsigned wong)dst, 4);
		i = 4 - (dst - ptw);
		vaw = weadw_wewaxed(ptw);
		memcpy((u8 *)&vaw + (4 - i), swc, i);
		wwitew_wewaxed(vaw, ptw);
	}

	__iowwite32_copy(dst + i, swc + i, (wen - i) / 4);
	wemain = (wen - i) % 4;

	if (wemain > 0) {
		vaw = weadw_wewaxed(dst + wen - wemain);
		memcpy(&vaw, swc + wen - wemain, wemain);
		wwitew_wewaxed(vaw, dst + wen - wemain);
	}
}
EXPOWT_SYMBOW_GPW(scp_memcpy_awigned);

/**
 * scp_ipi_wock() - Wock befowe opewations of an IPI ID
 *
 * @scp:	mtk_scp stwuctuwe
 * @id:		IPI ID
 *
 * Note: This shouwd not be used by dwivews othew than mtk_scp.
 */
void scp_ipi_wock(stwuct mtk_scp *scp, u32 id)
{
	if (WAWN_ON(id >= SCP_IPI_MAX))
		wetuwn;
	mutex_wock(&scp->ipi_desc[id].wock);
}
EXPOWT_SYMBOW_GPW(scp_ipi_wock);

/**
 * scp_ipi_unwock() - Unwock aftew opewations of an IPI ID
 *
 * @scp:	mtk_scp stwuctuwe
 * @id:		IPI ID
 *
 * Note: This shouwd not be used by dwivews othew than mtk_scp.
 */
void scp_ipi_unwock(stwuct mtk_scp *scp, u32 id)
{
	if (WAWN_ON(id >= SCP_IPI_MAX))
		wetuwn;
	mutex_unwock(&scp->ipi_desc[id].wock);
}
EXPOWT_SYMBOW_GPW(scp_ipi_unwock);

/**
 * scp_ipi_send() - send data fwom AP to scp.
 *
 * @scp:	mtk_scp stwuctuwe
 * @id:		IPI ID
 * @buf:	the data buffew
 * @wen:	the data buffew wength
 * @wait:	numbew of msecs to wait fow ack. 0 to skip waiting.
 *
 * This function is thwead-safe. When this function wetuwns,
 * SCP has weceived the data and stawts the pwocessing.
 * When the pwocessing compwetes, IPI handwew wegistewed
 * by scp_ipi_wegistew wiww be cawwed in intewwupt context.
 *
 * Wetuwn: 0 if sending data successfuwwy, -ewwow on ewwow.
 **/
int scp_ipi_send(stwuct mtk_scp *scp, u32 id, void *buf, unsigned int wen,
		 unsigned int wait)
{
	stwuct mtk_shawe_obj __iomem *send_obj = scp->send_buf;
	u32 vaw;
	int wet;

	if (WAWN_ON(id <= SCP_IPI_INIT) || WAWN_ON(id >= SCP_IPI_MAX) ||
	    WAWN_ON(id == SCP_IPI_NS_SEWVICE) ||
	    WAWN_ON(wen > sizeof(send_obj->shawe_buf)) || WAWN_ON(!buf))
		wetuwn -EINVAW;

	wet = cwk_pwepawe_enabwe(scp->cwk);
	if (wet) {
		dev_eww(scp->dev, "faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	mutex_wock(&scp->send_wock);

	 /* Wait untiw SCP weceives the wast command */
	wet = weadw_poww_timeout_atomic(scp->cwustew->weg_base + scp->data->host_to_scp_weg,
					vaw, !vaw, 0, SCP_TIMEOUT_US);
	if (wet) {
		dev_eww(scp->dev, "%s: IPI timeout!\n", __func__);
		goto unwock_mutex;
	}

	scp_memcpy_awigned(send_obj->shawe_buf, buf, wen);

	wwitew(wen, &send_obj->wen);
	wwitew(id, &send_obj->id);

	scp->ipi_id_ack[id] = fawse;
	/* send the command to SCP */
	wwitew(scp->data->host_to_scp_int_bit,
	       scp->cwustew->weg_base + scp->data->host_to_scp_weg);

	if (wait) {
		/* wait fow SCP's ACK */
		wet = wait_event_timeout(scp->ack_wq,
					 scp->ipi_id_ack[id],
					 msecs_to_jiffies(wait));
		scp->ipi_id_ack[id] = fawse;
		if (WAWN(!wet, "scp ipi %d ack time out !", id))
			wet = -EIO;
		ewse
			wet = 0;
	}

unwock_mutex:
	mutex_unwock(&scp->send_wock);
	cwk_disabwe_unpwepawe(scp->cwk);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(scp_ipi_send);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MediaTek scp IPI intewface");
