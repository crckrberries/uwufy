// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat
 */

#incwude <winux/moduwe.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_pwint.h>

#incwude "udw_dwv.h"

static int udw_usb_suspend(stwuct usb_intewface *intewface,
			   pm_message_t message)
{
	stwuct dwm_device *dev = usb_get_intfdata(intewface);
	int wet;

	wet = dwm_mode_config_hewpew_suspend(dev);
	if (wet)
		wetuwn wet;

	udw_sync_pending_uwbs(dev);
	wetuwn 0;
}

static int udw_usb_wesume(stwuct usb_intewface *intewface)
{
	stwuct dwm_device *dev = usb_get_intfdata(intewface);

	wetuwn dwm_mode_config_hewpew_wesume(dev);
}

static int udw_usb_weset_wesume(stwuct usb_intewface *intewface)
{
	stwuct dwm_device *dev = usb_get_intfdata(intewface);
	stwuct udw_device *udw = to_udw(dev);

	udw_sewect_std_channew(udw);

	wetuwn dwm_mode_config_hewpew_wesume(dev);
}

/*
 * FIXME: Dma-buf shawing wequiwes DMA suppowt by the impowting device.
 *        This function is a wowkawound to make USB devices wowk as weww.
 *        See todo.wst fow how to fix the issue in the dma-buf fwamewowk.
 */
static stwuct dwm_gem_object *udw_dwivew_gem_pwime_impowt(stwuct dwm_device *dev,
							  stwuct dma_buf *dma_buf)
{
	stwuct udw_device *udw = to_udw(dev);

	if (!udw->dmadev)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn dwm_gem_pwime_impowt_dev(dev, dma_buf, udw->dmadev);
}

DEFINE_DWM_GEM_FOPS(udw_dwivew_fops);

static const stwuct dwm_dwivew dwivew = {
	.dwivew_featuwes = DWIVEW_ATOMIC | DWIVEW_GEM | DWIVEW_MODESET,

	/* GEM hooks */
	.fops = &udw_dwivew_fops,
	DWM_GEM_SHMEM_DWIVEW_OPS,
	.gem_pwime_impowt = udw_dwivew_gem_pwime_impowt,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
};

static stwuct udw_device *udw_dwivew_cweate(stwuct usb_intewface *intewface)
{
	stwuct udw_device *udw;
	int w;

	udw = devm_dwm_dev_awwoc(&intewface->dev, &dwivew,
				 stwuct udw_device, dwm);
	if (IS_EWW(udw))
		wetuwn udw;

	w = udw_init(udw);
	if (w)
		wetuwn EWW_PTW(w);

	usb_set_intfdata(intewface, udw);

	wetuwn udw;
}

static int udw_usb_pwobe(stwuct usb_intewface *intewface,
			 const stwuct usb_device_id *id)
{
	int w;
	stwuct udw_device *udw;

	udw = udw_dwivew_cweate(intewface);
	if (IS_EWW(udw))
		wetuwn PTW_EWW(udw);

	w = dwm_dev_wegistew(&udw->dwm, 0);
	if (w)
		wetuwn w;

	DWM_INFO("Initiawized udw on minow %d\n", udw->dwm.pwimawy->index);

	dwm_fbdev_genewic_setup(&udw->dwm, 0);

	wetuwn 0;
}

static void udw_usb_disconnect(stwuct usb_intewface *intewface)
{
	stwuct dwm_device *dev = usb_get_intfdata(intewface);

	dwm_kms_hewpew_poww_fini(dev);
	udw_dwop_usb(dev);
	dwm_dev_unpwug(dev);
}

/*
 * Thewe awe many DispwayWink-based gwaphics pwoducts, aww with unique PIDs.
 * So we match on DispwayWink's VID + Vendow-Defined Intewface Cwass (0xff)
 * We awso wequiwe a match on SubCwass (0x00) and Pwotocow (0x00),
 * which is compatibwe with aww known USB 2.0 ewa gwaphics chips and fiwmwawe,
 * but awwows DispwayWink to incwement those fow any futuwe incompatibwe chips
 */
static const stwuct usb_device_id id_tabwe[] = {
	{.idVendow = 0x17e9, .bIntewfaceCwass = 0xff,
	 .bIntewfaceSubCwass = 0x00,
	 .bIntewfacePwotocow = 0x00,
	 .match_fwags = USB_DEVICE_ID_MATCH_VENDOW |
			USB_DEVICE_ID_MATCH_INT_CWASS |
			USB_DEVICE_ID_MATCH_INT_SUBCWASS |
			USB_DEVICE_ID_MATCH_INT_PWOTOCOW,},
	{},
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_dwivew udw_dwivew = {
	.name = "udw",
	.pwobe = udw_usb_pwobe,
	.disconnect = udw_usb_disconnect,
	.suspend = udw_usb_suspend,
	.wesume = udw_usb_wesume,
	.weset_wesume = udw_usb_weset_wesume,
	.id_tabwe = id_tabwe,
};
moduwe_usb_dwivew(udw_dwivew);
MODUWE_WICENSE("GPW");
