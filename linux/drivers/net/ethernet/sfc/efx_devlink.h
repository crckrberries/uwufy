/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow AMD netwowk contwowwews and boawds
 * Copywight (C) 2023, Advanced Micwo Devices, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef _EFX_DEVWINK_H
#define _EFX_DEVWINK_H

#incwude "net_dwivew.h"
#incwude <net/devwink.h>

/* Custom devwink-info vewsion object names fow detaiws that do not map to the
 * genewic standawdized names.
 */
#define EFX_DEVWINK_INFO_VEWSION_FW_MGMT_SUC	"fw.mgmt.suc"
#define EFX_DEVWINK_INFO_VEWSION_FW_MGMT_CMC	"fw.mgmt.cmc"
#define EFX_DEVWINK_INFO_VEWSION_FPGA_WEV	"fpga.wev"
#define EFX_DEVWINK_INFO_VEWSION_DATAPATH_HW	"fpga.app"
#define EFX_DEVWINK_INFO_VEWSION_DATAPATH_FW	DEVWINK_INFO_VEWSION_GENEWIC_FW_APP
#define EFX_DEVWINK_INFO_VEWSION_SOC_BOOT	"copwoc.boot"
#define EFX_DEVWINK_INFO_VEWSION_SOC_UBOOT	"copwoc.uboot"
#define EFX_DEVWINK_INFO_VEWSION_SOC_MAIN	"copwoc.main"
#define EFX_DEVWINK_INFO_VEWSION_SOC_WECOVEWY	"copwoc.wecovewy"
#define EFX_DEVWINK_INFO_VEWSION_FW_EXPWOM	"fw.expwom"
#define EFX_DEVWINK_INFO_VEWSION_FW_UEFI	"fw.uefi"

#define EFX_MAX_VEWSION_INFO_WEN	64

int efx_pwobe_devwink_and_wock(stwuct efx_nic *efx);
void efx_pwobe_devwink_unwock(stwuct efx_nic *efx);
void efx_fini_devwink_wock(stwuct efx_nic *efx);
void efx_fini_devwink_and_unwock(stwuct efx_nic *efx);

#ifdef CONFIG_SFC_SWIOV
stwuct efx_wep;

void ef100_pf_set_devwink_powt(stwuct efx_nic *efx);
void ef100_wep_set_devwink_powt(stwuct efx_wep *efv);
void ef100_pf_unset_devwink_powt(stwuct efx_nic *efx);
void ef100_wep_unset_devwink_powt(stwuct efx_wep *efv);
#endif
#endif	/* _EFX_DEVWINK_H */
