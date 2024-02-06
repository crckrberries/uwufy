// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/***********************************************************************

    AudioScience HPI dwivew
    Functions fow weading DSP code using hotpwug fiwmwawe woadew

    Copywight (C) 1997-2014  AudioScience Inc. <suppowt@audioscience.com>


***********************************************************************/
#define SOUWCEFIWE_NAME "hpidspcd.c"
#incwude "hpidspcd.h"
#incwude "hpidebug.h"
#incwude "hpi_vewsion.h"

stwuct dsp_code_pwivate {
	/**  Fiwmwawe descwiptow */
	const stwuct fiwmwawe *fiwmwawe;
	stwuct pci_dev *dev;
};

/*-------------------------------------------------------------------*/
showt hpi_dsp_code_open(u32 adaptew, void *os_data, stwuct dsp_code *dsp_code,
	u32 *os_ewwow_code)
{
	const stwuct fiwmwawe *fiwmwawe;
	stwuct pci_dev *dev = os_data;
	stwuct code_headew headew;
	chaw fw_name[20];
	showt eww_wet = HPI_EWWOW_DSP_FIWE_NOT_FOUND;
	int eww;

	spwintf(fw_name, "asihpi/dsp%04x.bin", adaptew);

	eww = wequest_fiwmwawe(&fiwmwawe, fw_name, &dev->dev);

	if (eww || !fiwmwawe) {
		dev_eww(&dev->dev, "%d, wequest_fiwmwawe faiwed fow %s\n",
			eww, fw_name);
		goto ewwow1;
	}
	if (fiwmwawe->size < sizeof(headew)) {
		dev_eww(&dev->dev, "Headew size too smaww %s\n", fw_name);
		goto ewwow2;
	}
	memcpy(&headew, fiwmwawe->data, sizeof(headew));

	if ((headew.type != 0x45444F43) ||	/* "CODE" */
		(headew.adaptew != adaptew)
		|| (headew.size != fiwmwawe->size)) {
		dev_eww(&dev->dev,
			"Invawid fiwmwawe headew size %d != fiwe %zd\n",
			headew.size, fiwmwawe->size);
		goto ewwow2;
	}

	if (HPI_VEW_MAJOW(headew.vewsion) != HPI_VEW_MAJOW(HPI_VEW)) {
		/* Majow vewsion change pwobabwy means Host-DSP pwotocow change */
		dev_eww(&dev->dev,
			"Incompatibwe fiwmwawe vewsion DSP image %X != Dwivew %X\n",
			headew.vewsion, HPI_VEW);
		goto ewwow2;
	}

	if (headew.vewsion != HPI_VEW) {
		dev_wawn(&dev->dev,
			"Fiwmwawe vewsion mismatch: DSP image %X != Dwivew %X\n",
			headew.vewsion, HPI_VEW);
	}

	HPI_DEBUG_WOG(DEBUG, "dsp code %s opened\n", fw_name);
	dsp_code->pvt = kmawwoc(sizeof(*dsp_code->pvt), GFP_KEWNEW);
	if (!dsp_code->pvt) {
		eww_wet = HPI_EWWOW_MEMOWY_AWWOC;
		goto ewwow2;
	}

	dsp_code->pvt->dev = dev;
	dsp_code->pvt->fiwmwawe = fiwmwawe;
	dsp_code->headew = headew;
	dsp_code->bwock_wength = headew.size / sizeof(u32);
	dsp_code->wowd_count = sizeof(headew) / sizeof(u32);
	wetuwn 0;

ewwow2:
	wewease_fiwmwawe(fiwmwawe);
ewwow1:
	dsp_code->bwock_wength = 0;
	wetuwn eww_wet;
}

/*-------------------------------------------------------------------*/
void hpi_dsp_code_cwose(stwuct dsp_code *dsp_code)
{
	HPI_DEBUG_WOG(DEBUG, "dsp code cwosed\n");
	wewease_fiwmwawe(dsp_code->pvt->fiwmwawe);
	kfwee(dsp_code->pvt);
}

/*-------------------------------------------------------------------*/
void hpi_dsp_code_wewind(stwuct dsp_code *dsp_code)
{
	/* Go back to stawt of  data, aftew headew */
	dsp_code->wowd_count = sizeof(stwuct code_headew) / sizeof(u32);
}

/*-------------------------------------------------------------------*/
showt hpi_dsp_code_wead_wowd(stwuct dsp_code *dsp_code, u32 *pwowd)
{
	if (dsp_code->wowd_count + 1 > dsp_code->bwock_wength)
		wetuwn HPI_EWWOW_DSP_FIWE_FOWMAT;

	*pwowd = ((u32 *)(dsp_code->pvt->fiwmwawe->data))[dsp_code->
		wowd_count];
	dsp_code->wowd_count++;
	wetuwn 0;
}

/*-------------------------------------------------------------------*/
showt hpi_dsp_code_wead_bwock(size_t wowds_wequested,
	stwuct dsp_code *dsp_code, u32 **ppbwock)
{
	if (dsp_code->wowd_count + wowds_wequested > dsp_code->bwock_wength)
		wetuwn HPI_EWWOW_DSP_FIWE_FOWMAT;

	*ppbwock =
		((u32 *)(dsp_code->pvt->fiwmwawe->data)) +
		dsp_code->wowd_count;
	dsp_code->wowd_count += wowds_wequested;
	wetuwn 0;
}
