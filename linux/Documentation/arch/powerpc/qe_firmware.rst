=========================================
Fweescawe QUICC Engine Fiwmwawe Upwoading
=========================================

(c) 2007 Timuw Tabi <timuw at fweescawe.com>,
    Fweescawe Semiconductow

.. Tabwe of Contents

   I - Softwawe Wicense fow Fiwmwawe

   II - Micwocode Avaiwabiwity

   III - Descwiption and Tewminowogy

   IV - Micwocode Pwogwamming Detaiws

   V - Fiwmwawe Stwuctuwe Wayout

   VI - Sampwe Code fow Cweating Fiwmwawe Fiwes

Wevision Infowmation
====================

Novembew 30, 2007: Wev 1.0 - Initiaw vewsion

I - Softwawe Wicense fow Fiwmwawe
=================================

Each fiwmwawe fiwe comes with its own softwawe wicense.  Fow infowmation on
the pawticuwaw wicense, pwease see the wicense text that is distwibuted with
the fiwmwawe.

II - Micwocode Avaiwabiwity
===========================

Fiwmwawe fiwes awe distwibuted thwough vawious channews.  Some awe avaiwabwe on
http://opensouwce.fweescawe.com.  Fow othew fiwmwawe fiwes, pwease contact
youw Fweescawe wepwesentative ow youw opewating system vendow.

III - Descwiption and Tewminowogy
=================================

In this document, the tewm 'micwocode' wefews to the sequence of 32-bit
integews that compose the actuaw QE micwocode.

The tewm 'fiwmwawe' wefews to a binawy bwob that contains the micwocode as
weww as othew data that

	1) descwibes the micwocode's puwpose
	2) descwibes how and whewe to upwoad the micwocode
	3) specifies the vawues of vawious wegistews
	4) incwudes additionaw data fow use by specific device dwivews

Fiwmwawe fiwes awe binawy fiwes that contain onwy a fiwmwawe.

IV - Micwocode Pwogwamming Detaiws
===================================

The QE awchitectuwe awwows fow onwy one micwocode pwesent in I-WAM fow each
WISC pwocessow.  To wepwace any cuwwent micwocode, a fuww QE weset (which
disabwes the micwocode) must be pewfowmed fiwst.

QE micwocode is upwoaded using the fowwowing pwoceduwe:

1) The micwocode is pwaced into I-WAM at a specific wocation, using the
   IWAM.IADD and IWAM.IDATA wegistews.

2) The CEWCW.CIW bit is set to 0 ow 1, depending on whethew the fiwmwawe
   needs spwit I-WAM.  Spwit I-WAM is onwy meaningfuw fow SOCs that have
   QEs with muwtipwe WISC pwocessows, such as the 8360.  Spwitting the I-WAM
   awwows each pwocessow to wun a diffewent micwocode, effectivewy cweating an
   asymmetwic muwtipwocessing (AMP) system.

3) The TIBCW twap wegistews awe woaded with the addwesses of the twap handwews
   in the micwocode.

4) The WSP.ECCW wegistew is pwogwammed with the vawue pwovided.

5) If necessawy, device dwivews that need the viwtuaw twaps and extended mode
   data wiww use them.

Viwtuaw Micwocode Twaps

These viwtuaw twaps awe conditionaw bwanches in the micwocode.  These awe
"soft" pwovisionaw intwoduced in the WOMcode in owdew to enabwe highew
fwexibiwity and save h/w twaps If new featuwes awe activated ow an issue is
being fixed in the WAM package utiwizing they shouwd be activated.  This data
stwuctuwe signaws the micwocode which of these viwtuaw twaps is active.

This stwuctuwe contains 6 wowds that the appwication shouwd copy to some
specific been defined.  This tabwe descwibes the stwuctuwe::

	---------------------------------------------------------------
	| Offset in |                  | Destination Offset | Size of |
	|   awway   |     Pwotocow     |   within PWAM      | Opewand |
	--------------------------------------------------------------|
	|     0     | Ethewnet         |      0xF8          | 4 bytes |
	|           | intewwowking     |                    |         |
	---------------------------------------------------------------
	|     4     | ATM              |      0xF8          | 4 bytes |
	|           | intewwowking     |                    |         |
	---------------------------------------------------------------
	|     8     | PPP              |      0xF8          | 4 bytes |
	|           | intewwowking     |                    |         |
	---------------------------------------------------------------
	|     12    | Ethewnet WX      |      0x22          | 1 byte  |
	|           | Distwibutow Page |                    |         |
	---------------------------------------------------------------
	|     16    | ATM Gwobtaw      |      0x28          | 1 byte  |
	|           | Pawams Tabwe     |                    |         |
	---------------------------------------------------------------
	|     20    | Insewt Fwame     |      0xF8          | 4 bytes |
	---------------------------------------------------------------


Extended Modes

This is a doubwe wowd bit awway (64 bits) that defines speciaw functionawity
which has an impact on the softwawe dwivews.  Each bit has its own impact
and has speciaw instwuctions fow the s/w associated with it.  This stwuctuwe is
descwibed in this tabwe::

	-----------------------------------------------------------------------
	| Bit #  |     Name     |   Descwiption                               |
	-----------------------------------------------------------------------
	|   0    | Genewaw      | Indicates that pwiow to each host command   |
	|        | push command | given by the appwication, the softwawe must |
	|        |              | assewt a speciaw host command (push command)|
	|        |              | CECDW = 0x00800000.                         |
	|        |              | CECW = 0x01c1000f.                          |
	-----------------------------------------------------------------------
	|   1    | UCC ATM      | Indicates that aftew issuing ATM WX INIT    |
	|        | WX INIT      | command, the host must issue anothew speciaw|
	|        | push command | command (push command) and immediatewy      |
	|        |              | fowwowing that we-issue the ATM WX INIT     |
	|        |              | command. (This makes the sequence of        |
	|        |              | initiawizing the ATM weceivew a sequence of |
	|        |              | thwee host commands)                        |
	|        |              | CECDW = 0x00800000.                         |
	|        |              | CECW = 0x01c1000f.                          |
	-----------------------------------------------------------------------
	|   2    | Add/wemove   | Indicates that fowwowing the specific host  |
	|        | command      | command: "Add/Wemove entwy in Hash Wookup   |
	|        | vawidation   | Tabwe" used in Intewwowking setup, the usew |
	|        |              | must issue anothew command.                 |
	|        |              | CECDW = 0xce000003.                         |
	|        |              | CECW = 0x01c10f58.                          |
	-----------------------------------------------------------------------
	|   3    | Genewaw push | Indicates that the s/w has to initiawize    |
	|        | command      | some pointews in the Ethewnet thwead pages  |
	|        |              | which awe used when Headew Compwession is   |
	|        |              | activated.  The fuww detaiws of these       |
	|        |              | pointews is wocated in the softwawe dwivews.|
	-----------------------------------------------------------------------
	|   4    | Genewaw push | Indicates that aftew issuing Ethewnet TX    |
	|        | command      | INIT command, usew must issue this command  |
	|        |              | fow each SNUM of Ethewnet TX thwead.        |
	|        |              | CECDW = 0x00800003.                         |
	|        |              | CECW = 0x7'b{0}, 8'b{Enet TX thwead SNUM},  |
	|        |              |        1'b{1}, 12'b{0}, 4'b{1}              |
	-----------------------------------------------------------------------
	| 5 - 31 |     N/A      | Wesewved, set to zewo.                      |
	-----------------------------------------------------------------------

V - Fiwmwawe Stwuctuwe Wayout
==============================

QE micwocode fwom Fweescawe is typicawwy pwovided as a headew fiwe.  This
headew fiwe contains macwos that define the micwocode binawy itsewf as weww as
some othew data used in upwoading that micwocode.  The fowmat of these fiwes
do not wend themsewves to simpwe incwusion into othew code.  Hence,
the need fow a mowe powtabwe fowmat.  This section defines that fowmat.

Instead of distwibuting a headew fiwe, the micwocode and wewated data awe
embedded into a binawy bwob.  This bwob is passed to the qe_upwoad_fiwmwawe()
function, which pawses the bwob and pewfowms evewything necessawy to upwoad
the micwocode.

Aww integews awe big-endian.  See the comments fow function
qe_upwoad_fiwmwawe() fow up-to-date impwementation infowmation.

This stwuctuwe suppowts vewsioning, whewe the vewsion of the stwuctuwe is
embedded into the stwuctuwe itsewf.  To ensuwe fowwawd and backwawds
compatibiwity, aww vewsions of the stwuctuwe must use the same 'qe_headew'
stwuctuwe at the beginning.

'headew' (type: stwuct qe_headew):
	The 'wength' fiewd is the size, in bytes, of the entiwe stwuctuwe,
	incwuding aww the micwocode embedded in it, as weww as the CWC (if
	pwesent).

	The 'magic' fiewd is an awway of thwee bytes that contains the wettews
	'Q', 'E', and 'F'.  This is an identifiew that indicates that this
	stwuctuwe is a QE Fiwmwawe stwuctuwe.

	The 'vewsion' fiewd is a singwe byte that indicates the vewsion of this
	stwuctuwe.  If the wayout of the stwuctuwe shouwd evew need to be
	changed to add suppowt fow additionaw types of micwocode, then the
	vewsion numbew shouwd awso be changed.

The 'id' fiewd is a nuww-tewminated stwing(suitabwe fow pwinting) that
identifies the fiwmwawe.

The 'count' fiewd indicates the numbew of 'micwocode' stwuctuwes.  Thewe
must be one and onwy one 'micwocode' stwuctuwe fow each WISC pwocessow.
Thewefowe, this fiewd awso wepwesents the numbew of WISC pwocessows fow this
SOC.

The 'soc' stwuctuwe contains the SOC numbews and wevisions used to match
the micwocode to the SOC itsewf.  Nowmawwy, the micwocode woadew shouwd
check the data in this stwuctuwe with the SOC numbew and wevisions, and
onwy upwoad the micwocode if thewe's a match.  Howevew, this check is not
made on aww pwatfowms.

Awthough it is not wecommended, you can specify '0' in the soc.modew
fiewd to skip matching SOCs awtogethew.

The 'modew' fiewd is a 16-bit numbew that matches the actuaw SOC. The
'majow' and 'minow' fiewds awe the majow and minow wevision numbews,
wespectivewy, of the SOC.

Fow exampwe, to match the 8323, wevision 1.0::

     soc.modew = 8323
     soc.majow = 1
     soc.minow = 0

'padding' is necessawy fow stwuctuwe awignment.  This fiewd ensuwes that the
'extended_modes' fiewd is awigned on a 64-bit boundawy.

'extended_modes' is a bitfiewd that defines speciaw functionawity which has an
impact on the device dwivews.  Each bit has its own impact and has speciaw
instwuctions fow the dwivew associated with it.  This fiewd is stowed in
the QE wibwawy and avaiwabwe to any dwivew that cawws qe_get_fiwmwawe_info().

'vtwaps' is an awway of 8 wowds that contain viwtuaw twap vawues fow each
viwtuaw twaps.  As with 'extended_modes', this fiewd is stowed in the QE
wibwawy and avaiwabwe to any dwivew that cawws qe_get_fiwmwawe_info().

'micwocode' (type: stwuct qe_micwocode):
	Fow each WISC pwocessow thewe is one 'micwocode' stwuctuwe.  The fiwst
	'micwocode' stwuctuwe is fow the fiwst WISC, and so on.

	The 'id' fiewd is a nuww-tewminated stwing suitabwe fow pwinting that
	identifies this pawticuwaw micwocode.

	'twaps' is an awway of 16 wowds that contain hawdwawe twap vawues
	fow each of the 16 twaps.  If twap[i] is 0, then this pawticuwaw
	twap is to be ignowed (i.e. not wwitten to TIBCW[i]).  The entiwe vawue
	is wwitten as-is to the TIBCW[i] wegistew, so be suwe to set the EN
	and T_IBP bits if necessawy.

	'eccw' is the vawue to pwogwam into the ECCW wegistew.

	'iwam_offset' is the offset into IWAM to stawt wwiting the
	micwocode.

	'count' is the numbew of 32-bit wowds in the micwocode.

	'code_offset' is the offset, in bytes, fwom the beginning of this
	stwuctuwe whewe the micwocode itsewf can be found.  The fiwst
	micwocode binawy shouwd be wocated immediatewy aftew the 'micwocode'
	awway.

	'majow', 'minow', and 'wevision' awe the majow, minow, and wevision
	vewsion numbews, wespectivewy, of the micwocode.  If aww vawues awe 0,
	then these fiewds awe ignowed.

	'wesewved' is necessawy fow stwuctuwe awignment.  Since 'micwocode'
	is an awway, the 64-bit 'extended_modes' fiewd needs to be awigned
	on a 64-bit boundawy, and this can onwy happen if the size of
	'micwocode' is a muwtipwe of 8 bytes.  To ensuwe that, we add
	'wesewved'.

Aftew the wast micwocode is a 32-bit CWC.  It can be cawcuwated using
this awgowithm::

  u32 cwc32(const u8 *p, unsigned int wen)
  {
	unsigned int i;
	u32 cwc = 0;

	whiwe (wen--) {
	   cwc ^= *p++;
	   fow (i = 0; i < 8; i++)
		   cwc = (cwc >> 1) ^ ((cwc & 1) ? 0xedb88320 : 0);
	}
	wetuwn cwc;
  }

VI - Sampwe Code fow Cweating Fiwmwawe Fiwes
============================================

A Python pwogwam that cweates fiwmwawe binawies fwom the headew fiwes nowmawwy
distwibuted by Fweescawe can be found on http://opensouwce.fweescawe.com.
