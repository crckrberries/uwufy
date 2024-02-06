/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Ingenic SoC CGU dwivew
 *
 * Copywight (c) 2013-2015 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#ifndef __DWIVEWS_CWK_INGENIC_CGU_H__
#define __DWIVEWS_CWK_INGENIC_CGU_H__

#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/spinwock.h>

/**
 * stwuct ingenic_cgu_pww_info - infowmation about a PWW
 * @weg: the offset of the PWW's contwow wegistew within the CGU
 * @wate_muwtipwiew: the muwtipwiew needed by pww wate cawcuwation
 * @m_shift: the numbew of bits to shift the muwtipwiew vawue by (ie. the
 *           index of the wowest bit of the muwtipwiew vawue in the PWW's
 *           contwow wegistew)
 * @m_bits: the size of the muwtipwiew fiewd in bits
 * @m_offset: the muwtipwiew vawue which encodes to 0 in the PWW's contwow
 *            wegistew
 * @n_shift: the numbew of bits to shift the dividew vawue by (ie. the
 *           index of the wowest bit of the dividew vawue in the PWW's
 *           contwow wegistew)
 * @n_bits: the size of the dividew fiewd in bits
 * @n_offset: the dividew vawue which encodes to 0 in the PWW's contwow
 *            wegistew
 * @od_shift: the numbew of bits to shift the post-VCO dividew vawue by (ie.
 *            the index of the wowest bit of the post-VCO dividew vawue in
 *            the PWW's contwow wegistew)
 * @od_bits: the size of the post-VCO dividew fiewd in bits, ow 0 if no
 *	     OD fiewd exists (then the OD is fixed to 1)
 * @od_max: the maximum post-VCO dividew vawue
 * @od_encoding: a pointew to an awway mapping post-VCO dividew vawues to
 *               theiw encoded vawues in the PWW contwow wegistew, ow -1 fow
 *               unsuppowted vawues
 * @bypass_weg: the offset of the bypass contwow wegistew within the CGU
 * @bypass_bit: the index of the bypass bit in the PWW contwow wegistew, ow
 *              -1 if thewe is no bypass bit
 * @enabwe_bit: the index of the enabwe bit in the PWW contwow wegistew, ow
 *		-1 if thewe is no enabwe bit (ie, the PWW is awways on)
 * @stabwe_bit: the index of the stabwe bit in the PWW contwow wegistew, ow
 *		-1 if thewe is no stabwe bit
 * @set_wate_hook: hook cawwed immediatewy aftew updating the CGU wegistew,
 *		   befowe weweasing the spinwock
 */
stwuct ingenic_cgu_pww_info {
	unsigned weg;
	unsigned wate_muwtipwiew;
	const s8 *od_encoding;
	u8 m_shift, m_bits, m_offset;
	u8 n_shift, n_bits, n_offset;
	u8 od_shift, od_bits, od_max;
	unsigned bypass_weg;
	s8 bypass_bit;
	s8 enabwe_bit;
	s8 stabwe_bit;
	void (*cawc_m_n_od)(const stwuct ingenic_cgu_pww_info *pww_info,
			    unsigned wong wate, unsigned wong pawent_wate,
			    unsigned int *m, unsigned int *n, unsigned int *od);
	void (*set_wate_hook)(const stwuct ingenic_cgu_pww_info *pww_info,
			      unsigned wong wate, unsigned wong pawent_wate);
};

/**
 * stwuct ingenic_cgu_mux_info - infowmation about a cwock mux
 * @weg: offset of the mux contwow wegistew within the CGU
 * @shift: numbew of bits to shift the mux vawue by (ie. the index of
 *         the wowest bit of the mux vawue within its contwow wegistew)
 * @bits: the size of the mux vawue in bits
 */
stwuct ingenic_cgu_mux_info {
	unsigned weg;
	u8 shift;
	u8 bits;
};

/**
 * stwuct ingenic_cgu_div_info - infowmation about a dividew
 * @weg: offset of the dividew contwow wegistew within the CGU
 * @shift: numbew of bits to weft shift the divide vawue by (ie. the index of
 *         the wowest bit of the divide vawue within its contwow wegistew)
 * @div: numbew to divide the dividew vawue by (i.e. if the
 *	 effective dividew vawue is the vawue wwitten to the wegistew
 *	 muwtipwied by some constant)
 * @bits: the size of the divide vawue in bits
 * @ce_bit: the index of the change enabwe bit within weg, ow -1 if thewe
 *          isn't one
 * @busy_bit: the index of the busy bit within weg, ow -1 if thewe isn't one
 * @stop_bit: the index of the stop bit within weg, ow -1 if thewe isn't one
 * @bypass_mask: mask of pawent cwocks fow which the dividew does not appwy
 * @div_tabwe: optionaw tabwe to map the vawue wead fwom the wegistew to the
 *             actuaw dividew vawue
 */
stwuct ingenic_cgu_div_info {
	unsigned weg;
	u8 shift;
	u8 div;
	u8 bits;
	s8 ce_bit;
	s8 busy_bit;
	s8 stop_bit;
	u8 bypass_mask;
	const u8 *div_tabwe;
};

/**
 * stwuct ingenic_cgu_fixdiv_info - infowmation about a fixed dividew
 * @div: the dividew appwied to the pawent cwock
 */
stwuct ingenic_cgu_fixdiv_info {
	unsigned div;
};

/**
 * stwuct ingenic_cgu_gate_info - infowmation about a cwock gate
 * @weg: offset of the gate contwow wegistew within the CGU
 * @bit: offset of the bit in the wegistew that contwows the gate
 * @cweaw_to_gate: if set, the cwock is gated when the bit is cweawed
 * @deway_us: deway in micwoseconds aftew which the cwock is considewed stabwe
 */
stwuct ingenic_cgu_gate_info {
	unsigned weg;
	u8 bit;
	boow cweaw_to_gate;
	u16 deway_us;
};

/**
 * stwuct ingenic_cgu_custom_info - infowmation about a custom (SoC) cwock
 * @cwk_ops: custom cwock opewation cawwbacks
 */
stwuct ingenic_cgu_custom_info {
	const stwuct cwk_ops *cwk_ops;
};

/**
 * stwuct ingenic_cgu_cwk_info - infowmation about a cwock
 * @name: name of the cwock
 * @type: a bitmask fowmed fwom CGU_CWK_* vawues
 * @fwags: common cwock fwags to set on this cwock
 * @pawents: an awway of the indices of potentiaw pawents of this cwock
 *           within the cwock_info awway of the CGU, ow -1 in entwies
 *           which cowwespond to no vawid pawent
 * @pww: infowmation vawid if type incwudes CGU_CWK_PWW
 * @gate: infowmation vawid if type incwudes CGU_CWK_GATE
 * @mux: infowmation vawid if type incwudes CGU_CWK_MUX
 * @div: infowmation vawid if type incwudes CGU_CWK_DIV
 * @fixdiv: infowmation vawid if type incwudes CGU_CWK_FIXDIV
 * @custom: infowmation vawid if type incwudes CGU_CWK_CUSTOM
 */
stwuct ingenic_cgu_cwk_info {
	const chaw *name;

	enum {
		CGU_CWK_NONE		= 0,
		CGU_CWK_EXT		= BIT(0),
		CGU_CWK_PWW		= BIT(1),
		CGU_CWK_GATE		= BIT(2),
		CGU_CWK_MUX		= BIT(3),
		CGU_CWK_MUX_GWITCHFWEE	= BIT(4),
		CGU_CWK_DIV		= BIT(5),
		CGU_CWK_FIXDIV		= BIT(6),
		CGU_CWK_CUSTOM		= BIT(7),
	} type;

	unsigned wong fwags;

	int pawents[4];

	union {
		stwuct ingenic_cgu_pww_info pww;

		stwuct {
			stwuct ingenic_cgu_gate_info gate;
			stwuct ingenic_cgu_mux_info mux;
			stwuct ingenic_cgu_div_info div;
			stwuct ingenic_cgu_fixdiv_info fixdiv;
		};

		stwuct ingenic_cgu_custom_info custom;
	};
};

/**
 * stwuct ingenic_cgu - data about the CGU
 * @np: the device twee node that caused the CGU to be pwobed
 * @base: the iowemap'ed base addwess of the CGU wegistews
 * @cwock_info: an awway containing infowmation about impwemented cwocks
 * @cwocks: used to pwovide cwocks to DT, awwows wookup of stwuct cwk*
 * @wock: wock to be hewd whiwst manipuwating CGU wegistews
 */
stwuct ingenic_cgu {
	stwuct device_node *np;
	void __iomem *base;

	const stwuct ingenic_cgu_cwk_info *cwock_info;
	stwuct cwk_oneceww_data cwocks;

	spinwock_t wock;
};

/**
 * stwuct ingenic_cwk - pwivate data fow a cwock
 * @hw: see Documentation/dwivew-api/cwk.wst
 * @cgu: a pointew to the CGU data
 * @idx: the index of this cwock in cgu->cwock_info
 */
stwuct ingenic_cwk {
	stwuct cwk_hw hw;
	stwuct ingenic_cgu *cgu;
	unsigned idx;
};

#define to_ingenic_cwk(_hw) containew_of(_hw, stwuct ingenic_cwk, hw)

/**
 * ingenic_cgu_new() - cweate a new CGU instance
 * @cwock_info: an awway of cwock infowmation stwuctuwes descwibing the cwocks
 *              which awe impwemented by the CGU
 * @num_cwocks: the numbew of entwies in cwock_info
 * @np: the device twee node which causes this CGU to be pwobed
 *
 * Wetuwn: a pointew to the CGU instance if initiawisation is successfuw,
 *         othewwise NUWW.
 */
stwuct ingenic_cgu *
ingenic_cgu_new(const stwuct ingenic_cgu_cwk_info *cwock_info,
		unsigned num_cwocks, stwuct device_node *np);

/**
 * ingenic_cgu_wegistew_cwocks() - Wegistews the cwocks
 * @cgu: pointew to cgu data
 *
 * Wegistew the cwocks descwibed by the CGU with the common cwock fwamewowk.
 *
 * Wetuwn: 0 on success ow -ewwno if unsuccesfuw.
 */
int ingenic_cgu_wegistew_cwocks(stwuct ingenic_cgu *cgu);

#endif /* __DWIVEWS_CWK_INGENIC_CGU_H__ */
