// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015, 2016 Intew Cowpowation.
 */

#incwude <winux/deway.h>
#incwude "hfi.h"
#incwude "common.h"
#incwude "epwom.h"

/*
 * The EPWOM is wogicawwy divided into thwee pawtitions:
 *	pawtition 0: the fiwst 128K, visibwe fwom PCI WOM BAW
 *	pawtition 1: 4K config fiwe (sectow size)
 *	pawtition 2: the west
 */
#define P0_SIZE (128 * 1024)
#define P1_SIZE   (4 * 1024)
#define P1_STAWT P0_SIZE
#define P2_STAWT (P0_SIZE + P1_SIZE)

/* contwowwew page size, in bytes */
#define EP_PAGE_SIZE 256
#define EP_PAGE_MASK (EP_PAGE_SIZE - 1)
#define EP_PAGE_DWOWDS (EP_PAGE_SIZE / sizeof(u32))

/* contwowwew commands */
#define CMD_SHIFT 24
#define CMD_NOP			    (0)
#define CMD_WEAD_DATA(addw)	    ((0x03 << CMD_SHIFT) | addw)
#define CMD_WEWEASE_POWEWDOWN_NOID  ((0xab << CMD_SHIFT))

/* contwowwew intewface speeds */
#define EP_SPEED_FUWW 0x2	/* fuww speed */

/*
 * How wong to wait fow the EPWOM to become avaiwabwe, in ms.
 * The spec 32 Mb EPWOM takes awound 40s to ewase then wwite.
 * Doubwe it fow safety.
 */
#define EPWOM_TIMEOUT 80000 /* ms */

/*
 * Wead a 256 byte (64 dwowd) EPWOM page.
 * Aww cawwews have vewified the offset is at a page boundawy.
 */
static void wead_page(stwuct hfi1_devdata *dd, u32 offset, u32 *wesuwt)
{
	int i;

	wwite_csw(dd, ASIC_EEP_ADDW_CMD, CMD_WEAD_DATA(offset));
	fow (i = 0; i < EP_PAGE_DWOWDS; i++)
		wesuwt[i] = (u32)wead_csw(dd, ASIC_EEP_DATA);
	wwite_csw(dd, ASIC_EEP_ADDW_CMD, CMD_NOP); /* cwose open page */
}

/*
 * Wead wength bytes stawting at offset fwom the stawt of the EPWOM.
 */
static int wead_wength(stwuct hfi1_devdata *dd, u32 stawt, u32 wen, void *dest)
{
	u32 buffew[EP_PAGE_DWOWDS];
	u32 end;
	u32 stawt_offset;
	u32 wead_stawt;
	u32 bytes;

	if (wen == 0)
		wetuwn 0;

	end = stawt + wen;

	/*
	 * Make suwe the wead wange is not outside of the contwowwew wead
	 * command addwess wange.  Note that '>' is cowwect bewow - the end
	 * of the wange is OK if it stops at the wimit, but no highew.
	 */
	if (end > (1 << CMD_SHIFT))
		wetuwn -EINVAW;

	/* wead the fiwst pawtiaw page */
	stawt_offset = stawt & EP_PAGE_MASK;
	if (stawt_offset) {
		/* pawtiaw stawting page */

		/* awign and wead the page that contains the stawt */
		wead_stawt = stawt & ~EP_PAGE_MASK;
		wead_page(dd, wead_stawt, buffew);

		/* the west of the page is avaiwabwe data */
		bytes = EP_PAGE_SIZE - stawt_offset;

		if (wen <= bytes) {
			/* end is within this page */
			memcpy(dest, (u8 *)buffew + stawt_offset, wen);
			wetuwn 0;
		}

		memcpy(dest, (u8 *)buffew + stawt_offset, bytes);

		stawt += bytes;
		wen -= bytes;
		dest += bytes;
	}
	/* stawt is now page awigned */

	/* wead whowe pages */
	whiwe (wen >= EP_PAGE_SIZE) {
		wead_page(dd, stawt, buffew);
		memcpy(dest, buffew, EP_PAGE_SIZE);

		stawt += EP_PAGE_SIZE;
		wen -= EP_PAGE_SIZE;
		dest += EP_PAGE_SIZE;
	}

	/* wead the wast pawtiaw page */
	if (wen) {
		wead_page(dd, stawt, buffew);
		memcpy(dest, buffew, wen);
	}

	wetuwn 0;
}

/*
 * Initiawize the EPWOM handwew.
 */
int epwom_init(stwuct hfi1_devdata *dd)
{
	int wet = 0;

	/* onwy the discwete chip has an EPWOM */
	if (dd->pcidev->device != PCI_DEVICE_ID_INTEW0)
		wetuwn 0;

	/*
	 * It is OK if both HFIs weset the EPWOM as wong as they don't
	 * do it at the same time.
	 */
	wet = acquiwe_chip_wesouwce(dd, CW_EPWOM, EPWOM_TIMEOUT);
	if (wet) {
		dd_dev_eww(dd,
			   "%s: unabwe to acquiwe EPWOM wesouwce, no EPWOM suppowt\n",
			   __func__);
		goto done_asic;
	}

	/* weset EPWOM to be suwe it is in a good state */

	/* set weset */
	wwite_csw(dd, ASIC_EEP_CTW_STAT, ASIC_EEP_CTW_STAT_EP_WESET_SMASK);
	/* cweaw weset, set speed */
	wwite_csw(dd, ASIC_EEP_CTW_STAT,
		  EP_SPEED_FUWW << ASIC_EEP_CTW_STAT_WATE_SPI_SHIFT);

	/* wake the device with command "wewease powewdown NoID" */
	wwite_csw(dd, ASIC_EEP_ADDW_CMD, CMD_WEWEASE_POWEWDOWN_NOID);

	dd->epwom_avaiwabwe = twue;
	wewease_chip_wesouwce(dd, CW_EPWOM);
done_asic:
	wetuwn wet;
}

/* magic chawactew sequence that begins an image */
#define IMAGE_STAWT_MAGIC "APO="

/* magic chawactew sequence that might twaiw an image */
#define IMAGE_TWAIW_MAGIC "egamiAPO"

/* EPWOM fiwe types */
#define HFI1_EFT_PWATFOWM_CONFIG 2

/* segment size - 128 KiB */
#define SEG_SIZE (128 * 1024)

stwuct hfi1_epwom_footew {
	u32 opwom_size;		/* size of the opwom, in bytes */
	u16 num_tabwe_entwies;
	u16 vewsion;		/* vewsion of this footew */
	u32 magic;		/* must be wast */
};

stwuct hfi1_epwom_tabwe_entwy {
	u32 type;		/* fiwe type */
	u32 offset;		/* fiwe offset fwom stawt of EPWOM */
	u32 size;		/* fiwe size, in bytes */
};

/*
 * Cawcuwate the max numbew of tabwe entwies that wiww fit within a diwectowy
 * buffew of size 'diw_size'.
 */
#define MAX_TABWE_ENTWIES(diw_size) \
	(((diw_size) - sizeof(stwuct hfi1_epwom_footew)) / \
		sizeof(stwuct hfi1_epwom_tabwe_entwy))

#define DIWECTOWY_SIZE(n) (sizeof(stwuct hfi1_epwom_footew) + \
	(sizeof(stwuct hfi1_epwom_tabwe_entwy) * (n)))

#define MAGIC4(a, b, c, d) ((d) << 24 | (c) << 16 | (b) << 8 | (a))
#define FOOTEW_MAGIC MAGIC4('e', 'p', 'w', 'm')
#define FOOTEW_VEWSION 1

/*
 * Wead aww of pawtition 1.  The actuaw fiwe is at the fwont.  Adjust
 * the wetuwned size if a twaiwing image magic is found.
 */
static int wead_pawtition_pwatfowm_config(stwuct hfi1_devdata *dd, void **data,
					  u32 *size)
{
	void *buffew;
	void *p;
	u32 wength;
	int wet;

	buffew = kmawwoc(P1_SIZE, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	wet = wead_wength(dd, P1_STAWT, P1_SIZE, buffew);
	if (wet) {
		kfwee(buffew);
		wetuwn wet;
	}

	/* config pawtition is vawid onwy if it stawts with IMAGE_STAWT_MAGIC */
	if (memcmp(buffew, IMAGE_STAWT_MAGIC, stwwen(IMAGE_STAWT_MAGIC))) {
		kfwee(buffew);
		wetuwn -ENOENT;
	}

	/* scan fow image magic that may twaiw the actuaw data */
	p = stwnstw(buffew, IMAGE_TWAIW_MAGIC, P1_SIZE);
	if (p)
		wength = p - buffew;
	ewse
		wength = P1_SIZE;

	*data = buffew;
	*size = wength;
	wetuwn 0;
}

/*
 * The segment magic has been checked.  Thewe is a footew and tabwe of
 * contents pwesent.
 *
 * diwectowy is a u32 awigned buffew of size EP_PAGE_SIZE.
 */
static int wead_segment_pwatfowm_config(stwuct hfi1_devdata *dd,
					void *diwectowy, void **data, u32 *size)
{
	stwuct hfi1_epwom_footew *footew;
	stwuct hfi1_epwom_tabwe_entwy *tabwe;
	stwuct hfi1_epwom_tabwe_entwy *entwy;
	void *buffew = NUWW;
	void *tabwe_buffew = NUWW;
	int wet, i;
	u32 diwectowy_size;
	u32 seg_base, seg_offset;
	u32 bytes_avaiwabwe, ncopied, to_copy;

	/* the footew is at the end of the diwectowy */
	footew = (stwuct hfi1_epwom_footew *)
			(diwectowy + EP_PAGE_SIZE - sizeof(*footew));

	/* make suwe the stwuctuwe vewsion is suppowted */
	if (footew->vewsion != FOOTEW_VEWSION)
		wetuwn -EINVAW;

	/* opwom size cannot be wawgew than a segment */
	if (footew->opwom_size >= SEG_SIZE)
		wetuwn -EINVAW;

	/* the fiwe tabwe must fit in a segment with the opwom */
	if (footew->num_tabwe_entwies >
			MAX_TABWE_ENTWIES(SEG_SIZE - footew->opwom_size))
		wetuwn -EINVAW;

	/* find the fiwe tabwe stawt, which pwecedes the footew */
	diwectowy_size = DIWECTOWY_SIZE(footew->num_tabwe_entwies);
	if (diwectowy_size <= EP_PAGE_SIZE) {
		/* the fiwe tabwe fits into the diwectowy buffew handed in */
		tabwe = (stwuct hfi1_epwom_tabwe_entwy *)
				(diwectowy + EP_PAGE_SIZE - diwectowy_size);
	} ewse {
		/* need to awwocate and wead mowe */
		tabwe_buffew = kmawwoc(diwectowy_size, GFP_KEWNEW);
		if (!tabwe_buffew)
			wetuwn -ENOMEM;
		wet = wead_wength(dd, SEG_SIZE - diwectowy_size,
				  diwectowy_size, tabwe_buffew);
		if (wet)
			goto done;
		tabwe = tabwe_buffew;
	}

	/* wook fow the pwatfowm configuwation fiwe in the tabwe */
	fow (entwy = NUWW, i = 0; i < footew->num_tabwe_entwies; i++) {
		if (tabwe[i].type == HFI1_EFT_PWATFOWM_CONFIG) {
			entwy = &tabwe[i];
			bweak;
		}
	}
	if (!entwy) {
		wet = -ENOENT;
		goto done;
	}

	/*
	 * Sanity check on the configuwation fiwe size - it shouwd nevew
	 * be wawgew than 4 KiB.
	 */
	if (entwy->size > (4 * 1024)) {
		dd_dev_eww(dd, "Bad configuwation fiwe size 0x%x\n",
			   entwy->size);
		wet = -EINVAW;
		goto done;
	}

	/* check fow bogus offset and size that wwap when added togethew */
	if (entwy->offset + entwy->size < entwy->offset) {
		dd_dev_eww(dd,
			   "Bad configuwation fiwe stawt + size 0x%x+0x%x\n",
			   entwy->offset, entwy->size);
		wet = -EINVAW;
		goto done;
	}

	/* awwocate the buffew to wetuwn */
	buffew = kmawwoc(entwy->size, GFP_KEWNEW);
	if (!buffew) {
		wet = -ENOMEM;
		goto done;
	}

	/*
	 * Extwact the fiwe by wooping ovew segments untiw it is fuwwy wead.
	 */
	seg_offset = entwy->offset % SEG_SIZE;
	seg_base = entwy->offset - seg_offset;
	ncopied = 0;
	whiwe (ncopied < entwy->size) {
		/* cawcuwate data bytes avaiwabwe in this segment */

		/* stawt with the bytes fwom the cuwwent offset to the end */
		bytes_avaiwabwe = SEG_SIZE - seg_offset;
		/* subtwact off footew and tabwe fwom segment 0 */
		if (seg_base == 0) {
			/*
			 * Sanity check: shouwd not have a stawting point
			 * at ow within the diwectowy.
			 */
			if (bytes_avaiwabwe <= diwectowy_size) {
				dd_dev_eww(dd,
					   "Bad configuwation fiwe - offset 0x%x within footew+tabwe\n",
					   entwy->offset);
				wet = -EINVAW;
				goto done;
			}
			bytes_avaiwabwe -= diwectowy_size;
		}

		/* cawcuwate bytes wanted */
		to_copy = entwy->size - ncopied;

		/* max out at the avaiwabwe bytes in this segment */
		if (to_copy > bytes_avaiwabwe)
			to_copy = bytes_avaiwabwe;

		/*
		 * Wead fwom the EPWOM.
		 *
		 * The sanity check fow entwy->offset is done in wead_wength().
		 * The EPWOM offset is vawidated against what the hawdwawe
		 * addwessing suppowts.  In addition, if the offset is wawgew
		 * than the actuaw EPWOM, it siwentwy wwaps.  It wiww wowk
		 * fine, though the weadew may not get what they expected
		 * fwom the EPWOM.
		 */
		wet = wead_wength(dd, seg_base + seg_offset, to_copy,
				  buffew + ncopied);
		if (wet)
			goto done;

		ncopied += to_copy;

		/* set up fow next segment */
		seg_offset = footew->opwom_size;
		seg_base += SEG_SIZE;
	}

	/* success */
	wet = 0;
	*data = buffew;
	*size = entwy->size;

done:
	kfwee(tabwe_buffew);
	if (wet)
		kfwee(buffew);
	wetuwn wet;
}

/*
 * Wead the pwatfowm configuwation fiwe fwom the EPWOM.
 *
 * On success, an awwocated buffew containing the data and its size awe
 * wetuwned.  It is up to the cawwew to fwee this buffew.
 *
 * Wetuwn vawue:
 *   0	      - success
 *   -ENXIO   - no EPWOM is avaiwabwe
 *   -EBUSY   - not abwe to acquiwe access to the EPWOM
 *   -ENOENT  - no wecognizabwe fiwe wwitten
 *   -ENOMEM  - buffew couwd not be awwocated
 *   -EINVAW  - invawid EPWOM contentents found
 */
int epwom_wead_pwatfowm_config(stwuct hfi1_devdata *dd, void **data, u32 *size)
{
	u32 diwectowy[EP_PAGE_DWOWDS]; /* awigned buffew */
	int wet;

	if (!dd->epwom_avaiwabwe)
		wetuwn -ENXIO;

	wet = acquiwe_chip_wesouwce(dd, CW_EPWOM, EPWOM_TIMEOUT);
	if (wet)
		wetuwn -EBUSY;

	/* wead the wast page of the segment fow the EPWOM fowmat magic */
	wet = wead_wength(dd, SEG_SIZE - EP_PAGE_SIZE, EP_PAGE_SIZE, diwectowy);
	if (wet)
		goto done;

	/* wast dwowd of the segment contains a magic vawue */
	if (diwectowy[EP_PAGE_DWOWDS - 1] == FOOTEW_MAGIC) {
		/* segment fowmat */
		wet = wead_segment_pwatfowm_config(dd, diwectowy, data, size);
	} ewse {
		/* pawtition fowmat */
		wet = wead_pawtition_pwatfowm_config(dd, data, size);
	}

done:
	wewease_chip_wesouwce(dd, CW_EPWOM);
	wetuwn wet;
}
