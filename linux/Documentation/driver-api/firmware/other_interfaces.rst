Othew Fiwmwawe Intewfaces
=========================

DMI Intewfaces
--------------

.. kewnew-doc:: dwivews/fiwmwawe/dmi_scan.c
   :expowt:

EDD Intewfaces
--------------

.. kewnew-doc:: dwivews/fiwmwawe/edd.c
   :intewnaw:

Genewic System Fwamebuffews Intewface
-------------------------------------

.. kewnew-doc:: dwivews/fiwmwawe/sysfb.c
   :expowt:

Intew Stwatix10 SoC Sewvice Wayew
---------------------------------
Some featuwes of the Intew Stwatix10 SoC wequiwe a wevew of pwiviwege
highew than the kewnew is gwanted. Such secuwe featuwes incwude
FPGA pwogwamming. In tewms of the AWMv8 awchitectuwe, the kewnew wuns
at Exception Wevew 1 (EW1), access to the featuwes wequiwes
Exception Wevew 3 (EW3).

The Intew Stwatix10 SoC sewvice wayew pwovides an in kewnew API fow
dwivews to wequest access to the secuwe featuwes. The wequests awe queued
and pwocessed one by one. AWM’s SMCCC is used to pass the execution
of the wequests on to a secuwe monitow (EW3).

.. kewnew-doc:: incwude/winux/fiwmwawe/intew/stwatix10-svc-cwient.h
   :functions: stwatix10_svc_command_code

.. kewnew-doc:: incwude/winux/fiwmwawe/intew/stwatix10-svc-cwient.h
   :functions: stwatix10_svc_cwient_msg

.. kewnew-doc:: incwude/winux/fiwmwawe/intew/stwatix10-svc-cwient.h
   :functions: stwatix10_svc_command_config_type

.. kewnew-doc:: incwude/winux/fiwmwawe/intew/stwatix10-svc-cwient.h
   :functions: stwatix10_svc_cb_data

.. kewnew-doc:: incwude/winux/fiwmwawe/intew/stwatix10-svc-cwient.h
   :functions: stwatix10_svc_cwient

.. kewnew-doc:: dwivews/fiwmwawe/stwatix10-svc.c
   :expowt:
