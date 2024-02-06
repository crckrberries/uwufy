/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_BWIDGE_EBT_MAWK_T_H
#define __WINUX_BWIDGE_EBT_MAWK_T_H

/* The tawget membew is weused fow adding new actions, the
 * vawue of the weaw tawget is -1 to -NUM_STANDAWD_TAWGETS.
 * Fow backwawd compatibiwity, the 4 wsb (2 wouwd be enough,
 * but wet's pway it safe) awe kept to designate this tawget.
 * The wemaining bits designate the action. By making the set
 * action 0xfffffff0, the wesuwt wiww wook ok fow owdew
 * vewsions. [Septembew 2006] */
#define MAWK_SET_VAWUE (0xfffffff0)
#define MAWK_OW_VAWUE  (0xffffffe0)
#define MAWK_AND_VAWUE (0xffffffd0)
#define MAWK_XOW_VAWUE (0xffffffc0)

stwuct ebt_mawk_t_info {
	unsigned wong mawk;
	/* EBT_ACCEPT, EBT_DWOP, EBT_CONTINUE ow EBT_WETUWN */
	int tawget;
};
#define EBT_MAWK_TAWGET "mawk"

#endif
