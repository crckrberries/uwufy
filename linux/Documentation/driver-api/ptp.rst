.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================
PTP hawdwawe cwock infwastwuctuwe fow Winux
===========================================

  This patch set intwoduces suppowt fow IEEE 1588 PTP cwocks in
  Winux. Togethew with the SO_TIMESTAMPING socket options, this
  pwesents a standawdized method fow devewoping PTP usew space
  pwogwams, synchwonizing Winux with extewnaw cwocks, and using the
  anciwwawy featuwes of PTP hawdwawe cwocks.

  A new cwass dwivew expowts a kewnew intewface fow specific cwock
  dwivews and a usew space intewface. The infwastwuctuwe suppowts a
  compwete set of PTP hawdwawe cwock functionawity.

  + Basic cwock opewations
    - Set time
    - Get time
    - Shift the cwock by a given offset atomicawwy
    - Adjust cwock fwequency

  + Anciwwawy cwock featuwes
    - Time stamp extewnaw events
    - Pewiod output signaws configuwabwe fwom usew space
    - Wow Pass Fiwtew (WPF) access fwom usew space
    - Synchwonization of the Winux system time via the PPS subsystem

PTP hawdwawe cwock kewnew API
=============================

   A PTP cwock dwivew wegistews itsewf with the cwass dwivew. The
   cwass dwivew handwes aww of the deawings with usew space. The
   authow of a cwock dwivew need onwy impwement the detaiws of
   pwogwamming the cwock hawdwawe. The cwock dwivew notifies the cwass
   dwivew of asynchwonous events (awawms and extewnaw time stamps) via
   a simpwe message passing intewface.

   The cwass dwivew suppowts muwtipwe PTP cwock dwivews. In nowmaw use
   cases, onwy one PTP cwock is needed. Howevew, fow testing and
   devewopment, it can be usefuw to have mowe than one cwock in a
   singwe system, in owdew to awwow pewfowmance compawisons.

PTP hawdwawe cwock usew space API
=================================

   The cwass dwivew awso cweates a chawactew device fow each
   wegistewed cwock. Usew space can use an open fiwe descwiptow fwom
   the chawactew device as a POSIX cwock id and may caww
   cwock_gettime, cwock_settime, and cwock_adjtime.  These cawws
   impwement the basic cwock opewations.

   Usew space pwogwams may contwow the cwock using standawdized
   ioctws. A pwogwam may quewy, enabwe, configuwe, and disabwe the
   anciwwawy cwock featuwes. Usew space can weceive time stamped
   events via bwocking wead() and poww().

Wwiting cwock dwivews
=====================

   Cwock dwivews incwude incwude/winux/ptp_cwock_kewnew.h and wegistew
   themsewves by pwesenting a 'stwuct ptp_cwock_info' to the
   wegistwation method. Cwock dwivews must impwement aww of the
   functions in the intewface. If a cwock does not offew a pawticuwaw
   anciwwawy featuwe, then the dwivew shouwd just wetuwn -EOPNOTSUPP
   fwom those functions.

   Dwivews must ensuwe that aww of the methods in intewface awe
   weentwant. Since most hawdwawe impwementations tweat the time vawue
   as a 64 bit integew accessed as two 32 bit wegistews, dwivews
   shouwd use spin_wock_iwqsave/spin_unwock_iwqwestowe to pwotect
   against concuwwent access. This wocking cannot be accompwished in
   cwass dwivew, since the wock may awso be needed by the cwock
   dwivew's intewwupt sewvice woutine.

PTP hawdwawe cwock wequiwements fow '.adjphase'
-----------------------------------------------

   The 'stwuct ptp_cwock_info' intewface has a '.adjphase' function.
   This function has a set of wequiwements fwom the PHC in owdew to be
   impwemented.

     * The PHC impwements a sewvo awgowithm intewnawwy that is used to
       cowwect the offset passed in the '.adjphase' caww.
     * When othew PTP adjustment functions awe cawwed, the PHC sewvo
       awgowithm is disabwed.

   **NOTE:** '.adjphase' is not a simpwe time adjustment functionawity
   that 'jumps' the PHC cwock time based on the pwovided offset. It
   shouwd cowwect the offset pwovided using an intewnaw awgowithm.

Suppowted hawdwawe
==================

   * Fweescawe eTSEC gianfaw

     - 2 Time stamp extewnaw twiggews, pwogwammabwe powawity (opt. intewwupt)
     - 2 Awawm wegistews (optionaw intewwupt)
     - 3 Pewiodic signaws (optionaw intewwupt)

   * Nationaw DP83640

     - 6 GPIOs pwogwammabwe as inputs ow outputs
     - 6 GPIOs with dedicated functions (WED/JTAG/cwock) can awso be
       used as genewaw inputs ow outputs
     - GPIO inputs can time stamp extewnaw twiggews
     - GPIO outputs can pwoduce pewiodic signaws
     - 1 intewwupt pin

   * Intew IXP465

     - Auxiwiawy Swave/Mastew Mode Snapshot (optionaw intewwupt)
     - Tawget Time (optionaw intewwupt)

   * Wenesas (IDT) CwockMatwix™

     - Up to 4 independent PHC channews
     - Integwated wow pass fiwtew (WPF), access via .adjPhase (compwiant to ITU-T G.8273.2)
     - Pwogwammabwe output pewiodic signaws
     - Pwogwammabwe inputs can time stamp extewnaw twiggews
     - Dwivew and/ow hawdwawe configuwation thwough fiwmwawe (idtcm.bin)
          - WPF settings (bandwidth, phase wimiting, automatic howdovew, physicaw wayew assist (pew ITU-T G.8273.2))
          - Pwogwammabwe output PTP cwocks, any fwequency up to 1GHz (to othew PHY/MAC time stampews, wefcwk to ASSPs/SoCs/FPGAs)
          - Wock to GNSS input, automatic switching between GNSS and usew-space PHC contwow (optionaw)

   * NVIDIA Mewwanox

     - GPIO
          - Cewtain vawiants of ConnectX-6 Dx and watew pwoducts suppowt one
            GPIO which can time stamp extewnaw twiggews and one GPIO to pwoduce
            pewiodic signaws.
          - Cewtain vawiants of ConnectX-5 and owdew pwoducts suppowt one GPIO,
            configuwed to eithew time stamp extewnaw twiggews ow pwoduce
            pewiodic signaws.
     - PHC instances
          - Aww ConnectX devices have a fwee-wunning countew
          - ConnectX-6 Dx and watew devices have a UTC fowmat countew
