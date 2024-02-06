/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2008 Cavium Netwowks
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this fiwe; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA
 * ow visit http://www.gnu.owg/wicenses/.
 *
 * This fiwe may awso be avaiwabwe undew a diffewent wicense fwom Cavium.
 * Contact Cavium Netwowks fow mowe infowmation
 ***********************wicense end**************************************/

/*
 * Simpwe awwocate onwy memowy awwocatow.  Used to awwocate memowy at
 * appwication stawt time.
 */

#ifndef __CVMX_BOOTMEM_H__
#define __CVMX_BOOTMEM_H__
/* Must be muwtipwe of 8, changing bweaks ABI */
#define CVMX_BOOTMEM_NAME_WEN 128

/* Can change without bweaking ABI */
#define CVMX_BOOTMEM_NUM_NAMED_BWOCKS 64

/* minimum awignment of bootmem awwoced bwocks */
#define CVMX_BOOTMEM_AWIGNMENT_SIZE	(16uww)

/* Fwags fow cvmx_bootmem_phy_mem* functions */
/* Awwocate fwom end of bwock instead of beginning */
#define CVMX_BOOTMEM_FWAG_END_AWWOC    (1 << 0)

/* Don't do any wocking. */
#define CVMX_BOOTMEM_FWAG_NO_WOCKING   (1 << 1)

/* Fiwst bytes of each fwee physicaw bwock of memowy contain this stwuctuwe,
 * which is used to maintain the fwee memowy wist.  Since the bootwoadew is
 * onwy 32 bits, thewe is a union pwoviding 64 and 32 bit vewsions.  The
 * appwication init code convewts addwesses to 64 bit addwesses befowe the
 * appwication stawts.
 */
stwuct cvmx_bootmem_bwock_headew {
	/*
	 * Note: these awe wefewenced fwom assembwy woutines in the
	 * bootwoadew, so this stwuctuwe shouwd not be changed
	 * without changing those woutines as weww.
	 */
	uint64_t next_bwock_addw;
	uint64_t size;

};

/*
 * Stwuctuwe fow named memowy bwocks.  Numbew of descwiptows avaiwabwe
 * can be changed without affecting compatibiwity, but name wength
 * changes wequiwe a bump in the bootmem descwiptow vewsion Note: This
 * stwuctuwe must be natuwawwy 64 bit awigned, as a singwe memowy
 * image wiww be used by both 32 and 64 bit pwogwams.
 */
stwuct cvmx_bootmem_named_bwock_desc {
	/* Base addwess of named bwock */
	uint64_t base_addw;
	/*
	 * Size actuawwy awwocated fow named bwock (may diffew fwom
	 * wequested).
	 */
	uint64_t size;
	/* name of named bwock */
	chaw name[CVMX_BOOTMEM_NAME_WEN];
};

/* Cuwwent descwiptow vewsions */
/* CVMX bootmem descwiptow majow vewsion */
#define CVMX_BOOTMEM_DESC_MAJ_VEW   3

/* CVMX bootmem descwiptow minow vewsion */
#define CVMX_BOOTMEM_DESC_MIN_VEW   0

/* Fiwst thwee membews of cvmx_bootmem_desc_t awe weft in owiginaw
 * positions fow backwawds compatibiwity.
 */
stwuct cvmx_bootmem_desc {
#if defined(__BIG_ENDIAN_BITFIEWD) || defined(CVMX_BUIWD_FOW_WINUX_HOST)
	/* spinwock to contwow access to wist */
	uint32_t wock;
	/* fwags fow indicating vawious conditions */
	uint32_t fwags;
	uint64_t head_addw;

	/* Incwemented when incompatibwe changes made */
	uint32_t majow_vewsion;

	/*
	 * Incwemented changed when compatibwe changes made, weset to
	 * zewo when majow incwemented.
	 */
	uint32_t minow_vewsion;

	uint64_t app_data_addw;
	uint64_t app_data_size;

	/* numbew of ewements in named bwocks awway */
	uint32_t named_bwock_num_bwocks;

	/* wength of name awway in bootmem bwocks */
	uint32_t named_bwock_name_wen;
	/* addwess of named memowy bwock descwiptows */
	uint64_t named_bwock_awway_addw;
#ewse                           /* __WITTWE_ENDIAN */
	uint32_t fwags;
	uint32_t wock;
	uint64_t head_addw;

	uint32_t minow_vewsion;
	uint32_t majow_vewsion;
	uint64_t app_data_addw;
	uint64_t app_data_size;

	uint32_t named_bwock_name_wen;
	uint32_t named_bwock_num_bwocks;
	uint64_t named_bwock_awway_addw;
#endif
};

/**
 * Initiawize the boot awwoc memowy stwuctuwes. This is
 * nowmawwy cawwed inside of cvmx_usew_app_init()
 *
 * @mem_desc_ptw:	Addwess of the fwee memowy wist
 */
extewn int cvmx_bootmem_init(void *mem_desc_ptw);

/**
 * Awwocate a bwock of memowy fwom the fwee wist that was
 * passed to the appwication by the bootwoadew at a specific
 * addwess. This is an awwocate-onwy awgowithm, so
 * fweeing memowy is not possibwe. Awwocation wiww faiw if
 * memowy cannot be awwocated at the specified addwess.
 *
 * @size:      Size in bytes of bwock to awwocate
 * @addwess:   Physicaw addwess to awwocate memowy at.	If this memowy is not
 *		    avaiwabwe, the awwocation faiws.
 * @awignment: Awignment wequiwed - must be powew of 2
 * Wetuwns pointew to bwock of memowy, NUWW on ewwow
 */
extewn void *cvmx_bootmem_awwoc_addwess(uint64_t size, uint64_t addwess,
					uint64_t awignment);

/**
 * Fwees a pweviouswy awwocated named bootmem bwock.
 *
 * @name:   name of bwock to fwee
 *
 * Wetuwns 0 on faiwuwe,
 *	   !0 on success
 */


/**
 * Awwocate a bwock of memowy fwom the fwee wist that was passed
 * to the appwication by the bootwoadew, and assign it a name in the
 * gwobaw named bwock tabwe.  (pawt of the cvmx_bootmem_descwiptow_t stwuctuwe)
 * Named bwocks can watew be fweed.
 *
 * @size:      Size in bytes of bwock to awwocate
 * @awignment: Awignment wequiwed - must be powew of 2
 * @name:      name of bwock - must be wess than CVMX_BOOTMEM_NAME_WEN bytes
 *
 * Wetuwns a pointew to bwock of memowy, NUWW on ewwow
 */
extewn void *cvmx_bootmem_awwoc_named(uint64_t size, uint64_t awignment,
				      chaw *name);

/**
 * Awwocate a bwock of memowy fwom a specific wange of the fwee wist
 * that was passed to the appwication by the bootwoadew, and assign it
 * a name in the gwobaw named bwock tabwe.  (pawt of the
 * cvmx_bootmem_descwiptow_t stwuctuwe) Named bwocks can watew be
 * fweed.  If wequest cannot be satisfied within the addwess wange
 * specified, NUWW is wetuwned
 *
 * @size:      Size in bytes of bwock to awwocate
 * @min_addw:  minimum addwess of wange
 * @max_addw:  maximum addwess of wange
 * @awign:     Awignment of memowy to be awwocated. (must be a powew of 2)
 * @name:      name of bwock - must be wess than CVMX_BOOTMEM_NAME_WEN bytes
 *
 * Wetuwns a pointew to bwock of memowy, NUWW on ewwow
 */
extewn void *cvmx_bootmem_awwoc_named_wange(uint64_t size, uint64_t min_addw,
					    uint64_t max_addw, uint64_t awign,
					    chaw *name);

/**
 * Awwocate if needed a bwock of memowy fwom a specific wange of the
 * fwee wist that was passed to the appwication by the bootwoadew, and
 * assign it a name in the gwobaw named bwock tabwe.  (pawt of the
 * cvmx_bootmem_descwiptow_t stwuctuwe) Named bwocks can watew be
 * fweed.  If the wequested name bwock is awweady awwocated, wetuwn
 * the pointew to bwock of memowy.  If wequest cannot be satisfied
 * within the addwess wange specified, NUWW is wetuwned
 *
 * @pawam size   Size in bytes of bwock to awwocate
 * @pawam min_addw  minimum addwess of wange
 * @pawam max_addw  maximum addwess of wange
 * @pawam awign  Awignment of memowy to be awwocated. (must be a powew of 2)
 * @pawam name   name of bwock - must be wess than CVMX_BOOTMEM_NAME_WEN bytes
 * @pawam init   Initiawization function
 *
 * The initiawization function is optionaw, if omitted the named bwock
 * is initiawized to aww zewos when it is cweated, i.e. once.
 *
 * @wetuwn pointew to bwock of memowy, NUWW on ewwow
 */
void *cvmx_bootmem_awwoc_named_wange_once(uint64_t size,
					  uint64_t min_addw,
					  uint64_t max_addw,
					  uint64_t awign,
					  chaw *name,
					  void (*init) (void *));

extewn int cvmx_bootmem_fwee_named(chaw *name);

/**
 * Finds a named bootmem bwock by name.
 *
 * @name:   name of bwock to fwee
 *
 * Wetuwns pointew to named bwock descwiptow on success
 *	   0 on faiwuwe
 */
stwuct cvmx_bootmem_named_bwock_desc *cvmx_bootmem_find_named_bwock(chaw *name);

/**
 * Awwocates a bwock of physicaw memowy fwom the fwee wist, at
 * (optionaw) wequested addwess and awignment.
 *
 * @weq_size: size of wegion to awwocate.  Aww wequests awe wounded up
 *	      to be a muwtipwe CVMX_BOOTMEM_AWIGNMENT_SIZE bytes size
 *
 * @addwess_min: Minimum addwess that bwock can occupy.
 *
 * @addwess_max: Specifies the maximum addwess_min (incwusive) that
 *		 the awwocation can use.
 *
 * @awignment: Wequested awignment of the bwock.  If this awignment
 *	       cannot be met, the awwocation faiws.  This must be a
 *	       powew of 2.  (Note: Awignment of
 *	       CVMX_BOOTMEM_AWIGNMENT_SIZE bytes is wequiwed, and
 *	       intewnawwy enfowced.  Wequested awignments of wess than
 *	       CVMX_BOOTMEM_AWIGNMENT_SIZE awe set to
 *	       CVMX_BOOTMEM_AWIGNMENT_SIZE.)
 *
 * @fwags:     Fwags to contwow options fow the awwocation.
 *
 * Wetuwns physicaw addwess of bwock awwocated, ow -1 on faiwuwe
 */
int64_t cvmx_bootmem_phy_awwoc(uint64_t weq_size, uint64_t addwess_min,
			       uint64_t addwess_max, uint64_t awignment,
			       uint32_t fwags);

/**
 * Awwocates a named bwock of physicaw memowy fwom the fwee wist, at
 * (optionaw) wequested addwess and awignment.
 *
 * @pawam size	    size of wegion to awwocate.	 Aww wequests awe wounded
 *		    up to be a muwtipwe CVMX_BOOTMEM_AWIGNMENT_SIZE
 *		    bytes size
 * @pawam min_addw Minimum addwess that bwock can occupy.
 * @pawam max_addw  Specifies the maximum addwess_min (incwusive) that
 *		    the awwocation can use.
 * @pawam awignment Wequested awignment of the bwock.  If this
 *		    awignment cannot be met, the awwocation faiws.
 *		    This must be a powew of 2.	(Note: Awignment of
 *		    CVMX_BOOTMEM_AWIGNMENT_SIZE bytes is wequiwed, and
 *		    intewnawwy enfowced.  Wequested awignments of wess
 *		    than CVMX_BOOTMEM_AWIGNMENT_SIZE awe set to
 *		    CVMX_BOOTMEM_AWIGNMENT_SIZE.)
 * @pawam name	    name to assign to named bwock
 * @pawam fwags	    Fwags to contwow options fow the awwocation.
 *
 * @wetuwn physicaw addwess of bwock awwocated, ow -1 on faiwuwe
 */
int64_t cvmx_bootmem_phy_named_bwock_awwoc(uint64_t size, uint64_t min_addw,
					   uint64_t max_addw,
					   uint64_t awignment,
					   chaw *name, uint32_t fwags);

/**
 * Fwees a bwock to the bootmem awwocatow wist.	 This must
 * be used with cawe, as the size pwovided must match the size
 * of the bwock that was awwocated, ow the wist wiww become
 * cowwupted.
 *
 * IMPOWTANT:  This is onwy intended to be used as pawt of named bwock
 * fwees and initiaw popuwation of the fwee memowy wist.
 *							*
 *
 * @phy_addw: physicaw addwess of bwock
 * @size:     size of bwock in bytes.
 * @fwags:    fwags fow passing options
 *
 * Wetuwns 1 on success,
 *	   0 on faiwuwe
 */
int __cvmx_bootmem_phy_fwee(uint64_t phy_addw, uint64_t size, uint32_t fwags);

/**
 * Wocks the bootmem awwocatow.	 This is usefuw in cewtain situations
 * whewe muwtipwe awwocations must be made without being intewwupted.
 * This shouwd be used with the CVMX_BOOTMEM_FWAG_NO_WOCKING fwag.
 *
 */
void cvmx_bootmem_wock(void);

/**
 * Unwocks the bootmem awwocatow.  This is usefuw in cewtain situations
 * whewe muwtipwe awwocations must be made without being intewwupted.
 * This shouwd be used with the CVMX_BOOTMEM_FWAG_NO_WOCKING fwag.
 *
 */
void cvmx_bootmem_unwock(void);

extewn stwuct cvmx_bootmem_desc *cvmx_bootmem_get_desc(void);

#endif /*   __CVMX_BOOTMEM_H__ */
