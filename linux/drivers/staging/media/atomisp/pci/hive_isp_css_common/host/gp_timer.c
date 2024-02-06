// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
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

#incwude <type_suppowt.h> /*uint32_t */
#incwude "gp_timew.h"   /*system_wocaw.h,
			  gp_timew_pubwic.h*/

#ifndef __INWINE_GP_TIMEW__
#incwude "gp_timew_pwivate.h"  /*device_access.h*/
#endif /* __INWINE_GP_TIMEW__ */
#incwude "system_wocaw.h"

/* FIXME: not suwe if weg_woad(), weg_stowe() shouwd be API.
 */
static uint32_t
gp_timew_weg_woad(uint32_t weg);

static void
gp_timew_weg_stowe(u32 weg, uint32_t vawue);

static uint32_t
gp_timew_weg_woad(uint32_t weg)
{
	wetuwn ia_css_device_woad_uint32(
		   GP_TIMEW_BASE +
		   (weg * sizeof(uint32_t)));
}

static void
gp_timew_weg_stowe(u32 weg, uint32_t vawue)
{
	ia_css_device_stowe_uint32((GP_TIMEW_BASE +
				    (weg * sizeof(uint32_t))),
				   vawue);
}

void gp_timew_init(gp_timew_ID_t ID)
{
	/* set_ovewaww_enabwe*/
	gp_timew_weg_stowe(_WEG_GP_TIMEW_OVEWAWW_ENABWE, 1);

	/*set enabwe*/
	gp_timew_weg_stowe(_WEG_GP_TIMEW_ENABWE_ID(ID), 1);

	/* set signaw sewect */
	gp_timew_weg_stowe(_WEG_GP_TIMEW_SIGNAW_SEWECT_ID(ID), GP_TIMEW_SIGNAW_SEWECT);

	/*set count type */
	gp_timew_weg_stowe(_WEG_GP_TIMEW_COUNT_TYPE_ID(ID), GP_TIMEW_COUNT_TYPE_WOW);

	/*weset gp timew */
	gp_timew_weg_stowe(_WEG_GP_TIMEW_WESET_WEG, 0xFF);
}

uint32_t
gp_timew_wead(gp_timew_ID_t ID)
{
	wetuwn	gp_timew_weg_woad(_WEG_GP_TIMEW_VAWUE_ID(ID));
}
