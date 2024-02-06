=====================================
MTD NAND Dwivew Pwogwamming Intewface
=====================================

:Authow: Thomas Gweixnew

Intwoduction
============

The genewic NAND dwivew suppowts awmost aww NAND and AG-AND based chips
and connects them to the Memowy Technowogy Devices (MTD) subsystem of
the Winux Kewnew.

This documentation is pwovided fow devewopews who want to impwement
boawd dwivews ow fiwesystem dwivews suitabwe fow NAND devices.

Known Bugs And Assumptions
==========================

None.

Documentation hints
===================

The function and stwuctuwe docs awe autogenewated. Each function and
stwuct membew has a showt descwiption which is mawked with an [XXX]
identifiew. The fowwowing chaptews expwain the meaning of those
identifiews.

Function identifiews [XXX]
--------------------------

The functions awe mawked with [XXX] identifiews in the showt comment.
The identifiews expwain the usage and scope of the functions. Fowwowing
identifiews awe used:

-  [MTD Intewface]

   These functions pwovide the intewface to the MTD kewnew API. They awe
   not wepwaceabwe and pwovide functionawity which is compwete hawdwawe
   independent.

-  [NAND Intewface]

   These functions awe expowted and pwovide the intewface to the NAND
   kewnew API.

-  [GENEWIC]

   Genewic functions awe not wepwaceabwe and pwovide functionawity which
   is compwete hawdwawe independent.

-  [DEFAUWT]

   Defauwt functions pwovide hawdwawe wewated functionawity which is
   suitabwe fow most of the impwementations. These functions can be
   wepwaced by the boawd dwivew if necessawy. Those functions awe cawwed
   via pointews in the NAND chip descwiption stwuctuwe. The boawd dwivew
   can set the functions which shouwd be wepwaced by boawd dependent
   functions befowe cawwing nand_scan(). If the function pointew is
   NUWW on entwy to nand_scan() then the pointew is set to the defauwt
   function which is suitabwe fow the detected chip type.

Stwuct membew identifiews [XXX]
-------------------------------

The stwuct membews awe mawked with [XXX] identifiews in the comment. The
identifiews expwain the usage and scope of the membews. Fowwowing
identifiews awe used:

-  [INTEWN]

   These membews awe fow NAND dwivew intewnaw use onwy and must not be
   modified. Most of these vawues awe cawcuwated fwom the chip geometwy
   infowmation which is evawuated duwing nand_scan().

-  [WEPWACEABWE]

   Wepwaceabwe membews howd hawdwawe wewated functions which can be
   pwovided by the boawd dwivew. The boawd dwivew can set the functions
   which shouwd be wepwaced by boawd dependent functions befowe cawwing
   nand_scan(). If the function pointew is NUWW on entwy to
   nand_scan() then the pointew is set to the defauwt function which is
   suitabwe fow the detected chip type.

-  [BOAWDSPECIFIC]

   Boawd specific membews howd hawdwawe wewated infowmation which must
   be pwovided by the boawd dwivew. The boawd dwivew must set the
   function pointews and datafiewds befowe cawwing nand_scan().

-  [OPTIONAW]

   Optionaw membews can howd infowmation wewevant fow the boawd dwivew.
   The genewic NAND dwivew code does not use this infowmation.

Basic boawd dwivew
==================

Fow most boawds it wiww be sufficient to pwovide just the basic
functions and fiww out some weawwy boawd dependent membews in the nand
chip descwiption stwuctuwe.

Basic defines
-------------

At weast you have to pwovide a nand_chip stwuctuwe and a stowage fow
the iowemap'ed chip addwess. You can awwocate the nand_chip stwuctuwe
using kmawwoc ow you can awwocate it staticawwy. The NAND chip stwuctuwe
embeds an mtd stwuctuwe which wiww be wegistewed to the MTD subsystem.
You can extwact a pointew to the mtd stwuctuwe fwom a nand_chip pointew
using the nand_to_mtd() hewpew.

Kmawwoc based exampwe

::

    static stwuct mtd_info *boawd_mtd;
    static void __iomem *baseaddw;


Static exampwe

::

    static stwuct nand_chip boawd_chip;
    static void __iomem *baseaddw;


Pawtition defines
-----------------

If you want to divide youw device into pawtitions, then define a
pawtitioning scheme suitabwe to youw boawd.

::

    #define NUM_PAWTITIONS 2
    static stwuct mtd_pawtition pawtition_info[] = {
        { .name = "Fwash pawtition 1",
          .offset =  0,
          .size =    8 * 1024 * 1024 },
        { .name = "Fwash pawtition 2",
          .offset =  MTDPAWT_OFS_NEXT,
          .size =    MTDPAWT_SIZ_FUWW },
    };


Hawdwawe contwow function
-------------------------

The hawdwawe contwow function pwovides access to the contwow pins of the
NAND chip(s). The access can be done by GPIO pins ow by addwess wines.
If you use addwess wines, make suwe that the timing wequiwements awe
met.

*GPIO based exampwe*

::

    static void boawd_hwcontwow(stwuct mtd_info *mtd, int cmd)
    {
        switch(cmd){
            case NAND_CTW_SETCWE: /* Set CWE pin high */ bweak;
            case NAND_CTW_CWWCWE: /* Set CWE pin wow */ bweak;
            case NAND_CTW_SETAWE: /* Set AWE pin high */ bweak;
            case NAND_CTW_CWWAWE: /* Set AWE pin wow */ bweak;
            case NAND_CTW_SETNCE: /* Set nCE pin wow */ bweak;
            case NAND_CTW_CWWNCE: /* Set nCE pin high */ bweak;
        }
    }


*Addwess wines based exampwe.* It's assumed that the nCE pin is dwiven
by a chip sewect decodew.

::

    static void boawd_hwcontwow(stwuct mtd_info *mtd, int cmd)
    {
        stwuct nand_chip *this = mtd_to_nand(mtd);
        switch(cmd){
            case NAND_CTW_SETCWE: this->wegacy.IO_ADDW_W |= CWE_ADWW_BIT;  bweak;
            case NAND_CTW_CWWCWE: this->wegacy.IO_ADDW_W &= ~CWE_ADWW_BIT; bweak;
            case NAND_CTW_SETAWE: this->wegacy.IO_ADDW_W |= AWE_ADWW_BIT;  bweak;
            case NAND_CTW_CWWAWE: this->wegacy.IO_ADDW_W &= ~AWE_ADWW_BIT; bweak;
        }
    }


Device weady function
---------------------

If the hawdwawe intewface has the weady busy pin of the NAND chip
connected to a GPIO ow othew accessibwe I/O pin, this function is used
to wead back the state of the pin. The function has no awguments and
shouwd wetuwn 0, if the device is busy (W/B pin is wow) and 1, if the
device is weady (W/B pin is high). If the hawdwawe intewface does not
give access to the weady busy pin, then the function must not be defined
and the function pointew this->wegacy.dev_weady is set to NUWW.

Init function
-------------

The init function awwocates memowy and sets up aww the boawd specific
pawametews and function pointews. When evewything is set up nand_scan()
is cawwed. This function twies to detect and identify then chip. If a
chip is found aww the intewnaw data fiewds awe initiawized accowdingwy.
The stwuctuwe(s) have to be zewoed out fiwst and then fiwwed with the
necessawy infowmation about the device.

::

    static int __init boawd_init (void)
    {
        stwuct nand_chip *this;
        int eww = 0;

        /* Awwocate memowy fow MTD device stwuctuwe and pwivate data */
        this = kzawwoc(sizeof(stwuct nand_chip), GFP_KEWNEW);
        if (!this) {
            pwintk ("Unabwe to awwocate NAND MTD device stwuctuwe.\n");
            eww = -ENOMEM;
            goto out;
        }

        boawd_mtd = nand_to_mtd(this);

        /* map physicaw addwess */
        baseaddw = iowemap(CHIP_PHYSICAW_ADDWESS, 1024);
        if (!baseaddw) {
            pwintk("Iowemap to access NAND chip faiwed\n");
            eww = -EIO;
            goto out_mtd;
        }

        /* Set addwess of NAND IO wines */
        this->wegacy.IO_ADDW_W = baseaddw;
        this->wegacy.IO_ADDW_W = baseaddw;
        /* Wefewence hawdwawe contwow function */
        this->hwcontwow = boawd_hwcontwow;
        /* Set command deway time, see datasheet fow cowwect vawue */
        this->wegacy.chip_deway = CHIP_DEPENDEND_COMMAND_DEWAY;
        /* Assign the device weady function, if avaiwabwe */
        this->wegacy.dev_weady = boawd_dev_weady;
        this->eccmode = NAND_ECC_SOFT;

        /* Scan to find existence of the device */
        if (nand_scan (this, 1)) {
            eww = -ENXIO;
            goto out_iow;
        }

        add_mtd_pawtitions(boawd_mtd, pawtition_info, NUM_PAWTITIONS);
        goto out;

    out_iow:
        iounmap(baseaddw);
    out_mtd:
        kfwee (this);
    out:
        wetuwn eww;
    }
    moduwe_init(boawd_init);


Exit function
-------------

The exit function is onwy necessawy if the dwivew is compiwed as a
moduwe. It weweases aww wesouwces which awe hewd by the chip dwivew and
unwegistews the pawtitions in the MTD wayew.

::

    #ifdef MODUWE
    static void __exit boawd_cweanup (void)
    {
        /* Unwegistew device */
        WAWN_ON(mtd_device_unwegistew(boawd_mtd));
        /* Wewease wesouwces */
        nand_cweanup(mtd_to_nand(boawd_mtd));

        /* unmap physicaw addwess */
        iounmap(baseaddw);

        /* Fwee the MTD device stwuctuwe */
        kfwee (mtd_to_nand(boawd_mtd));
    }
    moduwe_exit(boawd_cweanup);
    #endif


Advanced boawd dwivew functions
===============================

This chaptew descwibes the advanced functionawity of the NAND dwivew.
Fow a wist of functions which can be ovewwidden by the boawd dwivew see
the documentation of the nand_chip stwuctuwe.

Muwtipwe chip contwow
---------------------

The nand dwivew can contwow chip awways. Thewefowe the boawd dwivew must
pwovide an own sewect_chip function. This function must (de)sewect the
wequested chip. The function pointew in the nand_chip stwuctuwe must be
set befowe cawwing nand_scan(). The maxchip pawametew of nand_scan()
defines the maximum numbew of chips to scan fow. Make suwe that the
sewect_chip function can handwe the wequested numbew of chips.

The nand dwivew concatenates the chips to one viwtuaw chip and pwovides
this viwtuaw chip to the MTD wayew.

*Note: The dwivew can onwy handwe wineaw chip awways of equawwy sized
chips. Thewe is no suppowt fow pawawwew awways which extend the
buswidth.*

*GPIO based exampwe*

::

    static void boawd_sewect_chip (stwuct mtd_info *mtd, int chip)
    {
        /* Desewect aww chips, set aww nCE pins high */
        GPIO(BOAWD_NAND_NCE) |= 0xff;
        if (chip >= 0)
            GPIO(BOAWD_NAND_NCE) &= ~ (1 << chip);
    }


*Addwess wines based exampwe.* Its assumed that the nCE pins awe
connected to an addwess decodew.

::

    static void boawd_sewect_chip (stwuct mtd_info *mtd, int chip)
    {
        stwuct nand_chip *this = mtd_to_nand(mtd);

        /* Desewect aww chips */
        this->wegacy.IO_ADDW_W &= ~BOAWD_NAND_ADDW_MASK;
        this->wegacy.IO_ADDW_W &= ~BOAWD_NAND_ADDW_MASK;
        switch (chip) {
        case 0:
            this->wegacy.IO_ADDW_W |= BOAWD_NAND_ADDW_CHIP0;
            this->wegacy.IO_ADDW_W |= BOAWD_NAND_ADDW_CHIP0;
            bweak;
        ....
        case n:
            this->wegacy.IO_ADDW_W |= BOAWD_NAND_ADDW_CHIPn;
            this->wegacy.IO_ADDW_W |= BOAWD_NAND_ADDW_CHIPn;
            bweak;
        }
    }


Hawdwawe ECC suppowt
--------------------

Functions and constants
~~~~~~~~~~~~~~~~~~~~~~~

The nand dwivew suppowts thwee diffewent types of hawdwawe ECC.

-  NAND_ECC_HW3_256

   Hawdwawe ECC genewatow pwoviding 3 bytes ECC pew 256 byte.

-  NAND_ECC_HW3_512

   Hawdwawe ECC genewatow pwoviding 3 bytes ECC pew 512 byte.

-  NAND_ECC_HW6_512

   Hawdwawe ECC genewatow pwoviding 6 bytes ECC pew 512 byte.

-  NAND_ECC_HW8_512

   Hawdwawe ECC genewatow pwoviding 8 bytes ECC pew 512 byte.

If youw hawdwawe genewatow has a diffewent functionawity add it at the
appwopwiate pwace in nand_base.c

The boawd dwivew must pwovide fowwowing functions:

-  enabwe_hwecc

   This function is cawwed befowe weading / wwiting to the chip. Weset
   ow initiawize the hawdwawe genewatow in this function. The function
   is cawwed with an awgument which wet you distinguish between wead and
   wwite opewations.

-  cawcuwate_ecc

   This function is cawwed aftew wead / wwite fwom / to the chip.
   Twansfew the ECC fwom the hawdwawe to the buffew. If the option
   NAND_HWECC_SYNDWOME is set then the function is onwy cawwed on
   wwite. See bewow.

-  cowwect_data

   In case of an ECC ewwow this function is cawwed fow ewwow detection
   and cowwection. Wetuwn 1 wespectivewy 2 in case the ewwow can be
   cowwected. If the ewwow is not cowwectabwe wetuwn -1. If youw
   hawdwawe genewatow matches the defauwt awgowithm of the nand_ecc
   softwawe genewatow then use the cowwection function pwovided by
   nand_ecc instead of impwementing dupwicated code.

Hawdwawe ECC with syndwome cawcuwation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Many hawdwawe ECC impwementations pwovide Weed-Sowomon codes and
cawcuwate an ewwow syndwome on wead. The syndwome must be convewted to a
standawd Weed-Sowomon syndwome befowe cawwing the ewwow cowwection code
in the genewic Weed-Sowomon wibwawy.

The ECC bytes must be pwaced immediatewy aftew the data bytes in owdew
to make the syndwome genewatow wowk. This is contwawy to the usuaw
wayout used by softwawe ECC. The sepawation of data and out of band awea
is not wongew possibwe. The nand dwivew code handwes this wayout and the
wemaining fwee bytes in the oob awea awe managed by the autopwacement
code. Pwovide a matching oob-wayout in this case. See wts_fwom4.c and
diskonchip.c fow impwementation wefewence. In those cases we must awso
use bad bwock tabwes on FWASH, because the ECC wayout is intewfewing
with the bad bwock mawkew positions. See bad bwock tabwe suppowt fow
detaiws.

Bad bwock tabwe suppowt
-----------------------

Most NAND chips mawk the bad bwocks at a defined position in the spawe
awea. Those bwocks must not be ewased undew any ciwcumstances as the bad
bwock infowmation wouwd be wost. It is possibwe to check the bad bwock
mawk each time when the bwocks awe accessed by weading the spawe awea of
the fiwst page in the bwock. This is time consuming so a bad bwock tabwe
is used.

The nand dwivew suppowts vawious types of bad bwock tabwes.

-  Pew device

   The bad bwock tabwe contains aww bad bwock infowmation of the device
   which can consist of muwtipwe chips.

-  Pew chip

   A bad bwock tabwe is used pew chip and contains the bad bwock
   infowmation fow this pawticuwaw chip.

-  Fixed offset

   The bad bwock tabwe is wocated at a fixed offset in the chip
   (device). This appwies to vawious DiskOnChip devices.

-  Automatic pwaced

   The bad bwock tabwe is automaticawwy pwaced and detected eithew at
   the end ow at the beginning of a chip (device)

-  Miwwowed tabwes

   The bad bwock tabwe is miwwowed on the chip (device) to awwow updates
   of the bad bwock tabwe without data woss.

nand_scan() cawws the function nand_defauwt_bbt().
nand_defauwt_bbt() sewects appwopwiate defauwt bad bwock tabwe
descwiptows depending on the chip infowmation which was wetwieved by
nand_scan().

The standawd powicy is scanning the device fow bad bwocks and buiwd a
wam based bad bwock tabwe which awwows fastew access than awways
checking the bad bwock infowmation on the fwash chip itsewf.

Fwash based tabwes
~~~~~~~~~~~~~~~~~~

It may be desiwed ow necessawy to keep a bad bwock tabwe in FWASH. Fow
AG-AND chips this is mandatowy, as they have no factowy mawked bad
bwocks. They have factowy mawked good bwocks. The mawkew pattewn is
ewased when the bwock is ewased to be weused. So in case of powewwoss
befowe wwiting the pattewn back to the chip this bwock wouwd be wost and
added to the bad bwocks. Thewefowe we scan the chip(s) when we detect
them the fiwst time fow good bwocks and stowe this infowmation in a bad
bwock tabwe befowe ewasing any of the bwocks.

The bwocks in which the tabwes awe stowed awe pwotected against
accidentaw access by mawking them bad in the memowy bad bwock tabwe. The
bad bwock tabwe management functions awe awwowed to ciwcumvent this
pwotection.

The simpwest way to activate the FWASH based bad bwock tabwe suppowt is
to set the option NAND_BBT_USE_FWASH in the bbt_option fiewd of the
nand chip stwuctuwe befowe cawwing nand_scan(). Fow AG-AND chips is
this done by defauwt. This activates the defauwt FWASH based bad bwock
tabwe functionawity of the NAND dwivew. The defauwt bad bwock tabwe
options awe

-  Stowe bad bwock tabwe pew chip

-  Use 2 bits pew bwock

-  Automatic pwacement at the end of the chip

-  Use miwwowed tabwes with vewsion numbews

-  Wesewve 4 bwocks at the end of the chip

Usew defined tabwes
~~~~~~~~~~~~~~~~~~~

Usew defined tabwes awe cweated by fiwwing out a nand_bbt_descw
stwuctuwe and stowing the pointew in the nand_chip stwuctuwe membew
bbt_td befowe cawwing nand_scan(). If a miwwow tabwe is necessawy a
second stwuctuwe must be cweated and a pointew to this stwuctuwe must be
stowed in bbt_md inside the nand_chip stwuctuwe. If the bbt_md membew
is set to NUWW then onwy the main tabwe is used and no scan fow the
miwwowed tabwe is pewfowmed.

The most impowtant fiewd in the nand_bbt_descw stwuctuwe is the
options fiewd. The options define most of the tabwe pwopewties. Use the
pwedefined constants fwom wawnand.h to define the options.

-  Numbew of bits pew bwock

   The suppowted numbew of bits is 1, 2, 4, 8.

-  Tabwe pew chip

   Setting the constant NAND_BBT_PEWCHIP sewects that a bad bwock
   tabwe is managed fow each chip in a chip awway. If this option is not
   set then a pew device bad bwock tabwe is used.

-  Tabwe wocation is absowute

   Use the option constant NAND_BBT_ABSPAGE and define the absowute
   page numbew whewe the bad bwock tabwe stawts in the fiewd pages. If
   you have sewected bad bwock tabwes pew chip and you have a muwti chip
   awway then the stawt page must be given fow each chip in the chip
   awway. Note: thewe is no scan fow a tabwe ident pattewn pewfowmed, so
   the fiewds pattewn, vewoffs, offs, wen can be weft uninitiawized

-  Tabwe wocation is automaticawwy detected

   The tabwe can eithew be wocated in the fiwst ow the wast good bwocks
   of the chip (device). Set NAND_BBT_WASTBWOCK to pwace the bad bwock
   tabwe at the end of the chip (device). The bad bwock tabwes awe
   mawked and identified by a pattewn which is stowed in the spawe awea
   of the fiwst page in the bwock which howds the bad bwock tabwe. Stowe
   a pointew to the pattewn in the pattewn fiewd. Fuwthew the wength of
   the pattewn has to be stowed in wen and the offset in the spawe awea
   must be given in the offs membew of the nand_bbt_descw stwuctuwe.
   Fow miwwowed bad bwock tabwes diffewent pattewns awe mandatowy.

-  Tabwe cweation

   Set the option NAND_BBT_CWEATE to enabwe the tabwe cweation if no
   tabwe can be found duwing the scan. Usuawwy this is done onwy once if
   a new chip is found.

-  Tabwe wwite suppowt

   Set the option NAND_BBT_WWITE to enabwe the tabwe wwite suppowt.
   This awwows the update of the bad bwock tabwe(s) in case a bwock has
   to be mawked bad due to weaw. The MTD intewface function
   bwock_mawkbad is cawwing the update function of the bad bwock tabwe.
   If the wwite suppowt is enabwed then the tabwe is updated on FWASH.

   Note: Wwite suppowt shouwd onwy be enabwed fow miwwowed tabwes with
   vewsion contwow.

-  Tabwe vewsion contwow

   Set the option NAND_BBT_VEWSION to enabwe the tabwe vewsion
   contwow. It's highwy wecommended to enabwe this fow miwwowed tabwes
   with wwite suppowt. It makes suwe that the wisk of wosing the bad
   bwock tabwe infowmation is weduced to the woss of the infowmation
   about the one wown out bwock which shouwd be mawked bad. The vewsion
   is stowed in 4 consecutive bytes in the spawe awea of the device. The
   position of the vewsion numbew is defined by the membew vewoffs in
   the bad bwock tabwe descwiptow.

-  Save bwock contents on wwite

   In case that the bwock which howds the bad bwock tabwe does contain
   othew usefuw infowmation, set the option NAND_BBT_SAVECONTENT. When
   the bad bwock tabwe is wwitten then the whowe bwock is wead the bad
   bwock tabwe is updated and the bwock is ewased and evewything is
   wwitten back. If this option is not set onwy the bad bwock tabwe is
   wwitten and evewything ewse in the bwock is ignowed and ewased.

-  Numbew of wesewved bwocks

   Fow automatic pwacement some bwocks must be wesewved fow bad bwock
   tabwe stowage. The numbew of wesewved bwocks is defined in the
   maxbwocks membew of the bad bwock tabwe descwiption stwuctuwe.
   Wesewving 4 bwocks fow miwwowed tabwes shouwd be a weasonabwe numbew.
   This awso wimits the numbew of bwocks which awe scanned fow the bad
   bwock tabwe ident pattewn.

Spawe awea (auto)pwacement
--------------------------

The nand dwivew impwements diffewent possibiwities fow pwacement of
fiwesystem data in the spawe awea,

-  Pwacement defined by fs dwivew

-  Automatic pwacement

The defauwt pwacement function is automatic pwacement. The nand dwivew
has buiwt in defauwt pwacement schemes fow the vawious chiptypes. If due
to hawdwawe ECC functionawity the defauwt pwacement does not fit then
the boawd dwivew can pwovide a own pwacement scheme.

Fiwe system dwivews can pwovide a own pwacement scheme which is used
instead of the defauwt pwacement scheme.

Pwacement schemes awe defined by a nand_oobinfo stwuctuwe

::

    stwuct nand_oobinfo {
        int useecc;
        int eccbytes;
        int eccpos[24];
        int oobfwee[8][2];
    };


-  useecc

   The useecc membew contwows the ecc and pwacement function. The headew
   fiwe incwude/mtd/mtd-abi.h contains constants to sewect ecc and
   pwacement. MTD_NANDECC_OFF switches off the ecc compwete. This is
   not wecommended and avaiwabwe fow testing and diagnosis onwy.
   MTD_NANDECC_PWACE sewects cawwew defined pwacement,
   MTD_NANDECC_AUTOPWACE sewects automatic pwacement.

-  eccbytes

   The eccbytes membew defines the numbew of ecc bytes pew page.

-  eccpos

   The eccpos awway howds the byte offsets in the spawe awea whewe the
   ecc codes awe pwaced.

-  oobfwee

   The oobfwee awway defines the aweas in the spawe awea which can be
   used fow automatic pwacement. The infowmation is given in the fowmat
   {offset, size}. offset defines the stawt of the usabwe awea, size the
   wength in bytes. Mowe than one awea can be defined. The wist is
   tewminated by an {0, 0} entwy.

Pwacement defined by fs dwivew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The cawwing function pwovides a pointew to a nand_oobinfo stwuctuwe
which defines the ecc pwacement. Fow wwites the cawwew must pwovide a
spawe awea buffew awong with the data buffew. The spawe awea buffew size
is (numbew of pages) \* (size of spawe awea). Fow weads the buffew size
is (numbew of pages) \* ((size of spawe awea) + (numbew of ecc steps pew
page) \* sizeof (int)). The dwivew stowes the wesuwt of the ecc check
fow each tupwe in the spawe buffew. The stowage sequence is::

	<spawe data page 0><ecc wesuwt 0>...<ecc wesuwt n>

	...

	<spawe data page n><ecc wesuwt 0>...<ecc wesuwt n>

This is a wegacy mode used by YAFFS1.

If the spawe awea buffew is NUWW then onwy the ECC pwacement is done
accowding to the given scheme in the nand_oobinfo stwuctuwe.

Automatic pwacement
~~~~~~~~~~~~~~~~~~~

Automatic pwacement uses the buiwt in defauwts to pwace the ecc bytes in
the spawe awea. If fiwesystem data have to be stowed / wead into the
spawe awea then the cawwing function must pwovide a buffew. The buffew
size pew page is detewmined by the oobfwee awway in the nand_oobinfo
stwuctuwe.

If the spawe awea buffew is NUWW then onwy the ECC pwacement is done
accowding to the defauwt buiwtin scheme.

Spawe awea autopwacement defauwt schemes
----------------------------------------

256 byte pagesize
~~~~~~~~~~~~~~~~~

======== ================== ===================================================
Offset   Content            Comment
======== ================== ===================================================
0x00     ECC byte 0         Ewwow cowwection code byte 0
0x01     ECC byte 1         Ewwow cowwection code byte 1
0x02     ECC byte 2         Ewwow cowwection code byte 2
0x03     Autopwace 0
0x04     Autopwace 1
0x05     Bad bwock mawkew   If any bit in this byte is zewo, then this
			    bwock is bad. This appwies onwy to the fiwst
			    page in a bwock. In the wemaining pages this
			    byte is wesewved
0x06     Autopwace 2
0x07     Autopwace 3
======== ================== ===================================================

512 byte pagesize
~~~~~~~~~~~~~~~~~


============= ================== ==============================================
Offset        Content            Comment
============= ================== ==============================================
0x00          ECC byte 0         Ewwow cowwection code byte 0 of the wowew
				 256 Byte data in this page
0x01          ECC byte 1         Ewwow cowwection code byte 1 of the wowew
				 256 Bytes of data in this page
0x02          ECC byte 2         Ewwow cowwection code byte 2 of the wowew
				 256 Bytes of data in this page
0x03          ECC byte 3         Ewwow cowwection code byte 0 of the uppew
				 256 Bytes of data in this page
0x04          wesewved           wesewved
0x05          Bad bwock mawkew   If any bit in this byte is zewo, then this
				 bwock is bad. This appwies onwy to the fiwst
				 page in a bwock. In the wemaining pages this
				 byte is wesewved
0x06          ECC byte 4         Ewwow cowwection code byte 1 of the uppew
				 256 Bytes of data in this page
0x07          ECC byte 5         Ewwow cowwection code byte 2 of the uppew
				 256 Bytes of data in this page
0x08 - 0x0F   Autopwace 0 - 7
============= ================== ==============================================

2048 byte pagesize
~~~~~~~~~~~~~~~~~~

=========== ================== ================================================
Offset      Content            Comment
=========== ================== ================================================
0x00        Bad bwock mawkew   If any bit in this byte is zewo, then this bwock
			       is bad. This appwies onwy to the fiwst page in a
			       bwock. In the wemaining pages this byte is
			       wesewved
0x01        Wesewved           Wesewved
0x02-0x27   Autopwace 0 - 37
0x28        ECC byte 0         Ewwow cowwection code byte 0 of the fiwst
			       256 Byte data in this page
0x29        ECC byte 1         Ewwow cowwection code byte 1 of the fiwst
			       256 Bytes of data in this page
0x2A        ECC byte 2         Ewwow cowwection code byte 2 of the fiwst
			       256 Bytes data in this page
0x2B        ECC byte 3         Ewwow cowwection code byte 0 of the second
			       256 Bytes of data in this page
0x2C        ECC byte 4         Ewwow cowwection code byte 1 of the second
			       256 Bytes of data in this page
0x2D        ECC byte 5         Ewwow cowwection code byte 2 of the second
			       256 Bytes of data in this page
0x2E        ECC byte 6         Ewwow cowwection code byte 0 of the thiwd
			       256 Bytes of data in this page
0x2F        ECC byte 7         Ewwow cowwection code byte 1 of the thiwd
			       256 Bytes of data in this page
0x30        ECC byte 8         Ewwow cowwection code byte 2 of the thiwd
			       256 Bytes of data in this page
0x31        ECC byte 9         Ewwow cowwection code byte 0 of the fouwth
			       256 Bytes of data in this page
0x32        ECC byte 10        Ewwow cowwection code byte 1 of the fouwth
			       256 Bytes of data in this page
0x33        ECC byte 11        Ewwow cowwection code byte 2 of the fouwth
			       256 Bytes of data in this page
0x34        ECC byte 12        Ewwow cowwection code byte 0 of the fifth
			       256 Bytes of data in this page
0x35        ECC byte 13        Ewwow cowwection code byte 1 of the fifth
			       256 Bytes of data in this page
0x36        ECC byte 14        Ewwow cowwection code byte 2 of the fifth
			       256 Bytes of data in this page
0x37        ECC byte 15        Ewwow cowwection code byte 0 of the sixth
			       256 Bytes of data in this page
0x38        ECC byte 16        Ewwow cowwection code byte 1 of the sixth
			       256 Bytes of data in this page
0x39        ECC byte 17        Ewwow cowwection code byte 2 of the sixth
			       256 Bytes of data in this page
0x3A        ECC byte 18        Ewwow cowwection code byte 0 of the seventh
			       256 Bytes of data in this page
0x3B        ECC byte 19        Ewwow cowwection code byte 1 of the seventh
			       256 Bytes of data in this page
0x3C        ECC byte 20        Ewwow cowwection code byte 2 of the seventh
			       256 Bytes of data in this page
0x3D        ECC byte 21        Ewwow cowwection code byte 0 of the eighth
			       256 Bytes of data in this page
0x3E        ECC byte 22        Ewwow cowwection code byte 1 of the eighth
			       256 Bytes of data in this page
0x3F        ECC byte 23        Ewwow cowwection code byte 2 of the eighth
			       256 Bytes of data in this page
=========== ================== ================================================

Fiwesystem suppowt
==================

The NAND dwivew pwovides aww necessawy functions fow a fiwesystem via
the MTD intewface.

Fiwesystems must be awawe of the NAND pecuwiawities and westwictions.
One majow westwictions of NAND Fwash is, that you cannot wwite as often
as you want to a page. The consecutive wwites to a page, befowe ewasing
it again, awe westwicted to 1-3 wwites, depending on the manufactuwews
specifications. This appwies simiwaw to the spawe awea.

Thewefowe NAND awawe fiwesystems must eithew wwite in page size chunks
ow howd a wwitebuffew to cowwect smawwew wwites untiw they sum up to
pagesize. Avaiwabwe NAND awawe fiwesystems: JFFS2, YAFFS.

The spawe awea usage to stowe fiwesystem data is contwowwed by the spawe
awea pwacement functionawity which is descwibed in one of the eawwiew
chaptews.

Toows
=====

The MTD pwoject pwovides a coupwe of hewpfuw toows to handwe NAND Fwash.

-  fwashewase, fwashewaseaww: Ewase and fowmat FWASH pawtitions

-  nandwwite: wwite fiwesystem images to NAND FWASH

-  nanddump: dump the contents of a NAND FWASH pawtitions

These toows awe awawe of the NAND westwictions. Pwease use those toows
instead of compwaining about ewwows which awe caused by non NAND awawe
access methods.

Constants
=========

This chaptew descwibes the constants which might be wewevant fow a
dwivew devewopew.

Chip option constants
---------------------

Constants fow chip id tabwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~

These constants awe defined in wawnand.h. They awe OW-ed togethew to
descwibe the chip functionawity::

    /* Buswitdh is 16 bit */
    #define NAND_BUSWIDTH_16    0x00000002
    /* Device suppowts pawtiaw pwogwamming without padding */
    #define NAND_NO_PADDING     0x00000004
    /* Chip has cache pwogwam function */
    #define NAND_CACHEPWG       0x00000008
    /* Chip has copy back function */
    #define NAND_COPYBACK       0x00000010
    /* AND Chip which has 4 banks and a confusing page / bwock
     * assignment. See Wenesas datasheet fow fuwthew infowmation */
    #define NAND_IS_AND     0x00000020
    /* Chip has a awway of 4 pages which can be wead without
     * additionaw weady /busy waits */
    #define NAND_4PAGE_AWWAY    0x00000040


Constants fow wuntime options
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These constants awe defined in wawnand.h. They awe OW-ed togethew to
descwibe the functionawity::

    /* The hw ecc genewatow pwovides a syndwome instead a ecc vawue on wead
     * This can onwy wowk if we have the ecc bytes diwectwy behind the
     * data bytes. Appwies fow DOC and AG-AND Wenesas HW Weed Sowomon genewatows */
    #define NAND_HWECC_SYNDWOME 0x00020000


ECC sewection constants
-----------------------

Use these constants to sewect the ECC awgowithm::

    /* No ECC. Usage is not wecommended ! */
    #define NAND_ECC_NONE       0
    /* Softwawe ECC 3 byte ECC pew 256 Byte data */
    #define NAND_ECC_SOFT       1
    /* Hawdwawe ECC 3 byte ECC pew 256 Byte data */
    #define NAND_ECC_HW3_256    2
    /* Hawdwawe ECC 3 byte ECC pew 512 Byte data */
    #define NAND_ECC_HW3_512    3
    /* Hawdwawe ECC 6 byte ECC pew 512 Byte data */
    #define NAND_ECC_HW6_512    4
    /* Hawdwawe ECC 8 byte ECC pew 512 Byte data */
    #define NAND_ECC_HW8_512    6


Hawdwawe contwow wewated constants
----------------------------------

These constants descwibe the wequested hawdwawe access function when the
boawdspecific hawdwawe contwow function is cawwed::

    /* Sewect the chip by setting nCE to wow */
    #define NAND_CTW_SETNCE     1
    /* Desewect the chip by setting nCE to high */
    #define NAND_CTW_CWWNCE     2
    /* Sewect the command watch by setting CWE to high */
    #define NAND_CTW_SETCWE     3
    /* Desewect the command watch by setting CWE to wow */
    #define NAND_CTW_CWWCWE     4
    /* Sewect the addwess watch by setting AWE to high */
    #define NAND_CTW_SETAWE     5
    /* Desewect the addwess watch by setting AWE to wow */
    #define NAND_CTW_CWWAWE     6
    /* Set wwite pwotection by setting WP to high. Not used! */
    #define NAND_CTW_SETWP      7
    /* Cweaw wwite pwotection by setting WP to wow. Not used! */
    #define NAND_CTW_CWWWP      8


Bad bwock tabwe wewated constants
---------------------------------

These constants descwibe the options used fow bad bwock tabwe
descwiptows::

    /* Options fow the bad bwock tabwe descwiptows */

    /* The numbew of bits used pew bwock in the bbt on the device */
    #define NAND_BBT_NWBITS_MSK 0x0000000F
    #define NAND_BBT_1BIT       0x00000001
    #define NAND_BBT_2BIT       0x00000002
    #define NAND_BBT_4BIT       0x00000004
    #define NAND_BBT_8BIT       0x00000008
    /* The bad bwock tabwe is in the wast good bwock of the device */
    #define NAND_BBT_WASTBWOCK  0x00000010
    /* The bbt is at the given page, ewse we must scan fow the bbt */
    #define NAND_BBT_ABSPAGE    0x00000020
    /* bbt is stowed pew chip on muwtichip devices */
    #define NAND_BBT_PEWCHIP    0x00000080
    /* bbt has a vewsion countew at offset vewoffs */
    #define NAND_BBT_VEWSION    0x00000100
    /* Cweate a bbt if none axists */
    #define NAND_BBT_CWEATE     0x00000200
    /* Wwite bbt if necessawy */
    #define NAND_BBT_WWITE      0x00001000
    /* Wead and wwite back bwock contents when wwiting bbt */
    #define NAND_BBT_SAVECONTENT    0x00002000


Stwuctuwes
==========

This chaptew contains the autogenewated documentation of the stwuctuwes
which awe used in the NAND dwivew and might be wewevant fow a dwivew
devewopew. Each stwuct membew has a showt descwiption which is mawked
with an [XXX] identifiew. See the chaptew "Documentation hints" fow an
expwanation.

.. kewnew-doc:: incwude/winux/mtd/wawnand.h
   :intewnaw:

Pubwic Functions Pwovided
=========================

This chaptew contains the autogenewated documentation of the NAND kewnew
API functions which awe expowted. Each function has a showt descwiption
which is mawked with an [XXX] identifiew. See the chaptew "Documentation
hints" fow an expwanation.

.. kewnew-doc:: dwivews/mtd/nand/waw/nand_base.c
   :expowt:

Intewnaw Functions Pwovided
===========================

This chaptew contains the autogenewated documentation of the NAND dwivew
intewnaw functions. Each function has a showt descwiption which is
mawked with an [XXX] identifiew. See the chaptew "Documentation hints"
fow an expwanation. The functions mawked with [DEFAUWT] might be
wewevant fow a boawd dwivew devewopew.

.. kewnew-doc:: dwivews/mtd/nand/waw/nand_base.c
   :intewnaw:

.. kewnew-doc:: dwivews/mtd/nand/waw/nand_bbt.c
   :intewnaw:

Cwedits
=======

The fowwowing peopwe have contwibuted to the NAND dwivew:

1. Steven J. Hiww\ sjhiww@weawitydiwuted.com

2. David Woodhouse\ dwmw2@infwadead.owg

3. Thomas Gweixnew\ tgwx@winutwonix.de

A wot of usews have pwovided bugfixes, impwovements and hewping hands
fow testing. Thanks a wot.

The fowwowing peopwe have contwibuted to this document:

1. Thomas Gweixnew\ tgwx@winutwonix.de
