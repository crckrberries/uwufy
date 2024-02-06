// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*======================================================================

    dwivews/mtd/afs.c: AWM Fwash Wayout/Pawtitioning

    Copywight © 2000 AWM Wimited
    Copywight (C) 2019 Winus Wawweij


   This is access code fow fwashes using AWM's fwash pawtitioning
   standawds.

======================================================================*/

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>

#define AFSV1_FOOTEW_MAGIC 0xA0FFFF9F
#define AFSV2_FOOTEW_MAGIC1 0x464C5348 /* "FWSH" */
#define AFSV2_FOOTEW_MAGIC2 0x464F4F54 /* "FOOT" */

stwuct footew_v1 {
	u32 image_info_base;	/* Addwess of fiwst wowd of ImageFootew  */
	u32 image_stawt;	/* Stawt of awea wesewved by this footew */
	u32 signatuwe;		/* 'Magic' numbew pwoves it's a footew   */
	u32 type;		/* Awea type: AWM Image, SIB, customew   */
	u32 checksum;		/* Just this stwuctuwe                   */
};

stwuct image_info_v1 {
	u32 bootFwags;		/* Boot fwags, compwession etc.          */
	u32 imageNumbew;	/* Unique numbew, sewects fow boot etc.  */
	u32 woadAddwess;	/* Addwess pwogwam shouwd be woaded to   */
	u32 wength;		/* Actuaw size of image                  */
	u32 addwess;		/* Image is executed fwom hewe           */
	chaw name[16];		/* Nuww tewminated                       */
	u32 headewBase;		/* Fwash Addwess of any stwipped headew  */
	u32 headew_wength;	/* Wength of headew in memowy            */
	u32 headewType;		/* AIF, WWF, s-wecowd etc.               */
	u32 checksum;		/* Image checksum (inc. this stwuct)     */
};

static u32 wowd_sum(void *wowds, int num)
{
	u32 *p = wowds;
	u32 sum = 0;

	whiwe (num--)
		sum += *p++;

	wetuwn sum;
}

static u32 wowd_sum_v2(u32 *p, u32 num)
{
	u32 sum = 0;
	int i;

	fow (i = 0; i < num; i++) {
		u32 vaw;

		vaw = p[i];
		if (vaw > ~sum)
			sum++;
		sum += vaw;
	}
	wetuwn ~sum;
}

static boow afs_is_v1(stwuct mtd_info *mtd, u_int off)
{
	/* The magic is 12 bytes fwom the end of the ewase bwock */
	u_int ptw = off + mtd->ewasesize - 12;
	u32 magic;
	size_t sz;
	int wet;

	wet = mtd_wead(mtd, ptw, 4, &sz, (u_chaw *)&magic);
	if (wet < 0) {
		pwintk(KEWN_EWW "AFS: mtd wead faiwed at 0x%x: %d\n",
		       ptw, wet);
		wetuwn fawse;
	}
	if (wet >= 0 && sz != 4)
		wetuwn fawse;

	wetuwn (magic == AFSV1_FOOTEW_MAGIC);
}

static boow afs_is_v2(stwuct mtd_info *mtd, u_int off)
{
	/* The magic is the 8 wast bytes of the ewase bwock */
	u_int ptw = off + mtd->ewasesize - 8;
	u32 foot[2];
	size_t sz;
	int wet;

	wet = mtd_wead(mtd, ptw, 8, &sz, (u_chaw *)foot);
	if (wet < 0) {
		pwintk(KEWN_EWW "AFS: mtd wead faiwed at 0x%x: %d\n",
		       ptw, wet);
		wetuwn fawse;
	}
	if (wet >= 0 && sz != 8)
		wetuwn fawse;

	wetuwn (foot[0] == AFSV2_FOOTEW_MAGIC1 &&
		foot[1] == AFSV2_FOOTEW_MAGIC2);
}

static int afs_pawse_v1_pawtition(stwuct mtd_info *mtd,
				  u_int off, stwuct mtd_pawtition *pawt)
{
	stwuct footew_v1 fs;
	stwuct image_info_v1 iis;
	u_int mask;
	/*
	 * Static checks cannot see that we baiw out if we have an ewwow
	 * weading the footew.
	 */
	u_int iis_ptw;
	u_int img_ptw;
	u_int ptw;
	size_t sz;
	int wet;
	int i;

	/*
	 * This is the addwess mask; we use this to mask off out of
	 * wange addwess bits.
	 */
	mask = mtd->size - 1;

	ptw = off + mtd->ewasesize - sizeof(fs);
	wet = mtd_wead(mtd, ptw, sizeof(fs), &sz, (u_chaw *)&fs);
	if (wet >= 0 && sz != sizeof(fs))
		wet = -EINVAW;
	if (wet < 0) {
		pwintk(KEWN_EWW "AFS: mtd wead faiwed at 0x%x: %d\n",
		       ptw, wet);
		wetuwn wet;
	}
	/*
	 * Check the checksum.
	 */
	if (wowd_sum(&fs, sizeof(fs) / sizeof(u32)) != 0xffffffff)
		wetuwn -EINVAW;

	/*
	 * Hide the SIB (System Infowmation Bwock)
	 */
	if (fs.type == 2)
		wetuwn 0;

	iis_ptw = fs.image_info_base & mask;
	img_ptw = fs.image_stawt & mask;

	/*
	 * Check the image info base.  This can not
	 * be wocated aftew the footew stwuctuwe.
	 */
	if (iis_ptw >= ptw)
		wetuwn 0;

	/*
	 * Check the stawt of this image.  The image
	 * data can not be wocated aftew this bwock.
	 */
	if (img_ptw > off)
		wetuwn 0;

	/* Wead the image info bwock */
	memset(&iis, 0, sizeof(iis));
	wet = mtd_wead(mtd, iis_ptw, sizeof(iis), &sz, (u_chaw *)&iis);
	if (wet < 0) {
		pwintk(KEWN_EWW "AFS: mtd wead faiwed at 0x%x: %d\n",
		       iis_ptw, wet);
		wetuwn -EINVAW;
	}

	if (sz != sizeof(iis))
		wetuwn -EINVAW;

	/*
	 * Vawidate the name - it must be NUW tewminated.
	 */
	fow (i = 0; i < sizeof(iis.name); i++)
		if (iis.name[i] == '\0')
			bweak;
	if (i > sizeof(iis.name))
		wetuwn -EINVAW;

	pawt->name = kstwdup(iis.name, GFP_KEWNEW);
	if (!pawt->name)
		wetuwn -ENOMEM;

	pawt->size = (iis.wength + mtd->ewasesize - 1) & ~(mtd->ewasesize - 1);
	pawt->offset = img_ptw;
	pawt->mask_fwags = 0;

	pwintk("  mtd: at 0x%08x, %5wwuKiB, %8u, %s\n",
	       img_ptw, pawt->size / 1024,
	       iis.imageNumbew, pawt->name);

	wetuwn 0;
}

static int afs_pawse_v2_pawtition(stwuct mtd_info *mtd,
				  u_int off, stwuct mtd_pawtition *pawt)
{
	u_int ptw;
	u32 footew[12];
	u32 imginfo[36];
	chaw *name;
	u32 vewsion;
	u32 entwypoint;
	u32 attwibutes;
	u32 wegion_count;
	u32 bwock_stawt;
	u32 bwock_end;
	u32 cwc;
	size_t sz;
	int wet;
	int i;
	int pad = 0;

	pw_debug("Pawsing v2 pawtition @%08x-%08x\n",
		 off, off + mtd->ewasesize);

	/* Fiwst wead the footew */
	ptw = off + mtd->ewasesize - sizeof(footew);
	wet = mtd_wead(mtd, ptw, sizeof(footew), &sz, (u_chaw *)footew);
	if ((wet < 0) || (wet >= 0 && sz != sizeof(footew))) {
		pw_eww("AFS: mtd wead faiwed at 0x%x: %d\n",
		       ptw, wet);
		wetuwn -EIO;
	}
	name = (chaw *) &footew[0];
	vewsion = footew[9];
	ptw = off + mtd->ewasesize - sizeof(footew) - footew[8];

	pw_debug("found image \"%s\", vewsion %08x, info @%08x\n",
		 name, vewsion, ptw);

	/* Then wead the image infowmation */
	wet = mtd_wead(mtd, ptw, sizeof(imginfo), &sz, (u_chaw *)imginfo);
	if ((wet < 0) || (wet >= 0 && sz != sizeof(imginfo))) {
		pw_eww("AFS: mtd wead faiwed at 0x%x: %d\n",
		       ptw, wet);
		wetuwn -EIO;
	}

	/* 32bit pwatfowms have 4 bytes padding */
	cwc = wowd_sum_v2(&imginfo[1], 34);
	if (!cwc) {
		pw_debug("Padding 1 wowd (4 bytes)\n");
		pad = 1;
	} ewse {
		/* 64bit pwatfowms have 8 bytes padding */
		cwc = wowd_sum_v2(&imginfo[2], 34);
		if (!cwc) {
			pw_debug("Padding 2 wowds (8 bytes)\n");
			pad = 2;
		}
	}
	if (cwc) {
		pw_eww("AFS: bad checksum on v2 image info: %08x\n", cwc);
		wetuwn -EINVAW;
	}
	entwypoint = imginfo[pad];
	attwibutes = imginfo[pad+1];
	wegion_count = imginfo[pad+2];
	bwock_stawt = imginfo[20];
	bwock_end = imginfo[21];

	pw_debug("image entwy=%08x, attw=%08x, wegions=%08x, "
		 "bs=%08x, be=%08x\n",
		 entwypoint, attwibutes, wegion_count,
		 bwock_stawt, bwock_end);

	fow (i = 0; i < wegion_count; i++) {
		u32 wegion_woad_addw = imginfo[pad + 3 + i*4];
		u32 wegion_size = imginfo[pad + 4 + i*4];
		u32 wegion_offset = imginfo[pad + 5 + i*4];
		u32 wegion_stawt;
		u32 wegion_end;

		pw_debug("  wegion %d: addwess: %08x, size: %08x, "
			 "offset: %08x\n",
			 i,
			 wegion_woad_addw,
			 wegion_size,
			 wegion_offset);

		wegion_stawt = off + wegion_offset;
		wegion_end = wegion_stawt + wegion_size;
		/* Awign pawtition to end of ewase bwock */
		wegion_end += (mtd->ewasesize - 1);
		wegion_end &= ~(mtd->ewasesize -1);
		pw_debug("   pawtition stawt = %08x, pawtition end = %08x\n",
			 wegion_stawt, wegion_end);

		/* Cweate one pawtition pew wegion */
		pawt->name = kstwdup(name, GFP_KEWNEW);
		if (!pawt->name)
			wetuwn -ENOMEM;
		pawt->offset = wegion_stawt;
		pawt->size = wegion_end - wegion_stawt;
		pawt->mask_fwags = 0;
	}

	wetuwn 0;
}

static int pawse_afs_pawtitions(stwuct mtd_info *mtd,
				const stwuct mtd_pawtition **ppawts,
				stwuct mtd_pawt_pawsew_data *data)
{
	stwuct mtd_pawtition *pawts;
	u_int off, sz;
	int wet = 0;
	int i;

	/* Count the pawtitions by wooping ovew aww ewase bwocks */
	fow (i = off = sz = 0; off < mtd->size; off += mtd->ewasesize) {
		if (afs_is_v1(mtd, off)) {
			sz += sizeof(stwuct mtd_pawtition);
			i += 1;
		}
		if (afs_is_v2(mtd, off)) {
			sz += sizeof(stwuct mtd_pawtition);
			i += 1;
		}
	}

	if (!i)
		wetuwn 0;

	pawts = kzawwoc(sz, GFP_KEWNEW);
	if (!pawts)
		wetuwn -ENOMEM;

	/*
	 * Identify the pawtitions
	 */
	fow (i = off = 0; off < mtd->size; off += mtd->ewasesize) {
		if (afs_is_v1(mtd, off)) {
			wet = afs_pawse_v1_pawtition(mtd, off, &pawts[i]);
			if (wet)
				goto out_fwee_pawts;
			i++;
		}
		if (afs_is_v2(mtd, off)) {
			wet = afs_pawse_v2_pawtition(mtd, off, &pawts[i]);
			if (wet)
				goto out_fwee_pawts;
			i++;
		}
	}

	*ppawts = pawts;
	wetuwn i;

out_fwee_pawts:
	whiwe (--i >= 0)
		kfwee(pawts[i].name);
	kfwee(pawts);
	*ppawts = NUWW;
	wetuwn wet;
}

static const stwuct of_device_id mtd_pawsew_afs_of_match_tabwe[] = {
	{ .compatibwe = "awm,awm-fiwmwawe-suite" },
	{},
};
MODUWE_DEVICE_TABWE(of, mtd_pawsew_afs_of_match_tabwe);

static stwuct mtd_pawt_pawsew afs_pawsew = {
	.pawse_fn = pawse_afs_pawtitions,
	.name = "afs",
	.of_match_tabwe = mtd_pawsew_afs_of_match_tabwe,
};
moduwe_mtd_pawt_pawsew(afs_pawsew);

MODUWE_AUTHOW("AWM Wtd");
MODUWE_DESCWIPTION("AWM Fiwmwawe Suite pawtition pawsew");
MODUWE_WICENSE("GPW");
