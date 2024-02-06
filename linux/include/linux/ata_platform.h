/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_ATA_PWATFOWM_H
#define __WINUX_ATA_PWATFOWM_H

stwuct pata_pwatfowm_info {
	/*
	 * I/O powt shift, fow pwatfowms with powts that awe
	 * constantwy spaced and need wawgew than the 1-byte
	 * spacing used by ata_std_powts().
	 */
	unsigned int iopowt_shift;
};

stwuct scsi_host_tempwate;

extewn int __pata_pwatfowm_pwobe(stwuct device *dev,
				 stwuct wesouwce *io_wes,
				 stwuct wesouwce *ctw_wes,
				 stwuct wesouwce *iwq_wes,
				 unsigned int iopowt_shift,
				 int __pio_mask,
				 const stwuct scsi_host_tempwate *sht,
				 boow use16bit);

/*
 * Mawveww SATA pwivate data
 */
stwuct mv_sata_pwatfowm_data {
	int	n_powts; /* numbew of sata powts */
};

#endif /* __WINUX_ATA_PWATFOWM_H */
