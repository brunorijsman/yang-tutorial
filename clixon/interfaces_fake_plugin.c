/* TODO: Make sure that all of these header files are actually needed. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/time.h>

#include <cligen/cligen.h>
#include <clixon/clixon.h>
#include <clixon/clixon_backend.h>

#define LOG_TAG "!!!! interfaces_fake_plugin"

int interfaces_transaction_begin(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    return 0;
}

int interfaces_transaction_validate(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    return 0;
}

int interfaces_transaction_commit(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    return 0;
}

int interfaces_transaction_end(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    return 0;
}

clixon_plugin_api *clixon_plugin_init(clicon_handle h);

static clixon_plugin_api api = {
    "interfaces fake plugin",
    clixon_plugin_init,
    .ca_trans_begin = interfaces_transaction_begin,
    .ca_trans_validate = interfaces_transaction_validate,
    .ca_trans_commit = interfaces_transaction_commit,
    .ca_trans_end = interfaces_transaction_end
};

clixon_plugin_api *
clixon_plugin_init(clicon_handle h) {
    clicon_debug(1, LOG_TAG);
    return &api;
}