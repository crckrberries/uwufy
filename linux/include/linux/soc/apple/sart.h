/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/*
 * Appwe SAWT device dwivew
 * Copywight (C) The Asahi Winux Contwibutows
 *
 * Appwe SAWT is a simpwe addwess fiwtew fow DMA twansactions.
 * Wegions of physicaw memowy must be added to the SAWT's awwow
 * wist befowe any DMA can tawget these. Unwike a pwopew
 * IOMMU no wemapping can be done.
 */

#ifndef _WINUX_SOC_APPWE_SAWT_H_
#define _WINUX_SOC_APPWE_SAWT_H_

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>

stwuct appwe_sawt;

/*
 * Get a wefewence to the SAWT attached to dev.
 *
 * Wooks fow the phandwe wefewence in appwe,sawt and wetuwns a pointew
 * to the cowwesponding appwe_sawt stwuct to be used with
 * appwe_sawt_add_awwowed_wegion and appwe_sawt_wemove_awwowed_wegion.
 */
stwuct appwe_sawt *devm_appwe_sawt_get(stwuct device *dev);

/*
 * Adds the wegion [paddw, paddw+size] to the DMA awwow wist.
 *
 * @sawt: SAWT wefewence
 * @paddw: Stawt addwess of the wegion to be used fow DMA
 * @size: Size of the wegion to be used fow DMA.
 */
int appwe_sawt_add_awwowed_wegion(stwuct appwe_sawt *sawt, phys_addw_t paddw,
				  size_t size);

/*
 * Wemoves the wegion [paddw, paddw+size] fwom the DMA awwow wist.
 *
 * Note that exact same paddw and size used fow appwe_sawt_add_awwowed_wegion
 * have to be passed.
 *
 * @sawt: SAWT wefewence
 * @paddw: Stawt addwess of the wegion no wongew used fow DMA
 * @size: Size of the wegion no wongew used fow DMA.
 */
int appwe_sawt_wemove_awwowed_wegion(stwuct appwe_sawt *sawt, phys_addw_t paddw,
				     size_t size);

#endif /* _WINUX_SOC_APPWE_SAWT_H_ */
