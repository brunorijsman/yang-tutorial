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

int interfaces_commit(clicon_handle h, transaction_data td) {
    clicon_debug(1, "interfaces commit");
    return 0;
}

clixon_plugin_api *clixon_plugin_init(clicon_handle h);

static clixon_plugin_api api = {
    "interfaces backend",
    clixon_plugin_init,
    .ca_trans_commit = interfaces_commit,
};

clixon_plugin_api *
clixon_plugin_init(clicon_handle h) {
    return &api;
}