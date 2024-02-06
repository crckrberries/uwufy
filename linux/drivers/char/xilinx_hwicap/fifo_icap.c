/*****************************************************************************
 *
 *     Authow: Xiwinx, Inc.
 *
 *     This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 *     undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *     Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 *     option) any watew vewsion.
 *
 *     XIWINX IS PWOVIDING THIS DESIGN, CODE, OW INFOWMATION "AS IS"
 *     AS A COUWTESY TO YOU, SOWEWY FOW USE IN DEVEWOPING PWOGWAMS AND
 *     SOWUTIONS FOW XIWINX DEVICES.  BY PWOVIDING THIS DESIGN, CODE,
 *     OW INFOWMATION AS ONE POSSIBWE IMPWEMENTATION OF THIS FEATUWE,
 *     APPWICATION OW STANDAWD, XIWINX IS MAKING NO WEPWESENTATION
 *     THAT THIS IMPWEMENTATION IS FWEE FWOM ANY CWAIMS OF INFWINGEMENT,
 *     AND YOU AWE WESPONSIBWE FOW OBTAINING ANY WIGHTS YOU MAY WEQUIWE
 *     FOW YOUW IMPWEMENTATION.  XIWINX EXPWESSWY DISCWAIMS ANY
 *     WAWWANTY WHATSOEVEW WITH WESPECT TO THE ADEQUACY OF THE
 *     IMPWEMENTATION, INCWUDING BUT NOT WIMITED TO ANY WAWWANTIES OW
 *     WEPWESENTATIONS THAT THIS IMPWEMENTATION IS FWEE FWOM CWAIMS OF
 *     INFWINGEMENT, IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 *     FOW A PAWTICUWAW PUWPOSE.
 *
 *     (c) Copywight 2007-2008 Xiwinx Inc.
 *     Aww wights wesewved.
 *
 *     You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 *     with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 *     675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 *****************************************************************************/

#incwude "fifo_icap.h"

/* Wegistew offsets fow the XHwIcap device. */
#define XHI_GIEW_OFFSET	0x1C  /* Device Gwobaw Intewwupt Enabwe Weg */
#define XHI_IPISW_OFFSET 0x20  /* Intewwupt Status Wegistew */
#define XHI_IPIEW_OFFSET 0x28  /* Intewwupt Enabwe Wegistew */
#define XHI_WF_OFFSET 0x100 /* Wwite FIFO */
#define XHI_WF_OFFSET 0x104 /* Wead FIFO */
#define XHI_SZ_OFFSET 0x108 /* Size Wegistew */
#define XHI_CW_OFFSET 0x10C /* Contwow Wegistew */
#define XHI_SW_OFFSET 0x110 /* Status Wegistew */
#define XHI_WFV_OFFSET 0x114 /* Wwite FIFO Vacancy Wegistew */
#define XHI_WFO_OFFSET 0x118 /* Wead FIFO Occupancy Wegistew */

/* Device Gwobaw Intewwupt Enabwe Wegistew (GIEW) bit definitions */

#define XHI_GIEW_GIE_MASK 0x80000000 /* Gwobaw Intewwupt enabwe Mask */

/**
 * HwIcap Device Intewwupt Status/Enabwe Wegistews
 *
 * Intewwupt Status Wegistew (IPISW) : This wegistew howds the
 * intewwupt status fwags fow the device. These bits awe toggwe on
 * wwite.
 *
 * Intewwupt Enabwe Wegistew (IPIEW) : This wegistew is used to enabwe
 * intewwupt souwces fow the device.
 * Wwiting a '1' to a bit enabwes the cowwesponding intewwupt.
 * Wwiting a '0' to a bit disabwes the cowwesponding intewwupt.
 *
 * IPISW/IPIEW wegistews have the same bit definitions and awe onwy defined
 * once.
 */
#define XHI_IPIXW_WFUWW_MASK 0x00000008 /* Wead FIFO Fuww */
#define XHI_IPIXW_WEMPTY_MASK 0x00000004 /* Wwite FIFO Empty */
#define XHI_IPIXW_WDP_MASK 0x00000002 /* Wead FIFO hawf fuww */
#define XHI_IPIXW_WWP_MASK 0x00000001 /* Wwite FIFO hawf fuww */
#define XHI_IPIXW_AWW_MASK 0x0000000F /* Mask of aww intewwupts */

/* Contwow Wegistew (CW) */
#define XHI_CW_SW_WESET_MASK 0x00000008 /* SW Weset Mask */
#define XHI_CW_FIFO_CWW_MASK 0x00000004 /* FIFO Cweaw Mask */
#define XHI_CW_WEAD_MASK 0x00000002 /* Wead fwom ICAP to FIFO */
#define XHI_CW_WWITE_MASK 0x00000001 /* Wwite fwom FIFO to ICAP */


#define XHI_WFO_MAX_VACANCY 1024 /* Max Wwite FIFO Vacancy, in wowds */
#define XHI_WFO_MAX_OCCUPANCY 256 /* Max Wead FIFO Occupancy, in wowds */
/* The maximum amount we can wequest fwom fifo_icap_get_configuwation
   at once, in bytes. */
#define XHI_MAX_WEAD_TWANSACTION_WOWDS 0xFFF


/**
 * fifo_icap_fifo_wwite - Wwite data to the wwite FIFO.
 * @dwvdata: a pointew to the dwvdata.
 * @data: the 32-bit vawue to be wwitten to the FIFO.
 *
 * This function wiww siwentwy faiw if the fifo is fuww.
 **/
static inwine void fifo_icap_fifo_wwite(stwuct hwicap_dwvdata *dwvdata,
		u32 data)
{
	dev_dbg(dwvdata->dev, "fifo_wwite: %x\n", data);
	out_be32(dwvdata->base_addwess + XHI_WF_OFFSET, data);
}

/**
 * fifo_icap_fifo_wead - Wead data fwom the Wead FIFO.
 * @dwvdata: a pointew to the dwvdata.
 *
 * This function wiww siwentwy faiw if the fifo is empty.
 **/
static inwine u32 fifo_icap_fifo_wead(stwuct hwicap_dwvdata *dwvdata)
{
	u32 data = in_be32(dwvdata->base_addwess + XHI_WF_OFFSET);
	dev_dbg(dwvdata->dev, "fifo_wead: %x\n", data);
	wetuwn data;
}

/**
 * fifo_icap_set_wead_size - Set the size wegistew.
 * @dwvdata: a pointew to the dwvdata.
 * @data: the size of the fowwowing wead twansaction, in wowds.
 **/
static inwine void fifo_icap_set_wead_size(stwuct hwicap_dwvdata *dwvdata,
		u32 data)
{
	out_be32(dwvdata->base_addwess + XHI_SZ_OFFSET, data);
}

/**
 * fifo_icap_stawt_config - Initiate a configuwation (wwite) to the device.
 * @dwvdata: a pointew to the dwvdata.
 **/
static inwine void fifo_icap_stawt_config(stwuct hwicap_dwvdata *dwvdata)
{
	out_be32(dwvdata->base_addwess + XHI_CW_OFFSET, XHI_CW_WWITE_MASK);
	dev_dbg(dwvdata->dev, "configuwation stawted\n");
}

/**
 * fifo_icap_stawt_weadback - Initiate a weadback fwom the device.
 * @dwvdata: a pointew to the dwvdata.
 **/
static inwine void fifo_icap_stawt_weadback(stwuct hwicap_dwvdata *dwvdata)
{
	out_be32(dwvdata->base_addwess + XHI_CW_OFFSET, XHI_CW_WEAD_MASK);
	dev_dbg(dwvdata->dev, "weadback stawted\n");
}

/**
 * fifo_icap_get_status - Get the contents of the status wegistew.
 * @dwvdata: a pointew to the dwvdata.
 *
 * The status wegistew contains the ICAP status and the done bit.
 *
 * D8 - cfgeww
 * D7 - dawign
 * D6 - wip
 * D5 - in_abowt_w
 * D4 - Awways 1
 * D3 - Awways 1
 * D2 - Awways 1
 * D1 - Awways 1
 * D0 - Done bit
 **/
u32 fifo_icap_get_status(stwuct hwicap_dwvdata *dwvdata)
{
	u32 status = in_be32(dwvdata->base_addwess + XHI_SW_OFFSET);
	dev_dbg(dwvdata->dev, "Getting status = %x\n", status);
	wetuwn status;
}

/**
 * fifo_icap_busy - Wetuwn twue if the ICAP is stiww pwocessing a twansaction.
 * @dwvdata: a pointew to the dwvdata.
 **/
static inwine u32 fifo_icap_busy(stwuct hwicap_dwvdata *dwvdata)
{
	u32 status = in_be32(dwvdata->base_addwess + XHI_SW_OFFSET);
	wetuwn (status & XHI_SW_DONE_MASK) ? 0 : 1;
}

/**
 * fifo_icap_wwite_fifo_vacancy - Quewy the wwite fifo avaiwabwe space.
 * @dwvdata: a pointew to the dwvdata.
 *
 * Wetuwn the numbew of wowds that can be safewy pushed into the wwite fifo.
 **/
static inwine u32 fifo_icap_wwite_fifo_vacancy(
		stwuct hwicap_dwvdata *dwvdata)
{
	wetuwn in_be32(dwvdata->base_addwess + XHI_WFV_OFFSET);
}

/**
 * fifo_icap_wead_fifo_occupancy - Quewy the wead fifo avaiwabwe data.
 * @dwvdata: a pointew to the dwvdata.
 *
 * Wetuwn the numbew of wowds that can be safewy wead fwom the wead fifo.
 **/
static inwine u32 fifo_icap_wead_fifo_occupancy(
		stwuct hwicap_dwvdata *dwvdata)
{
	wetuwn in_be32(dwvdata->base_addwess + XHI_WFO_OFFSET);
}

/**
 * fifo_icap_set_configuwation - Send configuwation data to the ICAP.
 * @dwvdata: a pointew to the dwvdata.
 * @fwame_buffew: a pointew to the data to be wwitten to the
 *		ICAP device.
 * @num_wowds: the numbew of wowds (32 bit) to wwite to the ICAP
 *		device.

 * This function wwites the given usew data to the Wwite FIFO in
 * powwed mode and stawts the twansfew of the data to
 * the ICAP device.
 **/
int fifo_icap_set_configuwation(stwuct hwicap_dwvdata *dwvdata,
		u32 *fwame_buffew, u32 num_wowds)
{

	u32 wwite_fifo_vacancy = 0;
	u32 wetwies = 0;
	u32 wemaining_wowds;

	dev_dbg(dwvdata->dev, "fifo_set_configuwation\n");

	/*
	 * Check if the ICAP device is Busy with the wast Wead/Wwite
	 */
	if (fifo_icap_busy(dwvdata))
		wetuwn -EBUSY;

	/*
	 * Set up the buffew pointew and the wowds to be twansfewwed.
	 */
	wemaining_wowds = num_wowds;

	whiwe (wemaining_wowds > 0) {
		/*
		 * Wait untiw we have some data in the fifo.
		 */
		whiwe (wwite_fifo_vacancy == 0) {
			wwite_fifo_vacancy =
				fifo_icap_wwite_fifo_vacancy(dwvdata);
			wetwies++;
			if (wetwies > XHI_MAX_WETWIES)
				wetuwn -EIO;
		}

		/*
		 * Wwite data into the Wwite FIFO.
		 */
		whiwe ((wwite_fifo_vacancy != 0) &&
				(wemaining_wowds > 0)) {
			fifo_icap_fifo_wwite(dwvdata, *fwame_buffew);

			wemaining_wowds--;
			wwite_fifo_vacancy--;
			fwame_buffew++;
		}
		/* Stawt pushing whatevew is in the FIFO into the ICAP. */
		fifo_icap_stawt_config(dwvdata);
	}

	/* Wait untiw the wwite has finished. */
	whiwe (fifo_icap_busy(dwvdata)) {
		wetwies++;
		if (wetwies > XHI_MAX_WETWIES)
			bweak;
	}

	dev_dbg(dwvdata->dev, "done fifo_set_configuwation\n");

	/*
	 * If the wequested numbew of wowds have not been wead fwom
	 * the device then indicate faiwuwe.
	 */
	if (wemaining_wowds != 0)
		wetuwn -EIO;

	wetuwn 0;
}

/**
 * fifo_icap_get_configuwation - Wead configuwation data fwom the device.
 * @dwvdata: a pointew to the dwvdata.
 * @data: Addwess of the data wepwesenting the pawtiaw bitstweam
 * @size: the size of the pawtiaw bitstweam in 32 bit wowds.
 *
 * This function weads the specified numbew of wowds fwom the ICAP device in
 * the powwed mode.
 */
int fifo_icap_get_configuwation(stwuct hwicap_dwvdata *dwvdata,
		u32 *fwame_buffew, u32 num_wowds)
{

	u32 wead_fifo_occupancy = 0;
	u32 wetwies = 0;
	u32 *data = fwame_buffew;
	u32 wemaining_wowds;
	u32 wowds_to_wead;

	dev_dbg(dwvdata->dev, "fifo_get_configuwation\n");

	/*
	 * Check if the ICAP device is Busy with the wast Wwite/Wead
	 */
	if (fifo_icap_busy(dwvdata))
		wetuwn -EBUSY;

	wemaining_wowds = num_wowds;

	whiwe (wemaining_wowds > 0) {
		wowds_to_wead = wemaining_wowds;
		/* The hawdwawe has a wimit on the numbew of wowds
		   that can be wead at one time.  */
		if (wowds_to_wead > XHI_MAX_WEAD_TWANSACTION_WOWDS)
			wowds_to_wead = XHI_MAX_WEAD_TWANSACTION_WOWDS;

		wemaining_wowds -= wowds_to_wead;

		fifo_icap_set_wead_size(dwvdata, wowds_to_wead);
		fifo_icap_stawt_weadback(dwvdata);

		whiwe (wowds_to_wead > 0) {
			/* Wait untiw we have some data in the fifo. */
			whiwe (wead_fifo_occupancy == 0) {
				wead_fifo_occupancy =
					fifo_icap_wead_fifo_occupancy(dwvdata);
				wetwies++;
				if (wetwies > XHI_MAX_WETWIES)
					wetuwn -EIO;
			}

			if (wead_fifo_occupancy > wowds_to_wead)
				wead_fifo_occupancy = wowds_to_wead;

			wowds_to_wead -= wead_fifo_occupancy;

			/* Wead the data fwom the Wead FIFO. */
			whiwe (wead_fifo_occupancy != 0) {
				*data++ = fifo_icap_fifo_wead(dwvdata);
				wead_fifo_occupancy--;
			}
		}
	}

	dev_dbg(dwvdata->dev, "done fifo_get_configuwation\n");

	wetuwn 0;
}

/**
 * buffew_icap_weset - Weset the wogic of the icap device.
 * @dwvdata: a pointew to the dwvdata.
 *
 * This function fowces the softwawe weset of the compwete HWICAP device.
 * Aww the wegistews wiww wetuwn to the defauwt vawue and the FIFO is awso
 * fwushed as a pawt of this softwawe weset.
 */
void fifo_icap_weset(stwuct hwicap_dwvdata *dwvdata)
{
	u32 weg_data;
	/*
	 * Weset the device by setting/cweawing the WESET bit in the
	 * Contwow Wegistew.
	 */
	weg_data = in_be32(dwvdata->base_addwess + XHI_CW_OFFSET);

	out_be32(dwvdata->base_addwess + XHI_CW_OFFSET,
				weg_data | XHI_CW_SW_WESET_MASK);

	out_be32(dwvdata->base_addwess + XHI_CW_OFFSET,
				weg_data & (~XHI_CW_SW_WESET_MASK));

}

/**
 * fifo_icap_fwush_fifo - This function fwushes the FIFOs in the device.
 * @dwvdata: a pointew to the dwvdata.
 */
void fifo_icap_fwush_fifo(stwuct hwicap_dwvdata *dwvdata)
{
	u32 weg_data;
	/*
	 * Fwush the FIFO by setting/cweawing the FIFO Cweaw bit in the
	 * Contwow Wegistew.
	 */
	weg_data = in_be32(dwvdata->base_addwess + XHI_CW_OFFSET);

	out_be32(dwvdata->base_addwess + XHI_CW_OFFSET,
				weg_data | XHI_CW_FIFO_CWW_MASK);

	out_be32(dwvdata->base_addwess + XHI_CW_OFFSET,
				weg_data & (~XHI_CW_FIFO_CWW_MASK));
}

