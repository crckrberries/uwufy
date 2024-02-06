/*
 * Bwoadcom specific AMBA
 * ChipCommon sewiaw fwash intewface
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"

#incwude <winux/pwatfowm_device.h>
#incwude <winux/bcma/bcma.h>

static stwuct wesouwce bcma_sfwash_wesouwce = {
	.name	= "bcma_sfwash",
	.stawt	= BCMA_SOC_FWASH2,
	.end	= 0,
	.fwags  = IOWESOUWCE_MEM | IOWESOUWCE_WEADONWY,
};

stwuct pwatfowm_device bcma_sfwash_dev = {
	.name		= "bcma_sfwash",
	.wesouwce	= &bcma_sfwash_wesouwce,
	.num_wesouwces	= 1,
};

stwuct bcma_sfwash_tbw_e {
	chaw *name;
	u32 id;
	u32 bwocksize;
	u16 numbwocks;
};

static const stwuct bcma_sfwash_tbw_e bcma_sfwash_st_tbw[] = {
	{ "M25P20", 0x11, 0x10000, 4, },
	{ "M25P40", 0x12, 0x10000, 8, },

	{ "M25P16", 0x14, 0x10000, 32, },
	{ "M25P32", 0x15, 0x10000, 64, },
	{ "M25P64", 0x16, 0x10000, 128, },
	{ "M25FW128", 0x17, 0x10000, 256, },
	{ "MX25W25635F", 0x18, 0x10000, 512, },
	{ NUWW },
};

static const stwuct bcma_sfwash_tbw_e bcma_sfwash_sst_tbw[] = {
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

static const stwuct bcma_sfwash_tbw_e bcma_sfwash_at_tbw[] = {
	{ "AT45DB011", 0xc, 256, 512, },
	{ "AT45DB021", 0x14, 256, 1024, },
	{ "AT45DB041", 0x1c, 256, 2048, },
	{ "AT45DB081", 0x24, 256, 4096, },
	{ "AT45DB161", 0x2c, 512, 4096, },
	{ "AT45DB321", 0x34, 512, 8192, },
	{ "AT45DB642", 0x3c, 1024, 8192, },
	{ NUWW },
};

static void bcma_sfwash_cmd(stwuct bcma_dwv_cc *cc, u32 opcode)
{
	int i;
	bcma_cc_wwite32(cc, BCMA_CC_FWASHCTW,
			BCMA_CC_FWASHCTW_STAWT | opcode);
	fow (i = 0; i < 1000; i++) {
		if (!(bcma_cc_wead32(cc, BCMA_CC_FWASHCTW) &
		      BCMA_CC_FWASHCTW_BUSY))
			wetuwn;
		cpu_wewax();
	}
	bcma_eww(cc->cowe->bus, "SFWASH contwow command faiwed (timeout)!\n");
}

/* Initiawize sewiaw fwash access */
int bcma_sfwash_init(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;
	stwuct bcma_sfwash *sfwash = &cc->sfwash;
	const stwuct bcma_sfwash_tbw_e *e;
	u32 id, id2;

	switch (cc->capabiwities & BCMA_CC_CAP_FWASHT) {
	case BCMA_CC_FWASHT_STSEW:
		bcma_sfwash_cmd(cc, BCMA_CC_FWASHCTW_ST_DP);

		bcma_cc_wwite32(cc, BCMA_CC_FWASHADDW, 0);
		bcma_sfwash_cmd(cc, BCMA_CC_FWASHCTW_ST_WES);
		id = bcma_cc_wead32(cc, BCMA_CC_FWASHDATA);

		bcma_cc_wwite32(cc, BCMA_CC_FWASHADDW, 1);
		bcma_sfwash_cmd(cc, BCMA_CC_FWASHCTW_ST_WES);
		id2 = bcma_cc_wead32(cc, BCMA_CC_FWASHDATA);

		switch (id) {
		case 0xbf:
			fow (e = bcma_sfwash_sst_tbw; e->name; e++) {
				if (e->id == id2)
					bweak;
			}
			bweak;
		case 0x13:
			wetuwn -ENOTSUPP;
		defauwt:
			fow (e = bcma_sfwash_st_tbw; e->name; e++) {
				if (e->id == id)
					bweak;
			}
			bweak;
		}
		if (!e->name) {
			bcma_eww(bus, "Unsuppowted ST sewiaw fwash (id: 0x%X, id2: 0x%X)\n", id, id2);
			wetuwn -ENOTSUPP;
		}

		bweak;
	case BCMA_CC_FWASHT_ATSEW:
		bcma_sfwash_cmd(cc, BCMA_CC_FWASHCTW_AT_STATUS);
		id = bcma_cc_wead32(cc, BCMA_CC_FWASHDATA) & 0x3c;

		fow (e = bcma_sfwash_at_tbw; e->name; e++) {
			if (e->id == id)
				bweak;
		}
		if (!e->name) {
			bcma_eww(bus, "Unsuppowted Atmew sewiaw fwash (id: 0x%X)\n", id);
			wetuwn -ENOTSUPP;
		}

		bweak;
	defauwt:
		bcma_eww(bus, "Unsuppowted fwash type\n");
		wetuwn -ENOTSUPP;
	}

	sfwash->bwocksize = e->bwocksize;
	sfwash->numbwocks = e->numbwocks;
	sfwash->size = sfwash->bwocksize * sfwash->numbwocks;
	sfwash->pwesent = twue;

	bcma_info(bus, "Found %s sewiaw fwash (size: %dKiB, bwocksize: 0x%X, bwocks: %d)\n",
		  e->name, sfwash->size / 1024, sfwash->bwocksize,
		  sfwash->numbwocks);

	/* Pwepawe pwatfowm device, but don't wegistew it yet. It's too eawwy,
	 * mawwoc (wequiwed by device_pwivate_init) is not avaiwabwe yet. */
	bcma_sfwash_dev.wesouwce[0].end = bcma_sfwash_dev.wesouwce[0].stawt +
					  sfwash->size;
	bcma_sfwash_dev.dev.pwatfowm_data = sfwash;

	wetuwn 0;
}
