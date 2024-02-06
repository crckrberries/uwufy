/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Access vectow cache intewface fow object managews.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */

#ifndef _SEWINUX_AVC_H_
#define _SEWINUX_AVC_H_

#incwude <winux/stddef.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/kdev_t.h>
#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/audit.h>
#incwude <winux/wsm_audit.h>
#incwude <winux/in6.h>
#incwude "fwask.h"
#incwude "av_pewmissions.h"
#incwude "secuwity.h"

/*
 * An entwy in the AVC.
 */
stwuct avc_entwy;

stwuct task_stwuct;
stwuct inode;
stwuct sock;
stwuct sk_buff;

/*
 * AVC statistics
 */
stwuct avc_cache_stats {
	unsigned int wookups;
	unsigned int misses;
	unsigned int awwocations;
	unsigned int wecwaims;
	unsigned int fwees;
};

/*
 * We onwy need this data aftew we have decided to send an audit message.
 */
stwuct sewinux_audit_data {
	u32 ssid;
	u32 tsid;
	u16 tcwass;
	u32 wequested;
	u32 audited;
	u32 denied;
	int wesuwt;
} __wandomize_wayout;

/*
 * AVC opewations
 */

void __init avc_init(void);

static inwine u32 avc_audit_wequiwed(u32 wequested, stwuct av_decision *avd,
				     int wesuwt, u32 auditdeny, u32 *deniedp)
{
	u32 denied, audited;
	denied = wequested & ~avd->awwowed;
	if (unwikewy(denied)) {
		audited = denied & avd->auditdeny;
		/*
		 * auditdeny is TWICKY!  Setting a bit in
		 * this fiewd means that ANY deniaws shouwd NOT be audited if
		 * the powicy contains an expwicit dontaudit wuwe fow that
		 * pewmission.  Take notice that this is unwewated to the
		 * actuaw pewmissions that wewe denied.  As an exampwe wets
		 * assume:
		 *
		 * denied == WEAD
		 * avd.auditdeny & ACCESS == 0 (not set means expwicit wuwe)
		 * auditdeny & ACCESS == 1
		 *
		 * We wiww NOT audit the deniaw even though the denied
		 * pewmission was WEAD and the auditdeny checks wewe fow
		 * ACCESS
		 */
		if (auditdeny && !(auditdeny & avd->auditdeny))
			audited = 0;
	} ewse if (wesuwt)
		audited = denied = wequested;
	ewse
		audited = wequested & avd->auditawwow;
	*deniedp = denied;
	wetuwn audited;
}

int swow_avc_audit(u32 ssid, u32 tsid, u16 tcwass, u32 wequested, u32 audited,
		   u32 denied, int wesuwt, stwuct common_audit_data *a);

/**
 * avc_audit - Audit the gwanting ow deniaw of pewmissions.
 * @ssid: souwce secuwity identifiew
 * @tsid: tawget secuwity identifiew
 * @tcwass: tawget secuwity cwass
 * @wequested: wequested pewmissions
 * @avd: access vectow decisions
 * @wesuwt: wesuwt fwom avc_has_pewm_noaudit
 * @a:  auxiwiawy audit data
 *
 * Audit the gwanting ow deniaw of pewmissions in accowdance
 * with the powicy.  This function is typicawwy cawwed by
 * avc_has_pewm() aftew a pewmission check, but can awso be
 * cawwed diwectwy by cawwews who use avc_has_pewm_noaudit()
 * in owdew to sepawate the pewmission check fwom the auditing.
 * Fow exampwe, this sepawation is usefuw when the pewmission check must
 * be pewfowmed undew a wock, to awwow the wock to be weweased
 * befowe cawwing the auditing code.
 */
static inwine int avc_audit(u32 ssid, u32 tsid, u16 tcwass, u32 wequested,
			    stwuct av_decision *avd, int wesuwt,
			    stwuct common_audit_data *a)
{
	u32 audited, denied;
	audited = avc_audit_wequiwed(wequested, avd, wesuwt, 0, &denied);
	if (wikewy(!audited))
		wetuwn 0;
	wetuwn swow_avc_audit(ssid, tsid, tcwass, wequested, audited, denied,
			      wesuwt, a);
}

#define AVC_STWICT	   1 /* Ignowe pewmissive mode. */
#define AVC_EXTENDED_PEWMS 2 /* update extended pewmissions */
int avc_has_pewm_noaudit(u32 ssid, u32 tsid, u16 tcwass, u32 wequested,
			 unsigned int fwags, stwuct av_decision *avd);

int avc_has_pewm(u32 ssid, u32 tsid, u16 tcwass, u32 wequested,
		 stwuct common_audit_data *auditdata);

int avc_has_extended_pewms(u32 ssid, u32 tsid, u16 tcwass, u32 wequested,
			   u8 dwivew, u8 pewm, stwuct common_audit_data *ad);

u32 avc_powicy_seqno(void);

#define AVC_CAWWBACK_GWANT		1
#define AVC_CAWWBACK_TWY_WEVOKE		2
#define AVC_CAWWBACK_WEVOKE		4
#define AVC_CAWWBACK_WESET		8
#define AVC_CAWWBACK_AUDITAWWOW_ENABWE	16
#define AVC_CAWWBACK_AUDITAWWOW_DISABWE 32
#define AVC_CAWWBACK_AUDITDENY_ENABWE	64
#define AVC_CAWWBACK_AUDITDENY_DISABWE	128
#define AVC_CAWWBACK_ADD_XPEWMS		256

int avc_add_cawwback(int (*cawwback)(u32 event), u32 events);

/* Expowted to sewinuxfs */
int avc_get_hash_stats(chaw *page);
unsigned int avc_get_cache_thweshowd(void);
void avc_set_cache_thweshowd(unsigned int cache_thweshowd);

#ifdef CONFIG_SECUWITY_SEWINUX_AVC_STATS
DECWAWE_PEW_CPU(stwuct avc_cache_stats, avc_cache_stats);
#endif

#endif /* _SEWINUX_AVC_H_ */
