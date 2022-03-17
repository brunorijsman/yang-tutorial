# Installation instructions

TODO: Move these instructions into their respective chapters

All of the installation instructions below are for Ubuntu 12.04.

## Cloning and setting up this repository

Clone this repository:

<pre>
$ <b>git clone https://github.com/brunorijsman/yang-tutorial.git</b>
Cloning into 'yang-tutorial'...
remote: Enumerating objects: 32, done.
remote: Counting objects: 100% (32/32), done.
remote: Compressing objects: 100% (21/21), done.
remote: Total 32 (delta 8), reused 29 (delta 5), pack-reused 0
Unpacking objects: 100% (32/32), 848.05 KiB | 1.58 MiB/s, done.
</pre>

In the remainder of this tutorial I will assume that you cloned the repository into your home
directory. If not, replace `~` with whatever directory you cloned the repository into.

## Setting up a python virtual environment

Make sure that we have version 3.8 or higher of Python installed:

<pre>
$ <b>python3 --version</b>
Python 3.8.10
</pre>

Create a Python virtual environment:

<pre>
$ <b>cd yang-tutorial</b>
$ <b>python3 -m venv venv</b>
</pre>

Activate the Python virtual environment:

<pre>
$ <b>source venv/bin/activate</b>
(venv) $
</pre>

Install the Python dependencies:

<pre>
$ <b>pip install -r requirements.txt</b>
Collecting lxml==4.8.0
  Using cached lxml-4.8.0-cp38-cp38-manylinux_2_17_x86_64.manylinux2014_x86_64.manylinux_2_24_x86_64.whl (6.9 MB)
Collecting pyang==2.5.2
  Using cached pyang-2.5.2-py2.py3-none-any.whl (595 kB)
Installing collected packages: lxml, pyang
Successfully installed lxml-4.8.0 pyang-2.5.2
</pre>

## Pyang installation instructions

If you haven't already done so, follow the instructions for
[cloning and setting up this repository](#cloning-and-setting-up-this-repository)
and the instructions for
[setting up a python virtual environment](#setting-up-a-python-virtual-environment).

If you already did these installation steps previously, don't forget to reactivate your Python
virtual environment if it isn't already active:

<pre>
$ <b>cd ~/yang-tutorial</b>
$ <b>source venv/bin/activate</b>
(env) $
</pre>

If you followed the above installation instructions, the `pyang` Python package was already
installed as part of installing the Python dependencies.

If for some reason you want to install `pyang` separately, use the following command:

<pre>
$ <b>pip install pyang</b>
</pre>

Verify that `pyang` is properly installed:

<pre>
$ <b>pyang --version</b>
pyang 2.5.2
</pre>

One of the examples in the tutorial converts the YANG data model into a UML diagram.
This requires [PlantUML](https://plantuml.com/) to be installed:

<pre>
$ <b>sudo apt install -y plantuml</b>
[...]
</pre>

## Clixon installation instructions

[Clixon](https://github.com/clicon/clixon) is an open source project written in C that offers a
YANG-based configuration data store with plugin APIs for configuration consuming applications and 
with CLI, NETCONF, and RESTCONF frontend interfaces.

TODO: Install dependencies. Use a fresh Ubuntu virtual machine to get the exact steps right.

Clone the `clixon` GitHub repository:

<pre>
$ <b>cd ~</b>

$ <b>git clone https://github.com/clicon/clixon.git</b>
Cloning into 'clixon'...
[...]
</pre>

Build `clixon`:

<pre>
$ <b>cd clixon</b>

$ <b>./configure</b>
debug is no
checking for gcc... gcc
[...]
config.status: creating include/clixon_config.h
config.status: creating lib/clixon/clixon.h

$ <b>make</b>
(cd include && make  all)
make[1]: Entering directory '/home/parallels/test/clixon/include'
[...]
/usr/bin/id
After 'make install' as euid root, build example app and test utils: 'make example'

$ <b>sudo make install</b>
/usr/bin/id
for i in include lib  apps etc yang  doc; \
[...]
To install example app and test utils: make install-example
make[1]: Leaving directory '/home/parallels/test/clixon'
</pre>

We will explain how to start the clixon backend server and the clixon frontend servers for the
CLI, for NETCONF, and for RESTCONF in the main body of the tutorial.

## MG-Soft NETCONF browser instructions


## Ncclient installation instructions

[Ncclient](https://github.com/ncclient/ncclient) (short for NETCONF Client) @@@


