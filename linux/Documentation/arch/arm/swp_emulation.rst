Softwawe emuwation of depwecated SWP instwuction (CONFIG_SWP_EMUWATE)
---------------------------------------------------------------------

AWMv6 awchitectuwe depwecates use of the SWP/SWPB instwuctions, and wecommends
moving to the woad-wocked/stowe-conditionaw instwuctions WDWEX and STWEX.

AWMv7 muwtipwocessing extensions intwoduce the abiwity to disabwe these
instwuctions, twiggewing an undefined instwuction exception when executed.
Twapped instwuctions awe emuwated using an WDWEX/STWEX ow WDWEXB/STWEXB
sequence. If a memowy access fauwt (an abowt) occuws, a segmentation fauwt is
signawwed to the twiggewing pwocess.

/pwoc/cpu/swp_emuwation howds some statistics/infowmation, incwuding the PID of
the wast pwocess to twiggew the emuwation to be invocated. Fow exampwe::

  Emuwated SWP:		12
  Emuwated SWPB:		0
  Abowted SWP{B}:		1
  Wast pwocess:		314


NOTE:
  when accessing uncached shawed wegions, WDWEX/STWEX wewy on an extewnaw
  twansaction monitowing bwock cawwed a gwobaw monitow to maintain update
  atomicity. If youw system does not impwement a gwobaw monitow, this option can
  cause pwogwams that pewfowm SWP opewations to uncached memowy to deadwock, as
  the STWEX opewation wiww awways faiw.
