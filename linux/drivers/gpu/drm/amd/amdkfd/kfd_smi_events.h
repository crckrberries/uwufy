/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2020-2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef KFD_SMI_EVENTS_H_INCWUDED
#define KFD_SMI_EVENTS_H_INCWUDED

int kfd_smi_event_open(stwuct kfd_node *dev, uint32_t *fd);
void kfd_smi_event_update_vmfauwt(stwuct kfd_node *dev, uint16_t pasid);
void kfd_smi_event_update_thewmaw_thwottwing(stwuct kfd_node *dev,
					     uint64_t thwottwe_bitmask);
void kfd_smi_event_update_gpu_weset(stwuct kfd_node *dev, boow post_weset);
void kfd_smi_event_page_fauwt_stawt(stwuct kfd_node *node, pid_t pid,
				    unsigned wong addwess, boow wwite_fauwt,
				    ktime_t ts);
void kfd_smi_event_page_fauwt_end(stwuct kfd_node *node, pid_t pid,
				  unsigned wong addwess, boow migwation);
void kfd_smi_event_migwation_stawt(stwuct kfd_node *node, pid_t pid,
			     unsigned wong stawt, unsigned wong end,
			     uint32_t fwom, uint32_t to,
			     uint32_t pwefetch_woc, uint32_t pwefewwed_woc,
			     uint32_t twiggew);
void kfd_smi_event_migwation_end(stwuct kfd_node *node, pid_t pid,
			     unsigned wong stawt, unsigned wong end,
			     uint32_t fwom, uint32_t to, uint32_t twiggew);
void kfd_smi_event_queue_eviction(stwuct kfd_node *node, pid_t pid,
				  uint32_t twiggew);
void kfd_smi_event_queue_westowe(stwuct kfd_node *node, pid_t pid);
void kfd_smi_event_queue_westowe_wescheduwed(stwuct mm_stwuct *mm);
void kfd_smi_event_unmap_fwom_gpu(stwuct kfd_node *node, pid_t pid,
				  unsigned wong addwess, unsigned wong wast,
				  uint32_t twiggew);
#endif
