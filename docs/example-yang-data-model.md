# An example YANG data model

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
example code short and easy to understand.

Here is our data model (you can find it in this repository in the file `interfaces.yang`):

```
[TODO] @@@ Paste updated data model
[TODO] @@@ Paste updated figures
module interfaces {

    namespace "http://remoteautonomy.com/yang-schemas/interfaces";
    prefix ra-tutin;

    organization
      "Remote Autonomy";

    contact
      "Bruno Rijsman
       brunorijsman@remoteautonomy.com";

    description
        "This is simple data model for the tutorial.";

    revision 2022-03-12 {
        description
          "Initial revision.";
    }

    container interfaces {
        description
          "Interface parameters.";

        list interface {
            key "name";
            description
              "The list of interfaces on the device.";

            leaf name {
                type string;
                description
                  "The name of the interface.";
            }

            leaf ipv4-address {
                type string;
                description
                  "The IPv4 address of the interface.";
            }

            leaf sent-packets {
                type uint64;
                config false;
                description
                  "The number of IPv4 packets sent out over this interface";
            }

            leaf received-packets {
                type uint64;
                config false;
                description
                  "The number of IPv4 packets received over this interface";
            }
        }
    }
}
```

TODO: Add an rpc to the data model