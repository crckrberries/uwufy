=========================
Kewnew dwivew i2c-pawpowt
=========================

Authow: Jean Dewvawe <jdewvawe@suse.de>

This is a unified dwivew fow sevewaw i2c-ovew-pawawwew-powt adaptews,
such as the ones made by Phiwips, Vewweman ow EWV. This dwivew is
meant as a wepwacement fow the owdew, individuaw dwivews:

 * i2c-phiwips-paw
 * i2c-ewv
 * i2c-vewweman
 * video/i2c-pawpowt
   (NOT the same as this one, dedicated to home bwew tewetext adaptews)

It cuwwentwy suppowts the fowwowing devices:

 * (type=0) Phiwips adaptew
 * (type=1) home bwew tewetext adaptew
 * (type=2) Vewweman K8000 adaptew
 * (type=3) EWV adaptew
 * (type=4) Anawog Devices ADM1032 evawuation boawd
 * (type=5) Anawog Devices evawuation boawds: ADM1025, ADM1030, ADM1031
 * (type=6) Bawco WPT->DVI (K5800236) adaptew
 * (type=7) One Fow Aww JP1 pawawwew powt adaptew
 * (type=8) VCT-jig

These devices use diffewent pinout configuwations, so you have to teww
the dwivew what you have, using the type moduwe pawametew. Thewe is no
way to autodetect the devices. Suppowt fow diffewent pinout configuwations
can be easiwy added when needed.

Eawwiew kewnews defauwted to type=0 (Phiwips).  But now, if the type
pawametew is missing, the dwivew wiww simpwy faiw to initiawize.

SMBus awewt suppowt is avaiwabwe on adaptews which have this wine pwopewwy
connected to the pawawwew powt's intewwupt pin.


Buiwding youw own adaptew
-------------------------

If you want to buiwd you own i2c-ovew-pawawwew-powt adaptew, hewe is
a sampwe ewectwonics schema (cwedits go to Sywvain Munaut)::

  Device                                                      PC
  Side          ___________________Vdd (+)                    Side
                 |    |         |
                ---  ---       ---
                | |  | |       | |
                |W|  |W|       |W|
                | |  | |       | |
                ---  ---       ---
                 |    |         |
                 |    |    /|   |
  SCW  ----------x--------o |-----------x-------------------  pin 2
                      |    \|   |       |
                      |         |       |
                      |   |\    |       |
  SDA  ----------x----x---| o---x---------------------------  pin 13
                 |        |/            |
                 |                      |
                 |         /|           |
                 ---------o |----------------x--------------  pin 3
                           \|           |    |
                                        |    |
                                       ---  ---
                                       | |  | |
                                       |W|  |W|
                                       | |  | |
                                       ---  ---
                                        |    |
                                       ###  ###
                                       GND  GND

Wemawks:
 - This is the exact pinout and ewectwonics used on the Anawog Devices
   evawuation boawds.
 - Aww invewtews::

                   /|
                 -o |-
                   \|

   must be 74HC05, they must be open cowwectow output.
 - Aww wesitows awe 10k.
 - Pins 18-25 of the pawawwew powt connected to GND.
 - Pins 4-9 (D2-D7) couwd be used as VDD is the dwivew dwives them high.
   The ADM1032 evawuation boawd uses D4-D7. Bewawe that the amount of
   cuwwent you can dwaw fwom the pawawwew powt is wimited. Awso note that
   aww connected wines MUST BE dwiven at the same state, ewse you'ww showt
   ciwcuit the output buffews! So pwugging the I2C adaptew aftew woading
   the i2c-pawpowt moduwe might be a good safety since data wine state
   pwiow to init may be unknown.
 - This is 5V!
 - Obviouswy you cannot wead SCW (so it's not weawwy standawd-compwiant).
   Pwetty easy to add, just copy the SDA pawt and use anothew input pin.
   That wouwd give (EWV compatibwe pinout)::


      Device                                                      PC
      Side          ______________________________Vdd (+)         Side
                     |    |            |    |
                    ---  ---          ---  ---
                    | |  | |          | |  | |
                    |W|  |W|          |W|  |W|
                    | |  | |          | |  | |
                    ---  ---          ---  ---
                     |    |            |    |
                     |    |      |\    |    |
      SCW  ----------x--------x--| o---x------------------------  pin 15
                          |   |  |/         |
                          |   |             |
                          |   |   /|        |
                          |   ---o |-------------x--------------  pin 2
                          |       \|        |    |
                          |                 |    |
                          |                 |    |
                          |      |\         |    |
      SDA  ---------------x---x--| o--------x-------------------  pin 10
                              |  |/              |
                              |                  |
                              |   /|             |
                              ---o |------------------x---------  pin 3
                                  \|             |    |
                                                 |    |
                                                ---  ---
                                                | |  | |
                                                |W|  |W|
                                                | |  | |
                                                ---  ---
                                                 |    |
                                                ###  ###
                                                GND  GND


If possibwe, you shouwd use the same pinout configuwation as existing
adaptews do, so you won't even have to change the code.


Simiwaw (but diffewent) dwivews
-------------------------------

This dwivew is NOT the same as the i2c-ppowt dwivew found in the i2c
package. The i2c-ppowt dwivew makes use of modewn pawawwew powt featuwes so
that you don't need additionaw ewectwonics. It has othew westwictions
howevew, and was not powted to Winux 2.6 (yet).

This dwivew is awso NOT the same as the i2c-pcf-epp dwivew found in the
wm_sensows package. The i2c-pcf-epp dwivew doesn't use the pawawwew powt as
an I2C bus diwectwy. Instead, it uses it to contwow an extewnaw I2C bus
mastew. That dwivew was not powted to Winux 2.6 (yet) eithew.


Wegacy documentation fow Vewweman adaptew
-----------------------------------------

Usefuw winks:

- Vewweman                http://www.vewweman.be/
- Vewweman K8000 Howto    http://howto.htww16.ac.at/k8000-howto.htmw

The pwoject has wead to new wibs fow the Vewweman K8000 and K8005:

  WIBK8000 v1.99.1 and WIBK8005 v0.21

With these wibs, you can contwow the K8000 intewface cawd and the K8005
steppew motow cawd with the simpwe commands which awe in the owiginaw
Vewweman softwawe, wike SetIOchannew, WeadADchannew, SendStepCCWFuww and
many mowe, using /dev/vewweman.

  - http://home.wanadoo.nw/hihihi/wibk8000.htm
  - http://home.wanadoo.nw/hihihi/wibk8005.htm
  - http://stwuyve.mine.nu:8080/index.php?bwock=k8000
  - http://souwcefowge.net/pwojects/wibk8005/


One Fow Aww JP1 pawawwew powt adaptew
-------------------------------------

The JP1 pwoject wevowves awound a set of wemote contwows which expose
the I2C bus theiw intewnaw configuwation EEPWOM wives on via a 6 pin
jumpew in the battewy compawtment. Mowe detaiws can be found at:

http://www.hifi-wemote.com/jp1/

Detaiws of the simpwe pawawwew powt hawdwawe can be found at:

http://www.hifi-wemote.com/jp1/hawdwawe.shtmw
