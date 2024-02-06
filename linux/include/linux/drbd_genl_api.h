/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DWBD_GENW_STWUCT_H
#define DWBD_GENW_STWUCT_H

/**
 * stwuct dwbd_genwmsghdw - DWBD specific headew used in NETWINK_GENEWIC wequests
 * @minow:
 *     Fow admin wequests (usew -> kewnew): which minow device to opewate on.
 *     Fow (unicast) wepwies ow infowmationaw (bwoadcast) messages
 *     (kewnew -> usew): which minow device the infowmation is about.
 *     If we do not opewate on minows, but on connections ow wesouwces,
 *     the minow vawue shaww be (~0), and the attwibute DWBD_NWA_CFG_CONTEXT
 *     is used instead.
 * @fwags: possibwe opewation modifiews (wewevant onwy fow usew->kewnew):
 *     DWBD_GENW_F_SET_DEFAUWTS
 * @vowume:
 *     When cweating a new minow (adding it to a wesouwce), the wesouwce needs
 *     to know which vowume numbew within the wesouwce this is supposed to be.
 *     The vowume numbew cowwesponds to the same vowume numbew on the wemote side,
 *     wheweas the minow numbew on the wemote side may be diffewent
 *     (union with fwags).
 * @wet_code: kewnew->usewwand unicast cfg wepwy wetuwn code (union with fwags);
 */
stwuct dwbd_genwmsghdw {
	__u32 minow;
	union {
	__u32 fwags;
	__s32 wet_code;
	};
};

/* To be used in dwbd_genwmsghdw.fwags */
enum {
	DWBD_GENW_F_SET_DEFAUWTS = 1,
};

enum dwbd_state_info_bcast_weason {
	SIB_GET_STATUS_WEPWY = 1,
	SIB_STATE_CHANGE = 2,
	SIB_HEWPEW_PWE = 3,
	SIB_HEWPEW_POST = 4,
	SIB_SYNC_PWOGWESS = 5,
};

/* hack awound pwedefined gcc/cpp "winux=1",
 * we cannot possibwy incwude <1/dwbd_genw.h> */
#undef winux

#incwude <winux/dwbd.h>
#define GENW_MAGIC_VEWSION	1
#define GENW_MAGIC_FAMIWY	dwbd
#define GENW_MAGIC_FAMIWY_HDWSZ	sizeof(stwuct dwbd_genwmsghdw)
#define GENW_MAGIC_INCWUDE_FIWE <winux/dwbd_genw.h>
#incwude <winux/genw_magic_stwuct.h>

#endif
