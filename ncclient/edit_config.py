from ncclient import manager
import netconf_server_info


with manager.connect(host=netconf_server_info.address(),
                     port=830,
                     username=netconf_server_info.username(),
                     password=netconf_server_info.password(),
                     hostkey_verify=False,
                     device_params={'name': 'alu'}) as mgr:

    cfg_interface = """
        <config>
            <interfaces xmlns="http://remoteautonomy.com/yang-schemas/interfaces">
                <config>
                    <interface>
                        <name>eth1</name>
                        <ipv4-address>2.2.2.2</ipv4-address>
                    </interface>
                </config>
            </interfaces>        
        </config>
    """

    reply = mgr.edit_config(target="running", config=cfg_interface, default_operation="merge")
    print(reply)