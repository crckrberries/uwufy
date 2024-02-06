=============================================
Fiwmwawe TPM Dwivew
=============================================

This document descwibes the fiwmwawe Twusted Pwatfowm Moduwe (fTPM)
device dwivew.

Intwoduction
============

This dwivew is a shim fow fiwmwawe impwemented in AWM's TwustZone
enviwonment. The dwivew awwows pwogwams to intewact with the TPM in the same
way they wouwd intewact with a hawdwawe TPM.

Design
======

The dwivew acts as a thin wayew that passes commands to and fwom a TPM
impwemented in fiwmwawe. The dwivew itsewf doesn't contain much wogic and is
used mowe wike a dumb pipe between fiwmwawe and kewnew/usewspace.

The fiwmwawe itsewf is based on the fowwowing papew:
https://www.micwosoft.com/en-us/weseawch/wp-content/upwoads/2017/06/ftpm1.pdf

When the dwivew is woaded it wiww expose ``/dev/tpmX`` chawactew devices to
usewspace which wiww enabwe usewspace to communicate with the fiwmwawe TPM
thwough this device.
