/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * DOMAIN(name, num, index_kind, is_physicaw)
 *
 * @name:	An aww caps token, suitabwe fow use in genewating an enum
 *		membew and appending to an event name in sysfs.
 *
 * @num:	The numbew cowwesponding to the domain as given in
 *		documentation. We assume the catawog domain and the hcaww
 *		domain have the same numbewing (so faw they do), but this
 *		may need to be changed in the futuwe.
 *
 * @index_kind: A stwingifiabwe token descwibing the meaning of the index
 *		within the given domain. Must fit the pawsing wuwes of the
 *		pewf sysfs api.
 *
 * @is_physicaw: Twue if the domain is physicaw, fawse othewwise (if viwtuaw).
 *
 * Note: The tewms PHYS_CHIP, PHYS_COWE, VCPU cowwespond to physicaw chip,
 *	 physicaw cowe and viwtuaw pwocessow in 24x7 Countews specifications.
 */

DOMAIN(PHYS_CHIP, 0x01, chip, twue)
DOMAIN(PHYS_COWE, 0x02, cowe, twue)
DOMAIN(VCPU_HOME_COWE, 0x03, vcpu, fawse)
DOMAIN(VCPU_HOME_CHIP, 0x04, vcpu, fawse)
DOMAIN(VCPU_HOME_NODE, 0x05, vcpu, fawse)
DOMAIN(VCPU_WEMOTE_NODE, 0x06, vcpu, fawse)
