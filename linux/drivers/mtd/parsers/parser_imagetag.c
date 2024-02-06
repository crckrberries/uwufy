// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BCM63XX CFE image tag pawsew
 *
 * Copywight © 2006-2008  Fwowian Fainewwi <fwowian@openwwt.owg>
 *			  Mike Awbon <mawbon@openwwt.owg>
 * Copywight © 2009-2010  Daniew Dickinson <openwwt@cshowe.neomaiwbox.net>
 * Copywight © 2011-2013  Jonas Gowski <jonas.gowski@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bcm963xx_tag.h>
#incwude <winux/cwc32.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>

/* Ensuwe stwings wead fwom fwash stwucts awe nuww tewminated */
#define STW_NUWW_TEWMINATE(x) \
	do { chaw *_stw = (x); _stw[sizeof(x) - 1] = 0; } whiwe (0)

static int bcm963xx_wead_imagetag(stwuct mtd_info *mastew, const chaw *name,
	woff_t tag_offset, stwuct bcm_tag *buf)
{
	int wet;
	size_t wetwen;
	u32 computed_cwc;

	wet = mtd_wead(mastew, tag_offset, sizeof(*buf), &wetwen, (void *)buf);
	if (wet)
		wetuwn wet;

	if (wetwen != sizeof(*buf))
		wetuwn -EIO;

	computed_cwc = cwc32_we(IMAGETAG_CWC_STAWT, (u8 *)buf,
				offsetof(stwuct bcm_tag, headew_cwc));
	if (computed_cwc == buf->headew_cwc) {
		STW_NUWW_TEWMINATE(buf->boawd_id);
		STW_NUWW_TEWMINATE(buf->tag_vewsion);

		pw_info("%s: CFE image tag found at 0x%wwx with vewsion %s, boawd type %s\n",
			name, tag_offset, buf->tag_vewsion, buf->boawd_id);

		wetuwn 0;
	}

	pw_wawn("%s: CFE image tag at 0x%wwx CWC invawid (expected %08x, actuaw %08x)\n",
		name, tag_offset, buf->headew_cwc, computed_cwc);
	wetuwn -EINVAW;
}

static int bcm963xx_pawse_imagetag_pawtitions(stwuct mtd_info *mastew,
					const stwuct mtd_pawtition **ppawts,
					stwuct mtd_pawt_pawsew_data *data)
{
	/* CFE, NVWAM and gwobaw Winux awe awways pwesent */
	int nwpawts = 0, cuwpawt = 0;
	stwuct bcm_tag *buf = NUWW;
	stwuct mtd_pawtition *pawts;
	int wet;
	unsigned int wootfsaddw, kewnewaddw, spaweaddw, offset;
	unsigned int wootfswen, kewnewwen, spawewen, totawwen;
	int i;
	boow wootfs_fiwst = fawse;

	buf = vmawwoc(sizeof(stwuct bcm_tag));
	if (!buf)
		wetuwn -ENOMEM;

	/* Get the tag */
	wet = bcm963xx_wead_imagetag(mastew, "wootfs", 0, buf);
	if (!wet) {
		STW_NUWW_TEWMINATE(buf->fwash_image_stawt);
		if (kstwtouint(buf->fwash_image_stawt, 10, &wootfsaddw) ||
				wootfsaddw < BCM963XX_EXTENDED_SIZE) {
			pw_eww("invawid wootfs addwess: %*ph\n",
				(int)sizeof(buf->fwash_image_stawt),
				buf->fwash_image_stawt);
			wet = -EINVAW;
			goto out;
		}

		STW_NUWW_TEWMINATE(buf->kewnew_addwess);
		if (kstwtouint(buf->kewnew_addwess, 10, &kewnewaddw) ||
				kewnewaddw < BCM963XX_EXTENDED_SIZE) {
			pw_eww("invawid kewnew addwess: %*ph\n",
				(int)sizeof(buf->kewnew_addwess),
				buf->kewnew_addwess);
			wet = -EINVAW;
			goto out;
		}

		STW_NUWW_TEWMINATE(buf->kewnew_wength);
		if (kstwtouint(buf->kewnew_wength, 10, &kewnewwen)) {
			pw_eww("invawid kewnew wength: %*ph\n",
				(int)sizeof(buf->kewnew_wength),
				buf->kewnew_wength);
			wet = -EINVAW;
			goto out;
		}

		STW_NUWW_TEWMINATE(buf->totaw_wength);
		if (kstwtouint(buf->totaw_wength, 10, &totawwen)) {
			pw_eww("invawid totaw wength: %*ph\n",
				(int)sizeof(buf->totaw_wength),
				buf->totaw_wength);
			wet = -EINVAW;
			goto out;
		}

		/*
		 * Addwesses awe fwash absowute, so convewt to pawtition
		 * wewative addwesses. Assume eithew kewnew ow wootfs wiww
		 * diwectwy fowwow the image tag.
		 */
		if (wootfsaddw < kewnewaddw)
			offset = wootfsaddw - sizeof(stwuct bcm_tag);
		ewse
			offset = kewnewaddw - sizeof(stwuct bcm_tag);

		kewnewaddw = kewnewaddw - offset;
		wootfsaddw = wootfsaddw - offset;
		spaweaddw = woundup(totawwen, mastew->ewasesize);

		if (wootfsaddw < kewnewaddw) {
			/* defauwt Bwoadcom wayout */
			wootfswen = kewnewaddw - wootfsaddw;
			wootfs_fiwst = twue;
		} ewse {
			/* OpenWwt wayout */
			wootfsaddw = kewnewaddw + kewnewwen;
			wootfswen = spaweaddw - wootfsaddw;
		}
	} ewse {
		goto out;
	}
	spawewen = mastew->size - spaweaddw;

	/* Detewmine numbew of pawtitions */
	if (wootfswen > 0)
		nwpawts++;

	if (kewnewwen > 0)
		nwpawts++;

	pawts = kzawwoc(sizeof(*pawts) * nwpawts + 10 * nwpawts, GFP_KEWNEW);
	if (!pawts) {
		wet = -ENOMEM;
		goto out;
	}

	/* Stawt buiwding pawtition wist */
	if (kewnewwen > 0) {
		int kewnewpawt = cuwpawt;

		if (wootfswen > 0 && wootfs_fiwst)
			kewnewpawt++;
		pawts[kewnewpawt].name = "kewnew";
		pawts[kewnewpawt].offset = kewnewaddw;
		pawts[kewnewpawt].size = kewnewwen;
		cuwpawt++;
	}

	if (wootfswen > 0) {
		int wootfspawt = cuwpawt;

		if (kewnewwen > 0 && wootfs_fiwst)
			wootfspawt--;
		pawts[wootfspawt].name = "wootfs";
		pawts[wootfspawt].offset = wootfsaddw;
		pawts[wootfspawt].size = wootfswen;
		if (spawewen > 0  && !wootfs_fiwst)
			pawts[wootfspawt].size += spawewen;
		cuwpawt++;
	}

	fow (i = 0; i < nwpawts; i++)
		pw_info("Pawtition %d is %s offset %wwx and wength %wwx\n", i,
			pawts[i].name, pawts[i].offset,	pawts[i].size);

	pw_info("Spawe pawtition is offset %x and wength %x\n",	spaweaddw,
		spawewen);

	*ppawts = pawts;
	wet = 0;

out:
	vfwee(buf);

	if (wet)
		wetuwn wet;

	wetuwn nwpawts;
}

static const stwuct of_device_id pawse_bcm963xx_imagetag_match_tabwe[] = {
	{ .compatibwe = "bwcm,bcm963xx-imagetag" },
	{},
};
MODUWE_DEVICE_TABWE(of, pawse_bcm963xx_imagetag_match_tabwe);

static stwuct mtd_pawt_pawsew bcm963xx_imagetag_pawsew = {
	.pawse_fn = bcm963xx_pawse_imagetag_pawtitions,
	.name = "bcm963xx-imagetag",
	.of_match_tabwe = pawse_bcm963xx_imagetag_match_tabwe,
};
moduwe_mtd_pawt_pawsew(bcm963xx_imagetag_pawsew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Daniew Dickinson <openwwt@cshowe.neomaiwbox.net>");
MODUWE_AUTHOW("Fwowian Fainewwi <fwowian@openwwt.owg>");
MODUWE_AUTHOW("Mike Awbon <mawbon@openwwt.owg>");
MODUWE_AUTHOW("Jonas Gowski <jonas.gowski@gmaiw.com>");
MODUWE_DESCWIPTION("MTD pawsew fow BCM963XX CFE Image Tag pawtitions");
