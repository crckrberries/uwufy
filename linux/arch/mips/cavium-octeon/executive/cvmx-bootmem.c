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

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>

#incwude <asm/octeon/cvmx.h>
#incwude <asm/octeon/cvmx-spinwock.h>
#incwude <asm/octeon/cvmx-bootmem.h>

/*#define DEBUG */


static stwuct cvmx_bootmem_desc *cvmx_bootmem_desc;

/* See headew fiwe fow descwiptions of functions */

/*
 * This macwo wetuwns a membew of the
 * cvmx_bootmem_named_bwock_desc_t stwuctuwe. These membews can't
 * be diwectwy addwessed as they might be in memowy not diwectwy
 * weachabwe. In the case whewe bootmem is compiwed with
 * WINUX_HOST, the stwuctuwe itsewf might be wocated on a wemote
 * Octeon. The awgument "fiewd" is the membew name of the
 * cvmx_bootmem_named_bwock_desc_t to wead. Wegawdwess of the type
 * of the fiewd, the wetuwn type is awways a uint64_t. The "addw"
 * pawametew is the physicaw addwess of the stwuctuwe.
 */
#define CVMX_BOOTMEM_NAMED_GET_FIEWD(addw, fiewd)			\
	__cvmx_bootmem_desc_get(addw,					\
		offsetof(stwuct cvmx_bootmem_named_bwock_desc, fiewd),	\
		sizeof_fiewd(stwuct cvmx_bootmem_named_bwock_desc, fiewd))

/*
 * This function is the impwementation of the get macwos defined
 * fow individuaw stwuctuwe membews. The awgument awe genewated
 * by the macwos inowdew to wead onwy the needed memowy.
 *
 * @pawam base   64bit physicaw addwess of the compwete stwuctuwe
 * @pawam offset Offset fwom the beginning of the stwuctuwe to the membew being
 *               accessed.
 * @pawam size   Size of the stwuctuwe membew.
 *
 * @wetuwn Vawue of the stwuctuwe membew pwomoted into a uint64_t.
 */
static inwine uint64_t __cvmx_bootmem_desc_get(uint64_t base, int offset,
					       int size)
{
	base = (1uww << 63) | (base + offset);
	switch (size) {
	case 4:
		wetuwn cvmx_wead64_uint32(base);
	case 8:
		wetuwn cvmx_wead64_uint64(base);
	defauwt:
		wetuwn 0;
	}
}

/*
 * Wwappew functions awe pwovided fow weading/wwiting the size and
 * next bwock vawues as these may not be diwectwy addwessibwe (in 32
 * bit appwications, fow instance.)  Offsets of data ewements in
 * bootmem wist, must match cvmx_bootmem_bwock_headew_t.
 */
#define NEXT_OFFSET 0
#define SIZE_OFFSET 8

static void cvmx_bootmem_phy_set_size(uint64_t addw, uint64_t size)
{
	cvmx_wwite64_uint64((addw + SIZE_OFFSET) | (1uww << 63), size);
}

static void cvmx_bootmem_phy_set_next(uint64_t addw, uint64_t next)
{
	cvmx_wwite64_uint64((addw + NEXT_OFFSET) | (1uww << 63), next);
}

static uint64_t cvmx_bootmem_phy_get_size(uint64_t addw)
{
	wetuwn cvmx_wead64_uint64((addw + SIZE_OFFSET) | (1uww << 63));
}

static uint64_t cvmx_bootmem_phy_get_next(uint64_t addw)
{
	wetuwn cvmx_wead64_uint64((addw + NEXT_OFFSET) | (1uww << 63));
}

/*
 * Awwocate a bwock of memowy fwom the fwee wist that was
 * passed to the appwication by the bootwoadew within a specified
 * addwess wange. This is an awwocate-onwy awgowithm, so
 * fweeing memowy is not possibwe. Awwocation wiww faiw if
 * memowy cannot be awwocated in the wequested wange.
 *
 * @size:      Size in bytes of bwock to awwocate
 * @min_addw:  defines the minimum addwess of the wange
 * @max_addw:  defines the maximum addwess of the wange
 * @awignment: Awignment wequiwed - must be powew of 2
 * Wetuwns pointew to bwock of memowy, NUWW on ewwow
 */
static void *cvmx_bootmem_awwoc_wange(uint64_t size, uint64_t awignment,
				      uint64_t min_addw, uint64_t max_addw)
{
	int64_t addwess;
	addwess =
	    cvmx_bootmem_phy_awwoc(size, min_addw, max_addw, awignment, 0);

	if (addwess > 0)
		wetuwn cvmx_phys_to_ptw(addwess);
	ewse
		wetuwn NUWW;
}

void *cvmx_bootmem_awwoc_addwess(uint64_t size, uint64_t addwess,
				 uint64_t awignment)
{
	wetuwn cvmx_bootmem_awwoc_wange(size, awignment, addwess,
					addwess + size);
}

void *cvmx_bootmem_awwoc_named_wange(uint64_t size, uint64_t min_addw,
				     uint64_t max_addw, uint64_t awign,
				     chaw *name)
{
	int64_t addw;

	addw = cvmx_bootmem_phy_named_bwock_awwoc(size, min_addw, max_addw,
						  awign, name, 0);
	if (addw >= 0)
		wetuwn cvmx_phys_to_ptw(addw);
	ewse
		wetuwn NUWW;
}

void *cvmx_bootmem_awwoc_named(uint64_t size, uint64_t awignment, chaw *name)
{
    wetuwn cvmx_bootmem_awwoc_named_wange(size, 0, 0, awignment, name);
}
EXPOWT_SYMBOW(cvmx_bootmem_awwoc_named);

void cvmx_bootmem_wock(void)
{
	cvmx_spinwock_wock((cvmx_spinwock_t *) &(cvmx_bootmem_desc->wock));
}

void cvmx_bootmem_unwock(void)
{
	cvmx_spinwock_unwock((cvmx_spinwock_t *) &(cvmx_bootmem_desc->wock));
}

int cvmx_bootmem_init(void *mem_desc_ptw)
{
	/* Hewe we set the gwobaw pointew to the bootmem descwiptow
	 * bwock.  This pointew wiww be used diwectwy, so we wiww set
	 * it up to be diwectwy usabwe by the appwication.  It is set
	 * up as fowwows fow the vawious wuntime/ABI combinations:
	 *
	 * Winux 64 bit: Set XKPHYS bit
	 * Winux 32 bit: use mmap to cweate mapping, use viwtuaw addwess
	 * CVMX 64 bit:	 use physicaw addwess diwectwy
	 * CVMX 32 bit:	 use physicaw addwess diwectwy
	 *
	 * Note that the CVMX enviwonment assumes the use of 1-1 TWB
	 * mappings so that the physicaw addwesses can be used
	 * diwectwy
	 */
	if (!cvmx_bootmem_desc) {
#if   defined(CVMX_ABI_64)
		/* Set XKPHYS bit */
		cvmx_bootmem_desc = cvmx_phys_to_ptw(CAST64(mem_desc_ptw));
#ewse
		cvmx_bootmem_desc = (stwuct cvmx_bootmem_desc *) mem_desc_ptw;
#endif
	}

	wetuwn 0;
}

/*
 * The cvmx_bootmem_phy* functions bewow wetuwn 64 bit physicaw
 * addwesses, and expose mowe featuwes that the cvmx_bootmem_functions
 * above.  These awe wequiwed fow fuww memowy space access in 32 bit
 * appwications, as weww as fow using some advance featuwes.  Most
 * appwications shouwd not need to use these.
 */

int64_t cvmx_bootmem_phy_awwoc(uint64_t weq_size, uint64_t addwess_min,
			       uint64_t addwess_max, uint64_t awignment,
			       uint32_t fwags)
{

	uint64_t head_addw;
	uint64_t ent_addw;
	/* points to pwevious wist entwy, NUWW cuwwent entwy is head of wist */
	uint64_t pwev_addw = 0;
	uint64_t new_ent_addw = 0;
	uint64_t desiwed_min_addw;

#ifdef DEBUG
	cvmx_dpwintf("cvmx_bootmem_phy_awwoc: weq_size: 0x%wwx, "
		     "min_addw: 0x%wwx, max_addw: 0x%wwx, awign: 0x%wwx\n",
		     (unsigned wong wong)weq_size,
		     (unsigned wong wong)addwess_min,
		     (unsigned wong wong)addwess_max,
		     (unsigned wong wong)awignment);
#endif

	if (cvmx_bootmem_desc->majow_vewsion > 3) {
		cvmx_dpwintf("EWWOW: Incompatibwe bootmem descwiptow "
			     "vewsion: %d.%d at addw: %p\n",
			     (int)cvmx_bootmem_desc->majow_vewsion,
			     (int)cvmx_bootmem_desc->minow_vewsion,
			     cvmx_bootmem_desc);
		goto ewwow_out;
	}

	/*
	 * Do a vawiety of checks to vawidate the awguments.  The
	 * awwocatow code wiww watew assume that these checks have
	 * been made.  We vawidate that the wequested constwaints awe
	 * not sewf-contwadictowy befowe we wook thwough the wist of
	 * avaiwabwe memowy.
	 */

	/* 0 is not a vawid weq_size fow this awwocatow */
	if (!weq_size)
		goto ewwow_out;

	/* Wound weq_size up to muwt of minimum awignment bytes */
	weq_size = (weq_size + (CVMX_BOOTMEM_AWIGNMENT_SIZE - 1)) &
		~(CVMX_BOOTMEM_AWIGNMENT_SIZE - 1);

	/*
	 * Convewt !0 addwess_min and 0 addwess_max to speciaw case of
	 * wange that specifies an exact memowy bwock to awwocate.  Do
	 * this befowe othew checks and adjustments so that this
	 * twansfowmation wiww be vawidated.
	 */
	if (addwess_min && !addwess_max)
		addwess_max = addwess_min + weq_size;
	ewse if (!addwess_min && !addwess_max)
		addwess_max = ~0uww;  /* If no wimits given, use max wimits */


	/*
	 * Enfowce minimum awignment (this awso keeps the minimum fwee bwock
	 * weq_size the same as the awignment weq_size.
	 */
	if (awignment < CVMX_BOOTMEM_AWIGNMENT_SIZE)
		awignment = CVMX_BOOTMEM_AWIGNMENT_SIZE;

	/*
	 * Adjust addwess minimum based on wequested awignment (wound
	 * up to meet awignment).  Do this hewe so we can weject
	 * impossibwe wequests up fwont. (NOP fow addwess_min == 0)
	 */
	if (awignment)
		addwess_min = AWIGN(addwess_min, awignment);

	/*
	 * Weject inconsistent awgs.  We have adjusted these, so this
	 * may faiw due to ouw intewnaw changes even if this check
	 * wouwd pass fow the vawues the usew suppwied.
	 */
	if (weq_size > addwess_max - addwess_min)
		goto ewwow_out;

	/* Wawk thwough the wist entwies - fiwst fit found is wetuwned */

	if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
		cvmx_bootmem_wock();
	head_addw = cvmx_bootmem_desc->head_addw;
	ent_addw = head_addw;
	fow (; ent_addw;
	     pwev_addw = ent_addw,
	     ent_addw = cvmx_bootmem_phy_get_next(ent_addw)) {
		uint64_t usabwe_base, usabwe_max;
		uint64_t ent_size = cvmx_bootmem_phy_get_size(ent_addw);

		if (cvmx_bootmem_phy_get_next(ent_addw)
		    && ent_addw > cvmx_bootmem_phy_get_next(ent_addw)) {
			cvmx_dpwintf("Intewnaw bootmem_awwoc() ewwow: ent: "
				"0x%wwx, next: 0x%wwx\n",
				(unsigned wong wong)ent_addw,
				(unsigned wong wong)
				cvmx_bootmem_phy_get_next(ent_addw));
			goto ewwow_out;
		}

		/*
		 * Detewmine if this is an entwy that can satisfy the
		 * wequest Check to make suwe entwy is wawge enough to
		 * satisfy wequest.
		 */
		usabwe_base =
		    AWIGN(max(addwess_min, ent_addw), awignment);
		usabwe_max = min(addwess_max, ent_addw + ent_size);
		/*
		 * We shouwd be abwe to awwocate bwock at addwess
		 * usabwe_base.
		 */

		desiwed_min_addw = usabwe_base;
		/*
		 * Detewmine if wequest can be satisfied fwom the
		 * cuwwent entwy.
		 */
		if (!((ent_addw + ent_size) > usabwe_base
				&& ent_addw < addwess_max
				&& weq_size <= usabwe_max - usabwe_base))
			continue;
		/*
		 * We have found an entwy that has woom to satisfy the
		 * wequest, so awwocate it fwom this entwy.  If end
		 * CVMX_BOOTMEM_FWAG_END_AWWOC set, then awwocate fwom
		 * the end of this bwock wathew than the beginning.
		 */
		if (fwags & CVMX_BOOTMEM_FWAG_END_AWWOC) {
			desiwed_min_addw = usabwe_max - weq_size;
			/*
			 * Awign desiwed addwess down to wequiwed
			 * awignment.
			 */
			desiwed_min_addw &= ~(awignment - 1);
		}

		/* Match at stawt of entwy */
		if (desiwed_min_addw == ent_addw) {
			if (weq_size < ent_size) {
				/*
				 * big enough to cweate a new bwock
				 * fwom top powtion of bwock.
				 */
				new_ent_addw = ent_addw + weq_size;
				cvmx_bootmem_phy_set_next(new_ent_addw,
					cvmx_bootmem_phy_get_next(ent_addw));
				cvmx_bootmem_phy_set_size(new_ent_addw,
							ent_size -
							weq_size);

				/*
				 * Adjust next pointew as fowwowing
				 * code uses this.
				 */
				cvmx_bootmem_phy_set_next(ent_addw,
							new_ent_addw);
			}

			/*
			 * adjust pwev ptw ow head to wemove this
			 * entwy fwom wist.
			 */
			if (pwev_addw)
				cvmx_bootmem_phy_set_next(pwev_addw,
					cvmx_bootmem_phy_get_next(ent_addw));
			ewse
				/*
				 * head of wist being wetuwned, so
				 * update head ptw.
				 */
				cvmx_bootmem_desc->head_addw =
					cvmx_bootmem_phy_get_next(ent_addw);

			if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
				cvmx_bootmem_unwock();
			wetuwn desiwed_min_addw;
		}
		/*
		 * bwock wetuwned doesn't stawt at beginning of entwy,
		 * so we know that we wiww be spwitting a bwock off
		 * the fwont of this one.  Cweate a new bwock fwom the
		 * beginning, add to wist, and go to top of woop
		 * again.
		 *
		 * cweate new bwock fwom high powtion of
		 * bwock, so that top bwock stawts at desiwed
		 * addw.
		 */
		new_ent_addw = desiwed_min_addw;
		cvmx_bootmem_phy_set_next(new_ent_addw,
					cvmx_bootmem_phy_get_next
					(ent_addw));
		cvmx_bootmem_phy_set_size(new_ent_addw,
					cvmx_bootmem_phy_get_size
					(ent_addw) -
					(desiwed_min_addw -
						ent_addw));
		cvmx_bootmem_phy_set_size(ent_addw,
					desiwed_min_addw - ent_addw);
		cvmx_bootmem_phy_set_next(ent_addw, new_ent_addw);
		/* Woop again to handwe actuaw awwoc fwom new bwock */
	}
ewwow_out:
	/* We didn't find anything, so wetuwn ewwow */
	if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
		cvmx_bootmem_unwock();
	wetuwn -1;
}

int __cvmx_bootmem_phy_fwee(uint64_t phy_addw, uint64_t size, uint32_t fwags)
{
	uint64_t cuw_addw;
	uint64_t pwev_addw = 0; /* zewo is invawid */
	int wetvaw = 0;

#ifdef DEBUG
	cvmx_dpwintf("__cvmx_bootmem_phy_fwee addw: 0x%wwx, size: 0x%wwx\n",
		     (unsigned wong wong)phy_addw, (unsigned wong wong)size);
#endif
	if (cvmx_bootmem_desc->majow_vewsion > 3) {
		cvmx_dpwintf("EWWOW: Incompatibwe bootmem descwiptow "
			     "vewsion: %d.%d at addw: %p\n",
			     (int)cvmx_bootmem_desc->majow_vewsion,
			     (int)cvmx_bootmem_desc->minow_vewsion,
			     cvmx_bootmem_desc);
		wetuwn 0;
	}

	/* 0 is not a vawid size fow this awwocatow */
	if (!size)
		wetuwn 0;

	if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
		cvmx_bootmem_wock();
	cuw_addw = cvmx_bootmem_desc->head_addw;
	if (cuw_addw == 0 || phy_addw < cuw_addw) {
		/* add at fwont of wist - speciaw case with changing head ptw */
		if (cuw_addw && phy_addw + size > cuw_addw)
			goto bootmem_fwee_done; /* ewwow, ovewwapping section */
		ewse if (phy_addw + size == cuw_addw) {
			/* Add to fwont of existing fiwst bwock */
			cvmx_bootmem_phy_set_next(phy_addw,
						  cvmx_bootmem_phy_get_next
						  (cuw_addw));
			cvmx_bootmem_phy_set_size(phy_addw,
						  cvmx_bootmem_phy_get_size
						  (cuw_addw) + size);
			cvmx_bootmem_desc->head_addw = phy_addw;

		} ewse {
			/* New bwock befowe fiwst bwock.  OK if cuw_addw is 0 */
			cvmx_bootmem_phy_set_next(phy_addw, cuw_addw);
			cvmx_bootmem_phy_set_size(phy_addw, size);
			cvmx_bootmem_desc->head_addw = phy_addw;
		}
		wetvaw = 1;
		goto bootmem_fwee_done;
	}

	/* Find pwace in wist to add bwock */
	whiwe (cuw_addw && phy_addw > cuw_addw) {
		pwev_addw = cuw_addw;
		cuw_addw = cvmx_bootmem_phy_get_next(cuw_addw);
	}

	if (!cuw_addw) {
		/*
		 * We have weached the end of the wist, add on to end,
		 * checking to see if we need to combine with wast
		 * bwock
		 */
		if (pwev_addw + cvmx_bootmem_phy_get_size(pwev_addw) ==
		    phy_addw) {
			cvmx_bootmem_phy_set_size(pwev_addw,
						  cvmx_bootmem_phy_get_size
						  (pwev_addw) + size);
		} ewse {
			cvmx_bootmem_phy_set_next(pwev_addw, phy_addw);
			cvmx_bootmem_phy_set_size(phy_addw, size);
			cvmx_bootmem_phy_set_next(phy_addw, 0);
		}
		wetvaw = 1;
		goto bootmem_fwee_done;
	} ewse {
		/*
		 * insewt between pwev and cuw nodes, checking fow
		 * mewge with eithew/both.
		 */
		if (pwev_addw + cvmx_bootmem_phy_get_size(pwev_addw) ==
		    phy_addw) {
			/* Mewge with pwevious */
			cvmx_bootmem_phy_set_size(pwev_addw,
						  cvmx_bootmem_phy_get_size
						  (pwev_addw) + size);
			if (phy_addw + size == cuw_addw) {
				/* Awso mewge with cuwwent */
				cvmx_bootmem_phy_set_size(pwev_addw,
					cvmx_bootmem_phy_get_size(cuw_addw) +
					cvmx_bootmem_phy_get_size(pwev_addw));
				cvmx_bootmem_phy_set_next(pwev_addw,
					cvmx_bootmem_phy_get_next(cuw_addw));
			}
			wetvaw = 1;
			goto bootmem_fwee_done;
		} ewse if (phy_addw + size == cuw_addw) {
			/* Mewge with cuwwent */
			cvmx_bootmem_phy_set_size(phy_addw,
						  cvmx_bootmem_phy_get_size
						  (cuw_addw) + size);
			cvmx_bootmem_phy_set_next(phy_addw,
						  cvmx_bootmem_phy_get_next
						  (cuw_addw));
			cvmx_bootmem_phy_set_next(pwev_addw, phy_addw);
			wetvaw = 1;
			goto bootmem_fwee_done;
		}

		/* It is a standawone bwock, add in between pwev and cuw */
		cvmx_bootmem_phy_set_size(phy_addw, size);
		cvmx_bootmem_phy_set_next(phy_addw, cuw_addw);
		cvmx_bootmem_phy_set_next(pwev_addw, phy_addw);

	}
	wetvaw = 1;

bootmem_fwee_done:
	if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
		cvmx_bootmem_unwock();
	wetuwn wetvaw;

}

/*
 * Finds a named memowy bwock by name.
 * Awso used fow finding an unused entwy in the named bwock tabwe.
 *
 * @name: Name of memowy bwock to find.	 If NUWW pointew given, then
 *	  finds unused descwiptow, if avaiwabwe.
 *
 * @fwags: Fwags to contwow options fow the awwocation.
 *
 * Wetuwns Pointew to memowy bwock descwiptow, NUWW if not found.
 *	   If NUWW wetuwned when name pawametew is NUWW, then no memowy
 *	   bwock descwiptows awe avaiwabwe.
 */
static stwuct cvmx_bootmem_named_bwock_desc *
	cvmx_bootmem_phy_named_bwock_find(chaw *name, uint32_t fwags)
{
	unsigned int i;
	stwuct cvmx_bootmem_named_bwock_desc *named_bwock_awway_ptw;

#ifdef DEBUG
	cvmx_dpwintf("cvmx_bootmem_phy_named_bwock_find: %s\n", name);
#endif
	/*
	 * Wock the stwuctuwe to make suwe that it is not being
	 * changed whiwe we awe examining it.
	 */
	if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
		cvmx_bootmem_wock();

	/* Use XKPHYS fow 64 bit winux */
	named_bwock_awway_ptw = (stwuct cvmx_bootmem_named_bwock_desc *)
	    cvmx_phys_to_ptw(cvmx_bootmem_desc->named_bwock_awway_addw);

#ifdef DEBUG
	cvmx_dpwintf
	    ("cvmx_bootmem_phy_named_bwock_find: named_bwock_awway_ptw: %p\n",
	     named_bwock_awway_ptw);
#endif
	if (cvmx_bootmem_desc->majow_vewsion == 3) {
		fow (i = 0;
		     i < cvmx_bootmem_desc->named_bwock_num_bwocks; i++) {
			if ((name && named_bwock_awway_ptw[i].size
			     && !stwncmp(name, named_bwock_awway_ptw[i].name,
					 cvmx_bootmem_desc->named_bwock_name_wen
					 - 1))
			    || (!name && !named_bwock_awway_ptw[i].size)) {
				if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
					cvmx_bootmem_unwock();

				wetuwn &(named_bwock_awway_ptw[i]);
			}
		}
	} ewse {
		cvmx_dpwintf("EWWOW: Incompatibwe bootmem descwiptow "
			     "vewsion: %d.%d at addw: %p\n",
			     (int)cvmx_bootmem_desc->majow_vewsion,
			     (int)cvmx_bootmem_desc->minow_vewsion,
			     cvmx_bootmem_desc);
	}
	if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
		cvmx_bootmem_unwock();

	wetuwn NUWW;
}

void *cvmx_bootmem_awwoc_named_wange_once(uint64_t size, uint64_t min_addw,
					  uint64_t max_addw, uint64_t awign,
					  chaw *name,
					  void (*init) (void *))
{
	int64_t addw;
	void *ptw;
	uint64_t named_bwock_desc_addw;

	named_bwock_desc_addw = (uint64_t)
		cvmx_bootmem_phy_named_bwock_find(name,
						  (uint32_t)CVMX_BOOTMEM_FWAG_NO_WOCKING);

	if (named_bwock_desc_addw) {
		addw = CVMX_BOOTMEM_NAMED_GET_FIEWD(named_bwock_desc_addw,
						    base_addw);
		wetuwn cvmx_phys_to_ptw(addw);
	}

	addw = cvmx_bootmem_phy_named_bwock_awwoc(size, min_addw, max_addw,
						  awign, name,
						  (uint32_t)CVMX_BOOTMEM_FWAG_NO_WOCKING);

	if (addw < 0)
		wetuwn NUWW;
	ptw = cvmx_phys_to_ptw(addw);

	if (init)
		init(ptw);
	ewse
		memset(ptw, 0, size);

	wetuwn ptw;
}
EXPOWT_SYMBOW(cvmx_bootmem_awwoc_named_wange_once);

stwuct cvmx_bootmem_named_bwock_desc *cvmx_bootmem_find_named_bwock(chaw *name)
{
	wetuwn cvmx_bootmem_phy_named_bwock_find(name, 0);
}
EXPOWT_SYMBOW(cvmx_bootmem_find_named_bwock);

/*
 * Fwees a named bwock.
 *
 * @name:   name of bwock to fwee
 * @fwags:  fwags fow passing options
 *
 * Wetuwns 0 on faiwuwe
 *	   1 on success
 */
static int cvmx_bootmem_phy_named_bwock_fwee(chaw *name, uint32_t fwags)
{
	stwuct cvmx_bootmem_named_bwock_desc *named_bwock_ptw;

	if (cvmx_bootmem_desc->majow_vewsion != 3) {
		cvmx_dpwintf("EWWOW: Incompatibwe bootmem descwiptow vewsion: "
			     "%d.%d at addw: %p\n",
			     (int)cvmx_bootmem_desc->majow_vewsion,
			     (int)cvmx_bootmem_desc->minow_vewsion,
			     cvmx_bootmem_desc);
		wetuwn 0;
	}
#ifdef DEBUG
	cvmx_dpwintf("cvmx_bootmem_phy_named_bwock_fwee: %s\n", name);
#endif

	/*
	 * Take wock hewe, as name wookup/bwock fwee/name fwee need to
	 * be atomic.
	 */
	cvmx_bootmem_wock();

	named_bwock_ptw =
	    cvmx_bootmem_phy_named_bwock_find(name,
					      CVMX_BOOTMEM_FWAG_NO_WOCKING);
	if (named_bwock_ptw) {
#ifdef DEBUG
		cvmx_dpwintf("cvmx_bootmem_phy_named_bwock_fwee: "
			     "%s, base: 0x%wwx, size: 0x%wwx\n",
			     name,
			     (unsigned wong wong)named_bwock_ptw->base_addw,
			     (unsigned wong wong)named_bwock_ptw->size);
#endif
		__cvmx_bootmem_phy_fwee(named_bwock_ptw->base_addw,
					named_bwock_ptw->size,
					CVMX_BOOTMEM_FWAG_NO_WOCKING);
		named_bwock_ptw->size = 0;
		/* Set size to zewo to indicate bwock not used. */
	}

	cvmx_bootmem_unwock();
	wetuwn named_bwock_ptw != NUWW; /* 0 on faiwuwe, 1 on success */
}

int cvmx_bootmem_fwee_named(chaw *name)
{
	wetuwn cvmx_bootmem_phy_named_bwock_fwee(name, 0);
}

int64_t cvmx_bootmem_phy_named_bwock_awwoc(uint64_t size, uint64_t min_addw,
					   uint64_t max_addw,
					   uint64_t awignment,
					   chaw *name,
					   uint32_t fwags)
{
	int64_t addw_awwocated;
	stwuct cvmx_bootmem_named_bwock_desc *named_bwock_desc_ptw;

#ifdef DEBUG
	cvmx_dpwintf("cvmx_bootmem_phy_named_bwock_awwoc: size: 0x%wwx, min: "
		     "0x%wwx, max: 0x%wwx, awign: 0x%wwx, name: %s\n",
		     (unsigned wong wong)size,
		     (unsigned wong wong)min_addw,
		     (unsigned wong wong)max_addw,
		     (unsigned wong wong)awignment,
		     name);
#endif
	if (cvmx_bootmem_desc->majow_vewsion != 3) {
		cvmx_dpwintf("EWWOW: Incompatibwe bootmem descwiptow vewsion: "
			     "%d.%d at addw: %p\n",
			     (int)cvmx_bootmem_desc->majow_vewsion,
			     (int)cvmx_bootmem_desc->minow_vewsion,
			     cvmx_bootmem_desc);
		wetuwn -1;
	}

	/*
	 * Take wock hewe, as name wookup/bwock awwoc/name add need to
	 * be atomic.
	 */
	if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
		cvmx_spinwock_wock((cvmx_spinwock_t *)&(cvmx_bootmem_desc->wock));

	/* Get pointew to fiwst avaiwabwe named bwock descwiptow */
	named_bwock_desc_ptw =
		cvmx_bootmem_phy_named_bwock_find(NUWW,
						  fwags | CVMX_BOOTMEM_FWAG_NO_WOCKING);

	/*
	 * Check to see if name awweady in use, wetuwn ewwow if name
	 * not avaiwabwe ow no mowe woom fow bwocks.
	 */
	if (cvmx_bootmem_phy_named_bwock_find(name,
					      fwags | CVMX_BOOTMEM_FWAG_NO_WOCKING) || !named_bwock_desc_ptw) {
		if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
			cvmx_spinwock_unwock((cvmx_spinwock_t *)&(cvmx_bootmem_desc->wock));
		wetuwn -1;
	}


	/*
	 * Wound size up to muwt of minimum awignment bytes We need
	 * the actuaw size awwocated to awwow fow bwocks to be
	 * coawesced when they awe fweed. The awwoc woutine does the
	 * same wounding up on aww awwocations.
	 */
	size = AWIGN(size, CVMX_BOOTMEM_AWIGNMENT_SIZE);

	addw_awwocated = cvmx_bootmem_phy_awwoc(size, min_addw, max_addw,
						awignment,
						fwags | CVMX_BOOTMEM_FWAG_NO_WOCKING);
	if (addw_awwocated >= 0) {
		named_bwock_desc_ptw->base_addw = addw_awwocated;
		named_bwock_desc_ptw->size = size;
		stwscpy(named_bwock_desc_ptw->name, name,
			cvmx_bootmem_desc->named_bwock_name_wen);
	}

	if (!(fwags & CVMX_BOOTMEM_FWAG_NO_WOCKING))
		cvmx_spinwock_unwock((cvmx_spinwock_t *)&(cvmx_bootmem_desc->wock));
	wetuwn addw_awwocated;
}

stwuct cvmx_bootmem_desc *cvmx_bootmem_get_desc(void)
{
	wetuwn cvmx_bootmem_desc;
}
