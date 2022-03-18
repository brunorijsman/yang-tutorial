# Ncclient: an open source Python NETCONF client module

## Introduction

[Ncclient](https://github.com/ncclient/ncclient) (short for NETCONF client) is an open source
Python module that allows you to develop Python scripts that interact with a NETCONF server.

One issue with this project is that the
[documentation page](https://ncclient.readthedocs.io/en/latest/)
appears to be broken for some time now (many pages contain lists of empty placeholders).
So, you will have to be comfortable reading 
[the source code of `ncclient` on GitHub](https://github.com/ncclient/ncclient/tree/master/ncclient)
as documentation of its API.

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
We will use clixon as the NETCONF server.
Refer to the [clixon chapter in this tutorial](clixon.md) for instructions on how install clixon,
how to build clixon, how the start the clixon backend daemon, and how to configure SSH to start
the clixon NETCONF server.

As a quick sanity check to make sure the NETCONF server is running properly,
manually start an SSH session. You should see a NETCONF `hello` message from the server:

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

You may optionally set the following environment variables to configure the address, username,
and password of the NETCONF server:

<pre>
$ <b>export NETCONF_SERVER_ADDRESS="10.0.0.99"</b>       # Default: loopback address 127.0.0.1
$ <b>export NETCONF_SERVER_USERNAME="jamesbond"</b>      # Default: your current username
$ <b>export NETCONF_SERVER_PASSWORD="topsecret"</b>      # Default: none (certificate based authentication)
</pre>


TODO: Test certificate-based SSH authentication

## Show the running configuration

TODO: Remove `device_params={'name': 'alu'}` from all examples; it should not be needed anymore
now that the patch has been submitted to clixon.

The first example script `show_config.py` shows the running configuration in prettified XML
format:

```python
from ncclient import manager
from bs4 import BeautifulSoup
import netconf_server_info

with manager.connect(host=netconf_server_info.address(),
                     port=830,
                     username=netconf_server_info.username(),
                     password=netconf_server_info.password(),
                     hostkey_verify=False,
                     device_params={'name': 'alu'}) as mgr:
    config_xml = mgr.get_config(source='running').data_xml
    print(BeautifulSoup(config_xml, 'xml').prettify())
```

Module `netconf_server_info` is used to read the environment variables that contain the NETCONF
server information:

```python
import psutil
import os

def address():
    address = os.getenv('NETCONF_SERVER_ADDRESS')
    if address is None:
        return '127.0.0.1'
    return address

def username():
    username = os.getenv('NETCONF_SERVER_USERNAME')
    if username is None:
        return psutil.Process().username()
    return username

def password():
    return os.getenv('NETCONF_SERVER_PASSWORD')
```

Running the `show_config.py` script produces the following out (this assumes we configured 
interface `eth0` using the clixon CLI):

```xml
<?xml version="1.0" encoding="utf-8"?>
<rpc-reply message-id="urn:uuid:65f61253-834d-4fca-963f-ad7ed528b790">
 <data>
  <interfaces>
   <interface>
    <name>
     eth0
    </name>
    <ipv4-address>
     1.1.1.1
    </ipv4-address>
   </interface>
  </interfaces>
 </data>
</rpc-reply>
```

# Show the client and server capabilties

The example script `show_capabilities.py` shows the NETCONF client (ncclient) and
server (clixon) capabilities.

```python
from ncclient import manager
from bs4 import BeautifulSoup
import netconf_server_info

with manager.connect(host=netconf_server_info.address(),
                     port=830,
                     username=netconf_server_info.username(),
                     password=netconf_server_info.password(),
                     hostkey_verify=False,
                     device_params={'name': 'alu'}) as mgr:
    print("Client capabilities:")
    for capability in mgr.client_capabilities:
        print(f"  {capability}")
    print("Server capabilities:")
    for capability in mgr.server_capabilities:
        print(f"  {capability}")
```

The output of this script is:

```
Client capabilities:
  urn:ietf:params:netconf:base:1.0
Server capabilities:
  urn:ietf:params:netconf:base:1.1
  urn:ietf:params:netconf:base:1.0
  urn:ietf:params:netconf:capability:candidate:1.0
  urn:ietf:params:netconf:capability:validate:1.1
  urn:ietf:params:netconf:capability:startup:1.0
  urn:ietf:params:netconf:capability:xpath:1.0
  urn:ietf:params:netconf:capability:notification:1.0
```


# Edit the configuration

The example script `edit_config.py` adds an interface to the configuration:

