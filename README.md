--== **A WORK IN PROGRESS** ==--

# A scenic tour through the YANG ecosystem

In this tutorial we will take a hands-on scenic tour through the YANG related ecosystem:

 * Write a simple YANG data model to manage a set of interfaces.

 * Use [pyang](https://github.com/mbj4668/pyang) to validate the YANG data model and to convert it
   to various other formats.

 * Use [clixon](https://clixon-docs.readthedocs.io/en/latest/) to create a server that:
   * Implements the YANG data model.
   * Provides a command line interface (CLI).
   * Provides a NETCONF interface.
   * Provides a RESTCONF interface.
   * Initially provides a mocked backend for fake interfaces.
   * Later on provides a real backend for real interfaces on a Linux host.

* Use the clixon CLI client to access the command line interface provided by the clixon server.

* Use the [MGSoft](https://www.mg-soft.si/) [NETCONF browser](https://www.mg-soft.si/) to access
  the NETCONF interface provided by the clixon server.

* Use [ncclient](https://github.com/ncclient/ncclient) to 

## Write a YANG data model

We are going to start by writing a very simple little YANG data model that we will use throughout
the remainder of this tutorial.

Our data model manages the interfaces on a device. It contains a list of interfaces, and each
interface has a name, an IPv4 address, and counters for the number of sent and received
packets.

In real life, the data models for managing interfaces 
([RFC 8343](https://www.rfc-editor.org/rfc/pdfrfc/rfc8343.txt.pdf))
and for managing IP addresses
([RFC 8344](https://www.rfc-editor.org/rfc/pdfrfc/rfc8344.txt.pdf))
are way more complex, but we are using a simplistic data model in this tutorial to keep the
example code easy to understand.

Here is our data model (you can find it in this repository in the file `tutorial-interfaces.yang`):

```
```




## Pyang

Validate the correctness of the `stove.yang` data model:

<pre>
$ <b>pyang stove.yang</b>
</pre>

Since the data model is correct, this produces no output.

Changing the `organization` statement to the British spelling `organisation` produces the following
error message:

<pre>
$ <b>pyang stove.yang</b>
stove.yang:7: error: unexpected keyword "organisation"
</pre>

Produce a textual tree diagram of the YANG data model:

<pre>
$ <b>pyang -f tree stove.yang</b>
module: stove
  +--rw burners
     +--rw burner* [location]
        +--rw location                         enumeration
        +--rw temperature-setting              int8
        +--ro actual-temperature-in-celcius?   int16
</pre>

The command `pyang --tree-help` displays an explanation of the symbols in the tree diagram.

Produce a javascript tree diagram of the YANG data model for viewing in a web browser:

<pre>
$ <b>pyang -f jstree stove.yang > stove.html</b>
$ <b>open stove.html</b>
</pre>

![foo](figures/stove-html-tree-diagram.png)

Produce a UML diagram of the YANG data model (this requires [PlantUML](https://plantuml.com/)
to be installed):

<pre>
$ <b>pyang -f uml stove.yang > stove.uml</b>
$ <b>plantuml stove.uml</b>
$ <b>open img/stove.png</b>
</pre>

![foo](figures/stove-uml-diagram.png)

```
Convert to FORMAT.  Supported formats are: 
identifiers,
sample-xml-skeleton, capability, jsonxsl, depend,
jtox, name
```


# Installation instructions

## Pyang installation instructions

## Clixon installation instructions



# References

## YANG

## NETMOD

* [The IETF NETMOD working group](https://datatracker.ietf.org/wg/netmod/about/)
* [The IETF NETMOD standards](https://datatracker.ietf.org/wg/netmod/documents/)

## NETCONF

* [The IETF NETCONF working group](https://datatracker.ietf.org/wg/netconf/about/)
* [The IETF NETCONF standards](https://datatracker.ietf.org/wg/netconf/documents/)

## RESTCONF

## Pyang

* [The pyang GitHub repository](https://github.com/mbj4668/pyang)
* [A pyang tutorial](https://www.ietf.org/slides/slides-edu-pyang-tutorial-01.pdf)

## Clixon

* [The clixon GitHub repository](https://github.com/clicon/clixon)
* [Clixon documentation](https://clixon-docs.readthedocs.io/en/latest/)

## Ncclient

## MG-Soft NETCONF browser


