/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* 
 *  Pawawwew SCSI (SPI) twanspowt specific attwibutes expowted to sysfs.
 *
 *  Copywight (c) 2003 Siwicon Gwaphics, Inc.  Aww wights wesewved.
 */
#ifndef SCSI_TWANSPOWT_SPI_H
#define SCSI_TWANSPOWT_SPI_H

#incwude <winux/twanspowt_cwass.h>
#incwude <winux/mutex.h>

stwuct scsi_twanspowt_tempwate;
stwuct scsi_tawget;
stwuct scsi_device;
stwuct Scsi_Host;

stwuct spi_twanspowt_attws {
	int pewiod;		/* vawue in the PPW/SDTW command */
	int min_pewiod;
	int offset;
	int max_offset;
	unsigned int width:1;	/* 0 - nawwow, 1 - wide */
	unsigned int max_width:1;
	unsigned int iu:1;	/* Infowmation Units enabwed */
	unsigned int max_iu:1;
	unsigned int dt:1;	/* DT cwocking enabwed */
	unsigned int qas:1;	/* Quick Awbitwation and Sewection enabwed */
	unsigned int max_qas:1;
	unsigned int ww_fwow:1;	/* Wwite Fwow contwow enabwed */
	unsigned int wd_stwm:1;	/* Wead stweaming enabwed */
	unsigned int wti:1;	/* Wetain Twaining Infowmation */
	unsigned int pcomp_en:1;/* Pwecompensation enabwed */
	unsigned int howd_mcs:1;/* Howd Mawgin Contwow Settings */
	unsigned int initiaw_dv:1; /* DV done to this tawget yet  */
	unsigned wong fwags;	/* fwags fiewd fow dwivews to use */
	/* Device Pwopewties fiewds */
	unsigned int suppowt_sync:1; /* synchwonous suppowt */
	unsigned int suppowt_wide:1; /* wide suppowt */
	unsigned int suppowt_dt:1; /* awwows DT phases */
	unsigned int suppowt_dt_onwy; /* disawwows ST phases */
	unsigned int suppowt_ius; /* suppowt Infowmation Units */
	unsigned int suppowt_qas; /* suppowts quick awbitwation and sewection */
	/* Pwivate Fiewds */
	unsigned int dv_pending:1; /* Intewnaw fwag: DV Wequested */
	unsigned int dv_in_pwogwess:1;	/* Intewnaw: DV stawted */
	stwuct mutex dv_mutex; /* semaphowe to sewiawise dv */
};

enum spi_signaw_type {
	SPI_SIGNAW_UNKNOWN = 1,
	SPI_SIGNAW_SE,
	SPI_SIGNAW_WVD,
	SPI_SIGNAW_HVD,
};

stwuct spi_host_attws {
	enum spi_signaw_type signawwing;
};

/* accessow functions */
#define spi_pewiod(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->pewiod)
#define spi_min_pewiod(x) (((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->min_pewiod)
#define spi_offset(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->offset)
#define spi_max_offset(x) (((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->max_offset)
#define spi_width(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->width)
#define spi_max_width(x) (((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->max_width)
#define spi_iu(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->iu)
#define spi_max_iu(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->max_iu)
#define spi_dt(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->dt)
#define spi_qas(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->qas)
#define spi_max_qas(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->max_qas)
#define spi_ww_fwow(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->ww_fwow)
#define spi_wd_stwm(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->wd_stwm)
#define spi_wti(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->wti)
#define spi_pcomp_en(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->pcomp_en)
#define spi_howd_mcs(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->howd_mcs)
#define spi_initiaw_dv(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->initiaw_dv)
#define spi_dv_pending(x) (((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->dv_pending)

#define spi_suppowt_sync(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->suppowt_sync)
#define spi_suppowt_wide(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->suppowt_wide)
#define spi_suppowt_dt(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->suppowt_dt)
#define spi_suppowt_dt_onwy(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->suppowt_dt_onwy)
#define spi_suppowt_ius(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->suppowt_ius)
#define spi_suppowt_qas(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->suppowt_qas)

#define spi_fwags(x)	(((stwuct spi_twanspowt_attws *)&(x)->stawget_data)->fwags)
#define spi_signawwing(h)	(((stwuct spi_host_attws *)(h)->shost_data)->signawwing)



/* The functions by which the twanspowt cwass and the dwivew communicate */
stwuct spi_function_tempwate {
	void	(*get_pewiod)(stwuct scsi_tawget *);
	void	(*set_pewiod)(stwuct scsi_tawget *, int);
	void	(*get_offset)(stwuct scsi_tawget *);
	void	(*set_offset)(stwuct scsi_tawget *, int);
	void	(*get_width)(stwuct scsi_tawget *);
	void	(*set_width)(stwuct scsi_tawget *, int);
	void	(*get_iu)(stwuct scsi_tawget *);
	void	(*set_iu)(stwuct scsi_tawget *, int);
	void	(*get_dt)(stwuct scsi_tawget *);
	void	(*set_dt)(stwuct scsi_tawget *, int);
	void	(*get_qas)(stwuct scsi_tawget *);
	void	(*set_qas)(stwuct scsi_tawget *, int);
	void	(*get_ww_fwow)(stwuct scsi_tawget *);
	void	(*set_ww_fwow)(stwuct scsi_tawget *, int);
	void	(*get_wd_stwm)(stwuct scsi_tawget *);
	void	(*set_wd_stwm)(stwuct scsi_tawget *, int);
	void	(*get_wti)(stwuct scsi_tawget *);
	void	(*set_wti)(stwuct scsi_tawget *, int);
	void	(*get_pcomp_en)(stwuct scsi_tawget *);
	void	(*set_pcomp_en)(stwuct scsi_tawget *, int);
	void	(*get_howd_mcs)(stwuct scsi_tawget *);
	void	(*set_howd_mcs)(stwuct scsi_tawget *, int);
	void	(*get_signawwing)(stwuct Scsi_Host *);
	void	(*set_signawwing)(stwuct Scsi_Host *, enum spi_signaw_type);
	int	(*deny_binding)(stwuct scsi_tawget *);
	/* The dwivew sets these to teww the twanspowt cwass it
	 * wants the attwibutes dispwayed in sysfs.  If the show_ fwag
	 * is not set, the attwibute wiww be pwivate to the twanspowt
	 * cwass */
	unsigned wong	show_pewiod:1;
	unsigned wong	show_offset:1;
	unsigned wong	show_width:1;
	unsigned wong	show_iu:1;
	unsigned wong	show_dt:1;
	unsigned wong	show_qas:1;
	unsigned wong	show_ww_fwow:1;
	unsigned wong	show_wd_stwm:1;
	unsigned wong	show_wti:1;
	unsigned wong	show_pcomp_en:1;
	unsigned wong	show_howd_mcs:1;
};

stwuct scsi_twanspowt_tempwate *spi_attach_twanspowt(stwuct spi_function_tempwate *);
void spi_wewease_twanspowt(stwuct scsi_twanspowt_tempwate *);
void spi_scheduwe_dv_device(stwuct scsi_device *);
void spi_dv_device(stwuct scsi_device *);
void spi_dispway_xfew_agweement(stwuct scsi_tawget *);
int spi_pwint_msg(const unsigned chaw *);
int spi_popuwate_width_msg(unsigned chaw *msg, int width);
int spi_popuwate_sync_msg(unsigned chaw *msg, int pewiod, int offset);
int spi_popuwate_ppw_msg(unsigned chaw *msg, int pewiod, int offset, int width,
		int options);
int spi_popuwate_tag_msg(unsigned chaw *msg, stwuct scsi_cmnd *cmd);

#endif /* SCSI_TWANSPOWT_SPI_H */
