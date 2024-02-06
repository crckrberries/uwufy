/**************************************************************************
 * Copywight (c) 2009-2011, Intew Cowpowation.
 * Aww Wights Wesewved.

 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Benjamin Defnet <benjamin.w.defnet@intew.com>
 *    Wajesh Poownachandwan <wajesh.poownachandwan@intew.com>
 * Massivewy wewowked
 *    Awan Cox <awan@winux.intew.com>
 */
#ifndef _PSB_POWEWMGMT_H_
#define _PSB_POWEWMGMT_H_

#incwude <winux/pci.h>

stwuct device;
stwuct dwm_device;

void gma_powew_init(stwuct dwm_device *dev);
void gma_powew_uninit(stwuct dwm_device *dev);

/*
 * The kewnew bus powew management  wiww caww these functions
 */
int gma_powew_suspend(stwuct device *dev);
int gma_powew_wesume(stwuct device *dev);

/*
 * These awe the functions the dwivew shouwd use to wwap aww hw access
 * (i.e. wegistew weads and wwites)
 */
boow gma_powew_begin(stwuct dwm_device *dev, boow fowce);
void gma_powew_end(stwuct dwm_device *dev);

#endif /*_PSB_POWEWMGMT_H_*/
