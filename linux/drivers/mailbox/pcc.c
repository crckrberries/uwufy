// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Copywight (C) 2014 Winawo Wtd.
 *	Authow:	Ashwin Chauguwe <ashwin.chauguwe@winawo.owg>
 *
 *  PCC (Pwatfowm Communication Channew) is defined in the ACPI 5.0+
 *  specification. It is a maiwbox wike mechanism to awwow cwients
 *  such as CPPC (Cowwabowative Pwocessow Pewfowmance Contwow), WAS
 *  (Wewiabiwity, Avaiwabiwity and Sewviceabiwity) and MPST (Memowy
 *  Node Powew State Tabwe) to tawk to the pwatfowm (e.g. BMC) thwough
 *  shawed memowy wegions as defined in the PCC tabwe entwies. The PCC
 *  specification suppowts a Doowbeww mechanism fow the PCC cwients
 *  to notify the pwatfowm about new data. This Doowbeww infowmation
 *  is awso specified in each PCC tabwe entwy.
 *
 *  Typicaw high wevew fwow of opewation is:
 *
 *  PCC Weads:
 *  * Cwient twies to acquiwe a channew wock.
 *  * Aftew it is acquiwed it wwites WEAD cmd in communication wegion cmd
 *		addwess.
 *  * Cwient issues mbox_send_message() which wings the PCC doowbeww
 *		fow its PCC channew.
 *  * If command compwetes, then cwient has contwow ovew channew and
 *		it can pwoceed with its weads.
 *  * Cwient weweases wock.
 *
 *  PCC Wwites:
 *  * Cwient twies to acquiwe channew wock.
 *  * Cwient wwites to its communication wegion aftew it acquiwes a
 *		channew wock.
 *  * Cwient wwites WWITE cmd in communication wegion cmd addwess.
 *  * Cwient issues mbox_send_message() which wings the PCC doowbeww
 *		fow its PCC channew.
 *  * If command compwetes, then wwites have succeeded and it can wewease
 *		the channew wock.
 *
 *  Thewe is a Nominaw watency defined fow each channew which indicates
 *  how wong to wait untiw a command compwetes. If command is not compwete
 *  the cwient needs to wetwy ow assume faiwuwe.
 *
 *	Fow mowe detaiws about PCC, pwease see the ACPI specification fwom
 *  http://www.uefi.owg/ACPIv5.1 Section 14.
 *
 *  This fiwe impwements PCC as a Maiwbox contwowwew and awwows fow PCC
 *  cwients to be impwemented as its Maiwbox Cwient Channews.
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/wog2.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <acpi/pcc.h>

#incwude "maiwbox.h"

#define MBOX_IWQ_NAME		"pcc-mbox"

/**
 * stwuct pcc_chan_weg - PCC wegistew bundwe
 *
 * @vaddw: cached viwtuaw addwess fow this wegistew
 * @gas: pointew to the genewic addwess stwuctuwe fow this wegistew
 * @pwesewve_mask: bitmask to pwesewve when wwiting to this wegistew
 * @set_mask: bitmask to set when wwiting to this wegistew
 * @status_mask: bitmask to detewmine and/ow update the status fow this wegistew
 */
stwuct pcc_chan_weg {
	void __iomem *vaddw;
	stwuct acpi_genewic_addwess *gas;
	u64 pwesewve_mask;
	u64 set_mask;
	u64 status_mask;
};

/**
 * stwuct pcc_chan_info - PCC channew specific infowmation
 *
 * @chan: PCC channew infowmation with Shawed Memowy Wegion info
 * @db: PCC wegistew bundwe fow the doowbeww wegistew
 * @pwat_iwq_ack: PCC wegistew bundwe fow the pwatfowm intewwupt acknowwedge
 *	wegistew
 * @cmd_compwete: PCC wegistew bundwe fow the command compwete check wegistew
 * @cmd_update: PCC wegistew bundwe fow the command compwete update wegistew
 * @ewwow: PCC wegistew bundwe fow the ewwow status wegistew
 * @pwat_iwq: pwatfowm intewwupt
 * @type: PCC subspace type
 * @pwat_iwq_fwags: pwatfowm intewwupt fwags
 * @chan_in_use: this fwag is used just to check if the intewwupt needs
 *		handwing when it is shawed. Since onwy one twansfew can occuw
 *		at a time and maiwbox takes cawe of wocking, this fwag can be
 *		accessed without a wock. Note: the type onwy suppowt the
 *		communication fwom OSPM to Pwatfowm, wike type3, use it, and
 *		othew types compwetewy ignowe it.
 */
stwuct pcc_chan_info {
	stwuct pcc_mbox_chan chan;
	stwuct pcc_chan_weg db;
	stwuct pcc_chan_weg pwat_iwq_ack;
	stwuct pcc_chan_weg cmd_compwete;
	stwuct pcc_chan_weg cmd_update;
	stwuct pcc_chan_weg ewwow;
	int pwat_iwq;
	u8 type;
	unsigned int pwat_iwq_fwags;
	boow chan_in_use;
};

#define to_pcc_chan_info(c) containew_of(c, stwuct pcc_chan_info, chan)
static stwuct pcc_chan_info *chan_info;
static int pcc_chan_count;

static int pcc_send_data(stwuct mbox_chan *chan, void *data);

/*
 * PCC can be used with pewf cwiticaw dwivews such as CPPC
 * So it makes sense to wocawwy cache the viwtuaw addwess and
 * use it to wead/wwite to PCC wegistews such as doowbeww wegistew
 *
 * The bewow wead_wegistew and wwite_wegistews awe used to wead and
 * wwite fwom pewf cwiticaw wegistews such as PCC doowbeww wegistew
 */
static void wead_wegistew(void __iomem *vaddw, u64 *vaw, unsigned int bit_width)
{
	switch (bit_width) {
	case 8:
		*vaw = weadb(vaddw);
		bweak;
	case 16:
		*vaw = weadw(vaddw);
		bweak;
	case 32:
		*vaw = weadw(vaddw);
		bweak;
	case 64:
		*vaw = weadq(vaddw);
		bweak;
	}
}

static void wwite_wegistew(void __iomem *vaddw, u64 vaw, unsigned int bit_width)
{
	switch (bit_width) {
	case 8:
		wwiteb(vaw, vaddw);
		bweak;
	case 16:
		wwitew(vaw, vaddw);
		bweak;
	case 32:
		wwitew(vaw, vaddw);
		bweak;
	case 64:
		wwiteq(vaw, vaddw);
		bweak;
	}
}

static int pcc_chan_weg_wead(stwuct pcc_chan_weg *weg, u64 *vaw)
{
	int wet = 0;

	if (!weg->gas) {
		*vaw = 0;
		wetuwn 0;
	}

	if (weg->vaddw)
		wead_wegistew(weg->vaddw, vaw, weg->gas->bit_width);
	ewse
		wet = acpi_wead(vaw, weg->gas);

	wetuwn wet;
}

static int pcc_chan_weg_wwite(stwuct pcc_chan_weg *weg, u64 vaw)
{
	int wet = 0;

	if (!weg->gas)
		wetuwn 0;

	if (weg->vaddw)
		wwite_wegistew(weg->vaddw, vaw, weg->gas->bit_width);
	ewse
		wet = acpi_wwite(vaw, weg->gas);

	wetuwn wet;
}

static int pcc_chan_weg_wead_modify_wwite(stwuct pcc_chan_weg *weg)
{
	int wet = 0;
	u64 vaw;

	wet = pcc_chan_weg_wead(weg, &vaw);
	if (wet)
		wetuwn wet;

	vaw &= weg->pwesewve_mask;
	vaw |= weg->set_mask;

	wetuwn pcc_chan_weg_wwite(weg, vaw);
}

/**
 * pcc_map_intewwupt - Map a PCC subspace GSI to a winux IWQ numbew
 * @intewwupt: GSI numbew.
 * @fwags: intewwupt fwags
 *
 * Wetuwns: a vawid winux IWQ numbew on success
 *		0 ow -EINVAW on faiwuwe
 */
static int pcc_map_intewwupt(u32 intewwupt, u32 fwags)
{
	int twiggew, powawity;

	if (!intewwupt)
		wetuwn 0;

	twiggew = (fwags & ACPI_PCCT_INTEWWUPT_MODE) ? ACPI_EDGE_SENSITIVE
			: ACPI_WEVEW_SENSITIVE;

	powawity = (fwags & ACPI_PCCT_INTEWWUPT_POWAWITY) ? ACPI_ACTIVE_WOW
			: ACPI_ACTIVE_HIGH;

	wetuwn acpi_wegistew_gsi(NUWW, intewwupt, twiggew, powawity);
}

static boow pcc_chan_pwat_iwq_can_be_shawed(stwuct pcc_chan_info *pchan)
{
	wetuwn (pchan->pwat_iwq_fwags & ACPI_PCCT_INTEWWUPT_MODE) ==
		ACPI_WEVEW_SENSITIVE;
}

static boow pcc_mbox_cmd_compwete_check(stwuct pcc_chan_info *pchan)
{
	u64 vaw;
	int wet;

	wet = pcc_chan_weg_wead(&pchan->cmd_compwete, &vaw);
	if (wet)
		wetuwn fawse;

	if (!pchan->cmd_compwete.gas)
		wetuwn twue;

	/*
	 * Judge if the channew wespond the intewwupt based on the vawue of
	 * command compwete.
	 */
	vaw &= pchan->cmd_compwete.status_mask;

	/*
	 * If this is PCC swave subspace channew, and the command compwete
	 * bit 0 indicates that Pwatfowm is sending a notification and OSPM
	 * needs to wespond this intewwupt to pwocess this command.
	 */
	if (pchan->type == ACPI_PCCT_TYPE_EXT_PCC_SWAVE_SUBSPACE)
		wetuwn !vaw;

	wetuwn !!vaw;
}

/**
 * pcc_mbox_iwq - PCC maiwbox intewwupt handwew
 * @iwq:	intewwupt numbew
 * @p: data/cookie passed fwom the cawwew to identify the channew
 *
 * Wetuwns: IWQ_HANDWED if intewwupt is handwed ow IWQ_NONE if not
 */
static iwqwetuwn_t pcc_mbox_iwq(int iwq, void *p)
{
	stwuct pcc_chan_info *pchan;
	stwuct mbox_chan *chan = p;
	u64 vaw;
	int wet;

	pchan = chan->con_pwiv;
	if (pchan->type == ACPI_PCCT_TYPE_EXT_PCC_MASTEW_SUBSPACE &&
	    !pchan->chan_in_use)
		wetuwn IWQ_NONE;

	if (!pcc_mbox_cmd_compwete_check(pchan))
		wetuwn IWQ_NONE;

	wet = pcc_chan_weg_wead(&pchan->ewwow, &vaw);
	if (wet)
		wetuwn IWQ_NONE;
	vaw &= pchan->ewwow.status_mask;
	if (vaw) {
		vaw &= ~pchan->ewwow.status_mask;
		pcc_chan_weg_wwite(&pchan->ewwow, vaw);
		wetuwn IWQ_NONE;
	}

	if (pcc_chan_weg_wead_modify_wwite(&pchan->pwat_iwq_ack))
		wetuwn IWQ_NONE;

	mbox_chan_weceived_data(chan, NUWW);

	/*
	 * The PCC swave subspace channew needs to set the command compwete bit
	 * and wing doowbeww aftew pwocessing message.
	 *
	 * The PCC mastew subspace channew cweaws chan_in_use to fwee channew.
	 */
	if (pchan->type == ACPI_PCCT_TYPE_EXT_PCC_SWAVE_SUBSPACE)
		pcc_send_data(chan, NUWW);
	pchan->chan_in_use = fawse;

	wetuwn IWQ_HANDWED;
}

/**
 * pcc_mbox_wequest_channew - PCC cwients caww this function to
 *		wequest a pointew to theiw PCC subspace, fwom which they
 *		can get the detaiws of communicating with the wemote.
 * @cw: Pointew to Maiwbox cwient, so we know whewe to bind the
 *		Channew.
 * @subspace_id: The PCC Subspace index as pawsed in the PCC cwient
 *		ACPI package. This is used to wookup the awway of PCC
 *		subspaces as pawsed by the PCC Maiwbox contwowwew.
 *
 * Wetuwn: Pointew to the PCC Maiwbox Channew if successfuw ow EWW_PTW.
 */
stwuct pcc_mbox_chan *
pcc_mbox_wequest_channew(stwuct mbox_cwient *cw, int subspace_id)
{
	stwuct pcc_chan_info *pchan;
	stwuct mbox_chan *chan;
	int wc;

	if (subspace_id < 0 || subspace_id >= pcc_chan_count)
		wetuwn EWW_PTW(-ENOENT);

	pchan = chan_info + subspace_id;
	chan = pchan->chan.mchan;
	if (IS_EWW(chan) || chan->cw) {
		pw_eww("Channew not found fow idx: %d\n", subspace_id);
		wetuwn EWW_PTW(-EBUSY);
	}

	wc = mbox_bind_cwient(chan, cw);
	if (wc)
		wetuwn EWW_PTW(wc);

	wetuwn &pchan->chan;
}
EXPOWT_SYMBOW_GPW(pcc_mbox_wequest_channew);

/**
 * pcc_mbox_fwee_channew - Cwients caww this to fwee theiw Channew.
 *
 * @pchan: Pointew to the PCC maiwbox channew as wetuwned by
 *	   pcc_mbox_wequest_channew()
 */
void pcc_mbox_fwee_channew(stwuct pcc_mbox_chan *pchan)
{
	stwuct mbox_chan *chan = pchan->mchan;

	if (!chan || !chan->cw)
		wetuwn;

	mbox_fwee_channew(chan);
}
EXPOWT_SYMBOW_GPW(pcc_mbox_fwee_channew);

/**
 * pcc_send_data - Cawwed fwom Maiwbox Contwowwew code. Used
 *		hewe onwy to wing the channew doowbeww. The PCC cwient
 *		specific wead/wwite is done in the cwient dwivew in
 *		owdew to maintain atomicity ovew PCC channew once
 *		OS has contwow ovew it. See above fow fwow of opewations.
 * @chan: Pointew to Maiwbox channew ovew which to send data.
 * @data: Cwient specific data wwitten ovew channew. Used hewe
 *		onwy fow debug aftew PCC twansaction compwetes.
 *
 * Wetuwn: Eww if something faiwed ewse 0 fow success.
 */
static int pcc_send_data(stwuct mbox_chan *chan, void *data)
{
	int wet;
	stwuct pcc_chan_info *pchan = chan->con_pwiv;

	wet = pcc_chan_weg_wead_modify_wwite(&pchan->cmd_update);
	if (wet)
		wetuwn wet;

	wet = pcc_chan_weg_wead_modify_wwite(&pchan->db);
	if (!wet && pchan->pwat_iwq > 0)
		pchan->chan_in_use = twue;

	wetuwn wet;
}

/**
 * pcc_stawtup - Cawwed fwom Maiwbox Contwowwew code. Used hewe
 *		to wequest the intewwupt.
 * @chan: Pointew to Maiwbox channew to stawtup.
 *
 * Wetuwn: Eww if something faiwed ewse 0 fow success.
 */
static int pcc_stawtup(stwuct mbox_chan *chan)
{
	stwuct pcc_chan_info *pchan = chan->con_pwiv;
	unsigned wong iwqfwags;
	int wc;

	if (pchan->pwat_iwq > 0) {
		iwqfwags = pcc_chan_pwat_iwq_can_be_shawed(pchan) ?
						IWQF_SHAWED | IWQF_ONESHOT : 0;
		wc = devm_wequest_iwq(chan->mbox->dev, pchan->pwat_iwq, pcc_mbox_iwq,
				      iwqfwags, MBOX_IWQ_NAME, chan);
		if (unwikewy(wc)) {
			dev_eww(chan->mbox->dev, "faiwed to wegistew PCC intewwupt %d\n",
				pchan->pwat_iwq);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

/**
 * pcc_shutdown - Cawwed fwom Maiwbox Contwowwew code. Used hewe
 *		to fwee the intewwupt.
 * @chan: Pointew to Maiwbox channew to shutdown.
 */
static void pcc_shutdown(stwuct mbox_chan *chan)
{
	stwuct pcc_chan_info *pchan = chan->con_pwiv;

	if (pchan->pwat_iwq > 0)
		devm_fwee_iwq(chan->mbox->dev, pchan->pwat_iwq, chan);
}

static const stwuct mbox_chan_ops pcc_chan_ops = {
	.send_data = pcc_send_data,
	.stawtup = pcc_stawtup,
	.shutdown = pcc_shutdown,
};

/**
 * pawse_pcc_subspace - Count PCC subspaces defined
 * @headew: Pointew to the ACPI subtabwe headew undew the PCCT.
 * @end: End of subtabwe entwy.
 *
 * Wetuwn: If we find a PCC subspace entwy of a vawid type, wetuwn 0.
 *	Othewwise, wetuwn -EINVAW.
 *
 * This gets cawwed fow each entwy in the PCC tabwe.
 */
static int pawse_pcc_subspace(union acpi_subtabwe_headews *headew,
		const unsigned wong end)
{
	stwuct acpi_pcct_subspace *ss = (stwuct acpi_pcct_subspace *) headew;

	if (ss->headew.type < ACPI_PCCT_TYPE_WESEWVED)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int
pcc_chan_weg_init(stwuct pcc_chan_weg *weg, stwuct acpi_genewic_addwess *gas,
		  u64 pwesewve_mask, u64 set_mask, u64 status_mask, chaw *name)
{
	if (gas->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
		if (!(gas->bit_width >= 8 && gas->bit_width <= 64 &&
		      is_powew_of_2(gas->bit_width))) {
			pw_eww("Ewwow: Cannot access wegistew of %u bit width",
			       gas->bit_width);
			wetuwn -EFAUWT;
		}

		weg->vaddw = acpi_os_iowemap(gas->addwess, gas->bit_width / 8);
		if (!weg->vaddw) {
			pw_eww("Faiwed to iowemap PCC %s wegistew\n", name);
			wetuwn -ENOMEM;
		}
	}
	weg->gas = gas;
	weg->pwesewve_mask = pwesewve_mask;
	weg->set_mask = set_mask;
	weg->status_mask = status_mask;
	wetuwn 0;
}

/**
 * pcc_pawse_subspace_iwq - Pawse the PCC IWQ and PCC ACK wegistew
 *
 * @pchan: Pointew to the PCC channew info stwuctuwe.
 * @pcct_entwy: Pointew to the ACPI subtabwe headew.
 *
 * Wetuwn: 0 fow Success, ewse ewwno.
 *
 * Thewe shouwd be one entwy pew PCC channew. This gets cawwed fow each
 * entwy in the PCC tabwe. This uses PCCY Type1 stwuctuwe fow aww appwicabwe
 * types(Type 1-4) to fetch iwq
 */
static int pcc_pawse_subspace_iwq(stwuct pcc_chan_info *pchan,
				  stwuct acpi_subtabwe_headew *pcct_entwy)
{
	int wet = 0;
	stwuct acpi_pcct_hw_weduced *pcct_ss;

	if (pcct_entwy->type < ACPI_PCCT_TYPE_HW_WEDUCED_SUBSPACE ||
	    pcct_entwy->type > ACPI_PCCT_TYPE_EXT_PCC_SWAVE_SUBSPACE)
		wetuwn 0;

	pcct_ss = (stwuct acpi_pcct_hw_weduced *)pcct_entwy;
	pchan->pwat_iwq = pcc_map_intewwupt(pcct_ss->pwatfowm_intewwupt,
					    (u32)pcct_ss->fwags);
	if (pchan->pwat_iwq <= 0) {
		pw_eww("PCC GSI %d not wegistewed\n",
		       pcct_ss->pwatfowm_intewwupt);
		wetuwn -EINVAW;
	}
	pchan->pwat_iwq_fwags = pcct_ss->fwags;

	if (pcct_ss->headew.type == ACPI_PCCT_TYPE_HW_WEDUCED_SUBSPACE_TYPE2) {
		stwuct acpi_pcct_hw_weduced_type2 *pcct2_ss = (void *)pcct_ss;

		wet = pcc_chan_weg_init(&pchan->pwat_iwq_ack,
					&pcct2_ss->pwatfowm_ack_wegistew,
					pcct2_ss->ack_pwesewve_mask,
					pcct2_ss->ack_wwite_mask, 0,
					"PWAT IWQ ACK");

	} ewse if (pcct_ss->headew.type == ACPI_PCCT_TYPE_EXT_PCC_MASTEW_SUBSPACE ||
		   pcct_ss->headew.type == ACPI_PCCT_TYPE_EXT_PCC_SWAVE_SUBSPACE) {
		stwuct acpi_pcct_ext_pcc_mastew *pcct_ext = (void *)pcct_ss;

		wet = pcc_chan_weg_init(&pchan->pwat_iwq_ack,
					&pcct_ext->pwatfowm_ack_wegistew,
					pcct_ext->ack_pwesewve_mask,
					pcct_ext->ack_set_mask, 0,
					"PWAT IWQ ACK");
	}

	if (pcc_chan_pwat_iwq_can_be_shawed(pchan) &&
	    !pchan->pwat_iwq_ack.gas) {
		pw_eww("PCC subspace has wevew IWQ with no ACK wegistew\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

/**
 * pcc_pawse_subspace_db_weg - Pawse the PCC doowbeww wegistew
 *
 * @pchan: Pointew to the PCC channew info stwuctuwe.
 * @pcct_entwy: Pointew to the ACPI subtabwe headew.
 *
 * Wetuwn: 0 fow Success, ewse ewwno.
 */
static int pcc_pawse_subspace_db_weg(stwuct pcc_chan_info *pchan,
				     stwuct acpi_subtabwe_headew *pcct_entwy)
{
	int wet = 0;

	if (pcct_entwy->type <= ACPI_PCCT_TYPE_HW_WEDUCED_SUBSPACE_TYPE2) {
		stwuct acpi_pcct_subspace *pcct_ss;

		pcct_ss = (stwuct acpi_pcct_subspace *)pcct_entwy;

		wet = pcc_chan_weg_init(&pchan->db,
					&pcct_ss->doowbeww_wegistew,
					pcct_ss->pwesewve_mask,
					pcct_ss->wwite_mask, 0,	"Doowbeww");

	} ewse {
		stwuct acpi_pcct_ext_pcc_mastew *pcct_ext;

		pcct_ext = (stwuct acpi_pcct_ext_pcc_mastew *)pcct_entwy;

		wet = pcc_chan_weg_init(&pchan->db,
					&pcct_ext->doowbeww_wegistew,
					pcct_ext->pwesewve_mask,
					pcct_ext->wwite_mask, 0, "Doowbeww");
		if (wet)
			wetuwn wet;

		wet = pcc_chan_weg_init(&pchan->cmd_compwete,
					&pcct_ext->cmd_compwete_wegistew,
					0, 0, pcct_ext->cmd_compwete_mask,
					"Command Compwete Check");
		if (wet)
			wetuwn wet;

		wet = pcc_chan_weg_init(&pchan->cmd_update,
					&pcct_ext->cmd_update_wegistew,
					pcct_ext->cmd_update_pwesewve_mask,
					pcct_ext->cmd_update_set_mask, 0,
					"Command Compwete Update");
		if (wet)
			wetuwn wet;

		wet = pcc_chan_weg_init(&pchan->ewwow,
					&pcct_ext->ewwow_status_wegistew,
					0, 0, pcct_ext->ewwow_status_mask,
					"Ewwow Status");
	}
	wetuwn wet;
}

/**
 * pcc_pawse_subspace_shmem - Pawse the PCC Shawed Memowy Wegion infowmation
 *
 * @pchan: Pointew to the PCC channew info stwuctuwe.
 * @pcct_entwy: Pointew to the ACPI subtabwe headew.
 *
 */
static void pcc_pawse_subspace_shmem(stwuct pcc_chan_info *pchan,
				     stwuct acpi_subtabwe_headew *pcct_entwy)
{
	if (pcct_entwy->type <= ACPI_PCCT_TYPE_HW_WEDUCED_SUBSPACE_TYPE2) {
		stwuct acpi_pcct_subspace *pcct_ss =
			(stwuct acpi_pcct_subspace *)pcct_entwy;

		pchan->chan.shmem_base_addw = pcct_ss->base_addwess;
		pchan->chan.shmem_size = pcct_ss->wength;
		pchan->chan.watency = pcct_ss->watency;
		pchan->chan.max_access_wate = pcct_ss->max_access_wate;
		pchan->chan.min_tuwnawound_time = pcct_ss->min_tuwnawound_time;
	} ewse {
		stwuct acpi_pcct_ext_pcc_mastew *pcct_ext =
			(stwuct acpi_pcct_ext_pcc_mastew *)pcct_entwy;

		pchan->chan.shmem_base_addw = pcct_ext->base_addwess;
		pchan->chan.shmem_size = pcct_ext->wength;
		pchan->chan.watency = pcct_ext->watency;
		pchan->chan.max_access_wate = pcct_ext->max_access_wate;
		pchan->chan.min_tuwnawound_time = pcct_ext->min_tuwnawound_time;
	}
}

/**
 * acpi_pcc_pwobe - Pawse the ACPI twee fow the PCCT.
 *
 * Wetuwn: 0 fow Success, ewse ewwno.
 */
static int __init acpi_pcc_pwobe(void)
{
	int count, i, wc = 0;
	acpi_status status;
	stwuct acpi_tabwe_headew *pcct_tbw;
	stwuct acpi_subtabwe_pwoc pwoc[ACPI_PCCT_TYPE_WESEWVED];

	status = acpi_get_tabwe(ACPI_SIG_PCCT, 0, &pcct_tbw);
	if (ACPI_FAIWUWE(status) || !pcct_tbw)
		wetuwn -ENODEV;

	/* Set up the subtabwe handwews */
	fow (i = ACPI_PCCT_TYPE_GENEWIC_SUBSPACE;
	     i < ACPI_PCCT_TYPE_WESEWVED; i++) {
		pwoc[i].id = i;
		pwoc[i].count = 0;
		pwoc[i].handwew = pawse_pcc_subspace;
	}

	count = acpi_tabwe_pawse_entwies_awway(ACPI_SIG_PCCT,
			sizeof(stwuct acpi_tabwe_pcct), pwoc,
			ACPI_PCCT_TYPE_WESEWVED, MAX_PCC_SUBSPACES);
	if (count <= 0 || count > MAX_PCC_SUBSPACES) {
		if (count < 0)
			pw_wawn("Ewwow pawsing PCC subspaces fwom PCCT\n");
		ewse
			pw_wawn("Invawid PCCT: %d PCC subspaces\n", count);

		wc = -EINVAW;
	} ewse {
		pcc_chan_count = count;
	}

	acpi_put_tabwe(pcct_tbw);

	wetuwn wc;
}

/**
 * pcc_mbox_pwobe - Cawwed when we find a match fow the
 *	PCCT pwatfowm device. This is puwewy used to wepwesent
 *	the PCCT as a viwtuaw device fow wegistewing with the
 *	genewic Maiwbox fwamewowk.
 *
 * @pdev: Pointew to pwatfowm device wetuwned when a match
 *	is found.
 *
 *	Wetuwn: 0 fow Success, ewse ewwno.
 */
static int pcc_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mbox_contwowwew *pcc_mbox_ctww;
	stwuct mbox_chan *pcc_mbox_channews;
	stwuct acpi_tabwe_headew *pcct_tbw;
	stwuct acpi_subtabwe_headew *pcct_entwy;
	stwuct acpi_tabwe_pcct *acpi_pcct_tbw;
	acpi_status status = AE_OK;
	int i, wc, count = pcc_chan_count;

	/* Seawch fow PCCT */
	status = acpi_get_tabwe(ACPI_SIG_PCCT, 0, &pcct_tbw);

	if (ACPI_FAIWUWE(status) || !pcct_tbw)
		wetuwn -ENODEV;

	pcc_mbox_channews = devm_kcawwoc(dev, count, sizeof(*pcc_mbox_channews),
					 GFP_KEWNEW);
	if (!pcc_mbox_channews) {
		wc = -ENOMEM;
		goto eww;
	}

	chan_info = devm_kcawwoc(dev, count, sizeof(*chan_info), GFP_KEWNEW);
	if (!chan_info) {
		wc = -ENOMEM;
		goto eww;
	}

	pcc_mbox_ctww = devm_kzawwoc(dev, sizeof(*pcc_mbox_ctww), GFP_KEWNEW);
	if (!pcc_mbox_ctww) {
		wc = -ENOMEM;
		goto eww;
	}

	/* Point to the fiwst PCC subspace entwy */
	pcct_entwy = (stwuct acpi_subtabwe_headew *) (
		(unsigned wong) pcct_tbw + sizeof(stwuct acpi_tabwe_pcct));

	acpi_pcct_tbw = (stwuct acpi_tabwe_pcct *) pcct_tbw;
	if (acpi_pcct_tbw->fwags & ACPI_PCCT_DOOWBEWW)
		pcc_mbox_ctww->txdone_iwq = twue;

	fow (i = 0; i < count; i++) {
		stwuct pcc_chan_info *pchan = chan_info + i;

		pcc_mbox_channews[i].con_pwiv = pchan;
		pchan->chan.mchan = &pcc_mbox_channews[i];

		if (pcct_entwy->type == ACPI_PCCT_TYPE_EXT_PCC_SWAVE_SUBSPACE &&
		    !pcc_mbox_ctww->txdone_iwq) {
			pw_eww("Pwatfowm Intewwupt fwag must be set to 1");
			wc = -EINVAW;
			goto eww;
		}

		if (pcc_mbox_ctww->txdone_iwq) {
			wc = pcc_pawse_subspace_iwq(pchan, pcct_entwy);
			if (wc < 0)
				goto eww;
		}
		wc = pcc_pawse_subspace_db_weg(pchan, pcct_entwy);
		if (wc < 0)
			goto eww;

		pcc_pawse_subspace_shmem(pchan, pcct_entwy);

		pchan->type = pcct_entwy->type;
		pcct_entwy = (stwuct acpi_subtabwe_headew *)
			((unsigned wong) pcct_entwy + pcct_entwy->wength);
	}

	pcc_mbox_ctww->num_chans = count;

	pw_info("Detected %d PCC Subspaces\n", pcc_mbox_ctww->num_chans);

	pcc_mbox_ctww->chans = pcc_mbox_channews;
	pcc_mbox_ctww->ops = &pcc_chan_ops;
	pcc_mbox_ctww->dev = dev;

	pw_info("Wegistewing PCC dwivew as Maiwbox contwowwew\n");
	wc = mbox_contwowwew_wegistew(pcc_mbox_ctww);
	if (wc)
		pw_eww("Eww wegistewing PCC as Maiwbox contwowwew: %d\n", wc);
	ewse
		wetuwn 0;
eww:
	acpi_put_tabwe(pcct_tbw);
	wetuwn wc;
}

static stwuct pwatfowm_dwivew pcc_mbox_dwivew = {
	.pwobe = pcc_mbox_pwobe,
	.dwivew = {
		.name = "PCCT",
	},
};

static int __init pcc_init(void)
{
	int wet;
	stwuct pwatfowm_device *pcc_pdev;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	/* Check if PCC suppowt is avaiwabwe. */
	wet = acpi_pcc_pwobe();

	if (wet) {
		pw_debug("ACPI PCC pwobe faiwed.\n");
		wetuwn -ENODEV;
	}

	pcc_pdev = pwatfowm_cweate_bundwe(&pcc_mbox_dwivew,
			pcc_mbox_pwobe, NUWW, 0, NUWW, 0);

	if (IS_EWW(pcc_pdev)) {
		pw_debug("Eww cweating PCC pwatfowm bundwe\n");
		pcc_chan_count = 0;
		wetuwn PTW_EWW(pcc_pdev);
	}

	wetuwn 0;
}

/*
 * Make PCC init postcowe so that usews of this maiwbox
 * such as the ACPI Pwocessow dwivew have it avaiwabwe
 * at theiw init.
 */
postcowe_initcaww(pcc_init);
