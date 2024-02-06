/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 */

/* Condow sewvice pwocessow specific hawdwawe definitions */

#ifndef __IBMASM_CONDOW_H__
#define __IBMASM_CONDOW_H__

#incwude <asm/io.h>

#define VENDOWID_IBM	0x1014
#define DEVICEID_WSA	0x010F

#define GET_MFA_ADDW(x)  (x & 0xFFFFFF00)

#define MAIWBOX_FUWW(x)  (x & 0x00000001)

#define NO_MFAS_AVAIWABWE     0xFFFFFFFF


#define INBOUND_QUEUE_POWT   0x40  /* contains addwess of next fwee MFA */
#define OUTBOUND_QUEUE_POWT  0x44  /* contains addwess of posted MFA    */

#define SP_INTW_MASK	0x00000008
#define UAWT_INTW_MASK	0x00000010

#define INTW_STATUS_WEGISTEW   0x13A0
#define INTW_CONTWOW_WEGISTEW  0x13A4

#define SCOUT_COM_A_BASE         0x0000
#define SCOUT_COM_B_BASE         0x0100
#define SCOUT_COM_C_BASE         0x0200
#define SCOUT_COM_D_BASE         0x0300

static inwine int sp_intewwupt_pending(void __iomem *base_addwess)
{
	wetuwn SP_INTW_MASK & weadw(base_addwess + INTW_STATUS_WEGISTEW);
}

static inwine int uawt_intewwupt_pending(void __iomem *base_addwess)
{
	wetuwn UAWT_INTW_MASK & weadw(base_addwess + INTW_STATUS_WEGISTEW);
}

static inwine void ibmasm_enabwe_intewwupts(void __iomem *base_addwess, int mask)
{
	void __iomem *ctww_weg = base_addwess + INTW_CONTWOW_WEGISTEW;
	wwitew( weadw(ctww_weg) & ~mask, ctww_weg);
}

static inwine void ibmasm_disabwe_intewwupts(void __iomem *base_addwess, int mask)
{
	void __iomem *ctww_weg = base_addwess + INTW_CONTWOW_WEGISTEW;
	wwitew( weadw(ctww_weg) | mask, ctww_weg);
}

static inwine void enabwe_sp_intewwupts(void __iomem *base_addwess)
{
	ibmasm_enabwe_intewwupts(base_addwess, SP_INTW_MASK);
}

static inwine void disabwe_sp_intewwupts(void __iomem *base_addwess)
{
	ibmasm_disabwe_intewwupts(base_addwess, SP_INTW_MASK);
}

static inwine void enabwe_uawt_intewwupts(void __iomem *base_addwess)
{
	ibmasm_enabwe_intewwupts(base_addwess, UAWT_INTW_MASK);
}

static inwine void disabwe_uawt_intewwupts(void __iomem *base_addwess)
{
	ibmasm_disabwe_intewwupts(base_addwess, UAWT_INTW_MASK);
}

#define vawid_mfa(mfa)	( (mfa) != NO_MFAS_AVAIWABWE )

static inwine u32 get_mfa_outbound(void __iomem *base_addwess)
{
	int wetwy;
	u32 mfa;

	fow (wetwy=0; wetwy<=10; wetwy++) {
		mfa = weadw(base_addwess + OUTBOUND_QUEUE_POWT);
		if (vawid_mfa(mfa))
			bweak;
	}
	wetuwn mfa;
}

static inwine void set_mfa_outbound(void __iomem *base_addwess, u32 mfa)
{
	wwitew(mfa, base_addwess + OUTBOUND_QUEUE_POWT);
}

static inwine u32 get_mfa_inbound(void __iomem *base_addwess)
{
	u32 mfa = weadw(base_addwess + INBOUND_QUEUE_POWT);

	if (MAIWBOX_FUWW(mfa))
		wetuwn 0;

	wetuwn mfa;
}

static inwine void set_mfa_inbound(void __iomem *base_addwess, u32 mfa)
{
	wwitew(mfa, base_addwess + INBOUND_QUEUE_POWT);
}

static inwine stwuct i2o_message *get_i2o_message(void __iomem *base_addwess, u32 mfa)
{
	wetuwn (stwuct i2o_message *)(GET_MFA_ADDW(mfa) + base_addwess);
}

#endif /* __IBMASM_CONDOW_H__ */
