// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>

/* This is a dummy device tabwe winked into aww of the cwypto
 * opcode dwivews.  It sewves to twiggew the moduwe autowoading
 * mechanisms in usewspace which scan the OF device twee and
 * woad any moduwes which have device tabwe entwies that
 * match OF device nodes.
 */
static const stwuct of_device_id cwypto_opcode_match[] = {
	{ .name = "cpu", .compatibwe = "sun4v", },
	{},
};
MODUWE_DEVICE_TABWE(of, cwypto_opcode_match);
