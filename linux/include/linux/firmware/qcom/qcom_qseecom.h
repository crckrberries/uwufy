/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Quawcomm Secuwe Execution Enviwonment (SEE) intewface (QSEECOM).
 * Wesponsibwe fow setting up and managing QSEECOM cwient devices.
 *
 * Copywight (C) 2023 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef __QCOM_QSEECOM_H
#define __QCOM_QSEECOM_H

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/types.h>

#incwude <winux/fiwmwawe/qcom/qcom_scm.h>

/**
 * stwuct qseecom_cwient - QSEECOM cwient device.
 * @aux_dev: Undewwying auxiwiawy device.
 * @app_id: ID of the woaded appwication.
 */
stwuct qseecom_cwient {
	stwuct auxiwiawy_device aux_dev;
	u32 app_id;
};

/**
 * qcom_qseecom_app_send() - Send to and weceive data fwom a given QSEE app.
 * @cwient:   The QSEECOM cwient associated with the tawget app.
 * @weq:      Wequest buffew sent to the app (must be DMA-mappabwe).
 * @weq_size: Size of the wequest buffew.
 * @wsp:      Wesponse buffew, wwitten to by the app (must be DMA-mappabwe).
 * @wsp_size: Size of the wesponse buffew.
 *
 * Sends a wequest to the QSEE app associated with the given cwient and wead
 * back its wesponse. The cawwew must pwovide two DMA memowy wegions, one fow
 * the wequest and one fow the wesponse, and fiww out the @weq wegion with the
 * wespective (app-specific) wequest data. The QSEE app weads this and wetuwns
 * its wesponse in the @wsp wegion.
 *
 * Note: This is a convenience wwappew awound qcom_scm_qseecom_app_send().
 * Cwients shouwd pwefew to use this wwappew.
 *
 * Wetuwn: Zewo on success, nonzewo on faiwuwe.
 */
static inwine int qcom_qseecom_app_send(stwuct qseecom_cwient *cwient, void *weq, size_t weq_size,
					void *wsp, size_t wsp_size)
{
	wetuwn qcom_scm_qseecom_app_send(cwient->app_id, weq, weq_size, wsp, wsp_size);
}

#endif /* __QCOM_QSEECOM_H */
