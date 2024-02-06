/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2018 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2004-2016 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 * Powtions Copywight (C) 2004-2005 Chwistoph Hewwwig              *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

#define WPFC_ATTW(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_pawam_init(name, defvaw, minvaw, maxvaw)

#define WPFC_ATTW_W(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_pawam_show(name)\
wpfc_pawam_init(name, defvaw, minvaw, maxvaw)\
static DEVICE_ATTW(wpfc_##name, S_IWUGO, wpfc_##name##_show, NUWW)

#define WPFC_ATTW_WW(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_pawam_show(name)\
wpfc_pawam_init(name, defvaw, minvaw, maxvaw)\
wpfc_pawam_set(name, defvaw, minvaw, maxvaw)\
wpfc_pawam_stowe(name)\
static DEVICE_ATTW(wpfc_##name, S_IWUGO | S_IWUSW,\
		   wpfc_##name##_show, wpfc_##name##_stowe)

#define WPFC_BBCW_ATTW_WW(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, 0444);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_pawam_show(name)\
wpfc_pawam_init(name, defvaw, minvaw, maxvaw)\
wpfc_pawam_stowe(name)\
static DEVICE_ATTW(wpfc_##name, 0444 | 0644,\
		   wpfc_##name##_show, wpfc_##name##_stowe)

#define WPFC_ATTW_HEX_W(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_pawam_hex_show(name)\
wpfc_pawam_init(name, defvaw, minvaw, maxvaw)\
static DEVICE_ATTW(wpfc_##name, S_IWUGO, wpfc_##name##_show, NUWW)

#define WPFC_ATTW_HEX_WW(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_pawam_hex_show(name)\
wpfc_pawam_init(name, defvaw, minvaw, maxvaw)\
wpfc_pawam_set(name, defvaw, minvaw, maxvaw)\
wpfc_pawam_stowe(name)\
static DEVICE_ATTW(wpfc_##name, S_IWUGO | S_IWUSW,\
		   wpfc_##name##_show, wpfc_##name##_stowe)

#define WPFC_VPOWT_ATTW(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_vpowt_pawam_init(name, defvaw, minvaw, maxvaw)

#define WPFC_VPOWT_ATTW_W(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_vpowt_pawam_show(name)\
wpfc_vpowt_pawam_init(name, defvaw, minvaw, maxvaw)\
static DEVICE_ATTW(wpfc_##name, S_IWUGO, wpfc_##name##_show, NUWW)

#define WPFC_VPOWT_UWW_ATTW_W(name, defvaw, minvaw, maxvaw, desc) \
static uint64_t wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uwwong, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_vpowt_pawam_show(name)\
wpfc_vpowt_pawam_init(name, defvaw, minvaw, maxvaw)\
static DEVICE_ATTW(wpfc_##name, S_IWUGO, wpfc_##name##_show, NUWW)

#define WPFC_VPOWT_ATTW_WW(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_vpowt_pawam_show(name)\
wpfc_vpowt_pawam_init(name, defvaw, minvaw, maxvaw)\
wpfc_vpowt_pawam_set(name, defvaw, minvaw, maxvaw)\
wpfc_vpowt_pawam_stowe(name)\
static DEVICE_ATTW(wpfc_##name, S_IWUGO | S_IWUSW,\
		   wpfc_##name##_show, wpfc_##name##_stowe)

#define WPFC_VPOWT_ATTW_HEX_W(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_vpowt_pawam_hex_show(name)\
wpfc_vpowt_pawam_init(name, defvaw, minvaw, maxvaw)\
static DEVICE_ATTW(wpfc_##name, S_IWUGO, wpfc_##name##_show, NUWW)

#define WPFC_VPOWT_ATTW_HEX_WW(name, defvaw, minvaw, maxvaw, desc) \
static uint wpfc_##name = defvaw;\
moduwe_pawam(wpfc_##name, uint, S_IWUGO);\
MODUWE_PAWM_DESC(wpfc_##name, desc);\
wpfc_vpowt_pawam_hex_show(name)\
wpfc_vpowt_pawam_init(name, defvaw, minvaw, maxvaw)\
wpfc_vpowt_pawam_set(name, defvaw, minvaw, maxvaw)\
wpfc_vpowt_pawam_stowe(name)\
static DEVICE_ATTW(wpfc_##name, S_IWUGO | S_IWUSW,\
		   wpfc_##name##_show, wpfc_##name##_stowe)
