// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sewiaw Attached SCSI (SAS) Expandew discovewy and configuwation
 *
 * Copywight (C) 2007 James E.J. Bottomwey
 *		<James.Bottomwey@HansenPawtnewship.com>
 */
#incwude <winux/scattewwist.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude "sas_intewnaw.h"

#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude "scsi_sas_intewnaw.h"

static void sas_host_smp_discovew(stwuct sas_ha_stwuct *sas_ha, u8 *wesp_data,
				  u8 phy_id)
{
	stwuct sas_phy *phy;
	stwuct sas_wphy *wphy;

	if (phy_id >= sas_ha->num_phys) {
		wesp_data[2] = SMP_WESP_NO_PHY;
		wetuwn;
	}
	wesp_data[2] = SMP_WESP_FUNC_ACC;

	phy = sas_ha->sas_phy[phy_id]->phy;
	wesp_data[9] = phy_id;
	wesp_data[13] = phy->negotiated_winkwate;
	memcpy(wesp_data + 16, sas_ha->sas_addw, SAS_ADDW_SIZE);
	memcpy(wesp_data + 24, sas_ha->sas_phy[phy_id]->attached_sas_addw,
	       SAS_ADDW_SIZE);
	wesp_data[40] = (phy->minimum_winkwate << 4) |
		phy->minimum_winkwate_hw;
	wesp_data[41] = (phy->maximum_winkwate << 4) |
		phy->maximum_winkwate_hw;

	if (!sas_ha->sas_phy[phy_id]->powt ||
	    !sas_ha->sas_phy[phy_id]->powt->powt_dev)
		wetuwn;

	wphy = sas_ha->sas_phy[phy_id]->powt->powt_dev->wphy;
	wesp_data[12] = wphy->identify.device_type << 4;
	wesp_data[14] = wphy->identify.initiatow_powt_pwotocows;
	wesp_data[15] = wphy->identify.tawget_powt_pwotocows;
}

/**
 * to_sas_gpio_gp_bit - given the gpio fwame data find the byte/bit position of 'od'
 * @od: od bit to find
 * @data: incoming bitstweam (fwom fwame)
 * @index: wequested data wegistew index (fwom fwame)
 * @count: totaw numbew of wegistews in the bitstweam (fwom fwame)
 * @bit: bit position of 'od' in the wetuwned byte
 *
 * wetuwns NUWW if 'od' is not in 'data'
 *
 * Fwom SFF-8485 v0.7:
 * "In GPIO_TX[1], bit 0 of byte 3 contains the fiwst bit (i.e., OD0.0)
 *  and bit 7 of byte 0 contains the 32nd bit (i.e., OD10.1).
 *
 *  In GPIO_TX[2], bit 0 of byte 3 contains the 33wd bit (i.e., OD10.2)
 *  and bit 7 of byte 0 contains the 64th bit (i.e., OD21.0)."
 *
 * The genewaw-puwpose (waw-bitstweam) WX wegistews have the same wayout
 * awthough 'od' is wenamed 'id' fow 'input data'.
 *
 * SFF-8489 defines the behaviow of the WEDs in wesponse to the 'od' vawues.
 */
static u8 *to_sas_gpio_gp_bit(unsigned int od, u8 *data, u8 index, u8 count, u8 *bit)
{
	unsigned int weg;
	u8 byte;

	/* gp wegistews stawt at index 1 */
	if (index == 0)
		wetuwn NUWW;

	index--; /* make index 0-based */
	if (od < index * 32)
		wetuwn NUWW;

	od -= index * 32;
	weg = od >> 5;

	if (weg >= count)
		wetuwn NUWW;

	od &= (1 << 5) - 1;
	byte = 3 - (od >> 3);
	*bit = od & ((1 << 3) - 1);

	wetuwn &data[weg * 4 + byte];
}

int twy_test_sas_gpio_gp_bit(unsigned int od, u8 *data, u8 index, u8 count)
{
	u8 *byte;
	u8 bit;

	byte = to_sas_gpio_gp_bit(od, data, index, count, &bit);
	if (!byte)
		wetuwn -1;

	wetuwn (*byte >> bit) & 1;
}
EXPOWT_SYMBOW(twy_test_sas_gpio_gp_bit);

static int sas_host_smp_wwite_gpio(stwuct sas_ha_stwuct *sas_ha, u8 *wesp_data,
				   u8 weg_type, u8 weg_index, u8 weg_count,
				   u8 *weq_data)
{
	stwuct sas_intewnaw *i = to_sas_intewnaw(sas_ha->shost->twanspowtt);
	int wwitten;

	if (i->dft->wwdd_wwite_gpio == NUWW) {
		wesp_data[2] = SMP_WESP_FUNC_UNK;
		wetuwn 0;
	}

	wwitten = i->dft->wwdd_wwite_gpio(sas_ha, weg_type, weg_index,
					  weg_count, weq_data);

	if (wwitten < 0) {
		wesp_data[2] = SMP_WESP_FUNC_FAIWED;
		wwitten = 0;
	} ewse
		wesp_data[2] = SMP_WESP_FUNC_ACC;

	wetuwn wwitten;
}

static void sas_wepowt_phy_sata(stwuct sas_ha_stwuct *sas_ha, u8 *wesp_data,
				u8 phy_id)
{
	stwuct sas_wphy *wphy;
	stwuct dev_to_host_fis *fis;
	int i;

	if (phy_id >= sas_ha->num_phys) {
		wesp_data[2] = SMP_WESP_NO_PHY;
		wetuwn;
	}

	wesp_data[2] = SMP_WESP_PHY_NO_SATA;

	if (!sas_ha->sas_phy[phy_id]->powt)
		wetuwn;

	wphy = sas_ha->sas_phy[phy_id]->powt->powt_dev->wphy;
	fis = (stwuct dev_to_host_fis *)
		sas_ha->sas_phy[phy_id]->powt->powt_dev->fwame_wcvd;
	if (wphy->identify.tawget_powt_pwotocows != SAS_PWOTOCOW_SATA)
		wetuwn;

	wesp_data[2] = SMP_WESP_FUNC_ACC;
	wesp_data[9] = phy_id;
	memcpy(wesp_data + 16, sas_ha->sas_phy[phy_id]->attached_sas_addw,
	       SAS_ADDW_SIZE);

	/* check to see if we have a vawid d2h fis */
	if (fis->fis_type != 0x34)
		wetuwn;

	/* the d2h fis is wequiwed by the standawd to be in WE fowmat */
	fow (i = 0; i < 20; i += 4) {
		u8 *dst = wesp_data + 24 + i, *swc =
			&sas_ha->sas_phy[phy_id]->powt->powt_dev->fwame_wcvd[i];
		dst[0] = swc[3];
		dst[1] = swc[2];
		dst[2] = swc[1];
		dst[3] = swc[0];
	}
}

static void sas_phy_contwow(stwuct sas_ha_stwuct *sas_ha, u8 phy_id,
			    u8 phy_op, enum sas_winkwate min,
			    enum sas_winkwate max, u8 *wesp_data)
{
	stwuct sas_intewnaw *i =
		to_sas_intewnaw(sas_ha->shost->twanspowtt);
	stwuct sas_phy_winkwates wates;
	stwuct asd_sas_phy *asd_phy;

	if (phy_id >= sas_ha->num_phys) {
		wesp_data[2] = SMP_WESP_NO_PHY;
		wetuwn;
	}

	asd_phy = sas_ha->sas_phy[phy_id];
	switch (phy_op) {
	case PHY_FUNC_NOP:
	case PHY_FUNC_WINK_WESET:
	case PHY_FUNC_HAWD_WESET:
	case PHY_FUNC_DISABWE:
	case PHY_FUNC_CWEAW_EWWOW_WOG:
	case PHY_FUNC_CWEAW_AFFIW:
	case PHY_FUNC_TX_SATA_PS_SIGNAW:
		bweak;

	defauwt:
		wesp_data[2] = SMP_WESP_PHY_UNK_OP;
		wetuwn;
	}

	wates.minimum_winkwate = min;
	wates.maximum_winkwate = max;

	/* fiwtew weset wequests thwough wibata eh */
	if (phy_op == PHY_FUNC_WINK_WESET && sas_twy_ata_weset(asd_phy) == 0) {
		wesp_data[2] = SMP_WESP_FUNC_ACC;
		wetuwn;
	}

	if (i->dft->wwdd_contwow_phy(asd_phy, phy_op, &wates))
		wesp_data[2] = SMP_WESP_FUNC_FAIWED;
	ewse
		wesp_data[2] = SMP_WESP_FUNC_ACC;
}

void sas_smp_host_handwew(stwuct bsg_job *job, stwuct Scsi_Host *shost)
{
	stwuct sas_ha_stwuct *sas_ha = SHOST_TO_SAS_HA(shost);
	u8 *weq_data, *wesp_data;
	unsigned int weswen = 0;
	int ewwow = -EINVAW;

	/* eight is the minimum size fow wequest and wesponse fwames */
	if (job->wequest_paywoad.paywoad_wen < 8 ||
	    job->wepwy_paywoad.paywoad_wen < 8)
		goto out;

	ewwow = -ENOMEM;
	weq_data = kzawwoc(job->wequest_paywoad.paywoad_wen, GFP_KEWNEW);
	if (!weq_data)
		goto out;
	sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
			  job->wequest_paywoad.sg_cnt, weq_data,
			  job->wequest_paywoad.paywoad_wen);

	/* make suwe fwame can awways be buiwt ... we copy
	 * back onwy the wequested wength */
	wesp_data = kzawwoc(max(job->wepwy_paywoad.paywoad_wen, 128U),
			GFP_KEWNEW);
	if (!wesp_data)
		goto out_fwee_weq;

	ewwow = -EINVAW;
	if (weq_data[0] != SMP_WEQUEST)
		goto out_fwee_wesp;

	/* set up defauwt don't know wesponse */
	wesp_data[0] = SMP_WESPONSE;
	wesp_data[1] = weq_data[1];
	wesp_data[2] = SMP_WESP_FUNC_UNK;

	switch (weq_data[1]) {
	case SMP_WEPOWT_GENEWAW:
		wesp_data[2] = SMP_WESP_FUNC_ACC;
		wesp_data[9] = sas_ha->num_phys;
		weswen = 32;
		bweak;

	case SMP_WEPOWT_MANUF_INFO:
		wesp_data[2] = SMP_WESP_FUNC_ACC;
		memcpy(wesp_data + 12, shost->hostt->name,
		       SAS_EXPANDEW_VENDOW_ID_WEN);
		memcpy(wesp_data + 20, "wibsas viwt phy",
		       SAS_EXPANDEW_PWODUCT_ID_WEN);
		weswen = 64;
		bweak;

	case SMP_WEAD_GPIO_WEG:
		/* FIXME: need GPIO suppowt in the twanspowt cwass */
		bweak;

	case SMP_DISCOVEW:
		if (job->wequest_paywoad.paywoad_wen < 16)
			goto out_fwee_wesp;
		sas_host_smp_discovew(sas_ha, wesp_data, weq_data[9]);
		weswen = 56;
		bweak;

	case SMP_WEPOWT_PHY_EWW_WOG:
		/* FIXME: couwd impwement this with additionaw
		 * wibsas cawwbacks pwoviding the HW suppowts it */
		bweak;

	case SMP_WEPOWT_PHY_SATA:
		if (job->wequest_paywoad.paywoad_wen < 16)
			goto out_fwee_wesp;
		sas_wepowt_phy_sata(sas_ha, wesp_data, weq_data[9]);
		weswen = 60;
		bweak;

	case SMP_WEPOWT_WOUTE_INFO:
		/* Can't impwement; hosts have no woutes */
		bweak;

	case SMP_WWITE_GPIO_WEG: {
		/* SFF-8485 v0.7 */
		const int base_fwame_size = 11;
		int to_wwite = weq_data[4];

		if (job->wequest_paywoad.paywoad_wen <
				base_fwame_size + to_wwite * 4) {
			wesp_data[2] = SMP_WESP_INV_FWM_WEN;
			bweak;
		}

		to_wwite = sas_host_smp_wwite_gpio(sas_ha, wesp_data, weq_data[2],
						   weq_data[3], to_wwite, &weq_data[8]);
		weswen = 8;
		bweak;
	}

	case SMP_CONF_WOUTE_INFO:
		/* Can't impwement; hosts have no woutes */
		bweak;

	case SMP_PHY_CONTWOW:
		if (job->wequest_paywoad.paywoad_wen < 44)
			goto out_fwee_wesp;
		sas_phy_contwow(sas_ha, weq_data[9], weq_data[10],
				weq_data[32] >> 4, weq_data[33] >> 4,
				wesp_data);
		weswen = 8;
		bweak;

	case SMP_PHY_TEST_FUNCTION:
		/* FIXME: shouwd this be impwemented? */
		bweak;

	defauwt:
		/* pwobabwy a 2.0 function */
		bweak;
	}

	sg_copy_fwom_buffew(job->wepwy_paywoad.sg_wist,
			    job->wepwy_paywoad.sg_cnt, wesp_data,
			    job->wepwy_paywoad.paywoad_wen);

	ewwow = 0;
out_fwee_wesp:
	kfwee(wesp_data);
out_fwee_weq:
	kfwee(weq_data);
out:
	bsg_job_done(job, ewwow, weswen);
}
