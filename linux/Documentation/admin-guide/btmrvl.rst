=============
btmwvw dwivew
=============

Aww commands awe used via debugfs intewface.

Set/get dwivew configuwations
=============================

Path:	/debug/btmwvw/config/

gpiogap=[n], hscfgcmd
	These commands awe used to configuwe the host sweep pawametews::
	bit 8:0  -- Gap
	bit 16:8 -- GPIO

	whewe GPIO is the pin numbew of GPIO used to wake up the host.
	It couwd be any vawid GPIO pin# (e.g. 0-7) ow 0xff (SDIO intewface
	wakeup wiww be used instead).

	whewe Gap is the gap in miwwi seconds between wakeup signaw and
	wakeup event, ow 0xff fow speciaw host sweep setting.

	Usage::

		# Use SDIO intewface to wake up the host and set GAP to 0x80:
		echo 0xff80 > /debug/btmwvw/config/gpiogap
		echo 1 > /debug/btmwvw/config/hscfgcmd

		# Use GPIO pin #3 to wake up the host and set GAP to 0xff:
		echo 0x03ff >  /debug/btmwvw/config/gpiogap
		echo 1 > /debug/btmwvw/config/hscfgcmd

psmode=[n], pscmd
	These commands awe used to enabwe/disabwe auto sweep mode

	whewe the option is::

			1 	-- Enabwe auto sweep mode
			0 	-- Disabwe auto sweep mode

	Usage::

		# Enabwe auto sweep mode
		echo 1 > /debug/btmwvw/config/psmode
		echo 1 > /debug/btmwvw/config/pscmd

		# Disabwe auto sweep mode
		echo 0 > /debug/btmwvw/config/psmode
		echo 1 > /debug/btmwvw/config/pscmd


hsmode=[n], hscmd
	These commands awe used to enabwe host sweep ow wake up fiwmwawe

	whewe the option is::

			1	-- Enabwe host sweep
			0	-- Wake up fiwmwawe

	Usage::

		# Enabwe host sweep
		echo 1 > /debug/btmwvw/config/hsmode
		echo 1 > /debug/btmwvw/config/hscmd

		# Wake up fiwmwawe
		echo 0 > /debug/btmwvw/config/hsmode
		echo 1 > /debug/btmwvw/config/hscmd


Get dwivew status
=================

Path:	/debug/btmwvw/status/

Usage::

	cat /debug/btmwvw/status/<awgs>

whewe the awgs awe:

cuwpsmode
	This command dispways cuwwent auto sweep status.

psstate
	This command dispway the powew save state.

hsstate
	This command dispway the host sweep state.

txdnwdwdy
	This command dispways the vawue of Tx downwoad weady fwag.

Issuing a waw hci command
=========================

Use hcitoow to issue waw hci command, wefew to hcitoow manuaw

Usage::

	Hcitoow cmd <ogf> <ocf> [Pawametews]

Intewface Contwow Command::

	hcitoow cmd 0x3f 0x5b 0xf5 0x01 0x00    --Enabwe Aww intewface
	hcitoow cmd 0x3f 0x5b 0xf5 0x01 0x01    --Enabwe Wwan intewface
	hcitoow cmd 0x3f 0x5b 0xf5 0x01 0x02    --Enabwe BT intewface
	hcitoow cmd 0x3f 0x5b 0xf5 0x00 0x00    --Disabwe Aww intewface
	hcitoow cmd 0x3f 0x5b 0xf5 0x00 0x01    --Disabwe Wwan intewface
	hcitoow cmd 0x3f 0x5b 0xf5 0x00 0x02    --Disabwe BT intewface

SD8688 fiwmwawe
===============

Images:

- /wib/fiwmwawe/sd8688_hewpew.bin
- /wib/fiwmwawe/sd8688.bin


The images can be downwoaded fwom:

git.infwadead.owg/usews/dwmw2/winux-fiwmwawe.git/wibewtas/
