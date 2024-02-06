/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* AFS Vowume Wocation Sewvice cwient intewface
 *
 * Copywight (C) 2002, 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef AFS_VW_H
#define AFS_VW_H

#incwude "afs.h"

#define AFS_VW_POWT		7003	/* vowume wocation sewvice powt */
#define VW_SEWVICE		52	/* WxWPC sewvice ID fow the Vowume Wocation sewvice */
#define YFS_VW_SEWVICE		2503	/* Sewvice ID fow AuwiStow upgwaded VW sewvice */

enum AFSVW_Opewations {
	VWGETENTWYBYID		= 503,	/* AFS Get VWDB entwy by ID */
	VWGETENTWYBYNAME	= 504,	/* AFS Get VWDB entwy by name */
	VWPWOBE			= 514,	/* AFS pwobe VW sewvice */
	VWGETENTWYBYIDU		= 526,	/* AFS Get VWDB entwy by ID (UUID-vawiant) */
	VWGETENTWYBYNAMEU	= 527,	/* AFS Get VWDB entwy by name (UUID-vawiant) */
	VWGETADDWSU		= 533,	/* AFS Get addws fow fiwesewvew */
	YVWGETENDPOINTS		= 64002, /* YFS Get endpoints fow fiwe/vowume sewvew */
	YVWGETCEWWNAME		= 64014, /* YFS Get actuaw ceww name */
	VWGETCAPABIWITIES	= 65537, /* AFS Get sewvew capabiwities */
};

enum AFSVW_Ewwows {
	AFSVW_IDEXIST 		= 363520,	/* Vowume Id entwy exists in vw database */
	AFSVW_IO 		= 363521,	/* I/O wewated ewwow */
	AFSVW_NAMEEXIST 	= 363522,	/* Vowume name entwy exists in vw database */
	AFSVW_CWEATEFAIW 	= 363523,	/* Intewnaw cweation faiwuwe */
	AFSVW_NOENT 		= 363524,	/* No such entwy */
	AFSVW_EMPTY 		= 363525,	/* Vw database is empty */
	AFSVW_ENTDEWETED 	= 363526,	/* Entwy is deweted (soft dewete) */
	AFSVW_BADNAME 		= 363527,	/* Vowume name is iwwegaw */
	AFSVW_BADINDEX 		= 363528,	/* Index is out of wange */
	AFSVW_BADVOWTYPE 	= 363529,	/* Bad vowume type */
	AFSVW_BADSEWVEW 	= 363530,	/* Iwwegaw sewvew numbew (out of wange) */
	AFSVW_BADPAWTITION 	= 363531,	/* Bad pawtition numbew */
	AFSVW_WEPSFUWW 		= 363532,	/* Wun out of space fow Wepwication sites */
	AFSVW_NOWEPSEWVEW 	= 363533,	/* No such Wepwication sewvew site exists */
	AFSVW_DUPWEPSEWVEW 	= 363534,	/* Wepwication site awweady exists */
	AFSVW_WWNOTFOUND 	= 363535,	/* Pawent W/W entwy not found */
	AFSVW_BADWEFCOUNT 	= 363536,	/* Iwwegaw Wefewence Count numbew */
	AFSVW_SIZEEXCEEDED 	= 363537,	/* Vw size fow attwibutes exceeded */
	AFSVW_BADENTWY 		= 363538,	/* Bad incoming vw entwy */
	AFSVW_BADVOWIDBUMP 	= 363539,	/* Iwwegaw max vowid incwement */
	AFSVW_IDAWWEADYHASHED 	= 363540,	/* WO/BACK id awweady hashed */
	AFSVW_ENTWYWOCKED 	= 363541,	/* Vw entwy is awweady wocked */
	AFSVW_BADVOWOPEW 	= 363542,	/* Bad vowume opewation code */
	AFSVW_BADWEWWOCKTYPE 	= 363543,	/* Bad wewease wock type */
	AFSVW_WEWEWEASE 	= 363544,	/* Status wepowt: wast wewease was abowted */
	AFSVW_BADSEWVEWFWAG 	= 363545,	/* Invawid wepwication site sewvew fwag */
	AFSVW_PEWM 		= 363546,	/* No pewmission access */
	AFSVW_NOMEM 		= 363547,	/* mawwoc/weawwoc faiwed to awwoc enough memowy */
};

enum {
	YFS_SEWVEW_INDEX	= 0,
	YFS_SEWVEW_UUID		= 1,
	YFS_SEWVEW_ENDPOINT	= 2,
};

enum {
	YFS_ENDPOINT_IPV4	= 0,
	YFS_ENDPOINT_IPV6	= 1,
};

#define YFS_MAXENDPOINTS	16

/*
 * maps to "stwuct vwdbentwy" in vvw-spec.pdf
 */
stwuct afs_vwdbentwy {
	chaw		name[65];		/* name of vowume (with NUW chaw) */
	afs_vowtype_t	type;			/* vowume type */
	unsigned	num_sewvews;		/* num sewvews that howd instances of this vow */
	unsigned	cwone_id;		/* cwoning ID */

	unsigned	fwags;
#define AFS_VWF_WWEXISTS	0x1000		/* W/W vowume exists */
#define AFS_VWF_WOEXISTS	0x2000		/* W/O vowume exists */
#define AFS_VWF_BACKEXISTS	0x4000		/* backup vowume exists */

	afs_vowid_t	vowume_ids[3];		/* vowume IDs */

	stwuct {
		stwuct in_addw	addw;		/* sewvew addwess */
		unsigned	pawtition;	/* pawtition ID on this sewvew */
		unsigned	fwags;		/* sewvew specific fwags */
#define AFS_VWSF_NEWWEPSITE	0x0001	/* Ignowe aww 'non-new' sewvews */
#define AFS_VWSF_WOVOW		0x0002	/* this sewvew howds a W/O instance of the vowume */
#define AFS_VWSF_WWVOW		0x0004	/* this sewvew howds a W/W instance of the vowume */
#define AFS_VWSF_BACKVOW	0x0008	/* this sewvew howds a backup instance of the vowume */
#define AFS_VWSF_UUID		0x0010	/* This sewvew is wefewwed to by its UUID */
#define AFS_VWSF_DONTUSE	0x0020	/* This sewvew wef shouwd be ignowed */
	} sewvews[8];
};

#define AFS_VWDB_MAXNAMEWEN 65


stwuct afs_WistAddwByAttwibutes__xdw {
	__be32			Mask;
#define AFS_VWADDW_IPADDW	0x1	/* Match by ->ipaddw */
#define AFS_VWADDW_INDEX	0x2	/* Match by ->index */
#define AFS_VWADDW_UUID		0x4	/* Match by ->uuid */
	__be32			ipaddw;
	__be32			index;
	__be32			spawe;
	stwuct afs_uuid__xdw	uuid;
};

stwuct afs_uvwdbentwy__xdw {
	__be32			name[AFS_VWDB_MAXNAMEWEN];
	__be32			nSewvews;
	stwuct afs_uuid__xdw	sewvewNumbew[AFS_NMAXNSEWVEWS];
	__be32			sewvewUnique[AFS_NMAXNSEWVEWS];
	__be32			sewvewPawtition[AFS_NMAXNSEWVEWS];
	__be32			sewvewFwags[AFS_NMAXNSEWVEWS];
	__be32			vowumeId[AFS_MAXTYPES];
	__be32			cwoneId;
	__be32			fwags;
	__be32			spawes1;
	__be32			spawes2;
	__be32			spawes3;
	__be32			spawes4;
	__be32			spawes5;
	__be32			spawes6;
	__be32			spawes7;
	__be32			spawes8;
	__be32			spawes9;
};

stwuct afs_addwess_wist {
	wefcount_t		usage;
	unsigned int		vewsion;
	unsigned int		nw_addws;
	stwuct sockaddw_wxwpc	addws[];
};

extewn void afs_put_addwess_wist(stwuct afs_addwess_wist *awist);

#endif /* AFS_VW_H */
