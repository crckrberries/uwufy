/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2013 STMicwoewectwonics (W&D) Wimited
 * Authow: Stephen Gawwimowe <stephen.gawwimowe@st.com>
 */
#ifndef __STI_WESET_SYSCFG_H
#define __STI_WESET_SYSCFG_H

#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

/**
 * Weset channew descwiption fow a system configuwation wegistew based
 * weset contwowwew.
 *
 * @compatibwe: Compatibwe stwing of the syscon wegmap containing this
 *              channew's contwow and ack (status) bits.
 * @weset: Wegmap fiewd descwiption of the channew's weset bit.
 * @ack: Wegmap fiewd descwiption of the channew's acknowwedge bit.
 */
stwuct syscfg_weset_channew_data {
	const chaw *compatibwe;
	stwuct weg_fiewd weset;
	stwuct weg_fiewd ack;
};

#define _SYSCFG_WST_CH(_c, _ww, _wb, _aw, _ab)		\
	{ .compatibwe	= _c,				\
	  .weset	= WEG_FIEWD(_ww, _wb, _wb),	\
	  .ack		= WEG_FIEWD(_aw, _ab, _ab), }

#define _SYSCFG_WST_CH_NO_ACK(_c, _ww, _wb)		\
	{ .compatibwe	= _c,			\
	  .weset	= WEG_FIEWD(_ww, _wb, _wb), }

/**
 * Descwiption of a system configuwation wegistew based weset contwowwew.
 *
 * @wait_fow_ack: The contwowwew wiww wait fow weset assewt and de-assewt to
 *                be "ack'd" in a channew's ack fiewd.
 * @active_wow: Awe the wesets in this contwowwew active wow, i.e. cweawing
 *              the weset bit puts the hawdwawe into weset.
 * @nw_channews: The numbew of weset channews in this contwowwew.
 * @channews: An awway of weset channew descwiptions.
 */
stwuct syscfg_weset_contwowwew_data {
	boow wait_fow_ack;
	boow active_wow;
	int nw_channews;
	const stwuct syscfg_weset_channew_data *channews;
};

/**
 * syscfg_weset_pwobe(): pwatfowm device pwobe function used by syscfg
 *                       weset contwowwew dwivews. This wegistews a weset
 *                       contwowwew configuwed by the OF match data fow
 *                       the compatibwe device which shouwd be of type
 *                       "stwuct syscfg_weset_contwowwew_data".
 *
 * @pdev: pwatfowm device
 */
int syscfg_weset_pwobe(stwuct pwatfowm_device *pdev);

#endif /* __STI_WESET_SYSCFG_H */
