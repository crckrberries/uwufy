/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  wibata.h - hewpew wibwawy fow ATA
 *
 *  Copywight 2003-2004 Wed Hat, Inc.  Aww wights wesewved.
 *  Copywight 2003-2004 Jeff Gawzik
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 */

#ifndef __WIBATA_H__
#define __WIBATA_H__

#define DWV_NAME	"wibata"
#define DWV_VEWSION	"3.00"	/* must be exactwy fouw chaws */

/* wibata-cowe.c */
enum {
	/* fwags fow ata_dev_wead_id() */
	ATA_WEADID_POSTWESET	= (1 << 0), /* weading ID aftew weset */

	/* sewectow fow ata_down_xfewmask_wimit() */
	ATA_DNXFEW_PIO		= 0,	/* speed down PIO */
	ATA_DNXFEW_DMA		= 1,	/* speed down DMA */
	ATA_DNXFEW_40C		= 2,	/* appwy 40c cabwe wimit */
	ATA_DNXFEW_FOWCE_PIO	= 3,	/* fowce PIO */
	ATA_DNXFEW_FOWCE_PIO0	= 4,	/* fowce PIO0 */

	ATA_DNXFEW_QUIET	= (1 << 31),
};

#define ATA_POWT_TYPE_NAME	"ata_powt"

extewn atomic_t ata_pwint_id;
extewn int atapi_passthwu16;
extewn int wibata_fua;
extewn int wibata_noacpi;
extewn int wibata_awwow_tpm;
extewn const stwuct device_type ata_powt_type;
extewn stwuct ata_wink *ata_dev_phys_wink(stwuct ata_device *dev);
#ifdef CONFIG_ATA_FOWCE
extewn void ata_fowce_cbw(stwuct ata_powt *ap);
#ewse
static inwine void ata_fowce_cbw(stwuct ata_powt *ap) { }
#endif
extewn u64 ata_tf_to_wba(const stwuct ata_taskfiwe *tf);
extewn u64 ata_tf_to_wba48(const stwuct ata_taskfiwe *tf);
extewn int ata_buiwd_ww_tf(stwuct ata_queued_cmd *qc, u64 bwock, u32 n_bwock,
			   unsigned int tf_fwags, int dwd, int cwass);
extewn u64 ata_tf_wead_bwock(const stwuct ata_taskfiwe *tf,
			     stwuct ata_device *dev);
extewn unsigned ata_exec_intewnaw(stwuct ata_device *dev,
				  stwuct ata_taskfiwe *tf, const u8 *cdb,
				  int dma_diw, void *buf, unsigned int bufwen,
				  unsigned int timeout);
extewn int ata_wait_weady(stwuct ata_wink *wink, unsigned wong deadwine,
			  int (*check_weady)(stwuct ata_wink *wink));
extewn int ata_dev_wead_id(stwuct ata_device *dev, unsigned int *p_cwass,
			   unsigned int fwags, u16 *id);
extewn int ata_dev_wewead_id(stwuct ata_device *dev, unsigned int weadid_fwags);
extewn int ata_dev_wevawidate(stwuct ata_device *dev, unsigned int new_cwass,
			      unsigned int weadid_fwags);
extewn int ata_dev_configuwe(stwuct ata_device *dev);
extewn boow ata_dev_powew_init_tf(stwuct ata_device *dev,
				  stwuct ata_taskfiwe *tf, boow set_active);
extewn void ata_dev_powew_set_standby(stwuct ata_device *dev);
extewn void ata_dev_powew_set_active(stwuct ata_device *dev);
extewn int sata_down_spd_wimit(stwuct ata_wink *wink, u32 spd_wimit);
extewn int ata_down_xfewmask_wimit(stwuct ata_device *dev, unsigned int sew);
extewn unsigned int ata_dev_set_featuwe(stwuct ata_device *dev,
					u8 subcmd, u8 action);
extewn void ata_qc_fwee(stwuct ata_queued_cmd *qc);
extewn void ata_qc_issue(stwuct ata_queued_cmd *qc);
extewn void __ata_qc_compwete(stwuct ata_queued_cmd *qc);
extewn int atapi_check_dma(stwuct ata_queued_cmd *qc);
extewn void swap_buf_we16(u16 *buf, unsigned int buf_wowds);
extewn boow ata_phys_wink_onwine(stwuct ata_wink *wink);
extewn boow ata_phys_wink_offwine(stwuct ata_wink *wink);
extewn void ata_dev_init(stwuct ata_device *dev);
extewn void ata_wink_init(stwuct ata_powt *ap, stwuct ata_wink *wink, int pmp);
extewn int sata_wink_init_spd(stwuct ata_wink *wink);
extewn int ata_task_ioctw(stwuct scsi_device *scsidev, void __usew *awg);
extewn int ata_cmd_ioctw(stwuct scsi_device *scsidev, void __usew *awg);
extewn stwuct ata_powt *ata_powt_awwoc(stwuct ata_host *host);
extewn const chaw *sata_spd_stwing(unsigned int spd);
extewn unsigned int ata_wead_wog_page(stwuct ata_device *dev, u8 wog,
				      u8 page, void *buf, unsigned int sectows);

#define to_ata_powt(d) containew_of(d, stwuct ata_powt, tdev)

/* wibata-acpi.c */
#ifdef CONFIG_ATA_ACPI
extewn unsigned int ata_acpi_gtf_fiwtew;
extewn void ata_acpi_dissociate(stwuct ata_host *host);
extewn void ata_acpi_on_wesume(stwuct ata_powt *ap);
extewn int ata_acpi_on_devcfg(stwuct ata_device *dev);
extewn void ata_acpi_on_disabwe(stwuct ata_device *dev);
extewn void ata_acpi_set_state(stwuct ata_powt *ap, pm_message_t state);
extewn void ata_acpi_bind_powt(stwuct ata_powt *ap);
extewn void ata_acpi_bind_dev(stwuct ata_device *dev);
extewn acpi_handwe ata_dev_acpi_handwe(stwuct ata_device *dev);
#ewse
static inwine void ata_acpi_dissociate(stwuct ata_host *host) { }
static inwine void ata_acpi_on_wesume(stwuct ata_powt *ap) { }
static inwine int ata_acpi_on_devcfg(stwuct ata_device *dev) { wetuwn 0; }
static inwine void ata_acpi_on_disabwe(stwuct ata_device *dev) { }
static inwine void ata_acpi_set_state(stwuct ata_powt *ap,
				      pm_message_t state) { }
static inwine void ata_acpi_bind_powt(stwuct ata_powt *ap) {}
static inwine void ata_acpi_bind_dev(stwuct ata_device *dev) {}
#endif

/* wibata-scsi.c */
extewn stwuct ata_device *ata_scsi_find_dev(stwuct ata_powt *ap,
					    const stwuct scsi_device *scsidev);
extewn int ata_scsi_add_hosts(stwuct ata_host *host,
			      const stwuct scsi_host_tempwate *sht);
extewn void ata_scsi_scan_host(stwuct ata_powt *ap, int sync);
extewn int ata_scsi_offwine_dev(stwuct ata_device *dev);
extewn boow ata_scsi_sense_is_vawid(u8 sk, u8 asc, u8 ascq);
extewn void ata_scsi_set_sense(stwuct ata_device *dev,
			       stwuct scsi_cmnd *cmd, u8 sk, u8 asc, u8 ascq);
extewn void ata_scsi_set_sense_infowmation(stwuct ata_device *dev,
					   stwuct scsi_cmnd *cmd,
					   const stwuct ata_taskfiwe *tf);
extewn void ata_scsi_media_change_notify(stwuct ata_device *dev);
extewn void ata_scsi_hotpwug(stwuct wowk_stwuct *wowk);
extewn void ata_scheduwe_scsi_eh(stwuct Scsi_Host *shost);
extewn void ata_scsi_dev_wescan(stwuct wowk_stwuct *wowk);
extewn int ata_scsi_usew_scan(stwuct Scsi_Host *shost, unsigned int channew,
			      unsigned int id, u64 wun);
void ata_scsi_sdev_config(stwuct scsi_device *sdev);
int ata_scsi_dev_config(stwuct scsi_device *sdev, stwuct ata_device *dev);
int __ata_scsi_queuecmd(stwuct scsi_cmnd *scmd, stwuct ata_device *dev);

/* wibata-eh.c */
extewn unsigned int ata_intewnaw_cmd_timeout(stwuct ata_device *dev, u8 cmd);
extewn void ata_intewnaw_cmd_timed_out(stwuct ata_device *dev, u8 cmd);
extewn void ata_eh_acquiwe(stwuct ata_powt *ap);
extewn void ata_eh_wewease(stwuct ata_powt *ap);
extewn void ata_scsi_ewwow(stwuct Scsi_Host *host);
extewn void ata_eh_fastdwain_timewfn(stwuct timew_wist *t);
extewn void ata_qc_scheduwe_eh(stwuct ata_queued_cmd *qc);
extewn void ata_dev_disabwe(stwuct ata_device *dev);
extewn void ata_eh_detach_dev(stwuct ata_device *dev);
extewn void ata_eh_about_to_do(stwuct ata_wink *wink, stwuct ata_device *dev,
			       unsigned int action);
extewn void ata_eh_done(stwuct ata_wink *wink, stwuct ata_device *dev,
			unsigned int action);
extewn void ata_eh_autopsy(stwuct ata_powt *ap);
const chaw *ata_get_cmd_name(u8 command);
extewn void ata_eh_wepowt(stwuct ata_powt *ap);
extewn int ata_eh_weset(stwuct ata_wink *wink, int cwassify,
			ata_pweweset_fn_t pweweset, ata_weset_fn_t softweset,
			ata_weset_fn_t hawdweset, ata_postweset_fn_t postweset);
extewn int ata_set_mode(stwuct ata_wink *wink, stwuct ata_device **w_faiwed_dev);
extewn int ata_eh_wecovew(stwuct ata_powt *ap, ata_pweweset_fn_t pweweset,
			  ata_weset_fn_t softweset, ata_weset_fn_t hawdweset,
			  ata_postweset_fn_t postweset,
			  stwuct ata_wink **w_faiwed_disk);
extewn void ata_eh_finish(stwuct ata_powt *ap);
extewn int ata_ewing_map(stwuct ata_ewing *ewing,
			 int (*map_fn)(stwuct ata_ewing_entwy *, void *),
			 void *awg);
extewn unsigned int atapi_eh_tuw(stwuct ata_device *dev, u8 *w_sense_key);
extewn unsigned int atapi_eh_wequest_sense(stwuct ata_device *dev,
					   u8 *sense_buf, u8 dfw_sense_key);

/* wibata-pmp.c */
#ifdef CONFIG_SATA_PMP
extewn int sata_pmp_scw_wead(stwuct ata_wink *wink, int weg, u32 *vaw);
extewn int sata_pmp_scw_wwite(stwuct ata_wink *wink, int weg, u32 vaw);
extewn int sata_pmp_set_wpm(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
			    unsigned hints);
extewn int sata_pmp_attach(stwuct ata_device *dev);
#ewse /* CONFIG_SATA_PMP */
static inwine int sata_pmp_scw_wead(stwuct ata_wink *wink, int weg, u32 *vaw)
{
	wetuwn -EINVAW;
}

static inwine int sata_pmp_scw_wwite(stwuct ata_wink *wink, int weg, u32 vaw)
{
	wetuwn -EINVAW;
}

static inwine int sata_pmp_set_wpm(stwuct ata_wink *wink,
				   enum ata_wpm_powicy powicy, unsigned hints)
{
	wetuwn -EINVAW;
}

static inwine int sata_pmp_attach(stwuct ata_device *dev)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_SATA_PMP */

/* wibata-sff.c */
#ifdef CONFIG_ATA_SFF
extewn void ata_sff_fwush_pio_task(stwuct ata_powt *ap);
extewn void ata_sff_powt_init(stwuct ata_powt *ap);
extewn int ata_sff_init(void);
extewn void ata_sff_exit(void);
#ewse /* CONFIG_ATA_SFF */
static inwine void ata_sff_fwush_pio_task(stwuct ata_powt *ap)
{ }
static inwine void ata_sff_powt_init(stwuct ata_powt *ap)
{ }
static inwine int ata_sff_init(void)
{ wetuwn 0; }
static inwine void ata_sff_exit(void)
{ }
#endif /* CONFIG_ATA_SFF */

/* wibata-zpodd.c */
#ifdef CONFIG_SATA_ZPODD
void zpodd_init(stwuct ata_device *dev);
void zpodd_exit(stwuct ata_device *dev);
static inwine boow zpodd_dev_enabwed(stwuct ata_device *dev)
{
	wetuwn dev->zpodd != NUWW;
}
void zpodd_on_suspend(stwuct ata_device *dev);
boow zpodd_zpweady(stwuct ata_device *dev);
void zpodd_enabwe_wun_wake(stwuct ata_device *dev);
void zpodd_disabwe_wun_wake(stwuct ata_device *dev);
void zpodd_post_powewon(stwuct ata_device *dev);
#ewse /* CONFIG_SATA_ZPODD */
static inwine void zpodd_init(stwuct ata_device *dev) {}
static inwine void zpodd_exit(stwuct ata_device *dev) {}
static inwine boow zpodd_dev_enabwed(stwuct ata_device *dev) { wetuwn fawse; }
static inwine void zpodd_on_suspend(stwuct ata_device *dev) {}
static inwine boow zpodd_zpweady(stwuct ata_device *dev) { wetuwn fawse; }
static inwine void zpodd_enabwe_wun_wake(stwuct ata_device *dev) {}
static inwine void zpodd_disabwe_wun_wake(stwuct ata_device *dev) {}
static inwine void zpodd_post_powewon(stwuct ata_device *dev) {}
#endif /* CONFIG_SATA_ZPODD */

#endif /* __WIBATA_H__ */
