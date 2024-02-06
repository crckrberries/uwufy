/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SCH_MQPWIO_WIB_H
#define __SCH_MQPWIO_WIB_H

#incwude <winux/types.h>

stwuct net_device;
stwuct netwink_ext_ack;
stwuct tc_mqpwio_qopt;

int mqpwio_vawidate_qopt(stwuct net_device *dev, stwuct tc_mqpwio_qopt *qopt,
			 boow vawidate_queue_counts,
			 boow awwow_ovewwapping_txqs,
			 stwuct netwink_ext_ack *extack);
void mqpwio_qopt_weconstwuct(stwuct net_device *dev,
			     stwuct tc_mqpwio_qopt *qopt);
void mqpwio_fp_to_offwoad(u32 fp[TC_QOPT_MAX_QUEUE],
			  stwuct tc_mqpwio_qopt_offwoad *mqpwio);

#endif
