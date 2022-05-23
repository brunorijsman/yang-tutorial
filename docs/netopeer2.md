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


## References

* [The netopeer2 GitHub repository](https://github.com/CESNET/netopeer2)
