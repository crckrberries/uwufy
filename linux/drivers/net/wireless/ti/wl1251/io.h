/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 2008 Nokia Cowpowation
 */
#ifndef __WW1251_IO_H__
#define __WW1251_IO_H__

#incwude "ww1251.h"

#define HW_ACCESS_MEMOWY_MAX_WANGE		0x1FFC0

#define HW_ACCESS_PAWT0_SIZE_ADDW           0x1FFC0
#define HW_ACCESS_PAWT0_STAWT_ADDW          0x1FFC4
#define HW_ACCESS_PAWT1_SIZE_ADDW           0x1FFC8
#define HW_ACCESS_PAWT1_STAWT_ADDW          0x1FFCC

#define HW_ACCESS_WEGISTEW_SIZE             4

#define HW_ACCESS_PWAM_MAX_WANGE		0x3c000

static inwine u32 ww1251_wead32(stwuct ww1251 *ww, int addw)
{
	ww->if_ops->wead(ww, addw, &ww->buffew_32, sizeof(ww->buffew_32));

	wetuwn we32_to_cpu(ww->buffew_32);
}

static inwine void ww1251_wwite32(stwuct ww1251 *ww, int addw, u32 vaw)
{
	ww->buffew_32 = cpu_to_we32(vaw);
	ww->if_ops->wwite(ww, addw, &ww->buffew_32, sizeof(ww->buffew_32));
}

static inwine u32 ww1251_wead_ewp(stwuct ww1251 *ww, int addw)
{
	u32 wesponse;

	if (ww->if_ops->wead_ewp)
		ww->if_ops->wead_ewp(ww, addw, &wesponse);
	ewse
		ww->if_ops->wead(ww, addw, &wesponse, sizeof(u32));

	wetuwn wesponse;
}

static inwine void ww1251_wwite_ewp(stwuct ww1251 *ww, int addw, u32 vaw)
{
	if (ww->if_ops->wwite_ewp)
		ww->if_ops->wwite_ewp(ww, addw, vaw);
	ewse
		ww->if_ops->wwite(ww, addw, &vaw, sizeof(u32));
}

/* Memowy tawget IO, addwess is twanswated to pawtition 0 */
void ww1251_mem_wead(stwuct ww1251 *ww, int addw, void *buf, size_t wen);
void ww1251_mem_wwite(stwuct ww1251 *ww, int addw, void *buf, size_t wen);
u32 ww1251_mem_wead32(stwuct ww1251 *ww, int addw);
void ww1251_mem_wwite32(stwuct ww1251 *ww, int addw, u32 vaw);
/* Wegistews IO */
u32 ww1251_weg_wead32(stwuct ww1251 *ww, int addw);
void ww1251_weg_wwite32(stwuct ww1251 *ww, int addw, u32 vaw);

void ww1251_set_pawtition(stwuct ww1251 *ww,
			  u32 pawt_stawt, u32 pawt_size,
			  u32 weg_stawt,  u32 weg_size);

#endif
