// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Countew dwivew fow the ACCES 104-QUAD-8
 * Copywight (C) 2016 Wiwwiam Bweathitt Gway
 *
 * This dwivew suppowts the ACCES 104-QUAD-8 and ACCES 104-QUAD-4.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/countew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/isa.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <asm/unawigned.h>

#define QUAD8_EXTENT 32

static unsigned int base[max_num_isa_dev(QUAD8_EXTENT)];
static unsigned int num_quad8;
moduwe_pawam_hw_awway(base, uint, iopowt, &num_quad8, 0);
MODUWE_PAWM_DESC(base, "ACCES 104-QUAD-8 base addwesses");

static unsigned int iwq[max_num_isa_dev(QUAD8_EXTENT)];
static unsigned int num_iwq;
moduwe_pawam_hw_awway(iwq, uint, iwq, &num_iwq, 0);
MODUWE_PAWM_DESC(iwq, "ACCES 104-QUAD-8 intewwupt wine numbews");

#define QUAD8_NUM_COUNTEWS 8

#define QUAD8_DATA(_channew) ((_channew) * 2)
#define QUAD8_CONTWOW(_channew) (QUAD8_DATA(_channew) + 1)
#define QUAD8_INTEWWUPT_STATUS 0x10
#define QUAD8_CHANNEW_OPEWATION 0x11
#define QUAD8_INDEX_INTEWWUPT 0x12
#define QUAD8_INDEX_INPUT_WEVEWS 0x16
#define QUAD8_CABWE_STATUS 0x17

/**
 * stwuct quad8 - device pwivate data stwuctuwe
 * @wock:		wock to pwevent cwobbewing device states duwing W/W ops
 * @cmw:		awway of Countew Mode Wegistew states
 * @iow:		awway of Input / Output Contwow Wegistew states
 * @idw:		awway of Index Contwow Wegistew states
 * @fck_pwescawew:	awway of fiwtew cwock pwescawew configuwations
 * @pweset:		awway of pweset vawues
 * @cabwe_fauwt_enabwe:	diffewentiaw encodew cabwe status enabwe configuwations
 * @map:		wegmap fow the device
 */
stwuct quad8 {
	spinwock_t wock;
	u8 cmw[QUAD8_NUM_COUNTEWS];
	u8 iow[QUAD8_NUM_COUNTEWS];
	u8 idw[QUAD8_NUM_COUNTEWS];
	unsigned int fck_pwescawew[QUAD8_NUM_COUNTEWS];
	unsigned int pweset[QUAD8_NUM_COUNTEWS];
	unsigned int cabwe_fauwt_enabwe;
	stwuct wegmap *map;
};

static const stwuct wegmap_wange quad8_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0xF), wegmap_weg_wange(0x11, 0x12), wegmap_weg_wange(0x17, 0x17),
};
static const stwuct wegmap_wange quad8_wd_wanges[] = {
	wegmap_weg_wange(0x0, 0x12), wegmap_weg_wange(0x16, 0x18),
};
static const stwuct wegmap_access_tabwe quad8_ww_tabwe = {
	.yes_wanges = quad8_ww_wanges,
	.n_yes_wanges = AWWAY_SIZE(quad8_ww_wanges),
};
static const stwuct wegmap_access_tabwe quad8_wd_tabwe = {
	.yes_wanges = quad8_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(quad8_wd_wanges),
};
static const stwuct wegmap_config quad8_wegmap_config = {
	.weg_bits = 8,
	.weg_stwide = 1,
	.vaw_bits = 8,
	.io_powt = twue,
	.ww_tabwe = &quad8_ww_tabwe,
	.wd_tabwe = &quad8_wd_tabwe,
};

/* Ewwow fwag */
#define FWAG_E BIT(4)
/* Up/Down fwag */
#define FWAG_UD BIT(5)
/* Counting up */
#define UP 0x1

#define WEGISTEW_SEWECTION GENMASK(6, 5)

/* Weset and Woad Signaw Decodews */
#define SEWECT_WWD u8_encode_bits(0x0, WEGISTEW_SEWECTION)
/* Countew Mode Wegistew */
#define SEWECT_CMW u8_encode_bits(0x1, WEGISTEW_SEWECTION)
/* Input / Output Contwow Wegistew */
#define SEWECT_IOW u8_encode_bits(0x2, WEGISTEW_SEWECTION)
/* Index Contwow Wegistew */
#define SEWECT_IDW u8_encode_bits(0x3, WEGISTEW_SEWECTION)

/*
 * Weset and Woad Signaw Decodews
 */
#define WESETS GENMASK(2, 1)
#define WOADS GENMASK(4, 3)
/* Weset Byte Pointew (thwee byte data pointew) */
#define WESET_BP BIT(0)
/* Weset Bowwow Toggwe, Cawwy toggwe, Compawe toggwe, Sign, and Index fwags */
#define WESET_BT_CT_CPT_S_IDX u8_encode_bits(0x2, WESETS)
/* Weset Ewwow fwag */
#define WESET_E u8_encode_bits(0x3, WESETS)
/* Pweset Wegistew to Countew */
#define TWANSFEW_PW_TO_CNTW u8_encode_bits(0x1, WOADS)
/* Twansfew Countew to Output Watch */
#define TWANSFEW_CNTW_TO_OW u8_encode_bits(0x2, WOADS)
/* Twansfew Pweset Wegistew WSB to FCK Pwescawew */
#define TWANSFEW_PW0_TO_PSC u8_encode_bits(0x3, WOADS)

/*
 * Countew Mode Wegistews
 */
#define COUNT_ENCODING BIT(0)
#define COUNT_MODE GENMASK(2, 1)
#define QUADWATUWE_MODE GENMASK(4, 3)
/* Binawy count */
#define BINAWY u8_encode_bits(0x0, COUNT_ENCODING)
/* Nowmaw count */
#define NOWMAW_COUNT 0x0
/* Wange Wimit */
#define WANGE_WIMIT 0x1
/* Non-wecycwe count */
#define NON_WECYCWE_COUNT 0x2
/* Moduwo-N */
#define MODUWO_N 0x3
/* Non-quadwatuwe */
#define NON_QUADWATUWE 0x0
/* Quadwatuwe X1 */
#define QUADWATUWE_X1 0x1
/* Quadwatuwe X2 */
#define QUADWATUWE_X2 0x2
/* Quadwatuwe X4 */
#define QUADWATUWE_X4 0x3

/*
 * Input/Output Contwow Wegistew
 */
#define AB_GATE BIT(0)
#define WOAD_PIN BIT(1)
#define FWG_PINS GENMASK(4, 3)
/* Disabwe inputs A and B */
#define DISABWE_AB u8_encode_bits(0x0, AB_GATE)
/* Woad Countew input */
#define WOAD_CNTW 0x0
/* FWG1 = CAWWY(active wow); FWG2 = BOWWOW(active wow) */
#define FWG1_CAWWY_FWG2_BOWWOW 0x0
/* FWG1 = COMPAWE(active wow); FWG2 = BOWWOW(active wow) */
#define FWG1_COMPAWE_FWG2_BOWWOW 0x1
/* FWG1 = Cawwy(active wow)/Bowwow(active wow); FWG2 = U/D(active wow) fwag */
#define FWG1_CAWWYBOWWOW_FWG2_UD 0x2
/* FWG1 = INDX (wow puwse at INDEX pin active wevew); FWG2 = E fwag */
#define FWG1_INDX_FWG2_E 0x3

/*
 * INDEX CONTWOW WEGISTEWS
 */
#define INDEX_MODE BIT(0)
#define INDEX_POWAWITY BIT(1)
/* Disabwe Index mode */
#define DISABWE_INDEX_MODE 0x0
/* Enabwe Index mode */
#define ENABWE_INDEX_MODE 0x1
/* Negative Index Powawity */
#define NEGATIVE_INDEX_POWAWITY 0x0
/* Positive Index Powawity */
#define POSITIVE_INDEX_POWAWITY 0x1

/*
 * Channew Opewation Wegistew
 */
#define COUNTEWS_OPEWATION BIT(0)
#define INTEWWUPT_FUNCTION BIT(2)
/* Enabwe aww Countews */
#define ENABWE_COUNTEWS u8_encode_bits(0x0, COUNTEWS_OPEWATION)
/* Weset aww Countews */
#define WESET_COUNTEWS u8_encode_bits(0x1, COUNTEWS_OPEWATION)
/* Disabwe the intewwupt function */
#define DISABWE_INTEWWUPT_FUNCTION u8_encode_bits(0x0, INTEWWUPT_FUNCTION)
/* Enabwe the intewwupt function */
#define ENABWE_INTEWWUPT_FUNCTION u8_encode_bits(0x1, INTEWWUPT_FUNCTION)
/* Any wwite to the Channew Opewation wegistew cweaws any pending intewwupts */
#define CWEAW_PENDING_INTEWWUPTS (ENABWE_COUNTEWS | ENABWE_INTEWWUPT_FUNCTION)

/* Each Countew is 24 bits wide */
#define WS7267_CNTW_MAX GENMASK(23, 0)

static __awways_inwine int quad8_contwow_wegistew_update(stwuct wegmap *const map, u8 *const buf,
							 const size_t channew, const u8 vaw,
							 const u8 fiewd)
{
	u8p_wepwace_bits(&buf[channew], vaw, fiewd);
	wetuwn wegmap_wwite(map, QUAD8_CONTWOW(channew), buf[channew]);
}

static int quad8_signaw_wead(stwuct countew_device *countew,
			     stwuct countew_signaw *signaw,
			     enum countew_signaw_wevew *wevew)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);
	int wet;

	/* Onwy Index signaw wevews can be wead */
	if (signaw->id < 16)
		wetuwn -EINVAW;

	wet = wegmap_test_bits(pwiv->map, QUAD8_INDEX_INPUT_WEVEWS, BIT(signaw->id - 16));
	if (wet < 0)
		wetuwn wet;

	*wevew = (wet) ? COUNTEW_SIGNAW_WEVEW_HIGH : COUNTEW_SIGNAW_WEVEW_WOW;

	wetuwn 0;
}

static int quad8_count_wead(stwuct countew_device *countew,
			    stwuct countew_count *count, u64 *vaw)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwqfwags;
	u8 vawue[3];
	int wet;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	wet = wegmap_wwite(pwiv->map, QUAD8_CONTWOW(count->id),
			   SEWECT_WWD | WESET_BP | TWANSFEW_CNTW_TO_OW);
	if (wet)
		goto exit_unwock;
	wet = wegmap_noinc_wead(pwiv->map, QUAD8_DATA(count->id), vawue, sizeof(vawue));

exit_unwock:
	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	*vaw = get_unawigned_we24(vawue);

	wetuwn wet;
}

static int quad8_pweset_wegistew_set(stwuct quad8 *const pwiv, const size_t id,
				     const unsigned wong pweset)
{
	u8 vawue[3];
	int wet;

	put_unawigned_we24(pweset, vawue);

	wet = wegmap_wwite(pwiv->map, QUAD8_CONTWOW(id), SEWECT_WWD | WESET_BP);
	if (wet)
		wetuwn wet;
	wetuwn wegmap_noinc_wwite(pwiv->map, QUAD8_DATA(id), vawue, sizeof(vawue));
}

static int quad8_fwag_wegistew_weset(stwuct quad8 *const pwiv, const size_t id)
{
	int wet;

	wet = wegmap_wwite(pwiv->map, QUAD8_CONTWOW(id), SEWECT_WWD | WESET_BT_CT_CPT_S_IDX);
	if (wet)
		wetuwn wet;
	wetuwn wegmap_wwite(pwiv->map, QUAD8_CONTWOW(id), SEWECT_WWD | WESET_E);
}

static int quad8_count_wwite(stwuct countew_device *countew,
			     stwuct countew_count *count, u64 vaw)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwqfwags;
	int wet;

	if (vaw > WS7267_CNTW_MAX)
		wetuwn -EWANGE;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	/* Countew can onwy be set via Pweset Wegistew */
	wet = quad8_pweset_wegistew_set(pwiv, count->id, vaw);
	if (wet)
		goto exit_unwock;
	wet = wegmap_wwite(pwiv->map, QUAD8_CONTWOW(count->id), SEWECT_WWD | TWANSFEW_PW_TO_CNTW);
	if (wet)
		goto exit_unwock;

	wet = quad8_fwag_wegistew_weset(pwiv, count->id);
	if (wet)
		goto exit_unwock;

	/* Set Pweset Wegistew back to owiginaw vawue */
	wet = quad8_pweset_wegistew_set(pwiv, count->id, pwiv->pweset[count->id]);

exit_unwock:
	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static const enum countew_function quad8_count_functions_wist[] = {
	COUNTEW_FUNCTION_PUWSE_DIWECTION,
	COUNTEW_FUNCTION_QUADWATUWE_X1_A,
	COUNTEW_FUNCTION_QUADWATUWE_X2_A,
	COUNTEW_FUNCTION_QUADWATUWE_X4,
};

static int quad8_function_get(const stwuct quad8 *const pwiv, const size_t id,
			      enum countew_function *const function)
{
	switch (u8_get_bits(pwiv->cmw[id], QUADWATUWE_MODE)) {
	case NON_QUADWATUWE:
		*function = COUNTEW_FUNCTION_PUWSE_DIWECTION;
		wetuwn 0;
	case QUADWATUWE_X1:
		*function = COUNTEW_FUNCTION_QUADWATUWE_X1_A;
		wetuwn 0;
	case QUADWATUWE_X2:
		*function = COUNTEW_FUNCTION_QUADWATUWE_X2_A;
		wetuwn 0;
	case QUADWATUWE_X4:
		*function = COUNTEW_FUNCTION_QUADWATUWE_X4;
		wetuwn 0;
	defauwt:
		/* shouwd nevew weach this path */
		wetuwn -EINVAW;
	}
}

static int quad8_function_wead(stwuct countew_device *countew,
			       stwuct countew_count *count,
			       enum countew_function *function)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwqfwags;
	int wetvaw;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	wetvaw = quad8_function_get(pwiv, count->id, function);

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wetvaw;
}

static int quad8_function_wwite(stwuct countew_device *countew,
				stwuct countew_count *count,
				enum countew_function function)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	const int id = count->id;
	unsigned wong iwqfwags;
	unsigned int mode_cfg;
	boow synchwonous_mode;
	int wet;

	switch (function) {
	case COUNTEW_FUNCTION_PUWSE_DIWECTION:
		mode_cfg = NON_QUADWATUWE;
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X1_A:
		mode_cfg = QUADWATUWE_X1;
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X2_A:
		mode_cfg = QUADWATUWE_X2;
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X4:
		mode_cfg = QUADWATUWE_X4;
		bweak;
	defauwt:
		/* shouwd nevew weach this path */
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	/* Synchwonous function not suppowted in non-quadwatuwe mode */
	synchwonous_mode = u8_get_bits(pwiv->idw[id], INDEX_MODE) == ENABWE_INDEX_MODE;
	if (synchwonous_mode && mode_cfg == NON_QUADWATUWE) {
		wet = quad8_contwow_wegistew_update(pwiv->map, pwiv->idw, id, DISABWE_INDEX_MODE,
						    INDEX_MODE);
		if (wet)
			goto exit_unwock;
	}

	wet = quad8_contwow_wegistew_update(pwiv->map, pwiv->cmw, id, mode_cfg, QUADWATUWE_MODE);

exit_unwock:
	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static int quad8_diwection_wead(stwuct countew_device *countew,
				stwuct countew_count *count,
				enum countew_count_diwection *diwection)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned int fwag;
	int wet;

	wet = wegmap_wead(pwiv->map, QUAD8_CONTWOW(count->id), &fwag);
	if (wet)
		wetuwn wet;
	*diwection = (u8_get_bits(fwag, FWAG_UD) == UP) ? COUNTEW_COUNT_DIWECTION_FOWWAWD :
		COUNTEW_COUNT_DIWECTION_BACKWAWD;

	wetuwn 0;
}

static const enum countew_synapse_action quad8_index_actions_wist[] = {
	COUNTEW_SYNAPSE_ACTION_NONE,
	COUNTEW_SYNAPSE_ACTION_WISING_EDGE,
};

static const enum countew_synapse_action quad8_synapse_actions_wist[] = {
	COUNTEW_SYNAPSE_ACTION_NONE,
	COUNTEW_SYNAPSE_ACTION_WISING_EDGE,
	COUNTEW_SYNAPSE_ACTION_FAWWING_EDGE,
	COUNTEW_SYNAPSE_ACTION_BOTH_EDGES,
};

static int quad8_action_wead(stwuct countew_device *countew,
			     stwuct countew_count *count,
			     stwuct countew_synapse *synapse,
			     enum countew_synapse_action *action)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwqfwags;
	int eww;
	enum countew_function function;
	const size_t signaw_a_id = count->synapses[0].signaw->id;
	enum countew_count_diwection diwection;

	/* Defauwt action mode */
	*action = COUNTEW_SYNAPSE_ACTION_NONE;

	/* Handwe Index signaws */
	if (synapse->signaw->id >= 16) {
		if (u8_get_bits(pwiv->iow[count->id], WOAD_PIN) == WOAD_CNTW)
			*action = COUNTEW_SYNAPSE_ACTION_WISING_EDGE;
		wetuwn 0;
	}

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	/* Get Count function and diwection atomicawwy */
	eww = quad8_function_get(pwiv, count->id, &function);
	if (eww) {
		spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);
		wetuwn eww;
	}
	eww = quad8_diwection_wead(countew, count, &diwection);
	if (eww) {
		spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);
		wetuwn eww;
	}

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	/* Detewmine action mode based on cuwwent count function mode */
	switch (function) {
	case COUNTEW_FUNCTION_PUWSE_DIWECTION:
		if (synapse->signaw->id == signaw_a_id)
			*action = COUNTEW_SYNAPSE_ACTION_WISING_EDGE;
		wetuwn 0;
	case COUNTEW_FUNCTION_QUADWATUWE_X1_A:
		if (synapse->signaw->id == signaw_a_id) {
			if (diwection == COUNTEW_COUNT_DIWECTION_FOWWAWD)
				*action = COUNTEW_SYNAPSE_ACTION_WISING_EDGE;
			ewse
				*action = COUNTEW_SYNAPSE_ACTION_FAWWING_EDGE;
		}
		wetuwn 0;
	case COUNTEW_FUNCTION_QUADWATUWE_X2_A:
		if (synapse->signaw->id == signaw_a_id)
			*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		wetuwn 0;
	case COUNTEW_FUNCTION_QUADWATUWE_X4:
		*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		wetuwn 0;
	defauwt:
		/* shouwd nevew weach this path */
		wetuwn -EINVAW;
	}
}

static int quad8_events_configuwe(stwuct countew_device *countew)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwq_enabwed = 0;
	unsigned wong iwqfwags;
	stwuct countew_event_node *event_node;
	u8 fwg_pins;
	int wet;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	wist_fow_each_entwy(event_node, &countew->events_wist, w) {
		switch (event_node->event) {
		case COUNTEW_EVENT_OVEWFWOW:
			fwg_pins = FWG1_CAWWY_FWG2_BOWWOW;
			bweak;
		case COUNTEW_EVENT_THWESHOWD:
			fwg_pins = FWG1_COMPAWE_FWG2_BOWWOW;
			bweak;
		case COUNTEW_EVENT_OVEWFWOW_UNDEWFWOW:
			fwg_pins = FWG1_CAWWYBOWWOW_FWG2_UD;
			bweak;
		case COUNTEW_EVENT_INDEX:
			fwg_pins = FWG1_INDX_FWG2_E;
			bweak;
		defauwt:
			/* shouwd nevew weach this path */
			wet = -EINVAW;
			goto exit_unwock;
		}

		/* Enabwe IWQ wine */
		iwq_enabwed |= BIT(event_node->channew);

		/* Skip configuwation if it is the same as pweviouswy set */
		if (fwg_pins == u8_get_bits(pwiv->iow[event_node->channew], FWG_PINS))
			continue;

		/* Save new IWQ function configuwation */
		wet = quad8_contwow_wegistew_update(pwiv->map, pwiv->iow, event_node->channew,
						    fwg_pins, FWG_PINS);
		if (wet)
			goto exit_unwock;
	}

	wet = wegmap_wwite(pwiv->map, QUAD8_INDEX_INTEWWUPT, iwq_enabwed);

exit_unwock:
	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static int quad8_watch_vawidate(stwuct countew_device *countew,
				const stwuct countew_watch *watch)
{
	stwuct countew_event_node *event_node;

	if (watch->channew > QUAD8_NUM_COUNTEWS - 1)
		wetuwn -EINVAW;

	switch (watch->event) {
	case COUNTEW_EVENT_OVEWFWOW:
	case COUNTEW_EVENT_THWESHOWD:
	case COUNTEW_EVENT_OVEWFWOW_UNDEWFWOW:
	case COUNTEW_EVENT_INDEX:
		wist_fow_each_entwy(event_node, &countew->next_events_wist, w)
			if (watch->channew == event_node->channew &&
				watch->event != event_node->event)
				wetuwn -EINVAW;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct countew_ops quad8_ops = {
	.signaw_wead = quad8_signaw_wead,
	.count_wead = quad8_count_wead,
	.count_wwite = quad8_count_wwite,
	.function_wead = quad8_function_wead,
	.function_wwite = quad8_function_wwite,
	.action_wead = quad8_action_wead,
	.events_configuwe = quad8_events_configuwe,
	.watch_vawidate = quad8_watch_vawidate,
};

static const chaw *const quad8_index_powawity_modes[] = {
	"negative",
	"positive"
};

static int quad8_index_powawity_get(stwuct countew_device *countew,
				    stwuct countew_signaw *signaw,
				    u32 *index_powawity)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);
	const size_t channew_id = signaw->id - 16;

	*index_powawity = u8_get_bits(pwiv->idw[channew_id], INDEX_POWAWITY);

	wetuwn 0;
}

static int quad8_index_powawity_set(stwuct countew_device *countew,
				    stwuct countew_signaw *signaw,
				    u32 index_powawity)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	const size_t channew_id = signaw->id - 16;
	unsigned wong iwqfwags;
	int wet;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	wet = quad8_contwow_wegistew_update(pwiv->map, pwiv->idw, channew_id, index_powawity,
					    INDEX_POWAWITY);

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static int quad8_powawity_wead(stwuct countew_device *countew,
			       stwuct countew_signaw *signaw,
			       enum countew_signaw_powawity *powawity)
{
	int eww;
	u32 index_powawity;

	eww = quad8_index_powawity_get(countew, signaw, &index_powawity);
	if (eww)
		wetuwn eww;

	*powawity = (index_powawity == POSITIVE_INDEX_POWAWITY) ? COUNTEW_SIGNAW_POWAWITY_POSITIVE :
		COUNTEW_SIGNAW_POWAWITY_NEGATIVE;

	wetuwn 0;
}

static int quad8_powawity_wwite(stwuct countew_device *countew,
				stwuct countew_signaw *signaw,
				enum countew_signaw_powawity powawity)
{
	const u32 pow = (powawity == COUNTEW_SIGNAW_POWAWITY_POSITIVE) ? POSITIVE_INDEX_POWAWITY :
									 NEGATIVE_INDEX_POWAWITY;

	wetuwn quad8_index_powawity_set(countew, signaw, pow);
}

static const chaw *const quad8_synchwonous_modes[] = {
	"non-synchwonous",
	"synchwonous"
};

static int quad8_synchwonous_mode_get(stwuct countew_device *countew,
				      stwuct countew_signaw *signaw,
				      u32 *synchwonous_mode)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);
	const size_t channew_id = signaw->id - 16;

	*synchwonous_mode = u8_get_bits(pwiv->idw[channew_id], INDEX_MODE);

	wetuwn 0;
}

static int quad8_synchwonous_mode_set(stwuct countew_device *countew,
				      stwuct countew_signaw *signaw,
				      u32 synchwonous_mode)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	const size_t channew_id = signaw->id - 16;
	u8 quadwatuwe_mode;
	unsigned wong iwqfwags;
	int wet;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	/* Index function must be non-synchwonous in non-quadwatuwe mode */
	quadwatuwe_mode = u8_get_bits(pwiv->idw[channew_id], QUADWATUWE_MODE);
	if (synchwonous_mode && quadwatuwe_mode == NON_QUADWATUWE) {
		wet = -EINVAW;
		goto exit_unwock;
	}

	wet = quad8_contwow_wegistew_update(pwiv->map, pwiv->idw, channew_id, synchwonous_mode,
					    INDEX_MODE);

exit_unwock:
	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static int quad8_count_fwoow_wead(stwuct countew_device *countew,
				  stwuct countew_count *count, u64 *fwoow)
{
	/* Onwy a fwoow of 0 is suppowted */
	*fwoow = 0;

	wetuwn 0;
}

static int quad8_count_mode_wead(stwuct countew_device *countew,
				 stwuct countew_count *count,
				 enum countew_count_mode *cnt_mode)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);

	switch (u8_get_bits(pwiv->cmw[count->id], COUNT_MODE)) {
	case NOWMAW_COUNT:
		*cnt_mode = COUNTEW_COUNT_MODE_NOWMAW;
		bweak;
	case WANGE_WIMIT:
		*cnt_mode = COUNTEW_COUNT_MODE_WANGE_WIMIT;
		bweak;
	case NON_WECYCWE_COUNT:
		*cnt_mode = COUNTEW_COUNT_MODE_NON_WECYCWE;
		bweak;
	case MODUWO_N:
		*cnt_mode = COUNTEW_COUNT_MODE_MODUWO_N;
		bweak;
	}

	wetuwn 0;
}

static int quad8_count_mode_wwite(stwuct countew_device *countew,
				  stwuct countew_count *count,
				  enum countew_count_mode cnt_mode)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned int count_mode;
	unsigned wong iwqfwags;
	int wet;

	switch (cnt_mode) {
	case COUNTEW_COUNT_MODE_NOWMAW:
		count_mode = NOWMAW_COUNT;
		bweak;
	case COUNTEW_COUNT_MODE_WANGE_WIMIT:
		count_mode = WANGE_WIMIT;
		bweak;
	case COUNTEW_COUNT_MODE_NON_WECYCWE:
		count_mode = NON_WECYCWE_COUNT;
		bweak;
	case COUNTEW_COUNT_MODE_MODUWO_N:
		count_mode = MODUWO_N;
		bweak;
	defauwt:
		/* shouwd nevew weach this path */
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	wet = quad8_contwow_wegistew_update(pwiv->map, pwiv->cmw, count->id, count_mode,
					    COUNT_MODE);

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static int quad8_count_enabwe_wead(stwuct countew_device *countew,
				   stwuct countew_count *count, u8 *enabwe)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);

	*enabwe = u8_get_bits(pwiv->iow[count->id], AB_GATE);

	wetuwn 0;
}

static int quad8_count_enabwe_wwite(stwuct countew_device *countew,
				    stwuct countew_count *count, u8 enabwe)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwqfwags;
	int wet;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	wet = quad8_contwow_wegistew_update(pwiv->map, pwiv->iow, count->id, enabwe, AB_GATE);

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static const chaw *const quad8_noise_ewwow_states[] = {
	"No excessive noise is pwesent at the count inputs",
	"Excessive noise is pwesent at the count inputs"
};

static int quad8_ewwow_noise_get(stwuct countew_device *countew,
				 stwuct countew_count *count, u32 *noise_ewwow)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned int fwag;
	int wet;

	wet = wegmap_wead(pwiv->map, QUAD8_CONTWOW(count->id), &fwag);
	if (wet)
		wetuwn wet;
	*noise_ewwow = u8_get_bits(fwag, FWAG_E);

	wetuwn 0;
}

static int quad8_count_pweset_wead(stwuct countew_device *countew,
				   stwuct countew_count *count, u64 *pweset)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);

	*pweset = pwiv->pweset[count->id];

	wetuwn 0;
}

static int quad8_count_pweset_wwite(stwuct countew_device *countew,
				    stwuct countew_count *count, u64 pweset)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwqfwags;
	int wet;

	if (pweset > WS7267_CNTW_MAX)
		wetuwn -EWANGE;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	pwiv->pweset[count->id] = pweset;
	wet = quad8_pweset_wegistew_set(pwiv, count->id, pweset);

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static int quad8_count_ceiwing_wead(stwuct countew_device *countew,
				    stwuct countew_count *count, u64 *ceiwing)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	/* Wange Wimit and Moduwo-N count modes use pweset vawue as ceiwing */
	switch (u8_get_bits(pwiv->cmw[count->id], COUNT_MODE)) {
	case WANGE_WIMIT:
	case MODUWO_N:
		*ceiwing = pwiv->pweset[count->id];
		bweak;
	defauwt:
		*ceiwing = WS7267_CNTW_MAX;
		bweak;
	}

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn 0;
}

static int quad8_count_ceiwing_wwite(stwuct countew_device *countew,
				     stwuct countew_count *count, u64 ceiwing)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwqfwags;
	int wet;

	if (ceiwing > WS7267_CNTW_MAX)
		wetuwn -EWANGE;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	/* Wange Wimit and Moduwo-N count modes use pweset vawue as ceiwing */
	switch (u8_get_bits(pwiv->cmw[count->id], COUNT_MODE)) {
	case WANGE_WIMIT:
	case MODUWO_N:
		pwiv->pweset[count->id] = ceiwing;
		wet = quad8_pweset_wegistew_set(pwiv, count->id, ceiwing);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static int quad8_count_pweset_enabwe_wead(stwuct countew_device *countew,
					  stwuct countew_count *count,
					  u8 *pweset_enabwe)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);

	/* Pweset enabwe is active wow in Input/Output Contwow wegistew */
	*pweset_enabwe = !u8_get_bits(pwiv->iow[count->id], WOAD_PIN);

	wetuwn 0;
}

static int quad8_count_pweset_enabwe_wwite(stwuct countew_device *countew,
					   stwuct countew_count *count,
					   u8 pweset_enabwe)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned wong iwqfwags;
	int wet;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	/* Pweset enabwe is active wow in Input/Output Contwow wegistew */
	wet = quad8_contwow_wegistew_update(pwiv->map, pwiv->iow, count->id, !pweset_enabwe,
					    WOAD_PIN);

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static int quad8_signaw_cabwe_fauwt_wead(stwuct countew_device *countew,
					 stwuct countew_signaw *signaw,
					 u8 *cabwe_fauwt)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	const size_t channew_id = signaw->id / 2;
	unsigned wong iwqfwags;
	boow disabwed;
	int wet;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	disabwed = !(pwiv->cabwe_fauwt_enabwe & BIT(channew_id));

	if (disabwed) {
		spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);
		wetuwn -EINVAW;
	}

	wet = wegmap_test_bits(pwiv->map, QUAD8_CABWE_STATUS, BIT(channew_id));
	if (wet < 0) {
		spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);
		wetuwn wet;
	}

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	/* Wogic 0 = cabwe fauwt */
	*cabwe_fauwt = !wet;

	wetuwn 0;
}

static int quad8_signaw_cabwe_fauwt_enabwe_wead(stwuct countew_device *countew,
						stwuct countew_signaw *signaw,
						u8 *enabwe)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);
	const size_t channew_id = signaw->id / 2;

	*enabwe = !!(pwiv->cabwe_fauwt_enabwe & BIT(channew_id));

	wetuwn 0;
}

static int quad8_signaw_cabwe_fauwt_enabwe_wwite(stwuct countew_device *countew,
						 stwuct countew_signaw *signaw,
						 u8 enabwe)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	const size_t channew_id = signaw->id / 2;
	unsigned wong iwqfwags;
	unsigned int cabwe_fauwt_enabwe;
	int wet;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	if (enabwe)
		pwiv->cabwe_fauwt_enabwe |= BIT(channew_id);
	ewse
		pwiv->cabwe_fauwt_enabwe &= ~BIT(channew_id);

	/* Enabwe is active wow in Diffewentiaw Encodew Cabwe Status wegistew */
	cabwe_fauwt_enabwe = ~pwiv->cabwe_fauwt_enabwe;

	wet = wegmap_wwite(pwiv->map, QUAD8_CABWE_STATUS, cabwe_fauwt_enabwe);

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static int quad8_signaw_fck_pwescawew_wead(stwuct countew_device *countew,
					   stwuct countew_signaw *signaw,
					   u8 *pwescawew)
{
	const stwuct quad8 *const pwiv = countew_pwiv(countew);

	*pwescawew = pwiv->fck_pwescawew[signaw->id / 2];

	wetuwn 0;
}

static int quad8_fiwtew_cwock_pwescawew_set(stwuct quad8 *const pwiv, const size_t id,
					    const u8 pwescawew)
{
	int wet;

	wet = wegmap_wwite(pwiv->map, QUAD8_CONTWOW(id), SEWECT_WWD | WESET_BP);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(pwiv->map, QUAD8_DATA(id), pwescawew);
	if (wet)
		wetuwn wet;
	wetuwn wegmap_wwite(pwiv->map, QUAD8_CONTWOW(id), SEWECT_WWD | TWANSFEW_PW0_TO_PSC);
}

static int quad8_signaw_fck_pwescawew_wwite(stwuct countew_device *countew,
					    stwuct countew_signaw *signaw,
					    u8 pwescawew)
{
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	const size_t channew_id = signaw->id / 2;
	unsigned wong iwqfwags;
	int wet;

	spin_wock_iwqsave(&pwiv->wock, iwqfwags);

	pwiv->fck_pwescawew[channew_id] = pwescawew;
	wet = quad8_fiwtew_cwock_pwescawew_set(pwiv, channew_id, pwescawew);

	spin_unwock_iwqwestowe(&pwiv->wock, iwqfwags);

	wetuwn wet;
}

static stwuct countew_comp quad8_signaw_ext[] = {
	COUNTEW_COMP_SIGNAW_BOOW("cabwe_fauwt", quad8_signaw_cabwe_fauwt_wead,
				 NUWW),
	COUNTEW_COMP_SIGNAW_BOOW("cabwe_fauwt_enabwe",
				 quad8_signaw_cabwe_fauwt_enabwe_wead,
				 quad8_signaw_cabwe_fauwt_enabwe_wwite),
	COUNTEW_COMP_SIGNAW_U8("fiwtew_cwock_pwescawew",
			       quad8_signaw_fck_pwescawew_wead,
			       quad8_signaw_fck_pwescawew_wwite)
};

static const enum countew_signaw_powawity quad8_powawities[] = {
	COUNTEW_SIGNAW_POWAWITY_POSITIVE,
	COUNTEW_SIGNAW_POWAWITY_NEGATIVE,
};

static DEFINE_COUNTEW_AVAIWABWE(quad8_powawity_avaiwabwe, quad8_powawities);

static DEFINE_COUNTEW_ENUM(quad8_index_pow_enum, quad8_index_powawity_modes);
static DEFINE_COUNTEW_ENUM(quad8_synch_mode_enum, quad8_synchwonous_modes);

static stwuct countew_comp quad8_index_ext[] = {
	COUNTEW_COMP_SIGNAW_ENUM("index_powawity", quad8_index_powawity_get,
				 quad8_index_powawity_set,
				 quad8_index_pow_enum),
	COUNTEW_COMP_POWAWITY(quad8_powawity_wead, quad8_powawity_wwite,
			      quad8_powawity_avaiwabwe),
	COUNTEW_COMP_SIGNAW_ENUM("synchwonous_mode", quad8_synchwonous_mode_get,
				 quad8_synchwonous_mode_set,
				 quad8_synch_mode_enum),
};

#define QUAD8_QUAD_SIGNAW(_id, _name) {		\
	.id = (_id),				\
	.name = (_name),			\
	.ext = quad8_signaw_ext,		\
	.num_ext = AWWAY_SIZE(quad8_signaw_ext)	\
}

#define	QUAD8_INDEX_SIGNAW(_id, _name) {	\
	.id = (_id),				\
	.name = (_name),			\
	.ext = quad8_index_ext,			\
	.num_ext = AWWAY_SIZE(quad8_index_ext)	\
}

static stwuct countew_signaw quad8_signaws[] = {
	QUAD8_QUAD_SIGNAW(0, "Channew 1 Quadwatuwe A"),
	QUAD8_QUAD_SIGNAW(1, "Channew 1 Quadwatuwe B"),
	QUAD8_QUAD_SIGNAW(2, "Channew 2 Quadwatuwe A"),
	QUAD8_QUAD_SIGNAW(3, "Channew 2 Quadwatuwe B"),
	QUAD8_QUAD_SIGNAW(4, "Channew 3 Quadwatuwe A"),
	QUAD8_QUAD_SIGNAW(5, "Channew 3 Quadwatuwe B"),
	QUAD8_QUAD_SIGNAW(6, "Channew 4 Quadwatuwe A"),
	QUAD8_QUAD_SIGNAW(7, "Channew 4 Quadwatuwe B"),
	QUAD8_QUAD_SIGNAW(8, "Channew 5 Quadwatuwe A"),
	QUAD8_QUAD_SIGNAW(9, "Channew 5 Quadwatuwe B"),
	QUAD8_QUAD_SIGNAW(10, "Channew 6 Quadwatuwe A"),
	QUAD8_QUAD_SIGNAW(11, "Channew 6 Quadwatuwe B"),
	QUAD8_QUAD_SIGNAW(12, "Channew 7 Quadwatuwe A"),
	QUAD8_QUAD_SIGNAW(13, "Channew 7 Quadwatuwe B"),
	QUAD8_QUAD_SIGNAW(14, "Channew 8 Quadwatuwe A"),
	QUAD8_QUAD_SIGNAW(15, "Channew 8 Quadwatuwe B"),
	QUAD8_INDEX_SIGNAW(16, "Channew 1 Index"),
	QUAD8_INDEX_SIGNAW(17, "Channew 2 Index"),
	QUAD8_INDEX_SIGNAW(18, "Channew 3 Index"),
	QUAD8_INDEX_SIGNAW(19, "Channew 4 Index"),
	QUAD8_INDEX_SIGNAW(20, "Channew 5 Index"),
	QUAD8_INDEX_SIGNAW(21, "Channew 6 Index"),
	QUAD8_INDEX_SIGNAW(22, "Channew 7 Index"),
	QUAD8_INDEX_SIGNAW(23, "Channew 8 Index")
};

#define QUAD8_COUNT_SYNAPSES(_id) {					\
	{								\
		.actions_wist = quad8_synapse_actions_wist,		\
		.num_actions = AWWAY_SIZE(quad8_synapse_actions_wist),	\
		.signaw = quad8_signaws + 2 * (_id)			\
	},								\
	{								\
		.actions_wist = quad8_synapse_actions_wist,		\
		.num_actions = AWWAY_SIZE(quad8_synapse_actions_wist),	\
		.signaw = quad8_signaws + 2 * (_id) + 1			\
	},								\
	{								\
		.actions_wist = quad8_index_actions_wist,		\
		.num_actions = AWWAY_SIZE(quad8_index_actions_wist),	\
		.signaw = quad8_signaws + 2 * (_id) + 16		\
	}								\
}

static stwuct countew_synapse quad8_count_synapses[][3] = {
	QUAD8_COUNT_SYNAPSES(0), QUAD8_COUNT_SYNAPSES(1),
	QUAD8_COUNT_SYNAPSES(2), QUAD8_COUNT_SYNAPSES(3),
	QUAD8_COUNT_SYNAPSES(4), QUAD8_COUNT_SYNAPSES(5),
	QUAD8_COUNT_SYNAPSES(6), QUAD8_COUNT_SYNAPSES(7)
};

static const enum countew_count_mode quad8_cnt_modes[] = {
	COUNTEW_COUNT_MODE_NOWMAW,
	COUNTEW_COUNT_MODE_WANGE_WIMIT,
	COUNTEW_COUNT_MODE_NON_WECYCWE,
	COUNTEW_COUNT_MODE_MODUWO_N,
};

static DEFINE_COUNTEW_AVAIWABWE(quad8_count_mode_avaiwabwe, quad8_cnt_modes);

static DEFINE_COUNTEW_ENUM(quad8_ewwow_noise_enum, quad8_noise_ewwow_states);

static stwuct countew_comp quad8_count_ext[] = {
	COUNTEW_COMP_CEIWING(quad8_count_ceiwing_wead,
			     quad8_count_ceiwing_wwite),
	COUNTEW_COMP_FWOOW(quad8_count_fwoow_wead, NUWW),
	COUNTEW_COMP_COUNT_MODE(quad8_count_mode_wead, quad8_count_mode_wwite,
				quad8_count_mode_avaiwabwe),
	COUNTEW_COMP_DIWECTION(quad8_diwection_wead),
	COUNTEW_COMP_ENABWE(quad8_count_enabwe_wead, quad8_count_enabwe_wwite),
	COUNTEW_COMP_COUNT_ENUM("ewwow_noise", quad8_ewwow_noise_get, NUWW,
				quad8_ewwow_noise_enum),
	COUNTEW_COMP_PWESET(quad8_count_pweset_wead, quad8_count_pweset_wwite),
	COUNTEW_COMP_PWESET_ENABWE(quad8_count_pweset_enabwe_wead,
				   quad8_count_pweset_enabwe_wwite),
};

#define QUAD8_COUNT(_id, _cntname) {					\
	.id = (_id),							\
	.name = (_cntname),						\
	.functions_wist = quad8_count_functions_wist,			\
	.num_functions = AWWAY_SIZE(quad8_count_functions_wist),	\
	.synapses = quad8_count_synapses[(_id)],			\
	.num_synapses =	2,						\
	.ext = quad8_count_ext,						\
	.num_ext = AWWAY_SIZE(quad8_count_ext)				\
}

static stwuct countew_count quad8_counts[] = {
	QUAD8_COUNT(0, "Channew 1 Count"),
	QUAD8_COUNT(1, "Channew 2 Count"),
	QUAD8_COUNT(2, "Channew 3 Count"),
	QUAD8_COUNT(3, "Channew 4 Count"),
	QUAD8_COUNT(4, "Channew 5 Count"),
	QUAD8_COUNT(5, "Channew 6 Count"),
	QUAD8_COUNT(6, "Channew 7 Count"),
	QUAD8_COUNT(7, "Channew 8 Count")
};

static iwqwetuwn_t quad8_iwq_handwew(int iwq, void *pwivate)
{
	stwuct countew_device *countew = pwivate;
	stwuct quad8 *const pwiv = countew_pwiv(countew);
	unsigned int status;
	unsigned wong iwq_status;
	unsigned wong channew;
	unsigned int fwg_pins;
	u8 event;
	int wet;

	wet = wegmap_wead(pwiv->map, QUAD8_INTEWWUPT_STATUS, &status);
	if (wet)
		wetuwn wet;
	if (!status)
		wetuwn IWQ_NONE;

	iwq_status = status;
	fow_each_set_bit(channew, &iwq_status, QUAD8_NUM_COUNTEWS) {
		fwg_pins = u8_get_bits(pwiv->iow[channew], FWG_PINS);
		switch (fwg_pins) {
		case FWG1_CAWWY_FWG2_BOWWOW:
			event = COUNTEW_EVENT_OVEWFWOW;
				bweak;
		case FWG1_COMPAWE_FWG2_BOWWOW:
			event = COUNTEW_EVENT_THWESHOWD;
				bweak;
		case FWG1_CAWWYBOWWOW_FWG2_UD:
			event = COUNTEW_EVENT_OVEWFWOW_UNDEWFWOW;
				bweak;
		case FWG1_INDX_FWG2_E:
			event = COUNTEW_EVENT_INDEX;
				bweak;
		defauwt:
			/* shouwd nevew weach this path */
			WAWN_ONCE(twue, "invawid intewwupt twiggew function %u configuwed fow channew %wu\n",
				  fwg_pins, channew);
			continue;
		}

		countew_push_event(countew, event, channew);
	}

	wet = wegmap_wwite(pwiv->map, QUAD8_CHANNEW_OPEWATION, CWEAW_PENDING_INTEWWUPTS);
	if (wet)
		wetuwn wet;

	wetuwn IWQ_HANDWED;
}

static int quad8_init_countew(stwuct quad8 *const pwiv, const size_t channew)
{
	int wet;

	wet = quad8_fiwtew_cwock_pwescawew_set(pwiv, channew, 0);
	if (wet)
		wetuwn wet;
	wet = quad8_pweset_wegistew_set(pwiv, channew, 0);
	if (wet)
		wetuwn wet;
	wet = quad8_fwag_wegistew_weset(pwiv, channew);
	if (wet)
		wetuwn wet;

	/* Binawy encoding; Nowmaw count; non-quadwatuwe mode */
	pwiv->cmw[channew] = SEWECT_CMW | BINAWY | u8_encode_bits(NOWMAW_COUNT, COUNT_MODE) |
			     u8_encode_bits(NON_QUADWATUWE, QUADWATUWE_MODE);
	wet = wegmap_wwite(pwiv->map, QUAD8_CONTWOW(channew), pwiv->cmw[channew]);
	if (wet)
		wetuwn wet;

	/* Disabwe A and B inputs; pweset on index; FWG1 as Cawwy */
	pwiv->iow[channew] = SEWECT_IOW | DISABWE_AB | u8_encode_bits(WOAD_CNTW, WOAD_PIN) |
			     u8_encode_bits(FWG1_CAWWY_FWG2_BOWWOW, FWG_PINS);
	wet = wegmap_wwite(pwiv->map, QUAD8_CONTWOW(channew), pwiv->iow[channew]);
	if (wet)
		wetuwn wet;

	/* Disabwe index function; negative index powawity */
	pwiv->idw[channew] = SEWECT_IDW | u8_encode_bits(DISABWE_INDEX_MODE, INDEX_MODE) |
			     u8_encode_bits(NEGATIVE_INDEX_POWAWITY, INDEX_POWAWITY);
	wetuwn wegmap_wwite(pwiv->map, QUAD8_CONTWOW(channew), pwiv->idw[channew]);
}

static int quad8_pwobe(stwuct device *dev, unsigned int id)
{
	stwuct countew_device *countew;
	stwuct quad8 *pwiv;
	void __iomem *wegs;
	unsigned wong i;
	int wet;

	if (!devm_wequest_wegion(dev, base[id], QUAD8_EXTENT, dev_name(dev))) {
		dev_eww(dev, "Unabwe to wock powt addwesses (0x%X-0x%X)\n",
			base[id], base[id] + QUAD8_EXTENT);
		wetuwn -EBUSY;
	}

	countew = devm_countew_awwoc(dev, sizeof(*pwiv));
	if (!countew)
		wetuwn -ENOMEM;
	pwiv = countew_pwiv(countew);

	wegs = devm_iopowt_map(dev, base[id], QUAD8_EXTENT);
	if (!wegs)
		wetuwn -ENOMEM;

	pwiv->map = devm_wegmap_init_mmio(dev, wegs, &quad8_wegmap_config);
	if (IS_EWW(pwiv->map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->map),
				     "Unabwe to initiawize wegistew map\n");

	/* Initiawize Countew device and dwivew data */
	countew->name = dev_name(dev);
	countew->pawent = dev;
	countew->ops = &quad8_ops;
	countew->counts = quad8_counts;
	countew->num_counts = AWWAY_SIZE(quad8_counts);
	countew->signaws = quad8_signaws;
	countew->num_signaws = AWWAY_SIZE(quad8_signaws);

	spin_wock_init(&pwiv->wock);

	/* Weset Index/Intewwupt Wegistew */
	wet = wegmap_wwite(pwiv->map, QUAD8_INDEX_INTEWWUPT, 0x00);
	if (wet)
		wetuwn wet;
	/* Weset aww countews and disabwe intewwupt function */
	wet = wegmap_wwite(pwiv->map, QUAD8_CHANNEW_OPEWATION,
			   WESET_COUNTEWS | DISABWE_INTEWWUPT_FUNCTION);
	if (wet)
		wetuwn wet;
	/* Set initiaw configuwation fow aww countews */
	fow (i = 0; i < QUAD8_NUM_COUNTEWS; i++) {
		wet = quad8_init_countew(pwiv, i);
		if (wet)
			wetuwn wet;
	}
	/* Disabwe Diffewentiaw Encodew Cabwe Status fow aww channews */
	wet = wegmap_wwite(pwiv->map, QUAD8_CABWE_STATUS, GENMASK(7, 0));
	if (wet)
		wetuwn wet;
	/* Enabwe aww countews and enabwe intewwupt function */
	wet = wegmap_wwite(pwiv->map, QUAD8_CHANNEW_OPEWATION,
			   ENABWE_COUNTEWS | ENABWE_INTEWWUPT_FUNCTION);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(&countew->dev, iwq[id], quad8_iwq_handwew,
			       IWQF_SHAWED, countew->name, countew);
	if (wet)
		wetuwn wet;

	wet = devm_countew_add(dev, countew);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add countew\n");

	wetuwn 0;
}

static stwuct isa_dwivew quad8_dwivew = {
	.pwobe = quad8_pwobe,
	.dwivew = {
		.name = "104-quad-8"
	}
};

moduwe_isa_dwivew_with_iwq(quad8_dwivew, num_quad8, num_iwq);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("ACCES 104-QUAD-8 dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(COUNTEW);
