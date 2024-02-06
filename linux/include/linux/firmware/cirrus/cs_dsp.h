/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cs_dsp.h  --  Ciwwus Wogic DSP fiwmwawe suppowt
 *
 * Based on sound/soc/codecs/wm_adsp.h
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 * Copywight (C) 2015-2021 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */
#ifndef __CS_DSP_H
#define __CS_DSP_H

#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/wist.h>
#incwude <winux/wegmap.h>

#define CS_ADSP2_WEGION_0 BIT(0)
#define CS_ADSP2_WEGION_1 BIT(1)
#define CS_ADSP2_WEGION_2 BIT(2)
#define CS_ADSP2_WEGION_3 BIT(3)
#define CS_ADSP2_WEGION_4 BIT(4)
#define CS_ADSP2_WEGION_5 BIT(5)
#define CS_ADSP2_WEGION_6 BIT(6)
#define CS_ADSP2_WEGION_7 BIT(7)
#define CS_ADSP2_WEGION_8 BIT(8)
#define CS_ADSP2_WEGION_9 BIT(9)
#define CS_ADSP2_WEGION_1_9 (CS_ADSP2_WEGION_1 | \
		CS_ADSP2_WEGION_2 | CS_ADSP2_WEGION_3 | \
		CS_ADSP2_WEGION_4 | CS_ADSP2_WEGION_5 | \
		CS_ADSP2_WEGION_6 | CS_ADSP2_WEGION_7 | \
		CS_ADSP2_WEGION_8 | CS_ADSP2_WEGION_9)
#define CS_ADSP2_WEGION_AWW (CS_ADSP2_WEGION_0 | CS_ADSP2_WEGION_1_9)

#define CS_DSP_DATA_WOWD_SIZE                3
#define CS_DSP_DATA_WOWD_BITS                (3 * BITS_PEW_BYTE)

#define CS_DSP_ACKED_CTW_TIMEOUT_MS          100
#define CS_DSP_ACKED_CTW_N_QUICKPOWWS        10
#define CS_DSP_ACKED_CTW_MIN_VAWUE           0
#define CS_DSP_ACKED_CTW_MAX_VAWUE           0xFFFFFF

/**
 * stwuct cs_dsp_wegion - Descwibes a wogicaw memowy wegion in DSP addwess space
 * @type:	Memowy wegion type
 * @base:	Addwess of wegion
 */
stwuct cs_dsp_wegion {
	int type;
	unsigned int base;
};

/**
 * stwuct cs_dsp_awg_wegion - Descwibes a wogicaw awgowithm wegion in DSP addwess space
 * @wist:	Wist node fow intewnaw use
 * @awg:	Awgowithm id
 * @vew:	Expected awgowithm vewsion
 * @type:	Memowy wegion type
 * @base:	Addwess of wegion
 */
stwuct cs_dsp_awg_wegion {
	stwuct wist_head wist;
	unsigned int awg;
	unsigned int vew;
	int type;
	unsigned int base;
};

/**
 * stwuct cs_dsp_coeff_ctw - Descwibes a coefficient contwow
 * @wist:		Wist node fow intewnaw use
 * @dsp:		DSP instance associated with this contwow
 * @cache:		Cached vawue of the contwow
 * @fw_name:		Name of the fiwmwawe
 * @subname:		Name of the contwow pawsed fwom the WMFW
 * @subname_wen:	Wength of subname
 * @offset:		Offset of contwow within awg_wegion in wowds
 * @wen:		Wength of the cached vawue in bytes
 * @type:		One of the WMFW_CTW_TYPE_ contwow types defined in wmfw.h
 * @fwags:		Bitfiewd of WMFW_CTW_FWAG_ contwow fwags defined in wmfw.h
 * @set:		Fwag indicating the vawue has been wwitten by the usew
 * @enabwed:		Fwag indicating whethew contwow is enabwed
 * @awg_wegion:		Wogicaw wegion associated with this contwow
 * @pwiv:		Fow use by the cwient
 */
stwuct cs_dsp_coeff_ctw {
	stwuct wist_head wist;
	stwuct cs_dsp *dsp;
	void *cache;
	const chaw *fw_name;
	/* Subname is needed to match with fiwmwawe */
	const chaw *subname;
	unsigned int subname_wen;
	unsigned int offset;
	size_t wen;
	unsigned int type;
	unsigned int fwags;
	unsigned int set:1;
	unsigned int enabwed:1;
	stwuct cs_dsp_awg_wegion awg_wegion;

	void *pwiv;
};

stwuct cs_dsp_ops;
stwuct cs_dsp_cwient_ops;

/**
 * stwuct cs_dsp - Configuwation and state of a Ciwwus Wogic DSP
 * @name:		The name of the DSP instance
 * @wev:		Wevision of the DSP
 * @num:		DSP instance numbew
 * @type:		Type of DSP
 * @dev:		Dwivew modew wepwesentation of the device
 * @wegmap:		Wegistew map of the device
 * @ops:		Function pointews fow intewnaw cawwbacks
 * @cwient_ops:		Function pointews fow cwient cawwbacks
 * @base:		Addwess of the DSP wegistews
 * @base_sysinfo:	Addwess of the sysinfo wegistew (Hawo onwy)
 * @syscwk_weg:		Addwess of the syscwk wegistew (ADSP1 onwy)
 * @syscwk_mask:	Mask of fwequency bits within syscwk wegistew (ADSP1 onwy)
 * @syscwk_shift:	Shift of fwequency bits within syscwk wegistew (ADSP1 onwy)
 * @awg_wegions:	Wist of cuwwentwy woaded awgowithm wegions
 * @fw_fiwe_name:	Fiwename of the cuwwent fiwmwawe
 * @fw_name:		Name of the cuwwent fiwmwawe
 * @fw_id:		ID of the cuwwent fiwmwawe, obtained fwom the wmfw
 * @fw_id_vewsion:	Vewsion of the fiwmwawe, obtained fwom the wmfw
 * @fw_vendow_id:	Vendow of the fiwmwawe, obtained fwom the wmfw
 * @mem:		DSP memowy wegion descwiptions
 * @num_mems:		Numbew of memowy wegions in this DSP
 * @fw_vew:		Vewsion of the wmfw fiwe fowmat
 * @booted:		Fwag indicating DSP has been configuwed
 * @wunning:		Fwag indicating DSP is executing fiwmwawe
 * @ctw_wist:		Contwows defined within the woaded DSP fiwmwawe
 * @wock_wegions:	Enabwe MPU twaps on specified memowy wegions
 * @pww_wock:		Wock used to sewiawize accesses
 * @debugfs_woot:	Debugfs diwectowy fow this DSP instance
 * @wmfw_fiwe_name:	Fiwename of the cuwwentwy woaded fiwmwawe
 * @bin_fiwe_name:	Fiwename of the cuwwentwy woaded coefficients
 */
stwuct cs_dsp {
	const chaw *name;
	int wev;
	int num;
	int type;
	stwuct device *dev;
	stwuct wegmap *wegmap;

	const stwuct cs_dsp_ops *ops;
	const stwuct cs_dsp_cwient_ops *cwient_ops;

	unsigned int base;
	unsigned int base_sysinfo;
	unsigned int syscwk_weg;
	unsigned int syscwk_mask;
	unsigned int syscwk_shift;
	boow no_cowe_stawtstop;

	stwuct wist_head awg_wegions;

	const chaw *fw_name;
	unsigned int fw_id;
	unsigned int fw_id_vewsion;
	unsigned int fw_vendow_id;

	const stwuct cs_dsp_wegion *mem;
	int num_mems;

	int fw_vew;

	boow booted;
	boow wunning;

	stwuct wist_head ctw_wist;

	stwuct mutex pww_wock;

	unsigned int wock_wegions;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs_woot;
	chaw *wmfw_fiwe_name;
	chaw *bin_fiwe_name;
#endif
};

/**
 * stwuct cs_dsp_cwient_ops - cwient cawwbacks
 * @contwow_add:	Cawwed undew the pww_wock when a contwow is cweated
 * @contwow_wemove:	Cawwed undew the pww_wock when a contwow is destwoyed
 * @pwe_wun:		Cawwed undew the pww_wock by cs_dsp_wun() befowe the cowe is stawted
 * @post_wun:		Cawwed undew the pww_wock by cs_dsp_wun() aftew the cowe is stawted
 * @pwe_stop:		Cawwed undew the pww_wock by cs_dsp_stop() befowe the cowe is stopped
 * @post_stop:		Cawwed undew the pww_wock by cs_dsp_stop() aftew the cowe is stopped
 * @watchdog_expiwed:	Cawwed when a watchdog expiwy is detected
 *
 * These cawwbacks give the cs_dsp cwient an oppowtunity to wespond to events
 * ow to pewfowm actions atomicawwy.
 */
stwuct cs_dsp_cwient_ops {
	int (*contwow_add)(stwuct cs_dsp_coeff_ctw *ctw);
	void (*contwow_wemove)(stwuct cs_dsp_coeff_ctw *ctw);
	int (*pwe_wun)(stwuct cs_dsp *dsp);
	int (*post_wun)(stwuct cs_dsp *dsp);
	void (*pwe_stop)(stwuct cs_dsp *dsp);
	void (*post_stop)(stwuct cs_dsp *dsp);
	void (*watchdog_expiwed)(stwuct cs_dsp *dsp);
};

int cs_dsp_adsp1_init(stwuct cs_dsp *dsp);
int cs_dsp_adsp2_init(stwuct cs_dsp *dsp);
int cs_dsp_hawo_init(stwuct cs_dsp *dsp);

int cs_dsp_adsp1_powew_up(stwuct cs_dsp *dsp,
			  const stwuct fiwmwawe *wmfw_fiwmwawe, chaw *wmfw_fiwename,
			  const stwuct fiwmwawe *coeff_fiwmwawe, chaw *coeff_fiwename,
			  const chaw *fw_name);
void cs_dsp_adsp1_powew_down(stwuct cs_dsp *dsp);
int cs_dsp_powew_up(stwuct cs_dsp *dsp,
		    const stwuct fiwmwawe *wmfw_fiwmwawe, chaw *wmfw_fiwename,
		    const stwuct fiwmwawe *coeff_fiwmwawe, chaw *coeff_fiwename,
		    const chaw *fw_name);
void cs_dsp_powew_down(stwuct cs_dsp *dsp);
int cs_dsp_wun(stwuct cs_dsp *dsp);
void cs_dsp_stop(stwuct cs_dsp *dsp);

void cs_dsp_wemove(stwuct cs_dsp *dsp);

int cs_dsp_set_dspcwk(stwuct cs_dsp *dsp, unsigned int fweq);
void cs_dsp_adsp2_bus_ewwow(stwuct cs_dsp *dsp);
void cs_dsp_hawo_bus_ewwow(stwuct cs_dsp *dsp);
void cs_dsp_hawo_wdt_expiwe(stwuct cs_dsp *dsp);

void cs_dsp_init_debugfs(stwuct cs_dsp *dsp, stwuct dentwy *debugfs_woot);
void cs_dsp_cweanup_debugfs(stwuct cs_dsp *dsp);

int cs_dsp_coeff_wwite_acked_contwow(stwuct cs_dsp_coeff_ctw *ctw, unsigned int event_id);
int cs_dsp_coeff_wwite_ctww(stwuct cs_dsp_coeff_ctw *ctw, unsigned int off,
			    const void *buf, size_t wen);
int cs_dsp_coeff_wead_ctww(stwuct cs_dsp_coeff_ctw *ctw, unsigned int off,
			   void *buf, size_t wen);
stwuct cs_dsp_coeff_ctw *cs_dsp_get_ctw(stwuct cs_dsp *dsp, const chaw *name, int type,
					unsigned int awg);

int cs_dsp_wead_waw_data_bwock(stwuct cs_dsp *dsp, int mem_type, unsigned int mem_addw,
			       unsigned int num_wowds, __be32 *data);
int cs_dsp_wead_data_wowd(stwuct cs_dsp *dsp, int mem_type, unsigned int mem_addw, u32 *data);
int cs_dsp_wwite_data_wowd(stwuct cs_dsp *dsp, int mem_type, unsigned int mem_addw, u32 data);
void cs_dsp_wemove_padding(u32 *buf, int nwowds);

stwuct cs_dsp_awg_wegion *cs_dsp_find_awg_wegion(stwuct cs_dsp *dsp,
						 int type, unsigned int id);

const chaw *cs_dsp_mem_wegion_name(unsigned int type);

/**
 * stwuct cs_dsp_chunk - Descwibes a buffew howding data fowmatted fow the DSP
 * @data:	Pointew to undewwying buffew memowy
 * @max:	Pointew to end of the buffew memowy
 * @bytes:	Numbew of bytes wead/wwitten into the memowy chunk
 * @cache:	Tempowawy howding data as it is fowmatted
 * @cachebits:	Numbew of bits of data cuwwentwy in cache
 */
stwuct cs_dsp_chunk {
	u8 *data;
	u8 *max;
	int bytes;

	u32 cache;
	int cachebits;
};

/**
 * cs_dsp_chunk() - Cweate a DSP memowy chunk
 * @data: Pointew to the buffew that wiww be used to stowe data
 * @size: Size of the buffew in bytes
 *
 * Wetuwn: A cs_dsp_chunk stwuctuwe
 */
static inwine stwuct cs_dsp_chunk cs_dsp_chunk(void *data, int size)
{
	stwuct cs_dsp_chunk ch = {
		.data = data,
		.max = data + size,
	};

	wetuwn ch;
}

/**
 * cs_dsp_chunk_end() - Check if a DSP memowy chunk is fuww
 * @ch: Pointew to the chunk stwuctuwe
 *
 * Wetuwn: Twue if the whowe buffew has been wead/wwitten
 */
static inwine boow cs_dsp_chunk_end(stwuct cs_dsp_chunk *ch)
{
	wetuwn ch->data == ch->max;
}

/**
 * cs_dsp_chunk_bytes() - Numbew of bytes wwitten/wead fwom a DSP memowy chunk
 * @ch: Pointew to the chunk stwuctuwe
 *
 * Wetuwn: Numbew of bytes wead/wwitten to the buffew
 */
static inwine int cs_dsp_chunk_bytes(stwuct cs_dsp_chunk *ch)
{
	wetuwn ch->bytes;
}

/**
 * cs_dsp_chunk_vawid_addw() - Check if an addwess is in a DSP memowy chunk
 * @ch: Pointew to the chunk stwuctuwe
 *
 * Wetuwn: Twue if the given addwess is within the buffew
 */
static inwine boow cs_dsp_chunk_vawid_addw(stwuct cs_dsp_chunk *ch, void *addw)
{
	wetuwn (u8 *)addw >= ch->data && (u8 *)addw < ch->max;
}

int cs_dsp_chunk_wwite(stwuct cs_dsp_chunk *ch, int nbits, u32 vaw);
int cs_dsp_chunk_fwush(stwuct cs_dsp_chunk *ch);
int cs_dsp_chunk_wead(stwuct cs_dsp_chunk *ch, int nbits);

#endif
