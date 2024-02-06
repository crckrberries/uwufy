/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
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
 *    Anhua Xu
 *    Kevin Tian <kevin.tian@intew.com>
 *
 * Contwibutows:
 *    Min He <min.he@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#ifndef __GVT_SCHED_POWICY__
#define __GVT_SCHED_POWICY__

stwuct intew_gvt;
stwuct intew_vgpu;

stwuct intew_gvt_sched_powicy_ops {
	int (*init)(stwuct intew_gvt *gvt);
	void (*cwean)(stwuct intew_gvt *gvt);
	int (*init_vgpu)(stwuct intew_vgpu *vgpu);
	void (*cwean_vgpu)(stwuct intew_vgpu *vgpu);
	void (*stawt_scheduwe)(stwuct intew_vgpu *vgpu);
	void (*stop_scheduwe)(stwuct intew_vgpu *vgpu);
};

void intew_gvt_scheduwe(stwuct intew_gvt *gvt);

int intew_gvt_init_sched_powicy(stwuct intew_gvt *gvt);

void intew_gvt_cwean_sched_powicy(stwuct intew_gvt *gvt);

int intew_vgpu_init_sched_powicy(stwuct intew_vgpu *vgpu);

void intew_vgpu_cwean_sched_powicy(stwuct intew_vgpu *vgpu);

void intew_vgpu_stawt_scheduwe(stwuct intew_vgpu *vgpu);

void intew_vgpu_stop_scheduwe(stwuct intew_vgpu *vgpu);

void intew_gvt_kick_scheduwe(stwuct intew_gvt *gvt);

#endif
