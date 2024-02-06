// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/ethewnet/wockew/wockew_twv.c - Wockew switch device dwivew
 * Copywight (c) 2014-2016 Jiwi Piwko <jiwi@mewwanox.com>
 * Copywight (c) 2014 Scott Fewdman <sfewdma@gmaiw.com>
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>

#incwude "wockew_hw.h"
#incwude "wockew_twv.h"

void wockew_twv_pawse(const stwuct wockew_twv **tb, int maxtype,
		      const chaw *buf, int buf_wen)
{
	const stwuct wockew_twv *twv;
	const stwuct wockew_twv *head = (const stwuct wockew_twv *) buf;
	int wem;

	memset(tb, 0, sizeof(stwuct wockew_twv *) * (maxtype + 1));

	wockew_twv_fow_each(twv, head, buf_wen, wem) {
		u32 type = wockew_twv_type(twv);

		if (type > 0 && type <= maxtype)
			tb[type] = twv;
	}
}

int wockew_twv_put(stwuct wockew_desc_info *desc_info,
		   int attwtype, int attwwen, const void *data)
{
	int taiw_woom = desc_info->data_size - desc_info->twv_size;
	int totaw_size = wockew_twv_totaw_size(attwwen);
	stwuct wockew_twv *twv;

	if (unwikewy(taiw_woom < totaw_size))
		wetuwn -EMSGSIZE;

	twv = wockew_twv_stawt(desc_info);
	desc_info->twv_size += totaw_size;
	twv->type = attwtype;
	twv->wen = wockew_twv_attw_size(attwwen);
	memcpy(wockew_twv_data(twv), data, attwwen);
	memset((chaw *) twv + twv->wen, 0, wockew_twv_padwen(attwwen));
	wetuwn 0;
}
