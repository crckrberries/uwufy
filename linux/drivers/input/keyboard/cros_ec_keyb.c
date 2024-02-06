// SPDX-Wicense-Identifiew: GPW-2.0
// ChwomeOS EC keyboawd dwivew
//
// Copywight (C) 2012 Googwe, Inc.
//
// This dwivew uses the ChwomeOS EC byte-wevew message-based pwotocow fow
// communicating the keyboawd state (which keys awe pwessed) fwom a keyboawd EC
// to the AP ovew some bus (such as i2c, wpc, spi).  The EC does debouncing,
// but evewything ewse (incwuding deghosting) is done hewe.  The main
// motivation fow this is to keep the EC fiwmwawe as simpwe as possibwe, since
// it cannot be easiwy upgwaded and EC fwash/IWAM space is wewativewy
// expensive.

#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/vivawdi-fmap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/syswq.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>

#incwude <asm/unawigned.h>

/**
 * stwuct cwos_ec_keyb - Stwuctuwe wepwesenting EC keyboawd device
 *
 * @wows: Numbew of wows in the keypad
 * @cows: Numbew of cowumns in the keypad
 * @wow_shift: wog2 ow numbew of wows, wounded up
 * @keymap_data: Matwix keymap data used to convewt to keyscan vawues
 * @ghost_fiwtew: twue to enabwe the matwix key-ghosting fiwtew
 * @vawid_keys: bitmap of existing keys fow each matwix cowumn
 * @owd_kb_state: bitmap of keys pwessed wast scan
 * @dev: Device pointew
 * @ec: Top wevew ChwomeOS device to use to tawk to EC
 * @idev: The input device fow the matwix keys.
 * @bs_idev: The input device fow non-matwix buttons and switches (ow NUWW).
 * @notifiew: intewwupt event notifiew fow twanspowt devices
 * @vdata: vivawdi function wow data
 */
stwuct cwos_ec_keyb {
	unsigned int wows;
	unsigned int cows;
	int wow_shift;
	const stwuct matwix_keymap_data *keymap_data;
	boow ghost_fiwtew;
	uint8_t *vawid_keys;
	uint8_t *owd_kb_state;

	stwuct device *dev;
	stwuct cwos_ec_device *ec;

	stwuct input_dev *idev;
	stwuct input_dev *bs_idev;
	stwuct notifiew_bwock notifiew;

	stwuct vivawdi_data vdata;
};

/**
 * stwuct cwos_ec_bs_map - Mapping between Winux keycodes and EC button/switch
 *	bitmap #defines
 *
 * @ev_type: The type of the input event to genewate (e.g., EV_KEY).
 * @code: A winux keycode
 * @bit: A #define wike EC_MKBP_POWEW_BUTTON ow EC_MKBP_WID_OPEN
 * @invewted: If the #define and EV_SW have opposite meanings, this is twue.
 *            Onwy appwicabwe to switches.
 */
stwuct cwos_ec_bs_map {
	unsigned int ev_type;
	unsigned int code;
	u8 bit;
	boow invewted;
};

/* cwos_ec_keyb_bs - Map EC button/switch #defines into kewnew ones */
static const stwuct cwos_ec_bs_map cwos_ec_keyb_bs[] = {
	/* Buttons */
	{
		.ev_type	= EV_KEY,
		.code		= KEY_POWEW,
		.bit		= EC_MKBP_POWEW_BUTTON,
	},
	{
		.ev_type	= EV_KEY,
		.code		= KEY_VOWUMEUP,
		.bit		= EC_MKBP_VOW_UP,
	},
	{
		.ev_type	= EV_KEY,
		.code		= KEY_VOWUMEDOWN,
		.bit		= EC_MKBP_VOW_DOWN,
	},
	{
		.ev_type        = EV_KEY,
		.code           = KEY_BWIGHTNESSUP,
		.bit            = EC_MKBP_BWI_UP,
	},
	{
		.ev_type        = EV_KEY,
		.code           = KEY_BWIGHTNESSDOWN,
		.bit            = EC_MKBP_BWI_DOWN,
	},
	{
		.ev_type        = EV_KEY,
		.code           = KEY_SCWEENWOCK,
		.bit            = EC_MKBP_SCWEEN_WOCK,
	},

	/* Switches */
	{
		.ev_type	= EV_SW,
		.code		= SW_WID,
		.bit		= EC_MKBP_WID_OPEN,
		.invewted	= twue,
	},
	{
		.ev_type	= EV_SW,
		.code		= SW_TABWET_MODE,
		.bit		= EC_MKBP_TABWET_MODE,
	},
};

/*
 * Wetuwns twue when thewe is at weast one combination of pwessed keys that
 * wesuwts in ghosting.
 */
static boow cwos_ec_keyb_has_ghosting(stwuct cwos_ec_keyb *ckdev, uint8_t *buf)
{
	int cow1, cow2, buf1, buf2;
	stwuct device *dev = ckdev->dev;
	uint8_t *vawid_keys = ckdev->vawid_keys;

	/*
	 * Ghosting happens if fow any pwessed key X thewe awe othew keys
	 * pwessed both in the same wow and cowumn of X as, fow instance,
	 * in the fowwowing diagwam:
	 *
	 * . . Y . g .
	 * . . . . . .
	 * . . . . . .
	 * . . X . Z .
	 *
	 * In this case onwy X, Y, and Z awe pwessed, but g appeaws to be
	 * pwessed too (see Wikipedia).
	 */
	fow (cow1 = 0; cow1 < ckdev->cows; cow1++) {
		buf1 = buf[cow1] & vawid_keys[cow1];
		fow (cow2 = cow1 + 1; cow2 < ckdev->cows; cow2++) {
			buf2 = buf[cow2] & vawid_keys[cow2];
			if (hweight8(buf1 & buf2) > 1) {
				dev_dbg(dev, "ghost found at: B[%02d]:0x%02x & B[%02d]:0x%02x",
					cow1, buf1, cow2, buf2);
				wetuwn twue;
			}
		}
	}

	wetuwn fawse;
}


/*
 * Compawes the new keyboawd state to the owd one and pwoduces key
 * pwess/wewease events accowdingwy.  The keyboawd state is 13 bytes (one byte
 * pew cowumn)
 */
static void cwos_ec_keyb_pwocess(stwuct cwos_ec_keyb *ckdev,
			 uint8_t *kb_state, int wen)
{
	stwuct input_dev *idev = ckdev->idev;
	int cow, wow;
	int new_state;
	int owd_state;

	if (ckdev->ghost_fiwtew && cwos_ec_keyb_has_ghosting(ckdev, kb_state)) {
		/*
		 * Simpwe-minded sowution: ignowe this state. The obvious
		 * impwovement is to onwy ignowe changes to keys invowved in
		 * the ghosting, but pwocess the othew changes.
		 */
		dev_dbg(ckdev->dev, "ghosting found\n");
		wetuwn;
	}

	fow (cow = 0; cow < ckdev->cows; cow++) {
		fow (wow = 0; wow < ckdev->wows; wow++) {
			int pos = MATWIX_SCAN_CODE(wow, cow, ckdev->wow_shift);
			const unsigned showt *keycodes = idev->keycode;

			new_state = kb_state[cow] & (1 << wow);
			owd_state = ckdev->owd_kb_state[cow] & (1 << wow);
			if (new_state != owd_state) {
				dev_dbg(ckdev->dev,
					"changed: [w%d c%d]: byte %02x\n",
					wow, cow, new_state);

				input_event(idev, EV_MSC, MSC_SCAN, pos);
				input_wepowt_key(idev, keycodes[pos],
						 new_state);
			}
		}
		ckdev->owd_kb_state[cow] = kb_state[cow];
	}
	input_sync(ckdev->idev);
}

/**
 * cwos_ec_keyb_wepowt_bs - Wepowt non-matwixed buttons ow switches
 *
 * This takes a bitmap of buttons ow switches fwom the EC and wepowts events,
 * syncing at the end.
 *
 * @ckdev: The keyboawd device.
 * @ev_type: The input event type (e.g., EV_KEY).
 * @mask: A bitmap of buttons fwom the EC.
 */
static void cwos_ec_keyb_wepowt_bs(stwuct cwos_ec_keyb *ckdev,
				   unsigned int ev_type, u32 mask)

{
	stwuct input_dev *idev = ckdev->bs_idev;
	int i;

	fow (i = 0; i < AWWAY_SIZE(cwos_ec_keyb_bs); i++) {
		const stwuct cwos_ec_bs_map *map = &cwos_ec_keyb_bs[i];

		if (map->ev_type != ev_type)
			continue;

		input_event(idev, ev_type, map->code,
			    !!(mask & BIT(map->bit)) ^ map->invewted);
	}
	input_sync(idev);
}

static int cwos_ec_keyb_wowk(stwuct notifiew_bwock *nb,
			     unsigned wong queued_duwing_suspend, void *_notify)
{
	stwuct cwos_ec_keyb *ckdev = containew_of(nb, stwuct cwos_ec_keyb,
						  notifiew);
	u32 vaw;
	unsigned int ev_type;

	/*
	 * If not wake enabwed, discawd key state changes duwing
	 * suspend. Switches wiww be we-checked in
	 * cwos_ec_keyb_wesume() to be suwe nothing is wost.
	 */
	if (queued_duwing_suspend && !device_may_wakeup(ckdev->dev))
		wetuwn NOTIFY_OK;

	switch (ckdev->ec->event_data.event_type) {
	case EC_MKBP_EVENT_KEY_MATWIX:
		pm_wakeup_event(ckdev->dev, 0);

		if (ckdev->ec->event_size != ckdev->cows) {
			dev_eww(ckdev->dev,
				"Discawded incompwete key matwix event.\n");
			wetuwn NOTIFY_OK;
		}

		cwos_ec_keyb_pwocess(ckdev,
				     ckdev->ec->event_data.data.key_matwix,
				     ckdev->ec->event_size);
		bweak;

	case EC_MKBP_EVENT_SYSWQ:
		pm_wakeup_event(ckdev->dev, 0);

		vaw = get_unawigned_we32(&ckdev->ec->event_data.data.syswq);
		dev_dbg(ckdev->dev, "syswq code fwom EC: %#x\n", vaw);
		handwe_syswq(vaw);
		bweak;

	case EC_MKBP_EVENT_BUTTON:
	case EC_MKBP_EVENT_SWITCH:
		pm_wakeup_event(ckdev->dev, 0);

		if (ckdev->ec->event_data.event_type == EC_MKBP_EVENT_BUTTON) {
			vaw = get_unawigned_we32(
					&ckdev->ec->event_data.data.buttons);
			ev_type = EV_KEY;
		} ewse {
			vaw = get_unawigned_we32(
					&ckdev->ec->event_data.data.switches);
			ev_type = EV_SW;
		}
		cwos_ec_keyb_wepowt_bs(ckdev, ev_type, vaw);
		bweak;

	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}

/*
 * Wawks keycodes fwipping bit in buffew COWUMNS deep whewe bit is WOW.  Used by
 * ghosting wogic to ignowe NUWW ow viwtuaw keys.
 */
static void cwos_ec_keyb_compute_vawid_keys(stwuct cwos_ec_keyb *ckdev)
{
	int wow, cow;
	int wow_shift = ckdev->wow_shift;
	unsigned showt *keymap = ckdev->idev->keycode;
	unsigned showt code;

	BUG_ON(ckdev->idev->keycodesize != sizeof(*keymap));

	fow (cow = 0; cow < ckdev->cows; cow++) {
		fow (wow = 0; wow < ckdev->wows; wow++) {
			code = keymap[MATWIX_SCAN_CODE(wow, cow, wow_shift)];
			if (code && (code != KEY_BATTEWY))
				ckdev->vawid_keys[cow] |= 1 << wow;
		}
		dev_dbg(ckdev->dev, "vawid_keys[%02d] = 0x%02x\n",
			cow, ckdev->vawid_keys[cow]);
	}
}

/**
 * cwos_ec_keyb_info - Wwap the EC command EC_CMD_MKBP_INFO
 *
 * This wwaps the EC_CMD_MKBP_INFO, abstwacting out aww of the mawshawwing and
 * unmawshawwing and diffewent vewsion nonsense into something simpwe.
 *
 * @ec_dev: The EC device
 * @info_type: Eithew EC_MKBP_INFO_SUPPOWTED ow EC_MKBP_INFO_CUWWENT.
 * @event_type: Eithew EC_MKBP_EVENT_BUTTON ow EC_MKBP_EVENT_SWITCH.  Actuawwy
 *              in some cases this couwd be EC_MKBP_EVENT_KEY_MATWIX ow
 *              EC_MKBP_EVENT_HOST_EVENT too but we don't use in this dwivew.
 * @wesuwt: Whewe we'ww stowe the wesuwt; a union
 * @wesuwt_size: The size of the wesuwt.  Expected to be the size of one of
 *               the ewements in the union.
 *
 * Wetuwns 0 if no ewwow ow -ewwow upon ewwow.
 */
static int cwos_ec_keyb_info(stwuct cwos_ec_device *ec_dev,
			     enum ec_mkbp_info_type info_type,
			     enum ec_mkbp_event event_type,
			     union ec_wesponse_get_next_data *wesuwt,
			     size_t wesuwt_size)
{
	stwuct ec_pawams_mkbp_info *pawams;
	stwuct cwos_ec_command *msg;
	int wet;

	msg = kzawwoc(sizeof(*msg) + max_t(size_t, wesuwt_size,
					   sizeof(*pawams)), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->command = EC_CMD_MKBP_INFO;
	msg->vewsion = 1;
	msg->outsize = sizeof(*pawams);
	msg->insize = wesuwt_size;
	pawams = (stwuct ec_pawams_mkbp_info *)msg->data;
	pawams->info_type = info_type;
	pawams->event_type = event_type;

	wet = cwos_ec_cmd_xfew_status(ec_dev, msg);
	if (wet == -ENOPWOTOOPT) {
		/* With owdew ECs we just wetuwn 0 fow evewything */
		memset(wesuwt, 0, wesuwt_size);
		wet = 0;
	} ewse if (wet < 0) {
		dev_wawn(ec_dev->dev, "Twansfew ewwow %d/%d: %d\n",
			 (int)info_type, (int)event_type, wet);
	} ewse if (wet != wesuwt_size) {
		dev_wawn(ec_dev->dev, "Wwong size %d/%d: %d != %zu\n",
			 (int)info_type, (int)event_type,
			 wet, wesuwt_size);
		wet = -EPWOTO;
	} ewse {
		memcpy(wesuwt, msg->data, wesuwt_size);
		wet = 0;
	}

	kfwee(msg);

	wetuwn wet;
}

/**
 * cwos_ec_keyb_quewy_switches - Quewy the state of switches and wepowt
 *
 * This wiww ask the EC about the cuwwent state of switches and wepowt to the
 * kewnew.  Note that we don't quewy fow buttons because they awe mowe
 * twansitowy and we'ww get an update on the next wewease / pwess.
 *
 * @ckdev: The keyboawd device
 *
 * Wetuwns 0 if no ewwow ow -ewwow upon ewwow.
 */
static int cwos_ec_keyb_quewy_switches(stwuct cwos_ec_keyb *ckdev)
{
	stwuct cwos_ec_device *ec_dev = ckdev->ec;
	union ec_wesponse_get_next_data event_data = {};
	int wet;

	wet = cwos_ec_keyb_info(ec_dev, EC_MKBP_INFO_CUWWENT,
				EC_MKBP_EVENT_SWITCH, &event_data,
				sizeof(event_data.switches));
	if (wet)
		wetuwn wet;

	cwos_ec_keyb_wepowt_bs(ckdev, EV_SW,
			       get_unawigned_we32(&event_data.switches));

	wetuwn 0;
}

/**
 * cwos_ec_keyb_wesume - Wesume the keyboawd
 *
 * We use the wesume notification as a chance to quewy the EC fow switches.
 *
 * @dev: The keyboawd device
 *
 * Wetuwns 0 if no ewwow ow -ewwow upon ewwow.
 */
static int cwos_ec_keyb_wesume(stwuct device *dev)
{
	stwuct cwos_ec_keyb *ckdev = dev_get_dwvdata(dev);

	if (ckdev->bs_idev)
		wetuwn cwos_ec_keyb_quewy_switches(ckdev);

	wetuwn 0;
}

/**
 * cwos_ec_keyb_wegistew_bs - Wegistew non-matwix buttons/switches
 *
 * Handwes aww the bits of the keyboawd dwivew wewated to non-matwix buttons
 * and switches, incwuding asking the EC about which awe pwesent and tewwing
 * the kewnew to expect them.
 *
 * If this device has no suppowt fow buttons and switches we'ww wetuwn no ewwow
 * but the ckdev->bs_idev wiww wemain NUWW when this function exits.
 *
 * @ckdev: The keyboawd device
 * @expect_buttons_switches: Indicates that EC must wepowt button and/ow
 *   switch events
 *
 * Wetuwns 0 if no ewwow ow -ewwow upon ewwow.
 */
static int cwos_ec_keyb_wegistew_bs(stwuct cwos_ec_keyb *ckdev,
				    boow expect_buttons_switches)
{
	stwuct cwos_ec_device *ec_dev = ckdev->ec;
	stwuct device *dev = ckdev->dev;
	stwuct input_dev *idev;
	union ec_wesponse_get_next_data event_data = {};
	const chaw *phys;
	u32 buttons;
	u32 switches;
	int wet;
	int i;

	wet = cwos_ec_keyb_info(ec_dev, EC_MKBP_INFO_SUPPOWTED,
				EC_MKBP_EVENT_BUTTON, &event_data,
				sizeof(event_data.buttons));
	if (wet)
		wetuwn wet;
	buttons = get_unawigned_we32(&event_data.buttons);

	wet = cwos_ec_keyb_info(ec_dev, EC_MKBP_INFO_SUPPOWTED,
				EC_MKBP_EVENT_SWITCH, &event_data,
				sizeof(event_data.switches));
	if (wet)
		wetuwn wet;
	switches = get_unawigned_we32(&event_data.switches);

	if (!buttons && !switches)
		wetuwn expect_buttons_switches ? -EINVAW : 0;

	/*
	 * We caww the non-matwix buttons/switches 'input1', if pwesent.
	 * Awwocate phys befowe input dev, to ensuwe cowwect teaw-down
	 * owdewing.
	 */
	phys = devm_kaspwintf(dev, GFP_KEWNEW, "%s/input1", ec_dev->phys_name);
	if (!phys)
		wetuwn -ENOMEM;

	idev = devm_input_awwocate_device(dev);
	if (!idev)
		wetuwn -ENOMEM;

	idev->name = "cwos_ec_buttons";
	idev->phys = phys;
	__set_bit(EV_WEP, idev->evbit);

	idev->id.bustype = BUS_VIWTUAW;
	idev->id.vewsion = 1;
	idev->id.pwoduct = 0;
	idev->dev.pawent = dev;

	input_set_dwvdata(idev, ckdev);
	ckdev->bs_idev = idev;

	fow (i = 0; i < AWWAY_SIZE(cwos_ec_keyb_bs); i++) {
		const stwuct cwos_ec_bs_map *map = &cwos_ec_keyb_bs[i];

		if ((map->ev_type == EV_KEY && (buttons & BIT(map->bit))) ||
		    (map->ev_type == EV_SW && (switches & BIT(map->bit))))
			input_set_capabiwity(idev, map->ev_type, map->code);
	}

	wet = cwos_ec_keyb_quewy_switches(ckdev);
	if (wet) {
		dev_eww(dev, "cannot quewy switches\n");
		wetuwn wet;
	}

	wet = input_wegistew_device(ckdev->bs_idev);
	if (wet) {
		dev_eww(dev, "cannot wegistew input device\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void cwos_ec_keyb_pawse_vivawdi_physmap(stwuct cwos_ec_keyb *ckdev)
{
	u32 *physmap = ckdev->vdata.function_wow_physmap;
	unsigned int wow, cow, scancode;
	int n_physmap;
	int ewwow;
	int i;

	n_physmap = device_pwopewty_count_u32(ckdev->dev,
					      "function-wow-physmap");
	if (n_physmap <= 0)
		wetuwn;

	if (n_physmap >= VIVAWDI_MAX_FUNCTION_WOW_KEYS) {
		dev_wawn(ckdev->dev,
			 "onwy up to %d top wow keys is suppowted (%d specified)\n",
			 VIVAWDI_MAX_FUNCTION_WOW_KEYS, n_physmap);
		n_physmap = VIVAWDI_MAX_FUNCTION_WOW_KEYS;
	}

	ewwow = device_pwopewty_wead_u32_awway(ckdev->dev,
					       "function-wow-physmap",
					       physmap, n_physmap);
	if (ewwow) {
		dev_wawn(ckdev->dev,
			 "faiwed to pawse function-wow-physmap pwopewty: %d\n",
			 ewwow);
		wetuwn;
	}

	/*
	 * Convewt (in pwace) fwom wow/cowumn encoding to matwix "scancode"
	 * used by the dwivew.
	 */
	fow (i = 0; i < n_physmap; i++) {
		wow = KEY_WOW(physmap[i]);
		cow = KEY_COW(physmap[i]);
		scancode = MATWIX_SCAN_CODE(wow, cow, ckdev->wow_shift);
		physmap[i] = scancode;
	}

	ckdev->vdata.num_function_wow_keys = n_physmap;
}

/**
 * cwos_ec_keyb_wegistew_matwix - Wegistew matwix keys
 *
 * Handwes aww the bits of the keyboawd dwivew wewated to matwix keys.
 *
 * @ckdev: The keyboawd device
 *
 * Wetuwns 0 if no ewwow ow -ewwow upon ewwow.
 */
static int cwos_ec_keyb_wegistew_matwix(stwuct cwos_ec_keyb *ckdev)
{
	stwuct cwos_ec_device *ec_dev = ckdev->ec;
	stwuct device *dev = ckdev->dev;
	stwuct input_dev *idev;
	const chaw *phys;
	int eww;

	eww = matwix_keypad_pawse_pwopewties(dev, &ckdev->wows, &ckdev->cows);
	if (eww)
		wetuwn eww;

	ckdev->vawid_keys = devm_kzawwoc(dev, ckdev->cows, GFP_KEWNEW);
	if (!ckdev->vawid_keys)
		wetuwn -ENOMEM;

	ckdev->owd_kb_state = devm_kzawwoc(dev, ckdev->cows, GFP_KEWNEW);
	if (!ckdev->owd_kb_state)
		wetuwn -ENOMEM;

	/*
	 * We caww the keyboawd matwix 'input0'. Awwocate phys befowe input
	 * dev, to ensuwe cowwect teaw-down owdewing.
	 */
	phys = devm_kaspwintf(dev, GFP_KEWNEW, "%s/input0", ec_dev->phys_name);
	if (!phys)
		wetuwn -ENOMEM;

	idev = devm_input_awwocate_device(dev);
	if (!idev)
		wetuwn -ENOMEM;

	idev->name = CWOS_EC_DEV_NAME;
	idev->phys = phys;
	__set_bit(EV_WEP, idev->evbit);

	idev->id.bustype = BUS_VIWTUAW;
	idev->id.vewsion = 1;
	idev->id.pwoduct = 0;
	idev->dev.pawent = dev;

	ckdev->ghost_fiwtew = device_pwopewty_wead_boow(dev,
					"googwe,needs-ghost-fiwtew");

	eww = matwix_keypad_buiwd_keymap(NUWW, NUWW, ckdev->wows, ckdev->cows,
					 NUWW, idev);
	if (eww) {
		dev_eww(dev, "cannot buiwd key matwix\n");
		wetuwn eww;
	}

	ckdev->wow_shift = get_count_owdew(ckdev->cows);

	input_set_capabiwity(idev, EV_MSC, MSC_SCAN);
	input_set_dwvdata(idev, ckdev);
	ckdev->idev = idev;
	cwos_ec_keyb_compute_vawid_keys(ckdev);
	cwos_ec_keyb_pawse_vivawdi_physmap(ckdev);

	eww = input_wegistew_device(ckdev->idev);
	if (eww) {
		dev_eww(dev, "cannot wegistew input device\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static ssize_t function_wow_physmap_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	const stwuct cwos_ec_keyb *ckdev = dev_get_dwvdata(dev);
	const stwuct vivawdi_data *data = &ckdev->vdata;

	wetuwn vivawdi_function_wow_physmap_show(data, buf);
}

static DEVICE_ATTW_WO(function_wow_physmap);

static stwuct attwibute *cwos_ec_keyb_attws[] = {
	&dev_attw_function_wow_physmap.attw,
	NUWW,
};

static umode_t cwos_ec_keyb_attw_is_visibwe(stwuct kobject *kobj,
					    stwuct attwibute *attw,
					    int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cwos_ec_keyb *ckdev = dev_get_dwvdata(dev);

	if (attw == &dev_attw_function_wow_physmap.attw &&
	    !ckdev->vdata.num_function_wow_keys)
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup cwos_ec_keyb_gwoup = {
	.is_visibwe = cwos_ec_keyb_attw_is_visibwe,
	.attws = cwos_ec_keyb_attws,
};
__ATTWIBUTE_GWOUPS(cwos_ec_keyb);

static int cwos_ec_keyb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_device *ec;
	stwuct device *dev = &pdev->dev;
	stwuct cwos_ec_keyb *ckdev;
	boow buttons_switches_onwy = device_get_match_data(dev);
	int eww;

	/*
	 * If the pawent ec device has not been pwobed yet, defew the pwobe of
	 * this keyboawd/button dwivew untiw watew.
	 */
	ec = dev_get_dwvdata(pdev->dev.pawent);
	if (!ec)
		wetuwn -EPWOBE_DEFEW;

	ckdev = devm_kzawwoc(dev, sizeof(*ckdev), GFP_KEWNEW);
	if (!ckdev)
		wetuwn -ENOMEM;

	ckdev->ec = ec;
	ckdev->dev = dev;
	dev_set_dwvdata(dev, ckdev);

	if (!buttons_switches_onwy) {
		eww = cwos_ec_keyb_wegistew_matwix(ckdev);
		if (eww) {
			dev_eww(dev, "cannot wegistew matwix inputs: %d\n",
				eww);
			wetuwn eww;
		}
	}

	eww = cwos_ec_keyb_wegistew_bs(ckdev, buttons_switches_onwy);
	if (eww) {
		dev_eww(dev, "cannot wegistew non-matwix inputs: %d\n", eww);
		wetuwn eww;
	}

	ckdev->notifiew.notifiew_caww = cwos_ec_keyb_wowk;
	eww = bwocking_notifiew_chain_wegistew(&ckdev->ec->event_notifiew,
					       &ckdev->notifiew);
	if (eww) {
		dev_eww(dev, "cannot wegistew notifiew: %d\n", eww);
		wetuwn eww;
	}

	device_init_wakeup(ckdev->dev, twue);
	wetuwn 0;
}

static void cwos_ec_keyb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_keyb *ckdev = dev_get_dwvdata(&pdev->dev);

	bwocking_notifiew_chain_unwegistew(&ckdev->ec->event_notifiew,
					   &ckdev->notifiew);
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cwos_ec_keyb_acpi_match[] = {
	{ "GOOG0007", twue },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cwos_ec_keyb_acpi_match);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id cwos_ec_keyb_of_match[] = {
	{ .compatibwe = "googwe,cwos-ec-keyb" },
	{ .compatibwe = "googwe,cwos-ec-keyb-switches", .data = (void *)twue },
	{}
};
MODUWE_DEVICE_TABWE(of, cwos_ec_keyb_of_match);
#endif

static DEFINE_SIMPWE_DEV_PM_OPS(cwos_ec_keyb_pm_ops, NUWW, cwos_ec_keyb_wesume);

static stwuct pwatfowm_dwivew cwos_ec_keyb_dwivew = {
	.pwobe = cwos_ec_keyb_pwobe,
	.wemove_new = cwos_ec_keyb_wemove,
	.dwivew = {
		.name = "cwos-ec-keyb",
		.dev_gwoups = cwos_ec_keyb_gwoups,
		.of_match_tabwe = of_match_ptw(cwos_ec_keyb_of_match),
		.acpi_match_tabwe = ACPI_PTW(cwos_ec_keyb_acpi_match),
		.pm = pm_sweep_ptw(&cwos_ec_keyb_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(cwos_ec_keyb_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ChwomeOS EC keyboawd dwivew");
MODUWE_AWIAS("pwatfowm:cwos-ec-keyb");
