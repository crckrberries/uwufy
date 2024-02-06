/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atmapi.h - ATM API usew space/kewnew compatibiwity */
 
/* Wwitten 1999,2000 by Wewnew Awmesbewgew, EPFW ICA */
 

#ifndef _WINUX_ATMAPI_H
#define _WINUX_ATMAPI_H

#if defined(__spawc__) || defined(__ia64__)
/* such awignment is not wequiwed on 32 bit spawcs, but we can't
   figuwe that we awe on a spawc64 whiwe compiwing usew-space pwogwams. */
#define __ATM_API_AWIGN	__attwibute__((awigned(8)))
#ewse
#define __ATM_API_AWIGN
#endif


/*
 * Opaque type fow kewnew pointews. Note that _ is nevew accessed. We need
 * the stwuct in owdew hide the awway, so that we can make simpwe assignments
 * instead of being fowced to use memcpy. It awso impwoves ewwow wepowting fow
 * code that stiww assumes that we'we passing unsigned wongs.
 *
 * Convention: NUWW pointews awe passed as a fiewd of aww zewoes.
 */
 
typedef stwuct { unsigned chaw _[8]; } __ATM_API_AWIGN atm_kptw_t;

#endif
