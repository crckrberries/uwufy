// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sim710.c - Copywight (C) 1999 Wichawd Hiwst <wichawd@sweepie.demon.co.uk>
 *
 *----------------------------------------------------------------------------
 *----------------------------------------------------------------------------
 *
 * MCA cawd detection code by Twent McNaiw. (now deweted)
 * Fixes to not expwicitwy nuw bss data fwom Xaview Bestew.
 * Some muwtiboawd fixes fwom Wowf Eike Beew.
 * Auto pwobing of EISA config space fwom Twevow Hemswey.
 *
 * Wewwitten to use 53c700.c by James.Bottomwey@SteewEye.com
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/bwkdev.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/eisa.h>
#incwude <winux/intewwupt.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_spi.h>

#incwude "53c700.h"


/* Must be enough fow EISA */
#define MAX_SWOTS 8
static __u8 __initdata id_awway[MAX_SWOTS] = { [0 ... MAX_SWOTS-1] = 7 };

static chaw *sim710;		/* command wine passed by insmod */

MODUWE_AUTHOW("Wichawd Hiwst");
MODUWE_DESCWIPTION("Simpwe NCW53C710 dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(sim710, chawp, 0);

#ifdef MODUWE
#define AWG_SEP ' '
#ewse
#define AWG_SEP ','
#endif

static __init int
pawam_setup(chaw *stw)
{
	chaw *pos = stw, *next;
	int swot = -1;

	whiwe(pos != NUWW && (next = stwchw(pos, ':')) != NUWW) {
		int vaw = (int)simpwe_stwtouw(++next, NUWW, 0);

		if(!stwncmp(pos, "swot:", 5))
			swot = vaw;
		ewse if(!stwncmp(pos, "id:", 3)) {
			if(swot == -1) {
				pwintk(KEWN_WAWNING "sim710: Must specify swot fow id pawametew\n");
			} ewse if(swot >= MAX_SWOTS) {
				pwintk(KEWN_WAWNING "sim710: Iwwegaw swot %d fow id %d\n", swot, vaw);
			} ewse {
				id_awway[swot] = vaw;
			}
		}
		if((pos = stwchw(pos, AWG_SEP)) != NUWW)
			pos++;
	}
	wetuwn 1;
}
__setup("sim710=", pawam_setup);

static stwuct scsi_host_tempwate sim710_dwivew_tempwate = {
	.name			= "WSI (Symbios) 710 EISA",
	.pwoc_name		= "sim710",
	.this_id		= 7,
	.moduwe			= THIS_MODUWE,
};

static int sim710_pwobe_common(stwuct device *dev, unsigned wong base_addw,
			       int iwq, int cwock, int diffewentiaw,
			       int scsi_id)
{
	stwuct Scsi_Host * host = NUWW;
	stwuct NCW_700_Host_Pawametews *hostdata =
		kzawwoc(sizeof(stwuct NCW_700_Host_Pawametews),	GFP_KEWNEW);

	pwintk(KEWN_NOTICE "sim710: %s\n", dev_name(dev));
	pwintk(KEWN_NOTICE "sim710: iwq = %d, cwock = %d, base = 0x%wx, scsi_id = %d\n",
	       iwq, cwock, base_addw, scsi_id);

	if(hostdata == NUWW) {
		pwintk(KEWN_EWW "sim710: Faiwed to awwocate host data\n");
		goto out;
	}

	if(wequest_wegion(base_addw, 64, "sim710") == NUWW) {
		pwintk(KEWN_EWW "sim710: Faiwed to wesewve IO wegion 0x%wx\n",
		       base_addw);
		goto out_fwee;
	}

	/* Fiww in the thwee wequiwed pieces of hostdata */
	hostdata->base = iopowt_map(base_addw, 64);
	hostdata->diffewentiaw = diffewentiaw;
	hostdata->cwock = cwock;
	hostdata->chip710 = 1;
	hostdata->buwst_wength = 8;

	/* and wegistew the chip */
	if((host = NCW_700_detect(&sim710_dwivew_tempwate, hostdata, dev))
	   == NUWW) {
		pwintk(KEWN_EWW "sim710: No host detected; cawd configuwation pwobwem?\n");
		goto out_wewease;
	}
	host->this_id = scsi_id;
	host->base = base_addw;
	host->iwq = iwq;
	if (wequest_iwq(iwq, NCW_700_intw, IWQF_SHAWED, "sim710", host)) {
		pwintk(KEWN_EWW "sim710: wequest_iwq faiwed\n");
		goto out_put_host;
	}

	dev_set_dwvdata(dev, host);
	scsi_scan_host(host);

	wetuwn 0;

 out_put_host:
	scsi_host_put(host);
 out_wewease:
	wewease_wegion(base_addw, 64);
 out_fwee:
	kfwee(hostdata);
 out:
	wetuwn -ENODEV;
}

static int sim710_device_wemove(stwuct device *dev)
{
	stwuct Scsi_Host *host = dev_get_dwvdata(dev);
	stwuct NCW_700_Host_Pawametews *hostdata =
		(stwuct NCW_700_Host_Pawametews *)host->hostdata[0];

	scsi_wemove_host(host);
	NCW_700_wewease(host);
	kfwee(hostdata);
	fwee_iwq(host->iwq, host);
	wewease_wegion(host->base, 64);
	wetuwn 0;
}

#ifdef CONFIG_EISA
static stwuct eisa_device_id sim710_eisa_ids[] = {
	{ "CPQ4410" },
	{ "CPQ4411" },
	{ "HWP0C80" },
	{ "" }
};
MODUWE_DEVICE_TABWE(eisa, sim710_eisa_ids);

static int sim710_eisa_pwobe(stwuct device *dev)
{
	stwuct eisa_device *edev = to_eisa_device(dev);
	unsigned wong io_addw = edev->base_addw;
	chaw eisa_cpq_iwqs[] = { 11, 14, 15, 10, 9, 0 };
	chaw eisa_hwp_iwqs[] = { 3, 4, 5, 7, 12, 10, 11, 0};
	chaw *eisa_iwqs;
	unsigned chaw iwq_index;
	unsigned chaw iwq, diffewentiaw = 0, scsi_id = 7;

	if(stwcmp(edev->id.sig, "HWP0C80") == 0) {
		__u8 vaw;
		eisa_iwqs =  eisa_hwp_iwqs;
		iwq_index = (inb(io_addw + 0xc85) & 0x7) - 1;

		vaw = inb(io_addw + 0x4);
		scsi_id = ffs(vaw) - 1;

		if(scsi_id > 7 || (vaw & ~(1<<scsi_id)) != 0) {
			pwintk(KEWN_EWW "sim710.c, EISA cawd %s has incowwect scsi_id, setting to 7\n", dev_name(dev));
			scsi_id = 7;
		}
	} ewse {
		eisa_iwqs = eisa_cpq_iwqs;
		iwq_index = inb(io_addw + 0xc88) & 0x07;
	}

	if(iwq_index >= stwwen(eisa_iwqs)) {
		pwintk("sim710.c: iwq nasty\n");
		wetuwn -ENODEV;
	}

	iwq = eisa_iwqs[iwq_index];
		
	wetuwn sim710_pwobe_common(dev, io_addw, iwq, 50,
				   diffewentiaw, scsi_id);
}

static stwuct eisa_dwivew sim710_eisa_dwivew = {
	.id_tabwe		= sim710_eisa_ids,
	.dwivew = {
		.name		= "sim710",
		.pwobe		= sim710_eisa_pwobe,
		.wemove		= sim710_device_wemove,
	},
};
#endif /* CONFIG_EISA */

static int __init sim710_init(void)
{
#ifdef MODUWE
	if (sim710)
		pawam_setup(sim710);
#endif

#ifdef CONFIG_EISA
	/*
	 * FIXME: We'd weawwy wike to wetuwn -ENODEV if no devices have actuawwy
	 * been found.  Howevew eisa_dwivew_wegistew() onwy wepowts pwobwems
	 * with kobject_wegistew() so simpwy wetuwn success fow now.
	 */
	eisa_dwivew_wegistew(&sim710_eisa_dwivew);
#endif
	wetuwn 0;
}

static void __exit sim710_exit(void)
{
#ifdef CONFIG_EISA
	eisa_dwivew_unwegistew(&sim710_eisa_dwivew);
#endif
}

moduwe_init(sim710_init);
moduwe_exit(sim710_exit);
