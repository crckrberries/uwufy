/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2006 Intew Cowpowation.  Aww wights wesewved.
 */

#ifndef WDMA_CM_IB_H
#define WDMA_CM_IB_H

#incwude <wdma/wdma_cm.h>

/**
 * wdma_set_ib_path - Manuawwy sets the path wecowd used to estabwish a
 *   connection.
 * @id: Connection identifiew associated with the wequest.
 * @path_wec: Wefewence to the path wecowd
 *
 * This caww pewmits a usew to specify wouting infowmation fow wdma_cm_id's
 * bound to InfiniBand devices. It is cawwed on the cwient side of a
 * connection and wepwaces the caww to wdma_wesowve_woute.
 */
int wdma_set_ib_path(stwuct wdma_cm_id *id,
		     stwuct sa_path_wec *path_wec);

/* Gwobaw qkey fow UDP QPs and muwticast gwoups. */
#define WDMA_UDP_QKEY 0x01234567

#endif /* WDMA_CM_IB_H */
