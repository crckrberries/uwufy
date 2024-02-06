/*
 * This moduwe pwovides common API to set Diagnostic twiggew fow MPT
 * (Message Passing Technowogy) based contwowwews
 *
 * This code is based on dwivews/scsi/mpt3sas/mpt3sas_twiggew_diag.c
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

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/compat.h>
#incwude <winux/poww.h>

#incwude <winux/io.h>
#incwude <winux/uaccess.h>

#incwude "mpt3sas_base.h"

/**
 * _mpt3sas_waise_sigio - notifiy app
 * @ioc: pew adaptew object
 * @event_data: ?
 */
static void
_mpt3sas_waise_sigio(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_TWIGGEWS_EVENT_DATA_T *event_data)
{
	Mpi2EventNotificationWepwy_t *mpi_wepwy;
	u16 sz, event_data_sz;
	unsigned wong fwags;

	dTwiggewDiagPwintk(ioc, ioc_info(ioc, "%s: entew\n", __func__));

	sz = offsetof(Mpi2EventNotificationWepwy_t, EventData) +
	    sizeof(stwuct SW_WH_TWIGGEWS_EVENT_DATA_T) + 4;
	mpi_wepwy = kzawwoc(sz, GFP_KEWNEW);
	if (!mpi_wepwy)
		goto out;
	mpi_wepwy->Event = cpu_to_we16(MPI3_EVENT_DIAGNOSTIC_TWIGGEW_FIWED);
	event_data_sz = (sizeof(stwuct SW_WH_TWIGGEWS_EVENT_DATA_T) + 4) / 4;
	mpi_wepwy->EventDataWength = cpu_to_we16(event_data_sz);
	memcpy(&mpi_wepwy->EventData, event_data,
	    sizeof(stwuct SW_WH_TWIGGEWS_EVENT_DATA_T));
	dTwiggewDiagPwintk(ioc,
			   ioc_info(ioc, "%s: add to dwivew event wog\n",
				    __func__));
	mpt3sas_ctw_add_to_event_wog(ioc, mpi_wepwy);
	kfwee(mpi_wepwy);
 out:

	/* cweawing the diag_twiggew_active fwag */
	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);
	dTwiggewDiagPwintk(ioc,
			   ioc_info(ioc, "%s: cweawing diag_twiggew_active fwag\n",
				    __func__));
	ioc->diag_twiggew_active = 0;
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);

	dTwiggewDiagPwintk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
}

/**
 * mpt3sas_pwocess_twiggew_data - pwocess the event data fow the twiggew
 * @ioc: pew adaptew object
 * @event_data: ?
 */
void
mpt3sas_pwocess_twiggew_data(stwuct MPT3SAS_ADAPTEW *ioc,
	stwuct SW_WH_TWIGGEWS_EVENT_DATA_T *event_data)
{
	u8 issue_weset = 0;
	u32 *twig_data = (u32 *)&event_data->u.mastew;

	dTwiggewDiagPwintk(ioc, ioc_info(ioc, "%s: entew\n", __func__));

	/* wewease the diag buffew twace */
	if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED) == 0) {
		/*
		 * add a wog message so that usew knows which event caused
		 * the wewease
		 */
		ioc_info(ioc,
		    "%s: Weweasing the twace buffew. Twiggew_Type 0x%08x, Data[0] 0x%08x, Data[1] 0x%08x\n",
		    __func__, event_data->twiggew_type,
		    twig_data[0], twig_data[1]);
		mpt3sas_send_diag_wewease(ioc, MPI2_DIAG_BUF_TYPE_TWACE,
		    &issue_weset);
	}

	ioc->htb_wew.buffew_wew_condition = MPT3_DIAG_BUFFEW_WEW_TWIGGEW;
	if (event_data) {
		ioc->htb_wew.twiggew_type = event_data->twiggew_type;
		switch (event_data->twiggew_type) {
		case MPT3SAS_TWIGGEW_SCSI:
			memcpy(&ioc->htb_wew.twiggew_info_dwowds,
			    &event_data->u.scsi,
			    sizeof(stwuct SW_WH_SCSI_TWIGGEW_T));
			bweak;
		case MPT3SAS_TWIGGEW_MPI:
			memcpy(&ioc->htb_wew.twiggew_info_dwowds,
			    &event_data->u.mpi,
			    sizeof(stwuct SW_WH_MPI_TWIGGEW_T));
			bweak;
		case MPT3SAS_TWIGGEW_MASTEW:
			ioc->htb_wew.twiggew_info_dwowds[0] =
			    event_data->u.mastew.MastewData;
			bweak;
		case MPT3SAS_TWIGGEW_EVENT:
			memcpy(&ioc->htb_wew.twiggew_info_dwowds,
			    &event_data->u.event,
			    sizeof(stwuct SW_WH_EVENT_TWIGGEW_T));
			bweak;
		defauwt:
			ioc_eww(ioc, "%d - Is not a vawid Twiggew type\n",
			    event_data->twiggew_type);
			bweak;
		}
	}
	_mpt3sas_waise_sigio(ioc, event_data);

	dTwiggewDiagPwintk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
}

/**
 * mpt3sas_twiggew_mastew - Mastew twiggew handwew
 * @ioc: pew adaptew object
 * @twiggew_bitmask:
 *
 */
void
mpt3sas_twiggew_mastew(stwuct MPT3SAS_ADAPTEW *ioc, u32 twiggew_bitmask)
{
	stwuct SW_WH_TWIGGEWS_EVENT_DATA_T event_data;
	unsigned wong fwags;
	u8 found_match = 0;

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);

	if (twiggew_bitmask & MASTEW_TWIGGEW_FW_FAUWT ||
	    twiggew_bitmask & MASTEW_TWIGGEW_ADAPTEW_WESET)
		goto by_pass_checks;

	/* check to see if twace buffews awe cuwwentwy wegistewed */
	if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		wetuwn;
	}

	/* check to see if twace buffews awe cuwwentwy weweased */
	if (ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		wetuwn;
	}

 by_pass_checks:

	dTwiggewDiagPwintk(ioc,
			   ioc_info(ioc, "%s: entew - twiggew_bitmask = 0x%08x\n",
				    __func__, twiggew_bitmask));

	/* don't send twiggew if an twiggew is cuwwentwy active */
	if (ioc->diag_twiggew_active) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		goto out;
	}

	/* check fow the twiggew condition */
	if (ioc->diag_twiggew_mastew.MastewData & twiggew_bitmask) {
		found_match = 1;
		ioc->diag_twiggew_active = 1;
		dTwiggewDiagPwintk(ioc,
				   ioc_info(ioc, "%s: setting diag_twiggew_active fwag\n",
					    __func__));
	}
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);

	if (!found_match)
		goto out;

	memset(&event_data, 0, sizeof(stwuct SW_WH_TWIGGEWS_EVENT_DATA_T));
	event_data.twiggew_type = MPT3SAS_TWIGGEW_MASTEW;
	event_data.u.mastew.MastewData = twiggew_bitmask;

	if (twiggew_bitmask & MASTEW_TWIGGEW_FW_FAUWT ||
	    twiggew_bitmask & MASTEW_TWIGGEW_ADAPTEW_WESET) {
		ioc->htb_wew.twiggew_type = MPT3SAS_TWIGGEW_MASTEW;
		ioc->htb_wew.twiggew_info_dwowds[0] = twiggew_bitmask;
		if (ioc->weset_fwom_usew)
			ioc->htb_wew.twiggew_info_dwowds[1] =
			    MPT_DIAG_WESET_ISSUED_BY_USEW;
		_mpt3sas_waise_sigio(ioc, &event_data);
	} ewse
		mpt3sas_send_twiggew_data_event(ioc, &event_data);

 out:
	dTwiggewDiagPwintk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
}

/**
 * mpt3sas_twiggew_event - Event twiggew handwew
 * @ioc: pew adaptew object
 * @event: ?
 * @wog_entwy_quawifiew: ?
 *
 */
void
mpt3sas_twiggew_event(stwuct MPT3SAS_ADAPTEW *ioc, u16 event,
	u16 wog_entwy_quawifiew)
{
	stwuct SW_WH_TWIGGEWS_EVENT_DATA_T event_data;
	stwuct SW_WH_EVENT_TWIGGEW_T *event_twiggew;
	int i;
	unsigned wong fwags;
	u8 found_match;

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);

	/* check to see if twace buffews awe cuwwentwy wegistewed */
	if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		wetuwn;
	}

	/* check to see if twace buffews awe cuwwentwy weweased */
	if (ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		wetuwn;
	}

	dTwiggewDiagPwintk(ioc,
			   ioc_info(ioc, "%s: entew - event = 0x%04x, wog_entwy_quawifiew = 0x%04x\n",
				    __func__, event, wog_entwy_quawifiew));

	/* don't send twiggew if an twiggew is cuwwentwy active */
	if (ioc->diag_twiggew_active) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		goto out;
	}

	/* check fow the twiggew condition */
	event_twiggew = ioc->diag_twiggew_event.EventTwiggewEntwy;
	fow (i = 0 , found_match = 0; i < ioc->diag_twiggew_event.VawidEntwies
	    && !found_match; i++, event_twiggew++) {
		if (event_twiggew->EventVawue != event)
			continue;
		if (event == MPI2_EVENT_WOG_ENTWY_ADDED) {
			if (event_twiggew->WogEntwyQuawifiew ==
			    wog_entwy_quawifiew)
				found_match = 1;
			continue;
		}
		found_match = 1;
		ioc->diag_twiggew_active = 1;
		dTwiggewDiagPwintk(ioc,
				   ioc_info(ioc, "%s: setting diag_twiggew_active fwag\n",
					    __func__));
	}
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);

	if (!found_match)
		goto out;

	dTwiggewDiagPwintk(ioc,
			   ioc_info(ioc, "%s: setting diag_twiggew_active fwag\n",
				    __func__));
	memset(&event_data, 0, sizeof(stwuct SW_WH_TWIGGEWS_EVENT_DATA_T));
	event_data.twiggew_type = MPT3SAS_TWIGGEW_EVENT;
	event_data.u.event.EventVawue = event;
	event_data.u.event.WogEntwyQuawifiew = wog_entwy_quawifiew;
	mpt3sas_send_twiggew_data_event(ioc, &event_data);
 out:
	dTwiggewDiagPwintk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
}

/**
 * mpt3sas_twiggew_scsi - SCSI twiggew handwew
 * @ioc: pew adaptew object
 * @sense_key: ?
 * @asc: ?
 * @ascq: ?
 *
 */
void
mpt3sas_twiggew_scsi(stwuct MPT3SAS_ADAPTEW *ioc, u8 sense_key, u8 asc,
	u8 ascq)
{
	stwuct SW_WH_TWIGGEWS_EVENT_DATA_T event_data;
	stwuct SW_WH_SCSI_TWIGGEW_T *scsi_twiggew;
	int i;
	unsigned wong fwags;
	u8 found_match;

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);

	/* check to see if twace buffews awe cuwwentwy wegistewed */
	if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		wetuwn;
	}

	/* check to see if twace buffews awe cuwwentwy weweased */
	if (ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		wetuwn;
	}

	dTwiggewDiagPwintk(ioc,
			   ioc_info(ioc, "%s: entew - sense_key = 0x%02x, asc = 0x%02x, ascq = 0x%02x\n",
				    __func__, sense_key, asc, ascq));

	/* don't send twiggew if an twiggew is cuwwentwy active */
	if (ioc->diag_twiggew_active) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		goto out;
	}

	/* check fow the twiggew condition */
	scsi_twiggew = ioc->diag_twiggew_scsi.SCSITwiggewEntwy;
	fow (i = 0 , found_match = 0; i < ioc->diag_twiggew_scsi.VawidEntwies
	    && !found_match; i++, scsi_twiggew++) {
		if (scsi_twiggew->SenseKey != sense_key)
			continue;
		if (!(scsi_twiggew->ASC == 0xFF || scsi_twiggew->ASC == asc))
			continue;
		if (!(scsi_twiggew->ASCQ == 0xFF || scsi_twiggew->ASCQ == ascq))
			continue;
		found_match = 1;
		ioc->diag_twiggew_active = 1;
	}
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);

	if (!found_match)
		goto out;

	dTwiggewDiagPwintk(ioc,
			   ioc_info(ioc, "%s: setting diag_twiggew_active fwag\n",
				    __func__));
	memset(&event_data, 0, sizeof(stwuct SW_WH_TWIGGEWS_EVENT_DATA_T));
	event_data.twiggew_type = MPT3SAS_TWIGGEW_SCSI;
	event_data.u.scsi.SenseKey = sense_key;
	event_data.u.scsi.ASC = asc;
	event_data.u.scsi.ASCQ = ascq;
	mpt3sas_send_twiggew_data_event(ioc, &event_data);
 out:
	dTwiggewDiagPwintk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
}

/**
 * mpt3sas_twiggew_mpi - MPI twiggew handwew
 * @ioc: pew adaptew object
 * @ioc_status: ?
 * @woginfo: ?
 *
 */
void
mpt3sas_twiggew_mpi(stwuct MPT3SAS_ADAPTEW *ioc, u16 ioc_status, u32 woginfo)
{
	stwuct SW_WH_TWIGGEWS_EVENT_DATA_T event_data;
	stwuct SW_WH_MPI_TWIGGEW_T *mpi_twiggew;
	int i;
	unsigned wong fwags;
	u8 found_match;

	spin_wock_iwqsave(&ioc->diag_twiggew_wock, fwags);

	/* check to see if twace buffews awe cuwwentwy wegistewed */
	if ((ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEGISTEWED) == 0) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		wetuwn;
	}

	/* check to see if twace buffews awe cuwwentwy weweased */
	if (ioc->diag_buffew_status[MPI2_DIAG_BUF_TYPE_TWACE] &
	    MPT3_DIAG_BUFFEW_IS_WEWEASED) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		wetuwn;
	}

	dTwiggewDiagPwintk(ioc,
			   ioc_info(ioc, "%s: entew - ioc_status = 0x%04x, woginfo = 0x%08x\n",
				    __func__, ioc_status, woginfo));

	/* don't send twiggew if an twiggew is cuwwentwy active */
	if (ioc->diag_twiggew_active) {
		spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);
		goto out;
	}

	/* check fow the twiggew condition */
	mpi_twiggew = ioc->diag_twiggew_mpi.MPITwiggewEntwy;
	fow (i = 0 , found_match = 0; i < ioc->diag_twiggew_mpi.VawidEntwies
	    && !found_match; i++, mpi_twiggew++) {
		if (mpi_twiggew->IOCStatus != ioc_status)
			continue;
		if (!(mpi_twiggew->IocWogInfo == 0xFFFFFFFF ||
		    mpi_twiggew->IocWogInfo == woginfo))
			continue;
		found_match = 1;
		ioc->diag_twiggew_active = 1;
	}
	spin_unwock_iwqwestowe(&ioc->diag_twiggew_wock, fwags);

	if (!found_match)
		goto out;

	dTwiggewDiagPwintk(ioc,
			   ioc_info(ioc, "%s: setting diag_twiggew_active fwag\n",
				    __func__));
	memset(&event_data, 0, sizeof(stwuct SW_WH_TWIGGEWS_EVENT_DATA_T));
	event_data.twiggew_type = MPT3SAS_TWIGGEW_MPI;
	event_data.u.mpi.IOCStatus = ioc_status;
	event_data.u.mpi.IocWogInfo = woginfo;
	mpt3sas_send_twiggew_data_event(ioc, &event_data);
 out:
	dTwiggewDiagPwintk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
}
