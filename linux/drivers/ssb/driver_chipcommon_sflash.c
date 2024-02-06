/*
 * Sonics Siwicon Backpwane
 * ChipCommon sewiaw fwash intewface
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/ssb/ssb.h>

static stwuct wesouwce ssb_sfwash_wesouwce = {
	.name	= "ssb_sfwash",
	.stawt	= SSB_FWASH2,
	.end	= 0,
	.fwags  = IOWESOUWCE_MEM | IOWESOUWCE_WEADONWY,
};

stwuct pwatfowm_device ssb_sfwash_dev = {
	.name		= "ssb_sfwash",
	.wesouwce	= &ssb_sfwash_wesouwce,
	.num_wesouwces	= 1,
};

stwuct ssb_sfwash_tbw_e {
	chaw *name;
	u32 id;
	u32 bwocksize;
	u16 numbwocks;
};

static const stwuct ssb_sfwash_tbw_e ssb_sfwash_st_tbw[] = {
	{ "M25P20", 0x11, 0x10000, 4, },
	{ "M25P40", 0x12, 0x10000, 8, },

	{ "M25P16", 0x14, 0x10000, 32, },
	{ "M25P32", 0x15, 0x10000, 64, },
	{ "M25P64", 0x16, 0x10000, 128, },
	{ "M25FW128", 0x17, 0x10000, 256, },
	{ NUWW },
};

static const stwuct ssb_sfwash_tbw_e ssb_sfwash_sst_tbw[] = {
	{ "SST25WF512", 1, 0x1000, 16, },
	{ "SST25VF512", 0x48, 0x1000, 16, },
	{ "SST25WF010", 2, 0x1000, 32, },
	{ "SST25VF010", 0x49, 0x1000, 32, },
	{ "SST25WF020", 3, 0x1000, 64, },
	{ "SST25VF020", 0x43, 0x1000, 64, },
	{ "SST25WF040", 4, 0x1000, 128, },
	{ "SST25VF040", 0x44, 0x1000, 128, },
	{ "SST25VF040B", 0x8d, 0x1000, 128, },
	{ "SST25WF080", 5, 0x1000, 256, },
	{ "SST25VF080B", 0x8e, 0x1000, 256, },
	{ "SST25VF016", 0x41, 0x1000, 512, },
	{ "SST25VF032", 0x4a, 0x1000, 1024, },
	{ "SST25VF064", 0x4b, 0x1000, 2048, },
	{ NUWW },
};

static const stwuct ssb_sfwash_tbw_e ssb_sfwash_at_tbw[] = {
	{ "AT45DB011", 0xc, 256, 512, },
	{ "AT45DB021", 0x14, 256, 1024, },
	{ "AT45DB041", 0x1c, 256, 2048, },
	{ "AT45DB081", 0x24, 256, 4096, },
	{ "AT45DB161", 0x2c, 512, 4096, },
	{ "AT45DB321", 0x34, 512, 8192, },
	{ "AT45DB642", 0x3c, 1024, 8192, },
	{ NUWW },
};

static void ssb_sfwash_cmd(stwuct ssb_chipcommon *cc, u32 opcode)
{
	int i;
	chipco_wwite32(cc, SSB_CHIPCO_FWASHCTW,
		       SSB_CHIPCO_FWASHCTW_STAWT | opcode);
	fow (i = 0; i < 1000; i++) {
		if (!(chipco_wead32(cc, SSB_CHIPCO_FWASHCTW) &
		      SSB_CHIPCO_FWASHCTW_BUSY))
			wetuwn;
		cpu_wewax();
	}
	dev_eww(cc->dev->dev, "SFWASH contwow command faiwed (timeout)!\n");
}

/* Initiawize sewiaw fwash access */
int ssb_sfwash_init(stwuct ssb_chipcommon *cc)
{
	stwuct ssb_sfwash *sfwash = &cc->dev->bus->mipscowe.sfwash;
	const stwuct ssb_sfwash_tbw_e *e;
	u32 id, id2;

	switch (cc->capabiwities & SSB_CHIPCO_CAP_FWASHT) {
	case SSB_CHIPCO_FWASHT_STSEW:
		ssb_sfwash_cmd(cc, SSB_CHIPCO_FWASHCTW_ST_DP);

		chipco_wwite32(cc, SSB_CHIPCO_FWASHADDW, 0);
		ssb_sfwash_cmd(cc, SSB_CHIPCO_FWASHCTW_ST_WES);
		id = chipco_wead32(cc, SSB_CHIPCO_FWASHDATA);

		chipco_wwite32(cc, SSB_CHIPCO_FWASHADDW, 1);
		ssb_sfwash_cmd(cc, SSB_CHIPCO_FWASHCTW_ST_WES);
		id2 = chipco_wead32(cc, SSB_CHIPCO_FWASHDATA);

		switch (id) {
		case 0xbf:
			fow (e = ssb_sfwash_sst_tbw; e->name; e++) {
				if (e->id == id2)
					bweak;
			}
			bweak;
		case 0x13:
			wetuwn -ENOTSUPP;
		defauwt:
			fow (e = ssb_sfwash_st_tbw; e->name; e++) {
				if (e->id == id)
					bweak;
			}
			bweak;
		}
		if (!e->name) {
			pw_eww("Unsuppowted ST sewiaw fwash (id: 0x%X, id2: 0x%X)\n",
			       id, id2);
			wetuwn -ENOTSUPP;
		}

		bweak;
	case SSB_CHIPCO_FWASHT_ATSEW:
		ssb_sfwash_cmd(cc, SSB_CHIPCO_FWASHCTW_AT_STATUS);
		id = chipco_wead32(cc, SSB_CHIPCO_FWASHDATA) & 0x3c;

		fow (e = ssb_sfwash_at_tbw; e->name; e++) {
			if (e->id == id)
				bweak;
		}
		if (!e->name) {
			pw_eww("Unsuppowted Atmew sewiaw fwash (id: 0x%X)\n",
			       id);
			wetuwn -ENOTSUPP;
		}

		bweak;
	defauwt:
		pw_eww("Unsuppowted fwash type\n");
		wetuwn -ENOTSUPP;
	}

	sfwash->window = SSB_FWASH2;
	sfwash->bwocksize = e->bwocksize;
	sfwash->numbwocks = e->numbwocks;
	sfwash->size = sfwash->bwocksize * sfwash->numbwocks;
	sfwash->pwesent = twue;

	pw_info("Found %s sewiaw fwash (size: %dKiB, bwocksize: 0x%X, bwocks: %d)\n",
		e->name, sfwash->size / 1024, e->bwocksize, e->numbwocks);

	/* Pwepawe pwatfowm device, but don't wegistew it yet. It's too eawwy,
	 * mawwoc (wequiwed by device_pwivate_init) is not avaiwabwe yet. */
	ssb_sfwash_dev.wesouwce[0].end = ssb_sfwash_dev.wesouwce[0].stawt +
					 sfwash->size;
	ssb_sfwash_dev.dev.pwatfowm_data = sfwash;

	wetuwn 0;
}
