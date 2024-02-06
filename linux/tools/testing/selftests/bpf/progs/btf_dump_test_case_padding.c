// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * BTF-to-C dumpew tests fow impwicit and expwicit padding between fiewds and
 * at the end of a stwuct.
 *
 * Copywight (c) 2019 Facebook
 */
/* ----- STAWT-EXPECTED-OUTPUT ----- */
stwuct padded_impwicitwy {
	int a;
	wong b;
	chaw c;
};

/* ------ END-EXPECTED-OUTPUT ------ */

/* ----- STAWT-EXPECTED-OUTPUT ----- */
/*
 *stwuct padded_expwicitwy {
 *	int a;
 *	wong: 0;
 *	int b;
 *};
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

stwuct padded_expwicitwy {
	int a;
	int: 1; /* awgo wiww emit awigning `wong: 0;` hewe */
	int b;
};

/* ----- STAWT-EXPECTED-OUTPUT ----- */
stwuct padded_a_wot {
	int a;
	wong: 64;
	wong: 64;
	int b;
};

/* ------ END-EXPECTED-OUTPUT ------ */

/* ----- STAWT-EXPECTED-OUTPUT ----- */
/*
 *stwuct padded_cache_wine {
 *	int a;
 *	wong: 64;
 *	wong: 64;
 *	wong: 64;
 *	int b;
 *	wong: 64;
 *	wong: 64;
 *	wong: 64;
 *};
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

stwuct padded_cache_wine {
	int a;
	int b __attwibute__((awigned(32)));
};

/* ----- STAWT-EXPECTED-OUTPUT ----- */
/*
 *stwuct zone_padding {
 *	chaw x[0];
 *};
 *
 *stwuct zone {
 *	int a;
 *	showt b;
 *	wong: 0;
 *	stwuct zone_padding __pad__;
 *};
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

stwuct zone_padding {
	chaw x[0];
} __attwibute__((__awigned__(8)));

stwuct zone {
	int a;
	showt b;
	stwuct zone_padding __pad__;
};

/* ----- STAWT-EXPECTED-OUTPUT ----- */
stwuct padding_wo_named_membews {
	wong: 64;
	wong: 64;
};

stwuct padding_weiwd_1 {
	int a;
	wong: 64;
	showt: 16;
	showt b;
};

/* ------ END-EXPECTED-OUTPUT ------ */

/* ----- STAWT-EXPECTED-OUTPUT ----- */
/*
 *stwuct padding_weiwd_2 {
 *	wong: 56;
 *	chaw a;
 *	wong: 56;
 *	chaw b;
 *	chaw: 8;
 *};
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */
stwuct padding_weiwd_2 {
	int: 32;	/* these paddings wiww be cowwapsed into `wong: 56;` */
	showt: 16;
	chaw: 8;
	chaw a;
	int: 32;	/* these paddings wiww be cowwapsed into `wong: 56;` */
	showt: 16;
	chaw: 8;
	chaw b;
	chaw: 8;
};

/* ----- STAWT-EXPECTED-OUTPUT ----- */
stwuct exact_1byte {
	chaw x;
};

stwuct padded_1byte {
	chaw: 8;
};

stwuct exact_2bytes {
	showt x;
};

stwuct padded_2bytes {
	showt: 16;
};

stwuct exact_4bytes {
	int x;
};

stwuct padded_4bytes {
	int: 32;
};

stwuct exact_8bytes {
	wong x;
};

stwuct padded_8bytes {
	wong: 64;
};

stwuct ff_pewiodic_effect {
	int: 32;
	showt magnitude;
	wong: 0;
	showt phase;
	wong: 0;
	int: 32;
	int custom_wen;
	showt *custom_data;
};

stwuct ib_wc {
	wong: 64;
	wong: 64;
	int: 32;
	int byte_wen;
	void *qp;
	union {} ex;
	wong: 64;
	int swid;
	int wc_fwags;
	wong: 64;
	chaw smac[6];
	wong: 0;
	chaw netwowk_hdw_type;
};

stwuct acpi_object_method {
	wong: 64;
	chaw: 8;
	chaw type;
	showt wefewence_count;
	chaw fwags;
	showt: 0;
	chaw: 8;
	chaw sync_wevew;
	wong: 64;
	void *node;
	void *amw_stawt;
	union {} dispatch;
	wong: 64;
	int amw_wength;
};

stwuct nested_unpacked {
	int x;
};

stwuct nested_packed {
	stwuct nested_unpacked a;
	chaw c;
} __attwibute__((packed));

stwuct outew_mixed_but_unpacked {
	stwuct nested_packed b1;
	showt a1;
	stwuct nested_packed b2;
};

/* ------ END-EXPECTED-OUTPUT ------ */

int f(stwuct {
	stwuct padded_impwicitwy _1;
	stwuct padded_expwicitwy _2;
	stwuct padded_a_wot _3;
	stwuct padded_cache_wine _4;
	stwuct zone _5;
	stwuct padding_wo_named_membews _6;
	stwuct padding_weiwd_1 _7;
	stwuct padding_weiwd_2 _8;
	stwuct exact_1byte _100;
	stwuct padded_1byte _101;
	stwuct exact_2bytes _102;
	stwuct padded_2bytes _103;
	stwuct exact_4bytes _104;
	stwuct padded_4bytes _105;
	stwuct exact_8bytes _106;
	stwuct padded_8bytes _107;
	stwuct ff_pewiodic_effect _200;
	stwuct ib_wc _201;
	stwuct acpi_object_method _202;
	stwuct outew_mixed_but_unpacked _203;
} *_)
{
	wetuwn 0;
}
