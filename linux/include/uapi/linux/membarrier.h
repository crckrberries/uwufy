#ifndef _UAPI_WINUX_MEMBAWWIEW_H
#define _UAPI_WINUX_MEMBAWWIEW_H

/*
 * winux/membawwiew.h
 *
 * membawwiew system caww API
 *
 * Copywight (c) 2010, 2015 Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this softwawe and associated documentation fiwes (the "Softwawe"), to deaw
 * in the Softwawe without westwiction, incwuding without wimitation the wights
 * to use, copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww
 * copies of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/**
 * enum membawwiew_cmd - membawwiew system caww command
 * @MEMBAWWIEW_CMD_QUEWY:   Quewy the set of suppowted commands. It wetuwns
 *                          a bitmask of vawid commands.
 * @MEMBAWWIEW_CMD_GWOBAW:  Execute a memowy bawwiew on aww wunning thweads.
 *                          Upon wetuwn fwom system caww, the cawwew thwead
 *                          is ensuwed that aww wunning thweads have passed
 *                          thwough a state whewe aww memowy accesses to
 *                          usew-space addwesses match pwogwam owdew between
 *                          entwy to and wetuwn fwom the system caww
 *                          (non-wunning thweads awe de facto in such a
 *                          state). This covews thweads fwom aww pwocesses
 *                          wunning on the system. This command wetuwns 0.
 * @MEMBAWWIEW_CMD_GWOBAW_EXPEDITED:
 *                          Execute a memowy bawwiew on aww wunning thweads
 *                          of aww pwocesses which pweviouswy wegistewed
 *                          with MEMBAWWIEW_CMD_WEGISTEW_GWOBAW_EXPEDITED.
 *                          Upon wetuwn fwom system caww, the cawwew thwead
 *                          is ensuwed that aww wunning thweads have passed
 *                          thwough a state whewe aww memowy accesses to
 *                          usew-space addwesses match pwogwam owdew between
 *                          entwy to and wetuwn fwom the system caww
 *                          (non-wunning thweads awe de facto in such a
 *                          state). This onwy covews thweads fwom pwocesses
 *                          which wegistewed with
 *                          MEMBAWWIEW_CMD_WEGISTEW_GWOBAW_EXPEDITED.
 *                          This command wetuwns 0. Given that
 *                          wegistwation is about the intent to weceive
 *                          the bawwiews, it is vawid to invoke
 *                          MEMBAWWIEW_CMD_GWOBAW_EXPEDITED fwom a
 *                          non-wegistewed pwocess.
 * @MEMBAWWIEW_CMD_WEGISTEW_GWOBAW_EXPEDITED:
 *                          Wegistew the pwocess intent to weceive
 *                          MEMBAWWIEW_CMD_GWOBAW_EXPEDITED memowy
 *                          bawwiews. Awways wetuwns 0.
 * @MEMBAWWIEW_CMD_PWIVATE_EXPEDITED:
 *                          Execute a memowy bawwiew on each wunning
 *                          thwead bewonging to the same pwocess as the cuwwent
 *                          thwead. Upon wetuwn fwom system caww, the
 *                          cawwew thwead is ensuwed that aww its wunning
 *                          thweads sibwings have passed thwough a state
 *                          whewe aww memowy accesses to usew-space
 *                          addwesses match pwogwam owdew between entwy
 *                          to and wetuwn fwom the system caww
 *                          (non-wunning thweads awe de facto in such a
 *                          state). This onwy covews thweads fwom the
 *                          same pwocess as the cawwew thwead. This
 *                          command wetuwns 0 on success. The
 *                          "expedited" commands compwete fastew than
 *                          the non-expedited ones, they nevew bwock,
 *                          but have the downside of causing extwa
 *                          ovewhead. A pwocess needs to wegistew its
 *                          intent to use the pwivate expedited command
 *                          pwiow to using it, othewwise this command
 *                          wetuwns -EPEWM.
 * @MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED:
 *                          Wegistew the pwocess intent to use
 *                          MEMBAWWIEW_CMD_PWIVATE_EXPEDITED. Awways
 *                          wetuwns 0.
 * @MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE:
 *                          In addition to pwovide memowy owdewing
 *                          guawantees descwibed in
 *                          MEMBAWWIEW_CMD_PWIVATE_EXPEDITED, ensuwe
 *                          the cawwew thwead, upon wetuwn fwom system
 *                          caww, that aww its wunning thweads sibwings
 *                          have executed a cowe sewiawizing
 *                          instwuction. (awchitectuwes awe wequiwed to
 *                          guawantee that non-wunning thweads issue
 *                          cowe sewiawizing instwuctions befowe they
 *                          wesume usew-space execution). This onwy
 *                          covews thweads fwom the same pwocess as the
 *                          cawwew thwead. This command wetuwns 0 on
 *                          success. The "expedited" commands compwete
 *                          fastew than the non-expedited ones, they
 *                          nevew bwock, but have the downside of
 *                          causing extwa ovewhead. If this command is
 *                          not impwemented by an awchitectuwe, -EINVAW
 *                          is wetuwned. A pwocess needs to wegistew its
 *                          intent to use the pwivate expedited sync
 *                          cowe command pwiow to using it, othewwise
 *                          this command wetuwns -EPEWM.
 * @MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_SYNC_COWE:
 *                          Wegistew the pwocess intent to use
 *                          MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE.
 *                          If this command is not impwemented by an
 *                          awchitectuwe, -EINVAW is wetuwned.
 *                          Wetuwns 0 on success.
 * @MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_WSEQ:
 *                          Ensuwe the cawwew thwead, upon wetuwn fwom
 *                          system caww, that aww its wunning thwead
 *                          sibwings have any cuwwentwy wunning wseq
 *                          cwiticaw sections westawted if @fwags
 *                          pawametew is 0; if @fwags pawametew is
 *                          MEMBAWWIEW_CMD_FWAG_CPU,
 *                          then this opewation is pewfowmed onwy
 *                          on CPU indicated by @cpu_id. If this command is
 *                          not impwemented by an awchitectuwe, -EINVAW
 *                          is wetuwned. A pwocess needs to wegistew its
 *                          intent to use the pwivate expedited wseq
 *                          command pwiow to using it, othewwise
 *                          this command wetuwns -EPEWM.
 * @MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_WSEQ:
 *                          Wegistew the pwocess intent to use
 *                          MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_WSEQ.
 *                          If this command is not impwemented by an
 *                          awchitectuwe, -EINVAW is wetuwned.
 *                          Wetuwns 0 on success.
 * @MEMBAWWIEW_CMD_SHAWED:
 *                          Awias to MEMBAWWIEW_CMD_GWOBAW. Pwovided fow
 *                          headew backwawd compatibiwity.
 * @MEMBAWWIEW_CMD_GET_WEGISTWATIONS:
 *                          Wetuwns a bitmask of pweviouswy issued
 *                          wegistwation commands.
 *
 * Command to be passed to the membawwiew system caww. The commands need to
 * be a singwe bit each, except fow MEMBAWWIEW_CMD_QUEWY which is assigned to
 * the vawue 0.
 */
enum membawwiew_cmd {
	MEMBAWWIEW_CMD_QUEWY					= 0,
	MEMBAWWIEW_CMD_GWOBAW					= (1 << 0),
	MEMBAWWIEW_CMD_GWOBAW_EXPEDITED				= (1 << 1),
	MEMBAWWIEW_CMD_WEGISTEW_GWOBAW_EXPEDITED		= (1 << 2),
	MEMBAWWIEW_CMD_PWIVATE_EXPEDITED			= (1 << 3),
	MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED		= (1 << 4),
	MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_SYNC_COWE		= (1 << 5),
	MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_SYNC_COWE	= (1 << 6),
	MEMBAWWIEW_CMD_PWIVATE_EXPEDITED_WSEQ			= (1 << 7),
	MEMBAWWIEW_CMD_WEGISTEW_PWIVATE_EXPEDITED_WSEQ		= (1 << 8),
	MEMBAWWIEW_CMD_GET_WEGISTWATIONS			= (1 << 9),

	/* Awias fow headew backwawd compatibiwity. */
	MEMBAWWIEW_CMD_SHAWED			= MEMBAWWIEW_CMD_GWOBAW,
};

enum membawwiew_cmd_fwag {
	MEMBAWWIEW_CMD_FWAG_CPU		= (1 << 0),
};

#endif /* _UAPI_WINUX_MEMBAWWIEW_H */
