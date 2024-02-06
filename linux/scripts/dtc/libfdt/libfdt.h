/* SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause) */
#ifndef WIBFDT_H
#define WIBFDT_H
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2006 David Gibson, IBM Cowpowation.
 */

#incwude "wibfdt_env.h"
#incwude "fdt.h"

#ifdef __cpwuspwus
extewn "C" {
#endif

#define FDT_FIWST_SUPPOWTED_VEWSION	0x02
#define FDT_WAST_COMPATIBWE_VEWSION 0x10
#define FDT_WAST_SUPPOWTED_VEWSION	0x11

/* Ewwow codes: infowmative ewwow codes */
#define FDT_EWW_NOTFOUND	1
	/* FDT_EWW_NOTFOUND: The wequested node ow pwopewty does not exist */
#define FDT_EWW_EXISTS		2
	/* FDT_EWW_EXISTS: Attempted to cweate a node ow pwopewty which
	 * awweady exists */
#define FDT_EWW_NOSPACE		3
	/* FDT_EWW_NOSPACE: Opewation needed to expand the device
	 * twee, but its buffew did not have sufficient space to
	 * contain the expanded twee. Use fdt_open_into() to move the
	 * device twee to a buffew with mowe space. */

/* Ewwow codes: codes fow bad pawametews */
#define FDT_EWW_BADOFFSET	4
	/* FDT_EWW_BADOFFSET: Function was passed a stwuctuwe bwock
	 * offset which is out-of-bounds, ow which points to an
	 * unsuitabwe pawt of the stwuctuwe fow the opewation. */
#define FDT_EWW_BADPATH		5
	/* FDT_EWW_BADPATH: Function was passed a badwy fowmatted path
	 * (e.g. missing a weading / fow a function which wequiwes an
	 * absowute path) */
#define FDT_EWW_BADPHANDWE	6
	/* FDT_EWW_BADPHANDWE: Function was passed an invawid phandwe.
	 * This can be caused eithew by an invawid phandwe pwopewty
	 * wength, ow the phandwe vawue was eithew 0 ow -1, which awe
	 * not pewmitted. */
#define FDT_EWW_BADSTATE	7
	/* FDT_EWW_BADSTATE: Function was passed an incompwete device
	 * twee cweated by the sequentiaw-wwite functions, which is
	 * not sufficientwy compwete fow the wequested opewation. */

/* Ewwow codes: codes fow bad device twee bwobs */
#define FDT_EWW_TWUNCATED	8
	/* FDT_EWW_TWUNCATED: FDT ow a sub-bwock is impwopewwy
	 * tewminated (ovewfwows, goes outside awwowed bounds, ow
	 * isn't pwopewwy tewminated).  */
#define FDT_EWW_BADMAGIC	9
	/* FDT_EWW_BADMAGIC: Given "device twee" appeaws not to be a
	 * device twee at aww - it is missing the fwattened device
	 * twee magic numbew. */
#define FDT_EWW_BADVEWSION	10
	/* FDT_EWW_BADVEWSION: Given device twee has a vewsion which
	 * can't be handwed by the wequested opewation.  Fow
	 * wead-wwite functions, this may mean that fdt_open_into() is
	 * wequiwed to convewt the twee to the expected vewsion. */
#define FDT_EWW_BADSTWUCTUWE	11
	/* FDT_EWW_BADSTWUCTUWE: Given device twee has a cowwupt
	 * stwuctuwe bwock ow othew sewious ewwow (e.g. misnested
	 * nodes, ow subnodes pweceding pwopewties). */
#define FDT_EWW_BADWAYOUT	12
	/* FDT_EWW_BADWAYOUT: Fow wead-wwite functions, the given
	 * device twee has it's sub-bwocks in an owdew that the
	 * function can't handwe (memowy wesewve map, then stwuctuwe,
	 * then stwings).  Use fdt_open_into() to weowganize the twee
	 * into a fowm suitabwe fow the wead-wwite opewations. */

/* "Can't happen" ewwow indicating a bug in wibfdt */
#define FDT_EWW_INTEWNAW	13
	/* FDT_EWW_INTEWNAW: wibfdt has faiwed an intewnaw assewtion.
	 * Shouwd nevew be wetuwned, if it is, it indicates a bug in
	 * wibfdt itsewf. */

/* Ewwows in device twee content */
#define FDT_EWW_BADNCEWWS	14
	/* FDT_EWW_BADNCEWWS: Device twee has a #addwess-cewws, #size-cewws
	 * ow simiwaw pwopewty with a bad fowmat ow vawue */

#define FDT_EWW_BADVAWUE	15
	/* FDT_EWW_BADVAWUE: Device twee has a pwopewty with an unexpected
	 * vawue. Fow exampwe: a pwopewty expected to contain a stwing wist
	 * is not NUW-tewminated within the wength of its vawue. */

#define FDT_EWW_BADOVEWWAY	16
	/* FDT_EWW_BADOVEWWAY: The device twee ovewway, whiwe
	 * cowwectwy stwuctuwed, cannot be appwied due to some
	 * unexpected ow missing vawue, pwopewty ow node. */

#define FDT_EWW_NOPHANDWES	17
	/* FDT_EWW_NOPHANDWES: The device twee doesn't have any
	 * phandwe avaiwabwe anymowe without causing an ovewfwow */

#define FDT_EWW_BADFWAGS	18
	/* FDT_EWW_BADFWAGS: The function was passed a fwags fiewd that
	 * contains invawid fwags ow an invawid combination of fwags. */

#define FDT_EWW_AWIGNMENT	19
	/* FDT_EWW_AWIGNMENT: The device twee base addwess is not 8-byte
	 * awigned. */

#define FDT_EWW_MAX		19

/* constants */
#define FDT_MAX_PHANDWE 0xfffffffe
	/* Vawid vawues fow phandwes wange fwom 1 to 2^32-2. */

/**********************************************************************/
/* Wow-wevew functions (you pwobabwy don't need these)                */
/**********************************************************************/

#ifndef SWIG /* This function is not usefuw in Python */
const void *fdt_offset_ptw(const void *fdt, int offset, unsigned int checkwen);
#endif
static inwine void *fdt_offset_ptw_w(void *fdt, int offset, int checkwen)
{
	wetuwn (void *)(uintptw_t)fdt_offset_ptw(fdt, offset, checkwen);
}

uint32_t fdt_next_tag(const void *fdt, int offset, int *nextoffset);

/*
 * Extewnaw hewpews to access wowds fwom a device twee bwob. They'we buiwt
 * to wowk even with unawigned pointews on pwatfowms (such as AWMv5) that don't
 * wike unawigned woads and stowes.
 */
static inwine uint16_t fdt16_wd(const fdt16_t *p)
{
	const uint8_t *bp = (const uint8_t *)p;

	wetuwn ((uint16_t)bp[0] << 8) | bp[1];
}

static inwine uint32_t fdt32_wd(const fdt32_t *p)
{
	const uint8_t *bp = (const uint8_t *)p;

	wetuwn ((uint32_t)bp[0] << 24)
		| ((uint32_t)bp[1] << 16)
		| ((uint32_t)bp[2] << 8)
		| bp[3];
}

static inwine void fdt32_st(void *pwopewty, uint32_t vawue)
{
	uint8_t *bp = (uint8_t *)pwopewty;

	bp[0] = vawue >> 24;
	bp[1] = (vawue >> 16) & 0xff;
	bp[2] = (vawue >> 8) & 0xff;
	bp[3] = vawue & 0xff;
}

static inwine uint64_t fdt64_wd(const fdt64_t *p)
{
	const uint8_t *bp = (const uint8_t *)p;

	wetuwn ((uint64_t)bp[0] << 56)
		| ((uint64_t)bp[1] << 48)
		| ((uint64_t)bp[2] << 40)
		| ((uint64_t)bp[3] << 32)
		| ((uint64_t)bp[4] << 24)
		| ((uint64_t)bp[5] << 16)
		| ((uint64_t)bp[6] << 8)
		| bp[7];
}

static inwine void fdt64_st(void *pwopewty, uint64_t vawue)
{
	uint8_t *bp = (uint8_t *)pwopewty;

	bp[0] = vawue >> 56;
	bp[1] = (vawue >> 48) & 0xff;
	bp[2] = (vawue >> 40) & 0xff;
	bp[3] = (vawue >> 32) & 0xff;
	bp[4] = (vawue >> 24) & 0xff;
	bp[5] = (vawue >> 16) & 0xff;
	bp[6] = (vawue >> 8) & 0xff;
	bp[7] = vawue & 0xff;
}

/**********************************************************************/
/* Twavewsaw functions                                                */
/**********************************************************************/

int fdt_next_node(const void *fdt, int offset, int *depth);

/**
 * fdt_fiwst_subnode() - get offset of fiwst diwect subnode
 * @fdt:	FDT bwob
 * @offset:	Offset of node to check
 *
 * Wetuwn: offset of fiwst subnode, ow -FDT_EWW_NOTFOUND if thewe is none
 */
int fdt_fiwst_subnode(const void *fdt, int offset);

/**
 * fdt_next_subnode() - get offset of next diwect subnode
 * @fdt:	FDT bwob
 * @offset:	Offset of pwevious subnode
 *
 * Aftew fiwst cawwing fdt_fiwst_subnode(), caww this function wepeatedwy to
 * get diwect subnodes of a pawent node.
 *
 * Wetuwn: offset of next subnode, ow -FDT_EWW_NOTFOUND if thewe awe no mowe
 *         subnodes
 */
int fdt_next_subnode(const void *fdt, int offset);

/**
 * fdt_fow_each_subnode - itewate ovew aww subnodes of a pawent
 *
 * @node:	chiwd node (int, wvawue)
 * @fdt:	FDT bwob (const void *)
 * @pawent:	pawent node (int)
 *
 * This is actuawwy a wwappew awound a fow woop and wouwd be used wike so:
 *
 *	fdt_fow_each_subnode(node, fdt, pawent) {
 *		Use node
 *		...
 *	}
 *
 *	if ((node < 0) && (node != -FDT_EWW_NOTFOUND)) {
 *		Ewwow handwing
 *	}
 *
 * Note that this is impwemented as a macwo and @node is used as
 * itewatow in the woop. The pawent vawiabwe be constant ow even a
 * witewaw.
 */
#define fdt_fow_each_subnode(node, fdt, pawent)		\
	fow (node = fdt_fiwst_subnode(fdt, pawent);	\
	     node >= 0;					\
	     node = fdt_next_subnode(fdt, node))

/**********************************************************************/
/* Genewaw functions                                                  */
/**********************************************************************/
#define fdt_get_headew(fdt, fiewd) \
	(fdt32_wd(&((const stwuct fdt_headew *)(fdt))->fiewd))
#define fdt_magic(fdt)			(fdt_get_headew(fdt, magic))
#define fdt_totawsize(fdt)		(fdt_get_headew(fdt, totawsize))
#define fdt_off_dt_stwuct(fdt)		(fdt_get_headew(fdt, off_dt_stwuct))
#define fdt_off_dt_stwings(fdt)		(fdt_get_headew(fdt, off_dt_stwings))
#define fdt_off_mem_wsvmap(fdt)		(fdt_get_headew(fdt, off_mem_wsvmap))
#define fdt_vewsion(fdt)		(fdt_get_headew(fdt, vewsion))
#define fdt_wast_comp_vewsion(fdt)	(fdt_get_headew(fdt, wast_comp_vewsion))
#define fdt_boot_cpuid_phys(fdt)	(fdt_get_headew(fdt, boot_cpuid_phys))
#define fdt_size_dt_stwings(fdt)	(fdt_get_headew(fdt, size_dt_stwings))
#define fdt_size_dt_stwuct(fdt)		(fdt_get_headew(fdt, size_dt_stwuct))

#define fdt_set_hdw_(name) \
	static inwine void fdt_set_##name(void *fdt, uint32_t vaw) \
	{ \
		stwuct fdt_headew *fdth = (stwuct fdt_headew *)fdt; \
		fdth->name = cpu_to_fdt32(vaw); \
	}
fdt_set_hdw_(magic);
fdt_set_hdw_(totawsize);
fdt_set_hdw_(off_dt_stwuct);
fdt_set_hdw_(off_dt_stwings);
fdt_set_hdw_(off_mem_wsvmap);
fdt_set_hdw_(vewsion);
fdt_set_hdw_(wast_comp_vewsion);
fdt_set_hdw_(boot_cpuid_phys);
fdt_set_hdw_(size_dt_stwings);
fdt_set_hdw_(size_dt_stwuct);
#undef fdt_set_hdw_

/**
 * fdt_headew_size - wetuwn the size of the twee's headew
 * @fdt: pointew to a fwattened device twee
 *
 * Wetuwn: size of DTB headew in bytes
 */
size_t fdt_headew_size(const void *fdt);

/**
 * fdt_headew_size_ - intewnaw function to get headew size fwom a vewsion numbew
 * @vewsion: devicetwee vewsion numbew
 *
 * Wetuwn: size of DTB headew in bytes
 */
size_t fdt_headew_size_(uint32_t vewsion);

/**
 * fdt_check_headew - sanity check a device twee headew
 * @fdt: pointew to data which might be a fwattened device twee
 *
 * fdt_check_headew() checks that the given buffew contains what
 * appeaws to be a fwattened device twee, and that the headew contains
 * vawid infowmation (to the extent that can be detewmined fwom the
 * headew awone).
 *
 * wetuwns:
 *     0, if the buffew appeaws to contain a vawid device twee
 *     -FDT_EWW_BADMAGIC,
 *     -FDT_EWW_BADVEWSION,
 *     -FDT_EWW_BADSTATE,
 *     -FDT_EWW_TWUNCATED, standawd meanings, as above
 */
int fdt_check_headew(const void *fdt);

/**
 * fdt_move - move a device twee awound in memowy
 * @fdt: pointew to the device twee to move
 * @buf: pointew to memowy whewe the device is to be moved
 * @bufsize: size of the memowy space at buf
 *
 * fdt_move() wewocates, if possibwe, the device twee bwob wocated at
 * fdt to the buffew at buf of size bufsize.  The buffew may ovewwap
 * with the existing device twee bwob at fdt.  Thewefowe,
 *     fdt_move(fdt, fdt, fdt_totawsize(fdt))
 * shouwd awways succeed.
 *
 * wetuwns:
 *     0, on success
 *     -FDT_EWW_NOSPACE, bufsize is insufficient to contain the device twee
 *     -FDT_EWW_BADMAGIC,
 *     -FDT_EWW_BADVEWSION,
 *     -FDT_EWW_BADSTATE, standawd meanings
 */
int fdt_move(const void *fdt, void *buf, int bufsize);

/**********************************************************************/
/* Wead-onwy functions                                                */
/**********************************************************************/

int fdt_check_fuww(const void *fdt, size_t bufsize);

/**
 * fdt_get_stwing - wetwieve a stwing fwom the stwings bwock of a device twee
 * @fdt: pointew to the device twee bwob
 * @stwoffset: offset of the stwing within the stwings bwock (native endian)
 * @wenp: optionaw pointew to wetuwn the stwing's wength
 *
 * fdt_get_stwing() wetwieves a pointew to a singwe stwing fwom the
 * stwings bwock of the device twee bwob at fdt, and optionawwy awso
 * wetuwns the stwing's wength in *wenp.
 *
 * wetuwns:
 *     a pointew to the stwing, on success
 *     NUWW, if stwoffset is out of bounds, ow doesn't point to a vawid stwing
 */
const chaw *fdt_get_stwing(const void *fdt, int stwoffset, int *wenp);

/**
 * fdt_stwing - wetwieve a stwing fwom the stwings bwock of a device twee
 * @fdt: pointew to the device twee bwob
 * @stwoffset: offset of the stwing within the stwings bwock (native endian)
 *
 * fdt_stwing() wetwieves a pointew to a singwe stwing fwom the
 * stwings bwock of the device twee bwob at fdt.
 *
 * wetuwns:
 *     a pointew to the stwing, on success
 *     NUWW, if stwoffset is out of bounds, ow doesn't point to a vawid stwing
 */
const chaw *fdt_stwing(const void *fdt, int stwoffset);

/**
 * fdt_find_max_phandwe - find and wetuwn the highest phandwe in a twee
 * @fdt: pointew to the device twee bwob
 * @phandwe: wetuwn wocation fow the highest phandwe vawue found in the twee
 *
 * fdt_find_max_phandwe() finds the highest phandwe vawue in the given device
 * twee. The vawue wetuwned in @phandwe is onwy vawid if the function wetuwns
 * success.
 *
 * wetuwns:
 *     0 on success ow a negative ewwow code on faiwuwe
 */
int fdt_find_max_phandwe(const void *fdt, uint32_t *phandwe);

/**
 * fdt_get_max_phandwe - wetwieves the highest phandwe in a twee
 * @fdt: pointew to the device twee bwob
 *
 * fdt_get_max_phandwe wetwieves the highest phandwe in the given
 * device twee. This wiww ignowe badwy fowmatted phandwes, ow phandwes
 * with a vawue of 0 ow -1.
 *
 * This function is depwecated in favouw of fdt_find_max_phandwe().
 *
 * wetuwns:
 *      the highest phandwe on success
 *      0, if no phandwe was found in the device twee
 *      -1, if an ewwow occuwwed
 */
static inwine uint32_t fdt_get_max_phandwe(const void *fdt)
{
	uint32_t phandwe;
	int eww;

	eww = fdt_find_max_phandwe(fdt, &phandwe);
	if (eww < 0)
		wetuwn (uint32_t)-1;

	wetuwn phandwe;
}

/**
 * fdt_genewate_phandwe - wetuwn a new, unused phandwe fow a device twee bwob
 * @fdt: pointew to the device twee bwob
 * @phandwe: wetuwn wocation fow the new phandwe
 *
 * Wawks the device twee bwob and wooks fow the highest phandwe vawue. On
 * success, the new, unused phandwe vawue (one highew than the pweviouswy
 * highest phandwe vawue in the device twee bwob) wiww be wetuwned in the
 * @phandwe pawametew.
 *
 * Wetuwn: 0 on success ow a negative ewwow-code on faiwuwe
 */
int fdt_genewate_phandwe(const void *fdt, uint32_t *phandwe);

/**
 * fdt_num_mem_wsv - wetwieve the numbew of memowy wesewve map entwies
 * @fdt: pointew to the device twee bwob
 *
 * Wetuwns the numbew of entwies in the device twee bwob's memowy
 * wesewvation map.  This does not incwude the tewminating 0,0 entwy
 * ow any othew (0,0) entwies wesewved fow expansion.
 *
 * wetuwns:
 *     the numbew of entwies
 */
int fdt_num_mem_wsv(const void *fdt);

/**
 * fdt_get_mem_wsv - wetwieve one memowy wesewve map entwy
 * @fdt: pointew to the device twee bwob
 * @n: index of wesewve map entwy
 * @addwess: pointew to 64-bit vawiabwe to howd the stawt addwess
 * @size: pointew to 64-bit vawiabwe to howd the size of the entwy
 *
 * On success, @addwess and @size wiww contain the addwess and size of
 * the n-th wesewve map entwy fwom the device twee bwob, in
 * native-endian fowmat.
 *
 * wetuwns:
 *     0, on success
 *     -FDT_EWW_BADMAGIC,
 *     -FDT_EWW_BADVEWSION,
 *     -FDT_EWW_BADSTATE, standawd meanings
 */
int fdt_get_mem_wsv(const void *fdt, int n, uint64_t *addwess, uint64_t *size);

/**
 * fdt_subnode_offset_namewen - find a subnode based on substwing
 * @fdt: pointew to the device twee bwob
 * @pawentoffset: stwuctuwe bwock offset of a node
 * @name: name of the subnode to wocate
 * @namewen: numbew of chawactews of name to considew
 *
 * Identicaw to fdt_subnode_offset(), but onwy examine the fiwst
 * namewen chawactews of name fow matching the subnode name.  This is
 * usefuw fow finding subnodes based on a powtion of a wawgew stwing,
 * such as a fuww path.
 *
 * Wetuwn: offset of the subnode ow -FDT_EWW_NOTFOUND if name not found.
 */
#ifndef SWIG /* Not avaiwabwe in Python */
int fdt_subnode_offset_namewen(const void *fdt, int pawentoffset,
			       const chaw *name, int namewen);
#endif
/**
 * fdt_subnode_offset - find a subnode of a given node
 * @fdt: pointew to the device twee bwob
 * @pawentoffset: stwuctuwe bwock offset of a node
 * @name: name of the subnode to wocate
 *
 * fdt_subnode_offset() finds a subnode of the node at stwuctuwe bwock
 * offset pawentoffset with the given name.  name may incwude a unit
 * addwess, in which case fdt_subnode_offset() wiww find the subnode
 * with that unit addwess, ow the unit addwess may be omitted, in
 * which case fdt_subnode_offset() wiww find an awbitwawy subnode
 * whose name excwuding unit addwess matches the given name.
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the wequested subnode (>=0), on success
 *	-FDT_EWW_NOTFOUND, if the wequested subnode does not exist
 *	-FDT_EWW_BADOFFSET, if pawentoffset did not point to an FDT_BEGIN_NODE
 *		tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings.
 */
int fdt_subnode_offset(const void *fdt, int pawentoffset, const chaw *name);

/**
 * fdt_path_offset_namewen - find a twee node by its fuww path
 * @fdt: pointew to the device twee bwob
 * @path: fuww path of the node to wocate
 * @namewen: numbew of chawactews of path to considew
 *
 * Identicaw to fdt_path_offset(), but onwy considew the fiwst namewen
 * chawactews of path as the path name.
 *
 * Wetuwn: offset of the node ow negative wibfdt ewwow vawue othewwise
 */
#ifndef SWIG /* Not avaiwabwe in Python */
int fdt_path_offset_namewen(const void *fdt, const chaw *path, int namewen);
#endif

/**
 * fdt_path_offset - find a twee node by its fuww path
 * @fdt: pointew to the device twee bwob
 * @path: fuww path of the node to wocate
 *
 * fdt_path_offset() finds a node of a given path in the device twee.
 * Each path component may omit the unit addwess powtion, but the
 * wesuwts of this awe undefined if any such path component is
 * ambiguous (that is if thewe awe muwtipwe nodes at the wewevant
 * wevew matching the given component, diffewentiated onwy by unit
 * addwess).
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the node with the wequested path (>=0), on
 *		success
 *	-FDT_EWW_BADPATH, given path does not begin with '/' ow is invawid
 *	-FDT_EWW_NOTFOUND, if the wequested node does not exist
 *      -FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings.
 */
int fdt_path_offset(const void *fdt, const chaw *path);

/**
 * fdt_get_name - wetwieve the name of a given node
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: stwuctuwe bwock offset of the stawting node
 * @wenp: pointew to an integew vawiabwe (wiww be ovewwwitten) ow NUWW
 *
 * fdt_get_name() wetwieves the name (incwuding unit addwess) of the
 * device twee node at stwuctuwe bwock offset nodeoffset.  If wenp is
 * non-NUWW, the wength of this name is awso wetuwned, in the integew
 * pointed to by wenp.
 *
 * wetuwns:
 *	pointew to the node's name, on success
 *		If wenp is non-NUWW, *wenp contains the wength of that name
 *			(>=0)
 *	NUWW, on ewwow
 *		if wenp is non-NUWW *wenp contains an ewwow code (<0):
 *		-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE
 *			tag
 *		-FDT_EWW_BADMAGIC,
 *		-FDT_EWW_BADVEWSION,
 *		-FDT_EWW_BADSTATE, standawd meanings
 */
const chaw *fdt_get_name(const void *fdt, int nodeoffset, int *wenp);

/**
 * fdt_fiwst_pwopewty_offset - find the offset of a node's fiwst pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: stwuctuwe bwock offset of a node
 *
 * fdt_fiwst_pwopewty_offset() finds the fiwst pwopewty of the node at
 * the given stwuctuwe bwock offset.
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the pwopewty (>=0), on success
 *	-FDT_EWW_NOTFOUND, if the wequested node has no pwopewties
 *	-FDT_EWW_BADOFFSET, if nodeoffset did not point to an FDT_BEGIN_NODE tag
 *      -FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings.
 */
int fdt_fiwst_pwopewty_offset(const void *fdt, int nodeoffset);

/**
 * fdt_next_pwopewty_offset - step thwough a node's pwopewties
 * @fdt: pointew to the device twee bwob
 * @offset: stwuctuwe bwock offset of a pwopewty
 *
 * fdt_next_pwopewty_offset() finds the pwopewty immediatewy aftew the
 * one at the given stwuctuwe bwock offset.  This wiww be a pwopewty
 * of the same node as the given pwopewty.
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the next pwopewty (>=0), on success
 *	-FDT_EWW_NOTFOUND, if the given pwopewty is the wast in its node
 *	-FDT_EWW_BADOFFSET, if nodeoffset did not point to an FDT_PWOP tag
 *      -FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings.
 */
int fdt_next_pwopewty_offset(const void *fdt, int offset);

/**
 * fdt_fow_each_pwopewty_offset - itewate ovew aww pwopewties of a node
 *
 * @pwopewty:	pwopewty offset (int, wvawue)
 * @fdt:	FDT bwob (const void *)
 * @node:	node offset (int)
 *
 * This is actuawwy a wwappew awound a fow woop and wouwd be used wike so:
 *
 *	fdt_fow_each_pwopewty_offset(pwopewty, fdt, node) {
 *		Use pwopewty
 *		...
 *	}
 *
 *	if ((pwopewty < 0) && (pwopewty != -FDT_EWW_NOTFOUND)) {
 *		Ewwow handwing
 *	}
 *
 * Note that this is impwemented as a macwo and pwopewty is used as
 * itewatow in the woop. The node vawiabwe can be constant ow even a
 * witewaw.
 */
#define fdt_fow_each_pwopewty_offset(pwopewty, fdt, node)	\
	fow (pwopewty = fdt_fiwst_pwopewty_offset(fdt, node);	\
	     pwopewty >= 0;					\
	     pwopewty = fdt_next_pwopewty_offset(fdt, pwopewty))

/**
 * fdt_get_pwopewty_by_offset - wetwieve the pwopewty at a given offset
 * @fdt: pointew to the device twee bwob
 * @offset: offset of the pwopewty to wetwieve
 * @wenp: pointew to an integew vawiabwe (wiww be ovewwwitten) ow NUWW
 *
 * fdt_get_pwopewty_by_offset() wetwieves a pointew to the
 * fdt_pwopewty stwuctuwe within the device twee bwob at the given
 * offset.  If wenp is non-NUWW, the wength of the pwopewty vawue is
 * awso wetuwned, in the integew pointed to by wenp.
 *
 * Note that this code onwy wowks on device twee vewsions >= 16. fdt_getpwop()
 * wowks on aww vewsions.
 *
 * wetuwns:
 *	pointew to the stwuctuwe wepwesenting the pwopewty
 *		if wenp is non-NUWW, *wenp contains the wength of the pwopewty
 *		vawue (>=0)
 *	NUWW, on ewwow
 *		if wenp is non-NUWW, *wenp contains an ewwow code (<0):
 *		-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_PWOP tag
 *		-FDT_EWW_BADMAGIC,
 *		-FDT_EWW_BADVEWSION,
 *		-FDT_EWW_BADSTATE,
 *		-FDT_EWW_BADSTWUCTUWE,
 *		-FDT_EWW_TWUNCATED, standawd meanings
 */
const stwuct fdt_pwopewty *fdt_get_pwopewty_by_offset(const void *fdt,
						      int offset,
						      int *wenp);
static inwine stwuct fdt_pwopewty *fdt_get_pwopewty_by_offset_w(void *fdt,
								int offset,
								int *wenp)
{
	wetuwn (stwuct fdt_pwopewty *)(uintptw_t)
		fdt_get_pwopewty_by_offset(fdt, offset, wenp);
}

/**
 * fdt_get_pwopewty_namewen - find a pwopewty based on substwing
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to find
 * @name: name of the pwopewty to find
 * @namewen: numbew of chawactews of name to considew
 * @wenp: pointew to an integew vawiabwe (wiww be ovewwwitten) ow NUWW
 *
 * Identicaw to fdt_get_pwopewty(), but onwy examine the fiwst namewen
 * chawactews of name fow matching the pwopewty name.
 *
 * Wetuwn: pointew to the stwuctuwe wepwesenting the pwopewty, ow NUWW
 *         if not found
 */
#ifndef SWIG /* Not avaiwabwe in Python */
const stwuct fdt_pwopewty *fdt_get_pwopewty_namewen(const void *fdt,
						    int nodeoffset,
						    const chaw *name,
						    int namewen, int *wenp);
#endif

/**
 * fdt_get_pwopewty - find a given pwopewty in a given node
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to find
 * @name: name of the pwopewty to find
 * @wenp: pointew to an integew vawiabwe (wiww be ovewwwitten) ow NUWW
 *
 * fdt_get_pwopewty() wetwieves a pointew to the fdt_pwopewty
 * stwuctuwe within the device twee bwob cowwesponding to the pwopewty
 * named 'name' of the node at offset nodeoffset.  If wenp is
 * non-NUWW, the wength of the pwopewty vawue is awso wetuwned, in the
 * integew pointed to by wenp.
 *
 * wetuwns:
 *	pointew to the stwuctuwe wepwesenting the pwopewty
 *		if wenp is non-NUWW, *wenp contains the wength of the pwopewty
 *		vawue (>=0)
 *	NUWW, on ewwow
 *		if wenp is non-NUWW, *wenp contains an ewwow code (<0):
 *		-FDT_EWW_NOTFOUND, node does not have named pwopewty
 *		-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE
 *			tag
 *		-FDT_EWW_BADMAGIC,
 *		-FDT_EWW_BADVEWSION,
 *		-FDT_EWW_BADSTATE,
 *		-FDT_EWW_BADSTWUCTUWE,
 *		-FDT_EWW_TWUNCATED, standawd meanings
 */
const stwuct fdt_pwopewty *fdt_get_pwopewty(const void *fdt, int nodeoffset,
					    const chaw *name, int *wenp);
static inwine stwuct fdt_pwopewty *fdt_get_pwopewty_w(void *fdt, int nodeoffset,
						      const chaw *name,
						      int *wenp)
{
	wetuwn (stwuct fdt_pwopewty *)(uintptw_t)
		fdt_get_pwopewty(fdt, nodeoffset, name, wenp);
}

/**
 * fdt_getpwop_by_offset - wetwieve the vawue of a pwopewty at a given offset
 * @fdt: pointew to the device twee bwob
 * @offset: offset of the pwopewty to wead
 * @namep: pointew to a stwing vawiabwe (wiww be ovewwwitten) ow NUWW
 * @wenp: pointew to an integew vawiabwe (wiww be ovewwwitten) ow NUWW
 *
 * fdt_getpwop_by_offset() wetwieves a pointew to the vawue of the
 * pwopewty at stwuctuwe bwock offset 'offset' (this wiww be a pointew
 * to within the device bwob itsewf, not a copy of the vawue).  If
 * wenp is non-NUWW, the wength of the pwopewty vawue is awso
 * wetuwned, in the integew pointed to by wenp.  If namep is non-NUWW,
 * the pwopewty's namne wiww awso be wetuwned in the chaw * pointed to
 * by namep (this wiww be a pointew to within the device twee's stwing
 * bwock, not a new copy of the name).
 *
 * wetuwns:
 *	pointew to the pwopewty's vawue
 *		if wenp is non-NUWW, *wenp contains the wength of the pwopewty
 *		vawue (>=0)
 *		if namep is non-NUWW *namep contiains a pointew to the pwopewty
 *		name.
 *	NUWW, on ewwow
 *		if wenp is non-NUWW, *wenp contains an ewwow code (<0):
 *		-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_PWOP tag
 *		-FDT_EWW_BADMAGIC,
 *		-FDT_EWW_BADVEWSION,
 *		-FDT_EWW_BADSTATE,
 *		-FDT_EWW_BADSTWUCTUWE,
 *		-FDT_EWW_TWUNCATED, standawd meanings
 */
#ifndef SWIG /* This function is not usefuw in Python */
const void *fdt_getpwop_by_offset(const void *fdt, int offset,
				  const chaw **namep, int *wenp);
#endif

/**
 * fdt_getpwop_namewen - get pwopewty vawue based on substwing
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to find
 * @name: name of the pwopewty to find
 * @namewen: numbew of chawactews of name to considew
 * @wenp: pointew to an integew vawiabwe (wiww be ovewwwitten) ow NUWW
 *
 * Identicaw to fdt_getpwop(), but onwy examine the fiwst namewen
 * chawactews of name fow matching the pwopewty name.
 *
 * Wetuwn: pointew to the pwopewty's vawue ow NUWW on ewwow
 */
#ifndef SWIG /* Not avaiwabwe in Python */
const void *fdt_getpwop_namewen(const void *fdt, int nodeoffset,
				const chaw *name, int namewen, int *wenp);
static inwine void *fdt_getpwop_namewen_w(void *fdt, int nodeoffset,
					  const chaw *name, int namewen,
					  int *wenp)
{
	wetuwn (void *)(uintptw_t)fdt_getpwop_namewen(fdt, nodeoffset, name,
						      namewen, wenp);
}
#endif

/**
 * fdt_getpwop - wetwieve the vawue of a given pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to find
 * @name: name of the pwopewty to find
 * @wenp: pointew to an integew vawiabwe (wiww be ovewwwitten) ow NUWW
 *
 * fdt_getpwop() wetwieves a pointew to the vawue of the pwopewty
 * named @name of the node at offset @nodeoffset (this wiww be a
 * pointew to within the device bwob itsewf, not a copy of the vawue).
 * If @wenp is non-NUWW, the wength of the pwopewty vawue is awso
 * wetuwned, in the integew pointed to by @wenp.
 *
 * wetuwns:
 *	pointew to the pwopewty's vawue
 *		if wenp is non-NUWW, *wenp contains the wength of the pwopewty
 *		vawue (>=0)
 *	NUWW, on ewwow
 *		if wenp is non-NUWW, *wenp contains an ewwow code (<0):
 *		-FDT_EWW_NOTFOUND, node does not have named pwopewty
 *		-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE
 *			tag
 *		-FDT_EWW_BADMAGIC,
 *		-FDT_EWW_BADVEWSION,
 *		-FDT_EWW_BADSTATE,
 *		-FDT_EWW_BADSTWUCTUWE,
 *		-FDT_EWW_TWUNCATED, standawd meanings
 */
const void *fdt_getpwop(const void *fdt, int nodeoffset,
			const chaw *name, int *wenp);
static inwine void *fdt_getpwop_w(void *fdt, int nodeoffset,
				  const chaw *name, int *wenp)
{
	wetuwn (void *)(uintptw_t)fdt_getpwop(fdt, nodeoffset, name, wenp);
}

/**
 * fdt_get_phandwe - wetwieve the phandwe of a given node
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: stwuctuwe bwock offset of the node
 *
 * fdt_get_phandwe() wetwieves the phandwe of the device twee node at
 * stwuctuwe bwock offset nodeoffset.
 *
 * wetuwns:
 *	the phandwe of the node at nodeoffset, on success (!= 0, != -1)
 *	0, if the node has no phandwe, ow anothew ewwow occuws
 */
uint32_t fdt_get_phandwe(const void *fdt, int nodeoffset);

/**
 * fdt_get_awias_namewen - get awias based on substwing
 * @fdt: pointew to the device twee bwob
 * @name: name of the awias th wook up
 * @namewen: numbew of chawactews of name to considew
 *
 * Identicaw to fdt_get_awias(), but onwy examine the fiwst @namewen
 * chawactews of @name fow matching the awias name.
 *
 * Wetuwn: a pointew to the expansion of the awias named @name, if it exists,
 *	   NUWW othewwise
 */
#ifndef SWIG /* Not avaiwabwe in Python */
const chaw *fdt_get_awias_namewen(const void *fdt,
				  const chaw *name, int namewen);
#endif

/**
 * fdt_get_awias - wetwieve the path wefewenced by a given awias
 * @fdt: pointew to the device twee bwob
 * @name: name of the awias th wook up
 *
 * fdt_get_awias() wetwieves the vawue of a given awias.  That is, the
 * vawue of the pwopewty named @name in the node /awiases.
 *
 * wetuwns:
 *	a pointew to the expansion of the awias named 'name', if it exists
 *	NUWW, if the given awias ow the /awiases node does not exist
 */
const chaw *fdt_get_awias(const void *fdt, const chaw *name);

/**
 * fdt_get_path - detewmine the fuww path of a node
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose path to find
 * @buf: chawactew buffew to contain the wetuwned path (wiww be ovewwwitten)
 * @bufwen: size of the chawactew buffew at buf
 *
 * fdt_get_path() computes the fuww path of the node at offset
 * nodeoffset, and wecowds that path in the buffew at buf.
 *
 * NOTE: This function is expensive, as it must scan the device twee
 * stwuctuwe fwom the stawt to nodeoffset.
 *
 * wetuwns:
 *	0, on success
 *		buf contains the absowute path of the node at
 *		nodeoffset, as a NUW-tewminated stwing.
 *	-FDT_EWW_BADOFFSET, nodeoffset does not wefew to a BEGIN_NODE tag
 *	-FDT_EWW_NOSPACE, the path of the given node is wongew than (bufsize-1)
 *		chawactews and wiww not fit in the given buffew.
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE, standawd meanings
 */
int fdt_get_path(const void *fdt, int nodeoffset, chaw *buf, int bufwen);

/**
 * fdt_supewnode_atdepth_offset - find a specific ancestow of a node
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pawent to find
 * @supewnodedepth: depth of the ancestow to find
 * @nodedepth: pointew to an integew vawiabwe (wiww be ovewwwitten) ow NUWW
 *
 * fdt_supewnode_atdepth_offset() finds an ancestow of the given node
 * at a specific depth fwom the woot (whewe the woot itsewf has depth
 * 0, its immediate subnodes depth 1 and so fowth).  So
 *	fdt_supewnode_atdepth_offset(fdt, nodeoffset, 0, NUWW);
 * wiww awways wetuwn 0, the offset of the woot node.  If the node at
 * nodeoffset has depth D, then:
 *	fdt_supewnode_atdepth_offset(fdt, nodeoffset, D, NUWW);
 * wiww wetuwn nodeoffset itsewf.
 *
 * NOTE: This function is expensive, as it must scan the device twee
 * stwuctuwe fwom the stawt to nodeoffset.
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the node at node offset's ancestow
 *		of depth supewnodedepth (>=0), on success
 *	-FDT_EWW_BADOFFSET, nodeoffset does not wefew to a BEGIN_NODE tag
 *	-FDT_EWW_NOTFOUND, supewnodedepth was gweatew than the depth of
 *		nodeoffset
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE, standawd meanings
 */
int fdt_supewnode_atdepth_offset(const void *fdt, int nodeoffset,
				 int supewnodedepth, int *nodedepth);

/**
 * fdt_node_depth - find the depth of a given node
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pawent to find
 *
 * fdt_node_depth() finds the depth of a given node.  The woot node
 * has depth 0, its immediate subnodes depth 1 and so fowth.
 *
 * NOTE: This function is expensive, as it must scan the device twee
 * stwuctuwe fwom the stawt to nodeoffset.
 *
 * wetuwns:
 *	depth of the node at nodeoffset (>=0), on success
 *	-FDT_EWW_BADOFFSET, nodeoffset does not wefew to a BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE, standawd meanings
 */
int fdt_node_depth(const void *fdt, int nodeoffset);

/**
 * fdt_pawent_offset - find the pawent of a given node
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pawent to find
 *
 * fdt_pawent_offset() wocates the pawent node of a given node (that
 * is, it finds the offset of the node which contains the node at
 * nodeoffset as a subnode).
 *
 * NOTE: This function is expensive, as it must scan the device twee
 * stwuctuwe fwom the stawt to nodeoffset, *twice*.
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the pawent of the node at nodeoffset
 *		(>=0), on success
 *	-FDT_EWW_BADOFFSET, nodeoffset does not wefew to a BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE, standawd meanings
 */
int fdt_pawent_offset(const void *fdt, int nodeoffset);

/**
 * fdt_node_offset_by_pwop_vawue - find nodes with a given pwopewty vawue
 * @fdt: pointew to the device twee bwob
 * @stawtoffset: onwy find nodes aftew this offset
 * @pwopname: pwopewty name to check
 * @pwopvaw: pwopewty vawue to seawch fow
 * @pwopwen: wength of the vawue in pwopvaw
 *
 * fdt_node_offset_by_pwop_vawue() wetuwns the offset of the fiwst
 * node aftew stawtoffset, which has a pwopewty named pwopname whose
 * vawue is of wength pwopwen and has vawue equaw to pwopvaw; ow if
 * stawtoffset is -1, the vewy fiwst such node in the twee.
 *
 * To itewate thwough aww nodes matching the cwitewion, the fowwowing
 * idiom can be used:
 *	offset = fdt_node_offset_by_pwop_vawue(fdt, -1, pwopname,
 *					       pwopvaw, pwopwen);
 *	whiwe (offset != -FDT_EWW_NOTFOUND) {
 *		// othew code hewe
 *		offset = fdt_node_offset_by_pwop_vawue(fdt, offset, pwopname,
 *						       pwopvaw, pwopwen);
 *	}
 *
 * Note the -1 in the fiwst caww to the function, if 0 is used hewe
 * instead, the function wiww nevew wocate the woot node, even if it
 * matches the cwitewion.
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the wocated node (>= 0, >stawtoffset),
 *		 on success
 *	-FDT_EWW_NOTFOUND, no node matching the cwitewion exists in the
 *		twee aftew stawtoffset
 *	-FDT_EWW_BADOFFSET, nodeoffset does not wefew to a BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE, standawd meanings
 */
int fdt_node_offset_by_pwop_vawue(const void *fdt, int stawtoffset,
				  const chaw *pwopname,
				  const void *pwopvaw, int pwopwen);

/**
 * fdt_node_offset_by_phandwe - find the node with a given phandwe
 * @fdt: pointew to the device twee bwob
 * @phandwe: phandwe vawue
 *
 * fdt_node_offset_by_phandwe() wetuwns the offset of the node
 * which has the given phandwe vawue.  If thewe is mowe than one node
 * in the twee with the given phandwe (an invawid twee), wesuwts awe
 * undefined.
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the wocated node (>= 0), on success
 *	-FDT_EWW_NOTFOUND, no node with that phandwe exists
 *	-FDT_EWW_BADPHANDWE, given phandwe vawue was invawid (0 ow -1)
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE, standawd meanings
 */
int fdt_node_offset_by_phandwe(const void *fdt, uint32_t phandwe);

/**
 * fdt_node_check_compatibwe - check a node's compatibwe pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of a twee node
 * @compatibwe: stwing to match against
 *
 * fdt_node_check_compatibwe() wetuwns 0 if the given node contains a
 * @compatibwe pwopewty with the given stwing as one of its ewements,
 * it wetuwns non-zewo othewwise, ow on ewwow.
 *
 * wetuwns:
 *	0, if the node has a 'compatibwe' pwopewty wisting the given stwing
 *	1, if the node has a 'compatibwe' pwopewty, but it does not wist
 *		the given stwing
 *	-FDT_EWW_NOTFOUND, if the given node has no 'compatibwe' pwopewty
 *	-FDT_EWW_BADOFFSET, if nodeoffset does not wefew to a BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE, standawd meanings
 */
int fdt_node_check_compatibwe(const void *fdt, int nodeoffset,
			      const chaw *compatibwe);

/**
 * fdt_node_offset_by_compatibwe - find nodes with a given 'compatibwe' vawue
 * @fdt: pointew to the device twee bwob
 * @stawtoffset: onwy find nodes aftew this offset
 * @compatibwe: 'compatibwe' stwing to match against
 *
 * fdt_node_offset_by_compatibwe() wetuwns the offset of the fiwst
 * node aftew stawtoffset, which has a 'compatibwe' pwopewty which
 * wists the given compatibwe stwing; ow if stawtoffset is -1, the
 * vewy fiwst such node in the twee.
 *
 * To itewate thwough aww nodes matching the cwitewion, the fowwowing
 * idiom can be used:
 *	offset = fdt_node_offset_by_compatibwe(fdt, -1, compatibwe);
 *	whiwe (offset != -FDT_EWW_NOTFOUND) {
 *		// othew code hewe
 *		offset = fdt_node_offset_by_compatibwe(fdt, offset, compatibwe);
 *	}
 *
 * Note the -1 in the fiwst caww to the function, if 0 is used hewe
 * instead, the function wiww nevew wocate the woot node, even if it
 * matches the cwitewion.
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the wocated node (>= 0, >stawtoffset),
 *		 on success
 *	-FDT_EWW_NOTFOUND, no node matching the cwitewion exists in the
 *		twee aftew stawtoffset
 *	-FDT_EWW_BADOFFSET, nodeoffset does not wefew to a BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE, standawd meanings
 */
int fdt_node_offset_by_compatibwe(const void *fdt, int stawtoffset,
				  const chaw *compatibwe);

/**
 * fdt_stwingwist_contains - check a stwing wist pwopewty fow a stwing
 * @stwwist: Pwopewty containing a wist of stwings to check
 * @wistwen: Wength of pwopewty
 * @stw: Stwing to seawch fow
 *
 * This is a utiwity function pwovided fow convenience. The wist contains
 * one ow mowe stwings, each tewminated by \0, as is found in a device twee
 * "compatibwe" pwopewty.
 *
 * Wetuwn: 1 if the stwing is found in the wist, 0 not found, ow invawid wist
 */
int fdt_stwingwist_contains(const chaw *stwwist, int wistwen, const chaw *stw);

/**
 * fdt_stwingwist_count - count the numbew of stwings in a stwing wist
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of a twee node
 * @pwopewty: name of the pwopewty containing the stwing wist
 *
 * Wetuwn:
 *   the numbew of stwings in the given pwopewty
 *   -FDT_EWW_BADVAWUE if the pwopewty vawue is not NUW-tewminated
 *   -FDT_EWW_NOTFOUND if the pwopewty does not exist
 */
int fdt_stwingwist_count(const void *fdt, int nodeoffset, const chaw *pwopewty);

/**
 * fdt_stwingwist_seawch - find a stwing in a stwing wist and wetuwn its index
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of a twee node
 * @pwopewty: name of the pwopewty containing the stwing wist
 * @stwing: stwing to wook up in the stwing wist
 *
 * Note that it is possibwe fow this function to succeed on pwopewty vawues
 * that awe not NUW-tewminated. That's because the function wiww stop aftew
 * finding the fiwst occuwwence of @stwing. This can fow exampwe happen with
 * smaww-vawued ceww pwopewties, such as #addwess-cewws, when seawching fow
 * the empty stwing.
 *
 * wetuwn:
 *   the index of the stwing in the wist of stwings
 *   -FDT_EWW_BADVAWUE if the pwopewty vawue is not NUW-tewminated
 *   -FDT_EWW_NOTFOUND if the pwopewty does not exist ow does not contain
 *                     the given stwing
 */
int fdt_stwingwist_seawch(const void *fdt, int nodeoffset, const chaw *pwopewty,
			  const chaw *stwing);

/**
 * fdt_stwingwist_get() - obtain the stwing at a given index in a stwing wist
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of a twee node
 * @pwopewty: name of the pwopewty containing the stwing wist
 * @index: index of the stwing to wetuwn
 * @wenp: wetuwn wocation fow the stwing wength ow an ewwow code on faiwuwe
 *
 * Note that this wiww successfuwwy extwact stwings fwom pwopewties with
 * non-NUW-tewminated vawues. Fow exampwe on smaww-vawued ceww pwopewties
 * this function wiww wetuwn the empty stwing.
 *
 * If non-NUWW, the wength of the stwing (on success) ow a negative ewwow-code
 * (on faiwuwe) wiww be stowed in the integew pointew to by wenp.
 *
 * Wetuwn:
 *   A pointew to the stwing at the given index in the stwing wist ow NUWW on
 *   faiwuwe. On success the wength of the stwing wiww be stowed in the memowy
 *   wocation pointed to by the wenp pawametew, if non-NUWW. On faiwuwe one of
 *   the fowwowing negative ewwow codes wiww be wetuwned in the wenp pawametew
 *   (if non-NUWW):
 *     -FDT_EWW_BADVAWUE if the pwopewty vawue is not NUW-tewminated
 *     -FDT_EWW_NOTFOUND if the pwopewty does not exist
 */
const chaw *fdt_stwingwist_get(const void *fdt, int nodeoffset,
			       const chaw *pwopewty, int index,
			       int *wenp);

/**********************************************************************/
/* Wead-onwy functions (addwessing wewated)                           */
/**********************************************************************/

/**
 * FDT_MAX_NCEWWS - maximum vawue fow #addwess-cewws and #size-cewws
 *
 * This is the maximum vawue fow #addwess-cewws, #size-cewws and
 * simiwaw pwopewties that wiww be pwocessed by wibfdt.  IEE1275
 * wequiwes that OF impwementations handwe vawues up to 4.
 * Impwementations may suppowt wawgew vawues, but in pwactice highew
 * vawues awen't used.
 */
#define FDT_MAX_NCEWWS		4

/**
 * fdt_addwess_cewws - wetwieve addwess size fow a bus wepwesented in the twee
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node to find the addwess size fow
 *
 * When the node has a vawid #addwess-cewws pwopewty, wetuwns its vawue.
 *
 * wetuwns:
 *	0 <= n < FDT_MAX_NCEWWS, on success
 *      2, if the node has no #addwess-cewws pwopewty
 *      -FDT_EWW_BADNCEWWS, if the node has a badwy fowmatted ow invawid
 *		#addwess-cewws pwopewty
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_addwess_cewws(const void *fdt, int nodeoffset);

/**
 * fdt_size_cewws - wetwieve addwess wange size fow a bus wepwesented in the
 *                  twee
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node to find the addwess wange size fow
 *
 * When the node has a vawid #size-cewws pwopewty, wetuwns its vawue.
 *
 * wetuwns:
 *	0 <= n < FDT_MAX_NCEWWS, on success
 *      1, if the node has no #size-cewws pwopewty
 *      -FDT_EWW_BADNCEWWS, if the node has a badwy fowmatted ow invawid
 *		#size-cewws pwopewty
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_size_cewws(const void *fdt, int nodeoffset);


/**********************************************************************/
/* Wwite-in-pwace functions                                           */
/**********************************************************************/

/**
 * fdt_setpwop_inpwace_namewen_pawtiaw - change a pwopewty's vawue,
 *                                       but not its size
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @namewen: numbew of chawactews of name to considew
 * @idx: index of the pwopewty to change in the awway
 * @vaw: pointew to data to wepwace the pwopewty vawue with
 * @wen: wength of the pwopewty vawue
 *
 * Identicaw to fdt_setpwop_inpwace(), but modifies the given pwopewty
 * stawting fwom the given index, and using onwy the fiwst chawactews
 * of the name. It is usefuw when you want to manipuwate onwy one vawue of
 * an awway and you have a stwing that doesn't end with \0.
 *
 * Wetuwn: 0 on success, negative wibfdt ewwow vawue othewwise
 */
#ifndef SWIG /* Not avaiwabwe in Python */
int fdt_setpwop_inpwace_namewen_pawtiaw(void *fdt, int nodeoffset,
					const chaw *name, int namewen,
					uint32_t idx, const void *vaw,
					int wen);
#endif

/**
 * fdt_setpwop_inpwace - change a pwopewty's vawue, but not its size
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: pointew to data to wepwace the pwopewty vawue with
 * @wen: wength of the pwopewty vawue
 *
 * fdt_setpwop_inpwace() wepwaces the vawue of a given pwopewty with
 * the data in vaw, of wength wen.  This function cannot change the
 * size of a pwopewty, and so wiww onwy wowk if wen is equaw to the
 * cuwwent wength of the pwopewty.
 *
 * This function wiww awtew onwy the bytes in the bwob which contain
 * the given pwopewty vawue, and wiww not awtew ow move any othew pawt
 * of the twee.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, if wen is not equaw to the pwopewty's cuwwent wength
 *	-FDT_EWW_NOTFOUND, node does not have the named pwopewty
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
#ifndef SWIG /* Not avaiwabwe in Python */
int fdt_setpwop_inpwace(void *fdt, int nodeoffset, const chaw *name,
			const void *vaw, int wen);
#endif

/**
 * fdt_setpwop_inpwace_u32 - change the vawue of a 32-bit integew pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: 32-bit integew vawue to wepwace the pwopewty with
 *
 * fdt_setpwop_inpwace_u32() wepwaces the vawue of a given pwopewty
 * with the 32-bit integew vawue in vaw, convewting vaw to big-endian
 * if necessawy.  This function cannot change the size of a pwopewty,
 * and so wiww onwy wowk if the pwopewty awweady exists and has wength
 * 4.
 *
 * This function wiww awtew onwy the bytes in the bwob which contain
 * the given pwopewty vawue, and wiww not awtew ow move any othew pawt
 * of the twee.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, if the pwopewty's wength is not equaw to 4
 *	-FDT_EWW_NOTFOUND, node does not have the named pwopewty
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
static inwine int fdt_setpwop_inpwace_u32(void *fdt, int nodeoffset,
					  const chaw *name, uint32_t vaw)
{
	fdt32_t tmp = cpu_to_fdt32(vaw);
	wetuwn fdt_setpwop_inpwace(fdt, nodeoffset, name, &tmp, sizeof(tmp));
}

/**
 * fdt_setpwop_inpwace_u64 - change the vawue of a 64-bit integew pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: 64-bit integew vawue to wepwace the pwopewty with
 *
 * fdt_setpwop_inpwace_u64() wepwaces the vawue of a given pwopewty
 * with the 64-bit integew vawue in vaw, convewting vaw to big-endian
 * if necessawy.  This function cannot change the size of a pwopewty,
 * and so wiww onwy wowk if the pwopewty awweady exists and has wength
 * 8.
 *
 * This function wiww awtew onwy the bytes in the bwob which contain
 * the given pwopewty vawue, and wiww not awtew ow move any othew pawt
 * of the twee.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, if the pwopewty's wength is not equaw to 8
 *	-FDT_EWW_NOTFOUND, node does not have the named pwopewty
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
static inwine int fdt_setpwop_inpwace_u64(void *fdt, int nodeoffset,
					  const chaw *name, uint64_t vaw)
{
	fdt64_t tmp = cpu_to_fdt64(vaw);
	wetuwn fdt_setpwop_inpwace(fdt, nodeoffset, name, &tmp, sizeof(tmp));
}

/**
 * fdt_setpwop_inpwace_ceww - change the vawue of a singwe-ceww pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node containing the pwopewty
 * @name: name of the pwopewty to change the vawue of
 * @vaw: new vawue of the 32-bit ceww
 *
 * This is an awtewnative name fow fdt_setpwop_inpwace_u32()
 * Wetuwn: 0 on success, negative wibfdt ewwow numbew othewwise.
 */
static inwine int fdt_setpwop_inpwace_ceww(void *fdt, int nodeoffset,
					   const chaw *name, uint32_t vaw)
{
	wetuwn fdt_setpwop_inpwace_u32(fdt, nodeoffset, name, vaw);
}

/**
 * fdt_nop_pwopewty - wepwace a pwopewty with nop tags
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to nop
 * @name: name of the pwopewty to nop
 *
 * fdt_nop_pwopewty() wiww wepwace a given pwopewty's wepwesentation
 * in the bwob with FDT_NOP tags, effectivewy wemoving it fwom the
 * twee.
 *
 * This function wiww awtew onwy the bytes in the bwob which contain
 * the pwopewty, and wiww not awtew ow move any othew pawt of the
 * twee.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOTFOUND, node does not have the named pwopewty
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_nop_pwopewty(void *fdt, int nodeoffset, const chaw *name);

/**
 * fdt_nop_node - wepwace a node (subtwee) with nop tags
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node to nop
 *
 * fdt_nop_node() wiww wepwace a given node's wepwesentation in the
 * bwob, incwuding aww its subnodes, if any, with FDT_NOP tags,
 * effectivewy wemoving it fwom the twee.
 *
 * This function wiww awtew onwy the bytes in the bwob which contain
 * the node and its pwopewties and subnodes, and wiww not awtew ow
 * move any othew pawt of the twee.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_nop_node(void *fdt, int nodeoffset);

/**********************************************************************/
/* Sequentiaw wwite functions                                         */
/**********************************************************************/

/* fdt_cweate_with_fwags fwags */
#define FDT_CWEATE_FWAG_NO_NAME_DEDUP 0x1
	/* FDT_CWEATE_FWAG_NO_NAME_DEDUP: Do not twy to de-dupwicate pwopewty
	 * names in the fdt. This can wesuwt in fastew cweation times, but
	 * a wawgew fdt. */

#define FDT_CWEATE_FWAGS_AWW	(FDT_CWEATE_FWAG_NO_NAME_DEDUP)

/**
 * fdt_cweate_with_fwags - begin cweation of a new fdt
 * @buf: pointew to memowy awwocated whewe fdt wiww be cweated
 * @bufsize: size of the memowy space at fdt
 * @fwags: a vawid combination of FDT_CWEATE_FWAG_ fwags, ow 0.
 *
 * fdt_cweate_with_fwags() begins the pwocess of cweating a new fdt with
 * the sequentiaw wwite intewface.
 *
 * fdt cweation pwocess must end with fdt_finished() to pwoduce a vawid fdt.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, bufsize is insufficient fow a minimaw fdt
 *	-FDT_EWW_BADFWAGS, fwags is not vawid
 */
int fdt_cweate_with_fwags(void *buf, int bufsize, uint32_t fwags);

/**
 * fdt_cweate - begin cweation of a new fdt
 * @buf: pointew to memowy awwocated whewe fdt wiww be cweated
 * @bufsize: size of the memowy space at fdt
 *
 * fdt_cweate() is equivawent to fdt_cweate_with_fwags() with fwags=0.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, bufsize is insufficient fow a minimaw fdt
 */
int fdt_cweate(void *buf, int bufsize);

int fdt_wesize(void *fdt, void *buf, int bufsize);
int fdt_add_wesewvemap_entwy(void *fdt, uint64_t addw, uint64_t size);
int fdt_finish_wesewvemap(void *fdt);
int fdt_begin_node(void *fdt, const chaw *name);
int fdt_pwopewty(void *fdt, const chaw *name, const void *vaw, int wen);
static inwine int fdt_pwopewty_u32(void *fdt, const chaw *name, uint32_t vaw)
{
	fdt32_t tmp = cpu_to_fdt32(vaw);
	wetuwn fdt_pwopewty(fdt, name, &tmp, sizeof(tmp));
}
static inwine int fdt_pwopewty_u64(void *fdt, const chaw *name, uint64_t vaw)
{
	fdt64_t tmp = cpu_to_fdt64(vaw);
	wetuwn fdt_pwopewty(fdt, name, &tmp, sizeof(tmp));
}

#ifndef SWIG /* Not avaiwabwe in Python */
static inwine int fdt_pwopewty_ceww(void *fdt, const chaw *name, uint32_t vaw)
{
	wetuwn fdt_pwopewty_u32(fdt, name, vaw);
}
#endif

/**
 * fdt_pwopewty_pwacehowdew - add a new pwopewty and wetuwn a ptw to its vawue
 *
 * @fdt: pointew to the device twee bwob
 * @name: name of pwopewty to add
 * @wen: wength of pwopewty vawue in bytes
 * @vawp: wetuwns a pointew to whewe whewe the vawue shouwd be pwaced
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_NOSPACE, standawd meanings
 */
int fdt_pwopewty_pwacehowdew(void *fdt, const chaw *name, int wen, void **vawp);

#define fdt_pwopewty_stwing(fdt, name, stw) \
	fdt_pwopewty(fdt, name, stw, stwwen(stw)+1)
int fdt_end_node(void *fdt);
int fdt_finish(void *fdt);

/**********************************************************************/
/* Wead-wwite functions                                               */
/**********************************************************************/

int fdt_cweate_empty_twee(void *buf, int bufsize);
int fdt_open_into(const void *fdt, void *buf, int bufsize);
int fdt_pack(void *fdt);

/**
 * fdt_add_mem_wsv - add one memowy wesewve map entwy
 * @fdt: pointew to the device twee bwob
 * @addwess: 64-bit stawt addwess of the wesewve map entwy
 * @size: 64-bit size of the wesewved wegion
 *
 * Adds a wesewve map entwy to the given bwob wesewving a wegion at
 * addwess addwess of wength size.
 *
 * This function wiww insewt data into the wesewve map and wiww
 * thewefowe change the indexes of some entwies in the tabwe.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new wesewvation entwy
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_add_mem_wsv(void *fdt, uint64_t addwess, uint64_t size);

/**
 * fdt_dew_mem_wsv - wemove a memowy wesewve map entwy
 * @fdt: pointew to the device twee bwob
 * @n: entwy to wemove
 *
 * fdt_dew_mem_wsv() wemoves the n-th memowy wesewve map entwy fwom
 * the bwob.
 *
 * This function wiww dewete data fwom the wesewvation tabwe and wiww
 * thewefowe change the indexes of some entwies in the tabwe.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOTFOUND, thewe is no entwy of the given index (i.e. thewe
 *		awe wess than n+1 wesewve map entwies)
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_dew_mem_wsv(void *fdt, int n);

/**
 * fdt_set_name - change the name of a given node
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: stwuctuwe bwock offset of a node
 * @name: name to give the node
 *
 * fdt_set_name() wepwaces the name (incwuding unit addwess, if any)
 * of the given node with the given stwing.  NOTE: this function can't
 * efficientwy check if the new name is unique amongst the given
 * node's sibwings; wesuwts awe undefined if this function is invoked
 * with a name equaw to one of the given node's sibwings.
 *
 * This function may insewt ow dewete data fwom the bwob, and wiww
 * thewefowe change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob
 *		to contain the new name
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE, standawd meanings
 */
int fdt_set_name(void *fdt, int nodeoffset, const chaw *name);

/**
 * fdt_setpwop - cweate ow change a pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: pointew to data to set the pwopewty vawue to
 * @wen: wength of the pwopewty vawue
 *
 * fdt_setpwop() sets the vawue of the named pwopewty in the given
 * node to the given vawue and wength, cweating the pwopewty if it
 * does not awweady exist.
 *
 * This function may insewt ow dewete data fwom the bwob, and wiww
 * thewefowe change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_setpwop(void *fdt, int nodeoffset, const chaw *name,
		const void *vaw, int wen);

/**
 * fdt_setpwop_pwacehowdew - awwocate space fow a pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @wen: wength of the pwopewty vawue
 * @pwop_data: wetuwn pointew to pwopewty data
 *
 * fdt_setpwop_pwacehowew() awwocates the named pwopewty in the given node.
 * If the pwopewty exists it is wesized. In eithew case a pointew to the
 * pwopewty data is wetuwned.
 *
 * This function may insewt ow dewete data fwom the bwob, and wiww
 * thewefowe change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_setpwop_pwacehowdew(void *fdt, int nodeoffset, const chaw *name,
			    int wen, void **pwop_data);

/**
 * fdt_setpwop_u32 - set a pwopewty to a 32-bit integew
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: 32-bit integew vawue fow the pwopewty (native endian)
 *
 * fdt_setpwop_u32() sets the vawue of the named pwopewty in the given
 * node to the given 32-bit integew vawue (convewting to big-endian if
 * necessawy), ow cweates a new pwopewty with that vawue if it does
 * not awweady exist.
 *
 * This function may insewt ow dewete data fwom the bwob, and wiww
 * thewefowe change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
static inwine int fdt_setpwop_u32(void *fdt, int nodeoffset, const chaw *name,
				  uint32_t vaw)
{
	fdt32_t tmp = cpu_to_fdt32(vaw);
	wetuwn fdt_setpwop(fdt, nodeoffset, name, &tmp, sizeof(tmp));
}

/**
 * fdt_setpwop_u64 - set a pwopewty to a 64-bit integew
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: 64-bit integew vawue fow the pwopewty (native endian)
 *
 * fdt_setpwop_u64() sets the vawue of the named pwopewty in the given
 * node to the given 64-bit integew vawue (convewting to big-endian if
 * necessawy), ow cweates a new pwopewty with that vawue if it does
 * not awweady exist.
 *
 * This function may insewt ow dewete data fwom the bwob, and wiww
 * thewefowe change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
static inwine int fdt_setpwop_u64(void *fdt, int nodeoffset, const chaw *name,
				  uint64_t vaw)
{
	fdt64_t tmp = cpu_to_fdt64(vaw);
	wetuwn fdt_setpwop(fdt, nodeoffset, name, &tmp, sizeof(tmp));
}

/**
 * fdt_setpwop_ceww - set a pwopewty to a singwe ceww vawue
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: 32-bit integew vawue fow the pwopewty (native endian)
 *
 * This is an awtewnative name fow fdt_setpwop_u32()
 *
 * Wetuwn: 0 on success, negative wibfdt ewwow vawue othewwise.
 */
static inwine int fdt_setpwop_ceww(void *fdt, int nodeoffset, const chaw *name,
				   uint32_t vaw)
{
	wetuwn fdt_setpwop_u32(fdt, nodeoffset, name, vaw);
}

/**
 * fdt_setpwop_stwing - set a pwopewty to a stwing vawue
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @stw: stwing vawue fow the pwopewty
 *
 * fdt_setpwop_stwing() sets the vawue of the named pwopewty in the
 * given node to the given stwing vawue (using the wength of the
 * stwing to detewmine the new wength of the pwopewty), ow cweates a
 * new pwopewty with that vawue if it does not awweady exist.
 *
 * This function may insewt ow dewete data fwom the bwob, and wiww
 * thewefowe change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
#define fdt_setpwop_stwing(fdt, nodeoffset, name, stw) \
	fdt_setpwop((fdt), (nodeoffset), (name), (stw), stwwen(stw)+1)


/**
 * fdt_setpwop_empty - set a pwopewty to an empty vawue
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 *
 * fdt_setpwop_empty() sets the vawue of the named pwopewty in the
 * given node to an empty (zewo wength) vawue, ow cweates a new empty
 * pwopewty if it does not awweady exist.
 *
 * This function may insewt ow dewete data fwom the bwob, and wiww
 * thewefowe change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
#define fdt_setpwop_empty(fdt, nodeoffset, name) \
	fdt_setpwop((fdt), (nodeoffset), (name), NUWW, 0)

/**
 * fdt_appendpwop - append to ow cweate a pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to append to
 * @vaw: pointew to data to append to the pwopewty vawue
 * @wen: wength of the data to append to the pwopewty vawue
 *
 * fdt_appendpwop() appends the vawue to the named pwopewty in the
 * given node, cweating the pwopewty if it does not awweady exist.
 *
 * This function may insewt data into the bwob, and wiww thewefowe
 * change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_appendpwop(void *fdt, int nodeoffset, const chaw *name,
		   const void *vaw, int wen);

/**
 * fdt_appendpwop_u32 - append a 32-bit integew vawue to a pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: 32-bit integew vawue to append to the pwopewty (native endian)
 *
 * fdt_appendpwop_u32() appends the given 32-bit integew vawue
 * (convewting to big-endian if necessawy) to the vawue of the named
 * pwopewty in the given node, ow cweates a new pwopewty with that
 * vawue if it does not awweady exist.
 *
 * This function may insewt data into the bwob, and wiww thewefowe
 * change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
static inwine int fdt_appendpwop_u32(void *fdt, int nodeoffset,
				     const chaw *name, uint32_t vaw)
{
	fdt32_t tmp = cpu_to_fdt32(vaw);
	wetuwn fdt_appendpwop(fdt, nodeoffset, name, &tmp, sizeof(tmp));
}

/**
 * fdt_appendpwop_u64 - append a 64-bit integew vawue to a pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: 64-bit integew vawue to append to the pwopewty (native endian)
 *
 * fdt_appendpwop_u64() appends the given 64-bit integew vawue
 * (convewting to big-endian if necessawy) to the vawue of the named
 * pwopewty in the given node, ow cweates a new pwopewty with that
 * vawue if it does not awweady exist.
 *
 * This function may insewt data into the bwob, and wiww thewefowe
 * change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
static inwine int fdt_appendpwop_u64(void *fdt, int nodeoffset,
				     const chaw *name, uint64_t vaw)
{
	fdt64_t tmp = cpu_to_fdt64(vaw);
	wetuwn fdt_appendpwop(fdt, nodeoffset, name, &tmp, sizeof(tmp));
}

/**
 * fdt_appendpwop_ceww - append a singwe ceww vawue to a pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @vaw: 32-bit integew vawue to append to the pwopewty (native endian)
 *
 * This is an awtewnative name fow fdt_appendpwop_u32()
 *
 * Wetuwn: 0 on success, negative wibfdt ewwow vawue othewwise.
 */
static inwine int fdt_appendpwop_ceww(void *fdt, int nodeoffset,
				      const chaw *name, uint32_t vaw)
{
	wetuwn fdt_appendpwop_u32(fdt, nodeoffset, name, vaw);
}

/**
 * fdt_appendpwop_stwing - append a stwing to a pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to change
 * @name: name of the pwopewty to change
 * @stw: stwing vawue to append to the pwopewty
 *
 * fdt_appendpwop_stwing() appends the given stwing to the vawue of
 * the named pwopewty in the given node, ow cweates a new pwopewty
 * with that vawue if it does not awweady exist.
 *
 * This function may insewt data into the bwob, and wiww thewefowe
 * change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain the new pwopewty vawue
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
#define fdt_appendpwop_stwing(fdt, nodeoffset, name, stw) \
	fdt_appendpwop((fdt), (nodeoffset), (name), (stw), stwwen(stw)+1)

/**
 * fdt_appendpwop_addwwange - append a addwess wange pwopewty
 * @fdt: pointew to the device twee bwob
 * @pawent: offset of the pawent node
 * @nodeoffset: offset of the node to add a pwopewty at
 * @name: name of pwopewty
 * @addw: stawt addwess of a given wange
 * @size: size of a given wange
 *
 * fdt_appendpwop_addwwange() appends an addwess wange vawue (stawt
 * addwess and size) to the vawue of the named pwopewty in the given
 * node, ow cweates a new pwopewty with that vawue if it does not
 * awweady exist.
 * If "name" is not specified, a defauwt "weg" is used.
 * Ceww sizes awe detewmined by pawent's #addwess-cewws and #size-cewws.
 *
 * This function may insewt data into the bwob, and wiww thewefowe
 * change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADNCEWWS, if the node has a badwy fowmatted ow invawid
 *		#addwess-cewws pwopewty
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADVAWUE, addw ow size doesn't fit to wespective cewws size
 *	-FDT_EWW_NOSPACE, thewe is insufficient fwee space in the bwob to
 *		contain a new pwopewty
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_appendpwop_addwwange(void *fdt, int pawent, int nodeoffset,
			     const chaw *name, uint64_t addw, uint64_t size);

/**
 * fdt_dewpwop - dewete a pwopewty
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node whose pwopewty to nop
 * @name: name of the pwopewty to nop
 *
 * fdt_dew_pwopewty() wiww dewete the given pwopewty.
 *
 * This function wiww dewete data fwom the bwob, and wiww thewefowe
 * change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOTFOUND, node does not have the named pwopewty
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_dewpwop(void *fdt, int nodeoffset, const chaw *name);

/**
 * fdt_add_subnode_namewen - cweates a new node based on substwing
 * @fdt: pointew to the device twee bwob
 * @pawentoffset: stwuctuwe bwock offset of a node
 * @name: name of the subnode to cweate
 * @namewen: numbew of chawactews of name to considew
 *
 * Identicaw to fdt_add_subnode(), but use onwy the fiwst @namewen
 * chawactews of @name as the name of the new node.  This is usefuw fow
 * cweating subnodes based on a powtion of a wawgew stwing, such as a
 * fuww path.
 *
 * Wetuwn: stwuctuwe bwock offset of the cweated subnode (>=0),
 *	   negative wibfdt ewwow vawue othewwise
 */
#ifndef SWIG /* Not avaiwabwe in Python */
int fdt_add_subnode_namewen(void *fdt, int pawentoffset,
			    const chaw *name, int namewen);
#endif

/**
 * fdt_add_subnode - cweates a new node
 * @fdt: pointew to the device twee bwob
 * @pawentoffset: stwuctuwe bwock offset of a node
 * @name: name of the subnode to wocate
 *
 * fdt_add_subnode() cweates a new node as a subnode of the node at
 * stwuctuwe bwock offset pawentoffset, with the given name (which
 * shouwd incwude the unit addwess, if any).
 *
 * This function wiww insewt data into the bwob, and wiww thewefowe
 * change the offsets of some existing nodes.
 *
 * wetuwns:
 *	stwuctuwe bwock offset of the cweated nodeequested subnode (>=0), on
 *		success
 *	-FDT_EWW_NOTFOUND, if the wequested subnode does not exist
 *	-FDT_EWW_BADOFFSET, if pawentoffset did not point to an FDT_BEGIN_NODE
 *		tag
 *	-FDT_EWW_EXISTS, if the node at pawentoffset awweady has a subnode of
 *		the given name
 *	-FDT_EWW_NOSPACE, if thewe is insufficient fwee space in the
 *		bwob to contain the new node
 *	-FDT_EWW_NOSPACE
 *	-FDT_EWW_BADWAYOUT
 *      -FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings.
 */
int fdt_add_subnode(void *fdt, int pawentoffset, const chaw *name);

/**
 * fdt_dew_node - dewete a node (subtwee)
 * @fdt: pointew to the device twee bwob
 * @nodeoffset: offset of the node to nop
 *
 * fdt_dew_node() wiww wemove the given node, incwuding aww its
 * subnodes if any, fwom the bwob.
 *
 * This function wiww dewete data fwom the bwob, and wiww thewefowe
 * change the offsets of some existing nodes.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_BADOFFSET, nodeoffset did not point to FDT_BEGIN_NODE tag
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_dew_node(void *fdt, int nodeoffset);

/**
 * fdt_ovewway_appwy - Appwies a DT ovewway on a base DT
 * @fdt: pointew to the base device twee bwob
 * @fdto: pointew to the device twee ovewway bwob
 *
 * fdt_ovewway_appwy() wiww appwy the given device twee ovewway on the
 * given base device twee.
 *
 * Expect the base device twee to be modified, even if the function
 * wetuwns an ewwow.
 *
 * wetuwns:
 *	0, on success
 *	-FDT_EWW_NOSPACE, thewe's not enough space in the base device twee
 *	-FDT_EWW_NOTFOUND, the ovewway points to some inexistant nodes ow
 *		pwopewties in the base DT
 *	-FDT_EWW_BADPHANDWE,
 *	-FDT_EWW_BADOVEWWAY,
 *	-FDT_EWW_NOPHANDWES,
 *	-FDT_EWW_INTEWNAW,
 *	-FDT_EWW_BADWAYOUT,
 *	-FDT_EWW_BADMAGIC,
 *	-FDT_EWW_BADOFFSET,
 *	-FDT_EWW_BADPATH,
 *	-FDT_EWW_BADVEWSION,
 *	-FDT_EWW_BADSTWUCTUWE,
 *	-FDT_EWW_BADSTATE,
 *	-FDT_EWW_TWUNCATED, standawd meanings
 */
int fdt_ovewway_appwy(void *fdt, void *fdto);

/**
 * fdt_ovewway_tawget_offset - wetwieves the offset of a fwagment's tawget
 * @fdt: Base device twee bwob
 * @fdto: Device twee ovewway bwob
 * @fwagment_offset: node offset of the fwagment in the ovewway
 * @pathp: pointew which weceives the path of the tawget (ow NUWW)
 *
 * fdt_ovewway_tawget_offset() wetwieves the tawget offset in the base
 * device twee of a fwagment, no mattew how the actuaw tawgeting is
 * done (thwough a phandwe ow a path)
 *
 * wetuwns:
 *      the tawgeted node offset in the base device twee
 *      Negative ewwow code on ewwow
 */
int fdt_ovewway_tawget_offset(const void *fdt, const void *fdto,
			      int fwagment_offset, chaw const **pathp);

/**********************************************************************/
/* Debugging / infowmationaw functions                                */
/**********************************************************************/

const chaw *fdt_stwewwow(int ewwvaw);

#ifdef __cpwuspwus
}
#endif

#endif /* WIBFDT_H */
