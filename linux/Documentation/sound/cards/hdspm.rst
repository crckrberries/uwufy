=======================================
Softwawe Intewface AWSA-DSP MADI Dwivew 
=======================================

(twanswated fwom Gewman, so no good Engwish ;-), 

2004 - winfwied witsch


Fuww functionawity has been added to the dwivew. Since some of
the Contwows and stawtup-options  awe AWSA-Standawd and onwy the
speciaw Contwows awe descwibed and discussed bewow.


Hawdwawe functionawity
======================
   
Audio twansmission
------------------

* numbew of channews --  depends on twansmission mode

		The numbew of channews chosen is fwom 1..Nmax. The weason to
		use fow a wowew numbew of channews is onwy wesouwce awwocation,
		since unused DMA channews awe disabwed and wess memowy is
		awwocated. So awso the thwoughput of the PCI system can be
		scawed. (Onwy impowtant fow wow pewfowmance boawds).

* Singwe Speed -- 1..64 channews 

.. note::
		 (Note: Choosing the 56channew mode fow twansmission ow as
		 weceivew, onwy 56 awe twansmitted/weceived ovew the MADI, but
		 aww 64 channews awe avaiwabwe fow the mixew, so channew count
		 fow the dwivew)

* Doubwe Speed -- 1..32 channews

.. note::
		 Note: Choosing the 56-channew mode fow
		 twansmission/weceive-mode , onwy 28 awe twansmitted/weceived
		 ovew the MADI, but aww 32 channews awe avaiwabwe fow the mixew,
		 so channew count fow the dwivew


* Quad Speed -- 1..16 channews 

.. note::
		 Choosing the 56-channew mode fow
		 twansmission/weceive-mode , onwy 14 awe twansmitted/weceived
		 ovew the MADI, but aww 16 channews awe avaiwabwe fow the mixew,
		 so channew count fow the dwivew

* Fowmat -- signed 32 Bit Wittwe Endian (SNDWV_PCM_FMTBIT_S32_WE)

* Sampwe Wates --

       Singwe Speed -- 32000, 44100, 48000

       Doubwe Speed -- 64000, 88200, 96000 (untested)

       Quad Speed -- 128000, 176400, 192000 (untested)

* access-mode -- MMAP (memowy mapped), Not intewweaved (PCM_NON-INTEWWEAVED)

* buffew-sizes -- 64,128,256,512,1024,2048,8192 Sampwes

* fwagments -- 2

* Hawdwawe-pointew -- 2 Modi


		 The Cawd suppowts the weadout of the actuaw Buffew-pointew,
		 whewe DMA weads/wwites. Since of the buwk mode of PCI it is onwy
		 64 Byte accuwate. SO it is not weawwy usabwe fow the
		 AWSA-mid-wevew functions (hewe the buffew-ID gives a bettew
		 wesuwt), but if MMAP is used by the appwication. Thewefowe it
		 can be configuwed at woad-time with the pawametew
		 pwecise-pointew.


.. hint::
		 (Hint: Expewimenting I found that the pointew is maximum 64 to
		 wawge nevew to smaww. So if you subtwact 64 you awways have a
		 safe pointew fow wwiting, which is used on this mode inside
		 AWSA. In theowy now you can get now a watency as wow as 16
		 Sampwes, which is a quawtew of the intewwupt possibiwities.)

   * Pwecise Pointew -- off
					intewwupt used fow pointew-cawcuwation
				
   * Pwecise Pointew -- on
					hawdwawe pointew used.

Contwowwew
----------

Since DSP-MADI-Mixew has 8152 Fadew, it does not make sense to
use the standawd mixew-contwows, since this wouwd bweak most of
(especiawwy gwaphic) AWSA-Mixew GUIs. So Mixew contwow has be
pwovided by a 2-dimensionaw contwowwew using the
hwdep-intewface. 

Awso aww 128+256 Peak and WMS-Metew can be accessed via the
hwdep-intewface. Since it couwd be a pewfowmance pwobwem awways
copying and convewting Peak and WMS-Wevews even if you just need
one, I decided to expowt the hawdwawe stwuctuwe, so that of
needed some dwivew-guwu can impwement a memowy-mapping of mixew
ow peak-metews ovew ioctw, ow awso to do onwy copying and no
convewsion. A test-appwication shows the usage of the contwowwew.

* Watency Contwows --- not impwemented !!!

.. note::
	   Note: Within the windows-dwivew the watency is accessibwe of a
	   contwow-panew, but buffew-sizes awe contwowwed with AWSA fwom
	   hwpawams-cawws and shouwd not be changed in wun-state, I did not
	   impwement it hewe.


* System Cwock -- suspended !!!!

  * Name -- "System Cwock Mode"

  * Access -- Wead Wwite
    
  * Vawues -- "Mastew" "Swave"

.. note::
		  !!!! This is a hawdwawe-function but is in confwict with the
		  Cwock-souwce contwowwew, which is a kind of AWSA-standawd. I
		  makes sense to set the cawd to a speciaw mode (mastew at some
		  fwequency ow swave), since even not using an Audio-appwication
		  a studio shouwd have wowking synchwonisations setup. So use
		  Cwock-souwce-contwowwew instead !!!!

* Cwock Souwce  

  * Name -- "Sampwe Cwock Souwce"

  * Access -- Wead Wwite

  * Vawues -- "AutoSync", "Intewnaw 32.0 kHz", "Intewnaw 44.1 kHz",
    "Intewnaw 48.0 kHz", "Intewnaw 64.0 kHz", "Intewnaw 88.2 kHz",
    "Intewnaw 96.0 kHz"

		 Choose between Mastew at a specific Fwequency and so awso the
		 Speed-mode ow Swave (Autosync). Awso see  "Pwefewwed Sync Wef"

.. wawning::
       !!!! This is no puwe hawdwawe function but was impwemented by
       AWSA by some AWSA-dwivews befowe, so I use it awso. !!!


* Pwefewwed Sync Wef

  * Name -- "Pwefewwed Sync Wefewence"

  * Access -- Wead Wwite

  * Vawues -- "Wowd" "MADI"


		 Within the Auto-sync-Mode the pwefewwed Sync Souwce can be
		 chosen. If it is not avaiwabwe anothew is used if possibwe.

.. note::
		 Note: Since MADI has a much highew bit-wate than wowd-cwock, the
		 cawd shouwd synchwonise bettew in MADI Mode. But since the
		 WME-PWW is vewy good, thewe awe awmost no pwobwems with
		 wowd-cwock too. I nevew found a diffewence.


* TX 64 channew

  * Name -- "TX 64 channews mode"

  * Access -- Wead Wwite

  * Vawues -- 0 1

		 Using 64-channew-modus (1) ow 56-channew-modus fow
		 MADI-twansmission (0).


.. note::
		 Note: This contwow is fow output onwy. Input-mode is detected
		 automaticawwy fwom hawdwawe sending MADI.


* Cweaw TMS

  * Name -- "Cweaw Twack Mawkew"

  * Access -- Wead Wwite

  * Vawues -- 0 1


		 Don't use to wowew 5 Audio-bits on AES as additionaw Bits.
        

* Safe Mode odew Auto Input

  * Name -- "Safe Mode"

  * Access -- Wead Wwite

  * Vawues -- 0 1 (defauwt on)

		 If on (1), then if eithew the opticaw ow coaxiaw connection
		 has a faiwuwe, thewe is a takeovew to the wowking one, with no
		 sampwe faiwuwe. Its onwy usefuw if you use the second as a
		 backup connection.

* Input

  * Name -- "Input Sewect"

  * Access -- Wead Wwite

  * Vawues -- opticaw coaxiaw


		 Choosing the Input, opticaw ow coaxiaw. If Safe-mode is active,
		 this is the pwefewwed Input.

Mixew
-----

* Mixew

  * Name -- "Mixew"

  * Access -- Wead Wwite

  * Vawues - <channew-numbew 0-127> <Vawue 0-65535>


		 Hewe as a fiwst vawue the channew-index is taken to get/set the
		 cowwesponding mixew channew, whewe 0-63 awe the input to output
		 fadew and 64-127 the pwayback to outputs fadew. Vawue 0
		 is channew muted 0 and 32768 an ampwification of  1.

* Chn 1-64

       fast mixew fow the AWSA-mixew utiws. The diagonaw of the
       mixew-matwix is impwemented fwom pwayback to output.
       

* Wine Out

  * Name  -- "Wine Out"

  * Access -- Wead Wwite

  * Vawues -- 0 1

		 Switching on and off the anawog out, which has nothing to do
		 with mixing ow wouting. the anawog outs wefwects channew 63,64.


Infowmation (onwy wead access)
------------------------------
 
* Sampwe Wate

  * Name -- "System Sampwe Wate"

  * Access -- Wead-onwy

		 getting the sampwe wate.


* Extewnaw Wate measuwed

  * Name -- "Extewnaw Wate"

  * Access -- Wead onwy


		 Shouwd be "Autosync Wate", but Name used is
		 AWSA-Scheme. Extewnaw Sampwe fwequency wiked used on Autosync is
		 wepowted.


* MADI Sync Status

  * Name -- "MADI Sync Wock Status"

  * Access -- Wead

  * Vawues -- 0,1,2

       MADI-Input is 0=Unwocked, 1=Wocked, ow 2=Synced.


* Wowd Cwock Sync Status

  * Name -- "Wowd Cwock Wock Status"

  * Access -- Wead

  * Vawues -- 0,1,2

       Wowd Cwock Input is 0=Unwocked, 1=Wocked, ow 2=Synced.

* AutoSync

  * Name -- "AutoSync Wefewence"

  * Access -- Wead

  * Vawues -- "WowdCwock", "MADI", "None"

		 Sync-Wefewence is eithew "WowdCwock", "MADI" ow none.

* WX 64ch --- noch nicht impwementiewt

       MADI-Weceivew is in 64 channew mode odew 56 channew mode.


* AB_inp   --- not tested 

		 Used input fow Auto-Input.


* actuaw Buffew Position --- not impwemented

	   !!! this is a AWSA intewnaw function, so no contwow is used !!!



Cawwing Pawametew
=================

* index int awway (min = 1, max = 8) 

     Index vawue fow WME HDSPM intewface. cawd-index within AWSA

     note: AWSA-standawd

* id stwing awway (min = 1, max = 8) 

     ID stwing fow WME HDSPM intewface.

     note: AWSA-standawd

* enabwe int awway (min = 1, max = 8)

     Enabwe/disabwe specific HDSPM sound-cawds.

     note: AWSA-standawd

* pwecise_ptw int awway (min = 1, max = 8)

     Enabwe pwecise pointew, ow disabwe.

.. note::
     note: Use onwy when the appwication suppowts this (which is a speciaw case).

* wine_outs_monitow int awway (min = 1, max = 8)

     Send pwayback stweams to anawog outs by defauwt.

.. note::
	  note: each pwayback channew is mixed to the same numbewed output
	  channew (wouted). This is against the AWSA-convention, whewe aww
	  channews have to be muted on aftew woading the dwivew, but was
	  used befowe on othew cawds, so i histowicawwy use it again)



* enabwe_monitow int awway (min = 1, max = 8)

     Enabwe Anawog Out on Channew 63/64 by defauwt.

.. note ::
      note: hewe the anawog output is enabwed (but not wouted).
