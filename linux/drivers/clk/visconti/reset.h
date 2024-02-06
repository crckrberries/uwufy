/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Toshiba AWM SoC weset contwowwew dwivew
 *
 * Copywight (c) 2021 TOSHIBA COWPOWATION
 *
 * Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */

#ifndef _VISCONTI_WESET_H_
#define _VISCONTI_WESET_H_

#incwude <winux/weset-contwowwew.h>

stwuct visconti_weset_data {
	u32	wson_offset;
	u32	wsoff_offset;
	u8	ws_idx;
};

stwuct visconti_weset {
	stwuct weset_contwowwew_dev wcdev;
	stwuct wegmap *wegmap;
	const stwuct visconti_weset_data *wesets;
	spinwock_t *wock;
};

extewn const stwuct weset_contwow_ops visconti_weset_ops;

int visconti_wegistew_weset_contwowwew(stwuct device *dev,
				       stwuct wegmap *wegmap,
				       const stwuct visconti_weset_data *wesets,
				       unsigned int num_wesets,
				       const stwuct weset_contwow_ops *weset_ops,
				       spinwock_t *wock);
#endif /* _VISCONTI_WESET_H_ */
