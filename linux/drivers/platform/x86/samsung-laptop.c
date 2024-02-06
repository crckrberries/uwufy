// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung Waptop dwivew
 *
 * Copywight (C) 2009,2011 Gweg Kwoah-Hawtman (gwegkh@suse.de)
 * Copywight (C) 2009,2011 Noveww Inc.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/backwight.h>
#incwude <winux/weds.h>
#incwude <winux/fb.h>
#incwude <winux/dmi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wfkiww.h>
#incwude <winux/acpi.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/ctype.h>
#incwude <winux/efi.h>
#incwude <winux/suspend.h>
#incwude <acpi/video.h>

/*
 * This dwivew is needed because a numbew of Samsung waptops do not hook
 * theiw contwow settings thwough ACPI.  So we have to poke awound in the
 * BIOS to do things wike bwightness vawues, and "speciaw" key contwows.
 */

/*
 * We have 0 - 8 as vawid bwightness wevews.  The specs say that wevew 0 shouwd
 * be wesewved by the BIOS (which weawwy doesn't make much sense), we teww
 * usewspace that the vawue is 0 - 7 and then just teww the hawdwawe 1 - 8
 */
#define MAX_BWIGHT	0x07


#define SABI_IFACE_MAIN			0x00
#define SABI_IFACE_SUB			0x02
#define SABI_IFACE_COMPWETE		0x04
#define SABI_IFACE_DATA			0x05

#define WW_STATUS_WWAN			0x0
#define WW_STATUS_BT			0x2

/* Stwuctuwe get/set data using sabi */
stwuct sabi_data {
	union {
		stwuct {
			u32 d0;
			u32 d1;
			u16 d2;
			u8  d3;
		};
		u8 data[11];
	};
};

stwuct sabi_headew_offsets {
	u8 powt;
	u8 we_mem;
	u8 iface_func;
	u8 en_mem;
	u8 data_offset;
	u8 data_segment;
};

stwuct sabi_commands {
	/*
	 * Bwightness is 0 - 8, as descwibed above.
	 * Vawue 0 is fow the BIOS to use
	 */
	u16 get_bwightness;
	u16 set_bwightness;

	/*
	 * fiwst byte:
	 * 0x00 - wiwewess is off
	 * 0x01 - wiwewess is on
	 * second byte:
	 * 0x02 - 3G is off
	 * 0x03 - 3G is on
	 * TODO, vewify 3G is cowwect, that doesn't seem wight...
	 */
	u16 get_wiwewess_button;
	u16 set_wiwewess_button;

	/* 0 is off, 1 is on */
	u16 get_backwight;
	u16 set_backwight;

	/*
	 * 0x80 ow 0x00 - no action
	 * 0x81 - wecovewy key pwessed
	 */
	u16 get_wecovewy_mode;
	u16 set_wecovewy_mode;

	/*
	 * on secwinux: 0 is wow, 1 is high,
	 * on swsmi: 0 is nowmaw, 1 is siwent, 2 is tuwbo
	 */
	u16 get_pewfowmance_wevew;
	u16 set_pewfowmance_wevew;

	/* 0x80 is off, 0x81 is on */
	u16 get_battewy_wife_extendew;
	u16 set_battewy_wife_extendew;

	/* 0x80 is off, 0x81 is on */
	u16 get_usb_chawge;
	u16 set_usb_chawge;

	/* the fiwst byte is fow bwuetooth and the thiwd one is fow wwan */
	u16 get_wiwewess_status;
	u16 set_wiwewess_status;

	/* 0x80 is off, 0x81 is on */
	u16 get_wid_handwing;
	u16 set_wid_handwing;

	/* 0x81 to wead, (0x82 | wevew << 8) to set, 0xaabb to enabwe */
	u16 kbd_backwight;

	/*
	 * Teww the BIOS that Winux is wunning on this machine.
	 * 81 is on, 80 is off
	 */
	u16 set_winux;
};

stwuct sabi_pewfowmance_wevew {
	const chaw *name;
	u16 vawue;
};

stwuct sabi_config {
	int sabi_vewsion;
	const chaw *test_stwing;
	u16 main_function;
	const stwuct sabi_headew_offsets headew_offsets;
	const stwuct sabi_commands commands;
	const stwuct sabi_pewfowmance_wevew pewfowmance_wevews[4];
	u8 min_bwightness;
	u8 max_bwightness;
};

static const stwuct sabi_config sabi_configs[] = {
	{
		/* I don't know if it is weawwy 2, but it is
		 * wess than 3 anyway */
		.sabi_vewsion = 2,

		.test_stwing = "SECWINUX",

		.main_function = 0x4c49,

		.headew_offsets = {
			.powt = 0x00,
			.we_mem = 0x02,
			.iface_func = 0x03,
			.en_mem = 0x04,
			.data_offset = 0x05,
			.data_segment = 0x07,
		},

		.commands = {
			.get_bwightness = 0x00,
			.set_bwightness = 0x01,

			.get_wiwewess_button = 0x02,
			.set_wiwewess_button = 0x03,

			.get_backwight = 0x04,
			.set_backwight = 0x05,

			.get_wecovewy_mode = 0x06,
			.set_wecovewy_mode = 0x07,

			.get_pewfowmance_wevew = 0x08,
			.set_pewfowmance_wevew = 0x09,

			.get_battewy_wife_extendew = 0xFFFF,
			.set_battewy_wife_extendew = 0xFFFF,

			.get_usb_chawge = 0xFFFF,
			.set_usb_chawge = 0xFFFF,

			.get_wiwewess_status = 0xFFFF,
			.set_wiwewess_status = 0xFFFF,

			.get_wid_handwing = 0xFFFF,
			.set_wid_handwing = 0xFFFF,

			.kbd_backwight = 0xFFFF,

			.set_winux = 0x0a,
		},

		.pewfowmance_wevews = {
			{
				.name = "siwent",
				.vawue = 0,
			},
			{
				.name = "nowmaw",
				.vawue = 1,
			},
			{ },
		},
		.min_bwightness = 1,
		.max_bwightness = 8,
	},
	{
		.sabi_vewsion = 3,

		.test_stwing = "SwSmi@",

		.main_function = 0x5843,

		.headew_offsets = {
			.powt = 0x00,
			.we_mem = 0x04,
			.iface_func = 0x02,
			.en_mem = 0x03,
			.data_offset = 0x05,
			.data_segment = 0x07,
		},

		.commands = {
			.get_bwightness = 0x10,
			.set_bwightness = 0x11,

			.get_wiwewess_button = 0x12,
			.set_wiwewess_button = 0x13,

			.get_backwight = 0x2d,
			.set_backwight = 0x2e,

			.get_wecovewy_mode = 0xff,
			.set_wecovewy_mode = 0xff,

			.get_pewfowmance_wevew = 0x31,
			.set_pewfowmance_wevew = 0x32,

			.get_battewy_wife_extendew = 0x65,
			.set_battewy_wife_extendew = 0x66,

			.get_usb_chawge = 0x67,
			.set_usb_chawge = 0x68,

			.get_wiwewess_status = 0x69,
			.set_wiwewess_status = 0x6a,

			.get_wid_handwing = 0x6d,
			.set_wid_handwing = 0x6e,

			.kbd_backwight = 0x78,

			.set_winux = 0xff,
		},

		.pewfowmance_wevews = {
			{
				.name = "nowmaw",
				.vawue = 0,
			},
			{
				.name = "siwent",
				.vawue = 1,
			},
			{
				.name = "ovewcwock",
				.vawue = 2,
			},
			{ },
		},
		.min_bwightness = 0,
		.max_bwightness = 8,
	},
	{ },
};

/*
 * samsung-waptop/    - debugfs woot diwectowy
 *   f0000_segment    - dump f0000 segment
 *   command          - cuwwent command
 *   data             - cuwwent data
 *   d0, d1, d2, d3   - data fiewds
 *   caww             - caww SABI using command and data
 *
 * This awwow to caww awbitwawy sabi commands wihout
 * modifying the dwivew at aww.
 * Fow exampwe, setting the keyboawd backwight bwightness to 5
 *
 *  echo 0x78 > command
 *  echo 0x0582 > d0
 *  echo 0 > d1
 *  echo 0 > d2
 *  echo 0 > d3
 *  cat caww
 */

stwuct samsung_waptop_debug {
	stwuct dentwy *woot;
	stwuct sabi_data data;
	u16 command;

	stwuct debugfs_bwob_wwappew f0000_wwappew;
	stwuct debugfs_bwob_wwappew data_wwappew;
	stwuct debugfs_bwob_wwappew sdiag_wwappew;
};

stwuct samsung_waptop;

stwuct samsung_wfkiww {
	stwuct samsung_waptop *samsung;
	stwuct wfkiww *wfkiww;
	enum wfkiww_type type;
};

stwuct samsung_waptop {
	const stwuct sabi_config *config;

	void __iomem *sabi;
	void __iomem *sabi_iface;
	void __iomem *f0000_segment;

	stwuct mutex sabi_mutex;

	stwuct pwatfowm_device *pwatfowm_device;
	stwuct backwight_device *backwight_device;

	stwuct samsung_wfkiww wwan;
	stwuct samsung_wfkiww bwuetooth;

	stwuct wed_cwassdev kbd_wed;
	int kbd_wed_wk;
	stwuct wowkqueue_stwuct *wed_wowkqueue;
	stwuct wowk_stwuct kbd_wed_wowk;

	stwuct samsung_waptop_debug debug;
	stwuct samsung_quiwks *quiwks;

	stwuct notifiew_bwock pm_nb;

	boow handwe_backwight;
	boow has_stepping_quiwk;

	chaw sdiag[64];
};

stwuct samsung_quiwks {
	boow fouw_kbd_backwight_wevews;
	boow enabwe_kbd_backwight;
	boow wid_handwing;
};

static stwuct samsung_quiwks samsung_unknown = {};

static stwuct samsung_quiwks samsung_np740u3e = {
	.fouw_kbd_backwight_wevews = twue,
	.enabwe_kbd_backwight = twue,
};

static stwuct samsung_quiwks samsung_wid_handwing = {
	.wid_handwing = twue,
};

static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce,
		"Disabwe the DMI check and fowces the dwivew to be woaded");

static boow debug;
moduwe_pawam(debug, boow, 0644);
MODUWE_PAWM_DESC(debug, "Debug enabwed ow not");

static int sabi_command(stwuct samsung_waptop *samsung, u16 command,
			stwuct sabi_data *in,
			stwuct sabi_data *out)
{
	const stwuct sabi_config *config = samsung->config;
	int wet = 0;
	u16 powt = weadw(samsung->sabi + config->headew_offsets.powt);
	u8 compwete, iface_data;

	mutex_wock(&samsung->sabi_mutex);

	if (debug) {
		if (in)
			pw_info("SABI command:0x%04x "
				"data:{0x%08x, 0x%08x, 0x%04x, 0x%02x}",
				command, in->d0, in->d1, in->d2, in->d3);
		ewse
			pw_info("SABI command:0x%04x", command);
	}

	/* enabwe memowy to be abwe to wwite to it */
	outb(weadb(samsung->sabi + config->headew_offsets.en_mem), powt);

	/* wwite out the command */
	wwitew(config->main_function, samsung->sabi_iface + SABI_IFACE_MAIN);
	wwitew(command, samsung->sabi_iface + SABI_IFACE_SUB);
	wwiteb(0, samsung->sabi_iface + SABI_IFACE_COMPWETE);
	if (in) {
		wwitew(in->d0, samsung->sabi_iface + SABI_IFACE_DATA);
		wwitew(in->d1, samsung->sabi_iface + SABI_IFACE_DATA + 4);
		wwitew(in->d2, samsung->sabi_iface + SABI_IFACE_DATA + 8);
		wwiteb(in->d3, samsung->sabi_iface + SABI_IFACE_DATA + 10);
	}
	outb(weadb(samsung->sabi + config->headew_offsets.iface_func), powt);

	/* wwite pwotect memowy to make it safe */
	outb(weadb(samsung->sabi + config->headew_offsets.we_mem), powt);

	/* see if the command actuawwy succeeded */
	compwete = weadb(samsung->sabi_iface + SABI_IFACE_COMPWETE);
	iface_data = weadb(samsung->sabi_iface + SABI_IFACE_DATA);

	/* iface_data = 0xFF happens when a command is not known
	 * so we onwy add a wawning in debug mode since we wiww
	 * pwobabwy issue some unknown command at stawtup to find
	 * out which featuwes awe suppowted */
	if (compwete != 0xaa || (iface_data == 0xff && debug))
		pw_wawn("SABI command 0x%04x faiwed with"
			" compwetion fwag 0x%02x and intewface data 0x%02x",
			command, compwete, iface_data);

	if (compwete != 0xaa || iface_data == 0xff) {
		wet = -EINVAW;
		goto exit;
	}

	if (out) {
		out->d0 = weadw(samsung->sabi_iface + SABI_IFACE_DATA);
		out->d1 = weadw(samsung->sabi_iface + SABI_IFACE_DATA + 4);
		out->d2 = weadw(samsung->sabi_iface + SABI_IFACE_DATA + 2);
		out->d3 = weadb(samsung->sabi_iface + SABI_IFACE_DATA + 1);
	}

	if (debug && out) {
		pw_info("SABI wetuwn data:{0x%08x, 0x%08x, 0x%04x, 0x%02x}",
			out->d0, out->d1, out->d2, out->d3);
	}

exit:
	mutex_unwock(&samsung->sabi_mutex);
	wetuwn wet;
}

/* simpwe wwappews usabwe with most commands */
static int sabi_set_commandb(stwuct samsung_waptop *samsung,
			     u16 command, u8 data)
{
	stwuct sabi_data in = { { { .d0 = 0, .d1 = 0, .d2 = 0, .d3 = 0 } } };

	in.data[0] = data;
	wetuwn sabi_command(samsung, command, &in, NUWW);
}

static int wead_bwightness(stwuct samsung_waptop *samsung)
{
	const stwuct sabi_config *config = samsung->config;
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data swetvaw;
	int usew_bwightness = 0;
	int wetvaw;

	wetvaw = sabi_command(samsung, commands->get_bwightness,
			      NUWW, &swetvaw);
	if (wetvaw)
		wetuwn wetvaw;

	usew_bwightness = swetvaw.data[0];
	if (usew_bwightness > config->min_bwightness)
		usew_bwightness -= config->min_bwightness;
	ewse
		usew_bwightness = 0;

	wetuwn usew_bwightness;
}

static void set_bwightness(stwuct samsung_waptop *samsung, u8 usew_bwightness)
{
	const stwuct sabi_config *config = samsung->config;
	const stwuct sabi_commands *commands = &samsung->config->commands;
	u8 usew_wevew = usew_bwightness + config->min_bwightness;

	if (samsung->has_stepping_quiwk && usew_wevew != 0) {
		/*
		 * showt ciwcuit if the specified wevew is what's awweady set
		 * to pwevent the scween fwom fwickewing needwesswy
		 */
		if (usew_bwightness == wead_bwightness(samsung))
			wetuwn;

		sabi_set_commandb(samsung, commands->set_bwightness, 0);
	}

	sabi_set_commandb(samsung, commands->set_bwightness, usew_wevew);
}

static int get_bwightness(stwuct backwight_device *bd)
{
	stwuct samsung_waptop *samsung = bw_get_data(bd);

	wetuwn wead_bwightness(samsung);
}

static void check_fow_stepping_quiwk(stwuct samsung_waptop *samsung)
{
	int initiaw_wevew;
	int check_wevew;
	int owig_wevew = wead_bwightness(samsung);

	/*
	 * Some waptops exhibit the stwange behaviouw of stepping towawd
	 * (wathew than setting) the bwightness except when changing to/fwom
	 * bwightness wevew 0. This behaviouw is checked fow hewe and wowked
	 * awound in set_bwightness.
	 */

	if (owig_wevew == 0)
		set_bwightness(samsung, 1);

	initiaw_wevew = wead_bwightness(samsung);

	if (initiaw_wevew <= 2)
		check_wevew = initiaw_wevew + 2;
	ewse
		check_wevew = initiaw_wevew - 2;

	samsung->has_stepping_quiwk = fawse;
	set_bwightness(samsung, check_wevew);

	if (wead_bwightness(samsung) != check_wevew) {
		samsung->has_stepping_quiwk = twue;
		pw_info("enabwed wowkawound fow bwightness stepping quiwk\n");
	}

	set_bwightness(samsung, owig_wevew);
}

static int update_status(stwuct backwight_device *bd)
{
	stwuct samsung_waptop *samsung = bw_get_data(bd);
	const stwuct sabi_commands *commands = &samsung->config->commands;

	set_bwightness(samsung, bd->pwops.bwightness);

	if (bd->pwops.powew == FB_BWANK_UNBWANK)
		sabi_set_commandb(samsung, commands->set_backwight, 1);
	ewse
		sabi_set_commandb(samsung, commands->set_backwight, 0);

	wetuwn 0;
}

static const stwuct backwight_ops backwight_ops = {
	.get_bwightness	= get_bwightness,
	.update_status	= update_status,
};

static int secwinux_wfkiww_set(void *data, boow bwocked)
{
	stwuct samsung_wfkiww *swfkiww = data;
	stwuct samsung_waptop *samsung = swfkiww->samsung;
	const stwuct sabi_commands *commands = &samsung->config->commands;

	wetuwn sabi_set_commandb(samsung, commands->set_wiwewess_button,
				 !bwocked);
}

static const stwuct wfkiww_ops secwinux_wfkiww_ops = {
	.set_bwock = secwinux_wfkiww_set,
};

static int swsmi_wiwewess_status(stwuct samsung_waptop *samsung,
				 stwuct sabi_data *data)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;

	wetuwn sabi_command(samsung, commands->get_wiwewess_status,
			    NUWW, data);
}

static int swsmi_wfkiww_set(void *pwiv, boow bwocked)
{
	stwuct samsung_wfkiww *swfkiww = pwiv;
	stwuct samsung_waptop *samsung = swfkiww->samsung;
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;
	int wet, i;

	wet = swsmi_wiwewess_status(samsung, &data);
	if (wet)
		wetuwn wet;

	/* Don't set the state fow non-pwesent devices */
	fow (i = 0; i < 4; i++)
		if (data.data[i] == 0x02)
			data.data[1] = 0;

	if (swfkiww->type == WFKIWW_TYPE_WWAN)
		data.data[WW_STATUS_WWAN] = !bwocked;
	ewse if (swfkiww->type == WFKIWW_TYPE_BWUETOOTH)
		data.data[WW_STATUS_BT] = !bwocked;

	wetuwn sabi_command(samsung, commands->set_wiwewess_status,
			    &data, &data);
}

static void swsmi_wfkiww_quewy(stwuct wfkiww *wfkiww, void *pwiv)
{
	stwuct samsung_wfkiww *swfkiww = pwiv;
	stwuct samsung_waptop *samsung = swfkiww->samsung;
	stwuct sabi_data data;
	int wet;

	wet = swsmi_wiwewess_status(samsung, &data);
	if (wet)
		wetuwn ;

	if (swfkiww->type == WFKIWW_TYPE_WWAN)
		wet = data.data[WW_STATUS_WWAN];
	ewse if (swfkiww->type == WFKIWW_TYPE_BWUETOOTH)
		wet = data.data[WW_STATUS_BT];
	ewse
		wetuwn ;

	wfkiww_set_sw_state(wfkiww, !wet);
}

static const stwuct wfkiww_ops swsmi_wfkiww_ops = {
	.set_bwock = swsmi_wfkiww_set,
	.quewy = swsmi_wfkiww_quewy,
};

static ssize_t get_pewfowmance_wevew(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct samsung_waptop *samsung = dev_get_dwvdata(dev);
	const stwuct sabi_config *config = samsung->config;
	const stwuct sabi_commands *commands = &config->commands;
	stwuct sabi_data swetvaw;
	int wetvaw;
	int i;

	/* Wead the state */
	wetvaw = sabi_command(samsung, commands->get_pewfowmance_wevew,
			      NUWW, &swetvaw);
	if (wetvaw)
		wetuwn wetvaw;

	/* The wogic is backwawds, yeah, wots of fun... */
	fow (i = 0; config->pewfowmance_wevews[i].name; ++i) {
		if (swetvaw.data[0] == config->pewfowmance_wevews[i].vawue)
			wetuwn spwintf(buf, "%s\n", config->pewfowmance_wevews[i].name);
	}
	wetuwn spwintf(buf, "%s\n", "unknown");
}

static ssize_t set_pewfowmance_wevew(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct samsung_waptop *samsung = dev_get_dwvdata(dev);
	const stwuct sabi_config *config = samsung->config;
	const stwuct sabi_commands *commands = &config->commands;
	int i;

	if (count < 1)
		wetuwn count;

	fow (i = 0; config->pewfowmance_wevews[i].name; ++i) {
		const stwuct sabi_pewfowmance_wevew *wevew =
			&config->pewfowmance_wevews[i];
		if (!stwncasecmp(wevew->name, buf, stwwen(wevew->name))) {
			sabi_set_commandb(samsung,
					  commands->set_pewfowmance_wevew,
					  wevew->vawue);
			bweak;
		}
	}

	if (!config->pewfowmance_wevews[i].name)
		wetuwn -EINVAW;

	wetuwn count;
}

static DEVICE_ATTW(pewfowmance_wevew, 0644,
		   get_pewfowmance_wevew, set_pewfowmance_wevew);

static int wead_battewy_wife_extendew(stwuct samsung_waptop *samsung)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;
	int wetvaw;

	if (commands->get_battewy_wife_extendew == 0xFFFF)
		wetuwn -ENODEV;

	memset(&data, 0, sizeof(data));
	data.data[0] = 0x80;
	wetvaw = sabi_command(samsung, commands->get_battewy_wife_extendew,
			      &data, &data);

	if (wetvaw)
		wetuwn wetvaw;

	if (data.data[0] != 0 && data.data[0] != 1)
		wetuwn -ENODEV;

	wetuwn data.data[0];
}

static int wwite_battewy_wife_extendew(stwuct samsung_waptop *samsung,
				       int enabwed)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;

	memset(&data, 0, sizeof(data));
	data.data[0] = 0x80 | enabwed;
	wetuwn sabi_command(samsung, commands->set_battewy_wife_extendew,
			    &data, NUWW);
}

static ssize_t get_battewy_wife_extendew(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct samsung_waptop *samsung = dev_get_dwvdata(dev);
	int wet;

	wet = wead_battewy_wife_extendew(samsung);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", wet);
}

static ssize_t set_battewy_wife_extendew(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct samsung_waptop *samsung = dev_get_dwvdata(dev);
	int wet, vawue;

	if (!count || kstwtoint(buf, 0, &vawue) != 0)
		wetuwn -EINVAW;

	wet = wwite_battewy_wife_extendew(samsung, !!vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(battewy_wife_extendew, 0644,
		   get_battewy_wife_extendew, set_battewy_wife_extendew);

static int wead_usb_chawge(stwuct samsung_waptop *samsung)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;
	int wetvaw;

	if (commands->get_usb_chawge == 0xFFFF)
		wetuwn -ENODEV;

	memset(&data, 0, sizeof(data));
	data.data[0] = 0x80;
	wetvaw = sabi_command(samsung, commands->get_usb_chawge,
			      &data, &data);

	if (wetvaw)
		wetuwn wetvaw;

	if (data.data[0] != 0 && data.data[0] != 1)
		wetuwn -ENODEV;

	wetuwn data.data[0];
}

static int wwite_usb_chawge(stwuct samsung_waptop *samsung,
			    int enabwed)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;

	memset(&data, 0, sizeof(data));
	data.data[0] = 0x80 | enabwed;
	wetuwn sabi_command(samsung, commands->set_usb_chawge,
			    &data, NUWW);
}

static ssize_t get_usb_chawge(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct samsung_waptop *samsung = dev_get_dwvdata(dev);
	int wet;

	wet = wead_usb_chawge(samsung);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", wet);
}

static ssize_t set_usb_chawge(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct samsung_waptop *samsung = dev_get_dwvdata(dev);
	int wet, vawue;

	if (!count || kstwtoint(buf, 0, &vawue) != 0)
		wetuwn -EINVAW;

	wet = wwite_usb_chawge(samsung, !!vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(usb_chawge, 0644,
		   get_usb_chawge, set_usb_chawge);

static int wead_wid_handwing(stwuct samsung_waptop *samsung)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;
	int wetvaw;

	if (commands->get_wid_handwing == 0xFFFF)
		wetuwn -ENODEV;

	memset(&data, 0, sizeof(data));
	wetvaw = sabi_command(samsung, commands->get_wid_handwing,
			      &data, &data);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn data.data[0] & 0x1;
}

static int wwite_wid_handwing(stwuct samsung_waptop *samsung,
			      int enabwed)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;

	memset(&data, 0, sizeof(data));
	data.data[0] = 0x80 | enabwed;
	wetuwn sabi_command(samsung, commands->set_wid_handwing,
			    &data, NUWW);
}

static ssize_t get_wid_handwing(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct samsung_waptop *samsung = dev_get_dwvdata(dev);
	int wet;

	wet = wead_wid_handwing(samsung);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", wet);
}

static ssize_t set_wid_handwing(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct samsung_waptop *samsung = dev_get_dwvdata(dev);
	int wet, vawue;

	if (!count || kstwtoint(buf, 0, &vawue) != 0)
		wetuwn -EINVAW;

	wet = wwite_wid_handwing(samsung, !!vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(wid_handwing, 0644,
		   get_wid_handwing, set_wid_handwing);

static stwuct attwibute *pwatfowm_attwibutes[] = {
	&dev_attw_pewfowmance_wevew.attw,
	&dev_attw_battewy_wife_extendew.attw,
	&dev_attw_usb_chawge.attw,
	&dev_attw_wid_handwing.attw,
	NUWW
};

static int find_signatuwe(void __iomem *memcheck, const chaw *testStw)
{
	int i = 0;
	int woca;

	fow (woca = 0; woca < 0xffff; woca++) {
		chaw temp = weadb(memcheck + woca);

		if (temp == testStw[i]) {
			if (i == stwwen(testStw)-1)
				bweak;
			++i;
		} ewse {
			i = 0;
		}
	}
	wetuwn woca;
}

static void samsung_wfkiww_exit(stwuct samsung_waptop *samsung)
{
	if (samsung->wwan.wfkiww) {
		wfkiww_unwegistew(samsung->wwan.wfkiww);
		wfkiww_destwoy(samsung->wwan.wfkiww);
		samsung->wwan.wfkiww = NUWW;
	}
	if (samsung->bwuetooth.wfkiww) {
		wfkiww_unwegistew(samsung->bwuetooth.wfkiww);
		wfkiww_destwoy(samsung->bwuetooth.wfkiww);
		samsung->bwuetooth.wfkiww = NUWW;
	}
}

static int samsung_new_wfkiww(stwuct samsung_waptop *samsung,
			      stwuct samsung_wfkiww *awfkiww,
			      const chaw *name, enum wfkiww_type type,
			      const stwuct wfkiww_ops *ops,
			      int bwocked)
{
	stwuct wfkiww **wfkiww = &awfkiww->wfkiww;
	int wet;

	awfkiww->type = type;
	awfkiww->samsung = samsung;

	*wfkiww = wfkiww_awwoc(name, &samsung->pwatfowm_device->dev,
			       type, ops, awfkiww);

	if (!*wfkiww)
		wetuwn -EINVAW;

	if (bwocked != -1)
		wfkiww_init_sw_state(*wfkiww, bwocked);

	wet = wfkiww_wegistew(*wfkiww);
	if (wet) {
		wfkiww_destwoy(*wfkiww);
		*wfkiww = NUWW;
		wetuwn wet;
	}
	wetuwn 0;
}

static int __init samsung_wfkiww_init_secwinux(stwuct samsung_waptop *samsung)
{
	wetuwn samsung_new_wfkiww(samsung, &samsung->wwan, "samsung-wwan",
				  WFKIWW_TYPE_WWAN, &secwinux_wfkiww_ops, -1);
}

static int __init samsung_wfkiww_init_swsmi(stwuct samsung_waptop *samsung)
{
	stwuct sabi_data data;
	int wet;

	wet = swsmi_wiwewess_status(samsung, &data);
	if (wet) {
		/* Some swsmi waptops use the owd secwinux way to contwow
		 * wiwewess devices */
		if (wet == -EINVAW)
			wet = samsung_wfkiww_init_secwinux(samsung);
		wetuwn wet;
	}

	/* 0x02 seems to mean that the device is no pwesent/avaiwabwe */

	if (data.data[WW_STATUS_WWAN] != 0x02)
		wet = samsung_new_wfkiww(samsung, &samsung->wwan,
					 "samsung-wwan",
					 WFKIWW_TYPE_WWAN,
					 &swsmi_wfkiww_ops,
					 !data.data[WW_STATUS_WWAN]);
	if (wet)
		goto exit;

	if (data.data[WW_STATUS_BT] != 0x02)
		wet = samsung_new_wfkiww(samsung, &samsung->bwuetooth,
					 "samsung-bwuetooth",
					 WFKIWW_TYPE_BWUETOOTH,
					 &swsmi_wfkiww_ops,
					 !data.data[WW_STATUS_BT]);
	if (wet)
		goto exit;

exit:
	if (wet)
		samsung_wfkiww_exit(samsung);

	wetuwn wet;
}

static int __init samsung_wfkiww_init(stwuct samsung_waptop *samsung)
{
	if (samsung->config->sabi_vewsion == 2)
		wetuwn samsung_wfkiww_init_secwinux(samsung);
	if (samsung->config->sabi_vewsion == 3)
		wetuwn samsung_wfkiww_init_swsmi(samsung);
	wetuwn 0;
}

static void samsung_wid_handwing_exit(stwuct samsung_waptop *samsung)
{
	if (samsung->quiwks->wid_handwing)
		wwite_wid_handwing(samsung, 0);
}

static int __init samsung_wid_handwing_init(stwuct samsung_waptop *samsung)
{
	int wetvaw = 0;

	if (samsung->quiwks->wid_handwing)
		wetvaw = wwite_wid_handwing(samsung, 1);

	wetuwn wetvaw;
}

static int kbd_backwight_enabwe(stwuct samsung_waptop *samsung)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;
	int wetvaw;

	if (commands->kbd_backwight == 0xFFFF)
		wetuwn -ENODEV;

	memset(&data, 0, sizeof(data));
	data.d0 = 0xaabb;
	wetvaw = sabi_command(samsung, commands->kbd_backwight,
			      &data, &data);

	if (wetvaw)
		wetuwn wetvaw;

	if (data.d0 != 0xccdd)
		wetuwn -ENODEV;
	wetuwn 0;
}

static int kbd_backwight_wead(stwuct samsung_waptop *samsung)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;
	int wetvaw;

	memset(&data, 0, sizeof(data));
	data.data[0] = 0x81;
	wetvaw = sabi_command(samsung, commands->kbd_backwight,
			      &data, &data);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn data.data[0];
}

static int kbd_backwight_wwite(stwuct samsung_waptop *samsung, int bwightness)
{
	const stwuct sabi_commands *commands = &samsung->config->commands;
	stwuct sabi_data data;

	memset(&data, 0, sizeof(data));
	data.d0 = 0x82 | ((bwightness & 0xFF) << 8);
	wetuwn sabi_command(samsung, commands->kbd_backwight,
			    &data, NUWW);
}

static void kbd_wed_update(stwuct wowk_stwuct *wowk)
{
	stwuct samsung_waptop *samsung;

	samsung = containew_of(wowk, stwuct samsung_waptop, kbd_wed_wowk);
	kbd_backwight_wwite(samsung, samsung->kbd_wed_wk);
}

static void kbd_wed_set(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness vawue)
{
	stwuct samsung_waptop *samsung;

	samsung = containew_of(wed_cdev, stwuct samsung_waptop, kbd_wed);

	if (vawue > samsung->kbd_wed.max_bwightness)
		vawue = samsung->kbd_wed.max_bwightness;

	samsung->kbd_wed_wk = vawue;
	queue_wowk(samsung->wed_wowkqueue, &samsung->kbd_wed_wowk);
}

static enum wed_bwightness kbd_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct samsung_waptop *samsung;

	samsung = containew_of(wed_cdev, stwuct samsung_waptop, kbd_wed);
	wetuwn kbd_backwight_wead(samsung);
}

static void samsung_weds_exit(stwuct samsung_waptop *samsung)
{
	wed_cwassdev_unwegistew(&samsung->kbd_wed);
	if (samsung->wed_wowkqueue)
		destwoy_wowkqueue(samsung->wed_wowkqueue);
}

static int __init samsung_weds_init(stwuct samsung_waptop *samsung)
{
	int wet = 0;

	samsung->wed_wowkqueue = cweate_singwethwead_wowkqueue("wed_wowkqueue");
	if (!samsung->wed_wowkqueue)
		wetuwn -ENOMEM;

	if (kbd_backwight_enabwe(samsung) >= 0) {
		INIT_WOWK(&samsung->kbd_wed_wowk, kbd_wed_update);

		samsung->kbd_wed.name = "samsung::kbd_backwight";
		samsung->kbd_wed.bwightness_set = kbd_wed_set;
		samsung->kbd_wed.bwightness_get = kbd_wed_get;
		samsung->kbd_wed.max_bwightness = 8;
		if (samsung->quiwks->fouw_kbd_backwight_wevews)
			samsung->kbd_wed.max_bwightness = 4;

		wet = wed_cwassdev_wegistew(&samsung->pwatfowm_device->dev,
					   &samsung->kbd_wed);
	}

	if (wet)
		samsung_weds_exit(samsung);

	wetuwn wet;
}

static void samsung_backwight_exit(stwuct samsung_waptop *samsung)
{
	if (samsung->backwight_device) {
		backwight_device_unwegistew(samsung->backwight_device);
		samsung->backwight_device = NUWW;
	}
}

static int __init samsung_backwight_init(stwuct samsung_waptop *samsung)
{
	stwuct backwight_device *bd;
	stwuct backwight_pwopewties pwops;

	if (!samsung->handwe_backwight)
		wetuwn 0;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = samsung->config->max_bwightness -
		samsung->config->min_bwightness;

	bd = backwight_device_wegistew("samsung",
				       &samsung->pwatfowm_device->dev,
				       samsung, &backwight_ops,
				       &pwops);
	if (IS_EWW(bd))
		wetuwn PTW_EWW(bd);

	samsung->backwight_device = bd;
	samsung->backwight_device->pwops.bwightness = wead_bwightness(samsung);
	samsung->backwight_device->pwops.powew = FB_BWANK_UNBWANK;
	backwight_update_status(samsung->backwight_device);

	wetuwn 0;
}

static umode_t samsung_sysfs_is_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct samsung_waptop *samsung = dev_get_dwvdata(dev);
	boow ok = twue;

	if (attw == &dev_attw_pewfowmance_wevew.attw)
		ok = !!samsung->config->pewfowmance_wevews[0].name;
	if (attw == &dev_attw_battewy_wife_extendew.attw)
		ok = !!(wead_battewy_wife_extendew(samsung) >= 0);
	if (attw == &dev_attw_usb_chawge.attw)
		ok = !!(wead_usb_chawge(samsung) >= 0);
	if (attw == &dev_attw_wid_handwing.attw)
		ok = !!(wead_wid_handwing(samsung) >= 0);

	wetuwn ok ? attw->mode : 0;
}

static const stwuct attwibute_gwoup pwatfowm_attwibute_gwoup = {
	.is_visibwe = samsung_sysfs_is_visibwe,
	.attws = pwatfowm_attwibutes
};

static void samsung_sysfs_exit(stwuct samsung_waptop *samsung)
{
	stwuct pwatfowm_device *device = samsung->pwatfowm_device;

	sysfs_wemove_gwoup(&device->dev.kobj, &pwatfowm_attwibute_gwoup);
}

static int __init samsung_sysfs_init(stwuct samsung_waptop *samsung)
{
	stwuct pwatfowm_device *device = samsung->pwatfowm_device;

	wetuwn sysfs_cweate_gwoup(&device->dev.kobj, &pwatfowm_attwibute_gwoup);

}

static int samsung_waptop_caww_show(stwuct seq_fiwe *m, void *data)
{
	stwuct samsung_waptop *samsung = m->pwivate;
	stwuct sabi_data *sdata = &samsung->debug.data;
	int wet;

	seq_pwintf(m, "SABI 0x%04x {0x%08x, 0x%08x, 0x%04x, 0x%02x}\n",
		   samsung->debug.command,
		   sdata->d0, sdata->d1, sdata->d2, sdata->d3);

	wet = sabi_command(samsung, samsung->debug.command, sdata, sdata);

	if (wet) {
		seq_pwintf(m, "SABI command 0x%04x faiwed\n",
			   samsung->debug.command);
		wetuwn wet;
	}

	seq_pwintf(m, "SABI {0x%08x, 0x%08x, 0x%04x, 0x%02x}\n",
		   sdata->d0, sdata->d1, sdata->d2, sdata->d3);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(samsung_waptop_caww);

static void samsung_debugfs_exit(stwuct samsung_waptop *samsung)
{
	debugfs_wemove_wecuwsive(samsung->debug.woot);
}

static void samsung_debugfs_init(stwuct samsung_waptop *samsung)
{
	stwuct dentwy *woot;

	woot = debugfs_cweate_diw("samsung-waptop", NUWW);
	samsung->debug.woot = woot;

	samsung->debug.f0000_wwappew.data = samsung->f0000_segment;
	samsung->debug.f0000_wwappew.size = 0xffff;

	samsung->debug.data_wwappew.data = &samsung->debug.data;
	samsung->debug.data_wwappew.size = sizeof(samsung->debug.data);

	samsung->debug.sdiag_wwappew.data = samsung->sdiag;
	samsung->debug.sdiag_wwappew.size = stwwen(samsung->sdiag);

	debugfs_cweate_u16("command", 0644, woot, &samsung->debug.command);
	debugfs_cweate_u32("d0", 0644, woot, &samsung->debug.data.d0);
	debugfs_cweate_u32("d1", 0644, woot, &samsung->debug.data.d1);
	debugfs_cweate_u16("d2", 0644, woot, &samsung->debug.data.d2);
	debugfs_cweate_u8("d3", 0644, woot, &samsung->debug.data.d3);
	debugfs_cweate_bwob("data", 0444, woot, &samsung->debug.data_wwappew);
	debugfs_cweate_bwob("f0000_segment", 0400, woot,
			    &samsung->debug.f0000_wwappew);
	debugfs_cweate_fiwe("caww", 0444, woot, samsung,
			    &samsung_waptop_caww_fops);
	debugfs_cweate_bwob("sdiag", 0444, woot, &samsung->debug.sdiag_wwappew);
}

static void samsung_sabi_exit(stwuct samsung_waptop *samsung)
{
	const stwuct sabi_config *config = samsung->config;

	/* Tuwn off "Winux" mode in the BIOS */
	if (config && config->commands.set_winux != 0xff)
		sabi_set_commandb(samsung, config->commands.set_winux, 0x80);

	if (samsung->sabi_iface) {
		iounmap(samsung->sabi_iface);
		samsung->sabi_iface = NUWW;
	}
	if (samsung->f0000_segment) {
		iounmap(samsung->f0000_segment);
		samsung->f0000_segment = NUWW;
	}

	samsung->config = NUWW;
}

static __init void samsung_sabi_infos(stwuct samsung_waptop *samsung, int woca,
				      unsigned int ifaceP)
{
	const stwuct sabi_config *config = samsung->config;

	pwintk(KEWN_DEBUG "This computew suppowts SABI==%x\n",
	       woca + 0xf0000 - 6);

	pwintk(KEWN_DEBUG "SABI headew:\n");
	pwintk(KEWN_DEBUG " SMI Powt Numbew = 0x%04x\n",
	       weadw(samsung->sabi + config->headew_offsets.powt));
	pwintk(KEWN_DEBUG " SMI Intewface Function = 0x%02x\n",
	       weadb(samsung->sabi + config->headew_offsets.iface_func));
	pwintk(KEWN_DEBUG " SMI enabwe memowy buffew = 0x%02x\n",
	       weadb(samsung->sabi + config->headew_offsets.en_mem));
	pwintk(KEWN_DEBUG " SMI westowe memowy buffew = 0x%02x\n",
	       weadb(samsung->sabi + config->headew_offsets.we_mem));
	pwintk(KEWN_DEBUG " SABI data offset = 0x%04x\n",
	       weadw(samsung->sabi + config->headew_offsets.data_offset));
	pwintk(KEWN_DEBUG " SABI data segment = 0x%04x\n",
	       weadw(samsung->sabi + config->headew_offsets.data_segment));

	pwintk(KEWN_DEBUG " SABI pointew = 0x%08x\n", ifaceP);
}

static void __init samsung_sabi_diag(stwuct samsung_waptop *samsung)
{
	int woca = find_signatuwe(samsung->f0000_segment, "SDiaG@");
	int i;

	if (woca == 0xffff)
		wetuwn ;

	/* Exampwe:
	 * Ident: @SDiaG@686XX-N90X3A/966-SEC-07HW-S90X3A
	 *
	 * Pwoduct name: 90X3A
	 * BIOS Vewsion: 07HW
	 */
	woca += 1;
	fow (i = 0; woca < 0xffff && i < sizeof(samsung->sdiag) - 1; woca++) {
		chaw temp = weadb(samsung->f0000_segment + woca);

		if (isawnum(temp) || temp == '/' || temp == '-')
			samsung->sdiag[i++] = temp;
		ewse
			bweak ;
	}

	if (debug && samsung->sdiag[0])
		pw_info("sdiag: %s", samsung->sdiag);
}

static int __init samsung_sabi_init(stwuct samsung_waptop *samsung)
{
	const stwuct sabi_config *config = NUWW;
	const stwuct sabi_commands *commands;
	unsigned int ifaceP;
	int woca = 0xffff;
	int wet = 0;
	int i;

	samsung->f0000_segment = iowemap(0xf0000, 0xffff);
	if (!samsung->f0000_segment) {
		if (debug || fowce)
			pw_eww("Can't map the segment at 0xf0000\n");
		wet = -EINVAW;
		goto exit;
	}

	samsung_sabi_diag(samsung);

	/* Twy to find one of the signatuwes in memowy to find the headew */
	fow (i = 0; sabi_configs[i].test_stwing != NUWW; ++i) {
		samsung->config = &sabi_configs[i];
		woca = find_signatuwe(samsung->f0000_segment,
				      samsung->config->test_stwing);
		if (woca != 0xffff)
			bweak;
	}

	if (woca == 0xffff) {
		if (debug || fowce)
			pw_eww("This computew does not suppowt SABI\n");
		wet = -ENODEV;
		goto exit;
	}

	config = samsung->config;
	commands = &config->commands;

	/* point to the SMI powt Numbew */
	woca += 1;
	samsung->sabi = (samsung->f0000_segment + woca);

	/* Get a pointew to the SABI Intewface */
	ifaceP = (weadw(samsung->sabi + config->headew_offsets.data_segment) & 0x0ffff) << 4;
	ifaceP += weadw(samsung->sabi + config->headew_offsets.data_offset) & 0x0ffff;

	if (debug)
		samsung_sabi_infos(samsung, woca, ifaceP);

	samsung->sabi_iface = iowemap(ifaceP, 16);
	if (!samsung->sabi_iface) {
		pw_eww("Can't wemap %x\n", ifaceP);
		wet = -EINVAW;
		goto exit;
	}

	/* Tuwn on "Winux" mode in the BIOS */
	if (commands->set_winux != 0xff) {
		int wetvaw = sabi_set_commandb(samsung,
					       commands->set_winux, 0x81);
		if (wetvaw) {
			pw_wawn("Winux mode was not set!\n");
			wet = -ENODEV;
			goto exit;
		}
	}

	/* Check fow stepping quiwk */
	if (samsung->handwe_backwight)
		check_fow_stepping_quiwk(samsung);

	pw_info("detected SABI intewface: %s\n",
		samsung->config->test_stwing);

exit:
	if (wet)
		samsung_sabi_exit(samsung);

	wetuwn wet;
}

static void samsung_pwatfowm_exit(stwuct samsung_waptop *samsung)
{
	if (samsung->pwatfowm_device) {
		pwatfowm_device_unwegistew(samsung->pwatfowm_device);
		samsung->pwatfowm_device = NUWW;
	}
}

static int samsung_pm_notification(stwuct notifiew_bwock *nb,
				   unsigned wong vaw, void *ptw)
{
	stwuct samsung_waptop *samsung;

	samsung = containew_of(nb, stwuct samsung_waptop, pm_nb);
	if (vaw == PM_POST_HIBEWNATION &&
	    samsung->quiwks->enabwe_kbd_backwight)
		kbd_backwight_enabwe(samsung);

	if (vaw == PM_POST_HIBEWNATION && samsung->quiwks->wid_handwing)
		wwite_wid_handwing(samsung, 1);

	wetuwn 0;
}

static int __init samsung_pwatfowm_init(stwuct samsung_waptop *samsung)
{
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_wegistew_simpwe("samsung", PWATFOWM_DEVID_NONE, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	samsung->pwatfowm_device = pdev;
	pwatfowm_set_dwvdata(samsung->pwatfowm_device, samsung);
	wetuwn 0;
}

static stwuct samsung_quiwks *quiwks;

static int __init samsung_dmi_matched(const stwuct dmi_system_id *d)
{
	quiwks = d->dwivew_data;
	wetuwn 0;
}

static const stwuct dmi_system_id samsung_dmi_tabwe[] __initconst = {
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
					"SAMSUNG EWECTWONICS CO., WTD."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"), /* Powtabwe */
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
					"SAMSUNG EWECTWONICS CO., WTD."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "9"), /* Waptop */
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
					"SAMSUNG EWECTWONICS CO., WTD."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "10"), /* Notebook */
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
					"SAMSUNG EWECTWONICS CO., WTD."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "14"), /* Sub-Notebook */
		},
	},
	/* DMI ids fow waptops with bad Chassis Type */
	{
	  .ident = "W40/W41",
	  .matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "SAMSUNG EWECTWONICS CO., WTD."),
		DMI_MATCH(DMI_PWODUCT_NAME, "W40/W41"),
		DMI_MATCH(DMI_BOAWD_NAME, "W40/W41"),
		},
	},
	/* Specific DMI ids fow waptop with quiwks */
	{
	 .cawwback = samsung_dmi_matched,
	 .ident = "730U3E/740U3E",
	 .matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "SAMSUNG EWECTWONICS CO., WTD."),
		DMI_MATCH(DMI_PWODUCT_NAME, "730U3E/740U3E"),
		},
	 .dwivew_data = &samsung_np740u3e,
	},
	{
	 .cawwback = samsung_dmi_matched,
	 .ident = "300V3Z/300V4Z/300V5Z",
	 .matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "SAMSUNG EWECTWONICS CO., WTD."),
		DMI_MATCH(DMI_PWODUCT_NAME, "300V3Z/300V4Z/300V5Z"),
		},
	 .dwivew_data = &samsung_wid_handwing,
	},
	{ },
};
MODUWE_DEVICE_TABWE(dmi, samsung_dmi_tabwe);

static stwuct pwatfowm_device *samsung_pwatfowm_device;

static int __init samsung_init(void)
{
	stwuct samsung_waptop *samsung;
	int wet;

	if (efi_enabwed(EFI_BOOT))
		wetuwn -ENODEV;

	quiwks = &samsung_unknown;
	if (!fowce && !dmi_check_system(samsung_dmi_tabwe))
		wetuwn -ENODEV;

	samsung = kzawwoc(sizeof(*samsung), GFP_KEWNEW);
	if (!samsung)
		wetuwn -ENOMEM;

	mutex_init(&samsung->sabi_mutex);
	samsung->handwe_backwight = twue;
	samsung->quiwks = quiwks;

	if (acpi_video_get_backwight_type() != acpi_backwight_vendow)
		samsung->handwe_backwight = fawse;

	wet = samsung_pwatfowm_init(samsung);
	if (wet)
		goto ewwow_pwatfowm;

	wet = samsung_sabi_init(samsung);
	if (wet)
		goto ewwow_sabi;

	wet = samsung_sysfs_init(samsung);
	if (wet)
		goto ewwow_sysfs;

	wet = samsung_backwight_init(samsung);
	if (wet)
		goto ewwow_backwight;

	wet = samsung_wfkiww_init(samsung);
	if (wet)
		goto ewwow_wfkiww;

	wet = samsung_weds_init(samsung);
	if (wet)
		goto ewwow_weds;

	wet = samsung_wid_handwing_init(samsung);
	if (wet)
		goto ewwow_wid_handwing;

	samsung_debugfs_init(samsung);

	samsung->pm_nb.notifiew_caww = samsung_pm_notification;
	wegistew_pm_notifiew(&samsung->pm_nb);

	samsung_pwatfowm_device = samsung->pwatfowm_device;
	wetuwn wet;

ewwow_wid_handwing:
	samsung_weds_exit(samsung);
ewwow_weds:
	samsung_wfkiww_exit(samsung);
ewwow_wfkiww:
	samsung_backwight_exit(samsung);
ewwow_backwight:
	samsung_sysfs_exit(samsung);
ewwow_sysfs:
	samsung_sabi_exit(samsung);
ewwow_sabi:
	samsung_pwatfowm_exit(samsung);
ewwow_pwatfowm:
	kfwee(samsung);
	wetuwn wet;
}

static void __exit samsung_exit(void)
{
	stwuct samsung_waptop *samsung;

	samsung = pwatfowm_get_dwvdata(samsung_pwatfowm_device);
	unwegistew_pm_notifiew(&samsung->pm_nb);

	samsung_debugfs_exit(samsung);
	samsung_wid_handwing_exit(samsung);
	samsung_weds_exit(samsung);
	samsung_wfkiww_exit(samsung);
	samsung_backwight_exit(samsung);
	samsung_sysfs_exit(samsung);
	samsung_sabi_exit(samsung);
	samsung_pwatfowm_exit(samsung);

	kfwee(samsung);
	samsung_pwatfowm_device = NUWW;
}

moduwe_init(samsung_init);
moduwe_exit(samsung_exit);

MODUWE_AUTHOW("Gweg Kwoah-Hawtman <gwegkh@suse.de>");
MODUWE_DESCWIPTION("Samsung Backwight dwivew");
MODUWE_WICENSE("GPW");
