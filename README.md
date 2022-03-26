--== **A WORK IN PROGRESS** ==--

# A scenic tour through the YANG ecosystem

# Introduction

In this tutorial we will take a hands-on scenic tour through the YANG related ecosystem:

 * Write a simple YANG data model to manage a set of interfaces.

 * Use [pyang](https://github.com/mbj4668/pyang) to validate the YANG data model and to convert it
   to various other formats.

 * Use [clixon](https://clixon-docs.readthedocs.io/en/latest/) to implement a server that:
   - Implements the YANG data model.
   - Provides a command line interface (CLI).
   - Provides a NETCONF interface.
   - Provides a RESTCONF interface.
   - Initially provides a mocked backend for fake interfaces.
   - Later on provides a real backend for real interfaces on a Linux host.

* Use the clixon CLI client to access the command line interface provided by the clixon server.

* Use the [MGSoft](https://www.mg-soft.si/) [NETCONF browser](https://www.mg-soft.si/) to access
  the NETCONF interface provided by the clixon server.

* Use [ncclient](https://github.com/ncclient/ncclient) as a NETCONF client of the NETCONF
  interface provided by the clixon server.

* Use the basic version of [Tail-f](https://www.tail-f.com/)
   [CONFD](https://www.tail-f.com/confd-basic/) to implement a server that:
   - Implements the YANG data model.
   - Provides a command line interface (CLI).
   - Provides a NETCONF interface.
   - Initially provides a mocked backend for fake interfaces.
   - Later on provides a real backend for real interfaces on a Linux host.

* TODO: Add a YumaPro basic example.

* TODO: Add a Sysrepo example.


# Getting ready

[Setting up the environment for this tutorial](docs/tutorial-install.md)

[An example YANG data model](docs/example-yang-data-model.md)

# YANG data model validation and transformation tools:

These tools validate YANG data models for correctness and transform YANG data models into other
formats such as a text summary, an HTML summary, a UML diagram, etc.

Open source:

* [Pyang](docs/pyang.md)

* [Yanglint](https://www.mankier.com/1/yanglint) (TODO)

# Graphical YANG browsers

These tools provide a graphical user interface that allow you to:

1. Load a YANG data model and browse through the structure of that data model.

2. Connect to a YANG server using NETCONF or RESTCONF, browse through the contents of the data
   store, edit the contents of the data store, and invoke YANG actions.

Commercial:

* [NETCONF browser from MG-Soft](mg-soft-browser.md)

* YumaBench from YumaWorks

Open source / commercial:

[YANG Suite from Cisco](docs/yang-suite.md)

# YANG servers

A YANG server (also known as a YANG backend server):

* Implements the data store that stores data according to the data model described by YANG
  data models.

* Provides one or more of the following north-bound interfaces to access the data store:
  * NETCONF
  * RESTCONF
  * Command line interface (CLI)
  * SNMP

Open source:

* [Clixon](docs/clixon.md)

* [Netopeer2](https://github.com/CESNET/netopeer2) (TODO)

* [Sysrepo](https://github.com/sysrepo/sysrepo) (TODO)

Commercial:

* [CONFD from Tail-F (a Cisco company)](docs/confd.md)

* [YumaPro from YumaWorks](docs/yumapro.md)

# YANG client libraries

These tools are libraries or modules in a particular programming language (e.g. C, C++)
that provide NETCONF and/or RESTCONF client functionality to software developers:

Open source:

* [Libyang](https://netopeer.liberouter.org/doc/libyang/devel/html/) (C) (TODO)

* [Ncclient](docs/ncclient.md) (Python)

* [Yangson](https://yangson.labs.nic.cz/) (Python)

# References

## YANG

## NETMOD

* [The IETF NETMOD working group](https://datatracker.ietf.org/wg/netmod/about/)
* [The IETF NETMOD standards](https://datatracker.ietf.org/wg/netmod/documents/)

## NETCONF

* [The IETF NETCONF working group](https://datatracker.ietf.org/wg/netconf/about/)
* [The IETF NETCONF standards](https://datatracker.ietf.org/wg/netconf/documents/)

## RESTCONF
