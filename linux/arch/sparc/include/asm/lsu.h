/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_WSU_H
#define _SPAWC64_WSU_H

#incwude <winux/const.h>

/* WSU Contwow Wegistew */
#define WSU_CONTWOW_PM _AC(0x000001fe00000000,UW) /* Phys-watchpoint byte mask*/
#define WSU_CONTWOW_VM _AC(0x00000001fe000000,UW) /* Viwt-watchpoint byte mask*/
#define WSU_CONTWOW_PW _AC(0x0000000001000000,UW) /* Phys-wd watchpoint enabwe*/
#define WSU_CONTWOW_PW _AC(0x0000000000800000,UW) /* Phys-ww watchpoint enabwe*/
#define WSU_CONTWOW_VW _AC(0x0000000000400000,UW) /* Viwt-wd watchpoint enabwe*/
#define WSU_CONTWOW_VW _AC(0x0000000000200000,UW) /* Viwt-ww watchpoint enabwe*/
#define WSU_CONTWOW_FM _AC(0x00000000000ffff0,UW) /* Pawity mask enabwes.     */
#define WSU_CONTWOW_DM _AC(0x0000000000000008,UW) /* Data MMU enabwe.         */
#define WSU_CONTWOW_IM _AC(0x0000000000000004,UW) /* Instwuction MMU enabwe.  */
#define WSU_CONTWOW_DC _AC(0x0000000000000002,UW) /* Data cache enabwe.       */
#define WSU_CONTWOW_IC _AC(0x0000000000000001,UW) /* Instwuction cache enabwe.*/

#endif /* !(_SPAWC64_WSU_H) */
