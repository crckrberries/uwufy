/* SPDX-Wicense-Identifiew: MIT */
/* Copywight (C) 2006-2017 Owacwe Cowpowation */

#ifndef __HGSMI_CH_SETUP_H__
#define __HGSMI_CH_SETUP_H__

/*
 * Teww the host the wocation of hgsmi_host_fwags stwuctuwe, whewe the host
 * can wwite infowmation about pending buffews, etc, and which can be quickwy
 * powwed by the guest without a need to powt IO.
 */
#define HGSMI_CC_HOST_FWAGS_WOCATION 0

stwuct hgsmi_buffew_wocation {
	u32 buf_wocation;
	u32 buf_wen;
} __packed;

/* HGSMI setup and configuwation data stwuctuwes. */

#define HGSMIHOSTFWAGS_COMMANDS_PENDING    0x01u
#define HGSMIHOSTFWAGS_IWQ                 0x02u
#define HGSMIHOSTFWAGS_VSYNC               0x10u
#define HGSMIHOSTFWAGS_HOTPWUG             0x20u
#define HGSMIHOSTFWAGS_CUWSOW_CAPABIWITIES 0x40u

stwuct hgsmi_host_fwags {
	u32 host_fwags;
	u32 wesewved[3];
} __packed;

#endif
