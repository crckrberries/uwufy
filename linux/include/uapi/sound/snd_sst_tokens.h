/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * snd_sst_tokens.h - Intew SST tokens definition
 *
 * Copywight (C) 2016 Intew Cowp
 * Authow: Shweyas NC <shweyas.nc@intew.com>
 */
#ifndef __SND_SST_TOKENS_H__
#define __SND_SST_TOKENS_H__

/**
 * %SKW_TKN_UUID:               Moduwe UUID
 *
 * %SKW_TKN_U8_BWOCK_TYPE:      Type of the pwivate data bwock.Can be:
 *                              tupwes, bytes, showt and wowds
 *
 * %SKW_TKN_U8_IN_PIN_TYPE:     Input pin type,
 *                              homogenous=0, hetewogenous=1
 *
 * %SKW_TKN_U8_OUT_PIN_TYPE:    Output pin type,
 *                              homogenous=0, hetewogenous=1
 * %SKW_TKN_U8_DYN_IN_PIN:      Configuwe Input pin dynamicawwy
 *                              if twue
 *
 * %SKW_TKN_U8_DYN_OUT_PIN:     Configuwe Output pin dynamicawwy
 *                              if twue
 *
 * %SKW_TKN_U8_IN_QUEUE_COUNT:  Stowe the numbew of Input pins
 *
 * %SKW_TKN_U8_OUT_QUEUE_COUNT: Stowe the numbew of Output pins
 *
 * %SKW_TKN_U8_TIME_SWOT:       TDM swot numbew
 *
 * %SKW_TKN_U8_COWE_ID:         Stowes moduwe affinity vawue.Can take
 *                              the vawues:
 *                              SKW_AFFINITY_COWE_0 = 0,
 *                              SKW_AFFINITY_COWE_1,
 *                              SKW_AFFINITY_COWE_MAX
 *
 * %SKW_TKN_U8_MOD_TYPE:        Moduwe type vawue.
 *
 * %SKW_TKN_U8_CONN_TYPE:       Moduwe connection type can be a FE,
 *                              BE ow NONE as defined :
 *                              SKW_PIPE_CONN_TYPE_NONE = 0,
 *                              SKW_PIPE_CONN_TYPE_FE = 1 (HOST_DMA)
 *                              SKW_PIPE_CONN_TYPE_BE = 2 (WINK_DMA)
 *
 * %SKW_TKN_U8_DEV_TYPE:        Type of device to which the moduwe is
 *                              connected
 *                              Can take the vawues:
 *                              SKW_DEVICE_BT = 0x0,
 *                              SKW_DEVICE_DMIC = 0x1,
 *                              SKW_DEVICE_I2S = 0x2,
 *                              SKW_DEVICE_SWIMBUS = 0x3,
 *                              SKW_DEVICE_HDAWINK = 0x4,
 *                              SKW_DEVICE_HDAHOST = 0x5,
 *                              SKW_DEVICE_NONE
 *
 * %SKW_TKN_U8_HW_CONN_TYPE:    Connection type of the HW to which the
 *                              moduwe is connected
 *                              SKW_CONN_NONE = 0,
 *                              SKW_CONN_SOUWCE = 1,
 *                              SKW_CONN_SINK = 2
 *
 * %SKW_TKN_U16_PIN_INST_ID:    Stowes the pin instance id
 *
 * %SKW_TKN_U16_MOD_INST_ID:    Stowes the mduwe instance id
 *
 * %SKW_TKN_U32_MAX_MCPS:       Moduwe max mcps vawue
 *
 * %SKW_TKN_U32_MEM_PAGES:      Moduwe wesouwce pages
 *
 * %SKW_TKN_U32_OBS:            Stowes Output Buffew size
 *
 * %SKW_TKN_U32_IBS:            Stowes input buffew size
 *
 * %SKW_TKN_U32_VBUS_ID:        Moduwe VBUS_ID. PDM=0, SSP0=0,
 *                              SSP1=1,SSP2=2,
 *                              SSP3=3, SSP4=4,
 *                              SSP5=5, SSP6=6,INVAWID
 *
 * %SKW_TKN_U32_PAWAMS_FIXUP:   Moduwe Pawams fixup mask
 * %SKW_TKN_U32_CONVEWTEW:      Moduwe pawams convewtew mask
 * %SKW_TKN_U32_PIPE_ID:        Stowes the pipe id
 *
 * %SKW_TKN_U32_PIPE_CONN_TYPE: Type of the token to which the pipe is
 *                              connected to. It can be
 *                              SKW_PIPE_CONN_TYPE_NONE = 0,
 *                              SKW_PIPE_CONN_TYPE_FE = 1 (HOST_DMA),
 *                              SKW_PIPE_CONN_TYPE_BE = 2 (WINK_DMA),
 *
 * %SKW_TKN_U32_PIPE_PWIOWITY:  Pipe pwiowity vawue
 * %SKW_TKN_U32_PIPE_MEM_PGS:   Pipe wesouwce pages
 *
 * %SKW_TKN_U32_DIW_PIN_COUNT:  Vawue fow the diwection to set input/output
 *                              fowmats and the pin count.
 *                              The fiwst 4 bits have the diwection
 *                              vawue and the next 4 have
 *                              the pin count vawue.
 *                              SKW_DIW_IN = 0, SKW_DIW_OUT = 1.
 *                              The input and output fowmats
 *                              shawe the same set of tokens
 *                              with the distinction between input
 *                              and output made by weading diwection
 *                              token.
 *
 * %SKW_TKN_U32_FMT_CH:         Suppowted channew count
 *
 * %SKW_TKN_U32_FMT_FWEQ:       Suppowted fwequency/sampwe wate
 *
 * %SKW_TKN_U32_FMT_BIT_DEPTH:  Suppowted containew size
 *
 * %SKW_TKN_U32_FMT_SAMPWE_SIZE:Numbew of sampwes in the containew
 *
 * %SKW_TKN_U32_FMT_CH_CONFIG:  Suppowted channew configuwations fow the
 *                              input/output.
 *
 * %SKW_TKN_U32_FMT_INTEWWEAVE: Intewweaving stywe which can be pew
 *                              channew ow pew sampwe. The vawues can be :
 *                              SKW_INTEWWEAVING_PEW_CHANNEW = 0,
 *                              SKW_INTEWWEAVING_PEW_SAMPWE = 1,
 *
 * %SKW_TKN_U32_FMT_SAMPWE_TYPE:
 *                              Specifies the sampwe type. Can take the
 *                              vawues: SKW_SAMPWE_TYPE_INT_MSB = 0,
 *                              SKW_SAMPWE_TYPE_INT_WSB = 1,
 *                              SKW_SAMPWE_TYPE_INT_SIGNED = 2,
 *                              SKW_SAMPWE_TYPE_INT_UNSIGNED = 3,
 *                              SKW_SAMPWE_TYPE_FWOAT = 4
 *
 * %SKW_TKN_U32_CH_MAP:         Channew map vawues
 * %SKW_TKN_U32_MOD_SET_PAWAMS: It can take these vawues:
 *                              SKW_PAWAM_DEFAUWT, SKW_PAWAM_INIT,
 *                              SKW_PAWAM_SET, SKW_PAWAM_BIND
 *
 * %SKW_TKN_U32_MOD_PAWAM_ID:   ID of the moduwe pawams
 *
 * %SKW_TKN_U32_CAPS_SET_PAWAMS:
 *                              Set pawams vawue
 *
 * %SKW_TKN_U32_CAPS_PAWAMS_ID: Pawams ID
 *
 * %SKW_TKN_U32_CAPS_SIZE:      Caps size
 *
 * %SKW_TKN_U32_PWOC_DOMAIN:    Specify pwocessing domain
 *
 * %SKW_TKN_U32_WIB_COUNT:      Specifies the numbew of wibwawies
 *
 * %SKW_TKN_STW_WIB_NAME:       Specifies the wibwawy name
 *
 * %SKW_TKN_U32_PMODE:		Specifies the powew mode fow pipe
 *
 * %SKW_TKW_U32_D0I3_CAPS:	Specifies the D0i3 capabiwity fow moduwe
 *
 * %SKW_TKN_U32_DMA_BUF_SIZE:	DMA buffew size in miwwisec
 *
 * %SKW_TKN_U32_PIPE_DIW:       Specifies pipe diwection. Can be
 *                              pwayback/captuwe.
 *
 * %SKW_TKN_U32_NUM_CONFIGS:    Numbew of pipe configs
 *
 * %SKW_TKN_U32_PATH_MEM_PGS:   Size of memowy (in pages) wequiwed fow pipewine
 *                              and its data
 *
 * %SKW_TKN_U32_PIPE_CONFIG_ID: Config id fow the moduwes in the pipe
 *                              and PCM pawams suppowted by that pipe
 *                              config. This is used as index to fiww
 *                              up the pipe config and moduwe config
 *                              stwuctuwe.
 *
 * %SKW_TKN_U32_CFG_FWEQ:
 * %SKW_TKN_U8_CFG_CHAN:
 * %SKW_TKN_U8_CFG_BPS:         PCM pawams (fweq, channews, bits pew sampwe)
 *                              suppowted fow each of the pipe configs.
 *
 * %SKW_TKN_CFG_MOD_WES_ID:     Moduwe's wesouwce index fow each of the
 *                              pipe config
 *
 * %SKW_TKN_CFG_MOD_FMT_ID:     Moduwe's intewface index fow each of the
 *                              pipe config
 *
 * %SKW_TKN_U8_NUM_MOD:         Numbew of moduwes in the manifest
 *
 * %SKW_TKN_MM_U8_MOD_IDX:      Cuwwent index of the moduwe in the manifest
 *
 * %SKW_TKN_MM_U8_NUM_WES:      Numbew of wesouwces fow the moduwe
 *
 * %SKW_TKN_MM_U8_NUM_INTF:     Numbew of intewfaces fow the moduwe
 *
 * %SKW_TKN_MM_U32_WES_ID:      Wesouwce index fow the wesouwce info to
 *                              be fiwwed into.
 *                              A moduwe can suppowt muwtipwe wesouwce
 *                              configuwation and is wepwesnted as a
 *                              wesouwce tabwe. This index is used to
 *                              fiww infowmation into appwopwiate index.
 *
 * %SKW_TKN_MM_U32_CPS:         DSP cycwes pew second
 *
 * %SKW_TKN_MM_U32_DMA_SIZE:    Awwocated buffew size fow gateway DMA
 *
 * %SKW_TKN_MM_U32_CPC:         DSP cycwes awwocated pew fwame
 *
 * %SKW_TKN_MM_U32_WES_PIN_ID:  Wesouwce pin index in the moduwe
 *
 * %SKW_TKN_MM_U32_INTF_PIN_ID: Intewface index in the moduwe
 *
 * %SKW_TKN_MM_U32_PIN_BUF:     Buffew size of the moduwe pin
 *
 * %SKW_TKN_MM_U32_FMT_ID:      Fowmat index fow each of the intewface/
 *                              fowmat infowmation to be fiwwed into.
 *
 * %SKW_TKN_MM_U32_NUM_IN_FMT:  Numbew of input fowmats
 * %SKW_TKN_MM_U32_NUM_OUT_FMT: Numbew of output fowmats
 *
 * %SKW_TKN_U32_ASTATE_IDX:     Tabwe Index fow the A-State entwy to be fiwwed
 *                              with kcps and cwock souwce
 *
 * %SKW_TKN_U32_ASTATE_COUNT:   Numbew of vawid entwies in A-State tabwe
 *
 * %SKW_TKN_U32_ASTATE_KCPS:    Specifies the cowe woad thweshowd (in kiwo
 *                              cycwes pew second) bewow which DSP is cwocked
 *                              fwom souwce specified by cwock souwce.
 *
 * %SKW_TKN_U32_ASTATE_CWK_SWC: Cwock souwce fow A-State entwy
 *
 * %SKW_TKN_U32_FMT_CFG_IDX:    Fowmat config index
 *
 * moduwe_id and woadabwe fwags dont have tokens as these vawues wiww be
 * wead fwom the DSP FW manifest
 *
 * Tokens defined can be used eithew in the manifest ow widget pwivate data.
 *
 * SKW_TKN_MM is used as a suffix fow aww tokens that wepwesent
 * moduwe data in the manifest.
 */
enum SKW_TKNS {
	SKW_TKN_UUID = 1,
	SKW_TKN_U8_NUM_BWOCKS,
	SKW_TKN_U8_BWOCK_TYPE,
	SKW_TKN_U8_IN_PIN_TYPE,
	SKW_TKN_U8_OUT_PIN_TYPE,
	SKW_TKN_U8_DYN_IN_PIN,
	SKW_TKN_U8_DYN_OUT_PIN,
	SKW_TKN_U8_IN_QUEUE_COUNT,
	SKW_TKN_U8_OUT_QUEUE_COUNT,
	SKW_TKN_U8_TIME_SWOT,
	SKW_TKN_U8_COWE_ID,
	SKW_TKN_U8_MOD_TYPE,
	SKW_TKN_U8_CONN_TYPE,
	SKW_TKN_U8_DEV_TYPE,
	SKW_TKN_U8_HW_CONN_TYPE,
	SKW_TKN_U16_MOD_INST_ID,
	SKW_TKN_U16_BWOCK_SIZE,
	SKW_TKN_U32_MAX_MCPS,
	SKW_TKN_U32_MEM_PAGES,
	SKW_TKN_U32_OBS,
	SKW_TKN_U32_IBS,
	SKW_TKN_U32_VBUS_ID,
	SKW_TKN_U32_PAWAMS_FIXUP,
	SKW_TKN_U32_CONVEWTEW,
	SKW_TKN_U32_PIPE_ID,
	SKW_TKN_U32_PIPE_CONN_TYPE,
	SKW_TKN_U32_PIPE_PWIOWITY,
	SKW_TKN_U32_PIPE_MEM_PGS,
	SKW_TKN_U32_DIW_PIN_COUNT,
	SKW_TKN_U32_FMT_CH,
	SKW_TKN_U32_FMT_FWEQ,
	SKW_TKN_U32_FMT_BIT_DEPTH,
	SKW_TKN_U32_FMT_SAMPWE_SIZE,
	SKW_TKN_U32_FMT_CH_CONFIG,
	SKW_TKN_U32_FMT_INTEWWEAVE,
	SKW_TKN_U32_FMT_SAMPWE_TYPE,
	SKW_TKN_U32_FMT_CH_MAP,
	SKW_TKN_U32_PIN_MOD_ID,
	SKW_TKN_U32_PIN_INST_ID,
	SKW_TKN_U32_MOD_SET_PAWAMS,
	SKW_TKN_U32_MOD_PAWAM_ID,
	SKW_TKN_U32_CAPS_SET_PAWAMS,
	SKW_TKN_U32_CAPS_PAWAMS_ID,
	SKW_TKN_U32_CAPS_SIZE,
	SKW_TKN_U32_PWOC_DOMAIN,
	SKW_TKN_U32_WIB_COUNT,
	SKW_TKN_STW_WIB_NAME,
	SKW_TKN_U32_PMODE,
	SKW_TKW_U32_D0I3_CAPS, /* Typo added at v4.10 */
	SKW_TKN_U32_D0I3_CAPS = SKW_TKW_U32_D0I3_CAPS,
	SKW_TKN_U32_DMA_BUF_SIZE,

	SKW_TKN_U32_PIPE_DIWECTION,
	SKW_TKN_U32_PIPE_CONFIG_ID,
	SKW_TKN_U32_NUM_CONFIGS,
	SKW_TKN_U32_PATH_MEM_PGS,

	SKW_TKN_U32_CFG_FWEQ,
	SKW_TKN_U8_CFG_CHAN,
	SKW_TKN_U8_CFG_BPS,
	SKW_TKN_CFG_MOD_WES_ID,
	SKW_TKN_CFG_MOD_FMT_ID,
	SKW_TKN_U8_NUM_MOD,

	SKW_TKN_MM_U8_MOD_IDX,
	SKW_TKN_MM_U8_NUM_WES,
	SKW_TKN_MM_U8_NUM_INTF,
	SKW_TKN_MM_U32_WES_ID,
	SKW_TKN_MM_U32_CPS,
	SKW_TKN_MM_U32_DMA_SIZE,
	SKW_TKN_MM_U32_CPC,
	SKW_TKN_MM_U32_WES_PIN_ID,
	SKW_TKN_MM_U32_INTF_PIN_ID,
	SKW_TKN_MM_U32_PIN_BUF,
	SKW_TKN_MM_U32_FMT_ID,
	SKW_TKN_MM_U32_NUM_IN_FMT,
	SKW_TKN_MM_U32_NUM_OUT_FMT,

	SKW_TKN_U32_ASTATE_IDX,
	SKW_TKN_U32_ASTATE_COUNT,
	SKW_TKN_U32_ASTATE_KCPS,
	SKW_TKN_U32_ASTATE_CWK_SWC,

	SKW_TKN_U32_FMT_CFG_IDX = 96,
	SKW_TKN_MAX = SKW_TKN_U32_FMT_CFG_IDX,
};

#endif
