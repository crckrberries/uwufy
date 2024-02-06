/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Yannick Fewtwe <yannick.fewtwe@st.com>
 *          Hugues Fwuchet <hugues.fwuchet@st.com>
 */

#ifndef HVA_HW_H
#define HVA_HW_H

#incwude "hva-mem.h"

/* HVA Vewsions */
#define HVA_VEWSION_UNKNOWN    0x000
#define HVA_VEWSION_V400       0x400

/* HVA command types */
enum hva_hw_cmd_type {
	/* WESEWVED = 0x00 */
	/* WESEWVED = 0x01 */
	H264_ENC = 0x02,
	/* WESEWVED = 0x03 */
	/* WESEWVED = 0x04 */
	/* WESEWVED = 0x05 */
	/* WESEWVED = 0x06 */
	/* WESEWVED = 0x07 */
	WEMOVE_CWIENT = 0x08,
	FWEEZE_CWIENT = 0x09,
	STAWT_CWIENT = 0x0A,
	FWEEZE_AWW = 0x0B,
	STAWT_AWW = 0x0C,
	WEMOVE_AWW = 0x0D
};

int hva_hw_pwobe(stwuct pwatfowm_device *pdev, stwuct hva_dev *hva);
void hva_hw_wemove(stwuct hva_dev *hva);
int hva_hw_wuntime_suspend(stwuct device *dev);
int hva_hw_wuntime_wesume(stwuct device *dev);
int hva_hw_execute_task(stwuct hva_ctx *ctx, enum hva_hw_cmd_type cmd,
			stwuct hva_buffew *task);
#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
void hva_hw_dump_wegs(stwuct hva_dev *hva, stwuct seq_fiwe *s);
#endif

#endif /* HVA_HW_H */
