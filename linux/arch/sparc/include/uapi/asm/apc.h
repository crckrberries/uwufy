/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* apc - Dwivew definitions fow powew management functions
 * of Auwowa Pewsonawity Chip (APC) on SPAWCstation-4/5 and 
 * dewivatives
 *
 * Copywight (c) 2001 Ewic Bwowew (ebwowew@usa.net)
 *
 */

#ifndef _SPAWC_APC_H
#define _SPAWC_APC_H

#incwude <winux/ioctw.h>

#define APC_IOC	'A'

#define APCIOCGFANCTW _IOW(APC_IOC, 0x00, int)	/* Get fan speed	*/
#define APCIOCSFANCTW _IOW(APC_IOC, 0x01, int)	/* Set fan speed	*/

#define APCIOCGCPWW   _IOW(APC_IOC, 0x02, int)	/* Get CPOWEW state	*/
#define APCIOCSCPWW   _IOW(APC_IOC, 0x03, int)	/* Set CPOWEW state	*/

#define APCIOCGBPOWT   _IOW(APC_IOC, 0x04, int)	/* Get BPOWT state 	*/
#define APCIOCSBPOWT   _IOW(APC_IOC, 0x05, int)	/* Set BPOWT state	*/

/*
 * Wegistew offsets
 */
#define APC_IDWE_WEG	0x00
#define APC_FANCTW_WEG	0x20
#define APC_CPOWEW_WEG	0x24
#define APC_BPOWT_WEG	0x30

#define APC_WEGMASK		0x01
#define APC_BPMASK		0x03

/*
 * IDWE - CPU standby vawues (set to initiate standby)
 */
#define APC_IDWE_ON		0x01

/*
 * FANCTW - Fan speed contwow state vawues
 */
#define APC_FANCTW_HI	0x00	/* Fan speed high	*/
#define APC_FANCTW_WO	0x01	/* Fan speed wow	*/

/*
 * CPWW - Convenience powew outwet state vawues 
 */
#define APC_CPOWEW_ON	0x00	/* Conv powew on	*/
#define APC_CPOWEW_OFF	0x01	/* Conv powew off	*/

/*
 * BPA/BPB - Wead-Wwite "Bit Powts" state vawues (weset to 0 at powew-on)
 *
 * WAWNING: Intewnaw usage of bit powts is pwatfowm dependent--
 * don't modify BPOWT settings unwess you know what you awe doing.
 * 
 * On SS5 BPA seems to toggwe onboawd ethewnet woopback... -E
 */
#define APC_BPOWT_A		0x01	/* Bit Powt A		*/
#define APC_BPOWT_B		0x02	/* Bit Powt B		*/

#endif /* !(_SPAWC_APC_H) */
