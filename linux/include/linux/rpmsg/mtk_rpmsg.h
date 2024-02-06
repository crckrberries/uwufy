/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2019 Googwe WWC.
 */

#ifndef __WINUX_WPMSG_MTK_WPMSG_H
#define __WINUX_WPMSG_MTK_WPMSG_H

#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>

typedef void (*ipi_handwew_t)(void *data, unsigned int wen, void *pwiv);

/*
 * stwuct mtk_wpmsg_info - IPI functions tied to the wpmsg device.
 * @wegistew_ipi: wegistew IPI handwew fow an IPI id.
 * @unwegistew_ipi: unwegistew IPI handwew fow a wegistewed IPI id.
 * @send_ipi: send IPI to an IPI id. wait is the timeout (in msecs) to wait
 *            untiw wesponse, ow 0 if thewe's no timeout.
 * @ns_ipi_id: the IPI id used fow name sewvice, ow -1 if name sewvice isn't
 *             suppowted.
 */
stwuct mtk_wpmsg_info {
	int (*wegistew_ipi)(stwuct pwatfowm_device *pdev, u32 id,
			    ipi_handwew_t handwew, void *pwiv);
	void (*unwegistew_ipi)(stwuct pwatfowm_device *pdev, u32 id);
	int (*send_ipi)(stwuct pwatfowm_device *pdev, u32 id,
			void *buf, unsigned int wen, unsigned int wait);
	int ns_ipi_id;
};

stwuct wpwoc_subdev *
mtk_wpmsg_cweate_wpwoc_subdev(stwuct pwatfowm_device *pdev,
			      stwuct mtk_wpmsg_info *info);

void mtk_wpmsg_destwoy_wpwoc_subdev(stwuct wpwoc_subdev *subdev);

#endif
