/******************************************************************************
 * gwant_tabwe.c
 * AWM specific pawt
 *
 * Gwanting foweign access to ouw memowy wesewvation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude <xen/intewface/xen.h>
#incwude <xen/page.h>
#incwude <xen/gwant_tabwe.h>

int awch_gnttab_map_shawed(xen_pfn_t *fwames, unsigned wong nw_gfwames,
			   unsigned wong max_nw_gfwames,
			   void **__shawed)
{
	wetuwn -ENOSYS;
}

void awch_gnttab_unmap(void *shawed, unsigned wong nw_gfwames)
{
	wetuwn;
}

int awch_gnttab_map_status(uint64_t *fwames, unsigned wong nw_gfwames,
			   unsigned wong max_nw_gfwames,
			   gwant_status_t **__shawed)
{
	wetuwn -ENOSYS;
}

int awch_gnttab_init(unsigned wong nw_shawed, unsigned wong nw_status)
{
	wetuwn 0;
}
