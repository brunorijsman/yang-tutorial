# YumaPro SDK from YumaWorks

## Introduction

[YumaWorks](https://www.yumaworks.com/) is a company that offers a suite of network management
and control plane automation tools, with a focus on YANG, NETCONF, and RESTCONF.

Their product [YumaPro SDK](https://www.yumaworks.com/tools/multi-protocol-server/)
(Software Development Kit), also referred to as the
multi-protocol network management server toolkit or simply the multi-protocol server,
is a network automation management platform that provides developers a framework for developing
device management interfaces.

YumaPro SDK consists of the following components:

![YumaPro SDK Components](figures/yuma-pro-sdk-components.png)

YumaPro SDK is available in binary and in source code.

There are also YumaPro SDK Basic and YumaPro SDK Basic Plus versions that offer a subset of the
features and that you can use for free for internal use only subject to restrictions
(see the
[license document](https://www.yumaworks.com/download/yumapro-sdk-basic-license/)
for details):

![YumaPro SDK Basic Components](figures/yuma-pro-sdk-basic-components.png)

![YumaPro SDK Feature Comparison](figures/yuma-pro-sdk-feature-comparison.png)

In this tutorial we will be using the basic version.

## Download and install

Download the YumaPro SDK Basic software and documentation from the
[download page](https://www.yumaworks.com/support/download-yumapro-sdk-basic/)
It is available for several Linux distributions; we use Ubuntu 20.04.

Note: we had to use FireFox for the download; when using Chrome the checkbox to agree with the
license agreement does not appear when you scroll down to the bottom of the agreement.

As of 8 September 2022, this downloads files 
`yumapro-sdk-basic-21.10-8.u2004.amd64.deb` (the software) and
`yumapro-doc_21.10-8_all.deb` (the documentation).

Follow the instructions on the
[installation guide](https://www.yumaworks.com/pub/latest/install/yumapro-installation-guide.html)
page.

Update `apt-get` (the instructions don't mention this, but always a prudent first step):

<pre>
$ <b>sudo apt-get update</b>
</pre>

Install `libxml2`:

<pre>
$ <b>sudo apt-get install -y libxml2-dev</b>
</pre>

Install `openssh-server`:

<pre>
$ <b>sudo apt-get install -y openssh-server</b>
</pre>

Install `openssl` and `libssl-dev` (the instructions ask to install `openssl-dev` but that does
not work on Ubuntu):

<pre>
$ <b>sudo apt-get install -y openssl libssl-dev</b>
</pre>

Install `libcurl4-gnutls-dev`:

<pre>
$ <b>sudo apt-get install -y libcurl4-gnutls-dev</b>
</pre>

Install `libfcgi-dev`:

<pre>
$ <b>sudo apt-get install -y libfcgi-dev</b>
</pre>

Install `libssh2-1-dev`:

<pre>
$ <b>sudo apt-get install -y libssh2-1-dev</b>
</pre>

Install `libncurses5-dev`:

<pre>
$ <b>sudo apt-get install -y libncurses5-dev</b>
</pre>

Install `zlib1g-dev`:

<pre>
$ <b>sudo apt-get install -y zlib1g-dev</b>
</pre>

Install the YumaPro SDK Basic software package:

<pre>
$ <b>sudo dpkg -i ~/Downloads/yumapro-sdk-basic-21.10-8.u2004.amd64.deb</b>
</pre>

Verify that YumaPro SDK Basic has been installed:

<pre>
$ <b>/usr/sbin/netconfd-pro --version</b>

Starting netconfd-pro...
Copyright (c) 2008-2012, Andy Bierman, All Rights Reserved.
Copyright (c) 2012-2022, YumaWorks, Inc., All Rights Reserved.

netconfd-pro version 21.10-8-1fcb
</pre>

Install the YumaPro SDK Basic documentation package
(note the `--force-overwrite` option is needed because the software package installed some
documentation files with the same file names):

<pre>
$ <b>sudo dpkg -i --force-overwrite ~/Downloads/yumapro-doc_21.10-8_all.deb</b>
</pre>

Configure SSH:

Edit sshd_config, for example using `vi`:

<pre>
$ <b>sudo vi /etc/ssh/sshd_config</b>
</pre>

And add the following lines:

<pre>
Port 22
Port 830
Subsystem netconf /usr/sbin/netconf-subsystem-pro
</pre>

Generate SSH keys (accept defaults for all prompts):

<pre>
$ <b>ssh-keygen</b>
Generating public/private rsa key pair.
Enter file in which to save the key (/home/parallels/.ssh/id_rsa): 
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/parallels/.ssh/id_rsa
Your public key has been saved in /home/parallels/.ssh/id_rsa.pub
The key fingerprint is:
SHA256:AmezkogmPbMOZhxTcrf00DTydqxv0MyC4j7qTL4NRJA parallels@parallels-Parallels-Virtual-Platform
The key's randomart image is:
+---[RSA 3072]----+
|..   . o         |
|E     = o        |
| o o.+++ o       |
|.o+.o=*o*        |
|o==.ooo=S+       |
|= ++.. .+        |
|.*..     o       |
|*o+.    .        |
|.*+o.            |
+----[SHA256]-----+
</pre>

Restart SSH:

<pre>
$ <b>sudo service ssh restart</b>
</pre>

## Start the server

Start the `netconfd-pro` server:

<pre>
$ <b>netconfd-pro --log-level=debug4 --access-control=off</b>

Starting netconfd-pro...
Copyright (c) 2008-2012, Andy Bierman, All Rights Reserved.
Copyright (c) 2012-2022, YumaWorks, Inc., All Rights Reserved.

<i>...lots of output...</i>

netconfd-pro init OK, ready for sessions

Running netconfd-pro server (21.10-8-1fcb)

Binding to AF_LOCAL socket /tmp/ncxserver.sock

agt_ncxserver: listen ncxsock fd: 3
</pre>

## Start the command line interface (CLI) client

In a separate Terminal window, start the `yangcli-pro` client:

<pre>
$ <b>yangcli-pro</b>
  
  yangcli-pro version 21.10-8
  libssh2 version 1.8.0

  Copyright (c) 2008-2012, Andy Bierman, All Rights Reserved.
  Copyright (c) 2012-2022, YumaWorks, Inc., All Rights Reserved.

<i>...more output...</i>

&gt;
</pre>

Enter the following command in the CLI to connect to the server
(use your Linux username and password, and put the password in quotes if it contains a question mark):

<pre>
&gt; <b>connect server=localhost user=</b><i>&lt;username&gt;</i><b> password</b>=<i>&lt;password&gt;</i></b>

NETCONF 1.1 session established for parallels on localhost

Client Session Id: 1
Server Session Id: 4

<i>...more output...</i>

Protocol version set to: RFC 6241 (base:1.1)
Default target set to: <candidate>
Save operation mapped to: commit
Default with-defaults behavior: explicit
Additional with-defaults behavior: trim,report-all,report-all-tagged
YANG library set to: 1.0 (RFC 7895)
module-set-id: 4269

&gt;

</pre>

Issue an `sget` command to retrieve operational state:

<pre>
&gt; <b>sget /netconf-state/sessions</b>

Filling container /netconf-state/sessions:
RPC Data Reply 2 for session 4 [default]: 

rpc-reply {
  data {
    netconf-state {
      sessions {
        session  4 {
          session-id 4
          transport ncm:netconf-ssh
          username parallels
          source-host 127.0.0.1
          login-time 2022-09-08T14:09:15Z
          in-rpcs 1
          in-bad-rpcs 0
          out-rpc-errors 0
          out-notifications 0
        }
      }
    }
  }
}

&gt;
</pre>

Exit the CLI client:

<pre>
&gt; <b>quit</b>

$
</pre>