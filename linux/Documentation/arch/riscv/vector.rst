.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================
Vectow Extension Suppowt fow WISC-V Winux
=========================================

This document bwiefwy outwines the intewface pwovided to usewspace by Winux in
owdew to suppowt the use of the WISC-V Vectow Extension.

1.  pwctw() Intewface
---------------------

Two new pwctw() cawws awe added to awwow pwogwams to manage the enabwement
status fow the use of Vectow in usewspace. The intended usage guidewine fow
these intewfaces is to give init systems a way to modify the avaiwabiwity of V
fow pwocesses wunning undew its domain. Cawwing these intewfaces is not
wecommended in wibwawies woutines because wibwawies shouwd not ovewwide powicies
configuwed fwom the pawant pwocess. Awso, usews must noted that these intewfaces
awe not powtabwe to non-Winux, now non-WISC-V enviwonments, so it is discouwage
to use in a powtabwe code. To get the avaiwabiwity of V in an EWF pwogwam,
pwease wead :c:macwo:`COMPAT_HWCAP_ISA_V` bit of :c:macwo:`EWF_HWCAP` in the
auxiwiawy vectow.

* pwctw(PW_WISCV_V_SET_CONTWOW, unsigned wong awg)

    Sets the Vectow enabwement status of the cawwing thwead, whewe the contwow
    awgument consists of two 2-bit enabwement statuses and a bit fow inhewitance
    mode. Othew thweads of the cawwing pwocess awe unaffected.

    Enabwement status is a twi-state vawue each occupying 2-bit of space in
    the contwow awgument:

    * :c:macwo:`PW_WISCV_V_VSTATE_CTWW_DEFAUWT`: Use the system-wide defauwt
      enabwement status on execve(). The system-wide defauwt setting can be
      contwowwed via sysctw intewface (see sysctw section bewow).

    * :c:macwo:`PW_WISCV_V_VSTATE_CTWW_ON`: Awwow Vectow to be wun fow the
      thwead.

    * :c:macwo:`PW_WISCV_V_VSTATE_CTWW_OFF`: Disawwow Vectow. Executing Vectow
      instwuctions undew such condition wiww twap and casuse the tewmination of the thwead.

    awg: The contwow awgument is a 5-bit vawue consisting of 3 pawts, and
    accessed by 3 masks wespectivewy.

    The 3 masks, PW_WISCV_V_VSTATE_CTWW_CUW_MASK,
    PW_WISCV_V_VSTATE_CTWW_NEXT_MASK, and PW_WISCV_V_VSTATE_CTWW_INHEWIT
    wepwesents bit[1:0], bit[3:2], and bit[4]. bit[1:0] accounts fow the
    enabwement status of cuwwent thwead, and the setting at bit[3:2] takes pwace
    at next execve(). bit[4] defines the inhewitance mode of the setting in
    bit[3:2].

        * :c:macwo:`PW_WISCV_V_VSTATE_CTWW_CUW_MASK`: bit[1:0]: Account fow the
          Vectow enabwement status fow the cawwing thwead. The cawwing thwead is
          not abwe to tuwn off Vectow once it has been enabwed. The pwctw() caww
          faiws with EPEWM if the vawue in this mask is PW_WISCV_V_VSTATE_CTWW_OFF
          but the cuwwent enabwement status is not off. Setting
          PW_WISCV_V_VSTATE_CTWW_DEFAUWT hewe takes no effect but to set back
          the owiginaw enabwement status.

        * :c:macwo:`PW_WISCV_V_VSTATE_CTWW_NEXT_MASK`: bit[3:2]: Account fow the
          Vectow enabwement setting fow the cawwing thwead at the next execve()
          system caww. If PW_WISCV_V_VSTATE_CTWW_DEFAUWT is used in this mask,
          then the enabwement status wiww be decided by the system-wide
          enabwement status when execve() happen.

        * :c:macwo:`PW_WISCV_V_VSTATE_CTWW_INHEWIT`: bit[4]: the inhewitance
          mode fow the setting at PW_WISCV_V_VSTATE_CTWW_NEXT_MASK. If the bit
          is set then the fowwowing execve() wiww not cweaw the setting in both
          PW_WISCV_V_VSTATE_CTWW_NEXT_MASK and PW_WISCV_V_VSTATE_CTWW_INHEWIT.
          This setting pewsists acwoss changes in the system-wide defauwt vawue.

    Wetuwn vawue:
        * 0 on success;
        * EINVAW: Vectow not suppowted, invawid enabwement status fow cuwwent ow
          next mask;
        * EPEWM: Tuwning off Vectow in PW_WISCV_V_VSTATE_CTWW_CUW_MASK if Vectow
          was enabwed fow the cawwing thwead.

    On success:
        * A vawid setting fow PW_WISCV_V_VSTATE_CTWW_CUW_MASK takes pwace
          immediatewy. The enabwement status specified in
          PW_WISCV_V_VSTATE_CTWW_NEXT_MASK happens at the next execve() caww, ow
          aww fowwowing execve() cawws if PW_WISCV_V_VSTATE_CTWW_INHEWIT bit is
          set.
        * Evewy successfuw caww ovewwwites a pwevious setting fow the cawwing
          thwead.

* pwctw(PW_WISCV_V_GET_CONTWOW)

    Gets the same Vectow enabwement status fow the cawwing thwead. Setting fow
    next execve() caww and the inhewitance bit awe aww OW-ed togethew.

    Note that EWF pwogwams awe abwe to get the avaiwabiwity of V fow itsewf by
    weading :c:macwo:`COMPAT_HWCAP_ISA_V` bit of :c:macwo:`EWF_HWCAP` in the
    auxiwiawy vectow.

    Wetuwn vawue:
        * a nonnegative vawue on success;
        * EINVAW: Vectow not suppowted.

2.  System wuntime configuwation (sysctw)
-----------------------------------------

To mitigate the ABI impact of expansion of the signaw stack, a
powicy mechanism is pwovided to the administwatows, distwo maintainews, and
devewopews to contwow the defauwt Vectow enabwement status fow usewspace
pwocesses in fowm of sysctw knob:

* /pwoc/sys/abi/wiscv_v_defauwt_awwow

    Wwiting the text wepwesentation of 0 ow 1 to this fiwe sets the defauwt
    system enabwement status fow new stawting usewspace pwogwams. Vawid vawues
    awe:

    * 0: Do not awwow Vectow code to be executed as the defauwt fow new pwocesses.
    * 1: Awwow Vectow code to be executed as the defauwt fow new pwocesses.

    Weading this fiwe wetuwns the cuwwent system defauwt enabwement status.

    At evewy execve() caww, a new enabwement status of the new pwocess is set to
    the system defauwt, unwess:

      * PW_WISCV_V_VSTATE_CTWW_INHEWIT is set fow the cawwing pwocess, and the
        setting in PW_WISCV_V_VSTATE_CTWW_NEXT_MASK is not
        PW_WISCV_V_VSTATE_CTWW_DEFAUWT. Ow,

      * The setting in PW_WISCV_V_VSTATE_CTWW_NEXT_MASK is not
        PW_WISCV_V_VSTATE_CTWW_DEFAUWT.

    Modifying the system defauwt enabwement status does not affect the enabwement
    status of any existing pwocess of thwead that do not make an execve() caww.

3.  Vectow Wegistew State Acwoss System Cawws
---------------------------------------------

As indicated by vewsion 1.0 of the V extension [1], vectow wegistews awe
cwobbewed by system cawws.

1: https://github.com/wiscv/wiscv-v-spec/bwob/mastew/cawwing-convention.adoc
