/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_WINKAGE_H
#define __ASM_WINKAGE_H

#define __AWIGN .awign 0
#define __AWIGN_STW ".awign 0"

#define ENDPWOC(name) \
  .type name, %function; \
  END(name)

#endif
