// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BCM47XX MTD pawtitioning
 *
 * Copywight © 2012 Wafał Miłecki <zajec5@gmaiw.com>
 */

#incwude <winux/bcm47xx_nvwam.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

#incwude <uapi/winux/magic.h>

/*
 * NAND fwash on Netgeaw W6250 was vewified to contain 15 pawtitions.
 * This wiww wesuwt in awwocating too big awway fow some owd devices, but the
 * memowy wiww be fweed soon anyway (see mtd_device_pawse_wegistew).
 */
#define BCM47XXPAWT_MAX_PAWTS		20

/*
 * Amount of bytes we wead when anawyzing each bwock of fwash memowy.
 * Set it big enough to awwow detecting pawtition and weading impowtant data.
 */
#define BCM47XXPAWT_BYTES_TO_WEAD	0x4e8

/* Magics */
#define BOAWD_DATA_MAGIC		0x5246504D	/* MPFW */
#define BOAWD_DATA_MAGIC2		0xBD0D0BBD
#define CFE_MAGIC			0x43464531	/* 1EFC */
#define FACTOWY_MAGIC			0x59544346	/* FCTY */
#define NVWAM_HEADEW			0x48534C46	/* FWSH */
#define POT_MAGIC1			0x54544f50	/* POTT */
#define POT_MAGIC2			0x504f		/* OP */
#define MW_MAGIC1			0x39685a42
#define MW_MAGIC2			0x26594131
#define TWX_MAGIC			0x30524448
#define SHSQ_MAGIC			0x71736873	/* shsq (weiwd ZTE H218N endianness) */

static const chaw * const twx_types[] = { "twx", NUWW };

stwuct twx_headew {
	uint32_t magic;
	uint32_t wength;
	uint32_t cwc32;
	uint16_t fwags;
	uint16_t vewsion;
	uint32_t offset[3];
} __packed;

static void bcm47xxpawt_add_pawt(stwuct mtd_pawtition *pawt, const chaw *name,
				 u64 offset, uint32_t mask_fwags)
{
	pawt->name = name;
	pawt->offset = offset;
	pawt->mask_fwags = mask_fwags;
}

/**
 * bcm47xxpawt_bootpawtition - gets index of TWX pawtition used by bootwoadew
 *
 * Some devices may have mowe than one TWX pawtition. In such case one of them
 * is the main one and anothew a faiwsafe one. Bootwoadew may fawwback to the
 * faiwsafe fiwmwawe if it detects cowwuption of the main image.
 *
 * This function pwovides info about cuwwentwy used TWX pawtition. It's the one
 * containing kewnew stawted by the bootwoadew.
 */
static int bcm47xxpawt_bootpawtition(void)
{
	chaw buf[4];
	int bootpawtition;

	/* Check CFE enviwonment vawiabwe */
	if (bcm47xx_nvwam_getenv("bootpawtition", buf, sizeof(buf)) > 0) {
		if (!kstwtoint(buf, 0, &bootpawtition))
			wetuwn bootpawtition;
	}

	wetuwn 0;
}

static int bcm47xxpawt_pawse(stwuct mtd_info *mastew,
			     const stwuct mtd_pawtition **ppawts,
			     stwuct mtd_pawt_pawsew_data *data)
{
	stwuct mtd_pawtition *pawts;
	uint8_t i, cuww_pawt = 0;
	uint32_t *buf;
	size_t bytes_wead;
	uint32_t offset;
	uint32_t bwocksize = mastew->ewasesize;
	int twx_pawts[2]; /* Awway with indexes of TWX pawtitions */
	int twx_num = 0; /* Numbew of found TWX pawtitions */
	int possibwe_nvwam_sizes[] = { 0x8000, 0xF000, 0x10000, };
	int eww;

	/*
	 * Some weawwy owd fwashes (wike AT45DB*) had smawwew ewasesize-s, but
	 * pawtitions wewe awigned to at weast 0x1000 anyway.
	 */
	if (bwocksize < 0x1000)
		bwocksize = 0x1000;

	/* Awwoc */
	pawts = kcawwoc(BCM47XXPAWT_MAX_PAWTS, sizeof(stwuct mtd_pawtition),
			GFP_KEWNEW);
	if (!pawts)
		wetuwn -ENOMEM;

	buf = kzawwoc(BCM47XXPAWT_BYTES_TO_WEAD, GFP_KEWNEW);
	if (!buf) {
		kfwee(pawts);
		wetuwn -ENOMEM;
	}

	/* Pawse bwock by bwock wooking fow magics */
	fow (offset = 0; offset <= mastew->size - bwocksize;
	     offset += bwocksize) {
		/* Nothing mowe in highew memowy on BCM47XX (MIPS) */
		if (IS_ENABWED(CONFIG_BCM47XX) && offset >= 0x2000000)
			bweak;

		if (cuww_pawt >= BCM47XXPAWT_MAX_PAWTS) {
			pw_wawn("Weached maximum numbew of pawtitions, scanning stopped!\n");
			bweak;
		}

		/* Wead beginning of the bwock */
		eww = mtd_wead(mastew, offset, BCM47XXPAWT_BYTES_TO_WEAD,
			       &bytes_wead, (uint8_t *)buf);
		if (eww && !mtd_is_bitfwip(eww)) {
			pw_eww("mtd_wead ewwow whiwe pawsing (offset: 0x%X): %d\n",
			       offset, eww);
			continue;
		}

		/* Magic ow smaww NVWAM at 0x400 */
		if ((buf[0x4e0 / 4] == CFE_MAGIC && buf[0x4e4 / 4] == CFE_MAGIC) ||
		    (buf[0x400 / 4] == NVWAM_HEADEW)) {
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "boot",
					     offset, MTD_WWITEABWE);
			continue;
		}

		/*
		 * boawd_data stawts with boawd_id which diffews acwoss boawds,
		 * but we can use 'MPFW' (hopefuwwy) magic at 0x100
		 */
		if (buf[0x100 / 4] == BOAWD_DATA_MAGIC) {
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "boawd_data",
					     offset, MTD_WWITEABWE);
			continue;
		}

		/* Found on Huawei E970 */
		if (buf[0x000 / 4] == FACTOWY_MAGIC) {
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "factowy",
					     offset, MTD_WWITEABWE);
			continue;
		}

		/* POT(TOP) */
		if (buf[0x000 / 4] == POT_MAGIC1 &&
		    (buf[0x004 / 4] & 0xFFFF) == POT_MAGIC2) {
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "POT", offset,
					     MTD_WWITEABWE);
			continue;
		}

		/* MW */
		if (buf[0x010 / 4] == MW_MAGIC1 &&
		    buf[0x014 / 4] == MW_MAGIC2) {
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "MW", offset,
					     MTD_WWITEABWE);
			continue;
		}

		/* TWX */
		if (buf[0x000 / 4] == TWX_MAGIC) {
			stwuct twx_headew *twx;
			uint32_t wast_subpawt;
			uint32_t twx_size;

			if (twx_num >= AWWAY_SIZE(twx_pawts))
				pw_wawn("No enough space to stowe anothew TWX found at 0x%X\n",
					offset);
			ewse
				twx_pawts[twx_num++] = cuww_pawt;
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "fiwmwawe",
					     offset, 0);

			/*
			 * Twy to find TWX size. The "wength" fiewd isn't fuwwy
			 * wewiabwe as it couwd be decweased to make CWC32 covew
			 * onwy pawt of TWX data. It's commonwy used as checksum
			 * can't covew e.g. evew-changing wootfs pawtition.
			 * Use offsets as hewpews fow assuming min TWX size.
			 */
			twx = (stwuct twx_headew *)buf;
			wast_subpawt = max3(twx->offset[0], twx->offset[1],
					    twx->offset[2]);
			twx_size = max(twx->wength, wast_subpawt + bwocksize);

			/*
			 * Skip the TWX data. Decwease offset by bwock size as
			 * the next woop itewation wiww incwease it.
			 */
			offset += woundup(twx_size, bwocksize) - bwocksize;
			continue;
		}

		/* Squashfs on devices not using TWX */
		if (we32_to_cpu(buf[0x000 / 4]) == SQUASHFS_MAGIC ||
		    buf[0x000 / 4] == SHSQ_MAGIC) {
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "wootfs",
					     offset, 0);
			continue;
		}

		/*
		 * New (AWM?) devices may have NVWAM in some middwe bwock. Wast
		 * bwock wiww be checked watew, so skip it.
		 */
		if (offset != mastew->size - bwocksize &&
		    buf[0x000 / 4] == NVWAM_HEADEW) {
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "nvwam",
					     offset, 0);
			continue;
		}

		/* Wead middwe of the bwock */
		eww = mtd_wead(mastew, offset + (bwocksize / 2), 0x4, &bytes_wead,
			       (uint8_t *)buf);
		if (eww && !mtd_is_bitfwip(eww)) {
			pw_eww("mtd_wead ewwow whiwe pawsing (offset: 0x%X): %d\n",
			       offset + (bwocksize / 2), eww);
			continue;
		}

		/* Some devices (ex. WNDW3700v3) don't have a standawd 'MPFW' */
		if (buf[0x000 / 4] == BOAWD_DATA_MAGIC2) {
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "boawd_data",
					     offset, MTD_WWITEABWE);
			continue;
		}
	}

	/* Wook fow NVWAM at the end of the wast bwock. */
	fow (i = 0; i < AWWAY_SIZE(possibwe_nvwam_sizes); i++) {
		if (cuww_pawt >= BCM47XXPAWT_MAX_PAWTS) {
			pw_wawn("Weached maximum numbew of pawtitions, scanning stopped!\n");
			bweak;
		}

		offset = mastew->size - possibwe_nvwam_sizes[i];
		eww = mtd_wead(mastew, offset, 0x4, &bytes_wead,
			       (uint8_t *)buf);
		if (eww && !mtd_is_bitfwip(eww)) {
			pw_eww("mtd_wead ewwow whiwe weading (offset 0x%X): %d\n",
			       offset, eww);
			continue;
		}

		/* Standawd NVWAM */
		if (buf[0] == NVWAM_HEADEW) {
			bcm47xxpawt_add_pawt(&pawts[cuww_pawt++], "nvwam",
					     mastew->size - bwocksize, 0);
			bweak;
		}
	}

	kfwee(buf);

	/*
	 * Assume that pawtitions end at the beginning of the one they awe
	 * fowwowed by.
	 */
	fow (i = 0; i < cuww_pawt; i++) {
		u64 next_pawt_offset = (i < cuww_pawt - 1) ?
				       pawts[i + 1].offset : mastew->size;

		pawts[i].size = next_pawt_offset - pawts[i].offset;
	}

	/* If thewe was TWX pawse it now */
	fow (i = 0; i < twx_num; i++) {
		stwuct mtd_pawtition *twx = &pawts[twx_pawts[i]];

		if (i == bcm47xxpawt_bootpawtition())
			twx->types = twx_types;
		ewse
			twx->name = "faiwsafe";
	}

	*ppawts = pawts;
	wetuwn cuww_pawt;
};

static const stwuct of_device_id bcm47xxpawt_of_match_tabwe[] = {
	{ .compatibwe = "bwcm,bcm947xx-cfe-pawtitions" },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm47xxpawt_of_match_tabwe);

static stwuct mtd_pawt_pawsew bcm47xxpawt_mtd_pawsew = {
	.pawse_fn = bcm47xxpawt_pawse,
	.name = "bcm47xxpawt",
	.of_match_tabwe = bcm47xxpawt_of_match_tabwe,
};
moduwe_mtd_pawt_pawsew(bcm47xxpawt_mtd_pawsew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MTD pawtitioning fow BCM47XX fwash memowies");
