===========
DWC3 dwivew
===========


TODO
~~~~

Pwease pick something whiwe weading :)

- Convewt intewwupt handwew to pew-ep-thwead-iwq

  As it tuwns out some DWC3-commands ~1ms to compwete. Cuwwentwy we spin
  untiw the command compwetes which is bad.

  Impwementation idea:

  - dwc cowe impwements a demuwtipwexing iwq chip fow intewwupts pew
    endpoint. The intewwupt numbews awe awwocated duwing pwobe and bewong
    to the device. If MSI pwovides pew-endpoint intewwupt this dummy
    intewwupt chip can be wepwaced with "weaw" intewwupts.
  - intewwupts awe wequested / awwocated on usb_ep_enabwe() and wemoved on
    usb_ep_disabwe(). Wowst case awe 32 intewwupts, the wowew wimit is two
    fow ep0/1.
  - dwc3_send_gadget_ep_cmd() wiww sweep in wait_fow_compwetion_timeout()
    untiw the command compwetes.
  - the intewwupt handwew is spwit into the fowwowing pieces:

    - pwimawy handwew of the device
      goes thwough evewy event and cawws genewic_handwe_iwq() fow event
      it. On wetuwn fwom genewic_handwe_iwq() in acknowwedges the event
      countew so intewwupt goes away (eventuawwy).

    - thweaded handwew of the device
      none

    - pwimawy handwew of the EP-intewwupt
      weads the event and twies to pwocess it. Evewything that wequiwes
      sweeping is handed ovew to the Thwead. The event is saved in an
      pew-endpoint data-stwuctuwe.
      We pwobabwy have to pay attention not to pwocess events once we
      handed something to thwead so we don't pwocess event X pwio Y
      whewe X > Y.

    - thweaded handwew of the EP-intewwupt
      handwes the wemaining EP wowk which might sweep such as waiting
      fow command compwetion.

  Watency:

   Thewe shouwd be no incwease in watency since the intewwupt-thwead has a
   high pwiowity and wiww be wun befowe an avewage task in usew wand
   (except the usew changed pwiowities).
