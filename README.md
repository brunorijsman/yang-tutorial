--== **A WORK IN PROGRESS** ==--

# A scenic tour through the YANG ecosystem

# Introduction

This is a hands-on tutorial for the YANG ecosystem.

YANG is a data modeling language that is used for managing devices.
It is quite popular for managing networking devices such as routers, switches, firewalls,
load balancers, etc.
But in principle, YANG could be used to manage any device such as
washing machines, satellites, robots, storage arrays, whatever.

A YANG data model describes what the configurable and operational attributes of the device are.
A configuration attribute is an attribute that can be set by the operator, such as the temperature
for a washing machine (hot, warm, cold).
An operational attribute is an attribute that can only be read by the operator, such as the
remaining time for the cycle of a washing machine.
The YANG data model can also describe actions (e.g. start a washing cycle) and notifications
(e.g. the washing cycle has been completed).

The YANG data model is used to generate a management interface for the device.
One example of such a management interface is the command line interface (CLI) which is a
an interface intended for humans to configure and monitor the device.
Other examples of management interfaces are NETCONF and RESTCONF. These are intended to be used
by network management systems (NMSs) or software defined networking (SDN) controllers to configure
and monitor the device.

In this tutorial we won't spend much time on the theory of what YANG, CLI, NETCONF, or RESTCONF
are.
Instead, we will take a very hands-on approach and dive right in. We will define a toy YANG
data model for a router; it models only the IPv4 addresses on a set of interfaces.

Then, we will "take a tour through the YANG ecosystem". We will explore various open source and
commercial tools that do something with our toy YANG data model. Some tools allow us to validate
the correctness of the YANG data model. Other tools allow us to generate the code that would run
on the managed network devices: the CLI/NETCONF/RESTCONF server code that actually reflects
changes in the configuration onto the actual hardware. And other tools yet again allow us to
generate the code that runs in the network management system, i.e. the NETCONF/RESTCONF client
code.

We take a very hands-on approach for each tool that we explore: we explain how to install the tool
and how to use it to do something practically useful.

For a list of links to standards and tutorials related to YANG, NETCONF, RESTCONF, etc. see the 
[references page](docs/references.md).

# Getting started

This tutorial is written in such a way that you can follow along and run each example yourself.
For instructions on how to go to install the necessary software see the 
[setting up the environment for this tutorial](docs/tutorial-install.md) page.

# A very simple example YANG data model: interfaces.yang

Throughout this tutorial we will be using a simple example YANG data model called
`interfaces.yang` which is described in detail in the
[example YANG data model](docs/example-yang-data-model.md) page.

# YANG data model visualization, validation and transformation tools

These tools validate YANG data models for correctness and transform YANG data models into other
formats such as a text summary, an HTML summary, a UML diagram, etc.

Open source:
* [Pyang](docs/pyang.md)
* [Yanglint](docs/yanglint.md)

Online:
* [YANG Validator](docs/yang-validator.md)

Commercial:
* [MG-SOFT YANG Explorer Professional Edition](docs/mg-soft-explorer.md)
* [YumaWorks YumaPro Client](docs/yuma-pro-client.md)

TODO: Move some of the graphical YANG model browsers from down below to here.

# NETCONF / RESTCONF servers

NETCONF / RESTCONF servers are intended to implement the on-device management plane for
hardware devices. They typically provide the following functionality:

* They provide a north-bound (server-side) NETCONF and RESTCONF interface for clients.

* They often also provide other north-bound (server-side) interface such as gNMI, SNMP, and/or
  a command-line interface (CLI).

* They provide a software development kit (SDK) that allows the developers of the software on the
  device to map abstract YANG operations to concrete operations on the device hardware.
  Typically, the developers implement callback functions that get called when a configuration
  attribute needs to be validated, when a configuration attribute is set to a different value, when
  an operational attribute value is retrieved, when a transaction is committed, when an action is
  executed, when a notification needs to be generated, etc. etc. Different implementations support
  different programming languages.

* They provide the backend implementation for the YANG data models that manage the NETCONF /
  RESTCONF server functionality itself, e.g. 
  [RFC8525: YANG library](https://datatracker.ietf.org/doc/rfc8525/).

Open source:
* [Clixon](docs/clixon.md) (IN PROGRESS)
* [Netopeer2](docs/netopeer2.md) (IN PROGRESS)
* [Sysrepo](https://github.com/sysrepo/sysrepo) (TODO)

Commercial:
* [Cisco Tail-f ConfD](docs/confd.md) (TODO)
* [MG-SOFT NETCONF Simulator](docs/mg-soft-simulator.md)
* [YumaWorks YumaPro SDK](docs/yuma-pro-sdk.md)

# NETCONF / RESTCONF clients

NETCONF / RESTCONF clients are executable tools that allow a client-side user to manage devices
that offer a server-side NETCONF / RESTCONF interface.
They typically provide the following functionality:

* They can dynamically discover which YANG modules the device supports and download the
  corresponding YANG data model from the device. (Or alternatively, you can manually load YANG
  data models into the client).

* They can create, edit, and delete configuration attributes.

* They can retrieve operational attributes.

* They can invoke actions.

* They can receive notifications.

* Some tools offer a terminal-based command-line interface.
  Other tools offer a graphical user interface (GUI).

Commercial:
* [MG-SOFT NetConf Browser Professional Edition](docs/mg-soft-browser.md) (IN PROGRESS)
* [YumaWorks YumaBench](docs/yumabench.md)

# NETCONF / RESTCONF client libraries

These tools are libraries or modules in a particular programming language (e.g. C, C++)
that provide NETCONF and/or RESTCONF client functionality to software developers:

Open source:
* [Libyang](https://netopeer.liberouter.org/doc/libyang/devel/html/) (C) (TODO)
* [Ncclient](docs/ncclient.md) (Python)
* [Yangson](https://yangson.labs.nic.cz/) (Python) (TODO)

Commercial:
* [MG-SOFT NETCONF/YANG Python Scripting System](https://www.mg-soft.si/mgNetConfScripting.html) (TODO)

# YANG authoring tools

YANG authoring tools provide an integrated development environment (IDE) that help you author and
manage YANG data models.

Commercial:
* [MG-SOFT Visual YANG Designer Professional Edition](docs/mg-soft-designer.md)

# Other

I still have to look at the following tools and classify them:

* [YANG Development Kit](https://ydkgen.readthedocs.io/en/latest/index.html) (TODO)
* [Cisco Tail-f YANG Suite](https://developer.cisco.com/yangsuite/)
* [JetConf](https://github.com/CZ-NIC/jetconf)
* https://github.com/choppsv1/netconf

