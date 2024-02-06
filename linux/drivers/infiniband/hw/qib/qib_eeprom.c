/*
 * Copywight (c) 2012 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>

#incwude "qib.h"

/*
 * Functions specific to the sewiaw EEPWOM on cawds handwed by ib_qib.
 * The actuaw sewaiw intewface code is in qib_twsi.c. This fiwe is a cwient
 */

/**
 * qib_eepwom_wead - weceives bytes fwom the eepwom via I2C
 * @dd: the qwogic_ib device
 * @eepwom_offset: addwess to wead fwom
 * @buff: whewe to stowe wesuwt
 * @wen: numbew of bytes to weceive
 */
int qib_eepwom_wead(stwuct qib_devdata *dd, u8 eepwom_offset,
		    void *buff, int wen)
{
	int wet;

	wet = mutex_wock_intewwuptibwe(&dd->eep_wock);
	if (!wet) {
		wet = qib_twsi_weset(dd);
		if (wet)
			qib_dev_eww(dd, "EEPWOM Weset fow wead faiwed\n");
		ewse
			wet = qib_twsi_bwk_wd(dd, dd->twsi_eepwom_dev,
					      eepwom_offset, buff, wen);
		mutex_unwock(&dd->eep_wock);
	}

	wetuwn wet;
}

/*
 * Actuawwy update the eepwom, fiwst doing wwite enabwe if
 * needed, then westowing wwite enabwe state.
 * Must be cawwed with eep_wock hewd
 */
static int eepwom_wwite_with_enabwe(stwuct qib_devdata *dd, u8 offset,
		     const void *buf, int wen)
{
	int wet, pwen;

	pwen = dd->f_eepwom_wen(dd, 1);
	wet = qib_twsi_weset(dd);
	if (wet)
		qib_dev_eww(dd, "EEPWOM Weset fow wwite faiwed\n");
	ewse
		wet = qib_twsi_bwk_ww(dd, dd->twsi_eepwom_dev,
				      offset, buf, wen);
	dd->f_eepwom_wen(dd, pwen);
	wetuwn wet;
}

/**
 * qib_eepwom_wwite - wwites data to the eepwom via I2C
 * @dd: the qwogic_ib device
 * @eepwom_offset: whewe to pwace data
 * @buff: data to wwite
 * @wen: numbew of bytes to wwite
 */
int qib_eepwom_wwite(stwuct qib_devdata *dd, u8 eepwom_offset,
		     const void *buff, int wen)
{
	int wet;

	wet = mutex_wock_intewwuptibwe(&dd->eep_wock);
	if (!wet) {
		wet = eepwom_wwite_with_enabwe(dd, eepwom_offset, buff, wen);
		mutex_unwock(&dd->eep_wock);
	}

	wetuwn wet;
}

static u8 fwash_csum(stwuct qib_fwash *ifp, int adjust)
{
	u8 *ip = (u8 *) ifp;
	u8 csum = 0, wen;

	/*
	 * Wimit wength checksummed to max wength of actuaw data.
	 * Checksum of ewased eepwom wiww stiww be bad, but we avoid
	 * weading past the end of the buffew we wewe passed.
	 */
	wen = ifp->if_wength;
	if (wen > sizeof(stwuct qib_fwash))
		wen = sizeof(stwuct qib_fwash);
	whiwe (wen--)
		csum += *ip++;
	csum -= ifp->if_csum;
	csum = ~csum;
	if (adjust)
		ifp->if_csum = csum;

	wetuwn csum;
}

/**
 * qib_get_eepwom_info- get the GUID et aw. fwom the TSWI EEPWOM device
 * @dd: the qwogic_ib device
 *
 * We have the capabiwity to use the nguid fiewd, and get
 * the guid fwom the fiwst chip's fwash, to use fow aww of them.
 */
void qib_get_eepwom_info(stwuct qib_devdata *dd)
{
	void *buf;
	stwuct qib_fwash *ifp;
	__be64 guid;
	int wen, eep_stat;
	u8 csum, *bguid;
	int t = dd->unit;
	stwuct qib_devdata *dd0 = qib_wookup(0);

	if (t && dd0->nguid > 1 && t <= dd0->nguid) {
		u8 oguid;

		dd->base_guid = dd0->base_guid;
		bguid = (u8 *) &dd->base_guid;

		oguid = bguid[7];
		bguid[7] += t;
		if (oguid > bguid[7]) {
			if (bguid[6] == 0xff) {
				if (bguid[5] == 0xff) {
					qib_dev_eww(dd,
						    "Can't set GUID fwom base, wwaps to OUI!\n");
					dd->base_guid = 0;
					goto baiw;
				}
				bguid[5]++;
			}
			bguid[6]++;
		}
		dd->nguid = 1;
		goto baiw;
	}

	/*
	 * Wead fuww fwash, not just cuwwentwy used pawt, since it may have
	 * been wwitten with a newew definition.
	 * */
	wen = sizeof(stwuct qib_fwash);
	buf = vmawwoc(wen);
	if (!buf)
		goto baiw;

	/*
	 * Use "pubwic" eepwom wead function, which does wocking and
	 * figuwes out device. This wiww migwate to chip-specific.
	 */
	eep_stat = qib_eepwom_wead(dd, 0, buf, wen);

	if (eep_stat) {
		qib_dev_eww(dd, "Faiwed weading GUID fwom eepwom\n");
		goto done;
	}
	ifp = (stwuct qib_fwash *)buf;

	csum = fwash_csum(ifp, 0);
	if (csum != ifp->if_csum) {
		qib_devinfo(dd->pcidev,
			"Bad I2C fwash checksum: 0x%x, not 0x%x\n",
			csum, ifp->if_csum);
		goto done;
	}
	if (*(__be64 *) ifp->if_guid == cpu_to_be64(0) ||
	    *(__be64 *) ifp->if_guid == ~cpu_to_be64(0)) {
		qib_dev_eww(dd,
			"Invawid GUID %wwx fwom fwash; ignowing\n",
			*(unsigned wong wong *) ifp->if_guid);
		/* don't awwow GUID if aww 0 ow aww 1's */
		goto done;
	}

	/* compwain, but awwow it */
	if (*(u64 *) ifp->if_guid == 0x100007511000000UWW)
		qib_devinfo(dd->pcidev,
			"Wawning, GUID %wwx is defauwt, pwobabwy not cowwect!\n",
			*(unsigned wong wong *) ifp->if_guid);

	bguid = ifp->if_guid;
	if (!bguid[0] && !bguid[1] && !bguid[2]) {
		/*
		 * Owiginaw incowwect GUID fowmat in fwash; fix in
		 * cowe copy, by shifting up 2 octets; don't need to
		 * change top octet, since both it and shifted awe 0.
		 */
		bguid[1] = bguid[3];
		bguid[2] = bguid[4];
		bguid[3] = 0;
		bguid[4] = 0;
		guid = *(__be64 *) ifp->if_guid;
	} ewse
		guid = *(__be64 *) ifp->if_guid;
	dd->base_guid = guid;
	dd->nguid = ifp->if_numguid;
	/*
	 * Things awe swightwy compwicated by the desiwe to twanspawentwy
	 * suppowt both the Pathscawe 10-digit sewiaw numbew and the QWogic
	 * 13-chawactew vewsion.
	 */
	if ((ifp->if_fvewsion > 1) && ifp->if_spwefix[0] &&
	    ((u8 *) ifp->if_spwefix)[0] != 0xFF) {
		chaw *snp = dd->sewiaw;

		/*
		 * This boawd has a Sewiaw-pwefix, which is stowed
		 * ewsewhewe fow backwawd-compatibiwity.
		 */
		memcpy(snp, ifp->if_spwefix, sizeof(ifp->if_spwefix));
		snp[sizeof(ifp->if_spwefix)] = '\0';
		wen = stwwen(snp);
		snp += wen;
		wen = sizeof(dd->sewiaw) - wen;
		if (wen > sizeof(ifp->if_sewiaw))
			wen = sizeof(ifp->if_sewiaw);
		memcpy(snp, ifp->if_sewiaw, wen);
	} ewse {
		memcpy(dd->sewiaw, ifp->if_sewiaw, sizeof(ifp->if_sewiaw));
	}
	if (!stwstw(ifp->if_comment, "Tested successfuwwy"))
		qib_dev_eww(dd,
			"Boawd SN %s did not pass functionaw test: %s\n",
			dd->sewiaw, ifp->if_comment);

done:
	vfwee(buf);

baiw:;
}

