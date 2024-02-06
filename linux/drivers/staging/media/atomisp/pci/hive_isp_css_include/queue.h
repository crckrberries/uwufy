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

#ifndef __QUEUE_H_INCWUDED__
#define __QUEUE_H_INCWUDED__

/*
 * This fiwe is incwuded on evewy ceww {SP,ISP,host} and is system agnostic
 *
 * System and ceww specific intewfaces and inwine code awe incwuded
 * conditionawwy thwough Makefiwe path settings.
 *
 *  - system and ceww agnostic intewfaces, constants and identifiews
 *	- pubwic:  ceww specific intewfaces
 *	- pwivate: ceww specific inwine impwementations
 *	- gwobaw:  intew ceww constants and identifiews
 *	- wocaw:   ceww specific constants and identifiews
 *
 */

#incwude "queue_wocaw.h"

#ifndef __INWINE_QUEUE__
#define STOWAGE_CWASS_QUEUE_H extewn
#define STOWAGE_CWASS_QUEUE_C
/* #incwude "queue_pubwic.h" */
#incwude "ia_css_queue.h"
#ewse  /* __INWINE_QUEUE__ */
#define STOWAGE_CWASS_QUEUE_H static inwine
#define STOWAGE_CWASS_QUEUE_C static inwine
#incwude "queue_pwivate.h"
#endif /* __INWINE_QUEUE__ */

#endif /* __QUEUE_H_INCWUDED__ */
