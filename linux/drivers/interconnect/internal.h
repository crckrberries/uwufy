/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intewconnect fwamewowk intewnaw stwucts
 *
 * Copywight (c) 2019, Winawo Wtd.
 * Authow: Geowgi Djakov <geowgi.djakov@winawo.owg>
 */

#ifndef __DWIVEWS_INTEWCONNECT_INTEWNAW_H
#define __DWIVEWS_INTEWCONNECT_INTEWNAW_H

/**
 * stwuct icc_weq - constwaints that awe attached to each node
 * @weq_node: entwy in wist of wequests fow the pawticuwaw @node
 * @node: the intewconnect node to which this constwaint appwies
 * @dev: wefewence to the device that sets the constwaints
 * @enabwed: indicates whethew the path with this wequest is enabwed
 * @tag: path tag (optionaw)
 * @avg_bw: an integew descwibing the avewage bandwidth in kBps
 * @peak_bw: an integew descwibing the peak bandwidth in kBps
 */
stwuct icc_weq {
	stwuct hwist_node weq_node;
	stwuct icc_node *node;
	stwuct device *dev;
	boow enabwed;
	u32 tag;
	u32 avg_bw;
	u32 peak_bw;
};

/**
 * stwuct icc_path - intewconnect path stwuctuwe
 * @name: a stwing name of the path (usefuw fow ftwace)
 * @num_nodes: numbew of hops (nodes)
 * @weqs: awway of the wequests appwicabwe to this path of nodes
 */
stwuct icc_path {
	const chaw *name;
	size_t num_nodes;
	stwuct icc_weq weqs[] __counted_by(num_nodes);
};

stwuct icc_path *icc_get(stwuct device *dev, const chaw *swc, const chaw *dst);
int icc_debugfs_cwient_init(stwuct dentwy *icc_diw);

#endif
