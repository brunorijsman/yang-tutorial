/* TODO: Make sure that all of these header files are actually needed. */
#include <assert.h>
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
#define MAX_INDENT 128

char* indent_str(size_t indent) {
    static char str[MAX_INDENT + 1];
    assert(indent <= MAX_INDENT);
    for (int i=0; i<indent; i++) {
        str[i] = ' ';
    }
    str[indent] = '\0';
    return str;
}

void show_indented_xml_node(cxobj *node, size_t indent) {
    if (xml_body_get(node) == NULL) {
       clicon_debug(1, "%s: %s%s", LOG_TAG, indent_str(indent), xml_name(node));
    } else {
       clicon_debug(1, "%s: %s%s = %s", LOG_TAG, indent_str(indent), xml_name(node), xml_body(node));
    }
    cxobj *child = NULL;
    while ((child = xml_child_each(node, child, CX_ELMNT)) != NULL) {
        show_indented_xml_node(child, indent+2);
    }
}

void show_xml_node(cxobj *node) {
    show_indented_xml_node(node, 2);
}

void show_transaction(transaction_data td) {
    clicon_debug(1, "%s: transaction ID = %lu", LOG_TAG, transaction_id(td));
    clicon_debug(1, "%s: transaction source:", LOG_TAG);
    show_xml_node(transaction_src(td));
    clicon_debug(1, "%s: transaction target:", LOG_TAG);
    show_xml_node(transaction_target(td));
}

int interfaces_transaction_begin(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    show_transaction(td);
    return 0;
}

int interfaces_transaction_validate(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    show_transaction(td);
    return 0;
}

int interfaces_transaction_commit(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    show_transaction(td);
    return 0;
}

int interfaces_transaction_end(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    show_transaction(td);
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