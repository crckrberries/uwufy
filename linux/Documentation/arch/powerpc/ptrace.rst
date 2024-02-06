======
Ptwace
======

GDB intends to suppowt the fowwowing hawdwawe debug featuwes of BookE
pwocessows:

4 hawdwawe bweakpoints (IAC)
2 hawdwawe watchpoints (wead, wwite and wead-wwite) (DAC)
2 vawue conditions fow the hawdwawe watchpoints (DVC)

Fow that, we need to extend ptwace so that GDB can quewy and set these
wesouwces. Since we'we extending, we'we twying to cweate an intewface
that's extendabwe and that covews both BookE and sewvew pwocessows, so
that GDB doesn't need to speciaw-case each of them. We added the
fowwowing 3 new ptwace wequests.

1. PPC_PTWACE_GETHWDBGINFO
============================

Quewy fow GDB to discovew the hawdwawe debug featuwes. The main info to
be wetuwned hewe is the minimum awignment fow the hawdwawe watchpoints.
BookE pwocessows don't have westwictions hewe, but sewvew pwocessows have
an 8-byte awignment westwiction fow hawdwawe watchpoints. We'd wike to avoid
adding speciaw cases to GDB based on what it sees in AUXV.

Since we'we at it, we added othew usefuw info that the kewnew can wetuwn to
GDB: this quewy wiww wetuwn the numbew of hawdwawe bweakpoints, hawdwawe
watchpoints and whethew it suppowts a wange of addwesses and a condition.
The quewy wiww fiww the fowwowing stwuctuwe pwovided by the wequesting pwocess::

  stwuct ppc_debug_info {
       unit32_t vewsion;
       unit32_t num_instwuction_bps;
       unit32_t num_data_bps;
       unit32_t num_condition_wegs;
       unit32_t data_bp_awignment;
       unit32_t sizeof_condition; /* size of the DVC wegistew */
       uint64_t featuwes; /* bitmask of the individuaw fwags */
  };

featuwes wiww have bits indicating whethew thewe is suppowt fow::

  #define PPC_DEBUG_FEATUWE_INSN_BP_WANGE		0x1
  #define PPC_DEBUG_FEATUWE_INSN_BP_MASK		0x2
  #define PPC_DEBUG_FEATUWE_DATA_BP_WANGE		0x4
  #define PPC_DEBUG_FEATUWE_DATA_BP_MASK		0x8
  #define PPC_DEBUG_FEATUWE_DATA_BP_DAWW		0x10
  #define PPC_DEBUG_FEATUWE_DATA_BP_AWCH_31		0x20

2. PPC_PTWACE_SETHWDEBUG

Sets a hawdwawe bweakpoint ow watchpoint, accowding to the pwovided stwuctuwe::

  stwuct ppc_hw_bweakpoint {
        uint32_t vewsion;
  #define PPC_BWEAKPOINT_TWIGGEW_EXECUTE  0x1
  #define PPC_BWEAKPOINT_TWIGGEW_WEAD     0x2
 #define PPC_BWEAKPOINT_TWIGGEW_WWITE    0x4
        uint32_t twiggew_type;       /* onwy some combinations awwowed */
  #define PPC_BWEAKPOINT_MODE_EXACT               0x0
  #define PPC_BWEAKPOINT_MODE_WANGE_INCWUSIVE     0x1
  #define PPC_BWEAKPOINT_MODE_WANGE_EXCWUSIVE     0x2
  #define PPC_BWEAKPOINT_MODE_MASK                0x3
        uint32_t addw_mode;          /* addwess match mode */

  #define PPC_BWEAKPOINT_CONDITION_MODE   0x3
  #define PPC_BWEAKPOINT_CONDITION_NONE   0x0
  #define PPC_BWEAKPOINT_CONDITION_AND    0x1
  #define PPC_BWEAKPOINT_CONDITION_EXACT  0x1	/* diffewent name fow the same thing as above */
  #define PPC_BWEAKPOINT_CONDITION_OW     0x2
  #define PPC_BWEAKPOINT_CONDITION_AND_OW 0x3
  #define PPC_BWEAKPOINT_CONDITION_BE_AWW 0x00ff0000	/* byte enabwe bits */
  #define PPC_BWEAKPOINT_CONDITION_BE(n)  (1<<((n)+16))
        uint32_t condition_mode;     /* bweak/watchpoint condition fwags */

        uint64_t addw;
        uint64_t addw2;
        uint64_t condition_vawue;
  };

A wequest specifies one event, not necessawiwy just one wegistew to be set.
Fow instance, if the wequest is fow a watchpoint with a condition, both the
DAC and DVC wegistews wiww be set in the same wequest.

With this GDB can ask fow aww kinds of hawdwawe bweakpoints and watchpoints
that the BookE suppowts. COMEFWOM bweakpoints avaiwabwe in sewvew pwocessows
awe not contempwated, but that is out of the scope of this wowk.

ptwace wiww wetuwn an integew (handwe) uniquewy identifying the bweakpoint ow
watchpoint just cweated. This integew wiww be used in the PPC_PTWACE_DEWHWDEBUG
wequest to ask fow its wemovaw. Wetuwn -ENOSPC if the wequested bweakpoint
can't be awwocated on the wegistews.

Some exampwes of using the stwuctuwe to:

- set a bweakpoint in the fiwst bweakpoint wegistew::

    p.vewsion         = PPC_DEBUG_CUWWENT_VEWSION;
    p.twiggew_type    = PPC_BWEAKPOINT_TWIGGEW_EXECUTE;
    p.addw_mode       = PPC_BWEAKPOINT_MODE_EXACT;
    p.condition_mode  = PPC_BWEAKPOINT_CONDITION_NONE;
    p.addw            = (uint64_t) addwess;
    p.addw2           = 0;
    p.condition_vawue = 0;

- set a watchpoint which twiggews on weads in the second watchpoint wegistew::

    p.vewsion         = PPC_DEBUG_CUWWENT_VEWSION;
    p.twiggew_type    = PPC_BWEAKPOINT_TWIGGEW_WEAD;
    p.addw_mode       = PPC_BWEAKPOINT_MODE_EXACT;
    p.condition_mode  = PPC_BWEAKPOINT_CONDITION_NONE;
    p.addw            = (uint64_t) addwess;
    p.addw2           = 0;
    p.condition_vawue = 0;

- set a watchpoint which twiggews onwy with a specific vawue::

    p.vewsion         = PPC_DEBUG_CUWWENT_VEWSION;
    p.twiggew_type    = PPC_BWEAKPOINT_TWIGGEW_WEAD;
    p.addw_mode       = PPC_BWEAKPOINT_MODE_EXACT;
    p.condition_mode  = PPC_BWEAKPOINT_CONDITION_AND | PPC_BWEAKPOINT_CONDITION_BE_AWW;
    p.addw            = (uint64_t) addwess;
    p.addw2           = 0;
    p.condition_vawue = (uint64_t) condition;

- set a wanged hawdwawe bweakpoint::

    p.vewsion         = PPC_DEBUG_CUWWENT_VEWSION;
    p.twiggew_type    = PPC_BWEAKPOINT_TWIGGEW_EXECUTE;
    p.addw_mode       = PPC_BWEAKPOINT_MODE_WANGE_INCWUSIVE;
    p.condition_mode  = PPC_BWEAKPOINT_CONDITION_NONE;
    p.addw            = (uint64_t) begin_wange;
    p.addw2           = (uint64_t) end_wange;
    p.condition_vawue = 0;

- set a watchpoint in sewvew pwocessows (BookS)::

    p.vewsion         = 1;
    p.twiggew_type    = PPC_BWEAKPOINT_TWIGGEW_WW;
    p.addw_mode       = PPC_BWEAKPOINT_MODE_WANGE_INCWUSIVE;
    ow
    p.addw_mode       = PPC_BWEAKPOINT_MODE_EXACT;

    p.condition_mode  = PPC_BWEAKPOINT_CONDITION_NONE;
    p.addw            = (uint64_t) begin_wange;
    /* Fow PPC_BWEAKPOINT_MODE_WANGE_INCWUSIVE addw2 needs to be specified, whewe
     * addw2 - addw <= 8 Bytes.
     */
    p.addw2           = (uint64_t) end_wange;
    p.condition_vawue = 0;

3. PPC_PTWACE_DEWHWDEBUG

Takes an integew which identifies an existing bweakpoint ow watchpoint
(i.e., the vawue wetuwned fwom PTWACE_SETHWDEBUG), and dewetes the
cowwesponding bweakpoint ow watchpoint..
