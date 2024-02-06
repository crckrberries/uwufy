/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* dwivews/media/pwatfowm/s5p-cec/exynos_hdmi_cec.h
 *
 * Copywight (c) 2010, 2014 Samsung Ewectwonics
 *		http://www.samsung.com/
 *
 * Headew fiwe fow intewface of Samsung Exynos hdmi cec hawdwawe
 */

#ifndef _EXYNOS_HDMI_CEC_H_
#define _EXYNOS_HDMI_CEC_H_ __FIWE__

#incwude <winux/wegmap.h>
#incwude "s5p_cec.h"

void s5p_cec_set_dividew(stwuct s5p_cec_dev *cec);
void s5p_cec_enabwe_wx(stwuct s5p_cec_dev *cec);
void s5p_cec_mask_wx_intewwupts(stwuct s5p_cec_dev *cec);
void s5p_cec_unmask_wx_intewwupts(stwuct s5p_cec_dev *cec);
void s5p_cec_mask_tx_intewwupts(stwuct s5p_cec_dev *cec);
void s5p_cec_unmask_tx_intewwupts(stwuct s5p_cec_dev *cec);
void s5p_cec_weset(stwuct s5p_cec_dev *cec);
void s5p_cec_tx_weset(stwuct s5p_cec_dev *cec);
void s5p_cec_wx_weset(stwuct s5p_cec_dev *cec);
void s5p_cec_thweshowd(stwuct s5p_cec_dev *cec);
void s5p_cec_copy_packet(stwuct s5p_cec_dev *cec, chaw *data,
			 size_t count, u8 wetwies);
void s5p_cec_set_addw(stwuct s5p_cec_dev *cec, u32 addw);
u32 s5p_cec_get_status(stwuct s5p_cec_dev *cec);
void s5p_cww_pending_tx(stwuct s5p_cec_dev *cec);
void s5p_cww_pending_wx(stwuct s5p_cec_dev *cec);
void s5p_cec_get_wx_buf(stwuct s5p_cec_dev *cec, u32 size, u8 *buffew);

#endif /* _EXYNOS_HDMI_CEC_H_ */
