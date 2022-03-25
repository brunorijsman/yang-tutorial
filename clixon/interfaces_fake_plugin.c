#include <assert.h>
#include <stdbool.h>

#include <cligen/cligen.h>
#include <clixon/clixon.h>
#include <clixon/clixon_backend.h>

#define LOG_TAG "interfaces_fake_plugin"
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
    show_indented_xml_node(node, 4);
}

void show_xml_node_vec(cxobj **node_vec, size_t len) {
    for (size_t i=0; i<len; i++) {
        show_indented_xml_node(node_vec[i], 4);
    }
}

void show_transaction(transaction_data td, bool show_data) {
    clicon_debug(1, "%s:   transaction ID = %lu", LOG_TAG, transaction_id(td));
    if (show_data) {
        clicon_debug(1, "%s:   transaction source:", LOG_TAG);
        show_xml_node(transaction_src(td));
        clicon_debug(1, "%s:   transaction target:", LOG_TAG);
        show_xml_node(transaction_target(td));
        clicon_debug(1, "%s:   transaction deleted:", LOG_TAG);
        show_xml_node_vec(transaction_dvec(td), transaction_dlen(td));
        clicon_debug(1, "%s:   transaction added:", LOG_TAG);
        show_xml_node_vec(transaction_avec(td), transaction_alen(td));
        clicon_debug(1, "%s:   transaction changed source:", LOG_TAG);
        show_xml_node_vec(transaction_scvec(td), transaction_clen(td));
        clicon_debug(1, "%s:   transaction changed target:", LOG_TAG);
        show_xml_node_vec(transaction_tcvec(td), transaction_clen(td));
    }
}

int interfaces_transaction_begin(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    show_transaction(td, false);
    return 0;
}

int validate_interfaces(transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    int retval = -1;

    cvec *ns_ctx = xml_nsctx_init(NULL, "http://remoteautonomy.com/yang-schemas/interfaces");
    if (ns_ctx == NULL) {
        clicon_err(OE_CFG, 0, "Could not create namespace context");
        goto done;
    }

    cxobj *target = transaction_target(td);
    cxobj **nodes_vec = NULL;
    size_t nodes_len = 0;
    if (xpath_vec(target, ns_ctx, "/interfaces/interface/name", &nodes_vec, &nodes_len) < 0) {
        clicon_err(OE_CFG, 0, "Could not retrieve interface names");
        goto done;
    }

    int starts_with_x_count = 0;
	for (int i=0; i<nodes_len; i++){
	    char *name = xml_body(nodes_vec[i]);
        if (name != NULL && name[0] == 'x') {
            starts_with_x_count++;
        }
	}

    if (starts_with_x_count < 2) {
        return 0;
    }
    clicon_err(OE_CFG, 0, "Two or more interface names start with the letter x");

done:
    return retval;
}

int interfaces_transaction_validate(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    show_transaction(td, true);
    return validate_interfaces(td);
}

int interfaces_transaction_commit(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    show_transaction(td, true);
    return 0;
}

int interfaces_transaction_end(clicon_handle h, transaction_data td) {
    clicon_debug(1, "%s: %s", LOG_TAG, __func__);
    show_transaction(td, false);
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