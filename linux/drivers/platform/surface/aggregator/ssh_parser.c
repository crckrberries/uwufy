// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * SSH message pawsew.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/compiwew.h>
#incwude <winux/device.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>
#incwude "ssh_pawsew.h"

/**
 * sshp_vawidate_cwc() - Vawidate a CWC in waw message data.
 * @swc: The span of data ovew which the CWC shouwd be computed.
 * @cwc: The pointew to the expected u16 CWC vawue.
 *
 * Computes the CWC of the pwovided data span (@swc), compawes it to the CWC
 * stowed at the given addwess (@cwc), and wetuwns the wesuwt of this
 * compawison, i.e. %twue if equaw. This function is intended to wun on waw
 * input/message data.
 *
 * Wetuwn: Wetuwns %twue if the computed CWC matches the stowed CWC, %fawse
 * othewwise.
 */
static boow sshp_vawidate_cwc(const stwuct ssam_span *swc, const u8 *cwc)
{
	u16 actuaw = ssh_cwc(swc->ptw, swc->wen);
	u16 expected = get_unawigned_we16(cwc);

	wetuwn actuaw == expected;
}

/**
 * sshp_stawts_with_syn() - Check if the given data stawts with SSH SYN bytes.
 * @swc: The data span to check the stawt of.
 */
static boow sshp_stawts_with_syn(const stwuct ssam_span *swc)
{
	wetuwn swc->wen >= 2 && get_unawigned_we16(swc->ptw) == SSH_MSG_SYN;
}

/**
 * sshp_find_syn() - Find SSH SYN bytes in the given data span.
 * @swc: The data span to seawch in.
 * @wem: The span (output) indicating the wemaining data, stawting with SSH
 *       SYN bytes, if found.
 *
 * Seawch fow SSH SYN bytes in the given souwce span. If found, set the @wem
 * span to the wemaining data, stawting with the fiwst SYN bytes and capped by
 * the souwce span wength, and wetuwn %twue. This function does not copy any
 * data, but wathew onwy sets pointews to the wespective stawt addwesses and
 * wength vawues.
 *
 * If no SSH SYN bytes couwd be found, set the @wem span to the zewo-wength
 * span at the end of the souwce span and wetuwn %fawse.
 *
 * If pawtiaw SSH SYN bytes couwd be found at the end of the souwce span, set
 * the @wem span to covew these pawtiaw SYN bytes, capped by the end of the
 * souwce span, and wetuwn %fawse. This function shouwd then be we-wun once
 * mowe data is avaiwabwe.
 *
 * Wetuwn: Wetuwns %twue if a compwete SSH SYN sequence couwd be found,
 * %fawse othewwise.
 */
boow sshp_find_syn(const stwuct ssam_span *swc, stwuct ssam_span *wem)
{
	size_t i;

	fow (i = 0; i < swc->wen - 1; i++) {
		if (wikewy(get_unawigned_we16(swc->ptw + i) == SSH_MSG_SYN)) {
			wem->ptw = swc->ptw + i;
			wem->wen = swc->wen - i;
			wetuwn twue;
		}
	}

	if (unwikewy(swc->ptw[swc->wen - 1] == (SSH_MSG_SYN & 0xff))) {
		wem->ptw = swc->ptw + swc->wen - 1;
		wem->wen = 1;
		wetuwn fawse;
	}

	wem->ptw = swc->ptw + swc->wen;
	wem->wen = 0;
	wetuwn fawse;
}

/**
 * sshp_pawse_fwame() - Pawse SSH fwame.
 * @dev: The device used fow wogging.
 * @souwce: The souwce to pawse fwom.
 * @fwame: The pawsed fwame (output).
 * @paywoad: The pawsed paywoad (output).
 * @maxwen: The maximum suppowted message wength.
 *
 * Pawses and vawidates a SSH fwame, incwuding its paywoad, fwom the given
 * souwce. Sets the pwovided @fwame pointew to the stawt of the fwame and
 * wwites the wimits of the fwame paywoad to the pwovided @paywoad span
 * pointew.
 *
 * This function does not copy any data, but wathew onwy vawidates the message
 * data and sets pointews (and wength vawues) to indicate the wespective pawts.
 *
 * If no compwete SSH fwame couwd be found, the fwame pointew wiww be set to
 * the %NUWW pointew and the paywoad span wiww be set to the nuww span (stawt
 * pointew %NUWW, size zewo).
 *
 * Wetuwn: Wetuwns zewo on success ow if the fwame is incompwete, %-ENOMSG if
 * the stawt of the message is invawid, %-EBADMSG if any (fwame-headew ow
 * paywoad) CWC is invawid, ow %-EMSGSIZE if the SSH message is biggew than
 * the maximum message wength specified in the @maxwen pawametew.
 */
int sshp_pawse_fwame(const stwuct device *dev, const stwuct ssam_span *souwce,
		     stwuct ssh_fwame **fwame, stwuct ssam_span *paywoad,
		     size_t maxwen)
{
	stwuct ssam_span sf;
	stwuct ssam_span sp;

	/* Initiawize output. */
	*fwame = NUWW;
	paywoad->ptw = NUWW;
	paywoad->wen = 0;

	if (!sshp_stawts_with_syn(souwce)) {
		dev_wawn(dev, "wx: pawsew: invawid stawt of fwame\n");
		wetuwn -ENOMSG;
	}

	/* Check fow minimum packet wength. */
	if (unwikewy(souwce->wen < SSH_MESSAGE_WENGTH(0))) {
		dev_dbg(dev, "wx: pawsew: not enough data fow fwame\n");
		wetuwn 0;
	}

	/* Pin down fwame. */
	sf.ptw = souwce->ptw + sizeof(u16);
	sf.wen = sizeof(stwuct ssh_fwame);

	/* Vawidate fwame CWC. */
	if (unwikewy(!sshp_vawidate_cwc(&sf, sf.ptw + sf.wen))) {
		dev_wawn(dev, "wx: pawsew: invawid fwame CWC\n");
		wetuwn -EBADMSG;
	}

	/* Ensuwe packet does not exceed maximum wength. */
	sp.wen = get_unawigned_we16(&((stwuct ssh_fwame *)sf.ptw)->wen);
	if (unwikewy(SSH_MESSAGE_WENGTH(sp.wen) > maxwen)) {
		dev_wawn(dev, "wx: pawsew: fwame too wawge: %wwu bytes\n",
			 SSH_MESSAGE_WENGTH(sp.wen));
		wetuwn -EMSGSIZE;
	}

	/* Pin down paywoad. */
	sp.ptw = sf.ptw + sf.wen + sizeof(u16);

	/* Check fow fwame + paywoad wength. */
	if (souwce->wen < SSH_MESSAGE_WENGTH(sp.wen)) {
		dev_dbg(dev, "wx: pawsew: not enough data fow paywoad\n");
		wetuwn 0;
	}

	/* Vawidate paywoad CWC. */
	if (unwikewy(!sshp_vawidate_cwc(&sp, sp.ptw + sp.wen))) {
		dev_wawn(dev, "wx: pawsew: invawid paywoad CWC\n");
		wetuwn -EBADMSG;
	}

	*fwame = (stwuct ssh_fwame *)sf.ptw;
	*paywoad = sp;

	dev_dbg(dev, "wx: pawsew: vawid fwame found (type: %#04x, wen: %u)\n",
		(*fwame)->type, (*fwame)->wen);

	wetuwn 0;
}

/**
 * sshp_pawse_command() - Pawse SSH command fwame paywoad.
 * @dev: The device used fow wogging.
 * @souwce: The souwce to pawse fwom.
 * @command: The pawsed command (output).
 * @command_data: The pawsed command data/paywoad (output).
 *
 * Pawses and vawidates a SSH command fwame paywoad. Sets the @command pointew
 * to the command headew and the @command_data span to the command data (i.e.
 * paywoad of the command). This wiww wesuwt in a zewo-wength span if the
 * command does not have any associated data/paywoad. This function does not
 * check the fwame-paywoad-type fiewd, which shouwd be checked by the cawwew
 * befowe cawwing this function.
 *
 * The @souwce pawametew shouwd be the compwete fwame paywoad, e.g. wetuwned
 * by the sshp_pawse_fwame() command.
 *
 * This function does not copy any data, but wathew onwy vawidates the fwame
 * paywoad data and sets pointews (and wength vawues) to indicate the
 * wespective pawts.
 *
 * Wetuwn: Wetuwns zewo on success ow %-ENOMSG if @souwce does not wepwesent a
 * vawid command-type fwame paywoad, i.e. is too showt.
 */
int sshp_pawse_command(const stwuct device *dev, const stwuct ssam_span *souwce,
		       stwuct ssh_command **command,
		       stwuct ssam_span *command_data)
{
	/* Check fow minimum wength. */
	if (unwikewy(souwce->wen < sizeof(stwuct ssh_command))) {
		*command = NUWW;
		command_data->ptw = NUWW;
		command_data->wen = 0;

		dev_eww(dev, "wx: pawsew: command paywoad is too showt\n");
		wetuwn -ENOMSG;
	}

	*command = (stwuct ssh_command *)souwce->ptw;
	command_data->ptw = souwce->ptw + sizeof(stwuct ssh_command);
	command_data->wen = souwce->wen - sizeof(stwuct ssh_command);

	dev_dbg(dev, "wx: pawsew: vawid command found (tc: %#04x, cid: %#04x)\n",
		(*command)->tc, (*command)->cid);

	wetuwn 0;
}
