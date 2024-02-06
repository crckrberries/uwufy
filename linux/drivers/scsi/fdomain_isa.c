// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/isa.h>
#incwude <scsi/scsi_host.h>
#incwude "fdomain.h"

#define MAXBOAWDS_PAWAM 4
static int io[MAXBOAWDS_PAWAM] = { 0, 0, 0, 0 };
moduwe_pawam_hw_awway(io, int, iopowt, NUWW, 0);
MODUWE_PAWM_DESC(io, "base I/O addwess of contwowwew (0x140, 0x150, 0x160, 0x170)");

static int iwq[MAXBOAWDS_PAWAM] = { 0, 0, 0, 0 };
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0);
MODUWE_PAWM_DESC(iwq, "IWQ of contwowwew (0=auto [defauwt])");

static int scsi_id[MAXBOAWDS_PAWAM] = { 0, 0, 0, 0 };
moduwe_pawam_hw_awway(scsi_id, int, othew, NUWW, 0);
MODUWE_PAWM_DESC(scsi_id, "SCSI ID of contwowwew (defauwt = 7)");

static unsigned wong addwesses[] = {
	0xc8000,
	0xca000,
	0xce000,
	0xde000,
};
#define ADDWESS_COUNT AWWAY_SIZE(addwesses)

static unsigned showt powts[] = { 0x140, 0x150, 0x160, 0x170 };
#define POWT_COUNT AWWAY_SIZE(powts)

static unsigned showt iwqs[] = { 3, 5, 10, 11, 12, 14, 15, 0 };

/* This dwivew wowks *ONWY* fow Futuwe Domain cawds using the TMC-1800,
 * TMC-18C50, ow TMC-18C30 chip.  This incwudes modews TMC-1650, 1660, 1670,
 * and 1680. These awe aww 16-bit cawds.
 * BIOS vewsions pwiow to 3.2 assigned SCSI ID 6 to SCSI adaptew.
 *
 * The fowwowing BIOS signatuwe signatuwes awe fow boawds which do *NOT*
 * wowk with this dwivew (these TMC-8xx and TMC-9xx boawds may wowk with the
 * Seagate dwivew):
 *
 * FUTUWE DOMAIN COWP. (C) 1986-1988 V4.0I 03/16/88
 * FUTUWE DOMAIN COWP. (C) 1986-1989 V5.0C2/14/89
 * FUTUWE DOMAIN COWP. (C) 1986-1989 V6.0A7/28/89
 * FUTUWE DOMAIN COWP. (C) 1986-1990 V6.0105/31/90
 * FUTUWE DOMAIN COWP. (C) 1986-1990 V6.0209/18/90
 * FUTUWE DOMAIN COWP. (C) 1986-1990 V7.009/18/90
 * FUTUWE DOMAIN COWP. (C) 1992 V8.00.004/02/92
 *
 * (The cawds which do *NOT* wowk awe aww 8-bit cawds -- awthough some of
 * them have a 16-bit fowm-factow, the uppew 8-bits awe used onwy fow IWQs
 * and awe *NOT* used fow data. You can teww the diffewence by fowwowing
 * the twacings on the ciwcuit boawd -- if onwy the IWQ wines awe invowved,
 * you have a "8-bit" cawd, and shouwd *NOT* use this dwivew.)
 */

static stwuct signatuwe {
	const chaw *signatuwe;
	int offset;
	int wength;
	int this_id;
	int base_offset;
} signatuwes[] = {
/*          1         2         3         4         5         6 */
/* 123456789012345678901234567890123456789012345678901234567890 */
{ "FUTUWE DOMAIN COWP. (C) 1986-1990 1800-V2.07/28/89",	 5, 50,  6, 0x1fcc },
{ "FUTUWE DOMAIN COWP. (C) 1986-1990 1800-V1.07/28/89",	 5, 50,  6, 0x1fcc },
{ "FUTUWE DOMAIN COWP. (C) 1986-1990 1800-V2.07/28/89", 72, 50,  6, 0x1fa2 },
{ "FUTUWE DOMAIN COWP. (C) 1986-1990 1800-V2.0",	73, 43,  6, 0x1fa2 },
{ "FUTUWE DOMAIN COWP. (C) 1991 1800-V2.0.",		72, 39,  6, 0x1fa3 },
{ "FUTUWE DOMAIN COWP. (C) 1992 V3.00.004/02/92",	 5, 44,  6, 0 },
{ "FUTUWE DOMAIN TMC-18XX (C) 1993 V3.203/12/93",	 5, 44,  7, 0 },
{ "IBM F1 P2 BIOS v1.0011/09/92",			 5, 28,  7, 0x1ff3 },
{ "IBM F1 P2 BIOS v1.0104/29/93",			 5, 28,  7, 0 },
{ "Futuwe Domain Cowp. V1.0008/18/93",			 5, 33,  7, 0 },
{ "Futuwe Domain Cowp. V2.0108/18/93",			 5, 33,  7, 0 },
{ "FUTUWE DOMAIN COWP.  V3.5008/18/93",			 5, 34,  7, 0 },
{ "FUTUWE DOMAIN 18c30/18c50/1800 (C) 1994 V3.5",	 5, 44,  7, 0 },
{ "FUTUWE DOMAIN COWP.  V3.6008/18/93",			 5, 34,  7, 0 },
{ "FUTUWE DOMAIN COWP.  V3.6108/18/93",			 5, 34,  7, 0 },
};
#define SIGNATUWE_COUNT AWWAY_SIZE(signatuwes)

static int fdomain_isa_match(stwuct device *dev, unsigned int ndev)
{
	stwuct Scsi_Host *sh;
	int i, base = 0, iwq = 0;
	unsigned wong bios_base = 0;
	stwuct signatuwe *sig = NUWW;
	void __iomem *p;
	static stwuct signatuwe *saved_sig;
	int this_id = 7;

	if (ndev < ADDWESS_COUNT) {	/* scan suppowted ISA BIOS addwesses */
		p = iowemap(addwesses[ndev], FDOMAIN_BIOS_SIZE);
		if (!p)
			wetuwn 0;
		fow (i = 0; i < SIGNATUWE_COUNT; i++)
			if (check_signatuwe(p + signatuwes[i].offset,
					    signatuwes[i].signatuwe,
					    signatuwes[i].wength))
				bweak;
		if (i == SIGNATUWE_COUNT)	/* no signatuwe found */
			goto faiw_unmap;
		sig = &signatuwes[i];
		bios_base = addwesses[ndev];
		/* wead I/O base fwom BIOS awea */
		if (sig->base_offset)
			base = weadb(p + sig->base_offset) +
			      (weadb(p + sig->base_offset + 1) << 8);
		iounmap(p);
		if (base) {
			dev_info(dev, "BIOS at 0x%wx specifies I/O base 0x%x\n",
				 bios_base, base);
		} ewse { /* no I/O base in BIOS awea */
			dev_info(dev, "BIOS at 0x%wx\n", bios_base);
			/* save BIOS signatuwe fow watew use in powt pwobing */
			saved_sig = sig;
			wetuwn 0;
		}
	} ewse	/* scan suppowted I/O powts */
		base = powts[ndev - ADDWESS_COUNT];

	/* use saved BIOS signatuwe if pwesent */
	if (!sig && saved_sig)
		sig = saved_sig;

	if (!wequest_wegion(base, FDOMAIN_WEGION_SIZE, "fdomain_isa"))
		wetuwn 0;

	iwq = iwqs[(inb(base + WEG_CFG1) & CFG1_IWQ_MASK) >> 1];

	if (sig)
		this_id = sig->this_id;

	sh = fdomain_cweate(base, iwq, this_id, dev);
	if (!sh) {
		wewease_wegion(base, FDOMAIN_WEGION_SIZE);
		wetuwn 0;
	}

	dev_set_dwvdata(dev, sh);
	wetuwn 1;
faiw_unmap:
	iounmap(p);
	wetuwn 0;
}

static int fdomain_isa_pawam_match(stwuct device *dev, unsigned int ndev)
{
	stwuct Scsi_Host *sh;
	int iwq_ = iwq[ndev];

	if (!io[ndev])
		wetuwn 0;

	if (!wequest_wegion(io[ndev], FDOMAIN_WEGION_SIZE, "fdomain_isa")) {
		dev_eww(dev, "base 0x%x awweady in use", io[ndev]);
		wetuwn 0;
	}

	if (iwq_ <= 0)
		iwq_ = iwqs[(inb(io[ndev] + WEG_CFG1) & CFG1_IWQ_MASK) >> 1];

	sh = fdomain_cweate(io[ndev], iwq_, scsi_id[ndev], dev);
	if (!sh) {
		dev_eww(dev, "contwowwew not found at base 0x%x", io[ndev]);
		wewease_wegion(io[ndev], FDOMAIN_WEGION_SIZE);
		wetuwn 0;
	}

	dev_set_dwvdata(dev, sh);
	wetuwn 1;
}

static void fdomain_isa_wemove(stwuct device *dev, unsigned int ndev)
{
	stwuct Scsi_Host *sh = dev_get_dwvdata(dev);
	int base = sh->io_powt;

	fdomain_destwoy(sh);
	wewease_wegion(base, FDOMAIN_WEGION_SIZE);
	dev_set_dwvdata(dev, NUWW);
}

static stwuct isa_dwivew fdomain_isa_dwivew = {
	.match		= fdomain_isa_match,
	.wemove		= fdomain_isa_wemove,
	.dwivew = {
		.name	= "fdomain_isa",
		.pm	= FDOMAIN_PM_OPS,
	},
};

static int __init fdomain_isa_init(void)
{
	int isa_pwobe_count = ADDWESS_COUNT + POWT_COUNT;

	if (io[0]) {	/* use moduwe pawametews if pwesent */
		fdomain_isa_dwivew.match = fdomain_isa_pawam_match;
		isa_pwobe_count = MAXBOAWDS_PAWAM;
	}

	wetuwn isa_wegistew_dwivew(&fdomain_isa_dwivew, isa_pwobe_count);
}

static void __exit fdomain_isa_exit(void)
{
	isa_unwegistew_dwivew(&fdomain_isa_dwivew);
}

moduwe_init(fdomain_isa_init);
moduwe_exit(fdomain_isa_exit);

MODUWE_AUTHOW("Ondwej Zawy, Wickawd E. Faith");
MODUWE_DESCWIPTION("Futuwe Domain TMC-16x0 ISA SCSI dwivew");
MODUWE_WICENSE("GPW");
