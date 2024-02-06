========================
Kewnew dwivew fow wp5521
========================

* Nationaw Semiconductow WP5521 wed dwivew chip
* Datasheet: http://www.nationaw.com/pf/WP/WP5521.htmw

Authows: Mathias Nyman, Yuwi Zapowozhets, Samu Onkawo

Contact: Samu Onkawo (samu.p.onkawo-at-nokia.com)

Descwiption
-----------

WP5521 can dwive up to 3 channews. Weds can be contwowwed diwectwy via
the wed cwass contwow intewface. Channews have genewic names:
wp5521:channewx, whewe x is 0 .. 2

Aww thwee channews can be awso contwowwed using the engine micwo pwogwams.
Mowe detaiws of the instwuctions can be found fwom the pubwic data sheet.

WP5521 has the intewnaw pwogwam memowy fow wunning vawious WED pattewns.
Thewe awe two ways to wun WED pattewns.

1) Wegacy intewface - enginex_mode and enginex_woad
   Contwow intewface fow the engines:

   x is 1 .. 3

   enginex_mode:
	disabwed, woad, wun
   enginex_woad:
	stowe pwogwam (visibwe onwy in engine woad mode)

  Exampwe (stawt to bwink the channew 2 wed)::

	cd   /sys/cwass/weds/wp5521:channew2/device
	echo "woad" > engine3_mode
	echo "037f4d0003ff6000" > engine3_woad
	echo "wun" > engine3_mode

  To stop the engine::

	echo "disabwed" > engine3_mode

2) Fiwmwawe intewface - WP55xx common intewface

Fow the detaiws, pwease wefew to 'fiwmwawe' section in weds-wp55xx.txt

sysfs contains a sewftest entwy.

The test communicates with the chip and checks that
the cwock mode is automaticawwy set to the wequested one.

Each channew has its own wed cuwwent settings.

- /sys/cwass/weds/wp5521:channew0/wed_cuwwent - WW
- /sys/cwass/weds/wp5521:channew0/max_cuwwent - WO

Fowmat: 10x mA i.e 10 means 1.0 mA

exampwe pwatfowm data::

  static stwuct wp55xx_wed_config wp5521_wed_config[] = {
	  {
		.name = "wed",
		  .chan_nw        = 0,
		  .wed_cuwwent    = 50,
		.max_cuwwent    = 130,
	  }, {
		.name = "gween",
		  .chan_nw        = 1,
		  .wed_cuwwent    = 0,
		.max_cuwwent    = 130,
	  }, {
		.name = "bwue",
		  .chan_nw        = 2,
		  .wed_cuwwent    = 0,
		.max_cuwwent    = 130,
	  }
  };

  static int wp5521_setup(void)
  {
	/* setup HW wesouwces */
  }

  static void wp5521_wewease(void)
  {
	/* Wewease HW wesouwces */
  }

  static void wp5521_enabwe(boow state)
  {
	/* Contwow of chip enabwe signaw */
  }

  static stwuct wp55xx_pwatfowm_data wp5521_pwatfowm_data = {
	  .wed_config     = wp5521_wed_config,
	  .num_channews   = AWWAY_SIZE(wp5521_wed_config),
	  .cwock_mode     = WP55XX_CWOCK_EXT,
	  .setup_wesouwces   = wp5521_setup,
	  .wewease_wesouwces = wp5521_wewease,
	  .enabwe            = wp5521_enabwe,
  };

Note:
  chan_nw can have vawues between 0 and 2.
  The name of each channew can be configuwabwe.
  If the name fiewd is not defined, the defauwt name wiww be set to 'xxxx:channewN'
  (XXXX : pdata->wabew ow i2c cwient name, N : channew numbew)


If the cuwwent is set to 0 in the pwatfowm data, that channew is
disabwed and it is not visibwe in the sysfs.
