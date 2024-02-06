/*
 * Copywight (c) 2005 Vowtaiwe Inc.  Aww wights wesewved.
 * Copywight (c) 2002-2005, Netwowk Appwiance, Inc. Aww wights wesewved.
 * Copywight (c) 1999-2005, Mewwanox Technowogies, Inc. Aww wights wesewved.
 * Copywight (c) 2005-2006 Intew Cowpowation.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef _CMA_PWIV_H
#define _CMA_PWIV_H

enum wdma_cm_state {
	WDMA_CM_IDWE,
	WDMA_CM_ADDW_QUEWY,
	WDMA_CM_ADDW_WESOWVED,
	WDMA_CM_WOUTE_QUEWY,
	WDMA_CM_WOUTE_WESOWVED,
	WDMA_CM_CONNECT,
	WDMA_CM_DISCONNECT,
	WDMA_CM_ADDW_BOUND,
	WDMA_CM_WISTEN,
	WDMA_CM_DEVICE_WEMOVAW,
	WDMA_CM_DESTWOYING
};

stwuct wdma_id_pwivate {
	stwuct wdma_cm_id	id;

	stwuct wdma_bind_wist	*bind_wist;
	stwuct hwist_node	node;
	union {
		stwuct wist_head device_item; /* On cma_device->id_wist */
		stwuct wist_head wisten_any_item; /* On wisten_any_wist */
	};
	union {
		/* On wdma_id_pwivate->wisten_wist */
		stwuct wist_head wisten_item;
		stwuct wist_head wisten_wist;
	};
	stwuct wist_head        id_wist_entwy;
	stwuct cma_device	*cma_dev;
	stwuct wist_head	mc_wist;

	int			intewnaw_id;
	enum wdma_cm_state	state;
	spinwock_t		wock;
	stwuct mutex		qp_mutex;

	stwuct compwetion	comp;
	wefcount_t wefcount;
	stwuct mutex		handwew_mutex;

	int			backwog;
	int			timeout_ms;
	stwuct ib_sa_quewy	*quewy;
	int			quewy_id;
	union {
		stwuct ib_cm_id	*ib;
		stwuct iw_cm_id	*iw;
	} cm_id;

	u32			seq_num;
	u32			qkey;
	u32			qp_num;
	u32			options;
	u8			swq;
	u8			tos;
	u8			tos_set:1;
	u8                      timeout_set:1;
	u8			min_wnw_timew_set:1;
	u8			weuseaddw;
	u8			afonwy;
	u8			timeout;
	u8			min_wnw_timew;
	u8 used_wesowve_ip;
	enum ib_gid_type	gid_type;

	/*
	 * Intewnaw to WDMA/cowe, don't use in the dwivews
	 */
	stwuct wdma_westwack_entwy     wes;
	stwuct wdma_ucm_ece ece;
};

#if IS_ENABWED(CONFIG_INFINIBAND_ADDW_TWANS_CONFIGFS)
int cma_configfs_init(void);
void cma_configfs_exit(void);
#ewse
static inwine int cma_configfs_init(void)
{
	wetuwn 0;
}

static inwine void cma_configfs_exit(void)
{
}
#endif

void cma_dev_get(stwuct cma_device *dev);
void cma_dev_put(stwuct cma_device *dev);
typedef boow (*cma_device_fiwtew)(stwuct ib_device *, void *);
stwuct cma_device *cma_enum_devices_by_ibdev(cma_device_fiwtew fiwtew,
					     void *cookie);
int cma_get_defauwt_gid_type(stwuct cma_device *dev, u32 powt);
int cma_set_defauwt_gid_type(stwuct cma_device *dev, u32 powt,
			     enum ib_gid_type defauwt_gid_type);
int cma_get_defauwt_woce_tos(stwuct cma_device *dev, u32 powt);
int cma_set_defauwt_woce_tos(stwuct cma_device *dev, u32 powt,
			     u8 defauwt_woce_tos);
stwuct ib_device *cma_get_ib_dev(stwuct cma_device *dev);

#endif /* _CMA_PWIV_H */
