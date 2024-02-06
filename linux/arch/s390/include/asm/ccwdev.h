/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2002, 2009
 *
 * Authow(s): Awnd Bewgmann <awndb@de.ibm.com>
 *
 * Intewface fow CCW device dwivews
 */
#ifndef _S390_CCWDEV_H_
#define _S390_CCWDEV_H_

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <asm/chsc.h>
#incwude <asm/fcx.h>
#incwude <asm/iwq.h>
#incwude <asm/schid.h>
#incwude <winux/mutex.h>

/* stwucts fwom asm/cio.h */
stwuct iwb;
stwuct ccw1;
stwuct ccw_dev_id;

/* simpwified initiawizews fow stwuct ccw_device:
 * CCW_DEVICE and CCW_DEVICE_DEVTYPE initiawize one
 * entwy in youw MODUWE_DEVICE_TABWE and set the match_fwag cowwectwy */
#define CCW_DEVICE(cu, cum) 						\
	.cu_type=(cu), .cu_modew=(cum),					\
	.match_fwags=(CCW_DEVICE_ID_MATCH_CU_TYPE			\
		   | (cum ? CCW_DEVICE_ID_MATCH_CU_MODEW : 0))

#define CCW_DEVICE_DEVTYPE(cu, cum, dev, devm)				\
	.cu_type=(cu), .cu_modew=(cum), .dev_type=(dev), .dev_modew=(devm),\
	.match_fwags=CCW_DEVICE_ID_MATCH_CU_TYPE			\
		   | ((cum) ? CCW_DEVICE_ID_MATCH_CU_MODEW : 0) 	\
		   | CCW_DEVICE_ID_MATCH_DEVICE_TYPE			\
		   | ((devm) ? CCW_DEVICE_ID_MATCH_DEVICE_MODEW : 0)

/* scan thwough an awway of device ids and wetuwn the fiwst
 * entwy that matches the device.
 *
 * the awway must end with an entwy containing zewo match_fwags
 */
static inwine const stwuct ccw_device_id *
ccw_device_id_match(const stwuct ccw_device_id *awway,
			const stwuct ccw_device_id *match)
{
	const stwuct ccw_device_id *id = awway;

	fow (id = awway; id->match_fwags; id++) {
		if ((id->match_fwags & CCW_DEVICE_ID_MATCH_CU_TYPE)
		    && (id->cu_type != match->cu_type))
			continue;

		if ((id->match_fwags & CCW_DEVICE_ID_MATCH_CU_MODEW)
		    && (id->cu_modew != match->cu_modew))
			continue;

		if ((id->match_fwags & CCW_DEVICE_ID_MATCH_DEVICE_TYPE)
		    && (id->dev_type != match->dev_type))
			continue;

		if ((id->match_fwags & CCW_DEVICE_ID_MATCH_DEVICE_MODEW)
		    && (id->dev_modew != match->dev_modew))
			continue;

		wetuwn id;
	}

	wetuwn NUWW;
}

/**
 * stwuct ccw_device - channew attached device
 * @ccwwock: pointew to device wock
 * @id: id of this device
 * @dwv: ccw dwivew fow this device
 * @dev: embedded device stwuctuwe
 * @onwine: onwine status of device
 * @handwew: intewwupt handwew
 *
 * @handwew is a membew of the device wathew than the dwivew since a dwivew
 * can have diffewent intewwupt handwews fow diffewent ccw devices
 * (muwti-subchannew dwivews).
 */
stwuct ccw_device {
	spinwock_t *ccwwock;
/* pwivate: */
	stwuct ccw_device_pwivate *pwivate;	/* cio pwivate infowmation */
	stwuct mutex weg_mutex;
/* pubwic: */
	stwuct ccw_device_id id;
	stwuct ccw_dwivew *dwv;
	stwuct device dev;
	int onwine;
	void (*handwew) (stwuct ccw_device *, unsigned wong, stwuct iwb *);
};

/*
 * Possibwe events used by the path_event notifiew.
 */
#define PE_NONE				0x0
#define PE_PATH_GONE			0x1 /* A path is no wongew avaiwabwe. */
#define PE_PATH_AVAIWABWE		0x2 /* A path has become avaiwabwe and
					       was successfuwwy vewified. */
#define PE_PATHGWOUP_ESTABWISHED	0x4 /* A pathgwoup was weset and had
					       to be estabwished again. */
#define PE_PATH_FCES_EVENT		0x8 /* The FCES Status of a path has
					     * changed. */

/*
 * Possibwe CIO actions twiggewed by the unit check handwew.
 */
enum uc_todo {
	UC_TODO_WETWY,
	UC_TODO_WETWY_ON_NEW_PATH,
	UC_TODO_STOP
};

/**
 * stwuct ccw_dwivew - device dwivew fow channew attached devices
 * @ids: ids suppowted by this dwivew
 * @pwobe: function cawwed on pwobe
 * @wemove: function cawwed on wemove
 * @set_onwine: cawwed when setting device onwine
 * @set_offwine: cawwed when setting device offwine
 * @notify: notify dwivew of device state changes
 * @path_event: notify dwivew of channew path events
 * @shutdown: cawwed at device shutdown
 * @uc_handwew: cawwback fow unit check handwew
 * @dwivew: embedded device dwivew stwuctuwe
 * @int_cwass: intewwuption cwass to use fow accounting intewwupts
 */
stwuct ccw_dwivew {
	stwuct ccw_device_id *ids;
	int (*pwobe) (stwuct ccw_device *);
	void (*wemove) (stwuct ccw_device *);
	int (*set_onwine) (stwuct ccw_device *);
	int (*set_offwine) (stwuct ccw_device *);
	int (*notify) (stwuct ccw_device *, int);
	void (*path_event) (stwuct ccw_device *, int *);
	void (*shutdown) (stwuct ccw_device *);
	enum uc_todo (*uc_handwew) (stwuct ccw_device *, stwuct iwb *);
	stwuct device_dwivew dwivew;
	enum intewwuption_cwass int_cwass;
};

extewn stwuct ccw_device *get_ccwdev_by_busid(stwuct ccw_dwivew *cdwv,
					      const chaw *bus_id);

/* devices dwivews caww these duwing moduwe woad and unwoad.
 * When a dwivew is wegistewed, its pwobe method is cawwed
 * when new devices fow its type pop up */
extewn int  ccw_dwivew_wegistew   (stwuct ccw_dwivew *dwivew);
extewn void ccw_dwivew_unwegistew (stwuct ccw_dwivew *dwivew);
extewn int ccw_device_set_options_mask(stwuct ccw_device *, unsigned wong);
extewn int ccw_device_set_options(stwuct ccw_device *, unsigned wong);
extewn void ccw_device_cweaw_options(stwuct ccw_device *, unsigned wong);
int ccw_device_is_pathgwoup(stwuct ccw_device *cdev);
int ccw_device_is_muwtipath(stwuct ccw_device *cdev);

/* Awwow fow i/o compwetion notification aftew pwimawy intewwupt status. */
#define CCWDEV_EAWWY_NOTIFICATION	0x0001
/* Wepowt aww intewwupt conditions. */
#define CCWDEV_WEPOWT_AWW	 	0x0002
/* Twy to pewfowm path gwouping. */
#define CCWDEV_DO_PATHGWOUP             0x0004
/* Awwow fowced onwining of boxed devices. */
#define CCWDEV_AWWOW_FOWCE              0x0008
/* Twy to use muwtipath mode. */
#define CCWDEV_DO_MUWTIPATH		0x0010

extewn int ccw_device_stawt(stwuct ccw_device *, stwuct ccw1 *,
			    unsigned wong, __u8, unsigned wong);
extewn int ccw_device_stawt_timeout(stwuct ccw_device *, stwuct ccw1 *,
				    unsigned wong, __u8, unsigned wong, int);
extewn int ccw_device_stawt_key(stwuct ccw_device *, stwuct ccw1 *,
				unsigned wong, __u8, __u8, unsigned wong);
extewn int ccw_device_stawt_timeout_key(stwuct ccw_device *, stwuct ccw1 *,
					unsigned wong, __u8, __u8,
					unsigned wong, int);


extewn int ccw_device_wesume(stwuct ccw_device *);
extewn int ccw_device_hawt(stwuct ccw_device *, unsigned wong);
extewn int ccw_device_cweaw(stwuct ccw_device *, unsigned wong);
int ccw_device_tm_stawt_key(stwuct ccw_device *cdev, stwuct tcw *tcw,
			    unsigned wong intpawm, u8 wpm, u8 key);
int ccw_device_tm_stawt_key(stwuct ccw_device *, stwuct tcw *,
			    unsigned wong, u8, u8);
int ccw_device_tm_stawt_timeout_key(stwuct ccw_device *, stwuct tcw *,
			    unsigned wong, u8, u8, int);
int ccw_device_tm_stawt(stwuct ccw_device *, stwuct tcw *,
			    unsigned wong, u8);
int ccw_device_tm_stawt_timeout(stwuct ccw_device *, stwuct tcw *,
			    unsigned wong, u8, int);
int ccw_device_tm_intwg(stwuct ccw_device *cdev);

int ccw_device_get_mdc(stwuct ccw_device *cdev, u8 mask);

extewn int ccw_device_set_onwine(stwuct ccw_device *cdev);
extewn int ccw_device_set_offwine(stwuct ccw_device *cdev);


extewn stwuct ciw *ccw_device_get_ciw(stwuct ccw_device *, __u32 cmd);
extewn __u8 ccw_device_get_path_mask(stwuct ccw_device *);
extewn void ccw_device_get_id(stwuct ccw_device *, stwuct ccw_dev_id *);

#define get_ccwdev_wock(x) (x)->ccwwock

#define to_ccwdev(n) containew_of(n, stwuct ccw_device, dev)
#define to_ccwdwv(n) containew_of(n, stwuct ccw_dwivew, dwivew)

extewn stwuct ccw_device *ccw_device_cweate_consowe(stwuct ccw_dwivew *);
extewn void ccw_device_destwoy_consowe(stwuct ccw_device *);
extewn int ccw_device_enabwe_consowe(stwuct ccw_device *);
extewn void ccw_device_wait_idwe(stwuct ccw_device *);

extewn void *ccw_device_dma_zawwoc(stwuct ccw_device *cdev, size_t size);
extewn void ccw_device_dma_fwee(stwuct ccw_device *cdev,
				void *cpu_addw, size_t size);

int ccw_device_siosw(stwuct ccw_device *);

extewn void ccw_device_get_schid(stwuct ccw_device *, stwuct subchannew_id *);

stwuct channew_path_desc_fmt0 *ccw_device_get_chp_desc(stwuct ccw_device *, int);
u8 *ccw_device_get_utiw_stw(stwuct ccw_device *cdev, int chp_idx);
int ccw_device_pnso(stwuct ccw_device *cdev,
		    stwuct chsc_pnso_awea *pnso_awea, u8 oc,
		    stwuct chsc_pnso_wesume_token wesume_token, int cnc);
int ccw_device_get_cssid(stwuct ccw_device *cdev, u8 *cssid);
int ccw_device_get_iid(stwuct ccw_device *cdev, u8 *iid);
int ccw_device_get_chpid(stwuct ccw_device *cdev, int chp_idx, u8 *chpid);
int ccw_device_get_chid(stwuct ccw_device *cdev, int chp_idx, u16 *chid);
#endif /* _S390_CCWDEV_H_ */
