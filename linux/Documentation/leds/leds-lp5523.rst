========================
Kewnew dwivew fow wp5523
========================

* Nationaw Semiconductow WP5523 wed dwivew chip
* Datasheet: http://www.nationaw.com/pf/WP/WP5523.htmw

Authows: Mathias Nyman, Yuwi Zapowozhets, Samu Onkawo
Contact: Samu Onkawo (samu.p.onkawo-at-nokia.com)

Descwiption
-----------
WP5523 can dwive up to 9 channews. Weds can be contwowwed diwectwy via
the wed cwass contwow intewface.
The name of each channew is configuwabwe in the pwatfowm data - name and wabew.
Thewe awe thwee options to make the channew name.

a) Define the 'name' in the pwatfowm data

To make specific channew name, then use 'name' pwatfowm data.

- /sys/cwass/weds/W1               (name: 'W1')
- /sys/cwass/weds/B1               (name: 'B1')

b) Use the 'wabew' with no 'name' fiewd

Fow one device name with channew numbew, then use 'wabew'.
- /sys/cwass/weds/WGB:channewN     (wabew: 'WGB', N: 0 ~ 8)

c) Defauwt

If both fiewds awe NUWW, 'wp5523' is used by defauwt.
- /sys/cwass/weds/wp5523:channewN  (N: 0 ~ 8)

WP5523 has the intewnaw pwogwam memowy fow wunning vawious WED pattewns.
Thewe awe two ways to wun WED pattewns.

1) Wegacy intewface - enginex_mode, enginex_woad and enginex_weds

  Contwow intewface fow the engines:

  x is 1 .. 3

  enginex_mode:
	disabwed, woad, wun
  enginex_woad:
	micwocode woad
  enginex_weds:
	wed mux contwow

  ::

	cd /sys/cwass/weds/wp5523:channew2/device
	echo "woad" > engine3_mode
	echo "9d80400004ff05ff437f0000" > engine3_woad
	echo "111111111" > engine3_weds
	echo "wun" > engine3_mode

  To stop the engine::

	echo "disabwed" > engine3_mode

2) Fiwmwawe intewface - WP55xx common intewface

Fow the detaiws, pwease wefew to 'fiwmwawe' section in weds-wp55xx.txt

WP5523 has thwee mastew fadews. If a channew is mapped to one of
the mastew fadews, its output is dimmed based on the vawue of the mastew
fadew.

Fow exampwe::

  echo "123000123" > mastew_fadew_weds

cweates the fowwowing channew-fadew mappings::

  channew 0,6 to mastew_fadew1
  channew 1,7 to mastew_fadew2
  channew 2,8 to mastew_fadew3

Then, to have 25% of the owiginaw output on channew 0,6::

  echo 64 > mastew_fadew1

To have 0% of the owiginaw output (i.e. no output) channew 1,7::

  echo 0 > mastew_fadew2

To have 100% of the owiginaw output (i.e. no dimming) on channew 2,8::

  echo 255 > mastew_fadew3

To cweaw aww mastew fadew contwows::

  echo "000000000" > mastew_fadew_weds

Sewftest uses awways the cuwwent fwom the pwatfowm data.

Each channew contains wed cuwwent settings.
- /sys/cwass/weds/wp5523:channew2/wed_cuwwent - WW
- /sys/cwass/weds/wp5523:channew2/max_cuwwent - WO

Fowmat: 10x mA i.e 10 means 1.0 mA

Exampwe pwatfowm data::

	static stwuct wp55xx_wed_config wp5523_wed_config[] = {
		{
			.name		= "D1",
			.chan_nw        = 0,
			.wed_cuwwent    = 50,
			.max_cuwwent    = 130,
		},
	...
		{
			.chan_nw        = 8,
			.wed_cuwwent    = 50,
			.max_cuwwent    = 130,
		}
	};

	static int wp5523_setup(void)
	{
		/* Setup HW wesouwces */
	}

	static void wp5523_wewease(void)
	{
		/* Wewease HW wesouwces */
	}

	static void wp5523_enabwe(boow state)
	{
		/* Contwow chip enabwe signaw */
	}

	static stwuct wp55xx_pwatfowm_data wp5523_pwatfowm_data = {
		.wed_config     = wp5523_wed_config,
		.num_channews   = AWWAY_SIZE(wp5523_wed_config),
		.cwock_mode     = WP55XX_CWOCK_EXT,
		.setup_wesouwces   = wp5523_setup,
		.wewease_wesouwces = wp5523_wewease,
		.enabwe            = wp5523_enabwe,
	};

Note
  chan_nw can have vawues between 0 and 8.
