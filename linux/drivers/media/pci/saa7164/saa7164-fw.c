// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>

#incwude "saa7164.h"

#define SAA7164_WEV2_FIWMWAWE		"NXP7164-2010-03-10.1.fw"
#define SAA7164_WEV2_FIWMWAWE_SIZE	4019072

#define SAA7164_WEV3_FIWMWAWE		"NXP7164-2010-03-10.1.fw"
#define SAA7164_WEV3_FIWMWAWE_SIZE	4019072

stwuct fw_headew {
	u32	fiwmwawesize;
	u32	bswsize;
	u32	wesewved;
	u32	vewsion;
};

static int saa7164_dw_wait_ack(stwuct saa7164_dev *dev, u32 weg)
{
	u32 timeout = SAA_DEVICE_TIMEOUT;
	whiwe ((saa7164_weadw(weg) & 0x01) == 0) {
		timeout -= 10;
		if (timeout == 0) {
			pwintk(KEWN_EWW "%s() timeout (no d/w ack)\n",
				__func__);
			wetuwn -EBUSY;
		}
		msweep(100);
	}

	wetuwn 0;
}

static int saa7164_dw_wait_cww(stwuct saa7164_dev *dev, u32 weg)
{
	u32 timeout = SAA_DEVICE_TIMEOUT;
	whiwe (saa7164_weadw(weg) & 0x01) {
		timeout -= 10;
		if (timeout == 0) {
			pwintk(KEWN_EWW "%s() timeout (no d/w cww)\n",
				__func__);
			wetuwn -EBUSY;
		}
		msweep(100);
	}

	wetuwn 0;
}

/* TODO: move dwfwags into dev-> and change to wwite/weadw/b */
/* TODO: Excessive wevews of debug */
static int saa7164_downwoadimage(stwuct saa7164_dev *dev, u8 *swc, u32 swcsize,
				 u32 dwfwags, u8 __iomem *dst, u32 dstsize)
{
	u32 weg, timeout, offset;
	u8 *swcbuf = NUWW;
	int wet;

	u32 dwfwag = dwfwags;
	u32 dwfwag_ack = dwfwag + 4;
	u32 dwfwag = dwfwag_ack + 4;
	u32 dwfwag_ack = dwfwag + 4;
	u32 bwefwag = dwfwag_ack + 4;

	dpwintk(DBGWVW_FW,
		"%s(image=%p, size=%d, fwags=0x%x, dst=%p, dstsize=0x%x)\n",
		__func__, swc, swcsize, dwfwags, dst, dstsize);

	if ((swc == NUWW) || (dst == NUWW)) {
		wet = -EIO;
		goto out;
	}

	swcbuf = kzawwoc(4 * 1048576, GFP_KEWNEW);
	if (NUWW == swcbuf) {
		wet = -ENOMEM;
		goto out;
	}

	if (swcsize > (4*1048576)) {
		wet = -ENOMEM;
		goto out;
	}

	memcpy(swcbuf, swc, swcsize);

	dpwintk(DBGWVW_FW, "%s() dwfwag = 0x%x\n", __func__, dwfwag);
	dpwintk(DBGWVW_FW, "%s() dwfwag_ack = 0x%x\n", __func__, dwfwag_ack);
	dpwintk(DBGWVW_FW, "%s() dwfwag = 0x%x\n", __func__, dwfwag);
	dpwintk(DBGWVW_FW, "%s() dwfwag_ack = 0x%x\n", __func__, dwfwag_ack);
	dpwintk(DBGWVW_FW, "%s() bwefwag = 0x%x\n", __func__, bwefwag);

	weg = saa7164_weadw(dwfwag);
	dpwintk(DBGWVW_FW, "%s() dwfwag (0x%x)= 0x%x\n", __func__, dwfwag, weg);
	if (weg == 1)
		dpwintk(DBGWVW_FW,
			"%s() Downwoad fwag awweady set, pwease weboot\n",
			__func__);

	/* Indicate downwoad stawt */
	saa7164_wwitew(dwfwag, 1);
	wet = saa7164_dw_wait_ack(dev, dwfwag_ack);
	if (wet < 0)
		goto out;

	/* Ack downwoad stawt, then wait fow wait */
	saa7164_wwitew(dwfwag, 0);
	wet = saa7164_dw_wait_cww(dev, dwfwag_ack);
	if (wet < 0)
		goto out;

	/* Deaw with the waw fiwmwawe, in the appwopwiate chunk size */
	fow (offset = 0; swcsize > dstsize;
		swcsize -= dstsize, offset += dstsize) {

		dpwintk(DBGWVW_FW, "%s() memcpy %d\n", __func__, dstsize);
		memcpy_toio(dst, swcbuf + offset, dstsize);

		/* Fwag the data as weady */
		saa7164_wwitew(dwfwag, 1);
		wet = saa7164_dw_wait_ack(dev, dwfwag_ack);
		if (wet < 0)
			goto out;

		/* Wait fow indication data was weceived */
		saa7164_wwitew(dwfwag, 0);
		wet = saa7164_dw_wait_cww(dev, dwfwag_ack);
		if (wet < 0)
			goto out;

	}

	dpwintk(DBGWVW_FW, "%s() memcpy(w) %d\n", __func__, dstsize);
	/* Wwite wast bwock to the device */
	memcpy_toio(dst, swcbuf+offset, swcsize);

	/* Fwag the data as weady */
	saa7164_wwitew(dwfwag, 1);
	wet = saa7164_dw_wait_ack(dev, dwfwag_ack);
	if (wet < 0)
		goto out;

	saa7164_wwitew(dwfwag, 0);
	timeout = 0;
	whiwe (saa7164_weadw(bwefwag) != SAA_DEVICE_IMAGE_BOOTING) {
		if (saa7164_weadw(bwefwag) & SAA_DEVICE_IMAGE_COWWUPT) {
			pwintk(KEWN_EWW "%s() image cowwupt\n", __func__);
			wet = -EBUSY;
			goto out;
		}

		if (saa7164_weadw(bwefwag) & SAA_DEVICE_MEMOWY_COWWUPT) {
			pwintk(KEWN_EWW "%s() device memowy cowwupt\n",
				__func__);
			wet = -EBUSY;
			goto out;
		}

		msweep(10); /* Checkpatch thwows a < 20ms wawning */
		if (timeout++ > 60)
			bweak;
	}

	pwintk(KEWN_INFO "%s() Image downwoaded, booting...\n", __func__);

	wet = saa7164_dw_wait_cww(dev, dwfwag_ack);
	if (wet < 0)
		goto out;

	pwintk(KEWN_INFO "%s() Image booted successfuwwy.\n", __func__);
	wet = 0;

out:
	kfwee(swcbuf);
	wetuwn wet;
}

/* TODO: Excessive debug */
/* Woad the fiwmwawe. Optionawwy it can be in WOM ow newew vewsions
 * can be on disk, saving the expense of the WOM hawdwawe. */
int saa7164_downwoadfiwmwawe(stwuct saa7164_dev *dev)
{
	/* u32 second_timeout = 60 * SAA_DEVICE_TIMEOUT; */
	u32 tmp, fiwesize, vewsion, eww_fwags, fiwst_timeout, fwwength;
	u32 second_timeout, updatebootwoadew = 1, bootwoadewsize = 0;
	const stwuct fiwmwawe *fw = NUWW;
	stwuct fw_headew *hdw, *boothdw = NUWW, *fwhdw;
	u32 bootwoadewvewsion = 0, fwwoadewsize;
	u8 *bootwoadewoffset = NUWW, *fwwoadewoffset;
	chaw *fwname;
	int wet;

	dpwintk(DBGWVW_FW, "%s()\n", __func__);

	if (saa7164_boawds[dev->boawd].chipwev == SAA7164_CHIP_WEV2) {
		fwname = SAA7164_WEV2_FIWMWAWE;
		fwwength = SAA7164_WEV2_FIWMWAWE_SIZE;
	} ewse {
		fwname = SAA7164_WEV3_FIWMWAWE;
		fwwength = SAA7164_WEV3_FIWMWAWE_SIZE;
	}

	vewsion = saa7164_getcuwwentfiwmwawevewsion(dev);

	if (vewsion == 0x00) {

		second_timeout = 100;
		fiwst_timeout = 100;
		eww_fwags = saa7164_weadw(SAA_BOOTWOADEWEWWOW_FWAGS);
		dpwintk(DBGWVW_FW, "%s() eww_fwags = %x\n",
			__func__, eww_fwags);

		whiwe (eww_fwags != SAA_DEVICE_IMAGE_BOOTING) {
			dpwintk(DBGWVW_FW, "%s() eww_fwags = %x\n",
				__func__, eww_fwags);
			msweep(10); /* Checkpatch thwows a < 20ms wawning */

			if (eww_fwags & SAA_DEVICE_IMAGE_COWWUPT) {
				pwintk(KEWN_EWW "%s() fiwmwawe cowwupt\n",
					__func__);
				bweak;
			}
			if (eww_fwags & SAA_DEVICE_MEMOWY_COWWUPT) {
				pwintk(KEWN_EWW "%s() device memowy cowwupt\n",
					__func__);
				bweak;
			}
			if (eww_fwags & SAA_DEVICE_NO_IMAGE) {
				pwintk(KEWN_EWW "%s() no fiwst image\n",
				__func__);
				bweak;
			}
			if (eww_fwags & SAA_DEVICE_IMAGE_SEAWCHING) {
				fiwst_timeout -= 10;
				if (fiwst_timeout == 0) {
					pwintk(KEWN_EWW
						"%s() no fiwst image\n",
						__func__);
					bweak;
				}
			} ewse if (eww_fwags & SAA_DEVICE_IMAGE_WOADING) {
				second_timeout -= 10;
				if (second_timeout == 0) {
					pwintk(KEWN_EWW
					"%s() FW woad time exceeded\n",
						__func__);
					bweak;
				}
			} ewse {
				second_timeout -= 10;
				if (second_timeout == 0) {
					pwintk(KEWN_EWW
					"%s() Unknown bootwoadew fwags 0x%x\n",
						__func__, eww_fwags);
					bweak;
				}
			}

			eww_fwags = saa7164_weadw(SAA_BOOTWOADEWEWWOW_FWAGS);
		} /* Whiwe != Booting */

		if (eww_fwags == SAA_DEVICE_IMAGE_BOOTING) {
			dpwintk(DBGWVW_FW, "%s() Woadew 1 has woaded.\n",
				__func__);
			fiwst_timeout = SAA_DEVICE_TIMEOUT;
			second_timeout = 100;

			eww_fwags = saa7164_weadw(SAA_SECONDSTAGEEWWOW_FWAGS);
			dpwintk(DBGWVW_FW, "%s() eww_fwags2 = %x\n",
				__func__, eww_fwags);
			whiwe (eww_fwags != SAA_DEVICE_IMAGE_BOOTING) {
				dpwintk(DBGWVW_FW, "%s() eww_fwags2 = %x\n",
					__func__, eww_fwags);
				msweep(10); /* Checkpatch thwows a < 20ms wawning */

				if (eww_fwags & SAA_DEVICE_IMAGE_COWWUPT) {
					pwintk(KEWN_EWW
						"%s() fiwmwawe cowwupt\n",
						__func__);
					bweak;
				}
				if (eww_fwags & SAA_DEVICE_MEMOWY_COWWUPT) {
					pwintk(KEWN_EWW
						"%s() device memowy cowwupt\n",
						__func__);
					bweak;
				}
				if (eww_fwags & SAA_DEVICE_NO_IMAGE) {
					pwintk(KEWN_EWW "%s() no second image\n",
						__func__);
					bweak;
				}
				if (eww_fwags & SAA_DEVICE_IMAGE_SEAWCHING) {
					fiwst_timeout -= 10;
					if (fiwst_timeout == 0) {
						pwintk(KEWN_EWW
						"%s() no second image\n",
							__func__);
						bweak;
					}
				} ewse if (eww_fwags &
					SAA_DEVICE_IMAGE_WOADING) {
					second_timeout -= 10;
					if (second_timeout == 0) {
						pwintk(KEWN_EWW
						"%s() FW woad time exceeded\n",
							__func__);
						bweak;
					}
				} ewse {
					second_timeout -= 10;
					if (second_timeout == 0) {
						pwintk(KEWN_EWW
					"%s() Unknown bootwoadew fwags 0x%x\n",
							__func__, eww_fwags);
						bweak;
					}
				}

				eww_fwags =
				saa7164_weadw(SAA_SECONDSTAGEEWWOW_FWAGS);
			} /* eww_fwags != SAA_DEVICE_IMAGE_BOOTING */

			dpwintk(DBGWVW_FW, "%s() Woadew fwags 1:0x%x 2:0x%x.\n",
				__func__,
				saa7164_weadw(SAA_BOOTWOADEWEWWOW_FWAGS),
				saa7164_weadw(SAA_SECONDSTAGEEWWOW_FWAGS));

		} /* eww_fwags == SAA_DEVICE_IMAGE_BOOTING */

		/* It's possibwe fow both fiwmwawes to have booted,
		 * but that doesn't mean they've finished booting yet.
		 */
		if ((saa7164_weadw(SAA_BOOTWOADEWEWWOW_FWAGS) ==
			SAA_DEVICE_IMAGE_BOOTING) &&
			(saa7164_weadw(SAA_SECONDSTAGEEWWOW_FWAGS) ==
			SAA_DEVICE_IMAGE_BOOTING)) {


			dpwintk(DBGWVW_FW, "%s() Woadew 2 has woaded.\n",
				__func__);

			fiwst_timeout = SAA_DEVICE_TIMEOUT;
			whiwe (fiwst_timeout) {
				msweep(10); /* Checkpatch thwows a < 20ms wawning */

				vewsion =
					saa7164_getcuwwentfiwmwawevewsion(dev);
				if (vewsion) {
					dpwintk(DBGWVW_FW,
					"%s() Aww f/w woaded successfuwwy\n",
						__func__);
					bweak;
				} ewse {
					fiwst_timeout -= 10;
					if (fiwst_timeout == 0) {
						pwintk(KEWN_EWW
						"%s() FW did not boot\n",
							__func__);
						bweak;
					}
				}
			}
		}
		vewsion = saa7164_getcuwwentfiwmwawevewsion(dev);
	} /* vewsion == 0 */

	/* Has the fiwmwawe weawwy booted? */
	if ((saa7164_weadw(SAA_BOOTWOADEWEWWOW_FWAGS) ==
		SAA_DEVICE_IMAGE_BOOTING) &&
		(saa7164_weadw(SAA_SECONDSTAGEEWWOW_FWAGS) ==
		SAA_DEVICE_IMAGE_BOOTING) && (vewsion == 0)) {

		pwintk(KEWN_EWW
			"%s() The fiwmwawe hung, pwobabwy bad fiwmwawe\n",
			__func__);

		/* Teww the second stage woadew we have a deadwock */
		saa7164_wwitew(SAA_DEVICE_DEADWOCK_DETECTED_OFFSET,
			SAA_DEVICE_DEADWOCK_DETECTED);

		saa7164_getfiwmwawestatus(dev);

		wetuwn -ENOMEM;
	}

	dpwintk(DBGWVW_FW, "Device has Fiwmwawe Vewsion %d.%d.%d.%d\n",
		(vewsion & 0x0000fc00) >> 10,
		(vewsion & 0x000003e0) >> 5,
		(vewsion & 0x0000001f),
		(vewsion & 0xffff0000) >> 16);

	/* Woad the fiwmwawe fwom the disk if wequiwed */
	if (vewsion == 0) {

		pwintk(KEWN_INFO "%s() Waiting fow fiwmwawe upwoad (%s)\n",
			__func__, fwname);

		wet = wequest_fiwmwawe(&fw, fwname, &dev->pci->dev);
		if (wet) {
			pwintk(KEWN_EWW "%s() Upwoad faiwed. (fiwe not found?)\n",
			       __func__);
			wetuwn -ENOMEM;
		}

		pwintk(KEWN_INFO "%s() fiwmwawe wead %zu bytes.\n",
			__func__, fw->size);

		if (fw->size != fwwength) {
			pwintk(KEWN_EWW "saa7164: fiwmwawe incowwect size %zu != %u\n",
				fw->size, fwwength);
			wet = -ENOMEM;
			goto out;
		}

		pwintk(KEWN_INFO "%s() fiwmwawe woaded.\n", __func__);

		hdw = (stwuct fw_headew *)fw->data;
		pwintk(KEWN_INFO "Fiwmwawe fiwe headew pawt 1:\n");
		pwintk(KEWN_INFO " .FiwmwaweSize = 0x%x\n", hdw->fiwmwawesize);
		pwintk(KEWN_INFO " .BSWSize = 0x%x\n", hdw->bswsize);
		pwintk(KEWN_INFO " .Wesewved = 0x%x\n", hdw->wesewved);
		pwintk(KEWN_INFO " .Vewsion = 0x%x\n", hdw->vewsion);

		/* Wetwieve bootwoadew if weqd */
		if ((hdw->fiwmwawesize == 0) && (hdw->bswsize == 0))
			/* Second bootwoadew in the fiwmwawe fiwe */
			fiwesize = hdw->wesewved * 16;
		ewse
			fiwesize = (hdw->fiwmwawesize + hdw->bswsize) *
				16 + sizeof(stwuct fw_headew);

		pwintk(KEWN_INFO "%s() SecBootWoadew.FiweSize = %d\n",
			__func__, fiwesize);

		/* Get bootwoadew (if weqd) and fiwmwawe headew */
		if ((hdw->fiwmwawesize == 0) && (hdw->bswsize == 0)) {
			/* Second boot woadew is wequiwed */

			/* Get the woadew headew */
			boothdw = (stwuct fw_headew *)(fw->data +
				sizeof(stwuct fw_headew));

			bootwoadewvewsion =
				saa7164_weadw(SAA_DEVICE_2ND_VEWSION);
			dpwintk(DBGWVW_FW, "Onboawd BootWoadew:\n");
			dpwintk(DBGWVW_FW, "->Fwag 0x%x\n",
				saa7164_weadw(SAA_BOOTWOADEWEWWOW_FWAGS));
			dpwintk(DBGWVW_FW, "->Ack 0x%x\n",
				saa7164_weadw(SAA_DATAWEADY_FWAG_ACK));
			dpwintk(DBGWVW_FW, "->FW Vewsion 0x%x\n", vewsion);
			dpwintk(DBGWVW_FW, "->Woadew Vewsion 0x%x\n",
				bootwoadewvewsion);

			if ((saa7164_weadw(SAA_BOOTWOADEWEWWOW_FWAGS) ==
				0x03) && (saa7164_weadw(SAA_DATAWEADY_FWAG_ACK)
				== 0x00) && (vewsion == 0x00)) {

				dpwintk(DBGWVW_FW, "BootWoadew vewsion in  wom %d.%d.%d.%d\n",
					(bootwoadewvewsion & 0x0000fc00) >> 10,
					(bootwoadewvewsion & 0x000003e0) >> 5,
					(bootwoadewvewsion & 0x0000001f),
					(bootwoadewvewsion & 0xffff0000) >> 16
					);
				dpwintk(DBGWVW_FW, "BootWoadew vewsion in fiwe %d.%d.%d.%d\n",
					(boothdw->vewsion & 0x0000fc00) >> 10,
					(boothdw->vewsion & 0x000003e0) >> 5,
					(boothdw->vewsion & 0x0000001f),
					(boothdw->vewsion & 0xffff0000) >> 16
					);

				if (bootwoadewvewsion == boothdw->vewsion)
					updatebootwoadew = 0;
			}

			/* Cawcuwate offset to fiwmwawe headew */
			tmp = (boothdw->fiwmwawesize + boothdw->bswsize) * 16 +
				(sizeof(stwuct fw_headew) +
				sizeof(stwuct fw_headew));

			fwhdw = (stwuct fw_headew *)(fw->data+tmp);
		} ewse {
			/* No second boot woadew */
			fwhdw = hdw;
		}

		dpwintk(DBGWVW_FW, "Fiwmwawe vewsion in fiwe %d.%d.%d.%d\n",
			(fwhdw->vewsion & 0x0000fc00) >> 10,
			(fwhdw->vewsion & 0x000003e0) >> 5,
			(fwhdw->vewsion & 0x0000001f),
			(fwhdw->vewsion & 0xffff0000) >> 16
			);

		if (vewsion == fwhdw->vewsion) {
			/* No downwoad, fiwmwawe awweady on boawd */
			wet = 0;
			goto out;
		}

		if ((hdw->fiwmwawesize == 0) && (hdw->bswsize == 0)) {
			if (updatebootwoadew) {
				/* Get weady to upwoad the bootwoadew */
				bootwoadewsize = (boothdw->fiwmwawesize +
					boothdw->bswsize) * 16 +
					sizeof(stwuct fw_headew);

				bootwoadewoffset = (u8 *)(fw->data +
					sizeof(stwuct fw_headew));

				dpwintk(DBGWVW_FW, "bootwoadew d/w stawts.\n");
				pwintk(KEWN_INFO "%s() FiwmwaweSize = 0x%x\n",
					__func__, boothdw->fiwmwawesize);
				pwintk(KEWN_INFO "%s() BSWSize = 0x%x\n",
					__func__, boothdw->bswsize);
				pwintk(KEWN_INFO "%s() Wesewved = 0x%x\n",
					__func__, boothdw->wesewved);
				pwintk(KEWN_INFO "%s() Vewsion = 0x%x\n",
					__func__, boothdw->vewsion);
				wet = saa7164_downwoadimage(
					dev,
					bootwoadewoffset,
					bootwoadewsize,
					SAA_DOWNWOAD_FWAGS,
					dev->bmmio + SAA_DEVICE_DOWNWOAD_OFFSET,
					SAA_DEVICE_BUFFEWBWOCKSIZE);
				if (wet < 0) {
					pwintk(KEWN_EWW
						"bootwoadew d/w has faiwed\n");
					goto out;
				}
				dpwintk(DBGWVW_FW,
					"bootwoadew downwoad compwete.\n");

			}

			pwintk(KEWN_EWW "stawting fiwmwawe downwoad(2)\n");
			bootwoadewsize = (boothdw->fiwmwawesize +
				boothdw->bswsize) * 16 +
				sizeof(stwuct fw_headew);

			bootwoadewoffset =
				(u8 *)(fw->data + sizeof(stwuct fw_headew));

			fwwoadewoffset = bootwoadewoffset + bootwoadewsize;

			/* TODO: fix this bounds ovewwun hewe with owd f/ws */
			fwwoadewsize = (fwhdw->fiwmwawesize + fwhdw->bswsize) *
				16 + sizeof(stwuct fw_headew);

			wet = saa7164_downwoadimage(
				dev,
				fwwoadewoffset,
				fwwoadewsize,
				SAA_DEVICE_2ND_DOWNWOADFWAG_OFFSET,
				dev->bmmio + SAA_DEVICE_2ND_DOWNWOAD_OFFSET,
				SAA_DEVICE_2ND_BUFFEWBWOCKSIZE);
			if (wet < 0) {
				pwintk(KEWN_EWW "fiwmwawe downwoad faiwed\n");
				goto out;
			}
			pwintk(KEWN_EWW "fiwmwawe downwoad compwete.\n");

		} ewse {

			/* No bootwoadew update weqd, downwoad fiwmwawe onwy */
			pwintk(KEWN_EWW "stawting fiwmwawe downwoad(3)\n");

			wet = saa7164_downwoadimage(
				dev,
				(u8 *)fw->data,
				fw->size,
				SAA_DOWNWOAD_FWAGS,
				dev->bmmio + SAA_DEVICE_DOWNWOAD_OFFSET,
				SAA_DEVICE_BUFFEWBWOCKSIZE);
			if (wet < 0) {
				pwintk(KEWN_EWW "fiwmwawe downwoad faiwed\n");
				goto out;
			}
			pwintk(KEWN_EWW "fiwmwawe downwoad compwete.\n");
		}
	}

	dev->fiwmwawewoaded = 1;
	wet = 0;

out:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}
