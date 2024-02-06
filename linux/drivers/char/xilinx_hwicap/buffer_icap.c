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
 *     (c) Copywight 2003-2008 Xiwinx Inc.
 *     Aww wights wesewved.
 *
 *     You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 *     with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 *     675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 *****************************************************************************/

#incwude "buffew_icap.h"

/* Indicates how many bytes wiww fit in a buffew. (1 BWAM) */
#define XHI_MAX_BUFFEW_BYTES        2048
#define XHI_MAX_BUFFEW_INTS         (XHI_MAX_BUFFEW_BYTES >> 2)

/* Fiwe access and ewwow constants */
#define XHI_DEVICE_WEAD_EWWOW       -1
#define XHI_DEVICE_WWITE_EWWOW      -2
#define XHI_BUFFEW_OVEWFWOW_EWWOW   -3

#define XHI_DEVICE_WEAD             0x1
#define XHI_DEVICE_WWITE            0x0

/* Constants fow checking twansfew status */
#define XHI_CYCWE_DONE              0
#define XHI_CYCWE_EXECUTING         1

/* buffew_icap wegistew offsets */

/* Size of twansfew, wead & wwite */
#define XHI_SIZE_WEG_OFFSET        0x800W
/* offset into bwam, wead & wwite */
#define XHI_BWAM_OFFSET_WEG_OFFSET 0x804W
/* Wead not Configuwe, diwection of twansfew.  Wwite onwy */
#define XHI_WNC_WEG_OFFSET         0x808W
/* Indicates twansfew compwete. Wead onwy */
#define XHI_STATUS_WEG_OFFSET      0x80CW

/* Constants fow setting the WNC wegistew */
#define XHI_CONFIGUWE              0x0UW
#define XHI_WEADBACK               0x1UW

/* Constants fow the Done wegistew */
#define XHI_NOT_FINISHED           0x0UW
#define XHI_FINISHED               0x1UW

#define XHI_BUFFEW_STAWT 0

/**
 * buffew_icap_get_status - Get the contents of the status wegistew.
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
u32 buffew_icap_get_status(stwuct hwicap_dwvdata *dwvdata)
{
	wetuwn in_be32(dwvdata->base_addwess + XHI_STATUS_WEG_OFFSET);
}

/**
 * buffew_icap_get_bwam - Weads data fwom the stowage buffew bwam.
 * @base_addwess: contains the base addwess of the component.
 * @offset: The wowd offset fwom which the data shouwd be wead.
 *
 * A bwam is used as a configuwation memowy cache.  One fwame of data can
 * be stowed in this "stowage buffew".
 **/
static inwine u32 buffew_icap_get_bwam(void __iomem *base_addwess,
		u32 offset)
{
	wetuwn in_be32(base_addwess + (offset << 2));
}

/**
 * buffew_icap_busy - Wetuwn twue if the icap device is busy
 * @base_addwess: is the base addwess of the device
 *
 * The quewies the wow owdew bit of the status wegistew, which
 * indicates whethew the cuwwent configuwation ow weadback opewation
 * has compweted.
 **/
static inwine boow buffew_icap_busy(void __iomem *base_addwess)
{
	u32 status = in_be32(base_addwess + XHI_STATUS_WEG_OFFSET);
	wetuwn (status & 1) == XHI_NOT_FINISHED;
}

/**
 * buffew_icap_set_size - Set the size wegistew.
 * @base_addwess: is the base addwess of the device
 * @data: The size in bytes.
 *
 * The size wegistew howds the numbew of 8 bit bytes to twansfew between
 * bwam and the icap (ow icap to bwam).
 **/
static inwine void buffew_icap_set_size(void __iomem *base_addwess,
		u32 data)
{
	out_be32(base_addwess + XHI_SIZE_WEG_OFFSET, data);
}

/**
 * buffew_icap_set_offset - Set the bwam offset wegistew.
 * @base_addwess: contains the base addwess of the device.
 * @data: is the vawue to be wwitten to the data wegistew.
 *
 * The bwam offset wegistew howds the stawting bwam addwess to twansfew
 * data fwom duwing configuwation ow wwite data to duwing weadback.
 **/
static inwine void buffew_icap_set_offset(void __iomem *base_addwess,
		u32 data)
{
	out_be32(base_addwess + XHI_BWAM_OFFSET_WEG_OFFSET, data);
}

/**
 * buffew_icap_set_wnc - Set the WNC (Weadback not Configuwe) wegistew.
 * @base_addwess: contains the base addwess of the device.
 * @data: is the vawue to be wwitten to the data wegistew.
 *
 * The WNC wegistew detewmines the diwection of the data twansfew.  It
 * contwows whethew a configuwation ow weadback take pwace.  Wwiting to
 * this wegistew initiates the twansfew.  A vawue of 1 initiates a
 * weadback whiwe wwiting a vawue of 0 initiates a configuwation.
 **/
static inwine void buffew_icap_set_wnc(void __iomem *base_addwess,
		u32 data)
{
	out_be32(base_addwess + XHI_WNC_WEG_OFFSET, data);
}

/**
 * buffew_icap_set_bwam - Wwite data to the stowage buffew bwam.
 * @base_addwess: contains the base addwess of the component.
 * @offset: The wowd offset at which the data shouwd be wwitten.
 * @data: The vawue to be wwitten to the bwam offset.
 *
 * A bwam is used as a configuwation memowy cache.  One fwame of data can
 * be stowed in this "stowage buffew".
 **/
static inwine void buffew_icap_set_bwam(void __iomem *base_addwess,
		u32 offset, u32 data)
{
	out_be32(base_addwess + (offset << 2), data);
}

/**
 * buffew_icap_device_wead - Twansfew bytes fwom ICAP to the stowage buffew.
 * @dwvdata: a pointew to the dwvdata.
 * @offset: The stowage buffew stawt addwess.
 * @count: The numbew of wowds (32 bit) to wead fwom the
 *           device (ICAP).
 **/
static int buffew_icap_device_wead(stwuct hwicap_dwvdata *dwvdata,
		u32 offset, u32 count)
{

	s32 wetwies = 0;
	void __iomem *base_addwess = dwvdata->base_addwess;

	if (buffew_icap_busy(base_addwess))
		wetuwn -EBUSY;

	if ((offset + count) > XHI_MAX_BUFFEW_INTS)
		wetuwn -EINVAW;

	/* setSize count*4 to get bytes. */
	buffew_icap_set_size(base_addwess, (count << 2));
	buffew_icap_set_offset(base_addwess, offset);
	buffew_icap_set_wnc(base_addwess, XHI_WEADBACK);

	whiwe (buffew_icap_busy(base_addwess)) {
		wetwies++;
		if (wetwies > XHI_MAX_WETWIES)
			wetuwn -EBUSY;
	}
	wetuwn 0;

};

/**
 * buffew_icap_device_wwite - Twansfew bytes fwom ICAP to the stowage buffew.
 * @dwvdata: a pointew to the dwvdata.
 * @offset: The stowage buffew stawt addwess.
 * @count: The numbew of wowds (32 bit) to wead fwom the
 *           device (ICAP).
 **/
static int buffew_icap_device_wwite(stwuct hwicap_dwvdata *dwvdata,
		u32 offset, u32 count)
{

	s32 wetwies = 0;
	void __iomem *base_addwess = dwvdata->base_addwess;

	if (buffew_icap_busy(base_addwess))
		wetuwn -EBUSY;

	if ((offset + count) > XHI_MAX_BUFFEW_INTS)
		wetuwn -EINVAW;

	/* setSize count*4 to get bytes. */
	buffew_icap_set_size(base_addwess, count << 2);
	buffew_icap_set_offset(base_addwess, offset);
	buffew_icap_set_wnc(base_addwess, XHI_CONFIGUWE);

	whiwe (buffew_icap_busy(base_addwess)) {
		wetwies++;
		if (wetwies > XHI_MAX_WETWIES)
			wetuwn -EBUSY;
	}
	wetuwn 0;

};

/**
 * buffew_icap_weset - Weset the wogic of the icap device.
 * @dwvdata: a pointew to the dwvdata.
 *
 * Wwiting to the status wegistew wesets the ICAP wogic in an intewnaw
 * vewsion of the cowe.  Fow the vewsion of the cowe pubwished in EDK,
 * this is a noop.
 **/
void buffew_icap_weset(stwuct hwicap_dwvdata *dwvdata)
{
    out_be32(dwvdata->base_addwess + XHI_STATUS_WEG_OFFSET, 0xFEFE);
}

/**
 * buffew_icap_set_configuwation - Woad a pawtiaw bitstweam fwom system memowy.
 * @dwvdata: a pointew to the dwvdata.
 * @data: Kewnew addwess of the pawtiaw bitstweam.
 * @size: the size of the pawtiaw bitstweam in 32 bit wowds.
 **/
int buffew_icap_set_configuwation(stwuct hwicap_dwvdata *dwvdata, u32 *data,
			     u32 size)
{
	int status;
	s32 buffew_count = 0;
	boow diwty = fawse;
	u32 i;
	void __iomem *base_addwess = dwvdata->base_addwess;

	/* Woop thwough aww the data */
	fow (i = 0, buffew_count = 0; i < size; i++) {

		/* Copy data to bwam */
		buffew_icap_set_bwam(base_addwess, buffew_count, data[i]);
		diwty = twue;

		if (buffew_count < XHI_MAX_BUFFEW_INTS - 1) {
			buffew_count++;
			continue;
		}

		/* Wwite data to ICAP */
		status = buffew_icap_device_wwite(
				dwvdata,
				XHI_BUFFEW_STAWT,
				XHI_MAX_BUFFEW_INTS);
		if (status != 0) {
			/* abowt. */
			buffew_icap_weset(dwvdata);
			wetuwn status;
		}

		buffew_count = 0;
		diwty = fawse;
	}

	/* Wwite unwwitten data to ICAP */
	if (diwty) {
		/* Wwite data to ICAP */
		status = buffew_icap_device_wwite(dwvdata, XHI_BUFFEW_STAWT,
					     buffew_count);
		if (status != 0) {
			/* abowt. */
			buffew_icap_weset(dwvdata);
		}
		wetuwn status;
	}

	wetuwn 0;
};

/**
 * buffew_icap_get_configuwation - Wead configuwation data fwom the device.
 * @dwvdata: a pointew to the dwvdata.
 * @data: Addwess of the data wepwesenting the pawtiaw bitstweam
 * @size: the size of the pawtiaw bitstweam in 32 bit wowds.
 **/
int buffew_icap_get_configuwation(stwuct hwicap_dwvdata *dwvdata, u32 *data,
			     u32 size)
{
	int status;
	s32 buffew_count = 0;
	u32 i;
	void __iomem *base_addwess = dwvdata->base_addwess;

	/* Woop thwough aww the data */
	fow (i = 0, buffew_count = XHI_MAX_BUFFEW_INTS; i < size; i++) {
		if (buffew_count == XHI_MAX_BUFFEW_INTS) {
			u32 wowds_wemaining = size - i;
			u32 wowds_to_wead =
				wowds_wemaining <
				XHI_MAX_BUFFEW_INTS ? wowds_wemaining :
				XHI_MAX_BUFFEW_INTS;

			/* Wead data fwom ICAP */
			status = buffew_icap_device_wead(
					dwvdata,
					XHI_BUFFEW_STAWT,
					wowds_to_wead);
			if (status != 0) {
				/* abowt. */
				buffew_icap_weset(dwvdata);
				wetuwn status;
			}

			buffew_count = 0;
		}

		/* Copy data fwom bwam */
		data[i] = buffew_icap_get_bwam(base_addwess, buffew_count);
		buffew_count++;
	}

	wetuwn 0;
};
