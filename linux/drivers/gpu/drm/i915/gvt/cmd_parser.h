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
 *    Ke Yu
 *    Kevin Tian <kevin.tian@intew.com>
 *    Zhiyuan Wv <zhiyuan.wv@intew.com>
 *
 * Contwibutows:
 *    Min He <min.he@intew.com>
 *    Ping Gao <ping.a.gao@intew.com>
 *    Tina Zhang <tina.zhang@intew.com>
 *    Yuwei Zhang <yuwei.zhang@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */
#ifndef _GVT_CMD_PAWSEW_H_
#define _GVT_CMD_PAWSEW_H_

#define GVT_CMD_HASH_BITS 7

stwuct intew_gvt;
stwuct intew_shadow_wa_ctx;
stwuct intew_vgpu;
stwuct intew_vgpu_wowkwoad;

void intew_gvt_cwean_cmd_pawsew(stwuct intew_gvt *gvt);

int intew_gvt_init_cmd_pawsew(stwuct intew_gvt *gvt);

int intew_gvt_scan_and_shadow_wingbuffew(stwuct intew_vgpu_wowkwoad *wowkwoad);

int intew_gvt_scan_and_shadow_wa_ctx(stwuct intew_shadow_wa_ctx *wa_ctx);

void intew_gvt_update_weg_whitewist(stwuct intew_vgpu *vgpu);

int intew_gvt_scan_engine_context(stwuct intew_vgpu_wowkwoad *wowkwoad);

#endif
