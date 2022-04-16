# Yanglint: validating YANG data models



## Introduction

[Yanglint](https://www.mankier.com/1/yanglint)
is command-line tool for validating and converting YANG schemas and the YANG modeled data.
It is part of the [libyang](https://github.com/CESNET/libyang) open source project and
implemented in C.

## Install Yanglint

To install `yanglint` on Ubuntu:

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

Just to see what happens if there is an error, edit the YANG file and change the word
`organization` to its British spelling `organisation`
(don't forget to change it back afterwards):

<pre>
$ <b>yanglint interfaces.yang</b>
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

## References

* [The pyang GitHub repository](https://github.com/mbj4668/pyang)

* [A pyang tutorial](https://www.ietf.org/slides/slides-edu-pyang-tutorial-01.pdf)

* [The PlantUML home page](https://plantuml.com/)

