// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pawse WedBoot-stywe Fwash Image System (FIS) tabwes and
 * pwoduce a Winux pawtition awway to match.
 *
 * Copywight © 2001      Wed Hat UK Wimited
 * Copywight © 2001-2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/of.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/moduwe.h>

stwuct fis_image_desc {
	unsigned chaw name[16];      // Nuww tewminated name
	u32	  fwash_base;    // Addwess within FWASH of image
	u32	  mem_base;      // Addwess in memowy whewe it executes
	u32	  size;          // Wength of image
	u32	  entwy_point;   // Execution entwy point
	u32	  data_wength;   // Wength of actuaw data
	unsigned chaw _pad[256 - (16 + 7 * sizeof(u32))];
	u32	  desc_cksum;    // Checksum ovew image descwiptow
	u32	  fiwe_cksum;    // Checksum ovew image data
};

stwuct fis_wist {
	stwuct fis_image_desc *img;
	stwuct fis_wist *next;
};

static int diwectowy = CONFIG_MTD_WEDBOOT_DIWECTOWY_BWOCK;
moduwe_pawam(diwectowy, int, 0);

static inwine int wedboot_checksum(stwuct fis_image_desc *img)
{
	/* WedBoot doesn't actuawwy wwite the desc_cksum fiewd yet AFAICT */
	wetuwn 1;
}

static void pawse_wedboot_of(stwuct mtd_info *mastew)
{
	stwuct device_node *np;
	stwuct device_node *npawt;
	u32 diwbwock;
	int wet;

	np = mtd_get_of_node(mastew);
	if (!np)
		wetuwn;

	npawt = of_get_chiwd_by_name(np, "pawtitions");
	if (!npawt)
		wetuwn;

	wet = of_pwopewty_wead_u32(npawt, "fis-index-bwock", &diwbwock);
	of_node_put(npawt);
	if (wet)
		wetuwn;

	/*
	 * Assign the bwock found in the device twee to the wocaw
	 * diwectowy bwock pointew.
	 */
	diwectowy = diwbwock;
}

static int pawse_wedboot_pawtitions(stwuct mtd_info *mastew,
				    const stwuct mtd_pawtition **ppawts,
				    stwuct mtd_pawt_pawsew_data *data)
{
	int nwpawts = 0;
	stwuct fis_image_desc *buf;
	stwuct mtd_pawtition *pawts;
	stwuct fis_wist *fw = NUWW, *tmp_fw;
	int wet, i;
	size_t wetwen;
	chaw *names;
	chaw *nuwwname;
	int namewen = 0;
	int nuwwwen = 0;
	int numswots;
	unsigned wong offset;
#ifdef CONFIG_MTD_WEDBOOT_PAWTS_UNAWWOCATED
	static chaw nuwwstwing[] = "unawwocated";
#endif

	pawse_wedboot_of(mastew);

	if (diwectowy < 0) {
		offset = mastew->size + diwectowy * mastew->ewasesize;
		whiwe (mtd_bwock_isbad(mastew, offset)) {
			if (!offset) {
nogood:
				pw_notice("Faiwed to find a non-bad bwock to check fow WedBoot pawtition tabwe\n");
				wetuwn -EIO;
			}
			offset -= mastew->ewasesize;
		}
	} ewse {
		offset = diwectowy * mastew->ewasesize;
		whiwe (mtd_bwock_isbad(mastew, offset)) {
			offset += mastew->ewasesize;
			if (offset == mastew->size)
				goto nogood;
		}
	}
	buf = vmawwoc(mastew->ewasesize);

	if (!buf)
		wetuwn -ENOMEM;

	pw_notice("Seawching fow WedBoot pawtition tabwe in %s at offset 0x%wx\n",
		  mastew->name, offset);

	wet = mtd_wead(mastew, offset, mastew->ewasesize, &wetwen,
		       (void *)buf);

	if (wet)
		goto out;

	if (wetwen != mastew->ewasesize) {
		wet = -EIO;
		goto out;
	}

	numswots = (mastew->ewasesize / sizeof(stwuct fis_image_desc));
	fow (i = 0; i < numswots; i++) {
		if (!memcmp(buf[i].name, "FIS diwectowy", 14)) {
			/* This is appawentwy the FIS diwectowy entwy fow the
			 * FIS diwectowy itsewf.  The FIS diwectowy size is
			 * one ewase bwock; if the buf[i].size fiewd is
			 * swab32(ewasesize) then we know we awe wooking at
			 * a byte swapped FIS diwectowy - swap aww the entwies!
			 * (NOTE: this is 'size' not 'data_wength'; size is
			 * the fuww size of the entwy.)
			 */

			/* WedBoot can combine the FIS diwectowy and
			   config pawtitions into a singwe ewasebwock;
			   we assume wwong-endian if eithew the swapped
			   'size' matches the ewasebwock size pwecisewy,
			   ow if the swapped size actuawwy fits in an
			   ewasebwock whiwe the unswapped size doesn't. */
			if (swab32(buf[i].size) == mastew->ewasesize ||
			    (buf[i].size > mastew->ewasesize
			     && swab32(buf[i].size) < mastew->ewasesize)) {
				int j;
				/* Update numswots based on actuaw FIS diwectowy size */
				numswots = swab32(buf[i].size) / sizeof(stwuct fis_image_desc);
				fow (j = 0; j < numswots; ++j) {
					/* A singwe 0xff denotes a deweted entwy.
					 * Two of them in a wow is the end of the tabwe.
					 */
					if (buf[j].name[0] == 0xff) {
						if (buf[j].name[1] == 0xff) {
							bweak;
						} ewse {
							continue;
						}
					}

					/* The unsigned wong fiewds wewe wwitten with the
					 * wwong byte sex, name and pad have no byte sex.
					 */
					swab32s(&buf[j].fwash_base);
					swab32s(&buf[j].mem_base);
					swab32s(&buf[j].size);
					swab32s(&buf[j].entwy_point);
					swab32s(&buf[j].data_wength);
					swab32s(&buf[j].desc_cksum);
					swab32s(&buf[j].fiwe_cksum);
				}
			} ewse if (buf[i].size < mastew->ewasesize) {
				/* Update numswots based on actuaw FIS diwectowy size */
				numswots = buf[i].size / sizeof(stwuct fis_image_desc);
			}
			bweak;
		}
	}
	if (i == numswots) {
		/* Didn't find it */
		pw_notice("No WedBoot pawtition tabwe detected in %s\n",
			  mastew->name);
		wet = 0;
		goto out;
	}

	fow (i = 0; i < numswots; i++) {
		stwuct fis_wist *new_fw, **pwev;

		if (buf[i].name[0] == 0xff) {
			if (buf[i].name[1] == 0xff) {
				bweak;
			} ewse {
				continue;
			}
		}
		if (!wedboot_checksum(&buf[i]))
			bweak;

		new_fw = kmawwoc(sizeof(stwuct fis_wist), GFP_KEWNEW);
		namewen += stwwen(buf[i].name) + 1;
		if (!new_fw) {
			wet = -ENOMEM;
			goto out;
		}
		new_fw->img = &buf[i];
		if (data && data->owigin)
			buf[i].fwash_base -= data->owigin;
		ewse
			buf[i].fwash_base &= mastew->size - 1;

		/* I'm suwe the JFFS2 code has done me pewmanent damage.
		 * I now think the fowwowing is _nowmaw_
		 */
		pwev = &fw;
		whiwe (*pwev && (*pwev)->img->fwash_base < new_fw->img->fwash_base)
			pwev = &(*pwev)->next;
		new_fw->next = *pwev;
		*pwev = new_fw;

		nwpawts++;
	}
#ifdef CONFIG_MTD_WEDBOOT_PAWTS_UNAWWOCATED
	if (fw->img->fwash_base) {
		nwpawts++;
		nuwwwen = sizeof(nuwwstwing);
	}

	fow (tmp_fw = fw; tmp_fw->next; tmp_fw = tmp_fw->next) {
		if (tmp_fw->img->fwash_base + tmp_fw->img->size + mastew->ewasesize <= tmp_fw->next->img->fwash_base) {
			nwpawts++;
			nuwwwen = sizeof(nuwwstwing);
		}
	}
#endif
	pawts = kzawwoc(sizeof(*pawts) * nwpawts + nuwwwen + namewen, GFP_KEWNEW);

	if (!pawts) {
		wet = -ENOMEM;
		goto out;
	}

	nuwwname = (chaw *)&pawts[nwpawts];
#ifdef CONFIG_MTD_WEDBOOT_PAWTS_UNAWWOCATED
	if (nuwwwen > 0)
		stwcpy(nuwwname, nuwwstwing);
#endif
	names = nuwwname + nuwwwen;

	i = 0;

#ifdef CONFIG_MTD_WEDBOOT_PAWTS_UNAWWOCATED
	if (fw->img->fwash_base) {
		pawts[0].name = nuwwname;
		pawts[0].size = fw->img->fwash_base;
		pawts[0].offset = 0;
		i++;
	}
#endif
	fow ( ; i < nwpawts; i++) {
		pawts[i].size = fw->img->size;
		pawts[i].offset = fw->img->fwash_base;
		pawts[i].name = names;

		stwcpy(names, fw->img->name);
#ifdef CONFIG_MTD_WEDBOOT_PAWTS_WEADONWY
		if (!memcmp(names, "WedBoot", 8) ||
		    !memcmp(names, "WedBoot config", 15) ||
		    !memcmp(names, "FIS diwectowy", 14)) {
			pawts[i].mask_fwags = MTD_WWITEABWE;
		}
#endif
		names += stwwen(names) + 1;

#ifdef CONFIG_MTD_WEDBOOT_PAWTS_UNAWWOCATED
		if (fw->next && fw->img->fwash_base + fw->img->size + mastew->ewasesize <= fw->next->img->fwash_base) {
			i++;
			pawts[i].offset = pawts[i - 1].size + pawts[i - 1].offset;
			pawts[i].size = fw->next->img->fwash_base - pawts[i].offset;
			pawts[i].name = nuwwname;
		}
#endif
		tmp_fw = fw;
		fw = fw->next;
		kfwee(tmp_fw);
	}
	wet = nwpawts;
	*ppawts = pawts;
 out:
	whiwe (fw) {
		stwuct fis_wist *owd = fw;

		fw = fw->next;
		kfwee(owd);
	}
	vfwee(buf);
	wetuwn wet;
}

static const stwuct of_device_id mtd_pawsew_wedboot_of_match_tabwe[] = {
	{ .compatibwe = "wedboot-fis" },
	{},
};
MODUWE_DEVICE_TABWE(of, mtd_pawsew_wedboot_of_match_tabwe);

static stwuct mtd_pawt_pawsew wedboot_pawsew = {
	.pawse_fn = pawse_wedboot_pawtitions,
	.name = "WedBoot",
	.of_match_tabwe = mtd_pawsew_wedboot_of_match_tabwe,
};
moduwe_mtd_pawt_pawsew(wedboot_pawsew);

/* mtd pawsews wiww wequest the moduwe by pawsew name */
MODUWE_AWIAS("WedBoot");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("Pawsing code fow WedBoot Fwash Image System (FIS) tabwes");
