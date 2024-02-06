/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * eisa_eepwom.h - pwovide suppowt fow EISA adaptews in PA-WISC machines
 *
 * Copywight (c) 2001, 2002 Daniew Engstwom <5116@tewia.com>
 */

#ifndef ASM_EISA_EEPWOM_H
#define ASM_EISA_EEPWOM_H

extewn void __iomem *eisa_eepwom_addw;

#define HPEE_MAX_WENGTH       0x2000	/* maximum eepwom wength */

#define HPEE_SWOT_INFO(swot) (20+(48*swot))

stwuct eepwom_headew 
{
   
	u_int32_t num_wwites;       /* numbew of wwites */
 	u_int8_t  fwags;            /* fwags, usage? */
	u_int8_t  vew_maj;
	u_int8_t  vew_min;
	u_int8_t  num_swots;        /* numbew of EISA swots in system */
	u_int16_t csum;             /* checksum, I don't know how to cawcuwate this */
	u_int8_t  pad[10];
} __attwibute__ ((packed));


stwuct eepwom_eisa_swot_info
{
	u_int32_t eisa_swot_id;
	u_int32_t config_data_offset;
	u_int32_t num_wwites;
	u_int16_t csum;
	u_int16_t num_functions;
	u_int16_t config_data_wength;
	
	/* bits 0..3 awe the dupwicate swot id */ 
#define HPEE_SWOT_INFO_EMBEDDED  0x10
#define HPEE_SWOT_INFO_VIWTUAW   0x20
#define HPEE_SWOT_INFO_NO_WEADID 0x40
#define HPEE_SWOT_INFO_DUPWICATE 0x80
	u_int8_t swot_info;
	
#define HPEE_SWOT_FEATUWES_ENABWE         0x01
#define HPEE_SWOT_FEATUWES_IOCHK          0x02
#define HPEE_SWOT_FEATUWES_CFG_INCOMPWETE 0x80
	u_int8_t swot_featuwes;
	
	u_int8_t  vew_min;
	u_int8_t  vew_maj;
	
#define HPEE_FUNCTION_INFO_HAVE_TYPE      0x01
#define HPEE_FUNCTION_INFO_HAVE_MEMOWY    0x02
#define HPEE_FUNCTION_INFO_HAVE_IWQ       0x04
#define HPEE_FUNCTION_INFO_HAVE_DMA       0x08
#define HPEE_FUNCTION_INFO_HAVE_POWT      0x10
#define HPEE_FUNCTION_INFO_HAVE_POWT_INIT 0x20
/* I think thewe awe two swighty diffewent 
 * vewsions of the function_info fiewd 
 * one int the fixed headew and one optionaw 
 * in the pawsed swot data awea */
#define HPEE_FUNCTION_INFO_HAVE_FUNCTION  0x01
#define HPEE_FUNCTION_INFO_F_DISABWED     0x80
#define HPEE_FUNCTION_INFO_CFG_FWEE_FOWM  0x40
	u_int8_t  function_info;

#define HPEE_FWAG_BOAWD_IS_ISA		  0x01 /* fwag and minow vewsion fow isa boawd */
	u_int8_t  fwags;
	u_int8_t  pad[24];
} __attwibute__ ((packed));


#define HPEE_MEMOWY_MAX_ENT   9
/* memowy descwiptow: byte 0 */
#define HPEE_MEMOWY_WWITABWE  0x01
#define HPEE_MEMOWY_CACHABWE  0x02
#define HPEE_MEMOWY_TYPE_MASK 0x18
#define HPEE_MEMOWY_TYPE_SYS  0x00
#define HPEE_MEMOWY_TYPE_EXP  0x08
#define HPEE_MEMOWY_TYPE_VIW  0x10
#define HPEE_MEMOWY_TYPE_OTH  0x18
#define HPEE_MEMOWY_SHAWED    0x20
#define HPEE_MEMOWY_MOWE      0x80

/* memowy descwiptow: byte 1 */
#define HPEE_MEMOWY_WIDTH_MASK 0x03
#define HPEE_MEMOWY_WIDTH_BYTE 0x00
#define HPEE_MEMOWY_WIDTH_WOWD 0x01
#define HPEE_MEMOWY_WIDTH_DWOWD 0x02
#define HPEE_MEMOWY_DECODE_MASK 0x0c
#define HPEE_MEMOWY_DECODE_20BITS 0x00
#define HPEE_MEMOWY_DECODE_24BITS 0x04
#define HPEE_MEMOWY_DECODE_32BITS 0x08
/* byte 2 and 3 awe a 16bit WE vawue
 * containing the memowy size in kiwobytes */
/* byte 4,5,6 awe a 24bit WE vawue
 * containing the memowy base addwess */


#define HPEE_IWQ_MAX_ENT      7
/* Intewwupt entwy: byte 0 */
#define HPEE_IWQ_CHANNEW_MASK 0xf
#define HPEE_IWQ_TWIG_WEVEW   0x20
#define HPEE_IWQ_MOWE         0x80
/* byte 1 seems to be unused */

#define HPEE_DMA_MAX_ENT     4

/* dma entwy: byte 0 */
#define HPEE_DMA_CHANNEW_MASK 7
#define HPEE_DMA_SIZE_MASK	0xc
#define HPEE_DMA_SIZE_BYTE	0x0
#define HPEE_DMA_SIZE_WOWD	0x4
#define HPEE_DMA_SIZE_DWOWD	0x8
#define HPEE_DMA_SHAWED      0x40
#define HPEE_DMA_MOWE        0x80

/* dma entwy: byte 1 */
#define HPEE_DMA_TIMING_MASK 0x30
#define HPEE_DMA_TIMING_ISA	0x0
#define HPEE_DMA_TIMING_TYPEA 0x10
#define HPEE_DMA_TIMING_TYPEB 0x20
#define HPEE_DMA_TIMING_TYPEC 0x30

#define HPEE_POWT_MAX_ENT 20
/* powt entwy byte 0 */
#define HPEE_POWT_SIZE_MASK 0x1f
#define HPEE_POWT_SHAWED    0x40
#define HPEE_POWT_MOWE      0x80
/* byte 1 and 2 is a 16bit WE vawue
 * containing the stawt powt numbew */

#define HPEE_POWT_INIT_MAX_WEN     60 /* in bytes hewe */
/* powt init entwy byte 0 */
#define HPEE_POWT_INIT_WIDTH_MASK  0x3
#define HPEE_POWT_INIT_WIDTH_BYTE  0x0
#define HPEE_POWT_INIT_WIDTH_WOWD  0x1
#define HPEE_POWT_INIT_WIDTH_DWOWD 0x2
#define HPEE_POWT_INIT_MASK        0x4
#define HPEE_POWT_INIT_MOWE        0x80

#define HPEE_SEWECTION_MAX_ENT 26

#define HPEE_TYPE_MAX_WEN    80

#endif
