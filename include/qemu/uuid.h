/*
 *  QEMU UUID functions
 *
 *  Copyright 2016 Red Hat, Inc.
 *
 *  Authors:
 *   Fam Zheng <famz@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 */

#ifndef QEMU_UUID_H
#define QEMU_UUID_H


/* Version 4 UUID (pseudo random numbers), RFC4122 4.4. */

typedef struct {
    union {
        unsigned char data[16];
        struct {
            /* Generated in BE endian, can be swapped with qemu_uuid_bswap. */
            uint32_t time_low;
            uint16_t time_mid;
            uint16_t time_high_and_version;
            uint8_t  clock_seq_and_reserved;
            uint8_t  clock_seq_low;
            uint8_t  node[6];
        } fields;
    };
} QemuUUID;

#define UUID_FMT "%02hhx%02hhx%02hhx%02hhx-" \
                 "%02hhx%02hhx-%02hhx%02hhx-" \
                 "%02hhx%02hhx-" \
                 "%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx"

#define UUID_ARG(uuid) \
    (uuid)->data[0], (uuid)->data[1], (uuid)->data[2], (uuid)->data[3], \
    (uuid)->data[4], (uuid)->data[5], (uuid)->data[6], (uuid)->data[7], \
    (uuid)->data[8], (uuid)->data[9], (uuid)->data[10], (uuid)->data[11], \
    (uuid)->data[12], (uuid)->data[13], (uuid)->data[14], (uuid)->data[15]

#define UUID_FMT_LEN 36

#define UUID_NONE "00000000-0000-0000-0000-000000000000"

void qemu_uuid_generate(QemuUUID *out);

int qemu_uuid_is_null(const QemuUUID *uu);

int qemu_uuid_is_equal(const QemuUUID *lhv, const QemuUUID *rhv);

void qemu_uuid_unparse(const QemuUUID *uuid, char *out);

char *qemu_uuid_unparse_strdup(const QemuUUID *uuid);

int qemu_uuid_parse(const char *str, QemuUUID *uuid);

QemuUUID qemu_uuid_bswap(QemuUUID uuid);

QemuUUID *qemu_uuid_dup(const QemuUUID *uuid);

#endif
