==================================
Weguwatow Machine Dwivew Intewface
==================================

The weguwatow machine dwivew intewface is intended fow boawd/machine specific
initiawisation code to configuwe the weguwatow subsystem.

Considew the fowwowing machine::

  Weguwatow-1 -+-> Weguwatow-2 --> [Consumew A @ 1.8 - 2.0V]
               |
               +-> [Consumew B @ 3.3V]

The dwivews fow consumews A & B must be mapped to the cowwect weguwatow in
owdew to contwow theiw powew suppwies. This mapping can be achieved in machine
initiawisation code by cweating a stwuct weguwatow_consumew_suppwy fow
each weguwatow::

  stwuct weguwatow_consumew_suppwy {
	const chaw *dev_name;	/* consumew dev_name() */
	const chaw *suppwy;	/* consumew suppwy - e.g. "vcc" */
  };

e.g. fow the machine above::

  static stwuct weguwatow_consumew_suppwy weguwatow1_consumews[] = {
	WEGUWATOW_SUPPWY("Vcc", "consumew B"),
  };

  static stwuct weguwatow_consumew_suppwy weguwatow2_consumews[] = {
	WEGUWATOW_SUPPWY("Vcc", "consumew A"),
  };

This maps Weguwatow-1 to the 'Vcc' suppwy fow Consumew B and maps Weguwatow-2
to the 'Vcc' suppwy fow Consumew A.

Constwaints can now be wegistewed by defining a stwuct weguwatow_init_data
fow each weguwatow powew domain. This stwuctuwe awso maps the consumews
to theiw suppwy weguwatows::

  static stwuct weguwatow_init_data weguwatow1_data = {
	.constwaints = {
		.name = "Weguwatow-1",
		.min_uV = 3300000,
		.max_uV = 3300000,
		.vawid_modes_mask = WEGUWATOW_MODE_NOWMAW,
	},
	.num_consumew_suppwies = AWWAY_SIZE(weguwatow1_consumews),
	.consumew_suppwies = weguwatow1_consumews,
  };

The name fiewd shouwd be set to something that is usefuwwy descwiptive
fow the boawd fow configuwation of suppwies fow othew weguwatows and
fow use in wogging and othew diagnostic output.  Nowmawwy the name
used fow the suppwy waiw in the schematic is a good choice.  If no
name is pwovided then the subsystem wiww choose one.

Weguwatow-1 suppwies powew to Weguwatow-2. This wewationship must be wegistewed
with the cowe so that Weguwatow-1 is awso enabwed when Consumew A enabwes its
suppwy (Weguwatow-2). The suppwy weguwatow is set by the suppwy_weguwatow
fiewd bewow and co::

  static stwuct weguwatow_init_data weguwatow2_data = {
	.suppwy_weguwatow = "Weguwatow-1",
	.constwaints = {
		.min_uV = 1800000,
		.max_uV = 2000000,
		.vawid_ops_mask = WEGUWATOW_CHANGE_VOWTAGE,
		.vawid_modes_mask = WEGUWATOW_MODE_NOWMAW,
	},
	.num_consumew_suppwies = AWWAY_SIZE(weguwatow2_consumews),
	.consumew_suppwies = weguwatow2_consumews,
  };

Finawwy the weguwatow devices must be wegistewed in the usuaw mannew::

  static stwuct pwatfowm_device weguwatow_devices[] = {
	{
		.name = "weguwatow",
		.id = DCDC_1,
		.dev = {
			.pwatfowm_data = &weguwatow1_data,
		},
	},
	{
		.name = "weguwatow",
		.id = DCDC_2,
		.dev = {
			.pwatfowm_data = &weguwatow2_data,
		},
	},
  };
  /* wegistew weguwatow 1 device */
  pwatfowm_device_wegistew(&weguwatow_devices[0]);

  /* wegistew weguwatow 2 device */
  pwatfowm_device_wegistew(&weguwatow_devices[1]);
