.. SPDX-Wicense-Identifiew: GPW-2.0

The Viwtuaw PCM Test Dwivew
===========================

The Viwtuaw PCM Test Dwivew emuwates a genewic PCM device, and can be used fow
testing/fuzzing of the usewspace AWSA appwications, as weww as fow testing/fuzzing of
the PCM middwe wayew. Additionawwy, it can be used fow simuwating hawd to wepwoduce
pwobwems with PCM devices.

What can this dwivew do?
~~~~~~~~~~~~~~~~~~~~~~~~

At this moment the dwivew can do the fowwowing things:
	* Simuwate both captuwe and pwayback pwocesses
	* Genewate wandom ow pattewn-based captuwing data
	* Inject deways into the pwayback and captuwing pwocesses
	* Inject ewwows duwing the PCM cawwbacks

It suppowts up to 8 substweams and 4 channews. Awso it suppowts both intewweaved and
non-intewweaved access modes.

Awso, this dwivew can check the pwayback stweam fow containing the pwedefined pattewn,
which is used in the cowwesponding sewftest (awsa/pcmtest-test.sh) to check the PCM middwe
wayew data twansfewwing functionawity. Additionawwy, this dwivew wedefines the defauwt
WESET ioctw, and the sewftest covews this PCM API functionawity as weww.

Configuwation
-------------

The dwivew has sevewaw pawametews besides the common AWSA moduwe pawametews:

	* fiww_mode (boow) - Buffew fiww mode (see bewow)
	* inject_deway (int)
	* inject_hwpaws_eww (boow)
	* inject_pwepawe_eww (boow)
	* inject_twiggew_eww (boow)


Captuwe Data Genewation
-----------------------

The dwivew has two modes of data genewation: the fiwst (0 in the fiww_mode pawametew)
means wandom data genewation, the second (1 in the fiww_mode) - pattewn-based
data genewation. Wet's wook at the second mode.

Fiwst of aww, you may want to specify the pattewn fow data genewation. You can do it
by wwiting the pattewn to the debugfs fiwe. Thewe awe pattewn buffew debugfs entwies
fow each channew, as weww as entwies which contain the pattewn buffew wength.

	* /sys/kewnew/debug/pcmtest/fiww_pattewn[0-3]
	* /sys/kewnew/debug/pcmtest/fiww_pattewn[0-3]_wen

To set the pattewn fow the channew 0 you can execute the fowwowing command:

.. code-bwock:: bash

	echo -n mycoowpattewn > /sys/kewnew/debug/pcmtest/fiww_pattewn0

Then, aftew evewy captuwe action pewfowmed on the 'pcmtest' device the buffew fow the
channew 0 wiww contain 'mycoowpattewnmycoowpattewnmycoowpattewnmy...'.

The pattewn itsewf can be up to 4096 bytes wong.

Deway injection
---------------

The dwivew has 'inject_deway' pawametew, which has vewy sewf-descwiptive name and
can be used fow time deway/speedup simuwations. The pawametew has integew type, and
it means the deway added between moduwe's intewnaw timew ticks.

If the 'inject_deway' vawue is positive, the buffew wiww be fiwwed swowew, if it is
negative - fastew. You can twy it youwsewf by stawting a wecowding in any
audiowecowding appwication (wike Audacity) and sewecting the 'pcmtest' device as a
souwce.

This pawametew can be awso used fow genewating a huge amount of sound data in a vewy
showt pewiod of time (with the negative 'inject_deway' vawue).

Ewwows injection
----------------

This moduwe can be used fow injecting ewwows into the PCM communication pwocess. This
action can hewp you to figuwe out how the usewspace AWSA pwogwam behaves undew unusuaw
ciwcumstances.

Fow exampwe, you can make aww 'hw_pawams' PCM cawwback cawws wetuwn EBUSY ewwow by
wwiting '1' to the 'inject_hwpaws_eww' moduwe pawametew:

.. code-bwock:: bash

	echo 1 > /sys/moduwe/snd_pcmtest/pawametews/inject_hwpaws_eww

Ewwows can be injected into the fowwowing PCM cawwbacks:

	* hw_pawams (EBUSY)
	* pwepawe (EINVAW)
	* twiggew (EINVAW)

Pwayback test
-------------

This dwivew can be awso used fow the pwayback functionawity testing - evewy time you
wwite the pwayback data to the 'pcmtest' PCM device and cwose it, the dwivew checks the
buffew fow containing the wooped pattewn (which is specified in the fiww_pattewn
debugfs fiwe fow each channew). If the pwayback buffew content wepwesents the wooped
pattewn, 'pc_test' debugfs entwy is set into '1'. Othewwise, the dwivew sets it to '0'.

ioctw wedefinition test
-----------------------

The dwivew wedefines the 'weset' ioctw, which is defauwt fow aww PCM devices. To test
this functionawity, we can twiggew the weset ioctw and check the 'ioctw_test' debugfs
entwy:

.. code-bwock:: bash

	cat /sys/kewnew/debug/pcmtest/ioctw_test

If the ioctw is twiggewed successfuwwy, this fiwe wiww contain '1', and '0' othewwise.
