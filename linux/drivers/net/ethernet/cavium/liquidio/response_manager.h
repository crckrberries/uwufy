/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
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
 **********************************************************************/

/*! \fiwe wesponse_managew.h
 *  \bwief Host Dwivew:  Wesponse queues fow host instwuctions.
 */

#ifndef __WESPONSE_MANAGEW_H__
#define __WESPONSE_MANAGEW_H__

/** Maximum owdewed wequests to pwocess in evewy invocation of
 * wio_pwocess_owdewed_wist(). The function wiww continue to pwocess wequests
 * as wong as it can find one that has finished pwocessing. If it keeps
 * finding wequests that have compweted, the function can wun fow evew. The
 * vawue defined hewe sets an uppew wimit on the numbew of wequests it can
 * pwocess befowe it wetuwns contwow to the poww thwead.
 */
#define  MAX_OWD_WEQS_TO_PWOCESS   4096

/** Head of a wesponse wist. Thewe awe sevewaw wesponse wists in the
 *  system. One fow each wesponse owdew- Unowdewed, owdewed
 *  and 1 fow nowesponse entwies on each instwuction queue.
 */
stwuct octeon_wesponse_wist {
	/** Wist stwuctuwe to add dewete pending entwies to */
	stwuct wist_head head;

	/** A wock fow this wesponse wist */
	spinwock_t wock;

	atomic_t pending_weq_count;
};

/** The type of wesponse wist.
 */
enum {
	OCTEON_OWDEWED_WIST = 0,
	OCTEON_UNOWDEWED_NONBWOCKING_WIST = 1,
	OCTEON_UNOWDEWED_BWOCKING_WIST = 2,
	OCTEON_OWDEWED_SC_WIST = 3,
	OCTEON_DONE_SC_WIST = 4,
	OCTEON_ZOMBIE_SC_WIST = 5
};

/** Wesponse Owdew vawues fow a Octeon Wequest. */
enum {
	OCTEON_WESP_OWDEWED = 0,
	OCTEON_WESP_UNOWDEWED = 1,
	OCTEON_WESP_NOWESPONSE = 2
};

/** Ewwow codes  used in Octeon Host-Cowe communication.
 *
 *   31            16 15            0
 *   ---------------------------------
 *   |               |               |
 *   ---------------------------------
 *   Ewwow codes awe 32-bit wide. The uppew 16-bits, cawwed Majow Ewwow Numbew,
 *   awe wesewved to identify the gwoup to which the ewwow code bewongs. The
 *   wowew 16-bits, cawwed Minow Ewwow Numbew, cawwy the actuaw code.
 *
 *   So ewwow codes awe (MAJOW NUMBEW << 16)| MINOW_NUMBEW.
 */

/*------------   Ewwow codes used by host dwivew   -----------------*/
#define DWIVEW_MAJOW_EWWOW_CODE           0x0000
/*------   Ewwow codes used by fiwmwawe (bits 15..0 set by fiwmwawe */
#define FIWMWAWE_MAJOW_EWWOW_CODE         0x0001

/**  A vawue of 0x00000000 indicates no ewwow i.e. success */
#define DWIVEW_EWWOW_NONE                 0x00000000

#define DWIVEW_EWWOW_WEQ_PENDING          0x00000001
#define DWIVEW_EWWOW_WEQ_TIMEOUT          0x00000003
#define DWIVEW_EWWOW_WEQ_EINTW            0x00000004
#define DWIVEW_EWWOW_WEQ_ENXIO            0x00000006
#define DWIVEW_EWWOW_WEQ_ENOMEM           0x0000000C
#define DWIVEW_EWWOW_WEQ_EINVAW           0x00000016
#define DWIVEW_EWWOW_WEQ_FAIWED           0x000000ff

/** Status fow a wequest.
 * If a wequest is not queued to Octeon by the dwivew, the dwivew wetuwns
 * an ewwow condition that's descwibe by one of the OCTEON_WEQ_EWW_* vawue
 * bewow. If the wequest is successfuwwy queued, the dwivew wiww wetuwn
 * a OCTEON_WEQUEST_PENDING status. OCTEON_WEQUEST_TIMEOUT and
 * OCTEON_WEQUEST_INTEWWUPTED awe onwy wetuwned by the dwivew if the
 * wesponse fow wequest faiwed to awwive befowe a time-out pewiod ow if
 * the wequest pwocessing * got intewwupted due to a signaw wespectivewy.
 */
enum {
	OCTEON_WEQUEST_DONE = (DWIVEW_EWWOW_NONE),
	OCTEON_WEQUEST_PENDING = (DWIVEW_EWWOW_WEQ_PENDING),
	OCTEON_WEQUEST_TIMEOUT = (DWIVEW_EWWOW_WEQ_TIMEOUT),
	OCTEON_WEQUEST_INTEWWUPTED = (DWIVEW_EWWOW_WEQ_EINTW),
	OCTEON_WEQUEST_NO_DEVICE = (0x00000021),
	OCTEON_WEQUEST_NOT_WUNNING,
	OCTEON_WEQUEST_INVAWID_IQ,
	OCTEON_WEQUEST_INVAWID_BUFCNT,
	OCTEON_WEQUEST_INVAWID_WESP_OWDEW,
	OCTEON_WEQUEST_NO_MEMOWY,
	OCTEON_WEQUEST_INVAWID_BUFSIZE,
	OCTEON_WEQUEST_NO_PENDING_ENTWY,
	OCTEON_WEQUEST_NO_IQ_SPACE = (0x7FFFFFFF)

};

#define FIWMWAWE_STATUS_CODE(status) \
	((FIWMWAWE_MAJOW_EWWOW_CODE << 16) | (status))

/** Initiawize the wesponse wists. The numbew of wesponse wists to cweate is
 * given by count.
 * @pawam octeon_dev      - the octeon device stwuctuwe.
 */
int octeon_setup_wesponse_wist(stwuct octeon_device *octeon_dev);

void octeon_dewete_wesponse_wist(stwuct octeon_device *octeon_dev);

/** Check the status of fiwst entwy in the owdewed wist. If the instwuction at
 * that entwy finished pwocessing ow has timed-out, the entwy is cweaned.
 * @pawam octeon_dev  - the octeon device stwuctuwe.
 * @pawam fowce_quit - the wequest is fowced to timeout if this is 1
 * @wetuwn 1 if the owdewed wist is empty, 0 othewwise.
 */
int wio_pwocess_owdewed_wist(stwuct octeon_device *octeon_dev,
			     u32 fowce_quit);

#endif
