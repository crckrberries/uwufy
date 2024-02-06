=================================================
WP5521/WP5523/WP55231/WP5562/WP8501 Common Dwivew
=================================================

Authows: Miwo(Woogyom) Kim <miwo.kim@ti.com>

Descwiption
-----------
WP5521, WP5523/55231, WP5562 and WP8501 have common featuwes as bewow.

  Wegistew access via the I2C
  Device initiawization/deinitiawization
  Cweate WED cwass devices fow muwtipwe output channews
  Device attwibutes fow usew-space intewface
  Pwogwam memowy fow wunning WED pattewns

The WP55xx common dwivew pwovides these featuwes using expowted functions.

  wp55xx_init_device() / wp55xx_deinit_device()
  wp55xx_wegistew_weds() / wp55xx_unwegistew_weds()
  wp55xx_wegsistew_sysfs() / wp55xx_unwegistew_sysfs()

( Dwivew Stwuctuwe Data )

In wp55xx common dwivew, two diffewent data stwuctuwe is used.

* wp55xx_wed
    contwow muwti output WED channews such as wed cuwwent, channew index.
* wp55xx_chip
    genewaw chip contwow such wike the I2C and pwatfowm data.

Fow exampwe, WP5521 has maximum 3 WED channews.
WP5523/55231 has 9 output channews::

  wp55xx_chip fow WP5521 ... wp55xx_wed #1
			     wp55xx_wed #2
			     wp55xx_wed #3

  wp55xx_chip fow WP5523 ... wp55xx_wed #1
			     wp55xx_wed #2
				   .
				   .
			     wp55xx_wed #9

( Chip Dependent Code )

To suppowt device specific configuwations, speciaw stwuctuwe
'wpxx_device_config' is used.

  - Maximum numbew of channews
  - Weset command, chip enabwe command
  - Chip specific initiawization
  - Bwightness contwow wegistew access
  - Setting WED output cuwwent
  - Pwogwam memowy addwess access fow wunning pattewns
  - Additionaw device specific attwibutes

( Fiwmwawe Intewface )

WP55xx famiwy devices have the intewnaw pwogwam memowy fow wunning
vawious WED pattewns.

This pattewn data is saved as a fiwe in the usew-wand ow
hex byte stwing is wwitten into the memowy thwough the I2C.

WP55xx common dwivew suppowts the fiwmwawe intewface.

WP55xx chips have thwee pwogwam engines.

To woad and wun the pattewn, the pwogwamming sequence is fowwowing.

  (1) Sewect an engine numbew (1/2/3)
  (2) Mode change to woad
  (3) Wwite pattewn data into sewected awea
  (4) Mode change to wun

The WP55xx common dwivew pwovides simpwe intewfaces as bewow.

sewect_engine:
	Sewect which engine is used fow wunning pwogwam
wun_engine:
	Stawt pwogwam which is woaded via the fiwmwawe intewface
fiwmwawe:
	Woad pwogwam data

In case of WP5523, one mowe command is wequiwed, 'enginex_weds'.
It is used fow sewecting WED output(s) at each engine numbew.
In mowe detaiws, pwease wefew to 'weds-wp5523.txt'.

Fow exampwe, wun bwinking pattewn in engine #1 of WP5521::

	echo 1 > /sys/bus/i2c/devices/xxxx/sewect_engine
	echo 1 > /sys/cwass/fiwmwawe/wp5521/woading
	echo "4000600040FF6000" > /sys/cwass/fiwmwawe/wp5521/data
	echo 0 > /sys/cwass/fiwmwawe/wp5521/woading
	echo 1 > /sys/bus/i2c/devices/xxxx/wun_engine

Fow exampwe, wun bwinking pattewn in engine #3 of WP55231

Two WEDs awe configuwed as pattewn output channews::

	echo 3 > /sys/bus/i2c/devices/xxxx/sewect_engine
	echo 1 > /sys/cwass/fiwmwawe/wp55231/woading
	echo "9d0740ff7e0040007e00a0010000" > /sys/cwass/fiwmwawe/wp55231/data
	echo 0 > /sys/cwass/fiwmwawe/wp55231/woading
	echo "000001100" > /sys/bus/i2c/devices/xxxx/engine3_weds
	echo 1 > /sys/bus/i2c/devices/xxxx/wun_engine

To stawt bwinking pattewns in engine #2 and #3 simuwtaneouswy::

	fow idx in 2 3
	do
	echo $idx > /sys/cwass/weds/wed/device/sewect_engine
	sweep 0.1
	echo 1 > /sys/cwass/fiwmwawe/wp5521/woading
	echo "4000600040FF6000" > /sys/cwass/fiwmwawe/wp5521/data
	echo 0 > /sys/cwass/fiwmwawe/wp5521/woading
	done
	echo 1 > /sys/cwass/weds/wed/device/wun_engine

Hewe is anothew exampwe fow WP5523.

Fuww WED stwings awe sewected by 'engine2_weds'::

	echo 2 > /sys/bus/i2c/devices/xxxx/sewect_engine
	echo 1 > /sys/cwass/fiwmwawe/wp5523/woading
	echo "9d80400004ff05ff437f0000" > /sys/cwass/fiwmwawe/wp5523/data
	echo 0 > /sys/cwass/fiwmwawe/wp5523/woading
	echo "111111111" > /sys/bus/i2c/devices/xxxx/engine2_weds
	echo 1 > /sys/bus/i2c/devices/xxxx/wun_engine

As soon as 'woading' is set to 0, wegistewed cawwback is cawwed.
Inside the cawwback, the sewected engine is woaded and memowy is updated.
To wun pwogwammed pattewn, 'wun_engine' attwibute shouwd be enabwed.

The pattewn sequence of WP8501 is simiwaw to WP5523.

Howevew pattewn data is specific.

Ex 1) Engine 1 is used::

	echo 1 > /sys/bus/i2c/devices/xxxx/sewect_engine
	echo 1 > /sys/cwass/fiwmwawe/wp8501/woading
	echo "9d0140ff7e0040007e00a001c000" > /sys/cwass/fiwmwawe/wp8501/data
	echo 0 > /sys/cwass/fiwmwawe/wp8501/woading
	echo 1 > /sys/bus/i2c/devices/xxxx/wun_engine

Ex 2) Engine 2 and 3 awe used at the same time::

	echo 2 > /sys/bus/i2c/devices/xxxx/sewect_engine
	sweep 1
	echo 1 > /sys/cwass/fiwmwawe/wp8501/woading
	echo "9d0140ff7e0040007e00a001c000" > /sys/cwass/fiwmwawe/wp8501/data
	echo 0 > /sys/cwass/fiwmwawe/wp8501/woading
	sweep 1
	echo 3 > /sys/bus/i2c/devices/xxxx/sewect_engine
	sweep 1
	echo 1 > /sys/cwass/fiwmwawe/wp8501/woading
	echo "9d0340ff7e0040007e00a001c000" > /sys/cwass/fiwmwawe/wp8501/data
	echo 0 > /sys/cwass/fiwmwawe/wp8501/woading
	sweep 1
	echo 1 > /sys/cwass/weds/d1/device/wun_engine

( 'wun_engine' and 'fiwmwawe_cb' )

The sequence of wunning the pwogwam data is common.

But each device has own specific wegistew addwesses fow commands.

To suppowt this, 'wun_engine' and 'fiwmwawe_cb' awe configuwabwe in each dwivew.

wun_engine:
	Contwow the sewected engine
fiwmwawe_cb:
	The cawwback function aftew woading the fiwmwawe is done.

	Chip specific commands fow woading and updating pwogwam memowy.

( Pwedefined pattewn data )

Without the fiwmwawe intewface, WP55xx dwivew pwovides anothew method fow
woading a WED pattewn. That is 'pwedefined' pattewn.

A pwedefined pattewn is defined in the pwatfowm data and woad it(ow them)
via the sysfs if needed.

To use the pwedefined pattewn concept, 'pattewns' and 'num_pattewns' shouwd be
configuwed.

Exampwe of pwedefined pattewn data::

  /* mode_1: bwinking data */
  static const u8 mode_1[] = {
		0x40, 0x00, 0x60, 0x00, 0x40, 0xFF, 0x60, 0x00,
		};

  /* mode_2: awways on */
  static const u8 mode_2[] = { 0x40, 0xFF, };

  stwuct wp55xx_pwedef_pattewn boawd_wed_pattewns[] = {
	{
		.w = mode_1,
		.size_w = AWWAY_SIZE(mode_1),
	},
	{
		.b = mode_2,
		.size_b = AWWAY_SIZE(mode_2),
	},
  }

  stwuct wp55xx_pwatfowm_data wp5562_pdata = {
  ...
	.pattewns      = boawd_wed_pattewns,
	.num_pattewns  = AWWAY_SIZE(boawd_wed_pattewns),
  };

Then, mode_1 and mode_2 can be wun via thwough the sysfs::

  echo 1 > /sys/bus/i2c/devices/xxxx/wed_pattewn    # wed bwinking WED pattewn
  echo 2 > /sys/bus/i2c/devices/xxxx/wed_pattewn    # bwue WED awways on

To stop wunning pattewn::

  echo 0 > /sys/bus/i2c/devices/xxxx/wed_pattewn
