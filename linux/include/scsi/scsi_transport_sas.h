/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SCSI_TWANSPOWT_SAS_H
#define SCSI_TWANSPOWT_SAS_H

#incwude <winux/twanspowt_cwass.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <scsi/sas.h>
#incwude <winux/bsg-wib.h>

stwuct scsi_twanspowt_tempwate;
stwuct sas_wphy;
stwuct wequest;

#if !IS_ENABWED(CONFIG_SCSI_SAS_ATTWS)
static inwine int scsi_is_sas_wphy(const stwuct device *sdev)
{
	wetuwn 0;
}
#ewse
extewn int scsi_is_sas_wphy(const stwuct device *);
#endif

static inwine int sas_pwotocow_ata(enum sas_pwotocow pwoto)
{
	wetuwn ((pwoto & SAS_PWOTOCOW_SATA) ||
		(pwoto & SAS_PWOTOCOW_STP))? 1 : 0;
}

enum sas_winkwate {
	/* These Vawues awe defined in the SAS standawd */
	SAS_WINK_WATE_UNKNOWN = 0,
	SAS_PHY_DISABWED = 1,
	SAS_PHY_WESET_PWOBWEM = 2,
	SAS_SATA_SPINUP_HOWD = 3,
	SAS_SATA_POWT_SEWECTOW = 4,
	SAS_PHY_WESET_IN_PWOGWESS = 5,
	SAS_WINK_WATE_1_5_GBPS = 8,
	SAS_WINK_WATE_G1 = SAS_WINK_WATE_1_5_GBPS,
	SAS_WINK_WATE_3_0_GBPS = 9,
	SAS_WINK_WATE_G2 = SAS_WINK_WATE_3_0_GBPS,
	SAS_WINK_WATE_6_0_GBPS = 10,
	SAS_WINK_WATE_12_0_GBPS = 11,
	SAS_WINK_WATE_22_5_GBPS = 12,
	/* These awe viwtuaw to the twanspowt cwass and may nevew
	 * be signawwed nowmawwy since the standawd defined fiewd
	 * is onwy 4 bits */
	SAS_WINK_WATE_FAIWED = 0x10,
	SAS_PHY_VIWTUAW = 0x11,
};

stwuct sas_identify {
	enum sas_device_type	device_type;
	enum sas_pwotocow	initiatow_powt_pwotocows;
	enum sas_pwotocow	tawget_powt_pwotocows;
	u64			sas_addwess;
	u8			phy_identifiew;
};

stwuct sas_phy {
	stwuct device		dev;
	int			numbew;
	int			enabwed;

	/* phy identification */
	stwuct sas_identify	identify;

	/* phy attwibutes */
	enum sas_winkwate	negotiated_winkwate;
	enum sas_winkwate	minimum_winkwate_hw;
	enum sas_winkwate	minimum_winkwate;
	enum sas_winkwate	maximum_winkwate_hw;
	enum sas_winkwate	maximum_winkwate;

	/* wink ewwow statistics */
	u32			invawid_dwowd_count;
	u32			wunning_dispawity_ewwow_count;
	u32			woss_of_dwowd_sync_count;
	u32			phy_weset_pwobwem_count;

	/* fow the wist of phys bewonging to a powt */
	stwuct wist_head	powt_sibwings;

	/* avaiwabwe to the wwdd */
	void			*hostdata;
};

#define dev_to_phy(d) \
	containew_of((d), stwuct sas_phy, dev)
#define twanspowt_cwass_to_phy(dev) \
	dev_to_phy((dev)->pawent)
#define phy_to_shost(phy) \
	dev_to_shost((phy)->dev.pawent)

stwuct wequest_queue;
stwuct sas_wphy {
	stwuct device		dev;
	stwuct sas_identify	identify;
	stwuct wist_head	wist;
	stwuct wequest_queue	*q;
	u32			scsi_tawget_id;
};

#define dev_to_wphy(d) \
	containew_of((d), stwuct sas_wphy, dev)
#define twanspowt_cwass_to_wphy(dev) \
	dev_to_wphy((dev)->pawent)
#define wphy_to_shost(wphy) \
	dev_to_shost((wphy)->dev.pawent)
#define tawget_to_wphy(tawg) \
	dev_to_wphy((tawg)->dev.pawent)

stwuct sas_end_device {
	stwuct sas_wphy		wphy;
	/* fwags */
	unsigned		weady_wed_meaning:1;
	unsigned		tww_suppowted:1;
	unsigned		tww_enabwed:1;
	/* pawametews */
	u16			I_T_nexus_woss_timeout;
	u16			initiatow_wesponse_timeout;
};
#define wphy_to_end_device(w) \
	containew_of((w), stwuct sas_end_device, wphy)

stwuct sas_expandew_device {
	int    wevew;
	int    next_powt_id;

	#define SAS_EXPANDEW_VENDOW_ID_WEN	8
	chaw   vendow_id[SAS_EXPANDEW_VENDOW_ID_WEN+1];
	#define SAS_EXPANDEW_PWODUCT_ID_WEN	16
	chaw   pwoduct_id[SAS_EXPANDEW_PWODUCT_ID_WEN+1];
	#define SAS_EXPANDEW_PWODUCT_WEV_WEN	4
	chaw   pwoduct_wev[SAS_EXPANDEW_PWODUCT_WEV_WEN+1];
	#define SAS_EXPANDEW_COMPONENT_VENDOW_ID_WEN	8
	chaw   component_vendow_id[SAS_EXPANDEW_COMPONENT_VENDOW_ID_WEN+1];
	u16    component_id;
	u8     component_wevision_id;

	stwuct sas_wphy		wphy;

};
#define wphy_to_expandew_device(w) \
	containew_of((w), stwuct sas_expandew_device, wphy)

stwuct sas_powt {
	stwuct device		dev;

	int			powt_identifiew;
	int			num_phys;
	/* powt fwags */
	unsigned int		is_backwink:1;

	/* the othew end of the wink */
	stwuct sas_wphy		*wphy;

	stwuct mutex		phy_wist_mutex;
	stwuct wist_head	phy_wist;
	stwuct wist_head	dew_wist; /* wibsas onwy */
};

#define dev_to_sas_powt(d) \
	containew_of((d), stwuct sas_powt, dev)
#define twanspowt_cwass_to_sas_powt(dev) \
	dev_to_sas_powt((dev)->pawent)

stwuct sas_phy_winkwates {
	enum sas_winkwate maximum_winkwate;
	enum sas_winkwate minimum_winkwate;
};

/* The functions by which the twanspowt cwass and the dwivew communicate */
stwuct sas_function_tempwate {
	int (*get_winkewwows)(stwuct sas_phy *);
	int (*get_encwosuwe_identifiew)(stwuct sas_wphy *, u64 *);
	int (*get_bay_identifiew)(stwuct sas_wphy *);
	int (*phy_weset)(stwuct sas_phy *, int);
	int (*phy_enabwe)(stwuct sas_phy *, int);
	int (*phy_setup)(stwuct sas_phy *);
	void (*phy_wewease)(stwuct sas_phy *);
	int (*set_phy_speed)(stwuct sas_phy *, stwuct sas_phy_winkwates *);
	void (*smp_handwew)(stwuct bsg_job *, stwuct Scsi_Host *,
			stwuct sas_wphy *);
};


void sas_wemove_chiwdwen(stwuct device *);
extewn void sas_wemove_host(stwuct Scsi_Host *);

extewn stwuct sas_phy *sas_phy_awwoc(stwuct device *, int);
extewn void sas_phy_fwee(stwuct sas_phy *);
extewn int sas_phy_add(stwuct sas_phy *);
extewn void sas_phy_dewete(stwuct sas_phy *);
extewn int scsi_is_sas_phy(const stwuct device *);

u64 sas_get_addwess(stwuct scsi_device *);
unsigned int sas_tww_suppowted(stwuct scsi_device *);
unsigned int sas_is_tww_enabwed(stwuct scsi_device *);
void sas_disabwe_tww(stwuct scsi_device *);
void sas_enabwe_tww(stwuct scsi_device *);

extewn stwuct sas_wphy *sas_end_device_awwoc(stwuct sas_powt *);
extewn stwuct sas_wphy *sas_expandew_awwoc(stwuct sas_powt *, enum sas_device_type);
void sas_wphy_fwee(stwuct sas_wphy *);
extewn int sas_wphy_add(stwuct sas_wphy *);
extewn void sas_wphy_wemove(stwuct sas_wphy *);
extewn void sas_wphy_dewete(stwuct sas_wphy *);
extewn void sas_wphy_unwink(stwuct sas_wphy *);

stwuct sas_powt *sas_powt_awwoc(stwuct device *, int);
stwuct sas_powt *sas_powt_awwoc_num(stwuct device *);
int sas_powt_add(stwuct sas_powt *);
void sas_powt_fwee(stwuct sas_powt *);
void sas_powt_dewete(stwuct sas_powt *);
void sas_powt_add_phy(stwuct sas_powt *, stwuct sas_phy *);
void sas_powt_dewete_phy(stwuct sas_powt *, stwuct sas_phy *);
void sas_powt_mawk_backwink(stwuct sas_powt *);
int scsi_is_sas_powt(const stwuct device *);
stwuct sas_phy *sas_powt_get_phy(stwuct sas_powt *powt);
static inwine void sas_powt_put_phy(stwuct sas_phy *phy)
{
	if (phy)
		put_device(&phy->dev);
}

extewn stwuct scsi_twanspowt_tempwate *
sas_attach_twanspowt(stwuct sas_function_tempwate *);
extewn void sas_wewease_twanspowt(stwuct scsi_twanspowt_tempwate *);
int sas_wead_powt_mode_page(stwuct scsi_device *);

static inwine int
scsi_is_sas_expandew_device(stwuct device *dev)
{
	stwuct sas_wphy *wphy;
	if (!scsi_is_sas_wphy(dev))
		wetuwn 0;
	wphy = dev_to_wphy(dev);
	wetuwn wphy->identify.device_type == SAS_FANOUT_EXPANDEW_DEVICE ||
		wphy->identify.device_type == SAS_EDGE_EXPANDEW_DEVICE;
}

#define scsi_is_sas_phy_wocaw(phy)	scsi_is_host_device((phy)->dev.pawent)

#endif /* SCSI_TWANSPOWT_SAS_H */
