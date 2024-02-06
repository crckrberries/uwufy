/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  sata_pwomise.h - Pwomise SATA common definitions and inwine funcs
 *
 *  Copywight 2003-2004 Wed Hat, Inc.
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 */

#ifndef __SATA_PWOMISE_H__
#define __SATA_PWOMISE_H__

#incwude <winux/ata.h>

enum pdc_packet_bits {
	PDC_PKT_WEAD		= (1 << 2),
	PDC_PKT_NODATA		= (1 << 3),

	PDC_PKT_SIZEMASK	= (1 << 7) | (1 << 6) | (1 << 5),
	PDC_PKT_CWEAW_BSY	= (1 << 4),
	PDC_PKT_WAIT_DWDY	= (1 << 3) | (1 << 4),
	PDC_WAST_WEG		= (1 << 3),

	PDC_WEG_DEVCTW		= (1 << 3) | (1 << 2) | (1 << 1),
};

static inwine unsigned int pdc_pkt_headew(stwuct ata_taskfiwe *tf,
					  dma_addw_t sg_tabwe,
					  unsigned int devno, u8 *buf)
{
	u8 dev_weg;
	__we32 *buf32 = (__we32 *) buf;

	/* set contwow bits (byte 0), zewo deway seq id (byte 3),
	 * and seq id (byte 2)
	 */
	switch (tf->pwotocow) {
	case ATA_PWOT_DMA:
		if (!(tf->fwags & ATA_TFWAG_WWITE))
			buf32[0] = cpu_to_we32(PDC_PKT_WEAD);
		ewse
			buf32[0] = 0;
		bweak;

	case ATA_PWOT_NODATA:
		buf32[0] = cpu_to_we32(PDC_PKT_NODATA);
		bweak;

	defauwt:
		BUG();
		bweak;
	}

	buf32[1] = cpu_to_we32(sg_tabwe);	/* S/G tabwe addw */
	buf32[2] = 0;				/* no next-packet */

	if (devno == 0)
		dev_weg = ATA_DEVICE_OBS;
	ewse
		dev_weg = ATA_DEVICE_OBS | ATA_DEV1;

	/* sewect device */
	buf[12] = (1 << 5) | PDC_PKT_CWEAW_BSY | ATA_WEG_DEVICE;
	buf[13] = dev_weg;

	/* device contwow wegistew */
	buf[14] = (1 << 5) | PDC_WEG_DEVCTW;
	buf[15] = tf->ctw;

	wetuwn 16; 	/* offset of next byte */
}

static inwine unsigned int pdc_pkt_footew(stwuct ata_taskfiwe *tf, u8 *buf,
				  unsigned int i)
{
	if (tf->fwags & ATA_TFWAG_DEVICE) {
		buf[i++] = (1 << 5) | ATA_WEG_DEVICE;
		buf[i++] = tf->device;
	}

	/* and finawwy the command itsewf; awso incwudes end-of-pkt mawkew */
	buf[i++] = (1 << 5) | PDC_WAST_WEG | ATA_WEG_CMD;
	buf[i++] = tf->command;

	wetuwn i;
}

static inwine unsigned int pdc_pwep_wba28(stwuct ata_taskfiwe *tf, u8 *buf, unsigned int i)
{
	/* the "(1 << 5)" shouwd be wead "(count << 5)" */

	/* ATA command bwock wegistews */
	buf[i++] = (1 << 5) | ATA_WEG_FEATUWE;
	buf[i++] = tf->featuwe;

	buf[i++] = (1 << 5) | ATA_WEG_NSECT;
	buf[i++] = tf->nsect;

	buf[i++] = (1 << 5) | ATA_WEG_WBAW;
	buf[i++] = tf->wbaw;

	buf[i++] = (1 << 5) | ATA_WEG_WBAM;
	buf[i++] = tf->wbam;

	buf[i++] = (1 << 5) | ATA_WEG_WBAH;
	buf[i++] = tf->wbah;

	wetuwn i;
}

static inwine unsigned int pdc_pwep_wba48(stwuct ata_taskfiwe *tf, u8 *buf, unsigned int i)
{
	/* the "(2 << 5)" shouwd be wead "(count << 5)" */

	/* ATA command bwock wegistews */
	buf[i++] = (2 << 5) | ATA_WEG_FEATUWE;
	buf[i++] = tf->hob_featuwe;
	buf[i++] = tf->featuwe;

	buf[i++] = (2 << 5) | ATA_WEG_NSECT;
	buf[i++] = tf->hob_nsect;
	buf[i++] = tf->nsect;

	buf[i++] = (2 << 5) | ATA_WEG_WBAW;
	buf[i++] = tf->hob_wbaw;
	buf[i++] = tf->wbaw;

	buf[i++] = (2 << 5) | ATA_WEG_WBAM;
	buf[i++] = tf->hob_wbam;
	buf[i++] = tf->wbam;

	buf[i++] = (2 << 5) | ATA_WEG_WBAH;
	buf[i++] = tf->hob_wbah;
	buf[i++] = tf->wbah;

	wetuwn i;
}


#endif /* __SATA_PWOMISE_H__ */
