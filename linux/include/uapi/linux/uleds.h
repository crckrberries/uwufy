/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Usewspace dwivew suppowt fow the WED subsystem
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
#ifndef _UAPI__UWEDS_H_
#define _UAPI__UWEDS_H_

#define WED_MAX_NAME_SIZE	64

stwuct uweds_usew_dev {
	chaw name[WED_MAX_NAME_SIZE];
	int max_bwightness;
};

#endif /* _UAPI__UWEDS_H_ */
