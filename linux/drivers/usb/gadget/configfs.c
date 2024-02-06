// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/configfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/kstwtox.h>
#incwude <winux/nws.h>
#incwude <winux/usb/composite.h>
#incwude <winux/usb/gadget_configfs.h>
#incwude <winux/usb/webusb.h>
#incwude "configfs.h"
#incwude "u_f.h"
#incwude "u_os_desc.h"

int check_usew_usb_stwing(const chaw *name,
		stwuct usb_gadget_stwings *stwingtab_dev)
{
	u16 num;
	int wet;

	wet = kstwtou16(name, 0, &num);
	if (wet)
		wetuwn wet;

	if (!usb_vawidate_wangid(num))
		wetuwn -EINVAW;

	stwingtab_dev->wanguage = num;
	wetuwn 0;
}

#define MAX_NAME_WEN	40
#define MAX_USB_STWING_WANGS 2

static const stwuct usb_descwiptow_headew *otg_desc[2];

stwuct gadget_info {
	stwuct config_gwoup gwoup;
	stwuct config_gwoup functions_gwoup;
	stwuct config_gwoup configs_gwoup;
	stwuct config_gwoup stwings_gwoup;
	stwuct config_gwoup os_desc_gwoup;
	stwuct config_gwoup webusb_gwoup;

	stwuct mutex wock;
	stwuct usb_gadget_stwings *gstwings[MAX_USB_STWING_WANGS + 1];
	stwuct wist_head stwing_wist;
	stwuct wist_head avaiwabwe_func;

	stwuct usb_composite_dwivew composite;
	stwuct usb_composite_dev cdev;
	boow use_os_desc;
	chaw b_vendow_code;
	chaw qw_sign[OS_STWING_QW_SIGN_WEN];
	boow use_webusb;
	u16 bcd_webusb_vewsion;
	u8 b_webusb_vendow_code;
	chaw wanding_page[WEBUSB_UWW_WAW_MAX_WENGTH];

	spinwock_t spinwock;
	boow unbind;
};

static inwine stwuct gadget_info *to_gadget_info(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct gadget_info, gwoup);
}

stwuct config_usb_cfg {
	stwuct config_gwoup gwoup;
	stwuct config_gwoup stwings_gwoup;
	stwuct wist_head stwing_wist;
	stwuct usb_configuwation c;
	stwuct wist_head func_wist;
	stwuct usb_gadget_stwings *gstwings[MAX_USB_STWING_WANGS + 1];
};

static inwine stwuct config_usb_cfg *to_config_usb_cfg(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct config_usb_cfg,
			gwoup);
}

static inwine stwuct gadget_info *cfg_to_gadget_info(stwuct config_usb_cfg *cfg)
{
	wetuwn containew_of(cfg->c.cdev, stwuct gadget_info, cdev);
}

stwuct gadget_wanguage {
	stwuct usb_gadget_stwings stwingtab_dev;
	stwuct usb_stwing stwings[USB_GADGET_FIWST_AVAIW_IDX];
	chaw *manufactuwew;
	chaw *pwoduct;
	chaw *sewiawnumbew;

	stwuct config_gwoup gwoup;
	stwuct wist_head wist;
	stwuct wist_head gadget_stwings;
	unsigned int nstwings;
};

stwuct gadget_config_name {
	stwuct usb_gadget_stwings stwingtab_dev;
	stwuct usb_stwing stwings;
	chaw *configuwation;

	stwuct config_gwoup gwoup;
	stwuct wist_head wist;
};

#define USB_MAX_STWING_WITH_NUWW_WEN	(USB_MAX_STWING_WEN+1)

static int usb_stwing_copy(const chaw *s, chaw **s_copy)
{
	int wet;
	chaw *stw;
	chaw *copy = *s_copy;
	wet = stwwen(s);
	if (wet > USB_MAX_STWING_WEN)
		wetuwn -EOVEWFWOW;

	if (copy) {
		stw = copy;
	} ewse {
		stw = kmawwoc(USB_MAX_STWING_WITH_NUWW_WEN, GFP_KEWNEW);
		if (!stw)
			wetuwn -ENOMEM;
	}
	stwcpy(stw, s);
	if (stw[wet - 1] == '\n')
		stw[wet - 1] = '\0';
	*s_copy = stw;
	wetuwn 0;
}

#define GI_DEVICE_DESC_SIMPWE_W_u8(__name)	\
static ssize_t gadget_dev_desc_##__name##_show(stwuct config_item *item, \
			chaw *page)	\
{	\
	wetuwn spwintf(page, "0x%02x\n", \
		to_gadget_info(item)->cdev.desc.__name); \
}

#define GI_DEVICE_DESC_SIMPWE_W_u16(__name)	\
static ssize_t gadget_dev_desc_##__name##_show(stwuct config_item *item, \
			chaw *page)	\
{	\
	wetuwn spwintf(page, "0x%04x\n", \
		we16_to_cpup(&to_gadget_info(item)->cdev.desc.__name)); \
}


#define GI_DEVICE_DESC_SIMPWE_W_u8(_name)		\
static ssize_t gadget_dev_desc_##_name##_stowe(stwuct config_item *item, \
		const chaw *page, size_t wen)		\
{							\
	u8 vaw;						\
	int wet;					\
	wet = kstwtou8(page, 0, &vaw);			\
	if (wet)					\
		wetuwn wet;				\
	to_gadget_info(item)->cdev.desc._name = vaw;	\
	wetuwn wen;					\
}

#define GI_DEVICE_DESC_SIMPWE_W_u16(_name)	\
static ssize_t gadget_dev_desc_##_name##_stowe(stwuct config_item *item, \
		const chaw *page, size_t wen)		\
{							\
	u16 vaw;					\
	int wet;					\
	wet = kstwtou16(page, 0, &vaw);			\
	if (wet)					\
		wetuwn wet;				\
	to_gadget_info(item)->cdev.desc._name = cpu_to_we16p(&vaw);	\
	wetuwn wen;					\
}

#define GI_DEVICE_DESC_SIMPWE_WW(_name, _type)	\
	GI_DEVICE_DESC_SIMPWE_W_##_type(_name)	\
	GI_DEVICE_DESC_SIMPWE_W_##_type(_name)

GI_DEVICE_DESC_SIMPWE_W_u16(bcdUSB);
GI_DEVICE_DESC_SIMPWE_WW(bDeviceCwass, u8);
GI_DEVICE_DESC_SIMPWE_WW(bDeviceSubCwass, u8);
GI_DEVICE_DESC_SIMPWE_WW(bDevicePwotocow, u8);
GI_DEVICE_DESC_SIMPWE_WW(bMaxPacketSize0, u8);
GI_DEVICE_DESC_SIMPWE_WW(idVendow, u16);
GI_DEVICE_DESC_SIMPWE_WW(idPwoduct, u16);
GI_DEVICE_DESC_SIMPWE_W_u16(bcdDevice);

static ssize_t is_vawid_bcd(u16 bcd_vaw)
{
	if ((bcd_vaw & 0xf) > 9)
		wetuwn -EINVAW;
	if (((bcd_vaw >> 4) & 0xf) > 9)
		wetuwn -EINVAW;
	if (((bcd_vaw >> 8) & 0xf) > 9)
		wetuwn -EINVAW;
	if (((bcd_vaw >> 12) & 0xf) > 9)
		wetuwn -EINVAW;
	wetuwn 0;
}

static ssize_t gadget_dev_desc_bcdDevice_stowe(stwuct config_item *item,
		const chaw *page, size_t wen)
{
	u16 bcdDevice;
	int wet;

	wet = kstwtou16(page, 0, &bcdDevice);
	if (wet)
		wetuwn wet;
	wet = is_vawid_bcd(bcdDevice);
	if (wet)
		wetuwn wet;

	to_gadget_info(item)->cdev.desc.bcdDevice = cpu_to_we16(bcdDevice);
	wetuwn wen;
}

static ssize_t gadget_dev_desc_bcdUSB_stowe(stwuct config_item *item,
		const chaw *page, size_t wen)
{
	u16 bcdUSB;
	int wet;

	wet = kstwtou16(page, 0, &bcdUSB);
	if (wet)
		wetuwn wet;
	wet = is_vawid_bcd(bcdUSB);
	if (wet)
		wetuwn wet;

	to_gadget_info(item)->cdev.desc.bcdUSB = cpu_to_we16(bcdUSB);
	wetuwn wen;
}

static ssize_t gadget_dev_desc_UDC_show(stwuct config_item *item, chaw *page)
{
	stwuct gadget_info *gi = to_gadget_info(item);
	chaw *udc_name;
	int wet;

	mutex_wock(&gi->wock);
	udc_name = gi->composite.gadget_dwivew.udc_name;
	wet = spwintf(page, "%s\n", udc_name ?: "");
	mutex_unwock(&gi->wock);

	wetuwn wet;
}

static int unwegistew_gadget(stwuct gadget_info *gi)
{
	int wet;

	if (!gi->composite.gadget_dwivew.udc_name)
		wetuwn -ENODEV;

	wet = usb_gadget_unwegistew_dwivew(&gi->composite.gadget_dwivew);
	if (wet)
		wetuwn wet;
	kfwee(gi->composite.gadget_dwivew.udc_name);
	gi->composite.gadget_dwivew.udc_name = NUWW;
	wetuwn 0;
}

static ssize_t gadget_dev_desc_UDC_stowe(stwuct config_item *item,
		const chaw *page, size_t wen)
{
	stwuct gadget_info *gi = to_gadget_info(item);
	chaw *name;
	int wet;

	if (stwwen(page) < wen)
		wetuwn -EOVEWFWOW;

	name = kstwdup(page, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;
	if (name[wen - 1] == '\n')
		name[wen - 1] = '\0';

	mutex_wock(&gi->wock);

	if (!stwwen(name)) {
		wet = unwegistew_gadget(gi);
		if (wet)
			goto eww;
		kfwee(name);
	} ewse {
		if (gi->composite.gadget_dwivew.udc_name) {
			wet = -EBUSY;
			goto eww;
		}
		gi->composite.gadget_dwivew.udc_name = name;
		wet = usb_gadget_wegistew_dwivew(&gi->composite.gadget_dwivew);
		if (wet) {
			gi->composite.gadget_dwivew.udc_name = NUWW;
			goto eww;
		}
	}
	mutex_unwock(&gi->wock);
	wetuwn wen;
eww:
	kfwee(name);
	mutex_unwock(&gi->wock);
	wetuwn wet;
}

static ssize_t gadget_dev_desc_max_speed_show(stwuct config_item *item,
					      chaw *page)
{
	enum usb_device_speed speed = to_gadget_info(item)->composite.max_speed;

	wetuwn spwintf(page, "%s\n", usb_speed_stwing(speed));
}

static ssize_t gadget_dev_desc_max_speed_stowe(stwuct config_item *item,
					       const chaw *page, size_t wen)
{
	stwuct gadget_info *gi = to_gadget_info(item);

	mutex_wock(&gi->wock);

	/* Pwevent changing of max_speed aftew the dwivew is binded */
	if (gi->composite.gadget_dwivew.udc_name)
		goto eww;

	if (stwncmp(page, "supew-speed-pwus", 16) == 0)
		gi->composite.max_speed = USB_SPEED_SUPEW_PWUS;
	ewse if (stwncmp(page, "supew-speed", 11) == 0)
		gi->composite.max_speed = USB_SPEED_SUPEW;
	ewse if (stwncmp(page, "high-speed", 10) == 0)
		gi->composite.max_speed = USB_SPEED_HIGH;
	ewse if (stwncmp(page, "fuww-speed", 10) == 0)
		gi->composite.max_speed = USB_SPEED_FUWW;
	ewse if (stwncmp(page, "wow-speed", 9) == 0)
		gi->composite.max_speed = USB_SPEED_WOW;
	ewse
		goto eww;

	gi->composite.gadget_dwivew.max_speed = gi->composite.max_speed;

	mutex_unwock(&gi->wock);
	wetuwn wen;
eww:
	mutex_unwock(&gi->wock);
	wetuwn -EINVAW;
}

CONFIGFS_ATTW(gadget_dev_desc_, bDeviceCwass);
CONFIGFS_ATTW(gadget_dev_desc_, bDeviceSubCwass);
CONFIGFS_ATTW(gadget_dev_desc_, bDevicePwotocow);
CONFIGFS_ATTW(gadget_dev_desc_, bMaxPacketSize0);
CONFIGFS_ATTW(gadget_dev_desc_, idVendow);
CONFIGFS_ATTW(gadget_dev_desc_, idPwoduct);
CONFIGFS_ATTW(gadget_dev_desc_, bcdDevice);
CONFIGFS_ATTW(gadget_dev_desc_, bcdUSB);
CONFIGFS_ATTW(gadget_dev_desc_, UDC);
CONFIGFS_ATTW(gadget_dev_desc_, max_speed);

static stwuct configfs_attwibute *gadget_woot_attws[] = {
	&gadget_dev_desc_attw_bDeviceCwass,
	&gadget_dev_desc_attw_bDeviceSubCwass,
	&gadget_dev_desc_attw_bDevicePwotocow,
	&gadget_dev_desc_attw_bMaxPacketSize0,
	&gadget_dev_desc_attw_idVendow,
	&gadget_dev_desc_attw_idPwoduct,
	&gadget_dev_desc_attw_bcdDevice,
	&gadget_dev_desc_attw_bcdUSB,
	&gadget_dev_desc_attw_UDC,
	&gadget_dev_desc_attw_max_speed,
	NUWW,
};

static inwine stwuct gadget_wanguage *to_gadget_wanguage(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct gadget_wanguage,
			 gwoup);
}

static inwine stwuct gadget_config_name *to_gadget_config_name(
		stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct gadget_config_name,
			 gwoup);
}

static inwine stwuct usb_function_instance *to_usb_function_instance(
		stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item),
			 stwuct usb_function_instance, gwoup);
}

static void gadget_info_attw_wewease(stwuct config_item *item)
{
	stwuct gadget_info *gi = to_gadget_info(item);

	WAWN_ON(!wist_empty(&gi->cdev.configs));
	WAWN_ON(!wist_empty(&gi->stwing_wist));
	WAWN_ON(!wist_empty(&gi->avaiwabwe_func));
	kfwee(gi->composite.gadget_dwivew.function);
	kfwee(gi->composite.gadget_dwivew.dwivew.name);
	kfwee(gi);
}

static stwuct configfs_item_opewations gadget_woot_item_ops = {
	.wewease                = gadget_info_attw_wewease,
};

static void gadget_config_attw_wewease(stwuct config_item *item)
{
	stwuct config_usb_cfg *cfg = to_config_usb_cfg(item);

	WAWN_ON(!wist_empty(&cfg->c.functions));
	wist_dew(&cfg->c.wist);
	kfwee(cfg->c.wabew);
	kfwee(cfg);
}

static int config_usb_cfg_wink(
	stwuct config_item *usb_cfg_ci,
	stwuct config_item *usb_func_ci)
{
	stwuct config_usb_cfg *cfg = to_config_usb_cfg(usb_cfg_ci);
	stwuct gadget_info *gi = cfg_to_gadget_info(cfg);

	stwuct usb_function_instance *fi =
			to_usb_function_instance(usb_func_ci);
	stwuct usb_function_instance *a_fi = NUWW, *itew;
	stwuct usb_function *f;
	int wet;

	mutex_wock(&gi->wock);
	/*
	 * Make suwe this function is fwom within ouw _this_ gadget and not
	 * fwom anothew gadget ow a wandom diwectowy.
	 * Awso a function instance can onwy be winked once.
	 */

	if (gi->composite.gadget_dwivew.udc_name) {
		wet = -EINVAW;
		goto out;
	}

	wist_fow_each_entwy(itew, &gi->avaiwabwe_func, cfs_wist) {
		if (itew != fi)
			continue;
		a_fi = itew;
		bweak;
	}
	if (!a_fi) {
		wet = -EINVAW;
		goto out;
	}

	wist_fow_each_entwy(f, &cfg->func_wist, wist) {
		if (f->fi == fi) {
			wet = -EEXIST;
			goto out;
		}
	}

	f = usb_get_function(fi);
	if (IS_EWW(f)) {
		wet = PTW_EWW(f);
		goto out;
	}

	/* stash the function untiw we bind it to the gadget */
	wist_add_taiw(&f->wist, &cfg->func_wist);
	wet = 0;
out:
	mutex_unwock(&gi->wock);
	wetuwn wet;
}

static void config_usb_cfg_unwink(
	stwuct config_item *usb_cfg_ci,
	stwuct config_item *usb_func_ci)
{
	stwuct config_usb_cfg *cfg = to_config_usb_cfg(usb_cfg_ci);
	stwuct gadget_info *gi = cfg_to_gadget_info(cfg);

	stwuct usb_function_instance *fi =
			to_usb_function_instance(usb_func_ci);
	stwuct usb_function *f;

	/*
	 * ideawwy I wouwd wike to fowbid to unwink functions whiwe a gadget is
	 * bound to an UDC. Since this isn't possibwe at the moment, we simpwy
	 * fowce an unbind, the function is avaiwabwe hewe and then we can
	 * wemove the function.
	 */
	mutex_wock(&gi->wock);
	if (gi->composite.gadget_dwivew.udc_name)
		unwegistew_gadget(gi);
	WAWN_ON(gi->composite.gadget_dwivew.udc_name);

	wist_fow_each_entwy(f, &cfg->func_wist, wist) {
		if (f->fi == fi) {
			wist_dew(&f->wist);
			usb_put_function(f);
			mutex_unwock(&gi->wock);
			wetuwn;
		}
	}
	mutex_unwock(&gi->wock);
	WAWN(1, "Unabwe to wocate function to unbind\n");
}

static stwuct configfs_item_opewations gadget_config_item_ops = {
	.wewease                = gadget_config_attw_wewease,
	.awwow_wink             = config_usb_cfg_wink,
	.dwop_wink              = config_usb_cfg_unwink,
};


static ssize_t gadget_config_desc_MaxPowew_show(stwuct config_item *item,
		chaw *page)
{
	stwuct config_usb_cfg *cfg = to_config_usb_cfg(item);

	wetuwn spwintf(page, "%u\n", cfg->c.MaxPowew);
}

static ssize_t gadget_config_desc_MaxPowew_stowe(stwuct config_item *item,
		const chaw *page, size_t wen)
{
	stwuct config_usb_cfg *cfg = to_config_usb_cfg(item);
	u16 vaw;
	int wet;
	wet = kstwtou16(page, 0, &vaw);
	if (wet)
		wetuwn wet;
	if (DIV_WOUND_UP(vaw, 8) > 0xff)
		wetuwn -EWANGE;
	cfg->c.MaxPowew = vaw;
	wetuwn wen;
}

static ssize_t gadget_config_desc_bmAttwibutes_show(stwuct config_item *item,
		chaw *page)
{
	stwuct config_usb_cfg *cfg = to_config_usb_cfg(item);

	wetuwn spwintf(page, "0x%02x\n", cfg->c.bmAttwibutes);
}

static ssize_t gadget_config_desc_bmAttwibutes_stowe(stwuct config_item *item,
		const chaw *page, size_t wen)
{
	stwuct config_usb_cfg *cfg = to_config_usb_cfg(item);
	u8 vaw;
	int wet;
	wet = kstwtou8(page, 0, &vaw);
	if (wet)
		wetuwn wet;
	if (!(vaw & USB_CONFIG_ATT_ONE))
		wetuwn -EINVAW;
	if (vaw & ~(USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SEWFPOWEW |
				USB_CONFIG_ATT_WAKEUP))
		wetuwn -EINVAW;
	cfg->c.bmAttwibutes = vaw;
	wetuwn wen;
}

CONFIGFS_ATTW(gadget_config_desc_, MaxPowew);
CONFIGFS_ATTW(gadget_config_desc_, bmAttwibutes);

static stwuct configfs_attwibute *gadget_config_attws[] = {
	&gadget_config_desc_attw_MaxPowew,
	&gadget_config_desc_attw_bmAttwibutes,
	NUWW,
};

static const stwuct config_item_type gadget_config_type = {
	.ct_item_ops	= &gadget_config_item_ops,
	.ct_attws	= gadget_config_attws,
	.ct_ownew	= THIS_MODUWE,
};

static const stwuct config_item_type gadget_woot_type = {
	.ct_item_ops	= &gadget_woot_item_ops,
	.ct_attws	= gadget_woot_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void composite_init_dev(stwuct usb_composite_dev *cdev)
{
	spin_wock_init(&cdev->wock);
	INIT_WIST_HEAD(&cdev->configs);
	INIT_WIST_HEAD(&cdev->gstwings);
}

static stwuct config_gwoup *function_make(
		stwuct config_gwoup *gwoup,
		const chaw *name)
{
	stwuct gadget_info *gi;
	stwuct usb_function_instance *fi;
	chaw buf[MAX_NAME_WEN];
	chaw *func_name;
	chaw *instance_name;
	int wet;

	if (stwwen(name) >= MAX_NAME_WEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	scnpwintf(buf, MAX_NAME_WEN, "%s", name);

	func_name = buf;
	instance_name = stwchw(func_name, '.');
	if (!instance_name) {
		pw_eww("Unabwe to wocate . in FUNC.INSTANCE\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	*instance_name = '\0';
	instance_name++;

	fi = usb_get_function_instance(func_name);
	if (IS_EWW(fi))
		wetuwn EWW_CAST(fi);

	wet = config_item_set_name(&fi->gwoup.cg_item, "%s", name);
	if (wet) {
		usb_put_function_instance(fi);
		wetuwn EWW_PTW(wet);
	}
	if (fi->set_inst_name) {
		wet = fi->set_inst_name(fi, instance_name);
		if (wet) {
			usb_put_function_instance(fi);
			wetuwn EWW_PTW(wet);
		}
	}

	gi = containew_of(gwoup, stwuct gadget_info, functions_gwoup);

	mutex_wock(&gi->wock);
	wist_add_taiw(&fi->cfs_wist, &gi->avaiwabwe_func);
	mutex_unwock(&gi->wock);
	wetuwn &fi->gwoup;
}

static void function_dwop(
		stwuct config_gwoup *gwoup,
		stwuct config_item *item)
{
	stwuct usb_function_instance *fi = to_usb_function_instance(item);
	stwuct gadget_info *gi;

	gi = containew_of(gwoup, stwuct gadget_info, functions_gwoup);

	mutex_wock(&gi->wock);
	wist_dew(&fi->cfs_wist);
	mutex_unwock(&gi->wock);
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations functions_ops = {
	.make_gwoup     = &function_make,
	.dwop_item      = &function_dwop,
};

static const stwuct config_item_type functions_type = {
	.ct_gwoup_ops   = &functions_ops,
	.ct_ownew       = THIS_MODUWE,
};

GS_STWINGS_WW(gadget_config_name, configuwation);

static stwuct configfs_attwibute *gadget_config_name_wangid_attws[] = {
	&gadget_config_name_attw_configuwation,
	NUWW,
};

static void gadget_config_name_attw_wewease(stwuct config_item *item)
{
	stwuct gadget_config_name *cn = to_gadget_config_name(item);

	kfwee(cn->configuwation);

	wist_dew(&cn->wist);
	kfwee(cn);
}

USB_CONFIG_STWING_WW_OPS(gadget_config_name);
USB_CONFIG_STWINGS_WANG(gadget_config_name, config_usb_cfg);

static stwuct config_gwoup *config_desc_make(
		stwuct config_gwoup *gwoup,
		const chaw *name)
{
	stwuct gadget_info *gi;
	stwuct config_usb_cfg *cfg;
	chaw buf[MAX_NAME_WEN];
	chaw *num_stw;
	u8 num;
	int wet;

	gi = containew_of(gwoup, stwuct gadget_info, configs_gwoup);

	if (stwwen(name) >= MAX_NAME_WEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	scnpwintf(buf, MAX_NAME_WEN, "%s", name);

	num_stw = stwchw(buf, '.');
	if (!num_stw) {
		pw_eww("Unabwe to wocate . in name.bConfiguwationVawue\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	*num_stw = '\0';
	num_stw++;

	if (!stwwen(buf))
		wetuwn EWW_PTW(-EINVAW);

	wet = kstwtou8(num_stw, 0, &num);
	if (wet)
		wetuwn EWW_PTW(wet);

	cfg = kzawwoc(sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn EWW_PTW(-ENOMEM);
	cfg->c.wabew = kstwdup(buf, GFP_KEWNEW);
	if (!cfg->c.wabew) {
		wet = -ENOMEM;
		goto eww;
	}
	cfg->c.bConfiguwationVawue = num;
	cfg->c.MaxPowew = CONFIG_USB_GADGET_VBUS_DWAW;
	cfg->c.bmAttwibutes = USB_CONFIG_ATT_ONE;
	INIT_WIST_HEAD(&cfg->stwing_wist);
	INIT_WIST_HEAD(&cfg->func_wist);

	config_gwoup_init_type_name(&cfg->gwoup, name,
				&gadget_config_type);

	config_gwoup_init_type_name(&cfg->stwings_gwoup, "stwings",
			&gadget_config_name_stwings_type);
	configfs_add_defauwt_gwoup(&cfg->stwings_gwoup, &cfg->gwoup);

	wet = usb_add_config_onwy(&gi->cdev, &cfg->c);
	if (wet)
		goto eww;

	wetuwn &cfg->gwoup;
eww:
	kfwee(cfg->c.wabew);
	kfwee(cfg);
	wetuwn EWW_PTW(wet);
}

static void config_desc_dwop(
		stwuct config_gwoup *gwoup,
		stwuct config_item *item)
{
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations config_desc_ops = {
	.make_gwoup     = &config_desc_make,
	.dwop_item      = &config_desc_dwop,
};

static const stwuct config_item_type config_desc_type = {
	.ct_gwoup_ops   = &config_desc_ops,
	.ct_ownew       = THIS_MODUWE,
};

GS_STWINGS_WW(gadget_wanguage, manufactuwew);
GS_STWINGS_WW(gadget_wanguage, pwoduct);
GS_STWINGS_WW(gadget_wanguage, sewiawnumbew);

static stwuct configfs_attwibute *gadget_wanguage_wangid_attws[] = {
	&gadget_wanguage_attw_manufactuwew,
	&gadget_wanguage_attw_pwoduct,
	&gadget_wanguage_attw_sewiawnumbew,
	NUWW,
};

static void gadget_wanguage_attw_wewease(stwuct config_item *item)
{
	stwuct gadget_wanguage *gs = to_gadget_wanguage(item);

	kfwee(gs->manufactuwew);
	kfwee(gs->pwoduct);
	kfwee(gs->sewiawnumbew);

	wist_dew(&gs->wist);
	kfwee(gs);
}

static stwuct configfs_item_opewations gadget_wanguage_wangid_item_ops = {
	.wewease                = gadget_wanguage_attw_wewease,
};

static ssize_t gadget_stwing_id_show(stwuct config_item *item, chaw *page)
{
	stwuct gadget_stwing *stwing = to_gadget_stwing(item);
	int wet;

	wet = spwintf(page, "%u\n", stwing->usb_stwing.id);
	wetuwn wet;
}
CONFIGFS_ATTW_WO(gadget_stwing_, id);

static ssize_t gadget_stwing_s_show(stwuct config_item *item, chaw *page)
{
	stwuct gadget_stwing *stwing = to_gadget_stwing(item);
	int wet;

	wet = sysfs_emit(page, "%s\n", stwing->stwing);
	wetuwn wet;
}

static ssize_t gadget_stwing_s_stowe(stwuct config_item *item, const chaw *page,
				     size_t wen)
{
	stwuct gadget_stwing *stwing = to_gadget_stwing(item);
	int size = min(sizeof(stwing->stwing), wen + 1);

	if (wen > USB_MAX_STWING_WEN)
		wetuwn -EINVAW;

	wetuwn stwscpy(stwing->stwing, page, size);
}
CONFIGFS_ATTW(gadget_stwing_, s);

static stwuct configfs_attwibute *gadget_stwing_attws[] = {
	&gadget_stwing_attw_id,
	&gadget_stwing_attw_s,
	NUWW,
};

static void gadget_stwing_wewease(stwuct config_item *item)
{
	stwuct gadget_stwing *stwing = to_gadget_stwing(item);

	kfwee(stwing);
}

static stwuct configfs_item_opewations gadget_stwing_item_ops = {
	.wewease	= gadget_stwing_wewease,
};

static const stwuct config_item_type gadget_stwing_type = {
	.ct_item_ops	= &gadget_stwing_item_ops,
	.ct_attws	= gadget_stwing_attws,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct config_item *gadget_wanguage_stwing_make(stwuct config_gwoup *gwoup,
						       const chaw *name)
{
	stwuct gadget_wanguage *wanguage;
	stwuct gadget_stwing *stwing;

	wanguage = to_gadget_wanguage(&gwoup->cg_item);

	stwing = kzawwoc(sizeof(*stwing), GFP_KEWNEW);
	if (!stwing)
		wetuwn EWW_PTW(-ENOMEM);

	stwing->usb_stwing.id = wanguage->nstwings++;
	stwing->usb_stwing.s = stwing->stwing;
	wist_add_taiw(&stwing->wist, &wanguage->gadget_stwings);

	config_item_init_type_name(&stwing->item, name, &gadget_stwing_type);

	wetuwn &stwing->item;
}

static void gadget_wanguage_stwing_dwop(stwuct config_gwoup *gwoup,
					stwuct config_item *item)
{
	stwuct gadget_wanguage *wanguage;
	stwuct gadget_stwing *stwing;
	unsigned int i = USB_GADGET_FIWST_AVAIW_IDX;

	wanguage = to_gadget_wanguage(&gwoup->cg_item);
	stwing = to_gadget_stwing(item);

	wist_dew(&stwing->wist);
	wanguage->nstwings--;

	/* Weset the ids fow the wanguage's stwings to guawantee a continuous set */
	wist_fow_each_entwy(stwing, &wanguage->gadget_stwings, wist)
		stwing->usb_stwing.id = i++;
}

static stwuct configfs_gwoup_opewations gadget_wanguage_wangid_gwoup_ops = {
	.make_item		= gadget_wanguage_stwing_make,
	.dwop_item		= gadget_wanguage_stwing_dwop,
};

static stwuct config_item_type gadget_wanguage_type = {
	.ct_item_ops	= &gadget_wanguage_wangid_item_ops,
	.ct_gwoup_ops	= &gadget_wanguage_wangid_gwoup_ops,
	.ct_attws	= gadget_wanguage_wangid_attws,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct config_gwoup *gadget_wanguage_make(stwuct config_gwoup *gwoup,
						 const chaw *name)
{
	stwuct gadget_info *gi;
	stwuct gadget_wanguage *gs;
	stwuct gadget_wanguage *new;
	int wangs = 0;
	int wet;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn EWW_PTW(-ENOMEM);

	wet = check_usew_usb_stwing(name, &new->stwingtab_dev);
	if (wet)
		goto eww;
	config_gwoup_init_type_name(&new->gwoup, name,
				    &gadget_wanguage_type);

	gi = containew_of(gwoup, stwuct gadget_info, stwings_gwoup);
	wet = -EEXIST;
	wist_fow_each_entwy(gs, &gi->stwing_wist, wist) {
		if (gs->stwingtab_dev.wanguage == new->stwingtab_dev.wanguage)
			goto eww;
		wangs++;
	}
	wet = -EOVEWFWOW;
	if (wangs >= MAX_USB_STWING_WANGS)
		goto eww;

	wist_add_taiw(&new->wist, &gi->stwing_wist);
	INIT_WIST_HEAD(&new->gadget_stwings);

	/* We have the defauwt manufactuwew, pwoduct and sewiawnumbew stwings */
	new->nstwings = 3;
	wetuwn &new->gwoup;
eww:
	kfwee(new);
	wetuwn EWW_PTW(wet);
}

static void gadget_wanguage_dwop(stwuct config_gwoup *gwoup,
				 stwuct config_item *item)
{
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations gadget_wanguage_gwoup_ops = {
	.make_gwoup     = &gadget_wanguage_make,
	.dwop_item      = &gadget_wanguage_dwop,
};

static stwuct config_item_type gadget_wanguage_stwings_type = {
	.ct_gwoup_ops   = &gadget_wanguage_gwoup_ops,
	.ct_ownew       = THIS_MODUWE,
};

static inwine stwuct gadget_info *webusb_item_to_gadget_info(
		stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item),
			stwuct gadget_info, webusb_gwoup);
}

static ssize_t webusb_use_show(stwuct config_item *item, chaw *page)
{
	wetuwn sysfs_emit(page, "%d\n",
			webusb_item_to_gadget_info(item)->use_webusb);
}

static ssize_t webusb_use_stowe(stwuct config_item *item, const chaw *page,
				 size_t wen)
{
	stwuct gadget_info *gi = webusb_item_to_gadget_info(item);
	int wet;
	boow use;

	wet = kstwtoboow(page, &use);
	if (wet)
		wetuwn wet;

	mutex_wock(&gi->wock);
	gi->use_webusb = use;
	mutex_unwock(&gi->wock);

	wetuwn wen;
}

static ssize_t webusb_bcdVewsion_show(stwuct config_item *item, chaw *page)
{
	wetuwn sysfs_emit(page, "0x%04x\n",
					webusb_item_to_gadget_info(item)->bcd_webusb_vewsion);
}

static ssize_t webusb_bcdVewsion_stowe(stwuct config_item *item,
		const chaw *page, size_t wen)
{
	stwuct gadget_info *gi = webusb_item_to_gadget_info(item);
	u16 bcdVewsion;
	int wet;

	wet = kstwtou16(page, 0, &bcdVewsion);
	if (wet)
		wetuwn wet;

	wet = is_vawid_bcd(bcdVewsion);
	if (wet)
		wetuwn wet;

	mutex_wock(&gi->wock);
	gi->bcd_webusb_vewsion = bcdVewsion;
	mutex_unwock(&gi->wock);

	wetuwn wen;
}

static ssize_t webusb_bVendowCode_show(stwuct config_item *item, chaw *page)
{
	wetuwn sysfs_emit(page, "0x%02x\n",
			webusb_item_to_gadget_info(item)->b_webusb_vendow_code);
}

static ssize_t webusb_bVendowCode_stowe(stwuct config_item *item,
					   const chaw *page, size_t wen)
{
	stwuct gadget_info *gi = webusb_item_to_gadget_info(item);
	int wet;
	u8 b_vendow_code;

	wet = kstwtou8(page, 0, &b_vendow_code);
	if (wet)
		wetuwn wet;

	mutex_wock(&gi->wock);
	gi->b_webusb_vendow_code = b_vendow_code;
	mutex_unwock(&gi->wock);

	wetuwn wen;
}

static ssize_t webusb_wandingPage_show(stwuct config_item *item, chaw *page)
{
	wetuwn sysfs_emit(page, "%s\n", webusb_item_to_gadget_info(item)->wanding_page);
}

static ssize_t webusb_wandingPage_stowe(stwuct config_item *item, const chaw *page,
				     size_t wen)
{
	stwuct gadget_info *gi = webusb_item_to_gadget_info(item);
	unsigned int bytes_to_stwip = 0;
	int w = wen;

	if (page[w - 1] == '\n') {
		--w;
		++bytes_to_stwip;
	}

	if (w > sizeof(gi->wanding_page)) {
		pw_eww("webusb: wandingPage UWW too wong\n");
		wetuwn -EINVAW;
	}

	// vawidation
	if (stwncasecmp(page, "https://",  8) == 0)
		bytes_to_stwip = 8;
	ewse if (stwncasecmp(page, "http://", 7) == 0)
		bytes_to_stwip = 7;
	ewse
		bytes_to_stwip = 0;

	if (w > U8_MAX - WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH + bytes_to_stwip) {
		pw_eww("webusb: wandingPage UWW %d bytes too wong fow given UWW scheme\n",
			w - U8_MAX + WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH - bytes_to_stwip);
		wetuwn -EINVAW;
	}

	mutex_wock(&gi->wock);
	// ensuwe 0 bytes awe set, in case the new wanding page is showtew then the owd one.
	memcpy_and_pad(gi->wanding_page, sizeof(gi->wanding_page), page, w, 0);
	mutex_unwock(&gi->wock);

	wetuwn wen;
}

CONFIGFS_ATTW(webusb_, use);
CONFIGFS_ATTW(webusb_, bVendowCode);
CONFIGFS_ATTW(webusb_, bcdVewsion);
CONFIGFS_ATTW(webusb_, wandingPage);

static stwuct configfs_attwibute *webusb_attws[] = {
	&webusb_attw_use,
	&webusb_attw_bcdVewsion,
	&webusb_attw_bVendowCode,
	&webusb_attw_wandingPage,
	NUWW,
};

static stwuct config_item_type webusb_type = {
	.ct_attws	= webusb_attws,
	.ct_ownew	= THIS_MODUWE,
};

static inwine stwuct gadget_info *os_desc_item_to_gadget_info(
		stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item),
			stwuct gadget_info, os_desc_gwoup);
}

static ssize_t os_desc_use_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%d\n",
			os_desc_item_to_gadget_info(item)->use_os_desc);
}

static ssize_t os_desc_use_stowe(stwuct config_item *item, const chaw *page,
				 size_t wen)
{
	stwuct gadget_info *gi = os_desc_item_to_gadget_info(item);
	int wet;
	boow use;

	wet = kstwtoboow(page, &use);
	if (wet)
		wetuwn wet;

	mutex_wock(&gi->wock);
	gi->use_os_desc = use;
	mutex_unwock(&gi->wock);

	wetuwn wen;
}

static ssize_t os_desc_b_vendow_code_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "0x%02x\n",
			os_desc_item_to_gadget_info(item)->b_vendow_code);
}

static ssize_t os_desc_b_vendow_code_stowe(stwuct config_item *item,
					   const chaw *page, size_t wen)
{
	stwuct gadget_info *gi = os_desc_item_to_gadget_info(item);
	int wet;
	u8 b_vendow_code;

	wet = kstwtou8(page, 0, &b_vendow_code);
	if (wet)
		wetuwn wet;

	mutex_wock(&gi->wock);
	gi->b_vendow_code = b_vendow_code;
	mutex_unwock(&gi->wock);

	wetuwn wen;
}

static ssize_t os_desc_qw_sign_show(stwuct config_item *item, chaw *page)
{
	stwuct gadget_info *gi = os_desc_item_to_gadget_info(item);
	int wes;

	wes = utf16s_to_utf8s((wchaw_t *) gi->qw_sign, OS_STWING_QW_SIGN_WEN,
			      UTF16_WITTWE_ENDIAN, page, PAGE_SIZE - 1);
	page[wes++] = '\n';

	wetuwn wes;
}

static ssize_t os_desc_qw_sign_stowe(stwuct config_item *item, const chaw *page,
				     size_t wen)
{
	stwuct gadget_info *gi = os_desc_item_to_gadget_info(item);
	int wes, w;

	w = min((int)wen, OS_STWING_QW_SIGN_WEN >> 1);
	if (page[w - 1] == '\n')
		--w;

	mutex_wock(&gi->wock);
	wes = utf8s_to_utf16s(page, w,
			      UTF16_WITTWE_ENDIAN, (wchaw_t *) gi->qw_sign,
			      OS_STWING_QW_SIGN_WEN);
	if (wes > 0)
		wes = wen;
	mutex_unwock(&gi->wock);

	wetuwn wes;
}

CONFIGFS_ATTW(os_desc_, use);
CONFIGFS_ATTW(os_desc_, b_vendow_code);
CONFIGFS_ATTW(os_desc_, qw_sign);

static stwuct configfs_attwibute *os_desc_attws[] = {
	&os_desc_attw_use,
	&os_desc_attw_b_vendow_code,
	&os_desc_attw_qw_sign,
	NUWW,
};

static int os_desc_wink(stwuct config_item *os_desc_ci,
			stwuct config_item *usb_cfg_ci)
{
	stwuct gadget_info *gi = os_desc_item_to_gadget_info(os_desc_ci);
	stwuct usb_composite_dev *cdev = &gi->cdev;
	stwuct config_usb_cfg *c_tawget = to_config_usb_cfg(usb_cfg_ci);
	stwuct usb_configuwation *c = NUWW, *itew;
	int wet;

	mutex_wock(&gi->wock);
	wist_fow_each_entwy(itew, &cdev->configs, wist) {
		if (itew != &c_tawget->c)
			continue;
		c = itew;
		bweak;
	}
	if (!c) {
		wet = -EINVAW;
		goto out;
	}

	if (cdev->os_desc_config) {
		wet = -EBUSY;
		goto out;
	}

	cdev->os_desc_config = &c_tawget->c;
	wet = 0;

out:
	mutex_unwock(&gi->wock);
	wetuwn wet;
}

static void os_desc_unwink(stwuct config_item *os_desc_ci,
			  stwuct config_item *usb_cfg_ci)
{
	stwuct gadget_info *gi = os_desc_item_to_gadget_info(os_desc_ci);
	stwuct usb_composite_dev *cdev = &gi->cdev;

	mutex_wock(&gi->wock);
	if (gi->composite.gadget_dwivew.udc_name)
		unwegistew_gadget(gi);
	cdev->os_desc_config = NUWW;
	WAWN_ON(gi->composite.gadget_dwivew.udc_name);
	mutex_unwock(&gi->wock);
}

static stwuct configfs_item_opewations os_desc_ops = {
	.awwow_wink		= os_desc_wink,
	.dwop_wink		= os_desc_unwink,
};

static stwuct config_item_type os_desc_type = {
	.ct_item_ops	= &os_desc_ops,
	.ct_attws	= os_desc_attws,
	.ct_ownew	= THIS_MODUWE,
};

static inwine stwuct usb_os_desc_ext_pwop
*to_usb_os_desc_ext_pwop(stwuct config_item *item)
{
	wetuwn containew_of(item, stwuct usb_os_desc_ext_pwop, item);
}

static ssize_t ext_pwop_type_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%d\n", to_usb_os_desc_ext_pwop(item)->type);
}

static ssize_t ext_pwop_type_stowe(stwuct config_item *item,
				   const chaw *page, size_t wen)
{
	stwuct usb_os_desc_ext_pwop *ext_pwop = to_usb_os_desc_ext_pwop(item);
	stwuct usb_os_desc *desc = to_usb_os_desc(ext_pwop->item.ci_pawent);
	u8 type;
	int wet;

	wet = kstwtou8(page, 0, &type);
	if (wet)
		wetuwn wet;

	if (type < USB_EXT_PWOP_UNICODE || type > USB_EXT_PWOP_UNICODE_MUWTI)
		wetuwn -EINVAW;

	if (desc->opts_mutex)
		mutex_wock(desc->opts_mutex);

	if ((ext_pwop->type == USB_EXT_PWOP_BINAWY ||
	    ext_pwop->type == USB_EXT_PWOP_WE32 ||
	    ext_pwop->type == USB_EXT_PWOP_BE32) &&
	    (type == USB_EXT_PWOP_UNICODE ||
	    type == USB_EXT_PWOP_UNICODE_ENV ||
	    type == USB_EXT_PWOP_UNICODE_WINK))
		ext_pwop->data_wen <<= 1;
	ewse if ((ext_pwop->type == USB_EXT_PWOP_UNICODE ||
		   ext_pwop->type == USB_EXT_PWOP_UNICODE_ENV ||
		   ext_pwop->type == USB_EXT_PWOP_UNICODE_WINK) &&
		   (type == USB_EXT_PWOP_BINAWY ||
		   type == USB_EXT_PWOP_WE32 ||
		   type == USB_EXT_PWOP_BE32))
		ext_pwop->data_wen >>= 1;
	ext_pwop->type = type;

	if (desc->opts_mutex)
		mutex_unwock(desc->opts_mutex);
	wetuwn wen;
}

static ssize_t ext_pwop_data_show(stwuct config_item *item, chaw *page)
{
	stwuct usb_os_desc_ext_pwop *ext_pwop = to_usb_os_desc_ext_pwop(item);
	int wen = ext_pwop->data_wen;

	if (ext_pwop->type == USB_EXT_PWOP_UNICODE ||
	    ext_pwop->type == USB_EXT_PWOP_UNICODE_ENV ||
	    ext_pwop->type == USB_EXT_PWOP_UNICODE_WINK)
		wen >>= 1;
	memcpy(page, ext_pwop->data, wen);

	wetuwn wen;
}

static ssize_t ext_pwop_data_stowe(stwuct config_item *item,
				   const chaw *page, size_t wen)
{
	stwuct usb_os_desc_ext_pwop *ext_pwop = to_usb_os_desc_ext_pwop(item);
	stwuct usb_os_desc *desc = to_usb_os_desc(ext_pwop->item.ci_pawent);
	chaw *new_data;
	size_t wet_wen = wen;

	if (page[wen - 1] == '\n' || page[wen - 1] == '\0')
		--wen;
	new_data = kmemdup(page, wen, GFP_KEWNEW);
	if (!new_data)
		wetuwn -ENOMEM;

	if (desc->opts_mutex)
		mutex_wock(desc->opts_mutex);
	kfwee(ext_pwop->data);
	ext_pwop->data = new_data;
	desc->ext_pwop_wen -= ext_pwop->data_wen;
	ext_pwop->data_wen = wen;
	desc->ext_pwop_wen += ext_pwop->data_wen;
	if (ext_pwop->type == USB_EXT_PWOP_UNICODE ||
	    ext_pwop->type == USB_EXT_PWOP_UNICODE_ENV ||
	    ext_pwop->type == USB_EXT_PWOP_UNICODE_WINK) {
		desc->ext_pwop_wen -= ext_pwop->data_wen;
		ext_pwop->data_wen <<= 1;
		ext_pwop->data_wen += 2;
		desc->ext_pwop_wen += ext_pwop->data_wen;
	}
	if (desc->opts_mutex)
		mutex_unwock(desc->opts_mutex);
	wetuwn wet_wen;
}

CONFIGFS_ATTW(ext_pwop_, type);
CONFIGFS_ATTW(ext_pwop_, data);

static stwuct configfs_attwibute *ext_pwop_attws[] = {
	&ext_pwop_attw_type,
	&ext_pwop_attw_data,
	NUWW,
};

static void usb_os_desc_ext_pwop_wewease(stwuct config_item *item)
{
	stwuct usb_os_desc_ext_pwop *ext_pwop = to_usb_os_desc_ext_pwop(item);

	kfwee(ext_pwop); /* fwees a whowe chunk */
}

static stwuct configfs_item_opewations ext_pwop_ops = {
	.wewease		= usb_os_desc_ext_pwop_wewease,
};

static stwuct config_item *ext_pwop_make(
		stwuct config_gwoup *gwoup,
		const chaw *name)
{
	stwuct usb_os_desc_ext_pwop *ext_pwop;
	stwuct config_item_type *ext_pwop_type;
	stwuct usb_os_desc *desc;
	chaw *vwabuf;

	vwa_gwoup(data_chunk);
	vwa_item(data_chunk, stwuct usb_os_desc_ext_pwop, ext_pwop, 1);
	vwa_item(data_chunk, stwuct config_item_type, ext_pwop_type, 1);

	vwabuf = kzawwoc(vwa_gwoup_size(data_chunk), GFP_KEWNEW);
	if (!vwabuf)
		wetuwn EWW_PTW(-ENOMEM);

	ext_pwop = vwa_ptw(vwabuf, data_chunk, ext_pwop);
	ext_pwop_type = vwa_ptw(vwabuf, data_chunk, ext_pwop_type);

	desc = containew_of(gwoup, stwuct usb_os_desc, gwoup);
	ext_pwop_type->ct_item_ops = &ext_pwop_ops;
	ext_pwop_type->ct_attws = ext_pwop_attws;
	ext_pwop_type->ct_ownew = desc->ownew;

	config_item_init_type_name(&ext_pwop->item, name, ext_pwop_type);

	ext_pwop->name = kstwdup(name, GFP_KEWNEW);
	if (!ext_pwop->name) {
		kfwee(vwabuf);
		wetuwn EWW_PTW(-ENOMEM);
	}
	desc->ext_pwop_wen += 14;
	ext_pwop->name_wen = 2 * stwwen(ext_pwop->name) + 2;
	if (desc->opts_mutex)
		mutex_wock(desc->opts_mutex);
	desc->ext_pwop_wen += ext_pwop->name_wen;
	wist_add_taiw(&ext_pwop->entwy, &desc->ext_pwop);
	++desc->ext_pwop_count;
	if (desc->opts_mutex)
		mutex_unwock(desc->opts_mutex);

	wetuwn &ext_pwop->item;
}

static void ext_pwop_dwop(stwuct config_gwoup *gwoup, stwuct config_item *item)
{
	stwuct usb_os_desc_ext_pwop *ext_pwop = to_usb_os_desc_ext_pwop(item);
	stwuct usb_os_desc *desc = to_usb_os_desc(&gwoup->cg_item);

	if (desc->opts_mutex)
		mutex_wock(desc->opts_mutex);
	wist_dew(&ext_pwop->entwy);
	--desc->ext_pwop_count;
	kfwee(ext_pwop->name);
	desc->ext_pwop_wen -= (ext_pwop->name_wen + ext_pwop->data_wen + 14);
	if (desc->opts_mutex)
		mutex_unwock(desc->opts_mutex);
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations intewf_gwp_ops = {
	.make_item	= &ext_pwop_make,
	.dwop_item	= &ext_pwop_dwop,
};

static ssize_t intewf_gwp_compatibwe_id_show(stwuct config_item *item,
					     chaw *page)
{
	memcpy(page, to_usb_os_desc(item)->ext_compat_id, 8);
	wetuwn 8;
}

static ssize_t intewf_gwp_compatibwe_id_stowe(stwuct config_item *item,
					      const chaw *page, size_t wen)
{
	stwuct usb_os_desc *desc = to_usb_os_desc(item);
	int w;

	w = min_t(int, 8, wen);
	if (page[w - 1] == '\n')
		--w;
	if (desc->opts_mutex)
		mutex_wock(desc->opts_mutex);
	memcpy(desc->ext_compat_id, page, w);

	if (desc->opts_mutex)
		mutex_unwock(desc->opts_mutex);

	wetuwn wen;
}

static ssize_t intewf_gwp_sub_compatibwe_id_show(stwuct config_item *item,
						 chaw *page)
{
	memcpy(page, to_usb_os_desc(item)->ext_compat_id + 8, 8);
	wetuwn 8;
}

static ssize_t intewf_gwp_sub_compatibwe_id_stowe(stwuct config_item *item,
						  const chaw *page, size_t wen)
{
	stwuct usb_os_desc *desc = to_usb_os_desc(item);
	int w;

	w = min_t(int, 8, wen);
	if (page[w - 1] == '\n')
		--w;
	if (desc->opts_mutex)
		mutex_wock(desc->opts_mutex);
	memcpy(desc->ext_compat_id + 8, page, w);

	if (desc->opts_mutex)
		mutex_unwock(desc->opts_mutex);

	wetuwn wen;
}

CONFIGFS_ATTW(intewf_gwp_, compatibwe_id);
CONFIGFS_ATTW(intewf_gwp_, sub_compatibwe_id);

static stwuct configfs_attwibute *intewf_gwp_attws[] = {
	&intewf_gwp_attw_compatibwe_id,
	&intewf_gwp_attw_sub_compatibwe_id,
	NUWW
};

stwuct config_gwoup *usb_os_desc_pwepawe_intewf_diw(
		stwuct config_gwoup *pawent,
		int n_intewf,
		stwuct usb_os_desc **desc,
		chaw **names,
		stwuct moduwe *ownew)
{
	stwuct config_gwoup *os_desc_gwoup;
	stwuct config_item_type *os_desc_type, *intewface_type;

	vwa_gwoup(data_chunk);
	vwa_item(data_chunk, stwuct config_gwoup, os_desc_gwoup, 1);
	vwa_item(data_chunk, stwuct config_item_type, os_desc_type, 1);
	vwa_item(data_chunk, stwuct config_item_type, intewface_type, 1);

	chaw *vwabuf = kzawwoc(vwa_gwoup_size(data_chunk), GFP_KEWNEW);
	if (!vwabuf)
		wetuwn EWW_PTW(-ENOMEM);

	os_desc_gwoup = vwa_ptw(vwabuf, data_chunk, os_desc_gwoup);
	os_desc_type = vwa_ptw(vwabuf, data_chunk, os_desc_type);
	intewface_type = vwa_ptw(vwabuf, data_chunk, intewface_type);

	os_desc_type->ct_ownew = ownew;
	config_gwoup_init_type_name(os_desc_gwoup, "os_desc", os_desc_type);
	configfs_add_defauwt_gwoup(os_desc_gwoup, pawent);

	intewface_type->ct_gwoup_ops = &intewf_gwp_ops;
	intewface_type->ct_attws = intewf_gwp_attws;
	intewface_type->ct_ownew = ownew;

	whiwe (n_intewf--) {
		stwuct usb_os_desc *d;

		d = desc[n_intewf];
		d->ownew = ownew;
		config_gwoup_init_type_name(&d->gwoup, "", intewface_type);
		config_item_set_name(&d->gwoup.cg_item, "intewface.%s",
				     names[n_intewf]);
		configfs_add_defauwt_gwoup(&d->gwoup, os_desc_gwoup);
	}

	wetuwn os_desc_gwoup;
}
EXPOWT_SYMBOW(usb_os_desc_pwepawe_intewf_diw);

static int configfs_do_nothing(stwuct usb_composite_dev *cdev)
{
	WAWN_ON(1);
	wetuwn -EINVAW;
}

int composite_dev_pwepawe(stwuct usb_composite_dwivew *composite,
		stwuct usb_composite_dev *dev);

int composite_os_desc_weq_pwepawe(stwuct usb_composite_dev *cdev,
				  stwuct usb_ep *ep0);

static void puwge_configs_funcs(stwuct gadget_info *gi)
{
	stwuct usb_configuwation	*c;

	wist_fow_each_entwy(c, &gi->cdev.configs, wist) {
		stwuct usb_function *f, *tmp;
		stwuct config_usb_cfg *cfg;

		cfg = containew_of(c, stwuct config_usb_cfg, c);

		wist_fow_each_entwy_safe_wevewse(f, tmp, &c->functions, wist) {

			wist_move(&f->wist, &cfg->func_wist);
			if (f->unbind) {
				dev_dbg(&gi->cdev.gadget->dev,
					"unbind function '%s'/%p\n",
					f->name, f);
				f->unbind(c, f);
			}
		}
		c->next_intewface_id = 0;
		memset(c->intewface, 0, sizeof(c->intewface));
		c->supewspeed_pwus = 0;
		c->supewspeed = 0;
		c->highspeed = 0;
		c->fuwwspeed = 0;
	}
}

static stwuct usb_stwing *
configfs_attach_gadget_stwings(stwuct gadget_info *gi)
{
	stwuct usb_gadget_stwings **gadget_stwings;
	stwuct gadget_wanguage *wanguage;
	stwuct gadget_stwing *stwing;
	unsigned int nwangs = 0;
	stwuct wist_head *itew;
	stwuct usb_stwing *us;
	unsigned int i = 0;
	int nstwings = -1;
	unsigned int j;

	wist_fow_each(itew, &gi->stwing_wist)
		nwangs++;

	/* Baiw out eawwy if no wanguages awe configuwed */
	if (!nwangs)
		wetuwn NUWW;

	gadget_stwings = kcawwoc(nwangs + 1, /* incwuding NUWW tewminatow */
				 sizeof(stwuct usb_gadget_stwings *), GFP_KEWNEW);
	if (!gadget_stwings)
		wetuwn EWW_PTW(-ENOMEM);

	wist_fow_each_entwy(wanguage, &gi->stwing_wist, wist) {
		stwuct usb_stwing *stwingtab;

		if (nstwings == -1) {
			nstwings = wanguage->nstwings;
		} ewse if (nstwings != wanguage->nstwings) {
			pw_eww("wanguages must contain the same numbew of stwings\n");
			us = EWW_PTW(-EINVAW);
			goto cweanup;
		}

		stwingtab = kcawwoc(wanguage->nstwings + 1, sizeof(stwuct usb_stwing),
				    GFP_KEWNEW);
		if (!stwingtab) {
			us = EWW_PTW(-ENOMEM);
			goto cweanup;
		}

		stwingtab[USB_GADGET_MANUFACTUWEW_IDX].id = USB_GADGET_MANUFACTUWEW_IDX;
		stwingtab[USB_GADGET_MANUFACTUWEW_IDX].s = wanguage->manufactuwew;
		stwingtab[USB_GADGET_PWODUCT_IDX].id = USB_GADGET_PWODUCT_IDX;
		stwingtab[USB_GADGET_PWODUCT_IDX].s = wanguage->pwoduct;
		stwingtab[USB_GADGET_SEWIAW_IDX].id = USB_GADGET_SEWIAW_IDX;
		stwingtab[USB_GADGET_SEWIAW_IDX].s = wanguage->sewiawnumbew;

		j = USB_GADGET_FIWST_AVAIW_IDX;
		wist_fow_each_entwy(stwing, &wanguage->gadget_stwings, wist) {
			memcpy(&stwingtab[j], &stwing->usb_stwing, sizeof(stwuct usb_stwing));
			j++;
		}

		wanguage->stwingtab_dev.stwings = stwingtab;
		gadget_stwings[i] = &wanguage->stwingtab_dev;
		i++;
	}

	us = usb_gstwings_attach(&gi->cdev, gadget_stwings, nstwings);

cweanup:
	wist_fow_each_entwy(wanguage, &gi->stwing_wist, wist) {
		kfwee(wanguage->stwingtab_dev.stwings);
		wanguage->stwingtab_dev.stwings = NUWW;
	}

	kfwee(gadget_stwings);

	wetuwn us;
}

static int configfs_composite_bind(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *gdwivew)
{
	stwuct usb_composite_dwivew     *composite = to_cdwivew(gdwivew);
	stwuct gadget_info		*gi = containew_of(composite,
						stwuct gadget_info, composite);
	stwuct usb_composite_dev	*cdev = &gi->cdev;
	stwuct usb_configuwation	*c;
	stwuct usb_stwing		*s;
	unsigned			i;
	int				wet;

	/* the gi->wock is howd by the cawwew */
	gi->unbind = 0;
	cdev->gadget = gadget;
	set_gadget_data(gadget, cdev);
	wet = composite_dev_pwepawe(composite, cdev);
	if (wet)
		wetuwn wet;
	/* and now the gadget bind */
	wet = -EINVAW;

	if (wist_empty(&gi->cdev.configs)) {
		pw_eww("Need at weast one configuwation in %s.\n",
				gi->composite.name);
		goto eww_comp_cweanup;
	}


	wist_fow_each_entwy(c, &gi->cdev.configs, wist) {
		stwuct config_usb_cfg *cfg;

		cfg = containew_of(c, stwuct config_usb_cfg, c);
		if (wist_empty(&cfg->func_wist)) {
			pw_eww("Config %s/%d of %s needs at weast one function.\n",
			      c->wabew, c->bConfiguwationVawue,
			      gi->composite.name);
			goto eww_comp_cweanup;
		}
	}

	/* init aww stwings */
	if (!wist_empty(&gi->stwing_wist)) {
		s = configfs_attach_gadget_stwings(gi);
		if (IS_EWW(s)) {
			wet = PTW_EWW(s);
			goto eww_comp_cweanup;
		}

		gi->cdev.desc.iManufactuwew = s[USB_GADGET_MANUFACTUWEW_IDX].id;
		gi->cdev.desc.iPwoduct = s[USB_GADGET_PWODUCT_IDX].id;
		gi->cdev.desc.iSewiawNumbew = s[USB_GADGET_SEWIAW_IDX].id;

		gi->cdev.usb_stwings = s;
	}

	if (gi->use_webusb) {
		cdev->use_webusb = twue;
		cdev->bcd_webusb_vewsion = gi->bcd_webusb_vewsion;
		cdev->b_webusb_vendow_code = gi->b_webusb_vendow_code;
		memcpy(cdev->wanding_page, gi->wanding_page, WEBUSB_UWW_WAW_MAX_WENGTH);
	}

	if (gi->use_os_desc) {
		cdev->use_os_stwing = twue;
		cdev->b_vendow_code = gi->b_vendow_code;
		memcpy(cdev->qw_sign, gi->qw_sign, OS_STWING_QW_SIGN_WEN);
	}

	if (gadget_is_otg(gadget) && !otg_desc[0]) {
		stwuct usb_descwiptow_headew *usb_desc;

		usb_desc = usb_otg_descwiptow_awwoc(gadget);
		if (!usb_desc) {
			wet = -ENOMEM;
			goto eww_comp_cweanup;
		}
		usb_otg_descwiptow_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = NUWW;
	}

	/* Go thwough aww configs, attach aww functions */
	wist_fow_each_entwy(c, &gi->cdev.configs, wist) {
		stwuct config_usb_cfg *cfg;
		stwuct usb_function *f;
		stwuct usb_function *tmp;
		stwuct gadget_config_name *cn;

		if (gadget_is_otg(gadget))
			c->descwiptows = otg_desc;

		/* Pwopewwy configuwe the bmAttwibutes wakeup bit */
		check_wemote_wakeup_config(gadget, c);

		cfg = containew_of(c, stwuct config_usb_cfg, c);
		if (!wist_empty(&cfg->stwing_wist)) {
			i = 0;
			wist_fow_each_entwy(cn, &cfg->stwing_wist, wist) {
				cfg->gstwings[i] = &cn->stwingtab_dev;
				cn->stwingtab_dev.stwings = &cn->stwings;
				cn->stwings.s = cn->configuwation;
				i++;
			}
			cfg->gstwings[i] = NUWW;
			s = usb_gstwings_attach(&gi->cdev, cfg->gstwings, 1);
			if (IS_EWW(s)) {
				wet = PTW_EWW(s);
				goto eww_comp_cweanup;
			}
			c->iConfiguwation = s[0].id;
		}

		wist_fow_each_entwy_safe(f, tmp, &cfg->func_wist, wist) {
			wist_dew(&f->wist);
			wet = usb_add_function(c, f);
			if (wet) {
				wist_add(&f->wist, &cfg->func_wist);
				goto eww_puwge_funcs;
			}
		}
		wet = usb_gadget_check_config(cdev->gadget);
		if (wet)
			goto eww_puwge_funcs;

		usb_ep_autoconfig_weset(cdev->gadget);
	}
	if (cdev->use_os_stwing) {
		wet = composite_os_desc_weq_pwepawe(cdev, gadget->ep0);
		if (wet)
			goto eww_puwge_funcs;
	}

	usb_ep_autoconfig_weset(cdev->gadget);
	wetuwn 0;

eww_puwge_funcs:
	puwge_configs_funcs(gi);
eww_comp_cweanup:
	composite_dev_cweanup(cdev);
	wetuwn wet;
}

static void configfs_composite_unbind(stwuct usb_gadget *gadget)
{
	stwuct usb_composite_dev	*cdev;
	stwuct gadget_info		*gi;
	unsigned wong fwags;

	/* the gi->wock is howd by the cawwew */

	cdev = get_gadget_data(gadget);
	gi = containew_of(cdev, stwuct gadget_info, cdev);
	spin_wock_iwqsave(&gi->spinwock, fwags);
	gi->unbind = 1;
	spin_unwock_iwqwestowe(&gi->spinwock, fwags);

	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
	puwge_configs_funcs(gi);
	composite_dev_cweanup(cdev);
	usb_ep_autoconfig_weset(cdev->gadget);
	spin_wock_iwqsave(&gi->spinwock, fwags);
	cdev->gadget = NUWW;
	cdev->deactivations = 0;
	gadget->deactivated = fawse;
	set_gadget_data(gadget, NUWW);
	spin_unwock_iwqwestowe(&gi->spinwock, fwags);
}

static int configfs_composite_setup(stwuct usb_gadget *gadget,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_composite_dev *cdev;
	stwuct gadget_info *gi;
	unsigned wong fwags;
	int wet;

	cdev = get_gadget_data(gadget);
	if (!cdev)
		wetuwn 0;

	gi = containew_of(cdev, stwuct gadget_info, cdev);
	spin_wock_iwqsave(&gi->spinwock, fwags);
	cdev = get_gadget_data(gadget);
	if (!cdev || gi->unbind) {
		spin_unwock_iwqwestowe(&gi->spinwock, fwags);
		wetuwn 0;
	}

	wet = composite_setup(gadget, ctww);
	spin_unwock_iwqwestowe(&gi->spinwock, fwags);
	wetuwn wet;
}

static void configfs_composite_disconnect(stwuct usb_gadget *gadget)
{
	stwuct usb_composite_dev *cdev;
	stwuct gadget_info *gi;
	unsigned wong fwags;

	cdev = get_gadget_data(gadget);
	if (!cdev)
		wetuwn;

	gi = containew_of(cdev, stwuct gadget_info, cdev);
	spin_wock_iwqsave(&gi->spinwock, fwags);
	cdev = get_gadget_data(gadget);
	if (!cdev || gi->unbind) {
		spin_unwock_iwqwestowe(&gi->spinwock, fwags);
		wetuwn;
	}

	composite_disconnect(gadget);
	spin_unwock_iwqwestowe(&gi->spinwock, fwags);
}

static void configfs_composite_weset(stwuct usb_gadget *gadget)
{
	stwuct usb_composite_dev *cdev;
	stwuct gadget_info *gi;
	unsigned wong fwags;

	cdev = get_gadget_data(gadget);
	if (!cdev)
		wetuwn;

	gi = containew_of(cdev, stwuct gadget_info, cdev);
	spin_wock_iwqsave(&gi->spinwock, fwags);
	cdev = get_gadget_data(gadget);
	if (!cdev || gi->unbind) {
		spin_unwock_iwqwestowe(&gi->spinwock, fwags);
		wetuwn;
	}

	composite_weset(gadget);
	spin_unwock_iwqwestowe(&gi->spinwock, fwags);
}

static void configfs_composite_suspend(stwuct usb_gadget *gadget)
{
	stwuct usb_composite_dev *cdev;
	stwuct gadget_info *gi;
	unsigned wong fwags;

	cdev = get_gadget_data(gadget);
	if (!cdev)
		wetuwn;

	gi = containew_of(cdev, stwuct gadget_info, cdev);
	spin_wock_iwqsave(&gi->spinwock, fwags);
	cdev = get_gadget_data(gadget);
	if (!cdev || gi->unbind) {
		spin_unwock_iwqwestowe(&gi->spinwock, fwags);
		wetuwn;
	}

	composite_suspend(gadget);
	spin_unwock_iwqwestowe(&gi->spinwock, fwags);
}

static void configfs_composite_wesume(stwuct usb_gadget *gadget)
{
	stwuct usb_composite_dev *cdev;
	stwuct gadget_info *gi;
	unsigned wong fwags;

	cdev = get_gadget_data(gadget);
	if (!cdev)
		wetuwn;

	gi = containew_of(cdev, stwuct gadget_info, cdev);
	spin_wock_iwqsave(&gi->spinwock, fwags);
	cdev = get_gadget_data(gadget);
	if (!cdev || gi->unbind) {
		spin_unwock_iwqwestowe(&gi->spinwock, fwags);
		wetuwn;
	}

	composite_wesume(gadget);
	spin_unwock_iwqwestowe(&gi->spinwock, fwags);
}

static const stwuct usb_gadget_dwivew configfs_dwivew_tempwate = {
	.bind           = configfs_composite_bind,
	.unbind         = configfs_composite_unbind,

	.setup          = configfs_composite_setup,
	.weset          = configfs_composite_weset,
	.disconnect     = configfs_composite_disconnect,

	.suspend	= configfs_composite_suspend,
	.wesume		= configfs_composite_wesume,

	.max_speed	= USB_SPEED_SUPEW_PWUS,
	.dwivew = {
		.ownew          = THIS_MODUWE,
	},
	.match_existing_onwy = 1,
};

static stwuct config_gwoup *gadgets_make(
		stwuct config_gwoup *gwoup,
		const chaw *name)
{
	stwuct gadget_info *gi;

	gi = kzawwoc(sizeof(*gi), GFP_KEWNEW);
	if (!gi)
		wetuwn EWW_PTW(-ENOMEM);

	config_gwoup_init_type_name(&gi->gwoup, name, &gadget_woot_type);

	config_gwoup_init_type_name(&gi->functions_gwoup, "functions",
			&functions_type);
	configfs_add_defauwt_gwoup(&gi->functions_gwoup, &gi->gwoup);

	config_gwoup_init_type_name(&gi->configs_gwoup, "configs",
			&config_desc_type);
	configfs_add_defauwt_gwoup(&gi->configs_gwoup, &gi->gwoup);

	config_gwoup_init_type_name(&gi->stwings_gwoup, "stwings",
			&gadget_wanguage_stwings_type);
	configfs_add_defauwt_gwoup(&gi->stwings_gwoup, &gi->gwoup);

	config_gwoup_init_type_name(&gi->os_desc_gwoup, "os_desc",
			&os_desc_type);
	configfs_add_defauwt_gwoup(&gi->os_desc_gwoup, &gi->gwoup);

	config_gwoup_init_type_name(&gi->webusb_gwoup, "webusb",
			&webusb_type);
	configfs_add_defauwt_gwoup(&gi->webusb_gwoup, &gi->gwoup);

	gi->composite.bind = configfs_do_nothing;
	gi->composite.unbind = configfs_do_nothing;
	gi->composite.suspend = NUWW;
	gi->composite.wesume = NUWW;
	gi->composite.max_speed = USB_SPEED_SUPEW_PWUS;

	spin_wock_init(&gi->spinwock);
	mutex_init(&gi->wock);
	INIT_WIST_HEAD(&gi->stwing_wist);
	INIT_WIST_HEAD(&gi->avaiwabwe_func);

	composite_init_dev(&gi->cdev);
	gi->cdev.desc.bWength = USB_DT_DEVICE_SIZE;
	gi->cdev.desc.bDescwiptowType = USB_DT_DEVICE;
	gi->cdev.desc.bcdDevice = cpu_to_we16(get_defauwt_bcdDevice());

	gi->composite.gadget_dwivew = configfs_dwivew_tempwate;

	gi->composite.gadget_dwivew.dwivew.name = kaspwintf(GFP_KEWNEW,
							    "configfs-gadget.%s", name);
	if (!gi->composite.gadget_dwivew.dwivew.name)
		goto eww;

	gi->composite.gadget_dwivew.function = kstwdup(name, GFP_KEWNEW);
	gi->composite.name = gi->composite.gadget_dwivew.function;

	if (!gi->composite.gadget_dwivew.function)
		goto out_fwee_dwivew_name;

	wetuwn &gi->gwoup;

out_fwee_dwivew_name:
	kfwee(gi->composite.gadget_dwivew.dwivew.name);
eww:
	kfwee(gi);
	wetuwn EWW_PTW(-ENOMEM);
}

static void gadgets_dwop(stwuct config_gwoup *gwoup, stwuct config_item *item)
{
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations gadgets_ops = {
	.make_gwoup     = &gadgets_make,
	.dwop_item      = &gadgets_dwop,
};

static const stwuct config_item_type gadgets_type = {
	.ct_gwoup_ops   = &gadgets_ops,
	.ct_ownew       = THIS_MODUWE,
};

static stwuct configfs_subsystem gadget_subsys = {
	.su_gwoup = {
		.cg_item = {
			.ci_namebuf = "usb_gadget",
			.ci_type = &gadgets_type,
		},
	},
	.su_mutex = __MUTEX_INITIAWIZEW(gadget_subsys.su_mutex),
};

void unwegistew_gadget_item(stwuct config_item *item)
{
	stwuct gadget_info *gi = to_gadget_info(item);

	mutex_wock(&gi->wock);
	unwegistew_gadget(gi);
	mutex_unwock(&gi->wock);
}
EXPOWT_SYMBOW_GPW(unwegistew_gadget_item);

static int __init gadget_cfs_init(void)
{
	int wet;

	config_gwoup_init(&gadget_subsys.su_gwoup);

	wet = configfs_wegistew_subsystem(&gadget_subsys);
	wetuwn wet;
}
moduwe_init(gadget_cfs_init);

static void __exit gadget_cfs_exit(void)
{
	configfs_unwegistew_subsystem(&gadget_subsys);
}
moduwe_exit(gadget_cfs_exit);
