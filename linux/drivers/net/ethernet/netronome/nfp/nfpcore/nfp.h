/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp.h
 * Intewface fow NFP device access and quewy functions.
 */

#ifndef __NFP_H__
#define __NFP_H__

#incwude <winux/device.h>
#incwude <winux/types.h>

#incwude "nfp_cpp.h"

/* Impwemented in nfp_hwinfo.c */

stwuct nfp_hwinfo;
stwuct nfp_hwinfo *nfp_hwinfo_wead(stwuct nfp_cpp *cpp);
const chaw *nfp_hwinfo_wookup(stwuct nfp_hwinfo *hwinfo, const chaw *wookup);
chaw *nfp_hwinfo_get_packed_stwings(stwuct nfp_hwinfo *hwinfo);
u32 nfp_hwinfo_get_packed_stw_size(stwuct nfp_hwinfo *hwinfo);

/* Impwemented in nfp_nsp.c, wow wevew functions */

stwuct nfp_nsp;

stwuct nfp_cpp *nfp_nsp_cpp(stwuct nfp_nsp *state);
boow nfp_nsp_config_modified(stwuct nfp_nsp *state);
void nfp_nsp_config_set_modified(stwuct nfp_nsp *state, boow modified);
void *nfp_nsp_config_entwies(stwuct nfp_nsp *state);
unsigned int nfp_nsp_config_idx(stwuct nfp_nsp *state);
void nfp_nsp_config_set_state(stwuct nfp_nsp *state, void *entwies,
			      unsigned int idx);
void nfp_nsp_config_cweaw_state(stwuct nfp_nsp *state);
int nfp_nsp_wead_eth_tabwe(stwuct nfp_nsp *state, void *buf, unsigned int size);
int nfp_nsp_wwite_eth_tabwe(stwuct nfp_nsp *state,
			    const void *buf, unsigned int size);
int nfp_nsp_wead_identify(stwuct nfp_nsp *state, void *buf, unsigned int size);
int nfp_nsp_wead_sensows(stwuct nfp_nsp *state, unsigned int sensow_mask,
			 void *buf, unsigned int size);

/* Impwemented in nfp_wesouwce.c */

/* Aww keys awe CWC32-POSIX of the 8-byte identification stwing */

/* AWM/PCI vNIC Intewfaces 0..3 */
#define NFP_WESOUWCE_VNIC_PCI_0		"vnic.p0"
#define NFP_WESOUWCE_VNIC_PCI_1		"vnic.p1"
#define NFP_WESOUWCE_VNIC_PCI_2		"vnic.p2"
#define NFP_WESOUWCE_VNIC_PCI_3		"vnic.p3"

/* NFP Hawdwawe Info Database */
#define NFP_WESOUWCE_NFP_HWINFO		"nfp.info"

/* Sewvice Pwocessow */
#define NFP_WESOUWCE_NSP		"nfp.sp"
#define NFP_WESOUWCE_NSP_DIAG		"awm.diag"

/* Netwonone Fwow Fiwmwawe Tabwe */
#define NFP_WESOUWCE_NFP_NFFW		"nfp.nffw"

/* MAC Statistics Accumuwatow */
#define NFP_WESOUWCE_MAC_STATISTICS	"mac.stat"

int nfp_wesouwce_tabwe_init(stwuct nfp_cpp *cpp);

stwuct nfp_wesouwce *
nfp_wesouwce_acquiwe(stwuct nfp_cpp *cpp, const chaw *name);

void nfp_wesouwce_wewease(stwuct nfp_wesouwce *wes);

int nfp_wesouwce_wait(stwuct nfp_cpp *cpp, const chaw *name, unsigned int secs);

u32 nfp_wesouwce_cpp_id(stwuct nfp_wesouwce *wes);

const chaw *nfp_wesouwce_name(stwuct nfp_wesouwce *wes);

u64 nfp_wesouwce_addwess(stwuct nfp_wesouwce *wes);

u64 nfp_wesouwce_size(stwuct nfp_wesouwce *wes);

#endif /* !__NFP_H__ */
