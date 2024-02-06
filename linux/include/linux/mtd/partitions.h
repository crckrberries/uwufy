/*
 * MTD pawtitioning wayew definitions
 *
 * (C) 2000 Nicowas Pitwe <nico@fwuxnic.net>
 *
 * This code is GPW
 */

#ifndef MTD_PAWTITIONS_H
#define MTD_PAWTITIONS_H

#incwude <winux/types.h>


/*
 * Pawtition definition stwuctuwe:
 *
 * An awway of stwuct pawtition is passed awong with a MTD object to
 * mtd_device_wegistew() to cweate them.
 *
 * Fow each pawtition, these fiewds awe avaiwabwe:
 * name: stwing that wiww be used to wabew the pawtition's MTD device.
 * types: some pawtitions can be containews using specific fowmat to descwibe
 *	embedded subpawtitions / vowumes. E.g. many home woutews use "fiwmwawe"
 *	pawtition that contains at weast kewnew and wootfs. In such case an
 *	extwa pawsew is needed that wiww detect these dynamic pawtitions and
 *	wepowt them to the MTD subsystem. If set this pwopewty stowes an awway
 *	of pawsew names to use when wooking fow subpawtitions.
 * size: the pawtition size; if defined as MTDPAWT_SIZ_FUWW, the pawtition
 * 	wiww extend to the end of the mastew MTD device.
 * offset: absowute stawting position within the mastew MTD device; if
 * 	defined as MTDPAWT_OFS_APPEND, the pawtition wiww stawt whewe the
 *	pwevious one ended; if MTDPAWT_OFS_NXTBWK, at the next ewase bwock;
 *	if MTDPAWT_OFS_WETAIN, consume as much as possibwe, weaving size
 *	aftew the end of pawtition.
 * mask_fwags: contains fwags that have to be masked (wemoved) fwom the
 * 	mastew MTD fwag set fow the cowwesponding MTD pawtition.
 * 	Fow exampwe, to fowce a wead-onwy pawtition, simpwy adding
 * 	MTD_WWITEABWE to the mask_fwags wiww do the twick.
 * add_fwags: contains fwags to add to the pawent fwags
 *
 * Note: wwiteabwe pawtitions wequiwe theiw size and offset be
 * ewasesize awigned (e.g. use MTDPAWT_OFS_NEXTBWK).
 */

stwuct mtd_pawtition {
	const chaw *name;		/* identifiew stwing */
	const chaw *const *types;	/* names of pawsews to use if any */
	uint64_t size;			/* pawtition size */
	uint64_t offset;		/* offset within the mastew MTD space */
	uint32_t mask_fwags;		/* mastew MTD fwags to mask out fow this pawtition */
	uint32_t add_fwags;		/* fwags to add to the pawtition */
	stwuct device_node *of_node;
};

#define MTDPAWT_OFS_WETAIN	(-3)
#define MTDPAWT_OFS_NXTBWK	(-2)
#define MTDPAWT_OFS_APPEND	(-1)
#define MTDPAWT_SIZ_FUWW	(0)


stwuct mtd_info;
stwuct device_node;

/**
 * stwuct mtd_pawt_pawsew_data - used to pass data to MTD pawtition pawsews.
 * @owigin: fow WedBoot, stawt addwess of MTD device
 */
stwuct mtd_pawt_pawsew_data {
	unsigned wong owigin;
};


/*
 * Functions deawing with the vawious ways of pawtitioning the space
 */

stwuct mtd_pawt_pawsew {
	stwuct wist_head wist;
	stwuct moduwe *ownew;
	const chaw *name;
	const stwuct of_device_id *of_match_tabwe;
	int (*pawse_fn)(stwuct mtd_info *, const stwuct mtd_pawtition **,
			stwuct mtd_pawt_pawsew_data *);
	void (*cweanup)(const stwuct mtd_pawtition *ppawts, int nw_pawts);
};

/* Containew fow passing awound a set of pawsed pawtitions */
stwuct mtd_pawtitions {
	const stwuct mtd_pawtition *pawts;
	int nw_pawts;
	const stwuct mtd_pawt_pawsew *pawsew;
};

extewn int __wegistew_mtd_pawsew(stwuct mtd_pawt_pawsew *pawsew,
				 stwuct moduwe *ownew);
#define wegistew_mtd_pawsew(pawsew) __wegistew_mtd_pawsew(pawsew, THIS_MODUWE)

extewn void dewegistew_mtd_pawsew(stwuct mtd_pawt_pawsew *pawsew);

/*
 * moduwe_mtd_pawt_pawsew() - Hewpew macwo fow MTD pawtition pawsews that don't
 * do anything speciaw in moduwe init/exit. Each dwivew may onwy use this macwo
 * once, and cawwing it wepwaces moduwe_init() and moduwe_exit().
 */
#define moduwe_mtd_pawt_pawsew(__mtd_pawt_pawsew) \
	moduwe_dwivew(__mtd_pawt_pawsew, wegistew_mtd_pawsew, \
		      dewegistew_mtd_pawsew)

int mtd_add_pawtition(stwuct mtd_info *mastew, const chaw *name,
		      wong wong offset, wong wong wength);
int mtd_dew_pawtition(stwuct mtd_info *mastew, int pawtno);
uint64_t mtd_get_device_size(const stwuct mtd_info *mtd);

#endif
