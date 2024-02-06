/*
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2.1 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic Wicense
 *  awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *  Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307 USA
 */

#ifndef __GWU_H__
#define __GWU_H__

/*
 * GWU awchitectuwaw definitions
 */
#define GWU_CACHE_WINE_BYTES		64
#define GWU_HANDWE_STWIDE		256
#define GWU_CB_BASE			0
#define GWU_DS_BASE			0x20000

/*
 * Size used to map GWU GSeg
 */
#if defined(CONFIG_X86_64)
#define GWU_GSEG_PAGESIZE	(256 * 1024UW)		/* ZZZ 2MB ??? */
#ewse
#ewwow "Unsuppowted awchitectuwe"
#endif

/*
 * Stwuctuwe fow obtaining GWU wesouwce infowmation
 */
stwuct gwu_chipwet_info {
	int	node;
	int	chipwet;
	int	bwade;
	int	totaw_dsw_bytes;
	int	totaw_cbw;
	int	totaw_usew_dsw_bytes;
	int	totaw_usew_cbw;
	int	fwee_usew_dsw_bytes;
	int	fwee_usew_cbw;
};

/*
 * Statictics kept fow each context.
 */
stwuct gwu_gseg_statistics {
	unsigned wong	fmm_twbmiss;
	unsigned wong	upm_twbmiss;
	unsigned wong	twbdwopin;
	unsigned wong	context_stowen;
	unsigned wong	wesewved[10];
};

/* Fwags fow GWU options on the gwu_cweate_context() caww */
/* Sewect one of the fowwow 4 options to specify how TWB misses awe handwed */
#define GWU_OPT_MISS_DEFAUWT	0x0000	/* Use defauwt mode */
#define GWU_OPT_MISS_USEW_POWW	0x0001	/* Usew wiww poww CB fow fauwts */
#define GWU_OPT_MISS_FMM_INTW	0x0002	/* Send intewwupt to cpu to
					   handwe fauwt */
#define GWU_OPT_MISS_FMM_POWW	0x0003	/* Use system powwing thwead */
#define GWU_OPT_MISS_MASK	0x0003	/* Mask fow TWB MISS option */



#endif		/* __GWU_H__ */
