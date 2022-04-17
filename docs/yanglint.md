# Yanglint: validating YANG data models

## Introduction

[Yanglint](https://www.mankier.com/1/yanglint)
is command-line tool for validating and converting YANG schemas and YANG modeled data.
It is part of the [libyang](https://github.com/CESNET/libyang) open source project and
implemented in C.

## Install Yanglint

Install `yang-tools` (which includes `yanglint`). On Ubuntu this can be done as follows:

<pre>
$ <b>sudo apt install -y yang-tools</b>
</pre>

Verify that `yanglint` is properly installed:

<pre>
$ <b>yanglint --version</b>
yanglint 0.16.105
</pre>

## Validate a YANG data model

The simplest way of using `yanglint` is to validate the correctness of a YANG data model:

<pre>
$ <b>yanglint interfaces.yang</b>
</pre>

The fact that we get no output means that the YANG file was correct. In addition, the program
returns status code zero, so you can do something like this:

<pre>
$ <b>if yanglint interfaces.yang; then echo "All good"; else "There are errors"; fi</b>
All good
</pre>

Validate YANG data model `bad-interfaces.yang` to see an example of the error messages produced
by `yanglint`:

<pre>
$ <b>yanglint bad-interfaces.yang</b>
err : Invalid keyword "organisation".
err : Module "interfaces" parsing failed.
</pre>


## Convert a YANG data model

YANG data models tend to be very long and verbose. Yanglint can produce a summary of the YANG data
model in a tree format:

<pre>
$ <b>yanglint -f tree interfaces.yang</b>
module: interfaces
  +--rw interfaces
     +--rw interface* [name]
        +--rw name                string
        +--rw ipv4-address?       string
        +--ro sent-packets?       uint64
        +--ro received-packets?   uint64
</pre>

The command `yanglint --tree-help` displays an explanation of the symbols in the tree diagram.

In addition to producing a tree summary, Yanglint can also convert the YANG data model to 
several other formats:

<pre>
$ <b>yanglint --help</b>
Usage:
    yanglint [options] [-f { yang | yin | tree | tree-rfc | jsons}] &lt;file&gt;...
        Validates the YANG module in &lt;file&gt;, and all its dependencies.

    yanglint [options] [-f { xml | json }] &lt;schema>... &lt;file&gt;...
        Validates the YANG modeled data in &lt;file&gt; according to the &lt;schema&gt;.

    yanglint
        Starts interactive mode with more features.

Options:
  -h, --help            Show this help message and exit.

[...]

  -f FORMAT, --format=FORMAT
                        Convert to FORMAT. Supported formats: 
                        yang, yin, tree and jsons (JSON) for schemas,
                        xml, json for data.

[...]
</pre>


As an example, the following example converts the YANG data model to JSON:

<pre>
$ <b>yanglint -f jsons interfaces.yang</B>
{"interfaces":{"namespace":"http://remoteautonomy.com/yang-schemas/interfaces","prefix":"intf","description":{"text":"A simplistic tutorial data model for interfaces on a device."},"organization":{"text":"Remote Autonomy"},"contact":{"text":"Bruno Rijsman\u000Abrunorijsman@remoteautonomy.com"},"yang-version":{"value":"1.0"},"revision":{"2022-03-12":{"description":{"text":"Initial revision."}}},"data":{"interfaces":{"nodetype":"container"}}}}
</pre>

The JSON output is more readable if you pretty print it using [jq](https://manpages.ubuntu.com/manpages/bionic/man1/jq.1.html):

<pre>
$ <b>yanglint -f jsons interfaces.yang | jq</b>
{
  "interfaces": {
    "namespace": "http://remoteautonomy.com/yang-schemas/interfaces",
    "prefix": "intf",
    "description": {
      "text": "A simplistic tutorial data model for interfaces on a device."
    },
    "organization": {
      "text": "Remote Autonomy"
    },
    "contact": {
      "text": "Bruno Rijsman\nbrunorijsman@remoteautonomy.com"
    },
    "yang-version": {
      "value": "1.0"
    },
    "revision": {
      "2022-03-12": {
        "description": {
          "text": "Initial revision."
        }
      }
    },
    "data": {
      "interfaces": {
        "nodetype": "container"
      }
    }
  }
}
</pre>

## Interactive mode

It is also possible to run `yanglint` in interactive mode:

<pre>
$ <b>yanglint</b>
> <b>load interfaces</b>
> <b>print interfaces</b>
module: interfaces
  +--rw interfaces
     +--rw interface* [name]
        +--rw name                string
        +--rw ipv4-address?       string
        +--ro sent-packets?       uint64
        +--ro received-packets?   uint64
> <b>print interfaces -f jsons</b>
{"interfaces":{"namespace":"http://remoteautonomy.com/yang-schemas/interfaces","prefix":"intf","description":{"text":"A simplistic tutorial data model for interfaces on a device."},"organization":{"text":"Remote Autonomy"},"contact":{"text":"Bruno Rijsman\u000Abrunorijsman@remoteautonomy.com"},"yang-version":{"value":"1.0"},"revision":{"2022-03-12":{"description":{"text":"Initial revision."}}},"data":{"interfaces":{"nodetype":"container"}}}}
> <b>quit</b>
</pre>

## Validate and convert instance data

In addition to validating and converting data models, `yanglint` can also validate that instance
data confirms to a given data model and convert instance data.

Consider the following instance data in XML format (these are the contents of file
[`yanglint/data.xml`](https://github.com/brunorijsman/yang-tutorial/blob/main/yanglint/data.xml)
in the YANG tutorial repo):

```xml
<interfaces xmlns="http://remoteautonomy.com/yang-schemas/interfaces">
    <interface>
        <name>eth1</name>
        <ipv4-address>1.1.1.1</ipv4-address>
    </interface>
    <interface>
        <name>eth2</name>
        <ipv4-address>2.2.2.2</ipv4-address>
    </interface>
</interfaces>
```

The following sequence of commends in `yanglint` interactive mode validates that the above
instance data confirms to the `interfaces.yang` data model and converts the instance data from
XML to JSON:

<pre>
$ <b>yanglint</b>
> <b>load interfaces</b>
> <b>data -s -t config yanglint/data.xml -f json</b>
{
  "interfaces:interfaces": {
    "interface": [
      {
        "name": "eth1",
        "ipv4-address": "1.1.1.1"
      },
      {
        "name": "eth2",
        "ipv4-address": "2.2.2.2"
      }
    ]
  }
}
</pre>

Here the `-s` option enables strict validation, the `-t config` option indicates that we are
validating configuration data, and the `-f json` option indicates that the instance data must
be converted to JSON.

We can also perform the instance data validation and conversion from the command-line:

<pre>
$ <b>yanglint -s -t config yanglint/data.xml -f json interfaces.yang</b>
{
  "interfaces:interfaces": {
    "interface": [
      {
        "name": "eth1",
        "ipv4-address": "1.1.1.1"
      },
      {
        "name": "eth2",
        "ipv4-address": "2.2.2.2"
      }
    ]
  }
}
</pre>

Now, to demonstration a validation failure,
consider the following instance data in XML format (these are the contents of file
[`yanglint/bad-data.xml`](https://github.com/brunorijsman/yang-tutorial/blob/main/yanglint/bad-data.xml)
in the YANG tutorial repo).
Note that the IPv4 address is invalid (the first byte 300 is not in the range 0-255).

```xml
<interfaces xmlns="http://remoteautonomy.com/yang-schemas/interfaces">
    <interface>
        <name>eth</name>
        <ipv4-address>300.1.1.1</ipv4-address>
    </interface>
</interfaces>
```

Validating this instance data produces the following error message:

<pre>
$ <b>yanglint -s -t config yanglint/bad-data.xml -f json interfaces.yang</b>
err : Value "300.1.1.1" does not satisfy the constraint "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])" (range, length, or pattern). (/interfaces:interfaces/interface[name='eth']/ipv4-address)
</pre>

## References

* [The yanglint manual page](https://www.mankier.com/1/yanglint)

* [The libyang GitHub repository](https://github.com/CESNET/libyang)

