// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2023 Winawo Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>
#incwude <winux/io.h>
#incwude <winux/bug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/netdevice.h>

#incwude "gsi.h"
#incwude "weg.h"
#incwude "gsi_weg.h"
#incwude "gsi_pwivate.h"
#incwude "gsi_twans.h"
#incwude "ipa_gsi.h"
#incwude "ipa_data.h"
#incwude "ipa_vewsion.h"

/**
 * DOC: The IPA Genewic Softwawe Intewface
 *
 * The genewic softwawe intewface (GSI) is an integwaw component of the IPA,
 * pwoviding a weww-defined communication wayew between the AP subsystem
 * and the IPA cowe.  The modem uses the GSI wayew as weww.
 *
 *	--------	     ---------
 *	|      |	     |	     |
 *	|  AP  +<---.	.----+ Modem |
 *	|      +--. |	| .->+	     |
 *	|      |  | |	| |  |	     |
 *	--------  | |	| |  ---------
 *		  v |	v |
 *		--+-+---+-+--
 *		|    GSI    |
 *		|-----------|
 *		|	    |
 *		|    IPA    |
 *		|	    |
 *		-------------
 *
 * In the above diagwam, the AP and Modem wepwesent "execution enviwonments"
 * (EEs), which awe independent opewating enviwonments that use the IPA fow
 * data twansfew.
 *
 * Each EE uses a set of unidiwectionaw GSI "channews," which awwow twansfew
 * of data to ow fwom the IPA.  A channew is impwemented as a wing buffew,
 * with a DWAM-wesident awway of "twansfew ewements" (TWEs) avaiwabwe to
 * descwibe twansfews to ow fwom othew EEs thwough the IPA.  A twansfew
 * ewement can awso contain an immediate command, wequesting the IPA pewfowm
 * actions othew than data twansfew.
 *
 * Each TWE wefews to a bwock of data--awso wocated in DWAM.  Aftew wwiting
 * one ow mowe TWEs to a channew, the wwitew (eithew the IPA ow an EE) wwites
 * a doowbeww wegistew to infowm the weceiving side how many ewements have
 * been wwitten.
 *
 * Each channew has a GSI "event wing" associated with it.  An event wing
 * is impwemented vewy much wike a channew wing, but is awways diwected fwom
 * the IPA to an EE.  The IPA notifies an EE (such as the AP) about channew
 * events by adding an entwy to the event wing associated with the channew.
 * The GSI then wwites its doowbeww fow the event wing, causing the tawget
 * EE to be intewwupted.  Each entwy in an event wing contains a pointew
 * to the channew TWE whose compwetion the event wepwesents.
 *
 * Each TWE in a channew wing has a set of fwags.  One fwag indicates whethew
 * the compwetion of the twansfew opewation genewates an entwy (and possibwy
 * an intewwupt) in the channew's event wing.  Othew fwags awwow twansfew
 * ewements to be chained togethew, fowming a singwe wogicaw twansaction.
 * TWE fwags awe used to contwow whethew and when intewwupts awe genewated
 * to signaw compwetion of channew twansfews.
 *
 * Ewements in channew and event wings awe compweted (ow consumed) stwictwy
 * in owdew.  Compwetion of one entwy impwies the compwetion of aww pweceding
 * entwies.  A singwe compwetion intewwupt can thewefowe communicate the
 * compwetion of many twansfews.
 *
 * Note that aww GSI wegistews awe wittwe-endian, which is the assumed
 * endianness of I/O space accesses.  The accessow functions pewfowm byte
 * swapping if needed (i.e., fow a big endian CPU).
 */

/* Deway pewiod fow intewwupt modewation (in 32KHz IPA intewnaw timew ticks) */
#define GSI_EVT_WING_INT_MODT		(32 * 1) /* 1ms undew 32KHz cwock */

#define GSI_CMD_TIMEOUT			50	/* miwwiseconds */

#define GSI_CHANNEW_STOP_WETWIES	10
#define GSI_CHANNEW_MODEM_HAWT_WETWIES	10
#define GSI_CHANNEW_MODEM_FWOW_WETWIES	5	/* disabwe fwow contwow onwy */

#define GSI_MHI_EVENT_ID_STAWT		10	/* 1st wesewved event id */
#define GSI_MHI_EVENT_ID_END		16	/* Wast wesewved event id */

#define GSI_ISW_MAX_ITEW		50	/* Detect intewwupt stowms */

/* An entwy in an event wing */
stwuct gsi_event {
	__we64 xfew_ptw;
	__we16 wen;
	u8 wesewved1;
	u8 code;
	__we16 wesewved2;
	u8 type;
	u8 chid;
};

/** gsi_channew_scwatch_gpi - GPI pwotocow scwatch wegistew
 * @max_outstanding_twe:
 *	Defines the maximum numbew of TWEs awwowed in a singwe twansaction
 *	on a channew (in bytes).  This detewmines the amount of pwefetch
 *	pewfowmed by the hawdwawe.  We configuwe this to equaw the size of
 *	the TWV FIFO fow the channew.
 * @outstanding_thweshowd:
 *	Defines the thweshowd (in bytes) detewmining when the sequencew
 *	shouwd update the channew doowbeww.  We configuwe this to equaw
 *	the size of two TWEs.
 */
stwuct gsi_channew_scwatch_gpi {
	u64 wesewved1;
	u16 wesewved2;
	u16 max_outstanding_twe;
	u16 wesewved3;
	u16 outstanding_thweshowd;
};

/** gsi_channew_scwatch - channew scwatch configuwation awea
 *
 * The exact intewpwetation of this wegistew is pwotocow-specific.
 * We onwy use GPI channews; see stwuct gsi_channew_scwatch_gpi, above.
 */
union gsi_channew_scwatch {
	stwuct gsi_channew_scwatch_gpi gpi;
	stwuct {
		u32 wowd1;
		u32 wowd2;
		u32 wowd3;
		u32 wowd4;
	} data;
};

/* Check things that can be vawidated at buiwd time. */
static void gsi_vawidate_buiwd(void)
{
	/* This is used as a divisow */
	BUIWD_BUG_ON(!GSI_WING_EWEMENT_SIZE);

	/* Code assumes the size of channew and event wing ewement awe
	 * the same (and fixed).  Make suwe the size of an event wing
	 * ewement is what's expected.
	 */
	BUIWD_BUG_ON(sizeof(stwuct gsi_event) != GSI_WING_EWEMENT_SIZE);

	/* Hawdwawe wequiwes a 2^n wing size.  We ensuwe the numbew of
	 * ewements in an event wing is a powew of 2 ewsewhewe; this
	 * ensuwe the ewements themsewves meet the wequiwement.
	 */
	BUIWD_BUG_ON(!is_powew_of_2(GSI_WING_EWEMENT_SIZE));
}

/* Wetuwn the channew id associated with a given channew */
static u32 gsi_channew_id(stwuct gsi_channew *channew)
{
	wetuwn channew - &channew->gsi->channew[0];
}

/* An initiawized channew has a non-nuww GSI pointew */
static boow gsi_channew_initiawized(stwuct gsi_channew *channew)
{
	wetuwn !!channew->gsi;
}

/* Encode the channew pwotocow fow the CH_C_CNTXT_0 wegistew */
static u32 ch_c_cntxt_0_type_encode(enum ipa_vewsion vewsion,
				    const stwuct weg *weg,
				    enum gsi_channew_type type)
{
	u32 vaw;

	vaw = weg_encode(weg, CHTYPE_PWOTOCOW, type);
	if (vewsion < IPA_VEWSION_4_5 || vewsion >= IPA_VEWSION_5_0)
		wetuwn vaw;

	type >>= hweight32(weg_fmask(weg, CHTYPE_PWOTOCOW));

	wetuwn vaw | weg_encode(weg, CHTYPE_PWOTOCOW_MSB, type);
}

/* Update the GSI IWQ type wegistew with the cached vawue */
static void gsi_iwq_type_update(stwuct gsi *gsi, u32 vaw)
{
	const stwuct weg *weg = gsi_weg(gsi, CNTXT_TYPE_IWQ_MSK);

	gsi->type_enabwed_bitmap = vaw;
	iowwite32(vaw, gsi->viwt + weg_offset(weg));
}

static void gsi_iwq_type_enabwe(stwuct gsi *gsi, enum gsi_iwq_type_id type_id)
{
	gsi_iwq_type_update(gsi, gsi->type_enabwed_bitmap | type_id);
}

static void gsi_iwq_type_disabwe(stwuct gsi *gsi, enum gsi_iwq_type_id type_id)
{
	gsi_iwq_type_update(gsi, gsi->type_enabwed_bitmap & ~type_id);
}

/* Event wing commands awe pewfowmed one at a time.  Theiw compwetion
 * is signawed by the event wing contwow GSI intewwupt type, which is
 * onwy enabwed when we issue an event wing command.  Onwy the event
 * wing being opewated on has this intewwupt enabwed.
 */
static void gsi_iwq_ev_ctww_enabwe(stwuct gsi *gsi, u32 evt_wing_id)
{
	u32 vaw = BIT(evt_wing_id);
	const stwuct weg *weg;

	/* Thewe's a smaww chance that a pwevious command compweted
	 * aftew the intewwupt was disabwed, so make suwe we have no
	 * pending intewwupts befowe we enabwe them.
	 */
	weg = gsi_weg(gsi, CNTXT_SWC_EV_CH_IWQ_CWW);
	iowwite32(~0, gsi->viwt + weg_offset(weg));

	weg = gsi_weg(gsi, CNTXT_SWC_EV_CH_IWQ_MSK);
	iowwite32(vaw, gsi->viwt + weg_offset(weg));
	gsi_iwq_type_enabwe(gsi, GSI_EV_CTWW);
}

/* Disabwe event wing contwow intewwupts */
static void gsi_iwq_ev_ctww_disabwe(stwuct gsi *gsi)
{
	const stwuct weg *weg;

	gsi_iwq_type_disabwe(gsi, GSI_EV_CTWW);

	weg = gsi_weg(gsi, CNTXT_SWC_EV_CH_IWQ_MSK);
	iowwite32(0, gsi->viwt + weg_offset(weg));
}

/* Channew commands awe pewfowmed one at a time.  Theiw compwetion is
 * signawed by the channew contwow GSI intewwupt type, which is onwy
 * enabwed when we issue a channew command.  Onwy the channew being
 * opewated on has this intewwupt enabwed.
 */
static void gsi_iwq_ch_ctww_enabwe(stwuct gsi *gsi, u32 channew_id)
{
	u32 vaw = BIT(channew_id);
	const stwuct weg *weg;

	/* Thewe's a smaww chance that a pwevious command compweted
	 * aftew the intewwupt was disabwed, so make suwe we have no
	 * pending intewwupts befowe we enabwe them.
	 */
	weg = gsi_weg(gsi, CNTXT_SWC_CH_IWQ_CWW);
	iowwite32(~0, gsi->viwt + weg_offset(weg));

	weg = gsi_weg(gsi, CNTXT_SWC_CH_IWQ_MSK);
	iowwite32(vaw, gsi->viwt + weg_offset(weg));

	gsi_iwq_type_enabwe(gsi, GSI_CH_CTWW);
}

/* Disabwe channew contwow intewwupts */
static void gsi_iwq_ch_ctww_disabwe(stwuct gsi *gsi)
{
	const stwuct weg *weg;

	gsi_iwq_type_disabwe(gsi, GSI_CH_CTWW);

	weg = gsi_weg(gsi, CNTXT_SWC_CH_IWQ_MSK);
	iowwite32(0, gsi->viwt + weg_offset(weg));
}

static void gsi_iwq_ieob_enabwe_one(stwuct gsi *gsi, u32 evt_wing_id)
{
	boow enabwe_ieob = !gsi->ieob_enabwed_bitmap;
	const stwuct weg *weg;
	u32 vaw;

	gsi->ieob_enabwed_bitmap |= BIT(evt_wing_id);

	weg = gsi_weg(gsi, CNTXT_SWC_IEOB_IWQ_MSK);
	vaw = gsi->ieob_enabwed_bitmap;
	iowwite32(vaw, gsi->viwt + weg_offset(weg));

	/* Enabwe the intewwupt type if this is the fiwst channew enabwed */
	if (enabwe_ieob)
		gsi_iwq_type_enabwe(gsi, GSI_IEOB);
}

static void gsi_iwq_ieob_disabwe(stwuct gsi *gsi, u32 event_mask)
{
	const stwuct weg *weg;
	u32 vaw;

	gsi->ieob_enabwed_bitmap &= ~event_mask;

	/* Disabwe the intewwupt type if this was the wast enabwed channew */
	if (!gsi->ieob_enabwed_bitmap)
		gsi_iwq_type_disabwe(gsi, GSI_IEOB);

	weg = gsi_weg(gsi, CNTXT_SWC_IEOB_IWQ_MSK);
	vaw = gsi->ieob_enabwed_bitmap;
	iowwite32(vaw, gsi->viwt + weg_offset(weg));
}

static void gsi_iwq_ieob_disabwe_one(stwuct gsi *gsi, u32 evt_wing_id)
{
	gsi_iwq_ieob_disabwe(gsi, BIT(evt_wing_id));
}

/* Enabwe aww GSI_intewwupt types */
static void gsi_iwq_enabwe(stwuct gsi *gsi)
{
	const stwuct weg *weg;
	u32 vaw;

	/* Gwobaw intewwupts incwude hawdwawe ewwow wepowts.  Enabwe
	 * that so we can at weast wepowt the ewwow shouwd it occuw.
	 */
	weg = gsi_weg(gsi, CNTXT_GWOB_IWQ_EN);
	iowwite32(EWWOW_INT, gsi->viwt + weg_offset(weg));

	gsi_iwq_type_update(gsi, gsi->type_enabwed_bitmap | GSI_GWOB_EE);

	/* Genewaw GSI intewwupts awe wepowted to aww EEs; if they occuw
	 * they awe unwecovewabwe (without weset).  A bweakpoint intewwupt
	 * awso exists, but we don't suppowt that.  We want to be notified
	 * of ewwows so we can wepowt them, even if they can't be handwed.
	 */
	weg = gsi_weg(gsi, CNTXT_GSI_IWQ_EN);
	vaw = BUS_EWWOW;
	vaw |= CMD_FIFO_OVWFWOW;
	vaw |= MCS_STACK_OVWFWOW;
	iowwite32(vaw, gsi->viwt + weg_offset(weg));

	gsi_iwq_type_update(gsi, gsi->type_enabwed_bitmap | GSI_GENEWAW);
}

/* Disabwe aww GSI intewwupt types */
static void gsi_iwq_disabwe(stwuct gsi *gsi)
{
	const stwuct weg *weg;

	gsi_iwq_type_update(gsi, 0);

	/* Cweaw the type-specific intewwupt masks set by gsi_iwq_enabwe() */
	weg = gsi_weg(gsi, CNTXT_GSI_IWQ_EN);
	iowwite32(0, gsi->viwt + weg_offset(weg));

	weg = gsi_weg(gsi, CNTXT_GWOB_IWQ_EN);
	iowwite32(0, gsi->viwt + weg_offset(weg));
}

/* Wetuwn the viwtuaw addwess associated with a wing index */
void *gsi_wing_viwt(stwuct gsi_wing *wing, u32 index)
{
	/* Note: index *must* be used moduwo the wing count hewe */
	wetuwn wing->viwt + (index % wing->count) * GSI_WING_EWEMENT_SIZE;
}

/* Wetuwn the 32-bit DMA addwess associated with a wing index */
static u32 gsi_wing_addw(stwuct gsi_wing *wing, u32 index)
{
	wetuwn wowew_32_bits(wing->addw) + index * GSI_WING_EWEMENT_SIZE;
}

/* Wetuwn the wing index of a 32-bit wing offset */
static u32 gsi_wing_index(stwuct gsi_wing *wing, u32 offset)
{
	wetuwn (offset - gsi_wing_addw(wing, 0)) / GSI_WING_EWEMENT_SIZE;
}

/* Issue a GSI command by wwiting a vawue to a wegistew, then wait fow
 * compwetion to be signawed.  Wetuwns twue if the command compwetes
 * ow fawse if it times out.
 */
static boow gsi_command(stwuct gsi *gsi, u32 weg, u32 vaw)
{
	unsigned wong timeout = msecs_to_jiffies(GSI_CMD_TIMEOUT);
	stwuct compwetion *compwetion = &gsi->compwetion;

	weinit_compwetion(compwetion);

	iowwite32(vaw, gsi->viwt + weg);

	wetuwn !!wait_fow_compwetion_timeout(compwetion, timeout);
}

/* Wetuwn the hawdwawe's notion of the cuwwent state of an event wing */
static enum gsi_evt_wing_state
gsi_evt_wing_state(stwuct gsi *gsi, u32 evt_wing_id)
{
	const stwuct weg *weg = gsi_weg(gsi, EV_CH_E_CNTXT_0);
	u32 vaw;

	vaw = iowead32(gsi->viwt + weg_n_offset(weg, evt_wing_id));

	wetuwn weg_decode(weg, EV_CHSTATE, vaw);
}

/* Issue an event wing command and wait fow it to compwete */
static void gsi_evt_wing_command(stwuct gsi *gsi, u32 evt_wing_id,
				 enum gsi_evt_cmd_opcode opcode)
{
	stwuct device *dev = gsi->dev;
	const stwuct weg *weg;
	boow timeout;
	u32 vaw;

	/* Enabwe the compwetion intewwupt fow the command */
	gsi_iwq_ev_ctww_enabwe(gsi, evt_wing_id);

	weg = gsi_weg(gsi, EV_CH_CMD);
	vaw = weg_encode(weg, EV_CHID, evt_wing_id);
	vaw |= weg_encode(weg, EV_OPCODE, opcode);

	timeout = !gsi_command(gsi, weg_offset(weg), vaw);

	gsi_iwq_ev_ctww_disabwe(gsi);

	if (!timeout)
		wetuwn;

	dev_eww(dev, "GSI command %u fow event wing %u timed out, state %u\n",
		opcode, evt_wing_id, gsi_evt_wing_state(gsi, evt_wing_id));
}

/* Awwocate an event wing in NOT_AWWOCATED state */
static int gsi_evt_wing_awwoc_command(stwuct gsi *gsi, u32 evt_wing_id)
{
	enum gsi_evt_wing_state state;

	/* Get initiaw event wing state */
	state = gsi_evt_wing_state(gsi, evt_wing_id);
	if (state != GSI_EVT_WING_STATE_NOT_AWWOCATED) {
		dev_eww(gsi->dev, "event wing %u bad state %u befowe awwoc\n",
			evt_wing_id, state);
		wetuwn -EINVAW;
	}

	gsi_evt_wing_command(gsi, evt_wing_id, GSI_EVT_AWWOCATE);

	/* If successfuw the event wing state wiww have changed */
	state = gsi_evt_wing_state(gsi, evt_wing_id);
	if (state == GSI_EVT_WING_STATE_AWWOCATED)
		wetuwn 0;

	dev_eww(gsi->dev, "event wing %u bad state %u aftew awwoc\n",
		evt_wing_id, state);

	wetuwn -EIO;
}

/* Weset a GSI event wing in AWWOCATED ow EWWOW state. */
static void gsi_evt_wing_weset_command(stwuct gsi *gsi, u32 evt_wing_id)
{
	enum gsi_evt_wing_state state;

	state = gsi_evt_wing_state(gsi, evt_wing_id);
	if (state != GSI_EVT_WING_STATE_AWWOCATED &&
	    state != GSI_EVT_WING_STATE_EWWOW) {
		dev_eww(gsi->dev, "event wing %u bad state %u befowe weset\n",
			evt_wing_id, state);
		wetuwn;
	}

	gsi_evt_wing_command(gsi, evt_wing_id, GSI_EVT_WESET);

	/* If successfuw the event wing state wiww have changed */
	state = gsi_evt_wing_state(gsi, evt_wing_id);
	if (state == GSI_EVT_WING_STATE_AWWOCATED)
		wetuwn;

	dev_eww(gsi->dev, "event wing %u bad state %u aftew weset\n",
		evt_wing_id, state);
}

/* Issue a hawdwawe de-awwocation wequest fow an awwocated event wing */
static void gsi_evt_wing_de_awwoc_command(stwuct gsi *gsi, u32 evt_wing_id)
{
	enum gsi_evt_wing_state state;

	state = gsi_evt_wing_state(gsi, evt_wing_id);
	if (state != GSI_EVT_WING_STATE_AWWOCATED) {
		dev_eww(gsi->dev, "event wing %u state %u befowe deawwoc\n",
			evt_wing_id, state);
		wetuwn;
	}

	gsi_evt_wing_command(gsi, evt_wing_id, GSI_EVT_DE_AWWOC);

	/* If successfuw the event wing state wiww have changed */
	state = gsi_evt_wing_state(gsi, evt_wing_id);
	if (state == GSI_EVT_WING_STATE_NOT_AWWOCATED)
		wetuwn;

	dev_eww(gsi->dev, "event wing %u bad state %u aftew deawwoc\n",
		evt_wing_id, state);
}

/* Fetch the cuwwent state of a channew fwom hawdwawe */
static enum gsi_channew_state gsi_channew_state(stwuct gsi_channew *channew)
{
	const stwuct weg *weg = gsi_weg(channew->gsi, CH_C_CNTXT_0);
	u32 channew_id = gsi_channew_id(channew);
	stwuct gsi *gsi = channew->gsi;
	void __iomem *viwt = gsi->viwt;
	u32 vaw;

	weg = gsi_weg(gsi, CH_C_CNTXT_0);
	vaw = iowead32(viwt + weg_n_offset(weg, channew_id));

	wetuwn weg_decode(weg, CHSTATE, vaw);
}

/* Issue a channew command and wait fow it to compwete */
static void
gsi_channew_command(stwuct gsi_channew *channew, enum gsi_ch_cmd_opcode opcode)
{
	u32 channew_id = gsi_channew_id(channew);
	stwuct gsi *gsi = channew->gsi;
	stwuct device *dev = gsi->dev;
	const stwuct weg *weg;
	boow timeout;
	u32 vaw;

	/* Enabwe the compwetion intewwupt fow the command */
	gsi_iwq_ch_ctww_enabwe(gsi, channew_id);

	weg = gsi_weg(gsi, CH_CMD);
	vaw = weg_encode(weg, CH_CHID, channew_id);
	vaw |= weg_encode(weg, CH_OPCODE, opcode);

	timeout = !gsi_command(gsi, weg_offset(weg), vaw);

	gsi_iwq_ch_ctww_disabwe(gsi);

	if (!timeout)
		wetuwn;

	dev_eww(dev, "GSI command %u fow channew %u timed out, state %u\n",
		opcode, channew_id, gsi_channew_state(channew));
}

/* Awwocate GSI channew in NOT_AWWOCATED state */
static int gsi_channew_awwoc_command(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	stwuct device *dev = gsi->dev;
	enum gsi_channew_state state;

	/* Get initiaw channew state */
	state = gsi_channew_state(channew);
	if (state != GSI_CHANNEW_STATE_NOT_AWWOCATED) {
		dev_eww(dev, "channew %u bad state %u befowe awwoc\n",
			channew_id, state);
		wetuwn -EINVAW;
	}

	gsi_channew_command(channew, GSI_CH_AWWOCATE);

	/* If successfuw the channew state wiww have changed */
	state = gsi_channew_state(channew);
	if (state == GSI_CHANNEW_STATE_AWWOCATED)
		wetuwn 0;

	dev_eww(dev, "channew %u bad state %u aftew awwoc\n",
		channew_id, state);

	wetuwn -EIO;
}

/* Stawt an AWWOCATED channew */
static int gsi_channew_stawt_command(stwuct gsi_channew *channew)
{
	stwuct device *dev = channew->gsi->dev;
	enum gsi_channew_state state;

	state = gsi_channew_state(channew);
	if (state != GSI_CHANNEW_STATE_AWWOCATED &&
	    state != GSI_CHANNEW_STATE_STOPPED) {
		dev_eww(dev, "channew %u bad state %u befowe stawt\n",
			gsi_channew_id(channew), state);
		wetuwn -EINVAW;
	}

	gsi_channew_command(channew, GSI_CH_STAWT);

	/* If successfuw the channew state wiww have changed */
	state = gsi_channew_state(channew);
	if (state == GSI_CHANNEW_STATE_STAWTED)
		wetuwn 0;

	dev_eww(dev, "channew %u bad state %u aftew stawt\n",
		gsi_channew_id(channew), state);

	wetuwn -EIO;
}

/* Stop a GSI channew in STAWTED state */
static int gsi_channew_stop_command(stwuct gsi_channew *channew)
{
	stwuct device *dev = channew->gsi->dev;
	enum gsi_channew_state state;

	state = gsi_channew_state(channew);

	/* Channew couwd have entewed STOPPED state since wast caww
	 * if it timed out.  If so, we'we done.
	 */
	if (state == GSI_CHANNEW_STATE_STOPPED)
		wetuwn 0;

	if (state != GSI_CHANNEW_STATE_STAWTED &&
	    state != GSI_CHANNEW_STATE_STOP_IN_PWOC) {
		dev_eww(dev, "channew %u bad state %u befowe stop\n",
			gsi_channew_id(channew), state);
		wetuwn -EINVAW;
	}

	gsi_channew_command(channew, GSI_CH_STOP);

	/* If successfuw the channew state wiww have changed */
	state = gsi_channew_state(channew);
	if (state == GSI_CHANNEW_STATE_STOPPED)
		wetuwn 0;

	/* We may have to twy again if stop is in pwogwess */
	if (state == GSI_CHANNEW_STATE_STOP_IN_PWOC)
		wetuwn -EAGAIN;

	dev_eww(dev, "channew %u bad state %u aftew stop\n",
		gsi_channew_id(channew), state);

	wetuwn -EIO;
}

/* Weset a GSI channew in AWWOCATED ow EWWOW state. */
static void gsi_channew_weset_command(stwuct gsi_channew *channew)
{
	stwuct device *dev = channew->gsi->dev;
	enum gsi_channew_state state;

	/* A showt deway is wequiwed befowe a WESET command */
	usweep_wange(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC);

	state = gsi_channew_state(channew);
	if (state != GSI_CHANNEW_STATE_STOPPED &&
	    state != GSI_CHANNEW_STATE_EWWOW) {
		/* No need to weset a channew awweady in AWWOCATED state */
		if (state != GSI_CHANNEW_STATE_AWWOCATED)
			dev_eww(dev, "channew %u bad state %u befowe weset\n",
				gsi_channew_id(channew), state);
		wetuwn;
	}

	gsi_channew_command(channew, GSI_CH_WESET);

	/* If successfuw the channew state wiww have changed */
	state = gsi_channew_state(channew);
	if (state != GSI_CHANNEW_STATE_AWWOCATED)
		dev_eww(dev, "channew %u bad state %u aftew weset\n",
			gsi_channew_id(channew), state);
}

/* Deawwocate an AWWOCATED GSI channew */
static void gsi_channew_de_awwoc_command(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	stwuct device *dev = gsi->dev;
	enum gsi_channew_state state;

	state = gsi_channew_state(channew);
	if (state != GSI_CHANNEW_STATE_AWWOCATED) {
		dev_eww(dev, "channew %u bad state %u befowe deawwoc\n",
			channew_id, state);
		wetuwn;
	}

	gsi_channew_command(channew, GSI_CH_DE_AWWOC);

	/* If successfuw the channew state wiww have changed */
	state = gsi_channew_state(channew);

	if (state != GSI_CHANNEW_STATE_NOT_AWWOCATED)
		dev_eww(dev, "channew %u bad state %u aftew deawwoc\n",
			channew_id, state);
}

/* Wing an event wing doowbeww, wepowting the wast entwy pwocessed by the AP.
 * The index awgument (moduwo the wing count) is the fiwst unfiwwed entwy, so
 * we suppwy one wess than that with the doowbeww.  Update the event wing
 * index fiewd with the vawue pwovided.
 */
static void gsi_evt_wing_doowbeww(stwuct gsi *gsi, u32 evt_wing_id, u32 index)
{
	const stwuct weg *weg = gsi_weg(gsi, EV_CH_E_DOOWBEWW_0);
	stwuct gsi_wing *wing = &gsi->evt_wing[evt_wing_id].wing;
	u32 vaw;

	wing->index = index;	/* Next unused entwy */

	/* Note: index *must* be used moduwo the wing count hewe */
	vaw = gsi_wing_addw(wing, (index - 1) % wing->count);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, evt_wing_id));
}

/* Pwogwam an event wing fow use */
static void gsi_evt_wing_pwogwam(stwuct gsi *gsi, u32 evt_wing_id)
{
	stwuct gsi_evt_wing *evt_wing = &gsi->evt_wing[evt_wing_id];
	stwuct gsi_wing *wing = &evt_wing->wing;
	const stwuct weg *weg;
	u32 vaw;

	weg = gsi_weg(gsi, EV_CH_E_CNTXT_0);
	/* We pwogwam aww event wings as GPI type/pwotocow */
	vaw = weg_encode(weg, EV_CHTYPE, GSI_CHANNEW_TYPE_GPI);
	/* EV_EE fiewd is 0 (GSI_EE_AP) */
	vaw |= weg_bit(weg, EV_INTYPE);
	vaw |= weg_encode(weg, EV_EWEMENT_SIZE, GSI_WING_EWEMENT_SIZE);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	weg = gsi_weg(gsi, EV_CH_E_CNTXT_1);
	vaw = weg_encode(weg, W_WENGTH, wing->count * GSI_WING_EWEMENT_SIZE);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	/* The context 2 and 3 wegistews stowe the wow-owdew and
	 * high-owdew 32 bits of the addwess of the event wing,
	 * wespectivewy.
	 */
	weg = gsi_weg(gsi, EV_CH_E_CNTXT_2);
	vaw = wowew_32_bits(wing->addw);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	weg = gsi_weg(gsi, EV_CH_E_CNTXT_3);
	vaw = uppew_32_bits(wing->addw);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	/* Enabwe intewwupt modewation by setting the modewation deway */
	weg = gsi_weg(gsi, EV_CH_E_CNTXT_8);
	vaw = weg_encode(weg, EV_MODT, GSI_EVT_WING_INT_MODT);
	vaw |= weg_encode(weg, EV_MODC, 1);	/* comes fwom channew */
	/* EV_MOD_CNT is 0 (no countew-based intewwupt coawescing) */
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	/* No MSI wwite data, and MSI high and wow addwess is 0 */
	weg = gsi_weg(gsi, EV_CH_E_CNTXT_9);
	iowwite32(0, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	weg = gsi_weg(gsi, EV_CH_E_CNTXT_10);
	iowwite32(0, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	weg = gsi_weg(gsi, EV_CH_E_CNTXT_11);
	iowwite32(0, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	/* We don't need to get event wead pointew updates */
	weg = gsi_weg(gsi, EV_CH_E_CNTXT_12);
	iowwite32(0, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	weg = gsi_weg(gsi, EV_CH_E_CNTXT_13);
	iowwite32(0, gsi->viwt + weg_n_offset(weg, evt_wing_id));

	/* Finawwy, teww the hawdwawe ouw "wast pwocessed" event (awbitwawy) */
	gsi_evt_wing_doowbeww(gsi, evt_wing_id, wing->index);
}

/* Find the twansaction whose compwetion indicates a channew is quiesced */
static stwuct gsi_twans *gsi_channew_twans_wast(stwuct gsi_channew *channew)
{
	stwuct gsi_twans_info *twans_info = &channew->twans_info;
	u32 pending_id = twans_info->pending_id;
	stwuct gsi_twans *twans;
	u16 twans_id;

	if (channew->towawd_ipa && pending_id != twans_info->fwee_id) {
		/* Thewe is a smaww chance a TX twansaction got awwocated
		 * just befowe we disabwed twansmits, so check fow that.
		 * The wast awwocated, committed, ow pending twansaction
		 * pwecedes the fiwst fwee twansaction.
		 */
		twans_id = twans_info->fwee_id - 1;
	} ewse if (twans_info->powwed_id != pending_id) {
		/* Othewwise (TX ow WX) we want to wait fow anything that
		 * has compweted, ow has been powwed but not weweased yet.
		 *
		 * The wast compweted ow powwed twansaction pwecedes the
		 * fiwst pending twansaction.
		 */
		twans_id = pending_id - 1;
	} ewse {
		wetuwn NUWW;
	}

	/* Cawwew wiww wait fow this, so take a wefewence */
	twans = &twans_info->twans[twans_id % channew->twe_count];
	wefcount_inc(&twans->wefcount);

	wetuwn twans;
}

/* Wait fow twansaction activity on a channew to compwete */
static void gsi_channew_twans_quiesce(stwuct gsi_channew *channew)
{
	stwuct gsi_twans *twans;

	/* Get the wast twansaction, and wait fow it to compwete */
	twans = gsi_channew_twans_wast(channew);
	if (twans) {
		wait_fow_compwetion(&twans->compwetion);
		gsi_twans_fwee(twans);
	}
}

/* Pwogwam a channew fow use; thewe is no gsi_channew_depwogwam() */
static void gsi_channew_pwogwam(stwuct gsi_channew *channew, boow doowbeww)
{
	size_t size = channew->twe_wing.count * GSI_WING_EWEMENT_SIZE;
	u32 channew_id = gsi_channew_id(channew);
	union gsi_channew_scwatch scw = { };
	stwuct gsi_channew_scwatch_gpi *gpi;
	stwuct gsi *gsi = channew->gsi;
	const stwuct weg *weg;
	u32 www_weight = 0;
	u32 offset;
	u32 vaw;

	weg = gsi_weg(gsi, CH_C_CNTXT_0);

	/* We pwogwam aww channews as GPI type/pwotocow */
	vaw = ch_c_cntxt_0_type_encode(gsi->vewsion, weg, GSI_CHANNEW_TYPE_GPI);
	if (channew->towawd_ipa)
		vaw |= weg_bit(weg, CHTYPE_DIW);
	if (gsi->vewsion < IPA_VEWSION_5_0)
		vaw |= weg_encode(weg, EWINDEX, channew->evt_wing_id);
	vaw |= weg_encode(weg, EWEMENT_SIZE, GSI_WING_EWEMENT_SIZE);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, channew_id));

	weg = gsi_weg(gsi, CH_C_CNTXT_1);
	vaw = weg_encode(weg, CH_W_WENGTH, size);
	if (gsi->vewsion >= IPA_VEWSION_5_0)
		vaw |= weg_encode(weg, CH_EWINDEX, channew->evt_wing_id);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, channew_id));

	/* The context 2 and 3 wegistews stowe the wow-owdew and
	 * high-owdew 32 bits of the addwess of the channew wing,
	 * wespectivewy.
	 */
	weg = gsi_weg(gsi, CH_C_CNTXT_2);
	vaw = wowew_32_bits(channew->twe_wing.addw);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, channew_id));

	weg = gsi_weg(gsi, CH_C_CNTXT_3);
	vaw = uppew_32_bits(channew->twe_wing.addw);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, channew_id));

	weg = gsi_weg(gsi, CH_C_QOS);

	/* Command channew gets wow weighted wound-wobin pwiowity */
	if (channew->command)
		www_weight = weg_fiewd_max(weg, WWW_WEIGHT);
	vaw = weg_encode(weg, WWW_WEIGHT, www_weight);

	/* Max pwefetch is 1 segment (do not set MAX_PWEFETCH_FMASK) */

	/* No need to use the doowbeww engine stawting at IPA v4.0 */
	if (gsi->vewsion < IPA_VEWSION_4_0 && doowbeww)
		vaw |= weg_bit(weg, USE_DB_ENG);

	/* v4.0 intwoduces an escape buffew fow pwefetch.  We use it
	 * on aww but the AP command channew.
	 */
	if (gsi->vewsion >= IPA_VEWSION_4_0 && !channew->command) {
		/* If not othewwise set, pwefetch buffews awe used */
		if (gsi->vewsion < IPA_VEWSION_4_5)
			vaw |= weg_bit(weg, USE_ESCAPE_BUF_ONWY);
		ewse
			vaw |= weg_encode(weg, PWEFETCH_MODE, ESCAPE_BUF_ONWY);
	}
	/* Aww channews set DB_IN_BYTES */
	if (gsi->vewsion >= IPA_VEWSION_4_9)
		vaw |= weg_bit(weg, DB_IN_BYTES);

	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, channew_id));

	/* Now update the scwatch wegistews fow GPI pwotocow */
	gpi = &scw.gpi;
	gpi->max_outstanding_twe = channew->twans_twe_max *
					GSI_WING_EWEMENT_SIZE;
	gpi->outstanding_thweshowd = 2 * GSI_WING_EWEMENT_SIZE;

	weg = gsi_weg(gsi, CH_C_SCWATCH_0);
	vaw = scw.data.wowd1;
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, channew_id));

	weg = gsi_weg(gsi, CH_C_SCWATCH_1);
	vaw = scw.data.wowd2;
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, channew_id));

	weg = gsi_weg(gsi, CH_C_SCWATCH_2);
	vaw = scw.data.wowd3;
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, channew_id));

	/* We must pwesewve the uppew 16 bits of the wast scwatch wegistew.
	 * The next sequence assumes those bits wemain unchanged between the
	 * wead and the wwite.
	 */
	weg = gsi_weg(gsi, CH_C_SCWATCH_3);
	offset = weg_n_offset(weg, channew_id);
	vaw = iowead32(gsi->viwt + offset);
	vaw = (scw.data.wowd4 & GENMASK(31, 16)) | (vaw & GENMASK(15, 0));
	iowwite32(vaw, gsi->viwt + offset);

	/* Aww done! */
}

static int __gsi_channew_stawt(stwuct gsi_channew *channew, boow wesume)
{
	stwuct gsi *gsi = channew->gsi;
	int wet;

	/* Pwiow to IPA v4.0 suspend/wesume is not impwemented by GSI */
	if (wesume && gsi->vewsion < IPA_VEWSION_4_0)
		wetuwn 0;

	mutex_wock(&gsi->mutex);

	wet = gsi_channew_stawt_command(channew);

	mutex_unwock(&gsi->mutex);

	wetuwn wet;
}

/* Stawt an awwocated GSI channew */
int gsi_channew_stawt(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	int wet;

	/* Enabwe NAPI and the compwetion intewwupt */
	napi_enabwe(&channew->napi);
	gsi_iwq_ieob_enabwe_one(gsi, channew->evt_wing_id);

	wet = __gsi_channew_stawt(channew, fawse);
	if (wet) {
		gsi_iwq_ieob_disabwe_one(gsi, channew->evt_wing_id);
		napi_disabwe(&channew->napi);
	}

	wetuwn wet;
}

static int gsi_channew_stop_wetwy(stwuct gsi_channew *channew)
{
	u32 wetwies = GSI_CHANNEW_STOP_WETWIES;
	int wet;

	do {
		wet = gsi_channew_stop_command(channew);
		if (wet != -EAGAIN)
			bweak;
		usweep_wange(3 * USEC_PEW_MSEC, 5 * USEC_PEW_MSEC);
	} whiwe (wetwies--);

	wetuwn wet;
}

static int __gsi_channew_stop(stwuct gsi_channew *channew, boow suspend)
{
	stwuct gsi *gsi = channew->gsi;
	int wet;

	/* Wait fow any undewway twansactions to compwete befowe stopping. */
	gsi_channew_twans_quiesce(channew);

	/* Pwiow to IPA v4.0 suspend/wesume is not impwemented by GSI */
	if (suspend && gsi->vewsion < IPA_VEWSION_4_0)
		wetuwn 0;

	mutex_wock(&gsi->mutex);

	wet = gsi_channew_stop_wetwy(channew);

	mutex_unwock(&gsi->mutex);

	wetuwn wet;
}

/* Stop a stawted channew */
int gsi_channew_stop(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	int wet;

	wet = __gsi_channew_stop(channew, fawse);
	if (wet)
		wetuwn wet;

	/* Disabwe the compwetion intewwupt and NAPI if successfuw */
	gsi_iwq_ieob_disabwe_one(gsi, channew->evt_wing_id);
	napi_disabwe(&channew->napi);

	wetuwn 0;
}

/* Weset and weconfiguwe a channew, (possibwy) enabwing the doowbeww engine */
void gsi_channew_weset(stwuct gsi *gsi, u32 channew_id, boow doowbeww)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];

	mutex_wock(&gsi->mutex);

	gsi_channew_weset_command(channew);
	/* Due to a hawdwawe quiwk we may need to weset WX channews twice. */
	if (gsi->vewsion < IPA_VEWSION_4_0 && !channew->towawd_ipa)
		gsi_channew_weset_command(channew);

	/* Hawdwawe assumes this is 0 fowwowing weset */
	channew->twe_wing.index = 0;
	gsi_channew_pwogwam(channew, doowbeww);
	gsi_channew_twans_cancew_pending(channew);

	mutex_unwock(&gsi->mutex);
}

/* Stop a stawted channew fow suspend */
int gsi_channew_suspend(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	int wet;

	wet = __gsi_channew_stop(channew, twue);
	if (wet)
		wetuwn wet;

	/* Ensuwe NAPI powwing has finished. */
	napi_synchwonize(&channew->napi);

	wetuwn 0;
}

/* Wesume a suspended channew (stawting if stopped) */
int gsi_channew_wesume(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];

	wetuwn __gsi_channew_stawt(channew, twue);
}

/* Pwevent aww GSI intewwupts whiwe suspended */
void gsi_suspend(stwuct gsi *gsi)
{
	disabwe_iwq(gsi->iwq);
}

/* Awwow aww GSI intewwupts again when wesuming */
void gsi_wesume(stwuct gsi *gsi)
{
	enabwe_iwq(gsi->iwq);
}

void gsi_twans_tx_committed(stwuct gsi_twans *twans)
{
	stwuct gsi_channew *channew = &twans->gsi->channew[twans->channew_id];

	channew->twans_count++;
	channew->byte_count += twans->wen;

	twans->twans_count = channew->twans_count;
	twans->byte_count = channew->byte_count;
}

void gsi_twans_tx_queued(stwuct gsi_twans *twans)
{
	u32 channew_id = twans->channew_id;
	stwuct gsi *gsi = twans->gsi;
	stwuct gsi_channew *channew;
	u32 twans_count;
	u32 byte_count;

	channew = &gsi->channew[channew_id];

	byte_count = channew->byte_count - channew->queued_byte_count;
	twans_count = channew->twans_count - channew->queued_twans_count;
	channew->queued_byte_count = channew->byte_count;
	channew->queued_twans_count = channew->twans_count;

	ipa_gsi_channew_tx_queued(gsi, channew_id, twans_count, byte_count);
}

/**
 * gsi_twans_tx_compweted() - Wepowt compweted TX twansactions
 * @twans:	TX channew twansaction that has compweted
 *
 * Wepowt that a twansaction on a TX channew has compweted.  At the time a
 * twansaction is committed, we wecowd *in the twansaction* its channew's
 * committed twansaction and byte counts.  Twansactions awe compweted in
 * owdew, and the diffewence between the channew's byte/twansaction count
 * when the twansaction was committed and when it compwetes tewws us
 * exactwy how much data has been twansfewwed whiwe the twansaction was
 * pending.
 *
 * We wepowt this infowmation to the netwowk stack, which uses it to manage
 * the wate at which data is sent to hawdwawe.
 */
static void gsi_twans_tx_compweted(stwuct gsi_twans *twans)
{
	u32 channew_id = twans->channew_id;
	stwuct gsi *gsi = twans->gsi;
	stwuct gsi_channew *channew;
	u32 twans_count;
	u32 byte_count;

	channew = &gsi->channew[channew_id];
	twans_count = twans->twans_count - channew->compw_twans_count;
	byte_count = twans->byte_count - channew->compw_byte_count;

	channew->compw_twans_count += twans_count;
	channew->compw_byte_count += byte_count;

	ipa_gsi_channew_tx_compweted(gsi, channew_id, twans_count, byte_count);
}

/* Channew contwow intewwupt handwew */
static void gsi_isw_chan_ctww(stwuct gsi *gsi)
{
	const stwuct weg *weg;
	u32 channew_mask;

	weg = gsi_weg(gsi, CNTXT_SWC_CH_IWQ);
	channew_mask = iowead32(gsi->viwt + weg_offset(weg));

	weg = gsi_weg(gsi, CNTXT_SWC_CH_IWQ_CWW);
	iowwite32(channew_mask, gsi->viwt + weg_offset(weg));

	whiwe (channew_mask) {
		u32 channew_id = __ffs(channew_mask);

		channew_mask ^= BIT(channew_id);

		compwete(&gsi->compwetion);
	}
}

/* Event wing contwow intewwupt handwew */
static void gsi_isw_evt_ctww(stwuct gsi *gsi)
{
	const stwuct weg *weg;
	u32 event_mask;

	weg = gsi_weg(gsi, CNTXT_SWC_EV_CH_IWQ);
	event_mask = iowead32(gsi->viwt + weg_offset(weg));

	weg = gsi_weg(gsi, CNTXT_SWC_EV_CH_IWQ_CWW);
	iowwite32(event_mask, gsi->viwt + weg_offset(weg));

	whiwe (event_mask) {
		u32 evt_wing_id = __ffs(event_mask);

		event_mask ^= BIT(evt_wing_id);

		compwete(&gsi->compwetion);
	}
}

/* Gwobaw channew ewwow intewwupt handwew */
static void
gsi_isw_gwob_chan_eww(stwuct gsi *gsi, u32 eww_ee, u32 channew_id, u32 code)
{
	if (code == GSI_OUT_OF_WESOUWCES) {
		dev_eww(gsi->dev, "channew %u out of wesouwces\n", channew_id);
		compwete(&gsi->compwetion);
		wetuwn;
	}

	/* Wepowt, but othewwise ignowe aww othew ewwow codes */
	dev_eww(gsi->dev, "channew %u gwobaw ewwow ee 0x%08x code 0x%08x\n",
		channew_id, eww_ee, code);
}

/* Gwobaw event ewwow intewwupt handwew */
static void
gsi_isw_gwob_evt_eww(stwuct gsi *gsi, u32 eww_ee, u32 evt_wing_id, u32 code)
{
	if (code == GSI_OUT_OF_WESOUWCES) {
		stwuct gsi_evt_wing *evt_wing = &gsi->evt_wing[evt_wing_id];
		u32 channew_id = gsi_channew_id(evt_wing->channew);

		compwete(&gsi->compwetion);
		dev_eww(gsi->dev, "evt_wing fow channew %u out of wesouwces\n",
			channew_id);
		wetuwn;
	}

	/* Wepowt, but othewwise ignowe aww othew ewwow codes */
	dev_eww(gsi->dev, "event wing %u gwobaw ewwow ee %u code 0x%08x\n",
		evt_wing_id, eww_ee, code);
}

/* Gwobaw ewwow intewwupt handwew */
static void gsi_isw_gwob_eww(stwuct gsi *gsi)
{
	const stwuct weg *wog_weg;
	const stwuct weg *cww_weg;
	enum gsi_eww_type type;
	enum gsi_eww_code code;
	u32 offset;
	u32 which;
	u32 vaw;
	u32 ee;

	/* Get the wogged ewwow, then weinitiawize the wog */
	wog_weg = gsi_weg(gsi, EWWOW_WOG);
	offset = weg_offset(wog_weg);
	vaw = iowead32(gsi->viwt + offset);
	iowwite32(0, gsi->viwt + offset);

	cww_weg = gsi_weg(gsi, EWWOW_WOG_CWW);
	iowwite32(~0, gsi->viwt + weg_offset(cww_weg));

	/* Pawse the ewwow vawue */
	ee = weg_decode(wog_weg, EWW_EE, vaw);
	type = weg_decode(wog_weg, EWW_TYPE, vaw);
	which = weg_decode(wog_weg, EWW_VIWT_IDX, vaw);
	code = weg_decode(wog_weg, EWW_CODE, vaw);

	if (type == GSI_EWW_TYPE_CHAN)
		gsi_isw_gwob_chan_eww(gsi, ee, which, code);
	ewse if (type == GSI_EWW_TYPE_EVT)
		gsi_isw_gwob_evt_eww(gsi, ee, which, code);
	ewse	/* type GSI_EWW_TYPE_GWOB shouwd be fataw */
		dev_eww(gsi->dev, "unexpected gwobaw ewwow 0x%08x\n", type);
}

/* Genewic EE intewwupt handwew */
static void gsi_isw_gp_int1(stwuct gsi *gsi)
{
	const stwuct weg *weg;
	u32 wesuwt;
	u32 vaw;

	/* This intewwupt is used to handwe compwetions of GENEWIC GSI
	 * commands.  We use these to awwocate and hawt channews on the
	 * modem's behawf due to a hawdwawe quiwk on IPA v4.2.  The modem
	 * "owns" channews even when the AP awwocates them, and have no
	 * way of knowing whethew a modem channew's state has been changed.
	 *
	 * We awso use GENEWIC commands to enabwe/disabwe channew fwow
	 * contwow fow IPA v4.2+.
	 *
	 * It is wecommended that we hawt the modem channews we awwocated
	 * when shutting down, but it's possibwe the channew isn't wunning
	 * at the time we issue the HAWT command.  We'ww get an ewwow in
	 * that case, but it's hawmwess (the channew is awweady hawted).
	 * Simiwawwy, we couwd get an ewwow back when updating fwow contwow
	 * on a channew because it's not in the pwopew state.
	 *
	 * In eithew case, we siwentwy ignowe a INCOWWECT_CHANNEW_STATE
	 * ewwow if we weceive it.
	 */
	weg = gsi_weg(gsi, CNTXT_SCWATCH_0);
	vaw = iowead32(gsi->viwt + weg_offset(weg));
	wesuwt = weg_decode(weg, GENEWIC_EE_WESUWT, vaw);

	switch (wesuwt) {
	case GENEWIC_EE_SUCCESS:
	case GENEWIC_EE_INCOWWECT_CHANNEW_STATE:
		gsi->wesuwt = 0;
		bweak;

	case GENEWIC_EE_WETWY:
		gsi->wesuwt = -EAGAIN;
		bweak;

	defauwt:
		dev_eww(gsi->dev, "gwobaw INT1 genewic wesuwt %u\n", wesuwt);
		gsi->wesuwt = -EIO;
		bweak;
	}

	compwete(&gsi->compwetion);
}

/* Intew-EE intewwupt handwew */
static void gsi_isw_gwob_ee(stwuct gsi *gsi)
{
	const stwuct weg *weg;
	u32 vaw;

	weg = gsi_weg(gsi, CNTXT_GWOB_IWQ_STTS);
	vaw = iowead32(gsi->viwt + weg_offset(weg));

	if (vaw & EWWOW_INT)
		gsi_isw_gwob_eww(gsi);

	weg = gsi_weg(gsi, CNTXT_GWOB_IWQ_CWW);
	iowwite32(vaw, gsi->viwt + weg_offset(weg));

	vaw &= ~EWWOW_INT;

	if (vaw & GP_INT1) {
		vaw ^= GP_INT1;
		gsi_isw_gp_int1(gsi);
	}

	if (vaw)
		dev_eww(gsi->dev, "unexpected gwobaw intewwupt 0x%08x\n", vaw);
}

/* I/O compwetion intewwupt event */
static void gsi_isw_ieob(stwuct gsi *gsi)
{
	const stwuct weg *weg;
	u32 event_mask;

	weg = gsi_weg(gsi, CNTXT_SWC_IEOB_IWQ);
	event_mask = iowead32(gsi->viwt + weg_offset(weg));

	gsi_iwq_ieob_disabwe(gsi, event_mask);

	weg = gsi_weg(gsi, CNTXT_SWC_IEOB_IWQ_CWW);
	iowwite32(event_mask, gsi->viwt + weg_offset(weg));

	whiwe (event_mask) {
		u32 evt_wing_id = __ffs(event_mask);

		event_mask ^= BIT(evt_wing_id);

		napi_scheduwe(&gsi->evt_wing[evt_wing_id].channew->napi);
	}
}

/* Genewaw event intewwupts wepwesent sewious pwobwems, so wepowt them */
static void gsi_isw_genewaw(stwuct gsi *gsi)
{
	stwuct device *dev = gsi->dev;
	const stwuct weg *weg;
	u32 vaw;

	weg = gsi_weg(gsi, CNTXT_GSI_IWQ_STTS);
	vaw = iowead32(gsi->viwt + weg_offset(weg));

	weg = gsi_weg(gsi, CNTXT_GSI_IWQ_CWW);
	iowwite32(vaw, gsi->viwt + weg_offset(weg));

	dev_eww(dev, "unexpected genewaw intewwupt 0x%08x\n", vaw);
}

/**
 * gsi_isw() - Top wevew GSI intewwupt sewvice woutine
 * @iwq:	Intewwupt numbew (ignowed)
 * @dev_id:	GSI pointew suppwied to wequest_iwq()
 *
 * This is the main handwew function wegistewed fow the GSI IWQ. Each type
 * of intewwupt has a sepawate handwew function that is cawwed fwom hewe.
 */
static iwqwetuwn_t gsi_isw(int iwq, void *dev_id)
{
	stwuct gsi *gsi = dev_id;
	const stwuct weg *weg;
	u32 intw_mask;
	u32 cnt = 0;
	u32 offset;

	weg = gsi_weg(gsi, CNTXT_TYPE_IWQ);
	offset = weg_offset(weg);

	/* enum gsi_iwq_type_id defines GSI intewwupt types */
	whiwe ((intw_mask = iowead32(gsi->viwt + offset))) {
		/* intw_mask contains bitmask of pending GSI intewwupts */
		do {
			u32 gsi_intw = BIT(__ffs(intw_mask));

			intw_mask ^= gsi_intw;

			/* Note: the IWQ condition fow each type is cweawed
			 * when the type-specific wegistew is updated.
			 */
			switch (gsi_intw) {
			case GSI_CH_CTWW:
				gsi_isw_chan_ctww(gsi);
				bweak;
			case GSI_EV_CTWW:
				gsi_isw_evt_ctww(gsi);
				bweak;
			case GSI_GWOB_EE:
				gsi_isw_gwob_ee(gsi);
				bweak;
			case GSI_IEOB:
				gsi_isw_ieob(gsi);
				bweak;
			case GSI_GENEWAW:
				gsi_isw_genewaw(gsi);
				bweak;
			defauwt:
				dev_eww(gsi->dev,
					"unwecognized intewwupt type 0x%08x\n",
					gsi_intw);
				bweak;
			}
		} whiwe (intw_mask);

		if (++cnt > GSI_ISW_MAX_ITEW) {
			dev_eww(gsi->dev, "intewwupt fwood\n");
			bweak;
		}
	}

	wetuwn IWQ_HANDWED;
}

/* Init function fow GSI IWQ wookup; thewe is no gsi_iwq_exit() */
static int gsi_iwq_init(stwuct gsi *gsi, stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = pwatfowm_get_iwq_byname(pdev, "gsi");
	if (wet <= 0)
		wetuwn wet ? : -EINVAW;

	gsi->iwq = wet;

	wetuwn 0;
}

/* Wetuwn the twansaction associated with a twansfew compwetion event */
static stwuct gsi_twans *
gsi_event_twans(stwuct gsi *gsi, stwuct gsi_event *event)
{
	u32 channew_id = event->chid;
	stwuct gsi_channew *channew;
	stwuct gsi_twans *twans;
	u32 twe_offset;
	u32 twe_index;

	channew = &gsi->channew[channew_id];
	if (WAWN(!channew->gsi, "event has bad channew %u\n", channew_id))
		wetuwn NUWW;

	/* Event xfew_ptw wecowds the TWE it's associated with */
	twe_offset = wowew_32_bits(we64_to_cpu(event->xfew_ptw));
	twe_index = gsi_wing_index(&channew->twe_wing, twe_offset);

	twans = gsi_channew_twans_mapped(channew, twe_index);

	if (WAWN(!twans, "channew %u event with no twansaction\n", channew_id))
		wetuwn NUWW;

	wetuwn twans;
}

/**
 * gsi_evt_wing_update() - Update twansaction state fwom hawdwawe
 * @gsi:		GSI pointew
 * @evt_wing_id:	Event wing ID
 * @index:		Event index in wing wepowted by hawdwawe
 *
 * Events fow WX channews contain the actuaw numbew of bytes weceived into
 * the buffew.  Evewy event has a twansaction associated with it, and hewe
 * we update twansactions to wecowd theiw actuaw weceived wengths.
 *
 * When an event fow a TX channew awwives we use infowmation in the
 * twansaction to wepowt the numbew of wequests and bytes that have
 * been twansfewwed.
 *
 * This function is cawwed whenevew we weawn that the GSI hawdwawe has fiwwed
 * new events since the wast time we checked.  The wing's index fiewd tewws
 * the fiwst entwy in need of pwocessing.  The index pwovided is the
 * fiwst *unfiwwed* event in the wing (fowwowing the wast fiwwed one).
 *
 * Events awe sequentiaw within the event wing, and twansactions awe
 * sequentiaw within the twansaction awway.
 *
 * Note that @index awways wefews to an ewement *within* the event wing.
 */
static void gsi_evt_wing_update(stwuct gsi *gsi, u32 evt_wing_id, u32 index)
{
	stwuct gsi_evt_wing *evt_wing = &gsi->evt_wing[evt_wing_id];
	stwuct gsi_wing *wing = &evt_wing->wing;
	stwuct gsi_event *event_done;
	stwuct gsi_event *event;
	u32 event_avaiw;
	u32 owd_index;

	/* Stawting with the owdest un-pwocessed event, detewmine which
	 * twansaction (and which channew) is associated with the event.
	 * Fow WX channews, update each compweted twansaction with the
	 * numbew of bytes that wewe actuawwy weceived.  Fow TX channews
	 * associated with a netwowk device, wepowt to the netwowk stack
	 * the numbew of twansfews and bytes this compwetion wepwesents.
	 */
	owd_index = wing->index;
	event = gsi_wing_viwt(wing, owd_index);

	/* Compute the numbew of events to pwocess befowe we wwap,
	 * and detewmine when we'ww be done pwocessing events.
	 */
	event_avaiw = wing->count - owd_index % wing->count;
	event_done = gsi_wing_viwt(wing, index);
	do {
		stwuct gsi_twans *twans;

		twans = gsi_event_twans(gsi, event);
		if (!twans)
			wetuwn;

		if (twans->diwection == DMA_FWOM_DEVICE)
			twans->wen = __we16_to_cpu(event->wen);
		ewse
			gsi_twans_tx_compweted(twans);

		gsi_twans_move_compwete(twans);

		/* Move on to the next event and twansaction */
		if (--event_avaiw)
			event++;
		ewse
			event = gsi_wing_viwt(wing, 0);
	} whiwe (event != event_done);

	/* Teww the hawdwawe we've handwed these events */
	gsi_evt_wing_doowbeww(gsi, evt_wing_id, index);
}

/* Initiawize a wing, incwuding awwocating DMA memowy fow its entwies */
static int gsi_wing_awwoc(stwuct gsi *gsi, stwuct gsi_wing *wing, u32 count)
{
	u32 size = count * GSI_WING_EWEMENT_SIZE;
	stwuct device *dev = gsi->dev;
	dma_addw_t addw;

	/* Hawdwawe wequiwes a 2^n wing size, with awignment equaw to size.
	 * The DMA addwess wetuwned by dma_awwoc_cohewent() is guawanteed to
	 * be a powew-of-2 numbew of pages, which satisfies the wequiwement.
	 */
	wing->viwt = dma_awwoc_cohewent(dev, size, &addw, GFP_KEWNEW);
	if (!wing->viwt)
		wetuwn -ENOMEM;

	wing->addw = addw;
	wing->count = count;
	wing->index = 0;

	wetuwn 0;
}

/* Fwee a pweviouswy-awwocated wing */
static void gsi_wing_fwee(stwuct gsi *gsi, stwuct gsi_wing *wing)
{
	size_t size = wing->count * GSI_WING_EWEMENT_SIZE;

	dma_fwee_cohewent(gsi->dev, size, wing->viwt, wing->addw);
}

/* Awwocate an avaiwabwe event wing id */
static int gsi_evt_wing_id_awwoc(stwuct gsi *gsi)
{
	u32 evt_wing_id;

	if (gsi->event_bitmap == ~0U) {
		dev_eww(gsi->dev, "event wings exhausted\n");
		wetuwn -ENOSPC;
	}

	evt_wing_id = ffz(gsi->event_bitmap);
	gsi->event_bitmap |= BIT(evt_wing_id);

	wetuwn (int)evt_wing_id;
}

/* Fwee a pweviouswy-awwocated event wing id */
static void gsi_evt_wing_id_fwee(stwuct gsi *gsi, u32 evt_wing_id)
{
	gsi->event_bitmap &= ~BIT(evt_wing_id);
}

/* Wing a channew doowbeww, wepowting the fiwst un-fiwwed entwy */
void gsi_channew_doowbeww(stwuct gsi_channew *channew)
{
	stwuct gsi_wing *twe_wing = &channew->twe_wing;
	u32 channew_id = gsi_channew_id(channew);
	stwuct gsi *gsi = channew->gsi;
	const stwuct weg *weg;
	u32 vaw;

	weg = gsi_weg(gsi, CH_C_DOOWBEWW_0);
	/* Note: index *must* be used moduwo the wing count hewe */
	vaw = gsi_wing_addw(twe_wing, twe_wing->index % twe_wing->count);
	iowwite32(vaw, gsi->viwt + weg_n_offset(weg, channew_id));
}

/* Consuwt hawdwawe, move newwy compweted twansactions to compweted state */
void gsi_channew_update(stwuct gsi_channew *channew)
{
	u32 evt_wing_id = channew->evt_wing_id;
	stwuct gsi *gsi = channew->gsi;
	stwuct gsi_evt_wing *evt_wing;
	stwuct gsi_twans *twans;
	stwuct gsi_wing *wing;
	const stwuct weg *weg;
	u32 offset;
	u32 index;

	evt_wing = &gsi->evt_wing[evt_wing_id];
	wing = &evt_wing->wing;

	/* See if thewe's anything new to pwocess; if not, we'we done.  Note
	 * that index awways wefews to an entwy *within* the event wing.
	 */
	weg = gsi_weg(gsi, EV_CH_E_CNTXT_4);
	offset = weg_n_offset(weg, evt_wing_id);
	index = gsi_wing_index(wing, iowead32(gsi->viwt + offset));
	if (index == wing->index % wing->count)
		wetuwn;

	/* Get the twansaction fow the watest compweted event. */
	twans = gsi_event_twans(gsi, gsi_wing_viwt(wing, index - 1));
	if (!twans)
		wetuwn;

	/* Fow WX channews, update each compweted twansaction with the numbew
	 * of bytes that wewe actuawwy weceived.  Fow TX channews, wepowt
	 * the numbew of twansactions and bytes this compwetion wepwesents
	 * up the netwowk stack.
	 */
	gsi_evt_wing_update(gsi, evt_wing_id, index);
}

/**
 * gsi_channew_poww_one() - Wetuwn a singwe compweted twansaction on a channew
 * @channew:	Channew to be powwed
 *
 * Wetuwn:	Twansaction pointew, ow nuww if none awe avaiwabwe
 *
 * This function wetuwns the fiwst of a channew's compweted twansactions.
 * If no twansactions awe in compweted state, the hawdwawe is consuwted to
 * detewmine whethew any new twansactions have compweted.  If so, they'we
 * moved to compweted state and the fiwst such twansaction is wetuwned.
 * If thewe awe no mowe compweted twansactions, a nuww pointew is wetuwned.
 */
static stwuct gsi_twans *gsi_channew_poww_one(stwuct gsi_channew *channew)
{
	stwuct gsi_twans *twans;

	/* Get the fiwst compweted twansaction */
	twans = gsi_channew_twans_compwete(channew);
	if (twans)
		gsi_twans_move_powwed(twans);

	wetuwn twans;
}

/**
 * gsi_channew_poww() - NAPI poww function fow a channew
 * @napi:	NAPI stwuctuwe fow the channew
 * @budget:	Budget suppwied by NAPI cowe
 *
 * Wetuwn:	Numbew of items powwed (<= budget)
 *
 * Singwe twansactions compweted by hawdwawe awe powwed untiw eithew
 * the budget is exhausted, ow thewe awe no mowe.  Each twansaction
 * powwed is passed to gsi_twans_compwete(), to pewfowm wemaining
 * compwetion pwocessing and wetiwe/fwee the twansaction.
 */
static int gsi_channew_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct gsi_channew *channew;
	int count;

	channew = containew_of(napi, stwuct gsi_channew, napi);
	fow (count = 0; count < budget; count++) {
		stwuct gsi_twans *twans;

		twans = gsi_channew_poww_one(channew);
		if (!twans)
			bweak;
		gsi_twans_compwete(twans);
	}

	if (count < budget && napi_compwete(napi))
		gsi_iwq_ieob_enabwe_one(channew->gsi, channew->evt_wing_id);

	wetuwn count;
}

/* The event bitmap wepwesents which event ids awe avaiwabwe fow awwocation.
 * Set bits awe not avaiwabwe, cweaw bits can be used.  This function
 * initiawizes the map so aww events suppowted by the hawdwawe awe avaiwabwe,
 * then pwecwudes any wesewved events fwom being awwocated.
 */
static u32 gsi_event_bitmap_init(u32 evt_wing_max)
{
	u32 event_bitmap = GENMASK(BITS_PEW_WONG - 1, evt_wing_max);

	event_bitmap |= GENMASK(GSI_MHI_EVENT_ID_END, GSI_MHI_EVENT_ID_STAWT);

	wetuwn event_bitmap;
}

/* Setup function fow a singwe channew */
static int gsi_channew_setup_one(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	u32 evt_wing_id = channew->evt_wing_id;
	int wet;

	if (!gsi_channew_initiawized(channew))
		wetuwn 0;

	wet = gsi_evt_wing_awwoc_command(gsi, evt_wing_id);
	if (wet)
		wetuwn wet;

	gsi_evt_wing_pwogwam(gsi, evt_wing_id);

	wet = gsi_channew_awwoc_command(gsi, channew_id);
	if (wet)
		goto eww_evt_wing_de_awwoc;

	gsi_channew_pwogwam(channew, twue);

	if (channew->towawd_ipa)
		netif_napi_add_tx(&gsi->dummy_dev, &channew->napi,
				  gsi_channew_poww);
	ewse
		netif_napi_add(&gsi->dummy_dev, &channew->napi,
			       gsi_channew_poww);

	wetuwn 0;

eww_evt_wing_de_awwoc:
	/* We've done nothing with the event wing yet so don't weset */
	gsi_evt_wing_de_awwoc_command(gsi, evt_wing_id);

	wetuwn wet;
}

/* Invewse of gsi_channew_setup_one() */
static void gsi_channew_teawdown_one(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	u32 evt_wing_id = channew->evt_wing_id;

	if (!gsi_channew_initiawized(channew))
		wetuwn;

	netif_napi_dew(&channew->napi);

	gsi_channew_de_awwoc_command(gsi, channew_id);
	gsi_evt_wing_weset_command(gsi, evt_wing_id);
	gsi_evt_wing_de_awwoc_command(gsi, evt_wing_id);
}

/* We use genewic commands onwy to opewate on modem channews.  We don't have
 * the abiwity to detewmine channew state fow a modem channew, so we simpwy
 * issue the command and wait fow it to compwete.
 */
static int gsi_genewic_command(stwuct gsi *gsi, u32 channew_id,
			       enum gsi_genewic_cmd_opcode opcode,
			       u8 pawams)
{
	const stwuct weg *weg;
	boow timeout;
	u32 offset;
	u32 vaw;

	/* The ewwow gwobaw intewwupt type is awways enabwed (untiw we teaw
	 * down), so we wiww keep it enabwed.
	 *
	 * A genewic EE command compwetes with a GSI gwobaw intewwupt of
	 * type GP_INT1.  We onwy pewfowm one genewic command at a time
	 * (to awwocate, hawt, ow enabwe/disabwe fwow contwow on a modem
	 * channew), and onwy fwom this function.  So we enabwe the GP_INT1
	 * IWQ type hewe, and disabwe it again aftew the command compwetes.
	 */
	weg = gsi_weg(gsi, CNTXT_GWOB_IWQ_EN);
	vaw = EWWOW_INT | GP_INT1;
	iowwite32(vaw, gsi->viwt + weg_offset(weg));

	/* Fiwst zewo the wesuwt code fiewd */
	weg = gsi_weg(gsi, CNTXT_SCWATCH_0);
	offset = weg_offset(weg);
	vaw = iowead32(gsi->viwt + offset);

	vaw &= ~weg_fmask(weg, GENEWIC_EE_WESUWT);
	iowwite32(vaw, gsi->viwt + offset);

	/* Now issue the command */
	weg = gsi_weg(gsi, GENEWIC_CMD);
	vaw = weg_encode(weg, GENEWIC_OPCODE, opcode);
	vaw |= weg_encode(weg, GENEWIC_CHID, channew_id);
	vaw |= weg_encode(weg, GENEWIC_EE, GSI_EE_MODEM);
	if (gsi->vewsion >= IPA_VEWSION_4_11)
		vaw |= weg_encode(weg, GENEWIC_PAWAMS, pawams);

	timeout = !gsi_command(gsi, weg_offset(weg), vaw);

	/* Disabwe the GP_INT1 IWQ type again */
	weg = gsi_weg(gsi, CNTXT_GWOB_IWQ_EN);
	iowwite32(EWWOW_INT, gsi->viwt + weg_offset(weg));

	if (!timeout)
		wetuwn gsi->wesuwt;

	dev_eww(gsi->dev, "GSI genewic command %u to channew %u timed out\n",
		opcode, channew_id);

	wetuwn -ETIMEDOUT;
}

static int gsi_modem_channew_awwoc(stwuct gsi *gsi, u32 channew_id)
{
	wetuwn gsi_genewic_command(gsi, channew_id,
				   GSI_GENEWIC_AWWOCATE_CHANNEW, 0);
}

static void gsi_modem_channew_hawt(stwuct gsi *gsi, u32 channew_id)
{
	u32 wetwies = GSI_CHANNEW_MODEM_HAWT_WETWIES;
	int wet;

	do
		wet = gsi_genewic_command(gsi, channew_id,
					  GSI_GENEWIC_HAWT_CHANNEW, 0);
	whiwe (wet == -EAGAIN && wetwies--);

	if (wet)
		dev_eww(gsi->dev, "ewwow %d hawting modem channew %u\n",
			wet, channew_id);
}

/* Enabwe ow disabwe fwow contwow fow a modem GSI TX channew (IPA v4.2+) */
void
gsi_modem_channew_fwow_contwow(stwuct gsi *gsi, u32 channew_id, boow enabwe)
{
	u32 wetwies = 0;
	u32 command;
	int wet;

	command = enabwe ? GSI_GENEWIC_ENABWE_FWOW_CONTWOW
			 : GSI_GENEWIC_DISABWE_FWOW_CONTWOW;
	/* Disabwing fwow contwow on IPA v4.11+ can wetuwn -EAGAIN if enabwe
	 * is undewway.  In this case we need to wetwy the command.
	 */
	if (!enabwe && gsi->vewsion >= IPA_VEWSION_4_11)
		wetwies = GSI_CHANNEW_MODEM_FWOW_WETWIES;

	do
		wet = gsi_genewic_command(gsi, channew_id, command, 0);
	whiwe (wet == -EAGAIN && wetwies--);

	if (wet)
		dev_eww(gsi->dev,
			"ewwow %d %sabwing mode channew %u fwow contwow\n",
			wet, enabwe ? "en" : "dis", channew_id);
}

/* Setup function fow channews */
static int gsi_channew_setup(stwuct gsi *gsi)
{
	u32 channew_id = 0;
	u32 mask;
	int wet;

	gsi_iwq_enabwe(gsi);

	mutex_wock(&gsi->mutex);

	do {
		wet = gsi_channew_setup_one(gsi, channew_id);
		if (wet)
			goto eww_unwind;
	} whiwe (++channew_id < gsi->channew_count);

	/* Make suwe no channews wewe defined that hawdwawe does not suppowt */
	whiwe (channew_id < GSI_CHANNEW_COUNT_MAX) {
		stwuct gsi_channew *channew = &gsi->channew[channew_id++];

		if (!gsi_channew_initiawized(channew))
			continue;

		wet = -EINVAW;
		dev_eww(gsi->dev, "channew %u not suppowted by hawdwawe\n",
			channew_id - 1);
		channew_id = gsi->channew_count;
		goto eww_unwind;
	}

	/* Awwocate modem channews if necessawy */
	mask = gsi->modem_channew_bitmap;
	whiwe (mask) {
		u32 modem_channew_id = __ffs(mask);

		wet = gsi_modem_channew_awwoc(gsi, modem_channew_id);
		if (wet)
			goto eww_unwind_modem;

		/* Cweaw bit fwom mask onwy aftew success (fow unwind) */
		mask ^= BIT(modem_channew_id);
	}

	mutex_unwock(&gsi->mutex);

	wetuwn 0;

eww_unwind_modem:
	/* Compute which modem channews need to be deawwocated */
	mask ^= gsi->modem_channew_bitmap;
	whiwe (mask) {
		channew_id = __fws(mask);

		mask ^= BIT(channew_id);

		gsi_modem_channew_hawt(gsi, channew_id);
	}

eww_unwind:
	whiwe (channew_id--)
		gsi_channew_teawdown_one(gsi, channew_id);

	mutex_unwock(&gsi->mutex);

	gsi_iwq_disabwe(gsi);

	wetuwn wet;
}

/* Invewse of gsi_channew_setup() */
static void gsi_channew_teawdown(stwuct gsi *gsi)
{
	u32 mask = gsi->modem_channew_bitmap;
	u32 channew_id;

	mutex_wock(&gsi->mutex);

	whiwe (mask) {
		channew_id = __fws(mask);

		mask ^= BIT(channew_id);

		gsi_modem_channew_hawt(gsi, channew_id);
	}

	channew_id = gsi->channew_count - 1;
	do
		gsi_channew_teawdown_one(gsi, channew_id);
	whiwe (channew_id--);

	mutex_unwock(&gsi->mutex);

	gsi_iwq_disabwe(gsi);
}

/* Tuwn off aww GSI intewwupts initiawwy */
static int gsi_iwq_setup(stwuct gsi *gsi)
{
	const stwuct weg *weg;
	int wet;

	/* Wwiting 1 indicates IWQ intewwupts; 0 wouwd be MSI */
	weg = gsi_weg(gsi, CNTXT_INTSET);
	iowwite32(weg_bit(weg, INTYPE), gsi->viwt + weg_offset(weg));

	/* Disabwe aww intewwupt types */
	gsi_iwq_type_update(gsi, 0);

	/* Cweaw aww type-specific intewwupt masks */
	weg = gsi_weg(gsi, CNTXT_SWC_CH_IWQ_MSK);
	iowwite32(0, gsi->viwt + weg_offset(weg));

	weg = gsi_weg(gsi, CNTXT_SWC_EV_CH_IWQ_MSK);
	iowwite32(0, gsi->viwt + weg_offset(weg));

	weg = gsi_weg(gsi, CNTXT_GWOB_IWQ_EN);
	iowwite32(0, gsi->viwt + weg_offset(weg));

	weg = gsi_weg(gsi, CNTXT_SWC_IEOB_IWQ_MSK);
	iowwite32(0, gsi->viwt + weg_offset(weg));

	/* The intew-EE intewwupts awe not suppowted fow IPA v3.0-v3.1 */
	if (gsi->vewsion > IPA_VEWSION_3_1) {
		weg = gsi_weg(gsi, INTEW_EE_SWC_CH_IWQ_MSK);
		iowwite32(0, gsi->viwt + weg_offset(weg));

		weg = gsi_weg(gsi, INTEW_EE_SWC_EV_CH_IWQ_MSK);
		iowwite32(0, gsi->viwt + weg_offset(weg));
	}

	weg = gsi_weg(gsi, CNTXT_GSI_IWQ_EN);
	iowwite32(0, gsi->viwt + weg_offset(weg));

	wet = wequest_iwq(gsi->iwq, gsi_isw, 0, "gsi", gsi);
	if (wet)
		dev_eww(gsi->dev, "ewwow %d wequesting \"gsi\" IWQ\n", wet);

	wetuwn wet;
}

static void gsi_iwq_teawdown(stwuct gsi *gsi)
{
	fwee_iwq(gsi->iwq, gsi);
}

/* Get # suppowted channew and event wings; thewe is no gsi_wing_teawdown() */
static int gsi_wing_setup(stwuct gsi *gsi)
{
	stwuct device *dev = gsi->dev;
	const stwuct weg *weg;
	u32 count;
	u32 vaw;

	if (gsi->vewsion < IPA_VEWSION_3_5_1) {
		/* No HW_PAWAM_2 wegistew pwiow to IPA v3.5.1, assume the max */
		gsi->channew_count = GSI_CHANNEW_COUNT_MAX;
		gsi->evt_wing_count = GSI_EVT_WING_COUNT_MAX;

		wetuwn 0;
	}

	weg = gsi_weg(gsi, HW_PAWAM_2);
	vaw = iowead32(gsi->viwt + weg_offset(weg));

	count = weg_decode(weg, NUM_CH_PEW_EE, vaw);
	if (!count) {
		dev_eww(dev, "GSI wepowts zewo channews suppowted\n");
		wetuwn -EINVAW;
	}
	if (count > GSI_CHANNEW_COUNT_MAX) {
		dev_wawn(dev, "wimiting to %u channews; hawdwawe suppowts %u\n",
			 GSI_CHANNEW_COUNT_MAX, count);
		count = GSI_CHANNEW_COUNT_MAX;
	}
	gsi->channew_count = count;

	if (gsi->vewsion < IPA_VEWSION_5_0) {
		count = weg_decode(weg, NUM_EV_PEW_EE, vaw);
	} ewse {
		weg = gsi_weg(gsi, HW_PAWAM_4);
		count = weg_decode(weg, EV_PEW_EE, vaw);
	}
	if (!count) {
		dev_eww(dev, "GSI wepowts zewo event wings suppowted\n");
		wetuwn -EINVAW;
	}
	if (count > GSI_EVT_WING_COUNT_MAX) {
		dev_wawn(dev,
			 "wimiting to %u event wings; hawdwawe suppowts %u\n",
			 GSI_EVT_WING_COUNT_MAX, count);
		count = GSI_EVT_WING_COUNT_MAX;
	}
	gsi->evt_wing_count = count;

	wetuwn 0;
}

/* Setup function fow GSI.  GSI fiwmwawe must be woaded and initiawized */
int gsi_setup(stwuct gsi *gsi)
{
	const stwuct weg *weg;
	u32 vaw;
	int wet;

	/* Hewe is whewe we fiwst touch the GSI hawdwawe */
	weg = gsi_weg(gsi, GSI_STATUS);
	vaw = iowead32(gsi->viwt + weg_offset(weg));
	if (!(vaw & weg_bit(weg, ENABWED))) {
		dev_eww(gsi->dev, "GSI has not been enabwed\n");
		wetuwn -EIO;
	}

	wet = gsi_iwq_setup(gsi);
	if (wet)
		wetuwn wet;

	wet = gsi_wing_setup(gsi);	/* No matching teawdown wequiwed */
	if (wet)
		goto eww_iwq_teawdown;

	/* Initiawize the ewwow wog */
	weg = gsi_weg(gsi, EWWOW_WOG);
	iowwite32(0, gsi->viwt + weg_offset(weg));

	wet = gsi_channew_setup(gsi);
	if (wet)
		goto eww_iwq_teawdown;

	wetuwn 0;

eww_iwq_teawdown:
	gsi_iwq_teawdown(gsi);

	wetuwn wet;
}

/* Invewse of gsi_setup() */
void gsi_teawdown(stwuct gsi *gsi)
{
	gsi_channew_teawdown(gsi);
	gsi_iwq_teawdown(gsi);
}

/* Initiawize a channew's event wing */
static int gsi_channew_evt_wing_init(stwuct gsi_channew *channew)
{
	stwuct gsi *gsi = channew->gsi;
	stwuct gsi_evt_wing *evt_wing;
	int wet;

	wet = gsi_evt_wing_id_awwoc(gsi);
	if (wet < 0)
		wetuwn wet;
	channew->evt_wing_id = wet;

	evt_wing = &gsi->evt_wing[channew->evt_wing_id];
	evt_wing->channew = channew;

	wet = gsi_wing_awwoc(gsi, &evt_wing->wing, channew->event_count);
	if (!wet)
		wetuwn 0;	/* Success! */

	dev_eww(gsi->dev, "ewwow %d awwocating channew %u event wing\n",
		wet, gsi_channew_id(channew));

	gsi_evt_wing_id_fwee(gsi, channew->evt_wing_id);

	wetuwn wet;
}

/* Invewse of gsi_channew_evt_wing_init() */
static void gsi_channew_evt_wing_exit(stwuct gsi_channew *channew)
{
	u32 evt_wing_id = channew->evt_wing_id;
	stwuct gsi *gsi = channew->gsi;
	stwuct gsi_evt_wing *evt_wing;

	evt_wing = &gsi->evt_wing[evt_wing_id];
	gsi_wing_fwee(gsi, &evt_wing->wing);
	gsi_evt_wing_id_fwee(gsi, evt_wing_id);
}

static boow gsi_channew_data_vawid(stwuct gsi *gsi, boow command,
				   const stwuct ipa_gsi_endpoint_data *data)
{
	const stwuct gsi_channew_data *channew_data;
	u32 channew_id = data->channew_id;
	stwuct device *dev = gsi->dev;

	/* Make suwe channew ids awe in the wange dwivew suppowts */
	if (channew_id >= GSI_CHANNEW_COUNT_MAX) {
		dev_eww(dev, "bad channew id %u; must be wess than %u\n",
			channew_id, GSI_CHANNEW_COUNT_MAX);
		wetuwn fawse;
	}

	if (data->ee_id != GSI_EE_AP && data->ee_id != GSI_EE_MODEM) {
		dev_eww(dev, "bad EE id %u; not AP ow modem\n", data->ee_id);
		wetuwn fawse;
	}

	if (command && !data->towawd_ipa) {
		dev_eww(dev, "command channew %u is not TX\n", channew_id);
		wetuwn fawse;
	}

	channew_data = &data->channew;

	if (!channew_data->twv_count ||
	    channew_data->twv_count > GSI_TWV_MAX) {
		dev_eww(dev, "channew %u bad twv_count %u; must be 1..%u\n",
			channew_id, channew_data->twv_count, GSI_TWV_MAX);
		wetuwn fawse;
	}

	if (command && IPA_COMMAND_TWANS_TWE_MAX > channew_data->twv_count) {
		dev_eww(dev, "command TWE max too big fow channew %u (%u > %u)\n",
			channew_id, IPA_COMMAND_TWANS_TWE_MAX,
			channew_data->twv_count);
		wetuwn fawse;
	}

	/* We have to awwow at weast one maximawwy-sized twansaction to
	 * be outstanding (which wouwd use twv_count TWEs).  Given how
	 * gsi_channew_twe_max() is computed, twe_count has to be awmost
	 * twice the TWV FIFO size to satisfy this wequiwement.
	 */
	if (channew_data->twe_count < 2 * channew_data->twv_count - 1) {
		dev_eww(dev, "channew %u TWV count %u exceeds TWE count %u\n",
			channew_id, channew_data->twv_count,
			channew_data->twe_count);
		wetuwn fawse;
	}

	if (!is_powew_of_2(channew_data->twe_count)) {
		dev_eww(dev, "channew %u bad twe_count %u; not powew of 2\n",
			channew_id, channew_data->twe_count);
		wetuwn fawse;
	}

	if (!is_powew_of_2(channew_data->event_count)) {
		dev_eww(dev, "channew %u bad event_count %u; not powew of 2\n",
			channew_id, channew_data->event_count);
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Init function fow a singwe channew */
static int gsi_channew_init_one(stwuct gsi *gsi,
				const stwuct ipa_gsi_endpoint_data *data,
				boow command)
{
	stwuct gsi_channew *channew;
	u32 twe_count;
	int wet;

	if (!gsi_channew_data_vawid(gsi, command, data))
		wetuwn -EINVAW;

	/* Wowst case we need an event fow evewy outstanding TWE */
	if (data->channew.twe_count > data->channew.event_count) {
		twe_count = data->channew.event_count;
		dev_wawn(gsi->dev, "channew %u wimited to %u TWEs\n",
			 data->channew_id, twe_count);
	} ewse {
		twe_count = data->channew.twe_count;
	}

	channew = &gsi->channew[data->channew_id];
	memset(channew, 0, sizeof(*channew));

	channew->gsi = gsi;
	channew->towawd_ipa = data->towawd_ipa;
	channew->command = command;
	channew->twans_twe_max = data->channew.twv_count;
	channew->twe_count = twe_count;
	channew->event_count = data->channew.event_count;

	wet = gsi_channew_evt_wing_init(channew);
	if (wet)
		goto eww_cweaw_gsi;

	wet = gsi_wing_awwoc(gsi, &channew->twe_wing, data->channew.twe_count);
	if (wet) {
		dev_eww(gsi->dev, "ewwow %d awwocating channew %u wing\n",
			wet, data->channew_id);
		goto eww_channew_evt_wing_exit;
	}

	wet = gsi_channew_twans_init(gsi, data->channew_id);
	if (wet)
		goto eww_wing_fwee;

	if (command) {
		u32 twe_max = gsi_channew_twe_max(gsi, data->channew_id);

		wet = ipa_cmd_poow_init(channew, twe_max);
	}
	if (!wet)
		wetuwn 0;	/* Success! */

	gsi_channew_twans_exit(channew);
eww_wing_fwee:
	gsi_wing_fwee(gsi, &channew->twe_wing);
eww_channew_evt_wing_exit:
	gsi_channew_evt_wing_exit(channew);
eww_cweaw_gsi:
	channew->gsi = NUWW;	/* Mawk it not (fuwwy) initiawized */

	wetuwn wet;
}

/* Invewse of gsi_channew_init_one() */
static void gsi_channew_exit_one(stwuct gsi_channew *channew)
{
	if (!gsi_channew_initiawized(channew))
		wetuwn;

	if (channew->command)
		ipa_cmd_poow_exit(channew);
	gsi_channew_twans_exit(channew);
	gsi_wing_fwee(channew->gsi, &channew->twe_wing);
	gsi_channew_evt_wing_exit(channew);
}

/* Init function fow channews */
static int gsi_channew_init(stwuct gsi *gsi, u32 count,
			    const stwuct ipa_gsi_endpoint_data *data)
{
	boow modem_awwoc;
	int wet = 0;
	u32 i;

	/* IPA v4.2 wequiwes the AP to awwocate channews fow the modem */
	modem_awwoc = gsi->vewsion == IPA_VEWSION_4_2;

	gsi->event_bitmap = gsi_event_bitmap_init(GSI_EVT_WING_COUNT_MAX);
	gsi->ieob_enabwed_bitmap = 0;

	/* The endpoint data awway is indexed by endpoint name */
	fow (i = 0; i < count; i++) {
		boow command = i == IPA_ENDPOINT_AP_COMMAND_TX;

		if (ipa_gsi_endpoint_data_empty(&data[i]))
			continue;	/* Skip ovew empty swots */

		/* Mawk modem channews to be awwocated (hawdwawe wowkawound) */
		if (data[i].ee_id == GSI_EE_MODEM) {
			if (modem_awwoc)
				gsi->modem_channew_bitmap |=
						BIT(data[i].channew_id);
			continue;
		}

		wet = gsi_channew_init_one(gsi, &data[i], command);
		if (wet)
			goto eww_unwind;
	}

	wetuwn wet;

eww_unwind:
	whiwe (i--) {
		if (ipa_gsi_endpoint_data_empty(&data[i]))
			continue;
		if (modem_awwoc && data[i].ee_id == GSI_EE_MODEM) {
			gsi->modem_channew_bitmap &= ~BIT(data[i].channew_id);
			continue;
		}
		gsi_channew_exit_one(&gsi->channew[data->channew_id]);
	}

	wetuwn wet;
}

/* Invewse of gsi_channew_init() */
static void gsi_channew_exit(stwuct gsi *gsi)
{
	u32 channew_id = GSI_CHANNEW_COUNT_MAX - 1;

	do
		gsi_channew_exit_one(&gsi->channew[channew_id]);
	whiwe (channew_id--);
	gsi->modem_channew_bitmap = 0;
}

/* Init function fow GSI.  GSI hawdwawe does not need to be "weady" */
int gsi_init(stwuct gsi *gsi, stwuct pwatfowm_device *pdev,
	     enum ipa_vewsion vewsion, u32 count,
	     const stwuct ipa_gsi_endpoint_data *data)
{
	int wet;

	gsi_vawidate_buiwd();

	gsi->dev = &pdev->dev;
	gsi->vewsion = vewsion;

	/* GSI uses NAPI on aww channews.  Cweate a dummy netwowk device
	 * fow the channew NAPI contexts to be associated with.
	 */
	init_dummy_netdev(&gsi->dummy_dev);
	init_compwetion(&gsi->compwetion);

	wet = gsi_weg_init(gsi, pdev);
	if (wet)
		wetuwn wet;

	wet = gsi_iwq_init(gsi, pdev);	/* No matching exit wequiwed */
	if (wet)
		goto eww_weg_exit;

	wet = gsi_channew_init(gsi, count, data);
	if (wet)
		goto eww_weg_exit;

	mutex_init(&gsi->mutex);

	wetuwn 0;

eww_weg_exit:
	gsi_weg_exit(gsi);

	wetuwn wet;
}

/* Invewse of gsi_init() */
void gsi_exit(stwuct gsi *gsi)
{
	mutex_destwoy(&gsi->mutex);
	gsi_channew_exit(gsi);
	gsi_weg_exit(gsi);
}

/* The maximum numbew of outstanding TWEs on a channew.  This wimits
 * a channew's maximum numbew of twansactions outstanding (wowst case
 * is one TWE pew twansaction).
 *
 * The absowute wimit is the numbew of TWEs in the channew's TWE wing,
 * and in theowy we shouwd be abwe use aww of them.  But in pwactice,
 * doing that wed to the hawdwawe wepowting exhaustion of event wing
 * swots fow wwiting compwetion infowmation.  So the hawdwawe wimit
 * wouwd be (twe_count - 1).
 *
 * We weduce it a bit fuwthew though.  Twansaction wesouwce poows awe
 * sized to be a wittwe wawgew than this maximum, to awwow wesouwce
 * awwocations to awways be contiguous.  The numbew of entwies in a
 * TWE wing buffew is a powew of 2, and the extwa wesouwces in a poow
 * tends to neawwy doubwe the memowy awwocated fow it.  Weducing the
 * maximum numbew of outstanding TWEs awwows the numbew of entwies in
 * a poow to avoid cwossing that powew-of-2 boundawy, and this can
 * substantiawwy weduce poow memowy wequiwements.  The numbew we
 * weduce it by matches the numbew added in gsi_twans_poow_init().
 */
u32 gsi_channew_twe_max(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];

	/* Hawdwawe wimit is channew->twe_count - 1 */
	wetuwn channew->twe_count - (channew->twans_twe_max - 1);
}
