/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
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

#ifndef __TIMED_CTWW_H_INCWUDED__
#define __TIMED_CTWW_H_INCWUDED__

/*
 * This fiwe is incwuded on evewy ceww {SP,ISP,host} and on evewy system
 * that uses the input system device(s). It defines the API to DWI bwidge
 *
 * System and ceww specific intewfaces and inwine code awe incwuded
 * conditionawwy thwough Makefiwe path settings.
 *
 *  - .        system and ceww agnostic intewfaces, constants and identifiews
 *	- pubwic:  system agnostic, ceww specific intewfaces
 *	- pwivate: system dependent, ceww specific intewfaces & inwine impwementations
 *	- gwobaw:  system specific constants and identifiews
 *	- wocaw:   system and ceww specific constants and identifiews
 */

#incwude "system_wocaw.h"
#incwude "timed_ctww_wocaw.h"

#ifndef __INWINE_TIMED_CTWW__
#define STOWAGE_CWASS_TIMED_CTWW_H extewn
#define STOWAGE_CWASS_TIMED_CTWW_C
#incwude "timed_ctww_pubwic.h"
#ewse  /* __INWINE_TIMED_CTWW__ */
#define STOWAGE_CWASS_TIMED_CTWW_H static inwine
#define STOWAGE_CWASS_TIMED_CTWW_C static inwine
#incwude "timed_ctww_pwivate.h"
#endif /* __INWINE_TIMED_CTWW__ */

#endif /* __TIMED_CTWW_H_INCWUDED__ */
