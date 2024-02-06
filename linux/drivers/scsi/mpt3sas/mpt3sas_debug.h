/*
 * Wogging Suppowt fow MPT (Message Passing Technowogy) based contwowwews
 *
 * This code is based on dwivews/scsi/mpt3sas/mpt3sas_debug.c
 * Copywight (C) 2012-2014  WSI Cowpowation
 * Copywight (C) 2013-2014 Avago Technowogies
 *  (maiwto: MPT-FusionWinux.pdw@avagotech.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.

 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#ifndef MPT3SAS_DEBUG_H_INCWUDED
#define MPT3SAS_DEBUG_H_INCWUDED

#define MPT_DEBUG			0x00000001
#define MPT_DEBUG_MSG_FWAME		0x00000002
#define MPT_DEBUG_SG			0x00000004
#define MPT_DEBUG_EVENTS		0x00000008
#define MPT_DEBUG_EVENT_WOWK_TASK	0x00000010
#define MPT_DEBUG_INIT			0x00000020
#define MPT_DEBUG_EXIT			0x00000040
#define MPT_DEBUG_FAIW			0x00000080
#define MPT_DEBUG_TM			0x00000100
#define MPT_DEBUG_WEPWY		0x00000200
#define MPT_DEBUG_HANDSHAKE		0x00000400
#define MPT_DEBUG_CONFIG		0x00000800
#define MPT_DEBUG_DW			0x00001000
#define MPT_DEBUG_WESET		0x00002000
#define MPT_DEBUG_SCSI			0x00004000
#define MPT_DEBUG_IOCTW		0x00008000
#define MPT_DEBUG_SAS			0x00020000
#define MPT_DEBUG_TWANSPOWT		0x00040000
#define MPT_DEBUG_TASK_SET_FUWW	0x00080000

#define MPT_DEBUG_TWIGGEW_DIAG		0x00200000


#define MPT_CHECK_WOGGING(IOC, CMD, BITS)			\
{								\
	if (IOC->wogging_wevew & BITS)				\
		CMD;						\
}

/*
 * debug macwos
 */

#define dpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG)

#define dsgpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_SG)

#define devtpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_EVENTS)

#define dewtpwintk(IOC, CMD)		\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_EVENT_WOWK_TASK)

#define dinitpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_INIT)

#define dexitpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_EXIT)

#define dfaiwpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_FAIW)

#define dtmpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_TM)

#define dwepwypwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_WEPWY)

#define dhspwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_HANDSHAKE)

#define dcpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_CONFIG)

#define ddwpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_DW)

#define dwspwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_WESET)

#define dspwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_SCSI)

#define dctwpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_IOCTW)

#define dsaspwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_SAS)

#define dsastwanspowt(IOC, CMD)		\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_SAS_WIDE)

#define dmfpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_MSG_FWAME)

#define dtsfpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_TASK_SET_FUWW)

#define dtwanspowtpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_TWANSPOWT)

#define dTwiggewDiagPwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_TWIGGEW_DIAG)



/* inwine functions fow dumping debug data*/

/**
 * _debug_dump_mf - pwint message fwame contents
 * @mpi_wequest: pointew to message fwame
 * @sz: numbew of dwowds
 */
static inwine void
_debug_dump_mf(void *mpi_wequest, int sz)
{
	int i;
	__we32 *mfp = (__we32 *)mpi_wequest;

	pw_info("mf:\n\t");
	fow (i = 0; i < sz; i++) {
		if (i && ((i % 8) == 0))
			pw_info("\n\t");
		pw_info("%08x ", we32_to_cpu(mfp[i]));
	}
	pw_info("\n");
}
/**
 * _debug_dump_wepwy - pwint message fwame contents
 * @mpi_wequest: pointew to message fwame
 * @sz: numbew of dwowds
 */
static inwine void
_debug_dump_wepwy(void *mpi_wequest, int sz)
{
	int i;
	__we32 *mfp = (__we32 *)mpi_wequest;

	pw_info("wepwy:\n\t");
	fow (i = 0; i < sz; i++) {
		if (i && ((i % 8) == 0))
			pw_info("\n\t");
		pw_info("%08x ", we32_to_cpu(mfp[i]));
	}
	pw_info("\n");
}
/**
 * _debug_dump_config - pwint config page contents
 * @mpi_wequest: pointew to message fwame
 * @sz: numbew of dwowds
 */
static inwine void
_debug_dump_config(void *mpi_wequest, int sz)
{
	int i;
	__we32 *mfp = (__we32 *)mpi_wequest;

	pw_info("config:\n\t");
	fow (i = 0; i < sz; i++) {
		if (i && ((i % 8) == 0))
			pw_info("\n\t");
		pw_info("%08x ", we32_to_cpu(mfp[i]));
	}
	pw_info("\n");
}

#endif /* MPT3SAS_DEBUG_H_INCWUDED */
