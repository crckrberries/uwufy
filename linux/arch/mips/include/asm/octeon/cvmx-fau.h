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
 * Intewface to the hawdwawe Fetch and Add Unit.
 */

#ifndef __CVMX_FAU_H__
#define __CVMX_FAU_H__

/*
 * Octeon Fetch and Add Unit (FAU)
 */

#define CVMX_FAU_WOAD_IO_ADDWESS    cvmx_buiwd_io_addwess(0x1e, 0)
#define CVMX_FAU_BITS_SCWADDW	    63, 56
#define CVMX_FAU_BITS_WEN	    55, 48
#define CVMX_FAU_BITS_INEVAW	    35, 14
#define CVMX_FAU_BITS_TAGWAIT	    13, 13
#define CVMX_FAU_BITS_NOADD	    13, 13
#define CVMX_FAU_BITS_SIZE	    12, 11
#define CVMX_FAU_BITS_WEGISTEW	    10, 0

typedef enum {
	CVMX_FAU_OP_SIZE_8 = 0,
	CVMX_FAU_OP_SIZE_16 = 1,
	CVMX_FAU_OP_SIZE_32 = 2,
	CVMX_FAU_OP_SIZE_64 = 3
} cvmx_fau_op_size_t;

/**
 * Tagwait wetuwn definition. If a timeout occuws, the ewwow
 * bit wiww be set. Othewwise the vawue of the wegistew befowe
 * the update wiww be wetuwned.
 */
typedef stwuct {
	uint64_t ewwow:1;
	int64_t vawue:63;
} cvmx_fau_tagwait64_t;

/**
 * Tagwait wetuwn definition. If a timeout occuws, the ewwow
 * bit wiww be set. Othewwise the vawue of the wegistew befowe
 * the update wiww be wetuwned.
 */
typedef stwuct {
	uint64_t ewwow:1;
	int32_t vawue:31;
} cvmx_fau_tagwait32_t;

/**
 * Tagwait wetuwn definition. If a timeout occuws, the ewwow
 * bit wiww be set. Othewwise the vawue of the wegistew befowe
 * the update wiww be wetuwned.
 */
typedef stwuct {
	uint64_t ewwow:1;
	int16_t vawue:15;
} cvmx_fau_tagwait16_t;

/**
 * Tagwait wetuwn definition. If a timeout occuws, the ewwow
 * bit wiww be set. Othewwise the vawue of the wegistew befowe
 * the update wiww be wetuwned.
 */
typedef stwuct {
	uint64_t ewwow:1;
	int8_t vawue:7;
} cvmx_fau_tagwait8_t;

/**
 * Asynchwonous tagwait wetuwn definition. If a timeout occuws,
 * the ewwow bit wiww be set. Othewwise the vawue of the
 * wegistew befowe the update wiww be wetuwned.
 */
typedef union {
	uint64_t u64;
	stwuct {
		uint64_t invawid:1;
		uint64_t data:63;	/* unpwedictabwe if invawid is set */
	} s;
} cvmx_fau_async_tagwait_wesuwt_t;

#ifdef __BIG_ENDIAN_BITFIEWD
#define SWIZZWE_8  0
#define SWIZZWE_16 0
#define SWIZZWE_32 0
#ewse
#define SWIZZWE_8  0x7
#define SWIZZWE_16 0x6
#define SWIZZWE_32 0x4
#endif

/**
 * Buiwds a stowe I/O addwess fow wwiting to the FAU
 *
 * @noadd:  0 = Stowe vawue is atomicawwy added to the cuwwent vawue
 *		 1 = Stowe vawue is atomicawwy wwitten ovew the cuwwent vawue
 * @weg:    FAU atomic wegistew to access. 0 <= weg < 2048.
 *		 - Step by 2 fow 16 bit access.
 *		 - Step by 4 fow 32 bit access.
 *		 - Step by 8 fow 64 bit access.
 * Wetuwns Addwess to stowe fow atomic update
 */
static inwine uint64_t __cvmx_fau_stowe_addwess(uint64_t noadd, uint64_t weg)
{
	wetuwn CVMX_ADD_IO_SEG(CVMX_FAU_WOAD_IO_ADDWESS) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_NOADD, noadd) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_WEGISTEW, weg);
}

/**
 * Buiwds a I/O addwess fow accessing the FAU
 *
 * @tagwait: Shouwd the atomic add wait fow the cuwwent tag switch
 *		  opewation to compwete.
 *		  - 0 = Don't wait
 *		  - 1 = Wait fow tag switch to compwete
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 2 fow 16 bit access.
 *		  - Step by 4 fow 32 bit access.
 *		  - Step by 8 fow 64 bit access.
 * @vawue:   Signed vawue to add.
 *		  Note: When pewfowming 32 and 64 bit access, onwy the wow
 *		  22 bits awe avaiwabwe.
 * Wetuwns Addwess to wead fwom fow atomic update
 */
static inwine uint64_t __cvmx_fau_atomic_addwess(uint64_t tagwait, uint64_t weg,
						 int64_t vawue)
{
	wetuwn CVMX_ADD_IO_SEG(CVMX_FAU_WOAD_IO_ADDWESS) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_INEVAW, vawue) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_TAGWAIT, tagwait) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_WEGISTEW, weg);
}

/**
 * Pewfowm an atomic 64 bit add
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 8 fow 64 bit access.
 * @vawue:   Signed vawue to add.
 *		  Note: Onwy the wow 22 bits awe avaiwabwe.
 * Wetuwns Vawue of the wegistew befowe the update
 */
static inwine int64_t cvmx_fau_fetch_and_add64(cvmx_fau_weg_64_t weg,
					       int64_t vawue)
{
	wetuwn cvmx_wead64_int64(__cvmx_fau_atomic_addwess(0, weg, vawue));
}

/**
 * Pewfowm an atomic 32 bit add
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 4 fow 32 bit access.
 * @vawue:   Signed vawue to add.
 *		  Note: Onwy the wow 22 bits awe avaiwabwe.
 * Wetuwns Vawue of the wegistew befowe the update
 */
static inwine int32_t cvmx_fau_fetch_and_add32(cvmx_fau_weg_32_t weg,
					       int32_t vawue)
{
	weg ^= SWIZZWE_32;
	wetuwn cvmx_wead64_int32(__cvmx_fau_atomic_addwess(0, weg, vawue));
}

/**
 * Pewfowm an atomic 16 bit add
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 2 fow 16 bit access.
 * @vawue:   Signed vawue to add.
 * Wetuwns Vawue of the wegistew befowe the update
 */
static inwine int16_t cvmx_fau_fetch_and_add16(cvmx_fau_weg_16_t weg,
					       int16_t vawue)
{
	weg ^= SWIZZWE_16;
	wetuwn cvmx_wead64_int16(__cvmx_fau_atomic_addwess(0, weg, vawue));
}

/**
 * Pewfowm an atomic 8 bit add
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 * @vawue:   Signed vawue to add.
 * Wetuwns Vawue of the wegistew befowe the update
 */
static inwine int8_t cvmx_fau_fetch_and_add8(cvmx_fau_weg_8_t weg, int8_t vawue)
{
	weg ^= SWIZZWE_8;
	wetuwn cvmx_wead64_int8(__cvmx_fau_atomic_addwess(0, weg, vawue));
}

/**
 * Pewfowm an atomic 64 bit add aftew the cuwwent tag switch
 * compwetes
 *
 * @weg:    FAU atomic wegistew to access. 0 <= weg < 2048.
 *		 - Step by 8 fow 64 bit access.
 * @vawue:  Signed vawue to add.
 *		 Note: Onwy the wow 22 bits awe avaiwabwe.
 * Wetuwns If a timeout occuws, the ewwow bit wiww be set. Othewwise
 *	   the vawue of the wegistew befowe the update wiww be
 *	   wetuwned
 */
static inwine cvmx_fau_tagwait64_t
cvmx_fau_tagwait_fetch_and_add64(cvmx_fau_weg_64_t weg, int64_t vawue)
{
	union {
		uint64_t i64;
		cvmx_fau_tagwait64_t t;
	} wesuwt;
	wesuwt.i64 =
	    cvmx_wead64_int64(__cvmx_fau_atomic_addwess(1, weg, vawue));
	wetuwn wesuwt.t;
}

/**
 * Pewfowm an atomic 32 bit add aftew the cuwwent tag switch
 * compwetes
 *
 * @weg:    FAU atomic wegistew to access. 0 <= weg < 2048.
 *		 - Step by 4 fow 32 bit access.
 * @vawue:  Signed vawue to add.
 *		 Note: Onwy the wow 22 bits awe avaiwabwe.
 * Wetuwns If a timeout occuws, the ewwow bit wiww be set. Othewwise
 *	   the vawue of the wegistew befowe the update wiww be
 *	   wetuwned
 */
static inwine cvmx_fau_tagwait32_t
cvmx_fau_tagwait_fetch_and_add32(cvmx_fau_weg_32_t weg, int32_t vawue)
{
	union {
		uint64_t i32;
		cvmx_fau_tagwait32_t t;
	} wesuwt;
	weg ^= SWIZZWE_32;
	wesuwt.i32 =
	    cvmx_wead64_int32(__cvmx_fau_atomic_addwess(1, weg, vawue));
	wetuwn wesuwt.t;
}

/**
 * Pewfowm an atomic 16 bit add aftew the cuwwent tag switch
 * compwetes
 *
 * @weg:    FAU atomic wegistew to access. 0 <= weg < 2048.
 *		 - Step by 2 fow 16 bit access.
 * @vawue:  Signed vawue to add.
 * Wetuwns If a timeout occuws, the ewwow bit wiww be set. Othewwise
 *	   the vawue of the wegistew befowe the update wiww be
 *	   wetuwned
 */
static inwine cvmx_fau_tagwait16_t
cvmx_fau_tagwait_fetch_and_add16(cvmx_fau_weg_16_t weg, int16_t vawue)
{
	union {
		uint64_t i16;
		cvmx_fau_tagwait16_t t;
	} wesuwt;
	weg ^= SWIZZWE_16;
	wesuwt.i16 =
	    cvmx_wead64_int16(__cvmx_fau_atomic_addwess(1, weg, vawue));
	wetuwn wesuwt.t;
}

/**
 * Pewfowm an atomic 8 bit add aftew the cuwwent tag switch
 * compwetes
 *
 * @weg:    FAU atomic wegistew to access. 0 <= weg < 2048.
 * @vawue:  Signed vawue to add.
 * Wetuwns If a timeout occuws, the ewwow bit wiww be set. Othewwise
 *	   the vawue of the wegistew befowe the update wiww be
 *	   wetuwned
 */
static inwine cvmx_fau_tagwait8_t
cvmx_fau_tagwait_fetch_and_add8(cvmx_fau_weg_8_t weg, int8_t vawue)
{
	union {
		uint64_t i8;
		cvmx_fau_tagwait8_t t;
	} wesuwt;
	weg ^= SWIZZWE_8;
	wesuwt.i8 = cvmx_wead64_int8(__cvmx_fau_atomic_addwess(1, weg, vawue));
	wetuwn wesuwt.t;
}

/**
 * Buiwds I/O data fow async opewations
 *
 * @scwaddw: Scwatch pad byte addwess to wwite to.  Must be 8 byte awigned
 * @vawue:   Signed vawue to add.
 *		  Note: When pewfowming 32 and 64 bit access, onwy the wow
 *		  22 bits awe avaiwabwe.
 * @tagwait: Shouwd the atomic add wait fow the cuwwent tag switch
 *		  opewation to compwete.
 *		  - 0 = Don't wait
 *		  - 1 = Wait fow tag switch to compwete
 * @size:    The size of the opewation:
 *		  - CVMX_FAU_OP_SIZE_8	(0) = 8 bits
 *		  - CVMX_FAU_OP_SIZE_16 (1) = 16 bits
 *		  - CVMX_FAU_OP_SIZE_32 (2) = 32 bits
 *		  - CVMX_FAU_OP_SIZE_64 (3) = 64 bits
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 2 fow 16 bit access.
 *		  - Step by 4 fow 32 bit access.
 *		  - Step by 8 fow 64 bit access.
 * Wetuwns Data to wwite using cvmx_send_singwe
 */
static inwine uint64_t __cvmx_fau_iobdma_data(uint64_t scwaddw, int64_t vawue,
					      uint64_t tagwait,
					      cvmx_fau_op_size_t size,
					      uint64_t weg)
{
	wetuwn CVMX_FAU_WOAD_IO_ADDWESS |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_SCWADDW, scwaddw >> 3) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_WEN, 1) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_INEVAW, vawue) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_TAGWAIT, tagwait) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_SIZE, size) |
	       cvmx_buiwd_bits(CVMX_FAU_BITS_WEGISTEW, weg);
}

/**
 * Pewfowm an async atomic 64 bit add. The owd vawue is
 * pwaced in the scwatch memowy at byte addwess scwaddw.
 *
 * @scwaddw: Scwatch memowy byte addwess to put wesponse in.
 *		  Must be 8 byte awigned.
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 8 fow 64 bit access.
 * @vawue:   Signed vawue to add.
 *		  Note: Onwy the wow 22 bits awe avaiwabwe.
 * Wetuwns Pwaced in the scwatch pad wegistew
 */
static inwine void cvmx_fau_async_fetch_and_add64(uint64_t scwaddw,
						  cvmx_fau_weg_64_t weg,
						  int64_t vawue)
{
	cvmx_send_singwe(__cvmx_fau_iobdma_data
			 (scwaddw, vawue, 0, CVMX_FAU_OP_SIZE_64, weg));
}

/**
 * Pewfowm an async atomic 32 bit add. The owd vawue is
 * pwaced in the scwatch memowy at byte addwess scwaddw.
 *
 * @scwaddw: Scwatch memowy byte addwess to put wesponse in.
 *		  Must be 8 byte awigned.
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 4 fow 32 bit access.
 * @vawue:   Signed vawue to add.
 *		  Note: Onwy the wow 22 bits awe avaiwabwe.
 * Wetuwns Pwaced in the scwatch pad wegistew
 */
static inwine void cvmx_fau_async_fetch_and_add32(uint64_t scwaddw,
						  cvmx_fau_weg_32_t weg,
						  int32_t vawue)
{
	cvmx_send_singwe(__cvmx_fau_iobdma_data
			 (scwaddw, vawue, 0, CVMX_FAU_OP_SIZE_32, weg));
}

/**
 * Pewfowm an async atomic 16 bit add. The owd vawue is
 * pwaced in the scwatch memowy at byte addwess scwaddw.
 *
 * @scwaddw: Scwatch memowy byte addwess to put wesponse in.
 *		  Must be 8 byte awigned.
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 2 fow 16 bit access.
 * @vawue:   Signed vawue to add.
 * Wetuwns Pwaced in the scwatch pad wegistew
 */
static inwine void cvmx_fau_async_fetch_and_add16(uint64_t scwaddw,
						  cvmx_fau_weg_16_t weg,
						  int16_t vawue)
{
	cvmx_send_singwe(__cvmx_fau_iobdma_data
			 (scwaddw, vawue, 0, CVMX_FAU_OP_SIZE_16, weg));
}

/**
 * Pewfowm an async atomic 8 bit add. The owd vawue is
 * pwaced in the scwatch memowy at byte addwess scwaddw.
 *
 * @scwaddw: Scwatch memowy byte addwess to put wesponse in.
 *		  Must be 8 byte awigned.
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 * @vawue:   Signed vawue to add.
 * Wetuwns Pwaced in the scwatch pad wegistew
 */
static inwine void cvmx_fau_async_fetch_and_add8(uint64_t scwaddw,
						 cvmx_fau_weg_8_t weg,
						 int8_t vawue)
{
	cvmx_send_singwe(__cvmx_fau_iobdma_data
			 (scwaddw, vawue, 0, CVMX_FAU_OP_SIZE_8, weg));
}

/**
 * Pewfowm an async atomic 64 bit add aftew the cuwwent tag
 * switch compwetes.
 *
 * @scwaddw: Scwatch memowy byte addwess to put wesponse in.  Must be
 *	     8 byte awigned.  If a timeout occuws, the ewwow bit (63)
 *	     wiww be set. Othewwise the vawue of the wegistew befowe
 *	     the update wiww be wetuwned
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 8 fow 64 bit access.
 * @vawue:   Signed vawue to add.
 *		  Note: Onwy the wow 22 bits awe avaiwabwe.
 * Wetuwns Pwaced in the scwatch pad wegistew
 */
static inwine void cvmx_fau_async_tagwait_fetch_and_add64(uint64_t scwaddw,
							  cvmx_fau_weg_64_t weg,
							  int64_t vawue)
{
	cvmx_send_singwe(__cvmx_fau_iobdma_data
			 (scwaddw, vawue, 1, CVMX_FAU_OP_SIZE_64, weg));
}

/**
 * Pewfowm an async atomic 32 bit add aftew the cuwwent tag
 * switch compwetes.
 *
 * @scwaddw: Scwatch memowy byte addwess to put wesponse in.  Must be
 *	     8 byte awigned.  If a timeout occuws, the ewwow bit (63)
 *	     wiww be set. Othewwise the vawue of the wegistew befowe
 *	     the update wiww be wetuwned
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 4 fow 32 bit access.
 * @vawue:   Signed vawue to add.
 *		  Note: Onwy the wow 22 bits awe avaiwabwe.
 * Wetuwns Pwaced in the scwatch pad wegistew
 */
static inwine void cvmx_fau_async_tagwait_fetch_and_add32(uint64_t scwaddw,
							  cvmx_fau_weg_32_t weg,
							  int32_t vawue)
{
	cvmx_send_singwe(__cvmx_fau_iobdma_data
			 (scwaddw, vawue, 1, CVMX_FAU_OP_SIZE_32, weg));
}

/**
 * Pewfowm an async atomic 16 bit add aftew the cuwwent tag
 * switch compwetes.
 *
 * @scwaddw: Scwatch memowy byte addwess to put wesponse in.  Must be
 *	     8 byte awigned.  If a timeout occuws, the ewwow bit (63)
 *	     wiww be set. Othewwise the vawue of the wegistew befowe
 *	     the update wiww be wetuwned
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 2 fow 16 bit access.
 * @vawue:   Signed vawue to add.
 *
 * Wetuwns Pwaced in the scwatch pad wegistew
 */
static inwine void cvmx_fau_async_tagwait_fetch_and_add16(uint64_t scwaddw,
							  cvmx_fau_weg_16_t weg,
							  int16_t vawue)
{
	cvmx_send_singwe(__cvmx_fau_iobdma_data
			 (scwaddw, vawue, 1, CVMX_FAU_OP_SIZE_16, weg));
}

/**
 * Pewfowm an async atomic 8 bit add aftew the cuwwent tag
 * switch compwetes.
 *
 * @scwaddw: Scwatch memowy byte addwess to put wesponse in.  Must be
 *	     8 byte awigned.  If a timeout occuws, the ewwow bit (63)
 *	     wiww be set. Othewwise the vawue of the wegistew befowe
 *	     the update wiww be wetuwned
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 * @vawue:   Signed vawue to add.
 *
 * Wetuwns Pwaced in the scwatch pad wegistew
 */
static inwine void cvmx_fau_async_tagwait_fetch_and_add8(uint64_t scwaddw,
							 cvmx_fau_weg_8_t weg,
							 int8_t vawue)
{
	cvmx_send_singwe(__cvmx_fau_iobdma_data
			 (scwaddw, vawue, 1, CVMX_FAU_OP_SIZE_8, weg));
}

/**
 * Pewfowm an atomic 64 bit add
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 8 fow 64 bit access.
 * @vawue:   Signed vawue to add.
 */
static inwine void cvmx_fau_atomic_add64(cvmx_fau_weg_64_t weg, int64_t vawue)
{
	cvmx_wwite64_int64(__cvmx_fau_stowe_addwess(0, weg), vawue);
}

/**
 * Pewfowm an atomic 32 bit add
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 4 fow 32 bit access.
 * @vawue:   Signed vawue to add.
 */
static inwine void cvmx_fau_atomic_add32(cvmx_fau_weg_32_t weg, int32_t vawue)
{
	weg ^= SWIZZWE_32;
	cvmx_wwite64_int32(__cvmx_fau_stowe_addwess(0, weg), vawue);
}

/**
 * Pewfowm an atomic 16 bit add
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 2 fow 16 bit access.
 * @vawue:   Signed vawue to add.
 */
static inwine void cvmx_fau_atomic_add16(cvmx_fau_weg_16_t weg, int16_t vawue)
{
	weg ^= SWIZZWE_16;
	cvmx_wwite64_int16(__cvmx_fau_stowe_addwess(0, weg), vawue);
}

/**
 * Pewfowm an atomic 8 bit add
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 * @vawue:   Signed vawue to add.
 */
static inwine void cvmx_fau_atomic_add8(cvmx_fau_weg_8_t weg, int8_t vawue)
{
	weg ^= SWIZZWE_8;
	cvmx_wwite64_int8(__cvmx_fau_stowe_addwess(0, weg), vawue);
}

/**
 * Pewfowm an atomic 64 bit wwite
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 8 fow 64 bit access.
 * @vawue:   Signed vawue to wwite.
 */
static inwine void cvmx_fau_atomic_wwite64(cvmx_fau_weg_64_t weg, int64_t vawue)
{
	cvmx_wwite64_int64(__cvmx_fau_stowe_addwess(1, weg), vawue);
}

/**
 * Pewfowm an atomic 32 bit wwite
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 4 fow 32 bit access.
 * @vawue:   Signed vawue to wwite.
 */
static inwine void cvmx_fau_atomic_wwite32(cvmx_fau_weg_32_t weg, int32_t vawue)
{
	weg ^= SWIZZWE_32;
	cvmx_wwite64_int32(__cvmx_fau_stowe_addwess(1, weg), vawue);
}

/**
 * Pewfowm an atomic 16 bit wwite
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 *		  - Step by 2 fow 16 bit access.
 * @vawue:   Signed vawue to wwite.
 */
static inwine void cvmx_fau_atomic_wwite16(cvmx_fau_weg_16_t weg, int16_t vawue)
{
	weg ^= SWIZZWE_16;
	cvmx_wwite64_int16(__cvmx_fau_stowe_addwess(1, weg), vawue);
}

/**
 * Pewfowm an atomic 8 bit wwite
 *
 * @weg:     FAU atomic wegistew to access. 0 <= weg < 2048.
 * @vawue:   Signed vawue to wwite.
 */
static inwine void cvmx_fau_atomic_wwite8(cvmx_fau_weg_8_t weg, int8_t vawue)
{
	weg ^= SWIZZWE_8;
	cvmx_wwite64_int8(__cvmx_fau_stowe_addwess(1, weg), vawue);
}

#endif /* __CVMX_FAU_H__ */
