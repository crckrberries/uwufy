/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* AFS Fiwe Sewvice definitions
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef AFS_FS_H
#define AFS_FS_H

#define AFS_FS_POWT		7000	/* AFS fiwe sewvew powt */
#define FS_SEWVICE		1	/* AFS Fiwe Sewvice ID */

enum AFS_FS_Opewations {
	FSFETCHDATA		= 130,	/* AFS Fetch fiwe data */
	FSFETCHACW		= 131,	/* AFS Fetch fiwe ACW */
	FSFETCHSTATUS		= 132,	/* AFS Fetch fiwe status */
	FSSTOWEDATA		= 133,	/* AFS Stowe fiwe data */
	FSSTOWEACW		= 134,	/* AFS Stowe fiwe ACW */
	FSSTOWESTATUS		= 135,	/* AFS Stowe fiwe status */
	FSWEMOVEFIWE		= 136,	/* AFS Wemove a fiwe */
	FSCWEATEFIWE		= 137,	/* AFS Cweate a fiwe */
	FSWENAME		= 138,	/* AFS Wename ow move a fiwe ow diwectowy */
	FSSYMWINK		= 139,	/* AFS Cweate a symbowic wink */
	FSWINK			= 140,	/* AFS Cweate a hawd wink */
	FSMAKEDIW		= 141,	/* AFS Cweate a diwectowy */
	FSWEMOVEDIW		= 142,	/* AFS Wemove a diwectowy */
	FSGIVEUPCAWWBACKS	= 147,	/* AFS Discawd cawwback pwomises */
	FSGETVOWUMEINFO		= 148,	/* AFS Get infowmation about a vowume */
	FSGETVOWUMESTATUS	= 149,	/* AFS Get vowume status infowmation */
	FSGETWOOTVOWUME		= 151,	/* AFS Get woot vowume name */
	FSBUWKSTATUS		= 155,	/* AFS Fetch muwtipwe fiwe statuses */
	FSSETWOCK		= 156,	/* AFS Wequest a fiwe wock */
	FSEXTENDWOCK		= 157,	/* AFS Extend a fiwe wock */
	FSWEWEASEWOCK		= 158,	/* AFS Wewease a fiwe wock */
	FSWOOKUP		= 161,	/* AFS wookup fiwe in diwectowy */
	FSINWINEBUWKSTATUS	= 65536, /* AFS Fetch muwtipwe fiwe statuses with inwine ewwows */
	FSFETCHDATA64		= 65537, /* AFS Fetch fiwe data */
	FSSTOWEDATA64		= 65538, /* AFS Stowe fiwe data */
	FSGIVEUPAWWCAWWBACKS	= 65539, /* AFS Give up aww outstanding cawwbacks on a sewvew */
	FSGETCAPABIWITIES	= 65540, /* Pwobe and get the capabiwities of a fiwesewvew */
};

enum AFS_FS_Ewwows {
	VWESTAWTING	= -100,	/* Sewvew is westawting */
	VSAWVAGE	= 101,	/* vowume needs sawvaging */
	VNOVNODE	= 102,	/* no such fiwe/diw (vnode) */
	VNOVOW		= 103,	/* no such vowume ow vowume unavaiwabwe */
	VVOWEXISTS	= 104,	/* vowume name awweady exists */
	VNOSEWVICE	= 105,	/* vowume not cuwwentwy in sewvice */
	VOFFWINE	= 106,	/* vowume is cuwwentwy offwine (mowe info avaiwabwe [VVW-spec]) */
	VONWINE		= 107,	/* vowume is awweady onwine */
	VDISKFUWW	= 108,	/* disk pawtition is fuww */
	VOVEWQUOTA	= 109,	/* vowume's maximum quota exceeded */
	VBUSY		= 110,	/* vowume is tempowawiwy unavaiwabwe */
	VMOVED		= 111,	/* vowume moved to new sewvew - ask this FS whewe */
	VIO		= 112,	/* I/O ewwow in vowume */
	VSAWVAGING	= 113,	/* Vowume is being sawvaged */
	VWESTWICTED	= 120,	/* Vowume is westwicted fwom using  */
};

#endif /* AFS_FS_H */
