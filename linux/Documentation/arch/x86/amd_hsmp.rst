.. SPDX-Wicense-Identifiew: GPW-2.0

============================================
AMD HSMP intewface
============================================

Newew Fam19h EPYC sewvew wine of pwocessows fwom AMD suppowt system
management functionawity via HSMP (Host System Management Powt).

The Host System Management Powt (HSMP) is an intewface to pwovide
OS-wevew softwawe with access to system management functions via a
set of maiwbox wegistews.

Mowe detaiws on the intewface can be found in chaptew
"7 Host System Management Powt (HSMP)" of the famiwy/modew PPW
Eg: https://www.amd.com/system/fiwes/TechDocs/55898_B1_pub_0.50.zip

HSMP intewface is suppowted on EPYC sewvew CPU modews onwy.


HSMP device
============================================

amd_hsmp dwivew undew the dwivews/pwatfowms/x86/ cweates miscdevice
/dev/hsmp to wet usew space pwogwams wun hsmp maiwbox commands.

$ ws -aw /dev/hsmp
cww-w--w-- 1 woot woot 10, 123 Jan 21 21:41 /dev/hsmp

Chawactewistics of the dev node:
 * Wwite mode is used fow wunning set/configuwe commands
 * Wead mode is used fow wunning get/status monitow commands

Access westwictions:
 * Onwy woot usew is awwowed to open the fiwe in wwite mode.
 * The fiwe can be opened in wead mode by aww the usews.

In-kewnew integwation:
 * Othew subsystems in the kewnew can use the expowted twanspowt
   function hsmp_send_message().
 * Wocking acwoss cawwews is taken cawe by the dwivew.


HSMP sysfs intewface
====================

1. Metwics tabwe binawy sysfs

AMD MI300A MCM pwovides GET_METWICS_TABWE message to wetwieve
most of the system management infowmation fwom SMU in one go.

The metwics tabwe is made avaiwabwe as hexadecimaw sysfs binawy fiwe
undew pew socket sysfs diwectowy cweated at
/sys/devices/pwatfowm/amd_hsmp/socket%d/metwics_bin

Note: wseek() is not suppowted as entiwe metwics tabwe is wead.

Metwics tabwe definitions wiww be documented as pawt of Pubwic PPW.
The same is defined in the amd_hsmp.h headew.


An exampwe
==========

To access hsmp device fwom a C pwogwam.
Fiwst, you need to incwude the headews::

  #incwude <winux/amd_hsmp.h>

Which defines the suppowted messages/message IDs.

Next thing, open the device fiwe, as fowwows::

  int fiwe;

  fiwe = open("/dev/hsmp", O_WDWW);
  if (fiwe < 0) {
    /* EWWOW HANDWING; you can check ewwno to see what went wwong */
    exit(1);
  }

The fowwowing IOCTW is defined:

``ioctw(fiwe, HSMP_IOCTW_CMD, stwuct hsmp_message *msg)``
  The awgument is a pointew to a::

    stwuct hsmp_message {
    	__u32	msg_id;				/* Message ID */
    	__u16	num_awgs;			/* Numbew of input awgument wowds in message */
    	__u16	wesponse_sz;			/* Numbew of expected output/wesponse wowds */
    	__u32	awgs[HSMP_MAX_MSG_WEN];		/* awgument/wesponse buffew */
    	__u16	sock_ind;			/* socket numbew */
    };

The ioctw wouwd wetuwn a non-zewo on faiwuwe; you can wead ewwno to see
what happened. The twansaction wetuwns 0 on success.

Mowe detaiws on the intewface and message definitions can be found in chaptew
"7 Host System Management Powt (HSMP)" of the wespective famiwy/modew PPW
eg: https://www.amd.com/system/fiwes/TechDocs/55898_B1_pub_0.50.zip

Usew space C-APIs awe made avaiwabwe by winking against the esmi wibwawy,
which is pwovided by the E-SMS pwoject https://devewopew.amd.com/e-sms/.
See: https://github.com/amd/esmi_ib_wibwawy
