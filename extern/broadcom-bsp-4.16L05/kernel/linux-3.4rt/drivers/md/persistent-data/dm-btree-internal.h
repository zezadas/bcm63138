/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#ifndef DM_BTREE_INTERNAL_H
#define DM_BTREE_INTERNAL_H

#include "dm-btree.h"

/*----------------------------------------------------------------*/

/*
 * We'll need 2 accessor functions for n->csum and n->blocknr
 * to support dm-btree-spine.c in that case.
 */

enum node_flags {
	INTERNAL_NODE = 1,
	LEAF_NODE = 1 << 1
};

/*
 * Every btree node begins with this structure.  Make sure it's a multiple
 * of 8-bytes in size, otherwise the 64bit keys will be mis-aligned.
 */
struct node_header {
	__le32 csum;
	__le32 flags;
	__le64 blocknr; /* Block this node is supposed to live in. */

	__le32 nr_entries;
	__le32 max_entries;
	__le32 value_size;
	__le32 padding;
} __packed;

#if !defined(CONFIG_BCM_KF_ANDROID) || !defined(CONFIG_BCM_ANDROID)
struct node {
#else
struct btree_node {
#endif
	struct node_header header;
	__le64 keys[0];
} __packed;


#if !defined(CONFIG_BCM_KF_ANDROID) || !defined(CONFIG_BCM_ANDROID)
void inc_children(struct dm_transaction_manager *tm, struct node *n,
#else
void inc_children(struct dm_transaction_manager *tm, struct btree_node *n,
#endif
		  struct dm_btree_value_type *vt);

int new_block(struct dm_btree_info *info, struct dm_block **result);
int unlock_block(struct dm_btree_info *info, struct dm_block *b);

/*
 * Spines keep track of the rolling locks.  There are 2 variants, read-only
 * and one that uses shadowing.  These are separate structs to allow the
 * type checker to spot misuse, for example accidentally calling read_lock
 * on a shadow spine.
 */
struct ro_spine {
	struct dm_btree_info *info;

	int count;
	struct dm_block *nodes[2];
};

void init_ro_spine(struct ro_spine *s, struct dm_btree_info *info);
int exit_ro_spine(struct ro_spine *s);
int ro_step(struct ro_spine *s, dm_block_t new_child);
#if !defined(CONFIG_BCM_KF_ANDROID) || !defined(CONFIG_BCM_ANDROID)
struct node *ro_node(struct ro_spine *s);
#else
struct btree_node *ro_node(struct ro_spine *s);
#endif

struct shadow_spine {
	struct dm_btree_info *info;

	int count;
	struct dm_block *nodes[2];

	dm_block_t root;
};

void init_shadow_spine(struct shadow_spine *s, struct dm_btree_info *info);
int exit_shadow_spine(struct shadow_spine *s);

int shadow_step(struct shadow_spine *s, dm_block_t b,
		struct dm_btree_value_type *vt);

/*
 * The spine must have at least one entry before calling this.
 */
struct dm_block *shadow_current(struct shadow_spine *s);

/*
 * The spine must have at least two entries before calling this.
 */
struct dm_block *shadow_parent(struct shadow_spine *s);

int shadow_has_parent(struct shadow_spine *s);

int shadow_root(struct shadow_spine *s);

/*
 * Some inlines.
 */
#if !defined(CONFIG_BCM_KF_ANDROID) || !defined(CONFIG_BCM_ANDROID)
static inline __le64 *key_ptr(struct node *n, uint32_t index)
#else
static inline __le64 *key_ptr(struct btree_node *n, uint32_t index)
#endif
{
	return n->keys + index;
}

#if !defined(CONFIG_BCM_KF_ANDROID) || !defined(CONFIG_BCM_ANDROID)
static inline void *value_base(struct node *n)
#else
static inline void *value_base(struct btree_node *n)
#endif
{
	return &n->keys[le32_to_cpu(n->header.max_entries)];
}

#if !defined(CONFIG_BCM_KF_ANDROID) || !defined(CONFIG_BCM_ANDROID)
static inline void *value_ptr(struct node *n, uint32_t index)
#else
static inline void *value_ptr(struct btree_node *n, uint32_t index)
#endif
{
	uint32_t value_size = le32_to_cpu(n->header.value_size);
	return value_base(n) + (value_size * index);
}

/*
 * Assumes the values are suitably-aligned and converts to core format.
 */
#if !defined(CONFIG_BCM_KF_ANDROID) || !defined(CONFIG_BCM_ANDROID)
static inline uint64_t value64(struct node *n, uint32_t index)
#else
static inline uint64_t value64(struct btree_node *n, uint32_t index)
#endif
{
	__le64 *values_le = value_base(n);

	return le64_to_cpu(values_le[index]);
}

/*
 * Searching for a key within a single node.
 */
#if !defined(CONFIG_BCM_KF_ANDROID) || !defined(CONFIG_BCM_ANDROID)
int lower_bound(struct node *n, uint64_t key);
#else
int lower_bound(struct btree_node *n, uint64_t key);
#endif

extern struct dm_block_validator btree_node_validator;

#endif	/* DM_BTREE_INTERNAL_H */
