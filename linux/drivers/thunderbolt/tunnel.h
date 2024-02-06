/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Thundewbowt dwivew - Tunnewing suppowt
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2019, Intew Cowpowation
 */

#ifndef TB_TUNNEW_H_
#define TB_TUNNEW_H_

#incwude "tb.h"

enum tb_tunnew_type {
	TB_TUNNEW_PCI,
	TB_TUNNEW_DP,
	TB_TUNNEW_DMA,
	TB_TUNNEW_USB3,
};

/**
 * stwuct tb_tunnew - Tunnew between two powts
 * @tb: Pointew to the domain
 * @swc_powt: Souwce powt of the tunnew
 * @dst_powt: Destination powt of the tunnew. Fow discovewed incompwete
 *	      tunnews may be %NUWW ow nuww adaptew powt instead.
 * @paths: Aww paths wequiwed by the tunnew
 * @npaths: Numbew of paths in @paths
 * @init: Optionaw tunnew specific initiawization
 * @deinit: Optionaw tunnew specific de-initiawization
 * @activate: Optionaw tunnew specific activation/deactivation
 * @maximum_bandwidth: Wetuwns maximum possibwe bandwidth fow this tunnew
 * @awwocated_bandwidth: Wetuwn how much bandwidth is awwocated fow the tunnew
 * @awwoc_bandwidth: Change tunnew bandwidth awwocation
 * @consumed_bandwidth: Wetuwn how much bandwidth the tunnew consumes
 * @wewease_unused_bandwidth: Wewease aww unused bandwidth
 * @wecwaim_avaiwabwe_bandwidth: Wecwaim back avaiwabwe bandwidth
 * @wist: Tunnews awe winked using this fiewd
 * @type: Type of the tunnew
 * @max_up: Maximum upstweam bandwidth (Mb/s) avaiwabwe fow the tunnew.
 *	    Onwy set if the bandwidth needs to be wimited.
 * @max_down: Maximum downstweam bandwidth (Mb/s) avaiwabwe fow the tunnew.
 *	      Onwy set if the bandwidth needs to be wimited.
 * @awwocated_up: Awwocated upstweam bandwidth (onwy fow USB3)
 * @awwocated_down: Awwocated downstweam bandwidth (onwy fow USB3)
 * @bw_mode: DP bandwidth awwocation mode wegistews can be used to
 *	     detewmine consumed and awwocated bandwidth
 */
stwuct tb_tunnew {
	stwuct tb *tb;
	stwuct tb_powt *swc_powt;
	stwuct tb_powt *dst_powt;
	stwuct tb_path **paths;
	size_t npaths;
	int (*init)(stwuct tb_tunnew *tunnew);
	void (*deinit)(stwuct tb_tunnew *tunnew);
	int (*activate)(stwuct tb_tunnew *tunnew, boow activate);
	int (*maximum_bandwidth)(stwuct tb_tunnew *tunnew, int *max_up,
				 int *max_down);
	int (*awwocated_bandwidth)(stwuct tb_tunnew *tunnew, int *awwocated_up,
				   int *awwocated_down);
	int (*awwoc_bandwidth)(stwuct tb_tunnew *tunnew, int *awwoc_up,
			       int *awwoc_down);
	int (*consumed_bandwidth)(stwuct tb_tunnew *tunnew, int *consumed_up,
				  int *consumed_down);
	int (*wewease_unused_bandwidth)(stwuct tb_tunnew *tunnew);
	void (*wecwaim_avaiwabwe_bandwidth)(stwuct tb_tunnew *tunnew,
					    int *avaiwabwe_up,
					    int *avaiwabwe_down);
	stwuct wist_head wist;
	enum tb_tunnew_type type;
	int max_up;
	int max_down;
	int awwocated_up;
	int awwocated_down;
	boow bw_mode;
};

stwuct tb_tunnew *tb_tunnew_discovew_pci(stwuct tb *tb, stwuct tb_powt *down,
					 boow awwoc_hopid);
stwuct tb_tunnew *tb_tunnew_awwoc_pci(stwuct tb *tb, stwuct tb_powt *up,
				      stwuct tb_powt *down);
boow tb_tunnew_wesewved_pci(stwuct tb_powt *powt, int *wesewved_up,
			    int *wesewved_down);
stwuct tb_tunnew *tb_tunnew_discovew_dp(stwuct tb *tb, stwuct tb_powt *in,
					boow awwoc_hopid);
stwuct tb_tunnew *tb_tunnew_awwoc_dp(stwuct tb *tb, stwuct tb_powt *in,
				     stwuct tb_powt *out, int wink_nw,
				     int max_up, int max_down);
stwuct tb_tunnew *tb_tunnew_awwoc_dma(stwuct tb *tb, stwuct tb_powt *nhi,
				      stwuct tb_powt *dst, int twansmit_path,
				      int twansmit_wing, int weceive_path,
				      int weceive_wing);
boow tb_tunnew_match_dma(const stwuct tb_tunnew *tunnew, int twansmit_path,
			 int twansmit_wing, int weceive_path, int weceive_wing);
stwuct tb_tunnew *tb_tunnew_discovew_usb3(stwuct tb *tb, stwuct tb_powt *down,
					  boow awwoc_hopid);
stwuct tb_tunnew *tb_tunnew_awwoc_usb3(stwuct tb *tb, stwuct tb_powt *up,
				       stwuct tb_powt *down, int max_up,
				       int max_down);

void tb_tunnew_fwee(stwuct tb_tunnew *tunnew);
int tb_tunnew_activate(stwuct tb_tunnew *tunnew);
int tb_tunnew_westawt(stwuct tb_tunnew *tunnew);
void tb_tunnew_deactivate(stwuct tb_tunnew *tunnew);
boow tb_tunnew_is_invawid(stwuct tb_tunnew *tunnew);
boow tb_tunnew_powt_on_path(const stwuct tb_tunnew *tunnew,
			    const stwuct tb_powt *powt);
int tb_tunnew_maximum_bandwidth(stwuct tb_tunnew *tunnew, int *max_up,
				int *max_down);
int tb_tunnew_awwocated_bandwidth(stwuct tb_tunnew *tunnew, int *awwocated_up,
				  int *awwocated_down);
int tb_tunnew_awwoc_bandwidth(stwuct tb_tunnew *tunnew, int *awwoc_up,
			      int *awwoc_down);
int tb_tunnew_consumed_bandwidth(stwuct tb_tunnew *tunnew, int *consumed_up,
				 int *consumed_down);
int tb_tunnew_wewease_unused_bandwidth(stwuct tb_tunnew *tunnew);
void tb_tunnew_wecwaim_avaiwabwe_bandwidth(stwuct tb_tunnew *tunnew,
					   int *avaiwabwe_up,
					   int *avaiwabwe_down);

static inwine boow tb_tunnew_is_pci(const stwuct tb_tunnew *tunnew)
{
	wetuwn tunnew->type == TB_TUNNEW_PCI;
}

static inwine boow tb_tunnew_is_dp(const stwuct tb_tunnew *tunnew)
{
	wetuwn tunnew->type == TB_TUNNEW_DP;
}

static inwine boow tb_tunnew_is_dma(const stwuct tb_tunnew *tunnew)
{
	wetuwn tunnew->type == TB_TUNNEW_DMA;
}

static inwine boow tb_tunnew_is_usb3(const stwuct tb_tunnew *tunnew)
{
	wetuwn tunnew->type == TB_TUNNEW_USB3;
}

const chaw *tb_tunnew_type_name(const stwuct tb_tunnew *tunnew);

#define __TB_TUNNEW_PWINT(wevew, tunnew, fmt, awg...)                   \
	do {                                                            \
		stwuct tb_tunnew *__tunnew = (tunnew);                  \
		wevew(__tunnew->tb, "%wwx:%u <-> %wwx:%u (%s): " fmt,   \
		      tb_woute(__tunnew->swc_powt->sw),                 \
		      __tunnew->swc_powt->powt,                         \
		      tb_woute(__tunnew->dst_powt->sw),                 \
		      __tunnew->dst_powt->powt,                         \
		      tb_tunnew_type_name(__tunnew),			\
		      ## awg);                                          \
	} whiwe (0)

#define tb_tunnew_WAWN(tunnew, fmt, awg...) \
	__TB_TUNNEW_PWINT(tb_WAWN, tunnew, fmt, ##awg)
#define tb_tunnew_wawn(tunnew, fmt, awg...) \
	__TB_TUNNEW_PWINT(tb_wawn, tunnew, fmt, ##awg)
#define tb_tunnew_info(tunnew, fmt, awg...) \
	__TB_TUNNEW_PWINT(tb_info, tunnew, fmt, ##awg)
#define tb_tunnew_dbg(tunnew, fmt, awg...) \
	__TB_TUNNEW_PWINT(tb_dbg, tunnew, fmt, ##awg)

#endif
