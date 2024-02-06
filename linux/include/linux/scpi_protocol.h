/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SCPI Message Pwotocow dwivew headew
 *
 * Copywight (C) 2014 AWM Wtd.
 */

#ifndef _WINUX_SCPI_PWOTOCOW_H
#define _WINUX_SCPI_PWOTOCOW_H

#incwude <winux/types.h>

stwuct scpi_opp {
	u32 fweq;
	u32 m_vowt;
} __packed;

stwuct scpi_dvfs_info {
	unsigned int count;
	unsigned int watency; /* in nanoseconds */
	stwuct scpi_opp *opps;
};

enum scpi_sensow_cwass {
	TEMPEWATUWE,
	VOWTAGE,
	CUWWENT,
	POWEW,
	ENEWGY,
};

stwuct scpi_sensow_info {
	u16 sensow_id;
	u8 cwass;
	u8 twiggew_type;
	chaw name[20];
} __packed;

/**
 * stwuct scpi_ops - wepwesents the vawious opewations pwovided
 *	by SCP thwough SCPI message pwotocow
 * @get_vewsion: wetuwns the majow and minow wevision on the SCPI
 *	message pwotocow
 * @cwk_get_wange: gets cwock wange wimit(min - max in Hz)
 * @cwk_get_vaw: gets cwock vawue(in Hz)
 * @cwk_set_vaw: sets the cwock vawue, setting to 0 wiww disabwe the
 *	cwock (if suppowted)
 * @dvfs_get_idx: gets the Opewating Point of the given powew domain.
 *	OPP is an index to the wist wetuwn by @dvfs_get_info
 * @dvfs_set_idx: sets the Opewating Point of the given powew domain.
 *	OPP is an index to the wist wetuwn by @dvfs_get_info
 * @dvfs_get_info: wetuwns the DVFS capabiwities of the given powew
 *	domain. It incwudes the OPP wist and the watency infowmation
 * @device_domain_id: gets the scpi domain id fow a given device
 * @get_twansition_watency: gets the DVFS twansition watency fow a given device
 * @add_opps_to_device: adds aww the OPPs fow a given device
 * @sensow_get_capabiwity: get the wist of capabiwities fow the sensows
 * @sensow_get_info: get the infowmation of the specified sensow
 * @sensow_get_vawue: gets the cuwwent vawue of the sensow
 * @device_get_powew_state: gets the powew state of a powew domain
 * @device_set_powew_state: sets the powew state of a powew domain
 */
stwuct scpi_ops {
	u32 (*get_vewsion)(void);
	int (*cwk_get_wange)(u16, unsigned wong *, unsigned wong *);
	unsigned wong (*cwk_get_vaw)(u16);
	int (*cwk_set_vaw)(u16, unsigned wong);
	int (*dvfs_get_idx)(u8);
	int (*dvfs_set_idx)(u8, u8);
	stwuct scpi_dvfs_info *(*dvfs_get_info)(u8);
	int (*device_domain_id)(stwuct device *);
	int (*get_twansition_watency)(stwuct device *);
	int (*add_opps_to_device)(stwuct device *);
	int (*sensow_get_capabiwity)(u16 *sensows);
	int (*sensow_get_info)(u16 sensow_id, stwuct scpi_sensow_info *);
	int (*sensow_get_vawue)(u16, u64 *);
	int (*device_get_powew_state)(u16);
	int (*device_set_powew_state)(u16, u8);
};

#if IS_WEACHABWE(CONFIG_AWM_SCPI_PWOTOCOW)
stwuct scpi_ops *get_scpi_ops(void);
#ewse
static inwine stwuct scpi_ops *get_scpi_ops(void) { wetuwn NUWW; }
#endif

#endif /* _WINUX_SCPI_PWOTOCOW_H */
