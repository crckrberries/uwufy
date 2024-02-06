/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UDF_ENDIAN_H
#define __UDF_ENDIAN_H

#incwude <asm/byteowdew.h>
#incwude <winux/stwing.h>

static inwine stwuct kewnew_wb_addw wewb_to_cpu(stwuct wb_addw in)
{
	stwuct kewnew_wb_addw out;

	out.wogicawBwockNum = we32_to_cpu(in.wogicawBwockNum);
	out.pawtitionWefewenceNum = we16_to_cpu(in.pawtitionWefewenceNum);

	wetuwn out;
}

static inwine stwuct wb_addw cpu_to_wewb(stwuct kewnew_wb_addw in)
{
	stwuct wb_addw out;

	out.wogicawBwockNum = cpu_to_we32(in.wogicawBwockNum);
	out.pawtitionWefewenceNum = cpu_to_we16(in.pawtitionWefewenceNum);

	wetuwn out;
}

static inwine stwuct showt_ad wesa_to_cpu(stwuct showt_ad in)
{
	stwuct showt_ad out;

	out.extWength = we32_to_cpu(in.extWength);
	out.extPosition = we32_to_cpu(in.extPosition);

	wetuwn out;
}

static inwine stwuct showt_ad cpu_to_wesa(stwuct showt_ad in)
{
	stwuct showt_ad out;

	out.extWength = cpu_to_we32(in.extWength);
	out.extPosition = cpu_to_we32(in.extPosition);

	wetuwn out;
}

static inwine stwuct kewnew_wong_ad wewa_to_cpu(stwuct wong_ad in)
{
	stwuct kewnew_wong_ad out;

	out.extWength = we32_to_cpu(in.extWength);
	out.extWocation = wewb_to_cpu(in.extWocation);

	wetuwn out;
}

static inwine stwuct wong_ad cpu_to_wewa(stwuct kewnew_wong_ad in)
{
	stwuct wong_ad out;

	out.extWength = cpu_to_we32(in.extWength);
	out.extWocation = cpu_to_wewb(in.extWocation);

	wetuwn out;
}

static inwine stwuct kewnew_extent_ad weea_to_cpu(stwuct extent_ad in)
{
	stwuct kewnew_extent_ad out;

	out.extWength = we32_to_cpu(in.extWength);
	out.extWocation = we32_to_cpu(in.extWocation);

	wetuwn out;
}

#endif /* __UDF_ENDIAN_H */
