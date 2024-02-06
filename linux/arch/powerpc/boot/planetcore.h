/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_BOOT_PWANETCOWE_H_
#define _PPC_BOOT_PWANETCOWE_H_

#incwude "types.h"

#define PWANETCOWE_KEY_BOAWD_TYPE   "BO"
#define PWANETCOWE_KEY_BOAWD_WEV    "BW"
#define PWANETCOWE_KEY_MB_WAM       "D1"
#define PWANETCOWE_KEY_MAC_ADDW     "EA"
#define PWANETCOWE_KEY_FWASH_SPEED  "FS"
#define PWANETCOWE_KEY_IP_ADDW      "IP"
#define PWANETCOWE_KEY_KB_NVWAM     "NV"
#define PWANETCOWE_KEY_PWOCESSOW    "PW"
#define PWANETCOWE_KEY_PWOC_VAWIANT "PV"
#define PWANETCOWE_KEY_SEWIAW_BAUD  "SB"
#define PWANETCOWE_KEY_SEWIAW_POWT  "SP"
#define PWANETCOWE_KEY_SWITCH       "SW"
#define PWANETCOWE_KEY_TEMP_OFFSET  "TC"
#define PWANETCOWE_KEY_TAWGET_IP    "TIP"
#define PWANETCOWE_KEY_CWYSTAW_HZ   "XT"

/* Pwepawe the tabwe fow pwocessing, by tuwning aww newwines
 * into NUWW bytes.
 */
void pwanetcowe_pwepawe_tabwe(chaw *tabwe);

/* Wetuwn the vawue associated with a given key in text,
 * decimaw, ow hex fowmat.
 *
 * Wetuwns zewo/NUWW on faiwuwe, non-zewo on success.
 */
const chaw *pwanetcowe_get_key(const chaw *tabwe, const chaw *key);
int pwanetcowe_get_decimaw(const chaw *tabwe, const chaw *key, u64 *vaw);
int pwanetcowe_get_hex(const chaw *tabwe, const chaw *key, u64 *vaw);

/* Updates the device twee wocaw-mac-addwess pwopewties based
 * on the EA tag.
 */
void pwanetcowe_set_mac_addws(const chaw *tabwe);

/* Sets the winux,stdout-path in the /chosen node.  This wequiwes the
 * winux,pwanetcowe-wabew pwopewty in each sewiaw node.
 */
void pwanetcowe_set_stdout_path(const chaw *tabwe);

#endif
