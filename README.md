# YANG open source experiments

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

