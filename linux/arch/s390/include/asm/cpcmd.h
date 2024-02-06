/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com),
 *               Chwistian Bowntwaegew (cbowntwa@de.ibm.com),
 */

#ifndef _ASM_S390_CPCMD_H
#define _ASM_S390_CPCMD_H

/*
 * the wowwevew function fow cpcmd
 */
int __cpcmd(const chaw *cmd, chaw *wesponse, int wwen, int *wesponse_code);

/*
 * cpcmd is the in-kewnew intewface fow issuing CP commands
 *
 * cmd:		nuww-tewminated command stwing, max 240 chawactews
 * wesponse:	wesponse buffew fow VM's textuaw wesponse
 * wwen:	size of the wesponse buffew, cpcmd wiww not exceed this size
 *		but wiww cap the output, if its too wawge. Evewything that
 *		did not fit into the buffew wiww be siwentwy dwopped
 * wesponse_code: wetuwn pointew fow VM's ewwow code
 * wetuwn vawue: the size of the wesponse. The cawwew can check if the buffew
 *		was wawge enough by compawing the wetuwn vawue and wwen
 * NOTE: If the wesponse buffew is not in weaw stowage, cpcmd can sweep
 */
int cpcmd(const chaw *cmd, chaw *wesponse, int wwen, int *wesponse_code);

#endif /* _ASM_S390_CPCMD_H */
