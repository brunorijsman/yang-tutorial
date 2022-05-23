# Netopeer2

## Introduction

[Netopeer2](https://github.com/CESNET/netopeer2)
is an open source NETCONF server developed by
[CESNET](https://www.cesnet.cz/cesnet/?lang=en),
an association of universities of the Czech Republic and the Czech Academy of Sciences.

## Installation

We use an AWS t2.medium instance with 8 GB of disk running Ubuntu server 22.04 LTS.

Follow the netopeer2 installation instructions documented
[here](https://github.com/CESNET/netopeer2#compilation-and-installation):

Update `apt`:

<pre>
$ <b>sudo apt update</b>
</pre>

If any of the following steps generates a popup window, use tab and enter to select Ok.

Install `cmake`:

<pre>
$ <b>sudo apt install -y cmake</b>
</pre>

Install `libpcre2-dev`:

<pre>
$ <b>sudo apt install -y libpcre2-dev</b>
</pre>

Install `libssh-dev`:

<pre>
$ <b>sudo apt install -y libssh-dev</b>
</pre>

Install `openssl`:

<pre>
$ <b>sudo apt install -y openssl</b>
</pre>

Install `valgrind`:

<pre>
$ <b>sudo apt install -y valgrind</b>
</pre>

Install `libcmocka-dev`:

<pre>
$ <b>sudo apt install -y libcmocka-dev</b>
</pre>

Install `libsystemd-dev`:

<pre>
$ <b>sudo apt install -y libsystemd-dev</b>
</pre>

Install `build-essential`:

<pre>
$ <b>sudo apt install -y build-essential</b>
</pre>

Install `shunit2`:

<pre>
$ <b>sudo apt-get install -y shunit2</b>
</pre>

Install `expect`:

<pre>
$ <b>sudo apt-get install -y expect</b>
</pre>

Clone the `libyang` repo:

<pre>
$ <b>cd ~</b>
$ <b>git clone https://github.com/CESNET/libyang.git</b>
</pre>

Build `libyang` from source code:

<pre>
$ <b>cd libyang</b>
$ <b>mkdir build</b>
$ <b>cd build</b>
$ <b>cmake ..</b>
$ <b>make</b>
$ <b>sudo make install</b>
</pre>

Clone the `libnetconf2` repo:

<pre>
$ <b>cd ~</b>
$ <b>git clone https://github.com/CESNET/libnetconf2.git</b>
</pre>

Build `libnetconf2` from source code:

<pre>
$ <b>cd libnetconf2</b>
$ <b>mkdir build</b>
$ <b>cd build</b>
$ <b>cmake ..</b>
$ <b>make</b>
$ <b>sudo make install</b>
</pre>

Clone the `sysrepo` repo:

<pre>
$ <b>cd ~</b>
$ <b>git clone https://github.com/sysrepo/sysrepo</b>
</pre>

Build `sysrepo` from source code:

<pre>
$ <b>cd sysrepo</b>
$ <b>mkdir build</b>
$ <b>cd build</b>
$ <b>cmake ..</b>
$ <b>make</b>
$ <b>sudo make install</b>
</pre>

Clone the `netopeer2` repo:

<pre>
$ <b>cd ~</b>
$ <b>git clone https://github.com/CESNET/netopeer2.git</b>
</pre>

Build `netopeer2` from source code (note the extra `ldconfig` step):

<pre>
$ <b>cd netopeer2</b>
$ <b>mkdir build</b>
$ <b>cd build</b>
$ <b>cmake ..</b>   
$ <b>make</b>
$ <b>sudo ldconfig</b>
$ <b>sudo make install</b>
</pre>

## Verify installation

Verify that `netopeer2-server` has been installed:

<pre>
$ <b>netopeer2-server -V</b>
netopeer2-server 2.1.23
</pre>

Verify that `netopeer2-cli` has been installed. Type `exit` to return to the shell.

<pre>
$ <b>netopeer2-cli</b>
get_netconf_dir: Configuration directory "/home/ubuntu/.netopeer2-cli" did not exist, created.
load_config: No saved history.
load_config: No saved configuration.
&gt; <b>exit</b>
$s
</pre>

Note: manual pages are available for `netopeer2-server` and `netopeer2-cli`:

<pre>
$ <b>man netopeer2-server</b>
$ <b>man netopeer2-cli</b>
</pre>

Verify that `sysrepo` has been installed:

<pre>
$ <b>sudo sysrepoctl -l</b>
Sysrepo repository: /home/ubuntu/sysrepo/build/repository

Module Name                   | Revision   | Flags | Owner         | Startup Perms | Submodules | Features                                                                                
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
iana-crypt-hash               | 2014-08-06 | i     |               |               |            |                                                                                         
ietf-crypto-types             | 2019-07-02 | I     | ubuntu:ubuntu | 600           |            |                                                                                         
ietf-datastores               | 2018-02-14 | I     | root:root     | 444           |            |                                                                                         
ietf-inet-types               | 2013-07-15 | i     |               |               |            |                                                                                         
ietf-interfaces               | 2018-02-20 | I     | ubuntu:ubuntu | 600           |            |                                                                                         
ietf-ip                       | 2018-02-22 | I     | ubuntu:ubuntu | 600           |            |                                                                                         
ietf-keystore                 | 2019-07-02 | I     | ubuntu:ubuntu | 600           |            | keystore-supported                                                                      
ietf-netconf                  | 2013-09-29 | I     | ubuntu:ubuntu | 600           |            | writable-running candidate confirmed-commit rollback-on-error validate startup url xpath
ietf-netconf-acm              | 2018-02-14 | I     | root:root     | 600           |            |         
...
</pre>

## Set a password for user `ubuntu`

Set the password for user `ubuntu` to `secret` to allows `netopeer2-cli` 
(the NETCONF client) to use password authentication (for now) when connecting to
`netopeer2-server` (the NETCONF server):

<pre>
$ <b>sudo passwd ubuntu</b>
New password: <b>secret</b>
Retype new password: <b>secret</b>
</pre>

## Start the NETCONF server

Start the `netopeer2-server` NETCONF server as a daemon:

<pre>
$ <b>cd ~</b>
$ <b>sudo netopeer2-server</b>
$
</pre>

Verify that the server is running:

<pre>
$ <b>ps aux | grep netopeer2-server</b>
root       18132  0.1  0.1 337832  7372 ?        Ssl  10:54   0:00 netopeer2-server
ubuntu     18144  0.0  0.0   7008  2120 pts/0    S+   10:55   0:00 grep --color=auto netopeer2-server
</pre>


## Start the NETCONF client

Start the `netopeer2-cli` NETCONF client:

<pre>
$ <b>cd ~</b>
$ <b>netopeer2-client</b>
&gt;
</pre>

Enter `help` to see the list of client commands:

<pre>
&gt; <b>help</b>
Available commands:
  auth            Manage SSH authentication options
  knownhosts      Manage the user knownhosts file
  ...
  exit            Quit the program
&gt;
</pre>

Connect the client to the server (running on the same host)

<pre>
&gt; <b>connect</b>
Interactive SSH Authentication
Type your password:
Password: <b>secret</b>
&gt;
</pre>

Retrieve the running configuration:

<pre>
&gt; <b>get-config --source running</b>
</pre>
```
DATA
<data xmlns="urn:ietf:params:xml:ns:netconf:base:1.0">
  <keystore xmlns="urn:ietf:params:xml:ns:yang:ietf-keystore">
    <asymmetric-keys>
      <asymmetric-key>
        <name>genkey</name>
        <algorithm>rsa2048</algorithm>
        <public-key>MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAqIbDXmMsEeQKJhOP9gn4IIO/MwijcOpB9AxjYdMa/WEYjacNXOWAzFHsO8OuYi8gYGo69M+2XtdF4xid3hoE9HPlE3/tOnMA7UBbtbPoYSKei5wN8zobUmtbwJyRHJciyShDKUS8zxM+2P1FoqjIzg0Il3ELfUnxmWoCvDOz1ekkRISuKxDTz2PLnPEqr2HyuBxkMBBRudxfkSfFSQhB7rjPg0UolGOUP+ffOTJuWeodYNnX9NXPc/kKnTNhD2423pANGjFJbM56H6GUpBIDpzuTo6+ds+NcZgYJazk1OiIXpEqLadgVa4nxe/BtbUZYvIccMNbxP4nl6QukjU/74QIDAQAB</public-key>
      </asymmetric-key>
    </asymmetric-keys>
  </keystore>
  <netconf-server xmlns="urn:ietf:params:xml:ns:yang:ietf-netconf-server">
    <listen>
      <endpoint>
        <name>default-ssh</name>
        <ssh>
          <tcp-server-parameters>
            <local-address>0.0.0.0</local-address>
            <keepalives>
              <idle-time>1</idle-time>
              <max-probes>10</max-probes>
              <probe-interval>5</probe-interval>
            </keepalives>
          </tcp-server-parameters>
          <ssh-server-parameters>
            <server-identity>
              <host-key>
                <name>default-key</name>
                <public-key>
                  <keystore-reference>genkey</keystore-reference>
                </public-key>
              </host-key>
            </server-identity>
            <client-authentication>
              <supported-authentication-methods>
                <publickey/>
                <passsword/>
                <other>interactive</other>
              </supported-authentication-methods>
            </client-authentication>
          </ssh-server-parameters>
        </ssh>
      </endpoint>
    </listen>
  </netconf-server>
</data>
```


## TODO

* Certificate-based authentication

* The fancier NETCONF command-line client

* The NETCONF client GUI

* Loading our own YANG data model

* Implementing the back-end for our own YANG data model

## References

* [Netopeer2 GitHub repo](https://github.com/CESNET/netopeer2)

* [Libyang GitHub repo](https://github.com/CESNET/libyang.git)

* [Libnetconf2 GitHub repo](https://github.com/CESNET/libnetconf2.git)

* [Sysrepo homepage](https://www.sysrepo.org/)

* [Sysrepo GitHub repo](https://github.com/sysrepo/sysrepo)
