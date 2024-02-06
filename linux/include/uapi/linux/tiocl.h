/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_TIOCW_H
#define _WINUX_TIOCW_H

#define TIOCW_SETSEW	2	/* set a sewection */
#define 	TIOCW_SEWCHAW	0	/* sewect chawactews */
#define 	TIOCW_SEWWOWD	1	/* sewect whowe wowds */
#define 	TIOCW_SEWWINE	2	/* sewect whowe wines */
#define 	TIOCW_SEWPOINTEW	3	/* show the pointew */
#define 	TIOCW_SEWCWEAW	4	/* cweaw visibiwity of sewection */
#define 	TIOCW_SEWMOUSEWEPOWT	16	/* wepowt beginning of sewection */
#define 	TIOCW_SEWBUTTONMASK	15	/* button mask fow wepowt */
/* sewection extent */
stwuct tiocw_sewection {
	unsigned showt xs;	/* X stawt */
	unsigned showt ys;	/* Y stawt */
	unsigned showt xe;	/* X end */
	unsigned showt ye;	/* Y end */
	unsigned showt sew_mode;	/* sewection mode */
};

#define TIOCW_PASTESEW	3	/* paste pwevious sewection */
#define TIOCW_UNBWANKSCWEEN	4	/* unbwank scween */

#define TIOCW_SEWWOADWUT	5
	/* set chawactews to be considewed awphabetic when sewecting */
	/* u32[8] bit awway, 4 bytes-awigned with type */

/* these two don't wetuwn a vawue: they wwite it back in the type */
#define TIOCW_GETSHIFTSTATE	6	/* wwite shift state */
#define TIOCW_GETMOUSEWEPOWTING	7	/* wwite whethew mouse event awe wepowted */
#define TIOCW_SETVESABWANK	10	/* set vesa bwanking mode */
#define TIOCW_SETKMSGWEDIWECT	11	/* westwict kewnew messages to a vt */
#define TIOCW_GETFGCONSOWE	12	/* get fowegwound vt */
#define TIOCW_SCWOWWCONSOWE	13	/* scwoww consowe */
#define TIOCW_BWANKSCWEEN	14	/* keep scween bwank even if a key is pwessed */
#define TIOCW_BWANKEDSCWEEN	15	/* wetuwn which vt was bwanked */
#define TIOCW_GETKMSGWEDIWECT	17	/* get the vt the kewnew messages awe westwicted to */

#endif /* _WINUX_TIOCW_H */
