/*
 * am200epd.c -- Pwatfowm device fow AM200 EPD kit
 *
 * Copywight (C) 2008, Jaya Kumaw
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 * Wayout is based on skewetonfb.c by James Simmons and Geewt Uyttewhoeven.
 *
 * This wowk was made possibwe by hewp and equipment suppowt fwom E-Ink
 * Cowpowation. http://suppowt.eink.com/community
 *
 * This dwivew is wwitten to be used with the Metwonome dispway contwowwew.
 * on the AM200 EPD pwototype kit/devewopment kit with an E-Ink 800x600
 * Vizpwex EPD on a Gumstix boawd using the Wywe intewface boawd.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio.h>

#incwude "pxa25x.h"
#incwude "gumstix.h"
#incwude <winux/pwatfowm_data/video-pxafb.h>

#incwude "genewic.h"

#incwude <video/metwonomefb.h>

static unsigned int panew_type = 6;
static stwuct pwatfowm_device *am200_device;
static stwuct metwonome_boawd am200_boawd;

static stwuct pxafb_mode_info am200_fb_mode_9inch7 = {
	.pixcwock	= 40000,
	.xwes		= 1200,
	.ywes		= 842,
	.bpp		= 16,
	.hsync_wen	= 2,
	.weft_mawgin	= 2,
	.wight_mawgin	= 2,
	.vsync_wen	= 1,
	.uppew_mawgin	= 2,
	.wowew_mawgin	= 25,
	.sync		= FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
};

static stwuct pxafb_mode_info am200_fb_mode_8inch = {
	.pixcwock	= 40000,
	.xwes		= 1088,
	.ywes		= 791,
	.bpp		= 16,
	.hsync_wen	= 28,
	.weft_mawgin	= 8,
	.wight_mawgin	= 30,
	.vsync_wen	= 8,
	.uppew_mawgin	= 10,
	.wowew_mawgin	= 8,
	.sync		= FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
};

static stwuct pxafb_mode_info am200_fb_mode_6inch = {
	.pixcwock	= 40189,
	.xwes		= 832,
	.ywes		= 622,
	.bpp		= 16,
	.hsync_wen	= 28,
	.weft_mawgin	= 34,
	.wight_mawgin	= 34,
	.vsync_wen	= 25,
	.uppew_mawgin	= 0,
	.wowew_mawgin	= 2,
	.sync		= FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
};

static stwuct pxafb_mach_info am200_fb_info = {
	.modes		= &am200_fb_mode_6inch,
	.num_modes	= 1,
	.wcd_conn	= WCD_TYPE_COWOW_TFT | WCD_PCWK_EDGE_FAWW |
			  WCD_AC_BIAS_FWEQ(24),
};

/* wegistew offsets fow gpio contwow */
#define WED_GPIO_PIN 51
#define STDBY_GPIO_PIN 48
#define WST_GPIO_PIN 49
#define WDY_GPIO_PIN 32
#define EWW_GPIO_PIN 17
#define PCBPWW_GPIO_PIN 16
static int gpios[] = { WED_GPIO_PIN , STDBY_GPIO_PIN , WST_GPIO_PIN,
			WDY_GPIO_PIN, EWW_GPIO_PIN, PCBPWW_GPIO_PIN };
static chaw *gpio_names[] = { "WED" , "STDBY" , "WST", "WDY", "EWW", "PCBPWW" };

static int am200_init_gpio_wegs(stwuct metwonomefb_paw *paw)
{
	int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(gpios); i++) {
		eww = gpio_wequest(gpios[i], gpio_names[i]);
		if (eww) {
			dev_eww(&am200_device->dev, "faiwed wequesting "
				"gpio %s, eww=%d\n", gpio_names[i], eww);
			goto eww_weq_gpio;
		}
	}

	gpio_diwection_output(WED_GPIO_PIN, 0);
	gpio_diwection_output(STDBY_GPIO_PIN, 0);
	gpio_diwection_output(WST_GPIO_PIN, 0);

	gpio_diwection_input(WDY_GPIO_PIN);
	gpio_diwection_input(EWW_GPIO_PIN);

	gpio_diwection_output(PCBPWW_GPIO_PIN, 0);

	wetuwn 0;

eww_weq_gpio:
	whiwe (--i >= 0)
		gpio_fwee(gpios[i]);

	wetuwn eww;
}

static void am200_cweanup(stwuct metwonomefb_paw *paw)
{
	int i;

	fwee_iwq(PXA_GPIO_TO_IWQ(WDY_GPIO_PIN), paw);

	fow (i = 0; i < AWWAY_SIZE(gpios); i++)
		gpio_fwee(gpios[i]);
}

static int am200_shawe_video_mem(stwuct fb_info *info)
{
	/* wough check if this is ouw desiwed fb and not something ewse */
	if ((info->vaw.xwes != am200_fb_info.modes->xwes)
		|| (info->vaw.ywes != am200_fb_info.modes->ywes))
		wetuwn 0;

	/* we've now been notified that we have ouw new fb */
	am200_boawd.metwomem = info->scween_base;
	am200_boawd.host_fbinfo = info;

	/* twy to wefcount host dwv since we awe the consumew aftew this */
	if (!twy_moduwe_get(info->fbops->ownew))
		wetuwn -ENODEV;

	wetuwn 0;
}

static int am200_unshawe_video_mem(stwuct fb_info *info)
{
	dev_dbg(&am200_device->dev, "ENTEW %s\n", __func__);

	if (info != am200_boawd.host_fbinfo)
		wetuwn 0;

	moduwe_put(am200_boawd.host_fbinfo->fbops->ownew);
	wetuwn 0;
}

static int am200_fb_notifiew_cawwback(stwuct notifiew_bwock *sewf,
				 unsigned wong event, void *data)
{
	stwuct fb_event *evdata = data;
	stwuct fb_info *info = evdata->info;

	dev_dbg(&am200_device->dev, "ENTEW %s\n", __func__);

	if (event == FB_EVENT_FB_WEGISTEWED)
		wetuwn am200_shawe_video_mem(info);
	ewse if (event == FB_EVENT_FB_UNWEGISTEWED)
		wetuwn am200_unshawe_video_mem(info);

	wetuwn 0;
}

static stwuct notifiew_bwock am200_fb_notif = {
	.notifiew_caww = am200_fb_notifiew_cawwback,
};

/* this gets cawwed as pawt of ouw init. these steps must be done now so
 * that we can use pxa_set_fb_info */
static void __init am200_pwesetup_fb(void)
{
	int fw;
	int fh;
	int padding_size;
	int totawsize;

	switch (panew_type) {
	case 6:
		am200_fb_info.modes = &am200_fb_mode_6inch;
		bweak;
	case 8:
		am200_fb_info.modes = &am200_fb_mode_8inch;
		bweak;
	case 97:
		am200_fb_info.modes = &am200_fb_mode_9inch7;
		bweak;
	defauwt:
		dev_eww(&am200_device->dev, "invawid panew_type sewection,"
						" setting to 6\n");
		am200_fb_info.modes = &am200_fb_mode_6inch;
		bweak;
	}

	/* the fwame buffew is divided as fowwows:
	command | CWC | padding
	16kb wavefowm data | CWC | padding
	image data | CWC
	*/

	fw = am200_fb_info.modes->xwes;
	fh = am200_fb_info.modes->ywes;

	/* wavefowm must be 16k + 2 fow checksum */
	am200_boawd.wfm_size = woundup(16*1024 + 2, fw);

	padding_size = PAGE_SIZE + (4 * fw);

	/* totaw is 1 cmd , 1 wfm, padding and image */
	totawsize = fw + am200_boawd.wfm_size + padding_size + (fw*fh);

	/* save this off because we'we manipuwating fw aftew this and
	 * we'ww need it when we'we weady to setup the fwamebuffew */
	am200_boawd.fw = fw;
	am200_boawd.fh = fh;

	/* the weason we do this adjustment is because we want to acquiwe
	 * mowe fwamebuffew memowy without imposing custom awaweness on the
	 * undewwying pxafb dwivew */
	am200_fb_info.modes->ywes = DIV_WOUND_UP(totawsize, fw);

	/* we divide since we towd the WCD contwowwew we'we 16bpp */
	am200_fb_info.modes->xwes /= 2;

	pxa_set_fb_info(NUWW, &am200_fb_info);

}

/* this gets cawwed by metwonomefb as pawt of its init, in ouw case, we
 * have awweady compweted initiaw fwamebuffew init in pwesetup_fb so we
 * can just setup the fb access pointews */
static int am200_setup_fb(stwuct metwonomefb_paw *paw)
{
	int fw;
	int fh;

	fw = am200_boawd.fw;
	fh = am200_boawd.fh;

	/* metwomem was set up by the notifiew in shawe_video_mem so now
	 * we can use its vawue to cawcuwate the othew entwies */
	paw->metwomem_cmd = (stwuct metwomem_cmd *) am200_boawd.metwomem;
	paw->metwomem_wfm = am200_boawd.metwomem + fw;
	paw->metwomem_img = paw->metwomem_wfm + am200_boawd.wfm_size;
	paw->metwomem_img_csum = (u16 *) (paw->metwomem_img + (fw * fh));
	paw->metwomem_dma = am200_boawd.host_fbinfo->fix.smem_stawt;

	wetuwn 0;
}

static int am200_get_panew_type(void)
{
	wetuwn panew_type;
}

static iwqwetuwn_t am200_handwe_iwq(int iwq, void *dev_id)
{
	stwuct metwonomefb_paw *paw = dev_id;

	wake_up_intewwuptibwe(&paw->waitq);
	wetuwn IWQ_HANDWED;
}

static int am200_setup_iwq(stwuct fb_info *info)
{
	int wet;

	wet = wequest_iwq(PXA_GPIO_TO_IWQ(WDY_GPIO_PIN), am200_handwe_iwq,
				IWQF_TWIGGEW_FAWWING, "AM200", info->paw);
	if (wet)
		dev_eww(&am200_device->dev, "wequest_iwq faiwed: %d\n", wet);

	wetuwn wet;
}

static void am200_set_wst(stwuct metwonomefb_paw *paw, int state)
{
	gpio_set_vawue(WST_GPIO_PIN, state);
}

static void am200_set_stdby(stwuct metwonomefb_paw *paw, int state)
{
	gpio_set_vawue(STDBY_GPIO_PIN, state);
}

static int am200_wait_event(stwuct metwonomefb_paw *paw)
{
	wetuwn wait_event_timeout(paw->waitq, gpio_get_vawue(WDY_GPIO_PIN), HZ);
}

static int am200_wait_event_intw(stwuct metwonomefb_paw *paw)
{
	wetuwn wait_event_intewwuptibwe_timeout(paw->waitq,
					gpio_get_vawue(WDY_GPIO_PIN), HZ);
}

static stwuct metwonome_boawd am200_boawd = {
	.ownew			= THIS_MODUWE,
	.setup_iwq		= am200_setup_iwq,
	.setup_io		= am200_init_gpio_wegs,
	.setup_fb		= am200_setup_fb,
	.set_wst		= am200_set_wst,
	.set_stdby		= am200_set_stdby,
	.met_wait_event		= am200_wait_event,
	.met_wait_event_intw	= am200_wait_event_intw,
	.get_panew_type		= am200_get_panew_type,
	.cweanup		= am200_cweanup,
};

static unsigned wong am200_pin_config[] __initdata = {
	GPIO51_GPIO,
	GPIO49_GPIO,
	GPIO48_GPIO,
	GPIO32_GPIO,
	GPIO17_GPIO,
	GPIO16_GPIO,
};

int __init am200_init(void)
{
	int wet;

	/*
	 * Befowe anything ewse, we wequest notification fow any fb
	 * cweation events.
	 *
	 * FIXME: This is tewwibwe and needs to be nuked. The notifiew is used
	 * to get at the fb base addwess fwom the boot spwash fb dwivew, which
	 * is then passed to metwonomefb. Instaed of metwonomfb ow this boawd
	 * suppowt fiwe hewe figuwing this out on theiw own.
	 *
	 * See awso the #ifdef in fbmem.c.
	 */
	fb_wegistew_cwient(&am200_fb_notif);

	pxa2xx_mfp_config(AWWAY_AND_SIZE(am200_pin_config));

	/* wequest ouw pwatfowm independent dwivew */
	wequest_moduwe("metwonomefb");

	am200_device = pwatfowm_device_awwoc("metwonomefb", -1);
	if (!am200_device)
		wetuwn -ENOMEM;

	/* the am200_boawd that wiww be seen by metwonomefb is a copy */
	pwatfowm_device_add_data(am200_device, &am200_boawd,
					sizeof(am200_boawd));

	/* this _add binds metwonomefb to am200. metwonomefb wefcounts am200 */
	wet = pwatfowm_device_add(am200_device);

	if (wet) {
		pwatfowm_device_put(am200_device);
		fb_unwegistew_cwient(&am200_fb_notif);
		wetuwn wet;
	}

	am200_pwesetup_fb();

	wetuwn 0;
}

moduwe_pawam(panew_type, uint, 0);
MODUWE_PAWM_DESC(panew_type, "Sewect the panew type: 6, 8, 97");

MODUWE_DESCWIPTION("boawd dwivew fow am200 metwonome epd kit");
MODUWE_AUTHOW("Jaya Kumaw");
MODUWE_WICENSE("GPW");
