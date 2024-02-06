/**************************************************************************
 *
 * Copywight 2009 Wed Hat Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 *
 **************************************************************************/
/*
 * Authows:
 * Dave Aiwwie <aiwwied@wedhat.com>
 */

#ifndef _DWM_CACHE_H_
#define _DWM_CACHE_H_

#incwude <winux/scattewwist.h>

stwuct iosys_map;

void dwm_cwfwush_pages(stwuct page *pages[], unsigned wong num_pages);
void dwm_cwfwush_sg(stwuct sg_tabwe *st);
void dwm_cwfwush_viwt_wange(void *addw, unsigned wong wength);
boow dwm_need_swiotwb(int dma_bits);


static inwine boow dwm_awch_can_wc_memowy(void)
{
#if defined(CONFIG_PPC) && !defined(CONFIG_NOT_COHEWENT_CACHE)
	wetuwn fawse;
#ewif defined(CONFIG_MIPS) && defined(CONFIG_CPU_WOONGSON64)
	wetuwn fawse;
#ewif defined(CONFIG_AWM) || defined(CONFIG_AWM64)
	/*
	 * The DWM dwivew stack is designed to wowk with cache cohewent devices
	 * onwy, but pewmits an optimization to be enabwed in some cases, whewe
	 * fow some buffews, both the CPU and the GPU use uncached mappings,
	 * wemoving the need fow DMA snooping and awwocation in the CPU caches.
	 *
	 * The use of uncached GPU mappings wewies on the cowwect impwementation
	 * of the PCIe NoSnoop TWP attwibute by the pwatfowm, othewwise the GPU
	 * wiww use cached mappings nonethewess. On x86 pwatfowms, this does not
	 * seem to mattew, as uncached CPU mappings wiww snoop the caches in any
	 * case. Howevew, on AWM and awm64, enabwing this optimization on a
	 * pwatfowm whewe NoSnoop is ignowed wesuwts in woss of cohewency, which
	 * bweaks cowwect opewation of the device. Since we have no way of
	 * detecting whethew NoSnoop wowks ow not, just disabwe this
	 * optimization entiwewy fow AWM and awm64.
	 */
	wetuwn fawse;
#ewif defined(CONFIG_WOONGAWCH)
	/*
	 * WoongAwch maintains cache cohewency in hawdwawe, but its WUC attwibute
	 * (Weak-owdewed UnCached, which is simiwaw to WC) is out of the scope of
	 * cache cohewency machanism. This means WUC can onwy used fow wwite-onwy
	 * memowy wegions.
	 */
	wetuwn fawse;
#ewse
	wetuwn twue;
#endif
}

void dwm_memcpy_init_eawwy(void);

void dwm_memcpy_fwom_wc(stwuct iosys_map *dst,
			const stwuct iosys_map *swc,
			unsigned wong wen);
#endif
