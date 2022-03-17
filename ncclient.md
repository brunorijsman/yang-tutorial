# Ncclient: an open source Python NETCONF client module

## Introduction

[Ncclient](https://github.com/ncclient/ncclient) (short for NETCONF client) is an open source
Python module that allows you to develop Python scripts that interact with a NETCONF server.

## Install ncclient

If you followed the 
[instructions for setting up the environment for this tutorial](tutorial-install.md)
then ncclient is already installed.

Or, use `pip` if you want to install ncclient separately:

<pre>
$ <b>pip install ncclient</b>
</pre>

## Start the clixon NETCONF server

The MG-Soft NETCONF browser is a NETCONF client, so we need a NETCONF server to be running.
In this chapter we will use clixon as the NETCONF server.
Refer to the [clixon chapter in this tutorial](clixon.md) for instructions on how install clixon,
how to build clixon, how the start the clixon backend daemon, and how to configure SSH to start
the clixon NETCONF server.

You can manually start an SSH session to the clixon NETCONF server to make sure it is running
properly:

<pre>
$ <b>ssh localhost -s netconf</b>
username@localhost's password: <b>******</b>
<hello xmlns="urn:ietf:params:xml:ns:netconf:base:1.0" message-id="42"><capabilities><capability>urn:ietf:params:netconf:base:1.1</capability><capability>urn:ietf:params:netconf:base:1.0</capability><capability>urn:ietf:params:netconf:capability:candidate:1.0</capability><capability>urn:ietf:params:netconf:capability:validate:1.1</capability><capability>urn:ietf:params:netconf:capability:startup:1.0</capability><capability>urn:ietf:params:netconf:capability:xpath:1.0</capability><capability>urn:ietf:params:netconf:capability:notification:1.0</capability></capabilities><session-id>4</session-id></hello>]]>]]>
</pre>

Type Control-D to exit the SSH session.

## Example Python scripts

This repository contains several example Python scripts that use the `ncclient` Python module.
In the remainder of this chapter we will walk you through those examples.

<pre>
$ <b>cd ~/yang-tutorial/ncclient</b>

$ <b>ls -1</b>
[TODO] output
</pre>

## Get the running configuration

