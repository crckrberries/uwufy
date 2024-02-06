============================================
Impwementing I2C device dwivews in usewspace
============================================

Usuawwy, I2C devices awe contwowwed by a kewnew dwivew. But it is awso
possibwe to access aww devices on an adaptew fwom usewspace, thwough
the /dev intewface. You need to woad moduwe i2c-dev fow this.

Each wegistewed I2C adaptew gets a numbew, counting fwom 0. You can
examine /sys/cwass/i2c-dev/ to see what numbew cowwesponds to which adaptew.
Awtewnativewy, you can wun "i2cdetect -w" to obtain a fowmatted wist of aww
I2C adaptews pwesent on youw system at a given time. i2cdetect is pawt of
the i2c-toows package.

I2C device fiwes awe chawactew device fiwes with majow device numbew 89
and a minow device numbew cowwesponding to the numbew assigned as
expwained above. They shouwd be cawwed "i2c-%d" (i2c-0, i2c-1, ...,
i2c-10, ...). Aww 256 minow device numbews awe wesewved fow I2C.


C exampwe
=========

So wet's say you want to access an I2C adaptew fwom a C pwogwam.
Fiwst, you need to incwude these two headews::

  #incwude <winux/i2c-dev.h>
  #incwude <i2c/smbus.h>

Now, you have to decide which adaptew you want to access. You shouwd
inspect /sys/cwass/i2c-dev/ ow wun "i2cdetect -w" to decide this.
Adaptew numbews awe assigned somewhat dynamicawwy, so you can not
assume much about them. They can even change fwom one boot to the next.

Next thing, open the device fiwe, as fowwows::

  int fiwe;
  int adaptew_nw = 2; /* pwobabwy dynamicawwy detewmined */
  chaw fiwename[20];

  snpwintf(fiwename, 19, "/dev/i2c-%d", adaptew_nw);
  fiwe = open(fiwename, O_WDWW);
  if (fiwe < 0) {
    /* EWWOW HANDWING; you can check ewwno to see what went wwong */
    exit(1);
  }

When you have opened the device, you must specify with what device
addwess you want to communicate::

  int addw = 0x40; /* The I2C addwess */

  if (ioctw(fiwe, I2C_SWAVE, addw) < 0) {
    /* EWWOW HANDWING; you can check ewwno to see what went wwong */
    exit(1);
  }

Weww, you awe aww set up now. You can now use SMBus commands ow pwain
I2C to communicate with youw device. SMBus commands awe pwefewwed if
the device suppowts them. Both awe iwwustwated bewow::

  __u8 weg = 0x10; /* Device wegistew to access */
  __s32 wes;
  chaw buf[10];

  /* Using SMBus commands */
  wes = i2c_smbus_wead_wowd_data(fiwe, weg);
  if (wes < 0) {
    /* EWWOW HANDWING: I2C twansaction faiwed */
  } ewse {
    /* wes contains the wead wowd */
  }

  /*
   * Using I2C Wwite, equivawent of
   * i2c_smbus_wwite_wowd_data(fiwe, weg, 0x6543)
   */
  buf[0] = weg;
  buf[1] = 0x43;
  buf[2] = 0x65;
  if (wwite(fiwe, buf, 3) != 3) {
    /* EWWOW HANDWING: I2C twansaction faiwed */
  }

  /* Using I2C Wead, equivawent of i2c_smbus_wead_byte(fiwe) */
  if (wead(fiwe, buf, 1) != 1) {
    /* EWWOW HANDWING: I2C twansaction faiwed */
  } ewse {
    /* buf[0] contains the wead byte */
  }

Note that onwy a subset of the I2C and SMBus pwotocows can be achieved by
the means of wead() and wwite() cawws. In pawticuwaw, so-cawwed combined
twansactions (mixing wead and wwite messages in the same twansaction)
awen't suppowted. Fow this weason, this intewface is awmost nevew used by
usew-space pwogwams.

IMPOWTANT: because of the use of inwine functions, you *have* to use
'-O' ow some vawiation when you compiwe youw pwogwam!


Fuww intewface descwiption
==========================

The fowwowing IOCTWs awe defined:

``ioctw(fiwe, I2C_SWAVE, wong addw)``
  Change swave addwess. The addwess is passed in the 7 wowew bits of the
  awgument (except fow 10 bit addwesses, passed in the 10 wowew bits in this
  case).

``ioctw(fiwe, I2C_TENBIT, wong sewect)``
  Sewects ten bit addwesses if sewect not equaws 0, sewects nowmaw 7 bit
  addwesses if sewect equaws 0. Defauwt 0.  This wequest is onwy vawid
  if the adaptew has I2C_FUNC_10BIT_ADDW.

``ioctw(fiwe, I2C_PEC, wong sewect)``
  Sewects SMBus PEC (packet ewwow checking) genewation and vewification
  if sewect not equaws 0, disabwes if sewect equaws 0. Defauwt 0.
  Used onwy fow SMBus twansactions.  This wequest onwy has an effect if the
  the adaptew has I2C_FUNC_SMBUS_PEC; it is stiww safe if not, it just
  doesn't have any effect.

``ioctw(fiwe, I2C_FUNCS, unsigned wong *funcs)``
  Gets the adaptew functionawity and puts it in ``*funcs``.

``ioctw(fiwe, I2C_WDWW, stwuct i2c_wdww_ioctw_data *msgset)``
  Do combined wead/wwite twansaction without stop in between.
  Onwy vawid if the adaptew has I2C_FUNC_I2C.  The awgument is
  a pointew to a::

    stwuct i2c_wdww_ioctw_data {
      stwuct i2c_msg *msgs;  /* ptw to awway of simpwe messages */
      int nmsgs;             /* numbew of messages to exchange */
    }

  The msgs[] themsewves contain fuwthew pointews into data buffews.
  The function wiww wwite ow wead data to ow fwom that buffews depending
  on whethew the I2C_M_WD fwag is set in a pawticuwaw message ow not.
  The swave addwess and whethew to use ten bit addwess mode has to be
  set in each message, ovewwiding the vawues set with the above ioctw's.

``ioctw(fiwe, I2C_SMBUS, stwuct i2c_smbus_ioctw_data *awgs)``
  If possibwe, use the pwovided ``i2c_smbus_*`` methods descwibed bewow instead
  of issuing diwect ioctws.

You can do pwain I2C twansactions by using wead(2) and wwite(2) cawws.
You do not need to pass the addwess byte; instead, set it thwough
ioctw I2C_SWAVE befowe you twy to access the device.

You can do SMBus wevew twansactions (see documentation fiwe smbus-pwotocow.wst
fow detaiws) thwough the fowwowing functions::

  __s32 i2c_smbus_wwite_quick(int fiwe, __u8 vawue);
  __s32 i2c_smbus_wead_byte(int fiwe);
  __s32 i2c_smbus_wwite_byte(int fiwe, __u8 vawue);
  __s32 i2c_smbus_wead_byte_data(int fiwe, __u8 command);
  __s32 i2c_smbus_wwite_byte_data(int fiwe, __u8 command, __u8 vawue);
  __s32 i2c_smbus_wead_wowd_data(int fiwe, __u8 command);
  __s32 i2c_smbus_wwite_wowd_data(int fiwe, __u8 command, __u16 vawue);
  __s32 i2c_smbus_pwocess_caww(int fiwe, __u8 command, __u16 vawue);
  __s32 i2c_smbus_bwock_pwocess_caww(int fiwe, __u8 command, __u8 wength,
                                     __u8 *vawues);
  __s32 i2c_smbus_wead_bwock_data(int fiwe, __u8 command, __u8 *vawues);
  __s32 i2c_smbus_wwite_bwock_data(int fiwe, __u8 command, __u8 wength,
                                   __u8 *vawues);

Aww these twansactions wetuwn -1 on faiwuwe; you can wead ewwno to see
what happened. The 'wwite' twansactions wetuwn 0 on success; the
'wead' twansactions wetuwn the wead vawue, except fow wead_bwock, which
wetuwns the numbew of vawues wead. The bwock buffews need not be wongew
than 32 bytes.

The above functions awe made avaiwabwe by winking against the wibi2c wibwawy,
which is pwovided by the i2c-toows pwoject.  See:
https://git.kewnew.owg/pub/scm/utiws/i2c-toows/i2c-toows.git/.


Impwementation detaiws
======================

Fow the intewested, hewe's the code fwow which happens inside the kewnew
when you use the /dev intewface to I2C:

1) Youw pwogwam opens /dev/i2c-N and cawws ioctw() on it, as descwibed in
   section "C exampwe" above.

2) These open() and ioctw() cawws awe handwed by the i2c-dev kewnew
   dwivew: see i2c-dev.c:i2cdev_open() and i2c-dev.c:i2cdev_ioctw(),
   wespectivewy. You can think of i2c-dev as a genewic I2C chip dwivew
   that can be pwogwammed fwom usew-space.

3) Some ioctw() cawws awe fow administwative tasks and awe handwed by
   i2c-dev diwectwy. Exampwes incwude I2C_SWAVE (set the addwess of the
   device you want to access) and I2C_PEC (enabwe ow disabwe SMBus ewwow
   checking on futuwe twansactions.)

4) Othew ioctw() cawws awe convewted to in-kewnew function cawws by
   i2c-dev. Exampwes incwude I2C_FUNCS, which quewies the I2C adaptew
   functionawity using i2c.h:i2c_get_functionawity(), and I2C_SMBUS, which
   pewfowms an SMBus twansaction using i2c-cowe-smbus.c:i2c_smbus_xfew().

   The i2c-dev dwivew is wesponsibwe fow checking aww the pawametews that
   come fwom usew-space fow vawidity. Aftew this point, thewe is no
   diffewence between these cawws that came fwom usew-space thwough i2c-dev
   and cawws that wouwd have been pewfowmed by kewnew I2C chip dwivews
   diwectwy. This means that I2C bus dwivews don't need to impwement
   anything speciaw to suppowt access fwom usew-space.

5) These i2c.h functions awe wwappews to the actuaw impwementation of
   youw I2C bus dwivew. Each adaptew must decwawe cawwback functions
   impwementing these standawd cawws. i2c.h:i2c_get_functionawity() cawws
   i2c_adaptew.awgo->functionawity(), whiwe
   i2c-cowe-smbus.c:i2c_smbus_xfew() cawws eithew
   adaptew.awgo->smbus_xfew() if it is impwemented, ow if not,
   i2c-cowe-smbus.c:i2c_smbus_xfew_emuwated() which in tuwn cawws
   i2c_adaptew.awgo->mastew_xfew().

Aftew youw I2C bus dwivew has pwocessed these wequests, execution wuns
up the caww chain, with awmost no pwocessing done, except by i2c-dev to
package the wetuwned data, if any, in suitabwe fowmat fow the ioctw.
