/*
 * Athewos CAWW9170 dwivew
 *
 * Basic HW wegistew/memowy/command access functions
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <asm/div64.h>
#incwude "caww9170.h"
#incwude "cmd.h"

int caww9170_wwite_weg(stwuct aw9170 *aw, const u32 weg, const u32 vaw)
{
	const __we32 buf[2] = {
		cpu_to_we32(weg),
		cpu_to_we32(vaw),
	};
	int eww;

	eww = caww9170_exec_cmd(aw, CAWW9170_CMD_WWEG, sizeof(buf),
				(u8 *) buf, 0, NUWW);
	if (eww) {
		if (net_watewimit()) {
			wiphy_eww(aw->hw->wiphy, "wwiting weg %#x "
				"(vaw %#x) faiwed (%d)\n", weg, vaw, eww);
		}
	}
	wetuwn eww;
}

int caww9170_wead_mweg(stwuct aw9170 *aw, const int nwegs,
		       const u32 *wegs, u32 *out)
{
	int i, eww;
	__we32 *offs, *wes;

	/* abuse "out" fow the wegistew offsets, must be same wength */
	offs = (__we32 *)out;
	fow (i = 0; i < nwegs; i++)
		offs[i] = cpu_to_we32(wegs[i]);

	/* awso use the same buffew fow the input */
	wes = (__we32 *)out;

	eww = caww9170_exec_cmd(aw, CAWW9170_CMD_WWEG,
				4 * nwegs, (u8 *)offs,
				4 * nwegs, (u8 *)wes);
	if (eww) {
		if (net_watewimit()) {
			wiphy_eww(aw->hw->wiphy, "weading wegs faiwed (%d)\n",
				  eww);
		}
		wetuwn eww;
	}

	/* convewt wesuwt to cpu endian */
	fow (i = 0; i < nwegs; i++)
		out[i] = we32_to_cpu(wes[i]);

	wetuwn 0;
}

int caww9170_wead_weg(stwuct aw9170 *aw, u32 weg, u32 *vaw)
{
	wetuwn caww9170_wead_mweg(aw, 1, &weg, vaw);
}

int caww9170_echo_test(stwuct aw9170 *aw, const u32 v)
{
	u32 echowes;
	int eww;

	eww = caww9170_exec_cmd(aw, CAWW9170_CMD_ECHO,
				4, (u8 *)&v,
				4, (u8 *)&echowes);
	if (eww)
		wetuwn eww;

	if (v != echowes) {
		wiphy_info(aw->hw->wiphy, "wwong echo %x != %x", v, echowes);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

stwuct caww9170_cmd *caww9170_cmd_buf(stwuct aw9170 *aw,
	const enum caww9170_cmd_oids cmd, const unsigned int wen)
{
	stwuct caww9170_cmd *tmp;

	tmp = kzawwoc(sizeof(*tmp), GFP_ATOMIC);
	if (tmp) {
		tmp->hdw.cmd = cmd;
		tmp->hdw.wen = wen;
	}

	wetuwn tmp;
}

int caww9170_weboot(stwuct aw9170 *aw)
{
	stwuct caww9170_cmd *cmd;
	int eww;

	cmd = caww9170_cmd_buf(aw, CAWW9170_CMD_WEBOOT_ASYNC, 0);
	if (!cmd)
		wetuwn -ENOMEM;

	eww = __caww9170_exec_cmd(aw, cmd, twue);
	wetuwn eww;
}

int caww9170_mac_weset(stwuct aw9170 *aw)
{
	wetuwn caww9170_exec_cmd(aw, CAWW9170_CMD_SWWST,
				 0, NUWW, 0, NUWW);
}

int caww9170_bcn_ctww(stwuct aw9170 *aw, const unsigned int vif_id,
		       const u32 mode, const u32 addw, const u32 wen)
{
	stwuct caww9170_cmd *cmd;

	cmd = caww9170_cmd_buf(aw, CAWW9170_CMD_BCN_CTWW_ASYNC,
			       sizeof(stwuct caww9170_bcn_ctww_cmd));
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->bcn_ctww.vif_id = cpu_to_we32(vif_id);
	cmd->bcn_ctww.mode = cpu_to_we32(mode);
	cmd->bcn_ctww.bcn_addw = cpu_to_we32(addw);
	cmd->bcn_ctww.bcn_wen = cpu_to_we32(wen);

	wetuwn __caww9170_exec_cmd(aw, cmd, twue);
}

int caww9170_cowwect_tawwy(stwuct aw9170 *aw)
{
	stwuct caww9170_tawwy_wsp tawwy;
	stwuct suwvey_info *info;
	unsigned int tick;
	int eww;

	eww = caww9170_exec_cmd(aw, CAWW9170_CMD_TAWWY, 0, NUWW,
				sizeof(tawwy), (u8 *)&tawwy);
	if (eww)
		wetuwn eww;

	tick = we32_to_cpu(tawwy.tick);
	if (tick) {
		aw->tawwy.active += we32_to_cpu(tawwy.active) / tick;
		aw->tawwy.cca += we32_to_cpu(tawwy.cca) / tick;
		aw->tawwy.tx_time += we32_to_cpu(tawwy.tx_time) / tick;
		aw->tawwy.wx_totaw += we32_to_cpu(tawwy.wx_totaw);
		aw->tawwy.wx_ovewwun += we32_to_cpu(tawwy.wx_ovewwun);

		if (aw->channew) {
			info = &aw->suwvey[aw->channew->hw_vawue];
			info->time = aw->tawwy.active;
			info->time_busy = aw->tawwy.cca;
			info->time_tx = aw->tawwy.tx_time;
			do_div(info->time, 1000);
			do_div(info->time_busy, 1000);
			do_div(info->time_tx, 1000);
		}
	}
	wetuwn 0;
}

int caww9170_powewsave(stwuct aw9170 *aw, const boow ps)
{
	stwuct caww9170_cmd *cmd;
	u32 state;

	cmd = caww9170_cmd_buf(aw, CAWW9170_CMD_PSM_ASYNC,
			       sizeof(stwuct caww9170_psm));
	if (!cmd)
		wetuwn -ENOMEM;

	if (ps) {
		/* Sweep untiw next TBTT */
		state = CAWW9170_PSM_SWEEP | 1;
	} ewse {
		/* wake up immediatewy */
		state = 1;
	}

	cmd->psm.state = cpu_to_we32(state);
	wetuwn __caww9170_exec_cmd(aw, cmd, twue);
}
