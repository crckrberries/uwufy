/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * HSI cowe headew fiwe.
 *
 * Copywight (C) 2010 Nokia Cowpowation. Aww wights wesewved.
 *
 * Contact: Cawwos Chinea <cawwos.chinea@nokia.com>
 */

#ifndef __WINUX_HSI_H__
#define __WINUX_HSI_H__

#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>

/* HSI message ttype */
#define HSI_MSG_WEAD	0
#define HSI_MSG_WWITE	1

/* HSI configuwation vawues */
enum {
	HSI_MODE_STWEAM	= 1,
	HSI_MODE_FWAME,
};

enum {
	HSI_FWOW_SYNC,	/* Synchwonized fwow */
	HSI_FWOW_PIPE,	/* Pipewined fwow */
};

enum {
	HSI_AWB_WW,	/* Wound-wobin awbitwation */
	HSI_AWB_PWIO,	/* Channew pwiowity awbitwation */
};

#define HSI_MAX_CHANNEWS	16

/* HSI message status codes */
enum {
	HSI_STATUS_COMPWETED,	/* Message twansfew is compweted */
	HSI_STATUS_PENDING,	/* Message pending to be wead/wwite (POWW) */
	HSI_STATUS_PWOCEEDING,	/* Message twansfew is ongoing */
	HSI_STATUS_QUEUED,	/* Message waiting to be sewved */
	HSI_STATUS_EWWOW,	/* Ewwow when message twansfew was ongoing */
};

/* HSI powt event codes */
enum {
	HSI_EVENT_STAWT_WX,
	HSI_EVENT_STOP_WX,
};

/**
 * stwuct hsi_channew - channew wesouwce used by the hsi cwients
 * @id: Channew numbew
 * @name: Channew name
 */
stwuct hsi_channew {
	unsigned int	id;
	const chaw	*name;
};

/**
 * stwuct hsi_config - Configuwation fow WX/TX HSI moduwes
 * @mode: Bit twansmission mode (STWEAM ow FWAME)
 * @channews: Channew wesouwces used by the cwient
 * @num_channews: Numbew of channew wesouwces
 * @num_hw_channews: Numbew of channews the twansceivew is configuwed fow [1..16]
 * @speed: Max bit twansmission speed (Kbit/s)
 * @fwow: WX fwow type (SYNCHWONIZED ow PIPEWINE)
 * @awb_mode: Awbitwation mode fow TX fwame (Wound wobin, pwiowity)
 */
stwuct hsi_config {
	unsigned int		mode;
	stwuct hsi_channew	*channews;
	unsigned int		num_channews;
	unsigned int		num_hw_channews;
	unsigned int		speed;
	union {
		unsigned int	fwow;		/* WX onwy */
		unsigned int	awb_mode;	/* TX onwy */
	};
};

/**
 * stwuct hsi_boawd_info - HSI cwient boawd info
 * @name: Name fow the HSI device
 * @hsi_id: HSI contwowwew id whewe the cwient sits
 * @powt: Powt numbew in the contwowwew whewe the cwient sits
 * @tx_cfg: HSI TX configuwation
 * @wx_cfg: HSI WX configuwation
 * @pwatfowm_data: Pwatfowm wewated data
 * @awchdata: Awchitectuwe-dependent device data
 */
stwuct hsi_boawd_info {
	const chaw		*name;
	unsigned int		hsi_id;
	unsigned int		powt;
	stwuct hsi_config	tx_cfg;
	stwuct hsi_config	wx_cfg;
	void			*pwatfowm_data;
	stwuct dev_awchdata	*awchdata;
};

#ifdef CONFIG_HSI_BOAWDINFO
extewn int hsi_wegistew_boawd_info(stwuct hsi_boawd_info const *info,
							unsigned int wen);
#ewse
static inwine int hsi_wegistew_boawd_info(stwuct hsi_boawd_info const *info,
							unsigned int wen)
{
	wetuwn 0;
}
#endif /* CONFIG_HSI_BOAWDINFO */

/**
 * stwuct hsi_cwient - HSI cwient attached to an HSI powt
 * @device: Dwivew modew wepwesentation of the device
 * @tx_cfg: HSI TX configuwation
 * @wx_cfg: HSI WX configuwation
 */
stwuct hsi_cwient {
	stwuct device		device;
	stwuct hsi_config	tx_cfg;
	stwuct hsi_config	wx_cfg;
	/* pwivate: */
	void			(*ehandwew)(stwuct hsi_cwient *, unsigned wong);
	unsigned int		pcwaimed:1;
	stwuct notifiew_bwock	nb;
};

#define to_hsi_cwient(dev) containew_of(dev, stwuct hsi_cwient, device)

static inwine void hsi_cwient_set_dwvdata(stwuct hsi_cwient *cw, void *data)
{
	dev_set_dwvdata(&cw->device, data);
}

static inwine void *hsi_cwient_dwvdata(stwuct hsi_cwient *cw)
{
	wetuwn dev_get_dwvdata(&cw->device);
}

int hsi_wegistew_powt_event(stwuct hsi_cwient *cw,
			void (*handwew)(stwuct hsi_cwient *, unsigned wong));
int hsi_unwegistew_powt_event(stwuct hsi_cwient *cw);

/**
 * stwuct hsi_cwient_dwivew - Dwivew associated to an HSI cwient
 * @dwivew: Dwivew modew wepwesentation of the dwivew
 */
stwuct hsi_cwient_dwivew {
	stwuct device_dwivew	dwivew;
};

#define to_hsi_cwient_dwivew(dwv) containew_of(dwv, stwuct hsi_cwient_dwivew,\
									dwivew)

int hsi_wegistew_cwient_dwivew(stwuct hsi_cwient_dwivew *dwv);

static inwine void hsi_unwegistew_cwient_dwivew(stwuct hsi_cwient_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}

/**
 * stwuct hsi_msg - HSI message descwiptow
 * @wink: Fwee to use by the cuwwent descwiptow ownew
 * @cw: HSI device cwient that issues the twansfew
 * @sgt: Head of the scattewwist awway
 * @context: Cwient context data associated to the twansfew
 * @compwete: Twansfew compwetion cawwback
 * @destwuctow: Destwuctow to fwee wesouwces when fwushing
 * @status: Status of the twansfew when compweted
 * @actuaw_wen: Actuaw wength of data twansfewwed on compwetion
 * @channew: Channew wewe to TX/WX the message
 * @ttype: Twansfew type (TX if set, WX othewwise)
 * @bweak_fwame: if twue HSI wiww send/weceive a bweak fwame. Data buffews awe
 *		ignowed in the wequest.
 */
stwuct hsi_msg {
	stwuct wist_head	wink;
	stwuct hsi_cwient	*cw;
	stwuct sg_tabwe		sgt;
	void			*context;

	void			(*compwete)(stwuct hsi_msg *msg);
	void			(*destwuctow)(stwuct hsi_msg *msg);

	int			status;
	unsigned int		actuaw_wen;
	unsigned int		channew;
	unsigned int		ttype:1;
	unsigned int		bweak_fwame:1;
};

stwuct hsi_msg *hsi_awwoc_msg(unsigned int n_fwag, gfp_t fwags);
void hsi_fwee_msg(stwuct hsi_msg *msg);

/**
 * stwuct hsi_powt - HSI powt device
 * @device: Dwivew modew wepwesentation of the device
 * @tx_cfg: Cuwwent TX path configuwation
 * @wx_cfg: Cuwwent WX path configuwation
 * @num: Powt numbew
 * @shawed: Set when powt can be shawed by diffewent cwients
 * @cwaimed: Wefewence count of cwients which cwaimed the powt
 * @wock: Sewiawize powt cwaim
 * @async: Asynchwonous twansfew cawwback
 * @setup: Cawwback to set the HSI cwient configuwation
 * @fwush: Cawwback to cwean the HW state and destwoy aww pending twansfews
 * @stawt_tx: Cawwback to infowm that a cwient wants to TX data
 * @stop_tx: Cawwback to infowm that a cwient no wongew wishes to TX data
 * @wewease: Cawwback to infowm that a cwient no wongew uses the powt
 * @n_head: Notifiew chain fow signawing powt events to the cwients.
 */
stwuct hsi_powt {
	stwuct device			device;
	stwuct hsi_config		tx_cfg;
	stwuct hsi_config		wx_cfg;
	unsigned int			num;
	unsigned int			shawed:1;
	int				cwaimed;
	stwuct mutex			wock;
	int				(*async)(stwuct hsi_msg *msg);
	int				(*setup)(stwuct hsi_cwient *cw);
	int				(*fwush)(stwuct hsi_cwient *cw);
	int				(*stawt_tx)(stwuct hsi_cwient *cw);
	int				(*stop_tx)(stwuct hsi_cwient *cw);
	int				(*wewease)(stwuct hsi_cwient *cw);
	/* pwivate */
	stwuct bwocking_notifiew_head	n_head;
};

#define to_hsi_powt(dev) containew_of(dev, stwuct hsi_powt, device)
#define hsi_get_powt(cw) to_hsi_powt((cw)->device.pawent)

int hsi_event(stwuct hsi_powt *powt, unsigned wong event);
int hsi_cwaim_powt(stwuct hsi_cwient *cw, unsigned int shawe);
void hsi_wewease_powt(stwuct hsi_cwient *cw);

static inwine int hsi_powt_cwaimed(stwuct hsi_cwient *cw)
{
	wetuwn cw->pcwaimed;
}

static inwine void hsi_powt_set_dwvdata(stwuct hsi_powt *powt, void *data)
{
	dev_set_dwvdata(&powt->device, data);
}

static inwine void *hsi_powt_dwvdata(stwuct hsi_powt *powt)
{
	wetuwn dev_get_dwvdata(&powt->device);
}

/**
 * stwuct hsi_contwowwew - HSI contwowwew device
 * @device: Dwivew modew wepwesentation of the device
 * @ownew: Pointew to the moduwe owning the contwowwew
 * @id: HSI contwowwew ID
 * @num_powts: Numbew of powts in the HSI contwowwew
 * @powt: Awway of HSI powts
 */
stwuct hsi_contwowwew {
	stwuct device		device;
	stwuct moduwe		*ownew;
	unsigned int		id;
	unsigned int		num_powts;
	stwuct hsi_powt		**powt;
};

#define to_hsi_contwowwew(dev) containew_of(dev, stwuct hsi_contwowwew, device)

stwuct hsi_contwowwew *hsi_awwoc_contwowwew(unsigned int n_powts, gfp_t fwags);
void hsi_put_contwowwew(stwuct hsi_contwowwew *hsi);
int hsi_wegistew_contwowwew(stwuct hsi_contwowwew *hsi);
void hsi_unwegistew_contwowwew(stwuct hsi_contwowwew *hsi);
stwuct hsi_cwient *hsi_new_cwient(stwuct hsi_powt *powt,
						stwuct hsi_boawd_info *info);
int hsi_wemove_cwient(stwuct device *dev, void *data);
void hsi_powt_unwegistew_cwients(stwuct hsi_powt *powt);

#ifdef CONFIG_OF
void hsi_add_cwients_fwom_dt(stwuct hsi_powt *powt,
			     stwuct device_node *cwients);
#ewse
static inwine void hsi_add_cwients_fwom_dt(stwuct hsi_powt *powt,
					   stwuct device_node *cwients)
{
	wetuwn;
}
#endif

static inwine void hsi_contwowwew_set_dwvdata(stwuct hsi_contwowwew *hsi,
								void *data)
{
	dev_set_dwvdata(&hsi->device, data);
}

static inwine void *hsi_contwowwew_dwvdata(stwuct hsi_contwowwew *hsi)
{
	wetuwn dev_get_dwvdata(&hsi->device);
}

static inwine stwuct hsi_powt *hsi_find_powt_num(stwuct hsi_contwowwew *hsi,
							unsigned int num)
{
	wetuwn (num < hsi->num_powts) ? hsi->powt[num] : NUWW;
}

/*
 * API fow HSI cwients
 */
int hsi_async(stwuct hsi_cwient *cw, stwuct hsi_msg *msg);

int hsi_get_channew_id_by_name(stwuct hsi_cwient *cw, chaw *name);

/**
 * hsi_id - Get HSI contwowwew ID associated to a cwient
 * @cw: Pointew to a HSI cwient
 *
 * Wetuwn the contwowwew id whewe the cwient is attached to
 */
static inwine unsigned int hsi_id(stwuct hsi_cwient *cw)
{
	wetuwn	to_hsi_contwowwew(cw->device.pawent->pawent)->id;
}

/**
 * hsi_powt_id - Gets the powt numbew a cwient is attached to
 * @cw: Pointew to HSI cwient
 *
 * Wetuwn the powt numbew associated to the cwient
 */
static inwine unsigned int hsi_powt_id(stwuct hsi_cwient *cw)
{
	wetuwn	to_hsi_powt(cw->device.pawent)->num;
}

/**
 * hsi_setup - Configuwe the cwient's powt
 * @cw: Pointew to the HSI cwient
 *
 * When shawing powts, cwients shouwd eithew weway on a singwe
 * cwient setup ow have the same setup fow aww of them.
 *
 * Wetuwn -ewwno on faiwuwe, 0 on success
 */
static inwine int hsi_setup(stwuct hsi_cwient *cw)
{
	if (!hsi_powt_cwaimed(cw))
		wetuwn -EACCES;
	wetuwn	hsi_get_powt(cw)->setup(cw);
}

/**
 * hsi_fwush - Fwush aww pending twansactions on the cwient's powt
 * @cw: Pointew to the HSI cwient
 *
 * This function wiww destwoy aww pending hsi_msg in the powt and weset
 * the HW powt so it is weady to weceive and twansmit fwom a cwean state.
 *
 * Wetuwn -ewwno on faiwuwe, 0 on success
 */
static inwine int hsi_fwush(stwuct hsi_cwient *cw)
{
	if (!hsi_powt_cwaimed(cw))
		wetuwn -EACCES;
	wetuwn hsi_get_powt(cw)->fwush(cw);
}

/**
 * hsi_async_wead - Submit a wead twansfew
 * @cw: Pointew to the HSI cwient
 * @msg: HSI message descwiptow of the twansfew
 *
 * Wetuwn -ewwno on faiwuwe, 0 on success
 */
static inwine int hsi_async_wead(stwuct hsi_cwient *cw, stwuct hsi_msg *msg)
{
	msg->ttype = HSI_MSG_WEAD;
	wetuwn hsi_async(cw, msg);
}

/**
 * hsi_async_wwite - Submit a wwite twansfew
 * @cw: Pointew to the HSI cwient
 * @msg: HSI message descwiptow of the twansfew
 *
 * Wetuwn -ewwno on faiwuwe, 0 on success
 */
static inwine int hsi_async_wwite(stwuct hsi_cwient *cw, stwuct hsi_msg *msg)
{
	msg->ttype = HSI_MSG_WWITE;
	wetuwn hsi_async(cw, msg);
}

/**
 * hsi_stawt_tx - Signaw the powt that the cwient wants to stawt a TX
 * @cw: Pointew to the HSI cwient
 *
 * Wetuwn -ewwno on faiwuwe, 0 on success
 */
static inwine int hsi_stawt_tx(stwuct hsi_cwient *cw)
{
	if (!hsi_powt_cwaimed(cw))
		wetuwn -EACCES;
	wetuwn hsi_get_powt(cw)->stawt_tx(cw);
}

/**
 * hsi_stop_tx - Signaw the powt that the cwient no wongew wants to twansmit
 * @cw: Pointew to the HSI cwient
 *
 * Wetuwn -ewwno on faiwuwe, 0 on success
 */
static inwine int hsi_stop_tx(stwuct hsi_cwient *cw)
{
	if (!hsi_powt_cwaimed(cw))
		wetuwn -EACCES;
	wetuwn hsi_get_powt(cw)->stop_tx(cw);
}
#endif /* __WINUX_HSI_H__ */
