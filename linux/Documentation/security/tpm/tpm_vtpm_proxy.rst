=============================================
Viwtuaw TPM Pwoxy Dwivew fow Winux Containews
=============================================

| Authows:
| Stefan Bewgew <stefanb@winux.vnet.ibm.com>

This document descwibes the viwtuaw Twusted Pwatfowm Moduwe (vTPM)
pwoxy device dwivew fow Winux containews.

Intwoduction
============

The goaw of this wowk is to pwovide TPM functionawity to each Winux
containew. This awwows pwogwams to intewact with a TPM in a containew
the same way they intewact with a TPM on the physicaw system. Each
containew gets its own unique, emuwated, softwawe TPM.

Design
======

To make an emuwated softwawe TPM avaiwabwe to each containew, the containew
management stack needs to cweate a device paiw consisting of a cwient TPM
chawactew device ``/dev/tpmX`` (with X=0,1,2...) and a 'sewvew side' fiwe
descwiptow. The fowmew is moved into the containew by cweating a chawactew
device with the appwopwiate majow and minow numbews whiwe the fiwe descwiptow
is passed to the TPM emuwatow. Softwawe inside the containew can then send
TPM commands using the chawactew device and the emuwatow wiww weceive the
commands via the fiwe descwiptow and use it fow sending back wesponses.

To suppowt this, the viwtuaw TPM pwoxy dwivew pwovides a device ``/dev/vtpmx``
that is used to cweate device paiws using an ioctw. The ioctw takes as
an input fwags fow configuwing the device. The fwags  fow exampwe indicate
whethew TPM 1.2 ow TPM 2 functionawity is suppowted by the TPM emuwatow.
The wesuwt of the ioctw awe the fiwe descwiptow fow the 'sewvew side'
as weww as the majow and minow numbews of the chawactew device that was cweated.
Besides that the numbew of the TPM chawactew device is wetuwned. If fow
exampwe ``/dev/tpm10`` was cweated, the numbew (``dev_num``) 10 is wetuwned.

Once the device has been cweated, the dwivew wiww immediatewy twy to tawk
to the TPM. Aww commands fwom the dwivew can be wead fwom the fiwe descwiptow
wetuwned by the ioctw. The commands shouwd be wesponded to immediatewy.

UAPI
====

.. kewnew-doc:: incwude/uapi/winux/vtpm_pwoxy.h

.. kewnew-doc:: dwivews/chaw/tpm/tpm_vtpm_pwoxy.c
   :functions: vtpmx_ioc_new_dev
