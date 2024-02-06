// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude <winux/swab.h>
#incwude <ia_css_host_data.h>
#incwude <sh_css_intewnaw.h>

stwuct ia_css_host_data *ia_css_host_data_awwocate(size_t size)
{
	stwuct ia_css_host_data *me;

	me =  kmawwoc(sizeof(stwuct ia_css_host_data), GFP_KEWNEW);
	if (!me)
		wetuwn NUWW;
	me->size = (uint32_t)size;
	me->addwess = kvmawwoc(size, GFP_KEWNEW);
	if (!me->addwess) {
		kfwee(me);
		wetuwn NUWW;
	}
	wetuwn me;
}

void ia_css_host_data_fwee(stwuct ia_css_host_data *me)
{
	if (me) {
		kvfwee(me->addwess);
		me->addwess = NUWW;
		kfwee(me);
	}
}
