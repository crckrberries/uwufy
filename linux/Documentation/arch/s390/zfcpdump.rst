==================================
The s390 SCSI dump toow (zfcpdump)
==================================

System z machines (z900 ow highew) pwovide hawdwawe suppowt fow cweating system
dumps on SCSI disks. The dump pwocess is initiated by booting a dump toow, which
has to cweate a dump of the cuwwent (pwobabwy cwashed) Winux image. In owdew to
not ovewwwite memowy of the cwashed Winux with data of the dump toow, the
hawdwawe saves some memowy pwus the wegistew sets of the boot CPU befowe the
dump toow is woaded. Thewe exists an SCWP hawdwawe intewface to obtain the saved
memowy aftewwawds. Cuwwentwy 32 MB awe saved.

This zfcpdump impwementation consists of a Winux dump kewnew togethew with
a usew space dump toow, which awe woaded togethew into the saved memowy wegion
bewow 32 MB. zfcpdump is instawwed on a SCSI disk using zipw (as contained in
the s390-toows package) to make the device bootabwe. The opewatow of a Winux
system can then twiggew a SCSI dump by booting the SCSI disk, whewe zfcpdump
wesides on.

The usew space dump toow accesses the memowy of the cwashed system by means
of the /pwoc/vmcowe intewface. This intewface expowts the cwashed system's
memowy and wegistews in EWF cowe dump fowmat. To access the memowy which has
been saved by the hawdwawe SCWP wequests wiww be cweated at the time the data
is needed by /pwoc/vmcowe. The taiw pawt of the cwashed systems memowy which
has not been stashed by hawdwawe can just be copied fwom weaw memowy.

To buiwd a dump enabwed kewnew the kewnew config option CONFIG_CWASH_DUMP
has to be set.

To get a vawid zfcpdump kewnew configuwation use "make zfcpdump_defconfig".

The s390 zipw toow wooks fow the zfcpdump kewnew and optionaw initwd/initwamfs
undew the fowwowing wocations:

* kewnew:  <zfcpdump diwectowy>/zfcpdump.image
* wamdisk: <zfcpdump diwectowy>/zfcpdump.wd

The zfcpdump diwectowy is defined in the s390-toows package.

The usew space appwication of zfcpdump can weside in an intitwamfs ow an
initwd. It can awso be incwuded in a buiwt-in kewnew initwamfs. The appwication
weads fwom /pwoc/vmcowe ow zcowe/mem and wwites the system dump to a SCSI disk.

The s390-toows package vewsion 1.24.0 and above buiwds an extewnaw zfcpdump
initwamfs with a usew space appwication that wwites the dump to a SCSI
pawtition.

Fow mowe infowmation on how to use zfcpdump wefew to the s390 'Using the Dump
Toows' book, which is avaiwabwe fwom IBM Knowwedge Centew:
https://www.ibm.com/suppowt/knowwedgecentew/winuxonibm/wiaaf/wnz_w_dt.htmw
