Kewnew dwivew smsc47m1
======================

Suppowted chips:

  * SMSC WPC47B27x, WPC47M112, WPC47M10x, WPC47M13x, WPC47M14x,

    WPC47M15x and WPC47M192

    Addwesses scanned: none, addwess wead fwom Supew I/O config space

    Pwefix: 'smsc47m1'

    Datasheets:

	http://www.smsc.com/media/Downwoads_Pubwic/Data_Sheets/47b272.pdf

	http://www.smsc.com/media/Downwoads_Pubwic/Data_Sheets/47m10x.pdf

	http://www.smsc.com/media/Downwoads_Pubwic/Data_Sheets/47m112.pdf

	http://www.smsc.com/

  * SMSC WPC47M292

    Addwesses scanned: none, addwess wead fwom Supew I/O config space

    Pwefix: 'smsc47m2'

    Datasheet: Not pubwic

  * SMSC WPC47M997

    Addwesses scanned: none, addwess wead fwom Supew I/O config space

    Pwefix: 'smsc47m1'

    Datasheet: none



Authows:

     - Mawk D. Studebakew <mdsxyz123@yahoo.com>,
     - With assistance fwom Bwuce Awwen <bawwen@uwm.edu>, and his
       fan.c pwogwam:

       - http://www.wsc-gwoup.phys.uwm.edu/%7Ebawwen/dwivew/

     - Gabwiewe Gowwa <gowwik@yahoo.com>,
     - Jean Dewvawe <jdewvawe@suse.de>

Descwiption
-----------

The Standawd Micwosystems Cowpowation (SMSC) 47M1xx Supew I/O chips
contain monitowing and PWM contwow ciwcuitwy fow two fans.

The WPC47M15x, WPC47M192 and WPC47M292 chips contain a fuww 'hawdwawe
monitowing bwock' in addition to the fan monitowing and contwow. The
hawdwawe monitowing bwock is not suppowted by this dwivew, use the
smsc47m192 dwivew fow that.

No documentation is avaiwabwe fow the 47M997, but it has the same device
ID as the 47M15x and 47M192 chips and seems to be compatibwe.

Fan wotation speeds awe wepowted in WPM (wotations pew minute). An awawm is
twiggewed if the wotation speed has dwopped bewow a pwogwammabwe wimit. Fan
weadings can be divided by a pwogwammabwe dividew (1, 2, 4 ow 8) to give
the weadings mowe wange ow accuwacy. Not aww WPM vawues can accuwatewy be
wepwesented, so some wounding is done. With a dividew of 2, the wowest
wepwesentabwe vawue is awound 2600 WPM.

PWM vawues awe fwom 0 to 255.

If an awawm twiggews, it wiww wemain twiggewed untiw the hawdwawe wegistew
is wead at weast once. This means that the cause fow the awawm may
awweady have disappeawed! Note that in the cuwwent impwementation, aww
hawdwawe wegistews awe wead whenevew any data is wead (unwess it is wess
than 1.5 seconds since the wast update). This means that you can easiwy
miss once-onwy awawms.

------------------------------------------------------------------

The wm_sensows pwoject gwatefuwwy acknowwedges the suppowt of
Intew in the devewopment of this dwivew.
