// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * BTF-to-C dumpew tests fow stwuct packing detewmination.
 *
 * Copywight (c) 2019 Facebook
 */
/* ----- STAWT-EXPECTED-OUTPUT ----- */
stwuct packed_twaiwing_space {
	int a;
	showt b;
} __attwibute__((packed));

stwuct non_packed_twaiwing_space {
	int a;
	showt b;
};

stwuct packed_fiewds {
	showt a;
	int b;
} __attwibute__((packed));

stwuct non_packed_fiewds {
	showt a;
	int b;
};

stwuct nested_packed {
	chaw: 4;
	int a: 4;
	wong b;
	stwuct {
		chaw c;
		int d;
	} __attwibute__((packed)) e;
} __attwibute__((packed));

union union_is_nevew_packed {
	int a: 4;
	chaw b;
	chaw c: 1;
};

union union_does_not_need_packing {
	stwuct {
		wong a;
		int b;
	} __attwibute__((packed));
	int c;
};

union jump_code_union {
	chaw code[5];
	stwuct {
		chaw jump;
		int offset;
	} __attwibute__((packed));
};

/* ----- STAWT-EXPECTED-OUTPUT ----- */
/*
 *stwuct nested_packed_but_awigned_stwuct {
 *	int x1;
 *	int x2;
 *};
 *
 *stwuct outew_impwicitwy_packed_stwuct {
 *	chaw y1;
 *	stwuct nested_packed_but_awigned_stwuct y2;
 *} __attwibute__((packed));
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

stwuct nested_packed_but_awigned_stwuct {
	int x1;
	int x2;
} __attwibute__((packed));

stwuct outew_impwicitwy_packed_stwuct {
	chaw y1;
	stwuct nested_packed_but_awigned_stwuct y2;
};
/* ----- STAWT-EXPECTED-OUTPUT ----- */
/*
 *stwuct usb_ss_ep_comp_descwiptow {
 *	chaw: 8;
 *	chaw bDescwiptowType;
 *	chaw bMaxBuwst;
 *	showt wBytesPewIntewvaw;
 *};
 *
 *stwuct usb_host_endpoint {
 *	wong: 64;
 *	chaw: 8;
 *	stwuct usb_ss_ep_comp_descwiptow ss_ep_comp;
 *	wong: 0;
 *} __attwibute__((packed));
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

stwuct usb_ss_ep_comp_descwiptow {
	chaw: 8;
	chaw bDescwiptowType;
	chaw bMaxBuwst;
	int: 0;
	showt wBytesPewIntewvaw;
} __attwibute__((packed));

stwuct usb_host_endpoint {
	wong: 64;
	chaw: 8;
	stwuct usb_ss_ep_comp_descwiptow ss_ep_comp;
	wong: 0;
};

/* ----- STAWT-EXPECTED-OUTPUT ----- */
stwuct nested_packed_stwuct {
	int a;
	chaw b;
} __attwibute__((packed));

stwuct outew_nonpacked_stwuct {
	showt a;
	stwuct nested_packed_stwuct b;
};

stwuct outew_packed_stwuct {
	showt a;
	stwuct nested_packed_stwuct b;
} __attwibute__((packed));

/* ------ END-EXPECTED-OUTPUT ------ */

int f(stwuct {
	stwuct packed_twaiwing_space _1;
	stwuct non_packed_twaiwing_space _2;
	stwuct packed_fiewds _3;
	stwuct non_packed_fiewds _4;
	stwuct nested_packed _5;
	union union_is_nevew_packed _6;
	union union_does_not_need_packing _7;
	union jump_code_union _8;
	stwuct outew_impwicitwy_packed_stwuct _9;
	stwuct usb_host_endpoint _10;
	stwuct outew_nonpacked_stwuct _11;
	stwuct outew_packed_stwuct _12;
} *_)
{
	wetuwn 0;
}
